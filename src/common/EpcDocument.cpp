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

#include <stdexcept>

#include <H5Epublic.h>
#include <H5Fpublic.h>

#include <zip.h>

#include "HdfProxyROS3Factory.h"

#include "../epc/Relationship.h"
#include "../epc/FilePart.h"

#include "../eml2_3/HdfProxy.h"

#include "../resqml2/AbstractProperty.h"
#include "../resqml2/AbstractRepresentation.h"
#include "../resqml2/WellboreMarkerFrameRepresentation.h"

#include "../resqml2_0_1/DiscreteProperty.h"
#include "../resqml2_0_1/PropertySet.h"
#include "../resqml2_0_1/WellboreMarker.h"

#include "../witsml2_1/Log.h"
#include "../witsml2_1/Channel.h"
#include "../witsml2_1/ChannelSet.h"

using namespace std;
using namespace gsoap_resqml2_0_1;
using namespace COMMON_NS;

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
	std::vector<epc::Relationship> getAllEpcRelationships(const DataObjectRepository& repo, COMMON_NS::AbstractObject const* dataObj) {
		std::vector<epc::Relationship> result;

		// Special case for WellboreMarkerFrameRepresentation and byValue rel.
		if (dynamic_cast<RESQML2_NS::WellboreMarkerFrameRepresentation const*>(dataObj) != nullptr) {
			for (const auto* srcMarkerFrame : repo.getSourceObjects(dataObj)) {
				if (dynamic_cast<RESQML2_NS::WellboreMarker const*>(srcMarkerFrame) == nullptr) {
					epc::Relationship relRep("../" + srcMarkerFrame->getPartNameInEpcDocument(), "", srcMarkerFrame->getUuid());
					relRep.setSourceObjectType();
					result.push_back(relRep);
				}
				else {
					for (const auto* srcMarker : repo.getSourceObjects(srcMarkerFrame)) {
						if (!srcMarker->isPartial()) {
							epc::Relationship relRep("../" + srcMarker->getPartNameInEpcDocument(), "", srcMarker->getUuid());
							relRep.setSourceObjectType();
							result.push_back(relRep);
						}
					}
					for (const auto* targetMarker : repo.getTargetObjects(srcMarkerFrame)) {
						if (!targetMarker->isPartial() &&
							dynamic_cast<RESQML2_NS::WellboreMarkerFrameRepresentation const*>(targetMarker) == nullptr) {
							epc::Relationship relRep("../" + targetMarker->getPartNameInEpcDocument(), "", targetMarker->getUuid());
							relRep.setDestinationObjectType();
							result.push_back(relRep);
						}
					}
				}
			}

			for (const auto* targetMarkerFrame : repo.getTargetObjects(dataObj)) {
				if (!targetMarkerFrame->isPartial()) {
					epc::Relationship relRep("../" + targetMarkerFrame->getPartNameInEpcDocument(), "", targetMarkerFrame->getUuid());
					relRep.setDestinationObjectType();
					result.push_back(relRep);
				}
			}

			return result;
		}

		// More general case.
		const std::vector<COMMON_NS::AbstractObject*>& srcObj = repo.getSourceObjects(dataObj);
		for (size_t index = 0; index < srcObj.size(); ++index) {
			if (!srcObj[index]->isPartial()) {
				if (dynamic_cast<RESQML2_NS::WellboreMarker*>(srcObj[index]) == nullptr) {
					epc::Relationship relRep("../" + srcObj[index]->getPartNameInEpcDocument(), "", srcObj[index]->getUuid());
					relRep.setSourceObjectType();
					result.push_back(relRep);
				}
				else {
					const std::vector<COMMON_NS::AbstractObject*>& srcMarkers = repo.getSourceObjects(srcObj[index]);
					for (size_t index2 = 0; index2 < srcMarkers.size(); ++index2) {
						if (!srcMarkers[index2]->isPartial()) {
							epc::Relationship relRep("../" + srcMarkers[index2]->getPartNameInEpcDocument(), "", srcMarkers[index2]->getUuid());
							relRep.setSourceObjectType();
							result.push_back(relRep);
						}
					}
					auto* markerFrame = static_cast<RESQML2_NS::WellboreMarker*>(srcObj[index])->getWellboreMarkerFrameRepresentation();
					epc::Relationship relRep("../" + markerFrame->getPartNameInEpcDocument(), "", markerFrame->getUuid());
					relRep.setSourceObjectType();
					result.push_back(relRep);
				}
			}
		}

		if (dynamic_cast<WITSML2_1_NS::Log const*>(dataObj) == nullptr &&
			dynamic_cast<WITSML2_1_NS::ChannelSet const*>(dataObj) == nullptr) {
			for (COMMON_NS::AbstractObject* targetObj : repo.getTargetObjects(dataObj)) {
				if (!targetObj->isPartial()) {
					if (dynamic_cast<RESQML2_NS::WellboreMarker*>(targetObj) == nullptr) {
						epc::Relationship relRep("../" + targetObj->getPartNameInEpcDocument(), "", targetObj->getUuid());
						relRep.setDestinationObjectType();
						result.push_back(relRep);
					}
					else {
						for (COMMON_NS::AbstractObject* markerTarget : repo.getTargetObjects(targetObj)) {
							if (!markerTarget->isPartial() &&
								dynamic_cast<RESQML2_NS::WellboreMarkerFrameRepresentation*>(markerTarget) == nullptr) {
								epc::Relationship relRep("../" + markerTarget->getPartNameInEpcDocument(), "", markerTarget->getUuid());
								relRep.setDestinationObjectType();
								result.push_back(relRep);
							}
						}
					}
				}
				else {
					EML2_3_NS::HdfProxy const* eml23_hdfProxy = dynamic_cast<EML2_3_NS::HdfProxy const*>(targetObj);
					if (eml23_hdfProxy != nullptr) {
						epc::Relationship relExt(eml23_hdfProxy->getRelativePath(), "", "Hdf5File", false);
						relExt.setExternalResourceType();
						result.push_back(relExt);
					}
				}
			}
		}
		else {
			for (COMMON_NS::AbstractObject* targetObj : repo.getTargetObjects(dataObj)) {
				if (!targetObj->isPartial()) {
					if (dynamic_cast<WITSML2_1_NS::ChannelSet*>(targetObj) != nullptr) {
						for (WITSML2_1_NS::Channel* channel : static_cast<WITSML2_1_NS::ChannelSet*>(targetObj)->getChannels()) {
							for (COMMON_NS::AbstractObject* channelTarget : repo.getTargetObjects(channel)) {
								if (!channelTarget->isPartial()) {
									epc::Relationship relRep("../" + channelTarget->getPartNameInEpcDocument(), "", channelTarget->getUuid());
									relRep.setDestinationObjectType();
									result.push_back(relRep);
								}
							}
						}
					}
					else if (dynamic_cast<WITSML2_1_NS::Channel*>(targetObj) != nullptr) {
						for (COMMON_NS::AbstractObject* channelTarget : repo.getTargetObjects(targetObj)) {
							if (!channelTarget->isPartial()) {
								epc::Relationship relRep("../" + channelTarget->getPartNameInEpcDocument(), "", channelTarget->getUuid());
								relRep.setDestinationObjectType();
								result.push_back(relRep);
							}
						}
					}
					else if (!targetObj->isPartial()) {
						epc::Relationship relRep("../" + targetObj->getPartNameInEpcDocument(), "", targetObj->getUuid());
						relRep.setDestinationObjectType();
						result.push_back(relRep);
					}
				}
			}
		}

		// External part
		EML2_NS::AbstractHdfProxy const* hdfProxy = dynamic_cast<EML2_NS::AbstractHdfProxy const*>(dataObj);
		if (hdfProxy != nullptr && !hdfProxy->isPartial()) {
			epc::Relationship relExt(hdfProxy->getRelativePath(), "", "Hdf5File", false);
			relExt.setExternalResourceType();
			result.push_back(relExt);
		}

		return result;
	}
}

