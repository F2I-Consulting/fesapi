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
%{
#include "../src/witsml2_0/Channel.h"
#include "../src/witsml2_0/ChannelSet.h"
#include "../src/witsml2_0/Log.h"
#include "../src/witsml2_0/Trajectory.h"
#include "../src/witsml2_0/Well.h"
#include "../src/witsml2_0/Wellbore.h"
#include "../src/witsml2_0/WellboreCompletion.h"
#include "../src/witsml2_0/WellboreGeometry.h"
#include "../src/witsml2_0/WellboreMarker.h"
#include "../src/witsml2_0/WellCompletion.h"
%}

#define GETTER_AND_SETTER_GENERIC_ATTRIBUTE(attributeDatatype, attributeName)\
	void set##attributeName(const attributeDatatype & value);\
	attributeDatatype get##attributeName() const;
#define GETTER_PRESENCE_ATTRIBUTE(attributeName) bool has##attributeName() const;
#define GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE(attributeDatatype, attributeName)\
	GETTER_AND_SETTER_GENERIC_ATTRIBUTE(attributeDatatype, attributeName)\
	GETTER_PRESENCE_ATTRIBUTE(attributeName)

#define GETTER_AND_SETTER_MEASURE_ATTRIBUTE(attributeName, uomDatatype)\
	void set##attributeName(double value, uomDatatype uom);\
	double get##attributeName##Value() const;\
	uomDatatype get##attributeName##Uom() const;
#define GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE(attributeName, uomDatatype)\
	GETTER_AND_SETTER_MEASURE_ATTRIBUTE(attributeName, uomDatatype)\
	GETTER_PRESENCE_ATTRIBUTE(attributeName)

#define GETTER_AND_SETTER_DEPTH_MEASURE_ATTRIBUTE(attributeName, uomDatatype)\
	void set##attributeName(double value, uomDatatype uom, const std::string & datum);\
	double get##attributeName##Value() const;\
	uomDatatype get##attributeName##Uom() const;\
	std::string get##attributeName##Datum() const;
#define GETTER_AND_SETTER_DEPTH_MEASURE_OPTIONAL_ATTRIBUTE(attributeName, uomDatatype)\
	GETTER_AND_SETTER_DEPTH_MEASURE_ATTRIBUTE(attributeName, uomDatatype)\
	GETTER_PRESENCE_ATTRIBUTE(attributeName)

#define GETTER_AND_SETTER_GENERIC_ATTRIBUTE_IN_VECTOR(attributeDatatype, vectorName, attributeName)\
	void set##vectorName##attributeName(unsigned int index, const attributeDatatype & value);\
	attributeDatatype get##vectorName##attributeName(unsigned int index) const;	
	
#define GETTER_AND_SETTER_MEASURE_ATTRIBUTE_IN_VECTOR(vectorName, attributeName, uomDatatype)\
	void set##vectorName##attributeName(unsigned int index, double value, uomDatatype uom);\
	double get##vectorName##attributeName##Value(unsigned int index) const;\
	uomDatatype get##vectorName##attributeName##Uom(unsigned int index) const;

#define GETTER_PRESENCE_ATTRIBUTE_IN_VECTOR(vectorName, attributeName) bool has##vectorName##attributeName(unsigned int index) const;	
#define GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IN_VECTOR(attributeDatatype, vectorName, attributeName)\
	GETTER_AND_SETTER_GENERIC_ATTRIBUTE_IN_VECTOR(attributeDatatype, vectorName, attributeName)\
	GETTER_PRESENCE_ATTRIBUTE_IN_VECTOR(vectorName, attributeName)	
	
#define GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IN_VECTOR(vectorName, attributeName, uomDatatype)\
	GETTER_AND_SETTER_MEASURE_ATTRIBUTE_IN_VECTOR(vectorName, attributeName, uomDatatype)\
	GETTER_PRESENCE_ATTRIBUTE_IN_VECTOR(vectorName, attributeName)
	
#define GETTER_AND_SETTER_DEPTH_MEASURE_ATTRIBUTE_IN_VECTOR(vectorName, attributeName, uomDatatype)\
	void set##vectorName##attributeName(unsigned int index, double value, uomDatatype uom, const std::string & datum);\
	double get##vectorName##attributeName##Value(unsigned int index) const;\
	uomDatatype get##vectorName##attributeName##Uom(unsigned int index) const;\
	std::string get##vectorName##attributeName##Datum(unsigned int index) const;
