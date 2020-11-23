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
#include "IjkGridParametricRepresentation.h"

#include <limits>
#include <stdexcept>

#include <hdf5.h>

#include "../resqml2/AbstractFeatureInterpretation.h"
#include "../resqml2/AbstractLocal3dCrs.h"
#include "../resqml2/AbstractValuesProperty.h"
#include "../eml2/AbstractHdfProxy.h"

using namespace std;
using namespace gsoap_resqml2_0_1;
using namespace RESQML2_0_1_NS;

const char* IjkGridParametricRepresentation::XML_NS = "resqml20";

unsigned int IjkGridParametricRepresentation::getControlPointMaxCountPerPillar() const
{
	gsoap_resqml2_0_1::resqml20__PointGeometry* geom = getPointGeometry2_0_1(0);
	if (geom == nullptr) {
		throw invalid_argument("There is no geometry on this grid.");
	}
	resqml20__Point3dParametricArray* points = static_cast<resqml20__Point3dParametricArray*>(geom->Points);
	if (points->ParametricLines->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__ParametricLineArray) {
		const ULONG64 result = static_cast<resqml20__ParametricLineArray*>(points->ParametricLines)->KnotCount;
		if (result > (std::numeric_limits<unsigned int>::max)())
			throw std::range_error("There are too many knot counts");
		return static_cast<unsigned int>(result);
	}

	throw std::logic_error("Not yet implemented");
}

bool IjkGridParametricRepresentation::hasControlPointParameters() const
{
	gsoap_resqml2_0_1::resqml20__PointGeometry* geom = getPointGeometry2_0_1(0);
	if (geom == nullptr) {
		throw invalid_argument("There is no geometry on this grid.");
	}
	resqml20__Point3dParametricArray* points = static_cast<resqml20__Point3dParametricArray*>(geom->Points);
	if (points->ParametricLines->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__ParametricLineArray)
	{
		resqml20__ParametricLineArray* paramLineArray = static_cast<resqml20__ParametricLineArray*>(points->ParametricLines);
		return paramLineArray->ControlPointParameters != nullptr;
	}
	else
		throw std::logic_error("Not yet implemented");
}

bool IjkGridParametricRepresentation::isParametricLineKindConstant() const
{
	gsoap_resqml2_0_1::resqml20__PointGeometry* geom = getPointGeometry2_0_1(0);
	if (geom == nullptr) {
		throw invalid_argument("There is no geometry on this grid.");
	}
	resqml20__Point3dParametricArray* points = static_cast<resqml20__Point3dParametricArray*>(geom->Points);
	if (points->ParametricLines->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__ParametricLineArray)
	{
		resqml20__ParametricLineArray* paramLineArray = static_cast<resqml20__ParametricLineArray*>(points->ParametricLines);
		if (paramLineArray->LineKindIndices->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__IntegerLatticeArray)
		{
			if (static_cast<resqml20__IntegerLatticeArray*>(paramLineArray->LineKindIndices)->Offset[0]->Count == 0)
				return true;
		}
		else if (paramLineArray->LineKindIndices->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__IntegerConstantArray)
		{
			return true;
		}
		else if (paramLineArray->LineKindIndices->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__IntegerHdf5Array)
		{
			eml20__Hdf5Dataset const * dataset = static_cast<resqml20__IntegerHdf5Array*>(paramLineArray->LineKindIndices)->Values;
			EML2_NS::AbstractHdfProxy * hdfProxy = getHdfProxyFromDataset(dataset);
			if (getPillarCount() != hdfProxy->getElementCount(dataset->PathInHdfFile)) {
				throw std::logic_error("Size difference between values count in hdf and pillars count");
			}
			std::unique_ptr<short[]> pillarKind(new short[getPillarCount()]);
			hdfProxy->readArrayNdOfShortValues(dataset->PathInHdfFile, pillarKind.get());
			short firstPillarKind = pillarKind[0];
			size_t pillarIndex = 0;
			while (pillarIndex < getPillarCount()) {
				if (pillarKind[pillarIndex] != firstPillarKind) {
					return false;
				}
				++pillarIndex;
			}
			return true;
		}
		else
			throw std::logic_error("Not yet implemented");
	}
	else
		throw std::logic_error("This ijk grid should be a parametric one but does not look like a parametric one.");

	return false;
}

