#include<windows.h>
#include<iostream>
#include<wchar.h>
#include<string>
using namespace std;
string stohex(const string &str)
{
	const char temp[2049] = {0};
	const char *buf = temp;
	buf = str.c_str();

	char dst[2049] = {0};
	char buf_temp[2049] = {0};
	int x = 0;
	unsigned long i;
	while(*buf != '\0')
	{
		if(*buf == '\\')
		{
			strcpy(buf_temp,buf);
			*buf_temp = '0';
			*(buf_temp + 4) = '\0';
			i = strtoul(buf_temp, NULL, 16);
			dst[x] = i;
			buf += 3;
		}
		else
		{
			dst[x] = *buf;
		}
		x++;
		buf++;
 
 
	}	
	dst[x] = '\0';
	return dst;
}

string UTF8_To_string(const string & str)
{
	// system("pause");
	if(str[0]!='%')
		return str;
	string tmp="";
	int len=str.length();
	for(int i=0;i<len;i++)
	{
		if(str[i]=='%')
			tmp+='\\';
		tmp+=str[i];
	}
	// system("pause");
	replace(tmp.begin(),tmp.end(),'%','x');
	// cout<<tmp<<endl;
	return stohex(tmp);
}


