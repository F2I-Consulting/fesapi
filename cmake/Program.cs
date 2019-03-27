using System;

using f2i.energisticsStandardsApi;
using f2i.energisticsStandardsApi.${FESAPI_COMMON_NS};
using f2i.energisticsStandardsApi.${FESAPI_RESQML2_0_1_NS};
using f2i.energisticsStandardsApi.${FESAPI_WITSML2_0_NS};

// Add the fesapi cpp and hdf5, szip, zlib dll into the executable directory.

namespace example
{
    static class Program
    {
        private static void serialize()
        {
            using (EpcDocument epc_file = new EpcDocument("../../../TestingPackageCs.epc"))
            {
                LocalDepth3dCrs crs = epc_file.createLocalDepth3dCrs(Guid.NewGuid().ToString(), "UTF8 Crs title : éàç : олег1", 0.0, 0.0, 0.0, 0.0, eml20__LengthUom.eml20__LengthUom__m, 5215, eml20__LengthUom.eml20__LengthUom__m, "Unknown", false);
                System.Console.WriteLine("Serialize : CRS title is " + crs.getTitle());
				Well well = epc_file.createWell("1425632e-3c22-4845-b431-ecd36da0671e", "Well");
                System.Console.WriteLine("Serialize : Well title is " + well.getTitle());
                epc_file.serialize();
                epc_file.close();
            }
        }

        private static void deserialize()
        {
            using (EpcDocument epc_file = new EpcDocument("../../../TestingPackageCs.epc"))
            {
                string status = epc_file.deserialize();
                if (status.Length > 0) {
                    System.Console.WriteLine("Warnings are " + status);
				}
                LocalDepth3dCrsVector crs_set = epc_file.getLocalDepth3dCrsSet();
                System.Console.WriteLine("Deserialize : CRS title is " + crs_set[0].getTitle());
				Well well = epc_file.getDataObjectByUuid("1425632e-3c22-4845-b431-ecd36da0671e") as Well;
                System.Console.WriteLine("Deserialize : Well title is " + well.getTitle());
            }
        }

        static void Main(string[] args)
        {
            serialize();
            deserialize();
        }
    }
}
