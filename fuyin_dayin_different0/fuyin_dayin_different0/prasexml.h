#include "tinystr.h"
#pragma once
#include "tinyxml.h"
#include <iostream>
#include <string>
#include<opencv2/opencv.hpp>

using namespace cv;
using namespace std;

//��ȡxml�е��ļ����
typedef struct point_2{
	Point one;
	Point two;
}p2;
int getXmlPoint2s(string xmlpath,vector<p2>& p2s,int& charNumbers);
