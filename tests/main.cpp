#include <bits/stdc++.h>
#include <direct.h>
#include <windows.h>
#include <tchar.h>
#include <iomanip>
#include "BPlus_node.h"
#include "BPlus_tree.h"
#include "Log_control.h"
#include "BPlus_node.cpp"
#include "BPlus_tree.cpp"
#include "Log_control.cpp"
#include "user.cpp"
using namespace std;

void fileWatcher();

int main(int argc, char** argv)
{
	string a=argv[0];
    int len=a.length();
    a=a.substr(0,len-12);
    char path[MAX_PATH];
    strcpy(path,a.c_str());
    SetCurrentDirectoryA(path);

	fileWatcher();
	
}

void fileWatcher()
{
	DWORD cbBytes;
	char file_name[MAX_PATH];
	char file_rename[MAX_PATH]; 
	char notify[1024];
	int count = 0;
	TCHAR *dir = _T("D:\\Antarc\\C++\\Datastructure\\main\\cpps");

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

	while (true)
	{
		if (ReadDirectoryChangesW(dirHandle, &notify, 1024, true,
								  FILE_NOTIFY_CHANGE_FILE_NAME | FILE_NOTIFY_CHANGE_DIR_NAME | FILE_NOTIFY_CHANGE_SIZE,
								  &cbBytes, NULL, NULL))
		{

			switch (pnotify->Action)
			{

			case FILE_ACTION_MODIFIED:
				Login();
				break;

			}
		}
	}

	CloseHandle(dirHandle);
}