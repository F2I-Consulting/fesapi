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
#include "EnumStringMapper.h"

#include "../proxies/gsoap_resqml2_0_1H.h"
#include "../proxies/gsoap_eml2_3H.h"

using namespace COMMON_NS;

EnumStringMapper::EnumStringMapper()
{
	gsoapContext = soap_new2(SOAP_XML_STRICT | SOAP_C_UTFSTRING | SOAP_XML_IGNORENS, SOAP_XML_TREE | SOAP_XML_INDENT | SOAP_XML_CANONICAL | SOAP_C_UTFSTRING);
}

EnumStringMapper::~EnumStringMapper()
{
	soap_destroy(gsoapContext); // remove deserialized C++ objects
	soap_end(gsoapContext); // remove deserialized data
	soap_done(gsoapContext); // finalize last use of the context
	soap_free(gsoapContext); // Free the context
}

std::string EnumStringMapper::getEnergisticsPropertyKindName(gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind energisticsPropertyKind) const
{
	return gsoap_resqml2_0_1::soap_resqml20__ResqmlPropertyKind2s(gsoapContext, energisticsPropertyKind);
}

gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind EnumStringMapper::getEnergisticsPropertyKind(const std::string & energisticsPropertyKindName) const
{
	gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind result;
	return gsoap_resqml2_0_1::soap_s2resqml20__ResqmlPropertyKind(gsoapContext, energisticsPropertyKindName.c_str(), &result) == SOAP_OK ? result : gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind::RESQML_x0020root_x0020property;
}

std::string EnumStringMapper::getEnergisticsUnitOfMeasureName(gsoap_resqml2_0_1::resqml20__ResqmlUom energisticsUom) const
{
	return gsoap_resqml2_0_1::soap_resqml20__ResqmlUom2s(gsoapContext, energisticsUom);
}

gsoap_resqml2_0_1::resqml20__ResqmlUom EnumStringMapper::getEnergisticsUnitOfMeasure(const std::string & energisticsUomName) const
{
	gsoap_resqml2_0_1::resqml20__ResqmlUom result;
	return gsoap_resqml2_0_1::soap_s2resqml20__ResqmlUom(gsoapContext, energisticsUomName.c_str(), &result) == SOAP_OK ? result : gsoap_resqml2_0_1::resqml20__ResqmlUom::Euc;
}

std::string EnumStringMapper::getFacet(gsoap_resqml2_0_1::resqml20__Facet facet) const
{
	return gsoap_resqml2_0_1::soap_resqml20__Facet2s(gsoapContext, facet);
}

gsoap_resqml2_0_1::resqml20__Facet EnumStringMapper::getFacet(const std::string & facet) const
{
	gsoap_resqml2_0_1::resqml20__Facet result;
	return gsoap_resqml2_0_1::soap_s2resqml20__Facet(gsoapContext, facet.c_str(), &result) == SOAP_OK ? result : gsoap_resqml2_0_1::resqml20__Facet::what;
}

std::string EnumStringMapper::lengthUomToString(gsoap_eml2_3::eml23__LengthUom witsmlUom) const
{
	return gsoap_eml2_3::soap_eml23__LengthUom2s(gsoapContext, witsmlUom);
}

std::string EnumStringMapper::verticalCoordinateUomToString(gsoap_eml2_3::eml23__VerticalCoordinateUom witsmlUom) const
{
	return gsoap_eml2_3::soap_eml23__VerticalCoordinateUom2s(gsoapContext, witsmlUom);
}

std::string EnumStringMapper::planeAngleUomToString(gsoap_eml2_3::eml23__PlaneAngleUom witsmlUom) const
{
	return gsoap_eml2_3::soap_eml23__PlaneAngleUom2s(gsoapContext, witsmlUom);
}
