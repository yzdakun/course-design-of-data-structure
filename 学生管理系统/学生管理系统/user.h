#pragma once
#include<iostream>
using namespace std;
class user
{
public:
	int m_id;//id
	string m_name;
	string m_password;
	int m_type;
	//int m_ClassNum;
	//user(int id, int cId, int type, string name, string password);
	//~user();
};

class student : public user
{
public:
	int m_ClassNum;
	student(int id, int cId, string name, string password);
};

class manager :public user
{
public:
	manager(int id, string name, string password);
};