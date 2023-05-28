#include<iostream>
#include<fstream>
#include<windows.h>
#include<wchar.h>
#include<direct.h>
#include<string>
#include"user.h"
#include"Time.h"
#include"stringop.h"
#include"findWay.h"
using namespace std;

#define ASK_FOR_COURSE 1
#define ADD_ACTIVITY 2
#define DEL_ACTIVITY 3
#define MODIFY_ACTIVITY 4
#define SEARCH_ACTIVITY 5
#define FIND_SINGLE_WAY 6
#define FIND_MULTIPLE_WAY 7
ofstream ofsCou;
ifstream ifsArg;

student StudentList[MAX_PEOPLE];
int StudentCnt;
manager ManagerList[MAX_PEOPLE];
int ManagerCnt;

graph g;

student::student() {};
student::~student() {};
manager::manager() {};
manager::~manager() {};

void student::ManageSystem()
{
	Init();
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
			nowTS = time(0);
			if(nowTS - lastTS <= 1)
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
				int w;
				int searchWeek;
				string searchName;
				long long nowTimeStamp;
				int c_point,end,start;
				int point[50];
				int type;
				// DelLineData(2);

				switch (flag)
				{

				case ASK_FOR_COURSE:
					ifsArg>>w;
					ifsArg>>s;
					ifsArg>>nowTimeStamp;

					ofsCou.close();
					ofsCou.open("../htmls/pagebuffer.txt");
					ofsCou<<0<<endl;
					ofsCou<<w<<endl;
					ofsCou<<s<<endl;
					ofsCou<<nowTimeStamp<<endl;
					// ofsCou<<0<<endl;
					ofsCou.close();
					this->ShowClassSchedule(w);
					break;

				case ADD_ACTIVITY:
					ifsArg>>w;
					ifsArg>>s;
					ifsArg>>nowTimeStamp;

					ofsCou.close();
					ofsCou.open("../htmls/pagebuffer.txt");
					ofsCou<<0<<endl;
					ofsCou<<w<<endl;
					ofsCou<<s<<endl;
					ofsCou<<nowTimeStamp<<endl;

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
					ifsArg>>w;
					ifsArg>>s;
					ifsArg>>nowTimeStamp;

					ofsCou.close();
					ofsCou.open("../htmls/pagebuffer.txt");
					ofsCou<<0<<endl;
					ofsCou<<w<<endl;
					ofsCou<<s<<endl;
					ofsCou<<nowTimeStamp<<endl;

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
					ifsArg>>w;
					ifsArg>>s;
					ifsArg>>nowTimeStamp;

					ofsCou.close();
					ofsCou.open("../htmls/pagebuffer.txt");
					ofsCou<<0<<endl;
					ofsCou<<w<<endl;
					ofsCou<<s<<endl;
					ofsCou<<nowTimeStamp<<endl;

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
					break;

				case SEARCH_ACTIVITY:
					ifsArg>>w;
					ifsArg>>s;
					ifsArg>>nowTimeStamp;

					ofsCou.close();
					ofsCou.open("../htmls/pagebuffer.txt");
					ofsCou<<0<<endl;

					ifsArg >> type;
					ifsArg >> searchName;
					searchName = UTF8_To_string(searchName);
					searchWeek = Search(type,searchName);

					if(searchWeek > 0)
					{
						ofsCou<<searchWeek<<endl;
						ofsCou<<"null"<<endl;
						ofsCou<<nowTimeStamp<<endl;
						this->ShowClassSchedule(searchWeek);
					}
					else
					{
						ofsCou<<w<<endl;
						ofsCou<<s<<endl;
						ofsCou<<nowTimeStamp<<endl;
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
				default:
					break;
				};

			}
			// Sleep(100);
			ifsArg.close();
		}
	}

	CloseHandle(dirHandle);

	// while (true)
	// {
	// 	int t;
	// 	cout << "��Ҫ���еĲ������ͣ�1 �γ̱�չʾ��2 ���ң�3,���ӻ��4 ɾ�����5 �������ӣ�6 ɾ������ ��7 չʾ���� ��8 �˳�" << endl;
	// 	cin >> t;

	// 	if (t == 1)
	// 	{
	// 		cout << "��������Ҫչʾ�ڼ��ܵĿα���" << endl;
	// 		int w;
	// 		cin >> w;
	// 		this->ShowClassSchedule(w);

	// 	}
	// 	else if (t == 2)
	// 	{
	// 		cout << "��������Ҫ���ҵ����ͣ�1 �γ̣�2 ������3 ���˻ ��4 ��ʱ����" << endl;
	// 		int tp;
	// 		cin >> tp;
	// 		if (tp != 1 && tp != 2 && tp != 3 && tp != 4)
	// 		{
	// 			cout << "�������" << endl;
	// 		}
	// 		else
	// 		{
	// 			string s;
	// 			cout << "����������" << endl;
	// 			cin >> s;
	// 			int week = Search(tp, s);
	// 			if (week > 0)
	// 			{
	// 				ShowClassSchedule(week);
	// 			}
	// 			else
	// 			{
	// 				cout << "�����޸�����" << endl;
	// 			}
	// 		}
	// 	}
	// 	else if (t == 3)
	// 	{
	// 		cout << "��������Ҫ���ӵ���������;2 ���� ��3 ���˻ ��4 ��ʱ����" << endl;
	// 		int tp;
	// 		cin >> tp;
	// 		if (tp == 1)
	// 		{
	// 			cout << "û��Ȩ�����ӿγ�" << endl;
	// 		}
	// 		else if (tp == 2)
	// 		{
	// 			AddGroupAct();
	// 		}
	// 		else if (tp == 3)
	// 		{
	// 			AddActivity();
	// 		}
	// 		else if (tp == 4)
	// 		{
	// 			AddTempAct();
	// 		}
	// 		else
	// 		{
	// 			cout << "�������" << endl;
	// 		}

	// 	}
	// 	else if (t == 4)
	// 	{
	// 		cout << "��������Ҫɾ������������;2 ���� ��3 ���˻ ��4 ��ʱ����" << endl;
	// 		int tp;
	// 		cin >> tp;
	// 		if (tp == 1)
	// 		{
	// 			cout << "û��Ȩ��ɾ���γ�" << endl;
	// 		}
	// 		else if (tp == 2)
	// 		{
	// 			DeleteGroupAct();
	// 		}
	// 		else if (tp == 3)
	// 		{
	// 			DeleteActivity();
	// 		}
	// 		else if (tp == 4)
	// 		{
	// 			DeleteTempAct();
	// 		}
	// 		else
	// 		{
	// 			cout << "�������" << endl;
	// 		}
	// 	}
	// 	else if (t == 5)
	// 	{
	// 		int starttime, kind, endtime, acttime, type;
	// 		cout << "����������ʱ�䣬�������ͣ����ʼʱ��" << endl;
	// 		cin >> starttime >> kind >> acttime;
	// 		cout << "���������ڣ�1 ���Σ�2 ÿ�죬3 ÿ��" << endl;
	// 		cin >> type;
	// 		AddPersonalAlarmClock(starttime, kind, acttime, type);
	// 	}
	// 	else if (t == 6)
	// 	{
	// 		DeletePersonalAlarmClock();
	// 	}
	// 	else if (t == 7)
	// 	{
	// 		ShowPersonalAlarmClock();
	// 	}
	// 	else if (t == 8)
	// 	{
	// 		cout << "�����˳���¼" << endl;
	// 		break;
	// 	}
	// 	else 
	// 	{
	// 		cout << "�����ڴ˲���" << endl;
	// 	}


	// }
}



