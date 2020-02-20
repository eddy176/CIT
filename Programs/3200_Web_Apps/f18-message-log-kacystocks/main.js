
var click = function () {
    var button = document.querySelector("#button");
    var myaddress = document.getElementById("my-link");
    myaddress.value = "";
    button.textContent = "Get Link";
    button.onclick = function() {
        var myfield = document.getElementById("my-field").value;
        if (myfield === ""){
            window.alert("Your document isn't original enough, please input more data!");
        }
        else {
            createdata( myfield );
            var mytext = document.getElementById("my-field");
            mytext.value = "";
            var myJSON = document.getElementById("my-json");
            myJSON.innerHTML = "";
            loaddata( );
            button.textContent = "Copy Link";
            myaddress.value = "file:///C:/Users/Kacy/Desktop/WebAppDev/2PyServer/mydata.txt";
            
            button.onclick = function myFunction() {
                myaddress.select();
                document.execCommand("Copy");
                alert("Link copied to clipboard.");
                click();
            }
        }
            // allow creaters to save and modify the links with an admin link
            // allow users to directly use the data in the file
    }
}
var click2 = function () {
    var myJSON = document.querySelector("#my-json");
    var myField = document.getElementById("my-field");
    var fullList = document.querySelector("#full-list");
    fullList.style.display = "none";
    var button2 = document.querySelector("#button2");
    button2.onclick = function(){
        if(fullList.style.display === "none"){
            fullList.style.display = "block";
            fullList.style.border.width = "5px";
            fullList.style.border.color = "#999";
            myField.style.display = "none";
            myJSON.style.display = "none";
            button2.textContent = "Hide List";
        }
        else{
            fullList.style.display = "none";
            myField.style.display = "block";
            myJSON.style.display = "block";
            button2.textContent = "Show List";
        }
    }
}
click();
click2();

// this is creating the data, saving it to file
var createdata = function ( data ) {
    var encodeddata = "data=" + encodeURIComponent(data);
    fetch("http://localhost:8080/documents",{
    method: "POST",
    body: encodeddata,
    headers: {
        "Content-type": "application/x-www-form-urlencoded"
    }
}).then(function(response) {
        console.log("Cool, your data was created.")
    });
    var whatever = document.getElementById("my-field");
}

// this loads the data from the file to the screen
var loaddata = function ( ) {
    var myJSON = document.querySelector("#my-json");
    var fullList = document.querySelector("#full-list");
    var count = 0;
    fetch("http://localhost:8080/documents")
    .then(function(response){
        return response.json();
    })
    .then(function(data){
        data.forEach(function (record) {
            var newElement = document.createElement("textarea");
            newElement.innerHTML = record;
            newElement.className = "row";
            newElement.readOnly = true;
            newElement.onclick = function () {
            newElement.select();
            };
            myJSON.appendChild(newElement);
            count++;
            if (count >= 2) {
                fullList.textContent += ", " + record;
            }else{
                fullList.textContent += record;
            }
        });
    });
}


loaddata();