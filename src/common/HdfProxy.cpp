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
#include "common/HdfProxy.h"

#include <stdexcept>
#include <sstream>

#include "hdf5.h"

using namespace std;
using namespace COMMON_NS;


HdfProxy::HdfProxy(const std::string & packageDirAbsolutePath, const std::string & externalFilePath) :
	AbstractHdfProxy(packageDirAbsolutePath, externalFilePath), hdfFile(-1), compressionLevel(0) {}

void HdfProxy::open()
{
	if (hdfFile != -1) {
		close();
	}

	if (getEpcDocument() == nullptr || getEpcDocument()->getHdf5PermissionAccess() == COMMON_NS::EpcDocument::READ_ONLY) { // By default, if no Epc document is available (DAS use case), open in read only mode
		if (H5Fis_hdf5((packageDirectoryAbsolutePath + relativeFilePath).c_str()) > 0) {
			hdfFile = H5Fopen((packageDirectoryAbsolutePath + relativeFilePath).c_str(), H5F_ACC_RDONLY, H5P_DEFAULT);

			if (getEpcDocument() != nullptr) { // if no Epc document is available (DAS use case), we cannot check any HDF uuid
				// Check the uuid
				string hdfUuid = readStringAttribute(".", "uuid");
				if (getUuid() != hdfUuid) {
					getEpcDocument()->addWarning("The uuid \"" + hdfUuid + "\" attribute of the HDF5 file is not the same as the uuid \"" + getUuid() + "\" of the xml EpcExternalPart.");
				}
			}
		}
		else {
			throw invalid_argument("The HDF5 file " + packageDirectoryAbsolutePath + relativeFilePath + " does not exist or is not a valid HDF5 file.");
		}
	}
	else if (getEpcDocument()->getHdf5PermissionAccess() == COMMON_NS::EpcDocument::READ_WRITE) {
		hdfFile = H5Fcreate((packageDirectoryAbsolutePath + relativeFilePath).c_str(), H5F_ACC_EXCL, H5P_DEFAULT, H5P_DEFAULT);

		if (hdfFile < 0) {
			if (H5Fis_hdf5((packageDirectoryAbsolutePath + relativeFilePath).c_str()) > 0) {
				hdfFile = H5Fopen((packageDirectoryAbsolutePath + relativeFilePath).c_str(), H5F_ACC_RDWR, H5P_DEFAULT);

				// Check the uuid
				if (getEpcDocument() != nullptr) { // if no Epc document is available (DAS use case), we cannot check any HDF uuid
					string hdfUuid = readStringAttribute(".", "uuid");
					if (getUuid() != hdfUuid) {
						getEpcDocument()->addWarning("The uuid \"" + hdfUuid + "\" attribute of the HDF5 file is not the same as the uuid \"" + getUuid() + "\" of the xml EpcExternalPart.");
					}
				}
			}
			else {
				throw invalid_argument("The HDF5 file " + packageDirectoryAbsolutePath + relativeFilePath + " is not a valid HDF5 file.");
			}
		}
		else {
			// create an attribute at the file level to store the uuid of the corresponding resqml hdf proxy.
			hid_t aid = H5Screate(H5S_SCALAR);
			hid_t atype = H5Tcopy(H5T_C_S1);
			H5Tset_size(atype, getUuid().size());
			hid_t attribute_id = H5Acreate2(hdfFile, "uuid", atype, aid, H5P_DEFAULT, H5P_DEFAULT);
			int status = H5Awrite(attribute_id, atype, getUuid().c_str());
			if (status < 0) {
				throw invalid_argument("The uuid file attribute could not have been written.");
			}

			// Close the attribute.
			status = H5Sclose(aid);
			if (status < 0) {
				throw invalid_argument("The uuid file attribute dataspace could not have been closed.");
			}
			status = H5Tclose(atype);
			if (status < 0) {
				throw invalid_argument("The uuid file attribute datatype could not have been closed.");
			}
			status = H5Aclose(attribute_id);
			if (status < 0) {
				throw invalid_argument("The uuid file attribute could not have been closed.");
			}
		}
	}
	else if (getEpcDocument()->getHdf5PermissionAccess() == COMMON_NS::EpcDocument::OVERWRITE) {
		hdfFile = H5Fcreate((packageDirectoryAbsolutePath + relativeFilePath).c_str(), H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);

		// create an attribute at the file level to store the uuid of the corresponding resqml hdf proxy.
		hid_t aid = H5Screate(H5S_SCALAR);
		hid_t atype = H5Tcopy(H5T_C_S1);
		H5Tset_size(atype, getUuid().size());
		hid_t attribute_id = H5Acreate2(hdfFile, "uuid", atype, aid, H5P_DEFAULT, H5P_DEFAULT);
		int status = H5Awrite(attribute_id, atype, getUuid().c_str());
		if (status < 0) {
			throw invalid_argument("The uuid file attribute could not have been written.");
		}

		// Close the attribute.
		status = H5Sclose(aid);
		if (status < 0) {
			throw invalid_argument("The uuid file attribute dataspace could not have been closed.");
		}
		status = H5Tclose(atype);
		if (status < 0) {
			throw invalid_argument("The uuid file attribute datatype could not have been closed.");
		}
		status = H5Aclose(attribute_id);
		if (status < 0) {
			throw invalid_argument("The uuid file attribute could not have been closed.");
		}
	}
	else {
		throw invalid_argument("The HDF5 permission access is unknown.");
	}

	if (hdfFile < 0) {
		throw invalid_argument("The HDF5 file " + packageDirectoryAbsolutePath + relativeFilePath + " could not have been created or opened.");
	}
}

void HdfProxy::close()
{
	if (hdfFile != -1) {
		H5Fclose(hdfFile);
		hdfFile = -1;
	}
}

