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
#include "EpcDocument.h"

#include <sstream>
#include <stdexcept>

#include "H5Epublic.h"
#include "H5Fpublic.h"

#include "HdfProxyROS3Factory.h"

#include "../epc/Relationship.h"
#include "../epc/FilePart.h"

#include "../eml2/AbstractHdfProxy.h"

#include "../resqml2/AbstractProperty.h"
#include "../resqml2/WellboreMarkerFrameRepresentation.h"

#include "../resqml2_0_1/WellboreMarker.h"
#if WITH_RESQML2_2
#include "../resqml2_2/WellboreMarker.h"
#endif

#include "../witsml2_0/Log.h"
#include "../witsml2_0/Channel.h"
#include "../witsml2_0/ChannelSet.h"

using namespace std;
using namespace gsoap_resqml2_0_1;
using namespace COMMON_NS;

void  EpcDocument::open(const std::string & fileName)
{
	if (fileName.empty()) {
		throw invalid_argument("The epc document name cannot be empty.");
	}
	if (package != nullptr) {
		throw invalid_argument("The epc document must be closed before to be opened again.");
	}

	setFilePath(fileName);

	package.reset(new epc::Package());
}

void EpcDocument::setFilePath(const std::string & fp)
{
	filePath = fp;

	// Turn off HDF5 diagnostic messages
	herr_t hdf5Err = H5Eset_auto(H5E_DEFAULT, nullptr, nullptr);
	if (hdf5Err < 0) {
		throw invalid_argument("The HDF5 error handling could not have been disabled.");
	}

	// Add .epc extension if it is not already done in parameter
	const size_t dotPos = filePath.find_last_of('.');
	if (dotPos != string::npos) {
		if (filePath.substr(dotPos) != DOCUMENT_EXTENSION) {
			filePath += DOCUMENT_EXTENSION;
		}
	}
	else {
		filePath += DOCUMENT_EXTENSION;
	}
}

