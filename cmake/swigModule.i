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
%module fesapi

//************************/
// STD STRING
//************************/

%include "std_string.i"

%include "../src/nsDefinitions.h"

//************************/
// JAVA
//************************/

#ifdef SWIGJAVA
	// Notice you must not compile the C++ API with an optimisation superior to -O1 with gcc 4.4.7 in order SWIG to work
	
	/*
	 When using multiple modules or the nspace feature it is common to invoke SWIG with a different -package command line option for each module.
	 However, by default the generated code may not compile if generated classes in one package use generated classes in another package.
	 The visibility of the getCPtr() and pointer constructor generated from the javabody typemaps needs changing.
	 The default visibility is protected but it needs to be public for access from a different package. Just changing 'protected' to 'public' in the typemap achieves this.
	 Two macros are available in java.swg to make this easier and using them is the preferred approach over simply copying the typemaps and modifying as this is forward compatible with any changes in the javabody typemap in future versions of SWIG.
	 The macros are for the proxy and typewrapper classes and can respectively be used to make the method and constructor public:
	  SWIG_JAVABODY_PROXY(public, public, SWIGTYPE)
	  SWIG_JAVABODY_TYPEWRAPPER(public, public, public, SWIGTYPE)
	*/
	SWIG_JAVABODY_PROXY(public, public, SWIGTYPE)
	SWIG_JAVABODY_TYPEWRAPPER(public, public, public, SWIGTYPE)
	
	// http://www.swig.org/Doc4.0/SWIGDocumentation.html#Java_proper_enums
	%include "enums.swg"
	%javaconst(1);
	
	%include "swigJavaInclude.i"
#endif

//************************/
// CSHARP
//************************/

#ifdef SWIGCSHARP
	SWIG_CSBODY_PROXY(public, public, SWIGTYPE)
	SWIG_CSBODY_TYPEWRAPPER(public, public, public, SWIGTYPE)
	
	%include "swigCsInclude.i"
#endif

//************************/
// POD C ARRAYS
//************************/

%include "carrays_indexing64bits.i"
#ifdef SWIGJAVA // Use functions instead of classes in java in order to avoid premature garbage collection
	%array_functions(unsigned long long, ULongArray);
	%array_functions(unsigned int, UIntArray);
	%array_functions(int, IntArray);
	%array_functions(long long, LongArray);
	%array_functions(float, FloatArray);
	%array_functions(double, DoubleArray);
	%array_functions(short, ShortArray);
	%array_functions(unsigned short, UShortArray);
	%array_functions(char, CharArray);
	%array_functions(unsigned char, UCharArray);
	%array_functions(bool, BoolArray);
#else // Use GC.KeepAlive on these arrays to ensure no premature garbage collection in C#
	%array_class(unsigned long long, ULongArray);
	%array_class(unsigned int, UIntArray);
	%array_class(int, IntArray);
	%array_class(long long, LongArray);
	%array_class(float, FloatArray);
	%array_class(double, DoubleArray);
	%array_class(short, ShortArray);
	%array_class(unsigned short, UShortArray);
	%array_class(char, CharArray);
	%array_class(unsigned char, UCharArray);
	%array_class(bool, BoolArray);
#endif

// Example below of premature garbage collection
// DoubleArray myDoubleArray = new DoubleArray(100);
// myOperations(myDoubleArray.cast());
// myDoubleArray can be GC after cast and before myOperations has finished.

// Don't try to create vector of polymorphic data unless you really know what you are doing.
// Use C array approach instead.
%include "std_vector.i"

//************************/
// EXCEPTIONS
//************************/

%include "exception.i"
%exception {
    try {
        $action
    }
    catch (std::invalid_argument & e) {
        SWIG_exception(SWIG_TypeError,const_cast<char*>(e.what()));
    } 
    catch (std::out_of_range& e) {
        SWIG_exception(SWIG_IndexError,const_cast<char*>(e.what()));
    }
    catch (std::logic_error & e) {
        SWIG_exception(SWIG_SyntaxError,const_cast<char*>(e.what()));
    } 
    catch(...) {
        SWIG_exception(SWIG_RuntimeError,"Unknown exception at F2I C++ API level");
    }
}


typedef long long					LONG64;

#ifdef SWIGJAVA
typedef long long					ULONG64; // We don't want to use BigInteger in java.
#else
typedef unsigned long long	ULONG64;
#endif

typedef long long 				time_t;

#if defined(SWIGJAVA) || defined(SWIGCSHARP)
	%nspace COMMON_NS::DataObjectRepository;
	%nspace COMMON_NS::EnumStringMapper;
	%nspace COMMON_NS::EpcDocument;
	%nspace COMMON_NS::AbstractObject;
#endif

namespace EML2_NS
{
	class Activity;
}

namespace COMMON_NS
{
	%nodefaultctor; // Disable creation of default constructors
	
	class AbstractObject
	{
	public:
		enum hdfDatatypeEnum { UNKNOWN = 0, DOUBLE = 1, FLOAT = 2, LONG_64 = 3, ULONG_64 = 4, INT = 5, UINT = 6, SHORT = 7, USHORT = 8, CHAR = 9, UCHAR = 10};
	
		COMMON_NS::DataObjectRepository* getRepository() const;
	
		bool isPartial() const;
	
		std::string getUuid() const;
		std::string getTitle() const;
		std::string getEditor() const;
		time_t getCreation() const;
		std::string getOriginator() const;
		std::string getDescription() const;
		time_t getLastUpdate() const;
		std::string getFormat() const;
		std::string getDescriptiveKeywords() const;
		std::string getVersion() const;
		
		void setMetadata(const std::string & title, const std::string & editor, time_t creation, const std::string & originator, const std::string & description, time_t lastUpdate, const std::string & descriptiveKeywords);
		void setTitle(const std::string & title);
		void setEditor(const std::string & editor);
		void setCreation(time_t creation);
		void setOriginator(const std::string & originator);
		void setDescription(const std::string & description);
		void setLastUpdate(time_t lastUpdate);
		static void setFormat(const std::string & vendor, const std::string & applicationName, const std::string & applicationVersionNumber);
		void setDescriptiveKeywords(const std::string & descriptiveKeywords);
		void setVersion(const std::string & version);
				
		std::string getXmlTag() const;
		std::string getXmlNamespace() const;
		std::string getXmlNamespaceVersion() const;
		
		void addAlias(const std::string & authority, const std::string & title);
		unsigned int getAliasCount() const;
		std::string getAliasAuthorityAtIndex(unsigned int index) const;
		std::string getAliasTitleAtIndex(unsigned int index) const;
		
		void pushBackExtraMetadata(const std::string & key, const std::string & value);
		
		unsigned int getExtraMetadataCount() const;
		std::string getExtraMetadataKeyAtIndex(unsigned int index) const;
		std::string getExtraMetadataStringValueAtIndex(unsigned int index) const;

