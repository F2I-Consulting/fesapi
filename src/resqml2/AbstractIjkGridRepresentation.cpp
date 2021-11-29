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

#if WITH_RESQML2_2
#include "../resqml2_2/EarthModelInterpretation.h"
#endif

#include "AbstractFeatureInterpretation.h"

using namespace std;
using namespace gsoap_resqml2_0_1;
using namespace RESQML2_NS;

const char* AbstractIjkGridRepresentation::XML_TAG = "IjkGridRepresentation";
const char* AbstractIjkGridRepresentation::XML_TAG_TRUNCATED = "TruncatedIjkGridRepresentation";

AbstractIjkGridRepresentation::AbstractIjkGridRepresentation(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject, bool withTruncatedPillars) :
	AbstractColumnLayerGridRepresentation(partialObject, withTruncatedPillars), splitInformation(nullptr), kCellIndexWithGapLayer(nullptr), blockInformation(nullptr)
{
}

std::string AbstractIjkGridRepresentation::getXmlTag() const
{
	return !isTruncated() ? XML_TAG : XML_TAG_TRUNCATED;
}

void AbstractIjkGridRepresentation::init(COMMON_NS::DataObjectRepository * repo,
	const std::string & guid, const std::string & title,
	unsigned int iCount, unsigned int jCount, unsigned int kCount, bool* kGaps, EML2_NS::AbstractHdfProxy* proxy)
{
	if (repo == nullptr) {
		throw invalid_argument("The repo cannot be null.");
	}

	hsize_t kGapCount = 0;
	if (kGaps != nullptr) {
		for (size_t k = 0; k < kCount - 1; ++k) {
			if (kGaps[k]) {
				++kGapCount;
			}
		}
	}

	if (!withTruncatedPillars) {
		switch (repo->getDefaultResqmlVersion()) {
		case COMMON_NS::DataObjectRepository::EnergisticsStandard::RESQML2_0_1: {
			gsoapProxy2_0_1 = gsoap_resqml2_0_1::soap_new_resqml20__obj_USCOREIjkGridRepresentation(repo->getGsoapContext());
			gsoap_resqml2_0_1::_resqml20__IjkGridRepresentation* ijkGrid = static_cast<gsoap_resqml2_0_1::_resqml20__IjkGridRepresentation*>(gsoapProxy2_0_1);
			ijkGrid->Ni = iCount;
			ijkGrid->Nj = jCount;
			ijkGrid->Nk = kCount;

			if (kGapCount > 0) {
				if (proxy == nullptr) {
					proxy = repo->getDefaultHdfProxy();
					if (proxy == nullptr) {
						throw std::invalid_argument("A (default) HDF Proxy must be provided.");
					}
				}

				auto xmlKGaps = gsoap_resqml2_0_1::soap_new_resqml20__KGaps(getGsoapContext());
				xmlKGaps->__KGaps_sequence = gsoap_resqml2_0_1::soap_new___resqml20__KGaps_sequence(getGsoapContext());
				xmlKGaps->__KGaps_sequence->Count = kGapCount;
				
				resqml20__BooleanHdf5Array* boolArray = soap_new_resqml20__BooleanHdf5Array(getGsoapContext());
				boolArray->Values = soap_new_eml20__Hdf5Dataset(getGsoapContext());
				boolArray->Values->HdfProxy = proxy->newResqmlReference();
				boolArray->Values->PathInHdfFile = "/" + getXmlNamespace() + "/" + guid + "/GapAfterLayer";
				xmlKGaps->__KGaps_sequence->GapAfterLayer = boolArray;

				ijkGrid->KGaps = xmlKGaps;
			}

			break;
		}
		case COMMON_NS::DataObjectRepository::EnergisticsStandard::RESQML2_2: {
			gsoapProxy2_3 = gsoap_eml2_3::soap_new_resqml22__IjkGridRepresentation(repo->getGsoapContext());
			gsoap_eml2_3::_resqml22__IjkGridRepresentation* ijkGrid = static_cast<gsoap_eml2_3::_resqml22__IjkGridRepresentation*>(gsoapProxy2_3);
			ijkGrid->Ni = iCount;
			ijkGrid->Nj = jCount;
			ijkGrid->Nk = kCount;

			if (kGapCount > 0) {
				if (proxy == nullptr) {
					proxy = repo->getDefaultHdfProxy();
					if (proxy == nullptr) {
						throw std::invalid_argument("A (default) HDF Proxy must be provided.");
					}
				}

				auto xmlKGaps = gsoap_eml2_3::soap_new_resqml22__KGaps(getGsoapContext());
				xmlKGaps->Count = kGapCount;

				gsoap_eml2_3::eml23__BooleanExternalArray* boolArray = gsoap_eml2_3::soap_new_eml23__BooleanExternalArray(getGsoapContext());
				boolArray->Values = gsoap_eml2_3::soap_new_eml23__ExternalDataArray(getGsoapContext());
				boolArray->Values->ExternalDataArrayPart.push_back(createExternalDataArrayPart("/" + getXmlNamespace() + "/" + guid + "/GapAfterLayer", getCellCount(), proxy));
				xmlKGaps->GapAfterLayer = boolArray;

				ijkGrid->KGaps = xmlKGaps;
			}

			break;
		}
		default:
			throw std::invalid_argument("Unrecognized Energistics standard.");
		}

		if (kGapCount > 0) {
			// Need to copy the array since HDF5 do not support bool array and since sizeof bool is implementation dependent.
			std::unique_ptr<unsigned char[]> tmp(new unsigned char[kCount - 1]);
			for (size_t k = 0; k < kCount - 1; ++k) {
				tmp[k] = kGaps[k] ? 1 : 0;
			}
			proxy->writeArrayNd("/" + getXmlNamespace() + "/" + guid, "GapAfterLayer", H5T_NATIVE_UCHAR, tmp.get(), &kGapCount, 1);
		}
	}
	else {
		if (kGaps != nullptr) {
			throw std::invalid_argument("Truncated IJK grid representation cannot have K Gaps.");
		}

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

	repo->addDataObject(this);
}

AbstractIjkGridRepresentation::AbstractIjkGridRepresentation(COMMON_NS::DataObjectRepository * repo,
	const std::string & guid, const std::string & title,
	unsigned int iCount, unsigned int jCount, unsigned int kCount, bool* kGaps, EML2_NS::AbstractHdfProxy* proxy) :
	RESQML2_NS::AbstractColumnLayerGridRepresentation(false), splitInformation(nullptr), kCellIndexWithGapLayer(nullptr), blockInformation(nullptr)
{
	init(repo, guid, title, iCount, jCount, kCount, kGaps, proxy);

#if WITH_RESQML2_2
	if (gsoapProxy2_3 != nullptr) {
		setInterpretation(repo->createPartial<RESQML2_2_NS::EarthModelInterpretation>("", "Unknown interp"));
	}
#endif
}

AbstractIjkGridRepresentation::AbstractIjkGridRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp,
	const std::string & guid, const std::string & title,
	unsigned int iCount, unsigned int jCount, unsigned int kCount, bool* kGaps, EML2_NS::AbstractHdfProxy* proxy) :
	RESQML2_NS::AbstractColumnLayerGridRepresentation(false), splitInformation(nullptr), kCellIndexWithGapLayer(nullptr), blockInformation(nullptr)
{
	if (interp == nullptr) {
		throw invalid_argument("The interpretation of the IJK grid cannot be null.");
	}

	init(interp->getRepository(), guid, title, iCount, jCount, kCount, kGaps, proxy);

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
	const uint64_t iCellCount = gsoapProxy2_0_1 != nullptr
		? (isTruncated() ? getSpecializedTruncatedGsoapProxy2_0_1()->Ni : getSpecializedGsoapProxy2_0_1()->Ni)
		: (isTruncated() ? getSpecializedTruncatedGsoapProxy2_2()->Ni : getSpecializedGsoapProxy2_2()->Ni);

	if (iCellCount > (std::numeric_limits<unsigned int>::max)()) {
		throw std::range_error("There are too much cells against I dimension.");
	}

	return static_cast<unsigned int>(iCellCount);
}

