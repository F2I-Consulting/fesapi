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
#include "AbstractSurfaceFrameworkRepresentation.h"

#include <limits>
#include <stdexcept>

#include "H5Tpublic.h"

#include "../eml2/AbstractHdfProxy.h"

using namespace std;
using namespace RESQML2_NS;
using namespace gsoap_resqml2_0_1;
using namespace gsoap_eml2_3;

void AbstractSurfaceFrameworkRepresentation::pushBackContactIdentity(
	gsoap_resqml2_0_1::resqml20__IdentityKind kind,
	unsigned int contactCount, int const* contactIndices,
	EML2_NS::AbstractHdfProxy * proxy)
{
	if (proxy == nullptr) {
		proxy = getRepository()->getDefaultHdfProxy();
		if (proxy == nullptr) {
			throw std::invalid_argument("A (default) HDF Proxy must be provided.");
		}
	}

	std::string datasetName;
	if (gsoapProxy2_0_1 != nullptr) {
		resqml20__AbstractSurfaceFrameworkRepresentation* orgRep = static_cast<resqml20__AbstractSurfaceFrameworkRepresentation*>(gsoapProxy2_0_1);

		resqml20__ContactIdentity * contactIdentity = soap_new_resqml20__ContactIdentity(gsoapProxy2_0_1->soap);
		contactIdentity->IdentityKind = kind;

		// ListOfContactRepresentations handling
		resqml20__IntegerHdf5Array * xmlListOfContactRepresentations = soap_new_resqml20__IntegerHdf5Array(gsoapProxy2_0_1->soap);
		xmlListOfContactRepresentations->NullValue = -1; // Arbitrarily decided to something almost impossible since it has no interest to write index null value in this method
		xmlListOfContactRepresentations->Values = soap_new_eml20__Hdf5Dataset(gsoapProxy2_0_1->soap);
		xmlListOfContactRepresentations->Values->HdfProxy = proxy->newResqmlReference();
		datasetName = "contactIdentity_listOfContactRep_" + std::to_string(orgRep->ContactIdentity.size());
		xmlListOfContactRepresentations->Values->PathInHdfFile = getHdfGroup() + "/" + datasetName;
		contactIdentity->ListOfContactRepresentations = xmlListOfContactRepresentations;
		orgRep->ContactIdentity.push_back(contactIdentity);
	}
	else if (gsoapProxy2_3 != nullptr) {
		resqml22__AbstractSurfaceFrameworkRepresentation* orgRep = static_cast<resqml22__AbstractSurfaceFrameworkRepresentation*>(gsoapProxy2_3);

		resqml22__ContactIdentity * contactIdentity = soap_new_resqml22__ContactIdentity(gsoapProxy2_3->soap);
		contactIdentity->IdentityKind = static_cast<resqml22__IdentityKind>(kind);

		// ListOfContactRepresentations handling
		eml23__IntegerExternalArray * xmlListOfContactRepresentations = soap_new_eml23__IntegerExternalArray(gsoapProxy2_3->soap);
		xmlListOfContactRepresentations->NullValue = -1; // Arbitrarily decided to something almost impossible since it has no interest to write index null value in this method
		xmlListOfContactRepresentations->Values = soap_new_eml23__ExternalDataArray(gsoapProxy2_3->soap);
		datasetName = "contactIdentity_listOfContactRep_" + std::to_string(orgRep->ContactIdentity.size());
		xmlListOfContactRepresentations->Values->ExternalDataArrayPart.push_back(createExternalDataArrayPart(getHdfGroup() + "/" + datasetName, contactCount, proxy));
		contactIdentity->ContactIndices = xmlListOfContactRepresentations;
		orgRep->ContactIdentity.push_back(contactIdentity);
	}
	else {
		throw std::logic_error("Unknown RESQML version");
	}

	// ************ HDF *************
	hsize_t dimContactRepresentations = contactCount;
	proxy->writeArrayNd(getHdfGroup(),
		datasetName, H5T_NATIVE_UINT,
		contactIndices,
		&dimContactRepresentations, 1);
}

