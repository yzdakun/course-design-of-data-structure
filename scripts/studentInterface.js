var selectdom = document.getElementById('week');
var calen = document.getElementById('date');
var couta = document.getElementById('coutable');
var cit = document.querySelectorAll('.chooseItem-row');
var timeControler=document.querySelectorAll('div.chooseItem');
var exit = document.getElementById('exit');
var nowTime=new Date();
var timeWalkPace=1000;
var timeBox=document.getElementById('timeBox');

var daze=document.querySelectorAll(".day");

var addAct=document.getElementById('addAct');
var ActForm=document.getElementById('actForm');
var quizTim=document.getElementById('bonusquizTime');
var startDate=document.getElementById('newActdate');
var endDate=document.getElementById('endDate');
var addpage01=document.getElementById('addAct-page01');
var addpage02=document.getElementById('addAct-page02');
var dele=document.getElementById('del');

var totNum=document.getElementById('totNum');
var actSection=document.getElementById('actSection');
var alarmSection=document.getElementById('alarmSection');
var tips=document.getElementById('tips');

var coodinates=load("./coodinates.txt");
var num2plac=load("./num2placTable.txt");
var buffer=load("./pagebuffer.txt");
var log = load("../datas/log.txt");
coodinates=coodinates.split("\n");
buffer=buffer.split("\r").join("");
num2plac=num2plac.split("\r").join("");
num2plac=num2plac.split("\n");
log=log.split("\r").join("");
log=log.split("\n");
var balls=[];

const canvas=document.querySelector('canvas');
const ctx=canvas.getContext('2d');
var num=1;
var middlePointsNum=0;
var SANum=0;
var level;

document.querySelectorAll('select').forEach(el=>{
    if(el.id!="week" && el.id!="searchType")
        addOption(el);
})

function load(name) {
    let xhr = new XMLHttpRequest(),
        okStatus = document.location.protocol === "file:" ? 0 : 200;
    xhr.open('GET', name, false);
    xhr.overrideMimeType("text/html;charset=utf-8");//默认为utf-8
    xhr.send(null);
    return xhr.status === okStatus ? xhr.responseText : null;
}

window.onload = function() {
    buffer=buffer.split("\n");
    initLog();
    switch(Number(buffer[0]))
    {
        case -1:
            initTime(new Date("2023-02-20").getTime());
            changePage(0);
            timeSet(1);
            // initact();
            // initAlarm();
            var nowWeek = selectdom.selectedIndex+1;
            var para = document.createElement("a");
            para.href='closeexe://&&11&&' + nowWeek + '&&' + calen.value + '&&' + nowTime.getTime() + '&&' + jsHour2exe();
            para.click();
            break;
        case 0:
            changePage(0);

            selectdom.selectedIndex=Number(buffer[1])-1;
            if(buffer[2]!="null")
            {
                calen.value=buffer[2];
                chacalen(0);
            }
            else
                chacalen(1);

            initTime(Number(buffer[3]));
            timeSet(1);

            initact();
            initAlarm();
            var page01 = document.getElementById('page01');
            page01.scrollBy(0,Number(buffer[4]));
            if(Number(buffer[5]) === 1)
            {
                tips.style.display='block';
                var i=5;
                var tipsContent=document.getElementById('tipsContent');
                while(buffer[i]!="")
                {
                    if(buffer[i]==="1")
                    {
                        i++;
                        continue;
                    }
                    if(Number(buffer[i]) > 1 && Number(buffer[i] <= 10000))
                        buffer[i]=exeHour2js(buffer[i]);
                    var newp=document.createElement("p");
                    newp.innerHTML=buffer[i];
                    tipsContent.appendChild(newp);
                    i++;
                }
            }
            break;

        case 1:
            case 0:
            changePage(1);

            selectdom.selectedIndex=Number(buffer[1])-1;
            calen.value=buffer[2];
            chacalen(0);
            initTime(Number(buffer[3]));
            timeSet(0);

            initact();
            initAlarm();

            if(Number(buffer[4]) === 1)
            {
                tips.style.display='block';
                var i=5;
                var tipsContent=document.getElementById('tipsContent');
                while(buffer[i]!="")
                {
                    if(buffer[i]==="1")
                    {
                        i++;
                        continue;
                    }
                    if(Number(buffer[i]) > 1 && Number(buffer[i] <= 10000))
                        buffer[i]=exeHour2js(buffer[i]);
                    var newp=document.createElement("p");
                    newp.innerHTML=buffer[i];
                    tipsContent.appendChild(newp);
                    i++;
                }
            }
            break;

        case 2:
            selectdom.selectedIndex=Number(buffer[1])-1;
            calen.value=buffer[2];
            chacalen(0);

            initTime(Number(buffer[3]));
            timeSet(0);

            initact();
            initAlarm();

            changePage(2);
            drawWay();
            break;
        case 5:
            changePage(0);

            selectdom.selectedIndex=Number(buffer[1])-1;
            if(buffer[2]!="null")
            {
                calen.value=buffer[2];
                chacalen(0);
            }
            else
                chacalen(1);

            initTime(Number(buffer[3]));
            timeSet(1);
            var page01 = document.getElementById('page01');
            page01.scrollBy(0,Number(buffer[4]))
            initact();
            initAlarm();
            
            timeWalkPace = Number(buffer[5]);
            if(timeWalkPace === 1000)
                timeSet(1);
            else if(timeWalkPace === 1000 * 60 * 6)
                timeSet(2);
            else 
                timeSet(3);
            checkPAT();
            checkSAT();
            checkTAT();
            break;
        default:
            break;
    }
    // if(Number(buffer[0]==-1))
    // {
        
    // }
    // else
    // {
    //     initTime(new Date().getTime());
    //     changePage(0);
    //     timeSet(1);
    //         // cit[3].click();
            
    //     // }
    //     initact();
    //     initAlarm();
    // }
    
}

//切换页面
cit[0].onclick = function() {
    if(level!=0)
        changePage(0);
    timeControler[1].click();
}
cit[1].onclick = function() {
    if(level!=1)
        changePage(1);
    timeControler[0].click();
}
cit[2].onclick = function() {
    if(level!=2)
        changePage(2);
    timeControler[0].click();
}
cit[3].onclick = function() {
    if(level!=3)
    {
        changePage(3); 
    }
    initCanvas();    
    timeControler[0].click();
}
dele.onclick = function() {
    del(dele);
}
exit.onclick = function() {
    var para = document.createElement("a");
    para.href = 'closeexe://&&20&&';
    para.click();
}

function initTime(domTime) {

    nowTime=new Date(domTime);
    timeBox.innerHTML=nowTime.toLocaleString();
}//初始化时间

function timeWalk() {
    var nowTimStamp=new Date(nowTime).getTime();
    nowTimStamp+=timeWalkPace;
    var oriHour = nowTime.getHours();
    nowTime=new Date(nowTimStamp);
    var newHour = nowTime.getHours();
    var page01 = document.getElementById('page01');
    if(newHour != oriHour)
    {
        var week = selectdom.selectedIndex + 1;
        var para = document.createElement("a");
        para.href = 'closeexe://&&12&&' + week + '&&' + calen.value + '&&' + nowTime.getTime() + '&&' + page01.scrollTop + '&&' + timeWalkPace + '&&' + jsHour2exe();
        para.click();
    }
    timeBox.innerHTML=nowTime.toLocaleString();
}
setInterval(timeWalk,1000);//控制时间前进

function timeSet(i) {
    document.querySelectorAll('div.chooseItem').forEach(el=>{
        el.style='none';
        el.style.border='2px solid aliceblue';
    })
    timeControler[i].style.color='#57EEEB';
    timeControler[i].style.border='2px solid #57EEEB';

    if(i===0)
        timeWalkPace=0;
    else if(i===1)
        timeWalkPace=1000;
    else if(i===2)
        timeWalkPace=1000*60*6;
    else
        timeWalkPace=1000*60*60;
}//设置时间前进的快慢

