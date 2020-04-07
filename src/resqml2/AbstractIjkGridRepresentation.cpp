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
#include "AbstractIjkGridRepresentation.h"

#include <limits>
#include <stdexcept>

#include <hdf5.h>

#include "../eml2/AbstractHdfProxy.h"
#include "AbstractFeatureInterpretation.h"

using namespace std;
using namespace gsoap_resqml2_0_1;
using namespace RESQML2_NS;

const char* AbstractIjkGridRepresentation::XML_TAG = "IjkGridRepresentation";
const char* AbstractIjkGridRepresentation::XML_TAG_TRUNCATED = "TruncatedIjkGridRepresentation";

AbstractIjkGridRepresentation::AbstractIjkGridRepresentation(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject, bool withTruncatedPillars) :
	AbstractColumnLayerGridRepresentation(partialObject, withTruncatedPillars), splitInformation(nullptr), blockInformation(nullptr)
{
}

std::string AbstractIjkGridRepresentation::getXmlTag() const
{
	return !isTruncated() ? XML_TAG : XML_TAG_TRUNCATED;
}

void AbstractIjkGridRepresentation::init(COMMON_NS::DataObjectRepository * repo,
	const std::string & guid, const std::string & title,
	unsigned int iCount, unsigned int jCount, unsigned int kCount)
{
	if (repo == nullptr) {
		throw invalid_argument("The repo cannot be null.");
	}

	if (!withTruncatedPillars) {
		switch (repo->getDefaultResqmlVersion()) {
		case COMMON_NS::DataObjectRepository::EnergisticsStandard::RESQML2_0_1: {
			gsoapProxy2_0_1 = gsoap_resqml2_0_1::soap_new_resqml20__obj_USCOREIjkGridRepresentation(repo->getGsoapContext());
			gsoap_resqml2_0_1::_resqml20__IjkGridRepresentation* ijkGrid = static_cast<gsoap_resqml2_0_1::_resqml20__IjkGridRepresentation*>(gsoapProxy2_0_1);
			ijkGrid->Ni = iCount;
			ijkGrid->Nj = jCount;
			ijkGrid->Nk = kCount;
			break;
		}
		case COMMON_NS::DataObjectRepository::EnergisticsStandard::RESQML2_2: {
			gsoapProxy2_3 = gsoap_eml2_3::soap_new_resqml22__IjkGridRepresentation(repo->getGsoapContext());
			gsoap_eml2_3::_resqml22__IjkGridRepresentation* ijkGrid = static_cast<gsoap_eml2_3::_resqml22__IjkGridRepresentation*>(gsoapProxy2_3);
			ijkGrid->Ni = iCount;
			ijkGrid->Nj = jCount;
			ijkGrid->Nk = kCount;
			break;
		}
		default:
			throw std::invalid_argument("Unrecognized Energistics standard.");
		}
	}
	else {
		switch (repo->getDefaultResqmlVersion()) {
		case COMMON_NS::DataObjectRepository::EnergisticsStandard::RESQML2_0_1: {
			gsoapProxy2_0_1 = soap_new_resqml20__obj_USCORETruncatedIjkGridRepresentation(repo->getGsoapContext());
			gsoap_resqml2_0_1::_resqml20__TruncatedIjkGridRepresentation* ijkGrid = static_cast<gsoap_resqml2_0_1::_resqml20__TruncatedIjkGridRepresentation*>(gsoapProxy2_0_1);
			ijkGrid->Ni = iCount;
			ijkGrid->Nj = jCount;
			ijkGrid->Nk = kCount;
			break;
		}
		case COMMON_NS::DataObjectRepository::EnergisticsStandard::RESQML2_2: {
			gsoapProxy2_3 = gsoap_eml2_3::soap_new_resqml22__TruncatedIjkGridRepresentation(repo->getGsoapContext());
			gsoap_eml2_3::_resqml22__TruncatedIjkGridRepresentation* ijkGrid = static_cast<gsoap_eml2_3::_resqml22__TruncatedIjkGridRepresentation*>(gsoapProxy2_3);
			ijkGrid->Ni = iCount;
			ijkGrid->Nj = jCount;
			ijkGrid->Nk = kCount;
			break;
		}
		default:
			throw std::invalid_argument("Unrecognized Energistics standard.");
		}
	}

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "");

	repo->addOrReplaceDataObject(this);
}

AbstractIjkGridRepresentation::AbstractIjkGridRepresentation(COMMON_NS::DataObjectRepository * repo,
	const std::string & guid, const std::string & title,
	unsigned int iCount, unsigned int jCount, unsigned int kCount,
	bool withTruncatedPillars) :
	RESQML2_NS::AbstractColumnLayerGridRepresentation(withTruncatedPillars), splitInformation(nullptr), blockInformation(nullptr)
{
	init(repo, guid, title, iCount, jCount, kCount);
}

AbstractIjkGridRepresentation::AbstractIjkGridRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp,
	const std::string & guid, const std::string & title,
	unsigned int iCount, unsigned int jCount, unsigned int kCount,
	bool withTruncatedPillars) :
	RESQML2_NS::AbstractColumnLayerGridRepresentation(withTruncatedPillars), splitInformation(nullptr), blockInformation(nullptr)
{
	if (interp == nullptr) {
		throw invalid_argument("The interpretation of the IJK grid cannot be null.");
	}

	init(interp->getRepository(), guid, title, iCount, jCount, kCount);

	// relationhsips
	setInterpretation(interp);
}

gsoap_resqml2_0_1::_resqml20__IjkGridRepresentation* AbstractIjkGridRepresentation::getSpecializedGsoapProxy2_0_1() const
{
	cannotBePartial();
	return static_cast<_resqml20__IjkGridRepresentation*>(gsoapProxy2_0_1);
}

gsoap_resqml2_0_1::_resqml20__TruncatedIjkGridRepresentation* AbstractIjkGridRepresentation::getSpecializedTruncatedGsoapProxy2_0_1() const
{
	cannotBePartial();
	return static_cast<_resqml20__TruncatedIjkGridRepresentation*>(gsoapProxy2_0_1);
}

gsoap_eml2_3::_resqml22__IjkGridRepresentation* AbstractIjkGridRepresentation::getSpecializedGsoapProxy2_2() const
{
	cannotBePartial();
	return static_cast<gsoap_eml2_3::_resqml22__IjkGridRepresentation*>(gsoapProxy2_3);
}

gsoap_eml2_3::_resqml22__TruncatedIjkGridRepresentation* AbstractIjkGridRepresentation::getSpecializedTruncatedGsoapProxy2_2() const
{
	cannotBePartial();
	return static_cast<gsoap_eml2_3::_resqml22__TruncatedIjkGridRepresentation*>(gsoapProxy2_3);
}

gsoap_resqml2_0_1::resqml20__PointGeometry* AbstractIjkGridRepresentation::getPointGeometry2_0_1(unsigned int patchIndex) const
{
	if (gsoapProxy2_0_1 == nullptr) {
		throw logic_error("This is not a RESQML 2.0.1 dataobject.");
	}

	if (patchIndex == 0) {
		return isTruncated() ? getSpecializedTruncatedGsoapProxy2_0_1()->Geometry : getSpecializedGsoapProxy2_0_1()->Geometry;
	}

	throw range_error("There cannot be more than one patch is an ijk grid representation.");
}

