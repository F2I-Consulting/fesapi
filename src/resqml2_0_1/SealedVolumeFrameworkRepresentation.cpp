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
using namespace epc;
using namespace RESQML2_0_1_NS;
using namespace gsoap_resqml2_0_1;

SealedVolumeFrameworkRepresentation::SealedVolumeFrameworkRepresentation(StratigraphicColumnRankInterpretation* interp,
	const std::string & guid,
	const std::string & title,
	SealedSurfaceFrameworkRepresentation* ssf) :
	RESQML2_NS::RepresentationSetRepresentation(interp)
{
	if (interp == nullptr) {
		throw invalid_argument("The Stratigraphic Column Rank Interpretation cannot be null.");
	}
	if (ssf == nullptr) {
		throw invalid_argument("The Sealed Surface Framework Representation cannot be null.");
	}

	// proxy constructor
	gsoapProxy2_0_1 = soap_new_resqml2__obj_USCORESealedVolumeFrameworkRepresentation(interp->getGsoapContext(), 1);

	initMandatoryMetadata();
	setMetadata(guid, title, std::string(), -1, std::string(), std::string(), -1, std::string());

	// XML relationships
	setInterpretation(interp);
	setSealedSurfaceFramework(ssf);

	// Create a dummy shell as an official workaround (see note in http://docs.energistics.org/RESQML/RESQML_TOPICS/RESQML-500-269-0-R-sv2010.html)
	resqml2__VolumeShell* dummyShell = soap_new_resqml2__VolumeShell(gsoapProxy2_0_1->soap, 1);
	dummyShell->ShellUid = "dummy uid";
	static_cast<_resqml2__SealedVolumeFrameworkRepresentation*>(gsoapProxy2_0_1)->Shells.push_back(dummyShell);

	resqml2__OrientedMacroFace* face = soap_new_resqml2__OrientedMacroFace(gsoapProxy2_0_1->soap, 1);
	face->RepresentationIndex = (std::numeric_limits<int>::max)();
	face->PatchIndexOfRepresentation = (std::numeric_limits<int>::max)();
	dummyShell->MacroFaces.push_back(face);
}

void SealedVolumeFrameworkRepresentation::setSealedSurfaceFramework(SealedSurfaceFrameworkRepresentation* ssf)
{
	if (ssf == nullptr) {
		throw invalid_argument("Cannot set a null SealedSurfaceFrameworkRepresentation");
	}

	// EPC
	ssf->svfSet.push_back(this);

	// XML
	if (updateXml) {
		setXmlSealedSurfaceFramework(ssf);
	}
}

void SealedVolumeFrameworkRepresentation::setXmlSealedSurfaceFramework(class SealedSurfaceFrameworkRepresentation* ssf)
{
	if (ssf == nullptr) {
		throw invalid_argument("Cannot set a null SealedSurfaceFrameworkRepresentation");
	}

	static_cast<_resqml2__SealedVolumeFrameworkRepresentation*>(gsoapProxy2_0_1)->BasedOn = ssf->newResqmlReference();
}

void SealedVolumeFrameworkRepresentation::setInterpretationOfVolumeRegion(unsigned int regionIndex, StratigraphicUnitInterpretation * stratiUnitInterp)
{
	if (stratiUnitInterp == nullptr) {
		throw invalid_argument("Cannot set a null strati Unit Interpretation");
	}
	_resqml2__SealedVolumeFrameworkRepresentation* svf = static_cast<_resqml2__SealedVolumeFrameworkRepresentation*>(gsoapProxy2_0_1);
	if (regionIndex >= svf->Regions.size()) {
		throw range_error("The region index is out of range.");
	}

	// EPC
	stratiUnitInterp->svfSet.push_back(this);

	// XML
	if (updateXml) {
		setXmlInterpretationOfVolumeRegion(regionIndex, stratiUnitInterp);
	}
}

void SealedVolumeFrameworkRepresentation::setXmlInterpretationOfVolumeRegion(unsigned int regionIndex, StratigraphicUnitInterpretation * stratiUnitInterp)
{
	if (stratiUnitInterp == nullptr) {
		throw invalid_argument("Cannot set a null strati Unit Interpretation");
	}
	_resqml2__SealedVolumeFrameworkRepresentation* svf = static_cast<_resqml2__SealedVolumeFrameworkRepresentation*>(gsoapProxy2_0_1);
	if (regionIndex >= svf->Regions.size()) {
		throw range_error("The region index is out of range.");
	}

	svf->Regions[regionIndex]->Represents = stratiUnitInterp->newResqmlReference();
}

