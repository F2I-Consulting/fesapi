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

#include "../eml2/AbstractHdfProxy.h"

#include "../eml2/AbstractLocal3dCrs.h"

using namespace std;
using namespace gsoap_resqml2_0_1;
using namespace RESQML2_NS;

const char* UnstructuredGridRepresentation::XML_TAG = "UnstructuredGridRepresentation";

uint64_t UnstructuredGridRepresentation::getXyzPointCountOfPatch(unsigned int patchIndex) const
{
	if (patchIndex >= getPatchCount()) {
		throw out_of_range("The index of the patch is not in the allowed range of patch.");
	}

	return getNodeCount();
}

uint64_t const * UnstructuredGridRepresentation::getCumulativeFaceCountPerCell() const
{
	if (constantFaceCountPerCell != 0) {
		throw logic_error("This grid has a constant count of faces per cell. Please compute the cumulative count by your own.");
	}

	if (!cumulativeFaceCountPerCell) {
		throw logic_error("The geometry must have been loaded first.");
	}

	return cumulativeFaceCountPerCell.get();
}

void UnstructuredGridRepresentation::getFaceCountPerCell(uint64_t * faceCountPerCell) const
{
	getCumulativeFaceCountPerCell(faceCountPerCell);
	const uint64_t cellCount = getCellCount();
	uint64_t buffer = faceCountPerCell[0];
	uint64_t bufferCumCount = 0;
	for (uint64_t cumulativeFaceCountPerCellIndex = 1; cumulativeFaceCountPerCellIndex < cellCount; ++cumulativeFaceCountPerCellIndex)
	{
		bufferCumCount = faceCountPerCell[cumulativeFaceCountPerCellIndex];
		faceCountPerCell[cumulativeFaceCountPerCellIndex] -= buffer;
		buffer = bufferCumCount;
	}
}

void UnstructuredGridRepresentation::getNodeCountPerFace(uint64_t * nodeCountPerFace) const
{
	getCumulativeNodeCountPerFace(nodeCountPerFace);
	const uint64_t faceCount = getFaceCount();
	uint64_t buffer = nodeCountPerFace[0];
	uint64_t bufferCumCount = 0;
	for (uint64_t cumulativeNodeCountPerFaceIndex = 1; cumulativeNodeCountPerFaceIndex < faceCount; ++cumulativeNodeCountPerFaceIndex)
	{
		bufferCumCount = nodeCountPerFace[cumulativeNodeCountPerFaceIndex];
		nodeCountPerFace[cumulativeNodeCountPerFaceIndex] -= buffer;
		buffer = bufferCumCount;
	}
}

