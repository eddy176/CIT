console.log("work stuff");

var jobs;
var heading = document.querySelector("#heading");
var button = document.querySelector("#button");
var button2 = document.querySelector("#button2");

fetch('https://api.myjson.com/bins/t92ts')
    .then( function(res){
    res.json().
        then( function(chores){
            jobs = chores;
    })
})
button.onclick = function(){
    var myField = document.getElementById("my-field").value;
    if (myField != ""){
        var myList = document.querySelector("#chore-list");
        var currentItem = document.getElementById("current-chore");
        var listItem = document.createElement("li");
        
        var randomIndex = Math.floor(Math.random() * jobs.length);
        var job = jobs[randomIndex];

        console.log(myField);
        

        currentItem.innerHTML = myField + ": " + job;
        listItem.innerHTML = myField + ": " + job;
        myList.appendChild(listItem);

        var bubbles = document.createElement('li');
        bubbles.innerHTML = '***';
        myList.appendChild(bubbles);
        myList.style.display = "none";
        
        button2.onclick = function(){
            if(myList.style.display === "none"){
                myList.style.display = "block";
                myList.style.border.width = "5px";
                myList.style.border.color = "white";
            }
            else{
                myList.style.display = "none";
            }
        
        }
    }else{
        window.alert("Put in your name or you wont get to play video games!");
    }
};