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
#include "DataObjectRepository.h"

#include <algorithm>
#include <functional>

#include "../common/HdfProxyFactory.h"

#include "GraphicalInformationSet.h"

#include "../resqml2_0_1/PropertyKindMapper.h"

#include "../resqml2_0_1/LocalDepth3dCrs.h"
#include "../resqml2_0_1/LocalTime3dCrs.h"
#include "../resqml2_0_1/Horizon.h"
#include "../resqml2_0_1/FluidBoundaryFeature.h"
#include "../resqml2_0_1/TectonicBoundaryFeature.h"
#include "../resqml2_0_1/FrontierFeature.h"
#include "../resqml2_0_1/GeobodyFeature.h"
#include "../resqml2_0_1/GenericFeatureInterpretation.h"
#include "../resqml2_0_1/FaultInterpretation.h"
#include "../resqml2_0_1/HorizonInterpretation.h"
#include "../resqml2_0_1/GeobodyBoundaryInterpretation.h"
#include "../resqml2_0_1/GeobodyInterpretation.h"
#include "../resqml2_0_1/PolylineSetRepresentation.h"
#include "../resqml2_0_1/PointSetRepresentation.h"
#include "../resqml2_0_1/PlaneSetRepresentation.h"
#include "../resqml2_0_1/SeismicLatticeFeature.h"
#include "../resqml2_0_1/Grid2dRepresentation.h"
#include "../resqml2_0_1/HdfProxy.h"
#include "../resqml2_0_1/TriangulatedSetRepresentation.h"
#include "../resqml2_0_1/WellboreFeature.h"
#include "../resqml2_0_1/WellboreInterpretation.h"
#include "../resqml2_0_1/WellboreMarkerFrameRepresentation.h"
#include "../resqml2_0_1/WellboreTrajectoryRepresentation.h"
#include "../resqml2_0_1/DeviationSurveyRepresentation.h"
#include "../resqml2_0_1/MdDatum.h"
#include "../resqml2_0_1/PolylineRepresentation.h"
#include "../resqml2_0_1/SubRepresentation.h"
#include "../resqml2_0_1/GridConnectionSetRepresentation.h"
#include "../resqml2_0_1/TimeSeries.h"
#include "../resqml2_0_1/PropertyKind.h"
#include "../resqml2_0_1/PropertySet.h"
#include "../resqml2_0_1/ContinuousProperty.h"
#include "../resqml2_0_1/CategoricalProperty.h"
#include "../resqml2_0_1/DiscreteProperty.h"
#include "../resqml2_0_1/CommentProperty.h"
#include "../resqml2_0_1/StringTableLookup.h"
#include "../resqml2_0_1/SeismicLineFeature.h"
#include "../resqml2_0_1/SeismicLineSetFeature.h"
#include "../resqml2_0_1/OrganizationFeature.h"

#include "../resqml2_0_1/BlockedWellboreRepresentation.h"

#include "../resqml2_0_1/EarthModelInterpretation.h"
#include "../resqml2_0_1/RepresentationSetRepresentation.h"
#include "../resqml2_0_1/StructuralOrganizationInterpretation.h"
#include "../resqml2_0_1/NonSealedSurfaceFrameworkRepresentation.h"
#include "../resqml2_0_1/SealedSurfaceFrameworkRepresentation.h"
#include "../resqml2_0_1/SealedVolumeFrameworkRepresentation.h"

#include "../resqml2_0_1/RockFluidUnitFeature.h"
#include "../resqml2_0_1/RockFluidUnitInterpretation.h"
#include "../resqml2_0_1/RockFluidOrganizationInterpretation.h"

#include "../resqml2_0_1/StratigraphicUnitFeature.h"
#include "../resqml2_0_1/StratigraphicUnitInterpretation.h"
#include "../resqml2_0_1/StratigraphicColumn.h"
#include "../resqml2_0_1/StratigraphicColumnRankInterpretation.h"
#include "../resqml2_0_1/StratigraphicOccurrenceInterpretation.h"

#include "../resqml2_0_1/IjkGridExplicitRepresentation.h"
#include "../resqml2_0_1/IjkGridLatticeRepresentation.h"
#include "../resqml2_0_1/IjkGridNoGeometryRepresentation.h"
#include "../resqml2_0_1/IjkGridParametricRepresentation.h"
#include "../resqml2_0_1/UnstructuredGridRepresentation.h"

#include "../resqml2_0_1/Activity.h"
#include "../resqml2_0_1/ActivityTemplate.h"

#include "../resqml2_2/CategoricalProperty.h"
#include "../resqml2_2/CommentProperty.h"
#include "../resqml2_2/ContinuousProperty.h"
#include "../resqml2_2/ContinuousColorMap.h"
#include "../resqml2_2/DiscreteProperty.h"
#include "../resqml2_2/DiscreteColorMap.h"
#include "../resqml2_2/IjkGridExplicitRepresentation.h"
#include "../resqml2_2/IjkGridLatticeRepresentation.h"
#include "../resqml2_2/IjkGridNoGeometryRepresentation.h"
#include "../resqml2_2/IjkGridParametricRepresentation.h"
#include "../resqml2_2/SeismicWellboreFrameRepresentation.h"
#include "../resqml2_2/UnstructuredGridRepresentation.h"
#include "../resqml2_2/WellboreFrameRepresentation.h"

#include "../witsml2_0/Well.h"
#include "../witsml2_0/Wellbore.h"
#include "../witsml2_0/Trajectory.h"
#include "../witsml2_0/WellCompletion.h"
#include "../witsml2_0/WellboreCompletion.h"
#include "../witsml2_0/WellboreGeometry.h"
#include "../witsml2_0/Log.h"
#include "../witsml2_0/ChannelSet.h"
#include "../witsml2_0/Channel.h"
#include "../witsml2_0/PropertyKind.h"

#include "../prodml2_1/FluidSystem.h"
#include "../prodml2_1/FluidCharacterization.h"

#if !defined(FESAPI_USE_BOOST_UUID)
#include "../tools/GuidTools.h"
#else
#include <boost/uuid/random_generator.hpp>
#include <boost/uuid/uuid_io.hpp>
#endif

using namespace std;
using namespace COMMON_NS;
using namespace RESQML2_0_1_NS;
using namespace WITSML2_0_NS;
using namespace PRODML2_1_NS;
using namespace RESQML2_2_NS;

namespace {
	class SameVersion {
	private:
		std::string version;
	public:
		explicit SameVersion(const std::string & version_) : version(version_) {}

		bool operator()(COMMON_NS::AbstractObject const * dataObj) const
		{
			return dataObj->getVersion() == version;
		}
	};
}

// Create a fesapi partial wrapper based on a content type
#define CREATE_FESAPI_PARTIAL_WRAPPER(className)\
	(dataType.compare(className::XML_TAG) == 0)\
	{\
		return dor.getVersion().empty() ? createPartial<className>(dor.getUuid(), dor.getTitle()) : createPartial<className>(dor.getUuid(), dor.getTitle(), dor.getVersion());\
	}

/////////////////////
/////// RESQML //////
/////////////////////
#define GET_RESQML_2_0_1_GSOAP_PROXY_FROM_GSOAP_CONTEXT(className)\
	gsoap_resqml2_0_1::_resqml20__##className* read = gsoap_resqml2_0_1::soap_new_resqml20__obj_USCORE##className(gsoapContext);\
	soap_read_resqml20__obj_USCORE##className(gsoapContext, read);


#define GET_RESQML_2_0_1_FESAPI_WRAPPER_FROM_GSOAP_CONTEXT(className)\
	GET_RESQML_2_0_1_GSOAP_PROXY_FROM_GSOAP_CONTEXT(className)\
	wrapper = new RESQML2_0_1_NS::className(read);

#define CHECK_AND_GET_RESQML_2_0_1_FESAPI_WRAPPER_FROM_GSOAP_CONTEXT(className)\
	(resqmlContentType.compare(RESQML2_0_1_NS::className::XML_TAG) == 0)\
	{\
		GET_RESQML_2_0_1_FESAPI_WRAPPER_FROM_GSOAP_CONTEXT(className);\
	}

///////////////////////////
/////// RESQML 2.2 //////
///////////////////////////
#define GET_RESQML_2_2_GSOAP_PROXY_FROM_GSOAP_CONTEXT(className)\
	gsoap_eml2_2::_resqml22__##className* read = gsoap_eml2_2::soap_new_resqml22__##className(gsoapContext);\
	soap_read_resqml22__##className(gsoapContext, read);

#define GET_RESQML_2_2_FESAPI_WRAPPER_FROM_GSOAP_CONTEXT(className)\
	GET_RESQML_2_2_GSOAP_PROXY_FROM_GSOAP_CONTEXT(className)\
	wrapper = new RESQML2_2_NS::className(read);

#define CHECK_AND_GET_RESQML_2_2_FESAPI_WRAPPER_FROM_GSOAP_CONTEXT(className)\
	(resqmlContentType.compare(RESQML2_2_NS::className::XML_TAG) == 0)\
	{\
		GET_RESQML_2_2_FESAPI_WRAPPER_FROM_GSOAP_CONTEXT(className);\
	}

/////////////////////
///// WITSML 2.0 ////
/////////////////////
#define GET_WITSML_2_GSOAP_PROXY_FROM_GSOAP_CONTEXT(className, gsoapNameSpace)\
	gsoapNameSpace::_witsml20__##className* read = gsoapNameSpace::soap_new_witsml20__##className(gsoapContext);\
	gsoapNameSpace::soap_read_witsml20__##className(gsoapContext, read);

#define GET_WITSML_2_FESAPI_WRAPPER_FROM_GSOAP_CONTEXT(classNamespace, className, gsoapNameSpace)\
	GET_WITSML_2_GSOAP_PROXY_FROM_GSOAP_CONTEXT(className, gsoapNameSpace)\
	wrapper = new classNamespace::className(read);

#define CHECK_AND_GET_WITSML_2_FESAPI_WRAPPER_FROM_GSOAP_CONTEXT(classNamespace, className, gsoapNameSpace)\
	(datatype.compare(classNamespace::className::XML_TAG) == 0)\
	{\
		GET_WITSML_2_FESAPI_WRAPPER_FROM_GSOAP_CONTEXT(classNamespace, className, gsoapNameSpace);\
	}

/////////////////////
///// PRODML 2.1 ////
/////////////////////
#define GET_PRODML_2_1_GSOAP_PROXY_FROM_GSOAP_CONTEXT(className, gsoapNameSpace)\
	gsoapNameSpace::_prodml21__##className* read = gsoapNameSpace::soap_new_prodml21__##className(gsoapContext);\
	gsoapNameSpace::soap_read_prodml21__##className(gsoapContext, read);

#define GET_PRODML_2_1_FESAPI_WRAPPER_FROM_GSOAP_CONTEXT(classNamespace, className, gsoapNameSpace)\
	GET_PRODML_2_1_GSOAP_PROXY_FROM_GSOAP_CONTEXT(className, gsoapNameSpace)\
	wrapper = new classNamespace::className(read);

#define CHECK_AND_GET_PRODML_2_1_FESAPI_WRAPPER_FROM_GSOAP_CONTEXT(classNamespace, className, gsoapNameSpace)\
	(datatype.compare(classNamespace::className::XML_TAG) == 0)\
	{\
		GET_PRODML_2_1_FESAPI_WRAPPER_FROM_GSOAP_CONTEXT(classNamespace, className, gsoapNameSpace);\
	}

/////////////////////
////// EML 2.2 //////
/////////////////////
#define GET_EML_2_2_GSOAP_PROXY_FROM_GSOAP_CONTEXT(className, gsoapNameSpace)\
	gsoapNameSpace::_eml22__##className* read = gsoapNameSpace::soap_new_eml22__##className(gsoapContext);\
	gsoapNameSpace::soap_read_eml22__##className(gsoapContext, read);
#define GET_EML_2_2_FESAPI_WRAPPER_FROM_GSOAP_CONTEXT(classNamespace, className, gsoapNameSpace)\
	GET_EML_2_2_GSOAP_PROXY_FROM_GSOAP_CONTEXT(className, gsoapNameSpace)\
	wrapper = new classNamespace::className(read);
#define CHECK_AND_GET_EML_2_2_FESAPI_WRAPPER_FROM_GSOAP_CONTEXT(classNamespace, className, gsoapNameSpace)\
	(datatype.compare(classNamespace::className::XML_TAG) == 0)\
	{\
		GET_EML_2_2_FESAPI_WRAPPER_FROM_GSOAP_CONTEXT(classNamespace, className, gsoapNameSpace);\
	}

DataObjectRepository::DataObjectRepository() :
	dataObjects(),
	forwardRels(),
	backwardRels(),
	gsoapContext(soap_new2(SOAP_XML_STRICT | SOAP_C_UTFSTRING | SOAP_XML_IGNORENS, SOAP_XML_TREE | SOAP_XML_INDENT | SOAP_XML_CANONICAL | SOAP_C_UTFSTRING)),
	warnings(),
	propertyKindMapper(nullptr), defaultHdfProxy(nullptr), defaultCrs(nullptr),
	hdfProxyFactory(new COMMON_NS::HdfProxyFactory()),
	defaultProdmlVersion(COMMON_NS::DataObjectRepository::EnergisticsStandard::PRODML2_1),
	defaultResqmlVersion(COMMON_NS::DataObjectRepository::EnergisticsStandard::RESQML2_2),
	defaultWitsmlVersion(COMMON_NS::DataObjectRepository::EnergisticsStandard::WITSML2_0) {}

DataObjectRepository::DataObjectRepository(const std::string & propertyKindMappingFilesDirectory) :
	dataObjects(),
	forwardRels(),
	backwardRels(),
	gsoapContext(soap_new2(SOAP_XML_STRICT | SOAP_C_UTFSTRING | SOAP_XML_IGNORENS, SOAP_XML_TREE | SOAP_XML_INDENT | SOAP_XML_CANONICAL | SOAP_C_UTFSTRING)),
	warnings(),
	propertyKindMapper(new PropertyKindMapper(this)), defaultHdfProxy(nullptr), defaultCrs(nullptr),
	hdfProxyFactory(new COMMON_NS::HdfProxyFactory()),
	defaultProdmlVersion(COMMON_NS::DataObjectRepository::EnergisticsStandard::PRODML2_1),
	defaultResqmlVersion(COMMON_NS::DataObjectRepository::EnergisticsStandard::RESQML2_2),
	defaultWitsmlVersion(COMMON_NS::DataObjectRepository::EnergisticsStandard::WITSML2_0)
{
	const string error = propertyKindMapper->loadMappingFilesFromDirectory(propertyKindMappingFilesDirectory);
	if (!error.empty()) {
		delete propertyKindMapper;
		propertyKindMapper = nullptr;
		throw invalid_argument("Could not import property kind mappers : " + error);
	}
}

DataObjectRepository::~DataObjectRepository()
{
	clear();

	soap_destroy(gsoapContext); // remove deserialized C++ objects
	soap_end(gsoapContext); // remove deserialized data
	soap_done(gsoapContext); // finalize last use of the context
	soap_free(gsoapContext); // Free the context
}

void DataObjectRepository::clear()
{
	if (propertyKindMapper != nullptr) {
		delete propertyKindMapper;
		propertyKindMapper = nullptr;
	}

	for (std::unordered_map< std::string, std::vector< COMMON_NS::AbstractObject* > >::const_iterator it = dataObjects.begin(); it != dataObjects.end(); ++it) {
		for (size_t i = 0; i < it->second.size(); ++i) {
			delete it->second[i];
		}
	}
	dataObjects.clear();
	forwardRels.clear();
	backwardRels.clear();

	warnings.clear();

	delete hdfProxyFactory;
}

void DataObjectRepository::addRelationship(COMMON_NS::AbstractObject * source, COMMON_NS::AbstractObject * target)
{
	if (source == nullptr || target == nullptr) {
		throw invalid_argument("Cannot set a relationship with a null pointer");
	}

	auto sourceIt = forwardRels.find(source);
	if (sourceIt == forwardRels.end()) {
		forwardRels[source].push_back(target);
	}
	else {
		if (std::find(sourceIt->second.begin(), sourceIt->second.end(), target) == sourceIt->second.end()) {
			sourceIt->second.push_back(target);
		}
		else {
			return;
		}
	}
	backwardRels[target].push_back(source);

	RESQML2_NS::AbstractLocal3dCrs const * crs = dynamic_cast<RESQML2_NS::AbstractLocal3dCrs const *>(target);
	if (crs != nullptr) {
		RESQML2_NS::AbstractRepresentation const * rep = dynamic_cast<RESQML2_NS::AbstractRepresentation const *>(source);
		if (rep != nullptr && rep->getInterpretation() != nullptr) {
			rep->getInterpretation()->initDomain(gsoap_resqml2_0_1::resqml20__Domain__mixed);
		}
	}
}

