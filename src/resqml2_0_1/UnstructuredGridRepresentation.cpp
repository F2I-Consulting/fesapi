/*-----------------------------------------------------------------------
Licensed to the Apache Software Foundation (ASF) under one
or more contributor license agreements.  See the NOTICE file
distributed with this work for additional information
regarding copyright ownership.  The ASF licenses this file
to you under the Apache License, Version 2.0 (the
"License"; you may not use this file except in compliance
with the License.  You may obtain a copy of the License at

  http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing,
software distributed under the License is distributed on an
"AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
KIND, either express or implied.  See the License for the
specific language governing permissions and limitations
under the License.
-----------------------------------------------------------------------*/

#include "resqml2_0_1/UnstructuredGridRepresentation.h"

#include <stdexcept>

#include "hdf5.h"

#include "resqml2/AbstractFeatureInterpretation.h"
#include "resqml2/AbstractLocal3dCrs.h"
#include "common/AbstractHdfProxy.h"

using namespace std;
using namespace gsoap_resqml2_0_1;
using namespace RESQML2_0_1_NS;

const char* UnstructuredGridRepresentation::XML_TAG = "UnstructuredGridRepresentation";


void UnstructuredGridRepresentation::init(soap* soapContext, RESQML2_NS::AbstractLocal3dCrs * crs,
			const std::string & guid, const std::string & title,
			const ULONG64 & cellCount)
{
	if (soapContext == nullptr) {
		throw invalid_argument("The soap context cannot be null.");
	}
	if (crs == nullptr) {
		throw invalid_argument("The local CRS of the unstructured grid cannot be null.");
	}

	gsoapProxy2_0_1 = soap_new_resqml2__obj_USCOREUnstructuredGridRepresentation(soapContext, 1);
	_resqml2__UnstructuredGridRepresentation* unstructuredGrid = getSpecializedGsoapProxy();

	unstructuredGrid->CellCount = cellCount;

	initMandatoryMetadata();
	setMetadata(guid, title, std::string(), -1, std::string(), std::string(), -1, std::string());

	// relationhsips
	localCrs = crs;
	localCrs->addRepresentation(this);
}

UnstructuredGridRepresentation::UnstructuredGridRepresentation(soap* soapContext, RESQML2_NS::AbstractLocal3dCrs * crs,
	const std::string & guid, const std::string & title,
	const ULONG64 & cellCount):
	AbstractGridRepresentation(nullptr, crs, false), constantNodeCountPerFace(0), constantFaceCountPerCell(0),
	cumulativeNodeCountPerFace(nullptr), cumulativeFaceCountPerCell(nullptr),
	nodeIndicesOfFaces(nullptr), faceIndicesOfCells(nullptr)
{
	init(soapContext, crs, guid, title, cellCount);
}

UnstructuredGridRepresentation::UnstructuredGridRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp, RESQML2_NS::AbstractLocal3dCrs * crs,
	const std::string & guid, const std::string & title,
	const ULONG64 & cellCount):
	AbstractGridRepresentation(interp, crs, false), constantNodeCountPerFace(0), constantFaceCountPerCell(0),
	cumulativeNodeCountPerFace(nullptr), cumulativeFaceCountPerCell(nullptr),
	nodeIndicesOfFaces(nullptr), faceIndicesOfCells(nullptr)
{
	if (interp == nullptr)
		throw invalid_argument("The interpretation of the unstructured grid cannot be null.");

	init(interp->getGsoapContext(), crs, guid, title, cellCount);

	// relationhsips
	setInterpretation(interp);
}

bool UnstructuredGridRepresentation::hasGeometry() const
{
	return getSpecializedGsoapProxy()->Geometry != nullptr;
}

_resqml2__UnstructuredGridRepresentation* UnstructuredGridRepresentation::getSpecializedGsoapProxy() const
{
	if (isPartial()) {
		throw logic_error("Partial object");
	}

	return static_cast<_resqml2__UnstructuredGridRepresentation*>(gsoapProxy2_0_1);
}

gsoap_resqml2_0_1::resqml2__PointGeometry* UnstructuredGridRepresentation::getPointGeometry2_0_1(const unsigned int & patchIndex) const
{
	if (patchIndex == 0) {
		return getSpecializedGsoapProxy()->Geometry;
	}
	
	return nullptr;
}

string UnstructuredGridRepresentation::getHdfProxyUuid() const
{
	return getHdfProxyUuidFromPointGeometryPatch(getPointGeometry2_0_1(0));
}

ULONG64 UnstructuredGridRepresentation::getCellCount() const
{
	return getSpecializedGsoapProxy()->CellCount;
}

ULONG64 UnstructuredGridRepresentation::getFaceCount() const
{
	_resqml2__UnstructuredGridRepresentation* grid = getSpecializedGsoapProxy();
	if (grid->Geometry != nullptr) {
		return grid->Geometry->FaceCount;
	}
	
	return 0;
}

ULONG64 UnstructuredGridRepresentation::getNodeCount() const
{
	_resqml2__UnstructuredGridRepresentation* grid = getSpecializedGsoapProxy();
	if (grid->Geometry != nullptr) {
		return grid->Geometry->NodeCount;
	}

	return 0;
}

ULONG64 UnstructuredGridRepresentation::getXyzPointCountOfPatch(const unsigned int & patchIndex) const
{
	if (patchIndex >= getPatchCount()) {
		throw range_error("The index of the patch is not in the allowed range of patch.");
	}

	return getNodeCount();
}

