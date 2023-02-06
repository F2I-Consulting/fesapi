using System;

using F2iConsulting.Fesapi;
using F2iConsulting.Fesapi.${FESAPI_COMMON_NS};
using F2iConsulting.Fesapi.${FESAPI_EML2_NS};

namespace Example
{
    public class HdfProxyExample : AbstractHdfProxy
    {
        public HdfProxyExample(global::System.IntPtr cPtr, bool cMemoryOwn) : base(cPtr, cMemoryOwn) { }

        public HdfProxyExample(DataObjectRepository repo, string guid, string title, string packageDirAbsolutePath, string externalFilePath, DataObjectRepository.openingMode hdfPermissionAccess):
            base(packageDirAbsolutePath, externalFilePath, hdfPermissionAccess) 
        {
            initGsoapProxy(repo, guid, title, 20);
        }

        public void sayHello()
        {
            Console.WriteLine("Hello, I am a HdfProxyExample instance!");
        }
        
        public override string getXmlNamespace()
        {
            return "eml20";
        }

        public override void open()
        {
            throw new NotImplementedException();
        }

        public override bool isOpened()
        {
            throw new NotImplementedException();
        }

        public override void close()
        {
            throw new NotImplementedException();
        }

        public override numericalDatatypeEnum getNumericalDatatype(string datasetName)
        {
            throw new NotImplementedException();
        }

        public override int getHdfDatatypeClassInDataset(string datasetName)
        {
            throw new NotImplementedException();
        }

        public override void writeItemizedListOfList(string groupName, string name,
			numericalDatatypeEnum cumulativeLengthDatatype, SWIGTYPE_p_void cumulativeLength, ulong cumulativeLengthSize,
			numericalDatatypeEnum elementsDatatype, SWIGTYPE_p_void elements, ulong elementsSize)
        {
            throw new NotImplementedException();
        }

        public override UInt32Vector getElementCountPerDimension(string datasetName)
        {
            throw new NotImplementedException();
        }

        public override void setCompressionLevel(uint newCompressionLevel)
        {
            throw new NotImplementedException();
        }

        public override void writeArrayNd(string groupName, string name, numericalDatatypeEnum datatype, SWIGTYPE_p_void values, SWIGTYPE_p_unsigned_long_long numValuesInEachDimension, uint numDimensions)
        {
            Console.WriteLine("MyHdfProxy::writeArrayNd");
        }

        public override void createArrayNd(string groupName, string name, numericalDatatypeEnum datatype, SWIGTYPE_p_unsigned_long_long numValuesInEachDimension, uint numDimensions)
        {
            throw new NotImplementedException();
        }

        public override void writeArrayNdSlab(string groupName, string name, numericalDatatypeEnum datatype, SWIGTYPE_p_void values, SWIGTYPE_p_unsigned_long_long numValuesInEachDimension, SWIGTYPE_p_unsigned_long_long offsetValuesInEachDimension, uint numDimensions)
        {
            throw new NotImplementedException();
        }

        public override void writeGroupAttributes(string groupName, StringVector attributeNames, StringVector values)
        {
            throw new NotImplementedException();
        }

        public override void writeGroupAttribute(string groupName, string attributeName, StringVector values)
        {
            throw new NotImplementedException();
        }

        public override void writeGroupAttributes(string groupName, StringVector attributeNames, DoubleVector values)
        {
            throw new NotImplementedException();
        }

        public override void writeGroupAttributes(string groupName, StringVector attributeNames, Int32Vector values)
        {
            throw new NotImplementedException();
        }

        public override void writeDatasetAttributes(string datasetName, StringVector attributeNames, StringVector values)
        {
            throw new NotImplementedException();
        }

        public override void writeDatasetAttribute(string datasetName, string attributeName, StringVector values)
        {
            throw new NotImplementedException();
        }

        public override void writeDatasetAttributes(string datasetName, StringVector attributeNames, DoubleVector values)
        {
            throw new NotImplementedException();
        }

        public override void writeDatasetAttributes(string datasetName, StringVector attributeNames, Int32Vector values)
        {
            throw new NotImplementedException();
        }

        public override string readStringAttribute(string obj_name, string attr_name)
        {
            throw new NotImplementedException();
        }

        public override StringVector readStringArrayAttribute(string obj_name, string attr_name)
        {
            throw new NotImplementedException();
        }

        public override double readDoubleAttribute(string obj_name, string attr_name)
        {
            throw new NotImplementedException();
        }

