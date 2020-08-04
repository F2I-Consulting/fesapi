/*-----------------------------------------------------------------------
Licensed to the Apache Software Foundation (ASF) under one
or more contributor license agreements.  See the NOTICE file
distributed with this work for additional information
regarding copyright ownership.  The ASF licenses this file
to you under the Apache License, Version 2.0 (the
"License"; you may not use this file except in compliance
with the License.  You may obtain a copy of the License at

  http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing,
software distributed under the License is distributed on an
"AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
KIND, either express or implied.  See the License for the
specific language governing permissions and limitations
under the License.
-----------------------------------------------------------------------*/
#include "WellboreMarkerFrameRepresentation.h"

#include <stdexcept>

#include <H5Tpublic.h>

#include "../eml2/AbstractHdfProxy.h"

#include "../resqml2/WellboreInterpretation.h"
#include "../resqml2/WellboreTrajectoryRepresentation.h"
#include "../resqml2/StratigraphicOccurrenceInterpretation.h"
#include "../resqml2/BoundaryFeatureInterpretation.h"

#include "../witsml2_0/WellboreMarker.h"

#include "WellboreMarker.h"

using namespace std;
using namespace RESQML2_2_NS;
using namespace gsoap_eml2_3;

const char* WellboreMarkerFrameRepresentation::XML_NS = "resqml22";

WellboreMarkerFrameRepresentation::WellboreMarkerFrameRepresentation(RESQML2_NS::WellboreInterpretation* interp, const std::string& guid, const std::string& title, RESQML2_NS::WellboreTrajectoryRepresentation* traj)
{
	if (interp == nullptr) {
		throw invalid_argument("The wellbore interpretation cannot be null.");
	}
	if (traj == nullptr) {
		throw invalid_argument("The wellbore trajectory representation cannot be null.");
	}

	gsoapProxy2_3 = soap_new_resqml22__WellboreMarkerFrameRepresentation(interp->getGsoapContext());	
	_resqml22__WellboreMarkerFrameRepresentation* frame = static_cast<_resqml22__WellboreMarkerFrameRepresentation*>(gsoapProxy2_3);

	initMandatoryMetadata();
	setMetadata(guid, title, std::string(), -1, std::string(), std::string(), -1, std::string());

	setInterpretation(interp);

	frame->Trajectory = traj->newEml23Reference();
	getRepository()->addRelationship(this, traj);
}

void WellboreMarkerFrameRepresentation::pushBackNewWellboreMarker(RESQML2_2_NS::WellboreMarker * marker)
{
	getRepository()->addRelationship(marker, this);

	_resqml22__WellboreMarkerFrameRepresentation* frame = static_cast<_resqml22__WellboreMarkerFrameRepresentation*>(gsoapProxy2_3);
	frame->WellboreMarker.push_back(static_cast<resqml22__WellboreMarker*>(marker->getEml23GsoapProxy()));

	getRepository()->addOrReplaceDataObject(marker);
}

unsigned int WellboreMarkerFrameRepresentation::getWellboreMarkerCount()
{
	return static_cast<_resqml22__WellboreMarkerFrameRepresentation*>(gsoapProxy2_3)->WellboreMarker.size();
}

COMMON_NS::DataObjectReference WellboreMarkerFrameRepresentation::getStratigraphicOccurrenceInterpretationDor() const
{
	_resqml22__WellboreMarkerFrameRepresentation* frame = static_cast<_resqml22__WellboreMarkerFrameRepresentation*>(gsoapProxy2_3);

	if (frame->IntervalStratigraphiUnits.size() > 1) {
		throw range_error("More than one link to a strati column is not supported for now.");
	}

	return frame->IntervalStratigraphiUnits.empty()
		? COMMON_NS::DataObjectReference()
		: COMMON_NS::DataObjectReference(frame->IntervalStratigraphiUnits[0]->StratigraphicOrganizationInterpretation);	
}

