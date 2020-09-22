#include "processImg.h"
#include "prasexml.h"
#include "fileddl.h"
#include <unordered_map>
#include <sstream> //��Ӧ��intתstring��stringstream
//����xml�е�������ȡͼ����ַ�����
int cutRoi_dy(Mat src,vector<p2> p2s,vector<Mat>& Rois)
{
	//�趨ROI����
	int ret = 0;
	
	for(int i = 0;i<p2s.size();i++)
	{
		int width = p2s[i].two.x - p2s[i].one.x;
		int height = p2s[i].two.y - p2s[i].one.y;
		/*cout<<"cur_i"<<i<<endl;
		cout<<"width"<<width<<endl;
		cout<<"height"<<height<<endl;
		*/
		if(p2s[i].one.x<0 || p2s[i].two.x > src.cols 
			|| p2s[i].one.y<0 || p2s[i].one.y > src.rows)
		{
			continue;
		}
		Mat roi = src(Rect(p2s[i].one.x,p2s[i].one.y,width,height));
		if(!roi.data)
		{
			ret = -1;
			return ret;
		}	
		Rois.push_back(roi);
	}
	return ret;
}

//ѡȡ��ͬ�Ĵ�ӡ����ӡ���Ĳ����ַ�
int select_same_char(vector<int> sm_indexs,
	vector<int> fy_indexs,vector<Mat> sm_rois,
	vector<Mat> fy_rois,vector<Mat>& sel_sm_rois,
	vector<Mat>& sel_fy_rois)
{
	int ret = 0;
	if(sm_indexs.size() != fy_indexs.size())
	{
		cout<<"��ӡɨ��ѡ��ıȽ��ַ�����������һ��"<<endl;
		ret = -1;
		return ret;
	}

	for(int i=0;i<sm_indexs.size();i++)
	{
		if(sm_indexs[i] >= sm_rois.size() || 
			sm_indexs[i] < 0)
		{
			cout<<"��ӡɨ��ѡ����ַ�����Խ��"<<endl;
			ret = -2;
			return ret;
		}
		sel_sm_rois.push_back(sm_rois[sm_indexs[i]]);
		sel_fy_rois.push_back(fy_rois[fy_indexs[i]]);
	}
	return ret;
}
//���ڶ�ֵ����ͼ���������ȡ
Mat find_Contours(Mat src,
	vector<vector<Point>>& contours,//���еı�Ե�㼯��
	vector<Vec4i>& hierarchy)
{
	Mat contImg = Mat::zeros(src.size(),src.type());
	int mode = 0;
	int method = 0;


	findContours(src,contours,hierarchy,CV_RETR_CCOMP,CV_CHAIN_APPROX_NONE);

	//���Ʋ��ҵ�������
	drawContours(contImg, contours, -1, Scalar(255));

	return contImg;

}

//��ͼ��λ����Ĳ���
cv::Mat reserve_image(Mat src)
{
	cv::Mat res;
	cv::bitwise_not(src,res);
	return res;
}


//����ͼƬ
cv::Mat resize_process(Mat src,int bs)
{
	Mat res;
	cv::resize(src,res,cv::Size(src.cols*bs,src.rows*bs));
	return res;
}

//���ڶ�ֵͼƬ�ı�Ե������ȡ
int find_edge_points(Mat src,int edgeThresh,Mat& edge,vector<Point>& edge_points)
{
	int ret = 0;
	//blur(src, edge, Size(3,3));
	Canny(src,edge,edgeThresh, edgeThresh*3, 3);


	for(int i=0;i<edge.rows;i++)
	{
		for(int j = 0;j<edge.cols;j++)
		{

			Point edgePoint;
			if(edge.at<uchar>(i,j))
			{
				edgePoint.y = i;
				edgePoint.x = j;
				edge_points.push_back(edgePoint);
			}
			
		}
	}
	return ret;
}


