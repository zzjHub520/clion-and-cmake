# [ctest(1) ](https://cmake.org/cmake/help/latest/manual/ctest.1.html#id14)

内容

- [测试(1)](https://cmake.org/cmake/help/latest/manual/ctest.1.html#ctest-1)
  - [概要](https://cmake.org/cmake/help/latest/manual/ctest.1.html#synopsis)
  - [描述](https://cmake.org/cmake/help/latest/manual/ctest.1.html#description)
  - [选项](https://cmake.org/cmake/help/latest/manual/ctest.1.html#options)
  - [标签匹配](https://cmake.org/cmake/help/latest/manual/ctest.1.html#label-matching)
  - [标签和子项目摘要](https://cmake.org/cmake/help/latest/manual/ctest.1.html#label-and-subproject-summary)
  - [构建和测试模式](https://cmake.org/cmake/help/latest/manual/ctest.1.html#build-and-test-mode)
  - [仪表板客户端](https://cmake.org/cmake/help/latest/manual/ctest.1.html#dashboard-client)
    - [仪表板客户端步骤](https://cmake.org/cmake/help/latest/manual/ctest.1.html#dashboard-client-steps)
    - [仪表板客户端模式](https://cmake.org/cmake/help/latest/manual/ctest.1.html#dashboard-client-modes)
    - [通过 CTest 命令行的仪表板客户端](https://cmake.org/cmake/help/latest/manual/ctest.1.html#dashboard-client-via-ctest-command-line)
    - [通过 CTest 脚本的仪表板客户端](https://cmake.org/cmake/help/latest/manual/ctest.1.html#dashboard-client-via-ctest-script)
  - [仪表板客户端配置](https://cmake.org/cmake/help/latest/manual/ctest.1.html#dashboard-client-configuration)
    - [CTest 开始步骤](https://cmake.org/cmake/help/latest/manual/ctest.1.html#ctest-start-step)
    - [CTest 更新步骤](https://cmake.org/cmake/help/latest/manual/ctest.1.html#ctest-update-step)
    - [CTest 配置步骤](https://cmake.org/cmake/help/latest/manual/ctest.1.html#ctest-configure-step)
    - [CTest 构建步骤](https://cmake.org/cmake/help/latest/manual/ctest.1.html#ctest-build-step)
    - [CTest 测试步骤](https://cmake.org/cmake/help/latest/manual/ctest.1.html#ctest-test-step)
    - [CTest 覆盖步骤](https://cmake.org/cmake/help/latest/manual/ctest.1.html#ctest-coverage-step)
    - [CTest MemCheck 步骤](https://cmake.org/cmake/help/latest/manual/ctest.1.html#ctest-memcheck-step)
    - [CTest 提交步骤](https://cmake.org/cmake/help/latest/manual/ctest.1.html#ctest-submit-step)
  - [显示为 JSON 对象模型](https://cmake.org/cmake/help/latest/manual/ctest.1.html#show-as-json-object-model)
  - [资源分配](https://cmake.org/cmake/help/latest/manual/ctest.1.html#resource-allocation)
    - [资源规范文件](https://cmake.org/cmake/help/latest/manual/ctest.1.html#resource-specification-file)
    - [`RESOURCE_GROUPS`财产](https://cmake.org/cmake/help/latest/manual/ctest.1.html#resource-groups-property)
    - [环境变量](https://cmake.org/cmake/help/latest/manual/ctest.1.html#environment-variables)
  - [也可以看看](https://cmake.org/cmake/help/latest/manual/ctest.1.html#see-also)

## [Synopsis](https://cmake.org/cmake/help/latest/manual/ctest.1.html#id15)

```
ctest [<options>]
ctest --build-and-test <path-to-source> <path-to-build>
      --build-generator <generator> [<options>...]
      [--build-options <opts>...] [--test-command <command> [<args>...]]
ctest {-D <dashboard> | -M <model> -T <action> | -S <script> | -SP <script>}
      [-- <dashboard-options>...]
```

## [Description](https://cmake.org/cmake/help/latest/manual/ctest.1.html#id16)

ctest**可执行**文件是 CMake 测试驱动程序。CMake 生成的构建树为使用 [`enable_testing()`](https://cmake.org/cmake/help/latest/command/enable_testing.html#command:enable_testing)和[`add_test()`](https://cmake.org/cmake/help/latest/command/add_test.html#command:add_test)命令具有测试支持。该程序将运行测试并报告结果。



## [Options](https://cmake.org/cmake/help/latest/manual/ctest.1.html#id17)

- `--preset <preset>`, `--preset=<preset>`

  使用测试预设来指定测试选项。项目二进制目录是从`configurePreset`密钥中推断出来的。当前工作目录必须包含 CMake 预设文件。看[`preset`](https://cmake.org/cmake/help/latest/manual/cmake-presets.7.html#manual:cmake-presets(7))更多细节。

- `--list-presets`

  列出可用的测试预设。当前工作目录必须包含 CMake 预设文件。

- `-C <cfg>, --build-config <cfg>`

  选择要测试的配置。一些 CMake 生成的构建树可以在同一棵树中有多个构建配置。此选项可用于指定应测试哪一个。示例配置是`Debug`和 `Release`。

- `--progress`

  启用测试的短进度输出。当**ctest**的输出直接发送到终端时，通过更新同一行而不是在新行上打印每个测试的开始和结束消息来报告测试集的进度。这可以显着降低测试输出的详细程度。对于失败的测试，测试完成消息仍会在其自己的行上输出，并且最终的测试摘要也将被记录下来。也可以通过设置环境变量来启用此选项 [`CTEST_PROGRESS_OUTPUT`](https://cmake.org/cmake/help/latest/envvar/CTEST_PROGRESS_OUTPUT.html#envvar:CTEST_PROGRESS_OUTPUT).

- `-V,--verbose`

  启用测试的详细输出。测试输出通常被抑制，只显示摘要信息。此选项将显示所有测试输出。

- `-VV,--extra-verbose`

  从测试中启用更详细的输出。测试输出通常被抑制，只显示摘要信息。此选项将显示更多的测试输出。

- `--debug`

  显示更详细的 CTest 内部结构。此功能将产生大量输出，这些输出对调试仪表板问题非常有用。

- `--output-on-failure`

  如果测试失败，则输出测试程序输出的任何内容。此选项也可以通过设置 [`CTEST_OUTPUT_ON_FAILURE`](https://cmake.org/cmake/help/latest/envvar/CTEST_OUTPUT_ON_FAILURE.html#envvar:CTEST_OUTPUT_ON_FAILURE)环境变量

- `--stop-on-failure`

  当第一次失败发生时停止运行测试。

- `-F`

  启用故障转移。此选项允许 CTest 恢复先前中断的测试集执行。如果没有发生中断，该`-F`选项将无效。

- `-j <jobs>, --parallel <jobs>`

  使用给定数量的作业并行运行测试。此选项告诉 CTest 使用给定数量的作业并行运行测试。这个选项也可以通过设置 [`CTEST_PARALLEL_LEVEL`](https://cmake.org/cmake/help/latest/envvar/CTEST_PARALLEL_LEVEL.html#envvar:CTEST_PARALLEL_LEVEL)环境变量。此选项可与[`PROCESSORS`](https://cmake.org/cmake/help/latest/prop_test/PROCESSORS.html#prop_test:PROCESSORS)测试属性。请参阅[标签和子项目摘要](https://cmake.org/cmake/help/latest/manual/ctest.1.html#label-and-subproject-summary)。

- `--resource-spec-file <file>`

  在启用资源分配的 [情况](https://cmake.org/cmake/help/latest/manual/ctest.1.html#ctest-resource-specification-file)[下](https://cmake.org/cmake/help/latest/manual/ctest.1.html#ctest-resource-allocation)运行 CTest ，使用.`<file>`当`ctest`作为[仪表板客户端](https://cmake.org/cmake/help/latest/manual/ctest.1.html#dashboard-client)运行时，这将设置 [CTest 测试步骤](https://cmake.org/cmake/help/latest/manual/ctest.1.html#ctest-test-step)`ResourceSpecFile`的选项。

- `--test-load <level>`

  在并行运行测试时（例如使用`-j`），当测试可能导致 CPU 负载超过给定阈值时，尽量不要启动测试。当`ctest`作为[仪表板客户端](https://cmake.org/cmake/help/latest/manual/ctest.1.html#dashboard-client)运行时，这将设置 [CTest 测试步骤](https://cmake.org/cmake/help/latest/manual/ctest.1.html#ctest-test-step)`TestLoad`的选项。

- `-Q,--quiet`

  让 CTest 安静。此选项将抑制所有输出。如果指定了，仍将生成输出日志文件`--output-log`。如果指定，则忽略`--verbose`、`--extra-verbose`和等选项。`--debug``--quiet`

- `-O <file>, --output-log <file>`

  输出到日志文件。此选项告诉 CTest 将其所有输出写入`<file>`日志文件。

- `--output-junit <file>`

  以 JUnit 格式编写测试结果。`<file>`此选项告诉 CTest 以JUnit XML 格式写入测试结果。如果`<file>`已经存在，它将被覆盖。如果使用该 `-S`选项来运行仪表板脚本，请使用`OUTPUT_JUNIT`带有[`ctest_test()`](https://cmake.org/cmake/help/latest/command/ctest_test.html#command:ctest_test)而是命令。

- `-N,--show-only[=<format>]`

  禁用测试的实际执行。此选项告诉 CTest 列出将要运行但实际上并未运行的测试。`-R`与和`-E` 选项结合使用很有用。`<format>`可以是以下值之一。`human`人性化的输出。这不能保证是稳定的。这是默认设置。`json-v1`以 JSON 格式转储测试信息。请参阅[显示为 JSON 对象模型](https://cmake.org/cmake/help/latest/manual/ctest.1.html#show-as-json-object-model)。

- `-L <regex>, --label-regex <regex>`

  使用匹配正则表达式的标签运行测试，如 [string(REGEX)](https://cmake.org/cmake/help/latest/command/string.html#regex-specification)中所述。此选项告诉 CTest 仅运行标签与给定正则表达式匹配的测试。当给出多个选项时，只有当每个正则表达式匹配至少一个测试标签（即多个标签形成 关系）`-L`时，才会运行测试。请参阅[标签匹配](https://cmake.org/cmake/help/latest/manual/ctest.1.html#label-matching)。`-L``AND`

- `-R <regex>, --tests-regex <regex>`

  运行匹配正则表达式的测试。此选项告诉 CTest 仅运行名称与给定正则表达式匹配的测试。

- `-E <regex>, --exclude-regex <regex>`

  排除匹配正则表达式的测试。此选项告诉 CTest 不要运行名称与给定正则表达式匹配的测试。

- `-LE <regex>, --label-exclude <regex>`

  排除标签与正则表达式匹配的测试。此选项告诉 CTest 不要运行标签与给定正则表达式匹配的测试。当给出多个选项时，只有当每个正则表达式匹配至少一个测试标签（即多个标签形成 关系）`-LE`时，才会排除测试。请参阅[标签匹配](https://cmake.org/cmake/help/latest/manual/ctest.1.html#label-matching)。`-LE``AND`

- `-FA <regex>, --fixture-exclude-any <regex>`

  `<regex>`从自动将任何测试添加到测试集中排除匹配的夹具。如果要执行的测试集中的测试需要特定的夹具，则该夹具的设置和清理测试通常会自动添加到测试集中。此选项可防止为与`<regex>`. 请注意，所有其他夹具行为都将保留，包括测试依赖项和跳过具有夹具设置测试失败的测试。

- `-FS <regex>, --fixture-exclude-setup <regex>`

  与`-FA`仅排除匹配的设置测试相同。

- `-FC <regex>, --fixture-exclude-cleanup <regex>`

  与`-FA`仅排除匹配的清理测试相同。

- `-D <dashboard>, --dashboard <dashboard>`

  执行仪表板测试。此选项告诉 CTest 充当 Cdash 客户端并执行仪表板测试。所有测试都是`<Mode><Test>`, where `<Mode>`can be `Experimental`, `Nightly`, and `Continuous`, and `<Test>`can be `Start`, `Update`, `Configure`, `Build`, `Test`, `Coverage`, and `Submit`.请参阅[仪表板客户端](https://cmake.org/cmake/help/latest/manual/ctest.1.html#dashboard-client)。

- `-D <var>:<type>=<value>`

  为脚本模式定义一个变量。在命令行中传入变量值。与 结合使用`-S`将变量值传递给仪表板脚本。仅当后面的值与任何已知仪表板类型都不匹配时，才会尝试将参数解析`-D` 为变量值。`-D`

- `-M <model>, --test-model <model>`

  设置仪表板的模型。此选项告诉 CTest 充当 Cdash 客户端，其中`<model>` 可以是`Experimental`、`Nightly`和`Continuous`. 结合`-M`和`-T`类似于`-D`。请参阅[仪表板客户端](https://cmake.org/cmake/help/latest/manual/ctest.1.html#dashboard-client)。

- `-T <action>, --test-action <action>`

  设置要执行的仪表板操作。此选项告诉 CTest 充当 CDash 客户端并执行一些操作，例如`start`、`build`等`test`。请参阅 [仪表板客户端步骤](https://cmake.org/cmake/help/latest/manual/ctest.1.html#dashboard-client-steps)以获取完整的操作列表。结合`-M`和`-T`类似于`-D`。请参阅[仪表板客户端](https://cmake.org/cmake/help/latest/manual/ctest.1.html#dashboard-client)。

- `-S <script>, --script <script>`

  为配置执行仪表板。此选项告诉 CTest 加载配置脚本，该脚本设置许多参数，例如二进制和源目录。然后 CTest 将执行创建和运行仪表板所需的操作。此选项基本上设置仪表板，然后 使用适当的选项运行。`ctest -D`请参阅[仪表板客户端](https://cmake.org/cmake/help/latest/manual/ctest.1.html#dashboard-client)。

- `-SP <script>, --script-new-process <script>`

  为配置执行仪表板。此选项执行相同的操作，`-S`但它将在单独的进程中执行它们。这主要在脚本可能修改环境并且您不希望修改后的环境影响其他`-S`脚本的情况下有用。请参阅[仪表板客户端](https://cmake.org/cmake/help/latest/manual/ctest.1.html#dashboard-client)。

- `-I [Start,End,Stride,test#,test#|Test file], --tests-information`

  按编号运行特定数量的测试。此选项使 CTest 运行从 number 开始、在 number`Start`结束`End`并以 为增量的测试`Stride`。后面的任何附加数字`Stride`都被视为单独的测试编号。 `Start`, `End`, 或`Stride`可以为空。可以选择提供包含与命令行相同语法的文件。

- `-U, --union`

  取 和 的`-I`并集`-R`。默认情况下同时指定`-R`和时`-I`，将运行测试的交集。通过指定`-U`测试的联合来代替运行。

- `--rerun-failed`

  只运行之前失败的测试。此选项告诉 CTest 仅执行在其先前运行期间失败的测试。指定此选项时，CTest 会忽略所有其他旨在修改要运行的测试列表的选项（`-L`、`-R`、 `-E`、`-LE`、`-I`等）。如果 CTest 运行并且没有测试失败，则使用该`--rerun-failed`选项对 CTest 的后续调用将运行最近失败的测试集（如果有）。

- `--repeat <mode>:<n>`

  根据给定`<mode>`的`<n>`时间重复运行测试。模式是：`until-fail`要求每个测试运行`<n>`时间且不失败才能通过。这对于发现测试用例中的零星故障很有用。`until-pass`允许每个测试运行`<n>`多次才能通过。如果由于任何原因失败，则重复测试。这对于容忍测试用例中的零星故障很有用。`after-timeout`允许每个测试运行`<n>`多次才能通过。仅在超时时重复测试。这对于容忍繁忙机器上的测试用例中的零星超时非常有用。

- `--repeat-until-fail <n>`

  相当于。`--repeat until-fail:<n>`

- `--max-width <width>`

  设置要输出的测试名称的最大宽度。设置每个测试名称的最大宽度以显示在输出中。这允许用户扩大输出以避免剪裁可能非常烦人的测试名称。

- `--interactive-debug-mode [0|1]`

  将交互模式设置为`0`或`1`。此选项使 CTest 以交互模式或非交互模式运行测试。在仪表板模式 ( `Experimental`, `Nightly`, `Continuous`) 中，默认为非交互式。在非交互模式下，环境变量[`DASHBOARD_TEST_FROM_CTEST`](https://cmake.org/cmake/help/latest/envvar/DASHBOARD_TEST_FROM_CTEST.html#envvar:DASHBOARD_TEST_FROM_CTEST)已设置。在 CMake 3.11 之前，Windows 上的交互模式允许出现系统调试弹出窗口。现在，由于 CTest 使用`libuv`启动测试进程，所有系统调试弹出窗口总是被阻止。

- `--no-label-summary`

  禁用标签的时序摘要信息。此选项告诉 CTest 不要为与运行的测试关联的每个标签打印摘要信息。如果测试上没有标签，则不会打印任何额外内容。请参阅[标签和子项目摘要](https://cmake.org/cmake/help/latest/manual/ctest.1.html#label-and-subproject-summary)。

- `--no-subproject-summary`

  禁用子项目的时序摘要信息。此选项告诉 CTest 不要打印与运行的测试关联的每个子项目的摘要信息。如果测试中没有子项目，则不会打印任何额外内容。请参阅[标签和子项目摘要](https://cmake.org/cmake/help/latest/manual/ctest.1.html#label-and-subproject-summary)。

`--build-and-test` 请参阅[构建和测试模式](https://cmake.org/cmake/help/latest/manual/ctest.1.html#build-and-test-mode)。

`--test-dir <dir>` 指定要在其中查找测试的目录。

- `--test-output-size-passed <size>`

  *3.4 版中的新功能。*将已通过测试的输出限制为`<size>`字节。

- `--test-output-size-failed <size>`

  *3.4 版中的新功能。*将失败测试的输出限制为`<size>`字节。

- `--test-output-truncation <mode>`

  *版本 3.24 中的新功能。*一旦达到最大输出大小，就截断`tail`（默认）`middle`或测试输出。`head`

- `--overwrite`

  覆盖 CTest 配置选项。默认情况下，CTest 使用配置文件中的配置选项。此选项将覆盖配置选项。

- `--force-new-ctest-process`

  将子 CTest 实例作为新进程运行。默认情况下，CTest 将在同一进程中运行子 CTest 实例。如果不需要此行为，则此参数将为子 CTest 进程强制执行新进程。

- `--schedule-random`

  使用随机顺序安排测试。此选项将以随机顺序运行测试。它通常用于检测测试套件中的隐式依赖关系。

- `--submit-index`

  旧 Dart2 仪表板服务器功能的旧选项。不使用。

- `--timeout <seconds>`

  设置默认测试超时。此选项有效地为所有尚未设置超时的测试设置超时，通过[`TIMEOUT`](https://cmake.org/cmake/help/latest/prop_test/TIMEOUT.html#prop_test:TIMEOUT) 财产。

- `--stop-time <time>`

  设置所有测试停止运行的时间。设置一天中所有测试都应超时的实时时间。示例： 。接受 curl 日期解析器理解的任何时间格式。如果未指定时区，则假定为本地时间。`7:00:00 -0400`

- `--print-labels`

  打印所有可用的测试标签。此选项不会运行任何测试，它只会打印与测试集关联的所有标签的列表。

- `--no-tests=<[error|ignore]>`

  将未发现任何测试视为错误或忽略它。如果没有找到测试，CTest 的默认行为是始终记录错误消息，但仅在脚本模式下返回错误代码。此选项通过在未找到测试时返回错误代码或忽略它来统一 CTest 的行为。

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



## [标签匹配](https://cmake.org/cmake/help/latest/manual/ctest.1.html#id18)

测试可能附有标签。通过过滤标签，可以将测试包括或排除在测试运行中。每个单独的过滤器都是一个正则表达式，应用于附加到测试的标签。

使用`-L`时，为了让测试包含在测试运行中，每个正则表达式必须匹配至少一个标签。使用多个`-L`选项意味着“匹配**所有** 这些”。

该`-LE`选项的作用与 类似`-L`，但不包括测试而不是包括它们。如果每个正则表达式至少匹配一个标签，则排除测试。

如果测试没有附加标签，则`-L`永远不会包含该测试，`-LE`也永远不会排除该测试。作为带有标签的测试示例，考虑五个带有以下标签的测试：

- *test1*有标签*tuesday*和*production*
- *test2*有标签*tuesday*和*test*
- *test3*有标签*星期三*和*生产*
- *test4*有标签*星期三*
- *test5*有标签*friday*和*test*

运行`ctest`with将选择*test2*，它具有两个标签。运行 CTest将选择*test2*和 *test5*，因为它们都有一个与该正则表达式匹配的标签。`-L tuesday -L test``-L test`

因为匹配适用于正则表达式，请注意运行 CTest将匹配所有五个测试。要同时选择*星期二*和*星期三*测试，请使用匹配其中任何一个的单个正则表达式，例如.`-L es``-L "tue|wed"`



## [标签和子项目摘要](https://cmake.org/cmake/help/latest/manual/ctest.1.html#id19)

CTest 打印与测试运行相关联的每个`LABEL`子项目的时间摘要信息。标签时间摘要将不包括映射到子项目的标签。

*3.22 版中的新功能：*在测试执行期间动态添加的标签也会在时序摘要中报告。请参阅[附加标签](https://cmake.org/cmake/help/latest/command/ctest_test.html#additional-labels)。

当。。。的时候[`PROCESSORS`](https://cmake.org/cmake/help/latest/prop_test/PROCESSORS.html#prop_test:PROCESSORS)设置了测试属性，CTest 将在标签和子项目摘要中显示加权测试时序结果。使用sec*proc报告时间，而不仅仅是sec。

为每个标签或子项目报告的加权时间摘要`j` 计算如下：

```
Weighted Time Summary for Label/Subproject j =
    sum(raw_test_time[j,i] * num_processors[j,i], i=1...num_tests[j])

for labels/subprojects j=1...total
```

在哪里：

- `raw_test_time[j,i]`：标签或子项目`i`测试的挂钟时间`j`
- `num_processors[j,i]`: CTest 的值[`PROCESSORS`](https://cmake.org/cmake/help/latest/prop_test/PROCESSORS.html#prop_test:PROCESSORS)标签或子项目的`i`测试属性`j`
- `num_tests[j]``j`：与标签或子项目关联的测试数
- `total`：至少有一次测试运行的标签或子项目的总数

因此，每个标签或子项目的加权时间摘要表示 CTest 为运行每个标签或子项目的测试所花费的时间，并且与其他标签相比，可以很好地表示每个标签或子项目的测试总费用或子项目。

例如，如果`SubprojectA`显示和显示 ，则 CTest 分配大约 10 倍的 CPU/内核时间来运行测试，而不是 for （例如，如果要花费精力来降低整个项目的测试套件的成本，那么降低测试套件的成本可能会比努力降低测试套件的成本产生更大的影响）。`100 sec*proc``SubprojectB``10 sec*proc``SubprojectA``SubprojectB``SubprojectA``SubprojectB`



## [构建和测试模式](https://cmake.org/cmake/help/latest/manual/ctest.1.html#id20)

CTest 提供了一个命令行签名来配置（即运行 cmake）、构建和/或执行测试：

```
ctest --build-and-test <path-to-source> <path-to-build>
      --build-generator <generator>
      [<options>...]
      [--build-options <opts>...]
      [--test-command <command> [<args>...]]
```

配置和测试步骤是可选的。此命令行的参数是源目录和二进制目录。*必须*提供该`--build-generator`选项 才能使用。如果指定了，那么它将在构建完成后运行。影响此模式的其他选项包括：`--build-and-test``--test-command`

- `--build-target`

  指定要构建的特定目标。如果省略，`all`则构建目标。

- `--build-nocmake`

  在不先运行 cmake 的情况下运行构建。跳过 cmake 步骤。

- `--build-run-dir`

  指定从中运行程序的目录。程序编译后所在的目录。

- `--build-two-config`

  运行 CMake 两次。

- `--build-exe-dir`

  指定可执行文件的目录。

- `--build-generator`

  指定要使用的生成器。见[`cmake-generators(7)`](https://cmake.org/cmake/help/latest/manual/cmake-generators.7.html#manual:cmake-generators(7))手动的。

- `--build-generator-platform`

  指定特定于生成器的平台。

- `--build-generator-toolset`

  指定特定于生成器的工具集。

- `--build-project`

  指定要构建的项目的名称。

- `--build-makeprogram`

  指定 CMake 在配置和构建项目时要使用的显式 make 程序。仅适用于基于 Make 和 Ninja 的生成器。

- `--build-noclean`

  跳过 make clean 步骤。

- `--build-config-sample`

  用于确定应使用的配置的示例可执行文件。例如 `Debug`，`Release`等等。

- `--build-options`

  用于配置构建的附加选项（即用于 CMake，而不是用于构建工具）。请注意，如果指定了此项，则`--build-options` 关键字及其参数必须是命令行上给出的最后一个选项，可能的例外是`--test-command`.

- `--test-command`

  `--build-and-test`作为带有选项的测试步骤运行的命令。此关键字后面的所有参数都将被假定为测试命令行的一部分，因此它必须是给出的最后一个选项。

- `--test-timeout`

  以秒为单位的时间限制



## [仪表板客户端](https://cmake.org/cmake/help/latest/manual/ctest.1.html#id21)

CTest 可以作为[Cdash](https://cmake.org/cmake/help/latest/manual/ctest.1.html#cdash)软件质量仪表板应用程序的客户端运行。作为仪表板客户端，CTest 执行一系列步骤来配置、构建和测试软件，然后将结果提交给[Cdash](https://cmake.org/cmake/help/latest/manual/ctest.1.html#cdash)服务器。用于提交到[Cdash](https://cmake.org/cmake/help/latest/manual/ctest.1.html#cdash)的命令行签名是：

```
ctest (-D <dashboard> | -M <model> -T <action> | -S <script> | -SP <script>)
      [-- <dashboard-options>...]
```

Dashboard Client 的选项包括：

- `--group <group>`

  指定您要将结果提交给哪个组将仪表板提交到指定组而不是默认组。默认情况下，仪表板被提交到 Nightly、Experimental 或 Continuous 组，但通过指定此选项，该组可以是任意的。这替换了不推荐使用的选项`--track`。尽管名称更改，但其行为没有改变。

- `-A <file>, --add-notes <file>`

  添加带有提交的注释文件。此选项告诉 CTest 在提交仪表板时包含注释文件。

- `--tomorrow-tag`

  `Nightly`或`Experimental`从第二天标签开始。如果构建不会在一天内完成，这很有用。

- `--extra-submit <file>[;<file>]`

  向仪表板提交额外的文件。此选项会将额外文件提交到仪表板。

- `--http1.0`

  使用HTTP 1.0提交。此选项将强制 CTest 使用HTTP 1.0将文件提交到仪表板，而不是HTTP 1.1。

- `--no-compress-output`

  提交时不要压缩测试输出。该标志将关闭测试输出的自动压缩。使用它来保持与不支持压缩测试输出的旧版本 Cdash 的兼容性。

### [仪表板客户端步骤](https://cmake.org/cmake/help/latest/manual/ctest.1.html#id22)

CTest 定义了测试步骤的有序列表，其中部分或全部可以作为仪表板客户端运行：

- `Start`

  开始一个新的仪表板提交，由以下步骤记录的结果组成。请参阅下面的[CTest 开始步骤](https://cmake.org/cmake/help/latest/manual/ctest.1.html#ctest-start-step)部分。

- `Update`

  从其版本控制存储库更新源代码树。记录新旧版本以及更新的源文件列表。请参阅下面的[CTest 更新步骤](https://cmake.org/cmake/help/latest/manual/ctest.1.html#ctest-update-step)部分。

- `Configure`

  通过在构建树中运行命令来配置软件。记录配置输出日志。请参阅下面的[CTest 配置步骤](https://cmake.org/cmake/help/latest/manual/ctest.1.html#ctest-configure-step)部分。

- `Build`

  通过在构建树中运行命令来构建软件。记录构建输出日志并检测警告和错误。请参阅下面的[CTest 构建步骤](https://cmake.org/cmake/help/latest/manual/ctest.1.html#ctest-build-step)部分。

- `Test`

  通过从构建树加载`CTestTestfile.cmake` 并执行定义的测试来测试软件。记录每次测试的输出和结果。请参阅下面的[CTest 测试步骤](https://cmake.org/cmake/help/latest/manual/ctest.1.html#ctest-test-step)部分。

- `Coverage`

  通过运行覆盖率分析工具并记录其输出来计算源代码的覆盖率。请参阅下面的[CTest 覆盖步骤](https://cmake.org/cmake/help/latest/manual/ctest.1.html#ctest-coverage-step)部分。

- `MemCheck`

  通过内存检查工具运行软件测试套件。记录工具报告的测试输出、结果和问题。请参阅下面的[CTest MemCheck 步骤](https://cmake.org/cmake/help/latest/manual/ctest.1.html#ctest-memcheck-step)部分。

- `Submit`

  将其他测试步骤记录的结果提交到软件质量仪表板服务器。请参阅下面的[CTest 提交步骤](https://cmake.org/cmake/help/latest/manual/ctest.1.html#ctest-submit-step)部分。

### [仪表板客户端模式](https://cmake.org/cmake/help/latest/manual/ctest.1.html#id23)

CTest 定义了三种操作模式作为仪表板客户端：

- `Nightly`

  此模式旨在每天调用一次，通常在晚上。它默认启用`Start`、`Update`、`Configure`、`Build`、`Test`、 `Coverage`和`Submit`步骤。即使`Update`步骤报告源树没有更改，选定的步骤也会运行。

- `Continuous`

  此模式旨在全天重复调用。它默认启用`Start`、`Update`、`Configure`、`Build`、`Test`、 `Coverage`和步骤，但如果它报告源树没有更改，则`Submit`在步骤之后退出 。`Update`

- `Experimental`

  此模式旨在由开发人员调用以测试本地更改。它默认启用`Start`、`Configure`、`Build`、`Test`、`Coverage`和`Submit`步骤。

### [通过 CTest 命令行的仪表板客户端](https://cmake.org/cmake/help/latest/manual/ctest.1.html#id24)

CTest 可以在已经生成的构建树上执行测试。在当前工作目录设置为构建树的情况下运行`ctest`命令并使用以下签名之一：

```
ctest -D <mode>[<step>]
ctest -M <mode> [ -T <step> ]...
```

`<mode>`必须是上述仪表[板客户端模式](https://cmake.org/cmake/help/latest/manual/ctest.1.html#dashboard-client-modes)之一，并且每个`<step>`必须是上述[仪表板客户端步骤](https://cmake.org/cmake/help/latest/manual/ctest.1.html#dashboard-client-steps)之一。

CTest从构建树中名为 or的文件中读取[Dashboard Client 配置](https://cmake.org/cmake/help/latest/manual/ctest.1.html#dashboard-client-configuration)设置（名称为历史名称）。文件格式为：`CTestConfiguration.ini``DartConfiguration.tcl`

```
# Lines starting in '#' are comments.
# Other non-blank lines are key-value pairs.
<setting>: <value>
```

其中`<setting>`是设置名称，`<value>`是设置值。

在 CMake 生成的构建树中，此配置文件由[`CTest`](https://cmake.org/cmake/help/latest/module/CTest.html#module:CTest)模块（如果包含在项目中）。该模块使用变量来获取每个设置的值，如下面的设置所述。



### [通过 CTest 脚本的仪表板客户端](https://cmake.org/cmake/help/latest/manual/ctest.1.html#id25)

CTest 可以执行由一个驱动的测试[`cmake-language(7)`](https://cmake.org/cmake/help/latest/manual/cmake-language.7.html#manual:cmake-language(7)) 创建和维护源代码和构建树以及执行测试步骤的脚本。使用在任何构建树之外设置的当前工作目录运行`ctest`命令，并使用以下签名之一：

```
ctest -S <script>
ctest -SP <script>
```

该`<script>`文件必须调用[CTest 命令](https://cmake.org/cmake/help/latest/manual/cmake-commands.7.html#ctest-commands)命令来显式运行测试步骤，如下所述。这些命令从其参数或脚本中设置的变量获取[仪表板客户端配置设置。](https://cmake.org/cmake/help/latest/manual/ctest.1.html#dashboard-client-configuration)

## [仪表板客户端配置](https://cmake.org/cmake/help/latest/manual/ctest.1.html#id26)

[仪表板客户端步骤](https://cmake.org/cmake/help/latest/manual/ctest.1.html#dashboard-client-steps)可以通过命名设置进行配置，如以下部分所述。



### [CTest 开始步骤](https://cmake.org/cmake/help/latest/manual/ctest.1.html#id27)

开始一个新的仪表板提交，由以下步骤记录的结果组成。

在[CTest 脚本](https://cmake.org/cmake/help/latest/manual/ctest.1.html#ctest-script)中，[`ctest_start()`](https://cmake.org/cmake/help/latest/command/ctest_start.html#command:ctest_start)命令运行此步骤。命令的参数可以指定一些步骤设置。该命令首先运行由 `CTEST_CHECKOUT_COMMAND`变量指定的命令行（如果已设置）以初始化源目录。

配置设置包括：

- `BuildDirectory`

  项目构建树的完整路径。[CTest 脚本](https://cmake.org/cmake/help/latest/manual/ctest.1.html#ctest-script)变量：[`CTEST_BINARY_DIRECTORY`](https://cmake.org/cmake/help/latest/variable/CTEST_BINARY_DIRECTORY.html#variable:CTEST_BINARY_DIRECTORY)[`CTest`](https://cmake.org/cmake/help/latest/module/CTest.html#module:CTest)模块变量：[`PROJECT_BINARY_DIR`](https://cmake.org/cmake/help/latest/variable/PROJECT_BINARY_DIR.html#variable:PROJECT_BINARY_DIR)

- `SourceDirectory`

  项目源代码树的完整路径。[CTest 脚本](https://cmake.org/cmake/help/latest/manual/ctest.1.html#ctest-script)变量：[`CTEST_SOURCE_DIRECTORY`](https://cmake.org/cmake/help/latest/variable/CTEST_SOURCE_DIRECTORY.html#variable:CTEST_SOURCE_DIRECTORY)[`CTest`](https://cmake.org/cmake/help/latest/module/CTest.html#module:CTest)模块变量：[`PROJECT_SOURCE_DIR`](https://cmake.org/cmake/help/latest/variable/PROJECT_SOURCE_DIR.html#variable:PROJECT_SOURCE_DIR)



### [CTest 更新步骤](https://cmake.org/cmake/help/latest/manual/ctest.1.html#id28)

在[CTest 脚本](https://cmake.org/cmake/help/latest/manual/ctest.1.html#ctest-script)中，[`ctest_update()`](https://cmake.org/cmake/help/latest/command/ctest_update.html#command:ctest_update)命令运行此步骤。命令的参数可以指定一些步骤设置。

指定版本控制工具的配置设置包括：

- `BZRCommand`

  `bzr`如果源代码树由 Bazaar 管理，则使用命令行工具。[CTest 脚本](https://cmake.org/cmake/help/latest/manual/ctest.1.html#ctest-script)变量：[`CTEST_BZR_COMMAND`](https://cmake.org/cmake/help/latest/variable/CTEST_BZR_COMMAND.html#variable:CTEST_BZR_COMMAND)[`CTest`](https://cmake.org/cmake/help/latest/module/CTest.html#module:CTest)模块变量：无

- `BZRUpdateOptions`

  `BZRCommand`更新源时的命令行选项。[CTest 脚本](https://cmake.org/cmake/help/latest/manual/ctest.1.html#ctest-script)变量：[`CTEST_BZR_UPDATE_OPTIONS`](https://cmake.org/cmake/help/latest/variable/CTEST_BZR_UPDATE_OPTIONS.html#variable:CTEST_BZR_UPDATE_OPTIONS)[`CTest`](https://cmake.org/cmake/help/latest/module/CTest.html#module:CTest)模块变量：无

- `CVSCommand`

  `cvs`如果源代码树由 CVS 管理，则使用命令行工具。[CTest 脚本](https://cmake.org/cmake/help/latest/manual/ctest.1.html#ctest-script)变量：[`CTEST_CVS_COMMAND`](https://cmake.org/cmake/help/latest/variable/CTEST_CVS_COMMAND.html#variable:CTEST_CVS_COMMAND)[`CTest`](https://cmake.org/cmake/help/latest/module/CTest.html#module:CTest)模块变量：`CVSCOMMAND`

- `CVSUpdateOptions`

  `CVSCommand`更新源时的命令行选项。[CTest 脚本](https://cmake.org/cmake/help/latest/manual/ctest.1.html#ctest-script)变量：[`CTEST_CVS_UPDATE_OPTIONS`](https://cmake.org/cmake/help/latest/variable/CTEST_CVS_UPDATE_OPTIONS.html#variable:CTEST_CVS_UPDATE_OPTIONS)[`CTest`](https://cmake.org/cmake/help/latest/module/CTest.html#module:CTest)模块变量：`CVS_UPDATE_OPTIONS`

- `GITCommand`

  `git`如果源代码树由 Git 管理，则要使用的命令行工具。[CTest 脚本](https://cmake.org/cmake/help/latest/manual/ctest.1.html#ctest-script)变量：[`CTEST_GIT_COMMAND`](https://cmake.org/cmake/help/latest/variable/CTEST_GIT_COMMAND.html#variable:CTEST_GIT_COMMAND)[`CTest`](https://cmake.org/cmake/help/latest/module/CTest.html#module:CTest)模块变量：`GITCOMMAND`源代码树被更新，然后 是. 除了覆盖任何本地修改之外，结果相同。用于指定不同的方法。`git fetch``git reset --hard``FETCH_HEAD``git pull``GITUpdateCustom`

- `GITInitSubmodules`

  如果设置，CTest 将在更新之前更新存储库的子模块。[CTest 脚本](https://cmake.org/cmake/help/latest/manual/ctest.1.html#ctest-script)变量：[`CTEST_GIT_INIT_SUBMODULES`](https://cmake.org/cmake/help/latest/variable/CTEST_GIT_INIT_SUBMODULES.html#variable:CTEST_GIT_INIT_SUBMODULES)[`CTest`](https://cmake.org/cmake/help/latest/module/CTest.html#module:CTest)模块变量：`CTEST_GIT_INIT_SUBMODULES`

- `GITUpdateCustom`

  指定要在源树（Git 工作树）中运行的自定义命令行（作为分号分隔的列表）来更新它，而不是运行`GITCommand`.[CTest 脚本](https://cmake.org/cmake/help/latest/manual/ctest.1.html#ctest-script)变量：[`CTEST_GIT_UPDATE_CUSTOM`](https://cmake.org/cmake/help/latest/variable/CTEST_GIT_UPDATE_CUSTOM.html#variable:CTEST_GIT_UPDATE_CUSTOM)[`CTest`](https://cmake.org/cmake/help/latest/module/CTest.html#module:CTest)模块变量：`CTEST_GIT_UPDATE_CUSTOM`

- `GITUpdateOptions`

  `GITCommand`更新源时的命令行选项。[CTest 脚本](https://cmake.org/cmake/help/latest/manual/ctest.1.html#ctest-script)变量：[`CTEST_GIT_UPDATE_OPTIONS`](https://cmake.org/cmake/help/latest/variable/CTEST_GIT_UPDATE_OPTIONS.html#variable:CTEST_GIT_UPDATE_OPTIONS)[`CTest`](https://cmake.org/cmake/help/latest/module/CTest.html#module:CTest)模块变量：`GIT_UPDATE_OPTIONS`

- `HGCommand`

  `hg`如果源代码树由 Mercurial 管理，则要使用的命令行工具。[CTest 脚本](https://cmake.org/cmake/help/latest/manual/ctest.1.html#ctest-script)变量：[`CTEST_HG_COMMAND`](https://cmake.org/cmake/help/latest/variable/CTEST_HG_COMMAND.html#variable:CTEST_HG_COMMAND)[`CTest`](https://cmake.org/cmake/help/latest/module/CTest.html#module:CTest)模块变量：无

- `HGUpdateOptions`

  `HGCommand`更新源时的命令行选项。[CTest 脚本](https://cmake.org/cmake/help/latest/manual/ctest.1.html#ctest-script)变量：[`CTEST_HG_UPDATE_OPTIONS`](https://cmake.org/cmake/help/latest/variable/CTEST_HG_UPDATE_OPTIONS.html#variable:CTEST_HG_UPDATE_OPTIONS)[`CTest`](https://cmake.org/cmake/help/latest/module/CTest.html#module:CTest)模块变量：无

- `P4Client`

  `-c`期权的价值`P4Command`。[CTest 脚本](https://cmake.org/cmake/help/latest/manual/ctest.1.html#ctest-script)变量：[`CTEST_P4_CLIENT`](https://cmake.org/cmake/help/latest/variable/CTEST_P4_CLIENT.html#variable:CTEST_P4_CLIENT)[`CTest`](https://cmake.org/cmake/help/latest/module/CTest.html#module:CTest)模块变量：`CTEST_P4_CLIENT`

- `P4Command`

  `p4`如果源代码树由 Perforce 管理，则要使用的命令行工具。[CTest 脚本](https://cmake.org/cmake/help/latest/manual/ctest.1.html#ctest-script)变量：[`CTEST_P4_COMMAND`](https://cmake.org/cmake/help/latest/variable/CTEST_P4_COMMAND.html#variable:CTEST_P4_COMMAND)[`CTest`](https://cmake.org/cmake/help/latest/module/CTest.html#module:CTest)模块变量：`P4COMMAND`

- `P4Options`

  所有调用的命令行选项`P4Command`。[CTest 脚本](https://cmake.org/cmake/help/latest/manual/ctest.1.html#ctest-script)变量：[`CTEST_P4_OPTIONS`](https://cmake.org/cmake/help/latest/variable/CTEST_P4_OPTIONS.html#variable:CTEST_P4_OPTIONS)[`CTest`](https://cmake.org/cmake/help/latest/module/CTest.html#module:CTest)模块变量：`CTEST_P4_OPTIONS`

- `P4UpdateCustom`

  指定要在源树（Perforce 树）中运行的自定义命令行（作为分号分隔的列表）来更新它，而不是运行`P4Command`.[CTest 脚本](https://cmake.org/cmake/help/latest/manual/ctest.1.html#ctest-script)变量：无[`CTest`](https://cmake.org/cmake/help/latest/module/CTest.html#module:CTest)模块变量：`CTEST_P4_UPDATE_CUSTOM`

- `P4UpdateOptions`

  `P4Command`更新源时的命令行选项。[CTest 脚本](https://cmake.org/cmake/help/latest/manual/ctest.1.html#ctest-script)变量：[`CTEST_P4_UPDATE_OPTIONS`](https://cmake.org/cmake/help/latest/variable/CTEST_P4_UPDATE_OPTIONS.html#variable:CTEST_P4_UPDATE_OPTIONS)[`CTest`](https://cmake.org/cmake/help/latest/module/CTest.html#module:CTest)模块变量：`CTEST_P4_UPDATE_OPTIONS`

- `SVNCommand`

  `svn`如果源代码树由 Subversion 管理，则使用命令行工具。[CTest 脚本](https://cmake.org/cmake/help/latest/manual/ctest.1.html#ctest-script)变量：[`CTEST_SVN_COMMAND`](https://cmake.org/cmake/help/latest/variable/CTEST_SVN_COMMAND.html#variable:CTEST_SVN_COMMAND)[`CTest`](https://cmake.org/cmake/help/latest/module/CTest.html#module:CTest)模块变量：`SVNCOMMAND`

- `SVNOptions`

  所有调用的命令行选项`SVNCommand`。[CTest 脚本](https://cmake.org/cmake/help/latest/manual/ctest.1.html#ctest-script)变量：[`CTEST_SVN_OPTIONS`](https://cmake.org/cmake/help/latest/variable/CTEST_SVN_OPTIONS.html#variable:CTEST_SVN_OPTIONS)[`CTest`](https://cmake.org/cmake/help/latest/module/CTest.html#module:CTest)模块变量：`CTEST_SVN_OPTIONS`

- `SVNUpdateOptions`

  `SVNCommand`更新源时的命令行选项。[CTest 脚本](https://cmake.org/cmake/help/latest/manual/ctest.1.html#ctest-script)变量：[`CTEST_SVN_UPDATE_OPTIONS`](https://cmake.org/cmake/help/latest/variable/CTEST_SVN_UPDATE_OPTIONS.html#variable:CTEST_SVN_UPDATE_OPTIONS)[`CTest`](https://cmake.org/cmake/help/latest/module/CTest.html#module:CTest)模块变量：`SVN_UPDATE_OPTIONS`

- `UpdateCommand`

  指定在不检测管理源树的 VCS 的情况下使用的版本控制命令行工具。[CTest 脚本](https://cmake.org/cmake/help/latest/manual/ctest.1.html#ctest-script)变量：[`CTEST_UPDATE_COMMAND`](https://cmake.org/cmake/help/latest/variable/CTEST_UPDATE_COMMAND.html#variable:CTEST_UPDATE_COMMAND)[`CTest`](https://cmake.org/cmake/help/latest/module/CTest.html#module:CTest)模块变量：`<VCS>COMMAND` 当`UPDATE_TYPE`是`<vcs>`，否则`UPDATE_COMMAND`

- `UpdateOptions`

  的命令行选项`UpdateCommand`。[CTest 脚本](https://cmake.org/cmake/help/latest/manual/ctest.1.html#ctest-script)变量：[`CTEST_UPDATE_OPTIONS`](https://cmake.org/cmake/help/latest/variable/CTEST_UPDATE_OPTIONS.html#variable:CTEST_UPDATE_OPTIONS)[`CTest`](https://cmake.org/cmake/help/latest/module/CTest.html#module:CTest)模块变量：`<VCS>_UPDATE_OPTIONS` 当`UPDATE_TYPE`是`<vcs>`，否则`UPDATE_OPTIONS`

- `UpdateType`

  如果无法自动检测到源树，请指定管理源树的版本控制系统。该值可以是`bzr`, `cvs`, `git`, `hg`, `p4`, 或`svn`.[CTest 脚本](https://cmake.org/cmake/help/latest/manual/ctest.1.html#ctest-script)变量：无，从源代码树中检测到[`CTest`](https://cmake.org/cmake/help/latest/module/CTest.html#module:CTest)模块变量：`UPDATE_TYPE`如果设置，否则`CTEST_UPDATE_TYPE`

- `UpdateVersionOnly`

  指定您希望版本控制更新命令仅发现已签出的当前版本，而不是更新到其他版本。[CTest 脚本](https://cmake.org/cmake/help/latest/manual/ctest.1.html#ctest-script)变量：[`CTEST_UPDATE_VERSION_ONLY`](https://cmake.org/cmake/help/latest/variable/CTEST_UPDATE_VERSION_ONLY.html#variable:CTEST_UPDATE_VERSION_ONLY)

- `UpdateVersionOverride`

  指定源代码树的当前版本。当此变量设置为非空字符串时，CTest 将报告您指定的值，而不是使用更新命令来发现当前签出的版本。使用此变量取代 `UpdateVersionOnly`. 就像`UpdateVersionOnly`，使用这个变量告诉 CTest 不要将源代码树更新到不同的版本。[CTest 脚本](https://cmake.org/cmake/help/latest/manual/ctest.1.html#ctest-script)变量：[`CTEST_UPDATE_VERSION_OVERRIDE`](https://cmake.org/cmake/help/latest/variable/CTEST_UPDATE_VERSION_OVERRIDE.html#variable:CTEST_UPDATE_VERSION_OVERRIDE)

其他配置设置包括：

- `NightlyStartTime`

  在`Nightly`仪表板模式下，指定“每晚开始时间”。使用集中式版本控制系统 (`cvs`和`svn`)，该`Update`步骤检查此时的软件版本，以便多个客户端选择一个通用版本进行测试。这在分布式版本控制系统中没有明确定义，因此该设置被忽略。[CTest 脚本](https://cmake.org/cmake/help/latest/manual/ctest.1.html#ctest-script)变量：[`CTEST_NIGHTLY_START_TIME`](https://cmake.org/cmake/help/latest/variable/CTEST_NIGHTLY_START_TIME.html#variable:CTEST_NIGHTLY_START_TIME)[`CTest`](https://cmake.org/cmake/help/latest/module/CTest.html#module:CTest)模块变量：`NIGHTLY_START_TIME`如果设置，否则`CTEST_NIGHTLY_START_TIME`



### [CTest 配置步骤](https://cmake.org/cmake/help/latest/manual/ctest.1.html#id29)

在[CTest 脚本](https://cmake.org/cmake/help/latest/manual/ctest.1.html#ctest-script)中，[`ctest_configure()`](https://cmake.org/cmake/help/latest/command/ctest_configure.html#command:ctest_configure)命令运行此步骤。命令的参数可以指定一些步骤设置。

配置设置包括：

- `ConfigureCommand`

  命令行启动软件配置过程。它将在 `BuildDirectory`设置指定的位置执行。[CTest 脚本](https://cmake.org/cmake/help/latest/manual/ctest.1.html#ctest-script)变量：[`CTEST_CONFIGURE_COMMAND`](https://cmake.org/cmake/help/latest/variable/CTEST_CONFIGURE_COMMAND.html#variable:CTEST_CONFIGURE_COMMAND)[`CTest`](https://cmake.org/cmake/help/latest/module/CTest.html#module:CTest)模块变量：[`CMAKE_COMMAND`](https://cmake.org/cmake/help/latest/variable/CMAKE_COMMAND.html#variable:CMAKE_COMMAND) 其次是[`PROJECT_SOURCE_DIR`](https://cmake.org/cmake/help/latest/variable/PROJECT_SOURCE_DIR.html#variable:PROJECT_SOURCE_DIR)

- `LabelsForSubprojects`

  指定将被视为子项目的以分号分隔的标签列表。在提交配置、测试或构建结果时，此映射将传递给 Cdash。[CTest 脚本](https://cmake.org/cmake/help/latest/manual/ctest.1.html#ctest-script)变量：[`CTEST_LABELS_FOR_SUBPROJECTS`](https://cmake.org/cmake/help/latest/variable/CTEST_LABELS_FOR_SUBPROJECTS.html#variable:CTEST_LABELS_FOR_SUBPROJECTS)[`CTest`](https://cmake.org/cmake/help/latest/module/CTest.html#module:CTest)模块变量：`CTEST_LABELS_FOR_SUBPROJECTS`请参阅[标签和子项目摘要](https://cmake.org/cmake/help/latest/manual/ctest.1.html#label-and-subproject-summary)。



### [CTest 构建步骤](https://cmake.org/cmake/help/latest/manual/ctest.1.html#id30)

在[CTest 脚本](https://cmake.org/cmake/help/latest/manual/ctest.1.html#ctest-script)中，[`ctest_build()`](https://cmake.org/cmake/help/latest/command/ctest_build.html#command:ctest_build)命令运行此步骤。命令的参数可以指定一些步骤设置。

配置设置包括：

- `DefaultCTestConfigurationType`

  当要启动的构建系统允许在构建时选择配置（例如`Debug`， ）时，这指定了在没有为命令提供选项`Release`时要构建的默认配置。如果出现，该值将被替换为替换文字字符串 的值。`-C``ctest``MakeCommand``${CTEST_CONFIGURATION_TYPE}`[CTest 脚本](https://cmake.org/cmake/help/latest/manual/ctest.1.html#ctest-script)变量：[`CTEST_CONFIGURATION_TYPE`](https://cmake.org/cmake/help/latest/variable/CTEST_CONFIGURATION_TYPE.html#variable:CTEST_CONFIGURATION_TYPE)[`CTest`](https://cmake.org/cmake/help/latest/module/CTest.html#module:CTest)模块变量：`DEFAULT_CTEST_CONFIGURATION_TYPE`，由[`CMAKE_CONFIG_TYPE`](https://cmake.org/cmake/help/latest/envvar/CMAKE_CONFIG_TYPE.html#envvar:CMAKE_CONFIG_TYPE)环境变量

- `LabelsForSubprojects`

  指定将被视为子项目的以分号分隔的标签列表。在提交配置、测试或构建结果时，此映射将传递给 Cdash。[CTest 脚本](https://cmake.org/cmake/help/latest/manual/ctest.1.html#ctest-script)变量：[`CTEST_LABELS_FOR_SUBPROJECTS`](https://cmake.org/cmake/help/latest/variable/CTEST_LABELS_FOR_SUBPROJECTS.html#variable:CTEST_LABELS_FOR_SUBPROJECTS)[`CTest`](https://cmake.org/cmake/help/latest/module/CTest.html#module:CTest)模块变量：`CTEST_LABELS_FOR_SUBPROJECTS`请参阅[标签和子项目摘要](https://cmake.org/cmake/help/latest/manual/ctest.1.html#label-and-subproject-summary)。

- `MakeCommand`

  用于启动软件构建过程的命令行。它将在 `BuildDirectory`设置指定的位置执行。[CTest 脚本](https://cmake.org/cmake/help/latest/manual/ctest.1.html#ctest-script)变量：[`CTEST_BUILD_COMMAND`](https://cmake.org/cmake/help/latest/variable/CTEST_BUILD_COMMAND.html#variable:CTEST_BUILD_COMMAND)[`CTest`](https://cmake.org/cmake/help/latest/module/CTest.html#module:CTest)模块变量：`MAKECOMMAND`，由[`build_command()`](https://cmake.org/cmake/help/latest/command/build_command.html#command:build_command)命令

- `UseLaunchers`

  对于 CMake 使用 [Makefile Generators](https://cmake.org/cmake/help/latest/manual/cmake-generators.7.html#makefile-generators)或[`Ninja`](https://cmake.org/cmake/help/latest/generator/Ninja.html#generator:Ninja) 生成器，指定该 `CTEST_USE_LAUNCHERS`功能是否由 [`CTestUseLaunchers`](https://cmake.org/cmake/help/latest/module/CTestUseLaunchers.html#module:CTestUseLaunchers)模块（也包含在 [`CTest`](https://cmake.org/cmake/help/latest/module/CTest.html#module:CTest)模块）。启用后，生成的构建系统会将编译器、链接器或自定义命令行的每次调用都包含一个“启动器”，该启动器通过环境变量和文件与 CTest 通信，以报告详细的构建警告和错误信息。否则，CTest 必须“抓取”构建输出日志以进行诊断。[CTest 脚本](https://cmake.org/cmake/help/latest/manual/ctest.1.html#ctest-script)变量：[`CTEST_USE_LAUNCHERS`](https://cmake.org/cmake/help/latest/variable/CTEST_USE_LAUNCHERS.html#variable:CTEST_USE_LAUNCHERS)[`CTest`](https://cmake.org/cmake/help/latest/module/CTest.html#module:CTest)模块变量：`CTEST_USE_LAUNCHERS`



### [CTest 测试步骤](https://cmake.org/cmake/help/latest/manual/ctest.1.html#id31)

在[CTest 脚本](https://cmake.org/cmake/help/latest/manual/ctest.1.html#ctest-script)中，[`ctest_test()`](https://cmake.org/cmake/help/latest/command/ctest_test.html#command:ctest_test)命令运行此步骤。命令的参数可以指定一些步骤设置。

配置设置包括：

- `ResourceSpecFile`

  指定 [资源规范文件](https://cmake.org/cmake/help/latest/manual/ctest.1.html#ctest-resource-specification-file)。[CTest 脚本](https://cmake.org/cmake/help/latest/manual/ctest.1.html#ctest-script)变量：[`CTEST_RESOURCE_SPEC_FILE`](https://cmake.org/cmake/help/latest/variable/CTEST_RESOURCE_SPEC_FILE.html#variable:CTEST_RESOURCE_SPEC_FILE)[`CTest`](https://cmake.org/cmake/help/latest/module/CTest.html#module:CTest)模块变量：`CTEST_RESOURCE_SPEC_FILE`有关详细信息，请参阅[资源分配](https://cmake.org/cmake/help/latest/manual/ctest.1.html#ctest-resource-allocation)。

- `LabelsForSubprojects`

  指定将被视为子项目的以分号分隔的标签列表。在提交配置、测试或构建结果时，此映射将传递给 Cdash。[CTest 脚本](https://cmake.org/cmake/help/latest/manual/ctest.1.html#ctest-script)变量：[`CTEST_LABELS_FOR_SUBPROJECTS`](https://cmake.org/cmake/help/latest/variable/CTEST_LABELS_FOR_SUBPROJECTS.html#variable:CTEST_LABELS_FOR_SUBPROJECTS)[`CTest`](https://cmake.org/cmake/help/latest/module/CTest.html#module:CTest)模块变量：`CTEST_LABELS_FOR_SUBPROJECTS`请参阅[标签和子项目摘要](https://cmake.org/cmake/help/latest/manual/ctest.1.html#label-and-subproject-summary)。

- `TestLoad`

  在并行运行测试时（例如使用`-j`），当测试可能导致 CPU 负载超过给定阈值时，尽量不要启动测试。[CTest 脚本](https://cmake.org/cmake/help/latest/manual/ctest.1.html#ctest-script)变量：[`CTEST_TEST_LOAD`](https://cmake.org/cmake/help/latest/variable/CTEST_TEST_LOAD.html#variable:CTEST_TEST_LOAD)[`CTest`](https://cmake.org/cmake/help/latest/module/CTest.html#module:CTest)模块变量：`CTEST_TEST_LOAD`

- `TimeOut`

  如果未指定，则每个测试的默认超时 [`TIMEOUT`](https://cmake.org/cmake/help/latest/prop_test/TIMEOUT.html#prop_test:TIMEOUT)测试属性。[CTest 脚本](https://cmake.org/cmake/help/latest/manual/ctest.1.html#ctest-script)变量：[`CTEST_TEST_TIMEOUT`](https://cmake.org/cmake/help/latest/variable/CTEST_TEST_TIMEOUT.html#variable:CTEST_TEST_TIMEOUT)[`CTest`](https://cmake.org/cmake/help/latest/module/CTest.html#module:CTest)模块变量：`DART_TESTING_TIMEOUT`

要向 CDash 报告额外的测试值，请参阅[额外的测试测量](https://cmake.org/cmake/help/latest/command/ctest_test.html#additional-test-measurements)。



### [CTest 覆盖步骤](https://cmake.org/cmake/help/latest/manual/ctest.1.html#id32)

在[CTest 脚本](https://cmake.org/cmake/help/latest/manual/ctest.1.html#ctest-script)中，[`ctest_coverage()`](https://cmake.org/cmake/help/latest/command/ctest_coverage.html#command:ctest_coverage)命令运行此步骤。命令的参数可以指定一些步骤设置。

配置设置包括：

- `CoverageCommand`

  用于执行软件覆盖分析的命令行工具。它将在 `BuildDirectory`设置指定的位置执行。[CTest 脚本](https://cmake.org/cmake/help/latest/manual/ctest.1.html#ctest-script)变量：[`CTEST_COVERAGE_COMMAND`](https://cmake.org/cmake/help/latest/variable/CTEST_COVERAGE_COMMAND.html#variable:CTEST_COVERAGE_COMMAND)[`CTest`](https://cmake.org/cmake/help/latest/module/CTest.html#module:CTest)模块变量：`COVERAGE_COMMAND`

- `CoverageExtraFlags`

  指定工具的命令行选项`CoverageCommand`。[CTest 脚本](https://cmake.org/cmake/help/latest/manual/ctest.1.html#ctest-script)变量：[`CTEST_COVERAGE_EXTRA_FLAGS`](https://cmake.org/cmake/help/latest/variable/CTEST_COVERAGE_EXTRA_FLAGS.html#variable:CTEST_COVERAGE_EXTRA_FLAGS)[`CTest`](https://cmake.org/cmake/help/latest/module/CTest.html#module:CTest)模块变量：`COVERAGE_EXTRA_FLAGS`这些选项是传递给的第一个参数`CoverageCommand`。



### [CTest MemCheck 步骤](https://cmake.org/cmake/help/latest/manual/ctest.1.html#id33)

在[CTest 脚本](https://cmake.org/cmake/help/latest/manual/ctest.1.html#ctest-script)中，[`ctest_memcheck()`](https://cmake.org/cmake/help/latest/command/ctest_memcheck.html#command:ctest_memcheck)命令运行此步骤。命令的参数可以指定一些步骤设置。

配置设置包括：

- `MemoryCheckCommand`

  执行动态分析的命令行工具。测试命令行将通过此工具启动。[CTest 脚本](https://cmake.org/cmake/help/latest/manual/ctest.1.html#ctest-script)变量：[`CTEST_MEMORYCHECK_COMMAND`](https://cmake.org/cmake/help/latest/variable/CTEST_MEMORYCHECK_COMMAND.html#variable:CTEST_MEMORYCHECK_COMMAND)[`CTest`](https://cmake.org/cmake/help/latest/module/CTest.html#module:CTest)模块变量：`MEMORYCHECK_COMMAND`

- `MemoryCheckCommandOptions`

  指定工具的命令行选项`MemoryCheckCommand`。它们将被放置在测试命令行之前。[CTest 脚本](https://cmake.org/cmake/help/latest/manual/ctest.1.html#ctest-script)变量：[`CTEST_MEMORYCHECK_COMMAND_OPTIONS`](https://cmake.org/cmake/help/latest/variable/CTEST_MEMORYCHECK_COMMAND_OPTIONS.html#variable:CTEST_MEMORYCHECK_COMMAND_OPTIONS)[`CTest`](https://cmake.org/cmake/help/latest/module/CTest.html#module:CTest)模块变量：`MEMORYCHECK_COMMAND_OPTIONS`

- `MemoryCheckType`

  指定要执行的内存检查的类型。[CTest 脚本](https://cmake.org/cmake/help/latest/manual/ctest.1.html#ctest-script)变量：[`CTEST_MEMORYCHECK_TYPE`](https://cmake.org/cmake/help/latest/variable/CTEST_MEMORYCHECK_TYPE.html#variable:CTEST_MEMORYCHECK_TYPE)[`CTest`](https://cmake.org/cmake/help/latest/module/CTest.html#module:CTest)模块变量：`MEMORYCHECK_TYPE`

- `MemoryCheckSanitizerOptions`

  使用启用 sanitize 的构建运行时指定 sanitizer 的选项。[CTest 脚本](https://cmake.org/cmake/help/latest/manual/ctest.1.html#ctest-script)变量：[`CTEST_MEMORYCHECK_SANITIZER_OPTIONS`](https://cmake.org/cmake/help/latest/variable/CTEST_MEMORYCHECK_SANITIZER_OPTIONS.html#variable:CTEST_MEMORYCHECK_SANITIZER_OPTIONS)[`CTest`](https://cmake.org/cmake/help/latest/module/CTest.html#module:CTest)模块变量：`MEMORYCHECK_SANITIZER_OPTIONS`

- `MemoryCheckSuppressionFile`

  指定包含 `MemoryCheckCommand`工具抑制规则的文件。它将与适合该工具的选项一起传递。[CTest 脚本](https://cmake.org/cmake/help/latest/manual/ctest.1.html#ctest-script)变量：[`CTEST_MEMORYCHECK_SUPPRESSIONS_FILE`](https://cmake.org/cmake/help/latest/variable/CTEST_MEMORYCHECK_SUPPRESSIONS_FILE.html#variable:CTEST_MEMORYCHECK_SUPPRESSIONS_FILE)[`CTest`](https://cmake.org/cmake/help/latest/module/CTest.html#module:CTest)模块变量：`MEMORYCHECK_SUPPRESSIONS_FILE`

其他配置设置包括：

- `BoundsCheckerCommand`

  指定`MemoryCheckCommand`已知与边界检查器兼容的命令行。[CTest 脚本](https://cmake.org/cmake/help/latest/manual/ctest.1.html#ctest-script)变量：无[`CTest`](https://cmake.org/cmake/help/latest/module/CTest.html#module:CTest)模块变量：无

- `PurifyCommand`

  指定一个`MemoryCheckCommand`已知与 Purify 兼容的命令行。[CTest 脚本](https://cmake.org/cmake/help/latest/manual/ctest.1.html#ctest-script)变量：无[`CTest`](https://cmake.org/cmake/help/latest/module/CTest.html#module:CTest)模块变量：`PURIFYCOMMAND`

- `ValgrindCommand`

  指定一个`MemoryCheckCommand`已知与 Valgrind 兼容的命令行。[CTest 脚本](https://cmake.org/cmake/help/latest/manual/ctest.1.html#ctest-script)变量：无[`CTest`](https://cmake.org/cmake/help/latest/module/CTest.html#module:CTest)模块变量：`VALGRIND_COMMAND`

- `ValgrindCommandOptions`

  指定工具的命令行选项`ValgrindCommand`。它们将被放置在测试命令行之前。[CTest 脚本](https://cmake.org/cmake/help/latest/manual/ctest.1.html#ctest-script)变量：无[`CTest`](https://cmake.org/cmake/help/latest/module/CTest.html#module:CTest)模块变量：`VALGRIND_COMMAND_OPTIONS`

- `DrMemoryCommand`

  指定`MemoryCheckCommand`已知与 DrMemory 兼容的命令行。[CTest 脚本](https://cmake.org/cmake/help/latest/manual/ctest.1.html#ctest-script)变量：无[`CTest`](https://cmake.org/cmake/help/latest/module/CTest.html#module:CTest)模块变量：`DRMEMORY_COMMAND`

- `DrMemoryCommandOptions`

  指定工具的命令行选项`DrMemoryCommand`。它们将被放置在测试命令行之前。[CTest 脚本](https://cmake.org/cmake/help/latest/manual/ctest.1.html#ctest-script)变量：无[`CTest`](https://cmake.org/cmake/help/latest/module/CTest.html#module:CTest)模块变量：`DRMEMORY_COMMAND_OPTIONS`

- `CudaSanitizerCommand`

  指定`MemoryCheckCommand`已知与 cuda-memcheck 或 compute-sanitizer 兼容的命令行。[CTest 脚本](https://cmake.org/cmake/help/latest/manual/ctest.1.html#ctest-script)变量：无[`CTest`](https://cmake.org/cmake/help/latest/module/CTest.html#module:CTest)模块变量：`CUDA_SANITIZER_COMMAND`

- `CudaSanitizerCommandOptions`

  指定工具的命令行选项`CudaSanitizerCommand`。它们将被放置在测试命令行之前。[CTest 脚本](https://cmake.org/cmake/help/latest/manual/ctest.1.html#ctest-script)变量：无[`CTest`](https://cmake.org/cmake/help/latest/module/CTest.html#module:CTest)模块变量：`CUDA_SANITIZER_COMMAND_OPTIONS`



### [CTest 提交步骤](https://cmake.org/cmake/help/latest/manual/ctest.1.html#id34)

在[CTest 脚本](https://cmake.org/cmake/help/latest/manual/ctest.1.html#ctest-script)中，[`ctest_submit()`](https://cmake.org/cmake/help/latest/command/ctest_submit.html#command:ctest_submit)命令运行此步骤。命令的参数可以指定一些步骤设置。

配置设置包括：

- `BuildName`

  用短字符串描述仪表板客户端平台。（操作系统、编译器等）[CTest 脚本](https://cmake.org/cmake/help/latest/manual/ctest.1.html#ctest-script)变量：[`CTEST_BUILD_NAME`](https://cmake.org/cmake/help/latest/variable/CTEST_BUILD_NAME.html#variable:CTEST_BUILD_NAME)[`CTest`](https://cmake.org/cmake/help/latest/module/CTest.html#module:CTest)模块变量：`BUILDNAME`

- `CDashVersion`

  旧版选项。不曾用过。[CTest 脚本](https://cmake.org/cmake/help/latest/manual/ctest.1.html#ctest-script)变量：无，从服务器检测到[`CTest`](https://cmake.org/cmake/help/latest/module/CTest.html#module:CTest)模块变量：`CTEST_CDASH_VERSION`

- `CTestSubmitRetryCount`

  指定在网络故障时重试提交的尝试次数。[CTest 脚本](https://cmake.org/cmake/help/latest/manual/ctest.1.html#ctest-script)变量：无，使用[`ctest_submit()`](https://cmake.org/cmake/help/latest/command/ctest_submit.html#command:ctest_submit) `RETRY_COUNT`选项。[`CTest`](https://cmake.org/cmake/help/latest/module/CTest.html#module:CTest)模块变量：`CTEST_SUBMIT_RETRY_COUNT`

- `CTestSubmitRetryDelay`

  在网络故障重试提交之前指定延迟。[CTest 脚本](https://cmake.org/cmake/help/latest/manual/ctest.1.html#ctest-script)变量：无，使用[`ctest_submit()`](https://cmake.org/cmake/help/latest/command/ctest_submit.html#command:ctest_submit) `RETRY_DELAY`选项。[`CTest`](https://cmake.org/cmake/help/latest/module/CTest.html#module:CTest)模块变量：`CTEST_SUBMIT_RETRY_DELAY`

- `CurlOptions`

  指定以分号分隔的选项列表，以控制 CTest 在内部用于连接到服务器的 Curl 库。可能的选项是`CURLOPT_SSL_VERIFYPEER_OFF` 和`CURLOPT_SSL_VERIFYHOST_OFF`。[CTest 脚本](https://cmake.org/cmake/help/latest/manual/ctest.1.html#ctest-script)变量：[`CTEST_CURL_OPTIONS`](https://cmake.org/cmake/help/latest/variable/CTEST_CURL_OPTIONS.html#variable:CTEST_CURL_OPTIONS)[`CTest`](https://cmake.org/cmake/help/latest/module/CTest.html#module:CTest)模块变量：`CTEST_CURL_OPTIONS`

- `DropLocation`

  旧版选项。如果`SubmitURL`未设置，则由 `DropMethod`、`DropSiteUser`、`DropSitePassword`、`DropSite`和 构造`DropLocation`。[CTest 脚本](https://cmake.org/cmake/help/latest/manual/ctest.1.html#ctest-script)变量：[`CTEST_DROP_LOCATION`](https://cmake.org/cmake/help/latest/variable/CTEST_DROP_LOCATION.html#variable:CTEST_DROP_LOCATION)[`CTest`](https://cmake.org/cmake/help/latest/module/CTest.html#module:CTest)模块变量：`DROP_LOCATION`如果设置，否则`CTEST_DROP_LOCATION`

- `DropMethod`

  旧版选项。如果`SubmitURL`未设置，则由 `DropMethod`、`DropSiteUser`、`DropSitePassword`、`DropSite`和 构造`DropLocation`。[CTest 脚本](https://cmake.org/cmake/help/latest/manual/ctest.1.html#ctest-script)变量：[`CTEST_DROP_METHOD`](https://cmake.org/cmake/help/latest/variable/CTEST_DROP_METHOD.html#variable:CTEST_DROP_METHOD)[`CTest`](https://cmake.org/cmake/help/latest/module/CTest.html#module:CTest)模块变量：`DROP_METHOD`如果设置，否则`CTEST_DROP_METHOD`

- `DropSite`

  旧版选项。如果`SubmitURL`未设置，则由 `DropMethod`、`DropSiteUser`、`DropSitePassword`、`DropSite`和 构造`DropLocation`。[CTest 脚本](https://cmake.org/cmake/help/latest/manual/ctest.1.html#ctest-script)变量：[`CTEST_DROP_SITE`](https://cmake.org/cmake/help/latest/variable/CTEST_DROP_SITE.html#variable:CTEST_DROP_SITE)[`CTest`](https://cmake.org/cmake/help/latest/module/CTest.html#module:CTest)模块变量：`DROP_SITE`如果设置，否则`CTEST_DROP_SITE`

- `DropSitePassword`

  旧版选项。如果`SubmitURL`未设置，则由 `DropMethod`、`DropSiteUser`、`DropSitePassword`、`DropSite`和 构造`DropLocation`。[CTest 脚本](https://cmake.org/cmake/help/latest/manual/ctest.1.html#ctest-script)变量：[`CTEST_DROP_SITE_PASSWORD`](https://cmake.org/cmake/help/latest/variable/CTEST_DROP_SITE_PASSWORD.html#variable:CTEST_DROP_SITE_PASSWORD)[`CTest`](https://cmake.org/cmake/help/latest/module/CTest.html#module:CTest)模块变量：`DROP_SITE_PASSWORD`如果设置，否则`CTEST_DROP_SITE_PASWORD`

- `DropSiteUser`

  旧版选项。如果`SubmitURL`未设置，则由 `DropMethod`、`DropSiteUser`、`DropSitePassword`、`DropSite`和 构造`DropLocation`。[CTest 脚本](https://cmake.org/cmake/help/latest/manual/ctest.1.html#ctest-script)变量：[`CTEST_DROP_SITE_USER`](https://cmake.org/cmake/help/latest/variable/CTEST_DROP_SITE_USER.html#variable:CTEST_DROP_SITE_USER)[`CTest`](https://cmake.org/cmake/help/latest/module/CTest.html#module:CTest)模块变量：`DROP_SITE_USER`如果设置，否则`CTEST_DROP_SITE_USER`

- `IsCDash`

  旧版选项。不曾用过。[CTest 脚本](https://cmake.org/cmake/help/latest/manual/ctest.1.html#ctest-script)变量：[`CTEST_DROP_SITE_CDASH`](https://cmake.org/cmake/help/latest/variable/CTEST_DROP_SITE_CDASH.html#variable:CTEST_DROP_SITE_CDASH)[`CTest`](https://cmake.org/cmake/help/latest/module/CTest.html#module:CTest)模块变量：`CTEST_DROP_SITE_CDASH`

- `ScpCommand`

  旧版选项。不曾用过。[CTest 脚本](https://cmake.org/cmake/help/latest/manual/ctest.1.html#ctest-script)变量：[`CTEST_SCP_COMMAND`](https://cmake.org/cmake/help/latest/variable/CTEST_SCP_COMMAND.html#variable:CTEST_SCP_COMMAND)[`CTest`](https://cmake.org/cmake/help/latest/module/CTest.html#module:CTest)模块变量：`SCPCOMMAND`

- `Site`

  用短字符串描述仪表板客户端主机站点。（主机名、域等）[CTest 脚本](https://cmake.org/cmake/help/latest/manual/ctest.1.html#ctest-script)变量：[`CTEST_SITE`](https://cmake.org/cmake/help/latest/variable/CTEST_SITE.html#variable:CTEST_SITE)[`CTest`](https://cmake.org/cmake/help/latest/module/CTest.html#module:CTest)模块变量：`SITE`，由[`site_name()`](https://cmake.org/cmake/help/latest/command/site_name.html#command:site_name)命令

- `SubmitURL`

  将提交发送到的仪表板服务器的`http`或URL。`https`[CTest 脚本](https://cmake.org/cmake/help/latest/manual/ctest.1.html#ctest-script)变量：[`CTEST_SUBMIT_URL`](https://cmake.org/cmake/help/latest/variable/CTEST_SUBMIT_URL.html#variable:CTEST_SUBMIT_URL)[`CTest`](https://cmake.org/cmake/help/latest/module/CTest.html#module:CTest)模块变量：`SUBMIT_URL`如果设置，否则`CTEST_SUBMIT_URL`

- `SubmitInactivityTimeout`

  等待提交的时间，如果未完成则取消。指定零值以禁用超时。[CTest 脚本](https://cmake.org/cmake/help/latest/manual/ctest.1.html#ctest-script)变量：[`CTEST_SUBMIT_INACTIVITY_TIMEOUT`](https://cmake.org/cmake/help/latest/variable/CTEST_SUBMIT_INACTIVITY_TIMEOUT.html#variable:CTEST_SUBMIT_INACTIVITY_TIMEOUT)[`CTest`](https://cmake.org/cmake/help/latest/module/CTest.html#module:CTest)模块变量：`CTEST_SUBMIT_INACTIVITY_TIMEOUT`

- `TriggerSite`

  旧版选项。不曾用过。[CTest 脚本](https://cmake.org/cmake/help/latest/manual/ctest.1.html#ctest-script)变量：[`CTEST_TRIGGER_SITE`](https://cmake.org/cmake/help/latest/variable/CTEST_TRIGGER_SITE.html#variable:CTEST_TRIGGER_SITE)[`CTest`](https://cmake.org/cmake/help/latest/module/CTest.html#module:CTest)模块变量：`TRIGGER_SITE`如果设置，否则`CTEST_TRIGGER_SITE`



## [显示为 JSON 对象模型](https://cmake.org/cmake/help/latest/manual/ctest.1.html#id35)

给出命令行选项时`--show-only=json-v1`，以 JSON 格式输出测试信息。JSON对象模型的1.0版本定义如下：

- `kind`

  字符串“ctestInfo”。

- `version`

  指定版本组件的 JSON 对象。它的成员是`major`指定主要版本组件的非负整数。`minor`指定次要版本组件的非负整数。

- `backtraceGraph`

  JSON 对象表示具有以下成员的回溯信息：`commands`命令名称列表。`files`文件名列表。`nodes`具有成员的节点 JSON 对象列表：`command`索引到 的`commands`成员中`backtraceGraph`。`file`索引到 的`files`成员中`backtraceGraph`。`line`添加回溯的文件中的行号。`parent`索引到 图中代表父级的`nodes`成员。`backtraceGraph`

- `tests`

  列出每个测试的信息的 JSON 数组。每个条目都是一个带有成员的 JSON 对象：`name`测试名称。`config`可以运行测试的配置。空字符串表示任何配置。`command`列出第一个元素是测试命令，其余元素是命令参数。`backtrace`索引到 的`nodes`成员中`backtraceGraph`。`properties`测试属性。可以包含每个受支持的测试属性的键。



## [资源分配](https://cmake.org/cmake/help/latest/manual/ctest.1.html#id36)

CTest 提供了一种机制让测试以细粒度的方式指定他们需要的资源，并让用户指定正在运行的机器上可用的资源。这允许 CTest 在内部跟踪哪些资源正在使用，哪些资源是免费的，以防止它们尝试声明不可用资源的方式安排测试。

当使用资源分配特性时，CTest 不会超额订阅资源。例如，如果一个资源有 8 个插槽，CTest 将不会运行一次共同使用超过 8 个插槽的测试。这具有限制在任何给定时间可以运行多少测试的效果，即使使用高`-j` 参数，如果这些测试都使用来自同一资源的一些槽。此外，这意味着使用比机器上可用资源更多的资源的单个测试根本不会运行（并将报告为 ）。`Not Run`

此功能的一个常见用例是用于需要使用 GPU 的测试。多个测试可以同时从 GPU 分配内存，但如果太多测试尝试同时执行此操作，其中一些测试将无法分配，从而导致测试失败，即使测试会成功，如果它有所需的内存. 通过使用资源分配功能，每个测试都可以指定它需要 GPU 多少内存，从而允许 CTest 以一种同时运行多个这些测试不会耗尽 GPU 内存池的方式安排测试。

请注意，CTest 不知道 GPU 是什么或它有多少内存，也没有任何方式与 GPU 通信以检索此信息或执行任何内存管理。CTest 只是跟踪抽象资源类型的列表，每个资源类型都有一定数量的可用插槽供测试使用。每个测试都指定了它需要从某个资源获得的插槽数，然后 CTest 以一种防止正在使用的插槽总数超过列出的容量的方式安排它们。当一个测试被执行并且一个资源中的槽被分配给那个测试时，测试可以假设它们在测试过程的持续时间内独占使用这些槽。

CTest 资源分配功能包含两个输入：

- [资源规范文件](https://cmake.org/cmake/help/latest/manual/ctest.1.html#ctest-resource-specification-file)，如下所述，描述系统上可用的资源。
- 这[`RESOURCE_GROUPS`](https://cmake.org/cmake/help/latest/prop_test/RESOURCE_GROUPS.html#prop_test:RESOURCE_GROUPS)测试的属性，它描述了测试所需的资源。

[当 CTest 运行测试时，分配给该测试的资源以一组环境变量](https://cmake.org/cmake/help/latest/manual/ctest.1.html#ctest-resource-environment-variables)的形式传递， 如下所述。使用此信息来决定连接到哪个资源留给测试编写者。

该`RESOURCE_GROUPS`属性告诉 CTest 测试期望使用哪些资源以对测试有意义的方式分组。测试本身必须读取[环境变量](https://cmake.org/cmake/help/latest/manual/ctest.1.html#ctest-resource-environment-variables)以确定哪些资源已分配给每个组。例如，每个组可能对应于测试在执行时将产生的进程。

请注意，即使测试指定了一个属性，如果用户没有传递资源规范文件`RESOURCE_GROUPS`，它仍然可以在没有任何资源分配（并且没有相应的 [环境变量）的情况下运行。](https://cmake.org/cmake/help/latest/manual/ctest.1.html#ctest-resource-environment-variables)通过`--resource-spec-file`命令行参数或 `RESOURCE_SPEC_FILE`参数传递这个文件[`ctest_test()`](https://cmake.org/cmake/help/latest/command/ctest_test.html#command:ctest_test), 是激活资源分配功能的原因。测试应该检查 `CTEST_RESOURCE_GROUP_COUNT`环境变量以确定资源分配是否被激活。如果激活资源分配，将始终（且仅）定义此变量。如果没有激活资源分配，那么该`CTEST_RESOURCE_GROUP_COUNT`变量将不存在，即使它存在于父`ctest`进程。如果测试绝对必须有资源分配，那么它可以返回失败的退出代码或使用 [`SKIP_RETURN_CODE`](https://cmake.org/cmake/help/latest/prop_test/SKIP_RETURN_CODE.html#prop_test:SKIP_RETURN_CODE)或者[`SKIP_REGULAR_EXPRESSION`](https://cmake.org/cmake/help/latest/prop_test/SKIP_REGULAR_EXPRESSION.html#prop_test:SKIP_REGULAR_EXPRESSION) 属性来指示跳过的测试。



### [资源规范文件](https://cmake.org/cmake/help/latest/manual/ctest.1.html#id37)

资源规范文件是传递给 CTest 的 JSON 文件，无论是在[`ctest(1)`](https://cmake.org/cmake/help/latest/manual/ctest.1.html#manual:ctest(1))命令行作为`--resource-spec-file`，或作为 的 `RESOURCE_SPEC_FILE`参数[`ctest_test()`](https://cmake.org/cmake/help/latest/command/ctest_test.html#command:ctest_test). 如果使用仪表板脚本`RESOURCE_SPEC_FILE`但未指定，则值为 [`CTEST_RESOURCE_SPEC_FILE`](https://cmake.org/cmake/help/latest/variable/CTEST_RESOURCE_SPEC_FILE.html#variable:CTEST_RESOURCE_SPEC_FILE)而是使用仪表板脚本中的。如果`--resource-spec-file`,`RESOURCE_SPEC_FILE`和 [`CTEST_RESOURCE_SPEC_FILE`](https://cmake.org/cmake/help/latest/variable/CTEST_RESOURCE_SPEC_FILE.html#variable:CTEST_RESOURCE_SPEC_FILE)在仪表板脚本中未指定，值为[`CTEST_RESOURCE_SPEC_FILE`](https://cmake.org/cmake/help/latest/variable/CTEST_RESOURCE_SPEC_FILE.html#variable:CTEST_RESOURCE_SPEC_FILE)而是使用 CMake 构建中的。如果没有指定这些，则不使用资源规范文件。

资源规范文件必须是 JSON 对象。本文档中的所有示例都假定以下资源规范文件：

```
{
  "version": {
    "major": 1,
    "minor": 0
  },
  "local": [
    {
      "gpus": [
        {
          "id": "0",
          "slots": 2
        },
        {
          "id": "1",
          "slots": 4
        },
        {
          "id": "2",
          "slots": 2
        },
        {
          "id": "3"
        }
      ],
      "crypto_chips": [
        {
          "id": "card0",
          "slots": 4
        }
      ]
    }
  ]
}
```

成员是：

- `version`

  包含一个`major`整数字段和一个`minor`整数字段的对象。目前，唯一支持的版本是 major `1`， minor `0`。任何其他值都是错误。

- `local`

  系统上存在的 JSON 资源集数组。目前，此数组的大小限制为 1。每个数组元素都是一个 JSON 对象，其成员的名称与所需的资源类型相同，例如`gpus`. 这些名称必须以小写字母或下划线开头，后面的字符可以是小写字母、数字或下划线。不允许使用大写字母，因为某些平台具有不区分大小写的环境变量。有关详细信息，请参阅下面的[环境变量](https://cmake.org/cmake/help/latest/manual/ctest.1.html#environment-variables)部分。建议资源类型名称为名词的复数形式，如`gpus`or `crypto_chips`（和 not `gpu`or `crypto_chip`.）请注意，名称`gpus`和`crypto_chips`只是示例，CTest 不会以任何方式解释它们。您可以自由组合任何想要满足自己要求的资源类型。每个资源类型的值是一个 JSON 数组，由 JSON 对象组成，每个对象描述指定资源的特定实例。这些对象具有以下成员：`id`由资源标识符组成的字符串。标识符中的每个字符都可以是小写字母、数字或下划线。不允许使用大写字母。标识符在资源类型中必须是唯一的。但是，它们不必跨资源类型是唯一的。例如，拥有一个 `gpus`名为的资源`0`和一个`crypto_chips`名为的资源是有效的`0`，但不能`gpus`同时拥有两个名为 的资源`0`。请注意，ID `0`、`1`、`2`、`3`和`card0`只是示例，CTest 不会以任何方式解释它们。您可以根据自己的要求随意制作任何想要的 ID。`slots`一个可选的无符号数，指定资源上可用的插槽数。例如，这可能是 GPU 上的兆字节 RAM，或加密芯片上可用的加密单元。如果`slots`未指定，`1`则假定默认值为 。

在上面的示例文件中，有四个 ID 为 0 到 3 的 GPU。GPU 0 有 2 个插槽，GPU 1 有 4 个，GPU 2 有 2 个，GPU 3 有默认的 1 个插槽。还有一个带有 4 个插槽的加密芯片。

### [`RESOURCE_GROUPS` Property](https://cmake.org/cmake/help/latest/manual/ctest.1.html#id38)

看[`RESOURCE_GROUPS`](https://cmake.org/cmake/help/latest/prop_test/RESOURCE_GROUPS.html#prop_test:RESOURCE_GROUPS)有关此属性的说明。



### [环境变量](https://cmake.org/cmake/help/latest/manual/ctest.1.html#id39)

一旦 CTest 决定为测试分配哪些资源，它就会将此信息作为一系列环境变量传递给测试可执行文件。对于下面的每个示例，我们将假设所讨论的测试具有 [`RESOURCE_GROUPS`](https://cmake.org/cmake/help/latest/prop_test/RESOURCE_GROUPS.html#prop_test:RESOURCE_GROUPS)的财产 `2,gpus:2;gpus:4,gpus:1,crypto_chips:2`。

以下变量传递给测试过程：

- **CTEST_RESOURCE_GROUP_COUNT**

  指定的组总数[`RESOURCE_GROUPS`](https://cmake.org/cmake/help/latest/prop_test/RESOURCE_GROUPS.html#prop_test:RESOURCE_GROUPS) 财产。例如：`CTEST_RESOURCE_GROUP_COUNT=3`仅在以下情况下才会定义此变量[`ctest(1)`](https://cmake.org/cmake/help/latest/manual/ctest.1.html#manual:ctest(1))已获得 `--resource-spec-file`, 或者如果[`ctest_test()`](https://cmake.org/cmake/help/latest/command/ctest_test.html#command:ctest_test)已获得 `RESOURCE_SPEC_FILE`. 如果没有给出资源规范文件，则不会定义该变量。

- **CTEST_RESOURCE_GROUP_<数字>**

  分配给每个组的资源类型列表，每个项目用逗号分隔。`<num>`是一个从零到 `CTEST_RESOURCE_GROUP_COUNT`负一的数。为该范围内`CTEST_RESOURCE_GROUP_<num>` 的每个定义。`<num>`例如：`CTEST_RESOURCE_GROUP_0=gpus``CTEST_RESOURCE_GROUP_1=gpus``CTEST_RESOURCE_GROUP_2=crypto_chips,gpus`

- **CTEST_RESOURCE_GROUP_<num>_<resource-type>**

  针对给定资源类型分配给每个组的每个 ID 的资源 ID 列表和插槽数。该变量由一系列对组成，每对由分号分隔，对中的两个项目由逗号分隔。每对中的第一项`id:`后面是类型为 的资源的 ID，`<resource-type>`第二项 `slots:`后面是分配给给定组的该资源的槽数。例如：`CTEST_RESOURCE_GROUP_0_GPUS=id:0,slots:2``CTEST_RESOURCE_GROUP_1_GPUS=id:2,slots:2``CTEST_RESOURCE_GROUP_2_GPUS=id:1,slots:4;id:3,slots:1``CTEST_RESOURCE_GROUP_2_CRYPTO_CHIPS=id:card0,slots:2`在此示例中，组 0 从 GPU 获得 2 个插槽`0`，组 1 从 GPU 获得 2 个插槽，`2`组 2 从 GPU 获得 4 个插槽，从 GPU 获得`1`1 个插槽`3`，从密码芯片获得 2 个插槽`card0`。`<num>`是一个从零到`CTEST_RESOURCE_GROUP_COUNT`负一的数。 `<resource-type>`是资源类型的名称，转换为大写。 为上面列出的范围内的每个和列出的每个资源类型 `CTEST_RESOURCE_GROUP_<num>_<resource-type>`的产品定义。`<num>``CTEST_RESOURCE_GROUP_<num>`由于某些平台的环境变量名称不区分大小写，因此资源类型的名称在不区分大小写的环境中可能不会发生冲突。因此，为简单起见，所有资源类型必须在 [资源规范文件](https://cmake.org/cmake/help/latest/manual/ctest.1.html#ctest-resource-specification-file)和[`RESOURCE_GROUPS`](https://cmake.org/cmake/help/latest/prop_test/RESOURCE_GROUPS.html#prop_test:RESOURCE_GROUPS)属性，并且它们在`CTEST_RESOURCE_GROUP_<num>_<resource-type>`环境变量中被转换为全大写。

## [另见](https://cmake.org/cmake/help/latest/manual/ctest.1.html#id40)

以下资源可用于获取使用 CMake 的帮助：

- 主页

  [https://cmake.org](https://cmake.org/)学习 CMake 的主要起点。

- 在线文档和社区资源

  https://cmake.org/documentation可在此网页上找到指向可用文档和社区资源的链接。

- 话语论坛

  [https://discourse.cmake.org](https://discourse.cmake.org/)Discourse Forum 主持有关 CMake 的讨论和问题。

达世币：[https : ](https://cdash.org/)//cdash.org