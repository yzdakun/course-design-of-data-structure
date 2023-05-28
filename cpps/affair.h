#pragma once
#include<string>
using namespace std;

class course
{
public:
	string name;
	int StartTime;
	int EndTime;
	int place;
	int Class;
	int kind;
	int period;//1�ǵ��Σ�2������
	int c_week;//�Ͽε�����
	string week;
	int check[19]{0};
	course();
	void showInfo();
};

class group_act
{
public:
	string name;
	int StartTime;
	int EndTime;
	int place;
	int Class;//���˻ʱ����ѧ��id������ʱ����༶
	int kind;
};

class activity
{
public:
	string name;
	int StartTime;
	int EndTime;
	int place;
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
	int place;
	int id;
	int kind;
};