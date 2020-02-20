

// var addMessage = function(message) {
//   var messageDiv = document.createElement('div');
//   messageDiv.innerHTML = message;
//   messagesDiv.appendChild(messageDiv);
// };
//////////////////////

// var ROOT_URL = 'https://gameoflifemidterm.herokuapp.com';
var ROOT_URL = 'http://localhost:8080';

var createUser = function(user) {
  var data = `firstName=${encodeURIComponent(user.firstName)}`;
  data += `&lastName=${encodeURIComponent(user.lastName)}`;
  data += `&email=${encodeURIComponent(user.email)}`;
  data += `&plainPassword=${encodeURIComponent(user.plainPassword)}`;
  this.user = data;
  return fetch(`${ROOT_URL}/users`, {
    method: 'POST',
    headers: {'Content-type': 'application/x-www-form-urlencoded'},
    body: data,
  });
}

var checkLogin = function() {
  return fetch(`${ROOT_URL}/session`, {method: 'GET', credentials: 'include'});
};

// log in user
var createLogin = function(user) {
  var data = `email=${encodeURIComponent(user.email)}`;
  data += `&plainPassword=${encodeURIComponent(user.plainPassword)}`;
  return fetch(`${ROOT_URL}/session`, {
    method: 'POST',
    headers: {'Content-type': 'application/x-www-form-urlencoded'},
    body: data,
    credentials: 'include',

  });
};

// positive:
var createPositive = function(positive) {
  var data = `title=${encodeURIComponent(positive.title)}`;
  data += `&description=${encodeURIComponent(positive.description)}`;
  data += `&total=${encodeURIComponent(positive.total)}`;
  return fetch(`${ROOT_URL}/positives`, {
    method: 'POST',
    credentials: 'include',
    headers: {'Content-type': 'application/x-www-form-urlencoded'},
    body: data
  });
};

var getPositives = function() {
  return fetch(
      `${ROOT_URL}/positives`, {method: 'GET', credentials: 'include'});
};

var deletePositive = function(positive) {
  return fetch(`${ROOT_URL}/positives/${positive._id}`, {
    method: 'DELETE',
    credentials: 'include',
  });
};

var updatePositive = function(positive) {
  var data = `title=${encodeURIComponent(positive.title)}`;
  data += `&description=${encodeURIComponent(positive.description)}`;
  data += `&total=${encodeURIComponent(positive.total)}`;
  return fetch(`${ROOT_URL}/positives/${positive._id}`, {
    method: 'PUT',
    headers: {'Content-type': 'application/x-www-form-urlencoded'},
    credentials: 'include',
    body: data
  });
};

