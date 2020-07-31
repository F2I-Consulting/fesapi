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

#include "../common/AbstractObject.h"

namespace PRODML2_1_NS
{
	/** The time series data object is intended for use in transferring time series of data, e.g. from a historian. 
	 * The Time Series data object describes a context free, time based series of measurement data for the 
	 * purpose of targeted exchanges between consumers and providers of data services. This is intended for 
	 * use in support of smart fields or high-frequency historian type interactions, not reporting. It provides a 
	 * “flat” view of the data and uses a set of keyword-value pairs to define the business identity of the series, 
	 * as described in the following generalized hierarchy.
	 */
	class TimeSeriesData : public COMMON_NS::AbstractObject
	{
	public:

		/**
		 * Only to be used in partial transfer context
		 *
		 * @param [in,out]	partialObject	If non-null, the partial object.
		 *
		 * 
		 */
		DLL_IMPORT_OR_EXPORT TimeSeriesData(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : COMMON_NS::AbstractObject(partialObject) {}

		/**
		 * @brief	Creates an instance of this class in a gsoap context.
		 *
		 * @exception	std::invalid_argument	If <tt>repo == nullptr</tt>.
		 *
		 * @param [in,out]	repo			  	The dataobject repo where the underlying gsoap proxy is
		 * 										going to be created.
		 * @param 		  	guid			  	The guid to set to this instance. If empty then a new
		 * 										guid will be generated.
		 * @param 		  	title			  	The title.
		 */
		TimeSeriesData(COMMON_NS::DataObjectRepository * repo,
			const std::string & guid,
			const std::string & title);

		/**
		 * Creates an instance of this class by wrapping a gsoap instance.
		 *
		 * @param [in,out]	fromGsoap	If non-null, from gsoap.
		 */
		TimeSeriesData(gsoap_eml2_2::prodml21__TimeSeriesData* fromGsoap):AbstractObject(fromGsoap)  {}

		/** Destructor does nothing since the memory is managed by the gsoap context. */
		~TimeSeriesData() = default;

		/**
		* The keyword value pairs are used to characterize the underlying nature of the values. The key value may provide part of the unique identity of an instance of a concept or it may characterize the underlying concept.
		* @param	keyword	One of this enumerated value
		*   - asset identifier :	A formatted URI identifier of the asset (facility) related to the value. This captures the 
		*							kind of asset as well as the unique identifier of the asset within a specified context 
		*							(the authority). The identifier may define a hierarchy of assets.
		*   - qualifier :			A qualifier of the meaning of the value. This is used to distinguish between variations 
		*							of an underlying meaning based on the method of creating the value (e.g., measured 
		*							versus simulated). The values associated with this keyword must be from the list 
		*							defined by type FlowQualifier. 
		*	- subqualifier :		A specialization of a qualifier. The values associated with this keyword must be from 
		*							the list defined by type FlowSubQualifier. 
		*	- product :				The type of product that is represented by the value. This is generally used with 
		*							things like volume or flow rate. It is generally meaningless for things like temperature 
		*							or pressure. The values associated with this keyword must be from the list defined by 
		*							type ReportingProduct. 
		*	- flow :				Defines the part of the flow network where the asset is located. This is most useful in 
		*							situations (e.g., reporting) where detailed knowledge of the network configuration is 
		*							not needed. Basically, this classifies different segments of the flow network based on 
		*							its purpose within the context of the whole network. The values associated with this 
		*							keyword must be from the list defined by type ReportingFlow.
		* @param	value	The string value associated to the keyword
		*/
		DLL_IMPORT_OR_EXPORT void pushBackKeywordValue(gsoap_eml2_2::prodml21__TimeSeriesKeyword keyword, const std::string & value);

		/**
		* Set the uom of the data of the time series.
		*
		* @param uom	The unit of measure taken from the standard Energistics
		 * 				units of measure catalog. Please check
		 * 				COMMON_NS::EnumStringMapper::getEnergisticsUnitOfMeasure in order
		 * 				to minimize the use of non standard unit of measure.
		*/
		DLL_IMPORT_OR_EXPORT void setUom(gsoap_resqml2_0_1::resqml20__ResqmlUom uom);

		/**
		* Set the measure class of the data of the time series.
		*
		* @param measureClass	The measure class to set.
		*/
		DLL_IMPORT_OR_EXPORT void setMeasureClass(gsoap_eml2_2::eml22__MeasureClass measureClass);

		/**
		* Push back a new value (i.e data) in the time series
		*
		* @param value	The value to push back.
		* @param value	(Optional) The time of the value to push back.
		*/
		DLL_IMPORT_OR_EXPORT void pushBackDoubleValue(double value, time_t timestamp = -1);

		/**
		* Push back a new value (i.e data) in the time series
		*
		* @param value	The value to push back.
		* @param value	The time of the value to push back.
		* @param value	The status of the value to push back.
		*/
		DLL_IMPORT_OR_EXPORT void pushBackDoubleValue(double value, time_t timestamp, gsoap_eml2_2::prodml21__ValueStatus status);

		/**
		* Push back a new value (i.e data) in the time series
		*
		* @param value	The value to push back.
		* @param value	(Optional) The time of the value to push back.
		*/
		DLL_IMPORT_OR_EXPORT void pushBackStringValue(const std::string & value, time_t timestamp = -1);

		/**
		 * Gets the unit of measure of the values of this time series as a string.
		 *
		 * @returns	The unit of measure of the values of this time series as a string. Returns empty string if no uom is stored.
		 */
		DLL_IMPORT_OR_EXPORT std::string getUomAsString() const;

		/**
		 * Gets the measure class of the values of this time series as a string.
		 *
		 * @returns	The measure class of the values of this time series as a string. Returns empty string if no measure class is stored.
		 */
		DLL_IMPORT_OR_EXPORT std::string getMeasureClassAsString() const;

		/**
		* Get the count of value in this time series
		*/
		DLL_IMPORT_OR_EXPORT unsigned int getValueCount() const;

		/**
		* Check if a value at a particular index is a double one.
		*
		* @param index	The index of the value in this timeseries
		* @return true if the value at this index is a double one
		*/
		DLL_IMPORT_OR_EXPORT bool isDoubleValue(unsigned int index) const;

		/**
		* Check if a value at a particular index is a string one.
		*
		* @param index	The index of the value in this timeseries
		* @return true if the value at this index is a string one
		*/
		DLL_IMPORT_OR_EXPORT bool isStringValue(unsigned int index) const;

		/**
		* Get a double value at a particular index.
		*
		* @param index	The index of the value in this timeseries
		* @return the double value at a particular index
		*/
		DLL_IMPORT_OR_EXPORT double getDoubleValue(unsigned int index) const;

		/**
		* Get a string value at a particular index.
		*
		* @param index	The index of the value in this timeseries
		* @return the string value at a particular index
		*/
		DLL_IMPORT_OR_EXPORT std::string getStringValue(unsigned int index) const;

		/**
		* Get the timestamp associated to a value at a particular index.
		*
		* @param index	The index of the value in this timeseries
		* @return the timestamp associated to a value at a particular index. -1 if no timesteamp is provided for this value.
		*/
		DLL_IMPORT_OR_EXPORT time_t getValueTimestamp(unsigned int index) const;

		/**
		* Check if a value at a particular index has a status.
		*
		* @param index	The index of the value in this timeseries
		* @return true if the value at this index has a status
		*/
		DLL_IMPORT_OR_EXPORT bool hasValueStatus(unsigned int index) const;

		/**
		* Get the status associated to a value at a particular index.
		*
		* @param index	The index of the value in this timeseries
		* @return the status associated to a value at a particular index.
		*/
		DLL_IMPORT_OR_EXPORT gsoap_eml2_2::prodml21__ValueStatus getValueStatus(unsigned int index) const;

		/**
		* Get the count of keywords in this time series
		*/
		DLL_IMPORT_OR_EXPORT unsigned int getKeywordCount() const;

		/**
		* Get a keyword at a particular index.
		*
		* @param index	The index of the keyword in this timeseries
		* @return the keyword at a particular index
		*/
		DLL_IMPORT_OR_EXPORT gsoap_eml2_2::prodml21__TimeSeriesKeyword getKeyword(unsigned int index) const;

		/**
		* Get the value of a keyword at a particular index.
		*
		* @param index	The index of the value in this timeseries
		* @return the value of a keyword at a particular index.
		*/
		DLL_IMPORT_OR_EXPORT std::string getKeywordValue(unsigned int index) const;

		/**
		 * The standard XML tag without XML namespace for serializing this data object.
		 *
		 * @returns	The XML tag.
		 */
		DLL_IMPORT_OR_EXPORT static const char* XML_TAG;

		/**
		 * Get the standard XML tag without XML namespace for serializing this data object.
		 *
		 * @returns	The XML tag.
		 */
		DLL_IMPORT_OR_EXPORT virtual std::string getXmlTag() const { return XML_TAG; }

		/**
		* The standard XML namespace for serializing this data object.
		*/
		DLL_IMPORT_OR_EXPORT static const char* XML_NS;

		/**
		* Get the standard XML namespace for serializing this data object.
		*/
		DLL_IMPORT_OR_EXPORT std::string getXmlNamespace() const final { return XML_NS; }

		/** Loads target relationships */
		void loadTargetRelationships() {}
	};
}
