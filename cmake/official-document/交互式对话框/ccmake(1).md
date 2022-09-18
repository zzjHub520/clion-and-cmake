# ccmake(1) 

## Synopsis

```
ccmake [<options>] {<path-to-source> | <path-to-existing-build>}
```

## Description

**ccmake**可执行文件是CMake curses 接口。可以通过此 GUI 交互指定项目配置设置。程序运行时，终端底部会提供简要说明。

CMake 是一个跨平台的构建系统生成器。项目使用独立于平台的 CMake 列表文件指定其构建过程，该列表文件包含在名为`CMakeLists.txt`. 用户通过使用 CMake 为他们平台上的原生工具生成构建系统来构建项目。

## Options

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

## 另见

以下资源可用于获取使用 CMake 的帮助：

- 主页

  [https://cmake.org](https://cmake.org/)学习 CMake 的主要起点。

- 在线文档和社区资源

  https://cmake.org/documentation可在此网页上找到指向可用文档和社区资源的链接。

- 话语论坛

  [https://discourse.cmake.org](https://discourse.cmake.org/)Discourse Forum 主持有关 CMake 的讨论和问题。