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

#include "../witsml2/WellboreObject.h"

namespace WITSML2_0_NS
{
	/** The location/interval of the perforation set and its history. */
	class WellboreCompletion : public WITSML2_NS::WellboreObject
	{
	public:

		/**
		 * Only to be used in partial transfer context
		 *
		 * @param [in,out]	partialObject	If non-null, the partial object.
		 *
		 * 
		 */
		DLL_IMPORT_OR_EXPORT WellboreCompletion(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : WITSML2_NS::WellboreObject(partialObject) {}

		/**
		 * Constructor
		 *
		 * @param [in,out]	witsmlWellbore	  	If non-null, the witsml wellbore.
		 * @param [in,out]	wellCompletion	  	If non-null, the well completion.
		 * @param 		  	guid			  	Unique identifier.
		 * @param 		  	title			  	The title.
		 * @param 		  	wellCompletionName	Name of the well completion.
		 */
		WellboreCompletion(WITSML2_NS::Wellbore* witsmlWellbore,
			class WellCompletion* wellCompletion,
			const std::string & guid,
			const std::string & title,
			const std::string & wellCompletionName);

		/**
		 * Creates an instance of this class by wrapping a gsoap instance.
		 *
		 * @param [in,out]	fromGsoap	If non-null, from gsoap.
		 */
		WellboreCompletion(gsoap_eml2_1::witsml20__WellboreCompletion* fromGsoap) :WellboreObject(fromGsoap) {}

		/** Destructor does nothing since the memory is managed by the gsoap context. */
		~WellboreCompletion() = default;

		/**
		* Get the Data Object Reference of the wellbore linked with this data object.
		*/
		COMMON_NS::DataObjectReference getWellboreDor() const final;

		/**
		* Get the Data Object Reference of the well completion linked with this data object.
		*/
		COMMON_NS::DataObjectReference getWellCompletionDor() const;

		/** Get the well completion linked with this data object */
		DLL_IMPORT_OR_EXPORT class WellCompletion* getWellCompletion() const;

		/**
		 * Set the wellbore linked with this data object
		 *
		 * @param [in,out]	witsmlWellbore	If non-null, the witsml wellbore.
		 */
		DLL_IMPORT_OR_EXPORT void setWellbore(WITSML2_NS::Wellbore* witsmlWellbore) final;

		/**
		 * Set the well completion linked with this data object
		 *
		 * @param [in,out]	wellCompletion	If non-null, the well completion.
		 */
		DLL_IMPORT_OR_EXPORT void setWellCompletion(class WellCompletion* wellCompletion);

		/**
		 * Pushes a back perforation
		 *
		 * @param 	datum 	The datum.
		 * @param 	MdUnit	The md unit.
		 * @param 	TopMd 	The top md.
		 * @param 	BaseMd	The base md.
		 * @param 	guid  	(Optional) Unique identifier.
		 */
		DLL_IMPORT_OR_EXPORT void pushBackPerforation(const std::string & datum,
			gsoap_eml2_1::eml21__LengthUom MdUnit,
			double TopMd,
			double BaseMd, 
			const std::string & guid = "");

		/**
		 * Pushes a back perforation history
		 *
		 * @param 	index	Zero-based index of the.
		 * @param 	guid 	(Optional) Unique identifier.
		 */
		DLL_IMPORT_OR_EXPORT void pushBackPerforationHistory(unsigned int index,
			const std::string & guid = "");

		/**
		 * Pushes a back perforation history
		 *
		 * @param 	index			 	Zero-based index of the.
		 * @param 	perforationStatus	The perforation status.
		 * @param 	startDate		 	The start date.
		 * @param 	guid			 	(Optional) Unique identifier.
		 */
		DLL_IMPORT_OR_EXPORT void pushBackPerforationHistory(unsigned int index,
			gsoap_eml2_1::witsml20__PerforationStatus perforationStatus,
			time_t startDate,
			const std::string & guid = "");

		/**
		 * Gets perforation count
		 *
		 * @returns	The perforation count.
		 */
		DLL_IMPORT_OR_EXPORT unsigned int getPerforationCount() const;

		/**
		 * Gets perforation UID
		 *
		 * @param 	index	Zero-based index of the.
		 *
		 * @returns	The perforation UID.
		 */
		DLL_IMPORT_OR_EXPORT std::string getPerforationUid(unsigned int index) const;

		/**
		 * Query if 'index' has perforation md datum
		 *
		 * @param 	index	Zero-based index of the.
		 *
		 * @returns	True if perforation md datum, false if not.
		 */
		DLL_IMPORT_OR_EXPORT bool hasPerforationMdDatum(unsigned int index) const;

		/**
		 * Gets perforation md datum
		 *
		 * @param 	index	Zero-based index of the.
		 *
		 * @returns	The perforation md datum.
		 */
		DLL_IMPORT_OR_EXPORT std::string getPerforationMdDatum(unsigned int index) const;

		/**
		 * Query if 'index' has perforation md unit
		 *
		 * @param 	index	Zero-based index of the.
		 *
		 * @returns	True if perforation md unit, false if not.
		 */
		DLL_IMPORT_OR_EXPORT bool hasPerforationMdUnit(unsigned int index) const;

		/**
		 * Returns md base uom if exists, else returns md top uom. Raises an exception if no md is
		 * defined.
		 *
		 * @param 	index	Zero-based index of the.
		 *
		 * @returns	The perforation md unit.
		 */
		DLL_IMPORT_OR_EXPORT gsoap_eml2_1::eml21__LengthUom getPerforationMdUnit(unsigned int index) const;

		/**
		 * Returns md base uom (as string) if exists, else returns md top uom (as string). Raises an
		 * exception if no md is defined.
		 *
		 * @param 	index	Zero-based index of the.
		 *
		 * @returns	The perforation md unit as string.
		 */
		DLL_IMPORT_OR_EXPORT std::string getPerforationMdUnitAsString(unsigned int index) const;

		/**
		 * Query if 'index' has perforation top md
		 *
		 * @param 	index	Zero-based index of the.
		 *
		 * @returns	True if perforation top md, false if not.
		 */
		DLL_IMPORT_OR_EXPORT bool hasPerforationTopMd(unsigned int index) const;

		/**
		 * Gets perforation top md
		 *
		 * @param 	index	Zero-based index of the.
		 *
		 * @returns	The perforation top md.
		 */
		DLL_IMPORT_OR_EXPORT double getPerforationTopMd(unsigned int index) const;

		/**
		 * Query if 'index' has perforation base md
		 *
		 * @param 	index	Zero-based index of the.
		 *
		 * @returns	True if perforation base md, false if not.
		 */
		DLL_IMPORT_OR_EXPORT bool hasPerforationBaseMd(unsigned int index) const;

		/**
		 * Gets perforation base md
		 *
		 * @param 	index	Zero-based index of the.
		 *
		 * @returns	The perforation base md.
		 */
		DLL_IMPORT_OR_EXPORT double getPerforationBaseMd(unsigned int index) const;

		/**
		 * Gets perforation history count
		 *
		 * @param 	index	Zero-based index of the.
		 *
		 * @returns	The perforation history count.
		 */
		DLL_IMPORT_OR_EXPORT unsigned int getPerforationHistoryCount(unsigned int index) const;

		/**
		 * Query if 'historyIndex' has perforation history status
		 *
		 * @param 	historyIndex		Zero-based index of the history.
		 * @param 	perforationIndex	Zero-based index of the perforation.
		 *
		 * @returns	True if perforation history status, false if not.
		 */
		DLL_IMPORT_OR_EXPORT bool hasPerforationHistoryStatus(unsigned int historyIndex,
			unsigned int perforationIndex) const;

		/**
		 * Gets perforation history status
		 *
		 * @param 	historyIndex		Zero-based index of the history.
		 * @param 	perforationIndex	Zero-based index of the perforation.
		 *
		 * @returns	The perforation history status.
		 */
		DLL_IMPORT_OR_EXPORT gsoap_eml2_1::witsml20__PerforationStatus getPerforationHistoryStatus(unsigned int historyIndex,
			unsigned int perforationIndex) const;

		/**
		 * Gets perforation history status to string
		 *
		 * @param 	historyIndex		Zero-based index of the history.
		 * @param 	perforationIndex	Zero-based index of the perforation.
		 *
		 * @returns	The perforation history status to string.
		 */
		DLL_IMPORT_OR_EXPORT std::string getPerforationHistoryStatusToString(unsigned int historyIndex,
			unsigned int perforationIndex) const;

		/**
		 * Sets perforation history status
		 *
		 * @param 	historyIndex	 	Zero-based index of the history.
		 * @param 	perforationIndex 	Zero-based index of the perforation.
		 * @param 	perforationStatus	The perforation status.
		 */
		DLL_IMPORT_OR_EXPORT void setPerforationHistoryStatus(unsigned int historyIndex,
			unsigned int perforationIndex, 
			gsoap_eml2_1::witsml20__PerforationStatus perforationStatus);

		/**
		 * Query if 'historyIndex' has perforation history start date
		 *
		 * @param 	historyIndex		Zero-based index of the history.
		 * @param 	perforationIndex	Zero-based index of the perforation.
		 *
		 * @returns	True if perforation history start date, false if not.
		 */
		DLL_IMPORT_OR_EXPORT bool hasPerforationHistoryStartDate(unsigned int historyIndex,
			unsigned int perforationIndex) const;

		/**
		 * Gets perforation history start date
		 *
		 * @param 	historyIndex		Zero-based index of the history.
		 * @param 	perforationIndex	Zero-based index of the perforation.
		 *
		 * @returns	The perforation history start date.
		 */
		DLL_IMPORT_OR_EXPORT time_t getPerforationHistoryStartDate(unsigned int historyIndex,
			unsigned int perforationIndex) const;

		/**
		 * Sets perforation history start date
		 *
		 * @param 	historyIndex		Zero-based index of the history.
		 * @param 	perforationIndex	Zero-based index of the perforation.
		 * @param 	startDate			The start date.
		 */
		DLL_IMPORT_OR_EXPORT void setPerforationHistoryStartDate(unsigned int historyIndex,
			unsigned int perforationIndex, time_t startDate) const;

		/**
		 * Query if 'historyIndex' has perforation history end date
		 *
		 * @param 	historyIndex		Zero-based index of the history.
		 * @param 	perforationIndex	Zero-based index of the perforation.
		 *
		 * @returns	True if perforation history end date, false if not.
		 */
		DLL_IMPORT_OR_EXPORT bool hasPerforationHistoryEndDate(unsigned int historyIndex,
			unsigned int perforationIndex) const;

		/**
		 * Gets perforation history end date
		 *
		 * @param 	historyIndex		Zero-based index of the history.
		 * @param 	perforationIndex	Zero-based index of the perforation.
		 *
		 * @returns	The perforation history end date.
		 */
		DLL_IMPORT_OR_EXPORT time_t getPerforationHistoryEndDate(unsigned int historyIndex,
			unsigned int perforationIndex) const;

		/**
		 * Sets perforation history end date
		 *
		 * @param 	historyIndex		Zero-based index of the history.
		 * @param 	perforationIndex	Zero-based index of the perforation.
		 * @param 	endDate				The end date.
		 */
		DLL_IMPORT_OR_EXPORT void setPerforationHistoryEndDate(unsigned int historyIndex,
			unsigned int perforationIndex, time_t endDate) const;

		/**
		 * Query if 'historyIndex' has perforation history md datum
		 *
		 * @param 	historyIndex		Zero-based index of the history.
		 * @param 	perforationIndex	Zero-based index of the perforation.
		 *
		 * @returns	True if perforation history md datum, false if not.
		 */
		DLL_IMPORT_OR_EXPORT bool hasPerforationHistoryMdDatum(unsigned int historyIndex,
			unsigned int perforationIndex) const;

		/**
		 * Gets perforation history md datum
		 *
		 * @param 	historyIndex		Zero-based index of the history.
		 * @param 	perforationIndex	Zero-based index of the perforation.
		 *
		 * @returns	The perforation history md datum.
		 */
		DLL_IMPORT_OR_EXPORT std::string getPerforationHistoryMdDatum(unsigned int historyIndex,
			unsigned int perforationIndex) const;

		/**
		 * Query if 'historyIndex' has perforation history md unit
		 *
		 * @param 	historyIndex		Zero-based index of the history.
		 * @param 	perforationIndex	Zero-based index of the perforation.
		 *
		 * @returns	True if perforation history md unit, false if not.
		 */
		DLL_IMPORT_OR_EXPORT bool hasPerforationHistoryMdUnit(unsigned int historyIndex,
			unsigned int perforationIndex) const;

		/**
		 * Returns md base uom if exists, else returns md top uom. Raises an exception if no md is
		 * defined.
		 *
		 * @param 	historyIndex		Zero-based index of the history.
		 * @param 	perforationIndex	Zero-based index of the perforation.
		 *
		 * @returns	The perforation history md unit.
		 */
		DLL_IMPORT_OR_EXPORT gsoap_eml2_1::eml21__LengthUom getPerforationHistoryMdUnit(unsigned int historyIndex,
			unsigned int perforationIndex) const;

		/**
		 * Returns md base uom (as string) if exists, else returns md top uom (as string). Raises an
		 * exception if no md is defined.
		 *
		 * @param 	historyIndex		Zero-based index of the history.
		 * @param 	perforationIndex	Zero-based index of the perforation.
		 *
		 * @returns	The perforation history md unit as string.
		 */
		DLL_IMPORT_OR_EXPORT std::string getPerforationHistoryMdUnitAsString(unsigned int historyIndex,
			unsigned int perforationIndex) const;

		/**
		 * Query if 'historyIndex' has perforation history top md
		 *
		 * @param 	historyIndex		Zero-based index of the history.
		 * @param 	perforationIndex	Zero-based index of the perforation.
		 *
		 * @returns	True if perforation history top md, false if not.
		 */
		DLL_IMPORT_OR_EXPORT bool hasPerforationHistoryTopMd(unsigned int historyIndex,
			unsigned int perforationIndex) const;

		/**
		 * Gets perforation history top md
		 *
		 * @param 	historyIndex		Zero-based index of the history.
		 * @param 	perforationIndex	Zero-based index of the perforation.
		 *
		 * @returns	The perforation history top md.
		 */
		DLL_IMPORT_OR_EXPORT double getPerforationHistoryTopMd(unsigned int historyIndex,
			unsigned int perforationIndex) const;

		/**
		 * Perforation history datum is overwritten if exists. For instance if a base md is already
		 * defined.
		 *
		 * @param 	historyIndex		Zero-based index of the history.
		 * @param 	perforationIndex	Zero-based index of the perforation.
		 * @param 	datum				The datum.
		 * @param 	MdUnit				The md unit.
		 * @param 	TopMd				The top md.
		 */
		DLL_IMPORT_OR_EXPORT void setPerforationHistoryTopMd(unsigned int historyIndex,
			unsigned int perforationIndex,
			const std::string & datum,
			gsoap_eml2_1::eml21__LengthUom MdUnit,
			double TopMd);

		/**
		 * Query if 'historyIndex' has perforation history base md
		 *
		 * @param 	historyIndex		Zero-based index of the history.
		 * @param 	perforationIndex	Zero-based index of the perforation.
		 *
		 * @returns	True if perforation history base md, false if not.
		 */
		DLL_IMPORT_OR_EXPORT bool hasPerforationHistoryBaseMd(unsigned int historyIndex,
			unsigned int perforationIndex) const;

		/**
		 * Gets perforation history base md
		 *
		 * @param 	historyIndex		Zero-based index of the history.
		 * @param 	perforationIndex	Zero-based index of the perforation.
		 *
		 * @returns	The perforation history base md.
		 */
		DLL_IMPORT_OR_EXPORT double getPerforationHistoryBaseMd(unsigned int historyIndex,
			unsigned int perforationIndex) const;

		/**
		 * Perforation history datum is overwritten if exists. For instance if a top md is already
		 * defined.
		 *
		 * @param 	historyIndex		Zero-based index of the history.
		 * @param 	perforationIndex	Zero-based index of the perforation.
		 * @param 	datum				The datum.
		 * @param 	MdUnit				The md unit.
		 * @param 	BaseMd				The base md.
		 */
		DLL_IMPORT_OR_EXPORT void setPerforationHistoryBaseMd(unsigned int historyIndex,
			unsigned int perforationIndex,
			const std::string & datum,
			gsoap_eml2_1::eml21__LengthUom MdUnit,
			double BaseMd);

		/**
		 * Query if 'historyIndex' has perforation history comment
		 *
		 * @param 	historyIndex		Zero-based index of the history.
		 * @param 	perforationIndex	Zero-based index of the perforation.
		 *
		 * @returns	True if perforation history comment, false if not.
		 */
		DLL_IMPORT_OR_EXPORT bool hasPerforationHistoryComment(unsigned int historyIndex,
			unsigned int perforationIndex) const;

		/**
		 * Gets perforation history comment
		 *
		 * @param 	historyIndex		Zero-based index of the history.
		 * @param 	perforationIndex	Zero-based index of the perforation.
		 *
		 * @returns	The perforation history comment.
		 */
		DLL_IMPORT_OR_EXPORT std::string getPerforationHistoryComment(unsigned int historyIndex,
			unsigned int perforationIndex) const;

		/**
		 * Sets perforation history comment
		 *
		 * @param 	historyIndex		Zero-based index of the history.
		 * @param 	perforationIndex	Zero-based index of the perforation.
		 * @param 	comment				The comment.
		 */
		DLL_IMPORT_OR_EXPORT void setPerforationHistoryComment(unsigned int historyIndex,
			unsigned int perforationIndex,
			const std::string & comment);				

		/**
		 * The standard XML tag without XML namespace for serializing this data object.
		 *
		 * @returns	The XML tag.
		 */
		DLL_IMPORT_OR_EXPORT static constexpr char const* XML_TAG = "WellboreCompletion";

		/**
		 * Get the standard XML tag without XML namespace for serializing this data object.
		 *
		 * @returns	The XML tag.
		 */
		DLL_IMPORT_OR_EXPORT virtual std::string getXmlTag() const { return XML_TAG; }

		/**
		* Resolve all relationships of the object in an epc document.
		*/
		void loadTargetRelationships();

		/**
		* The standard XML namespace for serializing this data object.
		*/
		DLL_IMPORT_OR_EXPORT static constexpr char const* XML_NS = "witsml20";

		/**
		* Get the standard XML namespace for serializing this data object.
		*/
		DLL_IMPORT_OR_EXPORT std::string getXmlNamespace() const final { return XML_NS; }

	private:

		/**
		 * Gets a perforation
		 *
		 * @param 	index	Zero-based index of the.
		 *
		 * @returns	Null if it fails, else the perforation.
		 */
		gsoap_eml2_1::witsml20__PerforationSetInterval* getPerforation(unsigned int index) const;

		/**
		 * Gets perforation history entry
		 *
		 * @param 	index				Zero-based index of the.
		 * @param 	perforationIndex	Zero-based index of the perforation.
		 *
		 * @returns	Null if it fails, else the perforation history entry.
		 */
		gsoap_eml2_1::witsml20__PerforationStatusHistory* getPerforationHistoryEntry(unsigned int index,
			unsigned int perforationIndex) const;
	};
}