namespace {
	std::vector<epc::Relationship> getAllEpcRelationships(const DataObjectRepository & repo, COMMON_NS::AbstractObject const * dataObj) {
		std::vector<epc::Relationship> result;

		// Special case for WellboreMarkerFrameRepresentation and byValue rel.
		if (dynamic_cast<RESQML2_NS::WellboreMarkerFrameRepresentation const *>(dataObj) != nullptr) {
			for (const auto srcMarkerFrame : repo.getSourceObjects(dataObj)) {
				if (dynamic_cast<RESQML2_NS::WellboreMarker*>(srcMarkerFrame) == nullptr) {
					epc::Relationship relRep("../" + srcMarkerFrame->getPartNameInEpcDocument(), "", srcMarkerFrame->getUuid());
					relRep.setSourceObjectType();
					result.push_back(relRep);
				}
				else {
					for (const auto srcMarker : repo.getSourceObjects(srcMarkerFrame)) {
						if (!srcMarker->isPartial()) {
							epc::Relationship relRep("../" + srcMarker->getPartNameInEpcDocument(), "", srcMarker->getUuid());
							relRep.setSourceObjectType();
							result.push_back(relRep);
						}
					}
					for (const auto targetMarker : repo.getTargetObjects(srcMarkerFrame)) {
						if (!targetMarker->isPartial() &&
							dynamic_cast<RESQML2_NS::WellboreMarkerFrameRepresentation*>(targetMarker) == nullptr) {
							epc::Relationship relRep("../" + targetMarker->getPartNameInEpcDocument(), "", targetMarker->getUuid());
							relRep.setDestinationObjectType();
							result.push_back(relRep);
						}
					}
				}
			}

			for (const auto targetMarkerFrame : repo.getTargetObjects(dataObj)) {
				if (!targetMarkerFrame->isPartial()) {
					epc::Relationship relRep("../" + targetMarkerFrame->getPartNameInEpcDocument(), "", targetMarkerFrame->getUuid());
					relRep.setDestinationObjectType();
					result.push_back(relRep);
				}
			}

			return result;
		}

		// More general case.
		const std::vector<COMMON_NS::AbstractObject *>& srcObj = repo.getSourceObjects(dataObj);
		for (size_t index = 0; index < srcObj.size(); ++index) {
			if (!srcObj[index]->isPartial()) {
				if (dynamic_cast<RESQML2_NS::WellboreMarker*>(srcObj[index]) == nullptr) {
					epc::Relationship relRep("../" + srcObj[index]->getPartNameInEpcDocument(), "", srcObj[index]->getUuid());
					relRep.setSourceObjectType();
					result.push_back(relRep);
				}
				else {
					const std::vector<COMMON_NS::AbstractObject *>& srcMarkers = repo.getSourceObjects(srcObj[index]);
					for (size_t index2 = 0; index2 < srcMarkers.size(); ++index2) {
						if (!srcMarkers[index2]->isPartial()) {
							epc::Relationship relRep("../" + srcMarkers[index2]->getPartNameInEpcDocument(), "", srcMarkers[index2]->getUuid());
							relRep.setSourceObjectType();
							result.push_back(relRep);
						}
					}
					auto markerFrame = static_cast<RESQML2_NS::WellboreMarker*>(srcObj[index])->getWellboreMarkerFrameRepresentation();
					epc::Relationship relRep("../" + markerFrame->getPartNameInEpcDocument(), "", markerFrame->getUuid());
					relRep.setSourceObjectType();
					result.push_back(relRep);
				}
			}
		}

		const std::vector<COMMON_NS::AbstractObject *>& targetObj = repo.getTargetObjects(dataObj);
		if (dynamic_cast<WITSML2_0_NS::Log const *>(dataObj) == nullptr &&
			dynamic_cast<WITSML2_0_NS::ChannelSet const *>(dataObj) == nullptr) {
			for (size_t index = 0; index < targetObj.size(); ++index) {
				if (!targetObj[index]->isPartial()) {
					if (dynamic_cast<RESQML2_NS::WellboreMarker*>(targetObj[index]) == nullptr) {
						epc::Relationship relRep("../" + targetObj[index]->getPartNameInEpcDocument(), "", targetObj[index]->getUuid());
						relRep.setDestinationObjectType();
						result.push_back(relRep);
					}
					else {
						const std::vector<COMMON_NS::AbstractObject *>& targetMarkers = repo.getTargetObjects(srcObj[index]);
						for (size_t index2 = 0; index2 < targetMarkers.size(); ++index2) {
							if (!targetMarkers[index2]->isPartial() &&
								dynamic_cast<RESQML2_NS::WellboreMarkerFrameRepresentation*>(targetMarkers[index2]) == nullptr) {
								epc::Relationship relRep("../" + targetMarkers[index2]->getPartNameInEpcDocument(), "", targetMarkers[index2]->getUuid());
								relRep.setDestinationObjectType();
								result.push_back(relRep);
							}
						}
					}
				}
			}
		}
		else {
			for (size_t index = 0; index < targetObj.size(); ++index) {
				if (!targetObj[index]->isPartial() &&
					dynamic_cast<WITSML2_0_NS::ChannelSet*>(targetObj[index]) == nullptr &&
					dynamic_cast<WITSML2_0_NS::Channel*>(targetObj[index]) == nullptr) {
					epc::Relationship relRep("../" + targetObj[index]->getPartNameInEpcDocument(), "", targetObj[index]->getUuid());
					relRep.setDestinationObjectType();
					result.push_back(relRep);
				}
			}
		}

		// External part
		EML2_NS::AbstractHdfProxy const * hdfProxy = dynamic_cast<EML2_NS::AbstractHdfProxy const *>(dataObj);
		if (hdfProxy != nullptr && !hdfProxy->isPartial()) {
			epc::Relationship relExt(hdfProxy->getRelativePath(), "", "Hdf5File", false);
			relExt.setExternalResourceType();
			result.push_back(relExt);
		}

		return result;
	}
}

