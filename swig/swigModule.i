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
	%array_functions(unsigned long long, ULongLongArray);
	%array_functions(unsigned long, ULongArray);
	%array_functions(unsigned int, UIntArray);
	%array_functions(int, IntArray);
	%array_functions(long long, LongLongArray);
	%array_functions(long, LongArray);
	%array_functions(float, FloatArray);
	%array_functions(double, DoubleArray);
	%array_functions(short, ShortArray);
	%array_functions(unsigned short, UShortArray);
	%array_functions(char, CharArray);
	%array_functions(unsigned char, UCharArray);
	%array_functions(bool, BoolArray);
#else // Use GC.KeepAlive on these arrays to ensure no premature garbage collection in C#
	%array_class(unsigned long long, ULongLongArray);
	%array_class(unsigned long, ULongArray);
	%array_class(unsigned int, UIntArray);
	%array_class(int, IntArray);
	%array_class(long long, LongLongArray);
	%array_class(long, LongArray);
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
	%nspace COMMON_NS::EpcDocument;
	%nspace COMMON_NS::AbstractObject;
	%nspace COMMON_NS::EpcExternalPartReference;
	%nspace COMMON_NS::AbstractHdfProxy;
	%nspace COMMON_NS::HdfProxy;
#endif

namespace RESQML2_NS
{
	class Activity;
}

namespace COMMON_NS
{
	%nodefaultctor; // Disable creation of default constructors
	
	class AbstractObject
	{
	public:
		COMMON_NS::EpcDocument* getEpcDocument() const;
	
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
		std::string getVersionString() const;
		
		void setMetadata(const std::string & title, const std::string & editor, const time_t & creation, const std::string & originator,
				const std::string & description, const time_t & lastUpdate, const std::string & format, const std::string & descriptiveKeywords);
		void setTitle(const std::string & title);
		void setEditor(const std::string & editor);
		void setCreation(const time_t & creation);
		void setOriginator(const std::string & originator);
		void setDescription(const std::string & description);
		void setLastUpdate(const time_t & lastUpdate);
		void setFormat(const std::string & format);
		void setDescriptiveKeywords(const std::string & descriptiveKeywords);
		void setVersionString(const std::string & versionString);
				
		std::string getXmlTag() const;
		
		void addAlias(const std::string & authority, const std::string & title);
		unsigned int getAliasCount() const;
		std::string getAliasAuthorityAtIndex(const unsigned int & index) const;
		std::string getAliasTitleAtIndex(const unsigned int & index) const;
		
		void pushBackExtraMetadata(const std::string & key, const std::string & value);
		
		unsigned int getExtraMetadataCount() const;
		std::string getExtraMetadataKeyAtIndex(const unsigned int & index) const;
		std::string getExtraMetadataStringValueAtIndex(const unsigned int & index) const;

		unsigned int getActivityCount() const;
		RESQML2_NS::Activity* getActivity (const unsigned int & index) const;
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
	};

	class HdfProxy : public AbstractHdfProxy
	{
	public:
		void setCompressionLevel(const unsigned int & newCompressionLevel);
	};
	
}

%include "swigResqml2Include.i"
%include "swigResqml2_0_1Include.i"
%include "swigWitsml1_4_1_1Include.i"

%template(StringVector) std::vector< std::string >;

namespace RESQML2_NS
{
	class Activity;
}

namespace COMMON_NS
{
	%typemap(javafinalize) EpcDocument %{
	%}
	class EpcDocument
	{
	public:
	
		enum openingMode { READ_ONLY = 0, READ_WRITE = 1, OVERWRITE = 2 };
	
		EpcDocument(const std::string & fileName, const openingMode & hdf5PermissionAccess = READ_WRITE);
		EpcDocument(const std::string & fileName, const std::string & propertyKindMappingFilesDirectory, const openingMode & hdf5PermissionAccess = READ_WRITE);
		
		void setFilePath(const std::string & filePath);

		virtual void serialize(bool useZip64 = false);
		virtual std::string deserialize();
		void close();
		std::string getStorageDirectory() const;
		std::string getName() const;
		
		RESQML2_0_1_NS::PropertyKindMapper* getPropertyKindMapper() const;
		
