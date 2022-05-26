#include "graph.h"


void gray()
{
	// 从摄像头读入视频
	VideoCapture capture(1);
	while (1)
	{
		Mat frame;								//定义一个Mat变量，用于存储每一帧的图像
		capture >> frame;						//读取当前帧    
		// resize(frame, frame, Size(360, 240));	//改变图像大小
		cvtColor(frame, frame, COLOR_BGR2GRAY);		//转为灰度图
		imshow("aa", frame);
		waitKey(1);							//延时30ms
	}
}



void conv()
{
	VideoCapture capture(1);	// 从摄像头读入视频
	while (1)
	{
		Mat frame; //定义一个Mat变量，用于存储每一帧的图像
		capture >> frame;  //读取当前帧  

		Mat element = getStructuringElement(MORPH_RECT, Size(15, 15));	//自定义卷积核
		morphologyEx(frame, frame, MORPH_OPEN, element);

		imshow("A", frame);
		waitKey(30); //延时30ms
	}
}

void on_trackbar(int, void*) {}

void cap()
{
	int alpha_slider1, alpha_slider2;
	namedWindow("[总]");
	createTrackbar("Cmin", "[总]", &alpha_slider1, 255, on_trackbar);
	createTrackbar("Cmax", "[总]", &alpha_slider2, 255, on_trackbar);
	VideoCapture capture(1);	// 从摄像头读入视频
	while (1)
	{
		Mat frame; //定义一个Mat变量，用于存储每一帧的图像
		capture >> frame;  //读取当前帧  
		imshow("原图", frame);

		cvtColor(frame, frame, COLOR_BGR2GRAY);	//转化为灰度图
		Canny(frame, frame, alpha_slider1, alpha_slider2);

		imshow("[总]", frame);
		waitKey(30); //延时30ms
	}
}



void profile()
{

	int alpha_slider1 = 50, alpha_slider2 = 50;
	namedWindow("[总]");
	createTrackbar("Cmin", "[总]", &alpha_slider1, 255, on_trackbar);
	createTrackbar("Cmax", "[总]", &alpha_slider2, 255, on_trackbar);
	VideoCapture capture(1);	//【1】从摄像头读入视频
	while (1)
	{
		Mat frame; //定义一个Mat变量，用于存储每一帧的图像
		Mat dst;
		capture >> frame;  //读取当前帧  

		cvtColor(frame, frame, COLOR_RGB2GRAY);	//转化为灰度图
		Canny(frame, frame, alpha_slider1, alpha_slider2);
		vector<vector<Point>> contours;
		cv::findContours(
			frame,
			contours,
			cv::noArray(),
			cv::RETR_LIST,
			/*cv::RETR_EXTERNAL：表示只提取最外面的轮廓；
			cv::RETR_LIST：表示提取所有轮廓并将其放入列表；
			cv::RETR_CCOMP:表示提取所有轮廓并将组织成一个两层结构，其中顶层轮廓是外部轮廓，第二层轮廓是“洞”的轮廓；
			cv::RETR_TREE：表示提取所有轮廓并组织成轮廓嵌套的完整层级结构。*/
			cv::CHAIN_APPROX_TC89_L1
			/*cv::CHAIN_APPROX_NONE：将轮廓中的所有点的编码转换成点；
			cv::CHAIN_APPROX_SIMPLE：压缩水平、垂直和对角直线段，仅保留它们的端点；
			cv::CHAIN_APPROX_TC89_L1 or cv::CHAIN_APPROX_TC89_KCOS：应用Teh-Chin链近似算法中的一种风格*/
		);
		dst = frame.clone();
		dst = cv::Scalar::all(0);		//创建全黑图像
		cv::drawContours(dst, contours, -1, cv::Scalar::all(255));	//绘制白色轮廓

		imshow("A", frame);		//原canny滤波图像
		imshow("B", dst);		//对frame进行轮廓查找并重新绘制的图像
		waitKey(30); //延时30ms
	}
}