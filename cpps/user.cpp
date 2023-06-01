#include<iostream>
#include<fstream>
#include<windows.h>
#include<wchar.h>
#include<direct.h>
#include<string>
#include<chrono>
#include"user.h"
#include"Time.h"
#include "CLog.h"
#include"stringop.h"
#include"findWay.h"
// #include"CLog.cpp"
using namespace std;

#define ASK_FOR_COURSE 1
#define ADD_ACTIVITY 2
#define DEL_ACTIVITY 3
#define MODIFY_ACTIVITY 4
#define SEARCH_ACTIVITY 5
#define FIND_SINGLE_WAY 6
#define FIND_MULTIPLE_WAY 7
#define ADD_ALARM 8
#define DEL_ALARM 9
#define MODIFY_ALARM 10
#define INIT 11
#define CHECK_ALARM 12
#define SET_TIME 13

#define ADD_STUDENT 1
#define DEL_STUDENT 2
#define MODIFY_STUDENT 3
#define ADD_COURSE 4
#define DEL_COURSE 5
#define MODIFY_COURSE 6

ofstream ofsCou;
ofstream ofsAla;
ifstream ifsArg;

student StudentList[MAX_PEOPLE];
int StudentCnt;
manager ManagerList[MAX_PEOPLE];
int ManagerCnt;

graph g;
CLog log1;

student::student() {};
student::~student() {};
manager::manager() {};
manager::~manager() {};

