#include"student.h"
using namespace std;
student::student(int id, string name, int cId,string password)
{
	m_id = id;//学号
	m_name = name;//学生姓名
	m_ClassNum = cId;//班号
	m_password = password;//密码
	m_type = 1;
}//有参构造
