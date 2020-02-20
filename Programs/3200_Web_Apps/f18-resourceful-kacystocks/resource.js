var dwPic = document.querySelector("#dw-pic");
var spPic = document.querySelector("#sp-pic");

var nameField = document.querySelector("#name-field");
var roleField = document.querySelector("#role-field");
var classRaceField = document.querySelector("#class-race-field");
var trialsField = document.querySelector("#trials-needed-field");
var commentsField = document.querySelector("#comments");

var fullList = document.querySelector("#full-list");

var button = document.querySelector("#button");
var button2 = document.querySelector("#button2");

var subHeading = document.querySelector("#sub-heading");
var bottomText = document.querySelector("h2");

var nameHead = document.getElementById("nameHead");
var roleHead = document.getElementById("roleHead");
var classRace = document.getElementById("classRace");
var trialHead = document.getElementById("trialHead");
var commentHead = document.getElementById("commentHead");  

var showDocs = function(characters){
    fullList.innerHTML = "";
    characters.forEach(function (character) {
        //docID = character;
        var newElement = document.createElement("textarea");
        var newElement2 = document.createElement("textarea");
        var newElement3 = document.createElement("textarea");
        var newElement4 = document.createElement("textarea");
        var newElement5 = document.createElement("textarea");
        var newButton = document.createElement("button");
        var newButton2 = document.createElement("button");

        newElement.value = character['name'];
        newElement2.value = character['role'];
        newElement3.value = character['charClass'];
        newElement4.value = character['trials'];
        newElement5.value = character['comments'];
        newButton.textContent = "Update";
        newButton2.textContent = "Delete";

        newElement.style.backgroundColor = "#948";
        newElement2.style.backgroundColor = "#948";
        newElement3.style.backgroundColor = "#948";
        newElement4.style.backgroundColor = "#948";
        newElement5.style.backgroundColor = "#948";
        newElement.style.color = "#999";
        newElement2.style.color = "#999";
        newElement3.style.color = "#999";
        newElement4.style.color = "#999";
        newElement5.style.color = "#999";

        newElement.style.width = "100%";
        newElement2.style.width = "100%";
        newElement3.style.width = "100%";
        newElement4.style.width = "100%";
        newElement5.style.width = "100%";

        newElement.style.borderWidth = "0px";
        newElement2.style.borderWidth = "0px";
        newElement3.style.borderWidth = "0px";
        newElement4.style.borderWidth = "0px";
        newElement5.style.borderWidth = "0px";

        newElement.style.resize = "none";
        newElement2.style.resize = "none";
        newElement3.style.resize = "none";
        newElement4.style.resize = "none";
        newElement5.style.resize = "none";


        newButton.style.backgroundColor = "#444";
        newButton.style.color = "#aaa";
        newButton.style.borderWidth = "0px";
        newButton.style.fontFamily = "Cambria";
        newButton.style.marginRight = "5px";
        newButton.style.marginTop = "2px";
        newButton2.style.marginBottom = "15px";

        newButton2.style.backgroundColor = "#444";
        newButton2.style.color = "#aaa";
        newButton2.style.borderWidth = "0px";
        newButton2.style.fontFamily = "Cambria";
        newButton.style.marginLeft = "5px";
        newButton2.style.marginTop = "2px";
        newButton2.style.marginBottom = "15px";
        

        

        fullList.appendChild(newElement);
        fullList.appendChild(newElement2);
        fullList.appendChild(newElement3);
        fullList.appendChild(newElement4);
        fullList.appendChild(newElement5);
        fullList.appendChild(newButton);
        fullList.appendChild(newButton2);
        // console.log("newElement.value before click: ", newElement.value);

 



        newButton.onclick = function(){

            var fields = [newElement, newElement2, newElement3,
                newElement4, newElement5];
                // console.log("character id: ", character['id'])
            updateData(character['id'], fields);
        }
        newButton2.onclick = function(){
            deleteData(character['id']);
        }

        // var person = `name=${encodeURIComponent(nameField.value)}`;
        // person += `&role=${encodeURIComponent(roleField.value)}`;
        // person+= `&charClass=${encodeURIComponent(classRaceField.value)}`;
        // person += `&trials=${encodeURIComponent(trialsField.value)}`;
        // person += `&comments=${encodeURIComponent(commentsField.value)}`;

        // 1. create new element
        // 2. set innerhtml
        // 3. appendchild
        // 4. create some buttons, each with onclick
    });

    if (fullList.style.display === "none"){
        fullList.style.display = "block";
        dwPic.style.display = "none";
        spPic.style.display = "none";
        bottomText.textContent = "Click any field to edit.";
    } else {
        fullList.style.display = "none";
        dwPic.style.display = "block";
        spPic.style.display = "block";
        bottomText.textContent = 'Continue if you are in one of the above trial groups';
        nameHead.style.display = "none";
        roleHead.style.display = "none";
        classRace.style.display = "none";
        trialHead.style.display = "none";
        commentHead.style.display = "none";
        nameField.style.display = 'none';
        roleField.style.display = 'none';
        classRaceField.style.display = 'none';
        trialsField.style.display = 'none';
        commentsField.style.display = 'none';
    }
}

