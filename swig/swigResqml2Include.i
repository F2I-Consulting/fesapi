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

#include "../src/resqml2/ActivityTemplate.h"
#include "../src/common/HdfProxy.h"
%}
typedef long long					LONG64;

#ifdef SWIGJAVA
typedef long long					ULONG64; // We don't want to use BigInteger in java.
#else
typedef unsigned long long	ULONG64;
#endif

typedef long long 				time_t;

namespace RESQML2_NS {
	class Activity;
}

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
	%nspace RESQML2_NS::PropertySet;
	%nspace RESQML2_NS::RepresentationSetRepresentation;
	%nspace RESQML2_NS::SubRepresentation;
	%nspace RESQML2_NS::TimeSeries;
	%nspace RESQML2_NS::WellboreFrameRepresentation;
#endif

namespace gsoap_resqml2_0_1
{
	enum resqml20__PillarShape {
		resqml20__PillarShape__vertical = 0,
		resqml20__PillarShape__straight = 1,
		resqml20__PillarShape__curved = 2
	};
	enum resqml20__TimeSetKind {
		resqml20__TimeSetKind__single_x0020time = 0,
		resqml20__TimeSetKind__equivalent_x0020times = 1,
		resqml20__TimeSetKind__not_x0020a_x0020time_x0020set = 2
	};
}

namespace RESQML2_NS
{
	%nodefaultctor; // Disable creation of default constructors

	class ActivityTemplate : public COMMON_NS::AbstractObject
	{
	public:
		void pushBackParameter(const std::string & title,
			bool isInput, bool isOutput,
			unsigned int minOccurs, int maxOccurs);
		void pushBackParameter(const std::string & title,
			bool isInput, bool isOutput,
			unsigned int minOccurs, int maxOccurs,
			std::string resqmlObjectContentType);
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
		void setAxisOrder(gsoap_resqml2_0_1::eml20__AxisOrder2d axisOrder) const;
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
		
		virtual gsoap_resqml2_0_1::resqml20__MdReference getOriginKind() const = 0;
	};

	class AbstractFeatureInterpretation;
	class AbstractFeature : public COMMON_NS::AbstractObject
	{
	public:
		unsigned int getInterpretationCount() const;
		AbstractFeatureInterpretation* getInterpretation(const unsigned int & index) const;
	};

	class AbstractRepresentation;
	class AbstractFeatureInterpretation : public COMMON_NS::AbstractObject
	{
	public:
		unsigned int						getRepresentationCount() const;
		AbstractFeature*				getInterpretedFeature();
		AbstractRepresentation* 	getRepresentation(const unsigned int & index) const;
		std::string 						getInterpretedFeatureUuid() const;
		
		const gsoap_resqml2_0_1::resqml20__Domain & initDomain(const gsoap_resqml2_0_1::resqml20__Domain & defaultDomain) const;
		gsoap_resqml2_0_1::resqml20__Domain getDomain() const;
	};
	
	class AbstractValuesProperty;
	class SubRepresentation;
	class RepresentationSetRepresentation;
	class AbstractRepresentation : public COMMON_NS::AbstractObject
	{
	public:

		enum indexableElement { NODE = 0, EDGE = 1, FACE = 2, VOLUME = 3, PILLAR = 4 };
		
		AbstractFeatureInterpretation* getInterpretation() const;
		std::string getInterpretationUuid() const;
		AbstractLocal3dCrs * getLocalCrs(unsigned int patchIndex);
		std::string getLocalCrsUuid(unsigned int patchIndex) const;
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
		bool isInSingleLocalCrs() const;
		bool isInSingleGlobalCrs() const;
		void getXyzPointsOfAllPatchesInGlobalCrs(double * xyzPoints) const;
		virtual unsigned int getPatchCount() const;
		
