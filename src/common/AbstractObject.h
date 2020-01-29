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

#include <stdexcept>

#include "DataObjectRepository.h"

/** . */
namespace COMMON_NS
{
	/** An abstract object. */
	class AbstractObject
	{
	private:
		/** Should be instantiate in case a the object is (or was) a partial object. */
		gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject;

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

		/**
		 * Push back an extra metadata (not a standard one)
		 *
		 * @param 	key  	The key.
		 * @param 	value	The value.
		 */
		void pushBackExtraMetadataV2_0_1(const std::string & key, const std::string & value);

		/**
		 * Pushes a back extra metadata v 2 1
		 *
		 * @param 	key  	The key.
		 * @param 	value	The value.
		 */
		void pushBackExtraMetadataV2_1(const std::string & key, const std::string & value);

		/**
		 * Pushes a back extra metadata v 2
		 *
		 * @param 	key  	The key.
		 * @param 	value	The value.
		 */
		void pushBackExtraMetadataV2_2(const std::string & key, const std::string & value);

		/**
		 * Getter (in read only mode) of all the extra metadata
		 *
		 * @returns	The extra metadata set v 2 0 1.
		 */
		std::unordered_map< std::string, std::string > getExtraMetadataSetV2_0_1() const;

		/**
		 * Get an extra metadata according its key.
		 *
		 * @param 	key	The key.
		 *
		 * @returns	An empty vector if the extra metadata does not exist. Or the extra metadata value
		 * 			vector if it exists.
		 */
		std::vector<std::string> getExtraMetadataV2_0_1(const std::string & key) const;

		/**
		 * Get the count of extra metadata in the instance.
		 *
		 * @returns	The extra metadata count v 2 0 1.
		 */
		unsigned int getExtraMetadataCountV2_0_1() const;

		/**
		 * Get the key of a string value pair at a particular index in the extra metadata set
		 *
		 * @param 	index	Zero-based index of the.
		 *
		 * @returns	The extra metadata key at index v 2 0 1.
		 */
		std::string getExtraMetadataKeyAtIndexV2_0_1(unsigned int index) const;

		/**
		 * Get the string value of a string value pair at a particular index in the extra metadata set
		 *
		 * @param 	index	Zero-based index of the.
		 *
		 * @returns	The extra metadata string value at index v 2 0 1.
		 */
		std::string getExtraMetadataStringValueAtIndexV2_0_1(unsigned int index) const;

		/**
		 * Get the count of extra metadata in the instance.
		 *
		 * @returns	The extra metadata count v 2.
		 */
		unsigned int getExtraMetadataCountV2_2() const;

		/**
		 * Get the key of a string value pair at a particular index in the extra metadata set
		 *
		 * @param 	index	Zero-based index of the.
		 *
		 * @returns	The extra metadata key at index v 2.
		 */
		std::string getExtraMetadataKeyAtIndexV2_2(unsigned int index) const;

		/**
		 * Get the string value of a string value pair at a particular index in the extra metadata set
		 *
		 * @param 	index	Zero-based index of the.
		 *
		 * @returns	The extra metadata string value at index v 2.
		 */
		std::string getExtraMetadataStringValueAtIndexV2_2(unsigned int index) const;

	protected:

		/** Enumeration for the various EML versions. */
		enum EmlVersion {
			TWO_DOT_ZERO = 0,
			TWO_DOT_ONE = 1,
			TWO_DOT_TWO = 2
		};

		/** The underlying generated gSoap proxy for a EML 2.0 dataobject. */
		gsoap_resqml2_0_1::eml20__AbstractCitedDataObject* gsoapProxy2_0_1;

		/** The underlying generated gSoap proxy for a EML 2.1 dataobject. */
		gsoap_eml2_1::eml21__AbstractObject* gsoapProxy2_1;

		/** The underlying generated gSoap proxy for a EML 2.2 dataobject. */
		gsoap_eml2_2::eml22__AbstractObject* gsoapProxy2_2;