void HdfProxy::readArrayNdOfValues(const std::string & datasetName, void* values, const hid_t & datatype)
{
	if (!isOpened()) {
		open();
	}

	hid_t dataset = H5Dopen(hdfFile, datasetName.c_str(), H5P_DEFAULT);
	if (dataset < 0) {
		throw invalid_argument("The resqml dataset " + datasetName + " could not be opened.");
	}
	hid_t readingError = H5Dread (dataset, datatype, H5S_ALL, H5S_ALL, H5P_DEFAULT, values);

	H5Dclose(dataset);
	if (readingError < 0) {
		throw invalid_argument("The resqml dataset " + datasetName + " could not be read.");
	}
}

void HdfProxy::readArrayNdOfValues(
	const std::string & datasetName,
	void* values,
	unsigned long long * numValuesInEachDimension,
	unsigned long long * offsetInEachDimension,
	const unsigned int & numDimensions, const hid_t & datatype)
{
	readArrayNdOfValues(datasetName, values, numValuesInEachDimension, offsetInEachDimension, nullptr, nullptr, numDimensions, datatype);
}

void HdfProxy::readArrayNdOfValues(
	const std::string & datasetName,
	void* values,
	unsigned long long * blockCountPerDimension,
	unsigned long long * offsetInEachDimension,
	unsigned long long * strideInEachDimension,
	unsigned long long * blockSizeInEachDimension,
	const unsigned int & numDimensions, const hid_t & datatype)
{
	if (!isOpened()) {
		open();
	}

	hid_t dataset = H5Dopen(hdfFile, datasetName.c_str(), H5P_DEFAULT);
	if (dataset < 0) {
		throw invalid_argument("The resqml dataset " + datasetName + " could not be opened.");
	}

	hid_t filespace = H5Dget_space(dataset);
	if (filespace < 0) {
		H5Dclose(dataset);
		throw invalid_argument("The filespace of resqml dataset " + datasetName + " could not be opened.");
	}
	herr_t result = H5Sselect_hyperslab(filespace, H5S_SELECT_SET, offsetInEachDimension, strideInEachDimension, blockCountPerDimension, blockSizeInEachDimension);
	if (result < 0) {
		H5Sclose(filespace);
		H5Dclose(dataset);
		throw invalid_argument("The hyperslabbing of resqml dataset " + datasetName + " could not be selected.");
	}

	if (H5Sget_simple_extent_ndims(filespace) != (int) numDimensions) {
		H5Sclose(filespace);
		H5Dclose(dataset);
		throw invalid_argument("The resqml dataset " + datasetName + " does not have " + std::to_string(numDimensions) + " dimensions.");
	}

	hsize_t slab_size = 1;
	if (blockSizeInEachDimension == nullptr) {
		for (unsigned int h = 0; h < numDimensions; ++h) {
			slab_size *= blockCountPerDimension[h];
		}
	}
	else {
		for (unsigned int h = 0; h < numDimensions; ++h) {
			slab_size *= blockSizeInEachDimension[h];
		}
		for (unsigned int h = 0; h < numDimensions; ++h) {
			slab_size *= blockCountPerDimension[h];
		}
	}

	hid_t memspace = H5Screate_simple(1, &slab_size, nullptr);
	if (memspace < 0) {
		H5Sclose(filespace);
		H5Dclose(dataset);
		throw invalid_argument("The memory space for the slabbing of resqml dataset " + datasetName + " could not be created.");
	}

	hid_t readingError = H5Dread(dataset, datatype, memspace, filespace, H5P_DEFAULT, values);

	H5Sclose(memspace);
	H5Sclose(filespace);
	H5Dclose(dataset);

	if (readingError < 0) {
		throw invalid_argument("The resqml dataset " + datasetName + " could not be read.");
	}
}

void HdfProxy::selectArrayNdOfValues(
	const std::string & datasetName,
	unsigned long long * blockCountPerDimension,
	unsigned long long * offsetInEachDimension,
	unsigned long long * strideInEachDimension,
	unsigned long long * blockSizeInEachDimension,
	const unsigned int & numDimensions,
	bool newSelection,
	int & dataset,
	int & filespace)
{
	if (!isOpened()) {
		open();
	}

	if (newSelection) {
		dataset = H5Dopen(hdfFile, datasetName.c_str(), H5P_DEFAULT);
		if (dataset < 0) {
			throw invalid_argument("The resqml dataset " + datasetName + " could not be opened.");
		}

		filespace = H5Dget_space(dataset);
		if (filespace < 0) {
			H5Dclose(dataset);
			throw invalid_argument("The filespace of resqml dataset " + datasetName + " could not be opened.");
		}

		if (H5Sget_simple_extent_ndims(filespace) != (int) numDimensions)
		{
			H5Sclose(filespace);
			H5Dclose(dataset);
			throw invalid_argument("The resqml dataset " + datasetName + " does not have " + std::to_string(numDimensions) + " dimensions.");
		}
	}

	H5S_seloper_t selectionMode;
	if (newSelection)
		selectionMode = H5S_SELECT_SET;
	else
		selectionMode = H5S_SELECT_OR;

	herr_t result = H5Sselect_hyperslab(filespace, selectionMode, offsetInEachDimension, strideInEachDimension, blockCountPerDimension, blockSizeInEachDimension);
	if (result < 0) {
		H5Sclose(filespace);
		H5Dclose(dataset);
		throw invalid_argument("The hyperslabbing region cannot be added to the " + datasetName + " selected region.");
	}
}

