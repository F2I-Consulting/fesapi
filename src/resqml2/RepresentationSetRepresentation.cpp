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
#include "resqml2/RepresentationSetRepresentation.h"

#include <stdexcept>

#include "resqml2/AbstractLocal3dCrs.h"

#include "tools/Misc.h"

using namespace std;
using namespace epc;
using namespace resqml2;

const char* RepresentationSetRepresentation::XML_TAG = "RepresentationSetRepresentation";

std::string RepresentationSetRepresentation::getXmlTag() const
{
	return XML_TAG;
}

vector<Relationship> RepresentationSetRepresentation::getAllEpcRelationships() const
{
	vector<Relationship> result = AbstractRepresentation::getAllEpcRelationships();

	const unsigned int repCount = getRepresentationCount();
	for (size_t i = 0; i < repCount; ++i)
	{
		AbstractRepresentation* rep = getRepresentation(i);
		Relationship rel(rep->getPartNameInEpcDocument(), "", rep->getUuid());
		rel.setDestinationObjectType();
		result.push_back(rel);
	}

	return result;
}

void RepresentationSetRepresentation::importRelationshipSetFromEpc(common::EpcDocument* epcDoc)
{
	const unsigned int repCount = getRepresentationCount();
	for (unsigned int i = 0; i < repCount; ++i)
	{
		gsoap_resqml2_0_1::eml20__DataObjectReference* dor = getRepresentationDor(i);
		resqml2::AbstractRepresentation* rep = epcDoc->getResqmlAbstractObjectByUuid<resqml2::AbstractRepresentation>(dor->UUID);
		if (rep == nullptr) { // partial transfer
			getEpcDocument()->createPartial(dor);
			rep = getEpcDocument()->getResqmlAbstractObjectByUuid<resqml2::AbstractRepresentation>(dor->UUID);
		}
		if (rep == nullptr) {
			throw invalid_argument("The DOR looks invalid.");
		}
		updateXml = false;
		rep->pushBackIntoRepresentationSet(this, false);
		updateXml = true;
	}
}

ULONG64 RepresentationSetRepresentation::getXyzPointCountOfPatch(const unsigned int & patchIndex) const
{
	throw logic_error("Not implemented yet.");
}

void RepresentationSetRepresentation::getXyzPointsOfPatch(const unsigned int & patchIndex, double * xyzPoints) const
{
	if (patchIndex >= getPatchCount()) {
		throw range_error("The index patch is not in the allowed range of patch.");
	}

	throw logic_error("Please use getXyzPointsOfPatch on each included representation.");
}

bool RepresentationSetRepresentation::isHomogeneous() const
{
	if (gsoapProxy2_0_1 != nullptr) {
		return static_cast<gsoap_resqml2_0_1::_resqml2__RepresentationSetRepresentation*>(gsoapProxy2_0_1)->IsHomogeneous;
	}
	else {
		throw logic_error("Not implemented yet");
	}
}

unsigned int RepresentationSetRepresentation::getRepresentationCount() const
{
	if (gsoapProxy2_0_1 != nullptr) {
		return static_cast<gsoap_resqml2_0_1::_resqml2__RepresentationSetRepresentation*>(gsoapProxy2_0_1)->Representation.size();
	}
	else {
		throw logic_error("Not implemented yet");
	}
}

resqml2::AbstractRepresentation* RepresentationSetRepresentation::getRepresentation(const unsigned int & index) const
{
	return static_cast<resqml2::AbstractRepresentation*>(epcDocument->getResqmlAbstractObjectByUuid(getRepresentationUuid(index)));
}

gsoap_resqml2_0_1::eml20__DataObjectReference* RepresentationSetRepresentation::getRepresentationDor(const unsigned int & index) const
{
	if (index >= getRepresentationCount()) {
		throw range_error("The index of the representation to get is out of range in this representaiton set representation");
	}

	if (gsoapProxy2_0_1 != nullptr) {
		return static_cast<gsoap_resqml2_0_1::_resqml2__RepresentationSetRepresentation*>(gsoapProxy2_0_1)->Representation[index];
	}
	else {
		throw logic_error("Not implemented yet");
	}
}

std::string RepresentationSetRepresentation::getRepresentationUuid(const unsigned int & index) const
{
	return getRepresentationDor(index)->UUID;
}

void RepresentationSetRepresentation::pushBackXmlRepresentation(resqml2::AbstractRepresentation* rep)
{
	if (gsoapProxy2_0_1 != nullptr) {
		gsoap_resqml2_0_1::_resqml2__RepresentationSetRepresentation* rsr = static_cast<gsoap_resqml2_0_1::_resqml2__RepresentationSetRepresentation*>(gsoapProxy2_0_1);

		rsr->Representation.push_back(rep->newResqmlReference());
		if (isHomogeneous() && getRepresentationCount() > 1)
		{
			if (rep->getGsoapType() != getRepresentation(0)->getGsoapType()) {
				rsr->IsHomogeneous = false;
			}
		}
	}
	else {
		throw logic_error("Not implemented yet");
	}
}
