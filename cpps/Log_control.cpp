#include<iostream>
#include"Log_control.h"
using namespace std;
#include<fstream>

Log_control Log;
//user* U = NULL;
ifstream ifsTotal;
ofstream otsTotal;
void Login()
{
	Log.Init_StudentMessage();
	Log.Init_ManagerMessage();
	cout << "��ӭʹ��ѧ��ϵͳ" << endl;


	ifsTotal.open("js2exe.txt",ios::in);
	otsTotal.open("../htmls/exe2js.txt",ios::out);
		// cout << "��ѡ����������:" << endl;
		// cout << "ѧ����0  ����Ա �� 1���˳� �� 2" << endl;

		/*for (int i = 1; i <= StudentCnt; i++)
		{
			cout << i << " " << StudentList[i].id << " " << StudentList[i].password << endl;
		}
		for (int i = 1; i <= ManagerCnt; i++)
		{
			cout << i << " " << ManagerList[i].id << " " << ManagerList[i].password << endl;
		}*/
		int identity;
		ifsTotal >> identity;
		ifsTotal >> identity;
		cout<<identity<<endl;
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
			return ;
		}
		long long timestamp;
		ifsTotal>>timestamp;
		otsTotal<<timestamp<<endl;

		ifsTotal.close();
		otsTotal.close();
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


Log_control::Log_control() {};
Log_control:: ~Log_control() {};

void Log_control::Init_StudentMessage()
{
	ifstream ifs;

	ifs.open("../datas/studentmessage.txt", ios::in);
	if (!ifs.is_open())
	{
		// cout << "ѧ����Ϣ��ʼ������" << endl;
		// exit(0);
		return ;
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

	ifs.open("../datas/managermessage.txt", ios::in);
	if (!ifs.is_open())
	{
		// cout << "����Ա��Ϣ��ʼ������" << endl;
		// exit(0);
		return ;
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
	// cout << "����������id" << endl;
	ifsTotal >> id;
	cout<<id<<endl;
	ifsTotal >> password;
	if (Stu.search(id))
	{
		// cout << "��������������" << endl;
		

		int ptr = Stu.select(id);
		string p = StudentList[ptr].password;
		int len1 = password.size(), len2 =p.size();
		if (len1 != len2)
		{
			otsTotal<<0<<endl<<0<<endl;
			//cout << "�������?" << " " << password << " " << p << endl;
			// cout << "�������?" << endl;
		}
		else
		{
			//cout << "�������?" << " " << password << " " << p << endl;
			for (int i = 0; i < len1; i++)
			{
				if (password[i] != p[i])
				{
					otsTotal<<0<<endl<<0<<endl;
					//cout << "�������?" << password[i] << " " << p[i] << " " << endl;
					// cout << "�������?" << endl;
					return;
				}
			}
			otsTotal<<1<<endl<<0<<endl;
			// cout << "��ã�?" << StudentList[ptr].name << endl;
			long long timestamp;
			ifsTotal>>timestamp;
			otsTotal<<timestamp<<endl;
			StudentList[ptr].ManageSystem();
			//Student_ManageSystem();
		}

	}
	else
	{
		otsTotal<<2<<endl<<0<<endl;
		// cout << "�����˺��Ƿ���ȷ" << endl;
		return;
	}
}

void Log_control::Manager_login()
{
	//Tec.printData();
	int id;
	//char password[20];
	string password;
	// cout << "����������id" << endl;
	ifsTotal >> id;
	
	cout<<id<<endl;
	ifsTotal >> password;
	if (Tec.search(id))
	{
		// cout << "��������������" << endl;
		
		int ptr = Tec.select(id);
		string p = ManagerList[ptr].password;
		int len1 = password.size(), len2 = p.size();
		if (len1 != len2)
		{
			otsTotal<<0<<endl<<1<<endl;
			//cout << password;
			// cout << "�������?" <<  endl;
		}
		else
		{
			//cout << password << " " << p;
			for (int i = 0; i < len1; i++)
			{
				if (password[i] != p[i])
				{
					otsTotal<<0<<endl<<1<<endl;
					// cout << "�������?" <<  endl;
					return;
				}
			}
			otsTotal<<1<<endl<<1<<endl;
			//Manager_ManageSystem();
		}

	}
	else
	{
		otsTotal<<2<<endl<<1<<endl;
		// cout << "�����˺��Ƿ���ȷ" << endl;
		return;
	}
}