void UnstructuredGridRepresentation::getXyzPointsOfPatch(const unsigned int & patchIndex, double * xyzPoints) const
{
	if (patchIndex >= getPatchCount()) {
		throw range_error("The index of the patch is not in the allowed range of patch.");
	}

	resqml2__PointGeometry* pointGeom = getPointGeometry2_0_1(patchIndex);
	if (pointGeom != nullptr && pointGeom->Points->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__Point3dHdf5Array) {
		hdfProxy->readArrayNdOfDoubleValues(static_cast<resqml2__Point3dHdf5Array*>(pointGeom->Points)->Coordinates->PathInHdfFile, xyzPoints);
	}
	else {
		throw invalid_argument("The geometry of the representation either does not exist or it is not an explicit one.");
	}
}

void UnstructuredGridRepresentation::getFaceIndicesOfCells(ULONG64 * faceIndices) const
{
	_resqml2__UnstructuredGridRepresentation* grid = getSpecializedGsoapProxy();
	if (grid->Geometry == nullptr) {
		throw invalid_argument("There is no geometry in this grid.");
	}
	if (grid->Geometry->FacesPerCell->Elements->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__IntegerHdf5Array) {
		hdfProxy->readArrayNdOfGSoapULong64Values(static_cast<resqml2__IntegerHdf5Array*>(grid->Geometry->FacesPerCell->Elements)->Values->PathInHdfFile, faceIndices);	
	}
	else {
		throw logic_error("Not yet implemented");
	}
}

void UnstructuredGridRepresentation::getCumulativeFaceCountPerCell(ULONG64 * cumulativeFaceCountPerCell) const
{
	_resqml2__UnstructuredGridRepresentation* grid = getSpecializedGsoapProxy();
	if (grid->Geometry == nullptr)
		throw invalid_argument("There is no geometry in this grid.");
	if (grid->Geometry->FacesPerCell->CumulativeLength->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__IntegerHdf5Array)
	{
		hdfProxy->readArrayNdOfGSoapULong64Values(static_cast<resqml2__IntegerHdf5Array*>(grid->Geometry->FacesPerCell->CumulativeLength)->Values->PathInHdfFile, cumulativeFaceCountPerCell);
	}
	else if (grid->Geometry->FacesPerCell->CumulativeLength->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__IntegerLatticeArray)
	{
		cumulativeFaceCountPerCell[0] = static_cast<resqml2__IntegerLatticeArray*>(grid->Geometry->FacesPerCell->CumulativeLength)->StartValue;
		const LONG64 offsetValue = static_cast<resqml2__IntegerLatticeArray*>(grid->Geometry->FacesPerCell->CumulativeLength)->Offset[0]->Value;
		const ULONG64 cellCount = getCellCount();
		for (ULONG64 cumulativeFaceCountPerCellIndex = 1; cumulativeFaceCountPerCellIndex < cellCount; ++cumulativeFaceCountPerCellIndex)
		{
			cumulativeFaceCountPerCell[cumulativeFaceCountPerCellIndex] = cumulativeFaceCountPerCell[cumulativeFaceCountPerCellIndex - 1] + offsetValue;
		}
	}
	else if (grid->Geometry->FacesPerCell->CumulativeLength->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__IntegerConstantArray)
	{
		if (getCellCount() > 1)
			throw range_error("The cumulative length of faces count per cells cannot be constant if there is more than one cell in the grid");
		cumulativeFaceCountPerCell[0] = static_cast<resqml2__IntegerConstantArray*>(grid->Geometry->FacesPerCell->CumulativeLength)->Value;
	}
}

void UnstructuredGridRepresentation::getFaceCountPerCell(ULONG64 * faceCountPerCell) const
{
	getCumulativeFaceCountPerCell(faceCountPerCell);
	const ULONG64 cellCount = getCellCount();
	ULONG64 buffer = faceCountPerCell[0];
	ULONG64 bufferCumCount = 0;
	for (ULONG64 cumulativeFaceCountPerCellIndex = 1; cumulativeFaceCountPerCellIndex < cellCount; ++cumulativeFaceCountPerCellIndex)
	{
		bufferCumCount = faceCountPerCell[cumulativeFaceCountPerCellIndex];
		faceCountPerCell[cumulativeFaceCountPerCellIndex] -= buffer;
		buffer = bufferCumCount;
	}
}

bool UnstructuredGridRepresentation::isFaceCountOfCellsConstant() const
{
	_resqml2__UnstructuredGridRepresentation* grid = getSpecializedGsoapProxy();
	if (grid->Geometry == nullptr)
		throw invalid_argument("There is no geometry in this grid.");
	if (grid->Geometry->CellShape == resqml2__CellShape__hexahedral || grid->Geometry->CellShape == resqml2__CellShape__tetrahedral)
	{
		return true;
	}
	else if (grid->Geometry->FacesPerCell->CumulativeLength->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__IntegerLatticeArray)
	{
		if (static_cast<resqml2__IntegerLatticeArray*>(grid->Geometry->FacesPerCell->CumulativeLength)->StartValue == static_cast<resqml2__IntegerLatticeArray*>(grid->Geometry->FacesPerCell->CumulativeLength)->Offset[0]->Value)
			return true;
	}
	else if (grid->Geometry->FacesPerCell->CumulativeLength->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__IntegerConstantArray)
	{
		if (getCellCount() > 1)
			throw range_error("The cumulative length of faces count per cells cannot be constant if there is more than one cell in the grid");
		return true;
	}

	return false;
}

