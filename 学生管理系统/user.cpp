#include<iostream>
#include<fstream>
#include<windows.h>
#include"user.h"
#include"Time.h"
#include"CLog.h"
using namespace std;
student StudentList[MAX_PEOPLE];
int StudentCnt;
manager ManagerList[MAX_PEOPLE];
int ManagerCnt;

student::student() {};
student::~student() {};
manager::manager() {};
manager::~manager() {};

//initcourse有now_ime要改，search 588行有now—time要改

void student::ManageSystem()
{
	Init(now_time);
	
	log1.wr(now_time, this->name , "登陆了学生管理系统");
	//clog.wr(now_time, this->name, "登陆了管理系统");
	while (true)
	{
		int t;
		cout << "您要进行的操作类型：1 课程表展示，2 查找，3,添加活动，4 删除活动，5 添加闹钟，6 删除闹钟 ，7 展示闹钟 ，8 退出" << endl;
		cin >> t;

		if (t == 1)
		{
			cout << "请输入您要展示第几周的课表：" << endl;
			int w;
			cin >> w;
			this->ShowClassSchedule(w);

		}
		else if (t == 2)
		{
			cout << "请输入您要查找的类型：1 课程，2 集体活动，3 个人活动 ，4 临时事务" << endl;
			int tp;
			cin >> tp;
			if (tp != 1 && tp != 2 && tp != 3 && tp != 4)
			{
				cout << "输入错误" << endl;
			}
			else
			{
				string s;
				cout << "请输入名称" << endl;
				cin >> s;
				int week = Search(tp, s, now_time);
				if (week > 0)
				{
					ShowClassSchedule(week);
				}
				else
				{
					cout << "后续无该事务" << endl;
				}
			}
		}
		else if (t == 3)
		{
			cout << "请输入您要添加的事务类型;2 集体活动 ，3 个人活动 ，4 临时事务" << endl;
			int tp;
			cin >> tp;
			if (tp == 1)
			{
				cout << "没有权限添加课程" << endl;
			}
			else if (tp == 2)
			{
				AddGroupAct();
			}
			else if (tp == 3)
			{
				AddActivity();
			}
			else if (tp == 4)
			{
				AddTempAct();
			}
			else
			{
				cout << "输入错误" << endl;
			}

		}
		else if (t == 4)
		{
			cout << "请输入您要删除的事务类型;2 集体活动 ，3 个人活动 ，4 临时事务" << endl;
			int tp;
			cin >> tp;
			if (tp == 1)
			{
				cout << "没有权限删除课程" << endl;
			}
			else if (tp == 2)
			{
				DeleteGroupAct();
			}
			else if (tp == 3)
			{
				DeleteActivity();
			}
			else if (tp == 4)
			{
				DeleteTempAct();
			}
			else
			{
				cout << "输入错误" << endl;
			}
		}
		else if (t == 5)
		{
			int starttime, kind,  acttime, type;
			cout << "请输入闹钟时间，闹钟类型，活动开始时间" << endl;
			cin >> starttime >> kind >> acttime;
			cout << "请输入周期：1 单次，2 每天，3 每周" << endl;
			cin >> type;
			AddPersonalAlarmClock(starttime, kind, acttime, type);
		}
		else if (t == 6)
		{
			DeletePersonalAlarmClock();
		}
		else if (t == 7)
		{
			ShowPersonalAlarmClock();
		}
		else if (t == 8)
		{
			log1.wr(now_time, this->name, "退出登录");
			cout << "即将退出登录" << endl;
			break;
		}
		else
		{
			cout << "不存在此操作" << endl;
		}


	}

	save();
}



void student::Init(int now_time)
{
	memset(timeline, 0, sizeof(timeline));
	InitCourseInformation(now_time);
	InitGroupActInformation();
	InitActivityInformation();
	InitTempActInformation();
	InitAlarmClockInformation(now_time);
	//stop = 0;
	//sysalarm = thread(&student::SystemAlarmClock,this);
	//tmpalarm = thread(&student::TempAlarmClock,this);
	//personalalarm = thread(&student::PersonalAlarmClock,this);
		//tmpalarm, personalalarm;
	//thread sysalarm,tmpalarm,personalalarm;


}
void student::save()
{
	SaveGroupActInformation();
	SaveActivityInformation();
	SaveTempActInformation();
	SaveAlarmClockInformation();
	//sysalarm .join();
	//tmpalarm .join();
	//personalalarm.join();
	//this->stop = 1;
}


void student::InitCourseInformation(int now_time)
{
	for (int i = 0; i < WEEK_NUM; i++)
	{
		CourseNum[i] = 0;
	}
	CourseIdx = { 0,0 };
	ifstream ifs;
	int flag = 0;
	
	string filename = to_string(this->ClassNum);
	filename = filename + "course.txt";

	ifs.open(filename, ios::in);

	if (!ifs.is_open())
	{
		cout << "学生课程信息初始化错误" << endl;
		exit(0);
	}

	ifs.clear();
	ifs.seekg(0, ios::beg);

	string name;
	int StartTime;
	int EndTime;
	string place;
	int Class, kind;
	while (ifs >> name && ifs >> StartTime && ifs >> EndTime && ifs >> place && ifs >> Class && ifs >> kind)
	{
		int x = StartTime / 168;
		if (Class == this->ClassNum)//
		{
			if (StartTime >= now_time && flag == 0)
			{
				CourseIdx.x = x;
				CourseIdx.y = CourseNum[x];
				flag = 1;
			}
			int i = CourseNum[x];
			for (int j = StartTime; j < EndTime; j++)
			{
				timeline[j] = kind;
			}
			CourseList[x][i].name = name;
			CourseList[x][i].StartTime = StartTime;
			CourseList[x][i].EndTime = EndTime;
			CourseList[x][i].place = place;
			CourseList[x][i].Class = Class;
			CourseList[x][i].kind = kind;
			CourseNum[x]++;
		}
	}
	ifs.close();
}

