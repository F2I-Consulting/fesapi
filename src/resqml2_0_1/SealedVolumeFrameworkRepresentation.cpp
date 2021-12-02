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

#include "../resqml2/StratigraphicColumnRankInterpretation.h"
#include "../resqml2/SealedSurfaceFrameworkRepresentation.h"
#include "../resqml2/StratigraphicUnitInterpretation.h"

using namespace std;
using namespace RESQML2_0_1_NS;
using namespace gsoap_resqml2_0_1;

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
	gsoapProxy2_0_1 = soap_new_resqml20__obj_USCORESealedVolumeFrameworkRepresentation(interp->getGsoapContext());
	_resqml20__SealedVolumeFrameworkRepresentation* orgRep = static_cast<_resqml20__SealedVolumeFrameworkRepresentation*>(gsoapProxy2_0_1);

	orgRep->IsHomogeneous = true;
	initMandatoryMetadata();
	setMetadata(guid, title, std::string(), -1, std::string(), std::string(), -1, std::string());

	interp->getRepository()->addDataObject(this);
	// XML relationships
	setInterpretation(interp);
	setSealedSurfaceFramework(ssf);

	// Create a dummy shell as an official workaround (see note in http://docs.energistics.org/RESQML/RESQML_TOPICS/RESQML-500-269-0-R-sv2010.html)
	resqml20__VolumeShell* dummyShell = soap_new_resqml20__VolumeShell(gsoapProxy2_0_1->soap);
	dummyShell->ShellUid = "dummy uid";
	orgRep->Shells.push_back(dummyShell);

	resqml20__OrientedMacroFace* face = soap_new_resqml20__OrientedMacroFace(gsoapProxy2_0_1->soap);
	face->RepresentationIndex = (std::numeric_limits<int>::max)();
	face->PatchIndexOfRepresentation = (std::numeric_limits<int>::max)();
	dummyShell->MacroFaces.push_back(face);
}

void SealedVolumeFrameworkRepresentation::setXmlSealedSurfaceFramework(RESQML2_NS::SealedSurfaceFrameworkRepresentation* ssf)
{
	if (ssf == nullptr) {
		throw invalid_argument("Cannot set a null SealedSurfaceFrameworkRepresentation");
	}

	static_cast<_resqml20__SealedVolumeFrameworkRepresentation*>(gsoapProxy2_0_1)->BasedOn = ssf->newResqmlReference();
}

void SealedVolumeFrameworkRepresentation::setXmlInterpretationOfVolumeRegion(uint64_t regionIndex, RESQML2_NS::StratigraphicUnitInterpretation * stratiUnitInterp)
{
	if (stratiUnitInterp == nullptr) {
		throw invalid_argument("Cannot set a null strati Unit Interpretation");
	}
	_resqml20__SealedVolumeFrameworkRepresentation* svf = static_cast<_resqml20__SealedVolumeFrameworkRepresentation*>(gsoapProxy2_0_1);
	if (regionIndex >= svf->Regions.size()) {
		throw out_of_range("The region index is out of range.");
	}

	svf->Regions[regionIndex]->Represents = stratiUnitInterp->newResqmlReference();
}

gsoap_resqml2_0_1::resqml20__VolumeShell* SealedVolumeFrameworkRepresentation::createVolumeShell(
	uint64_t shellFaceCount,
	unsigned int const* faceRepresentationIndices, unsigned int const* faceRepPatchIndices, char const* faceSide)
{
	if (shellFaceCount == 0) {
		throw invalid_argument("Cannot create a shell with has got a face count of zero.");
	}

	resqml20__VolumeShell* externalShell = soap_new_resqml20__VolumeShell(gsoapProxy2_0_1->soap);
	externalShell->ShellUid = "dummy uid";

	// Faces
	for (unsigned int faceIdx = 0; faceIdx < shellFaceCount; ++faceIdx) {
		resqml20__OrientedMacroFace* face = soap_new_resqml20__OrientedMacroFace(gsoapProxy2_0_1->soap);
		face->RepresentationIndex = faceRepresentationIndices[faceIdx];
		face->PatchIndexOfRepresentation = faceRepPatchIndices[faceIdx];
		face->SideIsPlus = faceSide[faceIdx];
		externalShell->MacroFaces.push_back(face);
	}

	return externalShell;
}

void SealedVolumeFrameworkRepresentation::pushBackVolumeRegion(RESQML2_NS::StratigraphicUnitInterpretation * stratiUnitInterp,
	uint64_t externalShellFaceCount,
	unsigned int const* faceRepresentationIndices, unsigned int const* faceRepPatchIndices, char const* faceSide)
{
	// Region
	resqml20__VolumeRegion* region = soap_new_resqml20__VolumeRegion(gsoapProxy2_0_1->soap);
	region->PatchIndex = static_cast<_resqml20__SealedVolumeFrameworkRepresentation*>(gsoapProxy2_0_1)->Regions.size();
	static_cast<_resqml20__SealedVolumeFrameworkRepresentation*>(gsoapProxy2_0_1)->Regions.push_back(region);
	setInterpretationOfVolumeRegion(region->PatchIndex, stratiUnitInterp);

	// External shell
	region->ExternalShell = createVolumeShell(externalShellFaceCount,
		faceRepresentationIndices, faceRepPatchIndices, faceSide);
}

void SealedVolumeFrameworkRepresentation::pushBackInternalShell(uint64_t regionIndex,
	uint64_t internalShellFaceCount,
	unsigned int const* faceRepresentationIndices, unsigned int const* faceRepPatchIndices, char const* faceSide)
{
	getRegion(regionIndex)->InternalShells.push_back(createVolumeShell(internalShellFaceCount,
		faceRepresentationIndices, faceRepPatchIndices, faceSide));
}

