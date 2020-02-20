```
WebApp Developed 11/16/2018
Kacy Stocks
```
# Resources
_Characters:_

>   Name

>   Race and Class

>   Role

>   Trials needed

>   Comments from the player

_Users:_

>   First Name

>   Last Name

>   Email

>   Password


# Table Structure
```sql
    CREATE TABLE docs (                   
        id          integer primary key,  
        name        text,                 
        role        text,                 
        charClass   text,                 
        trials      text,                 
        comments    text                  
    );

    CREATE TABLE users (
        id          integer primary key,
        first_name   text,
        last_name    text,
        email        text,
        password     text
    );
```

# Database Schema

_Characters_

key | value
----|------
id | 01
name | @name
role | Trialrole
charClass | Class/race
trials | Location
comments | etc

_Users_

key | value
----|------
id | 01
first_name | Bob
last_name | Bobson
email | help@me.edu
password | disIsMaPass

# Endpoints:

_authenticationServer.py_
```
load_cookie checks to see if a new cookie needs to be made
send_cookie sends a cookie
load_session loads the session if a sessionID is in the cookie, if not, it creates one
end_headers handles the headers
__do_OPTIONS__ allows restful methods below
__do_Get__ handles get requests:
    /cookie checks your cookie
    /sessions gets your session
    /users allows you to get information about current user
    /docs gets the characters saved
    /docs/ gets one character by id

__do_POST__ handles post requests:
    /docs handles creation of characters
    /sessions handles creation of sessions
    /users handles creation of users
__do_DELETE__ calls handleDelete() which deletes characters from the table
__do_PUT__ request calls handleUpdate() which replaces characters you choose to update
__run__ allows the server to listen to requests via the browser
```

# Password Encryption Method:
>   Bcrypt