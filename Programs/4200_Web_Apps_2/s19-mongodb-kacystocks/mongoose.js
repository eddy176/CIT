const bodyParser = require('body-parser');
const express = require('express');
const mongoose = require('mongoose');

// MONGOOSE CONNECTION
mongoose.connect('mongodb://kstocks0811:ge8lp9@ds123534.mlab.com:23534/webapps2db', {useNewUrlParser: true});

// MONGOOSE MODELS
const Meal = mongoose.model('Meal', {
    meat: String,
    veggie: String,
    side: String
});

// new way
// app/middleware setup
// const 




var app = express();
app.use(bodyParser.urlencoded({extended: false })); // tells the server u r using middleware

app.get('/meals', (request, response) => {
    Meal.find().then(function (meals){
        response.set("Access-Control-Allow-Origin", "*");
        response.json(meals);
    });
});

app.post('/meals', (request, response) => {
    response.set("Access-Control-Allow-Origin", "*");

    let meal = new Meal({ 
        meat: request.body.meat,
        veggie: request.body.veggie,
        side: request.body.side
    });

    console.log("The body: ", request.body)
    meal.save().then(function () {
        response.set("Access-Control-Allow-Origin", "*");
        response.sendStatus(201);
    });
});


app.listen(8080, function () {
    console.log("Server is listening.");
});