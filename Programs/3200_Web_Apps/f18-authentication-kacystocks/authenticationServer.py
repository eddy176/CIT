from http.server import BaseHTTPRequestHandler, HTTPServer
from urllib.parse import parse_qs
import json
from authenticationDatabase import DocsDB
from passlib.hash import bcrypt
from http import cookies
from sessionStore import SessionStore

gSessionStore = SessionStore()

class MyHandler(BaseHTTPRequestHandler):

    #call load_cookie inside of loadSession and nowhere else
    def load_cookie(self):
        if 'Cookie' in self.headers:
            self.cookie = cookies.SimpleCookie(self.headers['Cookie'])
        else:
            self.cookie = cookies.SimpleCookie()

    def send_cookie(self):
        for morsel in self.cookie.values():
            self.send_header('Set-Cookie', morsel.OutputString())

    def load_session(self):
        self.load_cookie()
        if 'sessionID' in self.cookie:
            sessionID = self.cookie['sessionID'].value
            self.session = gSessionStore.getSession(sessionID)
            if self.session == None:                            # session data does not exist for this ID
                sessionID = gSessionStore.createSession()
                self.session = gSessionStore.getSession(sessionID)
                self.cookie['sessionID'] = sessionID            # staple gun code
        else:
            sessionID = gSessionStore.createSession()
            self.session = gSessionStore.getSession(sessionID)
            self.cookie['sessionID'] = sessionID
        # print('CURRENT SESSION:', self.session)

    def end_headers(self):
        self.send_cookie()
        self.send_header("Access-Control-Allow-Origin", self.headers['Origin'])    # could put domain name here
        self.send_header("Access-Control-Allow-Credentials", 'true')
        BaseHTTPRequestHandler.end_headers(self)

    def do_OPTIONS(self):
        self.load_session()
        self.send_response(200)
        self.send_header("Access-Control-Allow-Headers", "Content-type")
        self.send_header("Access-Control-Allow-Methods", "GET, POST, PUT, DELETE, OPTIONS")
        self.end_headers()
        return

    def do_GET(self):  # client requests a list of information
        self.load_session()
        
        if self.path == '/cookies':
            print(self.headers['Cookie'])
            self.send_response(200)
            self.send_header('Set-Cookie', 'logged=true')
            self.end_headers()
            self.wfile.write(bytes('logged!', 'utf-8'))
            return

        elif self.path == '/sessions':
            self.handleSessionRetrieve()

        elif self.path == '/users':
            user = self.session
            self.handleGetUser(user)
        
        elif self.path == "/docs":
            self.handlelist()
            
        elif self.path.startswith("/docs/"):
            parts = self.path.split('/')
            doc_id = parts[2]
            self.handleRetrieve(doc_id)

        else:
            self.handlenotfound()

    def do_POST(self):
        self.load_session()
        
        if self.path == "/docs":
            self.handleCreate()

        elif self.path == '/sessions':
            self.handleSessionCreate()

        elif self.path == '/users':
            self.handleUserCreate()

        else:
            self.handlenotfound()

    def do_DELETE(self):
        self.load_session()
        if self.path.startswith("/docs"):
            parts = self.path.split('/')
            doc_id = parts[2]
            self.handleDelete(doc_id)
        else:
            self.handlenotfound()

            
    def do_PUT(self):
        self.load_session()
        if self.path.startswith("/docs"):
            parts = self.path.split('/')
            doc_id = parts[2]
            self.handleUpdate(doc_id)
        else:
            self.handlenotfound()

    # notes
    # 422 status code to say unprocessible 
    # http is stateless
    # python holds the state of the browser
    # server handles cookies
    # client holds the cookies to access your web app
    # hashing a copy of the cookie allows you to authenticate it
    # the cookie connects the session with the user
    # using ids that are obscure is more secure than sequencial ids
    # we will have a database, session store, and cookies
    # cookies are transfered through the headers

    def handleRetrieve(self, docID):
        if 'userID' not in self.session:# base case for when not logged in, put it wherever there's a post
            self.handle401() # don't put this in userscreate
            print('handleretrieve if statement')
            return
        db = DocsDB()
        doc = db.getDoc(docID)
        if doc == None:
            self.handlenotfound()
        else:
            self.send_response(200)
            self.end_headers()
            self.wfile.write(bytes(json.dumps(doc), "utf-8"))


    def handleGetUser(self, user):
        db = DocsDB()
        user_email = user['email']
        user = db.findUserByEmail(user_email)
        if user == None:
            self.send_response(422)
        else:
            self.send_response(200)
            self.end_headers()
            self.wfile.write(bytes(json.dumps(user_email), 'utf-8'))

    def handleSessionRetrieve(self):######### how to get their name and stuff, logged in?
        if 'userID' in self.session:
            db = DocsDB()
            user = db.findUserByEmail(self.session['userID'])
            self.send_response(200)
            self.send_header('Content-type', 'application/json')
            self.end_headers()
            self.wfile.write(bytes(json.dumps(user), 'utf-8'))
        else:
            self.handle401()
            print('else statement reached')

    def handlelist(self):
        if 'userID' not in self.session:# base case for when not logged in, put it wherever there's a post
            self.handle401()
            print('handlelist if statement reached')
            print(gSessionStore.sessions)
            return
        self.send_response(200)
        self.send_header("Content-type", "application/json")
        self.end_headers()
        db = DocsDB()
        docs = db.getDocs()
        self.wfile.write(bytes(json.dumps(docs), "utf-8"))

    def handlenotfound(self):
        self.send_response(404)
        self.send_header("Content-type", "text/html")
        self.end_headers()
        self.wfile.write(bytes("<h1>Not Found.</h1>", "utf-8"))

    def handle401(self):
        self.send_response(401)
        self.send_header("Content-type", "text/html")
        self.end_headers()
        self.wfile.write(bytes("<h1>Not logged in.</h1>", "utf-8"))

    def handleCreate(self):
        if 'userID' not in self.session:# base case for when not logged in, put it wherever there's a post
            self.handle401()
            return
        length = self.headers["Content-length"]
        body = self.rfile.read(int(length)).decode("utf-8")
        data = parse_qs(body)
        name = data['name'][0]
        charClass = data['charClass'][0]
        role = data['role'][0]
        trials = data['trials'][0]
        comment = data['comment'][0]
        db = DocsDB()
        db.createDoc(name, charClass, role, trials, comment)
        self.send_response(201)
        self.end_headers()

    def handleUserCreate(self):
        length = self.headers['Content-length']
        body = self.rfile.read(int(length)).decode('utf-8')
        data = parse_qs(body)
        firstName = data['first_name'][0]
        lastName = data['last_name'][0]
        email = data['email'][0]
        unhashedPassword = data['password'][0]
        db = DocsDB()

        if db.findUserByEmail(email) != None:
            self.send_response(422)
            self.end_headers()
            return

        hashedPassword = self.handleUnhashedPassword(unhashedPassword)
        db.createUser(firstName, lastName, email, hashedPassword)
        self.send_response(201)
        self.end_headers()
    
    def handleSessionCreate(self):

        length = self.headers['Content-length']
        body = self.rfile.read(int(length)).decode("utf-8")
        data = parse_qs(body)

        email = data['email'][0]
        unhashedPassword = data['password'][0]

        db = DocsDB()
        user = db.findUserByEmail(email)

        if user == None:
            self.handle401()

            print('handlesessioncreate if statement')
        elif bcrypt.verify(unhashedPassword, user['password']):
            # print('passwords matched!!!!')
            self.session['userID'] = user['id']
            self.load_session()
                
            self.send_response(201)
            self.end_headers()
            print('session id: ', self.session['userID'])
        else:
            self.handle401()
            print('handlesessioncreate else statement')
        # self.end_headers()
        self.wfile.write(bytes(json.dumps(user), "utf-8"))


    def handleDelete(self, docID):
        if 'userID' not in self.session:# base case for when not logged in, put it wherever there's a post
            self.handle401()
            print('handledelete401')
            return
        db = DocsDB()
        doc = db.getDoc(docID)

        if doc == None:
            self.handlenotfound()
        else:
            db.deleteDoc(docID)
            self.send_response(200)
            self.end_headers()

    def handleUpdate(self, docID):
        if 'userID' not in self.session:# base case for when not logged in, put it wherever there's a post
            self.handle401()
            return
        db = DocsDB()
        doc = db.getDoc(docID)
        if doc == None:
            self.handlenotfound()
        else:
            length = self.headers["Content-length"]
            body = self.rfile.read(int(length)).decode("utf-8")
            data = parse_qs(body)
            name = data['name'][0]
            role = data['role'][0]
            charClass = data['charClass'][0]
            trials = data['trials'][0]
            comment = data['comment'][0]
            db.updateDoc(name, role, charClass, trials, comment, docID)
            self.send_response(200)
            self.end_headers()

    def handleUnhashedPassword(self, unhashed_password):
        return bcrypt.hash(unhashed_password)

    def handleVerifyPassword(self, unhashed_password, hashed_password):
        return bcrypt.verify(unhashed_password, hashed_password)


def run():
    listen = ("127.0.0.1", 8080)
    server = HTTPServer(listen, MyHandler)

    print("Listening...")
    server.serve_forever()


run()