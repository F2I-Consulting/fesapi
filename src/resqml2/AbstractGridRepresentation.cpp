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
#include "resqml2/AbstractGridRepresentation.h"

#include <stdexcept>
#include <limits>

#include "hdf5.h"

#include "resqml2_0_1/AbstractStratigraphicOrganizationInterpretation.h"
#include "common/AbstractHdfProxy.h"
#include "resqml2_0_1/UnstructuredGridRepresentation.h"
#include "resqml2_0_1/AbstractIjkGridRepresentation.h"

using namespace resqml2;
using namespace std;
using namespace epc;

const char* AbstractGridRepresentation::XML_TAG = "AbstractGridRepresentation";

vector<Relationship> AbstractGridRepresentation::getAllEpcRelationships() const
{
	vector<Relationship> result = AbstractRepresentation::getAllEpcRelationships();
	
	for (size_t i = 0; i < gridConnectionSetRepresentationSet.size(); ++i) {
		Relationship relRep(gridConnectionSetRepresentationSet[i]->getPartNameInEpcDocument(), "", gridConnectionSetRepresentationSet[i]->getUuid());
		relRep.setSourceObjectType();
		result.push_back(relRep);
	}

	for (size_t i = 0; i < blockedWellboreRepresentationSet.size(); ++i) {
		Relationship relBlockedWell(blockedWellboreRepresentationSet[i]->getPartNameInEpcDocument(), "", blockedWellboreRepresentationSet[i]->getUuid());
		relBlockedWell.setSourceObjectType();
		result.push_back(relBlockedWell);
	}

	if (getParentGrid() != nullptr) {
		Relationship relParent(getParentGrid()->getPartNameInEpcDocument(), "", getParentGrid()->getUuid());
		relParent.setDestinationObjectType();
		result.push_back(relParent);
	}

	unsigned int cildGridCount = getChildGridCount();
	for (unsigned int i = 0; i < cildGridCount; ++i) {
		AbstractGridRepresentation* childGrid = getChildGrid(i);
		Relationship relChild(childGrid->getPartNameInEpcDocument(), "", childGrid->getUuid());
		relChild.setSourceObjectType();
		result.push_back(relChild);
	}

	// Strati unit
	if (hasCellStratigraphicUnitIndices()) {
		resqml2_0_1::AbstractStratigraphicOrganizationInterpretation* stratiOrg = getStratigraphicOrganizationInterpretation();
		Relationship relStrati(stratiOrg->getPartNameInEpcDocument(), "", stratiOrg->getUuid());
		relStrati.setDestinationObjectType();
		result.push_back(relStrati);
	}

	return result;
}

resqml2::GridConnectionSetRepresentation* AbstractGridRepresentation::getGridConnectionSetRepresentation(const unsigned int & index) const
{
	if (gridConnectionSetRepresentationSet.size() > index) {
		return gridConnectionSetRepresentationSet[index];
	}
	
	throw std::out_of_range("No GridConnectionSetRepresentation at this index.");
}

gsoap_resqml2_0_1::resqml2__AbstractParentWindow* AbstractGridRepresentation::getParentWindow2_0_1() const
{
	if (gsoapProxy2_0_1 != nullptr) {
		return static_cast<gsoap_resqml2_0_1::resqml2__AbstractGridRepresentation*>(gsoapProxy2_0_1)->ParentWindow;
	}

	return nullptr;
}

gsoap_resqml2_0_1::eml20__DataObjectReference* AbstractGridRepresentation::getParentGridDor() const
{
	if (gsoapProxy2_0_1 != nullptr) {
		gsoap_resqml2_0_1::resqml2__AbstractParentWindow* parentWindow = getParentWindow2_0_1();

		if (parentWindow != nullptr) {
			if (parentWindow->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__IjkParentWindow) {
				gsoap_resqml2_0_1::resqml2__IjkParentWindow* pw = static_cast<gsoap_resqml2_0_1::resqml2__IjkParentWindow*>(parentWindow);
				return pw->ParentGrid;
			}
			else if (parentWindow->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__ColumnLayerParentWindow) {
				gsoap_resqml2_0_1::resqml2__ColumnLayerParentWindow* pw = static_cast<gsoap_resqml2_0_1::resqml2__ColumnLayerParentWindow*>(parentWindow);
				return pw->ParentGrid;
			}
			else if (parentWindow->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__CellParentWindow) {
				gsoap_resqml2_0_1::resqml2__CellParentWindow* pw = static_cast<gsoap_resqml2_0_1::resqml2__CellParentWindow*>(parentWindow);
				return pw->ParentGrid;
			}
			else {
				throw logic_error("Unexpected parent window type.");
			}
		}
	}
	else {
		throw logic_error("Not implemented yet");
	}

	return nullptr;
}

std::string AbstractGridRepresentation::getParentGridUuid() const
{
	gsoap_resqml2_0_1::eml20__DataObjectReference* dor = getParentGridDor();
	return dor == nullptr ? string() : dor->UUID;
}

AbstractGridRepresentation* AbstractGridRepresentation::getParentGrid() const
{
	const string parentGridUuid = getParentGridUuid();

	if (!parentGridUuid.empty()) {
		return static_cast<AbstractGridRepresentation*>(getEpcDocument()->getResqmlAbstractObjectByUuid(parentGridUuid));
	}
	
	return nullptr;
}

gsoap_resqml2_0_1::resqml2__Regrid* AbstractGridRepresentation::createRegrid(const unsigned int & indexRegridStart, unsigned int * childCellCountPerInterval, unsigned int * parentCellCountPerInterval, const unsigned int & intervalCount, double * childCellWeights,
	const std::string & dimension, bool forceConstantCellCountPerInterval)
{
	gsoap_resqml2_0_1::resqml2__Regrid* regrid = gsoap_resqml2_0_1::soap_new_resqml2__Regrid(gsoapProxy2_0_1->soap, 1);
	regrid->InitialIndexOnParentGrid = indexRegridStart;
	regrid->Intervals = gsoap_resqml2_0_1::soap_new_resqml2__Intervals(gsoapProxy2_0_1->soap, 1);
	regrid->Intervals->IntervalCount = intervalCount;
	
	if (intervalCount == 0) {
		throw invalid_argument("Cannot regrid an empty list of intervals.");
	}
	else if (intervalCount == 1 || forceConstantCellCountPerInterval) {
		gsoap_resqml2_0_1::resqml2__IntegerConstantArray* xmlChildCountPerInterval = gsoap_resqml2_0_1::soap_new_resqml2__IntegerConstantArray(gsoapProxy2_0_1->soap, 1);
		xmlChildCountPerInterval->Value = *childCellCountPerInterval;
		xmlChildCountPerInterval->Count = intervalCount;
		regrid->Intervals->ChildCountPerInterval = xmlChildCountPerInterval;

		gsoap_resqml2_0_1::resqml2__IntegerConstantArray* xmlParentCountPerInterval = gsoap_resqml2_0_1::soap_new_resqml2__IntegerConstantArray(gsoapProxy2_0_1->soap, 1);
		xmlParentCountPerInterval->Value = *parentCellCountPerInterval;
		xmlParentCountPerInterval->Count = intervalCount;
		regrid->Intervals->ParentCountPerInterval = xmlParentCountPerInterval;
	}
	else if (hdfProxy != nullptr) {
		gsoap_resqml2_0_1::resqml2__IntegerHdf5Array* hdf5ChildCountPerInterval = gsoap_resqml2_0_1::soap_new_resqml2__IntegerHdf5Array(gsoapProxy2_0_1->soap, 1);
		regrid->Intervals->ChildCountPerInterval = hdf5ChildCountPerInterval;
		hdf5ChildCountPerInterval->NullValue = (numeric_limits<unsigned int>::max)();
		hdf5ChildCountPerInterval->Values = gsoap_resqml2_0_1::soap_new_eml20__Hdf5Dataset(gsoapProxy2_0_1->soap, 1);
		hdf5ChildCountPerInterval->Values->HdfProxy = hdfProxy->newResqmlReference();
		hdf5ChildCountPerInterval->Values->PathInHdfFile = "/RESQML/" + gsoapProxy2_0_1->uuid + "/ParentWindow_" + dimension + "Regrid_ChildCountPerInterval";

		gsoap_resqml2_0_1::resqml2__IntegerHdf5Array* hdf5ParentCountPerInterval = gsoap_resqml2_0_1::soap_new_resqml2__IntegerHdf5Array(gsoapProxy2_0_1->soap, 1);
		regrid->Intervals->ParentCountPerInterval = hdf5ParentCountPerInterval;
		hdf5ParentCountPerInterval->NullValue = (numeric_limits<unsigned int>::max)();
		hdf5ParentCountPerInterval->Values = gsoap_resqml2_0_1::soap_new_eml20__Hdf5Dataset(gsoapProxy2_0_1->soap, 1);
		hdf5ParentCountPerInterval->Values->HdfProxy = hdfProxy->newResqmlReference();
		hdf5ParentCountPerInterval->Values->PathInHdfFile = "/RESQML/" + gsoapProxy2_0_1->uuid + "/ParentWindow_" + dimension + "Regrid_ParentCountPerInterval";
		
		// HDF
		hsize_t numValues = intervalCount;
		hdfProxy->writeArrayNd(gsoapProxy2_0_1->uuid, "ParentWindow_" + dimension + "Regrid_ChildCountPerInterval", H5T_NATIVE_UINT, childCellCountPerInterval, &numValues, 1);
		hdfProxy->writeArrayNd(gsoapProxy2_0_1->uuid, "ParentWindow_" + dimension + "Regrid_ParentCountPerInterval", H5T_NATIVE_UINT, parentCellCountPerInterval, &numValues, 1);
	}
	else {
		throw invalid_argument("The HDF proxy is missing.");
	}
	
	if (childCellWeights != nullptr) {
		gsoap_resqml2_0_1::resqml2__DoubleHdf5Array* hdf5ChildCellWeights = gsoap_resqml2_0_1::soap_new_resqml2__DoubleHdf5Array(gsoapProxy2_0_1->soap, 1);
		regrid->Intervals->ChildCellWeights = hdf5ChildCellWeights;
		hdf5ChildCellWeights->Values = gsoap_resqml2_0_1::soap_new_eml20__Hdf5Dataset(gsoapProxy2_0_1->soap, 1);
		hdf5ChildCellWeights->Values->HdfProxy = hdfProxy->newResqmlReference();
		hdf5ChildCellWeights->Values->PathInHdfFile = "/RESQML/" + gsoapProxy2_0_1->uuid + "/ParentWindow_" + dimension + "Regrid_ChildCellWeights";
		
		// HDF
		hsize_t numValues = 0;
		for (unsigned int i = 0; i < intervalCount; ++i) {
			numValues += childCellCountPerInterval[i];
		}
		hdfProxy->writeArrayNdOfDoubleValues(gsoapProxy2_0_1->uuid, "ParentWindow_" + dimension + "Regrid_ChildCellWeights", childCellWeights, &numValues, 1);
	}

	return regrid;
}

