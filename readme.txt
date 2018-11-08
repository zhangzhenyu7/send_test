


环境QT5.3.1(MinGW 4.8 (32-bit)) Windows7

 

把exe文件单独拷贝到一个空白文件夹.

打开Qt安装目录的命令行工具"Qt 5.3 for Desktop (MinGW 4.8 32 bit)"

切换当前目录至exe存放路径

执行windeployqt XXX.exe即可

 

 需要注意的是release版本的exe引用的DLL等会比debug版本的小不少.


