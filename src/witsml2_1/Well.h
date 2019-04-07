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

#include "witsml2_1/Wellbore.h"

namespace WITSML2_1_NS
{
	class DLL_IMPORT_OR_EXPORT Well : public WITSML2_1_NS::AbstractObject
	{
	public:
		/**
		* Creates an instance of this class in a gsoap context.
		* @param soapContext	The soap context where the underlying gsoap proxy is going to be created.
		* @param guid		The guid to set to this instance. If empty then a new guid will be generated.
		*/
		Well(soap* soapContext,
			const std::string & guid,
			const std::string & title);

		Well(soap* soapContext,
			const std::string & guid,
			const std::string & title,
			const std::string & operator_,
			gsoap_eml2_2::eml22__WellStatus statusWell,
			gsoap_eml2_2::witsml2__WellPurpose purposeWell,
			gsoap_eml2_2::witsml2__WellFluid fluidWell,
			gsoap_eml2_2::witsml2__WellDirection directionWell
		);

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		Well(gsoap_eml2_2::witsml2__Well* fromGsoap):AbstractObject(fromGsoap)  {}

		/**
		* Destructor does nothing since the memory is managed by the gsoap context.
		*/
		~Well() {}

		void setOperator(const std::string & operator_);

		double getLocationProjectedX(const unsigned int & locationIndex);
		double getLocationProjectedY(const unsigned int & locationIndex);

		void pushBackLocation(
			const std::string & guid,
			const double & projectedX,
			const double & projectedY,
			const unsigned int & projectedCrsEpsgCode);

		unsigned int geLocationCount() const;
		
		void pushBackDatum(
			const std::string & guid, 
			const std::string & title,
			gsoap_eml2_2::eml22__WellboreDatumReference code,
			const std::string & datum,
			gsoap_eml2_2::eml22__LengthUom elevationUnit,
			const double & elevation,
			const unsigned int & verticalCrsEpsgCode);

		unsigned int getDatumCount() const;
		
		/**
		* Resolve all relationships of the object in an epc document.
		* Does nothing since there is no forward relationship.
		*/
		void importRelationshipSetFromEpc(COMMON_NS::EpcDocument* epcDoc) {}

		std::vector<epc::Relationship> getAllEpcRelationships() const;

		const std::vector<Wellbore*>& getWellbores() const { return wellboreSet; }

		static const char* XML_TAG;
		virtual std::string getXmlTag() const {return XML_TAG;}

	protected:

		// backwards relationship
		std::vector<Wellbore*> wellboreSet;

		friend void Wellbore::setWell(Well* witsmlWell);
	};
}

