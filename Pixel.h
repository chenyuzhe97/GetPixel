#pragma once
#include"all.h"


using namespace std;
using namespace cv;


class Pixel
{
public:
	Pixel(vector<double> image) { this->img = image; }
	int getCirclePixel(int x, int y, int r); //�õ�Բ������ƽ�����ص�
	double getRectanglePixel(int x, int y, int lenx, int leny);//�õ���������ƽ�����ص�
	int getRectangle(int x, int y); //��þ�������
	double getCircle(); //���Բ������
	double getPixel(int x, int y); //��ø����ص��С

private:
	vector<double> img;
};

