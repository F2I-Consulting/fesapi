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

#include "common/DataObjectRepository.h"

namespace COMMON_NS
{
	class AbstractObject
	{
	private:
		gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject; // only in case of partial transfer

		static char citationFormat[];

		/**
		* Set a uuid. If the input uuid is empty then a random uuid will be set.
		* It is too dangerous for now to modify the uuid because too much things depend on it. That's why this method is private.
		*/
		void setUuid(const std::string & uuid);

		/**
		* Push back an extra metadata (not a standard one)
		*/
		void pushBackExtraMetadataV2_0_1(const std::string & key, const std::string & value);
		void pushBackExtraMetadataV2_1(const std::string & key, const std::string & value);
#if WITH_EXPERIMENTAL
		void pushBackExtraMetadataV2_2(const std::string & key, const std::string & value);
#endif

		/**
		* Getter (in read only mode) of all the extra metadata
		*/
		std::unordered_map< std::string, std::string > getExtraMetadataSetV2_0_1() const;

		/**
		* Get an extra metadata according its key.
		* @return An empty vector if the extra metadata does not exist. Or the extra metadata value vector if it exists
		*/
		std::vector<std::string> getExtraMetadataV2_0_1(const std::string & key) const;

		/**
		* Get the count of extra metadata in the instance.
		*/
		unsigned int getExtraMetadataCountV2_0_1() const;

		/**
		* Get the key of a string value pair at a particular index in the extra metadata set
		*/
		std::string getExtraMetadataKeyAtIndexV2_0_1(unsigned int index) const;

		/**
		* Get the string value of a string value pair at a particular index in the extra metadata set
		*/
		std::string getExtraMetadataStringValueAtIndexV2_0_1(unsigned int index) const;

	protected:

		enum EmlVersion {
			TWO_DOT_ZERO = 0,
			TWO_DOT_ONE = 1
		};

		gsoap_resqml2_0_1::eml20__AbstractCitedDataObject* gsoapProxy2_0_1;
		gsoap_eml2_1::eml21__AbstractObject* gsoapProxy2_1;
#if WITH_EXPERIMENTAL
		gsoap_eml2_2::eml22__AbstractObject* gsoapProxy2_2;
#endif
		COMMON_NS::DataObjectRepository* repository;

		//Default constructor
		AbstractObject();

		/**
		* Constructor for partial transfer
		*/
		AbstractObject(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject_);

		AbstractObject(gsoap_resqml2_0_1::eml20__AbstractCitedDataObject* proxy);

		AbstractObject(gsoap_eml2_1::eml21__AbstractObject* proxy);

#if WITH_EXPERIMENTAL
		AbstractObject(gsoap_eml2_2::eml22__AbstractObject* proxy);
#endif

		friend void COMMON_NS::DataObjectRepository::addOrReplaceDataObject(AbstractObject* proxy);

		void initMandatoryMetadata();
		
		/**
		* Read the forward relationships of this dataobject and update the rels of the associated datarepository.
		*/
		virtual void loadTargetRelationships() const = 0;
		friend void COMMON_NS::DataObjectRepository::updateAllRelationships();

		/**
		* It is too dangerous for now to modify the uuid because too much things depend on it. That's why this method is only protected : it is only used by derived class constructor.
		* Set a title and other common metadata for the resqml instance. Set to empty string or zero if you don't want to use.
		* @param title				The title to set to the resqml instance. Set to empty string if you don't want to set it.
		*/
		void setMetadata(const std::string & guid, const std::string & title, const std::string & editor, time_t creation, const std::string & originator,
			const std::string & description, time_t lastUpdate, const std::string & descriptiveKeywords);

		/**
		* Throw an exception if the instance if partial.
		*/
		void cannotBePartial() const;

		/**
		* Transform a non partial object into a partial one
		*/
		void changeToPartialObject();

		/*
		* Read an input array which come from XML (and potentially HDF5) and store it into a preallocated output array in memory.
		* It does not allocate or deallocate memory.
		*/
		void readArrayNdOfDoubleValues(gsoap_resqml2_0_1::resqml2__AbstractDoubleArray * arrayInput, double * arrayOutput) const;

		/*
		* Read an input array which come from XML (and potentially HDF5) and store it into a preallocated output array in memory.
		* It does not allocate or deallocate memory.
		*/
		void readArrayNdOfUIntValues(gsoap_resqml2_0_1::resqml2__AbstractIntegerArray * arrayInput, unsigned int * arrayOutput) const;

		/*
		* Get the count of item in an array of integer
		*
		* @param arrayInput	The array of integer.
		* @return			The count of item in the array of integer.
		*/
		ULONG64 getCountOfIntegerArray(gsoap_resqml2_0_1::resqml2__AbstractIntegerArray * arrayInput) const;

		void convertDorIntoRel(gsoap_resqml2_0_1::eml20__DataObjectReference const * dor) const;

#if WITH_EXPERIMENTAL
		void convertDorIntoRel(gsoap_eml2_2::eml22__DataObjectReference const * dor) const;
#endif

