#include "graph.h"


void gray()
{
	// ������ͷ������Ƶ
	VideoCapture capture(1);
	while (1)
	{
		Mat frame;								//����һ��Mat���������ڴ洢ÿһ֡��ͼ��
		capture >> frame;						//��ȡ��ǰ֡    
		// resize(frame, frame, Size(360, 240));	//�ı�ͼ���С
		cvtColor(frame, frame, COLOR_BGR2GRAY);		//תΪ�Ҷ�ͼ
		imshow("aa", frame);
		waitKey(1);							//��ʱ30ms
	}
}



void conv()
{
	VideoCapture capture(1);	// ������ͷ������Ƶ
	while (1)
	{
		Mat frame; //����һ��Mat���������ڴ洢ÿһ֡��ͼ��
		capture >> frame;  //��ȡ��ǰ֡  

		Mat element = getStructuringElement(MORPH_RECT, Size(15, 15));	//�Զ�������
		morphologyEx(frame, frame, MORPH_OPEN, element);

		imshow("A", frame);
		waitKey(30); //��ʱ30ms
	}
}

void on_trackbar(int, void*) {}

void cap()
{
	int alpha_slider1, alpha_slider2;
	namedWindow("[��]");
	createTrackbar("Cmin", "[��]", &alpha_slider1, 255, on_trackbar);
	createTrackbar("Cmax", "[��]", &alpha_slider2, 255, on_trackbar);
	VideoCapture capture(1);	// ������ͷ������Ƶ
	while (1)
	{
		Mat frame; //����һ��Mat���������ڴ洢ÿһ֡��ͼ��
		capture >> frame;  //��ȡ��ǰ֡  
		imshow("ԭͼ", frame);

		cvtColor(frame, frame, COLOR_BGR2GRAY);	//ת��Ϊ�Ҷ�ͼ
		Canny(frame, frame, alpha_slider1, alpha_slider2);

		imshow("[��]", frame);
		waitKey(30); //��ʱ30ms
	}
}



void profile()
{

	int alpha_slider1 = 50, alpha_slider2 = 50;
	namedWindow("[��]");
	createTrackbar("Cmin", "[��]", &alpha_slider1, 255, on_trackbar);
	createTrackbar("Cmax", "[��]", &alpha_slider2, 255, on_trackbar);
	VideoCapture capture(1);	//��1��������ͷ������Ƶ
	while (1)
	{
		Mat frame; //����һ��Mat���������ڴ洢ÿһ֡��ͼ��
		Mat dst;
		capture >> frame;  //��ȡ��ǰ֡  

		cvtColor(frame, frame, COLOR_RGB2GRAY);	//ת��Ϊ�Ҷ�ͼ
		Canny(frame, frame, alpha_slider1, alpha_slider2);
		vector<vector<Point>> contours;
		cv::findContours(
			frame,
			contours,
			cv::noArray(),
			cv::RETR_LIST,
			/*cv::RETR_EXTERNAL����ʾֻ��ȡ�������������
			cv::RETR_LIST����ʾ��ȡ������������������б�
			cv::RETR_CCOMP:��ʾ��ȡ��������������֯��һ������ṹ�����ж����������ⲿ�������ڶ��������ǡ�������������
			cv::RETR_TREE����ʾ��ȡ������������֯������Ƕ�׵������㼶�ṹ��*/
			cv::CHAIN_APPROX_TC89_L1
			/*cv::CHAIN_APPROX_NONE���������е����е�ı���ת���ɵ㣻
			cv::CHAIN_APPROX_SIMPLE��ѹ��ˮƽ����ֱ�ͶԽ�ֱ�߶Σ����������ǵĶ˵㣻
			cv::CHAIN_APPROX_TC89_L1 or cv::CHAIN_APPROX_TC89_KCOS��Ӧ��Teh-Chin�������㷨�е�һ�ַ��*/
		);
		dst = frame.clone();
		dst = cv::Scalar::all(0);		//����ȫ��ͼ��
		cv::drawContours(dst, contours, -1, cv::Scalar::all(255));	//���ư�ɫ����

		imshow("A", frame);		//ԭcanny�˲�ͼ��
		imshow("B", dst);		//��frame�����������Ҳ����»��Ƶ�ͼ��
		waitKey(30); //��ʱ30ms
	}
}