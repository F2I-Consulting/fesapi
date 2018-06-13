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

#include "resqml2/AbstractProperty.h"

namespace RESQML2_NS
{
	class DLL_IMPORT_OR_EXPORT TimeSeries : public COMMON_NS::AbstractObject
	{
	protected:
		/**
		* Default constructor does nothing
		*/
		TimeSeries() {}

		/**
		* Only to be used in partial transfer context
		*/
		TimeSeries(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : COMMON_NS::AbstractObject(partialObject) {}

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		TimeSeries(gsoap_resqml2_0_1::_resqml2__TimeSeries* fromGsoap) : COMMON_NS::AbstractObject(fromGsoap) {}

	public:
		
		/**
		* Destructor does nothing since the memory is managed by the gsoap context.
		*/
		~TimeSeries() {}

		static const char* XML_TAG;
		virtual std::string getXmlTag() const {return XML_TAG;}

		/**
		* Add a representation values object which uses this property type.
		* Does not add the inverse relationship i.e. from the representation values object to this property type.
		*/
		void pushBackTimestamp(const time_t & timestamp);

		/**
		* Add a representation values object which uses this property type.
		* Does not add the inverse relationship i.e. from the representation values object to this property type.
		*/
		void pushBackTimestamp(const tm & timestamp);

		/**
		* Get the index of a timestamp in the time series.
		* @return	uint.max if this timestamp has not been found in this time series.
		*/
		unsigned int getTimestampIndex(const time_t & timestamp) const;

		/**
		* Get the index of a timestamp in the time series.
		* @return	uint.max if this timestamp has not been found in this time series.
		*/
		unsigned int getTimestampIndex(const tm & timestamp) const;

		/**
		* Get the count of timestamps in this time series.
		*/
		unsigned int getTimestampCount() const;

		/**
		* Get a timestamp at a particular index of this timeseries.
		*/
		time_t getTimestamp(const unsigned int & index) const;

		/**
		* Get a timestamp as a time structure at a particular index of this timeseries.
		* It allows to read dates from 1900-01-01T00:00:00
		*/
		tm getTimestampAsTimeStructure(const unsigned int & index) const;

		/**
		* Get all the properties which use this time series
		*/
		const std::vector<RESQML2_NS::AbstractProperty*>& getPropertySet() const { return propertySet; }

	protected:

		std::vector<epc::Relationship> getAllEpcRelationships() const;
		/**
		* Does nothing since StringTableLookup has not got any forward relationship.
		*/
		void importRelationshipSetFromEpc(COMMON_NS::EpcDocument* epcDoc) {}

		// XML backward relationship
		std::vector<RESQML2_NS::AbstractProperty*> propertySet;

		friend void AbstractProperty::setTimeSeries(TimeSeries * ts);
	};
}

