from datetime import datetime
import fesapi

def serialize_grid(repo: fesapi.DataObjectRepository):
    """
    This function creates a one cell grid + a property on a partial ijk grid in the repo to be serialized
    """
    earth_model = repo.createEarthModel("f2060ce0-fa3d-11e5-8620-0002a5d5c51b", "Grid")
    earth_model_interp = repo.createEarthModelInterpretation(
        earth_model, "f5cd7520-fa3d-11e5-b65b-0002a5d5c51b", "Grid interp")

    # ONE CELL GRID
    single_cell_ijk_grid = repo.createIjkGridExplicitRepresentation(
        earth_model_interp, "e69bfe00-fa3d-11e5-b5eb-0002a5d5c51b", "One unfaulted sugar cube",
        1, 1, 1)
    python_points = [0.0, 0.0, 300.0, 700.0, 0.0, 350.0, 0.0, 150.0, 300.0, 700.0, 150.0, 350.0,
                     0.0, 0.0, 500.0, 700.0, 0.0, 550.0, 0.0, 150.0, 500.0, 700.0, 150.0, 550.0]
    resqml_points = fesapi.DoubleArray(24)
    for i, value in enumerate(python_points):
        resqml_points.setitem(i, value)
    single_cell_ijk_grid.setGeometryAsCoordinateLineNodes(
        fesapi.resqml20__PillarShape_vertical, fesapi.resqml20__KDirection_down, False,
        resqml_points.cast())

    # ONE CONTINUOUS PROPERTY ON A PARTIAL 3 cells I=1 J=1 K=3 GRID
    partial_ijk_grid = repo.createPartialIjkGridRepresentation("bc92a216-aa17-4a1f-9253-8b3ab094bf84", "partial grid")
    continuous_prop = repo.createContinuousProperty(partial_ijk_grid, "827d1074-5b16-4c7d-80bb-a8f3e1413753", "My length property", 1, fesapi.eml23__IndexableElement_cells,
        fesapi.resqml20__ResqmlUom_m, fesapi.resqml20__ResqmlPropertyKind_length)
    prop_values = [1.1, 2.2, 3.3]
    resqml_values = fesapi.FloatArray(3)
    for i, value in enumerate(prop_values):
        resqml_values.setitem(i, value)
    stats = fesapi.FloatArrayStatistics()
    stats.setMaximum(3.3)
    stats.setMinimum(1.1)
    continuous_prop.pushBackFloatArray3dOfValuesPlusStatistics(resqml_values.cast(), 1, 1, 3, stats)

    # A time series definition
    time_series = repo.createTimeSeries("1187d8a0-fa3e-11e5-ac3a-0002a5d5c51b", "Testing time series 1")
    time_series.pushBackTimestamp(1409753895)
    time_series.pushBackTimestamp(1441289895)

    # A continuous property with time series
    continuous_prop_time0 = repo.createContinuousProperty(partial_ijk_grid, "18027a00-fa3e-11e5-8255-0002a5d5c51b", "Time Series Property", 1,
                                                          fesapi.eml23__IndexableElement_cells, fesapi.resqml20__ResqmlUom_m, fesapi.resqml20__ResqmlPropertyKind_length)
    continuous_prop_time0.setTimeSeries(time_series)
    continuous_prop_time0.setSingleTimestamp(time_series.getTimestamp(0))
    continuous_prop_time0.pushBackFloatArray3dOfValues(resqml_values.cast(), 1, 1, 3)

    continuous_prop_time1= repo.createContinuousProperty(partial_ijk_grid, "1ba54340-fa3e-11e5-9534-0002a5d5c51b", "Time Series Property", 1,
                                                          fesapi.eml23__IndexableElement_cells, fesapi.resqml20__ResqmlUom_m, fesapi.resqml20__ResqmlPropertyKind_length)
    continuous_prop_time1.setTimeSeries(time_series)
    continuous_prop_time1.setSingleTimestamp(1441289895)
    continuous_prop_time1.pushBackFloatArray3dOfValues(resqml_values.cast(), 1, 1, 3)

    # unstructured grid example
    unstructured_grid = repo.createUnstructuredGridRepresentation(
        "9283cd33-5e52-4110-b7b1-616abde2b303",
        "One tetrahedron + prism grid",
        2
    )
    python_points = [0, 0, 300, 375, 0, 300, 0, 150, 300, # points for shared face between tetra and wedge
		0, 0, 500, # point for tetra
		0, 0, 0, 375, 0, 0, 0, 150, 0]
    resqml_points = fesapi.DoubleArray(21)
    for i, value in enumerate(python_points):
        resqml_points.setitem(i, value)
    python_node_indices_per_face = [0, 1, 2, # shared face
		1, 2, 3, 0, 1, 3, 0, 2, 3, # faces for tetra
		0, 2, 6, 4, 2, 1, 5, 6, 0, 1, 5, 4, 4, 5, 6] # faces for wedge
    resqml_node_indices_per_face = fesapi.UInt64Array(27)
    for i, value in enumerate(python_node_indices_per_face):
        resqml_node_indices_per_face.setitem(i, value)
    python_node_indices_cumulative_count_per_face = [3, # shared face
		6, 9, 12, # faces for tetra
		16, 20, 24, 27] # faces for wedge
    resqml_node_indices_cumulative_count_per_face = fesapi.UInt64Array(8)
    for i, value in enumerate(python_node_indices_cumulative_count_per_face):
        resqml_node_indices_cumulative_count_per_face.setitem(i, value)
    python_face_indices_per_cell = [0, 1, 2, 3, # tetra
		0, 4, 5, 6, 7] # wedge
    resqml_face_indices_per_cell = fesapi.UInt64Array(9)
    for i, value in enumerate(python_face_indices_per_cell):
        resqml_face_indices_per_cell.setitem(i, value)
    python_face_indices_cumulative_count_per_cell = [ 4, 9 ];
    resqml_face_indices_cumulative_count_per_cell = fesapi.UInt64Array(2)
    for i, value in enumerate(python_face_indices_cumulative_count_per_cell):
        resqml_face_indices_cumulative_count_per_cell.setitem(i, value)
    python_face_right_handness = [ 1, 0, 0, 1, 0, 0, 0, 1, 1 ];
    resqml_face_right_handness = fesapi.UInt8Array(9)
    for i, value in enumerate(python_face_right_handness):
        resqml_face_right_handness.setitem(i, value)
    unstructured_grid.setGeometry(resqml_face_right_handness.cast(), resqml_points.cast(), 7, None, resqml_face_indices_per_cell.cast(), resqml_face_indices_cumulative_count_per_cell.cast(), 8,
                                  resqml_node_indices_per_face.cast(), resqml_node_indices_cumulative_count_per_face.cast(), fesapi.resqml20__CellShape_prism);


