#include "graph.h"
#include "mouse.h"
#include "windows.h"
#include "all.h"

//全局变量
extern vector<string> files;

//声明位置
void test01();
void test02();
void test03();

void test01()
{
		cout << "请把图片放在该文件同目录下，命名为1.jpg。" << endl;
		string name;
		int key;
		cout << "输入数字1自定义文件名字，不然文件名默认为1.jpg。" << endl;
		cout << "请输入数字：";
		cin >> key;
		if (key == 1) {
			cout << "请输入名字：";
			cin >> name;
		}

		system("pause");
		opengraph(name);
		//conv();            
		//gray();
		//cap();
		//profile();
}


 void test02()
 {
	 string filePath = "D:\\c++\\image\\Project1\\Project1\\x64\\aa\\";
	 string format = "";				 //查找文件的格式
	 getAllFiles(filePath, files, format);
	 int size = files.size();
	 for (int i = 0; i < size; i++)
	 {
		 cout << files[i] << endl;
	 }
	 system("pause");
 }

 void test03()
 {

	 getFilesName("./dataset\\"); //找到文件
	 opengraphmul(files[0]);

 }

int main()
{
	int key=0;
	cout << "-------------------像素提取小程序--------------------" << endl;
	cout << "--------------------作者：CYZ------------------------" << endl;
	cout << "\n" << endl;
	cout << "输入指定的数字完成操作。" << endl;
	cout << "输入数字1，提取单张图片选定区域像素值" << endl;
	cout << "输入数字2，提取批量图片指定区域平均像素值,图片放入dataset文件夹中" << endl;
	cout << "输入数字0退出!" << endl;
	cout << "请输入数字：";
	cin >> key;
	system("cls");
	switch (key) {
	case 1:test01(); break;   //操作1
	case 2:test03(); break;   //操作2
	case 3:WindowsControl(); break;
	case 0:cout << "感谢使用，再见！" << endl;
	}
	return 0;
}