void student::Init()
{
	memset(timeline, 0, sizeof(timeline));
	InitCourseInformation();
	InitGroupActInformation();
	InitActivityInformation();
	InitTempActInformation();
	InitAlarmClockInformation();
	stop = 0;
	sysalarm = thread(&student::SystemAlarmClock,this);
	tmpalarm = thread(&student::TempAlarmClock,this);
	personalalarm = thread(&student::PersonalAlarmClock,this);
		//tmpalarm, personalalarm;
	//thread sysalarm,tmpalarm,personalalarm;


}
void student::save()
{
	sysalarm .join();
	tmpalarm .join();
	personalalarm.join();
	this->stop = 1;
}

void student::InitCourseInformation()
{
	for (int i = 0; i < WEEK_NUM; i++)
	{
		CourseNum[i] = 0;
	}
	CourseIdx = { 0,0 };
	ifstream ifs;
	int flag = 0;

	ifs.open("../datas/course_message.txt", ios::in);

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
}

void student::InitActivityInformation()
{
	for (int i = 0; i < WEEK_NUM; i++)
	{
		ActivityNum[i] = 0;
	}
	//ActivityIdx = { 0,0 };
	int flag = 0;

	ifstream ifs;

	ifs.open("../datas/activity_message.txt", ios::in);

	if (!ifs.is_open())
	{
		cout << "学生课外活动信息初始化错误" << endl;
		exit(0);
	}

	ifs.clear();
	ifs.seekg(0, ios::beg);

	string name;
	int StartTime;
	int place;
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

	ifstream ifs;

	ifs.open("../datas/groupact_message.txt", ios::in);

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
	int place;
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

	ifs.open("../datas/tempact_message.txt", ios::in);

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
	int place;
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
}

