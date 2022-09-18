# [cmake 语言(7) ](https://cmake.org/cmake/help/latest/manual/cmake-language.7.html#id9)

内容

- [cmake 语言(7)](https://cmake.org/cmake/help/latest/manual/cmake-language.7.html#cmake-language-7)
  - [组织](https://cmake.org/cmake/help/latest/manual/cmake-language.7.html#organization)
    - [目录](https://cmake.org/cmake/help/latest/manual/cmake-language.7.html#directories)
    - [脚本](https://cmake.org/cmake/help/latest/manual/cmake-language.7.html#scripts)
    - [模块](https://cmake.org/cmake/help/latest/manual/cmake-language.7.html#modules)
  - [句法](https://cmake.org/cmake/help/latest/manual/cmake-language.7.html#syntax)
    - [编码](https://cmake.org/cmake/help/latest/manual/cmake-language.7.html#encoding)
    - [源文件](https://cmake.org/cmake/help/latest/manual/cmake-language.7.html#source-files)
    - [命令调用](https://cmake.org/cmake/help/latest/manual/cmake-language.7.html#command-invocations)
    - [命令参数](https://cmake.org/cmake/help/latest/manual/cmake-language.7.html#command-arguments)
      - [括号参数](https://cmake.org/cmake/help/latest/manual/cmake-language.7.html#bracket-argument)
      - [引用的论点](https://cmake.org/cmake/help/latest/manual/cmake-language.7.html#quoted-argument)
      - [未引用的参数](https://cmake.org/cmake/help/latest/manual/cmake-language.7.html#unquoted-argument)
    - [转义序列](https://cmake.org/cmake/help/latest/manual/cmake-language.7.html#escape-sequences)
    - [变量引用](https://cmake.org/cmake/help/latest/manual/cmake-language.7.html#variable-references)
    - [注释](https://cmake.org/cmake/help/latest/manual/cmake-language.7.html#comments)
      - [括号注释](https://cmake.org/cmake/help/latest/manual/cmake-language.7.html#bracket-comment)
      - [行注释](https://cmake.org/cmake/help/latest/manual/cmake-language.7.html#line-comment)
  - [控制结构](https://cmake.org/cmake/help/latest/manual/cmake-language.7.html#control-structures)
    - [条件块](https://cmake.org/cmake/help/latest/manual/cmake-language.7.html#conditional-blocks)
    - [循环](https://cmake.org/cmake/help/latest/manual/cmake-language.7.html#loops)
    - [命令定义](https://cmake.org/cmake/help/latest/manual/cmake-language.7.html#command-definitions)
  - [变量](https://cmake.org/cmake/help/latest/manual/cmake-language.7.html#variables)
  - [环境变量](https://cmake.org/cmake/help/latest/manual/cmake-language.7.html#environment-variables)
  - [列表](https://cmake.org/cmake/help/latest/manual/cmake-language.7.html#lists)

## [Organization](https://cmake.org/cmake/help/latest/manual/cmake-language.7.html#id10)

CMake 输入文件以“CMake 语言”编写在`CMakeLists.txt`以文件扩展名命名或结尾的源文件中`.cmake`。

项目中的 CMake 语言源文件被组织成：

- [目录](https://cmake.org/cmake/help/latest/manual/cmake-language.7.html#directories)( `CMakeLists.txt`),
- [脚本](https://cmake.org/cmake/help/latest/manual/cmake-language.7.html#scripts)( `<script>.cmake`) 和
- [模块](https://cmake.org/cmake/help/latest/manual/cmake-language.7.html#modules)( `<module>.cmake`)。

### [Directories](https://cmake.org/cmake/help/latest/manual/cmake-language.7.html#id11)

`CMakeLists.txt`当 CMake 处理项目源代码树时，入口点是在顶级源目录中调用的源文件。该文件可能包含整个构建规范或使用[`add_subdirectory()`](https://cmake.org/cmake/help/latest/command/add_subdirectory.html#command:add_subdirectory)命令将子目录添加到构建中。该命令添加的每个子目录还必须包含一个`CMakeLists.txt`文件作为该目录的入口点。对于每个`CMakeLists.txt`处理其文件的源目录，CMake 在构建树中生成一个相应的目录，作为默认的工作和输出目录。

### [Scripts](https://cmake.org/cmake/help/latest/manual/cmake-language.7.html#id12)

<script>.cmake可以使用脚本模式处理单个源文件cmake(1)-P带有选项的命令行工具。脚本模式只运行给定 CMake 语言源文件中的命令，不会生成构建系统。它不允许定义构建目标或操作的 CMake 命令。

### [Modules](https://cmake.org/cmake/help/latest/manual/cmake-language.7.html#id13)

[目录](https://cmake.org/cmake/help/latest/manual/cmake-language.7.html#directories)或[脚本](https://cmake.org/cmake/help/latest/manual/cmake-language.7.html#scripts)中的 CMake 语言代码可以使用[`include()`](https://cmake.org/cmake/help/latest/command/include.html#command:include)命令在包含上下文的范围内加载`<module>.cmake` 源文件。见[`cmake-modules(7)`](https://cmake.org/cmake/help/latest/manual/cmake-modules.7.html#manual:cmake-modules(7))CMake 发行版中包含的模块文档的手册页。项目源代码树也可以提供它们自己的模块并在[`CMAKE_MODULE_PATH`](https://cmake.org/cmake/help/latest/variable/CMAKE_MODULE_PATH.html#variable:CMAKE_MODULE_PATH) 多变的。

## [Syntax](https://cmake.org/cmake/help/latest/manual/cmake-language.7.html#id14)



### [Encoding](https://cmake.org/cmake/help/latest/manual/cmake-language.7.html#id15)

CMake 语言源文件可以用 7 位 ASCII 文本编写，以便在所有支持的平台上实现最大的可移植性。换行符可以被编码为`\n`或者`\r\n`但将在`\n` 读取输入文件时转换为。

请注意，该实现是 8 位干净的，因此源文件可以在具有支持此编码的系统 API 的平台上编码为 UTF-8。此外，CMake 3.2 及以上版本支持 Windows 上以 UTF-8 编码的源文件（使用 UTF-16 调用系统 API）。此外，CMake 3.0 及更高版本允许 在源文件中使用前导 UTF-8[字节顺序标记。](http://en.wikipedia.org/wiki/Byte_order_mark)

### [源文件](https://cmake.org/cmake/help/latest/manual/cmake-language.7.html#id16)

CMake 语言源文件由零个或多个 [命令调用](https://cmake.org/cmake/help/latest/manual/cmake-language.7.html#command-invocations)组成，这些命令调用由换行符和可选的空格和[注释](https://cmake.org/cmake/help/latest/manual/cmake-language.7.html#comments)分隔：

```
文件        ::=   file_element*
文件元素::=   |command_invocation line_ending
                  (bracket_comment|space)* line_ending
行尾::=   line_comment? 空格       ::= <match '[ \t]+'>
换行     ::= <match '\n'>
newline
```

请注意，不在[Command Arguments](https://cmake.org/cmake/help/latest/manual/cmake-language.7.html#command-arguments)或[Bracket Comment](https://cmake.org/cmake/help/latest/manual/cmake-language.7.html#bracket-comment)中的任何源文件行都可以以[Line Comment](https://cmake.org/cmake/help/latest/manual/cmake-language.7.html#line-comment)结尾。



### [命令调用](https://cmake.org/cmake/help/latest/manual/cmake-language.7.html#id17)

*命令调用*是一个名称，后跟用空格分隔的括号括起来的参数：

```
command_invocation ::=   space* * '(' ')'
标识符         ::= <match '[A-Za-z_][A-Za-z0-9_]*'>
参数          ::=   ? *
identifier spaceargumentsargumentseparated_arguments分离参数 ::=   separation+ argument? |
                         separation* '(' arguments')'
分隔         ::=   space|line_ending
```

例如：

```
add_executable(hello world.c)
```

命令名称不区分大小写。参数中嵌套的不带引号的括号必须平衡。每个`(`or都作为文字[Unquoted Argument](https://cmake.org/cmake/help/latest/manual/cmake-language.7.html#unquoted-argument)`)`提供给命令调用。这可以用于调用[`if()`](https://cmake.org/cmake/help/latest/command/if.html#command:if)命令包围条件。例如：

```
if(FALSE AND (FALSE OR TRUE)) # evaluates to FALSE
```

笔记

 

3.0 之前的 CMake 版本要求命令名称标识符至少为 2 个字符。

2.8.12 之前的 CMake 版本静默接受不带[引号的](https://cmake.org/cmake/help/latest/manual/cmake-language.7.html#quoted-argument)[参数](https://cmake.org/cmake/help/latest/manual/cmake-language.7.html#unquoted-argument) 或紧跟带[引号的参数](https://cmake.org/cmake/help/latest/manual/cmake-language.7.html#quoted-argument)且不被任何空格分隔的带引号的参数。为了兼容性，CMake 2.8.12 及更高版本接受此类代码但会产生警告。

### [命令参数](https://cmake.org/cmake/help/latest/manual/cmake-language.7.html#id18)

[命令调用](https://cmake.org/cmake/help/latest/manual/cmake-language.7.html#command-invocations)中有三种类型的参数：

```
论据::=   bracket_argument| quoted_argument|unquoted_argument
```



#### [括号参数](https://cmake.org/cmake/help/latest/manual/cmake-language.7.html#id19)

[受Lua](http://www.lua.org/)长括号语法启发的括号*参数*将内容包含在相同长度的开始和结束“括号”之间：

```
括号参数::=  bracket_open bracket_content bracket_close
括号打开    ::= '[' '='* '['
括号内容::= <任何不包含a的bracket_close文本bracket_open与>

                       相同数量的“=”括号关闭   ::= ']' '='* ']'
```

写一个左括号，`[`后跟零个或多个`=`，然后是`[`。相应的右括号`]`后面是相同数量的，`=`然后是`]`。括号不嵌套。可以始终为左括号和右括号选择唯一的长度，以包含其他长度的右括号。

括号参数内容由左括号和右括号之间的所有文本组成，除了紧跟在左括号之后的一个换行符（如果有的话）将被忽略。不执行包含的内容的评估，例如[转义序列](https://cmake.org/cmake/help/latest/manual/cmake-language.7.html#escape-sequences)或[变量引用](https://cmake.org/cmake/help/latest/manual/cmake-language.7.html#variable-references)。括号参数总是作为一个参数提供给命令调用。

例如：

```
message([=[
This is the first line in a bracket argument with bracket length 1.
No \-escape sequences or ${variable} references are evaluated.
This is always one argument even though it contains a ; character.
The text does not end on a closing bracket of length 0 like ]].
It does end in a closing bracket of length 1.
]=])
```

笔记

 

3.0 之前的 CMake 版本不支持括号参数。他们将左括号解释为 [Unquoted Argument](https://cmake.org/cmake/help/latest/manual/cmake-language.7.html#unquoted-argument)的开始。



#### [引用参数](https://cmake.org/cmake/help/latest/manual/cmake-language.7.html#id20)

带引号的*参数*包含在开始和结束双引号字符之间的内容：

```
引用参数    ::= '"' quoted_element* '"'
引用元素     ::= <任何字符，除了'\'或'"'> |
                          escape_sequence|
                         quoted_continuation
引用_延续::= '\'newline
```

引用的参数内容由开始和结束引号之间的所有文本组成。[转义序列](https://cmake.org/cmake/help/latest/manual/cmake-language.7.html#escape-sequences)和[变量引用](https://cmake.org/cmake/help/latest/manual/cmake-language.7.html#variable-references)都 被评估。一个带引号的参数总是作为一个参数提供给命令调用。

例如：

```
message("This is a quoted argument containing multiple lines.
This is always one argument even though it contains a ; character.
Both \\-escape sequences and ${variable} references are evaluated.
The text does not end on an escaped double-quote like \".
It does end in an unescaped double quote.
")
```

任何以奇数个反斜杠结尾的最后`\`一行都被视为续行，并与紧随其后的换行符一起被忽略。例如：

```
message("\
This is the first line of a quoted argument. \
In fact it is the only line but since it is long \
the source code uses line continuation.\
")
```

笔记

 

3.0 之前的 CMake 版本不支持`\`. 它们在包含以奇数个`\`字符结尾的行的引用参数中报告错误。



#### [未引用的参数](https://cmake.org/cmake/help/latest/manual/cmake-language.7.html#id21)

未*引用的参数*不包含在任何引用语法中。它不能包含任何空格、, `(`, `)`, `#`,`"`或`\` 除非被反斜杠转义：

```
unquoted_argument ::=   unquoted_element+ |unquoted_legacy
unquoted_element ::= <除空格或 '()#"\' 之一以外的任何字符> |
                       escape_sequence
unquoted_legacy   ::= <见正文中的注释>
```

不带引号的参数内容由允许或转义字符的连续块中的所有文本组成。[转义序列](https://cmake.org/cmake/help/latest/manual/cmake-language.7.html#escape-sequences)和 [变量引用](https://cmake.org/cmake/help/latest/manual/cmake-language.7.html#variable-references)都被评估。结果值的划分方式与[列表](https://cmake.org/cmake/help/latest/manual/cmake-language.7.html#lists)划分为元素的方式相同。每个非空元素都作为参数提供给命令调用。因此，可以将不带引号的参数作为零个或多个参数提供给命令调用。

例如：

```
foreach(arg
    NoSpace
    Escaped\ Space
    This;Divides;Into;Five;Arguments
    Escaped\;Semicolon
    )
  message("${arg}")
endforeach()
```

笔记

 

为了支持旧版 CMake 代码，未加引号的参数还可能包含双引号字符串（`"..."`，可能包含水平空格）和 make 样式的变量引用（`$(MAKEVAR)`）。

未转义的双引号必须平衡，不能出现在未引用参数的开头，并被视为内容的一部分。例如，未引用的参数、 和均按字面意思解释。它们可以分别写为带引号的参数、 和。`-Da="b c"``-Da=$(v)``a" "b"c"d``"-Da=\"b c\""``"-Da=$(v)"``"a\" \"b\"c\"d"`

Make-style 引用被视为内容的一部分，不会进行变量扩展。它们被视为单个参数的一部分（而不是单独`$`的 、`(`、 `MAKEVAR`和`)`参数）。

上面的“unquoted_legacy”产生式代表了这样的论点。我们不建议在新代码中使用旧的不带引号的参数。而是使用带[引号的参数](https://cmake.org/cmake/help/latest/manual/cmake-language.7.html#quoted-argument)或[括号参数](https://cmake.org/cmake/help/latest/manual/cmake-language.7.html#bracket-argument)来表示内容。



### [转义序列](https://cmake.org/cmake/help/latest/manual/cmake-language.7.html#id22)

*转义序列*是 a`\`后跟一个字符：

```
转义序列::=   escape_identity| escape_encoded|escape_semicolon
escape_identity ::= '\' <匹配'[^A-Za-z0-9;]'>
转义编码  ::= '\t' | '\r' | '\n'
转义分号::= '\;'
```

A`\`后跟非字母数字字符只是对文字字符进行编码，而不将其解释为语法。A `\t`、`\r`或`\n` 分别编码制表符、回车符或换行符。[任何变量引用](https://cmake.org/cmake/help/latest/manual/cmake-language.7.html#variable-references)`\;` 之外的A都会对 自身进行编码，但可以在未 引用的[参数](https://cmake.org/cmake/help/latest/manual/cmake-language.7.html#unquoted-argument)中使用来对 内部[变量引用](https://cmake.org/cmake/help/latest/manual/cmake-language.7.html#variable-references)对文字字符进行编码 。（另见政策`;``\;``;`[`CMP0053`](https://cmake.org/cmake/help/latest/policy/CMP0053.html#policy:CMP0053)出于历史考虑的文档。）



### [变量引用](https://cmake.org/cmake/help/latest/manual/cmake-language.7.html#id23)

*变量引用*具有以下形式，并在[Quoted Argument](https://cmake.org/cmake/help/latest/manual/cmake-language.7.html#quoted-argument)或[Unquoted Argument](https://cmake.org/cmake/help/latest/manual/cmake-language.7.html#unquoted-argument)`${<variable>}`内进行评估。变量引用被指定变量或缓存条目的值替换，或者如果两者都未设置，则由空字符串替换。变量引用可以嵌套并从内向外求值，例如.`${outer_${inner_variable}_variable}`

文字变量引用可能由字母数字字符、characters`/_.+-`和[Escape Sequences](https://cmake.org/cmake/help/latest/manual/cmake-language.7.html#escape-sequences)组成。嵌套引用可用于评估任何名称的变量。另见政策 [`CMP0053`](https://cmake.org/cmake/help/latest/policy/CMP0053.html#policy:CMP0053)`$`出于历史考虑以及技术上允许但不鼓励这样做的原因的文档。

[变量](https://cmake.org/cmake/help/latest/manual/cmake-language.7.html#variables)部分记录了变量名称的范围以及如何设置它们的值。

*环境变量引用*的形式为`$ENV{<variable>}`. 有关详细信息，请参阅[环境变量](https://cmake.org/cmake/help/latest/manual/cmake-language.7.html#environment-variables)部分。

*缓存变量引用*的形式`$CACHE{<variable>}`为 ，并被指定缓存条目的值替换，而不检查同名的普通变量。如果缓存条目不存在，则将其替换为空字符串。看[`CACHE`](https://cmake.org/cmake/help/latest/variable/CACHE.html#variable:CACHE)了解更多信息。

这[`if()`](https://cmake.org/cmake/help/latest/command/if.html#command:if)command 有一个特殊的条件语法，它允许以简写形式`<variable>` 而不是`${<variable>}`. 但是，环境变量总是需要被引用为`$ENV{<variable>}`.

### [Comments](https://cmake.org/cmake/help/latest/manual/cmake-language.7.html#id24)

注释以`#`不在 [括号参数](https://cmake.org/cmake/help/latest/manual/cmake-language.7.html#bracket-argument)、[引用参数中或作为未引用](https://cmake.org/cmake/help/latest/manual/cmake-language.7.html#quoted-argument)[参数](https://cmake.org/cmake/help/latest/manual/cmake-language.7.html#unquoted-argument)`\` 的一部分转义的字符开头。有两种类型的注释：[括号注释](https://cmake.org/cmake/help/latest/manual/cmake-language.7.html#bracket-comment)和[行注释](https://cmake.org/cmake/help/latest/manual/cmake-language.7.html#line-comment)。



#### [括号注释](https://cmake.org/cmake/help/latest/manual/cmake-language.7.html#id25)

`#`紧随其后的 a[`bracket_open`](https://cmake.org/cmake/help/latest/manual/cmake-language.7.html#grammar-token-bracket_open)形成一个 括号*注释*，由整个括号外壳组成：

```
括号评论::= '#'bracket_argument
```

例如：

```
#[[This is a bracket comment.
It runs until the close bracket.]]
message("First Argument\n" #[[Bracket Comment]] "Second Argument")
```

笔记

 

3.0 之前的 CMake 版本不支持括号注释。他们将开头解释`#`为[Line Comment](https://cmake.org/cmake/help/latest/manual/cmake-language.7.html#line-comment)的开始。



#### [行注释](https://cmake.org/cmake/help/latest/manual/cmake-language.7.html#id26)

A`#`后不紧跟 a[`bracket_open`](https://cmake.org/cmake/help/latest/manual/cmake-language.7.html#grammar-token-bracket_open)形成一个 *行注释*，一直运行到行尾：

```
line_comment ::= '#' <任何不以 a 开头bracket_open
                       且不包含 a 的文本newline>
```

例如：

```
# This is a line comment.
message("First Argument\n" # This is a line comment :)
        "Second Argument") # This is a line comment.
```

## [控制结构](https://cmake.org/cmake/help/latest/manual/cmake-language.7.html#id27)

### [条件块](https://cmake.org/cmake/help/latest/manual/cmake-language.7.html#id28)

这[`if()`](https://cmake.org/cmake/help/latest/command/if.html#command:if)/[`elseif()`](https://cmake.org/cmake/help/latest/command/elseif.html#command:elseif)/[`else()`](https://cmake.org/cmake/help/latest/command/else.html#command:else)/[`endif()`](https://cmake.org/cmake/help/latest/command/endif.html#command:endif) 命令分隔要有条件地执行的代码块。

### [Loops](https://cmake.org/cmake/help/latest/manual/cmake-language.7.html#id29)

这[`foreach()`](https://cmake.org/cmake/help/latest/command/foreach.html#command:foreach)/[`endforeach()`](https://cmake.org/cmake/help/latest/command/endforeach.html#command:endforeach)和 [`while()`](https://cmake.org/cmake/help/latest/command/while.html#command:while)/[`endwhile()`](https://cmake.org/cmake/help/latest/command/endwhile.html#command:endwhile)命令分隔要在循环中执行的代码块。在这样的块内 [`break()`](https://cmake.org/cmake/help/latest/command/break.html#command:break)命令可用于提前终止循环，而[`continue()`](https://cmake.org/cmake/help/latest/command/continue.html#command:continue)命令可用于立即开始下一次迭代。

### [命令定义](https://cmake.org/cmake/help/latest/manual/cmake-language.7.html#id30)

这[`macro()`](https://cmake.org/cmake/help/latest/command/macro.html#command:macro)/[`endmacro()`](https://cmake.org/cmake/help/latest/command/endmacro.html#command:endmacro)， 和 [`function()`](https://cmake.org/cmake/help/latest/command/function.html#command:function)/[`endfunction()`](https://cmake.org/cmake/help/latest/command/endfunction.html#command:endfunction)命令分隔要记录的代码块，以供以后作为命令调用。



## [Variables](https://cmake.org/cmake/help/latest/manual/cmake-language.7.html#id31)

变量是 CMake 语言中的基本存储单元。它们的值始终是字符串类型，尽管某些命令可能会将字符串解释为其他类型的值。这[`set()`](https://cmake.org/cmake/help/latest/command/set.html#command:set)和[`unset()`](https://cmake.org/cmake/help/latest/command/unset.html#command:unset)命令显式设置或取消设置变量，但其他命令也具有修改变量的语义。变量名称区分大小写，几乎可以包含任何文本，但我们建议坚持使用仅由字母数字字符加`_`和组成的名称`-`。

变量具有动态范围。每个变量 "set" 或 "unset" 在当前范围内创建一个绑定：

- 功能范围

  [由](https://cmake.org/cmake/help/latest/manual/cmake-language.7.html#command-definitions)_[`function()`](https://cmake.org/cmake/help/latest/command/function.html#command:function)command 创建命令，当被调用时，在新的变量绑定范围内处理记录的命令。变量“set”或“unset”绑定在此范围内，对当前函数和其中的任何嵌套调用可见，但在函数返回后不可见。

- 目录范围

  源树中的每个[目录](https://cmake.org/cmake/help/latest/manual/cmake-language.7.html#directories)都有自己的变量绑定。在处理`CMakeLists.txt`目录的文件之前，CMake 会复制当前在父目录中定义的所有变量绑定（如果有），以初始化新的目录范围。CMake [Scripts](https://cmake.org/cmake/help/latest/manual/cmake-language.7.html#scripts)在使用 处理时，将变量绑定在一个“目录”范围内。`cmake -P`不在函数调用内的变量“set”或“unset”绑定到当前目录范围。

- 持久缓存

  CMake 存储一组单独的“缓存”变量或“缓存条目”，其值在项目构建树中的多次运行中保持不变。`CACHE`缓存条目有一个独立的绑定 范围，仅由显式请求修改，例如通过[`set()`](https://cmake.org/cmake/help/latest/command/set.html#command:set)和[`unset()`](https://cmake.org/cmake/help/latest/command/unset.html#command:unset)命令。

在评估[变量引用](https://cmake.org/cmake/help/latest/manual/cmake-language.7.html#variable-references)时，CMake 首先在函数调用堆栈（如果有）中搜索绑定，然后返回到当前目录范围内的绑定（如果有）。如果找到“set”绑定，则使用其值。如果找到“未设置”绑定，或者没有找到绑定，CMake 然后搜索缓存条目。如果找到缓存条目，则使用其值。否则，变量引用的计算结果为空字符串。该`$CACHE{VAR}`语法可用于进行直接缓存条目查找。

这[`cmake-variables(7)`](https://cmake.org/cmake/help/latest/manual/cmake-variables.7.html#manual:cmake-variables(7))手册记录了 CMake 提供的许多变量，或者在项目代码设置时对 CMake 有意义。

笔记

 

CMake 保留以下标识符：

- `CMAKE_`以（大写、小写或混合大小写）开头，或
- `_CMAKE_`以（大写、小写或混合大小写）开头，或
- `_`以任何名称开头[`CMake Command`](https://cmake.org/cmake/help/latest/manual/cmake-commands.7.html#manual:cmake-commands(7)).



## [环境变量](https://cmake.org/cmake/help/latest/manual/cmake-language.7.html#id32)

环境变量和普通[变量](https://cmake.org/cmake/help/latest/manual/cmake-language.7.html#variables)一样，有以下区别：

- 范围

  环境变量在 CMake 过程中具有全局范围。它们永远不会被缓存。

- 参考

  [变量引用](https://cmake.org/cmake/help/latest/manual/cmake-language.7.html#variable-references)具有形式`$ENV{<variable>}`，使用 [`ENV`](https://cmake.org/cmake/help/latest/variable/ENV.html#variable:ENV)操作员。

- 初始化

  CMake 环境变量的初始值是调用进程的初始值。可以使用[`set()`](https://cmake.org/cmake/help/latest/command/set.html#command:set)和[`unset()`](https://cmake.org/cmake/help/latest/command/unset.html#command:unset) 命令。这些命令只影响正在运行的 CMake 进程，而不影响整个系统环境。更改的值不会写回调用进程，后续构建或测试进程也看不到它们。请参阅[cmake -E env](https://cmake.org/cmake/help/latest/manual/cmake.1.html#run-a-command-line-tool)命令行工具以在修改后的环境中运行命令。

- 检查

  请参阅[cmake -E environment](https://cmake.org/cmake/help/latest/manual/cmake.1.html#run-a-command-line-tool)命令行工具以显示所有当前环境变量。

这[`cmake-env-variables(7)`](https://cmake.org/cmake/help/latest/manual/cmake-env-variables.7.html#manual:cmake-env-variables(7))手册记录对 CMake 具有特殊意义的环境变量。



## [Lists](https://cmake.org/cmake/help/latest/manual/cmake-language.7.html#id33)

尽管 CMake 中的所有值都存储为字符串，但在某些上下文中，例如在评估[Unquoted Argument](https://cmake.org/cmake/help/latest/manual/cmake-language.7.html#unquoted-argument)期间，字符串可能会被视为列表。`;`在这种情况下，字符串通过拆分不跟在不等数量的`[`and`]`字符之后且不紧跟在 a 之前的字符来划分为列表元素`\`。该序列`\;`不除值，而是`;`在结果元素中被替换。

通过连接由 . 分隔的元素，将元素列表表示为字符串`;`。例如，[`set()`](https://cmake.org/cmake/help/latest/command/set.html#command:set) 命令将多个值作为列表存储到目标变量中：

```
set(srcs a.c b.c c.c) # sets "srcs" to "a.c;b.c;c.c"
```

列表适用于简单的用例，例如源文件列表，不应用于复杂的数据处理任务。大多数构造列表的命令不会转义`;`列表元素中的字符，从而使嵌套列表变平：

```
set(x a "b;c") # sets "x" to "a;b;c", not "a;b\;c"
```

通常，列表不支持包含`;`字符的元素。为避免出现问题，请考虑以下建议：

- 许多 CMake 命令、变量和属性的接口接受分号分隔的列表。避免将带有包含分号的元素的列表传递给这些接口，除非它们记录了直接支持或某种方式来转义或编码分号。

- 构造列表时，请用其他未使用的占位符替换`;`in 元素 when。然后在处理列表元素时替换`;`占位符。例如，以下代码用于`|`代替`;`字符：

  ```
  set(mylist a "b|c")
  foreach(entry IN LISTS mylist)
    string(REPLACE "|" ";" entry "${entry}")
    # use "${entry}" normally
  endforeach()
  ```

  这[`ExternalProject`](https://cmake.org/cmake/help/latest/module/ExternalProject.html#module:ExternalProject)模块的`LIST_SEPARATOR`选项是使用这种方法构建的接口的一个示例。

- 在列表中[`generator expressions`](https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html#manual:cmake-generator-expressions(7))， 使用[`$`](https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html#genex:SEMICOLON)生成器表达式。

- 在命令调用中，尽可能使用[带引号的参数语法。](https://cmake.org/cmake/help/latest/manual/cmake-language.7.html#quoted-argument)被调用的命令将接收保留分号的参数内容。未[引用的参数](https://cmake.org/cmake/help/latest/manual/cmake-language.7.html#unquoted-argument)将用分号分隔。

- 在[`function()`](https://cmake.org/cmake/help/latest/command/function.html#command:function)实现，避免`ARGV`和`ARGN`，它们不区分值中的分号与那些分隔值。相反，更喜欢使用命名位置参数和`ARGC`and `ARGV#`变量。使用时[`cmake_parse_arguments()`](https://cmake.org/cmake/help/latest/command/cmake_parse_arguments.html#command:cmake_parse_arguments)解析参数，更喜欢它的`PARSE_ARGV`签名，它使用`ARGV#`变量。

  请注意，此方法不适用于[`macro()`](https://cmake.org/cmake/help/latest/command/macro.html#command:macro)实现，因为它们使用占位符引用参数，而不是实际变量。