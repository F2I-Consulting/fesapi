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
	%include "csharp/std_string_utf8.i"
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

#if defined(SWIGJAVA) || defined(SWIGCSHARP)
	%nspace common::EpcDocument;
	%nspace common::AbstractObject;
	%nspace common::EpcExternalPartReference;
	%nspace common::AbstractHdfProxy;
	%nspace common::HdfProxy;
#endif

namespace resqml2
{
	class Activity;
}

namespace common
{
	%nodefaultctor; // Disable creation of default constructors
	
	class AbstractObject
	{
	public:
		common::EpcDocument* getEpcDocument() const;
	
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
		resqml2::Activity* getActivity (const unsigned int & index) const;
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

namespace resqml2
{
	class Activity;
}

namespace common
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
		
		resqml2_0_1::PropertyKindMapper* getPropertyKindMapper() const;
		
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
		
		const std::vector<resqml2_0_1::LocalDepth3dCrs*> & getLocalDepth3dCrsSet() const;
		const std::vector<resqml2_0_1::LocalTime3dCrs*> & getLocalTime3dCrsSet() const;
		
		const std::vector<resqml2_0_1::StratigraphicColumn*> & getStratigraphicColumnSet() const;
		
		const std::vector<resqml2_0_1::TectonicBoundaryFeature*> & getFaultSet() const;
		const std::vector<resqml2_0_1::TectonicBoundaryFeature*> & getFractureSet() const {return fractureSet;}
		const std::vector<resqml2_0_1::FrontierFeature*> & getFrontierSet() const;
		std::vector<resqml2_0_1::PolylineSetRepresentation*> getFaultPolylineSetRepSet() const;
		std::vector<resqml2_0_1::PolylineSetRepresentation*> getFracturePolylineSetRepSet() const;
		std::vector<resqml2_0_1::PolylineSetRepresentation*> getFrontierPolylineSetRepSet() const;
		std::vector<resqml2_0_1::TriangulatedSetRepresentation*> getFaultTriangulatedSetRepSet() const;
		std::vector<resqml2_0_1::TriangulatedSetRepresentation*> getFractureTriangulatedSetRepSet() const;
		
		std::vector<resqml2_0_1::Horizon*> getHorizonSet() const;
		unsigned int getGeobodyBoundaryCount() const;
		resqml2_0_1::GeneticBoundaryFeature* getGeobodyBoundary(unsigned int index) const;
		const std::vector<resqml2_0_1::GeobodyFeature*> & getGeobodySet() const;
		std::vector<resqml2_0_1::Grid2dSetRepresentation*> getHorizonGrid2dSetRepSet() const;
		std::vector<resqml2_0_1::Grid2dRepresentation*> getHorizonGrid2dRepSet() const;
		std::vector<resqml2_0_1::PolylineRepresentation*> getHorizonPolylineRepSet() const;
		std::vector<resqml2_0_1::PolylineSetRepresentation*> getHorizonPolylineSetRepSet() const;
		std::vector<resqml2_0_1::TriangulatedSetRepresentation*> getHorizonTriangulatedSetRepSet() const;
		const std::vector<resqml2_0_1::TriangulatedSetRepresentation*> & getAllTriangulatedSetRepSet() const;
		std::vector<resqml2_0_1::TriangulatedSetRepresentation*> getUnclassifiedTriangulatedSetRepSet() const;
		
		const std::vector<resqml2_0_1::SeismicLineFeature*> & getSeismicLineSet() const;
		
		const std::vector<resqml2_0_1::WellboreFeature*> & getWellboreSet() const;
		std::vector<resqml2_0_1::WellboreTrajectoryRepresentation*> getWellboreTrajectoryRepresentationSet() const;
		std::vector<resqml2_0_1::DeviationSurveyRepresentation*> getDeviationSurveyRepresentationSet() const;
		
		unsigned int getRepresentationSetRepresentationCount() const;
		resqml2::RepresentationSetRepresentation* getRepresentationSetRepresentation(const unsigned int & index) const;
		
		unsigned int getHdfProxyCount() const;
		common::AbstractHdfProxy* getHdfProxy(const unsigned int & index) const;
		
