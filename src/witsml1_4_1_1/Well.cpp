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
#include "witsml1_4_1_1/Well.h"

#include <stdexcept>

#include "tools/GuidTools.h"

#include "witsml1_4_1_1/CoordinateReferenceSystem.h"

using namespace std;
using namespace WITSML1_4_1_1_NS;
using namespace gsoap_witsml1_4_1_1;
using namespace epc;
using namespace COMMON_NS;

const char* Well::XML_TAG = "wells";

Well::Well(soap* soapContext,
			const std::string & guid,
			const std::string & title,
			const std::string & timeZone)
{
	if (soapContext == nullptr) throw invalid_argument("A soap context must exist.");
	if (title.empty()) throw invalid_argument("A well must have a name.");
	if (timeZone.empty()) throw invalid_argument("A well must have a timezone.");

	collection = soap_new_witsml1__obj_USCOREwells(soapContext, 1);
	static_cast<_witsml1__wells*>(collection)->version = SCHEMA_VERSION;

	witsml1__obj_USCOREwell* well = soap_new_witsml1__obj_USCOREwell(collection->soap, 1);
	static_cast<_witsml1__wells*>(collection)->well.push_back(well);

	well->uid = soap_new_std__string(collection->soap, 1);
	if (guid.empty()) {
		well->uid->assign(GuidTools::generateUidAsString());
	} else {
		well->uid->assign(guid);
	}

	well->name = title;

	__witsml1__obj_USCOREwell_sequence* wellSequence = soap_new___witsml1__obj_USCOREwell_sequence(collection->soap, 1);
	wellSequence->timeZone = timeZone;
	well->__obj_USCOREwell_sequence = wellSequence;
}

Well::Well(soap* soapContext,
		const std::string & guid,
		const std::string & title,
		const std::string & timeZone,
		const std::string & operator_,
		witsml1__WellStatus statusWell,
		witsml1__WellPurpose purposeWell,
		witsml1__WellFluid fluidWell,
		witsml1__WellDirection directionWell,
		const time_t & dTimSpud,
		const std::string & sourceName,
		const time_t & dTimCreation,
		const time_t & dTimLastChange,
		const std::string & comments
	)
{
	if (soapContext == nullptr) throw invalid_argument("A soap context must exist.");
	if (title.empty()) throw invalid_argument("A well must have a name.");
	if (timeZone.empty()) throw invalid_argument("A well must have a timezone.");
	if (operator_.empty()) throw invalid_argument("You must set a non empty operator.");

	collection = soap_new_witsml1__obj_USCOREwells(soapContext, 1);
	static_cast<_witsml1__wells*>(collection)->version = SCHEMA_VERSION;

	witsml1__obj_USCOREwell* well = soap_new_witsml1__obj_USCOREwell(collection->soap, 1);
	static_cast<_witsml1__wells*>(collection)->well.push_back(well);

	well->uid = soap_new_std__string(collection->soap, 1);
	if (guid.empty()) {
		well->uid->assign(GuidTools::generateUidAsString());
	} else {
		well->uid->assign(guid);
	}

	well->name = title;

	__witsml1__obj_USCOREwell_sequence* wellSequence = soap_new___witsml1__obj_USCOREwell_sequence(collection->soap, 1);
	wellSequence->timeZone = timeZone;

	wellSequence->operator_ = soap_new_std__string(collection->soap, 1);
	wellSequence->operator_->assign(operator_); 

	wellSequence->statusWell = (witsml1__WellStatus *) soap_malloc(collection->soap, sizeof(witsml1__WellStatus));
	*wellSequence->statusWell = statusWell;

	wellSequence->purposeWell = (witsml1__WellPurpose *) soap_malloc(collection->soap, sizeof(witsml1__WellPurpose));
	*wellSequence->purposeWell = purposeWell;

	wellSequence->fluidWell = (witsml1__WellFluid *) soap_malloc(collection->soap, sizeof(witsml1__WellFluid));
	*wellSequence->fluidWell = fluidWell;

	wellSequence->directionWell = (witsml1__WellDirection *) soap_malloc(collection->soap, sizeof(witsml1__WellDirection));
	*wellSequence->directionWell = directionWell;

	wellSequence->dTimSpud = (tm *) soap_malloc(collection->soap, sizeof(tm));
	*wellSequence->dTimSpud = *gmtime(&dTimSpud);

	well->__obj_USCOREwell_sequence = wellSequence;

	// create the commonData attribute, if necessary
	if (!sourceName.empty() || dTimCreation>=0 || dTimLastChange>=0 || !comments.empty())
	{
		well->commonData = newCommonData(sourceName,
			dTimCreation,
			dTimLastChange,
			comments);
	}
}