//������ȡ��ԵȻ����ݱ�Ե���о���˵����
int fitting_5_5(Mat src,vector<Mat>& fitting_res)
{
	int ret = 0;
	vector<Point> edge_points;
	Mat edge;
	ret = find_edge_points(src,
		8,
		edge,edge_points);



	/*Mat fitting_55 = (Mat_<int>(5,5)<< 0,0,0,0,0,
		0,0,0,0,0,
		0,0,0,0,0,
		0,0,0,0,0,
		0,0,0,0,0);
	*/
	Mat src_temp = src;


	//imshow("src",src);
	//waitKey(0);
	Mat src_temp1 = Mat::zeros(src.size(),src.type());
	for(int i=0;i<edge_points.size();i++)
	{
		Point temp_cont = edge_points[i];
		
		//ԭͼĬ�ϵ�ͨ����Ϊ1
		int x = temp_cont.x;
		int y = temp_cont.y;
		int tq  = int(src.at<uchar>(y,x));


		Mat fitting_55 = (Mat_<int>(5,5)<< 0,0,0,0,0,
			0,0,0,0,0,
			0,0,255,0,0,
			0,0,0,0,0,
			0,0,0,0,0);
		int p0 = -2;
		int p1 =  3;
		int q0 = -2;
		int q1 =  3;
		
		if(y==1)
			p0=-1;
		if(y==src.rows-2)
			p1=2;
		if(y==0)
			p0 = 0;
		if(y==src.rows-1)
			p1=1;
		if(x==1)
			q0=-1;
		if(x==src.cols-2)
			q1=2;
		if(x==0)
			q0 = 0;
		if(x==src.cols-1)
			q1=1;

		int q00 = q0;

		for(;p0<p1;p0++)
		{
			q0 = q00;
			for(;q0<q1;q0++)
			{	
				int pd = int(src.at<uchar>(y+p0,x+q0));
				//if(pd && q0 > 0 && p0 > 0)
					//cout<<"yes"<<"good point"<<endl;
				if(pd)
					fitting_55.at<int>(p0+2,q0+2) = 255;	 
					
			}
		}
	//	cout<<"fittting55"<<fitting_55<<endl;
		fitting_res.push_back(fitting_55);
	}
	return ret;
}

/*
	�����ַ�����5*5���ַ���Ե����˺�����н��	
	#type-->��ӡ����ӡ������ 0Ϊ��ӡ 1  λ��ӡ
	#vector<Mat> fitting_res--> ��ȡ���������ַ�5*5������
	#char_index--> �ַ��ڶ�Ӧ��xml�ļ��е�����,
*/
int save_fitting_res_img(int type,vector<Mat> fitting_res,int char_index)
{
	int ret = 0;
	string savePath="./fitting_55/";
	if(type == 1)
	{
		savePath+="fy";
	}
	else
		savePath+="sm";
	if(isDirExist(savePath))
	{
		ret = -1;
		return ret;
	}
	stringstream temp;
	temp<<char_index;
	string str_char_index = temp.str();

	savePath = savePath + "/" + str_char_index;
	if(isDirExist(savePath))
	{
		ret = -2;
		return ret;
	}

	//д�����е�fitting55֮��ı�Եͼ��Ӳ��
	for(int i=0;i<fitting_res.size();i++)
	{	
		stringstream s;
		s<<i;
		string filepath = savePath + "/" + s.str()+".jpg";
		cv::imwrite(filepath,fitting_res[i]);
	}
	return ret;
}

//����ͼ��Ҷ������Сֵ
void MaxGrayValue(Mat image,int &max,int &min)
{
	max = 0;
	min = 255;
	Mat *im = reinterpret_cast<Mat*>((void*)&image);
	int height = image.rows;
	int width = image.cols;
	int N = height * width;
	//cout << "125" << " " << "125" << " " << static_cast<int>(im->at<uchar>(Point(182, 190))) << endl;
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if ((static_cast<int>(im->at<uchar>(Point(j, i))))>max)
				max = static_cast<int>(im->at<uchar>(Point(j, i)));
			else if ((static_cast<int>(im->at<uchar>(Point(j, i))))<min)
				min = static_cast<int>(im->at<uchar>(Point(j, i)));
		}
	}
}

