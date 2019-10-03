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
#include "resqml2_0_1/CategoricalProperty.h"

#include <stdexcept>
#include <sstream>

#include "hdf5.h"

#include "common/AbstractHdfProxy.h"
#include "common/EnumStringMapper.h"

#include "resqml2/AbstractRepresentation.h"
#include "resqml2_0_1/PropertyKind.h"
#include "resqml2_0_1/StringTableLookup.h"

using namespace std;
using namespace RESQML2_0_1_NS;
using namespace gsoap_resqml2_0_1;

const char* CategoricalProperty::XML_TAG = "CategoricalProperty";

CategoricalProperty::CategoricalProperty(RESQML2_NS::AbstractRepresentation * rep, const string & guid, const string & title,
	unsigned int dimension, gsoap_resqml2_0_1::resqml20__IndexableElements attachmentKind,
	StringTableLookup* strLookup, resqml20__ResqmlPropertyKind energisticsPropertyKind)
{
	gsoapProxy2_0_1 = soap_new_resqml20__obj_USCORECategoricalProperty(rep->getGsoapContext());	
	_resqml20__CategoricalProperty* prop = static_cast<_resqml20__CategoricalProperty*>(gsoapProxy2_0_1);
	prop->IndexableElement = attachmentKind;
	prop->Count = dimension;

	resqml20__StandardPropertyKind* xmlStandardPropKind = soap_new_resqml20__StandardPropertyKind(gsoapProxy2_0_1->soap);
	xmlStandardPropKind->Kind = energisticsPropertyKind;
	prop->PropertyKind = xmlStandardPropKind;

	initMandatoryMetadata();
	setMetadata(guid, title, std::string(), -1, std::string(), std::string(), -1, std::string());

	prop->Lookup = strLookup->newResqmlReference();
	getRepository()->addRelationship(this, strLookup);

	setRepresentation(rep);
}

CategoricalProperty::CategoricalProperty(RESQML2_NS::AbstractRepresentation * rep, const string & guid, const string & title,
	unsigned int dimension, gsoap_resqml2_0_1::resqml20__IndexableElements attachmentKind,
	StringTableLookup* strLookup, RESQML2_NS::PropertyKind * localPropKind)
{
	gsoapProxy2_0_1 = soap_new_resqml20__obj_USCORECategoricalProperty(rep->getGsoapContext());	
	_resqml20__CategoricalProperty* prop = static_cast<_resqml20__CategoricalProperty*>(gsoapProxy2_0_1);
	prop->IndexableElement = attachmentKind;
	prop->Count = dimension;

	initMandatoryMetadata();
	setMetadata(guid, title, std::string(), -1, std::string(), std::string(), -1, std::string());

	prop->Lookup = strLookup->newResqmlReference();
	getRepository()->addRelationship(this, strLookup);

	setRepresentation(rep);

	setLocalPropertyKind(localPropKind);
}

void CategoricalProperty::loadTargetRelationships()
{
	AbstractValuesProperty::loadTargetRelationships();

	convertDorIntoRel<StringTableLookup>(static_cast<_resqml20__CategoricalProperty*>(gsoapProxy2_0_1)->Lookup);
}

void CategoricalProperty::pushBackLongHdf5Array1dOfValues(const long * values, ULONG64 valueCount, COMMON_NS::AbstractHdfProxy * proxy, long nullValue)
{
	hsize_t valueCountPerDimension[1] = {valueCount};
	pushBackLongHdf5ArrayOfValues(values, valueCountPerDimension, 1, proxy, nullValue);
}

void CategoricalProperty::pushBackLongHdf5Array2dOfValues(const long * values, ULONG64 valueCountInFastestDim, ULONG64 valueCountInSlowestDim, COMMON_NS::AbstractHdfProxy * proxy, long nullValue)
{
	hsize_t valueCountPerDimension[2] = {valueCountInSlowestDim, valueCountInFastestDim};
	pushBackLongHdf5ArrayOfValues(values, valueCountPerDimension, 2, proxy, nullValue);
}

void CategoricalProperty::pushBackLongHdf5Array3dOfValues(const long * values, ULONG64 valueCountInFastestDim, ULONG64 valueCountInMiddleDim, ULONG64 valueCountInSlowestDim, COMMON_NS::AbstractHdfProxy * proxy, long nullValue)
{
	hsize_t valueCountPerDimension[3] = {valueCountInSlowestDim, valueCountInMiddleDim, valueCountInFastestDim};
	pushBackLongHdf5ArrayOfValues(values, valueCountPerDimension, 3, proxy, nullValue);
}

void CategoricalProperty::pushBackLongHdf5ArrayOfValues(const long * values, unsigned long long * numValues, unsigned int numDimensionsInArray, COMMON_NS::AbstractHdfProxy * proxy, long nullValue)
{
	if (proxy == nullptr) {
		proxy = getRepository()->getDefaultHdfProxy();
	}
	const string datasetName = pushBackRefToExistingDataset(proxy, "", nullValue);

	// HDF
	proxy->writeArrayNd(gsoapProxy2_0_1->uuid,
		datasetName,
		H5T_NATIVE_LONG,
		values,
		numValues, numDimensionsInArray);
}

void CategoricalProperty::pushBackUShortHdf5Array1dOfValues(const unsigned short * values, ULONG64 valueCount, COMMON_NS::AbstractHdfProxy * proxy, unsigned short nullValue)
{
	hsize_t valueCountPerDimension[3] = { valueCount };
	pushBackUShortHdf5ArrayOfValues(values, valueCountPerDimension, 1, proxy, nullValue);
}

