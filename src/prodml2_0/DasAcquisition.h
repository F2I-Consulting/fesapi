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
#pragma once

#include "prodml2_0/AbstractObject.h"
#include "resqml2/AbstractValuesProperty.h"

namespace COMMON_NS {
	class HdfProxy;
}

namespace PRODML2_0_NS
{
	class DLL_IMPORT_OR_EXPORT DasAcquisition : public PRODML2_0_NS::AbstractObject
	{
	private:
		/**
		* Mainly useful in the "only HDF5" scenario
		*/
		gsoap_eml2_1::prodml2__DasRaw* pushBackRawXmlOnly(const std::string & uuid, const std::string & rawDataUnit, const ULONG64 & startLocusIndex, const ULONG64 & numberOfLoci, const std::string & rawDescription,
			const std::string & startTime, const std::string endTime, const ULONG64 & timeCount,
			gsoap_eml2_1::prodml2__DasDimensions slowestHdfDimension, gsoap_eml2_1::prodml2__DasDimensions fastestHdfDimension,
			bool datatypeIsInteger,
			COMMON_NS::AbstractHdfProxy* proxy);

	public:
		/**
		* Default constructor
		*/
		DasAcquisition() {}

		/**
		* Creates an instance of this class in a gsoap context.
		* @param soap		A gsoap context wihch will manage the memory and the serialization/deserialization of this instance.
		* @param guid		The guid to set to this instance. If empty then a new guid will be generated.
		* @param title		A title for the instance to create.
		*/
		DasAcquisition(class FiberOpticalPath* fiberOpticalPath, class DasInstrumentBox* dasInstrumentBox,
			const std::string & guid, const std::string & title,
			const std::string & jobUuid, const std::string & facilityId, const std::string & vendorName,
			const double & pulseRate, const gsoap_eml2_1::eml21__FrequencyUom & pulseRateUom,
			const double & pulseWidth, const gsoap_eml2_1::eml21__TimeUom & pulseWidthUom,
			const double & gaugeLength, const gsoap_eml2_1::eml21__LengthUom & gaugeLengthUom,
			const double & spatialSamplingInterval, const gsoap_eml2_1::eml21__LengthUom & spatialSamplingIntervalUom,
			const double & minimumFrequency, const gsoap_eml2_1::eml21__FrequencyUom & minimumFrequencyUom,
			const double & maximumFrequency, const gsoap_eml2_1::eml21__FrequencyUom & maximumFrequencyUom,
			const ULONG64 & lociCount, const ULONG64 & startLocusIndex,
			const std::string & measurementStartIsoTime, bool triggeredMeasurement);

		/**
		* Creates an instance of this class by parsing an HDF5 file.
		*/
		DasAcquisition(class FiberOpticalPath* fiberOpticalPath, class DasInstrumentBox* dasInstrumentBox,
			PRODML2_0_NS::HdfProxy * proxy);

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		DasAcquisition(gsoap_eml2_1::_prodml2__DasAcquisition* fromGsoap) : AbstractObject(fromGsoap) {}

		/**
		* Destructor does nothing since the memory is managed by the gsoap context.
		*/
		~DasAcquisition() {}
		
		static const char* XML_TAG;
		virtual std::string getXmlTag() const {return XML_TAG;}

		void setHdfProxy(COMMON_NS::AbstractHdfProxy * proxy);

		gsoap_eml2_1::eml21__DataObjectReference* getFiberOpticalPathDor() const;
		class FiberOpticalPath* getFiberOpticalPath() const;

		void setFiberOpticalPath(class FiberOpticalPath* fiberOpticalPath);

		gsoap_eml2_1::eml21__DataObjectReference* getDasInstrumentBoxDor() const;
		class DasInstrumentBox* getDasInstrumentBox() const;

		void setDasInstrumentBox(class DasInstrumentBox* dasInstrumentBox);

		std::string getJobUuid() const;
		std::string getFacilityUuid() const; // only the first one for now
		std::string getVendorName() const;

		double getPulseRate() const;
		gsoap_eml2_1::eml21__FrequencyUom getPulseRateUom() const;

		double getPulseWidth() const;
		gsoap_eml2_1::eml21__TimeUom getPulseWidthUom() const;

		double getGaugeLength() const;
		gsoap_eml2_1::eml21__LengthUom getGaugeLengthUom() const;

		double getSpatialSamplingInterval() const;
		gsoap_eml2_1::eml21__LengthUom getSpatialSamplingIntervalUom() const;

		double getMinimumFrequency() const;
		gsoap_eml2_1::eml21__FrequencyUom getMinimumFrequencyUom() const;

		double getMaximumFrequency() const;
		gsoap_eml2_1::eml21__FrequencyUom getMaximumFrequencyUom() const;

		ULONG64 getLociCount() const;
		LONG64 getStartLocusIndex() const;

		std::string getMeasurementStartIsoTime() const;

		bool isTriggeredMeasurement() const;

		/**
		* Push back a raw das acquisition
		* Initiate the hdf dataset but do not write data in it.
		* @param guid				The guid for this raw acquisition
		* @param datatypeIsInteger	True if the raw data to be written are integers. Fale if they are floating point values.
		* @param datatypeByteCount	Count of bytes necessary to represent one single raw data. For example : 2 means short if datatypeIsInteger == true. 4 means float if datatypeIsInteger == false. etc...
		* @param rawDataUnit		Data unit for the DAS measurement instrument. 
		* @param timeArray			Unix timestamps in micro seconds
		* @param timeCount			The count of time in time array
		* @param proxy				The hdf proxy where the data will be stored.
		*/
		void pushBackRaw(const std::string & guid, bool datatypeIsInteger, const char & datatypeByteCount, const std::string & rawDataUnit, LONG64* timeArray, const ULONG64 & timeCount, COMMON_NS::AbstractHdfProxy* proxy);

