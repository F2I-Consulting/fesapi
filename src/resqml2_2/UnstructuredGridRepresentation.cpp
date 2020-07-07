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
#include "../resqml2/AbstractLocal3dCrs.h"
#include "../eml2/AbstractHdfProxy.h"

using namespace std;
using namespace gsoap_eml2_3;
using namespace RESQML2_2_NS;

void UnstructuredGridRepresentation::init(COMMON_NS::DataObjectRepository* repo,
	const std::string & guid, const std::string & title,
	ULONG64 cellCount)
{
	if (repo == nullptr) {
		throw invalid_argument("The repo cannot be null.");
	}

	gsoapProxy2_3 = soap_new_resqml22__UnstructuredGridRepresentation(repo->getGsoapContext());
	_resqml22__UnstructuredGridRepresentation* unstructuredGrid = getSpecializedGsoapProxy();

	unstructuredGrid->CellCount = cellCount;

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "");

	repo->addOrReplaceDataObject(this);
}

UnstructuredGridRepresentation::UnstructuredGridRepresentation(COMMON_NS::DataObjectRepository* repo,
	const std::string & guid, const std::string & title,
	ULONG64 cellCount)
{
	init(repo, guid, title, cellCount);
}

UnstructuredGridRepresentation::UnstructuredGridRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp,
	const std::string & guid, const std::string & title,
	ULONG64 cellCount)
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

_resqml22__UnstructuredGridRepresentation* UnstructuredGridRepresentation::getSpecializedGsoapProxy() const
{
	if (isPartial()) {
		throw logic_error("Partial object");
	}

	return static_cast<_resqml22__UnstructuredGridRepresentation*>(gsoapProxy2_3);
}

gsoap_eml2_3::resqml22__PointGeometry* UnstructuredGridRepresentation::getPointGeometry2_2(unsigned int patchIndex) const
{
	return patchIndex == 0 ? getSpecializedGsoapProxy()->Geometry : nullptr;
}

COMMON_NS::DataObjectReference UnstructuredGridRepresentation::getHdfProxyDor() const
{
	return getHdfProxyDorFromPointGeometryPatch(getPointGeometry2_0_1(0));
}

ULONG64 UnstructuredGridRepresentation::getCellCount() const
{
	return getSpecializedGsoapProxy()->CellCount;
}

ULONG64 UnstructuredGridRepresentation::getFaceCount() const
{
	_resqml22__UnstructuredGridRepresentation* grid = getSpecializedGsoapProxy();
	if (grid->Geometry != nullptr) {
		return grid->Geometry->FaceCount;
	}
	
	return 0;
}

ULONG64 UnstructuredGridRepresentation::getNodeCount() const
{
	_resqml22__UnstructuredGridRepresentation* grid = getSpecializedGsoapProxy();
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

	resqml22__PointGeometry* pointGeom = getPointGeometry2_2(patchIndex);
	if (pointGeom != nullptr && pointGeom->Points->soap_type() == SOAP_TYPE_gsoap_eml2_3_resqml22__Point3dExternalArray) {
		auto dataset = static_cast<resqml22__Point3dExternalArray*>(pointGeom->Points)->Coordinates->ExternalFileProxy[0];
		EML2_NS::AbstractHdfProxy * hdfProxy = getHdfProxyFromDataset(dataset);
		hdfProxy->readArrayNdOfDoubleValues(dataset->PathInExternalFile, xyzPoints);
	}
	else {
		throw invalid_argument("The geometry of the representation either does not exist or it is not an explicit one.");
	}
}

void UnstructuredGridRepresentation::getFaceIndicesOfCells(ULONG64 * faceIndices) const
{
	_resqml22__UnstructuredGridRepresentation* grid = getSpecializedGsoapProxy();
	if (grid->Geometry == nullptr) {
		throw invalid_argument("There is no geometry in this grid.");
	}
	if (grid->Geometry->FacesPerCell->Elements->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__IntegerExternalArray) {
		auto dataset = static_cast<eml23__IntegerExternalArray*>(grid->Geometry->FacesPerCell->Elements)->Values->ExternalFileProxy[0];
		EML2_NS::AbstractHdfProxy * hdfProxy = getHdfProxyFromDataset(dataset);
		hdfProxy->readArrayNdOfULongValues(dataset->PathInExternalFile, faceIndices);
	}
	else {
		throw logic_error("Not yet implemented");
	}
}

