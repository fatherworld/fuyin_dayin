#pragma once
#include<iostream>
#include<opencv2/opencv.hpp>
#include "prasexml.h"

using namespace cv;

using namespace std;

//根据xml中的坐标框截取图像的字符区域
int cutRoi_dy(Mat src,vector<p2> p2s,vector<Mat>& Rois);


//选取相同的打印件复印件的测试字符
int select_same_char(vector<int> sm_indexs,
	vector<int> fy_indexs,vector<Mat> sm_rois,
	vector<Mat> fy_rois,vector<Mat>& sel_sm_rois,
	vector<Mat>& sel_fy_rois);

//缩放图片
cv::Mat resize_process(Mat src,int bs);


//将图按位反向的操作
cv::Mat reserve_image(Mat src);

//进行图像边缘的卷积拟合
int fitting_5_5(Mat src,vector<Mat>& fitting_res);

//基于二值化的图像的轮廓提取
Mat find_Contours(Mat src,
	vector<vector<Point>>& contours,//所有的边缘点集合
	vector<Vec4i>& hierarchy);

//查找图像的边缘坐标点
int find_edge_points(Mat src,int edgeThresh,Mat& edge,vector<Point>& edge_points);

/*
	保存字符根据5*5对字符边缘卷积核后的所有结果	
	#type-->打印机复印机类型 0为打印 1  位复印
	#vector<Mat> fitting_res--> 获取到的所有字符5*5卷积结果
	#char_index--> 字符在对应的xml文件中的索引,
*/
int save_fitting_res_img(int type,vector<Mat> fitting_res,int char_index);


//计算图像灰度最大最小值
void MaxGrayValue(Mat image,int &max,int &min);

//自适应阈值 注：传入的只能是灰度图像
void adapthreshold(Mat &image,int iter_nums);

//进行图像的二值化
double threshold_img(Mat src,Mat dst,double thresh);

//判断图像是否是二值图像
bool is_binary_img(Mat src);

//统计每一个5*5核算子的类别数
int static_5_5_classes(int type,vector<Mat> fitting_res,int char_index);