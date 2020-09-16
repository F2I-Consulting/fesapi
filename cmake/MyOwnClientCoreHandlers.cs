using System;

using f2i.energisticsStandardsApi.Energistics.Etp.v12.Datatypes.Object;
using f2i.energisticsStandardsApi.Energistics.Etp.v12.Protocol.Core;
using f2i.energisticsStandardsApi.Energistics.Etp.v12.Protocol.Discovery;
using f2i.energisticsStandardsApi.${FESAPI_ETP_NS};

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
		mb.context.uri ="eml:///";
		mb.context.depth = 1;
		mb.scope = ContextScopeKind.self;
		mb.countObjects = true;

		getSession().send(mb);
	}
}