void UnstructuredGridRepresentation::setGeometry(unsigned char * cellFaceIsRightHanded, double * points, uint64_t pointCount, EML2_NS::AbstractHdfProxy * proxy,
	uint64_t * faceIndicesPerCell, uint64_t * faceIndicesCumulativeCountPerCell,
	uint64_t faceCount, uint64_t * nodeIndicesPerFace, uint64_t * nodeIndicesCumulativeCountPerFace,
	gsoap_resqml2_0_1::resqml20__CellShape cellShape, EML2_NS::AbstractLocal3dCrs * localCrs)
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

	const uint64_t cellCount = getCellCount();

	// HDF Face Right handness
	unsigned long long faceCountTmp = faceIndicesCumulativeCountPerCell[cellCount - 1]; // For GCC : uint64_t is not exactly an unsigned long long with GCC but an uint64_t {aka long unsigned int}
	proxy->writeArrayNd(getHdfGroup(), "CellFaceIsRightHanded", H5T_NATIVE_UCHAR, cellFaceIsRightHanded, &faceCountTmp, 1);

	// HDF Face indices
	proxy->writeItemizedListOfList(getHdfGroup(), "FacesPerCell", H5T_NATIVE_UINT64, faceIndicesCumulativeCountPerCell, cellCount, H5T_NATIVE_UINT64, faceIndicesPerCell, faceIndicesCumulativeCountPerCell[cellCount - 1]);

	// HDF Node indices
	proxy->writeItemizedListOfList(getHdfGroup(), "NodesPerFace", H5T_NATIVE_UINT64, nodeIndicesCumulativeCountPerFace, faceCount, H5T_NATIVE_UINT64, nodeIndicesPerFace, nodeIndicesCumulativeCountPerFace[faceCount - 1]);

	// HDF points
	hsize_t numValues[2] = { pointCount, 3 };
	proxy->writeArrayNdOfDoubleValues(getHdfGroup(), "Points", points, numValues, 2);

	setGeometryUsingExistingDatasets(getHdfGroup() + "/CellFaceIsRightHanded", getHdfGroup() + "/Points", pointCount, proxy,
		getHdfGroup() + "/FacesPerCell/" + EML2_NS::AbstractHdfProxy::ELEMENTS_DS_NAME, getHdfGroup() + "/FacesPerCell/" + EML2_NS::AbstractHdfProxy::CUMULATIVE_LENGTH_DS_NAME,
		faceCount, getHdfGroup() + "/NodesPerFace/" + EML2_NS::AbstractHdfProxy::ELEMENTS_DS_NAME, getHdfGroup() + "/NodesPerFace/" + EML2_NS::AbstractHdfProxy::CUMULATIVE_LENGTH_DS_NAME,
		cellShape, localCrs);
}

void UnstructuredGridRepresentation::setConstantCellShapeGeometry(unsigned char * cellFaceIsRightHanded, double * points,
	uint64_t pointCount, uint64_t faceCount, EML2_NS::AbstractLocal3dCrs * localCrs, EML2_NS::AbstractHdfProxy* proxy,
	uint64_t * faceIndicesPerCell, uint64_t faceCountPerCell,
	uint64_t * nodeIndicesPerFace, uint64_t nodeCountPerFace)
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

	const uint64_t cellCount = getCellCount();

	// HDF Face Right handness
	unsigned long long faceCountTmp = faceCountPerCell * cellCount; // For GCC : uint64_t is not exactly an unsigned long long with GCC but an uint64_t {aka long unsigned int}
	proxy->writeArrayNd(getHdfGroup(), "CellFaceIsRightHanded", H5T_NATIVE_UCHAR, cellFaceIsRightHanded, &faceCountTmp, 1);

	// HDF Face indices
	hsize_t numValues[2] = { cellCount, faceCountPerCell };
	proxy->writeArrayNd(getHdfGroup(), "FacesPerCell", H5T_NATIVE_UINT64, faceIndicesPerCell, numValues, 2);

	// HDF Node indices
	numValues[0] = faceCount;
	numValues[1] = nodeCountPerFace;
	proxy->writeArrayNd(getHdfGroup(), "NodesPerFace", H5T_NATIVE_UINT64, nodeIndicesPerFace, numValues, 2);

	// HDF points
	numValues[0] = pointCount;
	numValues[1] = 3; // 3 for X, Y and Z
	proxy->writeArrayNdOfDoubleValues(getHdfGroup(), "Points", points, numValues, 2);

	setConstantCellShapeGeometryUsingExistingDatasets(getHdfGroup() + "/CellFaceIsRightHanded", getHdfGroup() + "/Points",
		pointCount, faceCount, localCrs, proxy,
		getHdfGroup() + "/FacesPerCell", faceCountPerCell,
		getHdfGroup() + "/NodesPerFace", nodeCountPerFace);
}

void UnstructuredGridRepresentation::setTetrahedraOnlyGeometryUsingExistingDatasets(const std::string& cellFaceIsRightHanded, const std::string& points,
	uint64_t pointCount, uint64_t faceCount, EML2_NS::AbstractHdfProxy* proxy,
	const std::string& faceIndicesPerCell, const std::string& nodeIndicesPerFace, EML2_NS::AbstractLocal3dCrs * localCrs)
{
	setConstantCellShapeGeometryUsingExistingDatasets(cellFaceIsRightHanded, points,
		pointCount, faceCount, localCrs, proxy,
		faceIndicesPerCell, 4,
		nodeIndicesPerFace, 3);
}

