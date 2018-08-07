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
#define SWIG_FILE_WITH_INIT // In case we use Python Swig Wrapping

#include "resqml2/ActivityTemplate.h"
#include "common/HdfProxy.h"

%}
typedef long long					LONG64;

#ifdef SWIGJAVA
typedef long long					ULONG64; // We don't want to use BigInteger in java.
#else
typedef unsigned long long	ULONG64;
#endif

typedef long long 				time_t;


//************************
// STD::VECTOR DEFINITIONS
//************************

namespace RESQML2_NS {
	class Activity;
}

// Don't try to create vector of polymorphic data unless you really know what you are doing.
// Use C array approach instead.
%include "std_vector.i"

#ifdef SWIGPYTHON
namespace RESQML2_NS
{
	%typemap(out) COMMON_NS::AbstractObject*, COMMON_NS::AbstractHdfProxy*,  AbstractFeature*, AbstractFeatureInterpretation*,  AbstractLocal3dCrs*, AbstractProperty*, AbstractValuesProperty*,AbstractRepresentation* {
		// Check potential downcasting
		swig_type_info * const outtype = SWIG_TypeQuery(("resqml2::" + result->getXmlTag() + " *").c_str());
		resultobj = SWIG_NewPointerObj(SWIG_as_voidptr(result), outtype, 0);
	}
}
#endif
#ifdef SWIGJAVA
	%include "swigResqml2JavaInclude.i"
#endif
#ifdef SWIGCSHARP
	%include "swigResqml2CsInclude.i"
#endif
#if defined(SWIGJAVA) || defined(SWIGCSHARP)
	%nspace RESQML2_NS::AbstractColumnLayerGridRepresentation;
	%nspace COMMON_NS::AbstractObject;
	%nspace RESQML2_NS::AbstractFeature;
	%nspace RESQML2_NS::AbstractFeatureInterpretation;
	%nspace RESQML2_NS::AbstractGridRepresentation;
	%nspace RESQML2_NS::AbstractLocal3dCrs;
	%nspace RESQML2_NS::AbstractProperty;
	%nspace RESQML2_NS::AbstractRepresentation;
	%nspace RESQML2_NS::AbstractValuesProperty;
	%nspace RESQML2_NS::Activity;
	%nspace RESQML2_NS::ActivityTemplate;
	%nspace RESQML2_NS::GridConnectionSetRepresentation;
	%nspace RESQML2_NS::MdDatum;
	%nspace RESQML2_NS::PropertyKind;
	%nspace RESQML2_NS::RepresentationSetRepresentation;
	%nspace RESQML2_NS::SubRepresentation;
	%nspace RESQML2_NS::TimeSeries;
#endif

namespace RESQML2_NS
{
	%nodefaultctor; // Disable creation of default constructors

	
	//************************************
	//************ Activity **************
	//************************************

	class ActivityTemplate : public COMMON_NS::AbstractObject
	{
	public:
		void pushBackParameter(const std::string title,
			const bool & isInput, const bool isOutput,
			const unsigned int & minOccurs, const int & maxOccurs);
		void pushBackParameter(const std::string title,
			const bool & isInput, const bool isOutput,
			const unsigned int & minOccurs, const int & maxOccurs,
			const std::string & resqmlObjectContentType);
		bool isAnExistingParameter(const std::string & paramTitle) const;
		const unsigned int getParameterCount() const;
		const std::string & getParameterTitle(const unsigned int & index) const;
		const bool & getParameterIsInput(const unsigned int & index) const;
		const bool & getParameterIsInput(const std::string & paramTitle) const;
		const bool & getParameterIsOutput(const unsigned int & index) const;
		const bool & getParameterIsOutput(const std::string & paramTitle) const;
		const LONG64 getParameterMinOccurences(const unsigned int & index) const;
		const LONG64 getParameterMinOccurences(const std::string & paramTitle) const;
		const LONG64 getParameterMaxOccurences(const unsigned int & index) const;
		const LONG64 getParameterMaxOccurences(const std::string & paramTitle) const;
	};

