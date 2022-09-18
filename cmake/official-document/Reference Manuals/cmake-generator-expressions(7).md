# [cmake-generator-expressions(7) ](https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html#id1)

内容

- [cmake 生成器表达式（7）](https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html#cmake-generator-expressions-7)
  - [介绍](https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html#introduction)
  - [空格和引用](https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html#whitespace-and-quoting)
  - [调试](https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html#debugging)
  - [生成器表达式参考](https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html#generator-expression-reference)
    - [条件表达式](https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html#conditional-expressions)
    - [逻辑运算符](https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html#logical-operators)
    - [主要比较表达式](https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html#primary-comparison-expressions)
      - [字符串比较](https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html#string-comparisons)
      - [版本比较](https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html#version-comparisons)
    - [字符串转换](https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html#string-transformations)
    - [列表表达式](https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html#list-expressions)
    - [路径表达式](https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html#path-expressions)
      - [路径比较](https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html#path-comparisons)
      - [路径查询](https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html#path-queries)
      - [路径分解](https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html#path-decomposition)
      - [路径变换](https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html#path-transformations)
      - [外壳路径](https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html#shell-paths)
    - [配置表达式](https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html#configuration-expressions)
    - [工具链和语言表达式](https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html#toolchain-and-language-expressions)
      - [平台](https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html#platform)
      - [编译器版本](https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html#compiler-version)
      - [编译器语言和 ID](https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html#compiler-language-and-id)
      - [编译功能](https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html#compile-features)
      - [链接器语言和 ID](https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html#linker-language-and-id)
      - [链接功能](https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html#link-features)
      - [链接上下文](https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html#link-context)
    - [目标相关表达式](https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html#target-dependent-expressions)
    - [导出和安装表达式](https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html#export-and-install-expressions)
    - [多级表达评估](https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html#multi-level-expression-evaluation)
    - [转义字符](https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html#escaped-characters)
    - [不推荐使用的表达式](https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html#deprecated-expressions)

## [Introduction](https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html#id2)

在构建系统生成期间评估生成器表达式以生成特定于每个构建配置的信息。他们有形式 `$<...>`。例如：

```
target_include_directories(tgt PRIVATE /opt/include/$<CXX_COMPILER_ID>)
```

根据使用的 C++ 编译器，这将扩展为`/opt/include/GNU`,等。`/opt/include/Clang`

在许多目标属性的上下文中都允许生成器表达式，例如[`LINK_LIBRARIES`](https://cmake.org/cmake/help/latest/prop_tgt/LINK_LIBRARIES.html#prop_tgt:LINK_LIBRARIES), [`INCLUDE_DIRECTORIES`](https://cmake.org/cmake/help/latest/prop_tgt/INCLUDE_DIRECTORIES.html#prop_tgt:INCLUDE_DIRECTORIES), [`COMPILE_DEFINITIONS`](https://cmake.org/cmake/help/latest/prop_tgt/COMPILE_DEFINITIONS.html#prop_tgt:COMPILE_DEFINITIONS)和别的。它们也可以在使用命令填充这些属性时使用，例如[`target_link_libraries()`](https://cmake.org/cmake/help/latest/command/target_link_libraries.html#command:target_link_libraries), [`target_include_directories()`](https://cmake.org/cmake/help/latest/command/target_include_directories.html#command:target_include_directories),[`target_compile_definitions()`](https://cmake.org/cmake/help/latest/command/target_compile_definitions.html#command:target_compile_definitions) 和别的。它们启用条件链接、编译时使用的条件定义、条件包含目录等。条件可以基于构建配置、目标属性、平台信息或任何其他可查询信息。

生成器表达式可以嵌套：

```
target_compile_definitions(tgt PRIVATE
  $<$<VERSION_LESS:$<CXX_COMPILER_VERSION>,4.2.0>:OLD_COMPILER>
)
```

以上将扩展到`OLD_COMPILER`如果 [`CMAKE_CXX_COMPILER_VERSION`](https://cmake.org/cmake/help/latest/variable/CMAKE_LANG_COMPILER_VERSION.html#variable:CMAKE__COMPILER_VERSION)小于 4.2.0。

## [空格和引号](https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html#id3)

生成器表达式通常在命令参数之后解析。如果生成器表达式包含空格、换行符、分号或其他可能被解释为命令参数分隔符的字符，则整个表达式在传递给命令时应该用引号括起来。不这样做可能会导致表达式被拆分，并且可能不再被识别为生成器表达式。

使用时[`add_custom_command()`](https://cmake.org/cmake/help/latest/command/add_custom_command.html#command:add_custom_command)或者[`add_custom_target()`](https://cmake.org/cmake/help/latest/command/add_custom_target.html#command:add_custom_target), 使用`VERBATIM`and`COMMAND_EXPAND_LISTS`选项来获得健壮的参数拆分和引用。

```
# WRONG: Embedded space will be treated as an argument separator.
# This ends up not being seen as a generator expression at all.
add_custom_target(run_some_tool
  COMMAND some_tool -I$<JOIN:$<TARGET_PROPERTY:tgt,INCLUDE_DIRECTORIES>, -I>
  VERBATIM
)
# Better, but still not robust. Quotes prevent the space from splitting the
# expression. However, the tool will receive the expanded value as a single
# argument.
add_custom_target(run_some_tool
  COMMAND some_tool "-I$<JOIN:$<TARGET_PROPERTY:tgt,INCLUDE_DIRECTORIES>, -I>"
  VERBATIM
)
# Nearly correct. Using a semicolon to separate arguments and adding the
# COMMAND_EXPAND_LISTS option means that paths with spaces will be handled
# correctly. Quoting the whole expression ensures it is seen as a generator
# expression. But if the target property is empty, we will get a bare -I
# with nothing after it.
add_custom_target(run_some_tool
  COMMAND some_tool "-I$<JOIN:$<TARGET_PROPERTY:tgt,INCLUDE_DIRECTORIES>,;-I>"
  COMMAND_EXPAND_LISTS
  VERBATIM
)
```

使用变量构建更复杂的生成器表达式也是减少错误和提高可读性的好方法。上面的例子可以进一步改进，如下所示：

```
# The $<BOOL:...> check prevents adding anything if the property is empty,
# assuming the property value cannot be one of CMake's false constants.
set(prop "$<TARGET_PROPERTY:tgt,INCLUDE_DIRECTORIES>")
add_custom_target(run_some_tool
  COMMAND some_tool "$<$<BOOL:${prop}>:-I$<JOIN:${prop},;-I>>"
  COMMAND_EXPAND_LISTS
  VERBATIM
)
```

一个常见的错误是尝试使用缩进将生成器表达式拆分为多行：

```
# WRONG: New lines and spaces all treated as argument separators, so the
# generator expression is split and not recognized correctly.
target_compile_definitions(tgt PRIVATE
  $<$<AND:
      $<CXX_COMPILER_ID:GNU>,
      $<VERSION_GREATER_EQUAL:$<CXX_COMPILER_VERSION>,5>
    >:HAVE_5_OR_LATER>
)
```

再次，使用具有良好名称的辅助变量来构建一个可读的表达式：

```
set(is_gnu "$<CXX_COMPILER_ID:GNU>")
set(v5_or_later "$<VERSION_GREATER_EQUAL:$<CXX_COMPILER_VERSION>,5>")
set(meet_requirements "$<AND:${is_gnu},${v5_or_later}>")
target_compile_definitions(tgt PRIVATE
  "$<${meet_requirements}:HAVE_5_OR_LATER>"
)
```

## [Debugging](https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html#id4)

由于生成器表达式是在生成构建系统期间评估的，而不是在处理`CMakeLists.txt`文件期间，因此无法使用[`message()`](https://cmake.org/cmake/help/latest/command/message.html#command:message)命令。生成调试消息的一种可能方法是添加自定义目标：

```
add_custom_target(genexdebug COMMAND ${CMAKE_COMMAND} -E echo "$<...>")
```

运行后`cmake`，您可以构建`genexdebug`目标以打印`$<...>`表达式的结果（即运行命令 ）。`cmake --build ... --target genexdebug`

另一种方法是将调试消息写入文件[`file(GENERATE)`](https://cmake.org/cmake/help/latest/command/file.html#command:file):

```
file(GENERATE OUTPUT filename CONTENT "$<...>")
```

## [生成器表达式参考](https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html#id5)

笔记

 

该参考与大多数 CMake 文档有所不同，因为它省略了`<...>`占位符周围的尖括号，例如`condition`, `string`,`target`等。这是为了防止这些占位符被误解为生成器表达式的机会。



### [条件表达式](https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html#id6)

生成器表达式的一个基本类别与条件逻辑有关。支持两种形式的条件生成器表达式：

- **$<条件：true_string>**

  评估为`true_string`if `condition`is `1`，或一个空字符串 if`condition`评估为`0`。任何其他值都会`condition` 导致错误。

- **$<IF:条件,true_string,false_string>**

  *3.8 版中的新功能。*评估`true_string`if `condition`is`1`或`false_string` if `condition`is `0`。任何其他值都会`condition`导致错误。

通常，`condition`它本身就是一个生成器表达式。例如，以下表达式扩展为`DEBUG_MODE`使用`Debug` 配置时，以及所有其他配置的空字符串：

```
$<$<CONFIG:Debug>:DEBUG_MODE>
```

除了or之外的类似布尔`condition`值可以通过用生成器表达式包装它们来处理：`1``0``$<BOOL:...>`

- **$<BOOL:string>**

  转换`string`为`0`或`1`。评估`0`以下任何一项是否为真：`string`是空的，`string`是不区分大小写的等于 `0`, `FALSE`, `OFF`, `N`, `NO`, `IGNORE`, or `NOTFOUND`, or`string`以后缀结尾`-NOTFOUND`（区分大小写）。否则计算为`1`。

当a 由 CMake 变量提供`$<BOOL:...>`时，通常使用生成器表达式：`condition`

```
$<$<BOOL:${HAVE_SOME_FEATURE}>:-DENABLE_SOME_FEATURE>
```



### [逻辑运算符](https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html#id7)

支持常见的布尔逻辑运算符：

- **$<AND:条件>**

  where`conditions`是一个以逗号分隔的布尔表达式列表，所有这些表达式的计算结果都必须为`1`or `0`。`1`如果所有条件都是，则整个表达式的计算结果为`1`。如果任何条件为`0`，则整个表达式的计算结果为`0`。

- **$<OR:条件>**

  where`conditions`是以逗号分隔的布尔表达式列表。所有这些都必须评估为`1`or `0`。`1`如果至少有一个是，则整个表达式的计算结果`conditions`为`1`。如果全部 `conditions`计算为`0`，则整个表达式的计算结果为`0`。

- **$<NOT:条件>**

  `condition`必须是`0`或`1`。表达式的结果是 `0`if `condition`is `1`, else `1`。



### [主要比较表达式](https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html#id8)

CMake 支持各种比较事物的生成器表达式。本节介绍主要和最广泛使用的比较类型。其他更具体的比较类型在下面单独的部分中记录。

#### [字符串比较](https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html#id9)

- **$<STREQUAL:string1,string2>**

  `1`如果`string1`和`string2`相等，否则`0`。比较区分大小写。对于不区分大小写的比较，请结合[字符串转换生成器表达式](https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html#string-transforming-generator-expressions)。例如，以下计算结果`1`是否`${foo}`为`BAR`、`Bar`、`bar`等中的任何一个。`$<STREQUAL:$<UPPER_CASE:${foo}>,BAR> `

- **$<EQUAL:value1,value2>**

  `1`如果`value1`和`value2`在数值上相等，否则`0`。

#### [版本比较](https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html#id10)

- **$<VERSION_LESS:v1,v2>**

  `1`if`v1`是小于 的版本`v2`，否则`0`。

- **$<VERSION_GREATER:v1,v2>**

  `1`if`v1`是大于 的版本`v2`，否则`0`。

- **$<VERSION_EQUAL:v1,v2>**

  `1`if与, else`v1`版本相同。`v2``0`

- **$<VERSION_LESS_EQUAL:v1,v2>**

  *3.7 版中的新功能。*`1`if`v1`是小于或等于 的版本`v2`，否则`0`。

- **$<VERSION_GREATER_EQUAL:v1,v2>**

  *3.7 版中的新功能。*`1`if`v1`是大于或等于 的版本`v2`，否则`0`。



### [字符串转换](https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html#id11)

- **$<LOWER_CASE:string>**

  `string`转换为小写的内容。

- **$<UPPER_CASE:string>**

  `string`转换为大写的内容。

- **$<MAKE_C_IDENTIFIER:...>**

  `...`转换为 C 标识符的内容。转换遵循与[`string(MAKE_C_IDENTIFIER)`](https://cmake.org/cmake/help/latest/command/string.html#command:string).

### [列表表达式](https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html#id12)

- **$<IN_LIST:string,list>**

  *版本 3.12 中的新功能。*`1`if`string`是分号分隔的项目`list`，否则`0`。它使用区分大小写的比较。

- **$<JOIN:list,string>**

  `string`在每个项目之间插入的内容加入列表。

- **$<REMOVE_DUPLICATES:list>**

  *3.15 版中的新功能。*删除给定的重复项`list`。项目的相对顺序被保留，但如果遇到重复项，则仅保留第一个实例。

- **$<FILTER:list,INCLUDE|EXCLUDE,regex>**

  *3.15 版中的新功能。*包括或删除`list`与正则表达式匹配的 项目`regex`。

### [路径表达式](https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html#id13)

本节中的大部分表达都与 [`cmake_path()`](https://cmake.org/cmake/help/latest/command/cmake_path.html#command:cmake_path)命令，提供相同的功能，但采用生成器表达式的形式。

对于本节中的所有生成器表达式，路径应采用 cmake 样式格式。[$](https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html#genex-path-cmake-path) 生成器表达式可用于将本机路径转换为 cmake 样式的路径。



#### [路径比较](https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html#id14)

- **$<PATH_EQUAL:path1,path2>**

  *版本 3.24 中的新功能。*比较两条路径的词法表示。没有对任一路径执行标准化。`1`如果路径相等则返回，`0` 否则返回。有关更多详细信息，请参见[cmake_path(COMPARE)](https://cmake.org/cmake/help/latest/command/cmake_path.html#path-compare)。



#### [路径查询](https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html#id15)

这些表达式提供了与 [Query](https://cmake.org/cmake/help/latest/command/cmake_path.html#path-query)选项等效的生成时间功能[`cmake_path()`](https://cmake.org/cmake/help/latest/command/cmake_path.html#command:cmake_path)命令。所有路径都应采用 cmake 样式格式。

- **$<PATH:HAS_\*,path>**

  *版本 3.24 中的新功能。*`1`如果存在特定路径组件，则返回以下操作，`0`否则返回。有关每个路径组件的含义，请参阅[路径结构和术语](https://cmake.org/cmake/help/latest/command/cmake_path.html#path-structure-and-terminology)。`$<PATH:HAS_ROOT_NAME,path> $<PATH:HAS_ROOT_DIRECTORY,path> $<PATH:HAS_ROOT_PATH,path> $<PATH:HAS_FILENAME,path> $<PATH:HAS_EXTENSION,path> $<PATH:HAS_STEM,path> $<PATH:HAS_RELATIVE_PART,path> $<PATH:HAS_PARENT_PATH,path> `请注意以下特殊情况：对于，只有当或中的至少一个不为空`HAS_ROOT_PATH`时才会返回真正的结果。`root-name``root-directory`对于`HAS_PARENT_PATH`，根目录也被认为有一个父目录，它就是它自己。结果为真，除非路径仅包含一个[文件名](https://cmake.org/cmake/help/latest/command/cmake_path.html#filename-def)。

- **$<PATH:IS_ABSOLUTE,路径>**

  *版本 3.24 中的新功能。*`1`如果路径是[绝对](https://cmake.org/cmake/help/latest/command/cmake_path.html#is-absolute)的，则返回，`0`否则。

- **$<PATH:IS_RELATIVE,路径>**

  *版本 3.24 中的新功能。*这将返回相反的`IS_ABSOLUTE`.

- **$<PATH:IS_PREFIX[,NORMALIZE],路径,输入>**

  *版本 3.24 中的新功能。*`1`如果`path`是 的前缀，则返回`input`，`0`否则。指定`NORMALIZE`选项`path`并在检查前`input`进行 [标准化](https://cmake.org/cmake/help/latest/command/cmake_path.html#normalization)时。



#### [路径分解](https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html#id16)

这些表达式提供的生成时间功能 [等同](https://cmake.org/cmake/help/latest/command/cmake_path.html#path-decomposition)于[`cmake_path()`](https://cmake.org/cmake/help/latest/command/cmake_path.html#command:cmake_path) 命令。所有路径都应采用 cmake 样式格式。

- **$<PATH:GET_\*,...>**

  *版本 3.24 中的新功能。*以下操作从路径中检索不同的组件或组件组。有关每个路径组件的含义，请参阅[路径结构和术语](https://cmake.org/cmake/help/latest/command/cmake_path.html#path-structure-and-terminology)。`$<PATH:GET_ROOT_NAME,path> $<PATH:GET_ROOT_DIRECTORY,path> $<PATH:GET_ROOT_PATH,path> $<PATH:GET_FILENAME,path> $<PATH:GET_EXTENSION[,LAST_ONLY],path> $<PATH:GET_STEM[,LAST_ONLY],path> $<PATH:GET_RELATIVE_PART,path> $<PATH:GET_PARENT_PATH,path> `如果路径中不存在请求的组件，则返回空字符串。



#### [路径转换](https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html#id17)

这些表达式提供等效于 [修改](https://cmake.org/cmake/help/latest/command/cmake_path.html#path-modification)和[生成](https://cmake.org/cmake/help/latest/command/cmake_path.html#path-generation) 选项的生成时间功能[`cmake_path()`](https://cmake.org/cmake/help/latest/command/cmake_path.html#command:cmake_path)命令。所有路径都应采用 cmake 样式格式。



- **$<PATH:CMAKE_PATH[,NORMALIZE],路径>**

  *版本 3.24 中的新功能。*退货`path`。如果`path`是本机路径，则将其转换为带有正斜杠 ( `/`) 的 cmake 样式路径。在 Windows 上，考虑了长文件名标记。指定选项时`NORMALIZE`，路径在转换后进行[规范化。](https://cmake.org/cmake/help/latest/command/cmake_path.html#normalization)

- **$<PATH:APPEND,路径,输入,...>**

  *版本 3.24 中的新功能。*返回`input`附加到`path`using `/`as 的 所有参数`directory-separator`。根据`input`， 的值`path` 可能会被丢弃。有关更多详细信息，请参见[cmake_path(APPEND)](https://cmake.org/cmake/help/latest/command/string.html#append)。

- **$<PATH:REMOVE_FILENAME,路径>**

  *版本 3.24 中的新功能。*返回并删除`path`文件名组件（由 返回 ）。`$<PATH:GET_FILENAME>`删除后，任何尾随 `directory-separator`（如果存在）将被单独留下。有关更多详细信息，请参阅[cmake_path(REMOVE_FILENAME)](https://cmake.org/cmake/help/latest/command/cmake_path.html#remove-filename)。

- **$<PATH:REPLACE_FILENAME，路径，输入>**

  *版本 3.24 中的新功能。*返回`path`文件名组件替换为`input`. 如果 `path`没有文件名组件（即`$<PATH:HAS_FILENAME>`返回 `0`），`path`则不变。有关更多详细信息，请参阅[cmake_path(REPLACE_FILENAME)](https://cmake.org/cmake/help/latest/command/cmake_path.html#replace-filename)。

- **$<PATH:REMOVE_EXTENSION[,LAST_ONLY],路径>**

  *版本 3.24 中的新功能。*[删除扩展名](https://cmake.org/cmake/help/latest/command/cmake_path.html#extension-def)（如果有）`path`返回。有关更多详细信息，请参阅[cmake_path(REMOVE_EXTENSION)](https://cmake.org/cmake/help/latest/command/cmake_path.html#remove-extension)。

- **$<PATH:REPLACE_EXTENSION[,LAST_ONLY],路径,输入>**

  *版本 3.24 中的新功能。*如果有，则返回`path`用替换 的[扩展名](https://cmake.org/cmake/help/latest/command/cmake_path.html#extension-def)`input`。有关更多详细信息，请参阅[cmake_path(REPLACE_EXTENSION)](https://cmake.org/cmake/help/latest/command/cmake_path.html#replace-extension)。

- **$<PATH:NORMAL_PATH,路径>**

  *版本 3.24 中的新功能。*`path`根据规范化中描述的步骤 返回[规范化](https://cmake.org/cmake/help/latest/command/cmake_path.html#normalization)。

- **$<PATH:RELATIVE_PATH,path,base_directory>**

  *版本 3.24 中的新功能。*返回`path`，修改为相对于`base_directory` 参数。有关更多详细信息，请参见[cmake_path(RELATIVE_PATH)](https://cmake.org/cmake/help/latest/command/cmake_path.html#cmake-path-relative-path)。

- **$<PATH:ABSOLUTE_PATH[,NORMALIZE],path,base_directory>**

  *版本 3.24 中的新功能。*`path`以绝对值返回。如果`path`是相对路径（`$<PATH:IS_RELATIVE>`返回`1`），则相对于参数指定的给定基目录进行评估`base_directory`。指定选项时，路径计算后`NORMALIZE`路径被 [归一化。](https://cmake.org/cmake/help/latest/command/cmake_path.html#normalization)有关更多详细信息，请参见[cmake_path(ABSOLUTE_PATH)](https://cmake.org/cmake/help/latest/command/cmake_path.html#absolute-path)。

#### [外壳路径](https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html#id18)

- **$<SHELL_PATH:...>**

  *3.4 版中的新功能。*`...`转换为 shell 路径样式的内容。例如，斜杠在 Windows shell 中被转换为反斜杠，驱动器号在 MSYS shell 中被转换为 posix 路径。`...`必须是绝对路径。*3.14 版中*的新功能：`...`可能是以[分号分隔](https://cmake.org/cmake/help/latest/manual/cmake-language.7.html#cmake-language-lists)`:`的路径列表，在这种情况下，每个路径都会单独转换，并使用 shell 路径分隔符（在 POSIX 和 `;`Windows 上） 生成结果列表。请务必在 CMake 源代码中将包含此基因的参数括在双引号中，`;`以免拆分参数。

### [配置表达式](https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html#id19)

- **$<配置>**

  配置名称。使用这个而不是弃用的[`CONFIGURATION`](https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html#genex:CONFIGURATION) 生成器表达式。

- **$<配置：cfgs>**

  `1`如果 config 是逗号分隔列表中的任何一项 `cfgs`，否则`0`。这是不区分大小写的比较。中的映射 [`MAP_IMPORTED_CONFIG_`](https://cmake.org/cmake/help/latest/prop_tgt/MAP_IMPORTED_CONFIG_CONFIG.html#prop_tgt:MAP_IMPORTED_CONFIG_)此表达式在对[`IMPORTED`](https://cmake.org/cmake/help/latest/prop_tgt/IMPORTED.html#prop_tgt:IMPORTED) 目标。

- **$<OUTPUT_CONFIG:...>**

  *3.20 版中的新功能。*仅适用于[`add_custom_command()`](https://cmake.org/cmake/help/latest/command/add_custom_command.html#command:add_custom_command)和[`add_custom_target()`](https://cmake.org/cmake/help/latest/command/add_custom_target.html#command:add_custom_target) 作为参数中最外层的生成器表达式。随着[`Ninja Multi-Config`](https://cmake.org/cmake/help/latest/generator/Ninja Multi-Config.html#generator:Ninja Multi-Config)生成器，生成器表达式`...`使用自定义命令的“输出配置”进行评估。使用其他生成器，`...`通常会评估 的内容。

- **$<COMMAND_CONFIG:...>**

  *3.20 版中的新功能。*仅适用于[`add_custom_command()`](https://cmake.org/cmake/help/latest/command/add_custom_command.html#command:add_custom_command)和[`add_custom_target()`](https://cmake.org/cmake/help/latest/command/add_custom_target.html#command:add_custom_target) 作为参数中最外层的生成器表达式。随着[`Ninja Multi-Config`](https://cmake.org/cmake/help/latest/generator/Ninja Multi-Config.html#generator:Ninja Multi-Config)生成器，生成器表达式`...`使用自定义命令的“命令配置”进行评估。使用其他生成器，`...`通常会评估 的内容。

### [工具链和语言表达式](https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html#id20)

#### [Platform](https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html#id21)

- **$<PLATFORM_ID>**

  当前系统的 CMake 平台 ID。另见[`CMAKE_SYSTEM_NAME`](https://cmake.org/cmake/help/latest/variable/CMAKE_SYSTEM_NAME.html#variable:CMAKE_SYSTEM_NAME)多变的。

- **$<PLATFORM_ID:platform_ids>**

  where`platform_ids`是一个逗号分隔的列表。 `1`如果 CMake 的平台 id 与 中的任何一个条目匹配 `platform_ids`，否则`0`。另见[`CMAKE_SYSTEM_NAME`](https://cmake.org/cmake/help/latest/variable/CMAKE_SYSTEM_NAME.html#variable:CMAKE_SYSTEM_NAME)多变的。

#### [编译器版本](https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html#id22)

另见[`CMAKE__COMPILER_VERSION`](https://cmake.org/cmake/help/latest/variable/CMAKE_LANG_COMPILER_VERSION.html#variable:CMAKE__COMPILER_VERSION)变量，这与本小节中的表达式密切相关。

- **$<C_COMPILER_VERSION>**

  使用的 C 编译器的版本。

- **$<C_COMPILER_VERSION:版本>**

  `1`如果 C 编译器的版本匹配`version`，否则`0`。

- **$<CXX_COMPILER_VERSION>**

  使用的 CXX 编译器的版本。

- **$<CXX_COMPILER_VERSION:版本>**

  `1`如果 CXX 编译器的版本匹配`version`，否则`0`。

- **$<CUDA_COMPILER_VERSION>**

  *3.15 版中的新功能。*使用的 CUDA 编译器的版本。

- **$<CUDA_COMPILER_VERSION:版本>**

  *3.15 版中的新功能。*`1`如果 CXX 编译器的版本匹配`version`，否则`0`。

- **$<OBJC_COMPILER_VERSION>**

  *3.16 版中的新功能。*使用的 OBJC 编译器的版本。

- **$<OBJC_COMPILER_VERSION:版本>**

  *3.16 版中的新功能。*`1`如果 OBJC 编译器的版本匹配`version`，否则`0`。

- **$<OBJCXX_COMPILER_VERSION>**

  *3.16 版中的新功能。*使用的 OBJCXX 编译器的版本。

- **$<OBJCXX_COMPILER_VERSION:版本>**

  *3.16 版中的新功能。*`1`如果 OBJCXX 编译器的版本匹配`version`，否则`0`。

- **$<Fortran_COMPILER_VERSION>**

  使用的 Fortran 编译器的版本。

- **$<Fortran_COMPILER_VERSION:版本>**

  `1`如果 Fortran 编译器的版本匹配`version`，否则`0`。

- **$<HIP_COMPILER_VERSION>**

  *3.21 版中的新功能。*使用的 HIP 编译器的版本。

- **$<HIP_COMPILER_VERSION:版本>**

  *3.21 版中的新功能。*`1`如果 HIP 编译器的版本匹配`version`，否则`0`。

- **$<ISPC_COMPILER_VERSION>**

  *3.19 版中的新功能。*使用的 ISPC 编译器的版本。

- **$<ISPC_COMPILER_VERSION:版本>**

  *3.19 版中的新功能。*`1`如果 ISPC 编译器的版本匹配`version`，否则`0`。

#### [编译器语言和 ID ](https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html#id23)

另见[`CMAKE__COMPILER_ID`](https://cmake.org/cmake/help/latest/variable/CMAKE_LANG_COMPILER_ID.html#variable:CMAKE__COMPILER_ID)变量，它与本小节中的大多数表达式密切相关。

- **$<C_COMPILER_ID>**

  使用的 C 编译器的 CMake 编译器 ID。

- **$<C_COMPILER_ID:compiler_ids>**

  where`compiler_ids`是一个逗号分隔的列表。 `1`如果 CMake 的 C 编译器的编译器 ID 与 中的任何一个条目匹配`compiler_ids`，否则`0`.

- **$<CXX_COMPILER_ID>**

  使用的 CXX 编译器的 CMake 编译器 ID。

- **$<CXX_COMPILER_ID:compiler_ids>**

  where`compiler_ids`是一个逗号分隔的列表。 `1`如果 CMake 的 CXX 编译器的编译器 ID 与 中的任何一个条目匹配`compiler_ids`，否则`0`.

- **$<CUDA_COMPILER_ID>**

  *3.15 版中的新功能。*使用的 CUDA 编译器的 CMake 编译器 ID。

- **$<CUDA_COMPILER_ID:compiler_ids>**

  *3.15 版中的新功能。*where`compiler_ids`是一个逗号分隔的列表。 `1`如果 CUDA 编译器的 CMake 编译器 ID 匹配 中的任何一个条目`compiler_ids`，否则`0`.

- **$<OBJC_COMPILER_ID>**

  *3.16 版中的新功能。*使用的 OBJC 编译器的 CMake 编译器 ID。

- **$<OBJC_COMPILER_ID:compiler_ids>**

  *3.16 版中的新功能。*where`compiler_ids`是一个逗号分隔的列表。 `1`如果 CMake 的 Objective-C 编译器的编译器 id 与 中的任何一个条目匹配`compiler_ids`，否则`0`.

- **$<OBJCXX_COMPILER_ID>**

  *3.16 版中的新功能。*使用的 OBJCXX 编译器的 CMake 编译器 ID。

- **$<OBJCXX_COMPILER_ID:compiler_ids>**

  *3.16 版中的新功能。*where`compiler_ids`是一个逗号分隔的列表。 `1`如果 Objective-C++ 编译器的 CMake 的编译器 ID 匹配 中的任何一个条目`compiler_ids`，否则`0`.

- **$<Fortran_COMPILER_ID>**

  使用的 Fortran 编译器的 CMake 编译器 ID。

- **$<Fortran_COMPILER_ID:compiler_ids>**

  where`compiler_ids`是一个逗号分隔的列表。 `1`如果 Fortran 编译器的 CMake 编译器 ID 匹配 中的任何一个条目`compiler_ids`，否则`0`.

- **$<HIP_COMPILER_ID>**

  *3.21 版中的新功能。*使用的 HIP 编译器的 CMake 编译器 ID。

- **$<HIP_COMPILER_ID:compiler_ids>**

  *3.21 版中的新功能。*where`compiler_ids`是一个逗号分隔的列表。 `1`如果 CMake 的 HIP 编译器的编译器 id 与 中的任何一个条目匹配`compiler_ids`，否则`0`.

- **$<ISPC_COMPILER_ID>**

  *3.19 版中的新功能。*使用的 ISPC 编译器的 CMake 编译器 ID。

- **$<ISPC_COMPILER_ID:compiler_ids>**

  *3.19 版中的新功能。*where`compiler_ids`是一个逗号分隔的列表。 `1`如果 ISPC 编译器的 CMake 编译器 ID 与 中的任何一个条目匹配`compiler_ids`，否则`0`.

- **$<编译语言>**

  *3.3 版中的新功能。*评估编译选项时源文件的编译语言。有关此生成器表达式的可移植性的说明，请参阅[相关的布尔](https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html#boolean-compile-language-generator-expression) `$<COMPILE_LANGUAGE:language>` 表达式。



- **$<COMPILE_LANGUAGE:语言>**

  *3.3 版中的新功能。*`1`当用于编译单元的语言与 中的任何条目匹配时`languages`，否则`0`。此表达式可用于指定编译选项、编译定义和包含目标中特定语言的源文件的目录。例如：`add_executable(myapp main.cpp foo.c bar.cpp zot.cu) target_compile_options(myapp  PRIVATE $<$<COMPILE_LANGUAGE:CXX>:-fno-exceptions> ) target_compile_definitions(myapp  PRIVATE $<$<COMPILE_LANGUAGE:CXX>:COMPILING_CXX>          $<$<COMPILE_LANGUAGE:CUDA>:COMPILING_CUDA> ) target_include_directories(myapp  PRIVATE $<$<COMPILE_LANGUAGE:CXX,CUDA>:/opt/foo/headers> ) `这指定了`-fno-exceptions`编译选项、 `COMPILING_CXX`编译定义和`cxx_headers`仅用于 C++ 的包含目录的使用（编译器 id 检查省略）。它还指定了`COMPILING_CUDA`CUDA 的编译定义。请注意，使用[Visual Studio 生成器](https://cmake.org/cmake/help/latest/manual/cmake-generators.7.html#visual-studio-generators)和[`Xcode`](https://cmake.org/cmake/help/latest/generator/Xcode.html#generator:Xcode)无法表示目标范围的编译定义或单独包含`C`和`CXX`语言的目录。此外，使用[Visual Studio 生成器](https://cmake.org/cmake/help/latest/manual/cmake-generators.7.html#visual-studio-generators)无法分别表示目标范围的标志`C`和`CXX`语言。`CXX`在这些生成器下，如果有任何 C++ 源，则C 和 C++ 源的表达式将使用，否则使用`C`. 一种解决方法是为每种源文件语言创建单独的库：`add_library(myapp_c foo.c) add_library(myapp_cxx bar.cpp) target_compile_options(myapp_cxx PUBLIC -fno-exceptions) add_executable(myapp main.cpp) target_link_libraries(myapp myapp_c myapp_cxx) `

- **$<COMPILE_LANG_AND_ID:language,compiler_ids>**

  *3.15 版中的新功能。*`1`当用于编译单元的语言匹配`language`并且编译器的 CMake 的编译器 id`language`匹配 中的任何一个条目时`compiler_ids`，否则`0`. 此表达式是`$<COMPILE_LANGUAGE:language>`和 组合的简写形式`$<LANG_COMPILER_ID:compiler_ids>`。此表达式可用于指定编译选项、编译定义以及包含特定语言的源文件和目标中的编译器组合的目录。例如：`add_executable(myapp main.cpp foo.c bar.cpp zot.cu) target_compile_definitions(myapp  PRIVATE $<$<COMPILE_LANG_AND_ID:CXX,AppleClang,Clang>:COMPILING_CXX_WITH_CLANG>          $<$<COMPILE_LANG_AND_ID:CXX,Intel>:COMPILING_CXX_WITH_INTEL>          $<$<COMPILE_LANG_AND_ID:C,Clang>:COMPILING_C_WITH_CLANG> ) `这指定了基于编译器 id 和编译语言的不同编译定义的使用。`COMPILING_CXX_WITH_CLANG`当 Clang 是 CXX 编译器，而`COMPILING_CXX_WITH_INTEL`Intel 是 CXX 编译器时，此示例将具有 编译定义。同样，当 C 编译器是 Clang 时，它只会看到 `COMPILING_C_WITH_CLANG`定义。如果没有`COMPILE_LANG_AND_ID`生成器表达式，相同的逻辑将表示为：`target_compile_definitions(myapp  PRIVATE $<$<AND:$<COMPILE_LANGUAGE:CXX>,$<CXX_COMPILER_ID:AppleClang,Clang>>:COMPILING_CXX_WITH_CLANG>          $<$<AND:$<COMPILE_LANGUAGE:CXX>,$<CXX_COMPILER_ID:Intel>>:COMPILING_CXX_WITH_INTEL>          $<$<AND:$<COMPILE_LANGUAGE:C>,$<C_COMPILER_ID:Clang>>:COMPILING_C_WITH_CLANG> ) `

#### [编译功能](https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html#id24)

- **$<COMPILE_FEATURES:features>**

  *3.1 版中的新功能。*where`features`是一个逗号分隔的列表。评估`1`是否所有`features`这些都可用于“头部”目标，`0`否则。如果在评估目标的链接实现时使用此表达式，并且如果任何依赖项会传递地增加所需的[`C_STANDARD`](https://cmake.org/cmake/help/latest/prop_tgt/C_STANDARD.html#prop_tgt:C_STANDARD)或者[`CXX_STANDARD`](https://cmake.org/cmake/help/latest/prop_tgt/CXX_STANDARD.html#prop_tgt:CXX_STANDARD) 对于'head'目标，报错。见 [`cmake-compile-features(7)`](https://cmake.org/cmake/help/latest/manual/cmake-compile-features.7.html#manual:cmake-compile-features(7))有关编译功能和支持的编译器列表的信息手册。

#### [链接器语言和 ID ](https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html#id25)

- **$<LINK_LANGUAGE>**

  *3.18 版中的新功能。*评估链接选项时目标的链接语言。有关此生成器表达式的可移植性的说明，请参阅[相关的布尔](https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html#boolean-link-language-generator-expression) `$<LINK_LANGUAGE:languages>` 表达式。笔记 链接库属性不支持此生成器表达式，以避免由于对这些属性进行双重评估而产生的副作用。



- **$<LINK_LANGUAGE:语言>**

  *3.18 版中的新功能。*`1`当用于链接步骤的语言与 中的任何条目匹配时`languages`，否则`0`。此表达式可用于指定目标中特定语言的链接库、链接选项、链接目录和链接依赖项。例如：`add_library(api_C ...) add_library(api_CXX ...) add_library(api INTERFACE) target_link_options(api   INTERFACE $<$<LINK_LANGUAGE:C>:-opt_c>                                    $<$<LINK_LANGUAGE:CXX>:-opt_cxx>) target_link_libraries(api INTERFACE $<$<LINK_LANGUAGE:C>:api_C>                                    $<$<LINK_LANGUAGE:CXX>:api_CXX>) add_executable(myapp1 main.c) target_link_options(myapp1 PRIVATE api) add_executable(myapp2 main.cpp) target_link_options(myapp2 PRIVATE api) `这指定使用`api`目标来链接目标`myapp1`和 `myapp2`. 在实践中，`myapp1`将与目标`api_C`和选项链接，`-opt_c`因为它将`C`用作链接语言。并且`myapp2` 将与`api_CXX`和选项链接，`-opt_cxx`因为`CXX`将是链接语言。笔记 为了确定目标的链接语言，需要传递地收集将链接到它的所有目标。因此，对于链接库属性，将进行双重评估。在第一次评估期间，`$<LINK_LANGUAGE:..>`表达式将始终返回`0`。第一次通过后计算的链接语言将用于第二次通过。为避免不一致，要求第二遍不要更改链接语言。此外，为了避免意外的副作用，需要指定完整的实体作为 `$<LINK_LANGUAGE:..>`表达式的一部分。例如：`add_library(lib STATIC file.cxx) add_library(libother STATIC file.c) # bad usage add_executable(myapp1 main.c) target_link_libraries(myapp1 PRIVATE lib$<$<LINK_LANGUAGE:C>:other>) # correct usage add_executable(myapp2 main.c) target_link_libraries(myapp2 PRIVATE $<$<LINK_LANGUAGE:C>:libother>) `在此示例中，对于`myapp1`，第一遍将意外地确定链接语言是`CXX`因为生成器表达式的评估将是一个空字符串，因此`myapp1`将取决于目标`lib`是`C++`。相反，对于`myapp2`，第一次评估将`C`作为链接语言给出，因此第二次将正确添加目标`libother`作为链接依赖项。

- **$<LINK_LANG_AND_ID:language,compiler_ids>**

  *3.18 版中的新功能。*`1`当用于链接步骤的语言匹配`language`并且语言链接器的 CMake 编译器 id 与 中的任何一个条目匹配时`compiler_ids`，否则`0`. 此表达式是`$<LINK_LANGUAGE:language>`和 组合的简写形式`$<LANG_COMPILER_ID:compiler_ids>`。此表达式可用于指定目标中特定语言和链接器组合的链接库、链接选项、链接目录和链接依赖项。例如：`add_library(libC_Clang ...) add_library(libCXX_Clang ...) add_library(libC_Intel ...) add_library(libCXX_Intel ...) add_executable(myapp main.c) if (CXX_CONFIG)  target_sources(myapp PRIVATE file.cxx) endif() target_link_libraries(myapp  PRIVATE $<$<LINK_LANG_AND_ID:CXX,Clang,AppleClang>:libCXX_Clang>          $<$<LINK_LANG_AND_ID:C,Clang,AppleClang>:libC_Clang>          $<$<LINK_LANG_AND_ID:CXX,Intel>:libCXX_Intel>          $<$<LINK_LANG_AND_ID:C,Intel>:libC_Intel>) `这指定了基于编译器 id 和链接语言的不同链接库的使用。此示例将在或为 链接器时以及何时为链接器时将目标`libCXX_Clang` 作为链接依赖项。同样，当链接器为或时，目标 将被添加为链接依赖项，何时 为链接器。`Clang``AppleClang``CXX``libCXX_Intel``Intel``CXX``C``Clang``AppleClang``libC_Clang``libC_Intel``Intel``C`有关此生成器表达式的使用的限制，请参阅[与相关的注释。](https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html#constraints-link-language-generator-expression) `$<LINK_LANGUAGE:language>`

#### [链接功能](https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html#id26)

- **$<LINK_LIBRARY:feature,library-list>**

  *版本 3.24 中的新功能。*指定一组库以链接到目标，以及`feature` 提供有关*如何*链接它们的详细信息的库。例如：`add_library(lib1 STATIC ...) add_library(lib2 ...) target_link_libraries(lib2 PRIVATE "$<LINK_LIBRARY:WHOLE_ARCHIVE,lib1>") `这指定了在这样做时`lib2`应该链接到`lib1`并使用该 功能。`WHOLE_ARCHIVE`功能名称区分大小写，只能包含字母、数字和下划线。以全大写形式定义的功能名称是为 CMake 自己的内置功能保留的。预定义的内置库功能包括：`DEFAULT`此功能对应于标准链接，本质上等同于完全不使用任何功能。它通常只与 [`LINK_LIBRARY_OVERRIDE`](https://cmake.org/cmake/help/latest/prop_tgt/LINK_LIBRARY_OVERRIDE.html#prop_tgt:LINK_LIBRARY_OVERRIDE)和 [`LINK_LIBRARY_OVERRIDE_`](https://cmake.org/cmake/help/latest/prop_tgt/LINK_LIBRARY_OVERRIDE_LIBRARY.html#prop_tgt:LINK_LIBRARY_OVERRIDE_)目标属性。`WHOLE_ARCHIVE`强制包含静态库的所有成员。仅以下平台支持此功能，但有上述限制：Linux。所有 BSD 变体。太阳操作系统。所有 Apple 变体。库必须指定为 CMake 目标名称、库文件名（例如`libfoo.a`）或库文件路径（例如 `/path/to/libfoo.a`）。由于 Apple 链接器的限制，不能将其指定为普通库名称，例如`foo`，其中`foo` 不是 CMake 目标。视窗。使用 MSVC 或类似 MSVC 的工具链时，MSVC 版本必须大于 1900。赛格温。MSYS。`FRAMEWORK`此选项告诉链接器使用链接器选项搜索指定的框架`-framework`。它只能在 Apple 平台上使用，并且只能与理解所用选项的链接器一起使用（即 Xcode 提供的链接器，或与之兼容的链接器）。可以将框架指定为 CMake 框架目标、裸框架名称或文件路径。如果给出了目标，则该目标必须具有 [`FRAMEWORK`](https://cmake.org/cmake/help/latest/prop_tgt/FRAMEWORK.html#prop_tgt:FRAMEWORK)目标属性设置为真。对于文件路径，如果它包含目录部分，则该目录将被添加为框架搜索路径。`add_library(lib SHARED ...) target_link_libraries(lib PRIVATE "$<LINK_LIBRARY:FRAMEWORK,/path/to/my_framework>") # The constructed linker command line will contain: #   -F/path/to -framework my_framework `文件路径必须符合以下模式之一（`*`是通配符，可选部分显示为`[...]`）：`[/path/to/]FwName[.framework]``[/path/to/]FwName.framework/FwName``[/path/to/]FwName.framework/Versions/*/FwName`请注意，即使不使用`$<LINK_LIBRARY:FRAMEWORK,...>`表达式，CMake 也会识别并自动处理框架目标。如果项目想要明确说明生成器表达式，仍然可以将其与 CMake 目标一起使用，但不是必须这样做。链接器命令行与是否使用生成器表达式可能存在一些差异，但最终结果应该是相同的。另一方面，如果给出了文件路径，CMake 会自动识别一些路径，但不是所有情况。该项目可能希望使用 `$<LINK_LIBRARY:FRAMEWORK,...>`文件路径，以便明确预期的行为。`NEEDED_FRAMEWORK`这类似于该`FRAMEWORK`功能，除了它强制链接器与框架链接，即使它没有使用任何符号。它使用该`-needed_framework`选项并具有与 `FRAMEWORK`.`REEXPORT_FRAMEWORK`这类似于该`FRAMEWORK`功能，除了它告诉链接器该框架应该可供链接到正在创建的库的客户端使用。它使用该`-reexport_framework`选项并具有与`FRAMEWORK`.`WEAK_FRAMEWORK`这类似于该`FRAMEWORK`功能，除了它强制链接器将框架和对它的所有引用标记为弱导入。它使用该`-weak_framework`选项并具有与 `FRAMEWORK`.`NEEDED_LIBRARY`这类似于该`NEEDED_FRAMEWORK`功能，除了它用于非框架目标或库（仅限 Apple 平台）。它酌情使用`-needed_library`or`-needed-l`选项，并具有与`NEEDED_FRAMEWORK`.`REEXPORT_LIBRARY`这类似于该`REEXPORT_FRAMEWORK`功能，除了它用于非框架目标或库（仅限 Apple 平台）。它酌情使用`-reexport_library`or`-reexport-l`选项，并具有与`REEXPORT_FRAMEWORK`.`WEAK_LIBRARY`这类似于该`WEAK_FRAMEWORK`功能，除了它用于非框架目标或库（仅限 Apple 平台）。它酌情使用`-weak_library`or`-weak-l`选项，并具有与`WEAK_FRAMEWORK`.内置和自定义库功能根据以下变量定义：[`CMAKE__LINK_LIBRARY_USING__SUPPORTED`](https://cmake.org/cmake/help/latest/variable/CMAKE_LANG_LINK_LIBRARY_USING_FEATURE_SUPPORTED.html#variable:CMAKE__LINK_LIBRARY_USING__SUPPORTED)[`CMAKE__LINK_LIBRARY_USING_`](https://cmake.org/cmake/help/latest/variable/CMAKE_LANG_LINK_LIBRARY_USING_FEATURE.html#variable:CMAKE__LINK_LIBRARY_USING_)[`CMAKE_LINK_LIBRARY_USING__SUPPORTED`](https://cmake.org/cmake/help/latest/variable/CMAKE_LINK_LIBRARY_USING_FEATURE_SUPPORTED.html#variable:CMAKE_LINK_LIBRARY_USING__SUPPORTED)[`CMAKE_LINK_LIBRARY_USING_`](https://cmake.org/cmake/help/latest/variable/CMAKE_LINK_LIBRARY_USING_FEATURE.html#variable:CMAKE_LINK_LIBRARY_USING_)用于每个变量的值是在创建目标的目录范围末尾设置的值。用法如下：如果语言特定 [`CMAKE__LINK_LIBRARY_USING__SUPPORTED`](https://cmake.org/cmake/help/latest/variable/CMAKE_LANG_LINK_LIBRARY_USING_FEATURE_SUPPORTED.html#variable:CMAKE__LINK_LIBRARY_USING__SUPPORTED)变量为真，`feature`必须由对应的定义 [`CMAKE__LINK_LIBRARY_USING_`](https://cmake.org/cmake/help/latest/variable/CMAKE_LANG_LINK_LIBRARY_USING_FEATURE.html#variable:CMAKE__LINK_LIBRARY_USING_)多变的。如果不`feature`支持特定语言，则 [`CMAKE_LINK_LIBRARY_USING__SUPPORTED`](https://cmake.org/cmake/help/latest/variable/CMAKE_LINK_LIBRARY_USING_FEATURE_SUPPORTED.html#variable:CMAKE_LINK_LIBRARY_USING__SUPPORTED)变量必须为真并且`feature`必须由相应的定义 [`CMAKE_LINK_LIBRARY_USING_`](https://cmake.org/cmake/help/latest/variable/CMAKE_LINK_LIBRARY_USING_FEATURE.html#variable:CMAKE_LINK_LIBRARY_USING_)多变的。应注意以下限制：`library-list`可以指定 CMake 目标或库。任何[OBJECT](https://cmake.org/cmake/help/latest/manual/cmake-buildsystem.7.html#object-libraries) 或[INTERFACE](https://cmake.org/cmake/help/latest/manual/cmake-buildsystem.7.html#interface-libraries)类型的 CMake 目标都将忽略表达式的特征方面，而是以标准方式链接。生成器`$<LINK_LIBRARY:...>`表达式只能用于指定链接库。实际上，这意味着它可以出现在 [`LINK_LIBRARIES`](https://cmake.org/cmake/help/latest/prop_tgt/LINK_LIBRARIES.html#prop_tgt:LINK_LIBRARIES), [`INTERFACE_LINK_LIBRARIES`](https://cmake.org/cmake/help/latest/prop_tgt/INTERFACE_LINK_LIBRARIES.html#prop_tgt:INTERFACE_LINK_LIBRARIES)， 和 [`INTERFACE_LINK_LIBRARIES_DIRECT`](https://cmake.org/cmake/help/latest/prop_tgt/INTERFACE_LINK_LIBRARIES_DIRECT.html#prop_tgt:INTERFACE_LINK_LIBRARIES_DIRECT) 目标属性，并在[`target_link_libraries()`](https://cmake.org/cmake/help/latest/command/target_link_libraries.html#command:target_link_libraries)和[`link_libraries()`](https://cmake.org/cmake/help/latest/command/link_libraries.html#command:link_libraries) 命令。如果`$<LINK_LIBRARY:...>`生成器表达式出现在 [`INTERFACE_LINK_LIBRARIES`](https://cmake.org/cmake/help/latest/prop_tgt/INTERFACE_LINK_LIBRARIES.html#prop_tgt:INTERFACE_LINK_LIBRARIES)目标的属性，它将包含在由 a 生成的导入目标中[`install(EXPORT)`](https://cmake.org/cmake/help/latest/command/install.html#command:install) 命令。使用此导入的环境有责任定义此表达式使用的链接功能。链接步骤中涉及的每个目标或库最多只能具有一种库功能。缺少一个功能也与所有其他功能不兼容。例如：`add_library(lib1 ...) add_library(lib2 ...) add_library(lib3 ...) # lib1 will be associated with feature1 target_link_libraries(lib2 PUBLIC "$<LINK_LIBRARY:feature1,lib1>") # lib1 is being linked with no feature here. This conflicts with the # use of feature1 in the line above and would result in an error. target_link_libraries(lib3 PRIVATE lib1 lib2) `在给定目标或库的整个构建过程中无法使用相同功能的情况下，[`LINK_LIBRARY_OVERRIDE`](https://cmake.org/cmake/help/latest/prop_tgt/LINK_LIBRARY_OVERRIDE.html#prop_tgt:LINK_LIBRARY_OVERRIDE)和 [`LINK_LIBRARY_OVERRIDE_`](https://cmake.org/cmake/help/latest/prop_tgt/LINK_LIBRARY_OVERRIDE_LIBRARY.html#prop_tgt:LINK_LIBRARY_OVERRIDE_)目标属性可用于解决此类不兼容问题。生成器`$<LINK_LIBRARY:...>`表达式不保证指定目标和库的列表将保持组合在一起。要管理GNU链接器支持的`--start-group`和之类的结构，请使用`--end-group``ld`[`LINK_GROUP`](https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html#genex:LINK_GROUP) 而是生成器表达式。

- **$<LINK_GROUP:feature,library-list>**

  *版本 3.24 中的新功能。*指定一组库以链接到目标，以及`feature` 定义该组应如何链接的库。例如：`add_library(lib1 STATIC ...) add_library(lib2 ...) target_link_libraries(lib2 PRIVATE "$<LINK_GROUP:RESCAN,lib1,external>") `这指定`lib2`应该链接到`lib1`和`external`，并且这两个库都应该根据`RESCAN`功能的定义包含在链接器命令行中。功能名称区分大小写，只能包含字母、数字和下划线。以全大写形式定义的功能名称是为 CMake 自己的内置功能保留的。目前，只有一个预定义的内置组功能：`RESCAN`一些链接器仅是单通道的。对于此类链接器，库之间的循环引用通常会导致未解析的符号。此功能指示链接器重复搜索指定的静态库，直到没有创建新的未定义引用。通常，静态库仅按照命令行中指定的顺序搜索一次。如果需要该库中的符号来解析稍后出现在命令行上的库中的对象所引用的未定义符号，则链接器将无法解析该引用。通过将静态库与该`RESCAN` 功能分组，它们将被重复搜索，直到所有可能的引用都得到解决。这将使用链接器选项，如`--start-group`和 `--end-group`，或在 SunOS 上，和。`-z rescan-start``-z rescan-end`使用此功能会带来显着的性能成本。最好仅在两个或多个静态库之间存在不可避免的循环引用时才使用它。此功能在使用针对 Linux、BSD 和 SunOS 的工具链时可用。如果使用 GNU 工具链，它也可以在面向 Windows 平台时使用。内置和自定义组功能根据以下变量定义：[`CMAKE__LINK_GROUP_USING__SUPPORTED`](https://cmake.org/cmake/help/latest/variable/CMAKE_LANG_LINK_GROUP_USING_FEATURE_SUPPORTED.html#variable:CMAKE__LINK_GROUP_USING__SUPPORTED)[`CMAKE__LINK_GROUP_USING_`](https://cmake.org/cmake/help/latest/variable/CMAKE_LANG_LINK_GROUP_USING_FEATURE.html#variable:CMAKE__LINK_GROUP_USING_)[`CMAKE_LINK_GROUP_USING__SUPPORTED`](https://cmake.org/cmake/help/latest/variable/CMAKE_LINK_GROUP_USING_FEATURE_SUPPORTED.html#variable:CMAKE_LINK_GROUP_USING__SUPPORTED)[`CMAKE_LINK_GROUP_USING_`](https://cmake.org/cmake/help/latest/variable/CMAKE_LINK_GROUP_USING_FEATURE.html#variable:CMAKE_LINK_GROUP_USING_)用于每个变量的值是在创建目标的目录范围末尾设置的值。用法如下：如果语言特定 [`CMAKE__LINK_GROUP_USING__SUPPORTED`](https://cmake.org/cmake/help/latest/variable/CMAKE_LANG_LINK_GROUP_USING_FEATURE_SUPPORTED.html#variable:CMAKE__LINK_GROUP_USING__SUPPORTED)变量为真，`feature`必须由对应的定义 [`CMAKE__LINK_GROUP_USING_`](https://cmake.org/cmake/help/latest/variable/CMAKE_LANG_LINK_GROUP_USING_FEATURE.html#variable:CMAKE__LINK_GROUP_USING_)多变的。如果不`feature`支持特定语言，则 [`CMAKE_LINK_GROUP_USING__SUPPORTED`](https://cmake.org/cmake/help/latest/variable/CMAKE_LINK_GROUP_USING_FEATURE_SUPPORTED.html#variable:CMAKE_LINK_GROUP_USING__SUPPORTED)变量必须为真并且`feature`必须由相应的定义 [`CMAKE_LINK_GROUP_USING_`](https://cmake.org/cmake/help/latest/variable/CMAKE_LINK_GROUP_USING_FEATURE.html#variable:CMAKE_LINK_GROUP_USING_)多变的。生成器`LINK_GROUP`表达式与 [`LINK_LIBRARY`](https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html#genex:LINK_LIBRARY)生成器表达式。组中涉及的库可以使用[`LINK_LIBRARY`](https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html#genex:LINK_LIBRARY)生成器表达式。链接步骤中涉及的每个目标或外部库都允许成为多个组的一部分，但前提是所有涉及的组都指定相同的`feature`. 此类组不会在链接器命令行上合并，仍将保留各个组。禁止为同一个目标或库混合不同的组特征。`add_library(lib1 ...) add_library(lib2 ...) add_library(lib3 ...) add_library(lib4 ...) add_library(lib5 ...) target_link_libraries(lib3 PUBLIC  "$<LINK_GROUP:feature1,lib1,lib2>") target_link_libraries(lib4 PRIVATE "$<LINK_GROUP:feature1,lib1,lib3>") # lib4 will be linked with the groups {lib1,lib2} and {lib1,lib3}. # Both groups specify the same feature, so this is fine. target_link_libraries(lib5 PRIVATE "$<LINK_GROUP:feature2,lib1,lib3>") # An error will be raised here because both lib1 and lib3 are part of two # groups with different features. `当链接步骤中涉及目标或外部库作为组的一部分且不属于任何组时，非组链接项的任何出现都将被其所属的组替换。`add_library(lib1 ...) add_library(lib2 ...) add_library(lib3 ...) add_library(lib4 ...) target_link_libraries(lib3 PUBLIC lib1) target_link_libraries(lib4 PRIVATE lib3 "$<LINK_GROUP:feature1,lib1,lib2>") # lib4 will only be linked with lib3 and the group {lib1,lib2} `因为`lib1`是为定义的组的一部分，所以`lib4`该组然后被应用回使用`lib1`for `lib3`。最终结果将好像链接关系`lib3`已被指定为：`target_link_libraries(lib3 PUBLIC "$<LINK_GROUP:feature1,lib1,lib2>") `请注意，组优先于非组链接项可能会导致组之间的循环依赖关系。如果发生这种情况，则会引发致命错误，因为组不允许循环依赖。`add_library(lib1A ...) add_library(lib1B ...) add_library(lib2A ...) add_library(lib2B ...) add_library(lib3 ...) # Non-group linking relationships, these are non-circular so far target_link_libraries(lib1A PUBLIC lib2A) target_link_libraries(lib2B PUBLIC lib1B) # The addition of these groups creates circular dependencies target_link_libraries(lib3 PRIVATE  "$<LINK_GROUP:feat,lib1A,lib1B>"  "$<LINK_GROUP:feat,lib2A,lib2B>" ) `由于为 定义的组，和`lib3`的链接关系 有效地扩展为等效于：`lib1A``lib2B``target_link_libraries(lib1A PUBLIC "$<LINK_GROUP:feat,lib2A,lib2B>") target_link_libraries(lib2B PUBLIC "$<LINK_GROUP:feat,lib1A,lib1B>") `这会在组之间创建循环依赖： .`lib1A --> lib2B --> lib1A`还应注意以下限制：`library-list`可以指定 CMake 目标或库。任何[OBJECT](https://cmake.org/cmake/help/latest/manual/cmake-buildsystem.7.html#object-libraries) 或[INTERFACE](https://cmake.org/cmake/help/latest/manual/cmake-buildsystem.7.html#interface-libraries)类型的 CMake 目标都将忽略表达式的特征方面，而是以标准方式链接。生成器`$<LINK_GROUP:...>`表达式只能用于指定链接库。实际上，这意味着它可以出现在 [`LINK_LIBRARIES`](https://cmake.org/cmake/help/latest/prop_tgt/LINK_LIBRARIES.html#prop_tgt:LINK_LIBRARIES), [`INTERFACE_LINK_LIBRARIES`](https://cmake.org/cmake/help/latest/prop_tgt/INTERFACE_LINK_LIBRARIES.html#prop_tgt:INTERFACE_LINK_LIBRARIES)，和 [`INTERFACE_LINK_LIBRARIES_DIRECT`](https://cmake.org/cmake/help/latest/prop_tgt/INTERFACE_LINK_LIBRARIES_DIRECT.html#prop_tgt:INTERFACE_LINK_LIBRARIES_DIRECT)目标属性，并在[`target_link_libraries()`](https://cmake.org/cmake/help/latest/command/target_link_libraries.html#command:target_link_libraries)和[`link_libraries()`](https://cmake.org/cmake/help/latest/command/link_libraries.html#command:link_libraries) 命令。如果`$<LINK_GROUP:...>`生成器表达式出现在 [`INTERFACE_LINK_LIBRARIES`](https://cmake.org/cmake/help/latest/prop_tgt/INTERFACE_LINK_LIBRARIES.html#prop_tgt:INTERFACE_LINK_LIBRARIES)目标的属性，它将包含在由 a 生成的导入目标中[`install(EXPORT)`](https://cmake.org/cmake/help/latest/command/install.html#command:install) 命令。使用此导入的环境有责任定义此表达式使用的链接功能。

#### [链接上下文](https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html#id27)

- **$<LINK_ONLY:...>**

  *3.1 版中的新功能。*的内容`...`，除了在收集[Transitive Usage Requirements](https://cmake.org/cmake/help/latest/manual/cmake-buildsystem.7.html#target-usage-requirements)时，在这种情况下它是空字符串。这是用于在一个 [`INTERFACE_LINK_LIBRARIES`](https://cmake.org/cmake/help/latest/prop_tgt/INTERFACE_LINK_LIBRARIES.html#prop_tgt:INTERFACE_LINK_LIBRARIES)目标属性，通常通过[`target_link_libraries()`](https://cmake.org/cmake/help/latest/command/target_link_libraries.html#command:target_link_libraries)命令，在没有其他使用要求的情况下指定私有链接依赖项。*3.24 版中的新功能：*`LINK_ONLY`也可用于[`LINK_LIBRARIES`](https://cmake.org/cmake/help/latest/prop_tgt/LINK_LIBRARIES.html#prop_tgt:LINK_LIBRARIES)目标财产。查看政策[`CMP0131`](https://cmake.org/cmake/help/latest/policy/CMP0131.html#policy:CMP0131).

- **$<DEVICE_LINK:list>**

  *3.18 版中的新功能。*如果是设备链接步骤，则返回列表，否则返回空列表。设备链接步骤由[`CUDA_SEPARABLE_COMPILATION`](https://cmake.org/cmake/help/latest/prop_tgt/CUDA_SEPARABLE_COMPILATION.html#prop_tgt:CUDA_SEPARABLE_COMPILATION) 和[`CUDA_RESOLVE_DEVICE_SYMBOLS`](https://cmake.org/cmake/help/latest/prop_tgt/CUDA_RESOLVE_DEVICE_SYMBOLS.html#prop_tgt:CUDA_RESOLVE_DEVICE_SYMBOLS)属性和政策[`CMP0105`](https://cmake.org/cmake/help/latest/policy/CMP0105.html#policy:CMP0105). 此表达式只能用于指定链接选项。

- **$<HOST_LINK:list>**

  *3.18 版中的新功能。*如果是正常链接步骤，则返回列表，否则返回空列表。当还涉及设备链接步骤时，此表达式主要有用（请参阅[`$`](https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html#genex:DEVICE_LINK)生成器表达式）。此表达式只能用于指定链接选项。



### [目标相关表达式](https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html#id28)

这些查询引用一个目标`tgt`。除非另有说明，否则这可以是任何运行时工件，即：

- 由创建的可执行目标[`add_executable()`](https://cmake.org/cmake/help/latest/command/add_executable.html#command:add_executable).
- 由创建的共享库目标（`.so`，`.dll`但不是它们的`.lib`导入库）[`add_library()`](https://cmake.org/cmake/help/latest/command/add_library.html#command:add_library).
- 由创建的静态库目标[`add_library()`](https://cmake.org/cmake/help/latest/command/add_library.html#command:add_library).

在下文中，短语“`tgt`文件名”表示 `tgt`二进制文件的名称。这必须与短语“目标名称”区分开来，后者只是字符串`tgt`。

- **$<TARGET_EXISTS:tgt>**

  *版本 3.12 中的新功能。*`1`如果`tgt`作为 CMake 目标存在，则为`0`.

- **$<TARGET_NAME_IF_EXISTS:tgt>**

  *版本 3.12 中的新功能。*如果目标存在，则为目标名称`tgt`，否则为空字符串。请注意，`tgt`它不会作为评估此表达式的目标的依赖项添加。

- **$<TARGET_NAME:...>**

  标记`...`为目标的名称。如果将目标导出到多个从属导出集，则需要这样做。`...`必须是目标的文字名称，它可能不包含生成器表达式。

- **$<TARGET_PROPERTY:tgt,prop>**

  `prop`目标上的属性值`tgt`。请注意，`tgt`它不会作为评估此表达式的目标的依赖项添加。

- **$<TARGET_PROPERTY:prop>**

  `prop`正在评估表达式的目标上的属性值。请注意，对于 [Transitive Usage Requirements](https://cmake.org/cmake/help/latest/manual/cmake-buildsystem.7.html#target-usage-requirements)中的生成器表达式，这是消费目标，而不是指定需求的目标。

- **$<TARGET_OBJECTS:tgt>**

  *3.1 版中的新功能。*由 building 产生的对象列表`tgt`。这通常用于[对象库](https://cmake.org/cmake/help/latest/manual/cmake-buildsystem.7.html#object-libraries)目标。

- **$<TARGET_POLICY:policy>**

  `1`如果`policy`是`NEW`在创建“头”目标时，则为`0`。如果`policy`未设置，将发出该策略的警告消息。此生成器表达式仅适用于策略子集。

- **$<TARGET_FILE:tgt>**

  `tgt`二进制文件的完整路径。请注意，`tgt`它不会作为评估此表达式的目标的依赖项添加，除非该表达式正在用于 [`add_custom_command()`](https://cmake.org/cmake/help/latest/command/add_custom_command.html#command:add_custom_command)或者[`add_custom_target()`](https://cmake.org/cmake/help/latest/command/add_custom_target.html#command:add_custom_target).

- **$<TARGET_FILE_BASE_NAME:tgt>**

  *3.15 版中的新功能。*的基本名称`tgt`，即`$<TARGET_FILE_NAME:tgt>`不带前缀和后缀。例如，如果`tgt`文件名是`libbase.so`，则基本名称是`base`.另见[`OUTPUT_NAME`](https://cmake.org/cmake/help/latest/prop_tgt/OUTPUT_NAME.html#prop_tgt:OUTPUT_NAME), [`ARCHIVE_OUTPUT_NAME`](https://cmake.org/cmake/help/latest/prop_tgt/ARCHIVE_OUTPUT_NAME.html#prop_tgt:ARCHIVE_OUTPUT_NAME), [`LIBRARY_OUTPUT_NAME`](https://cmake.org/cmake/help/latest/prop_tgt/LIBRARY_OUTPUT_NAME.html#prop_tgt:LIBRARY_OUTPUT_NAME)和[`RUNTIME_OUTPUT_NAME`](https://cmake.org/cmake/help/latest/prop_tgt/RUNTIME_OUTPUT_NAME.html#prop_tgt:RUNTIME_OUTPUT_NAME) 目标属性及其配置特定变体 [`OUTPUT_NAME_`](https://cmake.org/cmake/help/latest/prop_tgt/OUTPUT_NAME_CONFIG.html#prop_tgt:OUTPUT_NAME_),[`ARCHIVE_OUTPUT_NAME_`](https://cmake.org/cmake/help/latest/prop_tgt/ARCHIVE_OUTPUT_NAME_CONFIG.html#prop_tgt:ARCHIVE_OUTPUT_NAME_), [`LIBRARY_OUTPUT_NAME_`](https://cmake.org/cmake/help/latest/prop_tgt/LIBRARY_OUTPUT_NAME_CONFIG.html#prop_tgt:LIBRARY_OUTPUT_NAME_)和 [`RUNTIME_OUTPUT_NAME_`](https://cmake.org/cmake/help/latest/prop_tgt/RUNTIME_OUTPUT_NAME_CONFIG.html#prop_tgt:RUNTIME_OUTPUT_NAME_).这[`_POSTFIX`](https://cmake.org/cmake/help/latest/prop_tgt/CONFIG_POSTFIX.html#prop_tgt:_POSTFIX)和[`DEBUG_POSTFIX`](https://cmake.org/cmake/help/latest/prop_tgt/DEBUG_POSTFIX.html#prop_tgt:DEBUG_POSTFIX)也可以考虑目标属性。请注意，`tgt`它不会作为评估此表达式的目标的依赖项添加。

- **$<TARGET_FILE_PREFIX:tgt>**

  *3.15 版中的新功能。*文件名的前缀`tgt`（例如`lib`）。另见[`PREFIX`](https://cmake.org/cmake/help/latest/prop_tgt/PREFIX.html#prop_tgt:PREFIX)目标财产。请注意，`tgt`它不会作为评估此表达式的目标的依赖项添加。

- **$<TARGET_FILE_SUFFIX:tgt>**

  *3.15 版中的新功能。*文件名的后缀`tgt`（扩展名，例如`.so`or `.exe`）。另见[`SUFFIX`](https://cmake.org/cmake/help/latest/prop_tgt/SUFFIX.html#prop_tgt:SUFFIX)目标财产。请注意，`tgt`它不会作为评估此表达式的目标的依赖项添加。

- **$<TARGET_FILE_NAME:tgt>**

  `tgt`文件名。请注意，`tgt`它不会作为评估此表达式的目标的依赖项添加（请参阅策略[`CMP0112`](https://cmake.org/cmake/help/latest/policy/CMP0112.html#policy:CMP0112)).

- **$<TARGET_FILE_DIR:tgt>**

  `tgt`二进制文件的目录。请注意，`tgt`它不会作为评估此表达式的目标的依赖项添加（请参阅策略[`CMP0112`](https://cmake.org/cmake/help/latest/policy/CMP0112.html#policy:CMP0112)).

- **$<TARGET_LINKER_FILE:tgt>**

  链接到`tgt`目标时使用的文件。这通常是`tgt`表示 ( `.a`, `.lib`, `.so`) 的库，但对于 DLL 平台上的共享库，它将是`.lib` 与 DLL 关联的导入库。

- **$<TARGET_LINKER_FILE_BASE_NAME:tgt>**

  *3.15 版中的新功能。*用于链接目标的文件的基本名称`tgt`，即 `$<TARGET_LINKER_FILE_NAME:tgt>`不带前缀和后缀。例如，如果目标文件名为`libbase.a`，则基本名称为`base`.另见[`OUTPUT_NAME`](https://cmake.org/cmake/help/latest/prop_tgt/OUTPUT_NAME.html#prop_tgt:OUTPUT_NAME), [`ARCHIVE_OUTPUT_NAME`](https://cmake.org/cmake/help/latest/prop_tgt/ARCHIVE_OUTPUT_NAME.html#prop_tgt:ARCHIVE_OUTPUT_NAME)， 和[`LIBRARY_OUTPUT_NAME`](https://cmake.org/cmake/help/latest/prop_tgt/LIBRARY_OUTPUT_NAME.html#prop_tgt:LIBRARY_OUTPUT_NAME)目标属性及其配置特定变体[`OUTPUT_NAME_`](https://cmake.org/cmake/help/latest/prop_tgt/OUTPUT_NAME_CONFIG.html#prop_tgt:OUTPUT_NAME_), [`ARCHIVE_OUTPUT_NAME_`](https://cmake.org/cmake/help/latest/prop_tgt/ARCHIVE_OUTPUT_NAME_CONFIG.html#prop_tgt:ARCHIVE_OUTPUT_NAME_)和 [`LIBRARY_OUTPUT_NAME_`](https://cmake.org/cmake/help/latest/prop_tgt/LIBRARY_OUTPUT_NAME_CONFIG.html#prop_tgt:LIBRARY_OUTPUT_NAME_).这[`_POSTFIX`](https://cmake.org/cmake/help/latest/prop_tgt/CONFIG_POSTFIX.html#prop_tgt:_POSTFIX)和[`DEBUG_POSTFIX`](https://cmake.org/cmake/help/latest/prop_tgt/DEBUG_POSTFIX.html#prop_tgt:DEBUG_POSTFIX)也可以考虑目标属性。请注意，`tgt`它不会作为评估此表达式的目标的依赖项添加。

- **$<TARGET_LINKER_FILE_PREFIX:tgt>**

  *3.15 版中的新功能。*用于链接目标的文件的前缀`tgt`。另见[`PREFIX`](https://cmake.org/cmake/help/latest/prop_tgt/PREFIX.html#prop_tgt:PREFIX)和[`IMPORT_PREFIX`](https://cmake.org/cmake/help/latest/prop_tgt/IMPORT_PREFIX.html#prop_tgt:IMPORT_PREFIX)目标属性。请注意，`tgt`它不会作为评估此表达式的目标的依赖项添加。

- **$<TARGET_LINKER_FILE_SUFFIX:tgt>**

  *3.15 版中的新功能。*用于链接的文件的后缀 where`tgt`是目标的名称。后缀对应于文件扩展名（例如“.so”或“.lib”）。另见[`SUFFIX`](https://cmake.org/cmake/help/latest/prop_tgt/SUFFIX.html#prop_tgt:SUFFIX)和[`IMPORT_SUFFIX`](https://cmake.org/cmake/help/latest/prop_tgt/IMPORT_SUFFIX.html#prop_tgt:IMPORT_SUFFIX)目标属性。请注意，`tgt`它不会作为评估此表达式的目标的依赖项添加。

- **$<TARGET_LINKER_FILE_NAME:tgt>**

  用于链接目标的文件名`tgt`。请注意，`tgt`它不会作为评估此表达式的目标的依赖项添加（请参阅策略[`CMP0112`](https://cmake.org/cmake/help/latest/policy/CMP0112.html#policy:CMP0112)).

- **$<TARGET_LINKER_FILE_DIR:tgt>**

  用于链接目标的文件目录`tgt`。请注意，`tgt`它不会作为评估此表达式的目标的依赖项添加（请参阅策略[`CMP0112`](https://cmake.org/cmake/help/latest/policy/CMP0112.html#policy:CMP0112)).

- **$<TARGET_SONAME_FILE:tgt>**

  带有 soname ( `.so.3`) 的文件，其中`tgt`是目标的名称。

- **$<TARGET_SONAME_FILE_NAME:tgt>**

  带有 soname ( `.so.3`) 的文件名。请注意，`tgt`它不会作为评估此表达式的目标的依赖项添加（请参阅策略[`CMP0112`](https://cmake.org/cmake/help/latest/policy/CMP0112.html#policy:CMP0112)).

- **$<TARGET_SONAME_FILE_DIR:tgt>**

  带有 soname ( `.so.3`) 的目录。请注意，`tgt`它不会作为评估此表达式的目标的依赖项添加（请参阅策略[`CMP0112`](https://cmake.org/cmake/help/latest/policy/CMP0112.html#policy:CMP0112)).

- **$<TARGET_PDB_FILE:tgt>**

  *3.1 版中的新功能。*链接器生成的程序数据库文件 (.pdb) 的完整路径，其中`tgt`是目标的名称。另见[`PDB_NAME`](https://cmake.org/cmake/help/latest/prop_tgt/PDB_NAME.html#prop_tgt:PDB_NAME)和[`PDB_OUTPUT_DIRECTORY`](https://cmake.org/cmake/help/latest/prop_tgt/PDB_OUTPUT_DIRECTORY.html#prop_tgt:PDB_OUTPUT_DIRECTORY) 目标属性及其配置特定变体 [`PDB_NAME_`](https://cmake.org/cmake/help/latest/prop_tgt/PDB_NAME_CONFIG.html#prop_tgt:PDB_NAME_)和[`PDB_OUTPUT_DIRECTORY_`](https://cmake.org/cmake/help/latest/prop_tgt/PDB_OUTPUT_DIRECTORY_CONFIG.html#prop_tgt:PDB_OUTPUT_DIRECTORY_).

- **$<TARGET_PDB_FILE_BASE_NAME:tgt>**

  *3.15 版中的新功能。*链接器生成的程序数据库文件 (.pdb) 的基本名称，其中`tgt`是目标的名称。基本名称对应于 `$<TARGET_PDB_FILE_NAME:tgt>`不带前缀和后缀的目标 PDB 文件名（请参阅 参考资料）。例如，如果目标文件名为`base.pdb`，则基本名称为`base`.另见[`PDB_NAME`](https://cmake.org/cmake/help/latest/prop_tgt/PDB_NAME.html#prop_tgt:PDB_NAME)目标属性及其配置特定变体[`PDB_NAME_`](https://cmake.org/cmake/help/latest/prop_tgt/PDB_NAME_CONFIG.html#prop_tgt:PDB_NAME_).这[`_POSTFIX`](https://cmake.org/cmake/help/latest/prop_tgt/CONFIG_POSTFIX.html#prop_tgt:_POSTFIX)和[`DEBUG_POSTFIX`](https://cmake.org/cmake/help/latest/prop_tgt/DEBUG_POSTFIX.html#prop_tgt:DEBUG_POSTFIX)也可以考虑目标属性。请注意，`tgt`它不会作为评估此表达式的目标的依赖项添加。

- **$<TARGET_PDB_FILE_NAME:tgt>**

  *3.1 版中的新功能。*链接器生成的程序数据库文件 (.pdb) 的名称。请注意，`tgt`它不会作为评估此表达式的目标的依赖项添加（请参阅策略[`CMP0112`](https://cmake.org/cmake/help/latest/policy/CMP0112.html#policy:CMP0112)).

- **$<TARGET_PDB_FILE_DIR:tgt>**

  *3.1 版中的新功能。*链接器生成的程序数据库文件 (.pdb) 的目录。请注意，`tgt`它不会作为评估此表达式的目标的依赖项添加（请参阅策略[`CMP0112`](https://cmake.org/cmake/help/latest/policy/CMP0112.html#policy:CMP0112)).

- **$<TARGET_BUNDLE_DIR:tgt>**

  *3.9 版中的新功能。*包目录的完整路径（`/path/to/my.app`、 `/path/to/my.framework`或`/path/to/my.bundle`），其中`tgt`是目标的名称。请注意，`tgt`它不会作为评估此表达式的目标的依赖项添加（请参阅策略[`CMP0112`](https://cmake.org/cmake/help/latest/policy/CMP0112.html#policy:CMP0112)).

- **$<TARGET_BUNDLE_DIR_NAME:tgt>**

  *版本 3.24 中的新功能。*包目录的名称（`my.app`、`my.framework`或 `my.bundle`），其中`tgt`是目标的名称。请注意，`tgt`它不会作为评估此表达式的目标的依赖项添加（请参阅策略[`CMP0112`](https://cmake.org/cmake/help/latest/policy/CMP0112.html#policy:CMP0112)).

- **$<TARGET_BUNDLE_CONTENT_DIR:tgt>**

  *3.9 版中的新功能。*包内容目录的完整路径，其中`tgt`是目标的名称。对于 macOS SDK，它会导致`/path/to/my.app/Contents`、 `/path/to/my.framework`或`/path/to/my.bundle/Contents`. 对于所有其他 SDK（例如 iOS），它会导致`/path/to/my.app`、 `/path/to/my.framework`或`/path/to/my.bundle`由于扁平包结构。请注意，`tgt`它不会作为评估此表达式的目标的依赖项添加（请参阅策略[`CMP0112`](https://cmake.org/cmake/help/latest/policy/CMP0112.html#policy:CMP0112)).

- **$<TARGET_RUNTIME_DLLS:tgt>**

  *3.21 版中的新功能。*目标在运行时依赖的 DLL 列表。这是由`SHARED`目标的传递依赖中所有目标的位置决定的。`SHARED`在可执行文件、库和库以外的目标上使用此生成器表达式`MODULE`是错误的。 **在非 DLL 平台上，此表达式的计算结果始终为空字符串**。此生成器表达式可用于将目标依赖的所有 DLL 复制到`POST_BUILD`自定义命令中的输出目录中。例如：`find_package(foo CONFIG REQUIRED) # package generated by install(EXPORT) add_executable(exe main.c) target_link_libraries(exe PRIVATE foo::foo foo::bar) add_custom_command(TARGET exe POST_BUILD  COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:exe> $<TARGET_FILE_DIR:exe>  COMMAND_EXPAND_LISTS ) `笔记 只有知道文件位置的[导入目标](https://cmake.org/cmake/help/latest/manual/cmake-buildsystem.7.html#imported-targets)`.dll`才受支持。导入的`SHARED`库必须具有 [`IMPORTED_LOCATION`](https://cmake.org/cmake/help/latest/prop_tgt/IMPORTED_LOCATION.html#prop_tgt:IMPORTED_LOCATION)设置为其`.dll`文件。有关详细信息，请参阅 [add_library 导入的库](https://cmake.org/cmake/help/latest/command/add_library.html#add-library-imported-libraries) 部分。许多[查找模块](https://cmake.org/cmake/help/latest/manual/cmake-developer.7.html#find-modules)生成具有该类型的导入目标，`UNKNOWN`因此将被忽略。

### [导出和安装表达式](https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html#id29)

- **$<安装接口：...>**

  `...`使用导出属性时的 内容[`install(EXPORT)`](https://cmake.org/cmake/help/latest/command/install.html#command:install)，否则为空。

- **$<BUILD_INTERFACE:...>**

  `...`使用导出属性时的内容[`export()`](https://cmake.org/cmake/help/latest/command/export.html#command:export)，或者当目标被同一构建系统中的另一个目标使用时。否则扩展为空字符串。

- **$<安装前缀>**

  导出目标时的安装前缀内容 [`install(EXPORT)`](https://cmake.org/cmake/help/latest/command/install.html#command:install)，或在评估时 [`INSTALL_NAME_DIR`](https://cmake.org/cmake/help/latest/prop_tgt/INSTALL_NAME_DIR.html#prop_tgt:INSTALL_NAME_DIR)财产或`INSTALL_NAME_DIR`论据 [`install(RUNTIME_DEPENDENCY_SET)`](https://cmake.org/cmake/help/latest/command/install.html#command:install)，否则为空。

### [多级表达式评估](https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html#id30)

- **$<GENEX_EVAL:expr>**

  *版本 3.12 中的新功能。*`expr`在当前上下文中评估为生成器表达式的内容。这使得能够使用生成器表达式，其评估结果本身就是生成器表达式。

- **$<TARGET_GENEX_EVAL:tgt,expr>**

  *版本 3.12 中的新功能。*在目标`expr`上下文中评估为生成器表达式的 内容。`tgt`这允许使用本身包含生成器表达式的自定义目标属性。当您想要管理支持生成器表达式的自定义属性时，具有评估生成器表达式的能力非常有用。例如：`add_library(foo ...) set_property(TARGET foo PROPERTY  CUSTOM_KEYS $<$<CONFIG:DEBUG>:FOO_EXTRA_THINGS> ) add_custom_target(printFooKeys  COMMAND ${CMAKE_COMMAND} -E echo $<TARGET_PROPERTY:foo,CUSTOM_KEYS> ) ``printFooKeys`自定义命令的这种幼稚实现是错误的，因为`CUSTOM_KEYS`未评估目标属性并且内容按原样传递（即`$<$<CONFIG:DEBUG>:FOO_EXTRA_THINGS>`）。要获得预期的结果（即`FOO_EXTRA_THINGS`如果 config 为 `Debug`），则需要评估 的输出 `$<TARGET_PROPERTY:foo,CUSTOM_KEYS>`：`add_custom_target(printFooKeys  COMMAND ${CMAKE_COMMAND} -E    echo $<TARGET_GENEX_EVAL:foo,$<TARGET_PROPERTY:foo,CUSTOM_KEYS>> ) `

### [转义字符](https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html#id31)

这些表达式计算为特定的字符串文字。在需要防止它们具有特殊含义的地方使用它们代替实际的字符串文字。

- **$<角度-R>**

  一个字面量`>`。例如用于比较包含`>`.

- **$<逗号>**

  一个字面量`,`。例如用于比较包含`,`.

- **$<分号>**

  一个字面量`;`。用于防止对带有 的参数进行列表扩展`;`。

### [不推荐使用的表达式](https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html#id32)

- **$<配置>**

  配置名称。自 CMake 3.0 起已弃用。利用[`CONFIG`](https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html#genex:CONFIG)反而。