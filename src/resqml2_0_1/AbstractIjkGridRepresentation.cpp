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

#include "resqml2_0_1/AbstractIjkGridRepresentation.h"

#include <stdexcept>

#include "hdf5.h"

#include "resqml2/AbstractFeatureInterpretation.h"
#include "resqml2/AbstractLocal3dCrs.h"
#include "common/AbstractHdfProxy.h"

using namespace std;
using namespace gsoap_resqml2_0_1;
using namespace RESQML2_0_1_NS;

const char* AbstractIjkGridRepresentation::XML_TAG = "IjkGridRepresentation";
const char* AbstractIjkGridRepresentation::XML_TAG_TRUNCATED = "TruncatedIjkGridRepresentation";

std::string AbstractIjkGridRepresentation::getXmlTag() const
{
	return !isTruncated() ? XML_TAG : XML_TAG_TRUNCATED;
}

void AbstractIjkGridRepresentation::init(soap* soapContext, RESQML2_NS::AbstractLocal3dCrs * crs,
			const std::string & guid, const std::string & title,
			const unsigned int & iCount, const unsigned int & jCount, const unsigned int & kCount,
			bool withTruncatedPillars)
{
	if (soapContext == nullptr) {
		throw invalid_argument("The soap context cannot be null.");
	}

	if (!withTruncatedPillars) {
		gsoapProxy2_0_1 = soap_new_resqml2__obj_USCOREIjkGridRepresentation(soapContext, 1);
		_resqml2__IjkGridRepresentation* ijkGrid = getSpecializedGsoapProxy();

		ijkGrid->Ni = iCount;
		ijkGrid->Nj = jCount;
		ijkGrid->Nk = kCount;
	}
	else {
		gsoapProxy2_0_1 = soap_new_resqml2__obj_USCORETruncatedIjkGridRepresentation(soapContext, 1);
		_resqml2__TruncatedIjkGridRepresentation* ijkGrid = static_cast<_resqml2__TruncatedIjkGridRepresentation*>(gsoapProxy2_0_1);

		ijkGrid->Ni = iCount;
		ijkGrid->Nj = jCount;
		ijkGrid->Nk = kCount;
	}

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "", "");

	// relationhsips
	if (crs != nullptr) {
		localCrs = crs;
		localCrs->addRepresentation(this);
	}
}

AbstractIjkGridRepresentation::AbstractIjkGridRepresentation(soap* soapContext, RESQML2_NS::AbstractLocal3dCrs * crs,
	const std::string & guid, const std::string & title,
	const unsigned int & iCount, const unsigned int & jCount, const unsigned int & kCount,
	bool withTruncatedPillars) :
	RESQML2_NS::AbstractColumnLayerGridRepresentation(nullptr, crs, withTruncatedPillars), splitInformation(nullptr), blockInformation(nullptr)
{
	init(soapContext, crs, guid, title, iCount, jCount, kCount, withTruncatedPillars);
}

AbstractIjkGridRepresentation::AbstractIjkGridRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp, RESQML2_NS::AbstractLocal3dCrs * crs,
	const std::string & guid, const std::string & title,
	const unsigned int & iCount, const unsigned int & jCount, const unsigned int & kCount,
	bool withTruncatedPillars) :
	RESQML2_NS::AbstractColumnLayerGridRepresentation(interp, crs, withTruncatedPillars), splitInformation(nullptr), blockInformation(nullptr)
{
	if (interp == nullptr) {
		throw invalid_argument("The interpretation of the IJK grid cannot be null.");
	}

	init(interp->getGsoapContext(), crs, guid, title, iCount, jCount, kCount, withTruncatedPillars);

	// relationhsips
	setInterpretation(interp);
}

_resqml2__IjkGridRepresentation* AbstractIjkGridRepresentation::getSpecializedGsoapProxy() const
{
	cannotBePartial();
	return static_cast<_resqml2__IjkGridRepresentation*>(gsoapProxy2_0_1);
}

gsoap_resqml2_0_1::_resqml2__TruncatedIjkGridRepresentation* AbstractIjkGridRepresentation::getSpecializedTruncatedGsoapProxy() const
{
	cannotBePartial();
	return static_cast<_resqml2__TruncatedIjkGridRepresentation*>(gsoapProxy2_0_1);
}

gsoap_resqml2_0_1::resqml2__PointGeometry* AbstractIjkGridRepresentation::getPointGeometry2_0_1(const unsigned int & patchIndex) const
{
	if (patchIndex == 0) {
		return isTruncated() ? getSpecializedTruncatedGsoapProxy()->Geometry : getSpecializedGsoapProxy()->Geometry;
	}

	throw range_error("There cannot be more than one patch is an ijk grid representation.");
}

unsigned int AbstractIjkGridRepresentation::getICellCount() const
{
	return isTruncated() ? getSpecializedTruncatedGsoapProxy()->Ni : getSpecializedGsoapProxy()->Ni;
}

void AbstractIjkGridRepresentation::setICellCount(const unsigned int & iCount)
{
	if (!isTruncated()) {
		getSpecializedGsoapProxy()->Ni = iCount;
	}
	else {
		getSpecializedTruncatedGsoapProxy()->Ni = iCount;
	}
}

