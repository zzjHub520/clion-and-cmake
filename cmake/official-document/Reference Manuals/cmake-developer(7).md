# [cmake-开发者(7) ](https://cmake.org/cmake/help/latest/manual/cmake-developer.7.html#id3)

内容

- [cmake-开发者(7)](https://cmake.org/cmake/help/latest/manual/cmake-developer.7.html#cmake-developer-7)
  - [介绍](https://cmake.org/cmake/help/latest/manual/cmake-developer.7.html#introduction)
  - [访问 Windows 注册表](https://cmake.org/cmake/help/latest/manual/cmake-developer.7.html#accessing-windows-registry)
    - [查询 Windows 注册表](https://cmake.org/cmake/help/latest/manual/cmake-developer.7.html#query-windows-registry)
    - [使用 Windows 注册表查找](https://cmake.org/cmake/help/latest/manual/cmake-developer.7.html#find-using-windows-registry)
  - [查找模块](https://cmake.org/cmake/help/latest/manual/cmake-developer.7.html#find-modules)
    - [标准变量名](https://cmake.org/cmake/help/latest/manual/cmake-developer.7.html#standard-variable-names)
    - [样本查找模块](https://cmake.org/cmake/help/latest/manual/cmake-developer.7.html#a-sample-find-module)

## [Introduction](https://cmake.org/cmake/help/latest/manual/cmake-developer.7.html#id4)

本手册供开发人员参考 [`cmake-language(7)`](https://cmake.org/cmake/help/latest/manual/cmake-language.7.html#manual:cmake-language(7))代码，无论是编写自己的模块，编写自己的构建系统，还是使用 CMake 本身。

请参阅https://cmake.org/get-involved/以参与上游 CMake 的开发。它包括指向贡献说明的链接，这些链接又链接到 CMake 本身的开发人员指南。

## [访问 Windows 注册表](https://cmake.org/cmake/help/latest/manual/cmake-developer.7.html#id5)

CMake 提供了一些工具来访问`Windows`平台上的注册表。

### [查询 Windows 注册表](https://cmake.org/cmake/help/latest/manual/cmake-developer.7.html#id6)

*版本 3.24 中的新功能。*

这[`cmake_host_system_information()`](https://cmake.org/cmake/help/latest/command/cmake_host_system_information.html#command:cmake_host_system_information)命令提供了在本地计算机上查询注册表的可能性。有关详细信息，请参阅 [cmake_host_system(QUERY_WINDOWS_REGISTRY)](https://cmake.org/cmake/help/latest/command/cmake_host_system_information.html#query-windows-registry)。



### [使用 Windows 注册表查找](https://cmake.org/cmake/help/latest/manual/cmake-developer.7.html#id7)

*在 3.24 版中更改。*

选项`HINTS`和`PATHS`_[`find_file()`](https://cmake.org/cmake/help/latest/command/find_file.html#command:find_file), [`find_library()`](https://cmake.org/cmake/help/latest/command/find_library.html#command:find_library), [`find_path()`](https://cmake.org/cmake/help/latest/command/find_path.html#command:find_path),[`find_program()`](https://cmake.org/cmake/help/latest/command/find_program.html#command:find_program)， 和 [`find_package()`](https://cmake.org/cmake/help/latest/command/find_package.html#command:find_package)命令提供了在`Windows` 平台上查询注册表的可能性。

注册表查询的正式语法（使用 带有常规扩展名的[BNF表示法指定）如下：](https://en.wikipedia.org/wiki/Backus–Naur_form)

```
注册表查询::= '[' sep_definition？root_key
                         （（）？（_）？）？']'
key_separator sub_keyvalue_separator value_namesep_definition ::= '{' value_separator'}'
root_key        ::= 'HKLM' | 'HKEY_LOCAL_MACHINE' | '香港中文大学' | 'HKEY_CURRENT_USER' |
                     '香港华润' | 'HKEY_CLASSES_ROOT' | 'HKCC' | 'HKEY_CURRENT_CONFIG' |
                     '港大' | 'HKEY_USERS'
子键        ::=   element( )*
key_separator elementkey_separator   ::= '/' | '\\'
值分隔符::=   element| ';'
值名称     ::=   element| '（默认）'
元素        ::=   character\+
字符      ::= <除key_separator和之外的任何字符value_separator>
```

[`sep_definition`](https://cmake.org/cmake/help/latest/manual/cmake-developer.7.html#grammar-token-sep_definition)可选项目提供了指定用于分隔项目的字符串[`sub_key`](https://cmake.org/cmake/help/latest/manual/cmake-developer.7.html#grammar-token-sub_key)的可能性[`value_name`](https://cmake.org/cmake/help/latest/manual/cmake-developer.7.html#grammar-token-value_name) 。如果未指定，`;`则使用该字符。可以将多个 [`registry_query`](https://cmake.org/cmake/help/latest/manual/cmake-developer.7.html#grammar-token-registry_query)项目指定为路径的一部分。

```
# example using default separator
find_file(... PATHS "/root/[HKLM/Stuff;InstallDir]/lib[HKLM\\\\Stuff;Architecture]")

# example using different specified separators
find_library(... HINTS "/root/[{|}HKCU/Stuff|InstallDir]/lib[{@@}HKCU\\\\Stuff@@Architecture]")
```

如果[`value_name`](https://cmake.org/cmake/help/latest/manual/cmake-developer.7.html#grammar-token-value_name)item 没有指定或者有特殊的 name `(default)`，则返回默认值的内容，如果有的话。支持的类型[`value_name`](https://cmake.org/cmake/help/latest/manual/cmake-developer.7.html#grammar-token-value_name)有：

- `REG_SZ`.
- `REG_EXPAND_SZ`. 返回的数据被展开。
- `REG_DWORD`.
- `REG_QWORD`.

当注册表查询失败时，通常是因为键不存在或数据类型不受支持，字符串`/REGISTRY-NOTFOUND`将替换为`[]`查询表达式。



## [查找模块](https://cmake.org/cmake/help/latest/manual/cmake-developer.7.html#id8)

“查找模块”是`Find<PackageName>.cmake`要由 [`find_package()`](https://cmake.org/cmake/help/latest/command/find_package.html#command:find_package)调用时的命令`<PackageName>`。

查找模块的主要任务是确定包是否可用，设置`<PackageName>_FOUND`变量以反映这一点，并提供使用包所需的任何变量、宏和导入的目标。在上游库不提供[配置文件包](https://cmake.org/cmake/help/latest/manual/cmake-packages.7.html#config-file-packages)的情况下，查找模块很有用。

传统方法是对所有内容使用变量，包括库和可执行文件：请参阅下面的[标准变量名称](https://cmake.org/cmake/help/latest/manual/cmake-developer.7.html#standard-variable-names)部分。这是 CMake 提供的大多数现有查找模块所做的。

[更现代的方法是通过提供导入的 target](https://cmake.org/cmake/help/latest/manual/cmake-buildsystem.7.html#imported-targets)尽可能地表现得像 [配置文件包](https://cmake.org/cmake/help/latest/manual/cmake-packages.7.html#config-file-packages)文件。这具有向消费者传播[传递性使用需求的优势。](https://cmake.org/cmake/help/latest/manual/cmake-buildsystem.7.html#target-usage-requirements)

在任何一种情况下（或者即使同时提供变量和导入的目标），查找模块都应该提供与具有相同名称的旧版本的向后兼容性。

FindFoo.cmake 模块通常由以下命令加载：

```
find_package(Foo [major[.minor[.patch[.tweak]]]]
             [EXACT] [QUIET] [REQUIRED]
             [[COMPONENTS] [components...]]
             [OPTIONAL_COMPONENTS components...]
             [NO_POLICY_SCOPE])
```

见[`find_package()`](https://cmake.org/cmake/help/latest/command/find_package.html#command:find_package)有关为 find 模块设置了哪些变量的详细信息的文档。其中大部分是通过使用处理的[`FindPackageHandleStandardArgs`](https://cmake.org/cmake/help/latest/module/FindPackageHandleStandardArgs.html#module:FindPackageHandleStandardArgs).

简而言之，模块应该只定位与请求版本兼容的包版本，如 `Foo_FIND_VERSION`变量族所述。如果`Foo_FIND_QUIETLY`设置为 true，它应该避免打印消息，包括任何抱怨找不到包的消息。如果`Foo_FIND_REQUIRED` 设置为 true，`FATAL_ERROR`如果找不到包，模块应该发出一个。如果两者都没有设置为 true，则如果找不到包，它应该打印一条非致命消息。

找到多个半独立部分（如库包）的包应该搜索列出的组件， `Foo_FIND_COMPONENTS`如果它被设置，并且只有`Foo_FOUND`在每个搜索到的组件`<c>`没有被 设置为 true 时才设置`Foo_FIND_REQUIRED_<c>`为 true。的`HANDLE_COMPONENTS` 参数`find_package_handle_standard_args()`可用于实现这一点。

如果`Foo_FIND_COMPONENTS`未设置，则搜索和需要哪些模块取决于查找模块，但应记录在案。

对于内部实现，普遍接受的约定是以下划线开头的变量仅供临时使用。



### [标准变量名称](https://cmake.org/cmake/help/latest/manual/cmake-developer.7.html#id9)

对于`FindXxx.cmake`采用设置变量方法的模块（而不是创建导入目标或除了创建导入目标之外），应使用以下变量名称来保持查找模块之间的一致性。请注意，所有变量都以 开头 `Xxx_`，（除非另有说明）必须与`FindXxx.cmake`文件名完全匹配，包括大写/小写。变量名上的这个前缀确保它们不会与其他 Find 模块的变量冲突。Find 模块定义的任何宏、函数和导入目标也应遵循相同的模式。

- `Xxx_INCLUDE_DIRS`

  最后一组包含目录列在一个变量中，供客户端代码使用。这不应该是一个缓存条目（注意，这也意味着这个变量不应该被用作一个结果变量 [`find_path()`](https://cmake.org/cmake/help/latest/command/find_path.html#command:find_path)命令 - 见`Xxx_INCLUDE_DIR`下文）。

- `Xxx_LIBRARIES`

  与模块一起使用的库。这些可能是 CMake 目标、库二进制文件的完整绝对路径或链接器必须在其搜索路径中找到的库的名称。这不应该是一个缓存条目（注意，这也意味着这个变量不应该被用作一个结果变量[`find_library()`](https://cmake.org/cmake/help/latest/command/find_library.html#command:find_library)命令 - 见 `Xxx_LIBRARY`下文）。

- `Xxx_DEFINITIONS`

  编译使用模块的代码时要使用的编译定义。这真的不应该包括诸如`-DHAS_JPEG`客户端源代码文件用来决定是否`#include <jpeg.h>`

- `Xxx_EXECUTABLE`

  可执行文件的完整绝对路径。在这种情况下，`Xxx`可能不是模块的名称，它可能是工具的名称（通常转换为全大写），假设该工具具有如此知名的名称，不太可能有另一个具有相同名称的工具存在。将其用作 a 的结果变量是合适的 [`find_program()`](https://cmake.org/cmake/help/latest/command/find_program.html#command:find_program)命令。

- `Xxx_YYY_EXECUTABLE`

  `Xxx_EXECUTABLE`与此处类似，`Xxx`始终是模块名称和`YYY`工具名称（同样，通常完全大写）。如果工具名称不是很广为人知或有可能与其他工具发生冲突，则更喜欢这种形式。为了更好的一致性，如果模块提供了多个可执行文件，也更喜欢这种形式。

- `Xxx_LIBRARY_DIRS`

  （可选）在一个变量中列出的最后一组库目录供客户端代码使用。这不应该是缓存条目。

- `Xxx_ROOT_DIR`

  在哪里可以找到模块的基本目录。

- `Xxx_VERSION_VV`

  这种形式的变量指定`Xxx`所提供的模块是否是模块的版本`VV`。对于给定的模块，不应有多个这种形式的变量设置为 true。例如，一个模块`Barry`可能已经发展了很多年，并经历了许多不同的主要版本。模块的版本 3`Barry`可能会将变量设置`Barry_VERSION_3`为 true，而旧版本的模块可能会设置`Barry_VERSION_2`为 true。`Barry_VERSION_3`两者`Barry_VERSION_2` 都设置为 true将是错误的。

- `Xxx_WRAP_YY`

  当这种形式的变量设置为false时，表示不应该使用相关的换行命令。包装命令取决于模块，它可能由模块名称暗示，也可能由`YY`变量的一部分指定。

- `Xxx_Yy_FOUND`

  对于这种形式的变量，`Yy`是模块的组件名称。它应该与可能传递给[`find_package()`](https://cmake.org/cmake/help/latest/command/find_package.html#command:find_package)模块的命令。如果这种形式的变量设置为false，则表示模块的`Yy` 组件`Xxx`未找到或不可用。这种形式的变量通常用于可选组件，以便调用者可以检查可选组件是否可用。

- `Xxx_FOUND`

  当。。。的时候[`find_package()`](https://cmake.org/cmake/help/latest/command/find_package.html#command:find_package)命令返回给调用者，如果模块被认为已成功找到，此变量将设置为 true。

- `Xxx_NOT_FOUND_MESSAGE`

  如果设置 `Xxx_FOUND`为 FALSE，则应由配置文件设置。包含的消息将由 [`find_package()`](https://cmake.org/cmake/help/latest/command/find_package.html#command:find_package)命令并通过 [`find_package_handle_standard_args()`](https://cmake.org/cmake/help/latest/module/FindPackageHandleStandardArgs.html#command:find_package_handle_standard_args)通知用户该问题。使用它而不是调用[`message()`](https://cmake.org/cmake/help/latest/command/message.html#command:message)直接报告找不到模块或包的原因。

- `Xxx_RUNTIME_LIBRARY_DIRS`

  （可选）运行链接到共享库的可执行文件时使用的运行时库搜索路径。用户代码应使用该列表`PATH`在 Windows 或`LD_LIBRARY_PATH`UNIX 上创建。这不应该是缓存条目。

- `Xxx_VERSION`

  找到的包的完整版本字符串（如果有）。请注意，许多现有模块提供`Xxx_VERSION_STRING`了替代。

- `Xxx_VERSION_MAJOR`

  找到的软件包的主要版本（如果有）。

- `Xxx_VERSION_MINOR`

  找到的软件包的次要版本（如果有）。

- `Xxx_VERSION_PATCH`

  找到的软件包的补丁版本（如果有）。

以下名称通常不应在`CMakeLists.txt`文件中使用。它们旨在供 Find 模块用于指定和缓存特定文件或目录的位置。用户通常可以设置和编辑这些变量来控制 Find 模块的行为（例如手动输入库的路径）：

- `Xxx_LIBRARY`

  库的路径。仅当模块提供单个库时才使用此表单。将其用作结果变量是合适的[`find_library()`](https://cmake.org/cmake/help/latest/command/find_library.html#command:find_library)命令。

- `Xxx_Yy_LIBRARY`

  `Yy`模块提供的库路径`Xxx`。当模块提供多个库或其他模块也可能提供同名库时使用此形式。使用这种形式作为结果变量也是合适的[`find_library()`](https://cmake.org/cmake/help/latest/command/find_library.html#command:find_library)命令。

- `Xxx_INCLUDE_DIR`

  当模块仅提供单个库时，此变量可用于指定在何处找到使用该库的标头（或更准确地说，该库的使用者应添加到其标头搜索路径的路径）。将其用作结果变量是合适的 [`find_path()`](https://cmake.org/cmake/help/latest/command/find_path.html#command:find_path)命令。

- `Xxx_Yy_INCLUDE_DIR`

  如果模块提供了多个库，或者其他模块也可能提供同名的库，则建议使用此表单指定在哪里可以找到使用`Yy`模块提供的库的头文件。同样，将其用作结果变量是合适的[`find_path()`](https://cmake.org/cmake/help/latest/command/find_path.html#command:find_path)命令。

为防止用户对配置设置感到不知所措，请尝试将尽可能多的选项保留在缓存之外，至少保留一个选项可用于禁用模块的使用，或查找未找到的库（例如`Xxx_ROOT_DIR`）。出于同样的原因，将大多数缓存选项标记为高级。对于同时提供调试和发布二进制文件的包，通常会创建带有 `_LIBRARY_<CONFIG>`后缀的缓存变量，例如`Foo_LIBRARY_RELEASE`and `Foo_LIBRARY_DEBUG`。这[`SelectLibraryConfigurations`](https://cmake.org/cmake/help/latest/module/SelectLibraryConfigurations.html#module:SelectLibraryConfigurations)模块对这种情况很有帮助。

虽然这些是标准变量名称，但您应该为实际使用的任何旧名称提供向后兼容性。确保您将它们评论为已弃用，以便没有人开始使用它们。

### [示例查找模块](https://cmake.org/cmake/help/latest/manual/cmake-developer.7.html#id10)

我们将描述如何为库创建一个简单的查找模块`Foo`。

模块的顶部应以许可证通知开头，然后是空行，然后是[括号注释](https://cmake.org/cmake/help/latest/manual/cmake-language.7.html#bracket-comment)。`.rst:`注释应以表明其其余内容为 reStructuredText 格式的文档开头。例如：

```
# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

#[=======================================================================[.rst:
FindFoo
-------

Finds the Foo library.

Imported Targets
^^^^^^^^^^^^^^^^

This module provides the following imported targets, if found:

``Foo::Foo``
  The Foo library

Result Variables
^^^^^^^^^^^^^^^^

This will define the following variables:

``Foo_FOUND``
  True if the system has the Foo library.
``Foo_VERSION``
  The version of the Foo library which was found.
``Foo_INCLUDE_DIRS``
  Include directories needed to use Foo.
``Foo_LIBRARIES``
  Libraries needed to link to Foo.

Cache Variables
^^^^^^^^^^^^^^^

The following cache variables may also be set:

``Foo_INCLUDE_DIR``
  The directory containing ``foo.h``.
``Foo_LIBRARY``
  The path to the Foo library.

#]=======================================================================]
```

模块文档包括：

- 指定模块名称的带下划线的标题。
- 对模块找到的内容的简单描述。某些软件包可能需要更多描述。如果有警告或模块用户应注意的其他详细信息，请在此处指定。
- 列出模块提供的导入目标的部分（如果有）。
- 列出模块提供的结果变量的部分。
- （可选）列出模块使用的缓存变量的部分（如果有）。

如果包提供了任何宏或函数，它们应该在附加部分中列出，但可以在`.rst:` 定义这些宏或函数的正上方的附加注释块中记录。

查找模块的实现可以在文档块下方开始。现在必须找到实际的库等。这里的代码显然会因模块而异（处理，毕竟，是查找模块的重点），但库往往有一个共同的模式。

首先，我们尝试使用`pkg-config`查找库。请注意，我们不能依赖它，因为它可能不可用，但它提供了一个很好的起点。

```
find_package(PkgConfig)
pkg_check_modules(PC_Foo QUIET Foo)
```

`PC_Foo_`这应该定义一些包含文件信息的变量`Foo.pc`。

现在我们需要找到库和包含文件；我们使用来自的信息`pkg-config`向 CMake 提供关于在哪里查找的提示。

```
find_path(Foo_INCLUDE_DIR
  NAMES foo.h
  PATHS ${PC_Foo_INCLUDE_DIRS}
  PATH_SUFFIXES Foo
)
find_library(Foo_LIBRARY
  NAMES foo
  PATHS ${PC_Foo_LIBRARY_DIRS}
)
```

或者，如果库可用于多种配置，您可以使用[`SelectLibraryConfigurations`](https://cmake.org/cmake/help/latest/module/SelectLibraryConfigurations.html#module:SelectLibraryConfigurations)改为自动设置 `Foo_LIBRARY`变量：

```
find_library(Foo_LIBRARY_RELEASE
  NAMES foo
  PATHS ${PC_Foo_LIBRARY_DIRS}/Release
)
find_library(Foo_LIBRARY_DEBUG
  NAMES foo
  PATHS ${PC_Foo_LIBRARY_DIRS}/Debug
)

include(SelectLibraryConfigurations)
select_library_configurations(Foo)
```

如果您有一种获取版本的好方法（例如，从头文件中），则可以使用该信息进行设置`Foo_VERSION`（尽管请注意 find 模块传统上使用`Foo_VERSION_STRING`，因此您可能需要同时设置两者）。否则，请尝试使用来自`pkg-config`

```
set(Foo_VERSION ${PC_Foo_VERSION})
```

现在我们可以使用[`FindPackageHandleStandardArgs`](https://cmake.org/cmake/help/latest/module/FindPackageHandleStandardArgs.html#module:FindPackageHandleStandardArgs)为我们完成剩下的大部分工作

```
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(Foo
  FOUND_VAR Foo_FOUND
  REQUIRED_VARS
    Foo_LIBRARY
    Foo_INCLUDE_DIR
  VERSION_VAR Foo_VERSION
)
```

这将检查`REQUIRED_VARS`包含的值（不以 结尾`-NOTFOUND`）并`Foo_FOUND`正确设置。它还将缓存这些值。如果`Foo_VERSION`已设置，并且所需的版本已传递给[`find_package()`](https://cmake.org/cmake/help/latest/command/find_package.html#command:find_package)，它将检查请求的版本与`Foo_VERSION`. 它还将酌情打印消息；请注意，如果找到了包，它将打印第一个必需变量的内容以指示找到它的位置。

此时，我们必须为 find 模块的用户提供一种链接到找到的库的方法。[如上面的“查找模块](https://cmake.org/cmake/help/latest/manual/cmake-developer.7.html#find-modules)”部分所述，有两种方法。传统的变量方法看起来像

```
if(Foo_FOUND)
  set(Foo_LIBRARIES ${Foo_LIBRARY})
  set(Foo_INCLUDE_DIRS ${Foo_INCLUDE_DIR})
  set(Foo_DEFINITIONS ${PC_Foo_CFLAGS_OTHER})
endif()
```

如果找到多个库，则所有这些都应包含在这些变量中（有关更多信息，请参阅[标准变量名称](https://cmake.org/cmake/help/latest/manual/cmake-developer.7.html#standard-variable-names)部分）。

当提供导入的目标时，这些应该是命名空间的（因此是 `Foo::`前缀）；CMake 将识别传递给的值 [`target_link_libraries()`](https://cmake.org/cmake/help/latest/command/target_link_libraries.html#command:target_link_libraries)名称中包含`::`的应该是导入的目标（而不仅仅是库名称），并且如果该目标不存在，将生成适当的诊断消息（请参阅策略[`CMP0028`](https://cmake.org/cmake/help/latest/policy/CMP0028.html#policy:CMP0028)).

```
if(Foo_FOUND AND NOT TARGET Foo::Foo)
  add_library(Foo::Foo UNKNOWN IMPORTED)
  set_target_properties(Foo::Foo PROPERTIES
    IMPORTED_LOCATION "${Foo_LIBRARY}"
    INTERFACE_COMPILE_OPTIONS "${PC_Foo_CFLAGS_OTHER}"
    INTERFACE_INCLUDE_DIRECTORIES "${Foo_INCLUDE_DIR}"
  )
endif()
```

关于这一点需要注意的一点是，`INTERFACE_INCLUDE_DIRECTORIES`和类似的属性应该只包含关于目标本身的信息，而不是它的任何依赖项。相反，这些依赖项也应该是目标，并且应该告诉 CMake 它们是该目标的依赖项。然后 CMake 将自动组合所有必要的信息。

的类型[`IMPORTED`](https://cmake.org/cmake/help/latest/prop_tgt/IMPORTED.html#prop_tgt:IMPORTED)中创建的目标 [`add_library()`](https://cmake.org/cmake/help/latest/command/add_library.html#command:add_library)命令总是可以指定为`UNKNOWN` 类型。这在可能找到静态或共享变体的情况下简化了代码，CMake 将通过检查文件来确定类型。

如果库具有多种配置，则 [`IMPORTED_CONFIGURATIONS`](https://cmake.org/cmake/help/latest/prop_tgt/IMPORTED_CONFIGURATIONS.html#prop_tgt:IMPORTED_CONFIGURATIONS)还应填充目标属性：

```
if(Foo_FOUND)
  if (NOT TARGET Foo::Foo)
    add_library(Foo::Foo UNKNOWN IMPORTED)
  endif()
  if (Foo_LIBRARY_RELEASE)
    set_property(TARGET Foo::Foo APPEND PROPERTY
      IMPORTED_CONFIGURATIONS RELEASE
    )
    set_target_properties(Foo::Foo PROPERTIES
      IMPORTED_LOCATION_RELEASE "${Foo_LIBRARY_RELEASE}"
    )
  endif()
  if (Foo_LIBRARY_DEBUG)
    set_property(TARGET Foo::Foo APPEND PROPERTY
      IMPORTED_CONFIGURATIONS DEBUG
    )
    set_target_properties(Foo::Foo PROPERTIES
      IMPORTED_LOCATION_DEBUG "${Foo_LIBRARY_DEBUG}"
    )
  endif()
  set_target_properties(Foo::Foo PROPERTIES
    INTERFACE_COMPILE_OPTIONS "${PC_Foo_CFLAGS_OTHER}"
    INTERFACE_INCLUDE_DIRECTORIES "${Foo_INCLUDE_DIR}"
  )
endif()
```

`RELEASE`变体应首先在属性中列出，以便在用户使用与列出的任何配置都不完全匹配的配置时选择变体`IMPORTED_CONFIGURATIONS`。

大多数缓存变量应该隐藏在`ccmake`界面中，除非用户明确要求编辑它们。

```
mark_as_advanced(
  Foo_INCLUDE_DIR
  Foo_LIBRARY
)
```

如果此模块替换旧版本，您应该设置兼容性变量以尽可能减少中断。

```
# compatibility variables
set(Foo_VERSION_STRING ${Foo_VERSION})
```