void student::InitActivityInformation()
{
	for (int i = 0; i < WEEK_NUM; i++)
	{
		ActivityNum[i] = 0;
	}
	//ActivityIdx = { 0,0 };
	int flag = 0;
	
	string filename = to_string(this->id);
	filename = filename + "activity.txt";
	ifstream ifs;

	ifs.open(filename, ios::in);

	if (!ifs.is_open())
	{
		cout << "学生课外活动信息初始化错误" << endl;
		exit(0);
	}

	ifs.clear();
	ifs.seekg(0, ios::beg);

	string name;
	int StartTime;
	string place;
	int id;
	int kind;
	while (ifs >> name && ifs >> StartTime && ifs >> place && ifs >> id && ifs >> kind)
	{
		int x = StartTime / 168;
		if (id == this->id)//
		{
			///*if (StartTime >= now_time && flag == 0)
			//{
			//	ActivityIdx.x = x;
			//	ActivityIdx.y = ActivityNum[x];
			//	flag = 1;
			//}*/
			int i = ActivityNum[x];
			if (timeline[StartTime] == 0)
			{
				timeline[StartTime] = kind;
				ActivityList[x][i].name = name;
				ActivityList[x][i].StartTime = StartTime;
				ActivityList[x][i].EndTime = StartTime + 1;
				ActivityList[x][i].place = place;
				ActivityList[x][i].id = id;
				ActivityList[x][i].kind = kind;
				ActivityNum[x]++;
			}
			else
			{
				flag = 1;
			}

		}
	}
	if (flag)
	{
		cout << "您有个人活动因冲突被删除" << endl;
	}
	ifs.close();
}


void student::InitGroupActInformation()
{
	for (int i = 0; i < WEEK_NUM; i++)
	{
		GroupActNum[i] = 0;
	}
	//GroupActIdx = { 0,0 };
	//ifstream ifs;
	//int flag = 0;

	string filename = to_string(this->ClassNum);
	filename = filename + "groupact.txt";

	ifstream ifs;

	ifs.open(filename, ios::in);

	if (!ifs.is_open())
	{
		cout << "学生集体活动信息初始化错误" << endl;
		exit(0);
	}

	ifs.clear();
	ifs.seekg(0, ios::beg);

	string name;
	int StartTime;
	//int EndTime;
	string place;
	int Class;
	int kind;
	while (ifs >> name && ifs >> StartTime && ifs >> place && ifs >> Class && ifs >> kind)
	{
		int x = StartTime / 168;
		if (Class == this->ClassNum)//
		{
			/*if (StartTime >= now_time && flag == 0)
			{
				GroupActIdx.x = x;
				GroupActIdx.y = GroupActNum[x];
				flag = 1;
			}*/
			int i = GroupActNum[x];

			timeline[StartTime] = kind;
			GroupActList[x][i].name = name;
			GroupActList[x][i].StartTime = StartTime;
			GroupActList[x][i].EndTime = StartTime + 1;
			GroupActList[x][i].place = place;
			GroupActList[x][i].Class = Class;
			GroupActList[x][i].kind = kind;
			GroupActNum[x]++;
		}
	}
	ifs.close();
}




void student::InitTempActInformation()
{
	for (int i = 0; i < WEEK_NUM; i++)
	{
		TempActNum[i] = 0;
	}
	//TempActIdx = { 0,0 };
	int flag = 0;

	ifstream ifs;

	string filename = to_string(this->id);
	filename = filename + "tempact.txt";

	ifs.open(filename, ios::in);

	if (!ifs.is_open())
	{
		cout << "学生临时事务信息初始化错误" << endl;
		exit(0);
	}

	ifs.clear();
	ifs.seekg(0, ios::beg);

	string name;
	int StartTime;
	//int EndTime;
	string place;
	int id;
	int kind;
	while (ifs >> name && ifs >> StartTime && ifs >> place && ifs >> id && ifs >> kind)
	{
		int x = StartTime / 168;
		if (id == this->id)//
		{
			/*if (StartTime >= now_time && flag == 0)
			{
				TempActIdx.x = x;
				TempActIdx.y = TempActNum[x];
				flag = 1;
			}*/
			int i = TempActNum[x];
			if (timeline[StartTime] == 0)
			{
				timeline[StartTime] = kind;
				TempActList[x][i].name = name;
				TempActList[x][i].StartTime = StartTime;
				TempActList[x][i].EndTime = StartTime + 1;
				TempActList[x][i].place = place;
				TempActList[x][i].id = id;
				TempActList[x][i].kind = kind;
				TempActNum[x]++;
			}
			else
			{
				flag = 1;
			}
		}
	}
	if (flag)
	{
		cout << "您有临时事务因冲突被删除" << endl;
	}
	ifs.close();
}




void student::InitAlarmClockInformation(int now_time)
{
	AlarmNum = 0;
	AlarmIdx = 0;
	int flag = 0;

	string filename = to_string(this->id);
	filename = filename + "alarmclock.txt";
	ifstream ifs;

	ifs.open(filename, ios::in);

	if (!ifs.is_open())
	{
		cout << "闹钟信息初始化错误" << endl;
		exit(0);
	}

	ifs.clear();
	ifs.seekg(0, ios::beg);

	int StartTime;
	int kind;
	int ActTime;
	int id;
	int tp;
	while (ifs >> StartTime && ifs >> kind && ifs >> tp && ifs >> ActTime && ifs >> id)
	{
		if (StartTime >= now_time && id == this->id)
		{
			AlarmList[AlarmNum].StartTime = StartTime;
			AlarmList[AlarmNum].kind = kind;
			AlarmList[AlarmNum].ActTime = ActTime;
			AlarmList[AlarmNum].id = id;
			AlarmList[AlarmNum].type = tp;
			AlarmNum++;
		}
	}
	ifs.close();
}


