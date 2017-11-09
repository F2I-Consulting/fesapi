/*-----------------------------------------------------------------------
Copyright F2I-CONSULTING, (2014-2017)

philippe.verney@f2i-consulting.com

This software is a computer program whose purpose is to access to data formatted using Energistics standards.

This software is governed by the CeCILL-B license under French law and
abiding by the rules of distribution of free software.  You can  use, 
modify and/ or redistribute the software under the terms of the CeCILL-B
license as circulated by CEA, CNRS and INRIA at the following URL
"http://www.cecill.info". 

As a counterpart to the access to the source code and  rights to copy,
modify and redistribute granted by the license, users are provided only
with a limited warranty  and the software's author,  the holder of the
economic rights,  and the successive licensors  have only  limited
liability. 

In this respect, the user's attention is drawn to the risks associated
with loading,  using,  modifying and/or developing or reproducing the
software by the user in light of its specific status of free software,
that may mean  that it is complicated to manipulate,  and  that  also
therefore means  that it is reserved for developers  and  experienced
professionals having in-depth computer knowledge. Users are therefore
encouraged to load and test the software's suitability as regards their
requirements in conditions enabling the security of their systems and/or 
data to be ensured and,  more generally, to use and operate it in the 
same conditions as regards security. 

The fact that you are presently reading this means that you have had
knowledge of the CeCILL-B license and that you accept its terms.
-----------------------------------------------------------------------*/
#pragma once

#include "proxies/gsoap_resqml2_0_1H.h"
#include "proxies/gsoap_eml2_1H.h"
#include "common/EpcDocument.h"

namespace common
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
		common::EpcDocument* epcDocument;
		std::vector<resqml2::Activity*> activitySet;

		bool updateXml; /// Indicate whether methods update the XML (gSoap) or only the C++ classes of the API.

		//Default constructor
		AbstractObject();

		/**
		* Constructor for partial transfer
		*/
		AbstractObject(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject);

		AbstractObject(gsoap_resqml2_0_1::eml20__AbstractCitedDataObject* proxy);

		AbstractObject(gsoap_eml2_1::eml21__AbstractObject* proxy);

		friend void common::EpcDocument::addGsoapProxy(AbstractObject* proxy);

		void initMandatoryMetadata();
		
		/**
		* Resolve all relationships of the object in an epc document
		*/
		virtual void importRelationshipSetFromEpc(common::EpcDocument * epcDoc) = 0;
		friend void common::EpcDocument::updateAllRelationships();

		/**
		* Return all relationships (backward and forward ones) of the instance using EPC format.
		*/
		virtual std::vector<epc::Relationship> getAllEpcRelationships() const = 0;
		friend void common::EpcDocument::serialize(bool useZip64);

		// Only for Activity. Can not use friendness between AbstractObject and Activity for circular dependencies reason.
		static void addActivityToResqmlObject(resqml2::Activity* activity, AbstractObject* resqmlObject);

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
		std::string getOriginator() const;
		std::string getDescription() const;
		time_t getLastUpdate() const;
		std::string getFormat() const;
		std::string getDescriptiveKeywords() const;

		void setTitle(const std::string & title);
		void setEditor(const std::string & editor);
		void setCreation(const time_t & creation);
		void setOriginator(const std::string & originator);
		void setDescription(const std::string & description);
		void setLastUpdate(const time_t & lastUpdate);
		void setFormat(const std::string & format);
		void setDescriptiveKeywords(const std::string & descriptiveKeywords);

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
		gsoap_resqml2_0_1::eml20__AbstractCitedDataObject* getGsoapProxy() const {return gsoapProxy2_0_1;}

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
		common::EpcDocument* getEpcDocument() const {return epcDocument;}

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
		const std::vector<resqml2::Activity*> & getActivitySet() const;

		/**
		* Get the count of associated activities.
		*/
		unsigned int getActivityCount() const;

		/**
		* Get the associated activity at a particular index.
		*/
		resqml2::Activity* getActivity (const unsigned int & index) const;

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
