#include<iostream>
#include"Log_control.h"
using namespace std;
#include<fstream>

Log_control Log;
//user* U = NULL;
void Login()
{
	Log.Init_StudentMessage();
	Log.Init_ManagerMessage();
	cout << "��ӭʹ��ѧ��ϵͳ" << endl;

	while (true)
	{
		cout << "��ѡ���������:" << endl;
		cout << "ѧ����0  ����Ա �� 1���˳� �� 2" << endl;

		/*for (int i = 1; i <= StudentCnt; i++)
		{
			cout << i << " " << StudentList[i].id << " " << StudentList[i].password << endl;
		}
		for (int i = 1; i <= ManagerCnt; i++)
		{
			cout << i << " " << ManagerList[i].id << " " << ManagerList[i].password << endl;
		}*/
		int identity;
		cin >> identity;
		if (identity == 0)
		{
			Log.Student_login();
		}
		else if (identity == 1)
		{
			Log.Manager_login();
		}
		else if (identity == 2)
		{
			break;
		}
		/*switch (identity)
		{
		case 0:
			Log.Student_login();
			break;
		case 1:
			Log.Manager_login();
			break;
		}*/
	}
	
}


Log_control::Log_control() {};
Log_control:: ~Log_control() {};

void Log_control::Init_StudentMessage()
{
	ifstream ifs;

	ifs.open("studentmessage.txt", ios::in);
	if (!ifs.is_open())
	{
		cout << "ѧ����Ϣ��ʼ������" << endl;
		exit(0);
	}

	ifs.clear();
	ifs.seekg(0, ios::beg);
	int id, ClassNum;
	string name, password;
	StudentCnt = 0;
	while (ifs >> id && ifs >> ClassNum && ifs >> name && ifs >> password)
	{
		++StudentCnt;
		StudentList[StudentCnt].id = id;
		StudentList[StudentCnt].ClassNum = ClassNum;
		StudentList[StudentCnt].name = name;
		StudentList[StudentCnt].password = password;
		Stu.insert(id, StudentCnt);
	}
	return;
}

void Log_control::Init_ManagerMessage()
{
	ifstream ifs;

	ifs.open("managermessage.txt", ios::in);
	if (!ifs.is_open())
	{
		cout << "����Ա��Ϣ��ʼ������" << endl;
		exit(0);
	}

	ifs.clear();
	ifs.seekg(0, ios::beg);
	int id;
	//char name[20], password[20];
	string name, password;
	ManagerCnt = 0;
	while (ifs >> id  && ifs >> name && ifs >> password)
	{
		++ManagerCnt;
		ManagerList[ManagerCnt].id = id;
		ManagerList[ManagerCnt].name = name;
		ManagerList[ManagerCnt].password = password;
		Tec.insert(id, ManagerCnt);
	}

	return;
}


void Log_control::Student_login()
{
	int id;
	string password;
	cout << "����������id" << endl;
	cin >> id;
	
	if (Stu.search(id))
	{
		cout << "��������������" << endl;
		cin >> password;

		int ptr = Stu.select(id);
		string p = StudentList[ptr].password;
		int len1 = password.size(), len2 =p.size();
		if (len1 != len2)
		{
			//cout << "�������" << " " << password << " " << p << endl;
			cout << "�������" << endl;
		}
		else
		{
			//cout << "�������" << " " << password << " " << p << endl;
			for (int i = 0; i < len1; i++)
			{
				if (password[i] != p[i])
				{
					//cout << "�������" << password[i] << " " << p[i] << " " << endl;
					cout << "�������" << endl;
					return;
				}
			}
			cout << "��ã�" << StudentList[ptr].name << endl;
			StudentList[ptr].ManageSystem();
			//Student_ManageSystem();
		}

	}
	else
	{
		cout << "�����˺��Ƿ���ȷ" << endl;
		return;
	}
}

void Log_control::Manager_login()
{
	//Tec.printData();
	int id;
	//char password[20];
	string password;
	cout << "����������id" << endl;
	cin >> id;
	

	if (Tec.search(id))
	{
		cout << "��������������" << endl;
		cin >> password;
		int ptr = Tec.select(id);
		string p = ManagerList[ptr].password;
		int len1 = password.size(), len2 = p.size();
		if (len1 != len2)
		{
			//cout << password;
			cout << "�������" <<  endl;
		}
		else
		{
			//cout << password << " " << p;
			for (int i = 0; i < len1; i++)
			{
				if (password[i] != p[i])
				{
					cout << "�������" <<  endl;
					return;
				}
			}
			//Manager_ManageSystem();
		}

	}
	else
	{
		cout << "�����˺��Ƿ���ȷ" << endl;
		return;
	}
}

