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

#include <limits>
#include <stdexcept>

#include <hdf5.h>

#include "AbstractStratigraphicOrganizationInterpretation.h"
#include "../eml2/AbstractHdfProxy.h"

using namespace gsoap_resqml2_0_1;
using namespace RESQML2_NS;
using namespace std;

unsigned int AbstractColumnLayerGridRepresentation::getKCellCount() const
{
	if (isPartial()) {
		throw logic_error("This method cannot be called on a partial object");
	}

	const uint64_t kCellCount = gsoapProxy2_0_1 != nullptr
		? (isTruncated() ? static_cast<resqml20__AbstractTruncatedColumnLayerGridRepresentation*>(gsoapProxy2_0_1)->Nk : static_cast<resqml20__AbstractColumnLayerGridRepresentation*>(gsoapProxy2_0_1)->Nk)
		: (isTruncated() ? static_cast<gsoap_eml2_3::resqml22__AbstractTruncatedColumnLayerGridRepresentation*>(gsoapProxy2_3)->Nk : static_cast<gsoap_eml2_3::resqml22__AbstractColumnLayerGridRepresentation*>(gsoapProxy2_3)->Nk);
		
	if (kCellCount > (std::numeric_limits<unsigned int>::max)()) {
		throw range_error("There are too much cells against K dimension");
	}
	return static_cast<unsigned int>(kCellCount);
}

void AbstractColumnLayerGridRepresentation::setKCellCount(unsigned int kCount)
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

