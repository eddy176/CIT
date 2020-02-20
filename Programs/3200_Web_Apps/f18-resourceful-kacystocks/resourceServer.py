from http.server import BaseHTTPRequestHandler, HTTPServer
from urllib.parse import parse_qs
import json
from resourceDatabase import DocsDB

class MyHandler(BaseHTTPRequestHandler):
    def do_OPTIONS(self):
        self.send_response(200)
        self.send_header("Access-Control-Allow-Origin", "*")
        self.send_header("Access-Control-Allow-Headers", "Content-type")
        self.send_header("Access-Control-Allow-Methods", "GET, POST, PUT, DELETE, OPTIONS")
        self.end_headers()
        return

    def do_GET(self):  # client requests a list of information
        if self.path == "/docs":
            self.handlelist()
        elif self.path.startswith("/docs/"):
            parts = self.path.split('/')
            doc_id = parts[2]
            self.handleRetrieve(doc_id)
        else:
            self.handlenotfound()

    def do_DELETE(self):
        if self.path.startswith("/docs"):
            parts = self.path.split('/')
            doc_id = parts[2]
            self.handleDelete(doc_id)
        else:
            self.handlenotfound()

            
    def do_PUT(self):
        if self.path.startswith("/docs"):
            parts = self.path.split('/')
            doc_id = parts[2]
            self.handleUpdate(doc_id)
        else:
            self.handlenotfound()

    def do_POST(self):  # client requests to create something
        if self.path == "/docs":
            self.handleCreate()
        else:
            self.handlenotfound()

    def handleRetrieve(self, docID):
        db = DocsDB()
        doc = db.getDoc(docID)
        if doc == None:
            self.handlenotfound()
        else:
            self.send_response(200)
            self.send_header("Access-Control-Allow-Origin", "*")
            self.end_headers()
            self.wfile.write(bytes(json.dumps(doc), "utf-8"))


    def handlelist(self):
        self.send_response(200)
        self.send_header("Content-type", "application/json")
        self.send_header("Access-Control-Allow-Origin", "*")  # CORS THINGY TO ALLOW SERVER TO WORK
        self.end_headers()
        db = DocsDB()
        docs = db.getDocs()
        self.wfile.write(bytes(json.dumps(docs), "utf-8"))  # we need to send json data

    def handlenotfound(self):
        self.send_response(404)  # when page isn't found it lets the client know it's not found
        self.send_header("Content-type", "text/html")
        self.send_header("Access-Control-Allow-Origin", "*")  # CORS THINGY TO ALLOW SERVER TO WORK
        self.end_headers()
        self.wfile.write(bytes("<h1>Not Found.</h1>", "utf-8"))  # bytes converts html to bytes

    def handleCreate(self):
        length = self.headers["Content-length"]  # grabs the length of the body from the header
        # read the body data from the client
        body = self.rfile.read(int(length)).decode("utf-8")  # using length, server recieves the body, reads it and decodes is from utf-8
        data = parse_qs(body)
        name = data['name'][0]
        charClass = data['charClass'][0]
        role = data['role'][0]
        trials = data['trials'][0]
        comments = data['comments'][0]

        db = DocsDB()
        db.createDoc(name, charClass, role, trials, comments)

        self.send_response(201)
        self.send_header("Access-Control-Allow-Origin", "*")  # CORS THINGY TO ALLOW SERVER TO WORK
        self.end_headers()

    def handleDelete(self, docID):
        db = DocsDB()
        doc = db.getDoc(docID)

        if doc == None:
            self.handlenotfound()
        else:
            db.deleteDoc(docID)
            self.send_response(200)
            self.send_header("Access-Control-Allow-Origin", "*")
            self.end_headers()

    def handleUpdate(self, docID):
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
            comments = data['comments'][0]
            db.updateDoc(name, role, charClass, trials, comments, docID)
            self.send_response(200)
            self.send_header("Access-Control-Allow-Origin", "*")
            self.end_headers()


def run():
    listen = ("127.0.0.1", 8080)
    server = HTTPServer(listen, MyHandler)

    print("Listening...")
    server.serve_forever()


run()