		/** The repository which contain this data object. */
		COMMON_NS::DataObjectRepository* repository;

		/** Default constructor */
		AbstractObject();

		/**
		 * Constructor for partial transfer
		 *
		 * @param [in,out]	partialObject_	If non-null, the partial object.
		 */
		AbstractObject(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject_);

		/**
		 * Constructor when importing EML 2.0 (i.e RESQML2.0.1) dataobjects
		 *
		 * @param [in,out]	proxy	If non-null, the proxy.
		 */
		AbstractObject(gsoap_resqml2_0_1::eml20__AbstractCitedDataObject* proxy);

		/**
		 * Constructor when importing EML 2.1 dataobjects
		 *
		 * @param [in,out]	proxy	If non-null, the proxy.
		 */
		AbstractObject(gsoap_eml2_1::eml21__AbstractObject* proxy);

		/**
		 * Constructor when importing EML 2.1 dataobjects
		 *
		 * @param [in,out]	proxy	If non-null, the proxy.
		 */
		AbstractObject(gsoap_eml2_2::eml22__AbstractObject* proxy);

		/**
		 * Adds an or replace data object
		 *
		 * @param [in,out]	proxy	If non-null, the proxy.
		 */
		friend void COMMON_NS::DataObjectRepository::addOrReplaceDataObject(AbstractObject* proxy);

		/**
		 * Initialize all mandatory attributes of an AbstractObject (not the attributes of a
		 * specialization) with some valid values.
		 */
		void initMandatoryMetadata();

		/**
		 * Read the forward relationships of this dataobject and update the rels of the associated
		 * datarepository.
		 */
		virtual void loadTargetRelationships() = 0;
		/** Updates all relationships */
		friend void COMMON_NS::DataObjectRepository::updateAllRelationships();

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
		 * Read an input array which come from XML (and potentially HDF5) and store it into a
		 * preallocated output array in memory. It does not allocate or deallocate memory.
		 *
		 * @param [in,out]	arrayInput 	If non-null, the array input.
		 * @param [in,out]	arrayOutput	If non-null, the array output.
		 */
		void readArrayNdOfDoubleValues(gsoap_resqml2_0_1::resqml20__AbstractDoubleArray * arrayInput, double * arrayOutput) const;

		/**
		 * Read an input array which come from XML (and potentially HDF5) and store it into a
		 * preallocated output array in memory. It does not allocate or deallocate memory.
		 *
		 * @param [in,out]	arrayInput 	If non-null, the array input.
		 * @param [in,out]	arrayOutput	If non-null, the array output.
		 */
		void readArrayNdOfUIntValues(gsoap_resqml2_0_1::resqml20__AbstractIntegerArray * arrayInput, unsigned int * arrayOutput) const;

		/**
		 * Get the count of item in an array of integer
		 *
		 * @param [in,out]	arrayInput	The array of integer.
		 *
		 * @returns	The count of item in the array of integer.
		 */
		ULONG64 getCountOfIntegerArray(gsoap_resqml2_0_1::resqml20__AbstractIntegerArray * arrayInput) const;

		/**
		 * Convert a EML 2.0 Data Object Reference into a DataObjectRepository relationship.
		 *
		 * @param 	dor	The dor.
		 */
		void convertDorIntoRel(gsoap_resqml2_0_1::eml20__DataObjectReference const * dor);

		/**
		 * Convert a EML 2.2 Data Object Reference into a DataObjectRepository relationship.
		 *
		 * @param 	dor	The dor.
		 */
		void convertDorIntoRel(gsoap_eml2_2::eml22__DataObjectReference const * dor);

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
		void convertDorIntoRel(gsoap_resqml2_0_1::eml20__DataObjectReference const * dor)
		{
			valueType * targetObj = getRepository()->getDataObjectByUuid<valueType>(dor->UUID);
			if (targetObj == nullptr) { // partial transfer
				getRepository()->createPartial(dor);
				targetObj = getRepository()->getDataObjectByUuid<valueType>(dor->UUID);
				if (targetObj == nullptr) {
					throw std::invalid_argument("The DOR looks invalid.");
				}
			}
			getRepository()->addRelationship(this, targetObj);
		}

