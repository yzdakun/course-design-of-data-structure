
const conf=document.querySelector('#confirm');
// var para=document.querySelector('#exec');
var logInState=document.querySelector('#returnMessage');

conf.addEventListener('click',()=>{
    test();
});
// console(conf);

window.onload= function()
{
    printAns();
}

function test(){
    var userid=document.getElementById("userid").value;
    var psw=document.getElementById("psw").value;
    var timestamp=Date.parse(new Date());
    console.log(userid);
    console.log(psw);
    var para=document.createElement("a");
    para.href='openexe://&&logIn.exe&&'+userid+'&&'+psw+'&&'+timestamp;
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

// function load(name)
// {
//     $.get(name,function(data)
//     {
//         var lines=data.split("\n");
//         $.each(lines,function(i,v)
//         {
//             console.log(v);
//         });
//     });
// }

function printAns()
{
    // load("./cpps/exe2js.txt");
    let text=load("./cpps/exe2js.txt");
    console.log(text);
    var tmp = 0;
    for(var i=2;i<=15;i++)
        tmp=tmp*10+Number(text[i]);
    console.log(tmp);
    var nowTimStamp=Date.parse(new Date());
    console.log(nowTimStamp);
    if(tmp==nowTimStamp)
    {
        if(text[0]=="1") logInState.innerHTML="登录成功！";
        else logInState.innerHTML="登录失败！";
    }
}