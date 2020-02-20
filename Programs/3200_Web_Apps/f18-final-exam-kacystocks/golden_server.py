import json
import sys
from http.server import BaseHTTPRequestHandler, HTTPServer
from urllib.parse import parse_qs
from golden_db import ticketDB
from http import cookies
import random

class ticketHandler(BaseHTTPRequestHandler):

    def load_cookie(self):
        if 'Cookie' in self.headers:
            self.cookie = cookies.SimpleCookie(self.headers['Cookie'])
        else:
            self.cookie = cookies.SimpleCookie()

    def send_cookie(self):
        for morsel in self.cookie.values():
            self.send_header('Set-Cookie', morsel.OutputString())

    def load_session(self):
        self.cookie['oompa'] = 'loompa'

    def end_headers(self):
        self.send_cookie()
        self.send_header("Access-Control-Allow-Origin", self.headers['Origin'])    # could put domain name here
        self.send_header("Access-Control-Allow-Credentials", 'true')
        BaseHTTPRequestHandler.end_headers(self)
        
    def do_GET(self):  # client requests a list of information
        self.load_cookie()
        if self.path == '/cookies':
            print(self.headers['Cookie'])
            self.send_response(200)
            self.send_header('Set-Cookie', 'logged=true')
            self.end_headers()
            self.wfile.write(bytes('logged!', 'utf-8'))

        elif self.path == '/tickets':
            self.handlelist()
        else:
            self.handlenotfound()

    def do_POST(self):       
        if self.path == "/tickets":
            self.load_cookie()
            if 'oompa' in self.cookie:
                self.send_response(403)
                self.end_headers()
                return
            self.load_session() 
            self.handleCreate()
        else:
            self.handlenotfound()

    def handlelist(self):
        self.send_response(200)
        self.send_header("Content-type", "application/json")
        self.end_headers()
        db = ticketDB()
        tickets = db.getTickets()
        self.wfile.write(bytes(json.dumps(tickets), "utf-8"))

    def handlenotfound(self):
        self.send_response(404)
        self.send_header("Content-type", "text/html")
        self.end_headers()
        self.wfile.write(bytes("It seems that this resource has been lost in the cocolate pipes. An Oompa Loompa will be dispatched promptly to recover the artifact.", "utf-8"))

    def handleCreate(self):
        length = self.headers["Content-length"]
        body = self.rfile.read(int(length)).decode("utf-8")
        data = parse_qs(body)
        name = data['entrant_name'][0]
        age = data['entrant_age'][0]
        guest_name = data['guest_name'][0]
        random_token = random.randrange(0, 7)
        db = ticketDB()
        db.createTicket(name, age, guest_name, random_token)
        self.send_response(201)
        self.end_headers()


def run():
    db = ticketDB()
    db.createTicketTable()
    listen = ("127.0.0.1", 8080)
    server = HTTPServer(listen, ticketHandler)
    print("I hear ya...")
    server.serve_forever()
run()

    