void AbstractGridRepresentation::setParentWindow(ULONG64 * cellIndices, const ULONG64 & cellIndexCount, resqml2_0_1::UnstructuredGridRepresentation* parentGrid)
{
	if (gsoapProxy2_0_1 != nullptr) {
		gsoap_resqml2_0_1::resqml2__AbstractGridRepresentation* rep = static_cast<gsoap_resqml2_0_1::resqml2__AbstractGridRepresentation*>(gsoapProxy2_0_1);

		gsoap_resqml2_0_1::resqml2__CellParentWindow* cpw = gsoap_resqml2_0_1::soap_new_resqml2__CellParentWindow(rep->soap, 1);
		rep->ParentWindow = cpw;

		cpw->ParentGrid = parentGrid->newResqmlReference();
		if (cellIndexCount > 1 && hdfProxy != nullptr) {
			gsoap_resqml2_0_1::resqml2__IntegerHdf5Array* hdf5CellIndices = gsoap_resqml2_0_1::soap_new_resqml2__IntegerHdf5Array(rep->soap, 1);
			cpw->CellIndices = hdf5CellIndices;

			hdf5CellIndices->NullValue = (numeric_limits<ULONG64>::max)();
			hdf5CellIndices->Values = gsoap_resqml2_0_1::soap_new_eml20__Hdf5Dataset(rep->soap, 1);
			hdf5CellIndices->Values->HdfProxy = hdfProxy->newResqmlReference();
			hdf5CellIndices->Values->PathInHdfFile = "/RESQML/" + gsoapProxy2_0_1->uuid + "/ParentWindow_CellIndices";
		
			// HDF
			hsize_t numValues = cellIndexCount;
			hdfProxy->writeArrayNdOfGSoapULong64Values(gsoapProxy2_0_1->uuid, "ParentWindow_CellIndices", cellIndices, &numValues, 1);
		}
		else if (cellIndexCount == 1) {
			gsoap_resqml2_0_1::resqml2__IntegerConstantArray* xmlCellIndices = gsoap_resqml2_0_1::soap_new_resqml2__IntegerConstantArray(rep->soap, 1);
			xmlCellIndices->Value = *cellIndices;
			xmlCellIndices->Count = 1;
			cpw->CellIndices = xmlCellIndices;
		}
	}
	else {
		throw logic_error("Not implemented yet");
	}

	if (cellIndexCount == 0) {
		throw invalid_argument("Cannot regrid an empty list of cells.");
	}
	if (hdfProxy == nullptr) {
		throw invalid_argument("The HDF proxy is missing.");
	}
	
	// LGR backward relationships
	parentGrid->childGridSet.push_back(this);
}

void AbstractGridRepresentation::setParentWindow(unsigned int * columnIndices, const unsigned int & columnIndexCount,
			const unsigned int & kLayerIndexRegridStart,
			unsigned int * childCellCountPerInterval, unsigned int * parentCellCountPerInterval,  const unsigned int & intervalCount,
			AbstractColumnLayerGridRepresentation* parentGrid, double * childCellWeights)
{
	if (gsoapProxy2_0_1 != nullptr) {
		gsoap_resqml2_0_1::resqml2__AbstractGridRepresentation* rep = static_cast<gsoap_resqml2_0_1::resqml2__AbstractGridRepresentation*>(gsoapProxy2_0_1);

		gsoap_resqml2_0_1::resqml2__ColumnLayerParentWindow* clpw = gsoap_resqml2_0_1::soap_new_resqml2__ColumnLayerParentWindow(rep->soap, 1);
		rep->ParentWindow = clpw;

		clpw->ParentGrid = parentGrid->newResqmlReference();

		// COLUMN INDICES
		if (columnIndexCount > 1 && hdfProxy != nullptr)
		{
			gsoap_resqml2_0_1::resqml2__IntegerHdf5Array* hdf5ColumnIndices = gsoap_resqml2_0_1::soap_new_resqml2__IntegerHdf5Array(rep->soap, 1);
			clpw->ColumnIndices = hdf5ColumnIndices;

			hdf5ColumnIndices->NullValue = (numeric_limits<unsigned int>::max)();
			hdf5ColumnIndices->Values = gsoap_resqml2_0_1::soap_new_eml20__Hdf5Dataset(rep->soap, 1);
			hdf5ColumnIndices->Values->HdfProxy = hdfProxy->newResqmlReference();
			hdf5ColumnIndices->Values->PathInHdfFile = "/RESQML/" + gsoapProxy2_0_1->uuid + "/ParentWindow_ColumnIndices";

			// HDF
			hsize_t numValues = columnIndexCount;
			hdfProxy->writeArrayNd(gsoapProxy2_0_1->uuid, "ParentWindow_ColumnIndices", H5T_NATIVE_UINT, columnIndices, &numValues, 1);
		}
		else if (columnIndexCount == 1)
		{
			gsoap_resqml2_0_1::resqml2__IntegerConstantArray* xmlColumnIndices = gsoap_resqml2_0_1::soap_new_resqml2__IntegerConstantArray(rep->soap, 1);
			xmlColumnIndices->Value = *columnIndices;
			xmlColumnIndices->Count = 1;
			clpw->ColumnIndices = xmlColumnIndices;
		}

		// K Regrid
		clpw->KRegrid = createRegrid(kLayerIndexRegridStart, childCellCountPerInterval, parentCellCountPerInterval, intervalCount, childCellWeights, "K");
	}
	else {
		throw logic_error("Not implemented yet");
	}

	if (columnIndexCount == 0) {
		throw invalid_argument("Cannot regrid an empty list of columns.");
	}
	if (hdfProxy == nullptr) {
		throw invalid_argument("The HDF proxy is missing.");
	}

	// LGR backward relationships
	parentGrid->childGridSet.push_back(this);
}

void AbstractGridRepresentation::setParentWindow(
	const unsigned int & iCellIndexRegridStart, unsigned int * childCellCountPerIInterval, unsigned int * parentCellCountPerIInterval,  const unsigned int & iIntervalCount,
	const unsigned int & jCellIndexRegridStart, unsigned int * childCellCountPerJInterval, unsigned int * parentCellCountPerJInterval,  const unsigned int & jIntervalCount,
	const unsigned int & kCellIndexRegridStart, unsigned int * childCellCountPerKInterval, unsigned int * parentCellCountPerKInterval,  const unsigned int & kIntervalCount,
	resqml2_0_1::AbstractIjkGridRepresentation* parentGrid, double * iChildCellWeights, double * jChildCellWeights, double * kChildCellWeights)
{
	if (gsoapProxy2_0_1 != nullptr) {
		gsoap_resqml2_0_1::resqml2__AbstractGridRepresentation* rep = static_cast<gsoap_resqml2_0_1::resqml2__AbstractGridRepresentation*>(gsoapProxy2_0_1);

		gsoap_resqml2_0_1::resqml2__IjkParentWindow* ijkpw = gsoap_resqml2_0_1::soap_new_resqml2__IjkParentWindow(rep->soap, 1);
		rep->ParentWindow = ijkpw;

		ijkpw->ParentGrid = parentGrid->newResqmlReference();
	
		// Regrids
		ijkpw->IRegrid = createRegrid(iCellIndexRegridStart, childCellCountPerIInterval, parentCellCountPerIInterval, iIntervalCount, iChildCellWeights, "I");
		ijkpw->JRegrid = createRegrid(jCellIndexRegridStart, childCellCountPerJInterval, parentCellCountPerJInterval, jIntervalCount, jChildCellWeights, "J");
		ijkpw->KRegrid = createRegrid(kCellIndexRegridStart, childCellCountPerKInterval, parentCellCountPerKInterval, kIntervalCount, kChildCellWeights, "K");
	}
	else {
		throw logic_error("Not implemented yet");
	}

	// LGR backward relationships
	parentGrid->childGridSet.push_back(this);
}

