
var ROOT_URL = "https://gameoflifemidterm.herokuapp.com";
// var ROOT_URL = 'http://localhost:8080';

////////////////////////////////// not tested
var createUser =
    function(user) {
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

// returns a status code
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

// // log out of session
// var logout = function(user) {
//   return fetch(`${ROOT_URL}/session/${user._id}`, {method: 'DELETE'});
// };

////////////// don't forget to put credentials include everywhere!!!!!

var formatDate =
    function(date) {
  return moment(date).format('MMMM DD YYYY');
}

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
  return fetch(`${ROOT_URL}/positives`, {
    method: 'GET', 
    credentials: 'include'
  });
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



// negative: /////////////////////////////////
var createNegative = function(negative) {
  var data = `title=${encodeURIComponent(negative.title)}`;
  data += `&description=${encodeURIComponent(negative.description)}`;
  data += `&total=${encodeURIComponent(negative.total)}`;
  return fetch(`${ROOT_URL}/negatives`, {
    method: 'POST',
    headers: {'Content-type': 'application/x-www-form-urlencoded'},
    credentials: 'include',
    body: data
  });
};

var getNegatives = function() {
  return fetch(`${ROOT_URL}/negatives`, {
    method: 'GET', 
    credentials: 'include'
  });
};

var deleteNegative = function(negative) {
  // fetch request to DELETE the negative passed in
  return fetch(
      `${ROOT_URL}/negatives/${negative._id}`,
      {method: 'DELETE', credentials: 'include'});
};

var updateNegative = function(negative) {
  var data = `title=${encodeURIComponent(negative.title)}`;
  data += `&description=${encodeURIComponent(negative.description)}`;
  data += `&total=${encodeURIComponent(negative.total)}`;
  return fetch(`${ROOT_URL}/negatives/${negative._id}`, {
    method: 'PUT',
    headers: {'Content-type': 'application/x-www-form-urlencoded'},
    credentials: 'include',
    body: data
  });
};



// journal: //////////////////////////////////////
var createJournal = function(journal) {
  var data = `title=${encodeURIComponent(journal.title)}`;
  data += `&entry=${encodeURIComponent(journal.entry)}`;
  this.journal = data;
  return fetch(`${ROOT_URL}/journals`, {

    method: 'POST',
    headers: {'Content-type': 'application/x-www-form-urlencoded'},
    credentials: 'include',
    body: data
  });
};

var getJournals = function() {
  return fetch(`${ROOT_URL}/journals`, {
    method: 'GET', 
    credentials: 'include'
  });
};

var deleteJournal = function(journal) {
  return fetch(`${ROOT_URL}/journals/${journal._id}`,{
    method: 'DELETE',
    credentials: 'include'
  });
};

var updateJournal = function(journal) {
  var data = `title=${encodeURIComponent(journal.title)}`;
  data += `&description=${encodeURIComponent(journal.description)}`;
  data += `&total=${encodeURIComponent(journal.total)}`;
  return fetch(`${ROOT_URL}/journals/${journal._id}`, {
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

    regFields: {firstName: '', lastName: ''},
    email: '',
    plainPassword: '',
    passwordFieldType: 'password',



    posFields: {title: '', description: '', total: ''},
    updatePosFields: {title: '', description: '', total: ''},
    negFields: {title: '', description: '', total: ''},
    updateNegFields: {title: '', description: '', total: ''},
    journalFields: {title: '', entry: ''},
    positives: [],
    negatives: [],
    journals: [],
    user: [],
    errors: []
  },


  methods: {


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
              this.refreshJournals;
              this.refreshNegatives;
              this.refreshPositives;
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
            console.log('Validation Error');
          });
        } else if (response.status == 201) {
          console.log('User created.');
          this.refreshPositives();
          this.refreshNegatives();
          this.refreshJournals();
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
      this.addNewNegative = false;
      this.beginJournal = false;
      this.showJournals = false;
      this.negativeChange = false;
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
          this.refreshPositives();
        } else if (response.status == 422) {
          alert("Please input a title, description, and a positive number.")
          console.log("Unprocessable");
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
      this.negativeDiv = true;
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
      this.addNewNegative = false;
    },



    removePositive: function(positive) {
      deletePositive(positive).then(response => {
        this.refreshPositives();
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
        this.refreshPositives();
      });
      this.positiveChange = false;
    },



    // end positive methods ///////////////////////////////////

    // start negative methods ////////////////////////////////

    showNegative: function() {
      this.addNewPositive = false;
      this.addNewNegative = true;
      // this.isJournal = false;
      this.beginJournal = false;
      this.showJournals = false;
      this.negativeChange = false;
      this.PositiveChange = false;
    },


    validateNegative: function() {
      this.errors = [];
      if (this.negFields.title.length == 0) {
        this.errors.push('You must specify a title');
      }
      if (this.negFields.description.length == 0) {
        this.errors.push('You must describe your input');
      }
      if (this.negFields.total.length == 0) {
        this.errors.push('You must input a total');
      }
    },


    addNegative: function() {
      this.validateNegative();
      if (this.errors.length > 0) {
        return;
      }
      createNegative({
        title: this.negFields.title,
        description: this.negFields.description,
        total: this.negFields.total
      }).then(response => {
        if (response.status == 201) {
          console.log('Negative created.');
          this.refreshNegatives();
        } else if (response.status == 422) {
          alert("Please input a title, description, and a negative number.")
          console.log("Unprocessable");
        } 
      });
      this.negFields.title = '';
      this.negFields.description = '';
      this.negFields.total = '';
      this.addNewNegative = false;
    },



    newNegative: function() {
      this.ShowRecords = true;
    },



    refreshNegatives: function() {
      getNegatives().then(response => {
        if (response.status == 200) {
          response.json().then(data => {
            this.negatives = data;
          });
        } else if (response.status == 401) {
          this.loggedIn = false;
        }
      });
    },



    selectNegative: function(negatives) {
      this.$set(negatives, 'showDetails', !negatives.showDetails);
      this.addNewNegative = false;
      this.addNewPositive = false;
    },



    removeNegative: function(negative) {
      deleteNegative(negative).then(response => {
        this.refreshNegatives();
      });
    },

    changeNegative: function(negative) {
      this.negativeChange = true;
    },


    putNegative: function(negative) {
      this.validateNegative();
      negative.title = this.updateNegFields.title;
      negative.description = this.updateNegFields.description;
      negative.total = this.updateNegFields.total;
      updateNegative(negative).then(response => {
        this.refreshNegatives();
      });
      this.negativeChange = false;
    },


    // end negative methods //////////////////////////


    // journal methods //////////////////////////////
    openJournal: function() {
      this.addNewNegative = false;
      this.addNewPositive = false;
      this.positiveDiv = false;
      this.negativeDiv = false;
      this.total = false;
      this.beginJournal = true;
    },



    validateJournal: function() {
      this.errors = [];
      if (this.journalFields.title.length == 0) {
        this.errors.push('You must specify a title');
      }
      if (this.journalFields.entry.length == 0) {
        this.errors.push('You have to write something to make a journal entry!');
      }
    },



    addJournal: function() {
      this.validateJournal();
      if (this.errors.length > 0) {
        return;
      }
      createJournal({
        title: this.journalFields.title,
        description: this.journalFields.entry,
      }).then(response => {
        console.log('Journal created.');
        this.refreshJournals();
      });
      this.journalFields.title = '';
      this.journalFields.entry = '';
      this.beginJournal = false;
      this.showJournals = true;
    },



    newJournal: function() {
      // openJournal = true;
      showRecords = false;
      isMainDoc = true;
      // show journal, hide positives and negatives
    },



    refreshJournals: function() {
      getJournals().then(response => {
        if (response.status == 200) {
          response.json().then(data => {
            this.journals = data;
          });
        } else if (response.status == 401) {
          this.loggedIn = false;
        }
      });
    },



    selectJournal: function() {
      this.$set(this.journals, 'showDetails', !this.journals.showDetails);
    },



    removeJournal: function(journal) {
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
    totalOfEntries: function() {
      let t = 0;
      this.positives.forEach(function(p) {
        t += p.total;
      });
      this.negatives.forEach(function(n) {
        t += n.total;
      });
      return t;
    }
  },



  created: function() {
    console.log('Vue.js is ready.');
    this.refreshPositives();
    this.refreshNegatives();
    this.refreshJournals();
  }
});
