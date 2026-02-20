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
#include "AbstractColumnLayerGridRepresentation.h"

#include <stdexcept>

#include <H5public.h>

#include "AbstractStratigraphicOrganizationInterpretation.h"

#include "../eml2/AbstractHdfProxy.h"

using namespace gsoap_resqml2_0_1;
using namespace RESQML2_NS;
using namespace std;

uint64_t AbstractColumnLayerGridRepresentation::getKCellCount() const
{
	if (isPartial()) {
		throw logic_error("This method cannot be called on a partial object");
	}

	return gsoapProxy2_0_1 != nullptr
		? (isTruncated() ? static_cast<resqml20__AbstractTruncatedColumnLayerGridRepresentation*>(gsoapProxy2_0_1)->Nk : static_cast<resqml20__AbstractColumnLayerGridRepresentation*>(gsoapProxy2_0_1)->Nk)
		: (isTruncated() ? static_cast<gsoap_eml2_3::resqml22__AbstractTruncatedColumnLayerGridRepresentation*>(gsoapProxy2_3)->Nk : static_cast<gsoap_eml2_3::resqml22__AbstractColumnLayerGridRepresentation*>(gsoapProxy2_3)->Nk);
}

void AbstractColumnLayerGridRepresentation::setKCellCount(uint64_t kCount)
{
	if (isPartial()) {
		throw logic_error("Partial object");
	}

	if (!isTruncated()) {
		if (gsoapProxy2_0_1 != nullptr) {
			static_cast<resqml20__AbstractColumnLayerGridRepresentation*>(gsoapProxy2_0_1)->Nk = kCount;
		}
		else {
			static_cast<gsoap_eml2_3::resqml22__AbstractColumnLayerGridRepresentation*>(gsoapProxy2_3)->Nk = kCount;
		}
	}
	else {
		if (gsoapProxy2_0_1 != nullptr) {
			static_cast<resqml20__AbstractTruncatedColumnLayerGridRepresentation*>(gsoapProxy2_0_1)->Nk = kCount;
		}
		else {
			static_cast<gsoap_eml2_3::resqml22__AbstractTruncatedColumnLayerGridRepresentation*>(gsoapProxy2_3)->Nk = kCount;
		}
	}
}

void AbstractColumnLayerGridRepresentation::setIntervalAssociationWithStratigraphicOrganizationInterpretation(int64_t const* stratiUnitIndices, int64_t nullValue, RESQML2_NS::AbstractStratigraphicOrganizationInterpretation* stratiOrgInterp, EML2_NS::AbstractHdfProxy * hdfProxy)
{
	if (isTruncated()) {
		throw invalid_argument("A truncated grid cannot be linked to a strati column in RESQML2");
	}
	if (hdfProxy == nullptr) {
		hdfProxy = getRepository()->getDefaultHdfProxy();
		if (hdfProxy == nullptr) {
			throw std::invalid_argument("A (default) HDF Proxy must be provided.");
		}
	}
	const uint64_t dim = getKCellCount();
	hdfProxy->writeArrayNd(getHdfGroup(), "IntervalStratigraphicUnits", COMMON_NS::AbstractObject::numericalDatatypeEnum::INT64, stratiUnitIndices, &dim, 1);

	getRepository()->addRelationship(this, hdfProxy);
	getRepository()->addRelationship(this, stratiOrgInterp);

	if (gsoapProxy2_0_1 != nullptr) {
		resqml20__AbstractColumnLayerGridRepresentation* rep = static_cast<resqml20__AbstractColumnLayerGridRepresentation*>(gsoapProxy2_0_1);
		rep->IntervalStratigraphicUnits = soap_new_resqml20__IntervalStratigraphicUnits(rep->soap);
		rep->IntervalStratigraphicUnits->StratigraphicOrganization = stratiOrgInterp->newResqmlReference();

		resqml20__IntegerHdf5Array* xmlDataset = soap_new_resqml20__IntegerHdf5Array(rep->soap);
		xmlDataset->NullValue = nullValue;
		xmlDataset->Values = soap_new_eml20__Hdf5Dataset(gsoapProxy2_0_1->soap);
		xmlDataset->Values->HdfProxy = hdfProxy->newResqmlReference();
		xmlDataset->Values->PathInHdfFile = getHdfGroup() + "/IntervalStratigraphicUnits";
		rep->IntervalStratigraphicUnits->UnitIndices = xmlDataset;
	}
	else if (gsoapProxy2_3 != nullptr) {
		gsoap_eml2_3::resqml22__AbstractColumnLayerGridRepresentation* rep = static_cast<gsoap_eml2_3::resqml22__AbstractColumnLayerGridRepresentation*>(gsoapProxy2_3);
		rep->IntervalStratigraphicUnits = gsoap_eml2_3::soap_new_resqml22__IntervalStratigraphicUnits(rep->soap);
		rep->IntervalStratigraphicUnits->StratigraphicOrganizationInterpretation = stratiOrgInterp->newEml23Reference();

		rep->IntervalStratigraphicUnits->UnitIndices = gsoap_eml2_3::soap_new_eml23__JaggedArray(rep->soap);
		// element XML
		gsoap_eml2_3::eml23__IntegerXmlArray* elementDataset = gsoap_eml2_3::soap_new_eml23__IntegerXmlArray(rep->soap);
		elementDataset->NullValue = nullValue;
		elementDataset->Values = std::to_string(stratiUnitIndices[0]);
		for (uint64_t i = 1; i < getKCellCount(); ++i) {
			elementDataset->Values += " " + std::to_string(stratiUnitIndices[i]);
		}
		rep->IntervalStratigraphicUnits->UnitIndices->Elements = elementDataset;

		// cumulative XML
		gsoap_eml2_3::eml23__IntegerXmlArray* cumulativeDataset = gsoap_eml2_3::soap_new_eml23__IntegerXmlArray(rep->soap);
		cumulativeDataset->NullValue = nullValue;
		cumulativeDataset->Values = "1";
		for (uint64_t i = 1; i < getKCellCount(); ++i) {
			cumulativeDataset->Values += " " + std::to_string(i + 1);
		}
		rep->IntervalStratigraphicUnits->UnitIndices->CumulativeLength = cumulativeDataset;
	}
	else {
		throw logic_error("Not implemented yet");
	}
}

