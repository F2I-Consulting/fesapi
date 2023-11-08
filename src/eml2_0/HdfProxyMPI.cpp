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
#include "HdfProxyMPI.h"

#include <hdf5.h>

using namespace std;
using namespace EML2_0_NS;

void HdfProxyMPI::open()
{
	if (hdfFile != -1) {
		std::cout << "close file" << std::endl;
		close();
	}

	/* setup file access template with parallel IO access. */
	hid_t fapl_id = H5Pcreate(H5P_FILE_ACCESS);
	if (fapl_id < 0) {
		throw invalid_argument("Cannot create the file property.");
	}

	/* set Parallel access with communicator */
	if (H5Pset_fapl_mpio( fapl_id, mpi_comm, MPI_INFO_NULL ) < 0) {
		throw invalid_argument("Cannot set the MPI communicator information to the file property.");
	}

	const std::string fullName = (packageDirectoryAbsolutePath.empty() || packageDirectoryAbsolutePath.back() == '/' || packageDirectoryAbsolutePath.back() == '\\'
		? packageDirectoryAbsolutePath
		: packageDirectoryAbsolutePath + '/') + relativeFilePath;
	/* create the file collectively */
	if (openingMode == COMMON_NS::DataObjectRepository::openingMode::READ_ONLY || openingMode == COMMON_NS::DataObjectRepository::openingMode::READ_WRITE_DO_NOT_CREATE) {
		if (H5Fis_hdf5(fullName.c_str()) > 0) {
			hdfFile = H5Fopen(fullName.c_str(),
				openingMode == COMMON_NS::DataObjectRepository::openingMode::READ_ONLY ? H5F_ACC_RDONLY : H5F_ACC_RDWR,
				fapl_id);
			if (hdfFile < 0) {
				throw invalid_argument("HDF5 library recognizes the HDF5 file but can not open it : " + fullName);
			}

			// Check the uuid
			/*
			const string hdfUuid = readStringAttribute(".", "uuid");
			if (getUuid() != hdfUuid) {
				getRepository()->addWarning("The uuid \"" + hdfUuid + "\" attribute of the HDF5 file is not the same as the uuid \"" + getUuid() + "\" of the xml EpcExternalPart.");
			}
			*/
		}
		else {
			throw invalid_argument("The HDF5 file " + fullName + " does not exist or is not a valid HDF5 file or is not accessible.");
		}
	}
	else if (openingMode == COMMON_NS::DataObjectRepository::openingMode::READ_WRITE) {
		hdfFile = H5Fcreate(fullName.c_str(), H5F_ACC_EXCL, H5P_DEFAULT, fapl_id);

		if (hdfFile < 0) {
			openingMode = COMMON_NS::DataObjectRepository::openingMode::READ_WRITE_DO_NOT_CREATE;
			open();
			openingMode = COMMON_NS::DataObjectRepository::openingMode::READ_WRITE;
		}
		else {
			//writeUuidAttribute();
		}
	}
	else if (openingMode == COMMON_NS::DataObjectRepository::openingMode::OVERWRITE) {
		hdfFile = H5Fcreate(fullName.c_str(), H5F_ACC_TRUNC, H5P_DEFAULT, fapl_id);
		if (hdfFile < 0) {
			throw invalid_argument("Can not create HDF5 file : " + fullName);
		}

		//writeUuidAttribute();
	}
	else {
		throw invalid_argument("The HDF5 permission access is unknown.");
	}
	
	/* Release file-access template */
	if (H5Pclose(fapl_id)) {
		throw invalid_argument("Cannot release the parallel file-access template");
	}
}

void HdfProxyMPI::setCollectiveIO()
{
	if(!dsetPlistId)
	{
		dsetPlistId.reset(new hid_t);
		*dsetPlistId = H5Pcreate(H5P_DATASET_XFER);
	}
	
	if( H5Pset_dxpl_mpio( *dsetPlistId, H5FD_MPIO_COLLECTIVE) < 0)
	{
		throw invalid_argument("Can not set the collective IO flag");
	}
}

void HdfProxyMPI::setIndependentIO()
{	
	if(!dsetPlistId)
	{
		dsetPlistId.reset(new hid_t);
		*dsetPlistId = H5Pcreate(H5P_DATASET_XFER);
	}

	if( H5Pset_dxpl_mpio( *dsetPlistId, H5FD_MPIO_INDEPENDENT) < 0)
	{
		throw invalid_argument("Can not set the independent IO flag");
	}
}