		unsigned int getIjkGridRepresentationCount() const;
		resqml2_0_1::AbstractIjkGridRepresentation* getIjkGridRepresentation(const unsigned int & i) const;
		std::vector<resqml2_0_1::IjkGridExplicitRepresentation*> getIjkGridExplicitRepresentationSet() const;
		std::vector<resqml2_0_1::IjkGridParametricRepresentation*> getIjkGridParametricRepresentationSet() const;

		std::vector<resqml2_0_1::PolylineRepresentation*> getSeismicLinePolylineRepSet() const;
		std::vector<resqml2_0_1::IjkGridLatticeRepresentation*> getIjkSeismicCubeGridRepresentationSet() const;
		
		const std::vector<resqml2_0_1::UnstructuredGridRepresentation*> & getUnstructuredGridRepresentationSet() const;
		
		unsigned int getSubRepresentationCount() const;
		resqml2::SubRepresentation* getSubRepresentation(const unsigned int & index) const;
		
		unsigned int getPointSetRepresentationCount() const;
		resqml2_0_1::PointSetRepresentation* getPointSetRepresentation(const unsigned int & index) const;
		
		void setExtendedCoreProperty(const std::string & key, const std::string & value);
		std::string getExtendedCoreProperty(const std::string & key);

		common::AbstractObject* getResqmlAbstractObjectByUuid(const std::string & uuid) const;
		witsml1_4_1_1::AbstractObject* getWitsmlAbstractObjectByUuid(const std::string & uuid) const;

		//************************************
		//************ HDF *******************
		//************************************

		virtual common::AbstractHdfProxy* createHdfProxy(const std::string & guid, const std::string & title, const std::string & packageDirAbsolutePath, const std::string & externalFilePath);

		//************************************
		//************ CRS *******************
		//************************************

		resqml2_0_1::LocalDepth3dCrs* createLocalDepth3dCrs(const std::string & guid, const std::string & title,
			const double & originOrdinal1, const double & originOrdinal2, const double & originOrdinal3,
			const double & arealRotation,
			const gsoap_resqml2_0_1::eml20__LengthUom & projectedUom, const unsigned long & projectedEpsgCode,
			const gsoap_resqml2_0_1::eml20__LengthUom & verticalUom, const unsigned int & verticalEpsgCode, const bool & isUpOriented);

		resqml2_0_1::LocalDepth3dCrs* createLocalDepth3dCrs(const std::string & guid, const std::string & title,
			const double & originOrdinal1, const double & originOrdinal2, const double & originOrdinal3,
			const double & arealRotation,
			const gsoap_resqml2_0_1::eml20__LengthUom & projectedUom, const std::string & projectedUnknownReason,
			const gsoap_resqml2_0_1::eml20__LengthUom & verticalUom, const std::string & verticalUnknownReason, const bool & isUpOriented);

		resqml2_0_1::LocalDepth3dCrs* createLocalDepth3dCrs(const std::string & guid, const std::string & title,
			const double & originOrdinal1, const double & originOrdinal2, const double & originOrdinal3,
			const double & arealRotation,
			const gsoap_resqml2_0_1::eml20__LengthUom & projectedUom, const unsigned long & projectedEpsgCode,
			const gsoap_resqml2_0_1::eml20__LengthUom & verticalUom, const std::string & verticalUnknownReason, const bool & isUpOriented);

		resqml2_0_1::LocalDepth3dCrs* createLocalDepth3dCrs(const std::string & guid, const std::string & title,
			const double & originOrdinal1, const double & originOrdinal2, const double & originOrdinal3,
			const double & arealRotation,
			const gsoap_resqml2_0_1::eml20__LengthUom & projectedUom, const std::string & projectedUnknownReason,
			const gsoap_resqml2_0_1::eml20__LengthUom & verticalUom, const unsigned int & verticalEpsgCode, const bool & isUpOriented);
	