function timeCha() {
    timeControler[0].click();
    var timeSetterBox=document.getElementById('timeSetterBox');
    var timeSetter=document.getElementById('timeSetter');
    timeSetterBox.style.display='block';
    timeSetter.value=nowTime;
    
}//更改当前时间

function timeCon(flag) {
    var timeSetterBox=document.getElementById('timeSetterBox');
    var timeSetter=document.getElementById('timeSetter');
    if(flag===1 && timeSetter.value!="")
    {
        console.log(timeSetter.value)
        nowTime=timeSetter.value;
        timeBox.innerHTML=nowTime.toLocaleString();
        timeSetterBox.style.display='none';
    }
    else
        timeSetterBox.style.display='none';
    timeControler[1].click();
    var nowTimStamp=new Date(nowTime).getTime();
    nowTime=new Date(nowTimStamp);
    nowWeek = selectdom.selectedIndex+1;
    var page01 = document.getElementById('page01');
    var para = document.createElement("a");
    para.href='closeexe://&&13&&' + nowWeek + '&&' + calen.value + '&&' + nowTime.getTime() + '&&' + page01.scrollTop + '&&' + jsHour2exe();
    para.click();
}//时间修改器的开启与关闭

function changePage(i) {
    level=i;
    var pag=document.querySelectorAll('.page')[i];

    document.querySelectorAll('.page').forEach(el=>{
        el.style.display = 'none';
    })
    document.querySelectorAll('.chooseItem-row').forEach(el=>{
        el.style='none';
        el.style.border='2px solid aliceblue';
    })

    pag.style.display = 'block';
    cit[i].style.color = '#57EEEB';
    cit[i].style.border = '2px solid #57EEEB';
}//更换页面

selectdom.onchange = function() 
{
    chacalen(1);
    askForCourse(selectdom.selectedIndex+1);
    
}

calen.onchange = function()
{
    chaselect();
    askForCourse(selectdom.selectedIndex+1);
    // chacalen(0); 
}

function chacalen(flag) {
    var index = selectdom.options.selectedIndex;
    var value = selectdom.options[index].value;
    var v = Number(value);
    var newdate="2023-02-20";
    if(v===1)
        newdate="2023-02-20";
    else if(v===2)
        newdate="2023-02-27";
    else if(v===3)
        newdate="2023-03-06";
    else if(v===4)
        newdate="2023-03-13";
    else if(v===5)
        newdate="2023-03-20";
    else if(v===6)
        newdate="2023-03-27";
    else if(v===7)
        newdate="2023-04-03";
    else if(v===8)
        newdate="2023-04-10";
    else if(v===9)
        newdate="2023-04-17";
    else if(v===10)
        newdate="2023-04-24";
    else if(v===11)
        newdate="2023-05-01";        
    else if(v===12)
        newdate="2023-05-08";
    else if(v===13)
        newdate="2023-05-15";
    else if(v===14)
        newdate="2023-05-22";
    else if(v===15)
        newdate="2023-05-29";
    else if(v===16)
        newdate="2023-06-05";
    else if(v===17)
        newdate="2023-06-12";
    else if(v===18)
        newdate="2023-06-19";
    else if(v===19)
        newdate="2023-06-26";

    
    console.log(flag);
    if(flag===1)
        calen.value = newdate;
        
    var date=new Date(newdate);
    for(var i=0;i<7;i++)
    {
        var m=date.getMonth()+1;
        m=m<10?'0'+m:m;
        var d=date.getDate();
        d=d<10?'0'+d:d;
        var s=m+'-'+d;
        daze[i].innerHTML=s;
        var tmp=date.valueOf();
        tmp+=1000*60*60*24;
        date=new Date(tmp);
    }
    
}//同步日程表的日期与周数

function chaselect() {
    var basedate=new Date("2023-02-20");
    var nowdate=new Date(calen.value);

    var base=basedate.valueOf();
    var now=nowdate.valueOf();

    selectdom.selectedIndex=(now-base)/1000/60/60/24/7;
}//同上

function initact() {
    var blos=couta.querySelectorAll('tr');
    let text=load("../datas/coumes.txt");
    text=text.split("\r").join("");
    var s=text.split("\n");
    // console.log(s);
    var j=0;
    for(var i=1;i<=7;i++)
    {
        var now=1;
        var info=s[j].split(" ");
        var num=Number(info[0]);
        for(var k=1;k<=num;k++)
        {
            j++;
            info=s[j].split(" ");
            if(info[0]==="1")
            {
                var top=Number(info[1])%24,bot=Number(info[2])%24,hei=bot-top;
                while(now<=top)
                {
                    addNtd(blos[now],now,i);
                    now++;
                }
                addEve(i,top,bot,hei,blos[now],info,1);
                now=bot+1;
            }
            else if(info[0]==="2")
            {
                var top=Number(info[1])%24,bot=Number(info[2])%24,hei=bot-top;
                while(now<=top)
                {
                    addNtd(blos[now],now,i);
                    now++;
                }
                addEve(i,top,bot,hei,blos[now],info,2);
                now=bot+1;
            }
            else if(info[0]==="3")
            {
                var top=Number(info[1])%24,bot=Number(info[2])%24,hei=bot-top;
                while(now<=top)
                {
                    addNtd(blos[now],now,i);
                    now++;
                }
                addEve(i,top,bot,hei,blos[now],info,3);
                now=bot+1;
            }
            else if(info[0]==="4")
            {
                var top=Number(info[1])%24,bot=Number(info[2])%24,hei=bot-top;
                while(now<=top)
                {
                    addNtd(blos[now],now,i);
                    now++;
                }
                addEve(i,top,bot,hei,blos[now],info,4);
                now=bot+1;
            }
        }
        j++;
        while(now<=24)
        {
            addNtd(blos[now],now,i);
            now++;
        }
    }
}//初始化日程表

function askForCourse(week)
{
    var para=document.createElement("a");
    para.href = 'closeexe://&&1&&' + week + '&&' + calen.value + '&&' + nowTime.getTime();
    para.click();
}

function addNtd(bl,tmp,i)
{
    var ntd=document.createElement("td");
    ntd.id=daze[i-1].innerHTML+'&'+tmp;
    ntd.onclick=function(){
        buildNew(ntd);
    }
    bl.appendChild(ntd);
}//加入空方格

