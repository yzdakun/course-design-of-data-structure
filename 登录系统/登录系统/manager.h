#pragma once
#include"user.h"
using namespace std;
class manager:public user
{
public:
	manager(int id, string name,string password);
};