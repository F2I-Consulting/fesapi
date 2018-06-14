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
#include "witsml1_4_1_1/AbstractObject.h"

#include <stdexcept>
#include <string>
#include <sstream>

#include "witsml1_4_1_1/CoordinateReferenceSystem.h"

using namespace std;
using namespace WITSML1_4_1_1_NS;
using namespace gsoap_witsml1_4_1_1;
using namespace epc;

const char* AbstractObject::SCHEMA_VERSION = "1.4.1.1";

void AbstractObject::serializeIntoStream(ostream * stream)
{
	if (!collection)
		throw invalid_argument("The wrapped gsoap proxy must not be null");

	if (!stream)
		throw invalid_argument("The stream where the entity will be stored cannot be null.");

	string xmlTagIncludingNamespace = getXmlNamespace() + ":"+ getXmlTag();

	collection->soap->os = stream;
	( soap_begin_send(collection->soap) || soap_send(collection->soap, collection->soap->prolog ? collection->soap->prolog : "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n") ||
		(collection->soap_serialize(collection->soap), 0) ||
		collection->soap_put(collection->soap, xmlTagIncludingNamespace.c_str(), nullptr) ||
		soap_end_send(collection->soap) );
}

string AbstractObject::getContentType() const
{
	return "application/x-witsml+xml;version=1.4.1.1;type=obj_" + getXmlTag();
}

std::string AbstractObject::getPartNameInEpcDocument() const
{
	return "obj_" + getXmlTag() + "_" + getUuid() + ".xml";
}

string AbstractObject::serializeIntoString()
{
	ostringstream oss;

	serializeIntoStream(&oss);

	return oss.str();
}

vector<Relationship> AbstractObject::getAllEpcRelationships() const
{
	vector<Relationship> result;

	// XML forward relationship
	if (crs)
	{
		Relationship rel(crs->getPartNameInEpcDocument(), "", crs->getUuid());
		rel.setDestinationObjectType();
		result.push_back(rel);
	}

	return result;
}

gsoap_resqml2_0_1::eml20__DataObjectReference* AbstractObject::newResqmlReference() const
{
	ostringstream oss;

	gsoap_resqml2_0_1::eml20__DataObjectReference* result = gsoap_resqml2_0_1::soap_new_eml20__DataObjectReference(collection->soap, 1);
	result->UUID = getUuid();
	result->Title = getTitle();
	result->ContentType = getContentType();

	return result;
}

void AbstractObject::setCoordinateReferenceSystem(CoordinateReferenceSystem* wellCrs)
{
	crs = wellCrs;
	wellCrs->objectsUsingThisCrs.push_back(this);
}

witsml1__cs_USCORElocation* AbstractObject::constructEastingNorthingLocation(
		witsml1__LengthUom uom,
		const double & easting,
		const double & northing,
		CoordinateReferenceSystem* wellCrs)
{
	soap* ctx = collection->soap;

	witsml1__cs_USCORElocation* location = soap_new_witsml1__cs_USCORElocation(ctx, 1);

	if (wellCrs != nullptr)
	{
		location->wellCRS = wellCrs->newReference();
		setCoordinateReferenceSystem(wellCrs);
	}

	location->easting = soap_new_witsml1__lengthMeasure(ctx, 1);
	location->easting->uom = uom;
	location->easting->__item = easting;

	location->northing = soap_new_witsml1__lengthMeasure(ctx, 1);
	location->northing->uom = uom;
	location->northing->__item = northing;

	return location;
}

witsml1__cs_USCORElocation* AbstractObject::constructWestingSouthingLocation(
		witsml1__LengthUom uom,
		const double & westing,
		const double & southing,
		CoordinateReferenceSystem* wellCrs)
{
	soap* ctx = collection->soap;

	witsml1__cs_USCORElocation* location = soap_new_witsml1__cs_USCORElocation(ctx, 1);

	if (wellCrs != nullptr)
	{
		location->wellCRS = wellCrs->newReference();
		setCoordinateReferenceSystem(wellCrs);
	}

	location->westing = soap_new_witsml1__lengthMeasure(ctx, 1);
	location->westing->uom = uom;
	location->westing->__item = westing;

	location->southing = soap_new_witsml1__lengthMeasure(ctx, 1);
	location->southing->uom = uom;
	location->southing->__item = southing;

	return location;
}

witsml1__cs_USCORElocation* AbstractObject::constructProjectedXProjectedYLocation(
		witsml1__LengthUom uom,
		const double & projectedX,
		const double & projectedY,
		CoordinateReferenceSystem* wellCrs)
{
	soap* ctx = collection->soap;

	witsml1__cs_USCORElocation* location = soap_new_witsml1__cs_USCORElocation(ctx, 1);

	if (wellCrs != nullptr)
	{
		location->wellCRS = wellCrs->newReference();
		setCoordinateReferenceSystem(wellCrs);
	}

	location->projectedX = soap_new_witsml1__lengthMeasure(ctx, 1);
	location->projectedX->uom = uom;
	location->projectedX->__item = projectedX;

	location->projectedY = soap_new_witsml1__lengthMeasure(ctx, 1);
	location->projectedY->uom = uom;
	location->projectedY->__item = projectedY;

	return location;
}

witsml1__cs_USCOREcommonData* AbstractObject::newCommonData(
			const std::string & sourceName,
			const time_t & dTimCreation,
			const time_t & dTimLastChange,
			const std::string & comments)
{
	witsml1__cs_USCOREcommonData* commonData = soap_new_witsml1__cs_USCOREcommonData(collection->soap, 1);

	if (!sourceName.empty())
	{
		commonData->sourceName = soap_new_std__string(collection->soap, 1);
		commonData->sourceName->assign(sourceName);
	}
	if (dTimCreation>=0)
	{
		commonData->dTimCreation = (tm *) soap_malloc(collection->soap, sizeof(tm));
		*commonData->dTimCreation = *gmtime(&dTimCreation);
	}
	if (dTimLastChange>=0)
	{
		commonData->dTimLastChange = (tm *)soap_malloc(collection->soap, sizeof(tm));
		*commonData->dTimLastChange = *gmtime(&dTimLastChange);
	}
	if (!comments.empty())
	{
		commonData->comments = soap_new_std__string(collection->soap, 1);
		commonData->comments->assign(comments);
	}

	return commonData;
}

