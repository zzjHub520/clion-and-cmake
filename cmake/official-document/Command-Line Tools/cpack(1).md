# cpack(1) 

## Synopsis

```
cpack [<options>]
```

## Description

cpack**可执行**文件是 CMake 打包程序。它生成各种格式的安装程序和源包。

对于每个安装程序或包格式，**cpack**都有一个特定的后端，称为“生成器”。生成器负责生成所需的输入并调用特定的包创建工具。不要将这些安装程序或软件包生成器与[`cmake`](https://cmake.org/cmake/help/latest/manual/cmake.1.html#manual:cmake(1))命令。

所有支持的生成器都在[`cpack-generators`](https://cmake.org/cmake/help/latest/manual/cpack-generators.7.html#manual:cpack-generators(7))手动的。该命令打印目标平台支持的生成器列表。可以通过`cpack --help`[`CPACK_GENERATOR`](https://cmake.org/cmake/help/latest/module/CPack.html#variable:CPACK_GENERATOR)变量或通过命令行选项`-G`。

cpack程序由编写 **在**[`CMake language`](https://cmake.org/cmake/help/latest/manual/cmake-language.7.html#manual:cmake-language(7)). 除非通过命令行选项以不同方式选择，否则将使用当前目录中`--config`的文件`CPackConfig.cmake` 。

在标准 CMake 工作流程中，文件`CPackConfig.cmake`由[`cmake`](https://cmake.org/cmake/help/latest/manual/cmake.1.html#manual:cmake(1))可执行，前提是[`CPack`](https://cmake.org/cmake/help/latest/module/CPack.html#module:CPack) 模块包含在项目的`CMakeLists.txt`文件中。

## Options

- `-G <generators>`

  `<generators>`是以[分号分隔](https://cmake.org/cmake/help/latest/manual/cmake-language.7.html#cmake-language-lists) 的生成器名称列表。 `cpack`将遍历此列表并根据`CPackConfig.cmake`配置文件中提供的详细信息生成该生成器格式的包。如果未给出此选项，则[`CPACK_GENERATOR`](https://cmake.org/cmake/help/latest/module/CPack.html#variable:CPACK_GENERATOR)变量确定将使用的默认生成器集。

- `-C <configs>`

  指定要打包的项目配置（例如`Debug`， `Release`等），其中`<configs>`是 [分号分隔的列表](https://cmake.org/cmake/help/latest/manual/cmake-language.7.html#cmake-language-lists)。当 CMake 项目使用多配置生成器（例如 Xcode 或 Visual Studio）时，需要此选项来告知 `cpack`要在包中包含哪些构建的可执行文件。用户负责确保列出的配置在调用之前已经构建`cpack`。

- `-D <var>=<value>`

  设置一个 CPack 变量。`<var>`这将覆盖在由 读取的输入文件中设置的任何值`cpack`。

- `--config <configFile>`

  指定读取的配置文件`cpack`以提供打包详细信息。默认情况下，`CPackConfig.cmake`会在当前目录中使用。

- `--verbose, -V`

  `cpack`以详细输出运行。这可用于显示包生成工具的更多细节，适合项目开发人员。

- `--debug`

  `cpack`使用调试输出运行。此选项主要供其`cpack`自身的开发人员使用，项目开发人员通常不需要。

- `--trace`

  将底层 cmake 脚本置于跟踪模式。

- `--trace-expand`

  将底层 cmake 脚本置于扩展跟踪模式。

- `-P <packageName>`

  覆盖/定义[`CPACK_PACKAGE_NAME`](https://cmake.org/cmake/help/latest/module/CPack.html#variable:CPACK_PACKAGE_NAME)用于包装的变量。`CPackConfig.cmake` 然后将忽略文件中为此变量设置的任何值。

- `-R <packageVersion>`

  覆盖/定义[`CPACK_PACKAGE_VERSION`](https://cmake.org/cmake/help/latest/module/CPack.html#variable:CPACK_PACKAGE_VERSION) 用于包装的变量。它将覆盖 `CPackConfig.cmake`文件中设置的值或自动计算的 值[`CPACK_PACKAGE_VERSION_MAJOR`](https://cmake.org/cmake/help/latest/module/CPack.html#variable:CPACK_PACKAGE_VERSION_MAJOR), [`CPACK_PACKAGE_VERSION_MINOR`](https://cmake.org/cmake/help/latest/module/CPack.html#variable:CPACK_PACKAGE_VERSION_MINOR)和 [`CPACK_PACKAGE_VERSION_PATCH`](https://cmake.org/cmake/help/latest/module/CPack.html#variable:CPACK_PACKAGE_VERSION_PATCH).

- `-B <packageDirectory>`

  覆盖/定义[`CPACK_PACKAGE_DIRECTORY`](https://cmake.org/cmake/help/latest/module/CPack.html#variable:CPACK_PACKAGE_DIRECTORY)，它控制 CPack 将执行其打包工作的目录。默认情况下，生成的包将在此位置创建，并且 `_CPack_Packages`还将在此目录下创建一个子目录，以在包创建期间用作工作区。

- `--vendor <vendorName>`

  覆盖/定义[`CPACK_PACKAGE_VENDOR`](https://cmake.org/cmake/help/latest/module/CPack.html#variable:CPACK_PACKAGE_VENDOR).

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