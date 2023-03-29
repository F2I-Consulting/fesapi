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
	/** The location/interval of the connections between well and reservoir and its history. */
	class WellboreCompletion : public WITSML2_NS::WellboreObject
	{
	public:

		/**
		* The physical nature of a connection from reservoir to wellbore
		*/
		enum class WellReservoirConnectionType { PERFORATION = 0, GRAVEL_PACK = 1, OPEN_HOLE = 2, SLOTS = 3};

		/**
		 * Only to be used in partial transfer context
		 *
		 * @param [in,out]	partialObject	If non-null, the partial object.
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
		 * Pushes back a connection
		 *
		 * @param	wellReservoirConnection	The physical nature of the connection from reservoir to wellbore to add
		 * @param 	datum 	The datum.
		 * @param 	MdUnit	The md unit.
		 * @param 	TopMd 	The top md.
		 * @param 	BaseMd	The base md.
		 * @param 	guid  	Unique identifier of the connection.
		 */
		DLL_IMPORT_OR_EXPORT void pushBackConnection(WellReservoirConnectionType wellReservoirConnection, const std::string & datum,
			gsoap_eml2_1::eml21__LengthUom MdUnit,
			double TopMd,
			double BaseMd, 
			const std::string & uid);

		/**
		 * Pushes back connection extra metadata
		 *
		 * @param	wellReservoirConnection	The physical nature of the connection
		 * @param 	connectionIndex The index of the connection in the array of type wellReservoirConnection.
		 * @param 	key  			The key of the metadata.
		 * @param 	value			The value of the metadata.
		 */
		DLL_IMPORT_OR_EXPORT void pushBackConnectionExtraMetadata(WellReservoirConnectionType wellReservoirConnection, uint64_t connectionIndex,
			const std::string & key, const std::string & value);

		/**
		 * Pushes a back perforaconnectiontion history
		 *
		 * @param	wellReservoirConnection	The physical nature of the connection
		 * @param 	connectionIndex The index of the connection in the array of type wellReservoirConnection.
		 * @param 	historyGuid 		(Optional) Unique identifier.
		 */
		DLL_IMPORT_OR_EXPORT void pushBackConnectionHistory(WellReservoirConnectionType wellReservoirConnection, uint64_t connectionIndex,
			const std::string & historyGuid = "");

		/**
		 * Pushes back connection history
		 *
		 * @param	wellReservoirConnection	The physical nature of the connection
		 * @param 	connectionIndex The index of the connection in the array of type wellReservoirConnection.
		 * @param 	status				The connection status.
		 * @param 	startDate		 	The start date.
		 * @param 	historyGuid			 (Optional) Unique identifier.
		 */
		DLL_IMPORT_OR_EXPORT void pushBackConnectionHistory(WellReservoirConnectionType wellReservoirConnection, uint64_t connectionIndex,
			gsoap_eml2_1::witsml20__PhysicalStatus staus,
			time_t startDate,
			const std::string & historyGuid = "");

		/**
		 * Gets connection count of a certin type
		 *
		 * @param	wellReservoirConnection	The physical nature of the connections to count

		 * @returns	The connection count of type wellReservoirConnection in this completion.
		 */
		DLL_IMPORT_OR_EXPORT uint64_t getConnectionCount(WellReservoirConnectionType wellReservoirConnection) const;

		/**
		 * Gets the UID of the connection of a particular type at a particular index
		 *
		 * @param	wellReservoirConnection	The physical nature of the connection
		 * @param 	connectionIndex The index of the connection in the array of type wellReservoirConnection.

		 * @returns	The connection UIDs of the completion.
		 */
		DLL_IMPORT_OR_EXPORT std::string getConnectionUid(WellReservoirConnectionType wellReservoirConnection, uint64_t connectionIndex) const;

		/**
		 * Gets an extra metadata of a particular connection according to its key
		 *
		 * @param	wellReservoirConnection	The physical nature of the connection
		 * @param 	connectionIndex The index of the connection in the array of type wellReservoirConnection.
		 * @param 	key	The key of an extra metadata.
		 *
		 * @returns	The vector of all metadata values sharing this @p key (empty vector if there is no such value) in the connection at @p index.
		 */
		DLL_IMPORT_OR_EXPORT std::vector<std::string> getConnectionExtraMetadata(WellReservoirConnectionType wellReservoirConnection, uint64_t connectionIndex, const std::string & key) const;

		/**
		 * Query if 'index' has connection md datum
		 *
		 * @param	wellReservoirConnection	The physical nature of the connection
		 * @param 	connectionIndex The index of the connection in the array of type wellReservoirConnection.
		 *
		 * @returns	True if connection md datum, false if not.
		 */
		DLL_IMPORT_OR_EXPORT bool hasConnectionMdDatum(WellReservoirConnectionType wellReservoirConnection, uint64_t connectionIndex) const;

		/**
		 * Gets connection md datum
		 *
		 * @param	wellReservoirConnection	The physical nature of the connection
		 * @param 	connectionIndex The index of the connection in the array of type wellReservoirConnection.
		 *
		 * @returns	The connection md datum.
		 */
		DLL_IMPORT_OR_EXPORT std::string getConnectionMdDatum(WellReservoirConnectionType wellReservoirConnection, uint64_t connectionIndex) const;

		/**
		 * Query if 'index' has connection md unit
		 *
		 * @param	wellReservoirConnection	The physical nature of the connection
		 * @param 	connectionIndex The index of the connection in the array of type wellReservoirConnection.
		 *
		 * @returns	True if connection md unit, false if not.
		 */
		DLL_IMPORT_OR_EXPORT bool hasConnectionMdUnit(WellReservoirConnectionType wellReservoirConnection, uint64_t connectionIndex) const;

		/**
		 * Returns md base uom if exists, else returns md top uom. Raises an exception if no md is
		 * defined.
		 *
		 * @param	wellReservoirConnection	The physical nature of the connection
		 * @param 	connectionIndex The index of the connection in the array of type wellReservoirConnection.
		 *
		 * @returns	The connection md unit.
		 */
		DLL_IMPORT_OR_EXPORT gsoap_eml2_1::eml21__LengthUom getConnectionMdUnit(WellReservoirConnectionType wellReservoirConnection, uint64_t connectionIndex) const;

		/**
		 * Returns md base uom (as string) if exists, else returns md top uom (as string). Raises an
		 * exception if no md is defined.
		 *
		 * @param	wellReservoirConnection	The physical nature of the connection
		 * @param 	connectionIndex The index of the connection in the array of type wellReservoirConnection.
		 *
		 * @returns	The connection md unit as string.
		 */
		DLL_IMPORT_OR_EXPORT std::string getConnectionMdUnitAsString(WellReservoirConnectionType wellReservoirConnection, uint64_t connectionIndex) const;

		/**
		 * Query if 'index' has connection top md
		 *
		 * @param 	index	Zero-based index of the.
		 *
		 * @returns	True if connection top md, false if not.
		 */
		DLL_IMPORT_OR_EXPORT bool hasConnectionTopMd(WellReservoirConnectionType wellReservoirConnection, uint64_t connectionIndex) const;

		/**
		 * Gets connection top md
		 *
		 * @param	wellReservoirConnection	The physical nature of the connection
		 * @param 	connectionIndex The index of the connection in the array of type wellReservoirConnection.
		 *
		 * @returns	The connection top md.
		 */
		DLL_IMPORT_OR_EXPORT double getConnectionTopMd(WellReservoirConnectionType wellReservoirConnection, uint64_t connectionIndex) const;

		/**
		 * Query if 'index' has connection base md
		 *
		 * @param 	index	Zero-based index of the.
		 *
		 * @returns	True if connection base md, false if not.
		 */
		DLL_IMPORT_OR_EXPORT bool hasConnectionBaseMd(WellReservoirConnectionType wellReservoirConnection, uint64_t connectionIndex) const;

		/**
		 * Gets connection base md
		 *
		 * @param	wellReservoirConnection	The physical nature of the connection
		 * @param 	connectionIndex The index of the connection in the array of type wellReservoirConnection.
		 *
		 * @returns	The connection base md.
		 */
		DLL_IMPORT_OR_EXPORT double getConnectionBaseMd(WellReservoirConnectionType wellReservoirConnection, uint64_t connectionIndex) const;

		/**
		 * Gets connection history count
		 *
		 * @param	wellReservoirConnection	The physical nature of the connection
		 * @param 	connectionIndex The index of the connection in the array of type wellReservoirConnection.
		 *
		 * @returns	The connection history count.
		 */
		DLL_IMPORT_OR_EXPORT uint64_t getConnectionHistoryCount(WellReservoirConnectionType wellReservoirConnection, uint64_t connectionIndex) const;

		/**
		 * Query if 'historyIndex' has connection history status
		 *
		 * @param 	historyIndex		Zero-based index of the history.
		 * @param	wellReservoirConnection	The physical nature of the connection
		 * @param 	connectionIndex The index of the connection in the array of type wellReservoirConnection.
		 *
		 * @returns	True if connection history status, false if not.
		 */
		DLL_IMPORT_OR_EXPORT bool hasConnectionHistoryStatus(uint64_t historyIndex,
			WellReservoirConnectionType wellReservoirConnection, uint64_t connectionIndex) const;

		/**
		 * Gets connection history status
		 *
		 * @param 	historyIndex		Zero-based index of the history.
		 * @param	wellReservoirConnection	The physical nature of the connection
		 * @param 	connectionIndex The index of the connection in the array of type wellReservoirConnection.
		 *
		 * @returns	The connection history status.
		 */
		DLL_IMPORT_OR_EXPORT gsoap_eml2_1::witsml20__PhysicalStatus getConnectionHistoryStatus(uint64_t historyIndex,
			WellReservoirConnectionType wellReservoirConnection, uint64_t connectionIndex) const;

		/**
		 * Gets connection history status to string
		 *
		 * @param 	historyIndex		Zero-based index of the history.
		 * @param	wellReservoirConnection	The physical nature of the connection
		 * @param 	connectionIndex The index of the connection in the array of type wellReservoirConnection.
		 *
		 * @returns	The connection history status to string.
		 */
		DLL_IMPORT_OR_EXPORT std::string getConnectionHistoryStatusToString(uint64_t historyIndex,
			WellReservoirConnectionType wellReservoirConnection, uint64_t connectionIndex) const;

		/**
		 * Sets connection history status
		 *
		 * @param 	historyIndex	 	Zero-based index of the history.
		 * @param	wellReservoirConnection	The physical nature of the connection
		 * @param 	connectionIndex The index of the connection in the array of type wellReservoirConnection.
		 * @param 	connectionStatus	The connection status.
		 */
		DLL_IMPORT_OR_EXPORT void setConnectionHistoryStatus(uint64_t historyIndex,
			WellReservoirConnectionType wellReservoirConnection, uint64_t connectionIndex, 
			gsoap_eml2_1::witsml20__PhysicalStatus connectionStatus);

		/**
		 * Query if 'historyIndex' has connection history start date
		 *
		 * @param 	historyIndex		Zero-based index of the history.
		 * @param	wellReservoirConnection	The physical nature of the connection
		 * @param 	connectionIndex The index of the connection in the array of type wellReservoirConnection.
		 *
		 * @returns	True if connection history start date, false if not.
		 */
		DLL_IMPORT_OR_EXPORT bool hasConnectionHistoryStartDate(uint64_t historyIndex,
			WellReservoirConnectionType wellReservoirConnection, uint64_t connectionIndex) const;

		/**
		 * Gets connection history start date
		 *
		 * @param 	historyIndex		Zero-based index of the history.
		 * @param	wellReservoirConnection	The physical nature of the connection
		 * @param 	connectionIndex	Zero-based index of the connection.
		 *
		 * @returns	The connection history start date.
		 */
		DLL_IMPORT_OR_EXPORT time_t getConnectionHistoryStartDate(uint64_t historyIndex,
			WellReservoirConnectionType wellReservoirConnection, uint64_t connectionIndex) const;

		/**
		 * Sets connection history start date
		 *
		 * @param 	historyIndex		Zero-based index of the history.
		 * @param	wellReservoirConnection	The physical nature of the connection
		 * @param 	connectionIndex	Zero-based index of the connection.
		 * @param 	startDate			The start date.
		 */
		DLL_IMPORT_OR_EXPORT void setConnectionHistoryStartDate(uint64_t historyIndex,
			WellReservoirConnectionType wellReservoirConnection, uint64_t connectionIndex, time_t startDate) const;

		/**
		 * Query if 'historyIndex' has connection history end date
		 *
		 * @param 	historyIndex		Zero-based index of the history.
		 * @param	wellReservoirConnection	The physical nature of the connection
		 * @param 	connectionIndex	Zero-based index of the connection.
		 *
		 * @returns	True if connection history end date, false if not.
		 */
		DLL_IMPORT_OR_EXPORT bool hasConnectionHistoryEndDate(uint64_t historyIndex,
			WellReservoirConnectionType wellReservoirConnection, uint64_t connectionIndex) const;

		/**
		 * Gets connection history end date
		 *
		 * @param 	historyIndex		Zero-based index of the history.
		 * @param	wellReservoirConnection	The physical nature of the connection
		 * @param 	connectionIndex	Zero-based index of the connection.
		 *
		 * @returns	The connection history end date.
		 */
		DLL_IMPORT_OR_EXPORT time_t getConnectionHistoryEndDate(uint64_t historyIndex,
			WellReservoirConnectionType wellReservoirConnection, uint64_t connectionIndex) const;

		/**
		 * Sets connection history end date
		 *
		 * @param 	historyIndex		Zero-based index of the history.
		 * @param	wellReservoirConnection	The physical nature of the connection
		 * @param 	connectionIndex	Zero-based index of the connection.
		 * @param 	endDate				The end date.
		 */
		DLL_IMPORT_OR_EXPORT void setConnectionHistoryEndDate(uint64_t historyIndex,
			WellReservoirConnectionType wellReservoirConnection, uint64_t connectionIndex, time_t endDate) const;

		/**
		 * Query if 'historyIndex' has connection history md datum
		 *
		 * @param 	historyIndex		Zero-based index of the history.
		 * @param	wellReservoirConnection	The physical nature of the connection
		 * @param 	connectionIndex	Zero-based index of the connection.
		 *
		 * @returns	True if connection history md datum, false if not.
		 */
		DLL_IMPORT_OR_EXPORT bool hasConnectionHistoryMdDatum(uint64_t historyIndex,
			WellReservoirConnectionType wellReservoirConnection, uint64_t connectionIndex) const;

		/**
		 * Gets connection history md datum
		 *
		 * @param 	historyIndex		Zero-based index of the history.
		 * @param	wellReservoirConnection	The physical nature of the connection
		 * @param 	connectionIndex	Zero-based index of the connection.
		 *
		 * @returns	The connection history md datum.
		 */
		DLL_IMPORT_OR_EXPORT std::string getConnectionHistoryMdDatum(uint64_t historyIndex,
			WellReservoirConnectionType wellReservoirConnection, uint64_t connectionIndex) const;

		/**
		 * Query if 'historyIndex' has connection history md unit
		 *
		 * @param 	historyIndex		Zero-based index of the history.
		 * @param	wellReservoirConnection	The physical nature of the connection
		 * @param 	connectionIndex	Zero-based index of the connection.
		 *
		 * @returns	True if connection history md unit, false if not.
		 */
		DLL_IMPORT_OR_EXPORT bool hasConnectionHistoryMdUnit(uint64_t historyIndex,
			WellReservoirConnectionType wellReservoirConnection, uint64_t connectionIndex) const;

		/**
		 * Returns md base uom if exists, else returns md top uom. Raises an exception if no md is
		 * defined.
		 *
		 * @param 	historyIndex		Zero-based index of the history.
		 * @param	wellReservoirConnection	The physical nature of the connection
		 * @param 	connectionIndex	Zero-based index of the connection.
		 *
		 * @returns	The connection history md unit.
		 */
		DLL_IMPORT_OR_EXPORT gsoap_eml2_1::eml21__LengthUom getConnectionHistoryMdUnit(uint64_t historyIndex,
			WellReservoirConnectionType wellReservoirConnection, uint64_t connectionIndex) const;

		/**
		 * Returns md base uom (as string) if exists, else returns md top uom (as string). Raises an
		 * exception if no md is defined.
		 *
		 * @param 	historyIndex		Zero-based index of the history.
		 * @param	wellReservoirConnection	The physical nature of the connection
		 * @param 	connectionIndex	Zero-based index of the connection.
		 *
		 * @returns	The connection history md unit as string.
		 */
		DLL_IMPORT_OR_EXPORT std::string getConnectionHistoryMdUnitAsString(uint64_t historyIndex,
			WellReservoirConnectionType wellReservoirConnection, uint64_t connectionIndex) const;

		/**
		 * Query if 'historyIndex' has connection history top md
		 *
		 * @param 	historyIndex		Zero-based index of the history.
		 * @param	wellReservoirConnection	The physical nature of the connection
		 * @param 	connectionIndex	Zero-based index of the connection.
		 *
		 * @returns	True if connection history top md, false if not.
		 */
		DLL_IMPORT_OR_EXPORT bool hasConnectionHistoryTopMd(uint64_t historyIndex,
			WellReservoirConnectionType wellReservoirConnection, uint64_t connectionIndex) const;

		/**
		 * Gets connection history top md
		 *
		 * @param 	historyIndex		Zero-based index of the history.
		 * @param	wellReservoirConnection	The physical nature of the connection
		 * @param 	connectionIndex	Zero-based index of the connection.
		 *
		 * @returns	The connection history top md.
		 */
		DLL_IMPORT_OR_EXPORT double getConnectionHistoryTopMd(uint64_t historyIndex,
			WellReservoirConnectionType wellReservoirConnection, uint64_t connectionIndex) const;

		/**
		 * Connection history datum is overwritten if exists. For instance if a base md is already
		 * defined.
		 *
		 * @param 	historyIndex		Zero-based index of the history.
		 * @param	wellReservoirConnection	The physical nature of the connection
		 * @param 	connectionIndex	Zero-based index of the connection.
		 * @param 	datum				The datum.
		 * @param 	MdUnit				The md unit.
		 * @param 	TopMd				The top md.
		 */
		DLL_IMPORT_OR_EXPORT void setConnectionHistoryTopMd(uint64_t historyIndex,
			WellReservoirConnectionType wellReservoirConnection, uint64_t connectionIndex,
			const std::string & datum,
			gsoap_eml2_1::eml21__LengthUom MdUnit,
			double TopMd);

		/**
		 * Query if 'historyIndex' has connection history base md
		 *
		 * @param 	historyIndex		Zero-based index of the history.
		 * @param	wellReservoirConnection	The physical nature of the connection
		 * @param 	connectionIndex	Zero-based index of the connection.
		 *
		 * @returns	True if connection history base md, false if not.
		 */
		DLL_IMPORT_OR_EXPORT bool hasConnectionHistoryBaseMd(uint64_t historyIndex,
			WellReservoirConnectionType wellReservoirConnection, uint64_t connectionIndex) const;

		/**
		 * Gets connection history base md
		 *
		 * @param 	historyIndex		Zero-based index of the history.
		 * @param	wellReservoirConnection	The physical nature of the connection
		 * @param 	connectionIndex	Zero-based index of the connection.
		 *
		 * @returns	The connection history base md.
		 */
		DLL_IMPORT_OR_EXPORT double getConnectionHistoryBaseMd(uint64_t historyIndex,
			WellReservoirConnectionType wellReservoirConnection, uint64_t connectionIndex) const;

		/**
		 * Connection history datum is overwritten if exists. For instance if a top md is already
		 * defined.
		 *
		 * @param 	historyIndex		Zero-based index of the history.
		 * @param	wellReservoirConnection	The physical nature of the connection
		 * @param 	connectionIndex	Zero-based index of the connection.
		 * @param 	datum				The datum.
		 * @param 	MdUnit				The md unit.
		 * @param 	BaseMd				The base md.
		 */
		DLL_IMPORT_OR_EXPORT void setConnectionHistoryBaseMd(uint64_t historyIndex,
			WellReservoirConnectionType wellReservoirConnection, uint64_t connectionIndex,
			const std::string & datum,
			gsoap_eml2_1::eml21__LengthUom MdUnit,
			double BaseMd);

		/**
		 * Query if 'historyIndex' has connection history comment
		 *
		 * @param 	historyIndex		Zero-based index of the history.
		 * @param	wellReservoirConnection	The physical nature of the connection
		 * @param 	connectionIndex	Zero-based index of the connection.
		 *
		 * @returns	True if connection history comment, false if not.
		 */
		DLL_IMPORT_OR_EXPORT bool hasConnectionHistoryComment(uint64_t historyIndex,
			WellReservoirConnectionType wellReservoirConnection, uint64_t connectionIndex) const;

		/**
		 * Gets connection history comment
		 *
		 * @param 	historyIndex		Zero-based index of the history.
		 * @param	wellReservoirConnection	The physical nature of the connection
		 * @param 	connectionIndex	Zero-based index of the connection.
		 *
		 * @returns	The connection history comment.
		 */
		DLL_IMPORT_OR_EXPORT std::string getConnectionHistoryComment(uint64_t historyIndex,
			WellReservoirConnectionType wellReservoirConnection, uint64_t connectionIndex) const;

		/**
		 * Sets connection history comment
		 *
		 * @param 	historyIndex		Zero-based index of the history.
		 * @param	wellReservoirConnection	The physical nature of the connection
		 * @param 	connectionIndex	Zero-based index of the connection.
		 * @param 	comment				The comment.
		 */
		DLL_IMPORT_OR_EXPORT void setConnectionHistoryComment(uint64_t historyIndex,
			WellReservoirConnectionType wellReservoirConnection, uint64_t connectionIndex,
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
		void loadTargetRelationships() final;

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
		 * @param 	index  	Zero-based index of the perforation.
		 *
		 * @returns	Null if it fails, else the perforation.
		 */
		gsoap_eml2_1::witsml20__PerforationSetInterval* getPerforation(uint64_t index) const;

		/**
		 * Gets a gravel pack
		 *
		 * @param 	index  	Zero-based index of the gravel pack.
		 *
		 * @returns	Null if it fails, else the gravel pack.
		 */
		gsoap_eml2_1::witsml20__GravelPackInterval* getGravelPack(uint64_t index) const;

		/**
		 * Gets a open hole
		 *
		 * @param 	index  	Zero-based index of the open hole.
		 *
		 * @returns	Null if it fails, else the open hole.
		 */
		gsoap_eml2_1::witsml20__OpenHoleInterval* getOpenHole(uint64_t index) const;

		/**
		 * Gets a slots
		 *
		 * @param 	index  	Zero-based index of the slots.
		 *
		 * @returns	Null if it fails, else the slots.
		 */
		gsoap_eml2_1::witsml20__SlotsInterval* getSlots(uint64_t index) const;

		/**
		 * Gets perforation history entry
		 *
		 * @param 	historyIndex		Zero-based index of the history entry.
		 * @param 	index  	Zero-based index of the perforation.
		 *
		 * @returns	Null if it fails, else the perforation history entry.
		 */
		gsoap_eml2_1::witsml20__PerforationStatusHistory* getPerforationHistoryEntry(uint64_t historyIndex,
			uint64_t index) const {
			return getPerforation(index)->PerforationStatusHistory.at(historyIndex);
		}

		/**
		 * Gets gravel pack history entry
		 *
		 * @param 	historyIndex		Zero-based index of the history entry.
		 * @param 	index  	Zero-based index of the gravel pack.
		 *
		 * @returns	Null if it fails, else the gravel pack history entry.
		 */
		gsoap_eml2_1::witsml20__IntervalStatusHistory* getGravelPackHistoryEntry(uint64_t historyIndex,
			uint64_t index) const {
			return getGravelPack(index)->StatusHistory.at(historyIndex);
		}

		/**
		 * Gets open hole history entry
		 *
		 * @param 	historyIndex		Zero-based index of the history entry.
		 * @param 	index  	Zero-based index of the open hole.
		 *
		 * @returns	Null if it fails, else the open hole history entry.
		 */
		gsoap_eml2_1::witsml20__IntervalStatusHistory* getOpenHoleHistoryEntry(uint64_t historyIndex,
			uint64_t index) const {
			return getOpenHole(index)->StatusHistory.at(historyIndex);
		}

		/**
		 * Gets slots history entry
		 *
		 * @param 	historyIndex		Zero-based index of the history entry.
		 * @param 	perforationIndex  	Zero-based index of the slots.
		 *
		 * @returns	Null if it fails, else the slots history entry.
		 */
		gsoap_eml2_1::witsml20__IntervalStatusHistory* getSlotsHistoryEntry(uint64_t historyIndex,
			uint64_t index) const {
			return getSlots(index)->StatusHistory.at(historyIndex);
		}
	};
}
