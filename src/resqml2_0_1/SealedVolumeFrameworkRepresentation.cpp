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
#include "resqml2_0_1/SealedVolumeFrameworkRepresentation.h"

#include "resqml2_0_1/StratigraphicColumnRankInterpretation.h"
#include "resqml2_0_1/SealedSurfaceFrameworkRepresentation.h"
#include "resqml2_0_1/StratigraphicUnitInterpretation.h"

using namespace std;
using namespace RESQML2_0_1_NS;
using namespace gsoap_resqml2_0_1;

const char* SealedVolumeFrameworkRepresentation::XML_TAG = "SealedVolumeFrameworkRepresentation";

SealedVolumeFrameworkRepresentation::SealedVolumeFrameworkRepresentation(StratigraphicColumnRankInterpretation* interp,
	const std::string & guid,
	const std::string & title,
	SealedSurfaceFrameworkRepresentation* ssf)
{
	if (interp == nullptr) {
		throw invalid_argument("The Stratigraphic Column Rank Interpretation cannot be null.");
	}
	if (ssf == nullptr) {
		throw invalid_argument("The Sealed Surface Framework Representation cannot be null.");
	}

	// proxy constructor
	gsoapProxy2_0_1 = soap_new_resqml20__obj_USCORESealedVolumeFrameworkRepresentation(interp->getGsoapContext(), 1);
	_resqml20__SealedVolumeFrameworkRepresentation* orgRep = static_cast<_resqml20__SealedVolumeFrameworkRepresentation*>(gsoapProxy2_0_1);

	orgRep->IsHomogeneous = true;
	initMandatoryMetadata();
	setMetadata(guid, title, std::string(), -1, std::string(), std::string(), -1, std::string());

	// XML relationships
	setInterpretation(interp);
	setSealedSurfaceFramework(ssf);

	// Create a dummy shell as an official workaround (see note in http://docs.energistics.org/RESQML/RESQML_TOPICS/RESQML-500-269-0-R-sv2010.html)
	resqml20__VolumeShell* dummyShell = soap_new_resqml20__VolumeShell(gsoapProxy2_0_1->soap, 1);
	dummyShell->ShellUid = "dummy uid";
	orgRep->Shells.push_back(dummyShell);

	resqml20__OrientedMacroFace* face = soap_new_resqml20__OrientedMacroFace(gsoapProxy2_0_1->soap, 1);
	face->RepresentationIndex = (std::numeric_limits<int>::max)();
	face->PatchIndexOfRepresentation = (std::numeric_limits<int>::max)();
	dummyShell->MacroFaces.push_back(face);
}

void SealedVolumeFrameworkRepresentation::setSealedSurfaceFramework(SealedSurfaceFrameworkRepresentation* ssf)
{
	if (ssf == nullptr) {
		throw invalid_argument("Cannot set a null SealedSurfaceFrameworkRepresentation");
	}
	if (getRepository() == nullptr) {
		ssf->getRepository()->addOrReplaceDataObject(this);
	}

	getRepository()->addRelationship(this, ssf);

	setXmlSealedSurfaceFramework(ssf);
}

void SealedVolumeFrameworkRepresentation::setXmlSealedSurfaceFramework(class SealedSurfaceFrameworkRepresentation* ssf)
{
	if (ssf == nullptr) {
		throw invalid_argument("Cannot set a null SealedSurfaceFrameworkRepresentation");
	}

	static_cast<_resqml20__SealedVolumeFrameworkRepresentation*>(gsoapProxy2_0_1)->BasedOn = ssf->newResqmlReference();
}

