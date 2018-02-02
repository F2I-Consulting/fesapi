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
#include "resqml2_0_1/SeismicLineSetFeature.h"

#include "resqml2_0_1/SeismicLineFeature.h"

using namespace std;
using namespace resqml2_0_1;
using namespace gsoap_resqml2_0_1;
using namespace epc;

const char* SeismicLineSetFeature::XML_TAG = "SeismicLineSetFeature";

SeismicLineSetFeature::SeismicLineSetFeature(soap* soapContext, const std::string & guid, const std::string & title)
{
	if (soapContext == nullptr)
		throw invalid_argument("The soap context cannot be null.");

	gsoapProxy2_0_1 = soap_new_resqml2__obj_USCORESeismicLineSetFeature(soapContext, 1);
	_resqml2__SeismicLineSetFeature* seismicLineSet = static_cast<_resqml2__SeismicLineSetFeature*>(gsoapProxy2_0_1);

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "", "");
}

std::vector<epc::Relationship> SeismicLineSetFeature::getAllEpcRelationships() const
{
	std::vector<epc::Relationship> result;

	for (unsigned int i = 0; i < seismicLineSet.size(); i++)
	{
		Relationship rel(seismicLineSet[i]->getPartNameInEpcDocument(), "", seismicLineSet[i]->getUuid());
		rel.setSourceObjectType();
		result.push_back(rel);
	}

	return result;
}

