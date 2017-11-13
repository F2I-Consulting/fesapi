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
#include "resqml2_0_1/WellboreMarkerFrameRepresentation.h"

#include <stdexcept>

#if defined(__gnu_linux__) || defined(__APPLE__)
#include <unistd.h>
#include <pwd.h>
#endif

#include "hdf5.h"

#include "resqml2_0_1/WellboreInterpretation.h"
#include "resqml2_0_1/WellboreTrajectoryRepresentation.h"
#include "resqml2/AbstractLocal3dCrs.h"
#include "tools/GuidTools.h"
#include "resqml2_0_1/WellboreMarker.h"
#include "resqml2_0_1/StratigraphicOccurrenceInterpretation.h"
#include "resqml2_0_1/HorizonInterpretation.h"
#include "common/AbstractHdfProxy.h"

#include "witsml1_4_1_1/FormationMarker.h"

using namespace std;
using namespace resqml2_0_1;
using namespace gsoap_resqml2_0_1;
using namespace epc;

const char* WellboreMarkerFrameRepresentation::XML_TAG = "WellboreMarkerFrameRepresentation";

WellboreMarkerFrameRepresentation::WellboreMarkerFrameRepresentation(WellboreInterpretation* interp, const std::string & guid, const std::string & title, WellboreTrajectoryRepresentation * traj):
	WellboreFrameRepresentation(interp, nullptr), stratigraphicOccurrenceInterpretation(nullptr)
{
	gsoapProxy2_0_1 = soap_new_resqml2__obj_USCOREWellboreMarkerFrameRepresentation(interp->getGsoapContext(), 1);	
	_resqml2__WellboreMarkerFrameRepresentation* frame = static_cast<_resqml2__WellboreMarkerFrameRepresentation*>(gsoapProxy2_0_1);

	setInterpretation(interp);

	frame->Trajectory = traj->newResqmlReference();
	trajectory = traj;
	traj->addWellboreFrameRepresentation(this);

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "", "");
}

WellboreMarkerFrameRepresentation::~WellboreMarkerFrameRepresentation()
{
	for (unsigned int i = 0; i < markerSet.size(); ++i)
		delete markerSet[i];
}

WellboreMarker* WellboreMarkerFrameRepresentation::pushBackNewWellboreMarker(const std::string & guid, const std::string & title)
{
	WellboreMarker* marker = new WellboreMarker(this, guid, title);
	markerSet.push_back(marker);

	_resqml2__WellboreMarkerFrameRepresentation* frame = static_cast<_resqml2__WellboreMarkerFrameRepresentation*>(gsoapProxy2_0_1);
	frame->WellboreMarker.push_back(static_cast<resqml2__WellboreMarker*>(marker->getGsoapProxy()));	

	return marker;
}

WellboreMarker* WellboreMarkerFrameRepresentation::pushBackNewWellboreMarker(const std::string & guid, const std::string & title, const gsoap_resqml2_0_1::resqml2__GeologicBoundaryKind & geologicBoundaryKind)
{
	WellboreMarker* marker = new WellboreMarker(this, guid, title, geologicBoundaryKind);
	markerSet.push_back(marker);

	_resqml2__WellboreMarkerFrameRepresentation* frame = static_cast<_resqml2__WellboreMarkerFrameRepresentation*>(gsoapProxy2_0_1);
	frame->WellboreMarker.push_back(static_cast<resqml2__WellboreMarker*>(marker->getGsoapProxy()));	

	return marker;
}

unsigned int WellboreMarkerFrameRepresentation::getWellboreMarkerCount()
{
	return static_cast<_resqml2__WellboreMarkerFrameRepresentation*>(gsoapProxy2_0_1)->WellboreMarker.size();
}

void WellboreMarkerFrameRepresentation::setStratigraphicOccurrenceInterpretation( StratigraphicOccurrenceInterpretation * stratiOccurenceInterp)
{
	// EPC
	stratigraphicOccurrenceInterpretation = stratiOccurenceInterp;
	stratiOccurenceInterp->wellboreMarkerFrameRepresentationSet.push_back(this);

	// XML
	if (updateXml)
	{
		_resqml2__WellboreMarkerFrameRepresentation* frame = static_cast<_resqml2__WellboreMarkerFrameRepresentation*>(gsoapProxy2_0_1);
		frame->IntervalStratigraphiUnits = soap_new_resqml2__IntervalStratigraphicUnits(frame->soap, 1);
		frame->IntervalStratigraphiUnits->StratigraphicOrganization = stratiOccurenceInterp->newResqmlReference();
	}
}

void WellboreMarkerFrameRepresentation::setIntervalStratigraphicUnits(unsigned int * stratiUnitIndices, const unsigned int & nullValue, StratigraphicOccurrenceInterpretation* stratiOccurenceInterp)
{
	if (stratiUnitIndices == nullptr)
		throw invalid_argument("The strati unit indices cannot be null.");

	setStratigraphicOccurrenceInterpretation(stratiOccurenceInterp);

	_resqml2__WellboreMarkerFrameRepresentation* frame = static_cast<_resqml2__WellboreMarkerFrameRepresentation*>(gsoapProxy2_0_1);

	resqml2__IntegerHdf5Array* xmlDataset = soap_new_resqml2__IntegerHdf5Array(frame->soap, 1);
	xmlDataset->NullValue = nullValue;
	xmlDataset->Values = soap_new_eml20__Hdf5Dataset(gsoapProxy2_0_1->soap, 1);
	xmlDataset->Values->HdfProxy = hdfProxy->newResqmlReference();
	xmlDataset->Values->PathInHdfFile = "/RESQML/" + frame->uuid + "/IntervalStratigraphicUnits";
	frame->IntervalStratigraphiUnits->UnitIndices = xmlDataset;

	// ************ HDF *************
	hsize_t dim = frame->NodeCount - 1;
	hdfProxy->writeArrayNd(frame->uuid, "IntervalStratigraphicUnits", H5T_NATIVE_UINT, stratiUnitIndices, &dim, 1);
}