void AbstractGridRepresentation::setParentWindow(
	const unsigned int & iCellIndexRegridStart, unsigned int constantChildCellCountPerIInterval, unsigned int constantParentCellCountPerIInterval, const unsigned int & iIntervalCount,
	const unsigned int & jCellIndexRegridStart, unsigned int constantChildCellCountPerJInterval, unsigned int constantParentCellCountPerJInterval, const unsigned int & jIntervalCount,
	const unsigned int & kCellIndexRegridStart, unsigned int constantChildCellCountPerKInterval, unsigned int constantParentCellCountPerKInterval, const unsigned int & kIntervalCount,
	resqml2_0_1::AbstractIjkGridRepresentation* parentGrid, double * iChildCellWeights, double * jChildCellWeights, double * kChildCellWeights)
{
	if (gsoapProxy2_0_1 != nullptr) {
		gsoap_resqml2_0_1::resqml2__AbstractGridRepresentation* rep = static_cast<gsoap_resqml2_0_1::resqml2__AbstractGridRepresentation*>(gsoapProxy2_0_1);

		gsoap_resqml2_0_1::resqml2__IjkParentWindow* ijkpw = gsoap_resqml2_0_1::soap_new_resqml2__IjkParentWindow(rep->soap, 1);
		rep->ParentWindow = ijkpw;

		ijkpw->ParentGrid = parentGrid->newResqmlReference();

		// Regrids
		ijkpw->IRegrid = createRegrid(iCellIndexRegridStart, &constantChildCellCountPerIInterval, &constantParentCellCountPerIInterval, iIntervalCount, iChildCellWeights, "I", true);
		ijkpw->JRegrid = createRegrid(jCellIndexRegridStart, &constantChildCellCountPerJInterval, &constantParentCellCountPerIInterval, jIntervalCount, jChildCellWeights, "J", true);
		ijkpw->KRegrid = createRegrid(kCellIndexRegridStart, &constantChildCellCountPerKInterval, &constantParentCellCountPerIInterval, kIntervalCount, kChildCellWeights, "K", true);
	}
	else {
		throw logic_error("Not implemented yet");
	}

	// LGR backward relationships
	parentGrid->childGridSet.push_back(this);
}

void AbstractGridRepresentation::setParentWindow(
	const unsigned int & iCellIndexRegridStart, unsigned int iChildCellCount, unsigned int iParentCellCount,
	const unsigned int & jCellIndexRegridStart, unsigned int jChildCellCount, unsigned int jParentCellCount,
	const unsigned int & kCellIndexRegridStart, unsigned int kChildCellCount, unsigned int kParentCellCount,
	resqml2_0_1::AbstractIjkGridRepresentation* parentGrid, double * iChildCellWeights, double * jChildCellWeights, double * kChildCellWeights)
{
	setParentWindow(
		iCellIndexRegridStart, &iChildCellCount, &iParentCellCount, 1,
		jCellIndexRegridStart, &jChildCellCount, &jParentCellCount, 1,
		kCellIndexRegridStart, &kChildCellCount, &kParentCellCount, 1,
		parentGrid, iChildCellWeights, jChildCellWeights, kChildCellWeights);
}

void AbstractGridRepresentation::setForcedNonRegridedParentCell(ULONG64 * cellIndices, const ULONG64 & cellIndexCount)
{
	if (gsoapProxy2_0_1 != nullptr) {
		gsoap_resqml2_0_1::resqml2__AbstractParentWindow* parentWindow = getParentWindow2_0_1();

		if (parentWindow != nullptr)
		{
			gsoap_resqml2_0_1::resqml2__AbstractIntegerArray* xmlCellIndices = nullptr;
			if (cellIndexCount > 1 && hdfProxy != nullptr)
			{
				xmlCellIndices = gsoap_resqml2_0_1::soap_new_resqml2__IntegerHdf5Array(parentWindow->soap, 1);
				static_cast<gsoap_resqml2_0_1::resqml2__IntegerHdf5Array*>(xmlCellIndices)->NullValue = (numeric_limits<ULONG64>::max)();
				static_cast<gsoap_resqml2_0_1::resqml2__IntegerHdf5Array*>(xmlCellIndices)->Values = gsoap_resqml2_0_1::soap_new_eml20__Hdf5Dataset(parentWindow->soap, 1);
				static_cast<gsoap_resqml2_0_1::resqml2__IntegerHdf5Array*>(xmlCellIndices)->Values->HdfProxy = hdfProxy->newResqmlReference();
				static_cast<gsoap_resqml2_0_1::resqml2__IntegerHdf5Array*>(xmlCellIndices)->Values->PathInHdfFile = "/RESQML/" + gsoapProxy2_0_1->uuid + "/ParentWindow_CellIndices";
			
				// HDF
				hsize_t numValues = cellIndexCount;
				hdfProxy->writeArrayNdOfGSoapULong64Values(gsoapProxy2_0_1->uuid, "ParentWindow_CellIndices", cellIndices, &numValues, 1);
			}
			else if (cellIndexCount == 1)
			{
				xmlCellIndices = gsoap_resqml2_0_1::soap_new_resqml2__IntegerConstantArray(parentWindow->soap, 1);
				static_cast<gsoap_resqml2_0_1::resqml2__IntegerConstantArray*>(xmlCellIndices)->Value = *cellIndices;
				static_cast<gsoap_resqml2_0_1::resqml2__IntegerConstantArray*>(xmlCellIndices)->Count = 1;
			}
			else if (cellIndexCount == 0)
				throw invalid_argument("Cannot force an empty list of cells.");
			else
				throw invalid_argument("The HDF proxy is missing.");

			if (parentWindow->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__IjkParentWindow)
			{
				static_cast<gsoap_resqml2_0_1::resqml2__IjkParentWindow*>(parentWindow)->OmitParentCells = xmlCellIndices;
			}
			else if (parentWindow->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__ColumnLayerParentWindow)
			{
				static_cast<gsoap_resqml2_0_1::resqml2__ColumnLayerParentWindow*>(parentWindow)->OmitParentCells = xmlCellIndices;
			}
			else
				throw invalid_argument("You can only force parent cell on a ijk or column layer parent window.");
		}
		else {
			throw invalid_argument("You cannot force parent cell without a parent window. Set the parent window first please.");
		}
	}
	else {
		throw logic_error("Not implemented yet");
	}
}

bool AbstractGridRepresentation::hasForcedNonRegridedParentCell() const
{
	if (gsoapProxy2_0_1 != nullptr) {
		gsoap_resqml2_0_1::resqml2__AbstractParentWindow* parentWindow = getParentWindow2_0_1();

		if (parentWindow != nullptr) {
			if (parentWindow->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__IjkParentWindow) {
				return static_cast<gsoap_resqml2_0_1::resqml2__IjkParentWindow*>(parentWindow)->OmitParentCells != nullptr;
			}
			else if (parentWindow->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__ColumnLayerParentWindow) {
				return static_cast<gsoap_resqml2_0_1::resqml2__ColumnLayerParentWindow*>(parentWindow)->OmitParentCells != nullptr;
			}

			return false;
		}
		else {
			throw invalid_argument("There is no parent window on this grid.");
		}
	}
	else {
		throw logic_error("Not implemented yet");
	}
}

void AbstractGridRepresentation::setCellOverlap(const ULONG64 & parentChildCellPairCount, ULONG64 * parentChildCellPair,
	const gsoap_resqml2_0_1::eml20__VolumeUom & volumeUom, double * overlapVolumes)
{
	if (gsoapProxy2_0_1 != nullptr) {
		gsoap_resqml2_0_1::resqml2__AbstractParentWindow* parentWindow = getParentWindow2_0_1();

		if (parentWindow != nullptr)
		{
			if (parentChildCellPairCount > 0 && hdfProxy != nullptr)
			{
				parentWindow->CellOverlap = gsoap_resqml2_0_1::soap_new_resqml2__CellOverlap(gsoapProxy2_0_1->soap, 1);

				gsoap_resqml2_0_1::resqml2__IntegerHdf5Array* hdf5CellPairs = gsoap_resqml2_0_1::soap_new_resqml2__IntegerHdf5Array(parentWindow->soap, 1);
				parentWindow->CellOverlap->__CellOverlap_sequence = gsoap_resqml2_0_1::soap_new___resqml2__CellOverlap_sequence(parentWindow->soap, 1);
				parentWindow->CellOverlap->__CellOverlap_sequence->Count = parentChildCellPairCount;
				parentWindow->CellOverlap->__CellOverlap_sequence->ParentChildCellPairs = hdf5CellPairs;
				hdf5CellPairs->NullValue = (numeric_limits<ULONG64>::max)();
				hdf5CellPairs->Values = gsoap_resqml2_0_1::soap_new_eml20__Hdf5Dataset(parentWindow->soap, 1);
				hdf5CellPairs->Values->HdfProxy = hdfProxy->newResqmlReference();
				hdf5CellPairs->Values->PathInHdfFile = "/RESQML/" + gsoapProxy2_0_1->uuid + "/ParentWindow_CellOverlap";
		
				// HDF
				hsize_t numValues[] = {parentChildCellPairCount, 2};
				hdfProxy->writeArrayNdOfGSoapULong64Values(gsoapProxy2_0_1->uuid, "ParentWindow_CellOverlap", parentChildCellPair, numValues, 2);
			}
			else if (parentChildCellPairCount == 0)
				throw invalid_argument("Cannot give cell overlap information with an empty list of cell pairs.");
			else
				throw invalid_argument("The HDF proxy is missing.");

			if (overlapVolumes != nullptr)
			{
				parentWindow->CellOverlap->__CellOverlap_sequence->OverlapVolume = gsoap_resqml2_0_1::soap_new_resqml2__OverlapVolume(parentWindow->soap, 1);
				parentWindow->CellOverlap->__CellOverlap_sequence->OverlapVolume->__OverlapVolume_sequence = gsoap_resqml2_0_1::soap_new___resqml2__OverlapVolume_sequence(parentWindow->soap, 1);
				parentWindow->CellOverlap->__CellOverlap_sequence->OverlapVolume->__OverlapVolume_sequence->VolumeUom = volumeUom;

				gsoap_resqml2_0_1::resqml2__DoubleHdf5Array* hdf5OverlapVolume = gsoap_resqml2_0_1::soap_new_resqml2__DoubleHdf5Array(parentWindow->soap, 1);
				parentWindow->CellOverlap->__CellOverlap_sequence->OverlapVolume->__OverlapVolume_sequence->OverlapVolumes = hdf5OverlapVolume;
				hdf5OverlapVolume->Values = gsoap_resqml2_0_1::soap_new_eml20__Hdf5Dataset(parentWindow->soap, 1);
				hdf5OverlapVolume->Values->HdfProxy = hdfProxy->newResqmlReference();
				hdf5OverlapVolume->Values->PathInHdfFile = "/RESQML/" + gsoapProxy2_0_1->uuid + "/ParentWindow_OverlapVolume";
		
				// HDF
				hsize_t numValues = parentChildCellPairCount;
				hdfProxy->writeArrayNdOfDoubleValues(gsoapProxy2_0_1->uuid, "ParentWindow_OverlapVolume", overlapVolumes, &numValues, 1);
			}
		}
		else {
			throw invalid_argument("You cannot give cell overlap information without a parent window. Set the parent window first please.");
		}
	}
	else {
		throw logic_error("Not implemented yet");
	}
}

