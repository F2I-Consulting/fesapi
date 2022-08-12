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

#include <algorithm>
#include <limits>
#include <numeric>
#include <stdexcept>

#include <hdf5.h>

using namespace std;
using namespace EML2_NS;

namespace {
	hid_t convertToHdf5Datatype(COMMON_NS::AbstractObject::numericalDatatypeEnum fesapiDatatype) {
		switch (fesapiDatatype) {
		case COMMON_NS::AbstractObject::numericalDatatypeEnum::DOUBLE: return H5T_NATIVE_DOUBLE;
		case COMMON_NS::AbstractObject::numericalDatatypeEnum::FLOAT: return H5T_NATIVE_FLOAT;
		case COMMON_NS::AbstractObject::numericalDatatypeEnum::INT64: return H5T_NATIVE_INT64;
		case COMMON_NS::AbstractObject::numericalDatatypeEnum::UINT64: return H5T_NATIVE_UINT64;
		case COMMON_NS::AbstractObject::numericalDatatypeEnum::INT32: return H5T_NATIVE_INT32;
		case COMMON_NS::AbstractObject::numericalDatatypeEnum::UINT32: return H5T_NATIVE_UINT32;
		case COMMON_NS::AbstractObject::numericalDatatypeEnum::INT16: return H5T_NATIVE_INT16;
		case COMMON_NS::AbstractObject::numericalDatatypeEnum::UINT16: return H5T_NATIVE_UINT16;
		case COMMON_NS::AbstractObject::numericalDatatypeEnum::INT8: return H5T_NATIVE_INT8;
		case COMMON_NS::AbstractObject::numericalDatatypeEnum::UINT8: return H5T_NATIVE_UINT8;
		default: throw invalid_argument("The FESAPI datatype is unknown.");
		}
	}

	COMMON_NS::AbstractObject::numericalDatatypeEnum convertToFesapiDatatype(hid_t hdf5Datatype) {
		if (H5Tequal(hdf5Datatype, H5T_NATIVE_DOUBLE) > 0)
			return COMMON_NS::AbstractObject::numericalDatatypeEnum::DOUBLE;
		else if (H5Tequal(hdf5Datatype, H5T_NATIVE_FLOAT) > 0)
			return COMMON_NS::AbstractObject::numericalDatatypeEnum::FLOAT;
		else if (H5Tequal(hdf5Datatype, H5T_NATIVE_INT64) > 0)
			return COMMON_NS::AbstractObject::numericalDatatypeEnum::INT64;
		else if (H5Tequal(hdf5Datatype, H5T_NATIVE_UINT64) > 0)
			return COMMON_NS::AbstractObject::numericalDatatypeEnum::UINT64;
		else if (H5Tequal(hdf5Datatype, H5T_NATIVE_INT) > 0)
			return COMMON_NS::AbstractObject::numericalDatatypeEnum::INT32;
		else if (H5Tequal(hdf5Datatype, H5T_NATIVE_UINT) > 0)
			return COMMON_NS::AbstractObject::numericalDatatypeEnum::UINT32;
		else if (H5Tequal(hdf5Datatype, H5T_NATIVE_INT16) > 0)
			return COMMON_NS::AbstractObject::numericalDatatypeEnum::INT16;
		else if (H5Tequal(hdf5Datatype, H5T_NATIVE_UINT16) > 0)
			return COMMON_NS::AbstractObject::numericalDatatypeEnum::UINT16;
		else if (H5Tequal(hdf5Datatype, H5T_NATIVE_INT8) > 0)
			return COMMON_NS::AbstractObject::numericalDatatypeEnum::INT8;
		else if (H5Tequal(hdf5Datatype, H5T_NATIVE_UINT8) > 0)
			return COMMON_NS::AbstractObject::numericalDatatypeEnum::UINT8;

		return COMMON_NS::AbstractObject::numericalDatatypeEnum::UNKNOWN;
	}
}

HdfProxy::HdfProxy(const std::string & packageDirAbsolutePath, const std::string & externalFilePath, COMMON_NS::DataObjectRepository::openingMode hdfPermissionAccess) :
	AbstractHdfProxy(packageDirAbsolutePath, externalFilePath, hdfPermissionAccess), hdfFile(-1), compressionLevel(0), openedGroups() {}

