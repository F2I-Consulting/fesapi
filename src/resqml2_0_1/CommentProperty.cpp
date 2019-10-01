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
#include "resqml2_0_1/CommentProperty.h"

#include <sstream>
#include <list>

#include "hdf5.h"

#include "common/AbstractHdfProxy.h"
#include "common/EnumStringMapper.h"

#include "resqml2/AbstractRepresentation.h"
#include "resqml2_0_1/PropertyKind.h"

using namespace std;
using namespace RESQML2_0_1_NS;
using namespace gsoap_resqml2_0_1;

const char* CommentProperty::XML_TAG = "CommentProperty";

CommentProperty::CommentProperty(RESQML2_NS::AbstractRepresentation * rep, const string & guid, const string & title,
	const unsigned int & dimension, const gsoap_resqml2_0_1::resqml20__IndexableElements & attachmentKind, const resqml20__ResqmlPropertyKind & energisticsPropertyKind)
{
	gsoapProxy2_0_1 = soap_new_resqml20__obj_USCORECommentProperty(rep->getGsoapContext());	
	_resqml20__CommentProperty* prop = static_cast<_resqml20__CommentProperty*>(gsoapProxy2_0_1);
	prop->IndexableElement = attachmentKind;
	prop->Count = dimension;

	resqml20__StandardPropertyKind* xmlStandardPropKind = soap_new_resqml20__StandardPropertyKind(gsoapProxy2_0_1->soap);
	xmlStandardPropKind->Kind = energisticsPropertyKind;
	prop->PropertyKind = xmlStandardPropKind;

	initMandatoryMetadata();
	setMetadata(guid, title, std::string(), -1, std::string(), std::string(), -1, std::string());

	setRepresentation(rep);
}

CommentProperty::CommentProperty(RESQML2_NS::AbstractRepresentation * rep, const string & guid, const string & title,
	const unsigned int & dimension, const gsoap_resqml2_0_1::resqml20__IndexableElements & attachmentKind, RESQML2_NS::PropertyKind * localPropKind)
{
	gsoapProxy2_0_1 = soap_new_resqml20__obj_USCORECommentProperty(rep->getGsoapContext());	
	_resqml20__CommentProperty* prop = static_cast<_resqml20__CommentProperty*>(gsoapProxy2_0_1);
	prop->IndexableElement = attachmentKind;
	prop->Count = dimension;

	initMandatoryMetadata();
	setMetadata(guid, title, std::string(), -1, std::string(), std::string(), -1, std::string());

	setRepresentation(rep);

	setLocalPropertyKind(localPropKind);
}

void CommentProperty::pushBackStringHdf5ArrayOfValues(const std::vector<std::string> & values,
	COMMON_NS::AbstractHdfProxy * proxy)
{
	const string datasetName = pushBackRefToExistingDataset(proxy, "");

	// Build the CHAR array
	hsize_t dimTwo = 0;
	for (std::vector<std::string>::const_iterator it = values.begin() ; it!= values.end() ; ++it){
		if ((*it).length() > dimTwo)
			dimTwo = (*it).length();
	}

	hsize_t strNb = values.size();
	unsigned char* cTab = new unsigned char[strNb*dimTwo];

	int indStr = 0;
	for (std::vector<std::string>::const_iterator it = values.begin() ; it!= values.end() ; ++it){
		for (unsigned int indCha = 0 ; indCha < dimTwo ; indCha++) {
			if (indCha < (*it).length())
				cTab[(indStr*dimTwo)+indCha] = (*it)[indCha];
			else
				cTab[(indStr*dimTwo)+indCha] = '\0';
		}
		indStr++;
	}

	hsize_t nbValPerDim[] = {strNb, dimTwo};
	const unsigned int nbDimensions = 2;

    // HDF
	proxy->writeArrayNd(gsoapProxy2_0_1->uuid,
		datasetName,
        H5T_NATIVE_UCHAR,
        cTab,
        nbValPerDim,   // 0 = number of strings, 1 = length of the longest string 
		nbDimensions); // 2

    delete [] cTab;
}

std::string CommentProperty::pushBackRefToExistingDataset(COMMON_NS::AbstractHdfProxy* hdfProxy, const std::string & datasetName, LONG64)
{
	getRepository()->addRelationship(this, hdfProxy);
	_resqml20__CommentProperty* prop = static_cast<_resqml20__CommentProperty*>(gsoapProxy2_0_1);

	resqml20__PatchOfValues* patch = soap_new_resqml20__PatchOfValues(gsoapProxy2_0_1->soap);
	patch->RepresentationPatchIndex = static_cast<ULONG64*>(soap_malloc(gsoapProxy2_0_1->soap, sizeof(ULONG64)));
	*(patch->RepresentationPatchIndex) = prop->PatchOfValues.size();

	// XML
	ostringstream oss;
	resqml20__StringHdf5Array* xmlValues = soap_new_resqml20__StringHdf5Array(gsoapProxy2_0_1->soap);
	xmlValues->Values = soap_new_eml20__Hdf5Dataset(gsoapProxy2_0_1->soap);
	xmlValues->Values->HdfProxy = hdfProxy->newResqmlReference();

	if (datasetName.empty()) {
		ostringstream ossForHdf;
		ossForHdf << "values_patch" << *(patch->RepresentationPatchIndex);
		xmlValues->Values->PathInHdfFile = "/RESQML/" + prop->uuid + "/" + ossForHdf.str();
	}
	else {
		xmlValues->Values->PathInHdfFile = datasetName;
	}

	patch->Values = xmlValues;

	prop->PatchOfValues.push_back(patch);

	return xmlValues->Values->PathInHdfFile;
}