LONG64 AbstractGridRepresentation::getParentCellIndexCount() const
{
	if (gsoapProxy2_0_1 != nullptr) {
		gsoap_resqml2_0_1::resqml2__AbstractParentWindow* parentWindow = getParentWindow2_0_1();

		if (parentWindow != nullptr)
		{
			if (parentWindow->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__CellParentWindow)
			{
				gsoap_resqml2_0_1::resqml2__CellParentWindow* cpw = static_cast<gsoap_resqml2_0_1::resqml2__CellParentWindow*>(parentWindow);
				if (cpw->CellIndices->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__IntegerHdf5Array)
				{
					return hdfProxy->getElementCount(static_cast<gsoap_resqml2_0_1::resqml2__IntegerHdf5Array*>(cpw->CellIndices)->Values->PathInHdfFile);
				}
				else
					throw invalid_argument("This list of cells can only be stored in HDF5 file.");
			}
			else
				throw invalid_argument("This information is only avaialble for cell parent window.");
		}
		else {
			throw invalid_argument("There is no parent window on this grid.");
		}
	}
	else {
		throw logic_error("Not implemented yet");
	}
}

void AbstractGridRepresentation::getParentCellIndices(ULONG64 * parentCellIndices) const
{
	if (gsoapProxy2_0_1 != nullptr) {
		gsoap_resqml2_0_1::resqml2__AbstractParentWindow* parentWindow = getParentWindow2_0_1();

		if (parentWindow != nullptr)
		{
			if (parentWindow->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__CellParentWindow)
			{
				gsoap_resqml2_0_1::resqml2__CellParentWindow* cpw = static_cast<gsoap_resqml2_0_1::resqml2__CellParentWindow*>(parentWindow);
				if (cpw->CellIndices->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__IntegerHdf5Array) {
					hdfProxy->readArrayNdOfGSoapULong64Values(static_cast<gsoap_resqml2_0_1::resqml2__IntegerHdf5Array*>(cpw->CellIndices)->Values->PathInHdfFile, parentCellIndices);
				}
				else
					throw invalid_argument("This list of cells can only be stored in HDF5 file.");
			}
			else
				throw invalid_argument("This information is only avaialble for cell parent window.");
		}
		else {
			throw invalid_argument("There is no parent window on this grid.");
		}
	}
	else {
		throw logic_error("Not implemented yet");
	}
}

LONG64 AbstractGridRepresentation::getParentColumnIndexCount() const
{
	if (gsoapProxy2_0_1 != nullptr) {
		gsoap_resqml2_0_1::resqml2__AbstractParentWindow* parentWindow = getParentWindow2_0_1();

		if (parentWindow != nullptr)
		{
			if (parentWindow->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__ColumnLayerParentWindow)
			{
				gsoap_resqml2_0_1::resqml2__ColumnLayerParentWindow* clpw = static_cast<gsoap_resqml2_0_1::resqml2__ColumnLayerParentWindow*>(parentWindow);
				if (clpw->ColumnIndices->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__IntegerHdf5Array) {
					return hdfProxy->getElementCount(static_cast<gsoap_resqml2_0_1::resqml2__IntegerHdf5Array*>(clpw->ColumnIndices)->Values->PathInHdfFile);
				}
				else {
					throw invalid_argument("This list of columns can only be stored in HDF5 file.");
				}
			}
			else {
				throw invalid_argument("This information is only avaialble for column layer parent window.");
			}
		}
		else {
			throw invalid_argument("There is no parent window on this grid.");
		}
	}
	else {
		throw logic_error("Not implemented yet");
	}
}

void AbstractGridRepresentation::getParentColumnIndices(ULONG64 * parentColumnIndices) const
{
	if (gsoapProxy2_0_1 != nullptr) {
		gsoap_resqml2_0_1::resqml2__AbstractParentWindow* parentWindow = getParentWindow2_0_1();

		if (parentWindow != nullptr)
		{
			if (parentWindow->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__ColumnLayerParentWindow)
			{
				gsoap_resqml2_0_1::resqml2__ColumnLayerParentWindow* clpw = static_cast<gsoap_resqml2_0_1::resqml2__ColumnLayerParentWindow*>(parentWindow);
				if (clpw->ColumnIndices->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__IntegerHdf5Array) {
					return hdfProxy->readArrayNdOfGSoapULong64Values(static_cast<gsoap_resqml2_0_1::resqml2__IntegerHdf5Array*>(clpw->ColumnIndices)->Values->PathInHdfFile, parentColumnIndices);
				}
				else {
					throw invalid_argument("This list of columns can only be stored in HDF5 file.");
				}
			}
			else {
				throw invalid_argument("This information is only avaialble for column layer parent window.");
			}
		}
		else {
			throw invalid_argument("There is no parent window on this grid.");
		}
	}
	else {
		throw logic_error("Not implemented yet");
	}
}

ULONG64 AbstractGridRepresentation::getRegridStartIndexOnParentGrid(const char & dimension) const
{
	if (gsoapProxy2_0_1 != nullptr) {
		gsoap_resqml2_0_1::resqml2__AbstractParentWindow* parentWindow = getParentWindow2_0_1();

		if (parentWindow != nullptr)
		{
			if (parentWindow->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__IjkParentWindow)
			{
				if (dimension == 'i' || dimension == 'I')
				{
					return static_cast<gsoap_resqml2_0_1::resqml2__IjkParentWindow*>(parentWindow)->IRegrid->InitialIndexOnParentGrid;
				}
				else if (dimension == 'j' || dimension == 'J')
				{
					return static_cast<gsoap_resqml2_0_1::resqml2__IjkParentWindow*>(parentWindow)->JRegrid->InitialIndexOnParentGrid;
				}
				else if (dimension == 'k' || dimension == 'K')
				{
					return static_cast<gsoap_resqml2_0_1::resqml2__IjkParentWindow*>(parentWindow)->KRegrid->InitialIndexOnParentGrid;
				}
				else
					throw invalid_argument("Only i, j or k dimension can be accessed for an IJK Parent Window.");
			}
			else if (parentWindow->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__ColumnLayerParentWindow)
			{
				if (dimension == 'k' || dimension == 'K')
				{
					return static_cast<gsoap_resqml2_0_1::resqml2__ColumnLayerParentWindow*>(parentWindow)->KRegrid->InitialIndexOnParentGrid;
				}
				else
					throw invalid_argument("Only k dimension can be accessed for a ColumnLayer Parent Window.");
			}
			else
				throw invalid_argument("Regrid information is only avaialble for ijk or column layer parent window.");
		}
		else {
			throw invalid_argument("There is no parent window on this grid.");
		}
	}
	else {
		throw logic_error("Not implemented yet");
	}
}

