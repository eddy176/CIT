const express = require('express');
const bodyParser = require('body-parser');
const WebSocket = require('ws');
const mongoose = require('mongoose');
const model = require('./model');
const cors = require('cors');

var app = express();
app.set('port', 8080);

app.use(bodyParser.urlencoded({ extended: false }));
app.use(express.static('public'));
app.use(cors());

app.get('/sightings',(request, response) => {
    model.Sighting.find({}).then(function (sightings) {
        response.json(sightings);
        console.log("got sightings: ", sightings);
        // sendAllToAllSockets();
    });
});

app.post('/sightings', function (req, res) {
    let sighting = new model.Sighting({
        location: req.body.location,
        approx_height: req.body.approx_height,
        body_type: req.body.body_type,
        group_size: req.body.group_size,
        skin_color: req.body.skin_color
    });
    sighting.save().then(
        function() {
          res.sendStatus(201);
          console.log('sigting created');

          sendAllToAllSockets();
        },
        function(error) {  // need this???
          if (err.errors) {
            // are there validation errors?
            var messages = {};
            for (var e in err.errors) {
              messages[e] = err.errors[e].message;
            }
            console.log('validation error saving sighting', messages);
            res.status(422).json(messages);
          } else {
            console.log('unexpected error saving sighting', err);
            res.sendStatus(500);
          }
        });
});

var server = app.listen(app.get('port'), () =>{
    console.log('Server is listening.');
});

const wss = new WebSocket.Server({server: server});

var broadcastToAllSockets = function(data) {
  wss.clients.forEach(function(client) {
    if (client.readyState === WebSocket.OPEN) {
      client.send(JSON.stringify(data));
    }
  });
};

var sendAllToAllSockets = function() {
  model.Sighting.find({}).then(function(sightings) {
    let data = {resource: 'sighting', action: 'list', data: sightings};
    broadcastToAllSockets(data);
  })
};

wss.on('connection', function connection(ws) {
  ws.on('message', function incoming(data) {
    data = JSON.parse(data);
    console.log('data received from client:', data);

    if (data.action == 'list' && data.resource == 'sighting') {
      model.Sighting.find({}).then(function(sightings) {
        let data = {resource: 'sighting', action: 'list', data: sightings};
        ws.send(JSON.stringify(data));
      });
    }
  });
});