void AbstractIjkGridRepresentation::setICellCount(unsigned int iCount)
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
	const uint64_t jCellCount = gsoapProxy2_0_1 != nullptr
		? (isTruncated() ? getSpecializedTruncatedGsoapProxy2_0_1()->Nj : getSpecializedGsoapProxy2_0_1()->Nj)
		: (isTruncated() ? getSpecializedTruncatedGsoapProxy2_2()->Nj : getSpecializedGsoapProxy2_2()->Nj);

	if (jCellCount > (std::numeric_limits<unsigned int>::max)()) {
		throw std::range_error("There are too much cells against J dimension.");
	}

	return static_cast<unsigned int>(jCellCount);
}

void AbstractIjkGridRepresentation::setJCellCount(unsigned int jCount)
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
			gsoap_eml2_3::eml23__ExternalDataArray const * dataset = static_cast<gsoap_eml2_3::eml23__IntegerExternalArray*>(geom->ColumnLayerSplitCoordinateLines->PillarIndices)->Values;
			EML2_NS::AbstractHdfProxy * hdfProxy = getOrCreateHdfProxyFromDataArrayPart(dataset->ExternalDataArrayPart[0]);
			hdfProxy->readArrayNdOfUIntValues(dataset->ExternalDataArrayPart[0]->PathInExternalFile, pillarIndices);
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
			gsoap_eml2_3::eml23__ExternalDataArray const * dataset = static_cast<gsoap_eml2_3::eml23__IntegerExternalArray*>(geom->ColumnLayerSplitCoordinateLines->ColumnsPerSplitCoordinateLine->Elements)->Values;
			EML2_NS::AbstractHdfProxy * hdfProxy = getOrCreateHdfProxyFromDataArrayPart(dataset->ExternalDataArrayPart[0]);
			hdfProxy->readArrayNdOfUIntValues(dataset->ExternalDataArrayPart[0]->PathInExternalFile, columnIndices);
			if (reverseIAxis || reverseJAxis) {
				datasetValueCount = hdfProxy->getElementCount(dataset->ExternalDataArrayPart[0]->PathInExternalFile);
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
			gsoap_eml2_3::eml23__ExternalDataArray const * dataset = static_cast<gsoap_eml2_3::eml23__IntegerExternalArray*>(geom->ColumnLayerSplitCoordinateLines->ColumnsPerSplitCoordinateLine->CumulativeLength)->Values;
			EML2_NS::AbstractHdfProxy * hdfProxy = getOrCreateHdfProxyFromDataArrayPart(dataset->ExternalDataArrayPart[0]);
			hdfProxy->readArrayNdOfUIntValues(dataset->ExternalDataArrayPart[0]->PathInExternalFile, columnIndexCountPerSplitCoordinateLine);
		}
		else {
			throw std::logic_error("Not implemented yet");
		}
	}
}

