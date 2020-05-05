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

#include <unordered_map>
#include <sstream>
#include <chrono>

#include "../proxies/gsoap_resqml2_0_1H.h"
#include "../proxies/gsoap_eml2_1H.h"
#include "../proxies/gsoap_eml2_2H.h"
#include "../proxies/gsoap_eml2_3H.h"

#include "DataObjectIdentifier.h"

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
	class PropertySet;
	class SubRepresentation;
	class TimeSeries;
	class RepresentationSetRepresentation;
	class WellboreFrameRepresentation;
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
	class PropertySet;
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

#if WITH_EXPERIMENTAL
namespace RESQML2_2_NS
{
	class DiscreteColorMap;
	class ContinuousColorMap;
	class SeismicWellboreFrameRepresentation;
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
#endif

namespace WITSML2_0_NS
{
	class AbstractObject;
	class Well;
	class WellCompletion;
	class Wellbore;
	class WellboreCompletion;
	class WellboreGeometry;
	class Trajectory;
	class Log;
	class ChannelSet;
	class Channel;
}

namespace PRODML2_1_NS
{
	class FluidSystem;
	class FluidCharacterization;
}

namespace COMMON_NS
{
	class AbstractObject;
	class AbstractHdfProxy;
	class DataFeeder;
	class HdfProxyFactory;
	class PropertyKind;
#if WITH_EXPERIMENTAL
	class GraphicalInformationSet;
#endif

	/**
	* This abstract class acts as a buffer between the RESQML (business) classes and the persisted data.
	*/
	class DataObjectRepository
	{
	public:

		DLL_IMPORT_OR_EXPORT DataObjectRepository();
		DLL_IMPORT_OR_EXPORT DataObjectRepository(const std::string & propertyKindMappingFilesDirectory);

		enum class openingMode : std::int8_t {
			READ_ONLY = 0, // It is meant to open an existing file in read only mode. It throws an exception if the file does not exist.
			READ_WRITE = 1, // It is meant to open a file in read and write mode. It creates the file if the file does not exist.
			READ_WRITE_DO_NOT_CREATE = 2, // It is meant to open an existing file in read and write mode. It throws an exception if the file does not exist.
			OVERWRITE = 3 // It is meant to open an existing file in read and write mode. It deletes the content of the file if the later does already exist.
		};
		enum CUD { CREATED = 0, UPDATED = 1, DELETED = 2 };

		DLL_IMPORT_OR_EXPORT virtual ~DataObjectRepository();

		soap* getGsoapContext() const { return gsoapContext; }

		/**
		* Remove and clean all dataobjects from this repository
		*/
		DLL_IMPORT_OR_EXPORT void clear();

		/**
		* Add a directed relationship between two objects.
		* Source and target are defined by Energistics data model. Usually, the simplest is to look at Energistics UML diagrams. Another way is to rely on XSD/XML : explicit relationships are contained by the source objects and point to target objects.
		* @param source	The source object of the relationship
		*/
		DLL_IMPORT_OR_EXPORT void addRelationship(COMMON_NS::AbstractObject * source, COMMON_NS::AbstractObject * target);

		/**
		* Register a data feeder to allow partial objects resolution.
		* It is your responsability to manage the memory of your data feeder. DataObject repository won't never free memory of a data feeder.
		*/
		DLL_IMPORT_OR_EXPORT void registerDataFeeder(COMMON_NS::DataFeeder * dataFeeder);

		/*
		* Delete a relationship between two objects
		* Source and target are defined by Energistics data model. Usually, the simplest is to look at Energistics UML diagrams. Another way is to rely on XSD/XML : explicit relationships are contained by the source objects and point to target objects.
		* @param source	The source object of the relationship
		*/
		DLL_IMPORT_OR_EXPORT void deleteRelationship(COMMON_NS::AbstractObject * source, COMMON_NS::AbstractObject * target);

		/**
		* Check either this repository has got an HDF proxy or not.
		*/
		DLL_IMPORT_OR_EXPORT bool hasHdfProxyFactory() { return hdfProxyFactory != nullptr; }

		/**
		* Set the factory used to create Hdf Proxy and takes ownership of this HDF Proxy factory (don't delete it!)
		*/
		DLL_IMPORT_OR_EXPORT void setHdfProxyFactory(COMMON_NS::HdfProxyFactory * factory);

		/**
		* Get the journal of the DataObject repository.
		*/
		const std::vector< std::tuple<std::chrono::time_point<std::chrono::system_clock>, COMMON_NS::DataObjectIdentifier, CUD> >& getJournal() const { return journal; }

		/**
		* Allow a specialization of a DataObjectRepository to provide a special behaviour when a dataobject is created
		*/
		DLL_IMPORT_OR_EXPORT virtual void on_CreateDataObject(const std::vector<std::pair<std::chrono::time_point<std::chrono::system_clock>, COMMON_NS::AbstractObject*>>&) {}

		/**
		* Allow a specialization of a DataObjectRepository to provide a special behaviour when a dataobject is update
		*/
		DLL_IMPORT_OR_EXPORT virtual void on_UpdateDataObject(const std::vector<std::pair<std::chrono::time_point<std::chrono::system_clock>, COMMON_NS::AbstractObject*>>&) {}

		/**
		* Resolve a partial object thanks to a data feeder into this data repository.
		* This method needs some registered data feeder in order to work.
		*/
		DLL_IMPORT_OR_EXPORT COMMON_NS::AbstractObject* resolvePartial(COMMON_NS::AbstractObject * partialObj);

		/**
		* Get the direct target objects (by reference) of a particular data object.
		*/
		DLL_IMPORT_OR_EXPORT const std::vector<COMMON_NS::AbstractObject*>& getTargetObjects(COMMON_NS::AbstractObject const * dataObj) const { return forwardRels.at(dataObj); }

		/**
		* Get the target objects of a particular data object and potentially targets of targets, etc...
		* @param dataObj			The dataobject which we want to know the targets about.
		* @param depth				How much targets of targets do we want? A depth of 0 means that we only want the dataobject itself. A depth of 1 means that we only want the direct targets.
		*							A depth of 2 means that we want the direct targets + the targets of the direct targets, etc... 
		* @param filteredDatatypes	The returned targets will be filtered based on this list of authorized datatypes. A qualified type "namespace.*" means a filter on the namespace.
		*/
		DLL_IMPORT_OR_EXPORT std::vector<COMMON_NS::AbstractObject*> getTargetObjects(COMMON_NS::AbstractObject const * dataObj, size_t depth,
			const std::vector<std::string>& filteredDatatypes = std::vector<std::string>()) const;

		template <class valueType>
		std::vector<valueType *> getTargetObjects(COMMON_NS::AbstractObject const * dataObj) const
		{
			return getObjsFilteredOnDatatype<valueType>(getTargetObjects(dataObj));
		}

