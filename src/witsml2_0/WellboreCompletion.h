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

#include "witsml2_0/WellboreObject.h"

namespace WITSML2_0_NS
{
	class WellboreCompletion : public WITSML2_0_NS::WellboreObject
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
		WellboreCompletion(gsoap_eml2_1::witsml2__WellboreCompletion* fromGsoap) :WellboreObject(fromGsoap) {}

		/**
		* Destructor does nothing since the memory is managed by the gsoap context.
		*/
		~WellboreCompletion() {}

		gsoap_eml2_1::eml21__DataObjectReference* getWellboreDor() const;

		gsoap_eml2_1::eml21__DataObjectReference* getWellCompletionDor() const;

		DLL_IMPORT_OR_EXPORT class WellCompletion* getWellCompletion() const;

		DLL_IMPORT_OR_EXPORT void setWellbore(class Wellbore* witsmlWellbore);
		
		DLL_IMPORT_OR_EXPORT void setWellCompletion(class WellCompletion* wellCompletion);

		DLL_IMPORT_OR_EXPORT void pushBackPerforation(const std::string & datum,
			gsoap_eml2_1::eml21__LengthUom MdUnit,
			const double & TopMd,
			const double & BaseMd, 
			const std::string & guid = "");

		DLL_IMPORT_OR_EXPORT void pushBackPerforationHistoryEntry(const std::string & perforationGuid,
			gsoap_eml2_1::witsml2__PerforationStatus perforationStatus,
			const std::string & datum,
			gsoap_eml2_1::eml21__LengthUom MdUnit,
			const double & TopMd,
			const double & BaseMd, 
			const time_t & startDate = -1,
			const time_t & endDate = -1,
			const std::string & guid = "");

		DLL_IMPORT_OR_EXPORT unsigned int getPerforationCount() const;

		DLL_IMPORT_OR_EXPORT bool hasPerforationMdDatum(const std::string & guid) const;
		
		DLL_IMPORT_OR_EXPORT std::string getPerforationMdDatum(const std::string & guid) const;
		
		DLL_IMPORT_OR_EXPORT bool hasPerforationMdUnit(const std::string & guid) const;
		
		DLL_IMPORT_OR_EXPORT gsoap_eml2_1::eml21__LengthUom getPerforationMdUnit(const std::string & guid) const;
		
		DLL_IMPORT_OR_EXPORT bool hasPerforationTopMd(const std::string & guid) const;
		
		DLL_IMPORT_OR_EXPORT double getPerforationTopMd(const std::string & guid) const;

		DLL_IMPORT_OR_EXPORT bool hasPerforationBaseMd(const std::string & guid) const;

		DLL_IMPORT_OR_EXPORT double getPerforationBaseMd(const std::string & guid) const;

		DLL_IMPORT_OR_EXPORT unsigned int getHistoryEntryCount(const std::string & perforationGuid) const;

		DLL_IMPORT_OR_EXPORT bool hasPerforationHistoryEntryStatus(const std::string & guid,
			const std::string & perforationGuid) const;

		DLL_IMPORT_OR_EXPORT gsoap_eml2_1::witsml2__PerforationStatus getPerforationHistoryEntryStatus(const std::string & guid,
			const std::string & perforationGuid) const;

		DLL_IMPORT_OR_EXPORT std::string getPerforationHistoryEntryStatusToString(const std::string & guid,
			const std::string & perforationGuid) const;

		DLL_IMPORT_OR_EXPORT bool hasPerforationHistoryEntryStartDate(const std::string & guid,
			const std::string & perforationGuid) const;

		DLL_IMPORT_OR_EXPORT time_t getPerforationHistoryEntryStartDate(const std::string & guid,
			const std::string & perforationGuid) const;

		DLL_IMPORT_OR_EXPORT bool hasPerforationHistoryEntryEndDate(const std::string & guid,
			const std::string & perforationGuid) const;

		DLL_IMPORT_OR_EXPORT time_t getPerforationHistoryEntryEndDate(const std::string & guid,
			const std::string & perforationGuid) const;
		
		DLL_IMPORT_OR_EXPORT bool hasPerforationHistoryEntryMdDatum(const std::string & guid,
			const std::string & perforationGuid) const;
		
		DLL_IMPORT_OR_EXPORT std::string getPerforationHistoryEntryMdDatum(const std::string & guid,
			const std::string & perforationGuid) const;
		
		DLL_IMPORT_OR_EXPORT bool hasPerforationHistoryEntryMdUnit(const std::string & guid,
			const std::string & perforationGuid) const;

		DLL_IMPORT_OR_EXPORT gsoap_eml2_1::eml21__LengthUom getPerforationHistoryEntryMdUnit(const std::string & guid,
			const std::string & perforationGuid) const;

		DLL_IMPORT_OR_EXPORT bool hasPerforationHistoryEntryTopMd(const std::string & guid,
			const std::string & perforationGuid) const;

		DLL_IMPORT_OR_EXPORT double getPerforationHistoryEntryTopMd(const std::string & guid,
			const std::string & perforationGuid) const;
		
		DLL_IMPORT_OR_EXPORT bool hasPerforationHistoryEntryBaseMd(const std::string & guid,
			const std::string & perforationGuid) const;

		DLL_IMPORT_OR_EXPORT double getPerforationHistoryEntryBaseMd(const std::string & guid,
			const std::string & perforationGuid) const;

		DLL_IMPORT_OR_EXPORT std::vector<epc::Relationship> getAllTargetRelationships() const;
		DLL_IMPORT_OR_EXPORT void resolveTargetRelationships(COMMON_NS::EpcDocument * epcDoc);

		DLL_IMPORT_OR_EXPORT static const char* XML_TAG;
		DLL_IMPORT_OR_EXPORT virtual std::string getXmlTag() const { return XML_TAG; }

	private:
		gsoap_eml2_1::witsml2__PerforationSetInterval* getPerforation(const std::string & guid) const;

		gsoap_eml2_1::witsml2__PerforationStatusHistory* getPerforationHistoryEntry(const std::string & guid, 
			const std::string & perforationGuid) const;
	};
}