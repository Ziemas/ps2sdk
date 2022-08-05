/*
# _____     ___ ____     ___ ____
#  ____|   |    ____|   |        | |____|
# |     ___|   |____ ___|    ____| |    \    PS2DEV Open Source Project.
#-----------------------------------------------------------------------
# Copyright 2001-2022, ps2dev - http://www.ps2dev.org
# Licenced under Academic Free License version 2.0
# Review ps2sdk README & LICENSE files for further details.
*/

#include <cstdio>
#include <vector>
#include <getopt.h>
#include <string>
#include <iterator>
#include <sstream>
#include <fstream>
#include <memory>

static constexpr std::size_t IRX_MAX_NAME = 8;

struct symbol_entry
{
    std::string name {};
    int index {-1};
    bool used {false};
};

struct module_entry
{
    std::string name {};
    int version {0};

    bool used {false};

    std::vector<symbol_entry> symbol_entries {};
};

struct object
{
    std::string filename;
};

struct symbol
{
    std::string name;
    std::shared_ptr<object> owner;

    char flag;
    bool resolved;
};

static std::vector<std::string> split(const std::string &s)
{
    std::vector<std::string> elements;
    std::istringstream iss(s);

    std::copy(std::istream_iterator<std::string>(iss),
              std::istream_iterator<std::string>(),
              std::back_inserter(elements));

    return elements;
}


static std::vector<std::string> read_and_split(std::fstream &in)
{
    std::string line;
    std::getline(in, line);
    return split(line);
}

static module_entry parse_ilb(std::fstream &in)
{
    module_entry entry;
    auto line  = read_and_split(in);
    entry.name = line.at(1);
    line       = read_and_split(in);
    std::sscanf(line.at(1).c_str(), "0x%04x", &entry.version);
    line       = read_and_split(in);
    std::sscanf(line.at(1).c_str(), "0x%04x", &entry.version);

    line = read_and_split(in);
    while (in.good() && line.at(0) == "E") {
        symbol_entry sym;
        sym.index = std::atoi(line.at(1).c_str());
        sym.name  = line.at(2);
        entry.symbol_entries.push_back(sym);
        line = read_and_split(in);
    }

    return entry;
}

static std::vector<module_entry> read_ilbs(std::vector<std::string> &files)
{
    std::vector<module_entry> modules;
    for (auto &f : files) {
        std::fstream file(f, std::fstream::in);
        std::string header;
        std::getline(file, header);
        while (file.good()) {
            modules.push_back(parse_ilb(file));
        }
    }

    return modules;
}

static void write_iop_source(const char *file, std::vector<module_entry> modules)
{
    FILE *fp = fopen(file, "w");
    fprintf(fp, "    .section .module.imports,\"aw\",@progbits\n");
    fprintf(fp, "    .set noreorder\n");
    fprintf(fp, "\n");

    for (auto &entry : modules) {
        if (!entry.used)
            continue;

        fprintf(fp, "    .globl %s_stub\n", entry.name.c_str());
        fprintf(fp, "%s_stub:\n", entry.name.c_str());
        fprintf(fp, "    .word 0x41e00000\n");
        fprintf(fp, "    .word 0x0\n");
        fprintf(fp, "    .word 0x%08x\n", entry.version);
        fprintf(fp, "    .ascii \"%s", entry.name.c_str());
        for (size_t i = 0; i < (IRX_MAX_NAME - entry.name.length()); i++) {
            fprintf(fp, "\\0");
        }
        fprintf(fp, "\"\n");
        fprintf(fp, "    .align 2\n");
        fprintf(fp, "\n");

        for (auto &sym : entry.symbol_entries) {
            if (!sym.used)
                continue;

            fprintf(fp, "    .globl %s\n", sym.name.c_str());
            fprintf(fp, "%s:\n", sym.name.c_str());
            fprintf(fp, "    j $31\n");
            fprintf(fp, "    addiu $0, $0, %d\n", sym.index);
            fprintf(fp, "\n");
        }
        fprintf(fp, "    .word 0\n");
        fprintf(fp, "    .word 0\n");
        fprintf(fp, "\n");
    }

    fclose(fp);
}

static std::vector<symbol> read_objects(char *exe, std::vector<std::string> &files)
{
    std::vector<symbol> symbols;
    for (auto &f : files) {
        auto obj      = std::make_shared<object>();
        obj->filename = f;

        std::string launch(exe);
        launch += " -f posix -g " + f;
        FILE *stream = popen(launch.c_str(), "r");
        char *line   = nullptr;
        size_t len   = 0;

        while (getline(&line, &len, stream) >= 0) {
            symbol sym;
            auto elems = split(line);
            sym.name   = elems[0];
            sym.flag   = elems[1][0];
            sym.owner  = obj;

            symbols.push_back(sym);
        }

        pclose(stream);
        free(line);
    }

    return symbols;
}

static void resolve_object_syms(std::vector<symbol> &symbols, std::vector<module_entry> &modules)
{
    for (auto &sym : symbols) {
        // If undefined or weak: go look through the modules
        if (sym.flag == 'U' || sym.flag == 'V' || sym.flag == 'v' || sym.flag == 'W' || sym.flag == 'w') {
            for (auto &mod : modules) {
                for (auto &fun : mod.symbol_entries) {
                    if (sym.name == fun.name) {
                        fun.used = true;
                        mod.used = true;
                    }
                }
            }
        }
    }
}

static void print_usage()
{
    printf("usage: ./libld [options]\n");
    printf(" options:\n");
    printf(" -s, --source \t Output .s source for stubs\n");
    printf(" -i, --input \t Input list of object files\n");
    printf(" -n, --nm \t Path to nm executable\n");
    printf(" -L, --ilb_path \t ilb search path's\n");
    printf(" -l, --ilbs \t Input list of ilb's\n");
    printf(" -e, --ee \t Generate ERX files\n");
    printf(" -i, --iop \t Generate IRX files\n");
    printf(" -h, --help \t display this text\n");
}

void collect_args(std::vector<std::string> &vec, int argc, char *argv[])
{
    int index = optind - 1;
    while (index != argc) {
        if (argv[index][0] == '-') {
            optind = index;
            break;
        }
        vec.emplace_back(argv[index]);
        index++;
    }
}

int main(int argc, char *argv[])
{
    std::vector<std::string> object_files;
    std::vector<std::string> ilbs_files;
    char *output = nullptr;
    char *nm_exe = nullptr;

    if (argc <= 1) {
        print_usage();
        return -1;
    }

    static option long_options[] = {
        {"source", required_argument, nullptr, 's'},
        {"input", required_argument, nullptr, 'i'},
        {"ilbs", required_argument, nullptr, 'l'},
        {"ilb_path", required_argument, nullptr, 'L'},
        {"nm", required_argument, nullptr, 'n'},
        {"help", no_argument, nullptr, 'h'},
    };

    int c            = 0;
    int option_index = 0;
    while ((c = getopt_long(argc, argv, "s:l:i:n:h", long_options, &option_index)) != -1) {
        switch (c) {
            case 's': {
                output = optarg;
            } break;
            case 'i': {
                collect_args(object_files, argc, argv);
            } break;
            case 'l': {
                collect_args(ilbs_files, argc, argv);
            } break;
            case 'n': {
                nm_exe = optarg;
            } break;
            case 'h': {
                print_usage();
                return 0;
            } break;
        }
    }

    auto libs = read_ilbs(ilbs_files);
    auto syms = read_objects(nm_exe, object_files);
    resolve_object_syms(syms, libs);
    write_iop_source(output, libs);

    return 0;
}
