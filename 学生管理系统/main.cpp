#include<iostream>
#include"BPlus_node.h"
#include"BPlus_tree.h"
#include"Time.h"
#include"Log_control.h"
#include"test1.h"
using namespace std;

thread a;

int main()
{
	//thread a;
	a = thread(time_run);
	//test1();
	Login();
	St = 1;
	a.join();




	/*CBPlusTree  T;
	
	while (1)
	{
		cout << "��������Ĳ���" << endl;
		cout << "insert 1" << endl;
		cout << "delete 2" << endl;
		cout << "search 3" << endl;
		cout << "�˳���¼ 4" << endl;

		int type;
		int key, dt;
		cin >> type;
		switch (type)
		{
		case 1:
			cout << "������Ҫ����ļ�ֵ������" << endl;
			cin >> key >> dt;
			T.insert(key, dt);
			break;
		case 2:
			cout << "������Ҫɾ���ļ�ֵ" << endl;
			cin >> key;
			T.remove(key);
			break;
		case 3:
			cout << "������Ҫ��ѯ�ļ�ֵ" << endl;
			cin >> key;
			if (T.search(key))
			{
				cout << "Yes" << endl;
			}
			else
			{
				cout << "No" << endl;
			}
			break;
		default:
			cout << "�´�����" << endl;
			break;
		}
		if (type == 4)
			break;

	}*/



}