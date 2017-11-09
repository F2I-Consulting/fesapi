/*-----------------------------------------------------------------------
Copyright F2I-CONSULTING, (2014-2017)

philippe.verney@f2i-consulting.com

This software is a computer program whose purpose is to access to data formatted using Energistics standards.

This software is governed by the CeCILL-B license under French law and
abiding by the rules of distribution of free software.  You can  use, 
modify and/ or redistribute the software under the terms of the CeCILL-B
license as circulated by CEA, CNRS and INRIA at the following URL
"http://www.cecill.info". 

As a counterpart to the access to the source code and  rights to copy,
modify and redistribute granted by the license, users are provided only
with a limited warranty  and the software's author,  the holder of the
economic rights,  and the successive licensors  have only  limited
liability. 

In this respect, the user's attention is drawn to the risks associated
with loading,  using,  modifying and/or developing or reproducing the
software by the user in light of its specific status of free software,
that may mean  that it is complicated to manipulate,  and  that  also
therefore means  that it is reserved for developers  and  experienced
professionals having in-depth computer knowledge. Users are therefore
encouraged to load and test the software's suitability as regards their
requirements in conditions enabling the security of their systems and/or 
data to be ensured and,  more generally, to use and operate it in the 
same conditions as regards security. 

The fact that you are presently reading this means that you have had
knowledge of the CeCILL-B license and that you accept its terms.
-----------------------------------------------------------------------*/
#pragma once

#include "common/EpcExternalPartReference.h"
#include "resqml2/AbstractRepresentation.h"
#include "prodml2_0/DasAcquisition.h"

#define CUMULATIVE_LENGTH_DS_NAME "cumulativeLength"
#define ELEMENTS_DS_NAME "elements"

namespace common
{
	class DLL_IMPORT_OR_EXPORT AbstractHdfProxy : public EpcExternalPartReference
	{
	protected:

		/**
		* @param soapContext	The soap context where the underlying gsoap proxy is going to be created.
		*/
		AbstractHdfProxy(const std::string & packageDirAbsolutePath, const std::string & externalFilePath);

		AbstractHdfProxy(gsoap_resqml2_0_1::_eml20__EpcExternalPartReference* fromGsoap, const std::string & packageDirAbsolutePath, const std::string & externalFilePath) :
			EpcExternalPartReference(fromGsoap, packageDirAbsolutePath, externalFilePath) {}

		AbstractHdfProxy(gsoap_eml2_1::_eml21__EpcExternalPartReference* fromGsoap, const std::string & packageDirAbsolutePath, const std::string & externalFilePath) :
			EpcExternalPartReference(fromGsoap, packageDirAbsolutePath, externalFilePath) {}

		/**
		* Instantiate and initialize the gsoap proxy v2.0.1.
		* This method is defined in order to be used in derived class without having to link to generated gsoap files.
		*/
		void initGsoapProxy(soap* soapContext, const std::string & guid, const std::string & title, const EmlVersion & emlVersion);

	public:  
		virtual ~AbstractHdfProxy() {}

		/**
		* Open the file for reading and writing.
		* The read/write access are determined by the EPC document configuration.
		*/
		virtual void open() = 0;

		/**
		 * Check if the Hdf file is open or not
		 */
		virtual bool isOpened() const = 0;

		/**
		 * Close the file
		 */
		virtual void close() = 0;

		/**
		 * Get the used (native) datatype in a dataset
		* To compare with H5T_NATIVE_INT, H5T_NATIVE_UINT, H5T_NATIVE_FLOAT, etc...
		 */
		virtual int getHdfDatatypeInDataset(const std::string & datasetName) const = 0;

		/**
		* Get the used datatype class in a dataset
		* To compare with H5T_INTEGER, H5T_FLOAT , H5T_STRING , etc...
		*/
		virtual int getHdfDatatypeClassInDataset(const std::string & datasetName) const = 0;