COMMON_NS::DataObjectReference AbstractColumnLayerGridRepresentation::getStratigraphicOrganizationInterpretationDor() const
{
	COMMON_NS::DataObjectReference result = RESQML2_NS::AbstractGridRepresentation::getStratigraphicOrganizationInterpretationDor();
	if (!result.isEmpty()) {
		return result;
	}

	if (isTruncated()) {
		return COMMON_NS::DataObjectReference();
	}

	if (gsoapProxy2_0_1 != nullptr) {
		resqml20__AbstractColumnLayerGridRepresentation* rep = static_cast<resqml20__AbstractColumnLayerGridRepresentation*>(gsoapProxy2_0_1);
		if (rep->IntervalStratigraphicUnits == nullptr) {
			return COMMON_NS::DataObjectReference();
		}
		return COMMON_NS::DataObjectReference(rep->IntervalStratigraphicUnits->StratigraphicOrganization);
	}
	else if (gsoapProxy2_3 != nullptr) {
		gsoap_eml2_3::resqml22__AbstractColumnLayerGridRepresentation* rep = static_cast<gsoap_eml2_3::resqml22__AbstractColumnLayerGridRepresentation*>(gsoapProxy2_3);
		if (rep->IntervalStratigraphicUnits == nullptr) {
			return COMMON_NS::DataObjectReference();
		}
		return COMMON_NS::DataObjectReference(rep->IntervalStratigraphicUnits->StratigraphicOrganizationInterpretation);
	}
	else {
		throw logic_error("Not implemented yet");
	}
}

bool AbstractColumnLayerGridRepresentation::hasIntervalStratigraphicUnitIndices() const
{
	if (isPartial()) {
		throw logic_error("Partial object");
	}

	if (!isTruncated()) {
		if (gsoapProxy2_0_1 != nullptr) {
			return static_cast<resqml20__AbstractColumnLayerGridRepresentation*>(gsoapProxy2_0_1)->IntervalStratigraphicUnits != nullptr;
		}
		else {
			return static_cast<gsoap_eml2_3::resqml22__AbstractColumnLayerGridRepresentation*>(gsoapProxy2_3)->IntervalStratigraphicUnits != nullptr;
		}
	}

	return false;
}