unsigned long AbstractIjkGridRepresentation::getSplitCoordinateLineCount() const
{
	uint64_t splitCoordinateLineCount = 0;
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
	if (splitInformation == nullptr)
		throw invalid_argument("The split information must have been loaded first.");
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


uint64_t AbstractIjkGridRepresentation::getSplitNodeCount() const
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
			gsoap_eml2_3::eml23__ExternalDataArray const * dataset = static_cast<gsoap_eml2_3::eml23__BooleanExternalArray*>(geom->PillarGeometryIsDefined)->Values;
			EML2_NS::AbstractHdfProxy * hdfProxy = getOrCreateHdfProxyFromDataArrayPart(dataset->ExternalDataArrayPart[0]);
			std::unique_ptr<char[]> tmp(new char[pillarCount]);
			hdfProxy->readArrayNdOfCharValues(dataset->ExternalDataArrayPart[0]->PathInExternalFile, tmp.get());
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

	const uint64_t cellCount = getCellCount();
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
			for (uint64_t i = 0; i < cellCount; ++i) {
				enabledCells[i] = tmp[i] != 0;
			}
		}
		else if (geom->CellGeometryIsDefined->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__BooleanConstantArray) {
			const bool enabled = static_cast<resqml20__BooleanConstantArray*>(geom->CellGeometryIsDefined)->Value;
			for (uint64_t i = 0; i < cellCount; ++i) {
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
			gsoap_eml2_3::eml23__ExternalDataArray const * dataset = static_cast<gsoap_eml2_3::eml23__BooleanExternalArray*>(geom->CellGeometryIsDefined)->Values;
			EML2_NS::AbstractHdfProxy * hdfProxy = getOrCreateHdfProxyFromDataArrayPart(dataset->ExternalDataArrayPart[0]);
			std::unique_ptr<char[]> tmp(new char[cellCount]);
			hdfProxy->readArrayNdOfCharValues(dataset->ExternalDataArrayPart[0]->PathInExternalFile, tmp.get());
			for (unsigned int i = 0; i < cellCount; ++i) {
				enabledCells[i] = tmp[i] != 0;
			}
		}
		else if (geom->CellGeometryIsDefined->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__BooleanConstantArray) {
			const bool enabled = static_cast<gsoap_eml2_3::eml23__BooleanConstantArray*>(geom->CellGeometryIsDefined)->Value;
			for (uint64_t i = 0; i < cellCount; ++i) {
				enabledCells[i] = enabled;
			}
		}
		else {
			throw std::logic_error("Not implemented yet");
		}
	}

	// Copy in order not to modify the controlPoints pointer
	if (reverseIAxis || reverseJAxis || reverseKAxis) {
		const uint64_t arrayCount = getCellCount();
		std::unique_ptr<bool[]> initialCellGeometryIsDefined(new bool[arrayCount]);
		for (uint64_t index = 0; index < arrayCount; ++index) {
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

	auto kCount = getKCellCount();
	kCellIndexWithGapLayer = new unsigned int[kCount];
	for (unsigned int k = 0; k < kCount; ++k) {
		kCellIndexWithGapLayer[k] = k;
	}
	const auto kGapCount = getKGapsCount();
	if (kGapCount > 0) {
		std::unique_ptr<bool[]> gapAfterLayer(new bool[kCount - 1]);
		getKGaps(gapAfterLayer.get());
		unsigned int offset = 0;
		for (unsigned int k = 0; k < kCount - 1; ++k) {
			kCellIndexWithGapLayer[k] += offset;
			if (gapAfterLayer[k]) {
				++offset;
			}
		}
		kCellIndexWithGapLayer[kCount - 1] += offset;
	}
}

void AbstractIjkGridRepresentation::loadBlockInformation(unsigned int iInterfaceStart, unsigned int iInterfaceEnd, unsigned int jInterfaceStart, unsigned int jInterfaceEnd, unsigned int kInterfaceStart, unsigned int kInterfaceEnd)
{
	if (splitInformation == nullptr || kCellIndexWithGapLayer == nullptr) {
		throw invalid_argument("The split information must have been loaded first.");
	}
	if (iInterfaceEnd > getICellCount()) {
		throw out_of_range("iInterfaceEnd is out of boundaries.");
	}
	if (iInterfaceStart > iInterfaceEnd) {
		throw range_error("iInterfaceStart > iInterfaceEnd");
	}

	if (jInterfaceEnd > getJCellCount()) {
		throw out_of_range("jInterfaceEnd is out of boundaries.");
	}
	if (jInterfaceStart > jInterfaceEnd) {
		throw range_error("jInterfaceStart > jInterfaceEnd");
	}

	if (kInterfaceEnd > getKCellCount() + getKGapsCount()) {
		throw out_of_range("kInterfaceEnd is out of boundaries.");
	}
	if (kInterfaceStart > kInterfaceEnd) {
		throw range_error("kInterfaceStart > kInterfaceEnd");
	}

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

	// setting mapping between global and local (to the block) split coordinate lines index
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
							// here is a split coordinate line impacting the block
							(blockInformation->globalToLocalSplitCoordinateLinesIndex)[splitInformation[pillarIndex][splitCoordinateLineIndex].first] = -1;

							break; // in order to be sure not adding twice a same coordinate line if it is adjacent to several columns within the block
						}
					}
				}
			}
		}
	}

	// we take advantage of the std::map order (by key) to set the split coordinate lines local indexes
	unsigned int splitCoordinateLineHdfLocalIndex = (iInterfaceEnd - iInterfaceStart + 1) * (jInterfaceEnd - jInterfaceStart + 1);
	for (std::map<unsigned int, unsigned int>::iterator it = blockInformation->globalToLocalSplitCoordinateLinesIndex.begin(); it != blockInformation->globalToLocalSplitCoordinateLinesIndex.end(); it++)
	{
		it->second = splitCoordinateLineHdfLocalIndex++;
	}
}