void WellboreMarkerFrameRepresentation::setStratigraphicOccurrenceInterpretation(RESQML2_NS::StratigraphicOccurrenceInterpretation * stratiOccurrenceInterp)
{
	getRepository()->addRelationship(this, stratiOccurrenceInterp);

	_resqml22__WellboreMarkerFrameRepresentation* frame = static_cast<_resqml22__WellboreMarkerFrameRepresentation*>(gsoapProxy2_3);
	resqml22__IntervalStratigraphicUnits* intervalStratigraphiUnits = nullptr;
	if (frame->IntervalStratigraphiUnits.empty()) {
		intervalStratigraphiUnits = soap_new_resqml22__IntervalStratigraphicUnits(frame->soap);
		frame->IntervalStratigraphiUnits.push_back(intervalStratigraphiUnits);
	}
	else {
		intervalStratigraphiUnits = frame->IntervalStratigraphiUnits[0];
	}
	intervalStratigraphiUnits->StratigraphicOrganizationInterpretation = stratiOccurrenceInterp->newEml23Reference();
}

void WellboreMarkerFrameRepresentation::setIntervalStratigraphicUnits(unsigned int const* stratiUnitIndices, unsigned int nullValue, RESQML2_NS::StratigraphicOccurrenceInterpretation* stratiOccurrenceInterp, EML2_NS::AbstractHdfProxy* proxy)
{
	if (stratiUnitIndices == nullptr) {
		throw invalid_argument("The strati unit indices cannot be null.");
	}

	setStratigraphicOccurrenceInterpretation(stratiOccurrenceInterp);
	getRepository()->addRelationship(this, proxy);

	_resqml22__WellboreMarkerFrameRepresentation* frame = static_cast<_resqml22__WellboreMarkerFrameRepresentation*>(gsoapProxy2_3);

	eml23__JaggedArray* xmlJaggedArray = soap_new_eml23__JaggedArray(frame->soap);

	// Elements
	eml23__IntegerExternalArray* xmlDataset = soap_new_eml23__IntegerExternalArray(frame->soap);
	xmlDataset->NullValue = nullValue;
	xmlDataset->Values = soap_new_eml23__ExternalDataset(gsoapProxy2_3->soap);
	auto dsPart = soap_new_eml23__ExternalDatasetPart(gsoapProxy2_3->soap);
	dsPart->EpcExternalPartReference = proxy->newEml23Reference();
	dsPart->PathInExternalFile = getHdfGroup() + "/IntervalStratigraphicUnits";
	xmlDataset->Values->ExternalFileProxy.push_back(dsPart);
	xmlJaggedArray->Elements = xmlDataset;

	// Cumumulative Length
	eml23__IntegerLatticeArray* cumulativeLength = soap_new_eml23__IntegerLatticeArray(frame->soap);
	cumulativeLength->StartValue = 1;
	eml23__IntegerConstantArray* offsets = soap_new_eml23__IntegerConstantArray(frame->soap);
	offsets->Value = 1;
	offsets->Count = frame->NodeCount - 2;
	cumulativeLength->Offset.push_back(offsets);

	frame->IntervalStratigraphiUnits[0]->UnitIndices = xmlJaggedArray;

	// ************ HDF *************
	hsize_t dim = frame->NodeCount - 1;
	proxy->writeArrayNd(getHdfGroup(), "IntervalStratigraphicUnits", H5T_NATIVE_UINT, stratiUnitIndices, &dim, 1);
}

void WellboreMarkerFrameRepresentation::loadTargetRelationships()
{
	RESQML2_NS::WellboreMarkerFrameRepresentation::loadTargetRelationships();

	_resqml22__WellboreMarkerFrameRepresentation* rep = static_cast<_resqml22__WellboreMarkerFrameRepresentation*>(gsoapProxy2_3);

	for (size_t i = 0; i < rep->WellboreMarker.size(); ++i) {
		WellboreMarker* marker = getRepository()->getDataObjectByUuid<WellboreMarker>(rep->WellboreMarker[i]->uuid);
		if (marker == nullptr) {
			marker = new WellboreMarker(rep->WellboreMarker[i]);
			getRepository()->addOrReplaceDataObject(marker);
			if (rep->WellboreMarker[i]->Interpretation != nullptr) {
				getRepository()->addRelationship(marker, getRepository()->getDataObjectByUuid<RESQML2_NS::BoundaryFeatureInterpretation>(rep->WellboreMarker[i]->Interpretation->Uuid));
			}
			if (rep->WellboreMarker[i]->WitsmlFormationMarker != nullptr) {
				getRepository()->addRelationship(marker, getRepository()->getDataObjectByUuid<WITSML2_0_NS::WellboreMarker>(rep->WellboreMarker[i]->WitsmlFormationMarker->Uuid));
			}
		}
		getRepository()->addRelationship(marker, this);
	}
}
