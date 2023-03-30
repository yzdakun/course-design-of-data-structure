#include<iostream>
#include<fstream>
#include"student.h"
#include"manager.h"
#include"control.h"
#include"user.h"
control::control()
{
	ifstream ifs;
	ifs.open("student.txt", ios::in);
	if (!ifs.is_open())
	{
		presentArray = NULL;
		presentNum = 0;
		return;
	}
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		presentArray = NULL;
		presentNum = 0;
		return;
	}
	else
	{
		ifs.clear();
		ifs.seekg(0, ios::beg);//将读入位置设置为文件开头
		int id, cId,type,num = 0;//num计人数
		string name,password;
		while (ifs >> cId && ifs >> id && ifs >> name)
		{
			num++;
		}//得到总数
		presentNum = num;
		presentArray = new user * [num];//开辟学生数组
		ifs.clear();//如果已经到达文件尾，用seekg之前要先用clear()
		ifs.seekg(0, ios::beg);//将读入位置设置为文件开头
		int i = 0;
		while (ifs >> type)
		{
			user* userPtr = NULL;
			switch (type)
			{
			case 1:
				ifs >> id;
				ifs >> name;
				ifs >> password;
				userPtr = new manager(id, name,password);
				break;
			case 2:
				ifs >> id;
				ifs >> name;
				ifs >> cId;
				ifs >> password;
				userPtr = new student(id, name, cId ,password);
				break;
			default:
				break;
			}			
			presentArray[i] = userPtr;
			i++;
		}//读入学生信息
		return;
	}
}
void control::log_in() 
{
	int id;
	string password;
	cout << "欢迎使用登录系统！"<<endl;
	cout << "请输入学工号:" << endl;
	cin >> password;
	if (seek())
	{
		cout << "请输入密码：" << endl;
		if (seek())
		{
			cout << "登陆成功！"<<endl;
			if ()
			{

			}
		}//密码正确
		else
		{
			cout << "密码错误！"<<endl;
		}//密码错误
	}//用户存在
	else
	{
		cout << "用户不存在！" << endl;
		
	}//用户不存在
}
int control::seek()
{
	
}//id与密码的匹配查找算法