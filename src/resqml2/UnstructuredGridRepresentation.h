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

#include "AbstractGridRepresentation.h"

namespace RESQML2_NS
{
	class UnstructuredGridRepresentation : public AbstractGridRepresentation
	{
	public:

		/**
		* Only to be used in partial transfer context
		*/
		DLL_IMPORT_OR_EXPORT UnstructuredGridRepresentation(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject):
			AbstractGridRepresentation(partialObject, false), constantNodeCountPerFace(0), constantFaceCountPerCell(0),
			cumulativeNodeCountPerFace(nullptr), cumulativeFaceCountPerCell(nullptr),
			nodeIndicesOfFaces(nullptr), faceIndicesOfCells(nullptr) {}

		/**
		* @param soapContext	The soap context where the underlying gsoap proxy is going to be created.
		*/
		UnstructuredGridRepresentation() :
			AbstractGridRepresentation(false), constantNodeCountPerFace(0), constantFaceCountPerCell(0),
			cumulativeNodeCountPerFace(nullptr), cumulativeFaceCountPerCell(nullptr),
			nodeIndicesOfFaces(nullptr), faceIndicesOfCells(nullptr) {}

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		UnstructuredGridRepresentation(gsoap_resqml2_0_1::_resqml20__UnstructuredGridRepresentation* fromGsoap) :
			RESQML2_NS::AbstractGridRepresentation(fromGsoap, false), constantNodeCountPerFace(0), constantFaceCountPerCell(0),
			cumulativeNodeCountPerFace(nullptr), cumulativeFaceCountPerCell(nullptr),
			nodeIndicesOfFaces(nullptr), faceIndicesOfCells(nullptr) {}

		/**
		* Destructor does nothing since the memory is managed by the gsoap context.
		*/
		virtual ~UnstructuredGridRepresentation() {}

		/**
		* Indicates wether the grid has a geometry or not.
		*/
		DLL_IMPORT_OR_EXPORT virtual bool hasGeometry() const = 0;

		/**
		* Get the xyz point count in a given patch.
		*/
		DLL_IMPORT_OR_EXPORT ULONG64 getXyzPointCountOfPatch(const unsigned int & patchIndex) const;

		/**
		 * Get all the face indices of all the cells.
		 * @param faceIndices 			It must be pre allocated with the last value returned by getCumulativeFaceCountPerCell()
		 */
		DLL_IMPORT_OR_EXPORT virtual void getFaceIndicesOfCells(ULONG64 * faceIndices) const = 0;

		/**
		* Get the cumulative face count per cell. First value is the count of faces in the first cell.
		* Second value is the count of faces in the first and in the second cell. Third value is the count of faces in the first and in the second and in the third cell. Etc...
		* Count of this array is equal to getCellCount()
		* A single face count should be at least 4.
		* @param cumulativeFaceCountPerCellIndex	It must be pre allocated with getCellCount()
		*/
		DLL_IMPORT_OR_EXPORT virtual void getCumulativeFaceCountPerCell(ULONG64 * cumulativeFaceCountPerCell_) const = 0;

		/**
		* Less efficient than getCumulativeFaceCountPerCell.
		* Get the face count per cell. First value is the count of faces in the first cell.
		* Second value is the count of faces in the second cell. etc...
		* @param faceCountPerCell	It must be pre allocated with getCellCount()
		*/
		DLL_IMPORT_OR_EXPORT void getFaceCountPerCell(ULONG64 * faceCountPerCell) const;

		/**
		* Detect if the face count per cell is constant in the grid.
		*/
		DLL_IMPORT_OR_EXPORT virtual bool isFaceCountOfCellsConstant() const = 0;

		/*
		* Get the constant face count per cell in the grid.
		*/
		DLL_IMPORT_OR_EXPORT virtual unsigned int getConstantFaceCountOfCells() const = 0;

		/**
		 * Get all the node indices of all the faces.
		 * @param nodeIndices	It must be pre allocated with the last value returned by getCumulativeNodeCountPerFace().
		 */
		DLL_IMPORT_OR_EXPORT virtual void getNodeIndicesOfFaces(ULONG64 * nodeIndices) const = 0;

