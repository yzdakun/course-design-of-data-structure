#pragma once
#include<string>
using namespace std;

class course
{
public: 
	string name;
	int StartTime;
	int EndTime;
	string place;
	int Class;
	int kind;
};

class group_act
{
public:
	string name;
	int StartTime;
	int EndTime;
	string place;
	int Class;//���˻ʱ����ѧ��id������ʱ����༶
	int kind;
};

class activity
{
public:
	string name;
	int StartTime;
	int EndTime;
	string place;
	int id;//���˻ʱ����ѧ��id������ʱ����༶
	int kind;
	int type;  
};

class temp_act
{
public:
	string name;
	int StartTime;
	int EndTime;
	string place;
	int id;
	int kind;
};