unsigned int UnstructuredGridRepresentation::getConstantFaceCountOfCells() const
{
	_resqml2__UnstructuredGridRepresentation* grid = getSpecializedGsoapProxy();
	if (!isFaceCountOfCellsConstant())
		throw invalid_argument("The face count per cell is not constant.");

	if (grid->Geometry->CellShape == resqml2__CellShape__hexahedral)
	{
		return 6;
	}
	else if (grid->Geometry->CellShape == resqml2__CellShape__tetrahedral)
	{
		return 4;
	}
	else if (grid->Geometry->FacesPerCell->CumulativeLength->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__IntegerLatticeArray)
	{
		return static_cast<resqml2__IntegerLatticeArray*>(grid->Geometry->FacesPerCell->CumulativeLength)->StartValue;
	}
	else if (grid->Geometry->FacesPerCell->CumulativeLength->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__IntegerConstantArray)
	{
		if (getCellCount() > 1)
			throw range_error("The cumulative length of faces count per cells cannot be constant if there is more than one cell in the grid");
		return static_cast<resqml2__IntegerConstantArray*>(grid->Geometry->FacesPerCell->CumulativeLength)->Value;
	}
	else
		return 0;
}

void UnstructuredGridRepresentation::getNodeIndicesOfFaces(ULONG64 * nodeIndices) const
{
	_resqml2__UnstructuredGridRepresentation* grid = getSpecializedGsoapProxy();
	if (grid->Geometry == nullptr)
		throw invalid_argument("There is no geometry in this grid.");
	if (grid->Geometry->NodesPerFace->Elements->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__IntegerHdf5Array)
	{
		hdfProxy->readArrayNdOfGSoapULong64Values(static_cast<resqml2__IntegerHdf5Array*>(grid->Geometry->NodesPerFace->Elements)->Values->PathInHdfFile, nodeIndices);
	}
	else
		throw logic_error("Not yet implemented");
}

void UnstructuredGridRepresentation::getCumulativeNodeCountPerFace(ULONG64 * nodeCountPerFace) const
{
	_resqml2__UnstructuredGridRepresentation* grid = getSpecializedGsoapProxy();
		if (grid->Geometry == nullptr)
			throw invalid_argument("There is no geometry in this grid.");
	if (grid->Geometry->NodesPerFace->CumulativeLength->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__IntegerHdf5Array)
	{
		hdfProxy->readArrayNdOfGSoapULong64Values(static_cast<resqml2__IntegerHdf5Array*>(grid->Geometry->NodesPerFace->CumulativeLength)->Values->PathInHdfFile, nodeCountPerFace);
	}
	else if (grid->Geometry->NodesPerFace->CumulativeLength->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__IntegerLatticeArray)
	{
		nodeCountPerFace[0] = static_cast<resqml2__IntegerLatticeArray*>(grid->Geometry->NodesPerFace->CumulativeLength)->StartValue;
		const LONG64 offsetValue = static_cast<resqml2__IntegerLatticeArray*>(grid->Geometry->NodesPerFace->CumulativeLength)->Offset[0]->Value;
		const ULONG64 faceCount = getFaceCount();
		for (ULONG64 nodeCountPerFaceIndex = 1; nodeCountPerFaceIndex < faceCount; ++nodeCountPerFaceIndex)
		{
			nodeCountPerFace[nodeCountPerFaceIndex] = nodeCountPerFace[nodeCountPerFaceIndex - 1] + offsetValue;
		}
	}
	else if (grid->Geometry->NodesPerFace->CumulativeLength->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__IntegerConstantArray)
	{
		throw range_error("The *cumulative* length of nodes count per cells cannot be constant.");
	}
}

void UnstructuredGridRepresentation::getNodeCountPerFace(ULONG64 * nodeCountPerFace) const
{
	getCumulativeNodeCountPerFace(nodeCountPerFace);
	const ULONG64 faceCount = getFaceCount();
	ULONG64 buffer = nodeCountPerFace[0];
	ULONG64 bufferCumCount = 0;
	for (ULONG64 cumulativeNodeCountPerFaceIndex = 1; cumulativeNodeCountPerFaceIndex < faceCount; ++cumulativeNodeCountPerFaceIndex)
	{
		bufferCumCount = nodeCountPerFace[cumulativeNodeCountPerFaceIndex];
		nodeCountPerFace[cumulativeNodeCountPerFaceIndex] -= buffer;
		buffer = bufferCumCount;
	}
}

bool UnstructuredGridRepresentation::isNodeCountOfFacesConstant() const
{
	_resqml2__UnstructuredGridRepresentation* grid = getSpecializedGsoapProxy();
	if (grid->Geometry == nullptr)
		throw invalid_argument("There is no geometry in this grid.");
	if (grid->Geometry->CellShape == resqml2__CellShape__hexahedral || grid->Geometry->CellShape == resqml2__CellShape__tetrahedral)
	{
		return true;
	}
	else if (grid->Geometry->NodesPerFace->CumulativeLength->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__IntegerLatticeArray)
	{
		if (static_cast<resqml2__IntegerLatticeArray*>(grid->Geometry->NodesPerFace->CumulativeLength)->StartValue == static_cast<resqml2__IntegerLatticeArray*>(grid->Geometry->NodesPerFace->CumulativeLength)->Offset[0]->Value)
			return true;
	}

	return false;
}