void UnstructuredGridRepresentation::getCumulativeFaceCountPerCell(ULONG64 * cumulativeFaceCountPerCell_) const
{
	_resqml22__UnstructuredGridRepresentation* grid = getSpecializedGsoapProxy();
	if (grid->Geometry == nullptr)
		throw logic_error("There is no geometry in this grid.");
	if (grid->Geometry->FacesPerCell->CumulativeLength->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__IntegerExternalArray)
	{
		auto dataset = static_cast<eml23__IntegerExternalArray*>(grid->Geometry->FacesPerCell->CumulativeLength)->Values->ExternalFileProxy[0];
		EML2_NS::AbstractHdfProxy * hdfProxy = getHdfProxyFromDataset(dataset);
		hdfProxy->readArrayNdOfULongValues(dataset->PathInExternalFile, cumulativeFaceCountPerCell_);
	}
	else if (grid->Geometry->FacesPerCell->CumulativeLength->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__IntegerLatticeArray)
	{
		cumulativeFaceCountPerCell_[0] = static_cast<eml23__IntegerLatticeArray*>(grid->Geometry->FacesPerCell->CumulativeLength)->StartValue;
		const LONG64 offsetValue = static_cast<eml23__IntegerLatticeArray*>(grid->Geometry->FacesPerCell->CumulativeLength)->Offset[0]->Value;
		const ULONG64 cellCount = getCellCount();
		for (ULONG64 cumulativeFaceCountPerCellIndex = 1; cumulativeFaceCountPerCellIndex < cellCount; ++cumulativeFaceCountPerCellIndex)
		{
			cumulativeFaceCountPerCell_[cumulativeFaceCountPerCellIndex] = cumulativeFaceCountPerCell_[cumulativeFaceCountPerCellIndex - 1] + offsetValue;
		}
	}
	else if (grid->Geometry->FacesPerCell->CumulativeLength->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__IntegerConstantArray)
	{
		if (getCellCount() > 1)
			throw range_error("The cumulative length of faces count per cell cannot be constant if there is more than one cell in the grid");
		cumulativeFaceCountPerCell_[0] = static_cast<eml23__IntegerConstantArray*>(grid->Geometry->FacesPerCell->CumulativeLength)->Value;
	}
}

bool UnstructuredGridRepresentation::isFaceCountOfCellsConstant() const
{
	_resqml22__UnstructuredGridRepresentation* grid = getSpecializedGsoapProxy();
	if (grid->Geometry == nullptr)
		throw invalid_argument("There is no geometry in this grid.");
	if (grid->Geometry->CellShape == resqml22__CellShape__hexahedral || grid->Geometry->CellShape == resqml22__CellShape__tetrahedral)
	{
		return true;
	}
	else if (grid->Geometry->FacesPerCell->CumulativeLength->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__IntegerLatticeArray)
	{
		if (static_cast<eml23__IntegerLatticeArray*>(grid->Geometry->FacesPerCell->CumulativeLength)->StartValue == static_cast<eml23__IntegerLatticeArray*>(grid->Geometry->FacesPerCell->CumulativeLength)->Offset[0]->Value)
			return true;
	}
	else if (grid->Geometry->FacesPerCell->CumulativeLength->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__IntegerConstantArray)
	{
		if (getCellCount() > 1)
			throw range_error("The cumulative length of faces count per cells cannot be constant if there is more than one cell in the grid");
		return true;
	}

	return false;
}

unsigned int UnstructuredGridRepresentation::getConstantFaceCountOfCells() const
{
	_resqml22__UnstructuredGridRepresentation* grid = getSpecializedGsoapProxy();
	if (!isFaceCountOfCellsConstant())
		throw logic_error("The face count per cell is not constant.");

	if (grid->Geometry->CellShape == resqml22__CellShape__hexahedral)
	{
		return 6;
	}
	else if (grid->Geometry->CellShape == resqml22__CellShape__tetrahedral)
	{
		return 4;
	}
	else if (grid->Geometry->FacesPerCell->CumulativeLength->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__IntegerLatticeArray)
	{
		return static_cast<eml23__IntegerLatticeArray*>(grid->Geometry->FacesPerCell->CumulativeLength)->StartValue;
	}
	else if (grid->Geometry->FacesPerCell->CumulativeLength->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__IntegerConstantArray)
	{
		if (getCellCount() > 1)
			throw range_error("The cumulative length of faces count per cells cannot be constant if there is more than one cell in the grid");
		return static_cast<eml23__IntegerConstantArray*>(grid->Geometry->FacesPerCell->CumulativeLength)->Value;
	}
	else
		return 0;
}