		/**
		 * Same as convertDorIntoRel(gsoap_eml2_1::eml21__DataObjectReference const * dor). Also check
		 * that the content type of the DOR is OK with the target datatype in memory.
		 *
		 * @exception	std::invalid_argument	Thrown when an invalid argument error condition occurs.
		 *
		 * @tparam	valueType	Type of the value type.
		 * @param 	dor	The dor.
		 */
		template <class valueType>
		void convertDorIntoRel(gsoap_eml2_1::eml21__DataObjectReference const * dor)
		{
			valueType * targetObj = getRepository()->getDataObjectByUuid<valueType>(dor->Uuid);
			if (targetObj == nullptr) { // partial transfer
				getRepository()->createPartial(dor);
				targetObj = getRepository()->getDataObjectByUuid<valueType>(dor->Uuid);
				if (targetObj == nullptr) {
					throw std::invalid_argument("The DOR looks invalid.");
				}
			}
			getRepository()->addRelationship(this, targetObj);
		}

		/**
		 * Same as convertDorIntoRel(gsoap_eml2_2::eml22__DataObjectReference const * dor). Also check
		 * that the content type of the DOR is OK with the target datatype in memory.
		 *
		 * @exception	std::invalid_argument	Thrown when an invalid argument error condition occurs.
		 *
		 * @tparam	valueType	Type of the value type.
		 * @param 	dor	The dor.
		 */
		template <class valueType>
		void convertDorIntoRel(gsoap_eml2_2::eml22__DataObjectReference const * dor)
		{
			valueType * targetObj = getRepository()->getDataObjectByUuid<valueType>(dor->Uuid);
			if (targetObj == nullptr) { // partial transfer
				getRepository()->createPartial(dor);
				targetObj = getRepository()->getDataObjectByUuid<valueType>(dor->Uuid);
				if (targetObj == nullptr) {
					throw std::invalid_argument("The DOR looks invalid.");
				}
			}
			getRepository()->addRelationship(this, targetObj);
		}

		/**
		 * Get an Hdf Proxy from a EML 2.0 dataset.
		 *
		 * @param 	dataset		  	The dataset.
		 * @param 	throwException	(Optional) True to throw exception.
		 *
		 * @returns	Null if it fails, else the hdf proxy from dataset.
		 */
		COMMON_NS::AbstractHdfProxy* getHdfProxyFromDataset(gsoap_resqml2_0_1::eml20__Hdf5Dataset const * dataset, bool throwException = true) const;

	public:
		/** Destructor */
		virtual ~AbstractObject() {}

		/**
		 * Indicate if the instance is actually a partial object. A partial object just contains a mime
		 * type, an uuid and a title as a minimum amount of information. A partial object is never
		 * explicit in an EPC document : it is not a file.
		 *
		 * @returns	True if partial, false if not.
		 */
		DLL_IMPORT_OR_EXPORT bool isPartial() const {return partialObject != nullptr;}

		/**
		 * Get the UUID (https://tools.ietf.org/html/rfc4122#page-3) of the DataOject. The UUID intends
		 * to give an id to the thing (i.e. the business object), not to this instance.
		 *
		 * @returns	The uuid.
		 */
		DLL_IMPORT_OR_EXPORT std::string getUuid() const;

		/**
		 * Get the title (i.e. name) of the DataOject. This is the equivalent in ISO 19115 of
		 * CI_Citation.title
		 *
		 * @returns	The title.
		 */
		DLL_IMPORT_OR_EXPORT std::string getTitle() const;

		/**
		 * Get the name (or other human-readable identifier) of the last person who updated the object.
		 * This is the equivalent in ISO 19115 to the CI_Individual.name or the CI_Organization.name of
		 * the citedResponsibleParty whose role is "editor".
		 *
		 * @returns	The editor.
		 */
		DLL_IMPORT_OR_EXPORT std::string getEditor() const;

