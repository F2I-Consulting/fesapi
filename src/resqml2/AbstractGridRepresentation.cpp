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
#include "resqml2/AbstractGridRepresentation.h"

#include <stdexcept>
#include <algorithm>
#include <limits>

#include "hdf5.h"
#include "tools/Misc.h"
#include "resqml2_0_1/AbstractStratigraphicOrganizationInterpretation.h"
#include "common/AbstractHdfProxy.h"
#include "resqml2_0_1/UnstructuredGridRepresentation.h"
#include "resqml2_0_1/AbstractIjkGridRepresentation.h"
#include "resqml2_0_1/RockFluidOrganizationInterpretation.h"

using namespace RESQML2_NS;
using namespace std;

const char* AbstractGridRepresentation::XML_TAG = "AbstractGridRepresentation";

std::vector<RESQML2_NS::GridConnectionSetRepresentation *> AbstractGridRepresentation::getGridConnectionSetRepresentationSet() const
{
	return repository->getSourceObjects<RESQML2_NS::GridConnectionSetRepresentation>(this);
}

unsigned int AbstractGridRepresentation::getGridConnectionSetRepresentationCount() const
{
	const size_t result = getGridConnectionSetRepresentationSet().size();

	if (result > (std::numeric_limits<unsigned int>::max)()) {
		throw out_of_range("The count of the GridConnectionSet Representations is too big.");
	}

	return static_cast<unsigned int>(result);
}

RESQML2_NS::GridConnectionSetRepresentation * AbstractGridRepresentation::getGridConnectionSetRepresentation(unsigned int index) const
{
	const std::vector<RESQML2_NS::GridConnectionSetRepresentation *>& gridConnectionSetRepresentationSet = getGridConnectionSetRepresentationSet();

	if (gridConnectionSetRepresentationSet.size() > index) {
		return gridConnectionSetRepresentationSet[index];
	}
	
	throw std::out_of_range("No GridConnectionSetRepresentation at this index.");
}

gsoap_resqml2_0_1::resqml20__AbstractParentWindow* AbstractGridRepresentation::getParentWindow2_0_1() const
{
	if (gsoapProxy2_0_1 != nullptr) {
		return static_cast<gsoap_resqml2_0_1::resqml20__AbstractGridRepresentation*>(gsoapProxy2_0_1)->ParentWindow;
	}

	return nullptr;
}