//����Ӧ��ֵ ע�������ֻ���ǻҶ�ͼ��
void adapthreshold(Mat &image,int iter_nums)
{
    int max, min;    //����������С�Ҷ�ֵ
    MaxGrayValue(image, max, min);   //����������С�Ҷ�ֵ
    int grayvalue;    //������ʱ��ȡÿ����ĻҶ�ֵ
    int Threshold = (max + min)/2;  //��ʼ��ֵ
    int Temp_Threshold = Threshold; //���ڴ�ȡÿ�ε��������ֵ
    int big_than_th;       //�����ۼӴ�����ֵ�ĻҶ�ֵ
    int bigcount;           //���ڴ�Ŵ�����ֵ�Ҷ�ֵ�����ص�����
    int sma_than_th;       //�����ۼ�С����ֵ�ĻҶ�ֵ
    int smacount;           //���ڴ��С����ֵ�Ҷ�ֵ�����ص�����
    Mat *im = reinterpret_cast<Mat*>((void*)&image);    //��ȡ���ص���Ϣ
    //Mat *im = &image
    int height = image.rows;   //��ȡͼ��߶�
    int width = image.cols;       //��ȡͼ����

    cv::Mat res = cv::Mat(image.size(),image.type());
    for (int k = 0; k < iter_nums; k++)   //������ֵ��������50��,��iter_nums<=50
    {
        big_than_th = 0;    
        bigcount = 0;
        sma_than_th = 0;
        smacount = 0;
        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                grayvalue = static_cast<int>(im->at<uchar>(Point(j, i)));  //��ȡָ����Ҷ�ֵ
                if (grayvalue>Threshold)   //����Ҷ�ֵ������ֵ���ӵ��ܻҶ�ֵ������+1
                {
                    big_than_th += grayvalue;
                    bigcount++;
                }
                else if (grayvalue < Threshold) //����Ҷ�ֵС����ֵ���ӵ��ܻҶ�ֵ������+1
                {
                    sma_than_th += grayvalue;
                    smacount++;
                }
            }
        }
        Temp_Threshold = ((big_than_th*1.0 / bigcount) + (sma_than_th*1.0 / smacount)) / 2;  //�����µ���ֵ
        if (abs(Temp_Threshold - Threshold) < 2)   //����µ���ֵ�;ɵ���ֵ��ֵ�ľ���ֵС��10�����˳�
            break;
        else
            Threshold = Temp_Threshold;    //�������ֵ��������ֵ
    }
    for (int i = 0; i < height; i++)     //��ͼ����ж�ֵ������
    {
        uchar* data = res.ptr<uchar>(i);
        for (int j = 0; j < width; j++)
        {
            //grayvalue = static_cast<int>(im->at<uchar>(Point(j, i)));
			grayvalue = static_cast<int>(im->at<uchar>(i,j));
            if (grayvalue>=Threshold)
                data[j] = 255;
            else if (grayvalue < Threshold)
                data[j] = 0;
        }
    }
}

//����ͼ��Ķ�ֵ��
double threshold_img(Mat src,Mat& dst,double thresh,int maxthresh=255)
{
	double res = 0.0f;
	res = cv::threshold(  
		src, // ����ͼ�� 
		dst, // ���ͼ��  
		thresh, // ��ֵ  
		maxthresh, // �������ֵĬ��Ϊ255  
		THRESH_BINARY 			// ��ֵ������������   
		);
	return res;
}

//�ж�ͼ���Ƿ��Ƕ�ֵͼ��
bool is_binary_img(Mat src)
{
	bool is_binary = true;
	for(int i=0;i<src.rows;i++)
	{
		for(int j=0;j<src.cols;j++)
		{
			int temp = (int)src.at<uchar>(i,j);
			if(0<temp && temp < 255)
			{
				is_binary = false;
				return is_binary;
			}
		}
	}
	return is_binary;
}

//����hash_map�е�key����ʹ��cv::
class mat_
{
public:
	cv::Mat t_m;
	mat_(cv::Mat m)
	{
		this->t_m = m;
	}
	bool operator==(const cv::Mat& m1) const{
		if(this->t_m.cols != m1.cols ||
			this->t_m.rows != m1.rows)
		{
			return false;
		}
		for(int i=0;i<t_m.rows;i++)
		{
			for(int j=0;j<t_m.cols;j++)
			{
				int t1 = this->t_m.at<int>(i,j);
				int t2 = m1.at<int>(i,j);
				if(t1!=t2)
					return false;
			}
		}	
		return true;
	}
};

