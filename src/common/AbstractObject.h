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

#include <unordered_map>
#include <vector>
#include <stdexcept>

#include "DataObjectRepository.h"

namespace COMMON_NS
{
	/** @brief	An abstract data object. */
	class AbstractObject
	{
	private:
		/** The variable which holds the format for all exported Energistics DataObjects. */
		static char citationFormat[];

		/**
		 * Set a uuid. If the input uuid is empty then a random uuid will be set. It is too dangerous
		 * for now to modify the uuid because too much things depend on it. That's why this method is
		 * private.
		 *
		 * @param 	uuid	The uuid.
		 */
		void setUuid(const std::string & uuid);

	protected:
		/** Should be instantiated when the object is (or was) a partial object. */
		gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject;

		/** The underlying generated gSoap proxy for a EML 2.0 dataobject. */
		gsoap_resqml2_0_1::eml20__AbstractCitedDataObject* gsoapProxy2_0_1;

		/** The underlying generated gSoap proxy for a EML 2.1 dataobject. */
		gsoap_eml2_1::eml21__AbstractObject* gsoapProxy2_1;

		/** The underlying generated gSoap proxy for a EML 2.2 dataobject. */
		gsoap_eml2_2::eml22__AbstractObject* gsoapProxy2_2;

		/** The underlying generated gSoap proxy for a EML 2.3 dataobject. */
		gsoap_eml2_3::eml23__AbstractObject* gsoapProxy2_3;

		/** The repository which contains this data object. */
		COMMON_NS::DataObjectRepository* repository;

		/**
		* Default constructor
		*/
		AbstractObject() :
			partialObject(nullptr), gsoapProxy2_0_1(nullptr),
			gsoapProxy2_1(nullptr),
			gsoapProxy2_2(nullptr),
			gsoapProxy2_3(nullptr),
			repository(nullptr) {}

		/**
		 * Constructor for partial transfer
		 *
		 * @param [in,out]	partialObject_	If non-null, the partial object.
		 */
		AbstractObject(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject_) :
			partialObject(partialObject_), gsoapProxy2_0_1(nullptr),
			gsoapProxy2_1(nullptr),
			gsoapProxy2_2(nullptr),
			gsoapProxy2_3(nullptr),
			repository(nullptr) {}
		AbstractObject(const DataObjectReference& dor) :
			partialObject(dor.toDor20()), gsoapProxy2_0_1(nullptr),
			gsoapProxy2_1(nullptr),
			gsoapProxy2_2(nullptr),
			gsoapProxy2_3(nullptr),
			repository(nullptr) {}

		/**
		 * Constructor when importing EML 2.0 (i.e RESQML2.0.1) dataobjects
		 *
		 * @param [in,out]	proxy	If non-null, the proxy.
		 */
		AbstractObject(gsoap_resqml2_0_1::eml20__AbstractCitedDataObject* proxy) :
			partialObject(nullptr), gsoapProxy2_0_1(proxy),
			gsoapProxy2_1(nullptr),
			gsoapProxy2_2(nullptr),
			gsoapProxy2_3(nullptr),
			repository(nullptr) {}

		/**
		 * Constructor when importing EML 2.1 dataobjects
		 *
		 * @param [in,out]	proxy	If non-null, the proxy.
		 */
		AbstractObject(gsoap_eml2_1::eml21__AbstractObject* proxy) :
			partialObject(nullptr), gsoapProxy2_0_1(nullptr),
			gsoapProxy2_1(proxy),
			gsoapProxy2_2(nullptr),
			gsoapProxy2_3(nullptr),
			repository(nullptr) {}

		/**
		 * Constructor when importing EML 2.2 dataobjects
		 *
		 * @param [in,out]	proxy	If non-null, the proxy.
		 */
		AbstractObject(gsoap_eml2_2::eml22__AbstractObject* proxy) :
			partialObject(nullptr), gsoapProxy2_0_1(nullptr),
			gsoapProxy2_1(nullptr),
			gsoapProxy2_2(proxy),
			gsoapProxy2_3(nullptr),
			repository(nullptr) {}

		/**
		 * Constructor when importing EML 2.3 dataobjects
		 *
		 * @param [in,out]	proxy	If non-null, the proxy.
		 */
		AbstractObject(gsoap_eml2_3::eml23__AbstractObject* proxy) :
			partialObject(nullptr), gsoapProxy2_0_1(nullptr),
			gsoapProxy2_1(nullptr),
			gsoapProxy2_2(nullptr),
			gsoapProxy2_3(proxy),
			repository(nullptr) {}

