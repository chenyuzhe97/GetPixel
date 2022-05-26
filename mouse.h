#pragma once
#include "all.h"
using namespace std;
using namespace cv;
void onMouse(int event, int x, int y, int flags, void* param);
void onMouseMul(int event, int x, int y, int flags, void* param);
int opengraph(string name);
int opengraphmul(string name);
void getAllFiles(string path, vector<string>& files, string format);

void getFilesName(string filePath);