		/**
		* Get the source objects of a particular data object.
		*/
		DLL_IMPORT_OR_EXPORT const std::vector< COMMON_NS::AbstractObject*>& getSourceObjects(COMMON_NS::AbstractObject const * dataObj) const { return backwardRels.at(dataObj); }

		/**
		* Get the source objects of a particular data object and potentially sources of sources, etc...
		* @param dataObj			The dataobject which we want to know the sources about.
		* @param depth				How much sources of sources do we want? A depth of 0 means that we only want the dataobject itself. A depth of 1 means that we only want the direct sources.
		*							A depth of 2 means that we want the direct sources + the sources of the direct sources, etc...
		* @param filteredDatatypes	The returned sources will be filtered based on this list of authorized datatypes. A qualified type "namespace.*" means a filter on the namespace.
		*/
		DLL_IMPORT_OR_EXPORT std::vector<COMMON_NS::AbstractObject*> getSourceObjects(COMMON_NS::AbstractObject const * dataObj, size_t depth,
			const std::vector<std::string>& filteredDatatypes = std::vector<std::string>()) const;

		template <class valueType>
		std::vector<valueType *> getSourceObjects(COMMON_NS::AbstractObject const * dataObj) const
		{
			const std::vector < COMMON_NS::AbstractObject*> & sourceObjects = getSourceObjects(dataObj);

			return getObjsFilteredOnDatatype<valueType>(sourceObjects);
		}

		/**
		* Update all the relationships based on the contained dataobjects
		*/
		DLL_IMPORT_OR_EXPORT void updateAllRelationships();

		/**
		* Add or replace (based on UUID and version) a dataobject in the repository.
		* It does not update the rel of the added or replaced data object.
		* @param proxy				The dataobject to add or replace.
		* @param replaceOnlyContent If true, it does not replace the full object (not the pointer) but only replace the content of the object.
		*/
		DLL_IMPORT_OR_EXPORT COMMON_NS::AbstractObject* addOrReplaceDataObject(COMMON_NS::AbstractObject* proxy, bool replaceOnlyContent = false);

		/**
		* Add a dataobject to the repository based on its Energistics XML definition.
		* @param xml				The XML which is the serialization of the Energistics dataobject to add or to replace.
		* @param contentOrDataType	The content or qualified data type of the Energistics dataobject to add or to replace.
		*/
		DLL_IMPORT_OR_EXPORT COMMON_NS::AbstractObject* addOrReplaceGsoapProxy(const std::string & xml, const std::string & contentOrDataType);

		/**
		* Get all the data objects which are part of this repository.
		* They are in a map wher the key is the UUID of the objects and the value is all different versions of this data object.
		*/
		const std::unordered_map< std::string, std::vector< COMMON_NS::AbstractObject* > > & getDataObjects() const { return dataObjects; }

		/**
		* Group Data objects by datatype
		* @return A map where the key is a qualified datatype and where the value is the collection of Data objects of this data type
		*/
		DLL_IMPORT_OR_EXPORT std::unordered_map< std::string, std::vector<COMMON_NS::AbstractObject*> > getDataObjectsGroupedByDataType() const;

		/**
		* Group Data objects of the repository by datatype based on a filtered list 
		* @param filter A string that the returned Dataobject must contain in their datatype.
		* @return A map where the key is a datatype and where the value is the collection of Data objects of this datatype
		*/
		DLL_IMPORT_OR_EXPORT std::unordered_map< std::string, std::vector<COMMON_NS::AbstractObject*> > getDataObjectsGroupedByDataType(const std::string & filter) const;

		/**
		* Get Data objects which honor this content type
		* @return The vector of Data objects in this repository which honor the content type
		*/
		DLL_IMPORT_OR_EXPORT std::vector<COMMON_NS::AbstractObject*> getDataObjectsByContentType(const std::string & contentType) const;

		/**
		* Get all data objects of a particular type indicated by means of the template class.
		*
		* @return The vector of data object in this EPC Document
		*/
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

		/**
		* DEPRECATED : use getDataObjects template method
		* Get all the local 3d depth crs contained into the EPC document
		*/
		DLL_IMPORT_OR_EXPORT std::vector<RESQML2_0_1_NS::LocalDepth3dCrs*> getLocalDepth3dCrsSet() const;

		/**
		* DEPRECATED : use getDataObjects template method
		* Get all the local 3d time crs contained into the EPC document
		*/
		DLL_IMPORT_OR_EXPORT std::vector<RESQML2_0_1_NS::LocalTime3dCrs*> getLocalTime3dCrsSet() const;

		/**
		* Get the default CRS for writing.
		* It is used in all writing methods where no explicit CRS is given.
		*/
		DLL_IMPORT_OR_EXPORT RESQML2_NS::AbstractLocal3dCrs* getDefaultCrs() const { return defaultCrs; }

		/**
		* Set a default CRS for writing.
		* It will be used in all writing methods where no explicit CRS is given.
		*/
		DLL_IMPORT_OR_EXPORT void setDefaultCrs(RESQML2_NS::AbstractLocal3dCrs* crs) { defaultCrs = crs; }

		/**
		* DEPRECATED : use getDataObjects template method
		* Get all the stratigraphic columns contained into the EPC document
		*/
		DLL_IMPORT_OR_EXPORT std::vector<RESQML2_0_1_NS::StratigraphicColumn*> getStratigraphicColumnSet() const;

		/**
		* Get all the faults contained into the EPC document
		*/
		DLL_IMPORT_OR_EXPORT std::vector<RESQML2_0_1_NS::TectonicBoundaryFeature*> getFaultSet() const;

		/**
		* Get all the fractures contained into the EPC document
		*/
		DLL_IMPORT_OR_EXPORT std::vector<RESQML2_0_1_NS::TectonicBoundaryFeature*> getFractureSet() const;

		/**
		* Get all the individual representations of faults which are associated to a polyline topology
		*/
		DLL_IMPORT_OR_EXPORT std::vector<RESQML2_0_1_NS::PolylineSetRepresentation *> getFaultPolylineSetRepSet() const;

		/**
		* Get all the individual representations of fractures which are associated to a polyline topology
		*/
		DLL_IMPORT_OR_EXPORT std::vector<RESQML2_0_1_NS::PolylineSetRepresentation *> getFracturePolylineSetRepSet() const;

		/**
		* Get all the individual representations of frontiers which are associated to a polyline set topology
		*/
		DLL_IMPORT_OR_EXPORT std::vector<RESQML2_0_1_NS::PolylineSetRepresentation *> getFrontierPolylineSetRepSet() const;

		/**
		* Get all the individual representations of faults which are associated to a triangulation set topology
		*/
		DLL_IMPORT_OR_EXPORT std::vector<RESQML2_0_1_NS::TriangulatedSetRepresentation *> getFaultTriangulatedSetRepSet() const;