		resqml2_0_1::LocalTime3dCrs* createLocalTime3dCrs(const std::string & guid, const std::string & title,
			const double & originOrdinal1, const double & originOrdinal2, const double & originOrdinal3,
			const double & arealRotation,
			const gsoap_resqml2_0_1::eml20__LengthUom & projectedUom, const unsigned long & projectedEpsgCode,
			const gsoap_resqml2_0_1::eml20__TimeUom & timeUom,
			const gsoap_resqml2_0_1::eml20__LengthUom & verticalUom, const unsigned int & verticalEpsgCode, const bool & isUpOriented);

		resqml2_0_1::LocalTime3dCrs* createLocalTime3dCrs(const std::string & guid, const std::string & title,
			const double & originOrdinal1, const double & originOrdinal2, const double & originOrdinal3,
			const double & arealRotation,
			const gsoap_resqml2_0_1::eml20__LengthUom & projectedUom, const std::string & projectedUnknownReason,
			const gsoap_resqml2_0_1::eml20__TimeUom & timeUom,
			const gsoap_resqml2_0_1::eml20__LengthUom & verticalUom, const std::string & verticalUnknownReason, const bool & isUpOriented);

		resqml2_0_1::LocalTime3dCrs* createLocalTime3dCrs(const std::string & guid, const std::string & title,
			const double & originOrdinal1, const double & originOrdinal2, const double & originOrdinal3,
			const double & arealRotation,
			const gsoap_resqml2_0_1::eml20__LengthUom & projectedUom, const unsigned long & projectedEpsgCode,
			const gsoap_resqml2_0_1::eml20__TimeUom & timeUom,
			const gsoap_resqml2_0_1::eml20__LengthUom & verticalUom, const std::string & verticalUnknownReason, const bool & isUpOriented);

		resqml2_0_1::LocalTime3dCrs* createLocalTime3dCrs(const std::string & guid, const std::string & title,
			const double & originOrdinal1, const double & originOrdinal2, const double & originOrdinal3,
			const double & arealRotation,
			const gsoap_resqml2_0_1::eml20__LengthUom & projectedUom, const std::string & projectedUnknownReason,
			const gsoap_resqml2_0_1::eml20__TimeUom & timeUom,
			const gsoap_resqml2_0_1::eml20__LengthUom & verticalUom, const unsigned int & verticalEpsgCode, const bool & isUpOriented);
			
		resqml2_0_1::MdDatum* createMdDatum(const std::string & guid, const std::string & title,
			resqml2::AbstractLocal3dCrs * locCrs, const gsoap_resqml2_0_1::resqml2__MdReference & originKind,
			const double & referenceLocationOrdinal1, const double & referenceLocationOrdinal2, const double & referenceLocationOrdinal3);

		//************************************
		//************ FEATURE ***************
		//************************************

		resqml2_0_1::BoundaryFeature* createBoundaryFeature(const std::string & guid, const std::string & title);

		resqml2_0_1::Horizon* createHorizon(const std::string & guid, const std::string & title);

		resqml2_0_1::GeneticBoundaryFeature* createGeobodyBoundaryFeature(const std::string & guid, const std::string & title);

		resqml2_0_1::GeobodyFeature* createGeobodyFeature(const std::string & guid, const std::string & title);

		resqml2_0_1::TectonicBoundaryFeature* createFault(const std::string & guid, const std::string & title);
		
		resqml2_0_1::TectonicBoundaryFeature* createFracture(const std::string & guid, const std::string & title);
		
		resqml2_0_1::WellboreFeature* createWellboreFeature(const std::string & guid, const std::string & title);
		
		resqml2_0_1::SeismicLatticeFeature* createSeismicLattice(const std::string & guid, const std::string & title,
			const int & inlineIncrement, const int & crosslineIncrement,
			const unsigned int & originInline, const unsigned int & originCrossline,
			const unsigned int & inlineCount, const unsigned int & crosslineCount);

		resqml2_0_1::SeismicLineFeature* createSeismicLine(const std::string & guid, const std::string & title,
			const int & traceIndexIncrement, const unsigned int & firstTraceIndex, const unsigned int & traceCount);
			
		resqml2_0_1::SeismicLineSetFeature* createSeismicLineSet(const std::string & guid, const std::string & title);

		resqml2_0_1::FrontierFeature* createFrontier(const std::string & guid, const std::string & title);
			