		/**
		 * Adds an or replace data object
		 *
		 * @param [in,out]	proxy				If non-null, the proxy.
		 * @param [in,out]	replaceOnlyContent	If true, only replace the content of corresponding object, not the object itself.
		 *
		 * @returns	The new DataObject.
		 */
		friend COMMON_NS::AbstractObject* COMMON_NS::DataObjectRepository::addOrReplaceDataObject(AbstractObject* proxy, bool replaceOnlyContent);

		/**
		 * Initialize all mandatory attributes of an AbstractObject (not the attributes of a
		 * specialization) with some valid values.
		 */
		void initMandatoryMetadata();

		/**
		 * It is too dangerous for now to modify the uuid because too much things depend on it. That's
		 * why this method is only protected : it is only used by derived class constructor. Set a title
		 * and other common metadata for the resqml instance. Set to empty string or zero if you don't
		 * want to use.
		 *
		 * @param 	guid			   	Unique identifier.
		 * @param 	title			   	The title to set to the resqml instance. Set to empty string if
		 * 								you don't want to set it.
		 * @param 	editor			   	The editor.
		 * @param 	creation		   	The creation.
		 * @param 	originator		   	The originator.
		 * @param 	description		   	The description.
		 * @param 	lastUpdate		   	The last update.
		 * @param 	descriptiveKeywords	The descriptive keywords.
		 */
		void setMetadata(const std::string & guid, const std::string & title, const std::string & editor, time_t creation, const std::string & originator,
			const std::string & description, time_t lastUpdate, const std::string & descriptiveKeywords);

		/** Throw an exception if the instance if partial. */
		void cannotBePartial() const;

		/** Transform a non partial object into a partial one */
		void changeToPartialObject();

		/**
		 * Read an input array which come from EML 2.0 (and potentially HDF5) and store it into a
		 * preallocated output array in memory. It does not allocate or deallocate memory.
		 *
		 * @param [in,out]	arrayInput 	If non-null, the array input.
		 * @param [in,out]	arrayOutput	If non-null, the array output.
		 */
		void readArrayNdOfDoubleValues(gsoap_resqml2_0_1::resqml20__AbstractDoubleArray * arrayInput, double * arrayOutput) const;

		/**
		 * Read an input array which come from EML 2.3 (and potentially HDF5) and store it into a
		 * preallocated output array in memory. It does not allocate or deallocate memory.
		 *
		 * @param [in,out]	arrayInput 	If non-null, the array input.
		 * @param [in,out]	arrayOutput	If non-null, the array output.
		 */
		void readArrayNdOfDoubleValues(gsoap_eml2_3::eml23__AbstractFloatingPointArray * arrayInput, double * arrayOutput) const;

		/**
		 * Read an input array which come from EML 2.0 (and potentially HDF5) and store it into a
		 * preallocated output array in memory. It does not allocate or deallocate memory.
		 *
		 * @param [in,out]	arrayInput 	If non-null, the array input.
		 * @param [in,out]	arrayOutput	If non-null, the array output.
		 */
		void readArrayNdOfUIntValues(gsoap_resqml2_0_1::resqml20__AbstractIntegerArray * arrayInput, unsigned int * arrayOutput) const;

		/**
		 * Read an input array which come from EML 2.3 (and potentially HDF5) and store it into a
		 * preallocated output array in memory. It does not allocate or deallocate memory.
		 *
		 * @param [in,out]	arrayInput 	If non-null, the array input.
		 * @param [in,out]	arrayOutput	If non-null, the array output.
		 */
		void readArrayNdOfUIntValues(gsoap_eml2_3::eml23__AbstractIntegerArray * arrayInput, unsigned int * arrayOutput) const;

		/**
		 * Get the count of item in an array of integer
		 *
		 * @param [in,out]	arrayInput	The array of integer.
		 *
		 * @returns	The count of item in the array of integer.
		 */
		ULONG64 getCountOfIntegerArray(gsoap_resqml2_0_1::resqml20__AbstractIntegerArray * arrayInput) const;

		/**
		 * Get the count of item in an array of integer
		 *
		 * @param [in,out]	arrayInput	The array of integer.
		 *
		 * @returns	The count of item in the array of integer.
		 */
		ULONG64 getCountOfIntegerArray(gsoap_eml2_3::eml23__AbstractIntegerArray * arrayInput) const;

		/**
		 * Converts a data object reference into a data object repository relationship.
		 *
		 * @param dor The data object reference to convert.
		 */
		void convertDorIntoRel(const DataObjectReference& dor);

