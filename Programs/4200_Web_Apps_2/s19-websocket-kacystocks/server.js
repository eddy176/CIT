const bodyParser = require('body-parser');
const cors = require('cors');
const express = require('express');
const model = require('./model.js');
const passport = require('passport');
const passportLocal = require('passport-local');
const session = require('express-session');
//////////////////////////////////////////////
const WebSocket = require('ws');
//////////////////////////////////////////////

// app/middleware setup
var app = express();
app.use(express.static('public'));
app.set('port', (process.env.PORT || 8080));
app.use(bodyParser.urlencoded({extended: false}));

//////////////////////////////////////
// switch these around when deploying
app.use(cors({credentials: true, origin: 'null'}));  // testing
// app.use(cors( { credentials: true, origin: 'null' } ));  // deployed
//////////////////////////////////////

// app.use(session({secret: 'gabldegook', resave: false, saveUninitialized:
// true}));
const sessionParser =
    session({secret: 'keyboard cat', resave: false, saveUninitialized: true});
app.use(sessionParser);
// above is for sessions and users
app.use(passport.initialize());
app.use(passport.session());

// passport config
// by default, passport expects username and password
passport.use(new passportLocal.Strategy(
    {usernameField: 'email', passwordField: 'plainPassword'},
    function(email, plainPassword, done) {  // this function handles auth
      // query db to find user by email then call function passing in user
      model.User.findOne({email: email})
          .then(
              function(user) {
                console.log(user);
                if (!user) {
                  return done(null, false);
                }
                user.verifyPassword(plainPassword, function(valid) {
                  if (valid) {
                    return done(null, user);
                  } else {
                    return done(null, false);
                  }
                });
              },
              function(err) {
                // error function logs the error, may return a server error
                return done(err);
              });
    }));

passport.serializeUser(function(user, done) {
  // put user id in session
  console.log('creating session: ', user._id);
  done(null, user._id);
});

passport.deserializeUser(function(id, done) {
  // query db and find user at id
  model.User.findOne({_id: id}).then(
      function(user) {
        // console.log("checking session: ", user._id)
        done(null, user);
      },
      function(err) {
        done(err);
      });
});

// express::login logic
// create session
app.post('/session', passport.authenticate('local'), function(req, res) {
  res.sendStatus(201);
  sendAllToAllSockets(req.userId);

});

