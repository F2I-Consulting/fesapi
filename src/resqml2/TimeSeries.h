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

#include "resqml2/AbstractProperty.h"

namespace resqml2
{
	class DLL_IMPORT_OR_EXPORT TimeSeries : public common::AbstractObject
	{
	protected:
		/**
		* Default constructor does nothing
		*/
		TimeSeries() {}

		/**
		* Only to be used in partial transfer context
		*/
		TimeSeries(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : common::AbstractObject(partialObject) {}

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		TimeSeries(gsoap_resqml2_0_1::_resqml2__TimeSeries* fromGsoap) : common::AbstractObject(fromGsoap) {}

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
		* Get the index of a timestamp in the time series.
		* @return	uint.max if this timestamps has not been found in this time series.
		*/
		unsigned int getTimestampIndex(const time_t & timestamp) const;

		/**
		* Get the count of timestamps in this time series.
		*/
		unsigned int getTimestampCount() const;

		/**
		* Get a timestamp at a particular index of this timeseries.
		*/
		time_t getTimestamp(const unsigned int & index) const;

		/**
		* Get all the properties which use this time series
		*/
		const std::vector<resqml2::AbstractProperty*>& getPropertySet() const { return propertySet; }

	protected:

		std::vector<epc::Relationship> getAllEpcRelationships() const;
		/**
		* Does nothing since StringTableLookup has not got any forward relationship.
		*/
		void importRelationshipSetFromEpc(common::EpcDocument* epcDoc) {}

		// XML backward relationship
		std::vector<resqml2::AbstractProperty*> propertySet;

		friend void AbstractProperty::setTimeSeries(TimeSeries * ts);
	};
}