		/**
		 * Same as convertDorIntoRel(gsoap_resqml2_0_1::eml20__DataObjectReference const * dor). Also
		 * check that the content type of the DOR is OK with the target datatype in memory.
		 *
		 * @exception	std::invalid_argument	Thrown when an invalid argument error condition occurs.
		 *
		 * @tparam	valueType	Type of the value type.
		 * @param 	dor	The dor.
		 */
		template <class valueType>
		void convertDorIntoRel(const DataObjectReference& dor)
		{
			valueType * targetObj = getRepository()->getDataObjectByUuid<valueType>(dor.getUuid());
			if (targetObj == nullptr) { // partial transfer
				getRepository()->createPartial(dor);
				targetObj = getRepository()->getDataObjectByUuid<valueType>(dor.getUuid());
				if (targetObj == nullptr) {
					throw std::invalid_argument("The DOR looks invalid.");
				}
			}
			getRepository()->addRelationship(this, targetObj);
		}

		/**
		 * Gets an Hdf Proxy from a EML 2.0 dataset.
		 *
		 * @exception	std::invalid_argument	If <tt>throwException == true</tt> and the HDF proxy is
		 * 										missing.
		 *
		 * @param 	dataset		  	The dataset.
		 * @param 	throwException	(Optional) True to throw exception.
		 *
		 * @returns	Null if it fails, else the HDF proxy from dataset.
		 */
		EML2_NS::AbstractHdfProxy* getHdfProxyFromDataset(gsoap_resqml2_0_1::eml20__Hdf5Dataset const * dataset, bool throwException = true) const;

		/**
		 * Gets an Hdf Proxy from a EML 2.2 dataset.
		 *
		 * @exception	std::invalid_argument	If <tt>throwException == true</tt> and the HDF proxy is
		 * 										missing.
		 *
		 * @param 	dataset		  	The dataset.
		 * @param 	throwException	(Optional) True to throw exception.
		 *
		 * @returns	Null if it fails, else the HDF proxy from dataset.
		 */
		EML2_NS::AbstractHdfProxy* getHdfProxyFromDataset(gsoap_eml2_3::eml23__ExternalDatasetPart const * dataset, bool throwException = true) const;

		/**
		* @return the HDF group where to write the numerical values associated to this object.
		*/
		std::string getHdfGroup() const {
			return "/" + getXmlNamespace() + "/" + getUuid();
		}

		gsoap_resqml2_0_1::resqml20__IndexableElements mapIndexableElement(gsoap_eml2_3::resqml22__IndexableElement toMap) const;

	public:

		enum hdfDatatypeEnum { UNKNOWN = 0, DOUBLE = 1, FLOAT = 2, LONG_64 = 3, ULONG_64 = 4, INT = 5, UINT = 6, SHORT = 7, USHORT = 8, CHAR = 9, UCHAR = 10};

		virtual ~AbstractObject() = default;

		/**
		 * Indicates if this data object is actually a partial object. A partial object just contains a mime
		 * type, an UUID and a title as a minimum amount of information. A partial object is never
		 * explicit in an EPC document: it is not a file
		 *
		 * @returns	True if is partial, false if is not.
		 */
		DLL_IMPORT_OR_EXPORT bool isPartial() const;

		DLL_IMPORT_OR_EXPORT virtual bool isTopLevelElement() const { return true; }

		/**
		 * Gets the UUID (https://tools.ietf.org/html/rfc4122#page-3) of this data object. The UUID
		 * intends to give an id to the \"thing\" (i.e. the business object), not to this instance
		 *
		 * @exception	std::invalid_argument	If no available gSOAP proxy instance is associated to
		 * 										this data object.
		 *
		 * @returns	The UUID of this data object.
		 */
		DLL_IMPORT_OR_EXPORT std::string getUuid() const;

		/**
		 * Gets the title (i.e. the name) of this data object. This is the equivalent of
		 * @c CI_Citation.title in ISO 19115
		 *
		 * @exception	std::invalid_argument	If no available gSOAP proxy instance is associated to
		 * 										this data object.
		 *
		 * @returns	The title of this data object.
		 */
		DLL_IMPORT_OR_EXPORT std::string getTitle() const;

		/**
		 * Gets the name (or other human-readable identifier) of the last person who updated the object.
		 * In ISO 19115, this is equivalent to the @c CI_Individual.name or the @c CI_Organization.name of
		 * the @c citedResponsibleParty whose role is @c editor
		 *
		 * @exception	std::invalid_argument	If this instance is actually a partial object.
		 *
		 * @returns	The editor of this data object if it is defined, else empty string.
		 */
		DLL_IMPORT_OR_EXPORT std::string getEditor() const;

		/**
		 * Gets the date and time the data object was created in the source application or, if that
		 * information is not available, when it was saved to the file. This is the equivalent of the
		 * ISO 19115 @c CI_Date where the @c CI_DateTypeCode is @c creation
		 *
		 * @exception	std::invalid_argument	If this instance is actually a partial object or if no
		 * 										available gSOAP proxy instance is associated to this data
		 * 										object.
		 *
		 * @returns	The creation date and time of the data object.
		 */
		DLL_IMPORT_OR_EXPORT time_t getCreation() const;