void student::SaveGroupActInformation()
{
	string filename = to_string(this->ClassNum);
	filename = filename + "groupact.txt";

	ofstream ofs;
	ofs.open(filename, ios::out | ios::trunc);

	if (!ofs.is_open())
	{
		cout << "集体活动储存错误" << endl;
		return;
	}

	for (int i = 0; i < WEEK_NUM; i++)
	{
		for (int j = 0; j < GroupActNum[i]; j++)
		{
			ofs << GroupActList[i][j].name << " "
			<< GroupActList[i][j].StartTime << " "
			<< GroupActList[i][j].EndTime << " "
			<< GroupActList[i][j].place << " "
			<< GroupActList[i][j].Class << " "
			<< GroupActList[i][j].kind << endl;
		}
	}
	ofs.close();
}
void student::SaveActivityInformation()
{
	string filename = to_string(this->id);
	filename = filename + "activity.txt";

	ofstream ofs;
	ofs.open(filename, ios::out | ios::trunc);

	if (!ofs.is_open())
	{
		cout << "个人活动储存错误" << endl;
		return;
	}

	for (int i = 0; i < WEEK_NUM; i++)
	{
		for (int j = 0; j < ActivityNum[i]; j++)
		{
			ofs << ActivityList[i][j].name << " "
			<< ActivityList[i][j].StartTime << " "
			<< ActivityList[i][j].EndTime << " "
			<< ActivityList[i][j].place << " "
			<< ActivityList[i][j].id << " "
			<< ActivityList[i][j].kind << endl;
		}
	}
	ofs.close();
}
void student::SaveTempActInformation()
{
	string filename = to_string(this->id);
	filename = filename + "tempact.txt";

	ofstream ofs;
	ofs.open(filename, ios::out | ios::trunc);

	if (!ofs.is_open())
	{
		cout << "个人活动储存错误" << endl;
		return;
	}

	for (int i = 0; i < WEEK_NUM; i++)
	{
		for (int j = 0; j < TempActNum[i]; j++)
		{
			ofs << TempActList[i][j].name << " "
			<< TempActList[i][j].StartTime << " "
			<< TempActList[i][j].EndTime << " "
			<< TempActList[i][j].place << " "
			<< TempActList[i][j].id << " "
			<< TempActList[i][j].kind << endl;
		}
	}
	ofs.close();
}
void student::SaveAlarmClockInformation()
{
	string filename = to_string(this->id);
	filename = filename + "alarmclock.txt";

	ofstream ofs;
	ofs.open(filename, ios::out | ios::trunc);

	if (!ofs.is_open())
	{
		cout << "个人活动储存错误" << endl;
		return;
	}

	for (int i = AlarmIdx; i < AlarmNum; i++)
	{
		ofs << AlarmList[i].StartTime << " "
		<< AlarmList[i].kind << " "
		<< AlarmList[i].type << " "
		<< AlarmList[i].ActTime << " "
		<< AlarmList[i].id << endl;
		
	}
	ofs.close();
}

