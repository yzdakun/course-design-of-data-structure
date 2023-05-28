var ActForm=document.getElementById('actForm');
var quizTim=document.getElementById('bonusquizTime');
var startDate=document.getElementById('newActdate');
var endDate=document.getElementById('endDate');
var bonusclass=document.getElementById('bonusClass');
var addpage01=document.getElementById('addAct-page01');
var addpage02=document.getElementById('addAct-page02');
var totNum=document.getElementById('totNum');
var num=1;

function gener(obj) {

    if(obj.value==="indAct")
    {   
        addpage01.style.display='block';
        addpage02.style.display='none';
    }
    else if(obj.value==="groAct")
    {
        bonusclass.style.display='block';
        addpage01.style.display='block';
        addpage02.style.display='none';
    }
    else
    {
        addpage01.style.display='none';
        addpage02.style.display='block';
    }
}

function quizTime(obj) {
    if(obj.value==="onTime")
        quizTim.style.display='none';
    else quizTim.style.display='block';
}

function update() {
    endDate.min=startDate.value;
    endDate.value=endDate.min;
}

function build() {
    num++;
    totNum.innerHTML="总数: "+num;

    var newp=document.createElement('p');
    var nsp=document.createElement('span');
    nsp.innerHTML='活动名称：';
    var nsp2=document.createElement('span');
    nsp2.innerHTML='活动地点：';

    var nname=document.createElement('input');
    nname.type='text';
    nname.id='name'+num;

    var nplac=document.createElement('input');
    nplac.type='text';
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
}

function del(obj) {
    num--;
    totNum.innerHTML="总数: "+num;
    var tmp=obj.parentNode;
    console.log(tmp);
    addpage02.removeChild(tmp);
}