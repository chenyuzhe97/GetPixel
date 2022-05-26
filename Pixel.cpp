#include "Pixel.h"

int Pixel::getCirclePixel(int x, int y, int r)
{
    return 0;
}

double Pixel::getRectanglePixel(int x, int y, int lenx, int leny)
{
    int area = lenx * leny;
    double sum = 0;
    for (int i = x - lenx / 2; i < x + lenx / 2; i++) {
        for (int j = y - leny / 2; j < y + leny / 2; j++) {
            sum += getPixel(i, j);
        }
    }
    return sum / (area);
}

int Pixel::getRectangle(int x, int y)
{
    return 0;
}

double Pixel::getCircle()
{
    return 0;
}

double Pixel::getPixel(int x, int y)
{
    return this->img[x, y];
}
