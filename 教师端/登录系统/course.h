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
	int period;//1�ǵ��Σ�2������
	int c_week;//�Ͽε�����
	string week;
	int check[19]{0};
	course();
	void showInfo();
};