int64_t AbstractColumnLayerGridRepresentation::getIntervalStratigraphicUnitIndices(int64_t* stratiUnitIndices)
{
	if (isTruncated()) {
		throw invalid_argument("A truncated grid cannot be linked to a strati columnumn in Resqml v2.0");
	}
	if (!hasIntervalStratigraphicUnitIndices()) {
		throw invalid_argument("This grid has no Interval StratigraphicUnits information");
	}

	if (gsoapProxy2_0_1 != nullptr) {
		resqml20__AbstractColumnLayerGridRepresentation const* rep = static_cast<resqml20__AbstractColumnLayerGridRepresentation*>(gsoapProxy2_0_1);
		return readArrayNdOfIntegerValues(rep->IntervalStratigraphicUnits->UnitIndices, stratiUnitIndices);
	}
	else if (gsoapProxy2_3 != nullptr) {
		gsoap_eml2_3::resqml22__AbstractColumnLayerGridRepresentation const* rep = static_cast<gsoap_eml2_3::resqml22__AbstractColumnLayerGridRepresentation*>(gsoapProxy2_3);
		if (rep->IntervalStratigraphicUnits->UnitIndices->CumulativeLength->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__IntegerLatticeArray) {
			gsoap_eml2_3::eml23__IntegerLatticeArray const* latticeArray = static_cast<gsoap_eml2_3::eml23__IntegerLatticeArray*>(rep->IntervalStratigraphicUnits->UnitIndices->CumulativeLength);
			if (latticeArray->StartValue == 1 && latticeArray->Offset.size() == 1 &&
				latticeArray->Offset[0]->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__IntegerConstantArray &&
				static_cast<gsoap_eml2_3::eml23__IntegerConstantArray*>(latticeArray->Offset[0])->Value == 1 &&
				static_cast<uint64_t>(static_cast<gsoap_eml2_3::eml23__IntegerConstantArray*>(latticeArray->Offset[0])->Count) == getKCellCount() - 1) {
				auto const* daPart = static_cast<gsoap_eml2_3::eml23__IntegerExternalArray*>(rep->IntervalStratigraphicUnits->UnitIndices->Elements)->Values->ExternalDataArrayPart[0];
				getOrCreateHdfProxyFromDataArrayPart(daPart)->readArrayNdOfInt64Values(daPart->PathInExternalFile, stratiUnitIndices);
				return static_cast<gsoap_eml2_3::eml23__IntegerExternalArray*>(rep->IntervalStratigraphicUnits->UnitIndices->Elements)->NullValue;
			}
			throw logic_error("FESAPI does not support an association of more than one strati unit for a single K layer for now.");
		}
		else if (rep->IntervalStratigraphicUnits->UnitIndices->CumulativeLength->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__IntegerXmlArray) {
			std::unique_ptr<uint64_t[]> cumulativeLength(new uint64_t[getKCellCount()]);
			readArrayNdOfIntegerValues(rep->IntervalStratigraphicUnits->UnitIndices->CumulativeLength, cumulativeLength.get());
			if (cumulativeLength[0] == 1 && cumulativeLength[getKCellCount() - 1] == getKCellCount()) {
				auto* elements = dynamic_cast<gsoap_eml2_3::eml23__AbstractIntegerArray*>(rep->IntervalStratigraphicUnits->UnitIndices->Elements);
				if (elements != nullptr) {
					return readArrayNdOfIntegerValues(elements, stratiUnitIndices);
				}
				throw logic_error("The stratigraphic unit indices associated to K layer must be integers only.");
			}
			throw logic_error("FESAPI does not support an association of more than one strati unit for a single K layer for now.");
		}

		throw logic_error("Not implemented yet.");
	}
	else {
		throw logic_error("Not implemented yet");
	}
}

void AbstractColumnLayerGridRepresentation::loadTargetRelationships()
{
	AbstractGridRepresentation::loadTargetRelationships();

	// Strati org backward relationships
	if (hasIntervalStratigraphicUnitIndices()) {
		COMMON_NS::DataObjectReference dor = getStratigraphicOrganizationInterpretationDor();
		RESQML2_NS::AbstractStratigraphicOrganizationInterpretation* stratiOrg = getRepository()->getDataObjectByUuid<RESQML2_NS::AbstractStratigraphicOrganizationInterpretation>(dor.getUuid());
		if (stratiOrg == nullptr) { // partial transfer
			getRepository()->createPartial(dor);
			stratiOrg = getRepository()->getDataObjectByUuid<RESQML2_NS::AbstractStratigraphicOrganizationInterpretation>(dor.getUuid());
			if (stratiOrg == nullptr) {
				throw invalid_argument("The DOR looks invalid.");
			}
		}
		repository->addRelationship(this, stratiOrg);
	}
}

