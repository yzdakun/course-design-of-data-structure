#include<bits/stdc++.h>
#include<windows.h>
#include<direct.h>
using namespace std;
char program[256];
char buffer[256];
void HideWindow()
{
    HWND hwnd=GetForegroundWindow();
    if(hwnd)
    {
        ShowWindow(hwnd, SW_HIDE);
    }
}
int main(int argc, char** argv)
{
    HideWindow();
    // Sleep(100000);
    string a=argv[0];
    int len=a.length();
    a=a.substr(0,len-16);
    char path[256];
    strcpy(path,a.c_str());
    SetCurrentDirectoryA(path);
    _getcwd(buffer,256);
    cout<<buffer<<endl;
    char **tmp=argv;
    cout<<argc<<endl;
    int i=0;
    while(*tmp!=NULL)
    {
        cout<<i++<<": "<<*tmp<<endl;
        ++tmp;
    }
    // Sleep(100000);
    // if(argc==1) return 0;
    freopen("js2exe.txt","w",stdout);
    // cout<<"test"<<endl;
    // Sleep(5000);
    // fclose(stdout);
    vector<string> new_argvs;
    string tmpArgvs;
    if(argc>1) tmpArgvs=argv[1];
    std::string::size_type cnt=tmpArgvs.find_last_of("&&");
    while(cnt!=-1)
    {
        new_argvs.push_back(tmpArgvs.substr(cnt+1,tmpArgvs.length()-cnt));
        tmpArgvs=tmpArgvs.substr(0,cnt);
        cnt=tmpArgvs.find_last_of("&&");
    }

    len=new_argvs.size()-1;
    for(int i=len;i>=0;i--)
        cout<<new_argvs[i]<<endl;

    // len=new_argvs.size()-1;
    // string msg="";
    // for(int i=len;i>=0;i--)
    // {
    //     msg+=new_argvs[i];
    //     msg+=' ';
    // }
    // msg=msg.substr(1,msg.length()-3);
    // cout<<msg<<endl;
    // char posMsg[256];
    // strcpy(posMsg,msg.c_str());
    // system(posMsg);
    fclose(stdout);
    exit(0);
    return 0;
}