short IjkGridParametricRepresentation::getConstantParametricLineKind() const
{
	if (!isParametricLineKindConstant()) {
		throw invalid_argument("The parametric line kind is not constant.");
	}

	gsoap_resqml2_0_1::resqml20__PointGeometry* geom = getPointGeometry2_0_1(0);
	if (geom == nullptr) {
		throw invalid_argument("There is no geometry on this grid.");
	}
	resqml20__Point3dParametricArray* points = static_cast<resqml20__Point3dParametricArray*>(geom->Points);
	if (points->ParametricLines->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__ParametricLineArray)
	{
		resqml20__ParametricLineArray* paramLineArray = static_cast<resqml20__ParametricLineArray*>(points->ParametricLines);
		if (paramLineArray->LineKindIndices->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__IntegerLatticeArray) {
			LONG64 result = static_cast<resqml20__IntegerLatticeArray*>(paramLineArray->LineKindIndices)->StartValue;
			if (result > (std::numeric_limits<short>::max)()) {
				throw std::range_error("The constant parametric line kind is not a short one.");
			}
			return static_cast<short>(result);
		}
		else if (paramLineArray->LineKindIndices->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__IntegerConstantArray) {
			LONG64 result = static_cast<resqml20__IntegerConstantArray*>(paramLineArray->LineKindIndices)->Value;
			if (result > (std::numeric_limits<short>::max)()) {
				throw std::range_error("The constant parametric line kind is not a short one.");
			}
			return static_cast<short>(result);
		}
		else if (paramLineArray->LineKindIndices->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__IntegerHdf5Array) {
			eml20__Hdf5Dataset const * dataset = static_cast<resqml20__IntegerHdf5Array*>(paramLineArray->LineKindIndices)->Values;
			EML2_NS::AbstractHdfProxy * hdfProxy = getHdfProxyFromDataset(dataset);
			std::unique_ptr<short[]> pillarKind(new short[getPillarCount()]);
			hdfProxy->readArrayNdOfShortValues(dataset->PathInHdfFile, pillarKind.get());
			return pillarKind[0];
		}
		else {
			throw std::logic_error("Not yet implemented");
		}
	}

	throw std::logic_error("This ijk grid should be a parametric one but does not look like a parametric one.");
}


void IjkGridParametricRepresentation::getRawParametricLineKind(short * pillarKind) const
{
	gsoap_resqml2_0_1::resqml20__PointGeometry* geom = getPointGeometry2_0_1(0);
	if (geom == nullptr) {
		throw invalid_argument("There is no geometry on this grid.");
	}
	resqml20__Point3dParametricArray* points = static_cast<resqml20__Point3dParametricArray*>(geom->Points);
	if (points->ParametricLines->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__ParametricLineArray)
	{
		resqml20__ParametricLineArray* paramLineArray = static_cast<resqml20__ParametricLineArray*>(points->ParametricLines);
		if (paramLineArray->LineKindIndices->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__IntegerHdf5Array)
		{
			eml20__Hdf5Dataset const * dataset = static_cast<resqml20__IntegerHdf5Array*>(paramLineArray->LineKindIndices)->Values;
			EML2_NS::AbstractHdfProxy * hdfProxy = getHdfProxyFromDataset(dataset);
			hdfProxy->readArrayNdOfShortValues(dataset->PathInHdfFile, pillarKind);
		}
		else if (paramLineArray->LineKindIndices->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__IntegerConstantArray)
		{
			const LONG64 value = static_cast<resqml20__IntegerConstantArray*>(paramLineArray->LineKindIndices)->Value;
			const ULONG64 lineKindCount = static_cast<resqml20__IntegerConstantArray*>(paramLineArray->LineKindIndices)->Count;
			if( lineKindCount != getPillarCount() ) {
				throw invalid_argument("The parametric line kind count is inconsistent with the pillar count.");
			}
			for (ULONG64 i = 0; i < lineKindCount; ++i) {
				pillarKind[i] = (short)value;
			}
		}
		else
			throw std::logic_error("Not yet implemented");
	}
	else
		throw std::logic_error("Not yet implemented");
}

