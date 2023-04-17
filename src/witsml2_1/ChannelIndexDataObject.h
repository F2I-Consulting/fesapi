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

#include "ChannelMetaDataObject.h"

#include <limits>

namespace WITSML2_1_NS
{
	/**
	 * Captures information about the configuration of the permanently installed components in a
	 * wellbore. It does not define the transient drilling strings (see the Tubular object) or the
	 * hanging production components (see the Completion object).
	 *
	 * @tparam	T	Generic type parameter.
	 */
	template <class T>
	class ChannelIndexDataObject : public ChannelMetaDataObject<T>
	{
	public:

		/**
		 * Constructor for partial transfer
		 *
		 * @param [in,out]	partialObject	If non-null, the partial object.
		 *
		 * 
		 */
		DLL_IMPORT_OR_EXPORT ChannelIndexDataObject(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : ChannelMetaDataObject<T>(partialObject) {}

		/** Creates an instance of this class in a gsoap context. */
		ChannelIndexDataObject() : ChannelMetaDataObject<T>() {}

		/**
		 * Creates an instance of this class by wrapping a gsoap instance.
		 *
		 * @param [in,out]	fromGsoap	If non-null, from gsoap.
		 */
		ChannelIndexDataObject(gsoap_eml2_3::eml23__AbstractObject* fromGsoap) : ChannelMetaDataObject<T>(fromGsoap) {}

		/** Destructor does nothing since the memory is managed by the gsoap context. */
		virtual ~ChannelIndexDataObject() = default;

		/**
		 * Pushes a back channel index
		 *
		 * @param 	indexKind  		The index.
		 * @param 	uom				The uom.
		 * @param 	mnemonic		The mnemonic.
		 * @param 	isIncreasing	(Optional) True if is increasing, false if not.
		 */
		DLL_IMPORT_OR_EXPORT virtual void pushBackChannelIndex(gsoap_eml2_3::eml23__DataIndexKind indexKind, gsoap_eml2_3::eml23__UnitOfMeasure uom, const std::string & mnemonic, bool isIncreasing = true) = 0;
		
		/**
		 * Gets channel index count
		 *
		 * @returns	The channel index count.
		 */
		unsigned int getChannelIndexCount() const {
			const size_t result = static_cast<T*>(this->gsoapProxy2_3)->Index.size();
			if (result > (std::numeric_limits<unsigned int>::max)()) {
				throw std::range_error("There are too much channel index.");
			}

			return static_cast<unsigned int>(result);
		}

		/**
		 * Gets channel index type
		 *
		 * @exception	std::out_of_range	Thrown when an out of range error condition occurs.
		 *
		 * @param 	index	Zero-based index of the.
		 *
		 * @returns	The channel index type.
		 */
		gsoap_eml2_3::eml23__DataIndexKind getChannelIndexKind(unsigned int index) {
			if (index >= getChannelIndexCount()) {
				throw std::out_of_range("The channel index is out of range");
			}
			return static_cast<T*>(this->gsoapProxy2_3)->Index[index]->IndexKind;
		}

		/**
		 * Gets channel index uom
		 *
		 * @exception	std::out_of_range	Thrown when an out of range error condition occurs.
		 *
		 * @param 	index	Zero-based index of the.
		 *
		 * @returns	The channel index uom.
		 */
		std::string getChannelIndexUom(unsigned int index) {
			if (index >= getChannelIndexCount()) {
				throw std::out_of_range("The channel index is out of range");
			}
			return static_cast<T*>(this->gsoapProxy2_3)->Index[index]->Uom;
		}

		/**
		 * Gets channel index is increasing
		 *
		 * @exception	std::out_of_range	Thrown when an out of range error condition occurs.
		 *
		 * @param 	index	Zero-based index of the.
		 *
		 * @returns	True if it succeeds, false if it fails.
		 */
		bool getChannelIndexIsIncreasing(unsigned int index) {
			if (index >= getChannelIndexCount()) {
				throw std::out_of_range("The channel index is out of range");
			}
			return static_cast<T*>(this->gsoapProxy2_3)->Index[index]->Direction == gsoap_eml2_3::eml23__IndexDirection::increasing;
		}

		/**
		 * Gets channel index mnemonic
		 *
		 * @exception	std::out_of_range	Thrown when an out of range error condition occurs.
		 *
		 * @param 	index	Zero-based index of the.
		 *
		 * @returns	The channel index mnemonic.
		 */
		std::string getChannelIndexMnemonic(unsigned int index) {
			if (index >= getChannelIndexCount()) {
				throw std::out_of_range("The channel index is out of range");
			}
			return static_cast<T*>(this->gsoapProxy2_3)->Index[index]->Mnemonic;
		}
	};
}
