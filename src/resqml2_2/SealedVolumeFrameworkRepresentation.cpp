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

#include <limits>

#include "../resqml2/StratigraphicColumnRankInterpretation.h"
#include "../resqml2/SealedSurfaceFrameworkRepresentation.h"
#include "../resqml2/StratigraphicUnitInterpretation.h"

using namespace std;
using namespace RESQML2_2_NS;
using namespace gsoap_eml2_3;

const char* SealedVolumeFrameworkRepresentation::XML_NS = "resqml22";

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
	setMetadata(guid, title, std::string(), -1, std::string(), std::string(), -1, std::string());

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
	_resqml22__SealedVolumeFrameworkRepresentation* svf = static_cast<_resqml22__SealedVolumeFrameworkRepresentation*>(gsoapProxy2_3);
	if (regionIndex >= svf->Regions.size()) {
		throw out_of_range("The region index is out of range.");
	}

	svf->Regions[regionIndex]->Represents = stratiUnitInterp->newEml23Reference();
}

gsoap_eml2_3::resqml22__VolumeShell* SealedVolumeFrameworkRepresentation::createVolumeShell(
	unsigned int shellFaceCount,
	unsigned int const* faceRepresentationIndices, unsigned int const* faceRepPatchIndices, bool const* faceSide)
{
	if (shellFaceCount == 0) {
		throw invalid_argument("Cannot create a shell with has got a face count of zero.");
	}

	resqml22__VolumeShell* externalShell = soap_new_resqml22__VolumeShell(gsoapProxy2_3->soap);
	externalShell->ShellUid = "dummy uid";

	// Faces
	for (unsigned int faceIdx = 0; faceIdx < shellFaceCount; ++faceIdx) {
		resqml22__OrientedMacroFace* face = soap_new_resqml22__OrientedMacroFace(gsoapProxy2_3->soap);
		face->RepresentationIndex = faceRepresentationIndices[faceIdx];
		face->PatchIndexOfRepresentation = faceRepPatchIndices[faceIdx];
		face->SideIsPlus = faceSide[faceIdx];
		externalShell->MacroFaces.push_back(face);
	}

	return externalShell;
}

void SealedVolumeFrameworkRepresentation::pushBackVolumeRegion(RESQML2_NS::StratigraphicUnitInterpretation * stratiUnitInterp,
	unsigned int externalShellFaceCount,
	unsigned int const* faceRepresentationIndices, unsigned int const* faceRepPatchIndices, bool const* faceSide)
{
	// Region
	resqml22__VolumeRegion* region = soap_new_resqml22__VolumeRegion(gsoapProxy2_3->soap);
	region->PatchIndex = static_cast<_resqml22__SealedVolumeFrameworkRepresentation*>(gsoapProxy2_3)->Regions.size();
	static_cast<_resqml22__SealedVolumeFrameworkRepresentation*>(gsoapProxy2_3)->Regions.push_back(region);
	setInterpretationOfVolumeRegion(region->PatchIndex, stratiUnitInterp);

	// External shell
	region->ExternalShell = createVolumeShell(externalShellFaceCount,
		faceRepresentationIndices, faceRepPatchIndices, faceSide);
}

void SealedVolumeFrameworkRepresentation::pushBackInternalShell(uint64_t regionIndex,
	unsigned int internalShellFaceCount,
	unsigned int const* faceRepresentationIndices, unsigned int const* faceRepPatchIndices, bool const* faceSide)
{
	getRegion(regionIndex)->InternalShells.push_back(createVolumeShell(internalShellFaceCount,
		faceRepresentationIndices, faceRepPatchIndices, faceSide));
}

COMMON_NS::DataObjectReference SealedVolumeFrameworkRepresentation::getSealedStructuralFrameworkDor() const
{
	return COMMON_NS::DataObjectReference(static_cast<gsoap_eml2_3::_resqml22__SealedVolumeFrameworkRepresentation*>(gsoapProxy2_3)->BasedOn);
}

