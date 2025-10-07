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

namespace RESQML2_NS
{
	class AbstractProperty;
}

namespace EML2_NS
{
	/**
	 * @brief	Proxy class for time series. Stores an ordered list of times, for example, for time-
	 * 			dependent properties, geometries, or representations. It is used in conjunction with
	 * 			the time index to specify times for RESQML.
	 */
	class TimeSeries : public COMMON_NS::AbstractObject
	{
	public:
		
		/** Destructor does nothing since the memory is managed by the gSOAP context. */
		virtual ~TimeSeries() = default;

		/**
		 * Pushes back an timestamp into this time series.
		 *
		 * @exception	std::logic_error	If the underlying gSOAP instance is not a RESQML2.0 one.
		 *
		 * @param 	timestamp	The timestamp to push back.
		 */
		DLL_IMPORT_OR_EXPORT void pushBackTimestamp(time_t timestamp);

		/**
		 * Pushes back an timestamp into this time series.
		 *
		 * @exception	std::logic_error	If the underlying gSOAP instance is not a RESQML2.0 one.
		 *
		 * @param 	timestamp	The timestamp to push back.
		 */
		DLL_IMPORT_OR_EXPORT virtual void pushBackTimestamp(const tm & timestamp) = 0;

		/**
		 * Gets the index of a given timestamp in this time series.
		 *
		 * @exception	std::logic_error 	If the underlying gSOAP instance is not a RESQML2.0 one.
		 * @exception	std::out_of_range	If @p timestamp has not been found in this time series.
		 *
		 * @param 	timestamp	The timestamp we look for.
		 * @param 	yearOffset	Indicates that the dateTime attribute must be translated according to this value.
		 *
		 * @returns	The index of @p timestamp in this time series.
		 */
		DLL_IMPORT_OR_EXPORT virtual uint64_t getTimestampIndex(time_t timestamp, LONG64 yearOffset = 0) const = 0;

		/**
		 * Gets the index of a given timestamp in this time series.
		 *
		 * @exception	std::logic_error 	If the underlying gSOAP instance is not a RESQML2.0 one.
		 * @exception	std::out_of_range	If @p timestamp has not been found in this time series.
		 *
		 * @param 	timestamp	The timestamp we look for.
		 * @param 	yearOffset	Indicates that the dateTime attribute must be translated according to this value.
		 *
		 * @returns	The index of @p timestamp in this time series.
		 */
		DLL_IMPORT_OR_EXPORT virtual uint64_t getTimestampIndex(const tm & timestamp, LONG64 yearOffset = 0) const = 0;

		/**
		 * Get the count of timestamps in this time series.
		 *
		 * @exception	std::logic_error	If the underlying gSOAP instance is not a RESQML2.0 one.
		 *
		 * @returns	The timestamp count.
		 */
		DLL_IMPORT_OR_EXPORT virtual uint64_t getTimestampCount() const = 0;

		/**
		 * Gets a timestamp at a particular index of this time series.
		 *
		 * @exception	std::logic_error 	If the underlying gSOAP instance is not a RESQML2.0 one.
		 * @exception	std::out_of_range	If @p index is out of range.
		 *
		 * @param 	index	Zero-based index of the timestamp we look for.
		 *
		 * @returns	The timestamp at position @p index.
		 */
		DLL_IMPORT_OR_EXPORT time_t getTimestamp(uint64_t index) const;

		/**
		 * Gets a timestamp as an ISO string at a particular index of this time series.
		 *
		 * @exception	std::logic_error 	If the underlying gSOAP instance is not a RESQML2.0 one.
		 * @exception	std::out_of_range	If @p index is out of range.
		 *
		 * @param 	index		Zero-based index of the timestamp we look for.
		 * @param 	withTime	Include or not the time in the output.
		 *
		 * @returns	The timestamp as an ISO string at position @p index.
		 */
		DLL_IMPORT_OR_EXPORT std::string getTimestampAsIsoString(uint64_t index, bool withTime = true) const;

		/**
		 * Gets a timestamp as a time structure at a particular index of this time series. It allows to
		 * read dates from 1900-01-01T00:00:00.
		 *
		 * @exception	std::logic_error 	If the underlying gSOAP instance is not a RESQML2.0 one.
		 * @exception	std::out_of_range	If @p index is out of range.
		 *
		 * @param 	index	Zero-based index of the timestamp we look for.
		 *
		 * @returns	The timestamp at position @p index.
		 */
		DLL_IMPORT_OR_EXPORT virtual tm getTimestampAsTimeStructure(uint64_t index) const = 0;

		/**
		 * Get all the properties which use this time series
		 *
		 * @returns	A vector of pointers to all the properties which use this time series.
		 */
		DLL_IMPORT_OR_EXPORT std::vector<RESQML2_NS::AbstractProperty*> getPropertySet() const;

		/** The standard XML tag without XML namespace for serializing this data object. */
		DLL_IMPORT_OR_EXPORT static constexpr char const* XML_TAG = "TimeSeries";

		DLL_IMPORT_OR_EXPORT virtual std::string getXmlTag() const override { return XML_TAG; }

	protected:

		/** Default constructor does nothing */
		TimeSeries() {}

		/**
		 * Only to be used in partial transfer context
		 *
		 * @param [in,out]	partialObject	If non-null, the partial object.
		 *
		 * 
		 */
		DLL_IMPORT_OR_EXPORT TimeSeries(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : COMMON_NS::AbstractObject(partialObject) {}

		/**
		 * Creates an instance of this class by wrapping a gsoap instance.
		 *
		 * @param [in,out]	fromGsoap	If non-null, from gsoap.
		 */
		TimeSeries(gsoap_resqml2_0_1::_resqml20__TimeSeries* fromGsoap) : COMMON_NS::AbstractObject(fromGsoap) {}

		/**
		 * Creates an instance of this class by wrapping a gsoap instance.
		 *
		 * @param [in,out]	fromGsoap	If non-null, from gsoap.
		 */
		TimeSeries(gsoap_eml2_3::_eml23__TimeSeries* fromGsoap) : COMMON_NS::AbstractObject(fromGsoap) {}

		/** Loads target relationships */
		void loadTargetRelationships() final {};
	};
}