		// Check that the content type of the DOR is OK with the datatype in memory.
		template <class valueType>
		void convertDorIntoRel(gsoap_resqml2_0_1::eml20__DataObjectReference const * dor) const
		{
			valueType const * targetObj = getRepository()->getDataObjectByUuid<valueType>(dor->UUID);
			if (targetObj == nullptr) { // partial transfer
				getRepository()->createPartial(dor);
				targetObj = getRepository()->getDataObjectByUuid<valueType>(dor->UUID);
				if (targetObj == nullptr) {
					throw std::invalid_argument("The DOR looks invalid.");
				}
			}
			getRepository()->addRelationship(this, targetObj);
		}

		template <class valueType>
		void convertDorIntoRel(gsoap_eml2_1::eml21__DataObjectReference const * dor) const
		{
			valueType const * targetObj = getRepository()->getDataObjectByUuid<valueType>(dor->Uuid);
			if (targetObj == nullptr) { // partial transfer
				getRepository()->createPartial(dor);
				targetObj = getRepository()->getDataObjectByUuid<valueType>(dor->Uuid);
				if (targetObj == nullptr) {
					throw std::invalid_argument("The DOR looks invalid.");
				}
			}
			getRepository()->addRelationship(this, targetObj);
		}

#if WITH_EXPERIMENTAL
		template <class valueType>
		void convertDorIntoRel(gsoap_eml2_2::eml22__DataObjectReference const * dor) const
		{
			valueType const * targetObj = getRepository()->getDataObjectByUuid<valueType>(dor->Uuid);
			if (targetObj == nullptr) { // partial transfer
				getRepository()->createPartial(dor);
				targetObj = getRepository()->getDataObjectByUuid<valueType>(dor->Uuid);
				if (targetObj == nullptr) {
					throw std::invalid_argument("The DOR looks invalid.");
				}
			}
			getRepository()->addRelationship(this, targetObj);
		}
#endif

		COMMON_NS::AbstractHdfProxy* getHdfProxyFromDataset(gsoap_resqml2_0_1::eml20__Hdf5Dataset const * dataset, bool throwException = true) const;

	public:
		virtual ~AbstractObject() {}

		/**
		* Indicate if the instance is actually a partial object.
		* A partial object just contains a mime type, an uuid and a title as a minimum amount of information.
		* A partial object is never explicit in an EPC document : it is not a file.
		*/
		DLL_IMPORT_OR_EXPORT bool isPartial() const {return partialObject != nullptr;}

		DLL_IMPORT_OR_EXPORT std::string getUuid() const;
		DLL_IMPORT_OR_EXPORT std::string getTitle() const;
		DLL_IMPORT_OR_EXPORT std::string getEditor() const;
		DLL_IMPORT_OR_EXPORT time_t getCreation() const;
		/**
		* Use this method if you want to read some dates out of range of time_t
		*/
		DLL_IMPORT_OR_EXPORT tm getCreationAsTimeStructure() const;
		DLL_IMPORT_OR_EXPORT std::string getOriginator() const;
		DLL_IMPORT_OR_EXPORT std::string getDescription() const;
		DLL_IMPORT_OR_EXPORT time_t getLastUpdate() const;
		/**
		* Use this method if you want to read some dates out of range of time_t
		*/
		DLL_IMPORT_OR_EXPORT tm getLastUpdateAsTimeStructure() const;
		DLL_IMPORT_OR_EXPORT std::string getFormat() const;
		DLL_IMPORT_OR_EXPORT std::string getDescriptiveKeywords() const;
		DLL_IMPORT_OR_EXPORT bool hasVersion() const;
		DLL_IMPORT_OR_EXPORT std::string getVersion() const;

		DLL_IMPORT_OR_EXPORT void setTitle(const std::string & title);
		DLL_IMPORT_OR_EXPORT void setEditor(const std::string & editor);
		DLL_IMPORT_OR_EXPORT void setCreation(time_t creation);
		/**
		* Use this method if you want to set some dates out of range of time_t
		*/
		DLL_IMPORT_OR_EXPORT void setCreation(const tm & creation);
		DLL_IMPORT_OR_EXPORT void setOriginator(const std::string & originator);
		DLL_IMPORT_OR_EXPORT void setDescription(const std::string & description);
		DLL_IMPORT_OR_EXPORT void setLastUpdate(time_t lastUpdate);
		/**
		* Use this method if you want to set some dates out of range of time_t
		*/
		DLL_IMPORT_OR_EXPORT void setLastUpdate(const tm & lastUpdate);
		
		/**
		* Set the default citation format which is going to be written in each created object.
		* A maximum of 256 chars is allowed.
		* @param vendor The vendor name which is exporting the RESQML objects
		* @param applicationName The application name which is exporting the RESQML objects
		* @param applicationVersionNumber The application version number which is exporting the RESQML objects
		*/
		DLL_IMPORT_OR_EXPORT static void setFormat(const std::string & vendor, const std::string & applicationName, const std::string & applicationVersionNumber);

		DLL_IMPORT_OR_EXPORT void setDescriptiveKeywords(const std::string & descriptiveKeywords);
		DLL_IMPORT_OR_EXPORT void setVersion(const std::string & version);