        public override long readLongAttribute(string obj_name, string attr_name)
        {
            throw new NotImplementedException();
        }

        public override void readArrayNdOfDoubleValues(string datasetName, SWIGTYPE_p_double values)
        {
            throw new NotImplementedException();
        }

        public override void readArrayNdOfDoubleValues(string datasetName, SWIGTYPE_p_double values, SWIGTYPE_p_unsigned_long_long numValuesInEachDimension, SWIGTYPE_p_unsigned_long_long offsetInEachDimension, uint numDimensions)
        {
            throw new NotImplementedException();
        }

        public override void readArrayNdOfDoubleValues(string datasetName, SWIGTYPE_p_double values, SWIGTYPE_p_unsigned_long_long blockCountPerDimension, SWIGTYPE_p_unsigned_long_long offsetInEachDimension, SWIGTYPE_p_unsigned_long_long strideInEachDimension, SWIGTYPE_p_unsigned_long_long blockSizeInEachDimension, uint numDimensions)
        {
            throw new NotImplementedException();
        }

        public override void selectArrayNdOfValues(string datasetName, SWIGTYPE_p_unsigned_long_long blockCountPerDimension, SWIGTYPE_p_unsigned_long_long offsetInEachDimension, SWIGTYPE_p_unsigned_long_long strideInEachDimension, SWIGTYPE_p_unsigned_long_long blockSizeInEachDimension, uint numDimensions, bool newSelection, SWIGTYPE_p_hdf5_hid_t dataset, SWIGTYPE_p_hdf5_hid_t filespace)
        {
            throw new NotImplementedException();
        }

        public override void readArrayNdOfDoubleValues(SWIGTYPE_p_hdf5_hid_t dataset, SWIGTYPE_p_hdf5_hid_t filespace, SWIGTYPE_p_void values, ulong slabSize)
        {
            throw new NotImplementedException();
        }

        public override void readArrayNdOfFloatValues(string datasetName, SWIGTYPE_p_float values)
        {
            throw new NotImplementedException();
        }

        public override void readArrayNdOfFloatValues(string datasetName, SWIGTYPE_p_float values, SWIGTYPE_p_unsigned_long_long numValuesInEachDimension, SWIGTYPE_p_unsigned_long_long offsetInEachDimension, uint numDimensions)
        {
            throw new NotImplementedException();
        }

        public override void readArrayNdOfInt64Values(string datasetName, SWIGTYPE_p_long_long values)
        {
            throw new NotImplementedException();
        }

        public override void readArrayNdOfInt64Values(string datasetName, SWIGTYPE_p_long_long values, SWIGTYPE_p_unsigned_long_long numValuesInEachDimension, SWIGTYPE_p_unsigned_long_long offsetInEachDimension, uint numDimensions)
        {
            throw new NotImplementedException();
        }

        public override void readArrayNdOfUInt64Values(string datasetName, SWIGTYPE_p_unsigned_long_long values)
        {
            throw new NotImplementedException();
        }

        public override void readArrayNdOfIntValues(string datasetName, SWIGTYPE_p_int values)
        {
            throw new NotImplementedException();
        }

        public override void readArrayNdOfIntValues(string datasetName, SWIGTYPE_p_int values, SWIGTYPE_p_unsigned_long_long numValuesInEachDimension, SWIGTYPE_p_unsigned_long_long offsetInEachDimension, uint numDimensions)
        {
            throw new NotImplementedException();
        }

        public override void readArrayNdOfUIntValues(string datasetName, SWIGTYPE_p_unsigned_int values)
        {
            throw new NotImplementedException();
        }

        public override void readArrayNdOfShortValues(string datasetName, SWIGTYPE_p_short values)
        {
            throw new NotImplementedException();
        }

        public override void readArrayNdOfUShortValues(string datasetName, SWIGTYPE_p_unsigned_short values)
        {
            throw new NotImplementedException();
        }

        public override void readArrayNdOfCharValues(string datasetName, string values)
        {
            throw new NotImplementedException();
        }

        public override void readArrayNdOfUCharValues(string datasetName, SWIGTYPE_p_unsigned_char values)
        {
            throw new NotImplementedException();
        }

        public override bool exist(string absolutePathInHdfFile)
        {
            throw new NotImplementedException();
        }

        public override bool isCompressed(string datasetName)
        {
            throw new NotImplementedException();
        }

        public override UInt32Vector getElementCountPerChunkDimension(string datasetName)
        {
            throw new NotImplementedException();
        }
    }
}
