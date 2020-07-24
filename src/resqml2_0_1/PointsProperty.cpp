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
using namespace RESQML2_0_1_NS;
using namespace gsoap_resqml2_0_1;

const char* PointsProperty::XML_NS = "resqml20";

PointsProperty::PointsProperty(RESQML2_NS::AbstractRepresentation * rep, const string & guid, const string & title,
	unsigned int dimension, gsoap_eml2_3::resqml22__IndexableElement attachmentKind, RESQML2_NS::AbstractLocal3dCrs* localCrs, resqml20__ResqmlPropertyKind energisticsPropertyKind)
{
	if (dimension == 0) {
		throw invalid_argument("The dimension cannot be zero.");
	}

	gsoapProxy2_0_1 = soap_new_resqml20__obj_USCOREPointsProperty(rep->getGsoapContext());
	_resqml20__PointsProperty* prop = static_cast<_resqml20__PointsProperty*>(gsoapProxy2_0_1);
	prop->IndexableElement = mapIndexableElement(attachmentKind);
	prop->Count = dimension;

	resqml20__StandardPropertyKind* xmlStandardPropKind = soap_new_resqml20__StandardPropertyKind(gsoapProxy2_0_1->soap);
	xmlStandardPropKind->Kind = energisticsPropertyKind;
	prop->PropertyKind = xmlStandardPropKind;

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "");

	setRepresentation(rep);
	setLocalCrs(localCrs);
}

PointsProperty::PointsProperty(RESQML2_NS::AbstractRepresentation * rep, const string & guid, const string & title,
	unsigned int dimension, gsoap_eml2_3::resqml22__IndexableElement attachmentKind, RESQML2_NS::AbstractLocal3dCrs* localCrs, EML2_NS::PropertyKind * localPropKind)
{
	if (dimension == 0) {
		throw invalid_argument("The dimension cannot be zero.");
	}

	gsoapProxy2_0_1 = soap_new_resqml20__obj_USCOREPointsProperty(rep->getGsoapContext());
	_resqml20__PointsProperty* prop = static_cast<_resqml20__PointsProperty*>(gsoapProxy2_0_1);
	prop->IndexableElement = mapIndexableElement(attachmentKind);
	prop->Count = dimension;

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "");

	setRepresentation(rep);
	setLocalCrs(localCrs);
	setPropertyKind(localPropKind);
}

unsigned int PointsProperty::getPatchCount() const
{
	size_t result = static_cast<gsoap_resqml2_0_1::_resqml20__PointsProperty*>(gsoapProxy2_0_1)->PatchOfPoints.size();

	if (result > (std::numeric_limits<unsigned int>::max)()) {
		throw out_of_range("The count of the patches is too big.");
	}

	return static_cast<unsigned int>(result);
}

EML2_NS::AbstractHdfProxy * PointsProperty::getDatasetOfPatch(unsigned int patchIndex, LONG64 & nullValue, std::string & dsPath) const
{
	if (patchIndex >= getPatchCount()) {
		throw out_of_range("The values property patch is out of range");
	}

	gsoap_resqml2_0_1::resqml20__PatchOfPoints* patch = static_cast<_resqml20__PointsProperty*>(gsoapProxy2_0_1)->PatchOfPoints[patchIndex];

	nullValue = (numeric_limits<long>::min)();
	int valuesType = patch->Points->soap_type();
	if (valuesType == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__Point3dHdf5Array) {
		dsPath = static_cast<gsoap_resqml2_0_1::resqml20__Point3dHdf5Array*>(patch->Points)->Coordinates->PathInHdfFile;
		return getHdfProxyFromDataset(static_cast<gsoap_resqml2_0_1::resqml20__Point3dHdf5Array*>(patch->Points)->Coordinates);
	}
	else {
		throw logic_error("Points property only support points given by means of a Point3dHdf5Array for now.");
	}
}

COMMON_NS::DataObjectReference PointsProperty::getHdfProxyDor(unsigned int patchIndex) const
{
	if (patchIndex >= getPatchCount()) {
		throw out_of_range("The values property patch is out of range");
	}

	gsoap_resqml2_0_1::resqml20__PatchOfPoints* patch = static_cast<_resqml20__PointsProperty*>(gsoapProxy2_0_1)->PatchOfPoints[patchIndex];

	int valuesType = patch->Points->soap_type();
	if (valuesType == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__Point3dHdf5Array) {
		return static_cast<gsoap_resqml2_0_1::resqml20__Point3dHdf5Array*>(patch->Points)->Coordinates->HdfProxy;
	}
	else {
		throw logic_error("Points property only support points given by means of a Point3dHdf5Array for now.");
	}
}

EML2_NS::AbstractHdfProxy* PointsProperty::getValuesHdfProxyAndDatasetPathOfPatch(unsigned int patchIndex, std::string & datasetPath) const
{
	if (patchIndex >= getPatchCount()) {
		throw out_of_range("The values property patch is out of range");
	}

	gsoap_resqml2_0_1::resqml20__PatchOfPoints* patch = static_cast<_resqml20__PointsProperty*>(gsoapProxy2_0_1)->PatchOfPoints[patchIndex];
	int valuesType = patch->Points->soap_type();
	if (valuesType == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__Point3dHdf5Array) {
		eml20__Hdf5Dataset const * dataset = static_cast<resqml20__Point3dHdf5Array*>(patch->Points)->Coordinates;
		datasetPath = dataset->PathInHdfFile;
		return getHdfProxyFromDataset(dataset);
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
	_resqml20__PointsProperty* prop = static_cast<_resqml20__PointsProperty*>(gsoapProxy2_0_1);

	gsoap_resqml2_0_1::resqml20__PatchOfPoints* patch = gsoap_resqml2_0_1::soap_new_resqml20__PatchOfPoints(gsoapProxy2_0_1->soap);
	patch->RepresentationPatchIndex = static_cast<ULONG64*>(soap_malloc(gsoapProxy2_0_1->soap, sizeof(ULONG64)));
	*(patch->RepresentationPatchIndex) = prop->PatchOfPoints.size();

	// XML
	gsoap_resqml2_0_1::resqml20__Point3dHdf5Array* xmlValues = gsoap_resqml2_0_1::soap_new_resqml20__Point3dHdf5Array(gsoapProxy2_0_1->soap);
	xmlValues->Coordinates = gsoap_resqml2_0_1::soap_new_eml20__Hdf5Dataset(gsoapProxy2_0_1->soap);
	xmlValues->Coordinates->HdfProxy = proxy->newResqmlReference();

	if (datasetName.empty()) {
		ostringstream ossForHdf;
		ossForHdf << "points_patch" << *(patch->RepresentationPatchIndex);
		xmlValues->Coordinates->PathInHdfFile = getHdfGroup() + "/" + ossForHdf.str();
	}
	else {
		xmlValues->Coordinates->PathInHdfFile = datasetName;
	}

	patch->Points = xmlValues;

	prop->PatchOfPoints.push_back(patch);

	return xmlValues->Coordinates->PathInHdfFile;
}

gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind PointsProperty::getEnergisticsPropertyKind() const
{
	return getEnergisticsPropertyKind201();
}