		resqml2_0_1::OrganizationFeature* createStructuralModel(const std::string & guid, const std::string & title);
		
		resqml2_0_1::StratigraphicUnitFeature* createStratigraphicUnit(const std::string & guid, const std::string & title);
		
		resqml2_0_1::OrganizationFeature* createStratigraphicModel(const std::string & guid, const std::string & title);

        resqml2_0_1::OrganizationFeature* createEarthModel(const std::string & guid, const std::string & title);
		
		resqml2_0_1::FluidBoundaryFeature* createFluidBoundaryFeature(const std::string & guid, const std::string & title, const gsoap_resqml2_0_1::resqml2__FluidContact & fluidContact);
		
		//************************************
		//************ INTERPRETATION ********
		//************************************

		resqml2_0_1::GenericFeatureInterpretation* createGenericFeatureInterpretation(resqml2::AbstractFeature * feature, const std::string & guid, const std::string & title);
		
		resqml2_0_1::BoundaryFeatureInterpretation* createBoundaryFeatureInterpretation(resqml2_0_1::BoundaryFeature * feature, const std::string & guid, const std::string & title);

		resqml2_0_1::HorizonInterpretation* createHorizonInterpretation(resqml2_0_1::Horizon * horizon, const std::string & guid, const std::string & title);

		resqml2_0_1::GeobodyBoundaryInterpretation* createGeobodyBoundaryInterpretation(resqml2_0_1::GeneticBoundaryFeature * geobodyBoundary, const std::string & guid, const std::string & title);

		resqml2_0_1::FaultInterpretation* createFaultInterpretation(resqml2_0_1::TectonicBoundaryFeature* fault, const std::string & guid, const std::string & title);
		
		resqml2_0_1::WellboreInterpretation* createWellboreInterpretation(resqml2_0_1::WellboreFeature * wellbore, const std::string & guid, const std::string & title, bool isDrilled);
		
		resqml2_0_1::EarthModelInterpretation* createEarthModelInterpretation(resqml2_0_1::OrganizationFeature * orgFeat, const std::string & guid, const std::string & title);

		resqml2_0_1::StructuralOrganizationInterpretation* createStructuralOrganizationInterpretationInAge(resqml2_0_1::OrganizationFeature * orgFeat, const std::string & guid, const std::string & title);	
		resqml2_0_1::StructuralOrganizationInterpretation* createStructuralOrganizationInterpretationInApparentDepth(resqml2_0_1::OrganizationFeature * orgFeat, const std::string & guid, const std::string & title);		
		resqml2_0_1::StructuralOrganizationInterpretation* createStructuralOrganizationInterpretationInMeasuredDepth(resqml2_0_1::OrganizationFeature * orgFeat, const std::string & guid, const std::string & title);

		resqml2_0_1::GeobodyInterpretation* createGeobodyInterpretation(resqml2_0_1::GeobodyFeature * geobody, const std::string & guid, const std::string & title);

		resqml2_0_1::StratigraphicUnitInterpretation* createStratigraphicUnitInterpretation(resqml2_0_1::StratigraphicUnitFeature * stratiUnitFeature, const std::string & guid, const std::string & title);
		resqml2_0_1::StratigraphicColumn* createStratigraphicColumn(const std::string & guid, const std::string & title);
		resqml2_0_1::StratigraphicColumnRankInterpretation* createStratigraphicColumnRankInterpretationInAge(resqml2_0_1::OrganizationFeature * orgFeat, const std::string & guid, const std::string & title, const unsigned long & rank);
		resqml2_0_1::StratigraphicColumnRankInterpretation* createStratigraphicColumnRankInterpretationInApparentDepth(resqml2_0_1::OrganizationFeature * orgFeat, const std::string & guid, const std::string & title, const unsigned long & rank);
		resqml2_0_1::StratigraphicOccurrenceInterpretation* createStratigraphicOccurrenceInterpretationInAge(resqml2_0_1::OrganizationFeature * orgFeat, const std::string & guid, const std::string & title);
		resqml2_0_1::StratigraphicOccurrenceInterpretation* createStratigraphicOccurrenceInterpretationInApparentDepth(resqml2_0_1::OrganizationFeature * orgFeat, const std::string & guid, const std::string & title);

