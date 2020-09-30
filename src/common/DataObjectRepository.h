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
#include <limits>

#include "DataObjectReference.h"

namespace EML2_NS
{
	class AbstractHdfProxy;
	class Activity;
	class ActivityTemplate;
	class GraphicalInformationSet;
	class PropertyKind;
	class TimeSeries;
}

namespace RESQML2_NS
{
	class AbstractFeature;
	class AbstractFeatureInterpretation;
	class AbstractIjkGridRepresentation;
	class AbstractLocal3dCrs;
	class AbstractOrganizationInterpretation;
	class AbstractRepresentation;
	class AbstractSeismicLineFeature;
	class BlockedWellboreRepresentation;
	class BoundaryFeature;
	class BoundaryFeatureInterpretation;
	class CategoricalProperty;
	class CmpLineFeature;
	class CommentProperty;
	class ContinuousColorMap;
	class ContinuousProperty;
	class CulturalFeature;
	class DiscreteColorMap;
	class DiscreteProperty;
	class DeviationSurveyRepresentation;
	class DoubleTableLookup;
	class EarthModelInterpretation;
	class FaultInterpretation;
	class GenericFeatureInterpretation;
	class GeobodyBoundaryInterpretation;
	class GeobodyInterpretation;
	class GridConnectionSetRepresentation;
	class Grid2dRepresentation;
	class HorizonInterpretation;
	class IjkGridExplicitRepresentation;
	class IjkGridLatticeRepresentation;
	class IjkGridNoGeometryRepresentation;
	class IjkGridParametricRepresentation;
	class LocalDepth3dCrs;
	class LocalTime3dCrs;
	class MdDatum;
	class Model;
	class NonSealedSurfaceFrameworkRepresentation;
	class PlaneSetRepresentation;
	class PointSetRepresentation;
	class PointsProperty;
	class PolylineRepresentation;
	class PolylineSetRepresentation;
	class PropertySet;
	class RepresentationSetRepresentation;
	class RockFluidOrganizationInterpretation;
	class RockFluidUnitInterpretation;
	class RockVolumeFeature;
	class SealedSurfaceFrameworkRepresentation;
	class SealedVolumeFrameworkRepresentation;
	class SeismicLatticeFeature;
	class SeismicLineSetFeature;
	class SeismicWellboreFrameRepresentation;
	class ShotPointLineFeature;
	class StratigraphicColumn;
	class StratigraphicColumnRankInterpretation;
	class StratigraphicOccurrenceInterpretation;
	class StratigraphicUnitInterpretation;
	class StringTableLookup;
	class StructuralOrganizationInterpretation;
	class SubRepresentation;
	class TriangulatedSetRepresentation;
	class UnstructuredGridRepresentation;
	class WellboreFeature;
	class WellboreFrameRepresentation;
	class WellboreInterpretation;
	class WellboreMarker;
	class WellboreMarkerFrameRepresentation;
	class WellboreTrajectoryRepresentation;
}

namespace RESQML2_0_1_NS
{
	class PropertyKindMapper;
	class CategoricalProperty;
	class CommentProperty;
	class ContinuousProperty;
	class DiscreteProperty;
	class FluidBoundaryFeature;
	class GeneticBoundaryFeature;
	class GeobodyFeature;
	class Horizon;
	class PointsProperty;
	class PropertyKind;
	class RockFluidUnitFeature;
	class SeismicLineFeature;
	class TectonicBoundaryFeature;
}

namespace WITSML2_0_NS
{
	class AbstractObject;
	class Well;
	class WellCompletion;
	class Wellbore;
	class WellboreCompletion;
	class WellboreGeometry;
	class WellboreMarker;
	class Trajectory;
	class Log;
	class ChannelSet;
	class Channel;
}

namespace PRODML2_1_NS
{
	class FluidSystem;
	class FluidCharacterization;
	class TimeSeriesData;
}

namespace COMMON_NS
{
	class AbstractObject;
	class DataFeeder;
	class HdfProxyFactory;

	/**
	 * @brief	This abstract class acts as a buffer between the RESQML (business) classes and the
	 * 			persisted data.
	 */
	class DataObjectRepository
	{
	public:

		/** Default constructor */
		DLL_IMPORT_OR_EXPORT DataObjectRepository();

		/**
		 * Constructor
		 *
		 * @param 	propertyKindMappingFilesDirectory	Pathname of the property kind mapping files
		 * 												directory.
		 */
		DLL_IMPORT_OR_EXPORT DataObjectRepository(const std::string & propertyKindMappingFilesDirectory);

		/** Destructor */
		DLL_IMPORT_OR_EXPORT virtual ~DataObjectRepository();

		/** Values that represent the HDF5 file permission access */
		enum class openingMode : std::int8_t {
			READ_ONLY = 0, // It is meant to open an existing file in read only mode. It throws an exception if the file does not exist.
			READ_WRITE = 1, // It is meant to open a file in read and write mode. It creates the file if the file does not exist.
			READ_WRITE_DO_NOT_CREATE = 2, // It is meant to open an existing file in read and write mode. It throws an exception if the file does not exist.
			OVERWRITE = 3 // It is meant to open an existing file in read and write mode. It deletes the content of the file if the later does already exist.
		};
		enum CUD { CREATED = 0, UPDATED = 1, DELETED = 2 };

		/**
		* Enumeration for the various Energistics standards.
		*/
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

		/**
		 * Gets the gSOAP context.
		 *
		 * @returns	The gSOAP context.
		 */
		soap* getGsoapContext() const { return gsoapContext; }

		/**
		* Set the used standard when creating a new dataobject
		*/
		DLL_IMPORT_OR_EXPORT void setDefaultStandard(EnergisticsStandard version) {
			switch (version) {
			case EnergisticsStandard::PRODML2_1:
				defaultProdmlVersion = version; break;
			case EnergisticsStandard::RESQML2_0_1:
			case EnergisticsStandard::RESQML2_2:
				defaultResqmlVersion = version; break;
			case EnergisticsStandard::WITSML2_0:
				defaultWitsmlVersion = version; break;
			case EnergisticsStandard::EML2_0:
			case EnergisticsStandard::EML2_1:
			case EnergisticsStandard::EML2_2:
			case EnergisticsStandard::EML2_3:
				defaultEmlVersion = version; break;
			default :
				throw std::invalid_argument("Unrecognized Energistics standard.");
			}
		}

		/**
		* Gets the default EML version used when creating a EML data object.
		*
		* @returns The default EML version.
		*/
		EnergisticsStandard getDefaultEmlVersion() const { return defaultEmlVersion; }

		/**
		* Gets the default PRODML version used when creating a PRODML data object.
		* 
		* @returns The default PRODML version.
		*/
		EnergisticsStandard getDefaultProdmlVersion() const { return defaultProdmlVersion; }

		/**
		* Gets the default RESQML version used when creating a RESQML data object.
		* 
		* @returns The default RESQML version.
		*/
		EnergisticsStandard getDefaultResqmlVersion() const { return defaultResqmlVersion; }

		/**
		* Gets the default WITSML version used when creating a WITSML data object.
		* 
		* @returns The default WITSML version.
		*/
		EnergisticsStandard getDefaultWitsmlVersion() const { return defaultWitsmlVersion; }

		/** Removes and cleans all data objects from this repository */
		DLL_IMPORT_OR_EXPORT void clear();

		/**
		 * Adds a directed relationship between two objects. Source and target of the relationship are
		 * defined by the Energistics data model. Usually, the easiest way is to look at Energistics UML
		 * diagrams. Another way is to rely on XSD/XML: explicit relationships are contained by the
		 * source objects and point to target objects.
		 *
		 * @exception	std::invalid_argument	if the source or target object is null.  
		 *
		 * @param [in]	source	The source object of the relationship.
		 * @param [in]	target	The target object of the relationship.
		 */
		DLL_IMPORT_OR_EXPORT void addRelationship(COMMON_NS::AbstractObject * source, COMMON_NS::AbstractObject * target);

		/**
		* Register a data feeder to allow partial objects resolution.
		* It is your responsability to manage the memory of your data feeder. DataObject repository won't never free memory of a data feeder.
		*/
		DLL_IMPORT_OR_EXPORT void registerDataFeeder(COMMON_NS::DataFeeder * dataFeeder);

		/*
		 * Delete a relationship between two objects. Source and target of the relationship are defined
		 * by Energistics data model. Usually, the simplest is to look at Energistics UML diagrams. 
		 * Another way is to rely on XSD/XML: explicit relationships are contained by the source objects
		 * and point to target objects.
		 * 
		 * @exception	std::invalid_argument	if the source or target object is null.
		 *
		 * @param [in]	source	The source object of the relationship.
		 * @param [in]	target	The target object of the relationship.
		 */
		DLL_IMPORT_OR_EXPORT void deleteRelationship(COMMON_NS::AbstractObject * source, COMMON_NS::AbstractObject * target);

		/**
		* Set the factory used to create HDF proxy and takes ownership of this HDF Proxy factory (don't delete it!)
		* 
		* @param [in]	factory	If non-null, the factory.
		*/
		DLL_IMPORT_OR_EXPORT void setHdfProxyFactory(COMMON_NS::HdfProxyFactory * factory);

		/**
		* Get the journal of the DataObject repository.
		*/
		const std::vector< std::tuple<std::chrono::time_point<std::chrono::system_clock>, COMMON_NS::DataObjectReference, CUD> >& getJournal() const { return journal; }

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

		/**
		 * Gets the @p valueType typed target objects of a particular data object.
		 *
		 * @exception	std::out_of_range	If the target objects have not been defined yet.
		 * 									
		 * @tparam	valueType	The type of target objects we look for.
		 * @param 	dataObj		The data object.
		 *
		 * @returns	A vector of pointers to all target objects.
		 */
		template <class valueType>
		std::vector<valueType *> getTargetObjects(COMMON_NS::AbstractObject const * dataObj) const
		{
			return getObjsFilteredOnDatatype<valueType>(getTargetObjects(dataObj));
		}

		/**
		 * Gets the source objects of a particular data object
		 *
		 * @exception	std::out_of_range	If the source objects have not been defined yet.
		 *
		 * @param 	dataObj	The data object.
		 *
		 * @returns	A vector of pointers to all source objects.
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

		/**
		 * Gets the @p valueType typed source objects
		 *
		 * @exception	std::out_of_range	If the source objects have not been defined yet.
		 * 									
		 * @tparam	valueType	The type of source objects we look for.
		 * @param 	dataObj		The data object.
		 *
		 * @returns	A vector of pointer to all source objects.
		 */
		template <class valueType>
		std::vector<valueType *> getSourceObjects(COMMON_NS::AbstractObject const * dataObj) const
		{
			const std::vector < COMMON_NS::AbstractObject*> & sourceObjects = getSourceObjects(dataObj);

			return getObjsFilteredOnDatatype<valueType>(sourceObjects);
		}

		/** Update all the relationships of the data objects contained in this repository */
		DLL_IMPORT_OR_EXPORT void updateAllRelationships();

		/**
		 * Adds or replaces (based on UUID and version) a data object in the repository. It does not
		 * update the relationships of the added or replaced data object
		 *
		 * @exception	std::invalid_argument	If, during a replacement, the content type of the data
		 * 										object has changed.
		 *
		 * @param [in, out]	proxy	The data object to add or to replace.
		 * @param replaceOnlyContent	If true, it does not replace the full object(not the pointer) but only replace the content of the object.
		 */
		DLL_IMPORT_OR_EXPORT COMMON_NS::AbstractObject* addOrReplaceDataObject(COMMON_NS::AbstractObject* proxy, bool replaceOnlyContent = false);

		/**
		 * Adds or replaces (based on Energistics XML definition) a data object in the repository. It
		 * does not update the relationships of the added or replaced data object
		 *
		 * @exception	std::invalid_argument	If, during a replacement, the content type of the data
		 * 										object has changed.
		 *
		 * @param 	xml		   	The XML which is the serialization of the Energistics data object to add
		 * 						or to replace.
		 * @param 	contentOrDataType	The content or qualified data type of the Energistics dataobject to add or to replace.
		 *
		 * @returns	Null if the content type of the data object cannot be wrapped by fesapi, else a
		 * 			pointer the added or replaced data object.
		 */
		DLL_IMPORT_OR_EXPORT COMMON_NS::AbstractObject* addOrReplaceGsoapProxy(const std::string & xml, const std::string & contentType);

		/**
		 * Gets all the data objects which are part of this repository
		 *
		 * @returns	A map where the key is the UUID of a data object and the value is a vector of
		 * 			pointers to all different versions of this data object.
		 */
		const std::unordered_map< std::string, std::vector< COMMON_NS::AbstractObject* > > & getDataObjects() const { return dataObjects; }

		/**
		 * Gets all the data object and groups them by datatype
		 *
		 * @returns	A map where the key is a content type and the value is a vector of pointers to all
		 * 			data objects of this datatype.
		 */
		DLL_IMPORT_OR_EXPORT std::unordered_map< std::string, std::vector<COMMON_NS::AbstractObject*> > getDataObjectsGroupedByDataType() const;

		/**
		* Group Data objects of the repository by datatype based on a filtered list 
		* @param filter A string that the returned Dataobject must contain in their datatype.
		* @return A map where the key is a datatype and where the value is the collection of Data objects of this datatype
		*/
		DLL_IMPORT_OR_EXPORT std::unordered_map< std::string, std::vector<COMMON_NS::AbstractObject*> > getDataObjectsGroupedByDataType(const std::string & filter) const;

		/**
		 * Gets all the data objects which honor a given content type
		 *
		 * @param 	contentType	A content type.
		 *
		 * @returns	A vector of pointers to all data objects in this repository which honor the content type.
		 */
		DLL_IMPORT_OR_EXPORT std::vector<COMMON_NS::AbstractObject*> getDataObjectsByContentType(const std::string & contentType) const;

		/**
		 * Gets all the data objects of a particular @p valueType type
		 *
		 * @tparam	valueType	The type of data objects we look for.
		 *
		 * @returns	A vector of pointers to all @p valueType typed data object in this repository.
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
		 * Gets the default CRS for writing. It is used in all writing methods if no explicit CRS is
		 * provided.
		 *
		 * @returns	A pointer to the default CRS if it is defined, else null.
		 */
		DLL_IMPORT_OR_EXPORT RESQML2_NS::AbstractLocal3dCrs* getDefaultCrs() const { return defaultCrs; }

		/**
		 * Sets a default CRS for writing. It will be used in all writing methods if no explicit CRS is
		 * provided
		 *
		 * @param [in]	crs	If non-null, the default CRS.
		 */
		DLL_IMPORT_OR_EXPORT void setDefaultCrs(RESQML2_NS::AbstractLocal3dCrs* crs) { defaultCrs = crs; }

		/**
		 * Gets the default HDF5 file proxy for writing. It is used in all writing methods if no
		 * explicit HDF5 file proxy is provided.
		 *
		 * @returns	@c nullptr if no default HDF5 file proxy is defined, else a pointer to the default HDF5 file proxy.
		 */
		DLL_IMPORT_OR_EXPORT EML2_NS::AbstractHdfProxy* getDefaultHdfProxy() const { return defaultHdfProxy; }

		/**
		 * Sets a default HDF5 file proxy for writing. It will be used in all writing methods if no
		 * explicit HDF5 file proxy is provided.
		 *
		 * @param [in]	hdfProxy	If non-null, the HDF5 file proxy.
		 */
		DLL_IMPORT_OR_EXPORT void setDefaultHdfProxy(EML2_NS::AbstractHdfProxy* hdfProxy) { defaultHdfProxy = hdfProxy; }