void DataObjectRepository::deleteRelationship(COMMON_NS::AbstractObject * source, COMMON_NS::AbstractObject * target)
{
	if (source == nullptr || target == nullptr) {
		throw invalid_argument("Cannot set a relationship with a null pointer");
	}

	auto sourceIt = forwardRels.find(source);
	if (sourceIt != forwardRels.end()) {
		auto targetIt = std::find(sourceIt->second.begin(), sourceIt->second.end(), target);
		if (targetIt != sourceIt->second.end()) {
			// Erase in Forward Rels
			sourceIt->second.erase(targetIt);

			// Erase in Backward rels
			auto& sources = backwardRels[target];
			sources.erase(std::find(sources.begin(), sources.end(), source));
		}
	}
}

const std::vector< COMMON_NS::AbstractObject * >& DataObjectRepository::getTargetObjects(COMMON_NS::AbstractObject const * dataObj) const
{
	return forwardRels.at(dataObj);
}

const std::vector< COMMON_NS::AbstractObject * >& DataObjectRepository::getSourceObjects(COMMON_NS::AbstractObject const * dataObj) const
{
	return backwardRels.at(dataObj);
}

namespace {
	void clearVectorOfMapEntry(std::pair< COMMON_NS::AbstractObject const * const, std::vector< COMMON_NS::AbstractObject * > > & entry) {
		entry.second.clear();
	}
}

void DataObjectRepository::updateAllRelationships()
{
	// Tansform the map values into a vector because we are going to potentially insert new elements in the map when looping.
	vector<COMMON_NS::AbstractObject*> nonPartialObjects;
	for (std::unordered_map< std::string, std::vector< COMMON_NS::AbstractObject* > >::const_iterator it = dataObjects.begin(); it != dataObjects.end(); ++it) {
		for (size_t i = 0; i < it->second.size(); ++i) {
			if (!it->second[i]->isPartial()) {
				nonPartialObjects.push_back(it->second[i]);
			}
		}
	}

	std::for_each(forwardRels.begin(), forwardRels.end(), clearVectorOfMapEntry);
	std::for_each(backwardRels.begin(), backwardRels.end(), clearVectorOfMapEntry);
	for (size_t nonPartialObjIndex = 0; nonPartialObjIndex < nonPartialObjects.size(); ++nonPartialObjIndex) {
		nonPartialObjects[nonPartialObjIndex]->loadTargetRelationships();
	}
}

void DataObjectRepository::addOrReplaceDataObject(COMMON_NS::AbstractObject* proxy)
{
	if (getDataObjectByUuid(proxy->getUuid()) == nullptr) {
		dataObjects[proxy->getUuid()].push_back(proxy);
		forwardRels[proxy] = std::vector<COMMON_NS::AbstractObject *>();
		backwardRels[proxy] = std::vector<COMMON_NS::AbstractObject *>();
	}
	else {
		std::vector< COMMON_NS::AbstractObject* >& versions = dataObjects[proxy->getUuid()];
		std::vector< COMMON_NS::AbstractObject* >::iterator same = std::find_if(versions.begin(), versions.end(), SameVersion(proxy->getVersion()));

		if (same == versions.end()) {
			dataObjects[proxy->getUuid()].push_back(proxy);
		}
		else {
			if (proxy->getContentType() != (*same)->getContentType()) {
				throw invalid_argument("Cannot replace " + proxy->getUuid() + " with a different content type : " + proxy->getContentType() + " vs " + (*same)->getContentType());
			}
			delete *same;
			*same = proxy;
		}
	}
	proxy->repository = this;
}

COMMON_NS::AbstractObject* DataObjectRepository::addOrReplaceGsoapProxy(const std::string & xml, const string & contentType)
{
	istringstream iss(xml);
	setGsoapStream(&iss);

	size_t lastEqualCharPos = contentType.find_last_of('_'); // The XML tag is after "obj_"
	if (lastEqualCharPos == string::npos) { lastEqualCharPos = contentType.find_last_of('='); }
	const string datatype = contentType.substr(lastEqualCharPos + 1);

	COMMON_NS::AbstractObject* wrapper = nullptr;
	if (contentType.find("application/x-eml+xml;version=2.0;type=obj_") != string::npos) {
		gsoap_resqml2_0_1::_eml20__EpcExternalPartReference* read = gsoap_resqml2_0_1::soap_new_eml20__obj_USCOREEpcExternalPartReference(gsoapContext);
		soap_read_eml20__obj_USCOREEpcExternalPartReference(gsoapContext, read);
		wrapper = hdfProxyFactory->make(read);
	}
	else if (contentType.find("application/x-resqml+xml;version=2.0;type=obj_") != string::npos) {
		wrapper = getResqml2_0_1WrapperFromGsoapContext(datatype);
	}
	else if (contentType.find("application/x-resqml+xml;version=2.0.1;type=obj_") != string::npos) {
		if (contentType != "application/x-resqml+xml;version=2.0.1;type=obj_Activity" &&
			contentType != "application/x-resqml+xml;version=2.0.1;type=obj_ActivityTemplate" &&
			contentType != "application/x-resqml+xml;version=2.0.1;type=obj_StreamlinesFeature" &&
			contentType != "application/x-resqml+xml;version=2.0.1;type=obj_StreamlinesRepresentation") {
			addWarning("Content type \"" + contentType + "\" does not belong to 2.0.1. Probably to 2.0? Please fix your ccontent type or ask exporter to fix it.");
		}
		wrapper = getResqml2_0_1WrapperFromGsoapContext(datatype);
	}
	else if (contentType.find("application/x-witsml+xml;version=2.0;type=") != string::npos) {
		wrapper = getWitsml2_0WrapperFromGsoapContext(datatype);
	}
	else if (contentType.find("application/x-prodml+xml;version=2.1;type=") != string::npos) {
		wrapper = getProdml2_1WrapperFromGsoapContext(datatype);
	}
	else if (contentType.find("application/x-resqml+xml;version=2.2;type=") != string::npos) {
		wrapper = getResqml2_2WrapperFromGsoapContext(datatype);
	}
	else if (contentType.find("application/x-eml+xml;version=2.2;type=") != string::npos) {
		wrapper = getEml2_2WrapperFromGsoapContext(datatype);
	}

	if (wrapper != nullptr) {
		if (gsoapContext->error != SOAP_OK) {
			ostringstream oss;
			soap_stream_fault(gsoapContext, oss);
			delete wrapper;
		}
		else {
			addOrReplaceDataObject(wrapper);
			return wrapper;
		}
	}

	addWarning("The content type " + contentType + " could not be wrapped by fesapi. The related instance will be ignored.");
	return nullptr;
}

std::unordered_map< std::string, std::vector<COMMON_NS::AbstractObject*> > DataObjectRepository::getDataObjectsGroupedByContentType() const
{
	std::unordered_map< std::string, std::vector<COMMON_NS::AbstractObject*> > result;
	for (std::unordered_map< std::string, std::vector< COMMON_NS::AbstractObject* > >::const_iterator it = dataObjects.begin(); it != dataObjects.end(); ++it) {
		for (size_t i = 0; i < it->second.size(); ++i) {
			std::string contentType = it->second[i]->getContentType();
			if (contentType.find("x-eml") == std::string::npos) {
				result[contentType].push_back(it->second[i]);
			}
		}
	}

	return result;
}

std::vector<COMMON_NS::AbstractObject*> DataObjectRepository::getDataObjectsByContentType(const std::string & contentType) const
{
	std::vector<COMMON_NS::AbstractObject*> result;

	for (std::unordered_map< std::string, std::vector< COMMON_NS::AbstractObject* > >::const_iterator it = dataObjects.begin(); it != dataObjects.end(); ++it) {
		for (size_t i = 0; i < it->second.size(); ++i) {
			if (it->second[i]->getContentType() == contentType) {
				result.push_back(it->second[i]);
			}
		}
	}

	return result;
}

COMMON_NS::AbstractObject* DataObjectRepository::getDataObjectByUuid(const string & uuid) const
{
	std::unordered_map< std::string, std::vector< COMMON_NS::AbstractObject* > >::const_iterator it = dataObjects.find(uuid);

	return it == dataObjects.end() || it->second.empty() ? nullptr : it->second[0];
}

COMMON_NS::AbstractObject* DataObjectRepository::getDataObjectByUuidAndVersion(const string & uuid, const std::string & version) const
{
	std::unordered_map< std::string, std::vector< COMMON_NS::AbstractObject* > >::const_iterator it = dataObjects.find(uuid);

	if (it == dataObjects.end() || it->second.empty()) {
		return nullptr;
	}

	std::vector< COMMON_NS::AbstractObject* >::const_iterator vectIt = std::find_if(it->second.begin(), it->second.end(), SameVersion(version));
	return vectIt == it->second.end() ? nullptr : *vectIt;
}

void DataObjectRepository::addWarning(const std::string & warning)
{
	warnings.push_back(warning);
}

const std::vector<std::string> & DataObjectRepository::getWarnings() const
{
	return warnings;
}

COMMON_NS::AbstractObject* DataObjectRepository::createPartial(const DataObjectReference& dor)
{
	std::string contentType = dor.getContentType();

	if (contentType.find("obj_") != std::string::npos) {
		const size_t lastEqualCharPos = contentType.find_last_of('_'); // The XML tag is after "type=obj_"
		const string dataType = contentType.substr(lastEqualCharPos + 1);

		if CREATE_FESAPI_PARTIAL_WRAPPER(MdDatum)
		else if CREATE_FESAPI_PARTIAL_WRAPPER(Activity)
		else if CREATE_FESAPI_PARTIAL_WRAPPER(ActivityTemplate)
		else if CREATE_FESAPI_PARTIAL_WRAPPER(SeismicLatticeFeature)
		else if CREATE_FESAPI_PARTIAL_WRAPPER(SeismicLineFeature)
		else if CREATE_FESAPI_PARTIAL_WRAPPER(SeismicLineSetFeature)
		else if CREATE_FESAPI_PARTIAL_WRAPPER(FrontierFeature)
		else if CREATE_FESAPI_PARTIAL_WRAPPER(LocalDepth3dCrs)
		else if CREATE_FESAPI_PARTIAL_WRAPPER(LocalTime3dCrs)
		else if CREATE_FESAPI_PARTIAL_WRAPPER(TectonicBoundaryFeature)
		else if CREATE_FESAPI_PARTIAL_WRAPPER(GeneticBoundaryFeature)
		else if CREATE_FESAPI_PARTIAL_WRAPPER(BoundaryFeature)
		else if CREATE_FESAPI_PARTIAL_WRAPPER(WellboreFeature)
		else if CREATE_FESAPI_PARTIAL_WRAPPER(StratigraphicUnitFeature)
		else if CREATE_FESAPI_PARTIAL_WRAPPER(StratigraphicColumn)
		else if CREATE_FESAPI_PARTIAL_WRAPPER(GenericFeatureInterpretation)
		else if CREATE_FESAPI_PARTIAL_WRAPPER(BoundaryFeatureInterpretation)
		else if CREATE_FESAPI_PARTIAL_WRAPPER(WellboreInterpretation)
		else if CREATE_FESAPI_PARTIAL_WRAPPER(FaultInterpretation)
		else if CREATE_FESAPI_PARTIAL_WRAPPER(HorizonInterpretation)
		else if CREATE_FESAPI_PARTIAL_WRAPPER(StratigraphicUnitInterpretation)
		else if CREATE_FESAPI_PARTIAL_WRAPPER(StratigraphicColumnRankInterpretation)
		else if CREATE_FESAPI_PARTIAL_WRAPPER(StratigraphicOccurrenceInterpretation)
		else if CREATE_FESAPI_PARTIAL_WRAPPER(RESQML2_0_1_NS::WellboreFrameRepresentation)
		else if CREATE_FESAPI_PARTIAL_WRAPPER(WellboreMarkerFrameRepresentation)
		else if CREATE_FESAPI_PARTIAL_WRAPPER(WellboreTrajectoryRepresentation)
		else if CREATE_FESAPI_PARTIAL_WRAPPER(PolylineSetRepresentation)
		else if CREATE_FESAPI_PARTIAL_WRAPPER(PointSetRepresentation)
		else if CREATE_FESAPI_PARTIAL_WRAPPER(PlaneSetRepresentation)
		else if CREATE_FESAPI_PARTIAL_WRAPPER(PolylineRepresentation)
		else if CREATE_FESAPI_PARTIAL_WRAPPER(Grid2dRepresentation)
		else if CREATE_FESAPI_PARTIAL_WRAPPER(TriangulatedSetRepresentation)
		else if CREATE_FESAPI_PARTIAL_WRAPPER(BlockedWellboreRepresentation)
		else if CREATE_FESAPI_PARTIAL_WRAPPER(RESQML2_NS::AbstractIjkGridRepresentation)
		else if CREATE_FESAPI_PARTIAL_WRAPPER(RESQML2_0_1_NS::UnstructuredGridRepresentation)
		else if CREATE_FESAPI_PARTIAL_WRAPPER(RESQML2_0_1_NS::PropertyKind)
		else if CREATE_FESAPI_PARTIAL_WRAPPER(PropertySet)
		else if CREATE_FESAPI_PARTIAL_WRAPPER(RESQML2_0_1_NS::ContinuousProperty)
		else if CREATE_FESAPI_PARTIAL_WRAPPER(RESQML2_0_1_NS::CategoricalProperty)
		else if CREATE_FESAPI_PARTIAL_WRAPPER(RESQML2_0_1_NS::DiscreteProperty)
		else if CREATE_FESAPI_PARTIAL_WRAPPER(RESQML2_0_1_NS::CommentProperty)
		else if CREATE_FESAPI_PARTIAL_WRAPPER(StringTableLookup)
		else if CREATE_FESAPI_PARTIAL_WRAPPER(EarthModelInterpretation)
		else if CREATE_FESAPI_PARTIAL_WRAPPER(OrganizationFeature)
		else if CREATE_FESAPI_PARTIAL_WRAPPER(StructuralOrganizationInterpretation)
		else if CREATE_FESAPI_PARTIAL_WRAPPER(FluidBoundaryFeature)
		else if CREATE_FESAPI_PARTIAL_WRAPPER(SubRepresentation)
		else if CREATE_FESAPI_PARTIAL_WRAPPER(GridConnectionSetRepresentation)
		else if CREATE_FESAPI_PARTIAL_WRAPPER(TimeSeries)
		else if CREATE_FESAPI_PARTIAL_WRAPPER(RepresentationSetRepresentation)
		else if CREATE_FESAPI_PARTIAL_WRAPPER(NonSealedSurfaceFrameworkRepresentation)
		else if CREATE_FESAPI_PARTIAL_WRAPPER(SealedSurfaceFrameworkRepresentation)
		else if CREATE_FESAPI_PARTIAL_WRAPPER(SealedVolumeFrameworkRepresentation)
		else if CREATE_FESAPI_PARTIAL_WRAPPER(DeviationSurveyRepresentation)
		else if CREATE_FESAPI_PARTIAL_WRAPPER(GeobodyFeature)
		else if CREATE_FESAPI_PARTIAL_WRAPPER(GeobodyBoundaryInterpretation)
		else if CREATE_FESAPI_PARTIAL_WRAPPER(GeobodyInterpretation)
		else if CREATE_FESAPI_PARTIAL_WRAPPER(RockFluidOrganizationInterpretation)
		else if CREATE_FESAPI_PARTIAL_WRAPPER(RockFluidUnitInterpretation)
		else if CREATE_FESAPI_PARTIAL_WRAPPER(RockFluidUnitFeature)
		else if (dataType.compare(COMMON_NS::EpcExternalPartReference::XML_TAG) == 0)
		{
			throw invalid_argument("Please handle this type outside this method since it is not only XML related.");
		}

		throw invalid_argument("The resqml2.0.1 dataType " + dataType + " of the partial object (DOR) to create has not been recognized by fesapi.");
	}
	else if (contentType.find("application/x-witsml+xml;version=2.0") != std::string::npos ||
		contentType.find("application/x-eml+xml;version=2.1") != std::string::npos) {
		const size_t lastEqualCharPos = contentType.find_last_of('='); // The XML tag is after "type="
		const string dataType = contentType.substr(lastEqualCharPos + 1);

		if CREATE_FESAPI_PARTIAL_WRAPPER(WITSML2_0_NS::Well)
		else if CREATE_FESAPI_PARTIAL_WRAPPER(WITSML2_0_NS::Wellbore)
		else if CREATE_FESAPI_PARTIAL_WRAPPER(WITSML2_0_NS::Trajectory)
		else if CREATE_FESAPI_PARTIAL_WRAPPER(WITSML2_0_NS::PropertyKind)
		else if CREATE_FESAPI_PARTIAL_WRAPPER(WITSML2_0_NS::Log)
		else if CREATE_FESAPI_PARTIAL_WRAPPER(WITSML2_0_NS::ChannelSet)
		else if CREATE_FESAPI_PARTIAL_WRAPPER(WITSML2_0_NS::Channel)
		else if (dataType.compare(COMMON_NS::EpcExternalPartReference::XML_TAG) == 0)
		{
			throw invalid_argument("Please handle this type outside this method since it is not only XML related.");
		}

		throw invalid_argument("The eml21 dataType " + dataType + " of the partial object (DOR) to create has not been recognized by fesapi.");
	}
	else if (contentType.find("application/x-prodml+xml;version=2.1") != std::string::npos ||
		contentType.find("application/x-resqml+xml;version=2.2") != std::string::npos) {
		const size_t lastEqualCharPos = contentType.find_last_of('='); // The XML tag is after "type="
		const string dataType = contentType.substr(lastEqualCharPos + 1);

		if CREATE_FESAPI_PARTIAL_WRAPPER(COMMON_NS::GraphicalInformationSet)
		else if CREATE_FESAPI_PARTIAL_WRAPPER(PRODML2_1_NS::FluidSystem)
		else if CREATE_FESAPI_PARTIAL_WRAPPER(PRODML2_1_NS::FluidCharacterization)
		else if CREATE_FESAPI_PARTIAL_WRAPPER(RESQML2_2_NS::DiscreteColorMap)
		else if CREATE_FESAPI_PARTIAL_WRAPPER(RESQML2_2_NS::ContinuousColorMap)
		else if CREATE_FESAPI_PARTIAL_WRAPPER(RESQML2_2_NS::WellboreFrameRepresentation)
		else if CREATE_FESAPI_PARTIAL_WRAPPER(RESQML2_2_NS::SeismicWellboreFrameRepresentation)
		else if (dataType.compare(COMMON_NS::EpcExternalPartReference::XML_TAG) == 0)
		{
			throw invalid_argument("Please handle this type outside this method since it is not only XML related.");
		}

		throw invalid_argument("The eml22 dataType " + dataType + " of the partial object (DOR) to create has not been recognized by fesapi.");
	}

	throw invalid_argument("The content type " + contentType + " of the partial object (DOR) to create has not been recognized by fesapi.");
}
//************************************
//************ HDF *******************
//************************************