		/**
		* Get all the individual representations of fractures which are associated to a triangulation set topology
		*/
		DLL_IMPORT_OR_EXPORT std::vector<RESQML2_0_1_NS::TriangulatedSetRepresentation *> getFractureTriangulatedSetRepSet() const;

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
		* DEPRECATED : use getDataObjects template method
		* Get all the geobodies contained into the EPC document
		*/
		DLL_IMPORT_OR_EXPORT std::vector<RESQML2_0_1_NS::GeobodyFeature*> getGeobodySet() const;

		/**
		* Get all the individual representations of horizons which are associated to grid 2d set topology
		*/
		DLL_IMPORT_OR_EXPORT std::vector<RESQML2_0_1_NS::Grid2dRepresentation *> getHorizonGrid2dRepSet() const;

		/**
		* Get all the single polyline representations of all the horizons
		*/
		DLL_IMPORT_OR_EXPORT std::vector<RESQML2_0_1_NS::PolylineRepresentation *> getHorizonPolylineRepSet() const;

		/**
		* Get all the single polyline representations of all the horizons
		*/
		DLL_IMPORT_OR_EXPORT std::vector<RESQML2_0_1_NS::PolylineSetRepresentation *> getHorizonPolylineSetRepSet() const;

		/**
		* Get all the triangulated set representations of all the horizons
		*/
		DLL_IMPORT_OR_EXPORT std::vector<RESQML2_0_1_NS::TriangulatedSetRepresentation *> getHorizonTriangulatedSetRepSet() const;

		/**
		* DEPRECATED : use getDataObjects template method
		* Get all the triangulated set representations of the EPC document
		*/
		DLL_IMPORT_OR_EXPORT std::vector<RESQML2_0_1_NS::TriangulatedSetRepresentation*> getAllTriangulatedSetRepSet() const;

		/**
		* DEPRECATED : use getDataObjects template method
		* Get all the grid 2d representations of the EPC document
		*/
		DLL_IMPORT_OR_EXPORT std::vector<RESQML2_0_1_NS::Grid2dRepresentation*> getAllGrid2dRepresentationSet() const;

		/**
		* DEPRECATED : use getDataObjects template method
		* Get all the polyline set representations of the EPC document
		*/
		DLL_IMPORT_OR_EXPORT std::vector<RESQML2_0_1_NS::PolylineSetRepresentation*> getAllPolylineSetRepSet() const;

		/**
		* Get all the triangulated set representations of the EPC document which are not horizon and fault neither.
		*/
		DLL_IMPORT_OR_EXPORT std::vector<RESQML2_0_1_NS::TriangulatedSetRepresentation*> getUnclassifiedTriangulatedSetRepSet() const;

		/**
		* DEPRECATED : use getDataObjects template method
		* Get all the seismic line contained into the EPC document
		*/
		DLL_IMPORT_OR_EXPORT std::vector<RESQML2_0_1_NS::SeismicLineFeature*> getSeismicLineSet() const;

		/**
		* DEPRECATED : use getDataObjects template method
		* Get all the wellbores contained into the EPC document
		*/
		DLL_IMPORT_OR_EXPORT std::vector<RESQML2_0_1_NS::WellboreFeature*> getWellboreSet() const;

		/**
		* Get all the trajectory representations of all wellbores.
		*/
		DLL_IMPORT_OR_EXPORT std::vector<RESQML2_0_1_NS::WellboreTrajectoryRepresentation *> getWellboreTrajectoryRepresentationSet() const;

		/**
		* Get all the devaition survey of all wellbores.
		*/
		DLL_IMPORT_OR_EXPORT std::vector<RESQML2_0_1_NS::DeviationSurveyRepresentation *> getDeviationSurveyRepresentationSet() const;

		/**
		* DEPRECATED : use getDataObjects template method
		* Get all the representationset representations contained into the EPC document
		*/
		DLL_IMPORT_OR_EXPORT std::vector<RESQML2_NS::RepresentationSetRepresentation*> getRepresentationSetRepresentationSet() const;

		/**
		* Get the representationset representations count of this EPC document
		*/
		DLL_IMPORT_OR_EXPORT unsigned int getRepresentationSetRepresentationCount() const;

		/**
		* Get the representationset representations at a particular index of this EPC document
		*/
		DLL_IMPORT_OR_EXPORT RESQML2_NS::RepresentationSetRepresentation* getRepresentationSetRepresentation(unsigned int index) const;

		/**
		* DEPRECATED : use getDataObjects template method
		* Get all the polyline representations contained into the EPC document.
		*/
		DLL_IMPORT_OR_EXPORT std::vector<RESQML2_0_1_NS::PolylineRepresentation*> getAllPolylineRepresentationSet() const;

		/**
		* Get all the single polyline representations contained into the EPC document which correspond to a seismic line.
		*/
		DLL_IMPORT_OR_EXPORT std::vector<RESQML2_0_1_NS::PolylineRepresentation*> getSeismicLinePolylineRepSet() const;

		/**
		* DEPRECATED : use getDataObjects template method
		* Get all the ijk grid contained into the EPC document.
		*/
		DLL_IMPORT_OR_EXPORT std::vector<RESQML2_0_1_NS::AbstractIjkGridRepresentation*> getIjkGridRepresentationSet() const;
		DLL_IMPORT_OR_EXPORT unsigned int getIjkGridRepresentationCount() const;
		DLL_IMPORT_OR_EXPORT RESQML2_0_1_NS::AbstractIjkGridRepresentation* getIjkGridRepresentation(unsigned int index) const;

		/**
		* DEPRECATED : use getDataObjects template method
		* Get all the ijk grid contained into the EPC document which have a parametric geometry.
		*/
		DLL_IMPORT_OR_EXPORT std::vector<RESQML2_0_1_NS::IjkGridParametricRepresentation*> getIjkGridParametricRepresentationSet() const;

		/**
		* DEPRECATED : use getDataObjects template method
		* Get all the ijk grid contained into the EPC document which have an explicit geometry.
		*/
		DLL_IMPORT_OR_EXPORT std::vector<RESQML2_0_1_NS::IjkGridExplicitRepresentation*> getIjkGridExplicitRepresentationSet() const;

		/**
		* Get all the ijk grid contained into the EPC document which correspond to a seismic cube.
		*/
		DLL_IMPORT_OR_EXPORT std::vector<RESQML2_0_1_NS::IjkGridLatticeRepresentation*> getIjkSeismicCubeGridRepresentationSet() const;

		/**
		* DEPRECATED : use getDataObjects template method
		* Get all the unstructured grid contained into the EPC document
		*/
		DLL_IMPORT_OR_EXPORT std::vector<RESQML2_0_1_NS::UnstructuredGridRepresentation*> getUnstructuredGridRepresentationSet() const;

		/**
		* DEPRECATED : use getDataObjects template method
		* Get all the frontier features contained into the EPC document
		*/
		DLL_IMPORT_OR_EXPORT std::vector<RESQML2_0_1_NS::FrontierFeature*> getFrontierSet() const;

