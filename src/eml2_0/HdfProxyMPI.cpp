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

#ifdef WITH_PARALLEL
void HdfProxyMPI::open()
{
// #if FESAPI_USE_MPI
	if (hdfFile != -1) {
		close();
	}

	/* create and set fapl entry */
	hid_t fapl_id = H5Pcreate(H5P_FILE_ACCESS);
	if (fapl_id < 0) {
		throw invalid_argument("Cannot create the file property.");
	}
	if (H5Pset_fapl_mpio( fapl_id, mpi_comm, MPI_INFO_NULL ) < 0) {
		throw invalid_argument("Cannot set the MPI communicator information to the file property.");
	}

	hdfFile = H5Fopen(relativeFilePath.c_str(), H5F_ACC_RDWR, fapl_id);
	if (hdfFile < 0) {
		throw invalid_argument("Can not open HDF5 file (in read only mode on AWS S3) on region \"" + packageDirectoryAbsolutePath + "\" and URL \"" + relativeFilePath + "\"");
	}

// #else
	// throw logic_error("Please enable MPI support using CMAKE FESAPI_USE_MPI variable if you want to use it.");
// #endif
}

#endif