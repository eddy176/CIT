import os
import psycopg2
import psycopg2.extras
import urllib.parse

class DocsDB:
    def __init__(self):
        urllib.parse.uses_netloc.append("postgres")
        url = urllib.parse.urlparse(os.environ["DATABASE_URL"])

        self.connection = psycopg2.connect(
            cursor_factory=psycopg2.extras.RealDictCursor,
            database=url.path[1:],
            user=url.username,
            password=url.password,
            host=url.hostname,
            port=url.port
        )

        self.cursor = self.connection.cursor()

    def __del__(self):
        self.connection.close()

    # DOCTABLE:
    def createDocTable(self):
        self.cursor.execute("CREATE TABLE IF NOT EXISTS docs ( id SERIAL PRIMARY KEY, name VARCHAR(255), role VARCHAR(255), charClass VARCHAR(255), trials VARCHAR(255), comment VARCHAR(255))")
        self.connection.commit()

    def getDocs(self):
        self.cursor.execute("SELECT * FROM docs")
        return self.cursor.fetchall()

    def getDoc(self, doc_id):
        self.cursor.execute("SELECT * FROM docs WHERE id = %s", [doc_id])
        return self.cursor.fetchone()
    
    def createDoc(self, name, role, charClass, trials, comment):
        self.cursor.execute("INSERT INTO docs (name, role, charClass, trials, comment) VALUES (%s, %s, %s, %s, %s)",[name, role, charClass, trials, comment])  # always a list
        self.connection.commit()  # anytime you modify your database, save

    def deleteDoc(self, doc_id):
        self.cursor.execute("DELETE FROM docs WHERE id=%s", [doc_id])
        self.connection.commit()

    def updateDoc(self, name, role, charClass, trials, comment,  id):
        self.cursor.execute("UPDATE docs SET name= %s, role= %s, charClass= %s, trials= %s, comment= %s WHERE id= %s", [name, role, charClass, trials, comment,  id])
        self.connection.commit()

    # USERTABLE:
    def createUserTable(self):
        self.cursor.execute("CREATE TABLE IF NOT EXISTS users (id SERIAL PRIMARY KEY, first_name VARCHAR(255), last_name VARCHAR(255), email VARCHAR(255), password VARCHAR(255))")
        self.connection.commit()

    def findUserByEmail(self, email):
        print('Email: ', email)
        self.cursor.execute("SELECT * FROM users WHERE email = %s", [email])
        user = self.cursor.fetchone()
        self.connection.commit()
        if not user:
            return None
        return user

    def getUser(self, user):    #get user by ID
        self.cursor.execute("SELECT * FROM users WHERE id = %s", [user])
        rows = self.cursor.fetchone()
        self.connection.commit()
        return rows

    def createUser(self, firstName, lastName, email, hashedPassword):
        self.cursor.execute("INSERT INTO users (first_name, last_name, email, password) VALUES (%s, %s, %s, %s)", [firstName, lastName, email, hashedPassword])
        self.connection.commit()

