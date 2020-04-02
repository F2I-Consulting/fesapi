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

#pragma once

#include "../resqml2/UnstructuredGridRepresentation.h"

namespace RESQML2_2_NS
{
	class UnstructuredGridRepresentation final : public RESQML2_NS::UnstructuredGridRepresentation
	{
	public:

		/**
		* Only to be used in partial transfer context
		*/
		DLL_IMPORT_OR_EXPORT UnstructuredGridRepresentation(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject):
			RESQML2_NS::UnstructuredGridRepresentation(partialObject) {}

		/**
		* @param soapContext	The soap context where the underlying gsoap proxy is going to be created.
		*/
		UnstructuredGridRepresentation(COMMON_NS::DataObjectRepository* repo,
			const std::string & guid, const std::string & title,
			ULONG64 cellCount);

		UnstructuredGridRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp,
			const std::string & guid, const std::string & title,
			ULONG64 cellCount);

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		UnstructuredGridRepresentation(gsoap_eml2_3::_resqml22__UnstructuredGridRepresentation* fromGsoap):
			RESQML2_NS::UnstructuredGridRepresentation(fromGsoap) {}

		/**
		* Destructor does nothing since the memory is managed by the gsoap context.
		*/
		~UnstructuredGridRepresentation() {}

		/**
		* Indicates wether the grid has a geometry or not.
		*/
		DLL_IMPORT_OR_EXPORT bool hasGeometry() const final;

		COMMON_NS::DataObjectReference getHdfProxyDor() const final;

		/**
		* Get all the XYZ points of a particular patch of this representation.
		* XYZ points are given in the local CRS.
		* @param xyzPoints A linearized 2d array where the first (quickest) dimension is coordinate dimension (XYZ) and second dimension is vertex dimension. It must be pre allocated.
		*/
		DLL_IMPORT_OR_EXPORT void getXyzPointsOfPatch(unsigned int patchIndex, double * xyzPoints) const final;

		/**
		 * Get all the face indices of all the cells.
		 * @param faceIndices 			It must be pre allocated with the last value returned by getCumulativeFaceCountPerCell()
		 */
		DLL_IMPORT_OR_EXPORT void getFaceIndicesOfCells(ULONG64 * faceIndices) const final;

		/**
		* Get the cumulative face count per cell. First value is the count of faces in the first cell.
		* Second value is the count of faces in the first and in the second cell. Third value is the count of faces in the first and in the second and in the third cell. Etc...
		* Count of this array is equal to getCellCount()
		* A single face count should be at least 4.
		* @param cumulativeFaceCountPerCellIndex	It must be pre allocated with getCellCount()
		*/
		DLL_IMPORT_OR_EXPORT void getCumulativeFaceCountPerCell(ULONG64 * cumulativeFaceCountPerCell_) const final;

		/**
		* Detect if the face count per cell is constant in the grid.
		*/
		DLL_IMPORT_OR_EXPORT bool isFaceCountOfCellsConstant() const final;

		/*
		* Get the constant face count per cell in the grid.
		*/
		DLL_IMPORT_OR_EXPORT unsigned int getConstantFaceCountOfCells() const final;

		/**
		 * Get all the node indices of all the faces.
		 * @param nodeIndices	It must be pre allocated with the last value returned by getCumulativeNodeCountPerFace().
		 */
		DLL_IMPORT_OR_EXPORT void getNodeIndicesOfFaces(ULONG64 * nodeIndices) const final;

		/**
		* Get the cumulative node count per face. First value is the count of nodes in the first face.
		* Second value is the count of nodes in the first and in the second face. Third value is the count of nodes in the first and in the second and in the third face. Etc...
		* Count of this array is equal to getFaceCount()
		* A single node count should be at least 3.
		* @param nodeCountPerFace	It must be pre allocated with the last value of getFaceCount().
		*/
		DLL_IMPORT_OR_EXPORT void getCumulativeNodeCountPerFace(ULONG64 * nodeCountPerFace) const final;

		/**
		* Detect if the node count per face is constant in the grid.
		*/
		DLL_IMPORT_OR_EXPORT bool isNodeCountOfFacesConstant() const final;

		/*
		* Get the constant node count per face in the grid.
		*/
		DLL_IMPORT_OR_EXPORT unsigned int getConstantNodeCountOfFaces() const final;

		/**
		 * Get the cell count
		 */
		DLL_IMPORT_OR_EXPORT ULONG64 getCellCount() const final;

		/**
		 * Get the face count
		 */
		DLL_IMPORT_OR_EXPORT ULONG64 getFaceCount() const final;

		/**
		 * Get the node count
		 */
		DLL_IMPORT_OR_EXPORT ULONG64 getNodeCount() const final;

    	/**
	    * Retrieves orientation i.e. if each cell face is right handed or not
    	*/
		DLL_IMPORT_OR_EXPORT void getCellFaceIsRightHanded(unsigned char* cellFaceIsRightHanded) const final;

