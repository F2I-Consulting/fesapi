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
#include "proxies/gsoap_eml2_1H.h"
#include "proxies/gsoap_eml2_2H.h"

#include "epc/Package.h"

#include "nsDefinitions.h"

#if (defined(_WIN32) && _MSC_VER < 1600) || (defined(__GNUC__) && (__GNUC__ < 4 || (__GNUC__ == 4 && __GNUC_MINOR__ < 6)))
#include "tools/nullptr_emulation.h"
#endif

#if defined(_WIN32) && !defined(FESAPI_STATIC)
	#if defined(FesapiCpp_EXPORTS) || defined(FesapiCppUnderDev_EXPORTS)
		#define DLL_IMPORT_OR_EXPORT __declspec(dllexport)
	#else
		#define DLL_IMPORT_OR_EXPORT __declspec(dllimport) 
	#endif
#else
	#define DLL_IMPORT_OR_EXPORT
#endif

namespace RESQML2_NS
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

namespace RESQML2_0_1_NS
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
	class SealedVolumeFrameworkRepresentation;
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
	class RockFluidOrganizationInterpretation;
	class RockFluidUnitInterpretation;
	class RockFluidUnitFeature;

}

namespace WITSML2_1_NS
{
	class ToolErrorModel;
	class ToolErrorModelDictionary;
	class ErrorTerm;
	class ErrorTermDictionary;
	class WeightingFunction;
	class WeightingFunctionDictionary;
}

namespace WITSML2_0_NS
{
	class Well;
	class WellCompletion;
	class Wellbore;
	class WellboreCompletion;
	class Trajectory;
}

namespace COMMON_NS
{
	class AbstractObject;
	class AbstractHdfProxy;

	/**
	* This class allows an access to a memory package representing an EPC document.
	*/
	class EpcDocument
	{
	private :

		/**
		* Necessary to avoid a dependency on GuidTools.h
		*/
		std::string generateRandomUuidAsString();
		
	public:

		enum openingMode { READ_ONLY = 0, READ_WRITE = 1, OVERWRITE = 2 };

		DLL_IMPORT_OR_EXPORT EpcDocument(const std::string & fileName, const openingMode & hdf5PermissionAccess = READ_ONLY);
		DLL_IMPORT_OR_EXPORT EpcDocument(const std::string & fileName, const std::string & propertyKindMappingFilesDirectory, const openingMode & hdf5PermissionAccess = READ_ONLY);

		/**
		* The destructor frees all allocated ressources.
		*/
		DLL_IMPORT_OR_EXPORT virtual ~EpcDocument();

		// A function pointer definition which allows to build an abstract hdf proxy in writing mode of an epc document
		typedef COMMON_NS::AbstractHdfProxy* (HdfProxyBuilder)(soap* soapContext, const std::string & guid, const std::string & title, const std::string & packageDirAbsolutePath, const std::string & externalFilePath);
		// A function pointer which allows to build a v2.0.1 abstract hdf proxy in reading mode of an epc document
		typedef COMMON_NS::AbstractHdfProxy* (HdfProxyBuilderFromGsoapProxy2_0_1)(gsoap_resqml2_0_1::_eml20__EpcExternalPartReference* fromGsoap, const std::string & packageDirAbsolutePath, const std::string & externalFilePath);

		// Allows a fesapi user to set a different builder of Hdf Proxy than the default one in writing mode of an epc document
		// This is especially useful when the fesapi users wants to use its own builder for example.
		DLL_IMPORT_OR_EXPORT void set_hdf_proxy_builder(HdfProxyBuilder builder);
		DLL_IMPORT_OR_EXPORT void set_hdf_proxy_builder(HdfProxyBuilderFromGsoapProxy2_0_1 builder);

		/**
		* Open an epc document.
		* If already opened, the epc document must be closed before to open a new one.
		* Don't forget to call close() before to destroy this object.
		*/
		DLL_IMPORT_OR_EXPORT void open(const std::string & fileName, const openingMode & hdf5PermissionAccess = READ_ONLY);
	
		/**
		 * Free all ressources contained in this package.
		 */
		DLL_IMPORT_OR_EXPORT void close();

		DLL_IMPORT_OR_EXPORT const openingMode & getHdf5PermissionAccess() const;

		/**
		 * Set the file path which will be used for future serialization and deserialization
		 * Will add the standard epc extension to the filePath is not already present.
		 */
		DLL_IMPORT_OR_EXPORT void setFilePath(const std::string & filePath);

		/**
		* Serialize the package by serializing all the gsoap wrappers and by zipping the package.
		*/
		DLL_IMPORT_OR_EXPORT virtual void serialize(bool useZip64 = false);

		/**
		* Unzip the package and get all contained elements with their relationships
		* @return			An empty string if everything's ok otherwise the error string.
		*/
		DLL_IMPORT_OR_EXPORT virtual std::string deserialize();

		/**
		* Get the soap context of the epc document.
		*/
		soap* getGsoapContext() const;

		/**
		* Add a gsoap proxy to serialize with the package
		*/
		void addGsoapProxy(COMMON_NS::AbstractObject* proxy);

		/**
		 * Get the property kind mapper of this epc document if given at EPC document construction time.
		 * Else return NULL.
		 */
		DLL_IMPORT_OR_EXPORT RESQML2_0_1_NS::PropertyKindMapper* getPropertyKindMapper() const;

		/**
		* Get the name of the energistics property kind as a string based on the enumerated property kind.
		* @return The empty string if no correspondence is found
		*/
		DLL_IMPORT_OR_EXPORT std::string getEnergisticsPropertyKindName(const gsoap_resqml2_0_1::resqml2__ResqmlPropertyKind & energisticsPropertyKind) const;

		/**
		* Get the Energistics property kind enumerated value from the name (string) of the property kind.
		* @return The most abstract energistics property kind if no correspondance is found with the property kind string/name.
		*/
		DLL_IMPORT_OR_EXPORT gsoap_resqml2_0_1::resqml2__ResqmlPropertyKind getEnergisticsPropertyKind(const std::string & energisticsPropertyKindName) const;

		/**
		* Get the name of the resqml standard property type as a string based on the enumerated property kind.
		* @return The empty string if no correspondence is found
		*/
		DLL_IMPORT_OR_EXPORT std::string getEnergisticsUnitOfMeasureName(const gsoap_resqml2_0_1::resqml2__ResqmlUom & energisticsUom) const;

		/**
		* Get the Energistics unit of measure enumerated value from the name (string) of the uom.
		* @return The Euclidian (no uom) energistics uom if no correspondance is found with the uom string/name.
		*/
		DLL_IMPORT_OR_EXPORT gsoap_resqml2_0_1::resqml2__ResqmlUom getEnergisticsUnitOfMeasure(const std::string & energisticsUomName) const;

		/**
		* Get the name of the resqml facet as a string based on the enumerated facet.
		* @return The empty string if no correspondence is found
		*/
		DLL_IMPORT_OR_EXPORT std::string getFacet(const gsoap_resqml2_0_1::resqml2__Facet & facet) const;

		/**
		* Get the facet enumerated value from the name (string) of the facet.
		* @return The what facet if no correspondance is found with the facet string/name.
		*/
		DLL_IMPORT_OR_EXPORT gsoap_resqml2_0_1::resqml2__Facet getFacet(const std::string & facet) const;

		/**
		* Get the name (string) of the witsml uom as a string based on the enumerated uom.
		* @return The empty string if no correspondence is found
		*/
		DLL_IMPORT_OR_EXPORT std::string lengthUomToString(const gsoap_eml2_1::eml21__LengthUom & witsmlUom) const;

		/**
		* Get the name (string) of the witsml uom as a string based on the enumerated uom.
		* @return The empty string if no correspondence is found
		*/
		DLL_IMPORT_OR_EXPORT std::string verticalCoordinateUomToString(const gsoap_eml2_1::eml21__VerticalCoordinateUom & witsmlUom) const;

		/**
		* Get the name (string) of the witsml uom as a string based on the enumerated uom.
		* @return The empty string if no correspondence is found
		*/
		DLL_IMPORT_OR_EXPORT std::string planeAngleUomToString(const gsoap_eml2_1::eml21__PlaneAngleUom & witsmlUom) const;