		unsigned int getActivityCount() const;

		EML2_NS::Activity * getActivity (unsigned int index) const;
	};
}

%{
#define SWIG_FILE_WITH_INIT // In case we use Python Swig Wrapping
%}

%include "swigEml2Include.i"
%include "swigEml2_0Include.i"
%include "swigEml2_1Include.i"
#ifdef WITH_RESQML2_2
%include "swigEml2_3Include.i"
#endif
%include "swigResqml2Include.i"
%include "swigResqml2_0_1Include.i"
#ifdef WITH_RESQML2_2
%include "swigResqml2_2Include.i"
#endif
%include "swigWitsml2_0Include.i"
%include "swigEtp1_2Include.i"

//************************/
// STD::VECTOR DEFINITIONS
//************************/

namespace std {
	%template(StringVector) vector< std::string >;
}

%{
#include "../src/common/EnumStringMapper.h"
#include "../src/common/EpcDocument.h"
%}

namespace COMMON_NS
{	
	class DataObjectRepository
	{
	public:
	
		enum class openingMode : std::int8_t {
			READ_ONLY = 0,
			READ_WRITE = 1,
			READ_WRITE_DO_NOT_CREATE = 2,
			OVERWRITE = 3
		};
		
		enum class EnergisticsStandard : std::int8_t {
			RESQML2_0_1 = 0,
			EML2_0 = 1,
			WITSML2_0 = 2,
			EML2_1 = 3,
			PRODML2_1 = 4,
			EML2_2 = 5,
			RESQML2_2 = 6,
			EML2_3 = 7
		};
		
		DataObjectRepository();
		DataObjectRepository(const std::string & propertyKindMappingFilesDirectory);	
		
		void setDefaultStandard(EnergisticsStandard version);
		EnergisticsStandard getDefaultEmlVersion() const;
		EnergisticsStandard getDefaultProdmlVersion() const;
		EnergisticsStandard getDefaultResqmlVersion() const;
		EnergisticsStandard getDefaultWitsmlVersion() const;
		
		void clear();
		
		RESQML2_NS::AbstractLocal3dCrs* getDefaultCrs() const;
		void setDefaultCrs(RESQML2_NS::AbstractLocal3dCrs* crs);
		
		bool hasHdfProxyFactory();
		
		EML2_NS::AbstractHdfProxy* getDefaultHdfProxy() const;
		void setDefaultHdfProxy(EML2_NS::AbstractHdfProxy* hdfProxy);
		
%define SWIG_GETTER_DATAOBJECTS(returnedDataType, dataObjectName)
		unsigned int get ## dataObjectName ## Count() const;
		returnedDataType * get ## dataObjectName(unsigned int index) const;
%enddef
		
		SWIG_GETTER_DATAOBJECTS(EML2_NS::TimeSeries, TimeSeries)
		SWIG_GETTER_DATAOBJECTS(EML2_NS::AbstractHdfProxy, HdfProxy)

		SWIG_GETTER_DATAOBJECTS(RESQML2_NS::LocalDepth3dCrs, LocalDepth3dCrs)
		SWIG_GETTER_DATAOBJECTS(RESQML2_NS::LocalTime3dCrs, LocalTime3dCrs)
		SWIG_GETTER_DATAOBJECTS(RESQML2_NS::StratigraphicColumn, StratigraphicColumn)
		SWIG_GETTER_DATAOBJECTS(RESQML2_NS::BoundaryFeature, Fault)
		SWIG_GETTER_DATAOBJECTS(RESQML2_NS::BoundaryFeature, Fracture)
		SWIG_GETTER_DATAOBJECTS(RESQML2_NS::BoundaryFeature, Horizon)
		SWIG_GETTER_DATAOBJECTS(RESQML2_NS::BoundaryFeature, GeobodyBoundary)
		SWIG_GETTER_DATAOBJECTS(RESQML2_NS::RockVolumeFeature, Geobody)
		SWIG_GETTER_DATAOBJECTS(RESQML2_NS::PolylineSetRepresentation, FaultPolylineSetRep)
		SWIG_GETTER_DATAOBJECTS(RESQML2_NS::PolylineSetRepresentation, FracturePolylineSetRep)
		SWIG_GETTER_DATAOBJECTS(RESQML2_NS::PolylineSetRepresentation, CulturalPolylineSetRep)
		SWIG_GETTER_DATAOBJECTS(RESQML2_NS::TriangulatedSetRepresentation, FaultTriangulatedSetRep)
		SWIG_GETTER_DATAOBJECTS(RESQML2_NS::TriangulatedSetRepresentation, FractureTriangulatedSetRep)
		SWIG_GETTER_DATAOBJECTS(RESQML2_NS::Grid2dRepresentation, HorizonGrid2dRep)
		SWIG_GETTER_DATAOBJECTS(RESQML2_NS::PolylineRepresentation, HorizonPolylineRep)
		SWIG_GETTER_DATAOBJECTS(RESQML2_NS::PolylineSetRepresentation, HorizonPolylineSetRep)
		SWIG_GETTER_DATAOBJECTS(RESQML2_NS::TriangulatedSetRepresentation, HorizonTriangulatedSetRep)
		SWIG_GETTER_DATAOBJECTS(RESQML2_NS::TriangulatedSetRepresentation, UnclassifiedTriangulatedSetRep)
		SWIG_GETTER_DATAOBJECTS(RESQML2_NS::TriangulatedSetRepresentation, AllTriangulatedSetRep)
		SWIG_GETTER_DATAOBJECTS(RESQML2_NS::Grid2dRepresentation, AllGrid2dRepresentation)
		SWIG_GETTER_DATAOBJECTS(RESQML2_NS::PolylineRepresentation, AllPolylineRepresentation)
		SWIG_GETTER_DATAOBJECTS(RESQML2_NS::PolylineSetRepresentation, AllPolylineSetRep)
		SWIG_GETTER_DATAOBJECTS(RESQML2_NS::AbstractSeismicLineFeature, SeismicLine)
		SWIG_GETTER_DATAOBJECTS(RESQML2_NS::PolylineRepresentation, SeismicLinePolylineRep)
		SWIG_GETTER_DATAOBJECTS(RESQML2_NS::WellboreFeature, Wellbore)
		SWIG_GETTER_DATAOBJECTS(RESQML2_NS::WellboreTrajectoryRepresentation, WellboreTrajectoryRepresentation)
		SWIG_GETTER_DATAOBJECTS(RESQML2_NS::DeviationSurveyRepresentation, DeviationSurveyRepresentation)
		SWIG_GETTER_DATAOBJECTS(RESQML2_NS::RepresentationSetRepresentation, RepresentationSetRepresentation)
		SWIG_GETTER_DATAOBJECTS(RESQML2_NS::AbstractIjkGridRepresentation, IjkGridRepresentation)
		SWIG_GETTER_DATAOBJECTS(RESQML2_NS::IjkGridParametricRepresentation, IjkGridParametricRepresentation)
		SWIG_GETTER_DATAOBJECTS(RESQML2_NS::IjkGridExplicitRepresentation, IjkGridExplicitRepresentation)
		SWIG_GETTER_DATAOBJECTS(RESQML2_NS::IjkGridLatticeRepresentation, IjkSeismicCubeGridRepresentation)
		SWIG_GETTER_DATAOBJECTS(RESQML2_NS::UnstructuredGridRepresentation, UnstructuredGridRepresentation)
		SWIG_GETTER_DATAOBJECTS(RESQML2_NS::CulturalFeature, Cultural)
		SWIG_GETTER_DATAOBJECTS(RESQML2_NS::Model, Model)
		SWIG_GETTER_DATAOBJECTS(RESQML2_NS::SubRepresentation, SubRepresentation)
		SWIG_GETTER_DATAOBJECTS(RESQML2_NS::PointSetRepresentation, PointSetRepresentation)
		
