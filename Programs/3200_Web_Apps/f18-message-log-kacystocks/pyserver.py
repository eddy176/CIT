from http.server import BaseHTTPRequestHandler , HTTPServer
from urllib.parse import parse_qs
import json

pandas = []

class MyHandler(BaseHTTPRequestHandler):

    def do_GET(self):               # client requests a list of information
        if self.path == "/documents":
            self.handlelist()
        else:
            self.handlenotfound()

    def do_POST(self):              # client requests to create something
        if self.path == "/documents":
            fout = open("mydata.txt", "a") # Writing to file
            length = self.headers["Content-length"]     # grabs the length of the body from the header
            #read the body data from the client
            body = self.rfile.read(int(length)).decode("utf-8") # using length, server recieves the body, reads it and decodes is from utf-8
            data = parse_qs(body)
            mess = data['data'][0]
            fout.write(mess+"\n")
            fout.close()
            self.send_response(201)
            self.send_header("Access-Control-Allow-Origin","*") # CORS THINGY TO ALLOW SERVER TO WORK
            self.end_headers()

        else:
            self.handlenotfound()

        return

    def handlelist(self):
        jsonstring = []
        fin = open("mydata.txt", "r")
        for f in fin:
            f = f.strip()
            jsonstring.append(f)
        self.send_response(200)
        logs = json.dumps(jsonstring)
        self.send_header("Content-type", "application/json")
        self.send_header("Access-Control-Allow-Origin","*") # CORS THINGY TO ALLOW SERVER TO WORK
        self.end_headers()
        #body
        self.wfile.write(bytes(logs, "utf-8"))# we need to send json data

    def handlenotfound(self):
        self.send_response(404)         # when page isn't found it lets the client know it's not found
        self.send_header("Content-type","text/html")
        self.send_header("Access-Control-Allow-Origin","*") # CORS THINGY TO ALLOW SERVER TO WORK
        self.end_headers()
        # body
        self.wfile.write(bytes("<h1>Not Found.</h1>", "utf-8")) # bytes converts html to bytes
        




def run():
    listen = ("127.0.0.1", 8080)
    server = HTTPServer(listen, MyHandler)

    print("Listening...")
    server.serve_forever()

run()

# server is going to be sending MIME types to the client
# application/x-www-form-urlencoded is a mimetype you need to know for the exam
# firstname=DJ&lastname=Holt
# percent encoding: used to encode spaces, !@#$%%^&*()..etc there is a library for this:: %20 is the percent encoding for a space
# encodURIComponent("charlie brown & lucy")