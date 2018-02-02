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
/*-----------------------------------------------------------------------
Copyright F2I-CONSULTING, (2014-2017)

philippe.verney@f2i-consulting.com

This software is a computer program whose purpose is to access to data formatted using Energistics standards.

This software is governed by the CeCILL-B license under French law and
abiding by the rules of distribution of free software.  You can  use,
modify and/ or redistribute the software under the terms of the CeCILL-B
license as circulated by CEA, CNRS and INRIA at the following URL
"http://www.cecill.info".

As a counterpart to the access to the source code and  rights to copy,
modify and redistribute granted by the license, users are provided only
with a limited warranty  and the software's author,  the holder of the
economic rights,  and the successive licensors  have only  limited
liability.

In this respect, the user's attention is drawn to the risks associated
with loading,  using,  modifying and/or developing or reproducing the
software by the user in light of its specific status of free software,
that may mean  that it is complicated to manipulate,  and  that  also
therefore means  that it is reserved for developers  and  experienced
professionals having in-depth computer knowledge. Users are therefore
encouraged to load and test the software's suitability as regards their
requirements in conditions enabling the security of their systems and/or
data to be ensured and,  more generally, to use and operate it in the
same conditions as regards security.

The fact that you are presently reading this means that you have had
knowledge of the CeCILL-B license and that you accept its terms.
-----------------------------------------------------------------------*/
#include "resqml2/AbstractColumnLayerGridRepresentation.h"

#include <stdexcept>

#include "hdf5.h"

#include "resqml2_0_1/AbstractStratigraphicOrganizationInterpretation.h"
#include "common/AbstractHdfProxy.h"

using namespace gsoap_resqml2_0_1;
using namespace resqml2;
using namespace std;
using namespace epc;

unsigned int AbstractColumnLayerGridRepresentation::getKCellCount() const
{
	if (isPartial()) {
		throw logic_error("This method cannot be called on a partial object");
	}

	if (gsoapProxy2_0_1 != nullptr) {
		return isTruncated() ? static_cast<resqml2__AbstractTruncatedColumnLayerGridRepresentation*>(gsoapProxy2_0_1)->Nk : static_cast<resqml2__AbstractColumnLayerGridRepresentation*>(gsoapProxy2_0_1)->Nk;
	}
	else {
		throw logic_error("Only version 2_0_1 is implemented yet");
	}
}

void AbstractColumnLayerGridRepresentation::setKCellCount(const unsigned int & kCount)
{
	if (isPartial()) {
		throw logic_error("Partial object");
	}

	if (gsoapProxy2_0_1 != nullptr) {
		if (!isTruncated()) {
			static_cast<resqml2__AbstractColumnLayerGridRepresentation*>(gsoapProxy2_0_1)->Nk = kCount;
		}
		else {
			static_cast<resqml2__AbstractTruncatedColumnLayerGridRepresentation*>(gsoapProxy2_0_1)->Nk = kCount;
		}
	}
	else {
		throw logic_error("Only version 2_0_1 is implemented yet");
	}
}

