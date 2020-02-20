var dwPic = document.querySelector("#dw-pic");
var spPic = document.querySelector("#sp-pic");

var email = document.querySelector('#email');
var firstName = document.querySelector('#first_name');
var lastName = document.querySelector('#last_name');
var unhashedPassword = document.querySelector('#unhashedPassword');

var firstLabel = document.querySelector('#first-label');
var lastLabel = document.querySelector('#last-label');
var emailLabel = document.querySelector('#email-label');
var passwordLabel = document.querySelector('#password-label');

var loginButton = document.querySelector('#login-button');
var registerButton = document.querySelector('#register-button');
var nav = document.querySelector('nav');
var user = null;

var nameField = document.querySelector("#name-field");
var roleField = document.querySelector("#role-field");
var classRaceField = document.querySelector("#class-race-field");
var trialsField = document.querySelector("#trials-needed-field");
var commentField = document.querySelector("#comment");

var fullList = document.querySelector("#full-list");

var button = document.querySelector("#button");
var button2 = document.querySelector("#button2");

var mainHeading = document.querySelector('#heading');
var subHeading = document.querySelector("#sub-heading");
var bottomText = document.querySelector("h2");

var nameHead = document.getElementById("nameHead");
var roleHead = document.getElementById("roleHead");
var classRace = document.getElementById("classRace");
var trialHead = document.getElementById("trialHead");
var commentHead = document.getElementById("commentHead");  

var showDocs = function(characters){
    console.log("in showDocs", fullList.style.display);
    if (fullList.style.display == "none" || fullList.style.display == ""){
        console.log("showing stuff");
        fullList.style.display = "block";
        dwPic.style.display = "none";
        spPic.style.display = "none";
        bottomText.textContent = "Click any field to edit.";

    } else if (fullList.style.display != 'none') {
        console.log("hiding stuff");
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
        commentField.style.display = 'none';
    }
    fullList.innerHTML = "";

    characters.forEach(function (character) {
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
        newElement5.value = character['comment'];
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

        newButton.onclick = function(){

            var fields = [newElement, newElement2, newElement3,
            newElement4, newElement5];
            updateData(character['id'], fields);
        }
        newButton2.onclick = function(){
            deleteData(character['id']);
        }
    });
}

loginButton.onclick = function() {
    if (email.value == '') {
        window.alert('Please input your email!');
    }
    else if (unhashedPassword.value == '') {
        window.alert('Please input your password!');
    }
    else {
        logUser(email,unhashedPassword);
    }
}

var logging = function () {
    loginButton.style.display = "none";
    email.style.display = 'none';
    unhashedPassword.style.display = 'none';
    button.style.display = 'inline-block';
    button2.style.display = 'inline-block';
    passwordLabel.style.display = 'none';
    emailLabel.style.display = 'none';
    firstLabel.style.display = 'none';
    lastLabel.style.display = 'none';
    firstName.style.display = 'none';
    lastName.style.display = 'none';
    registerButton.style.display = 'none';
}

var reg = function () {
    registerButton.onclick = function () {
        firstName.style.display = 'inline-block';
        lastName.style.display = 'inline-block';
        firstLabel.style.display = 'inline-block';
        lastLabel.style.display = 'inline-block';
        registerButton.onclick = function() {
            if (email.value == '') {
                window.alert('Please input your email!');
            }
            if (unhashedPassword.value == '') {
                window.alert('Please input your password!');
            }
            else if (firstName.value == '') {
                window.alert('Please input your first name!');
            }
            else if (lastName.value == '') {
                window.alert('Please input your last name!');
            }
            else {
                var newUser = [firstName, lastName, email, unhashedPassword];
                createUser(newUser);
            }
        }        
    }
}
reg();

var userCreated = function () {
    firstLabel.style.display = 'none';
    lastLabel.style.display = 'none';
    firstName.style.display = 'none';
    lastName.style.display = 'none';
    unhashedPassword.value = '';
}

// assume logged in, when a response is sent, determine if logged in or not
// if not, show login page 401
// if so, show the data page 201


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
        commentField.style.display = 'block';
        bottomText.textContent = "Please fill all the fields!";
    
        button.onclick = function(){
            if (nameField.value === '' | roleField.value === '' 
            | classRaceField.value === '' | trialsField.value === ''){
                window.alert("Required field is empty!");
            }else{
                createdata(nameField, roleField, 
                    classRaceField, trialsField, 
                    commentField);
                nameHead.style.display = "none";
                roleHead.style.display = "none";
                classRace.style.display = "none";
                trialHead.style.display = "none";
                commentHead.style.display = "none";
                nameField.style.display = 'none';
                roleField.style.display = 'none';
                classRaceField.style.display = 'none';
                trialsField.style.display = 'none';
                commentField.style.display = 'none';
                subHeading.textContent = "Thank you for your time, happy gaming!";
                fullList.innerHTML = "";
                loadData();
                button2.style.display = 'inline-block';
                next_q();
            }
        }
    }
}

button2.onclick = function() {
    loadData();
};

