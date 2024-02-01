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
#include "SealedVolumeFrameworkRepresentation.h"

#include <numeric>

#include <hdf5.h>

#include "../eml2/AbstractHdfProxy.h"

#include "../resqml2/StratigraphicColumnRankInterpretation.h"
#include "../resqml2/SealedSurfaceFrameworkRepresentation.h"
#include "../resqml2/StratigraphicUnitInterpretation.h"

using namespace std;
using namespace RESQML2_2_NS;
using namespace gsoap_eml2_3;

SealedVolumeFrameworkRepresentation::SealedVolumeFrameworkRepresentation(RESQML2_NS::StratigraphicColumnRankInterpretation* interp,
	const std::string & guid,
	const std::string & title,
	RESQML2_NS::SealedSurfaceFrameworkRepresentation* ssf)
{
	if (interp == nullptr) {
		throw invalid_argument("The Stratigraphic Column Rank Interpretation cannot be null.");
	}
	if (ssf == nullptr) {
		throw invalid_argument("The Sealed Surface Framework Representation cannot be null.");
	}

	// proxy constructor
	gsoapProxy2_3 = soap_new_resqml22__SealedVolumeFrameworkRepresentation(interp->getGsoapContext());
	_resqml22__SealedVolumeFrameworkRepresentation* orgRep = static_cast<_resqml22__SealedVolumeFrameworkRepresentation*>(gsoapProxy2_3);

	orgRep->IsHomogeneous = true;
	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "");

	interp->getRepository()->addDataObject(this);
	// XML relationships
	setInterpretation(interp);
	setSealedSurfaceFramework(ssf);
}

void SealedVolumeFrameworkRepresentation::setXmlSealedSurfaceFramework(RESQML2_NS::SealedSurfaceFrameworkRepresentation* ssf)
{
	if (ssf == nullptr) {
		throw invalid_argument("Cannot set a null SealedSurfaceFrameworkRepresentation");
	}

	static_cast<_resqml22__SealedVolumeFrameworkRepresentation*>(gsoapProxy2_3)->BasedOn = ssf->newEml23Reference();
}

void SealedVolumeFrameworkRepresentation::setXmlInterpretationOfVolumeRegion(uint64_t regionIndex, RESQML2_NS::StratigraphicUnitInterpretation * stratiUnitInterp)
{
	if (stratiUnitInterp == nullptr) {
		throw invalid_argument("Cannot set a null strati Unit Interpretation");
	}
	static_cast<_resqml22__SealedVolumeFrameworkRepresentation*>(gsoapProxy2_3)->Regions.at(regionIndex)->Represents = stratiUnitInterp->newEml23Reference();
}

gsoap_eml2_3::resqml22__VolumeShell* SealedVolumeFrameworkRepresentation::createVolumeShell(size_t regionIndex, size_t shellIndex,
	uint64_t shellFaceCount,
	unsigned int const* faceRepresentationIndices, unsigned int const* faceRepPatchIndices, bool const* faceSide)
{
	if (shellFaceCount == 0) {
		throw invalid_argument("Cannot create a shell with has got a face count of zero.");
	}
	auto* hdfProxy = getRepository()->getDefaultHdfProxy();
	if (hdfProxy == nullptr) {
		throw std::invalid_argument("A (default) HDF Proxy must be provided.");
	}

	resqml22__VolumeShell* externalShell = soap_new_resqml22__VolumeShell(gsoapProxy2_3->soap);

	// XML
	eml23__IntegerExternalArray* representationIndices = soap_new_eml23__IntegerExternalArray(gsoapProxy2_3->soap);
	representationIndices->NullValue = (std::numeric_limits<unsigned int>::max)();
	representationIndices->Values = soap_new_eml23__ExternalDataArray(gsoapProxy2_3->soap);
	representationIndices->Values->ExternalDataArrayPart.push_back(createExternalDataArrayPart(getHdfGroup() + "/RepresentationIndices_Region" + std::to_string(regionIndex) + "_Shell" + std::to_string(shellIndex), shellFaceCount, hdfProxy));
	externalShell->RepresentationIndices = representationIndices;

	eml23__IntegerExternalArray* patchIndicesOfRepresentation = soap_new_eml23__IntegerExternalArray(gsoapProxy2_3->soap);
	patchIndicesOfRepresentation->NullValue = (std::numeric_limits<unsigned int>::max)();
	patchIndicesOfRepresentation->Values = soap_new_eml23__ExternalDataArray(gsoapProxy2_3->soap);
	patchIndicesOfRepresentation->Values->ExternalDataArrayPart.push_back(createExternalDataArrayPart(getHdfGroup() + "/PatchIndicesOfRepresentation_Region" + std::to_string(regionIndex) + "_Shell" + std::to_string(shellIndex), shellFaceCount, hdfProxy));
	externalShell->PatchIndicesOfRepresentation = patchIndicesOfRepresentation;

	eml23__BooleanExternalArray* sideIsPlus = soap_new_eml23__BooleanExternalArray(gsoapProxy2_3->soap);
	sideIsPlus->Values = soap_new_eml23__ExternalDataArray(gsoapProxy2_3->soap);
	sideIsPlus->Values->ExternalDataArrayPart.push_back(createExternalDataArrayPart(getHdfGroup() + "/SideIsPlus_Region" + std::to_string(regionIndex) + "_Shell" + std::to_string(shellIndex), shellFaceCount, hdfProxy));
	externalShell->SideIsPlus = sideIsPlus;

	// HDF
	hdfProxy->writeArrayNd(getHdfGroup(),
		"RepresentationIndices_Region" + std::to_string(regionIndex) + "_Shell" + std::to_string(shellIndex),
		COMMON_NS::AbstractObject::numericalDatatypeEnum::UINT32,
		faceRepresentationIndices,
		&shellFaceCount, 1);
	hdfProxy->writeArrayNd(getHdfGroup(),
		"PatchIndicesOfRepresentation_Region" + std::to_string(regionIndex) + "_Shell" + std::to_string(shellIndex),
		COMMON_NS::AbstractObject::numericalDatatypeEnum::UINT32,
		faceRepPatchIndices,
		&shellFaceCount, 1);
	hdfProxy->writeArrayNd(getHdfGroup(),
		"SideIsPlus_Region" + std::to_string(regionIndex) + "_Shell" + std::to_string(shellIndex),
		COMMON_NS::AbstractObject::numericalDatatypeEnum::INT8,
		faceSide,
		&shellFaceCount, 1);

	return externalShell;
}

