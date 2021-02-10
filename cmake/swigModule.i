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



#ifdef SWIGJAVA
	// Notice you must not compile the C++ API with an optimisation superior to -O1 with gcc 4.4.7 in order SWIG to work
	
	/*
	 When using multiple modules or the nspace feature it is common to invoke SWIG with a different -package command line option for each module.
	 However, by default the generated code may not compile if generated classes in one package use generated classes in another package.
	 The visibility of the getCPtr() and pointer constructor generated from the javabody typemaps needs changing.
	 The default visibility is protected but it needs to be public for access from a different package. Just changing 'protected' to 'public' in the typemap achieves this.
	 Two macros are available in java.swg to make this easier and using them is the preferred approach over simply copying the typemaps and modifying as this is forward compatible with any changes in the javabody typemap in future versions of SWIG.
	 The macros are for the proxy and typewrapper classes and can respectively be used to to make the method and constructor public:
	  SWIG_JAVABODY_PROXY(public, public, SWIGTYPE)
	  SWIG_JAVABODY_TYPEWRAPPER(public, public, public, SWIGTYPE)
	*/
	SWIG_JAVABODY_PROXY(public, public, SWIGTYPE)
	SWIG_JAVABODY_TYPEWRAPPER(public, public, public, SWIGTYPE)
	
	// http://www.swig.org/Doc3.0/SWIGDocumentation.html#Java_proper_enums
	%include "enums.swg"
	%javaconst(1);
#endif

//************************
// STD STRING
//************************

#ifdef SWIGCSHARP
	%include "std_string.i"
	SWIG_CSBODY_PROXY(public, public, SWIGTYPE)
	SWIG_CSBODY_TYPEWRAPPER(public, public, public, SWIGTYPE)
#else
	%include "std_string.i"
#endif

//************************
// POD C ARRAYS
//************************
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

//************************
// EXCEPTIONS
//************************

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

%include "../src/nsDefinitions.h"

#if defined(SWIGJAVA) || defined(SWIGCSHARP)
	%nspace COMMON_NS::DataObjectRepository;
	%nspace COMMON_NS::EnumStringMapper;
	%nspace COMMON_NS::EpcDocument;
	%nspace COMMON_NS::AbstractObject;
	%nspace COMMON_NS::EpcExternalPartReference;
	%nspace COMMON_NS::AbstractHdfProxy;
	%nspace COMMON_NS::HdfProxy;
	%nspace COMMON_NS::PropertyKind;
#endif

namespace RESQML2_NS
{
	class Activity;
}

#ifdef SWIGJAVA
	%include "swigResqml2JavaInclude.i"
#endif

namespace COMMON_NS
{
	%nodefaultctor; // Disable creation of default constructors
	
	class AbstractObject
	{
	public:
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
		RESQML2_NS::Activity * getActivity (unsigned int index) const;
	};
	
	class PropertyKind : public COMMON_NS::AbstractObject
	{
	public:
		const std::string & getNamingSystem() const;
		
		gsoap_resqml2_0_1::resqml20__ResqmlUom getUom() const;
		std::string getUomAsString() const;
	};
	
	//************************************
	//************ HDF *******************
	//************************************
	class EpcExternalPartReference : public AbstractObject
	{
		std::string getRelativePath();
	};

	class AbstractHdfProxy : public EpcExternalPartReference
	{
	public:
		virtual bool isOpened() = 0;
		virtual void close() = 0;
		
		/**
		* Set the maximum size for a chunk of a dataset only in case the HDF5 file is compressed.
		* Chunk dimensions, and consequently actual size, will be computed from this maximum chunk memory size.
		* Chunks dimensions are computed by reducing dataset dimensions from slowest to fastest until the max chunk size is honored.
		*
		* Example : Let's take a 3d property 4x3x2 (fastest from slowest) of double with a max chunk size of 100 bytes
		* The total size of this property is 4*3*2*8 = 192 bytes which is greater than 100 bytes, the max chunk size.
		* The computed chunk dimension will consequently be 4*3*1 = 96 which is lower than (not equal to) 100 bytes, the max chunk size.
		* If we would have set a max chun size of 20 bytes, the chunk dimension would have been computed as 2*1*1 (16 bytes), etc...
		*
		* @param newMaxChunkSize The maximum chunk size to set in bytes.
		*/
		void setMaxChunkSize(unsigned int newMaxChunkSize);
	};

	class HdfProxy : public AbstractHdfProxy
	{
	public:
		void setCompressionLevel(unsigned int newCompressionLevel);
	};
}

%{
#define SWIG_FILE_WITH_INIT // In case we use Python Swig Wrapping
%}

%include "swigResqml2Include.i"
%include "swigResqml2_0_1Include.i"
%include "swigWitsml2_0Include.i"

%template(StringVector) std::vector< std::string >;

%{
#include "../src/common/EnumStringMapper.h"
#include "../src/common/EpcDocument.h"
%}

