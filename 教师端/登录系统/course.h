#pragma once
#include<iostream>
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
	int period;//1是单次，2是周期
	int c_week;//上课的周数
	string week;
	int check[19]{0};
	course();
	void showInfo();
};