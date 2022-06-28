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
#include "AbstractSeismicLineFeature.h"

#include <H5Tpublic.h>

#include "../eml2/AbstractHdfProxy.h"

#include "SeismicLineSetFeature.h"

using namespace std;
using namespace RESQML2_NS;

void AbstractSeismicLineFeature::setSeismicLineSet(RESQML2_NS::SeismicLineSetFeature * seisLineSet)
{
	getRepository()->addRelationship(this, seisLineSet);

	if (gsoapProxy2_0_1 != nullptr) {
		static_cast<gsoap_resqml2_0_1::_resqml20__SeismicLineFeature*>(gsoapProxy2_0_1)->IsPartOf = seisLineSet->newResqmlReference();
	}
	else if (gsoapProxy2_3 != nullptr) {
		static_cast<gsoap_eml2_3::resqml22__AbstractSeismicLineFeature*>(gsoapProxy2_3)->IsPartOf = seisLineSet->newEml23Reference();
	}
	else {
		throw logic_error("This version is not supported yet");
	}
}

COMMON_NS::DataObjectReference AbstractSeismicLineFeature::getSeismicLineSetDor() const
{
	if (gsoapProxy2_0_1 != nullptr) {
		gsoap_resqml2_0_1::_resqml20__SeismicLineFeature* seismicLine = static_cast<gsoap_resqml2_0_1::_resqml20__SeismicLineFeature*>(gsoapProxy2_0_1);
		return seismicLine->IsPartOf == nullptr ? COMMON_NS::DataObjectReference() : COMMON_NS::DataObjectReference(seismicLine->IsPartOf);
	}
	else if (gsoapProxy2_3 != nullptr) {
		gsoap_eml2_3::resqml22__AbstractSeismicLineFeature* seismicLine = static_cast<gsoap_eml2_3::resqml22__AbstractSeismicLineFeature*>(gsoapProxy2_3);
		return seismicLine->IsPartOf == nullptr ? COMMON_NS::DataObjectReference() : COMMON_NS::DataObjectReference(seismicLine->IsPartOf);
	}
	else {
		throw logic_error("This version is not supported yet");
	}
}

SeismicLineSetFeature* AbstractSeismicLineFeature::getSeismicLineSet() const
{
	return repository->getDataObjectByUuid<SeismicLineSetFeature>(getSeismicLineSetDor().getUuid());
}

void AbstractSeismicLineFeature::loadTargetRelationships()
{
	COMMON_NS::DataObjectReference dor = getSeismicLineSetDor();

	if (!dor.isEmpty()) {
		convertDorIntoRel<SeismicLineSetFeature>(dor);
	}

	if (gsoapProxy2_3 != nullptr) {
		gsoap_eml2_3::resqml22__AbstractSeismicLineFeature* seismicLine = static_cast<gsoap_eml2_3::resqml22__AbstractSeismicLineFeature*>(gsoapProxy2_3);

		if (seismicLine->TraceLabels != nullptr) {
			for (size_t i = 0; i < seismicLine->TraceLabels->Values->ExternalFileProxy.size(); ++i) {
				convertDorIntoRel<EML2_NS::AbstractHdfProxy>(COMMON_NS::DataObjectReference(seismicLine->TraceLabels->Values->ExternalFileProxy[i]->EpcExternalPartReference));
			}
		}
	}
}

