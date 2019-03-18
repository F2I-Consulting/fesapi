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

#include "witsml2_0/AbstractObject.h"
#include "witsml2_0/Wellbore.h"
#include "witsml2_0/WellCompletion.h"

#define GETTER_AND_SETTER_WELL_STRING64_ATTRIBUTE(attributeName)\
	DLL_IMPORT_OR_EXPORT void set##attributeName(const std::string & attributeName);\
	DLL_IMPORT_OR_EXPORT bool has##attributeName() const;\
	DLL_IMPORT_OR_EXPORT std::string get##attributeName() const;

#define GETTER_AND_SETTER_WELL_LENGTH_MEASURE_ATTRIBUTE(attributeName)\
	DLL_IMPORT_OR_EXPORT void set##attributeName(double value, gsoap_eml2_1::eml21__LengthUom uom);\
	DLL_IMPORT_OR_EXPORT bool has##attributeName() const;\
	DLL_IMPORT_OR_EXPORT double get##attributeName##Value() const;\
	DLL_IMPORT_OR_EXPORT gsoap_eml2_1::eml21__LengthUom get##attributeName##Uom() const;

namespace WITSML2_0_NS
{
	class Well : public WITSML2_0_NS::AbstractObject
	{
	private:
		void setString(std::string* & strToBeSet, const std::string & strToSet);
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
			gsoap_eml2_1::eml21__WellStatus statusWell,
			gsoap_eml2_1::witsml2__WellDirection directionWell
		);

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		Well(gsoap_eml2_1::witsml2__Well* fromGsoap):AbstractObject(fromGsoap)  {}

		/**
		* Destructor does nothing since the memory is managed by the gsoap context.
		*/
		~Well() {}

		GETTER_AND_SETTER_WELL_STRING64_ATTRIBUTE(NameLegal)
		GETTER_AND_SETTER_WELL_STRING64_ATTRIBUTE(NumLicense)
		GETTER_AND_SETTER_WELL_STRING64_ATTRIBUTE(NumGovt)
		GETTER_AND_SETTER_WELL_STRING64_ATTRIBUTE(Field)
		GETTER_AND_SETTER_WELL_STRING64_ATTRIBUTE(Country)
		GETTER_AND_SETTER_WELL_STRING64_ATTRIBUTE(State)
		GETTER_AND_SETTER_WELL_STRING64_ATTRIBUTE(County)
		GETTER_AND_SETTER_WELL_STRING64_ATTRIBUTE(Region)
		GETTER_AND_SETTER_WELL_STRING64_ATTRIBUTE(District)
		GETTER_AND_SETTER_WELL_STRING64_ATTRIBUTE(Block)
		GETTER_AND_SETTER_WELL_STRING64_ATTRIBUTE(Operator)
		GETTER_AND_SETTER_WELL_STRING64_ATTRIBUTE(OperatorDiv)
		GETTER_AND_SETTER_WELL_STRING64_ATTRIBUTE(OriginalOperator)
		GETTER_AND_SETTER_WELL_STRING64_ATTRIBUTE(NumAPI)

		GETTER_AND_SETTER_WELL_LENGTH_MEASURE_ATTRIBUTE(WaterDepth)
		GETTER_AND_SETTER_WELL_LENGTH_MEASURE_ATTRIBUTE(GroundElevation)

		DLL_IMPORT_OR_EXPORT double getLocationProjectedX(unsigned int locationIndex);
		DLL_IMPORT_OR_EXPORT double getLocationProjectedY(unsigned int locationIndex);

		DLL_IMPORT_OR_EXPORT void pushBackLocation(
			const std::string & guid,
			double projectedX,
			double projectedY,
			unsigned int projectedCrsEpsgCode);

		DLL_IMPORT_OR_EXPORT unsigned int geLocationCount() const;
		
		DLL_IMPORT_OR_EXPORT void pushBackDatum(
			const std::string & guid, 
			const std::string & title,
			gsoap_eml2_1::eml21__WellboreDatumReference code,
			const std::string & datum,
			gsoap_eml2_1::eml21__LengthUom elevationUnit,
			double elevation,
			unsigned int verticalCrsEpsgCode);

		DLL_IMPORT_OR_EXPORT unsigned int getDatumCount() const;
		
		void importRelationshipSetFromEpc(COMMON_NS::EpcDocument* epcDoc);

		std::vector<epc::Relationship> getAllEpcRelationships() const;

		DLL_IMPORT_OR_EXPORT RESQML2_0_1_NS::WellboreFeature* getResqmlWellboreFeature() const;

		DLL_IMPORT_OR_EXPORT const std::vector<Wellbore*>& getWellbores() const;

		DLL_IMPORT_OR_EXPORT const std::vector<WellCompletion*>& getWellcompletions() const;

		DLL_IMPORT_OR_EXPORT static const char* XML_TAG;
		DLL_IMPORT_OR_EXPORT virtual std::string getXmlTag() const {return XML_TAG;}

	protected:

		// backwards relationship
		RESQML2_0_1_NS::WellboreFeature* resqmlWellboreFeature;
		std::vector<Wellbore*> wellboreSet;
		std::vector<WellCompletion* > wellCompletionSet;

		friend void RESQML2_0_1_NS::WellboreFeature::setWitsmlWellbore(WITSML2_0_NS::Wellbore * wellbore);
		friend void Wellbore::setWell(Well* witsmlWell);
		friend void WellCompletion::setWell(Well* witsmlWell);
	};
}

