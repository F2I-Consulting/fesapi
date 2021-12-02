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

#include "../eml2/TimeSeries.h"

namespace EML2_3_NS
{
	/** A time series. */
	class TimeSeries final : public EML2_NS::TimeSeries
	{
	public:

		/**
		 * Only to be used in partial transfer context
		 *
		 * @param [in,out]	partialObject	If non-null, the partial object.
		 *
		 * 
		 */
		DLL_IMPORT_OR_EXPORT TimeSeries(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject):
			EML2_NS::TimeSeries(partialObject) {}

		/**
		 * Creates a time series
		 *
		 * @param [in,out]	repo 	the repo where this intance will be stored.
		 * @param 		  	guid 	The guid to set to the local 3d crs. If empty then a new guid will be
		 * 							generated.
		 * @param 		  	title	The title of the instance.
		 */
		TimeSeries(COMMON_NS::DataObjectRepository* repo, const std::string & guid, const std::string & title);

		/**
		 * Creates an instance of this class by wrapping a gsoap instance.
		 *
		 * @param [in,out]	fromGsoap	If non-null, from gsoap.
		 */
		TimeSeries(gsoap_eml2_3::_eml23__TimeSeries* fromGsoap) : EML2_NS::TimeSeries(fromGsoap) {}

		/** Destructor does nothing since the memory is managed by the gsoap context. */
		~TimeSeries() = default;

		/**
		 * Pushes back an timestamp into this time series.
		 *
		 * @exception	std::logic_error	If the underlying gSOAP instance is not a RESQML2.0 one.
		 *
		 * @param 	timestamp	The timestamp to push back.
		 * @param 	yearOffset	Indicates that the dateTime attribute must be translated according to this value.
		 */
		DLL_IMPORT_OR_EXPORT void pushBackTimestamp(const tm & timestamp, LONG64 yearOffset = 0) final;

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
		DLL_IMPORT_OR_EXPORT uint64_t getTimestampIndex(time_t timestamp, LONG64 yearOffset = 0) const final;

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
		DLL_IMPORT_OR_EXPORT uint64_t getTimestampIndex(const tm & timestamp, LONG64 yearOffset = 0) const final;

		/**
		 * Get the count of timestamps in this time series.
		 *
		 * @exception	std::logic_error	If the underlying gSOAP instance is not a RESQML2.0 one.
		 *
		 * @returns	The timestamp count.
		 */
		DLL_IMPORT_OR_EXPORT uint64_t getTimestampCount() const final;

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
		DLL_IMPORT_OR_EXPORT tm getTimestampAsTimeStructure(uint64_t index) const final;

		/**
		* The standard XML namespace for serializing this data object.
		*/
		DLL_IMPORT_OR_EXPORT static constexpr char const* XML_NS = "eml23";

		/**
		* Get the standard XML namespace for serializing this data object.
		*/
		DLL_IMPORT_OR_EXPORT std::string getXmlNamespace() const final { return XML_NS; }
	};
}
