#include<iostream>
#include"user.h"
using namespace std;

/*user::user(int id, int cId, int type, string name, string password)
{
	m_id = id;//学号
	m_ClassNum = cId;//班号
	m_type = type;
	m_name = name;//学生姓名
	m_password = password;//密码
	
}
user::~user() {};*/

student::student(int id,  int cId, string name,string password)
{
	m_id = id;//学号
	m_name = name;//学生姓名
	m_ClassNum = cId;//班号
	m_password = password;//密码
	m_type = 1;
}

manager::manager(int id, string name, string password)
{
	m_id = id;//学号
	m_name = name;//学生姓名
	m_password = password;//密码
	m_type = 2;
}