gsoap_resqml2_0_1::resqml20__PillarShape AbstractColumnLayerGridRepresentation::getMostComplexPillarGeometry() const
{
	if (gsoapProxy2_0_1 != nullptr) {
		gsoap_resqml2_0_1::resqml20__PointGeometry const* geom = getPointGeometry2_0_1(0);
		if (geom == nullptr) {
			throw invalid_argument("This grid has no point geoemtry.");
		}

		gsoap_resqml2_0_1::resqml20__AbstractColumnLayerGridGeometry const* specializedGeom = dynamic_cast<gsoap_resqml2_0_1::resqml20__AbstractColumnLayerGridGeometry const*>(geom);
		if (geom == nullptr) {
			throw invalid_argument("This grid has no AbstractColumnLayerGrid Geometry.");
		}

		return specializedGeom->PillarShape;
	}
	else if (gsoapProxy2_3 != nullptr) {
		gsoap_eml2_3::resqml22__PointGeometry const* geom = getPointGeometry2_2(0);
		if (geom == nullptr) {
			throw invalid_argument("This grid has no point geoemtry.");
		}

		gsoap_eml2_3::resqml22__AbstractColumnLayerGridGeometry const* specializedGeom = dynamic_cast<gsoap_eml2_3::resqml22__AbstractColumnLayerGridGeometry const*>(geom);
		if (geom == nullptr) {
			throw invalid_argument("This grid has no AbstractColumnLayerGrid Geometry.");
		}

		return static_cast<gsoap_resqml2_0_1::resqml20__PillarShape>(specializedGeom->PillarShape);
	}
	else {
		throw logic_error("Not implemented yet");
	}
}

void AbstractColumnLayerGridRepresentation::getSplitNodeParentNodeIndices(uint64_t* splitNodeParentNodeIndices) const
{
	if (gsoapProxy2_0_1 != nullptr) {
		gsoap_resqml2_0_1::resqml20__AbstractColumnLayerGridGeometry* geom = dynamic_cast<gsoap_resqml2_0_1::resqml20__AbstractColumnLayerGridGeometry*>(getPointGeometry2_0_1(0));
		if (geom == nullptr) {
			throw invalid_argument("There is no geometry on this grid.");
		}
		if (geom->SplitNodes == nullptr || geom->SplitNodes->Count == 0) {
			throw invalid_argument("There is no split node on this grid.");
		}

		readArrayNdOfIntegerValues(geom->SplitNodes->ParentNodeIndices, splitNodeParentNodeIndices);
	}
	else {
		gsoap_eml2_3::resqml22__AbstractColumnLayerGridGeometry* geom = dynamic_cast<gsoap_eml2_3::resqml22__AbstractColumnLayerGridGeometry*>(getPointGeometry2_2(0));
		if (geom == nullptr) {
			throw invalid_argument("There is no geometry on this grid.");
		}
		if (geom->SplitNodePatch == nullptr || geom->SplitNodePatch->Count == 0) {
			throw invalid_argument("There is no split node on this grid.");
		}

		readArrayNdOfIntegerValues(geom->SplitNodePatch->ParentNodeIndices, splitNodeParentNodeIndices);
	}
}

void AbstractColumnLayerGridRepresentation::getCumulativeCountOfCellsPerSplitNode(uint64_t* cumulativeCountOfCellsPerSplitNode) const
{
	if (gsoapProxy2_0_1 != nullptr) {
		gsoap_resqml2_0_1::resqml20__AbstractColumnLayerGridGeometry* geom = dynamic_cast<gsoap_resqml2_0_1::resqml20__AbstractColumnLayerGridGeometry*>(getPointGeometry2_0_1(0));
		if (geom == nullptr) {
			throw invalid_argument("There is no geometry on this grid.");
		}
		if (geom->SplitNodes == nullptr || geom->SplitNodes->Count == 0) {
			throw invalid_argument("There is no split node on this grid.");
		}

		readArrayNdOfIntegerValues(geom->SplitNodes->CellsPerSplitNode->CumulativeLength, cumulativeCountOfCellsPerSplitNode);
	}
	else {
		gsoap_eml2_3::resqml22__AbstractColumnLayerGridGeometry* geom = dynamic_cast<gsoap_eml2_3::resqml22__AbstractColumnLayerGridGeometry*>(getPointGeometry2_2(0));
		if (geom == nullptr) {
			throw invalid_argument("There is no geometry on this grid.");
		}
		if (geom->SplitNodePatch == nullptr || geom->SplitNodePatch->Count == 0) {
			throw invalid_argument("There is no split node on this grid.");
		}

		readArrayNdOfIntegerValues(geom->SplitNodePatch->CellsPerSplitNode->CumulativeLength, cumulativeCountOfCellsPerSplitNode);
	}
}