		/**
		* DEPRECATED : use getDataObjects template method
		* Get all the organization features contained into the EPC document
		*/
		DLL_IMPORT_OR_EXPORT std::vector<RESQML2_0_1_NS::OrganizationFeature*> getOrganizationSet() const;

		/**
		* DEPRECATED : use getDataObjects template method
		* Get all the time series contained into the EPC document
		*/
		DLL_IMPORT_OR_EXPORT std::vector<RESQML2_NS::TimeSeries*> getTimeSeriesSet() const;

		/**
		* DEPRECATED : use getDataObjects template method
		* Get all the subrepresentations contained into the EPC document
		*/
		DLL_IMPORT_OR_EXPORT std::vector<RESQML2_NS::SubRepresentation*> getSubRepresentationSet() const;
		DLL_IMPORT_OR_EXPORT unsigned int getSubRepresentationCount() const;
		DLL_IMPORT_OR_EXPORT RESQML2_NS::SubRepresentation* getSubRepresentation(unsigned int index) const;

		/**
		* DEPRECATED : use getDataObjects template method
		* Get all the point set representations contained into the EPC document
		*/
		DLL_IMPORT_OR_EXPORT std::vector<RESQML2_0_1_NS::PointSetRepresentation*> getPointSetRepresentationSet() const;
		DLL_IMPORT_OR_EXPORT unsigned int getPointSetRepresentationCount() const;
		DLL_IMPORT_OR_EXPORT RESQML2_0_1_NS::PointSetRepresentation* getPointSetRepresentation(unsigned int index) const;

		/**
		* DEPRECATED : use getDataObjects template method
		* Get all the HDF proxies
		*/
		DLL_IMPORT_OR_EXPORT std::vector<COMMON_NS::AbstractHdfProxy*> getHdfProxySet() const;
		DLL_IMPORT_OR_EXPORT unsigned int getHdfProxyCount() const;
		DLL_IMPORT_OR_EXPORT COMMON_NS::AbstractHdfProxy* getHdfProxy(unsigned int index) const;

		/**
		* Get the default hdf proxy for writing.
		* It is used in all writing methods where no explicit HDF proxy is given.
		*/
		DLL_IMPORT_OR_EXPORT COMMON_NS::AbstractHdfProxy* getDefaultHdfProxy() const { return defaultHdfProxy; }

		/**
		* Set a default hdf proxy for writing.
		* It will be used in all writing methods where no explicit HDF proxy is given.
		*/
		DLL_IMPORT_OR_EXPORT void setDefaultHdfProxy(COMMON_NS::AbstractHdfProxy* hdfProxy) { defaultHdfProxy = hdfProxy; }

		/**
		* Get a data object from the repository by means of its uuid.
		* If several versions of this uuid object exist in the repository, the first one in memory will be arbitrarily returned.
		* @param uuid		The uuid of the requested data object.
		* @return			nullptr if no dataobject corresponds to the uuid
		*/
		DLL_IMPORT_OR_EXPORT COMMON_NS::AbstractObject* getDataObjectByUuid(const std::string & uuid) const;

		/**
		* Get a data object from the repository by means of its uuid
		* and try to cast it to a child class of COMMON_NS::AbstractObject
		* @return nullptr if no dataobject corresponds to the uuid
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
		* Get a data object from the repository by means of its uuid and from its version.
		* @param uuid		The uuid of the requested data object.
		* @param version	The version of the requested data object.
		* @return			nullptr if no dataobject corresponds to the uuid + version
		*/
		DLL_IMPORT_OR_EXPORT COMMON_NS::AbstractObject* getDataObjectByUuidAndVersion(const std::string & uuid, const std::string & version) const;

		/**
		* Get a data object from the repository by means of its uuid and from its version.
		* @param uuid		The uuid of the requested data object.
		* @param version	The version of the requested data object.
		* @return			nullptr if no dataobject corresponds to the uuid + version
		*/
		DLL_IMPORT_OR_EXPORT COMMON_NS::AbstractObject* getDataObjectByUuidAndVersion(const std::array<uint8_t, 16> & uuid, const std::string & version) const;

		/**
		* Get a data object from the repository by means of its uuid and from its version
		* and try to cast it to a child class of COMMON_NS::AbstractObject
		* @return nullptr if no dataobject corresponds to the uuid + version
		*/
		template <class valueType>
		valueType* getDataObjectByUuidAndVersion(const std::string & uuid, const std::string & version) const
		{
			COMMON_NS::AbstractObject* const result = getDataObjectByUuidAndVersion(uuid, version);

			if (result == nullptr) {
				return nullptr;
			}

			if (dynamic_cast<valueType*>(result) != nullptr) {
				return static_cast<valueType*>(result);
			}

			throw std::invalid_argument("The uuid " + uuid + " does not resolve to the expected datatype");
		}

		/**
		* Create a partial object i.e. a data object reference (DOR) based on an UUID + a title + a content type + a version
		*/
		COMMON_NS::AbstractObject* createPartial(const std::string & uuid, const std::string & title, const std::string & contentType, const std::string & version = "");

		/**
		* Create a partial object in this repository based on a RESQML2.0 Data Object Reference
		*/
		COMMON_NS::AbstractObject* createPartial(gsoap_resqml2_0_1::eml20__DataObjectReference const * dor);

		/**
		* Create a partial object in this repository based on a EML2.1 Data Object Reference
		*/
		COMMON_NS::AbstractObject* createPartial(gsoap_eml2_1::eml21__DataObjectReference const * dor);

		/**
		* Create a partial object in this repository based on a EML2.2 Data Object Reference
		*/
		COMMON_NS::AbstractObject* createPartial(gsoap_eml2_2::eml22__DataObjectReference const * dor);
#if WITH_EXPERIMENTAL
		/**
		* Create a partial object in this repository based on a EML2.3 Data Object Reference
		*/
		COMMON_NS::AbstractObject* createPartial(gsoap_eml2_3::eml23__DataObjectReference const* dor);
#endif
		/**
		* Create a partial object i.e. a data object reference (DOR) based on an UUID + a title + a version.
		* Such an object is useful to describe the underlying data object by means of a minimal amount of information : UUID, Title, Version.
		* However, such an object has quickly a lot of limitations when we want to access the data object.
		*/
		template <class valueType>
		valueType* createPartial(const std::string & guid, const std::string & title, const std::string & version = "")
		{
			gsoap_resqml2_0_1::eml20__DataObjectReference* dor = createDor(guid, title, version);
			valueType* result = new valueType(dor);
			dor->ContentType = result->getContentType();
			addOrReplaceDataObject(result);
			return result;
		}


		//************************************
		//***** DataObject creation **********
		//************************************

		/**
		* This method create a non parallel access to an HDF proxy for writing to it.
		*/
		DLL_IMPORT_OR_EXPORT COMMON_NS::AbstractHdfProxy* createHdfProxy(const std::string & guid, const std::string & title, const std::string & packageDirAbsolutePath, const std::string & externalFilePath, DataObjectRepository::openingMode hdfPermissionAccess);


