#include <bits/stdc++.h>
#include <direct.h>
#include <windows.h>
#include <tchar.h>
#include <iomanip>
#include <thread>
#include "BPlus_node.h"
#include "BPlus_tree.h"
#include "Log_control.h"
#include "Time.h"
#include "findWay.h"
#include "user.h"
#include "BPlus_node.cpp"
#include "BPlus_tree.cpp"
#include "Log_control.cpp"
#include "user.cpp"
#include "Time.cpp"
// #include "manager.cpp"
#include "course.cpp"
using namespace std;


#define LOGIN_COMMAND 0
#define ASK_FOR_COURSE 1

void fileWatcher();
void HideWindow();
string CharToStr(char * contentChar);
void DelLineData(int lineNum);


int main(int argc, char** argv)
{
    // HideWindow();
	string a=argv[0];
    int len=a.length();
    a=a.substr(0,len-12);
    char path[MAX_PATH];
    strcpy(path,a.c_str());
    SetCurrentDirectoryA(path);

	fileWatcher();

	
}

void HideWindow()
{
    HWND hwnd=GetForegroundWindow();
    if(hwnd)
    {
        ShowWindow(hwnd, SW_HIDE);
    }
}

void fileWatcher()
{
	DWORD cbBytes;
	char file_name[MAX_PATH];
	char file_rename[MAX_PATH]; 
	char notify[1024];
	int count = 0;
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
				ifstream ifs;
				ifs.open("js2exe.txt",ios::in);
				ifs>>flag;
				cout<<flag<<endl;
				// DelLineData(2);

				switch (flag)
				{
				case LOGIN_COMMAND:
					// cout<<"LOGIN_COMMAND"<<endl;
					Login();
					ifs.close();
				
				default:
					break;
				}
				break;

			}
			// Sleep(100);
		}
	}

	CloseHandle(dirHandle);
}

// string CharToStr(char * contentChar)
// {
// 	string tempStr;
// 	for (int i=0;contentChar[i]!='\0';i++)
// 	{
// 		tempStr+=contentChar[i];
// 	}
// 	return tempStr;
// }

// void DelLineData(int lineNum)
// {
// 	ifstream in;
// 	in.open("js2exe.txt");
	
// 	string strFileData = "";
// 	int line = 1;
// 	char lineData[1024] = {0};
// 	while(in.getline(lineData, sizeof(lineData)))
// 	{
// 		if (line == lineNum)
// 		{
// 			strFileData += "\n";
// 		}
// 		else
// 		{
// 			strFileData += CharToStr(lineData);
// 			strFileData += "\n";
// 		}
// 		line++;
// 	}
// 	in.close();
 
// 	//写入文件
// 	ofstream out;
// 	out.open("js2exe.txt");
// 	out.flush();
// 	out<<strFileData;
// 	out.close();
// }
