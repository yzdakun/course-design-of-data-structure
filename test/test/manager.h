#pragma once

#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>
using namespace std;
class user
{
public:
	int id;//id
	string name;
	string password;
	int type;
};
class course
{
public:
	string name;
	int StartTime;
	int EndTime;
	string place;
	int Class;
	int kind;
	int period;//1是单次，2是周期
	int c_week;//上课的周数
	string week;
	int check[20]{ 0 };
	course();
};

class student : public user
{
public:
	int ClassNum;//学生班号
};
class manager :public user
{
public:
	void add_class();
	void delete_class();
	void change_class();
	void add_student();
	void delete_student();
	void change_student();
	void fUpdate();
	void init();
	void connection();
	void translate();
	void m_translate(course& c);
	vector<course> course_Array;
	int count_course = 0;
	vector<student> student_Array;
	int count_student = 0;
};