		/**
		* Get the cumulative node count per face. First value is the count of nodes in the first face.
		* Second value is the count of nodes in the first and in the second face. Third value is the count of nodes in the first and in the second and in the third face. Etc...
		* Count of this array is equal to getFaceCount()
		* A single node count should be at least 3.
		* @param nodeCountPerFace	It must be pre allocated with the last value of getFaceCount().
		*/
		DLL_IMPORT_OR_EXPORT virtual void getCumulativeNodeCountPerFace(ULONG64 * nodeCountPerFace) const = 0;

		/**
		* Less efficient than getCumulativeNodeCountPerFace.
		* Get the node count per face. First value is the count of nodes in the first face.
		* Second value is the count of nodes in the second face. etc...
		* @param nodeCountPerFace	It must be pre allocated with the last value of getFaceCount().
		*/
		DLL_IMPORT_OR_EXPORT void getNodeCountPerFace(ULONG64 * nodeCountPerFace) const;

		/**
		* Detect if the node count per face is constant in the grid.
		*/
		DLL_IMPORT_OR_EXPORT virtual bool isNodeCountOfFacesConstant() const = 0;

		/*
		* Get the constant node count per face in the grid.
		*/
		DLL_IMPORT_OR_EXPORT virtual unsigned int getConstantNodeCountOfFaces() const = 0;

		/**
		* Load the geoemtry into memory in order to ease access.
		* Be aware that you must unload by yourself this memory.
		*/
		DLL_IMPORT_OR_EXPORT void loadGeometry();

		/**
		* Unload the split information from memory.
		*/
		DLL_IMPORT_OR_EXPORT void unloadGeometry();

		/**
		* This method requires your have already loaded the geometry.
		* @return The count of faces in a particular cell.
		*/
		DLL_IMPORT_OR_EXPORT unsigned int getFaceCountOfCell(ULONG64 cellIndex) const;
	
		/**
		* This method requires your have already loaded the geometry.
		* @return The count of nodes in a particular face of a particular cell.
		*/
		DLL_IMPORT_OR_EXPORT unsigned int getNodeCountOfFaceOfCell(ULONG64 cellIndex, unsigned int localFaceIndex) const;

		/**
		* This method requires your have already loaded the geometry.
		* It gets all the node indices of a particular face of a particular cell
		*/
		DLL_IMPORT_OR_EXPORT ULONG64 * getNodeIndicesOfFaceOfCell(ULONG64 cellIndex, unsigned int localFaceIndex) const;

		/**
		 * Get the cell count
		 */
		DLL_IMPORT_OR_EXPORT virtual ULONG64 getCellCount() const = 0;

		/**
		 * Get the face count
		 */
		DLL_IMPORT_OR_EXPORT virtual ULONG64 getFaceCount() const = 0;

		/**
		 * Get the node count
		 */
		DLL_IMPORT_OR_EXPORT virtual ULONG64 getNodeCount() const = 0;

    	/**
	    * Retrieves orientation i.e. if each cell face is right handed or not
    	*/
		DLL_IMPORT_OR_EXPORT virtual void getCellFaceIsRightHanded(unsigned char* cellFaceIsRightHanded) const = 0;

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
		DLL_IMPORT_OR_EXPORT virtual void setGeometryUsingExistingDatasets(const std::string& cellFaceIsRightHanded, const std::string& points, ULONG64 pointCount, COMMON_NS::AbstractHdfProxy* proxy,
			const std::string& faceIndicesPerCell, const std::string& faceIndicesCumulativeCountPerCell,
			ULONG64 faceCount, const std::string& nodeIndicesPerFace, const std::string& nodeIndicesCumulativeCountPerFace,
			gsoap_resqml2_0_1::resqml20__CellShape cellShape, RESQML2_NS::AbstractLocal3dCrs * localCrs = nullptr) = 0;

