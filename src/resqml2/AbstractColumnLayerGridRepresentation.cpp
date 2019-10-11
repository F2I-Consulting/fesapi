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
#include "resqml2/AbstractColumnLayerGridRepresentation.h"

#include <stdexcept>

#include "hdf5.h"

#include "resqml2_0_1/AbstractStratigraphicOrganizationInterpretation.h"
#include "common/AbstractHdfProxy.h"

using namespace gsoap_resqml2_0_1;
using namespace RESQML2_NS;
using namespace std;

unsigned int AbstractColumnLayerGridRepresentation::getKCellCount() const
{
	if (isPartial()) {
		throw logic_error("This method cannot be called on a partial object");
	}

	if (gsoapProxy2_0_1 != nullptr) {
		const ULONG64 result = isTruncated() ? static_cast<resqml20__AbstractTruncatedColumnLayerGridRepresentation*>(gsoapProxy2_0_1)->Nk : static_cast<resqml20__AbstractColumnLayerGridRepresentation*>(gsoapProxy2_0_1)->Nk;
		if (result > (std::numeric_limits<unsigned int>::max)()) {
			throw range_error("The K cell count is superior to unsigned int max");
		}
		return static_cast<unsigned int>(result);
	}
	else {
		throw logic_error("Only version 2_0_1 is implemented yet");
	}
}

void AbstractColumnLayerGridRepresentation::setKCellCount(unsigned int kCount)
{
	if (isPartial()) {
		throw logic_error("Partial object");
	}

	if (gsoapProxy2_0_1 != nullptr) {
		if (!isTruncated()) {
			static_cast<resqml20__AbstractColumnLayerGridRepresentation*>(gsoapProxy2_0_1)->Nk = kCount;
		}
		else {
			static_cast<resqml20__AbstractTruncatedColumnLayerGridRepresentation*>(gsoapProxy2_0_1)->Nk = kCount;
		}
	}
	else {
		throw logic_error("Only version 2_0_1 is implemented yet");
	}
}

void AbstractColumnLayerGridRepresentation::setIntervalAssociationWithStratigraphicOrganizationInterpretation(ULONG64 * stratiUnitIndices, ULONG64 nullValue, RESQML2_0_1_NS::AbstractStratigraphicOrganizationInterpretation * stratiOrgInterp, COMMON_NS::AbstractHdfProxy * hdfProxy)
{
	if (isTruncated()) {
		throw invalid_argument("A truncated grid cannot be linked to a strati columnumn in Resqml2");
	}

	if (hdfProxy == nullptr) {
		hdfProxy = getRepository()->getDefaultHdfProxy();
	}
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
		xmlDataset->Values->PathInHdfFile = "/RESQML/" + rep->uuid + "/IntervalStratigraphicUnits";
		rep->IntervalStratigraphicUnits->UnitIndices = xmlDataset;
	}
	else {
		throw logic_error("Only version 2_0_1 is implemented yet");
	}

	// ************ HDF *************
	hsize_t dim = getKCellCount();
	hdfProxy->writeArrayNd(getUuid(), "IntervalStratigraphicUnits", H5T_NATIVE_ULLONG, stratiUnitIndices, &dim, 1);
}

gsoap_resqml2_0_1::eml20__DataObjectReference const * AbstractColumnLayerGridRepresentation::getStratigraphicOrganizationInterpretationDor() const
{
	gsoap_resqml2_0_1::eml20__DataObjectReference const * result = RESQML2_NS::AbstractGridRepresentation::getStratigraphicOrganizationInterpretationDor();
	if (result != nullptr) {
		return result;
	}

	if (gsoapProxy2_0_1 != nullptr) {
		if (isTruncated()) {
			return nullptr;
		}

		resqml20__AbstractColumnLayerGridRepresentation* rep = static_cast<resqml20__AbstractColumnLayerGridRepresentation*>(gsoapProxy2_0_1);
		if (rep->IntervalStratigraphicUnits == nullptr) {
			return nullptr;
		}
		return rep->IntervalStratigraphicUnits->StratigraphicOrganization;
	}
	else {
		throw logic_error("Only version 2_0_1 is implemented yet");
	}
}

bool AbstractColumnLayerGridRepresentation::hasIntervalStratigraphicUnitIndices() const
{
	if (isPartial()) {
		throw logic_error("Partial object");
	}

	if (gsoapProxy2_0_1 != nullptr) {
		return !isTruncated() && static_cast<resqml20__AbstractColumnLayerGridRepresentation*>(gsoapProxy2_0_1)->IntervalStratigraphicUnits != nullptr;
	}
	else {
		throw logic_error("Only version 2_0_1 is implemented yet");
	}
}

ULONG64 AbstractColumnLayerGridRepresentation::getIntervalStratigraphicUnitIndices(ULONG64 * stratiUnitIndices)
{
	if (isTruncated()) {
		throw invalid_argument("A truncated grid cannot be linked to a strati columnumn in Resqml v2.0");
	}
	if (!hasIntervalStratigraphicUnitIndices()) {
		throw invalid_argument("This grid has no Interval StratigraphicUnits information");
	}

	if (gsoapProxy2_0_1 != nullptr) {
		resqml20__AbstractColumnLayerGridRepresentation* rep = static_cast<resqml20__AbstractColumnLayerGridRepresentation*>(gsoapProxy2_0_1);

		if (rep->IntervalStratigraphicUnits->UnitIndices->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__IntegerHdf5Array)
		{
			eml20__Hdf5Dataset const * dataset = static_cast<resqml20__IntegerHdf5Array*>(rep->IntervalStratigraphicUnits->UnitIndices)->Values;
			COMMON_NS::AbstractHdfProxy * hdfProxy = getHdfProxyFromDataset(dataset);
			hdfProxy->readArrayNdOfULongValues(dataset->PathInHdfFile, stratiUnitIndices);
			return static_cast<resqml20__IntegerHdf5Array*>(rep->IntervalStratigraphicUnits->UnitIndices)->NullValue;
		}

		throw logic_error("Not implemented yet.");
	}
	else {
		throw logic_error("Only version 2_0_1 is implemented for now");
	}
}

void AbstractColumnLayerGridRepresentation::loadTargetRelationships()
{
	AbstractGridRepresentation::loadTargetRelationships();

	// Strati org backward relationships
	if (hasIntervalStratigraphicUnitIndices()) {
		gsoap_resqml2_0_1::eml20__DataObjectReference const * dor = getStratigraphicOrganizationInterpretationDor();
		RESQML2_0_1_NS::AbstractStratigraphicOrganizationInterpretation* stratiOrg = getRepository()->getDataObjectByUuid<RESQML2_0_1_NS::AbstractStratigraphicOrganizationInterpretation>(dor->UUID);
		if (stratiOrg == nullptr) { // partial transfer
			getRepository()->createPartial(dor);
			stratiOrg = getRepository()->getDataObjectByUuid<RESQML2_0_1_NS::AbstractStratigraphicOrganizationInterpretation>(dor->UUID);
			if (stratiOrg == nullptr) {
				throw invalid_argument("The DOR looks invalid.");
			}
		}
		repository->addRelationship(this, stratiOrg);
	}
}

gsoap_resqml2_0_1::resqml20__PillarShape AbstractColumnLayerGridRepresentation::getMostComplexPillarGeometry() const
{
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