gsoap_eml2_3::resqml22__VolumeRegion* SealedVolumeFrameworkRepresentation::getRegion(uint64_t regionIndex) const
{
	if (regionIndex >= getRegionCount()) {
		throw range_error("The region index is out of range.");
	}
	return static_cast<gsoap_eml2_3::_resqml22__SealedVolumeFrameworkRepresentation*>(gsoapProxy2_3)->Regions[regionIndex];
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

gsoap_eml2_3::resqml22__VolumeShell* SealedVolumeFrameworkRepresentation::getRegionInternalShell(uint64_t regionIndex, unsigned int internalShellIndex) const
{
	if (internalShellIndex >= getInternalShellCount(regionIndex)) {
		throw out_of_range("The internal shell index is out of range.");
	}

	return getRegion(regionIndex)->InternalShells[internalShellIndex];
}

uint64_t SealedVolumeFrameworkRepresentation::getFaceCountOfExternalShell(uint64_t regionIndex) const
{
	return getRegionExternalShell(regionIndex)->MacroFaces.size();
}

uint64_t SealedVolumeFrameworkRepresentation::getFaceCountOfInternalShell(uint64_t regionIndex, unsigned int internalShellIndex) const
{
	gsoap_eml2_3::resqml22__VolumeShell* shell = getRegionInternalShell(regionIndex, internalShellIndex);
	if (shell->MacroFaces.size() >= (std::numeric_limits<unsigned int>::max)()) {
		throw range_error("The count of faces in this shell is too big for fesapi.");
	}

	return static_cast<unsigned int>(shell->MacroFaces.size());
}

gsoap_eml2_3::resqml22__OrientedMacroFace* SealedVolumeFrameworkRepresentation::getRegionExternalShellFace(uint64_t regionIndex, unsigned int faceIndex) const
{
	if (faceIndex >= getFaceCountOfExternalShell(regionIndex)) {
		throw out_of_range("The face index of the region external shell is out of range.");
	}

	return getRegionExternalShell(regionIndex)->MacroFaces[faceIndex];
}

gsoap_eml2_3::resqml22__OrientedMacroFace* SealedVolumeFrameworkRepresentation::getRegionInternalShellFace(uint64_t regionIndex, unsigned int internalShellIndex, unsigned int faceIndex) const
{
	if (faceIndex >= getFaceCountOfInternalShell(regionIndex, internalShellIndex)) {
		throw out_of_range("The face index of the region internal shell is out of range.");
	}

	return getRegionInternalShell(regionIndex, internalShellIndex)->MacroFaces[faceIndex];
}

RESQML2_NS::AbstractRepresentation* SealedVolumeFrameworkRepresentation::getRepOfExternalShellFace(uint64_t regionIndex, unsigned int faceIndex) const
{
	return getRepresentation(getRegionExternalShellFace(regionIndex, faceIndex)->RepresentationIndex);
}

RESQML2_NS::AbstractRepresentation* SealedVolumeFrameworkRepresentation::getRepOfInternalShellFace(uint64_t regionIndex, unsigned int internalShellIndex, unsigned int faceIndex) const
{
	return getRepresentation(getRegionInternalShellFace(regionIndex, internalShellIndex, faceIndex)->RepresentationIndex);
}

uint64_t SealedVolumeFrameworkRepresentation::getRepPatchIndexOfExternalShellFace(uint64_t regionIndex, unsigned int faceIndex) const
{
	return getRegionExternalShellFace(regionIndex, faceIndex)->PatchIndexOfRepresentation;
}

uint64_t SealedVolumeFrameworkRepresentation::getRepPatchIndexOfInternalShellFace(uint64_t regionIndex, unsigned int internalShellIndex, unsigned int faceIndex) const
{
	return getRegionInternalShellFace(regionIndex, internalShellIndex, faceIndex)->PatchIndexOfRepresentation;
}

bool SealedVolumeFrameworkRepresentation::getSideFlagOfExternalShellFace(uint64_t regionIndex, unsigned int faceIndex) const
{
	return getRegionExternalShellFace(regionIndex, faceIndex)->SideIsPlus;
}

bool SealedVolumeFrameworkRepresentation::getSideFlagOfInternalShellFace(uint64_t regionIndex, unsigned int internalShellIndex, unsigned int faceIndex) const
{
	return getRegionInternalShellFace(regionIndex, internalShellIndex, faceIndex)->SideIsPlus;
}