		std::string getEnergisticsPropertyKindName(const gsoap_resqml2_0_1::resqml2__ResqmlPropertyKind & energisticsPropertyKind) const;
		gsoap_resqml2_0_1::resqml2__ResqmlPropertyKind getEnergisticsPropertyKind(const std::string & energisticsPropertyKindName) const;
		std::string getEnergisticsUnitOfMeasureName(const gsoap_resqml2_0_1::resqml2__ResqmlUom & energisticsUom) const;
		gsoap_resqml2_0_1::resqml2__ResqmlUom getEnergisticsUnitOfMeasure(const std::string & energisticsUomName) const;
		std::string getFacet(const gsoap_resqml2_0_1::resqml2__Facet & facet) const;
		gsoap_resqml2_0_1::resqml2__Facet getFacet(const std::string & facet) const;
		std::string getWitsmlLengthUom(const gsoap_witsml1_4_1_1::witsml1__LengthUom & witsmlUom) const;
		std::string getWitsmlWellVerticalCoordinateUom(const gsoap_witsml1_4_1_1::witsml1__WellVerticalCoordinateUom & witsmlUom) const;
		std::string getWitsmlMeasuredDepthUom(const gsoap_witsml1_4_1_1::witsml1__MeasuredDepthUom & witsmlUom) const;

		std::string getWitsmlPlaneAngleUom(const gsoap_witsml1_4_1_1::witsml1__PlaneAngleUom & witsmlUom) const;
		
		const std::vector<RESQML2_0_1_NS::LocalDepth3dCrs*> & getLocalDepth3dCrsSet() const;
		const std::vector<RESQML2_0_1_NS::LocalTime3dCrs*> & getLocalTime3dCrsSet() const;
		
		const std::vector<RESQML2_0_1_NS::StratigraphicColumn*> & getStratigraphicColumnSet() const;
		
		const std::vector<RESQML2_0_1_NS::TectonicBoundaryFeature*> & getFaultSet() const;
		const std::vector<RESQML2_0_1_NS::TectonicBoundaryFeature*> & getFractureSet() const {return fractureSet;}
		const std::vector<RESQML2_0_1_NS::FrontierFeature*> & getFrontierSet() const;
		std::vector<RESQML2_0_1_NS::PolylineSetRepresentation*> getFaultPolylineSetRepSet() const;
		std::vector<RESQML2_0_1_NS::PolylineSetRepresentation*> getFracturePolylineSetRepSet() const;
		std::vector<RESQML2_0_1_NS::PolylineSetRepresentation*> getFrontierPolylineSetRepSet() const;
		std::vector<RESQML2_0_1_NS::TriangulatedSetRepresentation*> getFaultTriangulatedSetRepSet() const;
		std::vector<RESQML2_0_1_NS::TriangulatedSetRepresentation*> getFractureTriangulatedSetRepSet() const;
		
		std::vector<RESQML2_0_1_NS::Horizon*> getHorizonSet() const;
		unsigned int getGeobodyBoundaryCount() const;
		RESQML2_0_1_NS::GeneticBoundaryFeature* getGeobodyBoundary(unsigned int index) const;
		const std::vector<RESQML2_0_1_NS::GeobodyFeature*> & getGeobodySet() const;
		std::vector<RESQML2_0_1_NS::Grid2dSetRepresentation*> getHorizonGrid2dSetRepSet() const;
		std::vector<RESQML2_0_1_NS::Grid2dRepresentation*> getHorizonGrid2dRepSet() const;
		std::vector<RESQML2_0_1_NS::PolylineRepresentation*> getHorizonPolylineRepSet() const;
		std::vector<RESQML2_0_1_NS::PolylineSetRepresentation*> getHorizonPolylineSetRepSet() const;
		std::vector<RESQML2_0_1_NS::TriangulatedSetRepresentation*> getHorizonTriangulatedSetRepSet() const;
		const std::vector<RESQML2_0_1_NS::TriangulatedSetRepresentation*> & getAllTriangulatedSetRepSet() const;
		std::vector<RESQML2_0_1_NS::TriangulatedSetRepresentation*> getUnclassifiedTriangulatedSetRepSet() const;
		
		const std::vector<RESQML2_0_1_NS::SeismicLineFeature*> & getSeismicLineSet() const;
		
		const std::vector<RESQML2_0_1_NS::WellboreFeature*> & getWellboreSet() const;
		std::vector<RESQML2_0_1_NS::WellboreTrajectoryRepresentation*> getWellboreTrajectoryRepresentationSet() const;
		std::vector<RESQML2_0_1_NS::DeviationSurveyRepresentation*> getDeviationSurveyRepresentationSet() const;
		