void SealedVolumeFrameworkRepresentation::setInterpretationOfVolumeRegion(unsigned int regionIndex, StratigraphicUnitInterpretation * stratiUnitInterp)
{
	if (stratiUnitInterp == nullptr) {
		throw invalid_argument("Cannot set a null strati Unit Interpretation");
	}
	_resqml20__SealedVolumeFrameworkRepresentation* svf = static_cast<_resqml20__SealedVolumeFrameworkRepresentation*>(gsoapProxy2_0_1);
	if (regionIndex >= svf->Regions.size()) {
		throw range_error("The region index is out of range.");
	}

	getRepository()->addRelationship(this, stratiUnitInterp);

	setXmlInterpretationOfVolumeRegion(regionIndex, stratiUnitInterp);
}

void SealedVolumeFrameworkRepresentation::setXmlInterpretationOfVolumeRegion(unsigned int regionIndex, StratigraphicUnitInterpretation * stratiUnitInterp)
{
	if (stratiUnitInterp == nullptr) {
		throw invalid_argument("Cannot set a null strati Unit Interpretation");
	}
	_resqml20__SealedVolumeFrameworkRepresentation* svf = static_cast<_resqml20__SealedVolumeFrameworkRepresentation*>(gsoapProxy2_0_1);
	if (regionIndex >= svf->Regions.size()) {
		throw range_error("The region index is out of range.");
	}

	svf->Regions[regionIndex]->Represents = stratiUnitInterp->newResqmlReference();
}

gsoap_resqml2_0_1::resqml20__VolumeShell* SealedVolumeFrameworkRepresentation::createVolumeShell(
	unsigned int shellFaceCount,
	unsigned int * faceRepresentationIndices, unsigned int * faceRepPatchIndices, bool * faceSide)
{
	if (shellFaceCount == 0) {
		throw invalid_argument("Cannot create a shell with has got a face count of zero.");
	}

	resqml20__VolumeShell* externalShell = soap_new_resqml20__VolumeShell(gsoapProxy2_0_1->soap, 1);
	externalShell->ShellUid = "dummy uid";

	// Faces
	for (unsigned int faceIdx = 0; faceIdx < shellFaceCount; ++faceIdx) {
		resqml20__OrientedMacroFace* face = soap_new_resqml20__OrientedMacroFace(gsoapProxy2_0_1->soap, 1);
		face->RepresentationIndex = faceRepresentationIndices[faceIdx];
		face->PatchIndexOfRepresentation = faceRepPatchIndices[faceIdx];
		face->SideIsPlus = faceSide[faceIdx];
		externalShell->MacroFaces.push_back(face);
	}

	return externalShell;
}

void SealedVolumeFrameworkRepresentation::pushBackVolumeRegion(StratigraphicUnitInterpretation * stratiUnitInterp,
	unsigned int externalShellFaceCount,
	unsigned int * faceRepresentationIndices, unsigned int * faceRepPatchIndices, bool * faceSide)
{
	// Region
	resqml20__VolumeRegion* region = soap_new_resqml20__VolumeRegion(gsoapProxy2_0_1->soap, 1);
	region->PatchIndex = static_cast<_resqml20__SealedVolumeFrameworkRepresentation*>(gsoapProxy2_0_1)->Regions.size();
	static_cast<_resqml20__SealedVolumeFrameworkRepresentation*>(gsoapProxy2_0_1)->Regions.push_back(region);
	setInterpretationOfVolumeRegion(region->PatchIndex, stratiUnitInterp);

	// External shell
	region->ExternalShell = createVolumeShell(externalShellFaceCount,
		faceRepresentationIndices, faceRepPatchIndices, faceSide);
}

void SealedVolumeFrameworkRepresentation::pushBackInternalShell(unsigned int regionIndex,
	unsigned int externalShellFaceCount,
	unsigned int * faceRepresentationIndices, unsigned int * faceRepPatchIndices, bool * faceSide)
{
	getRegion(regionIndex)->InternalShells.push_back(createVolumeShell(externalShellFaceCount,
		faceRepresentationIndices, faceRepPatchIndices, faceSide));
}