		/**
		 * Set the geometry and creates corresponding HDF5 datasets.
		 * @param isRightHanded						Boolean mask used to indicate which cell faces have an outwardly directed normal following a right hand rule. Array length is the sum of the cell face count per cell, and the data follows the order of the faces per cell RESQMLlist-of-lists.
		 * @param points							All the XYZ points defining the nodes of the unstructured grid. There must a double count of pointCount * 3.
		 * @param pointCount						The count of points defining the nodes of this unstructured grid.
		 * @param proxy								The hdf proxy which will store all the numerical values of this unstructured grid.
		 * @param faceIndicesPerCell				Each item defines the index of the face of a cell. There must be a count of the last value in faceIndicesCumulativeCountPerCell.
		 * @param faceIndicesCumulativeCountPerCell	Each item defines the cumulative count of faces. The count of this array must be equal to the count of cells in this unstructured grid. For example if the first cell a 4 faces, the second cell 5 faces and the third cell 6 faces then the array would be {4, 9, 15}
		 * @param faceCount							The count of faces in this unstructured grid. Be aware this count does not duplicate shared faces. Most of time, you have less faceCount than the last value of faceIndicesCumulativeCountPerCell which is the count of faces per cell.
		 * @param nodeIndicesPerFace				Each item defines the index of the node of a face. There must be a count of the last value in nodeIndicesCumulativeCountPerFace.
		 * @param nodeIndicesCumulativeCountPerFace	Each item defines the cumulative count of nodes. The count of this array must be eqaul to faceCount.
		 * @param cellShape							A denormalization of the information which gives quick access to the most complex shape of polyhedron encountered in this unstructured grid.
		 */
		DLL_IMPORT_OR_EXPORT void setGeometry(unsigned char * cellFaceIsRightHanded, double * points, ULONG64 pointCount, COMMON_NS::AbstractHdfProxy* proxy,
			ULONG64 * faceIndicesPerCell, ULONG64 * faceIndicesCumulativeCountPerCell,
			ULONG64 faceCount, ULONG64 * nodeIndicesPerFace, ULONG64 * nodeIndicesCumulativeCountPerFace,
			gsoap_resqml2_0_1::resqml20__CellShape cellShape, RESQML2_NS::AbstractLocal3dCrs * localCrs = nullptr);

		/**
		* Set a geometry which is only defined by means of tetrahedra using some existing hdf5 dataset. This geometry only contains tetrahedra.
		* @param isRightHanded						The path to the hdf5 dataset in the hdf proxy where a boolean mask is used to indicate which cell faces have an outwardly directed normal following a right hand rule. Array length is the sum of the cell face count per cell, and the data follows the order of the faces per cell RESQMLlist-of-lists.
		* @param points								The path to the hdf5 dataset in the hdf proxy where all the XYZ points defining the nodes of the unstructured grid are defined. There must a double count of pointCount * 3.
		* @param pointCount							The count of points defining the nodes of this unstructured grid.
		* @param faceCount							The count of faces in this unstructured grid. Be aware this count does not duplicate shared faces. Most of time, you have less faceCount than the last value of faceIndicesCumulativeCountPerCell which is the count of faces per cell.
		* @param proxy								The hdf proxy which contains the datasets given inthis method by means of path.
		* @param faceIndicesPerCell					The path to the hdf5 dataset in the hdf proxy where each item defines the index of the face of a cell. There must be a count of faceCountPerCell * cellCount.
		* @param nodeIndicesPerFace					The path to the hdf5 dataset in the hdf proxy where each item defines the index of the node of a face. There must be a count of nodeCountPerFace * faceCount.
		*/
		DLL_IMPORT_OR_EXPORT void setTetrahedraOnlyGeometryUsingExistingDatasets(const std::string& cellFaceIsRightHanded, const std::string& points,
			ULONG64 pointCount, ULONG64 faceCount, COMMON_NS::AbstractHdfProxy* proxy,
			const std::string& faceIndicesPerCell, const std::string& nodeIndicesPerFace, RESQML2_NS::AbstractLocal3dCrs * localCrs = nullptr);

