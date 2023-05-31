var stu=document.querySelector('#stu');
var cou=document.querySelector('#cou');
var page01 = document.getElementById('page01');
var page02 = document.getElementById('page02');
var btnadd = document.getElementById('btnadd');
var selectdom = document.querySelector('select');
var calen = document.getElementById('date');
var couta = document.getElementById('coutable');
var tips = document.getElementById('tips');
var modifyStuForm = document.getElementById('modifyStudentForm');
var courseForm = document.getElementById('courseForm');
var addCourseButton = document.getElementById('addCourseButton');

var timeControler=document.querySelectorAll('div.chooseItem');
var nowTime=new Date();
var timeWalkPace=1000;

var num2plac=load("./num2placTable.txt");
num2plac=num2plac.split("\r").join("");
num2plac=num2plac.split("\n");

function initTime(domTime) {
    nowTime=new Date(domTime);
    timeBox.innerHTML=nowTime.toLocaleString();
}//初始化时间

document.querySelectorAll('select').forEach(el=>{
    if(el.id!="week" && el.id!="searchType")
        addOption(el);
})

function timeWalk() {
    var nowTimStamp=new Date(nowTime).getTime();
    nowTimStamp+=timeWalkPace;
    nowTime=new Date(nowTimStamp);
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
}//时间修改器的开启与关闭
btnadd.onclick = function() {
    var name=document.getElementById('name').value;
    // var number=document.getElementById('number').value;
    var clas=document.getElementById('class').value;
    var id=document.getElementById('stuid').value;

    var para = document.createElement("a");
    para.href = 'closeexe://&&1&&' + nowTime.getTime() + '&&1'
                            + '&&' + id + '&&' + name + '&&' + clas;
    para.click();
}

addCourseButton.onclick = function() {
    var courseTitle=document.getElementById('courseTitle');
    courseTitle.innerHTML="添加新的课程";
    courseForm.style.display='block';
    var compCourse=document.getElementById('compCourse');
    compCourse.onclick = function() {
        addCourse();
    }
}

function deltr(obj) {
    // var table=obj.parentNode.parentNode.parentNode;
    var tr=obj.parentNode.parentNode;
    // var name=tr.getElementsByTagName("td")[0];
    // var number=tr.getElementsByTagName("td")[1];
    // var clas=tr.getElementsByTagName("td")[2];
    var id=tr.getElementsByTagName("td")[3].innerText;

    var para = document.createElement("a");
    para.href = 'closeexe://&&2&&' + nowTime.getTime() + '&&' + id;
    para.click();
    // var tx0=td0.getElementsByTagName("Text");
    // console.log(tx0);
    // console.log(td0.innerText);
    // console.log(td1.innerText);
    // console.log(td2.innerText);
    // console.log(td3.innerText);
    // table.removeChild(tr);
    // td0.removeChild(child0);
}

function chatr(obj) {
    var tr=obj.parentNode.parentNode;
    var name=tr.getElementsByTagName("td")[0].innerText;
    // var number=tr.getElementsByTagName("td")[1].innerText;
    var clas=tr.getElementsByTagName("td")[2].innerText;
    var id=tr.getElementsByTagName("td")[3].innerText;

    modifyStuForm.style.display = 'block';
    var newName=document.getElementById('newName');
    var newClass=document.getElementById('newClass');
    var newId=document.getElementById('newId');
    newName.value=name;
    newClass.value=clas;
    newId.value=id;

    var comp=document.getElementById('comp');
    comp.onclick = function() {
        modifyStudent(id);
    }
}

function modifyStudent(id) {
    var para = document.createElement("a");
    para.href = 'closeexe://&&3&&' + nowTime.getTime() + '&&' + id;

    var newName=document.getElementById('newName').value;
    var newClass=document.getElementById('newClass').value;
    var newId=document.getElementById('newId').value;

    para.href += '&&' + newId + '&&' + newName + '&&' + newClass;
    para.click();
}

cou.addEventListener('click', ()=> {
    chooseCou();
    changePage();
    page02.style.display = 'block';
})