void AbstractColumnLayerGridRepresentation::setIntervalAssociationWithStratigraphicOrganizationInterpretation(int64_t * stratiUnitIndices, int64_t nullValue, RESQML2_NS::AbstractStratigraphicOrganizationInterpretation* stratiOrgInterp, EML2_NS::AbstractHdfProxy * hdfProxy)
{
	if (isTruncated()) {
		throw invalid_argument("A truncated grid cannot be linked to a strati column in Resqml2");
	}

	getRepository()->addRelationship(this, stratiOrgInterp);

	if (gsoapProxy2_0_1 != nullptr) {
		if (hdfProxy == nullptr) {
			hdfProxy = getRepository()->getDefaultHdfProxy();
			if (hdfProxy == nullptr) {
				throw std::invalid_argument("A (default) HDF Proxy must be provided.");
			}
		}
		getRepository()->addRelationship(this, hdfProxy);
		hsize_t dim = getKCellCount();
		hdfProxy->writeArrayNd(getHdfGroup(), "IntervalStratigraphicUnits", H5T_NATIVE_INT64, stratiUnitIndices, &dim, 1);

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
		elementDataset->CountPerValue = nullValue;
		elementDataset->Values = std::to_string(stratiUnitIndices[0]);
		for (hsize_t i = 1; i < getKCellCount(); ++i) {
			elementDataset->Values += " " + std::to_string(stratiUnitIndices[i]);
		}
		rep->IntervalStratigraphicUnits->UnitIndices->Elements = elementDataset;

		// cumulative XML
		gsoap_eml2_3::eml23__IntegerXmlArray* cumulativeDataset = gsoap_eml2_3::soap_new_eml23__IntegerXmlArray(rep->soap);
		cumulativeDataset->CountPerValue = 1;
		cumulativeDataset->Values = "1";
		for (hsize_t i = 1; i < getKCellCount(); ++i) {
			cumulativeDataset->Values += " " + std::to_string(i+1);
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

int64_t AbstractColumnLayerGridRepresentation::getIntervalStratigraphicUnitIndices(int64_t * stratiUnitIndices)
{
	if (isTruncated()) {
		throw invalid_argument("A truncated grid cannot be linked to a strati columnumn in Resqml v2.0");
	}
	if (!hasIntervalStratigraphicUnitIndices()) {
		throw invalid_argument("This grid has no Interval StratigraphicUnits information");
	}

	if (gsoapProxy2_0_1 != nullptr) {
		resqml20__AbstractColumnLayerGridRepresentation* rep = static_cast<resqml20__AbstractColumnLayerGridRepresentation*>(gsoapProxy2_0_1);

		if (rep->IntervalStratigraphicUnits->UnitIndices->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__IntegerHdf5Array) {
			eml20__Hdf5Dataset const * dataset = static_cast<resqml20__IntegerHdf5Array*>(rep->IntervalStratigraphicUnits->UnitIndices)->Values;
			getHdfProxyFromDataset(dataset)->readArrayNdOfInt64Values(dataset->PathInHdfFile, stratiUnitIndices);
			return static_cast<resqml20__IntegerHdf5Array*>(rep->IntervalStratigraphicUnits->UnitIndices)->NullValue;
		}

		throw logic_error("Not implemented yet.");
	}
	else if (gsoapProxy2_3 != nullptr) {
		auto rep = static_cast<gsoap_eml2_3::resqml22__AbstractColumnLayerGridRepresentation*>(gsoapProxy2_3);
		if (rep->IntervalStratigraphicUnits->UnitIndices->CumulativeLength->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__IntegerLatticeArray) {
			gsoap_eml2_3::eml23__IntegerLatticeArray* latticeArray = static_cast<gsoap_eml2_3::eml23__IntegerLatticeArray*>(rep->IntervalStratigraphicUnits->UnitIndices->CumulativeLength);
			if (latticeArray->StartValue == 1 && latticeArray->Offset.size() == 1 &&
				latticeArray->Offset[0]->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__IntegerConstantArray &&
				static_cast<gsoap_eml2_3::eml23__IntegerConstantArray*>(latticeArray->Offset[0])->Value == 1 &&
				static_cast<gsoap_eml2_3::eml23__IntegerConstantArray*>(latticeArray->Offset[0])->Count == getKCellCount() - 1) {
				auto const* daPart = static_cast<gsoap_eml2_3::eml23__IntegerExternalArray*>(rep->IntervalStratigraphicUnits->UnitIndices->Elements)->Values->ExternalDataArrayPart[0];
				getOrCreateHdfProxyFromDataArrayPart(daPart)->readArrayNdOfInt64Values(daPart->PathInExternalFile, stratiUnitIndices);
				return static_cast<gsoap_eml2_3::eml23__IntegerExternalArray*>(rep->IntervalStratigraphicUnits->UnitIndices->Elements)->NullValue;
			}
			throw logic_error("FESAPI does not support an association of more than one strati unit for a single K layer for now.");
		}
		else if (rep->IntervalStratigraphicUnits->UnitIndices->CumulativeLength->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__IntegerXmlArray) {
			std::unique_ptr<int64_t[]> cumulativeLength(new int64_t[getKCellCount()]);
			readArrayNdOfInt64Values(rep->IntervalStratigraphicUnits->UnitIndices->CumulativeLength, cumulativeLength.get());
			if (cumulativeLength[0] == 1 && cumulativeLength[getKCellCount() - 1] == getKCellCount()) {
				auto* elements = dynamic_cast<gsoap_eml2_3::eml23__AbstractIntegerArray*>(rep->IntervalStratigraphicUnits->UnitIndices->Elements);
				if (elements != nullptr) {
					return readArrayNdOfInt64Values(elements, stratiUnitIndices);
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
		if (!dor.isEmpty()) {
			convertDorIntoRel(dor);
		}
	}
}

gsoap_resqml2_0_1::resqml20__PillarShape AbstractColumnLayerGridRepresentation::getMostComplexPillarGeometry() const
{
	if (gsoapProxy2_0_1 != nullptr) {
		gsoap_resqml2_0_1::resqml20__PointGeometry* geom = getPointGeometry2_0_1(0);
		if (geom == nullptr) {
			throw invalid_argument("This grid has no point geoemtry.");
		}

		gsoap_resqml2_0_1::resqml20__AbstractColumnLayerGridGeometry* specializedGeom = dynamic_cast<gsoap_resqml2_0_1::resqml20__AbstractColumnLayerGridGeometry*>(geom);
		if (geom == nullptr) {
			throw invalid_argument("This grid has no AbstractColumnLayerGrid Geometry.");
		}

		return specializedGeom->PillarShape;
	}
	else if (gsoapProxy2_3 != nullptr) {
		gsoap_eml2_3::resqml22__PointGeometry* geom = getPointGeometry2_2(0);
		if (geom == nullptr) {
			throw invalid_argument("This grid has no point geoemtry.");
		}

		gsoap_eml2_3::resqml22__AbstractColumnLayerGridGeometry* specializedGeom = dynamic_cast<gsoap_eml2_3::resqml22__AbstractColumnLayerGridGeometry*>(geom);
		if (geom == nullptr) {
			throw invalid_argument("This grid has no AbstractColumnLayerGrid Geometry.");
		}

		return static_cast<gsoap_resqml2_0_1::resqml20__PillarShape>(specializedGeom->PillarShape);
	}
	else {
		throw logic_error("Not implemented yet");
	}
}
