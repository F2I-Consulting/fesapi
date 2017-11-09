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

#include "resqml2_0_1/AbstractOrganizationInterpretation.h"
#include "resqml2/AbstractColumnLayerGridRepresentation.h"

namespace resqml2_0_1
{
	class DLL_IMPORT_OR_EXPORT AbstractStratigraphicOrganizationInterpretation : public AbstractOrganizationInterpretation
	{
	protected:

		/**
		* Only to be used in partial transfer context
		*/
		AbstractStratigraphicOrganizationInterpretation(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : AbstractOrganizationInterpretation(partialObject) {}

		AbstractStratigraphicOrganizationInterpretation() {}

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		AbstractStratigraphicOrganizationInterpretation(gsoap_resqml2_0_1::resqml2__AbstractStratigraphicOrganizationInterpretation* fromGsoap) : AbstractOrganizationInterpretation(fromGsoap) {}

		virtual std::vector<epc::Relationship> getAllEpcRelationships() const;

	public:

		/**
		* Destructor does nothing since the memory is managed by the gsoap context.
		*/
		virtual ~AbstractStratigraphicOrganizationInterpretation() {}

		/**
		* @return The count of grid representation assocaited to this strati organization.
		*/
		unsigned int getGridRepresentationCount() const;

		/**
		* Get a grid representation associated to this strati org interp by means of its index.
		* @param index	The index of the grid representation to get in the array of grid representaitons of this strati org interp.
		*/
		resqml2::AbstractGridRepresentation* getGridRepresentation(const unsigned int & index) const;

		/**
		* Check if a grid representation is wether associated to this strati org interp or not.
		* @param gridRep	The grid representation to check its assocaition with this strati org interp.
		* @return			True or false.
		*/
		bool isAssociatedToGridRepresentation(resqml2::AbstractGridRepresentation* gridRep) const;

	private:

		// Backward relationship
		std::vector<resqml2::AbstractGridRepresentation *> gridRepresentationSet;

		friend void resqml2::AbstractGridRepresentation::setCellAssociationWithStratigraphicOrganizationInterpretation(ULONG64 * stratiUnitIndices, const ULONG64 & nullValue, AbstractStratigraphicOrganizationInterpretation * stratiOrgInterp);
		friend void resqml2::AbstractColumnLayerGridRepresentation::setIntervalAssociationWithStratigraphicOrganizationInterpretation(ULONG64 * stratiUnitIndices, const ULONG64 & nullValue, AbstractStratigraphicOrganizationInterpretation* stratiOrgInterp);
	};
}