void student::InitAlarmClockInformation()
{
	AlarmNum = 0;
	AlarmIdx = 0;
	int flag = 0;

	ifstream ifs;

	ifs.open("../datas/alarmclock_message.txt", ios::in);

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
	while (ifs >> StartTime && ifs >> kind && ifs >> ActTime && ifs >> id)
	{
		if (StartTime >= now_time && id == this->id)
		{
			AlarmList[AlarmNum].StartTime = StartTime;
			AlarmList[AlarmNum].kind = kind;
			AlarmList[AlarmNum].ActTime = ActTime;
			AlarmList[AlarmNum].id = id;
			AlarmNum++;
		}	
	}
}

void student::ShowClassSchedule(int week)
{
	int CourseL = 0, CourseR = 0;
	int ActivityL = 0, ActivityR = 0;
	int GroupActL = 0, GroupActR = 0;
	int TempActL = 0, TempActR = 0;
	int w = week - 1;
	int num = 0;

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
}


int student::Search(int kind, string name)//半成品
{
	ofstream teststream;
	teststream.open("../datas/test_message.txt");

	teststream << name <<endl;
	int w = now_time / 168;
	int ret = -1;
	int flag = 0;
	//cout << now_time << " " << w << endl;
	if (kind == 1)
	{
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
					teststream << CourseList[i][j].name <<endl;
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
					teststream << CourseList[i][j].name <<endl;
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

	teststream << ret <<endl;
	teststream.close();
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

}

void student::SystemAlarmClock()
{
	int flag = 0;

	while (true)
	{
		Sleep(100);
		if (this->stop)
			break;
		int w = now_time / 168;
		if (now_time % 24 == 0 && flag == 0)
		{
			int idx = 0;
			for (idx = 0; idx < CourseNum[w]; idx++)
			{
				if (CourseList[w][idx].StartTime >= now_time)
				{
					break;
				}
			}
			for (int i = idx; i < CourseNum[w]; i++)
			{
				int tm = CourseList[w][i].StartTime;
				if (tm >= now_time + 24)
				{
					break;
				}
				cout << "";//�����Ϣ��
			}
			for (idx = 0; idx < GroupActNum[w]; idx++)
			{
				if (GroupActList[w][idx].StartTime >= now_time)
				{
					break;
				}
			}
			for (int i = idx; i < GroupActNum[w]; i++)
			{
				int tm = GroupActList[w][i].StartTime;
				if (tm >= now_time + 24)
				{
					break;
				}
				cout << "";//�����Ϣ��
			}
			for (idx = 0; idx < ActivityNum[w]; idx++)
			{
				if (ActivityList[w][idx].StartTime >= now_time)
				{
					break;
				}
			}
			for (int i = idx; i < ActivityNum[w]; i++)
			{
				int tm = ActivityList[w][i].StartTime;
				if (tm >= now_time + 24)
				{
					break;
				}
				cout << "";//�����Ϣ��
			}

		}
		else if (now_time % 24 != 0)
		{
			flag = 0;
		}
	}

}


void student::TempAlarmClock()
{
	int flag = 0;

	int tmpx, tmpy;

	while (true)
	{
		Sleep(100);
		if (this->stop)
			break;
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
			if (flag == 0)
			{
				cout << "";//�����Ϣ
				//���õ���
				flag = 1;
			}
		}
		else
		{
			flag = 0;
		}
	}
}


