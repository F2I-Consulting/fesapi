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
	/** @brief	An unstructured grid representation. This class cannot be inherited. */
	class UnstructuredGridRepresentation final : public RESQML2_NS::UnstructuredGridRepresentation
	{
	public:

		/**
		* Only to be used in partial transfer context
		*/
		DLL_IMPORT_OR_EXPORT UnstructuredGridRepresentation(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject):
			RESQML2_NS::UnstructuredGridRepresentation(partialObject) {}

		/**
		 * @brief	Constructor
		 *
		 * @param [in]	repo	 	The soap context where the underlying gsoap proxy is going to be
		 * 								created.
		 * @param 	  	guid	 	Unique identifier.
		 * @param 	  	title	 	The title.
		 * @param 	  	cellCount	Number of cells.
		 */
		UnstructuredGridRepresentation(COMMON_NS::DataObjectRepository* repo,
			const std::string & guid, const std::string & title,
			uint64_t cellCount);

		/**
		 * @brief	Constructor
		 *
		 * @param [in]	interp   	If non-nullptr, the interp.
		 * @param 	  	guid	 	Unique identifier.
		 * @param 	  	title	 	The title.
		 * @param 	  	cellCount	Number of cells.
		 */
		UnstructuredGridRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp,
			const std::string & guid, const std::string & title,
			uint64_t cellCount);

		/**
		 * @brief	Creates an instance of this class by wrapping a gsoap instance.
		 *
		 * @param [in]	fromGsoap	If non-nullptr, from gsoap.
		 */
		UnstructuredGridRepresentation(gsoap_eml2_3::_resqml22__UnstructuredGridRepresentation* fromGsoap):
			RESQML2_NS::UnstructuredGridRepresentation(fromGsoap) {}

		/**
		* Destructor does nothing since the memory is managed by the gsoap context.
		*/
		~UnstructuredGridRepresentation() = default;

		DLL_IMPORT_OR_EXPORT bool hasGeometry() const final;

		COMMON_NS::DataObjectReference getHdfProxyDor() const final;

		DLL_IMPORT_OR_EXPORT void getXyzPointsOfPatch(unsigned int patchIndex, double * xyzPoints) const final;

		DLL_IMPORT_OR_EXPORT void getFaceIndicesOfCells(uint64_t * faceIndices) const final;

		DLL_IMPORT_OR_EXPORT void getCumulativeFaceCountPerCell(uint64_t * cumulativeFaceCountPerCell_) const final;

		DLL_IMPORT_OR_EXPORT bool isFaceCountOfCellsConstant() const final;

		DLL_IMPORT_OR_EXPORT unsigned int getConstantFaceCountOfCells() const final;

		DLL_IMPORT_OR_EXPORT void getNodeIndicesOfFaces(uint64_t * nodeIndices) const final;

		DLL_IMPORT_OR_EXPORT void getCumulativeNodeCountPerFace(uint64_t * nodeCountPerFace) const final;

		DLL_IMPORT_OR_EXPORT bool isNodeCountOfFacesConstant() const final;

		DLL_IMPORT_OR_EXPORT unsigned int getConstantNodeCountOfFaces() const final;

		DLL_IMPORT_OR_EXPORT uint64_t getCellCount() const final;

		DLL_IMPORT_OR_EXPORT uint64_t getFaceCount() const final;

		DLL_IMPORT_OR_EXPORT uint64_t getNodeCount() const final;

    	DLL_IMPORT_OR_EXPORT void getCellFaceIsRightHanded(unsigned char* cellFaceIsRightHanded) const final;

		DLL_IMPORT_OR_EXPORT void setGeometryUsingExistingDatasets(const std::string& cellFaceIsRightHanded, const std::string& points, uint64_t pointCount, EML2_NS::AbstractHdfProxy* proxy,
			const std::string& faceIndicesPerCell, const std::string& faceIndicesCumulativeCountPerCell,
			uint64_t faceCount, const std::string& nodeIndicesPerFace, const std::string& nodeIndicesCumulativeCountPerFace,
			gsoap_resqml2_0_1::resqml20__CellShape cellShape, EML2_NS::AbstractLocal3dCrs * localCrs = nullptr) final;

		/**
		* The standard XML namespace for serializing this data object.
		*/
		DLL_IMPORT_OR_EXPORT static const char* XML_NS;

		/**
		* Get the standard XML namespace for serializing this data object.
		*/
		DLL_IMPORT_OR_EXPORT std::string getXmlNamespace() const final { return XML_NS; }

	private:

		/**
		* @param soapContext	The soap context where the underlying gsoap proxy is going to be created.
		*/
		void init(COMMON_NS::DataObjectRepository* repo,
			const std::string & guid, const std::string & title,
			uint64_t cellCount);

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
			uint64_t pointCount, uint64_t faceCount, EML2_NS::AbstractLocal3dCrs * localCrs, EML2_NS::AbstractHdfProxy* proxy,
			const std::string& faceIndicesPerCell, uint64_t faceCountPerCell,
			const std::string& nodeIndicesPerFace, uint64_t nodeCountPerFace) final;
	};
}
