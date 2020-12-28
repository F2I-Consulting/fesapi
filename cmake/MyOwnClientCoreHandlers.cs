using System;

using F2iConsulting.Fesapi.Energistics.Etp.v12.Datatypes.Object;
using F2iConsulting.Fesapi.Energistics.Etp.v12.Protocol.Core;
using F2iConsulting.Fesapi.Energistics.Etp.v12.Protocol.Discovery;
using F2iConsulting.Fesapi.${FESAPI_ETP_NS};

public class MyOwnClientCoreHandlers : CoreHandlers {
	public MyOwnClientCoreHandlers(AbstractSession mySession)
		: base(mySession)
	{
	}

	public override void on_OpenSession(OpenSession os, long correlationId)
	{
		Console.WriteLine("Opened a session");

		Console.WriteLine("Asking all dataobjects");
		GetResources mb = new GetResources();
		mb.context.uri = "eml:///";
		mb.context.depth = 1;
		mb.scope = ContextScopeKind.self;
		mb.countObjects = true;

		getSession().send(mb);
	}
}
