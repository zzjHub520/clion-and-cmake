# [Protobuf在Cmake中的正确使用方法详解](http://www.cppcns.com/wangluo/qitazonghe/380488.html)

Protobuf是google开发的一个序列化和反序列化的协议库，我们可以自己设计传递数据的格式，通过.proto文件定义我们的要传递的数据格式。例如，在深度学习中常用的ONNX交换模型就是使用.pr...

Protobuf是google开发的一个序列化和反序列化的协议库，我们可以自己设计传递数据的格式，通过`.proto文件`定义我们的要传递的数据格式。例如，在深度学习中常用的ONNX交换模型就是使用`.proto`编写的。我们可以通过多种前端(MNN、NCNN、TVM的前端)去读取这个.onnx这个模型，但是首先你要安装protobuf。

在之前的博文中已经简单介绍了onnx，其中onnx.proto就代表了onnx模型的基本数据结构。一般来说，protobuf经常搭配Cmake使用，Cmake有官方的modules，可以通过简单的几个命令`protobuf_generate_cpp`来生成对应的`.pb.cc`和`.pb.h`。

简单的例子：

```cmake
find_package(Protobuf REQUIRED)include_directories(${Protobuf_INCLUDE_DIRS})include_directories(${CMAKE_CURRENT_BINARY_DIR})protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS foo.proto)protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS EXPORT_MACRO DLL_EXPORT foo.proto)protobuf_generate_python(PROTO_PY foo.proto)add_executable(bar bar.cc ${PROTO_SRCS} ${PROTO_HDRS})target_link_libraries(bar ${Protobuf_LIBRARIES})
```

但是这个例子太简单了，如果我们的.proto文件只有一个或者说都只在一个目录里，那用这个命令没什么毛病...

但如果是这种情况，我们的文件目录如下：

```
├── CMakeLists.txt
├── README.md
├── meta
│ └── proto
│ ├── CMakeLists.txt
│ └── common
│ ├── bar
│ │ ├── CMakeLists.txt
│ │ └── bar.proto
│ └── foo
│ ├── CMakeLists.txt
│ └── foo.proto
└── src
  ├── CMakeLists.txt     
  ├── c_proto.cc     
  └── c_proto.hh
```

其中`foo.proto`文件如下:

```protobuf
message foo_msg{
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

如上，bar文件引用foo，而且这两个不在一个目录，如果直接使用protobuf_generate_cpp来生成，直接会报错。（这个例子取自Yu的一篇博文）

也想过把他俩放到同一个目录...然后`bar.proto`中import的代码就要修改，虽然这样可以，但显然是不适合大型的项目。

而这个大型项目显然就是mediapipe...折磨了我好久。

关于mediapipe的详细介绍在另一篇文章。mediapipe中使用了大量的ProtoBuf技术来表示图结构，而且mediapipe原生并不是采用cmake来构建项目，而是使用google自家研发的bazel，这个项目构建系统我就不评价了，而现在我需要使用Cmake来对其进行构建。

![Protobuf在Cmake中的正确使用方法详解](MarkDownImages/Protobuf%E5%9C%A8Cmake%E4%B8%AD%E7%9A%84%E6%AD%A3%E7%A1%AE%E4%BD%BF%E7%94%A8%E6%96%B9%E6%B3%95%E8%AF%A6%E8%A7%A3.assets/ly01zgizwvo.png)

这也是噩梦的开始，mediapipe的.proto文件很多，核心的framework的目录下存在很多的.proto文件，根目录和子目录都有.proto文件：

![Protobuf在Cmake中的正确使用方法详解](MarkDownImages/Protobuf%E5%9C%A8Cmake%E4%B8%AD%E7%9A%84%E6%AD%A3%E7%A1%AE%E4%BD%BF%E7%94%A8%E6%96%B9%E6%B3%95%E8%AF%A6%E8%A7%A3.assets/t2xbdskbc5r.png)

而且每个proto文件之间存在引用的顺序，framework根目录下的`calculator.proto`文件:

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

每个.proto文件都import了其他目录下的文件，这里的`import`类似于C++中的include，但是这里的import又可以相互引用，例如上述的`status_handler.proto`也引用了`mediapipe_options.proto`。

如果直接对上述所有的.proto文件直接使用`protobuf_generate_cpp`命令，会直接报错，因为这些文件不在一个目录，而且import的相对目录也无法分析。另外，不同目录内的`.cc`文件会引用相应目录生成的`.pb.h`文件，我们需要生成的`.pb.cc`和`.pb.h`在原始的目录中，这样才可以正常引用，要不然需要修改其他源代码的include地址，比较麻烦。

CLion中Cmake来编译proto生成的`.pb.cc`和`.pb.h`不在原始目录，而是集中在cmake-build-debug(release)中，我们额外需要将其中生成的`.pb.cc`和`.pb.h`文件移动到原始地址(Clion的情况是这样)。

## 正确修改cmake

对于这种情况，比较合适的做法是直接使用命令进行生成。

首先找到所有需要编译的.proto文件：

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

接下来，定义相关的目录地址，`PROTO_META_BASE_DIR`为编译之后生成文件的目录。`PROTO_FLAGS`很重要，指定编译`.proto`文件时的总的寻找路径，`.proto`中的import命令根据根据这个地址去连接其他的`.proto`文件：

```cmake
SET(PROTO_META_BASE_DIR ${CMAKE_CURRENT_BINARY_DIR})
LIST(APPEND PROTO_FLAGS -I${CMAKE_CURRENT_SOURCE_DIR})
```

设置好之后，通过`FOREACH`去循环之前的.proto文件，依次编译每个文件，然后将生成的`.pb.cc`和`.pb.h`移动回原始的目录，至此就可以正常工作了。

```cmake
FOREACH(FIL ${protobuf_files})      
GET_FILENAME_COMPONENT(FIL_WE ${FIL} NAME_WE)      
string(REGEX REPLACE ".+/(.+)\\..*" "\\1" FILE_NAME ${FIL})    
string(REGEX REPLACE "(.+)\\${FILE_NAME}.*" "\\1" FILE_PATH ${FIL})     
string(REGEX MATCH "(/mediapipe/framework.*|/mediapipe/util.*|/mediapipe/calculators/internal/)" OUT_PATH ${FILE_PATH}) 
set(PROTO_SRCS "${CMAKE_CURRENT_BINARY_DIR}${OUT_PATH}${FIL_WE}.pb.cc")     
set(PROTO_HDRS "${CMAKE_CURRENT_BINARY_DIR}${OUT_PATH}${FIL_WE}.pb.h")    
EXECUTE_PROCESS(         COMMAND ${PROTOBUF_PROTOC_EXECUTABLE} ${PROTO_FLAGS} --cpp_out=${PROTO_META_BASE_DIR} ${FIL} )  
message("Copying " ${PROTO_SRCS} " to " ${FILE_PATH})  
file(COPY ${PROTO_SRCS} DESTINATION ${FILE_PATH})   
file(COPY ${PROTO_HDRS} DESTINATION ${FILE_PATH}) ENDFOREACH()
```

