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

#include "common/EpcDocument.h"

namespace witsml1_4_1_1
{
	/**
	* They are all containers.
	*/
	class DLL_IMPORT_OR_EXPORT AbstractObject
	{
	protected:		
		gsoap_witsml1_4_1_1::abstract__abstractObject* collection;
		common::EpcDocument* epcDocument;

		// forward relationshsip
		class CoordinateReferenceSystem* crs;

		bool updateXml; /// Indicate wether methods update the XML (Gsoap) or only the C++ classes of the API.
		
		AbstractObject(gsoap_witsml1_4_1_1::abstract__abstractObject* proxy = nullptr) : collection(proxy), epcDocument (nullptr), crs(nullptr), updateXml(true) {}

		friend void common::EpcDocument::addGsoapProxy(witsml1_4_1_1::AbstractObject* proxy);

		gsoap_witsml1_4_1_1::witsml1__cs_USCOREcommonData* newCommonData(
			const std::string & sourceName,
			const time_t & dTimCreation,
			const time_t & dTimLastChange,
			const std::string & comments);

		gsoap_witsml1_4_1_1::witsml1__cs_USCORElocation* constructEastingNorthingLocation(
			gsoap_witsml1_4_1_1::witsml1__LengthUom uom,
			const double & easting,
			const double & northing,
			class CoordinateReferenceSystem* wellCrs);

		gsoap_witsml1_4_1_1::witsml1__cs_USCORElocation* constructWestingSouthingLocation(
			gsoap_witsml1_4_1_1::witsml1__LengthUom uom,
			const double & westing,
			const double & southing,
			class CoordinateReferenceSystem* wellCrs);

		gsoap_witsml1_4_1_1::witsml1__cs_USCORElocation* constructProjectedXProjectedYLocation(
			gsoap_witsml1_4_1_1::witsml1__LengthUom uom,
			const double & projectedX,
			const double & projectedY,
			class CoordinateReferenceSystem* wellCrs);

	public:
		virtual ~AbstractObject() {}

		static const char* SCHEMA_VERSION;

		virtual const std::string & getTitle() const = 0;

		virtual std::string getUuid() const = 0;
		virtual time_t getCreation() const = 0;
		virtual time_t getLastUpdate() const = 0;

		/**
		* Get the gsoap proxy which is wrapped by this entity
		*/
		gsoap_witsml1_4_1_1::abstract__abstractObject* getGsoapProxy() {return collection;}

		/**
		* Serialize the instance into a stream.
		* @param stream	The stream must be opened for writing and won't be closed.
		*/
		void serializeIntoStream(std::ostream * stream);

		/**
		* Get the Gsoap type of the wrapped element
		*/
		int getGsoapType() const {return collection->soap_type();}

		/**
		 * Return the EPC document which contains this gsoap wrapper.
		 */
		common::EpcDocument* getEpcDocument() const {return epcDocument;}

		/**
		* Get the XML namespace for the tags for the XML serialization of this instance
		*/
		virtual std::string getXmlNamespace() const {return "witsml1";}

		/**
		* Get the XML tag for the XML serialization of this instance
		*/
		virtual std::string getXmlTag() const = 0;

		/**
		* Get the content type of the instance according to EPC recommendation
		*/
		std::string getContentType() const;
		
		/**
		* Get part name of this XML top level instance in the EPC document
		*/
		std::string getPartNameInEpcDocument() const;

		gsoap_resqml2_0_1::eml20__DataObjectReference* newResqmlReference() const;

		void setCoordinateReferenceSystem(class CoordinateReferenceSystem* wellCrs);

		class CoordinateReferenceSystem* getCoordinateReferenceSystem() const {return crs;}

		/**
		* Return all relationships (backward and forward ones) of the instance using EPC format.
		*/
		virtual std::vector<epc::Relationship> getAllEpcRelationships() const;

		/**
		* Resolve all relationships of the object in an epc document
		*/
		virtual void importRelationshipSetFromEpc(common::EpcDocument * epcDoc) = 0;

		/**
		* Serialize the gsoap proxy into a string
		*/
		std::string serializeIntoString();
	};
}