unsigned int UnstructuredGridRepresentation::getConstantNodeCountOfFaces() const
{
	_resqml2__UnstructuredGridRepresentation* grid = getSpecializedGsoapProxy();
	if (isNodeCountOfFacesConstant() == false)
		throw invalid_argument("The node count per cell is not constant.");

	if (grid->Geometry->CellShape == resqml2__CellShape__hexahedral)
	{
		return 4;
	}
	else if (grid->Geometry->CellShape == resqml2__CellShape__tetrahedral)
	{
		return 3;
	}
	else if (grid->Geometry->NodesPerFace->CumulativeLength->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__IntegerLatticeArray)
	{
		return static_cast<resqml2__IntegerLatticeArray*>(grid->Geometry->NodesPerFace->CumulativeLength)->StartValue;
	}
	else
		return 0;
}

void UnstructuredGridRepresentation::getCellFaceIsRightHanded(unsigned char* cellFaceIsRightHanded) const
{
  _resqml2__UnstructuredGridRepresentation* grid = getSpecializedGsoapProxy();
  if (grid->Geometry == nullptr)
    throw invalid_argument("There is no geometry in this grid.");
  if (grid->Geometry->CellFaceIsRightHanded->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__BooleanHdf5Array)
  {
    hdfProxy->readArrayNdOfUCharValues(static_cast<resqml2__BooleanHdf5Array*>(grid->Geometry->CellFaceIsRightHanded)->Values->PathInHdfFile, cellFaceIsRightHanded);
  }
  else if (grid->Geometry->CellFaceIsRightHanded->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__BooleanConstantArray)
  {
	  for (size_t i = 0; i < static_cast<resqml2__BooleanConstantArray*>(grid->Geometry->CellFaceIsRightHanded)->Count; ++i)
	  {
		  cellFaceIsRightHanded[i] = static_cast<resqml2__BooleanConstantArray*>(grid->Geometry->CellFaceIsRightHanded)->Value;
	  }
  }
  else
	  throw logic_error("Not yet implemented.");
}

void UnstructuredGridRepresentation::setGeometryUsingExistingDatasets(const std::string& cellFaceIsRightHanded, const std::string& points, ULONG64 pointCount, COMMON_NS::AbstractHdfProxy* proxy,
	const std::string& faceIndicesPerCell, const std::string&faceIndicesCumulativeCountPerCell,
	ULONG64 faceCount, const std::string& nodeIndicesPerFace, const std::string& nodeIndicesCumulativeCountPerFace,
	const gsoap_resqml2_0_1::resqml2__CellShape & cellShape)
{
	if (cellFaceIsRightHanded.empty())
		throw invalid_argument("The cellFaceIsRightHanded dataset path information cannot be empty.");
	if (proxy == nullptr)
		throw invalid_argument("The hdf proxy cannot be null.");
	if (points.empty())
		throw invalid_argument("The points dataset path of the ijk grid cannot be null.");
	if (faceIndicesPerCell.empty())
		throw invalid_argument("The dataset path of the face indices per cell is incomplete.");
	if (faceIndicesCumulativeCountPerCell.empty())
		throw invalid_argument("The dataset path of the face indices count per cell is incomplete.");
	if (nodeIndicesPerFace.empty())
		throw invalid_argument("The dataset path of the node indices per face is incomplete.");
	if (nodeIndicesCumulativeCountPerFace.empty())
		throw invalid_argument("The dataset path of the node indices count per face is incomplete.");

	setHdfProxy(proxy);

	resqml2__UnstructuredGridGeometry* geom = soap_new_resqml2__UnstructuredGridGeometry(gsoapProxy2_0_1->soap, 1);
	getSpecializedGsoapProxy()->Geometry = geom;
	getSpecializedGsoapProxy()->Geometry->LocalCrs = localCrs->newResqmlReference();

	geom->FaceCount = faceCount;
	geom->NodeCount = pointCount;
	geom->CellShape = cellShape;

	// Face Right handness
	//XML
	resqml2__BooleanHdf5Array* cellFaceIsRightHandedForHdf5 = soap_new_resqml2__BooleanHdf5Array(gsoapProxy2_0_1->soap, 1);
	cellFaceIsRightHandedForHdf5->Values = soap_new_eml20__Hdf5Dataset(gsoapProxy2_0_1->soap, 1);
	cellFaceIsRightHandedForHdf5->Values->HdfProxy = proxy->newResqmlReference();
	cellFaceIsRightHandedForHdf5->Values->PathInHdfFile = cellFaceIsRightHanded;
	geom->CellFaceIsRightHanded = cellFaceIsRightHandedForHdf5;

	// Face indices
	//XML
	geom->FacesPerCell = soap_new_resqml2__ResqmlJaggedArray(gsoapProxy2_0_1->soap, 1);
	// Cumulative
	resqml2__IntegerHdf5Array* cumulativeLength = soap_new_resqml2__IntegerHdf5Array(gsoapProxy2_0_1->soap, 1);
	geom->FacesPerCell->CumulativeLength = cumulativeLength;
	cumulativeLength->NullValue = -1;
	cumulativeLength->Values = soap_new_eml20__Hdf5Dataset(gsoapProxy2_0_1->soap, 1);
	cumulativeLength->Values->HdfProxy = proxy->newResqmlReference();
	cumulativeLength->Values->PathInHdfFile = faceIndicesCumulativeCountPerCell;
	// Elements
	resqml2__IntegerHdf5Array* elements = soap_new_resqml2__IntegerHdf5Array(gsoapProxy2_0_1->soap, 1);
	geom->FacesPerCell->Elements = elements;
	elements->NullValue = faceCount+1;
	elements->Values = soap_new_eml20__Hdf5Dataset(gsoapProxy2_0_1->soap, 1);
	elements->Values->HdfProxy = proxy->newResqmlReference();
	elements->Values->PathInHdfFile = faceIndicesPerCell;

	// Node indices
	//XML
	geom->NodesPerFace = soap_new_resqml2__ResqmlJaggedArray(gsoapProxy2_0_1->soap, 1);
	// Cumulative
	cumulativeLength = soap_new_resqml2__IntegerHdf5Array(gsoapProxy2_0_1->soap, 1);
	geom->NodesPerFace->CumulativeLength = cumulativeLength;
	cumulativeLength->NullValue = -1;
	cumulativeLength->Values = soap_new_eml20__Hdf5Dataset(gsoapProxy2_0_1->soap, 1);
	cumulativeLength->Values->HdfProxy = proxy->newResqmlReference();
	cumulativeLength->Values->PathInHdfFile = nodeIndicesCumulativeCountPerFace;
	// Elements
	elements = soap_new_resqml2__IntegerHdf5Array(gsoapProxy2_0_1->soap, 1);
	geom->NodesPerFace->Elements = elements;
	elements->NullValue = pointCount+1;
	elements->Values = soap_new_eml20__Hdf5Dataset(gsoapProxy2_0_1->soap, 1);
	elements->Values->HdfProxy = proxy->newResqmlReference();
	elements->Values->PathInHdfFile = nodeIndicesPerFace;

	// XML points
	resqml2__Point3dHdf5Array* xmlPoints = soap_new_resqml2__Point3dHdf5Array(gsoapProxy2_0_1->soap, 1);
	geom->Points = xmlPoints;
	xmlPoints->Coordinates = soap_new_eml20__Hdf5Dataset(gsoapProxy2_0_1->soap, 1);
	xmlPoints->Coordinates->HdfProxy = proxy->newResqmlReference();
	xmlPoints->Coordinates->PathInHdfFile = points;
}

