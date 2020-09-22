#include "prasexml.h"
#include "processImg.h"
#include "fileddl.h"
//int getXmlPoint2s(string xmlpath,vector<p2>& p2s,int& charNumbers)
int main(int argv,char* argc[])
{
	char* cwd = getCwdPath();
	if(cwd)
	{
		free(cwd);
		cwd = NULL;
	}
		
	string smimgpath = "./TesXml_Pic/pic/sm_tmpImg.bmp";
	string fyimgpath = "./TesXml_Pic/pic/fy_tmpImg.bmp";
	string xmlpath_fy = "./TestXml/xmlFiles/һ�θ�ӡ_jpg.xml";
	string xmlpath_sm = "./TestXml/xmlFiles/һ��ɨ��_jpg.xml";
	Mat sm_img = cv::imread(smimgpath,-1);

	Mat fy_img = cv::imread(fyimgpath,-1);

	bool res_sm_ib = is_binary_img(sm_img);
	bool res_fy_ib = is_binary_img(fy_img);

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

	//��ȡsmͼƬ�����������λ��
	res_sm = getXmlPoint2s(xmlpath_sm,p2s_sm,charNumbers_sm);
	assert(charNumbers_sm == p2s_sm.size());
	//��ȡfyͼƬ�����������λ��
	res_fy = getXmlPoint2s(xmlpath_fy,p2s_fy,charNumbers_fy);
	assert(charNumbers_fy == p2s_fy.size());
	
	

	res_fy = cutRoi_dy(fy_img,p2s_fy,fy_rois);
	res_sm = cutRoi_dy(sm_img,p2s_sm,sm_rois);

	cout<<"roi��ͨ����Ϊ"<<endl;

	cout<<sm_rois[0].channels()<<endl;

	int for_each_number = (charNumbers_fy<charNumbers_sm?charNumbers_fy:charNumbers_sm);

	for(int i = 0;i<for_each_number;i++)
	{
		cv::Mat temp_fy = fy_rois[i];
		cv::Mat temp_sm = sm_rois[i];
	}


	vector<Mat> sel_fy_rois,sel_sm_rois; //���vector�ַ�list
	vector<int> fy_indexs,sm_indexs;
	int char_index_sm = 23;
	int char_index_fy = 17;
	fy_indexs.push_back(char_index_fy);
	sm_indexs.push_back(char_index_sm);


	//ѡ���ӡ���͸�ӡ��ͬһ���ַ�ͼƬ���в���
	int ret = select_same_char(sm_indexs,
		fy_indexs,sm_rois,
		fy_rois,sel_sm_rois,
		sel_fy_rois);

	//ѡ���ŵĸ�ӡ�ʹ�ӡ��ͬ�ַ�
	Mat pic_sm = sel_sm_rois[0];
	Mat pic_fy  = sel_fy_rois[0];

	pic_sm =  reserve_image(pic_sm);
	pic_fy =  reserve_image(pic_fy);

	imwrite("jian_fy.jpg",pic_fy);

	imwrite("jian_sm.jpg",pic_sm);

	bool res = is_binary_img(pic_sm);


	bool res1 = is_binary_img(pic_fy);


	//��ͼƬ����һ���̶ȵķ���,��������ͼ���ɷǶ�ֵ��ͼ��
	Mat resize_pic_sm = resize_process(pic_sm,10);
	Mat resize_pic_fy = resize_process(pic_fy,10);
	res = is_binary_img(resize_pic_sm);


	res1 = is_binary_img(resize_pic_fy);

	//����λͼ����Ĳ���
	Mat resize_pic_sm_res = reserve_image(pic_sm);
	Mat resize_pic_fy_res = reserve_image(pic_fy);

	res = is_binary_img(resize_pic_sm_res);


	res1 = is_binary_img(resize_pic_fy_res);


	vector<Mat> fitting_res_sm,fitting_res_fy;
	//��ȡ����ͼƬ�ı�Ե
	ret = fitting_5_5(resize_pic_sm_res,fitting_res_sm);
	ret = fitting_5_5(resize_pic_fy_res,fitting_res_fy);
	//Mat test = fitting_res[0];
	//cv::resize(test,test,Size(8*test.rows,8* test.cols));
	//imshow("res img",test);
	//waitKey(0);
	//ret = fitting_5_5(resize_pic_sm_res,fitting_res);


	int type_sm = 0;
	int type_fy = 1;
	int res11 = static_5_5_classes(type_sm,fitting_res_sm,char_index_sm);
	int res12 = static_5_5_classes(type_fy,fitting_res_fy,char_index_fy);
	//int ret1 = save_fitting_res_img(type_sm,fitting_res_sm,char_index_sm);
///	int ret2 = save_fitting_res_img(type_fy,fitting_res_fy,char_index_fy);
	cout<<"finished "<<endl;

	return 0;

}