ULONG64 AbstractGridRepresentation::getRegridIntervalCount(const char & dimension) const
{
	if (gsoapProxy2_0_1 != nullptr) {
		gsoap_resqml2_0_1::resqml2__AbstractParentWindow* parentWindow = getParentWindow2_0_1();

		if (parentWindow != nullptr)
		{
			if (parentWindow->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__IjkParentWindow)
			{
				if (dimension == 'i' || dimension == 'I')
				{
					if (static_cast<gsoap_resqml2_0_1::resqml2__IjkParentWindow*>(parentWindow)->IRegrid->Intervals != nullptr)
						return static_cast<gsoap_resqml2_0_1::resqml2__IjkParentWindow*>(parentWindow)->IRegrid->Intervals->IntervalCount;
					else
						return 0;
				}
				else if (dimension == 'j' || dimension == 'J')
				{
					if (static_cast<gsoap_resqml2_0_1::resqml2__IjkParentWindow*>(parentWindow)->JRegrid->Intervals != nullptr)
						return static_cast<gsoap_resqml2_0_1::resqml2__IjkParentWindow*>(parentWindow)->JRegrid->Intervals->IntervalCount;
					else
						return 0;
				}
				else if (dimension == 'k' || dimension == 'K')
				{
					if (static_cast<gsoap_resqml2_0_1::resqml2__IjkParentWindow*>(parentWindow)->KRegrid->Intervals != nullptr)
						return static_cast<gsoap_resqml2_0_1::resqml2__IjkParentWindow*>(parentWindow)->KRegrid->Intervals->IntervalCount;
					else
						return 0;
				}
				else
					throw invalid_argument("Only i, j or k dimension can be accessed for an IJK Parent Window.");
			}
			else if (parentWindow->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__ColumnLayerParentWindow)
			{
				if (dimension == 'k' || dimension == 'K')
				{
					if (static_cast<gsoap_resqml2_0_1::resqml2__ColumnLayerParentWindow*>(parentWindow)->KRegrid->Intervals != nullptr)
						return static_cast<gsoap_resqml2_0_1::resqml2__ColumnLayerParentWindow*>(parentWindow)->KRegrid->Intervals->IntervalCount;
					else
						return 0;
				}
				else
					throw invalid_argument("Only k dimension can be accessed for a ColumnLayer Parent Window.");
			}
			else
				throw invalid_argument("The parent window has not got any regrid information.");
		}
		else {
			throw invalid_argument("There is no parent window on this grid.");
		}
	}
	else {
		throw logic_error("Not implemented yet");
	}
}

gsoap_resqml2_0_1::resqml2__AbstractIntegerArray* AbstractGridRepresentation::getCellCountPerInterval2_0_1(const char & dimension, const bool & childVsParentCellCount) const {
	if (gsoapProxy2_0_1 != nullptr) {
		gsoap_resqml2_0_1::resqml2__AbstractParentWindow* parentWindow = getParentWindow2_0_1();

		if (parentWindow != nullptr) {
			if (parentWindow->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__IjkParentWindow) {
				const gsoap_resqml2_0_1::resqml2__IjkParentWindow* const ijkpw = static_cast<const gsoap_resqml2_0_1::resqml2__IjkParentWindow* const>(parentWindow);
				const gsoap_resqml2_0_1::resqml2__Regrid* regrid = nullptr;
				if (dimension == 'i' || dimension == 'I') {
					regrid = ijkpw->IRegrid;
				}
				else if (dimension == 'j' || dimension == 'J') {
					regrid = ijkpw->JRegrid;
				}
				else if (dimension == 'k' || dimension == 'K') {
					regrid = ijkpw->KRegrid;
				}
				else {
					throw invalid_argument("Only i, j or k dimension can be accessed for an IJK Parent Window.");
				}

				if (regrid->Intervals != nullptr) {
					return childVsParentCellCount ? regrid->Intervals->ChildCountPerInterval : regrid->Intervals->ParentCountPerInterval;
				}
				else {
					throw invalid_argument("No interval for this regrid.");
				}
			}
			else if (parentWindow->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__ColumnLayerParentWindow) {
				if (dimension == 'k' || dimension == 'K') {
					const gsoap_resqml2_0_1::resqml2__ColumnLayerParentWindow* const clpw = static_cast<const gsoap_resqml2_0_1::resqml2__ColumnLayerParentWindow* const>(parentWindow);
					if (clpw->KRegrid->Intervals != nullptr) {
						return childVsParentCellCount ? clpw->KRegrid->Intervals->ChildCountPerInterval : clpw->KRegrid->Intervals->ParentCountPerInterval;
					}
					else {
						throw invalid_argument("No interval for K regrid.");
					}
				}
				else {
					throw invalid_argument("Only k dimension can be accessed for a ColumnLayer Parent Window.");
				}
			}
			else {
				throw invalid_argument("The parent window has not got any regrid information.");
			}
		}
		else {
			throw invalid_argument("There is no parent window on this grid.");
		}
	}
	else {
		throw logic_error("Not implemented yet");
	}
}

bool AbstractGridRepresentation::isRegridCellCountPerIntervalConstant(const char & dimension, const bool & childVsParentCellCount) const {
	if (gsoapProxy2_0_1 != nullptr) {
		return getCellCountPerInterval2_0_1(dimension, childVsParentCellCount)->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__IntegerConstantArray;
	}
	else {
		throw logic_error("Not implemented yet");
	}
}

ULONG64 AbstractGridRepresentation::getRegridConstantCellCountPerInterval(const char & dimension, const bool & childVsParentCellCount) const {
	if (gsoapProxy2_0_1 != nullptr) {
		const gsoap_resqml2_0_1::resqml2__AbstractIntegerArray* const cellCountPerInterval = getCellCountPerInterval2_0_1(dimension, childVsParentCellCount);
		if (cellCountPerInterval->soap_type() != SOAP_TYPE_gsoap_resqml2_0_1_resqml2__IntegerConstantArray) {
			throw invalid_argument("The regrid child cell count per interval is not constant.");
		}

		return static_cast<const gsoap_resqml2_0_1::resqml2__IntegerConstantArray* const>(cellCountPerInterval)->Value;
	}
	else {
		throw logic_error("Not implemented yet");
	}
}

void AbstractGridRepresentation::getRegridCellCountPerInterval(const char & dimension, ULONG64 * childCellCountPerInterval, const bool & childVsParentCellCount) const
{
	if (gsoapProxy2_0_1 != nullptr) {
		const gsoap_resqml2_0_1::resqml2__AbstractIntegerArray* const childCountPerInterval = getCellCountPerInterval2_0_1(dimension, childVsParentCellCount);

		if (childCountPerInterval->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__IntegerConstantArray) {
			for (ULONG64 i = 0; i < static_cast<const gsoap_resqml2_0_1::resqml2__IntegerConstantArray* const>(childCountPerInterval)->Count; ++i) {
				childCellCountPerInterval[i] = static_cast<const gsoap_resqml2_0_1::resqml2__IntegerConstantArray* const>(childCountPerInterval)->Value;
			}
		}
		else if (childCountPerInterval->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__IntegerHdf5Array) {
			hdfProxy->readArrayNdOfGSoapULong64Values(static_cast<const gsoap_resqml2_0_1::resqml2__IntegerHdf5Array* const>(childCountPerInterval)->Values->PathInHdfFile, childCellCountPerInterval);
		}
		else  {
			throw logic_error("Not implemented yet");
		}
	}
	else {
		throw logic_error("Not implemented yet");
	}
}

bool AbstractGridRepresentation::hasRegridChildCellWeights(const char & dimension) const
{
	if (gsoapProxy2_0_1 != nullptr) {
		gsoap_resqml2_0_1::resqml2__AbstractParentWindow* parentWindow = getParentWindow2_0_1();

		if (parentWindow != nullptr) {
			if (parentWindow->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__IjkParentWindow)
			{
				gsoap_resqml2_0_1::resqml2__IjkParentWindow* ijkpw = static_cast<gsoap_resqml2_0_1::resqml2__IjkParentWindow*>(parentWindow);
				if (dimension == 'i' || dimension == 'I')
				{
					if (ijkpw->IRegrid->Intervals != nullptr)
					{
						return ijkpw->IRegrid->Intervals->ChildCellWeights != nullptr;
					}
					else
						throw invalid_argument("No interval for I regrid.");
				}
				else if (dimension == 'j' || dimension == 'J')
				{
					if (ijkpw->JRegrid->Intervals != nullptr)
					{
						return ijkpw->JRegrid->Intervals->ChildCellWeights != nullptr;
					}
					else
						throw invalid_argument("No interval for J regrid.");
				}
				else if (dimension == 'k' || dimension == 'K')
				{
					if (ijkpw->KRegrid->Intervals != nullptr)
					{
						return ijkpw->KRegrid->Intervals->ChildCellWeights != nullptr;
					}
					else {
						throw invalid_argument("No interval for K regrid.");
					}
				}
				else {
					throw invalid_argument("Only i, j or k dimension can be accessed for an IJK Parent Window.");
				}
			}
			else if (parentWindow->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__ColumnLayerParentWindow)
			{
				if (dimension == 'k' || dimension == 'K')
				{
					gsoap_resqml2_0_1::resqml2__ColumnLayerParentWindow* clpw = static_cast<gsoap_resqml2_0_1::resqml2__ColumnLayerParentWindow*>(parentWindow);
					if (clpw->KRegrid->Intervals != nullptr )
					{
						return clpw->KRegrid->Intervals->ChildCellWeights != nullptr;
					}
					else {
						throw invalid_argument("No interval for K regrid.");
					}
				}
				else {
					throw invalid_argument("Only k dimension can be accessed for a ColumnLayer Parent Window.");
				}
			}
			else
				throw invalid_argument("The parent window has not got any regrid information.");
		}
		else {
			throw invalid_argument("There is no parent window on this grid.");
		}
	}
	else {
		throw logic_error("Not implemented yet");
	}
}

