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

/** . */
namespace RESQML2_0_1_NS
{
	class AbstractStratigraphicOrganizationInterpretation;
}

/** . */
namespace RESQML2_NS
{
	/** Proxy class for an abstract column layer grid representation. */
	class AbstractColumnLayerGridRepresentation : public RESQML2_NS::AbstractGridRepresentation
	{
	public:

		/** Destructor does nothing since the memory is managed by the gsoap context. */
		virtual ~AbstractColumnLayerGridRepresentation() {}

		/**
		 * Gets the K layer count of this grid
		 *
		 * @exception	std::logic_error	If this grid is partial or if the underlying gSOAP instance
		 * 									is not a RESQML2.0 one.
		 * @exception	std::range_error	If the count is strictly greater than unsigned int max.
		 *
		 * @returns	The K layer count of this grid.
		 */
		DLL_IMPORT_OR_EXPORT unsigned int getKCellCount() const;

		/**
		 * Sets the K layer count of this grid
		 *
		 * @exception	std::logic_error	If this grid is partial or if the underlying gSOAP instance is not a RESQML2.0 one.
		 *
		 * @param 	kCount	The K layer count to set to this grid.
		 */
		DLL_IMPORT_OR_EXPORT void setKCellCount(unsigned int kCount);

		/**
		 * Gets the K direction (up, down or not monotonic) of this grid.
		 *
		 * @exception	std::invalid_argument	If there is no geometry on this grid.
		 *
		 * @returns	The K direction of this grid.
		 */
		DLL_IMPORT_OR_EXPORT virtual gsoap_resqml2_0_1::resqml20__KDirection getKDirection() const = 0;

		/**
		 * Set the stratigraphic organization interpretation which is associated to this grid
		 * representation.
		 *
		 * @exception	std::invalid_argument	If this grid is a truncated one and thus cannot be linked
		 * 										to a stratigraphic column in RESQML2.0.
		 * @exception	std::invalid_argument	If @p stratiOrgInterp is null.
		 * @exception	std::invalid_argument	If @p hdfProxy is null and no default HDF proxy is
		 * 										provided in the associated data object repository.
		 *
		 * @param [in]	   	stratiUnitIndices	Index of the stratigraphic unit of a given stratigraphic
		 * 										column for each interval of this grid representation.
		 * 										Array length is the number of interval in the grids.
		 * 										Intervals = layers + K gaps.
		 * @param 		   	nullValue		 	The value which is used to tell that the association
		 * 										between a grid interval and a stratigraphic unit is
		 * 										unavailable.
		 * @param [in]	   	stratiOrgInterp  	The stratigraphic organization interpretation which is
		 * 										associated to this grid representation.
		 * @param [in, out]	hdfProxy		 	(Optional) The HDF proxy where to write the values. It
		 * 										must be already opened for writing and won't be closed in
		 * 										this method.
		 */
		DLL_IMPORT_OR_EXPORT void setIntervalAssociationWithStratigraphicOrganizationInterpretation(ULONG64* stratiUnitIndices, ULONG64 nullValue, RESQML2_NS::AbstractStratigraphicOrganizationInterpretation* stratiOrgInterp, COMMON_NS::AbstractHdfProxy* hdfProxy = nullptr);

		/**
		 * Gets the data object reference of the stratigraphic organization interpretation which is
		 * associated to this grid representation.
		 *
		 * @returns	Empty if no stratigraphic organization interpretation is associated to this
		 * 			grid representation. Otherwise return the data objet reference of the associated
		 * 			stratigraphic organization interpretation.
		 */
		COMMON_NS::DataObjectReference getStratigraphicOrganizationInterpretationDor() const;

		/**
		 * Queries if this grid has some interval stratigraphic unit indices.
		 *
		 * @exception	std::logic_error	If this grid is partial or if the underlying gSOAP instance is not a RESQML2.0 one..
		 *
		 * @returns	true if this grid representation has got some association between stratigraphic unit
		 * 			indices and intervals. Intervals = layers + K gaps.
		 */
		DLL_IMPORT_OR_EXPORT bool hasIntervalStratigraphicUnitIndices() const;

		/**
		 * Get the stratigraphic unit indices (regarding the associated stratigraphic organization
		 * interpretation) of each interval of this grid representation.
		 *
		 * @exception	std::invalid_argument	If this grid is a truncated one.
		 * @exception	std::invalid_argument	If this grid has no stratigraphic unit interval
		 * 										information.
		 *
		 * @param [out]	stratiUnitIndices	This array must be allocated with a size equal to the
		 * 										count of interval in this grid. Intervals = layers + K gaps.
		 * 										It will be filled in with the stratigraphic unit indices
		 * 										ordered as grid intervals are ordered.
		 *
		 * @returns	The null value. The null value is used to tell the association between a grid
		 * 			interval and a stratigraphic unit is unavailable.
		 */
		DLL_IMPORT_OR_EXPORT ULONG64 getIntervalStratigraphicUnitIndices(ULONG64 * stratiUnitIndices);

		/**
		 * Gets the most complex pillar geometry we can find on this grid. The returned value is not
		 * computed. It is just read from the data object attributes. Since it is denormalized
		 * information, inconsistency (mainly due to non synchronized information) might occur. In order
		 * to be sure the value is consistent with actual data, please compute this value again from the
		 * pillar kind indices.
		 *
		 * @exception	std::invalid_argument	If this grid has no AbstractColumnLayerGridGeometry.
		 *
		 * @returns	The most complex pillar geometry which we can find on this grid.
		 */
		DLL_IMPORT_OR_EXPORT gsoap_resqml2_0_1::resqml20__PillarShape getMostComplexPillarGeometry() const;

	protected:

		/**
		* Only to be used in partial transfer context
		*/
		AbstractColumnLayerGridRepresentation(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject, bool withTruncatedPillars) :RESQML2_NS::AbstractGridRepresentation(partialObject, withTruncatedPillars) {}

		/**
		* Default constructor
		*/
		AbstractColumnLayerGridRepresentation(bool withTruncatedPillars) : RESQML2_NS::AbstractGridRepresentation(withTruncatedPillars) {}

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		AbstractColumnLayerGridRepresentation(gsoap_resqml2_0_1::resqml20__AbstractColumnLayerGridRepresentation* fromGsoap, bool withTruncatedPillars) : RESQML2_NS::AbstractGridRepresentation(fromGsoap, withTruncatedPillars) {}
		AbstractColumnLayerGridRepresentation(gsoap_resqml2_0_1::resqml20__AbstractTruncatedColumnLayerGridRepresentation* fromGsoap, bool withTruncatedPillars) : RESQML2_NS::AbstractGridRepresentation(fromGsoap, withTruncatedPillars) {}
		AbstractColumnLayerGridRepresentation(gsoap_eml2_2::resqml22__AbstractColumnLayerGridRepresentation* fromGsoap, bool withTruncatedPillars) : RESQML2_NS::AbstractGridRepresentation(fromGsoap, withTruncatedPillars) {}
		AbstractColumnLayerGridRepresentation(gsoap_eml2_2::resqml22__AbstractTruncatedColumnLayerGridRepresentation* fromGsoap, bool withTruncatedPillars) : RESQML2_NS::AbstractGridRepresentation(fromGsoap, withTruncatedPillars) {}

		void loadTargetRelationships();
	};
}
