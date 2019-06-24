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
#include "common/EnumStringMapper.h"

#include "proxies/gsoap_resqml2_0_1H.h"
#include "proxies/gsoap_eml2_1H.h"

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

std::string EnumStringMapper::getEnergisticsPropertyKindName(gsoap_resqml2_0_1::resqml2__ResqmlPropertyKind energisticsPropertyKind) const
{
	return gsoap_resqml2_0_1::soap_resqml2__ResqmlPropertyKind2s(gsoapContext, energisticsPropertyKind);
}

gsoap_resqml2_0_1::resqml2__ResqmlPropertyKind EnumStringMapper::getEnergisticsPropertyKind(const std::string & energisticsPropertyKindName) const
{
	gsoap_resqml2_0_1::resqml2__ResqmlPropertyKind result;
	return gsoap_resqml2_0_1::soap_s2resqml2__ResqmlPropertyKind(gsoapContext, energisticsPropertyKindName.c_str(), &result) == SOAP_OK ? result : gsoap_resqml2_0_1::resqml2__ResqmlPropertyKind__RESQML_x0020root_x0020property;
}

std::string EnumStringMapper::getEnergisticsUnitOfMeasureName(gsoap_resqml2_0_1::resqml2__ResqmlUom energisticsUom) const
{
	return gsoap_resqml2_0_1::soap_resqml2__ResqmlUom2s(gsoapContext, energisticsUom);
}

gsoap_resqml2_0_1::resqml2__ResqmlUom EnumStringMapper::getEnergisticsUnitOfMeasure(const std::string & energisticsUomName) const
{
	gsoap_resqml2_0_1::resqml2__ResqmlUom result;
	return gsoap_resqml2_0_1::soap_s2resqml2__ResqmlUom(gsoapContext, energisticsUomName.c_str(), &result) == SOAP_OK ? result : gsoap_resqml2_0_1::resqml2__ResqmlUom__Euc;
}

std::string EnumStringMapper::getFacet(gsoap_resqml2_0_1::resqml2__Facet facet) const
{
	return gsoap_resqml2_0_1::soap_resqml2__Facet2s(gsoapContext, facet);
}

gsoap_resqml2_0_1::resqml2__Facet EnumStringMapper::getFacet(const std::string & facet) const
{
	gsoap_resqml2_0_1::resqml2__Facet result;
	return gsoap_resqml2_0_1::soap_s2resqml2__Facet(gsoapContext, facet.c_str(), &result) == SOAP_OK ? result : gsoap_resqml2_0_1::resqml2__Facet__what;
}

std::string EnumStringMapper::lengthUomToString(gsoap_eml2_1::eml21__LengthUom witsmlUom) const
{
	return gsoap_eml2_1::soap_eml21__LengthUom2s(gsoapContext, witsmlUom);
}

std::string EnumStringMapper::verticalCoordinateUomToString(gsoap_eml2_1::eml21__VerticalCoordinateUom witsmlUom) const
{
	return gsoap_eml2_1::soap_eml21__VerticalCoordinateUom2s(gsoapContext, witsmlUom);
}

std::string EnumStringMapper::planeAngleUomToString(gsoap_eml2_1::eml21__PlaneAngleUom witsmlUom) const
{
	return gsoap_eml2_1::soap_eml21__PlaneAngleUom2s(gsoapContext, witsmlUom);
}