#define GETTER_AND_SETTER_DEPTH_MEASURE_OPTIONAL_ATTRIBUTE_IN_VECTOR(vectorName, attributeName, uomDatatype)\
	GETTER_AND_SETTER_DEPTH_MEASURE_ATTRIBUTE_IN_VECTOR(vectorName, attributeName, uomDatatype)\
	GETTER_PRESENCE_ATTRIBUTE_IN_VECTOR(vectorName, attributeName)

#if defined(SWIGJAVA) || defined(SWIGCSHARP)	
	%nspace WITSML2_0_NS::Channel;
	%nspace WITSML2_0_NS::ChannelSet;
	%nspace WITSML2_0_NS::Log;
	%nspace WITSML2_0_NS::Trajectory;
	%nspace WITSML2_0_NS::Well;
	%nspace WITSML2_0_NS::Wellbore;	
	%nspace WITSML2_0_NS::WellboreCompletion;
	%nspace WITSML2_0_NS::WellboreGeometry;	
	%nspace WITSML2_0_NS::WellboreMarker;
	%nspace WITSML2_0_NS::WellCompletion;
#endif

namespace WITSML2_0_NS
{
	%nodefaultctor; // Disable creation of default constructors
	
#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(Witsml20_Well) Well;
#endif	
	class Well : public WITSML2_NS::Well
	{
	public:
	};
	
#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(Witsml20_Wellbore) Wellbore;
#endif
	class Wellbore : public WITSML2_NS::Wellbore 
	{
	public:
	};
	
#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(Witsml20_WellCompletion) WellCompletion;
#endif
	class WellCompletion : public COMMON_NS::AbstractObject
	{
	public:		
		Well* getWell() const;
		void setWell(Well* witsmlWell);
	};
		
#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(Witsml20_WellboreCompletion) WellboreCompletion;
#endif
	/** The location/interval of the connections between well and reservoir and its history. */
	class WellboreCompletion : public WITSML2_NS::WellboreObject
	{
	public:

		// The physical nature of a connection from reservoir to wellbore
		enum class WellReservoirConnectionType { PERFORATION = 0, GRAVEL_PACK = 1, OPEN_HOLE = 2, SLOTS = 3};
		