	class Activity : public COMMON_NS::AbstractObject
	{
	public:
		void pushBackParameter(const std::string title,
			const std::string & value);
		void pushBackParameter(const std::string title,
			const LONG64 & value);
		void pushBackParameter(const std::string title,
			COMMON_NS::AbstractObject* resqmlObject);
		
		unsigned int getParameterCount() const;
		unsigned int getParameterCount(const std::string & paramTitle) const;

		const std::string & getParameterTitle(const unsigned int & index) const;

		bool isAFloatingPointQuantityParameter(const std::string & paramTitle) const;
		bool isAFloatingPointQuantityParameter(const unsigned int & index) const;
		double getFloatingPointQuantityParameterValue(const unsigned int & index) const;

		bool isAnIntegerQuantityParameter(const std::string & paramTitle) const;
		bool isAnIntegerQuantityParameter(const unsigned int & index) const;
		LONG64 getIntegerQuantityParameterValue(const unsigned int & index) const;

		bool isAStringParameter(const std::string & paramTitle) const;
		bool isAStringParameter(const unsigned int & index) const;
		const std::string & getStringParameterValue(const unsigned int & index) const;

		bool isAResqmlObjectParameter(const std::string & paramTitle) const;
		bool isAResqmlObjectParameter(const unsigned int & index) const;
		COMMON_NS::AbstractObject* getResqmlObjectParameterValue(const unsigned int & index) const;

		void setActivityTemplate(ActivityTemplate* activityTemplate);
		ActivityTemplate* getActivityTemplate() const;
	};
	
	//************************************
	//************ CRS *******************
	//************************************
	
	class AbstractLocal3dCrs : public COMMON_NS::AbstractObject
	{
	public:
		double getOriginOrdinal1() const;
		double getOriginOrdinal2() const;
		double getOriginDepthOrElevation() const;
		double getArealRotation() const;
		bool isDepthOriented() const;
		
		bool isProjectedCrsDefinedWithEpsg() const;
		bool isProjectedCrsUnknown() const;
		const std::string & getProjectedCrsUnknownReason() const;
		unsigned long long getProjectedCrsEpsgCode() const;
		
		bool isVerticalCrsDefinedWithEpsg() const;
		bool isVerticalCrsUnknown() const;
		const std::string & getVerticalCrsUnknownReason() const;
		unsigned long long getVerticalCrsEpsgCode() const;

		gsoap_resqml2_0_1::eml20__LengthUom getProjectedCrsUnit() const;
		std::string getProjectedCrsUnitAsString() const;
		gsoap_resqml2_0_1::eml20__LengthUom getVerticalCrsUnit() const;
		std::string getVerticalCrsUnitAsString() const;
		
		gsoap_resqml2_0_1::eml20__AxisOrder2d getAxisOrder() const;
		void setAxisOrder(const gsoap_resqml2_0_1::eml20__AxisOrder2d & axisOrder) const;
	};
	
	class MdDatum : public COMMON_NS::AbstractObject
	{
	public:
		AbstractLocal3dCrs * getLocalCrs() const;
		virtual std::string getLocalCrsUuid() const = 0;

		virtual double getX() const = 0;
		virtual double getXInGlobalCrs() const = 0;
		virtual double getY() const = 0;
		virtual double getYInGlobalCrs() const = 0;
		virtual double getZ() const = 0;
		virtual double getZInGlobalCrs() const = 0;
		
		virtual gsoap_resqml2_0_1::resqml2__MdReference getOriginKind() const = 0;
	};
	
	//************************************
	//************ FEATURE ***************
	//************************************

	class AbstractFeatureInterpretation;
	class AbstractFeature : public COMMON_NS::AbstractObject
	{
	public:
		unsigned int getInterpretationCount() const;
		AbstractFeatureInterpretation* getInterpretation(const unsigned int & index) const;
	};
	
