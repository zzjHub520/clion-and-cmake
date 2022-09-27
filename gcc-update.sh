
cd /home/zzj/workspaces/cpp/gcc-12.2.0

./contrib/download_prerequisites    
mkdir -p build  &&  cd build
../configure --prefix=/usr/local/gcc-12.2.0 --enable-bootstrap --enable-checking=release --enable-languages=c,c++ --disable-multilib

#编译生成makefile文件
make -j4
#安装GCC
make install

