# [cmake-buildsystem(7) ](https://cmake.org/cmake/help/latest/manual/cmake-buildsystem.7.html#id14)

内容

- [cmake-buildsystem(7)](https://cmake.org/cmake/help/latest/manual/cmake-buildsystem.7.html#cmake-buildsystem-7)
  - [介绍](https://cmake.org/cmake/help/latest/manual/cmake-buildsystem.7.html#introduction)
  - [二进制目标](https://cmake.org/cmake/help/latest/manual/cmake-buildsystem.7.html#binary-targets)
    - [二进制可执行文件](https://cmake.org/cmake/help/latest/manual/cmake-buildsystem.7.html#binary-executables)
    - [二进制库类型](https://cmake.org/cmake/help/latest/manual/cmake-buildsystem.7.html#binary-library-types)
      - [普通图书馆](https://cmake.org/cmake/help/latest/manual/cmake-buildsystem.7.html#normal-libraries)
        - [苹果框架](https://cmake.org/cmake/help/latest/manual/cmake-buildsystem.7.html#apple-frameworks)
      - [对象库](https://cmake.org/cmake/help/latest/manual/cmake-buildsystem.7.html#object-libraries)
  - [构建规范和使用要求](https://cmake.org/cmake/help/latest/manual/cmake-buildsystem.7.html#build-specification-and-usage-requirements)
    - [目标属性](https://cmake.org/cmake/help/latest/manual/cmake-buildsystem.7.html#target-properties)
    - [传递使用要求](https://cmake.org/cmake/help/latest/manual/cmake-buildsystem.7.html#transitive-usage-requirements)
    - [兼容的接口属性](https://cmake.org/cmake/help/latest/manual/cmake-buildsystem.7.html#compatible-interface-properties)
    - [属性原点调试](https://cmake.org/cmake/help/latest/manual/cmake-buildsystem.7.html#property-origin-debugging)
    - [使用生成器表达式构建规范](https://cmake.org/cmake/help/latest/manual/cmake-buildsystem.7.html#build-specification-with-generator-expressions)
      - [包括目录和使用要求](https://cmake.org/cmake/help/latest/manual/cmake-buildsystem.7.html#include-directories-and-usage-requirements)
    - [链接库和生成器表达式](https://cmake.org/cmake/help/latest/manual/cmake-buildsystem.7.html#link-libraries-and-generator-expressions)
    - [输出工件](https://cmake.org/cmake/help/latest/manual/cmake-buildsystem.7.html#output-artifacts)
      - [运行时输出工件](https://cmake.org/cmake/help/latest/manual/cmake-buildsystem.7.html#runtime-output-artifacts)
      - [库输出工件](https://cmake.org/cmake/help/latest/manual/cmake-buildsystem.7.html#library-output-artifacts)
      - [存档输出工件](https://cmake.org/cmake/help/latest/manual/cmake-buildsystem.7.html#archive-output-artifacts)
    - [目录范围的命令](https://cmake.org/cmake/help/latest/manual/cmake-buildsystem.7.html#directory-scoped-commands)
  - [构建配置](https://cmake.org/cmake/help/latest/manual/cmake-buildsystem.7.html#build-configurations)
    - [区分大小写](https://cmake.org/cmake/help/latest/manual/cmake-buildsystem.7.html#case-sensitivity)
    - [默认和自定义配置](https://cmake.org/cmake/help/latest/manual/cmake-buildsystem.7.html#default-and-custom-configurations)
  - [伪目标](https://cmake.org/cmake/help/latest/manual/cmake-buildsystem.7.html#pseudo-targets)
    - [导入的目标](https://cmake.org/cmake/help/latest/manual/cmake-buildsystem.7.html#imported-targets)
    - [别名目标](https://cmake.org/cmake/help/latest/manual/cmake-buildsystem.7.html#alias-targets)
    - [接口库](https://cmake.org/cmake/help/latest/manual/cmake-buildsystem.7.html#interface-libraries)

## [Introduction](https://cmake.org/cmake/help/latest/manual/cmake-buildsystem.7.html#id15)

基于 CMake 的构建系统被组织为一组高级逻辑目标。每个目标对应一个可执行文件或库，或者是包含自定义命令的自定义目标。目标之间的依赖关系在构建系统中表示，以确定构建顺序和重新生成规则以响应更改。

## [二进制目标](https://cmake.org/cmake/help/latest/manual/cmake-buildsystem.7.html#id16)

可执行文件和库是使用[`add_executable()`](https://cmake.org/cmake/help/latest/command/add_executable.html#command:add_executable) 和[`add_library()`](https://cmake.org/cmake/help/latest/command/add_library.html#command:add_library)命令。生成的二进制文件有适当的[`PREFIX`](https://cmake.org/cmake/help/latest/prop_tgt/PREFIX.html#prop_tgt:PREFIX), [`SUFFIX`](https://cmake.org/cmake/help/latest/prop_tgt/SUFFIX.html#prop_tgt:SUFFIX)和目标平台的扩展。二进制目标之间的依赖关系使用[`target_link_libraries()`](https://cmake.org/cmake/help/latest/command/target_link_libraries.html#command:target_link_libraries)命令：

```
add_library(archive archive.cpp zip.cpp lzma.cpp)
add_executable(zipapp zipapp.cpp)
target_link_libraries(zipapp archive)
```

`archive`被定义为一个`STATIC`库——一个包含从`archive.cpp`、`zip.cpp`和编译的对象的档案`lzma.cpp`。 `zipapp` 被定义为通过编译和链接形成的可执行文件`zipapp.cpp`。链接`zipapp`可执行文件时，将链接`archive`静态库。

### [二进制可执行文件](https://cmake.org/cmake/help/latest/manual/cmake-buildsystem.7.html#id17)

这[`add_executable()`](https://cmake.org/cmake/help/latest/command/add_executable.html#command:add_executable)命令定义一个可执行目标：

```
add_executable(mytool mytool.cpp)
```

命令如[`add_custom_command()`](https://cmake.org/cmake/help/latest/command/add_custom_command.html#command:add_custom_command)，它生成要在构建时运行的规则，可以透明地使用[`EXECUTABLE`](https://cmake.org/cmake/help/latest/prop_tgt/TYPE.html#prop_tgt:TYPE) 目标作为`COMMAND`可执行文件。构建系统规则将确保在尝试运行命令之前构建可执行文件。

### [二进制库类型](https://cmake.org/cmake/help/latest/manual/cmake-buildsystem.7.html#id18)



#### [普通库](https://cmake.org/cmake/help/latest/manual/cmake-buildsystem.7.html#id19)

默认情况下，[`add_library()`](https://cmake.org/cmake/help/latest/command/add_library.html#command:add_library)命令定义一个`STATIC`库，除非指定了类型。使用命令时可以指定类型：

```
add_library(archive SHARED archive.cpp zip.cpp lzma.cpp)
add_library(archive STATIC archive.cpp zip.cpp lzma.cpp)
```

这[`BUILD_SHARED_LIBS`](https://cmake.org/cmake/help/latest/variable/BUILD_SHARED_LIBS.html#variable:BUILD_SHARED_LIBS)变量可以被启用来改变行为[`add_library()`](https://cmake.org/cmake/help/latest/command/add_library.html#command:add_library)默认情况下构建共享库。

在构建系统定义作为一个整体的上下文中，特定库是否是`SHARED`或`STATIC`- 无论库类型如何，命令、依赖规范和其他 API 的工作方式都相似，这在很大程度上是无关紧要的。库`MODULE`类型的不同之处在于它通常不链接到 - 它不用于[`target_link_libraries()`](https://cmake.org/cmake/help/latest/command/target_link_libraries.html#command:target_link_libraries)命令。它是一种使用运行时技术作为插件加载的类型。如果库不导出任何非托管符号（例如 Windows 资源 DLL、C++/CLI DLL），则要求该库不是 `SHARED`库，因为 CMake 期望`SHARED`库至少导出一个符号。

```
add_library(archive MODULE 7z.cpp)
```



##### [苹果框架](https://cmake.org/cmake/help/latest/manual/cmake-buildsystem.7.html#id20)

`SHARED`图书馆可能会标有[`FRAMEWORK`](https://cmake.org/cmake/help/latest/prop_tgt/FRAMEWORK.html#prop_tgt:FRAMEWORK) target 属性来创建一个 macOS 或 iOS 框架包。具有`FRAMEWORK`目标属性的库也应该设置 [`FRAMEWORK_VERSION`](https://cmake.org/cmake/help/latest/prop_tgt/FRAMEWORK_VERSION.html#prop_tgt:FRAMEWORK_VERSION)目标财产。此属性通常按 macOS 约定设置为“A”的值。`MACOSX_FRAMEWORK_IDENTIFIER`sets键，`CFBundleIdentifier`它唯一地标识捆绑包。

```
add_library(MyFramework SHARED MyFramework.cpp)
set_target_properties(MyFramework PROPERTIES
  FRAMEWORK TRUE
  FRAMEWORK_VERSION A # Version "A" is macOS convention
  MACOSX_FRAMEWORK_IDENTIFIER org.cmake.MyFramework
)
```



#### [对象库](https://cmake.org/cmake/help/latest/manual/cmake-buildsystem.7.html#id21)

库`OBJECT`类型定义了由编译给定源文件产生的目标文件的非归档集合。通过使用语法，目标文件集合可以用作其他目标的源输入 `$<TARGET_OBJECTS:name>`。这是一个 [`generator expression`](https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html#manual:cmake-generator-expressions(7))可用于将`OBJECT`库内容提供给其他目标：

```
add_library(archive OBJECT archive.cpp zip.cpp lzma.cpp)

add_library(archiveExtras STATIC $<TARGET_OBJECTS:archive> extras.cpp)

add_executable(test_exe $<TARGET_OBJECTS:archive> test.cpp)
```

这些其他目标的链接（或归档）步骤将使用目标文件集合以及来自它们自己源的那些。

或者，对象库可以链接到其他目标：

```
add_library(archive OBJECT archive.cpp zip.cpp lzma.cpp)

add_library(archiveExtras STATIC extras.cpp)
target_link_libraries(archiveExtras PUBLIC archive)

add_executable(test_exe test.cpp)
target_link_libraries(test_exe archive)
```

这些其他目标的链接（或归档）步骤将使用*直接*链接的`OBJECT`库中的目标文件。此外，在其他目标中编译源代码时，将遵守库的使用要求。此外，这些使用要求将传递到那些其他目标的依赖项。`OBJECT`

对象库不得`TARGET`用作 [`add_custom_command(TARGET)`](https://cmake.org/cmake/help/latest/command/add_custom_command.html#command:add_custom_command)命令签名。但是，对象列表可以由[`add_custom_command(OUTPUT)`](https://cmake.org/cmake/help/latest/command/add_custom_command.html#command:add_custom_command) 或者[`file(GENERATE)`](https://cmake.org/cmake/help/latest/command/file.html#command:file)通过使用`$<TARGET_OBJECTS:objlib>`.

## [构建规范和使用要求](https://cmake.org/cmake/help/latest/manual/cmake-buildsystem.7.html#id22)

这[`target_include_directories()`](https://cmake.org/cmake/help/latest/command/target_include_directories.html#command:target_include_directories), [`target_compile_definitions()`](https://cmake.org/cmake/help/latest/command/target_compile_definitions.html#command:target_compile_definitions) 和[`target_compile_options()`](https://cmake.org/cmake/help/latest/command/target_compile_options.html#command:target_compile_options)命令指定二进制目标的构建规范和使用要求。命令填充 [`INCLUDE_DIRECTORIES`](https://cmake.org/cmake/help/latest/prop_tgt/INCLUDE_DIRECTORIES.html#prop_tgt:INCLUDE_DIRECTORIES), [`COMPILE_DEFINITIONS`](https://cmake.org/cmake/help/latest/prop_tgt/COMPILE_DEFINITIONS.html#prop_tgt:COMPILE_DEFINITIONS)和 [`COMPILE_OPTIONS`](https://cmake.org/cmake/help/latest/prop_tgt/COMPILE_OPTIONS.html#prop_tgt:COMPILE_OPTIONS)目标属性分别，和/或 [`INTERFACE_INCLUDE_DIRECTORIES`](https://cmake.org/cmake/help/latest/prop_tgt/INTERFACE_INCLUDE_DIRECTORIES.html#prop_tgt:INTERFACE_INCLUDE_DIRECTORIES),[`INTERFACE_COMPILE_DEFINITIONS`](https://cmake.org/cmake/help/latest/prop_tgt/INTERFACE_COMPILE_DEFINITIONS.html#prop_tgt:INTERFACE_COMPILE_DEFINITIONS) 和[`INTERFACE_COMPILE_OPTIONS`](https://cmake.org/cmake/help/latest/prop_tgt/INTERFACE_COMPILE_OPTIONS.html#prop_tgt:INTERFACE_COMPILE_OPTIONS)目标属性。

每个命令都有一个`PRIVATE`,`PUBLIC`和`INTERFACE`模式。该 模式仅填充目标属性`PRIVATE`的非变体，并且该模式仅填充变体。该模式会填充相应目标属性的两个变体。每个命令都可以通过每个关键字的多次使用来调用：`INTERFACE_``INTERFACE``INTERFACE_``PUBLIC`

```
target_compile_definitions(archive
  PRIVATE BUILDING_WITH_LZMA
  INTERFACE USING_ARCHIVE_LIB
)
```

请注意，使用要求并不是为了让下游使用特定的[`COMPILE_OPTIONS`](https://cmake.org/cmake/help/latest/prop_tgt/COMPILE_OPTIONS.html#prop_tgt:COMPILE_OPTIONS)或者 [`COMPILE_DEFINITIONS`](https://cmake.org/cmake/help/latest/prop_tgt/COMPILE_DEFINITIONS.html#prop_tgt:COMPILE_DEFINITIONS)等只是为了方便。属性的内容必须是**要求**，而不仅仅是建议或方便。

请参阅[创建可重定位包](https://cmake.org/cmake/help/latest/manual/cmake-packages.7.html#creating-relocatable-packages)部分 [`cmake-packages(7)`](https://cmake.org/cmake/help/latest/manual/cmake-packages.7.html#manual:cmake-packages(7))手册，用于讨论在创建用于重新分发的包时指定使用要求时必须注意的额外注意事项。

### [目标属性](https://cmake.org/cmake/help/latest/manual/cmake-buildsystem.7.html#id23)

的内容[`INCLUDE_DIRECTORIES`](https://cmake.org/cmake/help/latest/prop_tgt/INCLUDE_DIRECTORIES.html#prop_tgt:INCLUDE_DIRECTORIES), [`COMPILE_DEFINITIONS`](https://cmake.org/cmake/help/latest/prop_tgt/COMPILE_DEFINITIONS.html#prop_tgt:COMPILE_DEFINITIONS)和[`COMPILE_OPTIONS`](https://cmake.org/cmake/help/latest/prop_tgt/COMPILE_OPTIONS.html#prop_tgt:COMPILE_OPTIONS)在编译二进制目标的源文件时，适当地使用目标属性。

中的条目[`INCLUDE_DIRECTORIES`](https://cmake.org/cmake/help/latest/prop_tgt/INCLUDE_DIRECTORIES.html#prop_tgt:INCLUDE_DIRECTORIES)`-I`被添加到带有或前缀的编译行中，`-isystem`并按照属性值中出现的顺序。

中的条目[`COMPILE_DEFINITIONS`](https://cmake.org/cmake/help/latest/prop_tgt/COMPILE_DEFINITIONS.html#prop_tgt:COMPILE_DEFINITIONS)`-D`以or 为前缀，`/D`并以未指定的顺序添加到编译行。这 [`DEFINE_SYMBOL`](https://cmake.org/cmake/help/latest/prop_tgt/DEFINE_SYMBOL.html#prop_tgt:DEFINE_SYMBOL)`SHARED`target 属性也被添加为编译定义，作为`MODULE` 库目标的特殊便利用例。

中的条目[`COMPILE_OPTIONS`](https://cmake.org/cmake/help/latest/prop_tgt/COMPILE_OPTIONS.html#prop_tgt:COMPILE_OPTIONS)为 shell 转义并按属性值中出现的顺序添加。几个编译选项有特殊的单独处理，例如[`POSITION_INDEPENDENT_CODE`](https://cmake.org/cmake/help/latest/prop_tgt/POSITION_INDEPENDENT_CODE.html#prop_tgt:POSITION_INDEPENDENT_CODE).

的内容[`INTERFACE_INCLUDE_DIRECTORIES`](https://cmake.org/cmake/help/latest/prop_tgt/INTERFACE_INCLUDE_DIRECTORIES.html#prop_tgt:INTERFACE_INCLUDE_DIRECTORIES), [`INTERFACE_COMPILE_DEFINITIONS`](https://cmake.org/cmake/help/latest/prop_tgt/INTERFACE_COMPILE_DEFINITIONS.html#prop_tgt:INTERFACE_COMPILE_DEFINITIONS)和 [`INTERFACE_COMPILE_OPTIONS`](https://cmake.org/cmake/help/latest/prop_tgt/INTERFACE_COMPILE_OPTIONS.html#prop_tgt:INTERFACE_COMPILE_OPTIONS)目标属性是 *使用要求*——它们指定消费者必须使用哪些内容来正确编译并链接到它们出现的目标。对于任何二进制目标，`INTERFACE_`每个目标上的每个属性的内容都在[`target_link_libraries()`](https://cmake.org/cmake/help/latest/command/target_link_libraries.html#command:target_link_libraries)命令被消耗：

```
set(srcs archive.cpp zip.cpp)
if (LZMA_FOUND)
  list(APPEND srcs lzma.cpp)
endif()
add_library(archive SHARED ${srcs})
if (LZMA_FOUND)
  # The archive library sources are compiled with -DBUILDING_WITH_LZMA
  target_compile_definitions(archive PRIVATE BUILDING_WITH_LZMA)
endif()
target_compile_definitions(archive INTERFACE USING_ARCHIVE_LIB)

add_executable(consumer)
# Link consumer to archive and consume its usage requirements. The consumer
# executable sources are compiled with -DUSING_ARCHIVE_LIB.
target_link_libraries(consumer archive)
```

因为通常要求将源目录和相应的构建目录添加到[`INCLUDE_DIRECTORIES`](https://cmake.org/cmake/help/latest/prop_tgt/INCLUDE_DIRECTORIES.html#prop_tgt:INCLUDE_DIRECTORIES)， 这 [`CMAKE_INCLUDE_CURRENT_DIR`](https://cmake.org/cmake/help/latest/variable/CMAKE_INCLUDE_CURRENT_DIR.html#variable:CMAKE_INCLUDE_CURRENT_DIR)可以启用变量，方便地将对应的目录添加到[`INCLUDE_DIRECTORIES`](https://cmake.org/cmake/help/latest/prop_tgt/INCLUDE_DIRECTORIES.html#prop_tgt:INCLUDE_DIRECTORIES)的所有目标。变量[`CMAKE_INCLUDE_CURRENT_DIR_IN_INTERFACE`](https://cmake.org/cmake/help/latest/variable/CMAKE_INCLUDE_CURRENT_DIR_IN_INTERFACE.html#variable:CMAKE_INCLUDE_CURRENT_DIR_IN_INTERFACE) 可以启用将相应的目录添加到 [`INTERFACE_INCLUDE_DIRECTORIES`](https://cmake.org/cmake/help/latest/prop_tgt/INTERFACE_INCLUDE_DIRECTORIES.html#prop_tgt:INTERFACE_INCLUDE_DIRECTORIES)的所有目标。这使得通过使用 [`target_link_libraries()`](https://cmake.org/cmake/help/latest/command/target_link_libraries.html#command:target_link_libraries)命令。



### [传递使用要求](https://cmake.org/cmake/help/latest/manual/cmake-buildsystem.7.html#id24)

目标的使用要求可以传递到依赖项。这[`target_link_libraries()`](https://cmake.org/cmake/help/latest/command/target_link_libraries.html#command:target_link_libraries)命令有`PRIVATE`, `INTERFACE`和`PUBLIC`关键字来控制传播。

```
add_library(archive archive.cpp)
target_compile_definitions(archive INTERFACE USING_ARCHIVE_LIB)

add_library(serialization serialization.cpp)
target_compile_definitions(serialization INTERFACE USING_SERIALIZATION_LIB)

add_library(archiveExtras extras.cpp)
target_link_libraries(archiveExtras PUBLIC archive)
target_link_libraries(archiveExtras PRIVATE serialization)
# archiveExtras is compiled with -DUSING_ARCHIVE_LIB
# and -DUSING_SERIALIZATION_LIB

add_executable(consumer consumer.cpp)
# consumer is compiled with -DUSING_ARCHIVE_LIB
target_link_libraries(consumer archiveExtras)
```

因为`archive`是 的`PUBLIC`依赖关系`archiveExtras`，所以它的使用要求也会传播到`consumer`。因为 `serialization`是 的`PRIVATE`依赖项`archiveExtras`，所以它的使用要求不会传播到`consumer`.

通常，应在使用中指定依赖项 [`target_link_libraries()`](https://cmake.org/cmake/help/latest/command/target_link_libraries.html#command:target_link_libraries)`PRIVATE`如果它仅用于库的实现，而不是在头文件中，则使用关键字。如果在库的头文件中额外使用了依赖项（例如，用于类继承），则应将其指定为`PUBLIC`依赖项。一个不被库的实现使用，但只被它的头文件使用的依赖应该被指定为`INTERFACE`依赖。这 [`target_link_libraries()`](https://cmake.org/cmake/help/latest/command/target_link_libraries.html#command:target_link_libraries)可以通过多次使用每个关键字来调用命令：

```
target_link_libraries(archiveExtras
  PUBLIC archive
  PRIVATE serialization
)
```

`INTERFACE_`通过从依赖项中读取目标属性的变体并将值附加到操作数的非变体来传播使用要求`INTERFACE_`。例如， [`INTERFACE_INCLUDE_DIRECTORIES`](https://cmake.org/cmake/help/latest/prop_tgt/INTERFACE_INCLUDE_DIRECTORIES.html#prop_tgt:INTERFACE_INCLUDE_DIRECTORIES)的依赖项被读取并附加到[`INCLUDE_DIRECTORIES`](https://cmake.org/cmake/help/latest/prop_tgt/INCLUDE_DIRECTORIES.html#prop_tgt:INCLUDE_DIRECTORIES)的操作数。在订单相关且维持的情况下，以及由 [`target_link_libraries()`](https://cmake.org/cmake/help/latest/command/target_link_libraries.html#command:target_link_libraries)调用不允许正确编译，使用适当的命令直接设置属性可能会更新顺序。

例如，如果必须按顺序指定目标的链接库`lib1` `lib2` `lib3`，但必须按顺序指定包含目录`lib3` `lib1` `lib2`：

```
target_link_libraries(myExe lib1 lib2 lib3)
target_include_directories(myExe
  PRIVATE $<TARGET_PROPERTY:lib3,INTERFACE_INCLUDE_DIRECTORIES>)
```

请注意，在指定目标的使用要求时必须小心，这些目标将使用[`install(EXPORT)`](https://cmake.org/cmake/help/latest/command/install.html#command:install) 命令。有关更多信息，请参阅[创建包](https://cmake.org/cmake/help/latest/manual/cmake-packages.7.html#creating-packages)。



### [兼容的接口属性](https://cmake.org/cmake/help/latest/manual/cmake-buildsystem.7.html#id25)

一些目标属性需要在目标和每个依赖项的接口之间兼容。例如， [`POSITION_INDEPENDENT_CODE`](https://cmake.org/cmake/help/latest/prop_tgt/POSITION_INDEPENDENT_CODE.html#prop_tgt:POSITION_INDEPENDENT_CODE)目标属性可以指定一个目标是否应该编译为与位置无关的代码的布尔值，这具有特定于平台的后果。目标还可以指定使用要求 [`INTERFACE_POSITION_INDEPENDENT_CODE`](https://cmake.org/cmake/help/latest/prop_tgt/INTERFACE_POSITION_INDEPENDENT_CODE.html#prop_tgt:INTERFACE_POSITION_INDEPENDENT_CODE)传达消费者必须编译为与位置无关的代码。

```
add_executable(exe1 exe1.cpp)
set_property(TARGET exe1 PROPERTY POSITION_INDEPENDENT_CODE ON)

add_library(lib1 SHARED lib1.cpp)
set_property(TARGET lib1 PROPERTY INTERFACE_POSITION_INDEPENDENT_CODE ON)

add_executable(exe2 exe2.cpp)
target_link_libraries(exe2 lib1)
```

在这里，`exe1`和`exe2`都将被编译为与位置无关的代码。 `lib1`也将被编译为与位置无关的代码，因为这是`SHARED`库的默认设置。如果依赖项有冲突、不兼容的要求[`cmake(1)`](https://cmake.org/cmake/help/latest/manual/cmake.1.html#manual:cmake(1))发出诊断：

```
add_library(lib1 SHARED lib1.cpp)
set_property(TARGET lib1 PROPERTY INTERFACE_POSITION_INDEPENDENT_CODE ON)

add_library(lib2 SHARED lib2.cpp)
set_property(TARGET lib2 PROPERTY INTERFACE_POSITION_INDEPENDENT_CODE OFF)

add_executable(exe1 exe1.cpp)
target_link_libraries(exe1 lib1)
set_property(TARGET exe1 PROPERTY POSITION_INDEPENDENT_CODE OFF)

add_executable(exe2 exe2.cpp)
target_link_libraries(exe2 lib1 lib2)
```

该`lib1`要求`INTERFACE_POSITION_INDEPENDENT_CODE`与[`POSITION_INDEPENDENT_CODE`](https://cmake.org/cmake/help/latest/prop_tgt/POSITION_INDEPENDENT_CODE.html#prop_tgt:POSITION_INDEPENDENT_CODE)目标的属性`exe1`。该库要求将消费者构建为与位置无关的代码，而可执行文件指定不构建为与位置无关的代码，因此会发出诊断。

和要求不“兼容” `lib1`。`lib2`其中一个要求消费者构建为与位置无关的代码，而另一个要求消费者不构建为与位置无关的代码。因为`exe2`两者的链接存在冲突，所以会发出 CMake 错误消息：

```
CMake Error: The INTERFACE_POSITION_INDEPENDENT_CODE property of "lib2" does
not agree with the value of POSITION_INDEPENDENT_CODE already determined
for "exe2".
```

为了“兼容”，[`POSITION_INDEPENDENT_CODE`](https://cmake.org/cmake/help/latest/prop_tgt/POSITION_INDEPENDENT_CODE.html#prop_tgt:POSITION_INDEPENDENT_CODE)属性，如果设置必须是相同的，在布尔意义上，作为 [`INTERFACE_POSITION_INDEPENDENT_CODE`](https://cmake.org/cmake/help/latest/prop_tgt/INTERFACE_POSITION_INDEPENDENT_CODE.html#prop_tgt:INTERFACE_POSITION_INDEPENDENT_CODE)设置该属性的所有可传递指定依赖项的属性。

这个“兼容接口要求”的属性可以通过在 [`COMPATIBLE_INTERFACE_BOOL`](https://cmake.org/cmake/help/latest/prop_tgt/COMPATIBLE_INTERFACE_BOOL.html#prop_tgt:COMPATIBLE_INTERFACE_BOOL)目标财产。每个指定的属性必须在消费目标和对应的属性之间兼容，并带有`INTERFACE_`来自每个依赖项的前缀：

```
add_library(lib1Version2 SHARED lib1_v2.cpp)
set_property(TARGET lib1Version2 PROPERTY INTERFACE_CUSTOM_PROP ON)
set_property(TARGET lib1Version2 APPEND PROPERTY
  COMPATIBLE_INTERFACE_BOOL CUSTOM_PROP
)

add_library(lib1Version3 SHARED lib1_v3.cpp)
set_property(TARGET lib1Version3 PROPERTY INTERFACE_CUSTOM_PROP OFF)

add_executable(exe1 exe1.cpp)
target_link_libraries(exe1 lib1Version2) # CUSTOM_PROP will be ON

add_executable(exe2 exe2.cpp)
target_link_libraries(exe2 lib1Version2 lib1Version3) # Diagnostic
```

非布尔属性也可能参与“兼容接口”计算。中指定的属性 [`COMPATIBLE_INTERFACE_STRING`](https://cmake.org/cmake/help/latest/prop_tgt/COMPATIBLE_INTERFACE_STRING.html#prop_tgt:COMPATIBLE_INTERFACE_STRING) 属性必须要么未指定，要么与所有可传递指定的依赖项中的相同字符串进行比较。这对于确保一个库的多个不兼容版本不会通过目标的传递要求链接在一起很有用：

```
add_library(lib1Version2 SHARED lib1_v2.cpp)
set_property(TARGET lib1Version2 PROPERTY INTERFACE_LIB_VERSION 2)
set_property(TARGET lib1Version2 APPEND PROPERTY
  COMPATIBLE_INTERFACE_STRING LIB_VERSION
)

add_library(lib1Version3 SHARED lib1_v3.cpp)
set_property(TARGET lib1Version3 PROPERTY INTERFACE_LIB_VERSION 3)

add_executable(exe1 exe1.cpp)
target_link_libraries(exe1 lib1Version2) # LIB_VERSION will be "2"

add_executable(exe2 exe2.cpp)
target_link_libraries(exe2 lib1Version2 lib1Version3) # Diagnostic
```

这[`COMPATIBLE_INTERFACE_NUMBER_MAX`](https://cmake.org/cmake/help/latest/prop_tgt/COMPATIBLE_INTERFACE_NUMBER_MAX.html#prop_tgt:COMPATIBLE_INTERFACE_NUMBER_MAX)target 属性指定内容将以数字方式评估，并计算所有指定内容中的最大数量：

```
add_library(lib1Version2 SHARED lib1_v2.cpp)
set_property(TARGET lib1Version2 PROPERTY INTERFACE_CONTAINER_SIZE_REQUIRED 200)
set_property(TARGET lib1Version2 APPEND PROPERTY
  COMPATIBLE_INTERFACE_NUMBER_MAX CONTAINER_SIZE_REQUIRED
)

add_library(lib1Version3 SHARED lib1_v3.cpp)
set_property(TARGET lib1Version3 PROPERTY INTERFACE_CONTAINER_SIZE_REQUIRED 1000)

add_executable(exe1 exe1.cpp)
# CONTAINER_SIZE_REQUIRED will be "200"
target_link_libraries(exe1 lib1Version2)

add_executable(exe2 exe2.cpp)
# CONTAINER_SIZE_REQUIRED will be "1000"
target_link_libraries(exe2 lib1Version2 lib1Version3)
```

同样，[`COMPATIBLE_INTERFACE_NUMBER_MIN`](https://cmake.org/cmake/help/latest/prop_tgt/COMPATIBLE_INTERFACE_NUMBER_MIN.html#prop_tgt:COMPATIBLE_INTERFACE_NUMBER_MIN)可用于从依赖项中计算属性的数值最小值。

每个计算的“兼容”属性值都可以在生成时使用生成器表达式在消费者中读取。

请注意，对于每个依赖项，每个兼容接口属性中指定的属性集不得与任何其他属性中指定的属性集相交。

### [属性源调试](https://cmake.org/cmake/help/latest/manual/cmake-buildsystem.7.html#id26)

因为构建规范可以由依赖关系确定，所以创建目标的代码和负责设置构建规范的代码缺乏局部性可能会使代码更难推理。 [`cmake(1)`](https://cmake.org/cmake/help/latest/manual/cmake.1.html#manual:cmake(1))提供了一个调试工具来打印可能由依赖关系确定的属性内容的来源。可以调试的属性列在 [`CMAKE_DEBUG_TARGET_PROPERTIES`](https://cmake.org/cmake/help/latest/variable/CMAKE_DEBUG_TARGET_PROPERTIES.html#variable:CMAKE_DEBUG_TARGET_PROPERTIES)可变文档：

```
set(CMAKE_DEBUG_TARGET_PROPERTIES
  INCLUDE_DIRECTORIES
  COMPILE_DEFINITIONS
  POSITION_INDEPENDENT_CODE
  CONTAINER_SIZE_REQUIRED
  LIB_VERSION
)
add_executable(exe1 exe1.cpp)
```

在列出的属性的情况下[`COMPATIBLE_INTERFACE_BOOL`](https://cmake.org/cmake/help/latest/prop_tgt/COMPATIBLE_INTERFACE_BOOL.html#prop_tgt:COMPATIBLE_INTERFACE_BOOL)或者 [`COMPATIBLE_INTERFACE_STRING`](https://cmake.org/cmake/help/latest/prop_tgt/COMPATIBLE_INTERFACE_STRING.html#prop_tgt:COMPATIBLE_INTERFACE_STRING)，调试输出显示哪个目标负责设置属性，以及哪些其他依赖项也定义了该属性。如果是 [`COMPATIBLE_INTERFACE_NUMBER_MAX`](https://cmake.org/cmake/help/latest/prop_tgt/COMPATIBLE_INTERFACE_NUMBER_MAX.html#prop_tgt:COMPATIBLE_INTERFACE_NUMBER_MAX)和 [`COMPATIBLE_INTERFACE_NUMBER_MIN`](https://cmake.org/cmake/help/latest/prop_tgt/COMPATIBLE_INTERFACE_NUMBER_MIN.html#prop_tgt:COMPATIBLE_INTERFACE_NUMBER_MIN)，调试输出显示来自每个依赖项的属性值，以及该值是否决定了新的极值。

### [使用生成器表达式构建规范](https://cmake.org/cmake/help/latest/manual/cmake-buildsystem.7.html#id27)

构建规范可以使用 [`generator expressions`](https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html#manual:cmake-generator-expressions(7))包含可能是有条件的或仅在生成时才知道的内容。例如，属性的计算“兼容”值可以使用以下 `TARGET_PROPERTY`表达式读取：

```
add_library(lib1Version2 SHARED lib1_v2.cpp)
set_property(TARGET lib1Version2 PROPERTY
  INTERFACE_CONTAINER_SIZE_REQUIRED 200)
set_property(TARGET lib1Version2 APPEND PROPERTY
  COMPATIBLE_INTERFACE_NUMBER_MAX CONTAINER_SIZE_REQUIRED
)

add_executable(exe1 exe1.cpp)
target_link_libraries(exe1 lib1Version2)
target_compile_definitions(exe1 PRIVATE
    CONTAINER_SIZE=$<TARGET_PROPERTY:CONTAINER_SIZE_REQUIRED>
)
```

在这种情况下，`exe1`源文件将使用 `-DCONTAINER_SIZE=200`.

一元`TARGET_PROPERTY`生成器表达式和`TARGET_POLICY` 生成器表达式使用消费目标上下文进行评估。这意味着可以根据消费者对使用要求规范进行不同的评估：

```
add_library(lib1 lib1.cpp)
target_compile_definitions(lib1 INTERFACE
  $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,EXECUTABLE>:LIB1_WITH_EXE>
  $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,SHARED_LIBRARY>:LIB1_WITH_SHARED_LIB>
  $<$<TARGET_POLICY:CMP0041>:CONSUMER_CMP0041_NEW>
)

add_executable(exe1 exe1.cpp)
target_link_libraries(exe1 lib1)

cmake_policy(SET CMP0041 NEW)

add_library(shared_lib shared_lib.cpp)
target_link_libraries(shared_lib lib1)
```

`exe1`可执行文件将使用 编译，`-DLIB1_WITH_EXE`而 `shared_lib`共享库将使用`-DLIB1_WITH_SHARED_LIB` and编译`-DCONSUMER_CMP0041_NEW`，因为策略[`CMP0041`](https://cmake.org/cmake/help/latest/policy/CMP0041.html#policy:CMP0041)位于 创建目标`NEW`的位置`shared_lib`。

该`BUILD_INTERFACE`表达式包装了要求，这些要求仅在从同一构建系统中的目标使用时使用，或者从使用导出到构建目录的目标使用时使用[`export()`](https://cmake.org/cmake/help/latest/command/export.html#command:export)命令。该 `INSTALL_INTERFACE`表达式包装了仅在从已安装并导出的目标中使用时使用的需求 [`install(EXPORT)`](https://cmake.org/cmake/help/latest/command/install.html#command:install)命令：

```
add_library(ClimbingStats climbingstats.cpp)
target_compile_definitions(ClimbingStats INTERFACE
  $<BUILD_INTERFACE:ClimbingStats_FROM_BUILD_LOCATION>
  $<INSTALL_INTERFACE:ClimbingStats_FROM_INSTALLED_LOCATION>
)
install(TARGETS ClimbingStats EXPORT libExport ${InstallArgs})
install(EXPORT libExport NAMESPACE Upstream::
        DESTINATION lib/cmake/ClimbingStats)
export(EXPORT libExport NAMESPACE Upstream::)

add_executable(exe1 exe1.cpp)
target_link_libraries(exe1 ClimbingStats)
```

在这种情况下，`exe1`可执行文件将使用 `-DClimbingStats_FROM_BUILD_LOCATION`. 导出命令生成 [`IMPORTED`](https://cmake.org/cmake/help/latest/prop_tgt/IMPORTED.html#prop_tgt:IMPORTED)带有`INSTALL_INTERFACE`或 `BUILD_INTERFACE`省略的目标，并且`*_INTERFACE`标记被剥离。使用该`ClimbingStats`包的单独项目将包含：

```
find_package(ClimbingStats REQUIRED)

add_executable(Downstream main.cpp)
target_link_libraries(Downstream Upstream::ClimbingStats)
```

根据`ClimbingStats`是从构建位置还是安装位置使用包，`Downstream`目标将使用`-DClimbingStats_FROM_BUILD_LOCATION`或 编译`-DClimbingStats_FROM_INSTALL_LOCATION`。有关包和导出的更多信息，请参阅[`cmake-packages(7)`](https://cmake.org/cmake/help/latest/manual/cmake-packages.7.html#manual:cmake-packages(7))手动的。



#### [包括目录和使用要求](https://cmake.org/cmake/help/latest/manual/cmake-buildsystem.7.html#id28)

当指定为使用要求以及与生成器表达式一起使用时，包含目录需要一些特殊的考虑。这 [`target_include_directories()`](https://cmake.org/cmake/help/latest/command/target_include_directories.html#command:target_include_directories)命令接受相对和绝对包含目录：

```
add_library(lib1 lib1.cpp)
target_include_directories(lib1 PRIVATE
  /absolute/path
  relative/path
)
```

相对路径是相对于命令出现的源目录解释的。不允许使用相对路径 [`INTERFACE_INCLUDE_DIRECTORIES`](https://cmake.org/cmake/help/latest/prop_tgt/INTERFACE_INCLUDE_DIRECTORIES.html#prop_tgt:INTERFACE_INCLUDE_DIRECTORIES)的[`IMPORTED`](https://cmake.org/cmake/help/latest/prop_tgt/IMPORTED.html#prop_tgt:IMPORTED)目标。

在使用非平凡生成器表达式的情况下，该 `INSTALL_PREFIX`表达式可以在表达式的参数中使用 `INSTALL_INTERFACE`。它是一个替换标记，在被消费项目导入时扩展为安装前缀。

包含目录的使用要求通常在构建树和安装树之间有所不同。`BUILD_INTERFACE`和`INSTALL_INTERFACE` 生成器表达式可用于根据使用位置描述单独的使用要求。表达式中允许使用相对路径， `INSTALL_INTERFACE`并且相对于安装前缀进行解释。例如：

```
add_library(ClimbingStats climbingstats.cpp)
target_include_directories(ClimbingStats INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/generated>
  $<INSTALL_INTERFACE:/absolute/path>
  $<INSTALL_INTERFACE:relative/path>
  $<INSTALL_INTERFACE:$<INSTALL_PREFIX>/$<CONFIG>/generated>
)
```

提供了两个与包含目录使用要求相关的便利 API。这[`CMAKE_INCLUDE_CURRENT_DIR_IN_INTERFACE`](https://cmake.org/cmake/help/latest/variable/CMAKE_INCLUDE_CURRENT_DIR_IN_INTERFACE.html#variable:CMAKE_INCLUDE_CURRENT_DIR_IN_INTERFACE)可以启用变量，其效果等同于：

```
set_property(TARGET tgt APPEND PROPERTY INTERFACE_INCLUDE_DIRECTORIES
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR};${CMAKE_CURRENT_BINARY_DIR}>
)
```

每个受影响的目标。安装目标的便利是一个组件`INCLUDES DESTINATION`[`install(TARGETS)`](https://cmake.org/cmake/help/latest/command/install.html#command:install) 命令：

```
install(TARGETS foo bar bat EXPORT tgts ${dest_args}
  INCLUDES DESTINATION include
)
install(EXPORT tgts ${other_args})
install(FILES ${headers} DESTINATION include)
```

这相当于附加`${CMAKE_INSTALL_PREFIX}/include`到 [`INTERFACE_INCLUDE_DIRECTORIES`](https://cmake.org/cmake/help/latest/prop_tgt/INTERFACE_INCLUDE_DIRECTORIES.html#prop_tgt:INTERFACE_INCLUDE_DIRECTORIES)每个安装的 [`IMPORTED`](https://cmake.org/cmake/help/latest/prop_tgt/IMPORTED.html#prop_tgt:IMPORTED)生成时的目标[`install(EXPORT)`](https://cmake.org/cmake/help/latest/command/install.html#command:install).

当。。。的时候[`INTERFACE_INCLUDE_DIRECTORIES`](https://cmake.org/cmake/help/latest/prop_tgt/INTERFACE_INCLUDE_DIRECTORIES.html#prop_tgt:INTERFACE_INCLUDE_DIRECTORIES)的 [导入目标](https://cmake.org/cmake/help/latest/manual/cmake-buildsystem.7.html#imported-targets)被消耗，属性中的条目被视为`SYSTEM`包含目录，就好像它们被列在[`INTERFACE_SYSTEM_INCLUDE_DIRECTORIES`](https://cmake.org/cmake/help/latest/prop_tgt/INTERFACE_SYSTEM_INCLUDE_DIRECTORIES.html#prop_tgt:INTERFACE_SYSTEM_INCLUDE_DIRECTORIES)的依赖。这可能会导致忽略那些目录中的头文件的编译器警告。[导入目标](https://cmake.org/cmake/help/latest/manual/cmake-buildsystem.7.html#imported-targets)的这种行为可以通过设置[`NO_SYSTEM_FROM_IMPORTED`](https://cmake.org/cmake/help/latest/prop_tgt/NO_SYSTEM_FROM_IMPORTED.html#prop_tgt:NO_SYSTEM_FROM_IMPORTED)导入目标 的*消费者*的目标属性，或通过设置[`IMPORTED_NO_SYSTEM`](https://cmake.org/cmake/help/latest/prop_tgt/IMPORTED_NO_SYSTEM.html#prop_tgt:IMPORTED_NO_SYSTEM)导入目标本身的目标属性。

如果二进制目标传递链接到 macOS[`FRAMEWORK`](https://cmake.org/cmake/help/latest/prop_tgt/FRAMEWORK.html#prop_tgt:FRAMEWORK)， `Headers`框架的目录也被视为使用需求。这与将框架目录作为包含目录传递的效果相同。

### [链接库和生成器表达式](https://cmake.org/cmake/help/latest/manual/cmake-buildsystem.7.html#id29)

像构建规范一样，[`link libraries`](https://cmake.org/cmake/help/latest/prop_tgt/LINK_LIBRARIES.html#prop_tgt:LINK_LIBRARIES)可以用生成器表达式条件指定。但是，由于使用需求的消耗是基于从链接依赖项中收集的，因此存在一个附加限制，即链接依赖项必须形成“有向无环图”。也就是说，如果链接到目标依赖于目标属性的值，则该目标属性可能不依赖于链接的依赖项：

```
add_library(lib1 lib1.cpp)
add_library(lib2 lib2.cpp)
target_link_libraries(lib1 PUBLIC
  $<$<TARGET_PROPERTY:POSITION_INDEPENDENT_CODE>:lib2>
)
add_library(lib3 lib3.cpp)
set_property(TARGET lib3 PROPERTY INTERFACE_POSITION_INDEPENDENT_CODE ON)

add_executable(exe1 exe1.cpp)
target_link_libraries(exe1 lib1 lib3)
```

作为价值[`POSITION_INDEPENDENT_CODE`](https://cmake.org/cmake/help/latest/prop_tgt/POSITION_INDEPENDENT_CODE.html#prop_tgt:POSITION_INDEPENDENT_CODE)目标的属性`exe1`依赖于链接库（`lib3`），链接的边缘`exe1`由相同的 [`POSITION_INDEPENDENT_CODE`](https://cmake.org/cmake/help/latest/prop_tgt/POSITION_INDEPENDENT_CODE.html#prop_tgt:POSITION_INDEPENDENT_CODE)属性，上面的依赖图包含一个循环。 [`cmake(1)`](https://cmake.org/cmake/help/latest/manual/cmake.1.html#manual:cmake(1))发出错误消息。



### [输出工件](https://cmake.org/cmake/help/latest/manual/cmake-buildsystem.7.html#id30)

由[`add_library()`](https://cmake.org/cmake/help/latest/command/add_library.html#command:add_library)和 [`add_executable()`](https://cmake.org/cmake/help/latest/command/add_executable.html#command:add_executable)命令创建规则以创建二进制输出。二进制文件的确切输出位置只能在生成时确定，因为它可以取决于链接依赖项的构建配置和链接语言等 `TARGET_FILE`， `TARGET_LINKER_FILE`并且可以使用相关表达式来访问生成的二进制文件的名称和位置. 但是，这些表达式不适用于`OBJECT`库，因为此类库没有生成与表达式相关的单个文件。

如以下部分所述，可以由目标构建三种类型的输出工件。它们的分类在 DLL 平台和非 DLL 平台之间有所不同。包括 Cygwin 在内的所有基于 Windows 的系统都是 DLL 平台。



#### [运行时输出工件](https://cmake.org/cmake/help/latest/manual/cmake-buildsystem.7.html#id31)

构建系统目标的*运行时*输出工件可能是：

- 由`.exe`_[`add_executable()`](https://cmake.org/cmake/help/latest/command/add_executable.html#command:add_executable)命令。
- 在 DLL 平台上：`.dll`由[`add_library()`](https://cmake.org/cmake/help/latest/command/add_library.html#command:add_library)带有`SHARED`选项的命令。

这[`RUNTIME_OUTPUT_DIRECTORY`](https://cmake.org/cmake/help/latest/prop_tgt/RUNTIME_OUTPUT_DIRECTORY.html#prop_tgt:RUNTIME_OUTPUT_DIRECTORY)和[`RUNTIME_OUTPUT_NAME`](https://cmake.org/cmake/help/latest/prop_tgt/RUNTIME_OUTPUT_NAME.html#prop_tgt:RUNTIME_OUTPUT_NAME) 目标属性可用于控制构建树中的运行时输出工件位置和名称。



#### [库输出工件](https://cmake.org/cmake/help/latest/manual/cmake-buildsystem.7.html#id32)

构建系统目标的*库*输出工件可能是：

- 由`.dll`_ `.so`_[`add_library()`](https://cmake.org/cmake/help/latest/command/add_library.html#command:add_library)带有`MODULE`选项的命令。
- 在非 DLL 平台上`.so`：`.dylib`由[`add_library()`](https://cmake.org/cmake/help/latest/command/add_library.html#command:add_library) 带有`SHARED`选项的命令。

这[`LIBRARY_OUTPUT_DIRECTORY`](https://cmake.org/cmake/help/latest/prop_tgt/LIBRARY_OUTPUT_DIRECTORY.html#prop_tgt:LIBRARY_OUTPUT_DIRECTORY)和[`LIBRARY_OUTPUT_NAME`](https://cmake.org/cmake/help/latest/prop_tgt/LIBRARY_OUTPUT_NAME.html#prop_tgt:LIBRARY_OUTPUT_NAME) 目标属性可用于控制构建树中的库输出工件位置和名称。



#### [存档输出工件](https://cmake.org/cmake/help/latest/manual/cmake-buildsystem.7.html#id33)

构建系统目标的*存档*输出工件可能是：

- 由`.lib`_ `.a`_[`add_library()`](https://cmake.org/cmake/help/latest/command/add_library.html#command:add_library)带有`STATIC`选项的命令。
- 在 DLL 平台上：`.lib`由[`add_library()`](https://cmake.org/cmake/help/latest/command/add_library.html#command:add_library)带有`SHARED`选项的命令。仅当库导出至少一个非托管符号时，才能保证此文件存在。
- 在 DLL 平台上：`.lib`由[`add_executable()`](https://cmake.org/cmake/help/latest/command/add_executable.html#command:add_executable)命令当它[`ENABLE_EXPORTS`](https://cmake.org/cmake/help/latest/prop_tgt/ENABLE_EXPORTS.html#prop_tgt:ENABLE_EXPORTS)目标属性已设置。
- 在 AIX 上：`.imp`由[`add_executable()`](https://cmake.org/cmake/help/latest/command/add_executable.html#command:add_executable)命令当它 [`ENABLE_EXPORTS`](https://cmake.org/cmake/help/latest/prop_tgt/ENABLE_EXPORTS.html#prop_tgt:ENABLE_EXPORTS)目标属性已设置。

这[`ARCHIVE_OUTPUT_DIRECTORY`](https://cmake.org/cmake/help/latest/prop_tgt/ARCHIVE_OUTPUT_DIRECTORY.html#prop_tgt:ARCHIVE_OUTPUT_DIRECTORY)和[`ARCHIVE_OUTPUT_NAME`](https://cmake.org/cmake/help/latest/prop_tgt/ARCHIVE_OUTPUT_NAME.html#prop_tgt:ARCHIVE_OUTPUT_NAME) 目标属性可用于控制构建树中的存档输出工件位置和名称。

### [目录范围的命令](https://cmake.org/cmake/help/latest/manual/cmake-buildsystem.7.html#id34)

这[`target_include_directories()`](https://cmake.org/cmake/help/latest/command/target_include_directories.html#command:target_include_directories), [`target_compile_definitions()`](https://cmake.org/cmake/help/latest/command/target_compile_definitions.html#command:target_compile_definitions)和 [`target_compile_options()`](https://cmake.org/cmake/help/latest/command/target_compile_options.html#command:target_compile_options)命令一次只对一个目标产生影响。命令[`add_compile_definitions()`](https://cmake.org/cmake/help/latest/command/add_compile_definitions.html#command:add_compile_definitions), [`add_compile_options()`](https://cmake.org/cmake/help/latest/command/add_compile_options.html#command:add_compile_options)和[`include_directories()`](https://cmake.org/cmake/help/latest/command/include_directories.html#command:include_directories)具有类似的功能，但为方便起见，在目录范围而不是目标范围内操作。



## [构建配置](https://cmake.org/cmake/help/latest/manual/cmake-buildsystem.7.html#id35)

配置确定特定类型构建的规范，例如`Release`或`Debug`。指定的方式取决于[`generator`](https://cmake.org/cmake/help/latest/manual/cmake-generators.7.html#manual:cmake-generators(7))正在使用。对于像 [Makefile Generators](https://cmake.org/cmake/help/latest/manual/cmake-generators.7.html#makefile-generators)和 [`Ninja`](https://cmake.org/cmake/help/latest/generator/Ninja.html#generator:Ninja)，配置是在配置时指定的 [`CMAKE_BUILD_TYPE`](https://cmake.org/cmake/help/latest/variable/CMAKE_BUILD_TYPE.html#variable:CMAKE_BUILD_TYPE)多变的。[对于像Visual Studio](https://cmake.org/cmake/help/latest/manual/cmake-generators.7.html#visual-studio-generators)这样的多配置生成器，[`Xcode`](https://cmake.org/cmake/help/latest/generator/Xcode.html#generator:Xcode)， 和 [`Ninja Multi-Config`](https://cmake.org/cmake/help/latest/generator/Ninja Multi-Config.html#generator:Ninja Multi-Config)，配置由用户在构建时选择，并且[`CMAKE_BUILD_TYPE`](https://cmake.org/cmake/help/latest/variable/CMAKE_BUILD_TYPE.html#variable:CMAKE_BUILD_TYPE)被忽略。在多配置情况下，*可用*配置集由配置时指定[`CMAKE_CONFIGURATION_TYPES`](https://cmake.org/cmake/help/latest/variable/CMAKE_CONFIGURATION_TYPES.html#variable:CMAKE_CONFIGURATION_TYPES)变量，但在构建阶段之前无法知道实际使用的配置。这种差异经常被误解，导致有问题的代码如下：

```
# WARNING: This is wrong for multi-config generators because they don't use
#          and typically don't even set CMAKE_BUILD_TYPE
string(TOLOWER ${CMAKE_BUILD_TYPE} build_type)
if (build_type STREQUAL debug)
  target_compile_definitions(exe1 PRIVATE DEBUG_BUILD)
endif()
```

[`Generator expressions`](https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html#manual:cmake-generator-expressions(7))无论使用何种生成器，都应该使用它来正确处理特定于配置的逻辑。例如：

```
# Works correctly for both single and multi-config generators
target_compile_definitions(exe1 PRIVATE
  $<$<CONFIG:Debug>:DEBUG_BUILD>
)
```

在......的存在下[`IMPORTED`](https://cmake.org/cmake/help/latest/prop_tgt/IMPORTED.html#prop_tgt:IMPORTED)目标，内容 [`MAP_IMPORTED_CONFIG_DEBUG`](https://cmake.org/cmake/help/latest/prop_tgt/MAP_IMPORTED_CONFIG_CONFIG.html#prop_tgt:MAP_IMPORTED_CONFIG_)也是由上面的`$<CONFIG:Debug>`表达式解释的。

### [区分大小写](https://cmake.org/cmake/help/latest/manual/cmake-buildsystem.7.html#id36)

[`CMAKE_BUILD_TYPE`](https://cmake.org/cmake/help/latest/variable/CMAKE_BUILD_TYPE.html#variable:CMAKE_BUILD_TYPE)和[`CMAKE_CONFIGURATION_TYPES`](https://cmake.org/cmake/help/latest/variable/CMAKE_CONFIGURATION_TYPES.html#variable:CMAKE_CONFIGURATION_TYPES)就像其他变量一样，任何与其值进行的字符串比较都将区分大小写。生成器`$<CONFIG>`表达式还保留用户设置的配置大小写或 CMake 默认值。例如：

```
# NOTE: Don't use these patterns, they are for illustration purposes only.

set(CMAKE_BUILD_TYPE Debug)
if(CMAKE_BUILD_TYPE STREQUAL DEBUG)
  # ... will never get here, "Debug" != "DEBUG"
endif()
add_custom_target(print_config ALL
  # Prints "Config is Debug" in this single-config case
  COMMAND ${CMAKE_COMMAND} -E echo "Config is $<CONFIG>"
  VERBATIM
)

set(CMAKE_CONFIGURATION_TYPES Debug Release)
if(DEBUG IN_LIST CMAKE_CONFIGURATION_TYPES)
  # ... will never get here, "Debug" != "DEBUG"
endif()
```

相反，CMake 在根据配置修改行为的地方内部使用配置类型时不区分大小写。例如，`$<CONFIG:Debug>`生成器表达式将评估为 1 配置不仅`Debug`，而且`DEBUG`，`debug`甚至`DeBuG`。因此，您可以在 [`CMAKE_BUILD_TYPE`](https://cmake.org/cmake/help/latest/variable/CMAKE_BUILD_TYPE.html#variable:CMAKE_BUILD_TYPE)和[`CMAKE_CONFIGURATION_TYPES`](https://cmake.org/cmake/help/latest/variable/CMAKE_CONFIGURATION_TYPES.html#variable:CMAKE_CONFIGURATION_TYPES)大写和小写的任何混合，尽管有很强的约定（见下一节）。如果您必须在字符串比较中测试值，请始终先将值转换为大写或小写，并相应地调整测试。

### [默认和自定义配置](https://cmake.org/cmake/help/latest/manual/cmake-buildsystem.7.html#id37)

默认情况下，CMake 定义了许多标准配置：

- `Debug`
- `Release`
- `RelWithDebInfo`
- `MinSizeRel`

在多配置生成器中，[`CMAKE_CONFIGURATION_TYPES`](https://cmake.org/cmake/help/latest/variable/CMAKE_CONFIGURATION_TYPES.html#variable:CMAKE_CONFIGURATION_TYPES)默认情况下，变量将填充（可能是上述列表的子集），除非被项目或用户覆盖。实际使用的配置由用户在构建时选择。

对于单配置生成器，配置是用 [`CMAKE_BUILD_TYPE`](https://cmake.org/cmake/help/latest/variable/CMAKE_BUILD_TYPE.html#variable:CMAKE_BUILD_TYPE)在配置时变量并且不能在构建时更改。默认值通常不是上述标准配置，而是一个空字符串。一个常见的误解是，这与 相同`Debug`，但事实并非如此。用户应始终明确指定构建类型以避免此常见问题。

上述标准配置类型在大多数平台上提供了合理的行为，但可以扩展它们以提供其他类型。每个配置都为使用的语言定义了一组编译器和链接器标志变量。这些变量遵循约定[`CMAKE__FLAGS_`](https://cmake.org/cmake/help/latest/variable/CMAKE_LANG_FLAGS_CONFIG.html#variable:CMAKE__FLAGS_)，其中`<CONFIG>`始终是大写的配置名称。定义自定义配置类型时，请确保正确设置这些变量，通常作为缓存变量。

## [伪目标](https://cmake.org/cmake/help/latest/manual/cmake-buildsystem.7.html#id38)

一些目标类型不代表构建系统的输出，而只是输入，例如外部依赖项、别名或其他非构建工件。生成的构建系统中不表示伪目标。



### [导入的目标](https://cmake.org/cmake/help/latest/manual/cmake-buildsystem.7.html#id39)

一个[`IMPORTED`](https://cmake.org/cmake/help/latest/prop_tgt/IMPORTED.html#prop_tgt:IMPORTED)target 表示预先存在的依赖项。通常这样的目标是由上游包定义的，应该被视为不可变的。声明一个之后[`IMPORTED`](https://cmake.org/cmake/help/latest/prop_tgt/IMPORTED.html#prop_tgt:IMPORTED)目标可以通过使用常用命令来调整其目标属性，例如 [`target_compile_definitions()`](https://cmake.org/cmake/help/latest/command/target_compile_definitions.html#command:target_compile_definitions), [`target_include_directories()`](https://cmake.org/cmake/help/latest/command/target_include_directories.html#command:target_include_directories), [`target_compile_options()`](https://cmake.org/cmake/help/latest/command/target_compile_options.html#command:target_compile_options)或者[`target_link_libraries()`](https://cmake.org/cmake/help/latest/command/target_link_libraries.html#command:target_link_libraries)就像任何其他常规目标一样。

[`IMPORTED`](https://cmake.org/cmake/help/latest/prop_tgt/IMPORTED.html#prop_tgt:IMPORTED)目标可能具有与二进制目标相同的使用要求属性，例如 [`INTERFACE_INCLUDE_DIRECTORIES`](https://cmake.org/cmake/help/latest/prop_tgt/INTERFACE_INCLUDE_DIRECTORIES.html#prop_tgt:INTERFACE_INCLUDE_DIRECTORIES), [`INTERFACE_COMPILE_DEFINITIONS`](https://cmake.org/cmake/help/latest/prop_tgt/INTERFACE_COMPILE_DEFINITIONS.html#prop_tgt:INTERFACE_COMPILE_DEFINITIONS), [`INTERFACE_COMPILE_OPTIONS`](https://cmake.org/cmake/help/latest/prop_tgt/INTERFACE_COMPILE_OPTIONS.html#prop_tgt:INTERFACE_COMPILE_OPTIONS), [`INTERFACE_LINK_LIBRARIES`](https://cmake.org/cmake/help/latest/prop_tgt/INTERFACE_LINK_LIBRARIES.html#prop_tgt:INTERFACE_LINK_LIBRARIES)， 和 [`INTERFACE_POSITION_INDEPENDENT_CODE`](https://cmake.org/cmake/help/latest/prop_tgt/INTERFACE_POSITION_INDEPENDENT_CODE.html#prop_tgt:INTERFACE_POSITION_INDEPENDENT_CODE).

这[`LOCATION`](https://cmake.org/cmake/help/latest/prop_tgt/LOCATION.html#prop_tgt:LOCATION)也可以从 IMPORTED 目标中读取，尽管很少有这样做的理由。命令如[`add_custom_command()`](https://cmake.org/cmake/help/latest/command/add_custom_command.html#command:add_custom_command)可以透明地使用[`IMPORTED`](https://cmake.org/cmake/help/latest/prop_tgt/IMPORTED.html#prop_tgt:IMPORTED) [`EXECUTABLE`](https://cmake.org/cmake/help/latest/prop_tgt/TYPE.html#prop_tgt:TYPE)目标作为`COMMAND`可执行文件。

定义的范围[`IMPORTED`](https://cmake.org/cmake/help/latest/prop_tgt/IMPORTED.html#prop_tgt:IMPORTED)target 是定义它的目录。它可以从子目录访问和使用，但不能从父目录或兄弟目录访问和使用。范围类似于 cmake 变量的范围。

也可以定义一个`GLOBAL` [`IMPORTED`](https://cmake.org/cmake/help/latest/prop_tgt/IMPORTED.html#prop_tgt:IMPORTED)可在构建系统中全局访问的目标。

见[`cmake-packages(7)`](https://cmake.org/cmake/help/latest/manual/cmake-packages.7.html#manual:cmake-packages(7))手册了解更多关于创建包的信息[`IMPORTED`](https://cmake.org/cmake/help/latest/prop_tgt/IMPORTED.html#prop_tgt:IMPORTED)目标。



### [别名目标](https://cmake.org/cmake/help/latest/manual/cmake-buildsystem.7.html#id40)

目标是一个`ALIAS`名称，可以在只读上下文中与二进制目标名称互换使用。例如，目标的主要用例`ALIAS` 是库附带的单元测试可执行文件，它可能是同一构建系统的一部分，也可能是根据用户配置单独构建的。

```
add_library(lib1 lib1.cpp)
install(TARGETS lib1 EXPORT lib1Export ${dest_args})
install(EXPORT lib1Export NAMESPACE Upstream:: ${other_args})

add_library(Upstream::lib1 ALIAS lib1)
```

在另一个目录中，我们可以无条件链接到`Upstream::lib1` 目标，这可能是一个[`IMPORTED`](https://cmake.org/cmake/help/latest/prop_tgt/IMPORTED.html#prop_tgt:IMPORTED)来自包的 `ALIAS`目标，或者如果构建为同一构建系统的一部分，则为目标。

```
if (NOT TARGET Upstream::lib1)
  find_package(lib1 REQUIRED)
endif()
add_executable(exe1 exe1.cpp)
target_link_libraries(exe1 Upstream::lib1)
```

`ALIAS`目标不是可变的、可安装的或可导出的。它们完全是构建系统描述的本地化。`ALIAS`一个名字可以通过阅读来测试它是否是一个名字[`ALIASED_TARGET`](https://cmake.org/cmake/help/latest/prop_tgt/ALIASED_TARGET.html#prop_tgt:ALIASED_TARGET) 它的财产：

```
get_target_property(_aliased Upstream::lib1 ALIASED_TARGET)
if(_aliased)
  message(STATUS "The name Upstream::lib1 is an ALIAS for ${_aliased}.")
endif()
```



### [接口库](https://cmake.org/cmake/help/latest/manual/cmake-buildsystem.7.html#id41)

`INTERFACE`库目标不编译源代码，也不在磁盘上生成库工件，因此它没有[`LOCATION`](https://cmake.org/cmake/help/latest/prop_tgt/LOCATION.html#prop_tgt:LOCATION).

它可以指定使用要求，例如 [`INTERFACE_INCLUDE_DIRECTORIES`](https://cmake.org/cmake/help/latest/prop_tgt/INTERFACE_INCLUDE_DIRECTORIES.html#prop_tgt:INTERFACE_INCLUDE_DIRECTORIES), [`INTERFACE_COMPILE_DEFINITIONS`](https://cmake.org/cmake/help/latest/prop_tgt/INTERFACE_COMPILE_DEFINITIONS.html#prop_tgt:INTERFACE_COMPILE_DEFINITIONS), [`INTERFACE_COMPILE_OPTIONS`](https://cmake.org/cmake/help/latest/prop_tgt/INTERFACE_COMPILE_OPTIONS.html#prop_tgt:INTERFACE_COMPILE_OPTIONS), [`INTERFACE_LINK_LIBRARIES`](https://cmake.org/cmake/help/latest/prop_tgt/INTERFACE_LINK_LIBRARIES.html#prop_tgt:INTERFACE_LINK_LIBRARIES), [`INTERFACE_SOURCES`](https://cmake.org/cmake/help/latest/prop_tgt/INTERFACE_SOURCES.html#prop_tgt:INTERFACE_SOURCES)， 和[`INTERFACE_POSITION_INDEPENDENT_CODE`](https://cmake.org/cmake/help/latest/prop_tgt/INTERFACE_POSITION_INDEPENDENT_CODE.html#prop_tgt:INTERFACE_POSITION_INDEPENDENT_CODE). 只有`INTERFACE`模式[`target_include_directories()`](https://cmake.org/cmake/help/latest/command/target_include_directories.html#command:target_include_directories), [`target_compile_definitions()`](https://cmake.org/cmake/help/latest/command/target_compile_definitions.html#command:target_compile_definitions), [`target_compile_options()`](https://cmake.org/cmake/help/latest/command/target_compile_options.html#command:target_compile_options), [`target_sources()`](https://cmake.org/cmake/help/latest/command/target_sources.html#command:target_sources)， 和[`target_link_libraries()`](https://cmake.org/cmake/help/latest/command/target_link_libraries.html#command:target_link_libraries)命令可以与`INTERFACE`库一起使用。

从 CMake 3.19 开始，`INTERFACE`库目标可以选择包含源文件。包含源文件的接口库将作为构建目标包含在生成的构建系统中。它不编译源代码，但可能包含自定义命令来生成其他源代码。此外，IDE 会将源文件显示为目标的一部分，以进行交互式阅读和编辑。

库的主要用例`INTERFACE`是仅标头库。从 CMake 3.23 开始，头文件可以通过使用[`target_sources()`](https://cmake.org/cmake/help/latest/command/target_sources.html#command:target_sources)命令：

```
add_library(Eigen INTERFACE)

target_sources(Eigen INTERFACE
  FILE_SET HEADERS
    BASE_DIRS src
    FILES src/eigen.h src/vector.h src/matrix.h
)

add_executable(exe1 exe1.cpp)
target_link_libraries(exe1 Eigen)
```

当我们在`FILE_SET`此处指定时，`BASE_DIRS`我们定义的目标自动成为使用要求中的包含目录`Eigen`。来自目标的使用需求在编译时被消耗和使用，但对链接没有影响。

另一个用例是针对使用要求采用完全以目标为中心的设计：

```
add_library(pic_on INTERFACE)
set_property(TARGET pic_on PROPERTY INTERFACE_POSITION_INDEPENDENT_CODE ON)
add_library(pic_off INTERFACE)
set_property(TARGET pic_off PROPERTY INTERFACE_POSITION_INDEPENDENT_CODE OFF)

add_library(enable_rtti INTERFACE)
target_compile_options(enable_rtti INTERFACE
  $<$<OR:$<COMPILER_ID:GNU>,$<COMPILER_ID:Clang>>:-rtti>
)

add_executable(exe1 exe1.cpp)
target_link_libraries(exe1 pic_on enable_rtti)
```

这样，构建规范`exe1`完全表示为链接目标，并且编译器特定标志的复杂性封装在 `INTERFACE`库目标中。

`INTERFACE`可以安装和导出库。我们可以与目标一起安装默认标头集：

```
add_library(Eigen INTERFACE)

target_sources(Eigen INTERFACE
  FILE_SET HEADERS
    BASE_DIRS src
    FILES src/eigen.h src/vector.h src/matrix.h
)

install(TARGETS Eigen EXPORT eigenExport
  FILE_SET HEADERS DESTINATION include/Eigen)
install(EXPORT eigenExport NAMESPACE Upstream::
  DESTINATION lib/cmake/Eigen
)
```

在这里，标头集中定义的标头安装到`include/Eigen`. 安装目标自动成为一个包含目录，这是消费者的使用要求。