void WellboreMarkerFrameRepresentation::setWitsmlFormationMarker(const unsigned int & resqmlMarkerIndex, witsml1_4_1_1::FormationMarker * witsmlFormationMarker)
{
	_resqml2__WellboreMarkerFrameRepresentation* frame = static_cast<_resqml2__WellboreMarkerFrameRepresentation*>(gsoapProxy2_0_1);
	if (frame->WellboreMarker.size() <= resqmlMarkerIndex)
		throw out_of_range("The marker index is not valid");

	for (unsigned int i = witsmlFormationMarkerSet.size(); i < resqmlMarkerIndex+1; ++i)
		witsmlFormationMarkerSet.push_back(nullptr);

	witsmlFormationMarkerSet[resqmlMarkerIndex] = witsmlFormationMarker;
	witsmlFormationMarker->resqmlWellboreMarkerFrameRepresentation = this;

	if (updateXml)
		frame->WellboreMarker[resqmlMarkerIndex]->WitsmlFormationMarker = witsmlFormationMarker->newResqmlReference();
}

vector<Relationship> WellboreMarkerFrameRepresentation::getAllEpcRelationships() const
{
	_resqml2__WellboreMarkerFrameRepresentation* frame = static_cast<_resqml2__WellboreMarkerFrameRepresentation*>(gsoapProxy2_0_1);
	
	vector<Relationship> result = WellboreFrameRepresentation::getAllEpcRelationships();

	// XML forward relationship
	if (stratigraphicOccurrenceInterpretation != nullptr)
	{
		Relationship relStratiRank(stratigraphicOccurrenceInterpretation->getPartNameInEpcDocument(), "", stratigraphicOccurrenceInterpretation->getUuid());
		relStratiRank.setDestinationObjectType();
		result.push_back(relStratiRank);
	}

	for (unsigned int i = 0; i < markerSet.size(); ++i)
	{
		if (markerSet[i]->getBoundaryFeatureInterpretation())
		{
			Relationship relBoundaryFeature(markerSet[i]->getBoundaryFeatureInterpretation()->getPartNameInEpcDocument(), "", markerSet[i]->getBoundaryFeatureInterpretation()->getUuid());
			relBoundaryFeature.setDestinationObjectType();
			result.push_back(relBoundaryFeature);
		}
	}

	int firstNonNullWitsmlMarker = -1;
	for (unsigned int i = 0; i < witsmlFormationMarkerSet.size() && firstNonNullWitsmlMarker < 0; ++i)
	{
		if (witsmlFormationMarkerSet[i])
			firstNonNullWitsmlMarker = i;
	}
	if (firstNonNullWitsmlMarker>=0)
	{
		Relationship relWitsml(witsmlFormationMarkerSet[firstNonNullWitsmlMarker]->getPartNameInEpcDocument(), "", witsmlFormationMarkerSet[firstNonNullWitsmlMarker]->getUuid());
		relWitsml.setDestinationObjectType();
		result.push_back(relWitsml);
	}

	return result;
}

void WellboreMarkerFrameRepresentation::importRelationshipSetFromEpc(common::EpcDocument* epcDoc)
{
	WellboreFrameRepresentation::importRelationshipSetFromEpc(epcDoc);

	updateXml = false;

	_resqml2__WellboreMarkerFrameRepresentation* rep = static_cast<_resqml2__WellboreMarkerFrameRepresentation*>(gsoapProxy2_0_1);

	updateXml = false;

	if (rep->IntervalStratigraphiUnits != nullptr)
	{
		setStratigraphicOccurrenceInterpretation(epcDoc->getResqmlAbstractObjectByUuid<resqml2_0_1::StratigraphicOccurrenceInterpretation>(rep->IntervalStratigraphiUnits->StratigraphicOrganization->UUID));
	}

	updateXml = true;

	for (unsigned int i = 0; i < rep->WellboreMarker.size(); ++i)
	{
		if (rep->WellboreMarker[i]->WitsmlFormationMarker)
		{
			witsml1_4_1_1::FormationMarker* tmp = static_cast<witsml1_4_1_1::FormationMarker*>(epcDoc->getWitsmlAbstractObjectByUuid(rep->WellboreMarker[i]->WitsmlFormationMarker->UUID));
			if (tmp)
			{
				updateXml = false;
				setWitsmlFormationMarker(i, tmp);
				updateXml = true;
			}
		}

		WellboreMarker* marker = new WellboreMarker(rep->WellboreMarker[i], this);
		if (rep->WellboreMarker[i]->Interpretation)
		{
			marker->setBoundaryFeatureInterpretation(static_cast<BoundaryFeatureInterpretation*>(epcDoc->getResqmlAbstractObjectByUuid(rep->WellboreMarker[i]->Interpretation->UUID)));
		}
		markerSet.push_back(marker);
	}

	updateXml = true;
}
