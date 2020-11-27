"""
You must run the following command (only once) in order to create the FESAPI Python extension.
Run it from fesapi/cmake working directory : # python setup.py build_ext --build-lib ../python/src

Be sure that the FesapiCpp library and its dependencies are accessible (i.e. are in the PATH)
meaning for example on Windows that they are in the same directory than this file.
"""

import fesapi

def serialize():
    """
    This function serialize an EPC document
    """
    epc_file = fesapi.EpcDocument("TestingPackagePython.epc")
    repo = fesapi.DataObjectRepository()

    crs = repo.createLocalDepth3dCrs("798d47d8-0c7d-4f12-8c44-0f36b6d16c32", "Default CRS",
                                     0.0, 0.0, 0.0, 0.0,
                                     fesapi.eml20__LengthUom__m, 5215,
                                     fesapi.eml20__LengthUom__m, "Unknown",
                                     False)
    repo.setDefaultCrs(crs)

    # HdfProxy
    hdf_proxy = repo.createHdfProxy("798d47d8-0c7d-4f12-8c44-0f36b6d16c33", "Hdf Proxy",
                                    ".", "TestingPackagePython.h5",
                                    fesapi.DataObjectRepository.openingMode_OVERWRITE)
    repo.setDefaultHdfProxy(hdf_proxy)

    epc_file.serializeFrom(repo)
    epc_file.close()

serialize()
 