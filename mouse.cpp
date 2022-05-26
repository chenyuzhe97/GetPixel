#include "mouse.h"

vector<string> files;


void onMouseMul(int event, int x, int y, int flags, void* param)  //evnet:����¼����� x,y:������� flags������ĸ���
{
	Mat* im = reinterpret_cast<Mat*>(param);
	switch (event) {

	case EVENT_LBUTTONDOWN:
		//��ʾͼ������ֵ

		if (static_cast<int>(im->channels()) == 1)
		{
			int sum = 0;
			//��ͼ��Ϊ�Ҷ�ͼ������ʾ������������Լ��Ҷ�ֵ
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
			//��ͼ��Ϊ��ɫͼ������ʾ����������Լ���Ӧ��B, G, Rֵ
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

void onMouse(int event, int x, int y, int flags, void* param)  //evnet:����¼����� x,y:������� flags������ĸ���
{
	Mat* im = reinterpret_cast<Mat*>(param);
	switch (event) {

	case EVENT_LBUTTONDOWN:
		//��ʾͼ������ֵ

		if (static_cast<int>(im->channels()) == 1)
		{
			//��ͼ��Ϊ�Ҷ�ͼ������ʾ������������Լ��Ҷ�ֵ
			cout << "at (" << x << ", " << y << " ) value is: " << static_cast<int>(im->at<uchar>(Point(x, y))) << endl;
		}
		else
		{
			//��ͼ��Ϊ��ɫͼ������ʾ����������Լ���Ӧ��B, G, Rֵ
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
	Mat image1 = imread("1.jpg");  //��ȡͼ��
	if (image1.empty())
	{
		cout << "��ȡ����" << endl;
		return -1;
	}
	imshow("image1", image1);  //��ʾͼ��


	setMouseCallback("image1", onMouse, reinterpret_cast<void*>(&image1)); //����ͼ����ʾ���ں�onMouse����
	waitKey(0);  //��ͣ������ͼ����ʾ���ȴ���������

	return 0;
}

*/

int opengraph(string name)
{
	if (name.empty())
		name = "1.jpg";

	Mat image1 = imread(name);  //��ȡͼ��
	if (image1.empty())
	{
		cout << "��ȡ����" << endl;
		return -1;
	}
	namedWindow("image1", WINDOW_NORMAL);
	imshow("image1", image1);  //��ʾͼ��


	setMouseCallback("image1", onMouse, reinterpret_cast<void*>(&image1)); //����ͼ����ʾ���ں�onMouse����
	waitKey(0);  //��ͣ������ͼ����ʾ���ȴ���������

	return 0;
}

int opengraphmul(string name)
{
	
	if (name.empty())
		name = "1.jpg";
	Mat image1 = imread(name);  //��ȡͼ��
	if (image1.empty())
	{
		cout << "��ȡ����" << endl;
		return -1;
	}
	namedWindow("image1", WINDOW_NORMAL);
	imshow("image1", image1);  //��ʾͼ��
	setMouseCallback("image1", onMouseMul, reinterpret_cast<void*>(&image1)); //����ͼ����ʾ���ں�onMouse����
	waitKey(0);  //��ͣ������ͼ����ʾ���ȴ���������

	return 0;
}


void getAllFiles(string path, vector<string>& files, string format)
{
	intptr_t  hFile = 0;//�ļ����  64λ��long ��Ϊ intptr_t
	struct _finddata_t fileinfo;//�ļ���Ϣ 
	string p;
	if ((hFile = _findfirst(p.assign(path).append("\\*" + format).c_str(), &fileinfo)) != -1) //�ļ�����
	{
		do
		{
			if ((fileinfo.attrib & _A_SUBDIR))//�ж��Ƿ�Ϊ�ļ���
			{
				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)//�ļ������в���"."��".."
				{
					files.push_back(p.assign(path).append("\\").append(fileinfo.name)); //�����ļ�����
					getAllFiles(p.assign(path).append("\\").append(fileinfo.name), files, format); //�ݹ�����ļ���
				}
			}
			else
			{
				files.push_back(p.assign(path).append("\\").append(fileinfo.name));//��������ļ��У������ļ���
			}
		} while (_findnext(hFile, &fileinfo) == 0);
		_findclose(hFile);
	}
}

void getFilesName(string filePath = "./")
{
	string format = "";				 //�����ļ��ĸ�ʽ
	getAllFiles(filePath, files, format);
	int size = files.size();
	for (int i = 0; i < size; i++)
	{
		cout << files[i] << endl;
	}
	system("pause");
}