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
		ifs.seekg(0, ios::beg);//������λ������Ϊ�ļ���ͷ
		int id, cId,type,num = 0;//num������
		string name,password;
		while (ifs >> cId && ifs >> id && ifs >> name)
		{
			num++;
		}//�õ�����
		presentNum = num;
		presentArray = new user * [num];//����ѧ������
		ifs.clear();//����Ѿ������ļ�β����seekg֮ǰҪ����clear()
		ifs.seekg(0, ios::beg);//������λ������Ϊ�ļ���ͷ
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
		}//����ѧ����Ϣ
		return;
	}
}
void control::log_in() 
{
	int id;
	string password;
	cout << "��ӭʹ�õ�¼ϵͳ��"<<endl;
	cout << "������ѧ����:" << endl;
	cin >> password;
	if (seek())
	{
		cout << "���������룺" << endl;
		if (seek())
		{
			cout << "��½�ɹ���"<<endl;
			if ()
			{

			}
		}//������ȷ
		else
		{
			cout << "�������"<<endl;
		}//�������
	}//�û�����
	else
	{
		cout << "�û������ڣ�" << endl;
		
	}//�û�������
}
int control::seek()
{
	
}//id�������ƥ������㷨