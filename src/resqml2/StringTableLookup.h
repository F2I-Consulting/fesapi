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
	/**
	 * @brief	Defines an integer (key) to string (value) lookup table, for example, stores facies
	 * 			properties, where a facies index is associated with a facies name.
	 * 			
	 * 			Used for categorical properties, which also may use a double table lookup.
	 */
	class StringTableLookup : public COMMON_NS::AbstractObject
	{
	public:

		/**
		 * Only to be used in partial transfer context.
		 *
		 * @param [in]	partialObject	If non-nullptr, the partial object.
		 */
		DLL_IMPORT_OR_EXPORT StringTableLookup(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : COMMON_NS::AbstractObject(partialObject) {}

		/** Destructor does nothing since the memory is managed by the gSOAP context. */
		virtual ~StringTableLookup() = default;

		/**
		 * Checks whether a key is contained within this string lookup.
		 *
		 * @param 	key	A key.
		 *
		 * @returns	True if @p longValue is a key of this string table lookup, false if not.
		 */
		DLL_IMPORT_OR_EXPORT virtual bool containsKey(int64_t key) = 0;

		/**
		 * Gets the count of items in the string table lookup (in its map).
		 *
		 * @returns	The count of items.
		 */
		DLL_IMPORT_OR_EXPORT virtual uint64_t getItemCount() const = 0;

		/**
		 * Gets the key of a key/value pair at a particular index of this string table lookup (in its
		 * map).
		 *
		 * @exception	std::out_of_range	If <tt>index &gt;=</tt> getItemCount().
		 *
		 * @param 	index	Zero-based index of the key/value pair.
		 *
		 * @returns	The key of the key/value pair at position @p index.
		 */
		DLL_IMPORT_OR_EXPORT virtual int64_t getKeyAtIndex(uint64_t index) const = 0;

		/**
		 * Gets the string value of a key/value pair at a particular index of this string table lookup
		 * (in its map).
		 *
		 * @exception	std::out_of_range	If <tt>index &gt;=</tt> getItemCount().
		 *
		 * @param 	index	Zero-based index of the key/value pair.
		 *
		 * @returns	The string value of the key/value pair at position @p index.
		 */
		DLL_IMPORT_OR_EXPORT virtual std::string getStringValueAtIndex(uint64_t index) const = 0;

		/**
		 * Gets a string value from its associated key.
		 *
		 * @param 	key	A key.
		 *
		 * @returns	The string value corresponding to the key @p longValue if it exists, empty string if
		 * 			not.
		 */
		DLL_IMPORT_OR_EXPORT virtual std::string getStringValue(int64_t key) = 0;

		/**
		 * Adds a key/value pair to this string table lookup. No verification that the key (or string
		 * value) already exists is done.
		 *
		 * @param 	strValue 	A string value.
		 * @param 	longValue	A key.
		 */
		DLL_IMPORT_OR_EXPORT virtual void addValue(const std::string & strValue, int64_t key) = 0;

		/**
		 * Modifies the string value associated to a key. If the key does not exist, nothing is
		 * done.
		 *
		 * @param 	strValue 	The new string value.
		 * @param 	longValue	A key.
		 */
		DLL_IMPORT_OR_EXPORT virtual void setValue(const std::string & strValue, int64_t key) = 0;

		/**
		 * Gets the minimum key in this string table lookup. It reads it from file.
		 *
		 * @returns	The minimum key if some key/value pairs exists in this string table lookup, otherwise
		 * 			the int64_t maximum value.
		 */
		DLL_IMPORT_OR_EXPORT virtual int64_t getMinimumValue() = 0;

		/**
		 * Gets the maximum key in this string table lookup. It reads it from file.
		 *
		 * @returns	The maximum key if some key/value pairs exists in this string table lookup, otherwise
		 * 			the int64_t minimum value.
		 */
		DLL_IMPORT_OR_EXPORT virtual int64_t getMaximumValue() = 0;

		/**
		 * Gets the underlying key/value map of this string table lookup.
		 *
		 * @returns	The key/value map.
		 */
		DLL_IMPORT_OR_EXPORT virtual std::unordered_map<int64_t, std::string> getMap() const = 0;

		/** The standard XML tag without XML namespace for serializing this data object. */
		DLL_IMPORT_OR_EXPORT static constexpr char const* XML_TAG = "StringTableLookup";

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

		/** Loads target relationships */
		void loadTargetRelationships() final {}
	};
}