COMMON_NS::AbstractHdfProxy* DataObjectRepository::createHdfProxy(const std::string & guid, const std::string & title, const std::string & packageDirAbsolutePath, const std::string & externalFilePath, DataObjectRepository::openingMode hdfPermissionAccess)
{
	return hdfProxyFactory->make(this, guid, title, packageDirAbsolutePath, externalFilePath, hdfPermissionAccess);
}

//************************************
//************ CRS *******************
//************************************

LocalDepth3dCrs* DataObjectRepository::createLocalDepth3dCrs(const std::string & guid, const std::string & title,
	double originOrdinal1, double originOrdinal2, double originOrdinal3,
	double arealRotation,
	gsoap_resqml2_0_1::eml20__LengthUom projectedUom, unsigned long projectedEpsgCode,
	gsoap_resqml2_0_1::eml20__LengthUom verticalUom, unsigned int verticalEpsgCode, bool isUpOriented)
{
	return new LocalDepth3dCrs(this, guid, title, originOrdinal1, originOrdinal2, originOrdinal3, arealRotation,
		projectedUom, projectedEpsgCode,
		verticalUom, verticalEpsgCode, isUpOriented);
}

RESQML2_0_1_NS::LocalDepth3dCrs* DataObjectRepository::createLocalDepth3dCrs(const std::string & guid, const std::string & title,
	const double & originOrdinal1, const double & originOrdinal2, const double & originOrdinal3,
	const double & arealRotation,
	const gsoap_resqml2_0_1::eml20__LengthUom & projectedUom, const std::string & projectedUnknownReason,
	const gsoap_resqml2_0_1::eml20__LengthUom & verticalUom, const std::string & verticalUnknownReason, const bool & isUpOriented)
{
	return new LocalDepth3dCrs(this, guid, title, originOrdinal1, originOrdinal2, originOrdinal3, arealRotation,
		projectedUom, projectedUnknownReason,
		verticalUom, verticalUnknownReason, isUpOriented);
}

RESQML2_0_1_NS::LocalDepth3dCrs* DataObjectRepository::createLocalDepth3dCrs(const std::string & guid, const std::string & title,
	const double & originOrdinal1, const double & originOrdinal2, const double & originOrdinal3,
	const double & arealRotation,
	const gsoap_resqml2_0_1::eml20__LengthUom & projectedUom, const unsigned long & projectedEpsgCode,
	const gsoap_resqml2_0_1::eml20__LengthUom & verticalUom, const std::string & verticalUnknownReason, const bool & isUpOriented)
{
	return new LocalDepth3dCrs(this, guid, title, originOrdinal1, originOrdinal2, originOrdinal3, arealRotation,
		projectedUom, projectedEpsgCode,
		verticalUom, verticalUnknownReason, isUpOriented);
}

RESQML2_0_1_NS::LocalDepth3dCrs* DataObjectRepository::createLocalDepth3dCrs(const std::string & guid, const std::string & title,
	const double & originOrdinal1, const double & originOrdinal2, const double & originOrdinal3,
	const double & arealRotation,
	const gsoap_resqml2_0_1::eml20__LengthUom & projectedUom, const std::string & projectedUnknownReason,
	const gsoap_resqml2_0_1::eml20__LengthUom & verticalUom, const unsigned int & verticalEpsgCode, const bool & isUpOriented)
{
	return new LocalDepth3dCrs(this, guid, title, originOrdinal1, originOrdinal2, originOrdinal3, arealRotation,
		projectedUom, projectedUnknownReason,
		verticalUom, verticalEpsgCode, isUpOriented);
}

LocalTime3dCrs* DataObjectRepository::createLocalTime3dCrs(const std::string & guid, const std::string & title,
	const double & originOrdinal1, const double & originOrdinal2, const double & originOrdinal3,
	const double & arealRotation,
	const gsoap_resqml2_0_1::eml20__LengthUom & projectedUom, const unsigned long & projectedEpsgCode,
	const gsoap_resqml2_0_1::eml20__TimeUom & timeUom,
	const gsoap_resqml2_0_1::eml20__LengthUom & verticalUom, const unsigned int & verticalEpsgCode, const bool & isUpOriented)
{
	return new LocalTime3dCrs(this, guid, title, originOrdinal1, originOrdinal2, originOrdinal3, arealRotation,
		projectedUom, projectedEpsgCode,
		timeUom,
		verticalUom, verticalEpsgCode, isUpOriented);
}

LocalTime3dCrs* DataObjectRepository::createLocalTime3dCrs(const std::string & guid, const std::string & title,
	const double & originOrdinal1, const double & originOrdinal2, const double & originOrdinal3,
	const double & arealRotation,
	const gsoap_resqml2_0_1::eml20__LengthUom & projectedUom, const std::string & projectedUnknownReason,
	const gsoap_resqml2_0_1::eml20__TimeUom & timeUom,
	const gsoap_resqml2_0_1::eml20__LengthUom & verticalUom, const std::string & verticalUnknownReason, const bool & isUpOriented)
{
	return new LocalTime3dCrs(this, guid, title, originOrdinal1, originOrdinal2, originOrdinal3, arealRotation,
		projectedUom, projectedUnknownReason,
		timeUom,
		verticalUom, verticalUnknownReason, isUpOriented);
}

LocalTime3dCrs* DataObjectRepository::createLocalTime3dCrs(const std::string & guid, const std::string & title,
	const double & originOrdinal1, const double & originOrdinal2, const double & originOrdinal3,
	const double & arealRotation,
	const gsoap_resqml2_0_1::eml20__LengthUom & projectedUom, const unsigned long & projectedEpsgCode,
	const gsoap_resqml2_0_1::eml20__TimeUom & timeUom,
	const gsoap_resqml2_0_1::eml20__LengthUom & verticalUom, const std::string & verticalUnknownReason, const bool & isUpOriented)
{
	return new LocalTime3dCrs(this, guid, title, originOrdinal1, originOrdinal2, originOrdinal3, arealRotation,
		projectedUom, projectedEpsgCode,
		timeUom,
		verticalUom, verticalUnknownReason, isUpOriented);
}

LocalTime3dCrs* DataObjectRepository::createLocalTime3dCrs(const std::string & guid, const std::string & title,
	const double & originOrdinal1, const double & originOrdinal2, const double & originOrdinal3,
	const double & arealRotation,
	const gsoap_resqml2_0_1::eml20__LengthUom & projectedUom, const std::string & projectedUnknownReason,
	const gsoap_resqml2_0_1::eml20__TimeUom & timeUom,
	const gsoap_resqml2_0_1::eml20__LengthUom & verticalUom, const unsigned int & verticalEpsgCode, const bool & isUpOriented)
{
	return new LocalTime3dCrs(this, guid, title, originOrdinal1, originOrdinal2, originOrdinal3, arealRotation,
		projectedUom, projectedUnknownReason,
		timeUom,
		verticalUom, verticalEpsgCode, isUpOriented);
}

RESQML2_NS::MdDatum* DataObjectRepository::createMdDatum(const std::string & guid, const std::string & title,
	RESQML2_NS::AbstractLocal3dCrs * locCrs, const gsoap_resqml2_0_1::resqml20__MdReference & originKind,
	const double & referenceLocationOrdinal1, const double & referenceLocationOrdinal2, const double & referenceLocationOrdinal3)
{
	return new MdDatum(this, guid, title, locCrs, originKind, referenceLocationOrdinal1, referenceLocationOrdinal2, referenceLocationOrdinal3);
}
//************************************
//************ FEATURE ***************
//************************************

BoundaryFeature* DataObjectRepository::createBoundaryFeature(const std::string & guid, const std::string & title)
{
	return new BoundaryFeature(this, guid, title);
}

Horizon* DataObjectRepository::createHorizon(const std::string & guid, const std::string & title)
{
	return new Horizon(this, guid, title);
}

GeneticBoundaryFeature* DataObjectRepository::createGeobodyBoundaryFeature(const std::string & guid, const std::string & title)
{
	return new GeneticBoundaryFeature(this, guid, title, false);
}

RESQML2_0_1_NS::GeobodyFeature* DataObjectRepository::createGeobodyFeature(const std::string & guid, const std::string & title)
{
	return new GeobodyFeature(this, guid, title);
}

TectonicBoundaryFeature* DataObjectRepository::createFault(const std::string & guid, const std::string & title)
{
	return new TectonicBoundaryFeature(this, guid, title, false);
}

TectonicBoundaryFeature* DataObjectRepository::createFracture(const std::string & guid, const std::string & title)
{
	return new TectonicBoundaryFeature(this, guid, title, true);
}

RESQML2_NS::WellboreFeature* DataObjectRepository::createWellboreFeature(const std::string & guid, const std::string & title)
{
	return new RESQML2_0_1_NS::WellboreFeature(this, guid, title);
}

SeismicLatticeFeature* DataObjectRepository::createSeismicLattice(const std::string & guid, const std::string & title,
	const int & inlineIncrement, const int & crosslineIncrement,
	const unsigned int & originInline, const unsigned int & originCrossline,
	const unsigned int & inlineCount, const unsigned int & crosslineCount)
{
	return new SeismicLatticeFeature(this, guid, title, inlineIncrement, crosslineIncrement, originInline, originCrossline, inlineCount, crosslineCount);
}

SeismicLineFeature* DataObjectRepository::createSeismicLine(const std::string & guid, const std::string & title,
	const int & traceIndexIncrement, const unsigned int & firstTraceIndex, const unsigned int & traceCount)
{
	return new SeismicLineFeature(this, guid, title, traceIndexIncrement, firstTraceIndex, traceCount);
}

SeismicLineSetFeature* DataObjectRepository::createSeismicLineSet(const std::string & guid, const std::string & title)
{
	return new SeismicLineSetFeature(this, guid, title);
}

FrontierFeature* DataObjectRepository::createFrontier(const std::string & guid, const std::string & title)
{
	return new FrontierFeature(this, guid, title);
}

StratigraphicUnitFeature* DataObjectRepository::createStratigraphicUnit(const std::string & guid, const std::string & title)
{
	return new StratigraphicUnitFeature(this, guid, title);
}

RockFluidUnitFeature* DataObjectRepository::createRockFluidUnit(const std::string & guid, const std::string & title, gsoap_resqml2_0_1::resqml20__Phase phase,
	RESQML2_0_1_NS::FluidBoundaryFeature* fluidBoundaryTop, RESQML2_0_1_NS::FluidBoundaryFeature* fluidBoundaryBottom)
{
	return new RockFluidUnitFeature(this, guid, title, phase, fluidBoundaryTop, fluidBoundaryBottom);
}

OrganizationFeature* DataObjectRepository::createStructuralModel(const std::string & guid, const std::string & title)
{
	return new OrganizationFeature(this, guid, title, gsoap_resqml2_0_1::resqml20__OrganizationKind__structural);
}

OrganizationFeature* DataObjectRepository::createStratigraphicModel(const std::string & guid, const std::string & title)
{
	return new OrganizationFeature(this, guid, title, gsoap_resqml2_0_1::resqml20__OrganizationKind__stratigraphic);
}

OrganizationFeature* DataObjectRepository::createRockFluidModel(const std::string & guid, const std::string & title)
{
	return new OrganizationFeature(this, guid, title, gsoap_resqml2_0_1::resqml20__OrganizationKind__fluid);
}

OrganizationFeature* DataObjectRepository::createEarthModel(const std::string & guid, const std::string & title)
{
	return new OrganizationFeature(this, guid, title, gsoap_resqml2_0_1::resqml20__OrganizationKind__earth_x0020model);
}

FluidBoundaryFeature* DataObjectRepository::createFluidBoundaryFeature(const std::string & guid, const std::string & title, const gsoap_resqml2_0_1::resqml20__FluidContact & fluidContact)
{
	return new FluidBoundaryFeature(this, guid, title, fluidContact);
}

//************************************
//************ INTERPRETATION ********
//************************************

GenericFeatureInterpretation* DataObjectRepository::createGenericFeatureInterpretation(RESQML2_NS::AbstractFeature * feature, const std::string & guid, const std::string & title)
{
	return new GenericFeatureInterpretation(feature, guid, title);
}

BoundaryFeatureInterpretation* DataObjectRepository::createBoundaryFeatureInterpretation(RESQML2_0_1_NS::BoundaryFeature * feature, const std::string & guid, const std::string & title)
{
	return new BoundaryFeatureInterpretation(feature, guid, title);
}

HorizonInterpretation* DataObjectRepository::createHorizonInterpretation(Horizon * horizon, const std::string & guid, const std::string & title)
{
	return new HorizonInterpretation(horizon, guid, title);
}

RESQML2_0_1_NS::GeobodyBoundaryInterpretation* DataObjectRepository::createGeobodyBoundaryInterpretation(RESQML2_0_1_NS::GeneticBoundaryFeature * geobodyBoundary, const std::string & guid, const std::string & title)
{
	return new GeobodyBoundaryInterpretation(geobodyBoundary, guid, title);
}

FaultInterpretation* DataObjectRepository::createFaultInterpretation(TectonicBoundaryFeature * fault, const std::string & guid, const std::string & title)
{
	return new FaultInterpretation(fault, guid, title);
}