void CategoricalProperty::pushBackUShortHdf5Array2dOfValues(const unsigned short * values, ULONG64 valueCountInFastestDim, ULONG64 valueCountInSlowestDim, COMMON_NS::AbstractHdfProxy * proxy, unsigned short nullValue)
{
	hsize_t valueCountPerDimension[3] = { valueCountInSlowestDim, valueCountInFastestDim };
	pushBackUShortHdf5ArrayOfValues(values, valueCountPerDimension, 2, proxy, nullValue);
}

void CategoricalProperty::pushBackUShortHdf5Array3dOfValues(const unsigned short * values, ULONG64 valueCountInFastestDim, ULONG64 valueCountInMiddleDim, ULONG64 valueCountInSlowestDim, COMMON_NS::AbstractHdfProxy * proxy, unsigned short nullValue)
{
	hsize_t valueCountPerDimension[3] = { valueCountInSlowestDim, valueCountInMiddleDim, valueCountInFastestDim };
	pushBackUShortHdf5ArrayOfValues(values, valueCountPerDimension, 3, proxy, nullValue);
}

void CategoricalProperty::pushBackUShortHdf5ArrayOfValues(const unsigned short * values, unsigned long long * numValues, unsigned int numDimensionsInArray, COMMON_NS::AbstractHdfProxy* proxy, unsigned short nullValue)
{
	if (proxy == nullptr) {
		proxy = getRepository()->getDefaultHdfProxy();
	}
	const string datasetName = pushBackRefToExistingDataset(proxy, "", nullValue);

	// HDF
	proxy->writeArrayNd(gsoapProxy2_0_1->uuid,
		datasetName,
		H5T_NATIVE_USHORT,
		values,
		numValues, numDimensionsInArray);
}

std::string CategoricalProperty::pushBackRefToExistingDataset(COMMON_NS::AbstractHdfProxy* hdfProxy, const std::string & datasetName, LONG64 nullValue)
{
	return pushBackRefToExistingIntegerDataset(hdfProxy, datasetName, nullValue);
}

std::string CategoricalProperty::getStringLookupUuid() const
{
	return static_cast<_resqml20__CategoricalProperty*>(gsoapProxy2_0_1)->Lookup->UUID;
}

bool CategoricalProperty::validatePropertyKindAssociation(RESQML2_NS::PropertyKind* pk)
{
	if (pk == nullptr) {
		throw invalid_argument("The property kind to validate cannot be null.");
	}

	if (!pk->isPartial()) {
		if (pk->isAbstract()) {
			repository->addWarning("The categorical property " + getUuid() + " cannot be associated to a local property kind " + pk->getUuid() + " which is abstract. This property will be assumed to be a partial one.");
			changeToPartialObject();
			return false;
		}
		if (repository->getPropertyKindMapper() != nullptr) {
			if (pk->isParentPartial()) {
				repository->addWarning("Cannot verify if the local property kind " + pk->getUuid() + " of the categorical property " + getUuid() + " is right because one if its parent property kind is abstract.");
				return true;
			}
			if (!pk->isChildOf(resqml20__ResqmlPropertyKind__categorical)) {
				if (!pk->isChildOf(resqml20__ResqmlPropertyKind__discrete)) {
					repository->addWarning("The categorical property " + getUuid() + " cannot be associated to a local property kind " + pk->getUuid() + " which does not derive from the discrete or categorical standard property kind. This property will be assumed to be a partial one.");
					changeToPartialObject();
					return false;
				}
				else {
					repository->addWarning("The categorical property " + getUuid() + " is associated to a discrete local property kind " + pk->getUuid() + ".");
				}
			}
		}
		else {
			repository->addWarning("Cannot verify if the local property kind " + pk->getUuid() + " of the categorical property " + getUuid() + " is right because no property kind mapping files have been loaded.");
		}
	}
	else {
		repository->addWarning("Cannot verify if the local property kind " + pk->getUuid() + " of the categorical property " + getUuid() + " is right because it is abstract.");
	}

	return true;
}

bool CategoricalProperty::validatePropertyKindAssociation(gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind pk)
{
	COMMON_NS::EnumStringMapper tmp;
	std::string pkName = tmp.getEnergisticsPropertyKindName(pk);

	PropertyKindMapper* pkMapper = repository->getPropertyKindMapper();
	if (pkMapper != nullptr) {
		if (pkMapper->isAbstract(pk)) {
			repository->addWarning("The categorical property " + getUuid() + " cannot be associated to a resqml property kind \"" + pkName + "\" which is abstract. This property will be assumed to be a partial one.");
			changeToPartialObject();
			return false;
		}
		if (!pkMapper->isChildOf(pk, resqml20__ResqmlPropertyKind__categorical)) {
			if (!pkMapper->isChildOf(pk, resqml20__ResqmlPropertyKind__discrete)) {
				repository->addWarning("The categorical property " + getUuid() + " cannot be associated to a resqml property kind \"" + pkName + "\" which does not derive from the discrete or categorical standard property kind. This property will be assumed to be a partial one.");
				changeToPartialObject();
				return false;
			}
			else {
				getRepository()->addWarning("The categorical property " + getUuid() + " is associated to a discrete resqml property kind \"" + pkName + "\".");
			}
		}
	}
	else {
		repository->addWarning("Cannot verify if the resqml property kind \"" + pkName + "\" of the categorical property " + getUuid() + " is right because no property kind mapping files have been loaded.");
	}

	return true;
}

StringTableLookup* CategoricalProperty::getStringLookup()
{
	return getRepository()->getDataObjectByUuid<StringTableLookup>(getStringLookupUuid());
}
