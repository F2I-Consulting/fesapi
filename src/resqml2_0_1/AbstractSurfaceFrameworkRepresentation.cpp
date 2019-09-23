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
#include "resqml2_0_1/AbstractSurfaceFrameworkRepresentation.h"

#include <stdexcept>
#include <sstream>

#include "H5Tpublic.h"

#include "resqml2_0_1/StructuralOrganizationInterpretation.h"
#include "common/AbstractHdfProxy.h"

using namespace std;
using namespace RESQML2_0_1_NS;
using namespace gsoap_resqml2_0_1;

AbstractSurfaceFrameworkRepresentation::AbstractSurfaceFrameworkRepresentation() {}

void AbstractSurfaceFrameworkRepresentation::pushBackContactIdentity(
	gsoap_resqml2_0_1::resqml20__IdentityKind kind,
	unsigned int contactCount, int * contactIndices,
	COMMON_NS::AbstractHdfProxy * proxy)
{
	resqml20__AbstractSurfaceFrameworkRepresentation* orgRep = static_cast<resqml20__AbstractSurfaceFrameworkRepresentation*>(gsoapProxy2_0_1);

	resqml20__ContactIdentity * contactIdentity = soap_new_resqml20__ContactIdentity(gsoapProxy2_0_1->soap, 1);
	contactIdentity->IdentityKind = kind;

	// ListOfContactRepresentations handling
	resqml20__IntegerHdf5Array * xmlListOfContactRepresentations = soap_new_resqml20__IntegerHdf5Array(gsoapProxy2_0_1->soap, 1);
	xmlListOfContactRepresentations->NullValue = (std::numeric_limits<unsigned int>::max)();
	xmlListOfContactRepresentations->Values = soap_new_eml20__Hdf5Dataset(gsoapProxy2_0_1->soap, 1);
	xmlListOfContactRepresentations->Values->HdfProxy = proxy->newResqmlReference();
	ostringstream ossForHdfContactRepresentations;
	ossForHdfContactRepresentations << "contactIdentity_listOfContactRep_" << orgRep->ContactIdentity.size();
	xmlListOfContactRepresentations->Values->PathInHdfFile = "/RESQML/" + gsoapProxy2_0_1->uuid + "/" + ossForHdfContactRepresentations.str();
	contactIdentity->ListOfContactRepresentations = xmlListOfContactRepresentations;
	// ************ HDF *************
	hsize_t dimContactRepresentations[1] = { contactCount };
	proxy->writeArrayNd(gsoapProxy2_0_1->uuid,
		ossForHdfContactRepresentations.str(), H5T_NATIVE_UINT,
		contactIndices,
		dimContactRepresentations, 1);

	orgRep->ContactIdentity.push_back(contactIdentity);
}

void AbstractSurfaceFrameworkRepresentation::pushBackContactIdentity(
	gsoap_resqml2_0_1::resqml20__IdentityKind kind,
	unsigned int contactCount, int * contactIndices,
	unsigned int identicalNodesCount, int * identicalNodesIndexes, COMMON_NS::AbstractHdfProxy * proxy)
{
	resqml20__AbstractSurfaceFrameworkRepresentation* orgRep = static_cast<resqml20__AbstractSurfaceFrameworkRepresentation*>(gsoapProxy2_0_1);

	resqml20__ContactIdentity * contactIdentity = soap_new_resqml20__ContactIdentity(gsoapProxy2_0_1->soap, 1);
	contactIdentity->IdentityKind = kind;

	// ListOfContactRepresentations handling
	resqml20__IntegerHdf5Array * xmlListOfContactRepresentations = soap_new_resqml20__IntegerHdf5Array(gsoapProxy2_0_1->soap, 1);
	xmlListOfContactRepresentations->NullValue = (std::numeric_limits<unsigned int>::max)();
	xmlListOfContactRepresentations->Values = soap_new_eml20__Hdf5Dataset(gsoapProxy2_0_1->soap, 1);
	xmlListOfContactRepresentations->Values->HdfProxy = proxy->newResqmlReference();
	ostringstream ossForHdfContactRepresentations;
	ossForHdfContactRepresentations << "contactIdentity_listOfContactRep_" << orgRep->ContactIdentity.size();
	xmlListOfContactRepresentations->Values->PathInHdfFile = "/RESQML/" + gsoapProxy2_0_1->uuid + "/" + ossForHdfContactRepresentations.str();
	contactIdentity->ListOfContactRepresentations = xmlListOfContactRepresentations;
	// ************ HDF *************
	hsize_t dimContactRepresentations[1] = { contactCount };
	proxy->writeArrayNd(gsoapProxy2_0_1->uuid,
		ossForHdfContactRepresentations.str(), H5T_NATIVE_UINT,
		contactIndices,
		dimContactRepresentations, 1);

	// ListOfIdenticalNodes handling
	resqml20__IntegerHdf5Array * xmlListOfIdenticalNodes = soap_new_resqml20__IntegerHdf5Array(gsoapProxy2_0_1->soap, 1);
	xmlListOfIdenticalNodes->NullValue = (std::numeric_limits<unsigned int>::max)();
	xmlListOfIdenticalNodes->Values = soap_new_eml20__Hdf5Dataset(gsoapProxy2_0_1->soap, 1);
	xmlListOfIdenticalNodes->Values->HdfProxy = proxy->newResqmlReference();
	ostringstream ossForHdfIdenticalNodes;
	ossForHdfIdenticalNodes << "contactIdentity_listOfIdenticalNodes_" << orgRep->ContactIdentity.size();
	xmlListOfIdenticalNodes->Values->PathInHdfFile = "/RESQML/" + gsoapProxy2_0_1->uuid + "/" + ossForHdfIdenticalNodes.str();
	contactIdentity->ListOfIdenticalNodes = xmlListOfIdenticalNodes;
	// ************ HDF *************
	hsize_t dimIdenticalNodes[2] = { identicalNodesCount, contactCount };
	proxy->writeArrayNd(gsoapProxy2_0_1->uuid,
		ossForHdfIdenticalNodes.str(), H5T_NATIVE_UINT,
		identicalNodesIndexes,
		dimIdenticalNodes, 2);

	orgRep->ContactIdentity.push_back(contactIdentity);
}