		/**
		* Set a geometry which is only defined by means of tetrahedra and creates corresponding HDF5 datasets. This geometry only contains tetrahedra.
		* @param isRightHanded						Boolean mask used to indicate which cell faces have an outwardly directed normal following a right hand rule. Array length is the sum of the cell face count per cell, and the data follows the order of the faces per cell RESQMLlist-of-lists.
		* @param points								All the XYZ points defining the nodes of the unstructured grid. There must a double count of pointCount * 3.
		* @param pointCount							The count of points defining the nodes of this unstructured grid.
		* @param faceCount							The count of faces in this unstructured grid. Be aware this count does not duplicate shared faces. Most of time, you have less faceCount than the last value of faceIndicesCumulativeCountPerCell which is the count of faces per cell.
		* @param proxy								The hdf proxy which contains the datasets given inthis method by means of path.
		* @param faceIndicesPerCell					Each item defines the index of the face of a cell. There must be a count of faceCountPerCell * cellCount.
		* @param nodeIndicesPerFace					Each item defines the index of the node of a face. There must be a count of nodeCountPerFace * faceCount.
		*/
		DLL_IMPORT_OR_EXPORT void setTetrahedraOnlyGeometry(unsigned char * cellFaceIsRightHanded, double * points,
			ULONG64 pointCount, ULONG64 faceCount, COMMON_NS::AbstractHdfProxy* proxy,
			ULONG64 * faceIndicesPerCell, ULONG64 * nodeIndicesPerFace, RESQML2_NS::AbstractLocal3dCrs * localCrs = nullptr);

		/**
		* Set a geometry which is only defined by means of tetrahedra using some existing hdf5 dataset. This geometry only contains hexahedra.
		* @param isRightHanded						The path to the hdf5 dataset in the hdf proxy where a boolean mask is used to indicate which cell faces have an outwardly directed normal following a right hand rule. Array length is the sum of the cell face count per cell, and the data follows the order of the faces per cell RESQMLlist-of-lists.
		* @param points								The path to the hdf5 dataset in the hdf proxy where all the XYZ points defining the nodes of the unstructured grid are defined. There must a double count of pointCount * 3.
		* @param pointCount							The count of points defining the nodes of this unstructured grid.
		* @param faceCount							The count of faces in this unstructured grid. Be aware this count does not duplicate shared faces. Most of time, you have less faceCount than the last value of faceIndicesCumulativeCountPerCell which is the count of faces per cell.
		* @param proxy								The hdf proxy which contains the datasets given inthis method by means of path.
		* @param faceIndicesPerCell					The path to the hdf5 dataset in the hdf proxy where each item defines the index of the face of a cell. There must be a count of faceCountPerCell * cellCount.
		* @param nodeIndicesPerFace					The path to the hdf5 dataset in the hdf proxy where each item defines the index of the node of a face. There must be a count of nodeCountPerFace * faceCount.
		*/
		DLL_IMPORT_OR_EXPORT void setHexahedraOnlyGeometryUsingExistingDatasets(const std::string& cellFaceIsRightHanded, const std::string& points,
			ULONG64 pointCount, ULONG64 faceCount, COMMON_NS::AbstractHdfProxy* proxy,
			const std::string& faceIndicesPerCell, const std::string& nodeIndicesPerFace, RESQML2_NS::AbstractLocal3dCrs * localCrs = nullptr);