COMMON_NS::DataObjectReference IjkGridParametricRepresentation::getHdfProxyDor() const
{
	gsoap_resqml2_0_1::resqml20__PointGeometry* geom = getPointGeometry2_0_1(0);
	if (geom == nullptr) {
		throw invalid_argument("There is no geometry on this grid.");
	}
	resqml20__Point3dParametricArray* points = static_cast<resqml20__Point3dParametricArray*>(geom->Points);
	if (points->Parameters->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__DoubleHdf5Array)
	{
		return COMMON_NS::DataObjectReference(static_cast<resqml20__DoubleHdf5Array*>(points->Parameters)->Values->HdfProxy);
	}
	else
		throw std::logic_error("Not yet implemented");
}

void IjkGridParametricRepresentation::getXyzPointsOfPatch(unsigned int patchIndex, double * xyzPoints) const
{
	getXyzPointsFromParametricPoints(xyzPoints);

	// Truncation
	if (isTruncated()) {
		gsoap_resqml2_0_1::resqml20__PointGeometry* geom = getPointGeometry2_0_1(0);
		if (geom == nullptr) {
			throw logic_error("There is no geometry on this grid.");
		}

		resqml20__AbstractGridGeometry* truncatedGeom = static_cast<gsoap_resqml2_0_1::resqml20__AbstractGridGeometry*>(geom);
		if (truncatedGeom->AdditionalGridPoints.size() == 1 && truncatedGeom->AdditionalGridPoints[0]->Attachment == resqml20__GridGeometryAttachment__nodes) {
			if (truncatedGeom->AdditionalGridPoints[0]->Points->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__Point3dHdf5Array)
			{
				eml20__Hdf5Dataset const * xmlDataset = static_cast<resqml20__Point3dHdf5Array*>(truncatedGeom->AdditionalGridPoints[0]->Points)->Coordinates;
				EML2_NS::AbstractHdfProxy * hdfProxy = getHdfProxyFromDataset(xmlDataset);
				xyzPoints += getXyzPointCountOfPatch(patchIndex) - static_cast<gsoap_resqml2_0_1::_resqml20__TruncatedIjkGridRepresentation*>(gsoapProxy2_0_1)->TruncationCells->TruncationNodeCount;
				hdfProxy->readArrayNdOfDoubleValues(xmlDataset->PathInHdfFile, xyzPoints);
			}
			else {
				throw logic_error("The additional grid points must be explicit ones for now. Parametric additional points are not supported yet for example.");
			}
		}
		else {
			throw logic_error("The truncated geometry must have one additional grid points construct (more than one is not implemented in fesapi yet although allowed by the standard). The attachment of this grid points must be set to node.");
		}
	}
}