		AbstractObject* getDataObjectByUuid(const std::string & uuid) const;
		AbstractObject* getDataObjectByUuidAndVersion(const std::string & uuid, const std::string & version) const;
		
		template <class valueType>
		std::vector<valueType*> getDataObjects() const
		{
			std::vector<valueType*> result;

			for (std::unordered_map< std::string, std::vector<AbstractObject*> >::const_iterator it = dataObjects.begin(); it != dataObjects.end(); ++it) {
				for (size_t i = 0; i < it->second.size(); ++i) {
					if (dynamic_cast<valueType*>(it->second[i]) != nullptr) {
						result.push_back(static_cast<valueType*>(it->second[i]));
					}
				}
			}

			return result;
		}
		%template(getWells) getDataObjects<WITSML2_0_NS::Well>;
		%template(getWellbores) getDataObjects<WITSML2_0_NS::Wellbore>;
		%template(getTrajectories) getDataObjects<WITSML2_0_NS::Trajectory>;
		%template(getWellCompletions) getDataObjects<WITSML2_0_NS::WellCompletion>;
		%template(getWellboreCompletions) getDataObjects<WITSML2_0_NS::WellboreCompletion>;
		%template(getWellboreGeometries) getDataObjects<WITSML2_0_NS::WellboreGeometry>;
		%template(getLogs) getDataObjects<WITSML2_0_NS::Log>;
		%template(getChannelSets) getDataObjects<WITSML2_0_NS::ChannelSet>;
		%template(getChannels) getDataObjects<WITSML2_0_NS::Channel>;
#ifdef WITH_RESQML2_2
		%template(getGraphicalInformationSets) getDataObjects<EML2_3_NS::GraphicalInformationSet>;
#endif
		
		EML2_NS::AbstractHdfProxy* createHdfProxy(const std::string & guid, const std::string & title, const std::string & packageDirAbsolutePath, const std::string & externalFilePath, DataObjectRepository::openingMode hdfPermissionAccess);

		//************ CRS *******************/

		RESQML2_NS::LocalDepth3dCrs* createLocalDepth3dCrs(const std::string & guid, const std::string & title,
			double originOrdinal1, double originOrdinal2, double originOrdinal3,
			double arealRotation,
			gsoap_resqml2_0_1::eml20__LengthUom projectedUom, unsigned long projectedEpsgCode,
			gsoap_resqml2_0_1::eml20__LengthUom verticalUom, unsigned int verticalEpsgCode, bool isUpOriented);


		RESQML2_NS::LocalDepth3dCrs* createLocalDepth3dCrs(const std::string & guid, const std::string & title,
			double originOrdinal1, double originOrdinal2, double originOrdinal3,
			double arealRotation,
			gsoap_resqml2_0_1::eml20__LengthUom projectedUom, const std::string & projectedUnknownReason,
			gsoap_resqml2_0_1::eml20__LengthUom verticalUom, const std::string & verticalUnknownReason, bool isUpOriented);


		RESQML2_NS::LocalDepth3dCrs* createLocalDepth3dCrs(const std::string & guid, const std::string & title,
			double originOrdinal1, double originOrdinal2, double originOrdinal3,
			double arealRotation,
			gsoap_resqml2_0_1::eml20__LengthUom projectedUom, unsigned long projectedEpsgCode,
			gsoap_resqml2_0_1::eml20__LengthUom verticalUom, const std::string & verticalUnknownReason, const bool & isUpOriented);


		RESQML2_NS::LocalDepth3dCrs* createLocalDepth3dCrs(const std::string & guid, const std::string & title,
			double originOrdinal1, double originOrdinal2, double originOrdinal3,
			double arealRotation,
			gsoap_resqml2_0_1::eml20__LengthUom projectedUom, const std::string & projectedUnknownReason,
			gsoap_resqml2_0_1::eml20__LengthUom verticalUom, unsigned int verticalEpsgCode, const bool & isUpOriented);


		RESQML2_NS::LocalTime3dCrs* createLocalTime3dCrs(const std::string & guid, const std::string & title,
			double originOrdinal1, double originOrdinal2, double originOrdinal3,
			double arealRotation,
			gsoap_resqml2_0_1::eml20__LengthUom projectedUom, unsigned long projectedEpsgCode,
			gsoap_resqml2_0_1::eml20__TimeUom timeUom,
			gsoap_resqml2_0_1::eml20__LengthUom verticalUom, unsigned int verticalEpsgCode, const bool & isUpOriented);


		RESQML2_NS::LocalTime3dCrs* createLocalTime3dCrs(const std::string & guid, const std::string & title,
			double originOrdinal1, double originOrdinal2, double originOrdinal3,
			double arealRotation,
			gsoap_resqml2_0_1::eml20__LengthUom projectedUom, const std::string & projectedUnknownReason,
			gsoap_resqml2_0_1::eml20__TimeUom timeUom,
			gsoap_resqml2_0_1::eml20__LengthUom verticalUom, const std::string & verticalUnknownReason, const bool & isUpOriented);


		RESQML2_NS::LocalTime3dCrs* createLocalTime3dCrs(const std::string & guid, const std::string & title,
			double originOrdinal1, double originOrdinal2, double originOrdinal3,
			double arealRotation,
			gsoap_resqml2_0_1::eml20__LengthUom projectedUom, unsigned long projectedEpsgCode,
			gsoap_resqml2_0_1::eml20__TimeUom timeUom,
			gsoap_resqml2_0_1::eml20__LengthUom verticalUom, const std::string & verticalUnknownReason, const bool & isUpOriented);


