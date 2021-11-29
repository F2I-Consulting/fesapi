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
#include "HdfProxy.h"

#include "eml2/AbstractHdfProxy.h"
#include "eml2/PropertyKind.h"
#include "resqml2_0_1/PropertyKind.h"
#include "resqml2/AbstractIjkGridRepresentation.h"
#include "resqml2/DiscreteProperty.h"

using namespace std;
using namespace EML2_NS;
using namespace RESQML2_NS;
using namespace eml2_test;

HdfProxy::HdfProxy(const string & repoPath)
	: commontest::AbstractTest(repoPath) {
}

void HdfProxy::initRepo() {
	RESQML2_NS::AbstractIjkGridRepresentation * ijkgrid432 = repo->createPartialIjkGridRepresentation("", "");
	EML2_NS::PropertyKind * propType1 = repo->createPartial<RESQML2_0_1_NS::PropertyKind>("", "Partial prop kind");

	RESQML2_NS::DiscreteProperty* discreteProp432 = repo->createDiscreteProperty(ijkgrid432, "f9447f76-34c5-4967-a3ee-4f400f96dba6", "4x3x2 grid cellIndex",
		gsoap_eml2_3::eml23__IndexableElement::cells, propType1);
	LONG64 discreteProp432Values[24] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11,
		12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23 };

	// getting the hdf proxy
	EML2_NS::AbstractHdfProxy* hdfProxy = repo->getHdfProxySet()[0];
	hdfProxy->setCompressionLevel(6);
	hdfProxy->setMaxChunkSize(192/2); // Create two chunks
	discreteProp432->pushBackLongHdf5Array3dOfValues(discreteProp432Values, 4, 3, 2, hdfProxy, 1111);
}

void HdfProxy::readRepo() {
	auto* prop = repo->getDataObjectByUuid("f9447f76-34c5-4967-a3ee-4f400f96dba6");

	EML2_NS::AbstractHdfProxy* hdfProxy = repo->getHdfProxySet()[0];
	REQUIRE(hdfProxy->isCompressed("/" + prop->getXmlNamespace() + "/f9447f76-34c5-4967-a3ee-4f400f96dba6/values_patch0"));

	const std::string datasetName = "/" + prop->getXmlNamespace() + "/f9447f76-34c5-4967-a3ee-4f400f96dba6/values_patch0";

	auto dims = hdfProxy->getElementCountPerDimension(datasetName);
	REQUIRE(dims.size() == 3);
	REQUIRE(dims[0] == 2);
	REQUIRE(dims[1] == 3);
	REQUIRE(dims[2] == 4);

	dims = hdfProxy->getElementCountPerChunkDimension(datasetName);
	REQUIRE(dims.size() == 3);
	REQUIRE(dims[0] == 1);
	REQUIRE(dims[1] == 3);
	REQUIRE(dims[2] == 4);
}