void IjkGridParametricRepresentation::setGeometryAsParametricSplittedPillarNodes(
	gsoap_resqml2_0_1::resqml20__PillarShape mostComplexPillarGeometry, bool isRightHanded,
	double const * parameters, double const * controlPoints, double const * controlPointParameters, unsigned int controlPointMaxCountPerPillar, short const * pillarKind, EML2_NS::AbstractHdfProxy * proxy,
	unsigned long splitCoordinateLineCount, unsigned int const * pillarOfCoordinateLine,
	unsigned int const * splitCoordinateLineColumnCumulativeCount, unsigned int const * splitCoordinateLineColumns, RESQML2_NS::AbstractLocal3dCrs * localCrs)
{
	if (pillarKind == nullptr) {
		throw invalid_argument("The kind of the coordinate lines cannot be null.");
	}
	if (localCrs == nullptr) {
		localCrs = getRepository()->getDefaultCrs();
		if (localCrs == nullptr) {
			throw std::invalid_argument("A (default) CRS must be provided.");
		}
	}
	if (proxy == nullptr) {
		proxy = getRepository()->getDefaultHdfProxy();
		if (proxy == nullptr) {
			throw std::invalid_argument("A (default) HDF Proxy must be provided.");
		}
	}

	gsoap_resqml2_0_1::resqml20__KDirection kDirectionKind = computeKDirection(controlPoints, controlPointMaxCountPerPillar, pillarKind, localCrs);

	const std::string hdfDatasetPrefix = getHdfGroup();
	setGeometryAsParametricSplittedPillarNodesWithoutPillarKindUsingExistingDatasets(kDirectionKind, isRightHanded,
		hdfDatasetPrefix + "/PointParameters", hdfDatasetPrefix + "/ControlPoints", controlPointParameters != nullptr ? hdfDatasetPrefix + "/controlPointParameters" : "", controlPointMaxCountPerPillar, proxy,
		splitCoordinateLineCount, hdfDatasetPrefix + "/PillarIndices",
		hdfDatasetPrefix + "/ColumnsPerSplitCoordinateLine/" + CUMULATIVE_LENGTH_DS_NAME, hdfDatasetPrefix + "/ColumnsPerSplitCoordinateLine/" + ELEMENTS_DS_NAME, localCrs);

	writeGeometryOnHdf(parameters,
		controlPoints, controlPointParameters, controlPointMaxCountPerPillar,
		splitCoordinateLineCount, pillarOfCoordinateLine,
		splitCoordinateLineColumnCumulativeCount, splitCoordinateLineColumns, proxy);

	gsoap_resqml2_0_1::resqml20__IjkGridGeometry* geom = static_cast<gsoap_resqml2_0_1::resqml20__IjkGridGeometry*>(getPointGeometry2_0_1(0));
	if (geom == nullptr) {
		throw invalid_argument("There is no geometry on this grid.");
	}
	geom->PillarShape = mostComplexPillarGeometry;

	// XML Pillar defined
	resqml20__BooleanHdf5Array* xmlDefinedPillars = soap_new_resqml20__BooleanHdf5Array(gsoapProxy2_0_1->soap);
	geom->PillarGeometryIsDefined = xmlDefinedPillars;
	xmlDefinedPillars->Values = soap_new_eml20__Hdf5Dataset(gsoapProxy2_0_1->soap);
	xmlDefinedPillars->Values->HdfProxy = proxy->newResqmlReference();
	xmlDefinedPillars->Values->PathInHdfFile = getHdfGroup() + "/PillarGeometryIsDefined";

	// HDF Pillar defined
	getRepository()->addRelationship(this, proxy);
	const unsigned int pillarCount = getPillarCount();
	std::unique_ptr<unsigned char[]> definedPillars(new unsigned char[pillarCount]);
	for (unsigned int i = 0; i < pillarCount; ++i) {
		definedPillars[i] = pillarKind[i] == -1 ? 0 : 1;
	}
	hsize_t pillarGeometryIsDefinedCount[2] = { getJCellCount() + 1, getICellCount() + 1 };
	proxy->writeArrayNd(getHdfGroup(), "PillarGeometryIsDefined", H5T_NATIVE_UCHAR, definedPillars.get(), pillarGeometryIsDefinedCount, 2);

	// *********************************
	// Overwrite line kind hdf dataset
	// *********************************
	resqml20__Point3dParametricArray* xmlPoints = static_cast<resqml20__Point3dParametricArray*>(geom->Points);
	resqml20__ParametricLineArray* paramLines = static_cast<resqml20__ParametricLineArray*>(xmlPoints->ParametricLines);
	paramLines->KnotCount = controlPointMaxCountPerPillar;

	// XML Line kinds
	resqml20__IntegerHdf5Array* xmlLineKinds = soap_new_resqml20__IntegerHdf5Array(gsoapProxy2_0_1->soap);
	paramLines->LineKindIndices = xmlLineKinds;
	xmlLineKinds->NullValue = -1;
	xmlLineKinds->Values = soap_new_eml20__Hdf5Dataset(gsoapProxy2_0_1->soap);
	xmlLineKinds->Values->HdfProxy = proxy->newResqmlReference();
	xmlLineKinds->Values->PathInHdfFile = getHdfGroup() + "/LineKindIndices";

	// HDF Line kinds
	hsize_t lineKindCount[2] = { getJCellCount() + 1, getICellCount() + 1 };
	proxy->writeArrayNd(getHdfGroup(), "LineKindIndices", H5T_NATIVE_SHORT, pillarKind, lineKindCount, 2);
}

