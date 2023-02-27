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
#include "IjkGridExplicitRepresentation.h"

#include <hdf5.h>

#include "../eml2/AbstractHdfProxy.h"

using namespace std;
using namespace gsoap_resqml2_0_1;
using namespace RESQML2_NS;

void IjkGridExplicitRepresentation::getXyzPointsOfKInterfaceSequence(unsigned int kInterfaceStart, unsigned int kInterfaceEnd, double * xyzPoints)
{
	if (kInterfaceStart > getKCellCount() + getKGapsCount() || kInterfaceEnd > getKCellCount() + getKGapsCount()) {
		throw out_of_range("kInterfaceStart and/or kInterfaceEnd is/are out of boundaries.");
	}
	if (kInterfaceStart > kInterfaceEnd) {
		throw range_error("kInterfaceStart > kInterfaceEnd");
	}

	if (xyzPoints == nullptr) {
		throw invalid_argument("xyzPoints must be allocated.");
	}

	// Truncation
	if (isTruncated()) {
		throw invalid_argument("Getting all the XYZ points of a particular K interface is not supported yet for truncated grids.");
	}

	std::string datasetPathInExternalFile;
	uint64_t splitCoordinateLineCount;
	EML2_NS::AbstractHdfProxy* hdfProxy = getPointDatasetPath(datasetPathInExternalFile, splitCoordinateLineCount);

	if (splitCoordinateLineCount == 0)
	{
		std::unique_ptr<uint64_t[]> valueCountPerDimension(new uint64_t[4]);
		valueCountPerDimension[0] = kInterfaceEnd - kInterfaceStart + 1;
		valueCountPerDimension[1] = getJCellCount() + 1;
		valueCountPerDimension[2] = getICellCount() + 1;
		valueCountPerDimension[3] = 3;
		std::unique_ptr<uint64_t[]> offsetPerDimension(new uint64_t[4]);
		offsetPerDimension[0] = kInterfaceStart;
		offsetPerDimension[1] = 0;
		offsetPerDimension[2] = 0;
		offsetPerDimension[3] = 0;

		hdfProxy->readArrayNdOfDoubleValues(
			datasetPathInExternalFile,
			xyzPoints,
			valueCountPerDimension.get(),
			offsetPerDimension.get(),
			4);
	}
	else {
		const auto dimCount = hdfProxy->getDimensionCount(datasetPathInExternalFile);
		if (dimCount == 3) {
			std::unique_ptr<uint64_t[]> valueCountPerDimension(new uint64_t[3]);
			valueCountPerDimension[0] = kInterfaceEnd - kInterfaceStart + 1;
			valueCountPerDimension[1] = getPillarCount() + splitCoordinateLineCount;
			valueCountPerDimension[2] = 3;
			std::unique_ptr<uint64_t[]> offsetPerDimension(new uint64_t[3]);
			offsetPerDimension[0] = kInterfaceStart;
			offsetPerDimension[1] = 0;
			offsetPerDimension[2] = 0;

			hdfProxy->readArrayNdOfDoubleValues(
				datasetPathInExternalFile,
				xyzPoints,
				valueCountPerDimension.get(),
				offsetPerDimension.get(),
				3);
		}
		else if (dimCount == 2) {
			std::unique_ptr<uint64_t[]> valueCountPerDimension(new uint64_t[2]);
			valueCountPerDimension[0] = (kInterfaceEnd - kInterfaceStart + 1) * (getPillarCount() + splitCoordinateLineCount);
			valueCountPerDimension[1] = 3;
			std::unique_ptr<uint64_t[]> offsetPerDimension(new uint64_t[2]);
			offsetPerDimension[0] = kInterfaceStart * (getPillarCount() + splitCoordinateLineCount);
			offsetPerDimension[1] = 0;

			hdfProxy->readArrayNdOfDoubleValues(
				datasetPathInExternalFile,
				xyzPoints,
				valueCountPerDimension.get(),
				offsetPerDimension.get(),
				2);
		}
	}
}