		/**
		 * Same as {@link getCreation()}. Please use this method if you want to read some dates out of
		 * the range of @c time_t
		 *
		 * @exception	std::invalid_argument	If this instance is actually a partial object or if no
		 * 										available gSOAP proxy instance is associated to this data
		 * 										object.
		 *
		 * @returns	The creation date and time of the data object.
		 */
		DLL_IMPORT_OR_EXPORT tm getCreationAsTimeStructure() const;

		/**
		 * Gets the name (or other human-readable identifier) of the person who initially originated
		 * this data object or document in the source application. If that information is not available,
		 * then this is the user of the session during the file creation. The originator remains the
		 * same as the object is subsequently edited. This is the equivalent in ISO 19115 to the @c
		 * CI_Individual.name or the @c CI_Organization.name of the @c citedResponsibleParty whose role
		 * is @c originator
		 *
		 * @exception	std::invalid_argument	If this instance is actually a partial object or if no
		 * 										available gSOAP proxy instance is associated to this data
		 * 										object.
		 *
		 * @returns	The originator name or identifier.
		 */
		DLL_IMPORT_OR_EXPORT std::string getOriginator() const;

		/**
		 * Gets the user descriptive comments about this data object. Intended for end-user use (human
		 * readable); not necessarily meant to be used by software. This is the equivalent of the ISO
		 * 19115 @c abstract.CharacterString
		 *
		 * @exception	std::invalid_argument	If this instance is actually a partial object.
		 *
		 * @returns	The description of this data object if it is defined, else empty string.
		 */
		DLL_IMPORT_OR_EXPORT std::string getDescription() const;

		/**
		 * Gets the date and time the data object was last modified in the source application or, if
		 * that information is not available, when it was last saved to the file. This is the equivalent
		 * of the ISO 19115 @c CI_Date where the @c CI_DateTypeCode is @c lastUpdate
		 *
		 * @exception	std::invalid_argument	If this instance is actually a partial object.
		 *
		 * @returns	The last update date and time of the data object.
		 */
		DLL_IMPORT_OR_EXPORT time_t getLastUpdate() const;

		/**
		 * Same as {@link getLastUpdate()}. Please use this method if you want to read some dates out of
		 * the range of @c time_t
		 *
		 * @exception	std::invalid_argument	If this instance is actually a partial object.
		 *
		 * @returns	The last update date and time of the data object.
		 */
		DLL_IMPORT_OR_EXPORT tm getLastUpdateAsTimeStructure() const;

		/**
		 * Gets the identifier of the software or service that was used to originate the data object and
		 * to create the file. Must be human and machine readable and unambiguously identify the
		 * software by including the company name, software name and software version. This is the
		 * equivalent in ISO 19115 to the @c istributionFormat.MD_Format. The ISO format for this is
		 * <tt> [vendor:applicationName]/fileExtension </tt> where the application name includes the
		 * version number of the application. In our case, @c fileExtension is not relevant and will be
		 * ignored if present. @c vendor and @c applicationName are mandatory
		 *
		 * @exception	std::invalid_argument	If this instance is actually a partial object or if no
		 * 										available gSOAP proxy instance is associated to this data
		 * 										object.
		 *
		 * @returns	The identifier of the software or service that was used to originate the data object
		 * 			and to create the file.
		 */
		DLL_IMPORT_OR_EXPORT std::string getFormat() const;

		/**
		 * Gets the key words to describe the activity, for example, history match or volumetric
		 * calculations, relevant to this data object. Intended to be used in a search function by
		 * software. This is the equivalent in ISO 19115 of @c descriptiveKeywords.MD_Keywords
		 *
		 * @exception	std::invalid_argument	If this instance is actually a partial object.
		 *
		 * @returns	The key words to describe the activity relevant to this data object if they are
		 * 			defined, else empty string.
		 */
		DLL_IMPORT_OR_EXPORT std::string getDescriptiveKeywords() const;

		/**
		 * Gets the version of this data object. An empty version indicates that this is the latest (and
		 * ideally also the unique) version of this data object.
		 *
		 * @returns	The version of this object, empty string means latest version.
		 */
		DLL_IMPORT_OR_EXPORT std::string getVersion() const;

		/**
		 * Sets the title (i.e. the name) of this data object. This is the equivalent of
		 * @c CI_Citation.title in ISO 19115
		 *
		 * @exception	std::invalid_argument	If this instance is actually a partial object.
		 * @exception	std::range_error	 	If @p title is more than 256 chars long.
		 *
		 * @param 	title	The title to set to this data object. If empty then \"unknown\" title will be
		 * 					set.
		 */
		DLL_IMPORT_OR_EXPORT void setTitle(const std::string & title);