void AbstractColumnLayerGridRepresentation::getCellsPerSplitNode(uint64_t* cellsPerSplitNode) const
{
	if (gsoapProxy2_0_1 != nullptr) {
		gsoap_resqml2_0_1::resqml20__AbstractColumnLayerGridGeometry* geom = dynamic_cast<gsoap_resqml2_0_1::resqml20__AbstractColumnLayerGridGeometry*>(getPointGeometry2_0_1(0));
		if (geom == nullptr) {
			throw invalid_argument("There is no geometry on this grid.");
		}
		if (geom->SplitNodes == nullptr || geom->SplitNodes->Count == 0) {
			throw invalid_argument("There is no split node on this grid.");
		}

		readArrayNdOfIntegerValues(geom->SplitNodes->CellsPerSplitNode->Elements, cellsPerSplitNode);
	}
	else {
		gsoap_eml2_3::resqml22__AbstractColumnLayerGridGeometry* geom = dynamic_cast<gsoap_eml2_3::resqml22__AbstractColumnLayerGridGeometry*>(getPointGeometry2_2(0));
		if (geom == nullptr) {
			throw invalid_argument("There is no geometry on this grid.");
		}
		if (geom->SplitNodePatch == nullptr || geom->SplitNodePatch->Count == 0) {
			throw invalid_argument("There is no split node on this grid.");
		}

		readArrayNdOfIntegerValues(geom->SplitNodePatch->CellsPerSplitNode->Elements, cellsPerSplitNode);
	}
}

