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

#include <map>

namespace RESQML2_NS
{
	/**
	 * @brief	Defines a function for table lookups. For example, used for linear interpolation, such as PVT.
	 * 			
	 * 			Used for categorical properties, which also may use a double table lookup.
	 */
	class DoubleTableLookup : public COMMON_NS::AbstractObject
	{
	public:

		/**
		 * Only to be used in partial transfer context.
		 *
		 * @param [in]	partialObject	If non-nullptr, the partial object.
		 */
		DLL_IMPORT_OR_EXPORT DoubleTableLookup(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : COMMON_NS::AbstractObject(partialObject) {}

		/** Destructor does nothing since the memory is managed by the gSOAP context. */
		virtual ~DoubleTableLookup() = default;

		/**
		 * Checks whether a key is contained within this double table lookup.
		 *
		 * @param 	key	A key.
		 *
		 * @returns	True if @p key is a key of this double table lookup, false if not.
		 */
		DLL_IMPORT_OR_EXPORT virtual bool containsKey(double key) = 0;

		/**
		 * Gets the count of items in the double table lookup (in its map).
		 *
		 * @returns	The count of items.
		 */
		DLL_IMPORT_OR_EXPORT virtual unsigned int getItemCount() const = 0;

		/**
		 * Gets the key of a key/value pair at a particular index of this double table lookup (in its
		 * map).
		 *
		 * @exception	std::out_of_range	If <tt>index &gt;=</tt> getItemCount().
		 *
		 * @param 	index	Zero-based index of the key/value pair.
		 *
		 * @returns	The key of the key/value pair at position @p index.
		 */
		DLL_IMPORT_OR_EXPORT virtual double getKeyAtIndex(unsigned int index) const = 0;

		/**
		 * Gets the value of a key/value pair at a particular index of this double table lookup
		 * (in its map).
		 *
		 * @exception	std::out_of_range	If <tt>index &gt;=</tt> getItemCount().
		 *
		 * @param 	index	Zero-based index of the key/value pair.
		 *
		 * @returns	The value of the key/value pair at position @p index.
		 */
		DLL_IMPORT_OR_EXPORT virtual double getValueAtIndex(unsigned int index) const = 0;

		/**
		 * Gets a value from its associated key.
		 *
		 * @param 	longValue	A key.
		 *
		 * @returns	The value corresponding to the key @p longValue if it exists, NaN if
		 * 			not.
		 */
		DLL_IMPORT_OR_EXPORT virtual double getValueAtKey(double key) = 0;

		/**
		 * Adds a key/value pair to this double table lookup. No verification that the key already exists is done.
		 *
		 * @param 	key		A key.
		 * @param 	value	Teh associated value.
		 */
		DLL_IMPORT_OR_EXPORT virtual void addValue(double key, double value) = 0;

		/**
		 * Modifies the value associated to a key. If the key does not exist, nothing is
		 * done.
		 *
		 * @param 	key		A key.
		 * @param 	value	Teh associated value.
		 */
		DLL_IMPORT_OR_EXPORT virtual void setValue(double key, double value) = 0;

		/**
		 * Gets the minimum key in this double table lookup. It reads it from file.
		 *
		 * @returns	The minimum key if some key/value pairs exists in this double table lookup, otherwise
		 * 			the double maximum value.
		 */
		DLL_IMPORT_OR_EXPORT virtual double getMinimumValue() = 0;

		/**
		 * Gets the maximum key in this double table lookup. It reads it from file.
		 *
		 * @returns	The maximum key if some key/value pairs exists in this double table lookup, otherwise
		 * 			the double lowest value.
		 */
		DLL_IMPORT_OR_EXPORT virtual double getMaximumValue() = 0;

		/**
		 * Build and return a key/value map of this double table lookup.
		 * You cannot use this map to set a value since it is built at each call.
		 *
		 * @returns	The key/value map.
		 */
		DLL_IMPORT_OR_EXPORT virtual std::map<double, double> getMap() const = 0;

		/** The standard XML tag without XML namespace for serializing this data object. */
		DLL_IMPORT_OR_EXPORT static const char* XML_TAG;

		DLL_IMPORT_OR_EXPORT std::string getXmlTag() const final { return XML_TAG; }

	protected:

		/** Default constructor */
		DoubleTableLookup() {}

		/**
		 * Creates an instance of this class by wrapping a gSoap RESQML2.0.1 instance.
		 *
		 * @param [in,out]	fromGsoap	If non-null, from gsoap.
		 */
		DoubleTableLookup(gsoap_resqml2_0_1::_resqml20__DoubleTableLookup* fromGsoap) : AbstractObject(fromGsoap) {}

		/**
		 * Creates an instance of this class by wrapping a gSoap RESQML2.2 instance.
		 *
		 * @param [in,out]	fromGsoap	If non-null, from gsoap.
		 */
		DoubleTableLookup(gsoap_eml2_3::_resqml22__DoubleTableLookup* fromGsoap) : AbstractObject(fromGsoap) {}

		/** Loads target relationships */
		void loadTargetRelationships() final {}
	};
}