stu.addEventListener('click', ()=> {
    chooseStu();
    changePage();
    page01.style.display = 'block';
})

window.onload = function() {
    // initpage();
    // initstudent();
    // initTime(new Date().getTime());
    // timeSet(1);
    initstudent();
    initCourse();
    let text=load("./pagebuffer.txt");
    text=text.split("\r").join("");
    var s=text.split("\n");
    console.log(s);
    switch(Number(s[0]))
    {
        case -1:
            initTime(new Date("2023-02-20").getTime());
            timeSet(1);
            stu.click();
            break;
        case 0:
            initTime(Number(s[1]));
            timeSet(1);
            stu.click();
            if(Number(s[2]) === 1)
            {
                tips.style.display='block';
                var i=3;
                var tipsContent=document.getElementById('tipsContent');
                while(s[i]!="")
                {
                    if(s[i]==="1")
                    {
                        i++;
                        continue;
                    }
                    var newp=document.createElement("p");
                    newp.innerHTML=s[i];
                    tipsContent.appendChild(newp);
                    i++;
                }
            }
            break;
        case 1:
            initTime(Number(s[1]));
            timeSet(1);
            cou.click();
            if(Number(s[2]) === 1)
            {
                tips.style.display='block';
                var i=3;
                var tipsContent=document.getElementById('tipsContent');
                while(s[i]!="")
                {
                    if(s[i]==="1")
                    {
                        i++;
                        continue;
                    }
                    var newp=document.createElement("p");
                    newp.innerHTML=s[i];
                    tipsContent.appendChild(newp);
                    i++;
                }
            }
    }
    // var info=s[0].split(" ");
    // if(info[0]==="1")
    //     cou.click();
    // else
    //     stu.click();
        // cit[3].click();
}

function chooseStu() {
    // tea.style.color='black';
    stu.style.color='#57EEEB';
    stu.style.border='2px solid #57EEEB';
    cou.style='none';
    cou.style.border='2px solid aliceblue';
    level="0";
    console.log(level);
}

function chooseCou() {
    cou.style.color='#57EEEB';
    cou.style.border='2px solid #57EEEB';
    stu.style='none';
    stu.style.border='2px solid aliceblue';
    // stu.style.color='black';
    level="1";
    console.log(level);
}

function changePage() {
    document.querySelectorAll('.page').forEach(el=>{
        el.style.display = 'none';
    })
}

function load(name) {
    let xhr = new XMLHttpRequest(),
        okStatus = document.location.protocol === "file:" ? 0 : 200;
    xhr.open('GET', name, false);
    xhr.overrideMimeType("text/html;charset=utf-8");//默认为utf-8
    xhr.send(null);
    return xhr.status === okStatus ? xhr.responseText : null;
}

function initstudent() {
    let text=load("../datas/studentmessage.txt");
    var num=Number(text[0]);
    var s=text.split("\n");
    // console.log(num);
    for(var i=1;i<=num;i++)
    {
        var info=s[i].split(" ");
        // console.log(info);
        // document.getElementById('stuid').value=info[0];
        // document.getElementById('class').value=info[1];
        // document.getElementById('name').value=info[2];
        // document.getElementById('number').value=info[3];
        // btnadd.click();
        addStudentBlock(info[2],info[3],info[1],info[0]);
    }
    document.getElementById('stuid').value="请输入id";
    document.getElementById('class').value="请输入班级";
    document.getElementById('name').value="请输入姓名";
    // document.getElementById('number').value="请输入学号";
}