Wellbore* Well::createWellbore(
	const std::string & guid,
	const std::string & title)
{
	Wellbore* result = new Wellbore(this, guid, title);
	if (getEpcDocument() != nullptr)
	{
		try {
			getEpcDocument()->addGsoapProxy(result);
		}
		catch (const exception & e)
		{
			std::cerr << e.what() << endl;
			std::cerr << "The proxy is going to be deleted but deletion is not yet guaranteed. You should close your application." << endl;
			delete result;
			throw;
		}
	}
	return result;
}

Wellbore* Well::createWellbore(
	const std::string & guid,
	const std::string & title,
	gsoap_witsml1_4_1_1::witsml1__WellStatus statusWellbore,
	const bool & isActive,
	gsoap_witsml1_4_1_1::witsml1__WellPurpose purposeWellbore,
	gsoap_witsml1_4_1_1::witsml1__WellboreType typeWellbore,
	const bool & achievedTD,
	const std::string & sourceName,
	const time_t & dTimCreation,
	const time_t & dTimLastChange,
	const std::string & comments)
{
	Wellbore* result = new Wellbore(this, guid, title, statusWellbore, isActive, purposeWellbore, typeWellbore, achievedTD, sourceName, dTimCreation, dTimLastChange, comments);
	if (getEpcDocument() != nullptr)
	{
		try {
			getEpcDocument()->addGsoapProxy(result);
		}
		catch (const exception & e)
		{
			std::cerr << e.what() << endl;
			std::cerr << "The proxy is going to be deleted but deletion is not yet guaranteed. You should close your application." << endl;
			delete result;
			throw;
		}
	}
	return result;
}

void Well::setOperator(const string & operator_) 
{
	if (operator_.empty()) throw invalid_argument("You must set a non empty operator.");

	static_cast<_witsml1__wells*>(collection)->well[0]->__obj_USCOREwell_sequence->operator_ = soap_new_std__string(collection->soap, 1);
	static_cast<_witsml1__wells*>(collection)->well[0]->__obj_USCOREwell_sequence->operator_->assign(operator_); 
}

double Well::getWellHeadEastingLocationValue()
{
	witsml1__obj_USCOREwell* well = static_cast<_witsml1__wells*>(collection)->well[0];
	if (well->__obj_USCOREwell_sequence->wellLocation.size() > 0)
	{
		if (well->__obj_USCOREwell_sequence->wellLocation[0]->easting)
		{
			return well->__obj_USCOREwell_sequence->wellLocation[0]->easting->__item;
		}
		else if (well->__obj_USCOREwell_sequence->wellLocation[0]->westing)
		{
			return - well->__obj_USCOREwell_sequence->wellLocation[0]->westing->__item;
		}
	}

	return std::numeric_limits<double>::quiet_NaN();
}

gsoap_witsml1_4_1_1::witsml1__LengthUom Well::getWellHeadEastingLocationUom()
{
	witsml1__obj_USCOREwell* well = static_cast<_witsml1__wells*>(collection)->well[0];
	if (well->__obj_USCOREwell_sequence->wellLocation.size() > 0)
	{
		if (well->__obj_USCOREwell_sequence->wellLocation[0]->easting)
		{
			return well->__obj_USCOREwell_sequence->wellLocation[0]->easting->uom;
		}
		else if (well->__obj_USCOREwell_sequence->wellLocation[0]->westing)
		{
			return well->__obj_USCOREwell_sequence->wellLocation[0]->westing->uom;
		}
	}

	return witsml1__LengthUom__m;
}

double Well::getWellHeadNorthingLocationValue()
{
	witsml1__obj_USCOREwell* well = static_cast<_witsml1__wells*>(collection)->well[0];
	if (well->__obj_USCOREwell_sequence->wellLocation.size() > 0)
	{
		if (well->__obj_USCOREwell_sequence->wellLocation[0]->northing)
		{
			return well->__obj_USCOREwell_sequence->wellLocation[0]->northing->__item;
		}
		else if (well->__obj_USCOREwell_sequence->wellLocation[0]->southing)
		{
			return - well->__obj_USCOREwell_sequence->wellLocation[0]->southing->__item;
		}
	}

	return std::numeric_limits<double>::quiet_NaN();
}

gsoap_witsml1_4_1_1::witsml1__LengthUom Well::getWellHeadNorthingLocationUom()
{
	witsml1__obj_USCOREwell* well = static_cast<_witsml1__wells*>(collection)->well[0];
	if (well->__obj_USCOREwell_sequence->wellLocation.size() > 0)
	{
		if (well->__obj_USCOREwell_sequence->wellLocation[0]->northing)
		{
			return well->__obj_USCOREwell_sequence->wellLocation[0]->northing->uom;
		}
		else if (well->__obj_USCOREwell_sequence->wellLocation[0]->southing)
		{
			return well->__obj_USCOREwell_sequence->wellLocation[0]->southing->uom;
		}
	}

	return witsml1__LengthUom__m;
}

