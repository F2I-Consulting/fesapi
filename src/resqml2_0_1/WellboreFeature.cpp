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
#include "resqml2_0_1/WellboreFeature.h"

#include <stdexcept>

#include "witsml1_4_1_1/Well.h"

using namespace std;
using namespace resqml2_0_1;
using namespace gsoap_resqml2_0_1;
using namespace epc;

const char* WellboreFeature::XML_TAG = "WellboreFeature";

WellboreFeature::WellboreFeature(soap* soapContext, const string & guid, const std::string & title) :witsmlWellbore(nullptr)
{
	if (soapContext == nullptr)
		throw invalid_argument("The soap context cannot be null.");

	gsoapProxy2_0_1 = soap_new_resqml2__obj_USCOREWellboreFeature(soapContext, 1);

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "", "");
}

void WellboreFeature::setWitsmlWellbore(witsml1_4_1_1::Wellbore * wellbore)
{
	witsmlWellbore = wellbore;
	wellbore->resqmlWellboreFeature = this;

	if (updateXml)
	{
		resqml2__obj_USCOREWellboreFeature* resqmlWellbore = static_cast<resqml2__obj_USCOREWellboreFeature*>(gsoapProxy2_0_1);
		resqmlWellbore->WitsmlWellbore = soap_new_resqml2__WitsmlWellboreReference(gsoapProxy2_0_1->soap, 1);
		resqmlWellbore->WitsmlWellbore->WitsmlWellbore = wellbore->newResqmlReference();
		resqmlWellbore->WitsmlWellbore->WitsmlWell = wellbore->getWell()->newResqmlReference();
	}
}

vector<Relationship> WellboreFeature::getAllEpcRelationships() const
{
	vector<Relationship> result = AbstractTechnicalFeature::getAllEpcRelationships();

	if (witsmlWellbore)
	{
		Relationship relWellbores(witsmlWellbore->getPartNameInEpcDocument(), "", witsmlWellbore->getUuid());
		relWellbores.setDestinationObjectType();
		result.push_back(relWellbores);

		Relationship relWells(witsmlWellbore->getWell()->getPartNameInEpcDocument(), "", witsmlWellbore->getWell()->getUuid());
		relWells.setDestinationObjectType();
		result.push_back(relWells);
	}

	return result;
}

void WellboreFeature::importRelationshipSetFromEpc(common::EpcDocument* epcDoc)
{
	resqml2__obj_USCOREWellboreFeature* resqmlWellbore = static_cast<resqml2__obj_USCOREWellboreFeature*>(gsoapProxy2_0_1);

	if (resqmlWellbore->WitsmlWellbore && resqmlWellbore->WitsmlWellbore->WitsmlWellbore)
	{
		witsml1_4_1_1::Wellbore* tmp = static_cast<witsml1_4_1_1::Wellbore*>(epcDoc->getWitsmlAbstractObjectByUuid(resqmlWellbore->WitsmlWellbore->WitsmlWellbore->UUID));
		if (tmp)
		{
			updateXml = false;
			setWitsmlWellbore(tmp);
			updateXml = true;
		}
	}
}