void AbstractSurfaceFrameworkRepresentation::pushBackContactIdentity(
	gsoap_resqml2_0_1::resqml20__IdentityKind kind,
	unsigned int contactCount, int const* contactIndices,
	unsigned int identicalNodesCount, int const* identicalNodesIndexes, EML2_NS::AbstractHdfProxy * proxy)
{
	if (proxy == nullptr) {
		proxy = getRepository()->getDefaultHdfProxy();
		if (proxy == nullptr) {
			throw std::invalid_argument("A (default) HDF Proxy must be provided.");
		}
	}

	std::string datasetNameForHdfContactRepresentations;
	std::string datasetNameForHdfIdenticalNodes;
	if (gsoapProxy2_0_1 != nullptr) {
		resqml20__AbstractSurfaceFrameworkRepresentation* orgRep = static_cast<resqml20__AbstractSurfaceFrameworkRepresentation*>(gsoapProxy2_0_1);

		resqml20__ContactIdentity * contactIdentity = soap_new_resqml20__ContactIdentity(gsoapProxy2_0_1->soap);
		contactIdentity->IdentityKind = kind;

		// ListOfContactRepresentations handling
		resqml20__IntegerHdf5Array * xmlListOfContactRepresentations = soap_new_resqml20__IntegerHdf5Array(gsoapProxy2_0_1->soap);
		xmlListOfContactRepresentations->NullValue = -1; // Arbitrarily decided to something almost impossible since it has no interest to cell index null value in this method
		xmlListOfContactRepresentations->Values = soap_new_eml20__Hdf5Dataset(gsoapProxy2_0_1->soap);
		xmlListOfContactRepresentations->Values->HdfProxy = proxy->newResqmlReference();
		datasetNameForHdfContactRepresentations = "contactIdentity_listOfContactRep_" + std::to_string(orgRep->ContactIdentity.size());
		xmlListOfContactRepresentations->Values->PathInHdfFile = getHdfGroup() + "/" + datasetNameForHdfContactRepresentations;
		contactIdentity->ListOfContactRepresentations = xmlListOfContactRepresentations;

		// ListOfIdenticalNodes handling
		resqml20__IntegerHdf5Array * xmlListOfIdenticalNodes = soap_new_resqml20__IntegerHdf5Array(gsoapProxy2_0_1->soap);
		xmlListOfIdenticalNodes->NullValue = -1; // Arbitrarily decided to something almost impossible since it has no interest to write index null value in this method
		xmlListOfIdenticalNodes->Values = soap_new_eml20__Hdf5Dataset(gsoapProxy2_0_1->soap);
		xmlListOfIdenticalNodes->Values->HdfProxy = proxy->newResqmlReference();
		datasetNameForHdfIdenticalNodes = "contactIdentity_listOfIdenticalNodes_" + std::to_string(orgRep->ContactIdentity.size());
		xmlListOfIdenticalNodes->Values->PathInHdfFile = getHdfGroup() + "/" + datasetNameForHdfIdenticalNodes;
		contactIdentity->ListOfIdenticalNodes = xmlListOfIdenticalNodes;

		orgRep->ContactIdentity.push_back(contactIdentity);
	}
	else if (gsoapProxy2_3 != nullptr) {
		resqml22__AbstractSurfaceFrameworkRepresentation* orgRep = static_cast<resqml22__AbstractSurfaceFrameworkRepresentation*>(gsoapProxy2_3);

		resqml22__ContactIdentity * contactIdentity = soap_new_resqml22__ContactIdentity(gsoapProxy2_3->soap);
		contactIdentity->IdentityKind = static_cast<resqml22__IdentityKind>(kind);

		// ListOfContactRepresentations handling
		eml23__IntegerExternalArray * xmlListOfContactRepresentations = soap_new_eml23__IntegerExternalArray(gsoapProxy2_3->soap);
		xmlListOfContactRepresentations->NullValue = -1; // Arbitrarily decided to something almost impossible since it has no interest to write index null value in this method
		xmlListOfContactRepresentations->Values = soap_new_eml23__ExternalDataArray(gsoapProxy2_3->soap);
		datasetNameForHdfContactRepresentations = "contactIdentity_listOfContactRep_" + std::to_string(orgRep->ContactIdentity.size());
		auto* daPart = createExternalDataArrayPart(getHdfGroup() + "/" + datasetNameForHdfContactRepresentations, contactCount, proxy);
		xmlListOfContactRepresentations->Values->ExternalDataArrayPart.push_back(daPart);
		contactIdentity->ContactIndices = xmlListOfContactRepresentations;

		// ListOfIdenticalNodes handling
		eml23__IntegerExternalArray * xmlListOfIdenticalNodes = soap_new_eml23__IntegerExternalArray(gsoapProxy2_3->soap);
		xmlListOfIdenticalNodes->NullValue = -1; // Arbitrarily decided to something almost impossible since it has no interest to write index null value in this method
		xmlListOfIdenticalNodes->Values = soap_new_eml23__ExternalDataArray(gsoapProxy2_3->soap);
		datasetNameForHdfIdenticalNodes = "contactIdentity_listOfIdenticalNodes_" + std::to_string(orgRep->ContactIdentity.size());
		daPart = createExternalDataArrayPart(getHdfGroup() + "/" + datasetNameForHdfIdenticalNodes, identicalNodesCount* contactCount, proxy);
		xmlListOfIdenticalNodes->Values->ExternalDataArrayPart.push_back(daPart);
		contactIdentity->IdenticalNodeIndices = xmlListOfIdenticalNodes;

		orgRep->ContactIdentity.push_back(contactIdentity);
	}
	else {
		throw std::logic_error("Unknown RESQML version");
	}

	// ************ HDF *************
	hsize_t dimContactRepresentations = contactCount;
	proxy->writeArrayNd(getHdfGroup(),
		datasetNameForHdfContactRepresentations, H5T_NATIVE_UINT,
		contactIndices,
		&dimContactRepresentations, 1);

	// ************ HDF *************
	hsize_t dimIdenticalNodes[2] = { identicalNodesCount, contactCount };
	proxy->writeArrayNd(getHdfGroup(),
		datasetNameForHdfIdenticalNodes, H5T_NATIVE_UINT,
		identicalNodesIndexes,
		dimIdenticalNodes, 2);
}