/*struct hash_name{
	bool operator()(const mat_ & p) const{
		return  hash<cv::Mat>()(p.t_m);
	}
};
*/
/*void test_my_hash()
{
	unordered_map<cv::Mat,int,hash_name> umap;
	int res = 0;
	int ret = 0;

	unordered_map<mat_, int,hash_name> ids; //����Ҫ�ѹ�ϣ�������빹����
	cv::Mat m1 = (Mat_<int>(2,2)<<1,2,3,4);
	cv::Mat m2 = (Mat_<int>(2,2)<<2,2,3,4);
	cv::Mat m3 = (Mat_<int>(2,2)<<2,2,2,4);
	ids[m1]=1;
	ids[m2]=2;
	ids[m3]=3;
	for ( auto ii = ids.begin() ; ii != ids.end() ; ii++ )
		cout << ii->first.t_m
		<< " : " << ii->second
		<< endl;

}*/

//��5*5�����ӵ�ÿһ�����������������
void sort_55(vector<vector<Mat>> fitting_res,vector<int>& sort_max_index)
{
	vector<int> class_counts;
	for(int i = 0;i< fitting_res.size();i++)
	{
		class_counts.push_back(fitting_res[i].size());
	}
	
	for(int i =0;i<class_counts.size()-1;i++)
	{
		int max_count = i;
		int cur_count = class_counts[i];
		for(int j=i+1;j<class_counts.size();j++)
		{
			if(cur_count < class_counts[j])
			{
				cur_count = class_counts[j];
				max_count = j;
			}
		}
		if(max_count != i)
		{
			int temp = class_counts[max_count];
			class_counts[max_count] = class_counts[i];
			class_counts[i] = temp;
		}
		sort_max_index.push_back(max_count);
	}
}



//ͳ��ÿһ��5*5�����ӵ�ÿһ���������
//type==0 ��ʾ�Ǵ�ӡ������
//type==1 ��ʾ�Ǹ�ӡ������
int static_5_5_classes(int type,vector<Mat> fitting_res,int char_index)
{
	vector< vector<Mat> > class_numbers;
	int ret = 0;
	string savePath="./fitting55/sum_classes/";
	if(type == 1)
	{
		savePath+="fy";
	}
	else
		savePath+="sm";
	if(isDirExist(savePath))
	{
		ret = -1;
		return ret;
	}
	stringstream temp;
	temp<<char_index;
	string str_char_index = temp.str();

	savePath = savePath + "/" + str_char_index;
	if(isDirExist(savePath))
	{
		ret = -2;
		return ret;
	}
	//��ȡÿһ��fitting55��ͬ�ĸ�������
	for(int i=0;i<fitting_res.size();i++)
	{
		cv::Mat cur_i = fitting_res[i];
		vector<Mat>* signal_class_numbers;
		bool is_selected = false;
		for(int p =0;p<class_numbers.size();p++)
		{
			signal_class_numbers=
				&(class_numbers[p]);
			for(int q =0;q<signal_class_numbers->size();q++)
			{
				Mat q_temp = (*signal_class_numbers)[q];
				Mat diff = cur_i - q_temp;
				if(!cv::countNonZero(diff))
				{
					signal_class_numbers->push_back(cur_i);
					is_selected = true;
					break;
				}					
			}
			if(is_selected)
				break;
		}
		if(is_selected)
			continue;
		else
		{
			vector<Mat> signal_new_class_numbers;

			signal_new_class_numbers.push_back(cur_i);

			class_numbers.push_back(signal_new_class_numbers);
		}
	}
	vector<int> sort_max_index;
	sort_55(class_numbers,sort_max_index);
	for(int i =0;i<sort_max_index.size();i++)
	{
		int count_ = class_numbers[i].size();

		cv::Mat class_mat = class_numbers[i][0];
		//Ȼ�󱣴���ļ�����ʽ
		stringstream temp,tmp;
		temp<<count_;
		string str_char_index = temp.str();
		tmp<<i;
		string str_i_index = tmp.str();
		string savePath1 = savePath + "/" +str_char_index+"_"+ str_i_index;
		/*
		if(isDirExist(savePath1))
		{
			ret = -2;
			return ret;
		}
		*/
		string imgpath = savePath1+".jpg";
		imwrite(imgpath,class_mat);
	}
	return ret;
}