		/**
		* Write an itemized list of list into the HDF file by means of a single group containing 2 datasets.
		* @param groupName					The name of the group where to create the itemized list of list.
		*									This name must not contain '/' character and must be directly contained in RESQML group.
		* @param name						The name of the itemized list of list hdf group.
		* @param cumulativeLengthDatatype	The datatype of the cumulative length to write.
		* @param cumulativeLength			1d array of positive integers containing for each list the sum of all the previous list lengths including the current one
		* @param cumulativeLengthSize		Size of the cumulativeLength array.
		* @param elementsDatatype			The datatype of the elements to write.
		* @param elements					1d array of elements containing the aggregation of individual list content.
		* @param elementsSize				Size of the elements array.
		*/
		virtual void writeItemizedListOfList(const std::string & groupName,
			const std::string & name,
			const int & cumulativeLengthDatatype,
			void * cumulativeLength,
			const unsigned long long & cumulativeLengthSize,
			const int & elementsDatatype,
			void * elements,
			const unsigned long long & elementsSize) = 0;

		/**
		 * Get the number of dimensions in an HDF dataset of the proxy.
		 * @param datasetName	The absolute name of the dataset we want to get the number of dimensions.
		 */
		virtual unsigned int getDimensionCount(const std::string & datasetName) = 0;

		/**
		 * Get the number of elements in an HDF dataset of the proxy. The number of elements is get from all dimensions.
		 * @param datasetName	The absolute name of the dataset we want to get the number of elements.
		 */
		virtual signed long long getElementCount(const std::string & datasetName) = 0;

		/**
		 * Set the new compression level which will be used for all data to be written
		 * @param compressionLevel				Lower compression levels are faster but result in less compression. Range [0..9] is allowed.
		 */
		virtual void setCompressionLevel(const unsigned int & newCompressionLevel) = 0;

		virtual void writeArrayNdOfFloatValues(const std::string & groupName,
		  const std::string & name,
		  float * floatValues,
		  unsigned long long * numValuesInEachDimension,
		  const unsigned int & numDimensions) = 0;

		/**
		 * Write an array (potentially with multi dimensions) of double values into the HDF file by means of a single dataset.
		 * @param groupName						The name of the group where to create the array of double values.
		 *										This name must not contain '/' character and must be directly contained in RESQML group.
		 * @param name							The name of the array of double values hdf dataset. It must not already exist.
		 * @param dblValues						1d array of double values ordered firstly by fastest direction.
		 * @param numValuesInEachDimension		Number of values in each dimension of the array to write. They are ordered from fastest index to slowest index.
		 * @param numDimensions					The number of the dimensions of the array to write
		 */
		virtual void writeArrayNdOfDoubleValues(const std::string & groupName,
		  const std::string & name,
		  double * dblValues,
		  unsigned long long * numValuesInEachDimension,
		  const unsigned int & numDimensions) = 0;

		/**
		* Write an array (potentially with multi dimensions) of char values into the HDF file by means of a single dataset.
		* @param groupName						The name of the group where to create the array of int values.
		*										This name must not contain '/' character and must be directly contained in RESQML group.
		* @param name							The name of the array of int values hdf dataset. It must not already exist.
		* @param intValues						1d array of char values ordered firstly by fastest direction.
		* @param numValuesInEachDimension		Number of values in each dimension of the array to write. They are ordered from fastest index to slowest index.
		* @param numDimensions					The number of the dimensions of the array to write
		*/
		virtual void writeArrayNdOfCharValues(const std::string & groupName,
			const std::string & name,
			char * intValues,
			unsigned long long * numValuesInEachDimension,
			const unsigned int & numDimensions) = 0;

		/**
		 * Write an array (potentially with multi dimensions) of int values into the HDF file by means of a single dataset.
		 * @param groupName						The name of the group where to create the array of int values.
		 *										This name must not contain '/' character and must be directly contained in RESQML group.
		 * @param name							The name of the array of int values hdf dataset. It must not already exist.
		 * @param intValues						1d array of int values ordered firstly by fastest direction.
		 * @param numValuesInEachDimension		Number of values in each dimension of the array to write. They are ordered from fastest index to slowest index.
		 * @param numDimensions					The number of the dimensions of the array to write
		 */
		virtual void writeArrayNdOfIntValues(const std::string & groupName,
		  const std::string & name,
		  int * intValues,
		  unsigned long long * numValuesInEachDimension,
		  const unsigned int & numDimensions) = 0;