void AbstractColumnLayerGridRepresentation::setSplitNodePatch(uint64_t splitNodeCount, uint64_t* splitNodeParentNodeIndices,
	uint64_t* cumulativeCountOfCellsPerSplitNode, uint64_t* cellsPerSplitNode, EML2_NS::AbstractHdfProxy* proxy)
{
	if (proxy == nullptr) {
		proxy = getRepository()->getDefaultHdfProxy();
		if (proxy == nullptr) {
			throw std::invalid_argument("A (default) HDF Proxy must be provided.");
		}
	}

	if (gsoapProxy2_0_1 != nullptr) {
		gsoap_resqml2_0_1::resqml20__AbstractColumnLayerGridGeometry* geom = dynamic_cast<gsoap_resqml2_0_1::resqml20__AbstractColumnLayerGridGeometry*>(getPointGeometry2_0_1(0));
		if (geom == nullptr) {
			throw invalid_argument("There is no geometry on this grid.");
		}

		auto* patch = soap_new_resqml20__SplitNodePatch(gsoapProxy2_0_1->soap);
		patch->Count = splitNodeCount;

		auto* parentNodeIndicesArray = soap_new_resqml20__IntegerHdf5Array(gsoapProxy2_0_1->soap);
		parentNodeIndicesArray->Values = soap_new_eml20__Hdf5Dataset(gsoapProxy2_0_1->soap);
		parentNodeIndicesArray->Values->HdfProxy = proxy->newResqmlReference();
		parentNodeIndicesArray->Values->PathInHdfFile = getHdfGroup() + "/SplitNodeParentNodeIndices";
		parentNodeIndicesArray->NullValue = -1;
		patch->ParentNodeIndices = parentNodeIndicesArray;

		patch->CellsPerSplitNode = soap_new_resqml20__ResqmlJaggedArray(gsoapProxy2_0_1->soap);
		// Cumulative
		resqml20__IntegerHdf5Array* cumulativeLength = soap_new_resqml20__IntegerHdf5Array(gsoapProxy2_0_1->soap);
		patch->CellsPerSplitNode->CumulativeLength = cumulativeLength;
		cumulativeLength->NullValue = -1;
		cumulativeLength->Values = soap_new_eml20__Hdf5Dataset(gsoapProxy2_0_1->soap);
		cumulativeLength->Values->HdfProxy = proxy->newResqmlReference();
		cumulativeLength->Values->PathInHdfFile = getHdfGroup() + "/CellsPerSplitNode/" + EML2_NS::AbstractHdfProxy::CUMULATIVE_LENGTH_DS_NAME;
		// Elements
		resqml20__IntegerHdf5Array* elements = soap_new_resqml20__IntegerHdf5Array(gsoapProxy2_0_1->soap);
		patch->CellsPerSplitNode->Elements = elements;
		elements->NullValue = -1;
		elements->Values = soap_new_eml20__Hdf5Dataset(gsoapProxy2_0_1->soap);
		elements->Values->HdfProxy = proxy->newResqmlReference();
		elements->Values->PathInHdfFile = getHdfGroup() + "/CellsPerSplitNode/" + EML2_NS::AbstractHdfProxy::ELEMENTS_DS_NAME;

		geom->SplitNodes = patch;
	}
	else {
		gsoap_eml2_3::resqml22__AbstractColumnLayerGridGeometry* geom = dynamic_cast<gsoap_eml2_3::resqml22__AbstractColumnLayerGridGeometry*>(getPointGeometry2_2(0));
		if (geom == nullptr) {
			throw invalid_argument("There is no geometry on this grid.");
		}

		auto* patch = gsoap_eml2_3::soap_new_resqml22__SplitNodePatch(gsoapProxy2_3->soap);
		patch->Count = splitNodeCount;

		auto* parentNodeIndicesArray = gsoap_eml2_3::soap_new_eml23__IntegerExternalArray(gsoapProxy2_3->soap);
		parentNodeIndicesArray->Values = gsoap_eml2_3::soap_new_eml23__ExternalDataArray(gsoapProxy2_3->soap);
		parentNodeIndicesArray->Values->ExternalDataArrayPart.push_back(createExternalDataArrayPart(getHdfGroup() + "/SplitNodeParentNodeIndices", splitNodeCount, proxy));
		parentNodeIndicesArray->NullValue = -1;
		patch->ParentNodeIndices = parentNodeIndicesArray;

		patch->CellsPerSplitNode = gsoap_eml2_3::soap_new_eml23__JaggedArray(gsoapProxy2_3->soap);
		// cumulative XML
		auto* cumulativeDataset = gsoap_eml2_3::soap_new_eml23__IntegerExternalArray(gsoapProxy2_3->soap);
		cumulativeDataset->NullValue = -1;
		cumulativeDataset->Values = gsoap_eml2_3::soap_new_eml23__ExternalDataArray(gsoapProxy2_3->soap);
		cumulativeDataset->Values->ExternalDataArrayPart.push_back(
			createExternalDataArrayPart(getHdfGroup() + "/CellsPerSplitNode/" + EML2_NS::AbstractHdfProxy::CUMULATIVE_LENGTH_DS_NAME, splitNodeCount, proxy));
		patch->CellsPerSplitNode->CumulativeLength = cumulativeDataset;
		// element XML
		auto* elementDataset = gsoap_eml2_3::soap_new_eml23__IntegerExternalArray(gsoapProxy2_3->soap);
		elementDataset->NullValue = -1;
		elementDataset->Values = gsoap_eml2_3::soap_new_eml23__ExternalDataArray(gsoapProxy2_3->soap);
		elementDataset->Values->ExternalDataArrayPart.push_back(
			createExternalDataArrayPart(getHdfGroup() + "/CellsPerSplitNode/" + EML2_NS::AbstractHdfProxy::ELEMENTS_DS_NAME, cumulativeCountOfCellsPerSplitNode[splitNodeCount-1], proxy));
		patch->CellsPerSplitNode->Elements = elementDataset;

		geom->SplitNodePatch = patch;
	}

	// HDF
	proxy->writeArrayNdOfUInt64Values(getHdfGroup(), "SplitNodeParentNodeIndices", splitNodeParentNodeIndices, &splitNodeCount, 1);
	proxy->writeItemizedListOfList(getHdfGroup(), "CellsPerSplitNode",
		COMMON_NS::AbstractObject::numericalDatatypeEnum::UINT64, cumulativeCountOfCellsPerSplitNode, splitNodeCount,
		COMMON_NS::AbstractObject::numericalDatatypeEnum::UINT64, cellsPerSplitNode, cumulativeCountOfCellsPerSplitNode[splitNodeCount - 1]);
}