		/**
		 * Get the Date and time the document was created in the source application or, if that
		 * information is not available, when it was saved to the file. This is the equivalent of the
		 * ISO 19115 CI_Date where the CI_DateTypeCode = ”creation"
		 *
		 * @returns	The creation.
		 */
		DLL_IMPORT_OR_EXPORT time_t getCreation() const;

		/**
		 * Same as getCreation(). Use this method if you want to read some dates out of range of time_t
		 *
		 * @returns	The creation as time structure.
		 */
		DLL_IMPORT_OR_EXPORT tm getCreationAsTimeStructure() const;

		/**
		 * Get the name (or other human-readable identifier) of the person who initially originated the
		 * object or document in the source application. If that information is not available, then this
		 * is the user who created the format file. The originator remains the same as the object is
		 * subsequently edited. This is the equivalent in ISO 19115 to the CI_Individual.name or the
		 * CI_Organization.name of the citedResponsibleParty whose role is "originator".
		 *
		 * @returns	The originator.
		 */
		DLL_IMPORT_OR_EXPORT std::string getOriginator() const;

		/**
		 * Get the user descriptive comments about the object. Intended for end-user use (human
		 * readable); not necessarily meant to be used by software. This is the equivalent of the ISO
		 * 19115 abstract.CharacterString
		 *
		 * @returns	The description.
		 */
		DLL_IMPORT_OR_EXPORT std::string getDescription() const;

		/**
		 * Get the date and time the document was last modified in the source application or, if that
		 * information is not available, when it was last saved to the format file. This is the
		 * equivalent of the ISO 19115 CI_Date where the CI_DateTypeCode = ”lastUpdate"
		 *
		 * @returns	The last update.
		 */
		DLL_IMPORT_OR_EXPORT time_t getLastUpdate() const;

		/**
		 * Same as getLastUpdate()
		 * Use this method if you want to read some dates out of range of time_t
		 *
		 * @returns	The last update as time structure.
		 */
		DLL_IMPORT_OR_EXPORT tm getLastUpdateAsTimeStructure() const;

		/**
		 * Get the software or service that was used to originate the object and the file format
		 * created. Must be human and machine readable and unambiguously identify the software by
		 * including the company name, software name and software version. This is the equivalent in ISO
		 * 19115 to the distributionFormat.MD_Format. The ISO format for this is
		 * [vendor:applicationName]/fileExtension where the application name includes the version number
		 * of the application. In our case, FileExtension is not relevant and will be ignored if
		 * present. Vendor and applicationName are mandatory.
		 *
		 * @returns	The format.
		 */
		DLL_IMPORT_OR_EXPORT std::string getFormat() const;

		/**
		 * Get the key words to describe the activity, for example, history match or volumetric
		 * calculations, relevant to this object. Intended to be used in a search function by software.
		 * This is the equivalent in ISO 19115 of descriptiveKeywords.MD_Keywords
		 *
		 * @returns	The descriptive keywords.
		 */
		DLL_IMPORT_OR_EXPORT std::string getDescriptiveKeywords() const;

		/**
		 * Get the version of this data object. A returned empty version dataobject indicates that this
		 * is the latest (and ideally also the unique) version of this data object.
		 *
		 * @returns	The version.
		 */
		DLL_IMPORT_OR_EXPORT std::string getVersion() const;

		/**
		 * Set the title (i.e. name) of the DataOject. This is the equivalent in ISO 19115 of
		 * CI_Citation.title
		 *
		 * @param 	title	The title.
		 */
		DLL_IMPORT_OR_EXPORT void setTitle(const std::string & title);

		/**
		 * Set the name (or other human-readable identifier) of the last person who updated the object.
		 * This is the equivalent in ISO 19115 to the CI_Individual.name or the CI_Organization.name of
		 * the citedResponsibleParty whose role is "editor".
		 *
		 * @param 	editor	The editor.
		 */
		DLL_IMPORT_OR_EXPORT void setEditor(const std::string & editor);