gsoap_resqml2_0_1::eml20__DataObjectReference* SealedVolumeFrameworkRepresentation::getSealedStructuralFrameworkDor() const
{
	return static_cast<gsoap_resqml2_0_1::_resqml20__SealedVolumeFrameworkRepresentation*>(gsoapProxy2_0_1)->BasedOn;
}

std::string SealedVolumeFrameworkRepresentation::getSealedStructuralFrameworkUuid() const
{
	return getSealedStructuralFrameworkDor()->UUID;
}

SealedSurfaceFrameworkRepresentation* SealedVolumeFrameworkRepresentation::getSealedStructuralFramework() const
{
	return repository->getDataObjectByUuid<SealedSurfaceFrameworkRepresentation>(getSealedStructuralFrameworkUuid());
}

gsoap_resqml2_0_1::resqml20__VolumeRegion* SealedVolumeFrameworkRepresentation::getRegion(unsigned int regionIndex) const
{
	if (regionIndex >= getRegionCount()) {
		throw range_error("The region index is out of range.");
	}
	return static_cast<gsoap_resqml2_0_1::_resqml20__SealedVolumeFrameworkRepresentation*>(gsoapProxy2_0_1)->Regions[regionIndex];
}

gsoap_resqml2_0_1::eml20__DataObjectReference* SealedVolumeFrameworkRepresentation::getStratiUnitInterpDor(unsigned int regionIndex) const
{
	return getRegion(regionIndex)->Represents;
}

std::string SealedVolumeFrameworkRepresentation::getStratiUnitInterpUuid(unsigned int regionIndex) const
{
	return getStratiUnitInterpDor(regionIndex)->UUID;
}

StratigraphicUnitInterpretation* SealedVolumeFrameworkRepresentation::getStratiUnitInterp(unsigned int regionIndex) const
{
	return repository->getDataObjectByUuid<StratigraphicUnitInterpretation>(getStratiUnitInterpUuid(regionIndex));
}

unsigned int SealedVolumeFrameworkRepresentation::getRegionCount() const
{
	_resqml20__SealedVolumeFrameworkRepresentation* svf = static_cast<_resqml20__SealedVolumeFrameworkRepresentation*>(gsoapProxy2_0_1);
	if (svf->Regions.size() >= (std::numeric_limits<unsigned int>::max)()) {
		throw range_error("The count of regions in this framework is too big for fesapi.");
	}

	return static_cast<unsigned int>(svf->Regions.size());
}

unsigned int SealedVolumeFrameworkRepresentation::getInternalShellCount(unsigned int regionIndex) const
{
	const size_t count = getRegion(regionIndex)->InternalShells.size();
	if (count >= (std::numeric_limits<unsigned int>::max)()) {
		throw range_error("The count of internal shells in this region is too big for fesapi.");
	}

	return static_cast<unsigned int>(count);
}

gsoap_resqml2_0_1::resqml20__VolumeShell* SealedVolumeFrameworkRepresentation::getRegionExternalShell(unsigned int regionIndex) const
{
	return getRegion(regionIndex)->ExternalShell;
}

gsoap_resqml2_0_1::resqml20__VolumeShell* SealedVolumeFrameworkRepresentation::getRegionInternalShell(unsigned int regionIndex, unsigned int internalShellIndex) const
{
	if (internalShellIndex >= getInternalShellCount(regionIndex)) {
		throw range_error("The internal shell index is out of range.");
	}

	return getRegion(regionIndex)->InternalShells[internalShellIndex];
}

unsigned int SealedVolumeFrameworkRepresentation::getFaceCountOfExternalShell(unsigned int regionIndex) const
{
	gsoap_resqml2_0_1::resqml20__VolumeShell* shell = getRegionExternalShell(regionIndex);
	if (shell->MacroFaces.size() >= (std::numeric_limits<unsigned int>::max)()) {
		throw range_error("The count of faces in this shell is too big for fesapi.");
	}

	return static_cast<unsigned int>(shell->MacroFaces.size());
}