void UnstructuredGridRepresentation::setGeometry(unsigned char * cellFaceIsRightHanded, double * points, ULONG64 pointCount, COMMON_NS::AbstractHdfProxy * proxy,
	ULONG64 * faceIndicesPerCell, ULONG64 * faceIndicesCumulativeCountPerCell,
	ULONG64 faceCount, ULONG64 * nodeIndicesPerFace, ULONG64 * nodeIndicesCumulativeCountPerFace,
	const gsoap_resqml2_0_1::resqml2__CellShape & cellShape)
{
	if (cellFaceIsRightHanded == nullptr)
		throw invalid_argument("The cellFaceIsRightHanded information cannot be null.");
	if (points == nullptr)
		throw invalid_argument("The points of the ijk grid cannot be null.");
	if (faceIndicesPerCell == nullptr)
		throw invalid_argument("The definition of the face indices per cell is incomplete.");
	if (faceIndicesCumulativeCountPerCell == nullptr)
		throw invalid_argument("The definition of the face indices count per cell is incomplete.");
	if (nodeIndicesPerFace == nullptr)
		throw invalid_argument("The definition of the node indices per face is incomplete.");
	if (nodeIndicesCumulativeCountPerFace == nullptr)
		throw invalid_argument("The definition of the node indices count per face is incomplete.");

	setGeometryUsingExistingDatasets("/RESQML/" + gsoapProxy2_0_1->uuid + "/CellFaceIsRightHanded", "/RESQML/" + gsoapProxy2_0_1->uuid + "/Points", pointCount, proxy,
		"/RESQML/" + gsoapProxy2_0_1->uuid + "/FacesPerCell/" + ELEMENTS_DS_NAME, "/RESQML/" + gsoapProxy2_0_1->uuid + "/FacesPerCell/" + CUMULATIVE_LENGTH_DS_NAME,
		faceCount, "/RESQML/" + gsoapProxy2_0_1->uuid + "/NodesPerFace/" + ELEMENTS_DS_NAME, "/RESQML/" + gsoapProxy2_0_1->uuid + "/NodesPerFace/" + CUMULATIVE_LENGTH_DS_NAME,
		cellShape);

	ULONG64 cellCount = getSpecializedGsoapProxy()->CellCount;

	// HDF Face Right handness
	unsigned long long faceCountTmp = faceIndicesCumulativeCountPerCell[cellCount - 1]; // For GCC : ULONG64 is not exactly an unsigned long long with GCC but an uint64_t {aka long unsigned int}
	hdfProxy->writeArrayNd(gsoapProxy2_0_1->uuid, "CellFaceIsRightHanded", H5T_NATIVE_UCHAR, cellFaceIsRightHanded, &faceCountTmp, 1);

	// HDF Face indices
	hdfProxy->writeItemizedListOfList(gsoapProxy2_0_1->uuid, "FacesPerCell", H5T_NATIVE_ULLONG, faceIndicesCumulativeCountPerCell, cellCount, H5T_NATIVE_ULLONG, faceIndicesPerCell, faceIndicesCumulativeCountPerCell[cellCount - 1]);

	// HDF Node indices
	hdfProxy->writeItemizedListOfList(gsoapProxy2_0_1->uuid, "NodesPerFace", H5T_NATIVE_ULLONG, nodeIndicesCumulativeCountPerFace, faceCount, H5T_NATIVE_ULLONG, nodeIndicesPerFace, nodeIndicesCumulativeCountPerFace[faceCount - 1]);

	// HDF points
	hsize_t * numValues = new hsize_t[2];
	numValues[0] = pointCount;
	numValues[1] = 3; // 3 for X, Y and Z
	hdfProxy->writeArrayNdOfDoubleValues(gsoapProxy2_0_1->uuid, "Points", points, numValues, 2);
	delete [] numValues;
}

