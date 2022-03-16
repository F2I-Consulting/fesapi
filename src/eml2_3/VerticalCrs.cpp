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
#include "VerticalCrs.h"

#include <stdexcept>

using namespace std;
using namespace EML2_3_NS;
using namespace gsoap_eml2_3;

void VerticalCrs::init(eml23__VerticalCrs* verticalCrs, const std::string& guid, const std::string& title,
	gsoap_eml2_3::eml23__LengthUom verticalUom,
	bool isUpOriented)
{
	verticalCrs->uom = soap_eml23__LengthUom2s(gsoapProxy2_3->soap, verticalUom);
	verticalCrs->Direction = isUpOriented ? eml23__VerticalDirection::up : eml23__VerticalDirection::down;

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "");
}

VerticalCrs::VerticalCrs(COMMON_NS::DataObjectRepository* repo, const std::string& guid, const std::string& title,
	uint64_t verticalEpsgCode,
	gsoap_eml2_3::eml23__LengthUom verticalUom,
	bool isUpOriented)
{
	if (repo == nullptr) {
		throw invalid_argument("The soap context where the local 2d CRS will be instantiated must exist.");
	}

	gsoapProxy2_3 = soap_new_eml23__VerticalCrs(repo->getGsoapContext());
	eml23__VerticalCrs* verticalCrs = static_cast<eml23__VerticalCrs*>(gsoapProxy2_3);
	init(verticalCrs, guid, title, verticalUom, isUpOriented);

	auto* epsgCrs = soap_new_eml23__VerticalEpsgCrs(gsoapProxy2_3->soap);
	epsgCrs->EpsgCode = verticalEpsgCode;
	verticalCrs->AbstractVerticalCrs = epsgCrs;

	repo->addDataObject(this);
}

VerticalCrs::VerticalCrs(COMMON_NS::DataObjectRepository* repo, const std::string& guid, const std::string& title,
	std::string unknownReason,
	gsoap_eml2_3::eml23__LengthUom verticalUom,
	bool isUpOriented)
{
	if (repo == nullptr) {
		throw invalid_argument("The soap context where the local 2d CRS will be instantiated must exist.");
	}

	gsoapProxy2_3 = soap_new_eml23__VerticalCrs(repo->getGsoapContext());
	eml23__VerticalCrs* verticalCrs = static_cast<eml23__VerticalCrs*>(gsoapProxy2_3);
	init(verticalCrs, guid, title, verticalUom, isUpOriented);

	auto* unknownCrs = soap_new_eml23__VerticalUnknownCrs(gsoapProxy2_3->soap);
	unknownCrs->Unknown = unknownReason;
	verticalCrs->AbstractVerticalCrs = unknownCrs;

	repo->addDataObject(this);
}

bool VerticalCrs::isVerticalCrsDefinedWithEpsg() const
{
	return static_cast<gsoap_eml2_3::eml23__VerticalCrs*>(gsoapProxy2_3)->AbstractVerticalCrs->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__VerticalEpsgCrs;
}

bool VerticalCrs::isVerticalCrsUnknown() const
{
	return static_cast<gsoap_eml2_3::eml23__VerticalCrs*>(gsoapProxy2_3)->AbstractVerticalCrs->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__VerticalUnknownCrs;
}

std::string VerticalCrs::getVerticalCrsUnknownReason() const
{
	return static_cast<gsoap_eml2_3::eml23__VerticalUnknownCrs*>(static_cast<gsoap_eml2_3::eml23__VerticalCrs*>(gsoapProxy2_3)->AbstractVerticalCrs)->Unknown;
}

int64_t VerticalCrs::getVerticalCrsEpsgCode() const
{
	return static_cast<gsoap_eml2_3::eml23__VerticalEpsgCrs*>(static_cast<gsoap_eml2_3::eml23__VerticalCrs*>(gsoapProxy2_3)->AbstractVerticalCrs)->EpsgCode;
}
