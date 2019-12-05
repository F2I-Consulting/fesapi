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

namespace WITSML2_0_NS
{
	/**
	* Captures information about the configuration of the permanently installed components in a wellbore. It does not define the transient drilling strings (see the Tubular object) or the hanging production components (see the Completion object).
	*/
	template <class T>
	class ChannelIndexDataObject : public ChannelMetaDataObject<T>
	{
	public:
		/**
		* Constructor for partial transfer
		*/
		DLL_IMPORT_OR_EXPORT ChannelIndexDataObject(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : ChannelMetaDataObject<T>(partialObject) {}

		/**
		* Creates an instance of this class in a gsoap context.
		*/
		ChannelIndexDataObject() : ChannelMetaDataObject<T>() {}

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		ChannelIndexDataObject(gsoap_eml2_1::eml21__AbstractObject* fromGsoap) : ChannelMetaDataObject<T>(fromGsoap) {}

		/**
		* Destructor does nothing since the memory is managed by the gsoap context.
		*/
		virtual ~ChannelIndexDataObject() {}

		DLL_IMPORT_OR_EXPORT virtual void pushBackChannelIndex(gsoap_eml2_1::witsml20__ChannelIndexType indexType, gsoap_eml2_1::eml21__UnitOfMeasure uom, const std::string & mnemonic, bool isIncreasing = true, const std::string & datum = "") = 0;

		unsigned int getChannelIndexCount() const {
			return static_cast<T*>(this->gsoapProxy2_1)->Index.size();
		}

		gsoap_eml2_1::witsml20__ChannelIndexType getChannelIndexType(unsigned int index) {
			if (index >= getChannelIndexCount()) {
				throw std::out_of_range("The channel index is out of range");
			}
			return static_cast<T*>(this->gsoapProxy2_1)->Index[index]->IndexType;
		}

		std::string getChannelIndexUom(unsigned int index) {
			if (index >= getChannelIndexCount()) {
				throw std::out_of_range("The channel index is out of range");
			}
			return static_cast<T*>(this->gsoapProxy2_1)->Index[index]->Uom;
		}

		bool getChannelIndexIsIncreasing(unsigned int index) {
			if (index >= getChannelIndexCount()) {
				throw std::out_of_range("The channel index is out of range");
			}
			return static_cast<T*>(this->gsoapProxy2_1)->Index[index]->Direction == gsoap_eml2_1::witsml20__IndexDirection__increasing;
		}

		std::string getChannelIndexMnemonic(unsigned int index) {
			if (index >= getChannelIndexCount()) {
				throw std::out_of_range("The channel index is out of range");
			}
			return static_cast<T*>(this->gsoapProxy2_1)->Index[index]->Mnemonic;
		}

		std::string getChannelIndexDatum(unsigned int index) {
			if (index >= getChannelIndexCount()) {
				throw std::out_of_range("The channel index is out of range");
			}
			return static_cast<T*>(this->gsoapProxy2_1)->Index[index]->DatumReference == nullptr ? "" : *static_cast<T*>(this->gsoapProxy2_1)->Index[index]->DatumReference;
		}
	};
}
