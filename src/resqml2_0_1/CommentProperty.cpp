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
#include "CommentProperty.h"

#include <sstream>
#include <list>

#include "../eml2/AbstractHdfProxy.h"
#include "../common/EnumStringMapper.h"

#include "../resqml2/AbstractRepresentation.h"
#include "PropertyKind.h"

using namespace std;
using namespace RESQML2_0_1_NS;
using namespace gsoap_resqml2_0_1;

const char* CommentProperty::XML_NS = "resqml20";

CommentProperty::CommentProperty(RESQML2_NS::AbstractRepresentation * rep, const string & guid, const string & title,
	unsigned int dimension, gsoap_eml2_3::resqml22__IndexableElement attachmentKind, resqml20__ResqmlPropertyKind energisticsPropertyKind)
{
	if (rep == nullptr) {
		throw invalid_argument("The representation of this property values cannot be null.");
	}

	gsoapProxy2_0_1 = soap_new_resqml20__obj_USCORECommentProperty(rep->getGsoapContext());	
	_resqml20__CommentProperty* prop = static_cast<_resqml20__CommentProperty*>(gsoapProxy2_0_1);
	prop->IndexableElement = mapIndexableElement(attachmentKind);
	prop->Count = dimension;

	resqml20__StandardPropertyKind* xmlStandardPropKind = soap_new_resqml20__StandardPropertyKind(gsoapProxy2_0_1->soap);
	xmlStandardPropKind->Kind = energisticsPropertyKind;
	prop->PropertyKind = xmlStandardPropKind;

	initMandatoryMetadata();
	setMetadata(guid, title, std::string(), -1, std::string(), std::string(), -1, std::string());

	rep->getRepository()->addDataObject(this);
	setRepresentation(rep);
}

CommentProperty::CommentProperty(RESQML2_NS::AbstractRepresentation * rep, const string & guid, const string & title,
	unsigned int dimension, gsoap_eml2_3::resqml22__IndexableElement attachmentKind, EML2_NS::PropertyKind * localPropKind)
{
	if (rep == nullptr) {
		throw invalid_argument("The representation of this property values cannot be null.");
	}

	gsoapProxy2_0_1 = soap_new_resqml20__obj_USCORECommentProperty(rep->getGsoapContext());	
	_resqml20__CommentProperty* prop = static_cast<_resqml20__CommentProperty*>(gsoapProxy2_0_1);
	prop->IndexableElement = mapIndexableElement(attachmentKind);
	prop->Count = dimension;

	initMandatoryMetadata();
	setMetadata(guid, title, std::string(), -1, std::string(), std::string(), -1, std::string());

	rep->getRepository()->addDataObject(this);
	setRepresentation(rep);

	setPropertyKind(localPropKind);
}

std::string CommentProperty::pushBackRefToExistingDataset(EML2_NS::AbstractHdfProxy* hdfProxy, const std::string & datasetName)
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
		xmlValues->Values->PathInHdfFile = getHdfGroup() + "/" + ossForHdf.str();
	}
	else {
		xmlValues->Values->PathInHdfFile = datasetName;
	}

	patch->Values = xmlValues;

	prop->PatchOfValues.push_back(patch);

	return xmlValues->Values->PathInHdfFile;
}

EML2_NS::AbstractHdfProxy* CommentProperty::getValuesHdfProxyAndDatasetPathOfPatch(unsigned int patchIndex, std::string & datasetPath) const
{
	// Look for the hdf where the comments are stored.
	_resqml20__CommentProperty const * prop = static_cast<_resqml20__CommentProperty*>(gsoapProxy2_0_1);

	if (patchIndex >= prop->PatchOfValues.size()) {
		throw std::out_of_range("The patch index is out of range.");
	}

	eml20__Hdf5Dataset const * dataset = static_cast<resqml20__StringHdf5Array*>(prop->PatchOfValues[patchIndex]->Values)->Values;
	datasetPath = dataset->PathInHdfFile;
	return getHdfProxyFromDataset(dataset);
}

bool CommentProperty::validatePropertyKindAssociation(EML2_NS::PropertyKind* pk)
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
			auto pk201 = dynamic_cast<RESQML2_0_1_NS::PropertyKind*>(pk);
			if (pk201 != nullptr) {
				if (!pk201->isChildOf(resqml20__ResqmlPropertyKind::continuous) || pk201->isChildOf(resqml20__ResqmlPropertyKind::discrete) || pk201->isChildOf(resqml20__ResqmlPropertyKind::categorical)) {
					repository->addWarning("The comment property " + getUuid() + " cannot be associated to a local property kind " + pk->getUuid() + " which is either a continuous, discrete or categorical standard property kind. This property will be assumed to be a partial one.");
					changeToPartialObject();
					return false;
				}
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

bool CommentProperty::validatePropertyKindAssociation(gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind pk)
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
		if (pkMapper->isChildOf(pk, resqml20__ResqmlPropertyKind::continuous) || pkMapper->isChildOf(pk, resqml20__ResqmlPropertyKind::discrete) || pkMapper->isChildOf(pk, resqml20__ResqmlPropertyKind::categorical)) {
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

gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind CommentProperty::getEnergisticsPropertyKind() const
{
	return getEnergisticsPropertyKind201();
}