function addEve(ind,top,bot,hei,bl,info,type) {
    var ntd=document.createElement("td");
    var ndi=document.createElement("div");
    var box=document.createElement("div");

    ntd.rowSpan=hei;
    ntd.id=ind+'&'+daze[ind-1].innerHTML+'&'+top+'&'+bot;

    ndi.style.width='95%';
    ndi.style.height='98%';
    ndi.style.margin='1px 2px 1px 2px';
    ndi.style.borderRadius='5px';
    ndi.style.display='grid';
    ndi.style.placeItems='center';

    var goThere=document.createElement("button");
    goThere.type="button";
    goThere.style.display='none';
    goThere.innerHTML="导航";

    var delAct=document.createElement("button");
    delAct.type="button";
    delAct.style.display='none';
    delAct.innerHTML="删除";
    delAct.onclick = function() {
        delActicity(info)
    }

    var createAlarm=document.createElement("button");
    createAlarm.type="button";
    createAlarm.style.display='none';
    createAlarm.innerHTML="添加闹钟";
    if(type===4)
    {
        goThere.onclick = function() {
            goMultiple(info);
        }
    }
    else
    {
        goThere.onclick = function() {
            goSingle(info,type);
        }
    }
    if(type!=1)
    {
        createAlarm.onclick = function() {
            addAlarm(info,type);
        }
    }
    if(type===1)
    {
        ndi.style.backgroundColor='#F56A6A';
        var name=document.createElement("p");
        name.innerHTML=info[3];
        var clas=document.createElement("p");
        clas.innerHTML="上课班级："+info[4];
        var plac=document.createElement("p");
        plac.innerHTML="上课地点："+writePlace(Number(info[5]));
        box.appendChild(name);
        box.appendChild(clas);
        box.appendChild(plac);
        box.appendChild(goThere);
    }
    else if(type===3)
    {
        ndi.style.backgroundColor='#4784F4';
        var name=document.createElement("p");
        name.innerHTML=info[3];
        var plac=document.createElement("p");
        plac.innerHTML="活动地点："+writePlace(Number(info[4]));

        var lop=document.createElement("p");
        // console.log(info[5][0]);
        if(info[5][0]==='1')
            lop.innerHTML="周期：单次";
        else if(info[5][0]==='2')
            lop.innerHTML="周期：每天";
        else if(info[5][0]==='3')
            lop.innerHTML="周期：每周";
        // console.log(lop);

        box.appendChild(name);
        box.appendChild(plac);
        box.appendChild(lop);
        box.appendChild(goThere);
        box.appendChild(delAct);
        box.appendChild(createAlarm);

        ndi.ondblclick = function() {
            modifyAct(ntd,info[3],info[4],info[5][0],info);
        }
    }
    else if(type===2)
    {
        ndi.style.backgroundColor='#F8F55D';
        var classes=document.createElement("p");
        classes.innerHTML="参与班级："+info[3];
        var name=document.createElement("p");
        name.innerHTML=info[4];
        var plac=document.createElement("p");
        plac.innerHTML="活动地点："+writePlace(Number(info[5]));

        var lop=document.createElement("p");
        if(info[6][0]==='1')
            lop.innerHTML="周期：单次";
        else if(info[6][0]==='2')
            lop.innerHTML="周期：每天";
        else if(info[6][0]==='3')
            lop.innerHTML="周期：每周";

        box.appendChild(name);
        box.appendChild(classes);
        box.appendChild(plac);
        box.appendChild(lop);
        box.appendChild(goThere);
        box.appendChild(delAct);
        box.appendChild(createAlarm);

        ndi.ondblclick = function() {
            modifyGro(ntd,info[4],info[5],info[6][0],info);
        }
    }
    else if(type===4)
    {
        ndi.style.backgroundColor='#98F447';
        var num=Number(info[3]);
        var Num=document.createElement("p");
        Num.innerHTML="事务数量："+num;
        Num.id='Num';
        box.appendChild(Num);
        
        var now=4;
        for(var i=1;i<=num;i++)
        {
            var name=document.createElement("p");
            name.innerHTML=info[now]+"-"+writePlace(Number(info[now+1]));
            now+=2;
            box.appendChild(name);
        }

        box.appendChild(goThere);
        box.appendChild(delAct);
        box.appendChild(createAlarm);

        ndi.ondblclick = function() {
            modifyEve(ntd,info);
        }
    }

    ndi.onmouseover = function() {
        goThere.style.display='block';
        delAct.style.display='block';
        createAlarm.style.display='block';
    }
    ndi.onmouseout = function() {
        goThere.style.display='none';
        delAct.style.display='none';
        createAlarm.style.display='none';
    }
    
    ndi.appendChild(box);
    ntd.appendChild(ndi);
    bl.appendChild(ntd);
}//加入活动方格

function goSingle(info,type) {
    cit[2].click();
    while(middlePointsNum>0)
    {
        var delbut=document.getElementById('delPoint');
        delbut.click();
    }
    var endPoint=document.getElementById('endPoint');
    if(type===1 || type===2)
        endPoint.selectedIndex=Number(info[5]);
    else
        endPoint.selectedIndex=Number(info[4]);
}//单活动跳转至导航

function goMultiple(info) {
    cit[2].click();
    while(middlePointsNum>0)
    {
        var delbut=document.getElementById('delPoint');
        delbut.click();
    }
    var endPoint = document.getElementById('endPoint');
    endPoint.selectedIndex = 0;
    var num=Number(info[3]);
    var now=5;

    var newbut=document.getElementById('buildNewPoint');
    for(var i=1;i<=num;i++)
    {
        newbut.click();
        var newP=document.querySelectorAll('#middlePoint')[i-1];
        newP.selectedIndex=Number(info[now]);
        now=now+2;
    }
}//多活动跳转至导航

function buildNew(obj) {
    addAct.style.display='block';
    var head=document.getElementsByTagName('h1')[0];
    head.innerHTML="添加新的日程";

    document.querySelectorAll('.radio').forEach(el=>{
        el.disabled=false;
    })
    var indAct=document.getElementById('indAct');
    indAct.click();

    var startDate=document.getElementById('newActdate');
    var startTime=document.getElementById('startTime');
    var s=obj.id.split("&");
    startDate.value='2023-'+s[0];
    startTime.value=Number(s[1])-1;

    var comp=document.getElementById('comp');
    comp.onclick = function() {
        addActivity();
    }
    actSection.style.display='block';
    alarmSection.style.display='none';
}//添加新的日程

function addActivity() {
    var newActdate=document.getElementById('newActdate').value;
    var startTime=document.getElementById('startTime').value;
    if(startTime < 6 || startTime > 21)
    {
        warning("活动时间超出有效范围");
        return ;
    }
    var exeTime=dateHour2exe(newActdate,startTime);

    var nowWeek=selectdom.selectedIndex+1;
    var page01 = document.getElementById('page01');
    console.log(page01.scrollTop);
    
    var indAct=document.getElementById('indAct');
    var groAct=document.getElementById('groAct');
    var indEve=document.getElementById('indEve');
    var type=0;
    var lop=0;
    var para=document.createElement("a");

    if(indAct.checked===true)
    {
        type=3;

        var onTime=document.getElementById('onTime');
        var oneDay=document.getElementById('oneDay');
        var oneWeek=document.getElementById('oneWeek');
        if(onTime.checked===true)
        {
            lop=1;
            var Actname=document.getElementById('Actname').value;
            if(Actname === "")
            {
                warning("活动名称不能为空");
                return ;
            }
            var Actplac=document.getElementById('Actplac').selectedIndex;
            if(Actplac === 0)
            {
                warning("活动地点不能为空");
                return ;
            }

            para.href='closeexe://&&2&&' + nowWeek + '&&' + calen.value + '&&' + nowTime.getTime() + '&&' + page01.scrollTop
                                + '&&' + type + '&&' + lop
                                + '&&' + exeTime + '&&' + Actname + '&&' + Actplac;
            para.click();
        }
        else if(oneDay.checked===true)
        {
            lop=2;
            var Actname=document.getElementById('Actname').value;
            if(Actname === "")
            {
                warning("活动名称不能为空");
                return ;
            }
            var Actplac=document.getElementById('Actplac').selectedIndex;
            if(Actplac === 0)
            {
                warning("活动地点不能为空");
                return ;
            }
            var endDate=document.getElementById('endDate').value;
            var endExeTime=Number(dateHour2exe(endDate,startTime)+1);

            para.href='closeexe://&&2&&' + nowWeek + '&&' + calen.value + '&&' + nowTime.getTime() + '&&' + page01.scrollTop
                                + '&&' + type + '&&' + lop
                                + '&&' + exeTime + '&&' + endExeTime + '&&' + Actname + '&&' + Actplac;
            para.click();
        }
        else if(oneWeek.checked===true)
        {
            lop=3;
            var Actname=document.getElementById('Actname').value;
            if(Actname === "")
            {
                warning("活动名称不能为空");
                return ;
            }
            var Actplac=document.getElementById('Actplac').selectedIndex;
            var endDate=document.getElementById('endDate').value;
            var endExeTime=dateHour2exe(endDate,startTime)+1;
            if(Actplac === 0)
            {
                warning("活动地点不能为空");
                return ;
            }
            para.href='closeexe://&&2&&' + nowWeek + '&&' + calen.value + '&&' + nowTime.getTime() + '&&' + page01.scrollTop
                                + '&&' + type + '&&' + lop
                                + '&&' + exeTime + '&&' + endExeTime + '&&' + Actname + '&&' + Actplac;
            para.click();
            // console.log(Actname);
            // console.log(para.href);
        }
    }
        
    else if(groAct.checked===true)
    {
        type=2;
        var Actname=document.getElementById('Actname').value;
        if(Actname === "")
        {
            warning("活动名称不能为空");
            return ;
        }
        var Actplac=document.getElementById('Actplac').selectedIndex;
        if(Actplac === 0)
        {
            warning("活动地点不能为空");
            return ;
        }

        para.href='closeexe://&&2&&' + nowWeek + '&&' + calen.value + '&&' + nowTime.getTime() + '&&' + page01.scrollTop
                                + '&&' + type
                                + '&&' + exeTime + '&&' + Actname + '&&' + Actplac;
        para.click();
    }
        
    else if(indEve.checked===true)
    {
        type=4;
        if(num === 0)
        {
            warning("事务信息不能为空");
            return ;
        }
        para.href='closeexe://&&2&&' + nowWeek + '&&' + calen.value + '&&' + nowTime.getTime() + '&&' + page01.scrollTop
                                + '&&' + type + '&&' + num;
        
        for(var i=1;i<=num;i++)
        {
            var newName=document.getElementById('name'+i).value;
            if(newName === "")
            {
                warning("活动名称不能为空");
                return ;
            }
            var newPlac=document.getElementById('plac'+i).selectedIndex;
            if(newPlac === 0)
            {
                warning("活动地点不能为空");
                return ;
            }
            para.href += '&&' + exeTime + '&&' + newName + '&&' + newPlac;
        }
        para.click();
    }
        
    rec();
}