void student::PersonalAlarmClock()
{
	int flag = 0;

	while (true)
	{
		Sleep(100);
		if (this->stop)
			break;
		if (AlarmIdx < AlarmNum)
		{
			if (now_time == AlarmList[AlarmIdx].StartTime)
			{
				if (flag == 0)
				{
					ShowInfo(AlarmList[AlarmIdx].kind, AlarmList[AlarmIdx].ActTime);
					//���õ���
					if (AlarmList[AlarmIdx].type == 2)
					{
						AddPersonalAlarmClock(AlarmList[AlarmIdx].StartTime + 24, AlarmList[AlarmIdx].kind, AlarmList[AlarmIdx].ActTime + 24, AlarmList[AlarmIdx].type);
					}
					if (AlarmList[AlarmIdx].type == 3)
					{
						AddPersonalAlarmClock(AlarmList[AlarmIdx].StartTime + 168, AlarmList[AlarmIdx].kind, AlarmList[AlarmIdx].ActTime + 168, AlarmList[AlarmIdx].type);
					}
					flag = 1;
					AlarmIdx++;
				}
			}
			else
			{
				flag = 0;
			}
		}
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
}


void student::ShowPersonalAlarmClock()
{
	for (int i = AlarmIdx; i < AlarmNum; i++)
	{
		cout << AlarmList[i].StartTime << " " << AlarmList[i].kind << endl;
		ShowInfo(AlarmList[i].kind, AlarmList[i].ActTime);
	}
}

void student::ShowInfo(int kind, int ActTime)
{
	int w = ActTime / 168;
	int idx = 0;

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
		cout << CourseList[w][idx].name << " ";//��Ϣ��
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
		cout << GroupActList[w][idx].name << " ";
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
		cout << ActivityList[w][idx].name << " ";
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
		cout << TempActList[w][idx].name << " ";
	}


}




