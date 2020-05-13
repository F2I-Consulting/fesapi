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

#include "UnstructuredGridRepresentation.h"

#include <stdexcept>

#include <hdf5.h>

#include "../resqml2/AbstractFeatureInterpretation.h"
#include "../resqml2/AbstractLocal3dCrs.h"
#include "../common/AbstractHdfProxy.h"

using namespace std;
using namespace gsoap_resqml2_0_1;
using namespace RESQML2_0_1_NS;

const char* UnstructuredGridRepresentation::XML_TAG = "UnstructuredGridRepresentation";


void UnstructuredGridRepresentation::init(COMMON_NS::DataObjectRepository* repo,
			const std::string & guid, const std::string & title,
			ULONG64 cellCount)
{
	if (repo == nullptr) {
		throw invalid_argument("The repo cannot be null.");
	}

	gsoapProxy2_0_1 = soap_new_resqml20__obj_USCOREUnstructuredGridRepresentation(repo->getGsoapContext());
	_resqml20__UnstructuredGridRepresentation* unstructuredGrid = getSpecializedGsoapProxy();

	unstructuredGrid->CellCount = cellCount;

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "");

	repo->addOrReplaceDataObject(this);
}

UnstructuredGridRepresentation::UnstructuredGridRepresentation(COMMON_NS::DataObjectRepository* repo,
	const std::string & guid, const std::string & title,
	ULONG64 cellCount):
	AbstractGridRepresentation(false), constantNodeCountPerFace(0), constantFaceCountPerCell(0),
	cumulativeNodeCountPerFace(nullptr), cumulativeFaceCountPerCell(nullptr),
	nodeIndicesOfFaces(nullptr), faceIndicesOfCells(nullptr)
{
	init(repo, guid, title, cellCount);
}

UnstructuredGridRepresentation::UnstructuredGridRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp,
	const std::string & guid, const std::string & title,
	ULONG64 cellCount):
	AbstractGridRepresentation(false), constantNodeCountPerFace(0), constantFaceCountPerCell(0),
	cumulativeNodeCountPerFace(nullptr), cumulativeFaceCountPerCell(nullptr),
	nodeIndicesOfFaces(nullptr), faceIndicesOfCells(nullptr)
{
	if (interp == nullptr)
		throw invalid_argument("The interpretation of the unstructured grid cannot be null.");

	init(interp->getRepository(), guid, title, cellCount);

	// relationhsips
	setInterpretation(interp);
}

bool UnstructuredGridRepresentation::hasGeometry() const
{
	return getSpecializedGsoapProxy()->Geometry != nullptr;
}

_resqml20__UnstructuredGridRepresentation* UnstructuredGridRepresentation::getSpecializedGsoapProxy() const
{
	if (isPartial()) {
		throw logic_error("Partial object");
	}

	return static_cast<_resqml20__UnstructuredGridRepresentation*>(gsoapProxy2_0_1);
}

gsoap_resqml2_0_1::resqml20__PointGeometry* UnstructuredGridRepresentation::getPointGeometry2_0_1(unsigned int patchIndex) const
{
	if (patchIndex == 0) {
		return getSpecializedGsoapProxy()->Geometry;
	}
	
	return nullptr;
}

gsoap_resqml2_0_1::eml20__DataObjectReference* UnstructuredGridRepresentation::getHdfProxyDor() const
{
	return getHdfProxyDorFromPointGeometryPatch(getPointGeometry2_0_1(0));
}

ULONG64 UnstructuredGridRepresentation::getCellCount() const
{
	return getSpecializedGsoapProxy()->CellCount;
}

ULONG64 UnstructuredGridRepresentation::getFaceCount() const
{
	_resqml20__UnstructuredGridRepresentation* grid = getSpecializedGsoapProxy();
	if (grid->Geometry != nullptr) {
		return grid->Geometry->FaceCount;
	}
	
	return 0;
}

ULONG64 UnstructuredGridRepresentation::getNodeCount() const
{
	_resqml20__UnstructuredGridRepresentation* grid = getSpecializedGsoapProxy();
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

	resqml20__PointGeometry* pointGeom = getPointGeometry2_0_1(patchIndex);
	if (pointGeom != nullptr && pointGeom->Points->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__Point3dHdf5Array) {
		eml20__Hdf5Dataset const * dataset = static_cast<resqml20__Point3dHdf5Array*>(pointGeom->Points)->Coordinates;
		COMMON_NS::AbstractHdfProxy * hdfProxy = getHdfProxyFromDataset(dataset);
		hdfProxy->readArrayNdOfDoubleValues(dataset->PathInHdfFile, xyzPoints);
	}
	else {
		throw invalid_argument("The geometry of the representation either does not exist or it is not an explicit one.");
	}
}

