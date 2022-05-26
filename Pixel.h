#pragma once
#include"all.h"


using namespace std;
using namespace cv;


class Pixel
{
public:
	Pixel(vector<double> image) { this->img = image; }
	int getCirclePixel(int x, int y, int r); //得到圆形区域平均像素点
	double getRectanglePixel(int x, int y, int lenx, int leny);//得到矩形区域平均像素点
	int getRectangle(int x, int y); //获得矩形区域
	double getCircle(); //获得圆形区域
	double getPixel(int x, int y); //获得该像素点大小

private:
	vector<double> img;
};

