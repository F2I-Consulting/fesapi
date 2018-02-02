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

#include <string>
#include <vector>
#include <limits>
#include <stdexcept>

#include "proxies/stdsoap2.h"
#include "proxies/gsoap_resqml2_0_1H.h"
#include "proxies/gsoap_witsml1_4_1_1H.h"
#include "proxies/gsoap_eml2_1H.h"

#include "epc/Package.h"

#if (defined(_WIN32) && _MSC_VER < 1600) || (defined(__GNUC__) && (__GNUC__ < 4 || (__GNUC__ == 4 && __GNUC_MINOR__ < 6)))
#include "tools/nullptr_emulation.h"
#endif

#if defined(_WIN32) && defined(FESAPI_DLL)
	#if defined(FesapiCpp_EXPORTS) || defined(FesapiCppUnderDev_EXPORTS)
		#define DLL_IMPORT_OR_EXPORT __declspec(dllexport)
	#else
		#define DLL_IMPORT_OR_EXPORT __declspec(dllimport) 
	#endif
#else
	#define DLL_IMPORT_OR_EXPORT
#endif

namespace resqml2
{
	class AbstractFeature;
	class AbstractFeatureInterpretation;
	class AbstractLocal3dCrs;
	class AbstractRepresentation;
	class Activity;
	class ActivityTemplate;
	class GridConnectionSetRepresentation;
	class MdDatum;
	class PropertyKind;
	class SubRepresentation;
	class TimeSeries;
	class RepresentationSetRepresentation;
}

namespace resqml2_0_1
{
	class Activity;
	class ActivityTemplate;
	class PropertyKindMapper;
	class LocalDepth3dCrs;
	class LocalTime3dCrs;
	class GeneticBoundaryFeature;
	class GeobodyBoundaryInterpretation;
	class GeobodyFeature;
	class GeobodyInterpretation;
	class Horizon;
	class WellboreFeature;
	class SeismicLineFeature;
	class StratigraphicUnitFeature;
	class PolylineSetRepresentation;
	class PolylineRepresentation;
	class TriangulatedSetRepresentation;
	class Grid2dSetRepresentation;
	class Grid2dRepresentation;
	class WellboreTrajectoryRepresentation;
	class DeviationSurveyRepresentation;
	class AbstractIjkGridRepresentation;
	class IjkGridExplicitRepresentation;
	class IjkGridParametricRepresentation;
	class IjkGridLatticeRepresentation;
	class IjkGridNoGeometryRepresentation;
	class UnstructuredGridRepresentation;
	class BoundaryFeature;
	class BoundaryFeatureInterpretation;
	class TectonicBoundaryFeature;
	class SeismicLatticeFeature;
	class SeismicLineSetFeature;
	class OrganizationFeature;
	class GenericFeatureInterpretation;
	class HorizonInterpretation;
	class FaultInterpretation;
	class WellboreInterpretation;
	class EarthModelInterpretation;
	class StructuralOrganizationInterpretation;
	class StratigraphicUnitInterpretation;
	class StratigraphicColumn;
	class StratigraphicColumnRankInterpretation;
	class PointSetRepresentation;
	class WellboreFrameRepresentation;
	class WellboreMarkerFrameRepresentation;
	class NonSealedSurfaceFrameworkRepresentation;
	class SealedSurfaceFrameworkRepresentation;
	class StringTableLookup;
	class CommentProperty;
	class ContinuousProperty;
	class ContinuousPropertySeries;
	class DiscreteProperty;
	class DiscretePropertySeries;
	class CategoricalProperty;
	class CategoricalPropertySeries;
	class AbstractOrganizationInterpretation;
	class AbstractGridRepresentation;
	class OrganizationFeature;
	class StratigraphicOccurrenceInterpretation;
	class FrontierFeature;
	class PlaneSetRepresentation;
	class FluidBoundaryFeature;
	class BlockedWellboreRepresentation;
}

namespace witsml1_4_1_1
{
	class AbstractObject;
	class Well;
	class CoordinateReferenceSystem;
	class Trajectory;
}

namespace prodml2_0
{
	class DasAcquisition;
	class FiberOpticalPath;
	class DasInstrumentBox;
	class HdfProxy;
}

namespace common
{
	class AbstractObject;
	class AbstractHdfProxy;

	/**
	* This class allows an access to a memory package representing an EPC document.
	*/
	class DLL_IMPORT_OR_EXPORT EpcDocument
	{
	private :
		/**
		* In case of PRODML2.0, only one HDF5 file can be given without any EPC document.
		* this method will create a fake/virtual EPC document based on the HDF5 file
		*/
		std::string deserializeProdmlHdf5File();
	public:

		enum openingMode { READ_ONLY = 0, READ_WRITE = 1, OVERWRITE = 2 };

		EpcDocument(const std::string & fileName, const openingMode & hdf5PermissionAccess = READ_ONLY);
		EpcDocument(const std::string & fileName, const std::string & propertyKindMappingFilesDirectory, const openingMode & hdf5PermissionAccess = READ_ONLY);

		/**
		* The destructor frees all allocated ressources.
		*/
		virtual ~EpcDocument() { close(); }

		// A function pointer definition which allows to build an abstract hdf proxy in writing mode of an epc document
		typedef common::AbstractHdfProxy* (HdfProxyBuilder)(soap* soapContext, const std::string & guid, const std::string & title, const std::string & packageDirAbsolutePath, const std::string & externalFilePath, bool v21);
		// A function pointer which allows to build a v2.0.1 abstract hdf proxy in reading mode of an epc document
		typedef common::AbstractHdfProxy* (HdfProxyBuilderFromGsoapProxy2_0_1)(gsoap_resqml2_0_1::_eml20__EpcExternalPartReference* fromGsoap, const std::string & packageDirAbsolutePath, const std::string & externalFilePath);
		// A function pointer which allows to build a v2.0.1 abstract hdf proxy in reading mode of an epc document
		typedef prodml2_0::HdfProxy* (HdfProxyBuilderFromGsoapProxy2_1)(gsoap_eml2_1::_eml21__EpcExternalPartReference* fromGsoap, const std::string & packageDirAbsolutePath, const std::string & externalFilePath);