def serialize(file_name: str):
    """
    This function serializes an EPC document
    """
    epc_file = fesapi.EpcDocument(file_name + ".epc")
    repo = fesapi.DataObjectRepository()

    # CRS
    print(type(fesapi.eml20__LengthUom_m))
    local_3d_crs = repo.createLocalDepth3dCrs("798d47d8-0c7d-4f12-8c44-0f36b6d16c32", "Default CRS",
                                              0.0, 0.0, 0.0, 0.0,
                                              fesapi.eml20__LengthUom_m, 5215,
                                              fesapi.eml20__LengthUom_m, "Unknown",
                                              False)
    repo.createLocalTime3dCrs("", "Default local time CRS",
                              1.0, 0.1, 15, .0,
                              fesapi.eml20__LengthUom_m, 23031,
                              fesapi.eml20__TimeUom_s, fesapi.eml20__LengthUom_m, "Unknown",
                              False)
    repo.setDefaultCrs(local_3d_crs)

    # HdfProxy
    hdf_proxy = repo.createHdfProxy("798d47d8-0c7d-4f12-8c44-0f36b6d16c33", "Hdf Proxy",
                                    ".", file_name + ".h5",
                                    fesapi.DataObjectRepository.openingMode_OVERWRITE)
    repo.setDefaultHdfProxy(hdf_proxy)

    serialize_grid(repo)

    epc_file.serializeFrom(repo)

