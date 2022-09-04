# [ctest_build](https://cmake.org/cmake/help/latest/command/ctest_build.html)

作为[仪表板客户端](https://cmake.org/cmake/help/latest/manual/ctest.1.html#dashboard-client)执行[CTest 构建步骤](https://cmake.org/cmake/help/latest/manual/ctest.1.html#ctest-build-step)。

```cmake
ctest_build([BUILD <build-dir>] [APPEND]
            [CONFIGURATION <config>]
            [PARALLEL_LEVEL <parallel>]
            [FLAGS <flags>]
            [PROJECT_NAME <project-name>]
            [TARGET <target-name>]
            [NUMBER_ERRORS <num-err-var>]
            [NUMBER_WARNINGS <num-warn-var>]
            [RETURN_VALUE <result-var>]
            [CAPTURE_CMAKE_ERROR <result-var>]
            )
```

构建项目并存储结果以`Build.xml` 用于提交[`ctest_submit()`](https://cmake.org/cmake/help/latest/command/ctest_submit.html#command:ctest_submit)命令。

这[`CTEST_BUILD_COMMAND`](https://cmake.org/cmake/help/latest/variable/CTEST_BUILD_COMMAND.html#variable:CTEST_BUILD_COMMAND)变量可以设置为显式指定构建命令行。否则，构建命令行会根据给定的选项自动计算。

选项包括：

- `BUILD <build-dir>`

  指定顶级构建目录。如果没有给出，则 [`CTEST_BINARY_DIRECTORY`](https://cmake.org/cmake/help/latest/variable/CTEST_BINARY_DIRECTORY.html#variable:CTEST_BINARY_DIRECTORY)使用变量。

- `APPEND`

  标记`Build.xml`附加到自上次以来提交到仪表板服务器的结果[`ctest_start()`](https://cmake.org/cmake/help/latest/command/ctest_start.html#command:ctest_start)称呼。附加语义由正在使用的仪表板服务器定义。这不会*导致*将结果附加到`.xml`先前调用此命令生成的文件中。

- `CONFIGURATION <config>`

  指定构建配置（例如`Debug`）。如果未指定，`CTEST_BUILD_CONFIGURATION`将检查变量。否则给予的选项`-C <cfg>`[`ctest(1)`](https://cmake.org/cmake/help/latest/manual/ctest.1.html#manual:ctest(1)) 将使用命令，如果有的话。

- `PARALLEL_LEVEL <parallel>`

  *3.21 版中的新功能。*指定底层构建系统的并行级别。如果未指定，则[`CMAKE_BUILD_PARALLEL_LEVEL`](https://cmake.org/cmake/help/latest/envvar/CMAKE_BUILD_PARALLEL_LEVEL.html#envvar:CMAKE_BUILD_PARALLEL_LEVEL)将检查环境变量。

- `FLAGS <flags>`

  将附加参数传递给底层构建命令。如果未指定，`CTEST_BUILD_FLAGS`将检查变量。例如，这可以用于使用 `-j`make 选项触发并行构建。见[`ProcessorCount`](https://cmake.org/cmake/help/latest/module/ProcessorCount.html#module:ProcessorCount)以模块为例。

- `PROJECT_NAME <project-name>`

  自 CMake 3.0 起被忽略。*在 3.14 版更改：*不再需要此值。

- `TARGET <target-name>`

  指定要构建的目标的名称。如果未指定， `CTEST_BUILD_TARGET`将检查变量。否则将构建默认目标。这是“全部”目标（`ALL_BUILD`在[Visual Studio Generators](https://cmake.org/cmake/help/latest/manual/cmake-generators.7.html#visual-studio-generators)中调用）。

- `NUMBER_ERRORS <num-err-var>`

  将检测到的构建错误数存储在给定变量中。

- `NUMBER_WARNINGS <num-warn-var>`

  存储在给定变量中检测到的构建警告的数量。

- `RETURN_VALUE <result-var>`

  将本机构建工具的返回值存储在给定变量中。

- `CAPTURE_CMAKE_ERROR <result-var>`

  *3.7 版中的新功能。*如果运行命令有任何错误，则存储在`<result-var>`变量 -1 中，如果发生错误，则防止 ctest 返回非零值。

- `QUIET`

  *3.3 版中的新功能。*抑制任何本来会打印到控制台的 CTest 特定的非错误输出。警告/错误的摘要以及本机构建工具的输出不受此选项的影响。

# [ctest_configure](https://cmake.org/cmake/help/latest/command/ctest_configure.html)

作为[仪表板客户端](https://cmake.org/cmake/help/latest/manual/ctest.1.html#dashboard-client)执行[CTest 配置步骤](https://cmake.org/cmake/help/latest/manual/ctest.1.html#ctest-configure-step)。

```cmake
ctest_configure([BUILD <build-dir>] [SOURCE <source-dir>] [APPEND]
                [OPTIONS <options>] [RETURN_VALUE <result-var>] [QUIET]
                [CAPTURE_CMAKE_ERROR <result-var>])
```

配置项目构建树并记录结果以`Configure.xml` 用于提交[`ctest_submit()`](https://cmake.org/cmake/help/latest/command/ctest_submit.html#command:ctest_submit)命令。

选项包括：

- `BUILD <build-dir>`

  指定顶级构建目录。如果没有给出，则 [`CTEST_BINARY_DIRECTORY`](https://cmake.org/cmake/help/latest/variable/CTEST_BINARY_DIRECTORY.html#variable:CTEST_BINARY_DIRECTORY)使用变量。

- `SOURCE <source-dir>`

  指定源目录。如果没有给出，则 [`CTEST_SOURCE_DIRECTORY`](https://cmake.org/cmake/help/latest/variable/CTEST_SOURCE_DIRECTORY.html#variable:CTEST_SOURCE_DIRECTORY)使用变量。

- `APPEND`

  标记`Configure.xml`附加到自上次以来提交到仪表板服务器的结果[`ctest_start()`](https://cmake.org/cmake/help/latest/command/ctest_start.html#command:ctest_start)称呼。附加语义由正在使用的仪表板服务器定义。这不会*导致*将结果附加到`.xml`先前调用此命令生成的文件中。

- `OPTIONS <options>`

  指定要传递给配置工具的命令行参数。

- `RETURN_VALUE <result-var>`

  在`<result-var>`变量中存储原生配置工具的返回值。

- `CAPTURE_CMAKE_ERROR <result-var>`

  *3.7 版中的新功能。*如果运行命令有任何错误，则存储在`<result-var>`变量 -1 中，如果发生错误，则防止 ctest 返回非零值。

- `QUIET`

  *3.3 版中的新功能。*抑制任何本来会打印到控制台的 CTest 特定的非错误消息。底层配置命令的输出不受影响。



# [ctest_coverage](https://cmake.org/cmake/help/latest/command/ctest_coverage.html)

作为[仪表板客户端](https://cmake.org/cmake/help/latest/manual/ctest.1.html#dashboard-client)执行[CTest 覆盖步骤](https://cmake.org/cmake/help/latest/manual/ctest.1.html#ctest-coverage-step)。

```cmake
ctest_coverage([BUILD <build-dir>] [APPEND]
               [LABELS <label>...]
               [RETURN_VALUE <result-var>]
               [CAPTURE_CMAKE_ERROR <result-var>]
               [QUIET]
               )
```

收集覆盖工具结果并将其存储起来以`Coverage.xml` 与[`ctest_submit()`](https://cmake.org/cmake/help/latest/command/ctest_submit.html#command:ctest_submit)命令。

选项包括：

- `BUILD <build-dir>`

  指定顶级构建目录。如果没有给出，则 [`CTEST_BINARY_DIRECTORY`](https://cmake.org/cmake/help/latest/variable/CTEST_BINARY_DIRECTORY.html#variable:CTEST_BINARY_DIRECTORY)使用变量。

- `APPEND`

  标记`Coverage.xml`附加到自上次以来提交到仪表板服务器的结果[`ctest_start()`](https://cmake.org/cmake/help/latest/command/ctest_start.html#command:ctest_start)称呼。附加语义由正在使用的仪表板服务器定义。这不会*导致*将结果附加到`.xml`先前调用此命令生成的文件中。

- `LABELS`

  过滤覆盖率报告以仅包含标有至少一个指定标签的源文件。

- `RETURN_VALUE <result-var>`

  如果覆盖工具运行没有错误，则存储在`<result-var>`变量中，否则存储在变量中。`0`

- `CAPTURE_CMAKE_ERROR <result-var>`

  *3.7 版中的新功能。*如果运行命令有任何错误，则存储在`<result-var>`变量 -1 中，如果发生错误，则防止 ctest 返回非零值。

- `QUIET`

  *3.3 版中的新功能。*抑制任何本来会打印到控制台的 CTest 特定的非错误输出。指示覆盖了多少行代码的摘要不受此选项的影响。



# [ctest_empty_binary_directory](https://cmake.org/cmake/help/latest/command/ctest_empty_binary_directory.html)

清空二进制目录

```cmake
ctest_empty_binary_directory( directory )
```

删除二进制目录。此命令将在删除目录之前执行一些检查，以避免恶意或意外删除目录。



# [ctest_memcheck](https://cmake.org/cmake/help/latest/command/ctest_memcheck.html)

作为[仪表板客户端](https://cmake.org/cmake/help/latest/manual/ctest.1.html#dashboard-client)执行[CTest MemCheck 步骤](https://cmake.org/cmake/help/latest/manual/ctest.1.html#ctest-memcheck-step)。

```cmake
ctest_memcheck([BUILD <build-dir>] [APPEND]
               [START <start-number>]
               [END <end-number>]
               [STRIDE <stride-number>]
               [EXCLUDE <exclude-regex>]
               [INCLUDE <include-regex>]
               [EXCLUDE_LABEL <label-exclude-regex>]
               [INCLUDE_LABEL <label-include-regex>]
               [EXCLUDE_FIXTURE <regex>]
               [EXCLUDE_FIXTURE_SETUP <regex>]
               [EXCLUDE_FIXTURE_CLEANUP <regex>]
               [PARALLEL_LEVEL <level>]
               [RESOURCE_SPEC_FILE <file>]
               [TEST_LOAD <threshold>]
               [SCHEDULE_RANDOM <ON|OFF>]
               [STOP_ON_FAILURE]
               [STOP_TIME <time-of-day>]
               [RETURN_VALUE <result-var>]
               [CAPTURE_CMAKE_ERROR <result-var>]
               [REPEAT <mode>:<n>]
               [OUTPUT_JUNIT <file>]
               [DEFECT_COUNT <defect-count-var>]
               [QUIET]
               )
```

使用动态分析工具运行测试并将结果存储起来 `MemCheck.xml`以便与[`ctest_submit()`](https://cmake.org/cmake/help/latest/command/ctest_submit.html#command:ctest_submit) 命令。

大多数选项与[`ctest_test()`](https://cmake.org/cmake/help/latest/command/ctest_test.html#command:ctest_test)命令。

此命令独有的选项是：

- `DEFECT_COUNT <defect-count-var>`

  *3.8 版中的新功能。*存储`<defect-count-var>`发现的缺陷数。



# [ctest_read_custom_files](https://cmake.org/cmake/help/latest/command/ctest_read_custom_files.html)

读取 CTestCustom 文件。

```cmake
ctest_read_custom_files( directory ... )
```

从给定目录中读取所有 CTestCustom.ctest 或 CTestCustom.cmake 文件。

默认情况下，调用[`ctest(1)`](https://cmake.org/cmake/help/latest/manual/ctest.1.html#manual:ctest(1))没有脚本将从二进制目录中读取自定义文件。



# [ctest_run_script](https://cmake.org/cmake/help/latest/command/ctest_run_script.html)

运行 ctest -S 脚本

```cmake
ctest_run_script([NEW_PROCESS] script_file_name script_file_name1
            script_file_name2 ... [RETURN_VALUE var])
```

运行一个或多个脚本，就像从 ctest -S 运行一样。如果未提供参数，则使用变量的当前设置运行当前脚本。如果`NEW_PROCESS`指定，则每个脚本将在单独的进程中运行。`RETURN_VALUE`如果指定，最后一个脚本运行的返回值将被放入`var`.



# [ctest_sleep](https://cmake.org/cmake/help/latest/command/ctest_sleep.html)

睡了一段时间

```cmake
ctest_sleep(<seconds>)
```cmake

休眠给定的秒数。

```cmake
ctest_sleep(<time1> <duration> <time2>)
```cmake

如果 t > 0，则休眠 t=(time1 + duration - time2) 秒。



# [ctest_start](https://cmake.org/cmake/help/latest/command/ctest_start.html)

开始对给定模型的测试

```cmake
ctest_start(<model> [<source> [<binary>]] [GROUP <group>] [QUIET])

ctest_start([<model> [<source> [<binary>]]] [GROUP <group>] APPEND [QUIET])
```

开始对给定模型的测试。该命令应在二进制目录初始化后调用。

参数如下：

- `<model>`

  设置仪表板模型。必须是`Experimental`、`Continuous`或 之一`Nightly`。`APPEND`除非指定，否则此参数是必需的。

- `<source>`

  设置源目录。如果未指定，则值为 [`CTEST_SOURCE_DIRECTORY`](https://cmake.org/cmake/help/latest/variable/CTEST_SOURCE_DIRECTORY.html#variable:CTEST_SOURCE_DIRECTORY)改为使用。

- `<binary>`

  设置二进制目录。如果未指定，则值为 [`CTEST_BINARY_DIRECTORY`](https://cmake.org/cmake/help/latest/variable/CTEST_BINARY_DIRECTORY.html#variable:CTEST_BINARY_DIRECTORY)改为使用。

- `GROUP <group>`

  如果`GROUP`使用，提交将转到 Cdash 服务器上的指定组。如果`GROUP`指定 no，则默认使用模型名称。*在 3.16 版更改:*这取代了弃用的 option `TRACK`。尽管名称更改，但其行为没有改变。

- `APPEND`

  如果`APPEND`使用，则使用现有`TAG`的，而不是基于当前时间戳创建新的。如果使用`APPEND`，则可以省略 `<model>`and参数，因为它们将从生成的文件中读取。例如：`GROUP <group>``TAG``ctest_start(Experimental GROUP GroupExperimental) `后来，在另一个脚本中：`ctest -S``ctest_start(APPEND) `当第二个脚本运行`ctest_start(APPEND)`时，它将 从第一个命令生成的文件中读取`Experimental`模型和`GroupExperimental`组。请注意，如果您调用并指定了与第一个命令不同的模型或组，则会发出警告，并且将使用新的模型和组。`TAG``ctest_start()``ctest_start(APPEND)``ctest_start()`

- `QUIET`

  *3.3 版中的新功能。*如果`QUIET`使用，CTest 将禁止任何非错误消息，否则它会打印到控制台。

的参数`ctest_start()`可以按任何顺序发出，除了`<model>`、`<source>`和`<binary>`必须以相对于彼此的顺序出现。以下都是有效和等效的：

```cmake
ctest_start(Experimental path/to/source path/to/binary GROUP SomeGroup QUIET APPEND)

ctest_start(GROUP SomeGroup Experimental QUIET path/to/source APPEND path/to/binary)

ctest_start(APPEND QUIET Experimental path/to/source GROUP SomeGroup path/to/binary)
```

但是，为了便于阅读，建议您按照本页顶部列出的顺序对参数进行排序。

如果[`CTEST_CHECKOUT_COMMAND`](https://cmake.org/cmake/help/latest/variable/CTEST_CHECKOUT_COMMAND.html#variable:CTEST_CHECKOUT_COMMAND)变量（或 [`CTEST_CVS_CHECKOUT`](https://cmake.org/cmake/help/latest/variable/CTEST_CVS_CHECKOUT.html#variable:CTEST_CVS_CHECKOUT)变量）被设置，其内容被视为命令行。调用该命令时将当前工作目录设置为源目录的父目录，即使源目录已经存在。这可用于从版本控制存储库创建源代码树。



# [ctest_submit](https://cmake.org/cmake/help/latest/command/ctest_submit.html)

作为[仪表板客户端](https://cmake.org/cmake/help/latest/manual/ctest.1.html#dashboard-client)执行[CTest 提交步骤](https://cmake.org/cmake/help/latest/manual/ctest.1.html#ctest-submit-step)。

```cmake
ctest_submit([PARTS <part>...] [FILES <file>...]
             [SUBMIT_URL <url>]
             [BUILD_ID <result-var>]
             [HTTPHEADER <header>]
             [RETRY_COUNT <count>]
             [RETRY_DELAY <delay>]
             [RETURN_VALUE <result-var>]
             [CAPTURE_CMAKE_ERROR <result-var>]
             [QUIET]
             )
```

将结果提交到仪表板服务器。默认情况下，所有可用部件都已提交。

选项包括：

- `PARTS <part>...`

  指定要提交的部分子集。有效的零件名称是：`Start      = nothing Update     = ctest_update results, in Update.xml Configure  = ctest_configure results, in Configure.xml Build      = ctest_build results, in Build.xml Test       = ctest_test results, in Test.xml Coverage   = ctest_coverage results, in Coverage.xml MemCheck   = ctest_memcheck results, in DynamicAnalysis.xml and             DynamicAnalysis-Test.xml Notes      = Files listed by CTEST_NOTES_FILES, in Notes.xml ExtraFiles = Files listed by CTEST_EXTRA_SUBMIT_FILES Upload     = Files prepared for upload by ctest_upload(), in Upload.xml Submit     = nothing Done       = Build is complete, in Done.xml `

- `FILES <file>...`

  指定要提交的特定文件的明确列表。每个单独的文件在调用时都必须存在。

- `SUBMIT_URL <url>`

  *版本 3.14 中的新功能。*将提交发送到的仪表板服务器的`http`或URL。`https`如果没有给出，则[`CTEST_SUBMIT_URL`](https://cmake.org/cmake/help/latest/variable/CTEST_SUBMIT_URL.html#variable:CTEST_SUBMIT_URL)使用变量。

- `BUILD_ID <result-var>`

  *3.15 版中的新功能。*`<result-var>`将 Cdash 分配给此构建的 ID存储在变量中。

- `HTTPHEADER <HTTP-header>`

  *3.9 版中的新功能。*指定在提交期间包含在对 Cdash 的请求中的 HTTP 标头。例如，可以将 Cdash 配置为仅接受来自经过身份验证的客户端的提交。在这种情况下，您应该在标头中提供不记名令牌：`ctest_submit(HTTPHEADER "Authorization: Bearer <auth-token>") `此子选项可以针对多个标头重复多次。

- `RETRY_COUNT <count>`

  指定重试超时提交的次数。

- `RETRY_DELAY <delay>`

  指定在超时提交后等待多长时间（以秒为单位），然后再尝试重新提交。

- `RETURN_VALUE <result-var>`

  成功存储在`<result-var>`变量`0`中，失败时存储非零。

- `CAPTURE_CMAKE_ERROR <result-var>`

  *3.13 版中的新功能。*如果运行命令有任何错误，则存储在`<result-var>`变量 -1 中，如果发生错误，则防止 ctest 返回非零值。

- `QUIET`

  *3.3 版中的新功能。*禁止所有本应打印到控制台的非错误消息。

## 提交到 Cdash 上传 API 

*3.2 版中的新功能。*

```cmake
ctest_submit(CDASH_UPLOAD <file> [CDASH_UPLOAD_TYPE <type>]
             [SUBMIT_URL <url>]
             [BUILD_ID <result-var>]
             [HTTPHEADER <header>]
             [RETRY_COUNT <count>]
             [RETRY_DELAY <delay>]
             [RETURN_VALUE <result-var>]
             [QUIET])
```

第二个签名用于通过 Cdash 文件上传 API 将文件上传到 Cdash。API 首先发送一个上传到 Cdash 的请求以及文件的内容哈希。如果 Cdash 还没有该文件，则将其上载。与该文件一起，指定了一个 CDash 类型字符串来告诉 Cdash 使用哪个处理程序来处理数据。

此签名以与第一个相同的方式解释选项。

*3.8 版中的新功能：*添加了`RETRY_COUNT`, `RETRY_DELAY`,`QUIET`选项。

*3.9 版中的新功能：*添加了该`HTTPHEADER`选项。

*3.13 版中的新功能：*添加了该`RETURN_VALUE`选项。

*3.14 版中的新功能：*添加了该`SUBMIT_URL`选项。

*3.15 新版功能：*添加了该`BUILD_ID`选项。



# [ctest_test](https://cmake.org/cmake/help/latest/command/ctest_test.html)

作为[仪表板客户端](https://cmake.org/cmake/help/latest/manual/ctest.1.html#dashboard-client)执行[CTest 测试步骤](https://cmake.org/cmake/help/latest/manual/ctest.1.html#ctest-test-step)。

```cmake
ctest_test([BUILD <build-dir>] [APPEND]
           [START <start-number>]
           [END <end-number>]
           [STRIDE <stride-number>]
           [EXCLUDE <exclude-regex>]
           [INCLUDE <include-regex>]
           [EXCLUDE_LABEL <label-exclude-regex>]
           [INCLUDE_LABEL <label-include-regex>]
           [EXCLUDE_FIXTURE <regex>]
           [EXCLUDE_FIXTURE_SETUP <regex>]
           [EXCLUDE_FIXTURE_CLEANUP <regex>]
           [PARALLEL_LEVEL <level>]
           [RESOURCE_SPEC_FILE <file>]
           [TEST_LOAD <threshold>]
           [SCHEDULE_RANDOM <ON|OFF>]
           [STOP_ON_FAILURE]
           [STOP_TIME <time-of-day>]
           [RETURN_VALUE <result-var>]
           [CAPTURE_CMAKE_ERROR <result-var>]
           [REPEAT <mode>:<n>]
           [OUTPUT_JUNIT <file>]
           [QUIET]
           )
```

在项目构建树中运行测试并将结果存储到 `Test.xml`提交中[`ctest_submit()`](https://cmake.org/cmake/help/latest/command/ctest_submit.html#command:ctest_submit)命令。

选项包括：

- `BUILD <build-dir>`

  指定顶级构建目录。如果没有给出，则 [`CTEST_BINARY_DIRECTORY`](https://cmake.org/cmake/help/latest/variable/CTEST_BINARY_DIRECTORY.html#variable:CTEST_BINARY_DIRECTORY)使用变量。

- `APPEND`

  标记`Test.xml`附加到自上次以来提交到仪表板服务器的结果[`ctest_start()`](https://cmake.org/cmake/help/latest/command/ctest_start.html#command:ctest_start)称呼。附加语义由正在使用的仪表板服务器定义。这不会*导致*将结果附加到`.xml`先前调用此命令生成的文件中。

- `START <start-number>`

  指定一系列测试编号的开头。

- `END <end-number>`

  指定测试编号范围的结尾。

- `STRIDE <stride-number>`

  指定跨过一系列测试数字的步幅。

- `EXCLUDE <exclude-regex>`

  指定匹配要排除的测试名称的正则表达式。

- `INCLUDE <include-regex>`

  指定要包含的匹配测试名称的正则表达式。不匹配此表达式的测试将被排除。

- `EXCLUDE_LABEL <label-exclude-regex>`

  指定匹配要排除的测试标签的正则表达式。

- `INCLUDE_LABEL <label-include-regex>`

  指定要包含的匹配测试标签的正则表达式。不匹配此表达式的测试将被排除。

- `EXCLUDE_FIXTURE <regex>`

  *3.7 版中的新功能。*如果要执行的测试集中的测试需要特定的夹具，则该夹具的设置和清理测试通常会自动添加到测试集中。此选项可防止为与`<regex>`. 请注意，所有其他夹具行为都将保留，包括测试依赖项和跳过具有夹具设置测试失败的测试。

- `EXCLUDE_FIXTURE_SETUP <regex>`

  *3.7 版中的新功能。*与`EXCLUDE_FIXTURE`仅排除匹配的设置测试相同。

- `EXCLUDE_FIXTURE_CLEANUP <regex>`

  *3.7 版中的新功能。*与`EXCLUDE_FIXTURE`仅排除匹配的清理测试相同。

- `PARALLEL_LEVEL <level>`

  指定一个正数，表示要并行运行的测试数。

- `RESOURCE_SPEC_FILE <file>`

  *3.16 版中的新功能。*指定 [资源规范文件](https://cmake.org/cmake/help/latest/manual/ctest.1.html#ctest-resource-specification-file)。有关详细信息，请参阅 [资源分配](https://cmake.org/cmake/help/latest/manual/ctest.1.html#ctest-resource-allocation)。

- `TEST_LOAD <threshold>`

  *3.4 版中的新功能。*在并行运行测试时，当测试可能导致 CPU 负载超过给定阈值时，尽量不要启动测试。如果没有指定[`CTEST_TEST_LOAD`](https://cmake.org/cmake/help/latest/variable/CTEST_TEST_LOAD.html#variable:CTEST_TEST_LOAD)变量将被检查，然后`--test-load`命令行参数[`ctest(1)`](https://cmake.org/cmake/help/latest/manual/ctest.1.html#manual:ctest(1)). 另请参见[CTest 测试步骤](https://cmake.org/cmake/help/latest/manual/ctest.1.html#ctest-test-step)`TestLoad`中的设置。

- `REPEAT <mode>:<n>`

  *版本 3.17 中的新功能。*根据给定`<mode>`的`<n>`时间重复运行测试。模式是：`UNTIL_FAIL`要求每个测试运行`<n>`时间且不失败才能通过。这对于发现测试用例中的零星故障很有用。`UNTIL_PASS`允许每个测试运行`<n>`多次才能通过。如果由于任何原因失败，则重复测试。这对于容忍测试用例中的零星故障很有用。`AFTER_TIMEOUT`允许每个测试运行`<n>`多次才能通过。仅在超时时重复测试。这对于容忍繁忙机器上的测试用例中的零星超时非常有用。

- `SCHEDULE_RANDOM <ON|OFF>`

  以随机顺序启动测试。这对于检测隐式测试依赖关系可能很有用。

- `STOP_ON_FAILURE`

  *3.18 版中的新功能。*一旦测试失败，停止执行测试。

- `STOP_TIME <time-of-day>`

  指定测试应全部停止运行的时间。

- `RETURN_VALUE <result-var>`

  如果所有测试都通过，则存储在`<result-var>`变量中。`0`如果出现任何问题，存储非零值。

- `CAPTURE_CMAKE_ERROR <result-var>`

  *3.7 版中的新功能。*如果运行命令有任何错误，则存储在`<result-var>`变量 -1 中，如果发生错误，则防止 ctest 返回非零值。

- `OUTPUT_JUNIT <file>`

  *3.21 版中的新功能。*`<file>`以JUnit XML 格式写入测试结果。如果`<file>`是相对路径，则将其放置在构建目录中。如果`<file>` 已经存在，它将被覆盖。请注意，生成的 JUnit XML 文件**不会**上传到 Cdash，因为它与 CTest 的`Test.xml`文件是多余的。

- `QUIET`

  *3.3 版中的新功能。*抑制任何本来会打印到控制台的 CTest 特定的非错误消息。底层测试命令的输出不受影响。详细说明通过测试百分比的摘要信息也不受该`QUIET`选项的影响。

另见[`CTEST_CUSTOM_MAXIMUM_PASSED_TEST_OUTPUT_SIZE`](https://cmake.org/cmake/help/latest/variable/CTEST_CUSTOM_MAXIMUM_PASSED_TEST_OUTPUT_SIZE.html#variable:CTEST_CUSTOM_MAXIMUM_PASSED_TEST_OUTPUT_SIZE), [`CTEST_CUSTOM_MAXIMUM_FAILED_TEST_OUTPUT_SIZE`](https://cmake.org/cmake/help/latest/variable/CTEST_CUSTOM_MAXIMUM_FAILED_TEST_OUTPUT_SIZE.html#variable:CTEST_CUSTOM_MAXIMUM_FAILED_TEST_OUTPUT_SIZE)和 [`CTEST_CUSTOM_TEST_OUTPUT_TRUNCATION`](https://cmake.org/cmake/help/latest/variable/CTEST_CUSTOM_TEST_OUTPUT_TRUNCATION.html#variable:CTEST_CUSTOM_TEST_OUTPUT_TRUNCATION)变量。



## 附加测试测量

CTest 可以解析您的测试输出以获取额外的测量结果以报告给 CDash。

当作为[Dashboard Client](https://cmake.org/cmake/help/latest/manual/ctest.1.html#dashboard-client)运行时，CTest 会将这些自定义测量值包含在`Test.xml`上传到 CDash 的文件中。

查看[CDash 测试测量文档](https://github.com/Kitware/CDash/blob/master/docs/test_measurements.md) 以获取有关 CDash 识别的测试测量类型的更多信息。

以下示例演示了如何输出各种自定义测试测量值。

```cmake
std::cout <<
  "<CTestMeasurement type=\"numeric/double\" name=\"score\">28.3</CTestMeasurement>"
  << std::endl;

std::cout <<
  "<CTestMeasurement type=\"text/string\" name=\"color\">red</CTestMeasurement>"
  << std::endl;

std::cout <<
  "<CTestMeasurement type=\"text/link\" name=\"CMake URL\">https://cmake.org</CTestMeasurement>"
  << std::endl;

std::cout <<
  "<CTestMeasurement type=\"text/preformatted\" name=\"Console Output\">" <<
  "line 1.\n" <<
  "  \033[31;1m line 2. Bold red, and indented!\033[0;0ml\n" <<
  "line 3. Not bold or indented...\n" <<
  "</CTestMeasurement>" << std::endl;
```cmake

### 图像测量

以下示例演示如何将测试图像上传到 Cdash。

```cmake
std::cout <<
  "<CTestMeasurementFile type=\"image/jpg\" name=\"TestImage\">" <<
  "/dir/to/test_img.jpg</CTestMeasurementFile>" << std::endl;

std::cout <<
  "<CTestMeasurementFile type=\"image/gif\" name=\"ValidImage\">" <<
  "/dir/to/valid_img.gif</CTestMeasurementFile>" << std::endl;

std::cout <<
  "<CTestMeasurementFile type=\"image/png\" name=\"AlgoResult\"> <<
  "/dir/to/img.png</CTestMeasurementFile>"
  << std::endl;
```

如果图像具有以下两个或多个名称，则图像将在 Cdash 上以交互式比较模式一起显示。

- `TestImage`
- `ValidImage`
- `BaselineImage`
- `DifferenceImage2`

按照惯例，`TestImage`是您的测试生成的图像，并且 `ValidImage`（或`BaselineImage`）是用于确定测试是否通过的比较基础。

如果使用了另一个图像名称，它将由 Cdash 显示为与交互式比较 UI 分开的静态图像。

### 附件

*3.21 版中的新功能。*

以下示例演示如何将非图像文件上传到 Cdash。

```cmake
std::cout <<
  "<CTestMeasurementFile type=\"file\" name=\"TestInputData1\">" <<
  "/dir/to/data1.csv</CTestMeasurementFile>\n"                   <<
  "<CTestMeasurementFile type=\"file\" name=\"TestInputData2\">" <<
  "/dir/to/data2.csv</CTestMeasurementFile>"                     << std::endl;
```

如果在配置时知道要上传的文件的名称，则可以使用 [`ATTACHED_FILES`](https://cmake.org/cmake/help/latest/prop_test/ATTACHED_FILES.html#prop_test:ATTACHED_FILES)或者[`ATTACHED_FILES_ON_FAIL`](https://cmake.org/cmake/help/latest/prop_test/ATTACHED_FILES_ON_FAIL.html#prop_test:ATTACHED_FILES_ON_FAIL)而是测试属性。

### 自定义细节

*3.21 版中的新功能。*

以下示例演示了如何为 Cdash 上显示的字段指定自定义值。`Test Details`

```cmake
std::cout <<
  "<CTestDetails>My Custom Details Value</CTestDetails>" << std::endl;
```cmake



### 附加标签

*版本 3.22 中的新功能。*

以下示例演示了如何在运行时向测试添加其他标签。

```cmake
std::cout <<
  "<CTestLabel>Custom Label 1</CTestLabel>\n" <<
  "<CTestLabel>Custom Label 2</CTestLabel>"   << std::endl;
```

使用[`LABELS`](https://cmake.org/cmake/help/latest/prop_test/LABELS.html#prop_test:LABELS)测试属性，而不是可以在配置时确定的标签。



# [ctest_update](https://cmake.org/cmake/help/latest/command/ctest_update.html)

作为[仪表板客户端](https://cmake.org/cmake/help/latest/manual/ctest.1.html#dashboard-client)执行[CTest 更新步骤](https://cmake.org/cmake/help/latest/manual/ctest.1.html#ctest-update-step)。

```cmake
ctest_update([SOURCE <source-dir>]
             [RETURN_VALUE <result-var>]
             [CAPTURE_CMAKE_ERROR <result-var>]
             [QUIET])
```

从版本控制更新源代码树并记录结果以 `Update.xml`用于提交[`ctest_submit()`](https://cmake.org/cmake/help/latest/command/ctest_submit.html#command:ctest_submit)命令。

选项包括：

- `SOURCE <source-dir>`

  指定源目录。如果没有给出，则 [`CTEST_SOURCE_DIRECTORY`](https://cmake.org/cmake/help/latest/variable/CTEST_SOURCE_DIRECTORY.html#variable:CTEST_SOURCE_DIRECTORY)使用变量。

- `RETURN_VALUE <result-var>`

  将更新或出错的文件数存储在`<result-var>`变量中。`-1`

- `CAPTURE_CMAKE_ERROR <result-var>`

  *3.13 版中的新功能。*如果运行命令有任何错误，则存储在`<result-var>`变量 -1 中，如果发生错误，则防止 ctest 返回非零值。

- `QUIET`

  *3.3 版中的新功能。*告诉 CTest 禁止它本来会打印到控制台的大多数非错误消息。CTest 仍将报告存储库的新修订版以及找到的任何冲突文件。

更新始终遵循当前在源目录中签出的版本控制分支。有关[更改](https://cmake.org/cmake/help/latest/manual/ctest.1.html#ctest-update-step)`ctest_update()`. _



# [ctest_upload](https://cmake.org/cmake/help/latest/command/ctest_upload.html)

将文件作为[仪表板客户端](https://cmake.org/cmake/help/latest/manual/ctest.1.html#dashboard-client)上传到仪表板服务器。

```cmake
ctest_upload(FILES <file>... [QUIET] [CAPTURE_CMAKE_ERROR <result-var>])
```

选项包括：

- `FILES <file>...`

  指定要与构建结果一起发送到仪表板服务器的文件列表。

- `QUIET`

  *3.3 版中的新功能。*抑制任何本来会打印到控制台的 CTest 特定的非错误输出。

- `CAPTURE_CMAKE_ERROR <result-var>`

  *3.7 版中的新功能。*如果运行命令有任何错误，则存储在`<result-var>`变量 -1 中，如果发生错误，则防止 ctest 返回非零值。