void EpcDocument::serializeFrom(const DataObjectRepository & repo, bool useZip64)
{
	// Cannot include zip.h for some macro conflict reasons with beast which also includes a port of zlib. Consequently cannot use macros below.
	// 0 means APPEND_STATUS_CREATE
	package->openForWriting(filePath, 0, useZip64);

	const std::unordered_map< std::string, std::vector< COMMON_NS::AbstractObject* > > dataObjects = repo.getDataObjects();
	for (std::unordered_map< std::string, std::vector< COMMON_NS::AbstractObject* > >::const_iterator it = dataObjects.begin(); it != dataObjects.end(); ++it)
	{
		for (size_t i = 0; i < it->second.size(); ++i) {
			if (!it->second[i]->isPartial() &&
				dynamic_cast<RESQML2_0_1_NS::WellboreMarker*>(it->second[i]) == nullptr &&
#if WITH_RESQML2_2
				dynamic_cast<RESQML2_2_NS::WellboreMarker*>(it->second[i]) == nullptr &&
#endif
				(dynamic_cast<WITSML2_0_NS::ChannelSet*>(it->second[i]) == nullptr || static_cast<WITSML2_0_NS::ChannelSet*>(it->second[i])->getLogs().empty()) &&
				(dynamic_cast<WITSML2_0_NS::Channel*>(it->second[i]) == nullptr || static_cast<WITSML2_0_NS::Channel*>(it->second[i])->getChannelSets().empty())) {
				// Dataobject
				const string str = it->second[i]->serializeIntoString();
				epc::FilePart* const fp = package->createPart(str, it->second[i]->getPartNameInEpcDocument());

				// Relationships
				const std::vector<epc::Relationship>& relSet = getAllEpcRelationships(repo, it->second[i]);
				for (size_t relIndex = 0; relIndex < relSet.size(); ++relIndex) {
					fp->addRelationship(relSet[relIndex]);
				}

				// Content Type entry
				package->addContentType(epc::ContentType(false, it->second[i]->getContentType(), it->second[i]->getPartNameInEpcDocument()));
			}
		}
	}

	package->writePackage();
}

string EpcDocument::deserializeInto(DataObjectRepository & repo, DataObjectRepository::openingMode hdfPermissionAccess)
{
	std::string result;
	for (const auto& warning : package->openForReading(filePath)) {
		result += warning + '\n';
	}

	// Read all RESQML objects
	const epc::FileContentType::ContentTypeMap contentTypes = package->getFileContentType().getAllContentType();
	// 14 equals "application/x-".size()
	for (epc::FileContentType::ContentTypeMap::const_iterator it=contentTypes.begin(); it != contentTypes.end(); ++it) {
		std::string contentType = it->second.getContentTypeString();
		if (contentType.find("resqml", 14) != std::string::npos ||
			contentType.find("eml", 14) != std::string::npos ||
			contentType.find("witsml", 14) != std::string::npos ||
			contentType.find("prodml", 14) != std::string::npos) {
			if (contentType == "application/x-resqml+xml;version=2.0;type=obj_EpcExternalPartReference") {
				result += "The content type " + contentType + " should belong to EML20 and not to RESQML20 since obj_EpcExternalPartReference is part of COMMON 2.0 and not part of RESQML 2.0.\n";
				contentType = "application/x-eml+xml;version=2.0;type=obj_EpcExternalPartReference";
			}
			if (contentType == "application/x-eml+xml;version=2.0;type=obj_EpcExternalPartReference" ||
				contentType == "application/x-eml+xml;version=2.3;type=EpcExternalPartReference") {
				// Look for the relative path of the HDF file
				string relFilePath = "";
				const size_t slashPos = it->second.getExtensionOrPartName().substr(1).find_last_of("/\\");
				if (slashPos != string::npos) {
					relFilePath = it->second.getExtensionOrPartName().substr(1).substr(0, slashPos + 1);
				}
				relFilePath += "_rels" + it->second.getExtensionOrPartName().substr(it->second.getExtensionOrPartName().find_last_of("/\\")) + ".rels";
				if (!package->fileExists(relFilePath)) {
					result += "The EpcExternalPartReference (aka HDF proxy) " + it->second.getExtensionOrPartName() + " does not look to be associated to any HDF files : there is no rel file for this object. It is going to be withdrawn.\n";
					continue;
				}
				epc::FileRelationship relFile;
				relFile.readFromString(package->extractFile(relFilePath));
				const vector<epc::Relationship>& allRels = relFile.getAllRelationship();
				COMMON_NS::AbstractObject* wrapper = nullptr;
				std::string target;
				for (size_t relIndex = 0; relIndex < allRels.size(); ++relIndex) {
					if (allRels[relIndex].getType().compare("http://schemas.energistics.org/package/2012/relationships/externalResource") == 0) {
						target = allRels[relIndex].getTarget();
						if (target.find("http://") == 0 || target.find("https://") == 0) {
							repo.setHdfProxyFactory(new HdfProxyROS3Factory());
						}
						wrapper = repo.addOrReplaceGsoapProxy(package->extractFile(it->second.getExtensionOrPartName().substr(1)), contentType);
						break;
					}
				}

				if (wrapper != nullptr) {
					static_cast<EML2_NS::AbstractHdfProxy*>(wrapper)->setRelativePath(target);
					static_cast<EML2_NS::AbstractHdfProxy*>(wrapper)->setOpeningMode(hdfPermissionAccess);
					static_cast<EML2_NS::AbstractHdfProxy*>(wrapper)->setRootPath(getStorageDirectory());
					repo.setDefaultHdfProxy(static_cast<EML2_NS::AbstractHdfProxy*>(wrapper));
				}
				else {
					result += "The EpcExternalPartReference (aka HDF proxy) " + it->second.getExtensionOrPartName() + " is either not XML valid or it does not contain any EPC external relationship entry towards an HDF5 file.\n";
				}
			}
			else {
				repo.addOrReplaceGsoapProxy(package->extractFile(it->second.getExtensionOrPartName().substr(1)), contentType);
			}
		}
	}

	repo.updateAllRelationships();

	// Validate properties
	const vector<RESQML2_NS::AbstractProperty*> allprops = repo.getDataObjects<RESQML2_NS::AbstractProperty>();
	for (size_t propIndex = 0; propIndex < allprops.size(); ++propIndex) {
		allprops[propIndex]->validate();
	}

	for (const auto& warning : repo.getWarnings()) {
		result += warning + '\n';
	}

	return result;
}