gsoap_eml2_3::resqml22__PointGeometry* AbstractIjkGridRepresentation::getPointGeometry2_2(unsigned int patchIndex) const
{
	if (gsoapProxy2_3 == nullptr) {
		throw logic_error("This is not a RESQML 2.2 dataobject.");
	}

	if (patchIndex == 0) {
		return isTruncated() ? getSpecializedTruncatedGsoapProxy2_2()->Geometry : getSpecializedGsoapProxy2_2()->Geometry;
	}

	throw range_error("There cannot be more than one patch is an ijk grid representation.");
}

unsigned int AbstractIjkGridRepresentation::getICellCount() const
{
	const ULONG64 iCellCount = gsoapProxy2_0_1 != nullptr
		? (isTruncated() ? getSpecializedTruncatedGsoapProxy2_0_1()->Ni : getSpecializedGsoapProxy2_0_1()->Ni)
		: (isTruncated() ? getSpecializedTruncatedGsoapProxy2_2()->Ni : getSpecializedGsoapProxy2_2()->Ni);

	if (iCellCount > (std::numeric_limits<unsigned int>::max)()) {
		throw std::range_error("There are too much cells against I dimension.");
	}

	return static_cast<unsigned int>(iCellCount);
}

void AbstractIjkGridRepresentation::setICellCount(const unsigned int & iCount)
{
	if (!isTruncated()) {
		if (gsoapProxy2_0_1 != nullptr) {
			getSpecializedGsoapProxy2_0_1()->Ni = iCount;
		}
		else {
			getSpecializedGsoapProxy2_2()->Ni = iCount;
		}
	}
	else {
		if (gsoapProxy2_0_1 != nullptr) {
			getSpecializedTruncatedGsoapProxy2_0_1()->Ni = iCount;
		}
		else {
			getSpecializedTruncatedGsoapProxy2_2()->Ni = iCount;
		}
	}
}

unsigned int AbstractIjkGridRepresentation::getJCellCount() const
{
	const ULONG64 jCellCount = gsoapProxy2_0_1 != nullptr
		? (isTruncated() ? getSpecializedTruncatedGsoapProxy2_0_1()->Nj : getSpecializedGsoapProxy2_0_1()->Nj)
		: (isTruncated() ? getSpecializedTruncatedGsoapProxy2_2()->Nj : getSpecializedGsoapProxy2_2()->Nj);

	if (jCellCount > (std::numeric_limits<unsigned int>::max)()) {
		throw std::range_error("There are too much cells against J dimension.");
	}

	return static_cast<unsigned int>(jCellCount);
}

void AbstractIjkGridRepresentation::setJCellCount(const unsigned int & jCount)
{
	if (!isTruncated()) {
		if (gsoapProxy2_0_1 != nullptr) {
			getSpecializedGsoapProxy2_0_1()->Nj = jCount;
		}
		else {
			getSpecializedGsoapProxy2_2()->Nj = jCount;
		}
	}
	else {
		if (gsoapProxy2_0_1 != nullptr) {
			getSpecializedTruncatedGsoapProxy2_0_1()->Nj = jCount;
		}
		else {
			getSpecializedTruncatedGsoapProxy2_2()->Nj = jCount;
		}
	}
}

bool AbstractIjkGridRepresentation::isRightHanded() const
{
	if (gsoapProxy2_0_1 != nullptr) {
		gsoap_resqml2_0_1::resqml20__IjkGridGeometry* geom = static_cast<gsoap_resqml2_0_1::resqml20__IjkGridGeometry*>(getPointGeometry2_0_1(0));
		if (geom != nullptr) {
			return geom->GridIsRighthanded;
		}
	}
	else {
		gsoap_eml2_3::resqml22__IjkGridGeometry* geom = static_cast<gsoap_eml2_3::resqml22__IjkGridGeometry*>(getPointGeometry2_2(0));
		if (geom != nullptr) {
			return geom->GridIsRighthanded;
		}
	}

	throw logic_error("The IJK grid has no geometry. Or, the IJK grid is in an unrecognized version of RESQML.");
}

void AbstractIjkGridRepresentation::getPillarsOfSplitCoordinateLines(unsigned int * pillarIndices, bool reverseIAxis, bool reverseJAxis) const
{
	if (gsoapProxy2_0_1 != nullptr) {
		gsoap_resqml2_0_1::resqml20__IjkGridGeometry* geom = static_cast<gsoap_resqml2_0_1::resqml20__IjkGridGeometry*>(getPointGeometry2_0_1(0));
		if (geom == nullptr || geom->SplitCoordinateLines == nullptr) {
			throw invalid_argument("There is no geometry or no split coordinate line in this grid.");
		}
		if (geom->SplitCoordinateLines->PillarIndices->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__IntegerHdf5Array) {
			eml20__Hdf5Dataset const * dataset = static_cast<resqml20__IntegerHdf5Array*>(geom->SplitCoordinateLines->PillarIndices)->Values;
			EML2_NS::AbstractHdfProxy * hdfProxy = getHdfProxyFromDataset(dataset);
			hdfProxy->readArrayNdOfUIntValues(dataset->PathInHdfFile, pillarIndices);
		}
		else {
			throw std::logic_error("Not implemented yet");
		}
	}
	else {
		gsoap_eml2_3::resqml22__IjkGridGeometry* geom = static_cast<gsoap_eml2_3::resqml22__IjkGridGeometry*>(getPointGeometry2_2(0));
		if (geom == nullptr || geom->ColumnLayerSplitCoordinateLines == nullptr) {
			throw invalid_argument("There is no geometry or no split coordinate line in this grid.");
		}
		if (geom->ColumnLayerSplitCoordinateLines->PillarIndices->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__IntegerExternalArray) {
			gsoap_eml2_3::eml23__ExternalDataset const * dataset = static_cast<gsoap_eml2_3::eml23__IntegerExternalArray*>(geom->ColumnLayerSplitCoordinateLines->PillarIndices)->Values;
			EML2_NS::AbstractHdfProxy * hdfProxy = getHdfProxyFromDataset(dataset->ExternalFileProxy[0]);
			hdfProxy->readArrayNdOfUIntValues(dataset->ExternalFileProxy[0]->PathInExternalFile, pillarIndices);
		}
		else {
			throw std::logic_error("Not implemented yet");
		}
	}

	if (reverseIAxis || reverseJAxis) {
		const unsigned int iPillarCount = getICellCount()+1;
		if (reverseIAxis) {
			for (unsigned int index = 0; index < getSplitCoordinateLineCount(); ++index) {
				const unsigned int iPillar = pillarIndices[index] % iPillarCount;
				const unsigned int jPillar = pillarIndices[index] / iPillarCount;
				pillarIndices[index] = (getICellCount() - iPillar) + jPillar*iPillarCount;
			}
		}
		if (reverseJAxis) {
			for (unsigned int index = 0; index < getSplitCoordinateLineCount(); ++index) {
				const unsigned int iPillar = pillarIndices[index] % iPillarCount;
				const unsigned int jPillar = pillarIndices[index] / iPillarCount;
				pillarIndices[index] = iPillar + (getJCellCount()-jPillar)*iPillarCount;
			}
		}
	}
}