unsigned int AbstractIjkGridRepresentation::getJCellCount() const
{
	return isTruncated() ? getSpecializedTruncatedGsoapProxy()->Nj : getSpecializedGsoapProxy()->Nj;
}

void AbstractIjkGridRepresentation::setJCellCount(const unsigned int & jCount)
{
	if (!isTruncated()) {
		getSpecializedGsoapProxy()->Nj = jCount;
	}
	else {
		getSpecializedTruncatedGsoapProxy()->Nj = jCount;
	}
}

bool AbstractIjkGridRepresentation::isRightHanded() const
{
	gsoap_resqml2_0_1::resqml2__IjkGridGeometry* geom = static_cast<gsoap_resqml2_0_1::resqml2__IjkGridGeometry*>(getPointGeometry2_0_1(0));
	if (geom != nullptr) {
		return geom->GridIsRighthanded;
	}
	else {
		throw invalid_argument("The grid has no geometry.");
	}
}

void AbstractIjkGridRepresentation::getPillarsOfSplitCoordinateLines(unsigned int * pillarIndices, bool reverseIAxis, bool reverseJAxis) const
{
	gsoap_resqml2_0_1::resqml2__IjkGridGeometry* geom = static_cast<gsoap_resqml2_0_1::resqml2__IjkGridGeometry*>(getPointGeometry2_0_1(0));
	if (geom == nullptr || geom->SplitCoordinateLines == nullptr) {
		throw invalid_argument("There is no geometry or no split coordinate line in this grid.");
	}
	if (geom->SplitCoordinateLines->PillarIndices->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__IntegerHdf5Array){
		hdfProxy->readArrayNdOfUIntValues(static_cast<resqml2__IntegerHdf5Array*>(geom->SplitCoordinateLines->PillarIndices)->Values->PathInHdfFile, pillarIndices);
	}
	else {
		throw std::logic_error("Not yet implemented");
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
	gsoap_resqml2_0_1::resqml2__IjkGridGeometry* geom = static_cast<gsoap_resqml2_0_1::resqml2__IjkGridGeometry*>(getPointGeometry2_0_1(0));
	if (geom == nullptr || geom->SplitCoordinateLines == nullptr) {
		throw invalid_argument("There is no geometry or no split coordinate line in this grid.");
	}
	if (geom->SplitCoordinateLines->ColumnsPerSplitCoordinateLine->Elements->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__IntegerHdf5Array) {
		hdfProxy->readArrayNdOfUIntValues(static_cast<resqml2__IntegerHdf5Array*>(geom->SplitCoordinateLines->ColumnsPerSplitCoordinateLine->Elements)->Values->PathInHdfFile, columnIndices);
	}
	else
		throw std::logic_error("Not yet implemented");

	if (reverseIAxis || reverseJAxis) {
		hssize_t datasetValueCount = hdfProxy->getElementCount(static_cast<resqml2__IntegerHdf5Array*>(geom->SplitCoordinateLines->ColumnsPerSplitCoordinateLine->Elements)->Values->PathInHdfFile);
		if (reverseIAxis) {
			for (unsigned int index = 0; index < datasetValueCount; ++index) {
				unsigned int iColumn = columnIndices[index] % getICellCount();
				unsigned int jColumn = columnIndices[index] / getICellCount();
				columnIndices[index] = (getICellCount() - 1 - iColumn) + jColumn*getICellCount();
			}
		}
		if (reverseJAxis) {
			for (unsigned int index = 0; index < datasetValueCount; ++index) {
				unsigned int iColumn = columnIndices[index] % getICellCount();
				unsigned int jColumn = columnIndices[index] / getICellCount();
				columnIndices[index] = iColumn + (getJCellCount() - 1 - jColumn)*getICellCount();
			}
		}
	}
}

void AbstractIjkGridRepresentation::getColumnCountOfSplitCoordinateLines(unsigned int * columnIndexCountPerSplitCoordinateLine) const
{
	gsoap_resqml2_0_1::resqml2__IjkGridGeometry* geom = static_cast<gsoap_resqml2_0_1::resqml2__IjkGridGeometry*>(getPointGeometry2_0_1(0));
	if (geom == nullptr || geom->SplitCoordinateLines == nullptr) {
		throw invalid_argument("There is no geometry or no split coordinate line in this grid.");
	}
	if (geom->SplitCoordinateLines->ColumnsPerSplitCoordinateLine->CumulativeLength->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__IntegerHdf5Array) {
		hdfProxy->readArrayNdOfUIntValues(static_cast<resqml2__IntegerHdf5Array*>(geom->SplitCoordinateLines->ColumnsPerSplitCoordinateLine->CumulativeLength)->Values->PathInHdfFile, columnIndexCountPerSplitCoordinateLine);
	}
	else {
		throw std::logic_error("Not yet implemented");
	}
}

unsigned long AbstractIjkGridRepresentation::getSplitCoordinateLineCount() const
{
	gsoap_resqml2_0_1::resqml2__IjkGridGeometry* geom = static_cast<gsoap_resqml2_0_1::resqml2__IjkGridGeometry*>(getPointGeometry2_0_1(0));
	if (geom == nullptr) {
		throw invalid_argument("There is no geometry on this grid.");
	}

	return geom->SplitCoordinateLines != nullptr ? geom->SplitCoordinateLines->Count : 0;
}

unsigned long AbstractIjkGridRepresentation::getBlockSplitCoordinateLineCount() const
{
	if (blockInformation == nullptr)
		throw invalid_argument("The block information must have been loaded first.");

	unsigned long splitCoordinateLineCount = 0;
	
	// I traverse all pillars of the block
	for (unsigned int jPillarIndex = blockInformation->jInterfaceStart; jPillarIndex <= blockInformation->jInterfaceEnd; ++jPillarIndex)
	{
		for (unsigned int iPillarIndex = blockInformation->iInterfaceStart; iPillarIndex <= blockInformation->iInterfaceEnd; iPillarIndex++)
		{
			unsigned int pillarIndex = getGlobalIndexPillarFromIjIndex(iPillarIndex, jPillarIndex);

			// if I am looking at a splitted pillar
			if (splitInformation[pillarIndex].size() != 0) 
			{
				// I traverse all corresponding splitted coordinate lines
				for (unsigned int splitCoordinateLineIndex = 0; splitCoordinateLineIndex < splitInformation[pillarIndex].size(); ++splitCoordinateLineIndex)
				{
					// I traverse all columns adjacent to the split coordinate line
					for (unsigned int columnIndex = 0; columnIndex < splitInformation[pillarIndex][splitCoordinateLineIndex].second.size(); ++columnIndex)
					{
						unsigned int iColumnIndex = getIColumnFromGlobalIndex(splitInformation[pillarIndex][splitCoordinateLineIndex].second[columnIndex]);
						unsigned int jColumnIndex = getJColumnFromGlobalIndex(splitInformation[pillarIndex][splitCoordinateLineIndex].second[columnIndex]);

						// if the split coordinate line is adjacent to the cell of the block, I count the corresponding splited pillar
						if ((iColumnIndex >= blockInformation->iInterfaceStart && iColumnIndex <= blockInformation->iInterfaceEnd - 1) && (jColumnIndex >= blockInformation->jInterfaceStart && jColumnIndex <= blockInformation->jInterfaceEnd - 1))
						{
							++splitCoordinateLineCount;

							break; // to be sure not to count several time a same split pillar
						}
					}
				}
			}
		}
	}

	return splitCoordinateLineCount;
}


ULONG64 AbstractIjkGridRepresentation::getSplitNodeCount() const
{
	gsoap_resqml2_0_1::resqml2__IjkGridGeometry* geom = static_cast<gsoap_resqml2_0_1::resqml2__IjkGridGeometry*>(getPointGeometry2_0_1(0));
	if (geom == nullptr) {
		throw invalid_argument("There is no geometry on this grid.");
	}

	return geom->SplitNodes != nullptr ? geom->SplitNodes->Count : 0;
}

void AbstractIjkGridRepresentation::getPillarGeometryIsDefined(bool * pillarGeometryIsDefined, bool reverseIAxis, bool reverseJAxis) const
{
	gsoap_resqml2_0_1::resqml2__IjkGridGeometry* geom = static_cast<gsoap_resqml2_0_1::resqml2__IjkGridGeometry*>(getPointGeometry2_0_1(0));
	if (geom != nullptr) {
		unsigned int pillarCount = (getJCellCount() + 1) * (getICellCount() + 1);
		if (geom->PillarGeometryIsDefined->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__BooleanHdf5Array)
		{
			hid_t dt = hdfProxy->getHdfDatatypeInDataset(static_cast<resqml2__BooleanHdf5Array*>(geom->PillarGeometryIsDefined)->Values->PathInHdfFile);
			if (H5Tequal(dt, H5T_NATIVE_CHAR) > 0) {
				char* tmp = new char[pillarCount];
				hdfProxy->readArrayNdOfCharValues(static_cast<resqml2__BooleanHdf5Array*>(geom->PillarGeometryIsDefined)->Values->PathInHdfFile, tmp);
				for (unsigned int i = 0; i < pillarCount; ++i) {
					if (tmp[i] == 0) pillarGeometryIsDefined[i] = false; else pillarGeometryIsDefined[i] = true;
				}
				delete[] tmp;
			}
			else if (H5Tequal(dt, H5T_NATIVE_UCHAR) > 0) {
				unsigned char* tmp = new unsigned char[pillarCount];
				hdfProxy->readArrayNdOfUCharValues(static_cast<resqml2__BooleanHdf5Array*>(geom->PillarGeometryIsDefined)->Values->PathInHdfFile, tmp);
				for (unsigned int i = 0; i < pillarCount; ++i) {
					if (tmp[i] == 0) pillarGeometryIsDefined[i] = false; else pillarGeometryIsDefined[i] = true;
				}
				delete[] tmp;
			}
			else {
				throw std::logic_error("Not yet implemented");
			}
		}
		else if (geom->PillarGeometryIsDefined->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__BooleanConstantArray) {
			if (static_cast<resqml2__BooleanConstantArray*>(geom->PillarGeometryIsDefined)->Value == true) {
				for (unsigned int i = 0; i < pillarCount; ++i) {
					pillarGeometryIsDefined[i] = true;
				}
			}
			else {
				for (unsigned int i = 0; i < pillarCount; ++i) {
					pillarGeometryIsDefined[i] = false;
				}
			}
		}
		else {
			throw std::logic_error("Not yet implemented");
		}
	}
	else {
		throw invalid_argument("The grid has no geometry.");
	}

	

	if (reverseIAxis || reverseJAxis)
	{
		unsigned int iPillarCount = getICellCount()+1;
		unsigned int jPillarCount = getJCellCount()+1;
		unsigned int arrayCount = iPillarCount * jPillarCount;

		// Copy in order not to modify the controlPoints pointer
		bool * initialPillarGeometryIsDefined = new bool [arrayCount];
		for (unsigned int index = 0; index < arrayCount; ++index)
		{
			initialPillarGeometryIsDefined[index] = pillarGeometryIsDefined[index];
		}

		if (reverseIAxis)
		{
			unsigned int pillarIndex = 0;
			for (unsigned int j = 0; j < jPillarCount; ++j)
			{
				for (unsigned int i = 0; i < iPillarCount; ++i)
				{
					pillarGeometryIsDefined[pillarIndex] = initialPillarGeometryIsDefined[getICellCount() - i + j*iPillarCount];
					++pillarIndex;
				}
			}
		}

		if (reverseJAxis)
		{
			unsigned int pillarIndex = 0;
			for (unsigned int j = 0; j < jPillarCount; ++j)
			{
				for (unsigned int i = 0; i < iPillarCount; ++i)
				{
					pillarGeometryIsDefined[pillarIndex] = initialPillarGeometryIsDefined[i + (getJCellCount() - j)*iPillarCount];
					++pillarIndex;
				}
			}
		}

		delete [] initialPillarGeometryIsDefined;
	}
}

bool AbstractIjkGridRepresentation::hasEnabledCellInformation() const
{
	gsoap_resqml2_0_1::resqml2__IjkGridGeometry* geom = static_cast<gsoap_resqml2_0_1::resqml2__IjkGridGeometry*>(getPointGeometry2_0_1(0));
	return geom != nullptr && geom->CellGeometryIsDefined != nullptr;
}

void AbstractIjkGridRepresentation::getEnabledCells(bool * enabledCells, bool reverseIAxis, bool reverseJAxis, bool reverseKAxis) const
{
	if (!hasEnabledCellInformation()) {
		throw invalid_argument("The grid has no geometry or no information about enabled cells.");
	}

	gsoap_resqml2_0_1::resqml2__IjkGridGeometry* geom = static_cast<gsoap_resqml2_0_1::resqml2__IjkGridGeometry*>(getPointGeometry2_0_1(0));
	if (geom == nullptr) {
		throw invalid_argument("There is no geometry on this grid.");
	}

	ULONG64 cellCount = getCellCount();
	if (geom->CellGeometryIsDefined->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__BooleanHdf5Array) {
		char* tmp = new char[cellCount];
		hdfProxy->readArrayNdOfCharValues(static_cast<resqml2__BooleanHdf5Array*>(geom->CellGeometryIsDefined)->Values->PathInHdfFile, tmp);
		for (ULONG64 i = 0; i < cellCount; ++i) {
			if (tmp[i] == 0) enabledCells[i] = false; else enabledCells[i] = true;
		}
		delete [] tmp;
	}
	else if (geom->CellGeometryIsDefined->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__BooleanConstantArray) {
		if (static_cast<resqml2__BooleanConstantArray*>(geom->CellGeometryIsDefined)->Value == true) {
			for (unsigned int i = 0; i < cellCount; ++i) {
				enabledCells[i] = true;
			}
		}
		else {
			for (unsigned int i = 0; i < cellCount; ++i) {
				enabledCells[i] = false;
			}
		}
	}
	else
		throw std::logic_error("Not yet implemented");

	// Copy in order not to modify the controlPoints pointer
	if (reverseIAxis || reverseJAxis || reverseKAxis) {
		ULONG64 arrayCount = getCellCount();
		bool * initialCellGeometryIsDefined = new bool [arrayCount];
		for (ULONG64 index = 0; index < arrayCount; ++index) {
			initialCellGeometryIsDefined[index] = enabledCells[index];
		}

		if (reverseIAxis)
		{
			unsigned int cellIndex = 0;
			for (unsigned int k = 0; k < getKCellCount(); ++k)
			{
				for (unsigned int j = 0; j < getJCellCount(); ++j)
				{
					for (unsigned int i = 0; i < getICellCount(); ++i)
					{
						enabledCells[cellIndex] = initialCellGeometryIsDefined[getICellCount() - 1 - i + j*getICellCount() + k*getICellCount()*getJCellCount()];
						++cellIndex;
					}
				}
			}
		}

		if (reverseJAxis)
		{
			unsigned int cellIndex = 0;
			for (unsigned int k = 0; k < getKCellCount(); ++k)
			{
				for (unsigned int j = 0; j < getJCellCount(); ++j)
				{
					for (unsigned int i = 0; i < getICellCount(); ++i)
					{
						enabledCells[cellIndex] = initialCellGeometryIsDefined[i + (getJCellCount() - 1 -j)*getICellCount() + k*getICellCount()*getJCellCount()];
						++cellIndex;
					}
				}
			}
		}

		if (reverseKAxis)
		{
			unsigned int cellIndex = 0;
			for (unsigned int k = 0; k < getKCellCount(); ++k)
			{
				for (unsigned int j = 0; j < getJCellCount(); ++j)
				{
					for (unsigned int i = 0; i < getICellCount(); ++i)
					{
						enabledCells[cellIndex] = initialCellGeometryIsDefined[i + j*getICellCount() + (getKCellCount() - 1 -k)*getICellCount()*getJCellCount()];
						++cellIndex;
					}
				}
			}
		}

		delete [] initialCellGeometryIsDefined;
	}
}

unsigned int AbstractIjkGridRepresentation::getIPillarFromGlobalIndex(const unsigned int & globalIndex) const
{
	if (globalIndex >= getPillarCount())
		throw invalid_argument("The pillar index is out of range.");

	return globalIndex % (getICellCount() + 1);
}

unsigned int AbstractIjkGridRepresentation::getJPillarFromGlobalIndex(const unsigned int & globalIndex) const
{
	if (globalIndex >= getPillarCount())
		throw invalid_argument("The pillar index is out of range.");

	return globalIndex / (getICellCount() + 1);
}

unsigned int AbstractIjkGridRepresentation::getGlobalIndexPillarFromIjIndex(const unsigned int & iPillar, const unsigned int & jPillar) const
{
	if (iPillar > getICellCount())
		throw invalid_argument("The pillar I index is out of range.");
	if (jPillar > getJCellCount())
		throw invalid_argument("The pillar J index is out of range.");

	return iPillar + (getICellCount() + 1) * jPillar;
}

unsigned int AbstractIjkGridRepresentation::getIColumnFromGlobalIndex(const unsigned int & globalIndex) const
{
	if (globalIndex >= getColumnCount())
		throw invalid_argument("The column index is out of range.");

	return globalIndex % getICellCount();
}

unsigned int AbstractIjkGridRepresentation::getJColumnFromGlobalIndex(const unsigned int & globalIndex) const
{
	if (globalIndex >= getColumnCount())
		throw invalid_argument("The column index is out of range.");

	return globalIndex / getICellCount();
}

unsigned int AbstractIjkGridRepresentation::getGlobalIndexColumnFromIjIndex(const unsigned int & iColumn, const unsigned int & jColumn) const
{
	if (iColumn >= getICellCount())
		throw invalid_argument("The column I index is out of range.");
	if (jColumn >= getJCellCount())
		throw invalid_argument("The column J index is out of range.");

	return iColumn + getICellCount() * jColumn;
}

unsigned int AbstractIjkGridRepresentation::getGlobalIndexCellFromIjkIndex(const unsigned int & iCell, const unsigned int & jCell, const unsigned int & kCell) const
{
	if (iCell >= getICellCount())
		throw invalid_argument("The cell I index is out of range.");
	if (jCell >= getJCellCount())
		throw invalid_argument("The cell J index is out of range.");
	if (kCell >= getKCellCount())
		throw invalid_argument("The cell K index is out of range.");

	return iCell + getICellCount() * jCell + getColumnCount() * kCell;
}

void AbstractIjkGridRepresentation::loadSplitInformation()
{
	unloadSplitInformation();
	splitInformation = new std::vector< std::pair< unsigned int, std::vector<unsigned int> > >[(getICellCount()+1) * (getJCellCount()+1)];

	gsoap_resqml2_0_1::resqml2__IjkGridGeometry* geom = static_cast<gsoap_resqml2_0_1::resqml2__IjkGridGeometry*>(getPointGeometry2_0_1(0));
	if (geom == nullptr) {
		throw invalid_argument("There is no geometry on this grid.");
	}
	if (geom->SplitCoordinateLines != nullptr)
	{
		// Read the split information
		unsigned int* splitPillars = new unsigned int [getSplitCoordinateLineCount()];
		getPillarsOfSplitCoordinateLines(splitPillars);
		unsigned int* columnIndexCumulativeCountPerSplitCoordinateLine = new unsigned int[getSplitCoordinateLineCount()];
		getColumnCountOfSplitCoordinateLines(columnIndexCumulativeCountPerSplitCoordinateLine);
		unsigned int* splitColumnIndices = new unsigned int [columnIndexCumulativeCountPerSplitCoordinateLine[getSplitCoordinateLineCount() - 1]];
		getColumnsOfSplitCoordinateLines(splitColumnIndices);

		// Rearrange the split information
		std::pair< unsigned int, std::vector<unsigned int> > splittedColumns;
		splittedColumns.first = 0;
		for (unsigned int splitColumnIndex = 0;
			splitColumnIndex < columnIndexCumulativeCountPerSplitCoordinateLine[0];
			++splitColumnIndex)
		{
			splittedColumns.second.push_back(splitColumnIndices[splitColumnIndex]);
		}
		splitInformation[splitPillars[0]].push_back(splittedColumns);
		for (unsigned int splitCoordinateLineIndex = 1; splitCoordinateLineIndex < getSplitCoordinateLineCount(); ++splitCoordinateLineIndex)
		{
			splittedColumns.first = splitCoordinateLineIndex;
			splittedColumns.second.clear();
			for (unsigned int splitColumnIndex = columnIndexCumulativeCountPerSplitCoordinateLine[splitCoordinateLineIndex-1];
				splitColumnIndex < columnIndexCumulativeCountPerSplitCoordinateLine[splitCoordinateLineIndex];
				++splitColumnIndex)
			{
				splittedColumns.second.push_back(splitColumnIndices[splitColumnIndex]);
			}
			splitInformation[splitPillars[splitCoordinateLineIndex]].push_back(splittedColumns);
		}
		
		delete [] splitPillars;
		delete [] columnIndexCumulativeCountPerSplitCoordinateLine;
		delete [] splitColumnIndices;
	}
}

void AbstractIjkGridRepresentation::loadBlockInformation(const unsigned int & iInterfaceStart, const unsigned int & iInterfaceEnd, const unsigned int & jInterfaceStart, const unsigned int & jInterfaceEnd, const unsigned int & kInterfaceStart, const unsigned int & kInterfaceEnd)
{
	if (splitInformation == nullptr)
		throw invalid_argument("The split information must have been loaded first.");

	if (iInterfaceEnd > getICellCount() || iInterfaceEnd > getICellCount())
		throw range_error("iInterfaceStart and/or iInterfaceEnd is/are out of boundaries.");
	if (iInterfaceStart > iInterfaceEnd)
		throw range_error("iInterfaceStart > iInterfaceEnd");

	if (jInterfaceEnd > getJCellCount() || jInterfaceEnd > getJCellCount())
		throw range_error("jInterfaceStart and/or jInterfaceEnd is/are out of boundaries.");
	if (jInterfaceStart > jInterfaceEnd)
		throw range_error("jInterfaceStart > jInterfaceEnd");

	if (kInterfaceEnd > getKCellCount() || kInterfaceEnd > getKCellCount())
		throw range_error("kInterfaceStart and/or kInterfaceEnd is/are out of boundaries.");
	if (kInterfaceStart > kInterfaceEnd)
		throw range_error("kInterfaceStart > kInterfaceEnd");

	if (blockInformation != nullptr)
		delete blockInformation;

	blockInformation = new BlockInformation();

	blockInformation->iInterfaceStart = iInterfaceStart;
	blockInformation->iInterfaceEnd = iInterfaceEnd;
	blockInformation->jInterfaceStart = jInterfaceStart;
	blockInformation->jInterfaceEnd = jInterfaceEnd;
	blockInformation->kInterfaceStart = kInterfaceStart;
	blockInformation->kInterfaceEnd = kInterfaceEnd;

	// seting mapping between global and local (to the block) split coordinate lines index
	unsigned int splitCoordinateLineHdfLocalIndex = (iInterfaceEnd - iInterfaceStart + 1) * (jInterfaceEnd - jInterfaceStart + 1);
	for (unsigned int jPillarIndex = jInterfaceStart; jPillarIndex <= jInterfaceEnd; ++jPillarIndex)
	{
		for (unsigned int iPillarIndex = iInterfaceStart; iPillarIndex <= iInterfaceEnd; iPillarIndex++)
		{
			unsigned int pillarIndex = getGlobalIndexPillarFromIjIndex(iPillarIndex, jPillarIndex);

			if (splitInformation[pillarIndex].size() != 0)
			{
				// here is a split pillar

				// traversing all split coordinate lines corresponding to the current splitted pillar
				for (unsigned int splitCoordinateLineIndex = 0; splitCoordinateLineIndex < splitInformation[pillarIndex].size(); ++splitCoordinateLineIndex)
				{
					// traversing adjacent columns, it current column is in the bloc, corresponding coordinate line is added to the selected region
					for (unsigned int columnIndex = 0; columnIndex < splitInformation[pillarIndex][splitCoordinateLineIndex].second.size(); ++columnIndex)
					{
						unsigned int iColumnIndex = getIColumnFromGlobalIndex(splitInformation[pillarIndex][splitCoordinateLineIndex].second[columnIndex]);
						unsigned int jColumnIndex = getJColumnFromGlobalIndex(splitInformation[pillarIndex][splitCoordinateLineIndex].second[columnIndex]);

						if ((iColumnIndex >= iInterfaceStart && iColumnIndex < iInterfaceEnd) && (jColumnIndex >= jInterfaceStart && jColumnIndex < jInterfaceEnd))
						{
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

	gsoap_resqml2_0_1::resqml2__IjkGridGeometry* geom = static_cast<gsoap_resqml2_0_1::resqml2__IjkGridGeometry*>(getPointGeometry2_0_1(0));
	if (geom == nullptr) {
		throw invalid_argument("There is no geometry on this grid.");
	}
	if (geom->SplitCoordinateLines != nullptr)
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

bool AbstractIjkGridRepresentation::isColumnEdgeSplitted(const unsigned int & iColumn, const unsigned int & jColumn, const unsigned int & edge) const
{
	if (splitInformation == nullptr)
		throw invalid_argument("The split information must have been loaded first.");
	if (iColumn > getICellCount())
		throw range_error("I column is out of range.");
	if (jColumn > getJCellCount())
		throw range_error("J column is out of range.");
	if (edge > 7)
		throw range_error("Edge is out of range.");

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

	if (iOtherColum < 0 || jOtherColum < 0 || iOtherColum >= getICellCount() || jOtherColum >= getJCellCount())
		return false;
	unsigned int otherColumnIndex = getGlobalIndexColumnFromIjIndex(iOtherColum, jOtherColum);

	// Check split on first pillar of the column edge
	bool result = false;
	unsigned int pillarIndex = getGlobalIndexPillarFromIjIndex(iPillarIndex, jPillarIndex);
	if (splitInformation[pillarIndex].size() != 0)
	{
		unsigned int columnIndex = getGlobalIndexColumnFromIjIndex(iColumn, jColumn);
		for (size_t columnSet = 0; columnSet < splitInformation[pillarIndex].size(); ++columnSet)
			for (size_t column = 0; column < splitInformation[pillarIndex][columnSet].second.size(); ++column)
			{
				if (splitInformation[pillarIndex][columnSet].second[column] == columnIndex)
				{
					result = true;
					for (size_t otherColumn = 0; otherColumn < splitInformation[pillarIndex][columnSet].second.size(); ++otherColumn)
					{
						if (splitInformation[pillarIndex][columnSet].second[otherColumn] == otherColumnIndex)
							result = false;
					}
					if (result == true)
						return true;
					else
					{
						columnSet = splitInformation[pillarIndex].size();
						break;
					}
				}
				else if  (splitInformation[pillarIndex][columnSet].second[column] == otherColumnIndex)
				{
					result = true;
					for (size_t otherColumn = 0; otherColumn < splitInformation[pillarIndex][columnSet].second.size(); ++otherColumn)
					{
						if (splitInformation[pillarIndex][columnSet].second[otherColumn] == columnIndex)
							result = false;
					}
					if (result == true)
						return true;
					else
					{
						columnSet = splitInformation[pillarIndex].size();
						break;
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
	if (splitInformation[pillarIndex].size() != 0)
	{
		unsigned int columnIndex = getGlobalIndexColumnFromIjIndex(iColumn, jColumn);
		for (size_t columnSet = 0; columnSet < splitInformation[pillarIndex].size(); ++columnSet)
			for (size_t column = 0; column < splitInformation[pillarIndex][columnSet].second.size(); ++column)
			{
				if (splitInformation[pillarIndex][columnSet].second[column] == columnIndex)
				{
					for (size_t otherColumn = 0; otherColumn < splitInformation[pillarIndex][columnSet].second.size(); ++otherColumn)
					{
						if (splitInformation[pillarIndex][columnSet].second[otherColumn] == otherColumnIndex)
							return false;
					}
					return true;
				}
				else if (splitInformation[pillarIndex][columnSet].second[column] == otherColumnIndex)
				{
					for (size_t otherColumn = 0; otherColumn < splitInformation[pillarIndex][columnSet].second.size(); ++otherColumn)
					{
						if (splitInformation[pillarIndex][columnSet].second[otherColumn] == columnIndex)
							return false;
					}
					return true;
				}
			}
	}

	return result;
}

ULONG64 AbstractIjkGridRepresentation::getXyzPointIndexFromCellCorner(const unsigned int & iCell, const unsigned int & jCell, const unsigned int & kCell, const unsigned int & corner) const
{
	if (splitInformation == nullptr)
		throw invalid_argument("The split information must have been loaded first.");
	if (iCell > getICellCount())
		throw range_error("I Cell is out of range.");
	if (jCell > getJCellCount())
		throw range_error("J Cell is out of range.");
	if (kCell > getKCellCount())
		throw range_error("K Cell is out of range.");
	if (corner > 7)
		throw range_error("Corner is out of range.");

	unsigned int iPillarIndex = iCell;
	if (corner == 1 || corner == 2 || corner == 5 || corner == 6)
		++iPillarIndex;
	unsigned int jPillarIndex = jCell;
	if (corner == 2 || corner == 3 || corner == 6 || corner == 7)
		++jPillarIndex;
	unsigned int kPointIndex = kCell;
	if (corner > 3)
		++kPointIndex;

	unsigned int pillarIndex = getGlobalIndexPillarFromIjIndex(iPillarIndex, jPillarIndex);
	if (splitInformation[pillarIndex].size() != 0)
	{
		unsigned int columnIndex = getGlobalIndexColumnFromIjIndex(iCell, jCell);
		for (size_t columnSet = 0; columnSet < splitInformation[pillarIndex].size(); ++columnSet)
			for (size_t column = 0; column < splitInformation[pillarIndex][columnSet].second.size(); ++column)
			{
				if (splitInformation[pillarIndex][columnSet].second[column] == columnIndex)
				{
					return (getICellCount()+1) * (getJCellCount()+1) + splitInformation[pillarIndex][columnSet].first + kPointIndex * ((getICellCount()+1) * (getJCellCount()+1) + getSplitCoordinateLineCount()); // splitted point
				}
			}
	}

	return iPillarIndex + jPillarIndex * (getICellCount()+1) + kPointIndex * ((getICellCount()+1) * (getJCellCount()+1) + getSplitCoordinateLineCount()); // non splitted point
}

void AbstractIjkGridRepresentation::getXyzPointOfBlockFromCellCorner(const unsigned int & iCell, const unsigned int & jCell, const unsigned int & kCell, const unsigned int & corner,
	const double* xyzPoints, double & x, double & y, double & z) const
{
	if (splitInformation == nullptr)
		throw invalid_argument("The split information must have been loaded first.");
	if (blockInformation == nullptr)
		throw invalid_argument("The block information must have been loaded first.");
	if (corner > 7)
		throw range_error("Corner is out of the block.");

	unsigned int iPillarIndex = iCell;
	if (corner == 1 || corner == 2 || corner == 5 || corner == 6)
		++iPillarIndex;
	unsigned int jPillarIndex = jCell;
	if (corner == 2 || corner == 3 || corner == 6 || corner == 7)
		++jPillarIndex;
	unsigned int kPointIndex = kCell;
	if (corner > 3)
		++kPointIndex;
	kPointIndex -= blockInformation->kInterfaceStart;

	ULONG64 pointIndex;

	unsigned int pillarIndex = getGlobalIndexPillarFromIjIndex(iPillarIndex, jPillarIndex);
	if (splitInformation[pillarIndex].size() != 0)
	{
		unsigned int columnIndex = getGlobalIndexColumnFromIjIndex(iCell, jCell);
		for (size_t columnSet = 0; columnSet < splitInformation[pillarIndex].size(); ++columnSet)
			for (size_t column = 0; column < splitInformation[pillarIndex][columnSet].second.size(); ++column)
			{
				if (splitInformation[pillarIndex][columnSet].second[column] == columnIndex)
				{
					pointIndex = (blockInformation->globalToLocalSplitCoordinateLinesIndex)[splitInformation[pillarIndex][columnSet].first] + kPointIndex * ((blockInformation->iInterfaceEnd - blockInformation->iInterfaceStart + 1) * (blockInformation->jInterfaceEnd - blockInformation->jInterfaceStart + 1) + getBlockSplitCoordinateLineCount()); // splitted point
					x = xyzPoints[3 * pointIndex];
					y = xyzPoints[3 * pointIndex + 1];
					z = xyzPoints[3 * pointIndex + 2];
					return;
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

ULONG64 AbstractIjkGridRepresentation::getXyzPointCountOfKInterfaceOfPatch(const unsigned int & patchIndex) const
{
	gsoap_resqml2_0_1::resqml2__IjkGridGeometry* geom = static_cast<gsoap_resqml2_0_1::resqml2__IjkGridGeometry*>(getPointGeometry2_0_1(patchIndex));
	if (geom == nullptr) {
		throw invalid_argument("There is no geometry on this grid.");
	}

	return geom->SplitCoordinateLines == nullptr ? getPillarCount() : getPillarCount() + geom->SplitCoordinateLines->Count;
}

ULONG64 AbstractIjkGridRepresentation::getXyzPointCountOfBlock() const
{
	if (blockInformation == nullptr)
		throw invalid_argument("The block information must have been loaded first.");

	return (blockInformation->iInterfaceEnd - blockInformation->iInterfaceStart + 1) * (blockInformation->jInterfaceEnd - blockInformation->jInterfaceStart + 1) * (blockInformation->kInterfaceEnd - blockInformation->kInterfaceStart + 1) + (blockInformation->kInterfaceEnd - blockInformation->kInterfaceStart + 1) * getBlockSplitCoordinateLineCount();
}

void AbstractIjkGridRepresentation::getXyzPointsOfKInterfaceOfPatch(const unsigned int & kInterface, const unsigned int & patchIndex, double * xyzPoints)
{
	getXyzPointsOfKInterfaceSequenceOfPatch(kInterface, kInterface, patchIndex, xyzPoints);
}

void AbstractIjkGridRepresentation::setEnabledCells(unsigned char* enabledCells)
{
	gsoap_resqml2_0_1::resqml2__IjkGridGeometry* geom = static_cast<gsoap_resqml2_0_1::resqml2__IjkGridGeometry*>(getPointGeometry2_0_1(0));
	if (geom == nullptr) {
		throw invalid_argument("There is no geometry on this grid.");
	}

	resqml2__BooleanHdf5Array* boolArray = soap_new_resqml2__BooleanHdf5Array(gsoapProxy2_0_1->soap, 1);
	geom->CellGeometryIsDefined = boolArray;

	boolArray->Values = soap_new_eml20__Hdf5Dataset(gsoapProxy2_0_1->soap, 1);
	boolArray->Values->HdfProxy = hdfProxy->newResqmlReference();
	boolArray->Values->PathInHdfFile = "/RESQML/" + gsoapProxy2_0_1->uuid + "/CellGeometryIsDefined";

	// HDF
	hsize_t * cellGeometryIsDefinedCount = new hsize_t[3];
	cellGeometryIsDefinedCount[0] = getKCellCount();
	cellGeometryIsDefinedCount[1] = getJCellCount();
	cellGeometryIsDefinedCount[2] = getICellCount();
	hdfProxy->writeArrayNd(gsoapProxy2_0_1->uuid, "CellGeometryIsDefined", H5T_NATIVE_UCHAR, enabledCells, cellGeometryIsDefinedCount, 3);
	delete [] cellGeometryIsDefinedCount;
}

gsoap_resqml2_0_1::resqml2__KDirection AbstractIjkGridRepresentation::getKDirection() const
{
	gsoap_resqml2_0_1::resqml2__IjkGridGeometry* geom = static_cast<gsoap_resqml2_0_1::resqml2__IjkGridGeometry*>(getPointGeometry2_0_1(0));
	if (geom == nullptr) {
		throw invalid_argument("There is no geometry on this grid.");
	}

	return geom->KDirection;
}

