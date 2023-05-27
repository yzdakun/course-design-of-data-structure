#pragma once//防止文件重复包含
#include<iostream>
using namespace std;
class control
{
public:
	control();
	void log_in();
	int seek();
	int presentNum;
	user** presentArray;
};