void student::ManageSystem()
{
	// Init();
	g.init_graph();
	// cout<<"欢迎登陆"<<endl;
	ofsCou.open("../htmls/pagebuffer.txt");
	ofsCou<<-1<<endl;
	this->ShowClassSchedule(1);
	
	

	DWORD cbBytes;
	char notify[1024];
	char buffer[256];
    _getcwd(buffer,256);
	TCHAR dir[256];
    #ifdef UNICODE
        MultiByteToWideChar(CP_ACP,0,buffer,-1,dir,256);
    #else
        strcpy(dir,buffer);
    #endif
    cout<<buffer<<endl;
    cout<<dir<<endl;
	
	HANDLE dirHandle = CreateFile(dir,
								  GENERIC_READ | GENERIC_WRITE | FILE_LIST_DIRECTORY,
								  FILE_SHARE_READ | FILE_SHARE_WRITE,
								  NULL,
								  OPEN_EXISTING,
								  FILE_FLAG_BACKUP_SEMANTICS,
								  NULL);

	if (dirHandle == INVALID_HANDLE_VALUE)
	{
		cout << "error" + GetLastError() << endl;
	}

	memset(notify, 0, strlen(notify));
	FILE_NOTIFY_INFORMATION *pnotify = (FILE_NOTIFY_INFORMATION *)notify;

	cout << "Start Monitor..." << endl;

	
	int flag=0;

	
	long long lastTS = 0, nowTS = 0;
	// int level=0;
	while (true)
	{
		cout<<"Monitoring"<<endl;
		if (ReadDirectoryChangesW(dirHandle, &notify, 1024, true,
								  FILE_NOTIFY_CHANGE_FILE_NAME | FILE_NOTIFY_CHANGE_LAST_ACCESS,
								  &cbBytes, NULL, NULL))
		{
			std::chrono::milliseconds ms = std::chrono::duration_cast< std::chrono::milliseconds >(
        		std::chrono::system_clock::now().time_since_epoch()
    		);
			nowTS = ms.count();
			if(nowTS - lastTS <= 500)
			{
				lastTS = nowTS;
				cout<<nowTS<<endl;
				continue;
			}
			lastTS = nowTS;

			switch (pnotify->Action)
			{	
			case FILE_ACTION_MODIFIED:
                cout<<"Modified"<<endl;
				cout<<"test"<<endl;
				
				string s;
				ifsArg.open("js2exe.txt",ios::in);
				ifsArg>>flag;
				cout<<flag<<endl;
				int w,NTS,scrollTop;
				int searchWeek;
				string searchName;
				long long nowTimeStamp;
				int timeWalkPace;
				int c_point,end,start;
				int starttime,kind,acttime,tp;
				int point[50];
				int type;
				
				// DelLineData(2);
				switch (flag)
				{
				case INIT:
					log1.init("../datas/log.txt");
					ifsArg>>w>>s>>nowTimeStamp>>scrollTop;
					log1.wr(this->name , "登陆了学生管理系统");

					ofsCou.close();
					ofsCou.open("../htmls/pagebuffer.txt");
					ofsCou<<0<<endl<<w<<endl<<s<<endl<<nowTimeStamp<<endl<<scrollTop<<endl;
					
					ifsArg >> NTS;
					Init(NTS);
					this->ShowClassSchedule(w);
					ShowPersonalAlarmClock();
					break;

				case ASK_FOR_COURSE:
					ifsArg>>w>>s>>nowTimeStamp>>scrollTop;

					ofsCou.close();
					ofsCou.open("../htmls/pagebuffer.txt");
					ofsCou<<0<<endl<<w<<endl<<s<<endl<<nowTimeStamp<<endl<<scrollTop<<endl;
					// ofsCou<<0<<endl;
					ofsCou.close();
					this->ShowClassSchedule(w);
					break;

				case ADD_ACTIVITY:
					ifsArg>>w>>s>>nowTimeStamp>>scrollTop;

					ofsCou.close();
					ofsCou.open("../htmls/pagebuffer.txt");
					ofsCou<<0<<endl<<w<<endl<<s<<endl<<nowTimeStamp<<endl<<scrollTop<<endl;

					ifsArg>>type;
					if(type == 2)
						AddGroupAct();
					else if(type == 3)
						AddActivity();
					else if(type == 4)
					{
						int num;
						ifsArg>>num;
						for(int i=1;i<=num;i++)
						{
							AddTempAct();
						}
						
					}
						
					this->ShowClassSchedule(w);
					break;

				case DEL_ACTIVITY:
					ifsArg>>w>>s>>nowTimeStamp>>scrollTop;

					ofsCou.close();
					ofsCou.open("../htmls/pagebuffer.txt");
					ofsCou<<0<<endl<<w<<endl<<s<<endl<<nowTimeStamp<<endl<<scrollTop<<endl;

					ifsArg>>type;
					if(type == 2)
						DeleteGroupAct();
					else if(type == 3)
						DeleteActivity();
					else if(type == 4)
					{
						int num;
						ifsArg >> num;
						for(int i=1;i<=num;i++)
						{
							DeleteTempAct();
						}
					}

					this->ShowClassSchedule(w);
					break;

				case MODIFY_ACTIVITY:
					ifsArg>>w>>s>>nowTimeStamp>>scrollTop;

					ofsCou.close();
					ofsCou.open("../htmls/pagebuffer.txt");
					ofsCou<<0<<endl<<w<<endl<<s<<endl<<nowTimeStamp<<endl<<scrollTop<<endl;

					ifsArg>>type;
					if(type == 2)
					{
						DeleteGroupAct();
						AddGroupAct();
					}
						
					else if(type == 3)
					{
						DeleteActivity();
						AddActivity();
					}
						
					else if(type == 4)
					{
						int num;
						ifsArg>>num;
						for(int i=1;i<=num;i++)
						{
							DeleteTempAct();
						}
						ifsArg>>num;
						for(int i=1;i<=num;i++)
						{
							AddTempAct();
						}
					}
						
					this->ShowClassSchedule(w);
					ShowPersonalAlarmClock();
					break;

				case SEARCH_ACTIVITY:
					ifsArg>>w>>s>>nowTimeStamp>>scrollTop;

					ofsCou.close();
					ofsCou.open("../htmls/pagebuffer.txt");
					ofsCou<<0<<endl;

					ifsArg >> type;
					ifsArg >> searchName;
					ifsArg >> NTS;
					searchName = UTF8_To_string(searchName);
					searchWeek = Search(type,searchName,NTS);

					if(searchWeek > 0)
					{
						ofsCou<<searchWeek<<endl;
						ofsCou<<"null"<<endl;
						ofsCou<<nowTimeStamp<<endl;
						ofsCou<<scrollTop<<endl;
						this->ShowClassSchedule(searchWeek);
					}
					else
					{
						ofsCou<<w<<endl;
						ofsCou<<s<<endl;
						ofsCou<<nowTimeStamp<<endl;
						ofsCou<<scrollTop<<endl;
						this->ShowClassSchedule(w);

						ofsCou<<1<<endl;
						ofsCou<<"查找不到该日程"<<endl;
					}
					break;
				
				case FIND_SINGLE_WAY:
					ifsArg>>w;
					ifsArg>>s;
					ifsArg>>nowTimeStamp;

					ofsCou.close();
					ofsCou.open("../htmls/pagebuffer.txt");
					ofsCou<<2<<endl;
					ofsCou<<w<<endl;
					ofsCou<<s<<endl;
					ofsCou<<nowTimeStamp<<endl;

					ifsArg>>start>>end;
					g.dij(start,end);
					break;

				case FIND_MULTIPLE_WAY:
					ifsArg>>w;
					ifsArg>>s;
					ifsArg>>nowTimeStamp;

					ofsCou.close();
					ofsCou.open("../htmls/pagebuffer.txt");
					ofsCou<<2<<endl;
					ofsCou<<w<<endl;
					ofsCou<<s<<endl;
					ofsCou<<nowTimeStamp<<endl;

					ifsArg>>c_point;
					for(int i=0;i<c_point;i++)
						ifsArg>>point[i];
					g.floyd(c_point,point);
					break;

				case ADD_ALARM:
					ifsArg>>w;
					ifsArg>>s;
					ifsArg>>nowTimeStamp;

					ofsCou.close();
					ofsCou.open("../htmls/pagebuffer.txt");
					ofsCou<<1<<endl;
					ofsCou<<w<<endl;
					ofsCou<<s<<endl;
					ofsCou<<nowTimeStamp<<endl;

					ifsArg >> starttime >> kind >> acttime >> tp;
					AddPersonalAlarmClock(starttime,kind,acttime,tp);
					ShowPersonalAlarmClock();
					break;
				
				case DEL_ALARM:
					ifsArg>>w;
					ifsArg>>s;
					ifsArg>>nowTimeStamp;

					ofsCou.close();
					ofsCou.open("../htmls/pagebuffer.txt");
					ofsCou<<1<<endl;
					ofsCou<<w<<endl;
					ofsCou<<s<<endl;
					ofsCou<<nowTimeStamp<<endl;

					DeletePersonalAlarmClock();
					ShowPersonalAlarmClock();
					break;

				case MODIFY_ALARM:
					ifsArg>>w;
					ifsArg>>s;
					ifsArg>>nowTimeStamp;

					ofsCou.close();
					ofsCou.open("../htmls/pagebuffer.txt");
					ofsCou<<1<<endl;
					ofsCou<<w<<endl;
					ofsCou<<s<<endl;
					ofsCou<<nowTimeStamp<<endl;

					DeletePersonalAlarmClock();
					ifsArg >> starttime >> kind >> acttime >> tp;
					AddPersonalAlarmClock(starttime,kind,acttime,tp);
					ShowPersonalAlarmClock();
					break;	
				case CHECK_ALARM:
					
					ifsArg>>w;
					ifsArg>>s;
					ifsArg>>nowTimeStamp;
					ifsArg>>scrollTop;
					ifsArg>>timeWalkPace;

					ofsCou.close();
					ofsCou.open("../htmls/pagebuffer.txt");
					ofsCou<<5<<endl;
					ofsCou<<w<<endl;
					ofsCou<<s<<endl;
					ofsCou<<nowTimeStamp<<endl;
					ofsCou<<scrollTop<<endl;
					ofsCou<<timeWalkPace<<endl;

					ifsArg >> NTS;
					cout<<NTS<<endl;
					SystemAlarmClock(NTS);
					TempAlarmClock(NTS);
					PersonalAlarmClock(NTS);
					break;
				case SET_TIME:
					ifsArg>>w;
					ifsArg>>s;
					ifsArg>>nowTimeStamp;
					ifsArg>>scrollTop;
					
					ofsCou.close();
					ofsCou.open("../htmls/pagebuffer.txt");
					ofsCou<<5<<endl;
					ofsCou<<w<<endl;
					ofsCou<<s<<endl;
					ofsCou<<nowTimeStamp<<endl;
					ofsCou<<scrollTop<<endl;
					ofsCou<<1000<<endl;
					
					ifsArg >> NTS;
					save();
					Init(NTS);
					this->ShowClassSchedule(w);
					ShowPersonalAlarmClock();
					SystemAlarmClock(NTS);
					TempAlarmClock(NTS);
					PersonalAlarmClock(NTS);
					break;
				default:
					ifsArg.close();
					ofsCou.close();
					log1.~CLog();
					CloseHandle(dirHandle);
					save();
					return ;
				};

			}
			// Sleep(100);
			ifsArg.close();
		}
	}

	CloseHandle(dirHandle);
}