void UnstructuredGridRepresentation::setTetrahedraOnlyGeometry(unsigned char * cellFaceIsRightHanded, double * points, uint64_t pointCount, uint64_t faceCount, EML2_NS::AbstractHdfProxy * proxy,
	uint64_t * faceIndicesPerCell, uint64_t * nodeIndicesPerFace, EML2_NS::AbstractLocal3dCrs * localCrs)
{
	setConstantCellShapeGeometry(cellFaceIsRightHanded, points,
		pointCount, faceCount, localCrs, proxy,
		faceIndicesPerCell, 4,
		nodeIndicesPerFace, 3);
}

void UnstructuredGridRepresentation::setHexahedraOnlyGeometryUsingExistingDatasets(const std::string& cellFaceIsRightHanded, const std::string& points,
	uint64_t pointCount, uint64_t faceCount, EML2_NS::AbstractHdfProxy* proxy,
	const std::string& faceIndicesPerCell, const std::string& nodeIndicesPerFace, EML2_NS::AbstractLocal3dCrs * localCrs)
{
	setConstantCellShapeGeometryUsingExistingDatasets(cellFaceIsRightHanded, points,
		pointCount, faceCount, localCrs, proxy,
		faceIndicesPerCell, 6,
		nodeIndicesPerFace, 4);
}

void UnstructuredGridRepresentation::setHexahedraOnlyGeometry(unsigned char * cellFaceIsRightHanded, double * points, uint64_t pointCount, uint64_t faceCount, EML2_NS::AbstractHdfProxy * proxy,
	uint64_t * faceIndicesPerCell, uint64_t * nodeIndicesPerFace, EML2_NS::AbstractLocal3dCrs * localCrs)
{
	setConstantCellShapeGeometry(cellFaceIsRightHanded, points,
		pointCount, faceCount, localCrs, proxy,
		faceIndicesPerCell, 6,
		nodeIndicesPerFace, 4);
}

void UnstructuredGridRepresentation::loadGeometry()
{
	unloadGeometry();

	if (isNodeCountOfFacesConstant()) {
		constantNodeCountPerFace = getConstantNodeCountOfFaces();
		nodeIndicesOfFaces.reset(new uint64_t[constantNodeCountPerFace * getFaceCount()]);
	}
	else {
		cumulativeNodeCountPerFace.reset(new uint64_t[getFaceCount()]);
		getCumulativeNodeCountPerFace(cumulativeNodeCountPerFace.get());
		nodeIndicesOfFaces.reset(new uint64_t[cumulativeNodeCountPerFace[getFaceCount() - 1]]);
	}

	if (isFaceCountOfCellsConstant()) {
		constantFaceCountPerCell = getConstantFaceCountOfCells();
		faceIndicesOfCells.reset(new uint64_t[constantFaceCountPerCell * getCellCount()]);
	}
	else {
		cumulativeFaceCountPerCell.reset(new uint64_t[getCellCount()]);
		getCumulativeFaceCountPerCell(cumulativeFaceCountPerCell.get());
		faceIndicesOfCells.reset(new uint64_t[cumulativeFaceCountPerCell[getCellCount() - 1]]);
	}

	getNodeIndicesOfFaces(nodeIndicesOfFaces.get());

	getFaceIndicesOfCells(faceIndicesOfCells.get());
}

void UnstructuredGridRepresentation::unloadGeometry()
{
	constantNodeCountPerFace = 0;
	constantFaceCountPerCell = 0;

	cumulativeNodeCountPerFace.reset();
	cumulativeFaceCountPerCell.reset();
	nodeIndicesOfFaces.reset();
	faceIndicesOfCells.reset();
}

