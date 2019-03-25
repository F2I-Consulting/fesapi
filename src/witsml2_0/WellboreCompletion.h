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

namespace WITSML2_0_NS
{
	class DLL_IMPORT_OR_EXPORT WellboreCompletion : public WITSML2_0_NS::AbstractObject
	{
	public:
		WellboreCompletion(class Wellbore* witsmlWellbore,
			class WellCompletion* wellCompletion,
			const std::string & guid,
			const std::string & title,
			const std::string & wellCompletionName);
	
		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		WellboreCompletion(gsoap_eml2_1::witsml2__WellboreCompletion* fromGsoap) :AbstractObject(fromGsoap) {}

		/**
		* Destructor does nothing since the memory is managed by the gsoap context.
		*/
		~WellboreCompletion() {}

		gsoap_eml2_1::eml21__DataObjectReference* getWellboreDor() const;

		class Wellbore* getWellbore() const;

		gsoap_eml2_1::eml21__DataObjectReference* getWellCompletionDor() const;

		class WellCompletion* getWellCompletion() const;

		void setWellbore(class Wellbore* witsmlWellbore);
		
		void setWellCompletion(class WellCompletion* wellCompletion);

		void pushBackPerforation(const std::string & datum,
			gsoap_eml2_1::eml21__LengthUom MdUnit,
			const double & TopMd,
			const double & BaseMd, 
			const std::string & guid = "");

		// bien préciser dans la doc qu'on peut mettre -1 manuellement pour les dates et "" pour le guid
		void pushBackPerforationHistoryEntry(const std::string & perforationGuid,
			gsoap_eml2_1::witsml2__PerforationStatus perforationStatus,
			const std::string & datum,
			gsoap_eml2_1::eml21__LengthUom MdUnit,
			const double & TopMd,
			const double & BaseMd, 
			const time_t & startDate = -1,
			const time_t & endDate = -1,
			const std::string & guid = "");

		unsigned int getPerforationCount() const;

		bool hasPerforationMdDatum(const std::string & guid) const;
		
		std::string getPerforationMdDatum(const std::string & guid) const;
		
		bool hasPerforationMdUnit(const std::string & guid) const;
		
		gsoap_eml2_1::eml21__LengthUom getPerforationMdUnit(const std::string & guid) const;
		
		bool hasPerforationTopMd(const std::string & guid) const;
		
		double getPerforationTopMd(const std::string & guid) const;

		bool hasPerforationBaseMd(const std::string & guid) const;

		double getPerforationBaseMd(const std::string & guid) const;

		unsigned int getHistoryEntryCount(const std::string & perforationGuid) const;

		bool hasPerforationHistoryEntryStatus(const std::string & guid,
			const std::string & perforationGuid) const;

		gsoap_eml2_1::witsml2__PerforationStatus getPerforationHistoryEntryStatus(const std::string & guid,
			const std::string & perforationGuid) const;

		std::string getPerforationHistoryEntryStatusToString(const std::string & guid,
			const std::string & perforationGuid) const;

		bool hasPerforationHistoryEntryStartDate(const std::string & guid,
			const std::string & perforationGuid) const;

		time_t getPerforationHistoryEntryStartDate(const std::string & guid,
			const std::string & perforationGuid) const;

		bool hasPerforationHistoryEntryEndDate(const std::string & guid,
			const std::string & perforationGuid) const;

		time_t getPerforationHistoryEntryEndDate(const std::string & guid,
			const std::string & perforationGuid) const;
		
		bool hasPerforationHistoryEntryMdDatum(const std::string & guid,
			const std::string & perforationGuid) const;
		
		std::string getPerforationHistoryEntryMdDatum(const std::string & guid,
			const std::string & perforationGuid) const;
		
		bool hasPerforationHistoryEntryMdUnit(const std::string & guid,
			const std::string & perforationGuid) const;

		gsoap_eml2_1::eml21__LengthUom getPerforationHistoryEntryMdUnit(const std::string & guid,
			const std::string & perforationGuid) const;

		bool hasPerforationHistoryEntryTopMd(const std::string & guid,
			const std::string & perforationGuid) const;

		double getPerforationHistoryEntryTopMd(const std::string & guid,
			const std::string & perforationGuid) const;
		
		bool hasPerforationHistoryEntryBaseMd(const std::string & guid,
			const std::string & perforationGuid) const;

		double getPerforationHistoryEntryBaseMd(const std::string & guid,
			const std::string & perforationGuid) const;

		std::vector<epc::Relationship> getAllSourceRelationships() const;
		std::vector<epc::Relationship> getAllTargetRelationships() const;
		void resolveTargetRelationships(COMMON_NS::EpcDocument * epcDoc);

		static const char* XML_TAG;
		virtual std::string getXmlTag() const { return XML_TAG; }

	private:
		gsoap_eml2_1::witsml2__PerforationSetInterval* getPerforation(const std::string & guid) const;

		gsoap_eml2_1::witsml2__PerforationStatusHistory* getPerforationHistoryEntry(const std::string & guid, 
			const std::string & perforationGuid) const;
	};
}