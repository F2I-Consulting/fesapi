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

#include "resqml2/AbstractGridRepresentation.h"

namespace RESQML2_0_1_NS
{
	class AbstractStratigraphicOrganizationInterpretation;
}

namespace RESQML2_NS
{
	class AbstractColumnLayerGridRepresentation : public RESQML2_NS::AbstractGridRepresentation
	{
	protected:

		/**
		* Only to be used in partial transfer context
		*/
		AbstractColumnLayerGridRepresentation(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject, bool withTruncatedPillars) :RESQML2_NS::AbstractGridRepresentation(partialObject, withTruncatedPillars) {}

		/**
		* Default constructor
		*/
		AbstractColumnLayerGridRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp, RESQML2_NS::AbstractLocal3dCrs * crs, bool withTruncatedPillars) : RESQML2_NS::AbstractGridRepresentation(interp, crs, withTruncatedPillars) {}

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		AbstractColumnLayerGridRepresentation(gsoap_resqml2_0_1::resqml2__AbstractColumnLayerGridRepresentation* fromGsoap, bool withTruncatedPillars) : RESQML2_NS::AbstractGridRepresentation(fromGsoap, withTruncatedPillars) {}
		AbstractColumnLayerGridRepresentation(gsoap_resqml2_0_1::resqml2__AbstractTruncatedColumnLayerGridRepresentation* fromGsoap, bool withTruncatedPillars) : RESQML2_NS::AbstractGridRepresentation(fromGsoap, withTruncatedPillars) {}

		virtual std::vector<epc::Relationship> getAllEpcRelationships() const;
		void resolveTargetRelationships(COMMON_NS::DataObjectRepository* epcDoc);

	public:

		/**
		* Destructor does nothing since the memory is managed by the gsoap context.
		*/
		virtual ~AbstractColumnLayerGridRepresentation() {}

		/**
		* Get the K layer count of the grid
		*/
		DLL_IMPORT_OR_EXPORT unsigned int getKCellCount() const;

		/**
		* Set the K layer count of the grid
		*/
		DLL_IMPORT_OR_EXPORT void setKCellCount(const unsigned int & kCount);

		/**
		* Get the K direction of the grid.
		*/
		DLL_IMPORT_OR_EXPORT virtual gsoap_resqml2_0_1::resqml2__KDirection getKDirection() const = 0;

		/**
		* Set the stratigraphic organization interpretation which is associated to this grid representation.
		* @param stratiUnitIndices	Index of the stratigraphic unit of a given stratigraphic column for each interval of this grid representation. Array length is the number of interval in the grids. Intervals = layers + K gaps.
		* @param nullValue			The value which is used to tell the association between a grid interval and strati unit is unavailable.
		* @param stratiOrgInterp	The stratigraphic organization interpretation which is associated to this grid representation.
		*/
		DLL_IMPORT_OR_EXPORT void setIntervalAssociationWithStratigraphicOrganizationInterpretation(ULONG64 * stratiUnitIndices, const ULONG64 & nullValue, RESQML2_0_1_NS::AbstractStratigraphicOrganizationInterpretation* stratiOrgInterp);

		/**
		* @return	null pointer if no stratigraphic organization interpretation is associated to this grid representation. Otherwise return the data objet reference of the associated stratigraphic organization interpretation.
		*/
		gsoap_resqml2_0_1::eml20__DataObjectReference* getStratigraphicOrganizationInterpretationDor() const;

		/**
		* @return	true if this grid representation has got some association between stratigraphic unit indices and interval. Intervals = layers + K gaps.
		*/
		DLL_IMPORT_OR_EXPORT bool hasIntervalStratigraphicUnitIndices() const;

		/**
		* Get the stratigraphic unit indices (regarding the associated stratigraphic organization interpretation) of each interval of this grid representation.
		* @param stratiUnitIndices	This array must be allocated with a count equal to the count of interval in this grid. It will be filled in with the stratigraphic unit indices ordered as grid intervals are ordered.
		* @return					The null value is returned. The null value is used to tell the association between a grid interval and strati unit is unavailable.
		*/
		DLL_IMPORT_OR_EXPORT ULONG64 getIntervalStratigraphicUnitIndices(ULONG64 * stratiUnitIndices);
	};
}