RESQML2_NS::WellboreInterpretation* DataObjectRepository::createWellboreInterpretation(RESQML2_NS::WellboreFeature * wellbore, const std::string & guid, const std::string & title, bool isDrilled)
{
	return new RESQML2_0_1_NS::WellboreInterpretation(wellbore, guid, title, isDrilled);
}

EarthModelInterpretation* DataObjectRepository::createEarthModelInterpretation(OrganizationFeature * orgFeat, const std::string & guid, const std::string & title)
{
	return new EarthModelInterpretation(orgFeat, guid, title);
}

StructuralOrganizationInterpretation* DataObjectRepository::createStructuralOrganizationInterpretationInAge(OrganizationFeature * orgFeat, const std::string & guid, const std::string & title)
{
	return new StructuralOrganizationInterpretation(orgFeat, guid, title, gsoap_resqml2_0_1::resqml20__OrderingCriteria__age);
}

StructuralOrganizationInterpretation* DataObjectRepository::createStructuralOrganizationInterpretationInApparentDepth(OrganizationFeature * orgFeat, const std::string & guid, const std::string & title)
{
	return new StructuralOrganizationInterpretation(orgFeat, guid, title, gsoap_resqml2_0_1::resqml20__OrderingCriteria__apparent_x0020depth);
}

StructuralOrganizationInterpretation* DataObjectRepository::createStructuralOrganizationInterpretationInMeasuredDepth(OrganizationFeature * orgFeat, const std::string & guid, const std::string & title)
{
	return new StructuralOrganizationInterpretation(orgFeat, guid, title, gsoap_resqml2_0_1::resqml20__OrderingCriteria__measured_x0020depth);
}

RockFluidOrganizationInterpretation* DataObjectRepository::createRockFluidOrganizationInterpretation(OrganizationFeature * orgFeat, const std::string & guid, const std::string & title, RESQML2_0_1_NS::RockFluidUnitInterpretation * rockFluidUnitInterp)
{
	return new RockFluidOrganizationInterpretation(orgFeat, guid, title, rockFluidUnitInterp);
}

RockFluidUnitInterpretation* DataObjectRepository::createRockFluidUnitInterpretation(RESQML2_0_1_NS::RockFluidUnitFeature * rockFluidUnitFeature, const std::string & guid, const std::string & title)
{
	return new RockFluidUnitInterpretation(rockFluidUnitFeature, guid, title);
}

StratigraphicColumn* DataObjectRepository::createStratigraphicColumn(const std::string & guid, const std::string & title)
{
	return new StratigraphicColumn(this, guid, title);
}

GeobodyInterpretation* DataObjectRepository::createGeobodyInterpretation(RESQML2_0_1_NS::GeobodyFeature * geobody, const std::string & guid, const std::string & title)
{
	return new GeobodyInterpretation(geobody, guid, title);
}

StratigraphicUnitInterpretation* DataObjectRepository::createStratigraphicUnitInterpretation(StratigraphicUnitFeature * stratiUnitFeature, const std::string & guid, const std::string & title)
{
	return new StratigraphicUnitInterpretation(stratiUnitFeature, guid, title);
}

StratigraphicColumnRankInterpretation* DataObjectRepository::createStratigraphicColumnRankInterpretationInAge(OrganizationFeature * orgFeat, const std::string & guid, const std::string & title, const unsigned long & rank)
{
	return new StratigraphicColumnRankInterpretation(orgFeat, guid, title, rank, gsoap_resqml2_0_1::resqml20__OrderingCriteria__age);
}

StratigraphicColumnRankInterpretation* DataObjectRepository::createStratigraphicColumnRankInterpretationInApparentDepth(OrganizationFeature * orgFeat, const std::string & guid, const std::string & title, const unsigned long & rank)
{
	return new StratigraphicColumnRankInterpretation(orgFeat, guid, title, rank, gsoap_resqml2_0_1::resqml20__OrderingCriteria__apparent_x0020depth);
}

StratigraphicOccurrenceInterpretation* DataObjectRepository::createStratigraphicOccurrenceInterpretationInAge(OrganizationFeature * orgFeat, const std::string & guid, const std::string & title)
{
	return new StratigraphicOccurrenceInterpretation(orgFeat, guid, title, gsoap_resqml2_0_1::resqml20__OrderingCriteria__age);
}

StratigraphicOccurrenceInterpretation* DataObjectRepository::createStratigraphicOccurrenceInterpretationInApparentDepth(OrganizationFeature * orgFeat, const std::string & guid, const std::string & title)
{
	return new StratigraphicOccurrenceInterpretation(orgFeat, guid, title, gsoap_resqml2_0_1::resqml20__OrderingCriteria__apparent_x0020depth);
}

//************************************
//************ REPRESENTATION ********
//************************************

TriangulatedSetRepresentation* DataObjectRepository::createTriangulatedSetRepresentation(const std::string & guid, const std::string & title)
{
	return new TriangulatedSetRepresentation(this, guid, title);
}

TriangulatedSetRepresentation* DataObjectRepository::createTriangulatedSetRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp,
	const std::string & guid, const std::string & title)
{
	return new TriangulatedSetRepresentation(interp, guid, title);
}

PolylineSetRepresentation* DataObjectRepository::createPolylineSetRepresentation(const std::string & guid, const std::string & title)
{
	return new PolylineSetRepresentation(this, guid, title);
}

PolylineSetRepresentation* DataObjectRepository::createPolylineSetRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp,
	const std::string & guid, const std::string & title)
{
	return new PolylineSetRepresentation(interp, guid, title);
}

PolylineSetRepresentation* DataObjectRepository::createPolylineSetRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp,
	const std::string & guid, const std::string & title, gsoap_resqml2_0_1::resqml20__LineRole roleKind)
{
	return new PolylineSetRepresentation(interp, guid, title, roleKind);
}

PointSetRepresentation* DataObjectRepository::createPointSetRepresentation(const std::string & guid, const std::string & title)
{
	return new PointSetRepresentation(this, guid, title);
}

PointSetRepresentation* DataObjectRepository::createPointSetRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp,
	const std::string & guid, const std::string & title)
{
	return new PointSetRepresentation(interp, guid, title);
}

PlaneSetRepresentation* DataObjectRepository::createPlaneSetRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp,
	const std::string & guid, const std::string & title)
{
	return new PlaneSetRepresentation(interp, guid, title);
}

PolylineRepresentation* DataObjectRepository::createPolylineRepresentation(const std::string & guid, const std::string & title, bool isClosed)
{
	return new PolylineRepresentation(this, guid, title, isClosed);
}

PolylineRepresentation* DataObjectRepository::createPolylineRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp,
	const std::string & guid, const std::string & title, bool isClosed)
{
	return new PolylineRepresentation(interp, guid, title, isClosed);
}

PolylineRepresentation* DataObjectRepository::createPolylineRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp,
	const std::string & guid, const std::string & title, const gsoap_resqml2_0_1::resqml20__LineRole & roleKind, bool isClosed)
{
	return new PolylineRepresentation(interp, guid, title, roleKind, isClosed);
}

Grid2dRepresentation* DataObjectRepository::createGrid2dRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp,
	const std::string & guid, const std::string & title)
{
	return new Grid2dRepresentation(interp, guid, title);
}

RESQML2_NS::WellboreTrajectoryRepresentation* DataObjectRepository::createWellboreTrajectoryRepresentation(RESQML2_NS::WellboreInterpretation * interp, const std::string & guid, const std::string & title, RESQML2_NS::MdDatum * mdInfo)
{
	return new RESQML2_0_1_NS::WellboreTrajectoryRepresentation(interp, guid, title, mdInfo);
}

RESQML2_NS::WellboreTrajectoryRepresentation* DataObjectRepository::createWellboreTrajectoryRepresentation(RESQML2_NS::WellboreInterpretation * interp, const std::string & guid, const std::string & title, RESQML2_NS::DeviationSurveyRepresentation * deviationSurvey)
{
	return new RESQML2_0_1_NS::WellboreTrajectoryRepresentation(interp, guid, title, deviationSurvey);
}

RESQML2_NS::DeviationSurveyRepresentation* DataObjectRepository::createDeviationSurveyRepresentation(RESQML2_NS::WellboreInterpretation * interp, const std::string & guid, const std::string & title, const bool & isFinal, RESQML2_NS::MdDatum * mdInfo)
{
	return new RESQML2_0_1_NS::DeviationSurveyRepresentation(interp, guid, title, isFinal, mdInfo);
}

RESQML2_NS::WellboreFrameRepresentation* DataObjectRepository::createWellboreFrameRepresentation(RESQML2_NS::WellboreInterpretation * interp, const std::string & guid, const std::string & title, RESQML2_NS::WellboreTrajectoryRepresentation * traj)
{
	switch (defaultResqmlVersion) {
	case DataObjectRepository::EnergisticsStandard::RESQML2_0_1:
		return new RESQML2_0_1_NS::WellboreFrameRepresentation(interp, guid, title, traj);
	case DataObjectRepository::EnergisticsStandard::RESQML2_2:
		return new RESQML2_2_NS::WellboreFrameRepresentation(interp, guid, title, traj);
	default:
		throw std::invalid_argument("Unrecognized Energistics standard.");
	}
}

RESQML2_2_NS::SeismicWellboreFrameRepresentation* DataObjectRepository::createSeismicWellboreFrameRepresentation(
	RESQML2_NS::WellboreInterpretation* interp,
	const std::string& guid, const std::string& title,
	RESQML2_NS::WellboreTrajectoryRepresentation* traj,
	double seismicReferenceDatum,
	double weatheringVelocity,
	class RESQML2_0_1_NS::LocalTime3dCrs* crs)
{
	return new RESQML2_2_NS::SeismicWellboreFrameRepresentation(interp, guid, title, traj, seismicReferenceDatum, weatheringVelocity, crs);
}

RESQML2_0_1_NS::WellboreMarkerFrameRepresentation* DataObjectRepository::createWellboreMarkerFrameRepresentation(RESQML2_NS::WellboreInterpretation * interp, const std::string & guid, const std::string & title, RESQML2_NS::WellboreTrajectoryRepresentation * traj)
{
	return new RESQML2_0_1_NS::WellboreMarkerFrameRepresentation(interp, guid, title, traj);
}

BlockedWellboreRepresentation* DataObjectRepository::createBlockedWellboreRepresentation(RESQML2_NS::WellboreInterpretation * interp,
	const std::string & guid, const std::string & title, RESQML2_NS::WellboreTrajectoryRepresentation * traj)
{
	return new BlockedWellboreRepresentation(interp, guid, title, traj);
}

RESQML2_NS::RepresentationSetRepresentation* DataObjectRepository::createRepresentationSetRepresentation(
	RESQML2_NS::AbstractOrganizationInterpretation* interp,
	const std::string & guid,
	const std::string & title)
{
	return new RESQML2_0_1_NS::RepresentationSetRepresentation(interp, guid, title);
}

RESQML2_NS::RepresentationSetRepresentation* DataObjectRepository::createRepresentationSetRepresentation(
	const std::string & guid,
	const std::string & title)
{
	return new RESQML2_0_1_NS::RepresentationSetRepresentation(this, guid, title);
}

NonSealedSurfaceFrameworkRepresentation* DataObjectRepository::createNonSealedSurfaceFrameworkRepresentation(
	StructuralOrganizationInterpretation* interp,
	const std::string & guid,
	const std::string & title)
{
	return new NonSealedSurfaceFrameworkRepresentation(interp, guid, title);
}

SealedSurfaceFrameworkRepresentation* DataObjectRepository::createSealedSurfaceFrameworkRepresentation(
	StructuralOrganizationInterpretation* interp,
	const std::string & guid,
	const std::string & title)
{
	return new SealedSurfaceFrameworkRepresentation(interp, guid, title);
}

RESQML2_0_1_NS::SealedVolumeFrameworkRepresentation* DataObjectRepository::createSealedVolumeFrameworkRepresentation(
	RESQML2_0_1_NS::StratigraphicColumnRankInterpretation* interp,
	const std::string & guid,
	const std::string & title,
	RESQML2_0_1_NS::SealedSurfaceFrameworkRepresentation* ssf)
{
	return new SealedVolumeFrameworkRepresentation(interp, guid, title, ssf);
}

RESQML2_NS::AbstractIjkGridRepresentation* DataObjectRepository::createPartialIjkGridRepresentation(const std::string & guid, const std::string & title)
{
	return createPartial<RESQML2_NS::AbstractIjkGridRepresentation>(guid, title);
}

RESQML2_NS::AbstractIjkGridRepresentation* DataObjectRepository::createPartialTruncatedIjkGridRepresentation(const std::string & guid, const std::string & title)
{
	gsoap_resqml2_0_1::eml20__DataObjectReference* dor = gsoap_resqml2_0_1::soap_new_eml20__DataObjectReference(getGsoapContext());
	dor->UUID = guid;
	dor->Title = title;
	return new RESQML2_NS::AbstractIjkGridRepresentation(dor, true);
}

RESQML2_NS::IjkGridExplicitRepresentation* DataObjectRepository::createIjkGridExplicitRepresentation(const std::string & guid, const std::string & title,
	unsigned int iCount, unsigned int jCount, unsigned int kCount)
{
	switch (defaultResqmlVersion) {
	case EnergisticsStandard::RESQML2_0_1 : return new RESQML2_0_1_NS::IjkGridExplicitRepresentation(this, guid, title, iCount, jCount, kCount);
	case EnergisticsStandard::RESQML2_2: return new RESQML2_2_NS::IjkGridExplicitRepresentation(this, guid, title, iCount, jCount, kCount);
	default: throw std::logic_error("The RESQML version is not supported.");
	}
}

RESQML2_NS::IjkGridExplicitRepresentation* DataObjectRepository::createIjkGridExplicitRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp,
	const std::string & guid, const std::string & title,
	unsigned int iCount, unsigned int jCount, unsigned int kCount)
{
	switch (defaultResqmlVersion) {
	case EnergisticsStandard::RESQML2_0_1: return new RESQML2_0_1_NS::IjkGridExplicitRepresentation(interp, guid, title, iCount, jCount, kCount);
	case EnergisticsStandard::RESQML2_2: return new RESQML2_2_NS::IjkGridExplicitRepresentation(interp, guid, title, iCount, jCount, kCount);
	default: throw std::logic_error("The RESQML version is not supported.");
	}
}

RESQML2_NS::IjkGridParametricRepresentation* DataObjectRepository::createIjkGridParametricRepresentation(const std::string & guid, const std::string & title,
	unsigned int iCount, unsigned int jCount, unsigned int kCount)
{
	switch (defaultResqmlVersion) {
	case EnergisticsStandard::RESQML2_0_1: return new RESQML2_0_1_NS::IjkGridParametricRepresentation(this, guid, title, iCount, jCount, kCount);
	case EnergisticsStandard::RESQML2_2: return new RESQML2_2_NS::IjkGridParametricRepresentation(this, guid, title, iCount, jCount, kCount);
	default: throw std::logic_error("The RESQML version is not supported.");
	}
}

RESQML2_NS::IjkGridParametricRepresentation* DataObjectRepository::createIjkGridParametricRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp,
	const std::string & guid, const std::string & title,
	unsigned int iCount, unsigned int jCount, unsigned int kCount)
{
	switch (defaultResqmlVersion) {
	case EnergisticsStandard::RESQML2_0_1: return new RESQML2_0_1_NS::IjkGridParametricRepresentation(interp, guid, title, iCount, jCount, kCount);
	case EnergisticsStandard::RESQML2_2: return new RESQML2_2_NS::IjkGridParametricRepresentation(interp, guid, title, iCount, jCount, kCount);
	default: throw std::logic_error("The RESQML version is not supported.");
	}
}

RESQML2_NS::IjkGridLatticeRepresentation* DataObjectRepository::createIjkGridLatticeRepresentation(const std::string & guid, const std::string & title,
	unsigned int iCount, unsigned int jCount, unsigned int kCount)
{
	switch (defaultResqmlVersion) {
	case EnergisticsStandard::RESQML2_0_1: return new RESQML2_0_1_NS::IjkGridLatticeRepresentation(this, guid, title, iCount, jCount, kCount);
	case EnergisticsStandard::RESQML2_2: return new RESQML2_2_NS::IjkGridLatticeRepresentation(this, guid, title, iCount, jCount, kCount);
	default: throw std::logic_error("The RESQML version is not supported.");
	}
}