void AbstractIjkGridRepresentation::getColumnsOfSplitCoordinateLines(unsigned int * columnIndices, bool reverseIAxis, bool reverseJAxis) const
{
	hssize_t datasetValueCount = 0;
	if (gsoapProxy2_0_1 != nullptr) {
		gsoap_resqml2_0_1::resqml20__IjkGridGeometry* geom = static_cast<gsoap_resqml2_0_1::resqml20__IjkGridGeometry*>(getPointGeometry2_0_1(0));
		if (geom == nullptr || geom->SplitCoordinateLines == nullptr) {
			throw invalid_argument("There is no geometry or no split coordinate line in this IJK grid.");
		}

		if (geom->SplitCoordinateLines->ColumnsPerSplitCoordinateLine->Elements->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__IntegerHdf5Array) {
			eml20__Hdf5Dataset const * dataset = static_cast<resqml20__IntegerHdf5Array*>(geom->SplitCoordinateLines->ColumnsPerSplitCoordinateLine->Elements)->Values;
			EML2_NS::AbstractHdfProxy * hdfProxy = getHdfProxyFromDataset(dataset);
			hdfProxy->readArrayNdOfUIntValues(dataset->PathInHdfFile, columnIndices);
			if (reverseIAxis || reverseJAxis) {
				datasetValueCount = hdfProxy->getElementCount(dataset->PathInHdfFile);
			}
		}
		else
			throw std::logic_error("Not implemented yet");
	}
	else {
		gsoap_eml2_3::resqml22__IjkGridGeometry* geom = static_cast<gsoap_eml2_3::resqml22__IjkGridGeometry*>(getPointGeometry2_2(0));
		if (geom == nullptr || geom->ColumnLayerSplitCoordinateLines == nullptr) {
			throw invalid_argument("There is no geometry or no split coordinate line in this IJK grid.");
		}
		if (geom->ColumnLayerSplitCoordinateLines->ColumnsPerSplitCoordinateLine->Elements->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__IntegerExternalArray) {
			gsoap_eml2_3::eml23__ExternalDataset const * dataset = static_cast<gsoap_eml2_3::eml23__IntegerExternalArray*>(geom->ColumnLayerSplitCoordinateLines->ColumnsPerSplitCoordinateLine->Elements)->Values;
			EML2_NS::AbstractHdfProxy * hdfProxy = getHdfProxyFromDataset(dataset->ExternalFileProxy[0]);
			hdfProxy->readArrayNdOfUIntValues(dataset->ExternalFileProxy[0]->PathInExternalFile, columnIndices);
			if (reverseIAxis || reverseJAxis) {
				datasetValueCount = hdfProxy->getElementCount(dataset->ExternalFileProxy[0]->PathInExternalFile);
			}
		}
		else {
			throw std::logic_error("Not implemented yet");
		}
	}

	if (datasetValueCount > 0) {
		if (reverseIAxis) {
			for (unsigned int index = 0; index < datasetValueCount; ++index) {
				const unsigned int iColumn = columnIndices[index] % getICellCount();
				const unsigned int jColumn = columnIndices[index] / getICellCount();
				columnIndices[index] = (getICellCount() - 1 - iColumn) + jColumn*getICellCount();
			}
		}
		if (reverseJAxis) {
			for (unsigned int index = 0; index < datasetValueCount; ++index) {
				const unsigned int iColumn = columnIndices[index] % getICellCount();
				const unsigned int jColumn = columnIndices[index] / getICellCount();
				columnIndices[index] = iColumn + (getJCellCount() - 1 - jColumn)*getICellCount();
			}
		}
	}
}

void AbstractIjkGridRepresentation::getColumnCountOfSplitCoordinateLines(unsigned int * columnIndexCountPerSplitCoordinateLine) const
{
	if (gsoapProxy2_0_1 != nullptr) {
		gsoap_resqml2_0_1::resqml20__IjkGridGeometry* geom = static_cast<gsoap_resqml2_0_1::resqml20__IjkGridGeometry*>(getPointGeometry2_0_1(0));
		if (geom == nullptr || geom->SplitCoordinateLines == nullptr) {
			throw invalid_argument("There is no geometry or no split coordinate line in this grid.");
		}
		if (geom->SplitCoordinateLines->ColumnsPerSplitCoordinateLine->CumulativeLength->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__IntegerHdf5Array) {
			eml20__Hdf5Dataset const * dataset = static_cast<resqml20__IntegerHdf5Array*>(geom->SplitCoordinateLines->ColumnsPerSplitCoordinateLine->CumulativeLength)->Values;
			EML2_NS::AbstractHdfProxy * hdfProxy = getHdfProxyFromDataset(dataset);
			hdfProxy->readArrayNdOfUIntValues(dataset->PathInHdfFile, columnIndexCountPerSplitCoordinateLine);
		}
		else {
			throw std::logic_error("Not implemented yet");
		}
	}
	else {
		gsoap_eml2_3::resqml22__IjkGridGeometry* geom = static_cast<gsoap_eml2_3::resqml22__IjkGridGeometry*>(getPointGeometry2_2(0));
		if (geom == nullptr || geom->ColumnLayerSplitCoordinateLines == nullptr) {
			throw invalid_argument("There is no geometry or no split coordinate line in this IJK grid.");
		}
		if (geom->ColumnLayerSplitCoordinateLines->ColumnsPerSplitCoordinateLine->CumulativeLength->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__IntegerExternalArray) {
			gsoap_eml2_3::eml23__ExternalDataset const * dataset = static_cast<gsoap_eml2_3::eml23__IntegerExternalArray*>(geom->ColumnLayerSplitCoordinateLines->ColumnsPerSplitCoordinateLine->CumulativeLength)->Values;
			EML2_NS::AbstractHdfProxy * hdfProxy = getHdfProxyFromDataset(dataset->ExternalFileProxy[0]);
			hdfProxy->readArrayNdOfUIntValues(dataset->ExternalFileProxy[0]->PathInExternalFile, columnIndexCountPerSplitCoordinateLine);
		}
		else {
			throw std::logic_error("Not implemented yet");
		}
	}
}

unsigned long AbstractIjkGridRepresentation::getSplitCoordinateLineCount() const
{
	ULONG64 splitCoordinateLineCount = 0;
	if (gsoapProxy2_0_1 != nullptr) {
		gsoap_resqml2_0_1::resqml20__IjkGridGeometry* geom = static_cast<gsoap_resqml2_0_1::resqml20__IjkGridGeometry*>(getPointGeometry2_0_1(0));
		if (geom == nullptr) {
			throw invalid_argument("There is no geometry on this IJK grid.");
		}
		if (geom->SplitCoordinateLines != nullptr) {
			splitCoordinateLineCount = geom->SplitCoordinateLines->Count;
		}
	}
	else if (gsoapProxy2_3 != nullptr) {
		gsoap_eml2_3::resqml22__IjkGridGeometry* geom = static_cast<gsoap_eml2_3::resqml22__IjkGridGeometry*>(getPointGeometry2_2(0));
		if (geom == nullptr) {
			throw invalid_argument("There is no geometry on this IJK grid.");
		}
		if (geom->ColumnLayerSplitCoordinateLines != nullptr) {
			splitCoordinateLineCount = geom->ColumnLayerSplitCoordinateLines->Count;
		}
	}

	if (splitCoordinateLineCount > (std::numeric_limits<unsigned int>::max)()) {
		throw std::range_error("There are too much split coordinate lines.");
	}

	return static_cast<unsigned long>(splitCoordinateLineCount);
}