void UnstructuredGridRepresentation::getFaceIndicesOfCells(ULONG64 * faceIndices) const
{
	_resqml20__UnstructuredGridRepresentation* grid = getSpecializedGsoapProxy();
	if (grid->Geometry == nullptr) {
		throw invalid_argument("There is no geometry in this grid.");
	}
	if (grid->Geometry->FacesPerCell->Elements->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__IntegerHdf5Array) {
		eml20__Hdf5Dataset const * dataset = static_cast<resqml20__IntegerHdf5Array*>(grid->Geometry->FacesPerCell->Elements)->Values;
		COMMON_NS::AbstractHdfProxy * hdfProxy = getHdfProxyFromDataset(dataset);
		hdfProxy->readArrayNdOfULongValues(dataset->PathInHdfFile, faceIndices);
	}
	else {
		throw logic_error("Not yet implemented");
	}
}

void UnstructuredGridRepresentation::getCumulativeFaceCountPerCell(ULONG64 * cumulativeFaceCountPerCell_) const
{
	_resqml20__UnstructuredGridRepresentation* grid = getSpecializedGsoapProxy();
	if (grid->Geometry == nullptr)
		throw invalid_argument("There is no geometry in this grid.");
	if (grid->Geometry->FacesPerCell->CumulativeLength->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__IntegerHdf5Array)
	{
		eml20__Hdf5Dataset const * dataset = static_cast<resqml20__IntegerHdf5Array*>(grid->Geometry->FacesPerCell->CumulativeLength)->Values;
		COMMON_NS::AbstractHdfProxy * hdfProxy = getHdfProxyFromDataset(dataset);
		hdfProxy->readArrayNdOfULongValues(dataset->PathInHdfFile, cumulativeFaceCountPerCell_);
	}
	else if (grid->Geometry->FacesPerCell->CumulativeLength->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__IntegerLatticeArray)
	{
		cumulativeFaceCountPerCell_[0] = static_cast<resqml20__IntegerLatticeArray*>(grid->Geometry->FacesPerCell->CumulativeLength)->StartValue;
		const LONG64 offsetValue = static_cast<resqml20__IntegerLatticeArray*>(grid->Geometry->FacesPerCell->CumulativeLength)->Offset[0]->Value;
		const ULONG64 cellCount = getCellCount();
		for (ULONG64 cumulativeFaceCountPerCellIndex = 1; cumulativeFaceCountPerCellIndex < cellCount; ++cumulativeFaceCountPerCellIndex)
		{
			cumulativeFaceCountPerCell_[cumulativeFaceCountPerCellIndex] = cumulativeFaceCountPerCell_[cumulativeFaceCountPerCellIndex - 1] + offsetValue;
		}
	}
	else if (grid->Geometry->FacesPerCell->CumulativeLength->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__IntegerConstantArray)
	{
		if (getCellCount() > 1)
			throw range_error("The cumulative length of faces count per cells cannot be constant if there is more than one cell in the grid");
		cumulativeFaceCountPerCell_[0] = static_cast<resqml20__IntegerConstantArray*>(grid->Geometry->FacesPerCell->CumulativeLength)->Value;
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
	_resqml20__UnstructuredGridRepresentation* grid = getSpecializedGsoapProxy();
	if (grid->Geometry == nullptr)
		throw invalid_argument("There is no geometry in this grid.");
	if (grid->Geometry->CellShape == resqml20__CellShape__hexahedral || grid->Geometry->CellShape == resqml20__CellShape__tetrahedral)
	{
		return true;
	}
	else if (grid->Geometry->FacesPerCell->CumulativeLength->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__IntegerLatticeArray)
	{
		if (static_cast<resqml20__IntegerLatticeArray*>(grid->Geometry->FacesPerCell->CumulativeLength)->StartValue == static_cast<resqml20__IntegerLatticeArray*>(grid->Geometry->FacesPerCell->CumulativeLength)->Offset[0]->Value)
			return true;
	}
	else if (grid->Geometry->FacesPerCell->CumulativeLength->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__IntegerConstantArray)
	{
		if (getCellCount() > 1)
			throw range_error("The cumulative length of faces count per cells cannot be constant if there is more than one cell in the grid");
		return true;
	}

	return false;
}

unsigned int UnstructuredGridRepresentation::getConstantFaceCountOfCells() const
{
	_resqml20__UnstructuredGridRepresentation* grid = getSpecializedGsoapProxy();
	if (!isFaceCountOfCellsConstant())
		throw invalid_argument("The face count per cell is not constant.");

	if (grid->Geometry->CellShape == resqml20__CellShape__hexahedral)
	{
		return 6;
	}
	else if (grid->Geometry->CellShape == resqml20__CellShape__tetrahedral)
	{
		return 4;
	}
	else if (grid->Geometry->FacesPerCell->CumulativeLength->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__IntegerLatticeArray)
	{
		return static_cast<resqml20__IntegerLatticeArray*>(grid->Geometry->FacesPerCell->CumulativeLength)->StartValue;
	}
	else if (grid->Geometry->FacesPerCell->CumulativeLength->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__IntegerConstantArray)
	{
		if (getCellCount() > 1)
			throw range_error("The cumulative length of faces count per cells cannot be constant if there is more than one cell in the grid");
		return static_cast<resqml20__IntegerConstantArray*>(grid->Geometry->FacesPerCell->CumulativeLength)->Value;
	}
	else
		return 0;
}

void UnstructuredGridRepresentation::getNodeIndicesOfFaces(ULONG64 * nodeIndices) const
{
	_resqml20__UnstructuredGridRepresentation* grid = getSpecializedGsoapProxy();
	if (grid->Geometry == nullptr) {
		throw invalid_argument("There is no geometry in this grid.");
	}
	if (grid->Geometry->NodesPerFace->Elements->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__IntegerHdf5Array)
	{
		eml20__Hdf5Dataset const * dataset = static_cast<resqml20__IntegerHdf5Array*>(grid->Geometry->NodesPerFace->Elements)->Values;
		COMMON_NS::AbstractHdfProxy * hdfProxy = getHdfProxyFromDataset(dataset);
		hdfProxy->readArrayNdOfULongValues(dataset->PathInHdfFile, nodeIndices);
	}
	else
		throw logic_error("Not yet implemented");
}

void UnstructuredGridRepresentation::getCumulativeNodeCountPerFace(ULONG64 * nodeCountPerFace) const
{
	_resqml20__UnstructuredGridRepresentation* grid = getSpecializedGsoapProxy();
		if (grid->Geometry == nullptr)
			throw invalid_argument("There is no geometry in this grid.");
	if (grid->Geometry->NodesPerFace->CumulativeLength->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__IntegerHdf5Array)
	{
		eml20__Hdf5Dataset const * dataset = static_cast<resqml20__IntegerHdf5Array*>(grid->Geometry->NodesPerFace->CumulativeLength)->Values;
		COMMON_NS::AbstractHdfProxy * hdfProxy = getHdfProxyFromDataset(dataset);
		hdfProxy->readArrayNdOfULongValues(dataset->PathInHdfFile, nodeCountPerFace);
	}
	else if (grid->Geometry->NodesPerFace->CumulativeLength->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__IntegerLatticeArray)
	{
		nodeCountPerFace[0] = static_cast<resqml20__IntegerLatticeArray*>(grid->Geometry->NodesPerFace->CumulativeLength)->StartValue;
		const LONG64 offsetValue = static_cast<resqml20__IntegerLatticeArray*>(grid->Geometry->NodesPerFace->CumulativeLength)->Offset[0]->Value;
		const ULONG64 faceCount = getFaceCount();
		for (ULONG64 nodeCountPerFaceIndex = 1; nodeCountPerFaceIndex < faceCount; ++nodeCountPerFaceIndex)
		{
			nodeCountPerFace[nodeCountPerFaceIndex] = nodeCountPerFace[nodeCountPerFaceIndex - 1] + offsetValue;
		}
	}
	else if (grid->Geometry->NodesPerFace->CumulativeLength->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__IntegerConstantArray)
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
	_resqml20__UnstructuredGridRepresentation* grid = getSpecializedGsoapProxy();
	if (grid->Geometry == nullptr)
		throw invalid_argument("There is no geometry in this grid.");
	if (grid->Geometry->CellShape == resqml20__CellShape__hexahedral || grid->Geometry->CellShape == resqml20__CellShape__tetrahedral)
	{
		return true;
	}
	else if (grid->Geometry->NodesPerFace->CumulativeLength->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__IntegerLatticeArray)
	{
		if (static_cast<resqml20__IntegerLatticeArray*>(grid->Geometry->NodesPerFace->CumulativeLength)->StartValue == static_cast<resqml20__IntegerLatticeArray*>(grid->Geometry->NodesPerFace->CumulativeLength)->Offset[0]->Value)
			return true;
	}

	return false;
}

unsigned int UnstructuredGridRepresentation::getConstantNodeCountOfFaces() const
{
	_resqml20__UnstructuredGridRepresentation* grid = getSpecializedGsoapProxy();
	if (isNodeCountOfFacesConstant() == false)
		throw invalid_argument("The node count per cell is not constant.");

	if (grid->Geometry->CellShape == resqml20__CellShape__hexahedral)
	{
		return 4;
	}
	else if (grid->Geometry->CellShape == resqml20__CellShape__tetrahedral)
	{
		return 3;
	}
	else if (grid->Geometry->NodesPerFace->CumulativeLength->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__IntegerLatticeArray)
	{
		return static_cast<resqml20__IntegerLatticeArray*>(grid->Geometry->NodesPerFace->CumulativeLength)->StartValue;
	}
	else
		return 0;
}

void UnstructuredGridRepresentation::getCellFaceIsRightHanded(unsigned char* cellFaceIsRightHanded) const
{
  _resqml20__UnstructuredGridRepresentation* grid = getSpecializedGsoapProxy();
  if (grid->Geometry == nullptr)
    throw invalid_argument("There is no geometry in this grid.");
  if (grid->Geometry->CellFaceIsRightHanded->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__BooleanHdf5Array)
  {
	  eml20__Hdf5Dataset const * dataset = static_cast<resqml20__BooleanHdf5Array*>(grid->Geometry->CellFaceIsRightHanded)->Values;
	  COMMON_NS::AbstractHdfProxy * hdfProxy = getHdfProxyFromDataset(dataset);
	hdfProxy->readArrayNdOfUCharValues(dataset->PathInHdfFile, cellFaceIsRightHanded);
  }
  else if (grid->Geometry->CellFaceIsRightHanded->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__BooleanConstantArray)
  {
	  for (size_t i = 0; i < static_cast<resqml20__BooleanConstantArray*>(grid->Geometry->CellFaceIsRightHanded)->Count; ++i)
	  {
		  cellFaceIsRightHanded[i] = static_cast<resqml20__BooleanConstantArray*>(grid->Geometry->CellFaceIsRightHanded)->Value;
	  }
  }
  else
	  throw logic_error("Not yet implemented.");
}

void UnstructuredGridRepresentation::setGeometryUsingExistingDatasets(const std::string& cellFaceIsRightHanded, const std::string& points, ULONG64 pointCount, COMMON_NS::AbstractHdfProxy* proxy,
	const std::string& faceIndicesPerCell, const std::string&faceIndicesCumulativeCountPerCell,
	ULONG64 faceCount, const std::string& nodeIndicesPerFace, const std::string& nodeIndicesCumulativeCountPerFace,
	gsoap_resqml2_0_1::resqml20__CellShape cellShape, RESQML2_NS::AbstractLocal3dCrs * localCrs)
{
	if (cellFaceIsRightHanded.empty())
		throw invalid_argument("The cellFaceIsRightHanded dataset path information cannot be empty.");
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
	if (localCrs == nullptr) {
		localCrs = getRepository()->getDefaultCrs();
		if (localCrs == nullptr) {
			throw std::invalid_argument("A (default) CRS must be provided.");
		}
	}
	if (proxy == nullptr) {
		proxy = getRepository()->getDefaultHdfProxy();
		if (proxy == nullptr) {
			throw std::invalid_argument("A (default) HDF Proxy must be provided.");
		}
	}

	resqml20__UnstructuredGridGeometry* geom = soap_new_resqml20__UnstructuredGridGeometry(gsoapProxy2_0_1->soap);
	getSpecializedGsoapProxy()->Geometry = geom;
	getSpecializedGsoapProxy()->Geometry->LocalCrs = localCrs->newResqmlReference();

	geom->FaceCount = faceCount;
	geom->NodeCount = pointCount;
	geom->CellShape = cellShape;

	getRepository()->addRelationship(this, proxy);
	// Face Right handness
	//XML
	resqml20__BooleanHdf5Array* cellFaceIsRightHandedForHdf5 = soap_new_resqml20__BooleanHdf5Array(gsoapProxy2_0_1->soap);
	cellFaceIsRightHandedForHdf5->Values = soap_new_eml20__Hdf5Dataset(gsoapProxy2_0_1->soap);
	cellFaceIsRightHandedForHdf5->Values->HdfProxy = proxy->newResqmlReference();
	cellFaceIsRightHandedForHdf5->Values->PathInHdfFile = cellFaceIsRightHanded;
	geom->CellFaceIsRightHanded = cellFaceIsRightHandedForHdf5;

	// Face indices
	//XML
	geom->FacesPerCell = soap_new_resqml20__ResqmlJaggedArray(gsoapProxy2_0_1->soap);
	// Cumulative
	resqml20__IntegerHdf5Array* cumulativeLength = soap_new_resqml20__IntegerHdf5Array(gsoapProxy2_0_1->soap);
	geom->FacesPerCell->CumulativeLength = cumulativeLength;
	cumulativeLength->NullValue = -1;
	cumulativeLength->Values = soap_new_eml20__Hdf5Dataset(gsoapProxy2_0_1->soap);
	cumulativeLength->Values->HdfProxy = proxy->newResqmlReference();
	cumulativeLength->Values->PathInHdfFile = faceIndicesCumulativeCountPerCell;
	// Elements
	resqml20__IntegerHdf5Array* elements = soap_new_resqml20__IntegerHdf5Array(gsoapProxy2_0_1->soap);
	geom->FacesPerCell->Elements = elements;
	elements->NullValue = faceCount+1;
	elements->Values = soap_new_eml20__Hdf5Dataset(gsoapProxy2_0_1->soap);
	elements->Values->HdfProxy = proxy->newResqmlReference();
	elements->Values->PathInHdfFile = faceIndicesPerCell;

	// Node indices
	//XML
	geom->NodesPerFace = soap_new_resqml20__ResqmlJaggedArray(gsoapProxy2_0_1->soap);
	// Cumulative
	cumulativeLength = soap_new_resqml20__IntegerHdf5Array(gsoapProxy2_0_1->soap);
	geom->NodesPerFace->CumulativeLength = cumulativeLength;
	cumulativeLength->NullValue = -1;
	cumulativeLength->Values = soap_new_eml20__Hdf5Dataset(gsoapProxy2_0_1->soap);
	cumulativeLength->Values->HdfProxy = proxy->newResqmlReference();
	cumulativeLength->Values->PathInHdfFile = nodeIndicesCumulativeCountPerFace;
	// Elements
	elements = soap_new_resqml20__IntegerHdf5Array(gsoapProxy2_0_1->soap);
	geom->NodesPerFace->Elements = elements;
	elements->NullValue = pointCount+1;
	elements->Values = soap_new_eml20__Hdf5Dataset(gsoapProxy2_0_1->soap);
	elements->Values->HdfProxy = proxy->newResqmlReference();
	elements->Values->PathInHdfFile = nodeIndicesPerFace;

	// XML points
	resqml20__Point3dHdf5Array* xmlPoints = soap_new_resqml20__Point3dHdf5Array(gsoapProxy2_0_1->soap);
	geom->Points = xmlPoints;
	xmlPoints->Coordinates = soap_new_eml20__Hdf5Dataset(gsoapProxy2_0_1->soap);
	xmlPoints->Coordinates->HdfProxy = proxy->newResqmlReference();
	xmlPoints->Coordinates->PathInHdfFile = points;

	getRepository()->addRelationship(this, localCrs);
}

void UnstructuredGridRepresentation::setGeometry(unsigned char * cellFaceIsRightHanded, double * points, ULONG64 pointCount, COMMON_NS::AbstractHdfProxy * proxy,
	ULONG64 * faceIndicesPerCell, ULONG64 * faceIndicesCumulativeCountPerCell,
	ULONG64 faceCount, ULONG64 * nodeIndicesPerFace, ULONG64 * nodeIndicesCumulativeCountPerFace,
	gsoap_resqml2_0_1::resqml20__CellShape cellShape, RESQML2_NS::AbstractLocal3dCrs * localCrs)
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

	if (proxy == nullptr) {
		proxy = getRepository()->getDefaultHdfProxy();
		if (proxy == nullptr) {
			throw std::invalid_argument("A (default) HDF Proxy must be provided.");
		}
	}

	setGeometryUsingExistingDatasets("/RESQML/" + gsoapProxy2_0_1->uuid + "/CellFaceIsRightHanded", "/RESQML/" + gsoapProxy2_0_1->uuid + "/Points", pointCount, proxy,
		"/RESQML/" + gsoapProxy2_0_1->uuid + "/FacesPerCell/" + ELEMENTS_DS_NAME, "/RESQML/" + gsoapProxy2_0_1->uuid + "/FacesPerCell/" + CUMULATIVE_LENGTH_DS_NAME,
		faceCount, "/RESQML/" + gsoapProxy2_0_1->uuid + "/NodesPerFace/" + ELEMENTS_DS_NAME, "/RESQML/" + gsoapProxy2_0_1->uuid + "/NodesPerFace/" + CUMULATIVE_LENGTH_DS_NAME,
		cellShape, localCrs);

	ULONG64 cellCount = getSpecializedGsoapProxy()->CellCount;

	// HDF Face Right handness
	unsigned long long faceCountTmp = faceIndicesCumulativeCountPerCell[cellCount - 1]; // For GCC : ULONG64 is not exactly an unsigned long long with GCC but an uint64_t {aka long unsigned int}
	proxy->writeArrayNd(gsoapProxy2_0_1->uuid, "CellFaceIsRightHanded", H5T_NATIVE_UCHAR, cellFaceIsRightHanded, &faceCountTmp, 1);

	// HDF Face indices
	proxy->writeItemizedListOfList(gsoapProxy2_0_1->uuid, "FacesPerCell", H5T_NATIVE_ULLONG, faceIndicesCumulativeCountPerCell, cellCount, H5T_NATIVE_ULLONG, faceIndicesPerCell, faceIndicesCumulativeCountPerCell[cellCount - 1]);

	// HDF Node indices
	proxy->writeItemizedListOfList(gsoapProxy2_0_1->uuid, "NodesPerFace", H5T_NATIVE_ULLONG, nodeIndicesCumulativeCountPerFace, faceCount, H5T_NATIVE_ULLONG, nodeIndicesPerFace, nodeIndicesCumulativeCountPerFace[faceCount - 1]);

	// HDF points
	hsize_t * numValues = new hsize_t[2];
	numValues[0] = pointCount;
	numValues[1] = 3; // 3 for X, Y and Z
	proxy->writeArrayNdOfDoubleValues(gsoapProxy2_0_1->uuid, "Points", points, numValues, 2);
	delete [] numValues;
}

