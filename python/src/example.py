"""
You must run the following command (only once) in order to create the FESAPI Python extension.
Run it from fesapi/cmake working directory : # python setup.py build_ext --build-lib ../python/src

Be sure that the FesapiCpp library and its dependencies are accessible (i.e. are in the PATH)
meaning for example on Windows that they are in the same directory than this file.
"""

import fesapi

def serialize_grid(repo):
    """
    This function create some grids in the repo to be serialized
    """
    earth_model = repo.createEarthModel("f2060ce0-fa3d-11e5-8620-0002a5d5c51b", "Grid")
    earth_model_interp = repo.createEarthModelInterpretation(
        earth_model, "f5cd7520-fa3d-11e5-b65b-0002a5d5c51b", "Grid interp")

    # ONE SUGAR
    single_cell_ijk_grid = repo.createIjkGridExplicitRepresentation(
        earth_model_interp, "e69bfe00-fa3d-11e5-b5eb-0002a5d5c51b", "One unfaulted sugar cube",
        1, 1, 1)
    python_points = [0.0, 0.0, 300.0, 700.0, 0.0, 350.0, 0.0, 150.0, 300.0, 700.0, 150.0, 350.0,
                     0.0, 0.0, 500.0, 700.0, 0.0, 550.0, 0.0, 150.0, 500.0, 700.0, 150.0, 550.0]
    resqml_points = fesapi.DoubleArray(24)
    for i, value in enumerate(python_points):
        resqml_points.setitem(i, value)
    single_cell_ijk_grid.setGeometryAsCoordinateLineNodes(
        fesapi.resqml20__PillarShape__vertical, fesapi.resqml20__KDirection__down, False,
        resqml_points)

def serialize(file_name):
    """
    This function serializes an EPC document
    """
    epc_file = fesapi.EpcDocument(file_name + ".epc")
    repo = fesapi.DataObjectRepository()

    local_3d_crs = repo.createLocalDepth3dCrs("798d47d8-0c7d-4f12-8c44-0f36b6d16c32", "Default CRS",
                                              0.0, 0.0, 0.0, 0.0,
                                              fesapi.eml20__LengthUom__m, 5215,
                                              fesapi.eml20__LengthUom__m, "Unknown",
                                              False)
    local_time_3d_crs = repo.createLocalTime3dCrs("", "Default local time CRS",
                                                  1.0, 0.1, 15, .0,
                                                  fesapi.eml20__LengthUom__m, 23031,
                                                  fesapi.eml20__TimeUom__s,
                                                  fesapi.eml20__LengthUom__m, "Unknown",
                                                  False)
    repo.setDefaultCrs(local_3d_crs)

    # HdfProxy
    hdf_proxy = repo.createHdfProxy("798d47d8-0c7d-4f12-8c44-0f36b6d16c33", "Hdf Proxy",
                                    ".", file_name + ".h5",
                                    fesapi.DataObjectRepository.openingMode_OVERWRITE)
    repo.setDefaultHdfProxy(hdf_proxy)

    serialize_grid(repo)

    epc_file.serializeFrom(repo)
    epc_file.close()

def deserialize(file_name):
    """
    This function deserializes an EPC document
    """
    epc_file = fesapi.EpcDocument(file_name + ".epc")
    print("Start deserialization of " + epc_file.getName())
    repo = fesapi.DataObjectRepository()
    warnings = epc_file.deserializeInto(repo)
    if not warnings:
        print(warnings)
        repo.clearWarnings()

    hdf_proxy_count = repo.getHdfProxyCount()
    print("There is/are " + str(hdf_proxy_count) + " hdf file(s) associated to this epc document.")
    for hdf_proxy_index in range(0, hdf_proxy_count):
        print("Hdf file relative path : " + repo.getHdfProxy(hdf_proxy_index).getRelativePath())

    for warning in repo.getWarnings():
        print("Warning : " + warning)

    enum_str_mapper = fesapi.EnumStringMapper()
    print("MAPPING ENUM VS STRING")
    print("rock permeability == " + enum_str_mapper.getEnergisticsPropertyKindName(
        enum_str_mapper.getEnergisticsPropertyKind("rock permeability")))
    print("m (meter) == " + enum_str_mapper.getEnergisticsUnitOfMeasureName(
        enum_str_mapper.getEnergisticsUnitOfMeasure("m")))

    print("CRS")
    for depth_crs_index in range(repo.getLocalDepth3dCrsCount()):
        depth_crs = repo.getLocalDepth3dCrs(depth_crs_index)
        print("Title is : " + depth_crs.getTitle())
        if depth_crs.isProjectedCrsDefinedWithEpsg():
            print("Projected : EPSG " + str(depth_crs.getProjectedCrsEpsgCode()))
        else:
            if depth_crs.isProjectedCrsUnknown():
                print("Projected : Unknown. Reason is:" + depth_crs.getProjectedCrsUnknownReason())

    for time_crs_index in range(repo.getLocalTime3dCrsCount()):
        time_crs = repo.getLocalTime3dCrs(time_crs_index)
        print("Title is : " + time_crs.getTitle())
        if time_crs.isVerticalCrsDefinedWithEpsg():
            print("Vertical : EPSG one")
        else:
            if time_crs.isVerticalCrsUnknown():
                print("Vertical : Unknown. Reason is:" + time_crs.getVerticalCrsUnknownReason())

serialize("TestingPackagePython")
deserialize("TestingPackagePython")
