

# [add_compile_definitions](https://cmake.org/cmake/help/latest/command/add_compile_definitions.html)

*版本 3.12 中的新功能。*

将预处理器定义添加到源文件的编译中。

```cmake
add_compile_definitions(<definition> ...)
```

将预处理器定义添加到编译器命令行。

预处理器定义被添加到[`COMPILE_DEFINITIONS`](https://cmake.org/cmake/help/latest/prop_dir/COMPILE_DEFINITIONS.html#prop_dir:COMPILE_DEFINITIONS) 当前`CMakeLists`文件的目录属性。它们也被添加到[`COMPILE_DEFINITIONS`](https://cmake.org/cmake/help/latest/prop_tgt/COMPILE_DEFINITIONS.html#prop_tgt:COMPILE_DEFINITIONS)`CMakeLists`当前文件中每个目标的目标属性。

`VAR`使用语法或指定定义`VAR=value`。不支持函数样式定义。CMake 将自动为本机构建系统正确转义值（请注意，CMake 语言语法可能需要转义来指定某些值）。

参数 to`add_compile_definitions`可以使用带有语法的“生成器表达式” `$<...>`。见[`cmake-generator-expressions(7)`](https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html#manual:cmake-generator-expressions(7)) 可用表达式的手册。见[`cmake-buildsystem(7)`](https://cmake.org/cmake/help/latest/manual/cmake-buildsystem.7.html#manual:cmake-buildsystem(7)) 有关定义构建系统属性的更多信息。



# [add_compile_options](https://cmake.org/cmake/help/latest/command/add_compile_options.html)

为源文件的编译添加选项。

```cmake
add_compile_options(<option> ...)
```

将选项添加到[`COMPILE_OPTIONS`](https://cmake.org/cmake/help/latest/prop_dir/COMPILE_OPTIONS.html#prop_dir:COMPILE_OPTIONS)目录属性。从当前目录及以下目录编译目标时使用这些选项。

## Arguments

参数 to`add_compile_options`可以使用带有语法的“生成器表达式” `$<...>`。见[`cmake-generator-expressions(7)`](https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html#manual:cmake-generator-expressions(7)) 可用表达式的手册。见[`cmake-buildsystem(7)`](https://cmake.org/cmake/help/latest/manual/cmake-buildsystem.7.html#manual:cmake-buildsystem(7)) 有关定义构建系统属性的更多信息。

## 去重选项

用于目标的最终选项集是通过累积来自当前目标的选项及其依赖项的使用要求来构建的。对选项集进行重复数据删除以避免重复。

*3.12 版中的新功能：*虽然有利于单个选项，但重复数据删除步骤可以分解选项组。例如，变成 。可以使用类似 shell 的引用和前缀来指定一组选项。前缀被删除，其余的选项字符串使用 `-option A -option B` `-option A B` `SHELL:` `SHELL:`[`separate_arguments()`](https://cmake.org/cmake/help/latest/command/separate_arguments.html#command:separate_arguments) `UNIX_COMMAND`模式。例如， 变成。`"SHELL:-option A" "SHELL:-option B"` `-option A -option B`

## Example

由于不同的编译器支持不同的选项，此命令的典型用法是在特定于编译器的条件子句中：

```cmake
if (MSVC)
    # warning level 4 and all warnings as errors
    add_compile_options(/W4 /WX)
else()
    # lots of warnings and all warnings as errors
    add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()
```

## 另见

此命令可用于添加任何选项。但是，为了添加预处理器定义和包含目录，建议使用更具体的命令[`add_compile_definitions()`](https://cmake.org/cmake/help/latest/command/add_compile_definitions.html#command:add_compile_definitions) 和[`include_directories()`](https://cmake.org/cmake/help/latest/command/include_directories.html#command:include_directories).

命令[`target_compile_options()`](https://cmake.org/cmake/help/latest/command/target_compile_options.html#command:target_compile_options)添加特定于目标的选项。

源文件属性[`COMPILE_OPTIONS`](https://cmake.org/cmake/help/latest/prop_sf/COMPILE_OPTIONS.html#prop_sf:COMPILE_OPTIONS)将选项添加到一个源文件。



# [add_custom_command](https://cmake.org/cmake/help/latest/command/add_custom_command.html)

将自定义构建规则添加到生成的构建系统。

有两个主要的签名`add_custom_command`。

## 生成文件

第一个签名用于添加自定义命令以产生输出：

```cmake
add_custom_command(OUTPUT output1 [output2 ...]
                   COMMAND command1 [ARGS] [args1...]
                   [COMMAND command2 [ARGS] [args2...] ...]
                   [MAIN_DEPENDENCY depend]
                   [DEPENDS [depends...]]
                   [BYPRODUCTS [files...]]
                   [IMPLICIT_DEPENDS <lang1> depend1
                                    [<lang2> depend2] ...]
                   [WORKING_DIRECTORY dir]
                   [COMMENT comment]
                   [DEPFILE depfile]
                   [JOB_POOL job_pool]
                   [VERBATIM] [APPEND] [USES_TERMINAL]
                   [COMMAND_EXPAND_LISTS])
```

这定义了一个生成指定`OUTPUT`文件的命令。在同一目录 (`CMakeLists.txt`文件 ) 中创建的将自定义命令的任何输出指定为源文件的目标被赋予在构建时使用该命令生成文件的规则。不要在可能并行构建的多个独立目标中列出输出，否则规则的两个实例可能会发生冲突（而是使用[`add_custom_target()`](https://cmake.org/cmake/help/latest/command/add_custom_target.html#command:add_custom_target)命令来驱动命令并使其他目标依赖于该命令）。在 makefile 术语中，这会以以下形式创建一个新目标：

```cmake
OUTPUT: MAIN_DEPENDENCY DEPENDS
        COMMAND
```

选项包括：

- `APPEND`

  `COMMAND`将and选项值附加`DEPENDS`到指定的第一个输出的自定义命令。必须已经使用相同的输出调用了此命令。如果前一个调用通过生成器表达式指定了输出，则当前调用指定的输出在评估生成器表达式后必须至少匹配一个配置。在这种情况下，附加的命令和依赖项适用于所有配置。给出 APPEND 时，当前会忽略`COMMENT`、`MAIN_DEPENDENCY`和`WORKING_DIRECTORY` 选项，但将来可能会使用。

- `BYPRODUCTS`

  *3.2 版中的新功能。*指定命令预期生成的文件，但其修改时间可能会或可能不会比依赖项更新。如果副产品名称是相对路径，它将相对于与当前源目录对应的构建树目录进行解释。每个副产品文件都将标有[`GENERATED`](https://cmake.org/cmake/help/latest/prop_sf/GENERATED.html#prop_sf:GENERATED) 源文件属性自动。副产品的明确规范由 [`Ninja`](https://cmake.org/cmake/help/latest/generator/Ninja.html#generator:Ninja)生成器告诉`ninja`构建工具如何在副产品丢失时重新生成它们。当其他构建规则（例如自定义命令）依赖于副产品时，它也很有用。Ninja 需要为任何生成的文件建立一个构建规则，即使存在仅订单依赖项，以确保副产品在其依赖项构建之前可用。[Makefile 生成器](https://cmake.org/cmake/help/latest/manual/cmake-generators.7.html#makefile-generators)将删除`BYPRODUCTS`和其他 [`GENERATED`](https://cmake.org/cmake/help/latest/prop_sf/GENERATED.html#prop_sf:GENERATED)期间的文件。`make clean`*3.20 版中的新功能：*参数`BYPRODUCTS`可以使用一组受限的 [`generator expressions`](https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html#manual:cmake-generator-expressions(7)). 不允许[依赖于目标的表达式。](https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html#target-dependent-queries)

- `COMMAND`

  指定要在构建时执行的命令行。如果指定了多个，`COMMAND`它们将按顺序执行，但*不一定*组成有状态的 shell 或批处理脚本。（要运行完整的脚本，请使用[`configure_file()`](https://cmake.org/cmake/help/latest/command/configure_file.html#command:configure_file)命令或 [`file(GENERATE)`](https://cmake.org/cmake/help/latest/command/file.html#command:file)命令来创建它，然后指定 a`COMMAND`来启动它。）可选`ARGS`参数是为了向后兼容，将被忽略。如果`COMMAND`指定一个可执行目标名称（由 [`add_executable()`](https://cmake.org/cmake/help/latest/command/add_executable.html#command:add_executable)命令），如果以下任一情况为真，它将自动替换为构建时创建的可执行文件的位置：目标没有被交叉编译（即 [`CMAKE_CROSSCOMPILING`](https://cmake.org/cmake/help/latest/variable/CMAKE_CROSSCOMPILING.html#variable:CMAKE_CROSSCOMPILING)变量未设置为真）。*3.6 版中*的新功能：正在交叉编译目标并提供了一个模拟器（即它的[`CROSSCOMPILING_EMULATOR`](https://cmake.org/cmake/help/latest/prop_tgt/CROSSCOMPILING_EMULATOR.html#prop_tgt:CROSSCOMPILING_EMULATOR)目标属性已设置）。在这种情况下，内容[`CROSSCOMPILING_EMULATOR`](https://cmake.org/cmake/help/latest/prop_tgt/CROSSCOMPILING_EMULATOR.html#prop_tgt:CROSSCOMPILING_EMULATOR)将在目标可执行文件的位置之前添加到命令中。如果上述条件都不满足，则假定命令名称是`PATH`在构建时要找到的程序。`COMMAND`可以使用 的参数[`generator expressions`](https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html#manual:cmake-generator-expressions(7)). 使用[`TARGET_FILE`](https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html#genex:TARGET_FILE)生成器表达式稍后在命令行中引用目标的位置（即作为命令参数而不是作为要执行的命令）。每当以下基于目标的生成器表达式之一用作要执行的命令或在命令参数中提及时，将自动添加目标级别依赖项，以便在使用此自定义命令的任何目标之前构建所提到的目标（请参阅政策[`CMP0112`](https://cmake.org/cmake/help/latest/policy/CMP0112.html#policy:CMP0112)).`TARGET_FILE``TARGET_LINKER_FILE``TARGET_SONAME_FILE``TARGET_PDB_FILE`此目标级别依赖项不会添加会导致自定义命令在重新编译可执行文件时重新运行的文件级别依赖项。列出目标名称以及`DEPENDS`添加此类文件级依赖项的选项。

- `COMMENT`

  在构建时执行命令之前显示给定的消息。

- `DEPENDS`

  指定命令所依赖的文件。每个参数都转换为依赖项，如下所示：如果参数是目标的名称（由 [`add_custom_target()`](https://cmake.org/cmake/help/latest/command/add_custom_target.html#command:add_custom_target), [`add_executable()`](https://cmake.org/cmake/help/latest/command/add_executable.html#command:add_executable)， 或者 [`add_library()`](https://cmake.org/cmake/help/latest/command/add_library.html#command:add_library)命令）创建目标级别的依赖项，以确保在使用此自定义命令的任何目标之前构建目标。此外，如果目标是可执行文件或库，则会创建文件级依赖项，以便在重新编译目标时重新运行自定义命令。如果参数是绝对路径，则在该路径上创建文件级依赖项。如果参数是已添加到目标或已设置源文件属性的源文件的名称，则在该源文件上创建文件级依赖项。如果参数是相对路径并且它存在于当前源目录中，则在当前源目录中的该文件上创建文件级依赖项。否则，将在相对于当前二进制目录的路径上创建文件级依赖项。如果任何依赖项是`OUTPUT`同一目录（`CMakeLists.txt`文件）中另一个自定义命令的依赖项，CMake 会自动将另一个自定义命令带入构建此命令的目标中。*版本 3.16 中的新增功能：*如果将任何依赖项列为 `BYPRODUCTS`目标或其任何构建事件在同一目录中，则会添加目标级别依赖项，以确保副产品可用。如果`DEPENDS`未指定，则该命令将在`OUTPUT`缺少时运行；如果该命令实际上并未创建`OUTPUT`，则该规则将始终运行。*3.1 版中的新功能：*`DEPENDS`可以使用 的参数[`generator expressions`](https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html#manual:cmake-generator-expressions(7)).

- `COMMAND_EXPAND_LISTS`

  *3.8 版中的新功能。*参数中的列表`COMMAND`将被扩展，包括那些使用 [`generator expressions`](https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html#manual:cmake-generator-expressions(7)), 允许 正确扩展`COMMAND`诸如此类的参数 。`${CC} "-I$<JOIN:$<TARGET_PROPERTY:foo,INCLUDE_DIRECTORIES>,;-I>" foo.cc`

- `IMPLICIT_DEPENDS`

  请求扫描输入文件的隐式依赖项。给定的语言指定了应该使用其对应的依赖扫描程序的编程语言。目前仅支持`C`和`CXX`语言扫描仪。必须为列表中的每个文件指定语言 `IMPLICIT_DEPENDS`。从扫描中发现的依赖关系会在构建时添加到自定义命令的依赖关系中。请注意，该`IMPLICIT_DEPENDS`选项目前仅支持 Makefile 生成器，其他生成器将忽略该选项。笔记 此选项不能与选项同时指定`DEPFILE`。

- `JOB_POOL`

  *3.15 版中的新功能。*指定一个[`pool`](https://cmake.org/cmake/help/latest/prop_gbl/JOB_POOLS.html#prop_gbl:JOB_POOLS)为了[`Ninja`](https://cmake.org/cmake/help/latest/generator/Ninja.html#generator:Ninja) 发电机。与 不兼容`USES_TERMINAL`，这意味着`console`池。使用未定义的池[`JOB_POOLS`](https://cmake.org/cmake/help/latest/prop_gbl/JOB_POOLS.html#prop_gbl:JOB_POOLS)在构建时导致 ninja 出错。

- `MAIN_DEPENDENCY`

  指定命令的主要输入源文件。这与赋予`DEPENDS`选项的任何值一样被处理，但也向 Visual Studio 生成器建议在何处挂起自定义命令。每个源文件最多可以有一个命令将其指定为其主要依赖项。编译命令（即用于库或可执行文件）被视为隐式主要依赖项，它会被自定义命令规范静默覆盖。

- `OUTPUT`

  指定命令预期生成的输出文件。如果输出名称是相对路径，它将相对于与当前源目录对应的构建树目录进行解释。每个输出文件都将标有[`GENERATED`](https://cmake.org/cmake/help/latest/prop_sf/GENERATED.html#prop_sf:GENERATED) 源文件属性自动。如果自定义命令的输出实际上并未创建为磁盘上的文件，则应将其标记为[`SYMBOLIC`](https://cmake.org/cmake/help/latest/prop_sf/SYMBOLIC.html#prop_sf:SYMBOLIC) 源文件属性。*3.20 版中的新功能：*参数`OUTPUT`可以使用一组受限的 [`generator expressions`](https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html#manual:cmake-generator-expressions(7)). 不允许[依赖于目标的表达式。](https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html#target-dependent-queries)

- `USES_TERMINAL`

  *3.2 版中的新功能。*如果可能，该命令将直接访问终端。随着[`Ninja`](https://cmake.org/cmake/help/latest/generator/Ninja.html#generator:Ninja)生成器，这会将命令放在`console` [`pool`](https://cmake.org/cmake/help/latest/prop_gbl/JOB_POOLS.html#prop_gbl:JOB_POOLS).

- `VERBATIM`

  命令的所有参数都将为构建工具正确转义，以便调用的命令接收每个参数不变。请注意，在 add_custom_command 甚至看到参数之前，CMake 语言处理器仍然使用一级转义。建议使用 ，`VERBATIM`因为它可以实现正确的行为。未给出时`VERBATIM`，行为是特定于平台的，因为没有对特定于工具的特殊字符的保护。

- `WORKING_DIRECTORY`

  使用给定的当前工作目录执行命令。如果它是相对路径，它将相对于与当前源目录对应的构建树目录进行解释。*3.13 版中的新功能：*`WORKING_DIRECTORY`可以使用 的参数[`generator expressions`](https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html#manual:cmake-generator-expressions(7)).

- `DEPFILE`

  *3.7 版中的新功能。*指定一个包含自定义命令依赖项的 depfile。它通常由自定义命令本身发出。只有在生成器支持时才能使用此关键字，如下所述。`gcc`与使用选项生成的内容兼容的预期格式与生成`-M`器或平台无关。[使用带有常规扩展的BNF](https://en.wikipedia.org/wiki/Backus–Naur_form)表示法指定的正式语法 如下：`**depfile**       ::=   rule* **规则**         ::=   targets(':' ( ?)?)?separator dependencieseol **目标**      ::=   target( )* * separator targetseparator**目标**       ::=  pathname **依赖**::=   dependency( )* * separator dependencyseparator**依赖**   ::=  pathname **分隔符**    ::= ( space| line_continue)+ **line_continue** ::= '\'eol **空间**        ::= ' ' | '\t' **路径名**     ::=   character+ **字符**    ::=   std_character| dollar| hash|whitespace **std_character** ::= <除'$'、'#'或''之外的任何字符> **美元**       ::= '$$' **哈希**         ::= '\#' **空格**   ::= '\' **eol**           ::= '\r'? '\n' `笔记 作为 的一部分`pathname`，任何斜杠和反斜杠都被解释为目录分隔符。*3.7 版新功能*：[`Ninja`](https://cmake.org/cmake/help/latest/generator/Ninja.html#generator:Ninja)生成器支持`DEPFILE`自关键字首次添加以来。*3.17 版中的新功能：*添加了[`Ninja Multi-Config`](https://cmake.org/cmake/help/latest/generator/Ninja Multi-Config.html#generator:Ninja Multi-Config)生成器，其中包括对`DEPFILE`关键字的支持。*3.20 新版功能：*添加了对[Makefile Generators](https://cmake.org/cmake/help/latest/manual/cmake-generators.7.html#makefile-generators)的支持。笔记 `DEPFILE`[不能与Makefile Generators](https://cmake.org/cmake/help/latest/manual/cmake-generators.7.html#makefile-generators)`IMPLICIT_DEPENDS`的选项同时指定 。*3.21 版新功能：*添加了对 VS 2012 及更高版本的[Visual Studio 生成器](https://cmake.org/cmake/help/latest/manual/cmake-generators.7.html#visual-studio-generators)的支持，以及[`Xcode`](https://cmake.org/cmake/help/latest/generator/Xcode.html#generator:Xcode)发电机。支持 [`generator expressions`](https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html#manual:cmake-generator-expressions(7))也被添加了。`DEPFILE`与上面列出的生成器以外的生成器一起使用是错误的。如果`DEPFILE`参数是相对的，它应该是相对的 [`CMAKE_CURRENT_BINARY_DIR`](https://cmake.org/cmake/help/latest/variable/CMAKE_CURRENT_BINARY_DIR.html#variable:CMAKE_CURRENT_BINARY_DIR), 中的任何相对路径 `DEPFILE`也应该是相对于[`CMAKE_CURRENT_BINARY_DIR`](https://cmake.org/cmake/help/latest/variable/CMAKE_CURRENT_BINARY_DIR.html#variable:CMAKE_CURRENT_BINARY_DIR). 查看政策[`CMP0116`](https://cmake.org/cmake/help/latest/policy/CMP0116.html#policy:CMP0116)，它始终`NEW`适用于 [Makefile Generators](https://cmake.org/cmake/help/latest/manual/cmake-generators.7.html#makefile-generators)、[Visual Studio Generators](https://cmake.org/cmake/help/latest/manual/cmake-generators.7.html#visual-studio-generators)和[`Xcode`](https://cmake.org/cmake/help/latest/generator/Xcode.html#generator:Xcode)发电机。

## 示例：生成文件

自定义命令可用于生成源文件。例如，代码：

```cmake
add_custom_command(
  OUTPUT out.c
  COMMAND someTool -i ${CMAKE_CURRENT_SOURCE_DIR}/in.txt
                   -o out.c
  DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/in.txt
  VERBATIM)
add_library(myLib out.c)
```

添加一个自定义命令来运行`someTool`以生成`out.c`然后将生成的源代码编译为库的一部分。`in.txt`生成规则将在更改时重新运行。

*3.20 版中的新功能：*可以使用生成器表达式来指定每个配置的输出。例如，代码：

```cmake
add_custom_command(
  OUTPUT "out-$<CONFIG>.c"
  COMMAND someTool -i ${CMAKE_CURRENT_SOURCE_DIR}/in.txt
                   -o "out-$<CONFIG>.c"
                   -c "$<CONFIG>"
  DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/in.txt
  VERBATIM)
add_library(myLib "out-$<CONFIG>.c")
```

添加一个自定义命令来运行`someTool`generate `out-<config>.c`，其中`<config>`是构建配置，然后将生成的源代码编译为库的一部分。



## 构建事件

第二个签名将自定义命令添加到库或可执行文件等目标。这对于在构建目标之前或之后执行操作很有用。该命令成为目标的一部分，并且只会在构建目标本身时执行。如果目标已经构建，该命令将不会执行。

```cmake
add_custom_command(TARGET <target>
                   PRE_BUILD | PRE_LINK | POST_BUILD
                   COMMAND command1 [ARGS] [args1...]
                   [COMMAND command2 [ARGS] [args2...] ...]
                   [BYPRODUCTS [files...]]
                   [WORKING_DIRECTORY dir]
                   [COMMENT comment]
                   [VERBATIM] [USES_TERMINAL]
                   [COMMAND_EXPAND_LISTS])
```

这定义了一个新命令，它将与构建指定的`<target>`. `<target>`必须在当前目录中定义；不能指定在其他目录中定义的目标。

该命令何时发生取决于指定以下哪一项：

- `PRE_BUILD`

  在[Visual Studio Generators](https://cmake.org/cmake/help/latest/manual/cmake-generators.7.html#visual-studio-generators)上，在目标中执行任何其他规则之前运行。`PRE_LINK`在其他生成器上，在命令之前运行。

- `PRE_LINK`

  在编译源之后但在链接二进制文件或运行静态库的库管理器或归档器工具之前运行。这不是为创建的目标定义的 [`add_custom_target()`](https://cmake.org/cmake/help/latest/command/add_custom_target.html#command:add_custom_target)命令。

- `POST_BUILD`

  在目标中的所有其他规则都已执行后运行。

`TARGET`项目在使用表单时应始终指定上述三个关键字之一。出于向后兼容性的原因，`POST_BUILD`假设没有给出这样的关键字，但项目应明确提供关键字之一以明确他们期望的行为。

笔记

 

因为生成器表达式可以在自定义命令中使用，所以可以定义`COMMAND`行或整个自定义命令，这些命令对某些配置计算为空字符串。对于**Visual Studio 2010（和更新的）**生成器，这些命令行或自定义命令将被省略以用于特定配置，并且不会添加“empty-string-command”。

这允许为每个配置添加单独的构建事件。

*3.21 新版功能：*支持依赖于目标的生成器表达式。

## 示例：构建事件

一个`POST_BUILD`事件可用于在链接后对二进制文件进行后处理。例如，代码：

```cmake
add_executable(myExe myExe.c)
add_custom_command(
  TARGET myExe POST_BUILD
  COMMAND someHasher -i "$<TARGET_FILE:myExe>"
                     -o "$<TARGET_FILE:myExe>.hash"
  VERBATIM)
```

链接后将运行以在可执行文件旁边`someHasher`生成一个文件。`.hash`

*3.20 版中的新功能：*可以使用生成器表达式来指定每个配置的副产品。例如，代码：

```cmake
add_library(myPlugin MODULE myPlugin.c)
add_custom_command(
  TARGET myPlugin POST_BUILD
  COMMAND someHasher -i "$<TARGET_FILE:myPlugin>"
                     --as-code "myPlugin-hash-$<CONFIG>.c"
  BYPRODUCTS "myPlugin-hash-$<CONFIG>.c"
  VERBATIM)
add_executable(myExe myExe.c "myPlugin-hash-$<CONFIG>.c")
```

将`someHasher`在链接之后运行`myPlugin`，例如生成一个`.c` 包含代码的文件，以检查可执行文件在加载之前可以用来验证它的哈希`myPlugin`值`myExe` 。

## 忍者多重配置

*3.20 版新功能：*`add_custom_command`支持[`Ninja Multi-Config`](https://cmake.org/cmake/help/latest/generator/Ninja Multi-Config.html#generator:Ninja Multi-Config) 生成器的交叉配置功能。有关更多信息，请参阅生成器文档。



# [add_custom_target](https://cmake.org/cmake/help/latest/command/add_custom_target.html)

添加一个没有输出的目标，以便始终构建它。

```cmake
add_custom_target(Name [ALL] [command1 [args1...]]
                  [COMMAND command2 [args2...] ...]
                  [DEPENDS depend depend depend ... ]
                  [BYPRODUCTS [files...]]
                  [WORKING_DIRECTORY dir]
                  [COMMENT comment]
                  [JOB_POOL job_pool]
                  [VERBATIM] [USES_TERMINAL]
                  [COMMAND_EXPAND_LISTS]
                  [SOURCES src1 [src2...]])
```

添加具有给定名称的目标以执行给定命令。目标没有输出文件， 即使命令尝试使用目标的名称创建文件，它也*始终被认为是过时的。*使用[`add_custom_command()`](https://cmake.org/cmake/help/latest/command/add_custom_command.html#command:add_custom_command)命令生成具有依赖关系的文件。默认情况下，没有任何东西取决于自定义目标。使用[`add_dependencies()`](https://cmake.org/cmake/help/latest/command/add_dependencies.html#command:add_dependencies)命令向其他目标添加依赖项或从其他目标添加依赖项。

选项包括：

- `ALL`

  表明这个目标应该被添加到默认的构建目标中，这样每次都会运行它（命令不能被调用`ALL`）。

- `BYPRODUCTS`

  *3.2 版中的新功能。*指定命令预期生成但其修改时间可能会或可能不会在后续构建中更新的文件。如果副产品名称是相对路径，它将相对于与当前源目录对应的构建树目录进行解释。每个副产品文件都将标有[`GENERATED`](https://cmake.org/cmake/help/latest/prop_sf/GENERATED.html#prop_sf:GENERATED) 源文件属性自动。副产品的明确规范由 [`Ninja`](https://cmake.org/cmake/help/latest/generator/Ninja.html#generator:Ninja)生成器告诉`ninja`构建工具如何在副产品丢失时重新生成它们。当其他构建规则（例如自定义命令）依赖于副产品时，它也很有用。Ninja 需要为任何生成的文件建立一个构建规则，即使存在仅订单依赖项，以确保副产品在其依赖项构建之前可用。[Makefile 生成器](https://cmake.org/cmake/help/latest/manual/cmake-generators.7.html#makefile-generators)将删除`BYPRODUCTS`和其他 [`GENERATED`](https://cmake.org/cmake/help/latest/prop_sf/GENERATED.html#prop_sf:GENERATED)期间的文件。`make clean`*3.20 版中的新功能：*参数`BYPRODUCTS`可以使用一组受限的 [`generator expressions`](https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html#manual:cmake-generator-expressions(7)). 不允许[依赖于目标的表达式。](https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html#target-dependent-queries)

- `COMMAND`

  指定要在构建时执行的命令行。如果指定了多个，`COMMAND`它们将按顺序执行，但*不一定*组成有状态的 shell 或批处理脚本。（要运行完整的脚本，请使用[`configure_file()`](https://cmake.org/cmake/help/latest/command/configure_file.html#command:configure_file)命令或 [`file(GENERATE)`](https://cmake.org/cmake/help/latest/command/file.html#command:file)命令来创建它，然后指定 a`COMMAND`来启动它。）如果`COMMAND`指定一个可执行目标名称（由 [`add_executable()`](https://cmake.org/cmake/help/latest/command/add_executable.html#command:add_executable)命令），如果以下任一情况为真，它将自动替换为构建时创建的可执行文件的位置：目标没有被交叉编译（即 [`CMAKE_CROSSCOMPILING`](https://cmake.org/cmake/help/latest/variable/CMAKE_CROSSCOMPILING.html#variable:CMAKE_CROSSCOMPILING)变量未设置为真）。*3.6 版中*的新功能：正在交叉编译目标并提供了一个模拟器（即它的[`CROSSCOMPILING_EMULATOR`](https://cmake.org/cmake/help/latest/prop_tgt/CROSSCOMPILING_EMULATOR.html#prop_tgt:CROSSCOMPILING_EMULATOR)目标属性已设置）。在这种情况下，内容[`CROSSCOMPILING_EMULATOR`](https://cmake.org/cmake/help/latest/prop_tgt/CROSSCOMPILING_EMULATOR.html#prop_tgt:CROSSCOMPILING_EMULATOR)将在目标可执行文件的位置之前添加到命令中。如果上述条件都不满足，则假定命令名称是`PATH`在构建时要找到的程序。`COMMAND`可以使用 的参数[`generator expressions`](https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html#manual:cmake-generator-expressions(7)). 使用[`TARGET_FILE`](https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html#genex:TARGET_FILE)生成器表达式稍后在命令行中引用目标的位置（即作为命令参数而不是作为要执行的命令）。每当以下基于目标的生成器表达式之一用作要执行的命令或在命令参数中提及时，将自动添加目标级别的依赖项，以便在此自定义目标之前构建提及的目标（请参阅策略[`CMP0112`](https://cmake.org/cmake/help/latest/policy/CMP0112.html#policy:CMP0112)).`TARGET_FILE``TARGET_LINKER_FILE``TARGET_SONAME_FILE``TARGET_PDB_FILE`命令和参数是可选的，如果未指定，将创建一个空目标。

- `COMMENT`

  在构建时执行命令之前显示给定的消息。

- `DEPENDS`

  使用创建的自定义命令的参考文件和输出 [`add_custom_command()`](https://cmake.org/cmake/help/latest/command/add_custom_command.html#command:add_custom_command)命令在同一目录（`CMakeLists.txt`文件）中调用。它们将在构建目标时更新。*在 3.16 版中更改：*如果任何依赖项是目标的副产品或其任何构建事件在同一目录中，则会添加目标级别的依赖项，以确保在构建此目标之前副产品可用。使用[`add_dependencies()`](https://cmake.org/cmake/help/latest/command/add_dependencies.html#command:add_dependencies)命令添加对其他目标的依赖项。

- `COMMAND_EXPAND_LISTS`

  *3.8 版中的新功能。*参数中的列表`COMMAND`将被扩展，包括那些使用 [`generator expressions`](https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html#manual:cmake-generator-expressions(7)), 允许 正确扩展`COMMAND`诸如此类的参数 。`${CC} "-I$<JOIN:$<TARGET_PROPERTY:foo,INCLUDE_DIRECTORIES>,;-I>" foo.cc`

- `JOB_POOL`

  *3.15 版中的新功能。*指定一个[`pool`](https://cmake.org/cmake/help/latest/prop_gbl/JOB_POOLS.html#prop_gbl:JOB_POOLS)为了[`Ninja`](https://cmake.org/cmake/help/latest/generator/Ninja.html#generator:Ninja) 发电机。与 不兼容`USES_TERMINAL`，这意味着`console`池。使用未定义的池[`JOB_POOLS`](https://cmake.org/cmake/help/latest/prop_gbl/JOB_POOLS.html#prop_gbl:JOB_POOLS)在构建时导致 ninja 出错。

- `SOURCES`

  指定要包含在自定义目标中的其他源文件。指定的源文件将被添加到 IDE 项目文件中，以方便编辑，即使它们没有构建规则。

- `VERBATIM`

  命令的所有参数都将为构建工具正确转义，以便调用的命令接收每个参数不变。`add_custom_target`请注意，在看到参数之前，CMake 语言处理器仍然使用一级转义。建议使用 ，`VERBATIM`因为它可以实现正确的行为。未给出时`VERBATIM`，行为是特定于平台的，因为没有对特定于工具的特殊字符的保护。

- `USES_TERMINAL`

  *3.2 版中的新功能。*如果可能，该命令将直接访问终端。随着[`Ninja`](https://cmake.org/cmake/help/latest/generator/Ninja.html#generator:Ninja)生成器，这会将命令放在`console` [`pool`](https://cmake.org/cmake/help/latest/prop_gbl/JOB_POOLS.html#prop_gbl:JOB_POOLS).

- `WORKING_DIRECTORY`

  使用给定的当前工作目录执行命令。如果它是相对路径，它将相对于与当前源目录对应的构建树目录进行解释。*3.13 版中的新功能：*`WORKING_DIRECTORY`可以使用 的参数[`generator expressions`](https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html#manual:cmake-generator-expressions(7)).

## 忍者多重配置

*3.20 版新功能：*`add_custom_target`支持[`Ninja Multi-Config`](https://cmake.org/cmake/help/latest/generator/Ninja Multi-Config.html#generator:Ninja Multi-Config) 生成器的交叉配置功能。有关更多信息，请参阅生成器文档。



# [add_definitions](https://cmake.org/cmake/help/latest/command/add_definitions.html)

将 -D 定义标志添加到源文件的编译中。

```cmake
add_definitions(-DFOO -DBAR ...)
```

将定义添加到当前目录中的目标的编译器命令行，无论是在调用此命令之前还是之后添加，以及之后添加的子目录中的目标。此命令可用于添加任何标志，但它旨在添加预处理器定义。

笔记

 

此命令已被替代命令取代：

- 利用[`add_compile_definitions()`](https://cmake.org/cmake/help/latest/command/add_compile_definitions.html#command:add_compile_definitions)添加预处理器定义。
- 利用[`include_directories()`](https://cmake.org/cmake/help/latest/command/include_directories.html#command:include_directories)添加包含目录。
- 利用[`add_compile_options()`](https://cmake.org/cmake/help/latest/command/add_compile_options.html#command:add_compile_options)添加其他选项。

以预处理器定义开头`-D`或`/D`看起来像预处理器定义的标志会自动添加到[`COMPILE_DEFINITIONS`](https://cmake.org/cmake/help/latest/prop_dir/COMPILE_DEFINITIONS.html#prop_dir:COMPILE_DEFINITIONS)当前目录的目录属性。具有非平凡值的定义可能会留在标志集中，而不是出于向后兼容性的原因进行转换。参见文档 [`directory`](https://cmake.org/cmake/help/latest/prop_dir/COMPILE_DEFINITIONS.html#prop_dir:COMPILE_DEFINITIONS), [`target`](https://cmake.org/cmake/help/latest/prop_tgt/COMPILE_DEFINITIONS.html#prop_tgt:COMPILE_DEFINITIONS), [`source file`](https://cmake.org/cmake/help/latest/prop_sf/COMPILE_DEFINITIONS.html#prop_sf:COMPILE_DEFINITIONS) `COMPILE_DEFINITIONS` 有关将预处理器定义添加到特定范围和配置的详细信息的属性。

见[`cmake-buildsystem(7)`](https://cmake.org/cmake/help/latest/manual/cmake-buildsystem.7.html#manual:cmake-buildsystem(7))有关定义构建系统属性的更多信息。



# [add_dependencies](https://cmake.org/cmake/help/latest/command/add_dependencies.html)

在顶级目标之间添加依赖关系。

```cmake
add_dependencies(<target> [<target-dependency>]...)
```

使顶层`<target>`依赖于其他顶层目标，以确保它们之前构建`<target>`。顶级目标是由其中一个创建的[`add_executable()`](https://cmake.org/cmake/help/latest/command/add_executable.html#command:add_executable), [`add_library()`](https://cmake.org/cmake/help/latest/command/add_library.html#command:add_library)， 或者[`add_custom_target()`](https://cmake.org/cmake/help/latest/command/add_custom_target.html#command:add_custom_target)命令（但不是由 CMake 生成的目标，例如`install`）。

添加到[导入的目标](https://cmake.org/cmake/help/latest/manual/cmake-buildsystem.7.html#imported-targets) 或[接口库](https://cmake.org/cmake/help/latest/manual/cmake-buildsystem.7.html#interface-libraries)的依赖项会在其位置传递，因为目标本身不会构建。

*3.3 版新功能：*允许向接口库添加依赖项。

见`DEPENDS`选项[`add_custom_target()`](https://cmake.org/cmake/help/latest/command/add_custom_target.html#command:add_custom_target)和 [`add_custom_command()`](https://cmake.org/cmake/help/latest/command/add_custom_command.html#command:add_custom_command)用于在自定义规则中添加文件级依赖项的命令。见[`OBJECT_DEPENDS`](https://cmake.org/cmake/help/latest/prop_sf/OBJECT_DEPENDS.html#prop_sf:OBJECT_DEPENDS) 源文件属性将文件级依赖项添加到目标文件。



# [add_executable](https://cmake.org/cmake/help/latest/command/add_executable.html)

内容

- [add_executable](https://cmake.org/cmake/help/latest/command/add_executable.html#add-executable)
  - [正常的可执行文件](https://cmake.org/cmake/help/latest/command/add_executable.html#normal-executables)
  - [导入的可执行文件](https://cmake.org/cmake/help/latest/command/add_executable.html#imported-executables)
  - [别名可执行文件](https://cmake.org/cmake/help/latest/command/add_executable.html#alias-executables)

使用指定的源文件将可执行文件添加到项目中。

## [正常的可执行文件](https://cmake.org/cmake/help/latest/command/add_executable.html#id2)

```cmake
add_executable(<name> [WIN32] [MACOSX_BUNDLE]
               [EXCLUDE_FROM_ALL]
               [source1] [source2 ...])
```

添加一个`<name>`从命令调用中列出的源文件构建的可执行目标。对应于逻辑目标名称， `<name>`并且在项目中必须是全局唯一的。构建的可执行文件的实际文件名是根据本机平台的约定（例如 `<name>.exe`或只是`<name>`）构造的。

*3.1 版中的新功能：*源参数`add_executable`可以使用带有语法的“生成器表达式” `$<...>`。见[`cmake-generator-expressions(7)`](https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html#manual:cmake-generator-expressions(7)) 可用表达式的手册。

*3.11 版新功能：*如果稍后使用源文件添加源文件，则可以省略它们 [`target_sources()`](https://cmake.org/cmake/help/latest/command/target_sources.html#command:target_sources).

默认情况下，可执行文件将在与调用命令的源树目录对应的构建树目录中创建。参见文档 [`RUNTIME_OUTPUT_DIRECTORY`](https://cmake.org/cmake/help/latest/prop_tgt/RUNTIME_OUTPUT_DIRECTORY.html#prop_tgt:RUNTIME_OUTPUT_DIRECTORY)目标属性以更改此位置。参见文档[`OUTPUT_NAME`](https://cmake.org/cmake/help/latest/prop_tgt/OUTPUT_NAME.html#prop_tgt:OUTPUT_NAME)target 属性改变`<name>`部分最终文件名。

如果`WIN32`被赋予属性[`WIN32_EXECUTABLE`](https://cmake.org/cmake/help/latest/prop_tgt/WIN32_EXECUTABLE.html#prop_tgt:WIN32_EXECUTABLE)将在创建的目标上设置。有关详细信息，请参阅该目标属性的文档。

如果`MACOSX_BUNDLE`给出相应的属性，将在创建的目标上设置。参见文档[`MACOSX_BUNDLE`](https://cmake.org/cmake/help/latest/prop_tgt/MACOSX_BUNDLE.html#prop_tgt:MACOSX_BUNDLE) 目标属性以获取详细信息。

如果`EXCLUDE_FROM_ALL`给出相应的属性，将在创建的目标上设置。参见文档[`EXCLUDE_FROM_ALL`](https://cmake.org/cmake/help/latest/prop_tgt/EXCLUDE_FROM_ALL.html#prop_tgt:EXCLUDE_FROM_ALL) 目标属性以获取详细信息。

见[`cmake-buildsystem(7)`](https://cmake.org/cmake/help/latest/manual/cmake-buildsystem.7.html#manual:cmake-buildsystem(7))有关定义构建系统属性的更多信息。

也可以看看[`HEADER_FILE_ONLY`](https://cmake.org/cmake/help/latest/prop_sf/HEADER_FILE_ONLY.html#prop_sf:HEADER_FILE_ONLY)如果某些源已被预处理，并且您希望可以从 IDE 中访问原始源，该怎么办。

## [导入的可执行文件](https://cmake.org/cmake/help/latest/command/add_executable.html#id3)

```cmake
add_executable(<name> IMPORTED [GLOBAL])
```

IMPORTED[可执行目标](https://cmake.org/cmake/help/latest/manual/cmake-buildsystem.7.html#imported-targets)引用位于项目外部的可执行文件。没有生成规则来构建它，并且[`IMPORTED`](https://cmake.org/cmake/help/latest/prop_tgt/IMPORTED.html#prop_tgt:IMPORTED)目标属性是`True`。目标名称在创建它的目录及其下方具有范围，但该`GLOBAL`选项扩展了可见性。它可以像项目中构建的任何目标一样被引用。 `IMPORTED`可执行文件可用于方便地从命令中引用，例如[`add_custom_command()`](https://cmake.org/cmake/help/latest/command/add_custom_command.html#command:add_custom_command). 通过设置名称以 . 开头的属性来指定有关导入可执行文件的详细信息`IMPORTED_`。最重要的此类属性是 [`IMPORTED_LOCATION`](https://cmake.org/cmake/help/latest/prop_tgt/IMPORTED_LOCATION.html#prop_tgt:IMPORTED_LOCATION)（及其每个配置版本 [`IMPORTED_LOCATION_`](https://cmake.org/cmake/help/latest/prop_tgt/IMPORTED_LOCATION_CONFIG.html#prop_tgt:IMPORTED_LOCATION_)) 指定主要可执行文件在磁盘上的位置。有关更多信息，请参阅`IMPORTED_*` 属性文档。

## [别名可执行文件](https://cmake.org/cmake/help/latest/command/add_executable.html#id4)

```cmake
add_executable(<name> ALIAS <target>)
```

创建一个[别名目标](https://cmake.org/cmake/help/latest/manual/cmake-buildsystem.7.html#alias-targets)，`<name>`以便`<target>`在后续命令中引用。`<name>` 不会作为生成目标出现在生成的构建系统中。可能`<target>`不是. `ALIAS`

*3.11 版中的新功能：*可以`ALIAS`针对`GLOBAL` [导入的目标](https://cmake.org/cmake/help/latest/manual/cmake-buildsystem.7.html#imported-targets)

*3.18 版中的新功能：*可以`ALIAS`针对非`GLOBAL`导入目标。此类别名的范围仅限于创建它的目录和子目录。这[`ALIAS_GLOBAL`](https://cmake.org/cmake/help/latest/prop_tgt/ALIAS_GLOBAL.html#prop_tgt:ALIAS_GLOBAL)target 属性可用于检查别名是否是全局的。

`ALIAS`目标可用作从中读取属性的目标、自定义命令的可执行文件和自定义目标。也可以使用常规测试它们是否存在[`if(TARGET)`](https://cmake.org/cmake/help/latest/command/if.html#command:if)子命令。`<name>`不能用于修改 的属性，`<target>`即不能作为 的操作数[`set_property()`](https://cmake.org/cmake/help/latest/command/set_property.html#command:set_property), [`set_target_properties()`](https://cmake.org/cmake/help/latest/command/set_target_properties.html#command:set_target_properties), [`target_link_libraries()`](https://cmake.org/cmake/help/latest/command/target_link_libraries.html#command:target_link_libraries)等`ALIAS`目标可能无法安装或导出。



# [add_library](https://cmake.org/cmake/help/latest/command/add_library.html)

内容

- [add_library](https://cmake.org/cmake/help/latest/command/add_library.html#add-library)
  - [普通图书馆](https://cmake.org/cmake/help/latest/command/add_library.html#normal-libraries)
  - [对象库](https://cmake.org/cmake/help/latest/command/add_library.html#object-libraries)
  - [接口库](https://cmake.org/cmake/help/latest/command/add_library.html#interface-libraries)
  - [导入的库](https://cmake.org/cmake/help/latest/command/add_library.html#imported-libraries)
  - [别名库](https://cmake.org/cmake/help/latest/command/add_library.html#alias-libraries)

使用指定的源文件将库添加到项目中。

## [普通库](https://cmake.org/cmake/help/latest/command/add_library.html#id2)

```cmake
add_library(<name> [STATIC | SHARED | MODULE]
            [EXCLUDE_FROM_ALL]
            [<source>...])
```

添加一个库目标，称为`<name>`从命令调用中列出的源文件构建。对应于逻辑目标名称，`<name>` 并且在项目中必须是全局唯一的。构建的库的实际文件名是根据本机平台的约定（例如`lib<name>.a`或 `<name>.lib`）构建的。

*3.1 版中的新功能：*源参数`add_library`可以使用带有语法的“生成器表达式” `$<...>`。见[`cmake-generator-expressions(7)`](https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html#manual:cmake-generator-expressions(7)) 可用表达式的手册。

*3.11 版新功能：*如果稍后使用源文件添加源文件，则可以省略它们 [`target_sources()`](https://cmake.org/cmake/help/latest/command/target_sources.html#command:target_sources).

`STATIC`, `SHARED`, 或`MODULE`可以指定要创建的库的类型。 `STATIC`库是链接其他目标时使用的目标文件的档案。 `SHARED`库是动态链接并在运行时加载的。 `MODULE`库是未链接到其他目标但可以在运行时使用类似 dlopen 的功能动态加载的插件。如果没有明确给出类型，则类型是`STATIC`或`SHARED`基于变量的当前值[`BUILD_SHARED_LIBS`](https://cmake.org/cmake/help/latest/variable/BUILD_SHARED_LIBS.html#variable:BUILD_SHARED_LIBS)是`ON`。对于`SHARED`和 `MODULE`库[`POSITION_INDEPENDENT_CODE`](https://cmake.org/cmake/help/latest/prop_tgt/POSITION_INDEPENDENT_CODE.html#prop_tgt:POSITION_INDEPENDENT_CODE)目标属性设置为`ON`自动。`SHARED`图书馆可能会标有[`FRAMEWORK`](https://cmake.org/cmake/help/latest/prop_tgt/FRAMEWORK.html#prop_tgt:FRAMEWORK) target 属性来创建一个 macOS 框架。

*3.8 版中的新功能：*库`STATIC`可能会标有[`FRAMEWORK`](https://cmake.org/cmake/help/latest/prop_tgt/FRAMEWORK.html#prop_tgt:FRAMEWORK) 目标属性来创建一个静态框架。

如果库不导出任何符号，则不得将其声明为 `SHARED`库。例如，不导出非托管符号的 Windows 资源 DLL 或托管 C++/CLI DLL 需要是`MODULE`库。这是因为 CMake 期望`SHARED`库在 Windows 上始终具有关联的导入库。

默认情况下，将在与调用命令的源树目录对应的构建树目录中创建库文件。参见文档[`ARCHIVE_OUTPUT_DIRECTORY`](https://cmake.org/cmake/help/latest/prop_tgt/ARCHIVE_OUTPUT_DIRECTORY.html#prop_tgt:ARCHIVE_OUTPUT_DIRECTORY), [`LIBRARY_OUTPUT_DIRECTORY`](https://cmake.org/cmake/help/latest/prop_tgt/LIBRARY_OUTPUT_DIRECTORY.html#prop_tgt:LIBRARY_OUTPUT_DIRECTORY)， 和 [`RUNTIME_OUTPUT_DIRECTORY`](https://cmake.org/cmake/help/latest/prop_tgt/RUNTIME_OUTPUT_DIRECTORY.html#prop_tgt:RUNTIME_OUTPUT_DIRECTORY)目标属性以更改此位置。参见文档[`OUTPUT_NAME`](https://cmake.org/cmake/help/latest/prop_tgt/OUTPUT_NAME.html#prop_tgt:OUTPUT_NAME)target 属性改变`<name>`部分最终文件名。

如果`EXCLUDE_FROM_ALL`给出相应的属性，将在创建的目标上设置。参见文档[`EXCLUDE_FROM_ALL`](https://cmake.org/cmake/help/latest/prop_tgt/EXCLUDE_FROM_ALL.html#prop_tgt:EXCLUDE_FROM_ALL) 目标属性以获取详细信息。

见[`cmake-buildsystem(7)`](https://cmake.org/cmake/help/latest/manual/cmake-buildsystem.7.html#manual:cmake-buildsystem(7))有关定义构建系统属性的更多信息。

也可以看看[`HEADER_FILE_ONLY`](https://cmake.org/cmake/help/latest/prop_sf/HEADER_FILE_ONLY.html#prop_sf:HEADER_FILE_ONLY)如果某些源已被预处理，并且您希望可以从 IDE 中访问原始源，该怎么办。

## [对象库](https://cmake.org/cmake/help/latest/command/add_library.html#id3)

```cmake
add_library(<name> OBJECT [<source>...])
```

创建一个[对象库](https://cmake.org/cmake/help/latest/manual/cmake-buildsystem.7.html#object-libraries)。目标库编译源文件，但不会将其目标文件归档或链接到库中。而是由创建的其他目标[`add_library()`](https://cmake.org/cmake/help/latest/command/add_library.html#command:add_library)或者 [`add_executable()`](https://cmake.org/cmake/help/latest/command/add_executable.html#command:add_executable)可以使用表单的表达式`$<TARGET_OBJECTS:objlib>`作为源来引用对象，其中`objlib`是对象库名称。例如：

```cmake
add_library(... $<TARGET_OBJECTS:objlib> ...)
add_executable(... $<TARGET_OBJECTS:objlib> ...)
```

将在一个库和一个可执行文件中包含 objlib 的目标文件以及从它们自己的源代码编译的那些文件。对象库可能只包含编译源、头文件和其他不会影响正常库链接的文件（例如`.txt`）。它们可能包含生成此类源的自定义命令，但不包含 `PRE_BUILD`、`PRE_LINK`或`POST_BUILD`命令。一些本机构建系统（例如 Xcode）可能不喜欢只有目标文件的目标，因此请考虑将至少一个真实源文件添加到任何引用 `$<TARGET_OBJECTS:objlib>`.

*3.12 新版功能：*对象库可以链接到[`target_link_libraries()`](https://cmake.org/cmake/help/latest/command/target_link_libraries.html#command:target_link_libraries).

## [接口库](https://cmake.org/cmake/help/latest/command/add_library.html#id4)

```cmake
add_library(<name> INTERFACE)
```

创建一个[接口库](https://cmake.org/cmake/help/latest/manual/cmake-buildsystem.7.html#interface-libraries)。`INTERFACE`库目标不编译源代码，也不在磁盘上生成库工件。但是，它可能设置了属性，并且可以安装和导出。通常，`INTERFACE_*`使用以下命令在接口目标上填充属性：

- [`set_property()`](https://cmake.org/cmake/help/latest/command/set_property.html#command:set_property),
- [`target_link_libraries(INTERFACE)`](https://cmake.org/cmake/help/latest/command/target_link_libraries.html#command:target_link_libraries),
- [`target_link_options(INTERFACE)`](https://cmake.org/cmake/help/latest/command/target_link_options.html#command:target_link_options),
- [`target_include_directories(INTERFACE)`](https://cmake.org/cmake/help/latest/command/target_include_directories.html#command:target_include_directories),
- [`target_compile_options(INTERFACE)`](https://cmake.org/cmake/help/latest/command/target_compile_options.html#command:target_compile_options),
- [`target_compile_definitions(INTERFACE)`](https://cmake.org/cmake/help/latest/command/target_compile_definitions.html#command:target_compile_definitions)， 和
- [`target_sources(INTERFACE)`](https://cmake.org/cmake/help/latest/command/target_sources.html#command:target_sources),

然后它被用作参数[`target_link_libraries()`](https://cmake.org/cmake/help/latest/command/target_link_libraries.html#command:target_link_libraries) 像任何其他目标一样。

使用上述签名创建的接口库本身没有源文件，并且不作为目标包含在生成的构建系统中。

*3.15 版中的新功能：*接口库可以具有[`PUBLIC_HEADER`](https://cmake.org/cmake/help/latest/prop_tgt/PUBLIC_HEADER.html#prop_tgt:PUBLIC_HEADER)和 [`PRIVATE_HEADER`](https://cmake.org/cmake/help/latest/prop_tgt/PRIVATE_HEADER.html#prop_tgt:PRIVATE_HEADER)特性。这些属性指定的标头可以使用[`install(TARGETS)`](https://cmake.org/cmake/help/latest/command/install.html#command:install)命令。

*3.19 新版功能：*可以使用源文件创建接口库目标：

```cmake
add_library(<name> INTERFACE [<source>...] [EXCLUDE_FROM_ALL])
```

源文件可以直接在`add_library`调用中列出或稍后通过调用添加到[`target_sources()`](https://cmake.org/cmake/help/latest/command/target_sources.html#command:target_sources)使用`PRIVATE`or `PUBLIC`关键字。

如果接口库有源文件（即[`SOURCES`](https://cmake.org/cmake/help/latest/prop_tgt/SOURCES.html#prop_tgt:SOURCES) 目标属性设置），或标题集（即[`HEADER_SETS`](https://cmake.org/cmake/help/latest/prop_tgt/HEADER_SETS.html#prop_tgt:HEADER_SETS) target 属性），它将作为构建目标出现在生成的构建系统中，就像由 [`add_custom_target()`](https://cmake.org/cmake/help/latest/command/add_custom_target.html#command:add_custom_target)命令。它不编译任何源代码，但包含由 [`add_custom_command()`](https://cmake.org/cmake/help/latest/command/add_custom_command.html#command:add_custom_command)命令。

笔记

 

在`INTERFACE`关键字出现的大多数命令签名中，其后列出的项目仅成为该目标的使用要求的一部分，而不是目标自身设置的一部分。但是，在此签名中`add_library`，`INTERFACE`关键字仅指库类型。`add_library` 调用中在它后面列出的源是`PRIVATE`接口库，不会出现在它的 [`INTERFACE_SOURCES`](https://cmake.org/cmake/help/latest/prop_tgt/INTERFACE_SOURCES.html#prop_tgt:INTERFACE_SOURCES)目标财产。



## [导入的库](https://cmake.org/cmake/help/latest/command/add_library.html#id5)

```cmake
add_library(<name> <type> IMPORTED [GLOBAL])
```

创建一个名为的[IMPORTED 库目标](https://cmake.org/cmake/help/latest/manual/cmake-buildsystem.7.html#imported-targets)`<name>`。没有生成规则来构建它，并且[`IMPORTED`](https://cmake.org/cmake/help/latest/prop_tgt/IMPORTED.html#prop_tgt:IMPORTED)目标属性是`True`。目标名称在创建它的目录及其下方具有范围，但该`GLOBAL`选项扩展了可见性。它可以像项目中构建的任何目标一样被引用。 `IMPORTED`库对于方便地从命令中引用很有用[`target_link_libraries()`](https://cmake.org/cmake/help/latest/command/target_link_libraries.html#command:target_link_libraries). 通过设置名称以`IMPORTED_`和 开头的属性来指定有关导入库的详细信息`INTERFACE_`。

必须是以下`<type>`之一：

- `STATIC`, `SHARED`, `MODULE`, `UNKNOWN`

  引用位于项目外部的库文件。这 [`IMPORTED_LOCATION`](https://cmake.org/cmake/help/latest/prop_tgt/IMPORTED_LOCATION.html#prop_tgt:IMPORTED_LOCATION)目标属性（或其每个配置的变体[`IMPORTED_LOCATION_`](https://cmake.org/cmake/help/latest/prop_tgt/IMPORTED_LOCATION_CONFIG.html#prop_tgt:IMPORTED_LOCATION_)) 指定主库文件在磁盘上的位置：对于`SHARED`大多数非 Windows 平台上的库，主库文件是链接器和动态加载器都使用的`.so`或文件。`.dylib`如果引用的库文件有一个`SONAME`（或在 macOS 上，有一个`LC_ID_DYLIB`开头`@rpath/`），则该字段的值应设置在[`IMPORTED_SONAME`](https://cmake.org/cmake/help/latest/prop_tgt/IMPORTED_SONAME.html#prop_tgt:IMPORTED_SONAME)目标财产。如果引用的库文件没有`SONAME`，但平台支持，则[`IMPORTED_NO_SONAME`](https://cmake.org/cmake/help/latest/prop_tgt/IMPORTED_NO_SONAME.html#prop_tgt:IMPORTED_NO_SONAME)应设置目标属性。对于`SHARED`Windows 上的库，[`IMPORTED_IMPLIB`](https://cmake.org/cmake/help/latest/prop_tgt/IMPORTED_IMPLIB.html#prop_tgt:IMPORTED_IMPLIB) 目标属性（或其每个配置的变体 [`IMPORTED_IMPLIB_`](https://cmake.org/cmake/help/latest/prop_tgt/IMPORTED_IMPLIB_CONFIG.html#prop_tgt:IMPORTED_IMPLIB_)) 指定 DLL 导入库文件 (`.lib`或`.dll.a`) 在磁盘上 `IMPORTED_LOCATION`的位置，`.dll`并且 是运行时库的位置（并且是可选的，但需要[`TARGET_RUNTIME_DLLS`](https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html#genex:TARGET_RUNTIME_DLLS) 生成器表达式）。可以在`INTERFACE_*`属性中指定其他使用要求。`UNKNOWN`库类型通常仅用于 [Find Modules](https://cmake.org/cmake/help/latest/manual/cmake-developer.7.html#find-modules)的实现。它允许导入库的路径（通常使用[`find_library()`](https://cmake.org/cmake/help/latest/command/find_library.html#command:find_library)命令）来使用，而不必知道它是什么类型的库。这在静态库和 DLL 的导入库都具有相同文件扩展名的 Windows 上特别有用。

- `OBJECT`

  引用位于项目外部的一组目标文件。这[`IMPORTED_OBJECTS`](https://cmake.org/cmake/help/latest/prop_tgt/IMPORTED_OBJECTS.html#prop_tgt:IMPORTED_OBJECTS)目标属性（或其每个配置的变体[`IMPORTED_OBJECTS_`](https://cmake.org/cmake/help/latest/prop_tgt/IMPORTED_OBJECTS_CONFIG.html#prop_tgt:IMPORTED_OBJECTS_)) 指定目标文件在磁盘上的位置。可以在`INTERFACE_*`属性中指定其他使用要求。

- `INTERFACE`

  不引用磁盘上的任何库或对象文件，但可以在`INTERFACE_*`属性中指定使用要求。

有关详细信息，请参阅`IMPORTED_*`和`INTERFACE_*`属性的文档。

## [别名库](https://cmake.org/cmake/help/latest/command/add_library.html#id6)

```cmake
add_library(<name> ALIAS <target>)
```

创建一个[别名目标](https://cmake.org/cmake/help/latest/manual/cmake-buildsystem.7.html#alias-targets)，`<name>`以便`<target>`在后续命令中引用。`<name>`不会作为生成目标出现在生成的构建系统中。可能`<target>` 不是.`ALIAS`

*3.11 版中的新功能：*可以`ALIAS`针对`GLOBAL` [导入的目标](https://cmake.org/cmake/help/latest/manual/cmake-buildsystem.7.html#imported-targets)

*3.18 版中的新功能：*可以`ALIAS`针对非`GLOBAL`导入目标。此类别名的范围为创建它的目录及其下方。这[`ALIAS_GLOBAL`](https://cmake.org/cmake/help/latest/prop_tgt/ALIAS_GLOBAL.html#prop_tgt:ALIAS_GLOBAL)target 属性可用于检查别名是否是全局的。

`ALIAS`目标可以用作可链接目标，也可以用作从中读取属性的目标。也可以使用常规测试它们是否存在[`if(TARGET)`](https://cmake.org/cmake/help/latest/command/if.html#command:if)子命令。`<name>`不能用于修改 的属性，`<target>`即不能作为 的操作数[`set_property()`](https://cmake.org/cmake/help/latest/command/set_property.html#command:set_property), [`set_target_properties()`](https://cmake.org/cmake/help/latest/command/set_target_properties.html#command:set_target_properties), [`target_link_libraries()`](https://cmake.org/cmake/help/latest/command/target_link_libraries.html#command:target_link_libraries)等`ALIAS`目标可能无法安装或导出。



# [add_link_options](https://cmake.org/cmake/help/latest/command/add_link_options.html)

*3.13 版中的新功能。*

为当前目录及以下目录中的可执行文件、共享库或模块库目标的链接步骤添加选项，这些选项是在调用此命令后添加的。

```cmake
add_link_options(<option> ...)
```

此命令可用于添加任何链接选项，但存在用于添加库的替代命令（[`target_link_libraries()`](https://cmake.org/cmake/help/latest/command/target_link_libraries.html#command:target_link_libraries)或者 [`link_libraries()`](https://cmake.org/cmake/help/latest/command/link_libraries.html#command:link_libraries)）。参见文档 [`directory`](https://cmake.org/cmake/help/latest/prop_dir/LINK_OPTIONS.html#prop_dir:LINK_OPTIONS)和 [`target`](https://cmake.org/cmake/help/latest/prop_tgt/LINK_OPTIONS.html#prop_tgt:LINK_OPTIONS) `LINK_OPTIONS`特性。

笔记

 

此命令不能用于为静态库目标添加选项，因为它们不使用链接器。要添加归档器或 MSVC 图书馆员标志，请参阅[`STATIC_LIBRARY_OPTIONS`](https://cmake.org/cmake/help/latest/prop_tgt/STATIC_LIBRARY_OPTIONS.html#prop_tgt:STATIC_LIBRARY_OPTIONS)目标财产。

参数 to`add_link_options`可以使用带有语法的“生成器表达式” `$<...>`。见[`cmake-generator-expressions(7)`](https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html#manual:cmake-generator-expressions(7)) 可用表达式的手册。见[`cmake-buildsystem(7)`](https://cmake.org/cmake/help/latest/manual/cmake-buildsystem.7.html#manual:cmake-buildsystem(7)) 有关定义构建系统属性的更多信息。

## 主机和设备特定链接选项

*3.18 新版功能：*当涉及设备链接步骤时，由 [`CUDA_SEPARABLE_COMPILATION`](https://cmake.org/cmake/help/latest/prop_tgt/CUDA_SEPARABLE_COMPILATION.html#prop_tgt:CUDA_SEPARABLE_COMPILATION)和 [`CUDA_RESOLVE_DEVICE_SYMBOLS`](https://cmake.org/cmake/help/latest/prop_tgt/CUDA_RESOLVE_DEVICE_SYMBOLS.html#prop_tgt:CUDA_RESOLVE_DEVICE_SYMBOLS)属性和政策[`CMP0105`](https://cmake.org/cmake/help/latest/policy/CMP0105.html#policy:CMP0105)，原始选项将被传递到主机和设备链接步骤（包装在 设备链接中`-Xcompiler`或等效的设备链接中）。包裹的选项 `$<DEVICE_LINK:...>` [`generator expression`](https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html#manual:cmake-generator-expressions(7))将仅用于设备链接步骤。包裹的选项`$<HOST_LINK:...>` [`generator expression`](https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html#manual:cmake-generator-expressions(7))将仅用于主机链接步骤。

## 去重选项

用于目标的最终选项集是通过累积来自当前目标的选项及其依赖项的使用要求来构建的。对选项集进行重复数据删除以避免重复。

*3.12 版中的新功能：*虽然有利于单个选项，但重复数据删除步骤可以分解选项组。例如，变成 。可以使用类似 shell 的引用和前缀来指定一组选项。前缀被删除，其余的选项字符串使用 `-option A -option B``-option A B``SHELL:``SHELL:`[`separate_arguments()`](https://cmake.org/cmake/help/latest/command/separate_arguments.html#command:separate_arguments) `UNIX_COMMAND`模式。例如， 变成。`"SHELL:-option A" "SHELL:-option B"``-option A -option B`

## 处理编译器驱动程序差异

要将选项传递给链接器工具，每个编译器驱动程序都有自己的语法。`LINKER:`前缀和分隔符可用于以可移植的`,`方式指定传递给链接器工具的选项。`LINKER:`由适当的驱动程序选项和`,`适当的驱动程序分隔符替换。驱动程序前缀和驱动程序分隔符由 [`CMAKE__LINKER_WRAPPER_FLAG`](https://cmake.org/cmake/help/latest/variable/CMAKE_LANG_LINKER_WRAPPER_FLAG.html#variable:CMAKE__LINKER_WRAPPER_FLAG)和 [`CMAKE__LINKER_WRAPPER_FLAG_SEP`](https://cmake.org/cmake/help/latest/variable/CMAKE_LANG_LINKER_WRAPPER_FLAG_SEP.html#variable:CMAKE__LINKER_WRAPPER_FLAG_SEP)变量。

例如，`"LINKER:-z,defs"`变为for 和for 。`-Xlinker -z -Xlinker defs``Clang``-Wl,-z,defs``GNU GCC`

`LINKER:`前缀可以指定为`SHELL:`前缀表达式的一部分。

`LINKER:`作为替代语法，前缀支持使用前缀和空格作为分隔符的参数规范`SHELL:`。前面的例子就变成了`"LINKER:SHELL:-z defs"`


> **笔记** 不支持在前缀`SHELL:`开头以外的任何位置 指定前缀。`LINKER:`

 

# [add_subdirectory](https://cmake.org/cmake/help/latest/command/add_subdirectory.html)

将子目录添加到构建。

```cmake
add_subdirectory(source_dir [binary_dir] [EXCLUDE_FROM_ALL])
```

将子目录添加到构建。source_dir 指定源 CMakeLists.txt 和代码文件所在的目录。如果它是相对路径，它将相对于当前目录进行评估（典型用法），但它也可能是绝对路径。`binary_dir`指定放置输出文件的目录。如果它是相对路径，它将相对于当前输出目录进行评估，但它也可能是绝对路径。如果`binary_dir`未指定，则 在展开`source_dir`任何相对路径之前，将使用 的值（典型用法）。指定源目录中的 CMakeLists.txt 文件将由 CMake 立即处理，然后在当前输入文件中的处理继续超出此命令。

如果`EXCLUDE_FROM_ALL`提供了参数，则默认情况下子目录中的目标不会包含在`ALL`父目录的目标中，并且将从 IDE 项目文件中排除。用户必须在子目录中显式构建目标。这适用于子目录包含项目的单独部分有用但不必要的情况，例如一组示例。通常子目录应该包含它自己的[`project()`](https://cmake.org/cmake/help/latest/command/project.html#command:project) 命令调用，以便在子目录中生成完整的构建系统（例如 VS IDE 解决方案文件）。请注意，目标间依赖项取代了此排除项。如果父项目构建的目标依赖于子目录中的目标，则依赖目标将包含在父项目构建系统中以满足依赖关系。



# [aux_source_directory](https://cmake.org/cmake/help/latest/command/aux_source_directory.html)

查找目录中的所有源文件。

```cmake
aux_source_directory(<dir> <variable>)
```

收集指定目录中所有源文件的名称，并将列表存储在`<variable>`提供的. 此命令旨在供使用显式模板实例化的项目使用。模板实例化文件可以存储在 `Templates`子目录中，并使用此命令自动收集，以避免手动列出所有实例化。

使用此命令来避免为库或可执行目标编写源文件列表是很有诱惑力的。虽然这似乎可行，但 CMake 无法生成一个知道何时添加新源文件的构建系统。通常，生成的构建系统知道何时需要重新运行 CMake，因为`CMakeLists.txt`文件已被修改以添加新源。当源只是添加到目录而不修改此文件时，必须手动重新运行 CMake 以生成包含新文件的构建系统。



# [build_command](https://cmake.org/cmake/help/latest/command/build_command.html)

获取命令行来构建当前项目。这主要是供内部使用的[`CTest`](https://cmake.org/cmake/help/latest/module/CTest.html#module:CTest)模块。

```cmake
build_command(<variable>
              [CONFIGURATION <config>]
              [PARALLEL_LEVEL <parallel>]
              [TARGET <target>]
              [PROJECT_NAME <projname>] # legacy, causes warning
             )
```

将给定的形式设置`<variable>`为命令行字符串：

```cmake
<cmake> --build . [--config <config>] [--parallel <parallel>] [--target <target>...] [-- -i]
```

`<cmake>`的位置在哪里[`cmake(1)`](https://cmake.org/cmake/help/latest/manual/cmake.1.html#manual:cmake(1))命令行工具和`<config>`,`<parallel>`和`<target>`是提供给`CONFIGURATION`,`PARALLEL_LEVEL`和`TARGET` 选项（如果有）的值。如果策略，则为 [Makefile Generators](https://cmake.org/cmake/help/latest/manual/cmake-generators.7.html#makefile-generators)添加尾随选项`-- -i`[`CMP0061`](https://cmake.org/cmake/help/latest/policy/CMP0061.html#policy:CMP0061)未设置为 `NEW`。

调用时，此命令行将启动底层构建系统工具。`cmake --build`

*3.21 新版功能：*该`PARALLEL_LEVEL`参数可用于设置`--parallel` 标志。

```cmake
build_command(<cachevariable> <makecommand>)
```

第二个签名已弃用，但仍可用于向后兼容。请改用第一个签名。

如上所述，它将给定`<cachevariable>`设置为命令行字符串，但没有`--target`选项。被`<makecommand>`忽略，但应该是 devenv、nmake、make 或用于遗留调用的最终用户构建工具之一的完整路径。

> **笔记 **在 3.0 之前的 CMake 版本中，此命令返回一个命令行，该命令行直接调用当前生成器的本机构建工具。他们对该`PROJECT_NAME`选项的实现没有任何有用的效果，因此 CMake 现在会在使用该选项时发出警告。

 

# [define_property](https://cmake.org/cmake/help/latest/command/define_property.html)

定义和记录自定义属性。

```cmake
define_property(<GLOBAL | DIRECTORY | TARGET | SOURCE |
                 TEST | VARIABLE | CACHED_VARIABLE>
                 PROPERTY <name> [INHERITED]
                 [BRIEF_DOCS <brief-doc> [docs...]]
                 [FULL_DOCS <full-doc> [docs...]]
                 [INITIALIZE_FROM_VARIABLE <variable>])
```

在范围内定义一个属性以用于[`set_property()`](https://cmake.org/cmake/help/latest/command/set_property.html#command:set_property)和 [`get_property()`](https://cmake.org/cmake/help/latest/command/get_property.html#command:get_property)命令。它主要用于定义属性的初始化或继承方式。从历史上看，该命令还将文档与属性相关联，但这不再被视为主要用例。

第一个参数确定应使用属性的范围类型。它必须是以下之一：

```cmake
GLOBAL    = associated with the global namespace
DIRECTORY = associated with one directory
TARGET    = associated with one target
SOURCE    = associated with one source file
TEST      = associated with a test named with add_test
VARIABLE  = documents a CMake language variable
CACHED_VARIABLE = documents a CMake cache variable
```

请注意，不像[`set_property()`](https://cmake.org/cmake/help/latest/command/set_property.html#command:set_property)和[`get_property()`](https://cmake.org/cmake/help/latest/command/get_property.html#command:get_property)无需给出实际范围；只有范围的种类很重要。

required`PROPERTY`选项后面紧跟正在定义的属性的名称。

如果`INHERITED`给出选项，则[`get_property()`](https://cmake.org/cmake/help/latest/command/get_property.html#command:get_property)当请求的属性未设置在给定命令的范围内时，命令将链接到下一个更高的范围。

- `DIRECTORY`范围链到其父目录的范围，继续向上遍历父目录，直到目录具有属性集或不再有父目录。如果在顶级目录中仍未找到，则链接到`GLOBAL`范围。
- `TARGET`,`SOURCE`和`TEST`属性链到`DIRECTORY`范围，包括根据需要进一步链接目录等。

请注意，此范围链接行为仅适用于调用 [`get_property()`](https://cmake.org/cmake/help/latest/command/get_property.html#command:get_property), [`get_directory_property()`](https://cmake.org/cmake/help/latest/command/get_directory_property.html#command:get_directory_property), [`get_target_property()`](https://cmake.org/cmake/help/latest/command/get_target_property.html#command:get_target_property),[`get_source_file_property()`](https://cmake.org/cmake/help/latest/command/get_source_file_property.html#command:get_source_file_property)和 [`get_test_property()`](https://cmake.org/cmake/help/latest/command/get_test_property.html#command:get_test_property). *设置* 属性时没有继承行为，因此使用`APPEND`or`APPEND_STRING`与 [`set_property()`](https://cmake.org/cmake/help/latest/command/set_property.html#command:set_property)在计算要附加到的内容时，命令不会考虑继承的值。

`BRIEF_DOCS`和`FULL_DOCS`选项后面是与属性相关联的字符串，作为其简短和完整的文档。CMake 不使用此文档，而是通过相应选项将其提供给项目[`get_property()`](https://cmake.org/cmake/help/latest/command/get_property.html#command:get_property)命令。

*在 3.23 版更改:*和`BRIEF_DOCS`选项`FULL_DOCS`是可选的。

*3.23 版中的新功能：*该`INITIALIZE_FROM_VARIABLE`选项指定一个变量，应从该变量初始化属性。它只能与目标属性一起使用。名称必须以属性名称结尾，`<variable>`不能以`CMAKE_`or开头`_CMAKE_`。属性名称必须至少包含一个下划线。建议属性名称具有特定于项目的前缀。



# [enable_language](https://cmake.org/cmake/help/latest/command/enable_language.html)

启用一种语言（CXX/C/OBJC/OBJCXX/Fortran/等）

```cmake
enable_language(<lang> [OPTIONAL] )
```

在 CMake 中启用对命名语言的支持。这与[`project()`](https://cmake.org/cmake/help/latest/command/project.html#command:project)命令，但不会创建由 project 命令创建的任何额外变量。示例语言为`CXX`, `C`, `CUDA`, `OBJC`, `OBJCXX`, `Fortran`, `HIP`, `ISPC`, 和`ASM`.

*3.8 版中的新功能：*添加`CUDA`了支持。

*3.16 版新功能：*添加`OBJC`和`OBJCXX`支持。

*3.18 版中的新功能：*添加`ISPC`了支持。

*3.21 版中的新功能：*添加`HIP`了支持。

如果启用`ASM`，请最后启用它，以便 CMake 可以检查其他语言的编译器是否也`C`适用于汇编。

此命令必须在文件范围内调用，而不是在函数调用中。此外，它必须在所有使用命名语言的目标通用的最高目录中直接调用，以编译源代码或通过链接依赖项间接调用。在项目的顶级目录中启用所有需要的语言是最简单的。

该`OPTIONAL`关键字是未来实施的占位符，目前不起作用。相反，您可以使用[`CheckLanguage`](https://cmake.org/cmake/help/latest/module/CheckLanguage.html#module:CheckLanguage) 模块在启用之前验证支持。



# [export](https://cmake.org/cmake/help/latest/command/export.html)

导出外部项目的目标或包，以直接从当前项目的构建树中使用它们，无需安装。

见[`install(EXPORT)`](https://cmake.org/cmake/help/latest/command/install.html#command:install)命令从安装树中导出目标。

## Synopsis

```cmake
出口（目标<目标>... [...]）
出口（出口<出口名称> [...]）
出口（包<包名>）
```

## 导出目标



```cmake
export(TARGETS <target>... [NAMESPACE <namespace>]
       [APPEND] FILE <filename> [EXPORT_LINK_INTERFACE_LIBRARIES])
```

创建一个`<filename>`可能被外部项目包含的文件，以`<target>...`从当前项目的构建树中导入名为 by 的目标。这在交叉编译过程中很有用，可以在一个项目中构建可以在主机平台上运行的实用程序可执行文件，然后将它们导入到正在为目标平台编译的另一个项目中。

此命令创建的文件特定于构建树，不应安装。见[`install(EXPORT)`](https://cmake.org/cmake/help/latest/command/install.html#command:install)命令从安装树中导出目标。

选项包括：

- `NAMESPACE <namespace>`

  将`<namespace>`字符串添加到写入文件的所有目标名称中。

- `APPEND`

  附加到文件而不是覆盖它。这可用于将多个目标增量导出到同一个文件。

- `EXPORT_LINK_INTERFACE_LIBRARIES`

  在导出中包含以模式命名的属性的内容 `(IMPORTED_)?LINK_INTERFACE_LIBRARIES(_<CONFIG>)?` ，即使策略[`CMP0022`](https://cmake.org/cmake/help/latest/policy/CMP0022.html#policy:CMP0022)是新的。这对于支持使用早于 2.8.12 的 CMake 版本的消费者很有用。

此签名要求明确列出所有目标。如果导出中包含库目标，但不包含它链接到的目标，则行为未指定。查看[export(EXPORT)](https://cmake.org/cmake/help/latest/command/export.html#export-export)签名以自动从构建树中导出相同的目标 [`install(EXPORT)`](https://cmake.org/cmake/help/latest/command/install.html#command:install)将来自安装树。

笔记

 

[对象库](https://cmake.org/cmake/help/latest/manual/cmake-buildsystem.7.html#object-libraries)下[`Xcode`](https://cmake.org/cmake/help/latest/generator/Xcode.html#generator:Xcode)如果在中列出了多个架构，请进行特殊处理[`CMAKE_OSX_ARCHITECTURES`](https://cmake.org/cmake/help/latest/variable/CMAKE_OSX_ARCHITECTURES.html#variable:CMAKE_OSX_ARCHITECTURES). 在这种情况下，它们将作为[接口库](https://cmake.org/cmake/help/latest/manual/cmake-buildsystem.7.html#interface-libraries)导出，客户端没有可用的目标文件。这足以满足在其实现中链接到对象库的其他目标的传递使用要求。

### 将目标导出到 Android.mk 

```cmake
export(TARGETS <target>... ANDROID_MK <filename>)
```

*3.7 版中的新功能。*

此签名通过创建`Android.mk`引用预构建目标的文件将 cmake 构建目标导出到 android ndk 构建系统。Android NDK 支持使用预建库，包括静态库和共享库。这允许 cmake 构建项目的库，并使它们可用于具有传递依赖项的 ndk 构建系统，包括使用这些库所需的标志和定义。签名采用目标列表并将它们放在给定`Android.mk`指定的文件中 `<filename>`。此签名仅可用于政策 [`CMP0022`](https://cmake.org/cmake/help/latest/policy/CMP0022.html#policy:CMP0022)对于给定的所有目标都是新的。如果该政策针对其中一个目标设置为 OLD，则会发出错误。

## 导出目标匹配安装(EXPORT) 

```cmake
export(EXPORT <export-name> [NAMESPACE <namespace>] [FILE <filename>])
```

创建一个`<filename>`可能被外部项目包含的文件，以从当前项目的构建树中导入目标。这与[export(TARGETS)](https://cmake.org/cmake/help/latest/command/export.html#export-targets)签名相同，只是没有明确列出目标。相反，它会导出与安装 export 关联的目标`<export-name>`。目标安装可以`<export-name>`使用`EXPORT`选项与导出相关联[`install(TARGETS)`](https://cmake.org/cmake/help/latest/command/install.html#command:install)命令。

## 导出包



```cmake
export(PACKAGE <PackageName>)
```

将当前构建目录存储在 package 的 CMake 用户包注册表中`<PackageName>`。这[`find_package()`](https://cmake.org/cmake/help/latest/command/find_package.html#command:find_package)命令在搜索 package 时可能会考虑目录`<PackageName>`。这有助于依赖项目从当前项目的构建树中查找和使用包，而无需用户的帮助。请注意，此命令在包注册表中创建的条目仅与与`<PackageName>Config.cmake`构建树一起使用的包配置文件 ( ) 一起工作。在某些情况下，例如对于打包和系统范围的安装，不需要编写用户包注册表。

*在 3.1 版更改:*如果[`CMAKE_EXPORT_NO_PACKAGE_REGISTRY`](https://cmake.org/cmake/help/latest/variable/CMAKE_EXPORT_NO_PACKAGE_REGISTRY.html#variable:CMAKE_EXPORT_NO_PACKAGE_REGISTRY)变量已启用，该`export(PACKAGE)`命令将不执行任何操作。

*在 3.15 版更改：*默认情况下，该`export(PACKAGE)`命令不执行任何操作（请参阅策略 [`CMP0090`](https://cmake.org/cmake/help/latest/policy/CMP0090.html#policy:CMP0090)) 因为填充用户包注册表会在源代码和构建树之外产生影响。设置 [`CMAKE_EXPORT_PACKAGE_REGISTRY`](https://cmake.org/cmake/help/latest/variable/CMAKE_EXPORT_PACKAGE_REGISTRY.html#variable:CMAKE_EXPORT_PACKAGE_REGISTRY)变量以将构建目录添加到 CMake 用户包注册表。



# [fltk_wrap_ui](https://cmake.org/cmake/help/latest/command/fltk_wrap_ui.html)

创建 FLTK 用户界面包装器。

```cmake
fltk_wrap_ui(resultingLibraryName source1
             source2 ... sourceN )
```

为列出的所有 .fl 和 .fld 文件生成 .h 和 .cxx 文件。生成的 .h 和 .cxx 文件将添加到名为的变量中，该变量 `resultingLibraryName_FLTK_UI_SRCS`应添加到您的库中。



# [get_source_file_property](https://cmake.org/cmake/help/latest/command/get_source_file_property.html)

获取源文件的属性。

```cmake
get_source_file_property(<variable> <file>
                         [DIRECTORY <dir> | TARGET_DIRECTORY <target>]
                         <property>)
```

从源文件中获取属性。属性的值存储在指定的`<variable>`. 如果未找到源属性，则行为取决于它是否已被定义为`INHERITED` 属性（请参阅[`define_property()`](https://cmake.org/cmake/help/latest/command/define_property.html#command:define_property)）。非继承属性将设置`variable`为`NOTFOUND`，而继承属性将搜索相关的父范围，如[`define_property()`](https://cmake.org/cmake/help/latest/command/define_property.html#command:define_property) 命令，如果仍然无法找到该属性，`variable`将设置为空字符串。

默认情况下，源文件的属性将从当前源目录的范围中读取。

*3.18 版中的新增功能：*目录范围可以用以下子选项之一覆盖：

- `DIRECTORY <dir>`

  源文件属性将从`<dir>`目录的范围中读取。CMake 必须已经知道该源目录，或者通过调用添加它[`add_subdirectory()`](https://cmake.org/cmake/help/latest/command/add_subdirectory.html#command:add_subdirectory)或`<dir>` 作为顶级源目录。相对路径被视为相对于当前源目录。

- `TARGET_DIRECTORY <target>`

  源文件属性将从 `<target>`创建的目录范围中读取（`<target>`因此必须已经存在）。

利用[`set_source_files_properties()`](https://cmake.org/cmake/help/latest/command/set_source_files_properties.html#command:set_source_files_properties)设置属性值。源文件属性通常控制文件的构建方式。一种永远存在的属性[`LOCATION`](https://cmake.org/cmake/help/latest/prop_sf/LOCATION.html#prop_sf:LOCATION).

另见更一般的[`get_property()`](https://cmake.org/cmake/help/latest/command/get_property.html#command:get_property)命令。

> **笔记** 这[`GENERATED`](https://cmake.org/cmake/help/latest/prop_sf/GENERATED.html#prop_sf:GENERATED)源文件属性可能是全局可见的。有关详细信息，请参阅其文档。

 

# [get_target_property](https://cmake.org/cmake/help/latest/command/get_target_property.html)

从目标获取属性。

```cmake
get_target_property(<VAR> target property)
```

从目标获取属性。属性的值存储在变量中`<VAR>`。如果未找到目标属性，则行为取决于它是否已被定义为`INHERITED`属性（请参阅[`define_property()`](https://cmake.org/cmake/help/latest/command/define_property.html#command:define_property)）。非继承属性将设置`<VAR>`为`<VAR>-NOTFOUND`，而继承属性将搜索相关的父范围，如[`define_property()`](https://cmake.org/cmake/help/latest/command/define_property.html#command:define_property) 命令，如果仍然无法找到该属性，`<VAR>`将设置为空字符串。

利用[`set_target_properties()`](https://cmake.org/cmake/help/latest/command/set_target_properties.html#command:set_target_properties)设置目标属性值。属性通常用于控制如何构建目标，但有些是查询目标。此命令可以获取迄今为止创建的任何目标的属性。目标不需要在当前 `CMakeLists.txt`文件中。

另见更一般的[`get_property()`](https://cmake.org/cmake/help/latest/command/get_property.html#command:get_property)命令。

有关CMake 已知的属性列表，请参阅[目标上的属性。](https://cmake.org/cmake/help/latest/manual/cmake-properties.7.html#target-properties)



# [include_directories](https://cmake.org/cmake/help/latest/command/include_directories.html)

将包含目录添加到构建中。

```cmake
include_directories([AFTER|BEFORE] [SYSTEM] dir1 [dir2 ...])
```

将给定目录添加到编译器用于搜索包含文件的目录。相对路径被解释为相对于当前源目录。

包含目录被添加到[`INCLUDE_DIRECTORIES`](https://cmake.org/cmake/help/latest/prop_dir/INCLUDE_DIRECTORIES.html#prop_dir:INCLUDE_DIRECTORIES) 当前`CMakeLists`文件的目录属性。它们也被添加到[`INCLUDE_DIRECTORIES`](https://cmake.org/cmake/help/latest/prop_tgt/INCLUDE_DIRECTORIES.html#prop_tgt:INCLUDE_DIRECTORIES)`CMakeLists`当前文件中每个目标的目标属性。目标属性值是生成器使用的属性值。

默认情况下，指定的目录会附加到当前目录列表中。可以通过设置更改此默认行为 [`CMAKE_INCLUDE_DIRECTORIES_BEFORE`](https://cmake.org/cmake/help/latest/variable/CMAKE_INCLUDE_DIRECTORIES_BEFORE.html#variable:CMAKE_INCLUDE_DIRECTORIES_BEFORE)到`ON`. 通过使用 `AFTER`or`BEFORE`显式，您可以在附加和前置之间进行选择，而与默认值无关。

如果`SYSTEM`给出该选项，编译器将被告知这些目录是某些平台上的系统包含目录。发出此设置的信号可能会产生诸如编译器跳过警告之类的效果，或者这些固定安装的系统文件在依赖关系计算中不被考虑 - 请参阅编译器文档。

参数 to`include_directories`可以使用语法为“$<...>”的“生成器表达式”。见[`cmake-generator-expressions(7)`](https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html#manual:cmake-generator-expressions(7)) 可用表达式的手册。见[`cmake-buildsystem(7)`](https://cmake.org/cmake/help/latest/manual/cmake-buildsystem.7.html#manual:cmake-buildsystem(7)) 有关定义构建系统属性的更多信息。

> **笔记 **更喜欢[`target_include_directories()`](https://cmake.org/cmake/help/latest/command/target_include_directories.html#command:target_include_directories)命令将包含目录添加到各个目标，并可选择将它们传播/导出到依赖项。

 

# [include_external_msproject](https://cmake.org/cmake/help/latest/command/include_external_msproject.html)

在工作区中包含一个外部 Microsoft 项目文件。

```cmake
include_external_msproject(projectname location
                           [TYPE projectTypeGUID]
                           [GUID projectGUID]
                           [PLATFORM platformName]
                           dep1 dep2 ...)
```

在生成的工作区文件中包含一个外部 Microsoft 项目。目前在 UNIX 上什么都不做。这将创建一个名为`[projectname]`. 这可以用于[`add_dependencies()`](https://cmake.org/cmake/help/latest/command/add_dependencies.html#command:add_dependencies) 命令使事情依赖于外部项目。

`TYPE`,`GUID`和`PLATFORM`是可选参数，允许指定项目的类型、项目的 id ( `GUID`) 和目标平台的名称。这对于需要非默认值的项目（例如 WIX 项目）很有用。

*3.9 新功能：*如果导入的项目与当前项目的配置名称不同，请设置[`MAP_IMPORTED_CONFIG_`](https://cmake.org/cmake/help/latest/prop_tgt/MAP_IMPORTED_CONFIG_CONFIG.html#prop_tgt:MAP_IMPORTED_CONFIG_) target 属性来指定映射。



# [include_regular_expression](https://cmake.org/cmake/help/latest/command/include_regular_expression.html)

设置用于依赖检查的正则表达式。

```cmake
include_regular_expression(regex_match [regex_complain])
```

设置在依赖检查中使用的正则表达式。只有匹配的文件`regex_match`才会被跟踪为依赖项。`regex_complain`如果找不到匹配的文件（不搜索标准头路径），则只有匹配的文件才会生成警告。默认值为：

```cmake
regex_match    = "^.*$" (match everything)
regex_complain = "^$" (match empty string only)
```



# [install](https://cmake.org/cmake/help/latest/command/install.html)

指定在安装时运行的规则。

## Synopsis

```cmake
安装（目标<目标>... [...]）
安装（IMPORTED_RUNTIME_ARTIFACTS <目标>... [...]）
安装（{文件|程序} <文件>... [...]）
安装（目录<目录>... [...]）
安装（脚本<文件> [...]）
安装（代码<代码> [...]）
安装（出口<出口名称> [...]）
安装（RUNTIME_DEPENDENCY_SET <set-name> [...]）
```

## Introduction

此命令为项目生成安装规则。通过调用`install()`源目录中的命令指定的安装规则在安装期间按顺序执行。

*在 3.14 版更改:*在通过调用添加的子目录中安装规则[`add_subdirectory()`](https://cmake.org/cmake/help/latest/command/add_subdirectory.html#command:add_subdirectory)命令与父目录中的命令交错以按声明的顺序运行（请参阅策略[`CMP0082`](https://cmake.org/cmake/help/latest/policy/CMP0082.html#policy:CMP0082)).

*在 3.22 版更改:*环境变量[`CMAKE_INSTALL_MODE`](https://cmake.org/cmake/help/latest/envvar/CMAKE_INSTALL_MODE.html#envvar:CMAKE_INSTALL_MODE)可以覆盖的默认复制行为[`install()`](https://cmake.org/cmake/help/latest/command/install.html#command:install).

此命令有多个签名。其中一些定义了文件和目标的安装选项。此处涵盖了多个签名共有的选项，但它们仅对指定它们的签名有效。常见的选项是：

- `DESTINATION`

  指定要安装文件的磁盘目录。参数可以是相对路径或绝对路径。如果给出了相对路径，则相对于[`CMAKE_INSTALL_PREFIX`](https://cmake.org/cmake/help/latest/variable/CMAKE_INSTALL_PREFIX.html#variable:CMAKE_INSTALL_PREFIX)多变的。前缀可以在安装时使用中`DESTDIR` 解释的机制重新定位[`CMAKE_INSTALL_PREFIX`](https://cmake.org/cmake/help/latest/variable/CMAKE_INSTALL_PREFIX.html#variable:CMAKE_INSTALL_PREFIX)可变文档。如果给出了绝对路径（带有前导斜杠或驱动器号），则将逐字使用。由于不支持绝对路径[`cpack`](https://cmake.org/cmake/help/latest/manual/cpack.1.html#manual:cpack(1))安装程序生成器，最好始终使用相对路径。特别是，不需要通过前置来使路径成为绝对路径 [`CMAKE_INSTALL_PREFIX`](https://cmake.org/cmake/help/latest/variable/CMAKE_INSTALL_PREFIX.html#variable:CMAKE_INSTALL_PREFIX); 如果 DESTINATION 是相对路径，则默认使用此前缀。

- `PERMISSIONS`

  指定已安装文件的权限。有效权限为 `OWNER_READ`, `OWNER_WRITE`, `OWNER_EXECUTE`, `GROUP_READ`, `GROUP_WRITE`, `GROUP_EXECUTE`, `WORLD_READ`, `WORLD_WRITE`, `WORLD_EXECUTE`, `SETUID`, 和`SETGID`. 在某些平台上没有意义的权限在这些平台上会被忽略。

- `CONFIGURATIONS`

  指定安装规则适用的构建配置列表（调试、发布等）。请注意，为此选项指定的值仅适用于选项之后列出的`CONFIGURATIONS` 选项。例如，要为 Debug 和 Release 配置设置单独的安装路径，请执行以下操作：`install(TARGETS target        CONFIGURATIONS Debug        RUNTIME DESTINATION Debug/bin) install(TARGETS target        CONFIGURATIONS Release        RUNTIME DESTINATION Release/bin) `请注意，`CONFIGURATIONS`出现在 BEFORE 之前。`RUNTIME DESTINATION`

- `COMPONENT`

  指定与安装规则关联的安装组件名称，例如`Runtime`或`Development`。在特定于组件的安装期间，只会执行与给定组件名称关联的安装规则。在完全安装期间，所有组件都会安装，除非标有`EXCLUDE_FROM_ALL`。如果`COMPONENT`未提供，则创建默认组件“未指定”。默认组件名称可以通过 [`CMAKE_INSTALL_DEFAULT_COMPONENT_NAME`](https://cmake.org/cmake/help/latest/variable/CMAKE_INSTALL_DEFAULT_COMPONENT_NAME.html#variable:CMAKE_INSTALL_DEFAULT_COMPONENT_NAME)多变的。

- `EXCLUDE_FROM_ALL`

  *3.6 版中的新功能。*指定该文件从完整安装中排除，并且仅作为特定组件安装的一部分进行安装

- `RENAME`

  指定可能与原始文件不同的已安装文件的名称。仅当该命令安装了单个文件时才允许重命名。

- `OPTIONAL`

  如果要安装的文件不存在，则指定它不是错误。

*3.1 版新功能：*安装文件的命令签名可能会在安装期间打印消息。使用[`CMAKE_INSTALL_MESSAGE`](https://cmake.org/cmake/help/latest/variable/CMAKE_INSTALL_MESSAGE.html#variable:CMAKE_INSTALL_MESSAGE)变量来控制打印哪些消息。

*3.11 版新功能：*许多`install()`变体隐式创建包含已安装文件的目录。如果 [`CMAKE_INSTALL_DEFAULT_DIRECTORY_PERMISSIONS`](https://cmake.org/cmake/help/latest/variable/CMAKE_INSTALL_DEFAULT_DIRECTORY_PERMISSIONS.html#variable:CMAKE_INSTALL_DEFAULT_DIRECTORY_PERMISSIONS)设置后，将使用指定的权限创建这些目录。否则，它们将根据类 Unix 平台上的 uname 规则创建。Windows 平台不受影响。

## 安装目标



```cmake
install(TARGETS targets... [EXPORT <export-name>]
        [RUNTIME_DEPENDENCIES args...|RUNTIME_DEPENDENCY_SET <set-name>]
        [[ARCHIVE|LIBRARY|RUNTIME|OBJECTS|FRAMEWORK|BUNDLE|
          PRIVATE_HEADER|PUBLIC_HEADER|RESOURCE|FILE_SET <set-name>]
         [DESTINATION <dir>]
         [PERMISSIONS permissions...]
         [CONFIGURATIONS [Debug|Release|...]]
         [COMPONENT <component>]
         [NAMELINK_COMPONENT <component>]
         [OPTIONAL] [EXCLUDE_FROM_ALL]
         [NAMELINK_ONLY|NAMELINK_SKIP]
        ] [...]
        [INCLUDES DESTINATION [<dir> ...]]
        )
```

该`TARGETS`表单指定了从项目安装目标的规则。 可以安装几种目标[输出工件：](https://cmake.org/cmake/help/latest/manual/cmake-buildsystem.7.html#output-artifacts)

- `ARCHIVE`

  此类目标工件包括：*静态库* （在 macOS 上标记为 时除外`FRAMEWORK`，见下文）；*DLL 导入库* （在包括 Cygwin 在内的所有基于 Windows 的系统上；它们具有扩展名 `.lib`，与转到的`.dll`库相反`RUNTIME`）；在 AIX 上，为可执行文件创建 的*链接器导入文件*[`ENABLE_EXPORTS`](https://cmake.org/cmake/help/latest/prop_tgt/ENABLE_EXPORTS.html#prop_tgt:ENABLE_EXPORTS)启用。

- `LIBRARY`

  此类目标工件包括：*共享库*，除了DLL（这些转到`RUNTIME`，见下文），在 macOS 上标记为`FRAMEWORK`（见下文）。

- `RUNTIME`

  此类目标工件包括：*可执行文件* （在 macOS 上标记为 时除外`MACOSX_BUNDLE`，见`BUNDLE`下文）；DLL（在所有基于 Windows 的系统上，包括 Cygwin；请注意随附的导入库是 kind `ARCHIVE`）。

- `OBJECTS`

  *3.9 版中的新功能。**与对象库*关联的对象文件。

- `FRAMEWORK`

  标有该属性的静态库和共享库`FRAMEWORK` 都被视为`FRAMEWORK`macOS 上的目标。

- `BUNDLE`

  标有[`MACOSX_BUNDLE`](https://cmake.org/cmake/help/latest/prop_tgt/MACOSX_BUNDLE.html#prop_tgt:MACOSX_BUNDLE)`BUNDLE`属性在 macOS 上被视为 目标。

- `PUBLIC_HEADER`

  任何[`PUBLIC_HEADER`](https://cmake.org/cmake/help/latest/prop_tgt/PUBLIC_HEADER.html#prop_tgt:PUBLIC_HEADER)与库关联的文件安装在`PUBLIC_HEADER`非 Apple 平台上由参数指定的目标位置。此参数定义的规则被忽略[`FRAMEWORK`](https://cmake.org/cmake/help/latest/prop_tgt/FRAMEWORK.html#prop_tgt:FRAMEWORK) Apple 平台上的库，因为相关文件已安装到框架文件夹内的适当位置。看 [`PUBLIC_HEADER`](https://cmake.org/cmake/help/latest/prop_tgt/PUBLIC_HEADER.html#prop_tgt:PUBLIC_HEADER)详情。

- `PRIVATE_HEADER`

  类似于`PUBLIC_HEADER`，但用于`PRIVATE_HEADER`文件。看 [`PRIVATE_HEADER`](https://cmake.org/cmake/help/latest/prop_tgt/PRIVATE_HEADER.html#prop_tgt:PRIVATE_HEADER)详情。

- `RESOURCE`

  类似于`PUBLIC_HEADER`and `PRIVATE_HEADER`，但用于 `RESOURCE`文件。看[`RESOURCE`](https://cmake.org/cmake/help/latest/prop_tgt/RESOURCE.html#prop_tgt:RESOURCE)详情。

- `FILE_SET <set>`

  *版本 3.23 中的新功能。*文件集由[`target_sources(FILE_SET)`](https://cmake.org/cmake/help/latest/command/target_sources.html#command:target_sources)命令。如果文件集`<set>`存在并且是`PUBLIC`or `INTERFACE`，则该文件集中的任何文件都安装在目标下（见下文）。相对于文件集的基本目录的目录结构被保留。例如， `/blah/include/myproj/here.h`与基本目录一样添加到文件集的文件`/blah/include` 将安装到`myproj/here.h`目标下方。

对于给定的每个参数，它们后面的参数仅适用于参数中指定的目标或文件类型。如果没有给出，则安装属性适用于所有目标类型。如果只给出一个，那么只会安装该类型的目标（可用于仅安装 DLL 或仅安装导入库。）

对于常规可执行文件、静态库和共享库，该 `DESTINATION`参数不是必需的。对于这些目标类型，当 `DESTINATION`省略时，将从中的适当变量中获取默认目标[`GNUInstallDirs`](https://cmake.org/cmake/help/latest/module/GNUInstallDirs.html#module:GNUInstallDirs)，或者如果未定义该变量，则设置为内置默认值。这同样适用于文件集，以及通过[`PUBLIC_HEADER`](https://cmake.org/cmake/help/latest/prop_tgt/PUBLIC_HEADER.html#prop_tgt:PUBLIC_HEADER)和[`PRIVATE_HEADER`](https://cmake.org/cmake/help/latest/prop_tgt/PRIVATE_HEADER.html#prop_tgt:PRIVATE_HEADER) 目标属性。必须始终为模块库、Apple 包和框架提供目的地。接口和对象库可以省略目标，但它们的处理方式不同（请参阅本节末尾对本主题的讨论）。

下表显示了目标类型及其关联变量和在未指定目标时适用的内置默认值：

| 目标类型                    | GNUInstallDirs 变量           | 内置默认值 |
| :-------------------------- | :---------------------------- | :--------- |
| `RUNTIME`                   | `${CMAKE_INSTALL_BINDIR}`     | `bin`      |
| `LIBRARY`                   | `${CMAKE_INSTALL_LIBDIR}`     | `lib`      |
| `ARCHIVE`                   | `${CMAKE_INSTALL_LIBDIR}`     | `lib`      |
| `PRIVATE_HEADER`            | `${CMAKE_INSTALL_INCLUDEDIR}` | `include`  |
| `PUBLIC_HEADER`             | `${CMAKE_INSTALL_INCLUDEDIR}` | `include`  |
| `FILE_SET`（类型`HEADERS`） | `${CMAKE_INSTALL_INCLUDEDIR}` | `include`  |

希望遵循将标头安装到项目特定子目录的常见做法的项目可能更喜欢使用具有适当路径和基本目录的文件集。否则，他们必须提供一个`DESTINATION` 而不是能够依赖上述内容（参见下面的下一个示例）。

为了使包符合分发文件系统布局策略，如果项目必须指定 a `DESTINATION`，建议他们使用以适当的开头的路径[`GNUInstallDirs`](https://cmake.org/cmake/help/latest/module/GNUInstallDirs.html#module:GNUInstallDirs)多变的。这允许包维护者通过设置适当的缓存变量来控制安装目标。以下示例显示了一个静态库正在安装到由提供的默认目标 [`GNUInstallDirs`](https://cmake.org/cmake/help/latest/module/GNUInstallDirs.html#module:GNUInstallDirs)，但其标头安装到项目特定的子目录而不使用文件集：

```cmake
add_library(mylib STATIC ...)
set_target_properties(mylib PROPERTIES PUBLIC_HEADER mylib.h)
include(GNUInstallDirs)
install(TARGETS mylib
        PUBLIC_HEADER
          DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/myproj
)
```

除了上面列出的常用选项之外，每个目标都可以接受以下附加参数：

- `NAMELINK_COMPONENT`

  *版本 3.12 中的新功能。*在某些平台上，版本化共享库具有符号链接，例如：`lib<name>.so -> lib<name>.so.1 `where`lib<name>.so.1`是库的 soname 并且`lib<name>.so` 是“namelink”，允许链接器在给定时找到库 `-l<name>`。该`NAMELINK_COMPONENT`选项与该选项类似 `COMPONENT`，但如果生成了共享库名称链接，它会更改安装组件。如果未指定，则默认为 的值`COMPONENT`。`LIBRARY`在块外使用此参数是错误的 。考虑以下示例：`install(TARGETS mylib        LIBRARY          COMPONENT Libraries          NAMELINK_COMPONENT Development        PUBLIC_HEADER          COMPONENT Development       ) `在这种情况下，如果您选择仅安装`Development` 组件，则标题和名称链接都将在没有库的情况下安装。（如果您不安装该`Libraries`组件，则名称链接将是一个悬空符号链接，并且链接到该库的项目将出现构建错误。）如果您只安装该`Libraries`组件，则只会安装该库，没有标题和名称链接。此选项通常用于具有单独运行时和开发包的包管理器。例如，在 Debian 系统上，库应该在 runtime 包中，而 headers 和 namelink 应该在 development 包中。见[`VERSION`](https://cmake.org/cmake/help/latest/prop_tgt/VERSION.html#prop_tgt:VERSION)和[`SOVERSION`](https://cmake.org/cmake/help/latest/prop_tgt/SOVERSION.html#prop_tgt:SOVERSION)目标属性以获取有关创建版本化共享库的详细信息。

- `NAMELINK_ONLY`

  此选项导致在安装库目标时仅安装名称链接。在版本化共享库没有名称链接或库没有版本化的平台上，该`NAMELINK_ONLY` 选项不安装任何内容。`LIBRARY`在块外使用此参数是错误的 。当`NAMELINK_ONLY`给出时，`NAMELINK_COMPONENT`或 `COMPONENT`可用于指定名称链接的安装组件，但`COMPONENT`通常应首选。

- `NAMELINK_SKIP`

  与 类似`NAMELINK_ONLY`，但效果相反：在安装库目标时，会导致安装 namelink 以外的库文件。当两者都没有`NAMELINK_ONLY`或`NAMELINK_SKIP`没有给出时，两个部分都被安装。在版本化共享库没有符号链接的平台上或库没有版本化时，`NAMELINK_SKIP` 安装该库。`LIBRARY`在块外使用此参数是错误的 。如果`NAMELINK_SKIP`指定，`NAMELINK_COMPONENT`则无效。不建议`NAMELINK_SKIP`与 `NAMELINK_COMPONENT`.

[install(TARGETS)](https://cmake.org/cmake/help/latest/command/install.html#install-targets)命令还可以在顶层接受以下选项：

- `EXPORT`

  此选项将已安装的目标文件与名为 `<export-name>`. 它必须出现在任何目标选项之前。要实际安装导出文件本身，请调用[install(EXPORT)](https://cmake.org/cmake/help/latest/command/install.html#install-export)，如下所述。参见文档[`EXPORT_NAME`](https://cmake.org/cmake/help/latest/prop_tgt/EXPORT_NAME.html#prop_tgt:EXPORT_NAME)target 属性以更改导出目标的名称。如果`EXPORT`使用并且目标包含`PUBLIC`或`INTERFACE` 文件集，则必须使用`FILE_SET`参数指定所有这些。与目标关联的所有 `PUBLIC`或文件集都包含在导出中。`INTERFACE`

- `INCLUDES DESTINATION`

  此选项指定将添加到 [`INTERFACE_INCLUDE_DIRECTORIES`](https://cmake.org/cmake/help/latest/prop_tgt/INTERFACE_INCLUDE_DIRECTORIES.html#prop_tgt:INTERFACE_INCLUDE_DIRECTORIES)`<targets>`由[install(EXPORT)](https://cmake.org/cmake/help/latest/command/install.html#install-export)命令导出时的目标属性 。如果指定了相对路径，则将其视为相对于 `$<INSTALL_PREFIX>`.

- `RUNTIME_DEPENDENCY_SET`

  *3.21 版中的新功能。*此选项会导致已安装的可执行文件、共享库和模块目标的所有运行时依赖项添加到指定的运行时依赖项集中。然后可以使用 [install(RUNTIME_DEPENDENCY_SET)](https://cmake.org/cmake/help/latest/command/install.html#install-runtime-dependency-set)命令安装此集。这个关键字和`RUNTIME_DEPENDENCIES`关键字是互斥的。

- `RUNTIME_DEPENDENCIES`

  *3.21 版中的新功能。*此选项会导致已安装的可执行文件、共享库和模块目标的所有运行时依赖项与目标本身一起安装。、`RUNTIME`、`LIBRARY`和`FRAMEWORK`通用参数用于确定这些依赖项安装的属性（`DESTINATION`、 `COMPONENT`等）。`RUNTIME_DEPENDENCIES`在语义上等价于以下一对调用：`install(TARGETS ... RUNTIME_DEPENDENCY_SET <set-name>) install(RUNTIME_DEPENDENCY_SET <set-name> args...) `where`<set-name>`将是一个随机生成的集合名称。[可能包括install(RUNTIME_DEPENDENCY_SET)](https://cmake.org/cmake/help/latest/command/install.html#install-runtime-dependency-set)命令支持的`args...`以下任何关键字：`DIRECTORIES``PRE_INCLUDE_REGEXES``PRE_EXCLUDE_REGEXES``POST_INCLUDE_REGEXES``POST_EXCLUDE_REGEXES``POST_INCLUDE_FILES``POST_EXCLUDE_FILES``RUNTIME_DEPENDENCIES`和`RUNTIME_DEPENDENCY_SET`关键字是互斥的。

`TARGETS`可以在对该命令形式的一次调用中指定一组或多组属性。一个目标可以多次安装到不同的位置。考虑假设目标`myExe`、 `mySharedLib`和`myStaticLib`。编码：

```cmake
install(TARGETS myExe mySharedLib myStaticLib
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib/static)
install(TARGETS mySharedLib DESTINATION /some/full/path)
```

将安装`myExe`到`<prefix>/bin`和`myStaticLib`到 `<prefix>/lib/static`。在非 DLL 平台`mySharedLib`上将安装到`<prefix>/lib`和`/some/full/path`. 在 DLL 平台上，`mySharedLib`DLL 将安装到`<prefix>/bin`和 `/some/full/path`，其导入库将安装到 `<prefix>/lib/static`和`/some/full/path`。

[接口库](https://cmake.org/cmake/help/latest/manual/cmake-buildsystem.7.html#interface-libraries)可能会列在要安装的目标中。他们不安装任何工件，但将包含在关联的`EXPORT`. 如果[列出了对象库](https://cmake.org/cmake/help/latest/manual/cmake-buildsystem.7.html#object-libraries)但没有为其对象文件指定目标，则它们将被导出为[接口库](https://cmake.org/cmake/help/latest/manual/cmake-buildsystem.7.html#interface-libraries)。这足以满足在其实现中链接到对象库的其他目标的传递使用要求。

安装目标[`EXCLUDE_FROM_ALL`](https://cmake.org/cmake/help/latest/prop_tgt/EXCLUDE_FROM_ALL.html#prop_tgt:EXCLUDE_FROM_ALL)目标属性设置为`TRUE`具有未定义的行为。

*3.3 版中的新功能：*作为`DESTINATION`参数给出的安装目标可以使用带有语法的“生成器表达式” `$<...>`。见 [`cmake-generator-expressions(7)`](https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html#manual:cmake-generator-expressions(7))可用表达式的手册。

*3.13 版新功能：*[install(TARGETS)](https://cmake.org/cmake/help/latest/command/install.html#install-targets)可以安装在其他目录中创建的目标。使用此类跨目录安装规则时， 从子目录运行（或类似的）将不能保证来自其他目录的目标是最新的。您可以使用 `make install`[`target_link_libraries()`](https://cmake.org/cmake/help/latest/command/target_link_libraries.html#command:target_link_libraries)或者[`add_dependencies()`](https://cmake.org/cmake/help/latest/command/add_dependencies.html#command:add_dependencies) 以确保在运行特定于子目录的安装规则之前构建此类目录外目标。

## 安装导入的运行时工件



*3.21 版中的新功能。*

```cmake
install(IMPORTED_RUNTIME_ARTIFACTS targets...
        [RUNTIME_DEPENDENCY_SET <set-name>]
        [[LIBRARY|RUNTIME|FRAMEWORK|BUNDLE]
         [DESTINATION <dir>]
         [PERMISSIONS permissions...]
         [CONFIGURATIONS [Debug|Release|...]]
         [COMPONENT <component>]
         [OPTIONAL] [EXCLUDE_FROM_ALL]
        ] [...]
        )
```

该`IMPORTED_RUNTIME_ARTIFACTS`表单指定了安装导入目标的运行时工件的规则。如果项目想要在其安装中捆绑外部可执行文件或模块，则可以这样做。、 `LIBRARY`、`RUNTIME`和参数的语义`FRAMEWORK`与`BUNDLE`它们在[TARGETS](https://cmake.org/cmake/help/latest/command/install.html#targets)模式下的语义相同。只安装导入目标的运行时工件（除了[`FRAMEWORK`](https://cmake.org/cmake/help/latest/prop_tgt/FRAMEWORK.html#prop_tgt:FRAMEWORK) 图书馆，[`MACOSX_BUNDLE`](https://cmake.org/cmake/help/latest/prop_tgt/MACOSX_BUNDLE.html#prop_tgt:MACOSX_BUNDLE)可执行文件，以及[`BUNDLE`](https://cmake.org/cmake/help/latest/prop_tgt/BUNDLE.html#prop_tgt:BUNDLE) CFBundles。）例如，与 DLL 关联的头文件和导入库未安装。如果是[`FRAMEWORK`](https://cmake.org/cmake/help/latest/prop_tgt/FRAMEWORK.html#prop_tgt:FRAMEWORK)图书馆， [`MACOSX_BUNDLE`](https://cmake.org/cmake/help/latest/prop_tgt/MACOSX_BUNDLE.html#prop_tgt:MACOSX_BUNDLE)可执行文件，以及[`BUNDLE`](https://cmake.org/cmake/help/latest/prop_tgt/BUNDLE.html#prop_tgt:BUNDLE)CFBundles，整个目录都安装好了。

该`RUNTIME_DEPENDENCY_SET`选项会导致将导入的可执行文件、共享库和模块库的运行时工件`targets`添加到`<set-name>`运行时依赖项集中。然后可以使用[install(RUNTIME_DEPENDENCY_SET)](https://cmake.org/cmake/help/latest/command/install.html#install-runtime-dependency-set)命令安装此集。

## 安装文件



笔记

 

如果安装头文件，请考虑使用定义的文件集 [`target_sources(FILE_SET)`](https://cmake.org/cmake/help/latest/command/target_sources.html#command:target_sources)反而。文件集将标头与目标相关联，它们作为目标的一部分安装。

```cmake
install(<FILES|PROGRAMS> files...
        TYPE <type> | DESTINATION <dir>
        [PERMISSIONS permissions...]
        [CONFIGURATIONS [Debug|Release|...]]
        [COMPONENT <component>]
        [RENAME <name>] [OPTIONAL] [EXCLUDE_FROM_ALL])
```

该`FILES`表单指定了为项目安装文件的规则。以相对路径给出的文件名相对于当前源目录进行解释。通过这种形式安装的文件默认被赋予权限`OWNER_WRITE`, `OWNER_READ`, `GROUP_READ`, `WORLD_READ`如果没有`PERMISSIONS`给出参数。

`PROGRAMS`表单与表单相同，只是`FILES`安装文件的默认权限还包括`OWNER_EXECUTE`、 `GROUP_EXECUTE`和`WORLD_EXECUTE`。此表单旨在安装非目标程序，例如 shell 脚本。使用`TARGETS` 表单安装项目中构建的目标。

`files...`给定`FILES`或`PROGRAMS`可能使用带有语法的“生成器表达式”的列表`$<...>`。见 [`cmake-generator-expressions(7)`](https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html#manual:cmake-generator-expressions(7))可用表达式的手册。但是，如果任何项目以生成器表达式开头，则它必须评估为完整路径。

a`TYPE`或 a`DESTINATION`必须提供，但不能同时提供。参数指定正在安装的文件的`TYPE`通用文件类型。然后将通过从以下位置获取相应变量来自动设置目的地[`GNUInstallDirs`](https://cmake.org/cmake/help/latest/module/GNUInstallDirs.html#module:GNUInstallDirs)，或者如果未定义该变量，则使用内置默认值。有关支持的文件类型及其对应的变量和内置默认值，请参见下表。`DESTINATION`如果项目希望明确定义安装目标，则可以提供参数而不是文件类型。

| `TYPE`争论    | GNUInstallDirs 变量              | 内置默认值              |
| :------------ | :------------------------------- | :---------------------- |
| `BIN`         | `${CMAKE_INSTALL_BINDIR}`        | `bin`                   |
| `SBIN`        | `${CMAKE_INSTALL_SBINDIR}`       | `sbin`                  |
| `LIB`         | `${CMAKE_INSTALL_LIBDIR}`        | `lib`                   |
| `INCLUDE`     | `${CMAKE_INSTALL_INCLUDEDIR}`    | `include`               |
| `SYSCONF`     | `${CMAKE_INSTALL_SYSCONFDIR}`    | `etc`                   |
| `SHAREDSTATE` | `${CMAKE_INSTALL_SHARESTATEDIR}` | `com`                   |
| `LOCALSTATE`  | `${CMAKE_INSTALL_LOCALSTATEDIR}` | `var`                   |
| `RUNSTATE`    | `${CMAKE_INSTALL_RUNSTATEDIR}`   | `<LOCALSTATE dir>/run`  |
| `DATA`        | `${CMAKE_INSTALL_DATADIR}`       | `<DATAROOT dir>`        |
| `INFO`        | `${CMAKE_INSTALL_INFODIR}`       | `<DATAROOT dir>/info`   |
| `LOCALE`      | `${CMAKE_INSTALL_LOCALEDIR}`     | `<DATAROOT dir>/locale` |
| `MAN`         | `${CMAKE_INSTALL_MANDIR}`        | `<DATAROOT dir>/man`    |
| `DOC`         | `${CMAKE_INSTALL_DOCDIR}`        | `<DATAROOT dir>/doc`    |

希望遵循将标头安装到项目特定子目录中的常见做法的项目将需要提供目标而不是依赖于上述内容。使用文件集代替标题`install(FILES)` 会更好（请参阅[`target_sources(FILE_SET)`](https://cmake.org/cmake/help/latest/command/target_sources.html#command:target_sources)).

请注意，某些类型的内置默认值使用`DATAROOT`目录作为前缀。前缀的`DATAROOT`计算类似于类型， `CMAKE_INSTALL_DATAROOTDIR`作为变量和`share`内置默认值。您不能`DATAROOT`用作`TYPE`参数；请 `DATA`改用。

为了使包符合分发文件系统布局策略，如果项目必须指定 a `DESTINATION`，建议他们使用以适当的开头的路径[`GNUInstallDirs`](https://cmake.org/cmake/help/latest/module/GNUInstallDirs.html#module:GNUInstallDirs)多变的。这允许包维护者通过设置适当的缓存变量来控制安装目标。以下示例显示了在将图像安装到特定于项目的文档子目录时如何遵循此建议：

```cmake
include(GNUInstallDirs)
install(FILES logo.png
        DESTINATION ${CMAKE_INSTALL_DOCDIR}/myproj
)
```

*3.4 版中的新功能：*作为`DESTINATION`参数给出的安装目标可以使用带有语法的“生成器表达式” `$<...>`。见 [`cmake-generator-expressions(7)`](https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html#manual:cmake-generator-expressions(7))可用表达式的手册。

*3.20 版中的新功能：*作为`RENAME`参数给出的安装重命名可以使用带有语法的“生成器表达式” `$<...>`。见 [`cmake-generator-expressions(7)`](https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html#manual:cmake-generator-expressions(7))可用表达式的手册。

## 安装目录



笔记

 

要安装标头的目录子树，请考虑使用由定义的文件集[`target_sources(FILE_SET)`](https://cmake.org/cmake/help/latest/command/target_sources.html#command:target_sources)反而。文件集不仅保留目录结构，它们还将标头与目标相关联并作为目标的一部分安装。

```cmake
install(DIRECTORY dirs...
        TYPE <type> | DESTINATION <dir>
        [FILE_PERMISSIONS permissions...]
        [DIRECTORY_PERMISSIONS permissions...]
        [USE_SOURCE_PERMISSIONS] [OPTIONAL] [MESSAGE_NEVER]
        [CONFIGURATIONS [Debug|Release|...]]
        [COMPONENT <component>] [EXCLUDE_FROM_ALL]
        [FILES_MATCHING]
        [[PATTERN <pattern> | REGEX <regex>]
         [EXCLUDE] [PERMISSIONS permissions...]] [...])
```

该`DIRECTORY`表单将一个或多个目录的内容安装到给定的目的地。目录结构被逐字复制到目的地。每个目录名称的最后一个组件都附加到目标目录，但可以使用尾部斜杠来避免这种情况，因为它使最后一个组件为空。作为相对路径给出的目录名称是相对于当前源目录解释的。如果没有给出输入目录名称，则将创建目标目录，但不会将任何内容安装到其中。`FILE_PERMISSIONS`和`DIRECTORY_PERMISSIONS`选项指定授予目标中的文件和目录的权限。如果`USE_SOURCE_PERMISSIONS`指定并且`FILE_PERMISSIONS`不是，文件权限将从源目录结构中复制。如果没有指定权限，文件将被赋予以`FILES`命令形式指定的默认权限，目录将被赋予以 `PROGRAMS`命令形式指定的默认权限。

*3.1 版新功能：*该`MESSAGE_NEVER`选项禁用文件安装状态输出。

`PATTERN`可以使用or`REGEX`选项以精细的粒度控制目录的安装。这些“匹配”选项指定一个通配模式或正则表达式来匹配输入目录中遇到的目录或文件。它们可用于将某些选项（见下文）应用于遇到的文件和目录的子集。每个输入文件或目录的完整路径（带有正斜杠）与表达式匹配。A`PATTERN`将只匹配完整的文件名：与模式匹配的完整路径部分必须出现在文件名的末尾，并且前面有一个斜杠。A`REGEX`将匹配完整路径的任何部分，但它可以使用`/`并`$`模拟`PATTERN`行为。默认情况下，无论是否匹配，都会安装所有文件和目录。该`FILES_MATCHING`选项可以在第一个匹配选项之前给出，以禁用任何表达式不匹配的文件（但不是目录）的安装。例如，代码

```cmake
install(DIRECTORY src/ DESTINATION doc/myproj
        FILES_MATCHING PATTERN "*.png")
```

将从源代码树中提取和安装图像。

某些选项可能跟在[string(REGEX)](https://cmake.org/cmake/help/latest/command/string.html#regex-specification)中描述的`PATTERN`or表达式之后，并且仅适用于匹配它们的文件或目录。该选项将跳过匹配的文件或目录。该选项会覆盖匹配文件或目录的权限设置。例如代码`REGEX``EXCLUDE``PERMISSIONS`

```cmake
install(DIRECTORY icons scripts/ DESTINATION share/myproj
        PATTERN "CVS" EXCLUDE
        PATTERN "scripts/*"
        PERMISSIONS OWNER_EXECUTE OWNER_WRITE OWNER_READ
                    GROUP_EXECUTE GROUP_READ)
```

将安装`icons`目录`share/myproj/icons`和 `scripts`目录`share/myproj`。图标将获得默认文件权限，脚本将获得特定权限，并且任何 `CVS`目录都将被排除在外。

a`TYPE`或 a`DESTINATION`必须提供，但不能同时提供。参数指定正在安装的列出目录中的文件的`TYPE`通用文件类型。然后将通过从以下位置获取相应变量来自动设置目的地 [`GNUInstallDirs`](https://cmake.org/cmake/help/latest/module/GNUInstallDirs.html#module:GNUInstallDirs)，或者如果未定义该变量，则使用内置默认值。有关支持的文件类型及其对应的变量和内置默认值，请参见下表。`DESTINATION`如果项目希望明确定义安装目标，则可以提供 参数而不是文件类型。

| `TYPE`争论    | GNUInstallDirs 变量              | 内置默认值              |
| :------------ | :------------------------------- | :---------------------- |
| `BIN`         | `${CMAKE_INSTALL_BINDIR}`        | `bin`                   |
| `SBIN`        | `${CMAKE_INSTALL_SBINDIR}`       | `sbin`                  |
| `LIB`         | `${CMAKE_INSTALL_LIBDIR}`        | `lib`                   |
| `INCLUDE`     | `${CMAKE_INSTALL_INCLUDEDIR}`    | `include`               |
| `SYSCONF`     | `${CMAKE_INSTALL_SYSCONFDIR}`    | `etc`                   |
| `SHAREDSTATE` | `${CMAKE_INSTALL_SHARESTATEDIR}` | `com`                   |
| `LOCALSTATE`  | `${CMAKE_INSTALL_LOCALSTATEDIR}` | `var`                   |
| `RUNSTATE`    | `${CMAKE_INSTALL_RUNSTATEDIR}`   | `<LOCALSTATE dir>/run`  |
| `DATA`        | `${CMAKE_INSTALL_DATADIR}`       | `<DATAROOT dir>`        |
| `INFO`        | `${CMAKE_INSTALL_INFODIR}`       | `<DATAROOT dir>/info`   |
| `LOCALE`      | `${CMAKE_INSTALL_LOCALEDIR}`     | `<DATAROOT dir>/locale` |
| `MAN`         | `${CMAKE_INSTALL_MANDIR}`        | `<DATAROOT dir>/man`    |
| `DOC`         | `${CMAKE_INSTALL_DOCDIR}`        | `<DATAROOT dir>/doc`    |

请注意，某些类型的内置默认值使用`DATAROOT`目录作为前缀。前缀的`DATAROOT`计算类似于类型， `CMAKE_INSTALL_DATAROOTDIR`作为变量和`share`内置默认值。您不能`DATAROOT`用作`TYPE`参数；请 `DATA`改用。

为了使包符合分发文件系统布局策略，如果项目必须指定 a `DESTINATION`，建议他们使用以适当的开头的路径[`GNUInstallDirs`](https://cmake.org/cmake/help/latest/module/GNUInstallDirs.html#module:GNUInstallDirs)多变的。这允许包维护者通过设置适当的缓存变量来控制安装目标。

*3.4 版中的新功能：*作为`DESTINATION`参数给出的安装目标可以使用带有语法的“生成器表达式” `$<...>`。见 [`cmake-generator-expressions(7)`](https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html#manual:cmake-generator-expressions(7))可用表达式的手册。

*3.5 版新功能：*`dirs...`给定的列表`DIRECTORY`也可以使用“生成器表达式”。

## 自定义安装逻辑



```cmake
install([[SCRIPT <file>] [CODE <code>]]
        [ALL_COMPONENTS | COMPONENT <component>]
        [EXCLUDE_FROM_ALL] [...])
```

该`SCRIPT`表单将在安装期间调用给定的 CMake 脚本文件。如果脚本文件名是相对路径，它将根据当前源目录进行解释。该`CODE` 表单将在安装期间调用给定的 CMake 代码。代码被指定为双引号字符串内的单个参数。例如，代码

```cmake
install(CODE "MESSAGE(\"Sample install message.\")")
```

将在安装过程中打印一条消息。

*3.21 版新功能：*当`ALL_COMPONENTS`给出选项时，将为特定组件安装的每个组件执行自定义安装脚本代码。此选项与该选项互斥`COMPONENT` 。

*版本 3.14 中的新功能：*`<file>`或者`<code>`可以在语法中使用“生成器表达式” `$<...>`（在 的情况下`<file>`，这是指它们在文件名中的使用，而不是文件的内容）。见 [`cmake-generator-expressions(7)`](https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html#manual:cmake-generator-expressions(7))可用表达式的手册。

## 安装导出



```cmake
install(EXPORT <export-name> DESTINATION <dir>
        [NAMESPACE <namespace>] [[FILE <name>.cmake]|
        [PERMISSIONS permissions...]
        [CONFIGURATIONS [Debug|Release|...]]
        [EXPORT_LINK_INTERFACE_LIBRARIES]
        [COMPONENT <component>]
        [EXCLUDE_FROM_ALL])
install(EXPORT_ANDROID_MK <export-name> DESTINATION <dir> [...])
```

该`EXPORT`表单生成并安装一个 CMake 文件，其中包含将目标从安装树导入另一个项目的代码。`<export-name>` 使用上面记录的[install(TARGETS)](https://cmake.org/cmake/help/latest/command/install.html#install-targets)签名`EXPORT`选项将目标安装与导出相关联。该选项将在目标名称写入导入文件时添加到它们的前面。默认情况下，将调用生成的文件，但该 选项可用于指定不同的名称。赋予选项的值必须是带有扩展名的文件名。如果一个`NAMESPACE``<namespace>``<export-name>.cmake``FILE``FILE``.cmake``CONFIGURATIONS`给出选项，则仅在安装指定配置之一时才会安装该文件。此外，生成的导入文件将仅引用匹配的目标配置。关键字（`EXPORT_LINK_INTERFACE_LIBRARIES`如果存在）会导致匹配的属性的内容 `(IMPORTED_)?LINK_INTERFACE_LIBRARIES(_<CONFIG>)?`被导出，当策略[`CMP0022`](https://cmake.org/cmake/help/latest/policy/CMP0022.html#policy:CMP0022)是`NEW`。

笔记

 

安装的`<export-name>.cmake`文件可能附带额外的每个配置`<export-name>-*.cmake`文件，以通过 globbing 加载。不要在安装`<package-name>-config.cmake` 文件时使用与包名称相同的导出名称，否则后者可能会被 glob 错误匹配并加载。

当`COMPONENT`给出一个选项时，列出的`<component>`隐含依赖于导出集中提到的所有组件。导出的 `<name>.cmake`文件将要求每个导出的组件都存在，以便正确构建相关项目。例如，一个项目可以定义组件`Runtime`和`Development`，共享库进入`Runtime`组件，静态库和头文件进入`Development`组件。导出集通常也是组件的一部分，但它会从和组件中`Development`导出目标。因此，如果安装了组件，则需要安装该 组件，反之则不然。如果组件安装时没有`Runtime``Development``Runtime``Development``Development``Runtime`组件，尝试链接它的依赖项目会产生构建错误。包管理器（例如 APT 和 RPM）通常通过将`Runtime`组件列为包元数据中组件的依赖项来处理此问题`Development`，确保在存在标头和 CMake 导出文件时始终安装库。

*3.7 新版功能：*除了 cmake 语言文件外，该`EXPORT_ANDROID_MK`模式还可用于指定导出到 android ndk 构建系统。此模式接受与正常导出模式相同的选项。Android NDK 支持使用预建库，包括静态库和共享库。这允许 cmake 构建项目的库，并使它们可用于具有传递依赖项的 ndk 构建系统，包括使用这些库所需的标志和定义。

该`EXPORT`表单有助于帮助外部项目使用当前项目构建和安装的目标。例如，代码

```cmake
install(TARGETS myexe EXPORT myproj DESTINATION bin)
install(EXPORT myproj NAMESPACE mp_ DESTINATION lib/myproj)
install(EXPORT_ANDROID_MK myproj DESTINATION share/ndk-modules)
```

将安装可执行文件和代码`myexe`以`<prefix>/bin`将其导入文件`<prefix>/lib/myproj/myproj.cmake`和 `<prefix>/share/ndk-modules/Android.mk`. 外部项目可以使用 include 命令加载此文件，并`myexe` 使用导入的目标名称从安装树中引用可执行文件， `mp_myexe`就好像目标是在自己的树中构建的一样。

笔记

 

此命令取代[`install_targets()`](https://cmake.org/cmake/help/latest/command/install_targets.html#command:install_targets)命令和[`PRE_INSTALL_SCRIPT`](https://cmake.org/cmake/help/latest/prop_tgt/PRE_INSTALL_SCRIPT.html#prop_tgt:PRE_INSTALL_SCRIPT)和[`POST_INSTALL_SCRIPT`](https://cmake.org/cmake/help/latest/prop_tgt/POST_INSTALL_SCRIPT.html#prop_tgt:POST_INSTALL_SCRIPT) 目标属性。它还取代`FILES`了 [`install_files()`](https://cmake.org/cmake/help/latest/command/install_files.html#command:install_files)和[`install_programs()`](https://cmake.org/cmake/help/latest/command/install_programs.html#command:install_programs)命令。这些安装规则的处理顺序相对于生成的规则[`install_targets()`](https://cmake.org/cmake/help/latest/command/install_targets.html#command:install_targets), [`install_files()`](https://cmake.org/cmake/help/latest/command/install_files.html#command:install_files)， 和[`install_programs()`](https://cmake.org/cmake/help/latest/command/install_programs.html#command:install_programs)命令未定义。

## 安装运行时依赖



*3.21 版中的新功能。*

```cmake
install(RUNTIME_DEPENDENCY_SET <set-name>
        [[LIBRARY|RUNTIME|FRAMEWORK]
         [DESTINATION <dir>]
         [PERMISSIONS permissions...]
         [CONFIGURATIONS [Debug|Release|...]]
         [COMPONENT <component>]
         [NAMELINK_COMPONENT <component>]
         [OPTIONAL] [EXCLUDE_FROM_ALL]
        ] [...]
        [PRE_INCLUDE_REGEXES regexes...]
        [PRE_EXCLUDE_REGEXES regexes...]
        [POST_INCLUDE_REGEXES regexes...]
        [POST_EXCLUDE_REGEXES regexes...]
        [POST_INCLUDE_FILES files...]
        [POST_EXCLUDE_FILES files...]
        [DIRECTORIES directories...]
        )
```

安装以前由一个或多个 [install(TARGETS)](https://cmake.org/cmake/help/latest/command/install.html#install-targets)或[install(IMPORTED_RUNTIME_ARTIFACTS)](https://cmake.org/cmake/help/latest/command/install.html#install-imported-runtime-artifacts)命令创建的运行时依赖项集。属于运行时依赖集的目标的依赖安装在`RUNTIME`DLL 平台上的 `LIBRARY`目标和组件中，以及非 DLL 平台上的目标和组件中。macOS 框架安装在`FRAMEWORK`目标和组件中。在构建树中构建的目标永远不会作为运行时依赖项安装，它们自己的依赖项也不会安装，除非目标本身是使用[install(TARGETS) 安装](https://cmake.org/cmake/help/latest/command/install.html#install-targets)的。

生成的安装脚本调用[`file(GET_RUNTIME_DEPENDENCIES)`](https://cmake.org/cmake/help/latest/command/file.html#command:file) 在构建树文件上计算运行时依赖项。构建树可执行文件作为`EXECUTABLES`参数传递，构建树共享库作为`LIBRARIES`参数传递，构建树模块作为`MODULES`参数传递。在 macOS 上，如果其中一个可执行文件是 [`MACOSX_BUNDLE`](https://cmake.org/cmake/help/latest/prop_tgt/MACOSX_BUNDLE.html#prop_tgt:MACOSX_BUNDLE)`BUNDLE_EXECUTABLE`，该可执行文件作为参数传递 。最多一个这样的捆绑可执行文件可能位于 macOS 上的运行时依赖集中。这[`MACOSX_BUNDLE`](https://cmake.org/cmake/help/latest/prop_tgt/MACOSX_BUNDLE.html#prop_tgt:MACOSX_BUNDLE)属性对其他平台没有影响。注意 [`file(GET_RUNTIME_DEPENDENCIES)`](https://cmake.org/cmake/help/latest/command/file.html#command:file)仅支持收集 Windows、Linux 和 macOS 平台的运行时依赖项，因此 `install(RUNTIME_DEPENDENCY_SET)`具有相同的限制。

以下子参数作为相应参数转发到[`file(GET_RUNTIME_DEPENDENCIES)`](https://cmake.org/cmake/help/latest/command/file.html#command:file)（对于那些提供非空目录、正则表达式或文件列表的人）。他们都支持[`generator expressions`](https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html#manual:cmake-generator-expressions(7)).

- `DIRECTORIES <directories>`
- `PRE_INCLUDE_REGEXES <regexes>`
- `PRE_EXCLUDE_REGEXES <regexes>`
- `POST_INCLUDE_REGEXES <regexes>`
- `POST_EXCLUDE_REGEXES <regexes>`
- `POST_INCLUDE_FILES <files>`
- `POST_EXCLUDE_FILES <files>`

## 生成的安装脚本

笔记

 

不建议使用此功能。请考虑 `--install`使用[`cmake(1)`](https://cmake.org/cmake/help/latest/manual/cmake.1.html#manual:cmake(1))反而。

该`install()`命令`cmake_install.cmake`在 build 目录中生成一个文件 ，由生成的安装目标和 CPack 在内部使用。您也可以使用 手动调用此脚本。该脚本接受几个变量：`cmake -P`

- `COMPONENT`

  将此变量设置为仅安装单个 CPack 组件，而不是全部安装。例如，如果您只想安装`Development` 组件，请运行.`cmake -DCOMPONENT=Development -P cmake_install.cmake`

- `BUILD_TYPE`

  如果您使用的是多配置生成器，请设置此变量以更改构建类型。例如，要使用`Debug`配置进行安装，请运行 .`cmake -DBUILD_TYPE=Debug -P cmake_install.cmake`

- `DESTDIR`

  这是一个环境变量而不是 CMake 变量。它允许您更改 UNIX 系统上的安装前缀。看[`DESTDIR`](https://cmake.org/cmake/help/latest/envvar/DESTDIR.html#envvar:DESTDIR)详情。



# [link_directories](https://cmake.org/cmake/help/latest/command/link_directories.html)

添加链接器将在其中查找库的目录。

```cmake
link_directories([AFTER|BEFORE] directory1 [directory2 ...])
```

添加链接器应在其中搜索库的路径。赋予此命令的相对路径被解释为相对于当前源目录，请参阅[`CMP0015`](https://cmake.org/cmake/help/latest/policy/CMP0015.html#policy:CMP0015).

该命令仅适用于调用后创建的目标。

*3.13 新版功能：*将目录添加到[`LINK_DIRECTORIES`](https://cmake.org/cmake/help/latest/prop_dir/LINK_DIRECTORIES.html#prop_dir:LINK_DIRECTORIES)当前`CMakeLists.txt`文件的目录属性，根据需要将相对路径转换为绝对路径。见[`cmake-buildsystem(7)`](https://cmake.org/cmake/help/latest/manual/cmake-buildsystem.7.html#manual:cmake-buildsystem(7)) 有关定义构建系统属性的更多信息。

*3.13 新版功能：*默认情况下，指定的目录附加到当前目录列表中。可以通过设置更改此默认行为 [`CMAKE_LINK_DIRECTORIES_BEFORE`](https://cmake.org/cmake/help/latest/variable/CMAKE_LINK_DIRECTORIES_BEFORE.html#variable:CMAKE_LINK_DIRECTORIES_BEFORE)到`ON`. 通过使用 `AFTER`or`BEFORE`显式，您可以在附加和前置之间进行选择，而与默认值无关。

*3.13 新版功能：*参数 to`link_directories`可以使用语法为“$<...>”的“生成器表达式”。见[`cmake-generator-expressions(7)`](https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html#manual:cmake-generator-expressions(7)) 可用表达式的手册。

> **笔记** 此命令很少需要，在有其他选择时应避免使用。尽可能将完整的绝对路径传递给库，因为这样可以确保始终链接正确的库。这[`find_library()`](https://cmake.org/cmake/help/latest/command/find_library.html#command:find_library)命令提供完整路径，一般可以直接在调用中使用[`target_link_libraries()`](https://cmake.org/cmake/help/latest/command/target_link_libraries.html#command:target_link_libraries). 可能需要库搜索路径的情况包括：
>
> - 像 Xcode 这样的项目生成器，用户可以在构建时切换目标架构，但不能使用库的完整路径，因为它只提供一种架构（即它不是通用二进制文件）。
> - 库本身可能有其他私有库依赖项，这些依赖项期望通过`RPATH`机制找到，但一些链接器无法完全解码这些路径（例如，由于存在类似 的东西`$ORIGIN`）。
>
> 如果必须提供库搜索路径，请尽可能使用[`target_link_directories()`](https://cmake.org/cmake/help/latest/command/target_link_directories.html#command:target_link_directories)命令而不是`link_directories()`. 特定于目标的命令还可以控制搜索目录如何传播到其他相关目标。

 

# [link_libraries](https://cmake.org/cmake/help/latest/command/link_libraries.html)

将库链接到以后添加的所有目标。

```cmake
link_libraries([item1 [item2 [...]]]
               [[debug|optimized|general] <item>] ...)
```

通过以下命令链接稍后在当前目录或下面创建的任何目标时，指定要使用的库或标志[`add_executable()`](https://cmake.org/cmake/help/latest/command/add_executable.html#command:add_executable) 或者[`add_library()`](https://cmake.org/cmake/help/latest/command/add_library.html#command:add_library). 见[`target_link_libraries()`](https://cmake.org/cmake/help/latest/command/target_link_libraries.html#command:target_link_libraries)参数含义的命令。

> **笔记** 这[`target_link_libraries()`](https://cmake.org/cmake/help/latest/command/target_link_libraries.html#command:target_link_libraries)应尽可能首选命令。库依赖项是自动链接的，因此很少需要链接库的目录范围规范。

 

# [load_cache](https://cmake.org/cmake/help/latest/command/load_cache.html)

从另一个项目的 CMake 缓存中加载值。

```cmake
load_cache(pathToBuildDirectory READ_WITH_PREFIX prefix entry1...)
```

读取缓存并将请求的条目存储在变量中，其名称以给定前缀作为前缀。这只会读取值，不会在本地项目的缓存中创建条目。

```cmake
load_cache(pathToBuildDirectory [EXCLUDE entry1...]
           [INCLUDE_INTERNALS entry1...])
```

从另一个缓存中加载值并将它们作为内部条目存储在本地项目的缓存中。这对于依赖于构建在不同树中的另一个项目的项目很有用。 `EXCLUDE` 选项可用于提供要排除的条目列表。 `INCLUDE_INTERNALS`可用于提供要包含的内部条目列表。通常，不会引入内部条目。强烈建议不要使用这种形式的命令，但提供它是为了向后兼容。



# [project](https://cmake.org/cmake/help/latest/command/project.html)

设置项目的名称。

## Synopsis

```cmake
project(<PROJECT-NAME> [<language-name>...])
project(<PROJECT-NAME>
        [VERSION <major>[.<minor>[.<patch>[.<tweak>]]]]
        [DESCRIPTION <project-description-string>]
        [HOMEPAGE_URL <url-string>]
        [LANGUAGES <language-name>...])
```

设置项目的名称，并将其存储在变量中 [`PROJECT_NAME`](https://cmake.org/cmake/help/latest/variable/PROJECT_NAME.html#variable:PROJECT_NAME). 从顶层调用时， `CMakeLists.txt`还将项目名称存储在变量中[`CMAKE_PROJECT_NAME`](https://cmake.org/cmake/help/latest/variable/CMAKE_PROJECT_NAME.html#variable:CMAKE_PROJECT_NAME).

还设置变量：

- [`PROJECT_SOURCE_DIR`](https://cmake.org/cmake/help/latest/variable/PROJECT_SOURCE_DIR.html#variable:PROJECT_SOURCE_DIR), [`_SOURCE_DIR`](https://cmake.org/cmake/help/latest/variable/PROJECT-NAME_SOURCE_DIR.html#variable:_SOURCE_DIR)

  项目源目录的绝对路径。

- [`PROJECT_BINARY_DIR`](https://cmake.org/cmake/help/latest/variable/PROJECT_BINARY_DIR.html#variable:PROJECT_BINARY_DIR),[`_BINARY_DIR`](https://cmake.org/cmake/help/latest/variable/PROJECT-NAME_BINARY_DIR.html#variable:_BINARY_DIR)

  项目二进制目录的绝对路径。

- [`PROJECT_IS_TOP_LEVEL`](https://cmake.org/cmake/help/latest/variable/PROJECT_IS_TOP_LEVEL.html#variable:PROJECT_IS_TOP_LEVEL),[`_IS_TOP_LEVEL`](https://cmake.org/cmake/help/latest/variable/PROJECT-NAME_IS_TOP_LEVEL.html#variable:_IS_TOP_LEVEL)

  *3.21 版中的新功能。*指示项目是否为顶级的布尔值。

进一步的变量由下面描述的可选参数设置。如果未使用这些参数中的任何一个，则将相应的变量设置为空字符串。

## Options

选项包括：

- `VERSION <version>`

  可选的; 除非政策，否则不得使用[`CMP0048`](https://cmake.org/cmake/help/latest/policy/CMP0048.html#policy:CMP0048)设置为`NEW`。`<version>`接受由非负整数分量组成的参数，即，`<major>[.<minor>[.<patch>[.<tweak>]]]`并设置变量[`PROJECT_VERSION`](https://cmake.org/cmake/help/latest/variable/PROJECT_VERSION.html#variable:PROJECT_VERSION), [`_VERSION`](https://cmake.org/cmake/help/latest/variable/PROJECT-NAME_VERSION.html#variable:_VERSION)[`PROJECT_VERSION_MAJOR`](https://cmake.org/cmake/help/latest/variable/PROJECT_VERSION_MAJOR.html#variable:PROJECT_VERSION_MAJOR), [`_VERSION_MAJOR`](https://cmake.org/cmake/help/latest/variable/PROJECT-NAME_VERSION_MAJOR.html#variable:_VERSION_MAJOR)[`PROJECT_VERSION_MINOR`](https://cmake.org/cmake/help/latest/variable/PROJECT_VERSION_MINOR.html#variable:PROJECT_VERSION_MINOR), [`_VERSION_MINOR`](https://cmake.org/cmake/help/latest/variable/PROJECT-NAME_VERSION_MINOR.html#variable:_VERSION_MINOR)[`PROJECT_VERSION_PATCH`](https://cmake.org/cmake/help/latest/variable/PROJECT_VERSION_PATCH.html#variable:PROJECT_VERSION_PATCH), [`_VERSION_PATCH`](https://cmake.org/cmake/help/latest/variable/PROJECT-NAME_VERSION_PATCH.html#variable:_VERSION_PATCH)[`PROJECT_VERSION_TWEAK`](https://cmake.org/cmake/help/latest/variable/PROJECT_VERSION_TWEAK.html#variable:PROJECT_VERSION_TWEAK), [`_VERSION_TWEAK`](https://cmake.org/cmake/help/latest/variable/PROJECT-NAME_VERSION_TWEAK.html#variable:_VERSION_TWEAK).*3.12 新功能：*`project()`从顶层调用命令 时`CMakeLists.txt`，版本也存储在变量中 [`CMAKE_PROJECT_VERSION`](https://cmake.org/cmake/help/latest/variable/CMAKE_PROJECT_VERSION.html#variable:CMAKE_PROJECT_VERSION).

- `DESCRIPTION <project-description-string>`

  *3.9 版中的新功能。*可选的。设置变量[`PROJECT_DESCRIPTION`](https://cmake.org/cmake/help/latest/variable/PROJECT_DESCRIPTION.html#variable:PROJECT_DESCRIPTION), [`_DESCRIPTION`](https://cmake.org/cmake/help/latest/variable/PROJECT-NAME_DESCRIPTION.html#variable:_DESCRIPTION)到`<project-description-string>`. 建议这个描述是一个比较短的字符串，一般不超过几个字。当`project()`从顶层调用命令时`CMakeLists.txt`，描述也存储在变量中[`CMAKE_PROJECT_DESCRIPTION`](https://cmake.org/cmake/help/latest/variable/CMAKE_PROJECT_DESCRIPTION.html#variable:CMAKE_PROJECT_DESCRIPTION).*3.12 新版功能：*添加了`<PROJECT-NAME>_DESCRIPTION`变量。

- `HOMEPAGE_URL <url-string>`

  *版本 3.12 中的新功能。*可选的。设置变量[`PROJECT_HOMEPAGE_URL`](https://cmake.org/cmake/help/latest/variable/PROJECT_HOMEPAGE_URL.html#variable:PROJECT_HOMEPAGE_URL), [`_HOMEPAGE_URL`](https://cmake.org/cmake/help/latest/variable/PROJECT-NAME_HOMEPAGE_URL.html#variable:_HOMEPAGE_URL)to `<url-string>`，它应该是项目的规范主页 URL。当`project()`从顶层调用命令时`CMakeLists.txt`，URL 也存储在变量中[`CMAKE_PROJECT_HOMEPAGE_URL`](https://cmake.org/cmake/help/latest/variable/CMAKE_PROJECT_HOMEPAGE_URL.html#variable:CMAKE_PROJECT_HOMEPAGE_URL).

- `LANGUAGES <language-name>...`

  可选的。也可以`LANGUAGES`根据第一个短签名不带关键字指定。选择构建项目所需的编程语言。支持的语言包括`C`, `CXX`(即 C++), `CUDA`, `OBJC`(即 Objective-C), `OBJCXX`, `Fortran`, `HIP`,`ISPC`和`ASM`. 默认情况下，如果没有给出语言选项`C`，`CXX`则启用。指定 language `NONE`，或使用`LANGUAGES`关键字并不列出任何语言，以跳过启用任何语言。*3.8 版中的新功能：*添加`CUDA`了支持。*3.16 版新功能：*添加`OBJC`和`OBJCXX`支持。*3.18 版中的新功能：*添加`ISPC`了支持。如果启用`ASM`，请将其列在最后，以便 CMake 可以检查其他语言的编译器是否也`C`适用于汇编。

通过 和 选项设置的变量`VERSION`旨在 用作包元数据和文档中的默认值`DESCRIPTION`。`HOMEPAGE_URL`



## 代码注入

用户可以定义许多变量来指定要在`project()`命令执行期间的不同点包含的文件。以下概述了`project()`通话期间执行的步骤：

- *3.15 新版功能：*对于每个`project()`调用，无论项目名称如何，都包含名为的文件[`CMAKE_PROJECT_INCLUDE_BEFORE`](https://cmake.org/cmake/help/latest/variable/CMAKE_PROJECT_INCLUDE_BEFORE.html#variable:CMAKE_PROJECT_INCLUDE_BEFORE)，如果设置。
- *3.17 新版功能：*如果`project()`命令指定`<PROJECT-NAME>`为其项目名称，则包含名为的文件 [`CMAKE_PROJECT__INCLUDE_BEFORE`](https://cmake.org/cmake/help/latest/variable/CMAKE_PROJECT_PROJECT-NAME_INCLUDE_BEFORE.html#variable:CMAKE_PROJECT__INCLUDE_BEFORE)，如果设置。
- [设置上面概要](https://cmake.org/cmake/help/latest/command/project.html#synopsis) 和[选项](https://cmake.org/cmake/help/latest/command/project.html#options)部分中详述的各种项目特定变量。
- 仅限第一次`project()`通话：
  - 如果[`CMAKE_TOOLCHAIN_FILE`](https://cmake.org/cmake/help/latest/variable/CMAKE_TOOLCHAIN_FILE.html#variable:CMAKE_TOOLCHAIN_FILE)已设置，请至少阅读一次。它可以被多次读取，也可以在稍后启用语言时再次读取（见下文）。
  - 设置描述主机和目标平台的变量。此时可能会或可能不会设置特定于语言的变量。在第一次运行时，唯一可能定义的特定于语言的变量是工具链文件可能已设置的变量。在随后的运行中，可以设置从先前运行缓存的特定于语言的变量。
  - *3.24 版中的新功能：*包括列出的每个文件[`CMAKE_PROJECT_TOP_LEVEL_INCLUDES`](https://cmake.org/cmake/help/latest/variable/CMAKE_PROJECT_TOP_LEVEL_INCLUDES.html#variable:CMAKE_PROJECT_TOP_LEVEL_INCLUDES)，如果设置。此后，CMake 将忽略该变量。
- 启用调用中指定的任何语言，如果未提供默认语言，则启用默认语言。首次启用语言时，可能会重新读取工具链文件。
- *3.15 新版功能：*对于每个`project()`调用，无论项目名称如何，都包含名为的文件[`CMAKE_PROJECT_INCLUDE`](https://cmake.org/cmake/help/latest/variable/CMAKE_PROJECT_INCLUDE.html#variable:CMAKE_PROJECT_INCLUDE)，如果设置。
- 如果`project()`命令指定`<PROJECT-NAME>`为其项目名称，请包含名为的文件 [`CMAKE_PROJECT__INCLUDE`](https://cmake.org/cmake/help/latest/variable/CMAKE_PROJECT_PROJECT-NAME_INCLUDE.html#variable:CMAKE_PROJECT__INCLUDE)，如果设置。

## Usage

项目的顶级`CMakeLists.txt`文件必须包含对`project()`命令的直接调用；通过加载一个[`include()`](https://cmake.org/cmake/help/latest/command/include.html#command:include)命令是不够的。如果不存在这样的调用，CMake 将发出警告并假装 `project(Project)`顶部有一个以启用默认语言（`C`和`CXX`）。

> **笔记** `project()`在 top-level 的顶部附近 调用命令`CMakeLists.txt`，但*在*调用之后[`cmake_minimum_required()`](https://cmake.org/cmake/help/latest/command/cmake_minimum_required.html#command:cmake_minimum_required). 在调用可能影响其行为的其他命令之前，建立版本和策略设置非常重要。另见政策[`CMP0000`](https://cmake.org/cmake/help/latest/policy/CMP0000.html#policy:CMP0000).

 

# [remove_definitions](https://cmake.org/cmake/help/latest/command/remove_definitions.html)

删除 -D 定义添加的标志[`add_definitions()`](https://cmake.org/cmake/help/latest/command/add_definitions.html#command:add_definitions).

```cmake
remove_definitions(-DFOO -DBAR ...)
```

删除标志（由[`add_definitions()`](https://cmake.org/cmake/help/latest/command/add_definitions.html#command:add_definitions)) 从编译器命令行获取当前目录及以下目录中的源代码。



# [set_source_files_properties](https://cmake.org/cmake/help/latest/command/set_source_files_properties.html)

源文件可以具有影响其构建方式的属性。

```cmake
set_source_files_properties(<files> ...
                            [DIRECTORY <dirs> ...]
                            [TARGET_DIRECTORY <targets> ...]
                            PROPERTIES <prop1> <value1>
                            [<prop2> <value2>] ...)
```

使用键/值配对列表设置与源文件关联的属性。

*3.18 版新功能：*默认情况下，源文件属性仅对添加到同一目录 ( `CMakeLists.txt`) 中的目标可见。可以使用以下一个或两个选项在其他目录范围内设置可见性：

- `DIRECTORY <dirs>...`

  源文件属性将在每个`<dirs>` 目录的范围内设置。CMake 必须已经知道这些源目录中的每一个，或者通过调用添加它们 [`add_subdirectory()`](https://cmake.org/cmake/help/latest/command/add_subdirectory.html#command:add_subdirectory)或者它是顶级源目录。相对路径被视为相对于当前源目录。

- `TARGET_DIRECTORY <targets>...`

  源文件属性将在`<targets>`创建任何指定文件的每个目录范围中设置（`<targets>` 因此必须已经存在）。

利用[`get_source_file_property()`](https://cmake.org/cmake/help/latest/command/get_source_file_property.html#command:get_source_file_property)获取属性值。另见[`set_property(SOURCE)`](https://cmake.org/cmake/help/latest/command/set_property.html#command:set_property)命令。

有关CMake 已知的属性列表，请参阅[源文件的属性。](https://cmake.org/cmake/help/latest/manual/cmake-properties.7.html#source-file-properties)

> **笔记** 这[`GENERATED`](https://cmake.org/cmake/help/latest/prop_sf/GENERATED.html#prop_sf:GENERATED)源文件属性可能是全局可见的。有关详细信息，请参阅其文档。

 

# [set_target_properties](https://cmake.org/cmake/help/latest/command/set_target_properties.html)

目标可以具有影响其构建方式的属性。

```cmake
set_target_properties(target1 target2 ...
                      PROPERTIES prop1 value1
                      prop2 value2 ...)
```

设置目标的属性。该命令的语法是列出您要更改的所有目标，然后提供您接下来要设置的值。你可以使用任何你想要的道具值对，然后用[`get_property()`](https://cmake.org/cmake/help/latest/command/get_property.html#command:get_property)或者[`get_target_property()`](https://cmake.org/cmake/help/latest/command/get_target_property.html#command:get_target_property) 命令。

另见[`set_property(TARGET)`](https://cmake.org/cmake/help/latest/command/set_property.html#command:set_property)命令。

有关CMake 已知的属性列表，请参阅[目标上的属性。](https://cmake.org/cmake/help/latest/manual/cmake-properties.7.html#target-properties)



# [source_group](https://cmake.org/cmake/help/latest/command/source_group.html)

在 IDE 项目生成中为源文件定义分组。创建源组有两种不同的签名。

```cmake
source_group(<name> [FILES <src>...] [REGULAR_EXPRESSION <regex>])
source_group(TREE <root> [PREFIX <prefix>] [FILES <src>...])
```

定义将在项目文件中放置源的组。这旨在在 Visual Studio 中设置文件选项卡。该组的范围在调用命令的目录中，并适用于在该目录中创建的目标中的源。

选项包括：

- `TREE`

  *3.8 版中的新功能。*CMake 将自动从`<src>`文件路径中检测它需要创建的源组，以保持源组的结构类似于项目中的实际文件和目录结构。文件的路径`<src>` 将被剪切为相对于`<root>`. 如果其中的路径`src`不以 . 开头，则该命令将失败`root`。

- `PREFIX`

  *3.8 版中的新功能。*直接位于`<root>`路径中的源组和文件将被放置在`<prefix>`源组中。

- `FILES`

  任何明确指定的源文件都将放在 group 中 `<name>`。相对路径是相对于当前源目录解释的。

- `REGULAR_EXPRESSION`

  任何名称与正则表达式匹配的源文件都将放在 group 中`<name>`。

如果一个源文件与多个组匹配，那么明确列出该文件的*最后一个*`FILES`组将被优先考虑（如果有的话）。如果没有组显式列出文件，则正则表达式与文件匹配的*最后一个组将被优先考虑。*

`<name>`组和参数的可以`<prefix>`包含正斜杠或反斜杠来指定子组。反斜杠需要适当转义：

```cmake
source_group(base/subdir ...)
source_group(outer\\inner ...)
source_group(TREE <root> PREFIX sources\\inc ...)
```

*3.18 新版功能：*允许使用正斜杠 ( `/`) 来指定子组。

为了向后兼容，简写签名

```cmake
source_group(<name> <regex>)
```

相当于

```cmake
source_group(<name> REGULAR_EXPRESSION <regex>)
```



# [target_compile_definitions](https://cmake.org/cmake/help/latest/command/target_compile_definitions.html)

将编译定义添加到目标。

```cmake
target_compile_definitions(<target>
  <INTERFACE|PUBLIC|PRIVATE> [items1...]
  [<INTERFACE|PUBLIC|PRIVATE> [items2...] ...])
```

指定编译给定`<target>`. 名称`<target>`必须是由命令创建的，例如 [`add_executable()`](https://cmake.org/cmake/help/latest/command/add_executable.html#command:add_executable)或者[`add_library()`](https://cmake.org/cmake/help/latest/command/add_library.html#command:add_library)并且不能是 [ALIAS 目标](https://cmake.org/cmake/help/latest/manual/cmake-buildsystem.7.html#alias-targets)。

需要,`INTERFACE`和关键字`PUBLIC`来`PRIVATE`指定以下参数的范围。 `PRIVATE`并且`PUBLIC` 项目将填充[`COMPILE_DEFINITIONS`](https://cmake.org/cmake/help/latest/prop_tgt/COMPILE_DEFINITIONS.html#prop_tgt:COMPILE_DEFINITIONS)的财产 `<target>`。`PUBLIC`并且`INTERFACE`项目将填充 [`INTERFACE_COMPILE_DEFINITIONS`](https://cmake.org/cmake/help/latest/prop_tgt/INTERFACE_COMPILE_DEFINITIONS.html#prop_tgt:INTERFACE_COMPILE_DEFINITIONS)的财产`<target>`。以下参数指定编译定义。按调用顺序重复调用相同的`<target>`附加项。

*3.11 版新功能：允许在*[IMPORTED 目标](https://cmake.org/cmake/help/latest/manual/cmake-buildsystem.7.html#imported-targets)上设置`INTERFACE`项目。

参数 to`target_compile_definitions`可以使用带有语法的“生成器表达式” `$<...>`。见[`cmake-generator-expressions(7)`](https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html#manual:cmake-generator-expressions(7)) 可用表达式的手册。见[`cmake-buildsystem(7)`](https://cmake.org/cmake/help/latest/manual/cmake-buildsystem.7.html#manual:cmake-buildsystem(7)) 有关定义构建系统属性的更多信息。

项目上的任何前导`-D`都将被删除。空项目被忽略。例如，以下都是等价的：

```cmake
target_compile_definitions(foo PUBLIC FOO)
target_compile_definitions(foo PUBLIC -DFOO)  # -D removed
target_compile_definitions(foo PUBLIC "" FOO) # "" ignored
target_compile_definitions(foo PUBLIC -D FOO) # -D becomes "", then ignored
```

定义可以选择具有值：

```cmake
target_compile_definitions(foo PUBLIC FOO=1)
```

请注意，许多编译器将`-DFOO`其视为等效于`-DFOO=1`，但其他工具可能无法在所有情况下都识别这一点（例如 IntelliSense）。



# [target_compile_features](https://cmake.org/cmake/help/latest/command/target_compile_features.html)

*3.1 版中的新功能。*

将预期的编译器功能添加到目标。

```cmake
target_compile_features(<target> <PRIVATE|PUBLIC|INTERFACE> <feature> [...])
```

指定编译给定目标时所需的编译器功能。如果该功能未在[`CMAKE_C_COMPILE_FEATURES`](https://cmake.org/cmake/help/latest/variable/CMAKE_C_COMPILE_FEATURES.html#variable:CMAKE_C_COMPILE_FEATURES), [`CMAKE_CUDA_COMPILE_FEATURES`](https://cmake.org/cmake/help/latest/variable/CMAKE_CUDA_COMPILE_FEATURES.html#variable:CMAKE_CUDA_COMPILE_FEATURES)， 或者[`CMAKE_CXX_COMPILE_FEATURES`](https://cmake.org/cmake/help/latest/variable/CMAKE_CXX_COMPILE_FEATURES.html#variable:CMAKE_CXX_COMPILE_FEATURES) 变量，那么 CMake 会报错。如果使用该功能需要额外的编译器标志，例如`-std=gnu++11`，该标志将被自动添加。

需要,`INTERFACE`和关键字`PUBLIC`来`PRIVATE`指定功能的范围。 `PRIVATE`并且`PUBLIC`项目将填充[`COMPILE_FEATURES`](https://cmake.org/cmake/help/latest/prop_tgt/COMPILE_FEATURES.html#prop_tgt:COMPILE_FEATURES)的财产`<target>`。 `PUBLIC`并且`INTERFACE`项目将填充 [`INTERFACE_COMPILE_FEATURES`](https://cmake.org/cmake/help/latest/prop_tgt/INTERFACE_COMPILE_FEATURES.html#prop_tgt:INTERFACE_COMPILE_FEATURES)的财产`<target>`。重复调用相同的`<target>`附加项。

*3.11 版新功能：允许在*[IMPORTED 目标](https://cmake.org/cmake/help/latest/manual/cmake-buildsystem.7.html#imported-targets)上设置`INTERFACE`项目。

名称`<target>`必须是由命令创建的，例如 [`add_executable()`](https://cmake.org/cmake/help/latest/command/add_executable.html#command:add_executable)或者[`add_library()`](https://cmake.org/cmake/help/latest/command/add_library.html#command:add_library)并且不能是 [ALIAS 目标](https://cmake.org/cmake/help/latest/manual/cmake-buildsystem.7.html#alias-targets)。

参数 to`target_compile_features`可以使用带有语法的“生成器表达式” `$<...>`。见[`cmake-generator-expressions(7)`](https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html#manual:cmake-generator-expressions(7))可用表达式的手册。见[`cmake-compile-features(7)`](https://cmake.org/cmake/help/latest/manual/cmake-compile-features.7.html#manual:cmake-compile-features(7))有关编译功能和支持的编译器列表的信息手册。



# [target_compile_options](https://cmake.org/cmake/help/latest/command/target_compile_options.html)

将编译选项添加到目标。

```cmake
target_compile_options(<target> [BEFORE]
  <INTERFACE|PUBLIC|PRIVATE> [items1...]
  [<INTERFACE|PUBLIC|PRIVATE> [items2...] ...])
```

将选项添加到[`COMPILE_OPTIONS`](https://cmake.org/cmake/help/latest/prop_tgt/COMPILE_OPTIONS.html#prop_tgt:COMPILE_OPTIONS)或者 [`INTERFACE_COMPILE_OPTIONS`](https://cmake.org/cmake/help/latest/prop_tgt/INTERFACE_COMPILE_OPTIONS.html#prop_tgt:INTERFACE_COMPILE_OPTIONS)目标属性。这些选项在编译给定的时使用`<target>`，它必须是由命令创建的，例如[`add_executable()`](https://cmake.org/cmake/help/latest/command/add_executable.html#command:add_executable)或者 [`add_library()`](https://cmake.org/cmake/help/latest/command/add_library.html#command:add_library)并且不能是[ALIAS 目标](https://cmake.org/cmake/help/latest/manual/cmake-buildsystem.7.html#alias-targets)。

## Arguments

如果`BEFORE`指定，内容将被附加到属性而不是被附加。

需要,`INTERFACE`和关键字`PUBLIC`来`PRIVATE`指定以下参数的范围。 `PRIVATE`并且`PUBLIC` 项目将填充[`COMPILE_OPTIONS`](https://cmake.org/cmake/help/latest/prop_tgt/COMPILE_OPTIONS.html#prop_tgt:COMPILE_OPTIONS)的财产 `<target>`。 `PUBLIC`并且`INTERFACE`项目将填充 [`INTERFACE_COMPILE_OPTIONS`](https://cmake.org/cmake/help/latest/prop_tgt/INTERFACE_COMPILE_OPTIONS.html#prop_tgt:INTERFACE_COMPILE_OPTIONS)的财产`<target>`。以下参数指定编译选项。按调用顺序重复调用相同的 `<target>`附加项。

*3.11 版新功能：允许在*[IMPORTED 目标](https://cmake.org/cmake/help/latest/manual/cmake-buildsystem.7.html#imported-targets)上设置`INTERFACE`项目。

参数 to`target_compile_options`可以使用带有语法的“生成器表达式” `$<...>`。见[`cmake-generator-expressions(7)`](https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html#manual:cmake-generator-expressions(7)) 可用表达式的手册。见[`cmake-buildsystem(7)`](https://cmake.org/cmake/help/latest/manual/cmake-buildsystem.7.html#manual:cmake-buildsystem(7)) 有关定义构建系统属性的更多信息。

## 去重选项

用于目标的最终选项集是通过累积来自当前目标的选项及其依赖项的使用要求来构建的。对选项集进行重复数据删除以避免重复。

*3.12 版中的新功能：*虽然有利于单个选项，但重复数据删除步骤可以分解选项组。例如，变成 。可以使用类似 shell 的引用和前缀来指定一组选项。前缀被删除，其余的选项字符串使用 `-option A -option B``-option A B``SHELL:``SHELL:`[`separate_arguments()`](https://cmake.org/cmake/help/latest/command/separate_arguments.html#command:separate_arguments) `UNIX_COMMAND`模式。例如， 变成。`"SHELL:-option A" "SHELL:-option B"``-option A -option B`

## 另见

此命令可用于添加任何选项。但是，为了添加预处理器定义和包含目录，建议使用更具体的命令[`target_compile_definitions()`](https://cmake.org/cmake/help/latest/command/target_compile_definitions.html#command:target_compile_definitions) 和[`target_include_directories()`](https://cmake.org/cmake/help/latest/command/target_include_directories.html#command:target_include_directories).

对于目录范围的设置，有命令[`add_compile_options()`](https://cmake.org/cmake/help/latest/command/add_compile_options.html#command:add_compile_options).

对于特定于文件的设置，有源文件属性[`COMPILE_OPTIONS`](https://cmake.org/cmake/help/latest/prop_sf/COMPILE_OPTIONS.html#prop_sf:COMPILE_OPTIONS).



# [target_include_directories](https://cmake.org/cmake/help/latest/command/target_include_directories.html)

将包含目录添加到目标。

```cmake
target_include_directories(<target> [SYSTEM] [AFTER|BEFORE]
  <INTERFACE|PUBLIC|PRIVATE> [items1...]
  [<INTERFACE|PUBLIC|PRIVATE> [items2...] ...])
```

指定编译给定目标时要使用的包含目录。名称`<target>`必须是由命令创建的，例如[`add_executable()`](https://cmake.org/cmake/help/latest/command/add_executable.html#command:add_executable)或者[`add_library()`](https://cmake.org/cmake/help/latest/command/add_library.html#command:add_library)并且不能是 [ALIAS 目标](https://cmake.org/cmake/help/latest/manual/cmake-buildsystem.7.html#alias-targets)。

通过使用`AFTER`or`BEFORE`显式，您可以在附加和前置之间进行选择，而与默认值无关。

需要,`INTERFACE`和关键字`PUBLIC`来`PRIVATE`指定以下参数的范围。 `PRIVATE`并且`PUBLIC`项目将填充[`INCLUDE_DIRECTORIES`](https://cmake.org/cmake/help/latest/prop_tgt/INCLUDE_DIRECTORIES.html#prop_tgt:INCLUDE_DIRECTORIES)的财产`<target>`。 `PUBLIC`并且`INTERFACE`项目将填充 [`INTERFACE_INCLUDE_DIRECTORIES`](https://cmake.org/cmake/help/latest/prop_tgt/INTERFACE_INCLUDE_DIRECTORIES.html#prop_tgt:INTERFACE_INCLUDE_DIRECTORIES)的财产`<target>`。以下参数指定包含目录。

*3.11 版新功能：允许在*[IMPORTED 目标](https://cmake.org/cmake/help/latest/manual/cmake-buildsystem.7.html#imported-targets)上设置`INTERFACE`项目。

按调用顺序重复调用相同的`<target>`附加项。

如果`SYSTEM`指定，编译器将被告知目录在某些平台上是系统包含目录。这可能会产生诸如抑制警告或跳过依赖计算中包含的标头等效果（请参阅编译器文档）。此外，无论指定的顺序如何，都会在正常包含目录之后搜索系统包含目录。

如果`SYSTEM`与`PUBLIC`or一起使用`INTERFACE`，则 [`INTERFACE_SYSTEM_INCLUDE_DIRECTORIES`](https://cmake.org/cmake/help/latest/prop_tgt/INTERFACE_SYSTEM_INCLUDE_DIRECTORIES.html#prop_tgt:INTERFACE_SYSTEM_INCLUDE_DIRECTORIES)target 属性将填充指定的目录。

参数 to`target_include_directories`可以使用带有语法的“生成器表达式” `$<...>`。见[`cmake-generator-expressions(7)`](https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html#manual:cmake-generator-expressions(7)) 可用表达式的手册。见[`cmake-buildsystem(7)`](https://cmake.org/cmake/help/latest/manual/cmake-buildsystem.7.html#manual:cmake-buildsystem(7)) 有关定义构建系统属性的更多信息。

指定的包含目录可以是绝对路径或相对路径。相对路径将被解释为相对于当前源目录（即[`CMAKE_CURRENT_SOURCE_DIR`](https://cmake.org/cmake/help/latest/variable/CMAKE_CURRENT_SOURCE_DIR.html#variable:CMAKE_CURRENT_SOURCE_DIR)) 并在将其存储在关联的目标属性中之前转换为绝对路径。如果路径以生成器表达式开头，则始终假定它是绝对路径（下面指出一个例外）并且将不加修改地使用。

包含目录的使用要求通常在构建树和安装树之间有所不同。这[`BUILD_INTERFACE`](https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html#genex:BUILD_INTERFACE)和 [`INSTALL_INTERFACE`](https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html#genex:INSTALL_INTERFACE)生成器表达式可用于根据使用位置描述单独的使用要求。相对路径允许在[`INSTALL_INTERFACE`](https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html#genex:INSTALL_INTERFACE)表达式并被解释为相对于安装前缀。不应该使用相对路径[`BUILD_INTERFACE`](https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html#genex:BUILD_INTERFACE)表达式，因为它们不会被转换为绝对值。例如：

```cmake
target_include_directories(mylib PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/mylib>
  $<INSTALL_INTERFACE:include/mylib>  # <prefix>/include/mylib
)
```

## 创建可重定位包

请注意，不建议填充[`INSTALL_INTERFACE`](https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html#genex:INSTALL_INTERFACE)的[`INTERFACE_INCLUDE_DIRECTORIES`](https://cmake.org/cmake/help/latest/prop_tgt/INTERFACE_INCLUDE_DIRECTORIES.html#prop_tgt:INTERFACE_INCLUDE_DIRECTORIES)具有到依赖项的包含目录的绝对路径的目标。**这将硬编码到已安装的包中，包括在制作包的机器上找到的**依赖项的包含目录路径 。

这[`INSTALL_INTERFACE`](https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html#genex:INSTALL_INTERFACE)的[`INTERFACE_INCLUDE_DIRECTORIES`](https://cmake.org/cmake/help/latest/prop_tgt/INTERFACE_INCLUDE_DIRECTORIES.html#prop_tgt:INTERFACE_INCLUDE_DIRECTORIES)仅适用于为目标本身提供的标头指定所需的包含目录，而不是由其列出的传递依赖项提供的那些[`INTERFACE_LINK_LIBRARIES`](https://cmake.org/cmake/help/latest/prop_tgt/INTERFACE_LINK_LIBRARIES.html#prop_tgt:INTERFACE_LINK_LIBRARIES)目标财产。这些依赖项本身应该是在[`INTERFACE_INCLUDE_DIRECTORIES`](https://cmake.org/cmake/help/latest/prop_tgt/INTERFACE_INCLUDE_DIRECTORIES.html#prop_tgt:INTERFACE_INCLUDE_DIRECTORIES).

请参阅[创建可重定位包](https://cmake.org/cmake/help/latest/manual/cmake-packages.7.html#creating-relocatable-packages)部分 [`cmake-packages(7)`](https://cmake.org/cmake/help/latest/manual/cmake-packages.7.html#manual:cmake-packages(7))手册，用于讨论在创建用于重新分发的包时指定使用要求时必须注意的额外注意事项。



# [target_link_directories](https://cmake.org/cmake/help/latest/command/target_link_directories.html)

*3.13 版中的新功能。*

将链接目录添加到目标。

```cmake
target_link_directories(<target> [BEFORE]
  <INTERFACE|PUBLIC|PRIVATE> [items1...]
  [<INTERFACE|PUBLIC|PRIVATE> [items2...] ...])
```

指定链接器在链接给定目标时应在其中搜索库的路径。每个项目可以是绝对路径或相对路径，后者被解释为相对于当前源目录。这些项目将被添加到链接命令中。

名称`<target>`必须是由命令创建的，例如 [`add_executable()`](https://cmake.org/cmake/help/latest/command/add_executable.html#command:add_executable)或者[`add_library()`](https://cmake.org/cmake/help/latest/command/add_library.html#command:add_library)并且不能是 [ALIAS 目标](https://cmake.org/cmake/help/latest/manual/cmake-buildsystem.7.html#alias-targets)。

需要,`INTERFACE`和关键字`PUBLIC`来`PRIVATE`指定它们后面的项目的范围。 `PRIVATE`并且 `PUBLIC`项目将填充[`LINK_DIRECTORIES`](https://cmake.org/cmake/help/latest/prop_tgt/LINK_DIRECTORIES.html#prop_tgt:LINK_DIRECTORIES)的财产`<target>`。 `PUBLIC`并且`INTERFACE`项目将填充 [`INTERFACE_LINK_DIRECTORIES`](https://cmake.org/cmake/help/latest/prop_tgt/INTERFACE_LINK_DIRECTORIES.html#prop_tgt:INTERFACE_LINK_DIRECTORIES)`<target>` （[IMPORTED 目标](https://cmake.org/cmake/help/latest/manual/cmake-buildsystem.7.html#imported-targets)仅支持`INTERFACE`项目）的属性。每个项目都指定一个链接目录，如果需要，将在将其添加到相关属性之前将其转换为绝对路径。按调用顺序重复调用相同的`<target>`附加项。

如果`BEFORE`指定，内容将被附加到相关属性而不是被附加。

参数 to`target_link_directories`可以使用带有语法的“生成器表达式” `$<...>`。见[`cmake-generator-expressions(7)`](https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html#manual:cmake-generator-expressions(7)) 可用表达式的手册。见[`cmake-buildsystem(7)`](https://cmake.org/cmake/help/latest/manual/cmake-buildsystem.7.html#manual:cmake-buildsystem(7)) 有关定义构建系统属性的更多信息。

> **笔记** 此命令很少需要，在有其他选择时应避免使用。尽可能将完整的绝对路径传递给库，因为这样可以确保始终链接正确的库。这[`find_library()`](https://cmake.org/cmake/help/latest/command/find_library.html#command:find_library)命令提供完整路径，一般可以直接在调用中使用[`target_link_libraries()`](https://cmake.org/cmake/help/latest/command/target_link_libraries.html#command:target_link_libraries). 可能需要库搜索路径的情况包括：
>
> - 像 Xcode 这样的项目生成器，用户可以在构建时切换目标架构，但不能使用库的完整路径，因为它只提供一种架构（即它不是通用二进制文件）。
> - 库本身可能有其他私有库依赖项，这些依赖项期望通过`RPATH`机制找到，但一些链接器无法完全解码这些路径（例如，由于存在类似 的东西`$ORIGIN`）。

 

# [target_link_libraries](https://cmake.org/cmake/help/latest/command/target_link_libraries.html)

内容

- [target_link_libraries](https://cmake.org/cmake/help/latest/command/target_link_libraries.html#target-link-libraries)
  - [概述](https://cmake.org/cmake/help/latest/command/target_link_libraries.html#overview)
  - [目标和/或其依赖的库](https://cmake.org/cmake/help/latest/command/target_link_libraries.html#libraries-for-a-target-and-or-its-dependents)
  - [目标及其依赖的库](https://cmake.org/cmake/help/latest/command/target_link_libraries.html#libraries-for-both-a-target-and-its-dependents)
  - [目标和/或其依赖的库（旧版）](https://cmake.org/cmake/help/latest/command/target_link_libraries.html#libraries-for-a-target-and-or-its-dependents-legacy)
  - [仅限家属的图书馆（旧版）](https://cmake.org/cmake/help/latest/command/target_link_libraries.html#libraries-for-dependents-only-legacy)
  - [链接对象库](https://cmake.org/cmake/help/latest/command/target_link_libraries.html#linking-object-libraries)
    - [通过 $ 链接对象库](https://cmake.org/cmake/help/latest/command/target_link_libraries.html#linking-object-libraries-via-target-objects)
  - [静态库的循环依赖](https://cmake.org/cmake/help/latest/command/target_link_libraries.html#cyclic-dependencies-of-static-libraries)
  - [创建可重定位包](https://cmake.org/cmake/help/latest/command/target_link_libraries.html#creating-relocatable-packages)

指定链接给定目标和/或其依赖项时要使用的库或标志。 [来自链接库目标的使用要求](https://cmake.org/cmake/help/latest/manual/cmake-buildsystem.7.html#target-usage-requirements) 将被传播。目标依赖项的使用要求会影响其自身源的编译。

## [Overview](https://cmake.org/cmake/help/latest/command/target_link_libraries.html#id3)

该命令有几个签名，如下小节所述。它们都有一般形式

```cmake
target_link_libraries(<target> ... <item>... ...)
```

名称`<target>`必须是由命令创建的，例如 [`add_executable()`](https://cmake.org/cmake/help/latest/command/add_executable.html#command:add_executable)或者[`add_library()`](https://cmake.org/cmake/help/latest/command/add_library.html#command:add_library)并且不能是 [ALIAS 目标](https://cmake.org/cmake/help/latest/manual/cmake-buildsystem.7.html#alias-targets)。如果政策[`CMP0079`](https://cmake.org/cmake/help/latest/policy/CMP0079.html#policy:CMP0079)未设置为`NEW`则目标必须已在当前目录中创建。按调用顺序重复调用相同的`<target>`附加项。

*3.13 版中*的新功能：`<target>`不必在与 `target_link_libraries`调用相同的目录中定义。

每个`<item>`可能是：

- **库目标名称**：生成的链接行将具有与目标关联的可链接库文件的完整路径。`<target>`如果库文件更改，构建系统将具有重新链接的依赖项。

  命名目标必须由[`add_library()`](https://cmake.org/cmake/help/latest/command/add_library.html#command:add_library)在项目中或作为[导入库](https://cmake.org/cmake/help/latest/manual/cmake-buildsystem.7.html#imported-targets)。如果它是在项目中创建的，则会在构建系统中自动添加排序依赖项，以确保命名库目标在`<target>`链接之前是最新的。

  如果导入的库具有[`IMPORTED_NO_SONAME`](https://cmake.org/cmake/help/latest/prop_tgt/IMPORTED_NO_SONAME.html#prop_tgt:IMPORTED_NO_SONAME) 目标属性集，CMake 可能会要求链接器搜索库而不是使用完整路径（例如`/usr/lib/libfoo.so`become `-lfoo`）。

  目标工件的完整路径将自动为 shell 引用/转义。

- **库文件的完整路径**：生成的链接行通常会保留文件的完整路径。`<target>`如果库文件更改，构建系统将具有重新链接的依赖项。

  在某些情况下，CMake 可能会要求链接器搜索库（例如`/usr/lib/libfoo.so`become `-lfoo`），例如当检测到共享库没有`SONAME`字段时。查看政策[`CMP0060`](https://cmake.org/cmake/help/latest/policy/CMP0060.html#policy:CMP0060)讨论另一个案例。

  如果库文件在 macOS 框架中，框架的`Headers`目录也将作为 [使用要求](https://cmake.org/cmake/help/latest/manual/cmake-buildsystem.7.html#target-usage-requirements)进行处理。这与将框架目录作为包含目录传递的效果相同。

  *3.8 版新功能：*在[Visual Studio Generators](https://cmake.org/cmake/help/latest/manual/cmake-generators.7.html#visual-studio-generators) for VS 2010 及更高版本上，以 结尾的库文件`.targets`将被视为 MSBuild 目标文件并导入到生成的项目文件中。其他生成器不支持此功能。

  库文件的完整路径将自动为 shell 引用/转义。

- **一个普通的库名称**：生成的链接行将要求链接器搜索库（例如`foo`变成`-lfoo`或`foo.lib`）。

  库名称/标志被视为命令行字符串片段，将在没有额外引用或转义的情况下使用。

- **链接标志**：以 开头`-`但不是`-l`or 的项目名称`-framework`被视为链接器标志。请注意，出于传递依赖的目的，此类标志将被视为任何其他库链接项，因此通常将它们指定为不会传播给依赖项的私有链接项是安全的。

  此处指定的链接标志插入到链接命令中与链接库相同的位置。这可能不正确，具体取决于链接器。使用[`LINK_OPTIONS`](https://cmake.org/cmake/help/latest/prop_tgt/LINK_OPTIONS.html#prop_tgt:LINK_OPTIONS)目标财产或 [`target_link_options()`](https://cmake.org/cmake/help/latest/command/target_link_options.html#command:target_link_options)命令显式添加链接标志。然后，这些标志将放置在链接命令中工具链定义的标志位置。

  *3.13 版中的新功能：*[`LINK_OPTIONS`](https://cmake.org/cmake/help/latest/prop_tgt/LINK_OPTIONS.html#prop_tgt:LINK_OPTIONS)目标财产和[`target_link_options()`](https://cmake.org/cmake/help/latest/command/target_link_options.html#command:target_link_options) 命令。对于早期版本的 CMake，请使用[`LINK_FLAGS`](https://cmake.org/cmake/help/latest/prop_tgt/LINK_FLAGS.html#prop_tgt:LINK_FLAGS) 而是财产。

  链接标志被视为命令行字符串片段，将在没有额外引用或转义的情况下使用。

- **生成器表达式**：A`$<...>` [`generator expression`](https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html#manual:cmake-generator-expressions(7))可以评估任何上述项目或以[分号分隔的列表](https://cmake.org/cmake/help/latest/manual/cmake-language.7.html#cmake-language-lists)。如果`...`包含任何`;`字符，例如在评估`${list}`变量之后，请务必使用显式引用的参数`"$<...>"`，以便该命令将其作为单个 . 接收`<item>`。

  此外，生成器表达式可以用作上述任何项目的片段，例如`foo$<1:_d>`.

  请注意，生成器表达式不会用于 OLD 处理策略[`CMP0003`](https://cmake.org/cmake/help/latest/policy/CMP0003.html#policy:CMP0003)或政策[`CMP0004`](https://cmake.org/cmake/help/latest/policy/CMP0004.html#policy:CMP0004).

- 一个`debug`, `optimized`, 或`general`关键字紧跟在另一个之后`<item>`。此类关键字后面的项目将仅用于相应的构建配置。`debug`关键字对应于`Debug`配置（或在[`DEBUG_CONFIGURATIONS`](https://cmake.org/cmake/help/latest/prop_gbl/DEBUG_CONFIGURATIONS.html#prop_gbl:DEBUG_CONFIGURATIONS)全局属性（如果已设置）。该`optimized`关键字对应于所有其他配置。`general`关键字对应所有配置，纯属可选。 [通过创建和链接到IMPORTED 库目标](https://cmake.org/cmake/help/latest/manual/cmake-buildsystem.7.html#imported-targets)，可以为每个配置规则实现更高的粒度 。这些关键字由该命令立即解释，因此在由生成器表达式生成时没有特殊含义。

包含 的项目`::`，例如`Foo::Bar`，被假定为 [IMPORTED](https://cmake.org/cmake/help/latest/manual/cmake-buildsystem.7.html#imported-targets)或[ALIAS](https://cmake.org/cmake/help/latest/manual/cmake-buildsystem.7.html#alias-targets)库目标名称，如果不存在此类目标，则会导致错误。查看政策[`CMP0028`](https://cmake.org/cmake/help/latest/policy/CMP0028.html#policy:CMP0028).

见[`cmake-buildsystem(7)`](https://cmake.org/cmake/help/latest/manual/cmake-buildsystem.7.html#manual:cmake-buildsystem(7))有关定义构建系统属性的更多信息。

## [目标和/或其依赖的库](https://cmake.org/cmake/help/latest/command/target_link_libraries.html#id4)

```cmake
target_link_libraries(<target>
                      <PRIVATE|PUBLIC|INTERFACE> <item>...
                     [<PRIVATE|PUBLIC|INTERFACE> <item>...]...)
```

,`PUBLIC`和关键字可用于在一个命令中指定链接依赖项和链接接口`PRIVATE`。`INTERFACE`下面的库和目标`PUBLIC`链接到链接接口，并成为链接接口的一部分。下面的库和目标`PRIVATE` 链接到链接接口，但不是链接接口的一部分。以下库`INTERFACE`附加到链接接口，不用于链接`<target>`。

## [目标及其依赖的库](https://cmake.org/cmake/help/latest/command/target_link_libraries.html#id5)

```cmake
target_link_libraries(<target> <item>...)
```

默认情况下，使用此签名的库依赖项是可传递的。当这个目标链接到另一个目标时，链接到这个目标的库也将出现在另一个目标的链接行上。这个传递的“链接接口”存储在 [`INTERFACE_LINK_LIBRARIES`](https://cmake.org/cmake/help/latest/prop_tgt/INTERFACE_LINK_LIBRARIES.html#prop_tgt:INTERFACE_LINK_LIBRARIES)目标属性，并且可以通过直接设置属性来覆盖。什么时候[`CMP0022`](https://cmake.org/cmake/help/latest/policy/CMP0022.html#policy:CMP0022)未设置为 `NEW`，传递链接是内置的，但可能会被 [`LINK_INTERFACE_LIBRARIES`](https://cmake.org/cmake/help/latest/prop_tgt/LINK_INTERFACE_LIBRARIES.html#prop_tgt:LINK_INTERFACE_LIBRARIES)财产。调用此命令的其他签名可以设置属性，使该签名专门链接的任何库成为私有的。

## [目标和/或其依赖项（旧版）的库](https://cmake.org/cmake/help/latest/command/target_link_libraries.html#id6)

```cmake
target_link_libraries(<target>
                      <LINK_PRIVATE|LINK_PUBLIC> <lib>...
                     [<LINK_PRIVATE|LINK_PUBLIC> <lib>...]...)
```

和模式可用于在一个命令中指定链路依赖关系和链路接口`LINK_PUBLIC`。`LINK_PRIVATE`

此签名仅用于兼容性。更喜欢`PUBLIC`or `PRIVATE`关键字。

以下库和目标`LINK_PUBLIC`链接到并成为其中的一部分[`INTERFACE_LINK_LIBRARIES`](https://cmake.org/cmake/help/latest/prop_tgt/INTERFACE_LINK_LIBRARIES.html#prop_tgt:INTERFACE_LINK_LIBRARIES). 如果政策 [`CMP0022`](https://cmake.org/cmake/help/latest/policy/CMP0022.html#policy:CMP0022)不是`NEW`，它们也被做成了 [`LINK_INTERFACE_LIBRARIES`](https://cmake.org/cmake/help/latest/prop_tgt/LINK_INTERFACE_LIBRARIES.html#prop_tgt:LINK_INTERFACE_LIBRARIES). 以下库和目标 `LINK_PRIVATE`与 [`INTERFACE_LINK_LIBRARIES`](https://cmake.org/cmake/help/latest/prop_tgt/INTERFACE_LINK_LIBRARIES.html#prop_tgt:INTERFACE_LINK_LIBRARIES)（或者[`LINK_INTERFACE_LIBRARIES`](https://cmake.org/cmake/help/latest/prop_tgt/LINK_INTERFACE_LIBRARIES.html#prop_tgt:LINK_INTERFACE_LIBRARIES)).

## [仅受抚养人的库（旧版）](https://cmake.org/cmake/help/latest/command/target_link_libraries.html#id7)

```cmake
target_link_libraries(<target> LINK_INTERFACE_LIBRARIES <item>...)
```

该`LINK_INTERFACE_LIBRARIES`模式将库附加到 [`INTERFACE_LINK_LIBRARIES`](https://cmake.org/cmake/help/latest/prop_tgt/INTERFACE_LINK_LIBRARIES.html#prop_tgt:INTERFACE_LINK_LIBRARIES)目标属性，而不是使用它们进行链接。如果政策[`CMP0022`](https://cmake.org/cmake/help/latest/policy/CMP0022.html#policy:CMP0022)不是`NEW`，则此模式还将库附加到[`LINK_INTERFACE_LIBRARIES`](https://cmake.org/cmake/help/latest/prop_tgt/LINK_INTERFACE_LIBRARIES.html#prop_tgt:LINK_INTERFACE_LIBRARIES)及其每个配置的等效项。

此签名仅用于兼容性。`INTERFACE`而是更喜欢该模式。

指定为`debug`的库包含在生成器表达式中以对应于调试版本。如果政策[`CMP0022`](https://cmake.org/cmake/help/latest/policy/CMP0022.html#policy:CMP0022)不是`NEW`，这些库也附加到 [`LINK_INTERFACE_LIBRARIES_DEBUG`](https://cmake.org/cmake/help/latest/prop_tgt/LINK_INTERFACE_LIBRARIES_CONFIG.html#prop_tgt:LINK_INTERFACE_LIBRARIES_) 属性（或与列表中列出的配置相对应的属性）[`DEBUG_CONFIGURATIONS`](https://cmake.org/cmake/help/latest/prop_gbl/DEBUG_CONFIGURATIONS.html#prop_gbl:DEBUG_CONFIGURATIONS)全局属性（如果已设置）。指定为`optimized`的库附加到 [`INTERFACE_LINK_LIBRARIES`](https://cmake.org/cmake/help/latest/prop_tgt/INTERFACE_LINK_LIBRARIES.html#prop_tgt:INTERFACE_LINK_LIBRARIES)财产。如果政策[`CMP0022`](https://cmake.org/cmake/help/latest/policy/CMP0022.html#policy:CMP0022) 不是`NEW`，它们也附加到 [`LINK_INTERFACE_LIBRARIES`](https://cmake.org/cmake/help/latest/prop_tgt/LINK_INTERFACE_LIBRARIES.html#prop_tgt:LINK_INTERFACE_LIBRARIES)财产。指定为 `general`（或没有任何关键字）的库被视为同时为 `debug`和指定`optimized`。

## [链接对象库](https://cmake.org/cmake/help/latest/command/target_link_libraries.html#id8)

*版本 3.12 中的新功能。*

[对象库](https://cmake.org/cmake/help/latest/manual/cmake-buildsystem.7.html#object-libraries)可以用作`<target>`（第一个）参数`target_link_libraries`来指定它们的源对其他库的依赖关系。例如，代码

```cmake
add_library(A SHARED a.c)
target_compile_definitions(A PUBLIC A)

add_library(obj OBJECT obj.c)
target_compile_definitions(obj PUBLIC OBJ)
target_link_libraries(obj PUBLIC A)
```

编译`obj.c`并建立传播到其依赖项的使用要求。`-DA -DOBJ``obj`

普通库和可执行文件可以链接到[对象库](https://cmake.org/cmake/help/latest/manual/cmake-buildsystem.7.html#object-libraries) 以获取它们的对象和使用要求。继续上面的例子，代码

```cmake
add_library(B SHARED b.c)
target_link_libraries(B PUBLIC obj)
b.c`用编译，创建包含来自和 的目标文件的共享库，并链接到。此外，代码`-DA -DOBJ``B``b.c``obj.c``B``A
add_executable(main main.c)
target_link_libraries(main B)
```

编译`main.c`并链接可执行文件 到和。对象库的使用要求通过 传递，但其对象文件不是。`-DA -DOBJ``main``B``A``B`

[对象库](https://cmake.org/cmake/help/latest/manual/cmake-buildsystem.7.html#object-libraries)可以“链接”到其他对象库以获得使用要求，但由于它们没有链接步骤，因此不会对其对象文件进行任何操作。继续上面的例子，代码：

```cmake
add_library(obj2 OBJECT obj2.c)
target_link_libraries(obj2 PUBLIC obj)

add_executable(main2 main2.c)
target_link_libraries(main2 obj2)
```

用编译，`obj2.c`用 和 的目标文件创建可执行文件，并链接 到。`-DA -DOBJ``main2``main2.c``obj2.c``main2``A`

换句话说，当[对象库](https://cmake.org/cmake/help/latest/manual/cmake-buildsystem.7.html#object-libraries)出现在目标的 [`INTERFACE_LINK_LIBRARIES`](https://cmake.org/cmake/help/latest/prop_tgt/INTERFACE_LINK_LIBRARIES.html#prop_tgt:INTERFACE_LINK_LIBRARIES)属性它们将被视为[Interface Libraries](https://cmake.org/cmake/help/latest/manual/cmake-buildsystem.7.html#interface-libraries)，但是当它们出现在目标的[`LINK_LIBRARIES`](https://cmake.org/cmake/help/latest/prop_tgt/LINK_LIBRARIES.html#prop_tgt:LINK_LIBRARIES)属性他们的目标文件也将包含在链接中。



### [通过 $ 链接对象库](https://cmake.org/cmake/help/latest/command/target_link_libraries.html#id9)

*3.21 版中的新功能。*

与对象库关联的对象文件可以被[`$`](https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html#genex:TARGET_OBJECTS)生成器表达式。此类目标文件放置在所有库*之前的链接行上，无论它们的相对顺序如何。*此外，将向构建系统添加排序依赖项，以确保对象库在依赖目标链接之前是最新的。例如，代码

```cmake
add_library(obj3 OBJECT obj3.c)
target_compile_definitions(obj3 PUBLIC OBJ3)

add_executable(main3 main3.c)
target_link_libraries(main3 PRIVATE a3 $<TARGET_OBJECTS:obj3> b3)
```

将可执行文件与来自和 库的 目标`main3`文件链接起来。不使用. *_* _`main3.c``obj3.c``a3``b3``main3.c``obj3``-DOBJ3`

这种方法可用于实现目标文件在链接行中的传递包含作为使用要求。继续上面的例子，代码

```cmake
add_library(iface_obj3 INTERFACE)
target_link_libraries(iface_obj3 INTERFACE obj3 $<TARGET_OBJECTS:obj3>)
```

创建一个接口库`iface_obj3`，用于转发`obj3` 使用需求并将`obj3`目标文件添加到依赖项的链接行。编码

```cmake
add_executable(use_obj3 use_obj3.c)
target_link_libraries(use_obj3 PRIVATE iface_obj3)
use_obj3.c`与来自和 的目标文件一起编译`-DOBJ3`并链接可执行文件。`use_obj3``use_obj3.c``obj3.c
```

这也可以通过静态库传递。由于静态库不链接，因此它不会使用以这种方式引用的对象库中的对象文件。相反，目标文件成为静态库的传递链接依赖项。继续上面的例子，代码

```cmake
add_library(static3 STATIC static3.c)
target_link_libraries(static3 PRIVATE iface_obj3)

add_executable(use_static3 use_static3.c)
target_link_libraries(use_static3 PRIVATE static3)
```

仅使用其自己的目标文件进行 编译`static3.c`和`-DOBJ3`创建。编译*时没有，*因为使用要求不能通过. 但是，会传播 的链接依赖项，包括对 的引用。可执行文件是使用 和 中的目标文件创建的，并链接到 library 。`libstatic3.a``use_static3.c` `-DOBJ3``static3``static3``iface_obj3``$<TARGET_OBJECTS:obj3>``use_static3``use_static3.c``obj3.c``libstatic3.a`

使用这种方法时，项目有责任避免将多个依赖二进制文件链接到`iface_obj3`，因为它们都会`obj3`在其链接行上获取目标文件。

笔记

 

参考[`$`](https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html#genex:TARGET_OBJECTS)在`target_link_libraries` 某些情况下，在 3.21 之前的 CMake 版本中调用，但不完全支持：

- 它没有将目标文件放在链接行上的库之前。
- 它没有添加对对象库的排序依赖。
- 它不适用于具有多种架构的 Xcode。

## [静态库的循环依赖](https://cmake.org/cmake/help/latest/command/target_link_libraries.html#id10)

库依赖图通常是非循环的（DAG），但在相互依赖的`STATIC`库的情况下，CMake 允许图包含循环（强连接组件）。当另一个目标链接到其中一个库时，CMake 会重复整个连接的组件。例如，代码

```cmake
add_library(A STATIC a.c)
add_library(B STATIC b.c)
target_link_libraries(A B)
target_link_libraries(B A)
add_executable(main main.c)
target_link_libraries(main A)
```

链接`main`到. 虽然一次重复通常就足够了，但病态目标文件和符号排列可能需要更多。可以通过使用 `A B A B`[`LINK_INTERFACE_MULTIPLICITY`](https://cmake.org/cmake/help/latest/prop_tgt/LINK_INTERFACE_MULTIPLICITY.html#prop_tgt:LINK_INTERFACE_MULTIPLICITY)`target_link_libraries`target 属性或通过在上次调用中手动重复组件。但是，如果两个档案真的如此相互依赖，那么它们可能应该合并为一个档案，或许可以使用[Object Libraries](https://cmake.org/cmake/help/latest/manual/cmake-buildsystem.7.html#object-libraries)。

## [创建可重定位包](https://cmake.org/cmake/help/latest/command/target_link_libraries.html#id11)

请注意，不建议填充 [`INTERFACE_LINK_LIBRARIES`](https://cmake.org/cmake/help/latest/prop_tgt/INTERFACE_LINK_LIBRARIES.html#prop_tgt:INTERFACE_LINK_LIBRARIES)具有依赖项的绝对路径的目标。**这会将在制作包的机器上找到的**依赖项的库文件路径硬编码到已安装的包中。

请参阅[创建可重定位包](https://cmake.org/cmake/help/latest/manual/cmake-packages.7.html#creating-relocatable-packages)部分 [`cmake-packages(7)`](https://cmake.org/cmake/help/latest/manual/cmake-packages.7.html#manual:cmake-packages(7))手册，用于讨论在创建用于重新分发的包时指定使用要求时必须注意的额外注意事项。



# [target_link_options](https://cmake.org/cmake/help/latest/command/target_link_options.html)

*3.13 版中的新功能。*

为可执行文件、共享库或模块库目标的链接步骤添加选项。

```cmake
target_link_options(<target> [BEFORE]
  <INTERFACE|PUBLIC|PRIVATE> [items1...]
  [<INTERFACE|PUBLIC|PRIVATE> [items2...] ...])
```

名称`<target>`必须是由命令创建的，例如 [`add_executable()`](https://cmake.org/cmake/help/latest/command/add_executable.html#command:add_executable)或者[`add_library()`](https://cmake.org/cmake/help/latest/command/add_library.html#command:add_library)并且不能是 [ALIAS 目标](https://cmake.org/cmake/help/latest/manual/cmake-buildsystem.7.html#alias-targets)。

此命令可用于添加任何链接选项，但存在用于添加库的替代命令（[`target_link_libraries()`](https://cmake.org/cmake/help/latest/command/target_link_libraries.html#command:target_link_libraries)或者 [`link_libraries()`](https://cmake.org/cmake/help/latest/command/link_libraries.html#command:link_libraries)）。参见文档 [`directory`](https://cmake.org/cmake/help/latest/prop_dir/LINK_OPTIONS.html#prop_dir:LINK_OPTIONS)和 [`target`](https://cmake.org/cmake/help/latest/prop_tgt/LINK_OPTIONS.html#prop_tgt:LINK_OPTIONS) `LINK_OPTIONS`特性。

笔记

 

此命令不能用于为静态库目标添加选项，因为它们不使用链接器。要添加归档器或 MSVC 图书馆员标志，请参阅[`STATIC_LIBRARY_OPTIONS`](https://cmake.org/cmake/help/latest/prop_tgt/STATIC_LIBRARY_OPTIONS.html#prop_tgt:STATIC_LIBRARY_OPTIONS)目标财产。

如果`BEFORE`指定，内容将被附加到属性而不是被附加。

需要,`INTERFACE`和关键字`PUBLIC`来`PRIVATE`指定以下参数的范围。 `PRIVATE`并且`PUBLIC` 项目将填充[`LINK_OPTIONS`](https://cmake.org/cmake/help/latest/prop_tgt/LINK_OPTIONS.html#prop_tgt:LINK_OPTIONS)的财产 `<target>`。 `PUBLIC`并且`INTERFACE`项目将填充 [`INTERFACE_LINK_OPTIONS`](https://cmake.org/cmake/help/latest/prop_tgt/INTERFACE_LINK_OPTIONS.html#prop_tgt:INTERFACE_LINK_OPTIONS)的财产`<target>`。以下参数指定链接选项。按调用顺序重复调用相同的 `<target>`附加项。

笔记

 

[IMPORTED 目标](https://cmake.org/cmake/help/latest/manual/cmake-buildsystem.7.html#imported-targets)仅支持`INTERFACE`项目。

参数 to`target_link_options`可以使用带有语法的“生成器表达式” `$<...>`。见[`cmake-generator-expressions(7)`](https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html#manual:cmake-generator-expressions(7)) 可用表达式的手册。见[`cmake-buildsystem(7)`](https://cmake.org/cmake/help/latest/manual/cmake-buildsystem.7.html#manual:cmake-buildsystem(7)) 有关定义构建系统属性的更多信息。

## 主机和设备特定链接选项

*3.18 新版功能：*当涉及设备链接步骤时，由 [`CUDA_SEPARABLE_COMPILATION`](https://cmake.org/cmake/help/latest/prop_tgt/CUDA_SEPARABLE_COMPILATION.html#prop_tgt:CUDA_SEPARABLE_COMPILATION)和 [`CUDA_RESOLVE_DEVICE_SYMBOLS`](https://cmake.org/cmake/help/latest/prop_tgt/CUDA_RESOLVE_DEVICE_SYMBOLS.html#prop_tgt:CUDA_RESOLVE_DEVICE_SYMBOLS)属性和政策[`CMP0105`](https://cmake.org/cmake/help/latest/policy/CMP0105.html#policy:CMP0105)，原始选项将被传递到主机和设备链接步骤（包装在 设备链接中`-Xcompiler`或等效的设备链接中）。包裹的选项 `$<DEVICE_LINK:...>` [`generator expression`](https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html#manual:cmake-generator-expressions(7))将仅用于设备链接步骤。包裹的选项`$<HOST_LINK:...>` [`generator expression`](https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html#manual:cmake-generator-expressions(7))将仅用于主机链接步骤。

## 去重选项

用于目标的最终选项集是通过累积来自当前目标的选项及其依赖项的使用要求来构建的。对选项集进行重复数据删除以避免重复。

*3.12 版中的新功能：*虽然有利于单个选项，但重复数据删除步骤可以分解选项组。例如，变成 。可以使用类似 shell 的引用和前缀来指定一组选项。前缀被删除，其余的选项字符串使用 `-option A -option B``-option A B``SHELL:``SHELL:`[`separate_arguments()`](https://cmake.org/cmake/help/latest/command/separate_arguments.html#command:separate_arguments) `UNIX_COMMAND`模式。例如， 变成。`"SHELL:-option A" "SHELL:-option B"``-option A -option B`

## 处理编译器驱动程序差异

要将选项传递给链接器工具，每个编译器驱动程序都有自己的语法。`LINKER:`前缀和分隔符可用于以可移植的`,`方式指定传递给链接器工具的选项。`LINKER:`由适当的驱动程序选项和`,`适当的驱动程序分隔符替换。驱动程序前缀和驱动程序分隔符由 [`CMAKE__LINKER_WRAPPER_FLAG`](https://cmake.org/cmake/help/latest/variable/CMAKE_LANG_LINKER_WRAPPER_FLAG.html#variable:CMAKE__LINKER_WRAPPER_FLAG)和 [`CMAKE__LINKER_WRAPPER_FLAG_SEP`](https://cmake.org/cmake/help/latest/variable/CMAKE_LANG_LINKER_WRAPPER_FLAG_SEP.html#variable:CMAKE__LINKER_WRAPPER_FLAG_SEP)变量。

例如，`"LINKER:-z,defs"`变为for 和for 。`-Xlinker -z -Xlinker defs``Clang``-Wl,-z,defs``GNU GCC`

`LINKER:`前缀可以指定为`SHELL:`前缀表达式的一部分。

```cmake
LINKER:`作为替代语法，前缀支持使用前缀和空格作为分隔符的参数规范`SHELL:`。前面的例子就变成了。`"LINKER:SHELL:-z defs"
```

> **笔记** 不支持在前缀`SHELL:`开头以外的任何位置 指定前缀。`LINKER:`

 

# [target_precompile_headers](https://cmake.org/cmake/help/latest/command/target_precompile_headers.html)

*3.16 版中的新功能。*

添加要预编译的头文件列表。

预编译头文件可以通过创建一些头文件的部分处理版本，然后在编译期间使用该版本而不是重复解析原始头文件来加速编译。

## 主窗体

```cmake
target_precompile_headers(<target>
  <INTERFACE|PUBLIC|PRIVATE> [header1...]
  [<INTERFACE|PUBLIC|PRIVATE> [header2...] ...])
```

该命令将头文件添加到[`PRECOMPILE_HEADERS`](https://cmake.org/cmake/help/latest/prop_tgt/PRECOMPILE_HEADERS.html#prop_tgt:PRECOMPILE_HEADERS)和/或 [`INTERFACE_PRECOMPILE_HEADERS`](https://cmake.org/cmake/help/latest/prop_tgt/INTERFACE_PRECOMPILE_HEADERS.html#prop_tgt:INTERFACE_PRECOMPILE_HEADERS)的目标属性`<target>`。名称`<target>`必须是由命令创建的，例如 [`add_executable()`](https://cmake.org/cmake/help/latest/command/add_executable.html#command:add_executable)或者[`add_library()`](https://cmake.org/cmake/help/latest/command/add_library.html#command:add_library)并且不能是 [ALIAS 目标](https://cmake.org/cmake/help/latest/manual/cmake-buildsystem.7.html#alias-targets)。

需要,`INTERFACE`和关键字`PUBLIC`来`PRIVATE`指定以下参数的范围。 `PRIVATE`并且`PUBLIC` 项目将填充[`PRECOMPILE_HEADERS`](https://cmake.org/cmake/help/latest/prop_tgt/PRECOMPILE_HEADERS.html#prop_tgt:PRECOMPILE_HEADERS)的财产 `<target>`。 `PUBLIC`并且`INTERFACE`项目将填充 [`INTERFACE_PRECOMPILE_HEADERS`](https://cmake.org/cmake/help/latest/prop_tgt/INTERFACE_PRECOMPILE_HEADERS.html#prop_tgt:INTERFACE_PRECOMPILE_HEADERS)`<target>` （[IMPORTED 目标](https://cmake.org/cmake/help/latest/manual/cmake-buildsystem.7.html#imported-targets)仅支持`INTERFACE`项目）的属性。对相同的重复调用`<target>`将按照调用的顺序附加项目。

项目通常应该避免使用`PUBLIC`或`INTERFACE`用于将被[导出](https://cmake.org/cmake/help/latest/command/install.html#install-export)的目标，或者他们至少应该使用[`$`](https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html#genex:BUILD_INTERFACE)生成器表达式以防止预编译头出现在已安装的导出目标中。目标的使用者通常应该控制他们使用的预编译头文件，而不是被正在使用的目标强制预编译头文件（因为预编译头文件通常不是使用要求）。一个值得注意的例外是创建[接口库](https://cmake.org/cmake/help/latest/manual/cmake-buildsystem.7.html#interface-libraries)以在一个地方定义一组常用的预编译头文件，然后其他目标私下链接到该接口库。在这种情况下，接口库的存在专门用于将预编译头文件传播给它的消费者，消费者实际上仍然处于控制之中，因为它决定是否链接到接口库。

头文件列表用于生成名为的头文件 ，该头文件`cmake_pch.h|xx`用于生成预编译的头文件 ( `.pch`, `.gch`, `.pchi`) 工件。头`cmake_pch.h|xx`文件将被强制包含（`-include`对于 GCC，`/FI`对于 MSVC）所有源文件，所以源不需要有.`#include "pch.h"`

用尖括号（例如`<unordered_map>`）或显式双引号指定的头文件名（转义为[`cmake-language(7)`](https://cmake.org/cmake/help/latest/manual/cmake-language.7.html#manual:cmake-language(7)), eg `[["other_header.h"]]`) 将被按原样处理，并且包含目录必须可供编译器找到它们。其他头文件名（例如`project_header.h`）被解释为相对于当前源目录（例如[`CMAKE_CURRENT_SOURCE_DIR`](https://cmake.org/cmake/help/latest/variable/CMAKE_CURRENT_SOURCE_DIR.html#variable:CMAKE_CURRENT_SOURCE_DIR)) 并将包含在绝对路径中。例如：

```cmake
target_precompile_headers(myTarget
  PUBLIC
    project_header.h
  PRIVATE
    [["other_header.h"]]
    <unordered_map>
)
```

参数 to`target_precompile_headers()`可以使用带有语法的“生成器表达式” `$<...>`。见[`cmake-generator-expressions(7)`](https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html#manual:cmake-generator-expressions(7))可用表达式的手册。这[`$`](https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html#genex:COMPILE_LANGUAGE)生成器表达式对于指定特定于语言的标头以仅针对一种语言（例如`CXX`和 not `C`）进行预编译特别有用。在这种情况下，没有在双引号或尖括号中明确显示的头文件名必须由绝对路径指定。此外，在生成器表达式中指定尖括号时，请务必将结尾编码`>`为 `$<ANGLE-R>`. 例如：

```cmake
target_precompile_headers(mylib PRIVATE
  "$<$<COMPILE_LANGUAGE:CXX>:${CMAKE_CURRENT_SOURCE_DIR}/cxx_only.h>"
  "$<$<COMPILE_LANGUAGE:C>:<stddef.h$<ANGLE-R>>"
  "$<$<COMPILE_LANGUAGE:CXX>:<cstddef$<ANGLE-R>>"
)
```

## 重用预编译头

该命令还支持第二个签名，可用于指定一个目标重用来自另一个目标的预编译头文件工件，而不是生成自己的：

```cmake
target_precompile_headers(<target> REUSE_FROM <other_target>)
```

此表格设置[`PRECOMPILE_HEADERS_REUSE_FROM`](https://cmake.org/cmake/help/latest/prop_tgt/PRECOMPILE_HEADERS_REUSE_FROM.html#prop_tgt:PRECOMPILE_HEADERS_REUSE_FROM)属性 `<other_target>`并添加一个依赖项，该依赖项`<target>`将依赖于`<other_target>`. 如果出现错误，CMake 将停止 [`PRECOMPILE_HEADERS`](https://cmake.org/cmake/help/latest/prop_tgt/PRECOMPILE_HEADERS.html#prop_tgt:PRECOMPILE_HEADERS)使用表单`<target>`时已经设置了of 的属性。`REUSE_FROM`

笔记

 

该`REUSE_FROM`表单需要相同的一组编译器选项、编译器标志和编译器`<target>`定义 `<other_target>`。如果无法使用预编译的头文件（`-Winvalid-pch`），某些编译器（例如 GCC）可能会发出警告。

## 另见

要禁用特定目标的预编译头，请参阅 [`DISABLE_PRECOMPILE_HEADERS`](https://cmake.org/cmake/help/latest/prop_tgt/DISABLE_PRECOMPILE_HEADERS.html#prop_tgt:DISABLE_PRECOMPILE_HEADERS)目标财产。

要防止在编译特定源文件时使用预编译头文件，请参阅[`SKIP_PRECOMPILE_HEADERS`](https://cmake.org/cmake/help/latest/prop_sf/SKIP_PRECOMPILE_HEADERS.html#prop_sf:SKIP_PRECOMPILE_HEADERS)源文件属性。



# [target_sources](https://cmake.org/cmake/help/latest/command/target_sources.html)

*3.1 版中的新功能。*

将源添加到目标。

```cmake
target_sources(<target>
  <INTERFACE|PUBLIC|PRIVATE> [items1...]
  [<INTERFACE|PUBLIC|PRIVATE> [items2...] ...])
```

指定构建目标和/或其依赖项时要使用的源。名称`<target>`必须是由命令创建的，例如 [`add_executable()`](https://cmake.org/cmake/help/latest/command/add_executable.html#command:add_executable)或者[`add_library()`](https://cmake.org/cmake/help/latest/command/add_library.html#command:add_library)或者 [`add_custom_target()`](https://cmake.org/cmake/help/latest/command/add_custom_target.html#command:add_custom_target)并且不能是 [ALIAS 目标](https://cmake.org/cmake/help/latest/manual/cmake-buildsystem.7.html#alias-targets)。`<items>`可以 使用[`generator expressions`](https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html#manual:cmake-generator-expressions(7)).

*3.20 版中的新功能：*`<target>`可以是自定义目标。

需要,`INTERFACE`和关键字`PUBLIC`来`PRIVATE`指定源文件路径 ( `<items>`) 的范围。 `PRIVATE`并且`PUBLIC`项目将填充[`SOURCES`](https://cmake.org/cmake/help/latest/prop_tgt/SOURCES.html#prop_tgt:SOURCES) 的属性`<target>`，在构建目标本身时使用。 `PUBLIC`并且`INTERFACE`项目将填充 [`INTERFACE_SOURCES`](https://cmake.org/cmake/help/latest/prop_tgt/INTERFACE_SOURCES.html#prop_tgt:INTERFACE_SOURCES)的属性`<target>`，在构建依赖项时使用。由创建的目标[`add_custom_target()`](https://cmake.org/cmake/help/latest/command/add_custom_target.html#command:add_custom_target) 只能有`PRIVATE`范围。

按调用顺序重复调用相同的`<target>`附加项。

*3.3 版中的新功能：*允许导出目标[`INTERFACE_SOURCES`](https://cmake.org/cmake/help/latest/prop_tgt/INTERFACE_SOURCES.html#prop_tgt:INTERFACE_SOURCES).

*3.11 版新功能：允许在*[IMPORTED 目标](https://cmake.org/cmake/help/latest/manual/cmake-buildsystem.7.html#imported-targets)上设置`INTERFACE`项目 。

*在 3.13 版更改：*相对源文件路径被解释为相对于当前源目录（即[`CMAKE_CURRENT_SOURCE_DIR`](https://cmake.org/cmake/help/latest/variable/CMAKE_CURRENT_SOURCE_DIR.html#variable:CMAKE_CURRENT_SOURCE_DIR)）。查看政策[`CMP0076`](https://cmake.org/cmake/help/latest/policy/CMP0076.html#policy:CMP0076).

以生成器表达式开头的路径保持不变。当一个目标[`SOURCE_DIR`](https://cmake.org/cmake/help/latest/prop_tgt/SOURCE_DIR.html#prop_tgt:SOURCE_DIR)属性不同于 [`CMAKE_CURRENT_SOURCE_DIR`](https://cmake.org/cmake/help/latest/variable/CMAKE_CURRENT_SOURCE_DIR.html#variable:CMAKE_CURRENT_SOURCE_DIR)，在生成器表达式中使用绝对路径以确保源正确分配给目标。

```cmake
# WRONG: starts with generator expression, but relative path used
target_sources(MyTarget PRIVATE "$<$<CONFIG:Debug>:dbgsrc.cpp>")

# CORRECT: absolute path used inside the generator expression
target_sources(MyTarget PRIVATE "$<$<CONFIG:Debug>:${CMAKE_CURRENT_SOURCE_DIR}/dbgsrc.cpp>")
```

见[`cmake-buildsystem(7)`](https://cmake.org/cmake/help/latest/manual/cmake-buildsystem.7.html#manual:cmake-buildsystem(7))有关定义构建系统属性的更多信息。

## 文件集

*版本 3.23 中的新功能。*

```cmake
target_sources(<target>
  [<INTERFACE|PUBLIC|PRIVATE>
   [FILE_SET <set> [TYPE <type>] [BASE_DIRS <dirs>...] [FILES <files>...]]...
  ]...)
```

将文件集添加到目标，或将文件添加到现有文件集。目标具有零个或多个命名文件集。每个文件集都有一个名称、一个类型、一个、一个或多个基本目录的范围 ，`INTERFACE`以及这些目录中的文件。唯一可接受的类型是. 可选的默认文件集以其类型命名。目标可能不是自定义目标或`PUBLIC``PRIVATE``HEADERS`[`FRAMEWORK`](https://cmake.org/cmake/help/latest/prop_tgt/FRAMEWORK.html#prop_tgt:FRAMEWORK)目标。

出于 IDE 集成的目的，一个`PRIVATE`或`PUBLIC`文件集中的文件被标记为源文件。此外，文件集中的`HEADERS`文件有自己的[`HEADER_FILE_ONLY`](https://cmake.org/cmake/help/latest/prop_sf/HEADER_FILE_ONLY.html#prop_sf:HEADER_FILE_ONLY)属性设置为`TRUE`。一个 `INTERFACE`或`PUBLIC`文件集中的文件可以用 [`install(TARGETS)`](https://cmake.org/cmake/help/latest/command/install.html#command:install)命令，并使用 [`install(EXPORT)`](https://cmake.org/cmake/help/latest/command/install.html#command:install)和[`export()`](https://cmake.org/cmake/help/latest/command/export.html#command:export)命令。

每个`target_sources(FILE_SET)`条目都以`INTERFACE`、`PUBLIC`或 开头，`PRIVATE`并接受以下参数：

```cmake
FILE_SET <set>
```

> 要创建或添加到的文件集的名称。它只能包含字母、数字和下划线。以大写字母开头的名称保留给 CMake 预定义的内置文件集。唯一预定义的集合名称是 `HEADERS`. 所有其他集合名称不得以大写字母或下划线开头。

```cmake
TYPE <type>
```

> 每个文件集都与特定类型的文件相关联。`HEADERS` 是当前唯一定义的类型，指定其他类型是错误的。作为一种特殊情况，如果文件集的名称是`HEADERS`，则不需要指定类型，并且可以省略参数。对于所有其他文件集名称，是必需的。`TYPE <type>``TYPE`

```cmake
BASE_DIRS <dirs>...
```

> 文件集的基本目录的可选列表。任何相对路径都被视为相对于当前源目录（即[`CMAKE_CURRENT_SOURCE_DIR`](https://cmake.org/cmake/help/latest/variable/CMAKE_CURRENT_SOURCE_DIR.html#variable:CMAKE_CURRENT_SOURCE_DIR)）。如果`BASE_DIRS`第一次创建文件集时没有指定，则值为 [`CMAKE_CURRENT_SOURCE_DIR`](https://cmake.org/cmake/help/latest/variable/CMAKE_CURRENT_SOURCE_DIR.html#variable:CMAKE_CURRENT_SOURCE_DIR)被添加。这个论据支持 [`generator expressions`](https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html#manual:cmake-generator-expressions(7)).
>
> 一个文件集的两个基本目录不能是彼此的子目录。必须在添加到文件集中的所有基本目录中满足此要求，而不仅仅是对`target_sources()`.

```cmake
FILES <files>...
```

> 要添加到文件集中的可选文件列表。每个文件必须位于基本目录之一或基本目录之一的子目录中。这个论据支持 [`generator expressions`](https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html#manual:cmake-generator-expressions(7)).
>
> 如果指定了相对路径，则它们被认为是相对于 [`CMAKE_CURRENT_SOURCE_DIR`](https://cmake.org/cmake/help/latest/variable/CMAKE_CURRENT_SOURCE_DIR.html#variable:CMAKE_CURRENT_SOURCE_DIR)当时`target_sources()`叫。一个例外是以 . 开头的路径`$<`。在评估生成器表达式之后，此类路径被视为相对于目标的源目录。

以下目标属性由 设置`target_sources(FILE_SET)`，但通常不应直接操作它们：

- [`HEADER_SETS`](https://cmake.org/cmake/help/latest/prop_tgt/HEADER_SETS.html#prop_tgt:HEADER_SETS)
- [`INTERFACE_HEADER_SETS`](https://cmake.org/cmake/help/latest/prop_tgt/INTERFACE_HEADER_SETS.html#prop_tgt:INTERFACE_HEADER_SETS)
- [`HEADER_SET`](https://cmake.org/cmake/help/latest/prop_tgt/HEADER_SET.html#prop_tgt:HEADER_SET)
- [`HEADER_SET_`](https://cmake.org/cmake/help/latest/prop_tgt/HEADER_SET_NAME.html#prop_tgt:HEADER_SET_)
- [`HEADER_DIRS`](https://cmake.org/cmake/help/latest/prop_tgt/HEADER_DIRS.html#prop_tgt:HEADER_DIRS)
- [`HEADER_DIRS_`](https://cmake.org/cmake/help/latest/prop_tgt/HEADER_DIRS_NAME.html#prop_tgt:HEADER_DIRS_)

与包含目录相关的目标属性也修改 `target_sources(FILE_SET)`如下：

[`INCLUDE_DIRECTORIES`](https://cmake.org/cmake/help/latest/prop_tgt/INCLUDE_DIRECTORIES.html#prop_tgt:INCLUDE_DIRECTORIES)

> 如果`TYPE`是`HEADERS`，并且文件集的范围是`PRIVATE` 或`PUBLIC`，则所有`BASE_DIRS`文件集都包含在 [`$`](https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html#genex:BUILD_INTERFACE)并附加到此属性。

[`INTERFACE_INCLUDE_DIRECTORIES`](https://cmake.org/cmake/help/latest/prop_tgt/INTERFACE_INCLUDE_DIRECTORIES.html#prop_tgt:INTERFACE_INCLUDE_DIRECTORIES)

> 如果`TYPE`是`HEADERS`，并且文件集的范围是 `INTERFACE`或`PUBLIC`，则所有`BASE_DIRS`文件集都包含在[`$`](https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html#genex:BUILD_INTERFACE)并附加到此属性。



# [try_compile](https://cmake.org/cmake/help/latest/command/try_compile.html)

内容

- [尝试编译](https://cmake.org/cmake/help/latest/command/try_compile.html#try-compile)
  - [尝试编译整个项目](https://cmake.org/cmake/help/latest/command/try_compile.html#try-compiling-whole-projects)
  - [尝试编译源文件](https://cmake.org/cmake/help/latest/command/try_compile.html#try-compiling-source-files)
  - [其他行为设置](https://cmake.org/cmake/help/latest/command/try_compile.html#other-behavior-settings)

尝试构建一些代码。



## [尝试编译整个项目](https://cmake.org/cmake/help/latest/command/try_compile.html#id4)

```cmake
try_compile(<resultVar> <bindir> <srcdir>
            <projectName> [<targetName>] [CMAKE_FLAGS <flags>...]
            [OUTPUT_VARIABLE <var>])
```

尝试构建一个项目。的成功或失败`try_compile`，即`TRUE`或`FALSE`分别返回`<resultVar>`。

在这种形式中，`<srcdir>`应该包含一个带有 `CMakeLists.txt`文件和所有源的完整 CMake 项目。运行此 命令后不会删除`<bindir>`and 。`<srcdir>`指定`<targetName>`构建特定目标而不是`all`or`ALL_BUILD`目标。其他选项的含义见下文。

*在 3.24 版更改：*描述平台设置的 CMake 变量，以及由 [`CMAKE_TRY_COMPILE_PLATFORM_VARIABLES`](https://cmake.org/cmake/help/latest/variable/CMAKE_TRY_COMPILE_PLATFORM_VARIABLES.html#variable:CMAKE_TRY_COMPILE_PLATFORM_VARIABLES)变量，被传播到项目的构建配置中。查看政策[`CMP0137`](https://cmake.org/cmake/help/latest/policy/CMP0137.html#policy:CMP0137). 以前这仅由 [源文件](https://cmake.org/cmake/help/latest/command/try_compile.html#try-compiling-source-files)签名完成。



## [尝试编译源文件](https://cmake.org/cmake/help/latest/command/try_compile.html#id5)

```cmake
try_compile(<resultVar> <bindir> <srcfile|SOURCES srcfile...>
            [CMAKE_FLAGS <flags>...]
            [COMPILE_DEFINITIONS <defs>...]
            [LINK_OPTIONS <options>...]
            [LINK_LIBRARIES <libs>...]
            [OUTPUT_VARIABLE <var>]
            [COPY_FILE <fileName> [COPY_FILE_ERROR <var>]]
            [<LANG>_STANDARD <std>]
            [<LANG>_STANDARD_REQUIRED <bool>]
            [<LANG>_EXTENSIONS <bool>]
            )
```

尝试从一个或多个源文件（哪一个由[`CMAKE_TRY_COMPILE_TARGET_TYPE`](https://cmake.org/cmake/help/latest/variable/CMAKE_TRY_COMPILE_TARGET_TYPE.html#variable:CMAKE_TRY_COMPILE_TARGET_TYPE) 多变的）。的成功或失败`try_compile`，即`TRUE`或 `FALSE`分别返回`<resultVar>`。

在这种形式中，必须提供一个或多个源文件。如果 [`CMAKE_TRY_COMPILE_TARGET_TYPE`](https://cmake.org/cmake/help/latest/variable/CMAKE_TRY_COMPILE_TARGET_TYPE.html#variable:CMAKE_TRY_COMPILE_TARGET_TYPE)未设置或设置为`EXECUTABLE`，源必须包含定义`main`，CMake 将创建一个 `CMakeLists.txt`文件以将源构建为可执行文件。如果[`CMAKE_TRY_COMPILE_TARGET_TYPE`](https://cmake.org/cmake/help/latest/variable/CMAKE_TRY_COMPILE_TARGET_TYPE.html#variable:CMAKE_TRY_COMPILE_TARGET_TYPE)设置为`STATIC_LIBRARY`，将生成一个静态库，并且不需要定义 for `main`。对于可执行文件，生成的`CMakeLists.txt`文件将包含如下内容：

```cmake
add_definitions(<expanded COMPILE_DEFINITIONS from caller>)
include_directories(${INCLUDE_DIRECTORIES})
link_directories(${LINK_DIRECTORIES})
add_executable(cmTryCompileExec <srcfile>...)
target_link_options(cmTryCompileExec PRIVATE <LINK_OPTIONS from caller>)
target_link_libraries(cmTryCompileExec ${LINK_LIBRARIES})
```

选项包括：

- `CMAKE_FLAGS <flags>...`

  `-DVAR:TYPE=VALUE`指定要传递给`cmake`用于驱动测试构建的命令行的表单标志。上面的示例显示了如何使用变量 `INCLUDE_DIRECTORIES`、`LINK_DIRECTORIES`和`LINK_LIBRARIES` 的值。

- `COMPILE_DEFINITIONS <defs>...`

  指定`-Ddefinition`要传递给的参数[`add_definitions()`](https://cmake.org/cmake/help/latest/command/add_definitions.html#command:add_definitions) 在生成的测试项目中。

- `COPY_FILE <fileName>`

  将构建的可执行文件或静态库复制到给定的`<fileName>`.

- `COPY_FILE_ERROR <var>`

  使用 after将尝试复制文件时遇到的任何错误消息`COPY_FILE`捕获到变量中。`<var>`

- `LINK_LIBRARIES <libs>...`

  指定要在生成的项目中链接的库。库列表可以引用系统库和 来自调用项目的[导入目标。](https://cmake.org/cmake/help/latest/manual/cmake-buildsystem.7.html#imported-targets)如果指定了此选项，则任何`-DLINK_LIBRARIES=...`赋予该`CMAKE_FLAGS`选项的值都将被忽略。

- `LINK_OPTIONS <options>...`

  *版本 3.14 中的新功能。*指定要传递给的链接步骤选项[`target_link_options()`](https://cmake.org/cmake/help/latest/command/target_link_options.html#command:target_link_options)或设置[`STATIC_LIBRARY_OPTIONS`](https://cmake.org/cmake/help/latest/prop_tgt/STATIC_LIBRARY_OPTIONS.html#prop_tgt:STATIC_LIBRARY_OPTIONS)生成项目中的目标属性，具体取决于[`CMAKE_TRY_COMPILE_TARGET_TYPE`](https://cmake.org/cmake/help/latest/variable/CMAKE_TRY_COMPILE_TARGET_TYPE.html#variable:CMAKE_TRY_COMPILE_TARGET_TYPE)多变的。

- `OUTPUT_VARIABLE <var>`

  将构建过程的输出存储在给定的变量中。

- `<LANG>_STANDARD <std>`

  *3.8 版中的新功能。*指定[`C_STANDARD`](https://cmake.org/cmake/help/latest/prop_tgt/C_STANDARD.html#prop_tgt:C_STANDARD), [`CXX_STANDARD`](https://cmake.org/cmake/help/latest/prop_tgt/CXX_STANDARD.html#prop_tgt:CXX_STANDARD), [`OBJC_STANDARD`](https://cmake.org/cmake/help/latest/prop_tgt/OBJC_STANDARD.html#prop_tgt:OBJC_STANDARD),[`OBJCXX_STANDARD`](https://cmake.org/cmake/help/latest/prop_tgt/OBJCXX_STANDARD.html#prop_tgt:OBJCXX_STANDARD)， 或者[`CUDA_STANDARD`](https://cmake.org/cmake/help/latest/prop_tgt/CUDA_STANDARD.html#prop_tgt:CUDA_STANDARD)生成项目的目标属性。

- `<LANG>_STANDARD_REQUIRED <bool>`

  *3.8 版中的新功能。*指定[`C_STANDARD_REQUIRED`](https://cmake.org/cmake/help/latest/prop_tgt/C_STANDARD_REQUIRED.html#prop_tgt:C_STANDARD_REQUIRED), [`CXX_STANDARD_REQUIRED`](https://cmake.org/cmake/help/latest/prop_tgt/CXX_STANDARD_REQUIRED.html#prop_tgt:CXX_STANDARD_REQUIRED), [`OBJC_STANDARD_REQUIRED`](https://cmake.org/cmake/help/latest/prop_tgt/OBJC_STANDARD_REQUIRED.html#prop_tgt:OBJC_STANDARD_REQUIRED), [`OBJCXX_STANDARD_REQUIRED`](https://cmake.org/cmake/help/latest/prop_tgt/OBJCXX_STANDARD_REQUIRED.html#prop_tgt:OBJCXX_STANDARD_REQUIRED)，或者[`CUDA_STANDARD_REQUIRED`](https://cmake.org/cmake/help/latest/prop_tgt/CUDA_STANDARD_REQUIRED.html#prop_tgt:CUDA_STANDARD_REQUIRED) 生成项目的目标属性。

- `<LANG>_EXTENSIONS <bool>`

  *3.8 版中的新功能。*指定[`C_EXTENSIONS`](https://cmake.org/cmake/help/latest/prop_tgt/C_EXTENSIONS.html#prop_tgt:C_EXTENSIONS),[`CXX_EXTENSIONS`](https://cmake.org/cmake/help/latest/prop_tgt/CXX_EXTENSIONS.html#prop_tgt:CXX_EXTENSIONS), [`OBJC_EXTENSIONS`](https://cmake.org/cmake/help/latest/prop_tgt/OBJC_EXTENSIONS.html#prop_tgt:OBJC_EXTENSIONS),[`OBJCXX_EXTENSIONS`](https://cmake.org/cmake/help/latest/prop_tgt/OBJCXX_EXTENSIONS.html#prop_tgt:OBJCXX_EXTENSIONS)， 或者[`CUDA_EXTENSIONS`](https://cmake.org/cmake/help/latest/prop_tgt/CUDA_EXTENSIONS.html#prop_tgt:CUDA_EXTENSIONS)生成项目的目标属性。

在这个版本中，所有文件都`<bindir>/CMakeFiles/CMakeTmp`将被自动清理。对于调试，`--debug-trycompile`可以通过 to`cmake`来避免这种清理。但是，多个顺序 `try_compile`操作会重用这个单一的输出目录。如果使用 `--debug-trycompile`，则一次只能调试一个`try_compile`调用。建议的过程是`try_compile`通过逻辑保护项目中的所有调用，使用 cmake 配置一次，然后删除与感兴趣的 try_compile 调用关联的缓存条目，然后再次使用 .run 重新运行 cmake 。`if(NOT DEFINED <resultVar>)``--debug-trycompile`

## [其他行为设置](https://cmake.org/cmake/help/latest/command/try_compile.html#id6)

*3.4 版新功能：*如果设置，则将以下变量传递给生成的 try_compile CMakeLists.txt 以使用默认值初始化编译目标属性：

- [`CMAKE_CUDA_RUNTIME_LIBRARY`](https://cmake.org/cmake/help/latest/variable/CMAKE_CUDA_RUNTIME_LIBRARY.html#variable:CMAKE_CUDA_RUNTIME_LIBRARY)
- [`CMAKE_ENABLE_EXPORTS`](https://cmake.org/cmake/help/latest/variable/CMAKE_ENABLE_EXPORTS.html#variable:CMAKE_ENABLE_EXPORTS)
- [`CMAKE_LINK_SEARCH_START_STATIC`](https://cmake.org/cmake/help/latest/variable/CMAKE_LINK_SEARCH_START_STATIC.html#variable:CMAKE_LINK_SEARCH_START_STATIC)
- [`CMAKE_LINK_SEARCH_END_STATIC`](https://cmake.org/cmake/help/latest/variable/CMAKE_LINK_SEARCH_END_STATIC.html#variable:CMAKE_LINK_SEARCH_END_STATIC)
- [`CMAKE_MSVC_RUNTIME_LIBRARY`](https://cmake.org/cmake/help/latest/variable/CMAKE_MSVC_RUNTIME_LIBRARY.html#variable:CMAKE_MSVC_RUNTIME_LIBRARY)
- [`CMAKE_POSITION_INDEPENDENT_CODE`](https://cmake.org/cmake/help/latest/variable/CMAKE_POSITION_INDEPENDENT_CODE.html#variable:CMAKE_POSITION_INDEPENDENT_CODE)
- [`CMAKE_WATCOM_RUNTIME_LIBRARY`](https://cmake.org/cmake/help/latest/variable/CMAKE_WATCOM_RUNTIME_LIBRARY.html#variable:CMAKE_WATCOM_RUNTIME_LIBRARY)

如果[`CMP0056`](https://cmake.org/cmake/help/latest/policy/CMP0056.html#policy:CMP0056)设置为`NEW`，则 [`CMAKE_EXE_LINKER_FLAGS`](https://cmake.org/cmake/help/latest/variable/CMAKE_EXE_LINKER_FLAGS.html#variable:CMAKE_EXE_LINKER_FLAGS)也被传入。

*在 3.14 版更改:*如果[`CMP0083`](https://cmake.org/cmake/help/latest/policy/CMP0083.html#policy:CMP0083)设置为`NEW`，然后为了在链接时获得正确的行为，`check_pie_supported()`来自 [`CheckPIESupported`](https://cmake.org/cmake/help/latest/module/CheckPIESupported.html#module:CheckPIESupported)模块必须在使用之前调用 [`try_compile()`](https://cmake.org/cmake/help/latest/command/try_compile.html#command:try_compile)命令。

的当前设置[`CMP0065`](https://cmake.org/cmake/help/latest/policy/CMP0065.html#policy:CMP0065)和[`CMP0083`](https://cmake.org/cmake/help/latest/policy/CMP0083.html#policy:CMP0083)传播到生成的测试项目。

设置[`CMAKE_TRY_COMPILE_CONFIGURATION`](https://cmake.org/cmake/help/latest/variable/CMAKE_TRY_COMPILE_CONFIGURATION.html#variable:CMAKE_TRY_COMPILE_CONFIGURATION)变量来选择构建配置。

*3.6 版新功能：*设置[`CMAKE_TRY_COMPILE_TARGET_TYPE`](https://cmake.org/cmake/help/latest/variable/CMAKE_TRY_COMPILE_TARGET_TYPE.html#variable:CMAKE_TRY_COMPILE_TARGET_TYPE)变量来指定用于源文件签名的目标类型。

*3.6 版新功能：*设置[`CMAKE_TRY_COMPILE_PLATFORM_VARIABLES`](https://cmake.org/cmake/help/latest/variable/CMAKE_TRY_COMPILE_PLATFORM_VARIABLES.html#variable:CMAKE_TRY_COMPILE_PLATFORM_VARIABLES)variable 来指定必须传播到测试项目中的变量。此变量仅用于工具链文件，并且仅 `try_compile()`在源文件形式的命令中使用，而不是在给定整个项目时使用。

*在 3.8 版更改:*如果[`CMP0067`](https://cmake.org/cmake/help/latest/policy/CMP0067.html#policy:CMP0067)设置为`NEW`，或使用任何`<LANG>_STANDARD`、 `<LANG>_STANDARD_REQUIRED`、 或`<LANG>_EXTENSIONS`选项，则遵循语言标准变量：

- [`CMAKE_C_STANDARD`](https://cmake.org/cmake/help/latest/variable/CMAKE_C_STANDARD.html#variable:CMAKE_C_STANDARD)
- [`CMAKE_C_STANDARD_REQUIRED`](https://cmake.org/cmake/help/latest/variable/CMAKE_C_STANDARD_REQUIRED.html#variable:CMAKE_C_STANDARD_REQUIRED)
- [`CMAKE_C_EXTENSIONS`](https://cmake.org/cmake/help/latest/variable/CMAKE_C_EXTENSIONS.html#variable:CMAKE_C_EXTENSIONS)
- [`CMAKE_CXX_STANDARD`](https://cmake.org/cmake/help/latest/variable/CMAKE_CXX_STANDARD.html#variable:CMAKE_CXX_STANDARD)
- [`CMAKE_CXX_STANDARD_REQUIRED`](https://cmake.org/cmake/help/latest/variable/CMAKE_CXX_STANDARD_REQUIRED.html#variable:CMAKE_CXX_STANDARD_REQUIRED)
- [`CMAKE_CXX_EXTENSIONS`](https://cmake.org/cmake/help/latest/variable/CMAKE_CXX_EXTENSIONS.html#variable:CMAKE_CXX_EXTENSIONS)
- [`CMAKE_OBJC_STANDARD`](https://cmake.org/cmake/help/latest/variable/CMAKE_OBJC_STANDARD.html#variable:CMAKE_OBJC_STANDARD)
- [`CMAKE_OBJC_STANDARD_REQUIRED`](https://cmake.org/cmake/help/latest/variable/CMAKE_OBJC_STANDARD_REQUIRED.html#variable:CMAKE_OBJC_STANDARD_REQUIRED)
- [`CMAKE_OBJC_EXTENSIONS`](https://cmake.org/cmake/help/latest/variable/CMAKE_OBJC_EXTENSIONS.html#variable:CMAKE_OBJC_EXTENSIONS)
- [`CMAKE_OBJCXX_STANDARD`](https://cmake.org/cmake/help/latest/variable/CMAKE_OBJCXX_STANDARD.html#variable:CMAKE_OBJCXX_STANDARD)
- [`CMAKE_OBJCXX_STANDARD_REQUIRED`](https://cmake.org/cmake/help/latest/variable/CMAKE_OBJCXX_STANDARD_REQUIRED.html#variable:CMAKE_OBJCXX_STANDARD_REQUIRED)
- [`CMAKE_OBJCXX_EXTENSIONS`](https://cmake.org/cmake/help/latest/variable/CMAKE_OBJCXX_EXTENSIONS.html#variable:CMAKE_OBJCXX_EXTENSIONS)
- [`CMAKE_CUDA_STANDARD`](https://cmake.org/cmake/help/latest/variable/CMAKE_CUDA_STANDARD.html#variable:CMAKE_CUDA_STANDARD)
- [`CMAKE_CUDA_STANDARD_REQUIRED`](https://cmake.org/cmake/help/latest/variable/CMAKE_CUDA_STANDARD_REQUIRED.html#variable:CMAKE_CUDA_STANDARD_REQUIRED)
- [`CMAKE_CUDA_EXTENSIONS`](https://cmake.org/cmake/help/latest/variable/CMAKE_CUDA_EXTENSIONS.html#variable:CMAKE_CUDA_EXTENSIONS)

它们的值用于在生成的项目中设置相应的目标属性（除非被显式选项覆盖）。

*在 3.14 版更改：*对于[`Green Hills MULTI`](https://cmake.org/cmake/help/latest/generator/Green Hills MULTI.html#generator:Green Hills MULTI)生成器 GHS 工具集和目标系统自定义缓存变量也会传播到测试项目中。

*3.24 版中*的新功能：[`CMAKE_TRY_COMPILE_NO_PLATFORM_VARIABLES`](https://cmake.org/cmake/help/latest/variable/CMAKE_TRY_COMPILE_NO_PLATFORM_VARIABLES.html#variable:CMAKE_TRY_COMPILE_NO_PLATFORM_VARIABLES)变量可以设置为禁止将平台变量传递到测试项目中。



# [try_run](https://cmake.org/cmake/help/latest/command/try_run.html)

  内容

- [尝试运行](https://cmake.org/cmake/help/latest/command/try_run.html#try-run)
  - [尝试编译和运行源文件](https://cmake.org/cmake/help/latest/command/try_run.html#try-compiling-and-running-source-files)
  - [其他行为设置](https://cmake.org/cmake/help/latest/command/try_run.html#other-behavior-settings)
  - [交叉编译时的行为](https://cmake.org/cmake/help/latest/command/try_run.html#behavior-when-cross-compiling)

尝试编译然后运行一些代码。

## [尝试编译和运行源文件](https://cmake.org/cmake/help/latest/command/try_run.html#id2)

```cmake
try_run(<runResultVar> <compileResultVar>
        <bindir> <srcfile> [CMAKE_FLAGS <flags>...]
        [COMPILE_DEFINITIONS <defs>...]
        [LINK_OPTIONS <options>...]
        [LINK_LIBRARIES <libs>...]
        [COMPILE_OUTPUT_VARIABLE <var>]
        [RUN_OUTPUT_VARIABLE <var>]
        [OUTPUT_VARIABLE <var>]
        [WORKING_DIRECTORY <var>]
        [ARGS <args>...])
```

尝试编译一个`<srcfile>`. 返回`TRUE`或`FALSE`中的成功或失败`<compileResultVar>`。如果编译成功，则运行可执行文件并以`<runResultVar>`. 如果可执行文件已构建，但未能运行，`<runResultVar>`则将设置为`FAILED_TO_RUN`. 见[`try_compile()`](https://cmake.org/cmake/help/latest/command/try_compile.html#command:try_compile)命令以获取有关如何构建测试项目以构建源文件的信息。

选项包括：

- `CMAKE_FLAGS <flags>...`

  `-DVAR:TYPE=VALUE`指定要传递给`cmake`用于驱动测试构建的命令行的表单标志。中的示例[`try_compile()`](https://cmake.org/cmake/help/latest/command/try_compile.html#command:try_compile)显示如何使用变量 `INCLUDE_DIRECTORIES`、`LINK_DIRECTORIES`和`LINK_LIBRARIES` 的值。

- `COMPILE_DEFINITIONS <defs>...`

  指定`-Ddefinition`要传递给的参数[`add_definitions()`](https://cmake.org/cmake/help/latest/command/add_definitions.html#command:add_definitions) 在生成的测试项目中。

- `COMPILE_OUTPUT_VARIABLE <var>`

  报告给定变量中的编译步骤构建输出。

- `LINK_LIBRARIES <libs>...`

  *3.2 版中的新功能。*指定要在生成的项目中链接的库。库列表可以引用系统库和 来自调用项目的[导入目标。](https://cmake.org/cmake/help/latest/manual/cmake-buildsystem.7.html#imported-targets)如果指定了此选项，则任何`-DLINK_LIBRARIES=...`赋予该`CMAKE_FLAGS`选项的值都将被忽略。

- `LINK_OPTIONS <options>...`

  *版本 3.14 中的新功能。*指定要传递给的链接步骤选项[`target_link_options()`](https://cmake.org/cmake/help/latest/command/target_link_options.html#command:target_link_options)在生成的项目中。

- `OUTPUT_VARIABLE <var>`

  报告编译生成输出和在给定变量中运行可执行文件的输出。由于遗留原因，此选项存在。宁可 `COMPILE_OUTPUT_VARIABLE`取而代之`RUN_OUTPUT_VARIABLE`。

- `RUN_OUTPUT_VARIABLE <var>`

  报告在给定变量中运行可执行文件的输出。

- `WORKING_DIRECTORY <var>`

  *3.20 版中的新功能。*在给定目录中运行可执行文件。如果没有`WORKING_DIRECTORY`指定，可执行文件将在`<bindir>`.

## [其他行为设置](https://cmake.org/cmake/help/latest/command/try_run.html#id3)

设置[`CMAKE_TRY_COMPILE_CONFIGURATION`](https://cmake.org/cmake/help/latest/variable/CMAKE_TRY_COMPILE_CONFIGURATION.html#variable:CMAKE_TRY_COMPILE_CONFIGURATION)变量来选择构建配置。

## [交叉编译时的行为](https://cmake.org/cmake/help/latest/command/try_run.html#id4)

*3.3 版中的新功能：*`CMAKE_CROSSCOMPILING_EMULATOR`在运行交叉编译的二进制文件时使用。

交叉编译时，第一步编译的可执行文件通常无法在构建主机上运行。该`try_run`命令检查[`CMAKE_CROSSCOMPILING`](https://cmake.org/cmake/help/latest/variable/CMAKE_CROSSCOMPILING.html#variable:CMAKE_CROSSCOMPILING)变量来检测 CMake 是否处于交叉编译模式。如果是这种情况，它仍然会尝试编译可执行文件，但不会尝试运行可执行文件，除非 [`CMAKE_CROSSCOMPILING_EMULATOR`](https://cmake.org/cmake/help/latest/variable/CMAKE_CROSSCOMPILING_EMULATOR.html#variable:CMAKE_CROSSCOMPILING_EMULATOR)变量已设置。相反，它将创建缓存变量，这些变量必须由用户填充，或者通过在某些 CMake 脚本文件中将它们预设为可执行文件在其实际目标平台上运行时会产生的值。这些缓存条目是：

- `<runResultVar>`

  如果可执行文件要在目标平台上运行，则退出代码。

- `<runResultVar>__TRYRUN_OUTPUT`

  如果可执行文件要在目标平台上运行，则从 stdout 和 stderr 输出。仅当使用 `RUN_OUTPUT_VARIABLE`or`OUTPUT_VARIABLE`选项时才会创建。

为了使交叉编译您的项目更容易，请`try_run` 仅在确实需要时使用。如果您使用`try_run`，请 仅在确实需要时使用`RUN_OUTPUT_VARIABLE`or选项。`OUTPUT_VARIABLE`使用它们需要在交叉编译时，必须手动将缓存变量设置为可执行文件的输出。您还可以`try_run`使用[`if()`](https://cmake.org/cmake/help/latest/command/if.html#command:if) 块检查[`CMAKE_CROSSCOMPILING`](https://cmake.org/cmake/help/latest/variable/CMAKE_CROSSCOMPILING.html#variable:CMAKE_CROSSCOMPILING)变量并为这种情况提供易于预设的替代方案。




# [add_test](https://cmake.org/cmake/help/latest/command/add_test.html)

向要运行的项目添加测试[`ctest(1)`](https://cmake.org/cmake/help/latest/manual/ctest.1.html#manual:ctest(1)).

```cmake
add_test(NAME <name> COMMAND <command> [<arg>...]
         [CONFIGURATIONS <config>...]
         [WORKING_DIRECTORY <dir>]
         [COMMAND_EXPAND_LISTS])
```

添加一个名为`<name>`. 测试名称可以包含任意字符， 如有必要，表示为带[引号的参数](https://cmake.org/cmake/help/latest/manual/cmake-language.7.html#quoted-argument)或[括号参数。](https://cmake.org/cmake/help/latest/manual/cmake-language.7.html#bracket-argument)查看政策[`CMP0110`](https://cmake.org/cmake/help/latest/policy/CMP0110.html#policy:CMP0110). 选项包括：

- `COMMAND`

  指定测试命令行。如果`<command>`指定一个可执行目标（由[`add_executable()`](https://cmake.org/cmake/help/latest/command/add_executable.html#command:add_executable)) 它将自动替换为构建时创建的可执行文件的位置。该命令可以使用指定 [`generator expressions`](https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html#manual:cmake-generator-expressions(7)).

- `CONFIGURATIONS`

  将测试的执行仅限于指定的配置。

- `WORKING_DIRECTORY`

  设置[`WORKING_DIRECTORY`](https://cmake.org/cmake/help/latest/prop_test/WORKING_DIRECTORY.html#prop_test:WORKING_DIRECTORY)test 属性来指定执行测试的工作目录。如果未指定，则测试将在当前工作目录设置为与当前源目录对应的构建目录的情况下运行。可以使用指定工作目录 [`generator expressions`](https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html#manual:cmake-generator-expressions(7)).

- `COMMAND_EXPAND_LISTS`

  *3.16 版中的新功能。*参数中的列表`COMMAND`将被扩展，包括那些使用 [`generator expressions`](https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html#manual:cmake-generator-expressions(7)).

给定的测试命令预计将退出，代码`0`通过，非零失败，反之亦然，如果[`WILL_FAIL`](https://cmake.org/cmake/help/latest/prop_test/WILL_FAIL.html#prop_test:WILL_FAIL)测试属性已设置。写入 stdout 或 stderr 的任何输出都将被[`ctest(1)`](https://cmake.org/cmake/help/latest/manual/ctest.1.html#manual:ctest(1))但不影响通过/失败状态，除非[`PASS_REGULAR_EXPRESSION`](https://cmake.org/cmake/help/latest/prop_test/PASS_REGULAR_EXPRESSION.html#prop_test:PASS_REGULAR_EXPRESSION), [`FAIL_REGULAR_EXPRESSION`](https://cmake.org/cmake/help/latest/prop_test/FAIL_REGULAR_EXPRESSION.html#prop_test:FAIL_REGULAR_EXPRESSION)或者 [`SKIP_REGULAR_EXPRESSION`](https://cmake.org/cmake/help/latest/prop_test/SKIP_REGULAR_EXPRESSION.html#prop_test:SKIP_REGULAR_EXPRESSION)使用测试属性。

*3.16 版新功能：*已添加[`SKIP_REGULAR_EXPRESSION`](https://cmake.org/cmake/help/latest/prop_test/SKIP_REGULAR_EXPRESSION.html#prop_test:SKIP_REGULAR_EXPRESSION)财产。

`add_test(NAME)`使用签名支持 添加的测试[`generator expressions`](https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html#manual:cmake-generator-expressions(7)) 在由设置的测试属性中[`set_property(TEST)`](https://cmake.org/cmake/help/latest/command/set_property.html#command:set_property)或者 [`set_tests_properties()`](https://cmake.org/cmake/help/latest/command/set_tests_properties.html#command:set_tests_properties).

示例用法：

```cmake
add_test(NAME mytest
         COMMAND testDriver --config $<CONFIG>
                            --exe $<TARGET_FILE:myexe>)
```

这将创建一个测试`mytest`，其命令运行一个`testDriver`工具，传递配置名称和由 target 生成的可执行文件的完整路径`myexe`。

> **笔记 **CMake 将仅在以下情况下生成测试[`enable_testing()`](https://cmake.org/cmake/help/latest/command/enable_testing.html#command:enable_testing) 命令已被调用。这[`CTest`](https://cmake.org/cmake/help/latest/module/CTest.html#module:CTest)`BUILD_TESTING`除非打开该选项， 否则模块会自动调用该命令`OFF`。

------

此命令还支持更简单但不太灵活的签名：

```cmake
add_test(<name> <command> [<arg>...])
```

`<name>`添加使用给定命令行调用的测试。

与上述`NAME`签名不同，命令行中不支持目标名称。此外，使用此签名添加的测试不支持[`generator expressions`](https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html#manual:cmake-generator-expressions(7)) 在命令行或测试属性中。



# [set_tests_properties](https://cmake.org/cmake/help/latest/command/set_tests_properties.html)

设置测试的属性。

```cmake
set_tests_properties(test1 [test2...] PROPERTIES prop1 value1 prop2 value2)
```

设置测试的属性。如果没有找到测试，CMake 会报错。

可以使用指定测试属性值 [`generator expressions`](https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html#manual:cmake-generator-expressions(7)) 对于由[`add_test(NAME)`](https://cmake.org/cmake/help/latest/command/add_test.html#command:add_test)签名。

另见[`set_property(TEST)`](https://cmake.org/cmake/help/latest/command/set_property.html#command:set_property)命令。

有关CMake 已知的属性列表，请参阅[测试上的属性。](https://cmake.org/cmake/help/latest/manual/cmake-properties.7.html#test-properties)



# [get_test_property](https://cmake.org/cmake/help/latest/command/get_test_property.html)

获取测试的属性。

```cmake
get_test_property(test property VAR)
```

从测试中获取一个属性。属性的值存储在变量中`VAR`。如果未找到测试属性，则行为取决于它是否已被定义为`INHERITED`属性（请参阅[`define_property()`](https://cmake.org/cmake/help/latest/command/define_property.html#command:define_property)）。非继承属性将设置`VAR`为“NOTFOUND”，而继承属性将搜索相关的父范围，如[`define_property()`](https://cmake.org/cmake/help/latest/command/define_property.html#command:define_property) 命令，如果仍然无法找到该属性，`VAR`将设置为空字符串。

对于标准属性列表，您可以键入。`cmake --help-property-list`

另见更一般的[`get_property()`](https://cmake.org/cmake/help/latest/command/get_property.html#command:get_property)命令。



# [enable_testing](https://cmake.org/cmake/help/latest/command/enable_testing.html)

启用当前目录及以下目录的测试。

```cmake
enable_testing()
```

启用对此目录及以下目录的测试。

该命令应该在源目录根目录中，因为 ctest 期望在构建目录根目录中找到一个测试文件。

该命令在执行时自动调用[`CTest`](https://cmake.org/cmake/help/latest/module/CTest.html#module:CTest) 模块包括在内，除非该`BUILD_TESTING`选项被关闭。

另见[`add_test()`](https://cmake.org/cmake/help/latest/command/add_test.html#command:add_test)命令。



# [create_test_sourcelist](https://cmake.org/cmake/help/latest/command/create_test_sourcelist.html)

创建用于构建测试程序的测试驱动程序和源列表。

```cmake
create_test_sourcelist(sourceListName driverName
                       test1 test2 test3
                       EXTRA_INCLUDE include.h
                       FUNCTION function)
```

测试驱动程序是将许多小测试链接到一个可执行文件中的程序。这在使用大型库构建静态可执行文件以缩小所需的总大小时很有用。构建测试驱动程序所需的源文件列表将位于 `sourceListName`. `driverName`是测试驱动程序的名称。其余参数由测试源文件列表组成，可以用分号分隔。每个测试源文件都应该有一个函数，它与没有扩展名的文件同名（foo.cxx 应该有 int foo(int, char*[]);）`driverName`将能够按名称调用每个测试在命令行上。如果`EXTRA_INCLUDE`指定，则下一个参数将包含在生成的文件中。如果`FUNCTION`被指定，那么下一个参数被当作一个函数名，它被传递一个指向 ac 和 av 的指针。这可用于为每个测试添加额外的命令行处理。可以将 `CMAKE_TESTDRIVER_BEFORE_TESTMAIN`cmake 变量设置为在调用测试主函数之前直接放置的代码。 `CMAKE_TESTDRIVER_AFTER_TESTMAIN`可以设置为在调用测试主函数之后直接放置代码。