function delActicity(info) {
    var nowWeek=selectdom.selectedIndex+1;
    var page01 = document.getElementById('page01');

    var type = Number(info[0]);
    var para = document.createElement("a");
    var startTime = Number(info[1]);
    if(type === 2 || type === 3)
    {
        para.href='closeexe://&&3&&' + nowWeek + '&&' + calen.value + '&&' + nowTime.getTime() + '&&' + page01.scrollTop
                                + '&&' + type + '&&' + startTime;
        para.click();
        // console.log(para.href);
    }
    else
    {
        var num = Number(info[3]);
        para.href='closeexe://&&3&&' + nowWeek + '&&' + calen.value + '&&' + nowTime.getTime() + '&&' + page01.scrollTop
                                + '&&' + type + '&&' + num;
        var now = 4;

        for(var i=1;i<=num;i++)
        {
            para.href += '&&' + startTime + '&&' + info[now];
            now+=2;
        }
        para.href += '&&' + '0';
        para.click();
        // console.log(para.href);
    }
}

function modifyActivity(info) {
    var newActdate=document.getElementById('newActdate').value;
    var startTime=document.getElementById('startTime').value;
    if(startTime < 6 || startTime > 21)
    {
        warning("活动时间超出有效范围");
        return ;
    }
    var exeTime=dateHour2exe(newActdate,startTime);

    var nowWeek=selectdom.selectedIndex+1;
    var page01=document.getElementById('page01');
    
    var type=0;
    var lop=0;

    var type = Number(info[0]);
    var para = document.createElement("a");
    var oldStartTime = Number(info[1]);
    if(type === 3)
    {
        para.href = 'closeexe://&&4&&' + nowWeek + '&&' + calen.value + '&&' + nowTime.getTime() + '&&' + page01.scrollTop
                                + '&&' + type + '&&' + oldStartTime;

        var onTime=document.getElementById('onTime');
        var oneDay=document.getElementById('oneDay');
        var oneWeek=document.getElementById('oneWeek');
        if(onTime.checked === true)
        {
            lop = 1;
            var Actname=document.getElementById('Actname').value;
            if(Actname === "")
            {
                warning("活动名称不能为空");
                return ;
            }
            var Actplac=document.getElementById('Actplac').selectedIndex;
            if(Actplac === 0)
            {
                warning("活动地点不能为空");
            }
            para.href += '&&' + lop + '&&' + exeTime + '&&' + Actname + '&&' + Actplac;
            para.click();
            // console.log(para.href);
        }
        else if(oneDay.checked === true)
        {
            
            lop = 2;
            var Actname=document.getElementById('Actname').value;
            if(Actname === "")
            {
                warning("活动名称不能为空");
                return ;
            }
            var Actplac=document.getElementById('Actplac').selectedIndex;
            if(Actplac === 0)
            {
                warning("活动地点不能为空");
            }
            var endDate=document.getElementById('endDate').value;
            var endExeTime=Number(dateHour2exe(endDate,startTime)+1);

            para.href += '&&' + lop + '&&' + exeTime + '&&' + endExeTime + '&&' + Actname + '&&' + Actplac;
            para.click();
            // console.log(para.href);
        }
        else if(oneWeek.checked === true)
        {
            lop = 3;
            var Actname=document.getElementById('Actname').value;
            if(Actname === "")
            {
                warning("活动名称不能为空");
                return ;
            }
            var Actplac=document.getElementById('Actplac').selectedIndex;
            if(Actplac === 0)
            {
                warning("活动地点不能为空");
            }
            var endDate=document.getElementById('endDate').value;
            var endExeTime=Number(dateHour2exe(endDate,startTime)+1);

            para.href += '&&' + lop + '&&' + exeTime + '&&' + endExeTime + '&&' + Actname + '&&' + Actplac;
            para.click();
            // console.log(para.href);
        }
    }
    else if(type === 2)
    {
        para.href = 'closeexe://&&4&&' + nowWeek + '&&' + calen.value + '&&' + nowTime.getTime() + '&&' + page01.scrollTop
                                + '&&' + type + '&&' + oldStartTime;

        var Actname=document.getElementById('Actname').value;
        if(Actname === "")
        {
            warning("活动名称不能为空");
            return ;
        }
        var Actplac=document.getElementById('Actplac').selectedIndex;
        if(Actplac === 0)
        {
            warning("活动地点不能为空");
        }
        para.href += '&&' + exeTime + '&&' + Actname + '&&' + Actplac;
        para.click();
        // console.log(para.href);
    }
    else if(type === 4)
    {
        para.href = 'closeexe://&&4&&' + nowWeek + '&&' + calen.value + '&&' + nowTime.getTime() + '&&' + page01.scrollTop
                                + '&&' + type;

        var oldNum = Number(info[3]);
        para.href += '&&' + oldNum;
        var now = 4;
        for(var i=1;i<=oldNum;i++)
        {
            para.href += '&&' + oldStartTime + '&&' + info[now];
            now+=2;
        }

        para.href += '&&' + num;
        if(num === 0)
        {
            warning("事务信息不能为空");
            return ;
        }
        for(var i=1;i<=num;i++)
        {
            var newName=document.getElementById('name'+i).value;
            if(newName === "")
            {
                warning("活动名称不能为空");
                return ;
            }
            var newPlac=document.getElementById('plac'+i).selectedIndex;
            if(newPlac === 0)
            {
                warning("活动地点不能为空");
                return ;
            }
            para.href += '&&' + exeTime + '&&' + newName + '&&' + newPlac;
        }
        para.click();
        // console.log(para.href);
    }
}

