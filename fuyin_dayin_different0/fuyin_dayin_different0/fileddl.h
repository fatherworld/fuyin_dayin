//��������ͷ�ļ������ļ��Ĵ����ж��봴��
#include "direct.h"
#include<io.h>
#include<string>
#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<direct.h>
using namespace std;
//�ж��ļ��Ƿ���ڲ����ڴ���
bool isFileExist(string fname);

//�ж��ļ���·���Ƿ����
int isDirExist(string dirPath);

//��ȡ��ǰ�ļ����ڵ��ļ���·��
char* getCwdPath();