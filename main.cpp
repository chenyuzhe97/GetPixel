#include "graph.h"
#include "mouse.h"
#include "windows.h"
#include "all.h"

//ȫ�ֱ���
extern vector<string> files;

//����λ��
void test01();
void test02();
void test03();

void test01()
{
		cout << "���ͼƬ���ڸ��ļ�ͬĿ¼�£�����Ϊ1.jpg��" << endl;
		string name;
		int key;
		cout << "��������1�Զ����ļ����֣���Ȼ�ļ���Ĭ��Ϊ1.jpg��" << endl;
		cout << "���������֣�";
		cin >> key;
		if (key == 1) {
			cout << "���������֣�";
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
	 string format = "";				 //�����ļ��ĸ�ʽ
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

	 getFilesName("./dataset\\"); //�ҵ��ļ�
	 opengraphmul(files[0]);

 }

int main()
{
	int key=0;
	cout << "-------------------������ȡС����--------------------" << endl;
	cout << "--------------------���ߣ�CYZ------------------------" << endl;
	cout << "\n" << endl;
	cout << "����ָ����������ɲ�����" << endl;
	cout << "��������1����ȡ����ͼƬѡ����������ֵ" << endl;
	cout << "��������2����ȡ����ͼƬָ������ƽ������ֵ,ͼƬ����dataset�ļ�����" << endl;
	cout << "��������0�˳�!" << endl;
	cout << "���������֣�";
	cin >> key;
	system("cls");
	switch (key) {
	case 1:test01(); break;   //����1
	case 2:test03(); break;   //����2
	case 3:WindowsControl(); break;
	case 0:cout << "��лʹ�ã��ټ���" << endl;
	}
	return 0;
}