		/**
		 * Sets the name (or other human-readable identifier) of the last person who updated the object.
		 * In ISO 19115, this is equivalent to the @c CI_Individual.name or the @c CI_Organization.name
		 * of the @c citedResponsibleParty whose role is @c editor
		 *
		 * @exception	std::invalid_argument	If this instance is actually a partial object.
		 * @exception	std::range_error	 	If @p editor is more than 64 chars long.
		 *
		 * @param 	editor	The editor to set to this data object. 
		 */
		DLL_IMPORT_OR_EXPORT void setEditor(const std::string & editor);

		/**
		 * Sets the date and time the data object was created in the source application or, if that
		 * information is not available, when it was saved to the file. This is the equivalent of the
		 * ISO 19115 @c CI_Date where the @c CI_DateTypeCode is @c creation
		 *
		 * @exception	std::invalid_argument	If this instance is actually a partial object.
		 *
		 * @param 	creation	The creation date and time to set to this data object.
		 */
		DLL_IMPORT_OR_EXPORT void setCreation(time_t creation);

		/**
		 * Same as {@link setCreation()}. Please use this method if you want to set some dates out of
		 * the range of @c time_t
		 *
		 * @exception	std::invalid_argument	If this instance is actually a partial object.
		 *
		 * @param 	creation	The creation date and time to set to this data object.
		 */
		DLL_IMPORT_OR_EXPORT void setCreation(const tm & creation);

		/**
		 * Sets the name (or other human-readable identifier) of the person who initially originated
		 * this data object or document in the source application. If that information is not available,
		 * then this is the user of the session during the file creation. The originator remains the
		 * same as the object is subsequently edited. This is the equivalent in ISO 19115 to the @c
		 * CI_Individual.name or the @c CI_Organization.name of the @c citedResponsibleParty whose role
		 * is @c originator
		 *
		 * @exception	std::invalid_argument	If this instance is actually a partial object.
		 * @exception	std::range_error	 	If @p originator is more than 64 chars long.
		 *
		 * @param 	originator	The originator name or identifier to set to this data object. If empty,
		 * 						the user id is set if available, \"unknown\" if it is not.
		 */
		DLL_IMPORT_OR_EXPORT void setOriginator(const std::string & originator);

		/**
		 * Sets a user descriptive comments about this data object. Intended for end-user use (human
		 * readable); not necessarily meant to be used by software. This is the equivalent of the ISO
		 * 19115 @c abstract.CharacterString
		 *
		 * @exception	std::invalid_argument	If this instance is actually a partial object.
		 * @exception	std::range_error	 	If @p description is too long (more than 4000 chars for
		 * 										RESQML2.0 or more than 2000 chars for EML2.1 and EML2.2).
		 *
		 * @param 	description	The description to set to this data object.
		 */
		DLL_IMPORT_OR_EXPORT void setDescription(const std::string & description);

		/**
		 * Sets the date and time the data object was last modified in the source application or, if
		 * that information is not available, when it was last saved to the file. This is the equivalent
		 * of the ISO 19115 @c CI_Date where the @c CI_DateTypeCode is @c lastUpdate
		 *
		 * @exception	std::invalid_argument	If this instance is actually a partial object.
		 *
		 * @param 	lastUpdate	The last update date and time to set to this data object.
		 */
		DLL_IMPORT_OR_EXPORT void setLastUpdate(time_t lastUpdate);

		/**
		 * Same as {@link setLastUpdate()}. Please use this method if you want to read some dates out of
		 * the range of @c time_t
		 *
		 * @param 	lastUpdate	The last update date and time to set to this data object.
		 */
		DLL_IMPORT_OR_EXPORT void setLastUpdate(const tm & lastUpdate);

		/**
		 * Sets the default citation format which is going to be written in each created object. A
		 * maximum of 256 chars is allowed.
		 *
		 * @exception	std::range_error	If the format is more than 256 chars long.
		 *
		 * @param 	vendor						The name of the vendor which is exporting the data
		 * 										objects.
		 * @param 	applicationName				The name of the application which is exporting the data
		 * 										objects.
		 * @param 	applicationVersionNumber	The version of the application which is exporting the
		 * 										data objects.
		 */
		DLL_IMPORT_OR_EXPORT static void setFormat(const std::string & vendor, const std::string & applicationName, const std::string & applicationVersionNumber);

		/**
		 * Set the key words to describe the activity, for example, history match or volumetric
		 * calculations, relevant to this object. Intended to be used in a search function by software.
		 * This is the equivalent in ISO 19115 of descriptiveKeywords.MD_Keywords
		 *
		 * @exception	std::invalid_argument	If this instance is actually a partial object.
		 * @exception	std::range_error	 	If @p descriptiveKeywords is too long (more than 4000 chars for
		 * 										RESQML2.0 or more than 2000 chars for EML2.1 and EML2.2).
		 *
		 * @param 	descriptiveKeywords	The key words to describe the activity relevant to this data
		 * 								object.
		 */
		DLL_IMPORT_OR_EXPORT void setDescriptiveKeywords(const std::string & descriptiveKeywords);

