
cd /home/zzj/workspaces/cpp/gcc-12.2.0

./contrib/download_prerequisites    
mkdir -p build  &&  cd build
../configure --prefix=/usr/local/gcc-12.2.0 --enable-bootstrap --enable-checking=release --enable-languages=c,c++ --disable-multilib

#编译生成makefile文件
make -j16
#安装GCC
make install

#设置环境变量
touch /etc/profile.d/gcc.sh
sudo chmod 777 /etc/profile.d/gcc.sh 
sudo echo -e '\nexport PATH=/usr/local/gcc-12.2.0/bin:$PATH\n' >> /etc/profile.d/gcc.sh && source /etc/profile.d/gcc.sh

#设置头文件
sudo ln -sv /usr/local/gcc/include/ /usr/include/gcc

#设置库文件
touch /etc/ld.so.conf.d/gcc.conf
sudo chmod 777 /etc/ld.so.conf.d/gcc.conf 
sudo echo -e "/usr/local/gcc/lib64" >> /etc/ld.so.conf.d/gcc.conf

#加载动态连接库
sudo ldconfig -v
ldconfig -p |grep gcc   

strings /usr/lib64/libstdc++.so.6 |grep GLIBCXX     
ls -al /usr/lib64/libstdc++.so.6 


cp /usr/local/gcc-12.2.0/lib64/libstdc++.so.6.0.30 /usr/lib64
rm -rf /usr/lib64/libstdc++.so.6
ln -s /usr/lib64/libstdc++.so.6.0.30 /usr/lib64/libstdc++.so.6