// create an attribute at the file level to store the uuid of the corresponding COMMON hdf proxy.
void HdfProxy::writeUuidAttribute()
{
	const hid_t aid = H5Screate(H5S_SCALAR);
	if (aid < 0) {
		throw invalid_argument("The HDF5 uuid file attribute dataspace could not have been created.");
	}
	const hid_t atype = H5Tcopy(H5T_C_S1);
	if (atype < 0) {
		throw invalid_argument("The HDF5 uuid file attribute datatype could not have been created by copy.");
	}
	if (H5Tset_size(atype, getUuid().size()) < 0) {
		throw invalid_argument("Cannot set the size of the HDF5 uuid file attribute.");
	}
	const hid_t attribute_id = H5Acreate2(hdfFile, "uuid", atype, aid, H5P_DEFAULT, H5P_DEFAULT);
	if (attribute_id < 0) {
		throw invalid_argument("The HDF5 uuid file attribute could not have been created.");
	}
	if (H5Awrite(attribute_id, atype, getUuid().c_str()) < 0) {
		throw invalid_argument("The uuid file attribute could not have been written.");
	}

	// Close the attribute.
	if (H5Sclose(aid) < 0) {
		throw invalid_argument("The HDF5 uuid file attribute dataspace could not have been closed.");
	}
	if (H5Tclose(atype) < 0) {
		throw invalid_argument("The HDF5 uuid file attribute datatype could not have been closed.");
	}
	if (H5Aclose(attribute_id) < 0) {
		throw invalid_argument("The HDF5 uuid file attribute could not have been closed.");
	}
}

void HdfProxy::open()
{
	if (hdfFile > -1) {
		close();
	}

	const std::string fullName = (packageDirectoryAbsolutePath.empty() || packageDirectoryAbsolutePath.back() == '/' || packageDirectoryAbsolutePath.back() == '\\' ? packageDirectoryAbsolutePath : packageDirectoryAbsolutePath + '/')
		+ relativeFilePath;
	if (openingMode == COMMON_NS::DataObjectRepository::openingMode::READ_ONLY || openingMode == COMMON_NS::DataObjectRepository::openingMode::READ_WRITE_DO_NOT_CREATE) {
		if (H5Fis_hdf5(fullName.c_str()) > 0) {
			hdfFile = H5Fopen(fullName.c_str(),
				openingMode == COMMON_NS::DataObjectRepository::openingMode::READ_ONLY ? H5F_ACC_RDONLY : H5F_ACC_RDWR,
				H5P_DEFAULT);
			if (hdfFile < 0) {
				throw invalid_argument("HDF5 library recognizes the HDF5 file but can not open it : " + fullName);
			}

			// Check the uuid
			const string hdfUuid = readStringAttribute(".", "uuid");
			if (getUuid() != hdfUuid) {
				getRepository()->addWarning("The uuid \"" + hdfUuid + "\" attribute of the HDF5 file is not the same as the uuid \"" + getUuid() + "\" of the xml EpcExternalPart.");
			}
		}
		else {
			throw invalid_argument("The HDF5 file " + fullName + " does not exist or is not a valid HDF5 file or is not accessible.");
		}
	}
	else if (openingMode == COMMON_NS::DataObjectRepository::openingMode::READ_WRITE) {
		hid_t access_props = H5Pcreate (H5P_FILE_ACCESS);
#if H5_VERSION_GE(1,10,0)
		H5Pset_libver_bounds (access_props, H5F_LIBVER_V18, H5F_LIBVER_V18);
#endif

		hdfFile = H5Fcreate(fullName.c_str(), H5F_ACC_EXCL, H5P_DEFAULT, access_props);

		if (hdfFile < 0) {
			openingMode = COMMON_NS::DataObjectRepository::openingMode::READ_WRITE_DO_NOT_CREATE;
			open();
			openingMode = COMMON_NS::DataObjectRepository::openingMode::READ_WRITE;
		}
		else {
			writeUuidAttribute();
		}
	}
	else if (openingMode == COMMON_NS::DataObjectRepository::openingMode::OVERWRITE) {
		hid_t access_props = H5Pcreate (H5P_FILE_ACCESS);
#if H5_VERSION_GE(1,10,0)
		H5Pset_libver_bounds (access_props, H5F_LIBVER_V18, H5F_LIBVER_V18);
#endif

		hdfFile = H5Fcreate(fullName.c_str(), H5F_ACC_TRUNC, H5P_DEFAULT, access_props);
		if (hdfFile < 0) {
			throw invalid_argument("Can not create HDF5 file : " + fullName);
		}

		writeUuidAttribute();
	}
	else {
		throw invalid_argument("The HDF5 permission access is unknown.");
	}
}

void HdfProxy::close()
{
	for (auto it : openedGroups) {
		if (H5Gclose(it.second) < 0) {
			throw invalid_argument("The HDF5 group " + it.first + " could not have been closed.");
		}
	}
	openedGroups.clear();

	if (hdfFile > -1) {
		H5Fclose(hdfFile);
		hdfFile = -1;
	}
}

void HdfProxy::readArrayNdOfValues(const std::string & datasetName, void* values, hid_t datatype)
{
	if (!isOpened()) {
		open();
	}

	hid_t dataset = H5Dopen(hdfFile, datasetName.c_str(), H5P_DEFAULT);
	if (dataset < 0) {
		throw invalid_argument("The HDF5 dataset " + datasetName + " could not be opened.");
	}
	hid_t readingError = H5Dread (dataset, datatype, H5S_ALL, H5S_ALL, H5P_DEFAULT, values);

	H5Dclose(dataset);
	if (readingError < 0) {
		throw invalid_argument("The HDF5 dataset " + datasetName + " could not be read.");
	}
}