		/**
		 * Get the Date and time the document was created in the source application or, if that
		 * information is not available, when it was saved to the file. This is the equivalent of the
		 * ISO 19115 CI_Date where the CI_DateTypeCode = ”creation"
		 *
		 * @param 	creation	The creation.
		 */
		DLL_IMPORT_OR_EXPORT void setCreation(time_t creation);

		/**
		 * Same as setCreation(time_t creation)
		 * Use this method if you want to set some dates out of range of time_t
		 *
		 * @param 	creation	The creation.
		 */
		DLL_IMPORT_OR_EXPORT void setCreation(const tm & creation);

		/**
		 * Set the name (or other human-readable identifier) of the person who initially originated the
		 * object or document in the source application. If that information is not available, then this
		 * is the user who created the format file. The originator remains the same as the object is
		 * subsequently edited. This is the equivalent in ISO 19115 to the CI_Individual.name or the
		 * CI_Organization.name of the citedResponsibleParty whose role is "originator".
		 *
		 * @param 	originator	The originator.
		 */
		DLL_IMPORT_OR_EXPORT void setOriginator(const std::string & originator);

		/**
		 * Set the user descriptive comments about the object. Intended for end-user use (human
		 * readable); not necessarily meant to be used by software. This is the equivalent of the ISO
		 * 19115 abstract.CharacterString
		 *
		 * @param 	description	The description.
		 */
		DLL_IMPORT_OR_EXPORT void setDescription(const std::string & description);

		/**
		 * Set the date and time the document was last modified in the source application or, if that
		 * information is not available, when it was last saved to the format file. This is the
		 * equivalent of the ISO 19115 CI_Date where the CI_DateTypeCode = ”lastUpdate"
		 *
		 * @param 	lastUpdate	The last update.
		 */
		DLL_IMPORT_OR_EXPORT void setLastUpdate(time_t lastUpdate);

		/**
		 * Same as setLastUpdate(time_t lastUpdate). Use this method if you want to set some dates out
		 * of range of time_t.
		 *
		 * @param 	lastUpdate	The last update.
		 */
		DLL_IMPORT_OR_EXPORT void setLastUpdate(const tm & lastUpdate);

		/**
		 * Set the default citation format which is going to be written in each created object. A
		 * maximum of 256 chars is allowed.
		 *
		 * @param 	vendor						The vendor name which is exporting the RESQML objects.
		 * @param 	applicationName				The application name which is exporting the RESQML
		 * 										objects.
		 * @param 	applicationVersionNumber	The application version number which is exporting the
		 * 										RESQML objects.
		 */
		DLL_IMPORT_OR_EXPORT static void setFormat(const std::string & vendor, const std::string & applicationName, const std::string & applicationVersionNumber);

		/**
		 * Set the key words to describe the activity, for example, history match or volumetric
		 * calculations, relevant to this object. Intended to be used in a search function by software.
		 * This is the equivalent in ISO 19115 of descriptiveKeywords.MD_Keywords
		 *
		 * @param 	descriptiveKeywords	The descriptive keywords.
		 */
		DLL_IMPORT_OR_EXPORT void setDescriptiveKeywords(const std::string & descriptiveKeywords);

		/**
		 * Set the version of this data object.
		 *
		 * @param 	version	Cannot be empty.
		 */
		DLL_IMPORT_OR_EXPORT void setVersion(const std::string & version);

		/**
		 * Set a title and other common metadata for the resqml instance. Set to empty string or zero if
		 * you don't want to use.
		 *
		 * @param 	title			   	The title to set to the resqml instance. Set to empty string if
		 * 								you don't want to set it.
		 * @param 	editor			   	The editor.
		 * @param 	creation		   	The creation.
		 * @param 	originator		   	The originator.
		 * @param 	description		   	The description.
		 * @param 	lastUpdate		   	The last update.
		 * @param 	descriptiveKeywords	The descriptive keywords.
		 */
		DLL_IMPORT_OR_EXPORT void setMetadata(const std::string & title, const std::string & editor, time_t creation, const std::string & originator,
			const std::string & description, time_t lastUpdate, const std::string & descriptiveKeywords);