void UnstructuredGridRepresentation::setConstantCellShapeGeometryUsingExistingDatasets(const std::string& cellFaceIsRightHanded, const std::string& points,
	ULONG64 pointCount, ULONG64 faceCount, COMMON_NS::AbstractHdfProxy* proxy,
	const std::string& faceIndicesPerCell, ULONG64 faceCountPerCell,
	const std::string& nodeIndicesPerFace, ULONG64 nodeCountPerFace)
{
	if (cellFaceIsRightHanded.empty())
		throw invalid_argument("The cellFaceIsRightHanded dataset path cannot be empty.");
	if (proxy == nullptr)
		throw invalid_argument("The hdf proxy cannot be null.");
	if (points.empty())
		throw invalid_argument("The points dataset path of the ijk grid cannot be empty.");
	if (faceIndicesPerCell.empty())
		throw invalid_argument("The dataset path of the face indices per cell is incomplete.");
	if (nodeIndicesPerFace.empty())
		throw invalid_argument("The dataset path of the node indices per face is incomplete.");

	setHdfProxy(proxy);
	ULONG64 cellCount = getSpecializedGsoapProxy()->CellCount;

	resqml2__UnstructuredGridGeometry* geom = soap_new_resqml2__UnstructuredGridGeometry(gsoapProxy2_0_1->soap, 1);
	getSpecializedGsoapProxy()->Geometry = geom;
	getSpecializedGsoapProxy()->Geometry->LocalCrs = localCrs->newResqmlReference();

	geom->FaceCount = faceCount;
	geom->NodeCount = pointCount;
	if (nodeCountPerFace == 3 && faceCountPerCell == 4) {
		geom->CellShape = resqml2__CellShape__tetrahedral;
	}
	else if (nodeCountPerFace == 4 && faceCountPerCell == 6) {
		geom->CellShape = resqml2__CellShape__hexahedral;
	}
	else {
		geom->CellShape = resqml2__CellShape__polyhedral;
	}

	// Face Right handness
	//XML
	resqml2__BooleanHdf5Array* cellFaceIsRightHandedForHdf5 = soap_new_resqml2__BooleanHdf5Array(gsoapProxy2_0_1->soap, 1);
	cellFaceIsRightHandedForHdf5->Values = soap_new_eml20__Hdf5Dataset(gsoapProxy2_0_1->soap, 1);
	cellFaceIsRightHandedForHdf5->Values->HdfProxy = proxy->newResqmlReference();
	cellFaceIsRightHandedForHdf5->Values->PathInHdfFile = cellFaceIsRightHanded;
	geom->CellFaceIsRightHanded = cellFaceIsRightHandedForHdf5;

	// Face indices
	//XML
	geom->FacesPerCell = soap_new_resqml2__ResqmlJaggedArray(gsoapProxy2_0_1->soap, 1);
	// Cumulative
	if (cellCount == 1)
	{
		resqml2__IntegerConstantArray* cumulativeLength = soap_new_resqml2__IntegerConstantArray(gsoapProxy2_0_1->soap, 1);
		geom->FacesPerCell->CumulativeLength = cumulativeLength;
		cumulativeLength->Count = cellCount;
		cumulativeLength->Value = faceCountPerCell;
	}
	else
	{
		resqml2__IntegerLatticeArray* cumulativeLength = soap_new_resqml2__IntegerLatticeArray(gsoapProxy2_0_1->soap, 1);
		geom->FacesPerCell->CumulativeLength = cumulativeLength;
		cumulativeLength->StartValue = faceCountPerCell;
		cumulativeLength->Offset.push_back(soap_new_resqml2__IntegerConstantArray(gsoapProxy2_0_1->soap, 1));
		cumulativeLength->Offset[0]->Count = cellCount - 1;
		cumulativeLength->Offset[0]->Value = faceCountPerCell;
	}
	// Elements
	resqml2__IntegerHdf5Array* elements = soap_new_resqml2__IntegerHdf5Array(gsoapProxy2_0_1->soap, 1);
	geom->FacesPerCell->Elements = elements;
	elements->NullValue = faceCount+1;
	elements->Values = soap_new_eml20__Hdf5Dataset(gsoapProxy2_0_1->soap, 1);
	elements->Values->HdfProxy = proxy->newResqmlReference();
	elements->Values->PathInHdfFile = faceIndicesPerCell;

	// Node indices
	//XML
	geom->NodesPerFace = soap_new_resqml2__ResqmlJaggedArray(gsoapProxy2_0_1->soap, 1);
	// Cumulative
	resqml2__IntegerLatticeArray* cumulativeLength = soap_new_resqml2__IntegerLatticeArray(gsoapProxy2_0_1->soap, 1);
	geom->NodesPerFace->CumulativeLength = cumulativeLength;
	cumulativeLength->StartValue = nodeCountPerFace;
	cumulativeLength->Offset.push_back(soap_new_resqml2__IntegerConstantArray(gsoapProxy2_0_1->soap, 1));
	cumulativeLength->Offset[0]->Count = geom->FaceCount - 1;
	cumulativeLength->Offset[0]->Value = nodeCountPerFace;
	// Elements
	elements = soap_new_resqml2__IntegerHdf5Array(gsoapProxy2_0_1->soap, 1);
	geom->NodesPerFace->Elements = elements;
	elements->NullValue = pointCount+1;
	elements->Values = soap_new_eml20__Hdf5Dataset(gsoapProxy2_0_1->soap, 1);
	elements->Values->HdfProxy = proxy->newResqmlReference();
	elements->Values->PathInHdfFile = nodeIndicesPerFace;

	// XML points
	resqml2__Point3dHdf5Array* xmlPoints = soap_new_resqml2__Point3dHdf5Array(gsoapProxy2_0_1->soap, 1);
	geom->Points = xmlPoints;
	xmlPoints->Coordinates = soap_new_eml20__Hdf5Dataset(gsoapProxy2_0_1->soap, 1);
	xmlPoints->Coordinates->HdfProxy = proxy->newResqmlReference();
	xmlPoints->Coordinates->PathInHdfFile = points;
}

