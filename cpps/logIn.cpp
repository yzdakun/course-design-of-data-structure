#include<bits/stdc++.h>
#include<windows.h>
using namespace std;
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
    freopen("userids.txt","r",stdin);
    freopen("exe2js.txt","w",stdout);
    char **tmp=argv;
    // cout<<argc<<endl;
    int i=0;
    // while(*tmp!=NULL)
    // {
    //     cout<<i++<<": "<<*tmp<<endl;
    //     ++tmp;
    // }
    if(argc==1)
    {
        fclose(stdout);
        return 0;
    }
    tmp=argv;
    vector<string> userid;
    vector<string> psw;
    string a="x",b,c;
    while(a!="&")
    {
        cin>>a;
        userid.push_back(a);
        cin>>a;
        psw.push_back(a);
    }
    // for(auto x:userid)
    //     cout<<x<<endl;

    i=8;

    a=tmp[1];
    b=tmp[2];
    c=tmp[3];
    // cout<<tmp[1][i]<<endl;
    long long tim=stoll(c);

    int flag=0;
    int j=0,lenu=userid.size();
    for(;j<lenu;j++)
        if(a==userid[j])
        {
            flag=1;
            break;
        }

    if(!flag) cout<<0<<endl;
    else if(b!=psw[j]) cout<<0<<endl;
    else cout<<1<<endl;
    cout<<tim;      
    fclose(stdout);
    // system("pause");
    return 0;
}