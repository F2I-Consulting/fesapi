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

#include "proxies/gsoap_resqml2_0_1H.h"
#include "proxies/gsoap_eml2_1H.h"
#include "common/EpcDocument.h"

namespace COMMON_NS
{
	class DLL_IMPORT_OR_EXPORT AbstractObject
	{
	private:
		gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject; // only in case of partial transfer

		/**
		* Set a uuid. If the input uuid is empty then a random uuid will be set.
		* It is too dangerous for now to modify the uuid because too much things depend on it. That's why this method is private.
		*/
		void setUuid(const std::string & uuid);

		/**
		* Push back an extra metadata (not a standard one)
		*/
		void pushBackExtraMetadataV2_0_1(const std::string & key, const std::string & value);

		/**
		* Getter (in read only mode) of all the extra metadata
		*/
#if (defined(_WIN32) && _MSC_VER >= 1600) || defined(__APPLE__)
		std::unordered_map< std::string, std::string > getExtraMetadataSetV2_0_1() const;
#else
		std::tr1::unordered_map< std::string, std::string > getExtraMetadataSetV2_0_1() const;
#endif

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
		std::string getExtraMetadataKeyAtIndexV2_0_1(const unsigned int & index) const;

		/**
		* Get the string value of a string value pair at a particular index in the extra metadata set
		*/
		std::string getExtraMetadataStringValueAtIndexV2_0_1(const unsigned int & index) const;

	protected:

		enum EmlVersion {
			TWO_DOT_ZERO = 0,
			TWO_DOT_ONE = 1,
		};
		
		gsoap_resqml2_0_1::eml20__AbstractCitedDataObject* gsoapProxy2_0_1;
		gsoap_eml2_1::eml21__AbstractObject* gsoapProxy2_1;
		COMMON_NS::EpcDocument* epcDocument;
		std::vector<RESQML2_NS::Activity*> activitySet;

		bool updateXml; /// Indicate whether methods update the XML (gSoap) or only the C++ classes of the API.

		//Default constructor
		AbstractObject();

		/**
		* Constructor for partial transfer
		*/
		AbstractObject(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject);

		AbstractObject(gsoap_resqml2_0_1::eml20__AbstractCitedDataObject* proxy);

		AbstractObject(gsoap_eml2_1::eml21__AbstractObject* proxy);

		friend void COMMON_NS::EpcDocument::addGsoapProxy(AbstractObject* proxy);

		void initMandatoryMetadata();
		
		/**
		* Resolve all relationships of the object in an epc document
		*/
		virtual void importRelationshipSetFromEpc(COMMON_NS::EpcDocument * epcDoc) = 0;
		friend void COMMON_NS::EpcDocument::updateAllRelationships();

		/**
		* Return all relationships (backward and forward ones) of the instance using EPC format.
		*/
		virtual std::vector<epc::Relationship> getAllEpcRelationships() const = 0;
		friend void COMMON_NS::EpcDocument::serialize(bool useZip64);

		// Only for Activity. Can not use friendness between AbstractObject and Activity for circular dependencies reason.
		static void addActivityToResqmlObject(RESQML2_NS::Activity* activity, AbstractObject* resqmlObject);

		/**
		* It is too dangerous for now to modify the uuid because too much things depend on it. That's why this method is only protected : it is only used by derived class constructor.
		* Set a title and other common metadata for the resqml instance. Set to empty string or zero if you don't want to use.
		* @param title				The title to set to the resqml instance. Set to empty string if you don't want to set it.
		*/
		void setMetadata(const std::string & guid, const std::string & title, const std::string & editor, const time_t & creation, const std::string & originator,
			const std::string & description, const time_t & lastUpdate, const std::string & format, const std::string & descriptiveKeywords);

		/**
		* Throw an exception if the instance if partial.
		*/
		void cannotBePartial() const;

		/**
		* Transform a non partial object into a partial one
		*/
		void changeToPartialObject();

	public:
		virtual ~AbstractObject() {}

		/**
		* Indicate if the instance is actually a partial object.
		* A partial object just contains a mime type, an uuid and a title as a minimum amount of information.
		* A partial object is never explicit in an EPC document : it is not a file.
		*/
		bool isPartial() const {return partialObject != nullptr;}

		std::string getUuid() const;
		std::string getTitle() const;
		std::string getEditor() const;
		time_t getCreation() const;
		/**
		* Use this method if you want to read some dates out of range of time_t
		*/
		tm getCreationAsTimeStructure() const;
		std::string getOriginator() const;
		std::string getDescription() const;
		time_t getLastUpdate() const;
		/**
		* Use this method if you want to read some dates out of range of time_t
		*/
		tm getLastUpdateAsTimeStructure() const;
		std::string getFormat() const;
		std::string getDescriptiveKeywords() const;
		std::string getVersionString() const;

