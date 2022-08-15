# 关于深度学习:Protobuf在Cmake中的正确使用

2021-03-08

Protobuf是google开发的一个序列化和反序列化的协定库，咱们能够本人设计传递数据的格局，通过`.proto文件`定义咱们的要传递的数据格式。例如，在深度学习中罕用的ONNX替换模型就是应用`.proto`编写的。咱们能够通过多种前端(MNN、NCNN、TVM的前端)去读取这个.onnx这个模型，然而首先你要装置protobuf。

在之前的博文中曾经简略介绍了onnx，其中onnx.proto就代表了onnx模型的根本数据结构。一般来说，protobuf常常搭配Cmake应用，Cmake有官网的modules，能够通过简略的几个命令`protobuf_generate_cpp`来生成对应的`.pb.cc`和`.pb.h`。



简略的例子：

```cmake
find_package(Protobuf REQUIRED)
include_directories(${Protobuf_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_BINARY_DIR})
protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS foo.proto)
protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS EXPORT_MACRO DLL_EXPORT foo.proto)
protobuf_generate_python(PROTO_PY foo.proto)
add_executable(bar bar.cc ${PROTO_SRCS} ${PROTO_HDRS})
target_link_libraries(bar ${Protobuf_LIBRARIES})
```

然而这个例子太简略了，如果咱们的.proto文件只有一个或者说都只在一个目录里，那用这个命令没什么故障…

但如果是这种状况，咱们的文件目录如下：

```
├── CMakeLists.txt
├── README.md
├── meta
│   └── proto
│       ├── CMakeLists.txt
│       └── common
│           ├── bar
│           │   ├── CMakeLists.txt
│           │   └── bar.proto
│           └── foo
│               ├── CMakeLists.txt
│               └── foo.proto
└── src
    ├── CMakeLists.txt
    ├── c_proto.cc
    └── c_proto.hh
```

其中`foo.proto`文件如下:

```protobuf
message foo_msg 
{
  optional string name = 1;
}
```

`bar.proto`的文件如下：

```protobuf
import "common/foo/foo.proto";
 
message bar_msg 
{
  optional foo_msg foo = 1;
  optional string name = 2;
}
```

如上，bar文件援用foo，而且这两个不在一个目录，如果间接应用**protobuf_generate_cpp**来生成，间接会报错。（这个例子取自Yu的一篇博文）

也想过把他俩放到同一个目录…而后`bar.proto`中import的代码就要批改，尽管这样能够，但显然是不适宜大型的我的项目。

而这个大型项目显然就是mediapipe…折磨了我良久。

对于mediapipe的具体介绍在另一篇文章。mediapipe中应用了大量的ProtoBuf技术来示意图构造，而且mediapipe原生并不是采纳cmake来构建我的项目，而是应用google自家研发的bazel，这个我的项目构建零碎我就不评估了，而当初我须要应用Cmake来对其进行构建。



这也是噩梦的开始，mediapipe的.proto文件很多，外围的framework的目录下存在很多的.proto文件，根目录和子目录都有.proto文件：



而且每个proto文件之间存在援用的程序，framework根目录下的`calculator.proto`文件:

```protobuf
// mediapipe/framework/calculator.proto
syntax = "proto3";

package mediapipe;

import public "mediapipe/framework/calculator_options.proto";

import "google/protobuf/any.proto";
import "mediapipe/framework/mediapipe_options.proto";
import "mediapipe/framework/packet_factory.proto";
import "mediapipe/framework/packet_generator.proto";
import "mediapipe/framework/status_handler.proto";
import "mediapipe/framework/stream_handler.proto";
```

每个.proto文件都import了其余目录下的文件，这里的`import`相似于C++中的include，然而这里的import又能够互相援用，例如上述的`status_handler.proto`也援用了`mediapipe_options.proto`。

如果间接对上述所有的.proto文件间接应用`protobuf_generate_cpp`命令，会间接报错，因为这些文件不在一个目录，而且import的绝对目录也无奈剖析。另外，不同目录内的`.cc`文件会援用相应目录生成的`.pb.h`文件，咱们须要生成的`.pb.cc`和`.pb.h`在原始的目录中，这样才能够失常援用，要不然须要批改其余源代码的include地址，比拟麻烦。

CLion中Cmake来编译proto生成的`.pb.cc`和`.pb.h`不在原始目录，而是集中在cmake-build-debug(release)中，咱们额定须要将其中生成的`.pb.cc`和`.pb.h`文件挪动到原始地址(Clion的状况是这样)。

## 正确批改cmake

对于这种状况，比拟适合的做法是间接应用命令进行生成。

首先找到所有须要编译的.proto文件：

```cmake
file(GLOB protobuf_files
        mediapipe/framework/*.proto
        mediapipe/framework/tool/*.proto
        mediapipe/framework/deps/*.proto
        mediapipe/framework/testdata/*.proto
        mediapipe/framework/formats/*.proto
        mediapipe/framework/formats/annotation/*.proto
        mediapipe/framework/formats/motion/*.proto
        mediapipe/framework/formats/object_detection/*.proto
        mediapipe/framework/stream_handler/*.proto
        mediapipe/util/*.proto
        mediapipe/calculators/internal/*.proto
        )
```

接下来，定义相干的目录地址，`PROTO_META_BASE_DIR`为编译之后生成文件的目录。`PROTO_FLAGS`很重要，指定编译`.proto`文件时的总的寻找门路，`.proto`中的import命令依据依据这个地址去连贯其余的`.proto`文件：

```cmake
SET(PROTO_META_BASE_DIR ${CMAKE_CURRENT_BINARY_DIR})
LIST(APPEND PROTO_FLAGS -I${CMAKE_CURRENT_SOURCE_DIR})
```

设置好之后，通过`FOREACH`去循环之前的.proto文件，顺次编译每个文件，而后将生成的`.pb.cc`和`.pb.h`挪动回原始的目录，至此就能够失常工作了。

```cmake
FOREACH(FIL ${protobuf_files})

    GET_FILENAME_COMPONENT(FIL_WE ${FIL} NAME_WE)

    string(REGEX REPLACE ".+/(.+)\\..*" "\\1" FILE_NAME ${FIL})
    string(REGEX REPLACE "(.+)\\${FILE_NAME}.*" "\\1" FILE_PATH ${FIL})

    string(REGEX MATCH "(/mediapipe/framework.*|/mediapipe/util.*|/mediapipe/calculators/internal/)" OUT_PATH ${FILE_PATH})

    set(PROTO_SRCS "${CMAKE_CURRENT_BINARY_DIR}${OUT_PATH}${FIL_WE}.pb.cc")
    set(PROTO_HDRS "${CMAKE_CURRENT_BINARY_DIR}${OUT_PATH}${FIL_WE}.pb.h")

    EXECUTE_PROCESS(
            COMMAND ${PROTOBUF_PROTOC_EXECUTABLE} ${PROTO_FLAGS} --cpp_out=${PROTO_META_BASE_DIR} ${FIL}
    )
    message("Copying " ${PROTO_SRCS} " to " ${FILE_PATH})

    file(COPY ${PROTO_SRCS} DESTINATION ${FILE_PATH})
    file(COPY ${PROTO_HDRS} DESTINATION ${FILE_PATH})

ENDFOREACH()
```

