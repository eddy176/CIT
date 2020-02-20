const bodyParser = require('body-parser');
const cors = require('cors');
const express = require('express');
const model = require('./model.js');
const passport = require('passport');
const passportLocal = require('passport-local');
const session = require('express-session');

// app/middleware setup
var app = express();
app.use(express.static('public'));
app.set('port', (process.env.PORT || 8080));
app.use(bodyParser.urlencoded({ extended: false }));
// app.use(cors( { credentials: true, origin: 'null' } )); // must get rid of this if you deploy client
app.use(cors( { credentials: true, origin: 'null' } )); // switch to this if deployed
app.use(session({secret: 'gabldegook', resave: false, saveUninitialized: true}));
app.use(passport.initialize());
app.use(passport.session());

// passport config
// by default, passport expects username and password
passport.use(new passportLocal.Strategy({
  usernameField: 'email',
  passwordField: 'plainPassword'
}, function(email, plainPassword, done) {  // this function handles auth
  // query db to find user by email then call function passing in user
  model.User.findOne({ email: email }).then(function(user) {
    console.log(user);
    if (!user) {
      return done(null, false);
    }
    user.verifyPassword(plainPassword, function (valid) {
      if (valid) {
        return done(null, user);
      } else {
        return done(null, false);
      }
    });
    }, function (err) {
    // error function logs the error, may return a server error
    return done(err);
  });
}));

passport.serializeUser(function (user, done) {
  // put user id in session
  console.log("creating session: ", user._id);
  done(null, user._id);
});

passport.deserializeUser(function (id, done) {
  // query db and find user at id
  model.User.findOne({_id: id}).then(function(user) {
    // console.log("checking session: ", user._id)
    done(null, user);
  }, function (err) {
    done(err);
  });
});

// express::login logic
// create session
app.post('/session', passport.authenticate('local'), function (req, res) {
  res.sendStatus(201);
});

// express::are we logged in? test
app.get('/session', function(req, res) {
  // user is logged in
  if (req.user) {
    res.sendStatus(200);
  } else {
    res.sendStatus(401);
  };
});

// USER STUFF::

// USER CREATE ACTION
app.post('/users', (req, res) => {
  let user = new model.User({
    firstName: req.body.firstName,
    lastName: req.body.lastName,
    email: req.body.email,
  });
  // have user, so set their password
  user.setEncryptedPassword(req.body.plainPassword, function () {// plainPassword comes from client
    // when encrypted password is eventually set:, then:

    user.save().then(function () {
      res.sendStatus(201);
    }, function (err) {
      if (err.errors) {
        // are there validation errors?
        var messages = {};
        for (var e in err.errors) {
          messages[e] = err.errors[e].message;
        }
        console.log("validation error saving user", messages);
        res.status(422).json(messages);
      } else if (err.code == 11000) {
        res.status(422).json({
          email: "Someone has already registered with that email. Consider signing in instead."
        });
      } else {
        console.log("unexpected error saving user", err);
        res.sendStatus(500);
      }
    });
  });
});


// POSITIVE LIST ACTION
app.get('/positives', (req, res) => {
  if (!req.user) {
    res.sendStatus(401);
    return;
  }
  model.Positive.find({ user: req.user._id }).then(function (positives) {
    res.json(positives);
  });
});


// POSITIVE CREATE ACTION
app.post('/positives', (req, res) => {
  if (!req.user) {
    res.sendStatus(401);
    return;
  }
  let positive = new model.Positive({
    title: req.body.title,
    description: req.body.description,
    total: req.body.total,
    user: req.user._id  // put the user id from database
  });
  console.log(req.body.description);
  positive.save().then(function () {
    res.sendStatus(201);
  }, function (err) {
    // there was a problem saving this positive

    if (err.errors) {
      // are there validation errors?
      var messages = {};
      for (var e in err.errors) {
        messages[e] = err.errors[e].message;
      }
      console.log("validation error saving positive", messages);
      res.status(422).json(messages);
    } else {
      console.log("unexpected error saving positive", err);
      res.sendStatus(500);
    }
  });
});