unsigned long AbstractIjkGridRepresentation::getBlockSplitCoordinateLineCount() const
{
	if (blockInformation == nullptr) {
		throw invalid_argument("The block information must have been loaded first.");
	}

	unsigned long splitCoordinateLineCount = 0;
	
	// I traverse all pillars of the block
	for (unsigned int jPillarIndex = blockInformation->jInterfaceStart; jPillarIndex <= blockInformation->jInterfaceEnd; ++jPillarIndex) {
		for (unsigned int iPillarIndex = blockInformation->iInterfaceStart; iPillarIndex <= blockInformation->iInterfaceEnd; iPillarIndex++) {
			const unsigned int pillarIndex = getGlobalIndexPillarFromIjIndex(iPillarIndex, jPillarIndex);

			// I traverse all corresponding splitted coordinate lines
			for (size_t splitCoordinateLineIndex = 0; splitCoordinateLineIndex < splitInformation[pillarIndex].size(); ++splitCoordinateLineIndex) {
				// I traverse all columns adjacent to the split coordinate line
				for (size_t columnIndex = 0; columnIndex < splitInformation[pillarIndex][splitCoordinateLineIndex].second.size(); ++columnIndex) {
					unsigned int iColumnIndex = getIColumnFromGlobalIndex(splitInformation[pillarIndex][splitCoordinateLineIndex].second[columnIndex]);
					unsigned int jColumnIndex = getJColumnFromGlobalIndex(splitInformation[pillarIndex][splitCoordinateLineIndex].second[columnIndex]);

					// if the split coordinate line is adjacent to the cell of the block, I count the corresponding splited pillar
					if ((iColumnIndex >= blockInformation->iInterfaceStart && iColumnIndex <= blockInformation->iInterfaceEnd - 1) && (jColumnIndex >= blockInformation->jInterfaceStart && jColumnIndex <= blockInformation->jInterfaceEnd - 1)) {
						++splitCoordinateLineCount;

						break; // to be sure not to count several time a same split pillar
					}
				}
			}
		}
	}

	return splitCoordinateLineCount;
}


ULONG64 AbstractIjkGridRepresentation::getSplitNodeCount() const
{
	if (gsoapProxy2_0_1 != nullptr) {
		gsoap_resqml2_0_1::resqml20__IjkGridGeometry* geom = static_cast<gsoap_resqml2_0_1::resqml20__IjkGridGeometry*>(getPointGeometry2_0_1(0));
		if (geom == nullptr) {
			throw invalid_argument("There is no geometry on this grid.");
		}

		return geom->SplitNodes != nullptr ? geom->SplitNodes->Count : 0;
	}
	else {
		gsoap_eml2_3::resqml22__IjkGridGeometry* geom = static_cast<gsoap_eml2_3::resqml22__IjkGridGeometry*>(getPointGeometry2_2(0));
		if (geom == nullptr) {
			throw invalid_argument("There is no geometry on this IJK grid.");
		}
		return geom->SplitNodePatch != nullptr ? geom->SplitNodePatch->Count : 0;
	}
}

void AbstractIjkGridRepresentation::getPillarGeometryIsDefined(bool * pillarGeometryIsDefined, bool reverseIAxis, bool reverseJAxis) const
{
	const unsigned int pillarCount = getPillarCount();
	if (gsoapProxy2_0_1 != nullptr) {
		gsoap_resqml2_0_1::resqml20__IjkGridGeometry* geom = static_cast<gsoap_resqml2_0_1::resqml20__IjkGridGeometry*>(getPointGeometry2_0_1(0));
		if (geom == nullptr) {
			throw invalid_argument("There is no geometry on this grid.");
		}
		if (geom->PillarGeometryIsDefined->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__BooleanHdf5Array)
		{
			eml20__Hdf5Dataset const * dataset = static_cast<resqml20__BooleanHdf5Array*>(geom->PillarGeometryIsDefined)->Values;
			EML2_NS::AbstractHdfProxy * hdfProxy = getHdfProxyFromDataset(dataset);
			std::unique_ptr<char[]> tmp(new char[pillarCount]);
			hdfProxy->readArrayNdOfCharValues(dataset->PathInHdfFile, tmp.get());
			for (unsigned int i = 0; i < pillarCount; ++i) {
				pillarGeometryIsDefined[i] = tmp[i] != 0;
			}
		}
		else if (geom->PillarGeometryIsDefined->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__BooleanConstantArray) {
			const bool enabled = static_cast<resqml20__BooleanConstantArray*>(geom->PillarGeometryIsDefined)->Value;
			for (unsigned int i = 0; i < pillarCount; ++i) {
				pillarGeometryIsDefined[i] = enabled;
			}
		}
		else {
			throw std::logic_error("Not yet implemented");
		}
	}
	else {
		gsoap_eml2_3::resqml22__IjkGridGeometry* geom = static_cast<gsoap_eml2_3::resqml22__IjkGridGeometry*>(getPointGeometry2_2(0));
		if (geom == nullptr) {
			throw invalid_argument("There is no geometry on this IJK grid.");
		}
		if (geom->PillarGeometryIsDefined->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__BooleanExternalArray)
		{
			gsoap_eml2_3::eml23__ExternalDataset const * dataset = static_cast<gsoap_eml2_3::eml23__BooleanExternalArray*>(geom->PillarGeometryIsDefined)->Values;
			EML2_NS::AbstractHdfProxy * hdfProxy = getHdfProxyFromDataset(dataset->ExternalFileProxy[0]);
			std::unique_ptr<char[]> tmp(new char[pillarCount]);
			hdfProxy->readArrayNdOfCharValues(dataset->ExternalFileProxy[0]->PathInExternalFile, tmp.get());
			for (unsigned int i = 0; i < pillarCount; ++i) {
				pillarGeometryIsDefined[i] = tmp[i] != 0;
			}
		}
		else if (geom->PillarGeometryIsDefined->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__BooleanConstantArray) {
			const bool enabled = static_cast<gsoap_eml2_3::eml23__BooleanConstantArray*>(geom->PillarGeometryIsDefined)->Value;
			for (unsigned int i = 0; i < pillarCount; ++i) {
				pillarGeometryIsDefined[i] = enabled;
			}
		}
		else {
			throw std::logic_error("Not yet implemented");
		}
	}

	if (reverseIAxis || reverseJAxis)
	{
		const unsigned int iPillarCount = getICellCount()+1;
		const unsigned int jPillarCount = getJCellCount()+1;
		const unsigned int arrayCount = iPillarCount * jPillarCount;

		// Copy in order not to modify the controlPoints pointer
		std::unique_ptr<bool[]> initialPillarGeometryIsDefined(new bool[arrayCount]);
		for (unsigned int index = 0; index < arrayCount; ++index) {
			initialPillarGeometryIsDefined[index] = pillarGeometryIsDefined[index];
		}

		if (reverseIAxis) {
			unsigned int pillarIndex = 0;
			for (unsigned int j = 0; j < jPillarCount; ++j) {
				for (unsigned int i = 0; i < iPillarCount; ++i) {
					pillarGeometryIsDefined[pillarIndex] = initialPillarGeometryIsDefined[getICellCount() - i + j*iPillarCount];
					++pillarIndex;
				}
			}
		}

		if (reverseJAxis) {
			unsigned int pillarIndex = 0;
			for (unsigned int j = 0; j < jPillarCount; ++j) {
				for (unsigned int i = 0; i < iPillarCount; ++i) {
					pillarGeometryIsDefined[pillarIndex] = initialPillarGeometryIsDefined[i + (getJCellCount() - j)*iPillarCount];
					++pillarIndex;
				}
			}
		}
	}
}

bool AbstractIjkGridRepresentation::hasEnabledCellInformation() const
{
	if (gsoapProxy2_0_1 != nullptr) {
		gsoap_resqml2_0_1::resqml20__IjkGridGeometry* geom = static_cast<gsoap_resqml2_0_1::resqml20__IjkGridGeometry*>(getPointGeometry2_0_1(0));
		return geom != nullptr && geom->CellGeometryIsDefined != nullptr;
	}
	else {
		gsoap_eml2_3::resqml22__IjkGridGeometry* geom = static_cast<gsoap_eml2_3::resqml22__IjkGridGeometry*>(getPointGeometry2_2(0));
		return geom != nullptr && geom->CellGeometryIsDefined != nullptr;
	}
}

