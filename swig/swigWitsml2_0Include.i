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
	%rename(witsml20_Well) Well;
#endif	
	class Well : public WITSML2_NS::Well
	{
	public:
	};
	
#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(witsml20_Wellbore) Wellbore;
#endif
	class Wellbore : public WITSML2_NS::Wellbore 
	{
	public:
	};
	
#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(witsml20_WellCompletion) WellCompletion;
#endif
	class WellCompletion : public COMMON_NS::AbstractObject
	{
	public:		
		Well* getWell() const;
		void setWell(Well* witsmlWell);
	};
		
#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(witsml20_WellboreCompletion) WellboreCompletion;
#endif
	class WellboreCompletion : public WITSML2_NS::WellboreObject
	{
	public:
		WellCompletion* getWellCompletion() const;
		void setWellCompletion(WellCompletion* wellCompletion);

		void pushBackPerforation(const std::string & datum,
			gsoap_eml2_1::eml21__LengthUom MdUnit,
			double TopMd,
			double BaseMd, 
			const std::string & guid = "");

		void pushBackPerforationHistory(unsigned int index,
			const std::string & guid = "");
			
		void pushBackPerforationHistory(unsigned int index,
			gsoap_eml2_1::witsml20__PerforationStatus perforationStatus,
			time_t startDate,
			const std::string & guid = "");	

		unsigned int getPerforationCount() const;
		
		std::string getPerforationUid(unsigned int index) const;

		bool hasPerforationMdDatum(unsigned int index) const;
	
		std::string getPerforationMdDatum(unsigned int index) const;
		
		bool hasPerforationMdUnit(unsigned int index) const;
		
		gsoap_eml2_1::eml21__LengthUom getPerforationMdUnit(unsigned int index) const;
		
		std::string getPerforationMdUnitAsString(unsigned int index) const;
		
		bool hasPerforationTopMd(unsigned int index) const;
		
		double getPerforationTopMd(unsigned int index) const;

		bool hasPerforationBaseMd(unsigned int index) const;

		double getPerforationBaseMd(unsigned int index) const;

		unsigned int getPerforationHistoryCount(unsigned int index) const;

		bool hasPerforationHistoryStatus(unsigned int historyIndex,
			unsigned int perforationIndex) const;

		gsoap_eml2_1::witsml20__PerforationStatus getPerforationHistoryStatus(unsigned int historyIndex,
			unsigned int perforationIndex) const;

		std::string getPerforationHistoryStatusToString(unsigned int historyIndex,
			unsigned int perforationIndex) const;

		void setPerforationHistoryStatus(unsigned int historyIndex,
			unsigned int perforationIndex, 
			gsoap_eml2_1::witsml20__PerforationStatus perforationStatus);

		bool hasPerforationHistoryStartDate(unsigned int historyIndex,
			unsigned int perforationIndex) const;

		time_t getPerforationHistoryStartDate(unsigned int historyIndex,
			unsigned int perforationIndex) const;

		void setPerforationHistoryStartDate(unsigned int historyIndex,
			unsigned int perforationIndex, time_t startDate) const;

		bool hasPerforationHistoryEndDate(unsigned int historyIndex,
			unsigned int perforationIndex) const;

		time_t getPerforationHistoryEndDate(unsigned int historyIndex,
			unsigned int perforationIndex) const;

		void setPerforationHistoryEndDate(unsigned int historyIndex,
			unsigned int perforationIndex, time_t endDate) const;
		
		bool hasPerforationHistoryMdDatum(unsigned int historyIndex,
			unsigned int perforationIndex) const;
		
		std::string getPerforationHistoryMdDatum(unsigned int historyIndex,
			unsigned int perforationIndex) const;
		
		bool hasPerforationHistoryMdUnit(unsigned int historyIndex,
			unsigned int perforationIndex) const;

		gsoap_eml2_1::eml21__LengthUom getPerforationHistoryMdUnit(unsigned int historyIndex,
			unsigned int perforationIndex) const;
			
		std::string getPerforationHistoryMdUnitAsString(unsigned int historyIndex,
			unsigned int perforationIndex) const;

		bool hasPerforationHistoryTopMd(unsigned int historyIndex,
			unsigned int perforationIndex) const;

		double getPerforationHistoryTopMd(unsigned int historyIndex,
			unsigned int perforationIndex) const;

		void setPerforationHistoryTopMd(unsigned int historyIndex,
			unsigned int perforationIndex,
			const std::string & datum,
			gsoap_eml2_1::eml21__LengthUom MdUnit,
			double TopMd);
		
		bool hasPerforationHistoryBaseMd(unsigned int historyIndex,
			unsigned int perforationIndex) const;

		double getPerforationHistoryBaseMd(unsigned int historyIndex,
			unsigned int perforationIndex) const;

		void setPerforationHistoryBaseMd(unsigned int historyIndex,
			unsigned int perforationIndex,
			const std::string & datum,
			gsoap_eml2_1::eml21__LengthUom MdUnit,
			double BaseMd);
			
		bool hasPerforationHistoryComment(unsigned int historyIndex,
			unsigned int perforationIndex) const;

		std::string getPerforationHistoryComment(unsigned int historyIndex,
			unsigned int perforationIndex) const;

		void setPerforationHistoryComment(unsigned int historyIndex,
			unsigned int perforationIndex,
			const std::string & comment);
	};

#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(witsml20_WellboreGeometry) WellboreGeometry;
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
	%rename(witsml20_Trajectory) Trajectory;
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
	%rename(witsml20_Log) Log;
#endif
	class Log : public ChannelMetaDataObject<gsoap_eml2_1::witsml20__Log>
	{
	public:
		void pushBackChannelSet(class ChannelSet * channelSet);
		std::vector<ChannelSet*> getChannelSets() const;
	};
	
	class Channel;
#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(witsml20_ChannelSet) ChannelSet;
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
	%rename(witsml20_Channel) Channel;
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
	%rename(witsml20_WellboreMarker) WellboreMarker;
#endif
	class WellboreMarker : public WITSML2_NS::WellboreObject
	{
	public:
		GETTER_AND_SETTER_DEPTH_MEASURE_OPTIONAL_ATTRIBUTE(Md, gsoap_eml2_1::eml21__LengthUom)

		GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE(DipAngle, gsoap_eml2_1::eml21__PlaneAngleUom)
		GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE(DipDirection, gsoap_eml2_1::eml21__PlaneAngleUom)
	};
}
