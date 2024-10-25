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
#include "../src/witsml2_1/Channel.h"
#include "../src/witsml2_1/ChannelSet.h"
#include "../src/witsml2_1/Log.h"
#include "../src/witsml2_1/Trajectory.h"
#include "../src/witsml2_1/Well.h"
#include "../src/witsml2_1/Wellbore.h"
#include "../src/witsml2_1/WellboreCompletion.h"
#include "../src/witsml2_1/WellboreGeometry.h"
#include "../src/witsml2_1/WellboreMarker.h"
#include "../src/witsml2_1/WellCompletion.h"
%}

#if defined(SWIGJAVA) || defined(SWIGCSHARP)	
	%nspace WITSML2_1_NS::Channel;
	%nspace WITSML2_1_NS::ChannelSet;
	%nspace WITSML2_1_NS::Log;
	%nspace WITSML2_1_NS::Trajectory;
	%nspace WITSML2_1_NS::Well;
	%nspace WITSML2_1_NS::Wellbore;	
	%nspace WITSML2_1_NS::WellboreCompletion;
	%nspace WITSML2_1_NS::WellboreGeometry;	
	%nspace WITSML2_1_NS::WellboreMarker;
	%nspace WITSML2_1_NS::WellCompletion;
#endif

namespace WITSML2_1_NS
{
	%nodefaultctor; // Disable creation of default constructors
	
#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(Witsml21_Well) Well;
#endif	
	class Well : public WITSML2_NS::Well
	{
	public:
	};
	
#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(Witsml21_Wellbore) Wellbore;
#endif
	class Wellbore : public WITSML2_NS::Wellbore 
	{
	public:
	};
	
#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(Witsml21_WellCompletion) WellCompletion;
#endif
	class WellCompletion : public COMMON_NS::AbstractObject
	{
	public:		
		Well* getWell() const;
		void setWell(Well* witsmlWell);
	};
		
#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(Witsml21_WellboreCompletion) WellboreCompletion;
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
		 * @param 	MdUnit	The md unit.
		 * @param 	TopMd 	The top md.
		 * @param 	BaseMd	The base md.
		 * @param 	guid  	Unique identifier of the connection.
		 */
		void pushBackConnection(WellReservoirConnectionType wellReservoirConnection,
			gsoap_eml2_3::eml23__LengthUom MdUnit,
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
			gsoap_eml2_3::witsml21__PhysicalStatus status,
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
		 * Returns md base uom if exists, else returns md top uom. Raises an exception if no md is
		 * defined.
		 *
		 * @param	wellReservoirConnection	The physical nature of the connection
		 * @param 	connectionIndex The index of the connection in the array of type wellReservoirConnection.
		 *
		 * @returns	The connection md unit.
		 */
		gsoap_eml2_3::eml23__LengthUom getConnectionMdUnit(WellReservoirConnectionType wellReservoirConnection, uint64_t connectionIndex) const;

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
		 * Gets connection top md
		 *
		 * @param	wellReservoirConnection	The physical nature of the connection
		 * @param 	connectionIndex The index of the connection in the array of type wellReservoirConnection.
		 *
		 * @returns	The connection top md.
		 */
		double getConnectionTopMd(WellReservoirConnectionType wellReservoirConnection, uint64_t connectionIndex) const;

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
		gsoap_eml2_3::witsml21__PhysicalStatus getConnectionHistoryStatus(uint64_t historyIndex,
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
			gsoap_eml2_3::witsml21__PhysicalStatus connectionStatus);

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
		 * Query if 'historyIndex' has connection history MD interval
		 *
		 * @param 	historyIndex		Zero-based index of the history.
		 * @param	wellReservoirConnection	The physical nature of the connection
		 * @param 	connectionIndex	Zero-based index of the connection.
		 *
		 * @returns	True if connection history has MD interval, false if not.
		 */
		bool hasConnectionHistoryMdInterval(uint64_t historyIndex,
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
		gsoap_eml2_3::eml23__LengthUom getConnectionHistoryMdUnit(uint64_t historyIndex,
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
		 * @param 	MdUnit				The md unit.
		 * @param 	TopMd				The top md.
		 * @param 	BaseMd				The base md.
		 */
		void setConnectionHistoryMdInterval(uint64_t historyIndex,
			WellReservoirConnectionType wellReservoirConnection, uint64_t connectionIndex,
			gsoap_eml2_3::eml23__LengthUom MdUnit,
			double TopMd, double baseMd);

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
	%rename(Witsml21_WellboreGeometry) WellboreGeometry;
#endif
	class WellboreGeometry : public WITSML2_NS::WellboreObject
	{
	public:
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
		GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IN_VECTOR(gsoap_eml2_3::witsml21__HoleCasingType, WellboreGeometrySection, TypeHoleCasing)

		// Optional Length Measure
		GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IN_VECTOR(WellboreGeometrySection, IdSection, gsoap_eml2_3::eml23__LengthUom)
		GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IN_VECTOR(WellboreGeometrySection, OdSection, gsoap_eml2_3::eml23__LengthUom)
		GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IN_VECTOR(WellboreGeometrySection, DiaDrift, gsoap_eml2_3::eml23__LengthUom)

		// Optional Mass per Length Measure
		GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IN_VECTOR(WellboreGeometrySection, WtPerLen, gsoap_eml2_3::eml23__MassPerLengthUom)

		/**
		 * Gets wellbore geometry section md interval top
		 *
		 * @param 	index	Zero-based index of the.
		 *
		 * @returns	The wellbore geometry section md interval top.
		 */
		double getWellboreGeometrySectionMdIntervalTop(uint64_t index) const;

		/**
		 * Gets wellbore geometry section md interval base
		 *
		 * @param 	index	Zero-based index of the.
		 *
		 * @returns	The wellbore geometry section md interval base.
		 */
		double getWellboreGeometrySectionMdIntervalBase(uint64_t index) const;

		/**
		 * Gets wellbore geometry section md interval uom
		 *
		 * @param 	index	Zero-based index of the section.
		 *
		 * @returns	The wellbore geometry section md interval uom.
		 */
		gsoap_eml2_3::eml23__LengthUom getWellboreGeometrySectionMdIntervalUom(uint64_t index) const;

		/**
		 * Sets wellbore geometry section tvd interval
		 *
		 * @param 	index	Zero-based index of the.
		 * @param 	top  	The top.
		 * @param 	base 	The base.
		 * @param 	datum	The datum.
		 * @param 	uom  	The uom.
		 */
		void setWellboreGeometrySectionTvdInterval(uint64_t index, double top, double base, gsoap_eml2_3::eml23__LengthUom uom);

		/**
		 * Gets wellbore geometry section tvd interval top
		 *
		 * @param 	index	Zero-based index of the.
		 *
		 * @returns	The wellbore geometry section tvd interval top.
		 */
		double getWellboreGeometrySectionTvdIntervalTop(uint64_t index) const;

		/**
		 * Gets wellbore geometry section tvd interval uom
		 *
		 * @param 	index	Zero-based index of the.
		 *
		 * @returns	The wellbore geometry section tvd interval uom.
		 */
		gsoap_eml2_3::eml23__LengthUom getWellboreGeometrySectionTvdIntervalUom(uint64_t index) const;

		/**
		 * Gets wellbore geometry section tvd interval base
		 *
		 * @param 	index	Zero-based index of the.
		 *
		 * @returns	The wellbore geometry section tvd interval base.
		 */
		double getWellboreGeometrySectionTvdIntervalBase(uint64_t index) const;

		/**
		 * Query if 'index' has wellbore geometry section tvd interval
		 *
		 * @param 	index	Zero-based index of the.
		 *
		 * @returns	True if wellbore geometry section tvd interval, false if not.
		 */
		bool hasWellboreGeometrySectionTvdInterval(uint64_t index) const;

		/**
		* Push back an empty section into the instance.
		*
		* @param 	top  	The MD top.
		* @param 	base 	The MD base.
		* @param 	uom  	The MD uom.
		* @param 	uid	(Optional) The UID.
		*/
		void pushBackSection(double top, double base, gsoap_eml2_3::eml23__LengthUom uom, const std::string & uid = "");
		
		/**
		 * Get the count of sections in this instance
		 *
		 * @returns	the count of sections in this instance.
		 */
		uint64_t getSectionCount() const;
	};
	
#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(Witsml21_Trajectory) Trajectory;
#endif
	class Trajectory : public WITSML2_NS::Trajectory
	{
	public:
	};
	
	template <class T>
	class ChannelIndexDataObject : public WITSML2_NS::WellboreObject
	{
	public:
		/**
		 * Pushes a back channel index
		 *
		 * @param 	indexKind  		The index.
		 * @param 	uom				The uom.
		 * @param 	mnemonic		The mnemonic.
		 * @param 	isIncreasing	(Optional) True if is increasing, false if not.
		 */
		virtual void pushBackChannelIndex(gsoap_eml2_3::eml23__DataIndexKind indexKind, gsoap_eml2_3::eml23__UnitOfMeasure uom, const std::string & mnemonic, bool isIncreasing = true) = 0;

		/**
		 * Gets channel index count
		 *
		 * @returns	The channel index count.
		 */
		unsigned int getChannelIndexCount() const;
		
		/**
		 * Gets channel index type
		 *
		 * @exception	std::out_of_range	Thrown when an out of range error condition occurs.
		 *
		 * @param 	index	Zero-based index of the.
		 *
		 * @returns	The channel index type.
		 */
		gsoap_eml2_3::eml23__DataIndexKind getChannelIndexKind(unsigned int index);

		/**
		 * Gets channel index uom
		 *
		 * @exception	std::out_of_range	Thrown when an out of range error condition occurs.
		 *
		 * @param 	index	Zero-based index of the.
		 *
		 * @returns	The channel index uom.
		 */
		std::string getChannelIndexUom(unsigned int index);

		/**
		 * Gets channel index is increasing
		 *
		 * @exception	std::out_of_range	Thrown when an out of range error condition occurs.
		 *
		 * @param 	index	Zero-based index of the.
		 *
		 * @returns	True if it succeeds, false if it fails.
		 */
		bool getChannelIndexIsIncreasing(unsigned int index);

		/**
		 * Gets channel index mnemonic
		 *
		 * @exception	std::out_of_range	Thrown when an out of range error condition occurs.
		 *
		 * @param 	index	Zero-based index of the.
		 *
		 * @returns	The channel index mnemonic.
		 */
		std::string getChannelIndexMnemonic(unsigned int index);
	};
	%template(ChannelIndexDataChannelSet) ChannelIndexDataObject<gsoap_eml2_3::witsml21__ChannelSet>;
	%template(ChannelIndexDataChannel) ChannelIndexDataObject<gsoap_eml2_3::witsml21__Channel>;
	
	class ChannelSet;
#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(Witsml21_Log) Log;
#endif
	class Log : public WITSML2_NS::WellboreObject
	{
	public:
		void pushBackChannelSet(class ChannelSet * channelSet);
		std::vector<ChannelSet*> getChannelSets() const;
	};
	
	class Channel;
#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(Witsml21_ChannelSet) ChannelSet;
#endif
	class ChannelSet : public ChannelIndexDataObject<gsoap_eml2_3::witsml21__ChannelSet>
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
	%rename(Witsml21_Channel) Channel;
#endif
	class Channel : public ChannelIndexDataObject<gsoap_eml2_3::witsml21__Channel>
	{
	public:
		std::vector<class ChannelSet*> getChannelSets() const;
		EML2_NS::PropertyKind* getPropertyKind() const;
		void setPropertyKind(EML2_NS::PropertyKind* propKind);

		GETTER_AND_SETTER_GENERIC_ATTRIBUTE(std::string, Mnemonic)
		GETTER_AND_SETTER_GENERIC_ATTRIBUTE(std::string, Uom)
		GETTER_AND_SETTER_GENERIC_ATTRIBUTE(gsoap_eml2_3::witsml21__ChannelDataKind, DataKind)
	};
	
#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(Witsml21_WellboreMarker) WellboreMarker;
#endif
	class WellboreMarker : public WITSML2_NS::WellboreObject
	{
	public:
		GETTER_AND_SETTER_DEPTH_MEASURE_OPTIONAL_ATTRIBUTE(Md, gsoap_eml2_3::eml23__LengthUom)

		GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE(DipAngle, gsoap_eml2_3::eml23__PlaneAngleUom)
		GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE(DipDirection, gsoap_eml2_3::eml23__PlaneAngleUom)
	};
}

