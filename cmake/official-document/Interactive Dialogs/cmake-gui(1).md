# cmake-gui(1)

## Synopsis

```
cmake-gui [<options>]
cmake-gui [<options>] {<path-to-source> | <path-to-existing-build>}
cmake-gui [<options>] -S <path-to-source> -B <path-to-build>
cmake-gui [<options>] --browse-manual
```

## Description

**cmake-gui**可执行文件是CMake GUI。项目配置设置可以交互指定。程序运行时，窗口底部会提供简要说明。

CMake 是一个跨平台的构建系统生成器。项目使用独立于平台的 CMake 列表文件指定其构建过程，该列表文件包含在名为`CMakeLists.txt`. 用户通过使用 CMake 为他们平台上的原生工具生成构建系统来构建项目。

## Options

- `-S <path-to-source>`

  要构建的 CMake 项目的根目录的路径。

- `-B <path-to-build>`

  CMake 将用作构建目录的根目录的路径。如果该目录尚不存在，CMake 将创建它。

- `--preset=<preset-name>`

  项目中要使用的预设名称 [`presets`](https://cmake.org/cmake/help/latest/manual/cmake-presets.7.html#manual:cmake-presets(7))文件，如果有的话。

- `--browse-manual`

  在浏览器中打开 CMake 参考手册并立即退出。

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