
const conf = document.querySelector('#confirm');
// var para=document.querySelector('#exec');
var logInState = document.querySelector('#returnMessage');
var tea=document.querySelector('#tea');
var stu=document.querySelector('#stu');
// var level;

// chooseTea();

conf.addEventListener('click', () => {
    test();
});

tea.addEventListener('click', ()=> {
    chooseTea();
})

stu.addEventListener('click', ()=> {
    chooseStu();
})

window.onload = function () {
    if(tea.style.color==""&&stu.style.color=="") chooseTea();
    printAns();
    // chooseTea();
}

function test() {
    var userid = document.getElementById("userid").value;
    var psw = document.getElementById("psw").value;
    if(userid==""||psw=="")
        logInState.innerHTML="账号密码不能为空";
    else
    {
        var timestamp = new Date().getTime();
        console.log(userid);
        console.log(psw);
        var para = document.createElement("a");
        para.href = 'closeexe://&&0&&' + level + '&&' + userid + '&&' + psw + '&&' + timestamp;
        // para.target="_blank";
        console.log(para.href);
        para.click();
    }
    
}

function load(name) {
    let xhr = new XMLHttpRequest(),
        okStatus = document.location.protocol === "file:" ? 0 : 200;
    xhr.open('GET', name, false);
    xhr.overrideMimeType("text/html;charset=utf-8");//默认为utf-8
    xhr.send(null);
    return xhr.status === okStatus ? xhr.responseText : null;
}

function printAns() {
    // load("./cpps/exe2js.txt");
    let text = load("./exe2js.txt");
    console.log(text);
    var tmp = 0;
    for (var i = 6; i <= 18; i++)
        tmp = tmp * 10 + Number(text[i]);
    console.log(tmp);
    var nowTimStamp = new Date().getTime();
    console.log(nowTimStamp);
    if (nowTimStamp - tmp <= 1000) {
        if (text[0] == "1"&&text[3]=="1") jumpToTea();
        else if(text[0]=="1"&&text[3]=="0") jumpToStu();
        else if(text[0]=="0") logInState.innerHTML = "密码错误";
        else if(text[0]=="2") logInState.innerHTML = "请检查账号是否正确"
        if (text[3]== "1") chooseTea();
        else chooseStu();
    }
}

function chooseTea() {
    tea.style.color='#57EEEB';
    tea.style.border='2px solid #57EEEB';
    stu.style='none';
    stu.style.border='2px solid aliceblue';
    // stu.style.color='black';
    level="1";
    console.log(level);
}

function chooseStu() {
    // tea.style.color='black';
    stu.style.color='#57EEEB';
    stu.style.border='2px solid #57EEEB';
    tea.style='none';
    tea.style.border='2px solid aliceblue';
    level="0";
    console.log(level);
}

function jumpToTea() {
    var para=document.createElement("a");
    para.href="teacherInterface.html";
    // para.target="_blank";
    para.click();
}

function jumpToStu() {
    var para=document.createElement("a");
    para.href="studentInterface.html";
    // para.target="_blank";
    para.click();
}