		AbstractRepresentation* getSeismicSupportOfPatch(const unsigned int & patchIndex);
		void getSeismicLineAbscissaOfPointsOfPatch(unsigned int patchIndex, double* values) const;
		void addSeismic2dCoordinatesToPatch(const unsigned int patchIndex, double * lineAbscissa,
			AbstractRepresentation * seismicSupport, COMMON_NS::AbstractHdfProxy * proxy);
		void getInlinesOfPointsOfPatch(unsigned int patchIndex, double * values) const;
		void getCrosslinesOfPointsOfPatch(unsigned int patchIndex, double * values) const;
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
		void pushBackSubRepresentationPatch(const gsoap_resqml2_0_1::resqml20__IndexableElements & elementKind, const ULONG64 & originIndex, 
			const unsigned int & elementCountInSlowestDimension,
			const unsigned int & elementCountInMiddleDimension,
			const unsigned int & elementCountInFastestDimension);
		void pushBackSubRepresentationPatch(const gsoap_resqml2_0_1::resqml20__IndexableElements & elementKind, const ULONG64 & elementCount, ULONG64 * elementIndices, COMMON_NS::AbstractHdfProxy * proxy, short * supportingRepIndices = nullptr);
		void pushBackSubRepresentationPatch(const gsoap_resqml2_0_1::resqml20__IndexableElements & elementKind0, const gsoap_resqml2_0_1::resqml20__IndexableElements & elementKind1,
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
		GridConnectionSetRepresentation* getGridConnectionSetRepresentation(unsigned int index) const;
		virtual ULONG64 getCellCount() const = 0;
		
		std::string getParentGridUuid() const;
		AbstractGridRepresentation* getParentGrid() const;
		unsigned int getChildGridCount() const;
		AbstractGridRepresentation* getChildGrid(unsigned int index) const;
		void setParentWindow(ULONG64 * cellIndices, ULONG64 cellIndexCount, RESQML2_0_1_NS::UnstructuredGridRepresentation* parentGrid, COMMON_NS::AbstractHdfProxy * proxy = nullptr);
		void setParentWindow(unsigned int * columnIndices, unsigned int columnIndexCount,
			unsigned int kLayerIndexRegridStart,
			unsigned int * childCellCountPerInterval, unsigned int * parentCellCountPerInterval,  unsigned int intervalCount,
			class AbstractColumnLayerGridRepresentation* parentGrid,
			COMMON_NS::AbstractHdfProxy * proxy = nullptr, double * childCellWeights = nullptr);
		void setParentWindow(
			unsigned int iCellIndexRegridStart, unsigned int * childCellCountPerIInterval, unsigned int * parentCellCountPerIInterval,  unsigned int iIntervalCount,
			unsigned int jCellIndexRegridStart, unsigned int * childCellCountPerJInterval, unsigned int * parentCellCountPerJInterval,  unsigned int jIntervalCount,
			unsigned int kCellIndexRegridStart, unsigned int * childCellCountPerKInterval, unsigned int * parentCellCountPerKInterval,  unsigned int kIntervalCount,
			RESQML2_0_1_NS::AbstractIjkGridRepresentation* parentGrid, COMMON_NS::AbstractHdfProxy * proxy = nullptr, double * iChildCellWeights = nullptr, double * jChildCellWeights = nullptr, double * kChildCellWeights = nullptr);
		void setParentWindow(
			unsigned int iCellIndexRegridStart, unsigned int constantChildCellCountPerIInterval, unsigned int constantParentCellCountPerIInterval, unsigned int iIntervalCount,
			unsigned int jCellIndexRegridStart, unsigned int constantChildCellCountPerJInterval, unsigned int constantParentCellCountPerJInterval, unsigned int jIntervalCount,
			unsigned int kCellIndexRegridStart, unsigned int constantChildCellCountPerKInterval, unsigned int constantParentCellCountPerKInterval, unsigned int kIntervalCount,
			RESQML2_0_1_NS::AbstractIjkGridRepresentation* parentGrid, COMMON_NS::AbstractHdfProxy * proxy = nullptr, double * iChildCellWeights = nullptr, double * jChildCellWeights = nullptr, double * kChildCellWeights = nullptr);
		void setParentWindow(
			unsigned int iCellIndexRegridStart, unsigned int iChildCellCount, unsigned int iParentCellCount,
			unsigned int jCellIndexRegridStart, unsigned int jChildCellCount, unsigned int jParentCellCount,
			unsigned int kCellIndexRegridStart, unsigned int kChildCellCount, unsigned int kParentCellCount,
			RESQML2_0_1_NS::AbstractIjkGridRepresentation* parentGrid, COMMON_NS::AbstractHdfProxy * proxy = nullptr, double * iChildCellWeights = nullptr, double * jChildCellWeights = nullptr, double * kChildCellWeights = nullptr);
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
		void getRegridChildCellWeights(const char & dimension, double * childCellWeights) const;
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
		
		void setIntervalAssociationWithStratigraphicOrganizationInterpretation(ULONG64 * stratiUnitIndices, ULONG64 nullValue, RESQML2_0_1_NS::AbstractStratigraphicOrganizationInterpretation* stratiOrgInterp, COMMON_NS::AbstractHdfProxy * hdfProxy);
		RESQML2_0_1_NS::AbstractStratigraphicOrganizationInterpretation* getStratigraphicOrganizationInterpretation() const;
		bool hasIntervalStratigraphicUnitIndices() const;
		ULONG64 getIntervalStratigraphicUnitIndices(ULONG64 * stratiUnitIndices);
		gsoap_resqml2_0_1::resqml20__PillarShape getMostComplexPillarGeometry() const;
	};
	
