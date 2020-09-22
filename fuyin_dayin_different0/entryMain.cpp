#include "prasexml.h"
#include "processImg.h"
//int getXmlPoint2s(string xmlpath,vector<p2>& p2s,int& charNumbers)
int main_1(int argv,char* argc[])
{
	string smimgpath = "./TesXml_Pic/pic/一次扫描.jpg";
	string fyimgpath = "./TesXml_Pic/pic/一次复印.jpg";
	string xmlpath_fy = "./TestXml/xmlFiles/一次复印_jpg.xml";
	string xmlpath_sm = "./TestXml/xmlFiles/一次扫描_jpg.xml";
	Mat sm_img = cv::imread(smimgpath,-1);
	Mat fy_img = cv::imread(fyimgpath,-1);
	//Mat roi1 = sm_img(Rect(750,764,116,90));
	//Mat roi2 = sm_img(Rect(764,750,90,116));
	//imshow("uuu",sm_img);
	//waitKey(0);

	vector<Mat> sm_rois,fy_rois;
	
	vector<p2> p2s_sm;
	vector<p2> p2s_fy;
	int charNumbers_sm,charNumbers_fy;
	charNumbers_sm=charNumbers_fy=-1;
	int res_sm,res_fy;
	res_sm=res_fy=-1;

	//获取sm图片的所有坐标框位置
	res_sm = getXmlPoint2s(xmlpath_sm,p2s_sm,charNumbers_sm);
	assert(charNumbers_sm == p2s_sm.size());
	//获取fy图片的所有坐标框位置
	res_fy = getXmlPoint2s(xmlpath_fy,p2s_fy,charNumbers_fy);
	assert(charNumbers_fy == p2s_fy.size());
	
	

	res_fy = cutRoi_dy(fy_img,p2s_fy,fy_rois);
	res_sm = cutRoi_dy(sm_img,p2s_sm,sm_rois);

	cout<<"roi的通道数为"<<endl;

	cout<<sm_rois[0].channels()<<endl;

	int for_each_number = (charNumbers_fy<charNumbers_sm?charNumbers_fy:charNumbers_sm);
/*
	for(int i = 0;i<for_each_number;i++)
	{
		cv::Mat temp_fy = fy_rois[i];
		cv::Mat temp_sm = sm_rois[i];
	}
*/




	cout<<"finished "<<endl;



	return 0;

}