def show_all_metadata(data_object: fesapi.AbstractObject):
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

def show_ijk_grid(ijk_grid: fesapi.Resqml2_AbstractIjkGridRepresentation):
    """
    This function shows some ijk grids which have been deserialized
    """
    show_all_metadata(ijk_grid)
    if ijk_grid.isPartial():
        return

    if ijk_grid.getGeometryKind() != fesapi.Resqml2_AbstractIjkGridRepresentation.geometryKind_NO_GEOMETRY:
        most_complex_pillar_geom = ijk_grid.getMostComplexPillarGeometry()
        if most_complex_pillar_geom == fesapi.resqml20__PillarShape_vertical:
            print("Most complex pillar geometry is vertical")
        else:
            if most_complex_pillar_geom == fesapi.resqml20__PillarShape_straight:
                print("Most complex pillar geometry is straight")
            else:
                if most_complex_pillar_geom == fesapi.resqml20__PillarShape_curved:
                    print("Most complex pillar geometry is curved")

        k_gap_count = ijk_grid.getKGapsCount()
        print("K Gap Count = ", k_gap_count)

        if ijk_grid.getGeometryKind() == fesapi.Resqml2_AbstractIjkGridRepresentation.geometryKind_LATTICE:
            print("This 3d grid has a lattice geometry.")
        else:
            if ijk_grid.getGeometryKind() == \
               fesapi.Resqml2_AbstractIjkGridRepresentation.geometryKind_PARAMETRIC:
                print("This 3d grid has a parametric geometry.")
            else:
                if ijk_grid.getGeometryKind() == \
                   fesapi.Resqml2_AbstractIjkGridRepresentation.geometryKind_EXPLICIT:
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
            ijk_grid.getXyzPointsOfPatch(patch_index, xyz_points_in_patch.cast())
            for vertex_index in range(nb_xyz_points_in_patch):
                x = xyz_points_in_patch.getitem(vertex_index * 3)
                y = xyz_points_in_patch.getitem(vertex_index * 3 + 1)
                z = xyz_points_in_patch.getitem(vertex_index * 3 + 2)
                print("Vertex ", vertex_index, " : ", x, " ", y, " ", z)

        xyz_points = fesapi.DoubleArray(nb_xyz_points * 3)
        ijk_grid.getXyzPointsOfAllPatches(xyz_points.cast())

        ijk_grid.loadSplitInformation()
        for cell_corner in range(8):
            pt_index = ijk_grid.getXyzPointIndexFromCellCorner(0, 0, 0, cell_corner)
            print("Cell 0,0,0 corner ", cell_corner, " is at index ", pt_index)
            print("Cell 0,0,0 corner ", cell_corner, " is  ", xyz_points.getitem(pt_index * 3), " ", xyz_points.getitem(pt_index * 3 + 1), " ", xyz_points.getitem(pt_index * 3 + 2))
        ijk_grid.unloadSplitInformation();

    else:
        print("This 3d grid has no geometry.")

def deserialize(file_name: str):
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
    for crs_index in range(repo.getLocal3dCrsCount()):
        crs = repo.getLocal3dCrs(crs_index)
        print("Title is : " + crs.getTitle())
        if crs.isProjectedCrsDefinedWithEpsg():
            print("Projected : EPSG " + str(crs.getProjectedCrsEpsgCode()))
        else:
            if crs.isProjectedCrsUnknown():
                print("Projected : Unknown. Reason is:" + crs.getProjectedCrsUnknownReason())
        if crs.isATimeCrs():
            print("It is a time CRS")
        else:
            print("It is a depth CRS")

    ijk_grid_count = repo.getIjkGridRepresentationCount()
    for ijk_grid_index in range(ijk_grid_count):
        show_ijk_grid(repo.getIjkGridRepresentation(ijk_grid_index))

serialize("./TestingPackagePython")
deserialize("./TestingPackagePython")