void student::ShowClassSchedule(int week)
{
	int CourseL = 0, CourseR = 0;
	int ActivityL = 0, ActivityR = 0;
	int GroupActL = 0, GroupActR = 0;
	int TempActL = 0, TempActR = 0;
	int w = week - 1;
	int num = 0;
	log1.wr(now_time, this->name, "查看课程表");
	//for (int i = 0; i < 20; i++)
	//{
	//	cout << CourseNum[i] << " " << GroupActNum[i] << " " << ActivityNum[i] << " " << TempActNum[i] << endl;
	//}

	//for (int i = 0; i < CourseNum[w]; i++)
	//{
	//	cout << CourseList[w][i].name << " " << CourseList[w][i].StartTime << " " << CourseList[w][i].EndTime << " " << CourseList[w][i].place << " " << CourseList[w][i].kind << endl;//输出课程；
	//}

	for (int i = 0; i < 7; i++)
	{
		num = 0;
		for (CourseR = CourseL; CourseR < CourseNum[w]; CourseR++)
		{
			if ((CourseList[w][CourseR].StartTime % 168) / 24 != i)
			{
				break;
			}
			if (CourseR == 0 || (CourseR > 0 && CourseList[w][CourseR].StartTime != CourseList[w][CourseR - 1].StartTime))
			{
				num++;
			}
		}
		for (GroupActR = GroupActL; GroupActR < GroupActNum[w]; GroupActR++)
		{
			if ((GroupActList[w][GroupActR].StartTime % 168) / 24 != i)
			{
				break;
			}
			if (GroupActR == 0 || (GroupActR > 0 && GroupActList[w][GroupActR].StartTime != GroupActList[w][GroupActR - 1].StartTime))
			{
				num++;
			}

		}
		for (ActivityR = ActivityL; ActivityR < ActivityNum[w]; ActivityR++)
		{
			if ((ActivityList[w][ActivityR].StartTime % 168) / 24 != i)
			{
				break;
			}
			if (ActivityR == 0 || (ActivityR > 0 && ActivityList[w][ActivityR].StartTime != ActivityList[w][ActivityR - 1].StartTime))
			{
				num++;
			}
		}
		for (TempActR = TempActL; TempActR < TempActNum[w]; TempActR++)
		{
			if ((TempActList[w][TempActR].StartTime % 168) / 24 != i)
			{
				break;
			}
			if (TempActR == 0 || (TempActR > 0 && TempActList[w][TempActR].StartTime != TempActList[w][TempActR - 1].StartTime))
			{
				num++;
			}

		}
		//int num = CourseR - CourseL + GroupActR - GroupActL + ActivityR - ActivityL + TempActR - TempActL;
		cout << num << endl;
		while (1)
		{
			if (CourseR == CourseL && GroupActR == GroupActL && ActivityR == ActivityL && TempActR == TempActL)
			{
				break;
			}
			//int Ctm = CourseList[w][CourseL].StartTime, Gtm = GroupActList[w][GroupActL].StartTime, Atm = ActivityList[w][ActivityL].StartTime, Ttm = TempActList[w][TempActL].StartTime;
			int Ctm, Gtm, Atm, Ttm;
			if (CourseL == CourseNum[w])
				Ctm = 100000;
			else
				Ctm = CourseList[w][CourseL].StartTime;

			if (GroupActL == GroupActNum[w])
				Gtm = 100000;
			else
				Gtm = GroupActList[w][GroupActL].StartTime;

			if (ActivityL == ActivityNum[w])
				Atm = 100000;
			else
				Atm = ActivityList[w][ActivityL].StartTime;

			if (TempActL == TempActNum[w])
				Ttm = 100000;
			else
				Ttm = TempActList[w][TempActL].StartTime;

			if (Ctm < Atm && Ctm < Ttm && Ctm < Gtm)
			{
				cout << CourseList[w][CourseL].kind << " " << CourseList[w][CourseL].StartTime << " " << CourseList[w][CourseL].EndTime << " " << CourseList[w][CourseL].name << " " << CourseList[w][CourseL].Class << " " << CourseList[w][CourseL].place << endl;//输出课程；
				CourseL++;
			}
			else if (Gtm < Atm && Gtm < Ttm && Gtm < Ctm)
			{
				cout << GroupActList[w][GroupActL].kind << " " << GroupActList[w][GroupActL].StartTime << " " << GroupActList[w][GroupActL].EndTime << " " << GroupActList[w][GroupActL].Class << " " << GroupActList[w][GroupActL].name << " " << GroupActList[w][GroupActL].place << " " << GroupActList[w][GroupActL].kind << endl;
				GroupActL++;
			}
			else if (Atm < Ctm && Atm < Ttm && Atm < Gtm)
			{
				cout << ActivityList[w][ActivityL].kind << " " << ActivityList[w][ActivityL].StartTime << " " << ActivityList[w][ActivityL].EndTime << " " << ActivityList[w][ActivityL].place << " " << ActivityList[w][ActivityL].name << " " << ActivityList[w][ActivityL].type << endl;//对应活动
				ActivityL++;
			}
			else if (Ttm < Ctm && Ttm < Atm && Ttm < Gtm)
			{
				int tmpr = TempActL;
				while (TempActList[w][tmpr].StartTime == TempActList[w][TempActL].StartTime && tmpr < TempActR)
				{
					tmpr++;
				}

				cout << TempActList[w][TempActL].kind << " " << TempActList[w][TempActL].StartTime << " " << TempActList[w][TempActL].EndTime << " " << tmpr - TempActL << " ";
				while (TempActL < tmpr)
				{
					cout << TempActList[w][TempActL].name << " " << TempActList[w][TempActL].place << " ";
					TempActL++;
				}
				cout << endl;
				/*cout << TempActList[w][TempActL].name << " " << TempActList[w][TempActL].StartTime << " " << TempActList[w][TempActL].EndTime << " " << TempActList[w][TempActL].place << " " << TempActList[w][TempActL].kind << " ";
				TempActL++;
				while (TempActList[w][TempActL].StartTime == TempActList[w][TempActL - 1].StartTime)
				{
					cout <<
				}*/
			}
		}
	}
}



int student::Search(int kind, string name, int now_time)//半成品
{
	int w = now_time / 168;
	int ret = -1;
	int flag = 0;
	cout << now_time << " " << w << endl;
	if (kind == 1)
	{
		log1.wr(now_time, this->name, "查询课程");
		int x = w, y = 0;
		for (y = 0; y < CourseNum[x]; y++)
		{
			if (CourseList[x][y].StartTime > now_time)
			{
				break;
			}
		}
		for (int i = x; i < WEEK_NUM; i++)
		{
			if (i == x)
			{
				for (int j = y; j < CourseNum[i]; j++)
				{
					if (CourseList[i][j].name == name)
					{
						flag = 1;
						ret = x;
						break;
					}
				}
			}
			else
			{
				for (int j = 0; j < CourseNum[i]; j++)
				{
					if (CourseList[i][j].name == name)
					{
						flag = 1;
						ret = i;
						break;
					}
				}
			}
			if (flag)
				break;
		}
	}
	else if (kind == 2)
	{
		log1.wr(now_time, this->name, "查询集体活动");
		int x = w, y = 0;
		for (y = 0; y < GroupActNum[x]; y++)
		{
			if (GroupActList[x][y].StartTime > now_time)
			{
				break;
			}
		}
		for (int i = x; i < WEEK_NUM; i++)
		{
			if (i == x)
			{
				for (int j = y; j < GroupActNum[i]; j++)
				{
					if (GroupActList[i][j].name == name)
					{
						flag = 1;
						ret = x;
						break;
					}
				}
			}
			else
			{
				for (int j = 0; j < CourseNum[i]; j++)
				{
					if (GroupActList[i][j].name == name)
					{
						flag = 1;
						ret = i;
						break;
					}
				}
			}
			if (flag)
				break;
		}
	}
	else if (kind == 3)
	{
		log1.wr(now_time, this->name, "查询个人活动");
		int x = w, y = 0;
		for (y = 0; y < ActivityNum[y]; y++)
		{
			if (ActivityList[x][y].StartTime > now_time)
			{
				break;
			}
		}
		for (int i = x; i < WEEK_NUM; i++)
		{
			if (i == x)
			{
				for (int j = y; j < ActivityNum[i]; j++)
				{
					if (ActivityList[i][j].name == name)
					{
						flag = 1;
						ret = x;
						break;
					}
				}
			}
			else
			{
				for (int j = 0; j < ActivityNum[i]; j++)
				{
					if (ActivityList[i][j].name == name)
					{
						flag = 1;
						ret = i;
						break;
					}
				}
			}
			if (flag)
				break;
		}
	}
	else if (kind == 4)
	{
		log1.wr(now_time, this->name, "查询临时事务");
		int x = w, y = 0;
		for (y = 0; y < TempActNum[y]; y++)
		{
			if (TempActList[x][y].StartTime > now_time)
			{
				break;
			}
		}
		for (int i = x; i < WEEK_NUM; i++)
		{
			if (i == x)
			{
				for (int j = y; j < TempActNum[i]; j++)
				{
					if (TempActList[i][j].name == name)
					{
						flag = 1;
						ret = x;
						break;
					}
				}
			}
			else
			{
				for (int j = 0; j < TempActNum[i]; j++)
				{
					if (TempActList[i][j].name == name)
					{
						flag = 1;
						ret = i;
						break;
					}
				}
			}
			if (flag)
				break;
		}
	}
	return ret + 1;

}