void student::Init(int now_time)
{
	memset(timeline, 0, sizeof(timeline));
	InitCourseInformation(now_time);
	InitGroupActInformation();
	InitActivityInformation();
	InitTempActInformation();
	InitAlarmClockInformation(now_time);
	cout << now_time << endl;
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
	// sysalarm .join();
	// tmpalarm .join();
	// personalalarm.join();
	// this->stop = 1;
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
	filename = "../datas/" + filename + "course.txt";

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
	int place;
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
	filename = "../datas/" + filename + "activity.txt";
	// cout<<filename<<endl;
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
	int EndTime;
	int place;
	int id;
	int kind;
	int tp;
	while (ifs >> name && ifs >> StartTime && ifs >> EndTime && ifs >> place && ifs >> id && ifs >> kind && ifs >> tp)
	{
		// cout << StartTime << endl;
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
				ActivityList[x][i].EndTime = EndTime;
				ActivityList[x][i].place = place;
				ActivityList[x][i].id = id;
				ActivityList[x][i].kind = kind;
				ActivityList[x][i].type = tp;
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
		ofsCou << 1 << endl;
		ofsCou << "您有个人活动因冲突被删除" << endl;
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
	int flag = 0;

	string filename = to_string(this->ClassNum);
	filename = "../datas/" + filename + "groupact.txt";

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
	int StartTime, EndTime;
	//int EndTime;
	int place;
	int Class;
	int kind;
	int tp;
	while (ifs >> name && ifs >> StartTime && ifs >> EndTime && ifs >> place && ifs >> Class && ifs >> kind && ifs >> tp)
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
			if (timeline[StartTime] == 0)
			{
				timeline[StartTime] = kind;
				GroupActList[x][i].name = name;
				GroupActList[x][i].StartTime = StartTime;
				GroupActList[x][i].EndTime = EndTime;
				GroupActList[x][i].place = place;
				GroupActList[x][i].Class = Class;
				GroupActList[x][i].kind = kind;
				GroupActList[x][i].type = type;
				GroupActNum[x]++;
			}
			else
			{
				flag = 1;
			}
		}
	}
	if (flag)
	{
		ofsCou << 1 << endl;
		ofsCou << "您有集体活动因冲突被删除" << endl;
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
	filename = "../datas/" + filename + "tempact.txt";

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
	int EndTime;
	int place;
	int id;
	int kind;
	while (ifs >> name && ifs >> StartTime && ifs >> EndTime && ifs >> place && ifs >> id && ifs >> kind)
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
			if (timeline[StartTime] == 0 || timeline[StartTime] == 4)
			{
				timeline[StartTime] = kind;
				TempActList[x][i].name = name;
				TempActList[x][i].StartTime = StartTime;
				TempActList[x][i].EndTime = EndTime;
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
		ofsCou << 1 << endl;
		ofsCou << "您有临时事务因冲突被删除" << endl;
	}
	ifs.close();
}

void student::InitAlarmClockInformation(int now_time)
{
	AlarmNum = 0;
	AlarmIdx = 0;
	int flag = 0;

	string filename = to_string(this->id);
	filename = "../datas/" + filename + "alarmclock.txt";
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
	int type;
	int ActTime;
	int id;
	while (ifs >> StartTime && ifs >> kind && ifs >> type && ifs >> ActTime && ifs >> id)
	{
		if (StartTime >= now_time && id == this->id)
		{
			AlarmList[AlarmNum].StartTime = StartTime;
			AlarmList[AlarmNum].kind = kind;
			AlarmList[AlarmNum].type = type;
			AlarmList[AlarmNum].ActTime = ActTime;
			AlarmList[AlarmNum].id = id;
			AlarmNum++;
		}
	}
	ifs.close();
}

void student::SaveGroupActInformation()
{
	string filename = to_string(this->ClassNum);
	filename = "../datas/" + filename + "groupact.txt";

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
			<< GroupActList[i][j].kind << " "
			<< GroupActList[i][j].type << endl;
		}
	}
	ofs.close();
}
void student::SaveActivityInformation()
{
	string filename = to_string(this->id);
	filename = "../datas/" + filename + "activity.txt";

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
			<< ActivityList[i][j].kind << " "
			<< ActivityList[i][j].type << endl;
		}
	}
	ofs.close();
}
void student::SaveTempActInformation()
{
	string filename = to_string(this->id);
	filename = "../datas/" + filename + "tempact.txt";

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
	filename = "../datas/" + filename + "alarmclock.txt";

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
	log1.wr(this->name, "查看课程表");

	ofstream ofs;
	ofs.open("../datas/coumes.txt");
	//for (int i = 0; i < 20; i++)
	//{
	//	cout << CourseNum[i] << " " << GroupActNum[i] << " " << ActivityNum[i] << " " << TempActNum[i] << endl;
	//}

	//for (int i = 0; i < CourseNum[w]; i++)
	//{
	//	cout << CourseList[w][i].name << " " << CourseList[w][i].StartTime << " " << CourseList[w][i].EndTime << " " << CourseList[w][i].place << " " << CourseList[w][i].kind << endl;//����γ̣�
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
			if (ActivityR == 0  || (ActivityR > 0 && ActivityList[w][ActivityR].StartTime != ActivityList[w][ActivityR - 1].StartTime))
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
		ofs << num << endl;
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
				ofs << CourseList[w][CourseL].kind << " " << CourseList[w][CourseL].StartTime << " " << CourseList[w][CourseL].EndTime << " " << CourseList[w][CourseL].name << " " << CourseList[w][CourseL].Class << " " << CourseList[w][CourseL].place << endl;//����γ̣�
				CourseL++;
			}
			else if (Gtm < Atm && Gtm < Ttm && Gtm < Ctm)
			{
				ofs << GroupActList[w][GroupActL].kind << " " << GroupActList[w][GroupActL].StartTime << " " << GroupActList[w][GroupActL].EndTime << " " << GroupActList[w][GroupActL].Class << " " << GroupActList[w][GroupActL].name << " " << GroupActList[w][GroupActL].place << " " << 1 << endl;
				GroupActL++;
			}
			else if (Atm < Ctm && Atm < Ttm && Atm < Gtm)
			{
				ofs << ActivityList[w][ActivityL].kind << " " << ActivityList[w][ActivityL].StartTime << " " << ActivityList[w][ActivityL].EndTime << " " << ActivityList[w][ActivityL].name << " " << ActivityList[w][ActivityL].place << " " << ActivityList[w][ActivityL].type << endl;//��Ӧ�
				ActivityL++;
			}
			else if (Ttm < Ctm && Ttm < Atm && Ttm < Gtm)
			{
				int tmpr = TempActL ;
				while (TempActList[w][tmpr].StartTime == TempActList[w][TempActL].StartTime && tmpr < TempActR )
				{
					tmpr++;
				}

				ofs << TempActList[w][TempActL].kind << " " << TempActList[w][TempActL].StartTime << " " << TempActList[w][TempActL].EndTime << " " << tmpr-TempActL << " ";
				while (TempActL < tmpr)
				{
					ofs << TempActList[w][TempActL].name << " " << TempActList[w][TempActL].place << " ";
					TempActL++;
				}
				ofs << endl;
				/*cout << TempActList[w][TempActL].name << " " << TempActList[w][TempActL].StartTime << " " << TempActList[w][TempActL].EndTime << " " << TempActList[w][TempActL].place << " " << TempActList[w][TempActL].kind << " ";
				TempActL++;
				while (TempActList[w][TempActL].StartTime == TempActList[w][TempActL - 1].StartTime)
				{
					cout << 
				}*/
			}
		}
	}
	ofs.close();
}