	//************************************
	//************ INTERPRETATION ********
	//************************************

	class AbstractRepresentation;
	class AbstractFeatureInterpretation : public COMMON_NS::AbstractObject
	{
	public:
		unsigned int						getRepresentationCount() const;
		AbstractFeature*				getInterpretedFeature();
		AbstractRepresentation* 	getRepresentation(const unsigned int & index) const;
		std::string 						getInterpretedFeatureUuid() const;
		
		const gsoap_resqml2_0_1::resqml2__Domain & initDomain(const gsoap_resqml2_0_1::resqml2__Domain & defaultDomain) const;
		gsoap_resqml2_0_1::resqml2__Domain getDomain() const;
	};

	//************************************
	//************ REPRESENTATION ********
	//************************************
	
	class AbstractValuesProperty;
	class SubRepresentation;
	class RepresentationSetRepresentation;
	class AbstractRepresentation : public COMMON_NS::AbstractObject
	{
	public:

		enum indexableElement { NODE = 0, EDGE = 1, FACE = 2, VOLUME = 3, PILLAR = 4 };
		
		AbstractFeatureInterpretation* getInterpretation() const;
		std::string getInterpretationUuid() const;
		AbstractLocal3dCrs * getLocalCrs();
		std::string getLocalCrsUuid() const;
		COMMON_NS::AbstractHdfProxy * getHdfProxy();
		std::string getHdfProxyUuid() const;
		unsigned int getValuesPropertyCount() const;
		AbstractValuesProperty* getValuesProperty(const unsigned int & index) const;
		
		unsigned int getSubRepresentationCount() const;
		class SubRepresentation* getSubRepresentation(const unsigned int & index) const;
		unsigned int getFaultSubRepresentationCount() const;
		SubRepresentation* getFaultSubRepresentation(const unsigned int & index) const;

		virtual ULONG64 getXyzPointCountOfPatch(const unsigned int & patchIndex) const = 0;
		ULONG64 getXyzPointCountOfAllPatches() const;
		void getXyzPointsOfPatch(const unsigned int & patchIndex, double * xyzPoints) const;
		void getXyzPointsOfPatchInGlobalCrs(const unsigned int & patchIndex, double * xyzPoints) const;
		void getXyzPointsOfAllPatches(double * xyzPoints) const;
		void getXyzPointsOfAllPatchesInGlobalCrs(double * xyzPoints) const;
		virtual unsigned int getPatchCount() const;
		
		AbstractRepresentation* getSeismicSupportOfPatch(const unsigned int & patchIndex);
		void getSeismicLineAbscissaOfPointsOfPatch(const unsigned int & patchIndex, double* values);
		void addSeismic2dCoordinatesToPatch(const unsigned int patchIndex, double * lineAbscissa,
			AbstractRepresentation * seismicSupport, COMMON_NS::AbstractHdfProxy * proxy);
		void getInlinesOfPointsOfPatch(const unsigned int & patchIndex, double * values);
		void getCrosslinesOfPointsOfPatch(const unsigned int & patchIndex, double * values);
		void addSeismic3dCoordinatesToPatch(const unsigned int patchIndex, double * inlines, double * crosslines, const unsigned int & pointCount,
			AbstractRepresentation * seismicSupport, COMMON_NS::AbstractHdfProxy * proxy);
		void addSeismic3dCoordinatesToPatch(const unsigned int patchIndex, const double & startInline, const double & incrInline, const unsigned int & countInline,
			const double & startCrossline, const double & incrCrossline, const unsigned int & countCrossline,
			AbstractRepresentation * seismicSupport);

		void pushBackIntoRepresentationSet(RepresentationSetRepresentation * repSet);
		ULONG64 getRepresentationSetRepresentationCount() const;
		RepresentationSetRepresentation* getRepresentationSetRepresentation(const ULONG64  & index) const;
	};
	
