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
#include "witsml1_4_1_1/FormationMarker.h"

#include <stdexcept>

#include "tools/GuidTools.h"
#include "witsml1_4_1_1/Well.h"

using namespace std;
using namespace witsml1_4_1_1;
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
		fm->uid->assign(tools::GuidTools::generateUidAsString());
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
		fm->uid->assign(tools::GuidTools::generateUidAsString());
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

void FormationMarker::importRelationshipSetFromEpc(common::EpcDocument* epcDoc)
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