void UnstructuredGridRepresentation::setConstantCellShapeGeometryUsingExistingDatasets(const std::string& cellFaceIsRightHanded, const std::string& points,
	ULONG64 pointCount, ULONG64 faceCount, RESQML2_NS::AbstractLocal3dCrs * localCrs, COMMON_NS::AbstractHdfProxy* proxy,
	const std::string& faceIndicesPerCell, ULONG64 faceCountPerCell,
	const std::string& nodeIndicesPerFace, ULONG64 nodeCountPerFace)
{
	if (cellFaceIsRightHanded.empty())
		throw invalid_argument("The cellFaceIsRightHanded dataset path cannot be empty.");
	if (points.empty())
		throw invalid_argument("The points dataset path of the ijk grid cannot be empty.");
	if (faceIndicesPerCell.empty())
		throw invalid_argument("The dataset path of the face indices per cell is incomplete.");
	if (nodeIndicesPerFace.empty())
		throw invalid_argument("The dataset path of the node indices per face is incomplete.");
	if (localCrs == nullptr) {
		localCrs = getRepository()->getDefaultCrs();
		if (localCrs == nullptr) {
			throw std::invalid_argument("A (default) CRS must be provided.");
		}
	}
	if (proxy == nullptr) {
		proxy = getRepository()->getDefaultHdfProxy();
		if (proxy == nullptr) {
			throw std::invalid_argument("A (default) HDF Proxy must be provided.");
		}
	}

	const ULONG64 cellCount = getSpecializedGsoapProxy()->CellCount;

	resqml20__UnstructuredGridGeometry* geom = soap_new_resqml20__UnstructuredGridGeometry(gsoapProxy2_0_1->soap);
	getSpecializedGsoapProxy()->Geometry = geom;
	getSpecializedGsoapProxy()->Geometry->LocalCrs = localCrs->newResqmlReference();

	geom->FaceCount = faceCount;
	geom->NodeCount = pointCount;
	if (nodeCountPerFace == 3 && faceCountPerCell == 4) {
		geom->CellShape = resqml20__CellShape__tetrahedral;
	}
	else if (nodeCountPerFace == 4 && faceCountPerCell == 6) {
		geom->CellShape = resqml20__CellShape__hexahedral;
	}
	else {
		geom->CellShape = resqml20__CellShape__polyhedral;
	}

	getRepository()->addRelationship(this, proxy);
	// Face Right handness
	//XML
	resqml20__BooleanHdf5Array* cellFaceIsRightHandedForHdf5 = soap_new_resqml20__BooleanHdf5Array(gsoapProxy2_0_1->soap);
	cellFaceIsRightHandedForHdf5->Values = soap_new_eml20__Hdf5Dataset(gsoapProxy2_0_1->soap);
	cellFaceIsRightHandedForHdf5->Values->HdfProxy = proxy->newResqmlReference();
	cellFaceIsRightHandedForHdf5->Values->PathInHdfFile = cellFaceIsRightHanded;
	geom->CellFaceIsRightHanded = cellFaceIsRightHandedForHdf5;

	// Face indices
	//XML
	geom->FacesPerCell = soap_new_resqml20__ResqmlJaggedArray(gsoapProxy2_0_1->soap);
	// Cumulative
	if (cellCount == 1)
	{
		resqml20__IntegerConstantArray* cumulativeLength = soap_new_resqml20__IntegerConstantArray(gsoapProxy2_0_1->soap);
		geom->FacesPerCell->CumulativeLength = cumulativeLength;
		cumulativeLength->Count = cellCount;
		cumulativeLength->Value = faceCountPerCell;
	}
	else
	{
		resqml20__IntegerLatticeArray* cumulativeLength = soap_new_resqml20__IntegerLatticeArray(gsoapProxy2_0_1->soap);
		geom->FacesPerCell->CumulativeLength = cumulativeLength;
		cumulativeLength->StartValue = faceCountPerCell;
		cumulativeLength->Offset.push_back(soap_new_resqml20__IntegerConstantArray(gsoapProxy2_0_1->soap, 1));
		cumulativeLength->Offset[0]->Count = cellCount - 1;
		cumulativeLength->Offset[0]->Value = faceCountPerCell;
	}
	// Elements
	resqml20__IntegerHdf5Array* elements = soap_new_resqml20__IntegerHdf5Array(gsoapProxy2_0_1->soap);
	geom->FacesPerCell->Elements = elements;
	elements->NullValue = faceCount+1;
	elements->Values = soap_new_eml20__Hdf5Dataset(gsoapProxy2_0_1->soap);
	elements->Values->HdfProxy = proxy->newResqmlReference();
	elements->Values->PathInHdfFile = faceIndicesPerCell;

	// Node indices
	//XML
	geom->NodesPerFace = soap_new_resqml20__ResqmlJaggedArray(gsoapProxy2_0_1->soap);
	// Cumulative
	resqml20__IntegerLatticeArray* cumulativeLength = soap_new_resqml20__IntegerLatticeArray(gsoapProxy2_0_1->soap);
	geom->NodesPerFace->CumulativeLength = cumulativeLength;
	cumulativeLength->StartValue = nodeCountPerFace;
	cumulativeLength->Offset.push_back(soap_new_resqml20__IntegerConstantArray(gsoapProxy2_0_1->soap, 1));
	cumulativeLength->Offset[0]->Count = geom->FaceCount - 1;
	cumulativeLength->Offset[0]->Value = nodeCountPerFace;
	// Elements
	elements = soap_new_resqml20__IntegerHdf5Array(gsoapProxy2_0_1->soap);
	geom->NodesPerFace->Elements = elements;
	elements->NullValue = pointCount+1;
	elements->Values = soap_new_eml20__Hdf5Dataset(gsoapProxy2_0_1->soap);
	elements->Values->HdfProxy = proxy->newResqmlReference();
	elements->Values->PathInHdfFile = nodeIndicesPerFace;

	// XML points
	resqml20__Point3dHdf5Array* xmlPoints = soap_new_resqml20__Point3dHdf5Array(gsoapProxy2_0_1->soap);
	geom->Points = xmlPoints;
	xmlPoints->Coordinates = soap_new_eml20__Hdf5Dataset(gsoapProxy2_0_1->soap);
	xmlPoints->Coordinates->HdfProxy = proxy->newResqmlReference();
	xmlPoints->Coordinates->PathInHdfFile = points;

	getRepository()->addRelationship(this, localCrs);
}

