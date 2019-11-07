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

#include "../common/DataFeeder.h"
#include "../common/HdfProxyFactory.h"

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
#include "../resqml2_0_1/IjkGridParametricRepresentation.h"
#include "../resqml2_0_1/IjkGridLatticeRepresentation.h"
#include "../resqml2_0_1/IjkGridNoGeometryRepresentation.h"
#include "../resqml2_0_1/UnstructuredGridRepresentation.h"

#include "../resqml2_0_1/Activity.h"
#include "../resqml2_0_1/ActivityTemplate.h"
#include "../resqml2_0_1/ContinuousPropertySeries.h"
#include "../resqml2_0_1/CategoricalPropertySeries.h"
#include "../resqml2_0_1/DiscretePropertySeries.h"

#if WITH_EXPERIMENTAL
#include "../resqml2_2/DiscreteColorMap.h"
#include "../resqml2_2/ContinuousColorMap.h"
#include "../resqml2_2/WellboreFrameRepresentation.h"
#include "../resqml2_2/SeismicWellboreFrameRepresentation.h"

#include "../witsml2_1/Well.h"
#include "../witsml2_1/Wellbore.h"
#include "../witsml2_1/Trajectory.h"
#include "../witsml2_1/Log.h"
#include "../witsml2_1/WellboreMarkerSet.h"
#include "../witsml2_1/ToolErrorModelDictionary.h"
#include "../witsml2_1/ErrorTermDictionary.h"
#include "../witsml2_1/WeightingFunction.h"
#endif

#include "../witsml2_0/Well.h"
#include "../witsml2_0/Wellbore.h"
#include "../witsml2_0/Trajectory.h"
#include "../witsml2_0/WellCompletion.h"
#include "../witsml2_0/WellboreCompletion.h"

#include "../tools/GuidTools.h"

using namespace std;
using namespace COMMON_NS;
using namespace RESQML2_0_1_NS;
using namespace WITSML2_0_NS;
#if WITH_EXPERIMENTAL
using namespace RESQML2_2_NS;
#endif

namespace {
	class SameVersion {
	private:
		std::string version;
	public:
		explicit SameVersion(const std::string & version_): version(version_) {}

		bool operator()(COMMON_NS::AbstractObject const * dataObj) const
		{
			return dataObj->getVersion() == version;
		}
	};
}

// Create a fesapi partial wrapper based on a content type
#define CREATE_FESAPI_PARTIAL_WRAPPER_WITH_VERSION(className)\
	(datatype.compare(className::XML_TAG) == 0)\
	{\
		return createPartial<className>(uuid, title, version);\
	}
#define CREATE_EML_2_0_FESAPI_PARTIAL_WRAPPER(className)\
	(contentType.compare(className::XML_TAG) == 0)\
	{\
		return dor->VersionString == nullptr || dor->VersionString->empty() ? createPartial<className>(dor->UUID, dor->Title, dor->ContentType) : createPartial<className>(dor->UUID, dor->Title, dor->ContentType, *dor->VersionString);\
	}
#define CREATE_EML_2_1_FESAPI_PARTIAL_WRAPPER(className)\
	(contentType.compare(className::XML_TAG) == 0)\
	{\
		return dor->VersionString == nullptr || dor->VersionString->empty() ? createPartial<className>(dor->Uuid, dor->Title, dor->ContentType) : createPartial<className>(dor->Uuid, dor->Title, dor->ContentType, *dor->VersionString);\
	}