unsigned int AbstractSurfaceFrameworkRepresentation::getContactIdentityCount() const
{
	size_t result;
	if (gsoapProxy2_0_1 != nullptr) {
		result = static_cast<resqml20__AbstractSurfaceFrameworkRepresentation*>(gsoapProxy2_0_1)->ContactIdentity.size();
	}
	else if (gsoapProxy2_3 != nullptr) {
		result = static_cast<resqml22__AbstractSurfaceFrameworkRepresentation*>(gsoapProxy2_3)->ContactIdentity.size();
	}
	else {
		throw std::logic_error("Unknown RESQML version");
	}

	if (result > (std::numeric_limits<unsigned int>::max)()) {
		throw range_error("There are too much contact identities in this surface framework");
	}

	return static_cast<unsigned int>(result);
}

gsoap_resqml2_0_1::resqml20__ContactIdentity* AbstractSurfaceFrameworkRepresentation::getContactIdentity201(unsigned int ciIndex) const
{
	resqml20__AbstractSurfaceFrameworkRepresentation* orgRep = static_cast<resqml20__AbstractSurfaceFrameworkRepresentation*>(gsoapProxy2_0_1);

	if (ciIndex >= orgRep->ContactIdentity.size()) {
		throw out_of_range("The index of the contact identity is out of range.");
	}

	return orgRep->ContactIdentity[ciIndex];
}

gsoap_eml2_3::resqml22__ContactIdentity* AbstractSurfaceFrameworkRepresentation::getContactIdentity22(unsigned int ciIndex) const
{
	resqml22__AbstractSurfaceFrameworkRepresentation* orgRep = static_cast<resqml22__AbstractSurfaceFrameworkRepresentation*>(gsoapProxy2_3);

	if (ciIndex >= orgRep->ContactIdentity.size()) {
		throw out_of_range("The index of the contact identity is out of range.");
	}

	return orgRep->ContactIdentity[ciIndex];
}