		/**
		 * Serialize the instance into a stream.
		 *
		 * @param [in,out]	stream	The stream must be opened for writing and won't be closed.
		 */
		DLL_IMPORT_OR_EXPORT void serializeIntoStream(std::ostream * stream);

		/**
		 * Set the underlying gsoap proxy of this object
		 *
		 * @param [in,out]	gsoapProxy	If non-null, the gsoap proxy.
		 */
		void setGsoapProxy(gsoap_resqml2_0_1::eml20__AbstractCitedDataObject* gsoapProxy);

		/**
		 * Get the gsoap proxy which is wrapped by this entity
		 *
		 * @returns	Null if it fails, else the gsoap proxy.
		 */
		gsoap_resqml2_0_1::eml20__AbstractCitedDataObject* getGsoapProxy() const;

		/**
		 * Get the gsoap proxy which is wrapped by this entity
		 *
		 * @returns	Null if it fails, else the eml 21 gsoap proxy.
		 */
		gsoap_eml2_1::eml21__AbstractObject* getEml21GsoapProxy() const { return gsoapProxy2_1; }

		/**
		 * Get the gsoap context where the underlying gsoap proxy is defined.
		 *
		 * @returns	Null if it fails, else the gsoap context.
		 */
		soap* getGsoapContext() const;

		/**
		 * Get the Gsoap type of the wrapped element
		 *
		 * @returns	The gsoap type.
		 */
		int getGsoapType() const;

		/**
		 * Creates an returns an EML2.0 Data Object Reference which targets this dataobject.
		 *
		 * @returns	Null if it fails, else a pointer to a gsoap_resqml2_0_1::eml20__DataObjectReference.
		 */
		gsoap_resqml2_0_1::eml20__DataObjectReference* newResqmlReference() const;

		/**
		 * Creates an returns an EML2.1 Data Object Reference which targets this dataobject.
		 *
		 * @returns	Null if it fails, else a pointer to a gsoap_eml2_1::eml21__DataObjectReference.
		 */
		gsoap_eml2_1::eml21__DataObjectReference* newEmlReference() const;

		/**
		 * Creates an returns an EML2.2 Data Object Reference which targets this dataobject.
		 *
		 * @returns	Null if it fails, else a pointer to a gsoap_eml2_2::eml22__DataObjectReference.
		 */
		gsoap_eml2_2::eml22__DataObjectReference* newEml22Reference() const;

		/**
		 * Creates an returns an EML2.0 Contact Data Object Reference which targets this dataobject.
		 *
		 * @returns	Null if it fails, else a pointer to a
		 * 			gsoap_resqml2_0_1::resqml20__ContactElementReference.
		 */
		gsoap_resqml2_0_1::resqml20__ContactElementReference* newResqmlContactElementReference() const;

		/**
		 * Return the data object repository document which contains this gsoap wrapper.
		 *
		 * @returns	Null if it fails, else the repository.
		 */
		DLL_IMPORT_OR_EXPORT COMMON_NS::DataObjectRepository* getRepository() const {return repository;}

		/**
		 * Get the XML namespace for the tags for the XML serialization of this instance
		 *
		 * @returns	The XML namespace.
		 */
		virtual std::string getXmlNamespace() const;

		/**
		 * Get the XML tag for the XML serialization of this instance
		 *
		 * @returns	The XML tag.
		 */
		DLL_IMPORT_OR_EXPORT virtual std::string getXmlTag() const = 0;

		/**
		 * Get the version of the XML namespace (i.e. WITSML, RESQML, PRODML) for the XML serialization
		 * of this instance
		 *
		 * @returns	The XML namespace version.
		 */
		DLL_IMPORT_OR_EXPORT virtual std::string getXmlNamespaceVersion() const;