void student::AddGroupAct()
{
	cout << "请输入集体活动的开始时间" << endl;
	int tm;
	cin >> tm;
	group_act tmp;

	if (timeline[tm] == 0)
	{
		tmp.kind = 2;
		tmp.Class = this->ClassNum;
		tmp.StartTime = tm;
		tmp.EndTime = tmp.StartTime + 1;
		int w = tmp.StartTime / 168;

		cout << "请输入集体活动的名称与地点" << endl;
		cin >> tmp.name >> tmp.place;

		GroupActList[w][GroupActNum[w]] = tmp;
		GroupActNum[w]++;

		for (int i = GroupActNum[w] - 1; i >= 1; i--)
		{
			if (GroupActList[w][i].StartTime < GroupActList[w][i - 1].StartTime)
			{
				group_act x;
				x = GroupActList[w][i];
				GroupActList[w][i] = GroupActList[w][i - 1];
				GroupActList[w][i - 1] = x;
			}
		}
		timeline[tm] = 2;
		log1.wr(now_time, this->name, "添加一个集体活动");
	}
	else
	{
		cout << "时间冲突" << endl;

		int a = tm % 24;
		int num = 0;


		for (int i = tm - a + 6; i < tm - a + 21; i++)
		{
			if (timeline[i] == 0 && num < 3)
			{
				cout << i << endl;
				num++;
			}
		}

		if (num == 0)
		{
			cout << "无可用时间" << endl;
		}
	}
	//可以刷新一下课表
}

void student::AddActivity()
{
	//cout << "请输入个人活动的开始时间" << endl;
	//int tm;
	//cin >> tm;
	cout << "请输入周期类型:1 单次，2 每天，3 每周" << endl;
	int tp;
	cin >> tp;

	activity tmp;

	if (tp == 1)
	{
		cout << "请输入个人活动的开始时间,名称，地点" << endl;
		int tm;
		string name, place;
		cin >> tm >> name >> place;
		AddSingleActivity(tm, name, place, tp);
		log1.wr(now_time, this->name, "添加一个单次的个人活动");
	}
	else if (tp == 2)
	{
		cout << "请输入个人活动的开始时间,结束时间,名称，地点" << endl;
		int tm, endtm;
		string name, place;
		cin >> tm >> endtm >> name >> place;
		for (tm; tm <= endtm; tm += 24)
		{
			int x = AddSingleActivity(tm, name, place, tp);
			if (x == 0)
			{
				int w = tm / 168 + 1, d = (tm % 168) / 24 + 1;
				cout << "第" << w << "周周" << d << "活动有冲突，插入失败" << endl;
			}
		}
		log1.wr(now_time, this->name, "添加一个每天的个人活动");
	}
	else if (tp == 3)
	{
		cout << "请输入个人活动的开始时间,结束时间,名称，地点" << endl;
		int tm, endtm;
		string name, place;
		cin >> tm >> endtm >> name >> place;
		for (tm; tm <= endtm; tm += 168)
		{
			int x = AddSingleActivity(tm, name, place, tp);
			if (x == 0)
			{
				int w = tm / 168 + 1;
				cout << "第" << w << "周活动有冲突，插入失败" << endl;
			}
		}
		log1.wr(now_time, this->name, "添加一个每周的个人活动");
	}




	//可以刷新一下课表
}


int student::AddSingleActivity(int tm, string name, string place, int type)
{
	activity tmp;
	if (timeline[tm] == 0)
	{
		tmp.kind = 3;
		tmp.id = this->id;
		tmp.StartTime = tm;
		tmp.EndTime = tmp.StartTime + 1;
		tmp.type = type;
		tmp.name = name;
		tmp.place = place;
		int w = tmp.StartTime / 168;
		//cout << "请输入集体活动的名称与地点" << endl;

		ActivityList[w][ActivityNum[w]] = tmp;
		ActivityNum[w]++;

		for (int i = ActivityNum[w] - 1; i >= 1; i--)
		{
			if (ActivityList[w][i].StartTime < ActivityList[w][i - 1].StartTime)
			{
				activity x;
				x = ActivityList[w][i];
				ActivityList[w][i] = ActivityList[w][i - 1];
				ActivityList[w][i - 1] = x;
			}
			else
			{
				break;
			}
		}
		timeline[tm] = 3;
		return 1;
	}
	else
	{
		if (type == 1)
		{
			cout << "时间冲突" << endl;

			int a = tm % 24;
			int num = 0;

			for (int i = tm - a + 6; i < tm - a + 21; i++)
			{
				if (timeline[i] == 0 && num < 3)
				{
					cout << i << endl;
					num++;
				}
			}
			if (num == 0)
			{
				cout << "无可用时间" << endl;
			}
		}
		return 0;
	}
}


void student::AddTempAct()
{
	cout << "请输入临时事务的开始时间" << endl;
	int tm;
	cin >> tm;
	temp_act tmp;

	if (timeline[tm] == 0 || timeline[tm] == 4)
	{
		tmp.kind = 4;
		tmp.id = this->id;
		tmp.StartTime = tm;
		tmp.EndTime = tm + 1;
		int w = tmp.StartTime / 168;
		cout << "请输入临时事务的名称与地点" << endl;
		cin >> tmp.name >> tmp.place;

		TempActList[w][TempActNum[w]] = tmp;
		TempActNum[w]++;

		for (int i = TempActNum[w] - 1; i >= 1; i--)
		{
			if (TempActList[w][i].StartTime < TempActList[w][i - 1].StartTime)
			{
				temp_act x;
				x = TempActList[w][i];
				TempActList[w][i] = TempActList[w][i - 1];
				TempActList[w][i - 1] = x;
			}
		}
		timeline[tm] = 4;
		log1.wr(now_time, this->name, "添加一个临时事务");
	}
	else
	{
		cout << "时间冲突，输入失败" << endl;
	}
	//可以刷新一下课表
}

