import os, base64

class SessionStore:

    def __init__(self):
        self.sessions = {}
        return

    def generateSessionID(self):
        rnum = os.urandom(32)
        rstr = base64.b64encode(rnum).decode("utf-8")
        return rstr

    def createSession(self):
        sessionID = self.generateSessionID()
        self.sessions[sessionID] = {}
        return sessionID

    def getSession(self, sessionID):
        if sessionID in self.sessions:
            return self.sessions[sessionID]
        else:
            return None