		unsigned int getRepresentationSetRepresentationCount() const;
		RESQML2_NS::RepresentationSetRepresentation* getRepresentationSetRepresentation(const unsigned int & index) const;
		
		unsigned int getHdfProxyCount() const;
		COMMON_NS::AbstractHdfProxy* getHdfProxy(const unsigned int & index) const;
		
		unsigned int getIjkGridRepresentationCount() const;
		RESQML2_0_1_NS::AbstractIjkGridRepresentation* getIjkGridRepresentation(const unsigned int & i) const;
		std::vector<RESQML2_0_1_NS::IjkGridExplicitRepresentation*> getIjkGridExplicitRepresentationSet() const;
		std::vector<RESQML2_0_1_NS::IjkGridParametricRepresentation*> getIjkGridParametricRepresentationSet() const;

		std::vector<RESQML2_0_1_NS::PolylineRepresentation*> getSeismicLinePolylineRepSet() const;
		std::vector<RESQML2_0_1_NS::IjkGridLatticeRepresentation*> getIjkSeismicCubeGridRepresentationSet() const;
		
		const std::vector<RESQML2_0_1_NS::UnstructuredGridRepresentation*> & getUnstructuredGridRepresentationSet() const;
		
		unsigned int getSubRepresentationCount() const;
		RESQML2_NS::SubRepresentation* getSubRepresentation(const unsigned int & index) const;
		
		unsigned int getPointSetRepresentationCount() const;
		RESQML2_0_1_NS::PointSetRepresentation* getPointSetRepresentation(const unsigned int & index) const;
		
		void setExtendedCoreProperty(const std::string & key, const std::string & value);
		std::string getExtendedCoreProperty(const std::string & key);

		COMMON_NS::AbstractObject* getResqmlAbstractObjectByUuid(const std::string & uuid) const;
		WITSML1_4_1_1_NS::AbstractObject* getWitsmlAbstractObjectByUuid(const std::string & uuid) const;

		//************************************
		//************ HDF *******************
		//************************************

		virtual COMMON_NS::AbstractHdfProxy* createHdfProxy(const std::string & guid, const std::string & title, const std::string & packageDirAbsolutePath, const std::string & externalFilePath);

		//************************************
		//************ CRS *******************
		//************************************

		RESQML2_0_1_NS::LocalDepth3dCrs* createLocalDepth3dCrs(const std::string & guid, const std::string & title,
			const double & originOrdinal1, const double & originOrdinal2, const double & originOrdinal3,
			const double & arealRotation,
			const gsoap_resqml2_0_1::eml20__LengthUom & projectedUom, const unsigned long & projectedEpsgCode,
			const gsoap_resqml2_0_1::eml20__LengthUom & verticalUom, const unsigned int & verticalEpsgCode, const bool & isUpOriented);

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
			
		RESQML2_0_1_NS::MdDatum* createMdDatum(const std::string & guid, const std::string & title,
			RESQML2_NS::AbstractLocal3dCrs * locCrs, const gsoap_resqml2_0_1::resqml2__MdReference & originKind,
			const double & referenceLocationOrdinal1, const double & referenceLocationOrdinal2, const double & referenceLocationOrdinal3);

		//************************************
		//************ FEATURE ***************
		//************************************

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
			
		RESQML2_0_1_NS::OrganizationFeature* createStructuralModel(const std::string & guid, const std::string & title);
		
		RESQML2_0_1_NS::StratigraphicUnitFeature* createStratigraphicUnit(const std::string & guid, const std::string & title);
		
		RESQML2_0_1_NS::OrganizationFeature* createStratigraphicModel(const std::string & guid, const std::string & title);

        RESQML2_0_1_NS::OrganizationFeature* createEarthModel(const std::string & guid, const std::string & title);
		
		RESQML2_0_1_NS::FluidBoundaryFeature* createFluidBoundaryFeature(const std::string & guid, const std::string & title, const gsoap_resqml2_0_1::resqml2__FluidContact & fluidContact);
		
		//************************************
		//************ INTERPRETATION ********
		//************************************