		/**
		* Write an array (potentially with multi dimensions) of gSoap unsigned long 64 values into the HDF file by means of a single dataset.
		* @param groupName						The name of the group where to create the array of int values.
		*										This name must not contain '/' character and must be directly contained in RESQML group.
		* @param name							The name of the array of gSoap unsigned long 64 values hdf dataset. It must not already exist.
		* @param ulong64Values					1d array of gSoap unsigned long 64 values ordered firstly by fastest direction.
		* @param numValuesInEachDimension		Number of values in each dimension of the array to write. They are ordered from fastest index to slowest index.
		* @param numDimensions					The number of the dimensions of the array to write
		*/
 		virtual void writeArrayNdOfGSoapULong64Values(const std::string & groupName,
			const std::string & name,
			ULONG64 * ulong64Values,
			unsigned long long * numValuesInEachDimension,
			const unsigned int & numDimensions) = 0;

		/**
		 * Write an array (potentially with multi dimensions) of a specific datatype into the HDF file by means of a single dataset.
		 * @param groupName						The name of the group where to create the array of values.
		 *										This name must not contain '/' character and must be directly contained in RESQML group.
		 * @param name							The name of the array (potentially with multi dimensions) of a specific datatype hdf dataset. It must not already exist.
		 * @param datatype						The specific datatype of the valeus to write.
		 * @param values							1d array of specific datatype ordered firstly by fastest direction.
		 * @param numValuesInEachDimension		Number of values in each dimension of the array to write. They are ordered from fastest index to slowest index.
		 * @param numDimensions					The number of the dimensions of the array to write
		 */
		virtual void writeArrayNd(const std::string & groupName,
		  const std::string & name,
		  const int & datatype,
		  void * values,
		  unsigned long long * numValuesInEachDimension,
		  const unsigned int & numDimensions) = 0;

		/**
		 * Create an array (potentially with multi dimensions) of a specific datatype into the HDF file. Values are not yet written to this array.
		 * @param groupName                      The name of the group where to create the array of double values.
		 *                                       This name must not contain '/' character and must be directly contained in RESQML group.
		 * @param name                           The name of the array (potentially with multi dimensions) of a specific datatype hdf dataset. It must not exist.
		 * @param datatype                       The specific datatype of the values to write.
		 * @param numValuesInEachDimension       Number of values in each dimension of the array to write. They are ordered from fastest index to slowest index.
		 * @param numDimensions                  The number of the dimensions of the array to write.
		 */
		virtual void createArrayNd(
		  const std::string& groupName,
		  const std::string& name,
		  const int & datatype,
		  unsigned long long* numValuesInEachDimension,
		  const unsigned int& numDimensions
		  ) = 0;

		/**
		 * Find the array associated with @p groupName and @p name and write to it.
		 * @param groupName                      The name of the group associated with the array.
		 * @param name                           The name of the array (potentially with multi dimensions).
		 * @param values                         1d array of specific datatype ordered firstly by fastest direction.
		 * @param numValuesInEachDimension       Number of values in each dimension of the array to write. They are ordered from fastest index to slowest index.
		 * @param offsetValuesInEachDimension    Offset values in each dimension of the array to write. They are ordered from fastest index to slowest index.
		 * @param numDimensions                  The number of the dimensions of the array to write.
		 */
		virtual void writeArrayNdSlab(
		  const std::string& groupName,
		  const std::string& name,
		  const int & datatype,
		  void* values,
		  unsigned long long* numValuesInEachDimension,
		  unsigned long long* offsetValuesInEachDimension,
		  const unsigned int& numDimensions
		  ) = 0;

		/**
		* Write some string attributes into a group
		*/
		virtual void writeGroupAttributes(const std::string & groupName,
			const std::vector<std::string> & attributeNames,
			const std::vector<std::string> & values) = 0;

		/**
		* Write a single attribute which contain an array of strings
		*/
		virtual void writeGroupAttribute(const std::string & groupName,
			const std::string & attributeName,
			const std::vector<std::string> & values) = 0;

		/**
		* Write some double attributes into a group
		*/
		virtual void writeGroupAttributes(const std::string & groupName,
			const std::vector<std::string> & attributeNames,
			const std::vector<double> & values) = 0;

		/**
		* Write some int attributes into a group
		*/
		virtual void writeGroupAttributes(const std::string & groupName,
			const std::vector<std::string> & attributeNames,
			const std::vector<int> & values) = 0;

		/**
		* Write some string attributes into a dataset
		*/
		virtual void writeDatasetAttributes(const std::string & datasetName,
			const std::vector<std::string> & attributeNames,
			const std::vector<std::string> & values) = 0;

		/**
		* Write a single attribute which contain an array of strings
		*/
		virtual void writeDatasetAttribute(const std::string & datasetName,
			const std::string & attributeName,
			const std::vector<std::string> & values) = 0;