		void setTitle(const std::string & title);
		void setEditor(const std::string & editor);
		void setCreation(const time_t & creation);
		/**
		* Use this method if you want to set some dates out of range of time_t
		*/
		void setCreation(const tm & creation);
		void setOriginator(const std::string & originator);
		void setDescription(const std::string & description);
		void setLastUpdate(const time_t & lastUpdate);
		/**
		* Use this method if you want to set some dates out of range of time_t
		*/
		void setLastUpdate(const tm & lastUpdate);
		void setFormat(const std::string & format);
		void setDescriptiveKeywords(const std::string & descriptiveKeywords);
		void setVersionString(const std::string & versionString);

		/**
		* Set a title and other common metadata for the resqml instance. Set to empty string or zero if you don't want to use.
		* @param title				The title to set to the resqml instance. Set to empty string if you don't want to set it.
		*/
		void setMetadata(const std::string & title, const std::string & editor, const time_t & creation, const std::string & originator,
			const std::string & description, const time_t & lastUpdate, const std::string & format, const std::string & descriptiveKeywords);

		/**
		* Serialize the instance into a stream.
		* @param stream	The stream must be opened for writing and won't be closed.
		*/
		void serializeIntoStream(std::ostream * stream);

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

		gsoap_resqml2_0_1::resqml2__ContactElementReference* newResqmlContactElementReference() const;

		/**
		 * Return the EPC document which contains this gsoap wrapper.
		 */
		COMMON_NS::EpcDocument* getEpcDocument() const {return epcDocument;}

		/**
		* Get the XML namespace for the tags for the XML serialization of this instance
		*/
		virtual std::string getXmlNamespace() const;

		/**
		* Get the XML tag for the XML serialization of this instance
		*/
		virtual std::string getXmlTag() const = 0;

		/**
		* Get the XML tag for the XML serialization of this instance
		*/
		virtual std::string getResqmlVersion() const;

		/**
		* Get the content type of the instance according to EPC recommendation
		*/
		virtual std::string getContentType() const;
		
		/**
		* Get part name of this XML top level instance in the EPC document
		*/
		virtual std::string getPartNameInEpcDocument() const;

		/**
		* Serialize the gsoap proxy into a string
		*/
		std::string serializeIntoString();	

		/**
		* Add an alias for this object
		*/
		void addAlias(const std::string & authority, const std::string & title);

		/**
		* Get the count of aliases in the instance.
		*/
		unsigned int getAliasCount() const;

		/**
		* Get the alias authority at a particular index in the aliases set.
		*/
		std::string getAliasAuthorityAtIndex(const unsigned int & index) const;

		/**
		* Get the alias title at a particular index in the aliases set.
		*/
		std::string getAliasTitleAtIndex(const unsigned int & index) const;

		/**
		* Get all the activities where the instance is involved.
		*/
		const std::vector<RESQML2_NS::Activity*> & getActivitySet() const;

		/**
		* Get the count of associated activities.
		*/
		unsigned int getActivityCount() const;

		/**
		* Get the associated activity at a particular index.
		*/
		RESQML2_NS::Activity* getActivity (const unsigned int & index) const;

		/**
		* Push back an extra metadata (not a standard one)
		*/
		void pushBackExtraMetadata(const std::string & key, const std::string & value);

		/**
		* Getter (in read only mode) of all the extra metadata
		*/
#if (defined(_WIN32) && _MSC_VER >= 1600) || defined(__APPLE__)
		std::unordered_map< std::string, std::string > getExtraMetadataSet() const;
#else
		std::tr1::unordered_map< std::string, std::string > getExtraMetadataSet() const;
#endif

		/**
		* Get an extra metadata according its key.
		* @return An empty vector if the extra metadata does not exist. Or the extra metadata value set if it exists.
		*/
		std::vector<std::string> getExtraMetadata(const std::string & key) const;

		/**
		* Get the count of extra metadata in the instance.
		*/
		unsigned int getExtraMetadataCount() const;

		/**
		* Get the key of a string value pair at a particular index in the extra metadata set
		*/
		std::string getExtraMetadataKeyAtIndex(const unsigned int & index) const;

		/**
		* Get the string value of a string value pair at a particular index in the extra metadata set
		*/
		std::string getExtraMetadataStringValueAtIndex(const unsigned int & index) const;
	};
}