RESQML2_NS::IjkGridLatticeRepresentation* DataObjectRepository::createIjkGridLatticeRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp,
	const std::string & guid, const std::string & title,
	unsigned int iCount, unsigned int jCount, unsigned int kCount)
{
	switch (defaultResqmlVersion) {
	case EnergisticsStandard::RESQML2_0_1: return new RESQML2_0_1_NS::IjkGridLatticeRepresentation(interp, guid, title, iCount, jCount, kCount);
	case EnergisticsStandard::RESQML2_2: return new RESQML2_2_NS::IjkGridLatticeRepresentation(interp, guid, title, iCount, jCount, kCount);
	default: throw std::logic_error("The RESQML version is not supported.");
	}
}

RESQML2_NS::IjkGridNoGeometryRepresentation* DataObjectRepository::createIjkGridNoGeometryRepresentation(
	const std::string & guid, const std::string & title,
	unsigned int iCount, unsigned int jCount, unsigned int kCount)
{
	switch (defaultResqmlVersion) {
	case EnergisticsStandard::RESQML2_0_1: return new RESQML2_0_1_NS::IjkGridNoGeometryRepresentation(this, guid, title, iCount, jCount, kCount);
	case EnergisticsStandard::RESQML2_2: return new RESQML2_2_NS::IjkGridNoGeometryRepresentation(this, guid, title, iCount, jCount, kCount);
	default: throw std::logic_error("The RESQML version is not supported.");
	}
}

RESQML2_NS::IjkGridNoGeometryRepresentation* DataObjectRepository::createIjkGridNoGeometryRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp,
	const std::string & guid, const std::string & title,
	unsigned int iCount, unsigned int jCount, unsigned int kCount)
{
	switch (defaultResqmlVersion) {
	case EnergisticsStandard::RESQML2_0_1: return new RESQML2_0_1_NS::IjkGridNoGeometryRepresentation(interp, guid, title, iCount, jCount, kCount);
	case EnergisticsStandard::RESQML2_2: return new RESQML2_2_NS::IjkGridNoGeometryRepresentation(interp, guid, title, iCount, jCount, kCount);
	default: throw std::logic_error("The RESQML version is not supported.");
	}
}

RESQML2_NS::UnstructuredGridRepresentation* DataObjectRepository::createUnstructuredGridRepresentation(const std::string & guid, const std::string & title,
	const ULONG64 & cellCount)
{
	switch (defaultResqmlVersion) {
	case EnergisticsStandard::RESQML2_0_1: return new RESQML2_0_1_NS::UnstructuredGridRepresentation(this, guid, title, cellCount);
	case EnergisticsStandard::RESQML2_2: return new RESQML2_2_NS::UnstructuredGridRepresentation(this, guid, title, cellCount);
	default: throw std::logic_error("The RESQML version is not supported.");
	}
}

RESQML2_NS::SubRepresentation* DataObjectRepository::createSubRepresentation(const std::string & guid, const std::string & title)
{
	return new SubRepresentation(this, guid, title);
}

RESQML2_NS::SubRepresentation* DataObjectRepository::createSubRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp,
	const std::string & guid, const std::string & title)
{
	return new SubRepresentation(interp, guid, title);
}

RESQML2_NS::GridConnectionSetRepresentation* DataObjectRepository::createGridConnectionSetRepresentation(const std::string & guid, const std::string & title)
{
	return new GridConnectionSetRepresentation(this, guid, title);
}

RESQML2_NS::GridConnectionSetRepresentation* DataObjectRepository::createGridConnectionSetRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp,
	const std::string & guid, const std::string & title)
{
	return new GridConnectionSetRepresentation(interp, guid, title);
}

//************************************
//************* PROPERTIES ***********
//************************************

RESQML2_NS::TimeSeries* DataObjectRepository::createTimeSeries(const std::string & guid, const std::string & title)
{
	return new RESQML2_0_1_NS::TimeSeries(this, guid, title);
}

RESQML2_NS::StringTableLookup* DataObjectRepository::createStringTableLookup(const std::string & guid, const std::string & title)
{
	return new RESQML2_0_1_NS::StringTableLookup(this, guid, title);
}

RESQML2_0_1_NS::PropertyKind* DataObjectRepository::createPropertyKind201(const std::string & guid, const std::string & title,
	const std::string & namingSystem, const gsoap_resqml2_0_1::resqml20__ResqmlUom & uom, const gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind & parentEnergisticsPropertyKind)
{
	return new RESQML2_0_1_NS::PropertyKind(this, guid, title, namingSystem, uom, parentEnergisticsPropertyKind);
}

COMMON_NS::PropertyKind* DataObjectRepository::createPropertyKind(const std::string & guid, const std::string & title,
	const std::string & namingSystem, const gsoap_resqml2_0_1::resqml20__ResqmlUom & uom, COMMON_NS::PropertyKind * parentPropType)
{
	return new RESQML2_0_1_NS::PropertyKind(guid, title, namingSystem, uom, parentPropType);
}

RESQML2_0_1_NS::PropertyKind* DataObjectRepository::createPropertyKind201(const std::string & guid, const std::string & title,
	const std::string & namingSystem, const std::string & nonStandardUom, const gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind & parentEnergisticsPropertyKind)
{
	return new RESQML2_0_1_NS::PropertyKind(this, guid, title, namingSystem, nonStandardUom, parentEnergisticsPropertyKind);
}

COMMON_NS::PropertyKind* DataObjectRepository::createPropertyKind(const std::string & guid, const std::string & title,
	const std::string & namingSystem, const std::string & nonStandardUom, COMMON_NS::PropertyKind * parentPropType)
{
	return new RESQML2_0_1_NS::PropertyKind(guid, title, namingSystem, nonStandardUom, parentPropType);
}

COMMON_NS::PropertyKind* DataObjectRepository::createPropertyKind(const std::string & guid, const std::string & title,
	gsoap_eml2_1::eml21__QuantityClassKind quantityClass, bool isAbstract, COMMON_NS::PropertyKind* parentPropertyKind)
{
	return new WITSML2_0_NS::PropertyKind(this, guid, title, quantityClass, isAbstract, parentPropertyKind);
}

RESQML2_NS::PropertySet* DataObjectRepository::createPropertySet(const std::string & guid, const std::string & title,
	bool hasMultipleRealizations, bool hasSinglePropertyKind, gsoap_resqml2_0_1::resqml20__TimeSetKind timeSetKind)
{
	return new RESQML2_0_1_NS::PropertySet(this, guid, title, hasMultipleRealizations, hasSinglePropertyKind, timeSetKind);
}

RESQML2_0_1_NS::CommentProperty* DataObjectRepository::createCommentProperty201(RESQML2_NS::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
	unsigned int dimension, gsoap_eml2_2::resqml22__IndexableElement attachmentKind, gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind energisticsPropertyKind)
{
	return new RESQML2_0_1_NS::CommentProperty(rep, guid, title, dimension, attachmentKind, energisticsPropertyKind);
}

RESQML2_NS::CommentProperty* DataObjectRepository::createCommentProperty(RESQML2_NS::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
	unsigned int dimension, gsoap_eml2_2::resqml22__IndexableElement attachmentKind, COMMON_NS::PropertyKind * localPropType)
{
	switch (defaultResqmlVersion) {
	case DataObjectRepository::EnergisticsStandard::RESQML2_0_1:
		return new RESQML2_0_1_NS::CommentProperty(rep, guid, title, dimension, attachmentKind, localPropType);
	case DataObjectRepository::EnergisticsStandard::RESQML2_2:
		return new RESQML2_2_NS::CommentProperty(rep, guid, title, dimension, attachmentKind, localPropType);
	default:
		throw std::invalid_argument("Unrecognized Energistics standard.");
	}
}

RESQML2_0_1_NS::ContinuousProperty* DataObjectRepository::createContinuousProperty201(RESQML2_NS::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
	unsigned int dimension, gsoap_eml2_2::resqml22__IndexableElement attachmentKind, gsoap_resqml2_0_1::resqml20__ResqmlUom uom, gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind energisticsPropertyKind)
{
	return new RESQML2_0_1_NS::ContinuousProperty(rep, guid, title, dimension, attachmentKind, uom, energisticsPropertyKind);
}

RESQML2_NS::ContinuousProperty* DataObjectRepository::createContinuousProperty(RESQML2_NS::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
	unsigned int dimension, gsoap_eml2_2::resqml22__IndexableElement attachmentKind, gsoap_resqml2_0_1::resqml20__ResqmlUom uom, COMMON_NS::PropertyKind * localPropType)
{
	switch (defaultResqmlVersion) {
	case DataObjectRepository::EnergisticsStandard::RESQML2_0_1:
		return new RESQML2_0_1_NS::ContinuousProperty(rep, guid, title, dimension, attachmentKind, uom, localPropType);
	case DataObjectRepository::EnergisticsStandard::RESQML2_2:
		return new RESQML2_2_NS::ContinuousProperty(rep, guid, title, dimension, attachmentKind, uom, localPropType);
	default:
		throw std::invalid_argument("Unrecognized Energistics standard.");
	}
}

RESQML2_0_1_NS::ContinuousProperty* DataObjectRepository::createContinuousProperty201(RESQML2_NS::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
	unsigned int dimension, gsoap_eml2_2::resqml22__IndexableElement attachmentKind, std::string nonStandardUom, gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind energisticsPropertyKind)
{
	return new RESQML2_0_1_NS::ContinuousProperty(rep, guid, title, dimension, attachmentKind, nonStandardUom, energisticsPropertyKind);
}

RESQML2_NS::ContinuousProperty* DataObjectRepository::createContinuousProperty(RESQML2_NS::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
	unsigned int dimension, gsoap_eml2_2::resqml22__IndexableElement attachmentKind, const std::string & nonStandardUom, COMMON_NS::PropertyKind * localPropType)
{
	switch (defaultResqmlVersion) {
	case DataObjectRepository::EnergisticsStandard::RESQML2_0_1:
		return new RESQML2_0_1_NS::ContinuousProperty(rep, guid, title, dimension, attachmentKind, nonStandardUom, localPropType);
	case DataObjectRepository::EnergisticsStandard::RESQML2_2:
		return new RESQML2_2_NS::ContinuousProperty(rep, guid, title, dimension, attachmentKind, nonStandardUom, localPropType);
	default:
		throw std::invalid_argument("Unrecognized Energistics standard.");
	}
}

RESQML2_0_1_NS::DiscreteProperty* DataObjectRepository::createDiscreteProperty201(RESQML2_NS::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
	unsigned int dimension, gsoap_eml2_2::resqml22__IndexableElement attachmentKind, gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind energisticsPropertyKind)
{
	return new RESQML2_0_1_NS::DiscreteProperty(rep, guid, title, dimension, attachmentKind, energisticsPropertyKind);
}

RESQML2_NS::DiscreteProperty* DataObjectRepository::createDiscreteProperty(RESQML2_NS::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
	unsigned int dimension, gsoap_eml2_2::resqml22__IndexableElement attachmentKind, COMMON_NS::PropertyKind * localPropType)
{
	switch (defaultResqmlVersion) {
	case DataObjectRepository::EnergisticsStandard::RESQML2_0_1:
		return new RESQML2_0_1_NS::DiscreteProperty(rep, guid, title, dimension, attachmentKind, localPropType);
	case DataObjectRepository::EnergisticsStandard::RESQML2_2:
		return new RESQML2_2_NS::DiscreteProperty(rep, guid, title, dimension, attachmentKind, localPropType);
	default:
		throw std::invalid_argument("Unrecognized Energistics standard.");
	}
}

RESQML2_0_1_NS::CategoricalProperty* DataObjectRepository::createCategoricalProperty201(RESQML2_NS::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
	unsigned int dimension, gsoap_eml2_2::resqml22__IndexableElement attachmentKind,
	RESQML2_NS::StringTableLookup* strLookup, gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind energisticsPropertyKind)
{
	return new RESQML2_0_1_NS::CategoricalProperty(rep, guid, title, dimension, attachmentKind, strLookup, energisticsPropertyKind);
}

RESQML2_NS::CategoricalProperty* DataObjectRepository::createCategoricalProperty(RESQML2_NS::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
	unsigned int dimension, gsoap_eml2_2::resqml22__IndexableElement attachmentKind,
	RESQML2_NS::StringTableLookup* strLookup, COMMON_NS::PropertyKind * localPropType)
{
	switch (defaultResqmlVersion) {
	case DataObjectRepository::EnergisticsStandard::RESQML2_0_1:
		return new RESQML2_0_1_NS::CategoricalProperty(rep, guid, title, dimension, attachmentKind, strLookup, localPropType);
	case DataObjectRepository::EnergisticsStandard::RESQML2_2:
		return new RESQML2_2_NS::CategoricalProperty(rep, guid, title, dimension, attachmentKind, strLookup, localPropType);
	default:
		throw std::invalid_argument("Unrecognized Energistics standard.");
	}
}

//************************************
//************* ACTIVITIES ***********
//************************************

RESQML2_NS::ActivityTemplate* DataObjectRepository::createActivityTemplate(const std::string & guid, const std::string & title)
{
	return new ActivityTemplate(this, guid, title);
}

RESQML2_NS::Activity* DataObjectRepository::createActivity(RESQML2_NS::ActivityTemplate* activityTemplate, const std::string & guid, const std::string & title)
{
	return new Activity(activityTemplate, guid, title);
}

//************************************
//*************** WITSML *************
//************************************

WITSML2_0_NS::Well* DataObjectRepository::createWell(const std::string & guid,
	const std::string & title)
{
	return new Well(this, guid, title);
}

WITSML2_0_NS::Well* DataObjectRepository::createWell(const std::string & guid,
	const std::string & title,
	const std::string & operator_,
	gsoap_eml2_1::eml21__WellStatus statusWell,
	gsoap_eml2_1::witsml20__WellDirection directionWell)
{
	return new Well(this, guid, title, operator_, statusWell, directionWell);
}

WITSML2_0_NS::Wellbore* DataObjectRepository::createWellbore(WITSML2_0_NS::Well* witsmlWell,
	const std::string & guid,
	const std::string & title)
{
	return new Wellbore(witsmlWell, guid, title);
}

WITSML2_0_NS::Wellbore* DataObjectRepository::createWellbore(WITSML2_0_NS::Well* witsmlWell,
	const std::string & guid,
	const std::string & title,
	gsoap_eml2_1::eml21__WellStatus statusWellbore,
	bool isActive,
	bool achievedTD)
{
	return new Wellbore(witsmlWell, guid, title, statusWellbore, isActive, achievedTD);
}

WITSML2_0_NS::WellCompletion* DataObjectRepository::createWellCompletion(WITSML2_0_NS::Well* witsmlWell,
	const std::string & guid,
	const std::string & title)
{
	return new WellCompletion(witsmlWell, guid, title);
}

WITSML2_0_NS::WellboreCompletion* DataObjectRepository::createWellboreCompletion(WITSML2_0_NS::Wellbore* witsmlWellbore,
	WITSML2_0_NS::WellCompletion* wellCompletion,
	const std::string & guid,
	const std::string & title,
	const std::string & wellCompletionName)
{
	return new WellboreCompletion(witsmlWellbore, wellCompletion, guid, title, wellCompletionName);
}

WITSML2_0_NS::WellboreGeometry* DataObjectRepository::createWellboreGeometry(WITSML2_0_NS::Wellbore* witsmlWellbore,
	const std::string & guid,
	const std::string & title,
	gsoap_eml2_1::witsml20__ChannelStatus channelStatus)
{
	return new WellboreGeometry(witsmlWellbore, guid, title, channelStatus);
}

WITSML2_0_NS::Trajectory* DataObjectRepository::createTrajectory(WITSML2_0_NS::Wellbore* witsmlWellbore,
	const std::string & guid,
	const std::string & title,
	gsoap_eml2_1::witsml20__ChannelStatus channelStatus)
{
	return new WITSML2_0_NS::Trajectory(witsmlWellbore, guid, title, channelStatus);
}

WITSML2_0_NS::Log* DataObjectRepository::createLog(WITSML2_0_NS::Wellbore* witsmlWellbore,
	const std::string & guid,
	const std::string & title)
{
	return new WITSML2_0_NS::Log(witsmlWellbore, guid, title);
}