		/**
		* Write some double attributes into a dataset
		*/
		virtual void writeDatasetAttributes(const std::string & datasetName,
			const std::vector<std::string> & attributeNames,
			const std::vector<double> & values) = 0;

		/**
		* Write some int attributes into a dataset
		*/
		virtual void writeDatasetAttributes(const std::string & datasetName,
			const std::vector<std::string> & attributeNames,
			const std::vector<int> & values) = 0;

		/**
		* Read a string which is stored as an HDF attribute in a file, group or dataset
		* @param obj_name use '.' if the attribute to read is on the file otherwise the full path
		*/
		virtual std::string readStringAttribute(const std::string & obj_name,
			const std::string & attr_name) const = 0;

		virtual std::vector<std::string> readStringArrayAttribute(const std::string & obj_name,
			const std::string & attr_name) const = 0;

		/**
		* Read a double which is stored as an HDF attribute in a file, group or dataset
		* @param obj_name use '.' if the attribute to read is on the file otherwise the full path
		*/
		virtual double readDoubleAttribute(const std::string & obj_name,
			const std::string & attr_name) const = 0;

		/**
		* Read a long which is stored as an HDF attribute in a file, group or dataset
		* @param obj_name use '.' if the attribute to read is on the file otherwise the full path
		*/
		virtual LONG64 readLongAttribute(const std::string & obj_name,
			const std::string & attr_name) const = 0;

		/**
		 * Read an array Nd of double values stored in a specific dataset
		 * @param datasetName	The absolute dataset name where to read the values
		 * @param values 		The values must be pre-allocated.
		 */
		virtual void readArrayNdOfDoubleValues(const std::string & datasetName, double* values) = 0;

		/**
		 * Find the array associated with @p datasetName and read from it.
		 * @param datasetName                    The name of the array (potentially with multi dimensions).
		 * @param values                         1d array output of double values ordered firstly by fastest direction.
		 * @param numValuesInEachDimension       Number of values in each dimension of the array to read. They are ordered from fastest index to slowest index.
		 * @param offsetValuesInEachDimension    Offset values in each dimension of the array to read. They are ordered from fastest index to slowest index.
		 * @param numDimensions                  The number of the dimensions of the array to read.
		 */
		virtual void readArrayNdOfDoubleValues(
		  const std::string & datasetName,
		  double* values,
		  unsigned long long * numValuesInEachDimension,
		  unsigned long long * offsetInEachDimension,
		  const unsigned int & numDimensions
		  ) = 0;

		/**
		 * Read an array Nd of float values stored in a specific dataset.
		 * @param datasetName	The absolute dataset name where to read the values
		 * @param values 		The values must be pre-allocated.
		 */
		virtual void readArrayNdOfFloatValues(const std::string & datasetName, float* values) = 0;

		/**
		 * Find the array associated with @p datasetName and read from it.
		 * @param datasetName                    The name of the array (potentially with multi dimensions).
		 * @param values                         1d array output of float values ordered firstly by fastest direction.
		 * @param numValuesInEachDimension       Number of values in each dimension of the array to read. They are ordered from fastest index to slowest index.
		 * @param offsetValuesInEachDimension    Offset values in each dimension of the array to read. They are ordered from fastest index to slowest index.
		 * @param numDimensions                  The number of the dimensions of the array to read.
		 */
		virtual void readArrayNdOfFloatValues(
		  const std::string & datasetName,
		  float* values,
		  unsigned long long * numValuesInEachDimension,
		  unsigned long long * offsetInEachDimension,
		  const unsigned int & numDimensions
		  ) = 0;

		/**
		* TODO : check all possible size of LONG64 on all different platforms
		*/
		virtual void readArrayNdOfGSoapLong64Values(const std::string & datasetName, LONG64* values) = 0;
	
		/**
		* TODO : check all possible size of ULONG64 on all different platforms
		*/
		virtual void readArrayNdOfGSoapULong64Values(const std::string & datasetName, ULONG64* values) = 0;

		/**
		 * Read an array Nd of long values stored in a specific dataset.
		 * @param datasetName	The absolute dataset name where to read the values
		 * @param values 		The values must be pre-allocated.
		 */
		virtual void readArrayNdOfLongValues(const std::string & datasetName, long* values) = 0;