void UnstructuredGridRepresentation::getNodeIndicesOfFaces(ULONG64 * nodeIndices) const
{
	_resqml22__UnstructuredGridRepresentation* grid = getSpecializedGsoapProxy();
	if (grid->Geometry == nullptr) {
		throw invalid_argument("There is no geometry in this grid.");
	}
	if (grid->Geometry->NodesPerFace->Elements->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__IntegerExternalArray)
	{
		auto dataset = static_cast<eml23__IntegerExternalArray*>(grid->Geometry->NodesPerFace->Elements)->Values->ExternalFileProxy[0];
		EML2_NS::AbstractHdfProxy * hdfProxy = getHdfProxyFromDataset(dataset);
		hdfProxy->readArrayNdOfULongValues(dataset->PathInExternalFile, nodeIndices);
	}
	else
		throw logic_error("Not yet implemented");
}

void UnstructuredGridRepresentation::getCumulativeNodeCountPerFace(ULONG64 * nodeCountPerFace) const
{
	_resqml22__UnstructuredGridRepresentation* grid = getSpecializedGsoapProxy();
		if (grid->Geometry == nullptr)
			throw invalid_argument("There is no geometry in this grid.");
	if (grid->Geometry->NodesPerFace->CumulativeLength->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__IntegerExternalArray)
	{
		auto dataset = static_cast<eml23__IntegerExternalArray*>(grid->Geometry->NodesPerFace->CumulativeLength)->Values->ExternalFileProxy[0];
		EML2_NS::AbstractHdfProxy * hdfProxy = getHdfProxyFromDataset(dataset);
		hdfProxy->readArrayNdOfULongValues(dataset->PathInExternalFile, nodeCountPerFace);
	}
	else if (grid->Geometry->NodesPerFace->CumulativeLength->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__IntegerLatticeArray)
	{
		nodeCountPerFace[0] = static_cast<eml23__IntegerLatticeArray*>(grid->Geometry->NodesPerFace->CumulativeLength)->StartValue;
		const LONG64 offsetValue = static_cast<eml23__IntegerLatticeArray*>(grid->Geometry->NodesPerFace->CumulativeLength)->Offset[0]->Value;
		const ULONG64 faceCount = getFaceCount();
		for (ULONG64 nodeCountPerFaceIndex = 1; nodeCountPerFaceIndex < faceCount; ++nodeCountPerFaceIndex)
		{
			nodeCountPerFace[nodeCountPerFaceIndex] = nodeCountPerFace[nodeCountPerFaceIndex - 1] + offsetValue;
		}
	}
	else if (grid->Geometry->NodesPerFace->CumulativeLength->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__IntegerConstantArray)
	{
		throw range_error("The *cumulative* length of nodes count per face cannot be constant.");
	}
}

bool UnstructuredGridRepresentation::isNodeCountOfFacesConstant() const
{
	_resqml22__UnstructuredGridRepresentation* grid = getSpecializedGsoapProxy();
	if (grid->Geometry == nullptr)
		throw invalid_argument("There is no geometry in this grid.");
	if (grid->Geometry->CellShape == resqml22__CellShape__hexahedral || grid->Geometry->CellShape == resqml22__CellShape__tetrahedral)
	{
		return true;
	}
	else if (grid->Geometry->NodesPerFace->CumulativeLength->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__IntegerLatticeArray)
	{
		if (static_cast<eml23__IntegerLatticeArray*>(grid->Geometry->NodesPerFace->CumulativeLength)->StartValue == static_cast<eml23__IntegerLatticeArray*>(grid->Geometry->NodesPerFace->CumulativeLength)->Offset[0]->Value)
			return true;
	}

	return false;
}

