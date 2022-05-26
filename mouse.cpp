#include "mouse.h"

vector<string> files;


void onMouseMul(int event, int x, int y, int flags, void* param)  //evnet:鼠标事件类型 x,y:鼠标坐标 flags：鼠标哪个键
{
	Mat* im = reinterpret_cast<Mat*>(param);
	switch (event) {

	case EVENT_LBUTTONDOWN:
		//显示图像像素值

		if (static_cast<int>(im->channels()) == 1)
		{
			int sum = 0;
			//若图像为灰度图像，则显示鼠标点击的坐标以及灰度值
			for (int i = 0; i < files.size(); i++)
			{
				Mat pic = imread(files[i]);
				sum += static_cast<int>((&pic)->at<uchar>(Point(x, y)));
			}
			sum = sum / files.size();
			cout << "at (" << x << ", " << y << " ) value is: " << sum << endl;
		}
		else
		{
			int sumB = 0, sumG = 0, sumR = 0;
			//若图像为彩色图像，则显示鼠标点击坐标以及对应的B, G, R值
			for (int i = 0; i < files.size(); i++)
			{
				Mat pic = imread(files[i]);
				sumB += static_cast<int>((&pic)->at<Vec3b>(Point(x, y))[0]);
				sumG += static_cast<int>((&pic)->at<Vec3b>(Point(x, y))[1]);
				sumR += static_cast<int>((&pic)->at<Vec3b>(Point(x, y))[2]);
			}
			sumB = sumB / files.size();
			sumG = sumG / files.size();
			sumR = sumR / files.size();
			cout << "at (" << x << ", " << y << ")"
				<< "  B value is: " << sumB
				<< "  G value is: " << sumG
				<< "  R value is: " << sumR
				<< endl;
		}

		break;
	}
}

void onMouse(int event, int x, int y, int flags, void* param)  //evnet:鼠标事件类型 x,y:鼠标坐标 flags：鼠标哪个键
{
	Mat* im = reinterpret_cast<Mat*>(param);
	switch (event) {

	case EVENT_LBUTTONDOWN:
		//显示图像像素值

		if (static_cast<int>(im->channels()) == 1)
		{
			//若图像为灰度图像，则显示鼠标点击的坐标以及灰度值
			cout << "at (" << x << ", " << y << " ) value is: " << static_cast<int>(im->at<uchar>(Point(x, y))) << endl;
		}
		else
		{
			//若图像为彩色图像，则显示鼠标点击坐标以及对应的B, G, R值
			cout << "at (" << x << ", " << y << ")"
				<< "  B value is: " << static_cast<int>(im->at<Vec3b>(Point(x, y))[0])
				<< "  G value is: " << static_cast<int>(im->at<Vec3b>(Point(x, y))[1])
				<< "  R value is: " << static_cast<int>(im->at<Vec3b>(Point(x, y))[2])
				<< endl;
		}

		break;
	}
}





/*

int opengraph()
{
	Mat image1 = imread("1.jpg");  //读取图像；
	if (image1.empty())
	{
		cout << "读取错误" << endl;
		return -1;
	}
	imshow("image1", image1);  //显示图像；


	setMouseCallback("image1", onMouse, reinterpret_cast<void*>(&image1)); //关联图像显示窗口和onMouse函数
	waitKey(0);  //暂停，保持图像显示，等待按键结束

	return 0;
}

*/

int opengraph(string name)
{
	if (name.empty())
		name = "1.jpg";

	Mat image1 = imread(name);  //读取图像；
	if (image1.empty())
	{
		cout << "读取错误" << endl;
		return -1;
	}
	namedWindow("image1", WINDOW_NORMAL);
	imshow("image1", image1);  //显示图像；


	setMouseCallback("image1", onMouse, reinterpret_cast<void*>(&image1)); //关联图像显示窗口和onMouse函数
	waitKey(0);  //暂停，保持图像显示，等待按键结束

	return 0;
}

int opengraphmul(string name)
{
	
	if (name.empty())
		name = "1.jpg";
	Mat image1 = imread(name);  //读取图像；
	if (image1.empty())
	{
		cout << "读取错误" << endl;
		return -1;
	}
	namedWindow("image1", WINDOW_NORMAL);
	imshow("image1", image1);  //显示图像；
	setMouseCallback("image1", onMouseMul, reinterpret_cast<void*>(&image1)); //关联图像显示窗口和onMouse函数
	waitKey(0);  //暂停，保持图像显示，等待按键结束

	return 0;
}


void getAllFiles(string path, vector<string>& files, string format)
{
	intptr_t  hFile = 0;//文件句柄  64位下long 改为 intptr_t
	struct _finddata_t fileinfo;//文件信息 
	string p;
	if ((hFile = _findfirst(p.assign(path).append("\\*" + format).c_str(), &fileinfo)) != -1) //文件存在
	{
		do
		{
			if ((fileinfo.attrib & _A_SUBDIR))//判断是否为文件夹
			{
				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)//文件夹名中不含"."和".."
				{
					files.push_back(p.assign(path).append("\\").append(fileinfo.name)); //保存文件夹名
					getAllFiles(p.assign(path).append("\\").append(fileinfo.name), files, format); //递归遍历文件夹
				}
			}
			else
			{
				files.push_back(p.assign(path).append("\\").append(fileinfo.name));//如果不是文件夹，储存文件名
			}
		} while (_findnext(hFile, &fileinfo) == 0);
		_findclose(hFile);
	}
}

void getFilesName(string filePath = "./")
{
	string format = "";				 //查找文件的格式
	getAllFiles(filePath, files, format);
	int size = files.size();
	for (int i = 0; i < size; i++)
	{
		cout << files[i] << endl;
	}
	system("pause");
}