COMMON_NS::DataObjectReference SealedVolumeFrameworkRepresentation::getSealedStructuralFrameworkDor() const
{
	return COMMON_NS::DataObjectReference(static_cast<gsoap_resqml2_0_1::_resqml20__SealedVolumeFrameworkRepresentation*>(gsoapProxy2_0_1)->BasedOn);
}

gsoap_resqml2_0_1::resqml20__VolumeRegion* SealedVolumeFrameworkRepresentation::getRegion(uint64_t regionIndex) const
{
	if (regionIndex >= getRegionCount()) {
		throw out_of_range("The region index is out of range.");
	}
	return static_cast<gsoap_resqml2_0_1::_resqml20__SealedVolumeFrameworkRepresentation*>(gsoapProxy2_0_1)->Regions[regionIndex];
}

COMMON_NS::DataObjectReference SealedVolumeFrameworkRepresentation::getStratiUnitInterpDor(uint64_t regionIndex) const
{
	return COMMON_NS::DataObjectReference(getRegion(regionIndex)->Represents);
}

uint64_t SealedVolumeFrameworkRepresentation::getRegionCount() const
{
	return static_cast<_resqml20__SealedVolumeFrameworkRepresentation*>(gsoapProxy2_0_1)->Regions.size();
}

uint64_t SealedVolumeFrameworkRepresentation::getInternalShellCount(uint64_t regionIndex) const
{
	return getRegion(regionIndex)->InternalShells.size();
}

gsoap_resqml2_0_1::resqml20__VolumeShell* SealedVolumeFrameworkRepresentation::getRegionExternalShell(uint64_t regionIndex) const
{
	return getRegion(regionIndex)->ExternalShell;
}

gsoap_resqml2_0_1::resqml20__VolumeShell* SealedVolumeFrameworkRepresentation::getRegionInternalShell(uint64_t regionIndex, uint64_t internalShellIndex) const
{
	if (internalShellIndex >= getInternalShellCount(regionIndex)) {
		throw out_of_range("The internal shell index is out of range.");
	}

	return getRegion(regionIndex)->InternalShells[internalShellIndex];
}

uint64_t SealedVolumeFrameworkRepresentation::getFaceCountOfExternalShell(uint64_t regionIndex) const
{
	gsoap_resqml2_0_1::resqml20__VolumeShell* shell = getRegionExternalShell(regionIndex);
	return static_cast<unsigned int>(shell->MacroFaces.size());
}

uint64_t SealedVolumeFrameworkRepresentation::getFaceCountOfInternalShell(uint64_t regionIndex, uint64_t internalShellIndex) const
{
	gsoap_resqml2_0_1::resqml20__VolumeShell* shell = getRegionInternalShell(regionIndex, internalShellIndex);
	return static_cast<unsigned int>(shell->MacroFaces.size());
}

gsoap_resqml2_0_1::resqml20__OrientedMacroFace* SealedVolumeFrameworkRepresentation::getRegionExternalShellFace(uint64_t regionIndex, uint64_t faceIndex) const
{
	if (faceIndex >= getFaceCountOfExternalShell(regionIndex)) {
		throw out_of_range("The face index of the region external shell is out of range.");
	}

	return getRegionExternalShell(regionIndex)->MacroFaces[faceIndex];
}

gsoap_resqml2_0_1::resqml20__OrientedMacroFace* SealedVolumeFrameworkRepresentation::getRegionInternalShellFace(uint64_t regionIndex, uint64_t internalShellIndex, uint64_t faceIndex) const
{
	if (faceIndex >= getFaceCountOfInternalShell(regionIndex, internalShellIndex)) {
		throw out_of_range("The face index of the region internal shell is out of range.");
	}

	return getRegionInternalShell(regionIndex, internalShellIndex)->MacroFaces[faceIndex];
}

RESQML2_NS::AbstractRepresentation* SealedVolumeFrameworkRepresentation::getRepOfExternalShellFace(uint64_t regionIndex, uint64_t faceIndex)
{
	return getRepresentation(getRegionExternalShellFace(regionIndex, faceIndex)->RepresentationIndex);
}

RESQML2_NS::AbstractRepresentation* SealedVolumeFrameworkRepresentation::getRepOfInternalShellFace(uint64_t regionIndex, uint64_t internalShellIndex, uint64_t faceIndex)
{
	return getRepresentation(getRegionInternalShellFace(regionIndex, internalShellIndex, faceIndex)->RepresentationIndex);
}

uint64_t SealedVolumeFrameworkRepresentation::getRepPatchIndexOfExternalShellFace(uint64_t regionIndex, uint64_t faceIndex)
{
	return getRegionExternalShellFace(regionIndex, faceIndex)->PatchIndexOfRepresentation;
}

uint64_t SealedVolumeFrameworkRepresentation::getRepPatchIndexOfInternalShellFace(uint64_t regionIndex, uint64_t internalShellIndex, uint64_t faceIndex)
{
	return getRegionInternalShellFace(regionIndex, internalShellIndex, faceIndex)->PatchIndexOfRepresentation;
}

bool SealedVolumeFrameworkRepresentation::getSideFlagOfExternalShellFace(uint64_t regionIndex, uint64_t faceIndex)
{
	return getRegionExternalShellFace(regionIndex, faceIndex)->SideIsPlus;
}

bool SealedVolumeFrameworkRepresentation::getSideFlagOfInternalShellFace(uint64_t regionIndex, uint64_t internalShellIndex, uint64_t faceIndex)
{
	return getRegionInternalShellFace(regionIndex, internalShellIndex, faceIndex)->SideIsPlus;
}
