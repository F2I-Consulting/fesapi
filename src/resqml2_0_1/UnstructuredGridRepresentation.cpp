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

#include "../resqml2/AbstractFeatureInterpretation.h"
#include "../eml2/AbstractLocal3dCrs.h"
#include "../eml2/AbstractHdfProxy.h"

using namespace std;
using namespace gsoap_resqml2_0_1;
using namespace RESQML2_0_1_NS;

const char* UnstructuredGridRepresentation::XML_NS = "resqml20";

void UnstructuredGridRepresentation::init(COMMON_NS::DataObjectRepository* repo,
	const std::string & guid, const std::string & title,
	uint64_t cellCount)
{
	if (repo == nullptr) {
		throw invalid_argument("The repo cannot be null.");
	}

	gsoapProxy2_0_1 = soap_new_resqml20__obj_USCOREUnstructuredGridRepresentation(repo->getGsoapContext());
	_resqml20__UnstructuredGridRepresentation* unstructuredGrid = getSpecializedGsoapProxy();

	unstructuredGrid->CellCount = cellCount;

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "");

	repo->addDataObject(unique_ptr<COMMON_NS::AbstractObject>{this});
}

UnstructuredGridRepresentation::UnstructuredGridRepresentation(COMMON_NS::DataObjectRepository* repo,
	const std::string & guid, const std::string & title,
	uint64_t cellCount)
{
	init(repo, guid, title, cellCount);
}

