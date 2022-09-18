# [cmake-file-api(7) ](https://cmake.org/cmake/help/latest/manual/cmake-file-api.7.html#id1)

内容

- [cmake-file-api(7)](https://cmake.org/cmake/help/latest/manual/cmake-file-api.7.html#cmake-file-api-7)
  - [介绍](https://cmake.org/cmake/help/latest/manual/cmake-file-api.7.html#introduction)
  - [API v1](https://cmake.org/cmake/help/latest/manual/cmake-file-api.7.html#api-v1)
    - [v1 共享无状态查询文件](https://cmake.org/cmake/help/latest/manual/cmake-file-api.7.html#v1-shared-stateless-query-files)
    - [v1 客户端无状态查询文件](https://cmake.org/cmake/help/latest/manual/cmake-file-api.7.html#v1-client-stateless-query-files)
    - [v1 客户端状态查询文件](https://cmake.org/cmake/help/latest/manual/cmake-file-api.7.html#v1-client-stateful-query-files)
    - [v1 回复索引文件](https://cmake.org/cmake/help/latest/manual/cmake-file-api.7.html#v1-reply-index-file)
      - [v1 回复文件参考](https://cmake.org/cmake/help/latest/manual/cmake-file-api.7.html#v1-reply-file-reference)
    - [v1 回复文件](https://cmake.org/cmake/help/latest/manual/cmake-file-api.7.html#v1-reply-files)
  - [对象种类](https://cmake.org/cmake/help/latest/manual/cmake-file-api.7.html#object-kinds)
    - [对象种类“代码模型”](https://cmake.org/cmake/help/latest/manual/cmake-file-api.7.html#object-kind-codemodel)
      - [“代码模型”版本 2](https://cmake.org/cmake/help/latest/manual/cmake-file-api.7.html#codemodel-version-2)
      - [“codemodel”版本 2 “目录”对象](https://cmake.org/cmake/help/latest/manual/cmake-file-api.7.html#codemodel-version-2-directory-object)
      - [“codemodel”版本 2 “目标”对象](https://cmake.org/cmake/help/latest/manual/cmake-file-api.7.html#codemodel-version-2-target-object)
      - [“codemodel”版本 2 “回溯图”](https://cmake.org/cmake/help/latest/manual/cmake-file-api.7.html#codemodel-version-2-backtrace-graph)
    - [对象种类“缓存”](https://cmake.org/cmake/help/latest/manual/cmake-file-api.7.html#object-kind-cache)
      - [“缓存”版本 2](https://cmake.org/cmake/help/latest/manual/cmake-file-api.7.html#cache-version-2)
    - [对象种类“cmakeFiles”](https://cmake.org/cmake/help/latest/manual/cmake-file-api.7.html#object-kind-cmakefiles)
      - [“cmakeFiles”版本 1](https://cmake.org/cmake/help/latest/manual/cmake-file-api.7.html#cmakefiles-version-1)
    - [对象种类“工具链”](https://cmake.org/cmake/help/latest/manual/cmake-file-api.7.html#object-kind-toolchains)
      - [“工具链”版本 1](https://cmake.org/cmake/help/latest/manual/cmake-file-api.7.html#toolchains-version-1)

## [Introduction](https://cmake.org/cmake/help/latest/manual/cmake-file-api.7.html#id2)

CMake 提供了一个基于文件的 API，客户端可以使用它来获取有关 CMake 生成的构建系统的语义信息。客户端可以通过将查询文件写入构建树中的特定位置来使用 API，以请求零个或多个[Object Kinds](https://cmake.org/cmake/help/latest/manual/cmake-file-api.7.html#object-kinds)。当 CMake 在该构建树中生成构建系统时，它将读取查询文件并写入回复文件以供客户端读取。

基于文件的 API 使用`<build>/.cmake/api/`构建树顶部的目录。API 版本化以支持对 API 目录中文件布局的更改。API 文件布局版本控制与回复中使用的[对象种类](https://cmake.org/cmake/help/latest/manual/cmake-file-api.7.html#object-kinds)的版本控制正交。此版本的 CMake 仅支持一个 API 版本[API v1](https://cmake.org/cmake/help/latest/manual/cmake-file-api.7.html#api-v1)。

## [API v1 ](https://cmake.org/cmake/help/latest/manual/cmake-file-api.7.html#id3)

API v1 位于该`<build>/.cmake/api/v1/`目录中。它有以下子目录：

- `query/`

  保存客户端编写的查询文件。这些可能是[v1 共享无状态查询文件](https://cmake.org/cmake/help/latest/manual/cmake-file-api.7.html#v1-shared-stateless-query-files)、 [v1 客户端无状态查询文件](https://cmake.org/cmake/help/latest/manual/cmake-file-api.7.html#v1-client-stateless-query-files)或[v1 客户端有状态查询文件](https://cmake.org/cmake/help/latest/manual/cmake-file-api.7.html#v1-client-stateful-query-files)。

- `reply/`

  保存由 CMake 编写的回复文件，只要它运行以生成构建系统。这些由[v1 回复索引文件](https://cmake.org/cmake/help/latest/manual/cmake-file-api.7.html#v1-reply-index-file)文件索引，该文件可能引用其他[v1 回复文件](https://cmake.org/cmake/help/latest/manual/cmake-file-api.7.html#v1-reply-files)。CMake 拥有所有回复文件。客户绝不能删除它们。客户可以随时查找和阅读回复索引文件。`reply/`客户端可以随时选择创建目录并监视它是否出现新的回复索引文件。

### [v1 共享无状态查询文件](https://cmake.org/cmake/help/latest/manual/cmake-file-api.7.html#id4)

共享的无状态查询文件允许客户端共享[对象种类](https://cmake.org/cmake/help/latest/manual/cmake-file-api.7.html#object-kinds)的主要版本的请求，并获得运行的 CMake 识别的所有请求版本。

`v1/query/`客户端可以通过在目录中创建空文件来创建共享请求 。表格是：

```
<build>/.cmake/api/v1/query/<kind>-v<major>
```

其中`<kind>`是[Object Kinds](https://cmake.org/cmake/help/latest/manual/cmake-file-api.7.html#object-kinds)之一，`-v`是字面量，`<major>`是主要版本号。

这种形式的文件是不属于任何特定客户的无状态共享查询。一旦创建，它们不应在没有外部客户协调或人工干预的情况下被删除。

### [v1 客户端无状态查询文件](https://cmake.org/cmake/help/latest/manual/cmake-file-api.7.html#id5)

[客户端无状态查询文件允许客户端为对象种类](https://cmake.org/cmake/help/latest/manual/cmake-file-api.7.html#object-kinds)的主要版本创建拥有的请求，并获取运行的 CMake 识别的所有请求版本。

客户端可以通过在特定于客户端的查询子目录中创建空文件来创建拥有的请求。表格是：

```
<build>/.cmake/api/v1/query/client-<client>/<kind>-v<major>
```

其中`client-`是文字，`<client>`是唯一标识客户端的字符串，`<kind>`是[Object Kinds](https://cmake.org/cmake/help/latest/manual/cmake-file-api.7.html#object-kinds)之一， `-v`是文字，`<major>`是主要版本号。每个客户都必须`<client>`通过自己的方式选择一个唯一的标识符。

这种形式的文件是客户拥有的无状态查询`<client>`。拥有的客户可以随时删除它们。

### [v1 客户端状态查询文件](https://cmake.org/cmake/help/latest/manual/cmake-file-api.7.html#id6)

有状态查询文件允许客户端请求每个[对象种类](https://cmake.org/cmake/help/latest/manual/cmake-file-api.7.html#object-kinds)的版本列表，并仅获取运行的 CMake 识别的最新版本。

`query.json` 客户端可以通过在特定于客户端的查询子目录中创建文件来创建拥有的有状态查询。表格是：

```
<build>/.cmake/api/v1/query/client-<client>/query.json
```

其中`client-`是文字，`<client>`是唯一标识客户端的字符串，并且`query.json`是文字。每个客户都必须`<client>`通过自己的方式选择一个唯一的标识符。

`query.json`文件是客户端拥有的有状态查询`<client>`。拥有的客户端可以随时更新或删除它们。当给定客户端安装更新时，它可能会更新它写入的有状态查询以构建树以请求更新的对象版本。这可用于避免要求 CMake 不必要地生成多个对象版本。

文件`query.json`必须包含 JSON 对象：

```
{
  "requests": [
    { "kind": "<kind>" , "version": 1 },
    { "kind": "<kind>" , "version": { "major": 1, "minor": 2 } },
    { "kind": "<kind>" , "version": [2, 1] },
    { "kind": "<kind>" , "version": [2, { "major": 1, "minor": 2 }] },
    { "kind": "<kind>" , "version": 1, "client": {} },
    { "kind": "..." }
  ],
  "client": {}
}
```

成员是：

- `requests`

  包含零个或多个请求的 JSON 数组。每个请求都是一个带有成员的 JSON 对象：`kind`指定要包含在回复中的[对象种类之一。](https://cmake.org/cmake/help/latest/manual/cmake-file-api.7.html#object-kinds)`version`指示客户端理解的对象类型的版本。版本具有遵循语义版本约定的主要和次要组件。值必须是指定（非负）主要版本号的 JSON 整数，或一个 JSON 对象，包含`major`和（可选）`minor` 指定非负整数版本组件的成员，或一个 JSON 数组，其元素是上述每个元素。`client`保留供客户使用的可选成员。此值保留在 [v1 回复索引文件](https://cmake.org/cmake/help/latest/manual/cmake-file-api.7.html#v1-reply-index-file)中为客户端编写的回复中，否则将被忽略。客户可以使用它来将自定义信息与请求一起传递给其回复。对于每个请求的对象类型，CMake 将在请求中列出的那些类型中选择它识别的*第一个版本。*响应将使用所选的*主要*版本以及该主要版本的运行 CMake 已知的最高 *次要*版本。因此，客户应按首选顺序列出所有受支持的主要版本以及每个主要版本所需的最小次要版本。

- `client`

  保留供客户使用的可选成员。此值保留在 [v1 回复索引文件](https://cmake.org/cmake/help/latest/manual/cmake-file-api.7.html#v1-reply-index-file)中为客户端编写的回复中，否则将被忽略。客户可以使用它通过查询将自定义信息传递给其回复。

其他`query.json`顶级成员保留供将来使用。如果存在，它们将被忽略以实现前向兼容性。

### [v1 回复索引文件](https://cmake.org/cmake/help/latest/manual/cmake-file-api.7.html#id7)

CMake每次运行时都会将`index-*.json`文件写入`v1/reply/`目录以生成构建系统。客户端必须先读取回复索引文件，并且只能通过以下引用读取其他[v1 回复文件。](https://cmake.org/cmake/help/latest/manual/cmake-file-api.7.html#v1-reply-files)回复索引文件名的格式为：

```
<build>/.cmake/api/v1/reply/index-<unspecified>.json
```

where`index-`是文字，`<unspecified>`是 CMake 选择的未指定名称。每当生成一个新的索引文件时，它都会被赋予一个新的名称，并且任何旧的都会被删除。在这些步骤之间的短时间内，可能存在多个索引文件；在字典顺序中名称最大的一个是当前索引文件。

回复索引文件包含一个 JSON 对象：

```
{
  "cmake": {
    "version": {
      "major": 3, "minor": 14, "patch": 0, "suffix": "",
      "string": "3.14.0", "isDirty": false
    },
    "paths": {
      "cmake": "/prefix/bin/cmake",
      "ctest": "/prefix/bin/ctest",
      "cpack": "/prefix/bin/cpack",
      "root": "/prefix/share/cmake-3.14"
    },
    "generator": {
      "multiConfig": false,
      "name": "Unix Makefiles"
    }
  },
  "objects": [
    { "kind": "<kind>",
      "version": { "major": 1, "minor": 0 },
      "jsonFile": "<file>" },
    { "...": "..." }
  ],
  "reply": {
    "<kind>-v<major>": { "kind": "<kind>",
                         "version": { "major": 1, "minor": 0 },
                         "jsonFile": "<file>" },
    "<unknown>": { "error": "unknown query file" },
    "...": {},
    "client-<client>": {
      "<kind>-v<major>": { "kind": "<kind>",
                           "version": { "major": 1, "minor": 0 },
                           "jsonFile": "<file>" },
      "<unknown>": { "error": "unknown query file" },
      "...": {},
      "query.json": {
        "requests": [ {}, {}, {} ],
        "responses": [
          { "kind": "<kind>",
            "version": { "major": 1, "minor": 0 },
            "jsonFile": "<file>" },
          { "error": "unknown query file" },
          { "...": {} }
        ],
        "client": {}
      }
    }
  }
}
```

成员是：

- `cmake`

  一个 JSON 对象，其中包含有关生成回复的 CMake 实例的信息。它包含成员：`version`一个 JSON 对象，指定带有成员的 CMake 版本：`major`, `minor`, `patch`指定主要、次要和补丁版本组件的整数值。`suffix`指定版本后缀（如果有）的字符串，例如`g0abc3`.`string`指定格式的完整版本的字符串 `<major>.<minor>.<patch>[-<suffix>]`。`isDirty`一个布尔值，指示版本是否是从具有本地修改的版本控制源树构建的。`paths`一个 JSON 对象，指定 CMake 附带的东西的路径。它有成员 for `cmake`, `ctest`, 并且`cpack`其值是 JSON 字符串，指定每个工具的绝对路径，用正斜杠表示。它还有一个`root`成员，用于包含 CMake 资源（如 `Modules/`目录）的目录的绝对路径（请参阅[`CMAKE_ROOT`](https://cmake.org/cmake/help/latest/variable/CMAKE_ROOT.html#variable:CMAKE_ROOT)).`generator`描述用于构建的 CMake 生成器的 JSON 对象。它有成员：`multiConfig`一个布尔值，指定生成器是否支持多种输出配置。`name`指定生成器名称的字符串。`platform`如果生成器支持[`CMAKE_GENERATOR_PLATFORM`](https://cmake.org/cmake/help/latest/variable/CMAKE_GENERATOR_PLATFORM.html#variable:CMAKE_GENERATOR_PLATFORM)，这是一个指定生成器平台名称的字符串。

- `objects`

  一个 JSON 数组，列出作为回复的一部分生成的所有[对象种类的所有版本。](https://cmake.org/cmake/help/latest/manual/cmake-file-api.7.html#object-kinds)每个数组条目都是一个 [v1 回复文件参考](https://cmake.org/cmake/help/latest/manual/cmake-file-api.7.html#v1-reply-file-reference)。

- `reply`

  一个 JSON 对象，镜像`query/`CMake 加载以生成回复的目录内容。成员的形式为`<kind>-v<major>`对于 CMake 识别为对具有主要版本的对象类型的请求的每个[v1 共享无状态查询文件](https://cmake.org/cmake/help/latest/manual/cmake-file-api.7.html#v1-shared-stateless-query-files)，都会出现此表单的成员 。该值是对该对象种类和版本的相应回复文件的[v1 回复文件引用。](https://cmake.org/cmake/help/latest/manual/cmake-file-api.7.html#v1-reply-file-reference)`<kind>``<major>``<unknown>`对于CMake 无法识别的每个[v1 共享无状态查询文件](https://cmake.org/cmake/help/latest/manual/cmake-file-api.7.html#v1-shared-stateless-query-files)，都会出现此表单的成员 。该值是一个 JSON 对象，其中包含一个包含错误消息的字符串的单个`error`成员，该字符串指示查询文件未知。`client-<client>`对于每个持有[v1 Client Stateless Query Files](https://cmake.org/cmake/help/latest/manual/cmake-file-api.7.html#v1-client-stateless-query-files)的客户拥有的目录，都会出现一个此表单的成员。该值是一个镜像 `query/client-<client>/`目录内容的 JSON 对象。成员的形式为：`<kind>-v<major>`对于 CMake 识别为对具有主要版本的对象类型的请求的每个[v1 客户端无状态查询文件](https://cmake.org/cmake/help/latest/manual/cmake-file-api.7.html#v1-client-stateless-query-files)，都会出现此表单的成员 。该值是对该对象种类和版本的相应回复文件的[v1 回复文件引用。](https://cmake.org/cmake/help/latest/manual/cmake-file-api.7.html#v1-reply-file-reference)`<kind>``<major>``<unknown>`对于CMake 无法识别的每个[v1 客户端无状态查询文件](https://cmake.org/cmake/help/latest/manual/cmake-file-api.7.html#v1-client-stateless-query-files)，都会出现此表单的成员 。该值是一个 JSON 对象，其中包含一个包含错误消息的字符串的单个`error`成员，该字符串指示查询文件未知。`query.json`该成员针对使用 [v1 Client Stateful Query Files](https://cmake.org/cmake/help/latest/manual/cmake-file-api.7.html#v1-client-stateful-query-files)的客户端显示。如果`query.json`文件无法读取或解析为 JSON 对象，则此成员是一个 JSON 对象，其中`error`包含一个包含错误消息的字符串的单个成员。否则，此成员是镜像`query.json`文件内容的 JSON 对象。成员是：`client``query.json`文件成员的副本（`client`如果存在）。`requests``query.json`文件成员的副本（`requests`如果存在）。`responses`如果`query.json`文件成员丢失或无效，则此成员是一个 JSON 对象，其中包含一个包含错误消息的字符串`requests`的单个成员。`error`否则，此成员包含一个 JSON 数组，该 `requests`数组以相同的顺序对数组的每个条目进行响应。每个响应都是具有单个`error`成员的 JSON 对象，其中包含带有错误消息的字符串，或[v1 回复文件](https://cmake.org/cmake/help/latest/manual/cmake-file-api.7.html#v1-reply-file-reference)对请求的对象种类和所选版本的相应回复文件的引用。

读取回复索引文件后，客户端可以读取 它引用的其他[v1 回复文件。](https://cmake.org/cmake/help/latest/manual/cmake-file-api.7.html#v1-reply-files)

#### [v1 回复文件参考](https://cmake.org/cmake/help/latest/manual/cmake-file-api.7.html#id8)

回复索引文件使用带有成员的 JSON 对象表示对另一个回复文件的每个引用：

- `kind`

  [指定对象种类](https://cmake.org/cmake/help/latest/manual/cmake-file-api.7.html#object-kinds)之一的字符串。

- `version`

  具有成员`major`并`minor`指定对象类型的整数版本组件的 JSON 对象。

- `jsonFile`

  一个 JSON 字符串，指定相对于回复索引文件到包含该对象的另一个 JSON 文件的路径。

### [v1 回复文件](https://cmake.org/cmake/help/latest/manual/cmake-file-api.7.html#id9)

[包含特定对象种类](https://cmake.org/cmake/help/latest/manual/cmake-file-api.7.html#object-kinds)的回复文件由 CMake 编写。这些文件的名称未指定，客户端不得解释。客户端必须首先阅读[v1 回复索引文件](https://cmake.org/cmake/help/latest/manual/cmake-file-api.7.html#v1-reply-index-file)，并遵循对所需响应对象名称的引用。

回复文件（包括索引文件）永远不会被同名但内容不同的文件替换。这允许客户端与正在运行的 CMake 同时读取文件，这可能会生成新的回复。但是，在生成新的回复后，CMake 将尝试从以前的运行中删除它不只是写入的回复文件。如果客户端尝试读取索引引用的回复文件但发现文件丢失，则意味着并发 CMake 已生成新回复。客户端可以简单地通过读取新的回复索引文件重新开始。



## [对象种类](https://cmake.org/cmake/help/latest/manual/cmake-file-api.7.html#id10)

基于 CMake 文件的 API 使用以下类型的 JSON 对象报告有关构建系统的语义信息。每种对象都使用带有主要和次要组件的语义版本控制来独立进行版本控制。每种对象都有以下形式：

```
{
  "kind": "<kind>",
  "version": { "major": 1, "minor": 0 },
  "...": {}
}
```

该`kind`成员是指定对象种类名称的字符串。该`version`成员是一个 JSON 对象，`major`其`minor` 成员指定对象种类版本的整数组件。其他顶级成员特定于每种对象类型。

### [对象类型“代码模型” ](https://cmake.org/cmake/help/latest/manual/cmake-file-api.7.html#id11)

`codemodel`对象类型描述了由 CMake 建模的构建系统结构。

只有一个`codemodel`对象主要版本，版本 2。版本 1 不存在以避免与来自 [`cmake-server(7)`](https://cmake.org/cmake/help/latest/manual/cmake-server.7.html#manual:cmake-server(7))模式。

#### [“代码模型”版本 2 ](https://cmake.org/cmake/help/latest/manual/cmake-file-api.7.html#id12)

`codemodel`对象版本 2 是一个 JSON 对象：

```
{
  "kind": "codemodel",
  "version": { "major": 2, "minor": 4 },
  "paths": {
    "source": "/path/to/top-level-source-dir",
    "build": "/path/to/top-level-build-dir"
  },
  "configurations": [
    {
      "name": "Debug",
      "directories": [
        {
          "source": ".",
          "build": ".",
          "childIndexes": [ 1 ],
          "projectIndex": 0,
          "targetIndexes": [ 0 ],
          "hasInstallRule": true,
          "minimumCMakeVersion": {
            "string": "3.14"
          },
          "jsonFile": "<file>"
        },
        {
          "source": "sub",
          "build": "sub",
          "parentIndex": 0,
          "projectIndex": 0,
          "targetIndexes": [ 1 ],
          "minimumCMakeVersion": {
            "string": "3.14"
          },
          "jsonFile": "<file>"
        }
      ],
      "projects": [
        {
          "name": "MyProject",
          "directoryIndexes": [ 0, 1 ],
          "targetIndexes": [ 0, 1 ]
        }
      ],
      "targets": [
        {
          "name": "MyExecutable",
          "directoryIndex": 0,
          "projectIndex": 0,
          "jsonFile": "<file>"
        },
        {
          "name": "MyLibrary",
          "directoryIndex": 1,
          "projectIndex": 0,
          "jsonFile": "<file>"
        }
      ]
    }
  ]
}
```

特定于`codemodel`对象的成员是：

- `paths`

  包含成员的 JSON 对象：`source`一个字符串，指定顶级源目录的绝对路径，用正斜杠表示。`build`一个字符串，指定顶级构建目录的绝对路径，用正斜杠表示。

- `configurations`

  对应于可用构建配置的 JSON 条目数组。在单一配置的生成器上，有一个条目的值[`CMAKE_BUILD_TYPE`](https://cmake.org/cmake/help/latest/variable/CMAKE_BUILD_TYPE.html#variable:CMAKE_BUILD_TYPE)多变的。对于多配置生成器，列表中列出的每个配置都有一个条目 [`CMAKE_CONFIGURATION_TYPES`](https://cmake.org/cmake/help/latest/variable/CMAKE_CONFIGURATION_TYPES.html#variable:CMAKE_CONFIGURATION_TYPES)多变的。每个条目都是一个包含成员的 JSON 对象：`name`指定配置名称的字符串，例如`Debug`.`directories`一个 JSON 条目数组，每个条目对应于一个构建系统目录，其源目录包含一个`CMakeLists.txt`文件。第一个条目对应于顶级目录。每个条目都是一个包含成员的 JSON 对象：`source`一个字符串，指定源目录的路径，用正斜杠表示。如果目录在顶级源目录中，则路径是相对于该目录指定的（与`.`顶级源目录本身）。否则路径是绝对的。`build`一个字符串，指定构建目录的路径，用正斜杠表示。如果该目录位于顶级构建目录中，则路径是相对于该目录指定的（`.`用于顶级构建目录本身）。否则路径是绝对的。`parentIndex`当目录不是顶级目录时存在的可选成员。该值是主`directories`数组中另一个条目的基于 0 的无符号整数索引，该索引对应于添加此目录作为子目录的父目录。`childIndexes`当目录有子目录时存在的可选成员。该值是对应于由[`add_subdirectory()`](https://cmake.org/cmake/help/latest/command/add_subdirectory.html#command:add_subdirectory)或者[`subdirs()`](https://cmake.org/cmake/help/latest/command/subdirs.html#command:subdirs) 命令。每个条目都是主`directories`数组中另一个条目的基于 0 的无符号整数索引。`projectIndex`主`projects`数组中基于 0 的无符号整数索引，指示此目录所属的构建系统项目。`targetIndexes`当目录本身具有目标时存在的可选成员，不包括属于子目录的目标。该值是与目标对应的条目的 JSON 数组。每个条目都是主`targets`数组中基于 0 的无符号整数索引。`minimumCMakeVersion`当知道该目录所需的最低 CMake 版本时，可选成员存在。这是`<min>`提供给最本地调用的版本[`cmake_minimum_required(VERSION)`](https://cmake.org/cmake/help/latest/command/cmake_minimum_required.html#command:cmake_minimum_required) 命令在目录本身或其祖先之一。该值是一个具有一个成员的 JSON 对象：`string`指定最低要求版本的字符串，格式为：`<major>.<minor>[.<patch>[.<tweak>]][<suffix>] `每个组件都是一个无符号整数，后缀可以是任意字符串。`hasInstallRule``true`当目录或其子目录之一包含 任何[`install()`](https://cmake.org/cmake/help/latest/command/install.html#command:install)规则，即是否有 可用的规则或等效规则。`make install``jsonFile`一个 JSON 字符串，指定相对于 codemodel 文件的路径，指向另一个包含 [“codemodel”版本 2“目录”对象](https://cmake.org/cmake/help/latest/manual/cmake-file-api.7.html#codemodel-version-2-directory-object)的 JSON 文件。此字段是在 codemodel 2.3 版中添加的。`projects`对应于构建系统中定义的顶级项目和子项目的 JSON 条目数组。每个（子）项目对应一个源目录，其`CMakeLists.txt`文件调用[`project()`](https://cmake.org/cmake/help/latest/command/project.html#command:project)项目名称与其父目录不同的命令。第一个条目对应于顶级项目。每个条目都是一个包含成员的 JSON 对象：`name`一个字符串，指定给定的名称[`project()`](https://cmake.org/cmake/help/latest/command/project.html#command:project)命令。`parentIndex`当项目不是顶级时存在的可选成员。该值是主`projects`数组中另一个条目的基于 0 的无符号整数索引，该条目对应于添加此项目作为子项目的父项目。`childIndexes`当项目有子项目时存在的可选成员。该值是对应于子项目的条目的 JSON 数组。每个条目都是主`projects`数组中另一个条目的基于 0 的无符号整数索引。`directoryIndexes`对应于作为项目一部分的构建系统目录的 JSON 条目数组。第一个条目对应于项目的顶级目录。每个条目都是主`directories`数组中基于 0 的无符号整数索引。`targetIndexes`当项目本身有目标时出现的可选成员，不包括属于子项目的那些。该值是与目标对应的条目的 JSON 数组。每个条目都是主`targets`数组中基于 0 的无符号整数索引。`targets`对应于构建系统目标的 JSON 条目数组。这样的目标是通过调用创建的[`add_executable()`](https://cmake.org/cmake/help/latest/command/add_executable.html#command:add_executable), [`add_library()`](https://cmake.org/cmake/help/latest/command/add_library.html#command:add_library)， 和[`add_custom_target()`](https://cmake.org/cmake/help/latest/command/add_custom_target.html#command:add_custom_target)，不包括导入的目标和接口库（不生成任何构建规则）。每个条目都是一个包含成员的 JSON 对象：`name`指定目标名称的字符串。`id`唯一标识目标的字符串。这与.`id` 引用的文件中的字段匹配`jsonFile`。`directoryIndex`主`directories`数组中基于 0 的无符号整数索引，指示定义目标的构建系统目录。`projectIndex`主`projects`数组中基于 0 的无符号整数索引，指示定义目标的构建系统项目。`jsonFile`一个 JSON 字符串，指定相对于 codemodel 文件到另一个 JSON 文件的路径，该文件包含 [“codemodel”版本 2“target”对象](https://cmake.org/cmake/help/latest/manual/cmake-file-api.7.html#codemodel-version-2-target-object)。

#### [“codemodel” 版本 2 “目录” 对象](https://cmake.org/cmake/help/latest/manual/cmake-file-api.7.html#id13)

代码模型“目录”对象由[“代码模型”版本 2](https://cmake.org/cmake/help/latest/manual/cmake-file-api.7.html#codemodel-version-2) 对象的`directories`数组引用。每个“目录”对象都是一个带有成员的 JSON 对象：

- `paths`

  包含成员的 JSON 对象：`source`一个字符串，指定源目录的路径，用正斜杠表示。如果目录在顶级源目录中，则路径是相对于该目录指定的（与`.`顶级源目录本身）。否则路径是绝对的。`build`一个字符串，指定构建目录的路径，用正斜杠表示。如果该目录位于顶级构建目录中，则路径是相对于该目录指定的（`.`用于顶级构建目录本身）。否则路径是绝对的。

- `installers`

  对应于的条目的 JSON 数组[`install()`](https://cmake.org/cmake/help/latest/command/install.html#command:install)规则。每个条目都是一个包含成员的 JSON 对象：`component`一个字符串，指定相应选择的组件 [`install()`](https://cmake.org/cmake/help/latest/command/install.html#command:install)命令调用。`destination``type`以下特定值存在的可选成员。该值是指定安装目标路径的字符串。该路径可以是绝对的或相对于安装前缀的。`paths``type`以下特定值存在的可选成员。该值是对应于要安装的路径（文件或目录）的条目的 JSON 数组。每个条目是以下之一：一个字符串，指定安装文件或目录的路径。前面没有 a 的路径部分`/`还指定了文件或目录要安装到目标下的路径（名称）。具有成员的 JSON 对象：`from`一个字符串，指定安装文件或目录的路径。`to`一个字符串，指定文件或目录要安装到目标下的路径。在这两种情况下，路径都用正斜杠表示。如果“from”路径位于相应值记录的顶级目录中`type`，则路径是相对于该目录指定的。否则路径是绝对的。`type`指定安装规则类型的字符串。该值是以下之一，一些变体提供额外的成员：`file`一个[`install(FILES)`](https://cmake.org/cmake/help/latest/command/install.html#command:install)或者[`install(PROGRAMS)`](https://cmake.org/cmake/help/latest/command/install.html#command:install)称呼。`destination`和`paths`成员被填充，顶级*源*目录下的路径表示相对于它。该`isOptional`成员可能存在。此类型没有其他成员。`directory`一个[`install(DIRECTORY)`](https://cmake.org/cmake/help/latest/command/install.html#command:install)称呼。`destination`和`paths`成员被填充，顶级*源*目录下的路径表示相对于它。该`isOptional`成员可能存在。此类型没有其他成员。`target`一个[`install(TARGETS)`](https://cmake.org/cmake/help/latest/command/install.html#command:install)称呼。`destination`和`paths`成员被填充，顶级*构建*目录下的路径表示相对于它。该`isOptional`成员可能存在。此类型具有附加成员`targetId`、`targetIndex`、 `targetIsImportLibrary`和`targetInstallNamelink`。`export`一个[`install(EXPORT)`](https://cmake.org/cmake/help/latest/command/install.html#command:install)称呼。`destination`和`paths`成员被填充，顶级*构建*目录下的路径表示相对于它。这些`paths`条目是指由 CMake 自动生成的用于安装的文件，它们的实际值被认为是私有实现细节。这种类型有额外的成员`exportName`和`exportTargets`。`script`一个[`install(SCRIPT)`](https://cmake.org/cmake/help/latest/command/install.html#command:install)称呼。这种类型有额外的成员`scriptFile`。`code`一个[`install(CODE)`](https://cmake.org/cmake/help/latest/command/install.html#command:install)称呼。此类型没有其他成员。`importedRuntimeArtifacts`一个[`install(IMPORTED_RUNTIME_ARTIFACTS)`](https://cmake.org/cmake/help/latest/command/install.html#command:install)称呼。该`destination`成员已填充。该`isOptional`成员可能存在。此类型没有其他成员。`runtimeDependencySet`一个[`install(RUNTIME_DEPENDENCY_SET)`](https://cmake.org/cmake/help/latest/command/install.html#command:install)打电话或 [`install(TARGETS)`](https://cmake.org/cmake/help/latest/command/install.html#command:install)用 调用`RUNTIME_DEPENDENCIES`。该 `destination`成员已填充。这种类型有额外的成员 `runtimeDependencySetName`和`runtimeDependencySetType`。`fileSet`一个[`install(TARGETS)`](https://cmake.org/cmake/help/latest/command/install.html#command:install)用 调用`FILE_SET`。和`destination`成员`paths`已填充。该`isOptional`成员可能存在。此类型具有附加成员`fileSetName`、`fileSetType`、 `fileSetDirectories`和`fileSetTarget`。此类型是在 codemodel 版本 2.4 中添加的。`isExcludeFromAll`以布尔值存在的可选`true`成员 [`install()`](https://cmake.org/cmake/help/latest/command/install.html#command:install)`EXCLUDE_FROM_ALL`使用选项调用。`isForAllComponents`以布尔值存在的可选`true`成员 [`install(SCRIPT|CODE)`](https://cmake.org/cmake/help/latest/command/install.html#command:install)`ALL_COMPONENTS`使用选项调用 。`isOptional`以布尔值存在的可选`true`成员 [`install()`](https://cmake.org/cmake/help/latest/command/install.html#command:install)`OPTIONAL`使用选项调用。`type`当is `file`、`directory`或时，这是允许的`target`。`targetId``type`是时存在的可选成员`target`。该值是唯一标识要安装的目标的字符串。这与`id`主“codemodel”对象`targets`数组中的目标成员匹配。`targetIndex``type`是时存在的可选成员`target`。`targets`该值是要安装的目标的主“codemodel”对象数组的基于 0 的无符号整数索引。`targetIsImportLibrary``type`存在的可选成员，`target`并且安装程序用于 Windows DLL 导入库文件或 AIX 链接器导入文件。如果存在，它具有布尔值`true`。`targetInstallNamelink``type`存在的可选成员，`target`并且安装程序对应于可以使用符号链接来实现的目标[`VERSION`](https://cmake.org/cmake/help/latest/prop_tgt/VERSION.html#prop_tgt:VERSION)和[`SOVERSION`](https://cmake.org/cmake/help/latest/prop_tgt/SOVERSION.html#prop_tgt:SOVERSION) 目标属性。该值是一个字符串，指示安装程序应该如何处理符号链接：`skip`意味着安装程序应该跳过符号链接并只安装真实文件，并且`only`意味着安装程序应该只安装符号链接而不是真实文件。在所有情况下，`paths`成员都会列出它实际安装的内容。`exportName``type`是时存在的可选成员`export`。该值是指定导出名称的字符串。`exportTargets``type`是时存在的可选成员`export`。该值是对应于导出中包含的目标的 JSON 条目数组。每个条目都是一个带有成员的 JSON 对象：`id`唯一标识目标的字符串。这与`id`主“codemodel”对象`targets`数组中的目标成员匹配。`index`目标的主“codemodel”对象`targets`数组中基于 0 的无符号整数索引。`runtimeDependencySetName``type`存在的可选成员，`runtimeDependencySet` 并且安装程序是由 [`install(RUNTIME_DEPENDENCY_SET)`](https://cmake.org/cmake/help/latest/command/install.html#command:install)称呼。该值是一个字符串，指定已安装的运行时依赖集的名称。`runtimeDependencySetType``type`是时存在的可选成员`runtimeDependencySet`。该值是具有以下值之一的字符串：`library`表示此安装程序安装的依赖项不是 macOS 框架。`framework`表示此安装程序安装的是 macOS 框架的依赖项。`fileSetName``type`是时存在的可选成员`fileSet`。该值是带有文件集名称的字符串。此字段是在 codemodel 版本 2.4 中添加的。`fileSetType``type`是时存在的可选成员`fileSet`。该值是具有文件集类型的字符串。此字段是在 codemodel 版本 2.4 中添加的。`fileSetDirectories``type`是时存在的可选成员`fileSet`。该值是包含文件集基本目录的字符串列表（由genex-evaluation 确定[`HEADER_DIRS`](https://cmake.org/cmake/help/latest/prop_tgt/HEADER_DIRS.html#prop_tgt:HEADER_DIRS)或者 [`HEADER_DIRS_`](https://cmake.org/cmake/help/latest/prop_tgt/HEADER_DIRS_NAME.html#prop_tgt:HEADER_DIRS_)).此字段是在 codemodel 版本 2.4 中添加的。`fileSetTarget``type`是时存在的可选成员`fileSet`。该值是一个带有成员的 JSON 对象：`id`唯一标识目标的字符串。这与`id`主“codemodel”对象`targets`数组中的目标成员匹配。`index`目标的主“codemodel”对象`targets`数组中基于 0 的无符号整数索引。此字段是在 codemodel 版本 2.4 中添加的。`scriptFile``type`是时存在的可选成员`script`。该值是一个字符串，指定磁盘上脚本文件的路径，用正斜杠表示。如果文件位于顶级源目录中，则路径是相对于该目录指定的。否则路径是绝对的。`backtrace`当 CMake 语言回溯到[`install()`](https://cmake.org/cmake/help/latest/command/install.html#command:install)或添加此安装程序的其他命令调用可用。该值是`backtraceGraph`成员`nodes`数组中基于 0 的无符号整数索引。

- `backtraceGraph`

  一个[“代码模型”版本 2“回溯图”](https://cmake.org/cmake/help/latest/manual/cmake-file-api.7.html#codemodel-version-2-backtrace-graph)`backtrace` ，其节点被此“目录”对象中其他地方的成员引用。

#### [“codemodel” 版本 2 “目标” 对象](https://cmake.org/cmake/help/latest/manual/cmake-file-api.7.html#id14)

代码模型“目标”对象由[“代码模型”版本 2](https://cmake.org/cmake/help/latest/manual/cmake-file-api.7.html#codemodel-version-2) 对象的`targets`数组引用。每个“目标”对象都是一个带有成员的 JSON 对象：

- `name`

  一个字符串，指定目标的逻辑名称。

- `id`

  唯一标识目标的字符串。格式未指定，不应由客户端解释。

- `type`

  指定目标类型的字符串。该值为 `EXECUTABLE`、`STATIC_LIBRARY`、`SHARED_LIBRARY`、 `MODULE_LIBRARY`、`OBJECT_LIBRARY`、`INTERFACE_LIBRARY`或之一`UTILITY`。

- `backtrace`

  当创建目标的源代码中的命令的 CMake 语言回溯可用时存在的可选成员。该值是 `backtraceGraph`成员`nodes`数组中基于 0 的无符号整数索引。

- `folder`

  出现时的可选成员[`FOLDER`](https://cmake.org/cmake/help/latest/prop_tgt/FOLDER.html#prop_tgt:FOLDER)目标属性已设置。该值是一个具有一个成员的 JSON 对象：`name`一个字符串，指定目标文件夹的名称。

- `paths`

  包含成员的 JSON 对象：`source`一个字符串，指定目标源目录的路径，用正斜杠表示。如果目录在顶级源目录中，则路径是相对于该目录指定的（与`.`顶级源目录本身）。否则路径是绝对的。`build`一个字符串，指定目标构建目录的路径，用正斜杠表示。如果该目录位于顶级构建目录中，则路径是相对于该目录指定的（`.`用于顶级构建目录本身）。否则路径是绝对的。

- `nameOnDisk`

  对于链接或归档到单个主要工件的可执行文件和库目标存在的可选成员。该值是一个字符串，指定磁盘上该工件的文件名。

- `artifacts`

  存在于可执行文件和库目标的可选成员，这些目标在磁盘上生成供依赖项使用的工件。该值是与工件对应的条目的 JSON 数组。每个条目都是一个包含一个成员的 JSON 对象：`path`一个字符串，指定磁盘上文件的路径，用正斜杠表示。如果文件位于顶级构建目录中，则路径是相对于该目录指定的。否则路径是绝对的。

- `isGeneratorProvided`

  `true`如果目标是由 CMake 的构建系统生成器而不是源代码中的命令提供的，则以布尔值存在的可选成员。

- `install`

  当目标具有[`install()`](https://cmake.org/cmake/help/latest/command/install.html#command:install) 规则。该值是一个带有成员的 JSON 对象：`prefix`指定安装前缀的 JSON 对象。它有一个成员：`path`指定值的字符串[`CMAKE_INSTALL_PREFIX`](https://cmake.org/cmake/help/latest/variable/CMAKE_INSTALL_PREFIX.html#variable:CMAKE_INSTALL_PREFIX).`destinations`指定安装目标路径的 JSON 条目数组。每个条目都是一个带有成员的 JSON 对象：`path`指定安装目标路径的字符串。该路径可以是绝对的或相对于安装前缀的。`backtrace`当 CMake 语言回溯到[`install()`](https://cmake.org/cmake/help/latest/command/install.html#command:install)指定此目的地的命令调用可用。该值是`backtraceGraph`成员`nodes`数组中基于 0 的无符号整数索引。

- `link`

  对于链接到运行时二进制文件的可执行文件和共享库目标存在的可选成员。该值是一个 JSON 对象，其成员描述了链接步骤：`language``C`指定工具链的语言（例如, `CXX`）的字符串`Fortran`用于调用链接器。`commandFragments`当链接命令行调用的片段可用时存在的可选成员。该值是指定有序片段的 JSON 条目数组。每个条目都是一个带有成员的 JSON 对象：`fragment`一个字符串，指定链接命令行调用的片段。该值以构建系统的本机 shell 格式编码。`role`指定片段内容角色的字符串：`flags`: 链接标志。`libraries`: 链接库文件路径或标志。`libraryPath`：库搜索路径标志。`frameworkPath`: macOS 框架搜索路径标志。`lto``true` 启用链接时优化（也称为过程间优化或链接时代码生成）时以布尔值显示的可选成员。`sysroot`出现时的可选成员[`CMAKE_SYSROOT_LINK`](https://cmake.org/cmake/help/latest/variable/CMAKE_SYSROOT_LINK.html#variable:CMAKE_SYSROOT_LINK) 或者[`CMAKE_SYSROOT`](https://cmake.org/cmake/help/latest/variable/CMAKE_SYSROOT.html#variable:CMAKE_SYSROOT)变量被定义。该值是一个具有一个成员的 JSON 对象：`path`一个字符串，指定 sysroot 的绝对路径，用正斜杠表示。

- `archive`

  为静态库目标提供的可选成员。该值是一个 JSON 对象，其中包含描述归档步骤的成员：`commandFragments`当归档器命令行调用的片段可用时存在的可选成员。该值是指定片段的条目的 JSON 数组。每个条目都是一个带有成员的 JSON 对象：`fragment`一个字符串，指定归档器命令行调用的片段。该值以构建系统的本机 shell 格式编码。`role`指定片段内容角色的字符串：`flags`：归档器标志。`lto``true` 启用链接时优化（也称为过程间优化或链接时代码生成）时以布尔值显示的可选成员。

- `dependencies`

  当目标依赖于其他目标时存在的可选成员。该值是对应于依赖项的 JSON 条目数组。每个条目都是一个带有成员的 JSON 对象：`id`唯一标识此目标所依赖的目标的字符串。这匹配`id`另一个目标的主要成员。`backtrace`当 CMake 语言回溯到[`add_dependencies()`](https://cmake.org/cmake/help/latest/command/add_dependencies.html#command:add_dependencies), [`target_link_libraries()`](https://cmake.org/cmake/help/latest/command/target_link_libraries.html#command:target_link_libraries)，或创建此依赖项的其他命令调用可用。该值是`backtraceGraph`成员`nodes`数组中基于 0 的无符号整数索引。

- `sources`

  对应于目标源文件的 JSON 条目数组。每个条目都是一个带有成员的 JSON 对象：`path`一个字符串，指定磁盘上源文件的路径，用正斜杠表示。如果文件位于顶级源目录中，则路径是相对于该目录指定的。否则路径是绝对的。`compileGroupIndex`编译源时存在的可选成员。该值是 `compileGroups`数组中基于 0 的无符号整数索引。`sourceGroupIndex`当源是源组的一部分时存在的可选成员，或者通过[`source_group()`](https://cmake.org/cmake/help/latest/command/source_group.html#command:source_group)命令或默认情况下。该值是 `sourceGroups`数组中基于 0 的无符号整数索引。`isGenerated``true`如果源是，则以布尔值存在的可选成员[`GENERATED`](https://cmake.org/cmake/help/latest/prop_sf/GENERATED.html#prop_sf:GENERATED).`backtrace`当 CMake 语言回溯到[`target_sources()`](https://cmake.org/cmake/help/latest/command/target_sources.html#command:target_sources), [`add_executable()`](https://cmake.org/cmake/help/latest/command/add_executable.html#command:add_executable), [`add_library()`](https://cmake.org/cmake/help/latest/command/add_library.html#command:add_library),[`add_custom_target()`](https://cmake.org/cmake/help/latest/command/add_custom_target.html#command:add_custom_target), 或将此源添加到目标的其他命令调用可用。该值是`backtraceGraph`成员`nodes`数组中基于 0 的无符号整数索引。

- `sourceGroups`

  当源被组合在一起时出现的可选成员[`source_group()`](https://cmake.org/cmake/help/latest/command/source_group.html#command:source_group)命令或默认情况下。该值是对应于组的条目的 JSON 数组。每个条目都是一个带有成员的 JSON 对象：`name`一个字符串，指定源组的名称。`sourceIndexes`列出属于该组的源的 JSON 数组。每个条目都是目标主`sources`数组中基于 0 的无符号整数索引。

- `compileGroups`

  当目标具有可编译的源时存在的可选成员。该值是一个 JSON 条目数组，对应于所有使用相同设置编译的源组。每个条目都是一个带有成员的 JSON 对象：`sourceIndexes`列出属于该组的源的 JSON 数组。每个条目都是目标主`sources`数组中基于 0 的无符号整数索引。`language``C`指定工具链的语言（例如, `CXX`）的字符串`Fortran`用于编译源文件。`languageStandard`显式设置语言标准时出现的可选成员（例如，通过[`CXX_STANDARD`](https://cmake.org/cmake/help/latest/prop_tgt/CXX_STANDARD.html#prop_tgt:CXX_STANDARD)) 或通过编译功能隐含。每个条目都是一个带有两个成员的 JSON 对象：`backtraces`当设置的 CMake 语言回溯`<LANG>_STANDARD`可用时存在的可选成员。如果语言标准是由编译功能隐式设置的，则这些功能将用作回溯。多个编译功能可能需要相同的语言标准，因此可能会有多个回溯。`backtraceGraph` 该值是一个 JSON 数组，其中每个条目都是成员`nodes`数组中基于 0 的无符号整数索引。`standard`表示语言标准的字符串。此字段是在 codemodel 版本 2.2 中添加的。`compileCommandFragments`当编译器命令行调用的片段可用时存在的可选成员。该值是指定有序片段的 JSON 条目数组。每个条目都是一个带有一个成员的 JSON 对象：`fragment`一个字符串，指定编译命令行调用的片段。该值以构建系统的本机 shell 格式编码。`includes`存在包含目录时存在的可选成员。该值是一个 JSON 数组，每个目录都有一个条目。每个条目都是一个带有成员的 JSON 对象：`path`一个字符串，指定包含目录的路径，用正斜杠表示。`isSystem``true`如果包含目录被标记为系统包含目录，则以布尔值存在的可选成员。`backtrace`当 CMake 语言回溯到[`target_include_directories()`](https://cmake.org/cmake/help/latest/command/target_include_directories.html#command:target_include_directories)或添加此包含目录的其他命令调用可用。该值是`backtraceGraph` 成员`nodes`数组中基于 0 的无符号整数索引。`precompileHeaders`出现的可选成员[`target_precompile_headers()`](https://cmake.org/cmake/help/latest/command/target_precompile_headers.html#command:target_precompile_headers) 或其他命令调用集[`PRECOMPILE_HEADERS`](https://cmake.org/cmake/help/latest/prop_tgt/PRECOMPILE_HEADERS.html#prop_tgt:PRECOMPILE_HEADERS)在目标上。该值是一个 JSON 数组，每个标头都有一个条目。每个条目都是一个带有成员的 JSON 对象：`header`预编译头文件的完整路径。`backtrace`当 CMake 语言回溯到[`target_precompile_headers()`](https://cmake.org/cmake/help/latest/command/target_precompile_headers.html#command:target_precompile_headers)或添加此预编译标头的其他命令调用可用。该值是`backtraceGraph`成员 `nodes`数组中基于 0 的无符号整数索引。此字段是在 codemodel 版本 2.1 中添加的。`defines`存在预处理器定义时存在的可选成员。该值是一个 JSON 数组，每个定义都有一个条目。每个条目都是一个带有成员的 JSON 对象：`define`以 . 格式指定预处理器定义的字符串 `<name>[=<value>]`，例如`DEF`或`DEF=1`。`backtrace`当 CMake 语言回溯到[`target_compile_definitions()`](https://cmake.org/cmake/help/latest/command/target_compile_definitions.html#command:target_compile_definitions)或添加此预处理器定义的其他命令调用可用。该值是`backtraceGraph` 成员`nodes`数组中基于 0 的无符号整数索引。`sysroot`出现时的可选成员 [`CMAKE_SYSROOT_COMPILE`](https://cmake.org/cmake/help/latest/variable/CMAKE_SYSROOT_COMPILE.html#variable:CMAKE_SYSROOT_COMPILE)或者[`CMAKE_SYSROOT`](https://cmake.org/cmake/help/latest/variable/CMAKE_SYSROOT.html#variable:CMAKE_SYSROOT) 变量被定义。该值是一个具有一个成员的 JSON 对象：`path`一个字符串，指定 sysroot 的绝对路径，用正斜杠表示。

- `backtraceGraph`

  一个[“代码模型”版本 2“回溯图”](https://cmake.org/cmake/help/latest/manual/cmake-file-api.7.html#codemodel-version-2-backtrace-graph)`backtrace` ，其节点被此“目标”对象中其他地方的成员引用。

#### [“codemodel” 版本 2 “回溯图” ](https://cmake.org/cmake/help/latest/manual/cmake-file-api.7.html#id15)

“ `backtraceGraph`codemodel [”第 2 版“目录”对象](https://cmake.org/cmake/help/latest/manual/cmake-file-api.7.html#codemodel-version-2-directory-object)或[“codemodel”第 2 版“目标”对象](https://cmake.org/cmake/help/latest/manual/cmake-file-api.7.html#codemodel-version-2-target-object)的成员是描述回溯图的 JSON 对象。它的节点是从`backtrace`包含对象中其他地方的成员引用的。回溯图对象成员是：

- `nodes`

  在回溯图中列出节点的 JSON 数组。每个条目都是一个带有成员的 JSON 对象：`file``files`回溯数组中基于 0 的无符号整数索引。`line`当节点表示文件中的一行时出现的可选成员。该值是一个无符号整数，基于 1 的行号。`command`当节点表示文件中的命令调用时出现的可选成员。该值是回溯`commands`数组中基于 0 的无符号整数索引。`parent`当节点不是调用堆栈的底部时存在的可选成员。该值是回溯`nodes`数组中另一个条目的基于 0 的无符号整数索引。

- `commands`

  一个 JSON 数组，列出回溯节点引用的命令名称。每个条目都是一个指定命令名称的字符串。

- `files`

  列出回溯节点引用的 CMake 语言文件的 JSON 数组。每个条目都是一个字符串，指定文件的路径，用正斜杠表示。如果文件位于顶级源目录中，则路径是相对于该目录指定的。否则路径是绝对的。

### [对象类型“缓存” ](https://cmake.org/cmake/help/latest/manual/cmake-file-api.7.html#id16)

```
cache`对象种类列出缓存条目。这些是 存储在构建树的持久缓存 ( ) 中的[变量。](https://cmake.org/cmake/help/latest/manual/cmake-language.7.html#cmake-language-variables)`CMakeCache.txt
```

只有一个`cache`对象主要版本，版本 2。版本 1 不存在以避免与来自 [`cmake-server(7)`](https://cmake.org/cmake/help/latest/manual/cmake-server.7.html#manual:cmake-server(7))模式。

#### [“缓存”版本 2 ](https://cmake.org/cmake/help/latest/manual/cmake-file-api.7.html#id17)

`cache`对象版本 2 是一个 JSON 对象：

```
{
  "kind": "cache",
  "version": { "major": 2, "minor": 0 },
  "entries": [
    {
      "name": "BUILD_SHARED_LIBS",
      "value": "ON",
      "type": "BOOL",
      "properties": [
        {
          "name": "HELPSTRING",
          "value": "Build shared libraries"
        }
      ]
    },
    {
      "name": "CMAKE_GENERATOR",
      "value": "Unix Makefiles",
      "type": "INTERNAL",
      "properties": [
        {
          "name": "HELPSTRING",
          "value": "Name of generator."
        }
      ]
    }
  ]
}
```

特定于`cache`对象的成员是：

- `entries`

  一个 JSON 数组，其条目是每个指定缓存条目的 JSON 对象。每个条目的成员是：`name`指定条目名称的字符串。`value`指定条目值的字符串。`type`一个字符串，指定使用的条目的类型 [`cmake-gui(1)`](https://cmake.org/cmake/help/latest/manual/cmake-gui.1.html#manual:cmake-gui(1))选择要编辑的小部件。`properties`指定关联 [缓存条目属性](https://cmake.org/cmake/help/latest/manual/cmake-properties.7.html#cache-entry-properties)的 JSON 条目数组。每个条目都是一个包含成员的 JSON 对象：`name`一个字符串，指定缓存条目属性的名称。`value`一个字符串，指定缓存条目属性的值。

### [对象类型“cmakeFiles” ](https://cmake.org/cmake/help/latest/manual/cmake-file-api.7.html#id18)

`cmakeFiles`对象种类列出了 CMake 在配置和生成构建系统时使用的文件。这些包括 `CMakeLists.txt`文件以及包含的`.cmake`文件。

只有一个`cmakeFiles`对象主要版本，版本 1。

#### [“cmakeFiles” 版本 1 ](https://cmake.org/cmake/help/latest/manual/cmake-file-api.7.html#id19)

`cmakeFiles`对象版本 1 是一个 JSON 对象：

```
{
  "kind": "cmakeFiles",
  "version": { "major": 1, "minor": 0 },
  "paths": {
    "build": "/path/to/top-level-build-dir",
    "source": "/path/to/top-level-source-dir"
  },
  "inputs": [
    {
      "path": "CMakeLists.txt"
    },
    {
      "isGenerated": true,
      "path": "/path/to/top-level-build-dir/.../CMakeSystem.cmake"
    },
    {
      "isExternal": true,
      "path": "/path/to/external/third-party/module.cmake"
    },
    {
      "isCMake": true,
      "isExternal": true,
      "path": "/path/to/cmake/Modules/CMakeGenericSystem.cmake"
    }
  ]
}
```

特定于`cmakeFiles`对象的成员是：

- `paths`

  包含成员的 JSON 对象：`source`一个字符串，指定顶级源目录的绝对路径，用正斜杠表示。`build`一个字符串，指定顶级构建目录的绝对路径，用正斜杠表示。

- `inputs`

  一个 JSON 数组，其条目是每个 JSON 对象，指定 CMake 在配置和生成构建系统时使用的输入文件。每个条目的成员是：`path`一个字符串，指定 CMake 的输入文件的路径，用正斜杠表示。如果文件位于顶级源目录中，则路径是相对于该目录指定的。否则路径是绝对的。`isGenerated``true` 如果路径指定顶级构建目录下的文件并且构建是源外的，则以布尔值存在的可选成员。此成员在源代码构建中不可用。`isExternal``true` 如果路径指定不在顶级源或构建目录下的文件，则以布尔值存在的可选成员。`isCMake``true` 如果路径指定 CMake 安装中的文件，则以布尔值存在的可选成员。

### [对象类型“工具链” ](https://cmake.org/cmake/help/latest/manual/cmake-file-api.7.html#id20)

对象种类列出了构建期间使用的工具链的`toolchains`属性。其中包括语言、编译器路径、ID 和版本。

只有一个`toolchains`对象主要版本，版本 1。

#### [“工具链”版本 1 ](https://cmake.org/cmake/help/latest/manual/cmake-file-api.7.html#id21)

`toolchains`对象版本 1 是一个 JSON 对象：

```
{
  "kind": "toolchains",
  "version": { "major": 1, "minor": 0 },
  "toolchains": [
    {
      "language": "C",
      "compiler": {
        "path": "/usr/bin/cc",
        "id": "GNU",
        "version": "9.3.0",
        "implicit": {
          "includeDirectories": [
            "/usr/lib/gcc/x86_64-linux-gnu/9/include",
            "/usr/local/include",
            "/usr/include/x86_64-linux-gnu",
            "/usr/include"
          ],
          "linkDirectories": [
            "/usr/lib/gcc/x86_64-linux-gnu/9",
            "/usr/lib/x86_64-linux-gnu",
            "/usr/lib",
            "/lib/x86_64-linux-gnu",
            "/lib"
          ],
          "linkFrameworkDirectories": [],
          "linkLibraries": [ "gcc", "gcc_s", "c", "gcc", "gcc_s" ]
        }
      },
      "sourceFileExtensions": [ "c", "m" ]
    },
    {
      "language": "CXX",
      "compiler": {
        "path": "/usr/bin/c++",
        "id": "GNU",
        "version": "9.3.0",
        "implicit": {
          "includeDirectories": [
            "/usr/include/c++/9",
            "/usr/include/x86_64-linux-gnu/c++/9",
            "/usr/include/c++/9/backward",
            "/usr/lib/gcc/x86_64-linux-gnu/9/include",
            "/usr/local/include",
            "/usr/include/x86_64-linux-gnu",
            "/usr/include"
          ],
          "linkDirectories": [
            "/usr/lib/gcc/x86_64-linux-gnu/9",
            "/usr/lib/x86_64-linux-gnu",
            "/usr/lib",
            "/lib/x86_64-linux-gnu",
            "/lib"
          ],
          "linkFrameworkDirectories": [],
          "linkLibraries": [
            "stdc++", "m", "gcc_s", "gcc", "c", "gcc_s", "gcc"
          ]
        }
      },
      "sourceFileExtensions": [
        "C", "M", "c++", "cc", "cpp", "cxx", "mm", "CPP"
      ]
    }
  ]
}
```

特定于`toolchains`对象的成员是：

- `toolchains`

  一个 JSON 数组，其条目是每个 JSON 对象，指定与特定语言关联的工具链。每个条目的成员是：`language`指定工具链语言的 JSON 字符串，如 C 或 CXX。语言名称与可以传递给 [`project()`](https://cmake.org/cmake/help/latest/command/project.html#command:project)命令。因为 CMake 只支持每种语言的单个工具链，所以该字段可以用作键。`compiler`包含成员的 JSON 对象：`path`出现时的可选成员 [`CMAKE__COMPILER`](https://cmake.org/cmake/help/latest/variable/CMAKE_LANG_COMPILER.html#variable:CMAKE__COMPILER)变量是为当前语言定义的。它的值是一个 JSON 字符串，包含编译器的路径。`id`出现时的可选成员 [`CMAKE__COMPILER_ID`](https://cmake.org/cmake/help/latest/variable/CMAKE_LANG_COMPILER_ID.html#variable:CMAKE__COMPILER_ID)变量是为当前语言定义的。它的值是一个 JSON 字符串，包含编译器的 ID（GNU、MSVC 等）。`version`出现时的可选成员 [`CMAKE__COMPILER_VERSION`](https://cmake.org/cmake/help/latest/variable/CMAKE_LANG_COMPILER_VERSION.html#variable:CMAKE__COMPILER_VERSION)变量是为当前语言定义的。它的值是一个包含编译器版本的 JSON 字符串。`target`出现时的可选成员 [`CMAKE__COMPILER_TARGET`](https://cmake.org/cmake/help/latest/variable/CMAKE_LANG_COMPILER_TARGET.html#variable:CMAKE__COMPILER_TARGET)变量是为当前语言定义的。它的值是一个 JSON 字符串，包含编译器的交叉编译目标。`implicit`包含成员的 JSON 对象：`includeDirectories`出现时的可选成员 [`CMAKE__IMPLICIT_INCLUDE_DIRECTORIES`](https://cmake.org/cmake/help/latest/variable/CMAKE_LANG_IMPLICIT_INCLUDE_DIRECTORIES.html#variable:CMAKE__IMPLICIT_INCLUDE_DIRECTORIES)变量是为当前语言定义的。它的值是 JSON 字符串的 JSON 数组，其中每个字符串都包含一个指向编译器隐式包含目录的路径。`linkDirectories`出现时的可选成员 [`CMAKE__IMPLICIT_LINK_DIRECTORIES`](https://cmake.org/cmake/help/latest/variable/CMAKE_LANG_IMPLICIT_LINK_DIRECTORIES.html#variable:CMAKE__IMPLICIT_LINK_DIRECTORIES)变量是为当前语言定义的。它的值是一个 JSON 字符串的 JSON 数组，其中每个字符串都包含一个指向编译器隐式链接目录的路径。`linkFrameworkDirectories`出现时的可选成员 [`CMAKE__IMPLICIT_LINK_FRAMEWORK_DIRECTORIES`](https://cmake.org/cmake/help/latest/variable/CMAKE_LANG_IMPLICIT_LINK_FRAMEWORK_DIRECTORIES.html#variable:CMAKE__IMPLICIT_LINK_FRAMEWORK_DIRECTORIES)变量是为当前语言定义的。它的值是 JSON 字符串的 JSON 数组，其中每个字符串都包含一个指向编译器的隐式链接框架目录的路径。`linkLibraries`出现时的可选成员 [`CMAKE__IMPLICIT_LINK_LIBRARIES`](https://cmake.org/cmake/help/latest/variable/CMAKE_LANG_IMPLICIT_LINK_LIBRARIES.html#variable:CMAKE__IMPLICIT_LINK_LIBRARIES)变量是为当前语言定义的。它的值是一个 JSON 字符串的 JSON 数组，其中每个字符串都包含一个指向编译器隐式链接库的路径。`sourceFileExtensions`出现时的可选成员 [`CMAKE__SOURCE_FILE_EXTENSIONS`](https://cmake.org/cmake/help/latest/variable/CMAKE_LANG_SOURCE_FILE_EXTENSIONS.html#variable:CMAKE__SOURCE_FILE_EXTENSIONS)变量是为当前语言定义的。它的值是 JSON 字符串的 JSON 数组，其中每个字符串都包含该语言的文件扩展名（没有前导点）。