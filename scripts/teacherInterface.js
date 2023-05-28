var stu=document.querySelector('#stu');
var cou=document.querySelector('#cou');
var page01 = document.getElementById('page01');
var page02 = document.getElementById('page02');
var btnadd = document.getElementById('btnadd');
var selectdom = document.querySelector('select');
var calen = document.getElementById('date');
var couta = document.getElementById('coutable');

var timeControler=document.querySelectorAll('div.chooseItem');
var nowTime=new Date();
var timeWalkPace=1000;

function initTime(domTime) {
    nowTime=new Date(domTime);
    timeBox.innerHTML=nowTime.toLocaleString();
}//初始化时间

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
    var number=document.getElementById('number').value;
    var clas=document.getElementById('class').value;
    var stuid=document.getElementById('stuid').value;

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

function deltr(obj) {
    var table=obj.parentNode.parentNode.parentNode;
    var tr=obj.parentNode.parentNode;
    var td0=tr.getElementsByTagName("td")[0];
    var td1=tr.getElementsByTagName("td")[1];
    var td2=tr.getElementsByTagName("td")[2];
    var td3=tr.getElementsByTagName("td")[3];
    // var tx0=td0.getElementsByTagName("Text");
    // console.log(tx0);
    console.log(td0.innerText);
    console.log(td1.innerText);
    console.log(td2.innerText);
    console.log(td3.innerText);
    table.removeChild(tr);
    // td0.removeChild(child0);
}

function chatr(obj) {
    var tr=obj.parentNode.parentNode;
    var td0=tr.getElementsByTagName("td")[0];
    var td1=tr.getElementsByTagName("td")[1];
    var td2=tr.getElementsByTagName("td")[2];
    var td3=tr.getElementsByTagName("td")[3];
    var td4=tr.getElementsByTagName("td")[4];

    var childtd0=td0.childNodes;
    var childtd1=td1.childNodes;
    var childtd2=td2.childNodes;
    var childtd3=td3.childNodes;
    var childtd4=td4.childNodes;

    var child0=childtd0[0];
    var child1=childtd1[0];
    var child2=childtd2[0];
    var child3=childtd3[0];
    var child4=childtd4[0];

    td0.removeChild(child0);
    td1.removeChild(child1);
    td2.removeChild(child2);
    td3.removeChild(child3);
    td4.removeChild(child4);
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
    initpage();
    initstudent();
    initTime(new Date().getTime());
    timeSet(1);
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
    let text=load("../datas/students.txt");
    var num=Number(text[0]);
    var s=text.split("\n");
    console.log(num);
    for(var i=1;i<=num;i++)
    {
        var info=s[i].split(" ");
        console.log(info);
        document.getElementById('stuid').value=info[0];
        document.getElementById('class').value=info[1];
        document.getElementById('name').value=info[2];
        document.getElementById('number').value=info[3];
        btnadd.click();
    }
    document.getElementById('stuid').value="请输入id";
    document.getElementById('class').value="请输入班级";
    document.getElementById('name').value="请输入姓名";
    document.getElementById('number').value="请输入学号";
}

function initpage() {
    let text=load("./pagebuffer.txt");
    var s=text.split("\n");
    var info=s[0].split(" ");
    if(info[0]==="1")
        cou.click();
    else
        stu.click();
}

