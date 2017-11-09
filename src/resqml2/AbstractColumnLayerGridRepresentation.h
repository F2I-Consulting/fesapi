/*-----------------------------------------------------------------------
Copyright F2I-CONSULTING, (2014-2017)

philippe.verney@f2i-consulting.com

This software is a computer program whose purpose is to access to data formatted using Energistics standards.

This software is governed by the CeCILL-B license under French law and
abiding by the rules of distribution of free software.  You can  use, 
modify and/ or redistribute the software under the terms of the CeCILL-B
license as circulated by CEA, CNRS and INRIA at the following URL
"http://www.cecill.info". 

As a counterpart to the access to the source code and  rights to copy,
modify and redistribute granted by the license, users are provided only
with a limited warranty  and the software's author,  the holder of the
economic rights,  and the successive licensors  have only  limited
liability. 

In this respect, the user's attention is drawn to the risks associated
with loading,  using,  modifying and/or developing or reproducing the
software by the user in light of its specific status of free software,
that may mean  that it is complicated to manipulate,  and  that  also
therefore means  that it is reserved for developers  and  experienced
professionals having in-depth computer knowledge. Users are therefore
encouraged to load and test the software's suitability as regards their
requirements in conditions enabling the security of their systems and/or 
data to be ensured and,  more generally, to use and operate it in the 
same conditions as regards security. 

The fact that you are presently reading this means that you have had
knowledge of the CeCILL-B license and that you accept its terms.
-----------------------------------------------------------------------*/
#pragma once

#include "resqml2/AbstractGridRepresentation.h"

namespace resqml2_0_1
{
	class AbstractStratigraphicOrganizationInterpretation;
}

namespace resqml2
{
	class DLL_IMPORT_OR_EXPORT AbstractColumnLayerGridRepresentation : public resqml2::AbstractGridRepresentation
	{
	protected:

		/**
		* Only to be used in partial transfer context
		*/
		AbstractColumnLayerGridRepresentation(common::EpcDocument * epcDoc, gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject, bool withTruncatedPillars) :resqml2::AbstractGridRepresentation(partialObject, withTruncatedPillars) {}

		/**
		* Default constructor
		*/
		AbstractColumnLayerGridRepresentation(resqml2::AbstractFeatureInterpretation* interp, resqml2::AbstractLocal3dCrs * crs, bool withTruncatedPillars) : resqml2::AbstractGridRepresentation(interp, crs, withTruncatedPillars) {}

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		AbstractColumnLayerGridRepresentation(gsoap_resqml2_0_1::resqml2__AbstractColumnLayerGridRepresentation* fromGsoap, bool withTruncatedPillars) : resqml2::AbstractGridRepresentation(fromGsoap, withTruncatedPillars) {}
		AbstractColumnLayerGridRepresentation(gsoap_resqml2_0_1::resqml2__AbstractTruncatedColumnLayerGridRepresentation* fromGsoap, bool withTruncatedPillars) : resqml2::AbstractGridRepresentation(fromGsoap, withTruncatedPillars) {}

		virtual std::vector<epc::Relationship> getAllEpcRelationships() const;
		void importRelationshipSetFromEpc(common::EpcDocument* epcDoc);

	public:

		/**
		* Destructor does nothing since the memory is managed by the gsoap context.
		*/
		virtual ~AbstractColumnLayerGridRepresentation() {}

		/**
		* Get the K layer count of the grid
		*/
		unsigned int getKCellCount() const;

		/**
		* Set the K layer count of the grid
		*/
		void setKCellCount(const unsigned int & kCount);

		/**
		* Get the K direction of the grid.
		*/
		virtual gsoap_resqml2_0_1::resqml2__KDirection getKDirection() const = 0;

		/**
		* Set the stratigraphic organization interpretation which is associated to this grid representation.
		* @param stratiUnitIndices	Index of the stratigraphic unit of a given stratigraphic column for each interval of this grid representation. Array length is the number of interval in the grids. Intervals = layers + K gaps.
		* @param nullValue			The value which is used to tell the association between a grid interval and strati unit is unavailable.
		* @param stratiOrgInterp	The stratigraphic organization interpretation which is associated to this grid representation.
		*/
		void setIntervalAssociationWithStratigraphicOrganizationInterpretation(ULONG64 * stratiUnitIndices, const ULONG64 & nullValue, resqml2_0_1::AbstractStratigraphicOrganizationInterpretation* stratiOrgInterp);

		/**
		* @return	null pointer if no stratigraphic organization interpretation is associated to this grid representation. Otherwise return the data objet reference of the associated stratigraphic organization interpretation.
		*/
		gsoap_resqml2_0_1::eml20__DataObjectReference* getStratigraphicOrganizationInterpretationDor() const;

		/**
		* @return	true if this grid representation has got some association between stratigraphic unit indices and interval. Intervals = layers + K gaps.
		*/
		bool hasIntervalStratigraphicUnitIndices() const;

		/**
		* Get the stratigraphic unit indices (regarding the associated stratigraphic organization interpretation) of each interval of this grid representation.
		* @param stratiUnitIndices	This array must be allocated with a count equal to the count of interval in this grid. It will be filled in with the stratigraphic unit indices ordered as grid intervals are ordered.
		* @return					The null value is returned. The null value is used to tell the association between a grid interval and strati unit is unavailable.
		*/
		ULONG64 getIntervalStratigraphicUnitIndices(ULONG64 * stratiUnitIndices);
	};
}