	class RepresentationSetRepresentation : public RESQML2_NS::AbstractRepresentation
	{
	public:
		bool isHomogeneous() const;
		unsigned int 						getRepresentationCount() const;
		AbstractRepresentation*				getRepresentation(const unsigned int & index) const;
	};
	
	class SubRepresentation : public RESQML2_NS::AbstractRepresentation
	{
	public:
		void pushBackSubRepresentationPatch(const gsoap_resqml2_0_1::resqml2__IndexableElements & elementKind, const ULONG64 & originIndex, 
			const unsigned int & elementCountInSlowestDimension,
			const unsigned int & elementCountInMiddleDimension,
			const unsigned int & elementCountInFastestDimension);
		void pushBackSubRepresentationPatch(const gsoap_resqml2_0_1::resqml2__IndexableElements & elementKind, const ULONG64 & elementCount, ULONG64 * elementIndices, COMMON_NS::AbstractHdfProxy * proxy, short * supportingRepIndices = nullptr);
		void pushBackSubRepresentationPatch(const gsoap_resqml2_0_1::resqml2__IndexableElements & elementKind0, const gsoap_resqml2_0_1::resqml2__IndexableElements & elementKind1,
			const ULONG64 & elementCount,
			ULONG64 * elementIndices0, ULONG64 * elementIndices1,
			COMMON_NS::AbstractHdfProxy * proxy);
		
		bool areElementIndicesPairwise(const unsigned int & patchIndex) const;
		bool areElementIndicesBasedOnLattice(const unsigned int & patchIndex, const unsigned int & elementIndicesIndex = 0) const;

		LONG64 getLatticeElementIndicesStartValue(const unsigned int & patchIndex, const unsigned int & elementIndicesIndex = 0) const;
		unsigned int getLatticeElementIndicesDimensionCount(const unsigned int & patchIndex, const unsigned int & elementIndicesIndex = 0) const;
		LONG64 getLatticeElementIndicesOffsetValue(const unsigned int & latticeDimensionIndex, const unsigned int & patchIndex, const unsigned int & elementIndicesIndex = 0) const;
		ULONG64 getLatticeElementIndicesOffsetCount(const unsigned int & latticeDimensionIndex, const unsigned int & patchIndex, const unsigned int & elementIndicesIndex = 0) const;
		
		AbstractRepresentation::indexableElement getElementKindOfPatch(const unsigned int & patchIndex, const unsigned int & elementIndicesIndex) const;
		ULONG64 getElementCountOfPatch(const unsigned int & patchIndex) const;
		void getElementIndicesOfPatch(const unsigned int & patchIndex, const unsigned int & elementIndicesIndex, ULONG64 * elementIndices) const;
		

		void pushBackSupportingRepresentation(AbstractRepresentation * supportingRep);
		virtual unsigned int getSupportingRepresentationCount() const = 0;
		AbstractRepresentation* getSupportingRepresentation(unsigned int index) const;
		virtual std::string getSupportingRepresentationUuid(unsigned int index) const = 0;
		virtual std::string getSupportingRepresentationTitle(unsigned int index) const = 0;
		virtual std::string getSupportingRepresentationContentType() const = 0;
	};
	
	class GridConnectionSetRepresentation;
	class AbstractColumnLayerGridRepresentation;
	class AbstractGridRepresentation : public AbstractRepresentation
	{
	public:
		unsigned int getGridConnectionSetRepresentationCount() const;
		GridConnectionSetRepresentation* getGridConnectionSetRepresentation(const unsigned int & index) const;
		virtual ULONG64 getCellCount() const = 0;
		
