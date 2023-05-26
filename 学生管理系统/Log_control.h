#pragma once
#include"BPlus_node.h"
#include"BPlus_tree.h"
#include"user.h"
class Log_control
{
public:
	Log_control();
	~Log_control();

	void Student_login();
	void Manager_login();
	void Logout();

	void Init_StudentMessage();
	void Init_ManagerMessage();

private:
	CBPlusTree Stu;
	CBPlusTree Tec;
};
void Login();