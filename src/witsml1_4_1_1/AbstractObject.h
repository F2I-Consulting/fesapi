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
