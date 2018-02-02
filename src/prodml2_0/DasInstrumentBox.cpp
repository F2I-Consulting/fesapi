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
#include "prodml2_0/DasInstrumentBox.h"

#include <stdexcept>

using namespace std;
using namespace prodml2_0;
using namespace gsoap_eml2_1;
using namespace epc;

const char* DasInstrumentBox::XML_TAG = "DasInstrumentBox";

DasInstrumentBox::DasInstrumentBox(soap* soapContext, const string & guid, const string & title,
	const std::string & firmwareVersion, const std::string & instrumentName)
{
	if (soapContext == nullptr)
		throw invalid_argument("The soap context cannot be null.");

	gsoapProxy2_1 = soap_new_prodml2__DasInstrumentBox(soapContext, 1);

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "", "");

	_prodml2__DasInstrumentBox* dib = static_cast<_prodml2__DasInstrumentBox*>(gsoapProxy2_1);

	dib->FirmwareVersion = firmwareVersion;
	dib->Instrument = soap_new_prodml2__Instrument(soapContext, 1);
	dib->Instrument->Name = instrumentName;
}

vector<Relationship> DasInstrumentBox::getAllEpcRelationships() const
{
	_prodml2__DasAcquisition* da = static_cast<_prodml2__DasAcquisition*>(gsoapProxy2_1);

	vector<Relationship> result;
	
	// XML backward relationship
	for (size_t i = 0; i < dasAcquisitionSet.size(); i++)
	{
		Relationship rel(dasAcquisitionSet[i]->getPartNameInEpcDocument(), "", dasAcquisitionSet[i]->getUuid());
		rel.setSourceObjectType();
		result.push_back(rel);
	}
	
	return result;
}


