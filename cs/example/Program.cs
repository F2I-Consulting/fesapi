using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using f2i.energisticsStandardsApi;
using f2i.energisticsStandardsApi.common;
using f2i.energisticsStandardsApi.resqml2_0_1;

// Add the fesapi cpp and hdf5, szip, zlib dll into the executable directory.

namespace example
{
    class Program
    {
        private static void serialize()
        {
            using (EpcDocument epc_file = new EpcDocument("../../../TestingPackageCs"))
            {
                LocalDepth3dCrs crs = epc_file.createLocalDepth3dCrs(Guid.NewGuid().ToString(), "UTF8 Crs title : éàç : олег1", 0.0, 0.0, 0.0, 0.0, eml__LengthUom.eml__LengthUom__m, 5215, eml__LengthUom.eml__LengthUom__m, "Unknown", false);
                epc_file.serialize();
                epc_file.close();
            }
        }

        private static void deserialize()
        {
            using (EpcDocument epc_file = new EpcDocument("../../../TestingPackageCs"))
            {
                string des_status = epc_file.deserialize();
                LocalDepth3dCrsVector crs_set = epc_file.getLocalDepth3dCrsSet();
                System.Console.WriteLine("CRS title is " + crs_set[0].getTitle());
                epc_file.close();
                System.Console.WriteLine("Press enter to exit");
                System.Console.ReadLine();
            }
        }

        static void Main(string[] args)
        {
            serialize();
            deserialize();
        }
    }
}