void student::DeleteGroupAct()
{
	cout << "请输入起始时间" << endl;
	int tm;
	cin >> tm;

	int w = tm / 168;
	int idx;
	for (idx = 0; idx < GroupActNum[w]; idx++)
	{
		if (GroupActList[w][idx].StartTime == tm)
		{
			break;
		}
	}
	if (idx == GroupActNum[w])
	{
		cout << "不存在该事务" << endl;
	}
	for (int i = idx; i < GroupActNum[w] - 1; i++)
	{
		GroupActList[w][i] = GroupActList[w][i + 1];
	}
	GroupActNum[w]--;
	timeline[tm] = 0;
	log1.wr(now_time, this->name, "删除一个集体活动");
}

void student::DeleteActivity()
{
	cout << "请输入起始时间" << endl;
	int tm;
	cin >> tm;

	int w = tm / 168;
	int idx;
	for (idx = 0; idx < ActivityNum[w]; idx++)
	{
		if (ActivityList[w][idx].StartTime == tm)
		{
			break;
		}
	}
	if (idx == ActivityNum[w])
	{
		cout << "不存在该事务" << endl;
	}
	for (int i = idx; i < ActivityNum[w] - 1; i++)
	{
		ActivityList[w][i] = ActivityList[w][i + 1];
	}
	ActivityNum[w]--;
	timeline[tm] = 0;
	log1.wr(now_time, this->name, "删除一个个人活动");
}

void student::DeleteTempAct()
{
	cout << "请输入起始时间" << endl;
	int tm;
	cin >> tm;
	cout << "请输入事务名称" << endl;
	string nm;
	cin >> nm;



	int w = tm / 168;
	int idx;

	for (idx = 0; idx < TempActNum[w]; idx++)
	{
		if (TempActList[w][idx].StartTime == tm && TempActList[w][idx].name == nm)
		{
			break;
		}
	}
	if (idx == TempActNum[w])
	{
		cout << "不存在该事务" << endl;
	}
	for (int i = idx; i < TempActNum[w] - 1; i++)
	{
		TempActList[w][i] = TempActList[w][i + 1];
	}
	TempActNum[w]--;

	int flag = 0;
	for (int i = 0; i < TempActNum[w]; i++)
	{
		if (TempActList[w][idx].StartTime == tm)
		{
			flag = 1;
			break;
		}
	}
	if (!flag)
		timeline[tm] = 0;
	log1.wr(now_time, this->name, "删除一个临时事务");

}

void student::SystemAlarmClock(int now_time)
{
	//int flag = 0;

	int w = now_time / 168;
	if (now_time % 24 == 0)
	{
		//log1.wr(now_time, this->name, "系统提醒第二天课程与活动");
		int CourseL = 0, CourseR = 0;
		int GroupActL = 0, GroupActR = 0;
		int ActivityL = 0, ActivityR = 0;
		//int idx = 0;
		for (CourseL = 0; CourseL < CourseNum[w]; CourseL++)
		{
			if (CourseList[w][CourseL].StartTime >= now_time)
			{
				break;
			}
		}
		for (CourseR = CourseL; CourseR < CourseNum[w]; CourseR++)
		{
			int tm = CourseList[w][CourseR].StartTime;
			if (tm >= now_time + 24)
			{
				break;
			}//输出信息；
		}
		for (GroupActL = 0; GroupActL < GroupActNum[w]; GroupActL++)
		{
			if (GroupActList[w][GroupActL].StartTime >= now_time)
			{
				break;
			}
		}
		for (GroupActR = GroupActL; GroupActR < GroupActNum[w]; GroupActR++)
		{
			int tm = GroupActList[w][GroupActR].StartTime;
			if (tm >= now_time + 24)
			{
				break;
			}
		}
		for (ActivityL = 0; ActivityL < ActivityNum[w]; ActivityL++)
		{
			if (ActivityList[w][ActivityL].StartTime >= now_time)
			{
				break;
			}
		}
		for (ActivityR = ActivityL; ActivityR < ActivityNum[w]; ActivityR++)
		{
			int tm = ActivityList[w][ActivityR].StartTime;
			if (tm >= now_time + 24)
			{
				break;
			}
		}
		int num = CourseR - CourseL + GroupActR - GroupActL + ActivityR - ActivityL;
		cout << num << endl;
		while (1)
		{
			if (CourseR == CourseL && GroupActR == GroupActL && ActivityR == ActivityL)
			{
				break;
			}
			//int Ctm = CourseList[w][CourseL].StartTime, Gtm = GroupActList[w][GroupActL].StartTime, Atm = ActivityList[w][ActivityL].StartTime, Ttm = TempActList[w][TempActL].StartTime;
			int Ctm, Gtm, Atm;
			if (CourseL == CourseNum[w])
				Ctm = 100000;
			else
				Ctm = CourseList[w][CourseL].StartTime;

			if (GroupActL == GroupActNum[w])
				Gtm = 100000;
			else
				Gtm = GroupActList[w][GroupActL].StartTime;

			if (ActivityL == ActivityNum[w])
				Atm = 100000;
			else
				Atm = ActivityList[w][ActivityL].StartTime;

			if (Ctm < Atm && Ctm < Gtm)
			{
				cout << CourseList[w][CourseL].kind << " " << CourseList[w][CourseL].StartTime << " " << CourseList[w][CourseL].EndTime << " " << CourseList[w][CourseL].name << " " << CourseList[w][CourseL].Class << " " << CourseList[w][CourseL].place << endl;//输出课程；
				CourseL++;
			}
			else if (Gtm < Atm && Gtm < Ctm)
			{
				cout << GroupActList[w][GroupActL].kind << " " << GroupActList[w][GroupActL].StartTime << " " << GroupActList[w][GroupActL].EndTime << " " << GroupActList[w][GroupActL].Class << " " << GroupActList[w][GroupActL].name << " " << GroupActList[w][GroupActL].place << " " << GroupActList[w][GroupActL].kind << endl;
				GroupActL++;
			}
			else if (Atm < Ctm && Atm < Gtm)
			{
				cout << ActivityList[w][ActivityL].kind << " " << ActivityList[w][ActivityL].StartTime << " " << ActivityList[w][ActivityL].EndTime << " " << ActivityList[w][ActivityL].place << " " << ActivityList[w][ActivityL].name << " " << ActivityList[w][ActivityL].type << endl;//对应活动
				ActivityL++;
			}
		}
		//while (true)
		//{
		//	Sleep(100);
		//	if (this->stop)
		//		break;
		//	int w = now_time / 168;
		//	if (now_time % 24 == 0 && flag == 0)
		//	{
		//		int idx = 0;
		//		for (idx = 0; idx < CourseNum[w]; idx++)
		//		{
		//			if (CourseList[w][idx].StartTime >= now_time)
		//			{
		//				break;
		//			}
		//		}
		//		for (int i = idx; i < CourseNum[w]; i++)
		//		{
		//			int tm = CourseList[w][i].StartTime;
		//			if (tm >= now_time + 24)
		//			{
		//				break;
		//			}
		//			cout << "";//输出信息；
		//		}
		//		for (idx = 0; idx < GroupActNum[w]; idx++)
		//		{
		//			if (GroupActList[w][idx].StartTime >= now_time)
		//			{
		//				break;
		//			}
		//		}
		//		for (int i = idx; i < GroupActNum[w]; i++)
		//		{
		//			int tm = GroupActList[w][i].StartTime;
		//			if (tm >= now_time + 24)
		//			{
		//				break;
		//			}
		//			cout << "";//输出信息；
		//		}
		//		for (idx = 0; idx < ActivityNum[w]; idx++)
		//		{
		//			if (ActivityList[w][idx].StartTime >= now_time)
		//			{
		//				break;
		//			}
		//		}
		//		for (int i = idx; i < ActivityNum[w]; i++)
		//		{
		//			int tm = ActivityList[w][i].StartTime;
		//			if (tm >= now_time + 24)
		//			{
		//				break;
		//			}
		//			cout << "";//输出信息；
		//		}

		//	}
		//	else if (now_time % 24 != 0)
		//	{
		//		flag = 0;
		//	}
		//}

	}

}