function addStudentBlock(name,number,clas,stuid) {

    var tdname=document.createElement("td");
    tdname.appendChild(document.createTextNode(name));
    var tdnumber=document.createElement("td");
    tdnumber.appendChild(document.createTextNode(number));
    var tdclas=document.createElement("td");
    tdclas.appendChild(document.createTextNode(clas));
    var tdstuid=document.createElement("td");
    tdstuid.appendChild(document.createTextNode(stuid));
    
    var tddel=document.createElement("td");
    var del=document.createElement("input");
    del.setAttribute("type","button");
    del.setAttribute("onclick","deltr(this)");
    del.setAttribute("value","删除");
    tddel.appendChild(del);

    var cha=document.createElement("input");
    cha.setAttribute("type","button");
    cha.setAttribute("onclick","chatr(this)");
    cha.setAttribute("value","修改");
    tddel.appendChild(cha);

    var tr=document.createElement("tr");
    tr.appendChild(tdname);
    tr.appendChild(tdnumber);
    tr.appendChild(tdclas);
    tr.appendChild(tdstuid);
    tr.appendChild(tddel);

    var table=document.getElementsByTagName("table")[0];
    table.appendChild(tr);
}

function initCourse() {
    var text=load("../datas/course.txt");
    text=text.split("\r").join("");
    text=text.split("\n");
    var num=Number(text[0]);
    for(var i=1;i<=num;i++)
    {
        var info=text[i].split(" ");
        addCourseBlock(info[0],parseInt(Number(info[1])/24)+1,Number(info[1])%24,Number(info[2])%24,info[4],Number(info[3]),Number(info[6]),info[7]);
    }
}

function addCourse() {
    var para = document.createElement("a");
    para.href = 'closeexe://&&4&&' + nowTime.getTime() + '&&' + '1';

    var name=document.getElementById('courseName').value;
    var day=document.getElementById('courseDay').value;
    var sTime=document.getElementById('startTime').value;
    var eTime=document.getElementById('endTime').value;
    var plac=document.getElementById('coursePlac').selectedIndex;
    var clas=document.getElementById('courseClas').value;
    var Y=document.getElementById('Y');
    var N=document.getElementById('N');
    var courseWeek=document.getElementById('courseWeek').value;
    var weekNum=document.getElementById('weekNum').value;
    var multiWeek=document.getElementById('startWeek').value;
    sTime=Number((day-1)*24)+Number(sTime);
    eTime=Number((day-1)*24)+Number(eTime);

    para.href += '&&' + name + '&&' + sTime + '&&' + eTime + '&&' + plac + '&&' + clas;

    if(Y.checked === true)
    {
        para.href += '&&' + 1 + '&&' + courseWeek + '&&' + '0';
        para.click();
    }
    else
    {
        para.href += '&&' + 2 + '&&' + weekNum + '&&' + multiWeek + '&&' + '0';
        para.click();
    }
}

function delCourse(obj) {
    var tr=obj.parentNode.parentNode;
    var name=tr.getElementsByTagName("td")[0].innerText;

    var para = document.createElement("a");
    para.href = 'closeexe://&&5&&' + nowTime.getTime() + '&&' + name + '&&' + '0';
    para.click();
}

function chaCourse(name) {

    var courseName=document.getElementById('courseName').value;
    var courseDay=document.getElementById('courseDay').value;
    var startTime=document.getElementById('startTime').value;
    var endTime=document.getElementById('endTime').value;
    var coursePlac=document.getElementById('coursePlac').selectedIndex;
    var courseClas=document.getElementById('courseClas').value;
    var Y=document.getElementById('Y');
    var N=document.getElementById('N');
    var courseWeek=document.getElementById('courseWeek').value;
    var weekNum=document.getElementById('weekNum').value;
    var multiWeek=document.getElementById('startWeek').value;
    startTime=Number((courseDay-1)*24)+Number(startTime);
    endTime=Number((courseDay-1)*24)+Number(endTime);

    var para = document.createElement("a");
    para.href = 'closeexe://&&6&&' + nowTime.getTime() + '&&' + name;
    para.href += '&&' + courseName + '&&' + startTime + '&&' + endTime + '&&' + coursePlac + '&&' + courseClas;

    if(Y.checked === true)
    {
        para.href += '&&' + 1 + '&&' + courseWeek + '&&' + '0';
        para.click();
    }
    else
    {
        para.href += '&&' + 2 + '&&' + weekNum + '&&' + multiWeek + '&&' + '0';
        para.click();
    }
}