function searchActivity() {
    var searchName = document.getElementById('searchName').value;
    if(searchName === "")
    {
        warning("查询名称不能为空");
        return ;
    }
    var searchType = document.getElementById('searchType').value;
    var page01 = document.getElementById('page01');
    para = document.createElement("a");
    var nowWeek=selectdom.selectedIndex+1;
    para.href = 'closeexe://&&5&&' + nowWeek + '&&' + calen.value + '&&' + nowTime.getTime() + '&&' + page01.scrollTop
                                + '&&' + searchType + '&&' + searchName + '&&' + jsHour2exe();
    para.click();
}

function compAct() {
    rec();
}

function Canc() {
    rec();
}

function compAlarm() {
    rec();
}

function rec() {
    while(num>1)
    {
        var tmpid='name'+num;
        var tmp=document.getElementById(tmpid);
        del(tmp);
    }
    addAct.style.display='none';
    
}

function modifyAct(obj,name,plac,lop,info) {
    var s=obj.id.split('&');

    addAct.style.display='block';
    var head=document.getElementsByTagName('h1')[0];
    var comp=document.getElementById('comp');
    comp.onclick = function() {
        modifyActivity(info);
    }
    actSection.style.display='block';
    alarmSection.style.display='none';
    head.innerHTML="修改日程";

    document.querySelectorAll('.radio').forEach(el=>{
        el.disabled=false;
    })

    var newname=document.getElementById('Actname');
    var newplac=document.getElementById('Actplac');
    newname.value=name;
    newplac.selectedIndex=Number(plac);

    var startDate=document.getElementById('newActdate');
    var startTime=document.getElementById('startTime');
    var s=obj.id.split("&");
    startDate.value='2023-'+s[1];
    startTime.value=Number(s[2]);

    var indAct=document.getElementById('indAct');
    indAct.click();

    var onTime=document.getElementById('onTime');
    var oneDay=document.getElementById('oneDay');
    var oneWeek=document.getElementById('oneWeek');


    if(lop[0]==='1')
        onTime.click();
    else if(lop[0]==='2')
        oneDay.click();
    else if(lop[0]==='3')
        oneWeek.click();

    document.querySelectorAll('.radio').forEach(el=>{
        el.disabled=true;
    })
}//修改个人活动

function modifyGro(obj,name,plac,lop,info) {
    var s=obj.id.split('&');

    addAct.style.display='block';
    var head=document.getElementsByTagName('h1')[0];
    head.innerHTML="修改日程";

    var comp=document.getElementById('comp');
    comp.onclick = function() {
        modifyActivity(info);
    }
    actSection.style.display='block';
    alarmSection.style.display='none';

    document.querySelectorAll('.radio').forEach(el=>{
        el.disabled=false;
    })

    var newname=document.getElementById('Actname');
    var newplac=document.getElementById('Actplac');
    newname.value=name;
    newplac.selectedIndex=Number(plac);

    var startDate=document.getElementById('newActdate');
    var startTime=document.getElementById('startTime');
    var s=obj.id.split("&");
    console.log(s[0]);
    startDate.value='2023-'+s[1];
    startTime.value=Number(s[2]);

    var groAct=document.getElementById('groAct');
    groAct.click();

    var onTime=document.getElementById('onTime');
    var oneDay=document.getElementById('oneDay');
    var oneWeek=document.getElementById('oneWeek');


    console.log(lop);
    if(lop[0]==='1')
        onTime.click();
    else if(lop[0]==='2')
        oneDay.click();
    else if(lop[0]==='3')
        oneWeek.click();

    document.querySelectorAll('.radio').forEach(el=>{
        el.disabled=true;
    })
}//修改集体活动

function modifyEve(obj,info) {
    var s=obj.id.split('&');

    addAct.style.display='block';
    var head=document.getElementsByTagName('h1')[0];
    head.innerHTML="修改日程";

    var comp=document.getElementById('comp');
    comp.onclick = function() {
        modifyActivity(info);
    }
    actSection.style.display='block';
    alarmSection.style.display='none';

    document.querySelectorAll('.radio').forEach(el=>{
        el.disabled=false;
    })

    var startDate=document.getElementById('newActdate');
    var startTime=document.getElementById('startTime');
    var s=obj.id.split("&");
    console.log(s[0]);
    startDate.value='2023-'+s[1];
    startTime.value=Number(s[2]);

    var indEve=document.getElementById('indEve');
    indEve.click();

    var name1=document.getElementById('name1');
    var plac1=document.getElementById('plac1');
    name1.value=info[4];
    plac1.selectedIndex=Number(info[5]);

    var build=document.getElementById('build');
    var num=Number(info[3]);
    var now=6;
    for(var i=2;i<=num;i++)
    {
        build.click();
        var newnameid='name'+i;
        var newplacid='plac'+i;
        var newname=document.getElementById(newnameid);
        var newplac=document.getElementById(newplacid);

        newname.value=info[now];
        newplac.selectedIndex=Number(info[now+1]);

        now+=2;
    }
    document.querySelectorAll('.radio').forEach(el=>{
        el.disabled=true;
    })
}//修改临时事务

function gener(obj) {

    if(obj.value==="indAct")
    {  
        addpage01.style.display='block';
        addpage02.style.display='none';
    }
    else if(obj.value==="groAct")
    {
        addpage01.style.display='block';
        addpage02.style.display='none';
    }
    else
    {
        addpage01.style.display='none';
        addpage02.style.display='block';
    }
}//日程信息表页面切换

function quizTime(obj) {
    if(obj.value==="onTime" || alarmSection.style.display==="block")
        quizTim.style.display='none';
    else 
    {
        update();
        quizTim.style.display='block';
    }
}//日程信息表截止日期栏

function update() {
    endDate.min=startDate.value;
    endDate.value=endDate.min;
}//日程信息表截止日期与起始日期同步

function Build() {
    num++;
    totNum.innerHTML="总数: "+num;

    var newp=document.createElement('p');
    var nsp=document.createElement('span');
    nsp.innerHTML='活动名称：';
    var nsp2=document.createElement('span');
    nsp2.innerHTML='活动地点：';

    var nname=document.createElement('input');
    nname.type='text';
    nname.className='eveNameLists';
    // console.log(nname.class);
    nname.id='name'+num;

    var nplac=document.createElement('select');
    addOption(nplac);
    nplac.className='evePlacLists';
    nplac.id='plac'+num;

    var but_del=document.createElement('button');
    but_del.innerHTML='删除';
    but_del.type='button';
    but_del.onclick=function() {
        del(but_del);
    }

    newp.appendChild(nsp);
    newp.appendChild(nname);
    newp.appendChild(nsp2);
    newp.appendChild(nplac);
    newp.appendChild(but_del);
    addpage02.appendChild(newp);
}//日程信息表添加多个临时事务

function del(obj) {
    num--;
    totNum.innerHTML="总数: "+num;
    var tmp=obj.parentNode;
    addpage02.removeChild(tmp);

    if(num>0)
    {
        var nname=document.getElementsByClassName('eveNameLists');
        console.log(nname);
        for(var i=1;i<=num;i++)
            nname[i-1].id='name'+i;

        var nplac=document.getElementsByClassName('evePlacLists');
        console.log(nplac);
        for(var i=1;i<=num;i++)
            nplac[i-1].id='plac'+i;
    }
}//日程信息表删除多个临时事务


function addAlarm(info,type) {
    addAct.style.display='block';
    var head=document.getElementsByTagName('h1')[0];
    head.innerHTML="添加新的闹钟";

    document.querySelectorAll('.radio').forEach(el=>{
        el.disabled=false;
    })

    // var newAlarmDate=document.getElementById('newAlarmDate');
    var alarmTime=document.getElementById('alarmTime');
    var actTime=document.getElementById('actTime');

    // newAlarmDate.value=getDate();
    alarmTime.value=(Number(info[1])-1)%24;
    alarmTime.max=(Number(info[1])-1)%24;
    actTime.innerHTML="活动时间："+(Number(info[1])%24);

    var comp=document.getElementById('comp');
    comp.onclick = function() {
        compAddAlarm(info,type);
    }
    actSection.style.display='none';
    alarmSection.style.display='block';
}//添加新的闹钟