void UnstructuredGridRepresentation::setConstantCellShapeGeometry(unsigned char * cellFaceIsRightHanded, double * points,
	ULONG64 pointCount, ULONG64 faceCount, RESQML2_NS::AbstractLocal3dCrs * localCrs, COMMON_NS::AbstractHdfProxy* proxy,
	ULONG64 * faceIndicesPerCell, ULONG64 faceCountPerCell,
	ULONG64 * nodeIndicesPerFace, ULONG64 nodeCountPerFace)
{
	if (cellFaceIsRightHanded == nullptr) {
		throw invalid_argument("The cellFaceIsRightHanded information cannot be null.");
	}
	if (points == nullptr) {
		throw invalid_argument("The points of the ijk grid cannot be null.");
	}
	if (faceIndicesPerCell == nullptr) {
		throw invalid_argument("The definition of the face indices per cell is incomplete.");
	}
	if (nodeIndicesPerFace == nullptr) {
		throw invalid_argument("The definition of the node indices per face is incomplete.");
	}
	if (proxy == nullptr) {
		proxy = getRepository()->getDefaultHdfProxy();
		if (proxy == nullptr) {
			throw std::invalid_argument("A (default) HDF Proxy must be provided.");
		}
	}

	setConstantCellShapeGeometryUsingExistingDatasets("/RESQML/" + gsoapProxy2_0_1->uuid + "/CellFaceIsRightHanded", "/RESQML/" + gsoapProxy2_0_1->uuid + "/Points",
		pointCount, faceCount, localCrs, proxy,
		"/RESQML/" + gsoapProxy2_0_1->uuid + "/FacesPerCell", faceCountPerCell,
		"/RESQML/" + gsoapProxy2_0_1->uuid + "/NodesPerFace", nodeCountPerFace);

	ULONG64 cellCount = getSpecializedGsoapProxy()->CellCount;

	// HDF Face Right handness
	unsigned long long faceCountTmp = faceCountPerCell * cellCount; // For GCC : ULONG64 is not exactly an unsigned long long with GCC but an uint64_t {aka long unsigned int}
	proxy->writeArrayNd(gsoapProxy2_0_1->uuid, "CellFaceIsRightHanded", H5T_NATIVE_UCHAR, cellFaceIsRightHanded, &faceCountTmp, 1);

	// HDF Face indices
	hsize_t * numValues = new hsize_t[2];
	numValues[0] = cellCount;
	numValues[1] = faceCountPerCell;
	proxy->writeArrayNd(gsoapProxy2_0_1->uuid, "FacesPerCell", H5T_NATIVE_ULLONG, faceIndicesPerCell, numValues, 2);
	delete[] numValues;

	// HDF Node indices
	numValues = new hsize_t[2];
	numValues[0] = faceCount;
	numValues[1] = nodeCountPerFace;
	proxy->writeArrayNd(gsoapProxy2_0_1->uuid, "NodesPerFace", H5T_NATIVE_ULLONG, nodeIndicesPerFace, numValues, 2);
	delete[] numValues;

	// HDF points
	numValues = new hsize_t[2];
	numValues[0] = pointCount;
	numValues[1] = 3; // 3 for X, Y and Z
	proxy->writeArrayNdOfDoubleValues(gsoapProxy2_0_1->uuid, "Points", points, numValues, 2);
	delete[] numValues;
}

