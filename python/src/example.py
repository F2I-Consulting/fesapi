# You must run the following command (only once) in order to create the FESAPI Python extension. Run it from fesapi/cmake working directory
# python setup.py build_ext --build-lib ../python/src

# Then, be sure that the FesapiCpp library and its dependencies are accessible (i.e. are in the PATH) for this script
# meaning for example on Windows that they are in the same directory than this file.

from fesapi import *

def serialize():
    epc_file = EpcDocument("TestingPackagePython.epc")
    repo = DataObjectRepository()

    crs = repo.createLocalDepth3dCrs("798d47d8-0c7d-4f12-8c44-0f36b6d16c32", "Default CRS", 0.0, 0.0, 0.0, 0.0, eml20__LengthUom__m, 5215, eml20__LengthUom__m, "Unknown", False)
    repo.setDefaultCrs(crs)
    print("Serialize : CRS title is " + crs.getTitle())

    # HdfProxy
    hdfProxy = repo.createHdfProxy("798d47d8-0c7d-4f12-8c44-0f36b6d16c33", "Hdf Proxy", ".", "TestingPackagePython.h5", DataObjectRepository.openingMode_OVERWRITE)
    repo.setDefaultHdfProxy(hdfProxy)
    print(hdfProxy.getTitle())

    epc_file.serializeFrom(repo)
    epc_file.close()

serialize()
 