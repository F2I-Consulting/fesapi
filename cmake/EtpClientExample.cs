using System;

using F2iConsulting.Fesapi;
using F2iConsulting.Fesapi.${FESAPI_ETP_NS};

namespace EtpClientExample
{
    static class Program
    {
        static void Main(string[] args)
        {
            PlainClientSession session = fesapi.createClientSession("127.0.0.1", "8080", "/", "");
            session.setCoreProtocolHandlers(new MyOwnClientCoreHandlers(session));
            session.setDiscoveryProtocolHandlers(new MyOwnDiscoveryProtocolHandlers(session));
            session.setStoreProtocolHandlers(new MyOwnStoreProtocolHandlers(session));
            session.run();
            Console.WriteLine("FINISHED");
        }
    }
}