var logUser = function (emailInput, unhashedPassword) {
    var userLog = `email=${encodeURIComponent(emailInput.value)}`;
    userLog += `&password=${encodeURIComponent(unhashedPassword.value)}`;
    fetch("https://av-trial-manager.herokuapp.com/sessions", {
        method: 'POST',
        body: userLog,
        credentials: 'include',
        headers: {
            'Content-type': 'application/x-www-form-urlencoded'
        }
    }).then(function(response) {
        console.log('testing status: ', response.status);
        if (response.status == 422) {
            window.alert('Username and password incorrect.');
        }
        if (response.status == 201) {
            console.log(response, '-log successful');
            logging();
            next_q();
            muhClick();
            return response.json(); // do i need to do anything else???

        } else {
            // display unexpected error, try again
            window.alert('Unexpected error, please try again.');
        }
    })
}

// every time you fetch you need to make this change::::::::
// before headers below: 


// this is is creating data for both group's documents
var createdata = function (nameField, roleField, 
    classRaceField, trialsField, commentField) {
        var person = `name=${encodeURIComponent(nameField.value)}`;
        person += `&role=${encodeURIComponent(roleField.value)}`;
        person+= `&charClass=${encodeURIComponent(classRaceField.value)}`;
        person += `&trials=${encodeURIComponent(trialsField.value)}`;
        person += `&comment=${encodeURIComponent(commentField.value)}`;
        fetch("https://av-trial-manager.herokuapp.com/docs",{
            method: "POST",
            body: person,
            credentials: 'include',
            headers: {
            "Content-type": "application/x-www-form-urlencoded"
            }
        }).then(function(response) {
            console.log("Cool, your data will be saved.")
        });
}

var createUser = function (newUser) {
    var auth = `first_name=${encodeURIComponent(newUser[0].value)}`;
    auth += `&last_name=${encodeURIComponent(newUser[1].value)}`;
    auth += `&email=${encodeURIComponent(newUser[2].value)}`;
    auth += `&password=${encodeURIComponent(newUser[3].value)}`;
    fetch(`https://av-trial-manager.herokuapp.com/users`, {
        method: 'POST',
        body: auth,
        credentials: 'include',
        headers: {
            "Content-type": "application/x-www-form-urlencoded"
        }
    }).then(function(response) {
        console.log('testing status: ', response.status);
        if (response.status == 422) {
            window.alert('Username and password incorrect.');
        }
        if (response.status == 401) {
            window.alert('Not logged in, please log in.');
        }
        if (response.status == 201) {
            console.log('if statement 201 ran', response);
            loadData();       // auto login
            userCreated();
        } else {
            // display unexpected error, try again
            window.alert('Unexpected error, please try again.');
        }
    });
}

var updateData = function (char_id, fields) {
        var person = `name=${encodeURIComponent(fields[0].value)}`;
        person += `&role=${encodeURIComponent(fields[1].value)}`;
        person+= `&charClass=${encodeURIComponent(fields[2].value)}`;
        person += `&trials=${encodeURIComponent(fields[3].value)}`;
        person += `&comment=${encodeURIComponent(fields[4].value)}`;  
        fetch(`https://av-trial-manager.herokuapp.com/docs/${char_id}`,{
            method: "PUT",
            body: person,
            credentials: 'include',
            headers: {
                "Content-type": "application/x-www-form-urlencoded"
            }
        }).then(function(response) {
            loadData();
            console.log("Cool, your data will be updated.")
        });
}

var loadData = function () {
    fetch("https://av-trial-manager.herokuapp.com/docs", {
        credentials: 'include'
    }).then(function(response) {
    console.log(response.status);
        if (response.status == 401) {
            window.alert('Not logged in, please log in.');
        }
        else if (response.status == 200) {
            response.json().then(function(docs) {
                showDocs(docs);
                console.log('your status: ', response.status)
            })
        }
        else { 
            // display unexpected error, try again
            window.alert('Unexpected error, please try again.');
        }
    });
};

var deleteData = function (id) {
    if (confirm("You want to delete id:" + id + "?"),[id]){
        console.log("Deleting character with ID", id);
        fetch(`https://av-trial-manager.herokuapp.com/docs/${id}`,{
            method: "DELETE",
            credentials: 'include',
        }).then(function(response) {
            loadData();
            console.log("Character deleted successfully.")
        });
    }
}

var loadPage = function() {
    fetch(`https://av-trial-manager.herokuapp.com/sessions`,{
        method: 'GET',
        credentials: 'include',
        headers: {
            'Content-type': 'application/x-www-form-urlencoded'
        }
    }).then(function(response) {
        console.log(response.status);
        if (response.status == 200) {
            logging();
            next_q();
        }
        else {
            passwordLabel.style.display = 'inline-block';
            unhashedPassword.style.display = 'inline-block';
            emailLabel.style.display = 'inline-block';
            email.style.display = 'inline-block';
            loginButton.style.display = 'inline-block'
            registerButton.style.display = 'inline-block'
            
        }
    })
}
loadPage();