void UnstructuredGridRepresentation::setTetrahedraOnlyGeometryUsingExistingDatasets(const std::string& cellFaceIsRightHanded, const std::string& points,
	ULONG64 pointCount, ULONG64 faceCount, COMMON_NS::AbstractHdfProxy* proxy,
	const std::string& faceIndicesPerCell, const std::string& nodeIndicesPerFace, RESQML2_NS::AbstractLocal3dCrs * localCrs)
{
	setConstantCellShapeGeometryUsingExistingDatasets(cellFaceIsRightHanded, points,
		pointCount, faceCount, localCrs, proxy,
		faceIndicesPerCell, 4,
		nodeIndicesPerFace, 3);
}

void UnstructuredGridRepresentation::setTetrahedraOnlyGeometry(unsigned char * cellFaceIsRightHanded, double * points, ULONG64 pointCount, ULONG64 faceCount, COMMON_NS::AbstractHdfProxy * proxy,
	ULONG64 * faceIndicesPerCell, ULONG64 * nodeIndicesPerFace, RESQML2_NS::AbstractLocal3dCrs * localCrs)
{
	setConstantCellShapeGeometry(cellFaceIsRightHanded, points,
		pointCount, faceCount, localCrs, proxy,
		faceIndicesPerCell, 4,
		nodeIndicesPerFace, 3);
}