	class GridConnectionSetRepresentation : public RESQML2_NS::AbstractRepresentation
	{
	public:
		bool isAssociatedToInterpretations() const;
		void getInterpretationIndexCumulativeCount(unsigned int * cumulativeCount) const;
		void getInterpretationIndices(unsigned int * interpretationIndices) const;
		LONG64 getInterpretationIndexNullValue() const;
	
		ULONG64 getCellIndexPairCount() const;
		unsigned int getCellIndexPairCountFromInterpretationIndex(unsigned int interpretationIndex) const;
		
		ULONG64 getCellIndexPairs(ULONG64 * cellIndexPairs) const;
		void getGridConnectionSetInformationFromInterpretationIndex(ULONG64 * cellIndexPairs, unsigned short * gridIndexPairs, int * localFaceIndexPairs, unsigned int interpretationIndex) const;
		bool hasLocalFacePerCell() const;
		LONG64 getLocalFacePerCellIndexPairs(int * localFacePerCellIndexPairs) const;
		bool isBasedOnMultiGrids() const;
		void getGridIndexPairs(unsigned short * gridIndexPairs) const;
		
		void pushBackSupportingGridRepresentation(AbstractGridRepresentation * supportingGridRep);
		
		void setCellIndexPairs(ULONG64 cellIndexPairCount, ULONG64 * cellIndexPair, ULONG64 cellIndexPairNullValue, COMMON_NS::AbstractHdfProxy * proxy);
		void setCellIndexPairs(ULONG64 cellIndexPairCount, ULONG64 * cellIndexPair, ULONG64 cellIndexPairNullValue, COMMON_NS::AbstractHdfProxy * proxy, unsigned short gridIndexPairNullValue, unsigned short * gridIndexPair);
		void setLocalFacePerCellIndexPairs(ULONG64 cellIndexPairCount, int * localFacePerCellIndexPair, int nullValue, COMMON_NS::AbstractHdfProxy * proxy);
		void setConnectionInterpretationIndices(unsigned int * interpretationIndices, unsigned int interpretationIndiceCount, unsigned int nullValue, COMMON_NS::AbstractHdfProxy * proxy);
		void pushBackInterpretation(AbstractFeatureInterpretation* interp);
		
		std::string getInterpretationUuidFromIndex(const unsigned int & interpretationIndex) const;
		AbstractFeatureInterpretation * getInterpretationFromIndex(const unsigned int & interpretationIndex) const;
		unsigned int getInterpretationCount() const;
		
