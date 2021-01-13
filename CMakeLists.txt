# CMakeList.txt: CMakeProject1 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
cmake_minimum_required (VERSION 3.8)

project ("Sofixer")

# 将源代码添加到此项目的可执行文件。
add_executable (Sofixer "ElfReader.cpp" "ElfReader.h" "ElfRebuilder.cpp" "ElfRebuilder.h" "exelf.h" "FDebug.h" "main.cpp" "elf.h")

# TODO: 如有需要，请添加测试并安装目标。