void SealedVolumeFrameworkRepresentation::pushBackVolumeRegion(StratigraphicUnitInterpretation * stratiUnitInterp, const std::string & externalShellUid,
	unsigned int externalShellFaceCount,
	unsigned int * faceRepresentationIndices, unsigned int * faceRepPatchIndices, bool * faceSide)
{
	// Region
	resqml2__VolumeRegion* region = soap_new_resqml2__VolumeRegion(gsoapProxy2_0_1->soap, 1);
	region->PatchIndex = static_cast<_resqml2__SealedVolumeFrameworkRepresentation*>(gsoapProxy2_0_1)->Regions.size();
	static_cast<_resqml2__SealedVolumeFrameworkRepresentation*>(gsoapProxy2_0_1)->Regions.push_back(region);
	setInterpretationOfVolumeRegion(region->PatchIndex, stratiUnitInterp);

	// External shell
	resqml2__VolumeShell* externalShell = soap_new_resqml2__VolumeShell(gsoapProxy2_0_1->soap, 1);
	externalShell->ShellUid = externalShellUid;
	region->ExternalShell = externalShell;

	// Faces
	for (unsigned int faceIdx = 0; faceIdx < externalShellFaceCount; ++faceIdx) {
		resqml2__OrientedMacroFace* face = soap_new_resqml2__OrientedMacroFace(gsoapProxy2_0_1->soap, 1);
		face->RepresentationIndex = faceRepresentationIndices[faceIdx];
		face->PatchIndexOfRepresentation = faceRepPatchIndices[faceIdx];
		face->SideIsPlus = faceSide[faceIdx];
		externalShell->MacroFaces.push_back(face);
	}
}

gsoap_resqml2_0_1::eml20__DataObjectReference* SealedVolumeFrameworkRepresentation::getSealedStructuralFrameworkDor() const
{
	return static_cast<gsoap_resqml2_0_1::_resqml2__SealedVolumeFrameworkRepresentation*>(gsoapProxy2_0_1)->BasedOn;
}

std::string SealedVolumeFrameworkRepresentation::getSealedStructuralFrameworkUuid() const
{
	return getSealedStructuralFrameworkDor()->UUID;
}

SealedSurfaceFrameworkRepresentation* SealedVolumeFrameworkRepresentation::getSealedStructuralFramework() const
{
	return epcDocument->getDataObjectByUuid<SealedSurfaceFrameworkRepresentation>(getSealedStructuralFrameworkUuid());
}

gsoap_resqml2_0_1::resqml2__VolumeRegion* SealedVolumeFrameworkRepresentation::getRegion(unsigned int regionIndex) const
{
	if (regionIndex >= getRegionCount()) {
		throw range_error("The region index is out of range.");
	}
	return static_cast<gsoap_resqml2_0_1::_resqml2__SealedVolumeFrameworkRepresentation*>(gsoapProxy2_0_1)->Regions[regionIndex];
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
	return epcDocument->getDataObjectByUuid<StratigraphicUnitInterpretation>(getStratiUnitInterpUuid(regionIndex));
}

unsigned int SealedVolumeFrameworkRepresentation::getRegionCount() const
{
	_resqml2__SealedVolumeFrameworkRepresentation* svf = static_cast<_resqml2__SealedVolumeFrameworkRepresentation*>(gsoapProxy2_0_1);
	if (svf->Regions.size() >= (std::numeric_limits<unsigned int>::max)()) {
		throw range_error("The count of regions in this framework is too big for fesapi.");
	}

	return static_cast<unsigned int>(svf->Regions.size());
}

gsoap_resqml2_0_1::resqml2__VolumeShell* SealedVolumeFrameworkRepresentation::getRegionExternalShell(unsigned int regionIndex) const
{
	return getRegion(regionIndex)->ExternalShell;
}