void UnstructuredGridRepresentation::setConstantCellShapeGeometry(unsigned char * cellFaceIsRightHanded, double * points,
	ULONG64 pointCount, ULONG64 faceCount, COMMON_NS::AbstractHdfProxy* proxy,
	ULONG64 * faceIndicesPerCell, ULONG64 faceCountPerCell,
	ULONG64 * nodeIndicesPerFace, ULONG64 nodeCountPerFace)
{
	if (cellFaceIsRightHanded == nullptr)
		throw invalid_argument("The cellFaceIsRightHanded information cannot be null.");
	if (points == nullptr)
		throw invalid_argument("The points of the ijk grid cannot be null.");
	if (faceIndicesPerCell == nullptr)
		throw invalid_argument("The definition of the face indices per cell is incomplete.");
	if (nodeIndicesPerFace == nullptr)
		throw invalid_argument("The definition of the node indices per face is incomplete.");

	setConstantCellShapeGeometryUsingExistingDatasets("/RESQML/" + gsoapProxy2_0_1->uuid + "/CellFaceIsRightHanded", "/RESQML/" + gsoapProxy2_0_1->uuid + "/Points",
		pointCount, faceCount, proxy,
		"/RESQML/" + gsoapProxy2_0_1->uuid + "/FacesPerCell", faceCountPerCell,
		"/RESQML/" + gsoapProxy2_0_1->uuid + "/NodesPerFace", nodeCountPerFace);

	setHdfProxy(proxy);
	ULONG64 cellCount = getSpecializedGsoapProxy()->CellCount;

	// HDF Face Right handness
	unsigned long long faceCountTmp = faceCountPerCell * cellCount; // For GCC : ULONG64 is not exactly an unsigned long long with GCC but an uint64_t {aka long unsigned int}
	hdfProxy->writeArrayNd(gsoapProxy2_0_1->uuid, "CellFaceIsRightHanded", H5T_NATIVE_UCHAR, cellFaceIsRightHanded, &faceCountTmp, 1);

	// HDF Face indices
	hsize_t * numValues = new hsize_t[2];
	numValues[0] = cellCount;
	numValues[1] = faceCountPerCell;
	hdfProxy->writeArrayNd(gsoapProxy2_0_1->uuid, "FacesPerCell", H5T_NATIVE_ULLONG, faceIndicesPerCell, numValues, 2);
	delete[] numValues;

	// HDF Node indices
	numValues = new hsize_t[2];
	numValues[0] = faceCount;
	numValues[1] = nodeCountPerFace;
	hdfProxy->writeArrayNd(gsoapProxy2_0_1->uuid, "NodesPerFace", H5T_NATIVE_ULLONG, nodeIndicesPerFace, numValues, 2);
	delete[] numValues;

	// HDF points
	numValues = new hsize_t[2];
	numValues[0] = pointCount;
	numValues[1] = 3; // 3 for X, Y and Z
	hdfProxy->writeArrayNdOfDoubleValues(gsoapProxy2_0_1->uuid, "Points", points, numValues, 2);
	delete[] numValues;
}

void UnstructuredGridRepresentation::setTetrahedraOnlyGeometryUsingExistingDatasets(const std::string& cellFaceIsRightHanded, const std::string& points,
	ULONG64 pointCount, ULONG64 faceCount, COMMON_NS::AbstractHdfProxy* proxy,
	const std::string& faceIndicesPerCell, const std::string& nodeIndicesPerFace)
{
	setConstantCellShapeGeometryUsingExistingDatasets(cellFaceIsRightHanded, points,
		pointCount, faceCount, proxy,
		faceIndicesPerCell, 4,
		nodeIndicesPerFace, 3);
}

void UnstructuredGridRepresentation::setTetrahedraOnlyGeometry(unsigned char * cellFaceIsRightHanded, double * points, ULONG64 pointCount, ULONG64 faceCount, COMMON_NS::AbstractHdfProxy * proxy,
	ULONG64 * faceIndicesPerCell, ULONG64 * nodeIndicesPerFace)
{
	setConstantCellShapeGeometry(cellFaceIsRightHanded, points,
		pointCount, faceCount, proxy,
		faceIndicesPerCell, 4,
		nodeIndicesPerFace, 3);
}

void UnstructuredGridRepresentation::setHexahedraOnlyGeometryUsingExistingDatasets(const std::string& cellFaceIsRightHanded, const std::string& points,
	ULONG64 pointCount, ULONG64 faceCount, COMMON_NS::AbstractHdfProxy* proxy,
	const std::string& faceIndicesPerCell, const std::string& nodeIndicesPerFace)
{
	setConstantCellShapeGeometryUsingExistingDatasets(cellFaceIsRightHanded, points,
		pointCount, faceCount, proxy,
		faceIndicesPerCell, 6,
		nodeIndicesPerFace, 4);
}

