#pragma once
#include"user.h"
using namespace std;
class student: public user
{
public:
	int m_ClassNum;//ѧ�����
	student(int id, string name, int cId,string password);
};