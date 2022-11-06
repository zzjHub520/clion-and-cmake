## **1)下载GCC9.3.0源码并解压**

https://blog.csdn.net/pauljjf/article/details/105171154

从[GCC官方FTP下载地址](https://ftp.gnu.org/gnu/gcc/)可以看到GCC最新版本为9.3.0。由于官网下载速度慢,实际上用清华大学的镜像站进行下载,代码如下:

```sh
wget -c /opt/tmp/ https://mirrors.tuna.tsinghua.edu.cn/gnu/gcc/gcc-9.3.0/gcc-9.3.0.tar.gz
#考虑到安装失败的可能性，创建一个临时文件夹来安装GCC
sudo mkdir /opt/tmp
cd /opt/tmp
#解压安装包到临时文件夹里
sudo tar -zxvf /home/paul/Downloads/gcc-9.3.0.tar.gz 
```

## **2)下载依赖文件**

```sh
cd gcc-9.3.0/
#下载gmp mpfr mpc等供编译需求的依赖项
./contrib/download_prerequisites           
```

执行命令会出现如下的错误,可能原因是从清华大学镜像下的安装包有过改动,不能通过sha512验证

```sh
gmp-6.1.0.tar.bz2: FAILED
sha512sum: WARNING: 1 computed checksum did NOT match
error: Cannot verify integrity of possibly corrupted file gmp-6.1.0.tar.bz2       
```

查看download_prerequisites源码后, 在gcc-9.3.0目录下输入以下命令:

```sh
#删除上一命令安装失败产生的gmp压缩包和目录
rm gmp-6.1.0.tar.bz2 
rm gmp-6.1.0
#加--noverify选项禁止边下边验证
./contrib/download_prerequisites --no-verify        
```

## **3)创建预编译目录**

```sh
mkdir  build  &&  cd build             
```

## **4)设置编译选项并编译**

       ```sh
       ../configure --prefix=/usr/local/gcc-9.3.0 --enable-bootstrap --enable-checking=release --enable-languages=c,c++ --disable-multilib
       ```

     ```sh
     –-enable-languages表示你要让你的gcc支持哪些编程语言;
     -–disable-multilib表示编译器不编译成其他平台的可执行代码;
     -–disable-checking表示生成的编译器在编译过程中不做额外检查
     –-enable-checking=xxx 表示编译过程中增加XXX检查
     –prefix=/usr/local/gcc-9.3.0 指定安装路径
     –enable-bootstrap 表示用第一次编译生成的程序进行第二次编译，然后用再次生成的程序进行第三次编译，并且检查比较第二次和第三次结果的正确性，也就是进行冗余的编译检查工作。 非交叉编译环境下，默认已经将该值设为 enable，可以不用显示指定；交叉编译环境下，需要显示将其值设为 disable。         
     ```

## **5)安装**

```sh
#编译生成makefile文件
make -j4
#安装GCC
sudo make install            
```

## **6)安装后的设置**

```sh
#设置环境变量
touch /etc/profile.d/gcc.sh
sudo chmod 777 /etc/profile.d/gcc.sh 
sudo echo -e '\nexport PATH=/usr/local/gcc-9.3.0/bin:$PATH\n' >> /etc/profile.d/gcc.sh && source /etc/profile.d/gcc.sh

#设置头文件
sudo ln -sv /usr/local/gcc/include/ /usr/include/gcc

#设置库文件
touch /etc/ld.so.conf.d/gcc.conf
sudo chmod 777 /etc/ld.so.conf.d/gcc.conf 
sudo echo -e "/usr/local/gcc/lib64" >> /etc/ld.so.conf.d/gcc.conf

#加载动态连接库
sudo ldconfig -v
ldconfig -p |grep gcc   
```

## **7)测试版本号**

```sh
#测试
gcc -v
```

敲入命令后,终端显示如下文字,说明已成功安装GCC9.3.0

```sh
Target: x86_64-pc-linux-gnu
Configured with: …/configure --prefix=/usr/local/gcc-9.3.0 --enable-bootstrap --enable-checking=release --enable-languages=c,c++ --disable-multilib
Thread model: posix
gcc version 9.3.0 (GCC)   
```

## **8）升级libstdc++.so.6**

https://www.cnblogs.com/twinhead/p/9248745.html

### 1）检查了gcc版本：gcc --version 得到结果gcc (GCC) 4.9.2 已经比较新；

### 2）

centos7

```sh
strings /usr/lib64/libstdc++.so.6 |grep GLIBCXX        
```

ubuntu16

```sh
strings /usr/lib/x86_64-linux-gnu/libstdc++.so.6 | grep GLIBCXX            
```

得到结果：

```sh
GLIBCXX_3.4
GLIBCXX_3.4.1
GLIBCXX_3.4.2
GLIBCXX_3.4.3
GLIBCXX_3.4.4
GLIBCXX_3.4.5
GLIBCXX_3.4.6
GLIBCXX_3.4.7
GLIBCXX_3.4.8
GLIBCXX_3.4.9
GLIBCXX_3.4.10
GLIBCXX_3.4.11
GLIBCXX_3.4.12
GLIBCXX_3.4.13
GLIBCXX_3.4.14
GLIBCXX_3.4.15
GLIBCXX_3.4.16
GLIBCXX_3.4.17
GLIBCXX_DEBUG_MESSAGE_LENGTH
```

### 3）

```sh
sudo find / -name "libstdc++.so.6*"
```

得到结果：

```sh
/usr/share/gdb/auto-load/usr/lib64/libstdc++.so.6.0.13-gdb.pyc
/usr/share/gdb/auto-load/usr/lib64/libstdc++.so.6.0.13-gdb.pyo
/usr/share/gdb/auto-load/usr/lib64/libstdc++.so.6.0.13-gdb.py
/usr/share/gdb/auto-load/usr/lib/libstdc++.so.6.0.13-gdb.pyc
/usr/share/gdb/auto-load/usr/lib/libstdc++.so.6.0.13-gdb.pyo
/usr/share/gdb/auto-load/usr/lib/libstdc++.so.6.0.13-gdb.py
/usr/lib64/libstdc++.so.6.bak
/usr/lib64/libstdc++.so.6.0.17
/usr/lib64/libstdc++.so.6.0.13
/usr/lib64/libstdc++.so.6
/usr/local/lib64/libstdc++.so.6.0.18
/usr/local/lib64/libstdc++.so.6.0.18-gdb.py
/usr/local/lib64/libstdc++.so.6.0.20
/usr/local/lib64/libstdc++.so.6.0.20-gdb.py
/usr/local/lib64/libstdc++.so.6        
```

可以看到，已经有libstdc++.so.6.0.20

### 4)

centos7

```sh
ls -al /usr/lib64/libstdc++.so.6       
```

ubuntu16

```sh
ls -al /usr/lib/x86_64-linux-gnu/libstdc++.so.6 
```

得到结果：

```sh
lrwxrwxrwx. 1 root root 30 11月 16 11:31 /usr/lib64/libstdc++.so.6 -> /usr/lib64/libstdc++.so.6.0.17   
```

说明虽然gcc已经更新到最新版，但是连接还是旧版本，所以只需要修改连接就可以了。

解决方案步骤：

centos7

```sh
sudo cp /usr/local/gcc-9.3.0/lib64/libstdc++.so.6.0.28 /usr/lib64  //复制文件
sudo rm -rf /usr/lib64/libstdc++.so.6  //删除旧文件
sudo ln -s /usr/lib64/libstdc++.so.6.0.28 /usr/lib64/libstdc++.so.6 //链接到新版本             
```

ubuntu16

```sh
sudo cp /usr/local/gcc-9.3.0/lib64/libstdc++.so.6.0.28 /usr/lib/x86_64-linux-gnu/
sudo rm -rf /usr/lib/x86_64-linux-gnu/libstdc++.so.6
sudo ln -s /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.28 /usr/lib/x86_64-linux-gnu/libstdc++.so.6
```