		RESQML2_NS::LocalTime3dCrs* createLocalTime3dCrs(const std::string & guid, const std::string & title,
			double originOrdinal1, double originOrdinal2, double originOrdinal3,
			double arealRotation,
			gsoap_resqml2_0_1::eml20__LengthUom projectedUom, const std::string & projectedUnknownReason,
			gsoap_resqml2_0_1::eml20__TimeUom timeUom,
			gsoap_resqml2_0_1::eml20__LengthUom verticalUom, unsigned int verticalEpsgCode, const bool & isUpOriented);

		RESQML2_NS::MdDatum* createMdDatum(const std::string & guid, const std::string & title,
			RESQML2_NS::AbstractLocal3dCrs * locCrs, gsoap_eml2_3::eml23__WellboreDatumReference originKind,
			double referenceLocationOrdinal1, double referenceLocationOrdinal2, double referenceLocationOrdinal3);

		/* FEATURE */

		RESQML2_NS::BoundaryFeature* createBoundaryFeature(const std::string & guid, const std::string & title);

		RESQML2_NS::BoundaryFeature* createHorizon(const std::string & guid, const std::string & title);

		RESQML2_NS::BoundaryFeature* createGeobodyBoundaryFeature(const std::string & guid, const std::string & title);

		RESQML2_NS::RockVolumeFeature* createGeobodyFeature(const std::string & guid, const std::string & title);

		RESQML2_NS::BoundaryFeature* createFault(const std::string & guid, const std::string & title);

		RESQML2_NS::BoundaryFeature* createFracture(const std::string & guid, const std::string & title);

		RESQML2_NS::WellboreFeature* createWellboreFeature(const std::string & guid, const std::string & title);

		RESQML2_NS::SeismicLatticeFeature* createSeismicLattice(const std::string & guid, const std::string & title,
			int inlineIncrement, int crosslineIncrement,
			unsigned int originInline, unsigned int originCrossline,
			unsigned int inlineCount, unsigned int crosslineCount);

		RESQML2_0_1_NS::SeismicLineFeature* createSeismicLine(const std::string & guid, const std::string & title,
			int traceIndexIncrement, unsigned int firstTraceIndex, unsigned int traceCount);
#ifdef WITH_RESQML2_2	
		RESQML2_NS::CmpLineFeature* createCmpLine(const std::string & guid, const std::string & title,
			int nearestShotPointIndicesIncrement, int firstNearestShotPointIndex, unsigned int nearestShotPointCount);
			
		RESQML2_NS::ShotPointLineFeature* createShotPointLine(const std::string & guid, const std::string & title);
#endif
		RESQML2_NS::SeismicLineSetFeature* createSeismicLineSet(const std::string & guid, const std::string & title);

		RESQML2_NS::CulturalFeature* createCultural(const std::string & guid, const std::string & title,
			gsoap_eml2_3::resqml22__CulturalFeatureKind kind = gsoap_eml2_3::resqml22__CulturalFeatureKind__project_x0020boundaries);

		RESQML2_NS::RockVolumeFeature* createStratigraphicUnitFeature(const std::string & guid, const std::string & title);
#ifdef WITH_RESQML2_2
		RESQML2_NS::RockVolumeFeature* createRockVolumeFeature(const std::string & guid, const std::string & title);
		
		RESQML2_NS::Model* createModel(const std::string & guid, const std::string & title);
#endif
		RESQML2_NS::Model* createStructuralModel(const std::string & guid, const std::string & title);

		RESQML2_NS::Model* createStratigraphicModel(const std::string & guid, const std::string & title);

		RESQML2_NS::Model* createRockFluidModel(const std::string & guid, const std::string & title);

		RESQML2_NS::Model* createEarthModel(const std::string & guid, const std::string & title);

		RESQML2_0_1_NS::FluidBoundaryFeature* createFluidBoundaryFeature(const std::string & guid, const std::string & title, gsoap_resqml2_0_1::resqml20__FluidContact fluidContact);

		RESQML2_0_1_NS::RockFluidUnitFeature* createRockFluidUnit(const std::string & guid, const std::string & title, gsoap_resqml2_0_1::resqml20__Phase phase, RESQML2_0_1_NS::FluidBoundaryFeature* fluidBoundaryTop, RESQML2_0_1_NS::FluidBoundaryFeature* fluidBoundaryBottom);

		/* INTERPRETATION */

		RESQML2_NS::GenericFeatureInterpretation* createGenericFeatureInterpretation(RESQML2_NS::AbstractFeature * feature, const std::string & guid, const std::string & title);

		RESQML2_NS::BoundaryFeatureInterpretation* createBoundaryFeatureInterpretation(RESQML2_NS::BoundaryFeature * feature, const std::string & guid, const std::string & title);

		RESQML2_NS::HorizonInterpretation* createHorizonInterpretation(RESQML2_NS::BoundaryFeature * horizon, const std::string & guid, const std::string & title);

		RESQML2_NS::GeobodyBoundaryInterpretation* createGeobodyBoundaryInterpretation(RESQML2_NS::BoundaryFeature * geobodyBoundary, const std::string & guid, const std::string & title);

		RESQML2_NS::FaultInterpretation* createFaultInterpretation(RESQML2_NS::BoundaryFeature * fault, const std::string & guid, const std::string & title);

		RESQML2_NS::WellboreInterpretation* createWellboreInterpretation(RESQML2_NS::WellboreFeature * wellbore, const std::string & guid, const std::string & title, bool isDrilled);

		RESQML2_NS::EarthModelInterpretation* createEarthModelInterpretation(RESQML2_NS::Model * orgFeat, const std::string & guid, const std::string & title);

		RESQML2_NS::StructuralOrganizationInterpretation* createStructuralOrganizationInterpretationInAge(RESQML2_NS::Model * orgFeat, const std::string & guid, const std::string & title);
		RESQML2_NS::StructuralOrganizationInterpretation* createStructuralOrganizationInterpretationInApparentDepth(RESQML2_NS::Model * orgFeat, const std::string & guid, const std::string & title);
		RESQML2_NS::StructuralOrganizationInterpretation* createStructuralOrganizationInterpretationInMeasuredDepth(RESQML2_NS::Model * orgFeat, const std::string & guid, const std::string & title);

		RESQML2_NS::RockFluidOrganizationInterpretation* createRockFluidOrganizationInterpretation(RESQML2_NS::Model * orgFeat, const std::string & guid, const std::string & title);
		RESQML2_NS::RockFluidUnitInterpretation* createRockFluidUnitInterpretation(RESQML2_NS::RockVolumeFeature * rockFluidUnitFeature, const std::string & guid, const std::string & title);

		RESQML2_NS::GeobodyInterpretation* createGeobodyInterpretation(RESQML2_NS::RockVolumeFeature * geobody, const std::string & guid, const std::string & title);

