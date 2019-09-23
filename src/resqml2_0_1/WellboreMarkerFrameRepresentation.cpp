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
#include "resqml2_0_1/WellboreMarkerFrameRepresentation.h"

#include <stdexcept>

#if defined(__gnu_linux__) || defined(__APPLE__)
#include <unistd.h>
#include <pwd.h>
#endif

#include "H5Tpublic.h"

#include "resqml2_0_1/WellboreInterpretation.h"
#include "resqml2_0_1/WellboreTrajectoryRepresentation.h"
#include "resqml2/AbstractLocal3dCrs.h"
#include "tools/GuidTools.h"
#include "resqml2_0_1/WellboreMarker.h"
#include "resqml2_0_1/StratigraphicOccurrenceInterpretation.h"
#include "resqml2_0_1/HorizonInterpretation.h"
#include "common/AbstractHdfProxy.h"

using namespace std;
using namespace RESQML2_0_1_NS;
using namespace gsoap_resqml2_0_1;

const char* WellboreMarkerFrameRepresentation::XML_TAG = "WellboreMarkerFrameRepresentation";

WellboreMarkerFrameRepresentation::WellboreMarkerFrameRepresentation(WellboreInterpretation * interp, const std::string & guid, const std::string & title, WellboreTrajectoryRepresentation * traj)
{
	gsoapProxy2_0_1 = soap_new_resqml20__obj_USCOREWellboreMarkerFrameRepresentation(interp->getGsoapContext(), 1);	
	_resqml20__WellboreMarkerFrameRepresentation* frame = static_cast<_resqml20__WellboreMarkerFrameRepresentation*>(gsoapProxy2_0_1);

	initMandatoryMetadata();
	setMetadata(guid, title, std::string(), -1, std::string(), std::string(), -1, std::string());

	setInterpretation(interp);

	frame->Trajectory = traj->newResqmlReference();
	getRepository()->addRelationship(this, traj);
}

WellboreMarkerFrameRepresentation::WellboreMarkerFrameRepresentation(gsoap_resqml2_0_1::_resqml20__WellboreMarkerFrameRepresentation* fromGsoap) :
	WellboreFrameRepresentation(fromGsoap)
{
}

void WellboreMarkerFrameRepresentation::pushBackNewWellboreMarker(WellboreMarker * marker)
{
	getRepository()->addRelationship(marker, this);

	_resqml20__WellboreMarkerFrameRepresentation* frame = static_cast<_resqml20__WellboreMarkerFrameRepresentation*>(gsoapProxy2_0_1);
	frame->WellboreMarker.push_back(static_cast<resqml20__WellboreMarker*>(marker->getEml20GsoapProxy()));

	getRepository()->addOrReplaceDataObject(marker);
}

unsigned int WellboreMarkerFrameRepresentation::getWellboreMarkerCount()
{
	return static_cast<_resqml20__WellboreMarkerFrameRepresentation*>(gsoapProxy2_0_1)->WellboreMarker.size();
}

StratigraphicOccurrenceInterpretation* WellboreMarkerFrameRepresentation::getStratigraphicOccurrenceInterpretation()
{
	_resqml20__WellboreMarkerFrameRepresentation* wmfr = static_cast<_resqml20__WellboreMarkerFrameRepresentation*>(gsoapProxy2_0_1);
	return wmfr->IntervalStratigraphiUnits != nullptr && wmfr->IntervalStratigraphiUnits->StratigraphicOrganization != nullptr
		? getRepository()->getDataObjectByUuid<StratigraphicOccurrenceInterpretation>(wmfr->IntervalStratigraphiUnits->StratigraphicOrganization->UUID)
		: nullptr;
}

void WellboreMarkerFrameRepresentation::setStratigraphicOccurrenceInterpretation( StratigraphicOccurrenceInterpretation * stratiOccurenceInterp)
{
	getRepository()->addRelationship(this, stratiOccurenceInterp);

	_resqml20__WellboreMarkerFrameRepresentation* frame = static_cast<_resqml20__WellboreMarkerFrameRepresentation*>(gsoapProxy2_0_1);
	frame->IntervalStratigraphiUnits = soap_new_resqml20__IntervalStratigraphicUnits(frame->soap, 1);
	frame->IntervalStratigraphiUnits->StratigraphicOrganization = stratiOccurenceInterp->newResqmlReference();
}

void WellboreMarkerFrameRepresentation::setIntervalStratigraphicUnits(unsigned int * stratiUnitIndices, unsigned int nullValue, StratigraphicOccurrenceInterpretation* stratiOccurenceInterp, COMMON_NS::AbstractHdfProxy* proxy)
{
	if (stratiUnitIndices == nullptr) {
		throw invalid_argument("The strati unit indices cannot be null.");
	}

	setStratigraphicOccurrenceInterpretation(stratiOccurenceInterp);
	getRepository()->addRelationship(this, proxy);

	_resqml20__WellboreMarkerFrameRepresentation* frame = static_cast<_resqml20__WellboreMarkerFrameRepresentation*>(gsoapProxy2_0_1);

	resqml20__IntegerHdf5Array* xmlDataset = soap_new_resqml20__IntegerHdf5Array(frame->soap, 1);
	xmlDataset->NullValue = nullValue;
	xmlDataset->Values = soap_new_eml20__Hdf5Dataset(gsoapProxy2_0_1->soap, 1);
	xmlDataset->Values->HdfProxy = proxy->newResqmlReference();
	xmlDataset->Values->PathInHdfFile = "/RESQML/" + frame->uuid + "/IntervalStratigraphicUnits";
	frame->IntervalStratigraphiUnits->UnitIndices = xmlDataset;

	// ************ HDF *************
	hsize_t dim = frame->NodeCount - 1;
	proxy->writeArrayNd(frame->uuid, "IntervalStratigraphicUnits", H5T_NATIVE_UINT, stratiUnitIndices, &dim, 1);
}

void WellboreMarkerFrameRepresentation::loadTargetRelationships()
{
	WellboreFrameRepresentation::loadTargetRelationships();

	_resqml20__WellboreMarkerFrameRepresentation* rep = static_cast<_resqml20__WellboreMarkerFrameRepresentation*>(gsoapProxy2_0_1);

	if (rep->IntervalStratigraphiUnits != nullptr) {
		convertDorIntoRel<StratigraphicOccurrenceInterpretation>(rep->IntervalStratigraphiUnits->StratigraphicOrganization);
	}

	for (size_t i = 0; i < rep->WellboreMarker.size(); ++i)
	{
		WellboreMarker* marker = getRepository()->getDataObjectByUuid<WellboreMarker>(rep->WellboreMarker[i]->uuid);
		if (marker == nullptr) {
			marker = new WellboreMarker(rep->WellboreMarker[i]);
			getRepository()->addOrReplaceDataObject(marker);
			if (rep->WellboreMarker[i]->Interpretation != nullptr)
			{
				marker->setBoundaryFeatureInterpretation(getRepository()->getDataObjectByUuid<BoundaryFeatureInterpretation>(rep->WellboreMarker[i]->Interpretation->UUID));
			}
		}
		getRepository()->addRelationship(this, marker);
	}
}

std::vector<WellboreMarker *> WellboreMarkerFrameRepresentation::getWellboreMarkerSet() const
{
	return getRepository()->getTargetObjects<WellboreMarker>(this);
}