namespace {
	RESQML2_0_1_NS::DiscreteProperty* getOrCreateFakeProperty(DataObjectRepository& repo) {
		RESQML2_0_1_NS::DiscreteProperty* fakeProp = repo.getDataObjectByUuid<RESQML2_0_1_NS::DiscreteProperty>(RESQML2_0_1_NS::PropertySet::FAKE_PROP_UUID);
		if (fakeProp != nullptr) { return fakeProp; }

		auto* firstRep = repo.getDataObjects<RESQML2_NS::AbstractRepresentation>().at(0);
		fakeProp = repo.createDiscreteProperty(
			firstRep, RESQML2_0_1_NS::PropertySet::FAKE_PROP_UUID, "Fake Property", 1, gsoap_eml2_3::eml23__IndexableElement::representation, gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind::index);
		fakeProp->pushBackIntegerConstantArrayOfValues(-1, 1);

		return fakeProp;
	}

	void addFakePropertyToEmptyPropertySet(DataObjectRepository& repo) {
		for (auto* propSet : repo.getDataObjects<RESQML2_0_1_NS::PropertySet>()) {
			if (propSet->getProperties().empty()) {
				//Add a fake property since the RESQML2.0.1 does not allow empty property set
				propSet->pushBackProperty(getOrCreateFakeProperty(repo));
			}
		}
	}
}