gsoap_resqml2_0_1::resqml20__IdentityKind AbstractSurfaceFrameworkRepresentation::getContactIdentityKind(unsigned int ciIndex) const
{
	if (gsoapProxy2_0_1 != nullptr) {
		return getContactIdentity201(ciIndex)->IdentityKind;
	}
	else if (gsoapProxy2_3 != nullptr) {
		return static_cast<gsoap_resqml2_0_1::resqml20__IdentityKind>(getContactIdentity22(ciIndex)->IdentityKind);
	}
	else {
		throw std::logic_error("Unknown RESQML version");
	}
}

unsigned int AbstractSurfaceFrameworkRepresentation::getContactCountInContactIdentity(unsigned int ciIndex) const
{
	uint64_t result;
	if (gsoapProxy2_0_1 != nullptr) {
		result = getCountOfIntegerArray(getContactIdentity201(ciIndex)->ListOfContactRepresentations);
	}
	else if (gsoapProxy2_3 != nullptr) {
		result = getCountOfArray(getContactIdentity22(ciIndex)->ContactIndices);
	}
	else {
		throw std::logic_error("Unknown RESQML version");
	}

	if (result > (std::numeric_limits<unsigned int>::max)()) {
		throw range_error("There are too much contact representations for fesapi");
	}

	return static_cast<unsigned int>(result);
}

void AbstractSurfaceFrameworkRepresentation::getContactIndices(unsigned int ciIndex, unsigned int * contactRepIndices) const
{
	if (gsoapProxy2_0_1 != nullptr) {
		readArrayNdOfUInt32Values(getContactIdentity201(ciIndex)->ListOfContactRepresentations, contactRepIndices);
	}
	else if (gsoapProxy2_3 != nullptr) {
		readArrayNdOfUInt32Values(getContactIdentity22(ciIndex)->ContactIndices, contactRepIndices);
	}
	else {
		throw std::logic_error("Unknown RESQML version");
	}
}

bool AbstractSurfaceFrameworkRepresentation::areAllContactNodesIdentical(unsigned int ciIndex) const
{
	if (gsoapProxy2_0_1 != nullptr) {
		return getContactIdentity201(ciIndex)->ListOfIdenticalNodes == nullptr;
	}
	else if (gsoapProxy2_3 != nullptr) {
		return getContactIdentity22(ciIndex)->IdenticalNodeIndices == nullptr;
	}
	else {
		throw std::logic_error("Unknown RESQML version");
	}
}

unsigned int AbstractSurfaceFrameworkRepresentation::getIdenticalContactNodeCount(unsigned int ciIndex) const
{
	if (areAllContactNodesIdentical(ciIndex)) {
		throw invalid_argument("The nodes are all identical");
	}

	uint64_t result;
	if (gsoapProxy2_0_1 != nullptr) {
		result = getCountOfIntegerArray(getContactIdentity201(ciIndex)->ListOfIdenticalNodes);
	}
	else if (gsoapProxy2_3 != nullptr) {
		result = getCountOfArray(getContactIdentity22(ciIndex)->IdenticalNodeIndices);
	}
	else {
		throw std::logic_error("Unknown RESQML version");
	}
	
	if (result > (std::numeric_limits<unsigned int>::max)()) {
		throw range_error("There are too much identical nodes for fesapi");
	}

	return static_cast<unsigned int>(result);
}

void AbstractSurfaceFrameworkRepresentation::getIdenticalContactNodeIndices(unsigned int ciIndex, unsigned int * nodeIndices) const
{
	if (areAllContactNodesIdentical(ciIndex)) {
		throw invalid_argument("The nodes are all identical");
	}

	if (gsoapProxy2_0_1 != nullptr) {
		readArrayNdOfUInt32Values(getContactIdentity201(ciIndex)->ListOfIdenticalNodes, nodeIndices);
	}
	else if (gsoapProxy2_3 != nullptr) {
		readArrayNdOfUInt32Values(getContactIdentity22(ciIndex)->IdenticalNodeIndices, nodeIndices);
	}
	else {
		throw std::logic_error("Unknown RESQML version");
	}
}