void HdfProxy::readArrayNdOfValues(
	const std::string & datasetName,
	void* values,
	unsigned long long const * numValuesInEachDimension,
	unsigned long long const * offsetInEachDimension,
	unsigned int numDimensions, hid_t datatype)
{
	readArrayNdOfValues(datasetName, values, numValuesInEachDimension, offsetInEachDimension, nullptr, nullptr, numDimensions, datatype);
}

void HdfProxy::readArrayNdOfValues(
	const std::string & datasetName,
	void* values,
	unsigned long long const * blockCountPerDimension,
	unsigned long long const * offsetInEachDimension,
	unsigned long long const * strideInEachDimension,
	unsigned long long const * blockSizeInEachDimension,
	unsigned int numDimensions, hid_t datatype)
{
	if (!isOpened()) {
		open();
	}

	hid_t dataset = H5Dopen(hdfFile, datasetName.c_str(), H5P_DEFAULT);
	if (dataset < 0) {
		throw invalid_argument("The HDF5 dataset " + datasetName + " could not be opened.");
	}

	hid_t filespace = H5Dget_space(dataset);
	if (filespace < 0) {
		H5Dclose(dataset);
		throw invalid_argument("The filespace of HDF5 dataset " + datasetName + " could not be opened.");
	}
	herr_t result = H5Sselect_hyperslab(filespace, H5S_SELECT_SET, offsetInEachDimension, strideInEachDimension, blockCountPerDimension, blockSizeInEachDimension);
	if (result < 0) {
		H5Sclose(filespace);
		H5Dclose(dataset);
		throw invalid_argument("The hyperslabbing of HDF5 dataset " + datasetName + " could not be selected.");
	}

	if (H5Sget_simple_extent_ndims(filespace) != (int) numDimensions) {
		H5Sclose(filespace);
		H5Dclose(dataset);
		throw invalid_argument("The HDF5 dataset " + datasetName + " does not have " + std::to_string(numDimensions) + " dimensions.");
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
		throw invalid_argument("The memory space for the slabbing of HDF5 dataset " + datasetName + " could not be created.");
	}

	hid_t readingError = H5Dread(dataset, datatype, memspace, filespace, H5P_DEFAULT, values);

	H5Sclose(memspace);
	H5Sclose(filespace);
	H5Dclose(dataset);

	if (readingError < 0) {
		throw invalid_argument("The HDF5 dataset " + datasetName + " could not be read.");
	}
}

void HdfProxy::selectArrayNdOfValues(
	const std::string & datasetName,
	unsigned long long const * blockCountPerDimension,
	unsigned long long const * offsetInEachDimension,
	unsigned long long const * strideInEachDimension,
	unsigned long long const * blockSizeInEachDimension,
	unsigned int numDimensions,
	bool newSelection,
	hid_t & dataset,
	hid_t & filespace)
{
	if (!isOpened()) {
		open();
	}

	if (newSelection) {
		dataset = H5Dopen(hdfFile, datasetName.c_str(), H5P_DEFAULT);
		if (dataset < 0) {
			throw invalid_argument("The HDF5 dataset " + datasetName + " could not be opened.");
		}

		filespace = H5Dget_space(dataset);
		if (filespace < 0) {
			H5Dclose(dataset);
			throw invalid_argument("The filespace of HDF5 dataset " + datasetName + " could not be opened.");
		}

		if (H5Sget_simple_extent_ndims(filespace) != (int) numDimensions)
		{
			H5Sclose(filespace);
			H5Dclose(dataset);
			throw invalid_argument("The HDF5 dataset " + datasetName + " does not have " + std::to_string(numDimensions) + " dimensions.");
		}
	}

	herr_t result = H5Sselect_hyperslab(filespace, newSelection ? H5S_SELECT_SET : H5S_SELECT_OR, offsetInEachDimension, strideInEachDimension, blockCountPerDimension, blockSizeInEachDimension);
	if (result < 0) {
		H5Sclose(filespace);
		H5Dclose(dataset);
		throw invalid_argument("The hyperslabbing region cannot be added to the " + datasetName + " selected region.");
	}
}

void HdfProxy::readArrayNdOfValues(
	hid_t dataset,
	hid_t filespace,
	void* values, 
	unsigned long long slabSize, 
	hid_t datatype)
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
		throw invalid_argument("The memory space for the slabbing of HDF5 dataset " + datasetName + " could not be created.");
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
		throw invalid_argument("The HDF5 dataset " + datasetName + " could not be read.");
	}
}

COMMON_NS::AbstractObject::numericalDatatypeEnum HdfProxy::getNumericalDatatype(const std::string & datasetName)
{
	if (!isOpened()) {
		open();
	}

	hid_t dataset = H5Dopen(hdfFile, datasetName.c_str(), H5P_DEFAULT);
	hid_t datatype = H5Dget_type(dataset);
	hid_t native_datatype = H5Tget_native_type(datatype, H5T_DIR_ASCEND);

	H5Dclose(dataset);
	H5Tclose(datatype);

	return convertToFesapiDatatype(native_datatype);
}

