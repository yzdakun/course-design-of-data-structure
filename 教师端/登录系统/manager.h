#pragma once
#include"user.h"
#include"course.h"
#include"student.h"

using namespace std;
class manager:public user
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
	vector<course> course_Array;
	int count_course = 0;
	vector<student> student_Array;
	int count_student = 0;
};