#define CREATE_EML_2_2_FESAPI_PARTIAL_WRAPPER(className)\
	(contentType.compare(className::XML_TAG) == 0)\
	{\
		return dor->ObjectVersion == nullptr || dor->ObjectVersion->empty() ? createPartial<className>(dor->Uuid, dor->Title, dor->ContentType) : createPartial<className>(dor->Uuid, dor->Title, dor->ContentType, *dor->ObjectVersion);\
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
///// WITSML 2.1 ////
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
	hdfProxyFactory(new COMMON_NS::HdfProxyFactory())
{
}

DataObjectRepository::DataObjectRepository(const std::string & propertyKindMappingFilesDirectory) :
	dataObjects(),
	forwardRels(),
	backwardRels(),
	gsoapContext(soap_new2(SOAP_XML_STRICT | SOAP_C_UTFSTRING | SOAP_XML_IGNORENS, SOAP_XML_TREE | SOAP_XML_INDENT | SOAP_XML_CANONICAL | SOAP_C_UTFSTRING)),
	warnings(),
	propertyKindMapper(new PropertyKindMapper(this)), defaultHdfProxy(nullptr), defaultCrs(nullptr),
	hdfProxyFactory(new COMMON_NS::HdfProxyFactory())
{
	const string error = propertyKindMapper->loadMappingFilesFromDirectory(propertyKindMappingFilesDirectory);
	if (!error.empty())
	{
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

	if (forwardRels.find(source) == forwardRels.end()) {
		forwardRels[source].push_back(target);
	}
	else {
		const std::vector< COMMON_NS::AbstractObject * >& targets = forwardRels.at(source);
		if (std::find(targets.begin(), targets.end(), target) == targets.end()) {
			forwardRels[source].push_back(target);
		}
		else
			return;
	}
	backwardRels[target].push_back(source);
	
	RESQML2_NS::AbstractLocal3dCrs const * crs = dynamic_cast<RESQML2_NS::AbstractLocal3dCrs const *>(target);
	if (crs != nullptr) {
		RESQML2_NS::AbstractRepresentation const * rep = dynamic_cast<RESQML2_NS::AbstractRepresentation const *>(source);
		if (rep != nullptr && !rep->isPartial()) {
			RESQML2_NS::AbstractFeatureInterpretation * interp = rep->getInterpretation();
			if (interp != nullptr && !interp->isPartial()) {
				interp->initDomain(gsoap_resqml2_0_1::resqml20__Domain__mixed);
			}
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

std::string DataObjectRepository::generateRandomUuidAsString() const
{
	return GuidTools::generateUidAsString();
}

namespace {
	void replaceDataObjectInARelMap(COMMON_NS::AbstractObject* dataObjToReplace, COMMON_NS::AbstractObject * newDataObj, std::unordered_map< COMMON_NS::AbstractObject const *, std::vector< COMMON_NS::AbstractObject * > > & myMap) {
		for (auto& pair : myMap) {
			if (pair.first == dataObjToReplace) {
				myMap[newDataObj] = pair.second;
			}
			else {
				std::replace(pair.second.begin(), pair.second.end(), dataObjToReplace, newDataObj);
			}
		}
		myMap.erase(dataObjToReplace);
	}
}

void DataObjectRepository::replaceDataObjectInRels(COMMON_NS::AbstractObject* dataObjToReplace, COMMON_NS::AbstractObject* newDataObj)
{
	replaceDataObjectInARelMap(dataObjToReplace, newDataObj, forwardRels);
	replaceDataObjectInARelMap(dataObjToReplace, newDataObj, backwardRels);
}

COMMON_NS::AbstractObject* DataObjectRepository::addOrReplaceDataObject(COMMON_NS::AbstractObject* proxy, bool replaceOnlyContent)
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
			if (proxy->getVersion().empty() && !versions.empty()) {
				throw invalid_argument("You cannot have at the same time a versionned and an unversionned object.");
			}

			// replace unversionned version by the versioned version.
			if (!proxy->getVersion().empty()) {
				same = std::find_if(versions.begin(), versions.end(), SameVersion(""));
			}
		}

		if (same == versions.end()) {
			dataObjects[proxy->getUuid()].push_back(proxy);
		}
		else {
			if (proxy->getContentType() != (*same)->getContentType()) {
				throw invalid_argument("Cannot replace " + proxy->getUuid() + " with a different content type : " + proxy->getContentType() + " vs " + (*same)->getContentType());
			}
			if (!replaceOnlyContent || dynamic_cast<AbstractIjkGridRepresentation*>(*same) != nullptr) {
				replaceDataObjectInRels(*same, proxy);

				delete *same;
				*same = proxy;
			}
			else {
				if (proxy->getXmlNamespace() == "resqml20" || proxy->getXmlNamespace() == "eml20") {
					(*same)->setGsoapProxy(proxy->getEml20GsoapProxy());
				}
				else if (proxy->getXmlNamespace() == "witsml20" || proxy->getXmlNamespace() == "eml21") {
					(*same)->setGsoapProxy(proxy->getEml21GsoapProxy());
				}
#if WITH_EXPERIMENTAL
				else if (proxy->getXmlNamespace() == "resqml22" || proxy->getXmlNamespace() == "eml22") {
					(*same)->setGsoapProxy(proxy->getEml22GsoapProxy());
				}
#endif
				return *same;
			}
		}
	}
	proxy->repository = this;
	return proxy;
}

COMMON_NS::AbstractObject* DataObjectRepository::addOrReplaceGsoapProxy(const std::string & xml, const string & contentOrDataType)
{
	istringstream iss(xml);
	setGsoapStream(&iss);

	string ns;
	size_t dataTypeCharPos;
	if (contentOrDataType.find("application/x-") == 0) { // content type
		// datatype
		dataTypeCharPos = contentOrDataType.find_last_of('_'); // The XML tag is after "obj_"
		if (dataTypeCharPos == string::npos) { dataTypeCharPos = contentOrDataType.find_last_of('='); }

		//namespace
		const size_t dashPos = contentOrDataType.find('-');
		const size_t plusPos = contentOrDataType.find('+');
		ns = contentOrDataType.substr(dashPos + 1, plusPos - dashPos - 1);
		const size_t equalPos = contentOrDataType.find('=');
		ns += contentOrDataType[equalPos + 1];
		ns += contentOrDataType[equalPos + 3];
	}
	else { // qualified data type
		const size_t dotPos = contentOrDataType.find('.');

		// datatype
		dataTypeCharPos = contentOrDataType.find_last_of('_'); // The XML tag is after "obj_"
		if (dataTypeCharPos == string::npos) { dataTypeCharPos = dotPos; }

		//namespace
		ns = contentOrDataType.substr(0, dotPos);
	}
	const string datatype = contentOrDataType.substr(dataTypeCharPos + 1);

	COMMON_NS::AbstractObject* wrapper = nullptr;
	if (ns == "eml20" && datatype == "EpcExternalPartReference") {
		gsoap_resqml2_0_1::_eml20__EpcExternalPartReference* read = gsoap_resqml2_0_1::soap_new_eml20__obj_USCOREEpcExternalPartReference(gsoapContext);
		soap_read_eml20__obj_USCOREEpcExternalPartReference(gsoapContext, read);
		wrapper = hdfProxyFactory->make(read);
	}
	else if (ns == "resqml20") {
		if (contentOrDataType != "application/x-resqml+xml;version=2.0.1;type=obj_Activity" &&
			contentOrDataType != "application/x-resqml+xml;version=2.0.1;type=obj_ActivityTemplate" &&
			contentOrDataType != "application/x-resqml+xml;version=2.0.1;type=obj_CategoricalPropertySeries" &&
			contentOrDataType != "application/x-resqml+xml;version=2.0.1;type=obj_CommentPropertySeries" &&
			contentOrDataType != "application/x-resqml+xml;version=2.0.1;type=obj_ContinuousPropertySeries" &&
			contentOrDataType != "application/x-resqml+xml;version=2.0.1;type=obj_StreamlinesFeature" &&
			contentOrDataType != "application/x-resqml+xml;version=2.0.1;type=obj_StreamlinesRepresentation") {
			addWarning("Content type \"" + contentOrDataType + "\" does not belong to 2.0.1. Probably to 2.0? Please fix your content type or ask exporter to fix it.");
		}
		wrapper = getResqml2_0_1WrapperFromGsoapContext(datatype);
	}
	else if (ns == "witsml20") {
		wrapper = getWitsml2_0WrapperFromGsoapContext(datatype);
	}
#if WITH_EXPERIMENTAL
	else if (ns == "resqml22") {
		wrapper = getResqml2_2WrapperFromGsoapContext(datatype);
	}
	else if (ns == "eml22") {
		wrapper = getEml2_2WrapperFromGsoapContext(datatype);
	}
	else if (ns == "witsml21") {
		wrapper = getWitsml2_1WrapperFromGsoapContext(datatype);
	}
#endif

	if (wrapper != nullptr) {
		if (gsoapContext->error != SOAP_OK) {
			ostringstream oss;
			soap_stream_fault(gsoapContext, oss);
			delete wrapper;
		}
		else {
			COMMON_NS::AbstractObject* wrapperInRepo = addOrReplaceDataObject(wrapper, true);
			if (wrapperInRepo != wrapper) {
				delete wrapper;
			}
			return wrapperInRepo;
		}
	}

	addWarning("The content or data type " + contentOrDataType + " could not be wrapped by fesapi. The related instance will be ignored.");
	return nullptr;
}

std::unordered_map< std::string, std::vector<COMMON_NS::AbstractObject*> > DataObjectRepository::getDataObjectsGroupedByDataType() const
{
	std::unordered_map< std::string, std::vector<COMMON_NS::AbstractObject*> > result;
	for (std::unordered_map< std::string, std::vector< COMMON_NS::AbstractObject* > >::const_iterator it = dataObjects.begin(); it != dataObjects.end(); ++it) {
		for (size_t i = 0; i < it->second.size(); ++i) {
			result[it->second[i]->getQualifiedType()].push_back(it->second[i]);
		}
	}

	return result;
}

std::unordered_map< std::string, std::vector<COMMON_NS::AbstractObject*> > DataObjectRepository::getDataObjectsGroupedByDataType(const std::string & filter) const
{
	std::unordered_map< std::string, std::vector<COMMON_NS::AbstractObject*> > result;
	for (std::unordered_map< std::string, std::vector< COMMON_NS::AbstractObject* > >::const_iterator it = dataObjects.begin(); it != dataObjects.end(); ++it) {
		for (size_t i = 0; i < it->second.size(); ++i) {
			std::string datatype = it->second[i]->getQualifiedType();
			if (datatype.find(filter) != std::string::npos) {
				result[datatype].push_back(it->second[i]);
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

COMMON_NS::AbstractObject* DataObjectRepository::createPartial(const std::string & uuid, const std::string & title, const std::string & contentType, const std::string & version)
{
	size_t lastEqualCharPos = contentType.find_last_of('_'); // The XML tag is after "obj_"
	if (lastEqualCharPos == string::npos) { lastEqualCharPos = contentType.find_last_of('='); }
	const string datatype = contentType.substr(lastEqualCharPos + 1);

	if CREATE_FESAPI_PARTIAL_WRAPPER_WITH_VERSION(MdDatum)
	else if CREATE_FESAPI_PARTIAL_WRAPPER_WITH_VERSION(Activity)
	else if CREATE_FESAPI_PARTIAL_WRAPPER_WITH_VERSION(ActivityTemplate)
	else if CREATE_FESAPI_PARTIAL_WRAPPER_WITH_VERSION(SeismicLatticeFeature)
	else if CREATE_FESAPI_PARTIAL_WRAPPER_WITH_VERSION(SeismicLineFeature)
	else if CREATE_FESAPI_PARTIAL_WRAPPER_WITH_VERSION(SeismicLineSetFeature)
	else if CREATE_FESAPI_PARTIAL_WRAPPER_WITH_VERSION(FrontierFeature)
	else if CREATE_FESAPI_PARTIAL_WRAPPER_WITH_VERSION(LocalDepth3dCrs)
	else if CREATE_FESAPI_PARTIAL_WRAPPER_WITH_VERSION(LocalTime3dCrs)
	else if CREATE_FESAPI_PARTIAL_WRAPPER_WITH_VERSION(TectonicBoundaryFeature)
	else if CREATE_FESAPI_PARTIAL_WRAPPER_WITH_VERSION(GeneticBoundaryFeature)
	else if CREATE_FESAPI_PARTIAL_WRAPPER_WITH_VERSION(BoundaryFeature)
	else if CREATE_FESAPI_PARTIAL_WRAPPER_WITH_VERSION(WellboreFeature)
	else if CREATE_FESAPI_PARTIAL_WRAPPER_WITH_VERSION(StratigraphicUnitFeature)
	else if CREATE_FESAPI_PARTIAL_WRAPPER_WITH_VERSION(StratigraphicColumn)
	else if CREATE_FESAPI_PARTIAL_WRAPPER_WITH_VERSION(GenericFeatureInterpretation)
	else if CREATE_FESAPI_PARTIAL_WRAPPER_WITH_VERSION(BoundaryFeatureInterpretation)
	else if CREATE_FESAPI_PARTIAL_WRAPPER_WITH_VERSION(WellboreInterpretation)
	else if CREATE_FESAPI_PARTIAL_WRAPPER_WITH_VERSION(FaultInterpretation)
	else if CREATE_FESAPI_PARTIAL_WRAPPER_WITH_VERSION(HorizonInterpretation)
	else if CREATE_FESAPI_PARTIAL_WRAPPER_WITH_VERSION(StratigraphicUnitInterpretation)
	else if CREATE_FESAPI_PARTIAL_WRAPPER_WITH_VERSION(StratigraphicColumnRankInterpretation)
	else if CREATE_FESAPI_PARTIAL_WRAPPER_WITH_VERSION(StratigraphicOccurrenceInterpretation)
	else if CREATE_FESAPI_PARTIAL_WRAPPER_WITH_VERSION(RESQML2_0_1_NS::WellboreFrameRepresentation)
	else if CREATE_FESAPI_PARTIAL_WRAPPER_WITH_VERSION(WellboreMarkerFrameRepresentation)
	else if CREATE_FESAPI_PARTIAL_WRAPPER_WITH_VERSION(WellboreTrajectoryRepresentation)
	else if CREATE_FESAPI_PARTIAL_WRAPPER_WITH_VERSION(PolylineSetRepresentation)
	else if CREATE_FESAPI_PARTIAL_WRAPPER_WITH_VERSION(PointSetRepresentation)
	else if CREATE_FESAPI_PARTIAL_WRAPPER_WITH_VERSION(PlaneSetRepresentation)
	else if CREATE_FESAPI_PARTIAL_WRAPPER_WITH_VERSION(PolylineRepresentation)
	else if CREATE_FESAPI_PARTIAL_WRAPPER_WITH_VERSION(Grid2dRepresentation)
	else if CREATE_FESAPI_PARTIAL_WRAPPER_WITH_VERSION(TriangulatedSetRepresentation)
	else if CREATE_FESAPI_PARTIAL_WRAPPER_WITH_VERSION(BlockedWellboreRepresentation)
	else if CREATE_FESAPI_PARTIAL_WRAPPER_WITH_VERSION(AbstractIjkGridRepresentation)
	else if CREATE_FESAPI_PARTIAL_WRAPPER_WITH_VERSION(UnstructuredGridRepresentation)
	else if CREATE_FESAPI_PARTIAL_WRAPPER_WITH_VERSION(PropertyKind)
	else if CREATE_FESAPI_PARTIAL_WRAPPER_WITH_VERSION(PropertySet)
	else if CREATE_FESAPI_PARTIAL_WRAPPER_WITH_VERSION(ContinuousProperty)
	else if CREATE_FESAPI_PARTIAL_WRAPPER_WITH_VERSION(ContinuousPropertySeries)
	else if CREATE_FESAPI_PARTIAL_WRAPPER_WITH_VERSION(CategoricalProperty)
	else if CREATE_FESAPI_PARTIAL_WRAPPER_WITH_VERSION(CategoricalPropertySeries)
	else if CREATE_FESAPI_PARTIAL_WRAPPER_WITH_VERSION(DiscreteProperty)
	else if CREATE_FESAPI_PARTIAL_WRAPPER_WITH_VERSION(DiscretePropertySeries)
	else if CREATE_FESAPI_PARTIAL_WRAPPER_WITH_VERSION(CommentProperty)
	else if CREATE_FESAPI_PARTIAL_WRAPPER_WITH_VERSION(StringTableLookup)
	else if CREATE_FESAPI_PARTIAL_WRAPPER_WITH_VERSION(EarthModelInterpretation)
	else if CREATE_FESAPI_PARTIAL_WRAPPER_WITH_VERSION(OrganizationFeature)
	else if CREATE_FESAPI_PARTIAL_WRAPPER_WITH_VERSION(StructuralOrganizationInterpretation)
	else if CREATE_FESAPI_PARTIAL_WRAPPER_WITH_VERSION(FluidBoundaryFeature)
	else if CREATE_FESAPI_PARTIAL_WRAPPER_WITH_VERSION(SubRepresentation)
	else if CREATE_FESAPI_PARTIAL_WRAPPER_WITH_VERSION(GridConnectionSetRepresentation)
	else if CREATE_FESAPI_PARTIAL_WRAPPER_WITH_VERSION(TimeSeries)
	else if CREATE_FESAPI_PARTIAL_WRAPPER_WITH_VERSION(RepresentationSetRepresentation)
	else if CREATE_FESAPI_PARTIAL_WRAPPER_WITH_VERSION(NonSealedSurfaceFrameworkRepresentation)
	else if CREATE_FESAPI_PARTIAL_WRAPPER_WITH_VERSION(SealedSurfaceFrameworkRepresentation)
	else if CREATE_FESAPI_PARTIAL_WRAPPER_WITH_VERSION(SealedVolumeFrameworkRepresentation)
	else if CREATE_FESAPI_PARTIAL_WRAPPER_WITH_VERSION(DeviationSurveyRepresentation)
	else if CREATE_FESAPI_PARTIAL_WRAPPER_WITH_VERSION(GeobodyFeature)
	else if CREATE_FESAPI_PARTIAL_WRAPPER_WITH_VERSION(GeobodyBoundaryInterpretation)
	else if CREATE_FESAPI_PARTIAL_WRAPPER_WITH_VERSION(GeobodyInterpretation)
	else if CREATE_FESAPI_PARTIAL_WRAPPER_WITH_VERSION(RockFluidOrganizationInterpretation)
	else if CREATE_FESAPI_PARTIAL_WRAPPER_WITH_VERSION(RockFluidUnitInterpretation)
	else if CREATE_FESAPI_PARTIAL_WRAPPER_WITH_VERSION(RockFluidUnitFeature)
	else if CREATE_FESAPI_PARTIAL_WRAPPER_WITH_VERSION(WITSML2_0_NS::Well)
	else if CREATE_FESAPI_PARTIAL_WRAPPER_WITH_VERSION(WITSML2_0_NS::WellCompletion)
	else if CREATE_FESAPI_PARTIAL_WRAPPER_WITH_VERSION(WITSML2_0_NS::WellboreCompletion)
	else if CREATE_FESAPI_PARTIAL_WRAPPER_WITH_VERSION(WITSML2_0_NS::Wellbore)
	else if CREATE_FESAPI_PARTIAL_WRAPPER_WITH_VERSION(WITSML2_0_NS::Trajectory)
#if WITH_EXPERIMENTAL
	else if CREATE_FESAPI_PARTIAL_WRAPPER_WITH_VERSION(WITSML2_1_NS::ToolErrorModel)
	else if CREATE_FESAPI_PARTIAL_WRAPPER_WITH_VERSION(WITSML2_1_NS::ErrorTerm)
	else if CREATE_FESAPI_PARTIAL_WRAPPER_WITH_VERSION(WITSML2_1_NS::WeightingFunction)
	else if CREATE_FESAPI_PARTIAL_WRAPPER_WITH_VERSION(COMMON_NS::GraphicalInformationSet)
	else if CREATE_FESAPI_PARTIAL_WRAPPER_WITH_VERSION(RESQML2_2_NS::DiscreteColorMap)
	else if CREATE_FESAPI_PARTIAL_WRAPPER_WITH_VERSION(RESQML2_2_NS::ContinuousColorMap)
	else if CREATE_FESAPI_PARTIAL_WRAPPER_WITH_VERSION(RESQML2_2_NS::WellboreFrameRepresentation)
	else if CREATE_FESAPI_PARTIAL_WRAPPER_WITH_VERSION(RESQML2_2_NS::SeismicWellboreFrameRepresentation)
#endif
	else if (datatype.compare(COMMON_NS::EpcExternalPartReference::XML_TAG) == 0)
	{
		gsoap_resqml2_0_1::eml20__DataObjectReference* dor = createDor(uuid, title, version);
		COMMON_NS::AbstractObject* result = hdfProxyFactory->make(dor);
		dor->ContentType = result->getContentType();
		addOrReplaceDataObject(result);
		return result;
	}

	throw invalid_argument("The content type " + contentType + " of the partial object to create has not been recognized by fesapi.");
}

COMMON_NS::AbstractObject* DataObjectRepository::createPartial(gsoap_resqml2_0_1::eml20__DataObjectReference const * dor)
{
	const size_t lastEqualCharPos = dor->ContentType.find_last_of('_'); // The XML tag is after "type=obj_"
	const string contentType = dor->ContentType.substr(lastEqualCharPos + 1);
	const string uuid = dor->UUID;
	const string title = dor->Title;

	if (dor->VersionString == nullptr) {
		return createPartial(uuid, title, contentType);
	}
	else {
		return createPartial(uuid, title, contentType, *dor->VersionString);
	}
}

COMMON_NS::AbstractObject* DataObjectRepository::createPartial(gsoap_eml2_1::eml21__DataObjectReference const * dor)
{
	const size_t lastEqualCharPos = dor->ContentType.find_last_of('='); // The XML tag is after "type="
	const string contentType = dor->ContentType.substr(lastEqualCharPos + 1);
	const string uuid = dor->Uuid;
	const string title = dor->Title;

	if (dor->VersionString == nullptr) {
		return createPartial(uuid, title, contentType);
	}
	else {
		return createPartial(uuid, title, contentType, *dor->VersionString);
	}
}

#if WITH_EXPERIMENTAL
COMMON_NS::AbstractObject* DataObjectRepository::createPartial(gsoap_eml2_2::eml22__DataObjectReference const * dor)
{
	const size_t lastEqualCharPos = dor->ContentType.find_last_of('='); // The XML tag is after "type="
	const string contentType = dor->ContentType.substr(lastEqualCharPos + 1);
	const string uuid = dor->Uuid;
	const string title = dor->Title;

	if (dor->ObjectVersion == nullptr) {
		return createPartial(uuid, title, contentType);
	}
	else {
		return createPartial(uuid, title, contentType, *dor->ObjectVersion);
	}
}
#endif

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

WellboreFeature* DataObjectRepository::createWellboreFeature(const std::string & guid, const std::string & title)
{
	return new WellboreFeature(this, guid, title);
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

WellboreInterpretation* DataObjectRepository::createWellboreInterpretation(WellboreFeature * wellbore, const std::string & guid, const std::string & title, bool isDrilled)
{
	return new WellboreInterpretation(wellbore, guid, title, isDrilled);
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

WellboreTrajectoryRepresentation* DataObjectRepository::createWellboreTrajectoryRepresentation(WellboreInterpretation * interp, const std::string & guid, const std::string & title, RESQML2_NS::MdDatum * mdInfo)
{
	return new WellboreTrajectoryRepresentation(interp, guid, title, mdInfo);
}

WellboreTrajectoryRepresentation* DataObjectRepository::createWellboreTrajectoryRepresentation(WellboreInterpretation * interp, const std::string & guid, const std::string & title, DeviationSurveyRepresentation * deviationSurvey)
{
	return new WellboreTrajectoryRepresentation(interp, guid, title, deviationSurvey);
}

RESQML2_0_1_NS::DeviationSurveyRepresentation* DataObjectRepository::createDeviationSurveyRepresentation(RESQML2_0_1_NS::WellboreInterpretation * interp, const std::string & guid, const std::string & title, const bool & isFinal, RESQML2_NS::MdDatum * mdInfo)
{
	return new DeviationSurveyRepresentation(interp, guid, title, isFinal, mdInfo);
}

#if WITH_EXPERIMENTAL
RESQML2_NS::WellboreFrameRepresentation* DataObjectRepository::createWellboreFrameRepresentation(WellboreInterpretation * interp, const std::string & guid, const std::string & title, WellboreTrajectoryRepresentation * traj, bool previousEnergisticsVersion)
{
	if (previousEnergisticsVersion) {
		return new RESQML2_0_1_NS::WellboreFrameRepresentation(interp, guid, title, traj);
	}

	return new RESQML2_2_NS::WellboreFrameRepresentation(interp, guid, title, traj);
}

RESQML2_2_NS::SeismicWellboreFrameRepresentation* DataObjectRepository::createSeismicWellboreFrameRepresentation(
	RESQML2_0_1_NS::WellboreInterpretation* interp,
	const std::string& guid, const std::string& title,
	RESQML2_0_1_NS::WellboreTrajectoryRepresentation* traj,
	double seismicReferenceDatum,
	double weatheringVelocity,
	class RESQML2_0_1_NS::LocalTime3dCrs* crs)
{
	return new RESQML2_2_NS::SeismicWellboreFrameRepresentation(interp, guid, title, traj, seismicReferenceDatum, weatheringVelocity, crs);
}
#else
RESQML2_NS::WellboreFrameRepresentation* DataObjectRepository::createWellboreFrameRepresentation(WellboreInterpretation* interp, const std::string& guid, const std::string& title, WellboreTrajectoryRepresentation* traj)
{
	return new WellboreFrameRepresentation(interp, guid, title, traj);
}
#endif

WellboreMarkerFrameRepresentation* DataObjectRepository::createWellboreMarkerFrameRepresentation(WellboreInterpretation * interp, const std::string & guid, const std::string & title, WellboreTrajectoryRepresentation * traj)
{
	return new WellboreMarkerFrameRepresentation(interp, guid, title, traj);
}

BlockedWellboreRepresentation* DataObjectRepository::createBlockedWellboreRepresentation(WellboreInterpretation * interp,
	const std::string & guid, const std::string & title, WellboreTrajectoryRepresentation * traj)
{
	return new BlockedWellboreRepresentation(interp, guid, title, traj);
}

RESQML2_NS::RepresentationSetRepresentation* DataObjectRepository::createRepresentationSetRepresentation(
	AbstractOrganizationInterpretation* interp,
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

AbstractIjkGridRepresentation* DataObjectRepository::createPartialIjkGridRepresentation(const std::string & guid, const std::string & title)
{
	return createPartial<AbstractIjkGridRepresentation>(guid, title, "application/x-resqml+xml;version=2.0;type=obj_IjkGridRepresentation");
}

AbstractIjkGridRepresentation* DataObjectRepository::createPartialTruncatedIjkGridRepresentation(const std::string & guid, const std::string & title)
{
	gsoap_resqml2_0_1::eml20__DataObjectReference* dor = gsoap_resqml2_0_1::soap_new_eml20__DataObjectReference(getGsoapContext());
	dor->UUID = guid;
	dor->Title = title;
	return new AbstractIjkGridRepresentation(dor, true);
}

IjkGridExplicitRepresentation* DataObjectRepository::createIjkGridExplicitRepresentation(const std::string & guid, const std::string & title,
	unsigned int iCount, unsigned int jCount, unsigned int kCount)
{
	return new IjkGridExplicitRepresentation(this, guid, title, iCount, jCount, kCount);
}

IjkGridExplicitRepresentation* DataObjectRepository::createIjkGridExplicitRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp,
	const std::string & guid, const std::string & title,
	unsigned int iCount, unsigned int jCount, unsigned int kCount)
{
	return new IjkGridExplicitRepresentation(interp, guid, title, iCount, jCount, kCount);
}

IjkGridParametricRepresentation* DataObjectRepository::createIjkGridParametricRepresentation(const std::string & guid, const std::string & title,
	unsigned int iCount, unsigned int jCount, unsigned int kCount)
{
	return new IjkGridParametricRepresentation(this, guid, title, iCount, jCount, kCount);
}

IjkGridParametricRepresentation* DataObjectRepository::createIjkGridParametricRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp,
	const std::string & guid, const std::string & title,
	unsigned int iCount, unsigned int jCount, unsigned int kCount)
{
	return new IjkGridParametricRepresentation(interp, guid, title, iCount, jCount, kCount);
}

IjkGridLatticeRepresentation* DataObjectRepository::createIjkGridLatticeRepresentation(const std::string & guid, const std::string & title,
	unsigned int iCount, unsigned int jCount, unsigned int kCount)
{
	return new IjkGridLatticeRepresentation(this, guid, title, iCount, jCount, kCount);
}

IjkGridLatticeRepresentation* DataObjectRepository::createIjkGridLatticeRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp,
	const std::string & guid, const std::string & title,
	unsigned int iCount, unsigned int jCount, unsigned int kCount)
{
	return new IjkGridLatticeRepresentation(interp, guid, title, iCount, jCount, kCount);
}

RESQML2_0_1_NS::IjkGridNoGeometryRepresentation* DataObjectRepository::createIjkGridNoGeometryRepresentation(
	const std::string & guid, const std::string & title,
	unsigned int iCount, unsigned int jCount, unsigned int kCount)
{
	return new IjkGridNoGeometryRepresentation(this, guid, title, iCount, jCount, kCount);
}

RESQML2_0_1_NS::IjkGridNoGeometryRepresentation* DataObjectRepository::createIjkGridNoGeometryRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp,
	const std::string & guid, const std::string & title,
	unsigned int iCount, unsigned int jCount, unsigned int kCount)
{
	return new IjkGridNoGeometryRepresentation(interp, guid, title, iCount, jCount, kCount);
}

UnstructuredGridRepresentation* DataObjectRepository::createUnstructuredGridRepresentation(const std::string & guid, const std::string & title,
	const ULONG64 & cellCount)
{
	return new UnstructuredGridRepresentation(this, guid, title, cellCount);
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

StringTableLookup* DataObjectRepository::createStringTableLookup(const std::string & guid, const std::string & title)
{
	return new StringTableLookup(this, guid, title);
}

RESQML2_NS::PropertyKind* DataObjectRepository::createPropertyKind(const std::string & guid, const std::string & title,
	const std::string & namingSystem, const gsoap_resqml2_0_1::resqml20__ResqmlUom & uom, const gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind & parentEnergisticsPropertyKind)
{
	return new RESQML2_0_1_NS::PropertyKind(this, guid, title, namingSystem, uom, parentEnergisticsPropertyKind);
}

RESQML2_NS::PropertyKind* DataObjectRepository::createPropertyKind(const std::string & guid, const std::string & title,
	const std::string & namingSystem, const gsoap_resqml2_0_1::resqml20__ResqmlUom & uom, RESQML2_NS::PropertyKind * parentPropType)
{
	return new RESQML2_0_1_NS::PropertyKind(guid, title, namingSystem, uom, parentPropType);
}

RESQML2_NS::PropertyKind* DataObjectRepository::createPropertyKind(const std::string & guid, const std::string & title,
	const std::string & namingSystem, const std::string & nonStandardUom, const gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind & parentEnergisticsPropertyKind)
{
	return new RESQML2_0_1_NS::PropertyKind(this, guid, title, namingSystem, nonStandardUom, parentEnergisticsPropertyKind);
}

RESQML2_NS::PropertyKind* DataObjectRepository::createPropertyKind(const std::string & guid, const std::string & title,
	const std::string & namingSystem, const std::string & nonStandardUom, RESQML2_NS::PropertyKind * parentPropType)
{
	return new RESQML2_0_1_NS::PropertyKind(guid, title, namingSystem, nonStandardUom, parentPropType);
}

RESQML2_NS::PropertySet* DataObjectRepository::createPropertySet(const std::string & guid, const std::string & title,
	bool hasMultipleRealizations, bool hasSinglePropertyKind, gsoap_resqml2_0_1::resqml20__TimeSetKind timeSetKind)
{
	return new RESQML2_0_1_NS::PropertySet(this, guid, title, hasMultipleRealizations, hasSinglePropertyKind, timeSetKind);
}

CommentProperty* DataObjectRepository::createCommentProperty(RESQML2_NS::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
	const unsigned int & dimension, const gsoap_resqml2_0_1::resqml20__IndexableElements & attachmentKind, const gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind & energisticsPropertyKind)
{
	return new CommentProperty(rep, guid, title, dimension, attachmentKind, energisticsPropertyKind);
}

CommentProperty* DataObjectRepository::createCommentProperty(RESQML2_NS::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
	const unsigned int & dimension, const gsoap_resqml2_0_1::resqml20__IndexableElements & attachmentKind, RESQML2_NS::PropertyKind * localPropType)
{
	return new CommentProperty(rep, guid, title, dimension, attachmentKind, localPropType);
}

ContinuousProperty* DataObjectRepository::createContinuousProperty(RESQML2_NS::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
	const unsigned int & dimension, const gsoap_resqml2_0_1::resqml20__IndexableElements & attachmentKind, const gsoap_resqml2_0_1::resqml20__ResqmlUom & uom, const gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind & energisticsPropertyKind)
{
	return new ContinuousProperty(rep, guid, title, dimension, attachmentKind, uom, energisticsPropertyKind);
}

ContinuousProperty* DataObjectRepository::createContinuousProperty(RESQML2_NS::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
	const unsigned int & dimension, const gsoap_resqml2_0_1::resqml20__IndexableElements & attachmentKind, const gsoap_resqml2_0_1::resqml20__ResqmlUom & uom, RESQML2_NS::PropertyKind * localPropType)
{
	return new ContinuousProperty(rep, guid, title, dimension, attachmentKind, uom, localPropType);
}

ContinuousProperty* DataObjectRepository::createContinuousProperty(RESQML2_NS::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
	const unsigned int & dimension, const gsoap_resqml2_0_1::resqml20__IndexableElements & attachmentKind, const std::string & nonStandardUom, const gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind & energisticsPropertyKind)
{
	return new ContinuousProperty(rep, guid, title, dimension, attachmentKind, nonStandardUom, energisticsPropertyKind);
}

ContinuousProperty* DataObjectRepository::createContinuousProperty(RESQML2_NS::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
	const unsigned int & dimension, const gsoap_resqml2_0_1::resqml20__IndexableElements & attachmentKind, const std::string & nonStandardUom, RESQML2_NS::PropertyKind * localPropType)
{
	return new ContinuousProperty(rep, guid, title, dimension, attachmentKind, nonStandardUom, localPropType);
}

ContinuousPropertySeries* DataObjectRepository::createContinuousPropertySeries(RESQML2_NS::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
	const unsigned int & dimension, const gsoap_resqml2_0_1::resqml20__IndexableElements & attachmentKind, const gsoap_resqml2_0_1::resqml20__ResqmlUom & uom, const gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind & energisticsPropertyKind,
	RESQML2_NS::TimeSeries * ts, const bool & useInterval)
{
	return new ContinuousPropertySeries(rep, guid, title, dimension, attachmentKind, uom, energisticsPropertyKind, ts, useInterval);
}

ContinuousPropertySeries* DataObjectRepository::createContinuousPropertySeries(RESQML2_NS::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
	const unsigned int & dimension, const gsoap_resqml2_0_1::resqml20__IndexableElements & attachmentKind, const gsoap_resqml2_0_1::resqml20__ResqmlUom & uom, RESQML2_NS::PropertyKind * localPropType,
	RESQML2_NS::TimeSeries * ts, const bool & useInterval)
{
	return new ContinuousPropertySeries(rep, guid, title, dimension, attachmentKind, uom, localPropType, ts, useInterval);
}

DiscreteProperty* DataObjectRepository::createDiscreteProperty(RESQML2_NS::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
	const unsigned int & dimension, const gsoap_resqml2_0_1::resqml20__IndexableElements & attachmentKind, const gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind & energisticsPropertyKind)
{
	return new DiscreteProperty(rep, guid, title, dimension, attachmentKind, energisticsPropertyKind);
}

DiscreteProperty* DataObjectRepository::createDiscreteProperty(RESQML2_NS::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
	const unsigned int & dimension, const gsoap_resqml2_0_1::resqml20__IndexableElements & attachmentKind, RESQML2_NS::PropertyKind * localPropType)
{
	return new DiscreteProperty(rep, guid, title, dimension, attachmentKind, localPropType);
}

DiscretePropertySeries* DataObjectRepository::createDiscretePropertySeries(RESQML2_NS::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
	const unsigned int & dimension, const gsoap_resqml2_0_1::resqml20__IndexableElements & attachmentKind, const gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind & energisticsPropertyKind,
	RESQML2_NS::TimeSeries * ts, const bool & useInterval)
{
	return new DiscretePropertySeries(rep, guid, title, dimension, attachmentKind, energisticsPropertyKind, ts, useInterval);
}

DiscretePropertySeries* DataObjectRepository::createDiscretePropertySeries(RESQML2_NS::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
	const unsigned int & dimension, const gsoap_resqml2_0_1::resqml20__IndexableElements & attachmentKind, RESQML2_NS::PropertyKind * localPropType,
	RESQML2_NS::TimeSeries * ts, const bool & useInterval)
{
	return new DiscretePropertySeries(rep, guid, title, dimension, attachmentKind, localPropType, ts, useInterval);
}

CategoricalProperty* DataObjectRepository::createCategoricalProperty(RESQML2_NS::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
	const unsigned int & dimension, const gsoap_resqml2_0_1::resqml20__IndexableElements & attachmentKind,
	StringTableLookup* strLookup, const gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind & energisticsPropertyKind)
{
	return new CategoricalProperty(rep, guid, title, dimension, attachmentKind, strLookup, energisticsPropertyKind);
}

CategoricalProperty* DataObjectRepository::createCategoricalProperty(RESQML2_NS::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
	const unsigned int & dimension, const gsoap_resqml2_0_1::resqml20__IndexableElements & attachmentKind,
	StringTableLookup* strLookup, RESQML2_NS::PropertyKind * localPropType)
{
	return new CategoricalProperty(rep, guid, title, dimension, attachmentKind, strLookup, localPropType);
}

CategoricalPropertySeries* DataObjectRepository::createCategoricalPropertySeries(RESQML2_NS::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
	const unsigned int & dimension, const gsoap_resqml2_0_1::resqml20__IndexableElements & attachmentKind,
	StringTableLookup* strLookup, const gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind & energisticsPropertyKind,
	RESQML2_NS::TimeSeries * ts, const bool & useInterval)
{
	return new CategoricalPropertySeries(rep, guid, title, dimension, attachmentKind, strLookup, energisticsPropertyKind, ts, useInterval);
}

CategoricalPropertySeries* DataObjectRepository::createCategoricalPropertySeries(RESQML2_NS::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
	const unsigned int & dimension, const gsoap_resqml2_0_1::resqml20__IndexableElements & attachmentKind,
	StringTableLookup* strLookup, RESQML2_NS::PropertyKind * localPropType,
	RESQML2_NS::TimeSeries * ts, const bool & useInterval)
{
	return new CategoricalPropertySeries(rep, guid, title, dimension, attachmentKind, strLookup, localPropType, ts, useInterval);
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
	return new WITSML2_0_NS::Well(this, guid, title);
}

WITSML2_0_NS::Well* DataObjectRepository::createWell(const std::string & guid,
	const std::string & title,
	const std::string & operator_,
	gsoap_eml2_1::eml21__WellStatus statusWell,
	gsoap_eml2_1::witsml20__WellDirection directionWell)
{
	return new WITSML2_0_NS::Well(this, guid, title, operator_, statusWell, directionWell);
}

WITSML2_0_NS::Wellbore* DataObjectRepository::createWellbore(WITSML2_0_NS::Well* witsmlWell,
	const std::string & guid,
	const std::string & title)
{
	return new WITSML2_0_NS::Wellbore(witsmlWell, guid, title);
}

WITSML2_0_NS::Wellbore* DataObjectRepository::createWellbore(WITSML2_0_NS::Well* witsmlWell,
	const std::string & guid,
	const std::string & title,
	gsoap_eml2_1::eml21__WellStatus statusWellbore,
	bool isActive,
	bool achievedTD)
{
	return new WITSML2_0_NS::Wellbore(witsmlWell, guid, title, statusWellbore, isActive, achievedTD);
}

WITSML2_0_NS::WellCompletion* DataObjectRepository::createWellCompletion(WITSML2_0_NS::Well* witsmlWell,
	const std::string & guid,
	const std::string & title)
{
	return new WITSML2_0_NS::WellCompletion(witsmlWell, guid, title);
}

WITSML2_0_NS::WellboreCompletion* DataObjectRepository::createWellboreCompletion(WITSML2_0_NS::Wellbore* witsmlWellbore,
	WITSML2_0_NS::WellCompletion* wellCompletion,
	const std::string & guid,
	const std::string & title,
	const std::string & wellCompletionName)
{
	return new WITSML2_0_NS::WellboreCompletion(witsmlWellbore, wellCompletion, guid, title, wellCompletionName);
}

WITSML2_0_NS::Trajectory* DataObjectRepository::createTrajectory(WITSML2_0_NS::Wellbore* witsmlWellbore,
	const std::string & guid,
	const std::string & title,
	gsoap_eml2_1::witsml20__ChannelStatus channelStatus)
{
	return new WITSML2_0_NS::Trajectory(witsmlWellbore, guid, title, channelStatus);
}

#if WITH_EXPERIMENTAL
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

WITSML2_1_NS::ToolErrorModel* DataObjectRepository::createPartialToolErrorModel(
	const std::string & guid,
	const std::string & title)
{
	return createPartial<WITSML2_1_NS::ToolErrorModel>(guid, title);;
}

WITSML2_1_NS::ToolErrorModel* DataObjectRepository::createToolErrorModel(
	const std::string & guid,
	const std::string & title,
	gsoap_eml2_2::witsml2__MisalignmentMode misalignmentMode)
{
	return new WITSML2_1_NS::ToolErrorModel(this, guid, title, misalignmentMode);
}

WITSML2_1_NS::ToolErrorModelDictionary* DataObjectRepository::createToolErrorModelDictionary(
	const std::string & guid,
	const std::string & title)
{
	return new WITSML2_1_NS::ToolErrorModelDictionary(this, guid, title);
}

WITSML2_1_NS::ErrorTerm* DataObjectRepository::createErrorTerm(
	const std::string & guid,
	const std::string & title,
	gsoap_eml2_2::witsml2__ErrorPropagationMode propagationMode,
	WITSML2_1_NS::WeightingFunction* weightingFunction)
{
	return new WITSML2_1_NS::ErrorTerm(this, guid, title, propagationMode, weightingFunction);
}

WITSML2_1_NS::ErrorTermDictionary* DataObjectRepository::createErrorTermDictionary(
	const std::string & guid,
	const std::string & title)
{
	return new WITSML2_1_NS::ErrorTermDictionary(this, guid, title);
}

WITSML2_1_NS::WeightingFunction* DataObjectRepository::createWeightingFunction(
	const std::string & guid,
	const std::string & title,
	const std::string & depthFormula,
	const std::string & inclinationFormula,
	const std::string & azimuthFormula)
{
	return new WITSML2_1_NS::WeightingFunction(this, guid, title, depthFormula, inclinationFormula, azimuthFormula);
}

WITSML2_1_NS::WeightingFunctionDictionary* DataObjectRepository::createWeightingFunctionDictionary(
	const std::string & guid,
	const std::string & title)
{
	return new WITSML2_1_NS::WeightingFunctionDictionary(this, guid, title);
}
#endif

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
			const std::string contentType = tsr->getInterpretationContentType();
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

std::vector<RESQML2_0_1_NS::WellboreFeature*> DataObjectRepository::getWellboreSet() const { return getDataObjects<RESQML2_0_1_NS::WellboreFeature>(); }

vector<WellboreTrajectoryRepresentation *> DataObjectRepository::getWellboreTrajectoryRepresentationSet() const
{
	vector<WellboreTrajectoryRepresentation *> result;

	const std::vector<RESQML2_0_1_NS::WellboreFeature*> wellboreSet = getWellboreSet();

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

vector<DeviationSurveyRepresentation *> DataObjectRepository::getDeviationSurveyRepresentationSet() const
{
	vector<DeviationSurveyRepresentation *> result;

	const std::vector<RESQML2_0_1_NS::WellboreFeature*> wellboreSet = getWellboreSet();

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

std::vector<RESQML2_0_1_NS::AbstractIjkGridRepresentation*> DataObjectRepository::getIjkGridRepresentationSet() const { return getDataObjects<RESQML2_0_1_NS::AbstractIjkGridRepresentation>(); }

unsigned int DataObjectRepository::getIjkGridRepresentationCount() const
{
	const size_t result = getDataObjects<RESQML2_0_1_NS::AbstractIjkGridRepresentation>().size();

	if (result > (std::numeric_limits<unsigned int>::max)()) {
		throw out_of_range("The Ijk Grid Representation count is superior to unsigned int max");
	}
	return static_cast<unsigned int>(result);
}

RESQML2_0_1_NS::AbstractIjkGridRepresentation* DataObjectRepository::getIjkGridRepresentation(unsigned int index) const
{
	const std::vector<RESQML2_0_1_NS::AbstractIjkGridRepresentation*> result = getDataObjects<RESQML2_0_1_NS::AbstractIjkGridRepresentation>();

	if (index >= result.size()) {
		throw out_of_range("The index of the ijk grid is out of range");
	}

	return result[index];
}

std::vector<RESQML2_0_1_NS::IjkGridParametricRepresentation*> DataObjectRepository::getIjkGridParametricRepresentationSet() const { return getDataObjects<RESQML2_0_1_NS::IjkGridParametricRepresentation>(); }

std::vector<RESQML2_0_1_NS::IjkGridExplicitRepresentation*> DataObjectRepository::getIjkGridExplicitRepresentationSet() const { return getDataObjects<RESQML2_0_1_NS::IjkGridExplicitRepresentation>(); }

namespace {
	bool isSeismicOrFaciesCube(RESQML2_0_1_NS::IjkGridLatticeRepresentation* Ijkglr) {
		return Ijkglr->isASeismicCube() || Ijkglr->isAFaciesCube();
	}
}

vector<IjkGridLatticeRepresentation*> DataObjectRepository::getIjkSeismicCubeGridRepresentationSet() const
{
	std::vector<RESQML2_0_1_NS::IjkGridLatticeRepresentation*> result = getDataObjects<RESQML2_0_1_NS::IjkGridLatticeRepresentation>();

	result.erase(std::remove_if(result.begin(), result.end(), std::not1(std::ptr_fun(isSeismicOrFaciesCube))), result.end());

	return result;
}

std::vector<RESQML2_0_1_NS::UnstructuredGridRepresentation*> DataObjectRepository::getUnstructuredGridRepresentationSet() const { return getDataObjects<RESQML2_0_1_NS::UnstructuredGridRepresentation>(); }

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
	else if (resqmlContentType.compare(AbstractIjkGridRepresentation::XML_TAG) == 0)
	{
		GET_RESQML_2_0_1_GSOAP_PROXY_FROM_GSOAP_CONTEXT(IjkGridRepresentation)

			if (read->Geometry != nullptr) {
				switch (read->Geometry->Points->soap_type()) {
				case SOAP_TYPE_gsoap_resqml2_0_1_resqml20__Point3dHdf5Array:
					wrapper = new IjkGridExplicitRepresentation(read); break;
				case SOAP_TYPE_gsoap_resqml2_0_1_resqml20__Point3dParametricArray:
					wrapper = new IjkGridParametricRepresentation(read); break;
				case SOAP_TYPE_gsoap_resqml2_0_1_resqml20__Point3dLatticeArray:
					wrapper = new IjkGridLatticeRepresentation(read); break;
				}
			}
			else {
				wrapper = new IjkGridNoGeometryRepresentation(read);
			}
	}
	else if (resqmlContentType.compare(AbstractIjkGridRepresentation::XML_TAG_TRUNCATED) == 0)
	{
		GET_RESQML_2_0_1_GSOAP_PROXY_FROM_GSOAP_CONTEXT(TruncatedIjkGridRepresentation)

			if (read->Geometry != nullptr) {
				switch (read->Geometry->Points->soap_type()) {
				case SOAP_TYPE_gsoap_resqml2_0_1_resqml20__Point3dHdf5Array:
					wrapper = new IjkGridExplicitRepresentation(read); break;
				case SOAP_TYPE_gsoap_resqml2_0_1_resqml20__Point3dParametricArray:
					wrapper = new IjkGridParametricRepresentation(read); break;
				case SOAP_TYPE_gsoap_resqml2_0_1_resqml20__Point3dLatticeArray:
					wrapper = new IjkGridLatticeRepresentation(read); break;
				}
			}
			else {
				wrapper = new IjkGridNoGeometryRepresentation(read);
			}
	}
	else if CHECK_AND_GET_RESQML_2_0_1_FESAPI_WRAPPER_FROM_GSOAP_CONTEXT(UnstructuredGridRepresentation)
	else if CHECK_AND_GET_RESQML_2_0_1_FESAPI_WRAPPER_FROM_GSOAP_CONTEXT(PropertyKind)
	else if CHECK_AND_GET_RESQML_2_0_1_FESAPI_WRAPPER_FROM_GSOAP_CONTEXT(PropertySet)
	else if CHECK_AND_GET_RESQML_2_0_1_FESAPI_WRAPPER_FROM_GSOAP_CONTEXT(ContinuousProperty)
	else if CHECK_AND_GET_RESQML_2_0_1_FESAPI_WRAPPER_FROM_GSOAP_CONTEXT(ContinuousPropertySeries)
	else if CHECK_AND_GET_RESQML_2_0_1_FESAPI_WRAPPER_FROM_GSOAP_CONTEXT(CategoricalProperty)
	else if CHECK_AND_GET_RESQML_2_0_1_FESAPI_WRAPPER_FROM_GSOAP_CONTEXT(CategoricalPropertySeries)
	else if CHECK_AND_GET_RESQML_2_0_1_FESAPI_WRAPPER_FROM_GSOAP_CONTEXT(DiscreteProperty)
	else if CHECK_AND_GET_RESQML_2_0_1_FESAPI_WRAPPER_FROM_GSOAP_CONTEXT(DiscretePropertySeries)
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
	else if CHECK_AND_GET_WITSML_2_FESAPI_WRAPPER_FROM_GSOAP_CONTEXT(WITSML2_0_NS, Trajectory, gsoap_eml2_1)

	return wrapper;
}

#if WITH_EXPERIMENTAL
COMMON_NS::AbstractObject* DataObjectRepository::getWitsml2_1WrapperFromGsoapContext(const std::string & datatype)
{
	COMMON_NS::AbstractObject* wrapper = nullptr;

	if CHECK_AND_GET_WITSML_2_FESAPI_WRAPPER_FROM_GSOAP_CONTEXT(WITSML2_1_NS, ToolErrorModel, gsoap_eml2_2)
	else if CHECK_AND_GET_WITSML_2_FESAPI_WRAPPER_FROM_GSOAP_CONTEXT(WITSML2_1_NS, ToolErrorModelDictionary, gsoap_eml2_2)
	else if CHECK_AND_GET_WITSML_2_FESAPI_WRAPPER_FROM_GSOAP_CONTEXT(WITSML2_1_NS, ErrorTerm, gsoap_eml2_2)
	else if CHECK_AND_GET_WITSML_2_FESAPI_WRAPPER_FROM_GSOAP_CONTEXT(WITSML2_1_NS, ErrorTermDictionary, gsoap_eml2_2)
	else if CHECK_AND_GET_WITSML_2_FESAPI_WRAPPER_FROM_GSOAP_CONTEXT(WITSML2_1_NS, WeightingFunction, gsoap_eml2_2)
	else if CHECK_AND_GET_WITSML_2_FESAPI_WRAPPER_FROM_GSOAP_CONTEXT(WITSML2_1_NS, WeightingFunctionDictionary, gsoap_eml2_2)

	return wrapper;
}

COMMON_NS::AbstractObject* DataObjectRepository::getResqml2_2WrapperFromGsoapContext(const std::string& resqmlContentType)
{
	COMMON_NS::AbstractObject* wrapper = nullptr;

	if CHECK_AND_GET_RESQML_2_2_FESAPI_WRAPPER_FROM_GSOAP_CONTEXT(DiscreteColorMap)
	else if CHECK_AND_GET_RESQML_2_2_FESAPI_WRAPPER_FROM_GSOAP_CONTEXT(ContinuousColorMap)
	else if CHECK_AND_GET_RESQML_2_2_FESAPI_WRAPPER_FROM_GSOAP_CONTEXT(SeismicWellboreFrameRepresentation)
	else if CHECK_AND_GET_RESQML_2_2_FESAPI_WRAPPER_FROM_GSOAP_CONTEXT(WellboreFrameRepresentation)
		
	return wrapper;
}

COMMON_NS::AbstractObject* DataObjectRepository::getEml2_2WrapperFromGsoapContext(const std::string & datatype)
{
	COMMON_NS::AbstractObject* wrapper = nullptr;

	if CHECK_AND_GET_EML_2_2_FESAPI_WRAPPER_FROM_GSOAP_CONTEXT(COMMON_NS, GraphicalInformationSet, gsoap_eml2_2)
		return wrapper;
}
#endif

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

void DataObjectRepository::registerDataFeeder(COMMON_NS::DataFeeder * dataFeeder)
{
	dataFeeders.push_back(dataFeeder);
}

void DataObjectRepository::setHdfProxyFactory(COMMON_NS::HdfProxyFactory * factory) {
	delete hdfProxyFactory;
	hdfProxyFactory = factory;
}

COMMON_NS::AbstractObject* DataObjectRepository::resolvePartial(COMMON_NS::AbstractObject * partialObj)
{
	for (size_t i = 0; i < dataFeeders.size(); ++i) {
		std::string xml = dataFeeders[i]->resolvePartial(partialObj);
		if (!xml.empty()) {
			return addOrReplaceGsoapProxy(xml, partialObj->getContentType());
		}
	}

	return nullptr;
}

gsoap_resqml2_0_1::eml20__DataObjectReference* DataObjectRepository::createDor(const std::string & guid, const std::string & title, const std::string & version)
{
	gsoap_resqml2_0_1::eml20__DataObjectReference* dor = gsoap_resqml2_0_1::soap_new_eml20__DataObjectReference(gsoapContext);
	dor->UUID = guid.empty() ? generateRandomUuidAsString() : guid;
	dor->Title = title;
	if (!version.empty()) {
		dor->VersionString = gsoap_resqml2_0_1::soap_new_std__string(gsoapContext);
		dor->VersionString->assign(version);
	}
	return dor;
}
