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
#include "../resqml2/GeologicUnitOccurrenceInterpretation.h"
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

	interp->getRepository()->addDataObject(this);
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

COMMON_NS::DataObjectReference WellboreMarkerFrameRepresentation::getGeologicUnitOccurrenceInterpretationDor() const
{
	_resqml22__WellboreMarkerFrameRepresentation* frame = static_cast<_resqml22__WellboreMarkerFrameRepresentation*>(gsoapProxy2_3);

	if (frame->IntervalStratigraphicUnits.size() > 1) {
		throw range_error("More than one link to a strati column is not supported for now.");
	}

	return frame->IntervalStratigraphicUnits.empty()
		? COMMON_NS::DataObjectReference()
		: COMMON_NS::DataObjectReference(frame->IntervalStratigraphicUnits[0]->StratigraphicOrganizationInterpretation);	
}

void WellboreMarkerFrameRepresentation::setGeologicUnitOccurrenceInterpretation(RESQML2_NS::GeologicUnitOccurrenceInterpretation * occurrenceInterp)
{
	getRepository()->addRelationship(this, occurrenceInterp);

	_resqml22__WellboreMarkerFrameRepresentation* frame = static_cast<_resqml22__WellboreMarkerFrameRepresentation*>(gsoapProxy2_3);
	resqml22__IntervalStratigraphicUnits* intervalStratigraphiUnits = nullptr;
	if (frame->IntervalStratigraphicUnits.empty()) {
		intervalStratigraphiUnits = soap_new_resqml22__IntervalStratigraphicUnits(frame->soap);
		frame->IntervalStratigraphicUnits.push_back(intervalStratigraphiUnits);
	}
	else {
		intervalStratigraphiUnits = frame->IntervalStratigraphicUnits[0];
	}
	intervalStratigraphiUnits->StratigraphicOrganizationInterpretation = occurrenceInterp->newEml23Reference();
}

void WellboreMarkerFrameRepresentation::setIntervalStratigraphicUnits(unsigned int const* stratiUnitIndices, unsigned int nullValue, RESQML2_NS::GeologicUnitOccurrenceInterpretation* occurrenceInterp, EML2_NS::AbstractHdfProxy* proxy)
{
	if (stratiUnitIndices == nullptr) {
		throw invalid_argument("The strati unit indices cannot be null.");
	}

	setGeologicUnitOccurrenceInterpretation(occurrenceInterp);
	getRepository()->addRelationship(this, proxy);

	_resqml22__WellboreMarkerFrameRepresentation* frame = static_cast<_resqml22__WellboreMarkerFrameRepresentation*>(gsoapProxy2_3);

	eml23__JaggedArray* xmlJaggedArray = soap_new_eml23__JaggedArray(frame->soap);

	// Elements
	eml23__IntegerExternalArray* xmlDataset = soap_new_eml23__IntegerExternalArray(frame->soap);
	xmlDataset->NullValue = nullValue;
	xmlDataset->Values = soap_new_eml23__ExternalDataArray(gsoapProxy2_3->soap);
	xmlDataset->Values->ExternalDataArrayPart.push_back(createExternalDataArrayPart(getHdfGroup() +"/IntervalStratigraphicUnits", frame->NodeCount - 1, proxy));
	xmlJaggedArray->Elements = xmlDataset;

	// Cumumulative Length
	eml23__IntegerLatticeArray* cumulativeLength = soap_new_eml23__IntegerLatticeArray(frame->soap);
	cumulativeLength->StartValue = 1;
	eml23__IntegerConstantArray* offsets = soap_new_eml23__IntegerConstantArray(frame->soap);
	offsets->Value = 1;
	offsets->Count = frame->NodeCount - 2;
	cumulativeLength->Offset.push_back(offsets);

	frame->IntervalStratigraphicUnits[0]->UnitIndices = xmlJaggedArray;

	// ************ HDF *************
	const hsize_t dim = frame->NodeCount - 1;
	proxy->writeArrayNd(getHdfGroup(), "IntervalStratigraphicUnits", H5T_NATIVE_UINT, stratiUnitIndices, &dim, 1);
}

void WellboreMarkerFrameRepresentation::loadTargetRelationships()
{
	RESQML2_NS::WellboreMarkerFrameRepresentation::loadTargetRelationships();

	_resqml22__WellboreMarkerFrameRepresentation* rep = static_cast<_resqml22__WellboreMarkerFrameRepresentation*>(gsoapProxy2_3);

	for (auto* gsoapMarker : rep->WellboreMarker) {
		WellboreMarker* marker = getRepository()->getDataObjectByUuid<WellboreMarker>(gsoapMarker->uuid);
		if (marker == nullptr) {
			marker = new WellboreMarker(gsoapMarker);
			getRepository()->addOrReplaceDataObject(marker);
			if (gsoapMarker->Interpretation != nullptr) {
				getRepository()->addRelationship(marker, getRepository()->getDataObjectByUuid<RESQML2_NS::BoundaryFeatureInterpretation>(gsoapMarker->Interpretation->Uuid));
			}
			if (gsoapMarker->WitsmlFormationMarker != nullptr) {
				getRepository()->addRelationship(marker, getRepository()->getDataObjectByUuid<WITSML2_0_NS::WellboreMarker>(gsoapMarker->WitsmlFormationMarker->Uuid));
			}
		}
		getRepository()->addRelationship(marker, this);
	}
}