// apps: /////////////////////////////////////////
var app = new Vue({
  el: '#app',
  data: {

    // message: "",

    socket: null,  //////// new
    isMainDoc: true,
    showRecords: true,
    addNewPositive: false,
    positiveChange: false,
    total: true,
    positiveDiv: true,

    loggedIn: true,
    clickedRegister: false,

    regFields: {firstName: '', lastName: ''},
    email: '',
    plainPassword: '',
    passwordFieldType: 'password',

    
    posFields: {title: '', description: '', total: ''},
    updatePosFields: {title: '', description: '', total: ''},
    positives: [],
    user: [],
    errors: [],
    // messages: []
  },


  methods: {

    // websocket stuff::
    connectSocket: function() {
      this.socket = new WebSocket('ws://localhost:8080');
      this.socket.onmessage = event => {
        var received = event.data;
        var data = JSON.parse(received);
        console.log('data recieved from server: ', data);
        if (data.action == 'list' && data.resource == 'positive') {
          this.positives = data.data;
        }
        // if (data.action == 'list' && data.resource == 'message') {
        //   this.positives = data.data;
        // }
      };
    },

    sendPositives: function(user) {
      var data = {resource: 'positive', action: 'list'};
      this.socket.send(JSON.stringify(data));
    },
    // sendMessage: function() {
    //   var data = {resource: 'message', action: 'list'};
    //   this.socket.send(JSON.stringify(data));
    // },
    
    
    getPositivesFromSocket: function(user) {
      var data = {
        resource: "positive",
        action: "list"
      };
      this.socket.send(JSON.stringify(data));
    },    
    // getMessagesFromSocket: function() {
    //   var data = {
    //     resource: "message",
    //     action: "list"
    //   };
    //   this.socket.send(JSON.stringify(data));
    // },    
    // end websocket stuff::

    logUser: function() {
      createLogin({email: this.email, plainPassword: this.plainPassword})
          .then(response => {
            if (response.status == 422) {
              response.json().then(function(errors) {
                console.log('Validation Error');
              });
            } else if (response.status == 201) {
              console.log('User logged in.');
              this.loggedIn = true;
              // this.refreshPositives();
            } else if (response.status == 401) {
              alert('Incorrect login, please try again');
              console.log('Improper login info');
            } else if (response.status == 400) {
              alert('To log in, email and password are required.');
              console.log('Bad request');
            } else {
              console.log(response.status)
            }
          })
    },


    switchVisibility() {
      this.passwordFieldType =
          this.passwordFieldType === 'password' ? 'text' : 'password'
    },


    switchToRegister: function() {
      this.clickedRegister = true;
    },


    validateRegister: function() {
      this.errors = [];
      if (this.regFields.firstName.length <= 1) {
        this.errors.push('You must specify a first name');
      }
      if (this.regFields.lastName.length <= 3) {
        this.errors.push('You must specify a last name');
      }
      if (this.email.length <= 4) {
        this.errors.push('You must specify an email');
      }
      if (this.plainPassword.length < 6) {
        this.errors.push('You must give a password with length 6 or greater');
      }
    },


    registerUser: function() {
      this.validateRegister();
      if (this.errors.length > 0) {
        return;
      }
      createUser({
        firstName: this.regFields.firstName,
        lastName: this.regFields.lastName,
        email: this.email,
        plainPassword: this.plainPassword
      }).then(response => {
        if (response.status == 422) {
          response.json().then(function(errors) {
            alert('Improper login, try again.')
            console.log('Validation Error');
          });
        } else if (response.status == 201) {
          console.log('User created.');
          // this.refreshPositives();
          this.clickedRegister = false;
        } else {
          response.json().then(function(errors) {
            console.log(errors);
          });
        };
      });
    },


    // start positive methods //////////////////////////////

    validatePositive: function() {
      this.errors = [];
      if (this.posFields.title.length == 0) {
        this.errors.push('You must specify a title');
      }
      if (this.posFields.description.length == 0) {
        this.errors.push('You must describe your input');
      }
      if (this.posFields.total.length == 0) {
        this.errors.push('You must input a total');
      }
    },



    showPositive: function() {
      this.addNewPositive = true;
      this.PositiveChange = false;
    },



    addPositive: function() {
      this.validatePositive();
      if (this.errors.length > 0) {
        return;
      }
      createPositive({
        title: this.posFields.title,
        description: this.posFields.description,
        total: this.posFields.total
      }).then(response => {
        if (response.status == 201) {

          console.log('Positive created.');
          // this.refreshPositives();
        } else if (response.status == 422) {
          alert('Please input a title, description, and a positive number.')
          console.log('Unprocessable');
        }
      });
      this.posFields.title = '';
      this.posFields.description = '';
      this.posFields.total = '';
      this.addNewPositive = false;
    },



    newPositive: function() {
      this.showRecords = true;
      this.positiveDiv = true;
      this.totalOfEntries = true;
    },



    refreshPositives: function() {
      getPositives().then(response => {
        if (response.status == 200) {
          response.json().then(data => {
            this.positives = data;
          });
        } else if (response.status == 401) {
          this.loggedIn = false;
        }
      });
    },



    selectPositive: function(positive) {
      this.$set(positive, 'showDetails', !positive.showDetails);
      this.addNewPositive = false;
    },



    removePositive: function(positive) {
      deletePositive(positive).then(response => {
        // this.refreshPositives();
      });
    },



    changePositive: function(positive) {
      this.positiveChange = true;
    },



    putPositive: function(positive) {
      this.validatePositive();
      positive.title = this.updatePosFields.title;
      positive.description = this.updatePosFields.description;
      positive.total = this.updatePosFields.total;
      updatePositive(positive).then(response => {
        // this.refreshPositives();
      });
      this.positiveChange = false;
    },
  },  // end methods ////////////////////////////////

  computed: {
    totalOfEntries: function() {
      let t = 0;
      this.positives.forEach(function(p) {
        t += p.total;
      });
      return t;
    }
  },



  created: function() {
    console.log('Vue.js is ready.');
    this.refreshPositives();
    this.connectSocket();
    // this.sendAllToAllSockets();

  }
});