function compAddAlarm(info,type) {
    var nowWeek=selectdom.selectedIndex+1;
    var alarmTime=document.getElementById('alarmTime').value;
    var actTime=Number(info[1]);
    if(alarmTime >= actTime%24)
    {
        warning("闹钟时间必须小于活动时间");
        return ;
    }
    alarmTime = actTime - (actTime%24-alarmTime);

    var para = document.createElement("a");
    para.href = para.href = 'closeexe://&&8&&' + nowWeek + '&&' + calen.value + '&&' + nowTime.getTime() + '&&' + alarmTime + '&&' + type + '&&' + actTime;
    if(type === 3)
        para.href += '&&' + info[5][0];
    else para.href += '&&' + '1';

    para.click();
}

function initAlarm() {
    var alarmInfo=document.getElementById('alarmInfo');
    var alarms=load("../datas/alarms.txt");
    alarms=alarms.split("\r").join("");
    alarms=alarms.split("\n");
    // console.log(alarms);
    var k = 0;
    console.log(alarms[2]);
    while(alarms[k] != "")
    {
        console.log(k);
        
        var info=alarms[k].split(" ");
        // console.log(info);
        var newtr=document.createElement("tr");
        
        var type=document.createElement("td");
        info[1]=Number(info[1]);
        if(info[1]===3)
            type.innerHTML="个人活动";
        else if(info[1]===2)
            type.innerHTML="集体活动";
        else if(info[1]===4)
            type.innerHTML="临时事务";
        newtr.appendChild(type);

        var alarmTime = document.createElement("td");
        alarmTime.innerHTML = Number(info[0])%24 + ':00';
        newtr.appendChild(alarmTime);

        var actTime = document.createElement("td");
        var sTime = Number(info[2])%24;
        var eTime = Number(info[3])%24;
        actTime.innerHTML = sTime + ':00 ~ ' + eTime + ':00';
        newtr.appendChild(actTime);

        var date = document.createElement("td");
        date.innerHTML = exeHour2Date(Number(info[0]));
        newtr.appendChild(date);

        var tdlop = document.createElement("td");
        var lop = 0;
        if(info[1] === 2)
            lop = Number(info[7]);
        else if(info[1] === 3)
            lop = Number(info[6]);
        if(lop === 0)
            tdlop.innerHTML = '-';
        else if(lop === 1)
            tdlop.innerHTML = "单次";
        else if(lop === 2)
            tdlop.innerHTML = "每天";
        else
            tdlop.innerHTML = "每周";
        newtr.appendChild(tdlop);

        var tdName = document.createElement("td");
        var tdPlac = document.createElement("td");
        var tdClas = document.createElement("td");
        if(info[1] === 2 || info[1] === 3)
        {
            tdName.innerHTML = info[4];
            tdPlac.innerHTML = writePlace(Number(info[5]));
        }
        if(info[1] === 2)
            tdClas.innerHTML = info[6];
        else
            tdClas.innerHTML = '-';
        if(info[1] === 4)
        {
            tdName.innerHTML = "";
            tdPlac.innerHTML = "";
            var num = Number(info[4]);
            var now = 5;
            for(var i=1;i<=num;i++)
            {
                var newp1 = document.createElement("p");
                newp1.innerHTML = info[now];
                var newp2 = document.createElement("p");
                newp2.innerHTML = writePlace(info[now+1]);
                tdName.appendChild(newp1);
                tdPlac.appendChild(newp2);
                now += 2;
            }
        }
        newtr.appendChild(tdName);
        newtr.appendChild(tdPlac);
        newtr.appendChild(tdClas);
        
        var delbut=document.createElement("button");
        delbut.type="button";
        delbut.onclick=function() {
            delAlarm(Number(info[0]),date.innerHTML);
        }
        delbut.innerHTML="删除";

        var modifybut=document.createElement("button");
        modifybut.type="button";
        modifybut.id=info.join("&");
        modifybut.onclick=function() {
            modifyAlarm(this.id,lop);
        }
        modifybut.innerHTML="修改";

        var ops=document.createElement("td");
        ops.appendChild(delbut);
        ops.appendChild(modifybut);
        newtr.appendChild(ops);

        alarmInfo.appendChild(newtr);
        k++;
    }
}//初始化闹钟列表

function delAlarm(time,date) {
    var nowWeek=selectdom.selectedIndex+1;
    var para=document.createElement("a");
    para.href = 'closeexe://&&9&&' + nowWeek + '&&' + calen.value + '&&' + nowTime.getTime() + '&&' + dateHour2exe(date,time);
    para.click();
}//删除闹钟

function modifyAlarm(info,lop) {
    info=info.split("&");

    addAct.style.display='block';
    var head=document.getElementsByTagName('h1')[0];
    head.innerHTML="修改闹钟";

    document.querySelectorAll('.radio').forEach(el=>{
        el.disabled=false;
    })
    // var newAlarmDate=document.getElementById('newAlarmDate');
    var alarmTime=document.getElementById('alarmTime');
    var actTime=document.getElementById('actTime');
    // newAlarmDate.value=info[2];
    alarmTime.value=Number(info[0])%24;
    actTime.innerHTML="活动时间："+(Number(info[2])%24);

    var comp=document.getElementById('comp');
    comp.onclick = function() {
        compModifyAlarm(info,lop);
    }
    actSection.style.display='none';
    alarmSection.style.display='block';
}

function compModifyAlarm(info,lop) {
    var para = document.createElement("a");
    var nowWeek=selectdom.selectedIndex+1;
    para.href = para.href = 'closeexe://&&10&&' + nowWeek + '&&' + calen.value + '&&' + nowTime.getTime();

    var alarmTime=document.getElementById('alarmTime').value;
    var actTime=Number(info[2]);
    alarmTime = actTime - (actTime%24-alarmTime);
    if(alarmTime >= actTime%24)
    {
        warning("闹钟时间必须小于活动时间");
        return ;
    }

    para.href += '&&' + info[0] + '&&' + alarmTime + '&&' + Number(info[1]) + '&&' + actTime;
    if(lop === 0)
        lop = 1;
    para.href += '&&' + lop;
    para.click();
}

function closePAT() {
    var PAT=document.getElementById('personalAlarmTip');
    PAT.style.display = 'none';
    timeSet(1);
}
function closeTAT() {
    var TAT=document.getElementById('tempAlarmTip');
    TAT.style.display = 'none';
    timeSet(1);
}
function closeSAT() {
    var SAT=document.getElementById('systemAlarmTip');
    SAT.style.display = 'none';
    timeSet(1);
}