		std::string getParentGridUuid() const;
		AbstractGridRepresentation* getParentGrid() const;
		unsigned int getChildGridCount() const;
		AbstractGridRepresentation* getChildGrid(const unsigned int & index) const;
		void setParentWindow(ULONG64 * cellIndices, const ULONG64 & cellIndexCount, RESQML2_0_1_NS::UnstructuredGridRepresentation* parentGrid);
		void setParentWindow(unsigned int * columnIndices, const unsigned int & columnIndexCount,
			const unsigned int & kLayerIndexRegridStart,
			unsigned int * childCellCountPerInterval, unsigned int * parentCellCountPerInterval,  const unsigned int & intervalCount,
			AbstractColumnLayerGridRepresentation* parentGrid, double * childCellWeights = nullptr);
		void setParentWindow(
			const unsigned int & iCellIndexRegridStart, unsigned int * childCellCountPerIInterval, unsigned int * parentCellCountPerIInterval,  const unsigned int & iIntervalCount,
			const unsigned int & jCellIndexRegridStart, unsigned int * childCellCountPerJInterval, unsigned int * parentCellCountPerJInterval,  const unsigned int & jIntervalCount,
			const unsigned int & kCellIndexRegridStart, unsigned int * childCellCountPerKInterval, unsigned int * parentCellCountPerKInterval,  const unsigned int & kIntervalCount,
			RESQML2_0_1_NS::AbstractIjkGridRepresentation* parentGrid, double * iChildCellWeights = nullptr, double * jChildCellWeights = nullptr, double * kChildCellWeights = nullptr);
		void setParentWindow(
			const unsigned int & iCellIndexRegridStart, unsigned int constantChildCellCountPerIInterval, unsigned int constantParentCellCountPerIInterval, const unsigned int & iIntervalCount,
			const unsigned int & jCellIndexRegridStart, unsigned int constantChildCellCountPerJInterval, unsigned int constantParentCellCountPerJInterval, const unsigned int & jIntervalCount,
			const unsigned int & kCellIndexRegridStart, unsigned int constantChildCellCountPerKInterval, unsigned int constantParentCellCountPerKInterval, const unsigned int & kIntervalCount,
			RESQML2_0_1_NS::AbstractIjkGridRepresentation* parentGrid, double * iChildCellWeights = nullptr, double * jChildCellWeights = nullptr, double * kChildCellWeights = nullptr);
		void setParentWindow(
			const unsigned int & iCellIndexRegridStart, unsigned int iChildCellCount, unsigned int iParentCellCount,
			const unsigned int & jCellIndexRegridStart, unsigned int jChildCellCount, unsigned int jParentCellCount,
			const unsigned int & kCellIndexRegridStart, unsigned int kChildCellCount, unsigned int kParentCellCount,
			RESQML2_0_1_NS::AbstractIjkGridRepresentation* parentGrid, double * iChildCellWeights = nullptr, double * jChildCellWeights = nullptr, double * kChildCellWeights = nullptr);
		void setForcedNonRegridedParentCell(ULONG64 * cellIndices, const ULONG64 & cellIndexCount);	
		LONG64 getParentCellIndexCount() const;
		void getParentCellIndices(ULONG64 * parentCellIndices) const;
		LONG64 getParentColumnIndexCount() const;
		void getParentColumnIndices(ULONG64 * parentColumnIndices) const;
		ULONG64 getRegridStartIndexOnParentGrid(const char & dimension) const;
		ULONG64 getRegridIntervalCount(const char & dimension) const;
		bool isRegridCellCountPerIntervalConstant(const char & dimension, const bool & childVsParentCellCount) const;
		ULONG64 getRegridConstantCellCountPerInterval(const char & dimension, const bool & childVsParentCellCount) const;
		void getRegridCellCountPerInterval(const char & dimension, ULONG64 * childCellCountPerInterval, const bool & childVsParentCellCount) const;
		bool hasRegridChildCellWeights(const char & dimension) const;
		void getRegridChildCellWeights(const char & dimension, ULONG64 * childCellWeights) const;
		bool hasForcedNonRegridedParentCell() const;

