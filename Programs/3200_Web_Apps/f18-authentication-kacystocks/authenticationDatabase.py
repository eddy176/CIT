import sqlite3
# connecting
# open the file

def dict_factory(cursor, row):
    d = {}
    for idx, col in enumerate(cursor.description):
        d[col[0]] = row[idx]
    return d

class DocsDB:
    def __init__(self):
        print("Connecting to DB.")
        self.connection = sqlite3.connect("authentication_db.db")  # returns the connection object
        self.connection.row_factory = dict_factory
        self.cursor = self.connection.cursor()

    def __del__(self):
        print("Disconnecting from DB.")
        self.connection.close()

    def getDocs(self):
        self.cursor.execute("SELECT * FROM docs")
        return self.cursor.fetchall()

    def getDoc(self, doc_id):
        self.cursor.execute("SELECT * FROM docs WHERE id = ?", [doc_id])
        return self.cursor.fetchone()
    
    def createDoc(self, name, role, charClass, trials, comment):
        self.cursor.execute("INSERT INTO docs (name, role, charClass, trials, comment) VALUES (?, ?, ?, ?, ?)",[name, role, charClass, trials, comment])  # always a list
        self.connection.commit()  # anytime you modify your database, save

    def findUserByEmail(self, email):
        self.cursor.execute("SELECT * FROM users WHERE email = ?", [email])
        user = self.cursor.fetchone()
        self.connection.commit()
        if not user:
            return None
        return user

    def getUser(self, user):    #get user by ID
        self.cursor.execute("SELECT * FROM users WHERE id = ?", [user[0]])
        rows = self.cursor.fetchone()
        self.connection.commit()
        return rows

    def createUser(self, firstName, lastName, email, hashedPassword):
        self.cursor.execute("INSERT INTO users (first_name, last_name, email, password) VALUES (?, ?, ?, ?)", [firstName, lastName, email, hashedPassword])
        self.connection.commit()

    def deleteDoc(self, doc_id):
        self.cursor.execute("DELETE FROM docs WHERE id=?", [doc_id])
        self.connection.commit()

    def updateDoc(self, name, role, charClass, trials, comment,  id):
        self.cursor.execute("UPDATE docs SET name= ?, role= ?, charClass= ?, trials= ?, comment= ? WHERE id= ?", [name, role, charClass, trials, comment,  id])
        self.connection.commit()

