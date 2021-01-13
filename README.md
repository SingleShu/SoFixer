so修复相关，so结构研究得不多，勉强够我自己用而已。
使用就是 sofixer -s orig.so -o fix.so -d
如果是从内存中dump出来的，需要加上 -m dumpBase. 可以自动完成重定位的修复。

64位修复没有测试过，应该也没有这个需求吧
原理参考下面的文章
TK so修复参考[http://bbs.pediy.com/thread-191649.htm]

测试用例：Sofixer.exe -s .\libandroidmainruns.so_0xda658000_0x9f000.so -o fix.so -d -m -dumpbase 0x658000

编译过程：
1、windows，visual studio 2019
2、visual studio支持cmake，“用于 Windows 的 C++ CMake 工具”作为“使用 C++ 的桌面开发”和“使用 C++ 的 Linux 开发”工作负载的一部分进行安装。具体查看 https://docs.microsoft.com/zh-cn/cpp/build/cmake-projects-in-visual-studio?view=msvc-160 
3、使用visual studio 打开空项目，打开cmake项目。

也可以使用clion进行配合cygwin编译。或者直接在linux环境下编译。