		// Allows a fesapi user to set a different builder of Hdf Proxy than the default one in writing mode of an epc document
		// This is especially useful when the fesapi users wants to use its own builder for example.
		void set_hdf_proxy_builder(HdfProxyBuilder builder);
		void set_hdf_proxy_builder(HdfProxyBuilderFromGsoapProxy2_0_1 builder);
		void set_hdf_proxy_builder(HdfProxyBuilderFromGsoapProxy2_1 builder);

		/**
		* Open an epc document.
		* If already opened, the epc document must be closed before to open a new one.
		* Don't forget to call close() before to destroy this object.
		*/
		void open(const std::string & fileName, const openingMode & hdf5PermissionAccess = READ_ONLY);
	
		/**
		 * Free all ressources contained in this package.
		 */
		void close();

		const openingMode & getHdf5PermissionAccess() const;

		/**
		 * Set the file path which will be used for future serialization and deserialization
		 * Will add the standard epc extension to the filePath is not already present.
		 */
		void setFilePath(const std::string & filePath);

		/**
		* Serialize the package by serializing all the gsoap wrappers and by zipping the package.
		*/
		virtual void serialize(bool useZip64 = false);

		/**
		* Unzip the package and get all contained elements with their relationships
		* @return			An empty string if everything's ok otherwise the error string.
		*/
		virtual std::string deserialize();

		/**
		* Get the soap context of the epc document.
		*/
		soap* getGsoapContext() const;

		/**
		* Add a gsoap proxy to serialize with the package
		*/
		void addGsoapProxy(common::AbstractObject* proxy);

		/**
		* Add a gsoap proxy to serialize with the package
		*/
		void addGsoapProxy(witsml1_4_1_1::AbstractObject* proxy);

		/**
		 * Get the property kind mapper of this epc document if given at EPC document construction time.
		 * Else return NULL.
		 */
		resqml2_0_1::PropertyKindMapper* getPropertyKindMapper() const;

		/**
		* Get the name of the energistics property kind as a string based on the enumerated property kind.
		* @return The empty string if no correspondence is found
		*/
		std::string getEnergisticsPropertyKindName(const gsoap_resqml2_0_1::resqml2__ResqmlPropertyKind & energisticsPropertyKind) const;

		/**
		* Get the Energistics property kind enumerated value from the name (string) of the property kind.
		* @return The most abstract energistics property kind if no correspondance is found with the property kind string/name.
		*/
		gsoap_resqml2_0_1::resqml2__ResqmlPropertyKind getEnergisticsPropertyKind(const std::string & energisticsPropertyKindName) const;

		/**
		* Get the name of the resqml standard property type as a string based on the enumerated property kind.
		* @return The empty string if no correspondence is found
		*/
		std::string getEnergisticsUnitOfMeasureName(const gsoap_resqml2_0_1::resqml2__ResqmlUom & energisticsUom) const;

		/**
		* Get the Energistics unit of measure enumerated value from the name (string) of the uom.
		* @return The Euclidian (no uom) energistics uom if no correspondance is found with the uom string/name.
		*/
		gsoap_resqml2_0_1::resqml2__ResqmlUom getEnergisticsUnitOfMeasure(const std::string & energisticsUomName) const;

		/**
		* Get the name of the resqml facet as a string based on the enumerated facet.
		* @return The empty string if no correspondence is found
		*/
		std::string getFacet(const gsoap_resqml2_0_1::resqml2__Facet & facet) const;

		/**
		* Get the facet enumerated value from the name (string) of the facet.
		* @return The what facet if no correspondance is found with the facet string/name.
		*/
		gsoap_resqml2_0_1::resqml2__Facet getFacet(const std::string & facet) const;

		/**
		* Get the name (string) of the witsml uom as a string based on the enumerated uom.
		* @return The empty string if no correspondence is found
		*/
		std::string getWitsmlLengthUom(const gsoap_witsml1_4_1_1::witsml1__LengthUom & witsmlUom) const;

		/**
		* Get the name (string) of the witsml uom as a string based on the enumerated uom.
		* @return The empty string if no correspondence is found
		*/
		std::string getWitsmlWellVerticalCoordinateUom(const gsoap_witsml1_4_1_1::witsml1__WellVerticalCoordinateUom & witsmlUom) const;

		/**
		* Get the name (string) of the witsml uom as a string based on the enumerated uom.
		* @return The empty string if no correspondence is found
		*/
		std::string getWitsmlMeasuredDepthUom(const gsoap_witsml1_4_1_1::witsml1__MeasuredDepthUom & witsmlUom) const;

		/**
		* Get the name (string) of the witsml uom as a string based on the enumerated uom.
		* @return The empty string if no correspondence is found
		*/
		std::string getWitsmlPlaneAngleUom(const gsoap_witsml1_4_1_1::witsml1__PlaneAngleUom & witsmlUom) const;

		/**
		* Get all the resqml gsoap wrappers from the epc document
		*/
#if (defined(_WIN32) && _MSC_VER >= 1600) || defined(__APPLE__)
		const std::unordered_map< std::string, common::AbstractObject* > & getResqmlAbstractObjectSet() const;
#else
		const std::tr1::unordered_map< std::string, common::AbstractObject* > & getResqmlAbstractObjectSet() const;
#endif

		/**
		* Get the Gsoap type  by means of its uuid
		*/
		common::AbstractObject* getResqmlAbstractObjectByUuid(const std::string & uuid, int & gsoapType) const;

		/**
		* Get a gsoap wrapper from the epc document by means of its uuid
		*/
		common::AbstractObject* getResqmlAbstractObjectByUuid(const std::string & uuid) const;

		/**
		* Get a gsoap wrapper from the epc document by means of its uuid
		* and try to cast it to a child class of common::AbstractObject
		*/
		template <class valueType>
		valueType* getResqmlAbstractObjectByUuid(const std::string & uuid) const
		{
			common::AbstractObject* const result = getResqmlAbstractObjectByUuid(uuid);

			if (result == nullptr) {
				return nullptr;
			}

			if (dynamic_cast<valueType*>(result) != nullptr) {
				return static_cast<valueType*>(result);
			}

			throw std::invalid_argument("The uuid " + uuid + " does not resolve to the expected datatype");
		}

