#include"manager.h"
using namespace std;
manager::manager(int id, string name,string password)
{
	m_id = id;//学号
	m_name = name;//学生姓名
	m_password = password;//密码
	m_type = 2;
}//有参构造