void IjkGridExplicitRepresentation::getXyzPointsOfBlock(double * xyzPoints)
{
	if (!blockInformation) {
		throw logic_error("The block information must have been loaded first.");
	}

	if (xyzPoints == nullptr) {
		throw invalid_argument("xyzPoints must be allocated.");
	}

	// Truncation
	if (isTruncated()) {
		throw invalid_argument("Getting all the XYZ points of a particular K interface is not supported yet for truncated grids.");
	}

	std::string datasetPathInExternalFile;
	uint64_t splitCoordinateLineCount;
	EML2_NS::AbstractHdfProxy* hdfProxy = getPointDatasetPath(datasetPathInExternalFile, splitCoordinateLineCount);

	if (splitCoordinateLineCount == 0)
	{
		std::unique_ptr<uint64_t[]> valueCountPerDimension(new uint64_t[4]);
		valueCountPerDimension[0] = blockInformation->kInterfaceEnd - blockInformation->kInterfaceStart + 1;
		valueCountPerDimension[1] = blockInformation->jInterfaceEnd - blockInformation->jInterfaceStart + 1;
		valueCountPerDimension[2] = blockInformation->iInterfaceEnd - blockInformation->iInterfaceStart + 1;
		valueCountPerDimension[3] = 3;
		std::unique_ptr<uint64_t[]> offsetPerDimension(new uint64_t[4]);
		offsetPerDimension[0] = blockInformation->kInterfaceStart;
		offsetPerDimension[1] = blockInformation->jInterfaceStart;
		offsetPerDimension[2] = blockInformation->iInterfaceStart;
		offsetPerDimension[3] = 0;

		hdfProxy->readArrayNdOfDoubleValues(
			datasetPathInExternalFile,
			xyzPoints,
			valueCountPerDimension.get(),
			offsetPerDimension.get(),
			4);
	}
	else {
		std::unique_ptr<uint64_t[]> blockCountPerDimension(new uint64_t[3]);
		blockCountPerDimension[0] = 1;
		blockCountPerDimension[1] = blockInformation->jInterfaceEnd - blockInformation->jInterfaceStart + 1;
		blockCountPerDimension[2] = 1;
		std::unique_ptr<uint64_t[]> offsetPerDimension(new uint64_t[3]);
		offsetPerDimension[0] = blockInformation->kInterfaceStart;
		offsetPerDimension[1] = blockInformation->jInterfaceStart * (getICellCount() + 1) + blockInformation->iInterfaceStart;
		offsetPerDimension[2] = 0;
		std::unique_ptr<uint64_t[]> strideInEachDimension(new uint64_t[3]);
		strideInEachDimension[0] = 1;
		strideInEachDimension[1] = (blockInformation->iInterfaceEnd - blockInformation->iInterfaceStart + 1) + ((getICellCount() + 1) - (blockInformation->iInterfaceEnd - blockInformation->iInterfaceStart + 1));
		strideInEachDimension[2] = 1;
		std::unique_ptr<uint64_t[]> blockSizeInEachDimension(new uint64_t[3]);
		blockSizeInEachDimension[0] = blockInformation->kInterfaceEnd - blockInformation->kInterfaceStart + 1;
		blockSizeInEachDimension[1] = blockInformation->iInterfaceEnd - blockInformation->iInterfaceStart + 1;
		blockSizeInEachDimension[2] = 3;
		
		hdf5_hid_t dataset, filespace;
		hdfProxy->selectArrayNdOfValues(
			datasetPathInExternalFile,
			blockCountPerDimension.get(),
			offsetPerDimension.get(),
			strideInEachDimension.get(),
			blockSizeInEachDimension.get(),
			3,
			true,
			dataset,
			filespace);

		uint64_t slab_size = 1;
		for (size_t h = 0; h < 3; ++h) {
			slab_size *= blockSizeInEachDimension[h];
		}
		for (size_t h = 0; h < 3; ++h) {
			slab_size *= blockCountPerDimension[h];
		}

		// Adding block split coordinate lines to the selected regions
		// traversing all bloc pillars in direction i and then in direction j
		for (unsigned int jPillarIndex = blockInformation->jInterfaceStart; jPillarIndex <= blockInformation->jInterfaceEnd; ++jPillarIndex) {
			for (unsigned int iPillarIndex = blockInformation->iInterfaceStart; iPillarIndex <= blockInformation->iInterfaceEnd; iPillarIndex++) {
				unsigned int pillarIndex = getGlobalIndexPillarFromIjIndex(iPillarIndex, jPillarIndex);

				if (!splitInformation[pillarIndex].empty()) {
					// here is a split pillar

					// traversing all split coordinate lines corresponding to the current splitted pillar
					for (size_t splitCoordinateLineIndex = 0; splitCoordinateLineIndex < splitInformation[pillarIndex].size(); ++splitCoordinateLineIndex) {
						// traversing adjacent columns, it current column is in the bloc, corresponding coordinate line is added to the selected region
						for (size_t columnIndex = 0; columnIndex < splitInformation[pillarIndex][splitCoordinateLineIndex].second.size(); ++columnIndex) {
							unsigned int iColumnIndex = getIColumnFromGlobalIndex(splitInformation[pillarIndex][splitCoordinateLineIndex].second[columnIndex]);
							unsigned int jColumnIndex = getJColumnFromGlobalIndex(splitInformation[pillarIndex][splitCoordinateLineIndex].second[columnIndex]);
								
							if ((iColumnIndex >= blockInformation->iInterfaceStart && iColumnIndex < blockInformation->iInterfaceEnd) && (jColumnIndex >= blockInformation->jInterfaceStart && jColumnIndex < blockInformation->jInterfaceEnd))
							{
								// here is a split coordinate line impacting the bloc
								unsigned int splitCoordinateLineHdfIndex = (getICellCount() + 1) * (getJCellCount() + 1) + splitInformation[pillarIndex][splitCoordinateLineIndex].first;

								// the split coordinate line is added to the selected region
								blockCountPerDimension[0] = 1;
								blockCountPerDimension[1] = 1;
								blockCountPerDimension[2] = 1;
								offsetPerDimension[0] = blockInformation->kInterfaceStart;
								offsetPerDimension[1] = splitCoordinateLineHdfIndex;
								offsetPerDimension[2] = 0;
								strideInEachDimension[0] = 1;
								strideInEachDimension[1] = 1;
								strideInEachDimension[2] = 1;
								blockSizeInEachDimension[0] = blockInformation->kInterfaceEnd - blockInformation->kInterfaceStart + 1;
								blockSizeInEachDimension[1] = 1;
								blockSizeInEachDimension[2] = 3;

								hdfProxy->selectArrayNdOfValues(
									datasetPathInExternalFile,
									blockCountPerDimension.get(),
									offsetPerDimension.get(),
									strideInEachDimension.get(),
									blockSizeInEachDimension.get(),
									3,
									false,
									dataset,
									filespace);

								slab_size += (blockInformation->kInterfaceEnd - blockInformation->kInterfaceStart + 1) * 3;

								break; // in order to be sure not adding twice a same coordinate line if it is adjacent to several columns within the bloc
							}
						}
					}
				}
			}
		}

		// reading values corresponding to the whole selected region (non splitted and splitted part)
		hdfProxy->readArrayNdOfDoubleValues(dataset, filespace, xyzPoints, slab_size);
	}
}

AbstractIjkGridRepresentation::geometryKind IjkGridExplicitRepresentation::getGeometryKind() const
{
	return EXPLICIT;
}

bool IjkGridExplicitRepresentation::isNodeGeometryCompressed() const {
	std::string datasetPathInExternalFile;
	uint64_t splitCoordinateLineCount;
	EML2_NS::AbstractHdfProxy* hdfProxy = getPointDatasetPath(datasetPathInExternalFile, splitCoordinateLineCount);
	return hdfProxy->isCompressed(datasetPathInExternalFile);
}