		/**
		* Get all the resqml gsoap wrappers from the epc document
		*/
#if (defined(_WIN32) && _MSC_VER >= 1600) || defined(__APPLE__)
		DLL_IMPORT_OR_EXPORT const std::unordered_map< std::string, COMMON_NS::AbstractObject* > & getDataObjectSet() const;
#else
		const std::tr1::unordered_map< std::string, COMMON_NS::AbstractObject* > & getDataObjectSet() const;
#endif

		/**
		* Group Data objects by content type
		* @return A map where the key is a content type and where the value is the collection of Data objects of this content type
		*/
#if (defined(_WIN32) && _MSC_VER >= 1600) || defined(__APPLE__)
		DLL_IMPORT_OR_EXPORT std::unordered_map< std::string, std::vector<COMMON_NS::AbstractObject*> > getDataObjectsGroupedByContentType() const;
#else
		std::tr1::unordered_map< std::string, std::vector<COMMON_NS::AbstractObject*> > getDataObjectsGroupedByContentType() const;
#endif

		/**
		* Get Data objects which honor this content type
		* @return The vector of Data objects in this EPC Document which honor the content type
		*/
		DLL_IMPORT_OR_EXPORT std::vector<COMMON_NS::AbstractObject*> getDataObjectsByContentType(const std::string & contentType) const;

		/**
		* Get RESQML2.0 objects which honor a particular XML tag.
		* All fesapi objects expose publicly a "XML_TAG" static member.
		* It is necessary to build your application with "FESAPI_DLL" definition if you want to acces "XML_TAG" on Windows from a fesapi shared library (not with a static one).
		*
		* @return The vector of RESQML2.0.1 objects in this EPC Document which honor the XML tag
		*/
		DLL_IMPORT_OR_EXPORT std::vector<COMMON_NS::AbstractObject*> getResqml2_0ObjectsByXmlTag(const std::string & xmlTag) const;