		witsml1_4_1_1::AbstractObject* getWitsmlAbstractObjectByUuid(const std::string & uuid) const;

		std::vector<prodml2_0::DasAcquisition*> getDasAcquisitionSet() const;

		/**
		* Get all the local 3d depth crs contained into the EPC document
		*/
		const std::vector<resqml2_0_1::LocalDepth3dCrs*> & getLocalDepth3dCrsSet() const;

		/**
		* Get all the local 3d time crs contained into the EPC document
		*/
		const std::vector<resqml2_0_1::LocalTime3dCrs*> & getLocalTime3dCrsSet() const;

		/**
		* Get all the stratigraphic columns contained into the EPC document
		*/
		const std::vector<resqml2_0_1::StratigraphicColumn*> & getStratigraphicColumnSet() const;

		/**
		* Get all the faults contained into the EPC document
		*/
		const std::vector<resqml2_0_1::TectonicBoundaryFeature*> & getFaultSet() const;

		/**
		* Get all the fractures contained into the EPC document
		*/
		const std::vector<resqml2_0_1::TectonicBoundaryFeature*> & getFractureSet() const;

		/**
		* Get all the individual representations of faults which are associated to a polyline topology
		*/
		std::vector<resqml2_0_1::PolylineSetRepresentation*> getFaultPolylineSetRepSet() const;

		/**
		* Get all the individual representations of fractures which are associated to a polyline topology
		*/
		std::vector<resqml2_0_1::PolylineSetRepresentation*> getFracturePolylineSetRepSet() const;

		/**
		* Get all the individual representations of frontiers which are associated to a polyline set topology
		*/
		std::vector<resqml2_0_1::PolylineSetRepresentation*> getFrontierPolylineSetRepSet() const;

		/**
		* Get all the individual representations of faults which are associated to a triangulation set topology
		*/
		std::vector<resqml2_0_1::TriangulatedSetRepresentation*> getFaultTriangulatedSetRepSet() const;

        /**
		* Get all the individual representations of fractures which are associated to a triangulation set topology
		*/
		std::vector<resqml2_0_1::TriangulatedSetRepresentation*> getFractureTriangulatedSetRepSet() const;

		/**
		* Get all the horizons contained into the EPC document
		*/
		std::vector<resqml2_0_1::Horizon*> getHorizonSet() const;

		/**
		* Get all the geobody boundaries contained into the EPC document
		*/
		std::vector<resqml2_0_1::GeneticBoundaryFeature*> getGeobodyBoundarySet() const;
		unsigned int getGeobodyBoundaryCount() const;
		resqml2_0_1::GeneticBoundaryFeature* getGeobodyBoundary(unsigned int index) const;

		/**
		* Get all the geobodies contained into the EPC document
		*/
		const std::vector<resqml2_0_1::GeobodyFeature*> & getGeobodySet() const;

		/**
		* Get all the individual representations of horizons which are associated to grid 2d set topology
		*/
		std::vector<resqml2_0_1::Grid2dSetRepresentation*> getHorizonGrid2dSetRepSet() const;
        
		/**
		* Get all the individual representations of horizons which are associated to grid 2d set topology
		*/
		std::vector<resqml2_0_1::Grid2dRepresentation*> getHorizonGrid2dRepSet() const;
        
		/**
		* Get all the single polyline representations of all the horizons
		*/
		std::vector<resqml2_0_1::PolylineRepresentation*> getHorizonPolylineRepSet() const;
        
		/**
		* Get all the single polyline representations of all the horizons
		*/
		std::vector<resqml2_0_1::PolylineSetRepresentation*> getHorizonPolylineSetRepSet() const;
        
        /**
		* Get all the triangulated set representations of all the horizons
		*/
		std::vector<resqml2_0_1::TriangulatedSetRepresentation*> getHorizonTriangulatedSetRepSet() const;

		/**
		* Get all the triangulated set representations of the EPC document
		*/
		const std::vector<resqml2_0_1::TriangulatedSetRepresentation*> & getAllTriangulatedSetRepSet() const;

		/**
		* Get all the triangulated set representations of the EPC document which are not horizon and fault neither.
		*/
		std::vector<resqml2_0_1::TriangulatedSetRepresentation*> getUnclassifiedTriangulatedSetRepSet() const;

		/**
		* Get all the seismic line contained into the EPC document
		*/
		const std::vector<resqml2_0_1::SeismicLineFeature*> & getSeismicLineSet() const;

		/**
		* Get all the wellbores contained into the EPC document
		*/
		const std::vector<resqml2_0_1::WellboreFeature*> & getWellboreSet() const;

		/**
		* Get all the trajectory representations of all wellbores.
		*/
		std::vector<resqml2_0_1::WellboreTrajectoryRepresentation*> getWellboreTrajectoryRepresentationSet() const;

		/**
		* Get all the devaition survey of all wellbores.
		*/
		std::vector<resqml2_0_1::DeviationSurveyRepresentation*> getDeviationSurveyRepresentationSet() const;

		/**
		* Get all the representationset representations contained into the EPC document
		*/
		const std::vector<resqml2::RepresentationSetRepresentation*> & getRepresentationSetRepresentationSet() const;

		/**
		* Get the representationset representations count of this EPC document
		*/
		unsigned int getRepresentationSetRepresentationCount() const;

		/**
		* Get the representationset representations at a particular index of this EPC document
		*/
		resqml2::RepresentationSetRepresentation* getRepresentationSetRepresentation(const unsigned int & index) const;

		/**
		* Get all the polyline representation contained into the EPC document.
		*/
		std::vector<resqml2_0_1::PolylineRepresentation*> getPolylineRepresentationSet() const;

		/**
		* Get all the single polyline representations contained into the EPC document which correspond to a seismic line.
		*/
		std::vector<resqml2_0_1::PolylineRepresentation*> getSeismicLinePolylineRepSet() const;

