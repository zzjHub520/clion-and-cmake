# 各平台编译器中的Pre-build及Post-build操作

通常我们在编译一个工程或是链接库的时候，需要在编译链接之前或者编译链接之后执行一些操作，比如：拷贝一些第三方库到工程的工作目录下或执行一些批处理（shell）操作，这个时候就需要在编译器环境中进行相关设置：

#### Visual Studio####

> 说明： 在vs2005以及以上都支持了Build Events, 同时可以支持多行命令.
> 而在vs2003中要想执行多行命令，只能把命令写在一个批处理文件中，然后通过调用批处理来执行.

- 打开Build Events方框步骤：
  1.右键单击Solution Explorer，选择Properties
  2.选择Build Events，可以看到Pre-build 和Post-build，以及运行Post-build event 的条件
- 可以在相应的编译事件中添加以下常用操作：
  1.build完后修改build产物的名字(后缀),并覆盖已有的同名文件.
  `copy /y $(TargetFileName) $(TargetName).XXX`
  2.调用外部命令或批处理:
  `call "C:\Program Files\XXX.exe"`
  3.条件判断:
  `IF NOT $(ConfigurationName) == Release GOTO end call "C:\Program Files\XXX.exe" $(ProjectDir)$(TargetName).cvp :end`
  4.web project 自动部署
  `copy $(TargetDir)*.* //MyServer/MyService/bin copy $(ProjectDir)*.ascx //MyServer/MyService`
  5.拷贝文件到制定目录
  `copy "$(ProjectDir)pri.bin" "$(SolutionDir)$(SolutionName)\$(OutDir)"`

#### xcode####

1. 选择项目TARGETS，进入Build Phases页面
2. 点击“＋”按钮，选择“New Run Script Phase”
3. 在Shell选框中填入使用的bash版本，默认是/bin/sh
4. 在接下来的方框中编写想要执行的shell命令（支持所有shell命令）
5. 如果是想建立编译前事件，需将Run Script用鼠标拖动到Compile Sources之前，若是建立编译后事件，则保证Run Script在最后即可

#### CMake####

在CMake中提供了add_custom_command和add_custom_target用来为某个目标或库添加一些自定义命令，该命令本身会成为目标的一部分，仅在目标本身被构建时才会执行。如果该目标已经构建，命令将不会执行。

- add_custom_command: 增加自定义的构建规则到生成的构建系统中



```csharp
add_custom_command(TARGET target
                     PRE_BUILD | PRE_LINK| POST_BUILD
                     COMMAND command1[ARGS] [args1...]
                     [COMMAND command2[ARGS] [args2...] ...]
                     [WORKING_DIRECTORYdir]
                     [COMMENT comment][VERBATIM])
```

命令执行的时机由如下参数决定：
1.PRE_BUILD - 命令将会在其他依赖项执行前执行
2.PRE_LINK - 命令将会在其他依赖项执行完后执行
3.POST_BUILD - 命令将会在目标构建完后执行。

- add_custom_target: 增加一个没有输出的目标，使得它总是被构建



```css
add_custom_target(Name [ALL][command1 [args1...]]
                    [COMMAND command2 [args2...] ...]
                    [DEPENDS depend depend depend ... ]
                    [WORKING_DIRECTORY dir]
                    [COMMENT comment] [VERBATIM]
                    [SOURCES src1 [src2...]])
```

增加一个指定名字的目标，并执行指定的命令。该目标没有输出文件，总是被认为是过期的，即使是在试图用目标的名字创建一个文件。如果指定了ALL选项，那就表明该目标会被添加到默认的构建目标，使得它每次都被运行。

> 关于以上两个编译命令的具体用法，可以参考以下链接：[CMake客制化命令](https://link.jianshu.com/?t=http://blog.csdn.net/fuyajun01/article/details/8907207)

例子（在CMake文件中任意位置添加）：



```bash
ADD_CUSTOM_TARGET(
    TestExample ALL
)
ADD_CUSTOM_COMMAND(TARGET TestExample
        PRE_BUILD
        COMMAND chmod 700 /home/chenjs/test
        COMMAND /home/chenjs/test -c -o ../../output ../../input/test.txt
        COMMENT "Generate project output file" 
)
```

### Jni环境下的Android.mk####

在使用NDK为Android项目编译CPP库时，可以直接在Android.mk中添加执行Shell命令，需要注意的是在Cywin以及在Linux下编译的不同点，并对两个平台区别对待处理
例子（在Android.mk文件中正确添加）：



```jsx
ifndef SYSENV
    SYSENV := $(shell uname)
endif
ifeq (CYGWIN,$(findstring CYGWIN,$(SYSENV)))
    $(info Generate project output file under cywin)
    $(shell ../../tools/test.exe -c -o ../../output ../../output ../../input/test.txt)
else ifeq ($(SYSENV), Linux)
    $(info Generate project output file under linux)
    $(shell chmod 700 /home/chenjs/test)
    $(shell /home/chenjs/test -c -o ../../output ../../input/test.txt)
endif
```

