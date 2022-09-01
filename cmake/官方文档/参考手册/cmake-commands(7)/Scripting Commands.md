# [脚本命令](https://cmake.org/cmake/help/latest/manual/cmake-commands.7.html#id3)

这些命令始终可用。

## [break](https://cmake.org/cmake/help/latest/command/break.html)

从封闭的 foreach 或 while 循环中中断。

```
break()
```

从封闭中断[`foreach()`](https://cmake.org/cmake/help/latest/command/foreach.html#command:foreach)或者[`while()`](https://cmake.org/cmake/help/latest/command/while.html#command:while)环形。

另见[`continue()`](https://cmake.org/cmake/help/latest/command/continue.html#command:continue)命令。

## [cmake_host_system_information](https://cmake.org/cmake/help/latest/command/cmake_host_system_information.html)

查询各种主机系统信息。

### Synopsis

```
查询主机系统特定信息
  cmake_host_system_information(RESULT <variable> QUERY <key> ...)

查询 Windows 注册表
  cmake_host_system_information(RESULT <variable> QUERY WINDOWS_REGISTRY <key> ...)
```

### 查询主机系统特定信息

```
cmake_host_system_information(RESULT <variable> QUERY <key> ...)
```

查询运行cmake的宿主系统的系统信息。`<key>`可以提供一个或多个来选择要查询的信息。查询值列表存储在`<variable>`.

`<key>`可以是以下值之一：

- `NUMBER_OF_LOGICAL_CORES`

  逻辑核心数

- `NUMBER_OF_PHYSICAL_CORES`

  物理核心数

- `HOSTNAME`

  主机名

- `FQDN`

  完全限定域名

- `TOTAL_VIRTUAL_MEMORY`

  MiB [1中的总虚拟内存](https://cmake.org/cmake/help/latest/command/cmake_host_system_information.html#mebibytes)

- `AVAILABLE_VIRTUAL_MEMORY`

  MiB [1中的可用虚拟内存](https://cmake.org/cmake/help/latest/command/cmake_host_system_information.html#mebibytes)

- `TOTAL_PHYSICAL_MEMORY`

  [MiB 1](https://cmake.org/cmake/help/latest/command/cmake_host_system_information.html#mebibytes)中的总物理内存

- `AVAILABLE_PHYSICAL_MEMORY`

  [MiB 1](https://cmake.org/cmake/help/latest/command/cmake_host_system_information.html#mebibytes)中的可用物理内存

- `IS_64BIT`

  *3.10 版中的新功能。*如果处理器是 64 位，则为一个

- `HAS_FPU`

  *3.10 版中的新功能。*一个如果处理器有浮点单元

- `HAS_MMX`

  *3.10 版中的新功能。*一个如果处理器支持 MMX 指令

- `HAS_MMX_PLUS`

  *3.10 版中的新功能。*如果处理器支持分机，则为一个。MMX 指令

- `HAS_SSE`

  *3.10 版中的新功能。*一个如果处理器支持 SSE 指令

- `HAS_SSE2`

  *3.10 版中的新功能。*一个如果处理器支持 SSE2 指令

- `HAS_SSE_FP`

  *3.10 版中的新功能。*一个如果处理器支持 SSE FP 指令

- `HAS_SSE_MMX`

  *3.10 版中的新功能。*一个如果处理器支持 SSE MMX 指令

- `HAS_AMD_3DNOW`

  *3.10 版中的新功能。*一个如果处理器支持 3DNow 指令

- `HAS_AMD_3DNOW_PLUS`

  *3.10 版中的新功能。*一个如果处理器支持 3DNow+ 指令

- `HAS_IA64`

  *3.10 版中的新功能。*一个 if IA64 处理器模拟 x86

- `HAS_SERIAL_NUMBER`

  *3.10 版中的新功能。*如果处理器有序列号，则为一个

- `PROCESSOR_SERIAL_NUMBER`

  *3.10 版中的新功能。*处理器序列号

- `PROCESSOR_NAME`

  *3.10 版中的新功能。*人类可读的处理器名称

- `PROCESSOR_DESCRIPTION`

  *3.10 版中的新功能。*人类可读的完整处理器描述

- `OS_NAME`

  *3.10 版中的新功能。*看[`CMAKE_HOST_SYSTEM_NAME`](https://cmake.org/cmake/help/latest/variable/CMAKE_HOST_SYSTEM_NAME.html#variable:CMAKE_HOST_SYSTEM_NAME)

- `OS_RELEASE`

  *3.10 版中的新功能。*操作系统子类型，例如在 Windows 上`Professional`

- `OS_VERSION`

  *3.10 版中的新功能。*操作系统构建 ID

- `OS_PLATFORM`

  *3.10 版中的新功能。*看[`CMAKE_HOST_SYSTEM_PROCESSOR`](https://cmake.org/cmake/help/latest/variable/CMAKE_HOST_SYSTEM_PROCESSOR.html#variable:CMAKE_HOST_SYSTEM_PROCESSOR)

- `DISTRIB_INFO`

  *版本 3.22 中的新功能。*读取`/etc/os-release`文件并将给定定义`<variable>` 到读取变量列表中

- `DISTRIB_<name>`

  *版本 3.22 中的新功能。*获取文件中存在的`<name>`变量（参见[man 5 os-release](https://www.freedesktop.org/software/systemd/man/os-release.html)） `/etc/os-release`例子：`cmake_host_system_information(RESULT PRETTY_NAME QUERY DISTRIB_PRETTY_NAME) message(STATUS "${PRETTY_NAME}") cmake_host_system_information(RESULT DISTRO QUERY DISTRIB_INFO) foreach(VAR IN LISTS DISTRO)  message(STATUS "${VAR}=`${${VAR}}`") endforeach() `输出：`-- Ubuntu 20.04.2 LTS -- DISTRO_BUG_REPORT_URL=`https://bugs.launchpad.net/ubuntu/` -- DISTRO_HOME_URL=`https://www.ubuntu.com/` -- DISTRO_ID=`ubuntu` -- DISTRO_ID_LIKE=`debian` -- DISTRO_NAME=`Ubuntu` -- DISTRO_PRETTY_NAME=`Ubuntu 20.04.2 LTS` -- DISTRO_PRIVACY_POLICY_URL=`https://www.ubuntu.com/legal/terms-and-policies/privacy-policy` -- DISTRO_SUPPORT_URL=`https://help.ubuntu.com/` -- DISTRO_UBUNTU_CODENAME=`focal` -- DISTRO_VERSION=`20.04.2 LTS (Focal Fossa)` -- DISTRO_VERSION_CODENAME=`focal` -- DISTRO_VERSION_ID=`20.04` `

如果`/etc/os-release`找不到文件，该命令会尝试通过后备脚本收集操作系统标识。回退脚本可以使用[各种特定于发行版的文件](http://linuxmafia.com/faq/Admin/release-files.html)来收集操作系统标识数据并将其映射到[man 5 os-release](https://www.freedesktop.org/software/systemd/man/os-release.html)变量中。

#### 回退接口变量

- **CMAKE_GET_OS_RELEASE_FALLBACK_SCRIPTS**

  除了 CMake 附带的脚本之外，用户还可以将其脚本的完整路径附加到此列表中。脚本文件名具有以下格式：`NNN-<name>.cmake`，其中`NNN`三位数字用于按特定顺序应用收集的脚本。

- **CMAKE_GET_OS_RELEASE_FALLBACK_RESULT_<varname>**

  用户提供的备用脚本收集的变量应该使用此命名约定分配给 CMake 变量。例如，`ID`手册中的变量变为 `CMAKE_GET_OS_RELEASE_FALLBACK_RESULT_ID`.

- **CMAKE_GET_OS_RELEASE_FALLBACK_RESULT**

  后备脚本应该 `CMAKE_GET_OS_RELEASE_FALLBACK_RESULT_<varname>`在这个列表中存储所有分配变量的名称。

例子：

```
# Try to detect some old distribution
# See also
# - http://linuxmafia.com/faq/Admin/release-files.html
#
if(NOT EXISTS "${CMAKE_SYSROOT}/etc/foobar-release")
  return()
endif()
# Get the first string only
file(
    STRINGS "${CMAKE_SYSROOT}/etc/foobar-release" CMAKE_GET_OS_RELEASE_FALLBACK_CONTENT
    LIMIT_COUNT 1
  )
#
# Example:
#
#   Foobar distribution release 1.2.3 (server)
#
if(CMAKE_GET_OS_RELEASE_FALLBACK_CONTENT MATCHES "Foobar distribution release ([0-9\.]+) .*")
  set(CMAKE_GET_OS_RELEASE_FALLBACK_RESULT_NAME Foobar)
  set(CMAKE_GET_OS_RELEASE_FALLBACK_RESULT_PRETTY_NAME "${CMAKE_GET_OS_RELEASE_FALLBACK_CONTENT}")
  set(CMAKE_GET_OS_RELEASE_FALLBACK_RESULT_ID foobar)
  set(CMAKE_GET_OS_RELEASE_FALLBACK_RESULT_VERSION ${CMAKE_MATCH_1})
  set(CMAKE_GET_OS_RELEASE_FALLBACK_RESULT_VERSION_ID ${CMAKE_MATCH_1})
  list(
      APPEND CMAKE_GET_OS_RELEASE_FALLBACK_RESULT
      CMAKE_GET_OS_RELEASE_FALLBACK_RESULT_NAME
      CMAKE_GET_OS_RELEASE_FALLBACK_RESULT_PRETTY_NAME
      CMAKE_GET_OS_RELEASE_FALLBACK_RESULT_ID
      CMAKE_GET_OS_RELEASE_FALLBACK_RESULT_VERSION
      CMAKE_GET_OS_RELEASE_FALLBACK_RESULT_VERSION_ID
    )
endif()
unset(CMAKE_GET_OS_RELEASE_FALLBACK_CONTENT)
```

脚注

- 1([1](https://cmake.org/cmake/help/latest/command/cmake_host_system_information.html#id1),[2](https://cmake.org/cmake/help/latest/command/cmake_host_system_information.html#id2),[3](https://cmake.org/cmake/help/latest/command/cmake_host_system_information.html#id3),[4](https://cmake.org/cmake/help/latest/command/cmake_host_system_information.html#id4))

  1 MiB（兆字节）等于 1024x1024 字节。



### 查询 Windows 注册表

*版本 3.24 中的新功能。*

```
cmake_host_system_information(RESULT <variable>
                              QUERY WINDOWS_REGISTRY <key> [VALUE_NAMES|SUBKEYS|VALUE <name>]
                              [VIEW (64|32|64_32|32_64|HOST|TARGET|BOTH)]
                              [SEPARATOR <separator>]
                              [ERROR_VARIABLE <result>])
```

对本地计算机注册表子项执行查询操作。返回位于注册表中指定子键下的子键或值名称列表或指定值名称的数据。查询实体的结果存储在`<variable>`.

笔记

 

查询除 之外的任何其他平台的注册表`Windows`将 `CYGWIN`始终返回一个空字符串并在使用 sub-option 指定的变量中设置错误消息`ERROR_VARIABLE`。

`<key>`指定本地计算机上子项的完整路径。`<key>`必须包含有效的根密钥。 本地计算机的有效根密钥是：

- `HKLM`或者`HKEY_LOCAL_MACHINE`
- `HKCU`或者`HKEY_CURRENT_USER`
- `HKCR`或者`HKEY_CLASSES_ROOT`
- `HKU`或者`HKEY_USERS`
- `HKCC`或者`HKEY_CURRENT_CONFIG`

并且，可选地，指定根键下的子键的路径。路径分隔符可以是斜杠或反斜杠。`<key>`不区分大小写。例如：

```
cmake_host_system_information(RESULT result QUERY WINDOWS_REGISTRY "HKLM")
cmake_host_system_information(RESULT result QUERY WINDOWS_REGISTRY "HKLM/SOFTWARE/Kitware")
cmake_host_system_information(RESULT result QUERY WINDOWS_REGISTRY "HKCU\\SOFTWARE\\Kitware")
```

- `VALUE_NAMES`

  请求下定义的值名称列表`<key>`。如果定义了默认值，它将使用特殊名称进行标识`(default)`。

- `SUBKEYS`

  请求下定义的子键列表`<key>`。

- `VALUE <name>`

  请求存储在名为 的值中的数据`<name>`。如果`VALUE`未指定或参数为特殊名称`(default)`，则返回默认值的内容（如果有）。`# query default value for HKLM/SOFTWARE/Kitware key cmake_host_system_information(RESULT result                              QUERY WINDOWS_REGISTRY "HKLM/SOFTWARE/Kitware") # query default value for HKLM/SOFTWARE/Kitware key using special value name cmake_host_system_information(RESULT result                              QUERY WINDOWS_REGISTRY "HKLM/SOFTWARE/Kitware"                              VALUE "(default)") `支持的类型有：`REG_SZ`.`REG_EXPAND_SZ`. 返回的数据被展开。`REG_MULTI_SZ`. 返回的表示为 CMake 列表。另见 `SEPARATOR`子选项。`REG_DWORD`.`REG_QWORD`.对于所有其他类型，将返回一个空字符串。

- `VIEW`

  指定必须查询哪些注册表视图。如果未指定，`BOTH` 则使用视图。`64`查询 64 位注册表。On ，总是返回一个空字符串。`32bit Windows``32`查询 32 位注册表。`64_32`对于`VALUE`子选项或默认值，使用 view 查询注册表 `64`，如果请求失败，使用 view 查询注册表`32`。对于`VALUE_NAMES`和`SUBKEYS`子选项，查询两个视图（`64` 和`32`）并合并结果（已排序并删除重复项）。`32_64`对于`VALUE`子选项或默认值，使用 view 查询注册表 `32`，如果请求失败，使用 view 查询注册表`64`。对于`VALUE_NAMES`和`SUBKEYS`子选项，查询两个视图（`32` 和`64`）并合并结果（已排序并删除重复项）。`HOST`查询与主机架构匹配的注册表：`64`on和on 。`64bit Windows``32``32bit Windows``TARGET`查询与指定架构匹配的注册表 [`CMAKE_SIZEOF_VOID_P`](https://cmake.org/cmake/help/latest/variable/CMAKE_SIZEOF_VOID_P.html#variable:CMAKE_SIZEOF_VOID_P)多变的。如果未定义，则回退到 `HOST`查看。`BOTH`查询两个视图（`32`和`64`）。顺序取决于以下规则：如果[`CMAKE_SIZEOF_VOID_P`](https://cmake.org/cmake/help/latest/variable/CMAKE_SIZEOF_VOID_P.html#variable:CMAKE_SIZEOF_VOID_P)变量被定义。根据此变量的内容使用以下视图：`8`: `64_32``4`:`32_64`如果[`CMAKE_SIZEOF_VOID_P`](https://cmake.org/cmake/help/latest/variable/CMAKE_SIZEOF_VOID_P.html#variable:CMAKE_SIZEOF_VOID_P)变量未定义，依赖于主机的架构：`64bit`:`64_32``32bit`:`32`

- `SEPARATOR`

  指定`REG_MULTI_SZ`类型的分隔符。如果未指定，`\0`则使用该字符。

- `ERROR_VARIABLE <result>`

  返回查询操作期间引发的任何错误。在成功的情况下，该变量包含一个空字符串。

## [cmake_language](https://cmake.org/cmake/help/latest/command/cmake_language.html)

*3.18 版中的新功能。*

调用 CMake 命令的元操作。

### Synopsis

```
cmake_language( CALL <command> [<arg>...])
cmake_language( EVAL CODE <code>...)
cmake_language( DEFER <options>... CALL <command> [<arg>...])
cmake_language( SET_DEPENDENCY_PROVIDER <command> SUPPORTED_METHODS <methods>...)
```

### Introduction

此命令将调用内置 CMake 命令或通过[`macro()`](https://cmake.org/cmake/help/latest/command/macro.html#command:macro)或者[`function()`](https://cmake.org/cmake/help/latest/command/function.html#command:function)命令。

`cmake_language`不引入新的变量或策略范围。

### 调用命令

```
cmake_language(CALL <command> [<arg>...])
```

`<command>`使用给定的参数（如果有）调用命名。例如，代码：

```
set(message_command "message")
cmake_language(CALL ${message_command} STATUS "Hello World!")
```

相当于

```
message(STATUS "Hello World!")
```

笔记

 

为保证代码的一致性，不允许使用以下命令：

- `if` / `elseif` / `else` / `endif`
- `while` / `endwhile`
- `foreach`/`endforeach`
- `function`/`endfunction`
- `macro`/`endmacro`

### 评估代码

```
cmake_language(EVAL CODE <code>...)
```

评估`<code>...`as CMake 代码。

例如，代码：

```
set(A TRUE)
set(B TRUE)
set(C TRUE)
set(condition "(A AND B) OR C")

cmake_language(EVAL CODE "
  if (${condition})
    message(STATUS TRUE)
  else()
    message(STATUS FALSE)
  endif()"
)
```

相当于

```
set(A TRUE)
set(B TRUE)
set(C TRUE)
set(condition "(A AND B) OR C")

file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/eval.cmake "
  if (${condition})
    message(STATUS TRUE)
  else()
    message(STATUS FALSE)
  endif()"
)

include(${CMAKE_CURRENT_BINARY_DIR}/eval.cmake)
```

### 延迟调用

*3.19 版中的新功能。*

```
cmake_language(DEFER <options>... CALL <command> [<arg>...])
```

使用给定的参数（如果有）安排对命名的调用`<command>`在以后发生。默认情况下，延迟调用就像写在当前目录`CMakeLists.txt`文件的末尾一样执行，除了它们甚至在一个[`return()`](https://cmake.org/cmake/help/latest/command/return.html#command:return)称呼。参数中的变量引用在执行延迟调用时进行评估。

选项包括：

- `DIRECTORY <dir>`

  将调用安排在给定目录的末尾而不是当前目录。`<dir>`可以引用源目录或其对应的二进制目录。相对路径被视为相对于当前源目录。给定的目录必须是 CMake 知道的，可以是顶级目录，也可以是由 CMake 添加的目录[`add_subdirectory()`](https://cmake.org/cmake/help/latest/command/add_subdirectory.html#command:add_subdirectory). 此外，给定目录必须尚未完成处理。这意味着它可以是当前目录或其祖先之一。

- `ID <id>`

  指定延迟呼叫的标识。不能为空`<id>`，也不能以大写字母开头`A-Z`。仅当它是由用于获取 id的早期调用自动生成时，它才`<id>`可以以下划线 () 开头。`_``ID_VAR`

- `ID_VAR <var>`

  指定一个变量，用于存储延迟调用的标识。如果未给出，将生成一个新的标识，并且生成的 id 将以下划线 ( ) 开头。`ID <id>``_`

可以检索当前安排的延迟呼叫列表：

```
cmake_language(DEFER [DIRECTORY <dir>] GET_CALL_IDS <var>)
```

这将存储在`<var>`以[分号分隔](https://cmake.org/cmake/help/latest/manual/cmake-language.7.html#cmake-language-lists)的延迟呼叫 ID 列表中。id 用于调用被推迟到的目录范围（即它们将被执行的位置），它可以与创建它们的范围不同。该`DIRECTORY` 选项可用于指定检索呼叫 ID 的范围。如果未给出该选项，则将返回当前目录范围的调用 ID。

可以从其 id 中检索特定调用的详细信息：

```
cmake_language(DEFER [DIRECTORY <dir>] GET_CALL <id> <var>)
```

这将存储在`<var>`一个[分号分隔的列表](https://cmake.org/cmake/help/latest/manual/cmake-language.7.html#cmake-language-lists)中，其中第一个元素是要调用的命令的名称，其余元素是其未评估的参数（任何包含`;`的字符都按字面意思包含，无法与多个参数区分开来）。如果使用相同的 id 安排了多个调用，则检索第一个调用。`DIRECTORY`如果在指定范围（或当前目录范围，如果没有 给出选项）中没有使用给定 id 安排调用`DIRECTORY`，则这会将空字符串存储在变量中。

延迟调用可能会被他们的 id 取消：

```
cmake_language(DEFER [DIRECTORY <dir>] CANCEL_CALL <id>...)
```

这将取消与指定范围内的任何给定 ID 匹配的所有延迟调用 `DIRECTORY`（如果没有`DIRECTORY`给出选项，则取消当前目录范围）。未知的 id 会被默默地忽略。

#### 延迟调用示例

例如，代码：

```
cmake_language(DEFER CALL message "${deferred_message}")
cmake_language(DEFER ID_VAR id CALL message "Canceled Message")
cmake_language(DEFER CANCEL_CALL ${id})
message("Immediate Message")
set(deferred_message "Deferred Message")
```

印刷：

```
Immediate Message
Deferred Message
```

永远不会打印，因为它的命令被取消了。在调用站点之前不会评估变量引用，因此可以在安排延迟调用之后设置它。`Cancelled Message``deferred_message`

为了在安排延迟调用时立即评估变量引用，请使用`cmake_language(EVAL)`. 但是，请注意，参数将在延迟调用中重新评估，尽管可以通过使用括号参数来避免这种情况。例如：

```
set(deferred_message "Deferred Message 1")
set(re_evaluated [[${deferred_message}]])
cmake_language(EVAL CODE "
  cmake_language(DEFER CALL message [[${deferred_message}]])
  cmake_language(DEFER CALL message \"${re_evaluated}\")
")
message("Immediate Message")
set(deferred_message "Deferred Message 2")
```

还打印：

```
Immediate Message
Deferred Message 1
Deferred Message 2
```

### 依赖提供者

*版本 3.24 中的新功能。*

笔记

 

可以在 [Using Dependencies Guide](https://cmake.org/cmake/help/latest/guide/using-dependencies/index.html#dependency-providers-overview)中找到对此功能的高级介绍。

```
cmake_language(SET_DEPENDENCY_PROVIDER <command>
               SUPPORTED_METHODS <methods>...)
```

当呼叫到[`find_package()`](https://cmake.org/cmake/help/latest/command/find_package.html#command:find_package)或者 [`FetchContent_MakeAvailable()`](https://cmake.org/cmake/help/latest/module/FetchContent.html#command:fetchcontent_makeavailable)，调用可能会被转发给依赖提供者，然后依赖提供者有机会满足请求。如果请求是针对`<methods>`设置提供程序时指定的一个，CMake 会`<command>`使用一组特定于方法的参数调用提供程序。如果提供者不满足请求，或者提供者不支持请求的方法，或者没有设置提供者，则内置[`find_package()`](https://cmake.org/cmake/help/latest/command/find_package.html#command:find_package)或者 [`FetchContent_MakeAvailable()`](https://cmake.org/cmake/help/latest/module/FetchContent.html#command:fetchcontent_makeavailable)implementation 用于以通常的方式满足请求。

设置提供程序时，可以为 指定以下一个或多个值`<methods>` ：

- `FIND_PACKAGE`

  提供者命令接受[`find_package()`](https://cmake.org/cmake/help/latest/command/find_package.html#command:find_package)要求。

- `FETCHCONTENT_MAKEAVAILABLE_SERIAL`

  提供者命令接受[`FetchContent_MakeAvailable()`](https://cmake.org/cmake/help/latest/module/FetchContent.html#command:fetchcontent_makeavailable) 要求。它希望每次将每个依赖项都提供给提供程序命令，而不是一次性提供整个列表。

在任何时间点只能设置一个提供者。如果在`cmake_language(SET_DEPENDENCY_PROVIDER)`调用时已经设置了提供者，则新的提供者将替换先前设置的提供者。调用时指定的`<command>`必须已经存在`cmake_language(SET_DEPENDENCY_PROVIDER)`。`<command>`作为一种特殊情况，为 the和 no 提供一个空字符串`<methods>`将丢弃任何先前设置的提供程序。

依赖提供程序只能在处理由指定的文件之一时设置[`CMAKE_PROJECT_TOP_LEVEL_INCLUDES`](https://cmake.org/cmake/help/latest/variable/CMAKE_PROJECT_TOP_LEVEL_INCLUDES.html#variable:CMAKE_PROJECT_TOP_LEVEL_INCLUDES)多变的。因此，依赖提供者只能设置为第一次调用的一部分 [`project()`](https://cmake.org/cmake/help/latest/command/project.html#command:project). 在该上下文之外调用`cmake_language(SET_DEPENDENCY_PROVIDER)` 将导致错误。

笔记

 

依赖提供者的选择应该始终在用户的控制之下。为方便起见，项目可以选择提供一个文件，用户可以在他们的[`CMAKE_PROJECT_TOP_LEVEL_INCLUDES`](https://cmake.org/cmake/help/latest/variable/CMAKE_PROJECT_TOP_LEVEL_INCLUDES.html#variable:CMAKE_PROJECT_TOP_LEVEL_INCLUDES)变量，但使用这样的文件应该始终是用户的选择。

#### 提供者命令

提供者定义一个单一`<command>`的接受请求。命令的名称应该特定于该提供者，而不是其他提供者也可能使用的过于通用的名称。这使用户能够在他们自己的自定义提供程序中组合不同的提供程序。推荐的形式是 `xxx_provide_dependency()`，其中`xxx`是提供者特定的部分（例如`vcpkg_provide_dependency()`、`conan_provide_dependency()`、 `ourcompany_provide_dependency()`等）。

```
xxx_provide_dependency(<method> [<method-specific-args>...])
```

因为某些方法期望在调用范围内设置某些变量，所以提供程序命令通常应实现为宏而不是函数。这确保它不会引入新的变量范围。

CMake 传递给依赖提供者的参数取决于请求的类型。第一个参数始终是方法，它只会是`<methods>`设置提供程序时指定的方法之一。

- `FIND_PACKAGE`

  将`<method-specific-args>`是一切传递给 [`find_package()`](https://cmake.org/cmake/help/latest/command/find_package.html#command:find_package)调用请求依赖项。因此，第一个`<method-specific-args>`将始终是依赖项的名称。此方法的依赖项名称区分大小写，因为 [`find_package()`](https://cmake.org/cmake/help/latest/command/find_package.html#command:find_package)也区分大小写。如果提供者命令满足请求，它必须设置相同的变量[`find_package()`](https://cmake.org/cmake/help/latest/command/find_package.html#command:find_package)预计将被设置。对于名为 的依赖项 ，如果提供者满足请求`depName`，则必须将其设置为 true。`depName_FOUND`如果提供者在未设置此变量的情况下返回，CMake 将假定请求未完成并回退到内置实现。如果提供者需要调用内置[`find_package()`](https://cmake.org/cmake/help/latest/command/find_package.html#command:find_package) 实现作为其处理的一部分，它可以通过将 `BYPASS_PROVIDER`关键字作为参数之一来实现。

- `FETCHCONTENT_MAKEAVAILABE_SERIAL`

  将`<method-specific-args>`是一切传递给 [`FetchContent_Declare()`](https://cmake.org/cmake/help/latest/module/FetchContent.html#command:fetchcontent_declare)对应于请求的依赖项的调用，但以下情况除外：如果`SOURCE_DIR`或`BINARY_DIR`不是原始声明参数的一部分，它们将被添加它们的默认值。如果[`FETCHCONTENT_TRY_FIND_PACKAGE_MODE`](https://cmake.org/cmake/help/latest/module/FetchContent.html#variable:FETCHCONTENT_TRY_FIND_PACKAGE_MODE)设置为`NEVER`, any`FIND_PACKAGE_ARGS`将被省略。`OVERRIDE_FIND_PACKAGE`关键字总是被省略。第一个`<method-specific-args>`将始终是依赖项的名称。此方法的依赖项名称不区分大小写，因为 [`FetchContent`](https://cmake.org/cmake/help/latest/module/FetchContent.html#module:FetchContent)也对它们不区分大小写。如果提供者满足请求，它应该调用 [`FetchContent_SetPopulated()`](https://cmake.org/cmake/help/latest/module/FetchContent.html#command:fetchcontent_setpopulated)，将依赖项的名称作为第一个参数传递。仅当提供程序使依赖项的源和构建目录以与内置目录完全相同的方式可用时，才应给出该命令 的`SOURCE_DIR`and参数`BINARY_DIR`[`FetchContent_MakeAvailable()`](https://cmake.org/cmake/help/latest/module/FetchContent.html#command:fetchcontent_makeavailable)命令。如果提供者返回而不调用[`FetchContent_SetPopulated()`](https://cmake.org/cmake/help/latest/module/FetchContent.html#command:fetchcontent_setpopulated) 对于命名的依赖项，CMake 将假定请求未完成，并将回退到内置实现。请注意，对于此方法，空参数可能很重要（例如，`GIT_SUBMODULES`关键字后面的空字符串）。因此，如果将这些参数转发给另一个命令，则必须格外小心，以避免这些参数被静默丢弃。如果`FETCHCONTENT_SOURCE_DIR_<uppercaseDepName>`设置了，那么依赖提供者将永远不会看到`<depName>`对该方法的依赖的请求。当用户设置这样一个变量时，他们明确地覆盖了从哪里获取该依赖项，并承担了他们的覆盖版本满足该依赖项的任何要求并与项目中使用它的任何其他内容兼容的责任。取决于价值[`FETCHCONTENT_TRY_FIND_PACKAGE_MODE`](https://cmake.org/cmake/help/latest/module/FetchContent.html#variable:FETCHCONTENT_TRY_FIND_PACKAGE_MODE) 以及是否`OVERRIDE_FIND_PACKAGE`给予了选择权 [`FetchContent_Declare()`](https://cmake.org/cmake/help/latest/module/FetchContent.html#command:fetchcontent_declare)， `FETCHCONTENT_SOURCE_DIR_<uppercaseDepName>`设置也可能会阻止依赖提供者看到调用请求`find_package(depName)` 。

#### 提供者示例

第一个示例仅拦截[`find_package()`](https://cmake.org/cmake/help/latest/command/find_package.html#command:find_package)来电。提供者命令运行一个外部工具，该工具将相关工件复制到提供者特定的目录中，如果该工具知道依赖关系。然后它依赖于内置实现来查找这些工件。 [`FetchContent_MakeAvailable()`](https://cmake.org/cmake/help/latest/module/FetchContent.html#command:fetchcontent_makeavailable)电话不会通过提供者。

mycomp_provider.cmake 

```cmake
# Always ensure we have the policy settings this provider expects
cmake_minimum_required(VERSION 3.24)

set(MYCOMP_PROVIDER_INSTALL_DIR ${CMAKE_BINARY_DIR}/mycomp_packages
  CACHE PATH "The directory this provider installs packages to"
)
# Tell the built-in implementation to look in our area first, unless
# the find_package() call uses NO_..._PATH options to exclude it
list(APPEND CMAKE_MODULE_PATH ${MYCOMP_PROVIDER_INSTALL_DIR}/cmake)
list(APPEND CMAKE_PREFIX_PATH ${MYCOMP_PROVIDER_INSTALL_DIR})

macro(mycomp_provide_dependency method package_name)
  execute_process(
    COMMAND some_tool ${package_name} --installdir ${MYCOMP_PROVIDER_INSTALL_DIR}
    COMMAND_ERROR_IS_FATAL ANY
  )
endmacro()

cmake_language(
  SET_DEPENDENCY_PROVIDER mycomp_provide_dependency
  SUPPORTED_METHODS FIND_PACKAGE
)
```

然后，用户通常会像这样使用上述文件：

```
cmake -DCMAKE_PROJECT_TOP_LEVEL_INCLUDES=/path/to/mycomp_provider.cmake ...
```

下一个示例演示了一个接受这两种方法的提供程序，但只处理一个特定的依赖项。它强制使用提供 Google 测试[`FetchContent`](https://cmake.org/cmake/help/latest/module/FetchContent.html#module:FetchContent)，但让所有其他依赖项由 CMake 的内置实现来完成。它接受几个不同的名称，这展示了一种解决项目的方法，这些项目硬编码一种不寻常或不受欢迎的方式，将这种特定的依赖项添加到构建中。该示例还演示了如何使用[`list()`](https://cmake.org/cmake/help/latest/command/list.html#command:list)命令保留可能被调用覆盖的变量 [`FetchContent_MakeAvailable()`](https://cmake.org/cmake/help/latest/module/FetchContent.html#command:fetchcontent_makeavailable).

mycomp_provider.cmake 

```cmake
cmake_minimum_required(VERSION 3.24)

# Because we declare this very early, it will take precedence over any
# details the project might declare later for the same thing
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        e2239ee6043f73722e7aa812a459f54a28552929 # release-1.11.0
)

# Both FIND_PACKAGE and FETCHCONTENT_MAKEAVAILABLE_SERIAL methods provide
# the package or dependency name as the first method-specific argument.
macro(mycomp_provide_dependency method dep_name)
  if("${dep_name}" MATCHES "^(gtest|googletest)$")
    # Save our current command arguments in case we are called recursively
    list(APPEND mycomp_provider_args ${method} ${dep_name})

    # This will forward to the built-in FetchContent implementation,
    # which detects a recursive call for the same thing and avoids calling
    # the provider again if dep_name is the same as the current call.
    FetchContent_MakeAvailable(googletest)

    # Restore our command arguments
    list(POP_BACK mycomp_provider_args dep_name method)

    # Tell the caller we fulfilled the request
    if("${method}" STREQUAL "FIND_PACKAGE")
      # We need to set this if we got here from a find_package() call
      # since we used a different method to fulfill the request.
      # This example assumes projects only use the gtest targets,
      # not any of the variables the FindGTest module may define.
      set(${dep_name}_FOUND TRUE)
    elseif(NOT "${dep_name}" STREQUAL "googletest")
      # We used the same method, but were given a different name to the
      # one we populated with. Tell the caller about the name it used.
      FetchContent_SetPopulated(${dep_name}
        SOURCE_DIR "${googletest_SOURCE_DIR}"
        BINARY_DIR "${googletest_BINARY_DIR}"
      )
    endif()
  endif()
endmacro()

cmake_language(
  SET_DEPENDENCY_PROVIDER mycomp_provide_dependency
  SUPPORTED_METHODS
    FIND_PACKAGE
    FETCHCONTENT_MAKEAVAILABLE_SERIAL
)
```

最后一个示例演示了如何将参数修改为 [`find_package()`](https://cmake.org/cmake/help/latest/command/find_package.html#command:find_package)称呼。它强制所有此类调用具有 `QUIET`关键字。它使用`BYPASS_PROVIDER`关键字来防止为相同的依赖项递归调用提供程序命令。

mycomp_provider.cmake 

```cmake
cmake_minimum_required(VERSION 3.24)

macro(mycomp_provide_dependency method)
  find_package(${ARGN} BYPASS_PROVIDER QUIET)
endmacro()

cmake_language(
  SET_DEPENDENCY_PROVIDER mycomp_provide_dependency
  SUPPORTED_METHODS FIND_PACKAGE
)
```

## [cmake_minimum_required](https://cmake.org/cmake/help/latest/command/cmake_minimum_required.html)

## [cmake_parse_arguments](https://cmake.org/cmake/help/latest/command/cmake_parse_arguments.html)

## [cmake_path](https://cmake.org/cmake/help/latest/command/cmake_path.html)

## [cmake_policy](https://cmake.org/cmake/help/latest/command/cmake_policy.html)

## [configure_file](https://cmake.org/cmake/help/latest/command/configure_file.html)

## [continue](https://cmake.org/cmake/help/latest/command/continue.html)

## [else](https://cmake.org/cmake/help/latest/command/else.html)

## [elseif](https://cmake.org/cmake/help/latest/command/elseif.html)

## [endforeach](https://cmake.org/cmake/help/latest/command/endforeach.html)

## [endfunction](https://cmake.org/cmake/help/latest/command/endfunction.html)

## [endif](https://cmake.org/cmake/help/latest/command/endif.html)

## [endmacro](https://cmake.org/cmake/help/latest/command/endmacro.html)

## [endwhile](https://cmake.org/cmake/help/latest/command/endwhile.html)

## [execute_process](https://cmake.org/cmake/help/latest/command/execute_process.html)

## [file](https://cmake.org/cmake/help/latest/command/file.html)

## [find_file](https://cmake.org/cmake/help/latest/command/find_file.html)

## [find_library](https://cmake.org/cmake/help/latest/command/find_library.html)

## [find_package](https://cmake.org/cmake/help/latest/command/find_package.html)

## [find_path](https://cmake.org/cmake/help/latest/command/find_path.html)

## [find_program](https://cmake.org/cmake/help/latest/command/find_program.html)

## [foreach](https://cmake.org/cmake/help/latest/command/foreach.html)

## [function](https://cmake.org/cmake/help/latest/command/function.html)

## [get_cmake_property](https://cmake.org/cmake/help/latest/command/get_cmake_property.html)

## [get_directory_property](https://cmake.org/cmake/help/latest/command/get_directory_property.html)

## [get_filename_component](https://cmake.org/cmake/help/latest/command/get_filename_component.html)

## [get_property](https://cmake.org/cmake/help/latest/command/get_property.html)

## [if](https://cmake.org/cmake/help/latest/command/if.html)

## [include](https://cmake.org/cmake/help/latest/command/include.html)

## [include_guard](https://cmake.org/cmake/help/latest/command/include_guard.html)

## [list](https://cmake.org/cmake/help/latest/command/list.html)

## [macro](https://cmake.org/cmake/help/latest/command/macro.html)

## [mark_as_advanced](https://cmake.org/cmake/help/latest/command/mark_as_advanced.html)

## [math](https://cmake.org/cmake/help/latest/command/math.html)

## [message](https://cmake.org/cmake/help/latest/command/message.html)

## [option](https://cmake.org/cmake/help/latest/command/option.html)

## [return](https://cmake.org/cmake/help/latest/command/return.html)

## [separate_arguments](https://cmake.org/cmake/help/latest/command/separate_arguments.html)

## [set](https://cmake.org/cmake/help/latest/command/set.html)

## [set_directory_properties](https://cmake.org/cmake/help/latest/command/set_directory_properties.html)

## [set_property](https://cmake.org/cmake/help/latest/command/set_property.html)

## [site_name](https://cmake.org/cmake/help/latest/command/site_name.html)

## [string](https://cmake.org/cmake/help/latest/command/string.html)

## [unset](https://cmake.org/cmake/help/latest/command/unset.html)

## [variable_watch](https://cmake.org/cmake/help/latest/command/variable_watch.html)

## [while](https://cmake.org/cmake/help/latest/command/while.html)
