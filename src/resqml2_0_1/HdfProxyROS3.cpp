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
#include "HdfProxyROS3.h"

#include <stdexcept>

#include <hdf5.h>

using namespace std;
using namespace RESQML2_0_1_NS;

void HdfProxyROS3::open()
{
#if HDF5_ROS3_ENABLED
	if (hdfFile != -1) {
		close();
	}

	if (openingMode == COMMON_NS::DataObjectRepository::READ_ONLY) {
		H5FD_ros3_fapl_t fa = { 1, 0, "", "", "" }; // Only non authenticate mode is supported by fesapi so far.
		if (!secret_id.empty() && !secret_key.empty()) {
			strcpy(fa.aws_region, packageDirectoryAbsolutePath.c_str());
			strcpy(fa.secret_id, secret_id.c_str());
			strcpy(fa.secret_key, secret_key.c_str());
		}

		/* create and set fapl entry */
		hid_t fapl_id = H5Pcreate(H5P_FILE_ACCESS);
		if (fapl_id < 0) {
			throw invalid_argument("Cannot create the file property.");
		}
		if (H5Pset_fapl_ros3(fapl_id, &fa) < 0) {
			throw invalid_argument("Cannot set the ROS3 information to the file property.");
		}

		hdfFile = H5Fopen(relativeFilePath.c_str(), H5F_ACC_RDONLY, fapl_id);
		if (hdfFile < 0) {
			throw invalid_argument("Can not open HDF5 file (in read only mode on AWS S3) on region \"" + packageDirectoryAbsolutePath + "\" and URL \"" + relativeFilePath + "\"");
		}

		// Check the uuid
		string hdfUuid = readStringAttribute(".", "uuid");
		if (getUuid() != hdfUuid) {
			getRepository()->addWarning("The uuid \"" + hdfUuid + "\" attribute of the HDF5 file is not the same as the uuid \"" + getUuid() + "\" of the xml EpcExternalPart.");
		}
	}
	else {
		throw invalid_argument("HDF5 file on an AWS bucket can only be open in read only mode for now.");
	}
#else
	throw logic_error("Please enable ROS3 VFD support using CMAKE HDF5_ROS3_ENABLED variable if you want to use it.");
#endif
}