		/**
		 * Find the array associated with datasetName and read from it.
		 * @param datasetName                    The name of the array (potentially with multi dimensions).
		 * @param values                         1d array output of long values ordered firstly by fastest direction.
		 * @param numValuesInEachDimension       Number of values in each dimension of the array to read. They are ordered from fastest index to slowest index.
		 * @param offsetValuesInEachDimension    Offset values in each dimension of the array to read. They are ordered from fastest index to slowest index.
		 * @param numDimensions                  The number of the dimensions of the array to read.
		 */
		virtual void readArrayNdOfLongValues(
		  const std::string & datasetName,
		  long* values,
		  unsigned long long * numValuesInEachDimension,
		  unsigned long long * offsetInEachDimension,
		  const unsigned int & numDimensions
		  ) = 0;

		/**
		 * Read an array Nd of unsigned long values stored in a specific dataset.
		 * @param datasetName	The absolute dataset name where to read the values
		 * @param values 		The values must be pre-allocated.
		 */
		virtual void readArrayNdOfULongValues(const std::string & datasetName, unsigned long* values) = 0;

		/**
		 * Read an array Nd of int values stored in a specific dataset.
		 * @param datasetName	The absolute dataset name where to read the values
		 * @param values 		The values must be pre-allocated.
		 */
		virtual void readArrayNdOfIntValues(const std::string & datasetName, int* values) = 0;

		/**
		* Find the array associated with datasetName and read from it.
		* @param datasetName                    The name of the array (potentially with multi dimensions).
		* @param values                         1d array output of int values ordered firstly by fastest direction.
		* @param numValuesInEachDimension       Number of values in each dimension of the array to read. They are ordered from fastest index to slowest index.
		* @param offsetValuesInEachDimension    Offset values in each dimension of the array to read. They are ordered from fastest index to slowest index.
		* @param numDimensions                  The number of the dimensions of the array to read.
		*/
		virtual void readArrayNdOfIntValues(
			const std::string & datasetName,
			int* values,
			unsigned long long * numValuesInEachDimension,
			unsigned long long * offsetInEachDimension,
			const unsigned int & numDimensions
		) = 0;

		/**
		 * Read an array Nd of unsigned int values stored in a specific dataset
		 * Don"t forget to delete the allocated pointer when no more necessary.
		 * @param datasetName	The absolute dataset name where to read the values
		 */
		virtual void readArrayNdOfUIntValues(const std::string & datasetName, unsigned int* values) = 0;

		/**
		 * Read an array Nd of short values stored in a specific dataset
		 * Don"t forget to delete the allocated pointer when no more necessary.
		 * @param datasetName	The absolute dataset name where to read the values
		 * @param values 		The values must be pre-allocated.
		 */
		virtual void readArrayNdOfShortValues(const std::string & datasetName, short* values) = 0;

		/**
		 * Read an array Nd of unsigned short values stored in a specific dataset.
		 * @param datasetName	The absolute dataset name where to read the values
		 * @param values 		The values must be pre-allocated.
		 */
		virtual void readArrayNdOfUShortValues(const std::string & datasetName, unsigned short* values) = 0;

		/**
		 * Read an array Nd of char values stored in a specific dataset.
		 * @param datasetName	The absolute dataset name where to read the values
		 * @param values 		The values must be pre-allocated.
		 */
		virtual void readArrayNdOfCharValues(const std::string & datasetName, char* values) = 0;

		/**
		 * Read an array Nd of unsigned char values stored in a specific dataset.
		 * @param datasetName	The absolute dataset name where to read the values
		 */
		virtual void readArrayNdOfUCharValues(const std::string & datasetName, unsigned char* values) = 0;

		/**
		 * Read the dimensions of an array stored in a specific dataset
		 * @param datasetName	The absolute dataset name where to read the array dimensions
		 */
		virtual std::vector<unsigned long long> readArrayDimensions(const std::string & datasetName) = 0;

		/**
		* Check wether an absolute path exists in the hdf file or not.
		*/
		virtual bool exist(const std::string & absolutePathInHdfFile) const = 0;
  
		friend void resqml2::AbstractRepresentation::setHdfProxy(common::AbstractHdfProxy * proxy);
		friend void resqml2::AbstractProperty::setHdfProxy(common::AbstractHdfProxy * proxy);
		friend void prodml2_0::DasAcquisition::setHdfProxy(common::AbstractHdfProxy * proxy);

	};
}
