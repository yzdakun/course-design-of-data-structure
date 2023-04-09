#include<iostream>
#include<fstream>
#include"Log_control.h"
using namespace std;

Log_control Log;
user* U = NULL;
void Login()
{
	Log.Init_StudentMessage();
	Log.Init_ManagerMessage();
	cout << "��ӭʹ��ѧ��ϵͳ" << endl;
	cout << "��ѡ���������:" << endl;
	cout << "ѧ����0  ����Ա �� 1" << endl;

	int identity;
	cin >> identity;
	switch (identity)
	{
	case 0:
		Log.Student_login();
		break;
	case 1:
		Log.Manager_login();
		break;
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
	int id, cId;
	string name, password;
	while (ifs >> id && ifs >> cId && ifs >> name && ifs >> password)
	{
		//cout << id << " " << cId << " " << name << " " << password << endl;
		user* userptr = NULL;
		//userptr=new student(id,cId,type,name,password);
		userptr = new student(id, cId, name, password);
		U = userptr;
		//cout << userptr->m_password << endl;
		Stu.insert(id, userptr);
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
	while (ifs >> id  && ifs >> name && ifs >> password)
	{
		user* userptr = NULL;
		userptr = new manager(id, name, password);
		Tec.insert(id, userptr);
	}

	return;
}


void Log_control::Student_login()
{
	//Stu.printData();
	//Stu.print();
	cout << U->m_password << endl;

	int id;
	//char password[20];
	string password;
	cout << "��������������" << endl;
	cin >> id;
	
	if (Stu.search(id))
	{
		cout << "��������������" << endl;
		cin >> password;

		user* ptr = Stu.select(id);
		string p = ptr->m_password;
		int len1 = password.size(), len2 =p.size();
		if (len1 != len2)
		{
			//cout << "�������" << " " << password << " " << p << endl;
			cout << "�������" << endl;
		}
		else
		{
			for (int i = 0; i < len1; i++)
			{
				if (password[i] != p[i])
				{
					//cout << "�������" << password[i] << " " << p[i] << " " << endl;
					cout << "�������" << endl;
					return;
				}
			}
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
	cout << "��������������" << endl;
	cin >> id;
	

	if (Tec.search(id))
	{
		cout << "��������������" << endl;
		cin >> password;
		user* ptr = Tec.select(id);
		string p = ptr->m_password;
		int len1 = password.size(), len2 = p.size();
		if (len1 != len2)
		{
			//cout << password;
			cout << "�������" <<  endl;
		}
		else
		{
			cout << password << " " << p;
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