int student::Search(int kind, string name, int now_time)//半成品
{
	int w = now_time / 168;
	int ret = -1;
	int flag = 0;
	//cout << now_time << " " << w << endl;
	if (kind == 1)
	{
		log1.wr(this->name, "查询课程");
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
					// teststream << CourseList[i][j].name <<endl;
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
					// teststream << CourseList[i][j].name <<endl;
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
		log1.wr(this->name, "查询集体活动");
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
		log1.wr(this->name, "查询个人活动");
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
		log1.wr(this->name, "查询临时事务");
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

	// teststream << ret <<endl;
	// teststream.close();
	return ret + 1;

}


void student::AddGroupAct()
{
	// cout << "请输入集体活动的开始时间" << endl;
	int tm;
	ifsArg >> tm;
	group_act tmp;

	if (timeline[tm] == 0)
	{
		tmp.kind = 2;
		tmp.Class = this->ClassNum;
		tmp.StartTime = tm;
		tmp.EndTime = tmp.StartTime + 1;
		int w = tmp.StartTime / 168;

		// cout << "请输入集体活动的名称与地点" << endl;;
		ifsArg >> tmp.name >> tmp.place;
		tmp.name = UTF8_To_string(tmp.name);

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
		log1.wr(this->name, "添加一个集体活动");
	}
	else
	{
		ofsCou << 1 << endl;
		ofsCou << "时间冲突" << endl;

		int a = tm % 24;
		int num = 0;


		for (int i = tm - a + 6; i < tm - a + 21; i++)
		{
			if (timeline[i] == 0 && num < 3)
			{
				ofsCou << i << endl;
				num++;
			}
		}

		if (num == 0)
		{
			ofsCou << 1 << endl;
			ofsCou << "无可用时间" << endl;
		}
	}
	//����ˢ��һ�¿α�
}

void student::AddActivity()
{
	//cout << "��������˻�Ŀ�ʼʱ��" << endl;
	//int tm;
	//cin >> tm;
	// cout << "请输入周期类型：1 单次，2 每天，3 每周" << endl;
	int tp;
	ifsArg >> tp;

	activity tmp;

	if (tp == 1)
	{
		// cout << "请输入个人活动的开始时间，名称，地点" << endl;
		int tm;
		string name;
		int place;
		ifsArg >> tm >> name >> place;
		AddSingleActivity(tm, name, place,tp);
		log1.wr(this->name, "添加一个单次的个人活动");
	}
	else if (tp == 2)
	{
		// cout << "请输入个人活动的开始时间，结束时间，名称，地点" << endl;
		int tm,endtm;
		string name;
		int place;
		ifsArg >> tm >> endtm >> name >> place;
		for (tm; tm <= endtm; tm+=24)
		{
			int x= AddSingleActivity(tm, name, place, tp);
			if (x == 0)
			{
				int w = tm / 168 + 1,d = ( tm % 168 ) / 24 + 1;
				ofsCou << 1 << endl;
				ofsCou << "第" << w << "周星期"  << d << "活动有冲突，插入失败" << endl;
			}
		}
		log1.wr(this->name, "添加一个每天的个人活动");
	}
	else if (tp == 3)
	{
		// cout << "请输入个人活动的开始时间，结束时间，名称，地点" << endl;
		int tm, endtm;
		string name;
		int place;
		ifsArg >> tm >> endtm >> name >> place;
		for (tm; tm <= endtm; tm += 168)
		{
			int x = AddSingleActivity(tm, name, place, tp);
			if (x == 0)
			{
				int w = tm / 168 + 1 ;
				ofsCou << 1 << endl;
				ofsCou << "第" << w << "周活动有冲突，插入失败" << endl;
			}
		}
		log1.wr(this->name, "添加一个每周的个人活动");
	}



	
	//可以刷新一下课表
}


int student::AddSingleActivity(int tm,string name,int place,int type)
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
		tmp.name = UTF8_To_string(tmp.name);
		tmp.place = place;
		int w = tmp.StartTime / 168;
		//cout << "�����뼯����������ص�" << endl;

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
			ofsCou << 1 << endl;
			ofsCou << "时间冲突" << endl;

			int a = tm % 24;
			int num = 0;

			for (int i = tm - a + 6; i < tm - a + 21; i++)
			{
				if (timeline[i] == 0 && num < 3)
				{
					ofsCou << i << endl;
					num++;
				}
			}
			if (num == 0)
			{
				ofsCou << "无可用时间" << endl;
			}
		}
		return 0;
	}
}


void student::AddTempAct()
{
	// cout << "请输入临时事务的开始时间" << endl;
	int tm;
	ifsArg >> tm;
	temp_act tmp;

	if (timeline[tm] == 0 || timeline[tm] == 4)
	{
		tmp.kind = 4;
		tmp.id = this->id;
		tmp.StartTime = tm;
		tmp.EndTime = tm + 1;
		int w = tmp.StartTime / 168;
		// cout << "请输入临时事务的名称与地点" << endl;;
		ifsArg >> tmp.name >> tmp.place;
		tmp.name = UTF8_To_string(tmp.name);

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
		log1.wr(this->name, "添加一个临时事务");
	}
	else
	{
		ofsCou << 1 << endl;
		ofsCou << "时间冲突，输入失败" << endl;
	}
	//����ˢ��һ�¿α�
}

void student::DeleteGroupAct()
{
	// cout << "请输入起始时间" << endl;
	int tm;
	ifsArg >> tm;

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
	log1.wr(this->name, "删除一个集体活动");
}

void student::DeleteActivity()
{
	// cout << "请输入起始时间" << endl;
	int tm;
	ifsArg >> tm;

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
	log1.wr(this->name, "删除一个个人活动");
}

void student::DeleteTempAct()
{
	// cout << "请输入起始时间" << endl;
	int tm;
	ifsArg >> tm;
	// cout << "请输入事务名称" << endl;
	string nm;
	ifsArg >> nm;
	nm = UTF8_To_string(nm);


	int w = tm / 168;
	int idx ;
	
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
		if (TempActList[w][idx].StartTime == tm )
		{
			flag = 1;
			break;
		}
	}
	if(!flag)
		timeline[tm] = 0;
	log1.wr(this->name, "删除一个临时事务");

}