// express::are we logged in? test
app.get('/session', function(req, res) {
  // user is logged in
  if (req.user) {
    res.sendStatus(200);
    sendAllToAllSockets(req.userId);
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
  user.setEncryptedPassword(req.body.plainPassword, function() {  // plainPassword
                                                                  // comes from
                                                                  // client
    // when encrypted password is eventually set:, then:

    user.save().then(
        function() {
          res.sendStatus(201);
        },
        function(err) {
          if (err.errors) {
            // are there validation errors?
            var messages = {};
            for (var e in err.errors) {
              messages[e] = err.errors[e].message;
            }
            console.log('validation error saving user', messages);
            res.status(422).json(messages);
          } else if (err.code == 11000) {
            res.status(422).json({
              email:
                  'Someone has already registered with that email. Consider signing in instead.'
            });
          } else {
            console.log('unexpected error saving user', err);
            res.sendStatus(500);
          }
        });
  });
});

var server = app.listen(app.get('port'), function() {
  console.log('Server is listening.');
});
// POSITIVE LIST ACTION
app.get('/positives', (req, res) => {
  if (!req.user) {
    res.sendStatus(401);
    return;
  }
  model.Positive.find({user: req.user._id}).then(function(positives) {
    res.json(positives);
    sendAllToAllSockets(req.userId);

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
  // console.log(req.body.description);
  positive.save().then(
      function() {
        res.sendStatus(201);
        console.log('positive created');
        sendAllToAllSockets(req.userId);  //////////////////////////////////////
      },
      function(err) {
        // there was a problem saving this positive

        if (err.errors) {
          // are there validation errors?
          var messages = {};
          for (var e in err.errors) {
            messages[e] = err.errors[e].message;
          }
          console.log('validation error saving positive', messages);
          res.status(422).json(messages);
        } else {
          console.log('unexpected error saving positive', err);
          res.sendStatus(500);
        }
      });
});


// POSITIVE RETRIEVE ACTION
app.get('/positives/:id', (req, res) => {
  console.log('the id:', req.params.id);
  if (!req.user) {
    res.sendStatus(401);
    return;
  }
  model.Positive.findOne({_id: req.params.id})
      .then(
          function(positive) {
            if (positive) {
              res.json(positive);
            } else {
              console.log('Query succeded, but found nothing.')
              res.sendStatus(404);
            }
          },
          function(err) {
            console.log('there was an error');
            res.sendStatus(400);
          });
});


// POSITIVE UPDATE/REPLACE ACTION
app.put('/positives/:id', (req, res) => {
  // console.log("the id:", req.params.id);
  if (!req.user) {
    res.sendStatus(401);
    return;
  }
  model.Positive.findOne({_id: req.params.id})
      .then(
          function(positive) {
            if (positive) {
              positive.title = req.body.title;
              positive.description = req.body.description;
              positive.total = req.body.total;

              positive.save().then(function() {
                res.sendStatus(200);
                sendAllToAllSockets(req.userId);
              });
            } else {
              // query succeeded, but nothing found
              res.sendStatus(404);
            }
          },
          function(err) {
            if (err.errors) {
              var messages = {};
              for (var e in err.errors) {
                messages[e] = err.errors[e].message;
              }
              console.log('error saving positive item', messages);
              response.status(422).json(messages);
            } else {
              console.log('Unexpected error saving positive item', err);
              response.sendStatus(500);
            }
          });
});


// POSITIVE DELETE ACTION
app.delete('/positives/:id', (req, res) => {
  console.log('the id:', req.params.id);
  if (!req.user) {
    res.sendStatus(401);
    return;
  }
  model.Positive.findOne({_id: req.params.id})
      .then(
          function(positive) {
            if (positive) {
              positive.delete().then(function() {
                res.json(positive);
                sendAllToAllSockets(req.userId);
              });
            } else {
              res.sendStatus(404);
            }
          },
          function(err) {
            res.sendStatus(400);
          });
});

//////////////////////////////////////////////

// const wss = new WebSocket.Server({ server: server });
const wss = new WebSocket.Server({
  server: server,
  verifyClient: (info, done) => {
    sessionParser(info.req, {}, () => {
      done(info.req.session);
    });
  }
});
// above is for sessions and users

var broadcastToAllSockets =
    function(data) {
  wss.clients.forEach(function each(client) {
    if (client.readyState === WebSocket.OPEN) {
      // client.send(data);
      // console.log("broadcasting", data);
      client.send(JSON.stringify(data));
  }
  });
}

    app.get('/positives', (req, res) => {
      if (!req.user) {
        res.sendStatus(401);
        return;
      }
      model.Positive.find({user: req.user._id}).then(function(positives) {
        res.json(positives);
        sendAllToAllSockets(req.userId);
      });
    });



var sendAllToAllSockets =
    function(userid) {
  console.log('requesting all positives');
  model.Positive.find({}).then(function(positives) {
    let data = {resource: 'positive', action: 'list', data: positives};
    // console.log("sending data", data);
    broadcastToAllSockets(data);
  });
}

// var sendAllToAllSockets =
//     function(userid) {
//   console.log('requesting all positives');
//   model.Positive.find({user: userid}).then(function(positives) {
//     let data = {resource: 'positive', action: 'list', data: positives};
//     // console.log("sending data", data);
//     broadcastToAllSockets(data);
//   });
// }


    // wss = server
    // wss.on('connection', function connection(ws, req) {
    wss.on('connection', function(ws, req) {
      if (req.session.passport) {
        ws.userId = req.session.passport.user;
      }
      console.log("Websocket userid: ", ws.userId);
      ws.on('message', function incoming(data) {
        data = JSON.parse(data);
        sendAllToAllSockets(req.userId);
      });
    });
/////////////////////////////////////////////