		/**
		* Get all the ijk grid contained into the EPC document.
		*/
		const std::vector<resqml2_0_1::AbstractIjkGridRepresentation*> & getIjkGridRepresentationSet() const;
		unsigned int getIjkGridRepresentationCount() const;
		resqml2_0_1::AbstractIjkGridRepresentation* getIjkGridRepresentation(const unsigned int & i) const;

		/**
		* Get all the ijk grid contained into the EPC document which have a parametric geometry.
		*/
		std::vector<resqml2_0_1::IjkGridParametricRepresentation*> getIjkGridParametricRepresentationSet() const;

		/**
		* Get all the ijk grid contained into the EPC document which have an explicit geometry.
		*/
		std::vector<resqml2_0_1::IjkGridExplicitRepresentation*> getIjkGridExplicitRepresentationSet() const;

		/**
		* Get all the ijk grid contained into the EPC document which correspond to a seismic cube.
		*/
		std::vector<resqml2_0_1::IjkGridLatticeRepresentation*> getIjkSeismicCubeGridRepresentationSet() const;

		/**
		* Get all the unstructured grid contained into the EPC document
		*/
		const std::vector<resqml2_0_1::UnstructuredGridRepresentation*> & getUnstructuredGridRepresentationSet() const;

		/**
		* Get all the frontier features contained into the EPC document
		*/
		const std::vector<resqml2_0_1::FrontierFeature*> & getFrontierSet() const;

		/**
		 * Get all the organization features contained into the EPC document
		 */
		const std::vector<resqml2_0_1::OrganizationFeature*> & getOrganizationSet() const;

		/**
		 * Get all the time series contained into the EPC document
		 */
		const std::vector<resqml2::TimeSeries*> & getTimeSeriesSet() const;

		/**
		 * Get all the subrepresentations contained into the EPC document
		 */
		const std::vector<resqml2::SubRepresentation*> & getSubRepresentationSet() const;
		unsigned int getSubRepresentationCount() const;
		resqml2::SubRepresentation* getSubRepresentation(const unsigned int & index) const;

		/**
		* Get all the point set representations contained into the EPC document
		*/
		const std::vector<resqml2_0_1::PointSetRepresentation*> & getPointSetRepresentationSet() const;
		unsigned int getPointSetRepresentationCount() const;
		resqml2_0_1::PointSetRepresentation* getPointSetRepresentation(const unsigned int & index) const;

		/**
		* Get all the Hdf proxies used with this EPC document
		*/
		const std::vector<common::AbstractHdfProxy*> & getHdfProxySet() const;
		unsigned int getHdfProxyCount() const;
		common::AbstractHdfProxy* getHdfProxy(const unsigned int & index) const;

		/**
		* Get the absolute path of the directory where the epc document is stored.
		*/
		std::string getStorageDirectory() const;

		/**
		* Get the name of the epc document.
		*/
		std::string getName() const;

		/**
		* Try to resolve in memory all the relationshsips which are serialized into Resqml objects of the EPC document
		*/
		void updateAllRelationships();

#if (defined(_WIN32) && _MSC_VER >= 1600) || defined(__APPLE__)
		std::unordered_map< std::string, std::string > & getExtendedCoreProperty();
#else
		std::tr1::unordered_map< std::string, std::string > & getExtendedCoreProperty();
#endif

		void setExtendedCoreProperty(const std::string & key, const std::string & value);

		/**
		* Get an extended core property value according its key.
		* @return An empty string if the extended core property does not exist. Or the extended core property value if it exists
		*/
		std::string getExtendedCoreProperty(const std::string & key);

		/**
		* Create a partial object in this EpcDocument based on a Data Object Reference
		*/
		common::AbstractObject* createPartial(gsoap_resqml2_0_1::eml20__DataObjectReference* dor);

		/**
		* Create a partial object i.e. a data object reference (DOR)
		*/
		template <class valueType>
		valueType* createPartial(const std::string & guid, const std::string & title)
		{
			gsoap_resqml2_0_1::eml20__DataObjectReference* dor = gsoap_resqml2_0_1::soap_new_eml20__DataObjectReference(s, 1);
			dor->UUID = guid;
			dor->Title = title;
			valueType* result = new valueType(dor);
			addFesapiWrapperAndDeleteItIfException(result);
			return result;
		}

		//************************************
		//************ HDF *******************
		//************************************

		virtual common::AbstractHdfProxy* createHdfProxy(const std::string & guid, const std::string & title, const std::string & packageDirAbsolutePath, const std::string & externalFilePath, bool v21 = false);

		//************************************
		//************ CRS *******************
		//************************************

		/**
		* Creates a local depth 3d CRS which is fully identified by means of EPSG code.
		* @param guid				The guid to set to the local 3d crs. If empty then a new guid will be generated.
		* @param title				A title for the instance to create.
		* @param originOrdinal1		The offset of the global 2d crs on its first axis.
		* @param originOrdinal2		The offset of the global 2d crs on its second axis.
		* @param originOrdinal3		The offset in depth of the local CRS regarding the depth origin of the vertical CRS.
		* @param arealRotation		The areal rotation in radians regarding the projected crs.
		* @param projectedUom		The unit of measure of the projected axis of this instance.
		* @param projectedEpsgCode	The epsg code of the associated projected CRS.
		* @param verticalUom		The unit of measure of the vertical axis of this instance.
		* @param verticalEpsgCode	The epsg code of the associated vertical CRS.
		* @param isUpOriented		If true, indicates that this depth CRS is actually an elevation CRS.
		*/
		resqml2_0_1::LocalDepth3dCrs* createLocalDepth3dCrs(const std::string & guid, const std::string & title,
			const double & originOrdinal1, const double & originOrdinal2, const double & originOrdinal3,
			const double & arealRotation,
			const gsoap_resqml2_0_1::eml20__LengthUom & projectedUom, const unsigned long & projectedEpsgCode,
			const gsoap_resqml2_0_1::eml20__LengthUom & verticalUom, const unsigned int & verticalEpsgCode, const bool & isUpOriented);
		