void IjkGridParametricRepresentation::setGeometryAsParametricSplittedPillarNodesUsingExistingDatasets(
	gsoap_resqml2_0_1::resqml20__PillarShape mostComplexPillarGeometry, gsoap_resqml2_0_1::resqml20__KDirection kDirectionKind, bool isRightHanded,
	const std::string & parameters, const std::string & controlPoints, const std::string & controlPointParameters, unsigned int controlPointMaxCountPerPillar, const std::string & pillarKind, const std::string & definedPillars, EML2_NS::AbstractHdfProxy* proxy,
	unsigned long splitCoordinateLineCount, const std::string & pillarOfCoordinateLine,
	const std::string & splitCoordinateLineColumnCumulativeCount, const std::string & splitCoordinateLineColumns, RESQML2_NS::AbstractLocal3dCrs * localCrs)
{
	if (pillarKind.empty())
		throw invalid_argument("The kind of the coordinate lines cannot be null.");
	if (definedPillars.empty())
		throw invalid_argument("The defined pillars cannot be null.");

	setGeometryAsParametricSplittedPillarNodesWithoutPillarKindUsingExistingDatasets(kDirectionKind, isRightHanded,
		parameters, controlPoints, controlPointParameters, controlPointMaxCountPerPillar, proxy,
		splitCoordinateLineCount, pillarOfCoordinateLine,
		splitCoordinateLineColumnCumulativeCount, splitCoordinateLineColumns, localCrs);

	gsoap_resqml2_0_1::resqml20__IjkGridGeometry* geom = static_cast<gsoap_resqml2_0_1::resqml20__IjkGridGeometry*>(getPointGeometry2_0_1(0));
	if (geom == nullptr) {
		throw invalid_argument("There is no geometry on this grid.");
	}
	geom->PillarShape = mostComplexPillarGeometry;

	// XML Pillar defined
	resqml20__BooleanHdf5Array* xmlDefinedPillars = soap_new_resqml20__BooleanHdf5Array(gsoapProxy2_0_1->soap);
	geom->PillarGeometryIsDefined = xmlDefinedPillars;
	xmlDefinedPillars->Values = soap_new_eml20__Hdf5Dataset(gsoapProxy2_0_1->soap);
	xmlDefinedPillars->Values->HdfProxy = proxy->newResqmlReference();
	xmlDefinedPillars->Values->PathInHdfFile = definedPillars;

	// *********************************
	// Line kind hdf dataset
	// *********************************
	resqml20__Point3dParametricArray* xmlPoints = static_cast<resqml20__Point3dParametricArray*>(geom->Points);
	resqml20__ParametricLineArray* paramLines = static_cast<resqml20__ParametricLineArray*>(xmlPoints->ParametricLines);
	paramLines->KnotCount = controlPointMaxCountPerPillar;

	// XML Line kinds
	resqml20__IntegerHdf5Array* xmlLineKinds = soap_new_resqml20__IntegerHdf5Array(gsoapProxy2_0_1->soap);
	paramLines->LineKindIndices = xmlLineKinds;
	xmlLineKinds->NullValue = -1;
	xmlLineKinds->Values = soap_new_eml20__Hdf5Dataset(gsoapProxy2_0_1->soap);
	xmlLineKinds->Values->HdfProxy = proxy->newResqmlReference();
	xmlLineKinds->Values->PathInHdfFile = pillarKind;
}

