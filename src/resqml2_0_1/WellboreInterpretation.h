/*-----------------------------------------------------------------------
Copyright F2I-CONSULTING, (2014-2016)

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
	class DLL_IMPORT_OR_EXPORT WellboreInterpretation : public resqml2::AbstractFeatureInterpretation
	{
	public:

		/**
		* Only to be used in partial transfer context
		*/
		WellboreInterpretation(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) :
			resqml2::AbstractFeatureInterpretation(partialObject)
		{
		}

		/**
		* Creates an instance of this class in a gsoap context.
		* @param horizon	The feature the instance interprets.
		* @param guid		The guid to set to the fault. If empty then a new guid will be generated.
		* @param title		A title for the instance to create.
		* @param isDrilled	Indicate if the wellbore is interpreted wether as drilled or not.
		*/
		WellboreInterpretation(class WellboreFeature * WellboreFeature, const std::string & guid, const std::string & title, bool isDrilled);

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		WellboreInterpretation(gsoap_resqml2_0_1::_resqml2__WellboreInterpretation* fromGsoap) : resqml2::AbstractFeatureInterpretation(fromGsoap) {}

		/**
		* Destructor does nothing since the memory is managed by the gsoap context.
		*/
		~WellboreInterpretation() {}

		/**
		* Indicates if the wellbore has been interpreted as drilled or not.
		*/
		bool isDrilled() const;

		/**
		* Get all the trajectory representations of this interpretation
		*/
		std::vector<class WellboreTrajectoryRepresentation*> getWellboreTrajectoryRepresentationSet() const;

		static const char* XML_TAG;
		virtual std::string getXmlTag() const {return XML_TAG;}
	};
}