namespace {

	std::string extractUuidFromFileName(std::string fileName) {
		return fileName.substr(fileName.find_last_of('_') + 1, 36);
	}

}

std::string EpcDocument::deserializePartiallyInto(DataObjectRepository & repo, DataObjectRepository::openingMode hdfPermissionAccess)
{
	std::string result;
	for (const auto& warning : package->openForReading(filePath)) {
		result += warning + '\n';
	}

	// Read all RESQML objects
	const epc::FileContentType::ContentTypeMap contentTypes = package->getFileContentType().getAllContentType();
	// 14 equals "application/x-".size()
	for (epc::FileContentType::ContentTypeMap::const_iterator it = contentTypes.begin(); it != contentTypes.end(); ++it) {
		if (!it->second.isAssociatedToAnExtension) {
			std::string contentType = it->second.getContentTypeString();
			if (contentType.find("resqml", 14) != std::string::npos ||
				contentType.find("eml", 14) != std::string::npos ||
				contentType.find("witsml", 14) != std::string::npos ||
				contentType.find("prodml", 14) != std::string::npos)
			{
				if (contentType == "application/x-resqml+xml;version=2.0;type=obj_EpcExternalPartReference") {
					result += "The content type " + contentType + " should belong to EML20 and not to RESQML20 since obj_EpcExternalPartReference is part of COMMON 2.0 and not part of RESQML 2.0.\n";
					contentType = "application/x-eml+xml;version=2.0;type=obj_EpcExternalPartReference";
				}
				if (contentType == "application/x-eml+xml;version=2.0;type=obj_EpcExternalPartReference") {
					// Look for the relative path of the HDF file
					string relFilePath = "";
					const size_t slashPos = it->second.getExtensionOrPartName().substr(1).find_last_of("/\\");
					if (slashPos != string::npos) {
						relFilePath = it->second.getExtensionOrPartName().substr(1).substr(0, slashPos + 1);
					}
					relFilePath += "_rels" + it->second.getExtensionOrPartName().substr(it->second.getExtensionOrPartName().find_last_of("/\\")) + ".rels";
					if (!package->fileExists(relFilePath)) {
						result += "The HDF proxy " + it->second.getExtensionOrPartName() + " does not look to be associated to any HDF files : there is no rel file for this object. It is going to be withdrawn.\n";
						continue;
					}
					epc::FileRelationship relFile;
					relFile.readFromString(package->extractFile(relFilePath));
					const vector<epc::Relationship>& allRels = relFile.getAllRelationship();
					COMMON_NS::AbstractObject* wrapper = nullptr;
					for (size_t relIndex = 0; relIndex < allRels.size(); ++relIndex) {
						if (allRels[relIndex].getType().compare("http://schemas.energistics.org/package/2012/relationships/externalResource") == 0) {
							const std::string target = allRels[relIndex].getTarget();
							if (target.find("http://") == 0 || target.find("https://") == 0) {
								repo.setHdfProxyFactory(new HdfProxyROS3Factory());
							}
							else {
								repo.setHdfProxyFactory(new HdfProxyFactory());
							}
							wrapper = repo.addOrReplaceGsoapProxy(package->extractFile(it->second.getExtensionOrPartName().substr(1)), contentType);
							static_cast<EML2_0_NS::HdfProxy*>(wrapper)->setRelativePath(target);
							break;
						}
					}

					static_cast<EML2_0_NS::HdfProxy*>(wrapper)->setRootPath(getStorageDirectory());
					static_cast<EML2_0_NS::HdfProxy*>(wrapper)->setOpeningMode(hdfPermissionAccess);

					repo.setDefaultHdfProxy(static_cast<EML2_NS::AbstractHdfProxy*>(wrapper));
				}
				else {
					repo.createPartial(extractUuidFromFileName(it->first), "Partial title", contentType);
				}
			}
		}
	}

	deserializeRelFiles(repo);

	return result;
}

