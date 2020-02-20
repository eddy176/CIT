>   https://gameoflifemidterm.herokuapp.com
```
WebApp Developed 4/2/2019
Kacy Stocks
```
# Resources
_app.js_
```
handles all of the client-side page loading, effects, and changes
lending server.js a handle on objects in the document
```
_server.js_
```
app.post creates a positive or negative entry into the client's 
list, including an ammount to add up to a total, journal entries 
are documents
app.get shows all of the positives, negatives, or journals in memory
app.listen serves the client via localhost on port 8080 or port declared at the  top and responds to /positives, /negatives, or /journals
according to the type of request submitted by the client

```
_models.js_
```
handles all of the database transactions requested by the client
this is served on mlab, currently
```

# Database:

_users_

>   firstName: string,

>   lastName: string,

>   email: string,

>   hashedPassword: string

_positives_

>   title: string,

>   description: string,

>   total: int


# Endpoints:

_app.post /users_

>   creates a user

_app.get /session_

>   checks session for a logged in user

_app.post /session_

>   logs a user in

_app.get /positives_

>   returns a list of all positives

_app.post /positives_

>   title

>   description

>   total

>   user

_app.put /positives/:id_

>   title

>   description

>   total

>   user

_app.delete /positives/:id_

>   title

>   description

>   total

>   user