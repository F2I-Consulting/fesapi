# Please add the fesapi librairy and its dependencies into the same directory than this file (Windows), or in the PATH.

from fesapi import *

def serialize():
    epc_file = EpcDocument("TestingPackagePython.epc")
    repo = DataObjectRepository()

    crs = repo.createLocalDepth3dCrs("798d47d8-0c7d-4f12-8c44-0f36b6d16c32", "Default CRS", 0.0, 0.0, 0.0, 0.0, eml20__LengthUom__m, 5215, eml20__LengthUom__m, "Unknown", False)
    repo.setDefaultCrs(crs)
    print("Serialize : CRS title is " + crs.getTitle())
   
    # HdfProxy
    hdfProxy = repo.createHdfProxy("798d47d8-0c7d-4f12-8c44-0f36b6d16c33", "Hdf Proxy", ".", "TestingPackagePython.h5", DataObjectRepository.openingMode_OVERWRITE)
    print("The line 14 returns something odd")
    repo.setDefaultHdfProxy(hdfProxy)
    print("If you see this message you win!")
    print(hdfProxy.getTitle())
 
    epc_file.serializeFrom(repo)
    epc_file.close()
 
serialize()
 