WITSML2_0_NS::ChannelSet* DataObjectRepository::createChannelSet(const std::string & guid, const std::string & title)
{
	return new WITSML2_0_NS::ChannelSet(this, guid, title);
}

WITSML2_0_NS::Channel* DataObjectRepository::createChannel(COMMON_NS::PropertyKind * propertyKind,
	const std::string & guid, const std::string & title,
	const std::string & mnemonic, gsoap_eml2_1::eml21__UnitOfMeasure uom, gsoap_eml2_1::witsml20__EtpDataType dataType, gsoap_eml2_1::witsml20__ChannelStatus growingStatus,
	const std::string & timeDepth, const std::string & loggingCompanyName)
{
	return new WITSML2_0_NS::Channel(propertyKind,
		guid, title,
		mnemonic, uom, dataType, growingStatus,
		timeDepth, loggingCompanyName);
}

//************************************
//*************** PRODML *************
//************************************

PRODML2_1_NS::FluidSystem* DataObjectRepository::createFluidSystem(const std::string & guid,
	const std::string & title,
	double temperatureValue, gsoap_eml2_2::eml22__ThermodynamicTemperatureUom temperatureUom,
	double pressureValue, gsoap_eml2_2::eml22__PressureUom pressureUom,
	gsoap_eml2_2::prodml21__ReservoirFluidKind reservoirFluidKind,
	double gasOilRatio, gsoap_eml2_2::eml22__VolumePerVolumeUom gasOilRatioUom)
{
	return new PRODML2_1_NS::FluidSystem(this,
		guid, title,
		temperatureValue, temperatureUom,
		pressureValue, pressureUom,
		reservoirFluidKind,
		gasOilRatio, gasOilRatioUom);
}

PRODML2_1_NS::FluidCharacterization* DataObjectRepository::createFluidCharacterization(const std::string & guid, const std::string & title)
{
	return new PRODML2_1_NS::FluidCharacterization(this, guid, title);
}

COMMON_NS::GraphicalInformationSet* DataObjectRepository::createGraphicalInformationSet(const std::string & guid, const std::string & title)
{
	return new COMMON_NS::GraphicalInformationSet(this, guid, title);
}

RESQML2_2_NS::DiscreteColorMap* DataObjectRepository::createDiscreteColorMap(const std::string& guid, const std::string& title)
{
	return new RESQML2_2_NS::DiscreteColorMap(this, guid, title);
}

RESQML2_2_NS::ContinuousColorMap* DataObjectRepository::createContinuousColorMap(const std::string& guid, const std::string& title,
	gsoap_eml2_2::resqml22__InterpolationDomain interpolationDomain, gsoap_eml2_2::resqml22__InterpolationMethod interpolationMethod)
{
	return new RESQML2_2_NS::ContinuousColorMap(this, guid, title, interpolationDomain, interpolationMethod);
}

std::vector<RESQML2_0_1_NS::LocalDepth3dCrs*> DataObjectRepository::getLocalDepth3dCrsSet() const { return getDataObjects<RESQML2_0_1_NS::LocalDepth3dCrs>(); }

std::vector<RESQML2_0_1_NS::LocalTime3dCrs*> DataObjectRepository::getLocalTime3dCrsSet() const { return getDataObjects<RESQML2_0_1_NS::LocalTime3dCrs>(); }

std::vector<RESQML2_0_1_NS::StratigraphicColumn*> DataObjectRepository::getStratigraphicColumnSet() const { return getDataObjects<RESQML2_0_1_NS::StratigraphicColumn>(); }

namespace {
	bool isAFracture(RESQML2_0_1_NS::TectonicBoundaryFeature* tbf) { return tbf->isAFracture(); }
}

std::vector<RESQML2_0_1_NS::TectonicBoundaryFeature*> DataObjectRepository::getFaultSet() const
{
	std::vector<RESQML2_0_1_NS::TectonicBoundaryFeature*> result = getDataObjects<RESQML2_0_1_NS::TectonicBoundaryFeature>();

	result.erase(std::remove_if(result.begin(), result.end(), isAFracture), result.end());

	return result;
}

std::vector<RESQML2_0_1_NS::TectonicBoundaryFeature*> DataObjectRepository::getFractureSet() const
{
	std::vector<RESQML2_0_1_NS::TectonicBoundaryFeature*> result = getDataObjects<RESQML2_0_1_NS::TectonicBoundaryFeature>();

	result.erase(std::remove_if(result.begin(), result.end(), std::not1(std::ptr_fun(isAFracture))), result.end());

	return result;
}

vector<PolylineSetRepresentation *> DataObjectRepository::getFaultPolylineSetRepSet() const
{
	const std::vector<RESQML2_0_1_NS::TectonicBoundaryFeature*> faultSet = getFaultSet();

	vector<PolylineSetRepresentation *> result;

	for (size_t featureIndex = 0; featureIndex < faultSet.size(); ++featureIndex) {
		const vector<RESQML2_NS::AbstractFeatureInterpretation *> interpSet = faultSet[featureIndex]->getInterpretationSet();
		for (size_t interpIndex = 0; interpIndex < interpSet.size(); ++interpIndex) {
			const vector<RESQML2_NS::AbstractRepresentation *> repSet = interpSet[interpIndex]->getRepresentationSet();
			for (size_t repIndex = 0; repIndex < repSet.size(); ++repIndex) {
				if (repSet[repIndex]->getGsoapType() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__obj_USCOREPolylineSetRepresentation) {
					result.push_back(static_cast<PolylineSetRepresentation *>(repSet[repIndex]));
				}
			}
		}
	}

	return result;
}

vector<PolylineSetRepresentation *> DataObjectRepository::getFracturePolylineSetRepSet() const
{
	const std::vector<RESQML2_0_1_NS::TectonicBoundaryFeature*> fractureSet = getFractureSet();

	vector<PolylineSetRepresentation *> result;

	for (size_t featureIndex = 0; featureIndex < fractureSet.size(); ++featureIndex) {
		const vector<RESQML2_NS::AbstractFeatureInterpretation *> interpSet = fractureSet[featureIndex]->getInterpretationSet();
		for (size_t interpIndex = 0; interpIndex < interpSet.size(); ++interpIndex) {
			const vector<RESQML2_NS::AbstractRepresentation *> repSet = interpSet[interpIndex]->getRepresentationSet();
			for (size_t repIndex = 0; repIndex < repSet.size(); ++repIndex) {
				if (repSet[repIndex]->getGsoapType() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__obj_USCOREPolylineSetRepresentation) {
					result.push_back(static_cast<PolylineSetRepresentation *>(repSet[repIndex]));
				}
			}
		}
	}

	return result;
}

vector<PolylineSetRepresentation *> DataObjectRepository::getFrontierPolylineSetRepSet() const
{
	const std::vector<RESQML2_0_1_NS::FrontierFeature*> frontierSet = getFrontierSet();

	vector<PolylineSetRepresentation *> result;

	for (size_t featureIndex = 0; featureIndex < frontierSet.size(); ++featureIndex) {
		const vector<RESQML2_NS::AbstractFeatureInterpretation *> interpSet = frontierSet[featureIndex]->getInterpretationSet();
		for (size_t interpIndex = 0; interpIndex < interpSet.size(); ++interpIndex) {
			const vector<RESQML2_NS::AbstractRepresentation *> repSet = interpSet[interpIndex]->getRepresentationSet();
			for (size_t repIndex = 0; repIndex < repSet.size(); ++repIndex) {
				if (repSet[repIndex]->getGsoapType() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__obj_USCOREPolylineSetRepresentation) {
					result.push_back(static_cast<PolylineSetRepresentation *>(repSet[repIndex]));
				}
			}
		}
	}

	return result;
}

vector<TriangulatedSetRepresentation *> DataObjectRepository::getFaultTriangulatedSetRepSet() const
{
	const std::vector<RESQML2_0_1_NS::TectonicBoundaryFeature*> faultSet = getFaultSet();
	vector<TriangulatedSetRepresentation *> result;

	for (size_t featureIndex = 0; featureIndex < faultSet.size(); ++featureIndex) {
		const vector<RESQML2_NS::AbstractFeatureInterpretation *> interpSet = faultSet[featureIndex]->getInterpretationSet();
		for (size_t interpIndex = 0; interpIndex < interpSet.size(); ++interpIndex) {
			const vector<RESQML2_NS::AbstractRepresentation *> repSet = interpSet[interpIndex]->getRepresentationSet();
			for (size_t repIndex = 0; repIndex < repSet.size(); ++repIndex) {
				if (repSet[repIndex]->getGsoapType() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__obj_USCORETriangulatedSetRepresentation) {
					result.push_back(static_cast<TriangulatedSetRepresentation *>(repSet[repIndex]));
				}
			}
		}
	}

	return result;
}

vector<TriangulatedSetRepresentation *> DataObjectRepository::getFractureTriangulatedSetRepSet() const
{
	const std::vector<RESQML2_0_1_NS::TectonicBoundaryFeature*> fractureSet = getFractureSet();

	vector<TriangulatedSetRepresentation *> result;

	for (size_t featureIndex = 0; featureIndex < fractureSet.size(); ++featureIndex) {
		const vector<RESQML2_NS::AbstractFeatureInterpretation *> interpSet = fractureSet[featureIndex]->getInterpretationSet();
		for (size_t interpIndex = 0; interpIndex < interpSet.size(); ++interpIndex) {
			const vector<RESQML2_NS::AbstractRepresentation *> repSet = interpSet[interpIndex]->getRepresentationSet();
			for (size_t repIndex = 0; repIndex < repSet.size(); ++repIndex) {
				if (repSet[repIndex]->getGsoapType() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__obj_USCORETriangulatedSetRepresentation) {
					result.push_back(static_cast<TriangulatedSetRepresentation *>(repSet[repIndex]));
				}
			}
		}
	}

	return result;
}

std::vector<RESQML2_0_1_NS::Horizon*> DataObjectRepository::getHorizonSet() const
{
	std::vector<RESQML2_0_1_NS::Horizon*> result;

	const std::vector<RESQML2_0_1_NS::GeneticBoundaryFeature*> geneticBoundarySet = getDataObjects<RESQML2_0_1_NS::GeneticBoundaryFeature>();

	for (size_t i = 0; i < geneticBoundarySet.size(); ++i) {
		if (geneticBoundarySet[i]->isAnHorizon()) {
			result.push_back(static_cast<RESQML2_0_1_NS::Horizon*>(geneticBoundarySet[i]));
		}
	}

	return result;
}

namespace {
	bool isAnHorizon(RESQML2_0_1_NS::GeneticBoundaryFeature* gbf) { return gbf->isAnHorizon(); }
}

std::vector<RESQML2_0_1_NS::GeneticBoundaryFeature*> DataObjectRepository::getGeobodyBoundarySet() const
{
	std::vector<RESQML2_0_1_NS::GeneticBoundaryFeature*> result = getDataObjects<RESQML2_0_1_NS::GeneticBoundaryFeature>();

	result.erase(std::remove_if(result.begin(), result.end(), isAnHorizon), result.end());

	return result;
}

unsigned int DataObjectRepository::getGeobodyBoundaryCount() const
{
	size_t result = getGeobodyBoundarySet().size();

	if (result > (std::numeric_limits<unsigned int>::max)()) {
		throw out_of_range("The geobody boundary count is superior to unsigned int max");
	}
	return static_cast<unsigned int>(result);
}

RESQML2_0_1_NS::GeneticBoundaryFeature* DataObjectRepository::getGeobodyBoundary(unsigned int index) const
{
	std::vector<RESQML2_0_1_NS::GeneticBoundaryFeature*> allgb = getGeobodyBoundarySet();

	if (index >= allgb.size()) {
		throw out_of_range("The index of the geobody boundary is out of range");
	}

	return allgb[index];
}

std::vector<RESQML2_0_1_NS::GeobodyFeature*> DataObjectRepository::getGeobodySet() const { return getDataObjects<RESQML2_0_1_NS::GeobodyFeature>(); }

vector<Grid2dRepresentation *> DataObjectRepository::getHorizonGrid2dRepSet() const
{
	vector<Grid2dRepresentation *> result;

	const vector<Horizon*> horizonSet = getHorizonSet();
	for (size_t featureIndex = 0; featureIndex < horizonSet.size(); ++featureIndex) {
		const vector<RESQML2_NS::AbstractFeatureInterpretation *> interpSet = horizonSet[featureIndex]->getInterpretationSet();
		for (size_t interpIndex = 0; interpIndex < interpSet.size(); ++interpIndex) {
			const vector<RESQML2_NS::AbstractRepresentation *> repSet = interpSet[interpIndex]->getRepresentationSet();
			for (size_t repIndex = 0; repIndex < repSet.size(); ++repIndex) {
				if (repSet[repIndex]->getGsoapType() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__obj_USCOREGrid2dRepresentation) {
					result.push_back(static_cast<Grid2dRepresentation *>(repSet[repIndex]));
				}
			}
		}
	}

	return result;
}

std::vector<PolylineRepresentation *> DataObjectRepository::getHorizonPolylineRepSet() const
{
	vector<PolylineRepresentation *> result;

	const vector<Horizon*> horizonSet = getHorizonSet();
	for (size_t featureIndex = 0; featureIndex < horizonSet.size(); ++featureIndex) {
		const vector<RESQML2_NS::AbstractFeatureInterpretation *> interpSet = horizonSet[featureIndex]->getInterpretationSet();
		for (size_t interpIndex = 0; interpIndex < interpSet.size(); ++interpIndex) {
			const vector<RESQML2_NS::AbstractRepresentation *> repSet = interpSet[interpIndex]->getRepresentationSet();
			for (size_t repIndex = 0; repIndex < repSet.size(); ++repIndex) {
				if (repSet[repIndex]->getGsoapType() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__obj_USCOREPolylineRepresentation) {
					result.push_back(static_cast<PolylineRepresentation *>(repSet[repIndex]));
				}
			}
		}
	}

	return result;
}

std::vector<PolylineSetRepresentation *> DataObjectRepository::getHorizonPolylineSetRepSet() const
{
	vector<PolylineSetRepresentation *> result;

	const vector<Horizon*> horizonSet = getHorizonSet();
	for (size_t featureIndex = 0; featureIndex < horizonSet.size(); ++featureIndex) {
		const vector<RESQML2_NS::AbstractFeatureInterpretation *> interpSet = horizonSet[featureIndex]->getInterpretationSet();
		for (size_t interpIndex = 0; interpIndex < interpSet.size(); ++interpIndex) {
			const vector<RESQML2_NS::AbstractRepresentation *> repSet = interpSet[interpIndex]->getRepresentationSet();
			for (size_t repIndex = 0; repIndex < repSet.size(); ++repIndex) {
				if (repSet[repIndex]->getGsoapType() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__obj_USCOREPolylineSetRepresentation) {
					result.push_back(static_cast<PolylineSetRepresentation *>(repSet[repIndex]));
				}
			}
		}
	}

	return result;
}

vector<TriangulatedSetRepresentation *> DataObjectRepository::getHorizonTriangulatedSetRepSet() const
{
	vector<TriangulatedSetRepresentation *> result;

	const vector<Horizon*> horizonSet = getHorizonSet();
	for (size_t featureIndex = 0; featureIndex < horizonSet.size(); ++featureIndex) {
		const vector<RESQML2_NS::AbstractFeatureInterpretation *> interpSet = horizonSet[featureIndex]->getInterpretationSet();
		for (size_t interpIndex = 0; interpIndex < interpSet.size(); ++interpIndex) {
			const vector<RESQML2_NS::AbstractRepresentation *> repSet = interpSet[interpIndex]->getRepresentationSet();
			for (size_t repIndex = 0; repIndex < repSet.size(); ++repIndex) {
				if (repSet[repIndex]->getGsoapType() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__obj_USCORETriangulatedSetRepresentation) {
					result.push_back(static_cast<TriangulatedSetRepresentation *>(repSet[repIndex]));
				}
			}
		}
	}

	return result;
}

std::vector<RESQML2_0_1_NS::TriangulatedSetRepresentation*> DataObjectRepository::getAllTriangulatedSetRepSet() const { return getDataObjects<RESQML2_0_1_NS::TriangulatedSetRepresentation>(); }

std::vector<RESQML2_0_1_NS::Grid2dRepresentation*> DataObjectRepository::getAllGrid2dRepresentationSet() const { return getDataObjects<RESQML2_0_1_NS::Grid2dRepresentation>(); }