		RESQML2_NS::StratigraphicUnitInterpretation* createStratigraphicUnitInterpretation(RESQML2_NS::RockVolumeFeature * stratiUnitFeature, const std::string & guid, const std::string & title);
		RESQML2_NS::StratigraphicColumn* createStratigraphicColumn(const std::string & guid, const std::string & title);
		RESQML2_NS::StratigraphicColumnRankInterpretation* createStratigraphicColumnRankInterpretationInAge(RESQML2_NS::Model * orgFeat, const std::string & guid, const std::string & title, unsigned long rank);
		RESQML2_NS::StratigraphicColumnRankInterpretation* createStratigraphicColumnRankInterpretationInApparentDepth(RESQML2_NS::Model * orgFeat, const std::string & guid, const std::string & title, unsigned long rank);
		RESQML2_NS::StratigraphicOccurrenceInterpretation* createStratigraphicOccurrenceInterpretationInAge(RESQML2_NS::Model * orgFeat, const std::string & guid, const std::string & title);
		RESQML2_NS::StratigraphicOccurrenceInterpretation* createStratigraphicOccurrenceInterpretationInApparentDepth(RESQML2_NS::Model * orgFeat, const std::string & guid, const std::string & title);

		/* REPRESENTATION */

		RESQML2_NS::TriangulatedSetRepresentation* createTriangulatedSetRepresentation(const std::string & guid, const std::string & title);
			
		RESQML2_NS::TriangulatedSetRepresentation* createTriangulatedSetRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp,
			const std::string & guid, const std::string & title);

		RESQML2_NS::PolylineSetRepresentation* createPolylineSetRepresentation(const std::string & guid, const std::string & title);

		RESQML2_NS::PolylineSetRepresentation* createPolylineSetRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp,
			const std::string & guid, const std::string & title);

		RESQML2_NS::PolylineSetRepresentation* createPolylineSetRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp,
			const std::string & guid, const std::string & title, gsoap_eml2_3::resqml22__LineRole roleKind);

		RESQML2_NS::PointSetRepresentation* createPointSetRepresentation(const std::string & guid, const std::string & title);

		RESQML2_NS::PointSetRepresentation* createPointSetRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp,
			const std::string & guid, const std::string & title);

		RESQML2_NS::PlaneSetRepresentation* createPlaneSetRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp,
			const std::string & guid, const std::string & title);

		RESQML2_NS::PolylineRepresentation* createPolylineRepresentation(const std::string & guid, const std::string & title, bool isClosed = false);

		RESQML2_NS::PolylineRepresentation* createPolylineRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp,
			const std::string & guid, const std::string & title, bool isClosed = false);

		RESQML2_NS::PolylineRepresentation* createPolylineRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp,
			const std::string & guid, const std::string & title, gsoap_eml2_3::resqml22__LineRole roleKind, bool isClosed = false);

		RESQML2_NS::Grid2dRepresentation* createGrid2dRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp,
			const std::string & guid, const std::string & title);

		RESQML2_NS::WellboreTrajectoryRepresentation* createWellboreTrajectoryRepresentation(RESQML2_NS::WellboreInterpretation * interp, const std::string & guid, const std::string & title, RESQML2_NS::MdDatum * mdInfo);
		RESQML2_NS::WellboreTrajectoryRepresentation* createWellboreTrajectoryRepresentation(RESQML2_NS::WellboreInterpretation * interp, const std::string & guid, const std::string & title, RESQML2_NS::DeviationSurveyRepresentation * deviationSurvey);

		RESQML2_NS::DeviationSurveyRepresentation* createDeviationSurveyRepresentation(RESQML2_NS::WellboreInterpretation * interp, const std::string & guid, const std::string & title, const bool & isFinal, RESQML2_NS::MdDatum * mdInfo);

		RESQML2_NS::WellboreFrameRepresentation* createWellboreFrameRepresentation(RESQML2_NS::WellboreInterpretation* interp, const std::string& guid, const std::string& title, RESQML2_NS::WellboreTrajectoryRepresentation* traj);
#ifdef WITH_RESQML2_2
		RESQML2_NS::SeismicWellboreFrameRepresentation* createSeismicWellboreFrameRepresentation(
			RESQML2_NS::WellboreInterpretation* interp, 
			const std::string& guid, const std::string& title, 
			RESQML2_NS::WellboreTrajectoryRepresentation* traj,
			double seismicReferenceDatum,
			double weatheringVelocity,
			RESQML2_NS::LocalTime3dCrs* crs);