		/**
		 * Get the content type of the instance according to EPC recommendation
		 *
		 * @returns	The content type.
		 */
		DLL_IMPORT_OR_EXPORT virtual std::string getContentType() const;

		/**
		 * Get part name of this XML top level instance in the EPC document
		 *
		 * @returns	The part name in epc document.
		 */
		virtual std::string getPartNameInEpcDocument() const;

		/**
		 * Serialize the gsoap proxy into a string
		 *
		 * @returns	A std::string.
		 */
		DLL_IMPORT_OR_EXPORT std::string serializeIntoString();

		/**
		 * Add an alias for this object
		 *
		 * @param 	authority	The authority.
		 * @param 	title	 	The title.
		 */
		DLL_IMPORT_OR_EXPORT void addAlias(const std::string & authority, const std::string & title);

		/**
		 * Get the count of aliases in the instance.
		 *
		 * @returns	The alias count.
		 */
		DLL_IMPORT_OR_EXPORT unsigned int getAliasCount() const;

		/**
		 * Get the alias authority at a particular index in the aliases set.
		 *
		 * @param 	index	Zero-based index of the.
		 *
		 * @returns	The alias authority at index.
		 */
		DLL_IMPORT_OR_EXPORT std::string getAliasAuthorityAtIndex(unsigned int index) const;

		/**
		 * Get the alias title at a particular index in the aliases set.
		 *
		 * @param 	index	Zero-based index of the.
		 *
		 * @returns	The alias title at index.
		 */
		DLL_IMPORT_OR_EXPORT std::string getAliasTitleAtIndex(unsigned int index) const;

		/**
		 * Get all the activities where the instance is involved.
		 *
		 * @returns	Null if it fails, else the activity set.
		 */
		DLL_IMPORT_OR_EXPORT std::vector<RESQML2_NS::Activity *> getActivitySet() const;

		/**
		 * Get the count of associated activities.
		 *
		 * @returns	The activity count.
		 */
		DLL_IMPORT_OR_EXPORT unsigned int getActivityCount() const;

		/**
		 * Get the associated activity at a particular index.
		 *
		 * @param 	index	Zero-based index of the.
		 *
		 * @returns	Null if it fails, else the activity.
		 */
		DLL_IMPORT_OR_EXPORT RESQML2_NS::Activity * getActivity(unsigned int index) const;

		/**
		 * Push back an extra metadata (not a standard one)
		 *
		 * @param 	key  	The key.
		 * @param 	value	The value.
		 */
		DLL_IMPORT_OR_EXPORT void pushBackExtraMetadata(const std::string & key, const std::string & value);

		/**
		 * Getter (in read only mode) of all the extra metadata
		 *
		 * @returns	The extra metadata set.
		 */
		DLL_IMPORT_OR_EXPORT std::unordered_map< std::string, std::string > getExtraMetadataSet() const;

		/**
		 * Get an extra metadata according its key.
		 *
		 * @param 	key	The key.
		 *
		 * @returns	An empty vector if the extra metadata does not exist. Or the extra metadata value set
		 * 			if it exists.
		 */
		DLL_IMPORT_OR_EXPORT std::vector<std::string> getExtraMetadata(const std::string & key) const;

		/**
		 * Get the count of extra metadata in the instance.
		 *
		 * @returns	The extra metadata count.
		 */
		DLL_IMPORT_OR_EXPORT unsigned int getExtraMetadataCount() const;

		/**
		 * Get the key of a string value pair at a particular index in the extra metadata set
		 *
		 * @param 	index	Zero-based index of the.
		 *
		 * @returns	The extra metadata key at index.
		 */
		DLL_IMPORT_OR_EXPORT std::string getExtraMetadataKeyAtIndex(unsigned int index) const;

		/**
		 * Get the string value of a string value pair at a particular index in the extra metadata set
		 *
		 * @param 	index	Zero-based index of the.
		 *
		 * @returns	The extra metadata string value at index.
		 */
		DLL_IMPORT_OR_EXPORT std::string getExtraMetadataStringValueAtIndex(unsigned int index) const;
	};
}