std::vector<RESQML2_0_1_NS::PolylineSetRepresentation*> DataObjectRepository::getAllPolylineSetRepSet() const { return getDataObjects<RESQML2_0_1_NS::PolylineSetRepresentation>(); }

namespace {
	bool isClassified(RESQML2_0_1_NS::TriangulatedSetRepresentation* tsr) {
		RESQML2_NS::AbstractFeatureInterpretation const * const interp = tsr->getInterpretation();
		if (interp == nullptr) {
			return false;
		}

		if (!interp->isPartial()) {
			const int soapType = interp->getGsoapType();
			if (soapType != SOAP_TYPE_gsoap_resqml2_0_1_resqml20__obj_USCOREFaultInterpretation &&
				soapType != SOAP_TYPE_gsoap_resqml2_0_1_resqml20__obj_USCOREHorizonInterpretation) {
				return false;
			}
		}
		else {
			const std::string contentType = tsr->getInterpretationDor().getContentType();
			if (contentType.find("Horizon") == string::npos &&
				contentType.find("Fault") == string::npos) {
				return false;
			}
		}

		return true;
	}
}

std::vector<RESQML2_0_1_NS::TriangulatedSetRepresentation*> DataObjectRepository::getUnclassifiedTriangulatedSetRepSet() const
{
	std::vector<RESQML2_0_1_NS::TriangulatedSetRepresentation*> result = getDataObjects<RESQML2_0_1_NS::TriangulatedSetRepresentation>();

	result.erase(std::remove_if(result.begin(), result.end(), isClassified), result.end());

	return result;
}

std::vector<RESQML2_0_1_NS::SeismicLineFeature*> DataObjectRepository::getSeismicLineSet() const { return getDataObjects<RESQML2_0_1_NS::SeismicLineFeature>(); }

std::vector<RESQML2_NS::WellboreFeature*> DataObjectRepository::getWellboreSet() const { return getDataObjects<RESQML2_NS::WellboreFeature>(); }

vector<RESQML2_NS::WellboreTrajectoryRepresentation *> DataObjectRepository::getWellboreTrajectoryRepresentationSet() const
{
	vector<RESQML2_NS::WellboreTrajectoryRepresentation *> result;

	const std::vector<RESQML2_NS::WellboreFeature*> wellboreSet = getWellboreSet();

	for (size_t featureIndex = 0; featureIndex < wellboreSet.size(); ++featureIndex) {
		const std::vector<RESQML2_NS::AbstractFeatureInterpretation *> interpSet = wellboreSet[featureIndex]->getInterpretationSet();
		for (size_t interpIndex = 0; interpIndex < interpSet.size(); ++interpIndex) {
			const std::vector<RESQML2_NS::AbstractRepresentation *> repSet = interpSet[interpIndex]->getRepresentationSet();
			for (size_t repIndex = 0; repIndex < repSet.size(); ++repIndex) {
				if (repSet[repIndex]->getGsoapType() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__obj_USCOREWellboreTrajectoryRepresentation) {
					result.push_back(static_cast<WellboreTrajectoryRepresentation *>(repSet[repIndex]));
				}
			}
		}
	}

	return result;
}

vector<RESQML2_NS::DeviationSurveyRepresentation *> DataObjectRepository::getDeviationSurveyRepresentationSet() const
{
	vector<RESQML2_NS::DeviationSurveyRepresentation *> result;

	const std::vector<RESQML2_NS::WellboreFeature*> wellboreSet = getWellboreSet();

	for (size_t featureIndex = 0; featureIndex < wellboreSet.size(); ++featureIndex) {
		const std::vector<RESQML2_NS::AbstractFeatureInterpretation *> interpSet = wellboreSet[featureIndex]->getInterpretationSet();
		for (size_t interpIndex = 0; interpIndex < interpSet.size(); ++interpIndex) {
			const std::vector<RESQML2_NS::AbstractRepresentation *> repSet = interpSet[interpIndex]->getRepresentationSet();
			for (size_t repIndex = 0; repIndex < repSet.size(); ++repIndex) {
				if (repSet[repIndex]->getGsoapType() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__obj_USCOREDeviationSurveyRepresentation) {
					result.push_back(static_cast<DeviationSurveyRepresentation *>(repSet[repIndex]));
				}
			}
		}
	}

	return result;
}

std::vector<RESQML2_NS::RepresentationSetRepresentation*> DataObjectRepository::getRepresentationSetRepresentationSet() const { return getDataObjects<RESQML2_NS::RepresentationSetRepresentation>(); }

unsigned int DataObjectRepository::getRepresentationSetRepresentationCount() const
{
	const size_t result = getDataObjects<RESQML2_NS::RepresentationSetRepresentation>().size();

	if (result > (std::numeric_limits<unsigned int>::max)()) {
		throw out_of_range("The RepresentationSetRepresentation count is superior to unsigned int max");
	}
	return static_cast<unsigned int>(result);
}

RESQML2_NS::RepresentationSetRepresentation* DataObjectRepository::getRepresentationSetRepresentation(unsigned int index) const
{
	const std::vector<RESQML2_NS::RepresentationSetRepresentation*> result = getDataObjects<RESQML2_NS::RepresentationSetRepresentation>();

	if (index >= result.size()) {
		throw out_of_range("The index of the representation set representation is out of range");
	}

	return result[index];
}

std::vector<RESQML2_0_1_NS::PolylineRepresentation*> DataObjectRepository::getAllPolylineRepresentationSet() const { return getDataObjects<RESQML2_0_1_NS::PolylineRepresentation>(); }

namespace {
	bool isSeismicOrFaciesLine(RESQML2_0_1_NS::PolylineRepresentation* pr) {
		return pr->isASeismicLine() || pr->isAFaciesLine();
	}
}

std::vector<PolylineRepresentation*> DataObjectRepository::getSeismicLinePolylineRepSet() const
{
	std::vector<RESQML2_0_1_NS::PolylineRepresentation*> result = getDataObjects<RESQML2_0_1_NS::PolylineRepresentation>();

	result.erase(std::remove_if(result.begin(), result.end(), std::not1(std::ptr_fun(isSeismicOrFaciesLine))), result.end());

	return result;
}

std::vector<RESQML2_NS::AbstractIjkGridRepresentation*> DataObjectRepository::getIjkGridRepresentationSet() const { return getDataObjects<RESQML2_NS::AbstractIjkGridRepresentation>(); }

unsigned int DataObjectRepository::getIjkGridRepresentationCount() const
{
	const size_t result = getDataObjects<RESQML2_NS::AbstractIjkGridRepresentation>().size();

	if (result > (std::numeric_limits<unsigned int>::max)()) {
		throw out_of_range("The Ijk Grid Representation count is superior to unsigned int max");
	}
	return static_cast<unsigned int>(result);
}

RESQML2_NS::AbstractIjkGridRepresentation* DataObjectRepository::getIjkGridRepresentation(unsigned int index) const
{
	const std::vector<RESQML2_NS::AbstractIjkGridRepresentation*> result = getDataObjects<RESQML2_NS::AbstractIjkGridRepresentation>();

	if (index >= result.size()) {
		throw out_of_range("The index of the ijk grid is out of range");
	}

	return result[index];
}

std::vector<RESQML2_NS::IjkGridParametricRepresentation*> DataObjectRepository::getIjkGridParametricRepresentationSet() const { return getDataObjects<RESQML2_NS::IjkGridParametricRepresentation>(); }

std::vector<RESQML2_NS::IjkGridExplicitRepresentation*> DataObjectRepository::getIjkGridExplicitRepresentationSet() const { return getDataObjects<RESQML2_NS::IjkGridExplicitRepresentation>(); }

namespace {
	bool isSeismicOrFaciesCube(RESQML2_NS::IjkGridLatticeRepresentation* Ijkglr) {
		return Ijkglr->isASeismicCube() || Ijkglr->isAFaciesCube();
	}
}

vector<RESQML2_NS::IjkGridLatticeRepresentation*> DataObjectRepository::getIjkSeismicCubeGridRepresentationSet() const
{
	std::vector<RESQML2_NS::IjkGridLatticeRepresentation*> result = getDataObjects<RESQML2_NS::IjkGridLatticeRepresentation>();

	result.erase(std::remove_if(result.begin(), result.end(), std::not1(std::ptr_fun(isSeismicOrFaciesCube))), result.end());

	return result;
}

std::vector<RESQML2_NS::UnstructuredGridRepresentation*> DataObjectRepository::getUnstructuredGridRepresentationSet() const { return getDataObjects<RESQML2_NS::UnstructuredGridRepresentation>(); }

std::vector<RESQML2_0_1_NS::FrontierFeature*> DataObjectRepository::getFrontierSet() const { return getDataObjects<RESQML2_0_1_NS::FrontierFeature>(); }

std::vector<RESQML2_0_1_NS::OrganizationFeature*> DataObjectRepository::getOrganizationSet() const { return getDataObjects<RESQML2_0_1_NS::OrganizationFeature>(); }

std::vector<RESQML2_NS::TimeSeries*> DataObjectRepository::getTimeSeriesSet() const { return getDataObjects<RESQML2_NS::TimeSeries>(); }

std::vector<RESQML2_NS::SubRepresentation*> DataObjectRepository::getSubRepresentationSet() const { return getDataObjects<RESQML2_NS::SubRepresentation>(); }

unsigned int DataObjectRepository::getSubRepresentationCount() const {
	const size_t result = getDataObjects<RESQML2_NS::SubRepresentation>().size();

	if (result > (std::numeric_limits<unsigned int>::max)()) {
		throw out_of_range("The subrepresentation count is superior to unsigned int max");
	}
	return static_cast<unsigned int>(result);
}

RESQML2_NS::SubRepresentation* DataObjectRepository::getSubRepresentation(unsigned int index) const
{
	const std::vector<RESQML2_NS::SubRepresentation*> result = getDataObjects<RESQML2_NS::SubRepresentation>();

	if (index >= result.size()) {
		throw out_of_range("The index of the subrepresentation is out of range");
	}

	return result[index];
}

std::vector<RESQML2_0_1_NS::PointSetRepresentation*> DataObjectRepository::getPointSetRepresentationSet() const { return getDataObjects<RESQML2_0_1_NS::PointSetRepresentation>(); }

unsigned int DataObjectRepository::getPointSetRepresentationCount() const
{
	const size_t result = getDataObjects<RESQML2_0_1_NS::PointSetRepresentation>().size();

	if (result > (std::numeric_limits<unsigned int>::max)()) {
		throw out_of_range("The PointSet Representation count is superior to unsigned int max");
	}
	return static_cast<unsigned int>(result);
}

RESQML2_0_1_NS::PointSetRepresentation* DataObjectRepository::getPointSetRepresentation(unsigned int index) const
{
	const std::vector<RESQML2_0_1_NS::PointSetRepresentation*> result = getDataObjects<RESQML2_0_1_NS::PointSetRepresentation>();

	if (index >= result.size()) {
		throw out_of_range("The point set representation index is out of range.");
	}

	return result[index];
}

std::vector<COMMON_NS::AbstractHdfProxy*> DataObjectRepository::getHdfProxySet() const { return getDataObjects<COMMON_NS::AbstractHdfProxy>(); }

unsigned int DataObjectRepository::getHdfProxyCount() const {
	const size_t result = getDataObjects<COMMON_NS::AbstractHdfProxy>().size();

	if (result > (std::numeric_limits<unsigned int>::max)()) {
		throw out_of_range("The Hdf Proxy count is superior to unsigned int max");
	}
	return static_cast<unsigned int>(result);
}

COMMON_NS::AbstractHdfProxy* DataObjectRepository::getHdfProxy(unsigned int index) const
{
	const std::vector<COMMON_NS::AbstractHdfProxy*> result = getDataObjects<COMMON_NS::AbstractHdfProxy>();

	if (index >= result.size()) {
		throw out_of_range("The index of the requested hdf proxy is out of range");
	}

	return result[index];
}

