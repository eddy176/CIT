// DJ's 2nd class updates on first class.
// First Assignment
const querystring = require('querystring');
const http = require('http');

let CUSTOMOBJECTS = [{
    var1: "one",
    var2: 2,
    var3: 3.0
},{
    var1: 'four',
    var2: 5,
    var3: 6.0
}];
                                                // var is scoped to the entire function
let notFound = function (request, response) {   // let is only scoped to the block
    response.statusCode = 404;
    console.log('GET not found');
    response.end();
};

let objList = function ( request, response ) {
    response.statusCode = 200;
    response.setHeader( 'Content-type', 'application/json');
    response.write(JSON.stringify(CUSTOMOBJECTS));
    response.end();
};

let objectsCreate = function ( request, response ) {
    // notes on how node works
    let chunks = [];
    request.on('data', function (chunk) {
        chunks.push(chunk);
        console.log('Recieved a chunk of data: ', chunk);
    });
    request.on('end', function () {
        let data = Buffer.concat(chunks).toString();
        console.log('Data recieved in full: ', data);
        let parsedData = querystring.parse(data);
        console.log('Parsed data: ', parsedData);

        CUSTOMOBJECTS.push(parsedData);

        response.statusCode = 201;
        response.end();
    })
};

const server = http.createServer(function (request, response) {
    console.log('Request Recieved!', request.method, request.url);
    if (request.method == 'GET') {
        if (request.url == '/objects') {
            objList( request, response );
        } else {
            notFound( request, response );
        }

    } else if (request.method == 'POST'){
        if (request.url == '/objects') {
            objectsCreate( request, response );
        } else {
            notFound( request, response );
        }
    } else {
        notFound( request, response );
    }
});

server.listen(8080);
console.log('Listening...');