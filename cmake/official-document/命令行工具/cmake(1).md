# cmake(1) 

## Synopsis

```cmake
生成项目构建系统
 cmake [<options>] <path-to-source>
 cmake [<options>] <path-to-existing-build>
 cmake [<options>] -S <path-to-source> -B <path-to-build>

建立一个项目
 cmake --build <dir> [<options>] [-- <build-tool-options>]

安装项目
 cmake --install <目录> [<选项>]

打开一个项目
 cmake --open <目录>

运行脚本
 cmake [{-D <var>=<value>}...] -P <cmake-script-file>

运行命令行工具
 cmake -E <命令> [<选项>]

运行查找包工具
 cmake --find-package [<选项>]

查看帮助
 cmake --help[-<topic>]
```

## Description

**cmake**可执行文件是跨平台构建系统生成器 CMake 的命令行界面。上述[概要](https://cmake.org/cmake/help/latest/manual/cmake.1.html#synopsis)列出了该工具可以执行的各种操作，如下节所述。

要使用 CMake 构建软件项目，[请生成项目构建系统](https://cmake.org/cmake/help/latest/manual/cmake.1.html#generate-a-project-buildsystem)。可选择使用**cmake**构建[项目](https://cmake.org/cmake/help/latest/manual/cmake.1.html#build-a-project)、[安装项目](https://cmake.org/cmake/help/latest/manual/cmake.1.html#install-a-project)或直接运行相应的构建工具（例如`make`）。 **cmake**也可以用来[查看帮助](https://cmake.org/cmake/help/latest/manual/cmake.1.html#view-help)。

其他操作旨在供软件开发人员在[`CMake language`](https://cmake.org/cmake/help/latest/manual/cmake-language.7.html#manual:cmake-language(7))支持他们的构建。

有关可用于代替**cmake**的图形用户界面，请参阅[`ccmake`](https://cmake.org/cmake/help/latest/manual/ccmake.1.html#manual:ccmake(1))和[`cmake-gui`](https://cmake.org/cmake/help/latest/manual/cmake-gui.1.html#manual:cmake-gui(1)). 有关 CMake 测试和打包工具的命令行界面，请参阅[`ctest`](https://cmake.org/cmake/help/latest/manual/ctest.1.html#manual:ctest(1))和[`cpack`](https://cmake.org/cmake/help/latest/manual/cpack.1.html#manual:cpack(1)).

有关 CMake 的更多信息，[另请参阅](https://cmake.org/cmake/help/latest/manual/cmake.1.html#see-also)本手册末尾的链接。

## CMake 构建系统简介

构建*系统*描述了如何使用*构建工具*从源代码构建项目的可执行文件和库以自动化该过程。例如，构建系统可以`Makefile`与命令行 `make`工具或集成开发环境 (IDE) 的项目文件一起使用。为了避免维护多个这样的构建系统，一个项目可以抽象地指定它的构建系统，使用写在 [`CMake language`](https://cmake.org/cmake/help/latest/manual/cmake-language.7.html#manual:cmake-language(7)). *从这些文件中，CMake 通过称为generator*的后端为每个用户在本地生成首选的构建系统。

要使用 CMake 生成构建系统，必须选择以下内容：

- 源树

  包含项目提供的源文件的顶级目录。该项目使用文件指定其构建系统，如 [`cmake-language(7)`](https://cmake.org/cmake/help/latest/manual/cmake-language.7.html#manual:cmake-language(7))手册，从名为 `CMakeLists.txt`. 这些文件指定构建目标及其依赖项，如[`cmake-buildsystem(7)`](https://cmake.org/cmake/help/latest/manual/cmake-buildsystem.7.html#manual:cmake-buildsystem(7))手动的。

- 构建树

  要存储构建系统文件和构建输出工件（例如可执行文件和库）的顶级目录。CMake 将编写一个`CMakeCache.txt`文件以将目录标识为构建树并存储持久性信息，例如构建系统配置选项。要维护原始源代码树，请使用单独的专用构建树执行*源外构建。*还支持将构建树放置在与源代码树相同的目录中的源内构建，但不鼓励使用*。*

- 发电机

  这会选择要生成的构建系统的类型。见 [`cmake-generators(7)`](https://cmake.org/cmake/help/latest/manual/cmake-generators.7.html#manual:cmake-generators(7))所有发电机的文档手册。运行以查看本地可用的生成器列表。可以选择使用下面的选项来指定生成器，或者简单地接受为当前平台选择的默认 CMake。`cmake --help``-G`当使用[命令行构建工具生成器](https://cmake.org/cmake/help/latest/manual/cmake-generators.7.html#command-line-build-tool-generators)之一时， CMake 期望编译器工具链所需的环境已在 shell 中配置。使用 [IDE Build Tool Generators](https://cmake.org/cmake/help/latest/manual/cmake-generators.7.html#ide-build-tool-generators)之一时，不需要特定的环境。



## 生成项目构建系统

使用以下命令签名之一运行 CMake 以指定源和构建树并生成构建系统：

- `cmake [<options>] <path-to-source>`

  使用当前工作目录作为构建树和 `<path-to-source>`源树。指定的路径可以是绝对路径，也可以是相对于当前工作目录的路径。源代码树必须包含一个`CMakeLists.txt`文件，并且 *不能*包含一个`CMakeCache.txt`文件，因为后者标识了一个现有的构建树。例如：`$ mkdir build ; cd build $ cmake ../src `

- `cmake [<options>] <path-to-existing-build>`

  用作`<path-to-existing-build>`构建树，并从其`CMakeCache.txt`文件加载源树的路径，该文件必须已由先前的 CMake 运行生成。指定的路径可以是绝对路径，也可以是相对于当前工作目录的路径。例如：`$ cd build $ cmake . `

- `cmake [<options>] -S <path-to-source> -B <path-to-build>`

  用作`<path-to-build>`构建树和`<path-to-source>` 源树。指定的路径可以是绝对路径，也可以是相对于当前工作目录的路径。源代码树必须包含一个 `CMakeLists.txt`文件。如果构建树不存在，将自动创建它。例如：`$ cmake -S src -B build `

在所有情况下，`<options>`可能是以下[选项](https://cmake.org/cmake/help/latest/manual/cmake.1.html#options)中的零个或多个。

上述指定源树和构建树的样式可以混合使用。`-S`用或指定的路径`-B`总是分别分类为源树或构建树。使用普通参数指定的路径根据其内容和前面给出的路径类型进行分类。如果只给出一种类型的路径，则当前工作目录 (cwd) 用于另一种。例如：

| 命令行                  | 源目录 | 构建目录 |
| :---------------------- | :----- | :------- |
| `cmake src`             | `src`  | cwd      |
| `cmake build`（现存的） | 加载   | `build`  |
| `cmake -S src`          | `src`  | cwd      |
| `cmake -S src build`    | `src`  | `build`  |
| `cmake -S src -B build` | `src`  | `build`  |
| `cmake -B build`        | cwd    | `build`  |
| `cmake -B build src`    | `src`  | `build`  |
| `cmake -B build -S src` | `src`  | `build`  |

*在 3.23 版更改:* CMake 在指定多个源路径时发出警告。这从未被正式记录或支持，但旧版本意外地接受了多个源路径并使用了指定的最后一个路径。避免传递多个源路径参数。

生成构建系统后，可以使用相应的原生构建工具来构建项目。例如，使用后 [`Unix Makefiles`](https://cmake.org/cmake/help/latest/generator/Unix Makefiles.html#generator:Unix Makefiles)生成器一可以`make`直接运行：

> ```
> $ make
> $ make install
> ```

或者，可以使用**cmake**通过自动选择和调用适当的本地构建工具来[构建项目。](https://cmake.org/cmake/help/latest/manual/cmake.1.html#build-a-project)



### Options

- `-S <path-to-source>`

  要构建的 CMake 项目的根目录的路径。

- `-B <path-to-build>`

  CMake 将用作构建目录的根目录的路径。如果该目录尚不存在，CMake 将创建它。

- `-C <initial-cache>`

  预加载脚本以填充缓存。当 CMake 第一次在空的构建树中运行时，它会创建一个 `CMakeCache.txt`文件并使用项目的可自定义设置填充它。此选项可用于指定在第一次通过项目的 CMake 列表文件之前从中加载缓存条目的文件。加载的条目优先于项目的默认值。给定的文件应该是一个 CMake 脚本，其中包含[`set()`](https://cmake.org/cmake/help/latest/command/set.html#command:set)使用该`CACHE`选项的命令，而不是缓存格式文件。参考资料[`CMAKE_SOURCE_DIR`](https://cmake.org/cmake/help/latest/variable/CMAKE_SOURCE_DIR.html#variable:CMAKE_SOURCE_DIR)和[`CMAKE_BINARY_DIR`](https://cmake.org/cmake/help/latest/variable/CMAKE_BINARY_DIR.html#variable:CMAKE_BINARY_DIR) 在脚本中评估顶级源代码和构建树。

- `-D <var>:<type>=<value>, -D <var>=<value>`

  创建或更新 CMake`CACHE`条目。当 CMake 第一次在空的构建树中运行时，它会创建一个 `CMakeCache.txt`文件并使用项目的可自定义设置填充它。此选项可用于指定优先于项目默认值的设置。该选项可以根据需要重复多个`CACHE`条目。如果`:<type>`给出该部分，则它必须是指定的类型之一[`set()`](https://cmake.org/cmake/help/latest/command/set.html#command:set)`CACHE`其签名的命令文档 。如果`:<type>`省略该部分，则如果条目不存在类型，则将创建不带类型的条目。如果项目中的命令将类型设置为`PATH`或`FILEPATH` 然后`<value>`将转换为绝对路径。此选项也可以作为单个参数给出： `-D<var>:<type>=<value>`或`-D<var>=<value>`.

- `-U <globbing_expr>`

  从 CMake 中删除匹配的条目`CACHE`。此选项可用于从文件中删除一个或多个变量 ，支持使用和通`CMakeCache.txt`配表达式。该选项可以根据需要重复多个条目。`*``?``CACHE`小心使用，你可以让你的`CMakeCache.txt`非工作。

- `-G <generator-name>`

  指定构建系统生成器。CMake 可能在某些平台上支持多个本机构建系统。生成器负责生成特定的构建系统。可能的生成器名称在 [`cmake-generators(7)`](https://cmake.org/cmake/help/latest/manual/cmake-generators.7.html#manual:cmake-generators(7))手动的。如果未指定，CMake 会检查[`CMAKE_GENERATOR`](https://cmake.org/cmake/help/latest/envvar/CMAKE_GENERATOR.html#envvar:CMAKE_GENERATOR)环境变量，否则回退到内置的默认选择。

- `-T <toolset-spec>`

  生成器的工具集规范（如果支持）。一些 CMake 生成器支持工具集规范来告诉本机构建系统如何选择编译器。见 [`CMAKE_GENERATOR_TOOLSET`](https://cmake.org/cmake/help/latest/variable/CMAKE_GENERATOR_TOOLSET.html#variable:CMAKE_GENERATOR_TOOLSET)变量以获取详细信息。

- `-A <platform-name>`

  如果生成器支持，请指定平台名称。一些 CMake 生成器支持为本地构建系统提供平台名称，以选择编译器或 SDK。见 [`CMAKE_GENERATOR_PLATFORM`](https://cmake.org/cmake/help/latest/variable/CMAKE_GENERATOR_PLATFORM.html#variable:CMAKE_GENERATOR_PLATFORM)变量以获取详细信息。

- `--toolchain <path-to-file>`

  指定交叉编译工具链文件，相当于设置 [`CMAKE_TOOLCHAIN_FILE`](https://cmake.org/cmake/help/latest/variable/CMAKE_TOOLCHAIN_FILE.html#variable:CMAKE_TOOLCHAIN_FILE)多变的。

- `--install-prefix <directory>`

  指定安装目录，由 [`CMAKE_INSTALL_PREFIX`](https://cmake.org/cmake/help/latest/variable/CMAKE_INSTALL_PREFIX.html#variable:CMAKE_INSTALL_PREFIX)多变的。必须是绝对路径。

- `-Wno-dev`

  禁止开发人员警告。禁止针对 `CMakeLists.txt`文件作者的警告。默认情况下，这也会关闭弃用警告。

- `-Wdev`

  启用开发人员警告。启用针对`CMakeLists.txt` 文件作者的警告。默认情况下，这也会打开弃用警告。

- `-Werror=dev`

  使开发人员警告错误。发出针对`CMakeLists.txt`文件错误作者的警告。默认情况下，这也会将不推荐使用的警告作为错误打开。

- `-Wno-error=dev`

  使开发人员警告而不是错误。发出针对`CMakeLists.txt`文件作者的警告而不是错误。默认情况下，这还将关闭已弃用的警告作为错误。

- `-Wdeprecated`

  启用不推荐使用的功能警告。启用针对`CMakeLists.txt`文件作者的已弃用功能的使用警告。

- `-Wno-deprecated`

  禁止不推荐使用的功能警告。禁止使用已弃用功能的警告，这些警告是针对`CMakeLists.txt`文件作者的。

- `-Werror=deprecated`

  使已弃用的宏和函数警告错误。对使用已弃用的宏和函数发出警告，这些宏和函数是针对`CMakeLists.txt`文件作者的错误。

- `-Wno-error=deprecated`

  使不推荐使用的宏和函数警告不是错误。对已弃用的宏和函数的使用发出警告，这些宏和函数是针对`CMakeLists.txt`文件作者的，而不是错误的。

- `--fresh`

  *版本 3.24 中的新功能。*执行构建树的全新配置。这将删除任何现有`CMakeCache.txt`文件和相关 `CMakeFiles/`目录，并从头开始重新创建它们。

- `-L[A][H]`

  列出非高级缓存变量。列出`CACHE`变量将运行 CMake 并列出 CMake`CACHE`中未标记为`INTERNAL`或的所有变量[`ADVANCED`](https://cmake.org/cmake/help/latest/prop_cache/ADVANCED.html#prop_cache:ADVANCED). 这将有效地显示当前的 CMake 设置，然后可以使用`-D`选项进行更改。更改某些变量可能会导致创建更多变量。如果`A`指定，则它还将显示高级变量。如果`H`指定，它还将显示每个变量的帮助。

- `-N`

  仅查看模式。只加载缓存。不要实际运行配置和生成步骤。

- `--graphviz=[file]`

  生成依赖关系的graphviz，请参见[`CMakeGraphVizOptions`](https://cmake.org/cmake/help/latest/module/CMakeGraphVizOptions.html#module:CMakeGraphVizOptions)更多。生成一个 graphviz 输入文件，该文件将包含项目中的所有库和可执行依赖项。请参阅文档 [`CMakeGraphVizOptions`](https://cmake.org/cmake/help/latest/module/CMakeGraphVizOptions.html#module:CMakeGraphVizOptions)更多细节。

- `--system-information [file]`

  转储有关此系统的信息。转储有关当前系统的广泛信息。如果从 CMake 项目的二叉树顶部运行，它将转储附加信息，例如缓存、日志文件等。

- `--log-level=<ERROR|WARNING|NOTICE|STATUS|VERBOSE|DEBUG|TRACE>`

  设置日志级别。这[`message()`](https://cmake.org/cmake/help/latest/command/message.html#command:message)命令只会输出指定日志级别或更高级别的消息。默认日志级别为`STATUS`.要使 CMake 运行之间的日志级别保持不变，请设置 [`CMAKE_MESSAGE_LOG_LEVEL`](https://cmake.org/cmake/help/latest/variable/CMAKE_MESSAGE_LOG_LEVEL.html#variable:CMAKE_MESSAGE_LOG_LEVEL)而是作为缓存变量。如果同时给出命令行选项和变量，则命令行选项优先。出于向后兼容性的原因，`--loglevel`也被接受为此选项的同义词。

- `--log-context`

  启用[`message()`](https://cmake.org/cmake/help/latest/command/message.html#command:message)命令输出附加到每条消息的上下文。此选项打开仅显示当前 CMake 运行的上下文。要使所有后续 CMake 运行的上下文持久显示，请设置 [`CMAKE_MESSAGE_CONTEXT_SHOW`](https://cmake.org/cmake/help/latest/variable/CMAKE_MESSAGE_CONTEXT_SHOW.html#variable:CMAKE_MESSAGE_CONTEXT_SHOW)而是作为缓存变量。当给出这个命令行选项时，[`CMAKE_MESSAGE_CONTEXT_SHOW`](https://cmake.org/cmake/help/latest/variable/CMAKE_MESSAGE_CONTEXT_SHOW.html#variable:CMAKE_MESSAGE_CONTEXT_SHOW) 被忽略。

- `--debug-trycompile`

  不要删除[`try_compile()`](https://cmake.org/cmake/help/latest/command/try_compile.html#command:try_compile)构建树。只对一个有用[`try_compile()`](https://cmake.org/cmake/help/latest/command/try_compile.html#command:try_compile)一次。不要删除为[`try_compile()`](https://cmake.org/cmake/help/latest/command/try_compile.html#command:try_compile) 来电。这在调试失败的 try_compiles 时很有用。但是，它可能会更改尝试编译的结果，因为来自先前尝试编译的旧垃圾可能会导致不同的测试错误地通过或失败。此选项最好一次用于一次尝试编译，并且仅在调试时使用。

- `--debug-output`

  将 cmake 置于调试模式。在 cmake 运行期间打印额外信息，如堆栈跟踪 [`message(SEND_ERROR)`](https://cmake.org/cmake/help/latest/command/message.html#command:message)来电。

- `--debug-find`

  将 cmake find 命令置于调试模式。在 cmake 运行期间将额外的查找调用信息打印到标准错误。输出是为人类消费而设计的，而不是为解析而设计的。另见[`CMAKE_FIND_DEBUG_MODE`](https://cmake.org/cmake/help/latest/variable/CMAKE_FIND_DEBUG_MODE.html#variable:CMAKE_FIND_DEBUG_MODE)用于调试项目的更多本地部分的变量。

- `--debug-find-pkg=<pkg>[,...]`

  在调用下运行时将 cmake find 命令置于调试模式[`find_package()`](https://cmake.org/cmake/help/latest/command/find_package.html#command:find_package)，其中`<pkg>` 是给定的逗号分隔的区分大小写的包名称列表中的条目。类似`--debug-find`，但将范围限制为指定的包。

- `--debug-find-var=<var>[,...]`

  `<var>` 当作为结果变量调用时，将 cmake find 命令置于调试模式，其中`<var>`是给定逗号分隔列表中的条目。类似`--debug-find`，但将范围限制为指定的变量名。

- `--trace`

  将 cmake 置于跟踪模式。打印所有呼叫的踪迹以及来自何处。

- `--trace-expand`

  将 cmake 置于跟踪模式。像`--trace`，但扩展了变量。

- `--trace-format=<format>`

  将 cmake 置于跟踪模式并设置跟踪输出格式。`<format>`可以是以下值之一。`human`以人类可读的格式打印每个跟踪行。这是默认格式。`json-v1`将每一行打印为单独的 JSON 文档。每个文档由换行符 ( `\n`) 分隔。保证 JSON 文档中不会出现换行符。JSON 跟踪格式：`{  "file": "/full/path/to/the/CMake/file.txt",  "line": 0,  "cmd": "add_executable",  "args": ["foo", "bar"],  "time": 1579512535.9687231,  "frame": 2,  "global_frame": 4 } `成员是：`file`调用函数的 CMake 源文件的完整路径。`line``file`函数调用开始的行。`line_end`如果函数调用跨越多行，则该字段将设置为函数调用结束的行。如果函数调用跨越单行，则该字段将被取消设置。此字段是在`json-v1`格式的次要版本 2 中添加的。`defer`函数调用被延迟时存在的可选成员[`cmake_language(DEFER)`](https://cmake.org/cmake/help/latest/command/cmake_language.html#command:cmake_language). 如果存在，它的值是一个包含延迟调用的字符串`<id>`。`cmd`被调用的函数的名称。`args`所有函数参数的字符串列表。`time`函数调用的时间戳（自纪元以来的秒数）。`frame``CMakeLists.txt`在当前正在处理的上下文中调用的函数的堆栈帧深度 。`global_frame`调用的函数的堆栈帧深度，在跟踪中涉及的所有`CMakeLists.txt`文件中全局跟踪。此字段是在`json-v1`格式的次要版本 2 中添加的。此外，输出的第一个 JSON 文档包含 `version`当前主要版本和次要版本的密钥JSON 跟踪格式：`{  "version": {    "major": 1,    "minor": 2  } } `成员是：`version`表示 JSON 格式的版本。该版本具有遵循语义版本约定的主要和次要组件。

- `--trace-source=<file>`

  将 cmake 置于跟踪模式，但只输出指定文件的行。允许多个选项。

- `--trace-redirect=<file>`

  将 cmake 置于跟踪模式并将跟踪输出重定向到文件而不是 stderr。

- `--warn-uninitialized`

  警告未初始化的值。使用未初始化的变量时打印警告。

- `--warn-unused-vars`

  什么也没做。在 CMake 版本 3.2 及以下版本中，启用了有关未使用变量的警告。在 CMake 版本 3.3 到 3.18 中，该选项已损坏。在 CMake 3.19 及更高版本中，该选项已被删除。

- `--no-warn-unused-cli`

  不要警告命令行选项。不要找到在命令行上声明但未使用的变量。

- `--check-system-vars`

  查找系统文件中变量使用的问题。通常，未使用和未初始化的变量只在[`CMAKE_SOURCE_DIR`](https://cmake.org/cmake/help/latest/variable/CMAKE_SOURCE_DIR.html#variable:CMAKE_SOURCE_DIR)和[`CMAKE_BINARY_DIR`](https://cmake.org/cmake/help/latest/variable/CMAKE_BINARY_DIR.html#variable:CMAKE_BINARY_DIR). 这个标志告诉 CMake 也警告其他文件。

- `--compile-no-warning-as-error`

  忽略目标属性[`COMPILE_WARNING_AS_ERROR`](https://cmake.org/cmake/help/latest/prop_tgt/COMPILE_WARNING_AS_ERROR.html#prop_tgt:COMPILE_WARNING_AS_ERROR)和变量 [`CMAKE_COMPILE_WARNING_AS_ERROR`](https://cmake.org/cmake/help/latest/variable/CMAKE_COMPILE_WARNING_AS_ERROR.html#variable:CMAKE_COMPILE_WARNING_AS_ERROR)，防止警告在编译时被视为错误。

- `--profiling-output=<path>`

  与 结合使用`--profiling-format`以输出到给定路径。

- `--profiling-format=<file>`

  启用以给定格式输出 CMake 脚本的分析数据。这可以帮助对执行的 CMake 脚本进行性能分析。应使用第三方应用程序将输出处理为人类可读的格式。当前支持的值为： `google-trace`Google Trace 格式的输出，可以通过 Google Chrome 的 [about:tracing](about:tracing)选项卡或使用 Trace Compass 等工具的插件进行解析。

- `--preset <preset>`, `--preset=<preset>`

  读取一个[`preset`](https://cmake.org/cmake/help/latest/manual/cmake-presets.7.html#manual:cmake-presets(7))从 `<path-to-source>/CMakePresets.json`和 `<path-to-source>/CMakeUserPresets.json`。预设可以指定生成器和构建目录，以及要传递给 CMake 的变量列表和其他参数。当前工作目录必须包含 CMake 预设文件。这[`CMake GUI`](https://cmake.org/cmake/help/latest/manual/cmake-gui.1.html#manual:cmake-gui(1))也可以识别`CMakePresets.json`和`CMakeUserPresets.json`归档。有关这些文件的完整详细信息，请参阅[`cmake-presets(7)`](https://cmake.org/cmake/help/latest/manual/cmake-presets.7.html#manual:cmake-presets(7)).在所有其他命令行选项之前读取预设。预设指定的选项（变量、生成器等）都可以通过在命令行上手动指定它们来覆盖。例如，如果预设设置了一个名为`MYVAR`to的变量`1`，但用户使用参数将其设置为`2`， 则首选`-D`该值。`2`

- `--list-presets, --list-presets=<[configure | build | test | all]>`

  列出可用的预设。如果未指定选项，则只会列出配置预设。当前工作目录必须包含 CMake 预设文件。



## 构建项目

CMake 提供了一个命令行签名来构建一个已经生成的项目二叉树：

```
cmake --build <dir>             [<options>] [-- <build-tool-options>]
cmake --build --preset <preset> [<options>] [-- <build-tool-options>]
```

这使用以下选项抽象了本机构建工具的命令行界面：

- `--build <dir>`

  要构建的项目二进制目录。这是必需的（除非指定了预设）并且必须是第一个。

- `--preset <preset>`, `--preset=<preset>`

  使用构建预设来指定构建选项。项目二进制目录是从`configurePreset`密钥中推断出来的。当前工作目录必须包含 CMake 预设文件。看[`preset`](https://cmake.org/cmake/help/latest/manual/cmake-presets.7.html#manual:cmake-presets(7))更多细节。

- `--list-presets`

  列出可用的构建预设。当前工作目录必须包含 CMake 预设文件。

- `--parallel [<jobs>], -j [<jobs>]`

  构建时使用的最大并发进程数。如果`<jobs>`省略，则使用本机构建工具的默认编号。这[`CMAKE_BUILD_PARALLEL_LEVEL`](https://cmake.org/cmake/help/latest/envvar/CMAKE_BUILD_PARALLEL_LEVEL.html#envvar:CMAKE_BUILD_PARALLEL_LEVEL)如果设置了环境变量，则在未给出此选项时指定默认的并行级别。一些原生构建工具总是并行构建。`<jobs>` value of的使用`1`可用于限制单个作业。

- `--target <tgt>..., -t <tgt>...`

  构建`<tgt>`而不是默认目标。可以给出多个目标，用空格分隔。

- `--config <cfg>`

  对于多配置工具，选择配置`<cfg>`。

- `--clean-first`

  先构建目标`clean`，然后构建。（仅清洁，使用。）`--target clean`

- `--resolve-package-references=<on|off|only>`

  *版本 3.23 中的新功能。*在构建之前解析来自外部包管理器（例如 NuGet）的远程包引用。当设置为`on`（默认）时，将在构建目标之前恢复包。设置为 时`only`，将恢复包，但不会执行构建。当设置为 时`off`，不会恢复任何包。如果目标未定义任何包引用，则此选项不执行任何操作。可以在构建预设中指定此设置（使用 `resolvePackageReferences`）。如果指定了此命令行选项，预设设置将被忽略。如果未提供命令行参数或预设选项，则将评估特定于环境的缓存变量以决定是否应执行包恢复。使用 Visual Studio 生成器时，包引用是使用[`VS_PACKAGE_REFERENCES`](https://cmake.org/cmake/help/latest/prop_tgt/VS_PACKAGE_REFERENCES.html#prop_tgt:VS_PACKAGE_REFERENCES)财产。使用 NuGet 恢复包引用。可以通过将 `CMAKE_VS_NUGET_PACKAGE_RESTORE`变量设置为 来禁用它`OFF`。

- `--use-stderr`

  忽略。行为在 CMake >= 3.0 中是默认的。

- `--verbose, -v`

  启用详细输出 - 如果支持 - 包括要执行的构建命令。此选项可以省略，如果[`VERBOSE`](https://cmake.org/cmake/help/latest/envvar/VERBOSE.html#envvar:VERBOSE)环境变量或 [`CMAKE_VERBOSE_MAKEFILE`](https://cmake.org/cmake/help/latest/variable/CMAKE_VERBOSE_MAKEFILE.html#variable:CMAKE_VERBOSE_MAKEFILE)缓存变量已设置。

- `--`

  将剩余选项传递给本机工具。

在没有快速帮助选项的情况下运行。`cmake --build`

## 安装项目

CMake 提供了一个命令行签名来安装已经生成的项目二叉树：

```
cmake --install <dir> [<options>]
```

这可以在构建项目以运行安装后使用，而无需使用生成的构建系统或本机构建工具。选项包括：

- `--install <dir>`

  要安装的项目二进制目录。这是必需的，并且必须是第一个。

- `--config <cfg>`

  对于多配置生成器，请选择配置`<cfg>`。

- `--component <comp>`

  基于组件的安装。只安装组件`<comp>`。

- `--default-directory-permissions <permissions>`

  默认目录安装权限。格式的权限`<u=rwx,g=rx,o=rx>`。

- `--prefix <prefix>`

  覆盖安装前缀，[`CMAKE_INSTALL_PREFIX`](https://cmake.org/cmake/help/latest/variable/CMAKE_INSTALL_PREFIX.html#variable:CMAKE_INSTALL_PREFIX).

- `--strip`

  安装前剥离。

- `-v, --verbose`

  启用详细输出。此选项可以省略，如果[`VERBOSE`](https://cmake.org/cmake/help/latest/envvar/VERBOSE.html#envvar:VERBOSE)环境变量已设置。

在没有快速帮助选项的情况下运行。`cmake --install`

## 打开项目

```
cmake --open <dir>
```

在关联的应用程序中打开生成的项目。这仅受某些生成器支持。



## 运行脚本

```
cmake [{-D <var>=<value>}...] -P <cmake-script-file> [-- <unparsed-options>...]
```

将给定的 cmake 文件作为用 CMake 语言编写的脚本处理。不执行配置或生成步骤，也不修改缓存。如果使用 定义变量`-D`，则必须在`-P`参数之前完成。

之后的任何选项`--`都不会被 CMake 解析，但它们仍然包含在[`CMAKE_ARGV`](https://cmake.org/cmake/help/latest/variable/CMAKE_ARGV0.html#variable:CMAKE_ARGV0)传递给脚本的变量（包括`--`自身）。



## 运行命令行工具

CMake 通过签名提供内置的命令行工具

```
cmake -E <command> [<options>]
```

运行或获取命令摘要。可用的命令有：`cmake -E``cmake -E help`

- `capabilities`

  *3.7 版中的新功能。*以 JSON 格式报告 cmake 功能。输出是一个带有以下键的 JSON 对象：`version`带有版本信息的 JSON 对象。关键是：`string`cmake 显示的完整版本字符串`--version`。`major`整数形式的主版本号。`minor`整数形式的次要版本号。`patch`整数形式的补丁级别。`suffix`cmake 版本后缀字符串。`isDirty`如果 cmake 构建来自脏树，则设置一个布尔值。`generators`可用生成器列表。每个生成器都是一个带有以下键的 JSON 对象：`name`包含生成器名称的字符串。`toolsetSupport``true`如果生成器支持工具集等`false`。`platformSupport``true`如果生成器支持平台等`false`。`supportedPlatforms`*3.21 版中的新功能。*当生成器通过以下方式支持平台规范时可能存在的可选成员[`CMAKE_GENERATOR_PLATFORM`](https://cmake.org/cmake/help/latest/variable/CMAKE_GENERATOR_PLATFORM.html#variable:CMAKE_GENERATOR_PLATFORM) ( )。该值是已知支持的平台列表。`-A ...``extraGenerators`与生成器兼容的所有额外生成器的字符串列表。`fileApi`出现时的可选成员[`cmake-file-api(7)`](https://cmake.org/cmake/help/latest/manual/cmake-file-api.7.html#manual:cmake-file-api(7)) 可用。该值是一个具有一个成员的 JSON 对象：`requests`一个 JSON 数组，包含零个或多个受支持的文件 API 请求。每个请求都是一个带有成员的 JSON 对象：`kind`指定一种受支持的[对象种类](https://cmake.org/cmake/help/latest/manual/cmake-file-api.7.html#file-api-object-kinds)。`version`一个 JSON 数组，其元素都是一个 JSON 对象，其中包含 指定非负整数版本组件的成员`major`。`minor``serverMode``true`如果 cmake 支持服务器模式，`false`否则。自 CMake 3.20 以来总是错误的。

- `cat [--] <files>...`

  *3.18 版中的新功能。*连接文件并在标准输出上打印。*3.24 新版功能：*添加了对双破折号参数的支持`--`。这个基本实现`cat`不支持任何选项，所以使用以 开头的选项 `-`会导致错误。用于`--`指示选项的结束，以防文件以`-`.

- `chdir <dir> <cmd> [<arg>...]`

  更改当前工作目录并运行命令。

- `compare_files [--ignore-eol] <file1> <file2>`

  检查是否`<file1>`与`<file2>`. 如果文件相同，则返回`0`，否则返回`1`。如果参数无效，则返回 2。*3.14 版中的新增功能：*该`--ignore-eol`选项意味着逐行比较并忽略 LF/CRLF 差异。

- `copy <file>... <destination>`

  将文件复制到`<destination>`（文件或目录）。如果指定了多个文件，则`<destination>`必须是目录并且必须存在。不支持通配符。 `copy`确实遵循符号链接。这意味着它不会复制符号链接，而是它指向的文件或目录。*3.5 版新功能：*支持多个输入文件。

- `copy_directory <dir>... <destination>`

  将目录的内容复制`<dir>...`到`<destination>`目录。如果`<destination>`目录不存在，它将被创建。 `copy_directory`确实遵循符号链接。*3.5 版新功能：*支持多个输入目录。*3.15 新版功能：*当源目录不存在时，该命令现在会失败。以前它通过创建一个空的目标目录而成功。

- `copy_if_different <file>... <destination>`

  如果文件已更改，则将文件复制到`<destination>`（文件或目录）。如果指定了多个文件，则`<destination>`必须是目录并且必须存在。 `copy_if_different`确实遵循符号链接。*3.5 版新功能：*支持多个输入文件。

- `create_symlink <old> <new>`

  创建符号链接`<new>`命名`<old>`。*3.13 版新功能：*支持在 Windows 上创建符号链接。笔记 创建符号链接的路径必须`<new>`事先存在。

- `create_hardlink <old> <new>`

  *3.19 版中的新功能。*创建硬链接`<new>`命名`<old>`。笔记 `<new>`必须事先存在创建硬链接 的路径。`<old>`必须事先存在。

- `echo [<string>...]`

  将参数显示为文本。

- `echo_append [<string>...]`

  将参数显示为文本但不显示新行。

- `env [--unset=NAME ...] [NAME=VALUE ...] [--] <command> [<arg>...]`

  *3.1 版中的新功能。*在修改后的环境中运行命令。*3.24 新版功能：*添加了对双破折号参数的支持`--`。用于`--`停止解释选项/环境变量并将下一个参数视为命令，即使它`-`以`=`.

- `environment`

  显示当前环境变量。

- `false`

  *3.16 版中的新功能。*什么都不做，退出代码为 1。

- `make_directory <dir>...`

  创建`<dir>`目录。如有必要，也创建父目录。如果目录已经存在，它将被静默忽略。*3.5 版新功能：*支持多个输入目录。

- `md5sum <file>...`

  `md5sum`以兼容格式创建文件的 MD5 校验和：`351abe79cd3800b38cdfb25d45015a15  file1.txt 052f86c15bbde68af55c7f7b340ab639  file2.txt `

- `sha1sum <file>...`

  *3.10 版中的新功能。*`sha1sum`以兼容格式创建文件的 SHA1 校验和：`4bb7932a29e6f73c97bb9272f2bdc393122f86e0  file1.txt 1df4c8f318665f9a5f2ed38f55adadb7ef9f559c  file2.txt `

- `sha224sum <file>...`

  *3.10 版中的新功能。*`sha224sum`以兼容格式创建文件的 SHA224 校验和：`b9b9346bc8437bbda630b0b7ddfc5ea9ca157546dbbf4c613192f930  file1.txt 6dfbe55f4d2edc5fe5c9197bca51ceaaf824e48eba0cc453088aee24  file2.txt `

- `sha256sum <file>...`

  *3.10 版中的新功能。*`sha256sum`以兼容格式创建文件的 SHA256 校验和：`76713b23615d31680afeb0e9efe94d47d3d4229191198bb46d7485f9cb191acc  file1.txt 15b682ead6c12dedb1baf91231e1e89cfc7974b3787c1e2e01b986bffadae0ea  file2.txt `

- `sha384sum <file>...`

  *3.10 版中的新功能。*`sha384sum`以兼容格式创建文件的 SHA384 校验和：`acc049fedc091a22f5f2ce39a43b9057fd93c910e9afd76a6411a28a8f2b8a12c73d7129e292f94fc0329c309df49434  file1.txt 668ddeb108710d271ee21c0f3acbd6a7517e2b78f9181c6a2ff3b8943af92b0195dcb7cce48aa3e17893173c0a39e23d  file2.txt `

- `sha512sum <file>...`

  *3.10 版中的新功能。*`sha512sum`以兼容格式创建文件的 SHA512 校验和：`2a78d7a6c5328cfb1467c63beac8ff21794213901eaadafd48e7800289afbc08e5fb3e86aa31116c945ee3d7bf2a6194489ec6101051083d1108defc8e1dba89  file1.txt 7a0b54896fe5e70cca6dd643ad6f672614b189bf26f8153061c4d219474b05dad08c4e729af9f4b009f1a1a280cb625454bf587c690f4617c27e3aebdf3b7a2d  file2.txt `

- `remove [-f] <file>...`

  *自 3.17 版起已弃用。*删除文件。计划的行为是，如果任何列出的文件不存在，该命令将返回非零退出代码，但不记录任何消息。该`-f`选项将行为更改为在这种情况下返回零退出代码（即成功）。 `remove`不遵循符号链接。这意味着它只删除符号链接而不是它指向的文件。实现是错误的，总是返回 0。如果不破坏向后兼容性，就无法修复它。改为使用`rm`。

- `remove_directory <dir>...`

  *自 3.17 版起已弃用。*删除`<dir>`目录及其内容。如果目录不存在，它将被静默忽略。改为使用`rm`。*3.15 版新功能：*支持多个目录。*3.16 新版功能：*如果`<dir>`是指向目录的符号链接，则只会删除符号链接。

- `rename <oldname> <newname>`

  重命名文件或目录（在一个卷上）。如果`<newname>`同名文件已经存在，那么它将被静默替换。

- `rm [-rRf] [--] <file|dir>...`

  *版本 3.17 中的新功能。*删除文件`<file>`或目录`<dir>`。使用`-r`或`-R`递归删除目录及其内容。如果任何列出的文件/目录不存在，该命令将返回非零退出代码，但不记录任何消息。该`-f`选项将行为更改为在这种情况下返回零退出代码（即成功）。用于`--`停止解释选项并将所有剩余参数视为路径，即使它们以`-`.

- `server`

  发射[`cmake-server(7)`](https://cmake.org/cmake/help/latest/manual/cmake-server.7.html#manual:cmake-server(7))模式。

- `sleep <number>...`

  *3.0 版中的新功能。*休眠给定的秒数。

- `tar [cxt][vf][zjJ] file.tar [<options>] [--] [<pathname>...]`

  创建或提取 tar 或 zip 存档。选项是：`c`创建一个包含指定文件的新存档。如果使用，`<pathname>...`参数是强制性的。`x`从存档中提取到磁盘。*3.15 新版功能：*该`<pathname>...`参数可用于仅提取选定的文件或目录。提取选定的文件或目录时，您必须提供它们的确切名称，包括路径，如列表 ( `-t`) 所示。`t`列出存档内容。*3.15 新版功能：*该`<pathname>...`参数可用于仅列出选定的文件或目录。`v`产生详细的输出。`z`使用 gzip 压缩生成的存档。`j`使用 bzip2 压缩生成的存档。`J`*3.1 版中的新功能。*使用 XZ 压缩生成的存档。`--zstd`*3.15 版中的新功能。*使用 Zstandard 压缩生成的存档。`--files-from=<file>`*3.1 版中的新功能。*从给定文件中读取文件名，每行一个。空白行被忽略。除了添加名称`-` 以.`--add-file=<name>``-``--format=<format>`*3.3 版中的新功能。*指定要创建的存档的格式。支持的格式有：`7zip`, `gnutar`, `pax`, `paxr`(restricted pax, default), 和`zip`.`--mtime=<date>`*3.1 版中的新功能。*指定记录在 tarball 条目中的修改时间。`--touch`*版本 3.24 中的新功能。*使用当前本地时间戳，而不是从存档中提取文件时间戳。`--`*3.1 版中的新功能。*停止解释选项并将所有剩余的参数视为文件名，即使它们以`-`.*3.1 版中的新功能：* LZMA (7zip) 支持。*3.15 版中的新功能：*该命令现在继续将文件添加到存档中，即使某些文件不可读。这种行为更符合经典 `tar`工具。该命令现在还解析所有标志，如果提供了无效标志，则会发出警告。

- `time <command> [<args>...]`

  运行命令并显示经过的时间。*3.5 版中的新功能：*该命令现在可以正确地将带有空格或特殊字符的参数传递给子进程。这可能会破坏通过自己的额外引用或转义来解决错误的脚本。

- `touch <file>...`

  `<file>`如果文件不存在则创建。如果`<file>`存在，它正在改变`<file>`访问和修改时间。

- `touch_nocreate <file>...`

  如果文件存在，请触摸文件，但不要创建它。如果文件不存在，它将被静默忽略。

- `true`

  *3.16 版中的新功能。*什么都不做，退出代码为 0。

### 特定于 Windows 的命令行工具

以下命令仅在 Windows 上可用：`cmake -E`

- `delete_regv <key>`

  删除 Windows 注册表值。

- `env_vs8_wince <sdkname>`

  *3.2 版中的新功能。*显示一个批处理文件，该文件为安装在 VS2005 中提供的 Windows CE SDK 设置环境。

- `env_vs9_wince <sdkname>`

  *3.2 版中的新功能。*显示一个批处理文件，该文件为安装在 VS2008 中提供的 Windows CE SDK 设置环境。

- `write_regv <key> <value>`

  写入 Windows 注册表值。

## 运行查找包工具

CMake 为基于 Makefile 的项目提供了类似 pkg-config 的帮助程序：

```
cmake --find-package [<options>]
```

它使用搜索包[`find_package()`](https://cmake.org/cmake/help/latest/command/find_package.html#command:find_package)并将生成的标志打印到标准输出。这可以用来代替 pkg-config 在基于 Makefile 的普通项目或基于 autoconf 的项目中查找已安装的库（通过`share/aclocal/cmake.m4`）。

笔记

 

由于一些技术限制，这种模式没有得到很好的支持。它是为了兼容性而保留的，但不应在新项目中使用。

## 查看帮助

要打印 CMake 文档中的选定页面，请使用

```
cmake --help[-<topic>]
```

具有以下选项之一：

- `--help,-help,-usage,-h,-H,/?`

  打印使用信息并退出。用法描述了基本的命令行界面及其选项。

- `--version,-version,/V [<f>]`

  显示程序名称/版本横幅并退出。如果指定了文件，则将版本写入其中。如果给定，帮助将打印到命名的 <f> 文件。

- `--help-full [<f>]`

  打印所有帮助手册并退出。所有手册均以人类可读的文本格式打印。如果给定，帮助将打印到命名的 <f> 文件。

- `--help-manual <man> [<f>]`

  打印一份帮助手册并退出。指定的手册以人类可读的文本格式打印。如果给定，帮助将打印到命名的 <f> 文件。

- `--help-manual-list [<f>]`

  列出可用的帮助手册并退出。该列表包含所有可以通过使用`--help-manual`后跟手册名称的选项获得帮助的手册。如果给定，帮助将打印到命名的 <f> 文件。

- `--help-command <cmd> [<f>]`

  打印一个命令的帮助并退出。这[`cmake-commands(7)`](https://cmake.org/cmake/help/latest/manual/cmake-commands.7.html#manual:cmake-commands(7))手动输入以`<cmd>`人类可读的文本格式打印。如果给定，帮助将打印到命名的 <f> 文件。

- `--help-command-list [<f>]`

  列出可用帮助的命令并退出。该列表包含可以通过使用`--help-command`后跟命令名称的选项获得帮助的所有命令。如果给定，帮助将打印到命名的 <f> 文件。

- `--help-commands [<f>]`

  打印 cmake-commands 手册并退出。这[`cmake-commands(7)`](https://cmake.org/cmake/help/latest/manual/cmake-commands.7.html#manual:cmake-commands(7))手册以人类可读的文本格式打印。如果给定，帮助将打印到命名的 <f> 文件。

- `--help-module <mod> [<f>]`

  打印一个模块的帮助并退出。这[`cmake-modules(7)`](https://cmake.org/cmake/help/latest/manual/cmake-modules.7.html#manual:cmake-modules(7))手动输入以`<mod>`人类可读的文本格式打印。如果给定，帮助将打印到命名的 <f> 文件。

- `--help-module-list [<f>]`

  列出可用帮助的模块并退出。该列表包含可以通过使用`--help-module`后跟模块名称的选项获得帮助的所有模块。如果给定，帮助将打印到命名的 <f> 文件。

- `--help-modules [<f>]`

  打印 cmake-modules 手册并退出。这[`cmake-modules(7)`](https://cmake.org/cmake/help/latest/manual/cmake-modules.7.html#manual:cmake-modules(7))手册以人类可读的文本格式打印。如果给定，帮助将打印到命名的 <f> 文件。

- `--help-policy <cmp> [<f>]`

  打印一项政策的帮助并退出。这[`cmake-policies(7)`](https://cmake.org/cmake/help/latest/manual/cmake-policies.7.html#manual:cmake-policies(7))手动输入以`<cmp>`人类可读的文本格式打印。如果给定，帮助将打印到命名的 <f> 文件。

- `--help-policy-list [<f>]`

  列出有可用帮助的策略并退出。`--help-policy`该列表包含通过使用后跟策略名称的选项可以获得帮助的所有策略。如果给定，帮助将打印到命名的 <f> 文件。

- `--help-policies [<f>]`

  打印 cmake-policies 手册并退出。这[`cmake-policies(7)`](https://cmake.org/cmake/help/latest/manual/cmake-policies.7.html#manual:cmake-policies(7))手册以人类可读的文本格式打印。如果给定，帮助将打印到命名的 <f> 文件。

- `--help-property <prop> [<f>]`

  打印一个属性的帮助并退出。这[`cmake-properties(7)`](https://cmake.org/cmake/help/latest/manual/cmake-properties.7.html#manual:cmake-properties(7))的手动条目以`<prop>`人类可读的文本格式打印。如果给定，帮助将打印到命名的 <f> 文件。

- `--help-property-list [<f>]`

  列出可用帮助的属性并退出。该列表包含可以通过使用`--help-property`后跟属性名称的选项获得帮助的所有属性。如果给定，帮助将打印到命名的 <f> 文件。

- `--help-properties [<f>]`

  打印 cmake-properties 手册并退出。这[`cmake-properties(7)`](https://cmake.org/cmake/help/latest/manual/cmake-properties.7.html#manual:cmake-properties(7))手册以人类可读的文本格式打印。如果给定，帮助将打印到命名的 <f> 文件。

- `--help-variable <var> [<f>]`

  打印一个变量的帮助并退出。这[`cmake-variables(7)`](https://cmake.org/cmake/help/latest/manual/cmake-variables.7.html#manual:cmake-variables(7))手动输入以`<var>`人类可读的文本格式打印。如果给定，帮助将打印到命名的 <f> 文件。

- `--help-variable-list [<f>]`

  列出可用帮助的变量并退出。该列表包含可以通过使用`--help-variable`后跟变量名的选项获得帮助的所有变量。如果给定，帮助将打印到命名的 <f> 文件。

- `--help-variables [<f>]`

  打印 cmake-variables 手册并退出。这[`cmake-variables(7)`](https://cmake.org/cmake/help/latest/manual/cmake-variables.7.html#manual:cmake-variables(7))手册以人类可读的文本格式打印。如果给定，帮助将打印到命名的 <f> 文件。

要查看可用于项目的预设，请使用

```
cmake <source-dir> --list-presets
```



## 返回值（退出代码）

定期终止时，`cmake`可执行文件返回退出代码`0`。

如果终止是由命令引起的[`message(FATAL_ERROR)`](https://cmake.org/cmake/help/latest/command/message.html#command:message)，或其他错误条件，则返回非零退出代码。

## 另见

以下资源可用于获取使用 CMake 的帮助：

- 主页

  [https://cmake.org](https://cmake.org/)学习 CMake 的主要起点。

- 在线文档和社区资源

  https://cmake.org/documentation可在此网页上找到指向可用文档和社区资源的链接。

- 话语论坛

  [https://discourse.cmake.org](https://discourse.cmake.org/)Discourse Forum 主持有关 CMake 的讨论和问题。