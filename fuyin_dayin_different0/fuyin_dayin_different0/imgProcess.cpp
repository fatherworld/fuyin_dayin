
/*#include<iostream>
#include<opencv2/opencv.hpp>
using namespace cv;

using namespace std;
#define MAX_ALPHA 5
//截取扫描图像的roi区域
cv::Mat cutRoi_dy(Mat src)
{
	//设定ROI区域
	Mat roi = src(Rect(src.cols-2300,src.rows-2100,250,100));
	return roi;
	
}

//截取复印图像的roi区域
cv::Mat cutRoi_fy(Mat src)
{
	//设定ROI区域
	Mat roi = src(Rect(src.cols-2300,src.rows-2070,250,100));
	return roi;

}

//缩放图片
cv::Mat resize_process(Mat src)
{
	Mat res;
	cv::resize(src,res,cv::Size(src.cols*10,src.rows*10));
	return res;
}

//灰度化&二值化
cv::Mat gray_bin(Mat src,int threshold_num)
{
	Mat res;
	cv::cvtColor(src,res,COLOR_BGR2GRAY);
	threshold(res,res, threshold_num,255, 	THRESH_BINARY);
	return res;
}

//二值化
cv::Mat just_bin(Mat src,int threshold_num)
{
	Mat res;
	//cv::cvtColor(src,res,COLOR_BGR2GRAY);
	threshold(src,res, threshold_num,255, 	THRESH_BINARY);
	return res;
}

//将图按位反向的操作
cv::Mat reserve_image(Mat src)
{
	cv::Mat res;
	cv::bitwise_not(src,res);
	return res;

}

//基于二值化的图像的边缘提取
Mat find_edge(Mat src)
{
	Mat contImg = Mat::zeros(src.size(),src.type());

	vector<vector<Point>> contours;//所有的边缘集合
	vector<Vec4i> hierarchy; 

	int mode = 0;
	int method = 0;


	findContours(src,contours,hierarchy,CV_RETR_CCOMP,CV_CHAIN_APPROX_NONE);


	//绘制查找到的轮廓
	drawContours(contImg, contours, -1, Scalar(255));

	return contImg;

}

//调试查找边缘的不同参数
void trackbarHandle(int mode,void* img)
{
	Mat temp = *(static_cast<Mat*>(img));

	Mat contImg = Mat::zeros(temp.size(),temp.type());

	vector<vector<Point>> contours;//所有的边缘集合
	vector<Vec4i> hierarchy; 

	findContours(temp,contours,hierarchy,mode,CV_CHAIN_APPROX_NONE);
	//绘制查找到的轮廓
	drawContours(contImg, contours, -1, Scalar(255));
	imshow("edge",contImg);


}

//动态查找图像边缘的入口函数
void find_edge_dyn(Mat src)
{
	int mode;//滑动条当前值

	//创建窗体
	namedWindow("edge",0);
	mode = 0;
	Mat contImg = Mat::zeros(src.size(),src.type());
	vector<vector<Point>> contours;//所有的边缘集合
	vector<Vec4i> hierarchy; 

	findContours(src,contours,hierarchy,mode,CV_CHAIN_APPROX_NONE);
	//绘制查找到的轮廓
	drawContours(contImg, contours, -1, Scalar(255));
	imshow("edge",contImg);

	//设置滑动条当前值
	//在窗体中添加滑动条，注意最后参数的传递，避免的全局变量
	createTrackbar("模式", "edge", &mode,MAX_ALPHA,trackbarHandle,&src);
	
	waitKey(0);
	
}

//opencv实现两幅图像并排合并
cv::Mat megerImage(Mat img1,Mat img2) 
{
	int h1 = img1.rows;
	int w1 = img1.cols;
	int h2 = img2.rows;
	int w2 = img2.cols;
	//将图像等比例缩放与图像高度一致
	if(h1 > h2)
	{
		int resize_w1 = float(w1/h1) * h2;

		cv::resize(img1,img1,cv::Size(resize_w1,h2));
	}
	else if(h2 > h1)
	{
		int resize_w2 = float(w2/h2) * h1;
		cv::resize(img2,img2,cv::Size(resize_w2,h1));
	}
	int height = (h1> h2 ? h2:h1);
	//创建目标Mat
	Mat dst;
	dst.create(height,w1+w2,img1.type());
	Mat r1 = dst(Rect(0,0,w1,height)); 
	img1.copyTo(r1);
	Mat r2 =  dst(Rect(w1,0,w2,height));
	img2.copyTo(r2);
	
	return dst;
}


//测试合并起立的同一张图
int test_one_pic(Mat onepic)
{
	Mat resize_img;
	resize_img =  resize_process(onepic);

	Mat resize_gray_bin = gray_bin(resize_img,128);


	Mat rs_gray_bin_not = reserve_image(resize_gray_bin);

	Mat rs_gray_bin_not_edge = find_edge(rs_gray_bin_not);


	return 0;
}






int main11()

{

	//read the image

	Mat fy_image = imread("./Test_Pictures/fangzhengsongti/一次复印.jpg");
	Mat sm_image = imread("./Test_Pictures/fangzhengsongti/一次扫描.jpg");
	cout<<"sm_image.cols"<<sm_image.cols<<endl;
	cout<<"sm_image.rows"<<sm_image.rows<<endl;
	cout<<"sm_image.cols"<<sm_image.cols<<endl;
	cout<<"sm_image.rows"<<sm_image.rows<<endl;

	//截取感兴趣区域
	Mat sm_roi = cutRoi_dy(sm_image);
	Mat fy_roi = cutRoi_fy(fy_image);

	//将两张图片合并成一张图片
	Mat dst  = megerImage(sm_roi,fy_roi);

	int res = test_one_pic(dst);
	



	//进行图像的放缩
	Mat sm_roi_rs = resize_process(sm_roi);
	Mat fy_roi_rs = resize_process(fy_roi);

	//图像只进行二值化不进行灰度化
	Mat sm_roi_rs_bin = just_bin(sm_roi_rs,128);
	Mat fy_roi_rs_bin = just_bin(fy_roi_rs,128);



	//将图像进行灰度化和二值化
	Mat sm_roi_rs_gray_bin = gray_bin(sm_roi_rs,128);
	Mat fy_roi_rs_gray_bin = gray_bin(fy_roi_rs,128);

	//再将图像进行按位图反向
	Mat sm_roi_rs_gray_bin_not = reserve_image(sm_roi_rs_gray_bin);
	Mat fy_roi_rs_gray_bin_not = reserve_image(fy_roi_rs_gray_bin);

	Mat sm_roi_rs_gray_bin_edge = find_edge(sm_roi_rs_gray_bin_not);
	Mat fy_roi_rs_gray_bin_edge = find_edge(fy_roi_rs_gray_bin_not);

	//find_edge_dyn(sm_roi_rs_gray_bin_not);

	if (fy_image.data != NULL)
	{

		//show the image

		imshow("clock", fy_image);

		waitKey(0);

	}

	else

	{

		cout << "can&apos;t openc the file!" << endl;

		getchar();

	}

	cv::imshow("sm_roi",sm_roi);
	cv::imshow("fy_roi",fy_roi);

	waitKey(0);



	return 0;
}
*/