		/**
		* Creates a local depth 3d CRS which is fully unknown.
		* @param guid					The guid to set to the local 3d crs. If empty then a new guid will be generated.
		* @param title					A title for the instance to create.
		* @param originOrdinal1			The offset of the global 2d crs on its first axis.
		* @param originOrdinal2			The offset of the global 2d crs on its second axis.
		* @param originOrdinal3			The offset in depth of the local CRS regarding the depth origin of the vertical CRS.
		* @param arealRotation			The areal rotation in radians regarding the projected crs.
		* @param projectedUom			The unit of measure of the projected axis of this instance.
		* @param projectedUnknownReason	Indicates why the projected CRS cannot be provided using EPSG or GML.
		* @param verticalUom			The unit of measure of the vertical axis of this instance.
		* @param verticalUnknownReason	Indicates why the vertical CRS cannot be provided using EPSG or GML.
		* @param isUpOriented			If true, indicates that this depth CRS is actually an elevation CRS.
		*/
		resqml2_0_1::LocalDepth3dCrs* createLocalDepth3dCrs(const std::string & guid, const std::string & title,
			const double & originOrdinal1, const double & originOrdinal2, const double & originOrdinal3,
			const double & arealRotation,
			const gsoap_resqml2_0_1::eml20__LengthUom & projectedUom, const std::string & projectedUnknownReason,
			const gsoap_resqml2_0_1::eml20__LengthUom & verticalUom, const std::string & verticalUnknownReason, const bool & isUpOriented);

		/**
		* Creates a local depth 3d CRS which is identified by an EPSG code for its projected part and which is unkown for its vertial part.
		* @param guid					The guid to set to the local 3d crs. If empty then a new guid will be generated.
		* @param title					A title for the instance to create.
		* @param originOrdinal1			The offset of the global 2d crs on its first axis.
		* @param originOrdinal2			The offset of the global 2d crs on its second axis.
		* @param originOrdinal3			The offset in depth of the local CRS regarding the depth origin of the vertical CRS.
		* @param arealRotation			The areal rotation in radians regarding the projected crs.
		* @param projectedUom			The unit of measure of the projected axis of this instance.
		* @param projectedEpsgCode		The epsg code of the associated projected CRS.
		* @param verticalUom			The unit of measure of the vertical axis of this instance.
		* @param verticalUnknownReason	Indicates why the vertical CRS cannot be provided using EPSG or GML.
		* @param isUpOriented			If true, indicates that this depth CRS is actually an elevation CRS.
		*/
		resqml2_0_1::LocalDepth3dCrs* createLocalDepth3dCrs(const std::string & guid, const std::string & title,
			const double & originOrdinal1, const double & originOrdinal2, const double & originOrdinal3,
			const double & arealRotation,
			const gsoap_resqml2_0_1::eml20__LengthUom & projectedUom, const unsigned long & projectedEpsgCode,
			const gsoap_resqml2_0_1::eml20__LengthUom & verticalUom, const std::string & verticalUnknownReason, const bool & isUpOriented);

		/**
		* Creates a local depth 3d CRS which unkown for its projected part and which is identified by an EPSG code for its vertical part.
		* @param guid					The guid to set to the local 3d crs. If empty then a new guid will be generated.
		* @param title					A title for the instance to create.
		* @param originOrdinal1			The offset of the global 2d crs on its first axis.
		* @param originOrdinal2			The offset of the global 2d crs on its second axis.
		* @param originOrdinal3			The offset in depth of the local CRS regarding the depth origin of the vertical CRS.
		* @param arealRotation			The areal rotation in radians regarding the projected crs.
		* @param projectedUom			The unit of measure of the projected axis of this instance.
		* @param projectedUnknownReason	Indicates why the projected CRS cannot be provided using EPSG or GML.
		* @param verticalUom			The unit of measure of the vertical axis of this instance.
		* @param verticalEpsgCode		The epsg code of the associated vertical CRS.
		* @param isUpOriented			If true, indicates that this depth CRS is actually an elevation CRS.
		*/
		resqml2_0_1::LocalDepth3dCrs* createLocalDepth3dCrs(const std::string & guid, const std::string & title,
			const double & originOrdinal1, const double & originOrdinal2, const double & originOrdinal3,
			const double & arealRotation,
			const gsoap_resqml2_0_1::eml20__LengthUom & projectedUom, const std::string & projectedUnknownReason,
			const gsoap_resqml2_0_1::eml20__LengthUom & verticalUom, const unsigned int & verticalEpsgCode, const bool & isUpOriented);
	
		/**
		* Creates a local depth 3d CRS which is fully identified by means of EPSG code.
		* @param guid				The guid to set to the local 3d crs. If empty then a new guid will be generated.
		* @param title				A title for the instance to create.
		* @param originOrdinal1		The offset of the global 2d crs on its first axis.
		* @param originOrdinal2		The offset of the global 2d crs on its second axis.
		* @param originOrdinal3		The offset in depth of the local CRS regarding the depth origin of the vertical CRS.
		* @param arealRotation		The areal rotation in radians regarding the projected crs.
		* @param projectedUom		The unit of measure of the projected axis of this instance.
		* @param projectedEpsgCode	The epsg code of the associated projected CRS.
		* @param timeUom			The unit of measure of the Z offset of this instance.
		* @param verticalUom		The unit of measure of the vertical axis of this instance.
		* @param verticalEpsgCode	The epsg code of the associated vertical CRS.
		* @param isUpOriented		If true, indicates that the Z offset if an elevation when positive. If false, the Z offset if a depth when positive.
		*/
		resqml2_0_1::LocalTime3dCrs* createLocalTime3dCrs(const std::string & guid, const std::string & title,
			const double & originOrdinal1, const double & originOrdinal2, const double & originOrdinal3,
			const double & arealRotation,
			const gsoap_resqml2_0_1::eml20__LengthUom & projectedUom, const unsigned long & projectedEpsgCode,
			const gsoap_resqml2_0_1::eml20__TimeUom & timeUom,
			const gsoap_resqml2_0_1::eml20__LengthUom & verticalUom, const unsigned int & verticalEpsgCode, const bool & isUpOriented);

