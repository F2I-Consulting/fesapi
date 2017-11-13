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

#include "resqml2/AbstractFeatureInterpretation.h"

namespace resqml2_0_1
{
	/**
	* This class defines the behaviour of all Resqml2 organizations
	*/
	class DLL_IMPORT_OR_EXPORT AbstractOrganizationInterpretation : public resqml2::AbstractFeatureInterpretation
	{
	protected:

		/**
		* Only to be used in partial transfer context
		*/
		AbstractOrganizationInterpretation(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : resqml2::AbstractFeatureInterpretation(partialObject) {}

		AbstractOrganizationInterpretation() {}

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		AbstractOrganizationInterpretation(gsoap_resqml2_0_1::resqml2__AbstractOrganizationInterpretation* fromGsoap) : resqml2::AbstractFeatureInterpretation(fromGsoap) {}

	public:

		/**
		* Destructor does nothing since the memory is managed by the gsoap context.
		*/
		virtual ~AbstractOrganizationInterpretation() {}

		/**
		 * Add a binary contact to the organization interpretation by means of a simple sentence.
		 */
		void pushBackBinaryContact(const gsoap_resqml2_0_1::resqml2__ContactRelationship & kind, resqml2::AbstractFeatureInterpretation* subject, const gsoap_resqml2_0_1::resqml2__ContactVerb & verb, resqml2::AbstractFeatureInterpretation* directObject);

		/**
		 * Add a binary contact to the organization itnerpretation by means of a sentence where the direct object can be qualified.
		 */
		void pushBackBinaryContact(const gsoap_resqml2_0_1::resqml2__ContactRelationship & kind, resqml2::AbstractFeatureInterpretation* subject, const gsoap_resqml2_0_1::resqml2__ContactVerb & verb, resqml2::AbstractFeatureInterpretation* directObject,
				const gsoap_resqml2_0_1::resqml2__ContactSide & directObjectQualifier);

        /**
         * Add a binary contact to the organization interpretation by means of a sentence where both the subject and the direct object can be qualified.
         */
		void pushBackBinaryContact(const gsoap_resqml2_0_1::resqml2__ContactRelationship & kind, resqml2::AbstractFeatureInterpretation* subject, const gsoap_resqml2_0_1::resqml2__ContactSide & subjectQualifier,
                                   const gsoap_resqml2_0_1::resqml2__ContactVerb & verb,
								   resqml2::AbstractFeatureInterpretation* directObject, const gsoap_resqml2_0_1::resqml2__ContactSide & directObjectQualifier);
	};
}