void student::TempAlarmClock(int now_time)
{

	//int flag = 0;

	int tmpx, tmpy;
	tmpx = CourseIdx.x, tmpy = CourseIdx.y;
	if (now_time == CourseList[tmpx][tmpy].StartTime)
	{
		if (tmpy == CourseNum[tmpx] - 1)
		{
			CourseIdx.x++, CourseIdx.y = 0;
		}
		else
		{
			CourseIdx.y++;
		}
	}
	tmpx = CourseIdx.x, tmpy = CourseIdx.y;
	if (now_time == CourseList[tmpx][tmpy].StartTime - 1)
	{
		//log1.wr(now_time, this->name, "提前一小时提醒课程");
		cout << CourseList[tmpx][tmpy].kind << " " << CourseList[tmpx][tmpy].StartTime << " " << CourseList[tmpx][tmpy].EndTime << " " << CourseList[tmpx][tmpy].name << " " << CourseList[tmpx][tmpy].Class << " " << CourseList[tmpx][tmpy].place << endl;//输出信息			//调用导航

	}



	//while (true)
	//{
	//	Sleep(100);
	//	if (this->stop)
	//		break;
	//	tmpx = CourseIdx.x, tmpy = CourseIdx.y;
	//	if (now_time == CourseList[tmpx][tmpy].StartTime)
	//	{
	//		if (tmpy == CourseNum[tmpx] - 1)
	//		{
	//			CourseIdx.x++, CourseIdx.y = 0;
	//		}
	//		else
	//		{
	//			CourseIdx.y++;
	//		}
	//	}
	//	tmpx = CourseIdx.x, tmpy = CourseIdx.y;
	//	if (now_time == CourseList[tmpx][tmpy].StartTime - 1)
	//	{
	//		if (flag == 0)
	//		{
	//			cout << "";//输出信息
	//			//调用导航
	//			flag = 1;
	//		}
	//	}
	//	else
	//	{
	//		flag = 0;
	//	}
	//}
}


void student::PersonalAlarmClock(int now_time)
{

	if (AlarmIdx < AlarmNum)
	{
		if (now_time == AlarmList[AlarmIdx].StartTime)
		{

			ShowInfo(AlarmList[AlarmIdx].kind, AlarmList[AlarmIdx].ActTime);
			//调用导航
			if (AlarmList[AlarmIdx].type == 2)
			{
				AddPersonalAlarmClock(AlarmList[AlarmIdx].StartTime + 24, AlarmList[AlarmIdx].kind, AlarmList[AlarmIdx].ActTime + 24, AlarmList[AlarmIdx].type);
			}
			if (AlarmList[AlarmIdx].type == 3)
			{
				AddPersonalAlarmClock(AlarmList[AlarmIdx].StartTime + 168, AlarmList[AlarmIdx].kind, AlarmList[AlarmIdx].ActTime + 168, AlarmList[AlarmIdx].type);
			}
			//flag = 1;
			AlarmIdx++;

		}
	}
	//int flag = 0;

	//while (true)
	//{
		//Sleep(100);
		//if (this->stop)
		//	break;
		//if (AlarmIdx < AlarmNum)
		//{
		//	if (now_time == AlarmList[AlarmIdx].StartTime)
		//	{
		//		if (flag == 0)
		//		{
		//			ShowInfo(AlarmList[AlarmIdx].kind, AlarmList[AlarmIdx].ActTime);
		//			//调用导航
		//			if (AlarmList[AlarmIdx].type == 2)
		//			{
		//				AddPersonalAlarmClock(AlarmList[AlarmIdx].StartTime + 24, AlarmList[AlarmIdx].kind, AlarmList[AlarmIdx].ActTime + 24, AlarmList[AlarmIdx].type);
		//			}
		//			if (AlarmList[AlarmIdx].type == 3)
		//			{
		//				AddPersonalAlarmClock(AlarmList[AlarmIdx].StartTime + 168, AlarmList[AlarmIdx].kind, AlarmList[AlarmIdx].ActTime + 168, AlarmList[AlarmIdx].type);
		//			}
		//			flag = 1;
		//			AlarmIdx++;
		//		}
		//	}
		//	else
		//	{
		//		flag = 0;
		//	}
		//}
	//}
}