gsoap_resqml2_0_1::eml20__DataObjectReference* AbstractGridRepresentation::getParentGridDor() const
{
	if (gsoapProxy2_0_1 != nullptr) {
		gsoap_resqml2_0_1::resqml20__AbstractParentWindow* parentWindow = getParentWindow2_0_1();

		if (parentWindow != nullptr) {
			if (parentWindow->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__IjkParentWindow) {
				gsoap_resqml2_0_1::resqml20__IjkParentWindow* pw = static_cast<gsoap_resqml2_0_1::resqml20__IjkParentWindow*>(parentWindow);
				return pw->ParentGrid;
			}
			else if (parentWindow->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__ColumnLayerParentWindow) {
				gsoap_resqml2_0_1::resqml20__ColumnLayerParentWindow* pw = static_cast<gsoap_resqml2_0_1::resqml20__ColumnLayerParentWindow*>(parentWindow);
				return pw->ParentGrid;
			}
			else if (parentWindow->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__CellParentWindow) {
				gsoap_resqml2_0_1::resqml20__CellParentWindow* pw = static_cast<gsoap_resqml2_0_1::resqml20__CellParentWindow*>(parentWindow);
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
		return static_cast<AbstractGridRepresentation*>(getRepository()->getDataObjectByUuid(parentGridUuid));
	}
	
	return nullptr;
}

std::vector<RESQML2_NS::AbstractGridRepresentation *> AbstractGridRepresentation::getChildGridSet() const
{
	return repository->getSourceObjects<RESQML2_NS::AbstractGridRepresentation>(this);
}

unsigned int AbstractGridRepresentation::getChildGridCount() const {
	const size_t result = getChildGridSet().size();

	if (result > (std::numeric_limits<unsigned int>::max)()) {
		throw out_of_range("The count of the child grids is too big.");
	}

	return static_cast<unsigned int>(result);
}

AbstractGridRepresentation * AbstractGridRepresentation::getChildGrid(unsigned int index) const
{
	const std::vector<RESQML2_NS::AbstractGridRepresentation *>& childGridSet = getChildGridSet();

	if (childGridSet.size() > index) {
		return childGridSet[index];
	}

	throw std::out_of_range("The child grid index is out of range.");
}

gsoap_resqml2_0_1::resqml20__Regrid* AbstractGridRepresentation::createRegrid(unsigned int indexRegridStart, unsigned int * childCellCountPerInterval, unsigned int * parentCellCountPerInterval, unsigned int intervalCount, double * childCellWeights,
	const std::string & dimension, COMMON_NS::AbstractHdfProxy * proxy, bool forceConstantCellCountPerInterval)
{
	gsoap_resqml2_0_1::resqml20__Regrid* regrid = gsoap_resqml2_0_1::soap_new_resqml20__Regrid(gsoapProxy2_0_1->soap);
	regrid->InitialIndexOnParentGrid = indexRegridStart;
	regrid->Intervals = gsoap_resqml2_0_1::soap_new_resqml20__Intervals(gsoapProxy2_0_1->soap);
	regrid->Intervals->IntervalCount = intervalCount;
	
	if (intervalCount == 0) {
		throw invalid_argument("Cannot regrid an empty list of intervals.");
	}
	else if (intervalCount == 1 || forceConstantCellCountPerInterval) {
		gsoap_resqml2_0_1::resqml20__IntegerConstantArray* xmlChildCountPerInterval = gsoap_resqml2_0_1::soap_new_resqml20__IntegerConstantArray(gsoapProxy2_0_1->soap);
		xmlChildCountPerInterval->Value = *childCellCountPerInterval;
		xmlChildCountPerInterval->Count = intervalCount;
		regrid->Intervals->ChildCountPerInterval = xmlChildCountPerInterval;

		gsoap_resqml2_0_1::resqml20__IntegerConstantArray* xmlParentCountPerInterval = gsoap_resqml2_0_1::soap_new_resqml20__IntegerConstantArray(gsoapProxy2_0_1->soap);
		xmlParentCountPerInterval->Value = *parentCellCountPerInterval;
		xmlParentCountPerInterval->Count = intervalCount;
		regrid->Intervals->ParentCountPerInterval = xmlParentCountPerInterval;
	}
	else {

		if (proxy == nullptr) {
			proxy = getRepository()->getDefaultHdfProxy();
		}
		if (proxy == nullptr) {
			throw invalid_argument("No Hdf Proxy has been found");
		}
		getRepository()->addRelationship(this, proxy);

		gsoap_resqml2_0_1::resqml20__IntegerHdf5Array* hdf5ChildCountPerInterval = gsoap_resqml2_0_1::soap_new_resqml20__IntegerHdf5Array(gsoapProxy2_0_1->soap);
		regrid->Intervals->ChildCountPerInterval = hdf5ChildCountPerInterval;
		hdf5ChildCountPerInterval->NullValue = (numeric_limits<unsigned int>::max)();
		hdf5ChildCountPerInterval->Values = gsoap_resqml2_0_1::soap_new_eml20__Hdf5Dataset(gsoapProxy2_0_1->soap);
		hdf5ChildCountPerInterval->Values->HdfProxy = proxy->newResqmlReference();
		hdf5ChildCountPerInterval->Values->PathInHdfFile = "/RESQML/" + gsoapProxy2_0_1->uuid + "/ParentWindow_" + dimension + "Regrid_ChildCountPerInterval";

		gsoap_resqml2_0_1::resqml20__IntegerHdf5Array* hdf5ParentCountPerInterval = gsoap_resqml2_0_1::soap_new_resqml20__IntegerHdf5Array(gsoapProxy2_0_1->soap);
		regrid->Intervals->ParentCountPerInterval = hdf5ParentCountPerInterval;
		hdf5ParentCountPerInterval->NullValue = (numeric_limits<unsigned int>::max)();
		hdf5ParentCountPerInterval->Values = gsoap_resqml2_0_1::soap_new_eml20__Hdf5Dataset(gsoapProxy2_0_1->soap);
		hdf5ParentCountPerInterval->Values->HdfProxy = proxy->newResqmlReference();
		hdf5ParentCountPerInterval->Values->PathInHdfFile = "/RESQML/" + gsoapProxy2_0_1->uuid + "/ParentWindow_" + dimension + "Regrid_ParentCountPerInterval";
		
		// HDF
		hsize_t numValues = intervalCount;
		proxy->writeArrayNd(gsoapProxy2_0_1->uuid, "ParentWindow_" + dimension + "Regrid_ChildCountPerInterval", H5T_NATIVE_UINT, childCellCountPerInterval, &numValues, 1);
		proxy->writeArrayNd(gsoapProxy2_0_1->uuid, "ParentWindow_" + dimension + "Regrid_ParentCountPerInterval", H5T_NATIVE_UINT, parentCellCountPerInterval, &numValues, 1);
	}
	
	if (childCellWeights != nullptr) {
		if (proxy == nullptr) {
			proxy = getRepository()->getDefaultHdfProxy();
		}
		if (proxy == nullptr) {
			throw invalid_argument("No Hdf Proxy has been found");
		}
		getRepository()->addRelationship(this, proxy);

		gsoap_resqml2_0_1::resqml20__DoubleHdf5Array* hdf5ChildCellWeights = gsoap_resqml2_0_1::soap_new_resqml20__DoubleHdf5Array(gsoapProxy2_0_1->soap);
		regrid->Intervals->ChildCellWeights = hdf5ChildCellWeights;
		hdf5ChildCellWeights->Values = gsoap_resqml2_0_1::soap_new_eml20__Hdf5Dataset(gsoapProxy2_0_1->soap);
		hdf5ChildCellWeights->Values->HdfProxy = proxy->newResqmlReference();
		hdf5ChildCellWeights->Values->PathInHdfFile = "/RESQML/" + gsoapProxy2_0_1->uuid + "/ParentWindow_" + dimension + "Regrid_ChildCellWeights";
		
		// HDF
		hsize_t numValues = 0;
		for (unsigned int i = 0; i < intervalCount; ++i) {
			numValues += childCellCountPerInterval[i];
		}
		proxy->writeArrayNdOfDoubleValues(gsoapProxy2_0_1->uuid, "ParentWindow_" + dimension + "Regrid_ChildCellWeights", childCellWeights, &numValues, 1);
	}

	return regrid;
}

void AbstractGridRepresentation::setParentWindow(ULONG64 * cellIndices, ULONG64 cellIndexCount, RESQML2_0_1_NS::UnstructuredGridRepresentation* parentGrid, COMMON_NS::AbstractHdfProxy * proxy)
{
	if (cellIndexCount == 0 || cellIndices == nullptr || parentGrid == nullptr) {
		throw invalid_argument("One of the mandatory method parameter is zero or null");
	}

	if (gsoapProxy2_0_1 != nullptr) {
		gsoap_resqml2_0_1::resqml20__AbstractGridRepresentation* rep = static_cast<gsoap_resqml2_0_1::resqml20__AbstractGridRepresentation*>(gsoapProxy2_0_1);

		gsoap_resqml2_0_1::resqml20__CellParentWindow* cpw = gsoap_resqml2_0_1::soap_new_resqml20__CellParentWindow(rep->soap);
		rep->ParentWindow = cpw;

		cpw->ParentGrid = parentGrid->newResqmlReference();
		if (cellIndexCount > 1) {

			if (proxy == nullptr) {
				proxy = getRepository()->getDefaultHdfProxy();
			}
			if (proxy == nullptr) {
				throw invalid_argument("No Hdf Proxy has been found");
			}
			getRepository()->addRelationship(this, proxy);

			gsoap_resqml2_0_1::resqml20__IntegerHdf5Array* hdf5CellIndices = gsoap_resqml2_0_1::soap_new_resqml20__IntegerHdf5Array(rep->soap);
			cpw->CellIndices = hdf5CellIndices;

			hdf5CellIndices->NullValue = (numeric_limits<ULONG64>::max)();
			hdf5CellIndices->Values = gsoap_resqml2_0_1::soap_new_eml20__Hdf5Dataset(rep->soap);
			hdf5CellIndices->Values->HdfProxy = proxy->newResqmlReference();
			hdf5CellIndices->Values->PathInHdfFile = "/RESQML/" + gsoapProxy2_0_1->uuid + "/ParentWindow_CellIndices";
		
			// HDF
			hsize_t numValues = cellIndexCount;
			proxy->writeArrayNdOfGSoapULong64Values(gsoapProxy2_0_1->uuid, "ParentWindow_CellIndices", cellIndices, &numValues, 1);
		}
		else { // cellIndexCount == 1
			gsoap_resqml2_0_1::resqml20__IntegerConstantArray* xmlCellIndices = gsoap_resqml2_0_1::soap_new_resqml20__IntegerConstantArray(rep->soap);
			xmlCellIndices->Value = *cellIndices;
			xmlCellIndices->Count = 1;
			cpw->CellIndices = xmlCellIndices;
		}
	}
	else {
		throw logic_error("Not implemented yet");
	}
	
	repository->addRelationship(this, parentGrid);
}

void AbstractGridRepresentation::setParentWindow(unsigned int * columnIndices, unsigned int columnIndexCount,
	unsigned int kLayerIndexRegridStart,
	unsigned int * childCellCountPerInterval, unsigned int * parentCellCountPerInterval, unsigned int intervalCount,
	AbstractColumnLayerGridRepresentation* parentGrid,
	COMMON_NS::AbstractHdfProxy * proxy, double * childCellWeights)
{
	if (columnIndexCount == 0 || columnIndices == nullptr ||
		childCellCountPerInterval == nullptr || parentCellCountPerInterval == nullptr || intervalCount == 0 || parentGrid == nullptr) {
		throw invalid_argument("One of the mandatory method parameter is zero or null");
	}

	if (gsoapProxy2_0_1 != nullptr) {
		gsoap_resqml2_0_1::resqml20__AbstractGridRepresentation* rep = static_cast<gsoap_resqml2_0_1::resqml20__AbstractGridRepresentation*>(gsoapProxy2_0_1);

		gsoap_resqml2_0_1::resqml20__ColumnLayerParentWindow* clpw = gsoap_resqml2_0_1::soap_new_resqml20__ColumnLayerParentWindow(rep->soap);
		rep->ParentWindow = clpw;

		clpw->ParentGrid = parentGrid->newResqmlReference();

		// COLUMN INDICES
		if (columnIndexCount > 1)
		{
			if (proxy == nullptr) {
				proxy = getRepository()->getDefaultHdfProxy();
			}
			if (proxy == nullptr) {
				throw invalid_argument("No Hdf Proxy has been found");
			}
			getRepository()->addRelationship(this, proxy);

			gsoap_resqml2_0_1::resqml20__IntegerHdf5Array* hdf5ColumnIndices = gsoap_resqml2_0_1::soap_new_resqml20__IntegerHdf5Array(rep->soap);
			clpw->ColumnIndices = hdf5ColumnIndices;

			hdf5ColumnIndices->NullValue = (numeric_limits<unsigned int>::max)();
			hdf5ColumnIndices->Values = gsoap_resqml2_0_1::soap_new_eml20__Hdf5Dataset(rep->soap);
			hdf5ColumnIndices->Values->HdfProxy = proxy->newResqmlReference();
			hdf5ColumnIndices->Values->PathInHdfFile = "/RESQML/" + gsoapProxy2_0_1->uuid + "/ParentWindow_ColumnIndices";

			// HDF
			hsize_t numValues = columnIndexCount;
			proxy->writeArrayNd(gsoapProxy2_0_1->uuid, "ParentWindow_ColumnIndices", H5T_NATIVE_UINT, columnIndices, &numValues, 1);
		}
		else if (columnIndexCount == 1)
		{
			gsoap_resqml2_0_1::resqml20__IntegerConstantArray* xmlColumnIndices = gsoap_resqml2_0_1::soap_new_resqml20__IntegerConstantArray(rep->soap);
			xmlColumnIndices->Value = *columnIndices;
			xmlColumnIndices->Count = 1;
			clpw->ColumnIndices = xmlColumnIndices;
		}

		// K Regrid
		clpw->KRegrid = createRegrid(kLayerIndexRegridStart, childCellCountPerInterval, parentCellCountPerInterval, intervalCount, childCellWeights, "K", proxy);
	}
	else {
		throw logic_error("Not implemented yet");
	}

	repository->addRelationship(this, parentGrid);
}

void AbstractGridRepresentation::setParentWindow(
	unsigned int iCellIndexRegridStart, unsigned int * childCellCountPerIInterval, unsigned int * parentCellCountPerIInterval, unsigned int iIntervalCount,
	unsigned int jCellIndexRegridStart, unsigned int * childCellCountPerJInterval, unsigned int * parentCellCountPerJInterval, unsigned int jIntervalCount,
	unsigned int kCellIndexRegridStart, unsigned int * childCellCountPerKInterval, unsigned int * parentCellCountPerKInterval, unsigned int kIntervalCount,
	RESQML2_0_1_NS::AbstractIjkGridRepresentation* parentGrid, COMMON_NS::AbstractHdfProxy * proxy, double * iChildCellWeights, double * jChildCellWeights, double * kChildCellWeights)
{
	if (childCellCountPerIInterval == nullptr || parentCellCountPerIInterval == nullptr || iIntervalCount == 0 ||
		childCellCountPerJInterval == nullptr || parentCellCountPerJInterval == nullptr || jIntervalCount == 0 ||
		childCellCountPerKInterval == nullptr || parentCellCountPerKInterval == nullptr || kIntervalCount == 0 ||
		parentGrid == nullptr) {
		throw invalid_argument("One of the mandatory method parameter is zero or null");
	}

	if (gsoapProxy2_0_1 != nullptr) {
		gsoap_resqml2_0_1::resqml20__AbstractGridRepresentation* rep = static_cast<gsoap_resqml2_0_1::resqml20__AbstractGridRepresentation*>(gsoapProxy2_0_1);

		gsoap_resqml2_0_1::resqml20__IjkParentWindow* ijkpw = gsoap_resqml2_0_1::soap_new_resqml20__IjkParentWindow(rep->soap);
		rep->ParentWindow = ijkpw;

		ijkpw->ParentGrid = parentGrid->newResqmlReference();
	
		// Regrids
		ijkpw->IRegrid = createRegrid(iCellIndexRegridStart, childCellCountPerIInterval, parentCellCountPerIInterval, iIntervalCount, iChildCellWeights, "I", proxy);
		ijkpw->JRegrid = createRegrid(jCellIndexRegridStart, childCellCountPerJInterval, parentCellCountPerJInterval, jIntervalCount, jChildCellWeights, "J", proxy);
		ijkpw->KRegrid = createRegrid(kCellIndexRegridStart, childCellCountPerKInterval, parentCellCountPerKInterval, kIntervalCount, kChildCellWeights, "K", proxy);
	}
	else {
		throw logic_error("Not implemented yet");
	}

	repository->addRelationship(this, parentGrid);
}

void AbstractGridRepresentation::setParentWindow(
	unsigned int iCellIndexRegridStart, unsigned int constantChildCellCountPerIInterval, unsigned int constantParentCellCountPerIInterval, unsigned int iIntervalCount,
	unsigned int jCellIndexRegridStart, unsigned int constantChildCellCountPerJInterval, unsigned int constantParentCellCountPerJInterval, unsigned int jIntervalCount,
	unsigned int kCellIndexRegridStart, unsigned int constantChildCellCountPerKInterval, unsigned int constantParentCellCountPerKInterval, unsigned int kIntervalCount,
	RESQML2_0_1_NS::AbstractIjkGridRepresentation* parentGrid, COMMON_NS::AbstractHdfProxy * proxy, double * iChildCellWeights, double * jChildCellWeights, double * kChildCellWeights)
{
	if (constantChildCellCountPerIInterval == 0 || constantParentCellCountPerIInterval == 0 || iIntervalCount == 0 ||
		constantChildCellCountPerJInterval == 0 || constantParentCellCountPerJInterval == 0 || jIntervalCount == 0 ||
		constantChildCellCountPerKInterval == 0 || constantParentCellCountPerKInterval == 0 || kIntervalCount == 0 ||
		parentGrid == nullptr) {
		throw invalid_argument("One of the mandatory method parameter is zero or null");
	}

	if (gsoapProxy2_0_1 != nullptr) {
		gsoap_resqml2_0_1::resqml20__AbstractGridRepresentation* rep = static_cast<gsoap_resqml2_0_1::resqml20__AbstractGridRepresentation*>(gsoapProxy2_0_1);

		gsoap_resqml2_0_1::resqml20__IjkParentWindow* ijkpw = gsoap_resqml2_0_1::soap_new_resqml20__IjkParentWindow(rep->soap);
		rep->ParentWindow = ijkpw;

		ijkpw->ParentGrid = parentGrid->newResqmlReference();

		// Regrids
		ijkpw->IRegrid = createRegrid(iCellIndexRegridStart, &constantChildCellCountPerIInterval, &constantParentCellCountPerIInterval, iIntervalCount, iChildCellWeights, "I", proxy, true);
		ijkpw->JRegrid = createRegrid(jCellIndexRegridStart, &constantChildCellCountPerJInterval, &constantParentCellCountPerJInterval, jIntervalCount, jChildCellWeights, "J", proxy, true);
		ijkpw->KRegrid = createRegrid(kCellIndexRegridStart, &constantChildCellCountPerKInterval, &constantParentCellCountPerKInterval, kIntervalCount, kChildCellWeights, "K", proxy, true);
	}
	else {
		throw logic_error("Not implemented yet");
	}

	repository->addRelationship(this, parentGrid);
}

void AbstractGridRepresentation::setParentWindow(
	unsigned int iCellIndexRegridStart, unsigned int iChildCellCount, unsigned int iParentCellCount,
	unsigned int jCellIndexRegridStart, unsigned int jChildCellCount, unsigned int jParentCellCount,
	unsigned int kCellIndexRegridStart, unsigned int kChildCellCount, unsigned int kParentCellCount,
	RESQML2_0_1_NS::AbstractIjkGridRepresentation* parentGrid, COMMON_NS::AbstractHdfProxy * proxy, double * iChildCellWeights, double * jChildCellWeights, double * kChildCellWeights)
{
	setParentWindow(
		iCellIndexRegridStart, &iChildCellCount, &iParentCellCount, 1,
		jCellIndexRegridStart, &jChildCellCount, &jParentCellCount, 1,
		kCellIndexRegridStart, &kChildCellCount, &kParentCellCount, 1,
		parentGrid, proxy, iChildCellWeights, jChildCellWeights, kChildCellWeights);
}

void AbstractGridRepresentation::setForcedNonRegridedParentCell(ULONG64 * cellIndices, const ULONG64 & cellIndexCount)
{
	if (gsoapProxy2_0_1 != nullptr) {
		gsoap_resqml2_0_1::resqml20__AbstractParentWindow* parentWindow = getParentWindow2_0_1();

		if (parentWindow != nullptr)
		{
			gsoap_resqml2_0_1::resqml20__AbstractIntegerArray* xmlCellIndices = nullptr;

			COMMON_NS::AbstractHdfProxy * proxy = getRepository()->getDefaultHdfProxy();
			if (cellIndexCount > 1 && proxy != nullptr)
			{
				getRepository()->addRelationship(this, proxy);
				xmlCellIndices = gsoap_resqml2_0_1::soap_new_resqml20__IntegerHdf5Array(parentWindow->soap);
				static_cast<gsoap_resqml2_0_1::resqml20__IntegerHdf5Array*>(xmlCellIndices)->NullValue = (numeric_limits<ULONG64>::max)();
				static_cast<gsoap_resqml2_0_1::resqml20__IntegerHdf5Array*>(xmlCellIndices)->Values = gsoap_resqml2_0_1::soap_new_eml20__Hdf5Dataset(parentWindow->soap);
				static_cast<gsoap_resqml2_0_1::resqml20__IntegerHdf5Array*>(xmlCellIndices)->Values->HdfProxy = proxy->newResqmlReference();
				static_cast<gsoap_resqml2_0_1::resqml20__IntegerHdf5Array*>(xmlCellIndices)->Values->PathInHdfFile = "/RESQML/" + gsoapProxy2_0_1->uuid + "/ParentWindow_CellIndices";
			
				// HDF
				hsize_t numValues = cellIndexCount;
				proxy->writeArrayNdOfGSoapULong64Values(gsoapProxy2_0_1->uuid, "ParentWindow_CellIndices", cellIndices, &numValues, 1);
			}
			else if (cellIndexCount == 1)
			{
				xmlCellIndices = gsoap_resqml2_0_1::soap_new_resqml20__IntegerConstantArray(parentWindow->soap);
				static_cast<gsoap_resqml2_0_1::resqml20__IntegerConstantArray*>(xmlCellIndices)->Value = *cellIndices;
				static_cast<gsoap_resqml2_0_1::resqml20__IntegerConstantArray*>(xmlCellIndices)->Count = 1;
			}
			else if (cellIndexCount == 0)
				throw invalid_argument("Cannot force an empty list of cells.");
			else
				throw invalid_argument("The HDF proxy is missing.");

			if (parentWindow->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__IjkParentWindow)
			{
				static_cast<gsoap_resqml2_0_1::resqml20__IjkParentWindow*>(parentWindow)->OmitParentCells = xmlCellIndices;
			}
			else if (parentWindow->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__ColumnLayerParentWindow)
			{
				static_cast<gsoap_resqml2_0_1::resqml20__ColumnLayerParentWindow*>(parentWindow)->OmitParentCells = xmlCellIndices;
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
		gsoap_resqml2_0_1::resqml20__AbstractParentWindow* parentWindow = getParentWindow2_0_1();

		if (parentWindow != nullptr) {
			if (parentWindow->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__IjkParentWindow) {
				return static_cast<gsoap_resqml2_0_1::resqml20__IjkParentWindow*>(parentWindow)->OmitParentCells != nullptr;
			}
			else if (parentWindow->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__ColumnLayerParentWindow) {
				return static_cast<gsoap_resqml2_0_1::resqml20__ColumnLayerParentWindow*>(parentWindow)->OmitParentCells != nullptr;
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
		gsoap_resqml2_0_1::resqml20__AbstractParentWindow* parentWindow = getParentWindow2_0_1();

		if (parentWindow != nullptr)
		{
			COMMON_NS::AbstractHdfProxy * proxy = getRepository()->getDefaultHdfProxy();
			if (parentChildCellPairCount > 0 && proxy != nullptr)
			{
				getRepository()->addRelationship(this, proxy);
				parentWindow->CellOverlap = gsoap_resqml2_0_1::soap_new_resqml20__CellOverlap(gsoapProxy2_0_1->soap);

				gsoap_resqml2_0_1::resqml20__IntegerHdf5Array* hdf5CellPairs = gsoap_resqml2_0_1::soap_new_resqml20__IntegerHdf5Array(parentWindow->soap);
				parentWindow->CellOverlap->__CellOverlap_sequence = gsoap_resqml2_0_1::soap_new___resqml20__CellOverlap_sequence(parentWindow->soap);
				parentWindow->CellOverlap->__CellOverlap_sequence->Count = parentChildCellPairCount;
				parentWindow->CellOverlap->__CellOverlap_sequence->ParentChildCellPairs = hdf5CellPairs;
				hdf5CellPairs->NullValue = (numeric_limits<ULONG64>::max)();
				hdf5CellPairs->Values = gsoap_resqml2_0_1::soap_new_eml20__Hdf5Dataset(parentWindow->soap);
				hdf5CellPairs->Values->HdfProxy = proxy->newResqmlReference();
				hdf5CellPairs->Values->PathInHdfFile = "/RESQML/" + gsoapProxy2_0_1->uuid + "/ParentWindow_CellOverlap";
		
				// HDF
				hsize_t numValues[] = {parentChildCellPairCount, 2};
				proxy->writeArrayNdOfGSoapULong64Values(gsoapProxy2_0_1->uuid, "ParentWindow_CellOverlap", parentChildCellPair, numValues, 2);
			}
			else if (parentChildCellPairCount == 0)
				throw invalid_argument("Cannot give cell overlap information with an empty list of cell pairs.");
			else
				throw invalid_argument("The HDF proxy is missing.");

			if (overlapVolumes != nullptr)
			{
				parentWindow->CellOverlap->__CellOverlap_sequence->OverlapVolume = gsoap_resqml2_0_1::soap_new_resqml20__OverlapVolume(parentWindow->soap);
				parentWindow->CellOverlap->__CellOverlap_sequence->OverlapVolume->__OverlapVolume_sequence = gsoap_resqml2_0_1::soap_new___resqml20__OverlapVolume_sequence(parentWindow->soap);
				parentWindow->CellOverlap->__CellOverlap_sequence->OverlapVolume->__OverlapVolume_sequence->VolumeUom = volumeUom;

				gsoap_resqml2_0_1::resqml20__DoubleHdf5Array* hdf5OverlapVolume = gsoap_resqml2_0_1::soap_new_resqml20__DoubleHdf5Array(parentWindow->soap);
				parentWindow->CellOverlap->__CellOverlap_sequence->OverlapVolume->__OverlapVolume_sequence->OverlapVolumes = hdf5OverlapVolume;
				hdf5OverlapVolume->Values = gsoap_resqml2_0_1::soap_new_eml20__Hdf5Dataset(parentWindow->soap);
				hdf5OverlapVolume->Values->HdfProxy = proxy->newResqmlReference();
				hdf5OverlapVolume->Values->PathInHdfFile = "/RESQML/" + gsoapProxy2_0_1->uuid + "/ParentWindow_OverlapVolume";
		
				// HDF
				hsize_t numValues = parentChildCellPairCount;
				proxy->writeArrayNdOfDoubleValues(gsoapProxy2_0_1->uuid, "ParentWindow_OverlapVolume", overlapVolumes, &numValues, 1);
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
		gsoap_resqml2_0_1::resqml20__AbstractParentWindow* parentWindow = getParentWindow2_0_1();

		if (parentWindow != nullptr)
		{
			if (parentWindow->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__CellParentWindow)
			{
				gsoap_resqml2_0_1::resqml20__CellParentWindow* cpw = static_cast<gsoap_resqml2_0_1::resqml20__CellParentWindow*>(parentWindow);
				if (cpw->CellIndices->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__IntegerHdf5Array)
				{
					gsoap_resqml2_0_1::eml20__Hdf5Dataset const * dataset = static_cast<gsoap_resqml2_0_1::resqml20__IntegerHdf5Array*>(cpw->CellIndices)->Values;
					COMMON_NS::AbstractHdfProxy * hdfProxy = getHdfProxyFromDataset(dataset);
					return hdfProxy->getElementCount(dataset->PathInHdfFile);
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
		gsoap_resqml2_0_1::resqml20__AbstractParentWindow* parentWindow = getParentWindow2_0_1();

		if (parentWindow != nullptr)
		{
			if (parentWindow->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__CellParentWindow)
			{
				gsoap_resqml2_0_1::resqml20__CellParentWindow* cpw = static_cast<gsoap_resqml2_0_1::resqml20__CellParentWindow*>(parentWindow);
				if (cpw->CellIndices->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__IntegerHdf5Array) {
					gsoap_resqml2_0_1::eml20__Hdf5Dataset const * dataset = static_cast<gsoap_resqml2_0_1::resqml20__IntegerHdf5Array*>(cpw->CellIndices)->Values;
					COMMON_NS::AbstractHdfProxy * hdfProxy = getHdfProxyFromDataset(dataset);
					hdfProxy->readArrayNdOfGSoapULong64Values(dataset->PathInHdfFile, parentCellIndices);
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
		gsoap_resqml2_0_1::resqml20__AbstractParentWindow* parentWindow = getParentWindow2_0_1();

		if (parentWindow != nullptr)
		{
			if (parentWindow->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__ColumnLayerParentWindow)
			{
				gsoap_resqml2_0_1::resqml20__ColumnLayerParentWindow* clpw = static_cast<gsoap_resqml2_0_1::resqml20__ColumnLayerParentWindow*>(parentWindow);
				if (clpw->ColumnIndices->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__IntegerHdf5Array) {
					gsoap_resqml2_0_1::eml20__Hdf5Dataset const * dataset = static_cast<gsoap_resqml2_0_1::resqml20__IntegerHdf5Array*>(clpw->ColumnIndices)->Values;
					COMMON_NS::AbstractHdfProxy * hdfProxy = getHdfProxyFromDataset(dataset);
					return hdfProxy->getElementCount(dataset->PathInHdfFile);
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
		gsoap_resqml2_0_1::resqml20__AbstractParentWindow* parentWindow = getParentWindow2_0_1();

		if (parentWindow != nullptr)
		{
			if (parentWindow->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__ColumnLayerParentWindow)
			{
				gsoap_resqml2_0_1::resqml20__ColumnLayerParentWindow* clpw = static_cast<gsoap_resqml2_0_1::resqml20__ColumnLayerParentWindow*>(parentWindow);
				if (clpw->ColumnIndices->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__IntegerHdf5Array) {
					gsoap_resqml2_0_1::eml20__Hdf5Dataset const * dataset = static_cast<gsoap_resqml2_0_1::resqml20__IntegerHdf5Array*>(clpw->ColumnIndices)->Values;
					COMMON_NS::AbstractHdfProxy * hdfProxy = getHdfProxyFromDataset(dataset);
					return hdfProxy->readArrayNdOfGSoapULong64Values(dataset->PathInHdfFile, parentColumnIndices);
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
		gsoap_resqml2_0_1::resqml20__AbstractParentWindow* parentWindow = getParentWindow2_0_1();

		if (parentWindow != nullptr)
		{
			if (parentWindow->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__IjkParentWindow)
			{
				if (dimension == 'i' || dimension == 'I')
				{
					return static_cast<gsoap_resqml2_0_1::resqml20__IjkParentWindow*>(parentWindow)->IRegrid->InitialIndexOnParentGrid;
				}
				else if (dimension == 'j' || dimension == 'J')
				{
					return static_cast<gsoap_resqml2_0_1::resqml20__IjkParentWindow*>(parentWindow)->JRegrid->InitialIndexOnParentGrid;
				}
				else if (dimension == 'k' || dimension == 'K')
				{
					return static_cast<gsoap_resqml2_0_1::resqml20__IjkParentWindow*>(parentWindow)->KRegrid->InitialIndexOnParentGrid;
				}
				else
					throw invalid_argument("Only i, j or k dimension can be accessed for an IJK Parent Window.");
			}
			else if (parentWindow->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__ColumnLayerParentWindow)
			{
				if (dimension == 'k' || dimension == 'K')
				{
					return static_cast<gsoap_resqml2_0_1::resqml20__ColumnLayerParentWindow*>(parentWindow)->KRegrid->InitialIndexOnParentGrid;
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
		gsoap_resqml2_0_1::resqml20__AbstractParentWindow* parentWindow = getParentWindow2_0_1();

		if (parentWindow != nullptr)
		{
			if (parentWindow->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__IjkParentWindow)
			{
				if (dimension == 'i' || dimension == 'I')
				{
					if (static_cast<gsoap_resqml2_0_1::resqml20__IjkParentWindow*>(parentWindow)->IRegrid->Intervals != nullptr)
						return static_cast<gsoap_resqml2_0_1::resqml20__IjkParentWindow*>(parentWindow)->IRegrid->Intervals->IntervalCount;
					else
						return 0;
				}
				else if (dimension == 'j' || dimension == 'J')
				{
					if (static_cast<gsoap_resqml2_0_1::resqml20__IjkParentWindow*>(parentWindow)->JRegrid->Intervals != nullptr)
						return static_cast<gsoap_resqml2_0_1::resqml20__IjkParentWindow*>(parentWindow)->JRegrid->Intervals->IntervalCount;
					else
						return 0;
				}
				else if (dimension == 'k' || dimension == 'K')
				{
					if (static_cast<gsoap_resqml2_0_1::resqml20__IjkParentWindow*>(parentWindow)->KRegrid->Intervals != nullptr)
						return static_cast<gsoap_resqml2_0_1::resqml20__IjkParentWindow*>(parentWindow)->KRegrid->Intervals->IntervalCount;
					else
						return 0;
				}
				else
					throw invalid_argument("Only i, j or k dimension can be accessed for an IJK Parent Window.");
			}
			else if (parentWindow->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__ColumnLayerParentWindow)
			{
				if (dimension == 'k' || dimension == 'K')
				{
					if (static_cast<gsoap_resqml2_0_1::resqml20__ColumnLayerParentWindow*>(parentWindow)->KRegrid->Intervals != nullptr)
						return static_cast<gsoap_resqml2_0_1::resqml20__ColumnLayerParentWindow*>(parentWindow)->KRegrid->Intervals->IntervalCount;
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

gsoap_resqml2_0_1::resqml20__AbstractIntegerArray* AbstractGridRepresentation::getCellCountPerInterval2_0_1(const char & dimension, const bool & childVsParentCellCount) const {
	if (gsoapProxy2_0_1 != nullptr) {
		gsoap_resqml2_0_1::resqml20__AbstractParentWindow* parentWindow = getParentWindow2_0_1();

		if (parentWindow != nullptr) {
			if (parentWindow->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__IjkParentWindow) {
				const gsoap_resqml2_0_1::resqml20__IjkParentWindow* const ijkpw = static_cast<const gsoap_resqml2_0_1::resqml20__IjkParentWindow* const>(parentWindow);
				const gsoap_resqml2_0_1::resqml20__Regrid* regrid = nullptr;
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
			else if (parentWindow->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__ColumnLayerParentWindow) {
				if (dimension == 'k' || dimension == 'K') {
					const gsoap_resqml2_0_1::resqml20__ColumnLayerParentWindow* const clpw = static_cast<const gsoap_resqml2_0_1::resqml20__ColumnLayerParentWindow* const>(parentWindow);
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
		gsoap_resqml2_0_1::resqml20__AbstractIntegerArray* cellCountPerInterval = getCellCountPerInterval2_0_1(dimension, childVsParentCellCount);
		if (cellCountPerInterval->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__IntegerConstantArray) {
			return true;
		}
		else if (cellCountPerInterval->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__IntegerHdf5Array) {
			const ULONG64 intervalCount = getRegridIntervalCount(dimension);
			ULONG64* values = new ULONG64[intervalCount];
			getRegridCellCountPerInterval(dimension, values, childVsParentCellCount);

			for (ULONG64 index = 1; index < intervalCount; ++index) {
				if (values[index] != values[0]) {
					delete[] values;
					return false;
				}
			}

			delete[] values;
			return true;
		}
		return false;
	}
	else {
		throw logic_error("Not implemented yet");
	}
}

ULONG64 AbstractGridRepresentation::getRegridConstantCellCountPerInterval(const char & dimension, const bool & childVsParentCellCount) const {
	if (gsoapProxy2_0_1 != nullptr) {
		const gsoap_resqml2_0_1::resqml20__AbstractIntegerArray* const cellCountPerInterval = getCellCountPerInterval2_0_1(dimension, childVsParentCellCount);
		if (cellCountPerInterval->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__IntegerConstantArray) {
			return static_cast<const gsoap_resqml2_0_1::resqml20__IntegerConstantArray* const>(cellCountPerInterval)->Value;
		}
		else if (cellCountPerInterval->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__IntegerHdf5Array) {
			const ULONG64 intervalCount = getRegridIntervalCount(dimension);
			ULONG64* values = new ULONG64[intervalCount];
			getRegridCellCountPerInterval(dimension, values, childVsParentCellCount);
			ULONG64 result = values[0];
			delete[] values;
			return result;
		}
		else {
			throw logic_error("Not implemented yet");
		}	
	}
	else {
		throw logic_error("Not implemented yet");
	}
}

void AbstractGridRepresentation::getRegridCellCountPerInterval(const char & dimension, ULONG64 * childCellCountPerInterval, const bool & childVsParentCellCount) const
{
	if (gsoapProxy2_0_1 != nullptr) {
		gsoap_resqml2_0_1::resqml20__AbstractIntegerArray const * childCountPerInterval = getCellCountPerInterval2_0_1(dimension, childVsParentCellCount);

		if (childCountPerInterval->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__IntegerConstantArray) {
			for (ULONG64 i = 0; i < static_cast<const gsoap_resqml2_0_1::resqml20__IntegerConstantArray* const>(childCountPerInterval)->Count; ++i) {
				childCellCountPerInterval[i] = static_cast<const gsoap_resqml2_0_1::resqml20__IntegerConstantArray* const>(childCountPerInterval)->Value;
			}
		}
		else if (childCountPerInterval->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__IntegerHdf5Array) {
			gsoap_resqml2_0_1::eml20__Hdf5Dataset const * dataset = static_cast<gsoap_resqml2_0_1::resqml20__IntegerHdf5Array const *>(childCountPerInterval)->Values;
			COMMON_NS::AbstractHdfProxy * hdfProxy = getHdfProxyFromDataset(dataset);
			hdfProxy->readArrayNdOfGSoapULong64Values(dataset->PathInHdfFile, childCellCountPerInterval);
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
		gsoap_resqml2_0_1::resqml20__AbstractParentWindow* parentWindow = getParentWindow2_0_1();

		if (parentWindow != nullptr) {
			if (parentWindow->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__IjkParentWindow)
			{
				gsoap_resqml2_0_1::resqml20__IjkParentWindow* ijkpw = static_cast<gsoap_resqml2_0_1::resqml20__IjkParentWindow*>(parentWindow);
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
			else if (parentWindow->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__ColumnLayerParentWindow)
			{
				if (dimension == 'k' || dimension == 'K')
				{
					gsoap_resqml2_0_1::resqml20__ColumnLayerParentWindow* clpw = static_cast<gsoap_resqml2_0_1::resqml20__ColumnLayerParentWindow*>(parentWindow);
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

void AbstractGridRepresentation::getRegridChildCellWeights(const char & dimension, double * childCellWeights) const
{
	if (gsoapProxy2_0_1 != nullptr) {
		gsoap_resqml2_0_1::resqml20__AbstractParentWindow* parentWindow = getParentWindow2_0_1();

		if (parentWindow != nullptr) {
			if (parentWindow->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__IjkParentWindow)
			{
				gsoap_resqml2_0_1::resqml20__IjkParentWindow* ijkpw = static_cast<gsoap_resqml2_0_1::resqml20__IjkParentWindow*>(parentWindow);
				if (dimension == 'i' || dimension == 'I')
				{
					if (ijkpw->IRegrid->Intervals != nullptr && ijkpw->IRegrid->Intervals->ChildCellWeights != nullptr)
					{
						if (ijkpw->IRegrid->Intervals->ChildCellWeights->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__DoubleHdf5Array) {
							gsoap_resqml2_0_1::eml20__Hdf5Dataset const * dataset = static_cast<gsoap_resqml2_0_1::resqml20__DoubleHdf5Array*>(ijkpw->IRegrid->Intervals->ChildCellWeights)->Values;
							COMMON_NS::AbstractHdfProxy * hdfProxy = getHdfProxyFromDataset(dataset);
							hdfProxy->readArrayNdOfDoubleValues(dataset->PathInHdfFile, childCellWeights);
						}
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
						if (ijkpw->JRegrid->Intervals->ChildCellWeights->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__DoubleHdf5Array) {
							gsoap_resqml2_0_1::eml20__Hdf5Dataset const * dataset = static_cast<gsoap_resqml2_0_1::resqml20__DoubleHdf5Array*>(ijkpw->JRegrid->Intervals->ChildCellWeights)->Values;
							COMMON_NS::AbstractHdfProxy * hdfProxy = getHdfProxyFromDataset(dataset);
							hdfProxy->readArrayNdOfDoubleValues(dataset->PathInHdfFile, childCellWeights);
						}
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
						if (ijkpw->KRegrid->Intervals->ChildCellWeights->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__DoubleHdf5Array) {
							gsoap_resqml2_0_1::eml20__Hdf5Dataset const * dataset = static_cast<gsoap_resqml2_0_1::resqml20__DoubleHdf5Array*>(ijkpw->KRegrid->Intervals->ChildCellWeights)->Values;
							COMMON_NS::AbstractHdfProxy * hdfProxy = getHdfProxyFromDataset(dataset);
							hdfProxy->readArrayNdOfDoubleValues(dataset->PathInHdfFile, childCellWeights);
						}
						else
							throw invalid_argument("ChildCellWeights should be in HDF5 file.");
					}
					else
						throw invalid_argument("No interval for K regrid.");
				}
				else
					throw invalid_argument("Only i, j or k dimension can be accessed for an IJK Parent Window.");
			}
			else if (parentWindow->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__ColumnLayerParentWindow)
			{
				if (dimension == 'k' || dimension == 'K')
				{
					gsoap_resqml2_0_1::resqml20__ColumnLayerParentWindow* clpw = static_cast<gsoap_resqml2_0_1::resqml20__ColumnLayerParentWindow*>(parentWindow);
					if (clpw->KRegrid->Intervals != nullptr  && clpw->KRegrid->Intervals->ChildCellWeights != nullptr)
					{
						if (clpw->KRegrid->Intervals->ChildCellWeights->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__DoubleHdf5Array) {
							gsoap_resqml2_0_1::eml20__Hdf5Dataset const * dataset = static_cast<gsoap_resqml2_0_1::resqml20__DoubleHdf5Array*>(clpw->KRegrid->Intervals->ChildCellWeights)->Values;
							COMMON_NS::AbstractHdfProxy * hdfProxy = getHdfProxyFromDataset(dataset);
							hdfProxy->readArrayNdOfDoubleValues(dataset->PathInHdfFile, childCellWeights);
						}
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

void AbstractGridRepresentation::loadTargetRelationships()
{
	AbstractRepresentation::loadTargetRelationships();

	// LGR backward relationships
	gsoap_resqml2_0_1::eml20__DataObjectReference const * dor = getParentGridDor();
	if (dor != nullptr) {
		RESQML2_NS::AbstractGridRepresentation* parentGrid = repository->getDataObjectByUuid<RESQML2_NS::AbstractGridRepresentation>(dor->UUID);
		if (parentGrid == nullptr) { // partial transfer
			getRepository()->createPartial(dor);
			parentGrid = getRepository()->getDataObjectByUuid<RESQML2_NS::AbstractGridRepresentation>(dor->UUID);
		}
		if (parentGrid == nullptr) {
			throw invalid_argument("The DOR looks invalid.");
		}
		repository->addRelationship(this, parentGrid);
	}
	// Strati org backward relationships
	dor = getStratigraphicOrganizationInterpretationDor();
	if (dor != nullptr) {
		RESQML2_0_1_NS::AbstractStratigraphicOrganizationInterpretation* stratiOrg = repository->getDataObjectByUuid<RESQML2_0_1_NS::AbstractStratigraphicOrganizationInterpretation>(dor->UUID);
		if (stratiOrg == nullptr) { // partial transfer
			getRepository()->createPartial(dor);
			stratiOrg = getRepository()->getDataObjectByUuid<RESQML2_0_1_NS::AbstractStratigraphicOrganizationInterpretation>(dor->UUID);
		}
		if (stratiOrg == nullptr) {
			throw invalid_argument("The DOR looks invalid.");
		}
		repository->addRelationship(this, stratiOrg);
	}

	dor = getRockFluidOrganizationInterpretationDor();
	if(dor != nullptr) {
		RESQML2_0_1_NS::RockFluidOrganizationInterpretation* rockFluidOrg = repository->getDataObjectByUuid<RESQML2_0_1_NS::RockFluidOrganizationInterpretation>(dor->UUID);
		if(rockFluidOrg == nullptr) {
			getRepository()->createPartial(dor);
			rockFluidOrg = getRepository()->getDataObjectByUuid<RESQML2_0_1_NS::RockFluidOrganizationInterpretation>(dor->UUID);
		}
		if(rockFluidOrg == nullptr) {
			throw invalid_argument("The DOR looks invalid.");
		}
		repository->addRelationship(this, rockFluidOrg);
	}
}

void AbstractGridRepresentation::setCellAssociationWithStratigraphicOrganizationInterpretation(ULONG64 * stratiUnitIndices, const ULONG64 & nullValue, RESQML2_0_1_NS::AbstractStratigraphicOrganizationInterpretation * stratiOrgInterp)
{
	if (gsoapProxy2_0_1 != nullptr) {
		gsoap_resqml2_0_1::resqml20__AbstractGridRepresentation* rep = static_cast<gsoap_resqml2_0_1::resqml20__AbstractGridRepresentation*>(gsoapProxy2_0_1);
		rep->CellStratigraphicUnits = gsoap_resqml2_0_1::soap_new_resqml20__CellStratigraphicUnits(rep->soap);
		rep->CellStratigraphicUnits->StratigraphicOrganization = stratiOrgInterp->newResqmlReference();

		COMMON_NS::AbstractHdfProxy * proxy = getRepository()->getDefaultHdfProxy();
		if (proxy == nullptr) {
			throw invalid_argument("The HDF proxy is missing.");
		}
		gsoap_resqml2_0_1::resqml20__IntegerHdf5Array* xmlDataset = gsoap_resqml2_0_1::soap_new_resqml20__IntegerHdf5Array(rep->soap);
		xmlDataset->NullValue = nullValue;
		xmlDataset->Values = gsoap_resqml2_0_1::soap_new_eml20__Hdf5Dataset(gsoapProxy2_0_1->soap);
		xmlDataset->Values->HdfProxy = proxy->newResqmlReference();
		xmlDataset->Values->PathInHdfFile = "/RESQML/" + rep->uuid + "/CellStratigraphicUnits";
		rep->CellStratigraphicUnits->UnitIndices = xmlDataset;

		// ************ HDF *************
		hsize_t dim = getCellCount();
		proxy->writeArrayNd(rep->uuid, "CellStratigraphicUnits", H5T_NATIVE_ULLONG, stratiUnitIndices, &dim, 1);
	}
	else {
		throw logic_error("Not implemented yet");
	}
}

void AbstractGridRepresentation::setCellAssociationWithRockFluidOrganizationInterpretation(ULONG64 * rockFluidUnitIndices, const ULONG64 & nullValue, RESQML2_0_1_NS::RockFluidOrganizationInterpretation * rockfluidOrgInterp)
{

	if (gsoapProxy2_0_1 != nullptr) {
		gsoap_resqml2_0_1::resqml20__AbstractGridRepresentation* rep = static_cast<gsoap_resqml2_0_1::resqml20__AbstractGridRepresentation*>(gsoapProxy2_0_1);
		rep->CellFluidPhaseUnits = gsoap_resqml2_0_1::soap_new_resqml20__CellFluidPhaseUnits(rep->soap);
		rep->CellFluidPhaseUnits->FluidOrganization = rockfluidOrgInterp->newResqmlReference();

		COMMON_NS::AbstractHdfProxy * proxy = getRepository()->getDefaultHdfProxy();
		if (proxy == nullptr) {
			throw invalid_argument("The HDF proxy is missing.");
		}
		gsoap_resqml2_0_1::resqml20__IntegerHdf5Array* xmlDataset = gsoap_resqml2_0_1::soap_new_resqml20__IntegerHdf5Array(rep->soap);
		xmlDataset->NullValue = nullValue;
		xmlDataset->Values = gsoap_resqml2_0_1::soap_new_eml20__Hdf5Dataset(gsoapProxy2_0_1->soap);
		xmlDataset->Values->HdfProxy = proxy->newResqmlReference();
		xmlDataset->Values->PathInHdfFile = "/RESQML/" + rep->uuid + "/CellFluidPhaseUnits";
		rep->CellFluidPhaseUnits->PhaseUnitIndices = xmlDataset;

		// ************ HDF *************
		hsize_t dim = getCellCount();
		proxy->writeArrayNd(rep->uuid, "CellFluidPhaseUnits", H5T_NATIVE_ULLONG, rockFluidUnitIndices, &dim, 1);
	}
	else {
		throw logic_error("Not implemented yet");
	}
}

gsoap_resqml2_0_1::eml20__DataObjectReference const * AbstractGridRepresentation::getStratigraphicOrganizationInterpretationDor() const
{
	if (!hasCellStratigraphicUnitIndices()) {
		return nullptr;
	}

	if (gsoapProxy2_0_1 != nullptr) {
		return static_cast<gsoap_resqml2_0_1::resqml20__AbstractGridRepresentation*>(gsoapProxy2_0_1)->CellStratigraphicUnits->StratigraphicOrganization;
	}
	else {
		throw logic_error("Not implemented yet");
	}
}

gsoap_resqml2_0_1::eml20__DataObjectReference const * AbstractGridRepresentation::getRockFluidOrganizationInterpretationDor() const
{
	if (!hasCellFluidPhaseUnitIndices()) {
		return nullptr;
	}

	if (gsoapProxy2_0_1 != nullptr) {
		return static_cast<gsoap_resqml2_0_1::resqml20__AbstractGridRepresentation*>(gsoapProxy2_0_1)->CellFluidPhaseUnits->FluidOrganization;
	}
	else {
		throw logic_error("Not implemented yet");
	}
}

std::string AbstractGridRepresentation::getStratigraphicOrganizationInterpretationUuid() const
{
	gsoap_resqml2_0_1::eml20__DataObjectReference const * dor = getStratigraphicOrganizationInterpretationDor();
	return dor == nullptr ? "" : dor->UUID;
}

std::string AbstractGridRepresentation::getStratigraphicOrganizationInterpretationTitle() const
{
	gsoap_resqml2_0_1::eml20__DataObjectReference const * dor = getStratigraphicOrganizationInterpretationDor();
	return dor == nullptr ? "" : dor->Title;
}

std::string AbstractGridRepresentation::getRockFluidOrganizationInterpretationUuid() const
{
	gsoap_resqml2_0_1::eml20__DataObjectReference const * dor = getRockFluidOrganizationInterpretationDor();
	return dor == nullptr ? "" : dor->UUID;
}

std::string AbstractGridRepresentation::getRockFluidOrganizationInterpretationTitle() const
{
	gsoap_resqml2_0_1::eml20__DataObjectReference const * dor = getRockFluidOrganizationInterpretationDor();
	return dor == nullptr ? "" : dor->Title;
}

RESQML2_0_1_NS::AbstractStratigraphicOrganizationInterpretation* AbstractGridRepresentation::getStratigraphicOrganizationInterpretation() const
{
	const string stratigraphicOrganizationInterpretationUuid = getStratigraphicOrganizationInterpretationUuid();
	if (stratigraphicOrganizationInterpretationUuid.empty()) {
		return nullptr;
	}

	return static_cast<RESQML2_0_1_NS::AbstractStratigraphicOrganizationInterpretation*>(getRepository()->getDataObjectByUuid(stratigraphicOrganizationInterpretationUuid));
}

bool AbstractGridRepresentation::hasCellStratigraphicUnitIndices() const
{
	if (gsoapProxy2_0_1 != nullptr) {
		return static_cast<gsoap_resqml2_0_1::resqml20__AbstractGridRepresentation*>(gsoapProxy2_0_1)->CellStratigraphicUnits != nullptr;
	}
	else {
		throw logic_error("Not implemented yet");
	}
}

bool AbstractGridRepresentation::hasCellFluidPhaseUnitIndices() const
{
	if (gsoapProxy2_0_1 != nullptr) {
		return static_cast<gsoap_resqml2_0_1::resqml20__AbstractGridRepresentation*>(gsoapProxy2_0_1)->CellFluidPhaseUnits != nullptr;
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
		gsoap_resqml2_0_1::resqml20__AbstractGridRepresentation* rep = static_cast<gsoap_resqml2_0_1::resqml20__AbstractGridRepresentation*>(gsoapProxy2_0_1);
		if (rep->CellStratigraphicUnits->UnitIndices->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__IntegerHdf5Array)
		{
			gsoap_resqml2_0_1::eml20__Hdf5Dataset const * dataset = static_cast<gsoap_resqml2_0_1::resqml20__IntegerHdf5Array*>(rep->CellStratigraphicUnits->UnitIndices)->Values;
			COMMON_NS::AbstractHdfProxy * hdfProxy = getHdfProxyFromDataset(dataset);
			hdfProxy->readArrayNdOfGSoapULong64Values(dataset->PathInHdfFile, stratiUnitIndices);
			return static_cast<gsoap_resqml2_0_1::resqml20__IntegerHdf5Array*>(rep->CellStratigraphicUnits->UnitIndices)->NullValue;
		}

		throw logic_error("Not implemented yet.");
	}
	else {
		throw logic_error("Not implemented yet");
	}
}

ULONG64 AbstractGridRepresentation::getCellFluidPhaseUnitIndices(ULONG64 * rockFluidUnitIndices)
{
	if (!hasCellFluidPhaseUnitIndices()) {
		throw invalid_argument("This grid has no CellFluidPhaseUnits information");
	}

	if (gsoapProxy2_0_1 != nullptr) {
		gsoap_resqml2_0_1::resqml20__AbstractGridRepresentation* rep = static_cast<gsoap_resqml2_0_1::resqml20__AbstractGridRepresentation*>(gsoapProxy2_0_1);
		if (rep->CellFluidPhaseUnits->PhaseUnitIndices->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__IntegerHdf5Array)
		{
			gsoap_resqml2_0_1::eml20__Hdf5Dataset const * dataset = static_cast<gsoap_resqml2_0_1::resqml20__IntegerHdf5Array*>(rep->CellFluidPhaseUnits->PhaseUnitIndices)->Values;
			COMMON_NS::AbstractHdfProxy * hdfProxy = getHdfProxyFromDataset(dataset);
			hdfProxy->readArrayNdOfGSoapULong64Values(dataset->PathInHdfFile, rockFluidUnitIndices);
			return static_cast<gsoap_resqml2_0_1::resqml20__IntegerHdf5Array*>(rep->CellFluidPhaseUnits->PhaseUnitIndices)->NullValue;
		}

		throw logic_error("Not implemented yet.");
	}
	else {
		throw logic_error("Not implemented yet");
	}
}

RESQML2_0_1_NS::RockFluidOrganizationInterpretation* AbstractGridRepresentation::getRockFluidOrganizationInterpretation() const
{
	const string rockfluidOrganizationInterpretationUuid = getRockFluidOrganizationInterpretationUuid();
	if (rockfluidOrganizationInterpretationUuid.empty()) {
		return nullptr;
	}

	return static_cast<RESQML2_0_1_NS::RockFluidOrganizationInterpretation*>(getRepository()->getDataObjectByUuid(rockfluidOrganizationInterpretationUuid));

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
		gsoap_resqml2_0_1::resqml20__AbstractTruncatedColumnLayerGridRepresentation* rep = static_cast<gsoap_resqml2_0_1::resqml20__AbstractTruncatedColumnLayerGridRepresentation*>(gsoapProxy2_0_1);
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
		gsoap_resqml2_0_1::resqml20__AbstractTruncatedColumnLayerGridRepresentation* rep = static_cast<gsoap_resqml2_0_1::resqml20__AbstractTruncatedColumnLayerGridRepresentation*>(gsoapProxy2_0_1);

		if (rep->TruncationCells->NodesPerTruncationFace->Elements->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__IntegerHdf5Array)
		{
			gsoap_resqml2_0_1::eml20__Hdf5Dataset const * dataset = static_cast<gsoap_resqml2_0_1::resqml20__IntegerHdf5Array*>(rep->TruncationCells->NodesPerTruncationFace->Elements)->Values;
			COMMON_NS::AbstractHdfProxy * hdfProxy = getHdfProxyFromDataset(dataset);
			hdfProxy->readArrayNdOfGSoapULong64Values(dataset->PathInHdfFile, nodeIndices);
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
		gsoap_resqml2_0_1::resqml20__AbstractTruncatedColumnLayerGridRepresentation* rep = static_cast<gsoap_resqml2_0_1::resqml20__AbstractTruncatedColumnLayerGridRepresentation*>(gsoapProxy2_0_1);

		if (rep->TruncationCells->NodesPerTruncationFace->CumulativeLength->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__IntegerHdf5Array)
		{
			gsoap_resqml2_0_1::eml20__Hdf5Dataset const * dataset = static_cast<gsoap_resqml2_0_1::resqml20__IntegerHdf5Array*>(rep->TruncationCells->NodesPerTruncationFace->CumulativeLength)->Values;
			COMMON_NS::AbstractHdfProxy * hdfProxy = getHdfProxyFromDataset(dataset);
			hdfProxy->readArrayNdOfGSoapULong64Values(dataset->PathInHdfFile, nodeCountPerFace);
		}
		else if (rep->TruncationCells->NodesPerTruncationFace->CumulativeLength->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__IntegerLatticeArray)
		{
			nodeCountPerFace[0] = static_cast<gsoap_resqml2_0_1::resqml20__IntegerLatticeArray*>(rep->TruncationCells->NodesPerTruncationFace->CumulativeLength)->StartValue;
			const LONG64 offsetValue = static_cast<gsoap_resqml2_0_1::resqml20__IntegerLatticeArray*>(rep->TruncationCells->NodesPerTruncationFace->CumulativeLength)->Offset[0]->Value;
			const ULONG64 faceCount = getTruncatedFaceCount();
			for (ULONG64 nodeCountPerFaceIndex = 1; nodeCountPerFaceIndex < faceCount; ++nodeCountPerFaceIndex) {
				nodeCountPerFace[nodeCountPerFaceIndex] = nodeCountPerFace[nodeCountPerFaceIndex - 1] + offsetValue;
			}
		}
		else if (rep->TruncationCells->NodesPerTruncationFace->CumulativeLength->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__IntegerConstantArray)
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
		gsoap_resqml2_0_1::resqml20__AbstractTruncatedColumnLayerGridRepresentation* rep = static_cast<gsoap_resqml2_0_1::resqml20__AbstractTruncatedColumnLayerGridRepresentation*>(gsoapProxy2_0_1);
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
		gsoap_resqml2_0_1::resqml20__AbstractTruncatedColumnLayerGridRepresentation* rep = static_cast<gsoap_resqml2_0_1::resqml20__AbstractTruncatedColumnLayerGridRepresentation*>(gsoapProxy2_0_1);

		if (rep->TruncationCells->ParentCellIndices->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__IntegerHdf5Array)
		{
			gsoap_resqml2_0_1::eml20__Hdf5Dataset const * dataset = static_cast<gsoap_resqml2_0_1::resqml20__IntegerHdf5Array*>(rep->TruncationCells->ParentCellIndices)->Values;
			COMMON_NS::AbstractHdfProxy * hdfProxy = getHdfProxyFromDataset(dataset);
			hdfProxy->readArrayNdOfGSoapULong64Values(dataset->PathInHdfFile, cellIndices);
		}
		else if (rep->TruncationCells->ParentCellIndices->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__IntegerConstantArray)
		{
			for (size_t i = 0; i < static_cast<gsoap_resqml2_0_1::resqml20__IntegerConstantArray*>(rep->TruncationCells->ParentCellIndices)->Count; ++i)
			{
				cellIndices[i] = static_cast<gsoap_resqml2_0_1::resqml20__IntegerConstantArray*>(rep->TruncationCells->ParentCellIndices)->Value;
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
		gsoap_resqml2_0_1::resqml20__AbstractTruncatedColumnLayerGridRepresentation* rep = static_cast<gsoap_resqml2_0_1::resqml20__AbstractTruncatedColumnLayerGridRepresentation*>(gsoapProxy2_0_1);

		if (rep->TruncationCells->TruncationFacesPerCell->Elements->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__IntegerHdf5Array)
		{
			gsoap_resqml2_0_1::eml20__Hdf5Dataset const * dataset = static_cast<gsoap_resqml2_0_1::resqml20__IntegerHdf5Array*>(rep->TruncationCells->TruncationFacesPerCell->Elements)->Values;
			COMMON_NS::AbstractHdfProxy * hdfProxy = getHdfProxyFromDataset(dataset);
			hdfProxy->readArrayNdOfGSoapULong64Values(dataset->PathInHdfFile, faceIndices);
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
		gsoap_resqml2_0_1::resqml20__AbstractTruncatedColumnLayerGridRepresentation* rep = static_cast<gsoap_resqml2_0_1::resqml20__AbstractTruncatedColumnLayerGridRepresentation*>(gsoapProxy2_0_1);

		if (rep->TruncationCells->TruncationFacesPerCell->CumulativeLength->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__IntegerHdf5Array)
		{
			gsoap_resqml2_0_1::eml20__Hdf5Dataset const * dataset = static_cast<gsoap_resqml2_0_1::resqml20__IntegerHdf5Array*>(rep->TruncationCells->TruncationFacesPerCell->CumulativeLength)->Values;
			COMMON_NS::AbstractHdfProxy * hdfProxy = getHdfProxyFromDataset(dataset);
			hdfProxy->readArrayNdOfGSoapULong64Values(dataset->PathInHdfFile, cumulativeFaceCountPerCell);
		}
		else if (rep->TruncationCells->TruncationFacesPerCell->CumulativeLength->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__IntegerLatticeArray)
		{
			cumulativeFaceCountPerCell[0] = static_cast<gsoap_resqml2_0_1::resqml20__IntegerLatticeArray*>(rep->TruncationCells->TruncationFacesPerCell->CumulativeLength)->StartValue;
			const LONG64 offsetValue = static_cast<gsoap_resqml2_0_1::resqml20__IntegerLatticeArray*>(rep->TruncationCells->TruncationFacesPerCell->CumulativeLength)->Offset[0]->Value;
			const ULONG64 cellCount = getTruncatedCellCount();
			for (ULONG64 cumulativeFaceCountPerCellIndex = 1; cumulativeFaceCountPerCellIndex < cellCount; ++cumulativeFaceCountPerCellIndex)
			{
				cumulativeFaceCountPerCell[cumulativeFaceCountPerCellIndex] = cumulativeFaceCountPerCell[cumulativeFaceCountPerCellIndex - 1] + offsetValue;
			}
		}
		else if (rep->TruncationCells->TruncationFacesPerCell->CumulativeLength->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__IntegerConstantArray)
		{
			if (getTruncatedCellCount() > 1)
				throw range_error("The cumulative length of faces count per cells cannot be constant if there is more than one cell in the grid");
			cumulativeFaceCountPerCell[0] = static_cast<gsoap_resqml2_0_1::resqml20__IntegerConstantArray*>(rep->TruncationCells->TruncationFacesPerCell->CumulativeLength)->Value;
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
		gsoap_resqml2_0_1::resqml20__AbstractTruncatedColumnLayerGridRepresentation* rep = static_cast<gsoap_resqml2_0_1::resqml20__AbstractTruncatedColumnLayerGridRepresentation*>(gsoapProxy2_0_1);

		if (rep->TruncationCells->LocalFacesPerCell->Elements->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__IntegerHdf5Array)
		{
			gsoap_resqml2_0_1::eml20__Hdf5Dataset const * dataset = static_cast<gsoap_resqml2_0_1::resqml20__IntegerHdf5Array*>(rep->TruncationCells->LocalFacesPerCell->Elements)->Values;
			COMMON_NS::AbstractHdfProxy * hdfProxy = getHdfProxyFromDataset(dataset);
			hdfProxy->readArrayNdOfGSoapULong64Values(dataset->PathInHdfFile, faceIndices);
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
		gsoap_resqml2_0_1::resqml20__AbstractTruncatedColumnLayerGridRepresentation* rep = static_cast<gsoap_resqml2_0_1::resqml20__AbstractTruncatedColumnLayerGridRepresentation*>(gsoapProxy2_0_1);

		if (rep->TruncationCells->LocalFacesPerCell->CumulativeLength->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__IntegerHdf5Array)
		{
			gsoap_resqml2_0_1::eml20__Hdf5Dataset const * dataset = static_cast<gsoap_resqml2_0_1::resqml20__IntegerHdf5Array*>(rep->TruncationCells->LocalFacesPerCell->CumulativeLength)->Values;
			COMMON_NS::AbstractHdfProxy * hdfProxy = getHdfProxyFromDataset(dataset);
			hdfProxy->readArrayNdOfGSoapULong64Values(dataset->PathInHdfFile, cumulativeFaceCountPerCell);
		}
		else if (rep->TruncationCells->LocalFacesPerCell->CumulativeLength->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__IntegerLatticeArray)
		{
			cumulativeFaceCountPerCell[0] = static_cast<gsoap_resqml2_0_1::resqml20__IntegerLatticeArray*>(rep->TruncationCells->LocalFacesPerCell->CumulativeLength)->StartValue;
			const LONG64 offsetValue = static_cast<gsoap_resqml2_0_1::resqml20__IntegerLatticeArray*>(rep->TruncationCells->LocalFacesPerCell->CumulativeLength)->Offset[0]->Value;
			const ULONG64 cellCount = getTruncatedCellCount();
			for (ULONG64 cumulativeFaceCountPerCellIndex = 1; cumulativeFaceCountPerCellIndex < cellCount; ++cumulativeFaceCountPerCellIndex)
			{
				cumulativeFaceCountPerCell[cumulativeFaceCountPerCellIndex] = cumulativeFaceCountPerCell[cumulativeFaceCountPerCellIndex - 1] + offsetValue;
			}
		}
		else if (rep->TruncationCells->LocalFacesPerCell->CumulativeLength->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__IntegerConstantArray)
		{
			if (getTruncatedCellCount() > 1)
				throw range_error("The cumulative length of faces count per cells cannot be constant if there is more than one cell in the grid");
			cumulativeFaceCountPerCell[0] = static_cast<gsoap_resqml2_0_1::resqml20__IntegerConstantArray*>(rep->TruncationCells->LocalFacesPerCell->CumulativeLength)->Value;
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
		gsoap_resqml2_0_1::resqml20__AbstractTruncatedColumnLayerGridRepresentation* rep = static_cast<gsoap_resqml2_0_1::resqml20__AbstractTruncatedColumnLayerGridRepresentation*>(gsoapProxy2_0_1);

		if (rep->TruncationCells->TruncationCellFaceIsRightHanded->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__BooleanHdf5Array)
		{
			gsoap_resqml2_0_1::eml20__Hdf5Dataset const * dataset = static_cast<gsoap_resqml2_0_1::resqml20__BooleanHdf5Array*>(rep->TruncationCells->TruncationCellFaceIsRightHanded)->Values;
			COMMON_NS::AbstractHdfProxy * hdfProxy = getHdfProxyFromDataset(dataset);
			hdfProxy->readArrayNdOfUCharValues(dataset->PathInHdfFile, cellFaceIsRightHanded);
		}
		else if (rep->TruncationCells->TruncationCellFaceIsRightHanded->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__BooleanConstantArray)
		{
			for (size_t i = 0; i < static_cast<gsoap_resqml2_0_1::resqml20__BooleanConstantArray*>(rep->TruncationCells->TruncationCellFaceIsRightHanded)->Count; ++i)
			{
				cellFaceIsRightHanded[i] = static_cast<gsoap_resqml2_0_1::resqml20__BooleanConstantArray*>(rep->TruncationCells->TruncationCellFaceIsRightHanded)->Value;
			}
		}
		else
			throw logic_error("Not yet implemented.");
	}
	else {
		throw logic_error("Not implemented yet");
	}
}
