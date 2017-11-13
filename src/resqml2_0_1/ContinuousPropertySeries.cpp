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
#include "resqml2_0_1/ContinuousPropertySeries.h"

#include <stdexcept>

#include "resqml2_0_1/TimeSeries.h"
#include "resqml2/AbstractRepresentation.h"
#include "resqml2_0_1/PropertyKind.h"

using namespace std;
using namespace resqml2_0_1;
using namespace gsoap_resqml2_0_1;
using namespace epc;

const char* ContinuousPropertySeries::XML_TAG = "ContinuousPropertySeries";

ContinuousPropertySeries::ContinuousPropertySeries(resqml2::AbstractRepresentation * rep, const string & guid, const string & title,
	const unsigned int & dimension, const gsoap_resqml2_0_1::resqml2__IndexableElements & attachmentKind,
	const gsoap_resqml2_0_1::resqml2__ResqmlUom & uom, const resqml2__ResqmlPropertyKind & energisticsPropertyKind,
	resqml2::TimeSeries * ts, const bool & useInterval)
{
	gsoapProxy2_0_1 = soap_new_resqml2__obj_USCOREContinuousPropertySeries(rep->getGsoapContext(), 1);	
	_resqml2__ContinuousPropertySeries* prop = static_cast<_resqml2__ContinuousPropertySeries*>(gsoapProxy2_0_1);
	prop->IndexableElement = attachmentKind;
	prop->Count = dimension;
	prop->UOM = uom;

	resqml2__StandardPropertyKind* xmlStandardPropKind = soap_new_resqml2__StandardPropertyKind(gsoapProxy2_0_1->soap, 1);
	xmlStandardPropKind->Kind = energisticsPropertyKind;
	prop->PropertyKind = xmlStandardPropKind;

	setRepresentation(rep);

	prop->SeriesTimeIndices = soap_new_resqml2__TimeIndices(gsoapProxy2_0_1->soap, 1);
	prop->SeriesTimeIndices->TimeIndexCount = ts->getTimestampCount();
	prop->SeriesTimeIndices->UseInterval = useInterval;
	setTimeSeries(ts);

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "", "");
}

ContinuousPropertySeries::ContinuousPropertySeries(resqml2::AbstractRepresentation * rep, const string & guid, const string & title,
	const unsigned int & dimension, const gsoap_resqml2_0_1::resqml2__IndexableElements & attachmentKind,
	const gsoap_resqml2_0_1::resqml2__ResqmlUom & uom, resqml2::PropertyKind * localPropKind,
	resqml2::TimeSeries * ts, const bool & useInterval)
{
	gsoapProxy2_0_1 = soap_new_resqml2__obj_USCOREContinuousPropertySeries(rep->getGsoapContext(), 1);	
	_resqml2__ContinuousPropertySeries* prop = static_cast<_resqml2__ContinuousPropertySeries*>(gsoapProxy2_0_1);
	prop->IndexableElement = attachmentKind;
	prop->Count = dimension;
	prop->UOM = uom;

	setRepresentation(rep);

	prop->SeriesTimeIndices = soap_new_resqml2__TimeIndices(gsoapProxy2_0_1->soap, 1);
	prop->SeriesTimeIndices->TimeIndexCount = ts->getTimestampCount();
	prop->SeriesTimeIndices->UseInterval = useInterval;
	setTimeSeries(ts);

	setLocalPropertyKind(localPropKind);

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "", "");
}