		//************ CRS *******************

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
			double originOrdinal1, double originOrdinal2, double originOrdinal3,
			double arealRotation,
			gsoap_resqml2_0_1::eml20__LengthUom projectedUom, unsigned long projectedEpsgCode,
			gsoap_resqml2_0_1::eml20__LengthUom verticalUom, unsigned int verticalEpsgCode, bool isUpOriented);

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
			RESQML2_NS::AbstractLocal3dCrs * locCrs, const gsoap_resqml2_0_1::resqml20__MdReference & originKind,
			const double & referenceLocationOrdinal1, const double & referenceLocationOrdinal2, const double & referenceLocationOrdinal3);

		//************ FEATURE ***************

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

		DLL_IMPORT_OR_EXPORT RESQML2_0_1_NS::FluidBoundaryFeature* createFluidBoundaryFeature(const std::string & guid, const std::string & title, const gsoap_resqml2_0_1::resqml20__FluidContact & fluidContact);

		DLL_IMPORT_OR_EXPORT RESQML2_0_1_NS::RockFluidUnitFeature* createRockFluidUnit(const std::string & guid, const std::string & title, gsoap_resqml2_0_1::resqml20__Phase phase, RESQML2_0_1_NS::FluidBoundaryFeature* fluidBoundaryTop, RESQML2_0_1_NS::FluidBoundaryFeature* fluidBoundaryBottom);

		//************ INTERPRETATION ********

		DLL_IMPORT_OR_EXPORT RESQML2_0_1_NS::GenericFeatureInterpretation* createGenericFeatureInterpretation(RESQML2_NS::AbstractFeature * feature, const std::string & guid, const std::string & title);

		DLL_IMPORT_OR_EXPORT RESQML2_0_1_NS::BoundaryFeatureInterpretation* createBoundaryFeatureInterpretation(RESQML2_0_1_NS::BoundaryFeature * feature, const std::string & guid, const std::string & title);

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

		//************ REPRESENTATION ********

		DLL_IMPORT_OR_EXPORT RESQML2_0_1_NS::TriangulatedSetRepresentation* createTriangulatedSetRepresentation(const std::string & guid, const std::string & title);

		DLL_IMPORT_OR_EXPORT RESQML2_0_1_NS::TriangulatedSetRepresentation* createTriangulatedSetRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp,
			const std::string & guid, const std::string & title);

		DLL_IMPORT_OR_EXPORT RESQML2_0_1_NS::PolylineSetRepresentation* createPolylineSetRepresentation(const std::string & guid, const std::string & title);

		DLL_IMPORT_OR_EXPORT RESQML2_0_1_NS::PolylineSetRepresentation* createPolylineSetRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp,
			const std::string & guid, const std::string & title);

		DLL_IMPORT_OR_EXPORT RESQML2_0_1_NS::PolylineSetRepresentation* createPolylineSetRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp,
			const std::string & guid, const std::string & title, gsoap_resqml2_0_1::resqml20__LineRole roleKind);

		DLL_IMPORT_OR_EXPORT RESQML2_0_1_NS::PointSetRepresentation* createPointSetRepresentation(const std::string & guid, const std::string & title);

		DLL_IMPORT_OR_EXPORT RESQML2_0_1_NS::PointSetRepresentation* createPointSetRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp,
			const std::string & guid, const std::string & title);

		DLL_IMPORT_OR_EXPORT RESQML2_0_1_NS::PlaneSetRepresentation* createPlaneSetRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp,
			const std::string & guid, const std::string & title);

		DLL_IMPORT_OR_EXPORT RESQML2_0_1_NS::PolylineRepresentation* createPolylineRepresentation(const std::string & guid, const std::string & title, bool isClosed = false);

		DLL_IMPORT_OR_EXPORT RESQML2_0_1_NS::PolylineRepresentation* createPolylineRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp,
			const std::string & guid, const std::string & title, bool isClosed = false);

		DLL_IMPORT_OR_EXPORT RESQML2_0_1_NS::PolylineRepresentation* createPolylineRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp,
			const std::string & guid, const std::string & title, const gsoap_resqml2_0_1::resqml20__LineRole & roleKind, bool isClosed = false);

		DLL_IMPORT_OR_EXPORT RESQML2_0_1_NS::Grid2dRepresentation* createGrid2dRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp,
			const std::string & guid, const std::string & title);

		DLL_IMPORT_OR_EXPORT RESQML2_0_1_NS::WellboreTrajectoryRepresentation* createWellboreTrajectoryRepresentation(RESQML2_0_1_NS::WellboreInterpretation * interp, const std::string & guid, const std::string & title, RESQML2_NS::MdDatum * mdInfo);
		DLL_IMPORT_OR_EXPORT RESQML2_0_1_NS::WellboreTrajectoryRepresentation* createWellboreTrajectoryRepresentation(RESQML2_0_1_NS::WellboreInterpretation * interp, const std::string & guid, const std::string & title, RESQML2_0_1_NS::DeviationSurveyRepresentation * deviationSurvey);

		DLL_IMPORT_OR_EXPORT RESQML2_0_1_NS::DeviationSurveyRepresentation* createDeviationSurveyRepresentation(RESQML2_0_1_NS::WellboreInterpretation * interp, const std::string & guid, const std::string & title, const bool & isFinal, RESQML2_NS::MdDatum * mdInfo);
	
#if WITH_EXPERIMENTAL
		DLL_IMPORT_OR_EXPORT RESQML2_NS::WellboreFrameRepresentation* createWellboreFrameRepresentation(RESQML2_0_1_NS::WellboreInterpretation* interp, const std::string& guid, const std::string& title, RESQML2_0_1_NS::WellboreTrajectoryRepresentation* traj, bool previousEnergisticsVersion = false);

		DLL_IMPORT_OR_EXPORT RESQML2_2_NS::SeismicWellboreFrameRepresentation* createSeismicWellboreFrameRepresentation(
			RESQML2_0_1_NS::WellboreInterpretation* interp, 
			const std::string& guid, const std::string& title, 
			RESQML2_0_1_NS::WellboreTrajectoryRepresentation* traj,
			double seismicReferenceDatum,
			double weatheringVelocity,
			class RESQML2_0_1_NS::LocalTime3dCrs* crs);
#else
		DLL_IMPORT_OR_EXPORT RESQML2_NS::WellboreFrameRepresentation* createWellboreFrameRepresentation(RESQML2_0_1_NS::WellboreInterpretation* interp, const std::string& guid, const std::string& title, RESQML2_0_1_NS::WellboreTrajectoryRepresentation* traj);