void AbstractIjkGridRepresentation::getEnabledCells(bool * enabledCells, bool reverseIAxis, bool reverseJAxis, bool reverseKAxis) const
{
	if (!hasEnabledCellInformation()) {
		throw invalid_argument("The grid has no geometry or no information about enabled cells.");
	}

	const ULONG64 cellCount = getCellCount();
	if (gsoapProxy2_0_1 != nullptr) {
		gsoap_resqml2_0_1::resqml20__IjkGridGeometry* geom = static_cast<gsoap_resqml2_0_1::resqml20__IjkGridGeometry*>(getPointGeometry2_0_1(0));
		if (geom == nullptr) {
			throw invalid_argument("There is no geometry on this IJK grid.");
		}
		if (geom->CellGeometryIsDefined->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__BooleanHdf5Array) {
			eml20__Hdf5Dataset const * dataset = static_cast<resqml20__BooleanHdf5Array*>(geom->CellGeometryIsDefined)->Values;
			EML2_NS::AbstractHdfProxy * hdfProxy = getHdfProxyFromDataset(dataset);
			std::unique_ptr<char[]> tmp(new char[cellCount]);
			hdfProxy->readArrayNdOfCharValues(dataset->PathInHdfFile, tmp.get());
			for (ULONG64 i = 0; i < cellCount; ++i) {
				enabledCells[i] = tmp[i] != 0;
			}
		}
		else if (geom->CellGeometryIsDefined->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__BooleanConstantArray) {
			const bool enabled = static_cast<resqml20__BooleanConstantArray*>(geom->CellGeometryIsDefined)->Value;
			for (ULONG64 i = 0; i < cellCount; ++i) {
				enabledCells[i] = enabled;
			}
		}
		else {
			throw std::logic_error("Not implemented yet");
		}
	}
	else {
		gsoap_eml2_3::resqml22__IjkGridGeometry* geom = static_cast<gsoap_eml2_3::resqml22__IjkGridGeometry*>(getPointGeometry2_2(0));
		if (geom == nullptr) {
			throw invalid_argument("There is no geometry on this IJK grid.");
		}
		if (geom->CellGeometryIsDefined->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__BooleanExternalArray) {
			gsoap_eml2_3::eml23__ExternalDataset const * dataset = static_cast<gsoap_eml2_3::eml23__BooleanExternalArray*>(geom->CellGeometryIsDefined)->Values;
			EML2_NS::AbstractHdfProxy * hdfProxy = getHdfProxyFromDataset(dataset->ExternalFileProxy[0]);
			std::unique_ptr<char[]> tmp(new char[cellCount]);
			hdfProxy->readArrayNdOfCharValues(dataset->ExternalFileProxy[0]->PathInExternalFile, tmp.get());
			for (unsigned int i = 0; i < cellCount; ++i) {
				enabledCells[i] = tmp[i] != 0;
			}
		}
		else if (geom->CellGeometryIsDefined->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__BooleanConstantArray) {
			const bool enabled = static_cast<gsoap_eml2_3::eml23__BooleanConstantArray*>(geom->CellGeometryIsDefined)->Value;
			for (ULONG64 i = 0; i < cellCount; ++i) {
				enabledCells[i] = enabled;
			}
		}
		else {
			throw std::logic_error("Not implemented yet");
		}
	}

	// Copy in order not to modify the controlPoints pointer
	if (reverseIAxis || reverseJAxis || reverseKAxis) {
		const ULONG64 arrayCount = getCellCount();
		std::unique_ptr<bool[]> initialCellGeometryIsDefined(new bool[arrayCount]);
		for (ULONG64 index = 0; index < arrayCount; ++index) {
			initialCellGeometryIsDefined[index] = enabledCells[index];
		}

		if (reverseIAxis) {
			unsigned int cellIndex = 0;
			for (unsigned int k = 0; k < getKCellCount(); ++k) {
				for (unsigned int j = 0; j < getJCellCount(); ++j) {
					for (unsigned int i = 0; i < getICellCount(); ++i) {
						enabledCells[cellIndex] = initialCellGeometryIsDefined[getICellCount() - 1 - i + j*getICellCount() + k*getICellCount()*getJCellCount()];
						++cellIndex;
					}
				}
			}
		}

		if (reverseJAxis) {
			unsigned int cellIndex = 0;
			for (unsigned int k = 0; k < getKCellCount(); ++k) {
				for (unsigned int j = 0; j < getJCellCount(); ++j) {
					for (unsigned int i = 0; i < getICellCount(); ++i) {
						enabledCells[cellIndex] = initialCellGeometryIsDefined[i + (getJCellCount() - 1 -j)*getICellCount() + k*getICellCount()*getJCellCount()];
						++cellIndex;
					}
				}
			}
		}

		if (reverseKAxis) {
			unsigned int cellIndex = 0;
			for (unsigned int k = 0; k < getKCellCount(); ++k) {
				for (unsigned int j = 0; j < getJCellCount(); ++j) {
					for (unsigned int i = 0; i < getICellCount(); ++i) {
						enabledCells[cellIndex] = initialCellGeometryIsDefined[i + j*getICellCount() + (getKCellCount() - 1 -k)*getICellCount()*getJCellCount()];
						++cellIndex;
					}
				}
			}
		}
	}
}

unsigned int AbstractIjkGridRepresentation::getIPillarFromGlobalIndex(unsigned int globalIndex) const
{
	if (globalIndex >= getPillarCount()) {
		throw out_of_range("The pillar index is out of range.");
	}

	return globalIndex % (getICellCount() + 1);
}

unsigned int AbstractIjkGridRepresentation::getJPillarFromGlobalIndex(unsigned int globalIndex) const
{
	if (globalIndex >= getPillarCount()) {
		throw out_of_range("The pillar index is out of range.");
	}

	return globalIndex / (getICellCount() + 1);
}

unsigned int AbstractIjkGridRepresentation::getGlobalIndexPillarFromIjIndex(unsigned int iPillar, unsigned int jPillar) const
{
	if (iPillar > getICellCount()) {
		throw out_of_range("The pillar I index is out of range.");
	}
	if (jPillar > getJCellCount()) {
		throw out_of_range("The pillar J index is out of range.");
	}

	return iPillar + (getICellCount() + 1) * jPillar;
}

unsigned int AbstractIjkGridRepresentation::getIColumnFromGlobalIndex(unsigned int globalIndex) const
{
	if (globalIndex >= getColumnCount()) {
		throw out_of_range("The column index is out of range.");
	}

	return globalIndex % getICellCount();
}

unsigned int AbstractIjkGridRepresentation::getJColumnFromGlobalIndex(unsigned int globalIndex) const
{
	if (globalIndex >= getColumnCount()) {
		throw out_of_range("The column index is out of range.");
	}

	return globalIndex / getICellCount();
}

unsigned int AbstractIjkGridRepresentation::getGlobalIndexColumnFromIjIndex(unsigned int iColumn, unsigned int jColumn) const
{
	if (iColumn >= getICellCount()) {
		throw out_of_range("The column I index is out of range.");
	}
	if (jColumn >= getJCellCount()) {
		throw out_of_range("The column J index is out of range.");
	}

	return iColumn + getICellCount() * jColumn;
}

unsigned int AbstractIjkGridRepresentation::getGlobalIndexCellFromIjkIndex(unsigned int iCell, unsigned int jCell, unsigned int kCell) const
{
	if (iCell >= getICellCount()) {
		throw out_of_range("The cell I index is out of range.");
	}
	if (jCell >= getJCellCount()) {
		throw out_of_range("The cell J index is out of range.");
	}
	if (kCell >= getKCellCount()) {
		throw out_of_range("The cell K index is out of range.");
	}

	return iCell + getICellCount() * jCell + getColumnCount() * kCell;
}