void AbstractGridRepresentation::getRegridChildCellWeights(const char & dimension, ULONG64 * childCellWeights) const
{
	if (gsoapProxy2_0_1 != nullptr) {
		gsoap_resqml2_0_1::resqml2__AbstractParentWindow* parentWindow = getParentWindow2_0_1();

		if (parentWindow != nullptr) {
			if (parentWindow->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__IjkParentWindow)
			{
				gsoap_resqml2_0_1::resqml2__IjkParentWindow* ijkpw = static_cast<gsoap_resqml2_0_1::resqml2__IjkParentWindow*>(parentWindow);
				if (dimension == 'i' || dimension == 'I')
				{
					if (ijkpw->IRegrid->Intervals != nullptr && ijkpw->IRegrid->Intervals->ChildCellWeights != nullptr)
					{
						if (ijkpw->IRegrid->Intervals->ChildCellWeights->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__DoubleHdf5Array)
							hdfProxy->readArrayNdOfGSoapULong64Values(static_cast<gsoap_resqml2_0_1::resqml2__DoubleHdf5Array*>(ijkpw->IRegrid->Intervals->ChildCellWeights)->Values->PathInHdfFile, childCellWeights);
						else
							throw invalid_argument("ChildCellWeights should be in HDF5 file.");
					}
					else
						throw invalid_argument("No interval for I regrid.");
				}
				else if (dimension == 'j' || dimension == 'J')
				{
					if (ijkpw->JRegrid->Intervals != nullptr && ijkpw->JRegrid->Intervals->ChildCellWeights != nullptr)
					{
						if (ijkpw->JRegrid->Intervals->ChildCellWeights->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__DoubleHdf5Array)
							hdfProxy->readArrayNdOfGSoapULong64Values(static_cast<gsoap_resqml2_0_1::resqml2__DoubleHdf5Array*>(ijkpw->JRegrid->Intervals->ChildCellWeights)->Values->PathInHdfFile, childCellWeights);
						else
							throw invalid_argument("ChildCellWeights should be in HDF5 file.");
					}
					else
						throw invalid_argument("No interval for J regrid.");
				}
				else if (dimension == 'k' || dimension == 'K')
				{
					if (ijkpw->KRegrid->Intervals != nullptr && ijkpw->KRegrid->Intervals->ChildCellWeights != nullptr)
					{
						if (ijkpw->KRegrid->Intervals->ChildCellWeights->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__DoubleHdf5Array)
							hdfProxy->readArrayNdOfGSoapULong64Values(static_cast<gsoap_resqml2_0_1::resqml2__DoubleHdf5Array*>(ijkpw->KRegrid->Intervals->ChildCellWeights)->Values->PathInHdfFile, childCellWeights);
						else
							throw invalid_argument("ChildCellWeights should be in HDF5 file.");
					}
					else
						throw invalid_argument("No interval for K regrid.");
				}
				else
					throw invalid_argument("Only i, j or k dimension can be accessed for an IJK Parent Window.");
			}
			else if (parentWindow->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__ColumnLayerParentWindow)
			{
				if (dimension == 'k' || dimension == 'K')
				{
					gsoap_resqml2_0_1::resqml2__ColumnLayerParentWindow* clpw = static_cast<gsoap_resqml2_0_1::resqml2__ColumnLayerParentWindow*>(parentWindow);
					if (clpw->KRegrid->Intervals != nullptr  && clpw->KRegrid->Intervals->ChildCellWeights != nullptr)
					{
						if (clpw->KRegrid->Intervals->ChildCellWeights->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__DoubleHdf5Array)
							hdfProxy->readArrayNdOfGSoapULong64Values(static_cast<gsoap_resqml2_0_1::resqml2__DoubleHdf5Array*>(clpw->KRegrid->Intervals->ChildCellWeights)->Values->PathInHdfFile, childCellWeights);
						else
							throw invalid_argument("ChildCellWeights should be in HDF5 file.");
					}
					else
						throw invalid_argument("No interval for K regrid.");
				}
				else
					throw invalid_argument("Only k dimension can be accessed for a ColumnLayer Parent Window.");
			}
			else
				throw invalid_argument("The parent window has not got any regrid information.");
		}
		else {
			throw invalid_argument("There is no parent window on this grid.");
		}
	}
	else {
		throw logic_error("Not implemented yet");
	}
}

void AbstractGridRepresentation::importRelationshipSetFromEpc(common::EpcDocument* epcDoc)
{
	AbstractRepresentation::importRelationshipSetFromEpc(epcDoc);

	// LGR backward relationships
	gsoap_resqml2_0_1::eml20__DataObjectReference* dor = getParentGridDor();
	if (dor != nullptr) {
		resqml2::AbstractGridRepresentation* parentGrid = epcDoc->getResqmlAbstractObjectByUuid<resqml2::AbstractGridRepresentation>(dor->UUID);
		if (parentGrid == nullptr) { // partial transfer
			getEpcDocument()->createPartial(dor);
			parentGrid = getEpcDocument()->getResqmlAbstractObjectByUuid<resqml2::AbstractGridRepresentation>(dor->UUID);
		}
		if (parentGrid == nullptr) {
			throw invalid_argument("The DOR looks invalid.");
		}
		updateXml = false;
		parentGrid->childGridSet.push_back(this);
		updateXml = true;
	}

	// Strati org backward relationships
	dor = getStratigraphicOrganizationInterpretationDor();
	if (dor != nullptr) {
		resqml2_0_1::AbstractStratigraphicOrganizationInterpretation* stratiOrg = epcDoc->getResqmlAbstractObjectByUuid<resqml2_0_1::AbstractStratigraphicOrganizationInterpretation>(dor->UUID);
		if (stratiOrg == nullptr) { // partial transfer
			getEpcDocument()->createPartial(dor);
			stratiOrg = getEpcDocument()->getResqmlAbstractObjectByUuid<resqml2_0_1::AbstractStratigraphicOrganizationInterpretation>(dor->UUID);
		}
		if (stratiOrg == nullptr) {
			throw invalid_argument("The DOR looks invalid.");
		}
		updateXml = false;
		setCellAssociationWithStratigraphicOrganizationInterpretation(nullptr, 0, stratiOrg);
		updateXml = true;
	}
}

void AbstractGridRepresentation::setCellAssociationWithStratigraphicOrganizationInterpretation(ULONG64 * stratiUnitIndices, const ULONG64 & nullValue, resqml2_0_1::AbstractStratigraphicOrganizationInterpretation * stratiOrgInterp)
{
	// Backward rel
	if (!stratiOrgInterp->isAssociatedToGridRepresentation(this))
	{
		stratiOrgInterp->gridRepresentationSet.push_back(this);
	}

	// XML
	if (updateXml)
	{
		if (gsoapProxy2_0_1 != nullptr) {
			gsoap_resqml2_0_1::resqml2__AbstractGridRepresentation* rep = static_cast<gsoap_resqml2_0_1::resqml2__AbstractGridRepresentation*>(gsoapProxy2_0_1);
			rep->CellStratigraphicUnits = gsoap_resqml2_0_1::soap_new_resqml2__CellStratigraphicUnits(rep->soap, 1);
			rep->CellStratigraphicUnits->StratigraphicOrganization = stratiOrgInterp->newResqmlReference();

			gsoap_resqml2_0_1::resqml2__IntegerHdf5Array* xmlDataset = gsoap_resqml2_0_1::soap_new_resqml2__IntegerHdf5Array(rep->soap, 1);
			xmlDataset->NullValue = nullValue;
			xmlDataset->Values = gsoap_resqml2_0_1::soap_new_eml20__Hdf5Dataset(gsoapProxy2_0_1->soap, 1);
			xmlDataset->Values->HdfProxy = hdfProxy->newResqmlReference();
			xmlDataset->Values->PathInHdfFile = "/RESQML/" + rep->uuid + "/CellStratigraphicUnits";
			rep->CellStratigraphicUnits->UnitIndices = xmlDataset;

			// ************ HDF *************
			hsize_t dim = getCellCount();
			hdfProxy->writeArrayNd(rep->uuid, "CellStratigraphicUnits", H5T_NATIVE_ULLONG, stratiUnitIndices, &dim, 1);
		}
		else {
			throw logic_error("Not implemented yet");
		}
	}
}

gsoap_resqml2_0_1::eml20__DataObjectReference* AbstractGridRepresentation::getStratigraphicOrganizationInterpretationDor() const
{
	if (!hasCellStratigraphicUnitIndices()) {
		return nullptr;
	}

	if (gsoapProxy2_0_1 != nullptr) {
		return static_cast<gsoap_resqml2_0_1::resqml2__AbstractGridRepresentation*>(gsoapProxy2_0_1)->CellStratigraphicUnits->StratigraphicOrganization;
	}
	else {
		throw logic_error("Not implemented yet");
	}
}

std::string AbstractGridRepresentation::getStratigraphicOrganizationInterpretationUuid() const
{
	gsoap_resqml2_0_1::eml20__DataObjectReference* dor = getStratigraphicOrganizationInterpretationDor();
	return dor == nullptr ? string() : dor->UUID;
}

std::string AbstractGridRepresentation::getStratigraphicOrganizationInterpretationTitle() const
{
	gsoap_resqml2_0_1::eml20__DataObjectReference* dor = getStratigraphicOrganizationInterpretationDor();
	return dor == nullptr ? string() : dor->Title;
}

resqml2_0_1::AbstractStratigraphicOrganizationInterpretation* AbstractGridRepresentation::getStratigraphicOrganizationInterpretation() const
{
	const string stratigraphicOrganizationInterpretationUuid = getStratigraphicOrganizationInterpretationUuid();
	if (stratigraphicOrganizationInterpretationUuid.empty()) {
		return nullptr;
	}

	return static_cast<resqml2_0_1::AbstractStratigraphicOrganizationInterpretation*>(getEpcDocument()->getResqmlAbstractObjectByUuid(stratigraphicOrganizationInterpretationUuid));
}