unsigned int UnstructuredGridRepresentation::getConstantNodeCountOfFaces() const
{
	_resqml22__UnstructuredGridRepresentation* grid = getSpecializedGsoapProxy();
	if (isNodeCountOfFacesConstant() == false)
		throw invalid_argument("The node count per cell is not constant.");

	if (grid->Geometry->CellShape == resqml22__CellShape__hexahedral)
	{
		return 4;
	}
	else if (grid->Geometry->CellShape == resqml22__CellShape__tetrahedral)
	{
		return 3;
	}
	else if (grid->Geometry->NodesPerFace->CumulativeLength->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__IntegerLatticeArray)
	{
		return static_cast<eml23__IntegerLatticeArray*>(grid->Geometry->NodesPerFace->CumulativeLength)->StartValue;
	}
	else
		return 0;
}

void UnstructuredGridRepresentation::getCellFaceIsRightHanded(unsigned char* cellFaceIsRightHanded) const
{
  _resqml22__UnstructuredGridRepresentation* grid = getSpecializedGsoapProxy();
  if (grid->Geometry == nullptr)
    throw invalid_argument("There is no geometry in this grid.");
  if (grid->Geometry->CellFaceIsRightHanded->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__BooleanExternalArray)  {
	  auto dataset = static_cast<eml23__BooleanExternalArray*>(grid->Geometry->CellFaceIsRightHanded)->Values->ExternalFileProxy[0];
	  EML2_NS::AbstractHdfProxy * hdfProxy = getHdfProxyFromDataset(dataset);
	  hdfProxy->readArrayNdOfUCharValues(dataset->PathInExternalFile, cellFaceIsRightHanded);
  }
  else if (grid->Geometry->CellFaceIsRightHanded->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__BooleanConstantArray)  {
	  for (size_t i = 0; i < static_cast<eml23__BooleanConstantArray*>(grid->Geometry->CellFaceIsRightHanded)->Count; ++i)  {
		  cellFaceIsRightHanded[i] = static_cast<eml23__BooleanConstantArray*>(grid->Geometry->CellFaceIsRightHanded)->Value;
	  }
  }
  else
	  throw logic_error("Not yet implemented.");
}