		//************************************
		//************ REPRESENTATION ********
		//************************************

		resqml2_0_1::TriangulatedSetRepresentation* createTriangulatedSetRepresentation(resqml2::AbstractFeatureInterpretation* interp, resqml2::AbstractLocal3dCrs * crs, const std::string & guid, const std::string & title);

		resqml2_0_1::PolylineSetRepresentation* createPolylineSetRepresentation(resqml2::AbstractLocal3dCrs * crs, const std::string & guid, const std::string & title);
		
		resqml2_0_1::PolylineSetRepresentation* createPolylineSetRepresentation(resqml2::AbstractFeatureInterpretation* interp, resqml2::AbstractLocal3dCrs * crs, const std::string & guid, const std::string & title);

		resqml2_0_1::PolylineSetRepresentation* createPolylineSetRepresentation(resqml2::AbstractFeatureInterpretation* interp, resqml2::AbstractLocal3dCrs * crs, const std::string & guid, const std::string & title, const gsoap_resqml2_0_1::resqml2__LineRole & roleKind);
			
		resqml2_0_1::PointSetRepresentation* createPointSetRepresentation(resqml2::AbstractFeatureInterpretation* interp, resqml2::AbstractLocal3dCrs * crs,	const std::string & guid, const std::string & title);

		resqml2_0_1::PlaneSetRepresentation* createPlaneSetRepresentation(resqml2::AbstractFeatureInterpretation* interp, resqml2::AbstractLocal3dCrs * crs, const std::string & guid, const std::string & title);
		
		resqml2_0_1::PolylineRepresentation* createPolylineRepresentation(resqml2::AbstractLocal3dCrs * crs, const std::string & guid, const std::string & title, bool isClosed = false);
		
		resqml2_0_1::PolylineRepresentation* createPolylineRepresentation(resqml2::AbstractFeatureInterpretation* interp, resqml2::AbstractLocal3dCrs * crs, const std::string & guid, const std::string & title, bool isClosed = false);

		resqml2_0_1::PolylineRepresentation* createPolylineRepresentation(resqml2::AbstractFeatureInterpretation* interp, resqml2::AbstractLocal3dCrs * crs, const std::string & guid, const std::string & title, const gsoap_resqml2_0_1::resqml2__LineRole & roleKind, bool isClosed = false);

		resqml2_0_1::Grid2dRepresentation* createGrid2dRepresentation(resqml2::AbstractFeatureInterpretation* interp, resqml2::AbstractLocal3dCrs * crs, const std::string & guid, const std::string & title);

		resqml2_0_1::WellboreTrajectoryRepresentation* createWellboreTrajectoryRepresentation(resqml2_0_1::WellboreInterpretation* interp, const std::string & guid, const std::string & title, resqml2_0_1::MdDatum * mdInfo);	
		resqml2_0_1::WellboreTrajectoryRepresentation* createWellboreTrajectoryRepresentation(resqml2_0_1::WellboreInterpretation* interp, const std::string & guid, const std::string & title, resqml2_0_1::DeviationSurveyRepresentation* deviationSurvey);
		
		resqml2_0_1::DeviationSurveyRepresentation* createDeviationSurveyRepresentation(resqml2_0_1::WellboreInterpretation* interp, const std::string & guid, const std::string & title, const bool & isFinal, resqml2::MdDatum * mdInfo);
		
		resqml2_0_1::WellboreFrameRepresentation* createWellboreFrameRepresentation(resqml2_0_1::WellboreInterpretation* interp, const std::string & guid, const std::string & title, resqml2_0_1::WellboreTrajectoryRepresentation * traj);

		resqml2_0_1::WellboreMarkerFrameRepresentation* createWellboreMarkerFrameRepresentation(resqml2_0_1::WellboreInterpretation* interp, const std::string & guid, const std::string & title, resqml2_0_1::WellboreTrajectoryRepresentation * traj);
			
		resqml2::RepresentationSetRepresentation* createRepresentationSetRepresentation(
                resqml2_0_1::AbstractOrganizationInterpretation* interp,
                const std::string & guid,
				const std::string & title);

