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

#include <vector>

#include "resqml2/AbstractFeatureInterpretation.h"

namespace resqml2
{
	class DLL_IMPORT_OR_EXPORT AbstractFeature : public common::AbstractObject
	{
	public:

		/**
		* Only to be used in partial transfer context
		*/
		AbstractFeature(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : common::AbstractObject(partialObject) {}

		/**
		* Default constructor
		* Set the gsoap proxy to nullptr.
		*/
		AbstractFeature() {}

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		* @param fromGsoap	The gsoap proxy which shold be wrapped by the constructed feature.
		*/
		AbstractFeature(gsoap_resqml2_0_1::resqml2__AbstractFeature* fromGsoap) : common::AbstractObject(fromGsoap) {}

		/**
		* Destructor does nothing since the memory is managed by the gsoap context.
		*/
		virtual ~AbstractFeature() {}

		/**
		* Get all the interpretations of this feature
		*/
		std::vector<AbstractFeatureInterpretation*> 	getInterpretationSet() const;

		/**
		 * Get the interpretation count of this feature.
		 */
		unsigned int 								getInterpretationCount() const;

		/**
		 * Get a particular interpretation of this feature according to its position in the interpretation ordering.
		 */
		AbstractFeatureInterpretation*				getInterpretation(const unsigned int & index) const;

	protected:

		virtual std::vector<epc::Relationship> getAllEpcRelationships() const;
		/**
		* Does nothing since feature has not forward relationships at all
		*/
		virtual void importRelationshipSetFromEpc(common::EpcDocument* epcDoc) {}

		std::vector<AbstractFeatureInterpretation*> interpretationSet; /// All the interpretations of the feature

		friend void AbstractFeatureInterpretation::setInterpretedFeature(resqml2::AbstractFeature * feature);
	};
}