void AbstractIjkGridRepresentation::loadSplitInformation()
{
	unloadSplitInformation();
	splitInformation = new std::vector< std::pair< unsigned int, std::vector<unsigned int> > >[getPillarCount()];

	const auto splitCoordinateLineCount = getSplitCoordinateLineCount();
	if (splitCoordinateLineCount > 0) {
		// Read the split information
		std::unique_ptr<unsigned int[]> splitPillars(new unsigned int[splitCoordinateLineCount]);
		getPillarsOfSplitCoordinateLines(splitPillars.get());
		std::unique_ptr<unsigned int[]> columnIndexCumulativeCountPerSplitCoordinateLine(new unsigned int[splitCoordinateLineCount]);
		getColumnCountOfSplitCoordinateLines(columnIndexCumulativeCountPerSplitCoordinateLine.get());
		std::unique_ptr<unsigned int[]> splitColumnIndices(new unsigned int [columnIndexCumulativeCountPerSplitCoordinateLine[splitCoordinateLineCount - 1]]);
		getColumnsOfSplitCoordinateLines(splitColumnIndices.get());

		// Rearrange the split information
		std::pair< unsigned int, std::vector<unsigned int> > splittedColumns;
		splittedColumns.first = 0;
		for (unsigned int splitColumnIndex = 0;
			splitColumnIndex < columnIndexCumulativeCountPerSplitCoordinateLine[0];
			++splitColumnIndex) {
			splittedColumns.second.push_back(splitColumnIndices[splitColumnIndex]);
		}
		splitInformation[splitPillars[0]].push_back(splittedColumns);
		for (unsigned int splitCoordinateLineIndex = 1; splitCoordinateLineIndex < splitCoordinateLineCount; ++splitCoordinateLineIndex) {
			splittedColumns.first = splitCoordinateLineIndex;
			splittedColumns.second.clear();
			for (unsigned int splitColumnIndex = columnIndexCumulativeCountPerSplitCoordinateLine[splitCoordinateLineIndex-1];
				splitColumnIndex < columnIndexCumulativeCountPerSplitCoordinateLine[splitCoordinateLineIndex];
				++splitColumnIndex) {
				splittedColumns.second.push_back(splitColumnIndices[splitColumnIndex]);
			}
			splitInformation[splitPillars[splitCoordinateLineIndex]].push_back(splittedColumns);
		}
	}
}

void AbstractIjkGridRepresentation::loadBlockInformation(unsigned int iInterfaceStart, unsigned int iInterfaceEnd, unsigned int jInterfaceStart, unsigned int jInterfaceEnd, unsigned int kInterfaceStart, unsigned int kInterfaceEnd)
{
	if (splitInformation == nullptr)
		throw invalid_argument("The split information must have been loaded first.");

	if (iInterfaceEnd > getICellCount())
		throw out_of_range("iInterfaceEnd is out of boundaries.");
	if (iInterfaceStart > iInterfaceEnd)
		throw range_error("iInterfaceStart > iInterfaceEnd");

	if (jInterfaceEnd > getJCellCount())
		throw out_of_range("jInterfaceEnd is out of boundaries.");
	if (jInterfaceStart > jInterfaceEnd)
		throw range_error("jInterfaceStart > jInterfaceEnd");

	if (kInterfaceEnd > getKCellCount())
		throw out_of_range("kInterfaceEnd is out of boundaries.");
	if (kInterfaceStart > kInterfaceEnd)
		throw range_error("kInterfaceStart > kInterfaceEnd");

	if (blockInformation != nullptr) {
		delete blockInformation;
	}

	blockInformation = new BlockInformation();

	blockInformation->iInterfaceStart = iInterfaceStart;
	blockInformation->iInterfaceEnd = iInterfaceEnd;
	blockInformation->jInterfaceStart = jInterfaceStart;
	blockInformation->jInterfaceEnd = jInterfaceEnd;
	blockInformation->kInterfaceStart = kInterfaceStart;
	blockInformation->kInterfaceEnd = kInterfaceEnd;

	// seting mapping between global and local (to the block) split coordinate lines index
	unsigned int splitCoordinateLineHdfLocalIndex = (iInterfaceEnd - iInterfaceStart + 1) * (jInterfaceEnd - jInterfaceStart + 1);
	for (unsigned int jPillarIndex = jInterfaceStart; jPillarIndex <= jInterfaceEnd; ++jPillarIndex) {
		for (unsigned int iPillarIndex = iInterfaceStart; iPillarIndex <= iInterfaceEnd; iPillarIndex++) {
			const unsigned int pillarIndex = getGlobalIndexPillarFromIjIndex(iPillarIndex, jPillarIndex);

			if (!splitInformation[pillarIndex].empty()) {
				// here is a split pillar

				// traversing all split coordinate lines corresponding to the current splitted pillar
				for (unsigned int splitCoordinateLineIndex = 0; splitCoordinateLineIndex < splitInformation[pillarIndex].size(); ++splitCoordinateLineIndex) {
					// traversing adjacent columns, it current column is in the bloc, corresponding coordinate line is added to the selected region
					for (unsigned int columnIndex = 0; columnIndex < splitInformation[pillarIndex][splitCoordinateLineIndex].second.size(); ++columnIndex) {
						const unsigned int iColumnIndex = getIColumnFromGlobalIndex(splitInformation[pillarIndex][splitCoordinateLineIndex].second[columnIndex]);
						const unsigned int jColumnIndex = getJColumnFromGlobalIndex(splitInformation[pillarIndex][splitCoordinateLineIndex].second[columnIndex]);

						if ((iColumnIndex >= iInterfaceStart && iColumnIndex < iInterfaceEnd) && (jColumnIndex >= jInterfaceStart && jColumnIndex < jInterfaceEnd)) {
							// here is a split coordinate line impacting the bloc
							(blockInformation->globalToLocalSplitCoordinateLinesIndex)[splitInformation[pillarIndex][splitCoordinateLineIndex].first] = splitCoordinateLineHdfLocalIndex;
							++splitCoordinateLineHdfLocalIndex;

							break; // in order to be sure not adding twice a same coordinate line if it is adjacent to several columns within the bloc
						}
					}
				}
			}
		}
	}
}

void AbstractIjkGridRepresentation::unloadSplitInformation()
{
	if (splitInformation != nullptr) {
		delete [] splitInformation;
		splitInformation = nullptr;
	}
}

unsigned int AbstractIjkGridRepresentation::getFaceCount() const
{
	unsigned int faceCount = getICellCount() * getJCellCount() * (getKCellCount() + 1); // K faces which are assumed to be not splitted
	faceCount += getICellCount() * (getJCellCount() + 1) * getKCellCount(); // non splitted J faces
	faceCount += (getICellCount() + 1) * getJCellCount() * getKCellCount(); // non splitted I faces

	if (getSplitCoordinateLineCount() > 0)
	{
		// i split
		for (unsigned int j = 0; j < getJCellCount(); ++j) {
			for (unsigned int i = 0; i < getICellCount() - 1; ++i) {
				if (isColumnEdgeSplitted(i, j, 1)) {
					faceCount += getKCellCount();
				}
			}
		}

		// j split
		for (unsigned int j = 0; j < getJCellCount() - 1; ++j) {
			for (unsigned int i = 0; i < getICellCount(); ++i) {
				if (isColumnEdgeSplitted(i, j, 2)) {
					faceCount += getKCellCount();
				}
			}
		}
	}

	return faceCount;
}