unsigned int SealedVolumeFrameworkRepresentation::getFaceCountOfExternalShellFace(unsigned int regionIndex) const
{
	gsoap_resqml2_0_1::resqml2__VolumeShell* shell = getRegionExternalShell(regionIndex);
	if (shell->MacroFaces.size() >= (std::numeric_limits<unsigned int>::max)()) {
		throw range_error("The count of faces in this framework is too big for fesapi.");
	}

	return static_cast<unsigned int>(shell->MacroFaces.size());
}

gsoap_resqml2_0_1::resqml2__OrientedMacroFace* SealedVolumeFrameworkRepresentation::getRegionExternalShellFace(unsigned int regionIndex, unsigned int faceIndex) const
{
	if (faceIndex >= getFaceCountOfExternalShellFace(regionIndex)) {
		throw range_error("The face index of the region external shell is out of range.");
	}

	return getRegionExternalShell(regionIndex)->MacroFaces[faceIndex];
}

RESQML2_NS::AbstractRepresentation* SealedVolumeFrameworkRepresentation::getRepOfExternalShellFace(unsigned int regionIndex, unsigned int faceIndex) const
{
	return getRepresentation(getRegionExternalShellFace(regionIndex, faceIndex)->RepresentationIndex);
}

unsigned int SealedVolumeFrameworkRepresentation::getRepPatchIndexOfExternalShellFace(unsigned int regionIndex, unsigned int faceIndex) const
{
	return getRegionExternalShellFace(regionIndex, faceIndex)->PatchIndexOfRepresentation;
}

bool SealedVolumeFrameworkRepresentation::getSideFlageOfExternalShellFace(unsigned int regionIndex, unsigned int faceIndex) const
{
	return getRegionExternalShellFace(regionIndex, faceIndex)->SideIsPlus;
}

vector<Relationship> SealedVolumeFrameworkRepresentation::getAllEpcRelationships() const
{
	vector<Relationship> result = RESQML2_NS::RepresentationSetRepresentation::getAllEpcRelationships();

	SealedSurfaceFrameworkRepresentation* ssf = getSealedStructuralFramework();
	Relationship relSsf(ssf->getPartNameInEpcDocument(), "", ssf->getUuid());
	relSsf.setDestinationObjectType();
	result.push_back(relSsf);

	for (size_t regionIdx = 0; regionIdx < getRegionCount(); ++regionIdx) {
		StratigraphicUnitInterpretation* stratiUnitInterp = getStratiUnitInterp(regionIdx);
		Relationship relSii(stratiUnitInterp->getPartNameInEpcDocument(), "", stratiUnitInterp->getUuid());
		relSii.setDestinationObjectType();
		result.push_back(relSii);
	}

	return result;
}

void SealedVolumeFrameworkRepresentation::importRelationshipSetFromEpc(COMMON_NS::EpcDocument* epcDoc)
{
	RESQML2_NS::RepresentationSetRepresentation::importRelationshipSetFromEpc(epcDoc);

	updateXml = false;

	gsoap_resqml2_0_1::eml20__DataObjectReference* dor = getSealedStructuralFrameworkDor();
	SealedSurfaceFrameworkRepresentation* ssf = epcDoc->getDataObjectByUuid<SealedSurfaceFrameworkRepresentation>(dor->UUID);
	if (ssf == nullptr) { // partial transfer
		getEpcDocument()->createPartial(dor);
		ssf = getEpcDocument()->getDataObjectByUuid<SealedSurfaceFrameworkRepresentation>(dor->UUID);
	}
	if (ssf == nullptr) {
		throw invalid_argument("The DOR looks invalid.");
	}
	setSealedSurfaceFramework(ssf);

	for (size_t regionIdx = 0; regionIdx < getRegionCount(); ++regionIdx) {
		gsoap_resqml2_0_1::eml20__DataObjectReference* dor = getStratiUnitInterpDor(regionIdx);
		StratigraphicUnitInterpretation* sui = epcDoc->getDataObjectByUuid<StratigraphicUnitInterpretation>(dor->UUID);
		if (sui == nullptr) { // partial transfer
			getEpcDocument()->createPartial(dor);
			sui = getEpcDocument()->getDataObjectByUuid<StratigraphicUnitInterpretation>(dor->UUID);
		}
		if (sui == nullptr) {
			throw invalid_argument("The DOR looks invalid.");
		}
		setInterpretationOfVolumeRegion(regionIdx, sui);
	}

	updateXml = true;
}