void Well::setEastingNorthingLocation(
	witsml1__LengthUom uom,
	const double & easting,
	const double & northing,
	CoordinateReferenceSystem* wellCrs)
{
	witsml1__cs_USCORElocation* location = constructEastingNorthingLocation(uom, easting, northing, wellCrs);
	if (static_cast<_witsml1__wells*>(collection)->well[0]->__obj_USCOREwell_sequence == nullptr)
	{
		static_cast<_witsml1__wells*>(collection)->well[0]->__obj_USCOREwell_sequence = soap_new___witsml1__obj_USCOREwell_sequence(collection->soap, 1);
	}
	static_cast<_witsml1__wells*>(collection)->well[0]->__obj_USCOREwell_sequence->wellLocation.push_back(location);
}

void Well::setWestingSouthingLocation(
	witsml1__LengthUom uom,
	const double & westing,
	const double & southing,
	CoordinateReferenceSystem* wellCrs)
{
	witsml1__cs_USCORElocation* location = constructWestingSouthingLocation(uom, westing, southing, wellCrs);
	if (static_cast<_witsml1__wells*>(collection)->well[0]->__obj_USCOREwell_sequence == nullptr)
	{
		static_cast<_witsml1__wells*>(collection)->well[0]->__obj_USCOREwell_sequence = soap_new___witsml1__obj_USCOREwell_sequence(collection->soap, 1);
	}
	static_cast<_witsml1__wells*>(collection)->well[0]->__obj_USCOREwell_sequence->wellLocation.push_back(location);
}

void Well::setProjectedXProjectedYLocation(
	gsoap_witsml1_4_1_1::witsml1__LengthUom uom,
	const double & projectedX,
	const double & projectedY,
	CoordinateReferenceSystem* wellCrs)
{
	witsml1__cs_USCORElocation* location = constructProjectedXProjectedYLocation(uom, projectedX, projectedY, wellCrs);
	if (static_cast<_witsml1__wells*>(collection)->well[0]->__obj_USCOREwell_sequence == nullptr)
	{
		static_cast<_witsml1__wells*>(collection)->well[0]->__obj_USCOREwell_sequence = soap_new___witsml1__obj_USCOREwell_sequence(collection->soap, 1);
	}
	static_cast<_witsml1__wells*>(collection)->well[0]->__obj_USCOREwell_sequence->wellLocation.push_back(location);
}

void Well::pushBackDatum(
	const std::string & guid, 
	const std::string & title,
	gsoap_witsml1_4_1_1::witsml1__ElevCodeEnum code,
	const unsigned int & datumIndex,
	gsoap_witsml1_4_1_1::witsml1__WellVerticalCoordinateUom elevationUnit,
	const double & elevation)
{
	witsml1__cs_USCOREwellDatum* wellDatum = soap_new_witsml1__cs_USCOREwellDatum(collection->soap,1);
	if (guid.empty()) {
		wellDatum->uid.assign(GuidTools::generateUidAsString());
	} else {
		wellDatum->uid.assign(guid);
	}
	wellDatum->name = title;

	if (static_cast<_witsml1__wells*>(collection)->well[0]->__obj_USCOREwell_sequence == nullptr)
	{
		static_cast<_witsml1__wells*>(collection)->well[0]->__obj_USCOREwell_sequence = soap_new___witsml1__obj_USCOREwell_sequence(collection->soap, 1);
	}
	static_cast<_witsml1__wells*>(collection)->well[0]->__obj_USCOREwell_sequence->wellDatum.push_back(wellDatum);

	wellDatum->code = (witsml1__ElevCodeEnum *)soap_malloc(collection->soap, sizeof(witsml1__ElevCodeEnum));
	*wellDatum->code = code;

	wellDatum->elevation = soap_new_witsml1__wellElevationCoord(collection->soap,1);
	wellDatum->elevation->uom = elevationUnit;
	
	gsoap_witsml1_4_1_1::witsml1__cs_USCOREwellDatum* datum = getDatum(datumIndex);

	wellDatum->elevation->datum = soap_new_std__string(collection->soap, 1);
	wellDatum->elevation->datum->assign(datum->uid);

	wellDatum->elevation->__item = elevation;
}