		/**
		 * Set the version of this data object
		 *
		 * @exception	std::invalid_argument	If @p version is empty.
		 * @exception	std::range_error	 	If @p version is more than 64 chars long.
		 *
		 * @param 	version	The version to set to this data object.
		 */
		DLL_IMPORT_OR_EXPORT void setVersion(const std::string & version);

		/**
		 * Sets a title and other common metadata for this instance.
		 *
		 * @exception	std::invalid_argument	If this instance is actually a partial object.
		 * @exception	std::range_error	 	If @p title is more than 256 chars long.
		 * @exception	std::range_error	 	If @p editor title is more than 64 chars long.
		 * @exception	std::range_error	 	If @p originator title is more than 64 chars long.
		 * @exception	std::range_error	 	If @p description is too long (more than 4000 chars for
		 * 										RESQML2.0 or more than 2000 chars for EML2.1 and EML2.2).
		 * @exception	std::range_error	 	If @p descriptiveKeywords is too long (more than 4000
		 * 										chars for RESQML2.0 or more than 2000 chars for EML2.1
		 * 										and EML2.2).
		 *
		 * @param 	title			   	The title to set to this instance. If empty then \"unknown\"
		 * 								title will be set.
		 * @param 	editor			   	The editor to set to this instance. Set to empty string or zero
		 * 								if you don't want to use.
		 * @param 	creation		   	The creation date and time to set to this instance.
		 * @param 	originator		   	The originator name or identifier to set to this instance. If
		 * 								empty, the user id is set if available, \"unknown\" if it is not.
		 * @param 	description		   	The description to set to this instance. Set to empty string or
		 * 								zero if you don't want to use.
		 * @param 	lastUpdate		   	The last update date and time to set to this data object.
		 * @param 	descriptiveKeywords	The key words to describe the activity relevant to this data
		 * 								object. Set to empty string or zero if you don't want to use.
		 */
		DLL_IMPORT_OR_EXPORT void setMetadata(const std::string & title, const std::string & editor, time_t creation, const std::string & originator,
			const std::string & description, time_t lastUpdate, const std::string & descriptiveKeywords);

		/**
		 * Serializes this instance into a stream
		 *
		 * @exception	std::invalid_argument	If this instance is actually a partial object or if @p
		 * 										stream is null.
		 *
		 * @param [out]	stream	A stream. It must be opened for writing and won't be closed.
		 */
		DLL_IMPORT_OR_EXPORT void serializeIntoStream(std::ostream * stream);

		/**
		 * Sets the underlying RESQML2.0 gSOAP proxy of this data object
		 *
		 * @param [in]	gsoapProxy	If non-null, the gSOAP proxy.
		 */
		void setGsoapProxy(gsoap_resqml2_0_1::eml20__AbstractCitedDataObject* gsoapProxy) { gsoapProxy2_0_1 = gsoapProxy; }

		void setGsoapProxy(gsoap_eml2_1::eml21__AbstractObject* gsoapProxy) { gsoapProxy2_1 = gsoapProxy; }

		/**
		 * Get the EML2.0 gSOAP proxy which is wrapped by this entity
		 *
		 * @returns	A pointer to the EML2.0 gSOAP proxy.
		 */
		gsoap_resqml2_0_1::eml20__AbstractCitedDataObject* getEml20GsoapProxy() const { return gsoapProxy2_0_1; }

		/**
		 * Get the EML2.1 gSOAP proxy which is wrapped by this entity
		 *
		 * @returns	A pointer to the EML2.1 gSOAP proxy.
		 */
		gsoap_eml2_1::eml21__AbstractObject* getEml21GsoapProxy() const { return gsoapProxy2_1; }

		gsoap_eml2_2::eml22__AbstractObject* getEml22GsoapProxy() const { return gsoapProxy2_2; }
		void setGsoapProxy(gsoap_eml2_2::eml22__AbstractObject* gsoapProxy) { gsoapProxy2_2 = gsoapProxy; }

		/**
		 * Get the EML2.3 gSOAP proxy which is wrapped by this entity
		 *
		 * @returns	A pointer to the EML2.3 gSOAP proxy.
		 */
		gsoap_eml2_3::eml23__AbstractObject* getEml23GsoapProxy() const { return gsoapProxy2_3; }
		void setGsoapProxy(gsoap_eml2_3::eml23__AbstractObject* gsoapProxy) { gsoapProxy2_3 = gsoapProxy; }

		/**
		 * Get the gSOAP context where the underlying gSOAP proxy is defined
		 *
		 * @returns	A pointer to the gSOAP context.
		 */
		soap* getGsoapContext() const;