		/**
		* Set a geometry which is only defined by means of tetrahedra and creates corresponding HDF5 datasets. This geometry only contains hexahedra.
		* @param isRightHanded						Boolean mask used to indicate which cell faces have an outwardly directed normal following a right hand rule. Array length is the sum of the cell face count per cell, and the data follows the order of the faces per cell RESQMLlist-of-lists.
		* @param points								All the XYZ points defining the nodes of the unstructured grid. There must a double count of pointCount * 3.
		* @param pointCount							The count of points defining the nodes of this unstructured grid.
		* @param faceCount							The count of faces in this unstructured grid. Be aware this count does not duplicate shared faces. Most of time, you have less faceCount than the last value of faceIndicesCumulativeCountPerCell which is the count of faces per cell.
		* @param proxy								The hdf proxy which contains the datasets given inthis method by means of path.
		* @param faceIndicesPerCell					Each item defines the index of the face of a cell. There must be a count of faceCountPerCell * cellCount.
		* @param nodeIndicesPerFace					Each item defines the index of the node of a face. There must be a count of nodeCountPerFace * faceCount.
		*/
		DLL_IMPORT_OR_EXPORT void setHexahedraOnlyGeometry(unsigned char * cellFaceIsRightHanded, double * points,
			ULONG64 pointCount, ULONG64 faceCount, COMMON_NS::AbstractHdfProxy* proxy,
			ULONG64 * faceIndicesPerCell, ULONG64 * nodeIndicesPerFace, RESQML2_NS::AbstractLocal3dCrs * localCrs = nullptr);

		DLL_IMPORT_OR_EXPORT unsigned int getPatchCount() const {return 1;}

		/**
		* The standard XML tag without XML namespace for serializing this data object.
		*/
		DLL_IMPORT_OR_EXPORT static const char* XML_TAG;

		/**
		* Get the standard XML tag without XML namespace for serializing this data object.
		*/
		DLL_IMPORT_OR_EXPORT virtual std::string getXmlTag() const { return XML_TAG; }

	protected:
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
		void virtual setConstantCellShapeGeometryUsingExistingDatasets(const std::string& cellFaceIsRightHanded, const std::string& points,
			ULONG64 pointCount, ULONG64 faceCount, RESQML2_NS::AbstractLocal3dCrs * localCrs, COMMON_NS::AbstractHdfProxy* proxy,
			const std::string& faceIndicesPerCell, ULONG64 faceCountPerCell,
			const std::string& nodeIndicesPerFace, ULONG64 nodeCountPerFace) = 0;

	private:
		/**
		* Set a geometry and creates corresponding HDF5 datasets. This geometry only contains polyedra with constant face count per cell and constant node count per face.
		* @param isRightHanded						Boolean mask used to indicate which cell faces have an outwardly directed normal following a right hand rule. Array length is the sum of the cell face count per cell, and the data follows the order of the faces per cell RESQMLlist-of-lists.
		* @param points								All the XYZ points defining the nodes of the unstructured grid. There must a double count of pointCount * 3.
		* @param pointCount							The count of points defining the nodes of this unstructured grid.
		* @param faceCount							The count of faces in this unstructured grid. Be aware this count does not duplicate shared faces. Most of time, you have less faceCount than the last value of faceIndicesCumulativeCountPerCell which is the count of faces per cell.
		* @param proxy								The hdf proxy which contains the datasets given inthis method by means of path.
		* @param faceIndicesPerCell					Each item defines the index of the face of a cell. There must be a count of faceCountPerCell * cellCount.
		* @param faceCountPerCell					The constant face count per cell.
		* @param nodeIndicesPerFace					Each item defines the index of the node of a face. There must be a count of nodeCountPerFace * faceCount.
		* @param nodeCountPerFace					The constant node count per face.
		*/
		void setConstantCellShapeGeometry(unsigned char * cellFaceIsRightHanded, double * points,
			ULONG64 pointCount, ULONG64 faceCount, RESQML2_NS::AbstractLocal3dCrs * localCrs, COMMON_NS::AbstractHdfProxy* proxy,
			ULONG64 * faceIndicesPerCell, ULONG64 faceCountPerCell,
			ULONG64 * nodeIndicesPerFace, ULONG64 nodeCountPerFace);

		unsigned int constantNodeCountPerFace;
		unsigned int constantFaceCountPerCell;
		ULONG64 * cumulativeNodeCountPerFace;
		ULONG64 * cumulativeFaceCountPerCell;
		ULONG64 * nodeIndicesOfFaces;
		ULONG64 * faceIndicesOfCells;
	};
}