void HdfProxy::readArrayNdOfValues(
	int dataset,
	int filespace,
	void* values, 
	unsigned long long slabSize, 
	const int & datatype)
{
	if (!isOpened()) {
		open();
	}

	hid_t memspace = H5Screate_simple(1, &slabSize, nullptr);
	if (memspace < 0) {
		ssize_t size = 1 + H5Iget_name(dataset, NULL, 0);
		char * name = (char *)malloc(size);
		size = H5Iget_name(dataset, name, size);
		std::string datasetName(name);
		free(name);
		H5Sclose(filespace);
		H5Dclose(dataset);
		throw invalid_argument("The memory space for the slabbing of resqml dataset " + datasetName + " could not be created.");
	}

	hid_t readingError = H5Dread(dataset, datatype, memspace, filespace, H5P_DEFAULT, values);
	std::string datasetName;
	if (readingError < 0) {
		ssize_t size = 1 + H5Iget_name(dataset, NULL, 0);
		char * name = (char *)malloc(size);
		size = H5Iget_name(dataset, name, size);
		datasetName = std::string(name);
		free(name);
	}

	H5Sclose(memspace);
	H5Sclose(filespace);
	H5Dclose(dataset);

	if (readingError < 0) {
		throw invalid_argument("The resqml dataset " + datasetName + " could not be read.");
	}
}

int HdfProxy::getHdfDatatypeInDataset(const std::string & datasetName) const
{
	if (!isOpened()) {
		throw invalid_argument("The HDF5 file ust be opened");
	}

	hid_t dataset = H5Dopen(hdfFile, datasetName.c_str(), H5P_DEFAULT); 
	hid_t datatype = H5Dget_type(dataset); 
	hid_t native_datatype =  H5Tget_native_type(datatype, H5T_DIR_ASCEND); 

	H5Dclose(dataset);
	H5Tclose(datatype);

	return native_datatype;
}

int HdfProxy::getHdfDatatypeClassInDataset(const std::string & datasetName) const
{
	if (!isOpened()) {
		throw invalid_argument("The HDF5 file ust be opened");
	}

	hid_t dataset = H5Dopen(hdfFile, datasetName.c_str(), H5P_DEFAULT);
	hid_t datatype = H5Dget_type(dataset);
	hid_t result = H5Tget_class(datatype);

	H5Dclose(dataset);
	H5Tclose(datatype);

	return result;
}