		unsigned int getSupportingGridRepresentationCount() const;
		AbstractGridRepresentation* getSupportingGridRepresentation(unsigned int index);
		std::string getSupportingGridRepresentationUuid(unsigned int index) const;
	};
	
	class PropertySet : public COMMON_NS::AbstractObject
	{
	public:
		void setParent(PropertySet * parent);
		std::string getParentUuid() const;
		PropertySet * getParent() const;

		unsigned int getChildrenCount() const;
		PropertySet* getChildren(unsigned int index) const;

		void pushBackProperty(RESQML2_NS::AbstractProperty * prop);

		unsigned int getPropertyCount() const;
		RESQML2_NS::AbstractProperty* getProperty(unsigned int index) const;

		virtual bool hasMultipleRealizations() const = 0;
		virtual bool hasSinglePropertyKind() const = 0;
		virtual gsoap_resqml2_0_1::resqml20__TimeSetKind getTimeSetKind() const = 0;
	};
	
	class TimeSeries : public COMMON_NS::AbstractObject
	{
	public:
		void pushBackTimestamp(time_t timestamp);
		unsigned int getTimestampIndex(time_t timestamp) const;
		unsigned int getTimestampCount() const;
		time_t getTimestamp(unsigned int index) const;
	};
	
	class AbstractProperty: public COMMON_NS::AbstractObject
	{
	public:
		std::string getRepresentationUuid() const;
		AbstractRepresentation* getRepresentation();
		void setRepresentation(AbstractRepresentation * rep);
		
		std::string getPropertyKindDescription() const;
		std::string getPropertyKindAsString() const;
		std::string getPropertyKindParentAsString() const;
		bool isAssociatedToOneStandardEnergisticsPropertyKind() const;
		gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind getEnergisticsPropertyKind() const;
		
		std::string getLocalPropertyKindUuid() const;
		COMMON_NS::PropertyKind* getLocalPropertyKind() const;
		
		unsigned int getElementCountPerValue() const;
		
		gsoap_resqml2_0_1::resqml20__IndexableElements getAttachmentKind() const;
		
		std::vector<RESQML2_NS::PropertySet *> getPropertySets() const;
		unsigned int getPropertySetCount() const;
		RESQML2_NS::PropertySet * getPropertySet(unsigned int index) const;
		
		bool hasRealizationIndex() const;
		ULONG64 getRealizationIndex() const;
		void setRealizationIndex(ULONG64 realizationIndex);
		
		void setTimeIndex(const unsigned int & timeIndex, TimeSeries * ts);
		void setTimeStep(const unsigned int & timeStep);
		TimeSeries* getTimeSeries() const;
		time_t getTimestamp() const;
		unsigned int getTimeIndex() const;
	};
	
	class AbstractValuesProperty : public RESQML2_NS::AbstractProperty
	{
	public:
		COMMON_NS::AbstractObject::hdfDatatypeEnum getValuesHdfDatatype() const;
		virtual std::string pushBackRefToExistingDataset(COMMON_NS::AbstractHdfProxy* hdfProxy, const std::string & datasetName, LONG64 nullValue) = 0;
		
		LONG64 getLongValuesOfPatch(unsigned int patchIndex, LONG64 * values) const;

		LONG64 getNullValueOfPatch(unsigned int patchIndex) const;

		ULONG64 getULongValuesOfPatch(unsigned int patchIndex, ULONG64 * values) const;

		int getIntValuesOfPatch(unsigned int patchIndex, int * values) const;

		int getIntValuesOfPatch(
			unsigned int patchIndex,
			int* values,
			unsigned long long* numValuesInEachDimension,
			unsigned long long* offsetInEachDimension,
			unsigned int numArrayDimensions
		) const;

		void getIntValuesOf3dPatch(
			unsigned int patchIndex,
			int* values,
			unsigned int valueCountInFastestDim,
			unsigned int valueCountInMiddleDim,
			unsigned int valueCountInSlowestDim,
			unsigned int offsetInFastestDim,
			unsigned int offsetInMiddleDim,
			unsigned int offsetInSlowestDim
		) const;

