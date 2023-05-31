#pragma once

#include<iostream>
#include<fstream>
#include<string>
using namespace std;
class CLog
{
private:
	ofstream ofs;
public:
	CLog(const string filename)
	{
		this->ofs.open(filename.c_str(), ios::trunc);
		if (ofs.is_open())
		{
			ofs.close();
		}
		this->ofs.open(filename.c_str(), ios::out | ios::app);
		return;
	}
	~CLog()
	{
		if (this->ofs.is_open())
		{
			ofs.close();
		}
	}

	void wr(const int now_time, const string name, const string content)
	{
		this->ofs << now_time << "," << name << "," << content << endl;
		return;
	}
};


extern CLog log1;