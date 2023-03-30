#pragma once
#include"user.h"
using namespace std;
class student: public user
{
public:
	int m_ClassNum;//Ñ§Éú°àºÅ
	student(int id, string name, int cId,string password);
};