int HdfProxy::getHdfDatatypeClassInDataset(const std::string & datasetName)
{
	if (!isOpened()) {
		open();
	}

	hid_t dataset = H5Dopen(hdfFile, datasetName.c_str(), H5P_DEFAULT);
	hid_t datatype = H5Dget_type(dataset);
	H5T_class_t result = H5Tget_class(datatype);

	H5Dclose(dataset);
	H5Tclose(datatype);

	return result;
}

vector<unsigned long long> HdfProxy::reduceForChunking(hid_t datatype,
	const unsigned long long * numValuesInEachDimension,
	unsigned int numDimensions) const
{
	// Get size in bytes of this datatype.
	const size_t elementSize = H5Tget_size(datatype);
	if (maxChunkSize < elementSize) {
		throw std::invalid_argument("The maximum chunk size cannot be inferior to the size of one element of the dataset.");
	}

	vector<unsigned long long> chunkDimensions(numDimensions);
	for (unsigned int i = 0; i < numDimensions; ++i) {
		chunkDimensions[i] = numValuesInEachDimension[i];
	}

	// Compute product of all dimensions.
	unsigned long long dimensionProduct =
		std::accumulate(chunkDimensions.begin(),
			chunkDimensions.end(),
			1ULL,
			std::multiplies<unsigned long long>());

	// If the total size exceeds the allowed maximum chunk size,
	// reduce the chunk dimensions untill it is necessary
	size_t totalSize = dimensionProduct * elementSize;
	size_t dimensionToDivide = 0;
	while (totalSize > maxChunkSize) {
		while (chunkDimensions[dimensionToDivide] == 1) {
			++dimensionToDivide;
		}

		totalSize /= chunkDimensions[dimensionToDivide];
		chunkDimensions[dimensionToDivide] = maxChunkSize / totalSize;
		if (chunkDimensions[dimensionToDivide] == 0) {
			chunkDimensions[dimensionToDivide] = 1;
		}
		// else the while loop must exit
	}

	return chunkDimensions;
}

