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
        self.connection = sqlite3.connect("resource_db.db")  # returns the connection object
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
    
    def createDoc(self, name, role, charClass, trials, comments):
        self.cursor.execute("INSERT INTO docs (name, role, charClass, trials, comments) VALUES (?, ?, ?, ?, ?)",[name, role, charClass, trials, comments])  # always a list
        self.connection.commit()  # anytime you modify your database, save

    def deleteDoc(self, doc_id):
        self.cursor.execute("DELETE FROM docs WHERE id=?", [doc_id])
        self.connection.commit()

    def updateDoc(self, name, role, charClass, trials, comments,  id):
        self.cursor.execute("UPDATE docs SET name= ?, role= ?, charClass= ?, trials= ?, comments= ? WHERE id= ?", [name, role, charClass, trials, comments,  id])
        self.connection.commit()