var next_q = function () {
    button.onclick = function() {
        fullList.style.display = "none";
        button2.style.display = 'none';
        dwPic.style.display = "none";
        spPic.style.display = "none";
        nameHead.style.display = "block";
        roleHead.style.display = "block";
        classRace.style.display = "block";
        trialHead.style.display = "block";
        commentHead.style.display = "block";
        nameField.style.display = 'block';
        roleField.style.display = 'block';
        classRaceField.style.display = 'block';
        trialsField.style.display = 'block';
        commentsField.style.display = 'block';
        bottomText.textContent = "Please fill all the fields!";
    

        button.onclick = function(){
            if (nameField.value === '' | roleField.value === '' 
            | classRaceField.value === '' | trialsField.value === ''){
                window.alert("Required field is empty!");
            }else{
                createdata(nameField, roleField, 
                    classRaceField, trialsField, 
                    commentsField);
                // bottomText.style.display = 'none';
                nameHead.style.display = "none";
                roleHead.style.display = "none";
                classRace.style.display = "none";
                trialHead.style.display = "none";
                commentHead.style.display = "none";
                nameField.style.display = 'none';
                roleField.style.display = 'none';
                classRaceField.style.display = 'none';
                trialsField.style.display = 'none';
                commentsField.style.display = 'none';
                subHeading.textContent = "Thank you for your time, happy gaming!";
                fullList.innerHTML = "";
                loadData();
                button2.style.display = 'inline-block';
                next_q();
            }
        }
    }
}
next_q();
    
button2.onclick = function() {
    loadData();
}

// this is is creating data for both group's documents
var createdata = function (nameField, roleField, 
    classRaceField, trialsField, commentsField) {
    // if ("dw" in selection){
        var person = `name=${encodeURIComponent(nameField.value)}`;
        person += `&role=${encodeURIComponent(roleField.value)}`;
        person+= `&charClass=${encodeURIComponent(classRaceField.value)}`;
        person += `&trials=${encodeURIComponent(trialsField.value)}`;
        person += `&comments=${encodeURIComponent(commentsField.value)}`;
        fetch("http://localhost:8080/docs",{
            method: "POST",
            body: person,
            headers: {
            "Content-type": "application/x-www-form-urlencoded"
            }
        }).then(function(response) {
            console.log("Cool, your data will be saved.")
        });
}

var updateData = function (char_id, fields) {
        var person = `name=${encodeURIComponent(fields[0].value)}`;
        person += `&role=${encodeURIComponent(fields[1].value)}`;
        person+= `&charClass=${encodeURIComponent(fields[2].value)}`;
        person += `&trials=${encodeURIComponent(fields[3].value)}`;
        person += `&comments=${encodeURIComponent(fields[4].value)}`;  
        // console.log(person);  
        fetch(`http://localhost:8080/docs/${char_id}`,{
            method: "PUT",
            body: person,
            headers: {
                "Content-type": "application/x-www-form-urlencoded"
            }
        }).then(function(response) {
            loadData();
            console.log("Cool, your data will be saved.")
        });
}

var loadData = function () {
    fetch("http://localhost:8080/docs").then(function(response) {
        response.json().then(function(docs) {
            showDocs(docs);
            console.log("Documents: ", docs);
        });
    });
};

loadData();

var deleteData = function (id) {
    if (confirm("You want to delete id:" + id + "?"),[id]){
        console.log("Deleting character with ID", id);
        fetch(`http://localhost:8080/docs/${id}`,{
            method: "DELETE",
        }).then(function(response) {
            loadData();
            console.log("Character deleted successfully.")
        });
    }
}


// var d
// var selection = [];
// var clicked = function() {
//     var dw_select = document.querySelector("#dw-pic");
//     var sp_select = document.querySelector("#sp-pic");
//     dw_select.onclick = function() {
//         if ("dw" in selection){
//             selection.remove("dw");
//             check(dw_select);
//         }else{
//             selection.append("dw");
//             check(dw_select);
//         }
//     }
//     sp_select.onclick = function() {
//         if ("sp" in selection) {
//             selection.remove("sp");
//             check(sp_select);
//         } else {
//             selection.append("sp");
//             check(sp_select);
//         }
//     }
//     return selection;
// }

// var check = function(group_selected){
//     if (group_selected.style.opacity == 1){
//         group_selected.style.opacity = 2;
//     }
//     else if (group_selected.style.opacity == 2){
//         group_selected.style.opacity = 1;
//     }
// }




// updateButton.onclick = function() {    
    //     nameHead.style.display = "block";
    //     roleHead.style.display = "block";
    //     classRace.style.display = "block";
    //     trialHead.style.display = "block";
    //     commentHead.style.display = "block";
    //     nameField.style.display = 'block';
    //     roleField.style.display = 'block';
    //     classRaceField.style.display = 'block';
    //     trialsField.style.display = 'block';
    //     commentsField.style.display = 'block';
    
    //     updateData(nameField, roleField, classRaceField, trialsField, commentsField);
    
    //     updateButton.onclick = function(){
    //         if (nameField.value === '' | roleField.value === '' 
    //         | classRaceField.value === '' | trialsField.value === ''
    //         | commentsField.value === '' ){
    //             window.alert("Required field is empty!");
    //         }else{
    //             createdata(nameField.value, roleField.value, 
    //                 classRaceField.value, trialsField.value, 
    //                 commentsField.value);
    //             button.style.display = 'none';
    //             bottomText.style.display = 'none';
    //             nameHead.style.display = "none";
    //             roleHead.style.display = "none";
    //             classRace.style.display = "none";
    //             trialHead.style.display = "none";
    //             commentHead.style.display = "none";
    //             nameField.style.display = 'none';
    //             roleField.style.display = 'none';
    //             classRaceField.style.display = 'none';
    //             trialsField.style.display = 'none';
    //             commentsField.style.display = 'none';
    //             subHeading.textContent = "Thank you for your time, happy gaming!"
    //             fullList.style.display = 'block';
    //             updateButton.style.display = "inline-block";
    //             deleteButton.style.display = "inline-block";
    //         }
    //     }
    // }