function checkPAT() {
    var PA = load("../datas/personalAlarm.txt");
    PA = PA.split("\r").join("");
    PA = PA.split("\n");
    if(PA[0] === '1')
    {
        timeSet(0);
        var info = PA[1].split(" ");
        var PAT = document.getElementById('personalAlarmTip');
        PAT.style.display = 'block';

        var PAtype = document.getElementById('PAtype');
        var PAname = document.getElementById('PAname');
        var PAtime = document.getElementById('PAtime');
        var PAplac = document.getElementById('PAplac');
        var PAbutton = document.getElementById('PAbutton');

        if(info[0] === '2')
        {
            var name = info[3];
            var sTime = Number(info[1])%24;
            var eTime = Number(info[2])%24;
            var plac = Number(info[4]);

            PAtype.innerHTML = "日程类型：集体活动";
            PAname.innerHTML = '名称：' + name;
            PAtime.innerHTML = '时间：' + sTime + ':00 ~ ' + eTime + ':00';
            PAplac.innerHTML = '地点：' + writePlace(plac);
            PAbutton.onclick = function() {
                tipSingleWay(plac,PAT);
            }
        }
        else if(info[0] === '3')
        {
            var name = info[3];
            var sTime = Number(info[1])%24;
            var eTime = Number(info[2])%24;
            var plac = Number(info[4]);

            PAtype.innerHTML = "日程类型：个人活动";
            PAname.innerHTML = '名称：' + name;
            PAtime.innerHTML = '时间：' + sTime + ':00 ~ ' + eTime + ':00';
            PAplac.innerHTML = '地点：' + writePlace(plac);
            PAbutton.onclick = function() {
                tipSingleWay(plac,PAT);
            }
        }
        else
        {
            var sTime = Number(info[1])%24;
            var eTime = Number(info[2])%24;
            PAtype.innerHTML = "日程类型：临时事务";
            PAtime.innerHTML = '时间：' + sTime + ':00 ~ ' + eTime + ':00';

            var num = Number(info[3]);
            var now = 6;
            var name = info[4];
            var plac = writePlace(info[5]);
            for(var i=2;i<=num;i++)
            {
                name += '，' + info[now];
                plac += '，' + writePlace(info[now+1]);
                now += 2;
            }
            PAname.innerHTML = '名称：' + name;
            PAplac.innerHTML = '地点：' + plac;
            PAbutton.onclick = function() {
                tipMultiWay(info,PAT);
            }
        }
    }
}

function checkTAT() {
    var TA = load("../datas/tempAlarm.txt");
    TA = TA.split("\r").join("");
    TA = TA.split("\n");
    if(TA[0] === '1')
    {
        timeSet(0);
        var info = TA[1].split(" ");
        var TAT = document.getElementById('tempAlarmTip');
        TAT.style.display = 'block';

        var TAname = document.getElementById('TAname');
        var TAtime = document.getElementById('TAtime');
        var TAplac = document.getElementById('TAplac');
        var TAclas = document.getElementById('TAclas');
        var TAbutton = document.getElementById('TAbutton');

        var sTime = Number(info[1])%24;
        var eTime = Number(info[2])%24;
        var name = info[3];
        var clas = info[4];
        var plac = Number(info[5]);

        TAname.innerHTML = '课程名称：' + name;
        TAtime.innerHTML = '上课时间：' + sTime + ':00 ~ ' + eTime + ':00';
        TAplac.innerHTML = '上课地点：' + writePlace(plac);
        TAclas.innerHTML = '上课班级：' + clas;
        TAbutton.onclick = function() {
            tipSingleWay(plac,TAT);
        }
    }
}

function checkSAT() {
    
    var SA = load("../datas/systemAlarm.txt");
    SA = SA.split("\r").join("");
    SA = SA.split("\n");
    if(SA[0] === '1')
    {
        timeSet(0);
        var SAT = document.getElementById('systemAlarmTip');
        SAT.style.display = 'block';

        var SAtable = document.getElementById('SAtable');
        var oldtrs = SAtable.getElementsByTagName("tr");
        for(var i=1;i<=SANum;i++)
            SAtable.removeChild(oldtrs[i]);
        var num = Number(SA[1]);
        SANum = num;
        for(var i=1;i<=num;i++)
        {
            var info = SA[i+1].split(" ");
            var tr = document.createElement("tr");

            var tdType = document.createElement("td");
            var type = info[0];
            if(type === '1')
                tdType.innerHTML = "课程";
            else if(type === '2')
                tdType.innerHTML = "集体活动";
            else if(type === '3')
                tdType.innerHTML = "个人活动";
            
            var sTime = Number(info[1])%24;
            var eTime = Number(info[2])%24;
            var tdTime = document.createElement("td");
            tdTime.innerHTML = sTime + ':00 ~ ' + eTime + ':00';

            var tdName = document.createElement("td");
            var name = info[3];
            tdName.innerHTML = name;

            var tdPlac = document.createElement("td");
            var plac = writePlace(Number(info[4]));
            tdPlac.innerHTML = plac;

            var tdClas = document.createElement("td");
            if(type === '1' || type === '2')
            {
                var clas = info[5];
                tdClas.innerHTML = clas;
            }
            else
                tdClas.innerHTML = '-';
            
            tr.appendChild(tdType);
            tr.appendChild(tdTime);
            tr.appendChild(tdPlac);
            tr.appendChild(tdName);
            tr.appendChild(tdClas);
            SAtable.append(tr);
        }
    }
}

function tipSingleWay(plac,XAT) {
    XAT.style.display = 'none';
    cit[2].click();
    while(middlePointsNum>0)
    {
        var delbut=document.getElementById('delPoint');
        delbut.click();
    }
    var endPoint=document.getElementById('endPoint');
    endPoint.selectedIndex = Number(plac);
}

function tipMultiWay(info,XAT) {
    XAT.style.display = 'none';
    cit[2].click();
    while(middlePointsNum>0)
    {
        var delbut=document.getElementById('delPoint');
        delbut.click();
    }
    var endPoint = document.getElementById('endPoint');
    endPoint.selectedIndex = 0;
    var num=Number(info[3]);
    var now=5;

    var newbut=document.getElementById('buildNewPoint');
    for(var i=1;i<=num;i++)
    {
        newbut.click();
        var newP=document.querySelectorAll('#middlePoint')[i-1];
        newP.selectedIndex=Number(info[now]);
        now=now+2;
    }
}

function closeTips() {
    tips.style.display='none';
}


function newPoint() {
    var middlePoints=document.getElementById('middlePoints');
    middlePointsNum++;

    var newp=document.createElement("p");
    var nsp=document.createElement("span");
    nsp.id="mpSpan";
    nsp.innerHTML='途经点'+middlePointsNum+': ';

    var nPoint=document.createElement("select");
    addOption(nPoint);
    nPoint.id="middlePoint";

    var ndel=document.createElement("button");
    ndel.type="button";
    ndel.innerHTML="删除";
    ndel.id="delPoint";
    ndel.onclick=function() {
        delPoint(newp);
    }

    newp.appendChild(nsp);
    newp.appendChild(nPoint);
    newp.appendChild(ndel);
    middlePoints.appendChild(newp);
}//添加新的途经点

function delPoint(newp) {
    middlePointsNum--;

    var tmp=newp.parentNode;
    tmp.removeChild(newp);

    if(middlePointsNum>0)
    {
        var spans=document.querySelectorAll('#mpSpan');
        for(var i=1;i<=middlePointsNum;i++)
            spans[i-1].innerHTML="途径点"+i+': ';
    }
}//删除途经点

function initCanvas() {
    var w=canvas.width;
    var h=canvas.height;
    ctx.clearRect(0,0,w,h);
    // drawImg();
}//清空画布

function startFindWay() {
    var startPoint = document.getElementById('startPoint').selectedIndex;
    var endPoint = document.getElementById('endPoint').selectedIndex;
    if(startPoint === 0)
    {
        warning("起点不能为空");
        return ;
    }
    if(endPoint === 0 && middlePointsNum === 0)
    {
        warning("终点不能为空");
        return ;
    }
    var para = document.createElement("a");
    var nowWeek=selectdom.selectedIndex+1;
    if(endPoint != 0)
    {
        para.href = 'closeexe://&&6&&' + nowWeek + '&&' + calen.value + '&&' + nowTime.getTime();
        para.href += '&&' + startPoint + '&&' + endPoint;
        para.click();
    }
    else
    {
        para.href = 'closeexe://&&7&&' + nowWeek + '&&' + calen.value + '&&' + nowTime.getTime();
        para.href += '&&' + (middlePointsNum+1) + '&&' + startPoint;
        var middlePoints = document.querySelectorAll('#middlePoint');
        if(middlePointsNum > 18)
        {
            warning("途径点数量超出上限");
            return ;
        }
        for(var i=0;i<middlePointsNum;i++)
        {
            if(middlePoints[i].selectedIndex === 0)
            {
                warning("途径点不能为空");
                return ;
            }
            para.href += '&&' + middlePoints[i].selectedIndex;
        }
        para.click();
    }
}//开始寻路

