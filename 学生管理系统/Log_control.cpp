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
	cout << "欢迎使用学工系统" << endl;

	while (true)
	{
		cout << "请选择您的身份:" << endl;
		cout << "学生：0  管理员 ： 1，退出 ： 2" << endl;

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
		cout << "学生信息初始化错误" << endl;
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
		cout << "管理员信息初始化错误" << endl;
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
	cout << "请输入您的id" << endl;
	cin >> id;
	
	if (Stu.search(id))
	{
		cout << "请输入您的密码" << endl;
		cin >> password;

		int ptr = Stu.select(id);
		string p = StudentList[ptr].password;
		int len1 = password.size(), len2 =p.size();
		if (len1 != len2)
		{
			//cout << "密码错误" << " " << password << " " << p << endl;
			cout << "密码错误" << endl;
		}
		else
		{
			//cout << "密码错误" << " " << password << " " << p << endl;
			for (int i = 0; i < len1; i++)
			{
				if (password[i] != p[i])
				{
					//cout << "密码错误" << password[i] << " " << p[i] << " " << endl;
					cout << "密码错误" << endl;
					return;
				}
			}
			cout << "你好，" << StudentList[ptr].name << endl;
			StudentList[ptr].ManageSystem();
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
	cout << "请输入您的id" << endl;
	cin >> id;
	

	if (Tec.search(id))
	{
		cout << "请输入您的密码" << endl;
		cin >> password;
		int ptr = Tec.select(id);
		string p = ManagerList[ptr].password;
		int len1 = password.size(), len2 = p.size();
		if (len1 != len2)
		{
			//cout << password;
			cout << "密码错误" <<  endl;
		}
		else
		{
			//cout << password << " " << p;
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

