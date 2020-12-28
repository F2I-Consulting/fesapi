using System;

using F2iConsulting.Fesapi;
using F2iConsulting.Fesapi.Energistics.Etp.v12.Datatypes.Object;
using F2iConsulting.Fesapi.Energistics.Etp.v12.Protocol.Discovery;
using F2iConsulting.Fesapi.Energistics.Etp.v12.Protocol.Store;
using F2iConsulting.Fesapi.${FESAPI_ETP_NS};

public class MyOwnDiscoveryProtocolHandlers : DiscoveryHandlers
{
    public MyOwnDiscoveryProtocolHandlers(AbstractSession mySession)
        : base(mySession)
    {
    }

    public override void on_GetResourcesResponse(GetResourcesResponse msg, long correlationId)
    {
        ResourceVector resources = msg.resources;
        Console.WriteLine(resources.Count + " resources received.");
        foreach (Resource resource in msg.resources)
        {
            Console.WriteLine("*************************************************");
            Console.WriteLine("uri : " + resource.uri);
            Console.WriteLine("data type : " + resource.dataObjectType);
            Console.WriteLine("name : " + resource.name);
            Console.WriteLine("*************************************************");
        }

        Console.WriteLine("Asking to get the first dataobject");
        GetDataObjects gdo = new GetDataObjects();
        MapStringString uriMap = new MapStringString();
        uriMap.Add("0", resources[0].uri);
        gdo.uris =uriMap;
        getSession().send(gdo);
    }
}