		/**
		* Get all data objects of a particular type indicated by means of the template class.
		*
		* @return The vector of data object in this EPC Document 
		*/
		template <class valueType>
		std::vector<valueType*> getDataObjects() const
		{
			std::vector<valueType*> result;

#if (defined(_WIN32) && _MSC_VER >= 1600) || defined(__APPLE__)
			for (std::unordered_map< std::string, COMMON_NS::AbstractObject* >::const_iterator it = dataObjectSet.begin(); it != dataObjectSet.end(); ++it) {
#else
			for (std::tr1::unordered_map< std::string, COMMON_NS::AbstractObject* >::const_iterator it = dataObjectSet.begin(); it != dataObjectSet.end(); ++it) {
#endif
				if (dynamic_cast<valueType*>(it->second) != nullptr) {
					result.push_back(static_cast<valueType*>(it->second));
				}
			}

			return result;
		}

		/**
		* Get all UUIDs of the objects contained in the EPC document
		*/
		DLL_IMPORT_OR_EXPORT std::vector<std::string> getAllUuids() const;

		/**
		* Get the Gsoap type by means of its uuid
		*/
		DLL_IMPORT_OR_EXPORT COMMON_NS::AbstractObject* getDataObjectByUuid(const std::string & uuid, int & gsoapType) const;

		/**
		* Get a gsoap wrapper from the epc document by means of its uuid
		*/
		DLL_IMPORT_OR_EXPORT COMMON_NS::AbstractObject* getDataObjectByUuid(const std::string & uuid) const;

		/**
		* Get a gsoap wrapper from the epc document by means of its uuid
		* and try to cast it to a child class of COMMON_NS::AbstractObject
		*/
		template <class valueType>
		valueType* getDataObjectByUuid(const std::string & uuid) const
		{
			COMMON_NS::AbstractObject* const result = getDataObjectByUuid(uuid);

			if (result == nullptr) {
				return nullptr;
			}

			if (dynamic_cast<valueType*>(result) != nullptr) {
				return static_cast<valueType*>(result);
			}

			throw std::invalid_argument("The uuid " + uuid + " does not resolve to the expected datatype");
		}

		/**
		* Get all the local 3d depth crs contained into the EPC document
		*/
		DLL_IMPORT_OR_EXPORT const std::vector<RESQML2_0_1_NS::LocalDepth3dCrs*> & getLocalDepth3dCrsSet() const;

		/**
		* Get all the local 3d time crs contained into the EPC document
		*/
		DLL_IMPORT_OR_EXPORT const std::vector<RESQML2_0_1_NS::LocalTime3dCrs*> & getLocalTime3dCrsSet() const;

		/**
		* Get all the stratigraphic columns contained into the EPC document
		*/
		DLL_IMPORT_OR_EXPORT const std::vector<RESQML2_0_1_NS::StratigraphicColumn*> & getStratigraphicColumnSet() const;

		/**
		* Get all the faults contained into the EPC document
		*/
		DLL_IMPORT_OR_EXPORT const std::vector<RESQML2_0_1_NS::TectonicBoundaryFeature*> & getFaultSet() const;

		/**
		* Get all the fractures contained into the EPC document
		*/
		DLL_IMPORT_OR_EXPORT const std::vector<RESQML2_0_1_NS::TectonicBoundaryFeature*> & getFractureSet() const;

		/**
		* Get all the individual representations of faults which are associated to a polyline topology
		*/
		DLL_IMPORT_OR_EXPORT std::vector<RESQML2_0_1_NS::PolylineSetRepresentation*> getFaultPolylineSetRepSet() const;

		/**
		* Get all the individual representations of fractures which are associated to a polyline topology
		*/
		DLL_IMPORT_OR_EXPORT std::vector<RESQML2_0_1_NS::PolylineSetRepresentation*> getFracturePolylineSetRepSet() const;

		/**
		* Get all the individual representations of frontiers which are associated to a polyline set topology
		*/
		DLL_IMPORT_OR_EXPORT std::vector<RESQML2_0_1_NS::PolylineSetRepresentation*> getFrontierPolylineSetRepSet() const;

		/**
		* Get all the individual representations of faults which are associated to a triangulation set topology
		*/
		DLL_IMPORT_OR_EXPORT std::vector<RESQML2_0_1_NS::TriangulatedSetRepresentation*> getFaultTriangulatedSetRepSet() const;

        /**
		* Get all the individual representations of fractures which are associated to a triangulation set topology
		*/
		DLL_IMPORT_OR_EXPORT std::vector<RESQML2_0_1_NS::TriangulatedSetRepresentation*> getFractureTriangulatedSetRepSet() const;

		/**
		* Get all the horizons contained into the EPC document
		*/
		DLL_IMPORT_OR_EXPORT std::vector<RESQML2_0_1_NS::Horizon*> getHorizonSet() const;

		/**
		* Get all the geobody boundaries contained into the EPC document
		*/
		DLL_IMPORT_OR_EXPORT std::vector<RESQML2_0_1_NS::GeneticBoundaryFeature*> getGeobodyBoundarySet() const;
		DLL_IMPORT_OR_EXPORT unsigned int getGeobodyBoundaryCount() const;
		DLL_IMPORT_OR_EXPORT RESQML2_0_1_NS::GeneticBoundaryFeature* getGeobodyBoundary(unsigned int index) const;

		/**
		* Get all the geobodies contained into the EPC document
		*/
		DLL_IMPORT_OR_EXPORT const std::vector<RESQML2_0_1_NS::GeobodyFeature*> & getGeobodySet() const;
        
		/**
		* Get all the individual representations of horizons which are associated to grid 2d set topology
		*/
		DLL_IMPORT_OR_EXPORT std::vector<RESQML2_0_1_NS::Grid2dRepresentation*> getHorizonGrid2dRepSet() const;
        
		/**
		* Get all the single polyline representations of all the horizons
		*/
		DLL_IMPORT_OR_EXPORT std::vector<RESQML2_0_1_NS::PolylineRepresentation*> getHorizonPolylineRepSet() const;
        
		/**
		* Get all the single polyline representations of all the horizons
		*/
		DLL_IMPORT_OR_EXPORT std::vector<RESQML2_0_1_NS::PolylineSetRepresentation*> getHorizonPolylineSetRepSet() const;
        
        /**
		* Get all the triangulated set representations of all the horizons
		*/
		DLL_IMPORT_OR_EXPORT std::vector<RESQML2_0_1_NS::TriangulatedSetRepresentation*> getHorizonTriangulatedSetRepSet() const;

		/**
		* Get all the triangulated set representations of the EPC document
		*/
		DLL_IMPORT_OR_EXPORT const std::vector<RESQML2_0_1_NS::TriangulatedSetRepresentation*> & getAllTriangulatedSetRepSet() const;

		/**
		* Get all the grid 2d representations of the EPC document
		*/
		DLL_IMPORT_OR_EXPORT const std::vector<RESQML2_0_1_NS::Grid2dRepresentation*> & getAllGrid2dRepresentationSet() const;

		/**
		* Get all the polyline set representations of the EPC document
		*/
		DLL_IMPORT_OR_EXPORT const std::vector<RESQML2_0_1_NS::PolylineSetRepresentation*> & getAllPolylineSetRepSet() const;

		/**
		* Get all the triangulated set representations of the EPC document which are not horizon and fault neither.
		*/
		DLL_IMPORT_OR_EXPORT std::vector<RESQML2_0_1_NS::TriangulatedSetRepresentation*> getUnclassifiedTriangulatedSetRepSet() const;

		/**
		* Get all the seismic line contained into the EPC document
		*/
		DLL_IMPORT_OR_EXPORT const std::vector<RESQML2_0_1_NS::SeismicLineFeature*> & getSeismicLineSet() const;

		/**
		* Get all the wellbores contained into the EPC document
		*/
		DLL_IMPORT_OR_EXPORT const std::vector<RESQML2_0_1_NS::WellboreFeature*> & getWellboreSet() const;

		/**
		* Get all the trajectory representations of all wellbores.
		*/
		DLL_IMPORT_OR_EXPORT std::vector<RESQML2_0_1_NS::WellboreTrajectoryRepresentation*> getWellboreTrajectoryRepresentationSet() const;

		/**
		* Get all the devaition survey of all wellbores.
		*/
		DLL_IMPORT_OR_EXPORT std::vector<RESQML2_0_1_NS::DeviationSurveyRepresentation*> getDeviationSurveyRepresentationSet() const;

		/**
		* Get all the representationset representations contained into the EPC document
		*/
		DLL_IMPORT_OR_EXPORT const std::vector<RESQML2_NS::RepresentationSetRepresentation*> & getRepresentationSetRepresentationSet() const;

		/**
		* Get the representationset representations count of this EPC document
		*/
		DLL_IMPORT_OR_EXPORT unsigned int getRepresentationSetRepresentationCount() const;

		/**
		* Get the representationset representations at a particular index of this EPC document
		*/
		DLL_IMPORT_OR_EXPORT RESQML2_NS::RepresentationSetRepresentation* getRepresentationSetRepresentation(const unsigned int & index) const;

		/**
		* Get all the polyline representations contained into the EPC document.
		*/
		DLL_IMPORT_OR_EXPORT const std::vector<RESQML2_0_1_NS::PolylineRepresentation*> & getAllPolylineRepresentationSet() const;

		/**
		* Get all the single polyline representations contained into the EPC document which correspond to a seismic line.
		*/
		DLL_IMPORT_OR_EXPORT std::vector<RESQML2_0_1_NS::PolylineRepresentation*> getSeismicLinePolylineRepSet() const;

		/**
		* Get all the ijk grid contained into the EPC document.
		*/
		DLL_IMPORT_OR_EXPORT const std::vector<RESQML2_0_1_NS::AbstractIjkGridRepresentation*> & getIjkGridRepresentationSet() const;
		DLL_IMPORT_OR_EXPORT unsigned int getIjkGridRepresentationCount() const;
		DLL_IMPORT_OR_EXPORT RESQML2_0_1_NS::AbstractIjkGridRepresentation* getIjkGridRepresentation(const unsigned int & i) const;

		/**
		* Get all the ijk grid contained into the EPC document which have a parametric geometry.
		*/
		DLL_IMPORT_OR_EXPORT std::vector<RESQML2_0_1_NS::IjkGridParametricRepresentation*> getIjkGridParametricRepresentationSet() const;

		/**
		* Get all the ijk grid contained into the EPC document which have an explicit geometry.
		*/
		DLL_IMPORT_OR_EXPORT std::vector<RESQML2_0_1_NS::IjkGridExplicitRepresentation*> getIjkGridExplicitRepresentationSet() const;

		/**
		* Get all the ijk grid contained into the EPC document which correspond to a seismic cube.
		*/
		DLL_IMPORT_OR_EXPORT std::vector<RESQML2_0_1_NS::IjkGridLatticeRepresentation*> getIjkSeismicCubeGridRepresentationSet() const;

		/**
		* Get all the unstructured grid contained into the EPC document
		*/
		DLL_IMPORT_OR_EXPORT const std::vector<RESQML2_0_1_NS::UnstructuredGridRepresentation*> & getUnstructuredGridRepresentationSet() const;

		/**
		* Get all the frontier features contained into the EPC document
		*/
		DLL_IMPORT_OR_EXPORT const std::vector<RESQML2_0_1_NS::FrontierFeature*> & getFrontierSet() const;

		/**
		 * Get all the organization features contained into the EPC document
		 */
		DLL_IMPORT_OR_EXPORT const std::vector<RESQML2_0_1_NS::OrganizationFeature*> & getOrganizationSet() const;

		/**
		 * Get all the time series contained into the EPC document
		 */
		DLL_IMPORT_OR_EXPORT const std::vector<RESQML2_NS::TimeSeries*> & getTimeSeriesSet() const;

		/**
		 * Get all the subrepresentations contained into the EPC document
		 */
		DLL_IMPORT_OR_EXPORT const std::vector<RESQML2_NS::SubRepresentation*> & getSubRepresentationSet() const;
		DLL_IMPORT_OR_EXPORT unsigned int getSubRepresentationCount() const;
		DLL_IMPORT_OR_EXPORT RESQML2_NS::SubRepresentation* getSubRepresentation(const unsigned int & index) const;

		/**
		* Get all the point set representations contained into the EPC document
		*/
		DLL_IMPORT_OR_EXPORT const std::vector<RESQML2_0_1_NS::PointSetRepresentation*> & getPointSetRepresentationSet() const;
		DLL_IMPORT_OR_EXPORT unsigned int getPointSetRepresentationCount() const;
		DLL_IMPORT_OR_EXPORT RESQML2_0_1_NS::PointSetRepresentation* getPointSetRepresentation(const unsigned int & index) const;

		/**
		* Get all the Hdf proxies used with this EPC document
		*/
		DLL_IMPORT_OR_EXPORT const std::vector<COMMON_NS::AbstractHdfProxy*> & getHdfProxySet() const;
		DLL_IMPORT_OR_EXPORT unsigned int getHdfProxyCount() const;
		DLL_IMPORT_OR_EXPORT COMMON_NS::AbstractHdfProxy* getHdfProxy(const unsigned int & index) const;

		/**
		* Get the absolute path of the directory where the epc document is stored.
		*/
		DLL_IMPORT_OR_EXPORT std::string getStorageDirectory() const;

		/**
		* Get the name of the epc document.
		*/
		DLL_IMPORT_OR_EXPORT std::string getName() const;

		/**
		* Try to resolve in memory all the relationshsips which are serialized into Resqml objects of the EPC document
		*/
		void updateAllRelationships();

#if (defined(_WIN32) && _MSC_VER >= 1600) || defined(__APPLE__)
		DLL_IMPORT_OR_EXPORT std::unordered_map< std::string, std::string > & getExtendedCoreProperty();
#else
		std::tr1::unordered_map< std::string, std::string > & getExtendedCoreProperty();
#endif

		DLL_IMPORT_OR_EXPORT void setExtendedCoreProperty(const std::string & key, const std::string & value);

		/**
		* Get an extended core property value according its key.
		* @return An empty string if the extended core property does not exist. Or the extended core property value if it exists
		*/
		DLL_IMPORT_OR_EXPORT std::string getExtendedCoreProperty(const std::string & key);

		/**
		* Create a partial object in this EpcDocument based on a Data Object Reference
		*/
		COMMON_NS::AbstractObject* createPartial(gsoap_resqml2_0_1::eml20__DataObjectReference* dor);
		COMMON_NS::AbstractObject* createPartial(gsoap_eml2_1::eml21__DataObjectReference* dor);

		/**
		* Create a partial object i.e. a data object reference (DOR)
		*/
		template <class valueType>
		valueType* createPartial(const std::string & guid, const std::string & title)
		{
			gsoap_resqml2_0_1::eml20__DataObjectReference* dor = gsoap_resqml2_0_1::soap_new_eml20__DataObjectReference(s, 1);
			dor->UUID = guid.empty() ? generateRandomUuidAsString() : guid;
			dor->Title = title;
			valueType* result = new valueType(dor);
			addFesapiWrapperAndDeleteItIfException(result);
			return result;
		}

		//************************************
		//************ HDF *******************
		//************************************

		DLL_IMPORT_OR_EXPORT virtual COMMON_NS::AbstractHdfProxy* createHdfProxy(const std::string & guid, const std::string & title, const std::string & packageDirAbsolutePath, const std::string & externalFilePath);

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
		DLL_IMPORT_OR_EXPORT RESQML2_0_1_NS::LocalDepth3dCrs* createLocalDepth3dCrs(const std::string & guid, const std::string & title,
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
		DLL_IMPORT_OR_EXPORT RESQML2_0_1_NS::LocalDepth3dCrs* createLocalDepth3dCrs(const std::string & guid, const std::string & title,
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
		DLL_IMPORT_OR_EXPORT RESQML2_0_1_NS::LocalDepth3dCrs* createLocalDepth3dCrs(const std::string & guid, const std::string & title,
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
		DLL_IMPORT_OR_EXPORT RESQML2_0_1_NS::LocalDepth3dCrs* createLocalDepth3dCrs(const std::string & guid, const std::string & title,
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
		DLL_IMPORT_OR_EXPORT RESQML2_0_1_NS::LocalTime3dCrs* createLocalTime3dCrs(const std::string & guid, const std::string & title,
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
		DLL_IMPORT_OR_EXPORT RESQML2_0_1_NS::LocalTime3dCrs* createLocalTime3dCrs(const std::string & guid, const std::string & title,
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
		DLL_IMPORT_OR_EXPORT RESQML2_0_1_NS::LocalTime3dCrs* createLocalTime3dCrs(const std::string & guid, const std::string & title,
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
		DLL_IMPORT_OR_EXPORT RESQML2_0_1_NS::LocalTime3dCrs* createLocalTime3dCrs(const std::string & guid, const std::string & title,
			const double & originOrdinal1, const double & originOrdinal2, const double & originOrdinal3,
			const double & arealRotation,
			const gsoap_resqml2_0_1::eml20__LengthUom & projectedUom, const std::string & projectedUnknownReason,
			const gsoap_resqml2_0_1::eml20__TimeUom & timeUom,
			const gsoap_resqml2_0_1::eml20__LengthUom & verticalUom, const unsigned int & verticalEpsgCode, const bool & isUpOriented);

		DLL_IMPORT_OR_EXPORT RESQML2_NS::MdDatum* createMdDatum(const std::string & guid, const std::string & title,
			RESQML2_NS::AbstractLocal3dCrs * locCrs, const gsoap_resqml2_0_1::resqml2__MdReference & originKind,
			const double & referenceLocationOrdinal1, const double & referenceLocationOrdinal2, const double & referenceLocationOrdinal3);

		//************************************
		//************ FEATURE ***************
		//************************************

		DLL_IMPORT_OR_EXPORT RESQML2_0_1_NS::BoundaryFeature* createBoundaryFeature(const std::string & guid, const std::string & title);

		DLL_IMPORT_OR_EXPORT RESQML2_0_1_NS::Horizon* createHorizon(const std::string & guid, const std::string & title);

		DLL_IMPORT_OR_EXPORT RESQML2_0_1_NS::GeneticBoundaryFeature* createGeobodyBoundaryFeature(const std::string & guid, const std::string & title);

		DLL_IMPORT_OR_EXPORT RESQML2_0_1_NS::GeobodyFeature* createGeobodyFeature(const std::string & guid, const std::string & title);

		DLL_IMPORT_OR_EXPORT RESQML2_0_1_NS::TectonicBoundaryFeature* createFault(const std::string & guid, const std::string & title);

		DLL_IMPORT_OR_EXPORT RESQML2_0_1_NS::TectonicBoundaryFeature* createFracture(const std::string & guid, const std::string & title);

		DLL_IMPORT_OR_EXPORT RESQML2_0_1_NS::WellboreFeature* createWellboreFeature(const std::string & guid, const std::string & title);

		DLL_IMPORT_OR_EXPORT RESQML2_0_1_NS::SeismicLatticeFeature* createSeismicLattice(const std::string & guid, const std::string & title,
			const int & inlineIncrement, const int & crosslineIncrement,
			const unsigned int & originInline, const unsigned int & originCrossline,
			const unsigned int & inlineCount, const unsigned int & crosslineCount);

		DLL_IMPORT_OR_EXPORT RESQML2_0_1_NS::SeismicLineFeature* createSeismicLine(const std::string & guid, const std::string & title,
			const int & traceIndexIncrement, const unsigned int & firstTraceIndex, const unsigned int & traceCount);

		DLL_IMPORT_OR_EXPORT RESQML2_0_1_NS::SeismicLineSetFeature* createSeismicLineSet(const std::string & guid, const std::string & title);

		DLL_IMPORT_OR_EXPORT RESQML2_0_1_NS::FrontierFeature* createFrontier(const std::string & guid, const std::string & title);

		DLL_IMPORT_OR_EXPORT RESQML2_0_1_NS::StratigraphicUnitFeature* createStratigraphicUnit(const std::string & guid, const std::string & title);

		DLL_IMPORT_OR_EXPORT RESQML2_0_1_NS::OrganizationFeature* createStructuralModel(const std::string & guid, const std::string & title);

		DLL_IMPORT_OR_EXPORT RESQML2_0_1_NS::OrganizationFeature* createStratigraphicModel(const std::string & guid, const std::string & title);

		DLL_IMPORT_OR_EXPORT RESQML2_0_1_NS::OrganizationFeature* createRockFluidModel(const std::string & guid, const std::string & title);

		DLL_IMPORT_OR_EXPORT RESQML2_0_1_NS::OrganizationFeature* createEarthModel(const std::string & guid, const std::string & title);
		
		DLL_IMPORT_OR_EXPORT RESQML2_0_1_NS::FluidBoundaryFeature* createFluidBoundaryFeature(const std::string & guid, const std::string & title, const gsoap_resqml2_0_1::resqml2__FluidContact & fluidContact);

		DLL_IMPORT_OR_EXPORT RESQML2_0_1_NS::RockFluidUnitFeature* createRockFluidUnit(const std::string & guid, const std::string & title, gsoap_resqml2_0_1::resqml2__Phase phase, RESQML2_0_1_NS::FluidBoundaryFeature* fluidBoundaryTop, RESQML2_0_1_NS::FluidBoundaryFeature* fluidBoundaryBottom);


		//************************************
		//************ INTERPRETATION ********
		//************************************

		DLL_IMPORT_OR_EXPORT RESQML2_0_1_NS::GenericFeatureInterpretation* createGenericFeatureInterpretation(RESQML2_NS::AbstractFeature * feature, const std::string & guid, const std::string & title);
		
		DLL_IMPORT_OR_EXPORT RESQML2_0_1_NS::BoundaryFeatureInterpretation* createBoundaryFeatureInterpretation(RESQML2_0_1_NS::BoundaryFeature * feature, const std::string & guid, const std::string & title);

		DLL_IMPORT_OR_EXPORT RESQML2_0_1_NS::HorizonInterpretation* createPartialHorizonInterpretation(const std::string & guid, const std::string & title);

		DLL_IMPORT_OR_EXPORT RESQML2_0_1_NS::HorizonInterpretation* createHorizonInterpretation(RESQML2_0_1_NS::Horizon * horizon, const std::string & guid, const std::string & title);

		DLL_IMPORT_OR_EXPORT RESQML2_0_1_NS::GeobodyBoundaryInterpretation* createGeobodyBoundaryInterpretation(RESQML2_0_1_NS::GeneticBoundaryFeature * geobodyBoundary, const std::string & guid, const std::string & title);

		DLL_IMPORT_OR_EXPORT RESQML2_0_1_NS::FaultInterpretation* createFaultInterpretation(RESQML2_0_1_NS::TectonicBoundaryFeature * fault, const std::string & guid, const std::string & title);

		DLL_IMPORT_OR_EXPORT RESQML2_0_1_NS::WellboreInterpretation* createWellboreInterpretation(RESQML2_0_1_NS::WellboreFeature * wellbore, const std::string & guid, const std::string & title, bool isDrilled);
                
		DLL_IMPORT_OR_EXPORT RESQML2_0_1_NS::EarthModelInterpretation* createEarthModelInterpretation(RESQML2_0_1_NS::OrganizationFeature * orgFeat, const std::string & guid, const std::string & title);
		
		DLL_IMPORT_OR_EXPORT RESQML2_0_1_NS::StructuralOrganizationInterpretation* createStructuralOrganizationInterpretationInAge(RESQML2_0_1_NS::OrganizationFeature * orgFeat, const std::string & guid, const std::string & title);
		DLL_IMPORT_OR_EXPORT RESQML2_0_1_NS::StructuralOrganizationInterpretation* createStructuralOrganizationInterpretationInApparentDepth(RESQML2_0_1_NS::OrganizationFeature * orgFeat, const std::string & guid, const std::string & title);
		DLL_IMPORT_OR_EXPORT RESQML2_0_1_NS::StructuralOrganizationInterpretation* createStructuralOrganizationInterpretationInMeasuredDepth(RESQML2_0_1_NS::OrganizationFeature * orgFeat, const std::string & guid, const std::string & title);
		
		DLL_IMPORT_OR_EXPORT RESQML2_0_1_NS::RockFluidOrganizationInterpretation* createRockFluidOrganizationInterpretation(RESQML2_0_1_NS::OrganizationFeature * orgFeat, const std::string & guid, const std::string & title, RESQML2_0_1_NS::RockFluidUnitInterpretation * rockFluidUnitInterp);
		DLL_IMPORT_OR_EXPORT RESQML2_0_1_NS::RockFluidUnitInterpretation* createRockFluidUnitInterpretation(RESQML2_0_1_NS::RockFluidUnitFeature * rockFluidUnitFeature, const std::string & guid, const std::string & title);

		DLL_IMPORT_OR_EXPORT RESQML2_0_1_NS::GeobodyInterpretation* createGeobodyInterpretation(RESQML2_0_1_NS::GeobodyFeature * geobody, const std::string & guid, const std::string & title);

		DLL_IMPORT_OR_EXPORT RESQML2_0_1_NS::StratigraphicUnitInterpretation* createStratigraphicUnitInterpretation(RESQML2_0_1_NS::StratigraphicUnitFeature * stratiUnitFeature, const std::string & guid, const std::string & title);
		DLL_IMPORT_OR_EXPORT RESQML2_0_1_NS::StratigraphicColumn* createStratigraphicColumn(const std::string & guid, const std::string & title);
		DLL_IMPORT_OR_EXPORT RESQML2_0_1_NS::StratigraphicColumnRankInterpretation* createStratigraphicColumnRankInterpretationInAge(RESQML2_0_1_NS::OrganizationFeature * orgFeat, const std::string & guid, const std::string & title, const unsigned long & rank);
		DLL_IMPORT_OR_EXPORT RESQML2_0_1_NS::StratigraphicColumnRankInterpretation* createStratigraphicColumnRankInterpretationInApparentDepth(RESQML2_0_1_NS::OrganizationFeature * orgFeat, const std::string & guid, const std::string & title, const unsigned long & rank);
		DLL_IMPORT_OR_EXPORT RESQML2_0_1_NS::StratigraphicOccurrenceInterpretation* createStratigraphicOccurrenceInterpretationInAge(RESQML2_0_1_NS::OrganizationFeature * orgFeat, const std::string & guid, const std::string & title);
		DLL_IMPORT_OR_EXPORT RESQML2_0_1_NS::StratigraphicOccurrenceInterpretation* createStratigraphicOccurrenceInterpretationInApparentDepth(RESQML2_0_1_NS::OrganizationFeature * orgFeat, const std::string & guid, const std::string & title);

		//************************************
		//************ REPRESENTATION ********
		//************************************

		DLL_IMPORT_OR_EXPORT RESQML2_0_1_NS::TriangulatedSetRepresentation* createTriangulatedSetRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp, RESQML2_NS::AbstractLocal3dCrs * crs,
			const std::string & guid, const std::string & title);

		DLL_IMPORT_OR_EXPORT RESQML2_0_1_NS::PolylineSetRepresentation* createPolylineSetRepresentation(RESQML2_NS::AbstractLocal3dCrs * crs,
			const std::string & guid, const std::string & title);

		DLL_IMPORT_OR_EXPORT RESQML2_0_1_NS::PolylineSetRepresentation* createPolylineSetRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp, RESQML2_NS::AbstractLocal3dCrs * crs,
			const std::string & guid, const std::string & title);

		DLL_IMPORT_OR_EXPORT RESQML2_0_1_NS::PolylineSetRepresentation* createPolylineSetRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp, RESQML2_NS::AbstractLocal3dCrs * crs,
			const std::string & guid, const std::string & title, const gsoap_resqml2_0_1::resqml2__LineRole & roleKind);

		DLL_IMPORT_OR_EXPORT RESQML2_0_1_NS::PointSetRepresentation* createPointSetRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp, RESQML2_NS::AbstractLocal3dCrs * crs,
			const std::string & guid, const std::string & title);

		DLL_IMPORT_OR_EXPORT RESQML2_0_1_NS::PlaneSetRepresentation* createPlaneSetRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp, RESQML2_NS::AbstractLocal3dCrs * crs,
			const std::string & guid, const std::string & title);

		DLL_IMPORT_OR_EXPORT RESQML2_0_1_NS::PolylineRepresentation* createPolylineRepresentation(RESQML2_NS::AbstractLocal3dCrs * crs,
			const std::string & guid, const std::string & title, bool isClosed = false);

		DLL_IMPORT_OR_EXPORT RESQML2_0_1_NS::PolylineRepresentation* createPolylineRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp, RESQML2_NS::AbstractLocal3dCrs * crs,
			const std::string & guid, const std::string & title, bool isClosed = false);

		DLL_IMPORT_OR_EXPORT RESQML2_0_1_NS::PolylineRepresentation* createPolylineRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp, RESQML2_NS::AbstractLocal3dCrs * crs,
			const std::string & guid, const std::string & title, const gsoap_resqml2_0_1::resqml2__LineRole & roleKind, bool isClosed = false);

		DLL_IMPORT_OR_EXPORT RESQML2_0_1_NS::Grid2dRepresentation* createGrid2dRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp, RESQML2_NS::AbstractLocal3dCrs * crs,
			const std::string & guid, const std::string & title);

