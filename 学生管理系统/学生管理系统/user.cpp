#include<iostream>
#include"user.h"
using namespace std;

/*user::user(int id, int cId, int type, string name, string password)
{
	m_id = id;//ѧ��
	m_ClassNum = cId;//���
	m_type = type;
	m_name = name;//ѧ������
	m_password = password;//����
	
}
user::~user() {};*/

student::student(int id,  int cId, string name,string password)
{
	m_id = id;//ѧ��
	m_name = name;//ѧ������
	m_ClassNum = cId;//���
	m_password = password;//����
	m_type = 1;
}

manager::manager(int id, string name, string password)
{
	m_id = id;//ѧ��
	m_name = name;//ѧ������
	m_password = password;//����
	m_type = 2;
}