namespace RESQML2_NS
{
	class Activity;
}

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
		
		DataObjectRepository();
		DataObjectRepository(const std::string & propertyKindMappingFilesDirectory);
		
		void clear();
		
		bool hasHdfProxyFactory();
		
		std::vector<RESQML2_0_1_NS::LocalDepth3dCrs*> getLocalDepth3dCrsSet() const;

		std::vector<RESQML2_0_1_NS::LocalTime3dCrs*> getLocalTime3dCrsSet() const;
		
		RESQML2_NS::AbstractLocal3dCrs* getDefaultCrs() const;
		void setDefaultCrs(RESQML2_NS::AbstractLocal3dCrs* crs);
		
		std::vector<RESQML2_0_1_NS::StratigraphicColumn*> getStratigraphicColumnSet() const;

		std::vector<RESQML2_0_1_NS::TectonicBoundaryFeature*> getFaultSet() const;

		std::vector<RESQML2_0_1_NS::TectonicBoundaryFeature*> getFractureSet() const;

		std::vector<RESQML2_0_1_NS::PolylineSetRepresentation *> getFaultPolylineSetRepSet() const;

		std::vector<RESQML2_0_1_NS::PolylineSetRepresentation *> getFracturePolylineSetRepSet() const;

		std::vector<RESQML2_0_1_NS::PolylineSetRepresentation *> getFrontierPolylineSetRepSet() const;

		std::vector<RESQML2_0_1_NS::TriangulatedSetRepresentation *> getFaultTriangulatedSetRepSet() const;

		std::vector<RESQML2_0_1_NS::TriangulatedSetRepresentation *> getFractureTriangulatedSetRepSet() const;

		std::vector<RESQML2_0_1_NS::Horizon*> getHorizonSet() const;

		std::vector<RESQML2_0_1_NS::GeneticBoundaryFeature*> getGeobodyBoundarySet() const;
		unsigned int getGeobodyBoundaryCount() const;
		RESQML2_0_1_NS::GeneticBoundaryFeature* getGeobodyBoundary(unsigned int index) const;

		std::vector<RESQML2_0_1_NS::GeobodyFeature*> getGeobodySet() const;

		std::vector<RESQML2_0_1_NS::Grid2dRepresentation *> getHorizonGrid2dRepSet() const;

		std::vector<RESQML2_0_1_NS::PolylineRepresentation *> getHorizonPolylineRepSet() const;

		std::vector<RESQML2_0_1_NS::PolylineSetRepresentation *> getHorizonPolylineSetRepSet() const;

		std::vector<RESQML2_0_1_NS::TriangulatedSetRepresentation *> getHorizonTriangulatedSetRepSet() const;

		std::vector<RESQML2_0_1_NS::TriangulatedSetRepresentation*> getAllTriangulatedSetRepSet() const;

		std::vector<RESQML2_0_1_NS::Grid2dRepresentation*> getAllGrid2dRepresentationSet() const;

		std::vector<RESQML2_0_1_NS::PolylineSetRepresentation*> getAllPolylineSetRepSet() const;

		std::vector<RESQML2_0_1_NS::TriangulatedSetRepresentation*> getUnclassifiedTriangulatedSetRepSet() const;

		std::vector<RESQML2_0_1_NS::SeismicLineFeature*> getSeismicLineSet() const;

		std::vector<RESQML2_0_1_NS::WellboreFeature*> getWellboreSet();

		std::vector<RESQML2_0_1_NS::WellboreTrajectoryRepresentation *> getWellboreTrajectoryRepresentationSet() const;

		std::vector<RESQML2_0_1_NS::DeviationSurveyRepresentation *> getDeviationSurveyRepresentationSet() const;

		std::vector<RESQML2_NS::RepresentationSetRepresentation*> getRepresentationSetRepresentationSet() const;

		unsigned int getRepresentationSetRepresentationCount() const;

		RESQML2_NS::RepresentationSetRepresentation* getRepresentationSetRepresentation(unsigned int index) const;

		std::vector<RESQML2_0_1_NS::PolylineRepresentation*> getAllPolylineRepresentationSet() const;

		std::vector<RESQML2_0_1_NS::PolylineRepresentation*> getSeismicLinePolylineRepSet() const;

		std::vector<RESQML2_0_1_NS::AbstractIjkGridRepresentation*> getIjkGridRepresentationSet() const;
		unsigned int getIjkGridRepresentationCount() const;
		RESQML2_0_1_NS::AbstractIjkGridRepresentation* getIjkGridRepresentation(unsigned int index) const;

		std::vector<RESQML2_0_1_NS::IjkGridParametricRepresentation*> getIjkGridParametricRepresentationSet() const;

		std::vector<RESQML2_0_1_NS::IjkGridExplicitRepresentation*> getIjkGridExplicitRepresentationSet() const;

		std::vector<RESQML2_0_1_NS::IjkGridLatticeRepresentation*> getIjkSeismicCubeGridRepresentationSet() const;

		std::vector<RESQML2_0_1_NS::UnstructuredGridRepresentation*> getUnstructuredGridRepresentationSet() const;

		std::vector<RESQML2_0_1_NS::FrontierFeature*> getFrontierSet() const;

		std::vector<RESQML2_0_1_NS::OrganizationFeature*> getOrganizationSet() const;

		std::vector<RESQML2_NS::TimeSeries*> getTimeSeriesSet() const;

		std::vector<RESQML2_NS::SubRepresentation*> getSubRepresentationSet() const;
		unsigned int getSubRepresentationCount() const;
		RESQML2_NS::SubRepresentation* getSubRepresentation(unsigned int index) const;

		std::vector<RESQML2_0_1_NS::PointSetRepresentation*> getPointSetRepresentationSet() const;
		unsigned int getPointSetRepresentationCount() const;
		RESQML2_0_1_NS::PointSetRepresentation* getPointSetRepresentation(unsigned int index) const;

		std::vector<COMMON_NS::AbstractHdfProxy*> getHdfProxySet() const;
		unsigned int getHdfProxyCount() const;
		COMMON_NS::AbstractHdfProxy* getHdfProxy(unsigned int index) const;
		
		COMMON_NS::AbstractHdfProxy* getDefaultHdfProxy() const;
		void setDefaultHdfProxy(COMMON_NS::AbstractHdfProxy* hdfProxy);
		
		COMMON_NS::AbstractObject* getDataObjectByUuid(const std::string & uuid) const;
		COMMON_NS::AbstractObject* getDataObjectByUuidAndVersion(const std::string & uuid, const std::string & version) const;
		
		template <class valueType>
		std::vector<valueType*> getDataObjects() const
		{
			std::vector<valueType*> result;

			for (std::unordered_map< std::string, std::vector<COMMON_NS::AbstractObject*> >::const_iterator it = dataObjects.begin(); it != dataObjects.end(); ++it) {
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
		
		COMMON_NS::AbstractHdfProxy* createHdfProxy(const std::string & guid, const std::string & title, const std::string & packageDirAbsolutePath, const std::string & externalFilePath, DataObjectRepository::openingMode hdfPermissionAccess);


		//************ CRS *******************


		RESQML2_0_1_NS::LocalDepth3dCrs* createLocalDepth3dCrs(const std::string & guid, const std::string & title,
			double originOrdinal1, double originOrdinal2, double originOrdinal3,
			double arealRotation,
			gsoap_resqml2_0_1::eml20__LengthUom projectedUom, unsigned long projectedEpsgCode,
			gsoap_resqml2_0_1::eml20__LengthUom verticalUom, unsigned int verticalEpsgCode, bool isUpOriented);


		RESQML2_0_1_NS::LocalDepth3dCrs* createLocalDepth3dCrs(const std::string & guid, const std::string & title,
			const double & originOrdinal1, const double & originOrdinal2, const double & originOrdinal3,
			const double & arealRotation,
			const gsoap_resqml2_0_1::eml20__LengthUom & projectedUom, const std::string & projectedUnknownReason,
			const gsoap_resqml2_0_1::eml20__LengthUom & verticalUom, const std::string & verticalUnknownReason, const bool & isUpOriented);


		RESQML2_0_1_NS::LocalDepth3dCrs* createLocalDepth3dCrs(const std::string & guid, const std::string & title,
			const double & originOrdinal1, const double & originOrdinal2, const double & originOrdinal3,
			const double & arealRotation,
			const gsoap_resqml2_0_1::eml20__LengthUom & projectedUom, const unsigned long & projectedEpsgCode,
			const gsoap_resqml2_0_1::eml20__LengthUom & verticalUom, const std::string & verticalUnknownReason, const bool & isUpOriented);


		RESQML2_0_1_NS::LocalDepth3dCrs* createLocalDepth3dCrs(const std::string & guid, const std::string & title,
			const double & originOrdinal1, const double & originOrdinal2, const double & originOrdinal3,
			const double & arealRotation,
			const gsoap_resqml2_0_1::eml20__LengthUom & projectedUom, const std::string & projectedUnknownReason,
			const gsoap_resqml2_0_1::eml20__LengthUom & verticalUom, const unsigned int & verticalEpsgCode, const bool & isUpOriented);


		RESQML2_0_1_NS::LocalTime3dCrs* createLocalTime3dCrs(const std::string & guid, const std::string & title,
			const double & originOrdinal1, const double & originOrdinal2, const double & originOrdinal3,
			const double & arealRotation,
			const gsoap_resqml2_0_1::eml20__LengthUom & projectedUom, const unsigned long & projectedEpsgCode,
			const gsoap_resqml2_0_1::eml20__TimeUom & timeUom,
			const gsoap_resqml2_0_1::eml20__LengthUom & verticalUom, const unsigned int & verticalEpsgCode, const bool & isUpOriented);


		RESQML2_0_1_NS::LocalTime3dCrs* createLocalTime3dCrs(const std::string & guid, const std::string & title,
			const double & originOrdinal1, const double & originOrdinal2, const double & originOrdinal3,
			const double & arealRotation,
			const gsoap_resqml2_0_1::eml20__LengthUom & projectedUom, const std::string & projectedUnknownReason,
			const gsoap_resqml2_0_1::eml20__TimeUom & timeUom,
			const gsoap_resqml2_0_1::eml20__LengthUom & verticalUom, const std::string & verticalUnknownReason, const bool & isUpOriented);


		RESQML2_0_1_NS::LocalTime3dCrs* createLocalTime3dCrs(const std::string & guid, const std::string & title,
			const double & originOrdinal1, const double & originOrdinal2, const double & originOrdinal3,
			const double & arealRotation,
			const gsoap_resqml2_0_1::eml20__LengthUom & projectedUom, const unsigned long & projectedEpsgCode,
			const gsoap_resqml2_0_1::eml20__TimeUom & timeUom,
			const gsoap_resqml2_0_1::eml20__LengthUom & verticalUom, const std::string & verticalUnknownReason, const bool & isUpOriented);


		RESQML2_0_1_NS::LocalTime3dCrs* createLocalTime3dCrs(const std::string & guid, const std::string & title,
			const double & originOrdinal1, const double & originOrdinal2, const double & originOrdinal3,
			const double & arealRotation,
			const gsoap_resqml2_0_1::eml20__LengthUom & projectedUom, const std::string & projectedUnknownReason,
			const gsoap_resqml2_0_1::eml20__TimeUom & timeUom,
			const gsoap_resqml2_0_1::eml20__LengthUom & verticalUom, const unsigned int & verticalEpsgCode, const bool & isUpOriented);

		RESQML2_NS::MdDatum* createMdDatum(const std::string & guid, const std::string & title,
			RESQML2_NS::AbstractLocal3dCrs * locCrs, const gsoap_resqml2_0_1::resqml20__MdReference & originKind,
			const double & referenceLocationOrdinal1, const double & referenceLocationOrdinal2, const double & referenceLocationOrdinal3);

		//************ FEATURE ***************

		RESQML2_0_1_NS::BoundaryFeature* createBoundaryFeature(const std::string & guid, const std::string & title);

		RESQML2_0_1_NS::Horizon* createHorizon(const std::string & guid, const std::string & title);

		RESQML2_0_1_NS::GeneticBoundaryFeature* createGeobodyBoundaryFeature(const std::string & guid, const std::string & title);

		RESQML2_0_1_NS::GeobodyFeature* createGeobodyFeature(const std::string & guid, const std::string & title);

		RESQML2_0_1_NS::TectonicBoundaryFeature* createFault(const std::string & guid, const std::string & title);

		RESQML2_0_1_NS::TectonicBoundaryFeature* createFracture(const std::string & guid, const std::string & title);

		RESQML2_0_1_NS::WellboreFeature* createWellboreFeature(const std::string & guid, const std::string & title);

		RESQML2_0_1_NS::SeismicLatticeFeature* createSeismicLattice(const std::string & guid, const std::string & title,
			const int & inlineIncrement, const int & crosslineIncrement,
			const unsigned int & originInline, const unsigned int & originCrossline,
			const unsigned int & inlineCount, const unsigned int & crosslineCount);

		RESQML2_0_1_NS::SeismicLineFeature* createSeismicLine(const std::string & guid, const std::string & title,
			const int & traceIndexIncrement, const unsigned int & firstTraceIndex, const unsigned int & traceCount);

		RESQML2_0_1_NS::SeismicLineSetFeature* createSeismicLineSet(const std::string & guid, const std::string & title);

		RESQML2_0_1_NS::FrontierFeature* createFrontier(const std::string & guid, const std::string & title);

		RESQML2_0_1_NS::StratigraphicUnitFeature* createStratigraphicUnit(const std::string & guid, const std::string & title);

		RESQML2_0_1_NS::OrganizationFeature* createStructuralModel(const std::string & guid, const std::string & title);

		RESQML2_0_1_NS::OrganizationFeature* createStratigraphicModel(const std::string & guid, const std::string & title);

		RESQML2_0_1_NS::OrganizationFeature* createRockFluidModel(const std::string & guid, const std::string & title);

		RESQML2_0_1_NS::OrganizationFeature* createEarthModel(const std::string & guid, const std::string & title);

		RESQML2_0_1_NS::FluidBoundaryFeature* createFluidBoundaryFeature(const std::string & guid, const std::string & title, const gsoap_resqml2_0_1::resqml20__FluidContact & fluidContact);

		RESQML2_0_1_NS::RockFluidUnitFeature* createRockFluidUnit(const std::string & guid, const std::string & title, gsoap_resqml2_0_1::resqml20__Phase phase, RESQML2_0_1_NS::FluidBoundaryFeature* fluidBoundaryTop, RESQML2_0_1_NS::FluidBoundaryFeature* fluidBoundaryBottom);

		//************ INTERPRETATION ********

		RESQML2_0_1_NS::GenericFeatureInterpretation* createGenericFeatureInterpretation(RESQML2_NS::AbstractFeature * feature, const std::string & guid, const std::string & title);

		RESQML2_0_1_NS::BoundaryFeatureInterpretation* createBoundaryFeatureInterpretation(RESQML2_0_1_NS::BoundaryFeature * feature, const std::string & guid, const std::string & title);

		RESQML2_0_1_NS::HorizonInterpretation* createHorizonInterpretation(RESQML2_0_1_NS::Horizon * horizon, const std::string & guid, const std::string & title);

		RESQML2_0_1_NS::GeobodyBoundaryInterpretation* createGeobodyBoundaryInterpretation(RESQML2_0_1_NS::GeneticBoundaryFeature * geobodyBoundary, const std::string & guid, const std::string & title);

		RESQML2_0_1_NS::FaultInterpretation* createFaultInterpretation(RESQML2_0_1_NS::TectonicBoundaryFeature * fault, const std::string & guid, const std::string & title);

		RESQML2_0_1_NS::WellboreInterpretation* createWellboreInterpretation(RESQML2_0_1_NS::WellboreFeature * wellbore, const std::string & guid, const std::string & title, bool isDrilled);

		RESQML2_0_1_NS::EarthModelInterpretation* createEarthModelInterpretation(RESQML2_0_1_NS::OrganizationFeature * orgFeat, const std::string & guid, const std::string & title);

		RESQML2_0_1_NS::StructuralOrganizationInterpretation* createStructuralOrganizationInterpretationInAge(RESQML2_0_1_NS::OrganizationFeature * orgFeat, const std::string & guid, const std::string & title);
		RESQML2_0_1_NS::StructuralOrganizationInterpretation* createStructuralOrganizationInterpretationInApparentDepth(RESQML2_0_1_NS::OrganizationFeature * orgFeat, const std::string & guid, const std::string & title);
		RESQML2_0_1_NS::StructuralOrganizationInterpretation* createStructuralOrganizationInterpretationInMeasuredDepth(RESQML2_0_1_NS::OrganizationFeature * orgFeat, const std::string & guid, const std::string & title);

		RESQML2_0_1_NS::RockFluidOrganizationInterpretation* createRockFluidOrganizationInterpretation(RESQML2_0_1_NS::OrganizationFeature * orgFeat, const std::string & guid, const std::string & title, RESQML2_0_1_NS::RockFluidUnitInterpretation * rockFluidUnitInterp);
		RESQML2_0_1_NS::RockFluidUnitInterpretation* createRockFluidUnitInterpretation(RESQML2_0_1_NS::RockFluidUnitFeature * rockFluidUnitFeature, const std::string & guid, const std::string & title);

		RESQML2_0_1_NS::GeobodyInterpretation* createGeobodyInterpretation(RESQML2_0_1_NS::GeobodyFeature * geobody, const std::string & guid, const std::string & title);

		RESQML2_0_1_NS::StratigraphicUnitInterpretation* createStratigraphicUnitInterpretation(RESQML2_0_1_NS::StratigraphicUnitFeature * stratiUnitFeature, const std::string & guid, const std::string & title);
		RESQML2_0_1_NS::StratigraphicColumn* createStratigraphicColumn(const std::string & guid, const std::string & title);
		RESQML2_0_1_NS::StratigraphicColumnRankInterpretation* createStratigraphicColumnRankInterpretationInAge(RESQML2_0_1_NS::OrganizationFeature * orgFeat, const std::string & guid, const std::string & title, const unsigned long & rank);
		RESQML2_0_1_NS::StratigraphicColumnRankInterpretation* createStratigraphicColumnRankInterpretationInApparentDepth(RESQML2_0_1_NS::OrganizationFeature * orgFeat, const std::string & guid, const std::string & title, const unsigned long & rank);
		RESQML2_0_1_NS::StratigraphicOccurrenceInterpretation* createStratigraphicOccurrenceInterpretationInAge(RESQML2_0_1_NS::OrganizationFeature * orgFeat, const std::string & guid, const std::string & title);
		RESQML2_0_1_NS::StratigraphicOccurrenceInterpretation* createStratigraphicOccurrenceInterpretationInApparentDepth(RESQML2_0_1_NS::OrganizationFeature * orgFeat, const std::string & guid, const std::string & title);

		//************ REPRESENTATION ********

		RESQML2_0_1_NS::TriangulatedSetRepresentation* createTriangulatedSetRepresentation(const std::string & guid, const std::string & title);
			
		RESQML2_0_1_NS::TriangulatedSetRepresentation* createTriangulatedSetRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp,
			const std::string & guid, const std::string & title);

		RESQML2_0_1_NS::PolylineSetRepresentation* createPolylineSetRepresentation(const std::string & guid, const std::string & title);

		RESQML2_0_1_NS::PolylineSetRepresentation* createPolylineSetRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp,
			const std::string & guid, const std::string & title);

		RESQML2_0_1_NS::PolylineSetRepresentation* createPolylineSetRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp,
			const std::string & guid, const std::string & title, gsoap_resqml2_0_1::resqml20__LineRole roleKind);

		RESQML2_0_1_NS::PointSetRepresentation* createPointSetRepresentation(const std::string & guid, const std::string & title);

		RESQML2_0_1_NS::PointSetRepresentation* createPointSetRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp,
			const std::string & guid, const std::string & title);

		RESQML2_0_1_NS::PlaneSetRepresentation* createPlaneSetRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp,
			const std::string & guid, const std::string & title);

		RESQML2_0_1_NS::PolylineRepresentation* createPolylineRepresentation(const std::string & guid, const std::string & title, bool isClosed = false);

		RESQML2_0_1_NS::PolylineRepresentation* createPolylineRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp,
			const std::string & guid, const std::string & title, bool isClosed = false);

		RESQML2_0_1_NS::PolylineRepresentation* createPolylineRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp,
			const std::string & guid, const std::string & title, const gsoap_resqml2_0_1::resqml20__LineRole & roleKind, bool isClosed = false);

		RESQML2_0_1_NS::Grid2dRepresentation* createGrid2dRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp,
			const std::string & guid, const std::string & title);

		RESQML2_0_1_NS::WellboreTrajectoryRepresentation* createWellboreTrajectoryRepresentation(RESQML2_0_1_NS::WellboreInterpretation * interp, const std::string & guid, const std::string & title, RESQML2_NS::MdDatum * mdInfo);
		RESQML2_0_1_NS::WellboreTrajectoryRepresentation* createWellboreTrajectoryRepresentation(RESQML2_0_1_NS::WellboreInterpretation * interp, const std::string & guid, const std::string & title, RESQML2_0_1_NS::DeviationSurveyRepresentation * deviationSurvey);

		RESQML2_0_1_NS::DeviationSurveyRepresentation* createDeviationSurveyRepresentation(RESQML2_0_1_NS::WellboreInterpretation * interp, const std::string & guid, const std::string & title, const bool & isFinal, RESQML2_NS::MdDatum * mdInfo);

		RESQML2_NS::WellboreFrameRepresentation* createWellboreFrameRepresentation(RESQML2_0_1_NS::WellboreInterpretation * interp, const std::string & guid, const std::string & title, RESQML2_0_1_NS::WellboreTrajectoryRepresentation * traj);

		RESQML2_0_1_NS::WellboreMarkerFrameRepresentation* createWellboreMarkerFrameRepresentation(RESQML2_0_1_NS::WellboreInterpretation * interp, const std::string & guid, const std::string & title, RESQML2_0_1_NS::WellboreTrajectoryRepresentation * traj);

		RESQML2_0_1_NS::BlockedWellboreRepresentation* createBlockedWellboreRepresentation(RESQML2_0_1_NS::WellboreInterpretation * interp,
			const std::string & guid, const std::string & title, RESQML2_0_1_NS::WellboreTrajectoryRepresentation * traj);

		RESQML2_NS::RepresentationSetRepresentation* createRepresentationSetRepresentation(
			RESQML2_0_1_NS::AbstractOrganizationInterpretation* interp,
			const std::string & guid,
			const std::string & title);

		RESQML2_NS::RepresentationSetRepresentation* createRepresentationSetRepresentation(
			const std::string & guid,
			const std::string & title);

		RESQML2_0_1_NS::NonSealedSurfaceFrameworkRepresentation* createNonSealedSurfaceFrameworkRepresentation(
			RESQML2_0_1_NS::StructuralOrganizationInterpretation* interp,
			const std::string & guid,
			const std::string & title);

		RESQML2_0_1_NS::SealedSurfaceFrameworkRepresentation* createSealedSurfaceFrameworkRepresentation(
			RESQML2_0_1_NS::StructuralOrganizationInterpretation* interp,
			const std::string & guid,
			const std::string & title);

		RESQML2_0_1_NS::SealedVolumeFrameworkRepresentation* createSealedVolumeFrameworkRepresentation(
			RESQML2_0_1_NS::StratigraphicColumnRankInterpretation* interp,
			const std::string & guid,
			const std::string & title,
			RESQML2_0_1_NS::SealedSurfaceFrameworkRepresentation* ssf);

		RESQML2_0_1_NS::AbstractIjkGridRepresentation* createPartialIjkGridRepresentation(const std::string & guid, const std::string & title);

		RESQML2_0_1_NS::AbstractIjkGridRepresentation* createPartialTruncatedIjkGridRepresentation(const std::string & guid, const std::string & title);

		RESQML2_0_1_NS::IjkGridExplicitRepresentation* createIjkGridExplicitRepresentation(const std::string & guid, const std::string & title,
			unsigned int iCount, unsigned int jCount, unsigned int kCount);

		RESQML2_0_1_NS::IjkGridExplicitRepresentation* createIjkGridExplicitRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp,
			const std::string & guid, const std::string & title,
			unsigned int iCount, unsigned int jCount, unsigned int kCount);

		RESQML2_0_1_NS::IjkGridParametricRepresentation* createIjkGridParametricRepresentation(const std::string & guid, const std::string & title,
			unsigned int iCount, unsigned int jCount, unsigned int kCount);

		RESQML2_0_1_NS::IjkGridParametricRepresentation* createIjkGridParametricRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp,
			const std::string & guid, const std::string & title,
			unsigned int iCount, unsigned int jCount, unsigned int kCount);

		RESQML2_0_1_NS::IjkGridLatticeRepresentation* createIjkGridLatticeRepresentation(const std::string & guid, const std::string & title,
			unsigned int iCount, unsigned int jCount, unsigned int kCount);

		RESQML2_0_1_NS::IjkGridLatticeRepresentation* createIjkGridLatticeRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp,
			const std::string & guid, const std::string & title,
			unsigned int iCount, unsigned int jCount, unsigned int kCount);

		RESQML2_0_1_NS::IjkGridNoGeometryRepresentation* createIjkGridNoGeometryRepresentation(
			const std::string & guid, const std::string & title,
			unsigned int iCount, unsigned int jCount, unsigned int kCount);

		RESQML2_0_1_NS::IjkGridNoGeometryRepresentation* createIjkGridNoGeometryRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp,
			const std::string & guid, const std::string & title,
			unsigned int iCount, unsigned int jCount, unsigned int kCount);

		RESQML2_0_1_NS::UnstructuredGridRepresentation* createUnstructuredGridRepresentation(const std::string & guid, const std::string & title,
			const ULONG64 & cellCount);

		RESQML2_NS::SubRepresentation* createSubRepresentation(
			const std::string & guid, const std::string & title);

		RESQML2_NS::SubRepresentation* createSubRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp,
			const std::string & guid, const std::string & title);

		RESQML2_NS::GridConnectionSetRepresentation* createGridConnectionSetRepresentation(const std::string & guid, const std::string & title);

		RESQML2_NS::GridConnectionSetRepresentation* createGridConnectionSetRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp,
			const std::string & guid, const std::string & title);

		//************* PROPERTIES ***********

		RESQML2_NS::TimeSeries* createTimeSeries(const std::string & guid, const std::string & title);

		RESQML2_0_1_NS::StringTableLookup* createStringTableLookup(const std::string & guid, const std::string & title);

		COMMON_NS::PropertyKind* createPropertyKind(const std::string & guid, const std::string & title,
			const std::string & namingSystem, const gsoap_resqml2_0_1::resqml20__ResqmlUom & uom, const gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind & parentEnergisticsPropertyKind);

		COMMON_NS::PropertyKind* createPropertyKind(const std::string & guid, const std::string & title,
			const std::string & namingSystem, const gsoap_resqml2_0_1::resqml20__ResqmlUom & uom, COMMON_NS::PropertyKind * parentPropType);

		COMMON_NS::PropertyKind* createPropertyKind(const std::string & guid, const std::string & title,
			const std::string & namingSystem, const std::string & nonStandardUom, const gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind & parentEnergisticsPropertyKind);

		COMMON_NS::PropertyKind* createPropertyKind(const std::string & guid, const std::string & title,
			const std::string & namingSystem, const std::string & nonStandardUom, COMMON_NS::PropertyKind * parentPropType);

		RESQML2_NS::PropertySet* createPropertySet(const std::string & guid, const std::string & title,
			bool hasMultipleRealizations, bool hasSinglePropertyKind, gsoap_resqml2_0_1::resqml20__TimeSetKind timeSetKind);

		RESQML2_0_1_NS::CommentProperty* createCommentProperty(RESQML2_NS::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			const unsigned int & dimension, const gsoap_resqml2_0_1::resqml20__IndexableElements & attachmentKind, const gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind & energisticsPropertyKind);

		RESQML2_0_1_NS::CommentProperty* createCommentProperty(RESQML2_NS::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			const unsigned int & dimension, const gsoap_resqml2_0_1::resqml20__IndexableElements & attachmentKind, COMMON_NS::PropertyKind * localPropType);

		RESQML2_0_1_NS::ContinuousProperty* createContinuousProperty(RESQML2_NS::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			const unsigned int & dimension, const gsoap_resqml2_0_1::resqml20__IndexableElements & attachmentKind, const gsoap_resqml2_0_1::resqml20__ResqmlUom & uom, const gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind & energisticsPropertyKind);

		RESQML2_0_1_NS::ContinuousProperty* createContinuousProperty(RESQML2_NS::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			const unsigned int & dimension, const gsoap_resqml2_0_1::resqml20__IndexableElements & attachmentKind, const gsoap_resqml2_0_1::resqml20__ResqmlUom & uom, COMMON_NS::PropertyKind * localPropType);

		RESQML2_0_1_NS::ContinuousProperty* createContinuousProperty(RESQML2_NS::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			const unsigned int & dimension, const gsoap_resqml2_0_1::resqml20__IndexableElements & attachmentKind, const std::string & nonStandardUom, const gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind & energisticsPropertyKind);

		RESQML2_0_1_NS::ContinuousProperty* createContinuousProperty(RESQML2_NS::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			const unsigned int & dimension, const gsoap_resqml2_0_1::resqml20__IndexableElements & attachmentKind, const std::string & nonStandardUom, COMMON_NS::PropertyKind * localPropType);

		RESQML2_0_1_NS::ContinuousPropertySeries* createContinuousPropertySeries(RESQML2_NS::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			const unsigned int & dimension, const gsoap_resqml2_0_1::resqml20__IndexableElements & attachmentKind, const gsoap_resqml2_0_1::resqml20__ResqmlUom & uom, const gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind & energisticsPropertyKind,
			RESQML2_NS::TimeSeries * ts, const bool & useInterval = false);

		RESQML2_0_1_NS::ContinuousPropertySeries* createContinuousPropertySeries(RESQML2_NS::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			const unsigned int & dimension, const gsoap_resqml2_0_1::resqml20__IndexableElements & attachmentKind, const gsoap_resqml2_0_1::resqml20__ResqmlUom & uom, COMMON_NS::PropertyKind * localPropType,
			RESQML2_NS::TimeSeries * ts, const bool & useInterval = false);

		RESQML2_0_1_NS::DiscreteProperty* createDiscreteProperty(RESQML2_NS::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			const unsigned int & dimension, const gsoap_resqml2_0_1::resqml20__IndexableElements & attachmentKind, const gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind & energisticsPropertyKind);

		RESQML2_0_1_NS::DiscreteProperty* createDiscreteProperty(RESQML2_NS::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			const unsigned int & dimension, const gsoap_resqml2_0_1::resqml20__IndexableElements & attachmentKind, COMMON_NS::PropertyKind * localPropType);

		RESQML2_0_1_NS::DiscretePropertySeries* createDiscretePropertySeries(RESQML2_NS::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			const unsigned int & dimension, const gsoap_resqml2_0_1::resqml20__IndexableElements & attachmentKind, const gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind & energisticsPropertyKind,
			RESQML2_NS::TimeSeries * ts, const bool & useInterval = false);

		RESQML2_0_1_NS::DiscretePropertySeries* createDiscretePropertySeries(RESQML2_NS::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			const unsigned int & dimension, const gsoap_resqml2_0_1::resqml20__IndexableElements & attachmentKind, COMMON_NS::PropertyKind * localPropType,
			RESQML2_NS::TimeSeries * ts, const bool & useInterval = false);

		RESQML2_0_1_NS::CategoricalProperty* createCategoricalProperty(RESQML2_NS::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			const unsigned int & dimension, const gsoap_resqml2_0_1::resqml20__IndexableElements & attachmentKind,
			RESQML2_0_1_NS::StringTableLookup* strLookup, const gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind & energisticsPropertyKind);

		RESQML2_0_1_NS::CategoricalProperty* createCategoricalProperty(RESQML2_NS::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			const unsigned int & dimension, const gsoap_resqml2_0_1::resqml20__IndexableElements & attachmentKind,
			RESQML2_0_1_NS::StringTableLookup* strLookup, COMMON_NS::PropertyKind * localPropType);

		RESQML2_0_1_NS::CategoricalPropertySeries* createCategoricalPropertySeries(RESQML2_NS::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			const unsigned int & dimension, const gsoap_resqml2_0_1::resqml20__IndexableElements & attachmentKind,
			RESQML2_0_1_NS::StringTableLookup* strLookup, const gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind & energisticsPropertyKind,
			RESQML2_NS::TimeSeries * ts, const bool & useInterval = false);

		RESQML2_0_1_NS::CategoricalPropertySeries* createCategoricalPropertySeries(RESQML2_NS::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			const unsigned int & dimension, const gsoap_resqml2_0_1::resqml20__IndexableElements & attachmentKind,
			RESQML2_0_1_NS::StringTableLookup* strLookup, COMMON_NS::PropertyKind * localPropType,
			RESQML2_NS::TimeSeries * ts, const bool & useInterval = false);

		//************* ACTIVITIES ***********

		RESQML2_NS::ActivityTemplate* createActivityTemplate(const std::string & guid, const std::string & title);

		RESQML2_NS::Activity* createActivity(RESQML2_NS::ActivityTemplate* activityTemplate, const std::string & guid, const std::string & title);

		//*************** WITSML *************

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

		WITSML2_0_NS::Channel* createChannel(COMMON_NS::PropertyKind * propertyKind,
			const std::string & guid, const std::string & title,
			const std::string & mnemonic, gsoap_eml2_1::eml21__UnitOfMeasure uom, gsoap_eml2_1::witsml20__EtpDataType dataType, gsoap_eml2_1::witsml20__ChannelStatus growingStatus,
			const std::string & timeDepth, const std::string & loggingCompanyName);

		//************************************
		//***** STANDARD PROP KIND ***********
		//************************************
		
		RESQML2_0_1_NS::PropertyKindMapper* getPropertyKindMapper() const;

		//************************************
		//************* WARNINGS *************
		//************************************

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
		%template(createPartialWellboreFrameRepresentation) createPartial<RESQML2_0_1_NS::WellboreFrameRepresentation>;
		%template(createPartialWellboreMarkerFrameRepresentation) createPartial<RESQML2_0_1_NS::WellboreMarkerFrameRepresentation>;
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
		%template(createPartialDiscretePropertySeries) createPartial<RESQML2_0_1_NS::DiscretePropertySeries>;
		%template(createPartialCategoricalProperty) createPartial<RESQML2_0_1_NS::CategoricalProperty>;
		%template(createPartialCategoricalPropertySeries) createPartial<RESQML2_0_1_NS::CategoricalPropertySeries>;
		%template(createPartialCommentProperty) createPartial<RESQML2_0_1_NS::CommentProperty>;
		%template(createPartialContinuousProperty) createPartial<RESQML2_0_1_NS::ContinuousProperty>;
		%template(createPartialContinuousPropertySeries) createPartial<RESQML2_0_1_NS::ContinuousPropertySeries>;

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