#endif
		RESQML2_NS::WellboreMarkerFrameRepresentation* createWellboreMarkerFrameRepresentation(RESQML2_NS::WellboreInterpretation * interp, const std::string & guid, const std::string & title, RESQML2_NS::WellboreTrajectoryRepresentation * traj);

		RESQML2_NS::WellboreMarker* createWellboreMarker(RESQML2_NS::WellboreMarkerFrameRepresentation* wellboreMarkerFrame, const std::string& guid, const std::string& title);

		RESQML2_NS::WellboreMarker* createWellboreMarker(RESQML2_NS::WellboreMarkerFrameRepresentation* wellboreMarkerFrame, const std::string& guid, const std::string& title, gsoap_resqml2_0_1::resqml20__GeologicBoundaryKind geologicBoundaryKind);

		RESQML2_NS::BlockedWellboreRepresentation* createBlockedWellboreRepresentation(RESQML2_NS::WellboreInterpretation * interp,
			const std::string & guid, const std::string & title, RESQML2_NS::WellboreTrajectoryRepresentation * traj);

		RESQML2_NS::RepresentationSetRepresentation* createRepresentationSetRepresentation(
			RESQML2_NS::AbstractOrganizationInterpretation* interp,
			const std::string & guid,
			const std::string & title);

		RESQML2_NS::RepresentationSetRepresentation* createRepresentationSetRepresentation(
			const std::string & guid,
			const std::string & title);

		RESQML2_NS::NonSealedSurfaceFrameworkRepresentation* createNonSealedSurfaceFrameworkRepresentation(
			RESQML2_NS::StructuralOrganizationInterpretation* interp,
			const std::string & guid,
			const std::string & title);

		RESQML2_NS::SealedSurfaceFrameworkRepresentation* createSealedSurfaceFrameworkRepresentation(
			RESQML2_NS::StructuralOrganizationInterpretation* interp,
			const std::string & guid,
			const std::string & title);

		RESQML2_NS::SealedVolumeFrameworkRepresentation* createSealedVolumeFrameworkRepresentation(
			RESQML2_NS::StratigraphicColumnRankInterpretation* interp,
			const std::string & guid,
			const std::string & title,
			RESQML2_NS::SealedSurfaceFrameworkRepresentation* ssf);

		RESQML2_NS::AbstractIjkGridRepresentation* createPartialIjkGridRepresentation(const std::string & guid, const std::string & title);

		RESQML2_NS::AbstractIjkGridRepresentation* createPartialTruncatedIjkGridRepresentation(const std::string & guid, const std::string & title);

		RESQML2_NS::IjkGridExplicitRepresentation* createIjkGridExplicitRepresentation(const std::string & guid, const std::string & title,
			unsigned int iCount, unsigned int jCount, unsigned int kCount);

		RESQML2_NS::IjkGridExplicitRepresentation* createIjkGridExplicitRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp,
			const std::string & guid, const std::string & title,
			unsigned int iCount, unsigned int jCount, unsigned int kCount);

		RESQML2_NS::IjkGridParametricRepresentation* createIjkGridParametricRepresentation(const std::string & guid, const std::string & title,
			unsigned int iCount, unsigned int jCount, unsigned int kCount);

		RESQML2_NS::IjkGridParametricRepresentation* createIjkGridParametricRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp,
			const std::string & guid, const std::string & title,
			unsigned int iCount, unsigned int jCount, unsigned int kCount);

		RESQML2_NS::IjkGridLatticeRepresentation* createIjkGridLatticeRepresentation(const std::string & guid, const std::string & title,
			unsigned int iCount, unsigned int jCount, unsigned int kCount);

		RESQML2_NS::IjkGridLatticeRepresentation* createIjkGridLatticeRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp,
			const std::string & guid, const std::string & title,
			unsigned int iCount, unsigned int jCount, unsigned int kCount);

		RESQML2_NS::IjkGridNoGeometryRepresentation* createIjkGridNoGeometryRepresentation(
			const std::string & guid, const std::string & title,
			unsigned int iCount, unsigned int jCount, unsigned int kCount);

		RESQML2_NS::IjkGridNoGeometryRepresentation* createIjkGridNoGeometryRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp,
			const std::string & guid, const std::string & title,
			unsigned int iCount, unsigned int jCount, unsigned int kCount);

		RESQML2_NS::UnstructuredGridRepresentation* createUnstructuredGridRepresentation(const std::string & guid, const std::string & title,
			const ULONG64 & cellCount);

		RESQML2_NS::SubRepresentation* createSubRepresentation(
			const std::string & guid, const std::string & title);

		RESQML2_NS::SubRepresentation* createSubRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp,
			const std::string & guid, const std::string & title);

		RESQML2_NS::GridConnectionSetRepresentation* createGridConnectionSetRepresentation(const std::string & guid, const std::string & title);

		RESQML2_NS::GridConnectionSetRepresentation* createGridConnectionSetRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp,
			const std::string & guid, const std::string & title);

		/* PROPERTIES */

		EML2_NS::TimeSeries* createTimeSeries(const std::string & guid, const std::string & title);

		RESQML2_NS::StringTableLookup* createStringTableLookup(const std::string & guid, const std::string & title);

		RESQML2_0_1_NS::PropertyKind* createPropertyKind(const std::string & guid, const std::string & title,
			const std::string & namingSystem, gsoap_resqml2_0_1::resqml20__ResqmlUom uom, gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind parentEnergisticsPropertyKind);

		RESQML2_0_1_NS::PropertyKind* createPropertyKind(const std::string & guid, const std::string & title,
			const std::string & namingSystem, gsoap_resqml2_0_1::resqml20__ResqmlUom uom, EML2_NS::PropertyKind * parentPropType);

		RESQML2_0_1_NS::PropertyKind* createPropertyKind(const std::string & guid, const std::string & title,
			const std::string & namingSystem, const std::string & nonStandardUom, gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind parentEnergisticsPropertyKind);

		RESQML2_0_1_NS::PropertyKind* createPropertyKind(const std::string & guid, const std::string & title,
			const std::string & namingSystem, const std::string & nonStandardUom, EML2_NS::PropertyKind * parentPropType);

		EML2_NS::PropertyKind* createPropertyKind(const std::string & guid, const std::string & title,
			gsoap_eml2_1::eml21__QuantityClassKind quantityClass, bool isAbstract = false, EML2_NS::PropertyKind* parentPropertyKind = nullptr);

		RESQML2_NS::PropertySet* createPropertySet(const std::string & guid, const std::string & title,
			bool hasMultipleRealizations, bool hasSinglePropertyKind, gsoap_eml2_3::resqml22__TimeSetKind timeSetKind);

		RESQML2_0_1_NS::CommentProperty* createCommentProperty(RESQML2_NS::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			unsigned int dimension, gsoap_eml2_3::resqml22__IndexableElement attachmentKind, gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind energisticsPropertyKind);

		RESQML2_NS::CommentProperty* createCommentProperty(RESQML2_NS::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			unsigned int dimension, gsoap_eml2_3::resqml22__IndexableElement attachmentKind, EML2_NS::PropertyKind * localPropType);

		RESQML2_0_1_NS::ContinuousProperty* createContinuousProperty(RESQML2_NS::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			unsigned int dimension, gsoap_eml2_3::resqml22__IndexableElement attachmentKind, gsoap_resqml2_0_1::resqml20__ResqmlUom uom, gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind energisticsPropertyKind);

		RESQML2_NS::ContinuousProperty* createContinuousProperty(RESQML2_NS::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			unsigned int dimension, gsoap_eml2_3::resqml22__IndexableElement attachmentKind, gsoap_resqml2_0_1::resqml20__ResqmlUom uom, EML2_NS::PropertyKind * localPropType);

		RESQML2_0_1_NS::ContinuousProperty* createContinuousProperty(RESQML2_NS::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			unsigned int dimension, gsoap_eml2_3::resqml22__IndexableElement attachmentKind, std::string nonStandardUom, gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind energisticsPropertyKind);

		RESQML2_NS::ContinuousProperty* createContinuousProperty(RESQML2_NS::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			unsigned int dimension, gsoap_eml2_3::resqml22__IndexableElement attachmentKind, const std::string & nonStandardUom, EML2_NS::PropertyKind * localPropType);

		RESQML2_0_1_NS::DiscreteProperty* createDiscreteProperty(RESQML2_NS::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			unsigned int dimension, gsoap_eml2_3::resqml22__IndexableElement attachmentKind, gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind energisticsPropertyKind);

		RESQML2_NS::DiscreteProperty* createDiscreteProperty(RESQML2_NS::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			unsigned int dimension, gsoap_eml2_3::resqml22__IndexableElement attachmentKind, EML2_NS::PropertyKind * localPropType);

		RESQML2_0_1_NS::CategoricalProperty* createCategoricalProperty(RESQML2_NS::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			unsigned int dimension, gsoap_eml2_3::resqml22__IndexableElement attachmentKind,
			RESQML2_NS::StringTableLookup* strLookup, gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind energisticsPropertyKind);

		RESQML2_NS::CategoricalProperty* createCategoricalProperty(RESQML2_NS::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			unsigned int dimension, gsoap_eml2_3::resqml22__IndexableElement attachmentKind,
			RESQML2_NS::StringTableLookup* strLookup, EML2_NS::PropertyKind * localPropType);

		//************* ACTIVITIES ***********/

		EML2_NS::ActivityTemplate* createActivityTemplate(const std::string & guid, const std::string & title);

		EML2_NS::Activity* createActivity(EML2_NS::ActivityTemplate* activityTemplate, const std::string & guid, const std::string & title);

		//*************** WITSML *************/

		WITSML2_0_NS::Well* createWell(const std::string & guid,
			const std::string & title);

		WITSML2_0_NS::Well* createWell(const std::string & guid,
			const std::string & title,
			const std::string & operator_,
			gsoap_eml2_1::eml21__WellStatus statusWell,
			gsoap_eml2_1::witsml20__WellDirection directionWell
		);

		WITSML2_0_NS::Wellbore* createWellbore(WITSML2_0_NS::Well* witsmlWell,
			const std::string & guid,
			const std::string & title);

		WITSML2_0_NS::Wellbore* createWellbore(WITSML2_0_NS::Well* witsmlWell,
			const std::string & guid,
			const std::string & title,
			gsoap_eml2_1::eml21__WellStatus statusWellbore,
			bool isActive,
			bool achievedTD
		);

		WITSML2_0_NS::WellCompletion* createWellCompletion(WITSML2_0_NS::Well* witsmlWell,
			const std::string & guid,
			const std::string & title);

		WITSML2_0_NS::WellboreCompletion* createWellboreCompletion(WITSML2_0_NS::Wellbore* witsmlWellbore,
			WITSML2_0_NS::WellCompletion* wellCompletion,
			const std::string & guid,
			const std::string & title,
			const std::string & wellCompletionName);

		WITSML2_0_NS::WellboreGeometry* createWellboreGeometry(WITSML2_0_NS::Wellbore* witsmlWellbore,
			const std::string & guid,
			const std::string & title,
			gsoap_eml2_1::witsml20__ChannelStatus channelStatus);

		WITSML2_0_NS::Trajectory* createTrajectory(WITSML2_0_NS::Wellbore* witsmlWellbore,
			const std::string & guid,
			const std::string & title,
			gsoap_eml2_1::witsml20__ChannelStatus channelStatus);

		WITSML2_0_NS::Log* createLog(WITSML2_0_NS::Wellbore* witsmlWellbore,
			const std::string & guid,
			const std::string & title);

		WITSML2_0_NS::ChannelSet* createChannelSet(
			const std::string & guid,
			const std::string & title);

		WITSML2_0_NS::Channel* createChannel(EML2_NS::PropertyKind * propertyKind,
			const std::string & guid, const std::string & title,
			const std::string & mnemonic, gsoap_eml2_1::eml21__UnitOfMeasure uom, gsoap_eml2_1::witsml20__EtpDataType dataType, gsoap_eml2_1::witsml20__ChannelStatus growingStatus,
			const std::string & timeDepth, const std::string & loggingCompanyName);

