# [cmake-generators(7)](https://cmake.org/cmake/help/latest/manual/cmake-generators.7.html#id7)

Contents

- [cmake-generators(7)](https://cmake.org/cmake/help/latest/manual/cmake-generators.7.html#cmake-generators-7)
  - [Introduction](https://cmake.org/cmake/help/latest/manual/cmake-generators.7.html#introduction)
  - [CMake Generators](https://cmake.org/cmake/help/latest/manual/cmake-generators.7.html#cmake-generators)
    - [Command-Line Build Tool Generators](https://cmake.org/cmake/help/latest/manual/cmake-generators.7.html#command-line-build-tool-generators)
      - [Makefile Generators](https://cmake.org/cmake/help/latest/manual/cmake-generators.7.html#makefile-generators)
      - [Ninja Generators](https://cmake.org/cmake/help/latest/manual/cmake-generators.7.html#ninja-generators)
    - [IDE Build Tool Generators](https://cmake.org/cmake/help/latest/manual/cmake-generators.7.html#ide-build-tool-generators)
      - [Visual Studio Generators](https://cmake.org/cmake/help/latest/manual/cmake-generators.7.html#visual-studio-generators)
      - [Other Generators](https://cmake.org/cmake/help/latest/manual/cmake-generators.7.html#other-generators)
  - [Extra Generators](https://cmake.org/cmake/help/latest/manual/cmake-generators.7.html#extra-generators)

## [Introduction](https://cmake.org/cmake/help/latest/manual/cmake-generators.7.html#id8)

*CMake 生成器*负责为原生构建系统编写输入文件。必须为构建树选择确切的[CMake 生成器](https://cmake.org/cmake/help/latest/manual/cmake-generators.7.html#cmake-generators)之一，以确定要使用的本机构建系统。可选地，可以选择[额外生成器之一作为某些](https://cmake.org/cmake/help/latest/manual/cmake-generators.7.html#extra-generators)[命令行构建工具生成器](https://cmake.org/cmake/help/latest/manual/cmake-generators.7.html#command-line-build-tool-generators)的变体，以生成辅助 IDE 的项目文件。

CMake 生成器是特定于平台的，因此每个生成器可能仅在某些平台上可用。这[`cmake(1)`](https://cmake.org/cmake/help/latest/manual/cmake.1.html#manual:cmake(1))命令行工具`--help` 输出列出了当前平台上可用的生成器。使用它的`-G` 选项来指定新构建树的生成器。这[`cmake-gui(1)`](https://cmake.org/cmake/help/latest/manual/cmake-gui.1.html#manual:cmake-gui(1))在创建新的构建树时提供生成器的交互式选择。

## [CMake Generators](https://cmake.org/cmake/help/latest/manual/cmake-generators.7.html#id9)

### [Command-Line Build Tool Generators](https://cmake.org/cmake/help/latest/manual/cmake-generators.7.html#id10)

这些生成器支持命令行构建工具。为了使用它们，必须从命令行提示符启动 CMake，其环境已经为所选编译器和构建工具配置。

#### [Makefile Generators](https://cmake.org/cmake/help/latest/manual/cmake-generators.7.html#id11)

- [Borland Makefiles](https://cmake.org/cmake/help/latest/generator/Borland Makefiles.html)
- [MSYS Makefiles](https://cmake.org/cmake/help/latest/generator/MSYS Makefiles.html)
- [MinGW Makefiles](https://cmake.org/cmake/help/latest/generator/MinGW Makefiles.html)
- [NMake Makefiles](https://cmake.org/cmake/help/latest/generator/NMake Makefiles.html)
- [NMake Makefiles JOM](https://cmake.org/cmake/help/latest/generator/NMake Makefiles JOM.html)
- [Unix Makefiles](https://cmake.org/cmake/help/latest/generator/Unix Makefiles.html)
- [Watcom WMake](https://cmake.org/cmake/help/latest/generator/Watcom WMake.html)

#### [Ninja Generators](https://cmake.org/cmake/help/latest/manual/cmake-generators.7.html#id12)

- [Ninja](https://cmake.org/cmake/help/latest/generator/Ninja.html)
- [Ninja Multi-Config](https://cmake.org/cmake/help/latest/generator/Ninja Multi-Config.html)

### [IDE Build Tool Generators](https://cmake.org/cmake/help/latest/manual/cmake-generators.7.html#id13)

这些生成器支持集成开发环境 (IDE) 项目文件。由于 IDE 配置了自己的环境，因此可以从任何环境启动 CMake。

#### [Visual Studio Generators](https://cmake.org/cmake/help/latest/manual/cmake-generators.7.html#id14)

- [Visual Studio 6](https://cmake.org/cmake/help/latest/generator/Visual Studio 6.html)
- [Visual Studio 7](https://cmake.org/cmake/help/latest/generator/Visual Studio 7.html)
- [Visual Studio 7 .NET 2003](https://cmake.org/cmake/help/latest/generator/Visual Studio 7 .NET 2003.html)
- [Visual Studio 8 2005](https://cmake.org/cmake/help/latest/generator/Visual Studio 8 2005.html)
- [Visual Studio 9 2008](https://cmake.org/cmake/help/latest/generator/Visual Studio 9 2008.html)
- [Visual Studio 10 2010](https://cmake.org/cmake/help/latest/generator/Visual Studio 10 2010.html)
- [Visual Studio 11 2012](https://cmake.org/cmake/help/latest/generator/Visual Studio 11 2012.html)
- [Visual Studio 12 2013](https://cmake.org/cmake/help/latest/generator/Visual Studio 12 2013.html)
- [Visual Studio 14 2015](https://cmake.org/cmake/help/latest/generator/Visual Studio 14 2015.html)
- [Visual Studio 15 2017](https://cmake.org/cmake/help/latest/generator/Visual Studio 15 2017.html)
- [Visual Studio 16 2019](https://cmake.org/cmake/help/latest/generator/Visual Studio 16 2019.html)
- [Visual Studio 17 2022](https://cmake.org/cmake/help/latest/generator/Visual Studio 17 2022.html)

#### [Other Generators](https://cmake.org/cmake/help/latest/manual/cmake-generators.7.html#id15)

- [Green Hills MULTI](https://cmake.org/cmake/help/latest/generator/Green Hills MULTI.html)
- [Xcode](https://cmake.org/cmake/help/latest/generator/Xcode.html)

## [Extra Generators](https://cmake.org/cmake/help/latest/manual/cmake-generators.7.html#id16)

中列出的一些[CMake 生成器](https://cmake.org/cmake/help/latest/manual/cmake-generators.7.html#cmake-generators)[`cmake(1)`](https://cmake.org/cmake/help/latest/manual/cmake.1.html#manual:cmake(1)) 命令行工具`--help`输出可能具有为辅助 IDE 工具指定额外生成器的变体。这样的生成器名称具有. CMake 已知以下额外的生成器。`<extra-generator> - <main-generator>`

- [CodeBlocks](https://cmake.org/cmake/help/latest/generator/CodeBlocks.html)
- [CodeLite](https://cmake.org/cmake/help/latest/generator/CodeLite.html)
- [Eclipse CDT4](https://cmake.org/cmake/help/latest/generator/Eclipse CDT4.html)
- [Kate](https://cmake.org/cmake/help/latest/generator/Kate.html)
- [Sublime Text 2](https://cmake.org/cmake/help/latest/generator/Sublime Text 2.html)