#include"fileddl.h"
//判断文件是否存在不存在创建
bool isFileExist(string fname)
{
	fstream fs;
	fs.open(fname, ios::in);
	if(!fs)
		return false;
	return true;
}

//判断文件夹是否存在不存在创建
int isDirExist(string dirPath)
{
	char *p = getCwdPath();
	int ret = 0;
	if(_access(dirPath.c_str(),0) == -1)
	{
		ret = _mkdir(dirPath.c_str());
		cout << "该文件夹不存在，已自动创建" << endl;
	}
	else
	{
		cout << "该文件夹存在" << endl;
	}
	return ret;
}
//获取文件所在的文件夹路径
char* getCwdPath()
{
	char *p = new char[256];
	_getcwd(p,256);
	return p;
}