void EpcDocument::deserializeRelFiles(DataObjectRepository & repo)
{
	// Read all RESQML objects
	const epc::FileContentType::ContentTypeMap contentTypes = package->getFileContentType().getAllContentType();
	// 14 equals "application/x-".size()
	for (epc::FileContentType::ContentTypeMap::const_iterator it = contentTypes.begin(); it != contentTypes.end(); ++it)
	{
		std::string contentType = it->second.getContentTypeString();
		if (contentType.find("resqml", 14) != std::string::npos ||
			contentType.find("eml", 14) != std::string::npos ||
			contentType.find("witsml", 14) != std::string::npos)
		{
			// Look for the relative path of the file
			string relFilePath = "";
			const size_t slashPos = it->second.getExtensionOrPartName().substr(1).find_last_of("/\\");
			if (slashPos != string::npos) {
				relFilePath = it->second.getExtensionOrPartName().substr(1).substr(0, slashPos + 1);
			}
			relFilePath += "_rels" + it->second.getExtensionOrPartName().substr(it->second.getExtensionOrPartName().find_last_of("/\\")) + ".rels";
			if (package->fileExists(relFilePath)) {
				// Read Relationshsips
				epc::FileRelationship relFile;
				relFile.readFromString(package->extractFile(relFilePath));
				const vector<epc::Relationship>& allRels = relFile.getAllRelationship();
				for (size_t relIndex = 0; relIndex < allRels.size(); ++relIndex) {
					const epc::Relationship& rel = allRels[relIndex];
					if (rel.getType() == "http://schemas.energistics.org/package/2012/relationships/destinationObject") {
						COMMON_NS::AbstractObject* source = repo.getDataObjectByUuid(extractUuidFromFileName(it->first));
						COMMON_NS::AbstractObject* destination = repo.getDataObjectByUuid(extractUuidFromFileName(rel.getTarget()));
						repo.addRelationship(source, destination);
					}
				}
			}
		}
	}
}

string EpcDocument::getStorageDirectory() const
{
	const size_t slashPos = filePath.find_last_of("/\\");
	return slashPos != string::npos ? filePath.substr(0, slashPos + 1) : "";
}

string EpcDocument::getName() const
{
	// Remove the directories from the file path
	const size_t slashPos = filePath.find_last_of("/\\");
	const string nameSuffixed = slashPos != string::npos ? filePath.substr(slashPos + 1, filePath.size()) : filePath;

	// Remove the extension
	return nameSuffixed.substr(0, nameSuffixed.find_last_of("."));
}

unordered_map< string, string > & EpcDocument::getExtendedCoreProperty()
{
	return package->getExtendedCoreProperty();
}

void EpcDocument::setExtendedCoreProperty(const std::string & key, const std::string & value)
{
	package->getExtendedCoreProperty()[key] = value;
}

unsigned int EpcDocument::getExtendedCorePropertyCount() const
{
	return package->getExtendedCoreProperty().size();
}

std::string EpcDocument::getExtendedCoreProperty(const std::string & key)
{
	if (package->getExtendedCoreProperty().find(key) != package->getExtendedCoreProperty().end()) {
		return (package->getExtendedCoreProperty())[key];
	}

	return "";
}

std::string EpcDocument::resolvePartial(AbstractObject const * partialObj) const
{
	if (!package->isOpenedForReading()) {
		package->openForReading(filePath);
	}

	const epc::FileContentType::ContentTypeMap contentTypes = package->getFileContentType().getAllContentType();
	// 14 equals "application/x-".size()
	for (epc::FileContentType::ContentTypeMap::const_iterator it = contentTypes.begin(); it != contentTypes.end(); ++it)
	{
		if (it->first.find(partialObj->getUuid()) != std::string::npos)
		{
			return package->extractFile(it->second.getExtensionOrPartName().substr(1));
		}
	}

	return "";
}
