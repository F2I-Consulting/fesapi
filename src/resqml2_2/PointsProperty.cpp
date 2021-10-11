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
#include "PointsProperty.h"

#include "../resqml2/AbstractRepresentation.h"

#include "../eml2/AbstractHdfProxy.h"
#include "../eml2/PropertyKind.h"

using namespace std;
using namespace RESQML2_2_NS;
using namespace gsoap_eml2_3;

const char* PointsProperty::XML_NS = "resqml22";

PointsProperty::PointsProperty(RESQML2_NS::AbstractRepresentation * rep, const string & guid, const string & title,
	gsoap_eml2_3::eml23__IndexableElement attachmentKind, EML2_NS::AbstractLocal3dCrs* localCrs, EML2_NS::PropertyKind * localPropKind)
{
	gsoapProxy2_3 = soap_new_resqml22__PointsProperty(rep->getGsoapContext());
	_resqml22__PointsProperty* prop = static_cast<_resqml22__PointsProperty*>(gsoapProxy2_3);
	prop->IndexableElement = attachmentKind;
	prop->ValueCountPerIndexableElement = { 1 };

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "");

	rep->getRepository()->addDataObject(this);
	setRepresentation(rep);
	setLocalCrs(localCrs);
	setPropertyKind(localPropKind);
}

unsigned int PointsProperty::getPatchCount() const
{
	size_t result = static_cast<_resqml22__PointsProperty*>(gsoapProxy2_3)->PointsForPatch.size();

	if (result > (std::numeric_limits<unsigned int>::max)()) {
		throw out_of_range("The count of the patches is too big.");
	}

	return static_cast<unsigned int>(result);
}


EML2_NS::AbstractHdfProxy * PointsProperty::getDatasetOfPatch(unsigned int patchIndex, int64_t & nullValue, std::string & dsPath) const
{
	if (patchIndex >= getPatchCount()) {
		throw out_of_range("The values property patch is out of range");
	}

	nullValue = (numeric_limits<long>::min)();
	auto const* patch = static_cast<_resqml22__PointsProperty*>(gsoapProxy2_3)->PointsForPatch[patchIndex];
	if (patch->soap_type() == SOAP_TYPE_gsoap_eml2_3_resqml22__Point3dExternalArray) {
		dsPath = static_cast<gsoap_eml2_3::resqml22__Point3dExternalArray const*>(patch)->Coordinates->ExternalDataArrayPart[0]->PathInExternalFile;
		return getOrCreateHdfProxyFromDataArrayPart(static_cast<gsoap_eml2_3::resqml22__Point3dExternalArray const*>(patch)->Coordinates->ExternalDataArrayPart[0]);
	}
	else {
		throw logic_error("Points property only support points given by means of a Point3dExternalArray for now.");
	}
}

COMMON_NS::DataObjectReference PointsProperty::getHdfProxyDor(unsigned int patchIndex) const
{
	if (patchIndex >= getPatchCount()) {
		throw out_of_range("The values property patch is out of range");
	}

	auto const* patch = static_cast<_resqml22__PointsProperty*>(gsoapProxy2_3)->PointsForPatch[patchIndex];
	if (patch->soap_type() == SOAP_TYPE_gsoap_eml2_3_resqml22__Point3dExternalArray) {
		return COMMON_NS::DataObjectReference(getOrCreateHdfProxyFromDataArrayPart(static_cast<gsoap_eml2_3::resqml22__Point3dExternalArray const*>(patch)->Coordinates->ExternalDataArrayPart[0]));
	}
	else {
		throw logic_error("Points property only support points given by means of a Point3dExternalArray for now.");
	}
}

EML2_NS::AbstractHdfProxy* PointsProperty::getValuesHdfProxyAndDatasetPathOfPatch(unsigned int patchIndex, std::string & datasetPath) const
{
	if (patchIndex >= getPatchCount()) {
		throw out_of_range("The values property patch is out of range");
	}

	_resqml22__PointsProperty const* prop = static_cast<_resqml22__PointsProperty*>(gsoapProxy2_3);
	if (prop->PointsForPatch[patchIndex]->soap_type() == SOAP_TYPE_gsoap_eml2_3_resqml22__Point3dExternalArray) {
		eml23__ExternalDataArrayPart const* daPart = static_cast<resqml22__Point3dExternalArray const*>(prop->PointsForPatch[patchIndex])->Coordinates->ExternalDataArrayPart[0];
		datasetPath = daPart->PathInExternalFile;
		return getOrCreateHdfProxyFromDataArrayPart(daPart);
	}

	return nullptr;
}

std::string PointsProperty::pushBackRefToExistingDataset(EML2_NS::AbstractHdfProxy* proxy, const std::string & datasetName)
{
	if (proxy == nullptr) {
		proxy = getRepository()->getDefaultHdfProxy();
		if (proxy == nullptr) {
			throw std::invalid_argument("A (default) HDF Proxy must be provided.");
		}
	}
	if (datasetName.empty()) {
		throw std::invalid_argument("The dataset name wher to store of the points property cannot be empty.");
	}

	getRepository()->addRelationship(this, proxy);
	_resqml22__PointsProperty* prop = static_cast<_resqml22__PointsProperty*>(gsoapProxy2_3);

	// XML
	auto* externalArray = soap_new_resqml22__Point3dExternalArray(gsoapProxy2_3->soap);
	externalArray->Coordinates = soap_new_eml23__ExternalDataArray(gsoapProxy2_3->soap);
	externalArray->Coordinates->ExternalDataArrayPart.push_back(createExternalDataArrayPart(datasetName, proxy->getElementCount(datasetName), proxy));

	prop->PointsForPatch.push_back(externalArray);

	return datasetName;
}