void HdfProxy::writeItemizedListOfList(const string & groupName,
	const string & name,
	COMMON_NS::AbstractObject::numericalDatatypeEnum cumulativeLengthDatatype,
	const void * cumulativeLength,
	unsigned long long cumulativeLengthSize,
	COMMON_NS::AbstractObject::numericalDatatypeEnum elementsDatatype,
	const void * elements,
	unsigned long long elementsSize)
{
	if (!isOpened()) {
		open();
	}

	hid_t parentGrp = openOrCreateGroup(groupName);
	hid_t grp = H5Gcreate(parentGrp, name.c_str(), H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);

	// ************* CUMULATIVE LENGTH *************
	// Create dataspace for the dataset in the file.
	hid_t fspaceCL = H5Screate_simple(1, &cumulativeLengthSize, nullptr);

	hid_t datasetCL;
	const hid_t hdf5DatatypeCL = convertToHdf5Datatype(cumulativeLengthDatatype);
	if (compressionLevel > 0) {
		// Create dataset and write it into the file.
		hid_t dcpl = H5Pcreate (H5P_DATASET_CREATE);
		H5Pset_deflate (dcpl, compressionLevel);

		vector<unsigned long long> newValues =
			reduceForChunking (hdf5DatatypeCL,
					   &cumulativeLengthSize,
					   1);
		H5Pset_chunk (dcpl, 1, newValues.data());

		datasetCL = H5Dcreate(grp, CUMULATIVE_LENGTH_DS_NAME, hdf5DatatypeCL, fspaceCL, H5P_DEFAULT, dcpl, H5P_DEFAULT);

		H5Pclose(dcpl);
	}
	else {
		datasetCL = H5Dcreate(grp, CUMULATIVE_LENGTH_DS_NAME, hdf5DatatypeCL, fspaceCL, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
	}

	H5Dwrite(datasetCL, hdf5DatatypeCL, H5S_ALL, H5S_ALL, H5P_DEFAULT, cumulativeLength);
	H5Sclose(fspaceCL);
	H5Dclose(datasetCL);

	// ************* ELEMENTS *************
	// Create dataspace for the dataset in the file.
	hid_t fspaceE = H5Screate_simple(1, &elementsSize, nullptr);

	hid_t datasetE;
	const hid_t hdf5DatatypeE = convertToHdf5Datatype(elementsDatatype);
	if (compressionLevel > 0) {
		// Create dataset and write it into the file.
		hid_t dcpl = H5Pcreate (H5P_DATASET_CREATE);
		H5Pset_deflate (dcpl, compressionLevel);

		vector<unsigned long long> newValues =
			reduceForChunking (hdf5DatatypeE,
					   &elementsSize,
					   1);

		H5Pset_chunk (dcpl, 1, newValues.data());

		datasetE = H5Dcreate(grp, ELEMENTS_DS_NAME, hdf5DatatypeE, fspaceE, H5P_DEFAULT, dcpl, H5P_DEFAULT);

		H5Pclose(dcpl);
	}
	else {
		datasetE = H5Dcreate(grp, ELEMENTS_DS_NAME, hdf5DatatypeE, fspaceE, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
	}

	H5Dwrite(datasetE, hdf5DatatypeE, H5S_ALL, H5S_ALL, H5P_DEFAULT, elements);
	H5Sclose(fspaceE);
	H5Dclose(datasetE);

	H5Gclose(grp);
}

std::vector<unsigned long long> HdfProxy::getElementCountPerDimension(const std::string & datasetName)
{
	if (!isOpened()) {
		open();
	}

	hid_t dataset = H5Dopen(hdfFile, datasetName.c_str(), H5P_DEFAULT);
	if (dataset < 0) {
		throw invalid_argument("The dataset " + datasetName + " could not be opened.");
	}

	hid_t dataspace = H5Dget_space(dataset);
	if (dataspace < 0) {
		H5Dclose(dataset);
		throw invalid_argument("The dataspace for the dataset " + datasetName + " could not be opened.");
	}

	int ndims = H5Sget_simple_extent_ndims(dataspace);
	if (ndims < 0) {
		H5Sclose(dataspace);
		H5Dclose(dataset);
		throw invalid_argument("The number of dimensions of the dataspace for the dataset " + datasetName + " could not be read.");
	}

	std::unique_ptr<hsize_t[]> dims(new hsize_t[ndims]);
	ndims = H5Sget_simple_extent_dims(dataspace, dims.get(), nullptr);

	H5Sclose(dataspace);
	H5Dclose(dataset);
	if (ndims < 0) {
		throw invalid_argument("The number of elements in each dimension of the dataspace for the dataset " + datasetName + " could not be read.");
	}

	std::vector<unsigned long long> result;
	for (auto i = 0; i < ndims; ++i) {
		result.push_back(dims[i]);
	}

	return result;
}

void HdfProxy::writeArrayNd(const std::string & groupName,
	const std::string & name,
	COMMON_NS::AbstractObject::numericalDatatypeEnum datatype,
	const void * values,
	const unsigned long long * numValuesInEachDimension,
	unsigned int numDimensions)
{
	if (!isOpened()) {
		open();
	}

	hid_t grp = openOrCreateGroup(groupName);
	if (grp < 0) {
		throw invalid_argument("The group " + groupName + " could not be created.");
	}

	// Create the data space
	hid_t space = H5Screate_simple(numDimensions, numValuesInEachDimension, nullptr);
	if (space < 0) {
		throw invalid_argument("The dataspace for the dataset " + name + " could not be created.");
	}

    // Create the dataset.
	herr_t error;
	hid_t dataset;
	const hid_t hdf5Datatype = convertToHdf5Datatype(datatype);
	if (compressionLevel) {
		hid_t dcpl = H5Pcreate (H5P_DATASET_CREATE);
		H5Pset_deflate (dcpl, compressionLevel);
		vector<unsigned long long> newValues =
			reduceForChunking (hdf5Datatype,
					   numValuesInEachDimension,
					   numDimensions);

		H5Pset_chunk (dcpl, numDimensions, newValues.data());

		dataset = H5Dcreate(grp, name.c_str(), hdf5Datatype, space, H5P_DEFAULT, dcpl, H5P_DEFAULT);
		H5Pclose(dcpl);
		if (dataset < 0) {
			H5Sclose(space);
			throw invalid_argument("The dataset " + name + " could not be created.");
		}
	}
	else {
		dataset = H5Dcreate (grp, name.c_str(), hdf5Datatype, space, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
		if (dataset < 0) {
			H5Sclose(space);
			throw invalid_argument("The dataset " + name + " could not be created.");
		}
	}

	error = H5Dwrite(dataset, hdf5Datatype, H5S_ALL, H5S_ALL, H5P_DEFAULT, values);
	H5Sclose(space);
	H5Dclose(dataset);
	if (error < 0) {
		throw invalid_argument("The data could not be written in dataset " + name);
	}
}

void HdfProxy::createArrayNd(
	const std::string& groupName,
	const std::string& datasetName,
	COMMON_NS::AbstractObject::numericalDatatypeEnum datatype,
	const unsigned long long* numValuesInEachDimension,
	unsigned int numDimensions
) {
	if (!isOpened()) {
		open();
	}

	hid_t grp = openOrCreateGroup(groupName);
	if (grp < 0) {
		throw invalid_argument("The group " + groupName + " could not be created.");
	}

	// Create the data space
	hid_t space = H5Screate_simple(numDimensions, numValuesInEachDimension, nullptr);
	if (space < 0) {
		throw invalid_argument("The dataspace for the dataset " + datasetName + " could not be created.");
	}

	// Create the dataset.
	hid_t dataset;
	const hid_t hdf5Datatype = convertToHdf5Datatype(datatype);
	if (compressionLevel > 0) {
		hid_t dcpl = H5Pcreate (H5P_DATASET_CREATE);
		H5Pset_deflate (dcpl, compressionLevel);

		vector<unsigned long long> newValues =
			reduceForChunking (hdf5Datatype,
			numValuesInEachDimension,
			numDimensions);

		H5Pset_chunk (dcpl, numDimensions, newValues.data());

		dataset = H5Dcreate(grp, datasetName.c_str(), hdf5Datatype, space, H5P_DEFAULT, dcpl, H5P_DEFAULT);
		H5Pclose(dcpl);
		if (dataset < 0) {			
			H5Sclose(space);
			throw invalid_argument("The dataset " + datasetName + " could not be created.");
		}
	}
	else {
		dataset = H5Dcreate(grp, datasetName.c_str(), hdf5Datatype, space, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
		if (dataset < 0) {
			H5Sclose(space);
			throw invalid_argument("The dataset " + datasetName + " could not be created.");
		}
	}

	H5Sclose(space);
	H5Dclose(dataset);
}

void HdfProxy::writeArrayNdSlab(
	const string& groupName,
	const string& datasetName,
	COMMON_NS::AbstractObject::numericalDatatypeEnum datatype,
	const void* values,
	const hsize_t* numValuesInEachDimension,
	const hsize_t* offsetInEachDimension,
	unsigned int numDimensions)
{
	if (!isOpened()) {
		open();
	}

	hid_t grp = openOrCreateGroup(groupName);
	hid_t dataset = H5Dopen(grp, datasetName.c_str(), H5P_DEFAULT);
	if (dataset < 0) {
		throw invalid_argument("The HDF5 dataset " + datasetName + " could not be opened.");
	}
	
	hid_t filespace = H5Dget_space(dataset);
	if (filespace < 0) {
		throw invalid_argument("The resqml dataspace of " + datasetName + " could not be opened.");
	}
	herr_t errorCode = H5Sselect_hyperslab(filespace, H5S_SELECT_SET, offsetInEachDimension, nullptr, numValuesInEachDimension, nullptr);
	if (errorCode < 0) {
		H5Sclose(filespace);
		H5Dclose(dataset);
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
		throw invalid_argument("The dataspace for the slab of the dataset " + datasetName + " could not be created.");
	}

	hid_t datatypeOfDataset = H5Dget_type(dataset);
	if (datatypeOfDataset < 0) {
		throw invalid_argument("The datatype of the dataset " + datasetName + " could not be retrieved.");
	}
	const hid_t hdf5Datatype = convertToHdf5Datatype(datatype);
	if (H5Tequal(hdf5Datatype, datatypeOfDataset) <= 0) {
		throw invalid_argument("The given datatype for the slab is not compatible with the datatype of the dataset.");
	}
	errorCode = H5Dwrite(dataset, hdf5Datatype, memspace, filespace, H5P_DEFAULT, values);

	H5Sclose(memspace);
	H5Sclose(filespace);
	H5Dclose(dataset);

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
	hsize_t const * numValuesInEachDimension,
	hsize_t const * offsetInEachDimension,
	unsigned int numDimensions)
{
	readArrayNdOfValues(datasetName, values,
			numValuesInEachDimension, offsetInEachDimension, numDimensions,
			H5T_NATIVE_DOUBLE);
}

void HdfProxy::readArrayNdOfDoubleValues(
	const std::string & datasetName, double* values,
	hsize_t const * blockCountPerDimension,
	hsize_t const * offsetInEachDimension,
	hsize_t const * strideInEachDimension,
	hsize_t const * blockSizeInEachDimension,
	unsigned int numDimensions)
{
	readArrayNdOfValues(datasetName, values,
		blockCountPerDimension, offsetInEachDimension, strideInEachDimension, blockSizeInEachDimension, numDimensions,
		H5T_NATIVE_DOUBLE);
}

void HdfProxy::readArrayNdOfDoubleValues(
	hid_t dataset,
	hid_t filespace,
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
	hsize_t const * numValuesInEachDimension,
	hsize_t const * offsetInEachDimension,
	unsigned int numDimensions)
{
	readArrayNdOfValues(datasetName, values,
			numValuesInEachDimension, offsetInEachDimension, numDimensions,
			H5T_NATIVE_FLOAT);
}

void HdfProxy::readArrayNdOfInt64Values(const std::string & datasetName, int64_t* values)
{
	readArrayNdOfValues(datasetName, values, H5T_NATIVE_INT64);
}

void HdfProxy::readArrayNdOfInt64Values(
	const std::string& datasetName, int64_t* values,
	hsize_t const * numValuesInEachDimension,
	hsize_t const * offsetInEachDimension,
	unsigned int numDimensions)
{
	readArrayNdOfValues(datasetName, values,
			numValuesInEachDimension, offsetInEachDimension, numDimensions,
		H5T_NATIVE_INT64);
}

void HdfProxy::readArrayNdOfUInt64Values(const std::string & datasetName, uint64_t* values)
{
	readArrayNdOfValues(datasetName, values, H5T_NATIVE_UINT64);
}

void HdfProxy::readArrayNdOfIntValues(const std::string & datasetName, int* values)
{
	readArrayNdOfValues(datasetName, values, H5T_NATIVE_INT);
}

void HdfProxy::readArrayNdOfIntValues(
	const std::string & datasetName, int* values,
	hsize_t const * numValuesInEachDimension,
	hsize_t const * offsetInEachDimension,
	unsigned int numDimensions)
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

hid_t HdfProxy::openOrCreateGroup(const string & groupName)
{
	auto alreadyOpened = openedGroups.find(groupName);
	if (alreadyOpened != openedGroups.end()) {
		return alreadyOpened->second;
	}

	// The first char must be a slash
	if (groupName.empty() || groupName[0] != '/') {
		throw std::invalid_argument("The group to create is not correct. It must start with a slash and it is : " + groupName);
	}

	if (!isOpened()) {
		open();
	}

	std::string absoluteGroupName = "";
	hid_t currentOpenedGroup = hdfFile;
	size_t nextGroupStartIndex = 1;
	size_t nextSlashIndex = groupName.find("/", nextGroupStartIndex);
	if (nextSlashIndex == std::string::npos && nextGroupStartIndex < groupName.size()) {
		nextSlashIndex = groupName.size();
	}
	while (nextSlashIndex != std::string::npos) {
		const std::string relativeGroupName = groupName.substr(nextGroupStartIndex, nextSlashIndex - nextGroupStartIndex);
		absoluteGroupName += "/" + relativeGroupName;
		alreadyOpened = openedGroups.find(absoluteGroupName);
		if (alreadyOpened != openedGroups.end()) {
			currentOpenedGroup = alreadyOpened->second;
		}
		else {
			currentOpenedGroup = H5Lexists(currentOpenedGroup, relativeGroupName.c_str(), H5P_DEFAULT) > 0
				? H5Gopen(currentOpenedGroup, relativeGroupName.c_str(), H5P_DEFAULT)
				: H5Gcreate(currentOpenedGroup, relativeGroupName.c_str(), H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
			if (currentOpenedGroup < 0) {
				throw invalid_argument("The group " + absoluteGroupName + " could not be created.");
			}
			openedGroups[absoluteGroupName] = currentOpenedGroup;
		}
		nextGroupStartIndex = nextSlashIndex + 1;
		nextSlashIndex = groupName.find("/", nextGroupStartIndex);
		if (nextSlashIndex == std::string::npos && nextGroupStartIndex < groupName.size()) {
			nextSlashIndex = groupName.size();
		}
	}

	return currentOpenedGroup;
}

void HdfProxy::writeGroupAttributes(const std::string & groupName,
	const std::vector<std::string> & attributeNames,
	const std::vector<std::string> & values)
{
	if (attributeNames.size() != values.size()) {
		throw std::invalid_argument("The attribute name vector must be the same size as the attritbute value vector.");
	}

	hid_t groupId = openOrCreateGroup(groupName);

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
}

void HdfProxy::writeGroupAttribute(const std::string & groupName,
	const std::string & attributeName,
	const std::vector<std::string> & values)
{
	const hid_t groupId = openOrCreateGroup(groupName);

	size_t maxStringSize = 0;
	for (size_t i = 0; i < values.size(); ++i) {
		if (values[i].size() > maxStringSize) maxStringSize = values[i].size();
	}
	maxStringSize++;
	std::unique_ptr<char[]> concat(new char[maxStringSize * values.size()]);
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
	H5Awrite(attribute_id, atype, concat.get());
	H5Aclose(attribute_id);
	H5Sclose(aid);
	H5Tclose(atype);
}

void HdfProxy::writeGroupAttributes(const std::string & groupName,
	const std::vector<std::string> & attributeNames,
	const std::vector<double> & values)
{
	if (attributeNames.size() != values.size()) {
		throw std::invalid_argument("The attribute name vector must be the same size as the attritbute value vector.");
	}

	hid_t groupId = openOrCreateGroup(groupName);

	hid_t aid = H5Screate(H5S_SCALAR);
	for (size_t i = 0; i < attributeNames.size(); ++i) {
		hid_t attribute_id = H5Acreate2(groupId, attributeNames[i].c_str(), H5T_NATIVE_DOUBLE, aid, H5P_DEFAULT, H5P_DEFAULT);
		H5Awrite(attribute_id, H5T_NATIVE_DOUBLE, &(values[i]));
		H5Aclose(attribute_id);
	}
	H5Sclose(aid);
}

void HdfProxy::writeGroupAttributes(const std::string & groupName,
	const std::vector<std::string> & attributeNames,
	const std::vector<int> & values)
{
	if (attributeNames.size() != values.size()) {
		throw std::invalid_argument("The attribute name vector must be the same size as the attritbute value vector.");
	}

	hid_t groupId = openOrCreateGroup(groupName);

	hid_t aid = H5Screate(H5S_SCALAR);
	for (size_t i = 0; i < attributeNames.size(); ++i) {
		hid_t attribute_id = H5Acreate2(groupId, attributeNames[i].c_str(), H5T_NATIVE_INT, aid, H5P_DEFAULT, H5P_DEFAULT);
		H5Awrite(attribute_id, H5T_NATIVE_INT, &(values[i]));
		H5Aclose(attribute_id);
	}
	H5Sclose(aid);
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

	size_t maxStringSize = 0;
	for (size_t i = 0; i < values.size(); ++i) {
		if (values[i].size() > maxStringSize) maxStringSize = values[i].size();
	}
	std::unique_ptr<char[]> concat(new char[maxStringSize * values.size()]);
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
	H5Awrite(attribute_id, atype, concat.get());
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
		throw invalid_argument("The HDF5 file is not opened");
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
	while (result[result.size()-1] == '\0') {
		result.resize(result.size()-1);
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
		throw invalid_argument("The HDF5 file is not opened");
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
		throw invalid_argument("The HDF5 file is not opened");
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

int64_t HdfProxy::readLongAttribute(const std::string & obj_name,
	const std::string & attr_name) const
{
	if (!isOpened()) {
		throw invalid_argument("The HDF5 file must be opened");
	}

	hid_t uuidAtt = H5Aopen_by_name(hdfFile, obj_name.c_str(), attr_name.c_str(), H5P_DEFAULT, H5P_DEFAULT);
	if (uuidAtt < 0) {
		return (numeric_limits<int64_t>::min)();
	}

	int64_t result;
	hid_t readingError = H5Aread(uuidAtt, H5T_NATIVE_INT64, &result);
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

bool HdfProxy::isCompressed(const std::string & datasetName)
{
	if (!isOpened()) {
		open();
	}

	hid_t dataset_id = H5Dopen(hdfFile, datasetName.c_str(), H5P_DEFAULT);
	if (dataset_id < 0) {
		throw invalid_argument("The HDF5 dataset " + datasetName + " could not be opened.");
	}
	/* Retrieve filter information. */
	hid_t plist_id = H5Dget_create_plist(dataset_id);
	bool compressed = false;

	int numfilt = H5Pget_nfilters(plist_id);
	if (numfilt < 0) {
		throw invalid_argument("The filters cannot be got on the HDF5 dataset " + datasetName);
	}
	for (unsigned i = 0; i < static_cast<unsigned>(numfilt); ++i) {
		size_t nelmts = 0;
		unsigned flags, filter_info;
		H5Z_filter_t filter_type = H5Pget_filter(plist_id, i, &flags, &nelmts, nullptr, 0, nullptr, &filter_info);
		printf("Filter Type: ");
		if (filter_type == H5Z_FILTER_DEFLATE ||
			filter_type == H5Z_FILTER_SZIP ||
			filter_type == H5Z_FILTER_NBIT ||
			filter_type == H5Z_FILTER_SCALEOFFSET) {
			compressed = true;
			break;
		}
	}

	H5Dclose(dataset_id);
	H5Pclose(plist_id);

	return compressed;
}

std::vector<unsigned long long> HdfProxy::getElementCountPerChunkDimension(const std::string & datasetName)
{
	if (!isOpened()) {
		open();
	}

	std::vector<unsigned long long> result;

	hid_t dataset_id = H5Dopen(hdfFile, datasetName.c_str(), H5P_DEFAULT);
	if (dataset_id < 0) {
		throw invalid_argument("The HDF5 dataset " + datasetName + " could not be opened.");
	}
	/*
	 * Get creation properties list.
	 */
	hid_t plist_id = H5Dget_create_plist(dataset_id);/* Get properties handle first. */

	if (H5D_CHUNKED == H5Pget_layout(plist_id)) {
		/*
		 * Get rank information
		 */
		hid_t dataspace = H5Dget_space(dataset_id);
		int dsRank = H5Sget_simple_extent_ndims(dataspace);
		H5Sclose(dataspace);

		/*
		 * Get chunking information: rank and dimensions
		 */
		std::unique_ptr<hsize_t[]> chunkDims(new hsize_t[dsRank]);
		int chunkRank = H5Pget_chunk(plist_id, dsRank, chunkDims.get());
		if (chunkRank < 0) {
			throw invalid_argument("The chunk dimension cannot be retrieved in " + datasetName);
		}
		if (chunkRank != dsRank) {
			throw invalid_argument("The chunk rank in " + datasetName + " is not the same as the dataset rank.");
		}

		for (auto i = 0; i < dsRank; ++i) {
			result.push_back(chunkDims[i]);
		}
	}

	H5Dclose(dataset_id);
	H5Pclose(plist_id);

	return result;
}