		/**
		* Set the geometry using some existing hdf5 dataset
		* @param isRightHanded						The path to the hdf5 dataset in the hdf proxy where a boolean mask is used to indicate which cell faces have an outwardly directed normal following a right hand rule. Array length is the sum of the cell face count per cell, and the data follows the order of the faces per cell RESQMLlist-of-lists.
		* @param points								The path to the hdf5 dataset in the hdf proxy where all the XYZ points defining the nodes of the unstructured grid are defined. There must a double count of pointCount * 3.
		* @param pointCount							The count of points defining the nodes of this unstructured grid.
		* @param proxy								The hdf proxy which contains the datasets given inthis method by means of path.
		* @param faceIndicesPerCell					The path to the hdf5 dataset in the hdf proxy where each item defines the index of the face of a cell. There must be a count of the last value in faceIndicesCumulativeCountPerCell.
		* @param faceIndicesCumulativeCountPerCell	The path to the hdf5 dataset in the hdf proxy where each item defines the cumulative count of faces. The count of this array must be equal to the count of cells in this unstructured grid. For example if the first cell a 4 faces, the second cell 5 faces and the third cell 6 faces then the array would be {4, 9, 15}
		* @param faceCount							The count of faces in this unstructured grid. Be aware this count does not duplicate shared faces. Most of time, you have less faceCount than the last value of faceIndicesCumulativeCountPerCell which is the count of faces per cell.
		* @param nodeIndicesPerFace					The path to the hdf5 dataset in the hdf proxy where each item defines the index of the node of a face. There must be a count of the last value in nodeIndicesCumulativeCountPerFace.
		* @param nodeIndicesCumulativeCountPerFace	The path to the hdf5 dataset in the hdf proxy where each item defines the cumulative count of nodes. The count of this array must be eqaul to faceCount.
		* @param cellShape							A denormalization of the information which gives quick access to the most complex shape of polyhedron encountered in this unstructured grid.
		*/
		DLL_IMPORT_OR_EXPORT void setGeometryUsingExistingDatasets(const std::string& cellFaceIsRightHanded, const std::string& points, ULONG64 pointCount, EML2_NS::AbstractHdfProxy* proxy,
			const std::string& faceIndicesPerCell, const std::string& faceIndicesCumulativeCountPerCell,
			ULONG64 faceCount, const std::string& nodeIndicesPerFace, const std::string& nodeIndicesCumulativeCountPerFace,
			gsoap_resqml2_0_1::resqml20__CellShape cellShape, RESQML2_NS::AbstractLocal3dCrs * localCrs = nullptr) final;

	private:

		/**
		* @param soapContext	The soap context where the underlying gsoap proxy is going to be created.
		*/
		void init(COMMON_NS::DataObjectRepository* repo,
			const std::string & guid, const std::string & title,
			ULONG64 cellCount);

		gsoap_eml2_3::_resqml22__UnstructuredGridRepresentation* getSpecializedGsoapProxy() const;

		gsoap_eml2_3::resqml22__PointGeometry* getPointGeometry2_2(unsigned int patchIndex) const final;

		/**
		* Set a geometry using some existing hdf5 dataset. This geometry only contains polyedra with constant face count per cell and constant node count per face.
		* @param isRightHanded						The path to the hdf5 dataset in the hdf proxy where a boolean mask is used to indicate which cell faces have an outwardly directed normal following a right hand rule. Array length is the sum of the cell face count per cell, and the data follows the order of the faces per cell RESQMLlist-of-lists.
		* @param points								The path to the hdf5 dataset in the hdf proxy where all the XYZ points defining the nodes of the unstructured grid are defined. There must a double count of pointCount * 3.
		* @param pointCount							The count of points defining the nodes of this unstructured grid.
		* @param faceCount							The count of faces in this unstructured grid. Be aware this count does not duplicate shared faces. Most of time, you have less faceCount than the last value of faceIndicesCumulativeCountPerCell which is the count of faces per cell.
		* @param proxy								The hdf proxy which contains the datasets given inthis method by means of path.
		* @param faceIndicesPerCell					The path to the hdf5 dataset in the hdf proxy where each item defines the index of the face of a cell. There must be a count of faceCountPerCell * cellCount.
		* @param faceCountPerCell					The constant face count per cell.
		* @param nodeIndicesPerFace					The path to the hdf5 dataset in the hdf proxy where each item defines the index of the node of a face. There must be a count of nodeCountPerFace * faceCount.
		* @param nodeCountPerFace					The constant node count per face.
		*/
		void setConstantCellShapeGeometryUsingExistingDatasets(const std::string& cellFaceIsRightHanded, const std::string& points,
			ULONG64 pointCount, ULONG64 faceCount, RESQML2_NS::AbstractLocal3dCrs * localCrs, EML2_NS::AbstractHdfProxy* proxy,
			const std::string& faceIndicesPerCell, ULONG64 faceCountPerCell,
			const std::string& nodeIndicesPerFace, ULONG64 nodeCountPerFace) final;
	};
}
