//以下两个头文件用于文件的存在判断与创建
#include "direct.h"
#include<io.h>
#include<string>
#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<direct.h>
using namespace std;
//判断文件是否存在不存在创建
bool isFileExist(string fname);

//判断文件夹路径是否存在
int isDirExist(string dirPath);

//获取当前文件所在的文件夹路径
char* getCwdPath();