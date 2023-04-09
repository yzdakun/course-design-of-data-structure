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
	cout << "欢迎使用学工系统" << endl;
	cout << "请选择您的身份:" << endl;
	cout << "学生：0  管理员 ： 1" << endl;

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
		cout << "学生信息初始化错误" << endl;
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
		cout << "管理员信息初始化错误" << endl;
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
	cout << "请输入您的姓名" << endl;
	cin >> id;
	
	if (Stu.search(id))
	{
		cout << "请输入您的密码" << endl;
		cin >> password;

		user* ptr = Stu.select(id);
		string p = ptr->m_password;
		int len1 = password.size(), len2 =p.size();
		if (len1 != len2)
		{
			//cout << "密码错误" << " " << password << " " << p << endl;
			cout << "密码错误" << endl;
		}
		else
		{
			for (int i = 0; i < len1; i++)
			{
				if (password[i] != p[i])
				{
					//cout << "密码错误" << password[i] << " " << p[i] << " " << endl;
					cout << "密码错误" << endl;
					return;
				}
			}
			//Student_ManageSystem();
		}

	}
	else
	{
		cout << "请检查账号是否正确" << endl;
		return;
	}
}

void Log_control::Manager_login()
{
	//Tec.printData();
	int id;
	//char password[20];
	string password;
	cout << "请输入您的姓名" << endl;
	cin >> id;
	

	if (Tec.search(id))
	{
		cout << "请输入您的密码" << endl;
		cin >> password;
		user* ptr = Tec.select(id);
		string p = ptr->m_password;
		int len1 = password.size(), len2 = p.size();
		if (len1 != len2)
		{
			//cout << password;
			cout << "密码错误" <<  endl;
		}
		else
		{
			cout << password << " " << p;
			for (int i = 0; i < len1; i++)
			{
				if (password[i] != p[i])
				{
					cout << "密码错误" <<  endl;
					return;
				}
			}
			//Manager_ManageSystem();
		}

	}
	else
	{
		cout << "请检查账号是否正确" << endl;
		return;
	}
}