bool AbstractIjkGridRepresentation::isColumnEdgeSplitted(unsigned int iColumn, unsigned int jColumn, unsigned int edge) const
{
	if (splitInformation == nullptr)
		throw invalid_argument("The split information must have been loaded first.");
	if (iColumn > getICellCount())
		throw out_of_range("I column is out of range.");
	if (jColumn > getJCellCount())
		throw out_of_range("J column is out of range.");
	if (edge > 3)
		throw out_of_range("Edge is out of range.");

	// Pillar
	unsigned int iPillarIndex = iColumn;
	if (edge == 1 || edge == 2)
		++iPillarIndex;
	unsigned int jPillarIndex = jColumn;
	if (edge == 2 || edge == 3)
		++jPillarIndex;

	// Other column identification
	int iOtherColum = iColumn;
	int jOtherColum = jColumn;
					
	if (edge == 0) --jOtherColum;
	else if (edge == 1) ++iOtherColum;
	else if (edge == 2) ++jOtherColum;
	else if (edge == 3) --iOtherColum;

	if (iOtherColum < 0 || jOtherColum < 0 || static_cast<unsigned int>(iOtherColum) >= getICellCount() || static_cast<unsigned int>(jOtherColum) >= getJCellCount()) {
		return false;
	}
	unsigned int otherColumnIndex = getGlobalIndexColumnFromIjIndex(iOtherColum, jOtherColum);

	// Check split on first pillar of the column edge
	bool result = false;
	unsigned int pillarIndex = getGlobalIndexPillarFromIjIndex(iPillarIndex, jPillarIndex);
	if (!splitInformation[pillarIndex].empty()) {
		unsigned int columnIndex = getGlobalIndexColumnFromIjIndex(iColumn, jColumn);
		for (size_t columnSet = 0; columnSet < splitInformation[pillarIndex].size(); ++columnSet) {
			for (size_t column = 0; column < splitInformation[pillarIndex][columnSet].second.size(); ++column) {
				if (splitInformation[pillarIndex][columnSet].second[column] == columnIndex) {
					result = true;
					for (size_t otherColumn = 0; otherColumn < splitInformation[pillarIndex][columnSet].second.size(); ++otherColumn) {
						if (splitInformation[pillarIndex][columnSet].second[otherColumn] == otherColumnIndex)
							result = false;
					}
					if (result == true) {
						return true;
					}
					else {
						columnSet = splitInformation[pillarIndex].size();
						break;
					}
				}
				else if (splitInformation[pillarIndex][columnSet].second[column] == otherColumnIndex) {
					result = true;
					for (size_t otherColumn = 0; otherColumn < splitInformation[pillarIndex][columnSet].second.size(); ++otherColumn) {
						if (splitInformation[pillarIndex][columnSet].second[otherColumn] == columnIndex)
							result = false;
					}
					if (result == true) {
						return true;
					}
					else {
						columnSet = splitInformation[pillarIndex].size();
						break;
					}
				}
			}
		}
	}

	// Check split on second pillar of the column edge
	iPillarIndex = iColumn;
	if (edge == 0 || edge == 1)
		++iPillarIndex;
	jPillarIndex = jColumn;
	if (edge == 1 || edge == 2)
		++jPillarIndex;

	pillarIndex = getGlobalIndexPillarFromIjIndex(iPillarIndex, jPillarIndex);
	if (!splitInformation[pillarIndex].empty()) {
		unsigned int columnIndex = getGlobalIndexColumnFromIjIndex(iColumn, jColumn);
		for (size_t columnSet = 0; columnSet < splitInformation[pillarIndex].size(); ++columnSet) {
			for (size_t column = 0; column < splitInformation[pillarIndex][columnSet].second.size(); ++column) {
				if (splitInformation[pillarIndex][columnSet].second[column] == columnIndex) {
					for (size_t otherColumn = 0; otherColumn < splitInformation[pillarIndex][columnSet].second.size(); ++otherColumn) {
						if (splitInformation[pillarIndex][columnSet].second[otherColumn] == otherColumnIndex)
							return false;
					}
					return true;
				}
				else if (splitInformation[pillarIndex][columnSet].second[column] == otherColumnIndex) {
					for (size_t otherColumn = 0; otherColumn < splitInformation[pillarIndex][columnSet].second.size(); ++otherColumn) {
						if (splitInformation[pillarIndex][columnSet].second[otherColumn] == columnIndex)
							return false;
					}
					return true;
				}
			}
		}
	}

	return result;
}

ULONG64 AbstractIjkGridRepresentation::getXyzPointIndexFromCellCorner(unsigned int iCell, unsigned int jCell, unsigned int kCell, unsigned int corner) const
{
	if (splitInformation == nullptr) {
		throw invalid_argument("The split information must have been loaded first.");
	}
	if (iCell > getICellCount()) {
		throw out_of_range("I Cell is out of range.");
	}
	if (jCell > getJCellCount()) {
		throw out_of_range("J Cell is out of range.");
	}
	if (kCell > getKCellCount()) {
		throw out_of_range("K Cell is out of range.");
	}
	if (corner > 7) {
		throw out_of_range("Corner is out of range.");
	}

	unsigned int iPillarIndex = iCell;
	if (corner == 1 || corner == 2 || corner == 5 || corner == 6)
		++iPillarIndex;
	unsigned int jPillarIndex = jCell;
	if (corner == 2 || corner == 3 || corner == 6 || corner == 7)
		++jPillarIndex;
	unsigned int kPointIndex = kCell;
	if (corner > 3)
		++kPointIndex;

	const unsigned int pillarIndex = getGlobalIndexPillarFromIjIndex(iPillarIndex, jPillarIndex);
	if (!splitInformation[pillarIndex].empty()) {
		const unsigned int columnIndex = getGlobalIndexColumnFromIjIndex(iCell, jCell);
		for (size_t columnSet = 0; columnSet < splitInformation[pillarIndex].size(); ++columnSet) {
			for (size_t column = 0; column < splitInformation[pillarIndex][columnSet].second.size(); ++column) {
				if (splitInformation[pillarIndex][columnSet].second[column] == columnIndex) {
					return (getICellCount() + 1) * (getJCellCount() + 1) + splitInformation[pillarIndex][columnSet].first + kPointIndex * ((getICellCount() + 1) * (getJCellCount() + 1) + getSplitCoordinateLineCount()); // splitted point
				}
			}
		}
	}

	return iPillarIndex + jPillarIndex * (getICellCount()+1) + kPointIndex * ((getICellCount()+1) * (getJCellCount()+1) + getSplitCoordinateLineCount()); // non splitted point
}