void AbstractIjkGridRepresentation::unloadSplitInformation()
{
	if (splitInformation != nullptr) {
		delete [] splitInformation;
		splitInformation = nullptr;
	}
	if (kCellIndexWithGapLayer != nullptr) {
		delete [] kCellIndexWithGapLayer;
		kCellIndexWithGapLayer = nullptr;
	}
}

uint64_t AbstractIjkGridRepresentation::getKGapsCount() const
{
	if (isTruncated()) {
		return 0;
	}

	if (gsoapProxy2_0_1 != nullptr) {
		auto ijkGrid = getSpecializedGsoapProxy2_0_1();
		return ijkGrid->KGaps != nullptr && ijkGrid->KGaps->__KGaps_sequence != nullptr
			? ijkGrid->KGaps->__KGaps_sequence->Count
			: 0;
	}
	else if (gsoapProxy2_3 != nullptr) {
		auto ijkGrid = getSpecializedGsoapProxy2_2();
		return ijkGrid->KGaps != nullptr && ijkGrid->KGaps != nullptr
			? ijkGrid->KGaps->Count
			: 0;
	}

	throw logic_error("The IJK grid is a partial one.");
}

void AbstractIjkGridRepresentation::getKGaps(bool * kGaps) const
{
	if (getKGapsCount() <= 0) {
		throw invalid_argument("The grid has no K Gap.");
	}

	if (gsoapProxy2_0_1 != nullptr) {
		auto ijkGrid = getSpecializedGsoapProxy2_0_1();
		if (ijkGrid->KGaps->__KGaps_sequence->GapAfterLayer->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__BooleanHdf5Array) {
			eml20__Hdf5Dataset const * dataset = static_cast<resqml20__BooleanHdf5Array*>(ijkGrid->KGaps->__KGaps_sequence->GapAfterLayer)->Values;
			EML2_NS::AbstractHdfProxy * hdfProxy = getHdfProxyFromDataset(dataset);
			std::unique_ptr<char[]> tmp(new char[getKCellCount() - 1]);
			hdfProxy->readArrayNdOfCharValues(dataset->PathInHdfFile, tmp.get());
			for (uint64_t k = 0; k < getKCellCount() - 1; ++k) {
				kGaps[k] = tmp[k] != 0;
			}
		}
		else if (ijkGrid->KGaps->__KGaps_sequence->GapAfterLayer->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__BooleanConstantArray) {
			const bool hasGap = static_cast<resqml20__BooleanConstantArray*>(ijkGrid->KGaps->__KGaps_sequence->GapAfterLayer)->Value;
			for (uint64_t k = 0; k < getKCellCount() - 1; ++k) {
				kGaps[k] = hasGap;
			}
		}
		else {
			throw std::logic_error("Not implemented yet");
		}
	}
	else if (gsoapProxy2_3 != nullptr) {
		auto ijkGrid = getSpecializedGsoapProxy2_2();
		if (ijkGrid->KGaps->GapAfterLayer->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__BooleanExternalArray) {
			gsoap_eml2_3::eml23__ExternalDataArray const * dataset = static_cast<gsoap_eml2_3::eml23__BooleanExternalArray*>(ijkGrid->KGaps->GapAfterLayer)->Values;
			EML2_NS::AbstractHdfProxy * hdfProxy = getOrCreateHdfProxyFromDataArrayPart(dataset->ExternalDataArrayPart[0]);
			std::unique_ptr<char[]> tmp(new char[getKCellCount() - 1]);
			hdfProxy->readArrayNdOfCharValues(dataset->ExternalDataArrayPart[0]->PathInExternalFile, tmp.get());
			for (uint64_t k = 0; k < getKCellCount() - 1; ++k) {
				kGaps[k] = tmp[k] != 0;
			}
		}
		else if (ijkGrid->KGaps->GapAfterLayer->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__BooleanConstantArray) {
			const bool hasGap = static_cast<gsoap_eml2_3::eml23__BooleanConstantArray*>(ijkGrid->KGaps->GapAfterLayer)->Value;
			for (uint64_t k = 0; k < getKCellCount() - 1; ++k) {
				kGaps[k] = hasGap;
			}
		}
		else {
			throw std::logic_error("Not implemented yet");
		}
	}
	else {
		throw logic_error("The IJK grid is a partial one.");
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

uint64_t AbstractIjkGridRepresentation::getXyzPointIndexFromCellCorner(unsigned int iCell, unsigned int jCell, unsigned int kCell, unsigned int corner) const
{
	if (splitInformation == nullptr || kCellIndexWithGapLayer == nullptr) {
		throw invalid_argument("The split information must have been loaded first.");
	}
	if (kCell > getKCellCount()) {
		throw out_of_range("K Cell is out of range.");
	}
	if (corner > 7) {
		throw out_of_range("Corner is out of range.");
	}

	const unsigned int iPillarIndex = corner == 1 || corner == 2 || corner == 5 || corner == 6
		? iCell + 1
		: iCell;
	const unsigned int jPillarIndex = corner == 2 || corner == 3 || corner == 6 || corner == 7
		? jCell + 1
		: jCell;
	const unsigned int kPointIndex = corner > 3
		? kCellIndexWithGapLayer[kCell] + 1
		: kCellIndexWithGapLayer[kCell];

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

	unsigned int iPillarIndex = corner == 1 || corner == 2 || corner == 5 || corner == 6
		? iCell + 1
		: iCell;
	unsigned int jPillarIndex = corner == 2 || corner == 3 || corner == 6 || corner == 7
		? jCell + 1
		: jCell;
	unsigned int kPointIndex = corner > 3
		? kCellIndexWithGapLayer[kCell] + 1
		: kCellIndexWithGapLayer[kCell];
	kPointIndex -= blockInformation->kInterfaceStart;

	uint64_t pointIndex;

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

uint64_t AbstractIjkGridRepresentation::getXyzPointCountOfKInterface() const
{
	return getPillarCount() + getSplitCoordinateLineCount();
}

uint64_t AbstractIjkGridRepresentation::getXyzPointCountOfBlock() const
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
		boolArray->Values = gsoap_eml2_3::soap_new_eml23__ExternalDataArray(boolArray->soap);
		boolArray->Values->ExternalDataArrayPart.push_back(createExternalDataArrayPart(getHdfGroup() +"/CellGeometryIsDefined", getCellCount(), proxy));
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

uint64_t AbstractIjkGridRepresentation::getXyzPointCountOfPatch(unsigned int) const
{
	const uint64_t result = getXyzPointCountOfKInterface() * (getKCellCount() + 1 + getKGapsCount()) + getSplitNodeCount();

	if (gsoapProxy2_0_1 != nullptr) {
		return isTruncated()
			? result + static_cast<gsoap_resqml2_0_1::_resqml20__TruncatedIjkGridRepresentation*>(gsoapProxy2_0_1)->TruncationCells->TruncationNodeCount
			: result;
	}
	else if (gsoapProxy2_3 != nullptr) {
		return isTruncated()
			? result + static_cast<gsoap_eml2_3::_resqml22__TruncatedIjkGridRepresentation*>(gsoapProxy2_3)->TruncationCellPatch->TruncationNodeCount
			: result;
	}

	throw std::logic_error("The IJK Grid is in an unknown Energistics standard version.");
}

void AbstractIjkGridRepresentation::getXyzPointsOfPatch(unsigned int, double *) const
{
	throw std::logic_error("Partial object");
}