void SealedVolumeFrameworkRepresentation::pushBackVolumeRegion(RESQML2_NS::StratigraphicUnitInterpretation * stratiUnitInterp,
	uint64_t externalShellFaceCount,
	unsigned int const* faceRepresentationIndices, unsigned int const* faceRepPatchIndices, bool const* faceSide)
{
	// Region
	resqml22__VolumeRegion* region = soap_new_resqml22__VolumeRegion(gsoapProxy2_3->soap);
	static_cast<_resqml22__SealedVolumeFrameworkRepresentation*>(gsoapProxy2_3)->Regions.push_back(region);
	setInterpretationOfVolumeRegion(static_cast<_resqml22__SealedVolumeFrameworkRepresentation*>(gsoapProxy2_3)->Regions.size() - 1, stratiUnitInterp);

	// External shell
	region->ExternalShell = createVolumeShell(static_cast<_resqml22__SealedVolumeFrameworkRepresentation*>(gsoapProxy2_3)->Regions.size() - 1, 0, externalShellFaceCount,
		faceRepresentationIndices, faceRepPatchIndices, faceSide);
}

void SealedVolumeFrameworkRepresentation::pushBackInternalShell(uint64_t regionIndex,
	uint64_t internalShellFaceCount,
	unsigned int const* faceRepresentationIndices, unsigned int const* faceRepPatchIndices, bool const* faceSide)
{
	auto* region = getRegion(regionIndex);
	region->InternalShells.push_back(createVolumeShell(regionIndex, region->InternalShells.size()+1, internalShellFaceCount,
		faceRepresentationIndices, faceRepPatchIndices, faceSide));
}

COMMON_NS::DataObjectReference SealedVolumeFrameworkRepresentation::getSealedStructuralFrameworkDor() const
{
	return COMMON_NS::DataObjectReference(static_cast<gsoap_eml2_3::_resqml22__SealedVolumeFrameworkRepresentation*>(gsoapProxy2_3)->BasedOn);
}

gsoap_eml2_3::resqml22__VolumeRegion* SealedVolumeFrameworkRepresentation::getRegion(uint64_t regionIndex) const
{
	return static_cast<gsoap_eml2_3::_resqml22__SealedVolumeFrameworkRepresentation*>(gsoapProxy2_3)->Regions.at(regionIndex);
}

COMMON_NS::DataObjectReference SealedVolumeFrameworkRepresentation::getStratiUnitInterpDor(uint64_t regionIndex) const
{
	return COMMON_NS::DataObjectReference(getRegion(regionIndex)->Represents);
}

uint64_t SealedVolumeFrameworkRepresentation::getRegionCount() const
{
	return static_cast<_resqml22__SealedVolumeFrameworkRepresentation*>(gsoapProxy2_3)->Regions.size();
}

uint64_t SealedVolumeFrameworkRepresentation::getInternalShellCount(uint64_t regionIndex) const
{
	return getRegion(regionIndex)->InternalShells.size();
}

