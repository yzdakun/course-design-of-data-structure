
const conf = document.querySelector('#confirm');
// var para=document.querySelector('#exec');
var logInState = document.querySelector('#returnMessage');
var tea=document.querySelector('#tea');
var stu=document.querySelector('#stu');
var level;

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
    chooseTea();
    printAns();
}

function test() {
    var userid = document.getElementById("userid").value;
    var psw = document.getElementById("psw").value;
    var timestamp = new Date().getTime();
    console.log(userid);
    console.log(psw);
    var para = document.createElement("a");
    para.href = 'openexe://&&logIn.exe&&' + userid + '&&' + psw + '&&' + level + '&&' + timestamp;
    // para.target="_blank";
    console.log(para.href);
    para.click();
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
    let text = load("./cpps/exe2js.txt");
    console.log(text);
    var tmp = 0;
    for (var i = 2; i <= 15; i++)
        tmp = tmp * 10 + Number(text[i]);
    console.log(tmp);
    var nowTimStamp = new Date().getTime();
    console.log(nowTimStamp);
    if (nowTimStamp - tmp <= 1000) {
        if (text[0] == "1"&&level=="1") jumpToTea();
        else if(text[0]=="1"&&level=="0") jumpToStu();
        else logInState.innerHTML = "登录失败！";
        if (text[18]== "1") chooseTea();
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
}

function chooseStu() {
    // tea.style.color='black';
    stu.style.color='#57EEEB';
    stu.style.border='2px solid #57EEEB';
    tea.style='none';
    tea.style.border='2px solid aliceblue';
    level="0";
}

function jumpToTea() {
    var para=document.createElement("a");
    para.href="./htmls/teacherInterface.html";
    // para.target="_blank";
    para.click();
}

function jumpToStu() {
    var para=document.createElement("a");
    para.href="./htmls/studentInterface.html";
    // para.target="_blank";
    para.click();
}