		resqml2::RepresentationSetRepresentation* createRepresentationSetRepresentation(
			const std::string & guid,
			const std::string & title);
			
		resqml2::RepresentationSetRepresentation* createPartialRepresentationSetRepresentation(const std::string & guid, const std::string & title);
                
        resqml2_0_1::NonSealedSurfaceFrameworkRepresentation* createNonSealedSurfaceFrameworkRepresentation(
                resqml2_0_1::StructuralOrganizationInterpretation* interp, 
                const std::string & guid, 
                const std::string & title,
                const bool & isSealed);

		resqml2_0_1::SealedSurfaceFrameworkRepresentation* createSealedSurfaceFrameworkRepresentation(
		        resqml2_0_1::StructuralOrganizationInterpretation* interp,
		        const std::string & guid,
		        const std::string & title);
				
		resqml2_0_1::AbstractIjkGridRepresentation* createPartialIjkGridRepresentation(const std::string & guid, const std::string & title);
    	        
		resqml2_0_1::IjkGridExplicitRepresentation* createIjkGridExplicitRepresentation(resqml2::AbstractLocal3dCrs * crs,
			const std::string & guid, const std::string & title,
			const unsigned int & iCount, const unsigned int & jCount, const unsigned int & kCount);

		resqml2_0_1::IjkGridExplicitRepresentation* createIjkGridExplicitRepresentation(resqml2::AbstractFeatureInterpretation* interp, resqml2::AbstractLocal3dCrs * crs,
			const std::string & guid, const std::string & title,
			const unsigned int & iCount, const unsigned int & jCount, const unsigned int & kCount);

		resqml2_0_1::IjkGridParametricRepresentation* createIjkGridParametricRepresentation(resqml2::AbstractLocal3dCrs * crs,
			const std::string & guid, const std::string & title,
			const unsigned int & iCount, const unsigned int & jCount, const unsigned int & kCount);

		resqml2_0_1::IjkGridParametricRepresentation* createIjkGridParametricRepresentation(resqml2::AbstractFeatureInterpretation* interp, resqml2::AbstractLocal3dCrs * crs,
			const std::string & guid, const std::string & title,
			const unsigned int & iCount, const unsigned int & jCount, const unsigned int & kCount);

		resqml2_0_1::IjkGridLatticeRepresentation* createIjkGridLatticeRepresentation(resqml2::AbstractLocal3dCrs * crs,
			const std::string & guid, const std::string & title,
			const unsigned int & iCount, const unsigned int & jCount, const unsigned int & kCount);

		resqml2_0_1::IjkGridLatticeRepresentation* createIjkGridLatticeRepresentation(resqml2::AbstractFeatureInterpretation* interp, resqml2::AbstractLocal3dCrs * crs,
			const std::string & guid, const std::string & title,
			const unsigned int & iCount, const unsigned int & jCount, const unsigned int & kCount);

		resqml2_0_1::IjkGridNoGeometryRepresentation* createIjkGridNoGeometryRepresentation(
			const std::string & guid, const std::string & title,
			const unsigned int & iCount, const unsigned int & jCount, const unsigned int & kCount);

		resqml2_0_1::IjkGridNoGeometryRepresentation* createIjkGridNoGeometryRepresentation(resqml2::AbstractFeatureInterpretation* interp,
			const std::string & guid, const std::string & title,
			const unsigned int & iCount, const unsigned int & jCount, const unsigned int & kCount);
			
		resqml2_0_1::UnstructuredGridRepresentation* createPartialUnstructuredGridRepresentation(const std::string & guid, const std::string & title);

		resqml2_0_1::UnstructuredGridRepresentation* createUnstructuredGridRepresentation(resqml2::AbstractLocal3dCrs * crs,
			const std::string & guid, const std::string & title,
			const ULONG64 & cellCount);

		resqml2::SubRepresentation* createPartialSubRepresentation(const std::string & guid, const std::string & title);
			
		resqml2::SubRepresentation* createSubRepresentation(
                const std::string & guid, const std::string & title);
			
		resqml2::SubRepresentation* createSubRepresentation(resqml2::AbstractFeatureInterpretation* interp,
			const std::string & guid, const std::string & title);
		
