/*
Windows Registry Editor Version 5.00
[HKEY_CLASSES_ROOT\Start]
"URL Protocol"="D:\\Antarc\\C++\\Datastructure\\Learning\\scripts\\test.exe"
@="Start Protocol"
[HKEY_CLASSES_ROOT\Start\DefaultIcon]
@="D:\\Antarc\\C++\\Datastructure\\Learning\\scripts\\test.exe,1"
[HKEY_CLASSES_ROOT\Start\shell]
[HKEY_CLASSES_ROOT\Start\shell\open]
[HKEY_CLASSES_ROOT\Start\shell\open\command]
@="\"D:\\Antarc\\C++\\Datastructure\\Learning\\scripts\\test.exe\" \"%1\""
*/
#include<bits/stdc++.h>
#include<direct.h>
using namespace std;
char buffer[256];
string cwd,cwd2;
int main()
{
    _getcwd(buffer,256);
    int len=strlen(buffer);
    for(int i=0;i<len;i++)
    {
        if(buffer[i]!='\\') cwd+=buffer[i];
        else
        {   
            cwd+="\\\\";
        }
    }
    cwd2=cwd;
    cwd+="\\\\cpps\\\\control.exe";
    freopen("Start.reg","w",stdout);
    cout<<"Windows Registry Editor Version 5.00"<<endl;
    cout<<"[HKEY_CLASSES_ROOT\\openexe]"<<endl;
    cout<<"\"URL Protocol\"="<<"\""<<cwd<<"\""<<endl;
    cout<<"@=\"openexe Protocol\""<<endl;
    cout<<"[HKEY_CLASSES_ROOT\\openexe\\DefaultIcon]"<<endl;
    cout<<"@="<<"\""<<cwd<<",1\""<<endl;
    cout<<"[HKEY_CLASSES_ROOT\\openexe\\shell]"<<endl;
    cout<<"[HKEY_CLASSES_ROOT\\openexe\\shell\\open]"<<endl;
    cout<<"[HKEY_CLASSES_ROOT\\openexe\\shell\\open\\command]"<<endl;
    cout<<"@="<<"\"\\\""<<cwd<<"\\\" \\\"%1\\\"\""<<endl;
    fclose(stdout);

    cwd2+="\\\\cpps\\\\sendmessage.exe";
    freopen("Start2.reg","w",stdout);
    cout<<"Windows Registry Editor Version 5.00"<<endl;
    cout<<"[HKEY_CLASSES_ROOT\\closeexe]"<<endl;
    cout<<"\"URL Protocol\"="<<"\""<<cwd2<<"\""<<endl;
    cout<<"@=\"closeexe Protocol\""<<endl;
    cout<<"[HKEY_CLASSES_ROOT\\closeexe\\DefaultIcon]"<<endl;
    cout<<"@="<<"\""<<cwd2<<",1\""<<endl;
    cout<<"[HKEY_CLASSES_ROOT\\closeexe\\shell]"<<endl;
    cout<<"[HKEY_CLASSES_ROOT\\closeexe\\shell\\open]"<<endl;
    cout<<"[HKEY_CLASSES_ROOT\\closeexe\\shell\\open\\command]"<<endl;
    cout<<"@="<<"\"\\\""<<cwd2<<"\\\" \\\"%1\\\"\""<<endl;
    fclose(stdout);
    return 0;
}