void student::SystemAlarmClock(int now_time)
{
	//int flag = 0;
	ofstream ofs;
	ofs.open("../datas/systemAlarm.txt");
	int w = now_time / 168;
	if (now_time % 24 == 22)
	{
		ofs << 1 << endl;
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
		ofs << num << endl;
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
				ofs << CourseList[w][CourseL].kind << " " << CourseList[w][CourseL].StartTime << " " << CourseList[w][CourseL].EndTime << " " << CourseList[w][CourseL].name << " " << CourseList[w][CourseL].place << " " << CourseList[w][CourseL].Class << endl;//输出课程；
				CourseL++;
			}
			else if (Gtm < Atm && Gtm < Ctm)
			{
				ofs << GroupActList[w][GroupActL].kind << " " << GroupActList[w][GroupActL].StartTime << " " << GroupActList[w][GroupActL].EndTime << " " << GroupActList[w][GroupActL].name << " " << GroupActList[w][GroupActL].place << " " << GroupActList[w][GroupActL].Class << endl;
				GroupActL++;
			}
			else if (Atm < Ctm && Atm < Gtm)
			{
				ofs << ActivityList[w][ActivityL].kind << " " << ActivityList[w][ActivityL].StartTime << " " << ActivityList[w][ActivityL].EndTime << " " << ActivityList[w][ActivityL].name << " " << ActivityList[w][ActivityL].place << endl;//对应活动
				ActivityL++;
			}
		}

	}
	else
		ofs << 0 <<endl;
	ofs.close();
}


void student::TempAlarmClock(int now_time)
{

	//int flag = 0;
	ofstream ofs;
	ofs.open("../datas/tempAlarm.txt");
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
		ofs << 1 << endl;
		ofs << CourseList[tmpx][tmpy].kind << " " << CourseList[tmpx][tmpy].StartTime << " " << CourseList[tmpx][tmpy].EndTime << " " << CourseList[tmpx][tmpy].name << " " << CourseList[tmpx][tmpy].Class << " " << CourseList[tmpx][tmpy].place << endl;//输出信息
	}
	else
		ofs << 0 << endl;
	ofs.close();
}


void student::PersonalAlarmClock(int now_time)
{
	ofstream ofs;
	ofs.open("../datas/personalAlarm.txt");
	if (AlarmIdx < AlarmNum)
	{
		if (now_time == AlarmList[AlarmIdx].StartTime)
		{
			ofs.close();
			ShowInfo(AlarmIdx,AlarmList[AlarmIdx].kind, AlarmList[AlarmIdx].ActTime, 0);
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
		else
		{
			ofs << 0 << endl;
			ofs.close();
		}

	}
	else
	{
		ofs << 0 << endl;
		ofs.close();
	}
}

void student::AddPersonalAlarmClock(int starttime,int kind,int acttime,int tp)
{
	alarm x;
	//int tp;
	///*cout << "����������ʱ�䣬�������ͣ����ʼʱ��" << endl;
	//cin >> x.StartTime >> x.kind >> x.ActTime;
	//cout << "���������ڣ�1 ���Σ�2 ÿ�죬3 ÿ��" << endl;
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
		log1.wr(this->name, "添加一个单次闹钟");
		break;
	case 2:
		log1.wr(this->name, "添加一个每天闹钟");
		break;
	case 3:
		log1.wr(this->name, "添加一个每周闹钟");
		break;
	}
}

void student::DeletePersonalAlarmClock()
{
	int tm, idx;
	ifsArg >> tm;
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
	log1.wr(this->name, "删除一个单次闹钟");
}


void student::ShowPersonalAlarmClock()
{
	ofsAla.open("../datas/alarms.txt");
	// cout << AlarmNum - AlarmIdx << endl;
	for (int i = AlarmIdx; i < AlarmNum; i++)
	{
		ShowInfo(i,AlarmList[i].kind, AlarmList[i].ActTime, 1);
	}
	log1.wr(this->name, "展示闹钟信息");
	ofsAla.close();
}

void student::ShowInfo(int loc, int kind, int ActTime, int type)
{
	int w = ActTime / 168;
	int idx = -1;
	ofstream ofs;
	ofs.open("../datas/personalAlarm.txt");
	if(type == 0)
		ofs << 1 << endl;

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
			ofs.close();
			return;
		}
		if(type == 0)
			ofs <<  CourseList[w][idx].kind << " " << CourseList[w][idx].StartTime << " " << CourseList[w][idx].EndTime << " " << CourseList[w][idx].name << " " << CourseList[w][idx].place << " " << CourseList[w][idx].Class << endl;
		else
			ofsAla << AlarmList[loc].StartTime << " " << CourseList[w][idx].kind << " " << CourseList[w][idx].StartTime << " " << CourseList[w][idx].EndTime << " " << CourseList[w][idx].name << " " << CourseList[w][idx].place << " " << CourseList[w][idx].Class << endl;
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
			ofs.close();
			return;
		}
		if(type == 0)
			ofs << GroupActList[w][idx].kind << " " << GroupActList[w][idx].StartTime << " " << GroupActList[w][idx].EndTime << " " << GroupActList[w][idx].name << " " << GroupActList[w][idx].place << " " << GroupActList[w][idx].Class << " " << 1 << endl;
		else
			ofsAla << AlarmList[loc].StartTime << " " << GroupActList[w][idx].kind << " " << GroupActList[w][idx].StartTime << " " << GroupActList[w][idx].EndTime << " " << GroupActList[w][idx].name << " " << GroupActList[w][idx].place << " " << GroupActList[w][idx].Class << " " << 1 << endl;
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
			ofs.close();
			return;
		}
		if(type == 0)
			ofs << ActivityList[w][idx].kind << " " << ActivityList[w][idx].StartTime << " " << ActivityList[w][idx].EndTime << " " << ActivityList[w][idx].name << " " << ActivityList[w][idx].place << " " << ActivityList[w][idx].type << endl;
		else
			ofsAla << AlarmList[loc].StartTime << " " << ActivityList[w][idx].kind << " " << ActivityList[w][idx].StartTime << " " << ActivityList[w][idx].EndTime << " " << ActivityList[w][idx].name << " " << ActivityList[w][idx].place << " " << ActivityList[w][idx].type << endl;
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
			ofs.close();
			return;
		}
		int tmpr = idx;
		while (TempActList[w][tmpr].StartTime == TempActList[w][idx].StartTime && tmpr < TempActNum[w])
		{
			tmpr++;
		}
		if(type == 0)
			ofs << TempActList[w][idx].kind << " " << TempActList[w][idx].StartTime << " " << TempActList[w][idx].EndTime << " " << tmpr - idx << " ";
		else
			ofsAla << AlarmList[loc].StartTime << " " << TempActList[w][idx].kind << " " << TempActList[w][idx].StartTime << " " << TempActList[w][idx].EndTime << " " << tmpr - idx << " ";
		while (idx < tmpr)
		{
			if(type == 0)
				ofs << TempActList[w][idx].name << " " << TempActList[w][idx].place << " ";
			else
				ofsAla << TempActList[w][idx].name << " " << TempActList[w][idx].place << " ";
			idx++;
		}
		if(type == 0)
			ofs << endl;
		else 
			ofsAla << endl;
	}
	ofs.close();
}