bool cmp(course a, course b)
{
	return a.StartTime < b.StartTime;
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

		ifs >> c.c_week;//���ε����0
		ifs >> c.week;//���ε����0
		course_Array.push_back(c);
	}
	ifs.close();
	ifs.open("student.txt", ios::in);
	ifs >> count_student;
	for (int i = 0; i < count_student; i++)
	{
		ifs >> s.name;
		ifs >> s.password;
		ifs >> s.ClassNum;
		ifs >> s.id;

		student_Array.push_back(s);
	}
}
void manager::add_class()
{
	int num, j = 0;
	course c;
	cout << "��ѡ��Ҫ���ӵĿγ�����" << endl;
	cin >> num;
	for (int i = 0; i < num; i++)
	{
		while (1)
		{
			cout << "�������" << i + 1 << "���γ̵����ƣ�" << endl;
			cin >> c.name;
			for (j = 0; j < count_course; j++)
			{
				if (course_Array[j].name == c.name)
				{
					cout << "�ÿγ��Ѵ��ڣ�" << endl;
					break;
				}
			}
			if (j == count_course)
				break;
		}
		cout << "�������" << i + 1 << "���γ̵Ŀ�ʼʱ�䣺" << endl;
		cin >> c.StartTime;
		cout << "�������" << i + 1 << "���γ̵Ľ���ʱ�䣺" << endl;
		cin >> c.EndTime;
		cout << "�������" << i + 1 << "���γ̵��Ͽεص㣺" << endl;
		cin >> c.place;
		cout << "�������" << i + 1 << "���γ̵��Ͽΰ༶��" << endl;
		cin >> c.Class;
		cout << "��" << i + 1 << "���γ��Ƿ�Ϊ���οΣ�" << endl;
		cout << "1.��	2.��" << endl;
		cin >> c.period;
		if (c.period == 2)
		{
			cout << "�������" << i + 1 << "���γ̵��Ͽ�������" << endl;
			cin >> c.c_week;
			cout << "�����������" << i + 1 << "���γ̵��Ͽ��ܣ�" << endl;
			cin >> c.week;
		}
		else
		{
			c.c_week = 1;
			cout << "�����������" << i + 1 << "���γ̵��Ͽ��ܣ�" << endl;
			cin >> c.week;
		}
		course_Array.push_back(c);
		count_course++;
	}
	
	sort(course_Array.begin(), course_Array.end(), cmp);
	fUpdate();
	cout << "���ӳɹ���" << endl;
}
void manager::delete_class()
{
	string name;
	int num, i = 0;
	while (1)
	{
		cout << "������Ҫɾ���Ŀγ����ƣ�" << endl;
		cin >> name;

		for (i = 0; i < count_course; i++)
		{
			if (course_Array[i].name == name)
			{
				num = i;
				break;
			}
		}
		if (i == count_course)
			cout << "�ÿγ̲����ڣ�" << endl;
		else
			break;
	}
	auto it = course_Array.begin() + num;
	course_Array.erase(it);
	count_course--;
	fUpdate();
	cout << "ɾ���ɹ���" << endl;
}
void manager::change_class()
{
	string name;
	int num, j = 0, i = 0;
	course c;
	while (1)
	{
		cout << "������Ҫ�޸ĵĿγ����ƣ�" << endl;
		cin >> name;
		for (i = 0; i < count_course; i++)
		{
			if (course_Array[i].name == name)
			{
				num = i;
				break;
			}
		}
		if (i == count_course)
			cout << "�ÿγ̲����ڣ�" << endl;
		else
			break;
	}
	while (1)
	{
		cout << "�������޸ĺ�γ̵����ƣ�" << endl;
		cin >> c.name;
		for (j = 0; j < count_course; j++)
		{
			if (course_Array[j].name == c.name && num != j)
			{
				cout << "�ÿγ��Ѵ��ڣ�" << endl;
				break;
			}
		}
		if (j == count_course)
			break;
	}
	cout << "�������޸ĺ�γ̵Ŀ�ʼʱ�䣺" << endl;
	cin >> c.StartTime;
	cout << "�������޸ĺ�γ̵Ľ���ʱ�䣺" << endl;
	cin >> c.EndTime;
	cout << "�������޸ĺ�γ̵��Ͽεص㣺" << endl;
	cin >> c.place;
	cout << "�������޸ĺ�γ̵��Ͽΰ༶��" << endl;
	cin >> c.Class;
	cout << "�޸ĺ�γ��Ƿ�Ϊ���οΣ�" << endl;
	cout << "1.��	2.��" << endl;
	cin >> c.period;
	if (c.period == 2)
	{
		cout << "�������޸ĺ�γ̵��Ͽ�������" << endl;
		cin >> c.c_week;
		cout << "�����������޸ĺ�γ̵��Ͽ��ܣ�" << endl;
		cin >> c.week;
	}
	else
	{
		c.week = 1;
		cout << "�����������޸ĺ�γ̵��Ͽ��ܣ�" << endl;
		cin >> c.week;
	}
	course_Array[num] = c;
	fUpdate();
	cout << "�޸ĳɹ���" << endl;
}
void manager::add_student()
{
	int num, j = 0;
	student s;
	string s2;
	string s1 = "2021";
	cout << "��ѡ��Ҫ���ӵ�ѧ������" << endl;
	cin >> num;
	for (int i = 0; i < num; i++)
	{
		while (1)
		{
			cout << "�������" << i + 1 << "��ѧ����id��" << endl;
			cin >> s.id;
			for (j = 0; j < count_student; j++)
			{
				if (student_Array[j].id == s.id)
				{
					cout << "��ѧ���Ѵ��ڣ�" << endl;
					break;
				}
			}
			if (j == count_student)
				break;
		}
		cout << "�������" << i + 1 << "��ѧ����������" << endl;
		cin >> s.name;
		cout << "�������" << i + 1 << "��ѧ���İ༶��" << endl;
		cin >> s.ClassNum;
		s2 = to_string(s.id);
		s1 = "2021";
		s1 = s1 + s2;
		s.password = s1;//����Ĭ������
		student_Array.push_back(s);
		count_student++;
	}
	fUpdate();
	cout << "���ӳɹ���" << endl;
}
void manager::delete_student()
{
	int id;
	int num, i = 0;
	while (1)
	{
		cout << "������Ҫɾ����ѧ��id��" << endl;
		cin >> id;

		for (i = 0; i < count_student; i++)
		{
			if (student_Array[i].id == id)
			{
				num = i;
				break;
			}
		}
		if (i == count_student)
			cout << "��ѧ�������ڣ�" << endl;
		else
			break;
	}
	auto it = student_Array.begin() + num;
	student_Array.erase(it);
	count_student--;
	fUpdate();
	cout << "ɾ���ɹ���" << endl;
}
void manager::change_student()
{
	int id;
	int num, j = 0, i = 0;
	student s;
	while (1)
	{
		cout << "������Ҫ�޸ĵ�ѧ����id��" << endl;
		cin >> id;
		for (i = 0; i < count_student; i++)
		{
			if (student_Array[i].id == id)
			{
				num = i;
				break;
			}
		}
		if (i == count_student)
			cout << "��ѧ�������ڣ�" << endl;
		else
			break;
	}
	while (1)
	{
		cout << "�������޸ĺ��id��" << endl;
		cin >> s.id;
		for (j = 0; j < count_student; j++)
		{
			if (student_Array[j].id == s.id && num != j)
			{
				cout << "��ѧ���Ѵ��ڣ�" << endl;
				break;
			}
		}
		if (j == count_student)
			break;
	}
	cout << "�������޸ĺ�ѧ����������" << endl;
	cin >> s.name;
	cout << "�������޸ĺ�ѧ���İ༶��" << endl;
	cin >> s.ClassNum;
	s.password = student_Array[num].password;
	student_Array[num] = s;
	fUpdate();
	cout << "�޸ĳɹ���" << endl;
}
void manager::fUpdate()
{
	ofstream ofs;
	ofs.open("../datas/course.txt", ios::out);//outΪ��дģʽ�����Ὣԭ���ļ��е�����ȫ�����
	ofs << count_course << endl;
	for (int i = 0; i < count_course; i++)
	{
		ofs << course_Array[i].name << "\t"
			<< course_Array[i].StartTime << "\t"
			<< course_Array[i].EndTime << "\t"
			<< course_Array[i].place << "\t"
			<< course_Array[i].Class << "\t"
			<< course_Array[i].period << "\t"
			<< course_Array[i].c_week << "\t"
			<< course_Array[i].week << endl;
	}//д�ļ�����
	ofs.close();
	ofs.open("../datas/student.txt", ios::out);
	ofs << count_student << endl;
	for (int i = 0; i < count_student; i++)
	{
		ofs << student_Array[i].name << "\t"
			<< student_Array[i].password << "\t"
			<< student_Array[i].ClassNum << "\t"
			<< student_Array[i].id << endl;
	}//д�ļ�����
	ofs.close();
}
void manager::connection()
{
	ofstream ofs;
	ofs.open("course_list.txt", ios::out);
	vector<course> temp;
	temp = course_Array;
	int m_time = 0;
	for (int j = 1; j <= 19; j++)
	{
		for (int k = 0; k < count_course; k++)
		{
			if (temp[k].check[j] == 1)
			{
				ofs << temp[k].name << "\t";
				ofs << temp[k].StartTime << "\t";
				ofs << temp[k].EndTime << "\t";
				ofs << temp[k].place << "\t";
				ofs << temp[k].Class << "\t";
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