function initchaCourse(name,day,sTime,eTime,clas,plac,weekNum,week) {
    var courseTitle=document.getElementById('courseTitle');
    courseTitle.innerHTML="修改课程";
    courseForm.style.display='block';
    var compCourse=document.getElementById('compCourse');
    compCourse.onclick = function() {
        chaCourse(name);
    }

    document.getElementById('courseName').value = name;
    document.getElementById('courseDay').value = day;
    document.getElementById('startTime').value = sTime;
    document.getElementById('endTime').value = eTime;
    console.log(plac);
    document.getElementById('coursePlac').selectedIndex = Number(plac);
    document.getElementById('courseClas').value = clas;

    if(Number(weekNum) === 1)
    {
        var Y=document.getElementById('Y');
        Y.click();
        document.getElementById('courseWeek').value = week;
    }
    else
    {
        var N=document.getElementById('N');
        N.click();
        document.getElementById('weekNum').value = weekNum;
        document.getElementById('startWeek').value = week;
    }
    
    
    
}

function addCourseBlock(name,day,sTime,eTime,clas,plac,weekNum,week) {
    var tdname=document.createElement("td");
    tdname.appendChild(document.createTextNode(name));
    var tdday=document.createElement("td");
    tdday.appendChild(document.createTextNode(day));
    var tdsTime=document.createElement("td");
    tdsTime.appendChild(document.createTextNode(sTime+'~'+eTime));
    // var tdeTime=document.createElement("td");
    // tdeTime.appendChild(document.createTextNode(eTime));
    var tdclas=document.createElement("td");
    tdclas.appendChild(document.createTextNode(clas));
    var tdplac=document.createElement("td");
    tdplac.appendChild(document.createTextNode(writePlace(plac)));
    var tdweekNum=document.createElement("td");
    tdweekNum.appendChild(document.createTextNode(weekNum));
    var tdweek=document.createElement("td");
    tdweek.appendChild(document.createTextNode(week));

    var tddel=document.createElement("td");
    var del=document.createElement("input");
    del.setAttribute("type","button");
    del.setAttribute("onclick","delCourse(this)");
    del.setAttribute("value","删除");
    tddel.appendChild(del);

    var cha=document.createElement("input");
    cha.setAttribute("type","button");
    // cha.setAttribute("onclick","chaC(this)");
    cha.setAttribute("value","修改");
    cha.onclick = function() {
        initchaCourse(name,day,sTime,eTime,clas,plac,weekNum,week);
    }
    tddel.appendChild(cha);

    var tr=document.createElement("tr");
    tr.appendChild(tdname);
    tr.appendChild(tdday);
    tr.appendChild(tdsTime);
    // tr.appendChild(tdeTime);
    tr.appendChild(tdclas);
    tr.appendChild(tdplac);
    tr.appendChild(tdweekNum);
    tr.appendChild(tdweek);
    tr.appendChild(tddel);

    var table=document.getElementsByTagName("table")[1];
    table.appendChild(tr);
}

function closeTips() {
    tips.style.display='none';
}

function Canc() {
    modifyStuForm.style.display = 'none';
}

function closeCourse() {
    courseForm.style.display = 'none';
}

function addOption(obj) {
    for(var i=0;i<120;i++)
    {
        newOpt=document.createElement("option");
        newOpt.class = 'optionPoints';
        newOpt.innerHTML=num2plac[i];
        newOpt.value = i;
        obj.appendChild(newOpt);
    }
}//初始化地点选择器

function gener(obj) {
    var oneWeek = document.getElementById('oneWeek');
    var multiWeek = document.getElementById('multiWeek');
    if(obj.value === "Y")
    {
        oneWeek.style.display = 'block';
        multiWeek.style.display = 'none';
    }
    else
    {
        oneWeek.style.display = 'none';
        multiWeek.style.display = 'block';
    }
}

function writePlace(ind)
{
    return num2plac[ind];
}//数字地点转中文

// function initpage() {
    
// }