bool cmp(course a, course b)
{
	return a.StartTime < b.StartTime;
}

void manager::ManageSystem()
{
	init();
	fUpdate();
	log1.init("../datas/log.txt");
	ofsCou.open("../htmls/pagebuffer.txt");
	ofsCou << -1 << endl;
	log1.wr(this->name, "登录了教师系统");

	DWORD cbBytes;
	char notify[1024];
	char buffer[256];
    _getcwd(buffer,256);
	TCHAR dir[256];
    #ifdef UNICODE
        MultiByteToWideChar(CP_ACP,0,buffer,-1,dir,256);
    #else
        strcpy(dir,buffer);
    #endif
    cout<<buffer<<endl;
    cout<<dir<<endl;
	
	HANDLE dirHandle = CreateFile(dir,
								  GENERIC_READ | GENERIC_WRITE | FILE_LIST_DIRECTORY,
								  FILE_SHARE_READ | FILE_SHARE_WRITE,
								  NULL,
								  OPEN_EXISTING,
								  FILE_FLAG_BACKUP_SEMANTICS,
								  NULL);

	if (dirHandle == INVALID_HANDLE_VALUE)
	{
		cout << "error" + GetLastError() << endl;
	}

	memset(notify, 0, strlen(notify));
	FILE_NOTIFY_INFORMATION *pnotify = (FILE_NOTIFY_INFORMATION *)notify;

	cout << "Start Monitor..." << endl;

	
	int flag=0;
	long long lastTS = 0, nowTS = 0;
	// int level=0;
	while (true)
	{
		cout<<"Monitoring"<<endl;
		if (ReadDirectoryChangesW(dirHandle, &notify, 1024, true,
								  FILE_NOTIFY_CHANGE_FILE_NAME | FILE_NOTIFY_CHANGE_LAST_ACCESS,
								  &cbBytes, NULL, NULL))
		{
			std::chrono::milliseconds ms = std::chrono::duration_cast< std::chrono::milliseconds >(
        		std::chrono::system_clock::now().time_since_epoch()
    		);
			nowTS = ms.count();
			if(nowTS - lastTS <= 500)
			{
				lastTS = nowTS;
				cout<<nowTS<<endl;
				continue;
			}
			lastTS = nowTS;

			switch (pnotify->Action)
			{	
			case FILE_ACTION_MODIFIED:
                cout<<"Modified"<<endl;
				cout<<"test"<<endl;
				long long nowTimeStamp;
				ifsArg.open("js2exe.txt");
				ifsArg >> flag;
				cout << flag;
				switch(flag)
				{
					case ADD_STUDENT :
						ifsArg >> nowTimeStamp;

						ofsCou.close();
						ofsCou.open("../htmls/pagebuffer.txt");
						ofsCou << 0 << endl;
						ofsCou << nowTimeStamp << endl;
						add_student();
						break;
					case DEL_STUDENT :
						ifsArg >> nowTimeStamp;

						ofsCou.close();
						ofsCou.open("../htmls/pagebuffer.txt");
						ofsCou << 0 << endl;
						ofsCou << nowTimeStamp << endl;
						delete_student();
						break;
					case MODIFY_STUDENT :
						ifsArg >> nowTimeStamp;

						ofsCou.close();
						ofsCou.open("../htmls/pagebuffer.txt");
						ofsCou << 0 << endl;
						ofsCou << nowTimeStamp << endl;
						change_student();
						break;
					case ADD_COURSE :
						ifsArg >> nowTimeStamp;

						ofsCou.close();
						ofsCou.open("../htmls/pagebuffer.txt");
						ofsCou << 1 << endl;
						ofsCou << nowTimeStamp << endl;
						add_class();
						break;
					case DEL_COURSE :
						ifsArg >> nowTimeStamp;

						ofsCou.close();
						ofsCou.open("../htmls/pagebuffer.txt");
						ofsCou << 1 << endl;
						ofsCou << nowTimeStamp << endl;
						delete_class();
						break;
					case MODIFY_COURSE :
						ifsArg >> nowTimeStamp;

						ofsCou.close();
						ofsCou.open("../htmls/pagebuffer.txt");
						ofsCou << 1 << endl;
						ofsCou << nowTimeStamp << endl;
						change_class();
						break;
					default :
						ifsArg.close();
						ofsCou.close();
						CloseHandle(dirHandle);
						translate();
						connection();
						
						log1.~CLog();
						return ;
				}
			}
			ifsArg.close();
		}
	}
	CloseHandle(dirHandle);
}
void manager::init()
{
	ifstream ifs;
	course c;
	student s;
	int j = 0;
	ifs.open("../datas/course.txt", ios::in);
	ifs >> count_course;
	for (int i = 0; i < count_course; i++)
	{
		ifs >> c.name;
		ifs >> c.StartTime;
		ifs >> c.EndTime;
		ifs >> c.place;
		ifs >> c.Class;
		ifs >> c.period;

		ifs >> c.c_week;//单次的设成0
		ifs >> c.week;//单次的设成0
		course_Array.push_back(c);
	}
	ifs.close();
	ifs.open("../datas/studentmessage.txt", ios::in);
	ifs >> count_student;
	for (int i = 0; i < count_student; i++)
	{
		ifs >> s.id;
		ifs >> s.ClassNum;
		ifs >> s.name;
		ifs >> s.password;

		student_Array.push_back(s);
	}
}
void manager::add_class()
{
	int num, j = 0;
	course c;
	// cout << "请选择要添加的课程数：" << endl;
	ifsArg >> num;
	for (int i = 0; i < num; i++)
	{
			// cout << "请输入第" << i + 1 << "个课程的名称" << endl;
		ifsArg >> c.name;
		c.name = UTF8_To_string(c.name);
		for (j = 0; j < count_course; j++)
		{
			if (course_Array[j].name == c.name)
			{
				ofsCou << 1 << endl;
				ofsCou << "该课程已存在！" << endl;
				return ;
			}
		}
		// if (j == count_course)
		// 	return;
		// cout << "请输入第" << i + 1 << "个课程的开始时间" << endl;
		ifsArg >> c.StartTime;
		// cout << "请输入第" << i + 1 << "个课程的结束时间" << endl;
		ifsArg >> c.EndTime;
		// cout << "请输入第" << i + 1 << "个课程的上课地点" << endl;
		ifsArg >> c.place;
		// cout << "请输入第" << i + 1 << "个课程的上课班级" << endl;
		ifsArg >> c.Class;
		// cout << "第" << i + 1 << "个课程是否为单次课" << endl;
		// cout << "1.是	2.否" << endl;
		ifsArg >> c.period;
		if (c.period == 2)
		{
			// cout << "请输入第" << i + 1 << "个课程的上课周数" << endl;
			ifsArg >> c.c_week;
			// cout << "请依次输入第" << i + 1 << "个课程的上课周" << endl;
			ifsArg >> c.week;
		}
		else
		{
			c.c_week = 1;
			// cout << "请依次输入第" << i + 1 << "个课程的上课周" << endl;
			ifsArg >> c.week;
		}
		course_Array.push_back(c);
		count_course++;
	}
	log1.wr(this->name, "添加了一门课程");
	sort(course_Array.begin(), course_Array.end(), cmp);
	fUpdate();
	// cout << "添加成功！" << endl;
}
void manager::delete_class()
{
	string name;
	int num, i = 0;
		// cout << "请输入要删除的课程名称：" << endl;
	ifsArg >> name;
	name=UTF8_To_string(name);
	for (i = 0; i < count_course; i++)
	{
		if (course_Array[i].name == name)
		{
			num = i;
			break;
		}
	}
	if (i == count_course)
	{
		ofsCou << 1 << endl;
		ofsCou << "该课程不存在！" << endl;
		return ;
	}
		
	auto it = course_Array.begin() + num;
	course_Array.erase(it);
	count_course--;
	log1.wr(this->name, "删除了一门课程");
	fUpdate();
	// cout << "删除成功！" << endl;
}
void manager::change_class()
{
	string name;
	int num, j = 0, i = 0;
	course c;
		// cout << "请输入要修改的课程名称：" << endl;
	ifsArg >> name;
	name = UTF8_To_string(name);
	for (i = 0; i < count_course; i++)
	{
		if (course_Array[i].name == name)
		{
			num = i;
			break;
		}
	}
	if (i == count_course)
	{
		ofsCou << 1 <<endl;
		ofsCou << "该课程不存在！" << endl;
		return ;
	}
			
		// cout << "请输入修改后课程的名称：" << endl;
	ifsArg >> c.name;
	c.name = UTF8_To_string(c.name);
	for (j = 0; j < count_course; j++)
	{
		if (course_Array[j].name == c.name && num != j)
		{
			ofsCou << 1 << endl;
			ofsCou << "该课程已存在！" << endl;
			return;
		}
	}
	// if (j == count_course)
	// 	return ;
	// cout << "请输入修改后课程的开始时间：" << endl;
	ifsArg >> c.StartTime;
	// cout << "请输入修改后课程的结束时间：" << endl;
	ifsArg >> c.EndTime;
	// cout << "请输入修改后课程的上课地点：" << endl;
	ifsArg >> c.place;
	// cout << "请输入修改后课程的上课班级：" << endl;
	ifsArg >> c.Class;
	// cout << "修改后课程是否为单次课：" << endl;
	// cout << "1.是	2.否" << endl;
	ifsArg >> c.period;
	if (c.period == 2)
	{
		// cout << "请输入修改后课程的上课周数：" << endl;
		ifsArg >> c.c_week;
		// cout << "请依次输入修改后课程的上课周：" << endl;
		ifsArg >> c.week;
	}
	else
	{
		c.c_week = 1;
		// cout << "请依次输入修改后课程的上课周：" << endl;
		ifsArg >> c.week;
	}
	course_Array[num] = c;
	log1.wr(this->name, "修改了一门课程");
	fUpdate();
	// cout << "修改成功！" << endl;
}
void manager::add_student()
{
	int num, j = 0;
	student s;
	string s2;
	string s1 = "2021";
	// cout << "请选择要添加的学生数：" << endl;
	string filename1, filename2, filename3;
	ofstream ofs;
	ifsArg >> num;
	for (int i = 0; i < num; i++)
	{
			// cout << "请输入第" << i + 1 << "个学生的id" << endl;
		ifsArg >> s.id;
		for (j = 0; j < count_student; j++)
		{
			if (student_Array[j].id == s.id)
			{
				ofsCou << 1 << endl;
				ofsCou << "该学生已存在！" << endl;
				return;
			}
		}
		// if (j == count_student)
		// 	break;
		// cout << "请输入第" << i + 1 << "个学生的姓名" << endl;
		ifsArg >> s.name;
		s.name = UTF8_To_string(s.name);
		// cout << "请输入第" << i + 1 << "个学生的班级" << endl;
		ifsArg >> s.ClassNum;
		s2 = to_string(s.id);
		s1 = "2021";
		s1 = s1 + s2;
		s.password = s1;//设置默认密码
		student_Array.push_back(s);
		filename1 = "../datas/" + s2 + "activity" + ".txt";
		filename2 = "../datas/" + s2 + "tempact" + ".txt";
		filename3 = "../datas/" + s2 + "alarmclock" + ".txt";
		cout << filename1 << endl;
		ofs.open(filename1, ios::app|ios::out);
		ofs.close();
		ofs.open(filename2, ios::app|ios::out);
		ofs.close();
		ofs.open(filename3, ios::app|ios::out);
		ofs.close();
		count_student++;
	}
	log1.wr(this->name, "添加了一名学生");
	fUpdate();
	// cout << "添加成功" << endl;
}
void manager::delete_student()
{
	int id;
	int num, i = 0;
		// cout << "请输入要删除的学生id" << endl;
	ifsArg >> id;

	for (i = 0; i < count_student; i++)
	{
		if (student_Array[i].id == id)
		{
			num = i;
			break;
		}
	}
	if (i == count_student)
	{
		ofsCou << 1 << endl;
		ofsCou << "该学生不存在！" << endl;
		return ;
	}
	auto it = student_Array.begin() + num;
	student_Array.erase(it);
	count_student--;
	log1.wr(this->name, "删除了一名学生");
	fUpdate();
	// cout << "删除成功" << endl;
}
void manager::change_student()
{
	int id;
	int num, j = 0, i = 0;
	student s;
	string s2;
	string s1;
	string filename1, filename2, filename3;
	string oldfilename1, oldfilename2, oldfilename3;
		// cout << "请输入要修改的学生id：" << endl;
	ifsArg >> id;
	for (i = 0; i < count_student; i++)
	{
		if (student_Array[i].id == id)
		{
			num = i;
			break;
		}
	}
	if (i == count_student)
	{
		ofsCou << 1 << endl;
		ofsCou << "该学生不存在！" << endl;
		return ;
	}
		// cout << "请输入修改后的id" << endl;
	ifsArg >> s.id;
	for (j = 0; j < count_student; j++)
	{
		if (student_Array[j].id == s.id && num != j)
		{
			ofsCou << 1 << endl;
			ofsCou << "该学生已存在" << endl;
			return;
		}
	}
	// cout << "请输入修改后学生的姓名" << endl;
	ifsArg >> s.name;
	s.name = UTF8_To_string(s.name);
	// cout << "请输入修改后学生的班级" << endl;
	ifsArg >> s.ClassNum;

	s1 = to_string(id);
	s2 = to_string(s.id);
	oldfilename1 = "../datas/" + s1 + "activity" + ".txt";
	oldfilename2 = "../datas/" + s1 + "tempact" + ".txt";
	oldfilename3 = "../datas/" + s1 + "alarmclock" + ".txt";
	filename1 = "../datas/" + s2 + "activity" + ".txt";
	filename2 = "../datas/" + s2 + "tempact" + ".txt";
	filename3 = "../datas/" + s2 + "alarmclock" + ".txt";
	rename(oldfilename1.c_str(), filename1.c_str());
	rename(oldfilename2.c_str(), filename2.c_str());
	rename(oldfilename3.c_str(), filename3.c_str());
	string s3 = "2021";
	s.password = s3 + to_string(s.id);
	student_Array[num] = s;
	log1.wr(this->name, "修改了一名学生");
	fUpdate();
	// cout << "修改成功！" << endl;
}
void manager::fUpdate()
{
	ofstream ofs;
	ofs.open("../datas/course.txt", ios::out);//outΪ��дģʽ�����Ὣԭ���ļ��е�����ȫ�����
	ofs << count_course << endl;
	for (int i = 0; i < count_course; i++)
	{
		ofs << course_Array[i].name << " "
			<< course_Array[i].StartTime << " "
			<< course_Array[i].EndTime << " "
			<< course_Array[i].place << " "
			<< course_Array[i].Class << " "
			<< course_Array[i].period << " "
			<< course_Array[i].c_week << " "
			<< course_Array[i].week << endl;
	}//д�ļ�����
	ofs.close();
	ofs.open("../datas/studentmessage.txt", ios::out);
	ofs << count_student << endl;
	for (int i = 0; i < count_student; i++)
	{
		ofs << student_Array[i].id << " "
			<< student_Array[i].ClassNum << " "
			<< student_Array[i].name << " "
			<< student_Array[i].password << endl;
	}//д�ļ�����
	ofs.close();
}
void manager::connection()
{
	ofstream ofs;
	ofs.open("../datas/8course.txt", ios::out);
	vector<course> temp;
	temp = course_Array;
	int m_time = 0;
	for (int j = 1; j <= 19; j++)
	{
		for (int k = 0; k < count_course; k++)
		{
			if (temp[k].check[j] == 1)
			{
				ofs << temp[k].name << " ";
				ofs << temp[k].StartTime << " ";
				ofs << temp[k].EndTime << " ";
				ofs << temp[k].place << " ";
				ofs << temp[k].Class << " ";
				ofs << temp[k].kind << endl;
				m_time = temp[k].EndTime;
			}
		}
		for (int k = 0; k < count_course; k++)
		{
			temp[k].StartTime += 168;
			temp[k].EndTime += 168;
		}
	}
	ofs.close();
}
void manager::translate()
{
	string s;
	int start, end, single;

	for (int i = 0; i < count_course; i++)
	{
		s = course_Array[i].week;
		int j = 0;
		while (j < s.length())
		{
			if (s[j] == '-')
			{	
				if ((j>1)&&s[j - 2] >= '0' && s[j - 2] <= '9')//�ж��ǲ���ʮλ��
				{
					start = s[j - 1] - '0' + (s[j - 2] - '0') * 10;
				}
				else
				{
					start = s[j - 1] - '0';
				}
				if ((j + 2) < s.length()&&s[j + 2] >= '0' && s[j + 2] <= '9')//�ж��ǲ���ʮλ��
				{
					end = s[j + 2] - '0' + (s[j + 1] - '0') * 10;
					j += 3;
				
				}
				else
				{
					end = s[j + 1] - '0';
					j += 2;
					
				}
				for (int k = start; k <= end; k++)
				{
					course_Array[i].check[k] = 1;
				}
				continue;
			}


			else if (s[j] >= '0' && s[j] <= '9')//������
			{
				if ((j + 1) < s.length()&&s[j + 1] >= '0' && s[j + 1] <= '9')//����������ǲ���ʮλ���������ʮλ
				{
					single = 10 * (s[j] - '\0') + (s[j + 1] - '\0');
					if ((j == 0 && s[j + 2] == ',')||(j == 0 && s[j + 2] == '\0'))//��һ��
					{
						course_Array[i].check[single] = 1;
						j += 3;
					}
					else if ((j + 2) < s.length() && j > 0 && s[j - 1] == ',' && s[j + 2] == ',')//�������Ҷ��ǡ�����
					{
						course_Array[i].check[single] = 1;
						j += 3;

					}
					else if ((j + 2) < s.length() && j > 0 && s[j + 2] == '\0' && s[j - 1] == ',')//���һ��
					{
						course_Array[i].check[single] = 1;
						j += 3;

					}
					else
						j++;
				}
				else//����ʮλ��
				{
					single = s[j] - '0';
					if ((j + 1) < s.length() && j > 0 && s[j - 1] == ',' && s[j + 1] == ',')
					{
						course_Array[i].check[single] = 1;
						j += 2;

					}
					else if ((j == 0 && s[j + 1] == ',') || (j == 0 && s[j + 1] == '\0'))//��һ��
					{
						course_Array[i].check[single] = 1;
						j += 2;

					}
					else if ((j + 1) < s.length() && j > 0 && s[j + 1] == '\0' && s[j - 1] == ',')
					{
						course_Array[i].check[single] = 1;
						j += 2;

					}
					else
						j++;
				}
				
			}
			else
				j++;
		}
	}
}













/*user::user(int id, int cId, int type, string name, string password)
{
	m_id = id;//ѧ��
	m_ClassNum = cId;//���
	m_type = type;
	m_name = name;//ѧ������
	m_password = password;//����

}
user::~user() {};

student::student(int id,  int ClassNum, string name,string password)
{
	this->id = id;//ѧ��
	this->name = name;//ѧ������
	this->ClassNum = ClassNum;//���
	this->password = password;//����
	this->type = 1;
}

manager::manager(int id, string name, string password)
{
	this->id = id;//ѧ��
	this->name = name;//ѧ������
	this->password = password;//����
	this->type = 2;
}*/
/*

(n)
	int a=1<<n;


	00000~11111
	for(int i=0;i<a;i++)
	{
		for(int j=0;j<n;j++)
		{
			if(i>>j&1)
		}

	}

*/
