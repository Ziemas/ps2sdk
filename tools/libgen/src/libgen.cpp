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
#include <string>
#include <getopt.h>
#include <fstream>
#include <sstream>
#include <iterator>
#include <vector>

static constexpr std::size_t IRX_MAX_NAME = 8;

struct function_entry
{
    std::string name {};
    std::string name_internal {};
    int index;
};

struct module_data
{
    std::string libname {};
    std::string libname_internal {};
    int version;

    std::vector<function_entry> function_entries {};
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

static module_data parse_table(char *filename)
{
    module_data data;
    std::fstream in(filename);
    std::string line;
    while (std::getline(in, line)) {
        if (line[0] == '#') {
            continue;
        }

        auto elements = split(line);

        if (!elements.size()) {
            continue;
        }

        if ((elements[0].find("library")) != std::string::npos) {
            data.libname = elements[1];
            if (elements.size() > 2) {
                data.libname_internal = elements[1];
            } else {
                data.libname_internal = "_exp_" + elements[1];
            }
        }

        if ((elements[0].find("version")) != std::string::npos) {
            auto pos = elements[1].find('.');
            if (pos != std::string::npos) {
                auto first = elements[1].substr(0, pos);
                auto second = elements[1].substr(pos);
                data.version |= atoi(first.c_str()) << 8;
                data.version |= atoi(second.c_str() + 1);
            } else {
                data.version = atoi(elements[1].c_str());
            }
        }

        if ((elements[0].find("export")) != std::string::npos) {
            function_entry ent;

            ent.index = atoi(elements[1].c_str());
            ent.name = elements[2];

            if (ent.name == "-") {
                ent.name = "";
            } else {
                if (elements.size() > 2) {
                    ent.name_internal = elements[2];
                } else {
                    ent.name_internal = ent.name;
                }
            }

            data.function_entries.push_back(ent);
        }
    }

    return data;
}

static void write_iop_source(module_data &data, char *filename)
{
    FILE *fp = fopen(filename, "w");
    fprintf(fp, ".section .module.exports,\"aw\",@progbits\n");
    fprintf(fp, ".set noreorder\n");
    fprintf(fp, ".globl %s\n", data.libname_internal.c_str());
    fprintf(fp, "%s:\n", data.libname_internal.c_str());
    fprintf(fp, ".word 0x41c00000\n");
    fprintf(fp, ".word 0x0\n");
    fprintf(fp, ".word 0x%08x\n", data.version);
    fprintf(fp, ".ascii \"%s", data.libname.c_str());
    for (size_t i = 0; i < (IRX_MAX_NAME - data.libname.length()); i++) {
        fprintf(fp, "\\0");
    }
    fprintf(fp, "\"\n");
    fprintf(fp, ".align 2\n");

    int index           = 0;
    bool retonly_needed = false;
    for (auto &f : data.function_entries) {
        if (f.name != "") {
            fprintf(fp, ".extern %s\n", f.name_internal.c_str());
            fprintf(fp, ".word %s\n", f.name_internal.c_str());
        } else if (f.name_internal != "") {
            fprintf(fp, ".word _entry_%d\n", index);
        } else {
            fprintf(fp, ".word _retonly\n");
            retonly_needed = true;
        }
        index++;
    }
    fprintf(fp, ".word 0\n"); // 0 to signify end of table
    fprintf(fp, "\n");

    if (retonly_needed) {
        fprintf(fp, "_retonly:\n");
        fprintf(fp, "  j\t$31\n");
        fprintf(fp, "\tnop\n");
        fprintf(fp, "\n");
    }
    fclose(fp);
}


static void write_ilb(module_data &data, char *filename)
{
    FILE *fp = fopen(filename, "w");
    fprintf(fp, "#IOP-ILB#\n");

    fprintf(fp, "L %s\n", data.libname.c_str());

    int idx = 0;
    for (auto &e : data.function_entries) {
        if (e.name != "") {
            fprintf(fp, "E %d %s\n", idx, e.name.c_str());
        }
        idx++;
    }
    fclose(fp);
}

static void print_usage()
{
    printf("usage: ./libgen [options] <library_table>\n");
    printf(" options:\n");
    printf(" -s, --source \t Output .s source for entry\n");
    printf(" -l, --lib \t Output .ilb\n");
    printf(" -h, --help \t display this text\n");
}

int main(int argc, char *argv[])
{
    bool output_source = false, output_ilb = false;
    char *source = nullptr, *ilb = nullptr;

    if (argc <= 1) {
        print_usage();
        return -1;
    }

    static option long_options[] = {
        {"source", required_argument, nullptr, 's'},
        {"lib", required_argument, nullptr, 'l'},
        {"help", no_argument, nullptr, 'h'},
    };

    int option_index = 0;
    int c            = 0;
    while ((c = getopt_long(argc, argv, "s:l:h", long_options, &option_index)) != -1) {
        switch (c) {
            case 's':
                output_source = true;
                source        = optarg;
                break;
            case 'l':
                output_ilb = true;
                ilb        = optarg;
                break;
            case 'h':
                print_usage();
                return 0;
        }
    }

    if (optind == argc) {
        print_usage();
        return -1;
    }

    auto table = parse_table(argv[optind]);

    if (output_ilb) {
        write_ilb(table, ilb);
    }

    if (output_source) {
        write_iop_source(table, source);
    }

    return 0;
}
