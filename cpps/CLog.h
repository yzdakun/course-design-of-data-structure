#pragma once

#include<iostream>
#include<fstream>
#include<string>
#include<chrono>
using namespace std;
class CLog
{
private:
	ofstream ofsCLog;
public:
	void init(const string filename)
	{
		this->ofsCLog.open(filename.c_str(), ios::trunc);
		if (ofsCLog.is_open())
		{
			ofsCLog.close();
		}
		this->ofsCLog.open(filename.c_str(), ios::out | ios::app);
		if(this->ofsCLog.is_open())
			cout << "opened" << endl;
		else
			cout << "closed" << endl;
		return;
	}
	~CLog()
	{
		if (this->ofsCLog.is_open())
		{
			ofsCLog.close();
		}
	}

	void wr(const string name, const string content)
	{
		auto now = std::chrono::system_clock::now();
		time_t tt = std::chrono::system_clock::to_time_t(now);
		auto time_tm = localtime(&tt);
		char strTime[25] = { 0 };
		sprintf(strTime, "%d-%02d-%02d %02d:%02d:%02d", time_tm->tm_year + 1900,
			time_tm->tm_mon + 1, time_tm->tm_mday, time_tm->tm_hour,
			time_tm->tm_min, time_tm->tm_sec);

		if(this->ofsCLog.is_open())
			cout << "opened" << endl;
		else
			cout << "closed" << endl;

 		this->ofsCLog << strTime << ", " << name << "," << content << endl;
		this->ofsCLog.flush();
		return;
	}
};


extern CLog log1;