unsigned int SealedVolumeFrameworkRepresentation::getFaceCountOfInternalShell(unsigned int regionIndex, unsigned int internalShellIndex) const
{
	gsoap_resqml2_0_1::resqml20__VolumeShell* shell = getRegionInternalShell(regionIndex, internalShellIndex);
	if (shell->MacroFaces.size() >= (std::numeric_limits<unsigned int>::max)()) {
		throw range_error("The count of faces in this shell is too big for fesapi.");
	}

	return static_cast<unsigned int>(shell->MacroFaces.size());
}

gsoap_resqml2_0_1::resqml20__OrientedMacroFace* SealedVolumeFrameworkRepresentation::getRegionExternalShellFace(unsigned int regionIndex, unsigned int faceIndex) const
{
	if (faceIndex >= getFaceCountOfExternalShell(regionIndex)) {
		throw range_error("The face index of the region external shell is out of range.");
	}

	return getRegionExternalShell(regionIndex)->MacroFaces[faceIndex];
}

gsoap_resqml2_0_1::resqml20__OrientedMacroFace* SealedVolumeFrameworkRepresentation::getRegionInternalShellFace(unsigned int regionIndex, unsigned int internalShellIndex, unsigned int faceIndex) const
{
	if (faceIndex >= getFaceCountOfInternalShell(regionIndex, internalShellIndex)) {
		throw range_error("The face index of the region internal shell is out of range.");
	}

	return getRegionInternalShell(regionIndex, internalShellIndex)->MacroFaces[faceIndex];
}

RESQML2_NS::AbstractRepresentation* SealedVolumeFrameworkRepresentation::getRepOfExternalShellFace(unsigned int regionIndex, unsigned int faceIndex) const
{
	return getRepresentation(getRegionExternalShellFace(regionIndex, faceIndex)->RepresentationIndex);
}

RESQML2_NS::AbstractRepresentation* SealedVolumeFrameworkRepresentation::getRepOfInternalShellFace(unsigned int regionIndex, unsigned int internalShellIndex, unsigned int faceIndex) const
{
	return getRepresentation(getRegionInternalShellFace(regionIndex, internalShellIndex, faceIndex)->RepresentationIndex);
}

unsigned int SealedVolumeFrameworkRepresentation::getRepPatchIndexOfExternalShellFace(unsigned int regionIndex, unsigned int faceIndex) const
{
	return getRegionExternalShellFace(regionIndex, faceIndex)->PatchIndexOfRepresentation;
}

unsigned int SealedVolumeFrameworkRepresentation::getRepPatchIndexOfInternalShellFace(unsigned int regionIndex, unsigned int internalShellIndex, unsigned int faceIndex) const
{
	return getRegionInternalShellFace(regionIndex, internalShellIndex, faceIndex)->PatchIndexOfRepresentation;
}

bool SealedVolumeFrameworkRepresentation::getSideFlagOfExternalShellFace(unsigned int regionIndex, unsigned int faceIndex) const
{
	return getRegionExternalShellFace(regionIndex, faceIndex)->SideIsPlus;
}

bool SealedVolumeFrameworkRepresentation::getSideFlagOfInternalShellFace(unsigned int regionIndex, unsigned int internalShellIndex, unsigned int faceIndex) const
{
	return getRegionInternalShellFace(regionIndex, internalShellIndex, faceIndex)->SideIsPlus;
}

void SealedVolumeFrameworkRepresentation::loadTargetRelationships()
{
	RESQML2_NS::RepresentationSetRepresentation::loadTargetRelationships();

	gsoap_resqml2_0_1::eml20__DataObjectReference const * dor = getSealedStructuralFrameworkDor();
	convertDorIntoRel<SealedSurfaceFrameworkRepresentation>(dor);

	for (size_t regionIdx = 0; regionIdx < getRegionCount(); ++regionIdx) {
		dor = getStratiUnitInterpDor(regionIdx);
		convertDorIntoRel<StratigraphicUnitInterpretation>(dor);
	}
}