unsigned int UnstructuredGridRepresentation::getFaceCountOfCell(uint64_t cellIndex) const
{
	if (cellIndex >= getCellCount()) {
		throw out_of_range("The cell index is out of range.");
	}

	if (constantFaceCountPerCell != 0) {
		return constantFaceCountPerCell;
	}

	if (!faceIndicesOfCells) {
		throw logic_error("The geometry must have been loaded first.");
	}

	if (cellIndex == 0) {
		if (cumulativeFaceCountPerCell[0] < (std::numeric_limits<uint32_t>::lowest)() || cumulativeFaceCountPerCell[0] >(std::numeric_limits<uint32_t>::max)()) {
			throw range_error("The count of face is not in the uint32_t range");
		}

		return static_cast<uint32_t>(cumulativeFaceCountPerCell[0]);
	}
	
	auto result = cumulativeFaceCountPerCell[cellIndex] - cumulativeFaceCountPerCell[cellIndex - 1];
	if (result < (std::numeric_limits<uint32_t>::lowest)() || result >(std::numeric_limits<uint32_t>::max)()) {
		throw range_error("The count of face is not in the uint32_t range");
	}
	return static_cast<uint32_t>(result);
}

uint64_t UnstructuredGridRepresentation::getGlobalFaceIndex(uint64_t cellIndex, unsigned int localFaceIndex) const
{
	if (!faceIndicesOfCells) {
		throw invalid_argument("The geometry must have been loaded first.");
	}
	if (cellIndex >= getCellCount()) {
		throw range_error("The cell index is out of range.");
	}
	if (localFaceIndex >= getFaceCountOfCell(cellIndex)) {
		throw range_error("The face index is out of range.");
	}

	uint64_t globalFaceIndex = 0;
	if (cellIndex == 0) {
		globalFaceIndex = faceIndicesOfCells[localFaceIndex];
	}
	else {
		globalFaceIndex = constantFaceCountPerCell != 0
			? faceIndicesOfCells[constantFaceCountPerCell * cellIndex + localFaceIndex]
			: faceIndicesOfCells[cumulativeFaceCountPerCell[cellIndex - 1] + localFaceIndex];
	}

	return globalFaceIndex;
}

unsigned int UnstructuredGridRepresentation::getNodeCountOfFaceOfCell(uint64_t cellIndex, unsigned int localFaceIndex) const
{
	if (constantNodeCountPerFace != 0) {
		return constantNodeCountPerFace;
	}

	const uint64_t globalFaceIndex = getGlobalFaceIndex(cellIndex, localFaceIndex);

	if (globalFaceIndex == 0) {
		if (cumulativeFaceCountPerCell[0] < (std::numeric_limits<uint32_t>::lowest)() || cumulativeFaceCountPerCell[0] >(std::numeric_limits<uint32_t>::max)()) {
			throw range_error("The count of face is not in the uint32_t range");
		}
		return static_cast<uint32_t>(cumulativeNodeCountPerFace[0]);
	}

	auto result = cumulativeNodeCountPerFace[globalFaceIndex] - cumulativeNodeCountPerFace[globalFaceIndex - 1];
	if (result < (std::numeric_limits<uint32_t>::lowest)() || result >(std::numeric_limits<uint32_t>::max)()) {
		throw range_error("The count of nodes is not in the uint32_t range");
	}
	return static_cast<uint32_t>(result);
}

uint64_t const * UnstructuredGridRepresentation::getNodeIndicesOfFaceOfCell(uint64_t cellIndex, unsigned int localFaceIndex) const
{
	const uint64_t globalFaceIndex = getGlobalFaceIndex(cellIndex, localFaceIndex);

	if (globalFaceIndex == 0) {
		return nodeIndicesOfFaces.get();
	}

	if (constantNodeCountPerFace != 0)
		return &(nodeIndicesOfFaces[constantNodeCountPerFace * globalFaceIndex]);
	else
		return &(nodeIndicesOfFaces[cumulativeNodeCountPerFace[globalFaceIndex - 1]]);
}