		/**
		* This macro allows vector and array access at the same time. Array access is necessary for SWIG.
		*/
#define GETTER_DATAOBJECTS(returnedDataType, dataObjectName)\
		DLL_IMPORT_OR_EXPORT std::vector<returnedDataType*> get##dataObjectName##Set() const;\
		DLL_IMPORT_OR_EXPORT unsigned int get##dataObjectName##Count() const {\
			const size_t result = get##dataObjectName##Set().size();\
			if (result > (std::numeric_limits<unsigned int>::max)()) { throw std::range_error("The count is superior to unsigned int max"); }\
			return static_cast<unsigned int>(result);\
		}\
		DLL_IMPORT_OR_EXPORT returnedDataType* get##dataObjectName(unsigned int index) const {\
			std::vector<returnedDataType*> all = get##dataObjectName##Set();\
			if (index >= all.size()) { throw std::out_of_range("The index is out of range"); }\
			return all[index];\
		}

		GETTER_DATAOBJECTS(EML2_NS::TimeSeries, TimeSeries)
		GETTER_DATAOBJECTS(EML2_NS::AbstractHdfProxy, HdfProxy)

		GETTER_DATAOBJECTS(RESQML2_NS::LocalDepth3dCrs, LocalDepth3dCrs)
		GETTER_DATAOBJECTS(RESQML2_NS::LocalTime3dCrs, LocalTime3dCrs)
		GETTER_DATAOBJECTS(RESQML2_NS::StratigraphicColumn, StratigraphicColumn)
		GETTER_DATAOBJECTS(RESQML2_NS::BoundaryFeature, Fault)
		GETTER_DATAOBJECTS(RESQML2_NS::BoundaryFeature, Fracture)
		GETTER_DATAOBJECTS(RESQML2_NS::BoundaryFeature, Horizon)
		GETTER_DATAOBJECTS(RESQML2_NS::BoundaryFeature, GeobodyBoundary)
		GETTER_DATAOBJECTS(RESQML2_NS::RockVolumeFeature, Geobody)
		GETTER_DATAOBJECTS(RESQML2_NS::PolylineSetRepresentation, FaultPolylineSetRep)
		GETTER_DATAOBJECTS(RESQML2_NS::PolylineSetRepresentation, FracturePolylineSetRep)
		GETTER_DATAOBJECTS(RESQML2_NS::PolylineSetRepresentation, CulturalPolylineSetRep)
		GETTER_DATAOBJECTS(RESQML2_NS::TriangulatedSetRepresentation, FaultTriangulatedSetRep)
		GETTER_DATAOBJECTS(RESQML2_NS::TriangulatedSetRepresentation, FractureTriangulatedSetRep)
		GETTER_DATAOBJECTS(RESQML2_NS::Grid2dRepresentation, HorizonGrid2dRep)
		GETTER_DATAOBJECTS(RESQML2_NS::PolylineRepresentation, HorizonPolylineRep)
		GETTER_DATAOBJECTS(RESQML2_NS::PolylineSetRepresentation, HorizonPolylineSetRep)
		GETTER_DATAOBJECTS(RESQML2_NS::TriangulatedSetRepresentation, HorizonTriangulatedSetRep)
		GETTER_DATAOBJECTS(RESQML2_NS::TriangulatedSetRepresentation, UnclassifiedTriangulatedSetRep)
		GETTER_DATAOBJECTS(RESQML2_NS::TriangulatedSetRepresentation, AllTriangulatedSetRep)
		GETTER_DATAOBJECTS(RESQML2_NS::Grid2dRepresentation, AllGrid2dRepresentation)
		GETTER_DATAOBJECTS(RESQML2_NS::PolylineRepresentation, AllPolylineRepresentation)
		GETTER_DATAOBJECTS(RESQML2_NS::PolylineSetRepresentation, AllPolylineSetRep)
		GETTER_DATAOBJECTS(RESQML2_NS::AbstractSeismicLineFeature, SeismicLine)
		GETTER_DATAOBJECTS(RESQML2_NS::PolylineRepresentation, SeismicLinePolylineRep)
		GETTER_DATAOBJECTS(RESQML2_NS::WellboreFeature, Wellbore)
		GETTER_DATAOBJECTS(RESQML2_NS::WellboreTrajectoryRepresentation, WellboreTrajectoryRepresentation)
		GETTER_DATAOBJECTS(RESQML2_NS::DeviationSurveyRepresentation, DeviationSurveyRepresentation)
		GETTER_DATAOBJECTS(RESQML2_NS::RepresentationSetRepresentation, RepresentationSetRepresentation)
		GETTER_DATAOBJECTS(RESQML2_NS::AbstractIjkGridRepresentation, IjkGridRepresentation)
		GETTER_DATAOBJECTS(RESQML2_NS::IjkGridParametricRepresentation, IjkGridParametricRepresentation)
		GETTER_DATAOBJECTS(RESQML2_NS::IjkGridExplicitRepresentation, IjkGridExplicitRepresentation)
		GETTER_DATAOBJECTS(RESQML2_NS::IjkGridLatticeRepresentation, IjkSeismicCubeGridRepresentation)
		GETTER_DATAOBJECTS(RESQML2_NS::UnstructuredGridRepresentation, UnstructuredGridRepresentation)
		GETTER_DATAOBJECTS(RESQML2_NS::CulturalFeature, Cultural)
		GETTER_DATAOBJECTS(RESQML2_NS::Model, Model)
		GETTER_DATAOBJECTS(RESQML2_NS::SubRepresentation, SubRepresentation)
		GETTER_DATAOBJECTS(RESQML2_NS::PointSetRepresentation, PointSetRepresentation)

		/**
		 * Gets a data object from the repository by means of its uuid. If several data object
		 * correspond to this uuid in the repository, the first one in memory will be arbitrarily
		 * returned.
		 *
		 * @param 	uuid	The uuid of the requested data object.
		 *
		 * @returns	A pointer to the data object which corresponds to the uuid, @c nullptr if there exists no
		 * 			such data object.
		 */
		DLL_IMPORT_OR_EXPORT COMMON_NS::AbstractObject* getDataObjectByUuid(const std::string & uuid) const;

		/**
		 * Gets a data object from the repository by means of its uuid and try to cast it to @p valueType. 
		 * @p valueType must be a child of {@link AbstractObject}
		 *
		 * @exception	std::invalid_argument	If the uuid does not resolve to the expected @p
		 * 										valueType data type.
		 *
		 * @tparam	valueType	The data type to which the requested data object will be cast.
		 * @param 	uuid		The uuid of the requested data object.
		 *
		 * @returns	A pointer to the data object which corresponds to the uuid and cast to @p valueType, @c nullptr if
		 * 			there exists no such data object.
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
		 * Gets a data object from the repository by means of both its uuid and version.
		 *
		 * @param 	uuid   	The uuid of the requested data object.
		 * @param 	version	The version of the requested data object.
		 *
		 * @returns	A pointer to the data object which corresponds to both uuid and version, @c nullptr if there
		 * 			exists no such data object.
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
		 * Gets a data object from the repository by means of both its uuid and version and try to
		 * cast it to @p valueType. @p valueType must be a child of {@link AbstractObject}
		 *
		 * @exception	std::invalid_argument	If the combination of uuid and version does not
		 * 										resolve to the expected @p valueType data type.
		 *
		 * @tparam	valueType	The data type to which the requested data object will be cast.
		 * @param 	uuid   		The uuid of the requested data object.
		 * @param 	version		The version of the requested data object.
		 *
		 * @returns	A pointer to the data object which corresponds to both uuid and version and cast to 
		 * 			@p valueType, @c nullptr if there exists no such data object.
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
		 * Gets all the data object uuids which are part of this repository
		 *
		 * @returns	A vector of uuids.
		 */
		DLL_IMPORT_OR_EXPORT std::vector<std::string> getUuids() const;

		/**
		* Create a partial object i.e. a data object reference (DOR) based on an UUID + a title + a content type + a version
		*/
		COMMON_NS::AbstractObject* createPartial(const std::string & uuid, const std::string & title, const std::string & contentType, const std::string & version = "");

		/**
		 * Creates a partial object in this repository based on a data object reference.
		 *
		 * @exception	std::invalid_argument	If no partial object can be created from @p dor.
		 *
		 * @param 	dor	A data object reference.
		 *
		 * @returns	A pointer to the created partial object.
		 */
		COMMON_NS::AbstractObject* createPartial(const DataObjectReference& dor);

		/**
		 * Creates a partial object (i.e. a data object reference - or DOR - based on both uuid, title
		 * and version). Such an object is useful to describe the underlying data object by means of a
		 * minimal amount of information: uuid, title and version. However, such an object has often a
		 * lot of limitations when we want to access the data object.
		 *
		 * @tparam	valueType	The data type of the partial object to create.
		 * @param 	guid   	The guid to set to the partial object. If empty then a new guid
		 * 					will be generated.
		 * @param 	title  	The title of the partial object to create.
		 * @param 	version	(Optional) The version of the partial object to create.
		 *
		 * @returns	A pointer to the new partial object.
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
		 * Creates an EPC external part reference into this repository for 
		 * allowing the use of a different behavior for persisting numerical
		 * data. @p NumericalValueBase must be a child of {@link eml2::EpcExternalPartReference}
		 *
		 * @tparam	NumericalValueBase	Type of the numerical values.
		 * @param 	guid 	The guid to set to the EPC external part reference.
		 * @param 	title	The title to set to the EPC external part reference.
		 *
		 * @returns	A pointer to the new EPC external part reference.
		 */
		template <class NumericalValueBase>
		NumericalValueBase* createEpcExternalPartReference(const std::string & guid, const std::string & title)
		{
			NumericalValueBase* result = new NumericalValueBase(getGsoapContext(), guid);
			addDataObject(result);
			return result;
		}

		/**
		 * @brief	Creates a non parallel access to an HDF5 file for writing to it. Resulting HDF5 file
		 * 			proxy is stored into this repository
		 *
		 * @exception	std::invalid_argument	If the default RESQML version is unrecognized.
		 *
		 * @param 	guid				  	The guid to set to the HDF5 file proxy. If empty then a new
		 * 									guid will be generated.
		 * @param 	title				  	The title to set to the HDF5 file proxy. If empty then
		 * 									\"unknown\" title will be set.
		 * @param 	packageDirAbsolutePath	Path of the directory containing the EPC file.
		 * @param 	externalFilePath	  	Path of the HDF5 file relative to the directory where the EPC
		 * 									document is stored.
		 * @param 	hdfPermissionAccess   	The HDF5 file permission access. It is read
		 * 										only by default.
		 *
		 * @returns	A pointer to an instantiated HDF5 file proxy.
		 */
		DLL_IMPORT_OR_EXPORT EML2_NS::AbstractHdfProxy* createHdfProxy(const std::string & guid, const std::string & title, const std::string & packageDirAbsolutePath, const std::string & externalFilePath, DataObjectRepository::openingMode hdfPermissionAccess);

		//************ CRS *******************

		/**
		 * @brief	Creates a local depth 3d CRS which is fully identified by means of an EPSG code.
		 * 			Resulting local depth 3d CRS is stored into this repository
		 *
		 * @exception	std::invalid_argument	If the default RESQML version is unrecognized.
		 * @exception	std::invalid_argument	If <tt>projectedEpsgCode == 0 || verticalEpsgCode ==
		 * 										0</tt>.
		 *
		 * @param 	guid			 	The guid to set to the local 3d CRS. If empty then a new guid
		 * 								will be generated.
		 * @param 	title			 	The title to set to the local 3d CRS. If empty then \"unknown\"
		 * 								title will be set.
		 * @param 	originOrdinal1   	The offset of the global 2d CRS on its first axis.
		 * @param 	originOrdinal2   	The offset of the global 2d CRS on its second axis.
		 * @param 	originOrdinal3   	The offset in depth of the local CRS regarding the depth origin
		 * 								of the vertical CRS.
		 * @param 	arealRotation	 	The areal rotation in radians regarding the projected CRS.
		 * @param 	projectedUom	 	The unit of measure of the projected axis of this instance.
		 * @param 	projectedEpsgCode	The EPSG code of the associated projected CRS.
		 * @param 	verticalUom		 	The unit of measure of the vertical axis of this instance.
		 * @param 	verticalEpsgCode 	The EPSG code of the associated vertical CRS.
		 * @param 	isUpOriented	 	If true, indicates that this depth CRS is actually an elevation
		 * 								CRS.
		 *
		 * @returns	A pointer to the new local depth 3d CRS.
		 */
		DLL_IMPORT_OR_EXPORT RESQML2_NS::LocalDepth3dCrs* createLocalDepth3dCrs(const std::string & guid, const std::string & title,
			double originOrdinal1, double originOrdinal2, double originOrdinal3,
			double arealRotation,
			gsoap_resqml2_0_1::eml20__LengthUom projectedUom, unsigned long projectedEpsgCode,
			gsoap_resqml2_0_1::eml20__LengthUom verticalUom, unsigned int verticalEpsgCode, bool isUpOriented);

		/**
		 * @brief	Creates a local depth 3d CRS which is fully unknown. Resulting local depth 3d CRS is
		 * 			stored into this repository
		 *
		 * @exception	std::invalid_argument	If the default RESQML version is unrecognized.
		 *
		 * @param 	guid				  	The guid to set to the local 3d CRS. If empty then a new guid
		 * 									will be generated.
		 * @param 	title				  	The title to set to the local 3d CRS. If empty then
		 * 									\"unknown\" title will be set.
		 * @param 	originOrdinal1		  	The offset of the global 2d CRS on its first axis.
		 * @param 	originOrdinal2		  	The offset of the global 2d CRS on its second axis.
		 * @param 	originOrdinal3		  	The offset in depth of the local CRS regarding the depth
		 * 									origin of the vertical CRS.
		 * @param 	arealRotation		  	The areal rotation in radians regarding the projected CRS.
		 * @param 	projectedUom		  	The unit of measure of the projected axis of this instance.
		 * @param 	projectedUnknownReason	Indicates why the projected CRS cannot be provided using EPSG
		 * 									or GML.
		 * @param 	verticalUom			  	The unit of measure of the vertical axis of this instance.
		 * @param 	verticalUnknownReason 	Indicates why the vertical CRS cannot be provided using EPSG
		 * 									or GML.
		 * @param 	isUpOriented		  	If true, indicates that this depth CRS is actually an
		 * 									elevation CRS.
		 *
		 * @returns	A pointer to the new local depth 3d CRS.
		 */
		DLL_IMPORT_OR_EXPORT RESQML2_NS::LocalDepth3dCrs* createLocalDepth3dCrs(const std::string & guid, const std::string & title,
			double originOrdinal1, double originOrdinal2, double originOrdinal3,
			double arealRotation,
			gsoap_resqml2_0_1::eml20__LengthUom projectedUom, const std::string & projectedUnknownReason,
			gsoap_resqml2_0_1::eml20__LengthUom verticalUom, const std::string & verticalUnknownReason, bool isUpOriented);

		/**
		 * @brief	Creates a local depth 3d CRS which is identified by an EPSG code for its projected
		 * 			part and which is unknown for its vertical part. Resulting local depth 3d CRS is
		 * 			stored into this repository
		 *
		 * @exception	std::invalid_argument	If the default RESQML version is unrecognized.
		 * @exception	std::invalid_argument	If <tt>projectedEpsgCode == 0</tt>.
		 *
		 * @param 	guid				 	The guid to set to the local 3d CRS. If empty then a new guid
		 * 									will be generated.
		 * @param 	title				 	The title to set to the local 3d CRS. If empty then
		 * 									\"unknown\" title will be set.
		 * @param 	originOrdinal1		 	The offset of the global 2d CRS on its first axis.
		 * @param 	originOrdinal2		 	The offset of the global 2d CRS on its second axis.
		 * @param 	originOrdinal3		 	The offset in depth of the local CRS regarding the depth
		 * 									origin of the vertical CRS.
		 * @param 	arealRotation		 	The areal rotation in radians regarding the projected CRS.
		 * @param 	projectedUom		 	The unit of measure of the projected axis of this instance.
		 * @param 	projectedEpsgCode	 	The EPSG code of the associated projected CRS.
		 * @param 	verticalUom			 	The unit of measure of the vertical axis of this instance.
		 * @param 	verticalUnknownReason	Indicates why the vertical CRS cannot be provided using EPSG
		 * 									or GML.
		 * @param 	isUpOriented		 	If true, indicates that this depth CRS is actually an
		 * 									elevation CRS.
		 *
		 * @returns	A pointer to the new local depth 3d CRS.
		 */
		DLL_IMPORT_OR_EXPORT RESQML2_NS::LocalDepth3dCrs* createLocalDepth3dCrs(const std::string & guid, const std::string & title,
			double originOrdinal1, double originOrdinal2, double originOrdinal3,
			double arealRotation,
			gsoap_resqml2_0_1::eml20__LengthUom projectedUom, unsigned long projectedEpsgCode,
			gsoap_resqml2_0_1::eml20__LengthUom verticalUom, const std::string & verticalUnknownReason, bool isUpOriented);

		/**
		 * @brief	Creates a local depth 3d CRS which is unknown for its projected part and which is
		 * 			identified by an EPSG code for its vertical part. Resulting local depth 3d CRS is
		 * 			stored into this repository
		 *
		 * @exception	std::invalid_argument	If the default RESQML version is unrecognized.
		 * @exception	std::invalid_argument	If <tt>verticalEpsgCode == 0</tt>.
		 *
		 * @param 	guid				  	The guid to set to the local 3d CRS. If empty then a new guid
		 * 									will be generated.
		 * @param 	title				  	The title to set to the local 3d CRS. If empty then
		 * 									\"unknown\" title will be set.
		 * @param 	originOrdinal1		  	The offset of the global 2d CRS on its first axis.
		 * @param 	originOrdinal2		  	The offset of the global 2d CRS on its second axis.
		 * @param 	originOrdinal3		  	The offset in depth of the local CRS regarding the depth
		 * 									origin of the vertical CRS.
		 * @param 	arealRotation		  	The areal rotation in radians regarding the projected CRS.
		 * @param 	projectedUom		  	The unit of measure of the projected axis of this instance.
		 * @param 	projectedUnknownReason	Indicates why the projected CRS cannot be provided using EPSG
		 * 									or GML.
		 * @param 	verticalUom			  	The unit of measure of the vertical axis of this instance.
		 * @param 	verticalEpsgCode	  	The EPSG code of the associated vertical CRS.
		 * @param 	isUpOriented		  	If true, indicates that this depth CRS is actually an
		 * 									elevation CRS.
		 *
		 * @returns	A pointer to the new local depth 3d CRS.
		 */
		DLL_IMPORT_OR_EXPORT RESQML2_NS::LocalDepth3dCrs* createLocalDepth3dCrs(const std::string & guid, const std::string & title,
			double originOrdinal1, double originOrdinal2, double originOrdinal3,
			double arealRotation,
			gsoap_resqml2_0_1::eml20__LengthUom projectedUom, const std::string & projectedUnknownReason,
			gsoap_resqml2_0_1::eml20__LengthUom verticalUom, unsigned int verticalEpsgCode, bool isUpOriented);

		/**
		 * @brief	Creates a local time 3d CRS which is fully identified by means of EPSG code.
		 * 			Resulting local time 3d CRS is stored into this repository
		 *
		 * @exception	std::invalid_argument	If the default RESQML version is unrecognized.
		 * @exception	std::invalid_argument	If <tt>projectedEpsgCode == 0 || verticalEpsgCode ==
		 * 										0</tt>.
		 *
		 * @param 	guid			 	The guid to set to the local 3d CRS. If empty then a new guid
		 * 								will be generated.
		 * @param 	title			 	The title to set to the local 3d CRS. If empty then \"unknown\"
		 * 								title will be set.
		 * @param 	originOrdinal1   	The offset of the global 2d CRS on its first axis.
		 * @param 	originOrdinal2   	The offset of the global 2d CRS on its second axis.
		 * @param 	originOrdinal3   	The offset in depth of the local CRS regarding the depth origin
		 * 								of the vertical CRS.
		 * @param 	arealRotation	 	The areal rotation in radians regarding the projected CRS.
		 * @param 	projectedUom	 	The unit of measure of the projected axis of this instance.
		 * @param 	projectedEpsgCode	The EPSG code of the associated projected CRS.
		 * @param 	timeUom			 	The unit of measure of the Z offset of this instance.
		 * @param 	verticalUom		 	The unit of measure of the vertical axis of this instance.
		 * @param 	verticalEpsgCode 	The EPSG code of the associated vertical CRS.
		 * @param 	isUpOriented	 	If true, indicates that the Z offset if an elevation when
		 * 								positive. If false, the Z offset if a depth when positive.
		 *
		 * @returns	A pointer to the new local time 3d CRS.
		 */
		DLL_IMPORT_OR_EXPORT RESQML2_NS::LocalTime3dCrs* createLocalTime3dCrs(const std::string & guid, const std::string & title,
			double originOrdinal1, double originOrdinal2, double originOrdinal3,
			double arealRotation,
			gsoap_resqml2_0_1::eml20__LengthUom projectedUom, unsigned long projectedEpsgCode,
			gsoap_resqml2_0_1::eml20__TimeUom timeUom,
			gsoap_resqml2_0_1::eml20__LengthUom verticalUom, unsigned int verticalEpsgCode, bool isUpOriented);

		/**
		 * @brief	Creates a local time 3d CRS which is fully unknown. Resulting local time 3d CRS is
		 * 			stored into this repository
		 *
		 * @exception	std::invalid_argument	If the default RESQML version is unrecognized.
		 *
		 * @param 	guid				  	The guid to set to the local 3d CRS. If empty then a new guid
		 * 									will be generated.
		 * @param 	title				  	The title to set to the local 3d CRS. If empty then
		 * 									\"unknown\" title will be set.
		 * @param 	originOrdinal1		  	The offset of the global 2d CRS on its first axis.
		 * @param 	originOrdinal2		  	The offset of the global 2d CRS on its second axis.
		 * @param 	originOrdinal3		  	The offset in depth of the local CRS regarding the depth
		 * 									origin of the vertical CRS.
		 * @param 	arealRotation		  	The areal rotation in radians regarding the projected CRS.
		 * @param 	projectedUom		  	The unit of measure of the projected axis of this instance.
		 * @param 	projectedUnknownReason	Indicates why the projected CRS cannot be provided using EPSG
		 * 									or GML.
		 * @param 	timeUom				  	The unit of measure of the Z offset of this instance.
		 * @param 	verticalUom			  	The unit of measure of the vertical axis of this instance.
		 * @param 	verticalUnknownReason 	Indicates why the vertical CRS cannot be provided using EPSG
		 * 									or GML.
		 * @param 	isUpOriented		  	If true, indicates that the Z offset if an elevation when
		 * 									positive. If false, the Z offset if a depth when positive.
		 *
		 * @returns	A pointer to the new local time 3d CRS.
		 */
		DLL_IMPORT_OR_EXPORT RESQML2_NS::LocalTime3dCrs* createLocalTime3dCrs(const std::string & guid, const std::string & title,
			double originOrdinal1, double originOrdinal2, double originOrdinal3,
			double arealRotation,
			gsoap_resqml2_0_1::eml20__LengthUom projectedUom, const std::string & projectedUnknownReason,
			gsoap_resqml2_0_1::eml20__TimeUom timeUom,
			gsoap_resqml2_0_1::eml20__LengthUom verticalUom, const std::string & verticalUnknownReason, bool isUpOriented);

		/**
		 * @brief	Creates a local time 3d CRS which is identified by an EPSG code for its projected
		 * 			part and which is unknown for its vertical part. Resulting local time 3d CRS is
		 * 			stored into this repository
		 *
		 * @exception	std::invalid_argument	If the default RESQML version is unrecognized.
		 * @exception	std::invalid_argument	If <tt>projectedEpsgCode == 0</tt>.
		 *
		 * @param 	guid				 	The guid to set to the local 3d CRS. If empty then a new guid
		 * 									will be generated.
		 * @param 	title				 	The title to set to the local 3d CRS. If empty then
		 * 									\"unknown\" title will be set.
		 * @param 	originOrdinal1		 	The offset of the global 2d CRS on its first axis.
		 * @param 	originOrdinal2		 	The offset of the global 2d CRS on its second axis.
		 * @param 	originOrdinal3		 	The offset in depth of the local CRS regarding the depth
		 * 									origin of the vertical CRS.
		 * @param 	arealRotation		 	The areal rotation in radians regarding the projected CRS.
		 * @param 	projectedUom		 	The unit of measure of the projected axis of this instance.
		 * @param 	projectedEpsgCode	 	The EPSG code of the associated projected CRS.
		 * @param 	timeUom				 	The unit of measure of the Z offset of this instance.
		 * @param 	verticalUom			 	The unit of measure of the vertical axis of this instance.
		 * @param 	verticalUnknownReason	Indicates why the vertical CRS cannot be provided using EPSG
		 * 									or GML.
		 * @param 	isUpOriented		 	If true, indicates that the Z offset if an elevation when
		 * 									positive. If false, the Z offset if a depth when positive.
		 *
		 * @returns	A pointer to the new local time 3d CRS.
		 */
		DLL_IMPORT_OR_EXPORT RESQML2_NS::LocalTime3dCrs* createLocalTime3dCrs(const std::string & guid, const std::string & title,
			double originOrdinal1, double originOrdinal2, double originOrdinal3,
			double arealRotation,
			gsoap_resqml2_0_1::eml20__LengthUom projectedUom, unsigned long projectedEpsgCode,
			gsoap_resqml2_0_1::eml20__TimeUom timeUom,
			gsoap_resqml2_0_1::eml20__LengthUom verticalUom, const std::string & verticalUnknownReason, bool isUpOriented);

		/**
		 * @brief	Creates a local time 3d CRS which unknown for its projected part and which is
		 * 			identified by an EPSG code for its vertical part. Resulting local time 3d CRS is
		 * 			stored into this repository
		 *
		 * @exception	std::invalid_argument	If the default RESQML version is unrecognized.
		 * @exception	std::invalid_argument	If <tt>verticalEpsgCode == 0</tt>.
		 *
		 * @param 	guid				  	The guid to set to the local 3d CRS. If empty then a new guid
		 * 									will be generated.
		 * @param 	title				  	The title to set to the local 3d CRS. If empty then
		 * 									\"unknown\" title will be set.
		 * @param 	originOrdinal1		  	The offset of the global 2d CRS on its first axis.
		 * @param 	originOrdinal2		  	The offset of the global 2d CRS on its second axis.
		 * @param 	originOrdinal3		  	The offset in depth of the local CRS regarding the depth
		 * 									origin of the vertical CRS.
		 * @param 	arealRotation		  	The areal rotation in radians regarding the projected CRS.
		 * @param 	projectedUom		  	The unit of measure of the projected axis of this instance.
		 * @param 	projectedUnknownReason	Indicates why the projected CRS cannot be provided using EPSG
		 * 									or GML.
		 * @param 	timeUom				  	The unit of measure of the Z offset of this instance.
		 * @param 	verticalUom			  	The unit of measure of the vertical axis of this instance.
		 * @param 	verticalEpsgCode	  	The EPSG code of the associated vertical CRS.
		 * @param 	isUpOriented		  	If true, indicates that the Z offset if an elevation when
		 * 									positive. If false, the Z offset if a depth when positive.
		 *
		 * @returns	A pointer to the new local time 3d CRS.
		 */
		DLL_IMPORT_OR_EXPORT RESQML2_NS::LocalTime3dCrs* createLocalTime3dCrs(const std::string & guid, const std::string & title,
			double originOrdinal1, double originOrdinal2, double originOrdinal3,
			double arealRotation,
			gsoap_resqml2_0_1::eml20__LengthUom projectedUom, const std::string & projectedUnknownReason,
			gsoap_resqml2_0_1::eml20__TimeUom timeUom,
			gsoap_resqml2_0_1::eml20__LengthUom verticalUom, unsigned int verticalEpsgCode, bool isUpOriented);

		/**
		 * @brief	Creates a measured depth (MD) datum into this repository
		 *
		 * @exception	std::invalid_argument	If the default RESQML version is unrecognized.
		 *
		 * @param 	  	guid					 	The guid to set to the MD datum. If empty then a new
		 * 											guid will be generated.
		 * @param 	  	title					 	The title to set to the MD datum. If empty then
		 * 											\"unknown\" title will be set.
		 * @param [in]	locCrs					 	The local 3d CRS associated to this datum if non-null,
		 * 											else the default local 3d CRS.
		 * @param 	  	originKind				 	The reference location of the MD datum.
		 * @param 	  	referenceLocationOrdinal1	The first reference location ordinal relative to the
		 * 											local 3d CRS.
		 * @param 	  	referenceLocationOrdinal2	The second reference location ordinal relative to the
		 * 											local 3d CRS.
		 * @param 	  	referenceLocationOrdinal3	The third reference location ordinal relative to the
		 * 											local 3d CRS.
		 *
		 * @returns	A pointer to the new MD datum.
		 */
		DLL_IMPORT_OR_EXPORT RESQML2_NS::MdDatum* createMdDatum(const std::string & guid, const std::string & title,
			RESQML2_NS::AbstractLocal3dCrs * locCrs, gsoap_eml2_3::eml23__WellboreDatumReference originKind,
			double referenceLocationOrdinal1, double referenceLocationOrdinal2, double referenceLocationOrdinal3);

		//************ FEATURE ***************

		/**
		 * @brief	Creates a boundary feature into this repository
		 *
		 * @exception	std::invalid_argument	If the default RESQML version is unrecognized.
		 *
		 * @param 	guid 	The guid to set to the boundary feature. If empty then a new guid will be
		 * 					generated.
		 * @param 	title	The title to set to the boundary feature. If empty then \"unknown\" title
		 * 					will be set.
		 *
		 * @returns	A pointer to the new boundary feature.
		 */
		DLL_IMPORT_OR_EXPORT RESQML2_NS::BoundaryFeature* createBoundaryFeature(const std::string & guid, const std::string & title);

		/**
		 * @brief	@deprecated Use {@link createBoundaryFeature()} method for RESQML post v2.0.1 Creates
		 * 			a horizon into this repository
		 *
		 * @exception	std::invalid_argument	If the default RESQML version is unrecognized.
		 *
		 * @param 	guid 	The guid to set to the horizon. If empty then a new guid will be generated.
		 * @param 	title	The title to set to the horizon. If empty then \"unknown\" title will be set.
		 *
		 * @returns	A pointer to the new horizon.
		 */
		DLL_IMPORT_OR_EXPORT RESQML2_NS::BoundaryFeature* createHorizon(const std::string & guid, const std::string & title);

		/**
		 * @brief	@deprecated Use {@link createBoundaryFeature()} method for RESQML post v2.0.1 Creates
		 * 			a geobody boundary feature into this repository
		 *
		 * @exception	std::invalid_argument	If the default RESQML version is unrecognized.
		 *
		 * @param 	guid 	The guid to set to the geobody boundary feature. If empty then a new guid
		 * 					will be generated.
		 * @param 	title	The title to set to the geobody boundary feature. If empty then \"unknown\"
		 * 					title will be set.
		 *
		 * @returns	A pointer to the new geobody boundary feature.
		 */
		DLL_IMPORT_OR_EXPORT RESQML2_NS::BoundaryFeature* createGeobodyBoundaryFeature(const std::string & guid, const std::string & title);

		/**
		 * @brief	Creates a geobody feature into this repository
		 *
		 * @exception	std::invalid_argument	If the default RESQML version is unrecognized.
		 *
		 * @param 	guid 	The guid to set to the geobody feature. If empty then a new guid will be
		 * 					generated.
		 * @param 	title	The title to set to the geobody feature. If empty then \"unknown\" title will
		 * 					be set.
		 *
		 * @returns	A pointer to the new geobody feature.
		 */
		DLL_IMPORT_OR_EXPORT RESQML2_NS::RockVolumeFeature* createGeobodyFeature(const std::string & guid, const std::string & title);

		/**
		 * @brief	@deprecated Use {@link createBoundaryFeature()} method for RESQML post v2.0.1 Creates
		 * 			a fault into this repository
		 *
		 * @exception	std::invalid_argument	If the default RESQML version is unrecognized.
		 *
		 * @param 	guid 	The guid to set to the fault. If empty then a new guid will be generated.
		 * @param 	title	The title to set to the fault. If empty then \"unknown\" title will be set.
		 *
		 * @returns	A pointer to the new fault.
		 */
		DLL_IMPORT_OR_EXPORT RESQML2_NS::BoundaryFeature* createFault(const std::string & guid, const std::string & title);

		/**
		 * @brief	@deprecated Use {@link createBoundaryFeature()} method for RESQML post v2.0.1 Creates
		 * 			a fracture into this repository
		 *
		 * @exception	std::invalid_argument	If the default RESQML version is unrecognized.
		 *
		 * @param 	guid 	The guid to set to the fracture. If empty then a new guid will be generated.
		 * @param 	title	The title to set to the fracture. If empty then \"unknown\" title will be set.
		 *
		 * @returns	A pointer to the new fracture.
		 */
		DLL_IMPORT_OR_EXPORT RESQML2_NS::BoundaryFeature* createFracture(const std::string & guid, const std::string & title);

		/**
		 * @brief	Creates a wellbore feature into this repository
		 *
		 * @exception	std::invalid_argument	If the default RESQML version is unrecognized.
		 *
		 * @param 	guid 	The guid to set to the wellbore feature. If empty then a new guid will be
		 * 					generated.
		 * @param 	title	The title to set to the wellbore feature. If empty then \"unknown\" title
		 * 					will be set.
		 *
		 * @returns	A pointer to the new wellbore feature.
		 */
		DLL_IMPORT_OR_EXPORT RESQML2_NS::WellboreFeature* createWellboreFeature(const std::string & guid, const std::string & title);

		/**
		 * @brief	Creates a seismic lattice into this repository
		 *
		 * @exception	std::invalid_argument	If the default RESQML version is unrecognized.
		 *
		 * @param 	guid			  	The guid to set to the seismic lattice. If empty then a new guid
		 * 								will be generated.
		 * @param 	title			  	The title to set to the seismic lattice. If empty then
		 * 								\"unknown\" title will be set.
		 * @param 	inlineIncrement   	The constant index increment between two consecutive inlines of
		 * 								the seismic lattice.
		 * @param 	crosslineIncrement	The constant index increment between two consecutive crosslines
		 * 								of the seismic lattice.
		 * @param 	originInline	  	The index of the first inline of the seismic lattice.
		 * @param 	originCrossline   	The index of the first crossline of the seismic lattice.
		 * @param 	inlineCount		  	Number of inlines.
		 * @param 	crosslineCount	  	Number of crosslines.
		 *
		 * @returns	A pointer to the new seismic lattice.
		 */
		DLL_IMPORT_OR_EXPORT RESQML2_NS::SeismicLatticeFeature* createSeismicLattice(const std::string & guid, const std::string & title,
			int inlineIncrement, int crosslineIncrement,
			unsigned int originInline, unsigned int originCrossline,
			unsigned int inlineCount, unsigned int crosslineCount);

		/**
		 * Creates a seismic line into this repository
		 *
		 * @param 	guid			   	The guid to set to the seismic line. If empty then a new guid
		 * 								will be generated.
		 * @param 	title			   	The title to set to the seismic line. If empty then \"unknown\"
		 * 								title will be set.
		 * @param 	traceIndexIncrement	The constant index increment between two consecutive traces.
		 * @param 	firstTraceIndex	   	The index of the first trace of the seismic line.
		 * @param 	traceCount		   	Number of traces.
		 *
		 * @returns	A pointer to the new seismic line.
		 */
		DLL_IMPORT_OR_EXPORT RESQML2_0_1_NS::SeismicLineFeature* createSeismicLine(const std::string & guid, const std::string & title,
			int traceIndexIncrement, unsigned int firstTraceIndex, unsigned int traceCount);

		/**
		 * @brief	Creates a CMP line into this repository
		 *
		 * @param 	guid								The guid to set to the CMP line. If empty then a
		 * 												new guid will be generated.
		 * @param 	title								The title to set to the CMP line. If empty then
		 * 												\"unknown\" title will be set.
		 * @param 	nearestShotPointIndicesIncrement	The constant index increment between two
		 * 												consecutive shot points indices.
		 * @param 	firstNearestShotPointIndex			The index of the first shot point of the CMP line.
		 * @param 	nearestShotPointCount				Number of shot point.
		 *
		 * @returns	A pointer to the new CMP line.
		 */
		DLL_IMPORT_OR_EXPORT RESQML2_NS::CmpLineFeature* createCmpLine(const std::string & guid, const std::string & title,
			int nearestShotPointIndicesIncrement, int firstNearestShotPointIndex, unsigned int nearestShotPointCount);

		/**
		 * Creates a shot point line into this repository
		 *
		 * @param 	guid			   	The guid to set to the shot point line. If empty then a new guid
		 * 								will be generated.
		 * @param 	title			   	The title to set to the shot point line. If empty then \"unknown\"
		 * 								title will be set.
		 *
		 * @returns	A pointer to the new CMP line.
		 */
		DLL_IMPORT_OR_EXPORT RESQML2_NS::ShotPointLineFeature* createShotPointLine(const std::string & guid, const std::string & title);

		/**
		 * @brief	Creates a seismic line set into this repository
		 *
		 * @exception	std::invalid_argument	If the default RESQML version is unrecognized.
		 *
		 * @param 	guid 	The guid to set to the seismic line set. If empty then a new guid will be
		 * 					generated.
		 * @param 	title	The title to set to the seismic line set. If empty then \"unknown\".
		 *
		 * @returns	A pointer to the new seismic line set.
		 */
		DLL_IMPORT_OR_EXPORT RESQML2_NS::SeismicLineSetFeature* createSeismicLineSet(const std::string & guid, const std::string & title);

		/**
		 * @brief	Creates a cultural into this repository
		 *
		 * @exception	std::invalid_argument	If the default RESQML version is unrecognized.
		 *
		 * @param 	guid 	The guid to set to the cultural. If empty then a new guid will be generated.
		 * @param 	title	The title to set to the cultural. If empty then \"unknown\" title will be set.
		 * @param 	kind 	(Optional) The kind to set to the cultural. It is defaulted to
		 * 					gsoap_eml2_3::resqml22__CulturalFeatureKind__project_x0020boundaries for
		 * 					easing 2.0.1 compatibility.
		 *
		 * @returns	A pointer to the new cultural.
		 */
		DLL_IMPORT_OR_EXPORT RESQML2_NS::CulturalFeature* createCultural(const std::string & guid, const std::string & title,
			gsoap_eml2_3::resqml22__CulturalFeatureKind kind = gsoap_eml2_3::resqml22__CulturalFeatureKind__project_x0020boundaries);

		/**
		 * @brief	@deprecated Use {@link createRockVolumeFeature()} method for RESQML post v2.0.1
		 * 			Creates a stratigraphic unit into this repository
		 *
		 * @exception	std::invalid_argument	If the default RESQML version is unrecognized.
		 *
		 * @param 	guid 	The guid to set to the stratigraphic unit. If empty then a new guid will be
		 * 					generated.
		 * @param 	title	The title to set to the stratigraphic unit. If empty then \"unknown\" title
		 * 					will be set.
		 *
		 * @returns	A pointer to the new stratigraphic unit.
		 */
		DLL_IMPORT_OR_EXPORT RESQML2_NS::RockVolumeFeature* createStratigraphicUnitFeature(const std::string & guid, const std::string & title);

		/**
		 * @deprecated Use {@link createRockVolumeFeature()} method for RESQML post v2.0.1
		 * Creates a RockVolume feature into this repository
		 *
		 * @param 	guid 	The guid to set to the RockVolume feature. If empty then a new guid will be generated.
		 * @param 	title	The title to set to the RockVolume feature. If empty then \"unknown\" title will be set.
		 *
		 * @returns	A pointer to the new RockVolume feature.
		 */
		DLL_IMPORT_OR_EXPORT RESQML2_NS::RockVolumeFeature* createRockVolumeFeature(const std::string & guid, const std::string & title);

		/**
		 * Creates a model into this repository.
		 *
		 * @param 	guid 	The guid to set to the model. If empty then a new guid will be generated.
		 * @param 	title	The title to set to the model. If empty then \"unknown\" title will be set.
		 *
		 * @returns	A pointer to the new model.
		 */
		DLL_IMPORT_OR_EXPORT RESQML2_NS::Model* createModel(const std::string & guid, const std::string & title);

		/**
		 * @brief	@deprecated Use {@link createModel()} method for RESQML post v2.0.1 Creates a
		 * 			structural model into this repository
		 *
		 * @exception	std::invalid_argument	If the default RESQML version is unrecognized.
		 *
		 * @param 	guid 	The guid to set to the structural model. If empty then a new guid will be
		 * 					generated.
		 * @param 	title	The title to set to the structural model. If empty then \"unknown\" title
		 * 					will be set.
		 *
		 * @returns	A pointer to the new structural model.
		 */
		DLL_IMPORT_OR_EXPORT RESQML2_NS::Model* createStructuralModel(const std::string & guid, const std::string & title);

		/**
		 * @brief	@deprecated Use {@link createModel()} method for RESQML post v2.0.1 Creates a
		 * 			stratigraphic model into this repository
		 *
		 * @exception	std::invalid_argument	If the default RESQML version is unrecognized.
		 *
		 * @param 	guid 	The guid to set to the stratigraphic model. If empty then a new guid will be
		 * 					generated.
		 * @param 	title	The title to set to the stratigraphic model. If empty then \"unknown\" title
		 * 					will be set.
		 *
		 * @returns	A pointer to the new stratigraphic model.
		 */
		DLL_IMPORT_OR_EXPORT RESQML2_NS::Model* createStratigraphicModel(const std::string & guid, const std::string & title);

		/**
		 * @brief	@deprecated Use {@link createModel()} method for RESQML post v2.0.1 Creates a rock
		 * 			fluid model into this repository
		 *
		 * @exception	std::invalid_argument	If the default RESQML version is unrecognized.
		 *
		 * @param 	guid 	The guid to set to the rock fluid model. If empty then a new guid will be
		 * 					generated.
		 * @param 	title	The title to set to the rock fluid model. If empty then \"unknown\" title
		 * 					will be set.
		 *
		 * @returns	A pointer to the new rock fluid model.
		 */
		DLL_IMPORT_OR_EXPORT RESQML2_NS::Model* createRockFluidModel(const std::string & guid, const std::string & title);

		/**
		 * @brief	@deprecated Use {@link createModel()} method for RESQML post v2.0.1 Creates an earth
		 * 			model into this repository
		 *
		 * @exception	std::invalid_argument	If the default RESQML version is unrecognized.
		 *
		 * @param 	guid 	The guid to set to the earth model. If empty then a new guid will be
		 * 					generated.
		 * @param 	title	The title to set to the earth model. If empty then \"unknown\" title will be
		 * 					set.
		 *
		 * @returns	A pointer to the new earth model.
		 */
		DLL_IMPORT_OR_EXPORT RESQML2_NS::Model* createEarthModel(const std::string & guid, const std::string & title);

		/**
		 * Creates a fluid boundary feature into this repository
		 *
		 * @param 	guid			The guid to set to the fluid boundary feature. If empty then a new
		 * 							guid will be generated.
		 * @param 	title			The title to set to the fluid boundary feature. If empty then
		 * 							\"unknown\" title will be set.
		 * @param 	fluidContact	The fluid contact.
		 *
		 * @returns	A pointer to the new fluid boundary feature.
		 */
		DLL_IMPORT_OR_EXPORT RESQML2_0_1_NS::FluidBoundaryFeature* createFluidBoundaryFeature(const std::string & guid, const std::string & title, gsoap_resqml2_0_1::resqml20__FluidContact fluidContact);

		/**
		 * Creates rock fluid unit into this repository
		 *
		 * @param 		  	guid			   	The guid to set to the rock fluid unit. If empty then a
		 * 										new guid will be generated.
		 * @param 		  	title			   	The title to set to the rock fluid unit. If empty then
		 * 										\"unknown\" title will be set.
		 * @param 		  	phase			   	The phase to set to the rock fluid unit.
		 * @param [in]		fluidBoundaryTop   	The rock fluid unit top boundary. It cannot be null.
		 * @param [in]		fluidBoundaryBottom	The rock fluid unit bottom boundary. It cannot be null.
		 *
		 * @returns	A pointer to the new rock fluid unit.
		 */
		DLL_IMPORT_OR_EXPORT RESQML2_0_1_NS::RockFluidUnitFeature* createRockFluidUnit(const std::string & guid, const std::string & title, gsoap_resqml2_0_1::resqml20__Phase phase, RESQML2_0_1_NS::FluidBoundaryFeature* fluidBoundaryTop, RESQML2_0_1_NS::FluidBoundaryFeature* fluidBoundaryBottom);

		//************ INTERPRETATION ********

		/**
		 * @brief	Creates a generic feature interpretation into this repository
		 *
		 * @exception	std::invalid_argument	If the default RESQML version is unrecognized.
		 * @exception	std::invalid_argument	If <tt>feature == nullptr</tt>.
		 *
		 * @param [in]	feature	The interpreted feature. It cannot be null.
		 * @param 	  	guid   	The guid to set to the generic feature interpretation. If empty then a
		 * 						new guid will be generated.
		 * @param 	  	title  	The title to set to the generic feature interpretation. If empty then
		 * 						\"unknown\" title will be set.
		 *
		 * @returns	A pointer to the new generic feature interpretation.
		 */
		DLL_IMPORT_OR_EXPORT RESQML2_NS::GenericFeatureInterpretation* createGenericFeatureInterpretation(RESQML2_NS::AbstractFeature * feature, const std::string & guid, const std::string & title);

		/**
		 * Creates a boundary feature interpretation into this repository
		 *
		 * @exception	std::invalid_argument	If the default RESQML version is unrecognized.
		 * @exception	std::invalid_argument	If @p feature is @c nullptr.
		 *
		 * @param [in]	feature	The interpreted boundary feature. It cannot be null.
		 * @param 	  	guid   	The guid to set to the boundary feature interpretation. If empty then a
		 * 						new guid will be generated.
		 * @param 	  	title  	The title to set to the boundary feature interpretation. If empty then
		 * 						\"unknown\" title will be set.
		 *
		 * @returns	A pointer to the new boundary feature interpretation.
		 */
		DLL_IMPORT_OR_EXPORT RESQML2_NS::BoundaryFeatureInterpretation* createBoundaryFeatureInterpretation(RESQML2_NS::BoundaryFeature * feature, const std::string & guid, const std::string & title);

		/**
		 * @brief	Creates a horizon interpretation into this repository
		 *
		 * @exception	std::invalid_argument	If the default RESQML version is unrecognized.
		 * @exception	std::invalid_argument	If <tt>horizon == nullptr</tt>.
		 *
		 * @param [in]	horizon	The interpreted horizon. It cannot be null.
		 * @param 	  	guid   	The guid to set to the horizon interpretation. If empty then a new guid
		 * 						will be generated.
		 * @param 	  	title  	The title to set to the horizon interpretation. If empty then \"unknown\"
		 * 						title will be set.
		 *
		 * @returns	A pointer to the new horizon interpretation.
		 */
		DLL_IMPORT_OR_EXPORT RESQML2_NS::HorizonInterpretation* createHorizonInterpretation(RESQML2_NS::BoundaryFeature * horizon, const std::string & guid, const std::string & title);

		/**
		 * @brief	Creates a geobody boundary interpretation into this repository
		 *
		 * @exception	std::invalid_argument	If the default RESQML version is unrecognized.
		 * @exception	std::invalid_argument	If <tt>geobodyBoundary == nullptr</tt>.
		 *
		 * @param [in]	geobodyBoundary	The interpreted geobody boundary. It cannot be null.
		 * @param 	  	guid		   	The guid to set to the geobody boundary interpretation. If empty
		 * 								then a new guid will be generated.
		 * @param 	  	title		   	The title to set to the geobody boundary interpretation. If empty
		 * 								then \"unknown\" title will be set.
		 *
		 * @returns	A pointer to the new geobody boundary interpretation.
		 */
		DLL_IMPORT_OR_EXPORT RESQML2_NS::GeobodyBoundaryInterpretation* createGeobodyBoundaryInterpretation(RESQML2_NS::BoundaryFeature * geobodyBoundary, const std::string & guid, const std::string & title);

		/**
		 * @brief	Creates a fault interpretation into this repository
		 *
		 * @exception	std::invalid_argument	If the default RESQML version is unrecognized.
		 * @exception	std::invalid_argument	If <tt>fault == nullptr</tt>.
		 *
		 * @param [in]	fault	The interpreted fault. It cannot be null.
		 * @param 	  	guid 	The guid to set to the fault interpretation. If empty then a new guid
		 * 						will be generated.
		 * @param 	  	title	The title to set to the fault interpretation. If empty then \"unknown\"
		 * 						title will be set.
		 *
		 * @returns	A pointer to the new fault interpretation.
		 */
		DLL_IMPORT_OR_EXPORT RESQML2_NS::FaultInterpretation* createFaultInterpretation(RESQML2_NS::BoundaryFeature * fault, const std::string & guid, const std::string & title);

		/**
		 * @brief	Creates a wellbore interpretation into this repository
		 *
		 * @exception	std::invalid_argument	If the default RESQML version is unrecognized.
		 * @exception	std::invalid_argument	If @p wellbore is @c nullptr.
		 *
		 * @param [in]	wellbore 	The interpreted wellbore feature. It cannot be null.
		 * @param 	  	guid	 	The guid to set to the wellbore interpretation. If empty then a new
		 * 							guid will be generated.
		 * @param 	  	title	 	The title to set to the wellbore interpretation. If empty then
		 * 							\"unknown\" title will be set.
		 * @param 	  	isDrilled	Indicate if the wellbore is interpreted wether as drilled (true) or
		 * 									not (false).
		 *
		 * @returns	A pointer to the new wellbore interpretation.
		 */
		DLL_IMPORT_OR_EXPORT RESQML2_NS::WellboreInterpretation* createWellboreInterpretation(RESQML2_NS::WellboreFeature * wellbore, const std::string & guid, const std::string & title, bool isDrilled);

		/**
		 * @brief	Creates an earth model interpretation into this repository
		 *
		 * @exception	std::invalid_argument	If the default RESQML version is unrecognized.
		 * @exception	std::invalid_argument	If <tt>orgFeat == nullptr</tt>.
		 *
		 * @param [in]	orgFeat	The interpreted organization. It cannot be null.
		 * @param 	  	guid   	The guid to set to the earth model interpretation. If empty then a new
		 * 						guid will be generated.
		 * @param 	  	title  	The title to set to the earth model interpretation. If empty then
		 * 						\"unknown\" title will be set.
		 *
		 * @returns	A pointer to the new earth model interpretation.
		 */
		DLL_IMPORT_OR_EXPORT RESQML2_NS::EarthModelInterpretation* createEarthModelInterpretation(RESQML2_NS::Model * orgFeat, const std::string & guid, const std::string & title);

		/**
		 * @brief	Creates a structural organization interpretation ordered by age into this repository.
		 *
		 * @exception	std::invalid_argument	If the default RESQML version is unrecognized.
		 * @exception	std::invalid_argument	If <tt>orgFeat == nullptr</tt> or if in a RESQML v2.0
		 * 										context, @p orgFeat is not a structural organization.
		 *
		 * @param [in]	orgFeat	The interpreted organization. It cannot be null.
		 * @param 	  	guid   	The guid to set to the structural organization interpretation. If empty
		 * 						then a new guid will be generated.
		 * @param 	  	title  	The title to set to the structural organization interpretation. If empty
		 * 						then \"unknown\" title will be set.
		 *
		 * @returns	A pointer to the new structural organization interpretation.
		 */
		DLL_IMPORT_OR_EXPORT RESQML2_NS::StructuralOrganizationInterpretation* createStructuralOrganizationInterpretationInAge(RESQML2_NS::Model * orgFeat, const std::string & guid, const std::string & title);

		/**
		 * @brief	Creates a structural organization interpretation ordered by apparent depth into this
		 * 			repository.
		 *
		 * @exception	std::invalid_argument	If the default RESQML version is unrecognized.
		 * @exception	std::invalid_argument	If <tt>orgFeat == nullptr</tt> or if in a RESQML v2.0
		 * 										context, @p orgFeat is not a structural organization.
		 *
		 * @param [in]	orgFeat	The interpreted organization. It cannot be null.
		 * @param 	  	guid   	The guid to set to the structural organization interpretation. If empty
		 * 						then a new guid will be generated.
		 * @param 	  	title  	The title to set to the structural organization interpretation. If empty
		 * 						then \"unknown\" title will be set.
		 *
		 * @returns	A pointer to the new structural organization interpretation.
		 */
		DLL_IMPORT_OR_EXPORT RESQML2_NS::StructuralOrganizationInterpretation* createStructuralOrganizationInterpretationInApparentDepth(RESQML2_NS::Model * orgFeat, const std::string & guid, const std::string & title);

		/**
		 * @brief	Creates a structural organization interpretation ordered by measured depth into this
		 * 			repository
		 *
		 * @exception	std::invalid_argument	If the default RESQML version is unrecognized.
		 * @exception	std::invalid_argument	If <tt>orgFeat == nullptr</tt> or if in a RESQML v2.0
		 * 										context, @p orgFeat is not a structural organization.
		 *
		 * @param [in]	orgFeat	The interpreted organization. It cannot be null.
		 * @param 	  	guid   	The guid to set to the structural organization interpretation. If empty
		 * 						then a new guid will be generated.
		 * @param 	  	title  	The title to set to the structural organization interpretation. If empty
		 * 						then \"unknown\" title will be set.
		 *
		 * @returns	A pointer to the new structural organization interpretation.
		 */
		DLL_IMPORT_OR_EXPORT RESQML2_NS::StructuralOrganizationInterpretation* createStructuralOrganizationInterpretationInMeasuredDepth(RESQML2_NS::Model * orgFeat, const std::string & guid, const std::string & title);

		/**
		 * @brief	Creates a rock fluid organization interpretation into this repository
		 *
		 * @exception	std::invalid_argument	If the default RESQML version is unrecognized.
		 * @exception	std::invalid_argument	If <tt>orgFeat == nullptr</tt> or if in a RESQML v2.0
		 * 										context, @p orgFeat is not a fluid organization.
		 *
		 * @param [in]	orgFeat	The interpreted organization. It cannot be null.
		 * @param 	  	guid   	The guid to set to the rock fluid organization interpretation. If empty
		 * 						then a new guid will be generated.
		 * @param 	  	title  	The title to set to the rock fluid organization interpretation. If empty
		 * 						then \"unknown\" title will be set.
		 *
		 * @returns	A pointer to the new rock fluid organization interpretation.
		 */
		DLL_IMPORT_OR_EXPORT RESQML2_NS::RockFluidOrganizationInterpretation* createRockFluidOrganizationInterpretation(RESQML2_NS::Model * orgFeat, const std::string & guid, const std::string & title);

		/**
		 * @brief	Creates a rock fluid unit interpretation into this repository
		 *
		 * @exception	std::invalid_argument	If the default RESQML version is unrecognized.
		 * @exception	std::invalid_argument	If <tt>feature == nullptr</tt>.
		 *
		 * @param [in]	rockFluidUnitFeature	The interpreted rock fluid unit. It cannot be null.
		 * @param 	  	guid					The guid to set to the rock fluid unit interpretation. If
		 * 										empty then a new guid will be generated.
		 * @param 	  	title					The title to set to the rock fluid unit interpretation.
		 * 										If empty then \"unknown\" title will be set.
		 *
		 * @returns	A pointer to the new rock fluid unit interpretation.
		 */
		DLL_IMPORT_OR_EXPORT RESQML2_NS::RockFluidUnitInterpretation* createRockFluidUnitInterpretation(RESQML2_NS::RockVolumeFeature * rockFluidUnitFeature, const std::string & guid, const std::string & title);

		/**
		 * @brief	Creates a geobody interpretation into this repository
		 *
		 * @exception	std::invalid_argument	If the default RESQML version is unrecognized.
		 * @exception	std::invalid_argument	If <tt>geobody == nullptr</tt> or if in a RESQML v2.0
		 * 										context, @p geobody is not an actual geobody feature.
		 *
		 * @param [in]	geobody	The interpreted geobody. It cannot be null.
		 * @param 	  	guid   	The guid to set to the geobody interpretation. If empty then a new guid
		 * 						will be generated.
		 * @param 	  	title  	The title to set to the geobody interpretation. If empty then \"unknown\"
		 * 						title will be set.
		 *
		 * @returns	A pointer to the new geobody interpretation.
		 */
		DLL_IMPORT_OR_EXPORT RESQML2_NS::GeobodyInterpretation* createGeobodyInterpretation(RESQML2_NS::RockVolumeFeature* geobody, const std::string & guid, const std::string & title);

		/**
		 * @brief	Creates a stratigraphic unit interpretation into this repository.
		 *
		 * @exception	std::invalid_argument	If the default RESQML version is unrecognized.
		 * @exception	std::invalid_argument	If <tt>stratiUnitFeature == nullptr</tt>.
		 *
		 * @param [in]	stratiUnitFeature	The interpreted stratigraphic unit. It cannot be null.
		 * @param 	  	guid			 	The guid to set to the stratigraphic unit interpretation. If
		 * 									empty then a new guid will be generated.
		 * @param 	  	title			 	The title to set to the stratigraphic unit interpretation. If
		 * 									empty then \"unknown\" title will be set.
		 *
		 * @returns	A pointer to the new stratigraphic unit interpretation.
		 */
		DLL_IMPORT_OR_EXPORT RESQML2_NS::StratigraphicUnitInterpretation* createStratigraphicUnitInterpretation(RESQML2_NS::RockVolumeFeature * stratiUnitFeature, const std::string & guid, const std::string & title);

		/**
		 * @brief	Creates stratigraphic column into this repository
		 *
		 * @exception	std::invalid_argument	If the default RESQML version is unrecognized.
		 *
		 * @param 	guid 	The guid to set to the stratigraphic column. If empty then a new guid will be
		 * 					generated.
		 * @param 	title	The title to set to the stratigraphic column. If empty then \"unknown\" title
		 * 					will be set.
		 *
		 * @returns	A pointer to the new stratigraphic column.
		 */
		DLL_IMPORT_OR_EXPORT RESQML2_NS::StratigraphicColumn* createStratigraphicColumn(const std::string & guid, const std::string & title);

		/**
		 * @brief	Creates a stratigraphic column rank interpretation ordered by age into this
		 * 			repository.
		 *
		 * @exception	std::invalid_argument	If the default RESQML version is unrecognized.
		 * @exception	std::invalid_argument	If <tt>orgFeat == nullptr</tt> or if in a RESQML v2.0
		 * 										context, @p orgFeat is not a stratigraphic organization.
		 *
		 * @param [in]	orgFeat	The interpreted organization. It cannot be null.
		 * @param 	  	guid   	The guid to set to the stratigraphic column rank interpretation. If empty
		 * 						then a new guid will be generated.
		 * @param 	  	title  	The title to set to the stratigraphic column rank interpretation. If
		 * 						empty then \"unknown\" title will be set.
		 * @param 	  	rank   	The rank of the stratigraphic column rank interpretation.
		 *
		 * @returns	A pointer to the new stratigraphic column rank interpretation.
		 */
		DLL_IMPORT_OR_EXPORT RESQML2_NS::StratigraphicColumnRankInterpretation* createStratigraphicColumnRankInterpretationInAge(RESQML2_NS::Model * orgFeat, const std::string & guid, const std::string & title, const unsigned long & rank);

		/**
		 * @brief	Creates a stratigraphic column rank interpretation ordered by apparent depth into
		 * 			this repository
		 *
		 * @exception	std::invalid_argument	If the default RESQML version is unrecognized.
		 * @exception	std::invalid_argument	If <tt>orgFeat == nullptr</tt> or if in a RESQML v2.0
		 * 										context, @p orgFeat is not a stratigraphic organization.
		 *
		 * @param [in]	orgFeat	The interpreted organization. It cannot be null.
		 * @param 	  	guid   	The guid to set to the stratigraphic column rank interpretation. If empty
		 * 						then a new guid will be generated.
		 * @param 	  	title  	The title to set to the stratigraphic column rank interpretation. If
		 * 						empty then \"unknown\" title will be set.
		 * @param 	  	rank   	The rank of the stratigraphic column rank interpretation.
		 *
		 * @returns	A pointer to the new stratigraphic column rank interpretation.
		 */
		DLL_IMPORT_OR_EXPORT RESQML2_NS::StratigraphicColumnRankInterpretation* createStratigraphicColumnRankInterpretationInApparentDepth(RESQML2_NS::Model * orgFeat, const std::string & guid, const std::string & title, const unsigned long & rank);

		/**
		 * @brief	Creates a stratigraphic occurrence interpretation ordered by age into this repository
		 *
		 * @exception	std::invalid_argument	If the default RESQML version is unrecognized.
		 * @exception	std::invalid_argument	If <tt>orgFeat == nullptr</tt> or if in a RESQML v2.0
		 * 										context, @p orgFeat is not a stratigraphic organization.
		 *
		 * @param [in]	orgFeat	The interpreted organization. It cannot be null.
		 * @param 	  	guid   	The guid to set to the stratigraphic occurrence interpretation. If empty
		 * 						then a new guid will be generated.
		 * @param 	  	title  	The title to set to the stratigraphic occurrence interpretation. If empty
		 * 						then \"unknown\" title will be set.
		 *
		 * @returns	A pointer to the new stratigraphic occurrence interpretation.
		 */
		DLL_IMPORT_OR_EXPORT RESQML2_NS::StratigraphicOccurrenceInterpretation* createStratigraphicOccurrenceInterpretationInAge(RESQML2_NS::Model * orgFeat, const std::string & guid, const std::string & title);

		/**
		 * @brief	Creates a stratigraphic occurrence interpretation ordered by apparent depth into this
		 * 			repository
		 *
		 * @exception	std::invalid_argument	If the default RESQML version is unrecognized.
		 * @exception	std::invalid_argument	If <tt>orgFeat == nullptr</tt> or if in a RESQML v2.0
		 * 										context, @p orgFeat is not a stratigraphic organization.
		 *
		 * @param [in]	orgFeat	The interpreted organization. It cannot be null.
		 * @param 	  	guid   	The guid to set to the stratigraphic occurrence interpretation. If empty
		 * 						then a new guid will be generated.
		 * @param 	  	title  	The title to set to the stratigraphic occurrence interpretation. If empty
		 * 						then \"unknown\" title will be set.
		 *
		 * @returns	A pointer to the new stratigraphic occurrence interpretation.
		 */
		DLL_IMPORT_OR_EXPORT RESQML2_NS::StratigraphicOccurrenceInterpretation* createStratigraphicOccurrenceInterpretationInApparentDepth(RESQML2_NS::Model * orgFeat, const std::string & guid, const std::string & title);

		//************ REPRESENTATION ********

		/**
		 * @brief	Creates a triangulated set representation into this repository
		 *
		 * @exception	std::invalid_argument	If the default RESQML version is unrecognized.
		 *
		 * @param 	guid 	The guid to set to the triangulated set representation. If empty then a new
		 * 					guid will be generated.
		 * @param 	title	The title to set to the triangulated set representation. If empty then
		 * 					\"unknown\" title will be set.
		 *
		 * @returns	A pointer to the new triangulated set representation.
		 */
		DLL_IMPORT_OR_EXPORT RESQML2_NS::TriangulatedSetRepresentation* createTriangulatedSetRepresentation(const std::string & guid, const std::string & title);

		/**
		 * @brief	Creates a triangulated set representation into this repository
		 *
		 * @exception	std::invalid_argument	If the default RESQML version is unrecognized.
		 * @exception	std::invalid_argument	If <tt>interp == nullptr</tt>.
		 *
		 * @param [in]	interp	The represented interpretation. It cannot be null. You can alternatively
		 * 						use {@link  createTriangulatedSetRepresentation} if no interpretation is
		 * 						associated to this representation.
		 * @param 	  	guid  	The guid to set to the triangulated set representation. If empty then a
		 * 						new guid will be generated.
		 * @param 	  	title 	The title to set to the triangulated set representation. If empty then
		 * 						\"unknown\" title will be set.
		 *
		 * @returns	A pointer to the new triangulated set representation.
		 */
		DLL_IMPORT_OR_EXPORT RESQML2_NS::TriangulatedSetRepresentation* createTriangulatedSetRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp,
			const std::string & guid, const std::string & title);

		/**
		 * @brief	Creates a polyline set representation into this repository
		 *
		 * @exception	std::invalid_argument	If the default RESQML version is unrecognized.
		 *
		 * @param 	guid 	The guid to set to the polyline set representation. If empty then a new guid
		 * 					will be generated.
		 * @param 	title	The title to set to the polyline set representation. If empty then
		 * 					\"unknown\" title will be set.
		 *
		 * @returns	A pointer to the new polyline set representation.
		 */
		DLL_IMPORT_OR_EXPORT RESQML2_NS::PolylineSetRepresentation* createPolylineSetRepresentation(const std::string & guid, const std::string & title);

		/**
		 * @brief	Creates a polyline set representation into this repository
		 *
		 * @exception	std::invalid_argument	If the default RESQML version is unrecognized.
		 * @exception	std::invalid_argument	If <tt>interp == nullptr</tt>.
		 *
		 * @param [in]	interp	The represented interpretation. It cannot be null. You can alternatively
		 * 						use {@link  createPolylineSetRepresentation} if no interpretation is
		 * 						associated to this representation.
		 * @param 	  	guid  	The guid to set to the polyline set representation. If empty then a new
		 * 						guid will be generated.
		 * @param 	  	title 	The title to set to the polyline set representation. If empty then
		 * 						\"unknown\" title will be set.
		 *
		 * @returns	A pointer to the new polyline set representation.
		 */
		DLL_IMPORT_OR_EXPORT RESQML2_NS::PolylineSetRepresentation* createPolylineSetRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp,
			const std::string & guid, const std::string & title);

		/**
		 * @brief	Creates a polyline set representation into this repository
		 *
		 * @exception	std::invalid_argument	If the default RESQML version is unrecognized.
		 * @exception	std::invalid_argument	If <tt>interp == nullptr</tt>.
		 * @exception	std::invalid_argument	If in a RESQML v2.0 context, @p roleKind is a break line
		 * 										role.
		 *
		 * @param [in]	interp  	The represented interpretation. It cannot be null. You can
		 * 							alternatively use {@link  createPolylineSetRepresentation} if no
		 * 							interpretation is associated to this representation.
		 * @param 	  	guid		The guid to set to the polyline set representation. If empty then a
		 * 							new guid will be generated.
		 * @param 	  	title   	The title to set to the polyline set representation. If empty then
		 * 							\"unknown\" title will be set.
		 * @param 	  	roleKind	The polyline set role kind.
		 *
		 * @returns	A pointer to the new polyline set representation.
		 */
		DLL_IMPORT_OR_EXPORT RESQML2_NS::PolylineSetRepresentation* createPolylineSetRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp,
			const std::string & guid, const std::string & title, gsoap_eml2_3::resqml22__LineRole roleKind);

		/**
		 * @brief	Creates a point set representation into this repository
		 *
		 * @exception	std::invalid_argument	If the default RESQML version is unrecognized.
		 *
		 * @param 	guid 	The guid to set to the point set representation. If empty then a new guid
		 * 					will be generated.
		 * @param 	title	The title to set to the point set representation. If empty then \"unknown\"
		 * 					title will be set.
		 *
		 * @returns	A pointer to the new point set representation.
		 */
		DLL_IMPORT_OR_EXPORT RESQML2_NS::PointSetRepresentation* createPointSetRepresentation(const std::string & guid, const std::string & title);

		/**
		 * @brief	Creates a point set representation into this repository
		 *
		 * @exception	std::invalid_argument	If the default RESQML version is unrecognized.
		 * @exception	std::invalid_argument	If <tt>interp == nullptr</tt>.
		 *
		 * @param [in]	interp	The represented interpretation. It cannot be null.
		 * @param 	  	guid  	The guid to set to the point set representation. If empty then a new guid
		 * 						will be generated.
		 * @param 	  	title 	The title to set to the point set representation. If empty then
		 * 						\"unknown\" title will be set.
		 *
		 * @returns	A pointer to the new point set representation.
		 */
		DLL_IMPORT_OR_EXPORT RESQML2_NS::PointSetRepresentation* createPointSetRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp,
			const std::string & guid, const std::string & title);

		/**
		 * @brief	Creates a plane set representation into this repository
		 *
		 * @exception	std::invalid_argument	If the default RESQML version is unrecognized.
		 * @exception	std::invalid_argument	If <tt>interp == nullptr</tt>.
		 *
		 * @param [in]	interp	The represented interpretation. It cannot be null.
		 * @param 	  	guid  	The guid to set to the plane set representation. If empty then a new guid
		 * 						will be generated.
		 * @param 	  	title 	The title to set to the plane set representation. If empty then
		 * 						\"unknown\" title will be set.
		 *
		 * @returns	A pointer to the new plane set representation.
		 */
		DLL_IMPORT_OR_EXPORT RESQML2_NS::PlaneSetRepresentation* createPlaneSetRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp,
			const std::string & guid, const std::string & title);

		/**
		 * @brief	Creates a polyline representation into this repository
		 *
		 * @exception	std::invalid_argument	If the default RESQML version is unrecognized.
		 *
		 * @param 	guid		The guid to set to the polyline representation. If empty then a new guid
		 * 						will be generated.
		 * @param 	title   	The title to set to the polyline representation. If empty then
		 * 						\"unknown\" title will be set.
		 * @param 	isClosed	(Optional) True if the polyline is closed, false (default) if it is not.
		 *
		 * @returns	A pointer to the new polyline representation.
		 */
		DLL_IMPORT_OR_EXPORT RESQML2_NS::PolylineRepresentation* createPolylineRepresentation(const std::string & guid, const std::string & title, bool isClosed = false);

		/**
		 * @brief	Creates a polyline representation into this repository
		 *
		 * @exception	std::invalid_argument	If the default RESQML version is unrecognized.
		 * @exception	std::invalid_argument	If <tt>interp == nullptr</tt>.
		 *
		 * @param [in]	interp  	The represented interpretation. It cannot be null. You can
		 * 							alternatively use {@link  createPolylineRepresentation} if no
		 * 							interpretation is associated to this representation.
		 * @param 	  	guid		The guid to set to the polyline representation. If empty then a new
		 * 							guid will be generated.
		 * @param 	  	title   	The title to set to the polyline representation. If empty then
		 * 							\"unknown\" title will be set.
		 * @param 	  	isClosed	(Optional) True if the polyline is closed, false (default) if it is
		 * 							not.
		 *
		 * @returns	A pointer to the new polyline representation.
		 */
		DLL_IMPORT_OR_EXPORT RESQML2_NS::PolylineRepresentation* createPolylineRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp,
			const std::string & guid, const std::string & title, bool isClosed = false);

		/**
		 * @brief	Creates a polyline representation into this repository
		 *
		 * @exception	std::invalid_argument	If the default RESQML version is unrecognized.
		 * @exception	std::invalid_argument	If <tt>interp == nullptr</tt>.
		 *
		 * @param [in]	interp  	The represented interpretation. It cannot be null. You can
		 * 									alternatively use {@link  createPolylineRepresentation} if no
		 * 									interpretation is associated to this representation.
		 * @param 	  	guid		The guid to set to the polyline representation. If empty then a new
		 * 							guid will be generated.
		 * @param 	  	title   	The title to set to the polyline representation. If empty then
		 * 							\"unknown\" title will be set.
		 * @param 	  	roleKind	The polyline role kind.
		 * @param 	  	isClosed	(Optional) True if the polyline is closed, false (default) if it is
		 * 							not.
		 *
		 * @returns	A pointer to the new polyline representation.
		 */
		DLL_IMPORT_OR_EXPORT RESQML2_NS::PolylineRepresentation* createPolylineRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp,
			const std::string & guid, const std::string & title, gsoap_eml2_3::resqml22__LineRole roleKind, bool isClosed = false);

		/**
		 * Creates a 2d grid representation into this repository
		 *
		 * @exception	std::invalid_argument	If the default RESQML version is unrecognized.
		 * @exception	std::invalid_argument	If <tt>interp == nullptr</tt>.
		 *
		 * @param [in]	interp	The represented interpretation. It cannot be null.
		 * @param 	  	guid  	The guid to set to the 2d grid representation. If empty then a new guid
		 * 						will be generated.
		 * @param 	  	title 	The title to set to the 2d grid representation. If empty then \"unknown\"
		 * 						title will be set.
		 *
		 * @returns	A pointer to the new 2d grid representation.
		 */
		DLL_IMPORT_OR_EXPORT RESQML2_NS::Grid2dRepresentation* createGrid2dRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp,
			const std::string & guid, const std::string & title);

		/**
		 * @brief	Creates a wellbore trajectory representation into this repository
		 *
		 * @exception	std::invalid_argument	If the default RESQML version is unrecognized.
		 * @exception	std::invalid_argument	If @p interp or @p mdInfo is @c nullptr.
		 *
		 * @param [in]	interp	The represented wellbore interpretation. It cannot be null.
		 * @param 	  	guid  	The guid to set to the wellbore trajectory representation. If empty then
		 * 						a new guid will be generated.
		 * @param 	  	title 	The title to set to the wellbore trajectory representation. If empty then
		 * 						\"unknown\" title will be set.
		 * @param [in]	mdInfo	The MD information of the trajectory, mainly the well reference point.
		 * 						The unit of measure used for the mdInfo coordinates must also be used for
		 * 						the start and end MD of the trajectory. It cannot be null.
		 *
		 * @returns	A pointer to the new wellbore trajectory representation.
		 */
		DLL_IMPORT_OR_EXPORT RESQML2_NS::WellboreTrajectoryRepresentation* createWellboreTrajectoryRepresentation(RESQML2_NS::WellboreInterpretation* interp, const std::string& guid, const std::string& title, RESQML2_NS::MdDatum* mdInfo);

		/**
		 * Creates a wellbore trajectory representation (with an existing deviation survey as its
		 * origin) into this repository
		 *
		 * @exception	std::invalid_argument	If the default RESQML version is unrecognized.
		 * @exception	std::invalid_argument	If @p interp or @p deviationSurvey is @c nullptr.
		 *
		 * @param [in]	interp		   	The represented interpretation. It cannot be null.
		 * @param 	  	guid		   	The guid to set to the wellbore trajectory representation. If
		 * 								empty then a new guid will be generated.
		 * @param 	  	title		   	The title to set to the wellbore trajectory representation. If
		 * 								empty then \"unknown\" title will be set.
		 * @param [in]	deviationSurvey	The deviation survey on which this wellbore trajectory relies on.
		 * 								MD data will be retrieve from it. It cannot be null.
		 *
		 * @returns	A pointer to the new wellbore trajectory representation.
		 */
		DLL_IMPORT_OR_EXPORT RESQML2_NS::WellboreTrajectoryRepresentation* createWellboreTrajectoryRepresentation(RESQML2_NS::WellboreInterpretation* interp, const std::string& guid, const std::string& title, RESQML2_NS::DeviationSurveyRepresentation* deviationSurvey);

		/**
		 * @brief	Creates a deviation survey representation into this repository
		 *
		 * @exception	std::invalid_argument	If the default RESQML version is unrecognized.
		 * @exception	std::invalid_argument	If <tt>interp == nullptr</tt> or <tt>mdInfo ==
		 * 												nullptr</tt>.
		 *
		 * @param [in]	interp 	The represented interpretation. It cannot be null.
		 * @param 	  	guid   	The guid to set to the deviation survey representation. If empty then a
		 * 						new guid will be generated.
		 * @param 	  	title  	The title to set to the deviation survey representation. If empty then
		 * 						\"unknown\" title will be set.
		 * @param 	  	isFinal	Used to indicate that this is a final version of the deviation survey
		 * 						(true), as distinct from the interim interpretations (false).
		 * @param [in]	mdInfo 	The MD datum that refers this deviation survey representation. It
		 * 							cannot be null.
		 *
		 * @returns	A pointer to the new deviation survey representation.
		 */
		DLL_IMPORT_OR_EXPORT RESQML2_NS::DeviationSurveyRepresentation* createDeviationSurveyRepresentation(RESQML2_NS::WellboreInterpretation* interp, const std::string& guid, const std::string& title, const bool& isFinal, RESQML2_NS::MdDatum* mdInfo);

		/**
		 * @brief	Creates a wellbore frame representation into this repository
		 *
		 * @exception	std::invalid_argument	If the default RESQML version is unrecognized.
		 * @exception	std::invalid_argument	If @p interp or @p traj is @c nullptr.
		 *
		 * @param [in]	interp	The represented interpretation. It cannot be null.
		 * @param 	  	guid  	The guid to set to the wellbore frame representation. If empty then a new
		 * 						guid will be generated.
		 * @param 	  	title 	The title to set to the wellbore frame representation. If empty then
		 * 						\"unknown\" title will be set.
		 * @param [in]	traj  	The wellbore trajectory that refers this wellbore frame. It cannot be
		 * 						null.
		 *
		 * @returns	A pointer to the new wellbore frame representation.
		 */
		DLL_IMPORT_OR_EXPORT RESQML2_NS::WellboreFrameRepresentation* createWellboreFrameRepresentation(RESQML2_NS::WellboreInterpretation* interp, const std::string& guid, const std::string& title, RESQML2_NS::WellboreTrajectoryRepresentation* traj);

		/**
		 * @brief	Creates a seismic wellbore frame representation into this repository
		 *
		 * @exception	std::invalid_argument	If @p interp, @p traj or @p crs is @c nullptr.
		 *
		 * @param [in]	interp				 	The represented interpretation. It cannot be null.
		 * @param 	  	guid				 	The guid to set to the seismic wellbore frame
		 * 										representation. If empty then a new guid will be
		 * 										generated.
		 * @param 	  	title				 	The title to set to the seismic wellbore frame
		 * 										representation. If empty then \"unknown\" title will be
		 * 										set.
		 * @param [in]	traj				 	The wellbore trajectory that refers this seismic wellbore
		 * 										frame. It cannot be null.
		 * @param 	  	seismicReferenceDatum	The Z value where the seismic time is equal to zero for
		 * 										this survey wellbore frame.
		 * @param 	  	weatheringVelocity   	The weathering velocity. Sometimes also called seismic
		 * 										velocity replacement.
		 * @param [in]	crs					 	The local time 3d CRS that refers this seismic wellbore
		 * 										frame.
		 *
		 * @returns	A pointer to the new seismic wellbore frame representation.
		 */
		DLL_IMPORT_OR_EXPORT RESQML2_NS::SeismicWellboreFrameRepresentation* createSeismicWellboreFrameRepresentation(
			RESQML2_NS::WellboreInterpretation* interp,
			const std::string& guid, const std::string& title, 
			RESQML2_NS::WellboreTrajectoryRepresentation* traj,
			double seismicReferenceDatum,
			double weatheringVelocity,
			RESQML2_NS::LocalTime3dCrs* crs);

		/**
		 * Creates a wellbore marker frame representation into this repository
		 *
		 * @exception	std::invalid_argument	If the default RESQML version is unrecognized.
		 * @exception	std::invalid_argument	If @p interp of @p traj is @c nullptr.
		 *
		 * @param [in]	interp	The represented interpretation. It cannot be null.
		 * @param 	  	guid  	The guid to set to the wellbore marker frame representation. If empty
		 * 						then a new guid will be generated.
		 * @param 	  	title 	The title to set to the wellbore marker frame representation. If empty
		 * 						then \"unknown\" title will be set.
		 * @param [in]	traj  	The wellbore trajectory that refers this wellbore marker frame. It cannot
		 * 						be null.
		 *
		 * @returns	A pointer to the new wellbore marker frame representation.
		 */
		DLL_IMPORT_OR_EXPORT RESQML2_NS::WellboreMarkerFrameRepresentation* createWellboreMarkerFrameRepresentation(RESQML2_NS::WellboreInterpretation* interp, const std::string& guid, const std::string& title, RESQML2_NS::WellboreTrajectoryRepresentation* traj);

		/**
		 * @brief	Creates a wellbore marker within a given wellbore marker frame representation.
		 *
		 * @exception	std::invalid_argument	If <tt>wellboreMarkerFrame == nullptr</tt>.
		 *
		 * @param [in]	wellboreMarkerFrame	The wellbore marker frame representation where to push back
		 * 									the wellbore marker.
		 * @param 	  	guid			   	The guid to set to the wellbore marker. If empty then a new
		 * 									guid will be generated.
		 * @param 	  	title			   	The title to set to the wellbore marker. If empty then
		 * 									\"unknown\" title will be set.
		 *
		 * @returns	A pointer to the new wellbore marker.
		 */
		DLL_IMPORT_OR_EXPORT RESQML2_NS::WellboreMarker* createWellboreMarker(RESQML2_NS::WellboreMarkerFrameRepresentation* wellboreMarkerFrame, const std::string& guid, const std::string& title);

		/**
		 * @brief	Creates a wellbore marker within a given wellbore marker frame representation.
		 *
		 * @exception	std::invalid_argument	If <tt>wellboreMarkerFrame == nullptr</tt>.
		 *
		 * @param [in]	wellboreMarkerFrame 	The wellbore marker frame representation where to push
		 * 										back the wellbore marker.
		 * @param 	  	guid					The guid to set to the wellbore marker. If empty then a
		 * 										new guid will be generated.
		 * @param 	  	title					The title to set to the wellbore marker. If empty then
		 * 										\"unknown\" title will be set.
		 * @param 	  	geologicBoundaryKind	The geologic boundary kind.
		 *
		 * @returns	A pointer to the new wellbore marker.
		 */
		DLL_IMPORT_OR_EXPORT RESQML2_NS::WellboreMarker* createWellboreMarker(RESQML2_NS::WellboreMarkerFrameRepresentation* wellboreMarkerFrame, const std::string& guid, const std::string& title, gsoap_resqml2_0_1::resqml20__GeologicBoundaryKind geologicBoundaryKind);

		/**
		 * @brief	Creates a blocked wellbore representation into this repository
		 *
		 * @exception	std::invalid_argument	If the default RESQML version is unrecognized.
		 * @exception	std::invalid_argument	If <tt>traj == nullptr</tt>.
		 *
		 * @param [in]	interp	The represented interpretation. It cannot be null.
		 * @param 	  	guid  	The guid to set to the blocked wellbore representation. If empty then a
		 * 						new guid will be generated.
		 * @param 	  	title 	The title to set to the blocked wellbore representation. If empty then
		 * 						\"unknown\" title will be set.
		 * @param [in]	traj  	The wellbore trajectory that refers this blocked wellbore representation.
		 * 						It cannot be null.
		 *
		 * @returns	A pointer to the new blocked wellbore representation.
		 */
		DLL_IMPORT_OR_EXPORT RESQML2_NS::BlockedWellboreRepresentation* createBlockedWellboreRepresentation(RESQML2_NS::WellboreInterpretation* interp,
			const std::string& guid, const std::string& title, RESQML2_NS::WellboreTrajectoryRepresentation* traj);

		/**
		 * @brief	Creates a representation set representation into this repository
		 *
		 * @exception	std::invalid_argument	If the default RESQML version is unrecognized.
		 * @exception	std::invalid_argument	If <tt>interp == nullptr</tt>.
		 *
		 * @param [in]	interp	The represented interpretation. It cannot be null. You can alternatively
		 * 						use {@link  createRepresentationSetRepresentation} if no interpretation
		 * 						is associated to this representation.
		 * @param 	  	guid  	The guid to set to the representation set representation. If empty then a
		 * 						new guid will be generated.
		 * @param 	  	title 	The title to set to the representation set representation. If empty then
		 * 						\"unknown\" title will be set.
		 *
		 * @returns	A pointer to the new representation set representation.
		 */
		DLL_IMPORT_OR_EXPORT RESQML2_NS::RepresentationSetRepresentation* createRepresentationSetRepresentation(
			RESQML2_NS::AbstractOrganizationInterpretation* interp,
			const std::string & guid,
			const std::string & title);

		/**
		 * @brief	Creates a representation set representation into this repository
		 *
		 * @exception	std::invalid_argument	If the default RESQML version is unrecognized.
		 *
		 * @param 	guid 	The guid to set to the representation set representation. If empty then a new
		 * 					guid will be generated.
		 * @param 	title	The title to set to the representation set representation. If empty then
		 * 					\"unknown\" title will be set.
		 *
		 * @returns	A pointer to the new representation set representation.
		 */
		DLL_IMPORT_OR_EXPORT RESQML2_NS::RepresentationSetRepresentation* createRepresentationSetRepresentation(
			const std::string & guid,
			const std::string & title);

		/**
		 * @brief	Creates a non sealed surface framework representation into this repository
		 *
		 * @exception	std::invalid_argument	If the default RESQML version is unrecognized.
		 * @exception	std::invalid_argument	If <tt>interp == nullptr</tt>.
		 *
		 * @param [in]	interp	The represented interpretation. It cannot be null.
		 * @param 	  	guid  	The guid to set to the non sealed surface framework representation. If
		 * 						empty then a new guid will be generated.
		 * @param 	  	title 	The title to set to the non sealed surface framework representation. If
		 * 						empty then \"unknown\" title will be set.
		 *
		 * @returns	A pointer to the new non sealed surface framework representation.
		 */
		DLL_IMPORT_OR_EXPORT RESQML2_NS::NonSealedSurfaceFrameworkRepresentation* createNonSealedSurfaceFrameworkRepresentation(
			RESQML2_NS::StructuralOrganizationInterpretation* interp,
			const std::string & guid,
			const std::string & title);

		/**
		 * @brief	Creates a sealed surface framework representation into this repository
		 *
		 * @exception	std::invalid_argument	If the default RESQML version is unrecognized.
		 * @exception	std::invalid_argument	If <tt>interp == nullptr</tt>.
		 *
		 * @param [in]	interp	The represented interpretation. It cannot be null.
		 * @param 	  	guid  	The guid to set to the sealed surface framework representation. If empty
		 * 						then a new guid will be generated.
		 * @param 	  	title 	The title to set to the sealed surface framework representation. If empty
		 * 						then \"unknown\" title will be set.
		 *
		 * @returns	A pointer to the new sealed surface framework representation.
		 */
		DLL_IMPORT_OR_EXPORT RESQML2_NS::SealedSurfaceFrameworkRepresentation* createSealedSurfaceFrameworkRepresentation(
			RESQML2_NS::StructuralOrganizationInterpretation* interp,
			const std::string & guid,
			const std::string & title);

		/**
		 * @brief	Creates a sealed volume framework representation into this repository
		 *
		 * @exception	std::invalid_argument	If the default RESQML version is unrecognized.
		 * @exception	std::invalid_argument	If <tt>interp == nullptr</tt> or <tt>ssf == nullptr</tt>.
		 *
		 * @param [in]	interp	The represented interpretation. It cannot be null.
		 * @param 	  	guid  	The guid to set to the sealed volume framework representation. If empty
		 * 						then a new guid will be generated.
		 * @param 	  	title 	The title to set to the sealed volume framework representation. If empty
		 * 						then \"unknown\" title will be set.
		 * @param [in]	ssf   	The sealed surface framework that refers this sealed volume framework. It
		 * 						cannot be null.
		 *
		 * @returns	A pointer to the new sealed volume framework representation.
		 */
		DLL_IMPORT_OR_EXPORT RESQML2_NS::SealedVolumeFrameworkRepresentation* createSealedVolumeFrameworkRepresentation(
			RESQML2_NS::StratigraphicColumnRankInterpretation* interp,
			const std::string & guid,
			const std::string & title,
			RESQML2_NS::SealedSurfaceFrameworkRepresentation* ssf);

		/**
		 * Creates a partial ijk grid representation into this repository
		 *
		 * @param 	guid 	The guid to set to the sealed volume framework representation. If empty
		 * 					then a new guid will be generated.
		 * @param 	title	The title to set to the sealed volume framework representation.
		 *
		 * @returns	A pointer to the new partial ijk grid representation.
		 */
		DLL_IMPORT_OR_EXPORT RESQML2_NS::AbstractIjkGridRepresentation* createPartialIjkGridRepresentation(const std::string& guid, const std::string& title);

		/**
		 * Creates a partial truncated ijk grid representation into this repository
		 *
		 * @param 	guid 	The guid to set to the sealed volume framework representation.
		 * @param 	title	The title to set to the sealed volume framework representation.
		 *
		 * @returns	A pointer to the new partial truncated ijk grid representation.
		 */
		DLL_IMPORT_OR_EXPORT RESQML2_NS::AbstractIjkGridRepresentation* createPartialTruncatedIjkGridRepresentation(const std::string& guid, const std::string& title);

		/**
		 * @brief	Creates an ijk grid explicit representation into this repository
		 *
		 * @exception	std::invalid_argument	If the default RESQML version is unrecognized.
		 *
		 * @param 	guid  	The guid to set to the ijk grid explicit representation. If empty then a new
		 * 					guid will be generated.
		 * @param 	title 	The title to set to the ijk grid explicit representation. If empty then
		 * 					\"unknown\" title will be set.
		 * @param 	iCount	Count of cells in the I direction in the grid.
		 * @param 	jCount	Count of cells in the J direction in the grid.
		 * @param 	kCount	Number of layers in the grid.
		 *
		 * @returns	A pointer to the new ijk grid explicit representation.
		 */
		DLL_IMPORT_OR_EXPORT RESQML2_NS::IjkGridExplicitRepresentation* createIjkGridExplicitRepresentation(const std::string& guid, const std::string& title,
			unsigned int iCount, unsigned int jCount, unsigned int kCount);

		/**
		 * @brief	Creates an ijk grid explicit representation into this repository
		 *
		 * @exception	std::invalid_argument	If the default RESQML version is unrecognized.
		 * @exception	std::invalid_argument	If <tt>interp == nullptr</tt>.
		 *
		 * @param [in]	interp	The represented interpretation. It cannot be null.
		 * @param 	  	guid  	The guid to set to the ijk grid explicit representation. If empty then a
		 * 						new guid will be generated.
		 * @param 	  	title 	The title to set to the ijk grid explicit representation. If empty then
		 * 						\"unknown\" title will be set.
		 * @param 	  	iCount	Count of cells in the I direction in the grid.
		 * @param 	  	jCount	Count of cells in the J direction in the grid.
		 * @param 	  	kCount	Number of layers in the grid.
		 *
		 * @returns	A pointer to the new ijk grid explicit representation.
		 */
		DLL_IMPORT_OR_EXPORT RESQML2_NS::IjkGridExplicitRepresentation* createIjkGridExplicitRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp,
			const std::string& guid, const std::string& title,
			unsigned int iCount, unsigned int jCount, unsigned int kCount);

		/**
		 * @brief	Creates an ijk grid parametric representation into this repository
		 *
		 * @exception	std::invalid_argument	If the default RESQML version is unrecognized.
		 *
		 * @param 	guid  	The guid to set to the ijk grid parametric representation. If empty then a
		 * 					new guid will be generated.
		 * @param 	title 	The title to set to the ijk grid parametric representation. If empty then
		 * 					\"unknown\" title will be set.
		 * @param 	iCount	Count of cells in the I direction in the grid.
		 * @param 	jCount	Count of cells in the J direction in the grid.
		 * @param 	kCount	Number of layers in the grid.
		 *
		 * @returns	A pointer to the new ijk grid parametric representation.
		 */
		DLL_IMPORT_OR_EXPORT RESQML2_NS::IjkGridParametricRepresentation* createIjkGridParametricRepresentation(const std::string& guid, const std::string& title,
			unsigned int iCount, unsigned int jCount, unsigned int kCount);

		/**
		 * @brief	Creates an ijk grid parametric representation into this repository
		 *
		 * @exception	std::invalid_argument	If the default RESQML version is unrecognized.
		 * @exception	std::invalid_argument	If <tt>interp == nullptr</tt>.
		 *
		 * @param [in]	interp	The represented interpretation. It cannot be null.
		 * @param 	  	guid  	The guid to set to the ijk grid parametric representation. If empty then
		 * 						a new guid will be generated.
		 * @param 	  	title 	The title to set to the ijk grid parametric representation. If empty then
		 * 						\"unknown\" title will be set.
		 * @param 	  	iCount	Count of cells in the I direction in the grid.
		 * @param 	  	jCount	Count of cells in the J direction in the grid.
		 * @param 	  	kCount	Number of layers in the grid.
		 *
		 * @returns	A pointer to the new ijk grid parametric representation.
		 */
		DLL_IMPORT_OR_EXPORT RESQML2_NS::IjkGridParametricRepresentation* createIjkGridParametricRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp,
			const std::string& guid, const std::string& title,
			unsigned int iCount, unsigned int jCount, unsigned int kCount);

		/**
		 * @brief	Creates an ijk grid lattice representation into this repository
		 *
		 * @exception	std::invalid_argument	If the default RESQML version is unrecognized.
		 *
		 * @param 	guid  	The guid to set to the ijk grid lattice representation. If empty then a new
		 * 					guid will be generated.
		 * @param 	title 	The title to set to the ijk grid lattice representation. If empty then
		 * 					\"unknown\" title will be set.
		 * @param 	iCount	Count of cells in the I direction in the grid.
		 * @param 	jCount	Count of cells in the J direction in the grid.
		 * @param 	kCount	Number of layers in the grid.
		 *
		 * @returns	A pointer to the new ijk grid lattice representation.
		 */
		DLL_IMPORT_OR_EXPORT RESQML2_NS::IjkGridLatticeRepresentation* createIjkGridLatticeRepresentation(const std::string& guid, const std::string& title,
			unsigned int iCount, unsigned int jCount, unsigned int kCount);

		/**
		 * @brief	Creates an ijk grid lattice representation into this repository
		 *
		 * @exception	std::invalid_argument	If the default RESQML version is unrecognized.
		 * @exception	std::invalid_argument	If <tt>interp == nullptr</tt>.
		 *
		 * @param [in]	interp	The represented interpretation. It cannot be null.
		 * @param 	  	guid  	The guid to set to the ijk grid lattice representation. If empty then a
		 * 						new guid will be generated.
		 * @param 	  	title 	The title to set to the ijk grid lattice representation. If empty then
		 * 						\"unknown\" title will be set.
		 * @param 	  	iCount	Count of cells in the I direction in the grid.
		 * @param 	  	jCount	Count of cells in the J direction in the grid.
		 * @param 	  	kCount	Number of layers in the grid.
		 *
		 * @returns	A pointer to the new ijk grid lattice representation.
		 */
		DLL_IMPORT_OR_EXPORT RESQML2_NS::IjkGridLatticeRepresentation* createIjkGridLatticeRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp,
			const std::string& guid, const std::string& title,
			unsigned int iCount, unsigned int jCount, unsigned int kCount);

		/**
		 * @brief	Creates an ijk grid with no geometry representation into this repository
		 *
		 * @exception	std::invalid_argument	If the default RESQML version is unrecognized.
		 *
		 * @param 	guid  	The guid to set to the ijk grid with no geometry representation. If empty
		 * 					then a new guid will be generated.
		 * @param 	title 	The title to set to the ijk grid with no geometry representation. If empty
		 * 					then \"unknown\" title will be set.
		 * @param 	iCount	Count of cells in the I direction in the grid.
		 * @param 	jCount	Count of cells in the J direction in the grid.
		 * @param 	kCount	Number of layers in the grid.
		 *
		 * @returns	A pointer to the new ijk grid with no geometry representation.
		 */
		DLL_IMPORT_OR_EXPORT RESQML2_NS::IjkGridNoGeometryRepresentation* createIjkGridNoGeometryRepresentation(
			const std::string& guid, const std::string& title,
			unsigned int iCount, unsigned int jCount, unsigned int kCount);

		/**
		 * @brief	Creates an ijk grid with no geometry representation into this repository
		 *
		 * @exception	std::invalid_argument	If the default RESQML version is unrecognized.
		 * @exception	std::invalid_argument	If <tt>interp == nullptr</tt>.
		 *
		 * @param [in]	interp	The represented interpretation. It cannot be null.
		 * @param 	  	guid  	The guid to set to the ijk grid with no geometry representation. If empty
		 * 						then a new guid will be generated.
		 * @param 	  	title 	The title to set to the ijk grid with no geometry representation. If
		 * 						empty then \"unknown\" title will be set.
		 * @param 	  	iCount	Count of cells in the I direction in the grid.
		 * @param 	  	jCount	Count of cells in the J direction in the grid.
		 * @param 	  	kCount	Number of layers in the grid.
		 *
		 * @returns	A pointer to the new ijk grid with no geometry representation.
		 */
		DLL_IMPORT_OR_EXPORT RESQML2_NS::IjkGridNoGeometryRepresentation* createIjkGridNoGeometryRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp,
			const std::string& guid, const std::string& title,
			unsigned int iCount, unsigned int jCount, unsigned int kCount);

		/**
		 * @brief	Creates an unstructured grid representation into this repository
		 *
		 * @exception	std::invalid_argument	If the default RESQML version is unrecognized.
		 *
		 * @param 	guid	 	The guid to set to the unstructured grid representation. If empty then a
		 * 						new guid will be generated.
		 * @param 	title	 	The title to set to the unstructured grid representation. If empty then
		 * 						\"unknown\" title will be set.
		 * @param 	cellCount	Number of cells in the grid.
		 *
		 * @returns	A pointer to the new unstructured grid representation.
		 */
		DLL_IMPORT_OR_EXPORT RESQML2_NS::UnstructuredGridRepresentation* createUnstructuredGridRepresentation(const std::string& guid, const std::string& title,
			const ULONG64 & cellCount);

		/**
		 * @brief	Creates a sub-representation into this repository
		 *
		 * @exception	std::invalid_argument	If the default RESQML version is unrecognized.
		 *
		 * @param 	guid 	The guid to set to the sub-representation. If empty then a new guid will be
		 * 					generated.
		 * @param 	title	The title to set to the sub-representation. If empty then \"unknown\" title
		 * 					will be set.
		 *
		 * @returns	A pointer to the new sub-representation.
		 */
		DLL_IMPORT_OR_EXPORT RESQML2_NS::SubRepresentation* createSubRepresentation(
			const std::string & guid, const std::string & title);

		/**
		 * @brief	Creates a sub-representation into this repository
		 *
		 * @exception	std::invalid_argument	If the default RESQML version is unrecognized.
		 * @exception	std::invalid_argument	If <tt>interp == nullptr</tt>.
		 *
		 * @param [in]	interp	The represented interpretation. It cannot be null. You can alternatively
		 * 						use {@link  createSubRepresentation} if no interpretation is associated
		 * 						to this representation.
		 * @param 	  	guid  	The guid to set to the sub-representation. If empty then a new guid will
		 * 						be generated.
		 * @param 	  	title 	The title to set to the sub-representation. If empty then \"unknown\"
		 * 						title will be set.
		 *
		 * @returns	A pointer to the new sub-representation.
		 */
		DLL_IMPORT_OR_EXPORT RESQML2_NS::SubRepresentation* createSubRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp,
			const std::string & guid, const std::string & title);

		/**
		 * @brief	Creates a grid connection set representation into this repository
		 *
		 * @exception	std::invalid_argument	If the default RESQML version is unrecognized.
		 *
		 * @param 	guid 	The guid to set to the grid connection set representation. If empty then a
		 * 					new guid will be generated.
		 * @param 	title	The title to set to the grid connection set representation. If empty then
		 * 					\"unknown\" title will be set.
		 *
		 * @returns	A pointer to the new grid connection set representation.
		 */
		DLL_IMPORT_OR_EXPORT RESQML2_NS::GridConnectionSetRepresentation* createGridConnectionSetRepresentation(const std::string & guid, const std::string & title);

		/**
		 * @brief	Creates a grid connection set representation into this repository
		 *
		 * @exception	std::invalid_argument	If the default RESQML version is unrecognized.
		 * @exception	std::invalid_argument	If <tt>interp == nullptr</tt>.
		 *
		 * @param [in]	interp	The represented interpretation. It cannot be null. You can alternatively
		 * 						use {@link  createGridConnectionSetRepresentation} if no interpretation
		 * 						is associated to this representation.
		 * @param 	  	guid  	The guid to set to the grid connection set representation. If empty then
		 * 						a new guid will be generated.
		 * @param 	  	title 	The title to set to the grid connection set representation. If empty then
		 * 						\"unknown\" title will be set.
		 *
		 * @returns	A pointer to the new grid connection set representation.
		 */
		DLL_IMPORT_OR_EXPORT RESQML2_NS::GridConnectionSetRepresentation* createGridConnectionSetRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp,
			const std::string & guid, const std::string & title);

		//************* PROPERTIES ***********

		/**
		 * @brief	Creates a time series into this repository
		 *
		 * @exception	std::invalid_argument	If the default RESQML version is unrecognized.
		 *
		 * @param 	guid 	The guid to set to the time series. If empty then a new guid will be
		 * 					generated.
		 * @param 	title	The title to set to the time series. If empty then \"unknown\" title will be
		 * 					set.
		 *
		 * @returns	A pointer to the new time series.
		 */
		DLL_IMPORT_OR_EXPORT EML2_NS::TimeSeries* createTimeSeries(const std::string & guid, const std::string & title);

		/**
		 * @brief	Creates a double table lookup into this repository
		 *
		 * @exception	std::invalid_argument	If the default RESQML version is unrecognized.
		 *
		 * @param 	guid 	The guid to set to the double table lookup. If empty then a new guid will be
		 * 					generated.
		 * @param 	title	The title to set to the double table lookup. If empty then \"unknown\" title
		 * 					will be set.
		 *
		 * @returns	A pointer to the new double table lookup.
		 */
		DLL_IMPORT_OR_EXPORT RESQML2_NS::DoubleTableLookup* createDoubleTableLookup(const std::string & guid, const std::string & title);

		/**
		 * @brief	Creates a string table lookup into this repository
		 *
		 * @exception	std::invalid_argument	If the default RESQML version is unrecognized.
		 *
		 * @param 	guid 	The guid to set to the string table lookup. If empty then a new guid will be
		 * 					generated.
		 * @param 	title	The title to set to the string table lookup. If empty then \"unknown\" title
		 * 					will be set.
		 *
		 * @returns	A pointer to the new string table lookup.
		 */
		DLL_IMPORT_OR_EXPORT RESQML2_NS::StringTableLookup* createStringTableLookup(const std::string & guid, const std::string & title);

		/**
		 * Creates a property kind into this repository
		 *
		 * @param 	guid						 	The guid to set to the property kind. If empty then a
		 * 											new guid will be generated.
		 * @param 	title						 	The title to set to the property kind. If empty then
		 * 											\"unknown\" title will be set.
		 * @param 	namingSystem				 	The name of the dictionary within which the property
		 * 											is unique. This also defines the name of the
		 * 											controlling authority. Use a URN of the form <tt>urn:x-
		 * 											resqml:domainOrEmail:dictionaryName</tt>.
		 * @param 	uom							 	The property kind unit of measure taken from the
		 * 											standard RESQML units of measure catalog.
		 * @param 	parentEnergisticsPropertyKind	The parent property kind taken from the standard set
		 * 											of RESQML property kinds.
		 *
		 * @returns	A pointer to the new property kind.
		 */
		DLL_IMPORT_OR_EXPORT RESQML2_0_1_NS::PropertyKind* createPropertyKind(const std::string & guid, const std::string & title,
			const std::string & namingSystem, gsoap_resqml2_0_1::resqml20__ResqmlUom uom, gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind parentEnergisticsPropertyKind);

		/**
		 * @brief	Creates a property kind into this repository
		 *
		 * @exception	std::invalid_argument	If <tt>parentPropType == nullptr</tt>.
		 *
		 * @param 	  	guid		  	The guid to set to the property kind. If empty then a new guid
		 * 								will be generated.
		 * @param 	  	title		  	The title to set to the property kind. If empty then \"unknown\"
		 * 								title will be set.
		 * @param 	  	namingSystem  	The name of the dictionary within which the property is unique.
		 * 								This also defines the name of the controlling authority. Use a
		 * 								URN of the form \"urn:x- resqml:domainOrEmail:dictionaryName\".
		 * @param 	  	uom			  	The property kind unit of measure taken from the standard RESQML
		 * 								units of measure catalog.
		 * @param [in]	parentPropType	The parent property kind. It cannot be null.
		 *
		 * @returns	A pointer to the new property kind.
		 */
		DLL_IMPORT_OR_EXPORT RESQML2_0_1_NS::PropertyKind* createPropertyKind(const std::string & guid, const std::string & title,
			const std::string & namingSystem, gsoap_resqml2_0_1::resqml20__ResqmlUom uom, EML2_NS::PropertyKind * parentPropType);

		/**
		 * Creates a property kind into this repository.
		 *
		 * @param 	guid						 	The guid to set to the property kind. If empty then a
		 * 											new guid will be generated.
		 * @param 	title						 	The title to set to the property kind. If empty then
		 * 											\"unknown\" title will be set.
		 * @param 	namingSystem				 	The name of the dictionary within which the property
		 * 											is unique. This also defines the name of the
		 * 											controlling authority. Use a URN of the form \"urn:x-
		 * 											resqml:domainOrEmail:dictionaryName\".
		 * @param 	nonStandardUom				 	The property kind unit of measure.
		 * @param 	parentEnergisticsPropertyKind	The parent property kind taken from the standard set
		 * 											of RESQML property kinds.
		 *
		 * @returns	A pointer to the new property kind.
		 */
		DLL_IMPORT_OR_EXPORT RESQML2_0_1_NS::PropertyKind* createPropertyKind(const std::string & guid, const std::string & title,
			const std::string & namingSystem, const std::string & nonStandardUom, gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind parentEnergisticsPropertyKind);

		/**
		 * Creates a property kind into this repository
		 *
		 * @param 	  	guid		  	The guid to set to the property kind. If empty then a new guid
		 * 								will be generated.
		 * @param 	  	title		  	The title to set to the property kind. If empty then \"unknown\"
		 * 								title will be set.
		 * @param 	  	namingSystem  	The name of the dictionary within which the property is unique.
		 * 								This also defines the name of the controlling authority. Use a
		 * 								URN of the form \"urn:x- resqml:domainOrEmail:dictionaryName\".
		 * @param 	  	nonStandardUom	The property kind unit of measure.
		 * @param [in]	parentPropType	The parent property kind. It cannot be null.
		 *
		 * @returns	A pointer to the new property kind.
		 */
		DLL_IMPORT_OR_EXPORT RESQML2_0_1_NS::PropertyKind* createPropertyKind(const std::string & guid, const std::string & title,
			const std::string & namingSystem, const std::string & nonStandardUom, EML2_NS::PropertyKind * parentPropType);

		/**
		 * @brief	Creates an EML2.1 property kind into this repository
		 *
		 * @exception	std::invalid_argument	If the default RESQML version is unrecognized.
		 *
		 * @param 	  	guid			  	The guid to set to the property kind. If empty then a new
		 * 									guid will be generated.
		 * @param 	  	title			  	The title to set to the property kind. If empty then
		 * 									\"unknown\" title will be set.
		 * @param 	  	quantityClass	  	A reference to the name of a quantity class in the
		 * 									Energistics units of measure dictionary.
		 * @param 	  	isAbstract		  	(Optional) Indicates whether the property kind should be used
		 * 									as a real (default) property or not.
		 * @param [in]	parentPropertyKind	(Optional) If non-null, the parent property kind. If null, a
		 * 									default partial parent property kind will be created.
		 *
		 * @returns	A pointer to the new property kind.
		 */
		DLL_IMPORT_OR_EXPORT EML2_NS::PropertyKind* createPropertyKind(const std::string & guid, const std::string & title,
			gsoap_eml2_1::eml21__QuantityClassKind quantityClass, bool isAbstract = false, EML2_NS::PropertyKind* parentPropertyKind = nullptr);

		/**
		 * @brief	Creates a property set into this repository.
		 *
		 * @exception	std::invalid_argument	If the default RESQML version is unrecognized.
		 * @exception	std::invalid_argument	If, in a RESQML v2.0 context, @p timeSetKind is single
		 * 										time series.
		 *
		 * @param 	guid				   	The guid to set to the property set. If empty then a new guid
		 * 									will be generated.
		 * @param 	title				   	The title to set to the property set. If empty then
		 * 									\"unknown\" title will be set.
		 * @param 	hasMultipleRealizations	True if the set contains properties with defined realization
		 * 									indices, false if not.
		 * @param 	hasSinglePropertyKind  	True if the set contains only property values associated with
		 * 									a single property kind, false if not.
		 * @param 	timeSetKind			   	The time relationship that share the properties of this set,
		 * 									if any.
		 *
		 * @returns	A pointer to the new property set.
		 */
		DLL_IMPORT_OR_EXPORT RESQML2_NS::PropertySet* createPropertySet(const std::string & guid, const std::string & title,
			bool hasMultipleRealizations, bool hasSinglePropertyKind, gsoap_eml2_3::resqml22__TimeSetKind timeSetKind);

		/**
		 * Creates a comment property (which is of a well known Energistics property kind) into this
		 * repository.
		 *
		 * @exception	std::invalid_argument	If @p rep is null.
		 *
		 * @param [in]	rep					   	The representation on which this property is attached to.
		 * 										It cannot be null.
		 * @param 	  	guid				   	The guid to set to the property. If empty then a new guid
		 * 										will be generated.
		 * @param 	  	title				   	The title to set to the property. If empty then
		 * 										\"unknown\" title will be set.
		 * @param 	  	dimension			   	The dimension of each value of this property. Dimension
		 * 										is 1 for a scalar property.
		 * @param 	  	attachmentKind		   	The topological element on which the property values are
		 * 										attached to.
		 * @param 	  	energisticsPropertyKind	The property kind of these property values which must be
		 * 										defined in the standard Energistics property type
		 * 										dictionary.
		 *
		 * @returns	A pointer to the new comment property.
		 */
		DLL_IMPORT_OR_EXPORT RESQML2_0_1_NS::CommentProperty* createCommentProperty(RESQML2_NS::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			unsigned int dimension, gsoap_eml2_3::resqml22__IndexableElement attachmentKind, gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind energisticsPropertyKind);

		/**
		 * Creates a comment property (which is of a local property kind) into this repository
		 *
		 * @exception	std::invalid_argument	If the default RESQML version is unrecognized.
		 * @exception	std::invalid_argument	If @p rep or @p localPropKind is null.
		 *
		 * @param [in]	rep			  	The representation on which this property is attached to. It
		 * 								cannot be null.
		 * @param 	  	guid		  	The guid to set to the property. If empty then a new guid will be
		 * 								generated.
		 * @param 	  	title		  	The title to set to the property. If empty then \"unknown\" title
		 * 								will be set.
		 * @param 	  	dimension	  	The dimension of each value of this property. Dimension is 1 for
		 * 								a scalar property.
		 * @param 	  	attachmentKind	The topological element on which the property values are attached
		 * 								to.
		 * @param [in]	localPropType 	The property kind of these property values which must be defined
		 * 								in the EPC document as a local property kind. It cannot be null.
		 *
		 * @returns	A pointer to the new comment property.
		 */
		DLL_IMPORT_OR_EXPORT RESQML2_NS::CommentProperty* createCommentProperty(RESQML2_NS::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			unsigned int dimension, gsoap_eml2_3::resqml22__IndexableElement attachmentKind, EML2_NS::PropertyKind * localPropType);

		/**
		 * Creates a continuous property (which is of well known Energistics unit of measure and
		 * property kind) into this repository
		 *
		 * @exception	std::invalid_argument	If @p rep is null.
		 *
		 * @param [in]	rep					   	The representation on which this property is attached to.
		 * 										It cannot be null.
		 * @param 	  	guid				   	The guid to set to the property. If empty then a new guid
		 * 										will be generated.
		 * @param 	  	title				   	The title to set to the property. If empty then
		 * 										\"unknown\" title will be set.
		 * @param 	  	dimension			   	The dimension of each value of this property. Dimension
		 * 										is 1 for a scalar property.
		 * @param 	  	attachmentKind		   	The topological element on which the property values are
		 * 										attached to.
		 * @param 	  	uom					   	The property unit of measure taken from the standard
		 * 										Energistics units of measure catalog. Please check
		 * 										COMMON_NS::EnumStringMapper::getEnergisticsUnitOfMeasure
		 * 										in order to minimize the use of non standard unit of
		 * 										measure.
		 * @param 	  	energisticsPropertyKind	The property kind of these property values which must be
		 * 										defined in the standard Energistics property type
		 * 										dictionary.
		 *
		 * @returns	A pointer to the new continuous property.
		 */
		DLL_IMPORT_OR_EXPORT RESQML2_0_1_NS::ContinuousProperty* createContinuousProperty(RESQML2_NS::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			unsigned int dimension, gsoap_eml2_3::resqml22__IndexableElement attachmentKind, gsoap_resqml2_0_1::resqml20__ResqmlUom uom, gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind energisticsPropertyKind);

		/**
		 * Creates a continuous property (which is of a well known unit of measure and a local property
		 * kind) into this repository
		 *
		 * @exception	std::invalid_argument	If the default RESQML version is unrecognized.
		 * @exception	std::invalid_argument	If @p rep or @p localPropType is null.
		 *
		 * @param [in]	rep			  	The representation on which this property is attached to. It
		 * 								cannot be null.
		 * @param 	  	guid		  	The guid to set to the property. If empty then a new guid will be
		 * 								generated.
		 * @param 	  	title		  	The title to set to the property. If empty then \"unknown\" title
		 * 								will be set.
		 * @param 	  	dimension	  	The dimension of each value of this property. Dimension is 1 for
		 * 								a scalar property.
		 * @param 	  	attachmentKind	The topological element on which the property values are attached
		 * 								to.
		 * @param 	  	uom			  	The property unit of measure taken from the standard Energistics
		 * 								units of measure catalog. Please check
		 * 								COMMON_NS::EnumStringMapper::getEnergisticsUnitOfMeasure in order
		 * 								to minimize the use of non standard unit of measure.
		 * @param [in]	localPropType 	The property kind of these property values which must be defined
		 * 								in the EPC document as a local property kind. It cannot be null.
		 *
		 * @returns	A pointer to the new continuous property.
		 */
		DLL_IMPORT_OR_EXPORT RESQML2_NS::ContinuousProperty* createContinuousProperty(RESQML2_NS::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			unsigned int dimension, gsoap_eml2_3::resqml22__IndexableElement attachmentKind, gsoap_resqml2_0_1::resqml20__ResqmlUom uom, EML2_NS::PropertyKind * localPropType);

		/**
		 * Creates a continuous property (which is of a local unit of measure and a well known property
		 * kind) into this repository
		 *
		 * @exception	std::invalid_argument	If @p rep is null.
		 *
		 * @param [in]	rep					   	The representation on which this property is attached to.
		 * 										It cannot be null.
		 * @param 	  	guid				   	The guid to set to the property. If empty then a new guid
		 * 										will be generated.
		 * @param 	  	title				   	The title to set to the property. If empty then
		 * 										\"unknown\" title will be set.
		 * @param 	  	dimension			   	The dimension of each value of this property. Dimension
		 * 										is 1 for a scalar property.
		 * @param 	  	attachmentKind		   	The topological element on which the property values are
		 * 										attached to.
		 * @param 	  	nonStandardUom		   	The property unit of measure. Please check
		 * 										COMMON_NS::EnumStringMapper::getEnergisticsUnitOfMeasure
		 * 										in order to minimize the use of non standard unit of
		 * 										measure.
		 * @param 	  	energisticsPropertyKind	The property kind of these property values which must be
		 * 										defined in the standard Energistics property type
		 * 										dictionary.
		 *
		 * @returns	A pointer to the new continuous property.
		 */
		DLL_IMPORT_OR_EXPORT RESQML2_0_1_NS::ContinuousProperty* createContinuousProperty(RESQML2_NS::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			unsigned int dimension, gsoap_eml2_3::resqml22__IndexableElement attachmentKind, std::string nonStandardUom, gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind energisticsPropertyKind);

		/**
		 * Creates a continuous property (which is of local unit of measure and property kind) into this
		 * repository
		 *
		 * @exception	std::invalid_argument	If the default RESQML version is unrecognized.
		 * @exception	std::invalid_argument	If @p rep or @p localPropType is null.
		 *
		 * @param [in]	rep			  	The representation on which this property is attached to. It
		 * 								cannot be null.
		 * @param 	  	guid		  	The guid to set to the property. If empty then a new guid will be
		 * 								generated.
		 * @param 	  	title		  	The title to set to the property. If empty then \"unknown\" title
		 * 								will be set.
		 * @param 	  	dimension	  	The dimension of each value of this property. Dimension is 1 for
		 * 								a scalar property.
		 * @param 	  	attachmentKind	The topological element on which the property values are attached
		 * 								to.
		 * @param 	  	nonStandardUom	The property unit of measure. Please check
		 * 								COMMON_NS::EnumStringMapper::getEnergisticsUnitOfMeasure in order
		 * 								to minimize the use of non standard unit of measure.
		 * @param [in]	localPropType 	The property kind of these property values which must be defined
		 * 								in the EPC document as a local property kind. It cannot be null.
		 *
		 * @returns	A pointer to the new continuous property.
		 */
		DLL_IMPORT_OR_EXPORT RESQML2_NS::ContinuousProperty* createContinuousProperty(RESQML2_NS::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			unsigned int dimension, gsoap_eml2_3::resqml22__IndexableElement attachmentKind, const std::string & nonStandardUom, EML2_NS::PropertyKind * localPropType);

		/**
		 * Creates a discrete property (which is of a well known Energistics property kind) into this
		 * repository
		 *
		 * @exception	std::invalid_argument	If @p rep is null.
		 *
		 * @param [in]	rep					   	The representation on which this property is attached to.
		 * 										It cannot be null.
		 * @param 	  	guid				   	The guid to set to the property. If empty then a new guid
		 * 										will be generated.
		 * @param 	  	title				   	The title to set to the property. If empty then
		 * 										\"unknown\" title will be set.
		 * @param 	  	dimension			   	The dimension of each value of this property. Dimension
		 * 										is 1 for a scalar property.
		 * @param 	  	attachmentKind		   	The topological element on which the property values are
		 * 										attached to.
		 * @param 	  	energisticsPropertyKind	The property kind of these property values which must be
		 * 										defined in the standard Energistics property type
		 * 										dictionary.
		 *
		 * @returns	A pointer to the new discrete property.
		 */
		DLL_IMPORT_OR_EXPORT RESQML2_0_1_NS::DiscreteProperty* createDiscreteProperty(RESQML2_NS::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			unsigned int dimension, gsoap_eml2_3::resqml22__IndexableElement attachmentKind, gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind energisticsPropertyKind);

		/**
		 * Creates a discrete property (which is of a local property kind) into this repository
		 *
		 * @exception	std::invalid_argument	If the default RESQML version is unrecognized.
		 * @exception	std::invalid_argument	If @p or @p localPropKind is null.
		 *
		 * @param [in]	rep			  	The representation on which this property is attached to. It
		 * 								cannot be null.
		 * @param 	  	guid		  	The guid to set to the property. If empty then a new guid will be
		 * 								generated.
		 * @param 	  	title		  	The title to set to the property. If empty then \"unknown\" title
		 * 								will be set.
		 * @param 	  	dimension	  	The dimension of each value of this property. Dimension is 1 for
		 * 								a scalar property.
		 * @param 	  	attachmentKind	The topological element on which the property values are attached
		 * 								to.
		 * @param [in]	localPropType 	The property kind of these property values which must be defined
		 * 								in the EPC document as a local property kind. It cannot be null.
		 *
		 * @returns	A pointer to the new discrete property.
		 */
		DLL_IMPORT_OR_EXPORT RESQML2_NS::DiscreteProperty* createDiscreteProperty(RESQML2_NS::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			unsigned int dimension, gsoap_eml2_3::resqml22__IndexableElement attachmentKind, EML2_NS::PropertyKind * localPropType);

		/**
		 * Creates a categorical property (which is of a standard Energistics property kind) into this
		 * repository
		 *
		 * @exception	std::invalid_argument	If @p rep or @p strLookup is null.
		 *
		 * @param [in]	rep					   	The representation on which this property is attached to.
		 * 										It cannot be null.
		 * @param 	  	guid				   	The guid to set to the property. If empty then a new guid
		 * 										will be generated.
		 * @param 	  	title				   	The title to set to the property. If empty then
		 * 										\"unknown\" title will be set.
		 * @param 	  	dimension			   	The dimension of each value of this property. Dimension
		 * 										is 1 for a scalar property.
		 * @param 	  	attachmentKind		   	The topological element on which the property values are
		 * 										attached to.
		 * @param [in]	strLookup			   	The string lookup which defines the possible string
		 * 										values and their keys.
		 * @param 	  	energisticsPropertyKind	The property kind of these property values which must be
		 * 										defined in the standard Energistics property type
		 * 										dictionary.
		 *
		 * @returns A pointer to new categorical property.
		 */
		DLL_IMPORT_OR_EXPORT RESQML2_0_1_NS::CategoricalProperty* createCategoricalProperty(RESQML2_NS::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			unsigned int dimension, gsoap_eml2_3::resqml22__IndexableElement attachmentKind,
			RESQML2_NS::StringTableLookup* strLookup, gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind energisticsPropertyKind);

		/**
		 * Creates a categorical property (which is of a standard Energistics property kind) into this
		 * repository
		 *
		 * @exception	std::invalid_argument	If @p rep or @p strLookup is null.
		 *
		 * @param [in]	rep					   	The representation on which this property is attached to.
		 * 										It cannot be null.
		 * @param 	  	guid				   	The guid to set to the property. If empty then a new guid
		 * 										will be generated.
		 * @param 	  	title				   	The title to set to the property. If empty then
		 * 										\"unknown\" title will be set.
		 * @param 	  	dimension			   	The dimension of each value of this property. Dimension
		 * 										is 1 for a scalar property.
		 * @param 	  	attachmentKind		   	The topological element on which the property values are
		 * 										attached to.
		 * @param [in]	dblLookup			   	The double lookup which defines a discrete function associated with the property values.
		 * @param 	  	energisticsPropertyKind	The property kind of these property values which must be
		 * 										defined in the standard Energistics property type
		 * 										dictionary.
		 *
		 * @returns A pointer to new categorical property.
		 */
		DLL_IMPORT_OR_EXPORT RESQML2_0_1_NS::CategoricalProperty* createCategoricalProperty(RESQML2_NS::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			unsigned int dimension, gsoap_eml2_3::resqml22__IndexableElement attachmentKind,
			RESQML2_NS::DoubleTableLookup* dblLookup, gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind energisticsPropertyKind);

		/**
		 * Creates a categorical property (which is of a local property kind) into this repository
		 *
		 * @exception	std::invalid_argument	If the default RESQML version is unrecognized.
		 * @exception	std::invalid_argument	If @p rep, @p strLookup or @p localPropKind is null.
		 *
		 * @param [in]	rep			  	The representation on which this property is attached to. It
		 * 								cannot be null.
		 * @param 	  	guid		  	The guid to set to the property. If empty then a new guid will be
		 * 								generated.
		 * @param 	  	title		  	The title to set to the property. If empty then \"unknown\" title
		 * 								will be set.
		 * @param 	  	dimension	  	The dimension of each value of this property. Dimension is 1 for
		 * 								a scalar property.
		 * @param 	  	attachmentKind	The topological element on which the property values are attached
		 * 								to.
		 * @param [in]	strLookup	  	The string lookup which defines the possible string values and
		 * 								their keys. It cannot be null.
		 * @param [in]	localPropType 	The property kind of these property values which must be defined
		 * 								in the EPC document as a local property kind. It cannot be null.
		 *
		 * @returns	A pointer to the new categorical property.
		 */
		DLL_IMPORT_OR_EXPORT RESQML2_NS::CategoricalProperty* createCategoricalProperty(RESQML2_NS::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			unsigned int dimension, gsoap_eml2_3::resqml22__IndexableElement attachmentKind,
			RESQML2_NS::StringTableLookup* strLookup, EML2_NS::PropertyKind * localPropType);

		/**
		 * Creates a categorical property (which is of a local property kind) into this repository
		 *
		 * @exception	std::invalid_argument	If the default RESQML version is unrecognized.
		 * @exception	std::invalid_argument	If @p rep, @p strLookup or @p localPropKind is null.
		 *
		 * @param [in]	rep			  	The representation on which this property is attached to. It
		 * 								cannot be null.
		 * @param 	  	guid		  	The guid to set to the property. If empty then a new guid will be
		 * 								generated.
		 * @param 	  	title		  	The title to set to the property. If empty then \"unknown\" title
		 * 								will be set.
		 * @param 	  	dimension	  	The dimension of each value of this property. Dimension is 1 for
		 * 								a scalar property.
		 * @param 	  	attachmentKind	The topological element on which the property values are attached
		 * 								to.
		 * @param [in]	dblLookup		The double lookup which defines a discrete function associated with the property values.
		 * @param [in]	localPropType 	The property kind of these property values which must be defined
		 * 								in the EPC document as a local property kind. It cannot be null.
		 *
		 * @returns	A pointer to the new categorical property.
		 */
		DLL_IMPORT_OR_EXPORT RESQML2_NS::CategoricalProperty* createCategoricalProperty(RESQML2_NS::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			unsigned int dimension, gsoap_eml2_3::resqml22__IndexableElement attachmentKind,
			RESQML2_NS::DoubleTableLookup* dblLookup, EML2_NS::PropertyKind * localPropType);

		/**
		 * Creates a points property (which is of a well known Energistics property kind) into this
		 * repository
		 *
		 * @exception	std::invalid_argument	If @p rep is null.
		 *
		 * @param [in]	rep					   	The representation on which this property is attached to.
		 * 										It cannot be null.
		 * @param 	  	guid				   	The guid to set to the property. If empty then a new guid
		 * 										will be generated.
		 * @param 	  	title				   	The title to set to the property. If empty then
		 * 										\"unknown\" title will be set.
		 * @param 	  	dimension			   	The dimension of each value of this property. Dimension
		 * 										is 1 for a scalar property.
		 * @param 	  	attachmentKind		   	The topological element on which the property values are
		 * 										attached to.
		 * @param 	  	energisticsPropertyKind	The property kind of these property values which must be
		 * 										defined in the standard Energistics property type
		 * 										dictionary. Defautl is length
		 *
		 * @returns	A pointer to the new points property.
		 */
		DLL_IMPORT_OR_EXPORT RESQML2_0_1_NS::PointsProperty* createPointsProperty(RESQML2_NS::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			unsigned int dimension, gsoap_eml2_3::resqml22__IndexableElement attachmentKind, RESQML2_NS::AbstractLocal3dCrs* localCrs,
			gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind energisticsPropertyKind = gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind__length);

		/**
		 * Creates a points property (which is of a local property kind) into this repository
		 *
		 * @exception	std::invalid_argument	If the default RESQML version is unrecognized.
		 * @exception	std::invalid_argument	If @p or @p localPropKind is null.
		 *
		 * @param [in]	rep			  	The representation on which this property is attached to. It
		 * 								cannot be null.
		 * @param 	  	guid		  	The guid to set to the property. If empty then a new guid will be
		 * 								generated.
		 * @param 	  	title		  	The title to set to the property. If empty then \"unknown\" title
		 * 								will be set.
		 * @param 	  	dimension	  	The dimension of each value of this property. Dimension is 1 for
		 * 								a scalar property.
		 * @param 	  	attachmentKind	The topological element on which the property values are attached
		 * 								to.
		 * @param [in]	localPropType 	The property kind of these property values which must be defined
		 * 								in the EPC document as a local property kind. It cannot be null.
		 *
		 * @returns	A pointer to the new points property.
		 */
		DLL_IMPORT_OR_EXPORT RESQML2_NS::PointsProperty* createPointsProperty(RESQML2_NS::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			unsigned int dimension, gsoap_eml2_3::resqml22__IndexableElement attachmentKind, RESQML2_NS::AbstractLocal3dCrs* localCrs,
			EML2_NS::PropertyKind * localPropType);

		//************* ACTIVITIES ***********

		/**
		 * @brief	Creates an activity template into this repository
		 *
		 * @exception	std::invalid_argument	If the default EML version is unrecognized.
		 *
		 * @param 	guid 	The guid to set to the activity template. If empty then a new guid will be
		 * 					generated.
		 * @param 	title	The title to set to the activity template. If empty then \"unknown\" title
		 * 					will be set.
		 *
		 * @returns	A pointer to the new activity template.
		 */
		DLL_IMPORT_OR_EXPORT EML2_NS::ActivityTemplate* createActivityTemplate(const std::string & guid, const std::string & title);

		/**
		 * @brief	Creates an activity into this repository
		 *
		 * @exception	std::invalid_argument	If the default EML version is unrecognized.
		 * @exception	std::invalid_argument	If <tt>activityTemplate == nullptr</tt>.
		 *
		 * @param [in]	activityTemplate	The activity template on which this activity is based on.
		 * @param 	  	guid				The guid to set to the activity. If empty then a new guid
		 * 									will be generated.
		 * @param 	  	title				The title to set to the activity. If empty then \"unknown\"
		 * 									title will be set.
		 *
		 * @returns	A pointer to the new activity.
		 */
		DLL_IMPORT_OR_EXPORT EML2_NS::Activity* createActivity(EML2_NS::ActivityTemplate* activityTemplate, const std::string & guid, const std::string & title);

		//*************** WITSML *************