#endif


		DLL_IMPORT_OR_EXPORT RESQML2_0_1_NS::WellboreMarkerFrameRepresentation* createWellboreMarkerFrameRepresentation(RESQML2_0_1_NS::WellboreInterpretation * interp, const std::string & guid, const std::string & title, RESQML2_0_1_NS::WellboreTrajectoryRepresentation * traj);

		DLL_IMPORT_OR_EXPORT RESQML2_0_1_NS::BlockedWellboreRepresentation* createBlockedWellboreRepresentation(RESQML2_0_1_NS::WellboreInterpretation * interp,
			const std::string & guid, const std::string & title, RESQML2_0_1_NS::WellboreTrajectoryRepresentation * traj);

		DLL_IMPORT_OR_EXPORT RESQML2_NS::RepresentationSetRepresentation* createRepresentationSetRepresentation(
			RESQML2_0_1_NS::AbstractOrganizationInterpretation* interp,
			const std::string & guid,
			const std::string & title);

		DLL_IMPORT_OR_EXPORT RESQML2_NS::RepresentationSetRepresentation* createRepresentationSetRepresentation(
			const std::string & guid,
			const std::string & title);

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

		DLL_IMPORT_OR_EXPORT RESQML2_0_1_NS::IjkGridExplicitRepresentation* createIjkGridExplicitRepresentation(const std::string & guid, const std::string & title,
			unsigned int iCount, unsigned int jCount, unsigned int kCount);

		DLL_IMPORT_OR_EXPORT RESQML2_0_1_NS::IjkGridExplicitRepresentation* createIjkGridExplicitRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp,
			const std::string & guid, const std::string & title,
			unsigned int iCount, unsigned int jCount, unsigned int kCount);

		DLL_IMPORT_OR_EXPORT RESQML2_0_1_NS::IjkGridParametricRepresentation* createIjkGridParametricRepresentation(const std::string & guid, const std::string & title,
			unsigned int iCount, unsigned int jCount, unsigned int kCount);

		DLL_IMPORT_OR_EXPORT RESQML2_0_1_NS::IjkGridParametricRepresentation* createIjkGridParametricRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp,
			const std::string & guid, const std::string & title,
			unsigned int iCount, unsigned int jCount, unsigned int kCount);

		DLL_IMPORT_OR_EXPORT RESQML2_0_1_NS::IjkGridLatticeRepresentation* createIjkGridLatticeRepresentation(const std::string & guid, const std::string & title,
			unsigned int iCount, unsigned int jCount, unsigned int kCount);

		DLL_IMPORT_OR_EXPORT RESQML2_0_1_NS::IjkGridLatticeRepresentation* createIjkGridLatticeRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp,
			const std::string & guid, const std::string & title,
			unsigned int iCount, unsigned int jCount, unsigned int kCount);

		DLL_IMPORT_OR_EXPORT RESQML2_0_1_NS::IjkGridNoGeometryRepresentation* createIjkGridNoGeometryRepresentation(
			const std::string & guid, const std::string & title,
			unsigned int iCount, unsigned int jCount, unsigned int kCount);

		DLL_IMPORT_OR_EXPORT RESQML2_0_1_NS::IjkGridNoGeometryRepresentation* createIjkGridNoGeometryRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp,
			const std::string & guid, const std::string & title,
			unsigned int iCount, unsigned int jCount, unsigned int kCount);

		DLL_IMPORT_OR_EXPORT RESQML2_0_1_NS::UnstructuredGridRepresentation* createUnstructuredGridRepresentation(const std::string & guid, const std::string & title,
			const ULONG64 & cellCount);

		DLL_IMPORT_OR_EXPORT RESQML2_NS::SubRepresentation* createSubRepresentation(
			const std::string & guid, const std::string & title);

		DLL_IMPORT_OR_EXPORT RESQML2_NS::SubRepresentation* createSubRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp,
			const std::string & guid, const std::string & title);

		DLL_IMPORT_OR_EXPORT RESQML2_NS::GridConnectionSetRepresentation* createGridConnectionSetRepresentation(const std::string & guid, const std::string & title);

		DLL_IMPORT_OR_EXPORT RESQML2_NS::GridConnectionSetRepresentation* createGridConnectionSetRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp,
			const std::string & guid, const std::string & title);

		//************* PROPERTIES ***********

		DLL_IMPORT_OR_EXPORT RESQML2_NS::TimeSeries* createTimeSeries(const std::string & guid, const std::string & title);

		DLL_IMPORT_OR_EXPORT RESQML2_0_1_NS::StringTableLookup* createStringTableLookup(const std::string & guid, const std::string & title);

		DLL_IMPORT_OR_EXPORT COMMON_NS::PropertyKind* createPropertyKind(const std::string & guid, const std::string & title,
			const std::string & namingSystem, const gsoap_resqml2_0_1::resqml20__ResqmlUom & uom, const gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind & parentEnergisticsPropertyKind);

		DLL_IMPORT_OR_EXPORT COMMON_NS::PropertyKind* createPropertyKind(const std::string & guid, const std::string & title,
			const std::string & namingSystem, const gsoap_resqml2_0_1::resqml20__ResqmlUom & uom, COMMON_NS::PropertyKind * parentPropType);

		DLL_IMPORT_OR_EXPORT COMMON_NS::PropertyKind* createPropertyKind(const std::string & guid, const std::string & title,
			const std::string & namingSystem, const std::string & nonStandardUom, const gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind & parentEnergisticsPropertyKind);

		DLL_IMPORT_OR_EXPORT COMMON_NS::PropertyKind* createPropertyKind(const std::string & guid, const std::string & title,
			const std::string & namingSystem, const std::string & nonStandardUom, COMMON_NS::PropertyKind * parentPropType);

		/**
		* Create an EML2.1 property kind
		*/
		DLL_IMPORT_OR_EXPORT COMMON_NS::PropertyKind* createPropertyKind(const std::string & guid, const std::string & title,
			gsoap_eml2_1::eml21__QuantityClassKind quantityClass, bool isAbstract = false, COMMON_NS::PropertyKind* parentPropertyKind = nullptr);

		DLL_IMPORT_OR_EXPORT RESQML2_NS::PropertySet* createPropertySet(const std::string & guid, const std::string & title,
			bool hasMultipleRealizations, bool hasSinglePropertyKind, gsoap_resqml2_0_1::resqml20__TimeSetKind timeSetKind);

		DLL_IMPORT_OR_EXPORT RESQML2_0_1_NS::CommentProperty* createCommentProperty(RESQML2_NS::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			const unsigned int & dimension, const gsoap_resqml2_0_1::resqml20__IndexableElements & attachmentKind, const gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind & energisticsPropertyKind);

		DLL_IMPORT_OR_EXPORT RESQML2_0_1_NS::CommentProperty* createCommentProperty(RESQML2_NS::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			const unsigned int & dimension, const gsoap_resqml2_0_1::resqml20__IndexableElements & attachmentKind, COMMON_NS::PropertyKind * localPropType);

		DLL_IMPORT_OR_EXPORT RESQML2_0_1_NS::ContinuousProperty* createContinuousProperty(RESQML2_NS::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			const unsigned int & dimension, const gsoap_resqml2_0_1::resqml20__IndexableElements & attachmentKind, const gsoap_resqml2_0_1::resqml20__ResqmlUom & uom, const gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind & energisticsPropertyKind);

		DLL_IMPORT_OR_EXPORT RESQML2_0_1_NS::ContinuousProperty* createContinuousProperty(RESQML2_NS::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			const unsigned int & dimension, const gsoap_resqml2_0_1::resqml20__IndexableElements & attachmentKind, const gsoap_resqml2_0_1::resqml20__ResqmlUom & uom, COMMON_NS::PropertyKind * localPropType);

		DLL_IMPORT_OR_EXPORT RESQML2_0_1_NS::ContinuousProperty* createContinuousProperty(RESQML2_NS::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			const unsigned int & dimension, const gsoap_resqml2_0_1::resqml20__IndexableElements & attachmentKind, const std::string & nonStandardUom, const gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind & energisticsPropertyKind);

		DLL_IMPORT_OR_EXPORT RESQML2_0_1_NS::ContinuousProperty* createContinuousProperty(RESQML2_NS::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			const unsigned int & dimension, const gsoap_resqml2_0_1::resqml20__IndexableElements & attachmentKind, const std::string & nonStandardUom, COMMON_NS::PropertyKind * localPropType);

		DLL_IMPORT_OR_EXPORT RESQML2_0_1_NS::ContinuousPropertySeries* createContinuousPropertySeries(RESQML2_NS::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			const unsigned int & dimension, const gsoap_resqml2_0_1::resqml20__IndexableElements & attachmentKind, const gsoap_resqml2_0_1::resqml20__ResqmlUom & uom, const gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind & energisticsPropertyKind,
			RESQML2_NS::TimeSeries * ts, const bool & useInterval = false);

		DLL_IMPORT_OR_EXPORT RESQML2_0_1_NS::ContinuousPropertySeries* createContinuousPropertySeries(RESQML2_NS::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			const unsigned int & dimension, const gsoap_resqml2_0_1::resqml20__IndexableElements & attachmentKind, const gsoap_resqml2_0_1::resqml20__ResqmlUom & uom, COMMON_NS::PropertyKind * localPropType,
			RESQML2_NS::TimeSeries * ts, const bool & useInterval = false);

		DLL_IMPORT_OR_EXPORT RESQML2_0_1_NS::DiscreteProperty* createDiscreteProperty(RESQML2_NS::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			const unsigned int & dimension, const gsoap_resqml2_0_1::resqml20__IndexableElements & attachmentKind, const gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind & energisticsPropertyKind);

		DLL_IMPORT_OR_EXPORT RESQML2_0_1_NS::DiscreteProperty* createDiscreteProperty(RESQML2_NS::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			const unsigned int & dimension, const gsoap_resqml2_0_1::resqml20__IndexableElements & attachmentKind, COMMON_NS::PropertyKind * localPropType);

		DLL_IMPORT_OR_EXPORT RESQML2_0_1_NS::DiscretePropertySeries* createDiscretePropertySeries(RESQML2_NS::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			const unsigned int & dimension, const gsoap_resqml2_0_1::resqml20__IndexableElements & attachmentKind, const gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind & energisticsPropertyKind,
			RESQML2_NS::TimeSeries * ts, const bool & useInterval = false);

		DLL_IMPORT_OR_EXPORT RESQML2_0_1_NS::DiscretePropertySeries* createDiscretePropertySeries(RESQML2_NS::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			const unsigned int & dimension, const gsoap_resqml2_0_1::resqml20__IndexableElements & attachmentKind, COMMON_NS::PropertyKind * localPropType,
			RESQML2_NS::TimeSeries * ts, const bool & useInterval = false);

		DLL_IMPORT_OR_EXPORT RESQML2_0_1_NS::CategoricalProperty* createCategoricalProperty(RESQML2_NS::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			const unsigned int & dimension, const gsoap_resqml2_0_1::resqml20__IndexableElements & attachmentKind,
			RESQML2_0_1_NS::StringTableLookup* strLookup, const gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind & energisticsPropertyKind);

		DLL_IMPORT_OR_EXPORT RESQML2_0_1_NS::CategoricalProperty* createCategoricalProperty(RESQML2_NS::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			const unsigned int & dimension, const gsoap_resqml2_0_1::resqml20__IndexableElements & attachmentKind,
			RESQML2_0_1_NS::StringTableLookup* strLookup, COMMON_NS::PropertyKind * localPropType);

		DLL_IMPORT_OR_EXPORT RESQML2_0_1_NS::CategoricalPropertySeries* createCategoricalPropertySeries(RESQML2_NS::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			const unsigned int & dimension, const gsoap_resqml2_0_1::resqml20__IndexableElements & attachmentKind,
			RESQML2_0_1_NS::StringTableLookup* strLookup, const gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind & energisticsPropertyKind,
			RESQML2_NS::TimeSeries * ts, const bool & useInterval = false);

		DLL_IMPORT_OR_EXPORT RESQML2_0_1_NS::CategoricalPropertySeries* createCategoricalPropertySeries(RESQML2_NS::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			const unsigned int & dimension, const gsoap_resqml2_0_1::resqml20__IndexableElements & attachmentKind,
			RESQML2_0_1_NS::StringTableLookup* strLookup, COMMON_NS::PropertyKind * localPropType,
			RESQML2_NS::TimeSeries * ts, const bool & useInterval = false);

		//************* ACTIVITIES ***********

		DLL_IMPORT_OR_EXPORT RESQML2_NS::ActivityTemplate* createActivityTemplate(const std::string & guid, const std::string & title);

		DLL_IMPORT_OR_EXPORT RESQML2_NS::Activity* createActivity(RESQML2_NS::ActivityTemplate* activityTemplate, const std::string & guid, const std::string & title);

		//*************** WITSML *************