unsigned int AbstractSurfaceFrameworkRepresentation::getContactIdentityCount() const
{
	resqml20__AbstractSurfaceFrameworkRepresentation* orgRep = static_cast<resqml20__AbstractSurfaceFrameworkRepresentation*>(gsoapProxy2_0_1);

	if (orgRep->ContactIdentity.size() > (std::numeric_limits<unsigned int>::max)()) {
		throw range_error("There are too much contact identities in this surface framework");
	}

	return static_cast<unsigned int>(orgRep->ContactIdentity.size());
}

gsoap_resqml2_0_1::resqml20__ContactIdentity* AbstractSurfaceFrameworkRepresentation::getContactIdentity(unsigned int ciIndex) const
{
	resqml20__AbstractSurfaceFrameworkRepresentation* orgRep = static_cast<resqml20__AbstractSurfaceFrameworkRepresentation*>(gsoapProxy2_0_1);

	if (ciIndex >= orgRep->ContactIdentity.size()) {
		throw range_error("The index of the contact identity is out of range.");
	}

	return orgRep->ContactIdentity[ciIndex];
}

gsoap_resqml2_0_1::resqml20__IdentityKind AbstractSurfaceFrameworkRepresentation::getContactIdentityKind(unsigned int ciIndex) const
{
	return getContactIdentity(ciIndex)->IdentityKind;
}

unsigned int AbstractSurfaceFrameworkRepresentation::getContactCountInContactIdentity(unsigned int ciIndex) const
{
	ULONG64 result = getCountOfIntegerArray(getContactIdentity(ciIndex)->ListOfContactRepresentations);
	if (result > (std::numeric_limits<unsigned int>::max)()) {
		throw range_error("There are too much contact representations for fesapi");
	}

	return static_cast<unsigned int>(result);
}

void AbstractSurfaceFrameworkRepresentation::getContactIndices(unsigned int ciIndex, unsigned int * contactRepIndices) const
{
	readArrayNdOfUIntValues(getContactIdentity(ciIndex)->ListOfContactRepresentations, contactRepIndices);
}

bool AbstractSurfaceFrameworkRepresentation::areAllContactNodesIdentical(unsigned int ciIndex) const
{
	return getContactIdentity(ciIndex)->ListOfIdenticalNodes == nullptr;
}

unsigned int AbstractSurfaceFrameworkRepresentation::getIdenticalContactNodeCount(unsigned int ciIndex) const
{
	if (areAllContactNodesIdentical(ciIndex)) {
		throw invalid_argument("The nodes are all identical");
	}

	ULONG64 result = getCountOfIntegerArray(getContactIdentity(ciIndex)->ListOfIdenticalNodes);
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

	readArrayNdOfUIntValues(getContactIdentity(ciIndex)->ListOfIdenticalNodes, nodeIndices);
}