COMMON_NS::AbstractObject* DataObjectRepository::getResqml2_0_1WrapperFromGsoapContext(const std::string & resqmlContentType)
{
	COMMON_NS::AbstractObject* wrapper = nullptr;

	if CHECK_AND_GET_RESQML_2_0_1_FESAPI_WRAPPER_FROM_GSOAP_CONTEXT(MdDatum)
	else if CHECK_AND_GET_RESQML_2_0_1_FESAPI_WRAPPER_FROM_GSOAP_CONTEXT(Activity)
	else if CHECK_AND_GET_RESQML_2_0_1_FESAPI_WRAPPER_FROM_GSOAP_CONTEXT(ActivityTemplate)
	else if CHECK_AND_GET_RESQML_2_0_1_FESAPI_WRAPPER_FROM_GSOAP_CONTEXT(SeismicLatticeFeature)
	else if CHECK_AND_GET_RESQML_2_0_1_FESAPI_WRAPPER_FROM_GSOAP_CONTEXT(SeismicLineFeature)
	else if CHECK_AND_GET_RESQML_2_0_1_FESAPI_WRAPPER_FROM_GSOAP_CONTEXT(SeismicLineSetFeature)
	else if CHECK_AND_GET_RESQML_2_0_1_FESAPI_WRAPPER_FROM_GSOAP_CONTEXT(FrontierFeature)
	else if CHECK_AND_GET_RESQML_2_0_1_FESAPI_WRAPPER_FROM_GSOAP_CONTEXT(LocalDepth3dCrs)
	else if CHECK_AND_GET_RESQML_2_0_1_FESAPI_WRAPPER_FROM_GSOAP_CONTEXT(LocalTime3dCrs)
	else if CHECK_AND_GET_RESQML_2_0_1_FESAPI_WRAPPER_FROM_GSOAP_CONTEXT(TectonicBoundaryFeature)
	else if CHECK_AND_GET_RESQML_2_0_1_FESAPI_WRAPPER_FROM_GSOAP_CONTEXT(GeneticBoundaryFeature)
	else if CHECK_AND_GET_RESQML_2_0_1_FESAPI_WRAPPER_FROM_GSOAP_CONTEXT(BoundaryFeature)
	else if CHECK_AND_GET_RESQML_2_0_1_FESAPI_WRAPPER_FROM_GSOAP_CONTEXT(WellboreFeature)
	else if CHECK_AND_GET_RESQML_2_0_1_FESAPI_WRAPPER_FROM_GSOAP_CONTEXT(StratigraphicUnitFeature)
	else if CHECK_AND_GET_RESQML_2_0_1_FESAPI_WRAPPER_FROM_GSOAP_CONTEXT(StratigraphicColumn)
	else if CHECK_AND_GET_RESQML_2_0_1_FESAPI_WRAPPER_FROM_GSOAP_CONTEXT(GenericFeatureInterpretation)
	else if CHECK_AND_GET_RESQML_2_0_1_FESAPI_WRAPPER_FROM_GSOAP_CONTEXT(BoundaryFeatureInterpretation)
	else if CHECK_AND_GET_RESQML_2_0_1_FESAPI_WRAPPER_FROM_GSOAP_CONTEXT(WellboreInterpretation)
	else if CHECK_AND_GET_RESQML_2_0_1_FESAPI_WRAPPER_FROM_GSOAP_CONTEXT(FaultInterpretation)
	else if CHECK_AND_GET_RESQML_2_0_1_FESAPI_WRAPPER_FROM_GSOAP_CONTEXT(HorizonInterpretation)
	else if CHECK_AND_GET_RESQML_2_0_1_FESAPI_WRAPPER_FROM_GSOAP_CONTEXT(StratigraphicUnitInterpretation)
	else if CHECK_AND_GET_RESQML_2_0_1_FESAPI_WRAPPER_FROM_GSOAP_CONTEXT(StratigraphicColumnRankInterpretation)
	else if CHECK_AND_GET_RESQML_2_0_1_FESAPI_WRAPPER_FROM_GSOAP_CONTEXT(StratigraphicOccurrenceInterpretation)
	else if CHECK_AND_GET_RESQML_2_0_1_FESAPI_WRAPPER_FROM_GSOAP_CONTEXT(WellboreFrameRepresentation)
	else if CHECK_AND_GET_RESQML_2_0_1_FESAPI_WRAPPER_FROM_GSOAP_CONTEXT(WellboreMarkerFrameRepresentation)
	else if CHECK_AND_GET_RESQML_2_0_1_FESAPI_WRAPPER_FROM_GSOAP_CONTEXT(WellboreTrajectoryRepresentation)
	else if CHECK_AND_GET_RESQML_2_0_1_FESAPI_WRAPPER_FROM_GSOAP_CONTEXT(PolylineSetRepresentation)
	else if CHECK_AND_GET_RESQML_2_0_1_FESAPI_WRAPPER_FROM_GSOAP_CONTEXT(PointSetRepresentation)
	else if CHECK_AND_GET_RESQML_2_0_1_FESAPI_WRAPPER_FROM_GSOAP_CONTEXT(PlaneSetRepresentation)
	else if CHECK_AND_GET_RESQML_2_0_1_FESAPI_WRAPPER_FROM_GSOAP_CONTEXT(PolylineRepresentation)
	else if CHECK_AND_GET_RESQML_2_0_1_FESAPI_WRAPPER_FROM_GSOAP_CONTEXT(Grid2dRepresentation)
	else if CHECK_AND_GET_RESQML_2_0_1_FESAPI_WRAPPER_FROM_GSOAP_CONTEXT(TriangulatedSetRepresentation)
	else if CHECK_AND_GET_RESQML_2_0_1_FESAPI_WRAPPER_FROM_GSOAP_CONTEXT(BlockedWellboreRepresentation)
	else if CHECK_AND_GET_RESQML_2_0_1_FESAPI_WRAPPER_FROM_GSOAP_CONTEXT(DeviationSurveyRepresentation)
	else if (resqmlContentType.compare(RESQML2_NS::AbstractIjkGridRepresentation::XML_TAG) == 0)
	{
		GET_RESQML_2_0_1_GSOAP_PROXY_FROM_GSOAP_CONTEXT(IjkGridRepresentation)

			if (read->Geometry != nullptr) {
				switch (read->Geometry->Points->soap_type()) {
				case SOAP_TYPE_gsoap_resqml2_0_1_resqml20__Point3dHdf5Array:
					wrapper = new RESQML2_0_1_NS::IjkGridExplicitRepresentation(read); break;
				case SOAP_TYPE_gsoap_resqml2_0_1_resqml20__Point3dParametricArray:
					wrapper = new RESQML2_0_1_NS::IjkGridParametricRepresentation(read); break;
				case SOAP_TYPE_gsoap_resqml2_0_1_resqml20__Point3dLatticeArray:
					wrapper = new RESQML2_0_1_NS::IjkGridLatticeRepresentation(read); break;
				}
			}
			else {
				wrapper = new RESQML2_0_1_NS::IjkGridNoGeometryRepresentation(read);
			}
	}
	else if (resqmlContentType.compare(RESQML2_NS::AbstractIjkGridRepresentation::XML_TAG_TRUNCATED) == 0)
	{
		GET_RESQML_2_0_1_GSOAP_PROXY_FROM_GSOAP_CONTEXT(TruncatedIjkGridRepresentation)

			if (read->Geometry != nullptr) {
				switch (read->Geometry->Points->soap_type()) {
				case SOAP_TYPE_gsoap_resqml2_0_1_resqml20__Point3dHdf5Array:
					wrapper = new RESQML2_0_1_NS::IjkGridExplicitRepresentation(read); break;
				case SOAP_TYPE_gsoap_resqml2_0_1_resqml20__Point3dParametricArray:
					wrapper = new RESQML2_0_1_NS::IjkGridParametricRepresentation(read); break;
				case SOAP_TYPE_gsoap_resqml2_0_1_resqml20__Point3dLatticeArray:
					wrapper = new RESQML2_0_1_NS::IjkGridLatticeRepresentation(read); break;
				}
			}
			else {
				wrapper = new RESQML2_0_1_NS::IjkGridNoGeometryRepresentation(read);
			}
	}
	else if CHECK_AND_GET_RESQML_2_0_1_FESAPI_WRAPPER_FROM_GSOAP_CONTEXT(UnstructuredGridRepresentation)
	else if CHECK_AND_GET_RESQML_2_0_1_FESAPI_WRAPPER_FROM_GSOAP_CONTEXT(PropertyKind)
	else if CHECK_AND_GET_RESQML_2_0_1_FESAPI_WRAPPER_FROM_GSOAP_CONTEXT(PropertySet)
	else if CHECK_AND_GET_RESQML_2_0_1_FESAPI_WRAPPER_FROM_GSOAP_CONTEXT(ContinuousProperty)
	else if CHECK_AND_GET_RESQML_2_0_1_FESAPI_WRAPPER_FROM_GSOAP_CONTEXT(CategoricalProperty)
	else if CHECK_AND_GET_RESQML_2_0_1_FESAPI_WRAPPER_FROM_GSOAP_CONTEXT(DiscreteProperty)
	else if CHECK_AND_GET_RESQML_2_0_1_FESAPI_WRAPPER_FROM_GSOAP_CONTEXT(CommentProperty)
	else if CHECK_AND_GET_RESQML_2_0_1_FESAPI_WRAPPER_FROM_GSOAP_CONTEXT(StringTableLookup)
	else if CHECK_AND_GET_RESQML_2_0_1_FESAPI_WRAPPER_FROM_GSOAP_CONTEXT(EarthModelInterpretation)
	else if CHECK_AND_GET_RESQML_2_0_1_FESAPI_WRAPPER_FROM_GSOAP_CONTEXT(OrganizationFeature)
	else if CHECK_AND_GET_RESQML_2_0_1_FESAPI_WRAPPER_FROM_GSOAP_CONTEXT(StructuralOrganizationInterpretation)
	else if CHECK_AND_GET_RESQML_2_0_1_FESAPI_WRAPPER_FROM_GSOAP_CONTEXT(FluidBoundaryFeature)
	else if CHECK_AND_GET_RESQML_2_0_1_FESAPI_WRAPPER_FROM_GSOAP_CONTEXT(SubRepresentation)
	else if CHECK_AND_GET_RESQML_2_0_1_FESAPI_WRAPPER_FROM_GSOAP_CONTEXT(GridConnectionSetRepresentation)
	else if CHECK_AND_GET_RESQML_2_0_1_FESAPI_WRAPPER_FROM_GSOAP_CONTEXT(TimeSeries)
	else if CHECK_AND_GET_RESQML_2_0_1_FESAPI_WRAPPER_FROM_GSOAP_CONTEXT(RepresentationSetRepresentation)
	else if CHECK_AND_GET_RESQML_2_0_1_FESAPI_WRAPPER_FROM_GSOAP_CONTEXT(NonSealedSurfaceFrameworkRepresentation)
	else if CHECK_AND_GET_RESQML_2_0_1_FESAPI_WRAPPER_FROM_GSOAP_CONTEXT(SealedSurfaceFrameworkRepresentation)
	else if CHECK_AND_GET_RESQML_2_0_1_FESAPI_WRAPPER_FROM_GSOAP_CONTEXT(SealedVolumeFrameworkRepresentation)
	else if CHECK_AND_GET_RESQML_2_0_1_FESAPI_WRAPPER_FROM_GSOAP_CONTEXT(GeobodyFeature)
	else if CHECK_AND_GET_RESQML_2_0_1_FESAPI_WRAPPER_FROM_GSOAP_CONTEXT(GeobodyBoundaryInterpretation)
	else if CHECK_AND_GET_RESQML_2_0_1_FESAPI_WRAPPER_FROM_GSOAP_CONTEXT(GeobodyInterpretation)
	else if CHECK_AND_GET_RESQML_2_0_1_FESAPI_WRAPPER_FROM_GSOAP_CONTEXT(RockFluidOrganizationInterpretation)
	else if CHECK_AND_GET_RESQML_2_0_1_FESAPI_WRAPPER_FROM_GSOAP_CONTEXT(RockFluidUnitInterpretation)
	else if CHECK_AND_GET_RESQML_2_0_1_FESAPI_WRAPPER_FROM_GSOAP_CONTEXT(RockFluidUnitFeature)
	else if (resqmlContentType.compare(COMMON_NS::EpcExternalPartReference::XML_TAG) == 0)
	{
		throw invalid_argument("Please handle this type outside this method since it is not only XML related.");
	}

	return wrapper;
}

COMMON_NS::AbstractObject* DataObjectRepository::getWitsml2_0WrapperFromGsoapContext(const std::string & datatype)
{
	COMMON_NS::AbstractObject* wrapper = nullptr;

	if CHECK_AND_GET_WITSML_2_FESAPI_WRAPPER_FROM_GSOAP_CONTEXT(WITSML2_0_NS, Well, gsoap_eml2_1)
	else if CHECK_AND_GET_WITSML_2_FESAPI_WRAPPER_FROM_GSOAP_CONTEXT(WITSML2_0_NS, WellCompletion, gsoap_eml2_1)
	else if CHECK_AND_GET_WITSML_2_FESAPI_WRAPPER_FROM_GSOAP_CONTEXT(WITSML2_0_NS, Wellbore, gsoap_eml2_1)
	else if CHECK_AND_GET_WITSML_2_FESAPI_WRAPPER_FROM_GSOAP_CONTEXT(WITSML2_0_NS, WellboreCompletion, gsoap_eml2_1)
	else if CHECK_AND_GET_WITSML_2_FESAPI_WRAPPER_FROM_GSOAP_CONTEXT(WITSML2_0_NS, WellboreGeometry, gsoap_eml2_1)
	else if CHECK_AND_GET_WITSML_2_FESAPI_WRAPPER_FROM_GSOAP_CONTEXT(WITSML2_0_NS, Trajectory, gsoap_eml2_1)
	else if CHECK_AND_GET_WITSML_2_FESAPI_WRAPPER_FROM_GSOAP_CONTEXT(WITSML2_0_NS, Log, gsoap_eml2_1)
	else if CHECK_AND_GET_WITSML_2_FESAPI_WRAPPER_FROM_GSOAP_CONTEXT(WITSML2_0_NS, ChannelSet, gsoap_eml2_1)
	else if CHECK_AND_GET_WITSML_2_FESAPI_WRAPPER_FROM_GSOAP_CONTEXT(WITSML2_0_NS, Channel, gsoap_eml2_1)

		return wrapper;
}

COMMON_NS::AbstractObject* DataObjectRepository::getProdml2_1WrapperFromGsoapContext(const std::string & datatype)
{
	COMMON_NS::AbstractObject* wrapper = nullptr;

	if CHECK_AND_GET_PRODML_2_1_FESAPI_WRAPPER_FROM_GSOAP_CONTEXT(PRODML2_1_NS, FluidSystem, gsoap_eml2_2)
	else if CHECK_AND_GET_PRODML_2_1_FESAPI_WRAPPER_FROM_GSOAP_CONTEXT(PRODML2_1_NS, FluidCharacterization, gsoap_eml2_2)

		return wrapper;
}

COMMON_NS::AbstractObject* DataObjectRepository::getResqml2_2WrapperFromGsoapContext(const std::string& resqmlContentType)
{
	COMMON_NS::AbstractObject* wrapper = nullptr;

	if CHECK_AND_GET_RESQML_2_2_FESAPI_WRAPPER_FROM_GSOAP_CONTEXT(CategoricalProperty)
	else if CHECK_AND_GET_RESQML_2_2_FESAPI_WRAPPER_FROM_GSOAP_CONTEXT(CommentProperty)
	else if CHECK_AND_GET_RESQML_2_2_FESAPI_WRAPPER_FROM_GSOAP_CONTEXT(ContinuousProperty)
	else if CHECK_AND_GET_RESQML_2_2_FESAPI_WRAPPER_FROM_GSOAP_CONTEXT(ContinuousColorMap)
	else if CHECK_AND_GET_RESQML_2_2_FESAPI_WRAPPER_FROM_GSOAP_CONTEXT(DiscreteProperty)
	else if CHECK_AND_GET_RESQML_2_2_FESAPI_WRAPPER_FROM_GSOAP_CONTEXT(DiscreteColorMap)
	else if (resqmlContentType.compare(RESQML2_NS::AbstractIjkGridRepresentation::XML_TAG) == 0)
	{
		GET_RESQML_2_2_GSOAP_PROXY_FROM_GSOAP_CONTEXT(IjkGridRepresentation)

			if (read->Geometry != nullptr) {
				switch (read->Geometry->Points->soap_type()) {
				case SOAP_TYPE_gsoap_eml2_2_resqml22__Point3dExternalArray:
					wrapper = new RESQML2_2_NS::IjkGridExplicitRepresentation(read); break;
				case SOAP_TYPE_gsoap_eml2_2_resqml22__Point3dParametricArray:
					wrapper = new RESQML2_2_NS::IjkGridParametricRepresentation(read); break;
				case SOAP_TYPE_gsoap_resqml2_0_1_resqml20__Point3dLatticeArray:
					wrapper = new RESQML2_2_NS::IjkGridLatticeRepresentation(read); break;
				}
			}
			else {
				wrapper = new RESQML2_2_NS::IjkGridNoGeometryRepresentation(read);
			}
	}
	else if (resqmlContentType.compare(RESQML2_NS::AbstractIjkGridRepresentation::XML_TAG_TRUNCATED) == 0)
	{
		GET_RESQML_2_2_GSOAP_PROXY_FROM_GSOAP_CONTEXT(TruncatedIjkGridRepresentation)

			if (read->Geometry != nullptr) {
				switch (read->Geometry->Points->soap_type()) {
				case SOAP_TYPE_gsoap_eml2_2_resqml22__Point3dExternalArray:
					wrapper = new RESQML2_2_NS::IjkGridExplicitRepresentation(read); break;
				case SOAP_TYPE_gsoap_eml2_2_resqml22__Point3dParametricArray:
					wrapper = new RESQML2_2_NS::IjkGridParametricRepresentation(read); break;
				case SOAP_TYPE_gsoap_resqml2_0_1_resqml20__Point3dLatticeArray:
					wrapper = new RESQML2_2_NS::IjkGridLatticeRepresentation(read); break;
				}
			}
			else {
				wrapper = new RESQML2_2_NS::IjkGridNoGeometryRepresentation(read);
			}
	}
	else if CHECK_AND_GET_RESQML_2_2_FESAPI_WRAPPER_FROM_GSOAP_CONTEXT(SeismicWellboreFrameRepresentation)
	else if CHECK_AND_GET_RESQML_2_2_FESAPI_WRAPPER_FROM_GSOAP_CONTEXT(UnstructuredGridRepresentation)
	else if CHECK_AND_GET_RESQML_2_2_FESAPI_WRAPPER_FROM_GSOAP_CONTEXT(WellboreFrameRepresentation)
	
	return wrapper;
}

COMMON_NS::AbstractObject* DataObjectRepository::getEml2_2WrapperFromGsoapContext(const std::string & datatype)
{
	COMMON_NS::AbstractObject* wrapper = nullptr;
	if CHECK_AND_GET_EML_2_2_FESAPI_WRAPPER_FROM_GSOAP_CONTEXT(COMMON_NS, GraphicalInformationSet, gsoap_eml2_2)
		return wrapper;
}

int DataObjectRepository::getGsoapErrorCode() const
{
	return gsoapContext->error;
}

std::string DataObjectRepository::getGsoapErrorMessage() const
{
	ostringstream oss;
	soap_stream_fault(gsoapContext, oss);
	return oss.str();
}

void DataObjectRepository::setHdfProxyFactory(COMMON_NS::HdfProxyFactory * factory) {
	delete hdfProxyFactory;
	hdfProxyFactory = factory;
}

gsoap_resqml2_0_1::eml20__DataObjectReference* DataObjectRepository::createDor(const std::string & guid, const std::string & title, const std::string & version)
{
	gsoap_resqml2_0_1::eml20__DataObjectReference* dor = gsoap_resqml2_0_1::soap_new_eml20__DataObjectReference(gsoapContext);

	if (guid.empty()) {
#if !defined(FESAPI_USE_BOOST_UUID)
		dor->UUID = GuidTools::generateUidAsString();
#else
		boost::uuids::random_generator gen;
		dor->UUID = boost::uuids::to_string(gen());
#endif
	}
	else {
		dor->UUID = guid;
	}

	dor->Title = title;
	if (!version.empty()) {
		dor->VersionString = gsoap_resqml2_0_1::soap_new_std__string(gsoapContext);
		dor->VersionString->assign(version);
	}
	return dor;
}