// POSITIVE RETRIEVE ACTION
app.get('/positives/:id', (req, res) => {
  console.log("the id:", req.params.id);
  if (!req.user) {
    res.sendStatus(401);
    return;
  }
  model.Positive.findOne({ _id: req.params.id }).then(function (positive) {
    if (positive) {
      res.json(positive);
    } else {
      console.log("Query succeded, but found nothing.")
      res.sendStatus(404);
    }
  }, function (err) {
    console.log("there was an error");
    res.sendStatus(400);
  });
});


// POSITIVE UPDATE/REPLACE ACTION
app.put('/positives/:id', (req, res) => {
  console.log("the id:", req.params.id);
  if (!req.user) {
    res.sendStatus(401);
    return;
  }
  model.Positive.findOne({ _id: req.params.id }).then(function (positive) {
    if (positive) {
      positive.title = req.body.title;
      positive.description = req.body.description;
      positive.total = req.body.total;

      positive.save().then(function () {
        res.sendStatus(200);
      });
    } else {
      // query succeeded, but nothing found
      res.sendStatus(404);
    }
  } , function (err) {
if (err.errors){
  var messages = {};
  for (var e in err.errors) {
    messages[e] = err.errors[e].message;
  }
  console.log("error saving positive item", messages);
  response.status(422).json(messages);
} else {
  console.log("Unexpected error saving positive item", err);
  response.sendStatus(500);
  }
  });
});


// POSITIVE DELETE ACTION
app.delete('/positives/:id', (req, res) => {
  console.log("the id:", req.params.id);
  if (!req.user) {
    res.sendStatus(401);
    return;
  }
  model.Positive.findOne({ _id: req.params.id }).then(function (positive) {
    if (positive) {
      positive.delete().then(function () {
        res.json(positive);
      });
    } else {
      res.sendStatus(404);
    }
  }, function (err) {
    res.sendStatus(400);
  });
});


// NEGATIVES//////////////////////////////////////////////////////////////////
// NEGATIVE LIST ACTION
app.get('/negatives', (req, res) => {
  if (!req.user) {
    res.sendStatus(401);
    return;
  }
  model.Negative.find( { user: req.user._id } ).then(function (negatives) {
    res.json(negatives);
  });
});


// NEGATIVE CREATE ACTION
app.post('/negatives', (req, res) => {
  if (!req.user) {
    res.sendStatus(401);
    return;
  }
  let negative = new model.Negative({
    title: req.body.title,
    description: req.body.description,
    total: req.body.total,
    user: req.user._id
  });
  negative.save().then(function () {
    res.sendStatus(201);
  }, function (err) {
    // there was a problem saving this negative

    if (err.errors) {
      // are there validation errors?
      var messages = {};
      for (var e in err.errors) {
        messages[e] = err.errors[e].message;
      }
      console.log("validation error saving negative", messages);
      res.status(422).json(messages);
    } else {
      console.log("unexpected error saving negative", err);
      res.sendStatus(500);
    }
  });
});


// NEGATIVE RETRIEVE ACTION
app.get('/negatives/:id', (req, res) => {
  console.log("the id:", req.params.id);
  if (!req.user) {
    res.sendStatus(401);
    return;
  }
  model.Negative.findOne({ _id: req.params.id }).then(function (negative) {
    if (negative) {
      res.json(negative);
    } else {
      // query succeeded, but nothing found
      res.sendStatus(404);
    }
  }, function (err) {
    // query error!
    res.sendStatus(400);
  });
});