		/**
		* Set a title and other common metadata for the resqml instance. Set to empty string or zero if you don't want to use.
		* @param title				The title to set to the resqml instance. Set to empty string if you don't want to set it.
		*/
		DLL_IMPORT_OR_EXPORT void setMetadata(const std::string & title, const std::string & editor, time_t creation, const std::string & originator,
			const std::string & description, time_t lastUpdate, const std::string & descriptiveKeywords);

		/**
		* Serialize the instance into a stream.
		* @param stream	The stream must be opened for writing and won't be closed.
		*/
		DLL_IMPORT_OR_EXPORT void serializeIntoStream(std::ostream * stream);

		/**
		* Set the underlying gsoap proxy of this object
		*/
		void setGsoapProxy(gsoap_resqml2_0_1::eml20__AbstractCitedDataObject* gsoapProxy);

		/**
		* Get the gsoap proxy which is wrapped by this entity
		*/
		gsoap_resqml2_0_1::eml20__AbstractCitedDataObject* getGsoapProxy() const;

		/**
		* Get the gsoap context where the underlying gsoap proxy is defined.
		*/
		soap* getGsoapContext() const;

		/**
		* Get the Gsoap type of the wrapped element
		*/
		int getGsoapType() const;

		gsoap_resqml2_0_1::eml20__DataObjectReference* newResqmlReference() const;
		gsoap_eml2_1::eml21__DataObjectReference* newEmlReference() const;

#if WITH_EXPERIMENTAL
		gsoap_eml2_2::eml22__DataObjectReference* newEml22Reference() const;
#endif

		gsoap_resqml2_0_1::resqml2__ContactElementReference* newResqmlContactElementReference() const;

		/**
		 * Return the data object repository document which contains this gsoap wrapper.
		 */
		DLL_IMPORT_OR_EXPORT COMMON_NS::DataObjectRepository* getRepository() const {return repository;}

		/**
		* Get the XML namespace for the tags for the XML serialization of this instance
		*/
		virtual std::string getXmlNamespace() const;

		/**
		* Get the XML tag for the XML serialization of this instance
		*/
		DLL_IMPORT_OR_EXPORT virtual std::string getXmlTag() const = 0;

		/**
		* Get the XML tag for the XML serialization of this instance
		*/
		virtual std::string getResqmlVersion() const;

		/**
		* Get the content type of the instance according to EPC recommendation
		*/
		DLL_IMPORT_OR_EXPORT virtual std::string getContentType() const;
		
		/**
		* Get part name of this XML top level instance in the EPC document
		*/
		virtual std::string getPartNameInEpcDocument() const;

		/**
		* Serialize the gsoap proxy into a string
		*/
		DLL_IMPORT_OR_EXPORT std::string serializeIntoString();

		/**
		* Add an alias for this object
		*/
		DLL_IMPORT_OR_EXPORT void addAlias(const std::string & authority, const std::string & title);

		/**
		* Get the count of aliases in the instance.
		*/
		DLL_IMPORT_OR_EXPORT unsigned int getAliasCount() const;

		/**
		* Get the alias authority at a particular index in the aliases set.
		*/
		DLL_IMPORT_OR_EXPORT std::string getAliasAuthorityAtIndex(unsigned int index) const;

		/**
		* Get the alias title at a particular index in the aliases set.
		*/
		DLL_IMPORT_OR_EXPORT std::string getAliasTitleAtIndex(unsigned int index) const;

		/**
		* Get all the activities where the instance is involved.
		*/
		DLL_IMPORT_OR_EXPORT std::vector<RESQML2_NS::Activity const *> getActivitySet() const;

		/**
		* Get the count of associated activities.
		*/
		DLL_IMPORT_OR_EXPORT unsigned int getActivityCount() const;

		/**
		* Get the associated activity at a particular index.
		*/
		DLL_IMPORT_OR_EXPORT RESQML2_NS::Activity const * getActivity(unsigned int index) const;

		/**
		* Push back an extra metadata (not a standard one)
		*/
		DLL_IMPORT_OR_EXPORT void pushBackExtraMetadata(const std::string & key, const std::string & value);

		/**
		* Getter (in read only mode) of all the extra metadata
		*/
		DLL_IMPORT_OR_EXPORT std::unordered_map< std::string, std::string > getExtraMetadataSet() const;

		/**
		* Get an extra metadata according its key.
		* @return An empty vector if the extra metadata does not exist. Or the extra metadata value set if it exists.
		*/
		DLL_IMPORT_OR_EXPORT std::vector<std::string> getExtraMetadata(const std::string & key) const;

		/**
		* Get the count of extra metadata in the instance.
		*/
		DLL_IMPORT_OR_EXPORT unsigned int getExtraMetadataCount() const;

		/**
		* Get the key of a string value pair at a particular index in the extra metadata set
		*/
		DLL_IMPORT_OR_EXPORT std::string getExtraMetadataKeyAtIndex(unsigned int index) const;

		/**
		* Get the string value of a string value pair at a particular index in the extra metadata set
		*/
		DLL_IMPORT_OR_EXPORT std::string getExtraMetadataStringValueAtIndex(unsigned int index) const;
	};
}