bool AbstractGridRepresentation::hasCellStratigraphicUnitIndices() const
{
	if (gsoapProxy2_0_1 != nullptr) {
		return static_cast<gsoap_resqml2_0_1::resqml2__AbstractGridRepresentation*>(gsoapProxy2_0_1)->CellStratigraphicUnits != nullptr;
	}
	else {
		throw logic_error("Not implemented yet");
	}
}

ULONG64 AbstractGridRepresentation::getCellStratigraphicUnitIndices(ULONG64 * stratiUnitIndices)
{
	if (!hasCellStratigraphicUnitIndices()) {
		throw invalid_argument("This grid has no CellStratigraphicUnits information");
	}

	if (gsoapProxy2_0_1 != nullptr) {
		gsoap_resqml2_0_1::resqml2__AbstractGridRepresentation* rep = static_cast<gsoap_resqml2_0_1::resqml2__AbstractGridRepresentation*>(gsoapProxy2_0_1);
		if (rep->CellStratigraphicUnits->UnitIndices->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__IntegerHdf5Array)
		{
			hdfProxy->readArrayNdOfGSoapULong64Values(static_cast<gsoap_resqml2_0_1::resqml2__IntegerHdf5Array*>(rep->CellStratigraphicUnits->UnitIndices)->Values->PathInHdfFile, stratiUnitIndices);
			return static_cast<gsoap_resqml2_0_1::resqml2__IntegerHdf5Array*>(rep->CellStratigraphicUnits->UnitIndices)->NullValue;
		}

		throw logic_error("Not implemented yet.");
	}
	else {
		throw logic_error("Not implemented yet");
	}
}

bool AbstractGridRepresentation::isTruncated() const
{
	return withTruncatedPillars;
}

ULONG64 AbstractGridRepresentation::getTruncatedFaceCount() const
{
	if (!isTruncated()) {
		throw invalid_argument("The grid is not truncated");
	}

	if (gsoapProxy2_0_1 != nullptr) {
		gsoap_resqml2_0_1::resqml2__AbstractTruncatedColumnLayerGridRepresentation* rep = static_cast<gsoap_resqml2_0_1::resqml2__AbstractTruncatedColumnLayerGridRepresentation*>(gsoapProxy2_0_1);
		return rep->TruncationCells->TruncationFaceCount;
	}
	else {
		throw logic_error("Not implemented yet");
	}
}

void AbstractGridRepresentation::getNodeIndicesOfTruncatedFaces(ULONG64 * nodeIndices) const
{
	if (!isTruncated()) {
		throw invalid_argument("The grid is not truncated");
	}

	if (gsoapProxy2_0_1 != nullptr) {
		gsoap_resqml2_0_1::resqml2__AbstractTruncatedColumnLayerGridRepresentation* rep = static_cast<gsoap_resqml2_0_1::resqml2__AbstractTruncatedColumnLayerGridRepresentation*>(gsoapProxy2_0_1);

		if (rep->TruncationCells->NodesPerTruncationFace->Elements->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__IntegerHdf5Array)
		{
			hdfProxy->readArrayNdOfGSoapULong64Values(static_cast<gsoap_resqml2_0_1::resqml2__IntegerHdf5Array*>(rep->TruncationCells->NodesPerTruncationFace->Elements)->Values->PathInHdfFile, nodeIndices);
		}
		else
			throw logic_error("Not yet implemented");
	}
	else {
		throw logic_error("Not implemented yet");
	}
}

void AbstractGridRepresentation::getCumulativeNodeCountPerTruncatedFace(ULONG64 * nodeCountPerFace) const
{
	if (!isTruncated()) {
		throw invalid_argument("The grid is not truncated");
	}

	if (gsoapProxy2_0_1 != nullptr) {
		gsoap_resqml2_0_1::resqml2__AbstractTruncatedColumnLayerGridRepresentation* rep = static_cast<gsoap_resqml2_0_1::resqml2__AbstractTruncatedColumnLayerGridRepresentation*>(gsoapProxy2_0_1);

		if (rep->TruncationCells->NodesPerTruncationFace->CumulativeLength->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__IntegerHdf5Array)
		{
			hdfProxy->readArrayNdOfGSoapULong64Values(static_cast<gsoap_resqml2_0_1::resqml2__IntegerHdf5Array*>(rep->TruncationCells->NodesPerTruncationFace->CumulativeLength)->Values->PathInHdfFile, nodeCountPerFace);
		}
		else if (rep->TruncationCells->NodesPerTruncationFace->CumulativeLength->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__IntegerLatticeArray)
		{
			nodeCountPerFace[0] = static_cast<gsoap_resqml2_0_1::resqml2__IntegerLatticeArray*>(rep->TruncationCells->NodesPerTruncationFace->CumulativeLength)->StartValue;
			const LONG64 offsetValue = static_cast<gsoap_resqml2_0_1::resqml2__IntegerLatticeArray*>(rep->TruncationCells->NodesPerTruncationFace->CumulativeLength)->Offset[0]->Value;
			const ULONG64 faceCount = getTruncatedFaceCount();
			for (ULONG64 nodeCountPerFaceIndex = 1; nodeCountPerFaceIndex < faceCount; ++nodeCountPerFaceIndex) {
				nodeCountPerFace[nodeCountPerFaceIndex] = nodeCountPerFace[nodeCountPerFaceIndex - 1] + offsetValue;
			}
		}
		else if (rep->TruncationCells->NodesPerTruncationFace->CumulativeLength->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__IntegerConstantArray)
		{
			throw range_error("The *cumulative* length of nodes count per cells cannot be constant.");
		}
	}
	else {
		throw logic_error("Not implemented yet");
	}
}

void AbstractGridRepresentation::getNodeCountPerTruncatedFace(ULONG64 * nodeCountPerFace) const
{
	getCumulativeNodeCountPerTruncatedFace(nodeCountPerFace);
	const ULONG64 faceCount = getTruncatedFaceCount();
	ULONG64 buffer = nodeCountPerFace[0];
	ULONG64 bufferCumCount = 0;
	for (ULONG64 cumulativeNodeCountPerFaceIndex = 1; cumulativeNodeCountPerFaceIndex < faceCount; ++cumulativeNodeCountPerFaceIndex)
	{
		bufferCumCount = nodeCountPerFace[cumulativeNodeCountPerFaceIndex];
		nodeCountPerFace[cumulativeNodeCountPerFaceIndex] -= buffer;
		buffer = bufferCumCount;
	}
}

ULONG64 AbstractGridRepresentation::getTruncatedCellCount() const
{
	if (!isTruncated()) {
		throw invalid_argument("The grid is not truncated");
	}

	if (gsoapProxy2_0_1 != nullptr) {
		gsoap_resqml2_0_1::resqml2__AbstractTruncatedColumnLayerGridRepresentation* rep = static_cast<gsoap_resqml2_0_1::resqml2__AbstractTruncatedColumnLayerGridRepresentation*>(gsoapProxy2_0_1);
		return rep->TruncationCells->TruncationCellCount;
	}
	else {
		throw logic_error("Not implemented yet");
	}
}

void AbstractGridRepresentation::getTruncatedCellIndices(ULONG64* cellIndices) const
{
	if (!isTruncated()) {
		throw invalid_argument("The grid is not truncated");
	}

	if (gsoapProxy2_0_1 != nullptr) {
		gsoap_resqml2_0_1::resqml2__AbstractTruncatedColumnLayerGridRepresentation* rep = static_cast<gsoap_resqml2_0_1::resqml2__AbstractTruncatedColumnLayerGridRepresentation*>(gsoapProxy2_0_1);

		if (rep->TruncationCells->ParentCellIndices->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__IntegerHdf5Array)
		{
			hdfProxy->readArrayNdOfGSoapULong64Values(static_cast<gsoap_resqml2_0_1::resqml2__IntegerHdf5Array*>(rep->TruncationCells->ParentCellIndices)->Values->PathInHdfFile, cellIndices);
		}
		else if (rep->TruncationCells->ParentCellIndices->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__IntegerConstantArray)
		{
			for (size_t i = 0; i < static_cast<gsoap_resqml2_0_1::resqml2__IntegerConstantArray*>(rep->TruncationCells->ParentCellIndices)->Count; ++i)
			{
				cellIndices[i] = static_cast<gsoap_resqml2_0_1::resqml2__IntegerConstantArray*>(rep->TruncationCells->ParentCellIndices)->Value;
			}
		}
		else
			throw logic_error("Not yet implemented.");
	}
	else {
		throw logic_error("Not implemented yet");
	}
}

void AbstractGridRepresentation::getTruncatedFaceIndicesOfTruncatedCells(ULONG64 * faceIndices) const
{
	if (!isTruncated()) {
		throw invalid_argument("The grid is not truncated");
	}

	if (gsoapProxy2_0_1 != nullptr) {
		gsoap_resqml2_0_1::resqml2__AbstractTruncatedColumnLayerGridRepresentation* rep = static_cast<gsoap_resqml2_0_1::resqml2__AbstractTruncatedColumnLayerGridRepresentation*>(gsoapProxy2_0_1);

		if (rep->TruncationCells->TruncationFacesPerCell->Elements->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__IntegerHdf5Array)
		{
			hdfProxy->readArrayNdOfGSoapULong64Values(static_cast<gsoap_resqml2_0_1::resqml2__IntegerHdf5Array*>(rep->TruncationCells->TruncationFacesPerCell->Elements)->Values->PathInHdfFile, faceIndices);
		}
		else
			throw logic_error("Not yet implemented");
	}
	else {
		throw logic_error("Not implemented yet");
	}
}

