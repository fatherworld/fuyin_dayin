#include"fileddl.h"
//�ж��ļ��Ƿ���ڲ����ڴ���
bool isFileExist(string fname)
{
	fstream fs;
	fs.open(fname, ios::in);
	if(!fs)
		return false;
	return true;
}

//�ж��ļ����Ƿ���ڲ����ڴ���
int isDirExist(string dirPath)
{
	int ret = 0;
	if(_access(dirPath.c_str(),0) == -1)
	{
		ret = _mkdir(dirPath.c_str());
		cout << "���ļ��в����ڣ����Զ�����" << endl;
	}
	else
	{
		cout << "���ļ��д���" << endl;
	}
	return ret;
}