UnstructuredGridRepresentation::UnstructuredGridRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp,
	const std::string & guid, const std::string & title,
	uint64_t cellCount)
{
	if (interp == nullptr) {
		throw invalid_argument("The interpretation of the unstructured grid cannot be null.");
	}

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

gsoap_resqml2_0_1::resqml20__PointGeometry* UnstructuredGridRepresentation::getPointGeometry2_0_1(uint64_t patchIndex) const
{
	return patchIndex == 0 ? getSpecializedGsoapProxy()->Geometry : nullptr;
}

COMMON_NS::DataObjectReference UnstructuredGridRepresentation::getHdfProxyDor() const
{
	return getHdfProxyDorFromPointGeometryPatch(getPointGeometry2_0_1(0));
}

uint64_t UnstructuredGridRepresentation::getCellCount() const
{
	return getSpecializedGsoapProxy()->CellCount;
}

uint64_t UnstructuredGridRepresentation::getFaceCount() const
{
	_resqml20__UnstructuredGridRepresentation* grid = getSpecializedGsoapProxy();
	if (grid->Geometry != nullptr) {
		return grid->Geometry->FaceCount;
	}
	
	return 0;
}

uint64_t UnstructuredGridRepresentation::getNodeCount() const
{
	_resqml20__UnstructuredGridRepresentation* grid = getSpecializedGsoapProxy();
	if (grid->Geometry != nullptr) {
		return grid->Geometry->NodeCount;
	}

	return 0;
}

void UnstructuredGridRepresentation::getXyzPointsOfPatch(unsigned int patchIndex, double * xyzPoints) const
{
	if (patchIndex >= getPatchCount()) {
		throw range_error("The index of the patch is not in the allowed range of patch.");
	}

	resqml20__PointGeometry* pointGeom = getPointGeometry2_0_1(patchIndex);
	if (pointGeom != nullptr && pointGeom->Points->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__Point3dHdf5Array) {
		eml20__Hdf5Dataset const * dataset = static_cast<resqml20__Point3dHdf5Array*>(pointGeom->Points)->Coordinates;
		EML2_NS::AbstractHdfProxy * hdfProxy = getHdfProxyFromDataset(dataset);
		hdfProxy->readArrayNdOfDoubleValues(dataset->PathInHdfFile, xyzPoints);
	}
	else {
		throw invalid_argument("The geometry of the representation either does not exist or it is not an explicit one.");
	}
}

void UnstructuredGridRepresentation::getFaceIndicesOfCells(uint64_t * faceIndices) const
{
	_resqml20__UnstructuredGridRepresentation* grid = getSpecializedGsoapProxy();
	if (grid->Geometry == nullptr) {
		throw invalid_argument("There is no geometry in this grid.");
	}
	if (grid->Geometry->FacesPerCell->Elements->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__IntegerHdf5Array) {
		eml20__Hdf5Dataset const * dataset = static_cast<resqml20__IntegerHdf5Array*>(grid->Geometry->FacesPerCell->Elements)->Values;
		EML2_NS::AbstractHdfProxy * hdfProxy = getHdfProxyFromDataset(dataset);
		hdfProxy->readArrayNdOfUInt64Values(dataset->PathInHdfFile, faceIndices);
	}
	else {
		throw logic_error("Not yet implemented");
	}
}

void UnstructuredGridRepresentation::getCumulativeFaceCountPerCell(uint64_t * cumulativeFaceCountPerCell_) const
{
	_resqml20__UnstructuredGridRepresentation* grid = getSpecializedGsoapProxy();
	if (grid->Geometry == nullptr)
		throw logic_error("There is no geometry in this grid.");
	if (grid->Geometry->FacesPerCell->CumulativeLength->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__IntegerHdf5Array)
	{
		eml20__Hdf5Dataset const * dataset = static_cast<resqml20__IntegerHdf5Array*>(grid->Geometry->FacesPerCell->CumulativeLength)->Values;
		EML2_NS::AbstractHdfProxy * hdfProxy = getHdfProxyFromDataset(dataset);
		hdfProxy->readArrayNdOfUInt64Values(dataset->PathInHdfFile, cumulativeFaceCountPerCell_);
	}
	else if (grid->Geometry->FacesPerCell->CumulativeLength->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__IntegerLatticeArray)
	{
		cumulativeFaceCountPerCell_[0] = static_cast<resqml20__IntegerLatticeArray*>(grid->Geometry->FacesPerCell->CumulativeLength)->StartValue;
		const int64_t offsetValue = static_cast<resqml20__IntegerLatticeArray*>(grid->Geometry->FacesPerCell->CumulativeLength)->Offset[0]->Value;
		const uint64_t cellCount = getCellCount();
		for (uint64_t cumulativeFaceCountPerCellIndex = 1; cumulativeFaceCountPerCellIndex < cellCount; ++cumulativeFaceCountPerCellIndex)
		{
			cumulativeFaceCountPerCell_[cumulativeFaceCountPerCellIndex] = cumulativeFaceCountPerCell_[cumulativeFaceCountPerCellIndex - 1] + offsetValue;
		}
	}
	else if (grid->Geometry->FacesPerCell->CumulativeLength->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__IntegerConstantArray)
	{
		if (getCellCount() > 1)
			throw range_error("The cumulative length of faces count per cell cannot be constant if there is more than one cell in the grid");
		cumulativeFaceCountPerCell_[0] = static_cast<resqml20__IntegerConstantArray*>(grid->Geometry->FacesPerCell->CumulativeLength)->Value;
	}
}

bool UnstructuredGridRepresentation::isFaceCountOfCellsConstant() const
{
	_resqml20__UnstructuredGridRepresentation* grid = getSpecializedGsoapProxy();
	if (grid->Geometry == nullptr)
		throw invalid_argument("There is no geometry in this grid.");
	if (grid->Geometry->CellShape == resqml20__CellShape::hexahedral || grid->Geometry->CellShape == resqml20__CellShape::tetrahedral)
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
		throw logic_error("The face count per cell is not constant.");

	if (grid->Geometry->CellShape == resqml20__CellShape::hexahedral)
	{
		return 6;
	}
	else if (grid->Geometry->CellShape == resqml20__CellShape::tetrahedral)
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

void UnstructuredGridRepresentation::getNodeIndicesOfFaces(uint64_t * nodeIndices) const
{
	_resqml20__UnstructuredGridRepresentation* grid = getSpecializedGsoapProxy();
	if (grid->Geometry == nullptr) {
		throw invalid_argument("There is no geometry in this grid.");
	}
	if (grid->Geometry->NodesPerFace->Elements->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__IntegerHdf5Array)
	{
		eml20__Hdf5Dataset const * dataset = static_cast<resqml20__IntegerHdf5Array*>(grid->Geometry->NodesPerFace->Elements)->Values;
		EML2_NS::AbstractHdfProxy * hdfProxy = getHdfProxyFromDataset(dataset);
		hdfProxy->readArrayNdOfUInt64Values(dataset->PathInHdfFile, nodeIndices);
	}
	else
		throw logic_error("Not yet implemented");
}

void UnstructuredGridRepresentation::getCumulativeNodeCountPerFace(uint64_t * nodeCountPerFace) const
{
	_resqml20__UnstructuredGridRepresentation* grid = getSpecializedGsoapProxy();
		if (grid->Geometry == nullptr)
			throw invalid_argument("There is no geometry in this grid.");
	if (grid->Geometry->NodesPerFace->CumulativeLength->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__IntegerHdf5Array)
	{
		eml20__Hdf5Dataset const * dataset = static_cast<resqml20__IntegerHdf5Array*>(grid->Geometry->NodesPerFace->CumulativeLength)->Values;
		EML2_NS::AbstractHdfProxy * hdfProxy = getHdfProxyFromDataset(dataset);
		hdfProxy->readArrayNdOfUInt64Values(dataset->PathInHdfFile, nodeCountPerFace);
	}
	else if (grid->Geometry->NodesPerFace->CumulativeLength->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__IntegerLatticeArray)
	{
		nodeCountPerFace[0] = static_cast<resqml20__IntegerLatticeArray*>(grid->Geometry->NodesPerFace->CumulativeLength)->StartValue;
		const int64_t offsetValue = static_cast<resqml20__IntegerLatticeArray*>(grid->Geometry->NodesPerFace->CumulativeLength)->Offset[0]->Value;
		const uint64_t faceCount = getFaceCount();
		for (uint64_t nodeCountPerFaceIndex = 1; nodeCountPerFaceIndex < faceCount; ++nodeCountPerFaceIndex)
		{
			nodeCountPerFace[nodeCountPerFaceIndex] = nodeCountPerFace[nodeCountPerFaceIndex - 1] + offsetValue;
		}
	}
	else if (grid->Geometry->NodesPerFace->CumulativeLength->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__IntegerConstantArray)
	{
		throw range_error("The *cumulative* length of nodes count per face cannot be constant.");
	}
}

bool UnstructuredGridRepresentation::isNodeCountOfFacesConstant() const
{
	_resqml20__UnstructuredGridRepresentation* grid = getSpecializedGsoapProxy();
	if (grid->Geometry == nullptr)
		throw invalid_argument("There is no geometry in this grid.");
	if (grid->Geometry->CellShape == resqml20__CellShape::hexahedral || grid->Geometry->CellShape == resqml20__CellShape::tetrahedral)
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

	if (grid->Geometry->CellShape == resqml20__CellShape::hexahedral)
	{
		return 4;
	}
	else if (grid->Geometry->CellShape == resqml20__CellShape::tetrahedral)
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

void UnstructuredGridRepresentation::getCellFaceIsRightHanded(uint8_t* cellFaceIsRightHanded) const
{
  _resqml20__UnstructuredGridRepresentation* grid = getSpecializedGsoapProxy();
  if (grid->Geometry == nullptr)
    throw invalid_argument("There is no geometry in this grid.");
  if (grid->Geometry->CellFaceIsRightHanded->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__BooleanHdf5Array)
  {
	  eml20__Hdf5Dataset const * dataset = static_cast<resqml20__BooleanHdf5Array*>(grid->Geometry->CellFaceIsRightHanded)->Values;
	  EML2_NS::AbstractHdfProxy * hdfProxy = getHdfProxyFromDataset(dataset);
	hdfProxy->readArrayNdOfUInt8Values(dataset->PathInHdfFile, cellFaceIsRightHanded);
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

void UnstructuredGridRepresentation::setGeometryUsingExistingDatasets(const std::string& cellFaceIsRightHanded, const std::string& points, uint64_t pointCount, EML2_NS::AbstractHdfProxy* proxy,
	const std::string& faceIndicesPerCell, const std::string&faceIndicesCumulativeCountPerCell,
	uint64_t faceCount, const std::string& nodeIndicesPerFace, const std::string& nodeIndicesCumulativeCountPerFace,
	gsoap_resqml2_0_1::resqml20__CellShape cellShape, EML2_NS::AbstractLocal3dCrs * localCrs)
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

void UnstructuredGridRepresentation::setConstantCellShapeGeometryUsingExistingDatasets(const std::string& cellFaceIsRightHanded, const std::string& points,
	uint64_t pointCount, uint64_t faceCount, EML2_NS::AbstractLocal3dCrs * localCrs, EML2_NS::AbstractHdfProxy* proxy,
	const std::string& faceIndicesPerCell, uint64_t faceCountPerCell,
	const std::string& nodeIndicesPerFace, uint64_t nodeCountPerFace)
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

	const uint64_t cellCount = getSpecializedGsoapProxy()->CellCount;

	resqml20__UnstructuredGridGeometry* geom = soap_new_resqml20__UnstructuredGridGeometry(gsoapProxy2_0_1->soap);
	getSpecializedGsoapProxy()->Geometry = geom;
	getSpecializedGsoapProxy()->Geometry->LocalCrs = localCrs->newResqmlReference();

	geom->FaceCount = faceCount;
	geom->NodeCount = pointCount;
	if (nodeCountPerFace == 3 && faceCountPerCell == 4) {
		geom->CellShape = resqml20__CellShape::tetrahedral;
	}
	else if (nodeCountPerFace == 4 && faceCountPerCell == 6) {
		geom->CellShape = resqml20__CellShape::hexahedral;
	}
	else {
		geom->CellShape = resqml20__CellShape::polyhedral;
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