/*
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
*/
		/**
		 * Creates a well into this repository
		 *
		 * @param 	guid 	The guid to set to the well. If empty then a new guid will be generated.
		 * @param 	title	The title to set to the well. If empty then \"unknown\" title will be set.
		 *
		 * @returns	A pointer to the new well.
		 */
		DLL_IMPORT_OR_EXPORT WITSML2_0_NS::Well* createWell(const std::string & guid,
			const std::string & title);

		/**
		 * Creates a well into this repository
		 *
		 * @param 	guid		 	The guid to set to the well. If empty then a new guid will be
		 * 							generated.
		 * @param 	title		 	The title to set to the well. If empty then \"unknown\" title will be
		 * 							set.
		 * @param 	operator_	 	The operator company name.
		 * @param 	statusWell   	POSC well status.
		 * @param 	directionWell	POSC well direction. The direction of the flow of the fluids in a
		 * 							well facility (generally, injected or produced, or some combination).
		 *
		 * @returns	A pointer to the new well.
		 */
		DLL_IMPORT_OR_EXPORT WITSML2_0_NS::Well* createWell(const std::string & guid,
			const std::string & title,
			const std::string & operator_,
			gsoap_eml2_1::eml21__WellStatus statusWell,
			gsoap_eml2_1::witsml20__WellDirection directionWell
		);

		/**
		 * @brief	Creates a wellbore into this repository.
		 *
		 * @exception	std::invalid_argument	If <tt>witsmlWell == nullptr</tt>.
		 *
		 * @param [in]	witsmlWell	The well associated to this wellbore. It cannot be null.
		 * @param 	  	guid	  	The guid to set to the wellbore. If empty then a new guid will be
		 * 							generated.
		 * @param 	  	title	  	The title to set to the wellbore. If empty then \"unknown\" title
		 * 							will be set.
		 *
		 * @returns	A pointer to the new wellbore.
		 */
		DLL_IMPORT_OR_EXPORT WITSML2_0_NS::Wellbore* createWellbore(WITSML2_0_NS::Well* witsmlWell,
			const std::string & guid,
			const std::string & title);

		/**
		 * @brief	Creates a wellbore into this repository.
		 *
		 * @exception	std::invalid_argument	If <tt>witsmlWell == nullptr</tt>.
		 *
		 * @param [in]	witsmlWell	  	The well associated to this wellbore. It cannot be null.
		 * @param 	  	guid		  	The guid to set to the wellbore. If empty then a new guid will be
		 * 								generated.
		 * @param 	  	title		  	The title to set to the wellbore. If empty then \"unknown\" title
		 * 								will be set.
		 * @param 	  	statusWellbore	POSC wellbore status.
		 * @param 	  	isActive	  	True if is active, false if not.
		 * @param 	  	achievedTD	  	True indicates that the wellbore has achieved total depth. That
		 * 								is, drilling has completed. False indicates otherwise.  
		 *
		 * @returns	A pointer to the new wellbore.
		 */
		DLL_IMPORT_OR_EXPORT WITSML2_0_NS::Wellbore* createWellbore(WITSML2_0_NS::Well* witsmlWell,
			const std::string & guid,
			const std::string & title,
			gsoap_eml2_1::eml21__WellStatus statusWellbore,
			bool isActive,
			bool achievedTD
		);

		/**
		 * @brief	Creates a well completion into this repository
		 *
		 * @exception	std::invalid_argument	If <tt>witsmlWell == nullptr</tt>.
		 *
		 * @param [in]	witsmlWell	The well associated to this well completion. It cannot be null.
		 * @param 	  	guid	  	The guid to set to the well completion. If empty then a new guid will
		 * 							be generated.
		 * @param 	  	title	  	The title to set to the well completion. If empty then \"unknown\"
		 * 							title will be set.
		 *
		 * @returns	A pointer to the new well completion.
		 */
		DLL_IMPORT_OR_EXPORT WITSML2_0_NS::WellCompletion* createWellCompletion(WITSML2_0_NS::Well* witsmlWell,
			const std::string & guid,
			const std::string & title);

		/**
		 * Creates a wellbore completion into this repository
		 *
		 * @param [in]	witsmlWellbore	  	The wellbore associated to this wellbore completion. It
		 * 									cannot be null.
		 * @param [in]	wellCompletion	  	The well completion associated to this wellbore completion.
		 * 									It cannot be null.
		 * @param 	  	guid			  	The guid to set to the wellbore completion. If empty then a new guid will be
		 * 									generated.
		 * @param 	  	title			  	The title to set to the wellbore completion. If empty then \"unknown\" title
		 * 									will be set.
		 * @param 	  	wellCompletionName	Human-recognizable context for the well completion that
		 * 									contains the completion.
		 *
		 * @returns	A pointer to the new wellbore completion.
		 */
		DLL_IMPORT_OR_EXPORT WITSML2_0_NS::WellboreCompletion* createWellboreCompletion(WITSML2_0_NS::Wellbore* witsmlWellbore,
			WITSML2_0_NS::WellCompletion* wellCompletion,
			const std::string & guid,
			const std::string & title,
			const std::string & wellCompletionName);

		/**
		 * @brief	Creates a wellbore geometry into this repository. It is used to capture information
		 * 			about the configuration of the permanently installed components in a wellbore
		 *
		 * @exception	std::invalid_argument	If <tt>witsmlWellbore == nullptr</tt>.
		 *
		 * @param [in]	witsmlWellbore	The wellbore associated to this wellbore geometry. It cannot be
		 * 								null.
		 * @param 	  	guid		  	The guid to set to the geometry. If empty then a new guid will be
		 * 								generated.
		 * @param 	  	title		  	The title to set to the geometry. If empty then \"unknown\" title
		 * 								will be set.
		 * @param 	  	channelStatus 	Describes the growing status of the wellbore geometry, whether
		 * 								active, inactive or closed.
		 *
		 * @returns	A pointer to the new wellbore geometry.
		 */
		DLL_IMPORT_OR_EXPORT WITSML2_0_NS::WellboreGeometry* createWellboreGeometry(WITSML2_0_NS::Wellbore* witsmlWellbore,
			const std::string & guid,
			const std::string & title,
			gsoap_eml2_1::witsml20__ChannelStatus channelStatus);

		/**
		 * @brief	Creates a wellbore trajectory into this repository
		 *
		 * @exception	std::invalid_argument	If <tt>witsmlWellbore == nullptr</tt>.
		 *
		 * @param [in]	witsmlWellbore	The wellbore associated to this wellbore trajectory. It cannot be
		 * 								null.
		 * @param 	  	guid		  	The guid to set to the trajectory. If empty then a new guid will
		 * 								be generated.
		 * @param 	  	title		  	The title to set to the trajectory. If empty then \"unknown\"
		 * 								title will be set.
		 * @param 	  	channelStatus 	Describes the growing status of the trajectory, whether active,
		 * 								inactive or closed.
		 *
		 * @returns	A pointer to the new trajectory.
		 */
		DLL_IMPORT_OR_EXPORT WITSML2_0_NS::Trajectory* createTrajectory(WITSML2_0_NS::Wellbore* witsmlWellbore,
			const std::string & guid,
			const std::string & title,
			gsoap_eml2_1::witsml20__ChannelStatus channelStatus);

		/**
		 * @brief	Creates a wellbore log into this repository
		 *
		 * @exception	std::invalid_argument	If <tt>witsmlWellbore == nullptr</tt>.
		 *
		 * @param [in]	witsmlWellbore	The wellbore associated to this log. It cannot be null.
		 * @param 	  	guid		  	The guid to set to the log. If empty then a new guid will be
		 * 								generated.
		 * @param 	  	title		  	The title to set to the log. If empty then \"unknown\" title will
		 * 								be set.
		 *
		 * @returns	A pointer to the new log.
		 */
		DLL_IMPORT_OR_EXPORT WITSML2_0_NS::Log* createLog(WITSML2_0_NS::Wellbore* witsmlWellbore,
			const std::string & guid,
			const std::string & title);

		/**
		 * Creates a channel set into this repository
		 *
		 * @param 	guid 	The guid to set to the channel set. If empty then a new guid will be generated.
		 * @param 	title	The title to set to the channel set. If empty then \"unknown\" title will be set.
		 *
		 * @returns	A pointer to the new channel set.
		 */
		DLL_IMPORT_OR_EXPORT WITSML2_0_NS::ChannelSet* createChannelSet(
			const std::string & guid,
			const std::string & title);

		/**
		 * @brief	Creates a channel into this repository
		 *
		 * @exception	std::invalid_argument	If <tt>propertyKind == nullptr</tt>.
		 *
		 * @param [in]	propertyKind	  	The property kind associated to this channel. It cannot be
		 * 									null.
		 * @param 	  	guid			  	The guid to set to the channel. If empty then a new guid will
		 * 									be generated.
		 * @param 	  	title			  	The title to set to the channel. If empty then \"unknown\"
		 * 									title will be set.
		 * @param 	  	mnemonic		  	The mnemonic name to set to this channel.
		 * @param 	  	uom				  	The underlying unit of measure of the value.
		 * @param 	  	dataType		  	The underlying ETP data type of the value.
		 * @param 	  	growingStatus	  	The status of a channel with respect to creating new
		 * 									measurements.
		 * @param 	  	timeDepth		  	Use to indicate if this is a time or depth log.
		 * @param 	  	loggingCompanyName	Name of the logging company.
		 *
		 * @returns	A pointer to the new channel.
		 */
		DLL_IMPORT_OR_EXPORT WITSML2_0_NS::Channel* createChannel(EML2_NS::PropertyKind * propertyKind,
			const std::string & guid, const std::string & title,
			const std::string & mnemonic, gsoap_eml2_1::eml21__UnitOfMeasure uom, gsoap_eml2_1::witsml20__EtpDataType dataType, gsoap_eml2_1::witsml20__ChannelStatus growingStatus,
			const std::string & timeDepth, const std::string & loggingCompanyName);

		/**
		 * @brief	Creates a WITSML2.0 Wellbore Marker into this repository
		 *
		 * @param 	  	guid		  	The guid to set to the marker. If empty then a new guid will be
		 * 								generated.
		 * @param 	  	title		  	The title to set to the marker. If empty then \"unknown\" title will
		 * 								be set.
		 * @param 	  	md		  		The Measured Depth to set to this marker.
		 * @param 	  	mdUom			The underlying unit of measure of the MD value.
		 * @param 	  	mdDatum		  	A free string to unformally indicate the datum of the MD (i.e. where MD==0).
		 *
		 * @returns	A pointer to the new Wellbore Marker.
		 */
		DLL_IMPORT_OR_EXPORT WITSML2_0_NS::WellboreMarker* createWellboreMarker(
			const std::string & guid, const std::string & title,
			double md, gsoap_eml2_1::eml21__LengthUom mdUom, const std::string & mdDatum);

		/**
		 * @brief	Creates a WITSML2.0 Wellbore Marker into this repository
		 *
		 * @exception	std::invalid_argument	If <tt>witsmlWellbore == nullptr</tt>.
		 *
		 * @param [in]	witsmlWellbore	The wellbore associated to this marker. It cannot be null.
		 * @param 	  	guid		  	The guid to set to the marker. If empty then a new guid will be
		 * 								generated.
		 * @param 	  	title		  	The title to set to the marker. If empty then \"unknown\" title will
		 * 								be set.
		 * @param 	  	md		  		The Measured Depth to set to this marker.
		 * @param 	  	mdUom			The underlying unit of measure of the MD value.
		 * @param 	  	mdDatum		  	A free string to unformally indicate the datum of the MD (i.e. where MD==0).
		 *
		 * @returns	A pointer to the new Wellbore Marker.
		 */
		DLL_IMPORT_OR_EXPORT WITSML2_0_NS::WellboreMarker* createWellboreMarker(WITSML2_0_NS::Wellbore* witsmlWellbore,
			const std::string & guid, const std::string & title,
			double md, gsoap_eml2_1::eml21__LengthUom mdUom, const std::string & mdDatum);

		//*************** PRODML *************

		/**
		 * Creates a fluid system into this repository
		 *
		 * @param 	guid			  	The guid to set to the fluid system. If empty then a new guid
		 * 								will be generated.
		 * @param 	title			  	The title to set to the fluid system. If empty then \"unknown\"
		 * 								title will be set.
		 * @param 	temperatureValue  	The temperature value.
		 * @param 	temperatureUom	  	The temperature unit of measure.
		 * @param 	pressureValue	  	The pressure value.
		 * @param 	pressureUom		  	The pressure unit of measure.
		 * @param 	reservoirFluidKind	The kind of the reservoir fluid.
		 * @param 	gasOilRatio		  	The gas oil ratio.
		 * @param 	gasOilRatioUom	  	The gas oil ratio unit of measure.
		 *
		 * @returns	A pointer to the new fluid system.
		 */
		DLL_IMPORT_OR_EXPORT PRODML2_1_NS::FluidSystem* createFluidSystem(const std::string & guid,
			const std::string & title,
			double temperatureValue, gsoap_eml2_2::eml22__ThermodynamicTemperatureUom temperatureUom,
			double pressureValue, gsoap_eml2_2::eml22__PressureUom pressureUom,
			gsoap_eml2_2::prodml21__ReservoirFluidKind reservoirFluidKind,
			double gasOilRatio, gsoap_eml2_2::eml22__VolumePerVolumeUom gasOilRatioUom);

		/**
		 * Creates a fluid characterization into this repository
		 *
		 * @param 	guid 	The guid to set to the fluid characterization. If empty then a new guid will
		 * 					be generated.
		 * @param 	title	The title to set to the fluid characterization. If empty then \"unknown\"
		 * 					title will be set.
		 *
		 * @returns	A pointer to the new fluid characterization.
		 */
		DLL_IMPORT_OR_EXPORT PRODML2_1_NS::FluidCharacterization* createFluidCharacterization(const std::string & guid, const std::string & title);

		/**
		 * Creates a time series data into this repository
		 *
		 * @param 	guid 	The guid to set to the time series data. If empty then a new guid will
		 * 					be generated.
		 * @param 	title	The title to set to the time series data. If empty then \"unknown\"
		 * 					title will be set.
		 *
		 * @returns	A pointer to the new time series data.
		 */
		DLL_IMPORT_OR_EXPORT PRODML2_1_NS::TimeSeriesData* createTimeSeriesData(const std::string & guid, const std::string & title);

		//************** EML2.3 ****************

		/**
		 * Creates a graphical information set into this repository
		 *
		 * @param 	guid 	The guid to set to the graphical information set. If empty then a new guid will
		 * 					be generated.
		 * @param 	title	The title to set to the graphical information set. If empty then \"unknown\"
		 * 					title will be set.
		 *
		 * @returns	A pointer to the new graphical information set.
		 */
		DLL_IMPORT_OR_EXPORT EML2_NS::GraphicalInformationSet* createGraphicalInformationSet(const std::string & guid, const std::string & title);

		/**
		 * Creates a discrete color map into this repository
		 *
		 * @param 	guid 	The guid to set to the discrete color map. If empty then a new guid will be
		 * 					generated.
		 * @param 	title	The title to set to the discrete color map. If empty then \"unknown\" title
		 * 					will be set.
		 *
		 * @returns	A pointer to the new discrete color map.
		 */
		DLL_IMPORT_OR_EXPORT RESQML2_NS::DiscreteColorMap* createDiscreteColorMap(const std::string& guid, const std::string& title);

		/**
		 * Creates a continuous color map into this repository
		 *
		 * @param 	guid			   	The guid to set to the continuous color map. If empty then a new
		 * 								guid will be generated.
		 * @param 	title			   	The title to set to the continuous color map. If empty then
		 * 								\"unknown\" title will be set.
		 * @param 	interpolationDomain	The interpolation domain (the color space).
		 * @param 	interpolationMethod	The interpolation method.
		 *
		 * @returns	A pointer to the new continuous color map.
		 */
		DLL_IMPORT_OR_EXPORT RESQML2_NS::ContinuousColorMap* createContinuousColorMap(const std::string& guid, const std::string& title,
			gsoap_eml2_3::resqml22__InterpolationDomain interpolationDomain, gsoap_eml2_3::resqml22__InterpolationMethod interpolationMethod);

		//***** STANDARD PROP KIND ***********

		/**
		 * Gets the property kind mapper if it was given at repository construction time
		 *
		 * @returns	The property kind mapper, or @c nullptr if no property kind mapper was given at
		 * 			repository construction time.
		 */
		DLL_IMPORT_OR_EXPORT RESQML2_0_1_NS::PropertyKindMapper* getPropertyKindMapper() const { return propertyKindMapper.get(); }

		//*************** WARNINGS *************
		
		/** Clears the repository the warnings */
		DLL_IMPORT_OR_EXPORT void clearWarnings() { warnings.clear();  }

		/**
		 * Adds a warning to this repository
		 *
		 * @param 	warning	The warning.
		 */
		DLL_IMPORT_OR_EXPORT void addWarning(const std::string & warning);

		/**
		 * Gets the repository warnings
		 *
		 * @returns	A vector of all repository warnings.
		 */
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

		std::unique_ptr<RESQML2_0_1_NS::PropertyKindMapper> propertyKindMapper;

		EML2_NS::AbstractHdfProxy* defaultHdfProxy;
		RESQML2_NS::AbstractLocal3dCrs* defaultCrs;

		std::vector<COMMON_NS::DataFeeder*> dataFeeders;

		std::unique_ptr<COMMON_NS::HdfProxyFactory> hdfProxyFactory;

		EnergisticsStandard defaultEmlVersion;
		EnergisticsStandard defaultProdmlVersion;
		EnergisticsStandard defaultResqmlVersion;
		EnergisticsStandard defaultWitsmlVersion;

		std::vector< std::tuple<std::chrono::time_point<std::chrono::system_clock>, DataObjectReference, CUD> > journal;

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

		COMMON_NS::AbstractObject* getResqml2_2WrapperFromGsoapContext(const std::string& resqmlContentType);
		COMMON_NS::AbstractObject* getEml2_1WrapperFromGsoapContext(const std::string & datatype);
		COMMON_NS::AbstractObject* getEml2_3WrapperFromGsoapContext(const std::string & datatype);

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
