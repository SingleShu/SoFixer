#include <iostream>
#include "ElfReader.h"
#include "ElfRebuilder.h"
#include "FDebug.h"


const char* short_options = "hdm:s:o:";

void useage();

int main(int argc, char* argv[]) {
    int c;

    ElfReader elf_reader;

    std::string source, output;
    bool isValidArg = true;
    printf("/*********************************************sofixer***************************************/\n");
    printf("args counts : %d\n",argc);
    for (size_t i = 1; i < argc; )
    {
      char* argStr = argv[i];
      if (strcmp(argStr,"-s") == 0) {
        source = argv[i + 1];
        printf("[main::argcv ]source : %s\n",source.c_str());
        i += 2;
        continue;
      } else if (strcmp(argStr, "-o") == 0) {
        output = argv[i + 1];
        printf("[main::argcv ]output : %s\n", output.c_str());
        i += 2;
        continue;
      } else if (strcmp(argStr, "-m") == 0) {
        auto base = strtoul(argv[i + 1],0,16);
        printf("[main::argcv ]base : 0x%02X\n", base);
        elf_reader.setDumpSoFile(true);
        elf_reader.setDumpSoBaseAddr(base);
        i += 2;
        continue;
      }
      i++;
    }
    if(!isValidArg) {
        useage();
        return -1;
    }

    auto file = fopen(source.c_str(), "rb");
    if(nullptr == file) {
        printf("source so file cannot found!!!\n");
        return -1;
    }
    auto fd = fileno(file);

    printf("start to rebuild elf file\n");
    elf_reader.setSource(source.c_str(), fd);

    if(!elf_reader.Load()) {
        printf("source so file is invalid\n");
        return -1;
    }

    ElfRebuilder elf_rebuilder(&elf_reader);
    if(!elf_rebuilder.Rebuild()) {
        printf("error occured in rebuilding elf file\n");
        return -1;
    }
    fclose(file);

    if (!output.empty()) {
        file = fopen(output.c_str(), "wb+");
        if(nullptr == file) {
            printf("output so file cannot write !!!\n");
            return -1;
        }
        fwrite(elf_rebuilder.getRebuildData(), elf_rebuilder.getRebuildSize(), 1, file);
        fclose(file);
    }

    printf("Done!!!\n");
    return 0;
}

void useage() {
    printf("SoFixer v0.2 author F8LEFT(currwin)\n");
    printf("Useage: SoFixer <option(s)> -s sourcefile -o generatefile\n");
    printf(" try rebuild shdr with phdr\n");
    printf(" Options are:\n");

    printf("  -d --debug                                 Show debug info\n");
    printf("  -m --memso memBaseAddr(16bit format)       Source file is dump from memory from address x\n");
    printf("  -s --source sourceFilePath                 Source file path\n");
    printf("  -o --output generateFilePath               Generate file path\n");
    printf("  -h --help                                  Display this information\n");

}
