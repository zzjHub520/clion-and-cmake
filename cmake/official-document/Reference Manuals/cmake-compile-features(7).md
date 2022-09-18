# [cmake-compile-features(7) ](https://cmake.org/cmake/help/latest/manual/cmake-compile-features.7.html#id2)

内容

- [cmake-编译功能(7)](https://cmake.org/cmake/help/latest/manual/cmake-compile-features.7.html#cmake-compile-features-7)
  - [介绍](https://cmake.org/cmake/help/latest/manual/cmake-compile-features.7.html#introduction)
  - [编译功能要求](https://cmake.org/cmake/help/latest/manual/cmake-compile-features.7.html#compile-feature-requirements)
    - [要求语言标准](https://cmake.org/cmake/help/latest/manual/cmake-compile-features.7.html#requiring-language-standards)
    - [编译器扩展的可用性](https://cmake.org/cmake/help/latest/manual/cmake-compile-features.7.html#availability-of-compiler-extensions)
  - [可选的编译功能](https://cmake.org/cmake/help/latest/manual/cmake-compile-features.7.html#optional-compile-features)
  - [条件编译选项](https://cmake.org/cmake/help/latest/manual/cmake-compile-features.7.html#conditional-compilation-options)
  - [支持的编译器](https://cmake.org/cmake/help/latest/manual/cmake-compile-features.7.html#supported-compilers)

## [Introduction](https://cmake.org/cmake/help/latest/manual/cmake-compile-features.7.html#id3)

项目源代码可能取决于或取决于编译器某些功能的可用性。出现了三个用例： [编译功能要求](https://cmake.org/cmake/help/latest/manual/cmake-compile-features.7.html#compile-feature-requirements)、[可选编译功能](https://cmake.org/cmake/help/latest/manual/cmake-compile-features.7.html#optional-compile-features) 和[条件编译选项](https://cmake.org/cmake/help/latest/manual/cmake-compile-features.7.html#conditional-compilation-options)。

虽然功能通常在编程语言标准中指定，但 CMake 提供了基于对功能的精细处理的主要用户界面，而不是引入该功能的语言标准。

这[`CMAKE_C_KNOWN_FEATURES`](https://cmake.org/cmake/help/latest/prop_gbl/CMAKE_C_KNOWN_FEATURES.html#prop_gbl:CMAKE_C_KNOWN_FEATURES), [`CMAKE_CUDA_KNOWN_FEATURES`](https://cmake.org/cmake/help/latest/prop_gbl/CMAKE_CUDA_KNOWN_FEATURES.html#prop_gbl:CMAKE_CUDA_KNOWN_FEATURES)， 和[`CMAKE_CXX_KNOWN_FEATURES`](https://cmake.org/cmake/help/latest/prop_gbl/CMAKE_CXX_KNOWN_FEATURES.html#prop_gbl:CMAKE_CXX_KNOWN_FEATURES)全局属性包含 CMake 已知的所有功能，无论编译器对该功能的支持如何。这[`CMAKE_C_COMPILE_FEATURES`](https://cmake.org/cmake/help/latest/variable/CMAKE_C_COMPILE_FEATURES.html#variable:CMAKE_C_COMPILE_FEATURES),[`CMAKE_CUDA_COMPILE_FEATURES`](https://cmake.org/cmake/help/latest/variable/CMAKE_CUDA_COMPILE_FEATURES.html#variable:CMAKE_CUDA_COMPILE_FEATURES) ， 和[`CMAKE_CXX_COMPILE_FEATURES`](https://cmake.org/cmake/help/latest/variable/CMAKE_CXX_COMPILE_FEATURES.html#variable:CMAKE_CXX_COMPILE_FEATURES)变量包含 CMake 知道的编译器已知的所有功能，而不管使用它们所需的语言标准或编译标志。

CMake 已知的功能的命名大多遵循与 Clang 功能测试宏相同的约定。有一些例外，例如 CMake 使用`cxx_final`and而不是Clang 使用`cxx_override`的单一 。`cxx_override_control`

`OBJC`请注意，或`OBJCXX`语言没有单独的编译特性属性或变量。这些是基于`C`或`C++` 分别的，因此应该使用它们相应的基本语言的属性和变量。

## [编译功能要求](https://cmake.org/cmake/help/latest/manual/cmake-compile-features.7.html#id4)

编译功能要求可以用 [`target_compile_features()`](https://cmake.org/cmake/help/latest/command/target_compile_features.html#command:target_compile_features)命令。例如，如果一个目标必须在编译器支持的情况下编译 [`cxx_constexpr`](https://cmake.org/cmake/help/latest/prop_gbl/CMAKE_CXX_KNOWN_FEATURES.html#prop_gbl:CMAKE_CXX_KNOWN_FEATURES)特征：

```
add_library(mylib requires_constexpr.cpp)
target_compile_features(mylib PRIVATE cxx_constexpr)
```

在处理对`cxx_constexpr`特征的需求时， [`cmake(1)`](https://cmake.org/cmake/help/latest/manual/cmake.1.html#manual:cmake(1))将确保使用中的 C++ 编译器具有该功能，并将添加任何必要的标志，例如目标`-std=gnu++11` 中 C++ 文件的编译行`mylib`。`FATAL_ERROR`如果编译器不具备该功能，则会发出A。

确切的编译标志和语言标准故意不包含在此用例的用户界面中。CMake 将通过考虑为每个目标指定的功能来计算要使用的适当编译标志。

即使编译器支持没有标志的特定功能，也会添加此类编译标志。例如，即使`-std=gnu++98`使用了 GNU 编译器，它也支持可变参数模板（带有警告）。 如果指定为要求，CMake 添加`-std=gnu++11`标志。`cxx_variadic_templates`

在上面的示例中，它自己构建时`mylib`需要，但消费者不需要使用支持. 如果 的接口 确实需要该功能（或任何其他已知功能），则可以使用或 的签名来指定`cxx_constexpr``mylib``cxx_constexpr``mylib``cxx_constexpr``PUBLIC``INTERFACE`[`target_compile_features()`](https://cmake.org/cmake/help/latest/command/target_compile_features.html#command:target_compile_features):

```
add_library(mylib requires_constexpr.cpp)
# cxx_constexpr is a usage-requirement
target_compile_features(mylib PUBLIC cxx_constexpr)

# main.cpp will be compiled with -std=gnu++11 on GNU for cxx_constexpr.
add_executable(myexe main.cpp)
target_link_libraries(myexe mylib)
```

通过使用链接实现可传递地评估功能需求。看[`cmake-buildsystem(7)`](https://cmake.org/cmake/help/latest/manual/cmake-buildsystem.7.html#manual:cmake-buildsystem(7))有关构建属性和使用要求的传递行为的更多信息。



### [要求语言标准](https://cmake.org/cmake/help/latest/manual/cmake-compile-features.7.html#id5)

在使用来自特定语言标准（例如 C++ 11）的大量常用功能的项目中，可以指定`cxx_std_11`需要使用至少了解该标准的编译器模式的元功能（例如），但可以更大。这比单独指定所有特征要简单，但不能保证任何特定特征的存在。使用不受支持的功能的诊断将延迟到编译时。

例如，如果 C++ 11 的特性在项目的头文件中被广泛使用，那么客户端必须使用不低于 C++ 11 的编译器模式。这可以通过代码请求：

```
target_compile_features(mylib PUBLIC cxx_std_11)
```

在此示例中，CMake 将确保以至少 C++ 11（或 C++ 14、C++ 17、...）的模式调用编译器，并 `-std=gnu++11`在必要时添加标志。这适用于内部的源`mylib` 以及任何依赖项（可能包括来自 的标头`mylib`）。

笔记

 

如果编译器的默认标准级别至少是请求功能的级别，CMake 可能会省略该`-std=`标志。如果编译器的默认扩展模式与[`_EXTENSIONS`](https://cmake.org/cmake/help/latest/prop_tgt/LANG_EXTENSIONS.html#prop_tgt:_EXTENSIONS)目标财产，或者如果[`_STANDARD`](https://cmake.org/cmake/help/latest/prop_tgt/LANG_STANDARD.html#prop_tgt:_STANDARD)目标属性已设置。

### [编译器扩展的可用性](https://cmake.org/cmake/help/latest/manual/cmake-compile-features.7.html#id6)

这[`_EXTENSIONS`](https://cmake.org/cmake/help/latest/prop_tgt/LANG_EXTENSIONS.html#prop_tgt:_EXTENSIONS)target 属性默认为编译器的默认值（参见[`CMAKE__EXTENSIONS_DEFAULT`](https://cmake.org/cmake/help/latest/variable/CMAKE_LANG_EXTENSIONS_DEFAULT.html#variable:CMAKE__EXTENSIONS_DEFAULT)）。请注意，由于大多数编译器默认启用扩展，这可能会暴露用户代码或第三方依赖项的标头中的可移植性错误。

[`_EXTENSIONS`](https://cmake.org/cmake/help/latest/prop_tgt/LANG_EXTENSIONS.html#prop_tgt:_EXTENSIONS)用于默认为`ON`. 看[`CMP0128`](https://cmake.org/cmake/help/latest/policy/CMP0128.html#policy:CMP0128).

## [可选的编译功能](https://cmake.org/cmake/help/latest/manual/cmake-compile-features.7.html#id7)

如果可用，编译功能可能是首选，而不会产生硬性要求。这可以通过*不*指定特征 来实现[`target_compile_features()`](https://cmake.org/cmake/help/latest/command/target_compile_features.html#command:target_compile_features)而是使用项目代码中的预处理器条件检查编译器功能。

在这个用例中，项目可能希望建立一个特定的语言标准（如果可以从编译器获得），并使用预处理器条件来检测实际可用的功能。语言标准可以通过[要求语言标准](https://cmake.org/cmake/help/latest/manual/cmake-compile-features.7.html#requiring-language-standards)使用 [`target_compile_features()`](https://cmake.org/cmake/help/latest/command/target_compile_features.html#command:target_compile_features)具有类似的元特征`cxx_std_11`，或者通过设置[`CXX_STANDARD`](https://cmake.org/cmake/help/latest/prop_tgt/CXX_STANDARD.html#prop_tgt:CXX_STANDARD)目标财产或 [`CMAKE_CXX_STANDARD`](https://cmake.org/cmake/help/latest/variable/CMAKE_CXX_STANDARD.html#variable:CMAKE_CXX_STANDARD)多变的。

另见政策[`CMP0120`](https://cmake.org/cmake/help/latest/policy/CMP0120.html#policy:CMP0120)和有关已弃用的 [示例用法](https://cmake.org/cmake/help/latest/module/WriteCompilerDetectionHeader.html#wcdh-example-usage)的遗留文档 [`WriteCompilerDetectionHeader`](https://cmake.org/cmake/help/latest/module/WriteCompilerDetectionHeader.html#module:WriteCompilerDetectionHeader)模块。

## [条件编译选项](https://cmake.org/cmake/help/latest/manual/cmake-compile-features.7.html#id8)

根据请求的编译器功能，库可能会提供完全不同的头文件。

例如，标题`with_variadics/interface.h`可能包含：

```
template<int I, int... Is>
struct Interface;

template<int I>
struct Interface<I>
{
  static int accumulate()
  {
    return I;
  }
};

template<int I, int... Is>
struct Interface
{
  static int accumulate()
  {
    return I + Interface<Is...>::accumulate();
  }
};
```

虽然标题`no_variadics/interface.h`可能包含：

```
template<int I1, int I2 = 0, int I3 = 0, int I4 = 0>
struct Interface
{
  static int accumulate() { return I1 + I2 + I3 + I4; }
};
```

可以编写一个`interface.h`包含以下内容的抽象标头：

```
#ifdef HAVE_CXX_VARIADIC_TEMPLATES
#include "with_variadics/interface.h"
#else
#include "no_variadics/interface.h"
#endif
```

但是，如果要抽象的文件很多，这可能无法维护。需要的是根据编译器功能使用替代包含目录。

CMake 提供了一个`COMPILE_FEATURES` [`generator expression`](https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html#manual:cmake-generator-expressions(7))执行这些条件。这可以与 build-property 命令一起使用，例如 [`target_include_directories()`](https://cmake.org/cmake/help/latest/command/target_include_directories.html#command:target_include_directories)和[`target_link_libraries()`](https://cmake.org/cmake/help/latest/command/target_link_libraries.html#command:target_link_libraries) 设置适当的[`buildsystem`](https://cmake.org/cmake/help/latest/manual/cmake-buildsystem.7.html#manual:cmake-buildsystem(7)) 特性：

```
add_library(foo INTERFACE)
set(with_variadics ${CMAKE_CURRENT_SOURCE_DIR}/with_variadics)
set(no_variadics ${CMAKE_CURRENT_SOURCE_DIR}/no_variadics)
target_include_directories(foo
  INTERFACE
    "$<$<COMPILE_FEATURES:cxx_variadic_templates>:${with_variadics}>"
    "$<$<NOT:$<COMPILE_FEATURES:cxx_variadic_templates>>:${no_variadics}>"
  )
```

使用代码然后`foo`像往常一样简单地链接到目标并使用适合功能的包含目录

```
add_executable(consumer_with consumer_with.cpp)
target_link_libraries(consumer_with foo)
set_property(TARGET consumer_with CXX_STANDARD 11)

add_executable(consumer_no consumer_no.cpp)
target_link_libraries(consumer_no foo)
```

## [支持的编译器](https://cmake.org/cmake/help/latest/manual/cmake-compile-features.7.html#id9)

CMake 目前知道[`C++ standards`](https://cmake.org/cmake/help/latest/prop_tgt/CXX_STANDARD.html#prop_tgt:CXX_STANDARD) 和[`compile features`](https://cmake.org/cmake/help/latest/prop_gbl/CMAKE_CXX_KNOWN_FEATURES.html#prop_gbl:CMAKE_CXX_KNOWN_FEATURES)可从以下[`compiler ids`](https://cmake.org/cmake/help/latest/variable/CMAKE_LANG_COMPILER_ID.html#variable:CMAKE__COMPILER_ID)从为每个指定的版本开始：

- `AppleClang`: 适用于 Xcode 4.4+ 版本的 Apple Clang。
- `Clang`: Clang 编译器版本 2.9+。
- `GNU`: GNU 编译器版本 4.4+。
- `MSVC`：Microsoft Visual Studio 版本 2010+。
- `SunPro`：Oracle SolarisStudio 版本 12.4+。
- `Intel`：英特尔编译器版本 12.1+。

CMake 目前知道[`C standards`](https://cmake.org/cmake/help/latest/prop_tgt/C_STANDARD.html#prop_tgt:C_STANDARD) 和[`compile features`](https://cmake.org/cmake/help/latest/prop_gbl/CMAKE_C_KNOWN_FEATURES.html#prop_gbl:CMAKE_C_KNOWN_FEATURES)可从以下[`compiler ids`](https://cmake.org/cmake/help/latest/variable/CMAKE_LANG_COMPILER_ID.html#variable:CMAKE__COMPILER_ID)从为每个指定的版本开始：

- 上面列出的所有 C++ 编译器和版本。
- `GNU`: GNU 编译器版本 3.4+

CMake 目前知道[`C++ standards`](https://cmake.org/cmake/help/latest/prop_tgt/CXX_STANDARD.html#prop_tgt:CXX_STANDARD)及其相关的元特征（例如`cxx_std_11`）可从以下获得[`compiler ids`](https://cmake.org/cmake/help/latest/variable/CMAKE_LANG_COMPILER_ID.html#variable:CMAKE__COMPILER_ID)从为每个指定的版本开始：

- `Cray`: Cray 编译器环境版本 8.1+。
- `Fujitsu`: 富士通 HPC 编译器 4.0+。
- `PGI`：PGI 版本 12.10+。
- `NVHPC`: NVIDIA HPC 编译器版本 11.0+。
- `TI`：德州仪器编译器。
- `XL`：IBM XL 版本 10.1+。

CMake 目前知道[`C standards`](https://cmake.org/cmake/help/latest/prop_tgt/C_STANDARD.html#prop_tgt:C_STANDARD)及其相关的元特征（例如`c_std_99`）可从以下获得[`compiler ids`](https://cmake.org/cmake/help/latest/variable/CMAKE_LANG_COMPILER_ID.html#variable:CMAKE__COMPILER_ID)从为每个指定的版本开始：

- 上面列出的所有编译器和版本仅具有 C++ 的元功能。

CMake 目前知道[`CUDA standards`](https://cmake.org/cmake/help/latest/prop_tgt/CUDA_STANDARD.html#prop_tgt:CUDA_STANDARD)及其相关的元特征（例如`cuda_std_11`）可从以下获得[`compiler ids`](https://cmake.org/cmake/help/latest/variable/CMAKE_LANG_COMPILER_ID.html#variable:CMAKE__COMPILER_ID)从为每个指定的版本开始：

- `Clang`: Clang 编译器 5.0+。
- `NVIDIA`: NVIDIA nvcc 编译器 7.5+。