		RESQML2_0_1_NS::GenericFeatureInterpretation* createGenericFeatureInterpretation(RESQML2_NS::AbstractFeature * feature, const std::string & guid, const std::string & title);
		
		RESQML2_0_1_NS::BoundaryFeatureInterpretation* createBoundaryFeatureInterpretation(RESQML2_0_1_NS::BoundaryFeature * feature, const std::string & guid, const std::string & title);

		RESQML2_0_1_NS::HorizonInterpretation* createHorizonInterpretation(RESQML2_0_1_NS::Horizon * horizon, const std::string & guid, const std::string & title);

		RESQML2_0_1_NS::GeobodyBoundaryInterpretation* createGeobodyBoundaryInterpretation(RESQML2_0_1_NS::GeneticBoundaryFeature * geobodyBoundary, const std::string & guid, const std::string & title);

		RESQML2_0_1_NS::FaultInterpretation* createFaultInterpretation(RESQML2_0_1_NS::TectonicBoundaryFeature* fault, const std::string & guid, const std::string & title);
		
		RESQML2_0_1_NS::WellboreInterpretation* createWellboreInterpretation(RESQML2_0_1_NS::WellboreFeature * wellbore, const std::string & guid, const std::string & title, bool isDrilled);
		
		RESQML2_0_1_NS::EarthModelInterpretation* createEarthModelInterpretation(RESQML2_0_1_NS::OrganizationFeature * orgFeat, const std::string & guid, const std::string & title);

		RESQML2_0_1_NS::StructuralOrganizationInterpretation* createStructuralOrganizationInterpretationInAge(RESQML2_0_1_NS::OrganizationFeature * orgFeat, const std::string & guid, const std::string & title);	
		RESQML2_0_1_NS::StructuralOrganizationInterpretation* createStructuralOrganizationInterpretationInApparentDepth(RESQML2_0_1_NS::OrganizationFeature * orgFeat, const std::string & guid, const std::string & title);		
		RESQML2_0_1_NS::StructuralOrganizationInterpretation* createStructuralOrganizationInterpretationInMeasuredDepth(RESQML2_0_1_NS::OrganizationFeature * orgFeat, const std::string & guid, const std::string & title);

		RESQML2_0_1_NS::GeobodyInterpretation* createGeobodyInterpretation(RESQML2_0_1_NS::GeobodyFeature * geobody, const std::string & guid, const std::string & title);

		RESQML2_0_1_NS::StratigraphicUnitInterpretation* createStratigraphicUnitInterpretation(RESQML2_0_1_NS::StratigraphicUnitFeature * stratiUnitFeature, const std::string & guid, const std::string & title);
		RESQML2_0_1_NS::StratigraphicColumn* createStratigraphicColumn(const std::string & guid, const std::string & title);
		RESQML2_0_1_NS::StratigraphicColumnRankInterpretation* createStratigraphicColumnRankInterpretationInAge(RESQML2_0_1_NS::OrganizationFeature * orgFeat, const std::string & guid, const std::string & title, const unsigned long & rank);
		RESQML2_0_1_NS::StratigraphicColumnRankInterpretation* createStratigraphicColumnRankInterpretationInApparentDepth(RESQML2_0_1_NS::OrganizationFeature * orgFeat, const std::string & guid, const std::string & title, const unsigned long & rank);
		RESQML2_0_1_NS::StratigraphicOccurrenceInterpretation* createStratigraphicOccurrenceInterpretationInAge(RESQML2_0_1_NS::OrganizationFeature * orgFeat, const std::string & guid, const std::string & title);
		RESQML2_0_1_NS::StratigraphicOccurrenceInterpretation* createStratigraphicOccurrenceInterpretationInApparentDepth(RESQML2_0_1_NS::OrganizationFeature * orgFeat, const std::string & guid, const std::string & title);

		//************************************
		//************ REPRESENTATION ********
		//************************************

		RESQML2_0_1_NS::TriangulatedSetRepresentation* createTriangulatedSetRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp, RESQML2_NS::AbstractLocal3dCrs * crs, const std::string & guid, const std::string & title);

		RESQML2_0_1_NS::PolylineSetRepresentation* createPolylineSetRepresentation(RESQML2_NS::AbstractLocal3dCrs * crs, const std::string & guid, const std::string & title);
		