void AbstractGridRepresentation::getCumulativeTruncatedFaceCountPerTruncatedCell(ULONG64 * cumulativeFaceCountPerCell) const
{
	
	if (!isTruncated()) {
		throw invalid_argument("The grid is not truncated");
	}

	if (gsoapProxy2_0_1 != nullptr) {
		gsoap_resqml2_0_1::resqml2__AbstractTruncatedColumnLayerGridRepresentation* rep = static_cast<gsoap_resqml2_0_1::resqml2__AbstractTruncatedColumnLayerGridRepresentation*>(gsoapProxy2_0_1);

		if (rep->TruncationCells->TruncationFacesPerCell->CumulativeLength->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__IntegerHdf5Array)
		{
			hdfProxy->readArrayNdOfGSoapULong64Values(static_cast<gsoap_resqml2_0_1::resqml2__IntegerHdf5Array*>(rep->TruncationCells->TruncationFacesPerCell->CumulativeLength)->Values->PathInHdfFile, cumulativeFaceCountPerCell);
		}
		else if (rep->TruncationCells->TruncationFacesPerCell->CumulativeLength->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__IntegerLatticeArray)
		{
			cumulativeFaceCountPerCell[0] = static_cast<gsoap_resqml2_0_1::resqml2__IntegerLatticeArray*>(rep->TruncationCells->TruncationFacesPerCell->CumulativeLength)->StartValue;
			const LONG64 offsetValue = static_cast<gsoap_resqml2_0_1::resqml2__IntegerLatticeArray*>(rep->TruncationCells->TruncationFacesPerCell->CumulativeLength)->Offset[0]->Value;
			const ULONG64 cellCount = getTruncatedCellCount();
			for (ULONG64 cumulativeFaceCountPerCellIndex = 1; cumulativeFaceCountPerCellIndex < cellCount; ++cumulativeFaceCountPerCellIndex)
			{
				cumulativeFaceCountPerCell[cumulativeFaceCountPerCellIndex] = cumulativeFaceCountPerCell[cumulativeFaceCountPerCellIndex - 1] + offsetValue;
			}
		}
		else if (rep->TruncationCells->TruncationFacesPerCell->CumulativeLength->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__IntegerConstantArray)
		{
			if (getTruncatedCellCount() > 1)
				throw range_error("The cumulative length of faces count per cells cannot be constant if there is more than one cell in the grid");
			cumulativeFaceCountPerCell[0] = static_cast<gsoap_resqml2_0_1::resqml2__IntegerConstantArray*>(rep->TruncationCells->TruncationFacesPerCell->CumulativeLength)->Value;
		}
	}
	else {
		throw logic_error("Not implemented yet");
	}
}

void AbstractGridRepresentation::getTruncatedFaceCountPerTruncatedCell(ULONG64 * faceCountPerCell) const
{
	getCumulativeTruncatedFaceCountPerTruncatedCell(faceCountPerCell);
	const ULONG64 cellCount = getTruncatedCellCount();
	ULONG64 buffer = faceCountPerCell[0];
	ULONG64 bufferCumCount = 0;
	for (ULONG64 cumulativeFaceCountPerCellIndex = 1; cumulativeFaceCountPerCellIndex < cellCount; ++cumulativeFaceCountPerCellIndex)
	{
		bufferCumCount = faceCountPerCell[cumulativeFaceCountPerCellIndex];
		faceCountPerCell[cumulativeFaceCountPerCellIndex] -= buffer;
		buffer = bufferCumCount;
	}
}

void AbstractGridRepresentation::getNonTruncatedFaceIndicesOfTruncatedCells(ULONG64 * faceIndices) const
{
	if (!isTruncated()) {
		throw invalid_argument("The grid is not truncated");
	}

	if (gsoapProxy2_0_1 != nullptr) {
		gsoap_resqml2_0_1::resqml2__AbstractTruncatedColumnLayerGridRepresentation* rep = static_cast<gsoap_resqml2_0_1::resqml2__AbstractTruncatedColumnLayerGridRepresentation*>(gsoapProxy2_0_1);

		if (rep->TruncationCells->LocalFacesPerCell->Elements->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__IntegerHdf5Array)
		{
			hdfProxy->readArrayNdOfGSoapULong64Values(static_cast<gsoap_resqml2_0_1::resqml2__IntegerHdf5Array*>(rep->TruncationCells->LocalFacesPerCell->Elements)->Values->PathInHdfFile, faceIndices);
		}
		else
			throw logic_error("Not yet implemented");
	}
	else {
		throw logic_error("Not implemented yet");
	}
}

void AbstractGridRepresentation::getCumulativeNonTruncatedFaceCountPerTruncatedCell(ULONG64 * cumulativeFaceCountPerCell) const
{

	if (!isTruncated()) {
		throw invalid_argument("The grid is not truncated");
	}

	if (gsoapProxy2_0_1 != nullptr) {
		gsoap_resqml2_0_1::resqml2__AbstractTruncatedColumnLayerGridRepresentation* rep = static_cast<gsoap_resqml2_0_1::resqml2__AbstractTruncatedColumnLayerGridRepresentation*>(gsoapProxy2_0_1);

		if (rep->TruncationCells->LocalFacesPerCell->CumulativeLength->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__IntegerHdf5Array)
		{
			hdfProxy->readArrayNdOfGSoapULong64Values(static_cast<gsoap_resqml2_0_1::resqml2__IntegerHdf5Array*>(rep->TruncationCells->LocalFacesPerCell->CumulativeLength)->Values->PathInHdfFile, cumulativeFaceCountPerCell);
		}
		else if (rep->TruncationCells->LocalFacesPerCell->CumulativeLength->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__IntegerLatticeArray)
		{
			cumulativeFaceCountPerCell[0] = static_cast<gsoap_resqml2_0_1::resqml2__IntegerLatticeArray*>(rep->TruncationCells->LocalFacesPerCell->CumulativeLength)->StartValue;
			const LONG64 offsetValue = static_cast<gsoap_resqml2_0_1::resqml2__IntegerLatticeArray*>(rep->TruncationCells->LocalFacesPerCell->CumulativeLength)->Offset[0]->Value;
			const ULONG64 cellCount = getTruncatedCellCount();
			for (ULONG64 cumulativeFaceCountPerCellIndex = 1; cumulativeFaceCountPerCellIndex < cellCount; ++cumulativeFaceCountPerCellIndex)
			{
				cumulativeFaceCountPerCell[cumulativeFaceCountPerCellIndex] = cumulativeFaceCountPerCell[cumulativeFaceCountPerCellIndex - 1] + offsetValue;
			}
		}
		else if (rep->TruncationCells->LocalFacesPerCell->CumulativeLength->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__IntegerConstantArray)
		{
			if (getTruncatedCellCount() > 1)
				throw range_error("The cumulative length of faces count per cells cannot be constant if there is more than one cell in the grid");
			cumulativeFaceCountPerCell[0] = static_cast<gsoap_resqml2_0_1::resqml2__IntegerConstantArray*>(rep->TruncationCells->LocalFacesPerCell->CumulativeLength)->Value;
		}
	}
	else {
		throw logic_error("Not implemented yet");
	}
}

void AbstractGridRepresentation::getNonTruncatedFaceCountPerTruncatedCell(ULONG64 * faceCountPerCell) const
{
	getCumulativeNonTruncatedFaceCountPerTruncatedCell(faceCountPerCell);
	const ULONG64 cellCount = getTruncatedCellCount();
	ULONG64 buffer = faceCountPerCell[0];
	ULONG64 bufferCumCount = 0;
	for (ULONG64 cumulativeFaceCountPerCellIndex = 1; cumulativeFaceCountPerCellIndex < cellCount; ++cumulativeFaceCountPerCellIndex)
	{
		bufferCumCount = faceCountPerCell[cumulativeFaceCountPerCellIndex];
		faceCountPerCell[cumulativeFaceCountPerCellIndex] -= buffer;
		buffer = bufferCumCount;
	}
}

void AbstractGridRepresentation::getTruncatedFaceIsRightHanded(unsigned char* cellFaceIsRightHanded) const
{
	if (!isTruncated()) {
		throw invalid_argument("The grid is not truncated");
	}

	if (gsoapProxy2_0_1 != nullptr) {
		gsoap_resqml2_0_1::resqml2__AbstractTruncatedColumnLayerGridRepresentation* rep = static_cast<gsoap_resqml2_0_1::resqml2__AbstractTruncatedColumnLayerGridRepresentation*>(gsoapProxy2_0_1);

		if (rep->TruncationCells->TruncationCellFaceIsRightHanded->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__BooleanHdf5Array)
		{
			hdfProxy->readArrayNdOfUCharValues(static_cast<gsoap_resqml2_0_1::resqml2__BooleanHdf5Array*>(rep->TruncationCells->TruncationCellFaceIsRightHanded)->Values->PathInHdfFile, cellFaceIsRightHanded);
		}
		else if (rep->TruncationCells->TruncationCellFaceIsRightHanded->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__BooleanConstantArray)
		{
			for (size_t i = 0; i < static_cast<gsoap_resqml2_0_1::resqml2__BooleanConstantArray*>(rep->TruncationCells->TruncationCellFaceIsRightHanded)->Count; ++i)
			{
				cellFaceIsRightHanded[i] = static_cast<gsoap_resqml2_0_1::resqml2__BooleanConstantArray*>(rep->TruncationCells->TruncationCellFaceIsRightHanded)->Value;
			}
		}
		else
			throw logic_error("Not yet implemented.");
	}
	else {
		throw logic_error("Not implemented yet");
	}
}

