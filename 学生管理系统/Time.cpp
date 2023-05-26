#include<iostream>
#include<windows.h>
#include"Time.h"
using namespace std;

int now_time=0;
int speed =2000;
int x=1;
int St = 0;

void time_run()
{
	now_time = 0;
	while (true)
	{
		if (St == 1)
			break;
		Sleep(speed);
		now_time += x;
		cout << now_time << endl;
	}
}