std::vector<std::string> AbstractSeismicLineFeature::getTraceLabels() const
{
	std::vector<std::string> result;
	if (gsoapProxy2_0_1 != nullptr) {
		gsoap_resqml2_0_1::_resqml20__SeismicLineFeature* seismicLine = static_cast<gsoap_resqml2_0_1::_resqml20__SeismicLineFeature*>(gsoapProxy2_0_1);
		for (unsigned int incr = 0; incr < seismicLine->TraceCount; ++incr) {
			result.push_back(std::to_string(seismicLine->FirstTraceIndex + incr * seismicLine->TraceIndexIncrement));
		}
	}
	else if (gsoapProxy2_3 != nullptr) {
		gsoap_eml2_3::resqml22__AbstractSeismicLineFeature* seismicLine = static_cast<gsoap_eml2_3::resqml22__AbstractSeismicLineFeature*>(gsoapProxy2_3);

		if (seismicLine->TraceLabels == nullptr) {
			return result;
		}

		// HDF5
		std::string datasetPath;
		auto dsPart = seismicLine->TraceLabels->Values->ExternalFileProxy[0];
		EML2_NS::AbstractHdfProxy* hdfProxy = getHdfProxyFromDataset(dsPart);

		// Check if the hdf dataset really contains constant length string.
		std::vector<hsize_t> dims = hdfProxy->readArrayDimensions(datasetPath);
		if (dims.size() != 2) {
			return result;
		}
		// Check if the hdf dataset really contains unsigned char values.
		if (hdfProxy->getNumericalDatatype(dsPart->PathInExternalFile) != COMMON_NS::AbstractObject::numericalDatatypeEnum::UINT8) {
			return result;
		}

		const unsigned int nbStrings = (unsigned int)dims[0]; // The count of strings in the HDF dataset.
		const unsigned int stringLength = (unsigned int)dims[1]; // The constant string length in the hdf dataset.

		// Read all char/strings from the hdf dataset
		std::unique_ptr<unsigned char[]> values(new unsigned char[nbStrings * stringLength]);
		hdfProxy->readArrayNdOfUCharValues(datasetPath, values.get());

		for (unsigned int stringIndex = 0; stringIndex < nbStrings; ++stringIndex) {
			std::string comment = string();
			unsigned int globalCharIndex = stringIndex * stringLength;
			for (unsigned int localCharIndex = 0; localCharIndex < stringLength; ++localCharIndex) {
				if (values[globalCharIndex] != '\0') {
					comment.push_back(values[globalCharIndex]);
				}
				else {
					break;
				}
				globalCharIndex++;
			}

			result.push_back(comment);
		}
	}
	else {
		throw logic_error("This version is not supported yet");
	}

	return result;
}

void AbstractSeismicLineFeature::setTraceLabels(const std::vector<std::string> & values, EML2_NS::AbstractHdfProxy * proxy)
{
	if (gsoapProxy2_3 == nullptr) {
		throw logic_error("A non RESQML2.2 seismic line feature does not support trace label strings.");
	}

	if (proxy == nullptr) {
		proxy = getRepository()->getDefaultHdfProxy();
		if (proxy == nullptr) {
			throw std::invalid_argument("A (default) HDF Proxy must be provided.");
		}
	}
	getRepository()->addRelationship(this, proxy);

	gsoap_eml2_3::resqml22__AbstractSeismicLineFeature* seismicLine = static_cast<gsoap_eml2_3::resqml22__AbstractSeismicLineFeature*>(gsoapProxy2_3);
	seismicLine->TraceLabels = gsoap_eml2_3::soap_new_eml23__StringExternalArray(gsoapProxy2_3->soap);
	seismicLine->TraceLabels->Values = gsoap_eml2_3::soap_new_eml23__ExternalDataset(gsoapProxy2_3->soap);
	auto dsPart = gsoap_eml2_3::soap_new_eml23__ExternalDatasetPart(gsoapProxy2_3->soap);
	dsPart->Count = values.size();
	dsPart->PathInExternalFile = getHdfGroup() + "/TraceLabels";
	dsPart->EpcExternalPartReference = proxy->newEml23Reference();
	seismicLine->TraceLabels->Values->ExternalFileProxy.push_back(dsPart);

	// Build the CHAR array
	hsize_t dimTwo = 0;
	for (std::vector<std::string>::const_iterator it = values.begin(); it != values.end(); ++it) {
		if ((*it).length() > dimTwo)
			dimTwo = (*it).length();
	}

	hsize_t strNb = values.size();
	std::unique_ptr<unsigned char[]> cTab(new unsigned char[strNb*dimTwo]);

	int indStr = 0;
	for (std::vector<std::string>::const_iterator it = values.begin(); it != values.end(); ++it) {
		for (unsigned int indCha = 0; indCha < dimTwo; indCha++) {
			if (indCha < (*it).length())
				cTab[(indStr*dimTwo) + indCha] = (*it)[indCha];
			else
				cTab[(indStr*dimTwo) + indCha] = '\0';
		}
		indStr++;
	}

	hsize_t nbValPerDim[2] = { strNb, dimTwo };
	const unsigned int nbDimensions = 2;
	// HDF
	proxy->writeArrayNd(getHdfGroup(),
		dsPart->PathInExternalFile,
		COMMON_NS::AbstractObject::numericalDatatypeEnum::UINT8,
		cTab.get(),
		nbValPerDim,   // 0 = number of strings, 1 = length of the longest string 
		nbDimensions); // 2
}