void IjkGridParametricRepresentation::setGeometryAsParametricSplittedPillarNodesWithoutPillarKindUsingExistingDatasets(
	gsoap_resqml2_0_1::resqml20__KDirection kDirectionKind, bool isRightHanded,
	const std::string & parameters, const std::string & controlPoints, const std::string & controlPointParameters, unsigned int controlPointCountPerPillar, EML2_NS::AbstractHdfProxy* proxy,
	unsigned long splitCoordinateLineCount, const std::string & pillarOfCoordinateLine,
	const std::string & splitCoordinateLineColumnCumulativeCount, const std::string & splitCoordinateLineColumns, RESQML2_NS::AbstractLocal3dCrs * localCrs)
{
	if (controlPointCountPerPillar < 1) {
		throw invalid_argument("The max count of control points per coordinate line of the ijk grid cannot be less than one.");
	}
	if (localCrs == nullptr) {
		localCrs = getRepository()->getDefaultCrs();
		if (localCrs == nullptr) {
			throw std::invalid_argument("A (default) CRS must be provided.");
		}
	}
	if (proxy == nullptr) {
		proxy = getRepository()->getDefaultHdfProxy();
		if (proxy == nullptr) {
			throw std::invalid_argument("A (default) HDF Proxy must be provided.");
		}
	}

	resqml20__IjkGridGeometry* geom = soap_new_resqml20__IjkGridGeometry(gsoapProxy2_0_1->soap);
	geom->LocalCrs = localCrs->newResqmlReference();
	if (!isTruncated()) {
		getSpecializedGsoapProxy2_0_1()->Geometry = geom;
	}
	else {
		getSpecializedTruncatedGsoapProxy2_0_1()->Geometry = geom;
	}
	geom->GridIsRighthanded = isRightHanded;
	geom->KDirection = kDirectionKind;

	getRepository()->addRelationship(this, proxy);
	// XML parametric nodes
	resqml20__Point3dParametricArray* xmlPoints = soap_new_resqml20__Point3dParametricArray(gsoapProxy2_0_1->soap);
	geom->Points = xmlPoints;
	resqml20__DoubleHdf5Array* xmlParameters = soap_new_resqml20__DoubleHdf5Array(gsoapProxy2_0_1->soap);
	xmlPoints->Parameters = xmlParameters;
	xmlParameters->Values = soap_new_eml20__Hdf5Dataset(gsoapProxy2_0_1->soap);
	xmlParameters->Values->HdfProxy = proxy->newResqmlReference();
	xmlParameters->Values->PathInHdfFile = parameters;

	if (splitCoordinateLineCount > 0) {
		// XML split coordinate lines
		geom->SplitCoordinateLines = soap_new_resqml20__ColumnLayerSplitCoordinateLines(gsoapProxy2_0_1->soap);;
		geom->SplitCoordinateLines->Count = splitCoordinateLineCount;

		//XML
		resqml20__IntegerHdf5Array* pillarIndices = soap_new_resqml20__IntegerHdf5Array(gsoapProxy2_0_1->soap);
		geom->SplitCoordinateLines->PillarIndices = pillarIndices;
		pillarIndices->NullValue = getPillarCount();
		pillarIndices->Values = soap_new_eml20__Hdf5Dataset(gsoapProxy2_0_1->soap);
		pillarIndices->Values->HdfProxy = proxy->newResqmlReference();
		pillarIndices->Values->PathInHdfFile = pillarOfCoordinateLine;

		//XML
		geom->SplitCoordinateLines->ColumnsPerSplitCoordinateLine = soap_new_resqml20__ResqmlJaggedArray(gsoapProxy2_0_1->soap);
		// Cumulative
		resqml20__IntegerHdf5Array* cumulativeLength = soap_new_resqml20__IntegerHdf5Array(gsoapProxy2_0_1->soap);
		geom->SplitCoordinateLines->ColumnsPerSplitCoordinateLine->CumulativeLength = cumulativeLength;
		cumulativeLength->NullValue = 0;
		cumulativeLength->Values = soap_new_eml20__Hdf5Dataset(gsoapProxy2_0_1->soap);
		cumulativeLength->Values->HdfProxy = proxy->newResqmlReference();
		cumulativeLength->Values->PathInHdfFile = splitCoordinateLineColumnCumulativeCount;
		// Elements
		resqml20__IntegerHdf5Array* elements = soap_new_resqml20__IntegerHdf5Array(gsoapProxy2_0_1->soap);
		geom->SplitCoordinateLines->ColumnsPerSplitCoordinateLine->Elements = elements;
		elements->NullValue = getColumnCount();
		elements->Values = soap_new_eml20__Hdf5Dataset(gsoapProxy2_0_1->soap);
		elements->Values->HdfProxy = proxy->newResqmlReference();
		elements->Values->PathInHdfFile = splitCoordinateLineColumns;
	}

	// *********************************
	// Parametric coordinate lines
	// *********************************
	resqml20__ParametricLineArray* paramLines = soap_new_resqml20__ParametricLineArray(gsoapProxy2_0_1->soap);
	xmlPoints->ParametricLines = paramLines;
	paramLines->KnotCount = controlPointCountPerPillar;

	// XML control points
	resqml20__Point3dHdf5Array* xmlcontrolPoints = soap_new_resqml20__Point3dHdf5Array(gsoapProxy2_0_1->soap);
	paramLines->ControlPoints = xmlcontrolPoints;
	xmlcontrolPoints->Coordinates = soap_new_eml20__Hdf5Dataset(gsoapProxy2_0_1->soap);
	xmlcontrolPoints->Coordinates->HdfProxy = proxy->newResqmlReference();
	xmlcontrolPoints->Coordinates->PathInHdfFile = controlPoints;

	// *********************************
	// Control point parameters are defined
	// *********************************
	if (!controlPointParameters.empty()) {
		// XML control point parameters
		resqml20__DoubleHdf5Array* xmlcontrolPointParams = soap_new_resqml20__DoubleHdf5Array(gsoapProxy2_0_1->soap);
		paramLines->ControlPointParameters = xmlcontrolPointParams;
		xmlcontrolPointParams->Values = soap_new_eml20__Hdf5Dataset(gsoapProxy2_0_1->soap);
		xmlcontrolPointParams->Values->HdfProxy = proxy->newResqmlReference();
		xmlcontrolPointParams->Values->PathInHdfFile = controlPointParameters;
	}

	getRepository()->addRelationship(this, localCrs);
}


