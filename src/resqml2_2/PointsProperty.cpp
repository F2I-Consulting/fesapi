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
	unsigned int dimension, gsoap_eml2_3::resqml22__IndexableElement attachmentKind, RESQML2_NS::AbstractLocal3dCrs* localCrs, EML2_NS::PropertyKind * localPropKind)
{
	if (dimension == 0) {
		throw invalid_argument("The dimension cannot be zero.");
	}

	gsoapProxy2_3 = soap_new_resqml22__PointsProperty(rep->getGsoapContext());
	_resqml22__PointsProperty* prop = static_cast<_resqml22__PointsProperty*>(gsoapProxy2_3);
	prop->IndexableElement = attachmentKind;
	if (dimension > 1) {
		prop->ValueCountPerIndexableElement = static_cast<uint64_t*>(soap_malloc(gsoapProxy2_3->soap, sizeof(uint64_t)));
		*prop->ValueCountPerIndexableElement = dimension;
	}

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "");

	setRepresentation(rep);
	setLocalCrs(localCrs);
	setPropertyKind(localPropKind);
}

unsigned int PointsProperty::getPatchCount() const
{
	size_t result = static_cast<_resqml22__PointsProperty*>(gsoapProxy2_3)->PatchOfPoints.size();

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
	auto patch = static_cast<_resqml22__PointsProperty*>(gsoapProxy2_3)->PatchOfPoints[patchIndex]->Points;
	int valuesType = patch->soap_type();
	if (valuesType == SOAP_TYPE_gsoap_eml2_3_resqml22__Point3dExternalArray) {
		dsPath = static_cast<gsoap_eml2_3::resqml22__Point3dExternalArray*>(patch)->Coordinates->ExternalFileProxy[0]->PathInExternalFile;
		return getHdfProxyFromDataset(static_cast<gsoap_eml2_3::resqml22__Point3dExternalArray*>(patch)->Coordinates->ExternalFileProxy[0]);
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

	auto patch = static_cast<_resqml22__PointsProperty*>(gsoapProxy2_3)->PatchOfPoints[patchIndex]->Points;
	int valuesType = patch->soap_type();
	if (valuesType == SOAP_TYPE_gsoap_eml2_3_resqml22__Point3dExternalArray) {
		return static_cast<gsoap_eml2_3::resqml22__Point3dExternalArray*>(patch)->Coordinates->ExternalFileProxy[0]->EpcExternalPartReference;
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

	_resqml22__PointsProperty* prop = static_cast<_resqml22__PointsProperty*>(gsoapProxy2_3);
	if (prop->PatchOfPoints[patchIndex]->Points->soap_type() == SOAP_TYPE_gsoap_eml2_3_resqml22__Point3dExternalArray) {
		eml23__ExternalDatasetPart * dsPart = static_cast<resqml22__Point3dExternalArray*>(prop->PatchOfPoints[patchIndex]->Points)->Coordinates->ExternalFileProxy[0];
		datasetPath = dsPart->PathInExternalFile;
		return getHdfProxyFromDataset(dsPart);
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
	getRepository()->addRelationship(this, proxy);
	_resqml22__PointsProperty* prop = static_cast<_resqml22__PointsProperty*>(gsoapProxy2_3);

	// XML
	ostringstream oss;
	resqml22__PatchOfPoints* pathOfPts = soap_new_resqml22__PatchOfPoints(gsoapProxy2_3->soap);
	auto externalArray = soap_new_resqml22__Point3dExternalArray(gsoapProxy2_3->soap);
	externalArray->Coordinates = soap_new_eml23__ExternalDataset(gsoapProxy2_3->soap);
	pathOfPts->Points = externalArray;
	auto dsPart = soap_new_eml23__ExternalDatasetPart(gsoapProxy2_3->soap);
	dsPart->EpcExternalPartReference = proxy->newEml23Reference();

	if (datasetName.empty()) {
		ostringstream ossForHdf;
		ossForHdf << "points_patch" << prop->PatchOfPoints.size();
		dsPart->PathInExternalFile = getHdfGroup() + "/" + ossForHdf.str();
	}
	else {
		dsPart->PathInExternalFile = datasetName;
	}
	externalArray->Coordinates->ExternalFileProxy.push_back(dsPart);

	prop->PatchOfPoints.push_back(pathOfPts);

	return dsPart->PathInExternalFile;
}