gsoap_eml2_3::resqml22__VolumeShell* SealedVolumeFrameworkRepresentation::getRegionExternalShell(uint64_t regionIndex) const
{
	return getRegion(regionIndex)->ExternalShell;
}

gsoap_eml2_3::resqml22__VolumeShell* SealedVolumeFrameworkRepresentation::getRegionInternalShell(uint64_t regionIndex, uint64_t internalShellIndex) const
{
	return getRegion(regionIndex)->InternalShells.at(internalShellIndex);
}

uint64_t SealedVolumeFrameworkRepresentation::getFaceCountOfExternalShell(uint64_t regionIndex) const
{
	uint64_t result = 0;

	gsoap_eml2_3::resqml22__VolumeShell* shell = getRegionExternalShell(regionIndex);
	for (auto const* daPart : shell->SideIsPlus->Values->ExternalDataArrayPart) {
		result += std::accumulate(std::begin(daPart->Count), std::end(daPart->Count), static_cast<LONG64>(1), std::multiplies<LONG64>()); 
	}
	return result;
}

uint64_t SealedVolumeFrameworkRepresentation::getFaceCountOfInternalShell(uint64_t regionIndex, uint64_t internalShellIndex) const
{
	uint64_t result = 0;

	gsoap_eml2_3::resqml22__VolumeShell* shell = getRegionInternalShell(regionIndex, internalShellIndex);
	for (auto const* daPart : shell->SideIsPlus->Values->ExternalDataArrayPart) {
		result += std::accumulate(std::begin(daPart->Count), std::end(daPart->Count), static_cast<LONG64>(1), std::multiplies<LONG64>());
	}
	return result;
}

void SealedVolumeFrameworkRepresentation::loadShell(uint64_t regionIndex, uint64_t internalShellIndex)
{
	auto tmpPair = std::make_pair(regionIndex, internalShellIndex);
	if (loadedShell_ != tmpPair) {
		loadedShell_ = tmpPair;

		gsoap_eml2_3::resqml22__VolumeShell const* shell = internalShellIndex == (std::numeric_limits<uint64_t>::max)()
			? getRegionExternalShell(regionIndex)
			: getRegionInternalShell(regionIndex, internalShellIndex);
		const auto faceCount = internalShellIndex == (std::numeric_limits<uint64_t>::max)()
			? getFaceCountOfExternalShell(regionIndex)
			: getFaceCountOfInternalShell(regionIndex, internalShellIndex);

		faceRepresentationIndices_.reset(new unsigned int[faceCount]);
		readArrayNdOfUInt32Values(shell->RepresentationIndices, faceRepresentationIndices_.get());

		faceRepPatchIndices_.reset(new unsigned int[faceCount]);
		readArrayNdOfUInt32Values(shell->PatchIndicesOfRepresentation, faceRepPatchIndices_.get());

		faceSide_.reset(new int8_t[faceCount]);
		readArrayNdOfBooleanValues(shell->SideIsPlus, faceSide_.get());
	}
}

RESQML2_NS::AbstractRepresentation* SealedVolumeFrameworkRepresentation::getRepOfExternalShellFace(uint64_t regionIndex, uint64_t faceIndex)
{
	loadShell(regionIndex);
	return getRepresentation(faceRepresentationIndices_[faceIndex]);
}

RESQML2_NS::AbstractRepresentation* SealedVolumeFrameworkRepresentation::getRepOfInternalShellFace(uint64_t regionIndex, uint64_t internalShellIndex, uint64_t faceIndex)
{
	loadShell(regionIndex, internalShellIndex);
	return getRepresentation(faceRepresentationIndices_[faceIndex]);
}

uint64_t SealedVolumeFrameworkRepresentation::getRepPatchIndexOfExternalShellFace(uint64_t regionIndex, uint64_t faceIndex)
{
	loadShell(regionIndex);
	return faceRepPatchIndices_[faceIndex];
}

uint64_t SealedVolumeFrameworkRepresentation::getRepPatchIndexOfInternalShellFace(uint64_t regionIndex, uint64_t internalShellIndex, uint64_t faceIndex)
{
	loadShell(regionIndex, internalShellIndex);
	return faceRepPatchIndices_[faceIndex];
}

bool SealedVolumeFrameworkRepresentation::getSideFlagOfExternalShellFace(uint64_t regionIndex, uint64_t faceIndex)
{
	loadShell(regionIndex);
	return faceSide_[faceIndex];
}

bool SealedVolumeFrameworkRepresentation::getSideFlagOfInternalShellFace(uint64_t regionIndex, uint64_t internalShellIndex, uint64_t faceIndex)
{
	loadShell(regionIndex, internalShellIndex);
	return faceSide_[faceIndex];
}
