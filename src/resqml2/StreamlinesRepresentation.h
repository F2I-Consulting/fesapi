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

#include "AbstractRepresentation.h"

namespace RESQML2_NS
{
	class AbstractGridRepresentation;

	/**
	 * @brief	Representation of streamlines associated with a streamline feature and interpretation.
	 *			Use the StreamlinesFeature to specify the vector field that supports the streamlines, i.e., describes what flux is being traced.
	 *			Use the Generic Feature  Interpretation to distinguish between shared and differing interpretations.
	 */
	class StreamlinesRepresentation : public AbstractRepresentation
	{
	public:

		StreamlinesRepresentation() {}

		/**
		 * Only to be used in partial transfer context.
		 *
		 * @param [in]	partialObject	If non-nullptr, the partial object.
		 */
		DLL_IMPORT_OR_EXPORT StreamlinesRepresentation(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : AbstractRepresentation(partialObject) {}

		/**
		 * Creates an instance of this class by wrapping a gSOAP instance.
		 *
		 * @param [in]	fromGsoap	If non-null, the gSOAP instance.
		 */
		StreamlinesRepresentation(gsoap_resqml2_0_1::_resqml20__StreamlinesRepresentation* fromGsoap): AbstractRepresentation(fromGsoap) {}

		/**
		 * Creates an instance of this class by wrapping a gSOAP instance.
		 *
		 * @param [in]	fromGsoap	If non-null, the gSOAP instance.
		 */
		StreamlinesRepresentation(gsoap_eml2_3::_resqml22__StreamlinesRepresentation* fromGsoap) : AbstractRepresentation(fromGsoap) {}

		/**
		* Destructor does nothing since the memory is managed by the gSOAP context.
		*/
		virtual ~StreamlinesRepresentation() = default;

		/**
		 * Gets the count of line contained in this streamlines representation.
		 *
		 * @exception	std::logic_error	If this feature is partial.
		 *
		 * @returns	The count of line contained in this streamlines representation.
		*/
		DLL_IMPORT_OR_EXPORT virtual uint64_t getLineCount() const = 0;
		
		//********************************
		//****  WELLBORE INFO ************
		//********************************

		/**
		 * Gets the count of wellbore trajectories of this streamlines representation.
		 *
		 * @exception	std::range_error	If the count of wellbore trajectories is strictly
		 * 									greater than unsigned int max.
		 *
		 * @returns	The count of wellbore trajectories.
		 */
		DLL_IMPORT_OR_EXPORT virtual uint64_t getWellboreTrajectoryCount() const = 0;

		/**
		 * Gets the wellbore trajectory located at a specific index of this streamlines
		 * representation.
		 *
		 * @exception	std::out_of_range	If <tt>index &gt;=</tt>
		 * 									getWellboreTrajectoryCount().
		 *
		 * @param 	index	Zero-based index of the wellbore trajectory we look for.
		 *
		 * @returns	The wellbore trajectory at position @p index.
		 */
		DLL_IMPORT_OR_EXPORT RESQML2_NS::WellboreTrajectoryRepresentation* getWellboreTrajectory(uint64_t index) const;

		/**
		 * Get the DOR of the wellbore trajectory located at a specific index of this streamlines representation.
		 *
		 * @exception	std::out_of_range	If <tt>index &gt;=</tt>
		 * 									getWellboreTrajectoryCount().
		 *
		 * @param 	index	Zero-based index of the wellbore trajectory we look for.
		 *
		 * @returns	The DOR of the wellbore trajectory at position @p index.
		 */
		virtual COMMON_NS::DataObjectReference getWellboreTrajectoryDor(uint64_t index) const = 0;

		/**
		 * @brief	Gets all the wellbore indices which are injectors.
		 *			Null values signify that that line does not initiate at an injector, e.g., it may come from fluid expansion or an aquifer.
		 *
		 * @param [in/out]	injectorPerLine 	The 0-based injector wellbore index defined by the order of the wellbore in the list of WellboreTrajectoryRepresentation references.
		 *									It must be preallocated with a size getWellboreTrajectories().size() and it won't be freed by FESAPI.
		 *
		 * @returns	The null value used in injectorPerLine.
		 */
		DLL_IMPORT_OR_EXPORT virtual uint32_t getInjectorPerLine(uint32_t* injectorPerLine) const = 0;

		/**
		 * @brief	Gets all the wellbore indices which are producers.
		 *			Null values signify that that line does not terminate at a producer, e.g., it may approach a stagnation area.
		 *
		 * @param [in/out]	injectorPerLine 	The 0-based injector wellbore index defined by the order of the wellbore in the list of WellboreTrajectoryRepresentation references.
		 *									It must be preallocated with a size getWellboreTrajectories().size() and it won't be freed by FESAPI.
		 *
		 * @returns	The null value used in producerPerLine.
		 */
		DLL_IMPORT_OR_EXPORT virtual uint32_t getProducerPerLine(uint32_t* producerPerLine) const = 0;

		/**
		 * Specify the wellbores on which streamlines may originate or terminate.
		 *
		 * @param [in]	injectorPerLine			The 0-based injector wellbore index defined by the order of the wellbore in the list of WellboreTrajectoryRepresentation references.
		 *										Null values signify that that line does not initiate at an injector, e.g., it may come from fluid expansion or an aquifer.
		 * @param [in]	producerPerLine			The 0-based producer wellbore index defined by the order of the wellbore in the list of WellboreTrajectoryRepresentation references.
		 *										Null values signify that that line does not terminate at a producer, e.g., it may approach a stagnation area.
		 * @param [in]	wellboreTrajectories	The list of WellboreTrajectoryRepresentation references.
		 * @param [in]	nullValue				The null value used in injectorPerLine and producerPerLine.
		 * @param [in]	hdfProxy				(Optional) The HDF proxy which defines where the
		 * 										nodes will be stored. If @c nullptr (default), then
		 * 										the repository default HDF proxy will be used.
		 */
		void virtual setWellboreInformation(uint32_t const* injectorPerLine, uint32_t const* producerPerLine, const std::vector<RESQML2_NS::WellboreTrajectoryRepresentation*> & wellboreTrajectories,
			uint32_t nullValue = (std::numeric_limits<uint32_t>::max)(), EML2_NS::AbstractHdfProxy* hdfProxy = nullptr) = 0;

		//********************************
		//********** GEOMETRY ************
		//********************************

		/**
		 * Gets the node count per line.
		 *
		 * @param [out]	nodeCountPerPolyline	A preallocated array to receive the node count per
		 * 										line. Its size must be
		 * 										<tt>getLineCount(patchIndex)</tt>.
		 */
		DLL_IMPORT_OR_EXPORT virtual void getNodeCountPerLine(uint32_t * nodeCountPerPolyline) const = 0;

		/**
		* Get the xyz point count in a given patch.
		*/
		DLL_IMPORT_OR_EXPORT uint64_t getXyzPointCountOfPatch(uint64_t patchIndex) const final {
			if (patchIndex > 0) {
				throw std::out_of_range("The patch index is out of range and should only be zero.");
			}

			const uint64_t lineCount = getLineCount();
			std::unique_ptr<uint32_t[]> nodeCountPerPolyline(new uint32_t[lineCount]);
			getNodeCountPerLine(nodeCountPerPolyline.get());

			uint64_t result = 0;
			for (uint64_t lineIndex = 0; lineIndex < lineCount; ++lineIndex) {
				result += nodeCountPerPolyline[lineIndex];
			}
			return result;
		}

		/**
		 * Gets the interval count per line.
		 *
		 * @param [out]	intervalCountPerPolyline	A preallocated array to receive the interval count per
		 * 											line. Its size must be
		* 											<tt>getLineCount(patchIndex)</tt>.
		 */
		DLL_IMPORT_OR_EXPORT void getIntervalCountPerLine(uint32_t * intervalCountPerPolyline) const {
			getNodeCountPerLine(intervalCountPerPolyline);

			const uint64_t lineCount = getLineCount();
			for (uint64_t lineIndex = 0; lineIndex < lineCount; ++lineIndex) {
				intervalCountPerPolyline[lineIndex] -= 1;
			}
		}

		/**
		 * Gets the total interval count in this streamlines representation.
		 */
		DLL_IMPORT_OR_EXPORT uint64_t getIntervalCount() const {
			const uint64_t lineCount = getLineCount();
			std::unique_ptr<uint32_t[]> intervalCountPerPolyline(new uint32_t[lineCount]);
			getIntervalCountPerLine (intervalCountPerPolyline.get());

			uint64_t result = 0;
			for (uint64_t lineIndex = 0; lineIndex < lineCount; ++lineIndex) {
				result += intervalCountPerPolyline[lineIndex];
			}
			return result;
		}

		/**
		 * Sets the geometry of the streamlines representation.
		 *
		 * @exception	std::invalid_argument	If <tt>proxy == nullptr</tt> and no default HDF proxy is
		 * 										defined in the repository.
		 * @exception	std::invalid_argument	If <tt>localCrs == nullptr</tt> and no default local CRS
		 * 										id defined in the repository.
		 *
		 * @param [in]	  	nodeCountPerPolyline  	The node count per polyline in this representation. It is
		 * 											ordered by polyline. There must be getLineCount()
		 * 											values in this array.
		 * @param [in]	  	xyzPoints			  	The xyz values of the nodes. Ordered by xyz, then by
		 * 											node and then by polyline. It must be three times the
		 * 											total count of nodes.
		 *											If the streamlines are associated to grids then the there must be one point
		 *											one each face intersected by the a line + the start and end point.
		 * @param [in,out]	hdfProxy			  	(Optional) The HDF proxy which defines where the
		 * 											nodes will be stored. If @c nullptr (default), then
		 * 											the repository default HDF proxy will be used.
		 * @param [in]	  	localCrs			  	(Optional) The local CRS where the points are
		 * 											defined. If @c nullptr (default value), then the
		 * 											repository default local CRS will be used.
		 */
		DLL_IMPORT_OR_EXPORT virtual void setGeometry(
			uint32_t const * nodeCountPerPolyline, double const * xyzPoints,
			EML2_NS::AbstractHdfProxy* hdfProxy = nullptr, EML2_NS::AbstractLocal3dCrs* localCrs = nullptr) = 0;

		//********************************
		//*******  GRID INFO *************
		//********************************

		/**
		 * Sets all information about the intersected grid cells. You must first provide the geometry of
		 * the streamlines representation before to use this method.
		 *
		 * @exception	std::invalid_argument	If @p gridIndices, @p cellIndices, @p
		 * 										localFacePairPerCellIndices or @p hdfProxy is @c nullptr.
		 * @exception	std::invalid_argument	If <tt>cellCount == 0</tt>.
		 * @exception	std::logic_error	 	If the geometry of the streamlines have not been provided before
		 * 										using this method.
		 *
		 * @param 		  	gridIndices								An array containing, for each interval
		 * 															of the lines of the represenation, the index of the
		 * 															grid it is associated to. The size of
		 * 															this array is getIntervalCount.
		 * @param 		  	gridIndicesNullValue					The null value used in @p gridIndices
		 * 															in order to indicate that an interval
		 * 															does not correspond to any intersected
		 * 															grid.
		 * @param 		  	cellIndices								An array containing the intersected
		 * 															cell index. They are ordered according
		 * 															to geoemtry intervals and @p gridIndices.
		 * 															The array length must equal the getIntervalCount.
		 *															The null value is arbitrarily set to -1 since
		 *															it has no interest. Indeed corresponding gridIndex
		 *															already informs about the presence or not of a cell.
		 * @param 		  	localFacePairPerCellIndices				An array containing, for each cell,
		 * 															the entry and exit intersection faces of
		 * 															the line in the cell. The array
		 * 															dimension must equal twice getIntervalCount.
		 * @param 		  	localFacePairPerCellIndicesNullValue	The null value used in @p
		 * 															localFacePerCellIndices in order to
		 * 															indicate that it corresponds to a missing
		 * 															intersection, e.g., when a line
		 * 															originates or terminates within a cell.
		 * @param [in,out]	hdfProxy								The HDF proxy where the numerical
		 * 															values will be stored. It must be already
		 * 															opened for writing and won't be closed.It
		 * 															cannot be @c nullptr.
		 */
		DLL_IMPORT_OR_EXPORT virtual void setIntervalGridCells(uint16_t const* gridIndices, uint16_t gridIndicesNullValue,
			int64_t const* cellIndices,
			uint8_t const* localFacePairPerCellIndices, uint8_t localFacePairPerCellIndicesNullValue,
			const std::vector<RESQML2_NS::AbstractGridRepresentation*> & supportingGrids,
			EML2_NS::AbstractHdfProxy * hdfProxy = nullptr) = 0;

		/**
		 * For each interval of the lines of the representation, gets the index of the grid it is associated to.
		 *
		 * @exception	std::range_error	If the grid indices are stored in an integer constant array
		 * 									and if the the constant value is strictly superior than uint16_t maximum value.
		 * @exception	std::logic_error	If the grid indices are neither stored in a HDF5 integer
		 * 									array nor in an integer constant array.
		 *
		 * @param [out]	gridIndices	An array for receiving the grids indices. The size of this array is
		 * 							getIntervalCount.
		 *
		 * @returns	The null value used in @p gridIndices in order to indicate that an interval does not
		 * 			correspond to any intersected grid.
		 */
		DLL_IMPORT_OR_EXPORT virtual uint16_t getGridIndices(uint16_t * gridIndices) const = 0;

		/**
		 * For each interval of the lines of the representation, gets the index of the cell it is associated to.
		 * Cell index in in the scope of the associated grid at the same index.
		 *
		 * @exception	std::range_error	If the cell indices are stored in an integer constant array
		 * 									and if the the constant value is strictly superior than uint64_t maximum value.
		 * @exception	std::logic_error	If the * indices are neither stored in a HDF5 integer
		 * 									array nor in an integer constant array.
		 *
		 * @param [out]	cellIndices	An array for receiving the cell indices. The size of this array is
		 * 							getIntervalCount.
		 *
		 * @returns	The null value used in @p cellIndices in order to indicate that an interval does not
		 * 			correspond to any intersected grid.
		 */
		DLL_IMPORT_OR_EXPORT virtual int64_t getCellIndices(int64_t * cellIndices) const = 0;

		/**
		 * For each interval of the lines of the representation, gets the entry and exit intersection faces of the line in the cell.
		 *
		 * @exception	std::range_error	If the grid indices are stored in an integer constant array
		 * 									and if the the constant value is strictly superior than uint8_t maximum value.
		 * @exception	std::logic_error	If the grid indices are neither stored in a HDF5 integer
		 * 									array nor in an integer constant array.
		 *
		 * @param [out]	gridIndices	An array for receiving the local Face Pair Per Cell Indices. The size of this array is twice
		 * 							getIntervalCount.
		 *
		 * @returns	The null value used in @p localFacePairPerCellIndices in order to indicate that a line interval does not intersect a face in this cell.
		 */
		DLL_IMPORT_OR_EXPORT virtual uint8_t getLocalFacePairPerCellIndices(uint8_t * localFacePairPerCellIndices) const = 0;

		/**
		 * Gets the count of grid representations of this streamlines representation.
		 *
		 * @exception	std::range_error	If the count of grid representations is strictly
		 * 									greater than unsigned int max.
		 *
		 * @returns	The count of grid representation.
		 */
		DLL_IMPORT_OR_EXPORT virtual uint64_t getGridRepresentationCount() const = 0;

		/**
		 * Gets the grid representation located at a specific index of this streamlines
		 * representation.
		 *
		 * @exception	std::out_of_range	If <tt>index &gt;=</tt>
		 * 									getGridRepresentationCount().
		 *
		 * @param 	index	Zero-based index of the grid representation we look for.
		 *
		 * @returns	The grid representation at position @p index.
		 */
		DLL_IMPORT_OR_EXPORT RESQML2_NS::AbstractGridRepresentation* getGridRepresentation(uint64_t index) const;

		/**
		 * Get the DOR of the grid representation located at a specific index of this streamlines representation.
		 *
		 * @exception	std::out_of_range	If <tt>index &gt;=</tt>
		 * 									getGridRepresentationCount().
		 *
		 * @param 	index	Zero-based index of the grid representation we look for.
		 *
		 * @returns	The DOR of the grid representation at position @p index.
		 */
		virtual COMMON_NS::DataObjectReference getGridRepresentationDor(uint64_t index) const = 0;

		DLL_IMPORT_OR_EXPORT uint64_t getPatchCount() const final { return 1; }

		/** Loads target relationships */
		void loadTargetRelationships() final;

		/**
		* The standard XML tag without XML namespace for serializing this data object.
		*/
		DLL_IMPORT_OR_EXPORT static const char* XML_TAG;

		DLL_IMPORT_OR_EXPORT virtual std::string getXmlTag() const final { return XML_TAG; }
	};
}