		DLL_IMPORT_OR_EXPORT RESQML2_0_1_NS::WellboreTrajectoryRepresentation* createWellboreTrajectoryRepresentation(RESQML2_0_1_NS::WellboreInterpretation* interp, const std::string & guid, const std::string & title, RESQML2_NS::MdDatum * mdInfo);
		DLL_IMPORT_OR_EXPORT RESQML2_0_1_NS::WellboreTrajectoryRepresentation* createWellboreTrajectoryRepresentation(RESQML2_0_1_NS::WellboreInterpretation* interp, const std::string & guid, const std::string & title, RESQML2_0_1_NS::DeviationSurveyRepresentation* deviationSurvey);

		DLL_IMPORT_OR_EXPORT RESQML2_0_1_NS::DeviationSurveyRepresentation* createDeviationSurveyRepresentation(RESQML2_0_1_NS::WellboreInterpretation* interp, const std::string & guid, const std::string & title, const bool & isFinal, RESQML2_NS::MdDatum * mdInfo);

		DLL_IMPORT_OR_EXPORT RESQML2_0_1_NS::WellboreFrameRepresentation* createWellboreFrameRepresentation(RESQML2_0_1_NS::WellboreInterpretation* interp, const std::string & guid, const std::string & title, RESQML2_0_1_NS::WellboreTrajectoryRepresentation * traj);