		/**
		* Creates a local depth 3d CRS which is fully unknown.
		* @param guid					The guid to set to the local 3d crs. If empty then a new guid will be generated.
		* @param title					A title for the instance to create.
		* @param originOrdinal1			The offset of the global 2d crs on its first axis.
		* @param originOrdinal2			The offset of the global 2d crs on its second axis.
		* @param originOrdinal3			The offset in depth of the local CRS regarding the depth origin of the vertical CRS.
		* @param arealRotation			The areal rotation in radians regarding the projected crs.
		* @param projectedUom			The unit of measure of the projected axis of this instance.
		* @param projectedUnknownReason	Indicates why the projected CRS cannot be provided using EPSG or GML.
		* @param timeUom				The unit of measure of the Z offset of this instance.
		* @param verticalUom			The unit of measure of the vertical axis of this instance.
		* @param verticalUnknownReason	Indicates why the vertical CRS cannot be provided using EPSG or GML.
		* @param isUpOriented			If true, indicates that the Z offset if an elevation when positive. If false, the Z offset if a depth when positive.
		*/
		resqml2_0_1::LocalTime3dCrs* createLocalTime3dCrs(const std::string & guid, const std::string & title,
			const double & originOrdinal1, const double & originOrdinal2, const double & originOrdinal3,
			const double & arealRotation,
			const gsoap_resqml2_0_1::eml20__LengthUom & projectedUom, const std::string & projectedUnknownReason,
			const gsoap_resqml2_0_1::eml20__TimeUom & timeUom,
			const gsoap_resqml2_0_1::eml20__LengthUom & verticalUom, const std::string & verticalUnknownReason, const bool & isUpOriented);

		/**
		* Creates a local depth 3d CRS which is identified by an EPSG code for its projected part and which is unkown for its vertial part.
		* @param guid					The guid to set to the local 3d crs. If empty then a new guid will be generated.
		* @param title					A title for the instance to create.
		* @param originOrdinal1			The offset of the global 2d crs on its first axis.
		* @param originOrdinal2			The offset of the global 2d crs on its second axis.
		* @param originOrdinal3			The offset in depth of the local CRS regarding the depth origin of the vertical CRS.
		* @param arealRotation			The areal rotation in radians regarding the projected crs.
		* @param projectedUom			The unit of measure of the projected axis of this instance.
		* @param timeUom				The unit of measure of the Z offset of this instance.
		* @param projectedEpsgCode		The epsg code of the associated projected CRS.
		* @param verticalUom			The unit of measure of the vertical axis of this instance.
		* @param verticalUnknownReason	Indicates why the vertical CRS cannot be provided using EPSG or GML.
		* @param isUpOriented			If true, indicates that the Z offset if an elevation when positive. If false, the Z offset if a depth when positive.
		*/
		resqml2_0_1::LocalTime3dCrs* createLocalTime3dCrs(const std::string & guid, const std::string & title,
			const double & originOrdinal1, const double & originOrdinal2, const double & originOrdinal3,
			const double & arealRotation,
			const gsoap_resqml2_0_1::eml20__LengthUom & projectedUom, const unsigned long & projectedEpsgCode,
			const gsoap_resqml2_0_1::eml20__TimeUom & timeUom,
			const gsoap_resqml2_0_1::eml20__LengthUom & verticalUom, const std::string & verticalUnknownReason, const bool & isUpOriented);

		/**
		* Creates a local depth 3d CRS which unkown for its projected part and which is identified by an EPSG code for its vertical part.
		* @param guid					The guid to set to the local 3d crs. If empty then a new guid will be generated.
		* @param title					A title for the instance to create.
		* @param originOrdinal1			The offset of the global 2d crs on its first axis.
		* @param originOrdinal2			The offset of the global 2d crs on its second axis.
		* @param originOrdinal3			The offset in depth of the local CRS regarding the depth origin of the vertical CRS.
		* @param arealRotation			The areal rotation in radians regarding the projected crs.
		* @param projectedUom			The unit of measure of the projected axis of this instance.
		* @param projectedUnknownReason	Indicates why the projected CRS cannot be provided using EPSG or GML.
		* @param timeUom				The unit of measure of the Z offset of this instance.
		* @param verticalUom			The unit of measure of the vertical axis of this instance.
		* @param verticalEpsgCode		The epsg code of the associated vertical CRS.
		* @param isUpOriented			If true, indicates that the Z offset if an elevation when positive. If false, the Z offset if a depth when positive.
		*/
		resqml2_0_1::LocalTime3dCrs* createLocalTime3dCrs(const std::string & guid, const std::string & title,
			const double & originOrdinal1, const double & originOrdinal2, const double & originOrdinal3,
			const double & arealRotation,
			const gsoap_resqml2_0_1::eml20__LengthUom & projectedUom, const std::string & projectedUnknownReason,
			const gsoap_resqml2_0_1::eml20__TimeUom & timeUom,
			const gsoap_resqml2_0_1::eml20__LengthUom & verticalUom, const unsigned int & verticalEpsgCode, const bool & isUpOriented);