void UnstructuredGridRepresentation::setGeometryUsingExistingDatasets(const std::string& cellFaceIsRightHanded, const std::string& points, ULONG64 pointCount, EML2_NS::AbstractHdfProxy* proxy,
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

	resqml22__UnstructuredGridGeometry* geom = soap_new_resqml22__UnstructuredGridGeometry(gsoapProxy2_3->soap);
	getSpecializedGsoapProxy()->Geometry = geom;
	getSpecializedGsoapProxy()->Geometry->LocalCrs = localCrs->newEml23Reference();

	geom->FaceCount = faceCount;
	geom->NodeCount = pointCount;
	geom->CellShape = static_cast<resqml22__CellShape>(cellShape);

	getRepository()->addRelationship(this, proxy);
	// Face Right handness
	//XML
	eml23__BooleanExternalArray* cellFaceIsRightHandedForHdf5 = soap_new_eml23__BooleanExternalArray(gsoapProxy2_3->soap);
	cellFaceIsRightHandedForHdf5->Values = soap_new_eml23__ExternalDataset(gsoapProxy2_3->soap);
	auto dsPart = soap_new_eml23__ExternalDatasetPart(gsoapProxy2_3->soap);
	dsPart->EpcExternalPartReference = proxy->newEml23Reference();
	dsPart->PathInExternalFile = cellFaceIsRightHanded;
	cellFaceIsRightHandedForHdf5->Values->ExternalFileProxy.push_back(dsPart);
	geom->CellFaceIsRightHanded = cellFaceIsRightHandedForHdf5;

	// Face indices
	//XML
	geom->FacesPerCell = soap_new_eml23__JaggedArray(gsoapProxy2_3->soap);
	// Cumulative
	eml23__IntegerExternalArray* cumulativeLength = soap_new_eml23__IntegerExternalArray(gsoapProxy2_3->soap);
	geom->FacesPerCell->CumulativeLength = cumulativeLength;
	cumulativeLength->NullValue = -1;
	cumulativeLength->Values = soap_new_eml23__ExternalDataset(gsoapProxy2_3->soap);
	dsPart = soap_new_eml23__ExternalDatasetPart(gsoapProxy2_3->soap);
	dsPart->EpcExternalPartReference = proxy->newEml23Reference();
	dsPart->PathInExternalFile = faceIndicesCumulativeCountPerCell;
	cumulativeLength->Values->ExternalFileProxy.push_back(dsPart);
	// Elements
	eml23__IntegerExternalArray* elements = soap_new_eml23__IntegerExternalArray(gsoapProxy2_3->soap);
	geom->FacesPerCell->Elements = elements;
	elements->NullValue = faceCount+1;
	elements->Values = soap_new_eml23__ExternalDataset(gsoapProxy2_3->soap);
	dsPart = soap_new_eml23__ExternalDatasetPart(gsoapProxy2_3->soap);
	dsPart->EpcExternalPartReference = proxy->newEml23Reference();
	dsPart->PathInExternalFile = faceIndicesPerCell;
	elements->Values->ExternalFileProxy.push_back(dsPart);

	// Node indices
	//XML
	geom->NodesPerFace = soap_new_eml23__JaggedArray(gsoapProxy2_3->soap);
	// Cumulative
	cumulativeLength = soap_new_eml23__IntegerExternalArray(gsoapProxy2_3->soap);
	geom->NodesPerFace->CumulativeLength = cumulativeLength;
	cumulativeLength->NullValue = -1;
	cumulativeLength->Values = soap_new_eml23__ExternalDataset(gsoapProxy2_3->soap);
	dsPart = soap_new_eml23__ExternalDatasetPart(gsoapProxy2_3->soap);
	dsPart->EpcExternalPartReference = proxy->newEml23Reference();
	dsPart->PathInExternalFile = nodeIndicesCumulativeCountPerFace;
	cumulativeLength->Values->ExternalFileProxy.push_back(dsPart);
	// Elements
	elements = soap_new_eml23__IntegerExternalArray(gsoapProxy2_3->soap);
	geom->NodesPerFace->Elements = elements;
	elements->NullValue = pointCount+1;
	elements->Values = soap_new_eml23__ExternalDataset(gsoapProxy2_3->soap);
	dsPart = soap_new_eml23__ExternalDatasetPart(gsoapProxy2_3->soap);
	dsPart->EpcExternalPartReference = proxy->newEml23Reference();
	dsPart->PathInExternalFile = nodeIndicesPerFace;
	elements->Values->ExternalFileProxy.push_back(dsPart);

	// XML points
	resqml22__Point3dExternalArray* xmlPoints = soap_new_resqml22__Point3dExternalArray(gsoapProxy2_3->soap);
	geom->Points = xmlPoints;
	xmlPoints->Coordinates = soap_new_eml23__ExternalDataset(gsoapProxy2_3->soap);
	dsPart = soap_new_eml23__ExternalDatasetPart(gsoapProxy2_3->soap);
	dsPart->EpcExternalPartReference = proxy->newEml23Reference();
	dsPart->PathInExternalFile = points;
	xmlPoints->Coordinates->ExternalFileProxy.push_back(dsPart);

	getRepository()->addRelationship(this, localCrs);
}

