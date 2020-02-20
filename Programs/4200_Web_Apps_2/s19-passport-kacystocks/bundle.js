(function(){function r(e,n,t){function o(i,f){if(!n[i]){if(!e[i]){var c="function"==typeof require&&require;if(!f&&c)return c(i,!0);if(u)return u(i,!0);var a=new Error("Cannot find module '"+i+"'");throw a.code="MODULE_NOT_FOUND",a}var p=n[i]={exports:{}};e[i][0].call(p.exports,function(r){var n=e[i][1][r];return o(n||r)},p,p.exports,r,e,n,t)}return n[i].exports}for(var u="function"==typeof require&&require,i=0;i<t.length;i++)o(t[i]);return o}return r})()({1:[function(require,module,exports){

// var ROOT_URL = "https://gameoflifemidterm.herokuapp.com";
var ROOT_URL = "http://localhost:8080";

////////////////////////////////// not tested
var createUser = function(user) {
  var data = `firstName=${encodeURIComponent(user.firstName)}`;
    data += `&lastName=${encodeURIComponent(user.lastName)}`;
    data += `&email=${encodeURIComponent(user.email)}`;
    data += `&plainPassword=${encodeURIComponent(user.plainPassword)}`;

    return fetch(`${ROOT_URL}/users`, {
      
      method: "POST",
      headers: {
        "Content-type": "application/x-www-form-urlencoded"
      },
      body: data
    });
}

// returns a status code
var checkLogin = function() {
  return fetch(`${ROOT_URL}/session`);
};

// log in user
var createLogin = function() {
  var data = `email=${encodeURIComponent(user.email)}`;
  data += `&plainPassword=${encodeURIComponent(user.plainPassword)}`;
  return fetch(`${ROOT_URL}/session`, {
    method: "POST",
    headers: {
      "Content-type": "application/x-www-form-urlencoded"
    },
    body: data
  });
};

// log out of session
var logout = function (user) {
  return fetch(`${ROOT_URL}/session/${user._id}`, {
    method: "DELETE"
  });
};

////////////// don't forget to put credentials include everywhere!!!!!

var formatDate = function(date) {
  return moment(date).format("MMMM DD YYYY");
}

// positive:
var createPositive = function (positive) {
  var data = `title=${encodeURIComponent(positive.title)}`;
  data += `&description=${encodeURIComponent(positive.description)}`;
  data += `&total=${encodeURIComponent(positive.total)}`;
  return fetch(`${ROOT_URL}/positives`, {
    
    method: "POST",
    headers: {
      "Content-type": "application/x-www-form-urlencoded"
    },
    credentials: 'include',
    body: data
  });
};
  
var getPositives = function () {
  return fetch(`${ROOT_URL}/positives`);
};
  
var deletePositive = function (positive) {
  return fetch(`${ROOT_URL}/positives/${positive._id}`, {
    method: "DELETE"
  });
};

var updatePositive = function (positive) {
  var data = `title=${encodeURIComponent(positive.title)}`;
  data += `&description=${encodeURIComponent(positive.description)}`;
  data += `&total=${encodeURIComponent(positive.total)}`;
  return fetch(`${ROOT_URL}/positives/${positive._id}`, {
    method: "PUT",
    headers: {
      "Content-type": "application/x-www-form-urlencoded"
    },
    credentials: 'include',
    body: data
  });
};



  // negative: /////////////////////////////////
var createNegative = function (negative) {
  var data = `title=${encodeURIComponent(negative.title)}`;
  data += `&description=${encodeURIComponent(negative.description)}`;
  data += `&total=${encodeURIComponent(negative.total)}`;
  return fetch(`${ROOT_URL}/negatives`, {
    method: "POST",
    headers: {
      "Content-type": "application/x-www-form-urlencoded"
    },
    credentials: 'include',
    body: data
  });
};

var getNegatives = function () {
  return fetch(`${ROOT_URL}/negatives`);
};

var deleteNegative = function (negative) {
  // fetch request to DELETE the negative passed in
  return fetch(`${ROOT_URL}/negatives/${negative._id}`, {
    method: "DELETE"
  });
};

var updateNegative = function (negative) {
  var data = `title=${encodeURIComponent(negative.title)}`;
  data += `&description=${encodeURIComponent(negative.description)}`;
  data += `&total=${encodeURIComponent(negative.total)}`;
  return fetch(`${ROOT_URL}/negatives/${negative._id}`, {
    method: "PUT",
    headers: {
      "Content-type": "application/x-www-form-urlencoded"
    },
    credentials: 'include',
    body: data
  });
};



// journal: //////////////////////////////////////
var createJournal = function (journal) {
  var data = `title=${encodeURIComponent(journal.title)}`;
  data += `&entry=${encodeURIComponent(journal.entry)}`;
  return fetch(`${ROOT_URL}/journals`, {

    method: "POST",
    headers: {
      "Content-type": "application/x-www-form-urlencoded"
    },
    credentials: 'include',
    body: data
  });
};

var getJournals = function () {
  return fetch(`${ROOT_URL}/journals`);
};

var deleteJournal = function (journal) {
  return fetch(`${ROOT_URL}/journals/${journal._id}`, {
    method: "DELETE"
  });
};

var updateJournal = function (journal) {
  var data = `title=${encodeURIComponent(journal.title)}`;
  data += `&description=${encodeURIComponent(journal.description)}`;
  data += `&total=${encodeURIComponent(journal.total)}`;
  return fetch(`${ROOT_URL}/journals/${journal._id}`, {
    method: "PUT",
    headers: {
      "Content-type": "application/x-www-form-urlencoded"
    },
    credentials: 'include',
    body: data
  });
};


  
// apps: /////////////////////////////////////////
var app = new Vue({
  el: '#app',
  data: {
    isMainDoc: true,
    beginJournal: false,
    showRecords: true,
    addNewPositive: false,
    addNewNegative: false,
    positiveChange: false,
    negativeChange: false,
    showJournals: false,
    total: true,
    positiveDiv: true,
    negativeDiv: true,



    loggedIn: true,
    clickedRegister: false,
    password: "",
    passwordFieldType: 'password',
    loginFields: {
      email: "",
      password: "",
      passwordFieldType: 'password'
    },
    regFields: {
      firstName: "",
      lastName: "",
      email: "",
      plainPassword: ""
    },



    posFields: {
      title: "",
      description: "",
      total: ""
    },
    updatePosFields: {
      title: "",
      description: "",
      total: ""
    },
    negFields: {
      title: "",
      description: "",
      total: ""
    },
    updateNegFields: {
      title: "",
      description: "",
      total: ""
    },
    journalFields: {
      title: "",
      entry: ""
    },
    positives: [],
    negatives: [],
    journals: [],
  },


  methods: {    
    // user methods ////////////////////////////////////////
    isInSession: function() {
      checkLogin().then(response => {
        if (response == 200) {
          console.log("User logged in.")
          this.refreshPositives();
          this.refreshNegatives();
          this.refreshJournals();
          loggedIn = true;
        } else {
          console.log("User not logged in.");
          // show log in screen
          loggedIn = false;
        }
      });
    },


    // switches visibility on passwords
    switchVisibility() {
      this.passwordFieldType = this.passwordFieldType === 'password' ? 'text' : 'password'
    },

    // client-side validation
    validateUser: function() {
      this.errors = [];
      if (this.regFields.firstName.length <= 1) {
        this.errors.push("You must specify a first name");
      }
      if (this.regFields.lastName.length <= 3) {
        this.errors.push("You must specify a last name");
      }
      if (this.regFields.email.length <= 4) {
        this.errors.push("You must specify an email");
      }
      if (this.regFields.plainPassword.length < 6) {
        this.errors.push("You must give a password with length 6 or greater");
      }
      
      var now = new Date();
      var date = moment(this.completion_date);
      if (date < now) {
        this.errors.push("The date needs to be in the future.");
      }
    },

    switchToRegister: function () {
      this.clickedRegister = true;
    },


    registerUser: function () {
      this.validateUser();
      if (this.errors.length > 0) {
        return;
      }
      createUser({
        firstName: this.firstName,
        lastName: this.lastName,
        email: this.email,
        plainPassword: this.plainPassword
      }).then(response => {
      if (response.status == 422) {
        response.json().then(function(errors) {
          console.log(errors);
        });
      } else if (response.status == 201) {
        console.log("User created.");
        this.refreshPositives();
        this.refreshPositives();
        this.refreshJournals();
        // login?????
      } else {
        alert("unknown error creating user.")
      }
      });
    },


    // start positive methods //////////////////////////////

    validatePositive: function() {
      this.errors = [];
      if (this.title.length == 0) {
        this.errors.push("You must specify a title");
      }
      if (this.description.length <= 3) {
        this.errors.push("You must describe your positive");
      }
      if (this.total.length == 0) {
        this.errors.push("You must input a total");
      }
      
      var now = new Date();
      var date = moment(this.completion_date);
      if (date < now) {
        this.errors.push("The date needs to be in the future.");
      }
    },


    showPositive: function () {
      this.addNewPositive = true;
      this.addNewNegative = false;
      this.beginJournal = false;
      this.showJournals = false;
      this.negativeChange = false;
      this.PositiveChange = false;
    },


    addPositive: function () {
      createPositive({
        title: this.posFields.title,
        description: this.posFields.description,
        total: this.posFields.total
      }).then(response => {
        console.log("Positive created.");
        this.refreshPositives();
      });
      this.posFields.title = "";
      this.posFields.description = "";
      this.posFields.total = "";
      this.addNewPositive = false;
    },



    newPositive: function () {
      this.showRecords = true;
      this.positiveDiv = true;
      this.negativeDiv = true;
      this.totalOfEntries = true;
    },



    refreshPositives: function () {
      getPositives().then(response => {
        response.json().then(data => {
          this.positives = data;
        });
      });
    },



    selectPositive: function (positive) {
      this.$set(positive, 'showDetails', !positive.showDetails);
      this.addNewPositive = false;
      this.addNewNegative = false;
    },



    removePositive: function (positive) {
      deletePositive(positive).then(response => {
        this.refreshPositives();
      });
    },


    changePositive: function(positive){
      this.positiveChange = true;
      // add validation
    },


    putPositive: function (positive) {
      positive.title = this.updatePosFields.title;
      positive.description = this.updatePosFields.description;
      positive.total = this.updatePosFields.total;
      

      updatePositive(positive).then(response=>{
        this.refreshPositives();
      });
      this.positiveChange = false;
    },




    // end positive methods ///////////////////////////////////

    // start negative methods ////////////////////////////////

    showNegative: function () {
      this.addNewNegative = true;
      // this.isJournal = false;
      this.beginJournal = false;
      this.showJournals = false;
      this.negativeChange = false;
      this.PositiveChange = false;


      this.addNewPositive = false;
    },


    addNegative: function () {
      createNegative({
        title: this.negFields.title,
        description: this.negFields.description,
        total: this.negFields.total
      }).then(response => {
        console.log("Negative created.");
        this.refreshNegatives();
      });
      this.negFields.title = "";
      this.negFields.description = "";
      this.negFields.total = "";
      this.addNewNegative = false;
    },



    newNegative: function () {
      this.ShowRecords = true;
    },



    refreshNegatives: function () {
      getNegatives().then(response => {
        response.json().then(data => {
          this.negatives = data;
        });
      });
    },



    selectNegative: function (negatives) {
      this.$set(negatives, 'showDetails', !negatives.showDetails);
      this.addNewNegative = false;
      this.addNewPositive = false;
    },



    removeNegative: function (negative) {
      deleteNegative(negative).then(response => {
        this.refreshNegatives();
      });
    },

    changeNegative: function(negative){
      this.negativeChange = true;
    },


    putNegative: function (negative) {
      negative.title = this.updateNegFields.title;
      negative.description = this.updateNegFields.description;
      negative.total = this.updateNegFields.total;


      updateNegative(negative).then(response=>{
        this.refreshNegatives();
      });
      this.negativeChange = false;
    },


    // end negative methods //////////////////////////


    // journal methods //////////////////////////////
    openJournal: function () {
      this.addNewNegative = false;
      this.addNewPositive = false;
      this.positiveDiv = false;
      this.negativeDiv = false;
      this.total = false;
      this.beginJournal = true;
    },

    addJournal: function () {        
      createJournal({
        title: this.journalFields.title,
        description: this.journalFields.entry,
      }).then(response => {
        console.log("Journal created.");
        this.refreshJournals();
      });
      this.journalFields.title = "";
      this.journalFields.entry = "";
      this.beginJournal = false;
      this.showJournals = true;
    },



    newJournal: function () {
      // openJournal = true;
      showRecords = false;
      isMainDoc = true;
      // show journal, hide positives and negatives
    },



    refreshJournals: function () {
      getJournals().then(response => {
        response.json().then(data => {
          this.journals = data;
        });
      });
    },



    selectJournal: function (journal) {
      this.$set(journals, 'showDetails', !journals.showDetails);
    },



    removeJournal: function (journal) {
      deleteJournal(journal).then(response => {
        this.refreshJournals();
      });
    },


    // putJournal: function (journal) {
    //   updateJournal(journal).then(response=>{
    //     this.refreshJournals();
    //   });
    // },

    // end journal methods /////////////////////////

  },  // end methods ////////////////////////////////

  computed: {
    totalOfEntries: function () {
      let t = 0;
      this.positives.forEach(function (p) {
        t += p.total;
      });
      this.negatives.forEach(function (n) {
        t += n.total;
      });
      return t;
    }
  },



  created: function () {
    console.log("Vue.js is ready.");
    this.refreshPositives();
    this.refreshNegatives();
    this.refreshJournals();
  }
});

},{}]},{},[1]);
