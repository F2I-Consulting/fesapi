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
#include "resqml2_0_1/SeismicLineFeature.h"

#include "resqml2_0_1/SeismicLineSetFeature.h"

using namespace std;
using namespace resqml2_0_1;
using namespace gsoap_resqml2_0_1;
using namespace epc;

const char* SeismicLineFeature::XML_TAG = "SeismicLineFeature";

SeismicLineFeature::SeismicLineFeature(soap* soapContext, const std::string & guid, const std::string & title,
			const int & traceIndexIncrement, const int & firstTraceIndex, const unsigned int & traceCount):
	seismicLineSet(nullptr)
{
	if (soapContext == nullptr)
		throw invalid_argument("The soap context cannot be null.");

	gsoapProxy2_0_1 = soap_new_resqml2__obj_USCORESeismicLineFeature(soapContext, 1);
	_resqml2__SeismicLineFeature* seismicLine = static_cast<_resqml2__SeismicLineFeature*>(gsoapProxy2_0_1);

	seismicLine->TraceIndexIncrement = traceIndexIncrement;
	seismicLine->FirstTraceIndex = firstTraceIndex;
	seismicLine->TraceCount = traceCount;

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "", "");
}

int SeismicLineFeature::getTraceIndexIncrement() const
{
	return static_cast<_resqml2__SeismicLineFeature*>(gsoapProxy2_0_1)->TraceIndexIncrement;
}
		
int SeismicLineFeature::getFirstTraceIndex() const
{
	return static_cast<_resqml2__SeismicLineFeature*>(gsoapProxy2_0_1)->FirstTraceIndex;
}
		
unsigned int SeismicLineFeature::getTraceCount() const
{
	return static_cast<_resqml2__SeismicLineFeature*>(gsoapProxy2_0_1)->TraceCount;
}

void SeismicLineFeature::setSeismicLineSet(SeismicLineSetFeature * seisLineSet)
{
	// EPC
	seismicLineSet = seisLineSet;
	seisLineSet->seismicLineSet.push_back(this);

	// XML
	if (updateXml)
	{
		static_cast<_resqml2__SeismicLineFeature*>(gsoapProxy2_0_1)->IsPartOf = seisLineSet->newResqmlReference();
	}
}

std::vector<epc::Relationship> SeismicLineFeature::getAllEpcRelationships() const
{
	std::vector<epc::Relationship> result;

	if (seismicLineSet)
	{
		Relationship rel(seismicLineSet->getPartNameInEpcDocument(), "", seismicLineSet->getUuid());
		rel.setDestinationObjectType();
		result.push_back(rel);
	}

	return result;
}

void SeismicLineFeature::importRelationshipSetFromEpc(common::EpcDocument* epcDoc)
{
	updateXml = false;

	_resqml2__SeismicLineFeature* seismicLine = static_cast<_resqml2__SeismicLineFeature*>(gsoapProxy2_0_1);

	if (seismicLine->IsPartOf)
	{
		SeismicLineSetFeature* seisLineSet = static_cast<SeismicLineSetFeature*>(epcDoc->getResqmlAbstractObjectByUuid(seismicLine->IsPartOf->UUID));
		if (seisLineSet)
			setSeismicLineSet(seisLineSet);
	}

	updateXml = true;
}
