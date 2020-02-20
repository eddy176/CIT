```
WebApp Developed 10/26/2018
Kacy Stocks

Characters:
>   Name
>   Race and Class
>   Role
>   Trials needed
>   Comments from the player

This is the sql structure of my table below
    CREATE TABLE docs (                   
        id          integer primary key,  
        name        text,                 
        role        text,                 
        charClass   text,                 
        trials      text,                 
        comments    text                  
        );

Below is an example of what the database looks like:
________________________
|Characters             |
|-----------|-----------|
|id         |01         |
|name       |@name      |
|role       |Trialrole  |
|charClass  |Class/race |
|trials     |Location   |
|comments   |etc...     |
|-----------|-----------|
```

**Endpoints:** <br />
__resourceServer.py__ <br />
>__do_OPTIONS__ allows restful methods below<br />
>__do_POST__ request calls handleCreate() which creates a character and puts it into the table<br />
>__do_Get__ request calls handleRetrieve() which grabs a single character from the table<br />
>__do_PUT__ request calls handleUpdate() which replaces characters you choose to update<br />
>__do_DELETE__ calls handleDelete() which deletes characters from the table<br />
>__handlelist()__ returns all character in the table<br />
>__handlenotfound()__ is called when an incorrect address is requested, an incorrect id is updated/deleted, etc...<br />
>__run__ allows the server to listen to requests via the browser<br />

```
resourceDatabase.py
__del__ disconnects from the database
getDocs fetches all entries in the database
getDoc fetches a single entry in the database
createDoc creates a new entry to add to the database
deleteDoc removes a single entry from the database
updateDoc replaces a single entry from the database with new information

resource.js
showDocs: runs when the Show All button is clicked, it calls handlelist() through loadData, do_PUT through updateData, and do_DELETE through deleteData.
next_q: runs when the Next button is clicked, it calls do_POST through createdata.
```