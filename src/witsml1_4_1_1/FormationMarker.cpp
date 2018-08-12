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
#include "witsml1_4_1_1/FormationMarker.h"

#include <stdexcept>

#include "tools/GuidTools.h"
#include "witsml1_4_1_1/Well.h"

using namespace std;
using namespace WITSML1_4_1_1_NS;
using namespace gsoap_witsml1_4_1_1;
using namespace epc;

const char* FormationMarker::XML_TAG = "formationMarkers";

FormationMarker::FormationMarker(
	Wellbore* witsmlWellbore,
	const std::string & guid,
	const std::string & title,
	const unsigned int & mdDatumIndex,
	gsoap_witsml1_4_1_1::witsml1__MeasuredDepthUom mdUom,
	const double & mdTopSample):resqmlWellboreMarkerFrameRepresentation(nullptr)
{
	if (witsmlWellbore == nullptr) throw invalid_argument("A formation marker must be associated to a wellbore.");
	if (title.empty()) throw invalid_argument("A formation marker must have a name.");

	collection = soap_new_witsml1__obj_USCOREformationMarkers(witsmlWellbore->getGSoapContext(), 1);	
	static_cast<_witsml1__formationMarkers*>(collection)->version = SCHEMA_VERSION;

	witsml1__obj_USCOREformationMarker* fm = soap_new_witsml1__obj_USCOREformationMarker(collection->soap, 1);
	static_cast<_witsml1__formationMarkers*>(collection)->formationMarker.push_back(fm);

	setWellbore(witsmlWellbore);

	fm->uid = soap_new_std__string(collection->soap, 1);
	if (guid.empty()) {
		fm->uid->assign(GuidTools::generateUidAsString());
	} else {
		fm->uid->assign(guid);
	}

	fm->name = title;

	__witsml1__obj_USCOREformationMarker_sequence* fmSequence = soap_new___witsml1__obj_USCOREformationMarker_sequence(collection->soap, 1);
	// setting up mdTopSample with uom and datum (if exists)
	fmSequence->mdTopSample = soap_new_witsml1__measuredDepthCoord(collection->soap, 1);
	fmSequence->mdTopSample->uom = mdUom;
	fmSequence->mdTopSample->__item = mdTopSample;
	fmSequence->mdTopSample->datum = soap_new_std__string(collection->soap, 1);
	fmSequence->mdTopSample->datum->assign(getWellbore()->getWell()->getDatum(mdDatumIndex)->uid);
	fm->__obj_USCOREformationMarker_sequence = fmSequence;
}