void HdfProxy::writeItemizedListOfList(const string & groupName,
			const string & name,
			const int & cumulativeLengthDatatype,
			void * cumulativeLength,
			const unsigned long long & cumulativeLengthSize,
			const int & elementsDatatype,
			void * elements,
			const unsigned long long & elementsSize)
{
	if (!isOpened()) {
		open();
	}

	hid_t parentGrp = openOrCreateGroupInRootGroup(groupName);
	hid_t grp = H5Gcreate(parentGrp, name.c_str(), H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
	H5Gclose(parentGrp);

	// ************* CUMULATIVE LENGTH *************
	// Create dataspace for the dataset in the file.
	hid_t fspaceCL = H5Screate_simple(1, &cumulativeLengthSize, nullptr);

	hid_t datasetCL;
	if (compressionLevel) {
		// Create dataset and write it into the file.
		hid_t dcpl = H5Pcreate (H5P_DATASET_CREATE);
		H5Pset_deflate (dcpl, compressionLevel);
		H5Pset_chunk (dcpl, 1, &cumulativeLengthSize);

		datasetCL = H5Dcreate(grp, CUMULATIVE_LENGTH_DS_NAME, cumulativeLengthDatatype, fspaceCL, H5P_DEFAULT, dcpl, H5P_DEFAULT);

		H5Pclose(dcpl);
	}
	else {
		datasetCL = H5Dcreate(grp, CUMULATIVE_LENGTH_DS_NAME, cumulativeLengthDatatype, fspaceCL, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
	}

	H5Dwrite(datasetCL, cumulativeLengthDatatype, H5S_ALL, H5S_ALL, H5P_DEFAULT, cumulativeLength);
	H5Sclose(fspaceCL);
	H5Dclose(datasetCL);

	// ************* ELEMENTS *************
	// Create dataspace for the dataset in the file.
	hid_t fspaceE = H5Screate_simple(1, &elementsSize, nullptr);

	hid_t datasetE;
	if (compressionLevel) {
		// Create dataset and write it into the file.
		hid_t dcpl = H5Pcreate (H5P_DATASET_CREATE);
		H5Pset_deflate (dcpl, compressionLevel);
		H5Pset_chunk (dcpl, 1, &elementsSize);

		datasetE = H5Dcreate(grp, ELEMENTS_DS_NAME, elementsDatatype, fspaceE, H5P_DEFAULT, dcpl, H5P_DEFAULT);

		H5Pclose(dcpl);
	}
	else {
		datasetE = H5Dcreate(grp, ELEMENTS_DS_NAME, elementsDatatype, fspaceE, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
	}

	H5Dwrite(datasetE, elementsDatatype, H5S_ALL, H5S_ALL, H5P_DEFAULT, elements);
	H5Sclose(fspaceE);
	H5Dclose(datasetE);

	H5Gclose(grp);
}

unsigned int HdfProxy::getDimensionCount(const std::string & datasetName)
{
	if (!isOpened()) {
		open();
	}

	hid_t dataset = H5Dopen(hdfFile, datasetName.c_str(), H5P_DEFAULT);

	hid_t dataspace = H5Dget_space(dataset);
	int result = H5Sget_simple_extent_ndims(dataspace);

	H5Sclose(dataspace);
	H5Dclose(dataset);

	return result;
}

hssize_t HdfProxy::getElementCount(const std::string & datasetName)
{
	if (!isOpened()) {
		open();
	}

    hid_t dataset = H5Dopen(hdfFile, datasetName.c_str(), H5P_DEFAULT);
	
	hid_t dataspace = H5Dget_space(dataset);
	hssize_t result = H5Sget_simple_extent_npoints(dataspace);

	H5Sclose(dataspace);
	H5Dclose(dataset);

	return result;
}

void HdfProxy::writeArrayNdOfFloatValues(const string & groupName,
		const string & name,
		float * floatValues,
		hsize_t * numValuesInEachDimension,
		const unsigned int & numDimensions)
{
	writeArrayNd(groupName, name, H5T_NATIVE_FLOAT, floatValues, numValuesInEachDimension, numDimensions);
}

void HdfProxy::writeArrayNdOfDoubleValues(const string & groupName,
		const string & name,
		double * dblValues,
		hsize_t * numValuesInEachDimension,
		const unsigned int & numDimensions)
{
	writeArrayNd(groupName, name, H5T_NATIVE_DOUBLE, dblValues, numValuesInEachDimension, numDimensions);
}

void HdfProxy::writeArrayNdOfCharValues(const std::string & groupName,
		const std::string & name,
		char * intValues,
		unsigned long long * numValuesInEachDimension,
		const unsigned int & numDimensions)
{
	writeArrayNd(groupName, name, H5T_NATIVE_CHAR, intValues, numValuesInEachDimension, numDimensions);
}

void HdfProxy::writeArrayNdOfIntValues(const string & groupName,
        const string & name,
        int * intValues,
        hsize_t * numValuesInEachDimension,
        const unsigned int & numDimensions)
{
	writeArrayNd(groupName, name, H5T_NATIVE_INT, intValues, numValuesInEachDimension, numDimensions);
}

void HdfProxy::writeArrayNdOfGSoapULong64Values(const std::string & groupName,
		const std::string & name,
		ULONG64 * ulong64Values,
		hsize_t * numValuesInEachDimension,
		const unsigned int & numDimensions)
{
	writeArrayNd(groupName, name, H5T_NATIVE_ULLONG, ulong64Values, numValuesInEachDimension, numDimensions);
}

void HdfProxy::writeArrayNd(const std::string & groupName,
			const std::string & name,
			const int & datatype,
			void * values,
			unsigned long long * numValuesInEachDimension,
			const unsigned int & numDimensions)
{
	if (!isOpened()) {
		open();
	}

	hid_t grp = openOrCreateGroupInRootGroup(groupName);
	if (grp < 0) {
		throw invalid_argument("The group " + groupName + " could not be created.");
	}

	// Create the data space
	hid_t space = H5Screate_simple(numDimensions, numValuesInEachDimension, nullptr);
	if (space < 0) {
		H5Gclose(grp);
		throw invalid_argument("The dataspace for the dataset " + name + " could not be created.");
	}

    // Create the dataset.
	herr_t error;
	hid_t dataset;
	if (compressionLevel) {
		hid_t dcpl = H5Pcreate (H5P_DATASET_CREATE);
		H5Pset_deflate (dcpl, compressionLevel);
		H5Pset_chunk (dcpl, numDimensions, numValuesInEachDimension);

		dataset = H5Dcreate(grp, name.c_str(), datatype, space, H5P_DEFAULT, dcpl, H5P_DEFAULT);
		H5Pclose(dcpl);
		if (dataset < 0) {
			H5Sclose(space);
			H5Gclose(grp);
			throw invalid_argument("The dataset " + name + " could not be created.");
		}
	}
	else {
		dataset = H5Dcreate (grp, name.c_str(), datatype, space, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
		if (dataset < 0) {
			H5Sclose(space);
			H5Gclose(grp);
			throw invalid_argument("The dataset " + name + " could not be created.");
		}
	}

	error = H5Dwrite(dataset, datatype, H5S_ALL, H5S_ALL, H5P_DEFAULT, values);
	H5Sclose(space);
	H5Dclose(dataset);
	H5Gclose(grp);
	if (error < 0) {
		throw invalid_argument("The data could not be written in dataset " + name);
	}
}

void HdfProxy::createArrayNd(
	const std::string& groupName,
	const std::string& datasetName,
	const int & datatype,
	unsigned long long* numValuesInEachDimension,
	const unsigned int& numDimensions
) {
	if (!isOpened()) {
		open();
	}

	hid_t grp = openOrCreateGroupInRootGroup(groupName);
	if (grp < 0) {
		throw invalid_argument("The group " + groupName + " could not be created.");
	}

	// Create the data space
	hid_t space = H5Screate_simple(numDimensions, numValuesInEachDimension, nullptr);
	if (space < 0) {
		H5Gclose(grp);
		throw invalid_argument("The dataspace for the dataset " + datasetName + " could not be created.");
	}

	// Create the dataset.
	hid_t dataset;
	if (compressionLevel > 0) {
		hid_t dcpl = H5Pcreate (H5P_DATASET_CREATE);
		H5Pset_deflate (dcpl, compressionLevel);
		H5Pset_chunk (dcpl, numDimensions, numValuesInEachDimension);

		dataset = H5Dcreate(grp, datasetName.c_str(), datatype, space, H5P_DEFAULT, dcpl, H5P_DEFAULT);
		H5Pclose(dcpl);
		if (dataset < 0) {			
			H5Sclose(space);
			H5Gclose(grp);
			throw invalid_argument("The dataset " + datasetName + " could not be created.");
		}
	}
	else {
		dataset = H5Dcreate(grp, datasetName.c_str(), datatype, space, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
		if (dataset < 0) {
			H5Sclose(space);
			H5Gclose(grp);
			throw invalid_argument("The dataset " + datasetName + " could not be created.");
		}
	}

	H5Sclose(space);
	H5Dclose(dataset);
	H5Gclose(grp);
}


void HdfProxy::writeArrayNdSlab(
	const string& groupName,
	const string& datasetName,
	const int & datatype,
	void* values,
	hsize_t* numValuesInEachDimension,
	hsize_t* offsetInEachDimension,
	const unsigned int& numDimensions)
{
	if (!isOpened()) {
		open();
	}

	hid_t grp = openOrCreateGroupInRootGroup(groupName);
	hid_t dataset = H5Dopen(grp, datasetName.c_str(), H5P_DEFAULT);
	if (dataset < 0) {
		throw invalid_argument("The resqml dataset " + datasetName + " could not be opened.");
	}
	
	hid_t filespace = H5Dget_space(dataset);
	if (filespace < 0) {
		throw invalid_argument("The resqml dataspace of " + datasetName + " could not be opened.");
	}
	herr_t errorCode = H5Sselect_hyperslab(filespace, H5S_SELECT_SET, offsetInEachDimension, nullptr, numValuesInEachDimension, nullptr);
	if (errorCode < 0) {
		H5Sclose(filespace);
		H5Dclose(dataset);
		H5Gclose(grp);
		throw invalid_argument("The slab of dataset " + datasetName + " could not have been selected");
	}

	hsize_t slab_size = 1;
	for(unsigned int h = 0; h < numDimensions; ++h){
		slab_size *= numValuesInEachDimension[h];
	}
	hid_t memspace = H5Screate_simple(1, &slab_size, nullptr);
	if (memspace < 0) {
		H5Sclose(filespace);
		H5Dclose(dataset);
		H5Gclose(grp);
		throw invalid_argument("The dataspace for the slab of the dataset " + datasetName + " could not be created.");
	}

	hid_t datatypeOfDataset = H5Dget_type(dataset);
	if (datatypeOfDataset < 0) {
		throw invalid_argument("The datatype of the dataset " + datasetName + " could not be retrieved.");
	}
	if (H5Tequal(datatype, datatypeOfDataset) <= 0) {
		throw invalid_argument("The given datatype for the slab is not compatible with the datatype of the dataset.");
	}
	errorCode = H5Dwrite(dataset, datatype, memspace, filespace, H5P_DEFAULT, values);

	H5Tclose(datatype);
	H5Sclose(memspace);
	H5Sclose(filespace);
	H5Dclose(dataset);
	H5Gclose(grp);

	if (errorCode < 0) {
		throw invalid_argument("The data could not be written in dataset slab " + datasetName);
	}
}

void HdfProxy::readArrayNdOfDoubleValues(const std::string & datasetName, double* values)
{
	readArrayNdOfValues(datasetName, values, H5T_NATIVE_DOUBLE);
}

void HdfProxy::readArrayNdOfDoubleValues(
	  const std::string & datasetName, double* values,
	  hsize_t * numValuesInEachDimension,
	  hsize_t * offsetInEachDimension,
	  const unsigned int & numDimensions)
{
	readArrayNdOfValues(datasetName, values,
			numValuesInEachDimension, offsetInEachDimension, numDimensions,
			H5T_NATIVE_DOUBLE);
}

void HdfProxy::readArrayNdOfDoubleValues(
	const std::string & datasetName, double* values,
	hsize_t * blockCountPerDimension,
	hsize_t * offsetInEachDimension,
	hsize_t * strideInEachDimension,
	hsize_t * blockSizeInEachDimension,
	const unsigned int & numDimensions)
{
	readArrayNdOfValues(datasetName, values,
		blockCountPerDimension, offsetInEachDimension, strideInEachDimension, blockSizeInEachDimension, numDimensions,
		H5T_NATIVE_DOUBLE);
}

void HdfProxy::readArrayNdOfDoubleValues(
	int dataset,
	int filespace,
	void* values,
	unsigned long long slabSize)
{
	readArrayNdOfValues(dataset, filespace, values, slabSize, H5T_NATIVE_DOUBLE);
}

void HdfProxy::readArrayNdOfFloatValues(const std::string & datasetName, float* values)
{
	readArrayNdOfValues(datasetName, values, H5T_NATIVE_FLOAT);
}

void HdfProxy::readArrayNdOfFloatValues(
	const std::string& datasetName, float* values,
	hsize_t* numValuesInEachDimension,
	hsize_t* offsetInEachDimension,
	const unsigned int& numDimensions)
{
	readArrayNdOfValues(datasetName, values,
			numValuesInEachDimension, offsetInEachDimension, numDimensions,
			H5T_NATIVE_FLOAT);
}

void HdfProxy::readArrayNdOfGSoapLong64Values(const std::string & datasetName, LONG64* values)
{
	readArrayNdOfValues(datasetName, values, H5T_NATIVE_LLONG);
}

void HdfProxy::readArrayNdOfGSoapULong64Values(const std::string & datasetName, ULONG64* values)
{
	readArrayNdOfValues(datasetName, values, H5T_NATIVE_ULLONG);
}

void HdfProxy::readArrayNdOfLongValues(const std::string & datasetName, long* values)
{
	readArrayNdOfValues(datasetName, values, H5T_NATIVE_LONG);
}

void HdfProxy::readArrayNdOfLongValues(
	const std::string& datasetName, long* values,
	hsize_t* numValuesInEachDimension,
	hsize_t* offsetInEachDimension,
	const unsigned int& numDimensions)
{
	readArrayNdOfValues(datasetName, values,
			numValuesInEachDimension, offsetInEachDimension, numDimensions,
			H5T_NATIVE_LONG);
}

void HdfProxy::readArrayNdOfULongValues(const std::string & datasetName, unsigned long* values)
{
	readArrayNdOfValues(datasetName, values, H5T_NATIVE_ULONG);
}

void HdfProxy::readArrayNdOfIntValues(const std::string & datasetName, int* values)
{
	readArrayNdOfValues(datasetName, values, H5T_NATIVE_INT);
}

void HdfProxy::readArrayNdOfIntValues(
	const std::string& datasetName, int* values,
	hsize_t* numValuesInEachDimension,
	hsize_t* offsetInEachDimension,
	const unsigned int& numDimensions)
{
	readArrayNdOfValues(datasetName, values,
		numValuesInEachDimension, offsetInEachDimension, numDimensions,
		H5T_NATIVE_INT);
}

void HdfProxy::readArrayNdOfUIntValues(const std::string & datasetName, unsigned int* values)
{
	readArrayNdOfValues(datasetName, values, H5T_NATIVE_UINT);
}

 void HdfProxy::readArrayNdOfShortValues(const std::string & datasetName, short* values)
{
	readArrayNdOfValues(datasetName, values, H5T_NATIVE_SHORT);
}

void HdfProxy::readArrayNdOfUShortValues(const std::string & datasetName, unsigned short* values)
{
	readArrayNdOfValues(datasetName, values, H5T_NATIVE_USHORT);
}

void HdfProxy::readArrayNdOfCharValues(const std::string & datasetName, char* values)
{
	readArrayNdOfValues(datasetName, values, H5T_NATIVE_CHAR);
}

void HdfProxy::readArrayNdOfUCharValues(const std::string & datasetName, unsigned char* values)
{
	readArrayNdOfValues(datasetName, values, H5T_NATIVE_UCHAR);
}

int HdfProxy::openOrCreateRootGroup()
{
	return hdfFile;
}

int HdfProxy::openOrCreateGroupInRootGroup(const string & groupName)
{
	hid_t rootGroup = openOrCreateRootGroup();
	if (rootGroup < 0) {
		throw invalid_argument("The root group could not be opened or created in the hdf file.");
	}

	std::stringstream ss;
	ss.str(groupName);
	std::string group;
	hid_t result = -1;
	while (std::getline(ss, group, '/')) {
		if (group.empty()) continue;

		H5O_info_t info;
		herr_t status = H5Oget_info_by_name(rootGroup, groupName.c_str(), &info, H5P_DEFAULT);

		if (status >= 0) {
			result = H5Gopen(rootGroup, group.c_str(), H5P_DEFAULT);
		}
		else {
			result = H5Gcreate(rootGroup, group.c_str(), H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
		}
		H5Gclose(rootGroup);
		rootGroup = result;

		if (result < 0) {
			return result;
		}
	}
	return result;
}

std::vector<hsize_t> HdfProxy::readArrayDimensions(const std::string & datasetName)
{
	if (!isOpened()) {
		open();
	}

	hid_t dataset = H5Dopen(hdfFile, datasetName.c_str(), H5P_DEFAULT);

	hid_t dataspace = H5Dget_space(dataset);
	int nDim = H5Sget_simple_extent_ndims(dataspace);
	std::vector<hsize_t> dims(nDim, 0);
	H5Sget_simple_extent_dims(dataspace, &dims[0], nullptr);

	H5Sclose(dataspace);
	H5Dclose(dataset);

	return dims;
}

void HdfProxy::writeGroupAttributes(const std::string & groupName,
	const std::vector<std::string> & attributeNames,
	const std::vector<std::string> & values)
{
	if (attributeNames.size() != values.size()) {
		throw std::invalid_argument("The attribute name vector must be the same size as the attritbute value vector.");
	}

	int groupId = openOrCreateGroupInRootGroup(groupName);

	hid_t aid = H5Screate(H5S_SCALAR);
	hid_t atype = H5Tcopy(H5T_C_S1);
	for (size_t i = 0; i < attributeNames.size(); ++i) {
		H5Tset_size(atype, values[i].size());
		hid_t attribute_id = H5Acreate2(groupId, attributeNames[i].c_str(), atype, aid, H5P_DEFAULT, H5P_DEFAULT);
		H5Awrite(attribute_id, atype, values[i].c_str());
		H5Aclose(attribute_id);
	}
	H5Sclose(aid);
	H5Tclose(atype);

	H5Gclose(groupId);
}

void HdfProxy::writeGroupAttribute(const std::string & groupName,
	const std::string & attributeName,
	const std::vector<std::string> & values)
{
	const int groupId = openOrCreateGroupInRootGroup(groupName);

	unsigned int maxStringSize = 0;
	for (size_t i = 0; i < values.size(); ++i) {
		if (values[i].size() > maxStringSize) maxStringSize = values[i].size();
	}
	maxStringSize++;
	char* concat = new char[maxStringSize * values.size()];
	for (size_t i = 0; i < values.size(); ++i) {
		for (unsigned int j = 0; j < maxStringSize; ++j) {
			concat[j + i*maxStringSize] = values[i].size() > j ? values[i][j] : '\0';
		}
	}

	const hsize_t valueCount = values.size();
	const hid_t aid = H5Screate_simple(1, &valueCount, nullptr);
	const hid_t atype = H5Tcopy(H5T_C_S1);
	H5Tset_size(atype, maxStringSize + 1);
	const hid_t attribute_id = H5Acreate2(groupId, attributeName.c_str(), atype, aid, H5P_DEFAULT, H5P_DEFAULT);
	H5Awrite(attribute_id, atype, concat);
	delete[] concat;
	H5Aclose(attribute_id);
	H5Sclose(aid);
	H5Tclose(atype);

	H5Gclose(groupId);
}

void HdfProxy::writeGroupAttributes(const std::string & groupName,
	const std::vector<std::string> & attributeNames,
	const std::vector<double> & values)
{
	if (attributeNames.size() != values.size()) {
		throw std::invalid_argument("The attribute name vector must be the same size as the attritbute value vector.");
	}

	int groupId = openOrCreateGroupInRootGroup(groupName);

	hid_t aid = H5Screate(H5S_SCALAR);
	for (size_t i = 0; i < attributeNames.size(); ++i) {
		hid_t attribute_id = H5Acreate2(groupId, attributeNames[i].c_str(), H5T_NATIVE_DOUBLE, aid, H5P_DEFAULT, H5P_DEFAULT);
		H5Awrite(attribute_id, H5T_NATIVE_DOUBLE, &(values[i]));
		H5Aclose(attribute_id);
	}
	H5Sclose(aid);

	H5Gclose(groupId);
}

void HdfProxy::writeGroupAttributes(const std::string & groupName,
	const std::vector<std::string> & attributeNames,
	const std::vector<int> & values)
{
	if (attributeNames.size() != values.size()) {
		throw std::invalid_argument("The attribute name vector must be the same size as the attritbute value vector.");
	}

	int groupId = openOrCreateGroupInRootGroup(groupName);

	hid_t aid = H5Screate(H5S_SCALAR);
	for (size_t i = 0; i < attributeNames.size(); ++i) {
		hid_t attribute_id = H5Acreate2(groupId, attributeNames[i].c_str(), H5T_NATIVE_INT, aid, H5P_DEFAULT, H5P_DEFAULT);
		H5Awrite(attribute_id, H5T_NATIVE_INT, &(values[i]));
		H5Aclose(attribute_id);
	}
	H5Sclose(aid);

	H5Gclose(groupId);
}

void HdfProxy::writeDatasetAttributes(const std::string & datasetName,
	const std::vector<std::string> & attributeNames,
	const std::vector<std::string> & values)
{
	if (attributeNames.size() != values.size()) {
		throw std::invalid_argument("The attribute name vector must be the same size as the attritbute value vector.");
	}

	hid_t dataset = H5Dopen(hdfFile, datasetName.c_str(), H5P_DEFAULT);

	hid_t aid = H5Screate(H5S_SCALAR);
	hid_t atype = H5Tcopy(H5T_C_S1);
	for (size_t i = 0; i < attributeNames.size(); ++i) {
		H5Tset_size(atype, values[i].size());
		hid_t attribute_id = H5Acreate2(dataset, attributeNames[i].c_str(), atype, aid, H5P_DEFAULT, H5P_DEFAULT);
		H5Awrite(attribute_id, atype, values[i].c_str());
		H5Aclose(attribute_id);
	}
	H5Sclose(aid);
	H5Tclose(atype);

	H5Dclose(dataset);
}

void HdfProxy::writeDatasetAttribute(const std::string & datasetName,
	const std::string & attributeName,
	const std::vector<std::string> & values)
{
	hid_t dataset = H5Dopen(hdfFile, datasetName.c_str(), H5P_DEFAULT);

	unsigned int maxStringSize = 0;
	for (size_t i = 0; i < values.size(); ++i) {
		if (values[i].size() > maxStringSize) maxStringSize = values[i].size();
	}
	char* concat = new char[maxStringSize * values.size()];
	for (size_t i = 0; i < values.size(); ++i) {
		for (unsigned int j = 0; j < maxStringSize; ++j) {
			concat[j + i*maxStringSize] = values[i].size() > j ? values[i][j] : '\0';
		}
	}

	const hsize_t valueCount = values.size();
	const hid_t aid = H5Screate_simple(1, &valueCount, nullptr);
	const hid_t atype = H5Tcopy(H5T_C_S1);
	H5Tset_size(atype, maxStringSize);
	const hid_t attribute_id = H5Acreate2(dataset, attributeName.c_str(), atype, aid, H5P_DEFAULT, H5P_DEFAULT);
	H5Awrite(attribute_id, atype, concat);
	delete[] concat;
	H5Aclose(attribute_id);
	H5Sclose(aid);
	H5Tclose(atype);

	H5Dclose(dataset);
}

void HdfProxy::writeDatasetAttributes(const std::string & datasetName,
	const std::vector<std::string> & attributeNames,
	const std::vector<double> & values)
{
	if (attributeNames.size() != values.size()) {
		throw std::invalid_argument("The attribute name vector must be the same size as the attritbute value vector.");
	}

	hid_t dataset = H5Dopen(hdfFile, datasetName.c_str(), H5P_DEFAULT);

	hid_t aid = H5Screate(H5S_SCALAR);
	for (size_t i = 0; i < attributeNames.size(); ++i) {
		hid_t attribute_id = H5Acreate2(dataset, attributeNames[i].c_str(), H5T_NATIVE_DOUBLE, aid, H5P_DEFAULT, H5P_DEFAULT);
		H5Awrite(attribute_id, H5T_NATIVE_DOUBLE, &(values[i]));
		H5Aclose(attribute_id);
	}
	H5Sclose(aid);

	H5Dclose(dataset);
}

void HdfProxy::writeDatasetAttributes(const std::string & datasetName,
	const std::vector<std::string> & attributeNames,
	const std::vector<int> & values)
{
	if (attributeNames.size() != values.size()) {
		throw std::invalid_argument("The attribute name vector must be the same size as the attritbute value vector.");
	}

	hid_t dataset = H5Dopen(hdfFile, datasetName.c_str(), H5P_DEFAULT);

	hid_t aid = H5Screate(H5S_SCALAR);
	for (size_t i = 0; i < attributeNames.size(); ++i) {
		hid_t attribute_id = H5Acreate2(dataset, attributeNames[i].c_str(), H5T_NATIVE_INT, aid, H5P_DEFAULT, H5P_DEFAULT);
		H5Awrite(attribute_id, H5T_NATIVE_INT, &(values[i]));
		H5Aclose(attribute_id);
	}
	H5Sclose(aid);

	H5Dclose(dataset);
}

std::string HdfProxy::readStringAttribute(const std::string & obj_name,
	const std::string & attr_name) const
{
	if (!isOpened()) {
		throw invalid_argument("The HDF5 file must be opened");
	}

	hid_t uuidAtt = H5Aopen_by_name(hdfFile, obj_name.c_str(), attr_name.c_str(), H5P_DEFAULT, H5P_DEFAULT);
	if (uuidAtt < 0) {
		return string();
	}
	hid_t atype = H5Aget_type(uuidAtt);
	if (atype < 0) {
		throw invalid_argument("Cannot read the type of the \"" + attr_name + "\" attribute of \"" + obj_name + "\".");
	}
	size_t aSize = H5Tget_size(atype);
	char* buf = nullptr;
	if (H5Tis_variable_str(atype) <= 0) { // it would also read an array of string as a single string.
		const hid_t attDs = H5Aget_space(uuidAtt);
		const hssize_t stringCount = H5Sget_simple_extent_npoints(attDs);
		aSize *= stringCount;
		buf = new char[aSize];
		H5Sclose(attDs);
	} // else buf is allocated directly by HDF5
	hid_t readingError = H5Aread(uuidAtt, atype, buf);
	if (readingError < 0) {
		if (buf != nullptr) {
			if (H5Tis_variable_str(atype) <= 0) {
				delete[] buf;
			}
			else {
				// buf[i] has been allocated by HDF5 library using malloc/calloc. Consequently we cannot use delete[] on it but free.
				// Especially on windows, since buf[i] has been allocated by the HDF5 library, you will have memory conflict if you don't use the same C standard library for HDF5 lib and for fesapi!
				free(buf);
			}
		}
		throw invalid_argument("Cannot read the \"" + attr_name + "\" attribute of \"" + obj_name + "\".");
	}

	// Build the string to return
	std::string result(buf, aSize);  // Specify the size because an HDF5 string attribute is not forced to be null terminated.
	// Remove null terminating characters
	while (result.back() == '\0') {
		result.pop_back();
	}

	// Memory cleaning
	if (H5Tis_variable_str(atype) <= 0) {
		delete[] buf;
	}
	else {
		// buf[i] has been allocated by HDF5 library using malloc/calloc. Consequently we cannot use delete[] on it but free.
		// Especially on windows, since buf[i] has been allocated by the HDF5 library, you will have memory conflict if you don't use the same C standard library for HDF5 lib and for fesapi!
		free(buf);
	}

	H5Tclose(atype);
	H5Aclose(uuidAtt);

	return result;
}

vector<string> HdfProxy::readStringArrayAttribute(const std::string & obj_name,
	const std::string & attr_name) const
{
	if (!isOpened()) {
		throw invalid_argument("The HDF5 file must be opened");
	}

	vector<string> result;

	hid_t uuidAtt = H5Aopen_by_name(hdfFile, obj_name.c_str(), attr_name.c_str(), H5P_DEFAULT, H5P_DEFAULT);
	if (uuidAtt < 0) {
		return result;
	}
	hid_t aspace = H5Aget_space(uuidAtt);
	if (aspace < 0) {
		throw invalid_argument("Cannot read the dataspace of the \"" + attr_name + "\" attribute of \"" + obj_name + "\".");
	}
	hid_t atype = H5Aget_type(uuidAtt);
	if (atype < 0) {
		throw invalid_argument("Cannot read the type of the \"" + attr_name + "\" attribute of \"" + obj_name + "\".");
	}
	hssize_t globalStringCount = H5Sget_simple_extent_npoints(aspace);

	if (H5Tis_variable_str(atype) <= 0) { // Non variable lenth
		size_t aSizeFixed = H5Tget_size(atype);
		size_t aSize = aSizeFixed * globalStringCount;
		
		char* buf = new char[aSize + 1];
		hid_t readingError = H5Aread(uuidAtt, atype, buf);
		if (readingError < 0) {
			delete[] buf;
			throw invalid_argument("Cannot read the \"" + attr_name + "\" attribute of \"" + obj_name + "\".");
		}
		buf[aSize] = '\0'; //To ensure we have a null terminating char.

		char* bufShift = buf;
		for (size_t i = 0; i < aSize; i += aSizeFixed) {
			if (strlen(bufShift) <= aSizeFixed) {
				result.push_back(bufShift);
			}
			else {
				string tmp(bufShift, aSizeFixed);
				result.push_back(tmp);
			}
			bufShift += aSizeFixed;
		}
		delete[] buf;
	}
	else { // Variable lenth
		char** buf = new char*[globalStringCount];

		hid_t readingError = H5Aread(uuidAtt, atype, buf);
		if (readingError < 0) {
			delete[] buf;
			throw invalid_argument("Cannot read the \"" + attr_name + "\" attribute of \"" + obj_name + "\".");
		}

		for (hssize_t i = 0; i < globalStringCount; ++i) {
			result.push_back(buf[i]);
			// buf[i] has been allocated by HDF5 library using malloc/calloc. Consequently we cannot use delete[] on it but free.
			// Especially on windows, since buf[i] has been allocated by the HDF5 library, you will have memory conflict if you don't use the same C standard library for HDF5 lib and for fesapi!
			free(buf[i]);
		}

		delete[] buf;
	}

	H5Tclose(atype);
	H5Sclose(aspace);
	H5Aclose(uuidAtt);

	return result;
}

double HdfProxy::readDoubleAttribute(const std::string & obj_name,
	const std::string & attr_name) const
{
	if (!isOpened()) {
		throw invalid_argument("The HDF5 file must be opened");
	}

	hid_t uuidAtt = H5Aopen_by_name(hdfFile, obj_name.c_str(), attr_name.c_str(), H5P_DEFAULT, H5P_DEFAULT);
	if (uuidAtt < 0) {
		return numeric_limits<double>::quiet_NaN();
	}

	double result;
	hid_t readingError = H5Aread(uuidAtt, H5T_NATIVE_DOUBLE, &result);
	if (readingError < 0) {
		throw invalid_argument("Cannot read the \"" + attr_name + "\" attribute of \"" + obj_name + "\".");
	}

	H5Aclose(uuidAtt);
	return result;
}

LONG64 HdfProxy::readLongAttribute(const std::string & obj_name,
	const std::string & attr_name) const
{
	if (!isOpened()) {
		throw invalid_argument("The HDF5 file must be opened");
	}

	hid_t uuidAtt = H5Aopen_by_name(hdfFile, obj_name.c_str(), attr_name.c_str(), H5P_DEFAULT, H5P_DEFAULT);
	if (uuidAtt < 0) {
		return (numeric_limits<LONG64>::min)();
	}

	LONG64 result;
	hid_t readingError = H5Aread(uuidAtt, H5T_NATIVE_LLONG, &result);
	if (readingError < 0) {
		throw invalid_argument("Cannot read the \"" + attr_name + "\" attribute of \"" + obj_name + "\".");
	}

	H5Aclose(uuidAtt);
	return result;
}

bool HdfProxy::exist(const std::string & absolutePathInHdfFile) const
{
	return H5Oexists_by_name(hdfFile, absolutePathInHdfFile.c_str(), H5P_DEFAULT) > 0;
}