		/**
		 * Gets the gSOAP type of the wrapped element
		 *
		 * @exception	std::invalid_argument	It there is no available gSOAP proxy instance.
		 *
		 * @returns	The gSOAP type.
		 */
		int getGsoapType() const;

		/**
		 * Creates an returns an EML2.0 data object reference which targets this data object
		 *
		 * @returns	A pointer to the new EML2.0 data object reference.
		 */
		gsoap_resqml2_0_1::eml20__DataObjectReference* newResqmlReference() const;

		/**
		 * Creates an returns an EML2.1 data object reference which targets this data object
		 *
		 * @returns	A pointer to the new EML2.1 data object reference.
		 */
		gsoap_eml2_1::eml21__DataObjectReference* newEmlReference() const;

		/**
		 * Creates an returns an EML2.2 data object reference which targets this data object
		 *
		 * @returns	A pointer to the new EML2.2 data object reference.
		 */
		gsoap_eml2_2::eml22__DataObjectReference* newEml22Reference() const;

		/**
		 * Creates an returns an EML2.2 data object reference which targets this data object
		 *
		 * @returns	A pointer to the new EML2.2 data object reference.
		 */
		gsoap_eml2_3::eml23__DataObjectReference* newEml23Reference() const;

		/**
		 * Creates an returns an EML2.0 contact data object reference which targets this data object
		 *
		 * @returns	A pointer to the new EML2.0 contact data object reference.
		 */
		gsoap_resqml2_0_1::resqml20__ContactElementReference* newContactElementReference2_0_1() const;

		/**
		 * Creates an returns an EML2.2 contact data object reference which targets this data object
		 *
		 * @returns	A pointer to the new EML2.2 contact data object reference.
		 */
		gsoap_eml2_3::resqml22__ContactElement* newContactElementReference2_2() const;

		/**
		 * Returns the data object repository which contains this instance
		 * 
		 * @returns A pointer to the data object repository.
		 */
		DLL_IMPORT_OR_EXPORT COMMON_NS::DataObjectRepository* getRepository() const {return repository;}

		/**
		* Gets the XML namespace for the tags for the XML serialization of this instance
		*
		* @returns	The XML namespace of this instance.
		*/
		DLL_IMPORT_OR_EXPORT virtual std::string getXmlNamespace() const = 0;

		/**
		 * Gets the standard XML tag without XML namespace for serializing this data object.
		 *
		 * @returns	The XML tag.
		 */
		DLL_IMPORT_OR_EXPORT virtual std::string getXmlTag() const = 0;

		/**
		 * Gets the version of the XML namespace (i.e. WITSML, RESQML, PRODML) for the XML serialization
		 * of this instance
		 *
		 * @returns	The XML namespace version of this instance.
		 */
		DLL_IMPORT_OR_EXPORT virtual std::string getXmlNamespaceVersion() const;

		/**
		 * Gets the content type of this instance according to EPC recommendation
		 *
		 * @returns	The content type of this instance.
		 */
		DLL_IMPORT_OR_EXPORT virtual std::string getContentType() const;

		/**
		 * Get the qualified type of the instance i.e. "namespace.datatype"
		 *
		 * @returns	The qualified type of the instance i.e. "namespace.datatype"
		 */
		DLL_IMPORT_OR_EXPORT virtual std::string getQualifiedType() const;
		
		/**
		 * Gets the part name of this XML top level instance in the EPC document
		 *
		 * @returns	The part name of this instance.
		 */
		DLL_IMPORT_OR_EXPORT virtual std::string getPartNameInEpcDocument() const;

		/**
		 * Serializes the gSOAP proxy of this instance into a string
		 *
		 * @returns	The string result of the serialization process.
		 */
		DLL_IMPORT_OR_EXPORT std::string serializeIntoString();

		/**
		 * Adds an alias for this data object
		 *
		 * @exception	std::invalid_argument	If this instance is actually a partial object.
		 * @exception	std::range_error	 	If @p authority or @p title is more than 64 chars long.
		 *
		 * @param 	authority	The authority of the alias.
		 * @param 	title	 	The title of the alias.
		 */
		DLL_IMPORT_OR_EXPORT void addAlias(const std::string & authority, const std::string & title);

		/**
		 * Gets the count of aliases in this instance
		 *
		 * @exception	std::invalid_argument	If this instance is actually a partial object.
		 * @exception	std::range_error	 	If the count of aliases is strictly greater than unsigned
		 * 										int max.
		 *
		 * @returns	The alias count of this instance.
		 */
		DLL_IMPORT_OR_EXPORT unsigned int getAliasCount() const;