void UnstructuredGridRepresentation::setConstantCellShapeGeometryUsingExistingDatasets(const std::string& cellFaceIsRightHanded, const std::string& points,
	ULONG64 pointCount, ULONG64 faceCount, RESQML2_NS::AbstractLocal3dCrs * localCrs, EML2_NS::AbstractHdfProxy* proxy,
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

	resqml22__UnstructuredGridGeometry* geom = soap_new_resqml22__UnstructuredGridGeometry(gsoapProxy2_3->soap);
	getSpecializedGsoapProxy()->Geometry = geom;
	getSpecializedGsoapProxy()->Geometry->LocalCrs = localCrs->newEml23Reference();

	geom->FaceCount = faceCount;
	geom->NodeCount = pointCount;
	if (nodeCountPerFace == 3 && faceCountPerCell == 4) {
		geom->CellShape = resqml22__CellShape__tetrahedral;
	}
	else if (nodeCountPerFace == 4 && faceCountPerCell == 6) {
		geom->CellShape = resqml22__CellShape__hexahedral;
	}
	else {
		geom->CellShape = resqml22__CellShape__polyhedral;
	}

	getRepository()->addRelationship(this, proxy);
	// Face Right handness
	//XML
	eml23__BooleanExternalArray* cellFaceIsRightHandedForHdf5 = soap_new_eml23__BooleanExternalArray(gsoapProxy2_3->soap);
	cellFaceIsRightHandedForHdf5->Values = soap_new_eml23__ExternalDataset(gsoapProxy2_3->soap);
	auto dsPart = soap_new_eml23__ExternalDatasetPart(gsoapProxy2_3->soap);
	dsPart->EpcExternalPartReference = proxy->newEml23Reference();
	dsPart->PathInExternalFile = cellFaceIsRightHanded;
	cellFaceIsRightHandedForHdf5->Values->ExternalFileProxy.push_back(dsPart);
	geom->CellFaceIsRightHanded = cellFaceIsRightHandedForHdf5;

	// Face indices
	//XML
	geom->FacesPerCell = soap_new_eml23__JaggedArray(gsoapProxy2_3->soap);
	// Cumulative
	if (cellCount == 1)
	{
		eml23__IntegerConstantArray* cumulativeLength = soap_new_eml23__IntegerConstantArray(gsoapProxy2_3->soap);
		geom->FacesPerCell->CumulativeLength = cumulativeLength;
		cumulativeLength->Count = cellCount;
		cumulativeLength->Value = faceCountPerCell;
	}
	else
	{
		eml23__IntegerLatticeArray* cumulativeLength = soap_new_eml23__IntegerLatticeArray(gsoapProxy2_3->soap);
		geom->FacesPerCell->CumulativeLength = cumulativeLength;
		cumulativeLength->StartValue = faceCountPerCell;
		cumulativeLength->Offset.push_back(soap_new_eml23__IntegerConstantArray(gsoapProxy2_3->soap, 1));
		cumulativeLength->Offset[0]->Count = cellCount - 1;
		cumulativeLength->Offset[0]->Value = faceCountPerCell;
	}
	// Elements
	eml23__IntegerExternalArray* elements = soap_new_eml23__IntegerExternalArray(gsoapProxy2_3->soap);
	geom->FacesPerCell->Elements = elements;
	elements->NullValue = faceCount+1;
	elements->Values = soap_new_eml23__ExternalDataset(gsoapProxy2_3->soap);
	dsPart = soap_new_eml23__ExternalDatasetPart(gsoapProxy2_3->soap);
	dsPart->EpcExternalPartReference = proxy->newEml23Reference();
	dsPart->PathInExternalFile = faceIndicesPerCell;
	elements->Values->ExternalFileProxy.push_back(dsPart);

	// Node indices
	//XML
	geom->NodesPerFace = soap_new_eml23__JaggedArray(gsoapProxy2_3->soap);
	// Cumulative
	eml23__IntegerLatticeArray* cumulativeLength = soap_new_eml23__IntegerLatticeArray(gsoapProxy2_3->soap);
	geom->NodesPerFace->CumulativeLength = cumulativeLength;
	cumulativeLength->StartValue = nodeCountPerFace;
	cumulativeLength->Offset.push_back(soap_new_eml23__IntegerConstantArray(gsoapProxy2_3->soap, 1));
	cumulativeLength->Offset[0]->Count = geom->FaceCount - 1;
	cumulativeLength->Offset[0]->Value = nodeCountPerFace;
	// Elements
	elements = soap_new_eml23__IntegerExternalArray(gsoapProxy2_3->soap);
	geom->NodesPerFace->Elements = elements;
	elements->NullValue = pointCount+1;
	elements->Values = soap_new_eml23__ExternalDataset(gsoapProxy2_3->soap);
	dsPart = soap_new_eml23__ExternalDatasetPart(gsoapProxy2_3->soap);
	dsPart->EpcExternalPartReference = proxy->newEml23Reference();
	dsPart->PathInExternalFile = nodeIndicesPerFace;
	elements->Values->ExternalFileProxy.push_back(dsPart);

	// XML points
	resqml22__Point3dExternalArray* xmlPoints = soap_new_resqml22__Point3dExternalArray(gsoapProxy2_3->soap);
	geom->Points = xmlPoints;
	xmlPoints->Coordinates = soap_new_eml23__ExternalDataset(gsoapProxy2_3->soap);
	dsPart = soap_new_eml23__ExternalDatasetPart(gsoapProxy2_3->soap);
	dsPart->EpcExternalPartReference = proxy->newEml23Reference();
	dsPart->PathInExternalFile = points;
	xmlPoints->Coordinates->ExternalFileProxy.push_back(dsPart);

	getRepository()->addRelationship(this, localCrs);
}
