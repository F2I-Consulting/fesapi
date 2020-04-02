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

/** . */
namespace RESQML2_NS
{
	/** A string table lookup. */
	class StringTableLookup : public COMMON_NS::AbstractObject
	{
	public:

		/**
		 * Only to be used in partial transfer context
		 *
		 * @param [in,out]	partialObject	If non-null, the partial object.
		 */
		DLL_IMPORT_OR_EXPORT StringTableLookup(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : COMMON_NS::AbstractObject(partialObject) {}

		/** Destructor does nothing since the memory is managed by the gsoap context. */
		virtual ~StringTableLookup() {}

		/**
		 * Check wether a key value is contained within this string lookup or not.
		 *
		 * @param 	longValue	The long value.
		 *
		 * @returns	True if it succeeds, false if it fails.
		 */
		DLL_IMPORT_OR_EXPORT virtual bool containsKey(long longValue) = 0;

		/**
		 * Get the count of item in the stringTableLookup (in the map).
		 *
		 * @returns	The item count.
		 */
		DLL_IMPORT_OR_EXPORT virtual unsigned int getItemCount() const = 0;

		/**
		 * Get the key of a string value pair at a particular index in the string table lookup (in the
		 * map)
		 *
		 * @param 	index	Zero-based index of the.
		 *
		 * @returns	The key at index.
		 */
		DLL_IMPORT_OR_EXPORT virtual long getKeyAtIndex(unsigned int index) const = 0;

		/**
		 * Get the string value of a string value pair at a particular index in the string table lookup
		 * (in the map)
		 *
		 * @param 	index	Zero-based index of the.
		 *
		 * @returns	The string value at index.
		 */
		DLL_IMPORT_OR_EXPORT virtual std::string getStringValueAtIndex(unsigned int index) const = 0;

		/**
		 * Get a string value from its associated key (long) value. If the key value does not exist, an
		 * empty string is returned.
		 *
		 * @param 	longValue	The long value.
		 *
		 * @returns	The string value.
		 */
		DLL_IMPORT_OR_EXPORT virtual std::string getStringValue(long longValue) = 0;

		/**
		 * Add a pair value to the string lookup. No verification that the key value (or string value)
		 * already exists
		 *
		 * @param 	strValue 	The value.
		 * @param 	longValue	The long value.
		 */
		DLL_IMPORT_OR_EXPORT virtual void addValue(const std::string & strValue, long longValue) = 0;

		/**
		 * Modify the associated string value according to the key (long) value. If the key value does
		 * not exist, nothing is done.
		 *
		 * @param 	strValue 	The value.
		 * @param 	longValue	The long value.
		 */
		DLL_IMPORT_OR_EXPORT virtual void setValue(const std::string & strValue, long longValue) = 0;

		/**
		 * Get the minimum value in this discrete properties. It reads it from file.
		 *
		 * @returns	the minimum value if present in the file otherwise long.max.
		 */
		DLL_IMPORT_OR_EXPORT virtual LONG64 getMinimumValue() = 0;

		/**
		 * Get the maximum value in this discrete properties. It reads it from file.
		 *
		 * @returns	the maximum value if present in the file otherwise long.min.
		 */
		DLL_IMPORT_OR_EXPORT virtual LONG64 getMaximumValue() = 0;

		/**
		 * Getter for the underlying map of the string lookup.
		 *
		 * @returns	The map.
		 */
		DLL_IMPORT_OR_EXPORT virtual std::unordered_map<long, std::string> getMap() const = 0;

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
		DLL_IMPORT_OR_EXPORT std::string getXmlTag() const final { return XML_TAG; }

	protected:

		/** Default constructor */
		StringTableLookup() {}

		/**
		 * Creates an instance of this class by wrapping a gSoap RESQML2.0.1 instance.
		 *
		 * @param [in,out]	fromGsoap	If non-null, from gsoap.
		 */
		StringTableLookup(gsoap_resqml2_0_1::_resqml20__StringTableLookup* fromGsoap) : AbstractObject(fromGsoap) {}

		/**
		 * Creates an instance of this class by wrapping a gSoap RESQML2.2 instance.
		 *
		 * @param [in,out]	fromGsoap	If non-null, from gsoap.
		 */
		StringTableLookup(gsoap_eml2_3::_resqml22__StringTableLookup* fromGsoap) : AbstractObject(fromGsoap) {}

		/** Loads target relationships */
		void loadTargetRelationships() {}
	};
}