		DLL_IMPORT_OR_EXPORT RESQML2_0_1_NS::WellboreMarkerFrameRepresentation* createWellboreMarkerFrameRepresentation(RESQML2_0_1_NS::WellboreInterpretation* interp, const std::string & guid, const std::string & title, RESQML2_0_1_NS::WellboreTrajectoryRepresentation * traj);

		DLL_IMPORT_OR_EXPORT RESQML2_0_1_NS::BlockedWellboreRepresentation* createBlockedWellboreRepresentation(RESQML2_0_1_NS::WellboreInterpretation* interp,
			const std::string & guid, const std::string & title, RESQML2_0_1_NS::WellboreTrajectoryRepresentation * traj);

		DLL_IMPORT_OR_EXPORT RESQML2_NS::RepresentationSetRepresentation* createRepresentationSetRepresentation(
                RESQML2_0_1_NS::AbstractOrganizationInterpretation* interp,
                const std::string & guid,
				const std::string & title);

		DLL_IMPORT_OR_EXPORT RESQML2_NS::RepresentationSetRepresentation* createRepresentationSetRepresentation(
			const std::string & guid,
			const std::string & title);

		DLL_IMPORT_OR_EXPORT RESQML2_NS::RepresentationSetRepresentation* createPartialRepresentationSetRepresentation(const std::string & guid, const std::string & title);
                