		resqml2::GridConnectionSetRepresentation* createGridConnectionSetRepresentation(const std::string & guid, const std::string & title);

		resqml2::GridConnectionSetRepresentation* createGridConnectionSetRepresentation(resqml2::AbstractFeatureInterpretation* interp,
                const std::string & guid, const std::string & title);

		//************************************
		//************* PROPERTIES ***********
		//************************************

		resqml2::TimeSeries* createTimeSeries(const std::string & guid, const std::string & title);

		resqml2::TimeSeries* createPartialTimeSeries(const std::string & guid, const std::string & title);
		
		resqml2_0_1::StringTableLookup* createStringTableLookup(const std::string & guid, const std::string & title);
		
		resqml2::PropertyKind* createPropertyKind(const std::string & guid, const std::string & title,
			const std::string & namingSystem, const gsoap_resqml2_0_1::resqml2__ResqmlUom & uom, const gsoap_resqml2_0_1::resqml2__ResqmlPropertyKind & parentEnergisticsPropertyKind);

		resqml2::PropertyKind* createPropertyKind(const std::string & guid, const std::string & title,
			const std::string & namingSystem, const gsoap_resqml2_0_1::resqml2__ResqmlUom & uom, resqml2::PropertyKind * parentPropType);

		resqml2::PropertyKind* createPropertyKind(const std::string & guid, const std::string & title,
			const std::string & namingSystem, const std::string & nonStandardUom, const gsoap_resqml2_0_1::resqml2__ResqmlPropertyKind & parentEnergisticsPropertyKind);

		resqml2::PropertyKind* createPropertyKind(const std::string & guid, const std::string & title,
			const std::string & namingSystem, const std::string & nonStandardUom, resqml2::PropertyKind * parentPropType);

		resqml2::PropertyKind* createPartialPropertyKind(const std::string & guid, const std::string & title);

		resqml2_0_1::CommentProperty* createCommentProperty(resqml2::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			const unsigned int & dimension, const gsoap_resqml2_0_1::resqml2__IndexableElements & attachmentKind, const gsoap_resqml2_0_1::resqml2__ResqmlPropertyKind & energisticsPropertyKind);

		resqml2_0_1::CommentProperty* createCommentProperty(resqml2::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			const unsigned int & dimension, const gsoap_resqml2_0_1::resqml2__IndexableElements & attachmentKind, resqml2::PropertyKind * localPropType);
	
		resqml2_0_1::ContinuousProperty* createContinuousProperty(resqml2::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			const unsigned int & dimension, const gsoap_resqml2_0_1::resqml2__IndexableElements & attachmentKind, const gsoap_resqml2_0_1::resqml2__ResqmlUom & uom, const gsoap_resqml2_0_1::resqml2__ResqmlPropertyKind & energisticsPropertyKind);

		resqml2_0_1::ContinuousProperty* createContinuousProperty(resqml2::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			const unsigned int & dimension, const gsoap_resqml2_0_1::resqml2__IndexableElements & attachmentKind, const gsoap_resqml2_0_1::resqml2__ResqmlUom & uom, resqml2::PropertyKind * localPropType);

		resqml2_0_1::ContinuousProperty* createContinuousProperty(resqml2::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			const unsigned int & dimension, const gsoap_resqml2_0_1::resqml2__IndexableElements & attachmentKind, const std::string & nonStandardUom, const gsoap_resqml2_0_1::resqml2__ResqmlPropertyKind & energisticsPropertyKind);

		resqml2_0_1::ContinuousProperty* createContinuousProperty(resqml2::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			const unsigned int & dimension, const gsoap_resqml2_0_1::resqml2__IndexableElements & attachmentKind, const std::string & nonStandardUom, resqml2::PropertyKind * localPropType);

		resqml2_0_1::ContinuousPropertySeries* createContinuousPropertySeries(resqml2::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			const unsigned int & dimension, const gsoap_resqml2_0_1::resqml2__IndexableElements & attachmentKind, const gsoap_resqml2_0_1::resqml2__ResqmlUom & uom, const gsoap_resqml2_0_1::resqml2__ResqmlPropertyKind & energisticsPropertyKind,
			resqml2::TimeSeries * ts, const bool & useInterval = false);