std::vector<std::string> CommentProperty::getStringValuesOfPatch(unsigned int patchIndex)
{
	std::vector<std::string> result;

	// Look for the hdf where the comments are stored.
	_resqml20__CommentProperty const * prop = static_cast<_resqml20__CommentProperty*>(gsoapProxy2_0_1);
	eml20__Hdf5Dataset const * dataset = static_cast<resqml20__StringHdf5Array*>(prop->PatchOfValues[patchIndex]->Values)->Values;
	COMMON_NS::AbstractHdfProxy * hdfProxy = getHdfProxyFromDataset(dataset);

	// Check if the hdf dataset really contains constant length string.
	std::vector<hsize_t> dims = hdfProxy->readArrayDimensions (dataset->PathInHdfFile);
	if (dims.size() != 2) {
		return result;
	}
	// Check if the hdf dataset really contains unsigned char values.
	if (getValuesHdfDatatype() != AbstractValuesProperty::UCHAR) {
		return result;
	}

	const unsigned int nbStrings = (unsigned int)dims[0]; // The count of strings in the HDF dataset.
	const unsigned int stringLength = (unsigned int)dims[1]; // The constant string length in the hdf dataset.

	// Read all char/strings from the hdf dataset
	unsigned char* values = new unsigned char[nbStrings * stringLength];
	hdfProxy->readArrayNdOfUCharValues (dataset->PathInHdfFile, values);

	for (unsigned int stringIndex = 0; stringIndex < nbStrings; ++stringIndex) {
		std::string comment = string();
		unsigned int globalCharIndex = stringIndex*stringLength;
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

	delete [] values;

	return result;
}

bool CommentProperty::validatePropertyKindAssociation(RESQML2_NS::PropertyKind* pk)
{
	if (pk == nullptr) {
		throw invalid_argument("The property kind to validate cannot be null.");
	}

	if (!pk->isPartial()) {
		if (pk->isAbstract()) {
			repository->addWarning("The comment property " + getUuid() + " cannot be associated to a local property kind " + pk->getUuid() + " which is abstract. This property will be assumed to be a partial one.");
			changeToPartialObject();
			return false;
		}
		if (repository->getPropertyKindMapper() != nullptr) {
			if (pk->isParentPartial()) {
				repository->addWarning("Cannot verify if the local property kind " + pk->getUuid() + " of the comment property " + getUuid() + " is right because one if its parent property kind is abstract.");
				return true;
			}
			if (pk->isChildOf(resqml20__ResqmlPropertyKind__continuous) || pk->isChildOf(resqml20__ResqmlPropertyKind__discrete) || pk->isChildOf(resqml20__ResqmlPropertyKind__categorical)) {
				repository->addWarning("The comment property " + getUuid() + " cannot be associated to a local property kind " + pk->getUuid() + " which is either a continuous, discrete or categorical standard property kind. This property will be assumed to be a partial one.");
				changeToPartialObject();
				return false;
			}
		}
		else {
			repository->addWarning("Cannot verify if the local property kind " + pk->getUuid() + " of the comment property " + getUuid() + " is right because no property kind mapping files have been loaded.");
		}
	}
	else {
		repository->addWarning("Cannot verify if the local property kind " + pk->getUuid() + " of the comment property " + getUuid() + " is right because it is abstract.");
	}

	return true;
}

bool CommentProperty::validatePropertyKindAssociation(const gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind & pk)
{
	COMMON_NS::EnumStringMapper tmp;
	std::string pkName = tmp.getEnergisticsPropertyKindName(pk);

	PropertyKindMapper* pkMapper = repository->getPropertyKindMapper();
	if (pkMapper != nullptr) {
		if (pkMapper->isAbstract(pk)) {
			repository->addWarning("The comment property " + getUuid() + " cannot be associated to a resqml property kind \"" + pkName + "\" which is abstract. This property will be assumed to be a partial one.");
			changeToPartialObject();
			return false;
		}
		if (pkMapper->isChildOf(pk, resqml20__ResqmlPropertyKind__continuous) || pkMapper->isChildOf(pk, resqml20__ResqmlPropertyKind__discrete) || pkMapper->isChildOf(pk, resqml20__ResqmlPropertyKind__categorical)) {
			repository->addWarning("The comment property " + getUuid() + " cannot be associated to a resqml property kind \"" + pkName + "\" which is either a continuous, discrete or categorical standard property kind. This property will be assumed to be a partial one.");
			changeToPartialObject();
			return false;
		}
	}
	else {
		repository->addWarning("Cannot verify if the resqml property kind \"" + pkName + "\" of the comment property " + getUuid() + " is right because no property kind mapping files have been loaded.");
	}

	return true;
}
