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

#include "witsml1_4_1_1/AbstractObject.h"

namespace WITSML1_4_1_1_NS
{
	class DLL_IMPORT_OR_EXPORT CoordinateReferenceSystem : public AbstractObject
	{
	public:
		/**
		* Creates an instance of this class in a gsoap context.
		* @param soapContext	The soap context where the underlying gsoap proxy is going to be created.
		* @param guid			The guid to set to this instance. If empty then a new guid will be generated.
		*/
		CoordinateReferenceSystem(soap* soapContext,
			const std::string & guid,
			const std::string & title,
			const std::string & namingSystem,
			const std::string & code,
			const std::string & sourceName,
			const time_t & dTimCreation,
			const time_t & dTimLastChange,
			const std::string & comments
		);

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		CoordinateReferenceSystem(gsoap_witsml1_4_1_1::witsml1__obj_USCOREcoordinateReferenceSystems* fromGsoap):AbstractObject(fromGsoap) {}

		/**
		* Destructor does nothing since the memory is managed by the gsoap context.
		*/
		~CoordinateReferenceSystem() {}

		soap* getGSoapContext() const {return collection->soap;}

		gsoap_witsml1_4_1_1::witsml1__refNameString* newReference() const;

		const std::vector<AbstractObject*>& getObjectsUsingThisCrs() const {return objectsUsingThisCrs;}

		const std::string & getTitle() const {return static_cast<gsoap_witsml1_4_1_1::witsml1__obj_USCOREcoordinateReferenceSystems*>(collection)->coordinateReferenceSystem[0]->name;}

		std::string getUuid() const {return *static_cast<gsoap_witsml1_4_1_1::witsml1__obj_USCOREcoordinateReferenceSystems*>(collection)->coordinateReferenceSystem[0]->uid;}
		time_t getCreation() const
		{
			if (static_cast<gsoap_witsml1_4_1_1::_witsml1__coordinateReferenceSystems*>(collection)->coordinateReferenceSystem[0]->commonData->dTimCreation)
				return mktime(static_cast<gsoap_witsml1_4_1_1::_witsml1__coordinateReferenceSystems*>(collection)->coordinateReferenceSystem[0]->commonData->dTimCreation);
			else
				return -1;
		}
		time_t getLastUpdate() const
		{
			if (static_cast<gsoap_witsml1_4_1_1::_witsml1__coordinateReferenceSystems*>(collection)->coordinateReferenceSystem[0]->commonData->dTimLastChange)
				return mktime(static_cast<gsoap_witsml1_4_1_1::_witsml1__coordinateReferenceSystems*>(collection)->coordinateReferenceSystem[0]->commonData->dTimLastChange);
			else
				return -1;
		}

		std::vector<epc::Relationship> getAllEpcRelationships() const;

		/**
		* Resolve all relationships of the object in an epc document.
		* Does nothing since there is no forward relationship.
		*/
		void importRelationshipSetFromEpc(COMMON_NS::EpcDocument* epcDoc) {}

		static const char* XML_TAG;
		virtual std::string getXmlTag() const {return XML_TAG;}

	protected:

		//backward relationship
		std::vector<AbstractObject*> objectsUsingThisCrs;

		friend void AbstractObject::setCoordinateReferenceSystem(CoordinateReferenceSystem* wellCrs);
	};
}