void student::AddPersonalAlarmClock(int starttime, int kind, int acttime, int tp)
{
	alarm x;

	//int tp;
	///*cout << "请输入闹钟时间，闹钟类型，活动开始时间" << endl;
	//cin >> x.StartTime >> x.kind >> x.ActTime;
	//cout << "请输入周期：1 单次，2 每天，3 每周" << endl;
	//cin >> x.type;*/
	x.StartTime = starttime;
	x.kind = kind;
	x.ActTime = acttime;
	x.type = tp;
	x.id = this->id;


	AlarmList[AlarmNum] = x;
	AlarmNum++;

	for (int i = AlarmNum - 1; i > AlarmIdx; i--)
	{
		alarm a;
		if (AlarmList[i].StartTime < AlarmList[i - 1].StartTime)
		{
			a = AlarmList[i];
			AlarmList[i] = AlarmList[i - 1];
			AlarmList[i - 1] = a;
		}
		else
		{
			break;
		}
	}
	switch (tp)
	{
	case 1:
		log1.wr(now_time, this->name, "添加一个单次闹钟");
		break;
	case 2:
		log1.wr(now_time, this->name, "添加一个每天闹钟");
		break;
	case 3:
		log1.wr(now_time, this->name, "添加一个每周闹钟");
		break;
	}
}

void student::DeletePersonalAlarmClock()
{
	int tm, idx;
	cin >> tm;
	for (idx = AlarmIdx; idx < AlarmNum; idx++)
	{
		if (AlarmList[idx].StartTime == tm)
		{
			break;
		}
	}
	for (int i = idx; i < AlarmNum - 1; i++)
	{
		AlarmList[i] = AlarmList[i + 1];
	}
	AlarmNum--;
		
	log1.wr(now_time, this->name, "删除一个单次闹钟");
}


void student::ShowPersonalAlarmClock()
{
	cout << AlarmNum - AlarmIdx << endl;
	for (int i = AlarmIdx; i < AlarmNum; i++)
	{
		cout << AlarmList[i].kind << " " << AlarmList[i].StartTime << " " << AlarmList[i].ActTime << " ";
		ShowInfo(AlarmList[i].kind, AlarmList[i].ActTime);
	}
	log1.wr(now_time, this->name, "展示闹钟信息");
}

void student::ShowInfo(int kind, int ActTime)
{
	int w = ActTime / 168;
	int idx = -1;

	if (kind == 1)
	{
		for (int i = 0; i < CourseNum[w]; i++)
		{
			if (CourseList[w][i].StartTime == ActTime)
			{
				idx = i;
				break;
			}
		}
		if (idx == -1)
		{
			return;
		}
		cout << CourseList[w][idx].kind << " " << CourseList[w][idx].StartTime << " " << CourseList[w][idx].EndTime << " " << CourseList[w][idx].name << " " << CourseList[w][idx].Class << " " << CourseList[w][idx].place << endl;
	}
	else if (kind == 2)
	{
		for (int i = 0; i < GroupActNum[w]; i++)
		{
			if (GroupActList[w][i].StartTime == ActTime)
			{
				idx = i;
				break;
			}
		}
		if (idx == -1)
		{
			return;
		}
		cout << GroupActList[w][idx].kind << " " << GroupActList[w][idx].StartTime << " " << GroupActList[w][idx].EndTime << " " << GroupActList[w][idx].Class << " " << GroupActList[w][idx].name << " " << GroupActList[w][idx].place << " " << GroupActList[w][idx].kind << endl;
	}
	else if (kind == 3)
	{
		for (int i = 0; i < ActivityNum[w]; i++)
		{
			if (ActivityList[w][i].StartTime == ActTime)
			{
				idx = i;
				break;
			}
		}
		if (idx == -1)
		{
			return;
		}
		cout << ActivityList[w][idx].kind << " " << ActivityList[w][idx].StartTime << " " << ActivityList[w][idx].EndTime << " " << ActivityList[w][idx].place << " " << ActivityList[w][idx].name << " " << ActivityList[w][idx].type << endl;
	}
	else if (kind == 4)
	{
		for (int i = 0; i < TempActNum[w]; i++)
		{
			if (TempActList[w][i].StartTime == ActTime)
			{
				idx = i;
				break;
			}
		}
		if (idx == -1)
		{
			return;
		}
		int tmpr = idx;
		while (TempActList[w][tmpr].StartTime == TempActList[w][idx].StartTime && tmpr < TempActNum[w])
		{
			tmpr++;
		}

		cout << TempActList[w][idx].kind << " " << TempActList[w][idx].StartTime << " " << TempActList[w][idx].EndTime << " " << tmpr - idx << " ";
		while (idx < tmpr)
		{
			cout << TempActList[w][idx].name << " " << TempActList[w][idx].place << " ";
			idx++;
		}
		cout << endl;
	}

}