void UnstructuredGridRepresentation::setHexahedraOnlyGeometryUsingExistingDatasets(const std::string& cellFaceIsRightHanded, const std::string& points,
	ULONG64 pointCount, ULONG64 faceCount, COMMON_NS::AbstractHdfProxy* proxy,
	const std::string& faceIndicesPerCell, const std::string& nodeIndicesPerFace, RESQML2_NS::AbstractLocal3dCrs * localCrs)
{
	setConstantCellShapeGeometryUsingExistingDatasets(cellFaceIsRightHanded, points,
		pointCount, faceCount, localCrs, proxy,
		faceIndicesPerCell, 6,
		nodeIndicesPerFace, 4);
}

void UnstructuredGridRepresentation::setHexahedraOnlyGeometry(unsigned char * cellFaceIsRightHanded, double * points, ULONG64 pointCount, ULONG64 faceCount, COMMON_NS::AbstractHdfProxy * proxy,
	ULONG64 * faceIndicesPerCell, ULONG64 * nodeIndicesPerFace, RESQML2_NS::AbstractLocal3dCrs * localCrs)
{
	setConstantCellShapeGeometry(cellFaceIsRightHanded, points,
		pointCount, faceCount, localCrs, proxy,
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

unsigned int UnstructuredGridRepresentation::getFaceCountOfCell(ULONG64 cellIndex) const
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

ULONG64 UnstructuredGridRepresentation::getGlobalFaceIndex(ULONG64 cellIndex, unsigned int localFaceIndex) const
{
	if (faceIndicesOfCells == nullptr)
		throw invalid_argument("The geometry must have been loaded first.");
	if (cellIndex >= getCellCount())
		throw range_error("The cell index is out of range.");
	if (localFaceIndex >= getFaceCountOfCell(cellIndex))
		throw range_error("The face index is out of range.");

	ULONG64 globalFaceIndex = 0;
	if (cellIndex == 0)
		globalFaceIndex = faceIndicesOfCells[localFaceIndex];
	else
	{
		if (constantFaceCountPerCell != 0)
			globalFaceIndex = faceIndicesOfCells[constantFaceCountPerCell * cellIndex + localFaceIndex];
		else
			globalFaceIndex = faceIndicesOfCells[cumulativeFaceCountPerCell[cellIndex - 1] + localFaceIndex];
	}

	return globalFaceIndex;
}

unsigned int UnstructuredGridRepresentation::getNodeCountOfFaceOfCell(const ULONG64 & cellIndex, const unsigned int & localFaceIndex) const
{
	if (constantNodeCountPerFace != 0)
		return constantNodeCountPerFace;

	const ULONG64 globalFaceIndex = getGlobalFaceIndex(cellIndex, localFaceIndex);
	
	return globalFaceIndex == 0
		? cumulativeNodeCountPerFace[0]
		: cumulativeNodeCountPerFace[globalFaceIndex] - cumulativeNodeCountPerFace[globalFaceIndex - 1];
}

ULONG64 * UnstructuredGridRepresentation::getNodeIndicesOfFaceOfCell(const ULONG64 & cellIndex, const unsigned int & localFaceIndex) const
{
	const ULONG64 globalFaceIndex = getGlobalFaceIndex(cellIndex, localFaceIndex);

	if (globalFaceIndex == 0)
		return nodeIndicesOfFaces;

	if (constantNodeCountPerFace != 0)
		return &(nodeIndicesOfFaces[constantNodeCountPerFace * globalFaceIndex]);
	else
		return &(nodeIndicesOfFaces[cumulativeNodeCountPerFace[globalFaceIndex-1]]);
}
