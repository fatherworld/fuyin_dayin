//以下两个头文件用于文件的存在判断与创建
#include "direct.h"
#include<io.h>
#include<string>
#include<iostream>
#include<fstream>
using namespace std;
//判断文件是否存在不存在创建
bool isFileExist(string fname);

int isDirExist(string dirPath);