void IjkGridParametricRepresentation::setGeometryAsParametricSplittedPillarNodesUsingExistingDatasets(
	gsoap_resqml2_0_1::resqml20__KDirection kDirectionKind, bool isRightHanded,
	const std::string & parameters, const std::string & controlPoints, const std::string & controlPointParameters, unsigned int controlPointCountPerPillar, short pillarKind, EML2_NS::AbstractHdfProxy* proxy,
	unsigned long splitCoordinateLineCount, const std::string & pillarOfCoordinateLine,
	const std::string & splitCoordinateLineColumnCumulativeCount, const std::string & splitCoordinateLineColumns, RESQML2_NS::AbstractLocal3dCrs * localCrs)
{
	if (pillarKind < 0 || pillarKind > 5) {
		throw range_error("The kind of the coordinate lines is out of range.");
	}

	setGeometryAsParametricSplittedPillarNodesWithoutPillarKindUsingExistingDatasets(kDirectionKind, isRightHanded,
		parameters, controlPoints, controlPointParameters, controlPointCountPerPillar, proxy,
		splitCoordinateLineCount, pillarOfCoordinateLine,
		splitCoordinateLineColumnCumulativeCount, splitCoordinateLineColumns, localCrs);

	resqml20__IjkGridGeometry* geom = isTruncated() ? getSpecializedTruncatedGsoapProxy2_0_1()->Geometry : getSpecializedGsoapProxy2_0_1()->Geometry;
	if (geom == nullptr) {
		throw invalid_argument("There is no geometry on this grid.");
	}

	if (pillarKind > 1 || controlPointCountPerPillar > 2) {
		geom->PillarShape = resqml20__PillarShape__curved;
	}
	else if (pillarKind == 1) {
		geom->PillarShape = resqml20__PillarShape__straight;
	}
	else {
		geom->PillarShape = resqml20__PillarShape__vertical;
	}

	// XML Pillar defined
	resqml20__BooleanConstantArray* xmlDefinedPillars = soap_new_resqml20__BooleanConstantArray(gsoapProxy2_0_1->soap);
	geom->PillarGeometryIsDefined = xmlDefinedPillars;
	xmlDefinedPillars->Value = true;
	xmlDefinedPillars->Count = getPillarCount();

	resqml20__Point3dParametricArray* xmlPoints = static_cast<resqml20__Point3dParametricArray*>(geom->Points);
	resqml20__ParametricLineArray* paramLines = static_cast<resqml20__ParametricLineArray*>(xmlPoints->ParametricLines);

	// XML Line kinds
	resqml20__IntegerConstantArray* xmlLineKinds = soap_new_resqml20__IntegerConstantArray(gsoapProxy2_0_1->soap);
	paramLines->LineKindIndices = xmlLineKinds;
	xmlLineKinds->Value = pillarKind;
	xmlLineKinds->Count = getPillarCount();
}