		void setCellAssociationWithStratigraphicOrganizationInterpretation(ULONG64 * stratiUnitIndices, const ULONG64 & nullValue, RESQML2_0_1_NS::AbstractStratigraphicOrganizationInterpretation* stratiOrgInterp);
		virtual std::string getStratigraphicOrganizationInterpretationUuid() const;
		RESQML2_0_1_NS::AbstractStratigraphicOrganizationInterpretation* getStratigraphicOrganizationInterpretation() const;
		bool hasCellStratigraphicUnitIndices() const;
		ULONG64 getCellStratigraphicUnitIndices(ULONG64 * stratiUnitIndices);
		
		bool isTruncated() const;
		ULONG64 getTruncatedFaceCount() const;
		void getNodeIndicesOfTruncatedFaces(ULONG64 * nodeIndices) const;
		void getCumulativeNodeCountPerTruncatedFace(ULONG64 * nodeCountPerFace) const;
		void getNodeCountPerTruncatedFace(ULONG64 * nodeCountPerFace) const;
		ULONG64 getTruncatedCellCount() const;
		void getTruncatedCellIndices(ULONG64* cellIndices) const;
		void getTruncatedFaceIndicesOfTruncatedCells(ULONG64 * faceIndices) const;
		void getCumulativeTruncatedFaceCountPerTruncatedCell(ULONG64 * cumulativeFaceCountPerCell) const;
		void getTruncatedFaceCountPerTruncatedCell(ULONG64 * faceCountPerCell) const;
		void getNonTruncatedFaceIndicesOfTruncatedCells(ULONG64 * faceIndices) const;
		void getCumulativeNonTruncatedFaceCountPerTruncatedCell(ULONG64 * cumulativeFaceCountPerCell) const;
		void getNonTruncatedFaceCountPerTruncatedCell(ULONG64 * faceCountPerCell) const;
		void getTruncatedFaceIsRightHanded(unsigned char* cellFaceIsRightHanded) const;
	};
	
	class AbstractColumnLayerGridRepresentation : public AbstractGridRepresentation
	{
	public:
		unsigned int getKCellCount() const;
		void setKCellCount(const unsigned int & kCount);
		
		void setIntervalAssociationWithStratigraphicOrganizationInterpretation(ULONG64 * stratiUnitIndices, const ULONG64 & nullValue, RESQML2_0_1_NS::AbstractStratigraphicOrganizationInterpretation* stratiOrgInterp);
		RESQML2_0_1_NS::AbstractStratigraphicOrganizationInterpretation* getStratigraphicOrganizationInterpretation() const;
		bool hasIntervalStratigraphicUnitIndices() const;
		ULONG64 getIntervalStratigraphicUnitIndices(ULONG64 * stratiUnitIndices);
	};
	
	class GridConnectionSetRepresentation : public RESQML2_NS::AbstractRepresentation
	{
	public:
		bool isAssociatedToInterpretations() const;
		void getInterpretationIndexCumulativeCount(unsigned int * cumulativeCount) const;
		void getInterpretationIndices(unsigned int * interpretationIndices) const;
		LONG64 getInterpretationIndexNullValue() const;
	
		ULONG64 getCellIndexPairCount() const;
		unsigned int getCellIndexPairCountFromInterpretationIndex(const unsigned int & interpretationIndex) const;
		
		ULONG64 getCellIndexPairs(ULONG64 * cellIndexPairs) const;
		void getGridConnectionSetInformationFromInterpretationIndex(ULONG64 * cellIndexPairs, unsigned short * gridIndexPairs, int * localFaceIndexPairs, const unsigned int & interpretationIndex) const;
		bool hasLocalFacePerCell() const;
		LONG64 getLocalFacePerCellIndexPairs(int * localFacePerCellIndexPairs) const;
		bool isBasedOnMultiGrids() const;
		void getGridIndexPairs(unsigned short * gridIndexPairs) const;
		
		void pushBackSupportingGridRepresentation(AbstractGridRepresentation * supportingGridRep);
		