		DLL_IMPORT_OR_EXPORT RESQML2_0_1_NS::NonSealedSurfaceFrameworkRepresentation* createNonSealedSurfaceFrameworkRepresentation(
                RESQML2_0_1_NS::StructuralOrganizationInterpretation* interp, 
                const std::string & guid, 
                const std::string & title);

		DLL_IMPORT_OR_EXPORT RESQML2_0_1_NS::SealedSurfaceFrameworkRepresentation* createSealedSurfaceFrameworkRepresentation(
                RESQML2_0_1_NS::StructuralOrganizationInterpretation* interp,
                const std::string & guid,
                const std::string & title);

		DLL_IMPORT_OR_EXPORT RESQML2_0_1_NS::SealedVolumeFrameworkRepresentation* createSealedVolumeFrameworkRepresentation(
			RESQML2_0_1_NS::StratigraphicColumnRankInterpretation* interp,
			const std::string & guid,
			const std::string & title,
			RESQML2_0_1_NS::SealedSurfaceFrameworkRepresentation* ssf);

		DLL_IMPORT_OR_EXPORT RESQML2_0_1_NS::AbstractIjkGridRepresentation* createPartialIjkGridRepresentation(const std::string & guid, const std::string & title);

		DLL_IMPORT_OR_EXPORT RESQML2_0_1_NS::AbstractIjkGridRepresentation* createPartialTruncatedIjkGridRepresentation(const std::string & guid, const std::string & title);

		DLL_IMPORT_OR_EXPORT RESQML2_0_1_NS::IjkGridExplicitRepresentation* createIjkGridExplicitRepresentation(RESQML2_NS::AbstractLocal3dCrs * crs,
			const std::string & guid, const std::string & title,
			const unsigned int & iCount, const unsigned int & jCount, const unsigned int & kCount);

		DLL_IMPORT_OR_EXPORT RESQML2_0_1_NS::IjkGridExplicitRepresentation* createIjkGridExplicitRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp, RESQML2_NS::AbstractLocal3dCrs * crs,
			const std::string & guid, const std::string & title,
			const unsigned int & iCount, const unsigned int & jCount, const unsigned int & kCount);

		DLL_IMPORT_OR_EXPORT RESQML2_0_1_NS::IjkGridParametricRepresentation* createIjkGridParametricRepresentation(RESQML2_NS::AbstractLocal3dCrs * crs,
			const std::string & guid, const std::string & title,
			const unsigned int & iCount, const unsigned int & jCount, const unsigned int & kCount);

