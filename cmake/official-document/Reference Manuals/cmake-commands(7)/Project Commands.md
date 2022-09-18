# 配置参数

## [cmake_host_system_information](https://cmake.org/cmake/help/latest/command/cmake_host_system_information.html)

查询各种主机系统信息。

### 简明

```cmake
查询主机系统特定信息
  cmake_host_system_information(RESULT <variable> QUERY <key> ...)

查询 Windows 注册表
  cmake_host_system_information(RESULT <variable> QUERY WINDOWS_REGISTRY <key> ...)
```

### 查询主机系统特定信息

```cmake
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

### 回退接口变量

- **CMAKE_GET_OS_RELEASE_FALLBACK_SCRIPTS**

  除了 CMake 附带的脚本之外，用户还可以将其脚本的完整路径附加到此列表中。脚本文件名具有以下格式：`NNN-<name>.cmake`，其中`NNN`三位数字用于按特定顺序应用收集的脚本。

- **CMAKE_GET_OS_RELEASE_FALLBACK_RESULT_<varname>**

  用户提供的备用脚本收集的变量应该使用此命名约定分配给 CMake 变量。例如，`ID`手册中的变量变为 `CMAKE_GET_OS_RELEASE_FALLBACK_RESULT_ID`.

- **CMAKE_GET_OS_RELEASE_FALLBACK_RESULT**

  后备脚本应该 `CMAKE_GET_OS_RELEASE_FALLBACK_RESULT_<varname>`在这个列表中存储所有分配变量的名称。

例子：

```cmake
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

```cmake
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

```cmake
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

### 简明

```cmake
cmake_language( CALL <command> [<arg>...])
cmake_language( EVAL CODE <code>...)
cmake_language( DEFER <options>... CALL <command> [<arg>...])
cmake_language( SET_DEPENDENCY_PROVIDER <command> SUPPORTED_METHODS <methods>...)
```

### 简介

此命令将调用内置 CMake 命令或通过[`macro()`](https://cmake.org/cmake/help/latest/command/macro.html#command:macro)或者[`function()`](https://cmake.org/cmake/help/latest/command/function.html#command:function)命令。

`cmake_language`不引入新的变量或策略范围。

### 调用命令

```cmake
cmake_language(CALL <command> [<arg>...])
```

`<command>`使用给定的参数（如果有）调用命名。例如，代码：

```cmake
set(message_command "message")
cmake_language(CALL ${message_command} STATUS "Hello World!")
```

相当于

```cmake
message(STATUS "Hello World!")
```

> **笔记** 为保证代码的一致性，不允许使用以下命令：
>
> - `if` / `elseif` / `else` / `endif`
> - `while` / `endwhile`
> - `foreach`/`endforeach`
> - `function`/`endfunction`
> - `macro`/`endmacro`



#### 评估代码

```cmake
cmake_language(EVAL CODE <code>...)
```

评估`<code>...`as CMake 代码。

例如，代码：

```cmake
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

```cmake
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

```cmake
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

```cmake
cmake_language(DEFER [DIRECTORY <dir>] GET_CALL_IDS <var>)
```

这将存储在`<var>`以[分号分隔](https://cmake.org/cmake/help/latest/manual/cmake-language.7.html#cmake-language-lists)的延迟呼叫 ID 列表中。id 用于调用被推迟到的目录范围（即它们将被执行的位置），它可以与创建它们的范围不同。该`DIRECTORY` 选项可用于指定检索呼叫 ID 的范围。如果未给出该选项，则将返回当前目录范围的调用 ID。

可以从其 id 中检索特定调用的详细信息：

```cmake
cmake_language(DEFER [DIRECTORY <dir>] GET_CALL <id> <var>)
```

这将存储在`<var>`一个[分号分隔的列表](https://cmake.org/cmake/help/latest/manual/cmake-language.7.html#cmake-language-lists)中，其中第一个元素是要调用的命令的名称，其余元素是其未评估的参数（任何包含`;`的字符都按字面意思包含，无法与多个参数区分开来）。如果使用相同的 id 安排了多个调用，则检索第一个调用。`DIRECTORY`如果在指定范围（或当前目录范围，如果没有 给出选项）中没有使用给定 id 安排调用`DIRECTORY`，则这会将空字符串存储在变量中。

延迟调用可能会被他们的 id 取消：

```cmake
cmake_language(DEFER [DIRECTORY <dir>] CANCEL_CALL <id>...)
```

这将取消与指定范围内的任何给定 ID 匹配的所有延迟调用 `DIRECTORY`（如果没有`DIRECTORY`给出选项，则取消当前目录范围）。未知的 id 会被默默地忽略。

#### 延迟调用示例

例如，代码：

```cmake
cmake_language(DEFER CALL message "${deferred_message}")
cmake_language(DEFER ID_VAR id CALL message "Canceled Message")
cmake_language(DEFER CANCEL_CALL ${id})
message("Immediate Message")
set(deferred_message "Deferred Message")
```

印刷：

```cmake
Immediate Message
Deferred Message
```

永远不会打印，因为它的命令被取消了。在调用站点之前不会评估变量引用，因此可以在安排延迟调用之后设置它。`Cancelled Message``deferred_message`

为了在安排延迟调用时立即评估变量引用，请使用`cmake_language(EVAL)`. 但是，请注意，参数将在延迟调用中重新评估，尽管可以通过使用括号参数来避免这种情况。例如：

```cmake
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

```cmake
Immediate Message
Deferred Message 1
Deferred Message 2
```



### 依赖提供者

*版本 3.24 中的新功能。*

笔记

 

可以在 [Using Dependencies Guide](https://cmake.org/cmake/help/latest/guide/using-dependencies/index.html#dependency-providers-overview)中找到对此功能的高级介绍。

```cmake
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

```cmake
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

```cmake
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

需要最低版本的 cmake。

```cmake
cmake_minimum_required(VERSION <min>[...<policy_max>] [FATAL_ERROR])
```

*3.12 版中*的新功能：可选`<policy_max>`版本。

设置项目所需的最低 cmake 版本。还会更新策略设置，如下所述。

`<min>`并且可选`<policy_max>`的是 form 的每个 CMake 版本`major.minor[.patch[.tweak]]`，并且`...`是字面量。

如果 CMake 的运行版本低于`<min>`要求的版本，它将停止处理项目并报告错误。可选`<policy_max>`版本（如果指定）必须至少是 `<min>`版本并影响策略设置中所述的[策略设置](https://cmake.org/cmake/help/latest/command/cmake_minimum_required.html#policy-settings)。如果 CMake 的运行版本早于 3.12，多余的`...` 点将被视为版本组件分隔符，导致该 `...<max>`部分被忽略并保留 3.12 之前基于`<min>`.

该命令将设置的值 [`CMAKE_MINIMUM_REQUIRED_VERSION`](https://cmake.org/cmake/help/latest/variable/CMAKE_MINIMUM_REQUIRED_VERSION.html#variable:CMAKE_MINIMUM_REQUIRED_VERSION)变量为`<min>`。

`FATAL_ERROR`CMake 2.6 及更高版本接受但忽略该选项。应该指定它，以便 CMake 版本 2.4 和更低版本失败并出现错误，而不仅仅是警告。

> **笔记: ** `cmake_minimum_required()`在顶级文件的开头调用命令，`CMakeLists.txt`甚至在调用 [`project()`](https://cmake.org/cmake/help/latest/command/project.html#command:project)命令。在调用可能影响其行为的其他命令之前，建立版本和策略设置非常重要。另见政策[`CMP0000`](https://cmake.org/cmake/help/latest/policy/CMP0000.html#policy:CMP0000).
>
> `cmake_minimum_required()`在内部调用[`function()`](https://cmake.org/cmake/help/latest/command/function.html#command:function) 调用时限制对函数范围的一些影响。例如，[`CMAKE_MINIMUM_REQUIRED_VERSION`](https://cmake.org/cmake/help/latest/variable/CMAKE_MINIMUM_REQUIRED_VERSION.html#variable:CMAKE_MINIMUM_REQUIRED_VERSION)变量不会在调用范围内设置。但是函数不会引入自己的策略范围，因此调用者的策略设置*会*受到影响（见下文）。由于这种影响调用范围和不影响调用范围的事情的混合，`cmake_minimum_required()`通常不鼓励在函数内部调用。

### 策略设置

该`cmake_minimum_required(VERSION)`命令隐式调用 [`cmake_policy(VERSION)`](https://cmake.org/cmake/help/latest/command/cmake_policy.html#command:cmake_policy)命令指定当前项目代码是为给定的 CMake 版本范围编写的。CMake 的运行版本已知并在`<min>`（或`<max>`，如果指定）版本或更早版本中引入的所有策略都将设置为使用`NEW`行为。以后版本中引入的所有策略都将取消设置。这有效地请求了给定 CMake 版本的首选行为，并告诉较新的 CMake 版本警告其新策略。

当`<min>`指定高于 2.4 的版本时，该命令隐式调用

```cmake
cmake_policy(VERSION <min>[...<max>])
```

它根据指定的版本范围设置 CMake 策略。当`<min>`给出 2.4 或更低版本时，命令隐式调用

```cmake
cmake_policy(VERSION 2.4[...<max>])
```

这为 CMake 2.4 及更低版本启用了兼容性功能。



## [cmake_parse_arguments](https://cmake.org/cmake/help/latest/command/cmake_parse_arguments.html)

解析函数或宏参数。

```cmake
cmake_parse_arguments(<prefix> <options> <one_value_keywords>
                      <multi_value_keywords> <args>...)

cmake_parse_arguments(PARSE_ARGV <N> <prefix> <options>
                      <one_value_keywords> <multi_value_keywords>)
```

*3.5 版中的新功能：*此命令是本机实现的。之前已经在模块中定义了[`CMakeParseArguments`](https://cmake.org/cmake/help/latest/module/CMakeParseArguments.html#module:CMakeParseArguments).

此命令用于宏或函数。它处理赋予该宏或函数的参数，并定义一组变量来保存相应选项的值。

第一个签名读取在`<args>...`. 这可以用于任一[`macro()`](https://cmake.org/cmake/help/latest/command/macro.html#command:macro)或一个[`function()`](https://cmake.org/cmake/help/latest/command/function.html#command:function).

*3.7 新版功能：*签名`PARSE_ARGV`仅用于[`function()`](https://cmake.org/cmake/help/latest/command/function.html#command:function) 身体。在这种情况下，解析的参数来自 `ARGV#`调用函数的变量。解析从`<N>`-th 参数开始，其中`<N>`是一个无符号整数。这允许值具有像`;`它们一样的特殊字符。

该`<options>`参数包含相应宏的所有选项，即在调用宏时可以使用的关键字，没有任何值，`OPTIONAL`例如[`install()`](https://cmake.org/cmake/help/latest/command/install.html#command:install) 命令。

该参数包含此宏的所有关键字 `<one_value_keywords>`，后跟一个值，例如`DESTINATION`[`install()`](https://cmake.org/cmake/help/latest/command/install.html#command:install)命令。

该参数包含此宏的所有关键字，可以`<multi_value_keywords>`后跟多个值，例如 `TARGETS``FILES`[`install()`](https://cmake.org/cmake/help/latest/command/install.html#command:install)命令。

*在 3.5 版更改：*所有关键字都应是唯一的。即每个关键字只能在或 `<options>`中指定一次。如果违反唯一性，将发出警告。`<one_value_keywords>``<multi_value_keywords>`

完成后，`cmake_parse_arguments`将考虑 中列出的每个关键字`<options>`，`<one_value_keywords>`以及 `<multi_value_keywords>`由给定`<prefix>` 后跟`"_"`和相应关键字名称组成的变量。然后，这些变量将保存参数列表中的相应值，如果找不到相关选项，则这些变量将被取消定义。对于关键字，无论选项是否在参数列表中`<options>`，都将始终定义为 to`TRUE`或。`FALSE`

所有剩余的参数都收集在一个变量 `<prefix>_UNPARSED_ARGUMENTS`中，如果所有参数都被识别，该变量将是未定义的。这可以在之后检查以查看是否使用无法识别的参数调用了您的宏。

*3.15 版中的新功能：*`<one_value_keywords>`如果所有关键字都接收到值，则将完全`<multi_value_keywords>`没有值的变量收集在一个未定义的变量 中。`<prefix>_KEYWORDS_MISSING_VALUES`可以检查是否有没有给出任何值的关键字。

考虑以下示例宏 ，`my_install()`它采用与实数相似的参数[`install()`](https://cmake.org/cmake/help/latest/command/install.html#command:install)命令：

```cmake
macro(my_install)
    set(options OPTIONAL FAST)
    set(oneValueArgs DESTINATION RENAME)
    set(multiValueArgs TARGETS CONFIGURATIONS)
    cmake_parse_arguments(MY_INSTALL "${options}" "${oneValueArgs}"
                          "${multiValueArgs}" ${ARGN} )

    # ...
```

假设`my_install()`这样调用：

```cmake
my_install(TARGETS foo bar DESTINATION bin OPTIONAL blub CONFIGURATIONS)
```

调用后`cmake_parse_arguments`，宏将设置或取消定义以下变量：

```cmake
MY_INSTALL_OPTIONAL = TRUE
MY_INSTALL_FAST = FALSE # was not used in call to my_install
MY_INSTALL_DESTINATION = "bin"
MY_INSTALL_RENAME <UNDEFINED> # was not used
MY_INSTALL_TARGETS = "foo;bar"
MY_INSTALL_CONFIGURATIONS <UNDEFINED> # was not used
MY_INSTALL_UNPARSED_ARGUMENTS = "blub" # nothing expected after "OPTIONAL"
MY_INSTALL_KEYWORDS_MISSING_VALUES = "CONFIGURATIONS"
         # No value for "CONFIGURATIONS" given
```

然后，您可以继续并处理这些变量。

关键字终止值列表，例如，如果 `one_value_keyword`紧跟在另一个可识别的关键字之后，则这被解释为新选项的开始。例如 ，将导致 设置为，但 关键字本身将为空（但添加到），因此将设置为。`my_install(TARGETS foo DESTINATION OPTIONAL)``MY_INSTALL_DESTINATION``"OPTIONAL"``OPTIONAL``MY_INSTALL_DESTINATION``MY_INSTALL_KEYWORDS_MISSING_VALUES``MY_INSTALL_OPTIONAL``TRUE`



## [cmake_path](https://cmake.org/cmake/help/latest/command/cmake_path.html)

*3.20 版中的新功能。*

此命令用于处理路径。只处理路径的语法方面，不与任何底层文件系统进行任何类型的交互。该路径可能表示不存在的路径，甚至是当前文件系统或平台上不允许存在的路径。有关与文件系统交互的操作，请参阅[`file()`](https://cmake.org/cmake/help/latest/command/file.html#command:file) 命令。

笔记

 

该`cmake_path`命令处理构建系统（即主机平台）格式的路径，而不是目标系统。交叉编译时，如果路径包含在主机平台上无法表示的元素（例如，当主机不是 Windows 时的驱动器号），结果将是不可预知的。

### 简明

```cmake
Conventions

Path Structure And Terminology

Normalization

Decomposition
  cmake_path(GET <path-var> ROOT_NAME <out-var>)
  cmake_path(GET <path-var> ROOT_DIRECTORY <out-var>)
  cmake_path(GET <path-var> ROOT_PATH <out-var>)
  cmake_path(GET <path-var> FILENAME <out-var>)
  cmake_path(GET <path-var> EXTENSION [LAST_ONLY] <out-var>)
  cmake_path(GET <path-var> STEM [LAST_ONLY] <out-var>)
  cmake_path(GET <path-var> RELATIVE_PART <out-var>)
  cmake_path(GET <path-var> PARENT_PATH <out-var>)

Query
  cmake_path(HAS_ROOT_NAME <path-var> <out-var>)
  cmake_path(HAS_ROOT_DIRECTORY <path-var> <out-var>)
  cmake_path(HAS_ROOT_PATH <path-var> <out-var>)
  cmake_path(HAS_FILENAME <path-var> <out-var>)
  cmake_path(HAS_EXTENSION <path-var> <out-var>)
  cmake_path(HAS_STEM <path-var> <out-var>)
  cmake_path(HAS_RELATIVE_PART <path-var> <out-var>)
  cmake_path(HAS_PARENT_PATH <path-var> <out-var>)
  cmake_path(IS_ABSOLUTE <path-var> <out-var>)
  cmake_path(IS_RELATIVE <path-var> <out-var>)
  cmake_path(IS_PREFIX <path-var> <input> [NORMALIZE] <out-var>)
  cmake_path(COMPARE <input1> <OP> <input2> <out-var>)

Modification
  cmake_path(SET <path-var> [NORMALIZE] <input>)
  cmake_path(APPEND <path-var> [<input>...] [OUTPUT_VARIABLE <out-var>])
  cmake_path(APPEND_STRING <path-var> [<input>...] [OUTPUT_VARIABLE <out-var>])
  cmake_path(REMOVE_FILENAME <path-var> [OUTPUT_VARIABLE <out-var>])
  cmake_path(REPLACE_FILENAME <path-var> <input> [OUTPUT_VARIABLE <out-var>])
  cmake_path(REMOVE_EXTENSION <path-var> [LAST_ONLY] [OUTPUT_VARIABLE <out-var>])
  cmake_path(REPLACE_EXTENSION <path-var> [LAST_ONLY] <input> [OUTPUT_VARIABLE <out-var>])

Generation
  cmake_path(NORMAL_PATH <path-var> [OUTPUT_VARIABLE <out-var>])
  cmake_path(RELATIVE_PATH <path-var> [BASE_DIRECTORY <input>] [OUTPUT_VARIABLE <out-var>])
  cmake_path(ABSOLUTE_PATH <path-var> [BASE_DIRECTORY <input>] [NORMALIZE] [OUTPUT_VARIABLE <out-var>])

Native Conversion
  cmake_path(NATIVE_PATH <path-var> [NORMALIZE] <out-var>)
  cmake_path(CONVERT <input> TO_CMAKE_PATH_LIST <out-var> [NORMALIZE])
  cmake_path(CONVERT <input> TO_NATIVE_PATH_LIST <out-var> [NORMALIZE])

Hashing
  cmake_path(HASH <path-var> <out-var>)
```

### 约定

此命令的文档中使用了以下约定：

- `<path-var>`

  始终是变量的名称。对于期望 a`<path-var>` 作为输入的命令，该变量必须存在并且它应该包含单个路径。

- `<input>`

  一个字符串文字，它可能包含一个路径、路径片段或带有特殊分隔符的多个路径，具体取决于命令。查看每个命令的描述以了解如何解释。

- `<input>...`

  零个或多个字符串文字参数。

- `<out-var>`

  将写入命令结果的变量的名称。



### 路径结构和术语

路径具有以下结构（所有组件都是可选的，有一些约束）：

```cmake
root-name root-directory-separator (item-name directory-separator)* filename
```

- `root-name`

  标识具有多个根（例如`"C:"` 或`"//myserver"`）的文件系统上的根。它是可选的。

- `root-directory-separator`

  目录分隔符，如果存在，则表明此路径是绝对路径。如果它缺失并且除 the 之外的第一个元素 `root-name`是`item-name`，则路径是相对的。

- `item-name`

  不是目录分隔符的字符序列。此名称可以标识文件、硬链接、符号链接或目录。两种特殊情况被识别：由单个点字符组成的项目名称`.`是指当前目录的目录名称。由两个点字符组成的项目名称`..`是指父目录的目录名称。上面显示的`(...)*`模式是表示可以有零个或多个项目名称，多个项目用 . 分隔 `directory-separator`。`()*`字符不是路径的一部分。

- `directory-separator`

  唯一可识别的目录分隔符是正斜杠字符`/`。如果此字符重复，则将其视为单个目录分隔符。换句话说，`/usr///////lib`与 相同`/usr/lib`。



- `filename`

  如果路径`filename`不以 a 结尾，则它具有 a `directory-separator`。它`filename`实际上是路径的最后一个`item-name`，因此它也可以是硬链接、符号链接或目录。A`filename`可以有*扩展名*。默认情况下，扩展名定义为从最左边的句点（包括句点）开始到`filename`. 在接受`LAST_ONLY`关键字的命令中，`LAST_ONLY`将解释更改为从最右边的句点开始的子字符串。以下例外适用于上述解释：如果 中的第一个字符`filename`是句点，则忽略该句点（即，将`filename`like`".profile"`视为没有扩展名）。如果`filename`是`.`或`..`，则它没有扩展名。*词干*是`filename`延伸之前的部分。

一些命令指的是`root-path`. 这是 and 的串联 `root-name`，`root-directory-separator`其中一个或两个都可以为空。A`relative-part`是指`root-path` 删除任何内容的完整路径。

### 创建路径变量

虽然可以使用普通的路径小心地创建路径[`set()`](https://cmake.org/cmake/help/latest/command/set.html#command:set) 命令，建议使用[cmake_path(SET)](https://cmake.org/cmake/help/latest/command/cmake_path.html#cmake-path-set) 代替，因为它会在需要时自动将路径转换为所需的形式。cmake_path [(APPEND)](https://cmake.org/cmake/help/latest/command/string.html#append)子命令可能是另一个合适的替代方法，其中需要通过连接片段来构建路径。下面的例子比较了三种构造相同路径的方法：

```cmake
set(path1 "${CMAKE_CURRENT_SOURCE_DIR}/data")

cmake_path(SET path2 "${CMAKE_CURRENT_SOURCE_DIR}/data")

cmake_path(APPEND path3 "${CMAKE_CURRENT_SOURCE_DIR}" "data")
```

[修改](https://cmake.org/cmake/help/latest/command/cmake_path.html#modification)和[生成](https://cmake.org/cmake/help/latest/command/cmake_path.html#generation)`OUTPUT_VARIABLE`子命令可以将结果存储在原地，也可以存储在以 关键字命名的单独变量中。所有其他子命令将结果存储在强制`<out-var>` 变量中。



### Normalization

一些子命令支持*规范化*路径。用于规范化路径的算法如下：

1. 如果路径为空，则停止（空路径的规范化形式也是空路径）。
2. 将可能由多个分隔符组成的each 替换`directory-separator`为单个`/`( )。`/a///b --> /a/b`
3. 删除每个单独的句号 ( `.`) 和紧随其后 的`directory-separator`( )。`/a/./b/. --> /a/b`
4. 删除紧随 a和 a 的每个`item-name`（除了），以及紧随其后的( )。`..``directory-separator``..``directory-separator``/a/b/../c --> a/c`
5. 如果有`root-directory`，请删除紧随其后的任何`..`和任何 。`directory-separators`根目录的父级仍被视为根目录 ( )。`/../a --> /a`
6. 如果最后一个`item-name`是`..`，请删除任何尾随 `directory-separator`( )。`../ --> ..`
7. 如果此阶段路径为空，请添加一个`dot`（正常形式的`./` is `.`）。



### 分解

以下形式的`GET`子命令分别从路径中检索不同的组件或组件组。有关每个路径组件的含义，请参阅 [路径结构和术语](https://cmake.org/cmake/help/latest/command/cmake_path.html#path-structure-and-terminology)。

```cmake
cmake_path(GET <path-var> ROOT_NAME <out-var>)
cmake_path(GET <path-var> ROOT_DIRECTORY <out-var>)
cmake_path(GET <path-var> ROOT_PATH <out-var>)
cmake_path(GET <path-var> FILENAME <out-var>)
cmake_path(GET <path-var> EXTENSION [LAST_ONLY] <out-var>)
cmake_path(GET <path-var> STEM [LAST_ONLY] <out-var>)
cmake_path(GET <path-var> RELATIVE_PART <out-var>)
cmake_path(GET <path-var> PARENT_PATH <out-var>)
```

如果路径中不存在请求的组件，则会将空字符串存储在`<out-var>`. 例如，只有 Windows 系统才有 a 的概念`root-name`，所以当宿主机不是 Windows 时，`ROOT_NAME` 子命令将始终返回一个空字符串。

对于`PARENT_PATH`，如果[HAS_RELATIVE_PART](https://cmake.org/cmake/help/latest/command/cmake_path.html#has-relative-part)子命令返回 false，则结果是`<path-var>`. 请注意，这意味着根目录被认为具有父目录，而该父目录就是它本身。在[HAS_RELATIVE_PART](https://cmake.org/cmake/help/latest/command/cmake_path.html#has-relative-part)返回 true 的情况下，结果基本上会 `<path-var>`少一个元素。

### 根示例

```cmake
set(path "c:/a")

cmake_path(GET path ROOT_NAME rootName)
cmake_path(GET path ROOT_DIRECTORY rootDir)
cmake_path(GET path ROOT_PATH rootPath)

message("Root name is \"${rootName}\"")
message("Root directory is \"${rootDir}\"")
message("Root path is \"${rootPath}\"")
Root name is "c:"
Root directory is "/"
Root path is "c:/"
```

### 文件名示例

```cmake
set(path "/a/b")
cmake_path(GET path FILENAME filename)
message("First filename is \"${filename}\"")

# Trailing slash means filename is empty
set(path "/a/b/")
cmake_path(GET path FILENAME filename)
message("Second filename is \"${filename}\"")
First filename is "b"
Second filename is ""
```

### 扩展和词干示例

```cmake
set(path "name.ext1.ext2")

cmake_path(GET path EXTENSION fullExt)
cmake_path(GET path STEM fullStem)
message("Full extension is \"${fullExt}\"")
message("Full stem is \"${fullStem}\"")

# Effect of LAST_ONLY
cmake_path(GET path EXTENSION LAST_ONLY lastExt)
cmake_path(GET path STEM LAST_ONLY lastStem)
message("Last extension is \"${lastExt}\"")
message("Last stem is \"${lastStem}\"")

# Special cases
set(dotPath "/a/.")
set(dotDotPath "/a/..")
set(someMorePath "/a/.some.more")
cmake_path(GET dotPath EXTENSION dotExt)
cmake_path(GET dotPath STEM dotStem)
cmake_path(GET dotDotPath EXTENSION dotDotExt)
cmake_path(GET dotDotPath STEM dotDotStem)
cmake_path(GET dotMorePath EXTENSION someMoreExt)
cmake_path(GET dotMorePath STEM someMoreStem)
message("Dot extension is \"${dotExt}\"")
message("Dot stem is \"${dotStem}\"")
message("Dot-dot extension is \"${dotDotExt}\"")
message("Dot-dot stem is \"${dotDotStem}\"")
message(".some.more extension is \"${someMoreExt}\"")
message(".some.more stem is \"${someMoreStem}\"")
Full extension is ".ext1.ext2"
Full stem is "name"
Last extension is ".ext2"
Last stem is "name.ext1"
Dot extension is ""
Dot stem is "."
Dot-dot extension is ""
Dot-dot stem is ".."
.some.more extension is ".more"
.some.more stem is ".some"
```

### 相关部分示例

```cmake
set(path "c:/a/b")
cmake_path(GET path RELATIVE_PART result)
message("Relative part is \"${result}\"")

set(path "c/d")
cmake_path(GET path RELATIVE_PART result)
message("Relative part is \"${result}\"")

set(path "/")
cmake_path(GET path RELATIVE_PART result)
message("Relative part is \"${result}\"")
Relative part is "a/b"
Relative part is "c/d"
Relative part is ""
```

### 路径遍历示例

```cmake
set(path "c:/a/b")
cmake_path(GET path PARENT_PATH result)
message("Parent path is \"${result}\"")

set(path "c:/")
cmake_path(GET path PARENT_PATH result)
message("Parent path is \"${result}\"")
Parent path is "c:/a"
Parent path is "c:/"
```



### 查询

每个`GET`子命令都有一个相应的`HAS_...` 子命令，可用于发现是否存在特定路径组件。有关每个路径组件的含义，请参阅[路径结构和术语](https://cmake.org/cmake/help/latest/command/cmake_path.html#path-structure-and-terminology)。



```cmake
cmake_path(HAS_ROOT_NAME <path-var> <out-var>)
cmake_path(HAS_ROOT_DIRECTORY <path-var> <out-var>)
cmake_path(HAS_ROOT_PATH <path-var> <out-var>)
cmake_path(HAS_FILENAME <path-var> <out-var>)
cmake_path(HAS_EXTENSION <path-var> <out-var>)
cmake_path(HAS_STEM <path-var> <out-var>)
cmake_path(HAS_RELATIVE_PART <path-var> <out-var>)
cmake_path(HAS_PARENT_PATH <path-var> <out-var>)
```

如果路径具有关联的组件，则上述每个都遵循设置`<out-var>` 为 true 的可预测模式，否则设置为 false。请注意以下特殊情况：

- 对于，只有当或中的至少一个不为空`HAS_ROOT_PATH`时才会返回真正的结果。`root-name``root-directory`
- 对于`HAS_PARENT_PATH`，根目录也被认为有一个父目录，它就是它自己。结果为真，除非路径仅包含一个[文件名](https://cmake.org/cmake/help/latest/command/cmake_path.html#filename-def)。

```cmake
cmake_path(IS_ABSOLUTE <path-var> <out-var>)
```

如果是绝对的，则设置`<out-var>`为 true 。`<path-var>`绝对路径是在不参考其他起始位置的情况下明确标识文件位置的路径。在 Windows 上，这意味着路径必须同时具有 a`root-name`和 a`root-directory-separator`才能被视为绝对路径。在其他平台上，一个`root-directory-separator` 就足够了。请注意，这意味着在 Windows 上，`IS_ABSOLUTE`可以为假，而`HAS_ROOT_DIRECTORY`可以为真。

```cmake
cmake_path(IS_RELATIVE <path-var> <out-var>)
```

这将存储`IS_ABSOLUTE`in的反面`<out-var>`。

```cmake
cmake_path(IS_PREFIX <path-var> <input> [NORMALIZE] <out-var>)
```

检查是否`<path-var>`是 的前缀`<input>`。

指定`NORMALIZE`选项`<path-var>`并在检查前`<input>` 进行[标准化](https://cmake.org/cmake/help/latest/command/cmake_path.html#normalization)时。

```cmake
set(path "/a/b/c")
cmake_path(IS_PREFIX path "/a/b/c/d" result) # result = true
cmake_path(IS_PREFIX path "/a/b" result)     # result = false
cmake_path(IS_PREFIX path "/x/y/z" result)   # result = false

set(path "/a/b")
cmake_path(IS_PREFIX path "/a/c/../b" NORMALIZE result)   # result = true
```



```cmake
cmake_path(COMPARE <input1> EQUAL <input2> <out-var>)
cmake_path(COMPARE <input1> NOT_EQUAL <input2> <out-var>)
```

比较作为字符串文字提供的两个路径的词法表示。除了多个连续的目录分隔符被有效地折叠成一个分隔符外，不会对任一路径执行规范化。根据以下伪代码逻辑确定相等性：

```cmake
if(NOT <input1>.root_name() STREQUAL <input2>.root_name())
  return FALSE

if(<input1>.has_root_directory() XOR <input2>.has_root_directory())
  return FALSE

Return FALSE if a relative portion of <input1> is not lexicographically
equal to the relative portion of <input2>. This comparison is performed path
component-wise. If all of the components compare equal, then return TRUE.
```

笔记

 

与大多数其他`cmake_path()`子命令不同，该`COMPARE`子命令将文字字符串作为输入，而不是变量的名称。



### Modification

```cmake
cmake_path(SET <path-var> [NORMALIZE] <input>)
```

将`<input>`路径分配给`<path-var>`. 如果`<input>`是本机路径，则将其转换为带有正斜杠 ( `/`) 的 cmake 样式路径。在 Windows 上，考虑了长文件名标记。

指定选项时`NORMALIZE`，路径在转换后进行[规范化。](https://cmake.org/cmake/help/latest/command/cmake_path.html#normalization)

例如：

```cmake
set(native_path "c:\\a\\b/..\\c")
cmake_path(SET path "${native_path}")
message("CMake path is \"${path}\"")

cmake_path(SET path NORMALIZE "${native_path}")
message("Normalized CMake path is \"${path}\"")
```

输出：

```cmake
CMake path is "c:/a/b/../c"
Normalized CMake path is "c:/a/c"
cmake_path(APPEND <path-var> [<input>...] [OUTPUT_VARIABLE <out-var>])
```

`<input>`将所有参数附加到`<path-var>`using`/`作为`directory-separator`. 根据`<input>`， 的先前内容`<path-var>`可能会被丢弃。对于每个`<input>`参数，以下算法（伪代码）适用：

```cmake
# <path> is the contents of <path-var>

if(<input>.is_absolute() OR
   (<input>.has_root_name() AND
    NOT <input>.root_name() STREQUAL <path>.root_name()))
  replace <path> with <input>
  return()
endif()

if(<input>.has_root_directory())
  remove any root-directory and the entire relative path from <path>
elseif(<path>.has_filename() OR
       (NOT <path-var>.has_root_directory() OR <path>.is_absolute()))
  append directory-separator to <path>
endif()

append <input> omitting any root-name to <path>
cmake_path(APPEND_STRING <path-var> [<input>...] [OUTPUT_VARIABLE <out-var>])
```

将所有`<input>`参数附加到`<path-var>`而不添加任何 `directory-separator`.

```cmake
cmake_path(REMOVE_FILENAME <path-var> [OUTPUT_VARIABLE <out-var>])
```

从 中删除[文件名](https://cmake.org/cmake/help/latest/command/cmake_path.html#filename-def)组件（由 [GET ... FILENAME](https://cmake.org/cmake/help/latest/command/cmake_path.html#get-filename)返回）`<path-var>`。删除后，任何尾随`directory-separator`（如果存在）将被单独留下。

如果`OUTPUT_VARIABLE`未给出，则在此函数返回后， [HAS_FILENAME](https://cmake.org/cmake/help/latest/command/cmake_path.html#has-filename)为`<path-var>`.

例如：

```cmake
set(path "/a/b")
cmake_path(REMOVE_FILENAME path)
message("First path is \"${path}\"")

# filename is now already empty, the following removes nothing
cmake_path(REMOVE_FILENAME path)
message("Second path is \"${result}\"")
```

输出：

```cmake
First path is "/a/"
Second path is "/a/"
cmake_path(REPLACE_FILENAME <path-var> <input> [OUTPUT_VARIABLE <out-var>])
```

用替换[文件名](https://cmake.org/cmake/help/latest/command/cmake_path.html#filename-def)组件。如果没有文件名组件（即 [HAS_FILENAME](https://cmake.org/cmake/help/latest/command/cmake_path.html#has-filename)返回 false），则路径不变。该操作等效于以下内容：`<path-var>``<input>``<path-var>`

```cmake
cmake_path(HAS_FILENAME path has_filename)
if(has_filename)
  cmake_path(REMOVE_FILENAME path)
  cmake_path(APPEND path input);
endif()
cmake_path(REMOVE_EXTENSION <path-var> [LAST_ONLY]
                                       [OUTPUT_VARIABLE <out-var>])
```

从 中删除[扩展名](https://cmake.org/cmake/help/latest/command/cmake_path.html#extension-def)（如果有）`<path-var>`。

```cmake
cmake_path(REPLACE_EXTENSION <path-var> [LAST_ONLY] <input>
                             [OUTPUT_VARIABLE <out-var>])
```

[将扩展名](https://cmake.org/cmake/help/latest/command/cmake_path.html#extension-def)替换为`<input>`. 其效果相当于如下：

```cmake
cmake_path(REMOVE_EXTENSION path)
if(NOT "input" MATCHES "^\\.")
  cmake_path(APPEND_STRING path ".")
endif()
cmake_path(APPEND_STRING path "input")
```



### Generation

```cmake
cmake_path(NORMAL_PATH <path-var> [OUTPUT_VARIABLE <out-var>])
```

根据规范化`<path-var>`中描述的步骤进行[规范化](https://cmake.org/cmake/help/latest/command/cmake_path.html#normalization)。



```cmake
cmake_path(RELATIVE_PATH <path-var> [BASE_DIRECTORY <input>]
                                    [OUTPUT_VARIABLE <out-var>])
```

修改`<path-var>`以使其相对于`BASE_DIRECTORY`参数。如果`BASE_DIRECTORY`未指定，则默认基目录为 [`CMAKE_CURRENT_SOURCE_DIR`](https://cmake.org/cmake/help/latest/variable/CMAKE_CURRENT_SOURCE_DIR.html#variable:CMAKE_CURRENT_SOURCE_DIR).

作为参考，用于计算相对路径的算法与 C++ [std::filesystem::path::lexically_relative](https://en.cppreference.com/w/cpp/filesystem/path/lexically_normal)使用的算法相同。

```cmake
cmake_path(ABSOLUTE_PATH <path-var> [BASE_DIRECTORY <input>] [NORMALIZE]
                                    [OUTPUT_VARIABLE <out-var>])
```

如果`<path-var>`是相对路径（[IS_RELATIVE](https://cmake.org/cmake/help/latest/command/cmake_path.html#is-relative)为真），则相对于`BASE_DIRECTORY`选项指定的给定基目录进行评估。如果`BASE_DIRECTORY`未指定，则默认基目录为 [`CMAKE_CURRENT_SOURCE_DIR`](https://cmake.org/cmake/help/latest/variable/CMAKE_CURRENT_SOURCE_DIR.html#variable:CMAKE_CURRENT_SOURCE_DIR).

指定选项时，路径计算后`NORMALIZE`路径被[归一化。](https://cmake.org/cmake/help/latest/command/cmake_path.html#normalization)

因为`cmake_path()`不访问文件系统，所以不解析符号链接，也不扩展任何前导波浪号。要计算具有已解析符号链接和扩展前导波浪线的真实路径，请使用 [`file(REAL_PATH)`](https://cmake.org/cmake/help/latest/command/file.html#command:file)而是命令。

### 原生转换

对于本节中的命令，*native*是指宿主平台，而不是交叉编译时的目标平台。



```cmake
cmake_path(NATIVE_PATH <path-var> [NORMALIZE] <out-var>)
```

将 cmake 样式`<path-var>`转换为带有特定于平台的斜杠的本机路径（`\`在 Windows 主机和`/`其他地方）。

当`NORMALIZE`指定选项时，路径在转换之前被[规范化。](https://cmake.org/cmake/help/latest/command/cmake_path.html#normalization)



```cmake
cmake_path(CONVERT <input> TO_CMAKE_PATH_LIST <out-var> [NORMALIZE])
```

将本机`<input>`路径转换为带有正斜杠 ( `/`) 的 cmake 样式路径。在 Windows 主机上，会考虑长文件名标记。输入可以是单个路径或系统搜索路径，例如 `$ENV{PATH}`. 搜索路径将转换为由`;`字符分隔的 cmake 样式列表（在非 Windows 平台上，这实质上意味着`:`分隔符被替换为`;`）。转换的结果存储在`<out-var>`变量中。

当`NORMALIZE`指定选项时，路径在转换之前被[规范化。](https://cmake.org/cmake/help/latest/command/cmake_path.html#normalization)

笔记

 

与大多数其他`cmake_path()`子命令不同，该`CONVERT`子命令将文字字符串作为输入，而不是变量的名称。



```cmake
cmake_path(CONVERT <input> TO_NATIVE_PATH_LIST <out-var> [NORMALIZE])
```

将 cmake 样式的`<input>`路径转换为带有特定于平台的斜杠的本机路径（`\`在 Windows 主机和`/`其他地方）。输入可以是单个路径或 cmake 样式的列表。列表将被转换为本机搜索路径（`;`在 Windows 上为 `:`-separated，在其他平台上为 -separated）。转换的结果存储在`<out-var>`变量中。

当`NORMALIZE`指定选项时，路径在转换之前被[规范化。](https://cmake.org/cmake/help/latest/command/cmake_path.html#normalization)

笔记

 

与大多数其他`cmake_path()`子命令不同，该`CONVERT`子命令将文字字符串作为输入，而不是变量的名称。

例如：

```cmake
set(paths "/a/b/c" "/x/y/z")
cmake_path(CONVERT "${paths}" TO_NATIVE_PATH_LIST native_paths)
message("Native path list is \"${native_paths}\"")
```

Windows 上的输出：

```cmake
Native path list is "\a\b\c;\x\y\z"
```

所有其他平台上的输出：

```cmake
Native path list is "/a/b/c:/x/y/z"
```

### 哈希

```cmake
cmake_path(HASH <path-var> <out-var>)
```

计算 的散列值，使得 `<path-var>`对于两条比较相等的路径 ( [COMPARE ... EQUAL](https://cmake.org/cmake/help/latest/command/string.html#compare) )， 的散列值等于 的散列值。在计算散列之前，路径总是被 [规范化。](https://cmake.org/cmake/help/latest/command/cmake_path.html#normalization)`p1``p2``p1``p2`



## [cmake_policy](https://cmake.org/cmake/help/latest/command/cmake_policy.html)

管理 CMake 策略设置。见[`cmake-policies(7)`](https://cmake.org/cmake/help/latest/manual/cmake-policies.7.html#manual:cmake-policies(7)) 定义策略的手册。

随着 CMake 的发展，有时需要更改现有行为以修复错误或改进现有功能的实现。CMake 策略机制旨在帮助在新版本的 CMake 引入行为变化时保持现有项目的构建。每个新策略（行为变化）都被赋予一个形式的标识符， `CMP<NNNN>`其中`<NNNN>`是一个整数索引。与每项策略相关的文档描述了该策略的`OLD`行为`NEW`和引入该策略的原因。项目可以设置每个策略来选择所需的行为。当 CMake 需要知道使用哪种行为时，它会检查项目指定的设置。如果没有可用的设置，`OLD`则假定行为并生成警告，要求设置策略。

### 通过 CMake 版本设置策略

该`cmake_policy`命令用于设置策略`OLD`或`NEW` 行为。虽然支持单独设置策略，但我们鼓励项目根据 CMake 版本设置策略：

```cmake
cmake_policy(VERSION <min>[...<max>])
```

*3.12 版中*的新功能：可选`<max>`版本。

`<min>`并且可选`<max>`的是 form 的每个 CMake 版本 `major.minor[.patch[.tweak]]`，并且`...`是字面量。该`<min>` 版本必须至少`2.4`且最多是 CMake 的运行版本。如果`<max>`指定，版本必须至少是`<min>`版本，但可能超过 CMake 的运行版本。如果 CMake 的运行版本早于 3.12，多余的`...`点将被视为版本组件分隔符，导致该`...<max>`部分被忽略并保留 3.12 之前基于`<min>`.

这指定当前 CMake 代码是为给定的 CMake 版本范围编写的。CMake 的运行版本已知并在`<min>`（或`<max>`，如果指定）版本或更早版本中引入的所有策略都将设置为使用`NEW`行为。以后版本中引入的所有策略都将取消设置（除非 [`CMAKE_POLICY_DEFAULT_CMP`](https://cmake.org/cmake/help/latest/variable/CMAKE_POLICY_DEFAULT_CMPNNNN.html#variable:CMAKE_POLICY_DEFAULT_CMP)变量设置默认值）。这有效地请求了给定 CMake 版本的首选行为，并告诉较新的 CMake 版本警告其新策略。

请注意，[`cmake_minimum_required(VERSION)`](https://cmake.org/cmake/help/latest/command/cmake_minimum_required.html#command:cmake_minimum_required) command`cmake_policy(VERSION)`也隐式调用。

### 明确设置策略

```cmake
cmake_policy(SET CMP<NNNN> NEW)
cmake_policy(SET CMP<NNNN> OLD)
```

告诉 CMake 对给定策略使用`OLD`or`NEW`行为。依赖于给定策略的旧行为的项目可以通过将策略状态设置为 来使策略警告静音`OLD`。或者，可以修复项目以使用新行为并将策略状态设置为`NEW`.

笔记

 

策略的`OLD`行为是 [`deprecated by definition`](https://cmake.org/cmake/help/latest/manual/cmake-policies.7.html#manual:cmake-policies(7)) 并且可能会在 CMake 的未来版本中删除。

### 检查策略设置

```cmake
cmake_policy(GET CMP<NNNN> <variable>)
```

检查给定的策略是否设置为`OLD`或`NEW`行为。如果设置了策略，则输出`<variable>`值为`OLD`or `NEW`，否则为空。

### CMake 策略堆栈

CMake 将策略设置保存在堆栈上，因此命令所做的更改 `cmake_policy`仅影响堆栈的顶部。为每个子目录自动管理策略堆栈上的新条目，以保护其父级和兄弟级。CMake 还管理由加载的脚本的新条目[`include()`](https://cmake.org/cmake/help/latest/command/include.html#command:include)和[`find_package()`](https://cmake.org/cmake/help/latest/command/find_package.html#command:find_package)命令，除非使用`NO_POLICY_SCOPE`选项调用（另请参阅策略[`CMP0011`](https://cmake.org/cmake/help/latest/policy/CMP0011.html#policy:CMP0011)）。该`cmake_policy`命令提供了一个界面来管理策略堆栈上的自定义条目：

```cmake
cmake_policy(PUSH)
cmake_policy(POP)
```

每个都`PUSH`必须有一个匹配项`POP`才能删除任何更改。这对于临时更改策略设置很有用。调用[`cmake_minimum_required(VERSION)`](https://cmake.org/cmake/help/latest/command/cmake_minimum_required.html#command:cmake_minimum_required)、 `cmake_policy(VERSION)`或`cmake_policy(SET)`命令仅影响策略堆栈的当前顶部。

由创建的命令[`function()`](https://cmake.org/cmake/help/latest/command/function.html#command:function)和[`macro()`](https://cmake.org/cmake/help/latest/command/macro.html#command:macro) 命令在创建时记录策略设置，并在调用时使用预先记录的策略。如果函数或宏实现设置了策略，则更改会自动通过调用者向上传播，直到它们到达最近的嵌套策略堆栈条目。



## [configure_file](https://cmake.org/cmake/help/latest/command/configure_file.html)

将文件复制到另一个位置并修改其内容。

```cmake
configure_file(<input> <output>
               [NO_SOURCE_PERMISSIONS | USE_SOURCE_PERMISSIONS |
                FILE_PERMISSIONS <permissions>...]
               [COPYONLY] [ESCAPE_QUOTES] [@ONLY]
               [NEWLINE_STYLE [UNIX|DOS|WIN32|LF|CRLF] ])
```

将文件复制`<input>`到文件并替换在输入文件内容中`<output>`引用的变量值`@VAR@`。`${VAR}`每个变量引用都将替换为变量的当前值，如果未定义变量，则替换为空字符串。此外，表格的输入行

```cmake
#cmakedefine VAR ...
```

将被替换为

```cmake
#define VAR ...
```

或者

```cmake
/* #undef VAR */
```

取决于是否`VAR`在 CMake 中设置为任何不被视为假常量的值[`if()`](https://cmake.org/cmake/help/latest/command/if.html#command:if)命令。变量名后面的“...”内容，如果有的话，按照上面的方法处理。

与表格的行不同，在表格的行中 ，它本身将扩展为或 而不是被分配值。因此，表格的输入行`#cmakedefine VAR ...``#cmakedefine01 VAR``VAR``VAR 0``VAR 1``...`

```cmake
#cmakedefine01 VAR
```

将被替换为

```cmake
#define VAR 0
```

或者

```cmake
#define VAR 1
```

表单的输入行将扩展为或，这可能导致未定义的行为。`#cmakedefine01 VAR ...``#cmakedefine01 VAR ... 0``#cmakedefine01 VAR ... 0`

*3.10 版中的新功能：*结果行（`#undef`注释除外）可以在`#`字符和`cmakedefine`or`cmakedefine01`单词之间使用空格和/或制表符缩进。此空白缩进将保留在输出行中：

```cmake
#  cmakedefine VAR
#  cmakedefine01 VAR
```

`VAR`如果已定义，将被替换为

```cmake
#  define VAR
#  define VAR 1
```

如果输入文件被修改，构建系统将重新运行 CMake 以重新配置文件并再次生成构建系统。生成的文件会被修改，并且只有在其内容发生更改时才会在后续 cmake 运行时更新其时间戳。

论据是：

- `<input>`

  输入文件的路径。相对路径的值相对于[`CMAKE_CURRENT_SOURCE_DIR`](https://cmake.org/cmake/help/latest/variable/CMAKE_CURRENT_SOURCE_DIR.html#variable:CMAKE_CURRENT_SOURCE_DIR). 输入路径必须是文件，而不是目录。

- `<output>`

  输出文件或目录的路径。相对路径的值相对于[`CMAKE_CURRENT_BINARY_DIR`](https://cmake.org/cmake/help/latest/variable/CMAKE_CURRENT_BINARY_DIR.html#variable:CMAKE_CURRENT_BINARY_DIR). 如果路径命名现有目录，则输出文件将放置在该目录中，文件名与输入文件相同。如果路径包含不存在的目录，则会创建它们。

- `NO_SOURCE_PERMISSIONS`

  *3.19 版中的新功能。*不要将输入文件的权限转移到输出文件。复制的文件权限默认为标准 644 值 (-rw-r--r--)。

- `USE_SOURCE_PERMISSIONS`

  *3.20 版中的新功能。*将输入文件的权限转移到输出文件。 如果没有给出三个与权限相关的关键字（或）`NO_SOURCE_PERMISSIONS`，这已经是默认行为。关键字主要用作使呼叫站点上的预期行为更清晰的一种方式。`USE_SOURCE_PERMISSIONS``FILE_PERMISSIONS``USE_SOURCE_PERMISSIONS`

- `FILE_PERMISSIONS <permissions>...`

  *3.20 版中的新功能。*忽略输入文件的权限并使用`<permissions>` 为输出文件指定的权限。

- `COPYONLY`

  复制文件而不替换任何变量引用或其他内容。此选项不能与`NEWLINE_STYLE`.

- `ESCAPE_QUOTES`

  使用反斜杠（C 样式）转义任何替换的引号。

- `@ONLY`

  将变量替换限制为对表单的引用`@VAR@`。这对于配置使用`${VAR}`语法的脚本很有用。

- `NEWLINE_STYLE <style>`

  指定输出文件的换行样式。为换行指定 `UNIX`or ，或`LF`为换`\n`行指定 `DOS`, `WIN32`, or 。此选项不能与.`CRLF``\r\n``COPYONLY`

### Example

考虑一个包含`foo.h.in`文件的源代码树：

```cmake
#cmakedefine FOO_ENABLE
#cmakedefine FOO_STRING "@FOO_STRING@"
```

一个相邻的`CMakeLists.txt`可以`configure_file`用来配置标头：

```cmake
option(FOO_ENABLE "Enable Foo" ON)
if(FOO_ENABLE)
  set(FOO_STRING "foo")
endif()
configure_file(foo.h.in foo.h @ONLY)
```

`foo.h`这将在与此源目录对应的构建目录中创建一个。如果该`FOO_ENABLE`选项打开，配置文件将包含：

```cmake
#define FOO_ENABLE
#define FOO_STRING "foo"
```

否则它将包含：

```cmake
/* #undef FOO_ENABLE */
/* #undef FOO_STRING */
```

然后可以使用[`include_directories()`](https://cmake.org/cmake/help/latest/command/include_directories.html#command:include_directories)将输出目录指定为包含目录的命令：

```cmake
include_directories(${CMAKE_CURRENT_BINARY_DIR})
```

以便源可以将标头包含为.`#include <foo.h>`



# 基本语法

## [string](https://cmake.org/cmake/help/latest/command/string.html)

字符串操作。

### 简明

```cmake
Search and Replace
  string(FIND <string> <substring> <out-var> [...])
  string(REPLACE <match-string> <replace-string> <out-var> <input>...)
  string(REGEX MATCH <match-regex> <out-var> <input>...)
  string(REGEX MATCHALL <match-regex> <out-var> <input>...)
  string(REGEX REPLACE <match-regex> <replace-expr> <out-var> <input>...)

Manipulation
  string(APPEND <string-var> [<input>...])
  string(PREPEND <string-var> [<input>...])
  string(CONCAT <out-var> [<input>...])
  string(JOIN <glue> <out-var> [<input>...])
  string(TOLOWER <string> <out-var>)
  string(TOUPPER <string> <out-var>)
  string(LENGTH <string> <out-var>)
  string(SUBSTRING <string> <begin> <length> <out-var>)
  string(STRIP <string> <out-var>)
  string(GENEX_STRIP <string> <out-var>)
  string(REPEAT <string> <count> <out-var>)

Comparison
  string(COMPARE <op> <string1> <string2> <out-var>)

Hashing
  string(<HASH> <out-var> <input>)

Generation
  string(ASCII <number>... <out-var>)
  string(HEX <string> <out-var>)
  string(CONFIGURE <string> <out-var> [...])
  string(MAKE_C_IDENTIFIER <string> <out-var>)
  string(RANDOM [<option>...] <out-var>)
  string(TIMESTAMP <out-var> [<format string>] [UTC])
  string(UUID <out-var> ...)

JSON
  string(JSON <out-var> [ERROR_VARIABLE <error-var>]
         {GET | TYPE | LENGTH | REMOVE}
         <json-string> <member|index> [<member|index> ...])
  string(JSON <out-var> [ERROR_VARIABLE <error-var>]
         MEMBER <json-string>
         [<member|index> ...] <index>)
  string(JSON <out-var> [ERROR_VARIABLE <error-var>]
         SET <json-string>
         <member|index> [<member|index> ...] <value>)
  string(JSON <out-var> [ERROR_VARIABLE <error-var>]
         EQUAL <json-string1> <json-string2>)
```

### 搜索和替换

#### 搜索和替换为纯字符串

```cmake
string(FIND <string> <substring> <output_variable> [REVERSE])
```

`<substring>`返回在提供的中找到给定的位置`<string>`。如果`REVERSE`使用了标志，该命令将搜索指定的最后一次出现的位置 `<substring>`。如果`<substring>`未找到，则返回 -1 的位置。

该`string(FIND)`子命令将所有字符串视为仅 ASCII 字符。存储的索引`<output_variable>`也会以字节为单位计算，因此包含多字节字符的字符串可能会导致意外结果。

```cmake
string(REPLACE <match_string>
       <replace_string> <output_variable>
       <input> [<input>...])
```

用with替换所有出现的`<match_string>`，并将结果存储在.`<input>` `<replace_string>` `<output_variable>`

#### 用正则表达式搜索和替换

```cmake
string(REGEX MATCH <regular_expression>
       <output_variable> <input> [<input>...])
```

匹配`<regular_expression>`一次并将匹配存储在 `<output_variable>`. 所有`<input>`参数在匹配之前连接起来。正则表达式在下面的小节中指定。

```cmake
string(REGEX MATCHALL <regular_expression>
       <output_variable> <input> [<input>...])
```

`<regular_expression>`尽可能多地匹配并将匹配项存储在列表`<output_variable>`中。所有`<input>`参数在匹配之前连接起来。

```cmake
string(REGEX REPLACE <regular_expression>
       <replacement_expression> <output_variable>
       <input> [<input>...])
```

`<regular_expression>`尽可能多地匹配并替换`<replacement_expression>`输出中的匹配项。所有`<input>`参数在匹配之前连接起来。

可以使用`<replacement_expression>`来引用匹配的括号分隔的子表达式 `\1`, `\2`, ..., `\9`。请注意，CMake 代码中需要两个反斜杠 (`\\1`) 才能通过参数解析获得反斜杠。

#### 正则表达式规范

以下字符在正则表达式中具有特殊含义：

- `^`

  在输入开头匹配

- `$`

  在输入结束时匹配

- `.`

  匹配任何单个字符

- `\<char>`

  匹配由 指定的单个字符`<char>`。使用它来匹配特殊`\.`的正则表达式字符，例如文字`.` 或`\\`文字反斜杠`\`。转义非特殊字符是不必要的，但允许，例如`\a`matches `a`。

- `[ ]`

  匹配括号内的任何字符

- `[^ ]`

  匹配不在括号内的任何字符

- `-`

  在括号内，指定任一侧字符之间的包含范围，例如`[a-f]`要使用括号`[abcdef]` 匹配文字`-`，使其成为第一个或最后一个字符，例如`[+*/-]`匹配基本数学运算符。

- `*`

  匹配前面的模式零次或多次

- `+`

  匹配前面的模式一次或多次

- `?`

  匹配前面的模式零或只匹配一次

- `|`

  匹配两侧的模式`|`

- `()`

  保存匹配的子表达式，可以在操作中引用。`REGEX REPLACE`*3.9 版新功能：*所有与正则表达式相关的命令，包括例如 [`if(MATCHES)`](https://cmake.org/cmake/help/latest/command/if.html#command:if)，将子组匹配保存在变量中 [`CMAKE_MATCH_`](https://cmake.org/cmake/help/latest/variable/CMAKE_MATCH_n.html#variable:CMAKE_MATCH_)为`<n>`0..9。

`*`，`+`并且`?`具有比串联更高的优先级。 `|` 优先级低于串联。这意味着正则表达式`^ab+d$`匹配`abbd`但不匹配`ababd`，正则表达式`^(ab|cd)$`匹配`ab`但不匹配`abd`。

CMake 语言[转义序列](https://cmake.org/cmake/help/latest/manual/cmake-language.7.html#escape-sequences)，例如`\t`, `\r`,`\n`和`\\`可用于构造文字制表符、回车符、换行符和反斜杠（分别）以传入正则表达式。例如：

- 带引号的参数指定匹配任何单个空白字符的正则表达式。`"[ \t\r\n]"`
- 引用的参数`"[/\\]"`指定匹配单个正斜杠`/`或反斜杠的正则表达式`\`。
- 带引号的参数`"[A-Za-z0-9_]"`指定匹配 C 语言环境中任何单个“单词”字符的正则表达式。
- 带引号的参数`"\\(\\a\\+b\\)"`指定一个匹配确切字符串的正则表达式`(a+b)`。每个`\\`都在带引号的参数中被解析为 just `\`，因此正则表达式本身实际上是`\(\a\+\b\)`. 这也可以在[括号参数](https://cmake.org/cmake/help/latest/manual/cmake-language.7.html#bracket-argument)中指定，而不必转义反斜杠，例如`[[\(\a\+\b\)]]`.

### Manipulation

```cmake
string(APPEND <string_variable> [<input>...])
```

*3.4 版中的新功能。*

将所有参数附加`<input>`到字符串。

```cmake
string(PREPEND <string_variable> [<input>...])
```

*3.10 版中的新功能。*

将所有`<input>`参数添加到字符串。

```cmake
string(CONCAT <output_variable> [<input>...])
```

将所有`<input>`参数连接在一起并将结果存储在命名的`<output_variable>`.

```cmake
string(JOIN <glue> <output_variable> [<input>...])
```

*版本 3.12 中的新功能。*

使用字符串将所有`<input>`参数连接在一起`<glue>` ，并将结果存储在命名的`<output_variable>`.

要加入列表的元素，最好`JOIN`使用[`list()`](https://cmake.org/cmake/help/latest/command/list.html#command:list)命令。这允许元素具有像`;`它们一样的特殊字符。

```cmake
string(TOLOWER <string> <output_variable>)
```

转换`<string>`为小字符。

```cmake
string(TOUPPER <string> <output_variable>)
```

转换`<string>`为大写字符。

```cmake
string(LENGTH <string> <output_variable>)
```

以字节为单位存储`<output_variable>`给定字符串的长度。请注意，这意味着如果`<string>`包含多字节字符，则存储的结果`<output_variable>`将*不是*字符数。

```cmake
string(SUBSTRING <string> <begin> <length> <output_variable>)
```

存储在`<output_variable>`给定的子字符串中`<string>`。If `<length>`is 将返回`-1`从 at 开始的字符串的其余部分。`<begin>`

*在 3.2 版更改:*如果`<string>`短于`<length>`则使用字符串的结尾。在这种情况下，以前版本的 CMake 会报告错误。

两者`<begin>`和都以字节为单位，因此如果可能包含多字节字符`<length>`，则必须小心。`<string>`

```cmake
string(STRIP <string> <output_variable>)
```

存储在`<output_variable>`给定的子字符串中，`<string>`删除了前导和尾随空格。

```cmake
string(GENEX_STRIP <string> <output_variable>)
```

*3.1 版中的新功能。*

剥离任何[`generator expressions`](https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html#manual:cmake-generator-expressions(7)) 从输入中提取`<string>`结果并将结果存储在`<output_variable>`.

```cmake
string(REPEAT <string> <count> <output_variable>)
```

*3.15 版中的新功能。*

生成输出字符串作为输入`<string>`重复`<count>`次数。

### Comparison

```cmake
string(COMPARE LESS <string1> <string2> <output_variable>)
string(COMPARE GREATER <string1> <string2> <output_variable>)
string(COMPARE EQUAL <string1> <string2> <output_variable>)
string(COMPARE NOTEQUAL <string1> <string2> <output_variable>)
string(COMPARE LESS_EQUAL <string1> <string2> <output_variable>)
string(COMPARE GREATER_EQUAL <string1> <string2> <output_variable>)
```

比较字符串并将 true 或 false 存储在`<output_variable>`.

*3.7 新版功能：*添加了`LESS_EQUAL`and`GREATER_EQUAL`选项。



### Hashing

```cmake
string(<HASH> <output_variable> <input>)
```

计算`<input>`字符串的加密哈希。支持的`<HASH>`算法名称是：

- `MD5`

  消息摘要算法 5，RFC 1321。

- `SHA1`

  美国安全散列算法 1，RFC 3174。

- `SHA224`

  美国安全散列算法，RFC 4634。

- `SHA256`

  美国安全散列算法，RFC 4634。

- `SHA384`

  美国安全散列算法，RFC 4634。

- `SHA512`

  美国安全散列算法，RFC 4634。

- `SHA3_224`

  凯卡克 SHA-3。

- `SHA3_256`

  凯卡克 SHA-3。

- `SHA3_384`

  凯卡克 SHA-3。

- `SHA3_512`

  凯卡克 SHA-3。

*3.8 新版功能：*添加了`SHA3_*`哈希算法。

### Generation

```cmake
string(ASCII <number> [<number> ...] <output_variable>)
```

将所有数字转换为相应的 ASCII 字符。

```cmake
string(HEX <string> <output_variable>)
```

*3.18 版中的新功能。*

将输入中的每个字节转换`<string>`为其十六进制表示，并将连接的十六进制数字存储在`<output_variable>`. 输出中的字母（`a`通过`f`）是小写的。

```cmake
string(CONFIGURE <string> <output_variable>
       [@ONLY] [ESCAPE_QUOTES])
```

转换一个`<string>`like[`configure_file()`](https://cmake.org/cmake/help/latest/command/configure_file.html#command:configure_file)转换文件。

```cmake
string(MAKE_C_IDENTIFIER <string> <output_variable>)
```

将输入中的每个非字母数字字符转换`<string>`为下划线并将结果存储在`<output_variable>`. 如果 的第一个字符`<string>`是数字，则下划线也将被添加到结果前。

```cmake
string(RANDOM [LENGTH <length>] [ALPHABET <alphabet>]
       [RANDOM_SEED <seed>] <output_variable>)
```

`<length>`返回由给定字符组成的给定随机字符串`<alphabet>`。默认长度为 5 个字符，默认字母为所有数字和大小写字母。如果给定一个整数`RANDOM_SEED`，它的值将用于随机数生成器的种子。

```cmake
string(TIMESTAMP <output_variable> [<format_string>] [UTC])
```

将当前日期和/或时间的字符串表示形式写入`<output_variable>`.

如果命令无法获取时间戳，`<output_variable>` 则将设置为空字符串`""`。

可选`UTC`标志请求当前日期/时间表示为协调世界时 (UTC) 而不是本地时间。

可选的`<format_string>`可能包含以下格式说明符：

- `%%`

  *3.8 版中的新功能。*文字百分号 (%)。

- `%d`

  当前月份的日期 (01-31)。

- `%H`

  24 小时制的小时 (00-23)。

- `%I`

  12 小时制的小时 (01-12)。

- `%j`

  当前年份的日期 (001-366)。

- `%m`

  当年的月份 (01-12)。

- `%b`

  *3.7 版中的新功能。*缩写的月份名称（例如 Oct）。

- `%B`

  *3.10 版中的新功能。*完整的月份名称（例如十月）。

- `%M`

  当前小时的分钟 (00-59)。

- `%s`

  *3.6 版中的新功能。*1970 年 1 月 1 日午夜 (UTC) 以来的秒数（UNIX 时间）。

- `%S`

  当前分钟的第二个。60代表闰秒。(00-60)

- `%f`

  当前秒的微秒 (000000-999999)。

- `%U`

  当前年份的周数 (00-53)。

- `%V`

  *版本 3.22 中的新功能。*当年的 ISO 8601 周数 (01-53)。

- `%w`

  当前一周中的某一天。0 是星期日。(0-6)

- `%a`

  *3.7 版中的新功能。*缩写的工作日名称（例如 Fri）。

- `%A`

  *3.10 版中的新功能。*完整的工作日名称（例如星期五）。

- `%y`

  当前年份的最后两位数字 (00-99)。

- `%Y`

  本年度。

未知的格式说明符将被忽略并按原样复制到输出中。

如果没有给出明确`<format_string>`的，它将默认为：

```cmake
%Y-%m-%dT%H:%M:%S    for local time.
%Y-%m-%dT%H:%M:%SZ   for UTC.
```

*3.8 版新功能：*如果`SOURCE_DATE_EPOCH`设置了环境变量，将使用其值而不是当前时间。有关详细信息，请参阅https://reproducible-builds.org/specs/source-date-epoch/。

```cmake
string(UUID <output_variable> NAMESPACE <namespace> NAME <name>
       TYPE <MD5|SHA1> [UPPER])
```

*3.1 版中的新功能。*

根据 RFC4122 基于`<namespace>` （其本身必须是有效的 UUID）和`<name>`. 哈希算法可以是`MD5`（版本 3 UUID）或 `SHA1`（版本 5 UUID）。UUID 具有`xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx` 每个`x`代表小写十六进制字符的格式。如果需要，可以使用可选`UPPER`标志请求大写表示。

### JSON

*3.19 版中的新功能。*

用于查询 JSON 字符串的功能。

> **笔记** 在以下每个与 JSON 相关的子命令中，如果 `ERROR_VARIABLE`给出了可选参数，则将报告错误， `<error-variable>`并且`<out-var>`将 `<member|index>-[<member|index>...]-NOTFOUND`使用路径元素设置为直到发生错误的点，或者仅`NOTFOUND`在没有相关路径的情况下。如果发生错误但`ERROR_VARIABLE` 选项不存在，则会生成致命错误消息。如果没有发生错误，`<error-variable>`将设置为`NOTFOUND`。

```cmake
string(JSON <out-var> [ERROR_VARIABLE <error-variable>]
       GET <json-string> <member|index> [<member|index> ...])
```

从参数`<json-string>`列表给定的位置获取元素。`<member|index>`数组和对象元素将作为 JSON 字符串返回。布尔元素将返回为`ON`or `OFF`。Null 元素将作为空字符串返回。数字和字符串类型将作为字符串返回。

```cmake
string(JSON <out-var> [ERROR_VARIABLE <error-variable>]
       TYPE <json-string> <member|index> [<member|index> ...])
```

在参数`<json-string>`列表给定的位置获取元素的类型。`<member|index>`将`<out-var>` 设置为`NULL`、`NUMBER`、`STRING`、`BOOLEAN`、 `ARRAY`或之一`OBJECT`。

```cmake
string(JSON <out-var> [ERROR_VARIABLE <error-var>]
       MEMBER <json-string>
       [<member|index> ...] <index>)
```

在参数列表给定的位置获取`<index>`-th 成员的名称。需要对象类型的元素。`<json-string>``<member|index>`

```cmake
string(JSON <out-var> [ERROR_VARIABLE <error-variable>]
       LENGTH <json-string> [<member|index> ...])
```

在参数`<json-string>`列表给定的位置获取元素的长度。`<member|index>`需要数组或对象类型的元素。

```cmake
string(JSON <out-var> [ERROR_VARIABLE <error-variable>]
       REMOVE <json-string> <member|index> [<member|index> ...])
```

从参数`<json-string>`列表给定的位置删除一个元素。`<member|index>`没有移除元素的 JSON 字符串将存储在`<out-var>`.

```cmake
string(JSON <out-var> [ERROR_VARIABLE <error-variable>]
       SET <json-string> <member|index> [<member|index> ...] <value>)
```

在 的参数`<json-string>`列表给定的位置设置一个元素。的内容应该是有效的 JSON。`<member|index>``<value>``<value>`

```cmake
string(JSON <out-var> [ERROR_VARIABLE <error-var>]
       EQUAL <json-string1> <json-string2>)
```

比较由`<json-string1>`和给出的两个 JSON 对象`<json-string2>` 是否相等。`<json-string1>`和的内容`<json-string2>` 应该是有效的 JSON。如果`<out-var>`认为 JSON 对象相等，则将设置为真值，否则设置为假值。



## [set](https://cmake.org/cmake/help/latest/command/set.html)

将普通、缓存或环境变量设置为给定值。有关普通变量和缓存条目的作用域和交互，请参阅[cmake-language(7) 变量](https://cmake.org/cmake/help/latest/manual/cmake-language.7.html#cmake-language-variables) 文档。

指定`<value>...`占位符的此命令的签名需要零个或多个参数。多个参数将作为[分号分隔的列表](https://cmake.org/cmake/help/latest/manual/cmake-language.7.html#cmake-language-lists)连接，以形成要设置的实际变量值。零参数将导致未设置普通变量。见[`unset()`](https://cmake.org/cmake/help/latest/command/unset.html#command:unset)命令显式地取消设置变量。

### 设置正常变量

```cmake
set(<variable> <value>... [PARENT_SCOPE])
```

`<variable>`在当前函数或目录范围内设置给定的值。

如果`PARENT_SCOPE`给出选项，则变量将设置在当前范围之上的范围内。每个新目录或函数都会创建一个新范围。此命令会将变量的值设置到父目录或调用函数（以适用于手头的情况为准）。变量值的先前状态在当前范围内保持不变（例如，如果它之前未定义，它仍然是未定义的，如果它有一个值，它仍然是那个值）。

### 设置缓存条目

```cmake
set(<variable> <value>... CACHE <type> <docstring> [FORCE])
```

设置给定的缓存`<variable>`（缓存条目）。由于缓存条目旨在提供用户可设置的值，因此默认情况下不会覆盖现有的缓存条目。使用`FORCE`选项覆盖现有条目。

`<type>`必须指定为以下之一：

- `BOOL`

  布尔`ON/OFF`值。 [`cmake-gui(1)`](https://cmake.org/cmake/help/latest/manual/cmake-gui.1.html#manual:cmake-gui(1))提供一个复选框。

- `FILEPATH`

  磁盘上文件的路径。 [`cmake-gui(1)`](https://cmake.org/cmake/help/latest/manual/cmake-gui.1.html#manual:cmake-gui(1))提供文件对话框。

- `PATH`

  磁盘上目录的路径。 [`cmake-gui(1)`](https://cmake.org/cmake/help/latest/manual/cmake-gui.1.html#manual:cmake-gui(1))提供文件对话框。

- `STRING`

  一行文字。 [`cmake-gui(1)`](https://cmake.org/cmake/help/latest/manual/cmake-gui.1.html#manual:cmake-gui(1))如果[`STRINGS`](https://cmake.org/cmake/help/latest/prop_cache/STRINGS.html#prop_cache:STRINGS)缓存条目属性已设置。

- `INTERNAL`

  一行文字。 [`cmake-gui(1)`](https://cmake.org/cmake/help/latest/manual/cmake-gui.1.html#manual:cmake-gui(1))不显示内部条目。它们可用于跨运行持久存储变量。使用这种类型意味着`FORCE`.

`<docstring>`必须指定为一行文本，提供用于演示的选项的快速摘要[`cmake-gui(1)`](https://cmake.org/cmake/help/latest/manual/cmake-gui.1.html#manual:cmake-gui(1)) 用户。

如果在调用之前缓存条目不存在或`FORCE` 给出了选项，则缓存条目将设置为给定值。

笔记

 

如果已经存在同名的普通变量，则缓存变量的内容将无法直接访问（请参阅[变量评估规则](https://cmake.org/cmake/help/latest/manual/cmake-language.7.html#cmake-language-variables)）。如果政策[`CMP0126`](https://cmake.org/cmake/help/latest/policy/CMP0126.html#policy:CMP0126)设置为`OLD`，当前范围内的任何普通变量绑定都将被删除。

缓存条目可能在调用之前存在，但如果它是在[`cmake(1)`](https://cmake.org/cmake/help/latest/manual/cmake.1.html#manual:cmake(1))用户通过`-D<var>=<value>`选项在不指定类型的情况下使用命令行。在这种情况下，该`set`命令将添加类型。此外，如果命令行中提供的`<type>`is`PATH`或`FILEPATH` and`<value>`是相对路径，则该`set`命令会将路径视为相对于当前工作目录的相对路径，并将其转换为绝对路径。

### 设置环境变量

```cmake
set(ENV{<variable>} [<value>])
```

设置一个[`Environment Variable`](https://cmake.org/cmake/help/latest/manual/cmake-env-variables.7.html#manual:cmake-env-variables(7)) 到给定的值。后续调用`$ENV{<variable>}`将返回这个新值。

此命令仅影响当前的 CMake 进程，而不影响调用 CMake 的进程，也不影响整个系统环境，也不影响后续构建或测试进程的环境。

如果在之后没有给出参数`ENV{<variable>}`或者`<value>`是一个空字符串，那么这个命令将清除环境变量的任何现有值。

后面的参数`<value>`被忽略。如果发现额外的参数，则会发出作者警告。



## [unset](https://cmake.org/cmake/help/latest/command/unset.html)

取消设置变量、缓存变量或环境变量。

### 取消设置普通变量或缓存条目

```cmake
unset(<variable> [CACHE | PARENT_SCOPE])
```

从当前范围中删除一个普通变量，使其变为未定义。如果`CACHE`存在，则删除缓存变量而不是普通变量。请注意，在评估 表单的[变量引用](https://cmake.org/cmake/help/latest/manual/cmake-language.7.html#variable-references)`${VAR}`时，CMake 首先搜索具有该名称的普通变量。如果不存在这样的正常变量，则 CMake 将搜索具有该名称的缓存条目。因此，取消设置普通变量可以公开以前隐藏的缓存变量。要强制表单的变量引用`${VAR}`返回一个空字符串，请使用，它会清除普通变量但保留它的定义。`set(<variable> "")`

如果`PARENT_SCOPE`存在，则从当前范围上方的范围中删除该变量。在[`set()`](https://cmake.org/cmake/help/latest/command/set.html#command:set)命令以获取更多详细信息。

### 取消设置环境变量

```cmake
unset(ENV{<variable>})
```

从`<variable>`当前可用的 [`Environment Variables`](https://cmake.org/cmake/help/latest/manual/cmake-env-variables.7.html#manual:cmake-env-variables(7)). 后续调用`$ENV{<variable>}`将返回空字符串。

此命令仅影响当前的 CMake 进程，而不影响调用 CMake 的进程，也不影响整个系统环境，也不影响后续构建或测试进程的环境。



## [set_directory_properties](https://cmake.org/cmake/help/latest/command/set_directory_properties.html)

设置当前目录和子目录的属性。

```cmake
set_directory_properties(PROPERTIES prop1 value1 [prop2 value2] ...)
```

以键值对的形式设置当前目录及其子目录的属性。

另见[`set_property(DIRECTORY)`](https://cmake.org/cmake/help/latest/command/set_property.html#command:set_property)命令。

有关CMake 已知的属性列表及其有关每个属性行为的单独文档，请参阅[目录上的属性。](https://cmake.org/cmake/help/latest/manual/cmake-properties.7.html#directory-properties)



## [set_property](https://cmake.org/cmake/help/latest/command/set_property.html)

在给定范围内设置命名属性。

```cmake
set_property(<GLOBAL                      |
              DIRECTORY [<dir>]           |
              TARGET    [<target1> ...]   |
              SOURCE    [<src1> ...]
                        [DIRECTORY <dirs> ...]
                        [TARGET_DIRECTORY <targets> ...] |
              INSTALL   [<file1> ...]     |
              TEST      [<test1> ...]     |
              CACHE     [<entry1> ...]    >
             [APPEND] [APPEND_STRING]
             PROPERTY <name> [<value1> ...])
```

在范围的零个或多个对象上设置一个属性。

第一个参数确定设置属性的范围。它必须是以下之一：

- `GLOBAL`

  范围是唯一的，不接受名称。

- `DIRECTORY`

  范围默认为当前目录，但其他目录（已由 CMake 处理）可以通过完整路径或相对路径命名。相对路径被视为相对于当前源目录。另见[`set_directory_properties()`](https://cmake.org/cmake/help/latest/command/set_directory_properties.html#command:set_directory_properties)命令。

  *3.19 新版功能：*`<dir>`可能引用二进制目录。

- `TARGET`

  范围可以命名零个或多个现有目标。另见[`set_target_properties()`](https://cmake.org/cmake/help/latest/command/set_target_properties.html#command:set_target_properties)命令。

- `SOURCE`

  范围可以命名零个或多个源文件。默认情况下，源文件属性仅对添加到同一目录 ( `CMakeLists.txt`) 中的目标可见。

  *3.18 版中的新功能：*可以使用以下子选项之一或两者在其他目录范围中设置可见性：

  `DIRECTORY <dirs>...`

  ​		源文件属性将在每个`<dirs>` 目录的范围内设置。CMake 必须已经知道这些目录中的每一个，或者通过调用添加它们 [`add_subdirectory()`](https://cmake.org/cmake/help/latest/command/add_subdirectory.html#command:add_subdirectory)或者它是顶级源目录。相对路径被视为相对于当前源目录。*3.19 新版功能：*`<dirs>`可能引用二进制目录。

  `TARGET_DIRECTORY <targets>...`

  ​		源文件属性将在`<targets>`创建任何指定文件的每个目录范围内设置（`<targets>` 因此必须已经存在）。另见[`set_source_files_properties()`](https://cmake.org/cmake/help/latest/command/set_source_files_properties.html#command:set_source_files_properties)命令。

- `INSTALL`

  *3.1 版中的新功能。*

  范围可以命名零个或多个已安装的文件路径。这些可供 CPack 使用以影响部署。

  属性键和值都可以使用生成器表达式。特定属性可能适用于已安装的文件和/或目录。

  路径组件必须用正斜杠分隔，必须标准化并且区分大小写。

  要使用相对路径引用安装前缀本身，请使用`.`.

  当前安装的文件属性仅针对给定路径与安装前缀相关的 WIX 生成器定义。

- `TEST`

  范围可以命名零个或多个现有测试。另见[`set_tests_properties()`](https://cmake.org/cmake/help/latest/command/set_tests_properties.html#command:set_tests_properties)命令。

  可以使用指定测试属性值 [`generator expressions`](https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html#manual:cmake-generator-expressions(7)) 对于由[`add_test(NAME)`](https://cmake.org/cmake/help/latest/command/add_test.html#command:add_test)签名。

- `CACHE`

  范围必须命名零个或多个缓存现有条目。

required`PROPERTY`选项后面紧跟要设置的属性的名称。其余参数用于以分号分隔列表的形式组成属性值。

如果`APPEND`给出该选项，则列表将附加到任何现有的属性值（除了空值被忽略且不附加）。如果`APPEND_STRING`给出该选项，则字符串将作为字符串附加到任何现有属性值，即它会导致更长的字符串而不是字符串列表。当使用`APPEND`或 `APPEND_STRING`与定义为支持`INHERITED` 行为的属性一起使用时（请参阅[`define_property()`](https://cmake.org/cmake/help/latest/command/define_property.html#command:define_property))，在找到要附加到的初始值时不会发生继承。如果该属性尚未直接设置在指定范围内，则该命令将表现得好像 `APPEND`或`APPEND_STRING`没有给出一样。



## [list](https://cmake.org/cmake/help/latest/command/list.html)

列出操作。

### 简明

```cmake
Reading
  list(LENGTH <list> <out-var>)
  list(GET <list> <element index> [<index> ...] <out-var>)
  list(JOIN <list> <glue> <out-var>)
  list(SUBLIST <list> <begin> <length> <out-var>)

Search
  list(FIND <list> <value> <out-var>)

Modification
  list(APPEND <list> [<element>...])
  list(FILTER <list> {INCLUDE | EXCLUDE} REGEX <regex>)
  list(INSERT <list> <index> [<element>...])
  list(POP_BACK <list> [<out-var>...])
  list(POP_FRONT <list> [<out-var>...])
  list(PREPEND <list> [<element>...])
  list(REMOVE_ITEM <list> <value>...)
  list(REMOVE_AT <list> <index>...)
  list(REMOVE_DUPLICATES <list>)
  list(TRANSFORM <list> <ACTION> [...])

Ordering
  list(REVERSE <list>)
  list(SORT <list> [...])
```

### 简介

列表子命令`APPEND`, `INSERT`, `FILTER`, `PREPEND`, `POP_BACK`, `POP_FRONT`, `REMOVE_AT`, `REMOVE_ITEM`, `REMOVE_DUPLICATES`和可以在当前 CMake 变量范围内为列表创建新值`REVERSE`。`SORT`类似于[`set()`](https://cmake.org/cmake/help/latest/command/set.html#command:set)命令，LIST 命令在当前作用域中创建新的变量值，即使列表本身实际上是在父作用域中定义的。要向上传播这些操作的结果，请使用 [`set()`](https://cmake.org/cmake/help/latest/command/set.html#command:set)与`PARENT_SCOPE`,[`set()`](https://cmake.org/cmake/help/latest/command/set.html#command:set)或其他 一些价值传播方式。`CACHE INTERNAL`

>  **笔记：** cmake 中的列表是一`;`组单独的字符串。要创建列表，可以使用 set 命令。例如， 创建一个带有 的列表，并创建一个包含一项的字符串或列表。（注意宏参数不是变量，因此不能在 LIST 命令中使用。）`set(var a b c d e)``a;b;c;d;e``set(var "a b c d e")`

> **笔记：**指定索引值时，如果为 0 或更大，则从列表的开头开始索引，0 表示第一个列表元素。如果为 -1 或更小，则从列表末尾开始索引，其中 -1 表示最后一个列表元素。使用负索引计数时要小心：它们不是从 0 开始的。-0 相当于 0，即第一个列表元素。`<element index>``<element index>`

### Reading

```cmake
list(LENGTH <list> <output variable>)
```

返回列表的长度。

```cmake
list(GET <list> <element index> [<element index> ...] <output variable>)
```

返回列表中由索引指定的元素列表。

```cmake
list(JOIN <list> <glue> <output variable>)
```

*版本 3.12 中的新功能。*

返回使用粘合字符串连接所有列表元素的字符串。要连接不属于列表的多个字符串，请使用`JOIN`运算符 from[`string()`](https://cmake.org/cmake/help/latest/command/string.html#command:string)命令。

```cmake
list(SUBLIST <list> <begin> <length> <output variable>)
```

*版本 3.12 中的新功能。*

返回给定列表的子列表。如果`<length>`为 0，将返回一个空列表。如果`<length>`为 -1 或列表小于，则将返回`<begin>+<length>`列表中从 开始的剩余元素。`<begin>`

### Search

```cmake
list(FIND <list> <value> <output variable>)
```

返回列表中指定元素的索引，如果未找到则返回 -1。

### Modification

```cmake
list(APPEND <list> [<element> ...])
```

将元素附加到列表中。如果当前作用域中不存在名为`<list>`的变量，则其值被视为空，并且元素将附加到该空列表中。

```cmake
list(FILTER <list> <INCLUDE|EXCLUDE> REGEX <regular_expression>)
```

*3.6 版中的新功能。*

从列表中包含或删除与模式模式匹配的项目。在`REGEX`模式下，项目将与给定的正则表达式匹配。

有关正则表达式的更多信息，请查看 [string(REGEX)](https://cmake.org/cmake/help/latest/command/string.html#regex-specification)。

```cmake
list(INSERT <list> <element_index> <element> [<element> ...])
```

将元素插入到指定索引的列表中。指定超出范围的索引是错误的。有效索引为 0 到N ，其中N是列表的长度（含）。空列表的长度为 0。如果`<list>`当前范围内不存在名为的变量，则其值被视为空，并且元素将插入该空列表中。

```cmake
list(POP_BACK <list> [<out-var>...])
```

*3.15 版中的新功能。*

如果没有给出变量名，则只删除一个元素。否则，在提供N个变量名称的情况下，将最后N个元素的值分配给给定变量，然后从 `<list>`.

```cmake
list(POP_FRONT <list> [<out-var>...])
```

*3.15 版中的新功能。*

如果没有给出变量名，则只删除一个元素。否则，在提供N个变量名称的情况下，将前N个元素的值分配给给定变量，然后从 `<list>`.

```cmake
list(PREPEND <list> [<element> ...])
```

*3.15 版中的新功能。*

将元素插入到列表中的第 0 位。如果当前作用域中不存在名为 `<list>`的变量，则其值被视为空，并且元素将附加到该空列表中。

```cmake
list(REMOVE_ITEM <list> <value> [<value> ...])
```

从列表中删除给定项目的所有实例。

```cmake
list(REMOVE_AT <list> <index> [<index> ...])
```

从列表中删除给定索引处的项目。

```cmake
list(REMOVE_DUPLICATES <list>)
```

删除列表中的重复项。项目的相对顺序被保留，但如果遇到重复项，则仅保留第一个实例。

```cmake
list(TRANSFORM <list> <ACTION> [<SELECTOR>]
                      [OUTPUT_VARIABLE <output variable>])
```

*版本 3.12 中的新功能。*

通过对所有或通过指定 a `<SELECTOR>`对列表的选定元素应用操作来转换列表，将结果存储在原地或指定的输出变量中。

> **笔记：**该`TRANSFORM`子命令不会更改列表中的元素数量。如果`<SELECTOR>`指定了 a，则只会更改部分元素，其他元素将保持与转换前相同。

`<ACTION>`指定要应用于列表元素的操作。这些动作与子命令具有完全相同的语义 [`string()`](https://cmake.org/cmake/help/latest/command/string.html#command:string)命令。 `<ACTION>`必须是以下之一：

`APPEND`, `PREPEND`: 将指定的值附加到列表的每个元素之前。

> ```cmake
> list(TRANSFORM <list> <APPEND|PREPEND> <value> ...)
> ```

`TOUPPER`, `TOLOWER`: 将列表的每个元素转换为大写、小写字符。

> ```cmake
> list(TRANSFORM <list> <TOLOWER|TOUPPER> ...)
> ```

`STRIP`：从列表的每个元素中删除前导和尾随空格。

> ```cmake
> list(TRANSFORM <list> STRIP ...)
> ```

`GENEX_STRIP`: 剥离任何 [`generator expressions`](https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html#manual:cmake-generator-expressions(7))从列表的每个元素。

> ```cmake
> list(TRANSFORM <list> GENEX_STRIP ...)
> ```

`REPLACE`: 尽可能多地匹配正则表达式，并用替换表达式替换列表中每个元素的匹配项（语义与from`REGEX REPLACE`[`string()`](https://cmake.org/cmake/help/latest/command/string.html#command:string)命令）。

> ```cmake
> list(TRANSFORM <list> REPLACE <regular_expression>
>                            <replace_expression> ...)
> ```

`<SELECTOR>`确定列表的哪些元素将被转换。一次只能指定一种类型的选择器。给出时， `<SELECTOR>`必须是以下之一：

`AT`：指定索引列表。

> ```cmake
> list(TRANSFORM <list> <ACTION> AT <index> [<index> ...] ...)
> ```

`FOR`: 指定一个范围，可选地，用于迭代该范围的增量。

> ```cmake
> list(TRANSFORM <list> <ACTION> FOR <start> <stop> [<step>] ...)
> ```

`REGEX`: 指定正则表达式。只有匹配正则表达式的元素才会被转换。

> ```cmake
> list(TRANSFORM <list> <ACTION> REGEX <regular_expression> ...)
> ```

### Ordering

```cmake
list(REVERSE <list>)
```

就地反转列表的内容。

```cmake
list(SORT <list> [COMPARE <compare>] [CASE <case>] [ORDER <order>])
```

按字母顺序对列表进行就地排序。

*3.13 新版功能：*添加了`COMPARE`、`CASE`和`ORDER`选项。

*3.18 版中的新功能：*添加了该选项。`COMPARE NATURAL`

使用`COMPARE`关键字选择排序的比较方法。该`<compare>`选项应该是以下之一：

- `STRING`：按字母顺序对字符串列表进行排序。`COMPARE`如果未给出该选项，这是默认行为。
- `FILE_BASENAME`：按文件的基本名称对文件的路径名列表进行排序。
- `NATURAL`：使用自然顺序对字符串列表进行排序（参见`strverscmp(3)`手册），即将连续数字作为整数进行比较。例如：以下列表10.0 1.1 2.1 8.0 2.0 3.1如果 选择了比较，则将 排序为1.1 2.0 2.1 3.1 8.0 10.0 ，与比较将排序为1.1 10.0 2.0 2.1 3.1 8.0。`NATURAL``STRING`

使用`CASE`关键字选择区分大小写或不区分大小写的排序模式。该`<case>`选项应该是以下之一：

- `SENSITIVE`：列表项以区分大小写的方式排序。`CASE`如果未给出该选项，这是默认行为。
- `INSENSITIVE`：列表项不区分大小写。未指定仅大写/小写不同的项目的顺序。

要控制排序顺序，`ORDER`可以给出关键字。该`<order>`选项应该是以下之一：

- `ASCENDING`：按升序对列表进行排序。`ORDER`这是未给出选项时的默认行为。
- `DESCENDING`：按降序对列表进行排序。

## [message](https://cmake.org/cmake/help/latest/command/message.html)

记录一条消息。

### 简明

```cmake
一般信息
  message([<mode>] "消息文本" ...)

报告检查
  message(<checkState> "message text" ...)
```

### 一般信息

```cmake
message([<mode>] "message text" ...)
```

在日志中记录指定的消息文本。如果给出了多个消息字符串，则将它们连接成一条消息，字符串之间没有分隔符。

optional`<mode>`关键字确定消息的类型，这会影响消息的处理方式：

- `FATAL_ERROR`

  CMake 错误，停止处理和生成。这[`cmake(1)`](https://cmake.org/cmake/help/latest/manual/cmake.1.html#manual:cmake(1))可执行文件将返回非零 [退出代码](https://cmake.org/cmake/help/latest/manual/cmake.1.html#cmake-exit-code)。

- `SEND_ERROR`

  CMake 错误，继续处理，但跳过生成。

- `WARNING`

  CMake 警告，继续处理。

- `AUTHOR_WARNING`

  CMake 警告（开发），继续处理。

- `DEPRECATION`

  CMake 弃用错误或警告（如果变量） [`CMAKE_ERROR_DEPRECATED`](https://cmake.org/cmake/help/latest/variable/CMAKE_ERROR_DEPRECATED.html#variable:CMAKE_ERROR_DEPRECATED)或者[`CMAKE_WARN_DEPRECATED`](https://cmake.org/cmake/help/latest/variable/CMAKE_WARN_DEPRECATED.html#variable:CMAKE_WARN_DEPRECATED) 分别启用，否则没有消息。

- （无）或`NOTICE`

  打印到 stderr 以吸引用户注意的重要消息。

- `STATUS`

  项目用户可能感兴趣的主要有趣信息。理想情况下，这些信息应该简明扼要，不超过一行，但仍能提供信息。

- `VERBOSE`

  针对项目用户的详细信息消息。这些消息应该提供在大多数情况下不会感兴趣的额外细节，但是当他们想要更深入地了解正在发生的事情时，这可能对那些构建项目的人有用。

- `DEBUG`

  详细的信息消息旨在为项目本身的开发人员而不是只想构建它的用户提供。这些消息通常不会对构建项目的其他用户感兴趣，并且通常与内部实施细节密切相关。

- `TRACE`

  具有非常低级实现细节的细粒度消息。使用此日志级别的消息通常只是临时的，预计会在发布项目、打包文件等之前被删除。

*3.15 新版功能：*添加了`NOTICE`、`VERBOSE`、`DEBUG`和`TRACE`关卡。

CMake 命令行工具在标准输出上显示消息，消息前面有两个连字符和一个空格`STATUS`。`TRACE`所有其他消息类型都发送到 stderr，并且不带有连字符前缀。这 [`CMake GUI`](https://cmake.org/cmake/help/latest/manual/cmake-gui.1.html#manual:cmake-gui(1))在其日志区域中显示所有消息。这[`curses interface`](https://cmake.org/cmake/help/latest/manual/ccmake.1.html#manual:ccmake(1))`STATUS`在状态行上一次显示`TRACE` 一条消息，在交互式弹出框中显示其他消息。这些工具中的每一个的`--log-level`命令行选项可用于控制将显示哪些消息。

*3.17 版中*的新功能：要使日志级别在 CMake 运行之间保持不变， [`CMAKE_MESSAGE_LOG_LEVEL`](https://cmake.org/cmake/help/latest/variable/CMAKE_MESSAGE_LOG_LEVEL.html#variable:CMAKE_MESSAGE_LOG_LEVEL)可以改为设置变量。请注意，命令行选项优先于缓存变量。

*3.16 版新功能：*日志级别`NOTICE`及以下级别的消息将在每一行前面加上[`CMAKE_MESSAGE_INDENT`](https://cmake.org/cmake/help/latest/variable/CMAKE_MESSAGE_INDENT.html#variable:CMAKE_MESSAGE_INDENT)变量（通过连接其列表项转换为单个字符串）。对于消息`STATUS`，`TRACE` 此缩进内容将插入连字符之后。

*3.17 版中的新功能：*日志级别`NOTICE`及以下级别的消息也可以在每一行前面加上表单的上下文`[some.context.example]`。方括号之间的内容是通过转换得到的[`CMAKE_MESSAGE_CONTEXT`](https://cmake.org/cmake/help/latest/variable/CMAKE_MESSAGE_CONTEXT.html#variable:CMAKE_MESSAGE_CONTEXT) 列表变量到一个点分隔的字符串。消息上下文将始终出现在任何缩进内容之前，但在任何自动添加的前导连字符之后。默认情况下，消息上下文不显示，它必须通过给出显式启用[`cmake`](https://cmake.org/cmake/help/latest/manual/cmake.1.html#manual:cmake(1)) `--log-context` 命令行选项或通过设置[`CMAKE_MESSAGE_CONTEXT_SHOW`](https://cmake.org/cmake/help/latest/variable/CMAKE_MESSAGE_CONTEXT_SHOW.html#variable:CMAKE_MESSAGE_CONTEXT_SHOW) 变量为真。见[`CMAKE_MESSAGE_CONTEXT`](https://cmake.org/cmake/help/latest/variable/CMAKE_MESSAGE_CONTEXT.html#variable:CMAKE_MESSAGE_CONTEXT)使用示例的文档。

CMake 警告和错误消息文本使用简单的标记语言显示。非缩进文本以换行符分隔的换行段落格式化。缩进的文本被认为是预先格式化的。

### 报告检查

*版本 3.17 中的新功能。*

CMake 输出中的一个常见模式是指示某种检查开始的消息，然后是另一条报告该检查结果的消息。例如：

```cmake
message(STATUS "Looking for someheader.h")
#... do the checks, set checkSuccess with the result
if(checkSuccess)
  message(STATUS "Looking for someheader.h - found")
else()
  message(STATUS "Looking for someheader.h - not found")
endif()
```

这可以使用命令的`CHECK_...` 关键字形式更加健壮和方便地表达`message()`：

```cmake
message(<checkState> "message" ...)
```

where`<checkState>`必须是以下之一：

> - `CHECK_START`
>
>   记录关于将要执行的检查的简明消息。
>
> - `CHECK_PASS`
>
>   记录检查的成功结果。
>
> - `CHECK_FAIL`
>
>   记录不成功的检查结果。

记录检查结果时，该命令会从最近开始但尚未报告结果的检查中重复消息，然后是一些分隔符，然后是在 `CHECK_PASS`or`CHECK_FAIL`关键字之后提供的消息文本。检查消息总是在`STATUS`日志级别报告。

检查可能是嵌套的，并且每个都`CHECK_START`应该有一个匹配的`CHECK_PASS`or `CHECK_FAIL`。这[`CMAKE_MESSAGE_INDENT`](https://cmake.org/cmake/help/latest/variable/CMAKE_MESSAGE_INDENT.html#variable:CMAKE_MESSAGE_INDENT)如果需要，变量也可用于向嵌套检查添加缩进。例如：

```cmake
message(CHECK_START "Finding my things")
list(APPEND CMAKE_MESSAGE_INDENT "  ")
unset(missingComponents)

message(CHECK_START "Finding partA")
# ... do check, assume we find A
message(CHECK_PASS "found")

message(CHECK_START "Finding partB")
# ... do check, assume we don't find B
list(APPEND missingComponents B)
message(CHECK_FAIL "not found")

list(POP_BACK CMAKE_MESSAGE_INDENT)
if(missingComponents)
  message(CHECK_FAIL "missing components: ${missingComponents}")
else()
  message(CHECK_PASS "all components found")
endif()
```

上面的输出将如下所示：

```cmake
-- Finding my things
--   Finding partA
--   Finding partA - found
--   Finding partB
--   Finding partB - not found
-- Finding my things - missing components: B
```



## [file](https://cmake.org/cmake/help/latest/command/file.html)

文件操作命令。

此命令专用于需要访问文件系统的文件和路径操作。

对于其他路径操作，仅处理句法方面，看看 [`cmake_path()`](https://cmake.org/cmake/help/latest/command/cmake_path.html#command:cmake_path)命令。

笔记

 

子命令[RELATIVE_PATH](https://cmake.org/cmake/help/latest/command/file.html#relative-path)、[TO_CMAKE_PATH](https://cmake.org/cmake/help/latest/command/file.html#to-cmake-path)和[TO_NATIVE_PATH](https://cmake.org/cmake/help/latest/command/file.html#to-native-path)已分别 被子命令[RELATIVE_PATH](https://cmake.org/cmake/help/latest/command/cmake_path.html#cmake-path-relative-path)、 [CONVERT ... TO_CMAKE_PATH_LIST](https://cmake.org/cmake/help/latest/command/cmake_path.html#cmake-path-to-cmake-path-list)和 [CONVERT ... TO_NATIVE_PATH_LIST](https://cmake.org/cmake/help/latest/command/cmake_path.html#cmake-path-to-native-path-list)取代 [`cmake_path()`](https://cmake.org/cmake/help/latest/command/cmake_path.html#command:cmake_path)命令。

### 简明

```cmake
Reading
  file(READ <filename> <out-var> [...])
  file(STRINGS <filename> <out-var> [...])
  file(<HASH> <filename> <out-var>)
  file(TIMESTAMP <filename> <out-var> [...])
  file(GET_RUNTIME_DEPENDENCIES [...])

Writing
  file({WRITE | APPEND} <filename> <content>...)
  file({TOUCH | TOUCH_NOCREATE} [<file>...])
  file(GENERATE OUTPUT <output-file> [...])
  file(CONFIGURE OUTPUT <output-file> CONTENT <content> [...])

Filesystem
  file({GLOB | GLOB_RECURSE} <out-var> [...] [<globbing-expr>...])
  file(MAKE_DIRECTORY [<dir>...])
  file({REMOVE | REMOVE_RECURSE } [<files>...])
  file(RENAME <oldname> <newname> [...])
  file(COPY_FILE <oldname> <newname> [...])
  file({COPY | INSTALL} <file>... DESTINATION <dir> [...])
  file(SIZE <filename> <out-var>)
  file(READ_SYMLINK <linkname> <out-var>)
  file(CREATE_LINK <original> <linkname> [...])
  file(CHMOD <files>... <directories>... PERMISSIONS <permissions>... [...])
  file(CHMOD_RECURSE <files>... <directories>... PERMISSIONS <permissions>... [...])

Path Conversion
  file(REAL_PATH <path> <out-var> [BASE_DIRECTORY <dir>] [EXPAND_TILDE])
  file(RELATIVE_PATH <out-var> <directory> <file>)
  file({TO_CMAKE_PATH | TO_NATIVE_PATH} <path> <out-var>)

Transfer
  file(DOWNLOAD <url> [<file>] [...])
  file(UPLOAD <file> <url> [...])

Locking
  file(LOCK <path> [...])

Archiving
  file(ARCHIVE_CREATE OUTPUT <archive> PATHS <paths>... [...])
  file(ARCHIVE_EXTRACT INPUT <archive> [...])
```

### Reading

```cmake
file(READ <filename> <variable>
     [OFFSET <offset>] [LIMIT <max-in>] [HEX])
```

从名为的文件中读取内容`<filename>`并将其存储在 `<variable>`. 可选择从给定的开始`<offset>`并最多读取`<max-in>`字节。该`HEX`选项将数据转换为十六进制表示（对二进制数据有用）。如果 `HEX`指定了该选项，则输出中的字母 ( `a`through `f`) 为小写。

```cmake
file(STRINGS <filename> <variable> [<options>...])
```

解析 ASCII 字符串列表`<filename>`并将其存储在 `<variable>`. 文件中的二进制数据被忽略。回车 ( `\r`, CR) 字符被忽略。选项包括：

- `LENGTH_MAXIMUM <max-len>`

  只考虑最多给定长度的字符串。

- `LENGTH_MINIMUM <min-len>`

  只考虑至少给定长度的字符串。

- `LIMIT_COUNT <max-num>`

  限制要提取的不同字符串的数量。

- `LIMIT_INPUT <max-in>`

  限制从文件中读取的输入字节数。

- `LIMIT_OUTPUT <max-out>`

  限制要存储在`<variable>`.

- `NEWLINE_CONSUME`

  将换行符 ( `\n`, LF) 视为字符串内容的一部分，而不是在它们处终止。

- `NO_HEX_CONVERSION`

  除非给出此选项，否则 Intel Hex 和 Motorola S-record 文件在读取时会自动转换为二进制文件。

- `REGEX <regex>`

  仅考虑与给定正则表达式匹配的字符串，如[string(REGEX)](https://cmake.org/cmake/help/latest/command/string.html#regex-specification)中所述。

- `ENCODING <encoding-type>`

  *3.1 版中的新功能。*考虑给定编码的字符串。目前支持的编码有： `UTF-8`, `UTF-16LE`, `UTF-16BE`, `UTF-32LE`, `UTF-32BE`. 如果`ENCODING`未提供该选项并且文件具有字节顺序标记，则该`ENCODING`选项将默认尊重字节顺序标记。*3.2 版新功能：*添加了`UTF-16LE`, `UTF-16BE`, `UTF-32LE`,`UTF-32BE`编码。

例如，代码

```cmake
file(STRINGS myfile.txt myfile)
```

在变量`myfile`中存储一个列表，其中每个项目都是输入文件中的一行。

```cmake
file(<HASH> <filename> <variable>)
```

计算内容的加密哈希`<filename>`并将其存储在`<variable>`. 支持的`<HASH>`算法名称是由[string()](https://cmake.org/cmake/help/latest/command/string.html#supported-hash-algorithms) 命令列出的名称。

```cmake
file(TIMESTAMP <filename> <variable> [<format>] [UTC])
```

计算修改时间的字符串表示`<filename>` 并将其存储在`<variable>`. 如果命令无法获取时间戳变量，则将设置为空字符串（“”）。

见[`string(TIMESTAMP)`](https://cmake.org/cmake/help/latest/command/string.html#command:string)用于记录`<format>`和`UTC`选项的命令。

```cmake
file(GET_RUNTIME_DEPENDENCIES
  [RESOLVED_DEPENDENCIES_VAR <deps_var>]
  [UNRESOLVED_DEPENDENCIES_VAR <unresolved_deps_var>]
  [CONFLICTING_DEPENDENCIES_PREFIX <conflicting_deps_prefix>]
  [EXECUTABLES [<executable_files>...]]
  [LIBRARIES [<library_files>...]]
  [MODULES [<module_files>...]]
  [DIRECTORIES [<directories>...]]
  [BUNDLE_EXECUTABLE <bundle_executable_file>]
  [PRE_INCLUDE_REGEXES [<regexes>...]]
  [PRE_EXCLUDE_REGEXES [<regexes>...]]
  [POST_INCLUDE_REGEXES [<regexes>...]]
  [POST_EXCLUDE_REGEXES [<regexes>...]]
  [POST_INCLUDE_FILES [<files>...]]
  [POST_EXCLUDE_FILES [<files>...]]
  )
```

*3.16 版中的新功能。*

递归获取给定文件所依赖的库列表。

请注意，此子命令不适用于项目模式。它旨在在安装时使用，无论是从由 [`install(RUNTIME_DEPENDENCY_SET)`](https://cmake.org/cmake/help/latest/command/install.html#command:install)命令，或通过项目提供的代码[`install(CODE)`](https://cmake.org/cmake/help/latest/command/install.html#command:install)或者[`install(SCRIPT)`](https://cmake.org/cmake/help/latest/command/install.html#command:install). 例如：

```cmake
install(CODE [[
  file(GET_RUNTIME_DEPENDENCIES
    # ...
    )
  ]])
```

论据如下：

- `RESOLVED_DEPENDENCIES_VAR <deps_var>`

  存储已解析依赖项列表的变量的名称。

- `UNRESOLVED_DEPENDENCIES_VAR <unresolved_deps_var>`

  存储未解析依赖项列表的变量的名称。如果未指定此变量，并且存在任何未解决的依赖关系，则会发出错误。

- `CONFLICTING_DEPENDENCIES_PREFIX <conflicting_deps_prefix>`

  存储冲突依赖信息的变量前缀。如果在两个不同的目录中找到两个具有相同名称的文件，则依赖关系会发生冲突。冲突的文件名列表存储在 `<conflicting_deps_prefix>_FILENAMES`. 对于每个文件名，为该文件名找到的路径列表存储在 `<conflicting_deps_prefix>_<filename>`.

- `EXECUTABLES <executable_files>`

  要读取的依赖项的可执行文件列表。这些是通常使用创建的可执行文件[`add_executable()`](https://cmake.org/cmake/help/latest/command/add_executable.html#command:add_executable)，但它们不必由 CMake 创建。在 Apple 平台上，这些文件的路径决定了`@executable_path`递归解析库时的值。在此处指定任何类型的库（`STATIC`、`MODULE`或`SHARED`）将导致未定义的行为。

- `LIBRARIES <library_files>`

  要读取的依赖项的库文件列表。这些是通常使用创建的库[`add_library(SHARED)`](https://cmake.org/cmake/help/latest/command/add_library.html#command:add_library)，但它们不必由 CMake 创建。在此处指定`STATIC`库、`MODULE` 库或可执行文件将导致未定义的行为。

- `MODULES <module_files>`

  要读取依赖项的可加载模块文件列表。这些是通常使用创建的模块[`add_library(MODULE)`](https://cmake.org/cmake/help/latest/command/add_library.html#command:add_library)，但它们不必由 CMake 创建。它们通常通过 `dlopen()`在运行时调用而不是在链接时与. 在此处指定库、库或可执行文件将导致未定义的行为。`ld -l``STATIC``SHARED`

- `DIRECTORIES <directories>`

  用于搜索依赖项的其他目录列表。在 Linux 平台上，如果在任何其他常用路径中都找不到依赖项，则会搜索这些目录。如果在这样的目录中找到它，则会发出警告，因为这意味着该文件不完整（它没有列出包含其依赖项的所有目录）。在 Windows 平台上，如果在任何其他搜索路径中都找不到依赖项，则会搜索这些目录，但不会发出警告，因为搜索其他路径是 Windows 依赖项解析的正常部分。在 Apple 平台上，此参数无效。

- `BUNDLE_EXECUTABLE <bundle_executable_file>`

  可执行文件在解析库时被视为“捆绑可执行文件”。在 Apple 平台上，此参数确定何时递归解析和文件的`@executable_path` 库的值。它对文件没有影响。在其他平台上，它没有效果。这通常（但不总是）是 参数中指定包的“主要”可执行文件的可执行文件之一。`LIBRARIES``MODULES``EXECUTABLES``EXECUTABLES`

以下参数指定用于包含或排除要解析的库的过滤器。有关它们如何工作的完整描述，请参见下文。

- `PRE_INCLUDE_REGEXES <regexes>`

  预包含正则表达式的列表，通过这些正则表达式过滤尚未解决的依赖项的名称。

- `PRE_EXCLUDE_REGEXES <regexes>`

  用于过滤尚未解决的依赖项名称的预排除正则表达式列表。

- `POST_INCLUDE_REGEXES <regexes>`

  post-include 正则表达式列表，通过这些正则表达式过滤已解析依赖项的名称。

- `POST_EXCLUDE_REGEXES <regexes>`

  用于过滤已解析依赖项名称的排除后正则表达式列表。

- `POST_INCLUDE_FILES <files>`

  *3.21 版中的新功能。*后包含文件名列表，通过这些文件名过滤已解析依赖项的名称。尝试匹配这些文件名时会解析符号链接。

- `POST_EXCLUDE_FILES <files>`

  *3.21 版中的新功能。*用于过滤已解析依赖项名称的排除后文件名列表。尝试匹配这些文件名时会解析符号链接。

这些参数可用于在解析依赖项时排除不需要的系统库，或包含来自特定目录的库。过滤工作如下：

1. 如果尚未解析的依赖项与 中的任何一个匹配 `PRE_INCLUDE_REGEXES`，则跳过第 2 步和第 3 步，并且依赖项解析进行到第 4 步。
2. 如果尚未解决的依赖项与 中的任何一个匹配，则该依赖项的 `PRE_EXCLUDE_REGEXES`依赖项解析将停止。
3. 否则，依赖解析继续进行。
4. `file(GET_RUNTIME_DEPENDENCIES)`根据平台的链接规则搜索依赖（见下文）。
5. 如果找到依赖项，并且其完整路径与 `POST_INCLUDE_REGEXES`or之一匹配`POST_INCLUDE_FILES`，则将完整路径添加到已解析的依赖项中，并`file(GET_RUNTIME_DEPENDENCIES)` 递归解析该库自己的依赖项。否则，解析将进行到步骤 6。
6. 如果找到了依赖项，但其完整路径与 `POST_EXCLUDE_REGEXES`or之一匹配`POST_EXCLUDE_FILES`，则不会将其添加到已解析的依赖项中，并且该依赖项的依赖项解析停止。
7. 如果找到依赖项，并且其完整路径不匹配 `POST_INCLUDE_REGEXES`、`POST_INCLUDE_FILES`、`POST_EXCLUDE_REGEXES`或`POST_EXCLUDE_FILES`，则将完整路径添加到已解析的依赖项中，并`file(GET_RUNTIME_DEPENDENCIES)` 递归解析该库自己的依赖项。

不同的平台对于如何解决依赖关系有不同的规则。这些细节在此处进行了描述。

在 Linux 平台上，库解析的工作方式如下：

1. 如果依赖文件没有任何`RUNPATH`条目，并且该库以该顺序存在于依赖文件的`RPATH`条目之一或其父项中，则依赖关系将解析为该文件。
2. 否则，如果依赖文件有任何`RUNPATH`条目，并且库存在于这些条目之一中，则依赖关系将解析为该文件。
3. 否则，如果库存在于 列出的目录之一中 `ldconfig`，则依赖关系将解析为该文件。
4. 否则，如果该库存在于其中一个`DIRECTORIES`条目中，则依赖关系将解析为该文件。在这种情况下，会发出警告，因为在其中一种方式中找到文件`DIRECTORIES`意味着依赖文件不完整（它没有列出它从中提取依赖项的所有目录）。
5. 否则，依赖关系未解决。

在 Windows 平台上，库解析的工作方式如下：

1. 依赖的 DLL 名称被转换为小写。Windows DLL 名称不区分大小写，并且某些链接器会破坏 DLL 依赖项名称的大小写。但是，这使得 , , 和 正确过滤 DLL 名称变得更加困难`PRE_INCLUDE_REGEXES`- `PRE_EXCLUDE_REGEXES`每个`POST_INCLUDE_REGEXES`正 `POST_EXCLUDE_REGEXES`则表达式都必须检查大写和小写字母。例如：

   ```cmake
   file(GET_RUNTIME_DEPENDENCIES
     # ...
     PRE_INCLUDE_REGEXES "^[Mm][Yy][Ll][Ii][Bb][Rr][Aa][Rr][Yy]\\.[Dd][Ll][Ll]$"
     )
   ```

   将 DLL 名称转换为小写允许正则表达式仅匹配小写名称，从而简化正则表达式。例如：

   ```cmake
   file(GET_RUNTIME_DEPENDENCIES
     # ...
     PRE_INCLUDE_REGEXES "^mylibrary\\.dll$"
     )
   ```

   `mylibrary.dll`无论在磁盘上还是在依赖文件中，无论大小写如何，此正则表达式都将匹配。（例如，它将匹配 `mylibrary.dll`、`MyLibrary.dll`和`MYLIBRARY.DLL`。）

   请注意，任何已解析的 DLL 的目录部分都保留其大小写，并且不会转换为小写。只有文件名部分被转换。

2. （**尚未实现**）如果依赖文件是 Windows 应用商店应用程序，并且依赖项在应用程序的包清单中列为依赖项，则依赖项将解析为该文件。

3. 否则，如果库与依赖文件存在于同一目录中，则依赖关系将解析为该文件。

4. 否则，如果库存在于操作系统的 `system32`目录或`Windows`目录中，则依此顺序，依赖项将解析为该文件。

5. 否则，如果该库存在于 指定的目录之一中 `DIRECTORIES`，则按照它们列出的顺序，将依赖关系解析为该文件。在这种情况下，不会发出警告，因为搜索其他目录是 Windows 库解析的正常部分。

6. 否则，依赖关系未解决。

在 Apple 平台上，库解析的工作方式如下：

1. 如果依赖项以 开头，并且 正在解析 `@executable_path/`一个参数，并且替换为可执行文件的目录会产生一个现有文件，则依赖项将解析为该文件。`EXECUTABLES``@executable_path/`
2. 否则，如果依赖项以 开头`@executable_path/`，并且有一个`BUNDLE_EXECUTABLE`参数，并且替换`@executable_path/`为捆绑可执行文件的目录会产生一个现有文件，则依赖项将解析为该文件。
3. 否则，如果依赖项以 开头`@loader_path/`，并且用 `@loader_path/`依赖文件的目录替换会产生一个现有文件，则依赖项将解析为该文件。
4. 否则，如果依赖项以 开头`@rpath/`，并且用 依赖文件`@rpath/`的`RPATH`条目之一替换会产生现有文件，则依赖项将解析为该文件。请注意， 以相应路径`RPATH`开头`@executable_path/`或`@loader_path/` 同时将这些项目替换为相应路径的条目。
5. 否则，如果依赖项是存在的绝对文件，则将依赖项解析为该文件。
6. 否则，依赖关系未解决。

此函数接受几个变量，这些变量确定使用哪个工具进行依赖关系解析：

- **CMAKE_GET_RUNTIME_DEPENDENCIES_PLATFORM**

  确定构建文件的操作系统和可执行格式。这可能是几个值之一：`linux+elf``windows+pe``macos+macho`如果未指定此变量，则由系统自省自动确定。

- **CMAKE_GET_RUNTIME_DEPENDENCIES_TOOL**

  确定用于依赖关系解析的工具。它可以是几个值之一，具体取决于 

  | `CMAKE_GET_RUNTIME_DEPENDENCIES_PLATFORM` | `CMAKE_GET_RUNTIME_DEPENDENCIES_TOOL` |
  | ----------------------------------------- | ------------------------------------- |
  | `linux+elf`                               | `objdump`                             |
  | `windows+pe`                              | `dumpbin`                             |
  | `windows+pe`                              | `objdump`                             |
  | `macos+macho`                             | `otool`                               |

  如果未指定此变量，则由系统自省自动确定。

- **CMAKE_GET_RUNTIME_DEPENDENCIES_COMMAND**

  确定用于依赖关系解析的工具的路径。这是到 、 或 的`objdump`实际`dumpbin`路径`otool`。如果未指定此变量，则由 `CMAKE_OBJDUMP`if set 的值确定，否则由系统自省确定。*3.18 版中的新功能：*设置时使用`CMAKE_OBJDUMP`。

### Writing



```cmake
file(WRITE <filename> <content>...)
file(APPEND <filename> <content>...)
```

写入`<content>`一个名为`<filename>`. 如果文件不存在，则会创建它。如果文件已经存在，`WRITE` mode 将覆盖它，`APPEND`mode 将追加到末尾。将创建由指定的路径中`<filename>`不存在的任何目录。

如果文件是构建输入，请使用[`configure_file()`](https://cmake.org/cmake/help/latest/command/configure_file.html#command:configure_file)命令仅在其内容更改时更新文件。



```cmake
file(TOUCH [<files>...])
file(TOUCH_NOCREATE [<files>...])
```

*版本 3.12 中的新功能。*

如果文件尚不存在，则创建一个没有内容的文件。如果文件已经存在，它的访问和/或修改将更新到执行函数调用的时间。

如果文件存在，则使用 TOUCH_NOCREATE 触摸文件但不创建它。如果文件不存在，它将被静默忽略。

使用 TOUCH 和 TOUCH_NOCREATE 不会修改现有文件的内容。

```cmake
file(GENERATE OUTPUT output-file
     <INPUT input-file|CONTENT content>
     [CONDITION expression] [TARGET target]
     [NO_SOURCE_PERMISSIONS | USE_SOURCE_PERMISSIONS |
      FILE_PERMISSIONS <permissions>...]
     [NEWLINE_STYLE [UNIX|DOS|WIN32|LF|CRLF] ])
```

为当前支持的每个构建配置生成一个输出文件 [`CMake Generator`](https://cmake.org/cmake/help/latest/manual/cmake-generators.7.html#manual:cmake-generators(7)). 评估 [`generator expressions`](https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html#manual:cmake-generator-expressions(7)) 从输入内容产生输出内容。选项包括：

- `CONDITION <condition>`

  仅当条件为真时才为特定配置生成输出文件。条件必须是`0`或`1` 在评估生成器表达式之后。

- `CONTENT <content>`

  使用明确给出的内容作为输入。

- `INPUT <input-file>`

  使用给定文件中的内容作为输入。*在 3.10 版更改:*相对路径的值相对于 [`CMAKE_CURRENT_SOURCE_DIR`](https://cmake.org/cmake/help/latest/variable/CMAKE_CURRENT_SOURCE_DIR.html#variable:CMAKE_CURRENT_SOURCE_DIR). 查看政策[`CMP0070`](https://cmake.org/cmake/help/latest/policy/CMP0070.html#policy:CMP0070).

- `OUTPUT <output-file>`

  指定要生成的输出文件名。使用生成器表达式，例如`$<CONFIG>`指定特定于配置的输出文件名。只有当生成的内容相同时，多个配置才可能生成相同的输出文件。否则，`<output-file>` 必须为每个配置计算一个唯一名称。*在 3.10 版更改：*相对路径（在评估生成器表达式之后）根据[`CMAKE_CURRENT_BINARY_DIR`](https://cmake.org/cmake/help/latest/variable/CMAKE_CURRENT_BINARY_DIR.html#variable:CMAKE_CURRENT_BINARY_DIR). 查看政策[`CMP0070`](https://cmake.org/cmake/help/latest/policy/CMP0070.html#policy:CMP0070).

- `TARGET <target>`

  *3.19 版中的新功能。*指定在评估需要评估目标的生成器表达式时使用哪个目标（例如`$<COMPILE_FEATURES:...>`， `$<TARGET_PROPERTY:prop>`）。

- `NO_SOURCE_PERMISSIONS`

  *3.20 版中的新功能。*生成的文件权限默认为标准 644 值 (-rw-r--r--)。

- `USE_SOURCE_PERMISSIONS`

  *3.20 版中的新功能。*将文件的文件权限转移`INPUT`到生成的文件中。 如果没有给出三个与权限相关的关键字（或）`NO_SOURCE_PERMISSIONS`，这已经是默认行为。关键字主要用作使呼叫站点上的预期行为更清晰的一种方式。不指定此选项是错误的。`USE_SOURCE_PERMISSIONS``FILE_PERMISSIONS``USE_SOURCE_PERMISSIONS``INPUT`

- `FILE_PERMISSIONS <permissions>...`

  *3.20 版中的新功能。*对生成的文件使用指定的权限。

- `NEWLINE_STYLE <style>`

  *3.20 版中的新功能。*为生成的文件指定换行样式。为换行指定 `UNIX`or ，或`LF`为换`\n`行指定 `DOS`, `WIN32`, or 。`CRLF``\r\n`

必须给出确切的一个`CONTENT`或选项。`INPUT`一个特定的 `OUTPUT`文件最多可以通过一次调用来命名`file(GENERATE)`。生成的文件仅在其内容发生更改时才会在后续 cmake 运行时被修改并更新其时间戳。

另请注意，`file(GENERATE)`直到生成阶段才创建输出文件。当命令返回时，输出文件还没有被写入 `file(GENERATE)`，只有在处理完项目的所有`CMakeLists.txt`文件后才会写入。

```cmake
file(CONFIGURE OUTPUT output-file
     CONTENT content
     [ESCAPE_QUOTES] [@ONLY]
     [NEWLINE_STYLE [UNIX|DOS|WIN32|LF|CRLF] ])
```

*3.18 版中的新功能。*

`CONTENT`使用由引用`@VAR@`或`${VAR}`包含在其中的变量值给出的输入和替换变量值生成输出文件。替换规则的行为与[`configure_file()`](https://cmake.org/cmake/help/latest/command/configure_file.html#command:configure_file)命令。为了匹配[`configure_file()`](https://cmake.org/cmake/help/latest/command/configure_file.html#command:configure_file)的行为，生成器表达式不支持`OUTPUT`和`CONTENT`。

论据是：

- `OUTPUT <output-file>`

  指定要生成的输出文件名。相对路径的值相对于[`CMAKE_CURRENT_BINARY_DIR`](https://cmake.org/cmake/help/latest/variable/CMAKE_CURRENT_BINARY_DIR.html#variable:CMAKE_CURRENT_BINARY_DIR). `<output-file>`不支持生成器表达式。

- `CONTENT <content>`

  使用明确给出的内容作为输入。 `<content>`不支持生成器表达式。

- `ESCAPE_QUOTES`

  使用反斜杠（C 样式）转义任何替换的引号。

- `@ONLY`

  将变量替换限制为对表单的引用`@VAR@`。这对于配置使用`${VAR}`语法的脚本很有用。

- `NEWLINE_STYLE <style>`

  指定输出文件的换行样式。为换行指定 `UNIX`or ，或`LF`为换`\n`行指定 `DOS`, `WIN32`, or 。`CRLF``\r\n`

### Filesystem



```cmake
file(GLOB <variable>
     [LIST_DIRECTORIES true|false] [RELATIVE <path>] [CONFIGURE_DEPENDS]
     [<globbing-expressions>...])
file(GLOB_RECURSE <variable> [FOLLOW_SYMLINKS]
     [LIST_DIRECTORIES true|false] [RELATIVE <path>] [CONFIGURE_DEPENDS]
     [<globbing-expressions>...])
```

生成与 匹配的文件列表`<globbing-expressions>`并将其存储到`<variable>`. 通配表达式类似于正则表达式，但要简单得多。如果`RELATIVE`指定了标志，则结果将作为给定路径的相对路径返回。

*在 3.6 版更改:*结果将按字典顺序排列。

在 Windows 和 macOS 上，即使底层文件系统区分大小写，通配也不区分大小写（文件名和通配表达式在匹配之前都转换为小写）。在其他平台上，通配符区分大小写。

*3.3 版中的新功能：*默认情况下列出`GLOB`目录 - 如果 `LIST_DIRECTORIES`设置为 false，则在结果中省略目录。

*3.12 版新功能：*如果`CONFIGURE_DEPENDS`指定了标志，CMake 将向主构建系统检查目标添加逻辑，以`GLOB`在构建时重新运行标记的命令。如果任何输出发生变化，CMake 将重新生成构建系统。

> **笔记:** 我们不建议使用 GLOB 从源代码树中收集源文件列表。如果添加或删除源时没有 CMakeLists.txt 文件更改，则生成的构建系统无法知道何时要求 CMake 重新生成。该`CONFIGURE_DEPENDS`标志可能无法在所有生成器上可靠地工作，或者如果将来添加不能支持它的新生成器，使用它的项目将被卡住。即使`CONFIGURE_DEPENDS`工作可靠，每次重建都需要进行检查。

通配表达式的示例包括：

```cmake
*.cxx      - match all files with extension cxx
*.vt?      - match all files with extension vta,...,vtz
f[3-5].txt - match files f3.txt, f4.txt, f5.txt
```

该`GLOB_RECURSE`模式将遍历匹配目录的所有子目录并匹配文件。作为符号链接的子目录仅在`FOLLOW_SYMLINKS`给定或策略 时才被遍历[`CMP0009`](https://cmake.org/cmake/help/latest/policy/CMP0009.html#policy:CMP0009)未设置为`NEW`。

*3.3 版中的新功能：*默认情况下会`GLOB_RECURSE`从结果列表中省略目录 - 设置 `LIST_DIRECTORIES`为 true 会将目录添加到结果列表中。如果`FOLLOW_SYMLINKS`给出或政策[`CMP0009`](https://cmake.org/cmake/help/latest/policy/CMP0009.html#policy:CMP0009)未设置为 `NEW`则将`LIST_DIRECTORIES`符号链接视为目录。

递归通配符的示例包括：

```cmake
/dir/*.py  - match all python files in /dir and subdirectories
file(MAKE_DIRECTORY [<directories>...])
```

根据需要创建给定的目录及其父目录。



```cmake
file(REMOVE [<files>...])
file(REMOVE_RECURSE [<files>...])
```

删除给定的文件。该`REMOVE_RECURSE`模式将删除给定的文件和目录，以及非空目录。如果给定文件不存在，则不会发出错误。相对输入路径相对于当前源目录进行评估。

*在 3.15 版更改:*空输入路径被忽略并发出警告。以前版本的 CMake 将空字符串解释为相对于当前目录的相对路径并删除其内容。

```cmake
file(RENAME <oldname> <newname>
     [RESULT <result>]
     [NO_REPLACE])
```

将文件系统中的文件或目录从 移动`<oldname>`到 `<newname>`，以原子方式替换目标。

选项包括：

- `RESULT <result>`

  *3.21 版中的新功能。*将`<result>`变量设置为`0`成功或错误消息。如果`RESULT`未指定且操作失败，则会发出错误。

- `NO_REPLACE`

  *3.21 版中的新功能。*如果`<newname>`路径已经存在，请不要替换它。如果使用，结果变量将设置为. 否则，会发出错误。`RESULT <result>``NO_REPLACE`

```cmake
file(COPY_FILE <oldname> <newname>
     [RESULT <result>]
     [ONLY_IF_DIFFERENT])
```

*3.21 版中的新功能。*

将文件从 复制`<oldname>`到`<newname>`. 不支持目录。符号链接被忽略，的内容作为新文件`<oldfile>`被读取和写入。`<newname>`

选项包括：

- `RESULT <result>`

  将`<result>`变量设置为`0`成功或错误消息。如果`RESULT`未指定且操作失败，则会发出错误。

- `ONLY_IF_DIFFERENT`

  如果`<newname>`路径已经存在，如果文件的内容已经相同，则不要替换它`<oldname>`（这样可以避免更新 `<newname>`的时间戳）。

这个子命令有一些相似之处[`configure_file()`](https://cmake.org/cmake/help/latest/command/configure_file.html#command:configure_file)与 `COPYONLY`选项。一个重要的区别是[`configure_file()`](https://cmake.org/cmake/help/latest/command/configure_file.html#command:configure_file) 创建对源文件的依赖项，因此如果更改，CMake 将重新运行。`file(COPY_FILE)`子命令不会创建这样的依赖关系。

另请参阅`file(COPY)`下面的子命令，它提供了进一步的文件复制功能。



```cmake
file(<COPY|INSTALL> <files>... DESTINATION <dir>
     [NO_SOURCE_PERMISSIONS | USE_SOURCE_PERMISSIONS]
     [FILE_PERMISSIONS <permissions>...]
     [DIRECTORY_PERMISSIONS <permissions>...]
     [FOLLOW_SYMLINK_CHAIN]
     [FILES_MATCHING]
     [[PATTERN <pattern> | REGEX <regex>]
      [EXCLUDE] [PERMISSIONS <permissions>...]] [...])
```

> **笔记:** 对于简单的文件复制操作，`file(COPY_FILE)`上面的子命令可能更容易使用。

签名将`COPY`文件、目录和符号链接复制到目标文件夹。相对输入路径是相对于当前源目录评估的，相对目标是相对于当前构建目录评估的。复制会保留输入文件的时间戳，如果文件存在于目标位置且具有相同的时间戳，则会对其进行优化。复制会保留输入权限，除非`NO_SOURCE_PERMISSIONS` 给出明确的权限或（默认为`USE_SOURCE_PERMISSIONS`）。

*3.15 版中的新功能：*如果`FOLLOW_SYMLINK_CHAIN`指定，`COPY`将递归解析给定路径的符号链接，直到找到真实文件，并在目标位置为遇到的每个符号链接安装相应的符号链接。对于每个安装的符号链接，解析会从目录中剥离，只留下文件名，这意味着新符号链接指向与符号链接相同目录中的文件。此功能在某些 Unix 系统上很有用，其中库作为带有版本号的符号链接链安装，不太具体的版本指向更具体的版本。 `FOLLOW_SYMLINK_CHAIN`会将所有这些符号链接和库本身安装到目标目录中。例如，如果您具有以下目录结构：

- `/opt/foo/lib/libfoo.so.1.2.3`
- `/opt/foo/lib/libfoo.so.1.2 -> libfoo.so.1.2.3`
- `/opt/foo/lib/libfoo.so.1 -> libfoo.so.1.2`
- `/opt/foo/lib/libfoo.so -> libfoo.so.1`

你也是：

```cmake
file(COPY /opt/foo/lib/libfoo.so DESTINATION lib FOLLOW_SYMLINK_CHAIN)
```

这会将所有符号链接及其`libfoo.so.1.2.3`自身安装到 `lib`.

见[`install(DIRECTORY)`](https://cmake.org/cmake/help/latest/command/install.html#command:install)用于记录权限、`FILES_MATCHING`、`PATTERN`、`REGEX`和 `EXCLUDE`选项的命令。即使使用选项来选择文件的子集，复制目录也会保留其内容的结构。

`INSTALL`签名与 略有不同：`COPY`它打印状态消息，并且`NO_SOURCE_PERMISSIONS`是默认的。

生成的安装脚本[`install()`](https://cmake.org/cmake/help/latest/command/install.html#command:install)命令使用此签名（带有一些未记录的选项供内部使用）。

*在 3.22 版更改:*环境变量[`CMAKE_INSTALL_MODE`](https://cmake.org/cmake/help/latest/envvar/CMAKE_INSTALL_MODE.html#envvar:CMAKE_INSTALL_MODE)可以覆盖的默认复制行为[`file(INSTALL)`](https://cmake.org/cmake/help/latest/command/file.html#command:file).

```cmake
file(SIZE <filename> <variable>)
```

*版本 3.14 中的新功能。*

确定文件大小`<filename>`并将结果放入 `<variable>`变量中。要求这`<filename>`是指向文件的有效路径并且是可读的。

```cmake
file(READ_SYMLINK <linkname> <variable>)
```

*版本 3.14 中的新功能。*

此子命令查询符号链接`<linkname>`并将其指向的路径存储在结果中`<variable>`。如果`<linkname>`不存在或不是符号链接，CMake 会发出致命错误。

请注意，此命令返回原始符号链接路径并且不解析相对路径。以下是如何确保获取绝对路径的示例：

```cmake
set(linkname "/path/to/foo.sym")
file(READ_SYMLINK "${linkname}" result)
if(NOT IS_ABSOLUTE "${result}")
  get_filename_component(dir "${linkname}" DIRECTORY)
  set(result "${dir}/${result}")
endif()
file(CREATE_LINK <original> <linkname>
     [RESULT <result>] [COPY_ON_ERROR] [SYMBOLIC])
```

*版本 3.14 中的新功能。*

创建一个指向 的`<linkname>`链接`<original>`。默认情况下它将是一个硬链接，但提供该`SYMBOLIC`选项会导致一个符号链接。硬链接要求`original` 存在并且是文件，而不是目录。如果`<linkname>`已经存在，它将被覆盖。

该`<result>`变量（如果指定）接收操作的状态。它设置为`0`成功或错误消息。如果`RESULT` 未指定且操作失败，则会发出致命错误。

如果创建链接失败，指定`COPY_ON_ERROR`启用复制文件作为后备。它对于处理诸如处于不同驱动器或安装点的情况很有用 `<original>`，`<linkname>`这会使它们无法支持硬链接。

```cmake
file(CHMOD <files>... <directories>...
    [PERMISSIONS <permissions>...]
    [FILE_PERMISSIONS <permissions>...]
    [DIRECTORY_PERMISSIONS <permissions>...])
```

*3.19 版中的新功能。*

设置`<files>...`和`<directories>...`指定的权限。有效权限为 `OWNER_READ`, `OWNER_WRITE`, `OWNER_EXECUTE`, `GROUP_READ`, `GROUP_WRITE`, `GROUP_EXECUTE`, `WORLD_READ`, `WORLD_WRITE`, `WORLD_EXECUTE`, `SETUID`, `SETGID`.

关键字的有效组合是：

- `PERMISSIONS`

  所有项目都已更改。

- `FILE_PERMISSIONS`

  仅更改文件。

- `DIRECTORY_PERMISSIONS`

  仅更改目录。

- `PERMISSIONS`和`FILE_PERMISSIONS`

  `FILE_PERMISSIONS`覆盖`PERMISSIONS`文件。

- `PERMISSIONS`和`DIRECTORY_PERMISSIONS`

  `DIRECTORY_PERMISSIONS`覆盖`PERMISSIONS`目录。

- `FILE_PERMISSIONS`和`DIRECTORY_PERMISSIONS`

  用于`FILE_PERMISSIONS`文件和`DIRECTORY_PERMISSIONS`目录。

```cmake
file(CHMOD_RECURSE <files>... <directories>...
     [PERMISSIONS <permissions>...]
     [FILE_PERMISSIONS <permissions>...]
     [DIRECTORY_PERMISSIONS <permissions>...])
```

*3.19 版中的新功能。*

与[CHMOD](https://cmake.org/cmake/help/latest/command/file.html#chmod)`<directories>...`相同，但以递归方式更改文件和目录的权限。

### 路径转换

```cmake
file(REAL_PATH <path> <out-var> [BASE_DIRECTORY <dir>] [EXPAND_TILDE])
```

*3.19 版中的新功能。*

计算已解析符号链接的现有文件或目录的绝对路径。

- `BASE_DIRECTORY <dir>`

  如果提供`<path>`的是相对路径，则相对于给定的基本目录进行评估`<dir>`。如果未提供基本目录，则默认基本目录为[`CMAKE_CURRENT_SOURCE_DIR`](https://cmake.org/cmake/help/latest/variable/CMAKE_CURRENT_SOURCE_DIR.html#variable:CMAKE_CURRENT_SOURCE_DIR).

- `EXPAND_TILDE`

  *3.21 版中的新功能。*如果`<path>`is`~`或以 开头`~/`，则将`~`替换为用户的主目录。主目录的路径是从环境变量中获取的。在 Windows 上，使用环境变量，如果 未定义则`USERPROFILE`回退到环境变量。在所有其他平台上，仅使用。`HOME``USERPROFILE``HOME`

```cmake
file(RELATIVE_PATH <variable> <directory> <file>)
```

计算从 a`<directory>`到 a的相对路径`<file>`并将其存储在`<variable>`.



```cmake
file(TO_CMAKE_PATH "<path>" <variable>)
file(TO_NATIVE_PATH "<path>" <variable>)
```

该`TO_CMAKE_PATH`模式将本机`<path>`转换为带有正斜杠 ( `/`) 的 cmake 样式路径。输入可以是单个路径或系统搜索路径，例如`$ENV{PATH}`. 搜索路径将转换为由`;`字符分隔的 cmake 样式列表。

该`TO_NATIVE_PATH`模式将 cmake 样式`<path>`转换为带有特定于平台的斜杠的本机路径（`\`在 Windows 主机和`/` 其他地方）。

始终在 周围使用双引号`<path>`以确保将其视为此命令的单个参数。

### Transfer



```cmake
file(DOWNLOAD <url> [<file>] [<options>...])
file(UPLOAD   <file> <url> [<options>...])
```

该`DOWNLOAD`子命令将给定的内容下载`<url>`到本地`<file>`。该`UPLOAD`模式将本地上传`<file>`到给定的`<url>`.

*3.19 新版功能：*如果`<file>`未指定`file(DOWNLOAD)`，则不保存文件。如果您想知道是否可以下载文件（例如，检查它是否存在）而不实际将其保存在任何地方，这将很有用。

两者的选项`DOWNLOAD`和`UPLOAD`是：

- `INACTIVITY_TIMEOUT <seconds>`

  在一段时间不活动后终止操作。

- `LOG <variable>`

  将操作的人类可读日志存储在变量中。

- `SHOW_PROGRESS`

  将进度信息打印为状态消息，直到操作完成。

- `STATUS <variable>`

  将操作的结果状态存储在变量中。status 是一个`;`长度为 2 的分隔列表。第一个元素是操作的数字返回值，第二个元素是错误的字符串值。数字`0`错误意味着操作中没有错误。

- `TIMEOUT <seconds>`

  在给定的总时间过去后终止操作。

- `USERPWD <username>:<password>`

  *3.7 版中的新功能。*设置用户名和密码进行操作。

- `HTTPHEADER <HTTP-header>`

  *3.7 版中的新功能。*用于操作的 HTTP 标头。子选项可以重复多次。

- `NETRC <level>`

  *3.11 版中的新功能。*指定是否将 .netrc 文件用于操作。如果未指定此选项，则[`CMAKE_NETRC`](https://cmake.org/cmake/help/latest/variable/CMAKE_NETRC.html#variable:CMAKE_NETRC)变量将被使用。有效级别是：`IGNORED`.netrc 文件被忽略。这是默认设置。`OPTIONAL`.netrc 文件是可选的，URL 中的信息是首选。将扫描该文件以查找 URL 中未指定的信息。`REQUIRED`.netrc 文件是必需的，URL 中的信息被忽略。

- `NETRC_FILE <file>`

  *3.11 版中的新功能。*`NETRC`如果级别为`OPTIONAL`或，请为您的主目录中的文件指定一个替代 .netrc 文件`REQUIRED`。如果未指定此选项，则[`CMAKE_NETRC_FILE`](https://cmake.org/cmake/help/latest/variable/CMAKE_NETRC_FILE.html#variable:CMAKE_NETRC_FILE)变量将被使用。

- `TLS_VERIFY <ON|OFF>`

  指定是否验证`https://`URL 的服务器证书。默认为*不*验证。如果未指定此选项，则[`CMAKE_TLS_VERIFY`](https://cmake.org/cmake/help/latest/variable/CMAKE_TLS_VERIFY.html#variable:CMAKE_TLS_VERIFY)变量将被使用。*3.18 新版功能：*添加了对`file(UPLOAD)`.

- `TLS_CAINFO <file>`

  `https://`为URL指定自定义证书颁发机构文件。如果未指定此选项，则[`CMAKE_TLS_CAINFO`](https://cmake.org/cmake/help/latest/variable/CMAKE_TLS_CAINFO.html#variable:CMAKE_TLS_CAINFO) 变量将被使用。*3.18 新版功能：*添加了对`file(UPLOAD)`.

对于`https://`URL，CMake 必须使用 OpenSSL 支持构建。 `TLS/SSL` 默认情况下不检查证书。设置`TLS_VERIFY`为`ON`检查证书。

其他选项`DOWNLOAD`是：

```cmake
EXPECTED_HASH ALGO=<value>
```

> 验证下载的内容哈希是否与预期值匹配，其中 `ALGO`是 支持的算法之一`file(<HASH>)`。如果不匹配，则操作失败并出现错误。`DOWNLOAD`如果没有给出.指定这个是错误的`<file>`。

- `EXPECTED_MD5 <value>`

  的历史简写。如果没有给出.指定这个是错误的。`EXPECTED_HASH MD5=<value>``DOWNLOAD``<file>`

- `RANGE_START <value>`

  *版本 3.24 中的新功能。*文件中范围开始的偏移量（以字节为单位）。可以省略下载到指定的`RANGE_END`.

- `RANGE_END <value>`

  *版本 3.24 中的新功能。*文件中范围末尾的偏移量（以字节为单位）。可以省略以下载从指定`RANGE_START`文件到文件末尾的所有内容。

### Locking

```cmake
file(LOCK <path> [DIRECTORY] [RELEASE]
     [GUARD <FUNCTION|FILE|PROCESS>]
     [RESULT_VARIABLE <variable>]
     [TIMEOUT <seconds>])
```

*3.2 版中的新功能。*

`<path>`如果不存在`DIRECTORY`选项， 则锁定指定的文件，`<path>/cmake.lock`否则锁定文件。文件将被 `GUARD`选项定义的范围锁定（默认值为`PROCESS`）。`RELEASE`选项可用于显式解锁文件。如果`TIMEOUT`未指定选项，CMake 将等待锁定成功或发生致命错误。如果`TIMEOUT`设置为 `0`锁定，将尝试一次并立即报告结果。如果 `TIMEOUT`不是`0`，CMake 将尝试在`<seconds>`value 指定的时间段内锁定文件。如果没有 `RESULT_VARIABLE`选项，任何错误都将被解释为致命错误。否则结果将被存储`<variable>` 并`0`在成功或失败时显示错误消息。

请注意，锁是建议性的——不能保证其他进程会遵守这个锁，即锁同步两个或多个共享一些可修改资源的 CMake 实例。类似的逻辑应用于`DIRECTORY`选项 - 锁定父目录不会阻止其他`LOCK`命令锁定任何子目录或文件。

不允许尝试两次锁定文件。如果它们不存在，将创建任何中间目录和文件本身。 `GUARD`和选项在操作中`TIMEOUT` 被忽略。`RELEASE`

### Archiving

```cmake
file(ARCHIVE_CREATE OUTPUT <archive>
  PATHS <paths>...
  [FORMAT <format>]
  [COMPRESSION <compression> [COMPRESSION_LEVEL <compression-level>]]
  [MTIME <mtime>]
  [VERBOSE])
```

*3.18 版中的新功能。*

`<archive>`使用 中列出的文件和目录创建指定文件`<paths>`。请注意，`<paths>`必须列出实际文件或目录，不支持通配符。

使用该`FORMAT`选项指定存档格式。支持`<format>`的值为`7zip`、`gnutar`、`pax`、`paxr`和`raw`。 `zip`如果`FORMAT`未给出，则默认格式为`paxr`.

一些存档格式允许指定压缩类型。和存档格式已经暗示了一种特定类型的压缩`7zip`。`zip`其他格式默认不使用压缩，但可以使用该`COMPRESSION`选项进行指导。的有效值为 `<compression>`、`None`、`BZip2`、`GZip`和。`XZ``Zstd`

*3.19 新版功能：*可以使用`COMPRESSION_LEVEL`选项指定压缩级别。`<compression-level>`应该在 0-9 之间，默认值为 0。当给出选项时，该选项必须`COMPRESSION`存在。`COMPRESSION_LEVEL`

> **笔记：**`FORMAT`设置为只有一个文件将使用`raw`指定的压缩类型进行压缩`COMPRESSION`。

 该`VERBOSE`选项为归档操作启用详细输出。

要指定记录在 tarball 条目中的修改时间，请使用该`MTIME`选项。

```cmake
file(ARCHIVE_EXTRACT INPUT <archive>
  [DESTINATION <dir>]
  [PATTERNS <patterns>...]
  [LIST_ONLY]
  [VERBOSE]
  [TOUCH])
```

*3.18 版中的新功能。*

提取或列出指定的内容`<archive>`。

`DESTINATION`可以使用该选项指定存档内容将被提取到的目录。如果该目录不存在，则会创建该目录。如果`DESTINATION`没有给出，将使用当前的二进制目录。

如果需要，您可以使用指定的`<patterns>`. 支持通配符。如果`PATTERNS`未给出该选项，则将列出或提取整个存档。

`LIST_ONLY`将列出存档中的文件而不是提取它们。

*3.24 版中的新功能：*该`TOUCH`选项为提取的文件提供当前本地时间戳，而不是从存档中提取文件时间戳。

使用`VERBOSE`，该命令将产生详细的输出。



## [option](https://cmake.org/cmake/help/latest/command/option.html)

提供用户可以选择的布尔选项。

```cmake
option(<variable> "<help_text>" [value])
```

如果没有`<value>`提供初始值，则布尔值`OFF`是默认值。如果`<variable>`已设置为普通或缓存变量，则该命令不执行任何操作（请参阅策略[`CMP0077`](https://cmake.org/cmake/help/latest/policy/CMP0077.html#policy:CMP0077)).

对于依赖于其他选项值的选项，请参阅模块帮助[`CMakeDependentOption`](https://cmake.org/cmake/help/latest/module/CMakeDependentOption.html#module:CMakeDependentOption).

在 CMake 项目模式下，使用选项值创建一个布尔缓存变量。在 CMake 脚本模式下，使用选项值设置一个布尔变量。




# 判断语法

## [if](https://cmake.org/cmake/help/latest/command/if.html)

有条件地执行一组命令。

### 简明

```cmake
if(<condition>)
  <commands>
elseif(<condition>) # optional block, can be repeated
  <commands>
else()              # optional block
  <commands>
endif()
```

根据 下面描述的[条件语法](https://cmake.org/cmake/help/latest/command/if.html#condition-syntax)评估子句的`condition`参数。如果结果为真，则 执行块中的。否则，以相同方式处理可选块。最后，如果 no为真，则在可选 块中执行。`if``commands``if``elseif``condition``commands``else`

根据遗产，[`else()`](https://cmake.org/cmake/help/latest/command/else.html#command:else)和[`endif()`](https://cmake.org/cmake/help/latest/command/endif.html#command:endif)命令接受一个可选`<condition>`参数。如果使用，它必须是开头 `if`命令参数的逐字重复。



### 条件语法

以下语法适用`condition`于`if`,`elseif`和[`while()`](https://cmake.org/cmake/help/latest/command/while.html#command:while)条款。

复合条件按以下优先顺序进行评估：

1. 括号。
2. 一元测试，例如[EXISTS](https://cmake.org/cmake/help/latest/command/if.html#exists)、[COMMAND](https://cmake.org/cmake/help/latest/command/if.html#command)和[DEFINED](https://cmake.org/cmake/help/latest/command/if.html#defined)。
3. 二进制测试，例如[EQUAL](https://cmake.org/cmake/help/latest/command/if.html#equal)、[LESS](https://cmake.org/cmake/help/latest/command/if.html#less)、[LESS_EQUAL](https://cmake.org/cmake/help/latest/command/if.html#less-equal)、[GREATER](https://cmake.org/cmake/help/latest/command/if.html#greater)、 [GREATER_EQUAL](https://cmake.org/cmake/help/latest/command/if.html#greater-equal)、[STREQUAL](https://cmake.org/cmake/help/latest/command/if.html#strequal)、[STRLESS](https://cmake.org/cmake/help/latest/command/if.html#strless)、[STRLESS_EQUAL](https://cmake.org/cmake/help/latest/command/if.html#strless-equal)、 [STRGREATER](https://cmake.org/cmake/help/latest/command/if.html#strgreater)、[STRGREATER_EQUAL](https://cmake.org/cmake/help/latest/command/if.html#strgreater-equal)、[VERSION_EQUAL](https://cmake.org/cmake/help/latest/command/if.html#version-equal)、[VERSION_LESS](https://cmake.org/cmake/help/latest/command/if.html#version-less)、 [VERSION_LESS_EQUAL](https://cmake.org/cmake/help/latest/command/if.html#version-less-equal)、[VERSION_GREATER](https://cmake.org/cmake/help/latest/command/if.html#version-greater)、[VERSION_GREATER_EQUAL](https://cmake.org/cmake/help/latest/command/if.html#version-greater-equal)、 和[PATH_EQUAL ](https://cmake.org/cmake/help/latest/command/if.html#path-equal)[。](https://cmake.org/cmake/help/latest/command/if.html#matches)
4. 一元逻辑运算符[NOT](https://cmake.org/cmake/help/latest/command/if.html#not)。
5. 二元逻辑运算符[AND](https://cmake.org/cmake/help/latest/command/if.html#and)和[OR](https://cmake.org/cmake/help/latest/command/if.html#or)，从左到右，没有任何短路。

#### 基本表达式

- `if(<constant>)`

  如果常数是`1`, `ON`, `YES`, `TRUE`,`Y`或非零数（包括浮点数），则为真。False 如果常量是`0`, `OFF`, `NO`, `FALSE`, `N`, `IGNORE`, `NOTFOUND`, 空字符串，或以 suffix 结尾`-NOTFOUND`。命名布尔常量不区分大小写。如果参数不是这些特定常量之一，则将其视为变量或字符串（请参阅下面的[变量扩展](https://cmake.org/cmake/help/latest/command/if.html#variable-expansion) ），并适用以下两种形式之一。

- `if(<variable>)`

  如果给定一个定义为非假常量的值的变量，则为真。否则为 False，包括变量未定义时。请注意，宏参数不是变量。 [环境变量](https://cmake.org/cmake/help/latest/manual/cmake-language.7.html#cmake-language-environment-variables)也不能以这种方式进行测试，例如`if(ENV{some_var})`，总是会评估为假。

- `if(<string>)`

  带引号的字符串始终计算为 false，除非：字符串的值是真正的常量之一，或者政策[`CMP0054`](https://cmake.org/cmake/help/latest/policy/CMP0054.html#policy:CMP0054)未设置为`NEW`，并且字符串的值恰好是受以下因素影响的变量名[`CMP0054`](https://cmake.org/cmake/help/latest/policy/CMP0054.html#policy:CMP0054)的行为。

#### 逻辑运算符

- `if(NOT <condition>)`

  如果条件不为真，则为真。

- `if(<cond1> AND <cond2>)`

  如果两个条件都被单独认为是真的，则为真。

- `if(<cond1> OR <cond2>)`

  如果任一条件单独被认为是真的，则为真。

- `if((condition) AND (condition OR (condition)))`

  首先评估括号内的条件，然后像其他示例一样评估其余条件。在有嵌套括号的地方，最里面的括号被评估为评估包含它们的条件的一部分。

#### 存在性检查

- `if(COMMAND command-name)`

  如果给定名称是可以调用的命令、宏或函数，则为真。

- `if(POLICY policy-id)`

  如果给定名称是现有策略（形式为`CMP<NNNN>`），则为真。

- `if(TARGET target-name)`

  如果给定名称是由调用创建的现有逻辑目标名称，则为真[`add_executable()`](https://cmake.org/cmake/help/latest/command/add_executable.html#command:add_executable), [`add_library()`](https://cmake.org/cmake/help/latest/command/add_library.html#command:add_library)， 或者[`add_custom_target()`](https://cmake.org/cmake/help/latest/command/add_custom_target.html#command:add_custom_target)已经调用的命令（在任何目录中）。

- `if(TEST test-name)`

  *3.3 版新功能：*如果给定名称是由 [`add_test()`](https://cmake.org/cmake/help/latest/command/add_test.html#command:add_test)命令。

- `if(DEFINED <name>|CACHE{<name>}|ENV{<name>})`

  如果定义了给定的变量、缓存变量或环境变量，则为真`<name>`。变量的值无关紧要。请注意以下警告：宏参数不是变量。无法直接测试<name>是否为非缓存变量。如果存在缓存或非缓存变量，则表达式将评估为真。相比之下，只有存在缓存变量时，表达式才会计算为真。如果您需要知道是否存在非缓存变量，则需要测试这两个表达式： .`if(DEFINED someName)``someName``if(DEFINED CACHE{someName})``someName``if(DEFINED someName AND NOT DEFINED CACHE{someName})`*3.14 新版功能：*增加了对`CACHE{<name>}`变量的支持。

- `if(<variable|string> IN_LIST <variable>)`

  *3.3 新版功能：*如果给定元素包含在命名列表变量中，则为真。

#### 文件操作

- `if(EXISTS path-to-file-or-directory)`

  如果指定的文件或目录存在，则为真。行为仅针对显式完整路径进行了明确定义（前导`~/`不扩展为主目录，并且被视为相对路径）。解析符号链接，即如果指定的文件或目录是符号链接，如果符号链接的目标存在，则返回 true。

- `if(file1 IS_NEWER_THAN file2)`

  `file1`如果两个文件更新`file2`或两个文件之一不存在，则为真。行为仅针对完整路径进行了明确定义。如果文件时间戳完全相同，则`IS_NEWER_THAN`比较返回 true，以便在出现平局时发生任何相关的构建操作。这包括为 file1 和 file2 传递相同文件名的情况。

- `if(IS_DIRECTORY path-to-directory)`

  如果给定名称是目录，则为真。行为仅针对完整路径进行了明确定义。

- `if(IS_SYMLINK file-name)`

  如果给定名称是符号链接，则为真。行为仅针对完整路径进行了明确定义。

- `if(IS_ABSOLUTE path)`

  如果给定路径是绝对路径，则为真。请注意以下特殊情况：一个空的`path`评估为假。在 Windows 主机上，任何`path`以驱动器号和冒号（例如`C:`）、正斜杠或反斜杠开头的都将评估为真。这意味着路径 like`C:no\base\dir`将评估为 true，即使路径的非驱动部分是相对的。在非 Windows 主机上，任何`path`以波浪号 ( `~`) 开头的都计算为真。

#### Comparisons

- `if(<variable|string> MATCHES regex)`

  如果给定的字符串或变量的值与给定的正则表达式匹配，则为真。有关正则表达式格式，请参阅正则[表达式规范](https://cmake.org/cmake/help/latest/command/string.html#regex-specification)。*3.9 版中的新功能：*`()`组被捕获在[`CMAKE_MATCH_`](https://cmake.org/cmake/help/latest/variable/CMAKE_MATCH_n.html#variable:CMAKE_MATCH_)变量。

- `if(<variable|string> LESS <variable|string>)`

  如果给定字符串或变量的值是有效数字且小于右侧的数字，则为真。

- `if(<variable|string> GREATER <variable|string>)`

  如果给定的字符串或变量的值是有效数字并且大于右边的数字，则为真。

- `if(<variable|string> EQUAL <variable|string>)`

  如果给定字符串或变量的值是有效数字并且等于右侧的数字，则为真。

- `if(<variable|string> LESS_EQUAL <variable|string>)`

  *3.7 版新功能：*如果给定字符串或变量的值是有效数字且小于或等于右侧的数字，则为真。

- `if(<variable|string> GREATER_EQUAL <variable|string>)`

  *3.7 新版功能：*如果给定字符串或变量的值是有效数字并且大于或等于右侧的数字，则为真。

- `if(<variable|string> STRLESS <variable|string>)`

  如果给定字符串或变量的值按字典顺序小于右侧的字符串或变量，则为真。

- `if(<variable|string> STRGREATER <variable|string>)`

  如果给定字符串或变量的值按字典顺序大于右侧的字符串或变量，则为真。

- `if(<variable|string> STREQUAL <variable|string>)`

  如果给定字符串或变量的值在字典上等于右侧的字符串或变量，则为真。

- `if(<variable|string> STRLESS_EQUAL <variable|string>)`

  *3.7 版中的新功能：*如果给定字符串或变量的值按字典顺序小于或等于右侧的字符串或变量，则为真。

- `if(<variable|string> STRGREATER_EQUAL <variable|string>)`

  *3.7 新版功能：*如果给定字符串或变量的值在字典上大于或等于右侧的字符串或变量，则为真。

#### 版本比较

- `if(<variable|string> VERSION_LESS <variable|string>)`

  组件整数版本号比较（版本格式为 `major[.minor[.patch[.tweak]]]`，省略的组件被视为零）。任何非整数版本组件或版本组件的非整数尾随部分都会在该点有效地截断字符串。

- `if(<variable|string> VERSION_GREATER <variable|string>)`

  组件整数版本号比较（版本格式为 `major[.minor[.patch[.tweak]]]`，省略的组件被视为零）。任何非整数版本组件或版本组件的非整数尾随部分都会在该点有效地截断字符串。

- `if(<variable|string> VERSION_EQUAL <variable|string>)`

  组件整数版本号比较（版本格式为 `major[.minor[.patch[.tweak]]]`，省略的组件被视为零）。任何非整数版本组件或版本组件的非整数尾随部分都会在该点有效地截断字符串。

- `if(<variable|string> VERSION_LESS_EQUAL <variable|string>)`

  *3.7 版中的新功能：*组件方式的整数版本号比较（版本格式为 `major[.minor[.patch[.tweak]]]`，省略的组件被视为零）。任何非整数版本组件或版本组件的非整数尾随部分都会在该点有效地截断字符串。

- `if(<variable|string> VERSION_GREATER_EQUAL <variable|string>)`

  *3.7 版中的新功能：*组件方式的整数版本号比较（版本格式为 `major[.minor[.patch[.tweak]]]`，省略的组件被视为零）。任何非整数版本组件或版本组件的非整数尾随部分都会在该点有效地截断字符串。

#### 路径比较

- `if(<variable|string> PATH_EQUAL <variable|string>)`

  *版本 3.24 中的新功能。*逐个组件比较两个路径。只有当两条路径的每个组件都匹配时，两条路径才会比较相等。多个路径分隔符有效地折叠成一个分隔符，但请注意反斜杠不会转换为正斜杠。不执行其他 [路径规范化](https://cmake.org/cmake/help/latest/command/cmake_path.html#normalization)。由于对多个路径分隔符的处理，基于组件的比较优于基于字符串的比较。在以下示例中，表达式使用 计算为真`PATH_EQUAL`，但使用 计算为假 `STREQUAL`：`# comparison is TRUE if ("/a//b/c" PATH_EQUAL "/a/b/c")   ... endif() # comparison is FALSE if ("/a//b/c" STREQUAL "/a/b/c")   ... endif() `有关更多详细信息，请参见[cmake_path(COMPARE)](https://cmake.org/cmake/help/latest/command/cmake_path.html#path-compare)。

### 变量扩展

if 命令是在 CMake 历史的早期编写的，早于`${}`变量评估语法，为了方便起见，它评估由其参数命名的变量，如上述签名所示。请注意，`${}`在 if 命令甚至接收参数之前应用正常的变量评估。因此像这样的代码

```cmake
set(var1 OFF)
set(var2 "var1")
if(${var2})
```

在 if 命令中显示为

```cmake
if(var1)
```

并根据`if(<variable>)`上面记录的案例进行评估。结果`OFF`是错误的。但是，如果我们 `${}`从示例中删除 ，那么命令会看到

```cmake
if(var2)
```

这是真的，因为`var2`定义为`var1`which 不是假常数。

只要上述条件语法接受，自动评估就适用于其他情况`<variable|string>`：

- 首先检查左侧参数`MATCHES`是否为已定义变量，如果是，则使用变量的值，否则使用原始值。
- 如果左侧参数`MATCHES`丢失，则返回 false 且没有错误
- `LESS`, `GREATER`, `EQUAL`, `LESS_EQUAL`, 和, 的左右手参数`GREATER_EQUAL`都经过独立测试，以查看它们是否是定义的变量，如果是，则使用它们的定义值，否则使用原始值。
- `STRLESS`, `STRGREATER`, `STREQUAL`,`STRLESS_EQUAL`和的左右手参数`STRGREATER_EQUAL`都经过独立测试以查看它们是否是已定义的变量，如果是，则使用其定义的值，否则使用原始值。
- `VERSION_LESS`, `VERSION_GREATER`, `VERSION_EQUAL`,`VERSION_LESS_EQUAL`和 的左右手参数`VERSION_GREATER_EQUAL`都经过独立测试以查看它们是否是已定义的变量，如果是，则使用其定义的值，否则使用原始值。
- 测试右边的参数以`NOT`查看它是否是布尔常量，如果是则使用该值，否则假定它是一个变量并取消引用。
- `AND`和 的左手和右手参数`OR`被独立测试以查看它们是否是布尔常量，如果是，则将它们原样使用，否则它们被假定为变量并被取消引用。

*在 3.1 版更改：*为了防止歧义，可以在[Quoted Argument](https://cmake.org/cmake/help/latest/manual/cmake-language.7.html#quoted-argument)或[Bracket Argument](https://cmake.org/cmake/help/latest/manual/cmake-language.7.html#bracket-argument)中指定潜在的变量或关键字名称。带引号或括号的变量或关键字将被解释为字符串，不会被取消引用或解释。查看政策[`CMP0054`](https://cmake.org/cmake/help/latest/policy/CMP0054.html#policy:CMP0054).

[环境或缓存变量引用](https://cmake.org/cmake/help/latest/manual/cmake-language.7.html#variable-references)没有自动评估 。它们的值必须 在上述条件语法接受的地方`$ENV{<name>}`或任何地方引用。`$CACHE{<name>}``<variable|string>`



## [else](https://cmake.org/cmake/help/latest/command/else.html)

开始 if 块的 else 部分。

```cmake
else([<condition>])
```

见[`if()`](https://cmake.org/cmake/help/latest/command/if.html#command:if)命令。



## [elseif](https://cmake.org/cmake/help/latest/command/elseif.html)

开始 if 块的 elseif 部分。

```cmake
elseif(<condition>)
```

见[`if()`](https://cmake.org/cmake/help/latest/command/if.html#command:if)命令，尤其是对于`<condition>`.



## [endif](https://cmake.org/cmake/help/latest/command/endif.html)

结束 if 块中的命令列表。

```cmake
endif([<condition>])
```

见[`if()`](https://cmake.org/cmake/help/latest/command/if.html#command:if)命令。

支持可选`<condition>`参数仅是为了向后兼容。如果使用它，它必须是开头 `if`子句的论点的逐字重复。



# 循环语法

## [while](https://cmake.org/cmake/help/latest/command/while.html)

在条件为真时评估一组命令

```cmake
while(<condition>)
  <commands>
endwhile()
```

while 和匹配之间的所有命令[`endwhile()`](https://cmake.org/cmake/help/latest/command/endwhile.html#command:endwhile)被记录而不被调用。一旦[`endwhile()`](https://cmake.org/cmake/help/latest/command/endwhile.html#command:endwhile)被评估时，只要为`<condition>`真，就会调用记录的命令列表。

具有相同的`<condition>`语法，并且使用与详细描述的相同逻辑进行评估[`if()`](https://cmake.org/cmake/help/latest/command/if.html#command:if)命令。

命令[`break()`](https://cmake.org/cmake/help/latest/command/break.html#command:break)和[`continue()`](https://cmake.org/cmake/help/latest/command/continue.html#command:continue)提供脱离正常控制流的方法。

根据遗产，[`endwhile()`](https://cmake.org/cmake/help/latest/command/endwhile.html#command:endwhile)command 接受一个可选`<condition>`参数。如果使用，它必须是开头 `while`命令参数的逐字重复。



## [endwhile](https://cmake.org/cmake/help/latest/command/endwhile.html)

在 while 块中结束命令列表。

```cmake
endwhile([<condition>])
```

见[`while()`](https://cmake.org/cmake/help/latest/command/while.html#command:while)命令。

支持可选`<condition>`参数仅是为了向后兼容。如果使用它，它必须是开头 `while`子句的论点的逐字重复。



## [foreach](https://cmake.org/cmake/help/latest/command/foreach.html)

为列表中的每个值评估一组命令。

```cmake
foreach(<loop_var> <items>)
  <commands>
endforeach()
```

where`<items>`是由分号或空格分隔的项目列表。`foreach`记录和匹配之间的所有命令`endforeach`而不被调用。一旦`endforeach`被评估，记录的命令列表会为 中的每个项目调用一次`<items>`。在每次迭代开始时，变量`<loop_var>`将被设置为当前项的值。

的范围`<loop_var>`仅限于循环范围。查看政策 [`CMP0124`](https://cmake.org/cmake/help/latest/policy/CMP0124.html#policy:CMP0124)详情。

命令[`break()`](https://cmake.org/cmake/help/latest/command/break.html#command:break)和[`continue()`](https://cmake.org/cmake/help/latest/command/continue.html#command:continue)提供脱离正常控制流的方法。

根据遗产，[`endforeach()`](https://cmake.org/cmake/help/latest/command/endforeach.html#command:endforeach)command 接受一个可选`<loop_var>`参数。如果使用，它必须是开头 `foreach`命令参数的逐字重复。

```cmake
foreach(<loop_var> RANGE <stop>)
```

在这个变体中，`foreach`迭代数字 0, 1, ... 直到（包括）非负整数`<stop>`。

```cmake
foreach(<loop_var> RANGE <start> <stop> [<step>])
```

在这个变体中，`foreach`迭代数字从 `<start>`最多到最多`<stop>`以`<step>`. 如果`<step>`不指定，则步长为 1。三个参数`<start>` `<stop>` `<step>`必须都是非负整数，并且`<stop>`不能小于`<start>`；否则，您将进入可能在未来版本中更改的未记录行为的危险区域。

```cmake
foreach(<loop_var> IN [LISTS [<lists>]] [ITEMS [<items>]])
```

在这个变体中，`<lists>`是一个空格或分号分隔的列表值变量列表。该`foreach` 命令遍历每个给定列表中的每个项目。下面`<items>`的`ITEMS`关键字按照`foreach`命令的第一个变体进行处理。形式和是等价的。`LISTS A``ITEMS ${A}`

以下示例显示了如何`LISTS`处理选项：

```cmake
set(A 0;1)
set(B 2 3)
set(C "4 5")
set(D 6;7 8)
set(E "")
foreach(X IN LISTS A B C D E)
    message(STATUS "X=${X}")
endforeach()
```

产量

```cmake
-- X=0
-- X=1
-- X=2
-- X=3
-- X=4 5
-- X=6
-- X=7
-- X=8
foreach(<loop_var>... IN ZIP_LISTS <lists>)
```

*版本 3.17 中的新功能。*

在这个变体中，`<lists>`是一个空格或分号分隔的列表值变量列表。该`foreach` 命令同时迭代每个列表，设置迭代变量如下：

- 如果唯一`loop_var`给定，则将一系列 `loop_var_N`变量设置为相应列表中的当前项；
- 如果传递了多个变量名，则它们的计数应与列表变量计数匹配；
- 如果任何列表较短，则不会为当前迭代定义相应的迭代变量。

```cmake
list(APPEND English one two three four)
list(APPEND Bahasa satu dua tiga)

foreach(num IN ZIP_LISTS English Bahasa)
    message(STATUS "num_0=${num_0}, num_1=${num_1}")
endforeach()

foreach(en ba IN ZIP_LISTS English Bahasa)
    message(STATUS "en=${en}, ba=${ba}")
endforeach()
```

产量

```cmake
-- num_0=one, num_1=satu
-- num_0=two, num_1=dua
-- num_0=three, num_1=tiga
-- num_0=four, num_1=
-- en=one, ba=satu
-- en=two, ba=dua
-- en=three, ba=tiga
-- en=four, ba=
```



## [endforeach](https://cmake.org/cmake/help/latest/command/endforeach.html)

结束 foreach 块中的命令列表。

```cmake
endforeach([<loop_var>])
```

见[`foreach()`](https://cmake.org/cmake/help/latest/command/foreach.html#command:foreach)命令。

支持可选`<loop_var>`参数仅是为了向后兼容。如果使用它，它必须是开头子句的`<loop_var>`论点的逐字重复。`foreach`



## [break](https://cmake.org/cmake/help/latest/command/break.html)

从封闭的 foreach 或 while 循环中中断。

```cmake
break()
```

从封闭中断[`foreach()`](https://cmake.org/cmake/help/latest/command/foreach.html#command:foreach)或者[`while()`](https://cmake.org/cmake/help/latest/command/while.html#command:while)环形。

另见[`continue()`](https://cmake.org/cmake/help/latest/command/continue.html#command:continue)命令。



## [continue](https://cmake.org/cmake/help/latest/command/continue.html)

*3.2 版中的新功能。*

继续到封闭 foreach 或 while 循环的顶部。

```cmake
continue()
```

该`continue`命令允许 cmake 脚本中止块中的其余部分[`foreach()`](https://cmake.org/cmake/help/latest/command/foreach.html#command:foreach)或者[`while()`](https://cmake.org/cmake/help/latest/command/while.html#command:while)循环，并从下一次迭代的顶部开始。

另见[`break()`](https://cmake.org/cmake/help/latest/command/break.html#command:break)命令。




# 函数和宏

## [function](https://cmake.org/cmake/help/latest/command/function.html)

开始记录一个函数以供以后调用为命令。

```cmake
function(<name> [<arg1> ...])
  <commands>
endfunction()
```

定义一个名为的函数`<name>`，它接受名为 `<arg1>`, ... 的参数，`<commands>`函数定义中的 被记录；在调用函数之前，它们不会被执行。

根据遗产，[`endfunction()`](https://cmake.org/cmake/help/latest/command/endfunction.html#command:endfunction)command 接受一个可选 `<name>`参数。如果使用，它必须是开头`function`命令参数的逐字重复。

一个函数打开一个新的作用域：见[`set(var PARENT_SCOPE)`](https://cmake.org/cmake/help/latest/command/set.html#command:set)详情。

见[`cmake_policy()`](https://cmake.org/cmake/help/latest/command/cmake_policy.html#command:cmake_policy)函数内部策略行为的命令文档。

见[`macro()`](https://cmake.org/cmake/help/latest/command/macro.html#command:macro)CMake 函数和宏之间差异的命令文档。

### Invocation

函数调用不区分大小写。一个函数定义为

```cmake
function(foo)
  <commands>
endfunction()
```

可以通过任何调用

```cmake
foo()
Foo()
FOO()
cmake_language(CALL foo)
```

等等。但是，强烈建议保留函数定义中选择的情况。通常函数使用全小写的名称。

*3.18 版中*的新功能：[`cmake_language(CALL ...)`](https://cmake.org/cmake/help/latest/command/cmake_language.html#command:cmake_language)命令也可用于调用该函数。

### Arguments

调用函数时，`<commands>`首先通过将形式参数 ( `${arg1}`, ...) 替换为传递的参数来修改记录，然后作为普通命令调用。

除了引用形式参数之外，您还可以引用 `ARGC`将设置为传递给函数的参数数量的变量以及`ARGV0`, `ARGV1`, `ARGV2`, ... 这将具有传入参数的实际值。这有助于创建函数带有可选参数。

此外，`ARGV`保存给函数的所有参数列表，并`ARGN`保存最后一个预期参数之后的参数列表。引用`ARGV#`超出的参数`ARGC`具有未定义的行为。检查`ARGC`大于是`#`确保`ARGV#`作为额外参数传递给函数的唯一方法。



## [endfunction](https://cmake.org/cmake/help/latest/command/endfunction.html)

结束功能块中的命令列表。

```cmake
endfunction([<name>])
```

见[`function()`](https://cmake.org/cmake/help/latest/command/function.html#command:function)命令。

支持可选`<name>`参数仅是为了向后兼容。如果使用，它必须是开始命令`<name>`参数的逐字重复。`function`



## [macro](https://cmake.org/cmake/help/latest/command/macro.html)

开始录制宏以供以后作为命令调用

```cmake
macro(<name> [<arg1> ...])
  <commands>
endmacro()
```

定义一个名为的宏`<name>`，它接受名为 `<arg1>`, ... 的参数 在宏之后但匹配之前列出的命令[`endmacro()`](https://cmake.org/cmake/help/latest/command/endmacro.html#command:endmacro), 在调用宏之前不会执行。

根据遗产，[`endmacro()`](https://cmake.org/cmake/help/latest/command/endmacro.html#command:endmacro)command 接受一个可选 `<name>`参数。如果使用，它必须是开头`macro`命令参数的逐字重复。

见[`cmake_policy()`](https://cmake.org/cmake/help/latest/command/cmake_policy.html#command:cmake_policy)宏内部策略行为的命令文档。

请参阅下面的[宏与函数](https://cmake.org/cmake/help/latest/command/macro.html#macro-vs-function)部分，了解 CMake 宏和[`functions`](https://cmake.org/cmake/help/latest/command/function.html#command:function).

### Invocation

宏调用不区分大小写。一个宏定义为

```cmake
macro(foo)
  <commands>
endmacro()
```

可以通过任何调用

```cmake
foo()
Foo()
FOO()
cmake_language(CALL foo)
```

等等。但是，强烈建议保留在宏定义中选择的情况。通常宏使用全小写的名称。

*3.18 版中*的新功能：[`cmake_language(CALL ...)`](https://cmake.org/cmake/help/latest/command/cmake_language.html#command:cmake_language)命令也可用于调用宏。

### Arguments

调用宏时，宏中记录的命令首先通过将形式参数 ( `${arg1}`, ...) 替换为传递的参数进行修改，然后作为普通命令调用。

除了引用形式参数之外，您还可以引用`${ARGC}`将设置为传递给函数的参数数量的值，以及`${ARGV0}`将`${ARGV1}`具有`${ARGV2}`传入参数的实际值的值。这有助于创建宏带有可选参数。

此外，`${ARGV}`保存给宏的所有参数列表，并`${ARGN}`保存最后一个预期参数之后的参数列表。引用`${ARGV#}`超出的参数`${ARGC}`具有未定义的行为。检查`${ARGC}`大于是`#`确保`${ARGV#}`作为额外参数传递给函数的唯一方法。



### 宏与函数

该`macro`命令非常类似于[`function()`](https://cmake.org/cmake/help/latest/command/function.html#command:function)命令。尽管如此，还是有一些重要的区别。

在函数中，`ARGN`, `ARGC`,`ARGV`和`ARGV0`, `ARGV1`, ... 是通常 CMake 意义上的真实变量。在宏中，它们不是，它们是字符串替换，就像 C 预处理器对宏所做的那样。这会产生许多后果，如下面的[参数注意事项](https://cmake.org/cmake/help/latest/command/macro.html#argument-caveats)部分所述。

宏和函数之间的另一个区别是控制流。通过将控制从调用语句转移到函数体来执行函数。宏的执行就像宏体被粘贴在调用语句的位置一样。这会导致一个[`return()`](https://cmake.org/cmake/help/latest/command/return.html#command:return)在宏体中不仅仅终止宏的执行；相反，控制是从宏调用的范围内返回的。为避免混淆，建议避免[`return()`](https://cmake.org/cmake/help/latest/command/return.html#command:return)完全在宏中。

与函数不同，[`CMAKE_CURRENT_FUNCTION`](https://cmake.org/cmake/help/latest/variable/CMAKE_CURRENT_FUNCTION.html#variable:CMAKE_CURRENT_FUNCTION), [`CMAKE_CURRENT_FUNCTION_LIST_DIR`](https://cmake.org/cmake/help/latest/variable/CMAKE_CURRENT_FUNCTION_LIST_DIR.html#variable:CMAKE_CURRENT_FUNCTION_LIST_DIR), [`CMAKE_CURRENT_FUNCTION_LIST_FILE`](https://cmake.org/cmake/help/latest/variable/CMAKE_CURRENT_FUNCTION_LIST_FILE.html#variable:CMAKE_CURRENT_FUNCTION_LIST_FILE), [`CMAKE_CURRENT_FUNCTION_LIST_LINE`](https://cmake.org/cmake/help/latest/variable/CMAKE_CURRENT_FUNCTION_LIST_LINE.html#variable:CMAKE_CURRENT_FUNCTION_LIST_LINE)未为宏设置变量。



### 参数注意事项

由于`ARGN`, `ARGC`,`ARGV`等`ARGV0`不是变量，因此您将无法使用类似的命令

```cmake
if(ARGV1) # ARGV1 is not a variable
if(DEFINED ARGV2) # ARGV2 is not a variable
if(ARGC GREATER 2) # ARGC is not a variable
foreach(loop_var IN LISTS ARGN) # ARGN is not a variable
```

在第一种情况下，您可以使用`if(${ARGV1})`. 在第二种和第三种情况下，检查是否将可选变量传递给宏的正确方法是使用. 在最后一种情况下，您可以使用，但这会跳过空参数。如果您需要包含它们，您可以使用`if(${ARGC} GREATER 2)``foreach(loop_var ${ARGN})`

```cmake
set(list_var "${ARGN}")
foreach(loop_var IN LISTS list_var)
```

请注意，如果在调用宏的范围内有一个同名的变量，则使用未引用的名称将使用现有变量而不是参数。例如：

```cmake
macro(bar)
  foreach(arg IN LISTS ARGN)
    <commands>
  endforeach()
endmacro()

function(foo)
  bar(x y z)
endfunction()

foo(a b c)
```

将循环`a;b;c`而不是`x;y;z`像预期的那样循环。如果您想要真正的 CMake 变量和/或更好的 CMake 范围控制，您应该查看 function 命令。



## [endmacro](https://cmake.org/cmake/help/latest/command/endmacro.html)

结束宏块中的命令列表。

```cmake
endmacro([<name>])
```

见[`macro()`](https://cmake.org/cmake/help/latest/command/macro.html#command:macro)命令。

支持可选`<name>`参数仅是为了向后兼容。如果使用，它必须是开始命令`<name>`参数的逐字重复。`macro`



## [return](https://cmake.org/cmake/help/latest/command/return.html)

从文件、目录或函数返回。

```cmake
return()
```

从文件、目录或函数返回。当在包含文件中遇到此命令时（通过[`include()`](https://cmake.org/cmake/help/latest/command/include.html#command:include)或者 [`find_package()`](https://cmake.org/cmake/help/latest/command/find_package.html#command:find_package))，它会导致当前文件的处理停止并将控制权返回到包含文件。如果在另一个文件不包含的文件中遇到它，例如 a `CMakeLists.txt`，延迟调用由[`cmake_language(DEFER)`](https://cmake.org/cmake/help/latest/command/cmake_language.html#command:cmake_language)被调用并且控制返回到父目录，如果有的话。如果在函数中调用 return，则控制权返回给函数的调用者。

请注意，一个[`macro`](https://cmake.org/cmake/help/latest/command/macro.html#command:macro), 不像[`function`](https://cmake.org/cmake/help/latest/command/function.html#command:function), 已扩展到位，因此无法处理`return()`。




# 查找语法

## [find_file](https://cmake.org/cmake/help/latest/command/find_file.html)

速记签名是：

```cmake
find_file (<VAR> name1 [path1 path2 ...])
```

一般签名是：

```cmake
find_file (
          <VAR>
          name | NAMES name1 [name2 ...]
          [HINTS [path | ENV var]... ]
          [PATHS [path | ENV var]... ]
          [REGISTRY_VIEW (64|32|64_32|32_64|HOST|TARGET|BOTH)]
          [PATH_SUFFIXES suffix1 [suffix2 ...]]
          [DOC "cache documentation string"]
          [NO_CACHE]
          [REQUIRED]
          [NO_DEFAULT_PATH]
          [NO_PACKAGE_ROOT_PATH]
          [NO_CMAKE_PATH]
          [NO_CMAKE_ENVIRONMENT_PATH]
          [NO_SYSTEM_ENVIRONMENT_PATH]
          [NO_CMAKE_SYSTEM_PATH]
          [NO_CMAKE_INSTALL_PREFIX]
          [CMAKE_FIND_ROOT_PATH_BOTH |
           ONLY_CMAKE_FIND_ROOT_PATH |
           NO_CMAKE_FIND_ROOT_PATH]
         )
```

此命令用于查找命名文件的完整路径。一个缓存条目，或者一个普通变量，如果`NO_CACHE`指定的话，`<VAR>`被创建来存储这个命令的结果。如果找到文件的完整路径，则结果将存储在变量中，除非清除变量，否则不会重复搜索。如果什么都没找到，结果将是`<VAR>-NOTFOUND`。

选项包括：

- `NAMES`

  为文件的完整路径指定一个或多个可能的名称。当使用它来指定带有和不带版本后缀的名称时，我们建议首先指定未版本化的名称，以便在发行版提供的包之前可以找到本地构建的包。

- `HINTS`, `PATHS`

  除默认位置外，还指定要搜索的目录。子选项从系统环境变量中读取路径。`ENV var`*在 3.24 版更改:*在平台上，可以使用[专用语法](https://cmake.org/cmake/help/latest/manual/cmake-developer.7.html#find-using-windows-registry)`Windows`将注册表查询作为目录的一部分。在所有其他平台上，此类规范将被忽略。

- `REGISTRY_VIEW`

  *版本 3.24 中的新功能。*指定必须查询哪些注册表视图。此选项仅在平台上有意义，`Windows`在其他平台上将被忽略。如果未指定，`TARGET`则在以下情况下使用视图[`CMP0134`](https://cmake.org/cmake/help/latest/policy/CMP0134.html#policy:CMP0134) 政策是`NEW`。参考[`CMP0134`](https://cmake.org/cmake/help/latest/policy/CMP0134.html#policy:CMP0134)策略为`OLD`或未定义时的默认视图。`64`查询 64 位注册表。开启时，始终返回字符串 。`32bit Windows``/REGISTRY-NOTFOUND``32`查询 32 位注册表。`64_32`查询两个视图 (`64`和`32`) 并为每个视图生成一个路径。`32_64`查询两个视图 (`32`和`64`) 并为每个视图生成一个路径。`HOST`查询与主机架构匹配的注册表：`64`on和on 。`64bit Windows``32``32bit Windows``TARGET`查询与指定架构匹配的注册表 [`CMAKE_SIZEOF_VOID_P`](https://cmake.org/cmake/help/latest/variable/CMAKE_SIZEOF_VOID_P.html#variable:CMAKE_SIZEOF_VOID_P)多变的。如果未定义，则回退到 `HOST`查看。`BOTH`查询两个视图（`32`和`64`）。顺序取决于以下规则：如果[`CMAKE_SIZEOF_VOID_P`](https://cmake.org/cmake/help/latest/variable/CMAKE_SIZEOF_VOID_P.html#variable:CMAKE_SIZEOF_VOID_P)变量被定义。根据此变量的内容使用以下视图：`8`: `64_32``4`:`32_64`如果[`CMAKE_SIZEOF_VOID_P`](https://cmake.org/cmake/help/latest/variable/CMAKE_SIZEOF_VOID_P.html#variable:CMAKE_SIZEOF_VOID_P)变量未定义，依赖于主机的架构：`64bit`:`64_32``32bit`:`32`

- `PATH_SUFFIXES`

  指定其他子目录以在每个目录位置下方检查，否则会考虑。

- `DOC`

  指定`<VAR>`缓存条目的文档字符串。

- `NO_CACHE`

  *3.21 版中的新功能。*搜索结果将存储在普通变量而不是缓存条目中。

  > **笔记** 如果在调用之前已经设置了变量（作为普通变量或缓存变量），则不会发生搜索。
  >
  > **警告** 应谨慎使用此选项，因为它会大大增加重复配置步骤的成本。

- `REQUIRED`

  *3.18 版中的新功能。*如果未找到任何内容，则停止处理并显示错误消息，否则将在下次使用相同变量调用 find_file 时再次尝试搜索。

如果`NO_DEFAULT_PATH`指定，则不会将其他路径添加到搜索中。如果`NO_DEFAULT_PATH`不指定，则搜索过程如下：

1. *3.12 版中的新功能：*如果从查找模块或通过调用加载的任何其他脚本中调用 [`find_package()`](https://cmake.org/cmake/help/latest/command/find_package.html#command:find_package), 搜索对当前找到的包唯一的前缀。具体来说，查看 [`_ROOT`](https://cmake.org/cmake/help/latest/variable/PackageName_ROOT.html#variable:_ROOT)CMake 变量和 [`_ROOT`](https://cmake.org/cmake/help/latest/envvar/PackageName_ROOT.html#envvar:_ROOT)环境变量。包根变量作为堆栈维护，因此如果从嵌套的查找模块或配置包中调用，则将在当前模块或包的路径之后搜索来自父查找模块或配置包的根路径。换句话说，搜索顺序将是 `<CurrentPackage>_ROOT`, `ENV{<CurrentPackage>_ROOT}`, `<ParentPackage>_ROOT`, `ENV{<ParentPackage>_ROOT}`, 等等。如果`NO_PACKAGE_ROOT_PATH`通过或通过设置[`CMAKE_FIND_USE_PACKAGE_ROOT_PATH`](https://cmake.org/cmake/help/latest/variable/CMAKE_FIND_USE_PACKAGE_ROOT_PATH.html#variable:CMAKE_FIND_USE_PACKAGE_ROOT_PATH)到`FALSE`. 查看政策[`CMP0074`](https://cmake.org/cmake/help/latest/policy/CMP0074.html#policy:CMP0074).

   - `<prefix>/include/<arch>`如果[`CMAKE_LIBRARY_ARCHITECTURE`](https://cmake.org/cmake/help/latest/variable/CMAKE_LIBRARY_ARCHITECTURE.html#variable:CMAKE_LIBRARY_ARCHITECTURE) 被设置，并且对于 `<prefix>/include`每个`<prefix>`[`_ROOT`](https://cmake.org/cmake/help/latest/variable/PackageName_ROOT.html#variable:_ROOT)CMake 变量和 [`_ROOT`](https://cmake.org/cmake/help/latest/envvar/PackageName_ROOT.html#envvar:_ROOT)如果从加载的查找模块中调用环境变量 [`find_package()`](https://cmake.org/cmake/help/latest/command/find_package.html#command:find_package)

2. 在特定于 cmake 的缓存变量中指定的搜索路径。这些旨在用于带有`-DVAR=value`. 这些值被解释为[分号分隔的列表](https://cmake.org/cmake/help/latest/manual/cmake-language.7.html#cmake-language-lists)。如果`NO_CMAKE_PATH`通过或通过设置 [`CMAKE_FIND_USE_CMAKE_PATH`](https://cmake.org/cmake/help/latest/variable/CMAKE_FIND_USE_CMAKE_PATH.html#variable:CMAKE_FIND_USE_CMAKE_PATH)到`FALSE`.

   - `<prefix>/include/<arch>`如果[`CMAKE_LIBRARY_ARCHITECTURE`](https://cmake.org/cmake/help/latest/variable/CMAKE_LIBRARY_ARCHITECTURE.html#variable:CMAKE_LIBRARY_ARCHITECTURE) 被设置，并且`<prefix>/include`对于每个`<prefix>`在[`CMAKE_PREFIX_PATH`](https://cmake.org/cmake/help/latest/variable/CMAKE_PREFIX_PATH.html#variable:CMAKE_PREFIX_PATH)
   - [`CMAKE_INCLUDE_PATH`](https://cmake.org/cmake/help/latest/variable/CMAKE_INCLUDE_PATH.html#variable:CMAKE_INCLUDE_PATH)
   - [`CMAKE_FRAMEWORK_PATH`](https://cmake.org/cmake/help/latest/variable/CMAKE_FRAMEWORK_PATH.html#variable:CMAKE_FRAMEWORK_PATH)

3. 在特定于 cmake 的环境变量中指定的搜索路径。这些旨在在用户的 shell 配置中设置，因此使用主机的本机路径分隔符（`;`在 Windows 和`:`UNIX 上）。如果`NO_CMAKE_ENVIRONMENT_PATH`通过或通过设置[`CMAKE_FIND_USE_CMAKE_ENVIRONMENT_PATH`](https://cmake.org/cmake/help/latest/variable/CMAKE_FIND_USE_CMAKE_ENVIRONMENT_PATH.html#variable:CMAKE_FIND_USE_CMAKE_ENVIRONMENT_PATH)到`FALSE`.

   - `<prefix>/include/<arch>`如果[`CMAKE_LIBRARY_ARCHITECTURE`](https://cmake.org/cmake/help/latest/variable/CMAKE_LIBRARY_ARCHITECTURE.html#variable:CMAKE_LIBRARY_ARCHITECTURE) 被设置，并且`<prefix>/include`对于每个`<prefix>`在[`CMAKE_PREFIX_PATH`](https://cmake.org/cmake/help/latest/variable/CMAKE_PREFIX_PATH.html#variable:CMAKE_PREFIX_PATH)
   - [`CMAKE_INCLUDE_PATH`](https://cmake.org/cmake/help/latest/variable/CMAKE_INCLUDE_PATH.html#variable:CMAKE_INCLUDE_PATH)
   - [`CMAKE_FRAMEWORK_PATH`](https://cmake.org/cmake/help/latest/variable/CMAKE_FRAMEWORK_PATH.html#variable:CMAKE_FRAMEWORK_PATH)

4. 搜索选项指定的路径`HINTS`。这些应该是系统自省计算的路径，例如已找到的另一个项目的位置提供的提示。应使用该`PATHS`选项指定硬编码猜测。

5. 搜索标准系统环境变量。如果`NO_SYSTEM_ENVIRONMENT_PATH`通过或通过设置[`CMAKE_FIND_USE_SYSTEM_ENVIRONMENT_PATH`](https://cmake.org/cmake/help/latest/variable/CMAKE_FIND_USE_SYSTEM_ENVIRONMENT_PATH.html#variable:CMAKE_FIND_USE_SYSTEM_ENVIRONMENT_PATH)到`FALSE`.

   - `INCLUDE` 和中的目录`PATH`。
   - 在 Windows 主机上： `<prefix>/include/<arch>`如果[`CMAKE_LIBRARY_ARCHITECTURE`](https://cmake.org/cmake/help/latest/variable/CMAKE_LIBRARY_ARCHITECTURE.html#variable:CMAKE_LIBRARY_ARCHITECTURE) 已设置，并且对于中`<prefix>/include`的每个条目，以及 对于 中的其他条目。`<prefix>/[s]bin``PATH``<entry>/include``PATH`

6. 搜索当前系统的 Platform 文件中定义的 cmake 变量。如果`CMAKE_INSTALL_PREFIX`通过`NO_CMAKE_INSTALL_PREFIX`或通过设置 [`CMAKE_FIND_USE_INSTALL_PREFIX`](https://cmake.org/cmake/help/latest/variable/CMAKE_FIND_USE_INSTALL_PREFIX.html#variable:CMAKE_FIND_USE_INSTALL_PREFIX)到`FALSE`. 如果`NO_CMAKE_SYSTEM_PATH`通过或通过设置 [`CMAKE_FIND_USE_CMAKE_SYSTEM_PATH`](https://cmake.org/cmake/help/latest/variable/CMAKE_FIND_USE_CMAKE_SYSTEM_PATH.html#variable:CMAKE_FIND_USE_CMAKE_SYSTEM_PATH)到`FALSE`.

   - `<prefix>/include/<arch>`如果[`CMAKE_LIBRARY_ARCHITECTURE`](https://cmake.org/cmake/help/latest/variable/CMAKE_LIBRARY_ARCHITECTURE.html#variable:CMAKE_LIBRARY_ARCHITECTURE) 被设置，并且`<prefix>/include`对于每个`<prefix>`在 [`CMAKE_SYSTEM_PREFIX_PATH`](https://cmake.org/cmake/help/latest/variable/CMAKE_SYSTEM_PREFIX_PATH.html#variable:CMAKE_SYSTEM_PREFIX_PATH)
   - [`CMAKE_SYSTEM_INCLUDE_PATH`](https://cmake.org/cmake/help/latest/variable/CMAKE_SYSTEM_INCLUDE_PATH.html#variable:CMAKE_SYSTEM_INCLUDE_PATH)
   - [`CMAKE_SYSTEM_FRAMEWORK_PATH`](https://cmake.org/cmake/help/latest/variable/CMAKE_SYSTEM_FRAMEWORK_PATH.html#variable:CMAKE_SYSTEM_FRAMEWORK_PATH)

   这些变量包含的平台路径是通常包含已安装软件的位置。一个例子是`/usr/local`基于 UNIX 的平台。

7. 搜索由 PATHS 选项或命令的简写版本指定的路径。这些通常是硬编码的猜测。

这[`CMAKE_IGNORE_PATH`](https://cmake.org/cmake/help/latest/variable/CMAKE_IGNORE_PATH.html#variable:CMAKE_IGNORE_PATH), [`CMAKE_IGNORE_PREFIX_PATH`](https://cmake.org/cmake/help/latest/variable/CMAKE_IGNORE_PREFIX_PATH.html#variable:CMAKE_IGNORE_PREFIX_PATH), [`CMAKE_SYSTEM_IGNORE_PATH`](https://cmake.org/cmake/help/latest/variable/CMAKE_SYSTEM_IGNORE_PATH.html#variable:CMAKE_SYSTEM_IGNORE_PATH)和 [`CMAKE_SYSTEM_IGNORE_PREFIX_PATH`](https://cmake.org/cmake/help/latest/variable/CMAKE_SYSTEM_IGNORE_PREFIX_PATH.html#variable:CMAKE_SYSTEM_IGNORE_PREFIX_PATH)变量也可能导致上述某些位置被忽略。

*3.16 版中的新功能：*添加`CMAKE_FIND_USE_<CATEGORY>_PATH`了全局禁用各种搜索位置的变量。

在 macOS 上[`CMAKE_FIND_FRAMEWORK`](https://cmake.org/cmake/help/latest/variable/CMAKE_FIND_FRAMEWORK.html#variable:CMAKE_FIND_FRAMEWORK)和 [`CMAKE_FIND_APPBUNDLE`](https://cmake.org/cmake/help/latest/variable/CMAKE_FIND_APPBUNDLE.html#variable:CMAKE_FIND_APPBUNDLE)变量决定了 Apple 风格和 unix 风格的包组件之间的优先顺序。

CMake 变量[`CMAKE_FIND_ROOT_PATH`](https://cmake.org/cmake/help/latest/variable/CMAKE_FIND_ROOT_PATH.html#variable:CMAKE_FIND_ROOT_PATH)指定要附加到所有其他搜索目录的一个或多个目录。这有效地“重新扎根”了给定位置下的整个搜索。路径的后代[`CMAKE_STAGING_PREFIX`](https://cmake.org/cmake/help/latest/variable/CMAKE_STAGING_PREFIX.html#variable:CMAKE_STAGING_PREFIX)被排除在此重新生根之外，因为该变量始终是主机系统上的路径。默认情况下[`CMAKE_FIND_ROOT_PATH`](https://cmake.org/cmake/help/latest/variable/CMAKE_FIND_ROOT_PATH.html#variable:CMAKE_FIND_ROOT_PATH)是空的。

这[`CMAKE_SYSROOT`](https://cmake.org/cmake/help/latest/variable/CMAKE_SYSROOT.html#variable:CMAKE_SYSROOT)变量也可以用来指定一个目录作为前缀。环境[`CMAKE_SYSROOT`](https://cmake.org/cmake/help/latest/variable/CMAKE_SYSROOT.html#variable:CMAKE_SYSROOT)还有其他作用。有关更多信息，请参阅该变量的文档。

这些变量在交叉编译指向目标环境的根目录时特别有用，CMake 也会在那里搜索。默认情况下，首先列出的目录 [`CMAKE_FIND_ROOT_PATH`](https://cmake.org/cmake/help/latest/variable/CMAKE_FIND_ROOT_PATH.html#variable:CMAKE_FIND_ROOT_PATH)被搜索，然后[`CMAKE_SYSROOT`](https://cmake.org/cmake/help/latest/variable/CMAKE_SYSROOT.html#variable:CMAKE_SYSROOT) 搜索目录，然后将搜索非根目录。默认行为可以通过设置来调整 [`CMAKE_FIND_ROOT_PATH_MODE_INCLUDE`](https://cmake.org/cmake/help/latest/variable/CMAKE_FIND_ROOT_PATH_MODE_INCLUDE.html#variable:CMAKE_FIND_ROOT_PATH_MODE_INCLUDE). 可以使用以下选项在每次调用的基础上手动覆盖此行为：

- `CMAKE_FIND_ROOT_PATH_BOTH`

  按上述顺序搜索。

- `NO_CMAKE_FIND_ROOT_PATH`

  不要使用[`CMAKE_FIND_ROOT_PATH`](https://cmake.org/cmake/help/latest/variable/CMAKE_FIND_ROOT_PATH.html#variable:CMAKE_FIND_ROOT_PATH)多变的。

- `ONLY_CMAKE_FIND_ROOT_PATH`

  仅搜索以下重新植根的目录和目录 [`CMAKE_STAGING_PREFIX`](https://cmake.org/cmake/help/latest/variable/CMAKE_STAGING_PREFIX.html#variable:CMAKE_STAGING_PREFIX).

默认搜索顺序旨在针对常见用例从最具体到最不具体。项目可以通过简单地多次调用命令并使用`NO_*`选项来覆盖顺序：

```cmake
find_file (<VAR> NAMES name PATHS 路径... NO_DEFAULT_PATH)
find_file (<VAR> NAMES 名称)
```

一旦其中一个调用成功，结果变量将被设置并存储在缓存中，这样就不会再次搜索调用。



## [find_library](https://cmake.org/cmake/help/latest/command/find_library.html)

速记签名是：

```cmake
find_library (<VAR> name1 [path1 path2 ...])
```

一般签名是：

```cmake
find_library (
          <VAR>
          name | NAMES name1 [name2 ...] [NAMES_PER_DIR]
          [HINTS [path | ENV var]... ]
          [PATHS [path | ENV var]... ]
          [REGISTRY_VIEW (64|32|64_32|32_64|HOST|TARGET|BOTH)]
          [PATH_SUFFIXES suffix1 [suffix2 ...]]
          [DOC "cache documentation string"]
          [NO_CACHE]
          [REQUIRED]
          [NO_DEFAULT_PATH]
          [NO_PACKAGE_ROOT_PATH]
          [NO_CMAKE_PATH]
          [NO_CMAKE_ENVIRONMENT_PATH]
          [NO_SYSTEM_ENVIRONMENT_PATH]
          [NO_CMAKE_SYSTEM_PATH]
          [NO_CMAKE_INSTALL_PREFIX]
          [CMAKE_FIND_ROOT_PATH_BOTH |
           ONLY_CMAKE_FIND_ROOT_PATH |
           NO_CMAKE_FIND_ROOT_PATH]
         )
```

该命令用于查找库。一个缓存条目，或者一个普通变量，如果`NO_CACHE`指定的话，`<VAR>`被创建来存储这个命令的结果。如果找到库，则结果将存储在变量中，并且除非清除变量，否则不会重复搜索。如果什么都没找到，结果将是`<VAR>-NOTFOUND`。

选项包括：

- `NAMES`

  为库指定一个或多个可能的名称。当使用它来指定带有和不带版本后缀的名称时，我们建议首先指定未版本化的名称，以便在发行版提供的包之前可以找到本地构建的包。

- `HINTS`, `PATHS`

  除默认位置外，还指定要搜索的目录。子选项从系统环境变量中读取路径。`ENV var`*在 3.24 版更改:*在平台上，可以使用[专用语法](https://cmake.org/cmake/help/latest/manual/cmake-developer.7.html#find-using-windows-registry)`Windows`将注册表查询作为目录的一部分。在所有其他平台上，此类规范将被忽略。

- `REGISTRY_VIEW`

  *版本 3.24 中的新功能。*指定必须查询哪些注册表视图。此选项仅在平台上有意义，`Windows`在其他平台上将被忽略。如果未指定，`TARGET`则在以下情况下使用视图[`CMP0134`](https://cmake.org/cmake/help/latest/policy/CMP0134.html#policy:CMP0134) 政策是`NEW`。参考[`CMP0134`](https://cmake.org/cmake/help/latest/policy/CMP0134.html#policy:CMP0134)策略为`OLD`或未定义时的默认视图。`64`查询 64 位注册表。开启时，始终返回字符串 。`32bit Windows``/REGISTRY-NOTFOUND``32`查询 32 位注册表。`64_32`查询两个视图 (`64`和`32`) 并为每个视图生成一个路径。`32_64`查询两个视图 (`32`和`64`) 并为每个视图生成一个路径。`HOST`查询与主机架构匹配的注册表：`64`on和on 。`64bit Windows``32``32bit Windows``TARGET`查询与指定架构匹配的注册表 [`CMAKE_SIZEOF_VOID_P`](https://cmake.org/cmake/help/latest/variable/CMAKE_SIZEOF_VOID_P.html#variable:CMAKE_SIZEOF_VOID_P)多变的。如果未定义，则回退到 `HOST`查看。`BOTH`查询两个视图（`32`和`64`）。顺序取决于以下规则：如果[`CMAKE_SIZEOF_VOID_P`](https://cmake.org/cmake/help/latest/variable/CMAKE_SIZEOF_VOID_P.html#variable:CMAKE_SIZEOF_VOID_P)变量被定义。根据此变量的内容使用以下视图：`8`: `64_32``4`:`32_64`如果[`CMAKE_SIZEOF_VOID_P`](https://cmake.org/cmake/help/latest/variable/CMAKE_SIZEOF_VOID_P.html#variable:CMAKE_SIZEOF_VOID_P)变量未定义，依赖于主机的架构：`64bit`:`64_32``32bit`:`32`

- `PATH_SUFFIXES`

  指定其他子目录以在每个目录位置下方检查，否则会考虑。

- `DOC`

  指定`<VAR>`缓存条目的文档字符串。

- `NO_CACHE`

  *3.21 版中的新功能。*搜索结果将存储在普通变量而不是缓存条目中。

  > **笔记** 如果在调用之前已经设置了变量（作为普通变量或缓存变量），则不会发生搜索。
  >
  > **警告** 应谨慎使用此选项，因为它会大大增加重复配置步骤的成本。

- `REQUIRED`

  *3.18 版中的新功能。*如果未找到任何内容，则停止处理并显示错误消息，否则将在下次使用相同变量调用 find_library 时再次尝试搜索。

如果`NO_DEFAULT_PATH`指定，则不会将其他路径添加到搜索中。如果`NO_DEFAULT_PATH`不指定，则搜索过程如下：

1. *3.12 版中的新功能：*如果从查找模块或通过调用加载的任何其他脚本中调用 [`find_package()`](https://cmake.org/cmake/help/latest/command/find_package.html#command:find_package), 搜索对当前找到的包唯一的前缀。具体来说，查看 [`_ROOT`](https://cmake.org/cmake/help/latest/variable/PackageName_ROOT.html#variable:_ROOT)CMake 变量和 [`_ROOT`](https://cmake.org/cmake/help/latest/envvar/PackageName_ROOT.html#envvar:_ROOT)环境变量。包根变量作为堆栈维护，因此如果从嵌套的查找模块或配置包中调用，则将在当前模块或包的路径之后搜索来自父查找模块或配置包的根路径。换句话说，搜索顺序将是 `<CurrentPackage>_ROOT`, `ENV{<CurrentPackage>_ROOT}`, `<ParentPackage>_ROOT`, `ENV{<ParentPackage>_ROOT}`, 等等。如果`NO_PACKAGE_ROOT_PATH`通过或通过设置[`CMAKE_FIND_USE_PACKAGE_ROOT_PATH`](https://cmake.org/cmake/help/latest/variable/CMAKE_FIND_USE_PACKAGE_ROOT_PATH.html#variable:CMAKE_FIND_USE_PACKAGE_ROOT_PATH)到`FALSE`. 查看政策[`CMP0074`](https://cmake.org/cmake/help/latest/policy/CMP0074.html#policy:CMP0074).

   - `<prefix>/lib/<arch>`如果[`CMAKE_LIBRARY_ARCHITECTURE`](https://cmake.org/cmake/help/latest/variable/CMAKE_LIBRARY_ARCHITECTURE.html#variable:CMAKE_LIBRARY_ARCHITECTURE)被设置，并且对于 `<prefix>/lib`每个`<prefix>`[`_ROOT`](https://cmake.org/cmake/help/latest/variable/PackageName_ROOT.html#variable:_ROOT)CMake 变量和 [`_ROOT`](https://cmake.org/cmake/help/latest/envvar/PackageName_ROOT.html#envvar:_ROOT)如果从加载的查找模块中调用环境变量 [`find_package()`](https://cmake.org/cmake/help/latest/command/find_package.html#command:find_package)

2. 在特定于 cmake 的缓存变量中指定的搜索路径。这些旨在用于带有`-DVAR=value`. 这些值被解释为[分号分隔的列表](https://cmake.org/cmake/help/latest/manual/cmake-language.7.html#cmake-language-lists)。如果`NO_CMAKE_PATH`通过或通过设置 [`CMAKE_FIND_USE_CMAKE_PATH`](https://cmake.org/cmake/help/latest/variable/CMAKE_FIND_USE_CMAKE_PATH.html#variable:CMAKE_FIND_USE_CMAKE_PATH)到`FALSE`.

   - `<prefix>/lib/<arch>`如果[`CMAKE_LIBRARY_ARCHITECTURE`](https://cmake.org/cmake/help/latest/variable/CMAKE_LIBRARY_ARCHITECTURE.html#variable:CMAKE_LIBRARY_ARCHITECTURE)被设置，并且`<prefix>/lib`对于每个`<prefix>`在[`CMAKE_PREFIX_PATH`](https://cmake.org/cmake/help/latest/variable/CMAKE_PREFIX_PATH.html#variable:CMAKE_PREFIX_PATH)
   - [`CMAKE_LIBRARY_PATH`](https://cmake.org/cmake/help/latest/variable/CMAKE_LIBRARY_PATH.html#variable:CMAKE_LIBRARY_PATH)
   - [`CMAKE_FRAMEWORK_PATH`](https://cmake.org/cmake/help/latest/variable/CMAKE_FRAMEWORK_PATH.html#variable:CMAKE_FRAMEWORK_PATH)

3. 在特定于 cmake 的环境变量中指定的搜索路径。这些旨在在用户的 shell 配置中设置，因此使用主机的本机路径分隔符（`;`在 Windows 和`:`UNIX 上）。如果`NO_CMAKE_ENVIRONMENT_PATH`通过或通过设置[`CMAKE_FIND_USE_CMAKE_ENVIRONMENT_PATH`](https://cmake.org/cmake/help/latest/variable/CMAKE_FIND_USE_CMAKE_ENVIRONMENT_PATH.html#variable:CMAKE_FIND_USE_CMAKE_ENVIRONMENT_PATH)到`FALSE`.

   - `<prefix>/lib/<arch>`如果[`CMAKE_LIBRARY_ARCHITECTURE`](https://cmake.org/cmake/help/latest/variable/CMAKE_LIBRARY_ARCHITECTURE.html#variable:CMAKE_LIBRARY_ARCHITECTURE)被设置，并且`<prefix>/lib`对于每个`<prefix>`在[`CMAKE_PREFIX_PATH`](https://cmake.org/cmake/help/latest/variable/CMAKE_PREFIX_PATH.html#variable:CMAKE_PREFIX_PATH)
   - [`CMAKE_LIBRARY_PATH`](https://cmake.org/cmake/help/latest/variable/CMAKE_LIBRARY_PATH.html#variable:CMAKE_LIBRARY_PATH)
   - [`CMAKE_FRAMEWORK_PATH`](https://cmake.org/cmake/help/latest/variable/CMAKE_FRAMEWORK_PATH.html#variable:CMAKE_FRAMEWORK_PATH)

4. 搜索选项指定的路径`HINTS`。这些应该是系统自省计算的路径，例如已找到的另一个项目的位置提供的提示。应使用该`PATHS`选项指定硬编码猜测。

5. 搜索标准系统环境变量。如果`NO_SYSTEM_ENVIRONMENT_PATH`通过或通过设置[`CMAKE_FIND_USE_SYSTEM_ENVIRONMENT_PATH`](https://cmake.org/cmake/help/latest/variable/CMAKE_FIND_USE_SYSTEM_ENVIRONMENT_PATH.html#variable:CMAKE_FIND_USE_SYSTEM_ENVIRONMENT_PATH)到`FALSE`.

   - `LIB` 和中的目录`PATH`。
   - 在 Windows 主机上： `<prefix>/lib/<arch>`如果[`CMAKE_LIBRARY_ARCHITECTURE`](https://cmake.org/cmake/help/latest/variable/CMAKE_LIBRARY_ARCHITECTURE.html#variable:CMAKE_LIBRARY_ARCHITECTURE) 已设置，并且对于中`<prefix>/lib`的每个条目，以及 对于 中的其他条目。`<prefix>/[s]bin``PATH``<entry>/lib``PATH`

6. 搜索当前系统的 Platform 文件中定义的 cmake 变量。如果`CMAKE_INSTALL_PREFIX`通过`NO_CMAKE_INSTALL_PREFIX`或通过设置 [`CMAKE_FIND_USE_INSTALL_PREFIX`](https://cmake.org/cmake/help/latest/variable/CMAKE_FIND_USE_INSTALL_PREFIX.html#variable:CMAKE_FIND_USE_INSTALL_PREFIX)到`FALSE`. 如果`NO_CMAKE_SYSTEM_PATH`通过或通过设置 [`CMAKE_FIND_USE_CMAKE_SYSTEM_PATH`](https://cmake.org/cmake/help/latest/variable/CMAKE_FIND_USE_CMAKE_SYSTEM_PATH.html#variable:CMAKE_FIND_USE_CMAKE_SYSTEM_PATH)到`FALSE`.

   - `<prefix>/lib/<arch>`如果[`CMAKE_LIBRARY_ARCHITECTURE`](https://cmake.org/cmake/help/latest/variable/CMAKE_LIBRARY_ARCHITECTURE.html#variable:CMAKE_LIBRARY_ARCHITECTURE)被设置，并且`<prefix>/lib`对于每个`<prefix>`在 [`CMAKE_SYSTEM_PREFIX_PATH`](https://cmake.org/cmake/help/latest/variable/CMAKE_SYSTEM_PREFIX_PATH.html#variable:CMAKE_SYSTEM_PREFIX_PATH)
   - [`CMAKE_SYSTEM_LIBRARY_PATH`](https://cmake.org/cmake/help/latest/variable/CMAKE_SYSTEM_LIBRARY_PATH.html#variable:CMAKE_SYSTEM_LIBRARY_PATH)
   - [`CMAKE_SYSTEM_FRAMEWORK_PATH`](https://cmake.org/cmake/help/latest/variable/CMAKE_SYSTEM_FRAMEWORK_PATH.html#variable:CMAKE_SYSTEM_FRAMEWORK_PATH)

   这些变量包含的平台路径是通常包含已安装软件的位置。一个例子是`/usr/local`基于 UNIX 的平台。

7. 搜索由 PATHS 选项或命令的简写版本指定的路径。这些通常是硬编码的猜测。

这[`CMAKE_IGNORE_PATH`](https://cmake.org/cmake/help/latest/variable/CMAKE_IGNORE_PATH.html#variable:CMAKE_IGNORE_PATH), [`CMAKE_IGNORE_PREFIX_PATH`](https://cmake.org/cmake/help/latest/variable/CMAKE_IGNORE_PREFIX_PATH.html#variable:CMAKE_IGNORE_PREFIX_PATH), [`CMAKE_SYSTEM_IGNORE_PATH`](https://cmake.org/cmake/help/latest/variable/CMAKE_SYSTEM_IGNORE_PATH.html#variable:CMAKE_SYSTEM_IGNORE_PATH)和 [`CMAKE_SYSTEM_IGNORE_PREFIX_PATH`](https://cmake.org/cmake/help/latest/variable/CMAKE_SYSTEM_IGNORE_PREFIX_PATH.html#variable:CMAKE_SYSTEM_IGNORE_PREFIX_PATH)变量也可能导致上述某些位置被忽略。

*3.16 版中的新功能：*添加`CMAKE_FIND_USE_<CATEGORY>_PATH`了全局禁用各种搜索位置的变量。

在 macOS 上[`CMAKE_FIND_FRAMEWORK`](https://cmake.org/cmake/help/latest/variable/CMAKE_FIND_FRAMEWORK.html#variable:CMAKE_FIND_FRAMEWORK)和 [`CMAKE_FIND_APPBUNDLE`](https://cmake.org/cmake/help/latest/variable/CMAKE_FIND_APPBUNDLE.html#variable:CMAKE_FIND_APPBUNDLE)变量决定了 Apple 风格和 unix 风格的包组件之间的优先顺序。

CMake 变量[`CMAKE_FIND_ROOT_PATH`](https://cmake.org/cmake/help/latest/variable/CMAKE_FIND_ROOT_PATH.html#variable:CMAKE_FIND_ROOT_PATH)指定要附加到所有其他搜索目录的一个或多个目录。这有效地“重新扎根”了给定位置下的整个搜索。路径的后代[`CMAKE_STAGING_PREFIX`](https://cmake.org/cmake/help/latest/variable/CMAKE_STAGING_PREFIX.html#variable:CMAKE_STAGING_PREFIX)被排除在此重新生根之外，因为该变量始终是主机系统上的路径。默认情况下[`CMAKE_FIND_ROOT_PATH`](https://cmake.org/cmake/help/latest/variable/CMAKE_FIND_ROOT_PATH.html#variable:CMAKE_FIND_ROOT_PATH)是空的。

这[`CMAKE_SYSROOT`](https://cmake.org/cmake/help/latest/variable/CMAKE_SYSROOT.html#variable:CMAKE_SYSROOT)变量也可以用来指定一个目录作为前缀。环境[`CMAKE_SYSROOT`](https://cmake.org/cmake/help/latest/variable/CMAKE_SYSROOT.html#variable:CMAKE_SYSROOT)还有其他作用。有关更多信息，请参阅该变量的文档。

这些变量在交叉编译指向目标环境的根目录时特别有用，CMake 也会在那里搜索。默认情况下，首先列出的目录 [`CMAKE_FIND_ROOT_PATH`](https://cmake.org/cmake/help/latest/variable/CMAKE_FIND_ROOT_PATH.html#variable:CMAKE_FIND_ROOT_PATH)被搜索，然后[`CMAKE_SYSROOT`](https://cmake.org/cmake/help/latest/variable/CMAKE_SYSROOT.html#variable:CMAKE_SYSROOT) 搜索目录，然后将搜索非根目录。默认行为可以通过设置来调整 [`CMAKE_FIND_ROOT_PATH_MODE_LIBRARY`](https://cmake.org/cmake/help/latest/variable/CMAKE_FIND_ROOT_PATH_MODE_LIBRARY.html#variable:CMAKE_FIND_ROOT_PATH_MODE_LIBRARY). 可以使用以下选项在每次调用的基础上手动覆盖此行为：

- `CMAKE_FIND_ROOT_PATH_BOTH`

  按上述顺序搜索。

- `NO_CMAKE_FIND_ROOT_PATH`

  不要使用[`CMAKE_FIND_ROOT_PATH`](https://cmake.org/cmake/help/latest/variable/CMAKE_FIND_ROOT_PATH.html#variable:CMAKE_FIND_ROOT_PATH)多变的。

- `ONLY_CMAKE_FIND_ROOT_PATH`

  仅搜索以下重新植根的目录和目录 [`CMAKE_STAGING_PREFIX`](https://cmake.org/cmake/help/latest/variable/CMAKE_STAGING_PREFIX.html#variable:CMAKE_STAGING_PREFIX).

默认搜索顺序旨在针对常见用例从最具体到最不具体。项目可以通过简单地多次调用命令并使用`NO_*`选项来覆盖顺序：

```cmake
find_library (<VAR> NAMES name PATHS 路径... NO_DEFAULT_PATH)
find_library (<VAR> NAMES 名称)
```

一旦其中一个调用成功，结果变量将被设置并存储在缓存中，这样就不会再次搜索调用。

当为选项提供多个值时`NAMES`，默认情况下此命令将一次考虑一个名称并在每个目录中搜索它。该`NAMES_PER_DIR`选项告诉此命令一次考虑一个目录并搜索其中的所有名称。

赋予`NAMES`选项的每个库名称首先被视为库文件名，然后与特定于平台的前缀（例如`lib`）和后缀（例如`.so`）一起考虑。因此可以直接指定库文件名，例如`libfoo.a`。这可用于在类 UNIX 系统上定位静态库。

如果找到的库是框架，`<VAR>`则将设置为框架的完整路径`<fullPath>/A.framework`。当框架的完整路径用作库时，CMake 将使用 a和 a 将框架链接到目标。`-framework A``-F<fullPath>`

如果[`CMAKE_FIND_LIBRARY_CUSTOM_LIB_SUFFIX`](https://cmake.org/cmake/help/latest/variable/CMAKE_FIND_LIBRARY_CUSTOM_LIB_SUFFIX.html#variable:CMAKE_FIND_LIBRARY_CUSTOM_LIB_SUFFIX)变量设置所有搜索路径将正常测试，附加后缀，所有匹配`lib/`替换为 `lib${CMAKE_FIND_LIBRARY_CUSTOM_LIB_SUFFIX}/`. 此变量覆盖[`FIND_LIBRARY_USE_LIB32_PATHS`](https://cmake.org/cmake/help/latest/prop_gbl/FIND_LIBRARY_USE_LIB32_PATHS.html#prop_gbl:FIND_LIBRARY_USE_LIB32_PATHS), [`FIND_LIBRARY_USE_LIBX32_PATHS`](https://cmake.org/cmake/help/latest/prop_gbl/FIND_LIBRARY_USE_LIBX32_PATHS.html#prop_gbl:FIND_LIBRARY_USE_LIBX32_PATHS)， 和[`FIND_LIBRARY_USE_LIB64_PATHS`](https://cmake.org/cmake/help/latest/prop_gbl/FIND_LIBRARY_USE_LIB64_PATHS.html#prop_gbl:FIND_LIBRARY_USE_LIB64_PATHS)全局属性。

如果[`FIND_LIBRARY_USE_LIB32_PATHS`](https://cmake.org/cmake/help/latest/prop_gbl/FIND_LIBRARY_USE_LIB32_PATHS.html#prop_gbl:FIND_LIBRARY_USE_LIB32_PATHS)设置了全局属性，所有搜索路径都将正常进行测试，并`32/`附加，并且所有匹配项都`lib/`替换为`lib32/`. 如果至少有一种语言支持，则此属性会自动为已知需要它的平台设置[`project()`](https://cmake.org/cmake/help/latest/command/project.html#command:project)命令已启用。

如果[`FIND_LIBRARY_USE_LIBX32_PATHS`](https://cmake.org/cmake/help/latest/prop_gbl/FIND_LIBRARY_USE_LIBX32_PATHS.html#prop_gbl:FIND_LIBRARY_USE_LIBX32_PATHS)设置了全局属性，所有搜索路径都将正常进行测试，并`x32/`附加，并且所有匹配项都`lib/`替换为`libx32/`. 如果至少有一种语言支持，则此属性会自动为已知需要它的平台设置[`project()`](https://cmake.org/cmake/help/latest/command/project.html#command:project)命令已启用。

如果[`FIND_LIBRARY_USE_LIB64_PATHS`](https://cmake.org/cmake/help/latest/prop_gbl/FIND_LIBRARY_USE_LIB64_PATHS.html#prop_gbl:FIND_LIBRARY_USE_LIB64_PATHS)设置了全局属性，所有搜索路径都将正常进行测试，并`64/`附加，并且所有匹配项都`lib/`替换为`lib64/`. 如果至少有一种语言支持，则此属性会自动为已知需要它的平台设置[`project()`](https://cmake.org/cmake/help/latest/command/project.html#command:project)命令已启用。



## [find_package](https://cmake.org/cmake/help/latest/command/find_package.html)

### 内容

- [查找包](https://cmake.org/cmake/help/latest/command/find_package.html#find-package)
  - [搜索模式](https://cmake.org/cmake/help/latest/command/find_package.html#search-modes)
  - [基本签名](https://cmake.org/cmake/help/latest/command/find_package.html#basic-signature)
  - [完整签名](https://cmake.org/cmake/help/latest/command/find_package.html#full-signature)
  - [配置模式搜索过程](https://cmake.org/cmake/help/latest/command/find_package.html#config-mode-search-procedure)
  - [配置模式版本选择](https://cmake.org/cmake/help/latest/command/find_package.html#config-mode-version-selection)
  - [包文件接口变量](https://cmake.org/cmake/help/latest/command/find_package.html#package-file-interface-variables)

> **笔记 **这[`Using Dependencies Guide`](https://cmake.org/cmake/help/latest/guide/using-dependencies/index.html#guide:Using Dependencies Guide)提供了对该一般主题的高级介绍。它提供了一个更广泛的概述，说明该`find_package()`命令在哪里适合更大的图景，包括它与[`FetchContent`](https://cmake.org/cmake/help/latest/module/FetchContent.html#module:FetchContent)模块。建议在继续阅读以下详细信息之前先阅读该指南。

 找到一个包（通常由项目外部的东西提供），并加载其包特定的详细信息。对这个命令的调用也可以被[依赖提供者](https://cmake.org/cmake/help/latest/command/cmake_language.html#dependency-providers)拦截。

### [搜索模式](https://cmake.org/cmake/help/latest/command/find_package.html#id4)

该命令有几种搜索包的模式：

- **模块模式**

  在这种模式下，CMake 搜索一个名为 的文件`Find<PackageName>.cmake`，首先在[`CMAKE_MODULE_PATH`](https://cmake.org/cmake/help/latest/variable/CMAKE_MODULE_PATH.html#variable:CMAKE_MODULE_PATH)，然后在CMake 安装提供的[Find Modules中。](https://cmake.org/cmake/help/latest/manual/cmake-developer.7.html#find-modules)如果找到该文件，则由 CMake 读取并处理该文件。它负责查找包、检查版本并生成任何需要的消息。一些 Find 模块对版本控制提供有限或不支持；检查查找模块的文档。该`Find<PackageName>.cmake`文件通常不由包本身提供。相反，它通常由包外部的东西提供，例如操作系统、CMake 本身，甚至`find_package()`是调用命令的项目。由于是外部提供的，[查找模块](https://cmake.org/cmake/help/latest/manual/cmake-developer.7.html#find-modules)在本质上往往是启发式的，并且容易过时。他们通常搜索某些库、文件和其他包工件。模块模式仅受 [基本命令签名](https://cmake.org/cmake/help/latest/command/find_package.html#basic-signature)支持。

- **配置模式**

  在这种模式下，CMake 会搜索一个名为 `<lowercasePackageName>-config.cmake`or的文件`<PackageName>Config.cmake`。它还将查找`<lowercasePackageName>-config-version.cmake`或 `<PackageName>ConfigVersion.cmake`是否指定了版本详细信息（请参阅[配置模式版本选择](https://cmake.org/cmake/help/latest/command/find_package.html#version-selection)以了解如何使用这些单独的版本文件）。在配置模式下，可以为命令提供一个名称列表以作为包名称进行搜索。CMake 搜索配置和版本文件的位置比模块模式复杂得多（请参阅[配置模式搜索过程](https://cmake.org/cmake/help/latest/command/find_package.html#search-procedure)）。配置和版本文件通常作为包的一部分安装，因此它们往往比查找模块更可靠。它们通常包含对包内容的直接了解，因此在配置或版本文件本身中不需要搜索或启发。[基本](https://cmake.org/cmake/help/latest/command/find_package.html#basic-signature)和 [完整](https://cmake.org/cmake/help/latest/command/find_package.html#full-signature)命令签名都支持配置模式。

- **FetchContent 重定向模式**

  *3.24 版中的新功能：*调用`find_package()`可以在内部重定向到由[`FetchContent`](https://cmake.org/cmake/help/latest/module/FetchContent.html#module:FetchContent)模块。对调用者而言，该行为将类似于 Config 模式，只是绕过了搜索逻辑并且不使用组件信息。看 [`FetchContent_Declare()`](https://cmake.org/cmake/help/latest/module/FetchContent.html#command:fetchcontent_declare)和[`FetchContent_MakeAvailable()`](https://cmake.org/cmake/help/latest/module/FetchContent.html#command:fetchcontent_makeavailable) 了解更多详情。

当未重定向到由[`FetchContent`](https://cmake.org/cmake/help/latest/module/FetchContent.html#module:FetchContent)，命令参数决定是使用模块还是配置模式。当使用 [基本签名](https://cmake.org/cmake/help/latest/command/find_package.html#basic-signature)时，该命令首先在模块模式下搜索。如果未找到包，则搜索回退到配置模式。用户可以设置[`CMAKE_FIND_PACKAGE_PREFER_CONFIG`](https://cmake.org/cmake/help/latest/variable/CMAKE_FIND_PACKAGE_PREFER_CONFIG.html#variable:CMAKE_FIND_PACKAGE_PREFER_CONFIG)将变量设置为 true 以反转优先级并指示 CMake 先使用 Config 模式进行搜索，然后再返回到 Module 模式。也可以强制基本签名仅使用带有`MODULE`关键字的模块模式。如果使用 [完整签名](https://cmake.org/cmake/help/latest/command/find_package.html#full-signature)，则该命令仅在 Config 模式下搜索。

在可能的情况下，用户代码通常应该使用 [基本签名](https://cmake.org/cmake/help/latest/command/find_package.html#basic-signature)来查找包，因为这样可以在任何模式下找到包。希望提供配置包的项目维护者应该了解大局，如[完整签名](https://cmake.org/cmake/help/latest/command/find_package.html#full-signature)和本页所有后续部分中所述。



### [基本签名](https://cmake.org/cmake/help/latest/command/find_package.html#id5)

```cmake
find_package(<PackageName> [version] [EXACT] [QUIET] [MODULE]
             [REQUIRED] [[COMPONENTS] [components...]]
             [OPTIONAL_COMPONENTS components...]
             [REGISTRY_VIEW  (64|32|64_32|32_64|HOST|TARGET|BOTH)]
             [GLOBAL]
             [NO_POLICY_SCOPE]
             [BYPASS_PROVIDER])
```

模块和配置模式都支持基本签名。`MODULE`关键字意味着只能使用 Module 模式来查找包，而不能回退到 Config 模式。

无论使用何种模式，`<PackageName>_FOUND`都会设置一个变量来指示是否找到了包。当找到包时，可以通过 包本身记录的其他变量和[导入的目标来提供包特定的信息。](https://cmake.org/cmake/help/latest/manual/cmake-buildsystem.7.html#imported-targets)该 `QUIET`选项禁用信息性消息，包括那些指示如果不是，则无法找到包的消息`REQUIRED`。`REQUIRED` 如果找不到包，该选项将停止处理并显示错误消息。

`COMPONENTS`可以在关键字之后列出所需组件的特定于包的列表 。如果不能满足这些组件中的任何一个，则认为未找到整个包。如果该 `REQUIRED`选项也存在，则将其视为致命错误，否则仍会继续执行。作为一种简写形式，如果该 `REQUIRED`选项存在，则`COMPONENTS`可以省略关键字，并且可以在 之后直接列出所需的组件`REQUIRED`。

后面可能会列出其他可选组件 `OPTIONAL_COMPONENTS`。如果这些都不能满足，只要满足所有必需的组件，仍然可以认为整个包都找到了。

可用组件的集合及其含义由目标包定义。形式上，由目标包如何解释给它的组件信息，但它应该遵循上述期望。对于没有指定组件的调用，没有单一的预期行为，目标包应该清楚地定义在这种情况下会发生什么。常见的安排包括假设它应该找到所有组件，没有组件或可用组件的一些明确定义的子集。

*3.24 新版功能：*关键字`REGISTRY_VIEW`使能指定必须查询哪些注册表视图。此关键字仅在平台上有意义，`Windows`在所有其他平台上将被忽略。形式上，由目标包如何解释提供给它的注册表视图信息。

*3.24 版中*的新功能：指定`GLOBAL`关键字会将所有导入的目标提升到导入项目中的全局范围。或者，可以通过设置启用此功能[`CMAKE_FIND_PACKAGE_TARGETS_GLOBAL`](https://cmake.org/cmake/help/latest/variable/CMAKE_FIND_PACKAGE_TARGETS_GLOBAL.html#variable:CMAKE_FIND_PACKAGE_TARGETS_GLOBAL) 多变的。

该`[version]`参数请求找到的包应该兼容的版本。有两种可能的形式可以指定它：

> - 具有 format 的单个版本`major[.minor[.patch[.tweak]]]`，其中每个组件都是一个数值。
> - 一个版本范围，其格式与单个版本相同`versionMin...[<]versionMax`， `versionMin`并且`versionMax`对作为整数的组件具有相同的格式和约束。默认情况下，两个端点都包括在内。通过指定`<`，将排除上端点。只有 CMake 3.19 或更高版本才支持版本范围。

该`EXACT`选项要求版本完全匹配。此选项与版本范围的规范不兼容。

如果没有`[version]`和/或组件列表提供给查找模块内的递归调用，则相应的参数会自动从外部调用转发（包括`EXACT`标志 `[version]`）。当前仅在逐个包的基础上提供版本支持（请参阅下面的[版本选择](https://cmake.org/cmake/help/latest/command/find_package.html#version-selection)部分）。当指定版本范围但包仅设计为期望单个版本时，包将忽略范围的上端点，而仅考虑范围下端的单个版本。

见[`cmake_policy()`](https://cmake.org/cmake/help/latest/command/cmake_policy.html#command:cmake_policy)用于讨论该`NO_POLICY_SCOPE`选项的命令文档。

*3.24 新版功能：*该关键字仅在被[依赖提供者](https://cmake.org/cmake/help/latest/command/cmake_language.html#dependency-providers)`BYPASS_PROVIDER`调用时才允许使用。提供者可以使用它直接调用内置 实现，并防止该调用被重新路由回自身。CMake 的未来版本可能会检测到从依赖项提供程序以外的地方使用此关键字的尝试，并因致命错误而停止。`find_package()``find_package()`



### [完整签名](https://cmake.org/cmake/help/latest/command/find_package.html#id6)

```cmake
find_package(<PackageName> [version] [EXACT] [QUIET]
             [REQUIRED] [[COMPONENTS] [components...]]
             [OPTIONAL_COMPONENTS components...]
             [CONFIG|NO_MODULE]
             [GLOBAL]
             [NO_POLICY_SCOPE]
             [BYPASS_PROVIDER]
             [NAMES name1 [name2 ...]]
             [CONFIGS config1 [config2 ...]]
             [HINTS path1 [path2 ... ]]
             [PATHS path1 [path2 ... ]]
             [REGISTRY_VIEW  (64|32|64_32|32_64|HOST|TARGET|BOTH)]
             [PATH_SUFFIXES suffix1 [suffix2 ...]]
             [NO_DEFAULT_PATH]
             [NO_PACKAGE_ROOT_PATH]
             [NO_CMAKE_PATH]
             [NO_CMAKE_ENVIRONMENT_PATH]
             [NO_SYSTEM_ENVIRONMENT_PATH]
             [NO_CMAKE_PACKAGE_REGISTRY]
             [NO_CMAKE_BUILDS_PATH] # Deprecated; does nothing.
             [NO_CMAKE_SYSTEM_PATH]
             [NO_CMAKE_INSTALL_PREFIX]
             [NO_CMAKE_SYSTEM_PACKAGE_REGISTRY]
             [CMAKE_FIND_ROOT_PATH_BOTH |
              ONLY_CMAKE_FIND_ROOT_PATH |
              NO_CMAKE_FIND_ROOT_PATH])
```

`CONFIG`选项、同义`NO_MODULE`选项或使用[基本签名](https://cmake.org/cmake/help/latest/command/find_package.html#basic-signature)中未指定的选项都强制执行纯 Config 模式。在纯 Config 模式下，该命令会跳过 Module 模式搜索并立即进行 Config 模式搜索。

配置模式搜索尝试查找要查找的包提供的配置文件。创建一个名为的缓存条目`<PackageName>_DIR`来保存包含该文件的目录。默认情况下，该命令搜索名称为 的包`<PackageName>`。如果`NAMES`给出了选项，则使用它后面的名称而不是`<PackageName>`. 在确定是否将调用重定向到由[`FetchContent`](https://cmake.org/cmake/help/latest/module/FetchContent.html#module:FetchContent).

该命令搜索一个名为`<PackageName>Config.cmake`或 `<lowercasePackageName>-config.cmake`每个指定名称的文件。`CONFIGS`可以使用该选项给出一组可能的配置文件名的替换。配置[模式搜索过程](https://cmake.org/cmake/help/latest/command/find_package.html#search-procedure)如下所示。一旦找到，就会检查任何[版本约束](https://cmake.org/cmake/help/latest/command/find_package.html#version-selection)，如果满足，则 CMake 读取并处理配置文件。由于该文件是由包提供的，因此它已经知道包内容的位置。配置文件的完整路径存储在 cmake 变量`<PackageName>_CONFIG`中。

CMake 在搜索具有适当版本的包时考虑的所有配置文件都存储在 `<PackageName>_CONSIDERED_CONFIGS`变量中，相关的版本存储在`<PackageName>_CONSIDERED_VERSIONS`变量中。

如果找不到包配置文件，除非`QUIET`指定参数，否则 CMake 将生成描述问题的错误。如果`REQUIRED`指定且未找到包，则会生成致命错误并且配置步骤停止执行。如果 `<PackageName>_DIR`已设置为不包含配置文件的目录，CMake 将忽略它并从头开始搜索。

鼓励提供 CMake 包配置文件的包维护者命名并安装它们，以便下面概述的[配置模式搜索过程](https://cmake.org/cmake/help/latest/command/find_package.html#search-procedure) 将找到它们，而无需使用其他选项。



### [配置模式搜索过程](https://cmake.org/cmake/help/latest/command/find_package.html#id7)

> **笔记 **当使用配置模式时，无论给出[完整](https://cmake.org/cmake/help/latest/command/find_package.html#full-signature)签名还是[基本](https://cmake.org/cmake/help/latest/command/find_package.html#basic-signature) 签名，都会应用此搜索过程。

*3.24 新版功能：*所有调用`find_package()`（即使在模块模式下）首先在[`CMAKE_FIND_PACKAGE_REDIRECTS_DIR`](https://cmake.org/cmake/help/latest/variable/CMAKE_FIND_PACKAGE_REDIRECTS_DIR.html#variable:CMAKE_FIND_PACKAGE_REDIRECTS_DIR)目录。这[`FetchContent`](https://cmake.org/cmake/help/latest/module/FetchContent.html#module:FetchContent)模块，甚至项目本身，可能会将文件写入该位置，以将`find_package()`调用重定向到项目已提供的内容。如果在该位置未找到配置包文件，则搜索将按照下面描述的逻辑进行。

CMake 为包构造了一组可能的安装前缀。在每个前缀下搜索几个目录以查找配置文件。下表显示了搜索的目录。每个条目都适用于遵循 Windows ( `W`)、UNIX ( `U`) 或 Apple ( `A`) 约定的安装树：

```cmake
<prefix>/                                                       (W)
<prefix>/(cmake|CMake)/                                         (W)
<prefix>/<name>*/                                               (W)
<prefix>/<name>*/(cmake|CMake)/                                 (W)
<prefix>/(lib/<arch>|lib*|share)/cmake/<name>*/                 (U)
<prefix>/(lib/<arch>|lib*|share)/<name>*/                       (U)
<prefix>/(lib/<arch>|lib*|share)/<name>*/(cmake|CMake)/         (U)
<prefix>/<name>*/(lib/<arch>|lib*|share)/cmake/<name>*/         (W/U)
<prefix>/<name>*/(lib/<arch>|lib*|share)/<name>*/               (W/U)
<prefix>/<name>*/(lib/<arch>|lib*|share)/<name>*/(cmake|CMake)/ (W/U)
```

在支持 macOS 的系统上[`FRAMEWORK`](https://cmake.org/cmake/help/latest/prop_tgt/FRAMEWORK.html#prop_tgt:FRAMEWORK)和[`BUNDLE`](https://cmake.org/cmake/help/latest/prop_tgt/BUNDLE.html#prop_tgt:BUNDLE)，在以下目录中搜索包含配置文件的框架或应用程序包：

```cmake
<prefix>/<name>.framework/Resources/                    (A)
<prefix>/<name>.framework/Resources/CMake/              (A)
<prefix>/<name>.framework/Versions/*/Resources/         (A)
<prefix>/<name>.framework/Versions/*/Resources/CMake/   (A)
<prefix>/<name>.app/Contents/Resources/                 (A)
<prefix>/<name>.app/Contents/Resources/CMake/           (A)
```

在所有情况下`<name>`都被视为不区分大小写并对应于任何指定的名称（`<PackageName>`或由 给出的名称`NAMES`）。

如果`lib/<arch>`_ [`CMAKE_LIBRARY_ARCHITECTURE`](https://cmake.org/cmake/help/latest/variable/CMAKE_LIBRARY_ARCHITECTURE.html#variable:CMAKE_LIBRARY_ARCHITECTURE)变量已设置。包括一个或`lib*`多个值`lib64`、`lib32`或（按该顺序搜索）。`libx32``lib`

- 在 64 位平台上搜索路径，`lib64`如果 [`FIND_LIBRARY_USE_LIB64_PATHS`](https://cmake.org/cmake/help/latest/prop_gbl/FIND_LIBRARY_USE_LIB64_PATHS.html#prop_gbl:FIND_LIBRARY_USE_LIB64_PATHS)属性设置为`TRUE`。
- 在 32 位平台上搜索路径，`lib32`如果 [`FIND_LIBRARY_USE_LIB32_PATHS`](https://cmake.org/cmake/help/latest/prop_gbl/FIND_LIBRARY_USE_LIB32_PATHS.html#prop_gbl:FIND_LIBRARY_USE_LIB32_PATHS)属性设置为`TRUE`。
- `libx32`使用 x32 ABI 在平台上搜索路径[`FIND_LIBRARY_USE_LIBX32_PATHS`](https://cmake.org/cmake/help/latest/prop_gbl/FIND_LIBRARY_USE_LIBX32_PATHS.html#prop_gbl:FIND_LIBRARY_USE_LIBX32_PATHS)属性设置为`TRUE`。
- `lib`总是搜索路径。

*在 3.24 版更改:*在平台上，可以使用[专用语法](https://cmake.org/cmake/help/latest/manual/cmake-developer.7.html#find-using-windows-registry)`Windows`将注册表查询作为通过`HINTS`和关键字指定的目录的一部分。在所有其他平台上，此类规范将被忽略。`PATHS`

*3.24 版中的新功能：*`REGISTRY_VIEW`可以指定管理指定为和`Windows`的一部分的注册表查询。`PATHS``HINTS`

指定必须查询哪些注册表视图。此选项仅在平台上有意义，`Windows`在其他平台上将被忽略。如果未指定，`TARGET`则在以下情况下使用视图[`CMP0134`](https://cmake.org/cmake/help/latest/policy/CMP0134.html#policy:CMP0134) 政策是`NEW`。参考[`CMP0134`](https://cmake.org/cmake/help/latest/policy/CMP0134.html#policy:CMP0134)策略为`OLD`或未定义时的默认视图。

- `64`

  查询 64 位注册表。开启时，始终返回字符串 。`32bit Windows``/REGISTRY-NOTFOUND`

- `32`

  查询 32 位注册表。

- `64_32`

  查询两个视图 (`64`和`32`) 并为每个视图生成一个路径。

- `32_64`

  查询两个视图 (`32`和`64`) 并为每个视图生成一个路径。

- `HOST`

  查询与主机架构匹配的注册表：`64`on和on 。`64bit Windows``32``32bit Windows`

- `TARGET`

  查询与指定架构匹配的注册表 [`CMAKE_SIZEOF_VOID_P`](https://cmake.org/cmake/help/latest/variable/CMAKE_SIZEOF_VOID_P.html#variable:CMAKE_SIZEOF_VOID_P)多变的。如果未定义，则回退到 `HOST`查看。

- `BOTH`

  查询两个视图（`32`和`64`）。顺序取决于以下规则：如果[`CMAKE_SIZEOF_VOID_P`](https://cmake.org/cmake/help/latest/variable/CMAKE_SIZEOF_VOID_P.html#variable:CMAKE_SIZEOF_VOID_P)变量被定义。根据此变量的内容使用以下视图：`8`: `64_32``4`:`32_64`如果[`CMAKE_SIZEOF_VOID_P`](https://cmake.org/cmake/help/latest/variable/CMAKE_SIZEOF_VOID_P.html#variable:CMAKE_SIZEOF_VOID_P)变量未定义，依赖于主机的架构：`64bit`:`64_32``32bit`:`32`

如果`PATH_SUFFIXES`指定，则后缀将一个接一个地附加到每个 ( `W`) 或 ( `U`) 目录条目。

这组目录旨在与在其安装树中提供配置文件的项目合作。上面标有 ( `W`) 的目录适用于 Windows 上的安装，其中前缀可能指向应用程序安装目录的顶部。标有 ( `U`) 的那些适用于在多个包共享前缀的 UNIX 平台上安装。这只是一个约定，因此仍然会在所有平台上搜索所有 ( `W`) 和 ( ) 目录。`U`标有 ( `A`) 的目录适用于 Apple 平台上的安装。这 [`CMAKE_FIND_FRAMEWORK`](https://cmake.org/cmake/help/latest/variable/CMAKE_FIND_FRAMEWORK.html#variable:CMAKE_FIND_FRAMEWORK)和[`CMAKE_FIND_APPBUNDLE`](https://cmake.org/cmake/help/latest/variable/CMAKE_FIND_APPBUNDLE.html#variable:CMAKE_FIND_APPBUNDLE) 变量决定了偏好的顺序。

使用以下步骤构建安装前缀集。如果`NO_DEFAULT_PATH`指定了所有`NO_*`选项，则启用。

1. *3.12 新版功能：*在[`_ROOT`](https://cmake.org/cmake/help/latest/variable/PackageName_ROOT.html#variable:_ROOT)CMake 变量和[`_ROOT`](https://cmake.org/cmake/help/latest/envvar/PackageName_ROOT.html#envvar:_ROOT)环境变量，`<PackageName>`要找到的包在哪里。包根变量作为堆栈维护，因此如果从查找模块中调用，来自父查找模块的根路径也将在当前包的路径之后搜索。如果`NO_PACKAGE_ROOT_PATH`通过或通过设置[`CMAKE_FIND_USE_PACKAGE_ROOT_PATH`](https://cmake.org/cmake/help/latest/variable/CMAKE_FIND_USE_PACKAGE_ROOT_PATH.html#variable:CMAKE_FIND_USE_PACKAGE_ROOT_PATH)到`FALSE`. 查看政策[`CMP0074`](https://cmake.org/cmake/help/latest/policy/CMP0074.html#policy:CMP0074).

2. 在特定于 cmake 的缓存变量中指定的搜索路径。这些旨在用于带有`-DVAR=value`. 这些值被解释为[分号分隔的列表](https://cmake.org/cmake/help/latest/manual/cmake-language.7.html#cmake-language-lists)。如果`NO_CMAKE_PATH`通过或通过设置 [`CMAKE_FIND_USE_CMAKE_PATH`](https://cmake.org/cmake/help/latest/variable/CMAKE_FIND_USE_CMAKE_PATH.html#variable:CMAKE_FIND_USE_CMAKE_PATH)至`FALSE`：

   - [`CMAKE_PREFIX_PATH`](https://cmake.org/cmake/help/latest/variable/CMAKE_PREFIX_PATH.html#variable:CMAKE_PREFIX_PATH)
   - [`CMAKE_FRAMEWORK_PATH`](https://cmake.org/cmake/help/latest/variable/CMAKE_FRAMEWORK_PATH.html#variable:CMAKE_FRAMEWORK_PATH)
   - [`CMAKE_APPBUNDLE_PATH`](https://cmake.org/cmake/help/latest/variable/CMAKE_APPBUNDLE_PATH.html#variable:CMAKE_APPBUNDLE_PATH)

3. 在特定于 cmake 的环境变量中指定的搜索路径。这些旨在在用户的 shell 配置中设置，因此使用主机的本机路径分隔符（`;`在 Windows 和`:`UNIX 上）。如果`NO_CMAKE_ENVIRONMENT_PATH`通过或通过设置[`CMAKE_FIND_USE_CMAKE_ENVIRONMENT_PATH`](https://cmake.org/cmake/help/latest/variable/CMAKE_FIND_USE_CMAKE_ENVIRONMENT_PATH.html#variable:CMAKE_FIND_USE_CMAKE_ENVIRONMENT_PATH)至`FALSE`：

   - `<PackageName>_DIR`
   - [`CMAKE_PREFIX_PATH`](https://cmake.org/cmake/help/latest/envvar/CMAKE_PREFIX_PATH.html#envvar:CMAKE_PREFIX_PATH)
   - `CMAKE_FRAMEWORK_PATH`
   - `CMAKE_APPBUNDLE_PATH`

4. 选项指定的搜索路径`HINTS`。这些应该是系统自省计算的路径，例如已找到的另一个项目的位置提供的提示。应使用该`PATHS`选项指定硬编码猜测。

5. 搜索标准系统环境变量。如果`NO_SYSTEM_ENVIRONMENT_PATH`通过或通过设置 [`CMAKE_FIND_USE_SYSTEM_ENVIRONMENT_PATH`](https://cmake.org/cmake/help/latest/variable/CMAKE_FIND_USE_SYSTEM_ENVIRONMENT_PATH.html#variable:CMAKE_FIND_USE_SYSTEM_ENVIRONMENT_PATH)到`FALSE`. `/bin`以或结尾的路径条目`/sbin`会自动转换为其父目录：

   - `PATH`

6. 搜索存储在 CMake[用户包注册表](https://cmake.org/cmake/help/latest/manual/cmake-packages.7.html#user-package-registry)中的路径。`NO_CMAKE_PACKAGE_REGISTRY`如果通过或通过设置变量可以跳过这[`CMAKE_FIND_USE_PACKAGE_REGISTRY`](https://cmake.org/cmake/help/latest/variable/CMAKE_FIND_USE_PACKAGE_REGISTRY.html#variable:CMAKE_FIND_USE_PACKAGE_REGISTRY) 到`FALSE`或不推荐使用的变量 [`CMAKE_FIND_PACKAGE_NO_PACKAGE_REGISTRY`](https://cmake.org/cmake/help/latest/variable/CMAKE_FIND_PACKAGE_NO_PACKAGE_REGISTRY.html#variable:CMAKE_FIND_PACKAGE_NO_PACKAGE_REGISTRY)到`TRUE`.

   见[`cmake-packages(7)`](https://cmake.org/cmake/help/latest/manual/cmake-packages.7.html#manual:cmake-packages(7))有关用户包注册表的详细信息的手册。

7. 搜索当前系统的 Platform 文件中定义的 cmake 变量。的搜索[`CMAKE_INSTALL_PREFIX`](https://cmake.org/cmake/help/latest/variable/CMAKE_INSTALL_PREFIX.html#variable:CMAKE_INSTALL_PREFIX)如果`NO_CMAKE_INSTALL_PREFIX`通过或通过设置 [`CMAKE_FIND_USE_INSTALL_PREFIX`](https://cmake.org/cmake/help/latest/variable/CMAKE_FIND_USE_INSTALL_PREFIX.html#variable:CMAKE_FIND_USE_INSTALL_PREFIX)到`FALSE`. 如果`NO_CMAKE_SYSTEM_PATH`通过或通过设置 [`CMAKE_FIND_USE_CMAKE_SYSTEM_PATH`](https://cmake.org/cmake/help/latest/variable/CMAKE_FIND_USE_CMAKE_SYSTEM_PATH.html#variable:CMAKE_FIND_USE_CMAKE_SYSTEM_PATH)至`FALSE`：

   - [`CMAKE_SYSTEM_PREFIX_PATH`](https://cmake.org/cmake/help/latest/variable/CMAKE_SYSTEM_PREFIX_PATH.html#variable:CMAKE_SYSTEM_PREFIX_PATH)
   - [`CMAKE_SYSTEM_FRAMEWORK_PATH`](https://cmake.org/cmake/help/latest/variable/CMAKE_SYSTEM_FRAMEWORK_PATH.html#variable:CMAKE_SYSTEM_FRAMEWORK_PATH)
   - [`CMAKE_SYSTEM_APPBUNDLE_PATH`](https://cmake.org/cmake/help/latest/variable/CMAKE_SYSTEM_APPBUNDLE_PATH.html#variable:CMAKE_SYSTEM_APPBUNDLE_PATH)

   这些变量包含的平台路径是通常包含已安装软件的位置。一个例子是`/usr/local`基于 UNIX 的平台。

8. 搜索存储在 CMake [System Package Registry](https://cmake.org/cmake/help/latest/manual/cmake-packages.7.html#system-package-registry)中的路径。如果`NO_CMAKE_SYSTEM_PACKAGE_REGISTRY`通过或通过设置[`CMAKE_FIND_USE_SYSTEM_PACKAGE_REGISTRY`](https://cmake.org/cmake/help/latest/variable/CMAKE_FIND_USE_SYSTEM_PACKAGE_REGISTRY.html#variable:CMAKE_FIND_USE_SYSTEM_PACKAGE_REGISTRY) 变量到`FALSE`或不推荐使用的变量 [`CMAKE_FIND_PACKAGE_NO_SYSTEM_PACKAGE_REGISTRY`](https://cmake.org/cmake/help/latest/variable/CMAKE_FIND_PACKAGE_NO_SYSTEM_PACKAGE_REGISTRY.html#variable:CMAKE_FIND_PACKAGE_NO_SYSTEM_PACKAGE_REGISTRY)到`TRUE`.

   见[`cmake-packages(7)`](https://cmake.org/cmake/help/latest/manual/cmake-packages.7.html#manual:cmake-packages(7))手册以获取有关系统包注册表的详细信息。

9. 选项指定的搜索路径`PATHS`。这些通常是硬编码的猜测。

这[`CMAKE_IGNORE_PATH`](https://cmake.org/cmake/help/latest/variable/CMAKE_IGNORE_PATH.html#variable:CMAKE_IGNORE_PATH), [`CMAKE_IGNORE_PREFIX_PATH`](https://cmake.org/cmake/help/latest/variable/CMAKE_IGNORE_PREFIX_PATH.html#variable:CMAKE_IGNORE_PREFIX_PATH), [`CMAKE_SYSTEM_IGNORE_PATH`](https://cmake.org/cmake/help/latest/variable/CMAKE_SYSTEM_IGNORE_PATH.html#variable:CMAKE_SYSTEM_IGNORE_PATH)和 [`CMAKE_SYSTEM_IGNORE_PREFIX_PATH`](https://cmake.org/cmake/help/latest/variable/CMAKE_SYSTEM_IGNORE_PREFIX_PATH.html#variable:CMAKE_SYSTEM_IGNORE_PREFIX_PATH)变量也可能导致上述某些位置被忽略。

*3.16 新版功能：*添加了`CMAKE_FIND_USE_<CATEGORY>`全局禁用各种搜索位置的变量。

CMake 变量[`CMAKE_FIND_ROOT_PATH`](https://cmake.org/cmake/help/latest/variable/CMAKE_FIND_ROOT_PATH.html#variable:CMAKE_FIND_ROOT_PATH)指定要附加到所有其他搜索目录的一个或多个目录。这有效地“重新扎根”了给定位置下的整个搜索。路径的后代[`CMAKE_STAGING_PREFIX`](https://cmake.org/cmake/help/latest/variable/CMAKE_STAGING_PREFIX.html#variable:CMAKE_STAGING_PREFIX)被排除在此重新生根之外，因为该变量始终是主机系统上的路径。默认情况下[`CMAKE_FIND_ROOT_PATH`](https://cmake.org/cmake/help/latest/variable/CMAKE_FIND_ROOT_PATH.html#variable:CMAKE_FIND_ROOT_PATH)是空的。

这[`CMAKE_SYSROOT`](https://cmake.org/cmake/help/latest/variable/CMAKE_SYSROOT.html#variable:CMAKE_SYSROOT)变量也可以用来指定一个目录作为前缀。环境[`CMAKE_SYSROOT`](https://cmake.org/cmake/help/latest/variable/CMAKE_SYSROOT.html#variable:CMAKE_SYSROOT)还有其他作用。有关更多信息，请参阅该变量的文档。

这些变量在交叉编译指向目标环境的根目录时特别有用，CMake 也会在那里搜索。默认情况下，首先列出的目录 [`CMAKE_FIND_ROOT_PATH`](https://cmake.org/cmake/help/latest/variable/CMAKE_FIND_ROOT_PATH.html#variable:CMAKE_FIND_ROOT_PATH)被搜索，然后[`CMAKE_SYSROOT`](https://cmake.org/cmake/help/latest/variable/CMAKE_SYSROOT.html#variable:CMAKE_SYSROOT) 搜索目录，然后将搜索非根目录。默认行为可以通过设置来调整 [`CMAKE_FIND_ROOT_PATH_MODE_PACKAGE`](https://cmake.org/cmake/help/latest/variable/CMAKE_FIND_ROOT_PATH_MODE_PACKAGE.html#variable:CMAKE_FIND_ROOT_PATH_MODE_PACKAGE). 可以使用以下选项在每次调用的基础上手动覆盖此行为：

- `CMAKE_FIND_ROOT_PATH_BOTH`

  按上述顺序搜索。

- `NO_CMAKE_FIND_ROOT_PATH`

  不要使用[`CMAKE_FIND_ROOT_PATH`](https://cmake.org/cmake/help/latest/variable/CMAKE_FIND_ROOT_PATH.html#variable:CMAKE_FIND_ROOT_PATH)多变的。

- `ONLY_CMAKE_FIND_ROOT_PATH`

  仅搜索以下重新植根的目录和目录 [`CMAKE_STAGING_PREFIX`](https://cmake.org/cmake/help/latest/variable/CMAKE_STAGING_PREFIX.html#variable:CMAKE_STAGING_PREFIX).

默认搜索顺序旨在针对常见用例从最具体到最不具体。项目可以通过简单地多次调用命令并使用`NO_*`选项来覆盖顺序：

```cmake
find_package (<PackageName> PATHS 路径... NO_DEFAULT_PATH)
find_package (<包名>)
```

一旦其中一个调用成功，结果变量将被设置并存储在缓存中，这样就不会再次搜索调用。

默认情况下，存储在结果变量中的值将是找到文件的路径。这[`CMAKE_FIND_PACKAGE_RESOLVE_SYMLINKS`](https://cmake.org/cmake/help/latest/variable/CMAKE_FIND_PACKAGE_RESOLVE_SYMLINKS.html#variable:CMAKE_FIND_PACKAGE_RESOLVE_SYMLINKS) 变量可以`TRUE`在调用之前设置为`find_package`，以便解析符号链接并存储文件的真实路径。

每个非必需的`find_package`调用都可以被禁用或变为必需的：

- 设置[`CMAKE_DISABLE_FIND_PACKAGE_`](https://cmake.org/cmake/help/latest/variable/CMAKE_DISABLE_FIND_PACKAGE_PackageName.html#variable:CMAKE_DISABLE_FIND_PACKAGE_)变量`TRUE`禁用包。这也会禁用重定向到由[`FetchContent`](https://cmake.org/cmake/help/latest/module/FetchContent.html#module:FetchContent).
- 设置[`CMAKE_REQUIRE_FIND_PACKAGE_`](https://cmake.org/cmake/help/latest/variable/CMAKE_REQUIRE_FIND_PACKAGE_PackageName.html#variable:CMAKE_REQUIRE_FIND_PACKAGE_)`TRUE`使包成为必需的变量。

同时设置两个变量`TRUE`是错误的。



### [配置模式版本选择](https://cmake.org/cmake/help/latest/command/find_package.html#id8)

> **笔记** 使用 Config 模式时，无论给出[完整](https://cmake.org/cmake/help/latest/command/find_package.html#full-signature)签名还是 [基本](https://cmake.org/cmake/help/latest/command/find_package.html#basic-signature)签名，都会应用此版本选择过程。

当`[version]`给定参数时，配置模式只会找到声称与请求版本兼容的包版本（请参阅[格式规范](https://cmake.org/cmake/help/latest/command/find_package.html#find-package-version-format)）。如果 `EXACT`给出该选项，则只能找到声称与请求版本完全匹配的包版本。CMake 没有为版本号的含义建立任何约定。包版本号由包本身或由包提供的“版本”文件检查[`FetchContent`](https://cmake.org/cmake/help/latest/module/FetchContent.html#module:FetchContent). 对于候选包配置文件 `<config-file>.cmake`，相应的版本文件位于它旁边，并命名为`<config-file>-version.cmake`or 或 `<config-file>Version.cmake`. 如果没有这样的版本文件可用，则假定配置文件与任何请求的版本不兼容。可以使用以下命令创建包含通用版本匹配代码的基本版本文件 [`CMakePackageConfigHelpers`](https://cmake.org/cmake/help/latest/module/CMakePackageConfigHelpers.html#module:CMakePackageConfigHelpers)模块。当找到版本文件时，将加载它以检查请求的版本号。版本文件加载到嵌套范围内，其中定义了以下变量：

- `PACKAGE_FIND_NAME`

  这`<PackageName>`

- `PACKAGE_FIND_VERSION`

  完整请求的版本字符串

- `PACKAGE_FIND_VERSION_MAJOR`

  如果需要，则为主要版本，否则为 0

- `PACKAGE_FIND_VERSION_MINOR`

  如果需要，则为次要版本，否则为 0

- `PACKAGE_FIND_VERSION_PATCH`

  如果需要，则为补丁版本，否则为 0

- `PACKAGE_FIND_VERSION_TWEAK`

  如果需要，调整版本，否则为 0

- `PACKAGE_FIND_VERSION_COUNT`

  版本组件数，0 到 4

当指定版本范围时，上述版本变量将根据版本范围的下限保存值。这是为了保持与尚未实现以期望版本范围的包的兼容性。此外，版本范围将由以下变量描述：

- `PACKAGE_FIND_VERSION_RANGE`

  完整请求的版本范围字符串

- `PACKAGE_FIND_VERSION_RANGE_MIN`

  这指定是否应包括或排除版本范围的下端点。目前，此变量唯一支持的值是`INCLUDE`.

- `PACKAGE_FIND_VERSION_RANGE_MAX`

  这指定是否应包括或排除版本范围的上端点。此变量支持的值为 `INCLUDE`和`EXCLUDE`。

- `PACKAGE_FIND_VERSION_MIN`

  范围下限的完整请求版本字符串

- `PACKAGE_FIND_VERSION_MIN_MAJOR`

  如果请求，则为低端点的主要版本，否则为 0

- `PACKAGE_FIND_VERSION_MIN_MINOR`

  如果请求，则为低端点的次要版本，否则为 0

- `PACKAGE_FIND_VERSION_MIN_PATCH`

  如果请求，则为下端点的补丁版本，否则为 0

- `PACKAGE_FIND_VERSION_MIN_TWEAK`

  如果需要，则调整下端点的版本，否则为 0

- `PACKAGE_FIND_VERSION_MIN_COUNT`

  下端点的版本组件数，0到4

- `PACKAGE_FIND_VERSION_MAX`

  范围上端点的完整请求版本字符串

- `PACKAGE_FIND_VERSION_MAX_MAJOR`

  如果请求，则为上端点的主要版本，否则为 0

- `PACKAGE_FIND_VERSION_MAX_MINOR`

  如果请求，则为上端点的次要版本，否则为 0

- `PACKAGE_FIND_VERSION_MAX_PATCH`

  如果请求，则为上端点的补丁版本，否则为 0

- `PACKAGE_FIND_VERSION_MAX_TWEAK`

  如果需要，则调整上端点的版本，否则为 0

- `PACKAGE_FIND_VERSION_MAX_COUNT`

  上端点的版本组件数，0到4

无论是否指定了单个版本或版本范围，`PACKAGE_FIND_VERSION_COMPLETE`都将定义该变量并将保存指定的完整请求版本字符串。

版本文件检查它是否满足请求的版本并设置这些变量：

- `PACKAGE_VERSION`

  完整提供的版本字符串

- `PACKAGE_VERSION_EXACT`

  如果版本完全匹配，则为真

- `PACKAGE_VERSION_COMPATIBLE`

  如果版本兼容则为真

- `PACKAGE_VERSION_UNSUITABLE`

  如果不适合任何版本，则为真

命令检查这些变量`find_package`以确定配置文件是否提供了可接受的版本。`find_package`呼叫返回后它们不可用。如果版本可接受，则设置以下变量：

- `<PackageName>_VERSION`

  完整提供的版本字符串

- `<PackageName>_VERSION_MAJOR`

  主要版本（如果提供），否则为 0

- `<PackageName>_VERSION_MINOR`

  次要版本（如果提供），否则为 0

- `<PackageName>_VERSION_PATCH`

  补丁版本（如果提供），否则为 0

- `<PackageName>_VERSION_TWEAK`

  调整版本（如果提供），否则为 0

- `<PackageName>_VERSION_COUNT`

  版本组件数，0 到 4

并加载相应的包配置文件。当多个包配置文件可用，其版本文件声称与请求的版本兼容时，未指定选择哪一个：除非变量[`CMAKE_FIND_PACKAGE_SORT_ORDER`](https://cmake.org/cmake/help/latest/variable/CMAKE_FIND_PACKAGE_SORT_ORDER.html#variable:CMAKE_FIND_PACKAGE_SORT_ORDER) 设置为不尝试选择最高或最接近的版本号。

`find_package`要控制检查兼容性的顺序，请使用两个变量[`CMAKE_FIND_PACKAGE_SORT_ORDER`](https://cmake.org/cmake/help/latest/variable/CMAKE_FIND_PACKAGE_SORT_ORDER.html#variable:CMAKE_FIND_PACKAGE_SORT_ORDER)和 [`CMAKE_FIND_PACKAGE_SORT_DIRECTION`](https://cmake.org/cmake/help/latest/variable/CMAKE_FIND_PACKAGE_SORT_DIRECTION.html#variable:CMAKE_FIND_PACKAGE_SORT_DIRECTION). 例如，为了选择可以设置的最高版本

```cmake
SET(CMAKE_FIND_PACKAGE_SORT_ORDER NATURAL)
SET(CMAKE_FIND_PACKAGE_SORT_DIRECTION DEC)
```

打电话之前`find_package`。

### [包文件接口变量](https://cmake.org/cmake/help/latest/command/find_package.html#id9)

加载查找模块或包配置文件时`find_package` 定义变量以提供有关调用参数的信息（并在返回之前恢复其原始状态）：

- `CMAKE_FIND_PACKAGE_NAME`

  `<PackageName>`被搜索的那个

- `<PackageName>_FIND_REQUIRED`

  如果`REQUIRED`给出选项，则为真

- `<PackageName>_FIND_QUIETLY`

  如果`QUIET`给出选项，则为真

- `<PackageName>_FIND_REGISTRY_VIEW`

  `REGISTRY_VIEW`如果给出了选项，则请求的视图

- `<PackageName>_FIND_VERSION`

  完整请求的版本字符串

- `<PackageName>_FIND_VERSION_MAJOR`

  如果需要，则为主要版本，否则为 0

- `<PackageName>_FIND_VERSION_MINOR`

  如果需要，则为次要版本，否则为 0

- `<PackageName>_FIND_VERSION_PATCH`

  如果需要，则为补丁版本，否则为 0

- `<PackageName>_FIND_VERSION_TWEAK`

  如果需要，调整版本，否则为 0

- `<PackageName>_FIND_VERSION_COUNT`

  版本组件数，0 到 4

- `<PackageName>_FIND_VERSION_EXACT`

  如果`EXACT`给出选项，则为真

- `<PackageName>_FIND_COMPONENTS`

  指定组件列表（必需和可选）

- `<PackageName>_FIND_REQUIRED_<c>`

  如果组件`<c>`是必需的，则为 true，如果组件`<c>`是可选的，则为 false

当指定版本范围时，上述版本变量将根据版本范围的下限保存值。这是为了保持与尚未实现以期望版本范围的包的兼容性。此外，版本范围将由以下变量描述：

- `<PackageName>_FIND_VERSION_RANGE`

  完整请求的版本范围字符串

- `<PackageName>_FIND_VERSION_RANGE_MIN`

  这指定是包含还是排除版本范围的下端点。目前，`INCLUDE`是唯一受支持的值。

- `<PackageName>_FIND_VERSION_RANGE_MAX`

  这指定是包含还是排除版本范围的上端点。此变量的可能值为 `INCLUDE`或`EXCLUDE`。

- `<PackageName>_FIND_VERSION_MIN`

  范围下限的完整请求版本字符串

- `<PackageName>_FIND_VERSION_MIN_MAJOR`

  如果请求，则为低端点的主要版本，否则为 0

- `<PackageName>_FIND_VERSION_MIN_MINOR`

  如果请求，则为低端点的次要版本，否则为 0

- `<PackageName>_FIND_VERSION_MIN_PATCH`

  如果请求，则为下端点的补丁版本，否则为 0

- `<PackageName>_FIND_VERSION_MIN_TWEAK`

  如果需要，则调整下端点的版本，否则为 0

- `<PackageName>_FIND_VERSION_MIN_COUNT`

  下端点的版本组件数，0到4

- `<PackageName>_FIND_VERSION_MAX`

  范围上端点的完整请求版本字符串

- `<PackageName>_FIND_VERSION_MAX_MAJOR`

  如果请求，则为上端点的主要版本，否则为 0

- `<PackageName>_FIND_VERSION_MAX_MINOR`

  如果请求，则为上端点的次要版本，否则为 0

- `<PackageName>_FIND_VERSION_MAX_PATCH`

  如果请求，则为上端点的补丁版本，否则为 0

- `<PackageName>_FIND_VERSION_MAX_TWEAK`

  如果需要，则调整上端点的版本，否则为 0

- `<PackageName>_FIND_VERSION_MAX_COUNT`

  上端点的版本组件数，0到4

无论是否指定了单个版本或版本范围，`<PackageName>_FIND_VERSION_COMPLETE`都将定义该变量并将保存指定的完整请求版本字符串。

在模块模式下，加载的查找模块负责处理这些变量详细说明的请求；有关详细信息，请参阅查找模块。在 Config 模式下，自动`find_package`处理`REQUIRED`、`QUIET`和 `[version]`options ，但将其留给包配置文件以对包有意义的方式处理组件。包配置文件可能设置 `<PackageName>_FOUND`为 false 以告知`find_package`不满足组件要求。



## [find_path](https://cmake.org/cmake/help/latest/command/find_path.html)

速记签名是：

```cmake
find_path (<VAR> name1 [path1 path2 ...])
```

一般签名是：

```cmake
find_path (
          <VAR>
          name | NAMES name1 [name2 ...]
          [HINTS [path | ENV var]... ]
          [PATHS [path | ENV var]... ]
          [REGISTRY_VIEW (64|32|64_32|32_64|HOST|TARGET|BOTH)]
          [PATH_SUFFIXES suffix1 [suffix2 ...]]
          [DOC "cache documentation string"]
          [NO_CACHE]
          [REQUIRED]
          [NO_DEFAULT_PATH]
          [NO_PACKAGE_ROOT_PATH]
          [NO_CMAKE_PATH]
          [NO_CMAKE_ENVIRONMENT_PATH]
          [NO_SYSTEM_ENVIRONMENT_PATH]
          [NO_CMAKE_SYSTEM_PATH]
          [NO_CMAKE_INSTALL_PREFIX]
          [CMAKE_FIND_ROOT_PATH_BOTH |
           ONLY_CMAKE_FIND_ROOT_PATH |
           NO_CMAKE_FIND_ROOT_PATH]
         )
```

此命令用于查找包含命名文件的目录。一个缓存条目，或者一个普通变量，如果`NO_CACHE`指定的话，`<VAR>`被创建来存储这个命令的结果。如果找到目录中的文件，结果将存储在变量中，除非清除变量，否则不会重复搜索。如果什么都没找到，结果将是`<VAR>-NOTFOUND`。

选项包括：

- `NAMES`

  为目录中的文件指定一个或多个可能的名称。当使用它来指定带有和不带版本后缀的名称时，我们建议首先指定未版本化的名称，以便在发行版提供的包之前可以找到本地构建的包。

- `HINTS`, `PATHS`

  除默认位置外，还指定要搜索的目录。子选项从系统环境变量中读取路径。`ENV var`*在 3.24 版更改:*在平台上，可以使用[专用语法](https://cmake.org/cmake/help/latest/manual/cmake-developer.7.html#find-using-windows-registry)`Windows`将注册表查询作为目录的一部分。在所有其他平台上，此类规范将被忽略。

- `REGISTRY_VIEW`

  *版本 3.24 中的新功能。*指定必须查询哪些注册表视图。此选项仅在平台上有意义，`Windows`在其他平台上将被忽略。如果未指定，`TARGET`则在以下情况下使用视图[`CMP0134`](https://cmake.org/cmake/help/latest/policy/CMP0134.html#policy:CMP0134) 政策是`NEW`。参考[`CMP0134`](https://cmake.org/cmake/help/latest/policy/CMP0134.html#policy:CMP0134)策略为`OLD`或未定义时的默认视图。`64`查询 64 位注册表。开启时，始终返回字符串 。`32bit Windows``/REGISTRY-NOTFOUND``32`查询 32 位注册表。`64_32`查询两个视图 (`64`和`32`) 并为每个视图生成一个路径。`32_64`查询两个视图 (`32`和`64`) 并为每个视图生成一个路径。`HOST`查询与主机架构匹配的注册表：`64`on和on 。`64bit Windows``32``32bit Windows``TARGET`查询与指定架构匹配的注册表 [`CMAKE_SIZEOF_VOID_P`](https://cmake.org/cmake/help/latest/variable/CMAKE_SIZEOF_VOID_P.html#variable:CMAKE_SIZEOF_VOID_P)多变的。如果未定义，则回退到 `HOST`查看。`BOTH`查询两个视图（`32`和`64`）。顺序取决于以下规则：如果[`CMAKE_SIZEOF_VOID_P`](https://cmake.org/cmake/help/latest/variable/CMAKE_SIZEOF_VOID_P.html#variable:CMAKE_SIZEOF_VOID_P)变量被定义。根据此变量的内容使用以下视图：`8`: `64_32``4`:`32_64`如果[`CMAKE_SIZEOF_VOID_P`](https://cmake.org/cmake/help/latest/variable/CMAKE_SIZEOF_VOID_P.html#variable:CMAKE_SIZEOF_VOID_P)变量未定义，依赖于主机的架构：`64bit`:`64_32``32bit`:`32`

- `PATH_SUFFIXES`

  指定其他子目录以在每个目录位置下方检查，否则会考虑。

- `DOC`

  指定`<VAR>`缓存条目的文档字符串。

- `NO_CACHE`

  *3.21 版中的新功能。*搜索结果将存储在普通变量而不是缓存条目中。

  > **笔记** 如果在调用之前已经设置了变量（作为普通变量或缓存变量），则不会发生搜索。
  >
  > **警告** 应谨慎使用此选项，因为它会大大增加重复配置步骤的成本。

- `REQUIRED`

  *3.18 版中的新功能。*如果未找到任何内容，则停止处理并显示错误消息，否则将在下次使用相同变量调用 find_path 时再次尝试搜索。

如果`NO_DEFAULT_PATH`指定，则不会将其他路径添加到搜索中。如果`NO_DEFAULT_PATH`不指定，则搜索过程如下：

1. *3.12 版中的新功能：*如果从查找模块或通过调用加载的任何其他脚本中调用 [`find_package()`](https://cmake.org/cmake/help/latest/command/find_package.html#command:find_package), 搜索对当前找到的包唯一的前缀。具体来说，查看 [`_ROOT`](https://cmake.org/cmake/help/latest/variable/PackageName_ROOT.html#variable:_ROOT)CMake 变量和 [`_ROOT`](https://cmake.org/cmake/help/latest/envvar/PackageName_ROOT.html#envvar:_ROOT)环境变量。包根变量作为堆栈维护，因此如果从嵌套的查找模块或配置包中调用，则将在当前模块或包的路径之后搜索来自父查找模块或配置包的根路径。换句话说，搜索顺序将是 `<CurrentPackage>_ROOT`, `ENV{<CurrentPackage>_ROOT}`, `<ParentPackage>_ROOT`, `ENV{<ParentPackage>_ROOT}`, 等等。如果`NO_PACKAGE_ROOT_PATH`通过或通过设置[`CMAKE_FIND_USE_PACKAGE_ROOT_PATH`](https://cmake.org/cmake/help/latest/variable/CMAKE_FIND_USE_PACKAGE_ROOT_PATH.html#variable:CMAKE_FIND_USE_PACKAGE_ROOT_PATH)到`FALSE`. 查看政策[`CMP0074`](https://cmake.org/cmake/help/latest/policy/CMP0074.html#policy:CMP0074).

   - `<prefix>/include/<arch>`如果[`CMAKE_LIBRARY_ARCHITECTURE`](https://cmake.org/cmake/help/latest/variable/CMAKE_LIBRARY_ARCHITECTURE.html#variable:CMAKE_LIBRARY_ARCHITECTURE) 被设置，并且对于 `<prefix>/include`每个`<prefix>`[`_ROOT`](https://cmake.org/cmake/help/latest/variable/PackageName_ROOT.html#variable:_ROOT)CMake 变量和 [`_ROOT`](https://cmake.org/cmake/help/latest/envvar/PackageName_ROOT.html#envvar:_ROOT)如果从加载的查找模块中调用环境变量 [`find_package()`](https://cmake.org/cmake/help/latest/command/find_package.html#command:find_package)

2. 在特定于 cmake 的缓存变量中指定的搜索路径。这些旨在用于带有`-DVAR=value`. 这些值被解释为[分号分隔的列表](https://cmake.org/cmake/help/latest/manual/cmake-language.7.html#cmake-language-lists)。如果`NO_CMAKE_PATH`通过或通过设置 [`CMAKE_FIND_USE_CMAKE_PATH`](https://cmake.org/cmake/help/latest/variable/CMAKE_FIND_USE_CMAKE_PATH.html#variable:CMAKE_FIND_USE_CMAKE_PATH)到`FALSE`.

   - `<prefix>/include/<arch>`如果[`CMAKE_LIBRARY_ARCHITECTURE`](https://cmake.org/cmake/help/latest/variable/CMAKE_LIBRARY_ARCHITECTURE.html#variable:CMAKE_LIBRARY_ARCHITECTURE) 被设置，并且`<prefix>/include`对于每个`<prefix>`在[`CMAKE_PREFIX_PATH`](https://cmake.org/cmake/help/latest/variable/CMAKE_PREFIX_PATH.html#variable:CMAKE_PREFIX_PATH)
   - [`CMAKE_INCLUDE_PATH`](https://cmake.org/cmake/help/latest/variable/CMAKE_INCLUDE_PATH.html#variable:CMAKE_INCLUDE_PATH)
   - [`CMAKE_FRAMEWORK_PATH`](https://cmake.org/cmake/help/latest/variable/CMAKE_FRAMEWORK_PATH.html#variable:CMAKE_FRAMEWORK_PATH)

3. 在特定于 cmake 的环境变量中指定的搜索路径。这些旨在在用户的 shell 配置中设置，因此使用主机的本机路径分隔符（`;`在 Windows 和`:`UNIX 上）。如果`NO_CMAKE_ENVIRONMENT_PATH`通过或通过设置[`CMAKE_FIND_USE_CMAKE_ENVIRONMENT_PATH`](https://cmake.org/cmake/help/latest/variable/CMAKE_FIND_USE_CMAKE_ENVIRONMENT_PATH.html#variable:CMAKE_FIND_USE_CMAKE_ENVIRONMENT_PATH)到`FALSE`.

   - `<prefix>/include/<arch>`如果[`CMAKE_LIBRARY_ARCHITECTURE`](https://cmake.org/cmake/help/latest/variable/CMAKE_LIBRARY_ARCHITECTURE.html#variable:CMAKE_LIBRARY_ARCHITECTURE) 被设置，并且`<prefix>/include`对于每个`<prefix>`在[`CMAKE_PREFIX_PATH`](https://cmake.org/cmake/help/latest/variable/CMAKE_PREFIX_PATH.html#variable:CMAKE_PREFIX_PATH)
   - [`CMAKE_INCLUDE_PATH`](https://cmake.org/cmake/help/latest/variable/CMAKE_INCLUDE_PATH.html#variable:CMAKE_INCLUDE_PATH)
   - [`CMAKE_FRAMEWORK_PATH`](https://cmake.org/cmake/help/latest/variable/CMAKE_FRAMEWORK_PATH.html#variable:CMAKE_FRAMEWORK_PATH)

4. 搜索选项指定的路径`HINTS`。这些应该是系统自省计算的路径，例如已找到的另一个项目的位置提供的提示。应使用该`PATHS`选项指定硬编码猜测。

5. 搜索标准系统环境变量。如果`NO_SYSTEM_ENVIRONMENT_PATH`通过或通过设置[`CMAKE_FIND_USE_SYSTEM_ENVIRONMENT_PATH`](https://cmake.org/cmake/help/latest/variable/CMAKE_FIND_USE_SYSTEM_ENVIRONMENT_PATH.html#variable:CMAKE_FIND_USE_SYSTEM_ENVIRONMENT_PATH)到`FALSE`.

   - `INCLUDE` 和中的目录`PATH`。
   - 在 Windows 主机上： `<prefix>/include/<arch>`如果[`CMAKE_LIBRARY_ARCHITECTURE`](https://cmake.org/cmake/help/latest/variable/CMAKE_LIBRARY_ARCHITECTURE.html#variable:CMAKE_LIBRARY_ARCHITECTURE) 已设置，并且对于中`<prefix>/include`的每个条目，以及 对于 中的其他条目。`<prefix>/[s]bin``PATH``<entry>/include``PATH`

6. 搜索当前系统的 Platform 文件中定义的 cmake 变量。如果`CMAKE_INSTALL_PREFIX`通过`NO_CMAKE_INSTALL_PREFIX`或通过设置 [`CMAKE_FIND_USE_INSTALL_PREFIX`](https://cmake.org/cmake/help/latest/variable/CMAKE_FIND_USE_INSTALL_PREFIX.html#variable:CMAKE_FIND_USE_INSTALL_PREFIX)到`FALSE`. 如果`NO_CMAKE_SYSTEM_PATH`通过或通过设置 [`CMAKE_FIND_USE_CMAKE_SYSTEM_PATH`](https://cmake.org/cmake/help/latest/variable/CMAKE_FIND_USE_CMAKE_SYSTEM_PATH.html#variable:CMAKE_FIND_USE_CMAKE_SYSTEM_PATH)到`FALSE`.

   - `<prefix>/include/<arch>`如果[`CMAKE_LIBRARY_ARCHITECTURE`](https://cmake.org/cmake/help/latest/variable/CMAKE_LIBRARY_ARCHITECTURE.html#variable:CMAKE_LIBRARY_ARCHITECTURE) 被设置，并且`<prefix>/include`对于每个`<prefix>`在 [`CMAKE_SYSTEM_PREFIX_PATH`](https://cmake.org/cmake/help/latest/variable/CMAKE_SYSTEM_PREFIX_PATH.html#variable:CMAKE_SYSTEM_PREFIX_PATH)
   - [`CMAKE_SYSTEM_INCLUDE_PATH`](https://cmake.org/cmake/help/latest/variable/CMAKE_SYSTEM_INCLUDE_PATH.html#variable:CMAKE_SYSTEM_INCLUDE_PATH)
   - [`CMAKE_SYSTEM_FRAMEWORK_PATH`](https://cmake.org/cmake/help/latest/variable/CMAKE_SYSTEM_FRAMEWORK_PATH.html#variable:CMAKE_SYSTEM_FRAMEWORK_PATH)

   这些变量包含的平台路径是通常包含已安装软件的位置。一个例子是`/usr/local`基于 UNIX 的平台。

7. 搜索由 PATHS 选项或命令的简写版本指定的路径。这些通常是硬编码的猜测。

这[`CMAKE_IGNORE_PATH`](https://cmake.org/cmake/help/latest/variable/CMAKE_IGNORE_PATH.html#variable:CMAKE_IGNORE_PATH), [`CMAKE_IGNORE_PREFIX_PATH`](https://cmake.org/cmake/help/latest/variable/CMAKE_IGNORE_PREFIX_PATH.html#variable:CMAKE_IGNORE_PREFIX_PATH), [`CMAKE_SYSTEM_IGNORE_PATH`](https://cmake.org/cmake/help/latest/variable/CMAKE_SYSTEM_IGNORE_PATH.html#variable:CMAKE_SYSTEM_IGNORE_PATH)和 [`CMAKE_SYSTEM_IGNORE_PREFIX_PATH`](https://cmake.org/cmake/help/latest/variable/CMAKE_SYSTEM_IGNORE_PREFIX_PATH.html#variable:CMAKE_SYSTEM_IGNORE_PREFIX_PATH)变量也可能导致上述某些位置被忽略。

*3.16 版中的新功能：*添加`CMAKE_FIND_USE_<CATEGORY>_PATH`了全局禁用各种搜索位置的变量。

在 macOS 上[`CMAKE_FIND_FRAMEWORK`](https://cmake.org/cmake/help/latest/variable/CMAKE_FIND_FRAMEWORK.html#variable:CMAKE_FIND_FRAMEWORK)和 [`CMAKE_FIND_APPBUNDLE`](https://cmake.org/cmake/help/latest/variable/CMAKE_FIND_APPBUNDLE.html#variable:CMAKE_FIND_APPBUNDLE)变量决定了 Apple 风格和 unix 风格的包组件之间的优先顺序。

CMake 变量[`CMAKE_FIND_ROOT_PATH`](https://cmake.org/cmake/help/latest/variable/CMAKE_FIND_ROOT_PATH.html#variable:CMAKE_FIND_ROOT_PATH)指定要附加到所有其他搜索目录的一个或多个目录。这有效地“重新扎根”了给定位置下的整个搜索。路径的后代[`CMAKE_STAGING_PREFIX`](https://cmake.org/cmake/help/latest/variable/CMAKE_STAGING_PREFIX.html#variable:CMAKE_STAGING_PREFIX)被排除在此重新生根之外，因为该变量始终是主机系统上的路径。默认情况下[`CMAKE_FIND_ROOT_PATH`](https://cmake.org/cmake/help/latest/variable/CMAKE_FIND_ROOT_PATH.html#variable:CMAKE_FIND_ROOT_PATH)是空的。

这[`CMAKE_SYSROOT`](https://cmake.org/cmake/help/latest/variable/CMAKE_SYSROOT.html#variable:CMAKE_SYSROOT)变量也可以用来指定一个目录作为前缀。环境[`CMAKE_SYSROOT`](https://cmake.org/cmake/help/latest/variable/CMAKE_SYSROOT.html#variable:CMAKE_SYSROOT)还有其他作用。有关更多信息，请参阅该变量的文档。

这些变量在交叉编译指向目标环境的根目录时特别有用，CMake 也会在那里搜索。默认情况下，首先列出的目录 [`CMAKE_FIND_ROOT_PATH`](https://cmake.org/cmake/help/latest/variable/CMAKE_FIND_ROOT_PATH.html#variable:CMAKE_FIND_ROOT_PATH)被搜索，然后[`CMAKE_SYSROOT`](https://cmake.org/cmake/help/latest/variable/CMAKE_SYSROOT.html#variable:CMAKE_SYSROOT) 搜索目录，然后将搜索非根目录。默认行为可以通过设置来调整 [`CMAKE_FIND_ROOT_PATH_MODE_INCLUDE`](https://cmake.org/cmake/help/latest/variable/CMAKE_FIND_ROOT_PATH_MODE_INCLUDE.html#variable:CMAKE_FIND_ROOT_PATH_MODE_INCLUDE). 可以使用以下选项在每次调用的基础上手动覆盖此行为：

- `CMAKE_FIND_ROOT_PATH_BOTH`

  按上述顺序搜索。

- `NO_CMAKE_FIND_ROOT_PATH`

  不要使用[`CMAKE_FIND_ROOT_PATH`](https://cmake.org/cmake/help/latest/variable/CMAKE_FIND_ROOT_PATH.html#variable:CMAKE_FIND_ROOT_PATH)多变的。

- `ONLY_CMAKE_FIND_ROOT_PATH`

  仅搜索以下重新植根的目录和目录 [`CMAKE_STAGING_PREFIX`](https://cmake.org/cmake/help/latest/variable/CMAKE_STAGING_PREFIX.html#variable:CMAKE_STAGING_PREFIX).

默认搜索顺序旨在针对常见用例从最具体到最不具体。项目可以通过简单地多次调用命令并使用`NO_*`选项来覆盖顺序：

```cmake
find_path (<VAR> NAMES name PATHS 路径... NO_DEFAULT_PATH)
find_path (<VAR> NAMES 名称)
```

一旦其中一个调用成功，结果变量将被设置并存储在缓存中，这样就不会再次搜索调用。

搜索框架时，如果文件指定为`A/b.h`，则框架搜索将查找`A.framework/Headers/b.h`. 如果找到，则路径将设置为框架的路径。CMake 会将其转换为正确的`-F`选项以包含该文件。



## [find_program](https://cmake.org/cmake/help/latest/command/find_program.html)

速记签名是：

```cmake
find_program (<VAR> name1 [path1 path2 ...])
```

一般签名是：

```cmake
查找程序（
          <VAR>
          姓名 | NAMES name1 [name2 ...] [NAMES_PER_DIR]
          [提示 [路径 | 环境变量]...]
          [路径 [路径 | 环境变量]...]
          [REGISTRY_VIEW (64|32|64_32|32_64|主机|目标|两者)]
          [PATH_SUFFIXES suffix1 [suffix2 ...]]
          [DOC“缓存文档字符串”]
          [NO_CACHE]
          [必需的]
          [NO_DEFAULT_PATH]
          [NO_PACKAGE_ROOT_PATH]
          [NO_CMAKE_PATH]
          [NO_CMAKE_ENVIRONMENT_PATH]
          [NO_SYSTEM_ENVIRONMENT_PATH]
          [NO_CMAKE_SYSTEM_PATH]
          [NO_CMAKE_INSTALL_PREFIX]
          [CMAKE_FIND_ROOT_PATH_BOTH |
           ONLY_CMAKE_FIND_ROOT_PATH |
           NO_CMAKE_FIND_ROOT_PATH]
         )
```

该命令用于查找程序。一个缓存条目，或者一个普通变量，如果`NO_CACHE`指定的话，`<VAR>`被创建来存储这个命令的结果。如果找到程序，结果将存储在变量中，除非清除变量，否则不会重复搜索。如果什么都没找到，结果将是`<VAR>-NOTFOUND`。

选项包括：

- `NAMES`

  为程序指定一个或多个可能的名称。当使用它来指定带有和不带版本后缀的名称时，我们建议首先指定未版本化的名称，以便在发行版提供的包之前可以找到本地构建的包。

- `HINTS`, `PATHS`

  除默认位置外，还指定要搜索的目录。子选项从系统环境变量中读取路径。`ENV var`*在 3.24 版更改:*在平台上，可以使用[专用语法](https://cmake.org/cmake/help/latest/manual/cmake-developer.7.html#find-using-windows-registry)`Windows`将注册表查询作为目录的一部分。在所有其他平台上，此类规范将被忽略。

- `REGISTRY_VIEW`

  *版本 3.24 中的新功能。*指定必须查询哪些注册表视图。此选项仅在平台上有意义，`Windows`在其他平台上将被忽略。如果未指定，`BOTH`则在以下情况下使用视图[`CMP0134`](https://cmake.org/cmake/help/latest/policy/CMP0134.html#policy:CMP0134) 政策是`NEW`。参考[`CMP0134`](https://cmake.org/cmake/help/latest/policy/CMP0134.html#policy:CMP0134)策略为`OLD`或未定义时的默认视图。`64`查询 64 位注册表。开启时，始终返回字符串 。`32bit Windows``/REGISTRY-NOTFOUND``32`查询 32 位注册表。`64_32`查询两个视图 (`64`和`32`) 并为每个视图生成一个路径。`32_64`查询两个视图 (`32`和`64`) 并为每个视图生成一个路径。`HOST`查询与主机架构匹配的注册表：`64`on和on 。`64bit Windows``32``32bit Windows``TARGET`查询与指定架构匹配的注册表 [`CMAKE_SIZEOF_VOID_P`](https://cmake.org/cmake/help/latest/variable/CMAKE_SIZEOF_VOID_P.html#variable:CMAKE_SIZEOF_VOID_P)多变的。如果未定义，则回退到 `HOST`查看。`BOTH`查询两个视图（`32`和`64`）。顺序取决于以下规则：如果[`CMAKE_SIZEOF_VOID_P`](https://cmake.org/cmake/help/latest/variable/CMAKE_SIZEOF_VOID_P.html#variable:CMAKE_SIZEOF_VOID_P)变量被定义。根据此变量的内容使用以下视图：`8`: `64_32``4`:`32_64`如果[`CMAKE_SIZEOF_VOID_P`](https://cmake.org/cmake/help/latest/variable/CMAKE_SIZEOF_VOID_P.html#variable:CMAKE_SIZEOF_VOID_P)变量未定义，依赖于主机的架构：`64bit`:`64_32``32bit`:`32`

- `PATH_SUFFIXES`

  指定其他子目录以在每个目录位置下方检查，否则会考虑。

- `DOC`

  指定`<VAR>`缓存条目的文档字符串。

- `NO_CACHE`

  *3.21 版中的新功能。*搜索结果将存储在普通变量而不是缓存条目中。

  > **笔记** 如果在调用之前已经设置了变量（作为普通变量或缓存变量），则不会发生搜索。
  >
  > **警告** 应谨慎使用此选项，因为它会大大增加重复配置步骤的成本。

- `REQUIRED`

  *3.18 版中的新功能。*如果未找到任何内容，则停止处理并显示错误消息，否则将在下次使用相同变量调用 find_program 时再次尝试搜索。

如果`NO_DEFAULT_PATH`指定，则不会将其他路径添加到搜索中。如果`NO_DEFAULT_PATH`不指定，则搜索过程如下：

1. *3.12 版中的新功能：*如果从查找模块或通过调用加载的任何其他脚本中调用 [`find_package()`](https://cmake.org/cmake/help/latest/command/find_package.html#command:find_package), 搜索对当前找到的包唯一的前缀。具体来说，查看 [`_ROOT`](https://cmake.org/cmake/help/latest/variable/PackageName_ROOT.html#variable:_ROOT)CMake 变量和 [`_ROOT`](https://cmake.org/cmake/help/latest/envvar/PackageName_ROOT.html#envvar:_ROOT)环境变量。包根变量作为堆栈维护，因此如果从嵌套的查找模块或配置包中调用，则将在当前模块或包的路径之后搜索来自父查找模块或配置包的根路径。换句话说，搜索顺序将是 `<CurrentPackage>_ROOT`, `ENV{<CurrentPackage>_ROOT}`, `<ParentPackage>_ROOT`, `ENV{<ParentPackage>_ROOT}`, 等等。如果`NO_PACKAGE_ROOT_PATH`通过或通过设置[`CMAKE_FIND_USE_PACKAGE_ROOT_PATH`](https://cmake.org/cmake/help/latest/variable/CMAKE_FIND_USE_PACKAGE_ROOT_PATH.html#variable:CMAKE_FIND_USE_PACKAGE_ROOT_PATH)到`FALSE`. 查看政策[`CMP0074`](https://cmake.org/cmake/help/latest/policy/CMP0074.html#policy:CMP0074).

   - `<prefix>/[s]bin`对于每个`<prefix>`在 [`_ROOT`](https://cmake.org/cmake/help/latest/variable/PackageName_ROOT.html#variable:_ROOT)CMake 变量和 [`_ROOT`](https://cmake.org/cmake/help/latest/envvar/PackageName_ROOT.html#envvar:_ROOT)如果从加载的查找模块中调用环境变量 [`find_package()`](https://cmake.org/cmake/help/latest/command/find_package.html#command:find_package)

2. 在特定于 cmake 的缓存变量中指定的搜索路径。这些旨在用于带有`-DVAR=value`. 这些值被解释为[分号分隔的列表](https://cmake.org/cmake/help/latest/manual/cmake-language.7.html#cmake-language-lists)。如果`NO_CMAKE_PATH`通过或通过设置 [`CMAKE_FIND_USE_CMAKE_PATH`](https://cmake.org/cmake/help/latest/variable/CMAKE_FIND_USE_CMAKE_PATH.html#variable:CMAKE_FIND_USE_CMAKE_PATH)到`FALSE`.

   - `<prefix>/[s]bin`对于每个`<prefix>`在[`CMAKE_PREFIX_PATH`](https://cmake.org/cmake/help/latest/variable/CMAKE_PREFIX_PATH.html#variable:CMAKE_PREFIX_PATH)
   - [`CMAKE_PROGRAM_PATH`](https://cmake.org/cmake/help/latest/variable/CMAKE_PROGRAM_PATH.html#variable:CMAKE_PROGRAM_PATH)
   - [`CMAKE_APPBUNDLE_PATH`](https://cmake.org/cmake/help/latest/variable/CMAKE_APPBUNDLE_PATH.html#variable:CMAKE_APPBUNDLE_PATH)

3. 在特定于 cmake 的环境变量中指定的搜索路径。这些旨在在用户的 shell 配置中设置，因此使用主机的本机路径分隔符（`;`在 Windows 和`:`UNIX 上）。如果`NO_CMAKE_ENVIRONMENT_PATH`通过或通过设置[`CMAKE_FIND_USE_CMAKE_ENVIRONMENT_PATH`](https://cmake.org/cmake/help/latest/variable/CMAKE_FIND_USE_CMAKE_ENVIRONMENT_PATH.html#variable:CMAKE_FIND_USE_CMAKE_ENVIRONMENT_PATH)到`FALSE`.

   - `<prefix>/[s]bin`对于每个`<prefix>`在[`CMAKE_PREFIX_PATH`](https://cmake.org/cmake/help/latest/variable/CMAKE_PREFIX_PATH.html#variable:CMAKE_PREFIX_PATH)
   - [`CMAKE_PROGRAM_PATH`](https://cmake.org/cmake/help/latest/variable/CMAKE_PROGRAM_PATH.html#variable:CMAKE_PROGRAM_PATH)
   - [`CMAKE_APPBUNDLE_PATH`](https://cmake.org/cmake/help/latest/variable/CMAKE_APPBUNDLE_PATH.html#variable:CMAKE_APPBUNDLE_PATH)

4. 搜索选项指定的路径`HINTS`。这些应该是系统自省计算的路径，例如已找到的另一个项目的位置提供的提示。应使用该`PATHS`选项指定硬编码猜测。

5. 搜索标准系统环境变量。如果`NO_SYSTEM_ENVIRONMENT_PATH`通过或通过设置[`CMAKE_FIND_USE_SYSTEM_ENVIRONMENT_PATH`](https://cmake.org/cmake/help/latest/variable/CMAKE_FIND_USE_SYSTEM_ENVIRONMENT_PATH.html#variable:CMAKE_FIND_USE_SYSTEM_ENVIRONMENT_PATH)到`FALSE`.

   - 目录`PATH`本身。
   - 在 Windows 主机上不包含额外的搜索路径

6. 搜索当前系统的 Platform 文件中定义的 cmake 变量。如果`CMAKE_INSTALL_PREFIX`通过`NO_CMAKE_INSTALL_PREFIX`或通过设置 [`CMAKE_FIND_USE_INSTALL_PREFIX`](https://cmake.org/cmake/help/latest/variable/CMAKE_FIND_USE_INSTALL_PREFIX.html#variable:CMAKE_FIND_USE_INSTALL_PREFIX)到`FALSE`. 如果`NO_CMAKE_SYSTEM_PATH`通过或通过设置 [`CMAKE_FIND_USE_CMAKE_SYSTEM_PATH`](https://cmake.org/cmake/help/latest/variable/CMAKE_FIND_USE_CMAKE_SYSTEM_PATH.html#variable:CMAKE_FIND_USE_CMAKE_SYSTEM_PATH)到`FALSE`.

   - `<prefix>/[s]bin`对于每个`<prefix>`在 [`CMAKE_SYSTEM_PREFIX_PATH`](https://cmake.org/cmake/help/latest/variable/CMAKE_SYSTEM_PREFIX_PATH.html#variable:CMAKE_SYSTEM_PREFIX_PATH)
   - [`CMAKE_SYSTEM_PROGRAM_PATH`](https://cmake.org/cmake/help/latest/variable/CMAKE_SYSTEM_PROGRAM_PATH.html#variable:CMAKE_SYSTEM_PROGRAM_PATH)
   - [`CMAKE_SYSTEM_APPBUNDLE_PATH`](https://cmake.org/cmake/help/latest/variable/CMAKE_SYSTEM_APPBUNDLE_PATH.html#variable:CMAKE_SYSTEM_APPBUNDLE_PATH)

   这些变量包含的平台路径是通常包含已安装软件的位置。一个例子是`/usr/local`基于 UNIX 的平台。

7. 搜索由 PATHS 选项或命令的简写版本指定的路径。这些通常是硬编码的猜测。

这[`CMAKE_IGNORE_PATH`](https://cmake.org/cmake/help/latest/variable/CMAKE_IGNORE_PATH.html#variable:CMAKE_IGNORE_PATH), [`CMAKE_IGNORE_PREFIX_PATH`](https://cmake.org/cmake/help/latest/variable/CMAKE_IGNORE_PREFIX_PATH.html#variable:CMAKE_IGNORE_PREFIX_PATH), [`CMAKE_SYSTEM_IGNORE_PATH`](https://cmake.org/cmake/help/latest/variable/CMAKE_SYSTEM_IGNORE_PATH.html#variable:CMAKE_SYSTEM_IGNORE_PATH)和 [`CMAKE_SYSTEM_IGNORE_PREFIX_PATH`](https://cmake.org/cmake/help/latest/variable/CMAKE_SYSTEM_IGNORE_PREFIX_PATH.html#variable:CMAKE_SYSTEM_IGNORE_PREFIX_PATH)变量也可能导致上述某些位置被忽略。

*3.16 版中的新功能：*添加`CMAKE_FIND_USE_<CATEGORY>_PATH`了全局禁用各种搜索位置的变量。

在 macOS 上[`CMAKE_FIND_FRAMEWORK`](https://cmake.org/cmake/help/latest/variable/CMAKE_FIND_FRAMEWORK.html#variable:CMAKE_FIND_FRAMEWORK)和 [`CMAKE_FIND_APPBUNDLE`](https://cmake.org/cmake/help/latest/variable/CMAKE_FIND_APPBUNDLE.html#variable:CMAKE_FIND_APPBUNDLE)变量决定了 Apple 风格和 unix 风格的包组件之间的优先顺序。

CMake 变量[`CMAKE_FIND_ROOT_PATH`](https://cmake.org/cmake/help/latest/variable/CMAKE_FIND_ROOT_PATH.html#variable:CMAKE_FIND_ROOT_PATH)指定要附加到所有其他搜索目录的一个或多个目录。这有效地“重新扎根”了给定位置下的整个搜索。路径的后代[`CMAKE_STAGING_PREFIX`](https://cmake.org/cmake/help/latest/variable/CMAKE_STAGING_PREFIX.html#variable:CMAKE_STAGING_PREFIX)被排除在此重新生根之外，因为该变量始终是主机系统上的路径。默认情况下[`CMAKE_FIND_ROOT_PATH`](https://cmake.org/cmake/help/latest/variable/CMAKE_FIND_ROOT_PATH.html#variable:CMAKE_FIND_ROOT_PATH)是空的。

这[`CMAKE_SYSROOT`](https://cmake.org/cmake/help/latest/variable/CMAKE_SYSROOT.html#variable:CMAKE_SYSROOT)变量也可以用来指定一个目录作为前缀。环境[`CMAKE_SYSROOT`](https://cmake.org/cmake/help/latest/variable/CMAKE_SYSROOT.html#variable:CMAKE_SYSROOT)还有其他作用。有关更多信息，请参阅该变量的文档。

这些变量在交叉编译指向目标环境的根目录时特别有用，CMake 也会在那里搜索。默认情况下，首先列出的目录 [`CMAKE_FIND_ROOT_PATH`](https://cmake.org/cmake/help/latest/variable/CMAKE_FIND_ROOT_PATH.html#variable:CMAKE_FIND_ROOT_PATH)被搜索，然后[`CMAKE_SYSROOT`](https://cmake.org/cmake/help/latest/variable/CMAKE_SYSROOT.html#variable:CMAKE_SYSROOT) 搜索目录，然后将搜索非根目录。默认行为可以通过设置来调整 [`CMAKE_FIND_ROOT_PATH_MODE_PROGRAM`](https://cmake.org/cmake/help/latest/variable/CMAKE_FIND_ROOT_PATH_MODE_PROGRAM.html#variable:CMAKE_FIND_ROOT_PATH_MODE_PROGRAM). 可以使用以下选项在每次调用的基础上手动覆盖此行为：

- `CMAKE_FIND_ROOT_PATH_BOTH`

  按上述顺序搜索。

- `NO_CMAKE_FIND_ROOT_PATH`

  不要使用[`CMAKE_FIND_ROOT_PATH`](https://cmake.org/cmake/help/latest/variable/CMAKE_FIND_ROOT_PATH.html#variable:CMAKE_FIND_ROOT_PATH)多变的。

- `ONLY_CMAKE_FIND_ROOT_PATH`

  仅搜索以下重新植根的目录和目录 [`CMAKE_STAGING_PREFIX`](https://cmake.org/cmake/help/latest/variable/CMAKE_STAGING_PREFIX.html#variable:CMAKE_STAGING_PREFIX).

默认搜索顺序旨在针对常见用例从最具体到最不具体。项目可以通过简单地多次调用命令并使用`NO_*`选项来覆盖顺序：

```cmake
find_program (<VAR> NAMES name PATHS 路径... NO_DEFAULT_PATH)
find_program (<VAR> NAMES 名称)
```

一旦其中一个调用成功，结果变量将被设置并存储在缓存中，这样就不会再次搜索调用。

当为选项提供多个值时`NAMES`，默认情况下此命令将一次考虑一个名称并在每个目录中搜索它。该`NAMES_PER_DIR`选项告诉此命令一次考虑一个目录并搜索其中的所有名称。



# 其他

## [execute_process](https://cmake.org/cmake/help/latest/command/execute_process.html)

执行一个或多个子进程。

```cmake
execute_process(COMMAND <cmd1> [<arguments>]
                [COMMAND <cmd2> [<arguments>]]...
                [WORKING_DIRECTORY <directory>]
                [TIMEOUT <seconds>]
                [RESULT_VARIABLE <variable>]
                [RESULTS_VARIABLE <variable>]
                [OUTPUT_VARIABLE <variable>]
                [ERROR_VARIABLE <variable>]
                [INPUT_FILE <file>]
                [OUTPUT_FILE <file>]
                [ERROR_FILE <file>]
                [OUTPUT_QUIET]
                [ERROR_QUIET]
                [COMMAND_ECHO <where>]
                [OUTPUT_STRIP_TRAILING_WHITESPACE]
                [ERROR_STRIP_TRAILING_WHITESPACE]
                [ENCODING <name>]
                [ECHO_OUTPUT_VARIABLE]
                [ECHO_ERROR_VARIABLE]
                [COMMAND_ERROR_IS_FATAL <ANY|LAST>])
```

运行一个或多个命令的给定序列。

命令作为管道同时执行，每个进程的标准输出通过管道传送到下一个进程的标准输入。单个标准错误管道用于所有进程。

选项：

- `COMMAND`

  子进程命令行。CMake 直接使用操作系统 API 执行子进程：在 POSIX 平台上，命令行以`argv[]`样式数组的形式传递给子进程。在 Windows 平台上，命令行被编码为字符串，以便子进程使用`CommandLineToArgvW`将解码原始参数。不使用中间 shell，因此 shell 运算符如`>` 被视为普通参数。（使用`INPUT_*`、`OUTPUT_*`和`ERROR_*`选项重定向标准输入、标准输出和标准错误。）如果需要顺序执行多个命令，请使用多个 [`execute_process()`](https://cmake.org/cmake/help/latest/command/execute_process.html#command:execute_process)使用单个`COMMAND`参数调用。

- `WORKING_DIRECTORY`

  命名目录将被设置为子进程的当前工作目录。

- `TIMEOUT`

  在指定的秒数（允许分数）之后，所有未完成的子进程将被终止，并将`RESULT_VARIABLE`设置为提及“超时”的字符串。

- `RESULT_VARIABLE`

  该变量将被设置为包含最后一个子进程的结果。这将是来自最后一个孩子的整数返回码或描述错误条件的字符串。

- `RESULTS_VARIABLE <variable>`

  *3.10 版中的新功能。*该变量将被设置为包含所有进程的结果作为 [分号分隔的列表](https://cmake.org/cmake/help/latest/manual/cmake-language.7.html#cmake-language-lists)，按照给定`COMMAND`参数的顺序排列。每个条目将是来自相应子项的整数返回代码或描述错误条件的字符串。

- `OUTPUT_VARIABLE`, `ERROR_VARIABLE`

  命名的变量将分别设置为标准输出和标准错误管道的内容。如果为两个管道命名相同的变量，则它们的输出将按生成的顺序合并。

- `INPUT_FILE, OUTPUT_FILE`,`ERROR_FILE`

  命名的文件将分别附加到第一个进程的标准输入、最后一个进程的标准输出或所有进程的标准错误。*3.3 版中的新功能：*如果为输出和错误命名相同的文件，那么它将用于两者。

- `OUTPUT_QUIET`, `ERROR_QUIET`

  标准输出或标准错误结果将被悄悄地忽略。

- `COMMAND_ECHO <where>`

  *3.15 版中的新功能。*正在运行的命令将被回显，`<where>`并`<where>` 设置为或`STDERR`之一。见`STDOUT``NONE`[`CMAKE_EXECUTE_PROCESS_COMMAND_ECHO`](https://cmake.org/cmake/help/latest/variable/CMAKE_EXECUTE_PROCESS_COMMAND_ECHO.html#variable:CMAKE_EXECUTE_PROCESS_COMMAND_ECHO)变量，用于控制不存在此选项时的默认行为。

- `ENCODING <name>`

  *3.8 版中的新功能。*在 Windows 上，用于解码进程输出的编码。在其他平台上被忽略。有效的编码名称是：`NONE`不执行解码。这假定进程输出的编码方式与 CMake 的内部编码 (UTF-8) 相同。这是默认设置。`AUTO`使用当前活动控制台的代码页，或者如果不可用，则使用 ANSI。`ANSI`使用 ANSI 代码页。`OEM`使用原始设备制造商 (OEM) 代码页。`UTF8`或者`UTF-8`使用 UTF-8 代码页。*3.11 版中的新功能：*接受`UTF-8`拼写以与 [UTF-8 RFC](https://www.ietf.org/rfc/rfc3629)命名约定保持一致。

- `ECHO_OUTPUT_VARIABLE`, `ECHO_ERROR_VARIABLE`

  *3.18 版中的新功能。*标准输出或标准错误不会专门重定向到配置的变量。输出将被复制，它将被发送到配置的变量中，也将发送到标准输出或标准错误中。这类似于`tee`Unix 命令。

- `COMMAND_ERROR_IS_FATAL <ANY|LAST>`

  *3.19 版中的新功能。*以下选项`COMMAND_ERROR_IS_FATAL`确定遇到错误时的行为：`ANY` 如果命令列表中的任何命令失败，则 `execute_process()`命令会因错误而停止。`LAST` 如果命令列表中的最后一个命令失败，则该 `execute_process()`命令会因错误而停止。列表中较早的命令不会导致致命错误。

如果为同一管道提供了多个`OUTPUT_*`or`ERROR_*`选项，则不指定优先级。如果没有给出`OUTPUT_*`或`ERROR_*`给出选项，则输出将与 CMake 进程本身的相应管道共享。

这[`execute_process()`](https://cmake.org/cmake/help/latest/command/execute_process.html#command:execute_process)command 是一个更新更强大的版本 [`exec_program()`](https://cmake.org/cmake/help/latest/command/exec_program.html#command:exec_program)，但为了兼容性，保留了旧命令。当 CMake 在生成系统之前处理项目时，这两个命令都会运行。利用[`add_custom_target()`](https://cmake.org/cmake/help/latest/command/add_custom_target.html#command:add_custom_target)和 [`add_custom_command()`](https://cmake.org/cmake/help/latest/command/add_custom_command.html#command:add_custom_command)创建在构建时运行的自定义命令。



## [get_cmake_property](https://cmake.org/cmake/help/latest/command/get_cmake_property.html)

获取 CMake 实例的全局属性。

```cmake
get_cmake_property(<var> <property>)
```

从 CMake 实例获取全局属性。的值`<property>`存储在变量 中`<var>`。如果未找到该属性，`<var>`将设置为`NOTFOUND`。见[`cmake-properties(7)`](https://cmake.org/cmake/help/latest/manual/cmake-properties.7.html#manual:cmake-properties(7))可用属性的手册。

另见[`get_property()`](https://cmake.org/cmake/help/latest/command/get_property.html#command:get_property)命令`GLOBAL`选项。

除了全局属性，这个命令（出于历史原因）还支持[`VARIABLES`](https://cmake.org/cmake/help/latest/prop_dir/VARIABLES.html#prop_dir:VARIABLES)和[`MACROS`](https://cmake.org/cmake/help/latest/prop_dir/MACROS.html#prop_dir:MACROS)目录属性。它还支持一个特殊的`COMPONENTS`全局属性，该属性列出了分配给[`install()`](https://cmake.org/cmake/help/latest/command/install.html#command:install)命令。



## [get_directory_property](https://cmake.org/cmake/help/latest/command/get_directory_property.html)

获取`DIRECTORY`范围属性。

```cmake
get_directory_property(<variable> [DIRECTORY <dir>] <prop-name>)
```

将目录范围的属性存储在命名的`<variable>`.

该`DIRECTORY`参数指定要从中检索属性值的另一个目录，而不是当前目录。相对路径被视为相对于当前源目录。CMake 必须已经知道该目录，或者通过调用添加它[`add_subdirectory()`](https://cmake.org/cmake/help/latest/command/add_subdirectory.html#command:add_subdirectory) 或者是顶级目录。

*3.19 新版功能：*`<dir>`可能引用二进制目录。

如果没有为指定的目录范围定义该属性，则返回一个空字符串。对于`INHERITED`属性，如果未找到指定目录范围的属性，则搜索将链接到父范围，如为 [`define_property()`](https://cmake.org/cmake/help/latest/command/define_property.html#command:define_property)命令。

```cmake
get_directory_property(<variable> [DIRECTORY <dir>]
                       DEFINITION <var-name>)
```

从目录中获取变量定义。这种形式对于从另一个目录获取变量定义很有用。

另见更一般的[`get_property()`](https://cmake.org/cmake/help/latest/command/get_property.html#command:get_property)命令。



## [get_filename_component](https://cmake.org/cmake/help/latest/command/get_filename_component.html)

获取完整文件名的特定组成部分。

*在 3.20 版更改:*此命令已被取代[`cmake_path()`](https://cmake.org/cmake/help/latest/command/cmake_path.html#command:cmake_path)命令，除了 `REALPATH`现在由[file(REAL_PATH)](https://cmake.org/cmake/help/latest/command/file.html#real-path)命令提供并且 `PROGRAM`现在可用于[`separate_arguments(PROGRAM)`](https://cmake.org/cmake/help/latest/command/separate_arguments.html#command:separate_arguments)命令。

*在 3.24 版更改：*提供查询`Windows` 注册表功能的未记录功能已被 [cmake_host_system_information(QUERY WINDOWS_REGISTRY)](https://cmake.org/cmake/help/latest/command/cmake_host_system_information.html#query-windows-registry) 命令取代。

```cmake
get_filename_component(<var> <FileName> <mode> [CACHE])
```

设置`<var>`为 的一个组件`<FileName>`，其中`<mode>`是以下之一：

```cmake
DIRECTORY = Directory without file name
NAME      = File name without directory
EXT       = File name longest extension (.b.c from d/a.b.c)
NAME_WE   = File name with neither the directory nor the longest extension
LAST_EXT  = File name last extension (.c from d/a.b.c)
NAME_WLE  = File name with neither the directory nor the last extension
PATH      = Legacy alias for DIRECTORY (use for CMake <= 2.8.11)
```

*3.14 新版功能：*添加了`LAST_EXT`和`NAME_WLE`模式。

路径以正斜杠返回，并且没有尾随斜杠。如果指定了可选`CACHE`参数，则将结果变量添加到缓存中。

```cmake
get_filename_component(<var> <FileName> <mode> [BASE_DIR <dir>] [CACHE])
```

*3.4 版中的新功能。*

设置`<var>`为 的绝对路径`<FileName>`，其中`<mode>`是以下之一：

```cmake
ABSOLUTE  = Full path to file
REALPATH  = Full path to existing file with symlinks resolved
```

如果提供`<FileName>`的是相对路径，则相对于给定的基本目录进行评估`<dir>`。如果未提供基本目录，则默认基本目录为 [`CMAKE_CURRENT_SOURCE_DIR`](https://cmake.org/cmake/help/latest/variable/CMAKE_CURRENT_SOURCE_DIR.html#variable:CMAKE_CURRENT_SOURCE_DIR).

路径以正斜杠返回，并且没有尾随斜杠。如果指定了可选`CACHE`参数，则将结果变量添加到缓存中。

```cmake
get_filename_component(<var> <FileName> PROGRAM [PROGRAM_ARGS <arg_var>] [CACHE])
```

该程序`<FileName>`将在系统搜索路径中找到或保留为完整路径。如果`PROGRAM_ARGS`与 一起`PROGRAM`存在，则`<FileName>`字符串中存在的任何命令行参数都会从程序名称中分离出来并存储在`<arg_var>`. 这用于将程序名称与其在命令行字符串中的参数分开。



## [get_property](https://cmake.org/cmake/help/latest/command/get_property.html)

获得财产。

```cmake
get_property(<variable>
             <GLOBAL             |
              DIRECTORY [<dir>]  |
              TARGET    <target> |
              SOURCE    <source>
                        [DIRECTORY <dir> | TARGET_DIRECTORY <target>] |
              INSTALL   <file>   |
              TEST      <test>   |
              CACHE     <entry>  |
              VARIABLE           >
             PROPERTY <name>
             [SET | DEFINED | BRIEF_DOCS | FULL_DOCS])
```

从范围内的一个对象中获取一个属性。

第一个参数指定存储结果的变量。第二个参数确定从中获取属性的范围。它必须是以下之一：

- `GLOBAL`

  范围是唯一的，不接受名称。

- `DIRECTORY`

  范围默认为当前目录，但另一个目录（已由 CMake 处理）可能由完整或相对路径命名`<dir>`。相对路径被视为相对于当前源目录。另见[`get_directory_property()`](https://cmake.org/cmake/help/latest/command/get_directory_property.html#command:get_directory_property)命令。*3.19 新版功能：*`<dir>`可能引用二进制目录。

- `TARGET`

  范围必须命名一个现有目标。另见[`get_target_property()`](https://cmake.org/cmake/help/latest/command/get_target_property.html#command:get_target_property)命令。

- `SOURCE`

  范围必须命名一个源文件。默认情况下，源文件的属性将从当前源目录的范围中读取。*3.18 版中的新增功能：*目录范围可以用以下子选项之一覆盖：`DIRECTORY <dir>`源文件属性将从`<dir>`目录的范围中读取。CMake 必须已经知道该目录，或者通过调用添加它[`add_subdirectory()`](https://cmake.org/cmake/help/latest/command/add_subdirectory.html#command:add_subdirectory)或者`<dir>`是顶级目录。相对路径被视为相对于当前源目录。*3.19 新版功能：*`<dir>`可能引用二进制目录。`TARGET_DIRECTORY <target>`源文件属性将从 `<target>`创建的目录范围中读取（`<target>`因此必须已经存在）。另见[`get_source_file_property()`](https://cmake.org/cmake/help/latest/command/get_source_file_property.html#command:get_source_file_property)命令。

- `INSTALL`

  *3.1 版中的新功能。*范围必须命名一个安装的文件路径。

- `TEST`

  范围必须命名一个现有的测试。另见[`get_test_property()`](https://cmake.org/cmake/help/latest/command/get_test_property.html#command:get_test_property)命令。

- `CACHE`

  范围必须命名一个缓存条目。

- `VARIABLE`

  范围是唯一的，不接受名称。

required`PROPERTY`选项后面紧跟要获取的属性的名称。如果未设置属性，则返回空值，尽管某些属性支持从父范围继承（如果定义为以这种方式执行）（请参阅[`define_property()`](https://cmake.org/cmake/help/latest/command/define_property.html#command:define_property)).

如果`SET`给定选项，则将变量设置为布尔值，指示是否已设置属性。如果`DEFINED` 给定了选项，则将变量设置为布尔值，指示是否已定义属性，例如 [`define_property()`](https://cmake.org/cmake/help/latest/command/define_property.html#command:define_property)命令。

如果给出`BRIEF_DOCS`或`FULL_DOCS`，则变量设置为包含请求属性文档的字符串。如果为尚未定义的属性请求文档， `NOTFOUND`则返回。

> **笔记** [`GENERATED`](https://cmake.org/cmake/help/latest/prop_sf/GENERATED.html#prop_sf:GENERATED)源文件属性可能是全局可见的。有关详细信息，请参阅其文档。



## [include](https://cmake.org/cmake/help/latest/command/include.html)

从文件或模块加载并运行 CMake 代码。

```cmake
include(<file|module> [OPTIONAL] [RESULT_VARIABLE <var>]
                      [NO_POLICY_SCOPE])
```

从给定的文件加载并运行 CMake 代码。变量读写访问调用者的范围（动态范围）。如果`OPTIONAL` 存在，则如果文件不存在，则不会引发错误。如果 `RESULT_VARIABLE`给出，变量`<var>`将被设置为已包含的完整文件名，或者`NOTFOUND`如果它失败。

如果指定了模块而不是文件， `<modulename>.cmake`则首先搜索具有名称的文件[`CMAKE_MODULE_PATH`](https://cmake.org/cmake/help/latest/variable/CMAKE_MODULE_PATH.html#variable:CMAKE_MODULE_PATH)，然后在 CMake 模块目录中。有一个例外：如果调用的文件`include()`本身位于 CMake 内置模块目录中，则首先搜索 CMake 内置模块目录并 [`CMAKE_MODULE_PATH`](https://cmake.org/cmake/help/latest/variable/CMAKE_MODULE_PATH.html#variable:CMAKE_MODULE_PATH)然后。另见政策[`CMP0017`](https://cmake.org/cmake/help/latest/policy/CMP0017.html#policy:CMP0017).

见[`cmake_policy()`](https://cmake.org/cmake/help/latest/command/cmake_policy.html#command:cmake_policy)用于讨论该 `NO_POLICY_SCOPE`选项的命令文档。



## [include_guard](https://cmake.org/cmake/help/latest/command/include_guard.html)

*3.10 版中的新功能。*

为 CMake 当前正在处理的文件提供包含保护。

```cmake
include_guard([DIRECTORY|GLOBAL])
```

为当前 CMake 文件设置包含保护（请参阅 [`CMAKE_CURRENT_LIST_FILE`](https://cmake.org/cmake/help/latest/variable/CMAKE_CURRENT_LIST_FILE.html#variable:CMAKE_CURRENT_LIST_FILE)可变文档）。

CMake 将在 [`include_guard()`](https://cmake.org/cmake/help/latest/command/include_guard.html#command:include_guard)如果当前文件已针对适用范围进行处理，则为命令（见下文）。这提供了类似于源头文件或指令中常用的包含保护的功能 。如果当前文件之前已针对适用范围进行过处理，则效果如同`#pragma once`[`return()`](https://cmake.org/cmake/help/latest/command/return.html#command:return)已被调用。不要从当前文件中定义的函数内部调用此命令。

可以提供指定防护范围的可选参数。该选项的可能值为：

- `DIRECTORY`

  包含保护适用于当前目录及以下目录。该文件只会在此目录范围内包含一次，但可能会被此目录之外的其他文件再次包含（即父目录或其他未被拉入的目录）[`add_subdirectory()`](https://cmake.org/cmake/help/latest/command/add_subdirectory.html#command:add_subdirectory)或者 [`include()`](https://cmake.org/cmake/help/latest/command/include.html#command:include)从当前文件或其子文件）。

- `GLOBAL`

  包含保护全局适用于整个构建。无论范围如何，当前文件都只会包含一次。

如果没有给定参数，`include_guard`则与变量具有相同的范围，这意味着如果不存在内部函数范围，则包含保护效果被最近的函数范围或当前目录隔离。在这种情况下，命令行为与以下内容相同：

```cmake
if(__CURRENT_FILE_VAR__)
  return()
endif()
set(__CURRENT_FILE_VAR__ TRUE)
```



## [mark_as_advanced](https://cmake.org/cmake/help/latest/command/mark_as_advanced.html)

将 cmake 缓存变量标记为高级。

```cmake
mark_as_advanced([CLEAR|FORCE] <var1> ...)
```

设置命名缓存变量的高级/非高级状态。

除非该选项打开，否则任何 cmake GUI 中都不会显示高级变量。在脚本模式下，高级/非高级状态无效。`show advanced`

如果给定关键字`CLEAR`，则高级变量将更改回未高级。如果给定关键字`FORCE`，则使变量高级。如果既未指定`FORCE`也未`CLEAR`指定，新值将被标记为高级，但如果变量已经具有高级/非高级状态，则不会更改。

*在 3.17 版更改:*传递给此命令但尚未在缓存中的变量将被忽略。查看政策[`CMP0102`](https://cmake.org/cmake/help/latest/policy/CMP0102.html#policy:CMP0102).



## [math](https://cmake.org/cmake/help/latest/command/math.html)

评估一个数学表达式。

```cmake
math(EXPR <variable> "<expression>" [OUTPUT_FORMAT <format>])
```

评估数学`<expression>`并设置`<variable>`为结果值。表达式的结果必须可以表示为 64 位有符号整数。

数学表达式必须以字符串形式给出（即用双引号括起来）。一个例子是`"5 * (10 + 13)"`。支持的运算符有 `+`, `-`, `*`, `/`, `%`, `|`, `&`, `^`, `~`, `<<`, `>>` 和`(...)`; 它们与 C 代码中的含义相同。

*3.13 版中的新增功能：*十六进制数字在前缀为 时被识别`0x`，就像在 C 代码中一样。

*3.13 版中的新功能：*结果根据选项格式化`OUTPUT_FORMAT`，其中`<format>`是其中之一

- `HEXADECIMAL`

  C 代码中的十六进制表示法，即以“0x”开头。

- `DECIMAL`

  十进制表示法。如果未`OUTPUT_FORMAT`指定选项，也会使用它。

例如

```cmake
math(EXPR value "100 * 0xA" OUTPUT_FORMAT DECIMAL)      # value is set to "1000"
math(EXPR value "100 * 0xA" OUTPUT_FORMAT HEXADECIMAL)  # value is set to "0x3e8"
```



## [separate_arguments](https://cmake.org/cmake/help/latest/command/separate_arguments.html)

将命令行参数解析为分号分隔的列表。

```cmake
separate_arguments(<variable> <mode> [PROGRAM [SEPARATE_ARGS]] <args>)
```

将空格分隔的字符串解析`<args>`为项目列表，并将此列表以分号分隔的标准格式存储在`<variable>`.

此函数用于解析命令行参数。整个命令行必须作为参数中的一个字符串传递`<args>`。

确切的解析规则取决于操作系统。它们由参数指定，该`<mode>`参数必须是以下关键字之一：

- `UNIX_COMMAND`

  参数由不带引号的空格分隔。单引号和双引号对都受到尊重。反斜杠转义下一个文字字符（`\"`is `"`）；没有特殊的转义（`\n`is just `n`）。

- `WINDOWS_COMMAND`

  使用运行时库用于在启动时构造 argv 的相同语法解析 Windows 命令行。它通过非双引号的空格分隔参数。反斜杠是文字，除非它们在双引号之前。有关详细信息，请参阅 MSDN 文章[Parsing C Command-Line Arguments](https://msdn.microsoft.com/library/a1y7w461.aspx)。

- `NATIVE_COMMAND`

  *3.9 版中的新功能。*`WINDOWS_COMMAND`如果主机系统是 Windows，则按模式进行。否则按`UNIX_COMMAND`模式进行。

- `PROGRAM`

  *3.19 版中的新功能。*假定其中的第一项`<args>`是可执行文件，并将在系统搜索路径中搜索或保留为完整路径。如果没有找到， `<variable>`将为空。否则，`<variable>`是 2 个元素的列表：程序的绝对路径`<args>`以字符串形式存在的任何命令行参数例如：`separate_arguments (out UNIX_COMMAND PROGRAM "cc -c main.c") `列表的第一个元素：`/path/to/cc`列表的第二个元素：`" -c main.c"`

- `SEPARATE_ARGS`

  当指定选项的这个子选项时`PROGRAM`，命令行参数也将被拆分并存储在`<variable>`.例如：`separate_arguments (out UNIX_COMMAND PROGRAM SEPARATE_ARGS "cc -c main.c") `将的内容`out`是：`/path/to/cc;-c;main.c`

```cmake
separate_arguments(<var>)
```

将 的值转换为`<var>`分号分隔的列表。所有空格都替换为';'。这有助于生成命令行。



## [site_name](https://cmake.org/cmake/help/latest/command/site_name.html)

将给定变量设置为计算机的名称。

```cmake
site_name(variable)
```

在类 UNIX 平台上，如果`HOSTNAME`设置了变量，则其值将作为预期打印出主机名的命令执行，与`hostname`命令行工具非常相似。



## [variable_watch](https://cmake.org/cmake/help/latest/command/variable_watch.html)

观察 CMake 变量的变化。

```cmake
variable_watch(<variable> [<command>])
```

如果指定的`<variable>`更改并且没有`<command>`给出，将打印一条消息以通知更改。

如果`<command>`给出，则将执行此命令。该命令将接收以下参数： `COMMAND(<variable> <access> <value> <current_list_file> <stack>)`

- `<variable>`

  正在访问的变量的名称。

- `<access>`

  `READ_ACCESS`, `UNKNOWN_READ_ACCESS`, `MODIFIED_ACCESS`, `UNKNOWN_MODIFIED_ACCESS`或之一`REMOVED_ACCESS`。这些`UNKNOWN_` 值仅在从未设置变量时使用。一旦设置，它们就不会在同一个 CMake 运行期间再次使用，即使该变量后来被取消设置。

- `<value>`

  变量的值。在修改时，这是变量的新（修改）值。删除时，该值为空。

- `<current_list_file>`

  进行访问的文件的完整路径。

- `<stack>`

  当前在文件包含堆栈上的所有文件的绝对路径列表，最底部的文件在前，当前处理的文件（即`current_list_file`）最后。

请注意，对于某些访问，例如[`list(APPEND)`](https://cmake.org/cmake/help/latest/command/list.html#command:list)，观察者被执行两次，首先是读访问，然后是写访问。另请注意，一个[`if(DEFINED)`](https://cmake.org/cmake/help/latest/command/if.html#command:if)对变量的查询不会注册为访问，并且不会执行观察者。

使用此命令只能查看非缓存变量。从不监视对缓存变量的访问。但是，缓存变量的存在`var`会导致对非缓存变量的`var`访问不使用`UNKNOWN_`前缀，即使非缓存变量`var` 从未存在过。