		void setCellIndexPairs(const ULONG64 & cellIndexPairCount, ULONG64 * cellIndexPair, const LONG64 & nullValue, COMMON_NS::AbstractHdfProxy * proxy, unsigned short * gridIndexPair = nullptr);
		void setLocalFacePerCellIndexPairs(const ULONG64 & cellIndexPairCount, int * localFacePerCellIndexPair, const LONG64 & nullValue, COMMON_NS::AbstractHdfProxy * proxy);
		void setConnectionInterpretationIndices(unsigned int * interpretationIndices, const unsigned int & interpretationIndiceCount, const LONG64 & nullValue, COMMON_NS::AbstractHdfProxy * proxy);
		void pushBackInterpretation(AbstractFeatureInterpretation* interp);
		
		std::string getInterpretationUuidFromIndex(const unsigned int & interpretationIndex) const;
		AbstractFeatureInterpretation * getInterpretationFromIndex(const unsigned int & interpretationIndex) const;
		unsigned int getInterpretationCount() const;
		
		unsigned int getSupportingGridRepresentationCount() const;
		AbstractGridRepresentation* getSupportingGridRepresentation(unsigned int index);
		std::string getSupportingGridRepresentationUuid(unsigned int index) const;
	};

	//************************************
	//************** PROPERTY ************
	//************************************
	
	class PropertyKind : public COMMON_NS::AbstractObject
	{
	public:
		const std::string & getNamingSystem() const;
		
		const gsoap_resqml2_0_1::resqml2__ResqmlUom & getUom() const;
		std::string getUomAsString() const;
	};
	
	class TimeSeries : public COMMON_NS::AbstractObject
	{
	public:
		void pushBackTimestamp(const time_t & timestamp);
		unsigned int getTimestampIndex(const time_t & timestamp) const;
		unsigned int getTimestampCount() const;
		time_t getTimestamp(const unsigned int & index) const;
	};
	
	class AbstractProperty: public COMMON_NS::AbstractObject
	{
	public:
		std::string getRepresentationUuid() const;
		AbstractRepresentation* getRepresentation();
		void setRepresentation(AbstractRepresentation * rep);
		
		std::string getHdfProxyUuid() const;
		COMMON_NS::AbstractHdfProxy* getHdfProxy();
		
		std::string getPropertyKindDescription() const;
		std::string getPropertyKindAsString() const;
		std::string getPropertyKindParentAsString() const;
		bool isAssociatedToOneStandardEnergisticsPropertyKind() const;
		gsoap_resqml2_0_1::resqml2__ResqmlPropertyKind getEnergisticsPropertyKind() const;
		
		std::string getLocalPropertyKindUuid() const;
		PropertyKind* getLocalPropertyKind() const;
		
		unsigned int getElementCountPerValue() const;
		
		gsoap_resqml2_0_1::resqml2__IndexableElements getAttachmentKind() const;
		
		void setTimeIndex(const unsigned int & timeIndex, TimeSeries * ts);
		void setTimeStep(const unsigned int & timeStep);
		TimeSeries* getTimeSeries() const;
		time_t getTimestamp() const;
	};
	
	class AbstractValuesProperty : public RESQML2_NS::AbstractProperty
	{
	public:
		enum hdfDatatypeEnum { UNKNOWN = 0, DOUBLE = 1, FLOAT = 2, LONG = 3, ULONG = 4, INT = 5, UINT = 6, SHORT = 7, USHORT = 8, CHAR = 9, UCHAR = 10};
		AbstractValuesProperty::hdfDatatypeEnum getValuesHdfDatatype() const;
		virtual std::string pushBackRefToExistingDataset(COMMON_NS::AbstractHdfProxy* hdfProxy, const std::string & datasetName, const long & nullValue) = 0;
		
