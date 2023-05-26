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
	int Class;//个人活动时储存学生id，集体活动时储存班级
	int kind;
};

class activity
{
public:
	string name;
	int StartTime;
	int EndTime;
	string place;
	int id;//个人活动时储存学生id，集体活动时储存班级
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