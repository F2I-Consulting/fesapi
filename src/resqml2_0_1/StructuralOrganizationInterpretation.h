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
#include "resqml2_0_1/EarthModelInterpretation.h"

namespace resqml2_0_1
{
	class DLL_IMPORT_OR_EXPORT StructuralOrganizationInterpretation : public AbstractOrganizationInterpretation
	{
	public:

		/**
		* Only to be used in partial transfer context
		*/
		StructuralOrganizationInterpretation(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : AbstractOrganizationInterpretation(partialObject) {}

		/**
		* Creates an instance of this class in a gsoap context.
		* @param orgFeat			The feature the instance interprets. It must be a structural organization feature.
		* @param guid				The guid to set to the interpretation. If empty then a new guid will be generated.
		* @param title				A title for the instance to create.
		* @param orderingCriteria	How the included horizons are ordered.
		*/
		StructuralOrganizationInterpretation(class OrganizationFeature * orgFeat, const std::string & guid, const std::string & title, const gsoap_resqml2_0_1::resqml2__OrderingCriteria & orderingCriteria);

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		StructuralOrganizationInterpretation(gsoap_resqml2_0_1::_resqml2__StructuralOrganizationInterpretation* fromGsoap): AbstractOrganizationInterpretation(fromGsoap) {}

		/**
		* Destructor does nothing since the memory is managed by the gsoap context.
		*/
		~StructuralOrganizationInterpretation() {}

		static const char* XML_TAG;
		virtual std::string getXmlTag() const {return XML_TAG;}

        /**
        * Add a FaultInterpretation to this StructuralOrganizationInterpretation.
        * Does add the inverse relationship i.e. from the included FaultInterpretation to this StructuralOrganizationInterpretation.
        */
        void pushBackFaultInterpretation(class FaultInterpretation * faultInterpretation);

		unsigned int getFaultInterpretationCount() const;

		class FaultInterpretation* getFaultInterpretation(const unsigned int & index);

        /**
        * Add an HorizonInterpretation to this StructuralOrganizationInterpretation.
        * Does add the inverse relationship i.e. from the included HorizonInterpretation to this StructuralOrganizationInterpretation.
        * @param horizonInterpretation the HorizonInterpretation to add
        * @param stratigraphicRank the rank of the horizon interpretation within this structural organization
        **/
        void pushBackHorizonInterpretation(class HorizonInterpretation * horizonInterpretation, const int & stratigraphicRank);

		/**
        * Add a Frontier interpretation to this StructuralOrganizationInterpretation as a top.
        * Does add the inverse relationship i.e. from the included Frontier interpretation to this StructuralOrganizationInterpretation.
        */
		void pushBackTopFrontierInterpretation(AbstractFeatureInterpretation * topFrontierInterpretation);

		/**
        * Add a Frontier interpretation to this StructuralOrganizationInterpretation as a bottom.
        * Does add the inverse relationship i.e. from the included Frontier interpretation to this StructuralOrganizationInterpretation.
        */
        void pushBackBottomFrontierInterpretation(AbstractFeatureInterpretation * bottomFrontierInterpretation);

		/**
        * Add a Frontier interpretation to this StructuralOrganizationInterpretation as a side.
        * Does add the inverse relationship i.e. from the included Frontier interpretation to this StructuralOrganizationInterpretation.
        */
        void pushBackSideFrontierInterpretation(AbstractFeatureInterpretation * sideFrontierInterpretation);

    private:

        std::vector<epc::Relationship> getAllEpcRelationships() const;	
		void importRelationshipSetFromEpc(common::EpcDocument* epcDoc);

        // backward relationships
        std::vector<EarthModelInterpretation *> earthModelSet;
		std::vector<resqml2::GridConnectionSetRepresentation *> gridConnectionSet;

		friend void EarthModelInterpretation::setStructuralOrganizationInterpretation(StructuralOrganizationInterpretation * structOrganization);
	};
}
