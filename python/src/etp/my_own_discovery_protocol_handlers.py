import fesapi

class MyOwnDiscoveryProtocolHandlers(fesapi.DiscoveryHandlers):

    def __init__(self, my_session):
        fesapi.DiscoveryHandlers.__init__(self, my_session)

    def on_GetResourcesResponse(self, msg, correlation_id):
        print("on_GetResourcesResponse 1")
        resources = msg.resources
        resources_size = resources.size()
        print(resources_size, " resources received.")
        for resource in resources:
            print("*************************************************")
            print("uri : ", resource.uri)
            print("data type : ", resource.dataObjectType)
            print("name : ", resource.name)
            print("*************************************************")

        print("Asking to get the first dataobject")
        gdo = fesapi.GetDataObjects()
        uriMap = fesapi.MapStringString()
        uriMap["0"] = resources[0].uri
        gdo.uris =uriMap
        self.getSession().send(gdo, 0, 0x02)
