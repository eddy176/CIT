import sqlite3

def dict_factory(cursor, row):
    d = {}
    for idx, col in enumerate(cursor.description):
        d[col[0]] = row[idx]
    return d

class ticketDB:
    def __init__(self):
        print("Connecting to DB.")
        self.connection = sqlite3.connect("golden_db.db")  # returns the connection object
        self.connection.row_factory = dict_factory
        self.cursor = self.connection.cursor()

    def __del__(self):
        print("Disconnecting from DB.")
        self.connection.close()

    def createTicketTable(self):
        self.cursor.execute("CREATE TABLE IF NOT EXISTS tickets ( id INTEGER PRIMARY KEY, entrant_name TEXT, entrant_age INTEGER, guest_name TEXT, random_token INTEGER)")
        self.connection.commit()

    def getTickets(self):
        self.cursor.execute("SELECT * FROM tickets")
        return self.cursor.fetchall()

    def createTicket(self, name, age, guest_name, random_token):
        self.cursor.execute("INSERT INTO tickets (entrant_name, entrant_age, guest_name, random_token) VALUES (?, ?, ?, ?)",[name, age, guest_name, random_token])
        self.connection.commit()