#ifdef WITH_RESQML2_2
		//************************************/
		//************ EML2.3 ****************/
		//************************************/

		EML2_NS::GraphicalInformationSet* createGraphicalInformationSet(const std::string & guid, const std::string & title);

		RESQML2_NS::DiscreteColorMap* createDiscreteColorMap(const std::string& guid, const std::string& title);

		RESQML2_NS::ContinuousColorMap* createContinuousColorMap(const std::string& guid, const std::string& title,
			gsoap_eml2_3::resqml22__InterpolationDomain interpolationDomain, gsoap_eml2_3::resqml22__InterpolationMethod interpolationMethod);
#endif
		//************************************/
		//***** STANDARD PROP KIND ***********/
		//************************************/
		
		RESQML2_0_1_NS::PropertyKindMapper* getPropertyKindMapper() const;

		//************************************/
		//************* WARNINGS *************/
		//************************************/

		void clearWarnings();
		const std::vector<std::string> & getWarnings() const;
		
		template <class valueType>
		valueType* createPartial(const std::string & guid, const std::string & title, const std::string & version = "")
		{
			gsoap_resqml2_0_1::eml20__DataObjectReference* dor = gsoap_resqml2_0_1::soap_new_eml20__DataObjectReference(gsoapContext);
			dor->UUID = guid.empty() ? generateRandomUuidAsString() : guid;
			dor->Title = title;
			if (!version.empty()) {
				dor->VersionString = gsoap_resqml2_0_1::soap_new_std__string(gsoapContext);
				dor->VersionString->assign(version);
			}
			valueType* result = new valueType(dor);
			addOrReplaceDataObject(result);
			return result;
		}
		
		// Template for partial RESQML2.2
#ifdef WITH_RESQML2_2		
		%template(createPartialDiscreteColorMap) createPartial<RESQML2_2_NS::DiscreteColorMap>;
		%template(createPartialContinuousColorMap) createPartial<RESQML2_2_NS::ContinuousColorMap>;
		%template(createPartialSeismicWellboreFrameRepresentation) createPartial<RESQML2_2_NS::SeismicWellboreFrameRepresentation>;