		/**
		 * Gets the alias authority at a particular index in the aliases set
		 *
		 * @exception	std::invalid_argument	If this instance is actually a partial object or if there
		 * 										is no underlying gSOAP proxy.
		 * @exception	std::out_of_range	 	If @p index is out of range.
		 *
		 * @param 	index	Zero-based index of the asked alias authority.
		 *
		 * @returns	The alias authority at @p index.
		 */
		DLL_IMPORT_OR_EXPORT std::string getAliasAuthorityAtIndex(unsigned int index) const;

		/**
		 * Gets the alias title at a particular index in the aliases set
		 *
		 * @exception	std::invalid_argument	If this instance is actually a partial object or if there
		 * 										is no underlying gSOAP proxy.
		 * @exception	std::out_of_range	 	If @p index is out of range.
		 *
		 * @param 	index	Zero-based index of the asked alias title.
		 *
		 * @returns	The alias title at @p index.
		 */
		DLL_IMPORT_OR_EXPORT std::string getAliasTitleAtIndex(unsigned int index) const;

		/**
		 * Gets all the activities where this instance is involved
		 *
		 * @returns	The vector of all activities involving this instance.
		 */
		DLL_IMPORT_OR_EXPORT std::vector<EML2_NS::Activity*> getActivitySet() const;

		/**
		 * Gets the count of the activities where this instance is involved
		 *
		 * @exception	std::out_of_range	If the count of activities is strictly greater than unsigned
		 * 									int max.
		 *
		 * @returns	The count of all activities involving this instance.
		 */
		DLL_IMPORT_OR_EXPORT unsigned int getActivityCount() const;

		/**
		 * Gets an associated activity at a particular index
		 *
		 * @exception	std::invalid_argument	If this instance is actually a partial object or if there
		 * 										is no underlying gSOAP proxy.
		 * @exception	std::out_of_range	 	If @p index is out of range.
		 *
		 * @param 	index	Zero-based index of the asked activity.
		 *
		 * @returns	The associated activity at @p index.
		 */
		DLL_IMPORT_OR_EXPORT EML2_NS::Activity* getActivity(unsigned int index) const;

		/**
		 * Pushes back an extra metadata (not a standard one) onto this instance
		 *
		 * @exception	std::logic_error	If the underlying gSOAP instance is not a RESQML2.0, EML2.1 or EML2.2 one.
		 *
		 * @param 	key  	The key of the metadata.
		 * @param 	value	The value of the metadata.
		 */
		DLL_IMPORT_OR_EXPORT void pushBackExtraMetadata(const std::string & key, const std::string & value);

		/**
		 * Gets all the extra metadata of this instance in read only mode
		 *
		 * @exception	std::logic_error	If the underlying gSOAP instance is not a RESQML2.0 one.
		 *
		 * @returns	A map associated the keys and values of all extra metadata.
		 */
		DLL_IMPORT_OR_EXPORT std::unordered_map< std::string, std::string > getExtraMetadataSet() const;

		/**
		 * Gets an extra metadata of this instance according to its key
		 *
		 * @exception	std::logic_error	If the underlying gSOAP instance is not a RESQML2.0 one.
		 *
		 * @param 	key	The key of an extra metadata.
		 *
		 * @returns	The vector of all metadata values sharing this @p key (empty vector if there is no such value).
		 */
		DLL_IMPORT_OR_EXPORT std::vector<std::string> getExtraMetadata(const std::string & key) const;

		/**
		 * Get the count of extra metadata in this instance
		 *
		 * @exception	std::logic_error	If the underlying gSOAP instance is not a RESQML2.0 or EML2.2 one.
		 *
		 * @returns	The extra metadata count of this instance.
		 */
		DLL_IMPORT_OR_EXPORT unsigned int getExtraMetadataCount() const;

		/**
		 * Get the key of a key value pair at a particular index in the extra metadata set of this
		 * instance
		 *
		 * @exception	std::logic_error	If the underlying gSOAP instance is not a RESQML2.0 or EML2.2 one.
		 *
		 * @param 	index	Zero-based index of the asked key.
		 *
		 * @returns	The extra metadata key at @p index.
		 */
		DLL_IMPORT_OR_EXPORT std::string getExtraMetadataKeyAtIndex(unsigned int index) const;

		/**
		 * Get the value of a key value pair at a particular index in the extra metadata set of this
		 * instance
		 *
		 * @exception	std::logic_error	If the underlying gSOAP instance is not a RESQML2.0 or EML2.2 one.
		 *
		 * @param 	index	Zero-based index of the asked value.
		 *
		 * @returns	The extra metadata value at @p index.
		 */
		DLL_IMPORT_OR_EXPORT std::string getExtraMetadataStringValueAtIndex(unsigned int index) const;
		
		/**
		 * Reads the forward relationships of this data object and update the <tt>.rels</tt> of the
		 * associated data repository.
		 */
		virtual void loadTargetRelationships() = 0;
	};
}
