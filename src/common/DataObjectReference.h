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

#if defined(__clang__)
#elif defined(__GNUG__) && __GNUC__ > 12  // https://stackoverflow.com/questions/31509434/gcc-does-not-honor-pragma-gcc-diagnostic-to-silence-warnings
#pragma GCC diagnostic push 
#pragma GCC diagnostic ignored "-Wmisleading-indentation"
#endif
#include "../proxies/gsoap_resqml2_0_1H.h"
#include "../proxies/gsoap_eml2_3H.h"
#if defined(__clang__)
#elif defined(__GNUG__) && __GNUC__ > 12
#pragma GCC diagnostic pop
#endif

#include "../nsDefinitions.h"

#if defined(_WIN32) && !defined(FESAPI_STATIC)
#if defined(FesapiCpp_EXPORTS) || defined(FesapiCppUnderDev_EXPORTS)
#define DLL_IMPORT_OR_EXPORT __declspec(dllexport)
#else
#define DLL_IMPORT_OR_EXPORT __declspec(dllimport) 
#endif
#else
#define DLL_IMPORT_OR_EXPORT
#endif

namespace COMMON_NS
{
	class AbstractObject;
	/** @brief	This class wraps an Energistics Data Object Reference whatever its version is. */
	class DataObjectReference
	{
	public:

		/** Default constructor */
		DataObjectReference(): dor20(nullptr), dor23(nullptr) {}
		
		/**
		 * Constructor
		 *
		 * @param [in]	dor	If non-nullptr, the EML2.0 DOR to wrap.
		 */
		DataObjectReference(gsoap_resqml2_0_1::eml20__DataObjectReference * dor): dor20(dor), dor23(nullptr) {}
		
		/**
		 * Constructor
		 *
		 * @param [in,out]	dor	If non-nullptr, the EML2.3 DOR to wrap.
		 */
		DataObjectReference(gsoap_eml2_3::eml23__DataObjectReference * dor) : dor20(nullptr), dor23(dor) {}

		/**
		 * Constructor
		 *
		 * @param [in,out]	dor	If non-nullptr, the Energistics DataObject to wrap.
		 */
		explicit DataObjectReference(AbstractObject const * dataObj);

		/** Destructor */
		~DataObjectReference() = default;

		/**
		 * Checks if this reference is empty (i.e. it points to nothing)
		 *
		 * @returns	True if this reference empty, false if it is not.
		 */
		DLL_IMPORT_OR_EXPORT bool isEmpty() const {
			return dor20 == nullptr && dor23 == nullptr;
		}

		/**
		 * Gets the referenced data object UUID
		 *
		 * @returns	The UUID of the referenced data object if it exists, otherwise empty string.
		 */
		DLL_IMPORT_OR_EXPORT std::string getUuid() const {
			if (dor20 != nullptr) {
				return dor20->UUID;
			}
			else if (dor23 != nullptr) {
				return dor23->Uuid;
			}
			else {
				return "";
			}
		}

		/**
		 * Gets the referenced data object title (i.e. its name)
		 *
		 * @returns	The title of the referenced data object if it exists, otherwise empty string.
		 */
		DLL_IMPORT_OR_EXPORT std::string getTitle() const {
			if (dor20 != nullptr) {
				return dor20->Title;
			}
			else if (dor23 != nullptr) {
				return dor23->Title;
			}
			else {
				return "";
			}
		}

		/**
		 * Gets the referenced data object version
		 *
		 * @returns	The version of the referenced data object if it exists, otherwise empty string.
		 */
		DLL_IMPORT_OR_EXPORT std::string getVersion() const {
			if (dor20 != nullptr) {
				return dor20->VersionString != nullptr ? *dor20->VersionString : "";
			}
			else if (dor23 != nullptr) {
				return dor23->ObjectVersion != nullptr ? *dor23->ObjectVersion : "";
			}
			else {
				return "";
			}
		}

		/**
		 * Gets the referenced data object type
		 *
		 * @returns	The content type of the referenced data object if it exists, otherwise empty string.
		 */
		DLL_IMPORT_OR_EXPORT std::string getContentType() const {
			if (dor20 != nullptr) {
				return dor20->ContentType;
			}
			else if (dor23 != nullptr) {
				return dor23->QualifiedType;
			}
			else {
				return "";
			}
		}

		/**
		 * Gets the Energistics URI of the referenced data object
		 *
		 * @returns	The Energistics URI of the referenced data object if it exists, otherwise empty string.
		 */
		DLL_IMPORT_OR_EXPORT std::string getEnergisticsUri() const {
			if (dor23 != nullptr && dor23->EnergisticsUri != nullptr) {
				return *dor23->EnergisticsUri;
			}
			else {
				return "";
			}
		}

		/**
		* Convert this instance to an EML2.0 DataObjectReference
		* The return type memory will be managed by gSoap, don't delete it.
		*
		* @returns A potentially new EML2.0 DataObjectReference corresponding to this instance. Do not delete it.
		*/
		DLL_IMPORT_OR_EXPORT gsoap_resqml2_0_1::eml20__DataObjectReference* toDor20() const;

	private :
		gsoap_resqml2_0_1::eml20__DataObjectReference* dor20;
		gsoap_eml2_3::eml23__DataObjectReference* dor23;
	};

	/**
	 * @brief	Title is not part of the real identifier of a dataobject. This is just a hint.
	 *
	 * @param 	ldor	The first instance to compare.
	 * @param 	rdor	The second instance to compare.
	 *
	 * @returns	True if the parameters are considered equivalent.
	 */
	inline bool operator==(const DataObjectReference& ldor, const DataObjectReference& rdor)
	{
		return ldor.getUuid() == rdor.getUuid() &&
			ldor.getContentType() == rdor.getContentType() &&
			ldor.getVersion() == rdor.getVersion();
	}
}
