/*-----------------------------------------------------------------------
Licensed to the Apache Software Foundation (ASF) under one
or more contributor license agreements.  See the NOTICE file
distributed with this work for additional information
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
#include <mpi.h>

#include "common/EpcDocument.h"

#include "eml2/AbstractHdfProxy.h"

#include "resqml2/SubRepresentation.h"

#include "resqml2_0_1/ContinuousProperty.h"
#include "resqml2_0_1/UnstructuredGridRepresentation.h"

// filepath is defined in a macro to better check memory leak
#define filePath "../../testingPackageCpp_MPI.epc"

void serialize(const std::string filename) {
	// Get the number of processes
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    // Get the rank of the process
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
	
/*
    // Get the name of the processor
    char processor_name[MPI_MAX_PROCESSOR_NAME];
    int name_len;
    MPI_Get_processor_name(processor_name, &name_len);
    printf("Hello world from processor %s, rank %d out of %d processors\n", processor_name, world_rank, world_size);
*/

	COMMON_NS::EpcDocument pck(filePath);
	COMMON_NS::DataObjectRepository repo;

	EML2_NS::AbstractHdfProxy* hdfProxy = repo.createHdfProxy("", "Parallel Hdf Proxy", pck.getStorageDirectory(), pck.getName() + ".h5", COMMON_NS::DataObjectRepository::openingMode::OVERWRITE);
	repo.setDefaultHdfProxy(hdfProxy);

	auto* unstructuredGrid_4cells = repo.createPartial<RESQML2_0_1_NS::UnstructuredGridRepresentation>("", "Testing Unstructured grid");

	// It is important to explictely give an UUID to the subrep in order all ranks write into the same HDF dataset.
	// If it is a random, each rank would write in a different HDF dataset.
	RESQML2_NS::SubRepresentation* subrep = repo.createSubRepresentation("0c5803ec-b620-4d56-9fc4-bf354fdc5b6b", "parallel subrep");
	subrep->pushBackSupportingRepresentation(unstructuredGrid_4cells);
	subrep->pushBackSubRepresentationPatch(gsoap_eml2_3::resqml22__IndexableElement::cells, 3); // only 3 cells of the 4
	if (world_rank < 3) {
		uint64_t elementIndice = world_rank;
		subrep->setElementIndices(&elementIndice, 1, world_rank);
	}

	// It is important to explictely give an UUID to the property in order all ranks write into the same HDF dataset.
	// If it is a random, each rank would write in a different HDF dataset.
	RESQML2_NS::ContinuousProperty* prop = repo.createContinuousProperty(unstructuredGrid_4cells, "9cd64cd9-9ecc-4da1-a3f3-ee77335d98c8", "parallel property", 1, gsoap_eml2_3::resqml22__IndexableElement::cells,
		gsoap_resqml2_0_1::resqml20__ResqmlUom::m, gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind::length);

	prop->pushBackHdf5Array1dOfValues(COMMON_NS::AbstractObject::numericalDatatypeEnum::DOUBLE, world_size);

	double value = world_rank;
	std::cout << "Rank " << world_rank << " writes its rank into HDF5 property 1D dataset at offset " << world_rank << std::endl;
	prop->setValuesOfDoubleHdf5Array1dOfValues(&value, 1, world_rank);

	if (world_rank == 0) {
		std::cout << "Rank 0 only : Start serialization of " << pck.getName() << " in " << (pck.getStorageDirectory().empty() ? "working directory." : pck.getStorageDirectory()) << std::endl;
		pck.serializeFrom(repo);
	}
}

void deserialize(const std::string filename) {
    // Get the rank of the process
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

	if (world_rank == 0) {
		COMMON_NS::EpcDocument pck(filePath);
		COMMON_NS::DataObjectRepository repo;
		const std::string resqmlResult = pck.deserializeInto(repo);
		if (!resqmlResult.empty()) {
			std::cerr << resqmlResult << std::endl;
			repo.clearWarnings();
		}
		pck.close();

		auto* unstructuredGrid_4cells = repo.getUnstructuredGridRepresentation(0);
		RESQML2_NS::ContinuousProperty* prop = dynamic_cast<RESQML2_NS::ContinuousProperty*>(unstructuredGrid_4cells->getValuesProperty(0));

		std::array<double, 4> values;
		prop->getDoubleValuesOfPatch(0, values.data());
		std::cout << "Read all values in rank " << world_rank << " from the property : " << std::endl;
		for (auto val : values) {
			std::cout << val << std::endl;
		}
	}
}

int main() {
    // Initialize the MPI environment
    MPI_Init(NULL, NULL);

	serialize(filePath);
	deserialize(filePath);

    // Finalize the MPI environment.
    MPI_Finalize();
}
