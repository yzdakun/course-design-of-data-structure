#include"student.h"
using namespace std;
student::student(int id, string name, int cId,string password)
{
	m_id = id;//ѧ��
	m_name = name;//ѧ������
	m_ClassNum = cId;//���
	m_password = password;//����
	m_type = 1;
}//�вι���
