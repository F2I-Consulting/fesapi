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
#include "resqml2_0_1/CategoricalProperty.h"

#include <stdexcept>
#include <sstream>

#include "hdf5.h"

#include "resqml2/AbstractRepresentation.h"
#include "resqml2_0_1/PropertyKind.h"
#include "resqml2_0_1/StringTableLookup.h"
#include "common/AbstractHdfProxy.h"

using namespace std;
using namespace resqml2_0_1;
using namespace gsoap_resqml2_0_1;
using namespace epc;

const char* CategoricalProperty::XML_TAG = "CategoricalProperty";

CategoricalProperty::CategoricalProperty(resqml2::AbstractRepresentation * rep, const string & guid, const string & title,
	const unsigned int & dimension, const gsoap_resqml2_0_1::resqml2__IndexableElements & attachmentKind,
	StringTableLookup* strLookup, const resqml2__ResqmlPropertyKind & energisticsPropertyKind)
	: stringLookup(strLookup)
{
	gsoapProxy2_0_1 = soap_new_resqml2__obj_USCORECategoricalProperty(rep->getGsoapContext(), 1);	
	_resqml2__CategoricalProperty* prop = static_cast<_resqml2__CategoricalProperty*>(gsoapProxy2_0_1);
	prop->IndexableElement = attachmentKind;
	prop->Count = dimension;

	resqml2__StandardPropertyKind* xmlStandardPropKind = soap_new_resqml2__StandardPropertyKind(gsoapProxy2_0_1->soap, 1);
	xmlStandardPropKind->Kind = energisticsPropertyKind;
	prop->PropertyKind = xmlStandardPropKind;

	stringLookup->addCategoricalPropertyValues(this);
	prop->Lookup = stringLookup->newResqmlReference();

	setRepresentation(rep);

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "", "");
}

CategoricalProperty::CategoricalProperty(resqml2::AbstractRepresentation * rep, const string & guid, const string & title,
	const unsigned int & dimension, const gsoap_resqml2_0_1::resqml2__IndexableElements & attachmentKind,
	StringTableLookup* strLookup, resqml2::PropertyKind * localPropKind)
	:stringLookup(strLookup)
{
	gsoapProxy2_0_1 = soap_new_resqml2__obj_USCORECategoricalProperty(rep->getGsoapContext(), 1);	
	_resqml2__CategoricalProperty* prop = static_cast<_resqml2__CategoricalProperty*>(gsoapProxy2_0_1);
	prop->IndexableElement = attachmentKind;
	prop->Count = dimension;

	stringLookup->addCategoricalPropertyValues(this);
	prop->Lookup = stringLookup->newResqmlReference();

	setRepresentation(rep);

	setLocalPropertyKind(localPropKind);

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "", "");
}

vector<Relationship> CategoricalProperty::getAllEpcRelationships() const
{
	vector<Relationship> result = AbstractValuesProperty::getAllEpcRelationships();

	_resqml2__CategoricalProperty* prop = static_cast<_resqml2__CategoricalProperty*>(gsoapProxy2_0_1);

	if (stringLookup)
	{
		Relationship rel(stringLookup->getPartNameInEpcDocument(), "", prop->Lookup->UUID);
		rel.setDestinationObjectType();
		result.push_back(rel);
	}
	else
		throw domain_error("The string lookup associated to the categorical property values cannot be nullptr.");

	return result;
}

void CategoricalProperty::importRelationshipSetFromEpc(common::EpcDocument* epcDoc)
{
	AbstractValuesProperty:: importRelationshipSetFromEpc(epcDoc);

	_resqml2__CategoricalProperty* prop = static_cast<_resqml2__CategoricalProperty*>(gsoapProxy2_0_1);
	stringLookup = static_cast<StringTableLookup*>(epcDoc->getResqmlAbstractObjectByUuid(prop->Lookup->UUID));
	if (stringLookup)
		stringLookup->addCategoricalPropertyValues(this);
}

void CategoricalProperty::pushBackLongHdf5Array1dOfValues(long * values, const ULONG64 & valueCount, common::AbstractHdfProxy * proxy, const long & nullValue)
{
	hsize_t valueCountPerDimension[1] = {valueCount};
	pushBackLongHdf5ArrayOfValues(values, valueCountPerDimension, 1, proxy, nullValue);
}

void CategoricalProperty::pushBackLongHdf5Array2dOfValues(long * values, const ULONG64 & valueCountInFastestDim, const ULONG64 & valueCountInSlowestDim, common::AbstractHdfProxy * proxy, const long & nullValue)
{
	hsize_t valueCountPerDimension[2] = {valueCountInSlowestDim, valueCountInFastestDim};
	pushBackLongHdf5ArrayOfValues(values, valueCountPerDimension, 2, proxy, nullValue);
}

void CategoricalProperty::pushBackLongHdf5Array3dOfValues(long * values, const ULONG64 & valueCountInFastestDim, const ULONG64 & valueCountInMiddleDim, const ULONG64 & valueCountInSlowestDim, common::AbstractHdfProxy * proxy, const long & nullValue)
{
	hsize_t valueCountPerDimension[3] = {valueCountInSlowestDim, valueCountInMiddleDim, valueCountInFastestDim};
	pushBackLongHdf5ArrayOfValues(values, valueCountPerDimension, 3, proxy, nullValue);
}

void CategoricalProperty::pushBackLongHdf5ArrayOfValues(long * values, unsigned long long * numValues, const unsigned int & numDimensionsInArray, common::AbstractHdfProxy * proxy, const long & nullValue)
{
	const string datasetName = pushBackRefToExistingDataset(proxy, "", nullValue);

	// HDF
	proxy->writeArrayNd(gsoapProxy2_0_1->uuid,
		datasetName,
		H5T_NATIVE_LONG,
		values,
		numValues, numDimensionsInArray);
}

void CategoricalProperty::pushBackUShortHdf5Array1dOfValues(unsigned short * values, const ULONG64 & valueCount, common::AbstractHdfProxy * proxy, const long & nullValue)
{
	hsize_t valueCountPerDimension[3] = { valueCount };
	pushBackUShortHdf5ArrayOfValues(values, valueCountPerDimension, 1, proxy, nullValue);
}

void CategoricalProperty::pushBackUShortHdf5Array2dOfValues(unsigned short * values, const ULONG64 & valueCountInFastestDim, const ULONG64 & valueCountInSlowestDim, common::AbstractHdfProxy * proxy, const long & nullValue)
{
	hsize_t valueCountPerDimension[3] = { valueCountInSlowestDim, valueCountInFastestDim };
	pushBackUShortHdf5ArrayOfValues(values, valueCountPerDimension, 2, proxy, nullValue);
}

void CategoricalProperty::pushBackUShortHdf5Array3dOfValues(unsigned short * values, const ULONG64 & valueCountInFastestDim, const ULONG64 & valueCountInMiddleDim, const ULONG64 & valueCountInSlowestDim, common::AbstractHdfProxy * proxy, const long & nullValue)
{
	hsize_t valueCountPerDimension[3] = { valueCountInSlowestDim, valueCountInMiddleDim, valueCountInFastestDim };
	pushBackUShortHdf5ArrayOfValues(values, valueCountPerDimension, 3, proxy, nullValue);
}

void CategoricalProperty::pushBackUShortHdf5ArrayOfValues(unsigned short * values, unsigned long long * numValues, const unsigned int & numDimensionsInArray, common::AbstractHdfProxy* proxy, const unsigned short & nullValue)
{
	const string datasetName = pushBackRefToExistingDataset(proxy, "", nullValue);

	// HDF
	proxy->writeArrayNd(gsoapProxy2_0_1->uuid,
		datasetName,
		H5T_NATIVE_USHORT,
		values,
		numValues, numDimensionsInArray);
}

std::string CategoricalProperty::pushBackRefToExistingDataset(common::AbstractHdfProxy* hdfProxy, const std::string & datasetName, const long & nullValue)
{
	return pushBackRefToExistingIntegerDataset(hdfProxy, datasetName, nullValue);
}

std::string CategoricalProperty::getStringLookupUuid() const
{
	return static_cast<_resqml2__CategoricalProperty*>(gsoapProxy2_0_1)->Lookup->UUID;
}

bool CategoricalProperty::validatePropertyKindAssociation(resqml2::PropertyKind* pk)
{
	if (pk == nullptr) {
		throw invalid_argument("The property kind to validate cannot be null.");
	}

	if (!pk->isPartial()) {
		if (pk->isAbstract()) {
			epcDocument->addWarning("The categorical property " + getUuid() + " cannot be associated to a local property kind " + pk->getUuid() + " which is abstract. This property will be assumed to be a partial one.");
			changeToPartialObject();
			return false;
		}
		if (epcDocument->getPropertyKindMapper() != nullptr) {
			if (!pk->isChildOf(resqml2__ResqmlPropertyKind__categorical)) {
				if (!pk->isChildOf(resqml2__ResqmlPropertyKind__discrete)) {
					epcDocument->addWarning("The categorical property " + getUuid() + " cannot be associated to a local property kind " + pk->getUuid() + " which does not derive from the discrete or categorical standard property kind. This property will be assumed to be a partial one.");
					changeToPartialObject();
					return false;
				}
				else {
					epcDocument->addWarning("The categorical property " + getUuid() + " is associated to a discrete local property kind " + pk->getUuid() + ".");
				}
			}
		}
		else {
			epcDocument->addWarning("Cannot verify if the local property kind " + pk->getUuid() + " of the categorical property " + getUuid() + " is right because no property kind mapping files have been loaded.");
		}
	}

	return true;
}

bool CategoricalProperty::validatePropertyKindAssociation(const gsoap_resqml2_0_1::resqml2__ResqmlPropertyKind & pk)
{
	PropertyKindMapper* pkMapper = epcDocument->getPropertyKindMapper();
	if (pkMapper != nullptr) {
		if (pkMapper->isAbstract(pk)) {
			epcDocument->addWarning("The categorical property " + getUuid() + " cannot be associated to a resqml property kind \"" + epcDocument->getEnergisticsPropertyKindName(pk) + "\" which is abstract. This property will be assumed to be a partial one.");
			changeToPartialObject();
			return false;
		}
		if (!pkMapper->isChildOf(pk, resqml2__ResqmlPropertyKind__categorical)) {
			if (!pkMapper->isChildOf(pk, resqml2__ResqmlPropertyKind__discrete)) {
				epcDocument->addWarning("The categorical property " + getUuid() + " cannot be associated to a resqml property kind \"" + epcDocument->getEnergisticsPropertyKindName(pk) + "\" which does not derive from the discrete or categorical standard property kind. This property will be assumed to be a partial one.");
				changeToPartialObject();
				return false;
			}
			else {
				getEpcDocument()->addWarning("The categorical property " + getUuid() + " is associated to a discrete resqml property kind \"" + epcDocument->getEnergisticsPropertyKindName(pk) + "\".");
			}
		}
	}
	else {
		epcDocument->addWarning("Cannot verify if the resqml property kind \"" + epcDocument->getEnergisticsPropertyKindName(pk) + "\" of the categorical property " + getUuid() + " is right because no property kind mapping files have been loaded.");
	}

	return true;
}