#if WITH_EXPERIMENTAL
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
			const std::string & title);
#endif
		DLL_IMPORT_OR_EXPORT WITSML2_0_NS::Well* createWell(const std::string & guid,
			const std::string & title);

		DLL_IMPORT_OR_EXPORT WITSML2_0_NS::Well* createWell(const std::string & guid,
			const std::string & title,
			const std::string & operator_,
			gsoap_eml2_1::eml21__WellStatus statusWell,
			gsoap_eml2_1::witsml20__WellDirection directionWell
		);

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

		DLL_IMPORT_OR_EXPORT WITSML2_0_NS::WellboreGeometry* createWellboreGeometry(WITSML2_0_NS::Wellbore* witsmlWellbore,
			const std::string & guid,
			const std::string & title,
			gsoap_eml2_1::witsml20__ChannelStatus channelStatus);

		DLL_IMPORT_OR_EXPORT WITSML2_0_NS::Trajectory* createTrajectory(WITSML2_0_NS::Wellbore* witsmlWellbore,
			const std::string & guid,
			const std::string & title,
			gsoap_eml2_1::witsml20__ChannelStatus channelStatus);

		DLL_IMPORT_OR_EXPORT WITSML2_0_NS::Log* createLog(WITSML2_0_NS::Wellbore* witsmlWellbore,
			const std::string & guid,
			const std::string & title);

		DLL_IMPORT_OR_EXPORT WITSML2_0_NS::ChannelSet* createChannelSet(
			const std::string & guid,
			const std::string & title);

		DLL_IMPORT_OR_EXPORT WITSML2_0_NS::Channel* createChannel(COMMON_NS::PropertyKind * propertyKind,
			const std::string & guid, const std::string & title,
			const std::string & mnemonic, gsoap_eml2_1::eml21__UnitOfMeasure uom, gsoap_eml2_1::witsml20__EtpDataType dataType, gsoap_eml2_1::witsml20__ChannelStatus growingStatus,
			const std::string & timeDepth, const std::string & loggingCompanyName);

		//*************** PRODML *************

		DLL_IMPORT_OR_EXPORT PRODML2_1_NS::FluidSystem* createFluidSystem(const std::string & guid,
			const std::string & title,
			double temperatureValue, gsoap_eml2_2::eml22__ThermodynamicTemperatureUom temperatureUom,
			double pressureValue, gsoap_eml2_2::eml22__PressureUom pressureUom,
			gsoap_eml2_2::prodml21__ReservoirFluidKind reservoirFluidKind,
			double gasOilRatio, gsoap_eml2_2::eml22__VolumePerVolumeUom gasOilRatioUom);

		DLL_IMPORT_OR_EXPORT PRODML2_1_NS::FluidCharacterization* createFluidCharacterization(const std::string & guid, const std::string & title);

		//************************************
		//************ EML2.3 ****************
		//************************************