void Well::pushBackDatum(
	const std::string & guid, 
	const std::string & title,
	gsoap_witsml1_4_1_1::witsml1__ElevCodeEnum code,
	const std::string & refNamingSystem,
	const std::string & refCode,
	const std::string & refName)
{
	witsml1__cs_USCOREwellDatum* wellDatum = soap_new_witsml1__cs_USCOREwellDatum(collection->soap,1);
	if (guid.empty()) {
		wellDatum->uid.assign(GuidTools::generateUidAsString());
	} else {
		wellDatum->uid.assign(guid);
	}
	wellDatum->name = title;

	if (static_cast<_witsml1__wells*>(collection)->well[0]->__obj_USCOREwell_sequence == nullptr)
	{
		static_cast<_witsml1__wells*>(collection)->well[0]->__obj_USCOREwell_sequence = soap_new___witsml1__obj_USCOREwell_sequence(collection->soap, 1);
	}
	static_cast<_witsml1__wells*>(collection)->well[0]->__obj_USCOREwell_sequence->wellDatum.push_back(wellDatum);

	wellDatum->code = (witsml1__ElevCodeEnum *)soap_malloc(collection->soap, sizeof(witsml1__ElevCodeEnum));
	*wellDatum->code = code;

	// 1 means that in the choice between datumName and datumCRS, we choose the first one: datumName 
	// (0 means that the choice is optionnal, see GSsoap documentation http://www.cs.fsu.edu/~engelen/soap.html chapter 11.7)
	wellDatum->__union_cs_USCOREwellDatum = 1;
	wellDatum->union_cs_USCOREwellDatum.datumName = soap_new_witsml1__wellKnownNameStruct(collection->soap, 1);
	wellDatum->union_cs_USCOREwellDatum.datumName->__item = refName;
	wellDatum->union_cs_USCOREwellDatum.datumName->namingSystem = refNamingSystem;
	wellDatum->union_cs_USCOREwellDatum.datumName->code = soap_new_std__string(collection->soap,1);
	wellDatum->union_cs_USCOREwellDatum.datumName->code->assign(refCode);
}

unsigned int Well::getDatumCount() const
{
	return static_cast<_witsml1__wells*>(collection)->well[0]->__obj_USCOREwell_sequence->wellDatum.size();
}

witsml1__cs_USCOREwellDatum* Well::getDatum(const unsigned int & index) const
{
	return static_cast<_witsml1__wells*>(collection)->well[0]->__obj_USCOREwell_sequence->wellDatum[index];
}

gsoap_witsml1_4_1_1::witsml1__cs_USCOREwellDatum* Well::getDatum(const std::string & uid) const
{
	for (unsigned int i = 0; i < static_cast<_witsml1__wells*>(collection)->well[0]->__obj_USCOREwell_sequence->wellDatum.size(); ++i)
		if (static_cast<_witsml1__wells*>(collection)->well[0]->__obj_USCOREwell_sequence->wellDatum[i]->uid == uid)
			return static_cast<_witsml1__wells*>(collection)->well[0]->__obj_USCOREwell_sequence->wellDatum[i];

	return nullptr;
}

void Well::importRelationshipSetFromEpc(COMMON_NS::EpcDocument* epcDoc)
{
	witsml1__obj_USCOREwell* well = static_cast<_witsml1__wells*>(collection)->well[0];
	for (unsigned int i = 0; i < well->__obj_USCOREwell_sequence->wellLocation.size(); ++i)
	{
		if (well->__obj_USCOREwell_sequence->wellLocation[i]->wellCRS)
		{
			updateXml = false;
			setCoordinateReferenceSystem(static_cast<CoordinateReferenceSystem*>(epcDoc->getWitsmlAbstractObjectByUuid(
				*well->__obj_USCOREwell_sequence->wellLocation[i]->wellCRS->uidRef)));
			updateXml = true;
			break;
		}
	}
}

vector<Relationship> Well::getAllEpcRelationships() const
{
	vector<Relationship> result = AbstractObject::getAllEpcRelationships();

	// XML backward relationship
	std::vector<Wellbore*> wellboreSet = getWellbores();
	for (unsigned int j = 0; j < wellboreSet.size(); ++j)
	{
		RESQML2_0_1_NS::WellboreFeature* resqmlWellboreFeature = wellboreSet[j]->getResqmlWellboreFeature();
		if (resqmlWellboreFeature)
		{
			Relationship rel(resqmlWellboreFeature->getPartNameInEpcDocument(), "", resqmlWellboreFeature->getUuid());
			rel.setSourceObjectType();
			result.push_back(rel);
		}

		Relationship relWellbore(wellboreSet[j]->getPartNameInEpcDocument(), "", wellboreSet[j]->getUuid());
		relWellbore.setSourceObjectType();
		result.push_back(relWellbore);

		std::vector<Trajectory*> trajSet = wellboreSet[j]->getTrajectories();
		for (unsigned int t = 0; t < trajSet.size(); ++t)
		{
			Relationship relTrajectory(trajSet[t]->getPartNameInEpcDocument(), "", trajSet[t]->getUuid());
			relTrajectory.setSourceObjectType();
			result.push_back(relTrajectory);
		}
	}

	return result;
}