void EpcDocument::serializeFrom(DataObjectRepository& repo)
{
	addFakePropertyToEmptyPropertySet(repo);

	package->openForWriting(filePath, APPEND_STATUS_CREATE);

	for (auto const& uuidDataobjectPair : repo.getDataObjects()) {
		for (auto const& dataobject : uuidDataobjectPair.second) {
			if (!dataobject->isPartial() &&
				dynamic_cast<RESQML2_0_1_NS::WellboreMarker*>(dataobject.get()) == nullptr &&
				(dynamic_cast<WITSML2_1_NS::ChannelSet*>(dataobject.get()) == nullptr || static_cast<WITSML2_1_NS::ChannelSet*>(dataobject.get())->getLogs().empty()) &&
				(dynamic_cast<WITSML2_1_NS::Channel*>(dataobject.get()) == nullptr || static_cast<WITSML2_1_NS::Channel*>(dataobject.get())->getChannelSets().empty())) {
				// Dataobject
				epc::FilePart* const fp = package->createPart(dataobject->serializeIntoString(), dataobject->getPartNameInEpcDocument());

				// Relationships
				for (const auto& rel : getAllEpcRelationships(repo, dataobject.get())) {
					fp->addRelationship(rel);
				}

				// Content Type entry
				package->addContentType(epc::ContentType(false, dataobject->getContentType(), dataobject->getPartNameInEpcDocument()));
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

	for (const auto& contentTypeEntry : package->getFileContentType().getAllContentType()) {
		std::string contentType = contentTypeEntry.second.getContentTypeString();
		// 14 equals "application/x-".size()
		if (contentType.find("resqml", 14) != std::string::npos ||
			contentType.find("eml", 14) != std::string::npos ||
			contentType.find("witsml", 14) != std::string::npos ||
			contentType.find("prodml", 14) != std::string::npos) {
			if (contentType == "application/x-resqml+xml;version=2.0;type=obj_EpcExternalPartReference") {
				result += "The content type " + contentType + " should belong to EML20 and not to RESQML20 since obj_EpcExternalPartReference is part of COMMON 2.0 and not part of RESQML 2.0.\n";
				contentType = "application/x-eml+xml;version=2.0;type=obj_EpcExternalPartReference";
			}
			COMMON_NS::AbstractObject* wrapper = nullptr;
			if (contentType == "application/x-eml+xml;version=2.0;type=obj_EpcExternalPartReference") {
				// Look for the relative path of the HDF file
				string relFilePath = "";
				const size_t slashPos = contentTypeEntry.second.getExtensionOrPartName().substr(1).find_last_of("/\\");
				if (slashPos != string::npos) {
					relFilePath = contentTypeEntry.second.getExtensionOrPartName().substr(1).substr(0, slashPos + 1);
				}
				relFilePath += "_rels" + contentTypeEntry.second.getExtensionOrPartName().substr(contentTypeEntry.second.getExtensionOrPartName().find_last_of("/\\")) + ".rels";
				if (!package->fileExists(relFilePath)) {
					result += "The EpcExternalPartReference (aka HDF proxy) " + contentTypeEntry.second.getExtensionOrPartName() + " does not look to be associated to any HDF file : there is no rel file for this object. It is going to be withdrawn.\n";
					continue;
				}
				epc::FileRelationship relFile;
				relFile.readFromString(package->extractFile(relFilePath));
				std::string target;
				for (const auto& rel : relFile.getAllRelationship()) {
					if (rel.getType().compare("http://schemas.energistics.org/package/2012/relationships/externalResource") == 0) {
						target = rel.getTarget();
						if (target.find("http://") == 0 || target.find("https://") == 0) {
							repo.setHdfProxyFactory(new HdfProxyROS3Factory());
						}
						wrapper = repo.addOrReplaceGsoapProxy(package->extractFile(contentTypeEntry.second.getExtensionOrPartName().substr(1)), contentType, filePath);
						break;
					}
				}

				if (wrapper != nullptr) {
					static_cast<EML2_NS::AbstractHdfProxy*>(wrapper)->setRelativePath(target);
					static_cast<EML2_NS::AbstractHdfProxy*>(wrapper)->setOpeningMode(hdfPermissionAccess);
					static_cast<EML2_NS::AbstractHdfProxy*>(wrapper)->setRootPath(getStorageDirectory());
				}
				else {
					result += "The EpcExternalPartReference (aka HDF proxy) " + contentTypeEntry.second.getExtensionOrPartName() + " is either not XML valid or it does not contain any EPC external relationship entry towards an HDF5 file.\n";
				}
			}
			else {
				wrapper = repo.addOrReplaceGsoapProxy(package->extractFile(contentTypeEntry.second.getExtensionOrPartName().substr(1)), contentType, filePath);
			}
		}
		else if (contentType.find("application/vnd.openxmlformats-package") == std::string::npos &&
			contentType != "application/x-extended-core-properties+xml") {
			result += "The content type " + contentType + " is not recognized by FESAPI and will be ignored.";
		}
	}

	repo.updateAllRelationships();

	// Validate properties
	for (auto* prop : repo.getDataObjects<RESQML2_NS::AbstractProperty>()) {
		if (!prop->isPartial()) {
			prop->validate();
		}
	}

	for (const auto& warning : repo.getWarnings()) {
		result += warning + '\n';
	}

	for (auto* hdfProxy : repo.getHdfProxySet()) {
		hdfProxy->setOpeningMode(hdfPermissionAccess); // Must repeat this setter in case of RESQML2.2 which is not an obj_EpcExternalPartReference
	}

	package->close();

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

	// 14 equals "application/x-".size()
	for (auto it : package->getFileContentType().getAllContentType()) {
		if (!it.second.isAssociatedToAnExtension) {
			std::string contentType = it.second.getContentTypeString();
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
					const size_t slashPos = it.second.getExtensionOrPartName().substr(1).find_last_of("/\\");
					if (slashPos != string::npos) {
						relFilePath = it.second.getExtensionOrPartName().substr(1).substr(0, slashPos + 1);
					}
					relFilePath += "_rels" + it.second.getExtensionOrPartName().substr(it.second.getExtensionOrPartName().find_last_of("/\\")) + ".rels";
					if (!package->fileExists(relFilePath)) {
						result += "The HDF proxy " + it.second.getExtensionOrPartName() + " does not look to be associated to any HDF files : there is no rel file for this object. It is going to be withdrawn.\n";
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
							wrapper = repo.addOrReplaceGsoapProxy(package->extractFile(it.second.getExtensionOrPartName().substr(1)), contentType, filePath);
							static_cast<EML2_0_NS::HdfProxy*>(wrapper)->setRelativePath(target);
							break;
						}
					}
					if (wrapper == nullptr) {
						throw std::invalid_argument("The EpcExternalPartReference (aka HDF proxy) has not got any standard relationship towards an HDF5 file.");
					}

					static_cast<EML2_0_NS::HdfProxy*>(wrapper)->setRootPath(getStorageDirectory());
					static_cast<EML2_0_NS::HdfProxy*>(wrapper)->setOpeningMode(hdfPermissionAccess);
				}
				else {
					repo.createPartial(extractUuidFromFileName(it.first), "Partial title", contentType);
				}
			}
		}
	}

	deserializeRelFiles(repo);

	for (auto* hdfProxy : repo.getHdfProxySet()){
		hdfProxy->setOpeningMode(hdfPermissionAccess); // Must repeat this setter in case of RESQML2.2 which is not an obj_EpcExternalPartReference
	}

	package->close();

	return result;
}

