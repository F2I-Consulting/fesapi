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

namespace RESQML2_0_1_NS
{
	class StringTableLookup : public COMMON_NS::AbstractObject
	{
	public:

		/**
		* Only to be used in partial transfer context
		*/
		StringTableLookup(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : COMMON_NS::AbstractObject(partialObject) {}

		/**
		* Default constructor
		*/
		StringTableLookup() {}

		/**
		* Creates an instance of this class in a gsoap context.
		* @param repo		A repo which will manage the memory of this instance.
		* @param guid		The guid to set to this instance. If empty then a new guid will be generated.
		* @param title		A title for the instance to create.
		*/
		StringTableLookup(COMMON_NS::DataObjectRepository* repo, const std::string & guid, const std::string & title);

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		StringTableLookup(gsoap_resqml2_0_1::_resqml2__StringTableLookup* fromGsoap) : AbstractObject(fromGsoap) {}

		/**
		* Destructor does nothing since the memory is managed by the gsoap context.
		*/
		~StringTableLookup() {}
		
		DLL_IMPORT_OR_EXPORT static const char* XML_TAG;
		DLL_IMPORT_OR_EXPORT virtual std::string getXmlTag() const {return XML_TAG;}

		/**
		* Check wether a key value is contained within this string lookup or not.
		*/
		DLL_IMPORT_OR_EXPORT bool containsKey(const long & longValue);

		/**
		* Get the count of item in the stringTableLookup (in the map).
		*/
		DLL_IMPORT_OR_EXPORT unsigned int getItemCount() const;

		/**
		* Get the key of a string value pair at a particular index in the string table lookup (in the map)
		*/
		DLL_IMPORT_OR_EXPORT long getKeyAtIndex(const unsigned int & index) const;

		/**
		* Get the string value of a string value pair at a particular index in the string table lookup (in the map)
		*/
		DLL_IMPORT_OR_EXPORT std::string getStringValueAtIndex(const unsigned int & index) const;

		/**
		* Get a string value from its associated key (long) value.
		* If the key value does not exist, an empty string is returned.
		*/
		DLL_IMPORT_OR_EXPORT std::string getStringValue(const long & longValue);

		/**
		* Add a pair value to the string lookup.
		* No verification that the key value (or string value) already exists
		*/
		DLL_IMPORT_OR_EXPORT void addValue(const std::string & strValue, const long & longValue);

		/**
		* Modify the associated string value according to the key (long) value.
		* If the key value does not exist, nothing is done.
		*/
		DLL_IMPORT_OR_EXPORT void setValue(const std::string & strValue, const long & longValue);

		/*
		* Get the minimum value in this discrete properties. It reads it from file.
		* @return the minimum value if present in the file otherwise long.max.
		*/
		DLL_IMPORT_OR_EXPORT LONG64 getMinimumValue();

		/*
		* Get the maximum value in this discrete properties. It reads it from file.
		* @return the maximum value if present in the file otherwise long.min.
		*/
		DLL_IMPORT_OR_EXPORT LONG64 getMaximumValue();

		/*
		* Getter for the underlying map of the string lookup.
		*/
		DLL_IMPORT_OR_EXPORT std::unordered_map<long, std::string> getMap() const;

		void loadTargetRelationships();
	};
}