function drawWay() {
    // var text=load("./coodinates.txt");
    // var s=text.split("\n");
    // for(var i=0;i<=119;i++)
    // {
    //     var info=s[i].split(" ");
    //     var X=Number(info[1]),Y=Number(info[2]);
    //     console.log(X),console.log(Y);
    //     var ball = new Ball(X,Y,0,0,'red',4);
    //     ball.draw();
    // }
    var s=load("../datas/road.txt");
    s.split("\r").join("");
    var road=s.split("\n");
    var cnt=Number(road[0]);
    // console.log(cnt);
    var points=road[1].split(" ");

    
    for(var i=0;i<cnt;i++)
    {
        var ind=Number(points[i]);
        var info=coodinates[ind-1].split(" ");
        var X=Number(info[1]);
        var Y=Number(info[2]);
        // console.log(ind);console.log(X);console.log(Y);
        balls[i]=new Ball(X,Y,0,0,'blue',5);
        balls[i].draw();
    }

    // ctx.strokeStyle='green';
    // ctx.lineWidth=2;
    // ctx.beginPath();
    // ctx.moveTo(balls[0].x,balls[0].y);
    for(var i=1;i<cnt;i++)
        drawArrow(ctx, balls[i-1].x, balls[i-1].y, balls[i].x, balls[i].y, 30, 10, 2, '#F4288E')
        // ctx.lineTo(balls[i].x,balls[i].y);
    // ctx.stroke();

    cnt=Number(road[2]);
    points=road[3].split(" ");

    for(var i=0;i<cnt;i++)
    {
        var ind=Number(points[i]);
        var info=coodinates[ind-1].split(" ");
        var X=Number(info[1]);
        var Y=Number(info[2]);
        // console.log(ind);console.log(X);console.log(Y);
        if(i === 0 || i === cnt-1)
            balls[i]=new Ball(X,Y,0,0,'yellow',5);
        else
            balls[i]=new Ball(X,Y,0,0,'red',5);
        balls[i].draw();
    }

    if(cnt === 2)
    {
        var startPoint = document.getElementById('startPoint');
        var endPoint = document.getElementById('endPoint');
        startPoint.selectedIndex = points[0];
        endPoint.selectedIndex = points[1];
    }
    else
    {
        var startPoint = document.getElementById('startPoint');
        startPoint.selectedIndex = points[0];
        var buildNewPoint = document.getElementById('buildNewPoint');
        for(var i=1;i<cnt-1;i++)
        {
            buildNewPoint.click();   
        }
        var nPoints = document.querySelectorAll('#middlePoint');
        for(var i=0;i<cnt-2;i++)
            nPoints[i].selectedIndex = points[i+1];
    }

    var shortest = road[4];
    var shortestLen = document.getElementById('shortestLen');
    shortestLen.innerHTML = '最短距离：' + shortest
}//绘制路径

function Ball(x,y,velX,velY,color,size) {
    this.x=x;
    this.y=y;
    this.velX=velX;
    this.velY=velY;
    this.color=color;
    this.size=size;
}

Ball.prototype.draw = function() {
    ctx.beginPath();
    ctx.fillStyle = this.color;
    ctx.arc(this.x,this.y,this.size,0,2*Math.PI);
    ctx.fill();
}

Ball.prototype.update = function() {
    this.x += this.velX;
    this.y += this.velY;
}


function drawArrow(ctx, fromX, fromY, toX, toY, theta, headlen, width, color) {
 
    theta = typeof(theta) != 'undefined' ? theta : 30;
    headlen = typeof(theta) != 'undefined' ? headlen : 10;
    width = typeof(width) != 'undefined' ? width : 1;
    color = typeof(color) != 'color' ? color : '#000';
 
    // 计算各角度和对应的P2,P3坐标
    var angle = Math.atan2(fromY - toY, fromX - toX) * 180 / Math.PI,
        angle1 = (angle + theta) * Math.PI / 180,
        angle2 = (angle - theta) * Math.PI / 180,
        topX = headlen * Math.cos(angle1),
        topY = headlen * Math.sin(angle1),
        botX = headlen * Math.cos(angle2),
        botY = headlen * Math.sin(angle2);
 
    ctx.save();
    ctx.beginPath();
 
    var arrowX = fromX - topX,
        arrowY = fromY - topY;
 
    ctx.moveTo(arrowX, arrowY);
    ctx.moveTo(fromX, fromY);
    ctx.lineTo(toX, toY);
    arrowX = toX + topX;
    arrowY = toY + topY;
    ctx.moveTo(arrowX, arrowY);
    ctx.lineTo(toX, toY);
    arrowX = toX + botX;
    arrowY = toY + botY;
    ctx.lineTo(arrowX, arrowY);
    ctx.strokeStyle = color;
    ctx.lineWidth = width;
    ctx.stroke();
    ctx.restore();
}

function initLog() {
    var i = 0;
    var page04 = document.getElementById("page04");
    while(log[i] != "")
    {
        var newp = document.createElement("p");
        newp.innerHTML = log[i];
        page04.append(newp);
        i++;
    }
}

function addOption(obj)
{
    for(var i=0;i<120;i++)
    {
        newOpt=document.createElement("option");
        newOpt.class = 'optionPoints';
        newOpt.innerHTML=num2plac[i];
        newOpt.value = i;
        obj.appendChild(newOpt);
    }
}//初始化地点选择器

function writePlace(ind)
{
    return num2plac[ind];
}//数字地点转中文

function getDate()
{
    var year=nowTime.getFullYear();
    var month=("0"+(nowTime.getMonth()+1)).slice(-2);
    var day=("0"+nowTime.getDate()).slice(-2);
    var mydate=year+'-'+month+'-'+day;
    return mydate;
}//现在时间转yyyy-mm-dd格式

function dateHour2exe(date,hour)
{
    var tmpdate=new Date(date);
    var oridate=new Date("2023-02-20");
    var basehour=(tmpdate.getTime()-oridate.getTime())/1000/60/60;
    var res=0;
    res = basehour + Number(hour);
    return res;
}

function jsHour2exe()
{
    var oridate=new Date("2023-02-20");
    return parseInt(parseInt(parseInt((nowTime.getTime() - oridate.getTime())/1000)/60)/60) + 8;
}
function exeHour2js(hour)
{
    var res="";
    res=(Number(hour)%24) + ':00 ~ ' + (Number(hour)%24+1) + ':00';
    return res;
}

function exeHour2Date(hour)
{
    var oridate = new Date("2023-02-20");
    var oriST = oridate.getTime();
    oriST=Number(oriST+hour*1000*60*60);
    var newDate = new Date(oriST);
    var year=newDate.getFullYear();
    var month=("0"+(newDate.getMonth()+1)).slice(-2);
    var day=("0"+newDate.getDate()).slice(-2);
    var mydate=year+'-'+month+'-'+day;
    return mydate;
}

function warning(content)
{
    var warningTip = document.getElementById('warningTip');
    var warningContent = document.getElementById('warningContent');
    warningTip.style.display = 'block';
    warningContent.innerHTML = content;
}

function closeWarn()
{
    var warningTip = document.getElementById('warningTip');
    warningTip.style.display = 'none';
}