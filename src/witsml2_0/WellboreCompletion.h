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

#include "WellboreObject.h"

namespace WITSML2_0_NS
{
	/**
	* The location/interval of the perforation set and its history.
	*/
	class WellboreCompletion : public WITSML2_0_NS::WellboreObject
	{
	public:

		/**
		* Only to be used in partial transfer context
		*/
		DLL_IMPORT_OR_EXPORT WellboreCompletion(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : WITSML2_0_NS::WellboreObject(partialObject) {}

		/**
		* Constructor
		*/
		WellboreCompletion(class Wellbore* witsmlWellbore,
			class WellCompletion* wellCompletion,
			const std::string & guid,
			const std::string & title,
			const std::string & wellCompletionName);
	
		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		WellboreCompletion(gsoap_eml2_1::witsml20__WellboreCompletion* fromGsoap) :WellboreObject(fromGsoap) {}

		/**
		* Destructor does nothing since the memory is managed by the gsoap context.
		*/
		~WellboreCompletion() {}

		/**
		* Get the Data Object Reference of the wellbore linked with this data object.
		*/
		gsoap_eml2_1::eml21__DataObjectReference* getWellboreDor() const;

		/**
		* Get the Data Object Reference of the well completion linked with this data object.
		*/
		gsoap_eml2_1::eml21__DataObjectReference* getWellCompletionDor() const;

		/**
		* Get the well completion linked with this data object
		*/
		DLL_IMPORT_OR_EXPORT class WellCompletion* getWellCompletion() const;

		/**
		* Set the wellbore linked with this data object
		*/
		DLL_IMPORT_OR_EXPORT void setWellbore(class Wellbore* witsmlWellbore);
		
		/**
		* Set the well completion linked with this data object
		*/
		DLL_IMPORT_OR_EXPORT void setWellCompletion(class WellCompletion* wellCompletion);

		DLL_IMPORT_OR_EXPORT void pushBackPerforation(const std::string & datum,
			gsoap_eml2_1::eml21__LengthUom MdUnit,
			double TopMd,
			double BaseMd, 
			const std::string & guid = "");

		DLL_IMPORT_OR_EXPORT void pushBackPerforationHistory(unsigned int index,
			const std::string & guid = "");

		DLL_IMPORT_OR_EXPORT void pushBackPerforationHistory(unsigned int index,
			gsoap_eml2_1::witsml20__PerforationStatus perforationStatus,
			time_t startDate,
			const std::string & guid = "");

		DLL_IMPORT_OR_EXPORT unsigned int getPerforationCount() const;

		DLL_IMPORT_OR_EXPORT std::string getPerforationUid(unsigned int index) const;

		DLL_IMPORT_OR_EXPORT bool hasPerforationMdDatum(unsigned int index) const;
	
		DLL_IMPORT_OR_EXPORT std::string getPerforationMdDatum(unsigned int index) const;
		
		DLL_IMPORT_OR_EXPORT bool hasPerforationMdUnit(unsigned int index) const;
		
		/**
		* Returns md base uom if exists, else returns md top uom. Raises an exception if no md is defined. 
		*/
		DLL_IMPORT_OR_EXPORT gsoap_eml2_1::eml21__LengthUom getPerforationMdUnit(unsigned int index) const;

		/**
		* Returns md base uom (as string) if exists, else returns md top uom (as string). Raises an exception if no md is defined.
		*/
		DLL_IMPORT_OR_EXPORT std::string getPerforationMdUnitAsString(unsigned int index) const;
		
		DLL_IMPORT_OR_EXPORT bool hasPerforationTopMd(unsigned int index) const;
		
		DLL_IMPORT_OR_EXPORT double getPerforationTopMd(unsigned int index) const;

		DLL_IMPORT_OR_EXPORT bool hasPerforationBaseMd(unsigned int index) const;

		DLL_IMPORT_OR_EXPORT double getPerforationBaseMd(unsigned int index) const;

		DLL_IMPORT_OR_EXPORT unsigned int getPerforationHistoryCount(unsigned int index) const;

		DLL_IMPORT_OR_EXPORT bool hasPerforationHistoryStatus(unsigned int historyIndex,
			unsigned int perforationIndex) const;

		DLL_IMPORT_OR_EXPORT gsoap_eml2_1::witsml20__PerforationStatus getPerforationHistoryStatus(unsigned int historyIndex,
			unsigned int perforationIndex) const;

		DLL_IMPORT_OR_EXPORT std::string getPerforationHistoryStatusToString(unsigned int historyIndex,
			unsigned int perforationIndex) const;

		DLL_IMPORT_OR_EXPORT void setPerforationHistoryStatus(unsigned int historyIndex,
			unsigned int perforationIndex, 
			gsoap_eml2_1::witsml20__PerforationStatus perforationStatus);

		DLL_IMPORT_OR_EXPORT bool hasPerforationHistoryStartDate(unsigned int historyIndex,
			unsigned int perforationIndex) const;

		DLL_IMPORT_OR_EXPORT time_t getPerforationHistoryStartDate(unsigned int historyIndex,
			unsigned int perforationIndex) const;

		DLL_IMPORT_OR_EXPORT void setPerforationHistoryStartDate(unsigned int historyIndex,
			unsigned int perforationIndex, time_t startDate) const;

		DLL_IMPORT_OR_EXPORT bool hasPerforationHistoryEndDate(unsigned int historyIndex,
			unsigned int perforationIndex) const;

		DLL_IMPORT_OR_EXPORT time_t getPerforationHistoryEndDate(unsigned int historyIndex,
			unsigned int perforationIndex) const;

		DLL_IMPORT_OR_EXPORT void setPerforationHistoryEndDate(unsigned int historyIndex,
			unsigned int perforationIndex, time_t endDate) const;
		
		DLL_IMPORT_OR_EXPORT bool hasPerforationHistoryMdDatum(unsigned int historyIndex,
			unsigned int perforationIndex) const;
		
		DLL_IMPORT_OR_EXPORT std::string getPerforationHistoryMdDatum(unsigned int historyIndex,
			unsigned int perforationIndex) const;
		
		DLL_IMPORT_OR_EXPORT bool hasPerforationHistoryMdUnit(unsigned int historyIndex,
			unsigned int perforationIndex) const;

		/**
		* Returns md base uom if exists, else returns md top uom. Raises an exception if no md is defined.
		*/
		DLL_IMPORT_OR_EXPORT gsoap_eml2_1::eml21__LengthUom getPerforationHistoryMdUnit(unsigned int historyIndex,
			unsigned int perforationIndex) const;

		/**
		* Returns md base uom (as string) if exists, else returns md top uom (as string). Raises an exception if no md is defined.
		*/
		DLL_IMPORT_OR_EXPORT std::string getPerforationHistoryMdUnitAsString(unsigned int historyIndex,
			unsigned int perforationIndex) const;

		DLL_IMPORT_OR_EXPORT bool hasPerforationHistoryTopMd(unsigned int historyIndex,
			unsigned int perforationIndex) const;

		DLL_IMPORT_OR_EXPORT double getPerforationHistoryTopMd(unsigned int historyIndex,
			unsigned int perforationIndex) const;

		/**
		* Perforation history datum is overwritten if exists. For instance if a base md is already defined.
		*/
		DLL_IMPORT_OR_EXPORT void setPerforationHistoryTopMd(unsigned int historyIndex,
			unsigned int perforationIndex,
			const std::string & datum,
			gsoap_eml2_1::eml21__LengthUom MdUnit,
			double TopMd);
		
		DLL_IMPORT_OR_EXPORT bool hasPerforationHistoryBaseMd(unsigned int historyIndex,
			unsigned int perforationIndex) const;

		DLL_IMPORT_OR_EXPORT double getPerforationHistoryBaseMd(unsigned int historyIndex,
			unsigned int perforationIndex) const;

		/**
		* Perforation history datum is overwritten if exists. For instance if a top md is already defined.
		*/
		DLL_IMPORT_OR_EXPORT void setPerforationHistoryBaseMd(unsigned int historyIndex,
			unsigned int perforationIndex,
			const std::string & datum,
			gsoap_eml2_1::eml21__LengthUom MdUnit,
			double BaseMd);
			
		DLL_IMPORT_OR_EXPORT bool hasPerforationHistoryComment(unsigned int historyIndex,
			unsigned int perforationIndex) const;

		DLL_IMPORT_OR_EXPORT std::string getPerforationHistoryComment(unsigned int historyIndex,
			unsigned int perforationIndex) const;

		DLL_IMPORT_OR_EXPORT void setPerforationHistoryComment(unsigned int historyIndex,
			unsigned int perforationIndex,
			const std::string & comment);				

		/**
		* The standard XML tag without XML namespace for serializing this data object.
		*/
		DLL_IMPORT_OR_EXPORT static const char* XML_TAG;

		/**
		* Get the standard XML tag without XML namespace for serializing this data object.
		*/
		DLL_IMPORT_OR_EXPORT virtual std::string getXmlTag() const { return XML_TAG; }

		/**
		* Resolve all relationships of the object in an epc document.
		*/
		void loadTargetRelationships();

	private:
		gsoap_eml2_1::witsml20__PerforationSetInterval* getPerforation(unsigned int index) const;

		gsoap_eml2_1::witsml20__PerforationStatusHistory* getPerforationHistoryEntry(unsigned int index,
			unsigned int perforationIndex) const;
	};
}
