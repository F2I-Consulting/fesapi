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

#include "common/AbstractObject.h"

namespace resqml2_0_1
{
	class DLL_IMPORT_OR_EXPORT StringTableLookup : public common::AbstractObject
	{
	public:

		/**
		* Only to be used in partial transfer context
		*/
		StringTableLookup(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : common::AbstractObject(partialObject) {}

		/**
		* Default constructor
		*/
		StringTableLookup() {}

		/**
		* Creates an instance of this class in a gsoap context.
		* @param soap		A gsoap context wihch will manage the memory and the serialization/deserialization of this instance.
		* @param guid		The guid to set to this instance. If empty then a new guid will be generated.
		* @param title		A title for the instance to create.
		*/
		StringTableLookup(soap* soapContext, const std::string & guid, const std::string & title);

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		StringTableLookup(gsoap_resqml2_0_1::_resqml2__StringTableLookup* fromGsoap) : AbstractObject(fromGsoap) {}

		/**
		* Destructor does nothing since the memory is managed by the gsoap context.
		*/
		~StringTableLookup() {}
		
		static const char* XML_TAG;
		virtual std::string getXmlTag() const {return XML_TAG;}

		/**
		* Add a categorical property values object which uses this string lookup.
		* Does not add the inverse relationship i.e. from the categorical property values object to this string lookup.
		*/
		void addCategoricalPropertyValues(class CategoricalProperty* categVal) {categoricalPropertyValuesSet.push_back(categVal);}

		/**
		* Check wether a key value is contained within this string lookup or not.
		*/
		bool containsKey(const long & longValue);

		/**
		* Get the count of item in the stringTableLookup (in the map).
		*/
		unsigned int getItemCount() const;

		/**
		* Get the key of a string value pair at a particular index in the string table lookup (in the map)
		*/
		long getKeyAtIndex(const unsigned int & index) const;

		/**
		* Get the string value of a string value pair at a particular index in the string table lookup (in the map)
		*/
		std::string getStringValueAtIndex(const unsigned int & index) const;

		/**
		* Get a string value from its associated key (long) value.
		* If the key value does not exist, an empty string is returned.
		*/
		std::string getStringValue(const long & longValue);

		/**
		* Add a pair value to the string lookup.
		* No verification that the key value (or string value) already exists
		*/
		void addValue(const std::string & strValue, const long & longValue);

		/**
		* Modify the associated string value according to the key (long) value.
		* If the key value does not exist, nothing is done.
		*/
		void setValue(const std::string & strValue, const long & longValue);

		/*
		* Getter for the underlying map of the string lookup.
		*/
#if (defined(_WIN32) && _MSC_VER >= 1600) || defined(__APPLE__)
		std::unordered_map<long, std::string> getMap() const;
#else
		std::tr1::unordered_map<long, std::string> getMap() const;
#endif

	protected:

		std::vector<epc::Relationship> getAllEpcRelationships() const;
		/**
		* Does nothing since StringTableLookup has not got any forward relationship.
		*/
		void importRelationshipSetFromEpc(common::EpcDocument* epcDoc) {}

		// XML backwards relationships
		std::vector<class CategoricalProperty*> categoricalPropertyValuesSet;
	};
}