		WellCompletion* getWellCompletion() const;
		void setWellCompletion(WellCompletion* wellCompletion);
		
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
		void pushBackConnection(WellReservoirConnectionType wellReservoirConnection, const std::string & datum,
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
		void pushBackConnectionExtraMetadata(WellReservoirConnectionType wellReservoirConnection, uint64_t connectionIndex,
			const std::string & key, const std::string & value);

		/**
		 * Pushes a back perforaconnectiontion history
		 *
		 * @param	wellReservoirConnection	The physical nature of the connection
		 * @param 	connectionIndex The index of the connection in the array of type wellReservoirConnection.
		 * @param 	historyGuid 		(Optional) Unique identifier.
		 */
		void pushBackConnectionHistory(WellReservoirConnectionType wellReservoirConnection, uint64_t connectionIndex,
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
		void pushBackConnectionHistory(WellReservoirConnectionType wellReservoirConnection, uint64_t connectionIndex,
			gsoap_eml2_1::witsml20__PhysicalStatus staus,
			time_t startDate,
			const std::string & historyGuid = "");

		/**
		 * Gets connection count of a certin type
		 *
		 * @param	wellReservoirConnection	The physical nature of the connections to count

		 * @returns	The connection count of type wellReservoirConnection in this completion.
		 */
		uint64_t getConnectionCount(WellReservoirConnectionType wellReservoirConnection) const;

		/**
		 * Gets the UID of the connection of a particular type at a particular index
		 *
		 * @param	wellReservoirConnection	The physical nature of the connection
		 * @param 	connectionIndex The index of the connection in the array of type wellReservoirConnection.

		 * @returns	The connection UIDs of the completion.
		 */
		std::string getConnectionUid(WellReservoirConnectionType wellReservoirConnection, uint64_t connectionIndex) const;

		/**
		 * Gets an extra metadata of a particular connection according to its key
		 *
		 * @param	wellReservoirConnection	The physical nature of the connection
		 * @param 	connectionIndex The index of the connection in the array of type wellReservoirConnection.
		 * @param 	key	The key of an extra metadata.
		 *
		 * @returns	The vector of all metadata values sharing this @p key (empty vector if there is no such value) in the connection at @p index.
		 */
		std::vector<std::string> getConnectionExtraMetadata(WellReservoirConnectionType wellReservoirConnection, uint64_t connectionIndex, const std::string & key) const;

		/**
		 * Query if 'index' has connection md datum
		 *
		 * @param	wellReservoirConnection	The physical nature of the connection
		 * @param 	connectionIndex The index of the connection in the array of type wellReservoirConnection.
		 *
		 * @returns	True if connection md datum, false if not.
		 */
		bool hasConnectionMdDatum(WellReservoirConnectionType wellReservoirConnection, uint64_t connectionIndex) const;

		/**
		 * Gets connection md datum
		 *
		 * @param	wellReservoirConnection	The physical nature of the connection
		 * @param 	connectionIndex The index of the connection in the array of type wellReservoirConnection.
		 *
		 * @returns	The connection md datum.
		 */
		std::string getConnectionMdDatum(WellReservoirConnectionType wellReservoirConnection, uint64_t connectionIndex) const;

		/**
		 * Query if 'index' has connection md unit
		 *
		 * @param	wellReservoirConnection	The physical nature of the connection
		 * @param 	connectionIndex The index of the connection in the array of type wellReservoirConnection.
		 *
		 * @returns	True if connection md unit, false if not.
		 */
		bool hasConnectionMdUnit(WellReservoirConnectionType wellReservoirConnection, uint64_t connectionIndex) const;

		/**
		 * Returns md base uom if exists, else returns md top uom. Raises an exception if no md is
		 * defined.
		 *
		 * @param	wellReservoirConnection	The physical nature of the connection
		 * @param 	connectionIndex The index of the connection in the array of type wellReservoirConnection.
		 *
		 * @returns	The connection md unit.
		 */
		gsoap_eml2_1::eml21__LengthUom getConnectionMdUnit(WellReservoirConnectionType wellReservoirConnection, uint64_t connectionIndex) const;

		/**
		 * Returns md base uom (as string) if exists, else returns md top uom (as string). Raises an
		 * exception if no md is defined.
		 *
		 * @param	wellReservoirConnection	The physical nature of the connection
		 * @param 	connectionIndex The index of the connection in the array of type wellReservoirConnection.
		 *
		 * @returns	The connection md unit as string.
		 */
		std::string getConnectionMdUnitAsString(WellReservoirConnectionType wellReservoirConnection, uint64_t connectionIndex) const;

		/**
		 * Query if 'index' has connection top md
		 *
		 * @param 	index	Zero-based index of the.
		 *
		 * @returns	True if connection top md, false if not.
		 */
		bool hasConnectionTopMd(WellReservoirConnectionType wellReservoirConnection, uint64_t connectionIndex) const;

		/**
		 * Gets connection top md
		 *
		 * @param	wellReservoirConnection	The physical nature of the connection
		 * @param 	connectionIndex The index of the connection in the array of type wellReservoirConnection.
		 *
		 * @returns	The connection top md.
		 */
		double getConnectionTopMd(WellReservoirConnectionType wellReservoirConnection, uint64_t connectionIndex) const;

		/**
		 * Query if 'index' has connection base md
		 *
		 * @param 	index	Zero-based index of the.
		 *
		 * @returns	True if connection base md, false if not.
		 */
		bool hasConnectionBaseMd(WellReservoirConnectionType wellReservoirConnection, uint64_t connectionIndex) const;

		/**
		 * Gets connection base md
		 *
		 * @param	wellReservoirConnection	The physical nature of the connection
		 * @param 	connectionIndex The index of the connection in the array of type wellReservoirConnection.
		 *
		 * @returns	The connection base md.
		 */
		double getConnectionBaseMd(WellReservoirConnectionType wellReservoirConnection, uint64_t connectionIndex) const;

		/**
		 * Gets connection history count
		 *
		 * @param	wellReservoirConnection	The physical nature of the connection
		 * @param 	connectionIndex The index of the connection in the array of type wellReservoirConnection.
		 *
		 * @returns	The connection history count.
		 */
		uint64_t getConnectionHistoryCount(WellReservoirConnectionType wellReservoirConnection, uint64_t connectionIndex) const;

		/**
		 * Query if 'historyIndex' has connection history status
		 *
		 * @param 	historyIndex		Zero-based index of the history.
		 * @param	wellReservoirConnection	The physical nature of the connection
		 * @param 	connectionIndex The index of the connection in the array of type wellReservoirConnection.
		 *
		 * @returns	True if connection history status, false if not.
		 */
		bool hasConnectionHistoryStatus(uint64_t historyIndex,
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
		gsoap_eml2_1::witsml20__PhysicalStatus getConnectionHistoryStatus(uint64_t historyIndex,
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
		std::string getConnectionHistoryStatusToString(uint64_t historyIndex,
			WellReservoirConnectionType wellReservoirConnection, uint64_t connectionIndex) const;

		/**
		 * Sets connection history status
		 *
		 * @param 	historyIndex	 	Zero-based index of the history.
		 * @param	wellReservoirConnection	The physical nature of the connection
		 * @param 	connectionIndex The index of the connection in the array of type wellReservoirConnection.
		 * @param 	connectionStatus	The connection status.
		 */
		void setConnectionHistoryStatus(uint64_t historyIndex,
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
		bool hasConnectionHistoryStartDate(uint64_t historyIndex,
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
		time_t getConnectionHistoryStartDate(uint64_t historyIndex,
			WellReservoirConnectionType wellReservoirConnection, uint64_t connectionIndex) const;

		/**
		 * Sets connection history start date
		 *
		 * @param 	historyIndex		Zero-based index of the history.
		 * @param	wellReservoirConnection	The physical nature of the connection
		 * @param 	connectionIndex	Zero-based index of the connection.
		 * @param 	startDate			The start date.
		 */
		void setConnectionHistoryStartDate(uint64_t historyIndex,
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
		bool hasConnectionHistoryEndDate(uint64_t historyIndex,
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
		time_t getConnectionHistoryEndDate(uint64_t historyIndex,
			WellReservoirConnectionType wellReservoirConnection, uint64_t connectionIndex) const;

		/**
		 * Sets connection history end date
		 *
		 * @param 	historyIndex		Zero-based index of the history.
		 * @param	wellReservoirConnection	The physical nature of the connection
		 * @param 	connectionIndex	Zero-based index of the connection.
		 * @param 	endDate				The end date.
		 */
		void setConnectionHistoryEndDate(uint64_t historyIndex,
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
		bool hasConnectionHistoryMdDatum(uint64_t historyIndex,
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
		std::string getConnectionHistoryMdDatum(uint64_t historyIndex,
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
		bool hasConnectionHistoryMdUnit(uint64_t historyIndex,
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
		gsoap_eml2_1::eml21__LengthUom getConnectionHistoryMdUnit(uint64_t historyIndex,
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
		std::string getConnectionHistoryMdUnitAsString(uint64_t historyIndex,
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
		bool hasConnectionHistoryTopMd(uint64_t historyIndex,
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
		double getConnectionHistoryTopMd(uint64_t historyIndex,
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
		void setConnectionHistoryTopMd(uint64_t historyIndex,
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
		bool hasConnectionHistoryBaseMd(uint64_t historyIndex,
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
		double getConnectionHistoryBaseMd(uint64_t historyIndex,
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
		void setConnectionHistoryBaseMd(uint64_t historyIndex,
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
		bool hasConnectionHistoryComment(uint64_t historyIndex,
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
		std::string getConnectionHistoryComment(uint64_t historyIndex,
			WellReservoirConnectionType wellReservoirConnection, uint64_t connectionIndex) const;

		/**
		 * Sets connection history comment
		 *
		 * @param 	historyIndex		Zero-based index of the history.
		 * @param	wellReservoirConnection	The physical nature of the connection
		 * @param 	connectionIndex	Zero-based index of the connection.
		 * @param 	comment				The comment.
		 */
		void setConnectionHistoryComment(uint64_t historyIndex,
			WellReservoirConnectionType wellReservoirConnection, uint64_t connectionIndex,
			const std::string & comment);
	};

#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(Witsml20_WellboreGeometry) WellboreGeometry;
#endif
	class WellboreGeometry : public WITSML2_NS::WellboreObject
	{
	public:
		GETTER_AND_SETTER_DEPTH_MEASURE_OPTIONAL_ATTRIBUTE(MdBase, gsoap_eml2_1::eml21__LengthUom)

		GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE(GapAir, gsoap_eml2_1::eml21__LengthUom)
		GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE(DepthWaterMean, gsoap_eml2_1::eml21__LengthUom)

		//***************************************/
		//************** SECTION ****************/
		//***************************************/

		// Mandatory
		GETTER_AND_SETTER_GENERIC_ATTRIBUTE_IN_VECTOR(std::string, WellboreGeometrySection, uid)

		// Optional bool
		GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IN_VECTOR(bool, WellboreGeometrySection, CurveConductor)

		// Optional double
		GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IN_VECTOR(double, WellboreGeometrySection, FactFric)

		// Optional string
		GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IN_VECTOR(std::string, WellboreGeometrySection, Grade)

		// Optional enum
		GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IN_VECTOR(gsoap_eml2_1::witsml20__HoleCasingType, WellboreGeometrySection, TypeHoleCasing)

		// Optional Length Measure
		GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IN_VECTOR(WellboreGeometrySection, IdSection, gsoap_eml2_1::eml21__LengthUom)
		GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IN_VECTOR(WellboreGeometrySection, OdSection, gsoap_eml2_1::eml21__LengthUom)
		GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IN_VECTOR(WellboreGeometrySection, DiaDrift, gsoap_eml2_1::eml21__LengthUom)

		// Optional Mass per Length Measure
		GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IN_VECTOR(WellboreGeometrySection, WtPerLen, gsoap_eml2_1::eml21__MassPerLengthUom)

		void setWellboreGeometrySectionMdInterval(unsigned int index, double top, double base, const std::string & datum, gsoap_eml2_1::eml21__LengthUom uom);
		double getWellboreGeometrySectionMdIntervalTop(unsigned int index) const;
		gsoap_eml2_1::eml21__LengthUom getWellboreGeometrySectionMdIntervalTopUom(unsigned int index) const;
		double getWellboreGeometrySectionMdIntervalBase(unsigned int index) const;
		gsoap_eml2_1::eml21__LengthUom getWellboreGeometrySectionMdIntervalBaseUom(unsigned int index) const;
		std::string getWellboreGeometrySectionMdIntervaldatum(unsigned int index) const;
		bool hasWellboreGeometrySectionMdInterval(unsigned int index) const;

		void setWellboreGeometrySectionTvdInterval(unsigned int index, double top, double base, const std::string & datum, gsoap_eml2_1::eml21__LengthUom uom);
		double getWellboreGeometrySectionTvdIntervalTop(unsigned int index) const;
		gsoap_eml2_1::eml21__LengthUom getWellboreGeometrySectionTvdIntervalTopUom(unsigned int index) const;
		double getWellboreGeometrySectionTvdIntervalBase(unsigned int index) const;
		gsoap_eml2_1::eml21__LengthUom getWellboreGeometrySectionTvdIntervalBaseUom(unsigned int index) const;
		std::string getWellboreGeometrySectionTvdIntervaldatum(unsigned int index) const;
		bool hasWellboreGeometrySectionTvdInterval(unsigned int index) const;

		void pushBackSection(const std::string & uid = "");
		unsigned int getSectionCount() const;
	};
	
#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(Witsml20_Trajectory) Trajectory;
#endif
	class Trajectory : public WITSML2_NS::Trajectory
	{
	public:
	};
	
	template <class T>
	class ChannelMetaDataObject : public WITSML2_NS::WellboreObject
	{
	public:

		EML2_NS::PropertyKind* getPropertyKind() const;
		void setPropertyKind(EML2_NS::PropertyKind* propKind);
	};

	%template(ChannelMetaDataLog) ChannelMetaDataObject<gsoap_eml2_1::witsml20__Log>;
	%template(ChannelMetaDataChannelSet) ChannelMetaDataObject<gsoap_eml2_1::witsml20__ChannelSet>;
	%template(ChannelMetaDataChannel) ChannelMetaDataObject<gsoap_eml2_1::witsml20__Channel>;
	
	template <class T>
	class ChannelIndexDataObject : public ChannelMetaDataObject<T>
	{
	public:
		virtual void pushBackChannelIndex(gsoap_eml2_1::witsml20__ChannelIndexType indexType, gsoap_eml2_1::eml21__UnitOfMeasure uom, const std::string & mnemonic, bool isIncreasing = true, const std::string & datum = "") = 0;

		unsigned int getChannelIndexCount() const {
			return static_cast<T*>(gsoapProxy2_1)->Index.size();
		}

		gsoap_eml2_1::witsml20__ChannelIndexType getChannelIndexType(unsigned int index) {
			if (index >= getChannelIndexCount()) {
				throw std::out_of_range("The channel index is out of range");
			}
			return static_cast<T*>(gsoapProxy2_1)->Index[index]->IndexType;
		}

		std::string getChannelIndexUom(unsigned int index) {
			if (index >= getChannelIndexCount()) {
				throw std::out_of_range("The channel index is out of range");
			}
			return static_cast<T*>(gsoapProxy2_1)->Index[index]->Uom;
		}

		bool getChannelIndexIsIncreasing(unsigned int index) {
			if (index >= getChannelIndexCount()) {
				throw std::out_of_range("The channel index is out of range");
			}
			return static_cast<T*>(gsoapProxy2_1)->Index[index]->Direction == gsoap_eml2_1::witsml20__IndexDirection__increasing;
		}

		std::string getChannelIndexMnemonic(unsigned int index) {
			if (index >= getChannelIndexCount()) {
				throw std::out_of_range("The channel index is out of range");
			}
			return static_cast<T*>(gsoapProxy2_1)->Index[index]->Mnemonic;
		}

		std::string getChannelIndexDatum(unsigned int index) {
			if (index >= getChannelIndexCount()) {
				throw std::out_of_range("The channel index is out of range");
			}
			return static_cast<T*>(gsoapProxy2_1)->Index[index]->DatumReference == nullptr ? "" : *static_cast<T*>(gsoapProxy2_1)->Index[index]->DatumReference;
		}
	};
	%template(ChannelIndexDataChannelSet) ChannelIndexDataObject<gsoap_eml2_1::witsml20__ChannelSet>;
	%template(ChannelIndexDataChannel) ChannelIndexDataObject<gsoap_eml2_1::witsml20__Channel>;
	
	class ChannelSet;
#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(Witsml20_Log) Log;
#endif
	class Log : public ChannelMetaDataObject<gsoap_eml2_1::witsml20__Log>
	{
	public:
		void pushBackChannelSet(class ChannelSet * channelSet);
		std::vector<ChannelSet*> getChannelSets() const;
	};
	
	class Channel;
#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(Witsml20_ChannelSet) ChannelSet;
#endif
	class ChannelSet : public ChannelIndexDataObject<gsoap_eml2_1::witsml20__ChannelSet>
	{
	public:
		void pushBackChannel(class Channel * channel);

		void setDataAsJsonArray(const std::string & jsonArray);
		void setDataAsFileUri(const std::string & fileUri);

		bool hasDataAsJsonArray() const;
		bool hasDataAsFileUri() const;

		const std::string & getDataAsJsonArray() const;
		const std::string & getDataAsFileUri() const;

		std::vector<class Log*> getLogs() const;
		std::vector<class Channel*> getChannels() const;
	};
	
#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(Witsml20_Channel) Channel;
#endif
	class Channel : public ChannelIndexDataObject<gsoap_eml2_1::witsml20__Channel>
	{
	public:
		std::vector<class ChannelSet*> getChannelSets() const;
		EML2_NS::PropertyKind* getPropertyKind() const;

		GETTER_AND_SETTER_GENERIC_ATTRIBUTE(std::string, Mnemonic)
		GETTER_AND_SETTER_GENERIC_ATTRIBUTE(std::string, Uom)
		GETTER_AND_SETTER_GENERIC_ATTRIBUTE(gsoap_eml2_1::witsml20__EtpDataType, DataType)
		GETTER_AND_SETTER_GENERIC_ATTRIBUTE(gsoap_eml2_1::witsml20__ChannelStatus, GrowingStatus)
	};
	
#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(Witsml20_WellboreMarker) WellboreMarker;
#endif
	class WellboreMarker : public WITSML2_NS::WellboreObject
	{
	public:
		GETTER_AND_SETTER_DEPTH_MEASURE_OPTIONAL_ATTRIBUTE(Md, gsoap_eml2_1::eml21__LengthUom)

		GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE(DipAngle, gsoap_eml2_1::eml21__PlaneAngleUom)
		GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE(DipDirection, gsoap_eml2_1::eml21__PlaneAngleUom)
	};
}