		long getNullValueOfPatch(const unsigned int & patchIndex);
		long getLongValuesOfPatch(const unsigned int & patchIndex, long * values);
		unsigned long getULongValuesOfPatch(const unsigned int & patchIndex, unsigned long * values);
		int getIntValuesOfPatch(const unsigned int & patchIndex, int * values);
		
		int getIntValuesOfPatch(
			const unsigned int& patchIndex,
			int* values,
			unsigned long long* numValuesInEachDimension,
			unsigned long long* offsetInEachDimension,
			const unsigned int& numArrayDimensions
		);
		
		void getIntValuesOf3dPatch(
			const unsigned int& patchIndex,
			int* values,
			const unsigned int& valueCountInFastestDim,
			const unsigned int& valueCountInMiddleDim,
			const unsigned int& valueCountInSlowestDim,
			const unsigned int& offsetInFastestDim,
			const unsigned int& offsetInMiddleDim,
			const unsigned int& offsetInSlowestDim
		);
		
		unsigned int getUIntValuesOfPatch(const unsigned int & patchIndex, unsigned int * values);
		short getShortValuesOfPatch(const unsigned int & patchIndex, short * values);
		unsigned short getUShortValuesOfPatch(const unsigned int & patchIndex, unsigned short * values);
		char getCharValuesOfPatch(const unsigned int & patchIndex, char * values);
		unsigned char getUCharValuesOfPatch(const unsigned int & patchIndex, unsigned char * values);
		
		unsigned int getValuesCountOfPatch (const unsigned int & patchIndex);
		unsigned int getValuesCountOfDimensionOfPatch(const unsigned int & dimIndex, const unsigned int & patchIndex);
		unsigned int getDimensionsCountOfPatch(const unsigned int & patchIndex);
		
		void pushBackFacet(const gsoap_resqml2_0_1::resqml2__Facet & facet, const std::string & facetValue);
		unsigned int getFacetCount() const;
		gsoap_resqml2_0_1::resqml2__Facet getFacet(const unsigned int & index) const;
		std::string getFacetValue(const unsigned int & index) const;
		
		void createLongHdf5ArrayOfValues(
			unsigned long long* numValues, 
			const unsigned int& numArrayDimensions, 
			COMMON_NS::AbstractHdfProxy* proxy
		);
		void createLongHdf5Array3dOfValues(
			const unsigned int& valueCountInFastestDim, 
			const unsigned int& valueCountInMiddleDim, 
			const unsigned int& valueCountInSlowestDim, 
			COMMON_NS::AbstractHdfProxy * proxy
		);
		void pushBackLongHdf5SlabArray3dOfValues(
			long* values, 
			const unsigned int& valueCountInFastestDim, 
			const unsigned int& valueCountInMiddleDim, 
			const unsigned int& valueCountInSlowestDim, 
			const unsigned int& offsetInFastestDim, 
			const unsigned int& offsetInMiddleDim, 
			const unsigned int& offsetInSlowestDim, 
			COMMON_NS::AbstractHdfProxy* proxy
		);
		void pushBackLongHdf5SlabArrayOfValues(
			long * values, 
			unsigned long long * numValues, 
			unsigned long long * offsetValues, 
			const unsigned int & numArrayDimensions, 
			COMMON_NS::AbstractHdfProxy * proxy
		);
		void getLongValuesOfPatch(
			const unsigned int& patchIndex, 
			long* values, 
			unsigned long long* numValuesInEachDimension,
			unsigned long long* offsetInEachDimension, 
			const unsigned int& numArrayDimensions
		);
		void getLongValuesOf3dPatch(
			const unsigned int& patchIndex, 
			long* values, 
			const unsigned int& valueCountInFastestDim, 
			const unsigned int& valueCountInMiddleDim, 
			const unsigned int& valueCountInSlowestDim, 
			const unsigned int& offsetInFastestDim, 
			const unsigned int& offsetInMiddleDim, 
			const unsigned int& offsetInSlowestDim
		);
		
	};
	
}