		resqml2::MdDatum* createMdDatum(const std::string & guid, const std::string & title,
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

		resqml2_0_1::StratigraphicUnitFeature* createStratigraphicUnit(const std::string & guid, const std::string & title);

		resqml2_0_1::OrganizationFeature* createStructuralModel(const std::string & guid, const std::string & title);

		resqml2_0_1::OrganizationFeature* createStratigraphicModel(const std::string & guid, const std::string & title);

        resqml2_0_1::OrganizationFeature* createEarthModel(const std::string & guid, const std::string & title);
		
		resqml2_0_1::FluidBoundaryFeature* createFluidBoundaryFeature(const std::string & guid, const std::string & title, const gsoap_resqml2_0_1::resqml2__FluidContact & fluidContact);

		//************************************
		//************ INTERPRETATION ********
		//************************************

		resqml2_0_1::GenericFeatureInterpretation* createGenericFeatureInterpretation(resqml2::AbstractFeature * feature, const std::string & guid, const std::string & title);
		
		resqml2_0_1::BoundaryFeatureInterpretation* createBoundaryFeatureInterpretation(resqml2_0_1::BoundaryFeature * feature, const std::string & guid, const std::string & title);

		resqml2_0_1::HorizonInterpretation* createPartialHorizonInterpretation(const std::string & guid, const std::string & title);

		resqml2_0_1::HorizonInterpretation* createHorizonInterpretation(resqml2_0_1::Horizon * horizon, const std::string & guid, const std::string & title);

		resqml2_0_1::GeobodyBoundaryInterpretation* createGeobodyBoundaryInterpretation(resqml2_0_1::GeneticBoundaryFeature * geobodyBoundary, const std::string & guid, const std::string & title);

		resqml2_0_1::FaultInterpretation* createFaultInterpretation(resqml2_0_1::TectonicBoundaryFeature * fault, const std::string & guid, const std::string & title);

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

		resqml2_0_1::TriangulatedSetRepresentation* createTriangulatedSetRepresentation(resqml2::AbstractFeatureInterpretation* interp, resqml2::AbstractLocal3dCrs * crs,
			const std::string & guid, const std::string & title);

		resqml2_0_1::PolylineSetRepresentation* createPolylineSetRepresentation(resqml2::AbstractLocal3dCrs * crs,
			const std::string & guid, const std::string & title);

		resqml2_0_1::PolylineSetRepresentation* createPolylineSetRepresentation(resqml2::AbstractFeatureInterpretation* interp, resqml2::AbstractLocal3dCrs * crs,
			const std::string & guid, const std::string & title);

		resqml2_0_1::PolylineSetRepresentation* createPolylineSetRepresentation(resqml2::AbstractFeatureInterpretation* interp, resqml2::AbstractLocal3dCrs * crs,
			const std::string & guid, const std::string & title, const gsoap_resqml2_0_1::resqml2__LineRole & roleKind);

		resqml2_0_1::PointSetRepresentation* createPointSetRepresentation(resqml2::AbstractFeatureInterpretation* interp, resqml2::AbstractLocal3dCrs * crs,
			const std::string & guid, const std::string & title);

		resqml2_0_1::PlaneSetRepresentation* createPlaneSetRepresentation(resqml2::AbstractFeatureInterpretation* interp, resqml2::AbstractLocal3dCrs * crs,
			const std::string & guid, const std::string & title);

		resqml2_0_1::PolylineRepresentation* createPolylineRepresentation(resqml2::AbstractLocal3dCrs * crs,
			const std::string & guid, const std::string & title, bool isClosed = false);

		resqml2_0_1::PolylineRepresentation* createPolylineRepresentation(resqml2::AbstractFeatureInterpretation* interp, resqml2::AbstractLocal3dCrs * crs,
			const std::string & guid, const std::string & title, bool isClosed = false);

		resqml2_0_1::PolylineRepresentation* createPolylineRepresentation(resqml2::AbstractFeatureInterpretation* interp, resqml2::AbstractLocal3dCrs * crs,
			const std::string & guid, const std::string & title, const gsoap_resqml2_0_1::resqml2__LineRole & roleKind, bool isClosed = false);

		resqml2_0_1::Grid2dRepresentation* createGrid2dRepresentation(resqml2::AbstractFeatureInterpretation* interp, resqml2::AbstractLocal3dCrs * crs,
			const std::string & guid, const std::string & title);

		resqml2_0_1::WellboreTrajectoryRepresentation* createWellboreTrajectoryRepresentation(resqml2_0_1::WellboreInterpretation* interp, const std::string & guid, const std::string & title, resqml2::MdDatum * mdInfo);
		resqml2_0_1::WellboreTrajectoryRepresentation* createWellboreTrajectoryRepresentation(resqml2_0_1::WellboreInterpretation* interp, const std::string & guid, const std::string & title, resqml2_0_1::DeviationSurveyRepresentation* deviationSurvey);

		resqml2_0_1::DeviationSurveyRepresentation* createDeviationSurveyRepresentation(resqml2_0_1::WellboreInterpretation* interp, const std::string & guid, const std::string & title, const bool & isFinal, resqml2::MdDatum * mdInfo);

		resqml2_0_1::WellboreFrameRepresentation* createWellboreFrameRepresentation(resqml2_0_1::WellboreInterpretation* interp, const std::string & guid, const std::string & title, resqml2_0_1::WellboreTrajectoryRepresentation * traj);

		resqml2_0_1::WellboreMarkerFrameRepresentation* createWellboreMarkerFrameRepresentation(resqml2_0_1::WellboreInterpretation* interp, const std::string & guid, const std::string & title, resqml2_0_1::WellboreTrajectoryRepresentation * traj);

		resqml2_0_1::BlockedWellboreRepresentation* createBlockedWellboreRepresentation(resqml2_0_1::WellboreInterpretation* interp,
			const std::string & guid, const std::string & title, resqml2_0_1::WellboreTrajectoryRepresentation * traj);

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

		resqml2_0_1::AbstractIjkGridRepresentation* createPartialTruncatedIjkGridRepresentation(const std::string & guid, const std::string & title);

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

		resqml2::GridConnectionSetRepresentation* createPartialGridConnectionSetRepresentation(const std::string & guid, const std::string & title);

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
		//*************** WITSML *************
		//************************************
		
		/**
		* Get all the witsml trajectories contained into the EPC document
		*/
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

		//************************************
		//************ PRODML ****************
		//************************************

		prodml2_0::DasAcquisition* createDasAcquisition(prodml2_0::FiberOpticalPath* fiberOpticalPath, prodml2_0::DasInstrumentBox* dasInstrumentBox,
			const std::string & guid, const std::string & title,
			const std::string & jobGuid, const std::string & facilityId, const std::string & vendorName,
			const double & pulseRate, const gsoap_eml2_1::eml21__FrequencyUom & pulseRateUom,
			const double & pulseWidth, const gsoap_eml2_1::eml21__TimeUom & pulseWidthUom,
			const double & gaugeLength, const gsoap_eml2_1::eml21__LengthUom & gaugeLengthUom,
			const double & spatialSamplingInterval, const gsoap_eml2_1::eml21__LengthUom & spatialSamplingIntervalUom,
			const double & minimumFrequency, const gsoap_eml2_1::eml21__FrequencyUom & minimumFrequencyUom,
			const double & maximumFrequency, const gsoap_eml2_1::eml21__FrequencyUom & maximumFrequencyUom,
			const ULONG64 & lociCount, const ULONG64 & startLocusIndex,
			const std::string & measurementStartIsoTime, bool triggeredMeasurement);

		prodml2_0::FiberOpticalPath* createFiberOpticalPath(const std::string & guid, const std::string & title,
			const std::string & firstSegmentUid, const double & firstSegmentLength, const gsoap_eml2_1::eml21__LengthUom & firstSegmentLengthUom,
			const std::string & terminatorUid, const gsoap_eml2_1::prodml2__TerminationType & terminationType);

		prodml2_0::DasInstrumentBox* createDasInstrumentBox(const std::string & guid, const std::string & title,
			const std::string & firmwareVersion, const std::string & instrumentName);

		//************************************
		//************* WARNINGS *************
		//************************************

		void addWarning(const std::string & warning);
		const std::vector<std::string> & getWarnings() const;

	protected:
		/**
		* Get the error code of the current gsoap context.
		*/
		int getGsoapErrorCode() const;

		/**
		* Get the error message (if any) of the current gsoap context.
		*/
		std::string getGsoapErrorMessage() const;

		/**
		* Set the stream of the curent gsoap context.
		*/
		void setGsoapStream(std::istream * inputStream);

		/**
		* Add a resqml fesapi wrapper into this instance
		*/
		void addFesapiWrapperAndDeleteItIfException(common::AbstractObject* proxy);

		/**
		* Add a witsml fesapi wrapper into this instance
		*/
		void addFesapiWrapperAndDeleteItIfException(witsml1_4_1_1::AbstractObject* proxy);

		/**
		* Read the Gsoap proxy from the stream associated to the current gsoap context and wrap this gsoap proxy into a fesapi wrapper.
		* It does not add this fesapi wrapper to the current instance.
		* It does not work for EpcExternalPartReference content type since this type is related to an external file which must be handled differently.
		*/
		common::AbstractObject* getResqml2_0_1WrapperFromGsoapContext(const std::string & resqmlContentType);

		/**
		* Read the Gsoap proxy from the stream associated to the current gsoap context which must contains an EpcExternalPartReference xml document.
		* It does not add this gsoap proxy to the current instance.
		*/
		gsoap_resqml2_0_1::_eml20__EpcExternalPartReference* getEpcExternalPartReference_2_0_GsoapProxyFromGsoapContext();

		gsoap_eml2_1::_eml21__EpcExternalPartReference* getEpcExternalPartReference_2_1_GsoapProxyFromGsoapContext();

	private :
		static const char * DOCUMENT_EXTENSION;

		openingMode hdf5PermissionAccess;

		epc::Package* package;
#if (defined(_WIN32) && _MSC_VER >= 1600) || defined(__APPLE__)
		std::unordered_map< std::string, common::AbstractObject* > resqmlAbstractObjectSet;
#else
		std::tr1::unordered_map< std::string, common::AbstractObject* > resqmlAbstractObjectSet;
#endif
#if (defined(_WIN32) && _MSC_VER >= 1600) || defined(__APPLE__)
		std::unordered_map< std::string, witsml1_4_1_1::AbstractObject* > witsmlAbstractObjectSet;
#else
		std::tr1::unordered_map< std::string, witsml1_4_1_1::AbstractObject* > witsmlAbstractObjectSet;
#endif
		soap* s;
		std::string filePath;

		// Better for performance reason to have set of important objects instead of having a global vector of GsoapWrapper
		// Even if redundant with resqmlAbstractObjectSet
		std::vector<resqml2_0_1::LocalDepth3dCrs*>					localDepth3dCrsSet;
		std::vector<resqml2_0_1::LocalTime3dCrs*>					localTime3dCrsSet;
		std::vector<resqml2_0_1::TectonicBoundaryFeature*>			faultSet;
		std::vector<resqml2_0_1::TectonicBoundaryFeature*>			fractureSet;
		std::vector<resqml2_0_1::GeneticBoundaryFeature*>			geneticBoundarySet;
		std::vector<resqml2_0_1::GeobodyFeature*>					geobodySet;
		std::vector<resqml2_0_1::SeismicLineFeature*>				seismicLineSet;
		std::vector<common::AbstractHdfProxy*>						hdfProxySet;
		std::vector<resqml2_0_1::WellboreFeature*>					wellboreSet;
		std::vector<resqml2::RepresentationSetRepresentation*>		representationSetRepresentationSet;
		std::vector<witsml1_4_1_1::Trajectory*>						witsmlTrajectorySet;
		std::vector<resqml2_0_1::TriangulatedSetRepresentation*>	triangulatedSetRepresentationSet;
		std::vector<resqml2_0_1::PolylineRepresentation*>			polylineRepresentationSet;
		std::vector<resqml2_0_1::AbstractIjkGridRepresentation*>	ijkGridRepresentationSet;
		std::vector<resqml2_0_1::UnstructuredGridRepresentation*>	unstructuredGridRepresentationSet;
		std::vector<resqml2_0_1::StratigraphicColumn*>				stratigraphicColumnSet;
		std::vector<resqml2_0_1::FrontierFeature*>					frontierSet;
		std::vector<resqml2_0_1::OrganizationFeature*> 				organizationSet;
		std::vector<resqml2::TimeSeries*> 							timeSeriesSet;
		std::vector<resqml2::SubRepresentation*>					subRepresentationSet;
		std::vector<resqml2_0_1::PointSetRepresentation*>			pointSetRepresentationSet;

		resqml2_0_1::PropertyKindMapper* propertyKindMapper;

		std::vector<std::string> warnings;

		HdfProxyBuilder* make_hdf_proxy; /// the builder for HDF proxy in writing mode of the epc document
		HdfProxyBuilderFromGsoapProxy2_0_1* make_hdf_proxy_from_gsoap_proxy_2_0_1; /// the builder for a v2.0.1 HDF proxy in reading mode of the epc document
		HdfProxyBuilderFromGsoapProxy2_1* make_hdf_proxy_from_gsoap_proxy_2_1; /// the builder for a v2.1 HDF proxy in reading mode of the epc document
	};
}



