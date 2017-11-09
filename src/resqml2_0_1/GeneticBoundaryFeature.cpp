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
#include "resqml2_0_1/GeneticBoundaryFeature.h"

using namespace std;
using namespace resqml2_0_1;

const char* GeneticBoundaryFeature::XML_TAG = "GeneticBoundaryFeature";

GeneticBoundaryFeature::GeneticBoundaryFeature(soap* soapContext, const string & guid, const string & title, bool isAnHorizon)
{
	if (soapContext == nullptr)
		throw invalid_argument("The soap context cannot be null.");

	gsoapProxy2_0_1 = gsoap_resqml2_0_1::soap_new_resqml2__obj_USCOREGeneticBoundaryFeature(soapContext, 1);
	gsoap_resqml2_0_1::_resqml2__GeneticBoundaryFeature* horizon = static_cast<gsoap_resqml2_0_1::_resqml2__GeneticBoundaryFeature*>(gsoapProxy2_0_1);
	horizon->GeneticBoundaryKind = isAnHorizon ? gsoap_resqml2_0_1::resqml2__GeneticBoundaryKind__horizon : gsoap_resqml2_0_1::resqml2__GeneticBoundaryKind__geobody_x0020boundary;

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "", "");
}

bool GeneticBoundaryFeature::isAnHorizon() const
{
	return static_cast<gsoap_resqml2_0_1::_resqml2__GeneticBoundaryFeature*>(gsoapProxy2_0_1)->GeneticBoundaryKind == gsoap_resqml2_0_1::resqml2__GeneticBoundaryKind__horizon;
}

void GeneticBoundaryFeature::setAge(const ULONG64 & age)
{
	gsoap_resqml2_0_1::_resqml2__GeneticBoundaryFeature* feature = static_cast<gsoap_resqml2_0_1::_resqml2__GeneticBoundaryFeature*>(gsoapProxy2_0_1);
	if (!hasAnAge()) {
		feature->AbsoluteAge = gsoap_resqml2_0_1::soap_new_resqml2__Timestamp(getGsoapContext());
	}
	if (feature->AbsoluteAge->YearOffset == nullptr) {
		feature->AbsoluteAge->YearOffset = static_cast<LONG64*>(soap_malloc(getGsoapContext(), sizeof(LONG64)));
	}

	*(feature->AbsoluteAge->YearOffset) = age;
}

bool GeneticBoundaryFeature::hasAnAge() const
{
	return static_cast<gsoap_resqml2_0_1::_resqml2__GeneticBoundaryFeature*>(gsoapProxy2_0_1)->AbsoluteAge != nullptr;
}

ULONG64 GeneticBoundaryFeature::getAge() const
{
	if (!hasAnAge()) {
		throw invalid_argument("This feature has not an age.");
	}

	return static_cast<gsoap_resqml2_0_1::_resqml2__GeneticBoundaryFeature*>(gsoapProxy2_0_1)->AbsoluteAge->YearOffset == nullptr ? 0 : abs(*(static_cast<gsoap_resqml2_0_1::_resqml2__GeneticBoundaryFeature*>(gsoapProxy2_0_1)->AbsoluteAge->YearOffset));
}