		DLL_IMPORT_OR_EXPORT RESQML2_0_1_NS::IjkGridParametricRepresentation* createIjkGridParametricRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp, RESQML2_NS::AbstractLocal3dCrs * crs,
			const std::string & guid, const std::string & title,
			const unsigned int & iCount, const unsigned int & jCount, const unsigned int & kCount);

		DLL_IMPORT_OR_EXPORT RESQML2_0_1_NS::IjkGridLatticeRepresentation* createIjkGridLatticeRepresentation(RESQML2_NS::AbstractLocal3dCrs * crs,
			const std::string & guid, const std::string & title,
			const unsigned int & iCount, const unsigned int & jCount, const unsigned int & kCount);

		DLL_IMPORT_OR_EXPORT RESQML2_0_1_NS::IjkGridLatticeRepresentation* createIjkGridLatticeRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp, RESQML2_NS::AbstractLocal3dCrs * crs,
			const std::string & guid, const std::string & title,
			const unsigned int & iCount, const unsigned int & jCount, const unsigned int & kCount);

		DLL_IMPORT_OR_EXPORT RESQML2_0_1_NS::IjkGridNoGeometryRepresentation* createIjkGridNoGeometryRepresentation(
			const std::string & guid, const std::string & title,
			const unsigned int & iCount, const unsigned int & jCount, const unsigned int & kCount);

		DLL_IMPORT_OR_EXPORT RESQML2_0_1_NS::IjkGridNoGeometryRepresentation* createIjkGridNoGeometryRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp,
			const std::string & guid, const std::string & title,
			const unsigned int & iCount, const unsigned int & jCount, const unsigned int & kCount);

		DLL_IMPORT_OR_EXPORT RESQML2_0_1_NS::UnstructuredGridRepresentation* createPartialUnstructuredGridRepresentation(const std::string & guid, const std::string & title);

		DLL_IMPORT_OR_EXPORT RESQML2_0_1_NS::UnstructuredGridRepresentation* createUnstructuredGridRepresentation(RESQML2_NS::AbstractLocal3dCrs * crs,
			const std::string & guid, const std::string & title,
			const ULONG64 & cellCount);

		DLL_IMPORT_OR_EXPORT RESQML2_NS::SubRepresentation* createPartialSubRepresentation(const std::string & guid, const std::string & title);

		DLL_IMPORT_OR_EXPORT RESQML2_NS::SubRepresentation* createSubRepresentation(
                const std::string & guid, const std::string & title);

		DLL_IMPORT_OR_EXPORT RESQML2_NS::SubRepresentation* createSubRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp,
                const std::string & guid, const std::string & title);

		DLL_IMPORT_OR_EXPORT RESQML2_NS::GridConnectionSetRepresentation* createPartialGridConnectionSetRepresentation(const std::string & guid, const std::string & title);

		DLL_IMPORT_OR_EXPORT RESQML2_NS::GridConnectionSetRepresentation* createGridConnectionSetRepresentation(const std::string & guid, const std::string & title);

		DLL_IMPORT_OR_EXPORT RESQML2_NS::GridConnectionSetRepresentation* createGridConnectionSetRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp,
                const std::string & guid, const std::string & title);

		//************************************
		//************* PROPERTIES ***********
		//************************************

		DLL_IMPORT_OR_EXPORT RESQML2_NS::TimeSeries* createTimeSeries(const std::string & guid, const std::string & title);

		DLL_IMPORT_OR_EXPORT RESQML2_NS::TimeSeries* createPartialTimeSeries(const std::string & guid, const std::string & title);

		DLL_IMPORT_OR_EXPORT RESQML2_0_1_NS::StringTableLookup* createStringTableLookup(const std::string & guid, const std::string & title);

		DLL_IMPORT_OR_EXPORT RESQML2_NS::PropertyKind* createPropertyKind(const std::string & guid, const std::string & title,
			const std::string & namingSystem, const gsoap_resqml2_0_1::resqml2__ResqmlUom & uom, const gsoap_resqml2_0_1::resqml2__ResqmlPropertyKind & parentEnergisticsPropertyKind);

		DLL_IMPORT_OR_EXPORT RESQML2_NS::PropertyKind* createPropertyKind(const std::string & guid, const std::string & title,
			const std::string & namingSystem, const gsoap_resqml2_0_1::resqml2__ResqmlUom & uom, RESQML2_NS::PropertyKind * parentPropType);

		DLL_IMPORT_OR_EXPORT RESQML2_NS::PropertyKind* createPropertyKind(const std::string & guid, const std::string & title,
			const std::string & namingSystem, const std::string & nonStandardUom, const gsoap_resqml2_0_1::resqml2__ResqmlPropertyKind & parentEnergisticsPropertyKind);

		DLL_IMPORT_OR_EXPORT RESQML2_NS::PropertyKind* createPropertyKind(const std::string & guid, const std::string & title,
			const std::string & namingSystem, const std::string & nonStandardUom, RESQML2_NS::PropertyKind * parentPropType);

		DLL_IMPORT_OR_EXPORT RESQML2_NS::PropertyKind* createPartialPropertyKind(const std::string & guid, const std::string & title);

		DLL_IMPORT_OR_EXPORT RESQML2_0_1_NS::CommentProperty* createCommentProperty(RESQML2_NS::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			const unsigned int & dimension, const gsoap_resqml2_0_1::resqml2__IndexableElements & attachmentKind, const gsoap_resqml2_0_1::resqml2__ResqmlPropertyKind & energisticsPropertyKind);

		DLL_IMPORT_OR_EXPORT RESQML2_0_1_NS::CommentProperty* createCommentProperty(RESQML2_NS::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			const unsigned int & dimension, const gsoap_resqml2_0_1::resqml2__IndexableElements & attachmentKind, RESQML2_NS::PropertyKind * localPropType);
	
		DLL_IMPORT_OR_EXPORT RESQML2_0_1_NS::ContinuousProperty* createContinuousProperty(RESQML2_NS::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			const unsigned int & dimension, const gsoap_resqml2_0_1::resqml2__IndexableElements & attachmentKind, const gsoap_resqml2_0_1::resqml2__ResqmlUom & uom, const gsoap_resqml2_0_1::resqml2__ResqmlPropertyKind & energisticsPropertyKind);

		DLL_IMPORT_OR_EXPORT RESQML2_0_1_NS::ContinuousProperty* createContinuousProperty(RESQML2_NS::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			const unsigned int & dimension, const gsoap_resqml2_0_1::resqml2__IndexableElements & attachmentKind, const gsoap_resqml2_0_1::resqml2__ResqmlUom & uom, RESQML2_NS::PropertyKind * localPropType);

		DLL_IMPORT_OR_EXPORT RESQML2_0_1_NS::ContinuousProperty* createContinuousProperty(RESQML2_NS::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			const unsigned int & dimension, const gsoap_resqml2_0_1::resqml2__IndexableElements & attachmentKind, const std::string & nonStandardUom, const gsoap_resqml2_0_1::resqml2__ResqmlPropertyKind & energisticsPropertyKind);

		DLL_IMPORT_OR_EXPORT RESQML2_0_1_NS::ContinuousProperty* createContinuousProperty(RESQML2_NS::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			const unsigned int & dimension, const gsoap_resqml2_0_1::resqml2__IndexableElements & attachmentKind, const std::string & nonStandardUom, RESQML2_NS::PropertyKind * localPropType);

		DLL_IMPORT_OR_EXPORT RESQML2_0_1_NS::ContinuousPropertySeries* createContinuousPropertySeries(RESQML2_NS::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			const unsigned int & dimension, const gsoap_resqml2_0_1::resqml2__IndexableElements & attachmentKind, const gsoap_resqml2_0_1::resqml2__ResqmlUom & uom, const gsoap_resqml2_0_1::resqml2__ResqmlPropertyKind & energisticsPropertyKind,
			RESQML2_NS::TimeSeries * ts, const bool & useInterval = false);

		DLL_IMPORT_OR_EXPORT RESQML2_0_1_NS::ContinuousPropertySeries* createContinuousPropertySeries(RESQML2_NS::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			const unsigned int & dimension, const gsoap_resqml2_0_1::resqml2__IndexableElements & attachmentKind, const gsoap_resqml2_0_1::resqml2__ResqmlUom & uom, RESQML2_NS::PropertyKind * localPropType,
			RESQML2_NS::TimeSeries * ts, const bool & useInterval = false);
	
		DLL_IMPORT_OR_EXPORT RESQML2_0_1_NS::DiscreteProperty* createDiscreteProperty(RESQML2_NS::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			const unsigned int & dimension, const gsoap_resqml2_0_1::resqml2__IndexableElements & attachmentKind, const gsoap_resqml2_0_1::resqml2__ResqmlPropertyKind & energisticsPropertyKind);

		DLL_IMPORT_OR_EXPORT RESQML2_0_1_NS::DiscreteProperty* createDiscreteProperty(RESQML2_NS::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			const unsigned int & dimension, const gsoap_resqml2_0_1::resqml2__IndexableElements & attachmentKind, RESQML2_NS::PropertyKind * localPropType);
	
		DLL_IMPORT_OR_EXPORT RESQML2_0_1_NS::DiscretePropertySeries* createDiscretePropertySeries(RESQML2_NS::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			const unsigned int & dimension, const gsoap_resqml2_0_1::resqml2__IndexableElements & attachmentKind, const gsoap_resqml2_0_1::resqml2__ResqmlPropertyKind & energisticsPropertyKind,
			RESQML2_NS::TimeSeries * ts, const bool & useInterval = false);

		DLL_IMPORT_OR_EXPORT RESQML2_0_1_NS::DiscretePropertySeries* createDiscretePropertySeries(RESQML2_NS::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			const unsigned int & dimension, const gsoap_resqml2_0_1::resqml2__IndexableElements & attachmentKind, RESQML2_NS::PropertyKind * localPropType,
			RESQML2_NS::TimeSeries * ts, const bool & useInterval = false);

		DLL_IMPORT_OR_EXPORT RESQML2_0_1_NS::CategoricalProperty* createCategoricalProperty(RESQML2_NS::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			const unsigned int & dimension, const gsoap_resqml2_0_1::resqml2__IndexableElements & attachmentKind,
			RESQML2_0_1_NS::StringTableLookup* strLookup, const gsoap_resqml2_0_1::resqml2__ResqmlPropertyKind & energisticsPropertyKind);
	
		DLL_IMPORT_OR_EXPORT RESQML2_0_1_NS::CategoricalProperty* createCategoricalProperty(RESQML2_NS::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			const unsigned int & dimension, const gsoap_resqml2_0_1::resqml2__IndexableElements & attachmentKind,
			RESQML2_0_1_NS::StringTableLookup* strLookup, RESQML2_NS::PropertyKind * localPropType);

		DLL_IMPORT_OR_EXPORT RESQML2_0_1_NS::CategoricalPropertySeries* createCategoricalPropertySeries(RESQML2_NS::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			const unsigned int & dimension, const gsoap_resqml2_0_1::resqml2__IndexableElements & attachmentKind,
			RESQML2_0_1_NS::StringTableLookup* strLookup, const gsoap_resqml2_0_1::resqml2__ResqmlPropertyKind & energisticsPropertyKind,
			RESQML2_NS::TimeSeries * ts, const bool & useInterval = false);

		DLL_IMPORT_OR_EXPORT RESQML2_0_1_NS::CategoricalPropertySeries* createCategoricalPropertySeries(RESQML2_NS::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			const unsigned int & dimension, const gsoap_resqml2_0_1::resqml2__IndexableElements & attachmentKind,
			RESQML2_0_1_NS::StringTableLookup* strLookup, RESQML2_NS::PropertyKind * localPropType,
			RESQML2_NS::TimeSeries * ts, const bool & useInterval = false);

		//************************************
		//************* ACTIVITIES ***********
		//************************************

		DLL_IMPORT_OR_EXPORT RESQML2_NS::ActivityTemplate* createActivityTemplate(const std::string & guid, const std::string & title);
		
		DLL_IMPORT_OR_EXPORT RESQML2_NS::Activity* createActivity(RESQML2_NS::ActivityTemplate* activityTemplate, const std::string & guid, const std::string & title);
		
		//************************************
		//*************** WITSML *************
		//************************************
		
		/**
		* Get all the witsml trajectories contained into the EPC document
		*/
		DLL_IMPORT_OR_EXPORT std::vector<WITSML2_1_NS::Trajectory*> getWitsmlTrajectorySet() const;

		DLL_IMPORT_OR_EXPORT WITSML2_1_NS::ToolErrorModel* createPartialToolErrorModel(
			const std::string & guid,
			const std::string & title);

		DLL_IMPORT_OR_EXPORT WITSML2_1_NS::ToolErrorModel* createToolErrorModel(
			const std::string & guid,
			const std::string & title,
			gsoap_eml2_2::witsml2__MisalignmentMode misalignmentMode);

		DLL_IMPORT_OR_EXPORT WITSML2_1_NS::ToolErrorModelDictionary* createToolErrorModelDictionary(
			const std::string & guid,
			const std::string & title);

		DLL_IMPORT_OR_EXPORT WITSML2_1_NS::ErrorTerm* createErrorTerm(
			const std::string & guid,
			const std::string & title,
			gsoap_eml2_2::witsml2__ErrorPropagationMode propagationMode,
			WITSML2_1_NS::WeightingFunction* weightingFunction);

		DLL_IMPORT_OR_EXPORT WITSML2_1_NS::ErrorTermDictionary* createErrorTermDictionary(
			const std::string & guid,
			const std::string & title);

		DLL_IMPORT_OR_EXPORT WITSML2_1_NS::WeightingFunction* createWeightingFunction(
			const std::string & guid,
			const std::string & title,
			const std::string & depthFormula,
			const std::string & inclinationFormula,
			const std::string & azimuthFormula);

		DLL_IMPORT_OR_EXPORT WITSML2_1_NS::WeightingFunctionDictionary* createWeightingFunctionDictionary(
			const std::string & guid,

		DLL_IMPORT_OR_EXPORT WITSML2_0_NS::Well* createWell(const std::string & guid,
			const std::string & title);

		DLL_IMPORT_OR_EXPORT WITSML2_0_NS::Well* createWell(const std::string & guid,
			const std::string & title,
			const std::string & operator_,
			gsoap_eml2_1::eml21__WellStatus statusWell,
			gsoap_eml2_1::witsml2__WellDirection directionWell
		);

		DLL_IMPORT_OR_EXPORT WITSML2_0_NS::Wellbore* createPartialWellbore(
			const std::string & guid,
			const std::string & title);

		DLL_IMPORT_OR_EXPORT WITSML2_0_NS::Wellbore* createWellbore(WITSML2_0_NS::Well* witsmlWell,
			const std::string & guid,
			const std::string & title);

		DLL_IMPORT_OR_EXPORT WITSML2_0_NS::Wellbore* createWellbore(WITSML2_0_NS::Well* witsmlWell,
			const std::string & guid,
			const std::string & title,
			gsoap_eml2_1::eml21__WellStatus statusWellbore,
			bool isActive,
			bool achievedTD
		);

		DLL_IMPORT_OR_EXPORT WITSML2_0_NS::WellCompletion* createWellCompletion(WITSML2_0_NS::Well* witsmlWell,
			const std::string & guid,
			const std::string & title);

		DLL_IMPORT_OR_EXPORT WITSML2_0_NS::WellboreCompletion* createWellboreCompletion(WITSML2_0_NS::Wellbore* witsmlWellbore,
			WITSML2_0_NS::WellCompletion* wellCompletion,
			const std::string & guid,
			const std::string & title,
			const std::string & wellCompletionName);

		DLL_IMPORT_OR_EXPORT WITSML2_0_NS::Trajectory* createTrajectory(WITSML2_0_NS::Wellbore* witsmlWellbore,
			const std::string & guid,
			const std::string & title,
			gsoap_eml2_1::witsml2__ChannelStatus channelStatus);

		//************************************
		//************* WARNINGS *************
		//************************************

		DLL_IMPORT_OR_EXPORT void addWarning(const std::string & warning);
		DLL_IMPORT_OR_EXPORT const std::vector<std::string> & getWarnings() const;

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
		void addFesapiWrapperAndDeleteItIfException(COMMON_NS::AbstractObject* proxy);

		/**
		* Read the Gsoap proxy from the stream associated to the current gsoap context and wrap this gsoap proxy into a fesapi wrapper.
		* It does not add this fesapi wrapper to the current instance.
		* It does not work for EpcExternalPartReference content type since this type is related to an external file which must be handled differently.
		*/
		COMMON_NS::AbstractObject* getResqml2_0_1WrapperFromGsoapContext(const std::string & resqmlContentType);

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
		std::unordered_map< std::string, COMMON_NS::AbstractObject* > dataObjectSet;
#else
		std::tr1::unordered_map< std::string, COMMON_NS::AbstractObject* > dataObjectSet;
#endif
		soap* s;
		std::string filePath;

		// Better for performance reason to have set of important objects instead of having a global vector of GsoapWrapper
		// Even if redundant with resqmlAbstractObjectSet
		std::vector<RESQML2_0_1_NS::LocalDepth3dCrs*>					localDepth3dCrsSet;
		std::vector<RESQML2_0_1_NS::LocalTime3dCrs*>					localTime3dCrsSet;
		std::vector<RESQML2_0_1_NS::TectonicBoundaryFeature*>			faultSet;
		std::vector<RESQML2_0_1_NS::TectonicBoundaryFeature*>			fractureSet;
		std::vector<RESQML2_0_1_NS::GeneticBoundaryFeature*>			geneticBoundarySet;
		std::vector<RESQML2_0_1_NS::GeobodyFeature*>					geobodySet;
		std::vector<RESQML2_0_1_NS::SeismicLineFeature*>				seismicLineSet;
		std::vector<COMMON_NS::AbstractHdfProxy*>						hdfProxySet;
		std::vector<RESQML2_0_1_NS::WellboreFeature*>					wellboreSet;
		std::vector<RESQML2_NS::RepresentationSetRepresentation*>		representationSetRepresentationSet;
		std::vector<RESQML2_0_1_NS::TriangulatedSetRepresentation*>		triangulatedSetRepresentationSet;
		std::vector<RESQML2_0_1_NS::Grid2dRepresentation*>				grid2dRepresentationSet;
		std::vector<WITSML2_1_NS::Trajectory*>							witsmlTrajectorySet;
		std::vector<RESQML2_0_1_NS::PolylineRepresentation*>			polylineRepresentationSet;
		std::vector<RESQML2_0_1_NS::PolylineSetRepresentation*>			polylineSetRepresentationSet;
		std::vector<RESQML2_0_1_NS::AbstractIjkGridRepresentation*>		ijkGridRepresentationSet;
		std::vector<RESQML2_0_1_NS::UnstructuredGridRepresentation*>	unstructuredGridRepresentationSet;
		std::vector<RESQML2_0_1_NS::StratigraphicColumn*>				stratigraphicColumnSet;
		std::vector<RESQML2_0_1_NS::FrontierFeature*>					frontierSet;
		std::vector<RESQML2_0_1_NS::OrganizationFeature*> 				organizationSet;
		std::vector<RESQML2_NS::TimeSeries*> 							timeSeriesSet;
		std::vector<RESQML2_NS::SubRepresentation*>						subRepresentationSet;
		std::vector<RESQML2_0_1_NS::PointSetRepresentation*>			pointSetRepresentationSet;

		RESQML2_0_1_NS::PropertyKindMapper* propertyKindMapper;

		std::vector<std::string> warnings;

		HdfProxyBuilder* make_hdf_proxy; /// the builder for HDF proxy in writing mode of the epc document
		HdfProxyBuilderFromGsoapProxy2_0_1* make_hdf_proxy_from_gsoap_proxy_2_0_1; /// the builder for a v2.0.1 HDF proxy in reading mode of the epc document
	};
}
