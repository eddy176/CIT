const bodyParser = require('body-parser');
const express = require('express');

var app = express();
app.use(bodyParser.urlencoded({extended: false })); // tells the server u r using middleware

let OBJECTS = [{
    v1: 1,
    v2: 2,
    v3: 3
}];

app.get('/objects', (request, response) => {
    response.json(OBJECTS);
});

app.post('/objects', (request, response) => {
    console.log('the body', request.body);
    
    if (!request.body.v1 || !request.body.v2 ||
        !request.body.v3 || !request.body.v4){
            response.sendStatus(422);
        }

    let object = {
        v1: request.body.v1,
        v2: request.body.v2,
        v3: request.body.v3
    };

    OBJECTS.push(object);

    response.sendStatus(201);
});


app.listen(8080, function () {
    console.log("Server is listening.");
});