		unsigned int getUIntValuesOfPatch(unsigned int patchIndex, unsigned int * values) const;
		
		short getShortValuesOfPatch(unsigned int patchIndex, short * values) const;

		unsigned short getUShortValuesOfPatch(unsigned int patchIndex, unsigned short * values) const;

		char getCharValuesOfPatch(unsigned int patchIndex, char * values) const;

		unsigned char getUCharValuesOfPatch(unsigned int patchIndex, unsigned char * values) const;

		unsigned int getValuesCountOfPatch (unsigned int patchIndex) const;

		unsigned int getValuesCountOfDimensionOfPatch(unsigned int dimIndex, unsigned int patchIndex) const;

		unsigned int getDimensionsCountOfPatch(unsigned int patchIndex) const;

		void pushBackFacet(const gsoap_resqml2_0_1::resqml20__Facet & facet, const std::string & facetValue);

		unsigned int getFacetCount() const const;

		gsoap_resqml2_0_1::resqml20__Facet getFacet(unsigned int index) const const;

		std::string getFacetValue(unsigned int index) const;

		void createLongHdf5ArrayOfValues(
			unsigned long long* numValues, 
			unsigned int numArrayDimensions, 
			COMMON_NS::AbstractHdfProxy* proxy = nullptr);

		void createLongHdf5Array3dOfValues(
			unsigned int valueCountInFastestDim, 
			unsigned int valueCountInMiddleDim, 
			unsigned int valueCountInSlowestDim, 
			COMMON_NS::AbstractHdfProxy* proxy = nullptr);

		void pushBackLongHdf5SlabArray3dOfValues(
			LONG64* values, 
			unsigned int valueCountInFastestDim, 
			unsigned int valueCountInMiddleDim, 
			unsigned int valueCountInSlowestDim, 
			unsigned int offsetInFastestDim, 
			unsigned int offsetInMiddleDim, 
			unsigned int offsetInSlowestDim, 
			COMMON_NS::AbstractHdfProxy* proxy = nullptr);

		void pushBackLongHdf5SlabArrayOfValues(
			LONG64 * values, 
			unsigned long long const * numValues,
			unsigned long long const * offsetValues,
			unsigned int numArrayDimensions, 
			COMMON_NS::AbstractHdfProxy* proxy = nullptr);

		void getLongValuesOfPatch(
			unsigned int patchIndex, 
			LONG64* values, 
			unsigned long long* numValuesInEachDimension,
			unsigned long long* offsetInEachDimension,
			unsigned int numArrayDimensions
		) const;

		void getLongValuesOf3dPatch(
			unsigned int patchIndex, 
			LONG64* values, 
			unsigned int valueCountInFastestDim, 
			unsigned int valueCountInMiddleDim, 
			unsigned int valueCountInSlowestDim, 
			unsigned int offsetInFastestDim, 
			unsigned int offsetInMiddleDim, 
			unsigned int offsetInSlowestDim
		) const;
	};

	class WellboreFrameRepresentation : public RESQML2_NS::AbstractRepresentation
	{
	public:
		void setMdValues(double const * mdValues, unsigned int mdValueCount, COMMON_NS::AbstractHdfProxy* proxy = nullptr);
		void setMdValues(double firstMdValue, double incrementMdValue, unsigned int mdValueCount);

		bool areMdValuesRegularlySpaced() const;
		double getMdConstantIncrementValue() const;
		double getMdFirstValue() const;
		unsigned int getMdValuesCount() const;
		AbstractValuesProperty::hdfDatatypeEnum getMdHdfDatatype() const;
		void getMdAsDoubleValues(double * values) const;
		void getMdAsFloatValues(float * values) const;

		std::string getWellboreTrajectoryUuid() const;
		RESQML2_0_1_NS::WellboreTrajectoryRepresentation* getWellboreTrajectory() const;
	};
}
