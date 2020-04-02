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

#include "../resqml2/StringTableLookup.h"

/** . */
namespace RESQML2_2_NS
{
	/** A string table lookup. */
	class StringTableLookup final : public RESQML2_NS::StringTableLookup
	{
	public:

		/**
		 * Only to be used in partial transfer context
		 *
		 * @param [in,out]	partialObject	If non-null, the partial object.
		 *
		 * @returns	A DLL_IMPORT_OR_EXPORT.
		 */
		DLL_IMPORT_OR_EXPORT StringTableLookup(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : RESQML2_NS::StringTableLookup(partialObject) {}

		/**
		 * Creates an instance of this class in a gsoap context.
		 *
		 * @param [in,out]	repo 	A repo which will manage the memory of this instance.
		 * @param 		  	guid 	The guid to set to this instance. If empty then a new guid will be
		 * 							generated.
		 * @param 		  	title	A title for the instance to create.
		 */
		StringTableLookup(COMMON_NS::DataObjectRepository* repo, const std::string & guid, const std::string & title);

		/**
		 * Creates an instance of this class by wrapping a gsoap instance.
		 *
		 * @param [in,out]	fromGsoap	If non-null, from gsoap.
		 */
		StringTableLookup(gsoap_eml2_3::_resqml22__StringTableLookup* fromGsoap) : RESQML2_NS::StringTableLookup(fromGsoap) {}

		/** Destructor does nothing since the memory is managed by the gsoap context. */
		~StringTableLookup() {}

		/**
		 * Check wether a key value is contained within this string lookup or not.
		 *
		 * @param 	longValue	The long value.
		 *
		 * @returns	True if it succeeds, false if it fails.
		 */
		DLL_IMPORT_OR_EXPORT bool containsKey(long longValue);

		/**
		 * Get the count of item in the stringTableLookup (in the map).
		 *
		 * @returns	The item count.
		 */
		DLL_IMPORT_OR_EXPORT unsigned int getItemCount() const;

		/**
		 * Get the key of a string value pair at a particular index in the string table lookup (in the
		 * map)
		 *
		 * @param 	index	Zero-based index of the.
		 *
		 * @returns	The key at index.
		 */
		DLL_IMPORT_OR_EXPORT long getKeyAtIndex(unsigned int index) const;

		/**
		 * Get the string value of a string value pair at a particular index in the string table lookup
		 * (in the map)
		 *
		 * @param 	index	Zero-based index of the.
		 *
		 * @returns	The string value at index.
		 */
		DLL_IMPORT_OR_EXPORT std::string getStringValueAtIndex(unsigned int index) const;

		/**
		 * Get a string value from its associated key (long) value. If the key value does not exist, an
		 * empty string is returned.
		 *
		 * @param 	longValue	The long value.
		 *
		 * @returns	The string value.
		 */
		DLL_IMPORT_OR_EXPORT std::string getStringValue(long longValue);

		/**
		 * Add a pair value to the string lookup. No verification that the key value (or string value)
		 * already exists
		 *
		 * @param 	strValue 	The value.
		 * @param 	longValue	The long value.
		 */
		DLL_IMPORT_OR_EXPORT void addValue(const std::string & strValue, long longValue);

		/**
		 * Modify the associated string value according to the key (long) value. If the key value does
		 * not exist, nothing is done.
		 *
		 * @param 	strValue 	The value.
		 * @param 	longValue	The long value.
		 */
		DLL_IMPORT_OR_EXPORT void setValue(const std::string & strValue, long longValue);

		/**
		 * Get the minimum value in this discrete properties. It reads it from file.
		 *
		 * @returns	the minimum value if present in the file otherwise long.max.
		 */
		DLL_IMPORT_OR_EXPORT LONG64 getMinimumValue();

		/**
		 * Get the maximum value in this discrete properties. It reads it from file.
		 *
		 * @returns	the maximum value if present in the file otherwise long.min.
		 */
		DLL_IMPORT_OR_EXPORT LONG64 getMaximumValue();

		/**
		 * Getter for the underlying map of the string lookup.
		 *
		 * @returns	The map.
		 */
		DLL_IMPORT_OR_EXPORT std::unordered_map<long, std::string> getMap() const;
	};
}
