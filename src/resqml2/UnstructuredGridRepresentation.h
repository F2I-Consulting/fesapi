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
	/**
	 * @brief	Unstructured grid representation characterized by a cell count, and potentially
	 * 			nothing else. Both the oldest and newest simulation formats are based on this format.
	 */
	class UnstructuredGridRepresentation : public AbstractGridRepresentation
	{
	public:

		/**
		 * Only to be used in partial transfer context.
		 *
		 * @param [in]	partialObject	If non-nullptr, the partial object.
		 */
		DLL_IMPORT_OR_EXPORT UnstructuredGridRepresentation(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject):
			AbstractGridRepresentation(partialObject, false), constantNodeCountPerFace(0), constantFaceCountPerCell(0),
			cumulativeNodeCountPerFace(nullptr), cumulativeFaceCountPerCell(nullptr),
			nodeIndicesOfFaces(nullptr), faceIndicesOfCells(nullptr) {}

		/** Default constructor */
		UnstructuredGridRepresentation() :
			AbstractGridRepresentation(false), constantNodeCountPerFace(0), constantFaceCountPerCell(0),
			cumulativeNodeCountPerFace(nullptr), cumulativeFaceCountPerCell(nullptr),
			nodeIndicesOfFaces(nullptr), faceIndicesOfCells(nullptr) {}

		/**
		 * Creates an instance of this class by wrapping a gSOAP instance.
		 *
		 * @param [in]	fromGsoap	If non-null, the gSOAP instance.
		 */
		UnstructuredGridRepresentation(gsoap_resqml2_0_1::_resqml20__UnstructuredGridRepresentation* fromGsoap) :
			RESQML2_NS::AbstractGridRepresentation(fromGsoap, false), constantNodeCountPerFace(0), constantFaceCountPerCell(0),
			cumulativeNodeCountPerFace(nullptr), cumulativeFaceCountPerCell(nullptr),
			nodeIndicesOfFaces(nullptr), faceIndicesOfCells(nullptr) {}

		/**
		 * Creates an instance of this class by wrapping a gSOAP instance.
		 *
		 * @param [in]	fromGsoap	If non-null, the gSOAP instance.
		 */
		UnstructuredGridRepresentation(gsoap_eml2_3::_resqml22__UnstructuredGridRepresentation* fromGsoap) :
			RESQML2_NS::AbstractGridRepresentation(fromGsoap, false), constantNodeCountPerFace(0), constantFaceCountPerCell(0),
			cumulativeNodeCountPerFace(nullptr), cumulativeFaceCountPerCell(nullptr),
			nodeIndicesOfFaces(nullptr), faceIndicesOfCells(nullptr) {}

		/**
		* Destructor does nothing since the memory is managed by the gSOAP context.
		*/
		virtual ~UnstructuredGridRepresentation() = default;

		/**
		 * Indicates whether this grid has a geometry or not.
		 *
		 * @returns	True if this grid has a geometry, false if not.
		 */
		DLL_IMPORT_OR_EXPORT virtual bool hasGeometry() const = 0;

		DLL_IMPORT_OR_EXPORT uint64_t getXyzPointCountOfPatch(unsigned int patchIndex) const final;

		/**
		 * Gets all the face indices of all the cells.
		 *
		 * @exception	std::logic_error	 	If this grid is partial.
		 * @exception	std::logic_error	 	If this grid has no geometry (please check the existence
		 * 										of a geometry thanks to hasGeometry() before calling this
		 * 										method).
		 * @exception	std::logic_error	 	If the data structure used to store the face indices of
		 * 										the cells is not already supported by fesapi.
		 * @exception	std::invalid_argument	If a required HDF proxy is missing.
		 *
		 * @param [out]	faceIndices	Preallocated array to receive all the face indices of all the cells.
		 * 							It size must be the last value outputted by
		 * 							getCumulativeFaceCountPerCell(). It is ordered first by faces and
		 * 							then by cells.
		 */
		DLL_IMPORT_OR_EXPORT virtual void getFaceIndicesOfCells(uint64_t * faceIndices) const = 0;

		/**
		 * Gets the cumulative face count per cell. A single face count should be at least 4.
		 *
		 * @exception	std::logic_error	 	If this grid is partial.
		 * @exception	std::logic_error	 	If this grid has no geometry (please check the existence
		 * 										of a geometry thanks to hasGeometry() before calling this
		 * 										method).
		 * @exception	std::invalid_argument	If a required HDF proxy is missing.
		 * @exception	std::range_error	 	If the cumulative face count per cell is stored in an
		 * 										integer constant array while there is more than one cell
		 * 										in this grid.
		 *
		 * @param [out]	cumulativeFaceCountPerCell_	Preallocated array of size getCellCount() to receive
		 * 											the cumulative face count per cell. First value is
		 * 											the count of faces in the first cell. Second value is
		 * 											the count of faces in the first and in the second
		 * 											cell. Third value is the count of faces in the first
		 * 											and in the second and in the third cell. And so on.
		 */
		DLL_IMPORT_OR_EXPORT virtual void getCumulativeFaceCountPerCell(uint64_t * cumulativeFaceCountPerCell_) const = 0;

		/**
		 * Gets the cumulative face count per cell. This method requires you to have already loaded the
		 * geometry.
		 *
		 * @exception	std::logic_error	If this grid has a constant count of faces per cell.
		 * @exception	std::logic_error 	If the geometry is not loaded.
		 *
		 * @returns	The cumulative face count per cell. First value is
		 * 			the count of faces in the first cell. Second value is
		 * 			the count of faces in the first and in the second
		 * 			cell. Third value is the count of faces in the first
		 * 			and in the second and in the third cell. And so on.
		 *			DO NOT FREE the returned value. It is owned and managed by this class.
		 */
		DLL_IMPORT_OR_EXPORT uint64_t const * getCumulativeFaceCountPerCell() const;

		/**
		 * Gets the face count per cell. This method is less efficient than
		 * getCumulativeFaceCountPerCell().
		 *
		 * @exception	std::logic_error	 	If this grid is partial.
		 * @exception	std::logic_error	 	If this grid has no geometry (please check the existence
		 * 										of a geometry thanks to hasGeometry() before calling this
		 * 										method).
		 * @exception	std::invalid_argument	If a required HDF proxy is missing.
		 * @exception	std::range_error	 	If the cumulative face count per cell is stored in an
		 * 										integer constant array while there is more than one cell
		 * 										in this grid.
		 *
		 * @param [out]	faceCountPerCell	Preallocated array of size getCellCount() to receive the face
		 * 									count per cell. First value is the count of faces in the first
		 * 									cell. Second value is the count of faces in the second cell. And
		 * 									so on.
		 */
		DLL_IMPORT_OR_EXPORT void getFaceCountPerCell(uint64_t * faceCountPerCell) const;

		/**
		 * Checks whether the face count per cell is constant in this unstructured grid.
		 *
		 * @exception	std::logic_error	If this grid is partial.
		 * @exception	std::logic_error	If this grid has no geometry (please check the existence of a
		 * 									geometry thanks to hasGeometry() before calling this method).
		 * @exception	std::range_error	If the cumulative face count per cell is stored in an integer
		 * 									constant array while there is more than one cell in this grid.
		 *
		 * @returns	True if the face count per cell is constant, false if not.
		 */
		DLL_IMPORT_OR_EXPORT virtual bool isFaceCountOfCellsConstant() const = 0;

		/**
		 * Gets the constant face count per cell in this unstructured grid.
		 *
		 * @exception	std::logic_error	If the face count per cell is not constant (please check the
		 * 									constantness of the face count per cell with
		 * 									isFaceCountOfCellsConstant() before calling this method).
		 * @exception	std::logic_error	If this grid is partial.
		 * @exception	std::logic_error	If this grid has no geometry (please check the existence of a
		 * 									geometry thanks to hasGeometry() before calling this method).
		 * @exception	std::range_error	If the cumulative face count per cell is stored in an integer
		 * 									constant array while there is more than one cell in this grid.
		 *
		 * @returns	The constant face count per cell.
		 */
		DLL_IMPORT_OR_EXPORT virtual unsigned int getConstantFaceCountOfCells() const = 0;

		/**
		 * Gets all the node indices of all the faces.
		 *
		 * @exception	std::logic_error	 	If this grid is partial.
		 * @exception	std::logic_error	 	If this grid has no geometry (please check the existence
		 * 										of a geometry thanks to hasGeometry() before calling this
		 * 										method).
		 * @exception	std::logic_error	 	If the data structure used to store the node indices of
		 * 										the faces is not already supported by fesapi.
		 * @exception	std::invalid_argument	If a required HDF proxy is missing.
		 *
		 * @param [out]	nodeIndices	Preallocated array to receive all the node indices of all the faces.
		 * 							It size must be the last value outputted by
		 * 							getCumulativeNodeCountPerFace(). It is ordered first by nodes, then
		 * 							by faces and then by cells.
		 */
		DLL_IMPORT_OR_EXPORT virtual void getNodeIndicesOfFaces(uint64_t * nodeIndices) const = 0;

		/**
		 * Gets the cumulative node count per face. A single node count should be at least 3.
		 *
		 * @exception	std::logic_error	 	If this grid is partial.
		 * @exception	std::logic_error	 	If this grid has no geometry (please check the existence
		 * 										of a geometry thanks to hasGeometry() before calling this
		 * 										method).
		 * @exception	std::invalid_argument	If a required HDF proxy is missing.
		 * @exception	std::range_error	 	If the cumulative node count per face is stored in a
		 * 										integer constant array.
		 *
		 * @param [out]	nodeCountPerFace	Preallocated array to receive the cumulative node count per
		 * 									face. Its size must be getFaceCount(). First value is the count
		 * 									of nodes in the first face. Second value is the count of nodes in
		 * 									the first and in the second face. Third value is the count of
		 * 									nodes in the first and in the second and in the third face. And
		 * 									so on.
		 */
		DLL_IMPORT_OR_EXPORT virtual void getCumulativeNodeCountPerFace(uint64_t * nodeCountPerFace) const = 0;

		/**
		 * Gets the node count per face. This method is less efficient than
		 * getCumulativeNodeCountPerFace().
		 *
		 * @exception	std::logic_error	 	If this grid is partial.
		 * @exception	std::logic_error	 	If this grid has no geometry (please check the existence
		 * 										of a geometry thanks to hasGeometry() before calling this
		 * 										method).
		 * @exception	std::invalid_argument	If a required HDF proxy is missing.
		 * @exception	std::range_error	 	If the cumulative node count per face is stored in a
		 * 										integer constant array.
		 *
		 * @param [out]	nodeCountPerFace	Preallocated array of size getFaceCount() to receive the node
		 * 									count per face. First value is the count of nodes in the first
		 * 									face. Second value is the count of nodes in the second face. And
		 * 									so on.
		 */
		DLL_IMPORT_OR_EXPORT void getNodeCountPerFace(uint64_t * nodeCountPerFace) const;

		/**
		 * Checks whether the node count per face is constant in this unstructured grid.
		 *
		 * @exception	std::logic_error	If this grid is partial.
		 * @exception	std::logic_error	If this grid has no geometry (please check the existence of a
		 * 									geometry thanks to hasGeometry() before calling this method).
		 *
		 * @returns	True if the node count per face is constant, false if not.
		 */
		DLL_IMPORT_OR_EXPORT virtual bool isNodeCountOfFacesConstant() const = 0;

		/**
		 * Gets the constant node count per face in this unstructured grid.
		 *
		 * @exception	std::logic_error	If the node count per face is not constant (please check the
		 * 									constantness of the node count per face with
		 * 									isNodeCountOfFacesConstant() before calling this method).
		 * @exception	std::logic_error	If this grid is partial.
		 * @exception	std::logic_error	If this grid has no geometry (please check the existence of a
		 * 									geometry thanks to hasGeometry() before calling this method).
		 *
		 * @returns	The constant node count per face.
		 */
		DLL_IMPORT_OR_EXPORT virtual unsigned int getConstantNodeCountOfFaces() const = 0;

		/**
		 * Loads the geoemtry into memory in order to ease access. Be aware that you must unload by
		 * yourself this memory thanks to unloadGeometry().
		 *
		 * @exception	std::logic_error	 	If this grid is partial.
		 * @exception	std::logic_error	 	If this grid has no geometry (please check the existence
		 * 										of a geometry thanks to hasGeometry() before calling this
		 * 										method).
		 * @exception	std::logic_error	 	If the data structure used to store the face indices of
		 * 										the cells is not already supported by fesapi.
		 * @exception	std::logic_error	 	If the data structure used to store the node indices of
		 * 										the faces is not already supported by fesapi.
		 * @exception	std::range_error	 	If the cumulative face count per cell is stored in an
		 * 										integer constant array while there is more than one cell
		 * 										in this grid.
		 * @exception	std::range_error	 	If the cumulative node count per face is stored in a
		 * 										integer constant array.
		 * @exception	std::invalid_argument	If a required HDF proxy is missing.
		 */
		DLL_IMPORT_OR_EXPORT void loadGeometry();

		/** Unloads the geometry from memory. */
		DLL_IMPORT_OR_EXPORT void unloadGeometry();

		/**
		 * Gets the face count of a particular cell. This method requires you to have already loaded the
		 * geometry.
		 *
		 * @exception	std::logic_error 	If this grid is partial.
		 * @exception	std::logic_error 	If the geometry is not loaded.
		 * @exception	std::out_of_range	If <tt>cellIndex &gt;=</tt> getCellCount().
		 *
		 * @param 	cellIndex	Zero-based index of the cell for which we want to count the faces.
		 *
		 * @returns	The count of faces in the cell at position @p cellIndex.
		 */
		DLL_IMPORT_OR_EXPORT uint64_t getFaceCountOfCell(uint64_t cellIndex) const;

		/**
		 * Gets the node count of a particular face of a particular cell. This method requires you to
		 * have already loaded the geometry.
		 *
		 * @exception	std::logic_error 	If this grid is partial.
		 * @exception	std::logic_error 	If the geometry is not loaded.
		 * @exception	std::out_of_range	If <tt>cellIndex &gt;=</tt> getCellCount().
		 * @exception	std::out_of_range	If <tt>localFaceIndex &gt;=</tt>
		 * 									getFaceCountOfCell(cellIndex).
		 *
		 * @param 	cellIndex	  	Zero-based index of the cell for which we want to count the nodes of
		 * 							one face.
		 * @param 	localFaceIndex	Zero-based local index of the face for which we want to count the
		 * 							nodes.
		 *
		 * @returns	The count of nodes in the face @p localFaceIndex of the cell @p cellIndex.
		 */
		DLL_IMPORT_OR_EXPORT uint64_t getNodeCountOfFaceOfCell(uint64_t cellIndex, unsigned int localFaceIndex) const;

		/**
		 * Gets all the node indices of a particular face of a particular cell. This method requires you
		 * to have already loaded the geometry.
		 *
		 * @exception	std::logic_error 	If this grid is partial.
		 * @exception	std::logic_error 	If the geometry is not loaded.
		 * @exception	std::out_of_range	If <tt>cellIndex &gt;=</tt> getCellCount().
		 * @exception	std::out_of_range	If <tt>localFaceIndex &gt;=</tt>
		 * 									getFaceCountOfCell(cellIndex).
		 *
		 * @param 	cellIndex	  	Zero-based index of the cell for which we want to get the node
		 * 							indices of one face.
		 * @param 	localFaceIndex	Zero-based local index of the face for which we want to get the node
		 * 							indices.
		 *
		 * @returns	A pointer to an array containing the node indices of the face @p localFaceIndex of
		 * 			the cell @p cellIndex. This array is allocated by loadGeometry() and is freed by
		 * 			unloadGeometry().
		 */
		DLL_IMPORT_OR_EXPORT uint64_t const * getNodeIndicesOfFaceOfCell(uint64_t cellIndex, unsigned int localFaceIndex) const;

		DLL_IMPORT_OR_EXPORT virtual uint64_t getCellCount() const override = 0;

		/**
		 * Gets the face count
		 *
		 * @exception	std::logic_error	If this grid is partial.
		 *
		 * @returns	The face count.
		 */
		DLL_IMPORT_OR_EXPORT virtual uint64_t getFaceCount() const = 0;

		/**
		 * Get the node count
		 *
		 * @exception	std::logic_error	If this grid is partial.
		 *
		 * @returns	The node count.
		 */
		DLL_IMPORT_OR_EXPORT virtual uint64_t getNodeCount() const = 0;

		/**
		 * Gets the orientation of each cell face. That is to say tells for each cell face, if its face
		 * normal defined using a right hand rule is outwardly directed.
		 *
		 * @exception	std::logic_error	If this grid is partial.
		 * @exception	std::logic_error	If the geometry is not loaded.
		 * @exception	std::logic_error	If the data structure used to store the orientation of the
		 * 									cell is not already supported by fesapi.
		 *
		 * @param [out]	cellFaceIsRightHanded	Preallocated array for receiving the orientation of each
		 * 										cell face. The size is the last value returned by
		 * 										getCumulativeFaceCountPerCell().
		 */
		DLL_IMPORT_OR_EXPORT virtual void getCellFaceIsRightHanded(uint8_t* cellFaceIsRightHanded) const = 0;

		/**
		 * Sets the geometry using some existing HDF5 dataset.
		 *
		 * @exception	std::logic_error	 	If this grid is partial.
		 * @exception	std::invalid_argument	If @p cellFaceIsRightHanded, @p points, @p
		 * 										faceIndicesPerCell, @p faceIndicesCumulativeCountPerCell,
		 * 										@p nodeIndicesPerFace or @p
		 * 										nodeIndicesCumulativeCountPerFace is empty.
		 * @exception	std::invalid_argument	If <tt>proxy == nullptr</tt> and no default HDF proxy is
		 * 										defined in the repository.
		 * @exception	std::invalid_argument	If <tt>localCrs == nullptr</tt> and no default local CRS
		 * 										is defined in the repository.
		 *
		 * @param 		  	cellFaceIsRightHanded			 	The path to the HDF5 dataset in the HDF
		 * 														proxy where a boolean mask is used to
		 * 														indicate which cell faces have an
		 * 														outwardly directed normal following a
		 * 														right hand rule. Array length is the sum
		 * 														of the cell face count per cell, and the
		 * 														data follows the order of the faces per
		 * 														cell RESQMLlist-of-lists.
		 * @param 		  	points							 	The path to the HDF5 dataset in the HDF
		 * 														proxy where all the xyz points defining
		 * 														the nodes of the unstructured grid are
		 * 														defined. There must a double count of
		 * 														<tt>pointCount * 3</tt>.
		 * @param 		  	pointCount						 	The count of points defining the nodes of
		 * 														this unstructured grid.
		 * @param [in,out]	proxy							 	The HDF proxy which contains the datasets
		 * 														given in this method by means of paths.
		 * 														If @c nullptr, then the repository
		 * 														default HDF proxy will be used.
		 * @param 		  	faceIndicesPerCell				 	The path to the HDF5 dataset in the HDF
		 * 														proxy where each item defines the index
		 * 														of the face of a cell. There must be a
		 * 														count of the last value in
		 * 														@p faceIndicesCumulativeCountPerCell.
		 * @param 		  	faceIndicesCumulativeCountPerCell	The path to the HDF5 dataset in the HDF
		 * 														proxy where each item defines the
		 * 														cumulative count of faces. The count of
		 * 														this array must be equal to the count of
		 * 														cells in this unstructured grid. For
		 * 														example if the first cell a 4 faces, the
		 * 														second cell 5 faces and the third cell 6
		 * 														faces then the array would be {4, 9, 15}.
		 * @param 		  	faceCount						 	The count of faces in this unstructured
		 * 														grid. Be aware this count does not
		 * 														duplicate shared faces. Most of time, you
		 * 														have less faceCount than the last value
		 * 														of @p faceIndicesCumulativeCountPerCell
		 * 														which is the count of faces per cell.
		 * @param 		  	nodeIndicesPerFace				 	The path to the HDF5 dataset in the HDF
		 * 														proxy where each item defines the index
		 * 														of the node of a face. There must be a
		 * 														count of the last value in
		 * 														@p nodeIndicesCumulativeCountPerFace.
		 * @param 		  	nodeIndicesCumulativeCountPerFace	The path to the HDF5 dataset in the HDF
		 * 														proxy where each item defines the
		 * 														cumulative count of nodes. The count of
		 * 														this array must be equal to @p faceCount.
		 * @param 		  	cellShape						 	A denormalization of the information
		 * 														which gives quick access to the most
		 * 														complex shape of polyhedron encountered
		 * 														in this unstructured grid.
		 * @param [in]	  	localCrs						 	(Optional) The local CRS. If @c nullptr
		 * 														(default), then the repository default
		 * 														local CRS will be used.
		 */
		DLL_IMPORT_OR_EXPORT virtual void setGeometryUsingExistingDatasets(const std::string& cellFaceIsRightHanded, const std::string& points, uint64_t pointCount, EML2_NS::AbstractHdfProxy* proxy,
			const std::string& faceIndicesPerCell, const std::string& faceIndicesCumulativeCountPerCell,
			uint64_t faceCount, const std::string& nodeIndicesPerFace, const std::string& nodeIndicesCumulativeCountPerFace,
			gsoap_resqml2_0_1::resqml20__CellShape cellShape, EML2_NS::AbstractLocal3dCrs * localCrs = nullptr) = 0;

		/**
		 * Sets the geometry and creates corresponding HDF5 datasets.
		 *
		 * @exception	std::logic_error	 	If this grid is partial.
		 * @exception	std::invalid_argument	If @p cellFaceIsRightHanded, @p points, @p
		 * 										faceIndicesPerCell, @p faceIndicesCumulativeCountPerCell,
		 * 										@p nodeIndicesPerFace or @p
		 * 										nodeIndicesCumulativeCountPerFace is @c nullptr.
		 * @exception	std::invalid_argument	If <tt>proxy == nullptr</tt> and no default HDF proxy is
		 * 										defined in the repository.
		 * @exception	std::invalid_argument	If <tt>localCrs == nullptr</tt> and no default local CRS
		 * 										is defined in the repository.
		 *
		 * @param [in]	  	cellFaceIsRightHanded			 	Boolean mask used to indicate which cell
		 * 														faces have an outwardly directed normal
		 * 														following a right hand rule. Array length
		 * 														is the sum of the cell face count per
		 * 														cell, and the data follows the order of
		 * 														the faces per cell RESQMLlist-of-lists.
		 * @param [in]	  	points							 	All the XYZ points defining the nodes of
		 * 														the unstructured grid. There must a
		 * 														double count of <tt>pointCount * 3</tt>.
		 * @param 		  	pointCount						 	The count of points defining the nodes of
		 * 														this unstructured grid.
		 * @param [in,out]	proxy							 	The HDF proxy which will store all the
		 * 														numerical values of this unstructured
		 * 														grid. If @c nullptr, then the repository
		 * 														default HDF proxy will be used.
		 * @param [in]	  	faceIndicesPerCell				 	Each item defines the index of the face
		 * 														of a cell. There must be a count of the
		 * 														last value in
		 * 														@p faceIndicesCumulativeCountPerCell.
		 * @param [in]	  	faceIndicesCumulativeCountPerCell	Each item defines the cumulative count of
		 * 														faces. The count of this array must be
		 * 														equal to the count of cells in this
		 * 														unstructured grid. For example if the
		 * 														first cell a 4 faces, the second cell 5
		 * 														faces and the third cell 6 faces then the
		 * 														array would be {4, 9, 15}.
		 * @param 		  	faceCount						 	The count of faces in this unstructured
		 * 														grid. Be aware this count does not
		 * 														duplicate shared faces. Most of time, you
		 * 														have less faceCount than the last value
		 * 														of @p faceIndicesCumulativeCountPerCell
		 * 														which is the count of faces per cell.
		 * @param [in]	  	nodeIndicesPerFace				 	Each item defines the index of the node
		 * 														of a face. There must be a count of the
		 * 														last value in
		 * 														@p nodeIndicesCumulativeCountPerFace.
		 * @param [in]	  	nodeIndicesCumulativeCountPerFace	Each item defines the cumulative count of
		 * 														nodes. The count of this array must be
		 * 														equal to @p faceCount.
		 * @param 		  	cellShape						 	A denormalization of the information
		 * 														which gives quick access to the most
		 * 														complex shape of polyhedron encountered
		 * 														in this unstructured grid.
		 * @param [in]	  	localCrs						 	(Optional) The local CRS. If @c nullptr
		 * 														(default), then the repository default
		 * 														local CRS will be used.
		 */
		DLL_IMPORT_OR_EXPORT void setGeometry(uint8_t * cellFaceIsRightHanded, double * points, uint64_t pointCount, EML2_NS::AbstractHdfProxy* proxy,
			uint64_t * faceIndicesPerCell, uint64_t * faceIndicesCumulativeCountPerCell,
			uint64_t faceCount, uint64_t * nodeIndicesPerFace, uint64_t * nodeIndicesCumulativeCountPerFace,
			gsoap_resqml2_0_1::resqml20__CellShape cellShape, EML2_NS::AbstractLocal3dCrs * localCrs = nullptr);

		/**
		 * @brief Sets a geometry which is only defined by means of tetrahedra using some existing HDF5 dataset.
		 *
		 * @exception	std::logic_error	 	If this grid is partial.
		 * @exception	std::invalid_argument	If @p cellFaceIsRightHanded, @p points, @p
		 * 										faceIndicesPerCell or @p nodeIndicesPerFace is empty.
		 * @exception	std::invalid_argument	If <tt>proxy == nullptr</tt> and no default HDF proxy is
		 * 										defined in the repository.
		 * @exception	std::invalid_argument	If <tt>localCrs == nullptr</tt> and no default local CRS
		 * 										is defined in the repository.
		 *
		 * @param 		  	cellFaceIsRightHanded	The path to the HDF5 dataset in the HDF proxy where a
		 * 											boolean mask is used to indicate which cell faces
		 * 											have an outwardly directed normal following a right
		 * 											hand rule. Array length is the sum of the cell face
		 * 											count per cell, and the data follows the order of the
		 * 											faces per cell RESQMLlist-of-lists.
		 * @param 		  	points				 	The path to the HDF5 dataset in the HDF proxy where
		 * 											all the xyz points defining the nodes of the
		 * 											unstructured grid are defined. There must a double
		 * 											count of <tt>pointCount * 3</tt>.
		 * @param 		  	pointCount			 	The count of points defining the nodes of this
		 * 											unstructured grid.
		 * @param 		  	faceCount			 	The count of faces in this unstructured grid. Be
		 * 											aware this count does not duplicate cell-shared faces.
		 * @param [in,out]	proxy				 	The HDF proxy which contains the datasets given in
		 * 											this method by means of paths. If @c nullptr, then
		 * 											the repository default HDF proxy will be used.
		 * @param 		  	faceIndicesPerCell   	The path to the HDF5 dataset in the HDF proxy where
		 * 											each item defines the index of the face of a cell.
		 * 											There must be a count of <tt>faceCountPerCell *
		 * 											cellCount</tt>.
		 * @param 		  	nodeIndicesPerFace   	The path to the HDF5 dataset in the HDF proxy where
		 * 											each item defines the index of the node of a face.
		 * 											There must be a count of <tt>nodeCountPerFace *
		 * 											faceCount</tt>.
		 * @param [in]	  	localCrs			 	(Optional) The local CRS. If @c nullptr (default),
		 * 											then the repository default local CRS will be used.
		 */
		DLL_IMPORT_OR_EXPORT void setTetrahedraOnlyGeometryUsingExistingDatasets(const std::string& cellFaceIsRightHanded, const std::string& points,
			uint64_t pointCount, uint64_t faceCount, EML2_NS::AbstractHdfProxy* proxy,
			const std::string& faceIndicesPerCell, const std::string& nodeIndicesPerFace, EML2_NS::AbstractLocal3dCrs * localCrs = nullptr);

		/**
		 * @brief Sets a geometry which is only defined by means of tetrahedra and creates corresponding HDF5
		 * datasets.
		 *
		 * @exception	std::logic_error	 	If this grid is partial.
		 * @exception	std::invalid_argument	If @p cellFaceIsRightHanded, @p points, @p
		 * 										faceIndicesPerCell or @p nodeIndicesPerFace is @c nullptr.
		 * @exception	std::invalid_argument	If <tt>proxy == nullptr</tt> and no default HDF proxy is
		 * 										defined in the repository.
		 * @exception	std::invalid_argument	If <tt>localCrs == nullptr</tt> and no default local CRS
		 * 										is defined in the repository.
		 *
		 * @param [in]	  	cellFaceIsRightHanded	Boolean mask used to indicate which cell faces have
		 * 												an outwardly directed normal following a right hand
		 * 												rule. Array length is the sum of the cell face count
		 * 												per cell, and the data follows the order of the
		 * 												faces per cell RESQMLlist-of-lists.
		 * @param [in]	  	points				 	All the xyz points defining the nodes of the
		 * 												unstructured grid. There must a double count of
		 * 												<tt>pointCount * 3</tt>.
		 * @param 		  	pointCount			 	The count of points defining the nodes of this
		 * 											unstructured grid.
		 * @param 		  	faceCount			 	The count of faces in this unstructured grid. Be
		 * 											aware this count does not duplicate cell-shared faces.
		 * @param [in,out]	proxy				 	The hdf proxy which contains the datasets given in
		 * 											this method by means of paths. If @c nullptr, then
		 * 											the repository default HDF proxy will be used.
		 * @param [in]	  	faceIndicesPerCell   	Each item defines the index of the face of a cell.
		 * 												There must be a count of <tt>faceCountPerCell *
		 * 												cellCount</tt>.
		 * @param [in]	  	nodeIndicesPerFace   	Each item defines the index of the node of a face.
		 * 												There must be a count of <tt>nodeCountPerFace *
		 * 												faceCount</tt>.
		 * @param [in]	  	localCrs			 	(Optional) The local CRS. If @c nullptr (default),
		 * 												then the repository default local CRS will be used.
		 */
		DLL_IMPORT_OR_EXPORT void setTetrahedraOnlyGeometry(uint8_t * cellFaceIsRightHanded, double * points,
			uint64_t pointCount, uint64_t faceCount, EML2_NS::AbstractHdfProxy* proxy,
			uint64_t * faceIndicesPerCell, uint64_t * nodeIndicesPerFace, EML2_NS::AbstractLocal3dCrs * localCrs = nullptr);

		/**
		* Sets a geometry which is only defined by means of hexahedra using some existing HDF5 dataset.
		*
		* @copydetails setTetrahedraOnlyGeometryUsingExistingDatasets
		*/
		DLL_IMPORT_OR_EXPORT void setHexahedraOnlyGeometryUsingExistingDatasets(const std::string& cellFaceIsRightHanded, const std::string& points,
			uint64_t pointCount, uint64_t faceCount, EML2_NS::AbstractHdfProxy* proxy,
			const std::string& faceIndicesPerCell, const std::string& nodeIndicesPerFace, EML2_NS::AbstractLocal3dCrs * localCrs = nullptr);

		/**
		* Sets a geometry which is only defined by means of hexahedra and creates corresponding HDF5 datasets.
		*
		* @copydetails setTetrahedraOnlyGeometry
		*/
		DLL_IMPORT_OR_EXPORT void setHexahedraOnlyGeometry(uint8_t * cellFaceIsRightHanded, double * points,
			uint64_t pointCount, uint64_t faceCount, EML2_NS::AbstractHdfProxy* proxy,
			uint64_t * faceIndicesPerCell, uint64_t * nodeIndicesPerFace, EML2_NS::AbstractLocal3dCrs * localCrs = nullptr);

		DLL_IMPORT_OR_EXPORT uint64_t getPatchCount() const final {return 1;}

		/** The standard XML tag without XML namespace for serializing this data object. */
		DLL_IMPORT_OR_EXPORT static const char* XML_TAG;

		DLL_IMPORT_OR_EXPORT virtual std::string getXmlTag() const final { return XML_TAG; }

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
			uint64_t pointCount, uint64_t faceCount, EML2_NS::AbstractLocal3dCrs * localCrs, EML2_NS::AbstractHdfProxy* proxy,
			const std::string& faceIndicesPerCell, uint64_t faceCountPerCell,
			const std::string& nodeIndicesPerFace, uint64_t nodeCountPerFace) = 0;

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
		void setConstantCellShapeGeometry(uint8_t * cellFaceIsRightHanded, double * points,
			uint64_t pointCount, uint64_t faceCount, EML2_NS::AbstractLocal3dCrs * localCrs, EML2_NS::AbstractHdfProxy* proxy,
			uint64_t * faceIndicesPerCell, uint64_t faceCountPerCell,
			uint64_t * nodeIndicesPerFace, uint64_t nodeCountPerFace);

		unsigned int constantNodeCountPerFace;
		unsigned int constantFaceCountPerCell;
		std::unique_ptr<uint64_t[]> cumulativeNodeCountPerFace;
		std::unique_ptr<uint64_t[]> cumulativeFaceCountPerCell;
		std::unique_ptr<uint64_t[]> nodeIndicesOfFaces;
		std::unique_ptr<uint64_t[]> faceIndicesOfCells;

		/**
		* This method requires you have already loaded the geometry.
		*
		* @param cellIndex		The cell which contains the face we are getting its global index.
		* @param localFaceIndex The local face index regarding the cell of the face we are getting its global index.
		* @return				The global face index from its local face index in a cell.
		*/
		uint64_t getGlobalFaceIndex(uint64_t cellIndex, unsigned int localFaceIndex) const;
	};
}
