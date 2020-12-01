"""
You must run the following command (only once) in order to create the FESAPI Python extension.
Run it from fesapi/swig working directory : python3 setup.py build_ext --build-lib ../python/src

Be sure that the FesapiCpp library and its dependencies are accessible
i.e. are in the (LD_LIBRARY_)PATH meaning for example on Windows that
they are in the same directory than this file and the generated pyd file.
"""

from datetime import datetime
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

    # CRS
    local_3d_crs = repo.createLocalDepth3dCrs("798d47d8-0c7d-4f12-8c44-0f36b6d16c32", "Default CRS",
                                              0.0, 0.0, 0.0, 0.0,
                                              fesapi.eml20__LengthUom__m, 5215,
                                              fesapi.eml20__LengthUom__m, "Unknown",
                                              False)
    repo.createLocalTime3dCrs("", "Default local time CRS",
                              1.0, 0.1, 15, .0,
                              fesapi.eml20__LengthUom__m, 23031,
                              fesapi.eml20__TimeUom__s, fesapi.eml20__LengthUom__m, "Unknown",
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

def show_all_metadata(data_object):
    """
    Show all metadata of a dataobject
    """
    print("Title is : " + data_object.getTitle())
    print("Guid is : " + data_object.getUuid())
    if not data_object.isPartial():
        print("Creation date is (unix timestamp) : ",
              datetime.fromtimestamp(data_object.getCreation()))
    else:
        print("IS PARTIAL!")

def show_ijk_grid(ijk_grid):
    """
    This function shows some ijk grids which have been deserialized
    """
    show_all_metadata(ijk_grid)

    if ijk_grid.getGeometryKind() != fesapi.resqml2_AbstractIjkGridRepresentation.NO_GEOMETRY:
        most_complex_pillar_geom = ijk_grid.getMostComplexPillarGeometry()
        if most_complex_pillar_geom == fesapi.resqml20__PillarShape__vertical:
            print("Most complex pillar geometry is vertical")
        else:
            if most_complex_pillar_geom == fesapi.resqml20__PillarShape__straight:
                print("Most complex pillar geometry is straight")
            else:
                if most_complex_pillar_geom == fesapi.resqml20__PillarShape__curved:
                    print("Most complex pillar geometry is curved")

        k_gap_count = ijk_grid.getKGapsCount()
        print("K Gap Count = ", k_gap_count)

        if ijk_grid.getGeometryKind() == fesapi.resqml2_AbstractIjkGridRepresentation.LATTICE:
            print("This 3d grid has a lattice geometry.")
        else:
            if ijk_grid.getGeometryKind() == \
               fesapi.resqml2_AbstractIjkGridRepresentation.PARAMETRIC:
                print("This 3d grid has a parametric geometry.")
            else:
                if ijk_grid.getGeometryKind() == \
                   fesapi.resqml2_AbstractIjkGridRepresentation.EXPLICIT:
                    print("This 3d grid has an explicit geometry.")
                else:
                    print("This 3d grid has an unknown geometry.")
                    
        patch_count = ijk_grid.getPatchCount()
        print("Patch Count =", patch_count)

        nb_xyz_points = ijk_grid.getXyzPointCountOfAllPatches()
        print("XYZ points count :", nb_xyz_points)
        
        for patch_index in range(patch_count):
            nb_xyz_points_in_patch = ijk_grid.getXyzPointCountOfPatch(patch_index)
            xyz_points_in_patch = fesapi.DoubleArray(nb_xyz_points_in_patch * 3)
            ijk_grid.getXyzPointsOfPatch(patch_index, xyz_points_in_patch)
            for vertex_index in range(nb_xyz_points_in_patch):
                x = xyz_points_in_patch.getitem(vertex_index * 3)
                y = xyz_points_in_patch.getitem(vertex_index * 3 + 1)
                z = xyz_points_in_patch.getitem(vertex_index * 3 + 2)
                print("Vertex ", vertex_index, " : ", x, " ", y, " ", z)
        
        xyz_points = fesapi.DoubleArray(nb_xyz_points * 3)
        ijk_grid.getXyzPointsOfAllPatches(xyz_points)
        
        ijk_grid.loadSplitInformation()
        for cell_corner in range(8):
            pt_index = ijk_grid.getXyzPointIndexFromCellCorner(0, 0, 0, cell_corner)
            print("Cell 0,0,0 corner ", cell_corner, " is at index ", pt_index)
            print("Cell 0,0,0 corner ", cell_corner, " is  ", xyz_points.getitem(pt_index * 3), " ", xyz_points.getitem(pt_index * 3 + 1), " ", xyz_points.getitem(pt_index * 3 + 2))
        ijk_grid.unloadSplitInformation();

    else:
        print("This 3d grid has no geometry.")

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
    epc_file.close()

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

    ijk_grid_count = repo.getIjkGridRepresentationCount()
    for ijk_grid_index in range(ijk_grid_count):
        show_ijk_grid(repo.getIjkGridRepresentation(ijk_grid_index))

serialize("./TestingPackagePython")
deserialize("./TestingPackagePython")
