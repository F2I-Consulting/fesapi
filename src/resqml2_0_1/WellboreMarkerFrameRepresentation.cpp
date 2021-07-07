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
using namespace RESQML2_0_1_NS;
using namespace gsoap_resqml2_0_1;

const char* WellboreMarkerFrameRepresentation::XML_NS = "resqml20";

WellboreMarkerFrameRepresentation::WellboreMarkerFrameRepresentation(RESQML2_NS::WellboreInterpretation* interp, const std::string& guid, const std::string& title, RESQML2_NS::WellboreTrajectoryRepresentation* traj)
{
	if (interp == nullptr) {
		throw invalid_argument("The wellbore interpretation cannot be null.");
	}
	if (traj == nullptr) {
		throw invalid_argument("The wellbore trajectory representation cannot be null.");
	}

	gsoapProxy2_0_1 = soap_new_resqml20__obj_USCOREWellboreMarkerFrameRepresentation(interp->getGsoapContext());	
	_resqml20__WellboreMarkerFrameRepresentation* frame = static_cast<_resqml20__WellboreMarkerFrameRepresentation*>(gsoapProxy2_0_1);

	initMandatoryMetadata();
	setMetadata(guid, title, std::string(), -1, std::string(), std::string(), -1, std::string());

	interp->getRepository()->addDataObject(this);
	setInterpretation(interp);

	frame->Trajectory = traj->newResqmlReference();
	getRepository()->addRelationship(this, traj);
}

void WellboreMarkerFrameRepresentation::pushBackNewWellboreMarker(RESQML2_0_1_NS::WellboreMarker * marker)
{
	getRepository()->addRelationship(marker, this);

	_resqml20__WellboreMarkerFrameRepresentation* frame = static_cast<_resqml20__WellboreMarkerFrameRepresentation*>(gsoapProxy2_0_1);
	frame->WellboreMarker.push_back(static_cast<resqml20__WellboreMarker*>(marker->getEml20GsoapProxy()));

	getRepository()->addOrReplaceDataObject(marker);
}

COMMON_NS::DataObjectReference WellboreMarkerFrameRepresentation::getGeologicUnitOccurrenceInterpretationDor() const
{
	_resqml20__WellboreMarkerFrameRepresentation* frame = static_cast<_resqml20__WellboreMarkerFrameRepresentation*>(gsoapProxy2_0_1);
	return frame->IntervalStratigraphiUnits != nullptr ? COMMON_NS::DataObjectReference(frame->IntervalStratigraphiUnits->StratigraphicOrganization) : COMMON_NS::DataObjectReference();
}

void WellboreMarkerFrameRepresentation::setGeologicUnitOccurrenceInterpretation(RESQML2_NS::GeologicUnitOccurrenceInterpretation * occurrenceInterp)
{
	getRepository()->addRelationship(this, occurrenceInterp);

	_resqml20__WellboreMarkerFrameRepresentation* frame = static_cast<_resqml20__WellboreMarkerFrameRepresentation*>(gsoapProxy2_0_1);
	frame->IntervalStratigraphiUnits = soap_new_resqml20__IntervalStratigraphicUnits(frame->soap);
	frame->IntervalStratigraphiUnits->StratigraphicOrganization = occurrenceInterp->newResqmlReference();
}

void WellboreMarkerFrameRepresentation::setIntervalStratigraphicUnits(unsigned int const* stratiUnitIndices, unsigned int nullValue, RESQML2_NS::GeologicUnitOccurrenceInterpretation* occurrenceInterp, EML2_NS::AbstractHdfProxy* proxy)
{
	if (stratiUnitIndices == nullptr) {
		throw invalid_argument("The strati unit indices cannot be null.");
	}

	setGeologicUnitOccurrenceInterpretation(occurrenceInterp);
	getRepository()->addRelationship(this, proxy);

	_resqml20__WellboreMarkerFrameRepresentation* frame = static_cast<_resqml20__WellboreMarkerFrameRepresentation*>(gsoapProxy2_0_1);

	resqml20__IntegerHdf5Array* xmlDataset = soap_new_resqml20__IntegerHdf5Array(frame->soap);
	xmlDataset->NullValue = nullValue;
	xmlDataset->Values = soap_new_eml20__Hdf5Dataset(gsoapProxy2_0_1->soap);
	xmlDataset->Values->HdfProxy = proxy->newResqmlReference();
	xmlDataset->Values->PathInHdfFile = getHdfGroup() + "/IntervalStratigraphicUnits";
	frame->IntervalStratigraphiUnits->UnitIndices = xmlDataset;

	// ************ HDF *************
	const hsize_t dim = frame->NodeCount - 1;
	proxy->writeArrayNd(getHdfGroup(), "IntervalStratigraphicUnits", H5T_NATIVE_UINT, stratiUnitIndices, &dim, 1);
}

void WellboreMarkerFrameRepresentation::loadTargetRelationships()
{
	RESQML2_NS::WellboreMarkerFrameRepresentation::loadTargetRelationships();

	_resqml20__WellboreMarkerFrameRepresentation* rep = static_cast<_resqml20__WellboreMarkerFrameRepresentation*>(gsoapProxy2_0_1);

	for (auto* gsoapMarker : rep->WellboreMarker) {
		WellboreMarker* marker = getRepository()->getDataObjectByUuid<WellboreMarker>(gsoapMarker->uuid);
		if (marker == nullptr) {
			marker = new WellboreMarker(gsoapMarker);
			getRepository()->addOrReplaceDataObject(marker);
			if (gsoapMarker->Interpretation != nullptr) {
				getRepository()->addRelationship(marker, getRepository()->getDataObjectByUuid<RESQML2_NS::BoundaryFeatureInterpretation>(gsoapMarker->Interpretation->UUID));
			}
			if (gsoapMarker->WitsmlFormationMarker != nullptr) {
				getRepository()->addRelationship(marker, getRepository()->getDataObjectByUuid<WITSML2_0_NS::WellboreMarker>(gsoapMarker->WitsmlFormationMarker->UUID));
			}
		}
		getRepository()->addRelationship(marker, this);
	}
}