void AbstractIjkGridRepresentation::getXyzPointOfBlockFromCellCorner(unsigned int iCell, unsigned int jCell, unsigned int kCell, unsigned int corner,
	const double* xyzPoints, double & x, double & y, double & z) const
{
	if (splitInformation == nullptr) {
		throw invalid_argument("The split information must have been loaded first.");
	}
	if (blockInformation == nullptr) {
		throw invalid_argument("The block information must have been loaded first.");
	}
	if (iCell > getICellCount()) {
		throw out_of_range("I Cell is out of range.");
	}
	if (jCell > getJCellCount()) {
		throw out_of_range("J Cell is out of range.");
	}
	if (kCell > getKCellCount()) {
		throw out_of_range("K Cell is out of range.");
	}
	if (corner > 7) {
		throw out_of_range("Corner is out of the block.");
	}

	unsigned int iPillarIndex = iCell;
	if (corner == 1 || corner == 2 || corner == 5 || corner == 6) {
		++iPillarIndex;
	}
	unsigned int jPillarIndex = jCell;
	if (corner == 2 || corner == 3 || corner == 6 || corner == 7) {
		++jPillarIndex;
	}
	unsigned int kPointIndex = kCell;
	if (corner > 3) {
		++kPointIndex;
	}
	kPointIndex -= blockInformation->kInterfaceStart;

	ULONG64 pointIndex;

	const unsigned int pillarIndex = getGlobalIndexPillarFromIjIndex(iPillarIndex, jPillarIndex);
	if (!splitInformation[pillarIndex].empty()) {
		const unsigned int columnIndex = getGlobalIndexColumnFromIjIndex(iCell, jCell);
		for (size_t columnSet = 0; columnSet < splitInformation[pillarIndex].size(); ++columnSet) {
			for (size_t column = 0; column < splitInformation[pillarIndex][columnSet].second.size(); ++column) {
				if (splitInformation[pillarIndex][columnSet].second[column] == columnIndex) {
					pointIndex = (blockInformation->globalToLocalSplitCoordinateLinesIndex)[splitInformation[pillarIndex][columnSet].first] + kPointIndex * ((blockInformation->iInterfaceEnd - blockInformation->iInterfaceStart + 1) * (blockInformation->jInterfaceEnd - blockInformation->jInterfaceStart + 1) + getBlockSplitCoordinateLineCount()); // splitted point
					x = xyzPoints[3 * pointIndex];
					y = xyzPoints[3 * pointIndex + 1];
					z = xyzPoints[3 * pointIndex + 2];
					return;
				}
			}
		}
	}

	iPillarIndex -= blockInformation->iInterfaceStart;
	jPillarIndex -= blockInformation->jInterfaceStart;

	pointIndex = iPillarIndex + jPillarIndex * (blockInformation->iInterfaceEnd - blockInformation->iInterfaceStart + 1) + kPointIndex * ((blockInformation->iInterfaceEnd - blockInformation->iInterfaceStart + 1) * (blockInformation->jInterfaceEnd - blockInformation->jInterfaceStart + 1) + getBlockSplitCoordinateLineCount()); // non splitted point
	x = xyzPoints[3 * pointIndex];
	y = xyzPoints[3 * pointIndex + 1];
	z = xyzPoints[3 * pointIndex + 2];
}

ULONG64 AbstractIjkGridRepresentation::getXyzPointCountOfKInterface() const
{
	return getPillarCount() + getSplitCoordinateLineCount();
}

ULONG64 AbstractIjkGridRepresentation::getXyzPointCountOfBlock() const
{
	if (blockInformation == nullptr) {
		throw invalid_argument("The block information must have been loaded first.");
	}

	return (blockInformation->iInterfaceEnd - blockInformation->iInterfaceStart + 1) * (blockInformation->jInterfaceEnd - blockInformation->jInterfaceStart + 1) * (blockInformation->kInterfaceEnd - blockInformation->kInterfaceStart + 1) + (blockInformation->kInterfaceEnd - blockInformation->kInterfaceStart + 1) * getBlockSplitCoordinateLineCount();
}

void AbstractIjkGridRepresentation::getXyzPointsOfKInterface(unsigned int kInterface, double * xyzPoints)
{
	getXyzPointsOfKInterfaceSequence(kInterface, kInterface, xyzPoints);
}

void AbstractIjkGridRepresentation::setEnabledCells(unsigned char* enabledCells, EML2_NS::AbstractHdfProxy* proxy)
{
	if (proxy == nullptr) {
		proxy = getRepository()->getDefaultHdfProxy();
		if (proxy == nullptr) {
			throw std::invalid_argument("A (default) HDF Proxy must be provided.");
		}
	}

	if (gsoapProxy2_0_1 != nullptr) {
		gsoap_resqml2_0_1::resqml20__IjkGridGeometry* geom = static_cast<gsoap_resqml2_0_1::resqml20__IjkGridGeometry*>(getPointGeometry2_0_1(0));
		if (geom == nullptr) {
			throw invalid_argument("There is no geometry on this IJK grid.");
		}

		resqml20__BooleanHdf5Array* boolArray = soap_new_resqml20__BooleanHdf5Array(gsoapProxy2_0_1->soap);
		boolArray->Values = soap_new_eml20__Hdf5Dataset(gsoapProxy2_0_1->soap);
		boolArray->Values->HdfProxy = proxy->newResqmlReference();
		boolArray->Values->PathInHdfFile = getHdfGroup() + "/CellGeometryIsDefined";
		geom->CellGeometryIsDefined = boolArray;
	}
	else {
		gsoap_eml2_3::resqml22__IjkGridGeometry* geom = static_cast<gsoap_eml2_3::resqml22__IjkGridGeometry*>(getPointGeometry2_2(0));
		if (geom == nullptr) {
			throw invalid_argument("There is no geometry on this IJK grid.");
		}

		gsoap_eml2_3::eml23__BooleanExternalArray* boolArray = gsoap_eml2_3::soap_new_eml23__BooleanExternalArray(gsoapProxy2_3->soap);
		boolArray->Values = gsoap_eml2_3::soap_new_eml23__ExternalDataset(boolArray->soap);
		gsoap_eml2_3::eml23__ExternalDatasetPart* dsPart = gsoap_eml2_3::soap_new_eml23__ExternalDatasetPart(boolArray->soap);
		dsPart->EpcExternalPartReference = proxy->newEml23Reference();
		dsPart->PathInExternalFile = getHdfGroup() + "/CellGeometryIsDefined";
		dsPart->StartIndex = 0;
		dsPart->Count = getCellCount();
		boolArray->Values->ExternalFileProxy.push_back(dsPart);
		geom->CellGeometryIsDefined = boolArray;
	}

	// HDF
	hsize_t cellGeometryIsDefinedCount[3] = { getKCellCount(), getJCellCount(), getICellCount() };
	proxy->writeArrayNd(getHdfGroup(), "CellGeometryIsDefined", H5T_NATIVE_UCHAR, enabledCells, cellGeometryIsDefinedCount, 3);
}

gsoap_resqml2_0_1::resqml20__KDirection AbstractIjkGridRepresentation::getKDirection() const
{
	if (gsoapProxy2_0_1 != nullptr) {
		gsoap_resqml2_0_1::resqml20__IjkGridGeometry* geom = static_cast<gsoap_resqml2_0_1::resqml20__IjkGridGeometry*>(getPointGeometry2_0_1(0));
		if (geom == nullptr) {
			throw invalid_argument("There is no geometry on this IJK grid.");
		}
		return geom->KDirection;
	}
	else {
		gsoap_eml2_3::resqml22__IjkGridGeometry* geom = static_cast<gsoap_eml2_3::resqml22__IjkGridGeometry*>(getPointGeometry2_2(0));
		if (geom == nullptr) {
			throw invalid_argument("There is no geometry on this IJK grid.");
		}
		return static_cast<gsoap_resqml2_0_1::resqml20__KDirection>(geom->KDirection);
	}
}

void AbstractIjkGridRepresentation::getXyzPointsOfKInterfaceSequence(unsigned int, unsigned int, double *)
{
	throw std::logic_error("Partial object");
}

void AbstractIjkGridRepresentation::getXyzPointsOfBlock(double *)
{
	throw std::logic_error("Partial object");
}

ULONG64 AbstractIjkGridRepresentation::getXyzPointCountOfPatch(unsigned int) const
{
	throw std::logic_error("Partial object");
}

void AbstractIjkGridRepresentation::getXyzPointsOfPatch(unsigned int, double *) const
{
	throw std::logic_error("Partial object");
}
