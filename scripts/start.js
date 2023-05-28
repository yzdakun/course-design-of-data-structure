var conf=document.querySelector(".chooseItem");

conf.addEventListener('click',()=>{
    var para1=document.createElement("a");
    para1.href='openexe://';
    para1.click();
    var para2=document.createElement("a");
    para2.href='./htmls/login.html';
    para2.click();
})