EML2_NS::AbstractHdfProxy* IjkGridParametricRepresentation::getParameterDatasetPath(std::string & datasetPathInExternalFile) const
{
	gsoap_resqml2_0_1::resqml20__PointGeometry* geom = getPointGeometry2_0_1(0);
	if (geom == nullptr) {
		throw invalid_argument("There is no geometry on this grid.");
	}
	resqml20__Point3dParametricArray* parametricPoint3d = static_cast<resqml20__Point3dParametricArray*>(geom->Points);
	if (parametricPoint3d->Parameters->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__DoubleHdf5Array) {
		eml20__Hdf5Dataset const * xmlDataset = static_cast<resqml20__DoubleHdf5Array*>(parametricPoint3d->Parameters)->Values;
		datasetPathInExternalFile = xmlDataset->PathInHdfFile;
		return getHdfProxyFromDataset(xmlDataset);
	}
	else {
		throw logic_error("Non floating point coordinate line parameters are not implemented yet");
	}
}

EML2_NS::AbstractHdfProxy* IjkGridParametricRepresentation::getControlPointDatasetPath(std::string & datasetPathInExternalFile) const
{
	gsoap_resqml2_0_1::resqml20__PointGeometry* geom = getPointGeometry2_0_1(0);
	if (geom == nullptr) {
		throw invalid_argument("There is no geometry on this grid.");
	}
	resqml20__Point3dParametricArray* points = static_cast<resqml20__Point3dParametricArray*>(geom->Points);
	if (points->ParametricLines->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__ParametricLineArray) {
		resqml20__ParametricLineArray* paramLineArray = static_cast<resqml20__ParametricLineArray*>(points->ParametricLines);
		if (paramLineArray->ControlPoints->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__Point3dHdf5Array) {
			eml20__Hdf5Dataset const * dataset = static_cast<resqml20__Point3dHdf5Array*>(paramLineArray->ControlPoints)->Coordinates;
			datasetPathInExternalFile = dataset->PathInHdfFile;
			return getHdfProxyFromDataset(dataset);
		}
		else
			throw std::logic_error("Not implemented yet");
	}
	else {
		throw std::logic_error("Not implemented yet");
	}
}

EML2_NS::AbstractHdfProxy* IjkGridParametricRepresentation::getControlPointParametersDatasetPath(std::string & datasetPathInExternalFile) const
{
	gsoap_resqml2_0_1::resqml20__PointGeometry* geom = getPointGeometry2_0_1(0);
	if (geom == nullptr) {
		throw invalid_argument("There is no geometry on this grid.");
	}
	resqml20__Point3dParametricArray* points = static_cast<resqml20__Point3dParametricArray*>(geom->Points);
	if (points->ParametricLines->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__ParametricLineArray)
	{
		resqml20__ParametricLineArray* paramLineArray = static_cast<resqml20__ParametricLineArray*>(points->ParametricLines);
		if (paramLineArray->ControlPointParameters == nullptr)
			throw invalid_argument("The grid does not contain any control point parameters.");
		if (paramLineArray->ControlPointParameters->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__DoubleHdf5Array)
		{
			eml20__Hdf5Dataset const * dataset = static_cast<resqml20__DoubleHdf5Array*>(paramLineArray->ControlPointParameters)->Values;
			datasetPathInExternalFile = dataset->PathInHdfFile;
			return getHdfProxyFromDataset(dataset);
		}
		else
			throw std::logic_error("Not implemented yet");
	}
	else
		throw std::logic_error("Not implemented yet");
}

EML2_NS::AbstractHdfProxy* IjkGridParametricRepresentation::getParametersOfNodesDatasetPath(std::string & datasetPathInExternalFile) const
{
	gsoap_resqml2_0_1::resqml20__PointGeometry* geom = getPointGeometry2_0_1(0);
	if (geom == nullptr) {
		throw invalid_argument("There is no geometry on this grid.");
	}
	resqml20__Point3dParametricArray* points = static_cast<resqml20__Point3dParametricArray*>(geom->Points);
	if (points->Parameters->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__DoubleHdf5Array)
	{
		eml20__Hdf5Dataset const * dataset = static_cast<resqml20__DoubleHdf5Array*>(points->Parameters)->Values;
		datasetPathInExternalFile = dataset->PathInHdfFile;
		return getHdfProxyFromDataset(dataset);
	}
	else
		throw std::logic_error("Not implemented yet");
}