#endif
		// Template for partial RESQML2.0.1
		
		%template(createPartialLocalDepth3dCrs) createPartial<RESQML2_0_1_NS::LocalDepth3dCrs>;
		%template(createPartialLocalTime3dCrs) createPartial<RESQML2_0_1_NS::LocalTime3dCrs>;
		%template(createPartialMdDatum) createPartial<RESQML2_0_1_NS::MdDatum>;

		%template(createPartialHorizon) createPartial<RESQML2_0_1_NS::Horizon>;
		%template(createPartialTectonicBoundaryFeature) createPartial<RESQML2_0_1_NS::TectonicBoundaryFeature>;
		%template(createPartialFrontierFeature) createPartial<RESQML2_0_1_NS::FrontierFeature>;
		%template(createPartialWellboreFeature) createPartial<RESQML2_0_1_NS::WellboreFeature>;
		%template(createPartialSeismicLineFeature) createPartial<RESQML2_0_1_NS::SeismicLineFeature>;
		%template(createPartialSeismicLineSetFeature) createPartial<RESQML2_0_1_NS::SeismicLineSetFeature>;
		%template(createPartialSeismicLatticeFeature) createPartial<RESQML2_0_1_NS::SeismicLatticeFeature>;
		%template(createPartialOrganizationFeature) createPartial<RESQML2_0_1_NS::OrganizationFeature>;
		%template(createPartialStratigraphicUnitFeature) createPartial<RESQML2_0_1_NS::StratigraphicUnitFeature>;
		%template(createPartialGeobodyFeature) createPartial<RESQML2_0_1_NS::GeobodyFeature>;
		%template(createPartialFluidBoundaryFeature) createPartial<RESQML2_0_1_NS::FluidBoundaryFeature>;

		%template(createPartialGenericFeatureInterpretation) createPartial<RESQML2_0_1_NS::GenericFeatureInterpretation>;
		%template(createPartialHorizonInterpretation) createPartial<RESQML2_0_1_NS::HorizonInterpretation>;
		%template(createPartialFaultInterpretation) createPartial<RESQML2_0_1_NS::FaultInterpretation>;
		%template(createPartialWellboreInterpretation) createPartial<RESQML2_0_1_NS::WellboreInterpretation>;
		%template(createPartialStratigraphicUnitInterpretation) createPartial<RESQML2_0_1_NS::StratigraphicUnitInterpretation>;
		%template(createPartialStructuralOrganizationInterpretation) createPartial<RESQML2_0_1_NS::StructuralOrganizationInterpretation>;
		%template(createPartialStratigraphicColumnRankInterpretation) createPartial<RESQML2_0_1_NS::StratigraphicColumnRankInterpretation>;
		%template(createPartialStratigraphicOccurrenceInterpretation) createPartial<RESQML2_0_1_NS::StratigraphicOccurrenceInterpretation>;
		%template(createPartialEarthModelInterpretation) createPartial<RESQML2_0_1_NS::EarthModelInterpretation>;
		%template(createPartialGeobodyBoundaryInterpretation) createPartial<RESQML2_0_1_NS::GeobodyBoundaryInterpretation>;
		%template(createPartialGeobodyInterpretation) createPartial<RESQML2_0_1_NS::GeobodyInterpretation>;

		%template(createPartialPolylineSetRepresentation) createPartial<RESQML2_0_1_NS::PolylineSetRepresentation>;
		%template(createPartialPointSetRepresentation) createPartial<RESQML2_0_1_NS::PointSetRepresentation>;
		%template(createPartialPlaneSetRepresentation) createPartial<RESQML2_0_1_NS::PlaneSetRepresentation>;
		%template(createPartialPolylineRepresentation) createPartial<RESQML2_0_1_NS::PolylineRepresentation>;
		%template(createPartialGrid2dRepresentation) createPartial<RESQML2_0_1_NS::Grid2dRepresentation>;
		%template(createPartialTriangulatedSetRepresentation) createPartial<RESQML2_0_1_NS::TriangulatedSetRepresentation>;
		%template(createPartialWellboreTrajectoryRepresentation) createPartial<RESQML2_0_1_NS::WellboreTrajectoryRepresentation>;
		%template(createPartialDeviationSurveyRepresentation) createPartial<RESQML2_0_1_NS::DeviationSurveyRepresentation>;
		%template(createPartialRepresentationSetRepresentation) createPartial<RESQML2_0_1_NS::RepresentationSetRepresentation>;
		%template(createPartialNonSealedSurfaceFrameworkRepresentation) createPartial<RESQML2_0_1_NS::NonSealedSurfaceFrameworkRepresentation>;
		%template(createPartialSealedSurfaceFrameworkRepresentation) createPartial<RESQML2_0_1_NS::SealedSurfaceFrameworkRepresentation>;

		%template(createPartialUnstructuredGridRepresentation) createPartial<RESQML2_0_1_NS::UnstructuredGridRepresentation>;
		%template(createPartialSubRepresentation) createPartial<RESQML2_0_1_NS::SubRepresentation>;
		%template(createPartialGridConnectionSetRepresentation) createPartial<RESQML2_0_1_NS::GridConnectionSetRepresentation>;

		%template(createPartialTimeSeries) createPartial<RESQML2_0_1_NS::TimeSeries>;

		%template(createPartialPropertyKind) createPartial<RESQML2_0_1_NS::PropertyKind>;
		%template(createPartialPropertySet) createPartial<RESQML2_0_1_NS::PropertySet>;
		%template(createPartialStringTableLookup) createPartial<RESQML2_0_1_NS::StringTableLookup>;
		%template(createPartialDiscreteProperty) createPartial<RESQML2_0_1_NS::DiscreteProperty>;
		%template(createPartialCategoricalProperty) createPartial<RESQML2_0_1_NS::CategoricalProperty>;
		%template(createPartialCommentProperty) createPartial<RESQML2_0_1_NS::CommentProperty>;
		%template(createPartialContinuousProperty) createPartial<RESQML2_0_1_NS::ContinuousProperty>;

		%template(createPartialActivity) createPartial<RESQML2_0_1_NS::Activity>;
		%template(createPartialActivityTemplate) createPartial<RESQML2_0_1_NS::ActivityTemplate>;
		
		// Template for partial WITSML2.0
		
		%template(createPartialWell) createPartial<WITSML2_0_NS::Well>;
		%template(createPartialWellCompletion) createPartial<WITSML2_0_NS::WellCompletion>;
		%template(createPartialWellbore) createPartial<WITSML2_0_NS::Wellbore>;
		%template(createPartialWellboreCompletion) createPartial<WITSML2_0_NS::WellboreCompletion>;
		%template(createPartialWellboreGeometry) createPartial<WITSML2_0_NS::WellboreGeometry>;
		%template(createPartialTrajectory) createPartial<WITSML2_0_NS::Trajectory>;
		%template(createPartialLog) createPartial<WITSML2_0_NS::Log>;
		%template(createPartialChannelSet) createPartial<WITSML2_0_NS::ChannelSet>;
		%template(createPartialChannel) createPartial<WITSML2_0_NS::Channel>;
	};
	
	class EpcDocument
	{
	public:
	
		EpcDocument(const std::string & fileName);
		
		void setFilePath(const std::string & fp);

		virtual void serializeFrom(const DataObjectRepository & repo, bool useZip64 = false);
		virtual std::string deserializeInto(DataObjectRepository & repo, DataObjectRepository::openingMode hdfPermissionAccess = DataObjectRepository::openingMode::READ_ONLY);
		void close();
		std::string getStorageDirectory() const;
		std::string getName() const;
		
		void setExtendedCoreProperty(const std::string & key, const std::string & value);
		std::string getExtendedCoreProperty(const std::string & key);
	};
	
	class EnumStringMapper
	{
	public :
		EnumStringMapper();

		std::string getEnergisticsPropertyKindName(gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind energisticsPropertyKind) const;
		gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind getEnergisticsPropertyKind(const std::string & energisticsPropertyKindName) const;

		std::string getEnergisticsUnitOfMeasureName(gsoap_resqml2_0_1::resqml20__ResqmlUom energisticsUom) const;
		gsoap_resqml2_0_1::resqml20__ResqmlUom getEnergisticsUnitOfMeasure(const std::string & energisticsUomName) const;

		std::string getFacet(gsoap_resqml2_0_1::resqml20__Facet facet) const;
		gsoap_resqml2_0_1::resqml20__Facet getFacet(const std::string & facet) const;

		std::string lengthUomToString(gsoap_eml2_1::eml21__LengthUom witsmlUom) const;

		std::string verticalCoordinateUomToString(gsoap_eml2_1::eml21__VerticalCoordinateUom witsmlUom) const;

		std::string planeAngleUomToString(gsoap_eml2_1::eml21__PlaneAngleUom witsmlUom) const;
	};
}