void AbstractColumnLayerGridRepresentation::setIntervalAssociationWithStratigraphicOrganizationInterpretation(ULONG64 * stratiUnitIndices, const ULONG64 & nullValue, resqml2_0_1::AbstractStratigraphicOrganizationInterpretation * stratiOrgInterp)
{
	if (isTruncated()) {
		throw invalid_argument("A truncated grid cannot be linked to a strati columnumn in Resqml2");
	}

	// Backward rel
	if (!stratiOrgInterp->isAssociatedToGridRepresentation(this))
	{
		stratiOrgInterp->gridRepresentationSet.push_back(this);
	}

	// XML
	if (updateXml)
	{
		if (gsoapProxy2_0_1 != nullptr) {
			resqml2__AbstractColumnLayerGridRepresentation* rep = static_cast<resqml2__AbstractColumnLayerGridRepresentation*>(gsoapProxy2_0_1);
			rep->IntervalStratigraphicUnits = soap_new_resqml2__IntervalStratigraphicUnits(rep->soap, 1);
			rep->IntervalStratigraphicUnits->StratigraphicOrganization = stratiOrgInterp->newResqmlReference();

			resqml2__IntegerHdf5Array* xmlDataset = soap_new_resqml2__IntegerHdf5Array(rep->soap, 1);
			xmlDataset->NullValue = nullValue;
			xmlDataset->Values = soap_new_eml20__Hdf5Dataset(gsoapProxy2_0_1->soap, 1);
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
}

gsoap_resqml2_0_1::eml20__DataObjectReference* AbstractColumnLayerGridRepresentation::getStratigraphicOrganizationInterpretationDor() const
{
	gsoap_resqml2_0_1::eml20__DataObjectReference* result = resqml2::AbstractGridRepresentation::getStratigraphicOrganizationInterpretationDor();
	if (result != nullptr) {
		return result;
	}

	if (gsoapProxy2_0_1 != nullptr) {
		if (isTruncated()) {
			return nullptr;
		}

		resqml2__AbstractColumnLayerGridRepresentation* rep = static_cast<resqml2__AbstractColumnLayerGridRepresentation*>(gsoapProxy2_0_1);
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
		return !isTruncated() && static_cast<resqml2__AbstractColumnLayerGridRepresentation*>(gsoapProxy2_0_1)->IntervalStratigraphicUnits != nullptr;
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
		resqml2__AbstractColumnLayerGridRepresentation* rep = static_cast<resqml2__AbstractColumnLayerGridRepresentation*>(gsoapProxy2_0_1);

		if (rep->IntervalStratigraphicUnits->UnitIndices->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__IntegerHdf5Array)
		{
			hdfProxy->readArrayNdOfGSoapULong64Values(static_cast<resqml2__IntegerHdf5Array*>(rep->IntervalStratigraphicUnits->UnitIndices)->Values->PathInHdfFile, stratiUnitIndices);
			return static_cast<resqml2__IntegerHdf5Array*>(rep->IntervalStratigraphicUnits->UnitIndices)->NullValue;
		}

		throw logic_error("Not implemented yet.");
	}
	else {
		throw logic_error("Only version 2_0_1 is implemented yet");
	}
}

vector<Relationship> AbstractColumnLayerGridRepresentation::getAllEpcRelationships() const
{
	vector<Relationship> result = AbstractGridRepresentation::getAllEpcRelationships();

	// Strati unit
	if (!hasCellStratigraphicUnitIndices() && hasIntervalStratigraphicUnitIndices())
	{
		resqml2_0_1::AbstractStratigraphicOrganizationInterpretation* stratiOrg = getStratigraphicOrganizationInterpretation();
		Relationship relStrati(stratiOrg->getPartNameInEpcDocument(), "", stratiOrg->getUuid());
		relStrati.setDestinationObjectType();
		result.push_back(relStrati);
	}

	return result;
}

void AbstractColumnLayerGridRepresentation::importRelationshipSetFromEpc(common::EpcDocument* epcDoc)
{
	AbstractGridRepresentation::importRelationshipSetFromEpc(epcDoc);

	// Strati org backward relationships
	if (hasIntervalStratigraphicUnitIndices()) {
		gsoap_resqml2_0_1::eml20__DataObjectReference* dor = getStratigraphicOrganizationInterpretationDor();
		resqml2_0_1::AbstractStratigraphicOrganizationInterpretation* stratiOrg = getEpcDocument()->getResqmlAbstractObjectByUuid<resqml2_0_1::AbstractStratigraphicOrganizationInterpretation>(dor->UUID);
		if (stratiOrg == nullptr) { // partial transfer
			getEpcDocument()->createPartial(dor);
			stratiOrg = getEpcDocument()->getResqmlAbstractObjectByUuid<resqml2_0_1::AbstractStratigraphicOrganizationInterpretation>(dor->UUID);
		}
		if (stratiOrg == nullptr) {
			throw invalid_argument("The DOR looks invalid.");
		}
		updateXml = false;
		setIntervalAssociationWithStratigraphicOrganizationInterpretation(nullptr, 0, stratiOrg);
		updateXml = true;
	}
}