		/**
		* @param data			The measured data. A linearized array of a 2d one where loci go fastest and time slowest.
		*/
		void writeIntoDataset(float * data,
			unsigned long numSampleForAllLoci,
			unsigned long timeStepIndex);
		void writeIntoDataset(double * data,
			unsigned long numSampleForAllLoci,
			unsigned long timeStepIndex);
		void writeIntoDataset(LONG64 * data,
			unsigned long numSampleForAllLoci,
			unsigned long timeStepIndex);
		void writeIntoDataset(int * data,
			unsigned long numSampleForAllLoci,
			unsigned long timeStepIndex);
		void writeIntoDataset(short * data,
			unsigned long numSampleForAllLoci,
			unsigned long timeStepIndex);
		void writeIntoDataset(char * data,
			unsigned long numSampleForAllLoci,
			unsigned long timeStepIndex);

		/**
		* Get the count of raw in this data instance
		*/
		unsigned int getRawCount() const;

		/**
		* Get the slowest (generally called first) dimension desription of the raw.
		* @param rawIndex	The index of the raw we want the values from.
		*/
		gsoap_eml2_1::prodml2__DasDimensions getRawDataSlowestDimension(const unsigned int & rawIndex) const;

		/**
		* Get the fastest (generally called second) dimension desription of the raw.
		* @param rawIndex	The index of the raw we want the values from.
		*/
		gsoap_eml2_1::prodml2__DasDimensions getRawDataFastestDimension(const unsigned int & rawIndex) const;

		std::string getRawDataUnit(const unsigned int & rawIndex) const;
		LONG64 getStartLocusIndex(const unsigned int & rawIndex) const;
		ULONG64 getNumberOfLoci(const unsigned int & rawIndex) const;
		ULONG64 getRawDataTimeCount(const unsigned int & rawIndex) const;

		/**
		* Get the values datatype in the HDF dataset
		*/
		RESQML2_NS::AbstractValuesProperty::hdfDatatypeEnum getRawDataHdfDatatype(const unsigned int & rawIndex) const;

		/**
		* Get all the values of a particular raw of the instance which are supposed to be double ones.
		* @param rawIndex	The index of the raw we want the values from.
		* @param values		The array (pointer) of values must be preallocated regarding getRawDataSlowestDimension and getRawDataFastestDimension and their respective count.
		*/
		void getRawDataAsDoubleValues(const unsigned int & rawIndex, double * values);

		/**
		* Get all the values of a particular raw of the instance which are supposed to be float ones.
		* @param rawIndex	The index of the raw we want the values from.
		* @param values		The array (pointer) of values must be preallocated regarding getRawDataSlowestDimension and getRawDataFastestDimension and their respective count.
		*/
		void getRawDataAsFloatValues(const unsigned int & rawIndex, float * values);

		/**
		* Get all the values of a particular raw of the instance which are supposed to be int 64 bits ones.
		* @param rawIndex	The index of the raw we want the values from.
		* @param values		The array (pointer) of values must be preallocated regarding getRawDataSlowestDimension and getRawDataFastestDimension and their respective count.
		*/
		void getRawDataAsLongValues(const unsigned int & rawIndex, LONG64 * values);

		/**
		* Get all the values of a particular raw of the instance which are supposed to be int 32 bits ones.
		* @param rawIndex	The index of the raw we want the values from.
		* @param values		The array (pointer) of values must be preallocated regarding getRawDataSlowestDimension and getRawDataFastestDimension and their respective count.
		*/
		void getRawDataAsIntValues(const unsigned int & rawIndex, int * values);

		/**
		* Get all the values of a particular raw of the instance which are supposed to be int 16 bits ones.
		* @param rawIndex	The index of the raw we want the values from.
		* @param values		The array (pointer) of values must be preallocated regarding getRawDataSlowestDimension and getRawDataFastestDimension and their respective count.
		*/
		void getRawDataAsShortValues(const unsigned int & rawIndex, short * values);

		/**
		* Get all the values of a particular raw of the instance which are supposed to be int 8 bits ones.
		* @param rawIndex	The index of the raw we want the values from.
		* @param values		The array (pointer) of values must be preallocated regarding getRawDataSlowestDimension and getRawDataFastestDimension and their respective count.
		*/
		void getRawDataAsCharValues(const unsigned int & rawIndex, char * values);

		/**
		* Get all the time of a particular raw of the instance.
		* @param rawIndex	The index of the raw we want the values from.
		*/
		void getRawDataTime(const unsigned int & rawIndex, LONG64 * values);

		COMMON_NS::AbstractHdfProxy* getHdfProxy() const;

		std::string getHdfProxyUuid() const;

	private:

		void initHdfAttributes();

		std::vector<epc::Relationship> getAllEpcRelationships() const;
		/**
		* Does nothing since StringTableLookup has not got any forward relationship.
		*/
		void importRelationshipSetFromEpc(COMMON_NS::EpcDocument* epcDoc) {}
	};
}