		resqml2_0_1::ContinuousPropertySeries* createContinuousPropertySeries(resqml2::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			const unsigned int & dimension, const gsoap_resqml2_0_1::resqml2__IndexableElements & attachmentKind, const gsoap_resqml2_0_1::resqml2__ResqmlUom & uom, resqml2::PropertyKind * localPropType,
			resqml2::TimeSeries * ts, const bool & useInterval = false);
	
		resqml2_0_1::DiscreteProperty* createDiscreteProperty(resqml2::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			const unsigned int & dimension, const gsoap_resqml2_0_1::resqml2__IndexableElements & attachmentKind, const gsoap_resqml2_0_1::resqml2__ResqmlPropertyKind & energisticsPropertyKind);

		resqml2_0_1::DiscreteProperty* createDiscreteProperty(resqml2::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			const unsigned int & dimension, const gsoap_resqml2_0_1::resqml2__IndexableElements & attachmentKind, resqml2::PropertyKind * localPropType);
	
		resqml2_0_1::DiscretePropertySeries* createDiscretePropertySeries(resqml2::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			const unsigned int & dimension, const gsoap_resqml2_0_1::resqml2__IndexableElements & attachmentKind, const gsoap_resqml2_0_1::resqml2__ResqmlPropertyKind & energisticsPropertyKind,
			resqml2::TimeSeries * ts, const bool & useInterval = false);

		resqml2_0_1::DiscretePropertySeries* createDiscretePropertySeries(resqml2::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			const unsigned int & dimension, const gsoap_resqml2_0_1::resqml2__IndexableElements & attachmentKind, resqml2::PropertyKind * localPropType,
			resqml2::TimeSeries * ts, const bool & useInterval = false);

		resqml2_0_1::CategoricalProperty* createCategoricalProperty(resqml2::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			const unsigned int & dimension, const gsoap_resqml2_0_1::resqml2__IndexableElements & attachmentKind,
			resqml2_0_1::StringTableLookup* strLookup, const gsoap_resqml2_0_1::resqml2__ResqmlPropertyKind & energisticsPropertyKind);
	
		resqml2_0_1::CategoricalProperty* createCategoricalProperty(resqml2::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			const unsigned int & dimension, const gsoap_resqml2_0_1::resqml2__IndexableElements & attachmentKind,
			resqml2_0_1::StringTableLookup* strLookup, resqml2::PropertyKind * localPropType);

		resqml2_0_1::CategoricalPropertySeries* createCategoricalPropertySeries(resqml2::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			const unsigned int & dimension, const gsoap_resqml2_0_1::resqml2__IndexableElements & attachmentKind,
			resqml2_0_1::StringTableLookup* strLookup, const gsoap_resqml2_0_1::resqml2__ResqmlPropertyKind & energisticsPropertyKind,
			resqml2::TimeSeries * ts, const bool & useInterval = false);

		resqml2_0_1::CategoricalPropertySeries* createCategoricalPropertySeries(resqml2::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			const unsigned int & dimension, const gsoap_resqml2_0_1::resqml2__IndexableElements & attachmentKind,
			resqml2_0_1::StringTableLookup* strLookup, resqml2::PropertyKind * localPropType,
			resqml2::TimeSeries * ts, const bool & useInterval = false);

		//************************************
		//************* ACTIVITIES ***********
		//************************************

		resqml2::ActivityTemplate* createActivityTemplate(const std::string & guid, const std::string & title);
		
		resqml2::Activity* createActivity(resqml2::ActivityTemplate* activityTemplate, const std::string & guid, const std::string & title);
			

		//************************************
		//************ WITSML ****************
		//************************************
		
		std::vector<witsml1_4_1_1::Trajectory*> getWitsmlTrajectorySet() const;
		
		witsml1_4_1_1::Well* createWell(
			const std::string & guid,
			const std::string & title,
			const std::string & timeZone);

		witsml1_4_1_1::Well* createWell(
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

		witsml1_4_1_1::CoordinateReferenceSystem* createCoordinateReferenceSystem(
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