void EpcDocument::deserializeRelFiles(DataObjectRepository & repo)
{
	// 14 equals "application/x-".size()
	for (auto it : package->getFileContentType().getAllContentType()) {
		std::string contentType = it.second.getContentTypeString();
		if (contentType.find("resqml", 14) != std::string::npos ||
			contentType.find("eml", 14) != std::string::npos ||
			contentType.find("witsml", 14) != std::string::npos)
		{
			// Look for the relative path of the file
			string relFilePath = "";
			const size_t slashPos = it.second.getExtensionOrPartName().substr(1).find_last_of("/\\");
			if (slashPos != string::npos) {
				relFilePath = it.second.getExtensionOrPartName().substr(1).substr(0, slashPos + 1);
			}
			relFilePath += "_rels" + it.second.getExtensionOrPartName().substr(it.second.getExtensionOrPartName().find_last_of("/\\")) + ".rels";
			if (package->fileExists(relFilePath)) {
				// Read Relationshsips
				epc::FileRelationship relFile;
				relFile.readFromString(package->extractFile(relFilePath));
				const vector<epc::Relationship>& allRels = relFile.getAllRelationship();
				for (size_t relIndex = 0; relIndex < allRels.size(); ++relIndex) {
					const epc::Relationship& rel = allRels[relIndex];
					if (rel.getType() == "http://schemas.energistics.org/package/2012/relationships/destinationObject") {
						COMMON_NS::AbstractObject* source = repo.getDataObjectByUuid(extractUuidFromFileName(it.first));
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

uint64_t EpcDocument::getExtendedCorePropertyCount() const
{
	return package->getExtendedCoreProperty().size();
}

std::string EpcDocument::getExtendedCoreProperty(const std::string & key) const
{
	auto entry = package->getExtendedCoreProperty().find(key);
	return entry != package->getExtendedCoreProperty().end()
		? entry->second
		: "";
}

std::string EpcDocument::resolvePartial(AbstractObject const * partialObj) const
{
	if (!package->isOpenedForReading()) {
		package->openForReading(filePath);
	}

	// 14 equals "application/x-".size()
	for (auto it : package->getFileContentType().getAllContentType()) {
		if (it.first.find(partialObj->getUuid()) != std::string::npos)
		{
			std::string result = package->extractFile(it.second.getExtensionOrPartName().substr(1));
			package->close();
			return result;
		}
	}

	package->close();
	return "";
}
