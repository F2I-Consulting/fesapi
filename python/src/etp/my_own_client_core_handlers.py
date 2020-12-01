import fesapi

class MyOwnClientCoreHandlers(fesapi.CoreHandlers):

    def __init__(self, my_session):
        fesapi.CoreHandlers.__init__(self, my_session)

    def on_OpenSession(self, os, correlation_id):
        print("Opened a session")
	
        print("Asking all dataobjects")
        mb = fesapi.GetResources()
        mb.context.uri = "eml:///"
        mb.context.depth = 1
        mb.scope = fesapi._self
        mb.countObjects = True
        self.getSession().send(mb)