FormationMarker::FormationMarker(
	Wellbore* witsmlWellbore,
	const std::string & guid,
	const std::string & title,
	const unsigned int & mdDatumIndex,
	gsoap_witsml1_4_1_1::witsml1__MeasuredDepthUom mdUom,
	const double & mdTopSample,
	const unsigned int & tvdDatumIndex,
	gsoap_witsml1_4_1_1::witsml1__WellVerticalCoordinateUom tvdUom,
	const double & tvdTopSample,
	gsoap_witsml1_4_1_1::witsml1__PlaneAngleUom dipUom,
	const double & dip,
	gsoap_witsml1_4_1_1::witsml1__PlaneAngleUom dipDirectionUom,
	const double & dipDirection,
	const std::string & sourceName,
	const time_t & dTimCreation,
	const time_t & dTimLastChange,
	const std::string & comments
	):resqmlWellboreMarkerFrameRepresentation(nullptr)
{
	if (witsmlWellbore == nullptr) throw invalid_argument("A trajectory must be associated to a well.");
	if (title.empty()) throw invalid_argument("A trajectory must have a name.");

	collection = soap_new_witsml1__obj_USCOREformationMarkers(witsmlWellbore->getGSoapContext(), 1);	
	static_cast<_witsml1__formationMarkers*>(collection)->version = SCHEMA_VERSION;

	witsml1__obj_USCOREformationMarker* fm = soap_new_witsml1__obj_USCOREformationMarker(collection->soap, 1);
	static_cast<_witsml1__formationMarkers*>(collection)->formationMarker.push_back(fm);

	setWellbore(witsmlWellbore);

	fm->uid = soap_new_std__string(collection->soap, 1);
	if (guid.empty()) {
		fm->uid->assign(GuidTools::generateUidAsString());
	} else {
		fm->uid->assign(guid);
	}

	fm->name = title;

	__witsml1__obj_USCOREformationMarker_sequence* fmSequence = soap_new___witsml1__obj_USCOREformationMarker_sequence(collection->soap, 1);
	// setting up mdTopSample with uom and datum (if exists)
	fmSequence->mdTopSample = soap_new_witsml1__measuredDepthCoord(collection->soap, 1);
	fmSequence->mdTopSample->uom = mdUom;
	fmSequence->mdTopSample->__item = mdTopSample;
	fmSequence->mdTopSample->datum = soap_new_std__string(collection->soap, 1);
	fmSequence->mdTopSample->datum->assign(getWellbore()->getWell()->getDatum(mdDatumIndex)->uid);
	fm->__obj_USCOREformationMarker_sequence = fmSequence;

	fmSequence->tvdTopSample = soap_new_witsml1__wellVerticalDepthCoord(collection->soap, 1);
	fmSequence->tvdTopSample->uom = tvdUom;
	fmSequence->tvdTopSample->__item = tvdTopSample;
	fmSequence->tvdTopSample->datum = soap_new_std__string(collection->soap, 1);
	fmSequence->tvdTopSample->datum->assign(getWellbore()->getWell()->getDatum(tvdDatumIndex)->uid);

	// setting up dip and dipDirection if not NaN
	if (dip == dip)
	{
		fmSequence->dip = soap_new_witsml1__planeAngleMeasure(collection->soap, 1);
		fmSequence->dip->uom = dipUom;
		fmSequence->dip->__item = dip;
	}
	if (dipDirection == dipDirection)
	{
		fmSequence->dipDirection = soap_new_witsml1__planeAngleMeasure(collection->soap, 1);
		fmSequence->dipDirection->uom = dipDirectionUom;
		fmSequence->dipDirection->__item = dip;
	}

	fm->__obj_USCOREformationMarker_sequence = fmSequence;

	// create the commonData attribute, if necessary
	if (!sourceName.empty() || dTimCreation>=0 || dTimLastChange>=0 || !comments.empty())
	{
		fm->commonData = newCommonData(sourceName,
			dTimCreation,
			dTimLastChange,
			comments);
	}
}

void FormationMarker::setWellbore(Wellbore* witsmlWellbore)
{
	wellbore = witsmlWellbore;
	witsmlWellbore->formationMarkerSet.push_back(this);

	if (updateXml)
	{
		witsml1__obj_USCOREformationMarker* fm = static_cast<_witsml1__formationMarkers*>(collection)->formationMarker[0];
		fm->nameWellbore = witsmlWellbore->getTitle();
		fm->uidWellbore = soap_new_std__string(collection->soap, 1);
		fm->uidWellbore->assign(witsmlWellbore->getUuid());

		fm->nameWell = witsmlWellbore->getWell()->getTitle();
		fm->uidWell = soap_new_std__string(collection->soap, 1);
		fm->uidWell->assign(witsmlWellbore->getWell()->getUuid());
	}
}

void FormationMarker::importRelationshipSetFromEpc(COMMON_NS::EpcDocument* epcDoc)
{
	witsml1__obj_USCOREformationMarker* fm = static_cast<_witsml1__formationMarkers*>(collection)->formationMarker[0];
	if (fm && fm->uidWellbore)
	{
		updateXml = false;
		setWellbore(static_cast<Wellbore*>(epcDoc->getWitsmlAbstractObjectByUuid(*fm->uidWellbore)));
		updateXml = true;
	}
}

vector<Relationship> FormationMarker::getAllEpcRelationships() const
{
	vector<Relationship> result = AbstractObject::getAllEpcRelationships();

	// XML forward relationship
	Relationship relWellbore(wellbore->getPartNameInEpcDocument(), "", wellbore->getUuid());
	relWellbore.setDestinationObjectType();
	result.push_back(relWellbore);
		
	Relationship relWell(wellbore->getWell()->getPartNameInEpcDocument(), "", wellbore->getWell()->getUuid());
	relWell.setDestinationObjectType();
	result.push_back(relWell);

	// XML backward relationship
	if (resqmlWellboreMarkerFrameRepresentation)
	{
		Relationship rel(resqmlWellboreMarkerFrameRepresentation->getPartNameInEpcDocument(), "", resqmlWellboreMarkerFrameRepresentation->getUuid());
		rel.setSourceObjectType();
		result.push_back(rel);
	}

	return result;
}