// NEGATIVE UPDATE/REPLACE ACTION
app.put('/negatives/:id', (req, res) => {
  console.log("the id:", req.params.id);
  if (!req.user) {
    res.sendStatus(401);
    return;
  }
  model.Negative.findOne({ _id: req.params.id }).then(function (negative) {
    if (negative) {
      negative.title = req.body.title;
      negative.description = req.body.description;
      negative.total = req.body.total;

      negative.save().then(function () {
        res.sendStatus(200);
      });
    } else {
      // query succeeded, but nothing found
      res.sendStatus(404);
    }
  }, function (err) {
    // query error!
    res.sendStatus(400);
  });
});


// NEGATIVE DELETE ACTION
app.delete('/negatives/:id', (req, res) => {
  console.log("the id:", req.params.id);
  if (!req.user) {
    res.sendStatus(401);
    return;
  }
  model.Negative.findOne({ _id: req.params.id }).then(function (negative) {
    if (negative) {
      negative.delete().then(function () {
        res.json(negative);
      });
    } else {
      // query succeeded, but nothing found
      res.sendStatus(404);
    }
  }, function (err) {
    // query error!
    res.sendStatus(400);
  });
});
// END NEGATIVES /////////////////


// JOURNAL //////////////////////
app.get('/journals', (req, res) => {
  if (!req.user) {
    res.sendStatus(401);
    return;
  }
  model.Journal.find( { user: req.user._id } ).then(function (journal) {
    res.json(journal);
  });
});


// JOURNAL CREATE ACTION
app.post('/journals', (req, res) => {
  if (!req.user) {
    res.sendStatus(401);
    return;
  }
  let journal = new model.Journal({
    title: req.body.title,
    entry: req.body.entry,
    user: req.user._id
  });
  journal.save().then(function () {
    res.sendStatus(201);
  }, function (err) {
    // there was a problem saving this negative

    if (err.errors) {
      // are there validation errors?
      var messages = {};
      for (var e in err.errors) {
        messages[e] = err.errors[e].message;
      }
      console.log("validation error saving journal", messages);
      res.status(422).json(messages);
    } else {
      console.log("unexpected error saving journal", err);
      res.sendStatus(500);
    }
  });
});


// JOURNAL RETRIEVE ACTION
app.get('/journals/:id', (req, res) => {
  console.log("the id:", req.params.id);
  if (!req.user) {
    res.sendStatus(401);
    return;
  }
  model.Journal.findOne({ _id: req.params.id }).then(function (journal) {
    if (journal) {
      res.json(journal);
    } else {
      console.log("Query succeded, but found nothing.")
      res.sendStatus(404);
    }
  }, function (err) {
    console.log("there was an error");
    res.sendStatus(400);
  });
});


// JOURNAL UPDATE/REPLACE ACTION
app.put('/journals/:id', (req, res) => {
  console.log("the id:", req.params.id);
  if (!req.user) {
    res.sendStatus(401);
    return;
  }
  model.Journal.findOne({ _id: req.params.id }).then(function (journal) {
    if (journal) {
      journal.title = req.body.title;
      journal.entry = req.body.entry;

      journal.save().then(function () {
        res.sendStatus(200);
      });
    } else {
      // query succeeded, but nothing found
      res.sendStatus(404);
    }
  }, function (err) {
    if (err.errors){
      var messages = {};
      for (var e in err.errors) {
        messages[e] = err.errors[e].message;
      }
      console.log("error saving journal", messages);
      response.status(422).json(messages);
    } else {
      console.log("Unexpected error saving journal", err);
      response.sendStatus(500);
      }
      });
    });
    

// JOURNAL DELETE ACTION
app.delete('/journals/:id', (req, res) => {
  console.log("the id:", req.params.id);
  if (!req.user) {
    res.sendStatus(401);
    return;
  }
  model.Journal.findOne({ _id: req.params.id }).then(function (journal) {
    if (journal) {
      journal.delete().then(function () {
        res.json(journal);
      });
    } else {
      res.sendStatus(404);
    }
  }, function (err) {
    res.sendStatus(400);
  });
});
// END JOURNAL ////////////////////////////


app.listen(app.get("port"), function () {
  console.log("Server is listening.");
});