		RESQML2_0_1_NS::PolylineSetRepresentation* createPolylineSetRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp, RESQML2_NS::AbstractLocal3dCrs * crs, const std::string & guid, const std::string & title);

		RESQML2_0_1_NS::PolylineSetRepresentation* createPolylineSetRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp, RESQML2_NS::AbstractLocal3dCrs * crs, const std::string & guid, const std::string & title, const gsoap_resqml2_0_1::resqml2__LineRole & roleKind);
			
		RESQML2_0_1_NS::PointSetRepresentation* createPointSetRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp, RESQML2_NS::AbstractLocal3dCrs * crs,	const std::string & guid, const std::string & title);

		RESQML2_0_1_NS::PlaneSetRepresentation* createPlaneSetRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp, RESQML2_NS::AbstractLocal3dCrs * crs, const std::string & guid, const std::string & title);
		
		RESQML2_0_1_NS::PolylineRepresentation* createPolylineRepresentation(RESQML2_NS::AbstractLocal3dCrs * crs, const std::string & guid, const std::string & title, bool isClosed = false);
		
		RESQML2_0_1_NS::PolylineRepresentation* createPolylineRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp, RESQML2_NS::AbstractLocal3dCrs * crs, const std::string & guid, const std::string & title, bool isClosed = false);

		RESQML2_0_1_NS::PolylineRepresentation* createPolylineRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp, RESQML2_NS::AbstractLocal3dCrs * crs, const std::string & guid, const std::string & title, const gsoap_resqml2_0_1::resqml2__LineRole & roleKind, bool isClosed = false);

		RESQML2_0_1_NS::Grid2dRepresentation* createGrid2dRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp, RESQML2_NS::AbstractLocal3dCrs * crs, const std::string & guid, const std::string & title);

		RESQML2_0_1_NS::WellboreTrajectoryRepresentation* createWellboreTrajectoryRepresentation(RESQML2_0_1_NS::WellboreInterpretation* interp, const std::string & guid, const std::string & title, RESQML2_0_1_NS::MdDatum * mdInfo);	
		RESQML2_0_1_NS::WellboreTrajectoryRepresentation* createWellboreTrajectoryRepresentation(RESQML2_0_1_NS::WellboreInterpretation* interp, const std::string & guid, const std::string & title, RESQML2_0_1_NS::DeviationSurveyRepresentation* deviationSurvey);
		
		RESQML2_0_1_NS::DeviationSurveyRepresentation* createDeviationSurveyRepresentation(RESQML2_0_1_NS::WellboreInterpretation* interp, const std::string & guid, const std::string & title, const bool & isFinal, RESQML2_NS::MdDatum * mdInfo);
		
		RESQML2_0_1_NS::WellboreFrameRepresentation* createWellboreFrameRepresentation(RESQML2_0_1_NS::WellboreInterpretation* interp, const std::string & guid, const std::string & title, RESQML2_0_1_NS::WellboreTrajectoryRepresentation * traj);

		RESQML2_0_1_NS::WellboreMarkerFrameRepresentation* createWellboreMarkerFrameRepresentation(RESQML2_0_1_NS::WellboreInterpretation* interp, const std::string & guid, const std::string & title, RESQML2_0_1_NS::WellboreTrajectoryRepresentation * traj);
			
		RESQML2_NS::RepresentationSetRepresentation* createRepresentationSetRepresentation(
                RESQML2_0_1_NS::AbstractOrganizationInterpretation* interp,
                const std::string & guid,
				const std::string & title);

		RESQML2_NS::RepresentationSetRepresentation* createRepresentationSetRepresentation(
			const std::string & guid,
			const std::string & title);
			
		RESQML2_NS::RepresentationSetRepresentation* createPartialRepresentationSetRepresentation(const std::string & guid, const std::string & title);
                
        RESQML2_0_1_NS::NonSealedSurfaceFrameworkRepresentation* createNonSealedSurfaceFrameworkRepresentation(
                RESQML2_0_1_NS::StructuralOrganizationInterpretation* interp, 
                const std::string & guid, 
                const std::string & title,
                const bool & isSealed);

		RESQML2_0_1_NS::SealedSurfaceFrameworkRepresentation* createSealedSurfaceFrameworkRepresentation(
		        RESQML2_0_1_NS::StructuralOrganizationInterpretation* interp,
		        const std::string & guid,
		        const std::string & title);
				
		RESQML2_0_1_NS::AbstractIjkGridRepresentation* createPartialIjkGridRepresentation(const std::string & guid, const std::string & title);
    	        
		RESQML2_0_1_NS::IjkGridExplicitRepresentation* createIjkGridExplicitRepresentation(RESQML2_NS::AbstractLocal3dCrs * crs,
			const std::string & guid, const std::string & title,
			const unsigned int & iCount, const unsigned int & jCount, const unsigned int & kCount);

		RESQML2_0_1_NS::IjkGridExplicitRepresentation* createIjkGridExplicitRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp, RESQML2_NS::AbstractLocal3dCrs * crs,
			const std::string & guid, const std::string & title,
			const unsigned int & iCount, const unsigned int & jCount, const unsigned int & kCount);

		RESQML2_0_1_NS::IjkGridParametricRepresentation* createIjkGridParametricRepresentation(RESQML2_NS::AbstractLocal3dCrs * crs,
			const std::string & guid, const std::string & title,
			const unsigned int & iCount, const unsigned int & jCount, const unsigned int & kCount);

		RESQML2_0_1_NS::IjkGridParametricRepresentation* createIjkGridParametricRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp, RESQML2_NS::AbstractLocal3dCrs * crs,
			const std::string & guid, const std::string & title,
			const unsigned int & iCount, const unsigned int & jCount, const unsigned int & kCount);

		RESQML2_0_1_NS::IjkGridLatticeRepresentation* createIjkGridLatticeRepresentation(RESQML2_NS::AbstractLocal3dCrs * crs,
			const std::string & guid, const std::string & title,
			const unsigned int & iCount, const unsigned int & jCount, const unsigned int & kCount);

		RESQML2_0_1_NS::IjkGridLatticeRepresentation* createIjkGridLatticeRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp, RESQML2_NS::AbstractLocal3dCrs * crs,
			const std::string & guid, const std::string & title,
			const unsigned int & iCount, const unsigned int & jCount, const unsigned int & kCount);

		RESQML2_0_1_NS::IjkGridNoGeometryRepresentation* createIjkGridNoGeometryRepresentation(
			const std::string & guid, const std::string & title,
			const unsigned int & iCount, const unsigned int & jCount, const unsigned int & kCount);

		RESQML2_0_1_NS::IjkGridNoGeometryRepresentation* createIjkGridNoGeometryRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp,
			const std::string & guid, const std::string & title,
			const unsigned int & iCount, const unsigned int & jCount, const unsigned int & kCount);
			
		RESQML2_0_1_NS::UnstructuredGridRepresentation* createPartialUnstructuredGridRepresentation(const std::string & guid, const std::string & title);

		RESQML2_0_1_NS::UnstructuredGridRepresentation* createUnstructuredGridRepresentation(RESQML2_NS::AbstractLocal3dCrs * crs,
			const std::string & guid, const std::string & title,
			const ULONG64 & cellCount);

		RESQML2_NS::SubRepresentation* createPartialSubRepresentation(const std::string & guid, const std::string & title);
			
		RESQML2_NS::SubRepresentation* createSubRepresentation(
                const std::string & guid, const std::string & title);
			
		RESQML2_NS::SubRepresentation* createSubRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp,
			const std::string & guid, const std::string & title);
		
		RESQML2_NS::GridConnectionSetRepresentation* createGridConnectionSetRepresentation(const std::string & guid, const std::string & title);

		RESQML2_NS::GridConnectionSetRepresentation* createGridConnectionSetRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp,
                const std::string & guid, const std::string & title);

		//************************************
		//************* PROPERTIES ***********
		//************************************

		RESQML2_NS::TimeSeries* createTimeSeries(const std::string & guid, const std::string & title);

		RESQML2_NS::TimeSeries* createPartialTimeSeries(const std::string & guid, const std::string & title);
		
		RESQML2_0_1_NS::StringTableLookup* createStringTableLookup(const std::string & guid, const std::string & title);
		
		RESQML2_NS::PropertyKind* createPropertyKind(const std::string & guid, const std::string & title,
			const std::string & namingSystem, const gsoap_resqml2_0_1::resqml2__ResqmlUom & uom, const gsoap_resqml2_0_1::resqml2__ResqmlPropertyKind & parentEnergisticsPropertyKind);

		RESQML2_NS::PropertyKind* createPropertyKind(const std::string & guid, const std::string & title,
			const std::string & namingSystem, const gsoap_resqml2_0_1::resqml2__ResqmlUom & uom, RESQML2_NS::PropertyKind * parentPropType);

		RESQML2_NS::PropertyKind* createPropertyKind(const std::string & guid, const std::string & title,
			const std::string & namingSystem, const std::string & nonStandardUom, const gsoap_resqml2_0_1::resqml2__ResqmlPropertyKind & parentEnergisticsPropertyKind);

		RESQML2_NS::PropertyKind* createPropertyKind(const std::string & guid, const std::string & title,
			const std::string & namingSystem, const std::string & nonStandardUom, RESQML2_NS::PropertyKind * parentPropType);

		RESQML2_NS::PropertyKind* createPartialPropertyKind(const std::string & guid, const std::string & title);

		RESQML2_0_1_NS::CommentProperty* createCommentProperty(RESQML2_NS::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			const unsigned int & dimension, const gsoap_resqml2_0_1::resqml2__IndexableElements & attachmentKind, const gsoap_resqml2_0_1::resqml2__ResqmlPropertyKind & energisticsPropertyKind);

		RESQML2_0_1_NS::CommentProperty* createCommentProperty(RESQML2_NS::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			const unsigned int & dimension, const gsoap_resqml2_0_1::resqml2__IndexableElements & attachmentKind, RESQML2_NS::PropertyKind * localPropType);
	
		RESQML2_0_1_NS::ContinuousProperty* createContinuousProperty(RESQML2_NS::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			const unsigned int & dimension, const gsoap_resqml2_0_1::resqml2__IndexableElements & attachmentKind, const gsoap_resqml2_0_1::resqml2__ResqmlUom & uom, const gsoap_resqml2_0_1::resqml2__ResqmlPropertyKind & energisticsPropertyKind);

		RESQML2_0_1_NS::ContinuousProperty* createContinuousProperty(RESQML2_NS::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			const unsigned int & dimension, const gsoap_resqml2_0_1::resqml2__IndexableElements & attachmentKind, const gsoap_resqml2_0_1::resqml2__ResqmlUom & uom, RESQML2_NS::PropertyKind * localPropType);

		RESQML2_0_1_NS::ContinuousProperty* createContinuousProperty(RESQML2_NS::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			const unsigned int & dimension, const gsoap_resqml2_0_1::resqml2__IndexableElements & attachmentKind, const std::string & nonStandardUom, const gsoap_resqml2_0_1::resqml2__ResqmlPropertyKind & energisticsPropertyKind);

		RESQML2_0_1_NS::ContinuousProperty* createContinuousProperty(RESQML2_NS::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			const unsigned int & dimension, const gsoap_resqml2_0_1::resqml2__IndexableElements & attachmentKind, const std::string & nonStandardUom, RESQML2_NS::PropertyKind * localPropType);

		RESQML2_0_1_NS::ContinuousPropertySeries* createContinuousPropertySeries(RESQML2_NS::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			const unsigned int & dimension, const gsoap_resqml2_0_1::resqml2__IndexableElements & attachmentKind, const gsoap_resqml2_0_1::resqml2__ResqmlUom & uom, const gsoap_resqml2_0_1::resqml2__ResqmlPropertyKind & energisticsPropertyKind,
			RESQML2_NS::TimeSeries * ts, const bool & useInterval = false);

		RESQML2_0_1_NS::ContinuousPropertySeries* createContinuousPropertySeries(RESQML2_NS::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			const unsigned int & dimension, const gsoap_resqml2_0_1::resqml2__IndexableElements & attachmentKind, const gsoap_resqml2_0_1::resqml2__ResqmlUom & uom, RESQML2_NS::PropertyKind * localPropType,
			RESQML2_NS::TimeSeries * ts, const bool & useInterval = false);
	
		RESQML2_0_1_NS::DiscreteProperty* createDiscreteProperty(RESQML2_NS::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			const unsigned int & dimension, const gsoap_resqml2_0_1::resqml2__IndexableElements & attachmentKind, const gsoap_resqml2_0_1::resqml2__ResqmlPropertyKind & energisticsPropertyKind);

		RESQML2_0_1_NS::DiscreteProperty* createDiscreteProperty(RESQML2_NS::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			const unsigned int & dimension, const gsoap_resqml2_0_1::resqml2__IndexableElements & attachmentKind, RESQML2_NS::PropertyKind * localPropType);
	
		RESQML2_0_1_NS::DiscretePropertySeries* createDiscretePropertySeries(RESQML2_NS::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			const unsigned int & dimension, const gsoap_resqml2_0_1::resqml2__IndexableElements & attachmentKind, const gsoap_resqml2_0_1::resqml2__ResqmlPropertyKind & energisticsPropertyKind,
			RESQML2_NS::TimeSeries * ts, const bool & useInterval = false);

		RESQML2_0_1_NS::DiscretePropertySeries* createDiscretePropertySeries(RESQML2_NS::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			const unsigned int & dimension, const gsoap_resqml2_0_1::resqml2__IndexableElements & attachmentKind, RESQML2_NS::PropertyKind * localPropType,
			RESQML2_NS::TimeSeries * ts, const bool & useInterval = false);

		RESQML2_0_1_NS::CategoricalProperty* createCategoricalProperty(RESQML2_NS::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			const unsigned int & dimension, const gsoap_resqml2_0_1::resqml2__IndexableElements & attachmentKind,
			RESQML2_0_1_NS::StringTableLookup* strLookup, const gsoap_resqml2_0_1::resqml2__ResqmlPropertyKind & energisticsPropertyKind);
	
		RESQML2_0_1_NS::CategoricalProperty* createCategoricalProperty(RESQML2_NS::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			const unsigned int & dimension, const gsoap_resqml2_0_1::resqml2__IndexableElements & attachmentKind,
			RESQML2_0_1_NS::StringTableLookup* strLookup, RESQML2_NS::PropertyKind * localPropType);

		RESQML2_0_1_NS::CategoricalPropertySeries* createCategoricalPropertySeries(RESQML2_NS::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			const unsigned int & dimension, const gsoap_resqml2_0_1::resqml2__IndexableElements & attachmentKind,
			RESQML2_0_1_NS::StringTableLookup* strLookup, const gsoap_resqml2_0_1::resqml2__ResqmlPropertyKind & energisticsPropertyKind,
			RESQML2_NS::TimeSeries * ts, const bool & useInterval = false);

		RESQML2_0_1_NS::CategoricalPropertySeries* createCategoricalPropertySeries(RESQML2_NS::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			const unsigned int & dimension, const gsoap_resqml2_0_1::resqml2__IndexableElements & attachmentKind,
			RESQML2_0_1_NS::StringTableLookup* strLookup, RESQML2_NS::PropertyKind * localPropType,
			RESQML2_NS::TimeSeries * ts, const bool & useInterval = false);

		//************************************
		//************* ACTIVITIES ***********
		//************************************

		RESQML2_NS::ActivityTemplate* createActivityTemplate(const std::string & guid, const std::string & title);
		
		RESQML2_NS::Activity* createActivity(RESQML2_NS::ActivityTemplate* activityTemplate, const std::string & guid, const std::string & title);
			

		//************************************
		//************ WITSML ****************
		//************************************
		
		std::vector<WITSML1_4_1_1_NS::Trajectory*> getWitsmlTrajectorySet() const;
		
		WITSML1_4_1_1_NS::Well* createWell(
			const std::string & guid,
			const std::string & title,
			const std::string & timeZone);

		WITSML1_4_1_1_NS::Well* createWell(
			const std::string & guid,
			const std::string & title,
			const std::string & timeZone,
			const std::string & operator_,
			gsoap_witsml1_4_1_1::witsml1__WellStatus statusWell,
			gsoap_witsml1_4_1_1::witsml1__WellPurpose purposeWell,
			gsoap_witsml1_4_1_1::witsml1__WellFluid fluidWell,
			gsoap_witsml1_4_1_1::witsml1__WellDirection directionWell,
			const time_t & dTimSpud,
			const std::string & sourceName,
			const time_t & dTimCreation,
			const time_t & dTimLastChange,
			const std::string & comments
		);

		WITSML1_4_1_1_NS::CoordinateReferenceSystem* createCoordinateReferenceSystem(
			const std::string & guid,
			const std::string & title,
			const std::string & namingSystem,
			const std::string & code,
			const std::string & sourceName,
			const time_t & dTimCreation,
			const time_t & dTimLastChange,
			const std::string & comments);
				
		const std::vector<std::string> & getWarnings() const;
	};
}