void UnstructuredGridRepresentation::setHexahedraOnlyGeometry(unsigned char * cellFaceIsRightHanded, double * points, ULONG64 pointCount, ULONG64 faceCount, COMMON_NS::AbstractHdfProxy * proxy,
	ULONG64 * faceIndicesPerCell, ULONG64 * nodeIndicesPerFace)
{

	setConstantCellShapeGeometry(cellFaceIsRightHanded, points,
		pointCount, faceCount, proxy,
		faceIndicesPerCell, 6,
		nodeIndicesPerFace, 4);
}

void UnstructuredGridRepresentation::loadGeometry()
{
	unloadGeometry();

	if (isNodeCountOfFacesConstant() == true)
	{
		constantNodeCountPerFace = getConstantNodeCountOfFaces();
		nodeIndicesOfFaces = new ULONG64[constantNodeCountPerFace * getFaceCount()];
	}
	else
	{
		cumulativeNodeCountPerFace = new ULONG64[getFaceCount()];
		getCumulativeNodeCountPerFace(cumulativeNodeCountPerFace);
		nodeIndicesOfFaces = new ULONG64[cumulativeNodeCountPerFace[getFaceCount() - 1]];
	}

	if (isFaceCountOfCellsConstant() == true)
	{
		constantFaceCountPerCell = getConstantFaceCountOfCells();
		faceIndicesOfCells = new ULONG64[constantFaceCountPerCell * getCellCount()];
	}
	else
	{
		cumulativeFaceCountPerCell = new ULONG64[getCellCount()];
		getCumulativeFaceCountPerCell(cumulativeFaceCountPerCell);
		faceIndicesOfCells = new ULONG64[cumulativeFaceCountPerCell[getCellCount() - 1]];
	}

	getNodeIndicesOfFaces(nodeIndicesOfFaces);

	getFaceIndicesOfCells(faceIndicesOfCells);
}

void UnstructuredGridRepresentation::unloadGeometry()
{
	constantNodeCountPerFace = 0;
	constantFaceCountPerCell = 0;

  delete[] cumulativeNodeCountPerFace;
  cumulativeNodeCountPerFace = nullptr;
  delete[] cumulativeFaceCountPerCell;
  cumulativeFaceCountPerCell = nullptr;
  delete[] nodeIndicesOfFaces;
  nodeIndicesOfFaces = nullptr;
  delete[] faceIndicesOfCells;
  faceIndicesOfCells = nullptr;
}

unsigned int UnstructuredGridRepresentation::getFaceCountOfCell(const ULONG64 & cellIndex) const
{
	if (cellIndex >= getCellCount())
		throw range_error("The cell index is out of range.");

	if (constantFaceCountPerCell != 0)
		return constantFaceCountPerCell;

	if (faceIndicesOfCells == nullptr)
		throw invalid_argument("The geometry must have been loaded first.");

	if (cellIndex == 0)
		return cumulativeFaceCountPerCell[0];
	
	return cumulativeFaceCountPerCell[cellIndex] -  cumulativeFaceCountPerCell[cellIndex-1];
}

unsigned int UnstructuredGridRepresentation::getNodeCountOfFaceOfCell(const ULONG64 & cellIndex, const unsigned int & localFaceIndex) const
{
	if (cellIndex >= getCellCount())
		throw range_error("The cell index is out of range.");
	if (localFaceIndex >= getFaceCountOfCell(cellIndex))
		throw range_error("The face index is out of range.");
	
	if (constantNodeCountPerFace != 0)
		return constantNodeCountPerFace;

	if (faceIndicesOfCells == nullptr)
		throw invalid_argument("The geometry must have been loaded first.");

	// Global face index
	ULONG64 globalFaceIndex = 0;
	if (cellIndex == 0)
		globalFaceIndex = faceIndicesOfCells[cumulativeFaceCountPerCell[0] + localFaceIndex];
	else
		globalFaceIndex = faceIndicesOfCells[cumulativeFaceCountPerCell[cellIndex-1] + localFaceIndex];
	
	if (globalFaceIndex == 0)
		return cumulativeNodeCountPerFace[0];

	return cumulativeNodeCountPerFace[globalFaceIndex] -  cumulativeNodeCountPerFace[globalFaceIndex-1];
}

ULONG64 * UnstructuredGridRepresentation::getNodeIndicesOfFaceOfCell(const ULONG64 & cellIndex, const unsigned int & localFaceIndex) const
{
	if (faceIndicesOfCells == nullptr)
		throw invalid_argument("The geometry must have been loaded first.");
	if (cellIndex >= getCellCount())
		throw range_error("The cell index is out of range.");
	if (localFaceIndex >= getFaceCountOfCell(cellIndex))
		throw range_error("The face index is out of range.");

	// Global face index
	ULONG64 globalFaceIndex = 0;
	if (cellIndex == 0)
		globalFaceIndex = faceIndicesOfCells[localFaceIndex];
	else
	{
		if (constantFaceCountPerCell != 0)
			globalFaceIndex = faceIndicesOfCells[constantFaceCountPerCell * cellIndex + localFaceIndex];
		else
			globalFaceIndex = faceIndicesOfCells[cumulativeFaceCountPerCell[cellIndex-1] + localFaceIndex];
	}

	if (globalFaceIndex == 0)
		return nodeIndicesOfFaces;

	if (constantNodeCountPerFace != 0)
		return &(nodeIndicesOfFaces[constantNodeCountPerFace * globalFaceIndex]);
	else
		return &(nodeIndicesOfFaces[cumulativeNodeCountPerFace[globalFaceIndex-1]]);
}

