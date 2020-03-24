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

#include "../proxies/gsoap_resqml2_0_1H.h"
#include "../proxies/gsoap_eml2_1H.h"
#include "../proxies/gsoap_eml2_2H.h"
#include "../proxies/gsoap_eml2_3H.h"

#include "../nsDefinitions.h"

namespace COMMON_NS
{
	/**
	* This class wraps an Energistics Data Object Reference whatever its version is.
	*/
	class DataObjectReference
	{
	public:

		DataObjectReference(): dor20(nullptr), dor21(nullptr), dor22(nullptr), dor23(nullptr) {}
		DataObjectReference(gsoap_resqml2_0_1::eml20__DataObjectReference * dor): dor20(dor), dor21(nullptr), dor22(nullptr), dor23(nullptr) {}
		DataObjectReference(gsoap_eml2_1::eml21__DataObjectReference * dor) : dor20(nullptr), dor21(dor), dor22(nullptr), dor23(nullptr) {}
		DataObjectReference(gsoap_eml2_2::eml22__DataObjectReference * dor) : dor20(nullptr), dor21(nullptr), dor22(dor), dor23(nullptr) {}
		DataObjectReference(gsoap_eml2_3::eml23__DataObjectReference * dor) : dor20(nullptr), dor21(nullptr), dor22(nullptr), dor23(dor) {}

		~DataObjectReference() {}

		/**
		* Check if the reference is empty (i.e. points to nothing)
		*/
		bool isEmpty() const {
			return dor20 == nullptr && dor21 == nullptr && dor22 == nullptr && dor23 == nullptr;
		}

		/**
		* Get the referenced dataobject UUID
		*/
		std::string getUuid() const {
			if (dor20 != nullptr) {
				return dor20->UUID;
			}
			else if (dor21 != nullptr) {
				return dor21->Uuid;
			}
			else if (dor22 != nullptr) {
				return dor22->Uuid;
			}
			else if (dor23 != nullptr) {
				return dor23->Uuid;
			}
			else {
				return "";
			}
		}

		/**
		* Get the referenced dataobject title (i.e. name)
		*/
		std::string getTitle() const {
			if (dor20 != nullptr) {
				return dor20->Title;
			}
			else if (dor21 != nullptr) {
				return dor21->Title;
			}
			else if (dor22 != nullptr) {
				return dor22->Title;
			}
			else if (dor23 != nullptr) {
				return dor23->Title;
			}
			else {
				return "";
			}
		}

		/**
		* Get the referenced dataobject version
		*/
		std::string getVersion() const {
			if (dor20 != nullptr) {
				return dor20->VersionString != nullptr ? *dor20->VersionString : "";
			}
			else if (dor21 != nullptr) {
				return dor21->VersionString != nullptr ? *dor21->VersionString : "";
			}
			else if (dor22 != nullptr) {
				return dor22->ObjectVersion != nullptr ? *dor22->ObjectVersion : "";
			}
			else if (dor23 != nullptr) {
				return dor23->ObjectVersion != nullptr ? *dor23->ObjectVersion : "";
			}
			else {
				return "";
			}
		}

		/**
		* Get the referenced dataobject type
		*/
		std::string getContentType() const {
			if (dor20 != nullptr) {
				return dor20->ContentType;
			}
			else if (dor21 != nullptr) {
				return dor21->ContentType;
			}
			else if (dor22 != nullptr) {
				return dor22->ContentType;
			}
			else if (dor23 != nullptr) {
				return dor23->ContentType;
			}
			else {
				return "";
			}
		}

	private :
		gsoap_resqml2_0_1::eml20__DataObjectReference* dor20;
		gsoap_eml2_1::eml21__DataObjectReference* dor21;
		gsoap_eml2_2::eml22__DataObjectReference* dor22;
		gsoap_eml2_3::eml23__DataObjectReference* dor23;
	};
}
