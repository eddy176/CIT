
var getButton = document.querySelector('#get-button');
var ticketList = document.querySelector('#list-wrapper');

var showTickets = function(tickets){
    ticketList.innerHTML = "";
    // should show all of the tickets from the database

    tickets.forEach(function (ticket) {
        var newName = document.createElement('textarea');
        var newAge = document.createElement('textarea');
        var newGuestName = document.createElement('textarea');
        var newTicketNumber = document.createElement('textarea');
        newName.value = ticket['entrant_name'];
        newAge.value = ticket['entrant_age'];
        newGuestName.value = ticket['guest_name'];
        newTicketNumber.value = ticket['random_token'];
        
        var dayOfWeek = new Date().getDay();
        if (newTicketNumber.value == dayOfWeek) {
            newName.style.backgroundColor = "#FF0";
            newAge.style.backgroundColor = "#FF0";
            newGuestName.style.backgroundColor = "#FF0";
            newTicketNumber.style.backgroundColor = "#FF0";
            newName.style.color = "#000";
            newAge.style.color = "#000";
            newGuestName.style.color = "#000";
            newTicketNumber.style.color = "#000";
        } else { 
            newName.style.backgroundColor = "#FFF";
            newAge.style.backgroundColor = "#FFF";
            newGuestName.style.backgroundColor = "#FFF";
            newTicketNumber.style.backgroundColor = "#FFF";
            newName.style.color = "#000";
            newAge.style.color = "#000";
            newGuestName.style.color = "#000";
            newTicketNumber.style.color = "#000";
        }

        newName.style.borderWidth = "0px";
        newAge.style.borderWidth = "0px";
        newGuestName.style.borderWidth = "0px";
        newTicketNumber.style.borderWidth = "0px";

        newName.style.resize = "none";
        newAge.style.resize = "none";
        newGuestName.style.resize = "none";
        newTicketNumber.style.resize = "none";

        newName.style.display = "block";
        newAge.style.display = "block";
        newGuestName.style.display = "block";
        newTicketNumber.style.display = "block";

        ticketList.appendChild(newName);
        ticketList.appendChild(newAge);
        ticketList.appendChild(newGuestName);
        ticketList.appendChild(newTicketNumber);
    });
}

getButton.onclick = function() {
    var name = document.querySelector('#name');
    var age = document.querySelector('#age');
    var guestName = document.querySelector('#guest-name');
    if (name.value == '') {
        window.alert('Please input your name!');
    }
    else if (age.value == '') {
        window.alert('Please input your age!');
    }
    else if (guestName.value == '') {
        window.alert("Please input your guest's name!")
    }
    else {
        postTicket(name, age, guestName);
    }
}

var postTicket = function (name, age, guestName) {
    var ticket = `entrant_name=${encodeURIComponent(name.value)}`;
    ticket += `&entrant_age=${encodeURIComponent(age.value)}`;
    ticket += `&guest_name=${encodeURIComponent(guestName.value)}`;
    fetch("http://localhost:8080/tickets", {
        method: "POST",
        body: ticket,
        credentials: 'include',
        headers: {
            "Content-type": "application/x-www-form-urlencoded"
        }
    }).then(function(response) {
        if (response.status == 201) {
            console.log("You created a ticket.");
            loadTickets();
        }
        if (response.status == 403) {
            window.alert('The Oompa Loompas have already recieved your ticket. Please try again tomorrow.');
        }
    });
}

var loadTickets = function() {
    fetch("http://localhost:8080/tickets",{
        method: 'GET',
        credentials: 'include',
        headers: {
            'Content-type': 'application/x-www-form-urlencoded'
        }
    }).then(function(response) {
        if (response.status == 200) {
            response.json().then(function(tickets) {
                showTickets(tickets);
                console.log("Here are my tickets: ", tickets);
            });
        }else {
            window.alert('Unexpected error.');
        }
    });
}
loadTickets();