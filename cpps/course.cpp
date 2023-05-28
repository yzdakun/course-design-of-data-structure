#include"affair.h"
using namespace std;
course::course()
{
	this->kind = 1;
	this->week = "0";
	this->c_week = 0;
}
void course::showInfo()
{
	cout <<  this->name<< this->StartTime<< this->EndTime<< this->place << this->Class << this->period << this->c_week << this->week << endl;
}