#if WITH_EXPERIMENTAL
		DLL_IMPORT_OR_EXPORT GraphicalInformationSet* createGraphicalInformationSet(const std::string & guid, const std::string & title);

		DLL_IMPORT_OR_EXPORT RESQML2_2_NS::DiscreteColorMap* createDiscreteColorMap(const std::string& guid, const std::string& title);

		DLL_IMPORT_OR_EXPORT RESQML2_2_NS::ContinuousColorMap* createContinuousColorMap(const std::string& guid, const std::string& title,
			gsoap_eml2_3::resqml22__InterpolationDomain interpolationDomain, gsoap_eml2_3::resqml22__InterpolationMethod interpolationMethod);
#endif

		//************************************
		//***** STANDARD PROP KIND ***********
		//************************************

		/**
		* Get the property kind mapper if given at repository construction time.
		* Else return NULL.
		*/
		DLL_IMPORT_OR_EXPORT RESQML2_0_1_NS::PropertyKindMapper* getPropertyKindMapper() const { return propertyKindMapper; }

		//************************************
		//************* WARNINGS *************
		//************************************

		DLL_IMPORT_OR_EXPORT void clearWarnings() { warnings.clear();  }
		DLL_IMPORT_OR_EXPORT void addWarning(const std::string & warning);
		DLL_IMPORT_OR_EXPORT const std::vector<std::string> & getWarnings() const;

		//*********** TRANSACTION ***********

		/**
		* Creates a transaction.
		* The transactionis actually a child dataobject repository which will be merged into this master dataobject repository.
		*/
		DataObjectRepository* newTransactionRepo();

		/**
		* Commit a transaction into this master repository.
		*/
		void commitTransactionRepo(DataObjectRepository* transactionRepo);


	private:

		/**
		* The key is the UUID.
		* The value is a vector storing all various versions of this data object
		*/
		std::unordered_map< std::string, std::vector< COMMON_NS::AbstractObject* > > dataObjects;

		// Forward relationships
		std::unordered_map< COMMON_NS::AbstractObject const *, std::vector< COMMON_NS::AbstractObject * > > forwardRels;

		// Backward relationships. It is redundant with forward relationships but it allows more performance.
		std::unordered_map< COMMON_NS::AbstractObject const *, std::vector< COMMON_NS::AbstractObject * > > backwardRels;

		soap* gsoapContext;

		std::vector<std::string> warnings;

		RESQML2_0_1_NS::PropertyKindMapper* propertyKindMapper;

		COMMON_NS::AbstractHdfProxy* defaultHdfProxy;
		RESQML2_NS::AbstractLocal3dCrs* defaultCrs;

		std::vector<COMMON_NS::DataFeeder*> dataFeeders;

		COMMON_NS::HdfProxyFactory* hdfProxyFactory;

		std::vector< std::tuple<std::chrono::time_point<std::chrono::system_clock>, DataObjectIdentifier, CUD> > journal;

		/**
		* Necessary to avoid a dependency on GuidTools.h
		*/
		std::string generateRandomUuidAsString() const;

		/**
		* Set the stream of the curent gsoap context.
		*/
		void setGsoapStream(std::istream * inputStream) { gsoapContext->is = inputStream; }

		/**
		* Read the Gsoap proxy from the stream associated to the current gsoap context and wrap this gsoap proxy into a fesapi wrapper.
		* It does not add this fesapi wrapper to the current instance.
		* It does not work for EpcExternalPartReference content type since this type is related to an external file which must be handled differently.
		*/
		COMMON_NS::AbstractObject* getResqml2_0_1WrapperFromGsoapContext(const std::string & resqmlContentType);
#if WITH_EXPERIMENTAL
		COMMON_NS::AbstractObject* getResqml2_2WrapperFromGsoapContext(const std::string& resqmlContentType);

		COMMON_NS::AbstractObject* getEml2_3WrapperFromGsoapContext(const std::string& datatype);
#endif

		COMMON_NS::AbstractObject* getWitsml2_0WrapperFromGsoapContext(const std::string & datatype);
		COMMON_NS::AbstractObject* getProdml2_1WrapperFromGsoapContext(const std::string & datatype);

		/**
		* Get the error code of the current gsoap context.
		*/
		int getGsoapErrorCode() const;

		/**
		* Get the error message (if any) of the current gsoap context.
		*/
		std::string getGsoapErrorMessage() const;

		template <class valueType>
		std::vector<valueType *> getObjsFilteredOnDatatype(const std::vector< COMMON_NS::AbstractObject * >& objs) const
		{
			std::vector<valueType *> result;
			for (size_t i = 0; i < objs.size(); ++i) {
				valueType * castedObj = dynamic_cast<valueType *>(objs[i]);
				if (castedObj != nullptr) {
					result.push_back(castedObj);
				}
			}
			return result;
		}

		DLL_IMPORT_OR_EXPORT gsoap_resqml2_0_1::eml20__DataObjectReference* createDor(const std::string & guid, const std::string & title, const std::string & version);

		void replaceDataObjectInRels(COMMON_NS::AbstractObject* dataObjToReplace, COMMON_NS::AbstractObject* newDataObj);
	};
}
