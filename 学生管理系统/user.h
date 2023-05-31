#pragma once
#include<iostream>
#include<string>
#include<windows.h>
#include<thread>
#include"affair.h"
#include"BPlus_tree.h"
using namespace std;
#define MAX_PEOPLE 1000
#define WEEK_NUM 30
#define ACT_NUM 50
#define ALARM_NUM 200
class user
{
public:
	int id;//id
	string name;
	string password;
	int type;
	//int m_ClassNum;
	//user(int id, int cId, int type, string name, string password);
	//~user();
};

typedef struct
{
	int x, y;
}IDX;

typedef struct
{
	int StartTime;
	int kind;
	int ActTime;
	int type;
	int id;
}alarm;

class student : public user
{
public:
	int ClassNum;
	//  int stop;

	int timeline[5000];

	course CourseList[WEEK_NUM][ACT_NUM];
	int CourseNum[WEEK_NUM];
	IDX CourseIdx;

	activity ActivityList[WEEK_NUM][ACT_NUM];
	int ActivityNum[WEEK_NUM];
	//IDX ActivityIdx;

	group_act GroupActList[WEEK_NUM][ACT_NUM];
	int GroupActNum[WEEK_NUM];
	//IDX GroupActIdx;

	temp_act TempActList[WEEK_NUM][ACT_NUM];
	int TempActNum[WEEK_NUM];
	//IDX TempActIdx;

	alarm AlarmList[ALARM_NUM];
	int AlarmNum;
	int AlarmIdx;
	void ManageSystem();
	//thread sysalarm, tmpalarm, personalalarm;
	void SystemAlarmClock(int now_time);
	void TempAlarmClock(int now_time);
	void PersonalAlarmClock(int now_time);
	student();
	~student();
private:
	//CBPlusTree Course;
	void Init(int now_time);
	void save();
	void course_showinfo();
	void InitCourseInformation(int now_time);
	void InitActivityInformation();
	void InitGroupActInformation();
	void InitTempActInformation();
	void InitAlarmClockInformation(int now_time);
	void SaveGroupActInformation();
	void SaveActivityInformation();
	void SaveTempActInformation();
	void SaveAlarmClockInformation();
	void ShowClassSchedule(int week);



	int Search(int kind, string name,int now_time);
	void AddGroupAct();
	void AddActivity();
	int AddSingleActivity(int tm, string name, string place, int type);
	void AddTempAct();
	void DeleteGroupAct();
	void DeleteActivity();
	void DeleteTempAct();
	
	
	void AddPersonalAlarmClock(int starttime, int kind, int acttime, int tp);
	void DeletePersonalAlarmClock();
	void ShowPersonalAlarmClock();
	void ShowInfo(int kind, int ActTime);

	//student(int id, int ClassNum, string name, string password);
};

class manager :public user
{
public:
	manager();
	~manager();
	//manager(int id, string name, string password);
};


extern student StudentList[MAX_PEOPLE];
extern int StudentCnt ;
extern manager ManagerList[MAX_PEOPLE];
extern int ManagerCnt ;





