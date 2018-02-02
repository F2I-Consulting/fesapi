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
#include "resqml2_0_1/Grid2dSetRepresentation.h"

#include <stdexcept>
#include <algorithm>

#include "resqml2/AbstractFeatureInterpretation.h"
#include "resqml2_0_1/Grid2dRepresentation.h"
#include "resqml2/AbstractLocal3dCrs.h"
#include "common/AbstractHdfProxy.h"

using namespace std;
using namespace resqml2_0_1;
using namespace gsoap_resqml2_0_1;
using namespace epc;

const char* Grid2dSetRepresentation::XML_TAG = "Grid2dSetRepresentation";

Grid2dSetRepresentation::Grid2dSetRepresentation(resqml2::AbstractFeatureInterpretation* interp, resqml2::AbstractLocal3dCrs * crs,
	const string & guid, const string & title):
	AbstractSurfaceRepresentation(interp, crs)
{
	gsoapProxy2_0_1 = soap_new_resqml2__obj_USCOREGrid2dSetRepresentation(interp->getGsoapContext(), 1);
	_resqml2__Grid2dSetRepresentation* grid2dSetRep = static_cast<_resqml2__Grid2dSetRepresentation*>(gsoapProxy2_0_1);
	
	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "", "");

	// relationhsips
	localCrs = crs;
	localCrs->addRepresentation(this);

	setInterpretation(interp);
}

void Grid2dSetRepresentation::getXyzPointsOfPatch(const unsigned int & patchIndex, double * xyzPoints) const
{
	if (patchIndex >= getPatchCount())
		throw range_error("The index patch is not in the allowed range of patch.");

	throw logic_error("Please use compute X and Y values with th elattice information.");
}

unsigned int Grid2dSetRepresentation::getNodeCountAlongIAxis(const unsigned int & patchIndex) const
{
	return static_cast<_resqml2__Grid2dSetRepresentation*>(gsoapProxy2_0_1)->Grid2dPatch[patchIndex]->FastestAxisCount;
}

unsigned int Grid2dSetRepresentation::getNodeCountAlongJAxis(const unsigned int & patchIndex) const
{
	return static_cast<_resqml2__Grid2dSetRepresentation*>(gsoapProxy2_0_1)->Grid2dPatch[patchIndex]->SlowestAxisCount;
}

resqml2__PointGeometry* Grid2dSetRepresentation::getPointGeometry2_0_1(const unsigned int & patchIndex) const
{
	if (patchIndex < static_cast<_resqml2__Grid2dSetRepresentation*>(gsoapProxy2_0_1)->Grid2dPatch.size())
		return static_cast<_resqml2__Grid2dSetRepresentation*>(gsoapProxy2_0_1)->Grid2dPatch[patchIndex]->Geometry;
	else
		return nullptr;
}

string Grid2dSetRepresentation::getHdfProxyUuid() const
{
	return getHdfProxyUuidFromPointGeometryPatch(getPointGeometry2_0_1(0));
}

void Grid2dSetRepresentation::getZValuesOfPatch(const unsigned int & patchIndex, double* values) const
{
	_resqml2__Grid2dSetRepresentation* rep = static_cast<_resqml2__Grid2dSetRepresentation*>(gsoapProxy2_0_1);
	resqml2__AbstractDoubleArray* zValues = static_cast<resqml2__Point3dZValueArray*>(rep->Grid2dPatch[patchIndex]->Geometry->Points)->ZValues;
	string datasetName = "";
	if (zValues->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__DoubleHdf5Array)
	{
		datasetName = static_cast<resqml2__DoubleHdf5Array*>(zValues)->Values->PathInHdfFile;
	}
	else
	{
		return;
	}

	hdfProxy->readArrayNdOfDoubleValues(datasetName, values);
}

void Grid2dSetRepresentation::getZValuesOfPatchInGlobalCrs(const unsigned int & patchIndex, double* values) const
{
	getZValuesOfPatch(patchIndex, values);

	if (localCrs->getGsoapType() != SOAP_TYPE_gsoap_resqml2_0_1_resqml2__obj_USCORELocalTime3dCrs)
	{
		_resqml2__Grid2dSetRepresentation* rep = static_cast<_resqml2__Grid2dSetRepresentation*>(gsoapProxy2_0_1);
		unsigned int NodeCount = rep->Grid2dPatch[patchIndex]->FastestAxisCount * rep->Grid2dPatch[patchIndex]->SlowestAxisCount;
		double zOffset = localCrs->getOriginDepthOrElevation();
		if (zOffset != .0)
		{
			for (unsigned int index = 0; index < NodeCount; index++)
				values[index] += zOffset;
		}
	}
}

unsigned int Grid2dSetRepresentation::getPatchCount() const
{
	return static_cast<_resqml2__Grid2dSetRepresentation*>(gsoapProxy2_0_1)->Grid2dPatch.size();
}

void Grid2dSetRepresentation::pushBackGeometryPatch(double * zValues,
	const unsigned int & numI, const unsigned int & numJ, common::AbstractHdfProxy * proxy,
	Grid2dRepresentation * supportingGrid2dRepresentation,
	const unsigned int & startIndexI, const unsigned int & startIndexJ,
	const int & indexIncrementI, const int & indexIncrementJ)
{
	if (updateXml)
	{
		resqml2__Grid2dPatch* patch = soap_new_resqml2__Grid2dPatch(gsoapProxy2_0_1->soap, 1);
		patch->PatchIndex = static_cast<_resqml2__Grid2dSetRepresentation*>(gsoapProxy2_0_1)->Grid2dPatch.size();
		static_cast<_resqml2__Grid2dSetRepresentation*>(gsoapProxy2_0_1)->Grid2dPatch.push_back(patch);

		patch->SlowestAxisCount = numJ;
		patch->FastestAxisCount = numI;

		resqml2__PointGeometry* geomPatch = createArray2dOfExplicitZ(0,
				zValues,
				numI, numJ, proxy,
				supportingGrid2dRepresentation,
				startIndexI + startIndexJ * numI,
				indexIncrementI, indexIncrementJ);
		patch->Geometry = geomPatch;
	}
	
	supportingRepresentationSet.push_back(supportingGrid2dRepresentation);
	supportingGrid2dRepresentation->supportedRepresentationSet.push_back(this);
}

std::string Grid2dSetRepresentation::getSupportingRepresentationUuid(const unsigned int & patchIndex) const
{
	resqml2__Point3dFromRepresentationLatticeArray* geom = getPoint3dFromRepresentationLatticeArrayFromPointGeometryPatch(static_cast<_resqml2__Grid2dSetRepresentation*>(gsoapProxy2_0_1)->Grid2dPatch[patchIndex]->Geometry);
	
	if (geom)
	{
		return geom->SupportingRepresentation->UUID;
	}
	else
	{
		return "";
	}
}

int Grid2dSetRepresentation::getIndexOriginOnSupportingRepresentation(const unsigned int & patchIndex, const unsigned int & dimension) const
{
	int result = 0;

	resqml2__Point3dFromRepresentationLatticeArray* geom = getPoint3dFromRepresentationLatticeArrayFromPointGeometryPatch(static_cast<_resqml2__Grid2dSetRepresentation*>(gsoapProxy2_0_1)->Grid2dPatch[patchIndex]->Geometry);

	if (geom)
	{
		if (dimension == 0) // J dimension : slowest
			result = geom->NodeIndicesOnSupportingRepresentation->StartValue / getNodeCountAlongIAxis(patchIndex);
		else if (dimension == 1) // I dimension : fastest
			result = geom->NodeIndicesOnSupportingRepresentation->StartValue % getNodeCountAlongIAxis(patchIndex);
	}

	return result;
}

int Grid2dSetRepresentation::getNodeCountOnSupportingRepresentation(const unsigned int & patchIndex, const unsigned int & dimension) const
{
	int result = 0;

	resqml2__Point3dFromRepresentationLatticeArray* geom = getPoint3dFromRepresentationLatticeArrayFromPointGeometryPatch(static_cast<_resqml2__Grid2dSetRepresentation*>(gsoapProxy2_0_1)->Grid2dPatch[patchIndex]->Geometry);

	if (geom)
		result = geom->NodeIndicesOnSupportingRepresentation->Offset[dimension]->Count + 1;

	return result;
}

int Grid2dSetRepresentation::getIndexOffsetOnSupportingRepresentation(const unsigned int & patchIndex, const unsigned int & dimension) const
{
	int result = 0;

	resqml2__Point3dFromRepresentationLatticeArray* geom = getPoint3dFromRepresentationLatticeArrayFromPointGeometryPatch(static_cast<_resqml2__Grid2dSetRepresentation*>(gsoapProxy2_0_1)->Grid2dPatch[patchIndex]->Geometry);

	if (geom)
		result = geom->NodeIndicesOnSupportingRepresentation->Offset[dimension]->Value;

	return result;
}

vector<Relationship> Grid2dSetRepresentation::getAllEpcRelationships() const
{
	vector<Relationship> result = AbstractSurfaceRepresentation::getAllEpcRelationships();

	// Supporting representations
	for(vector<Grid2dRepresentation*>::const_iterator it = supportingRepresentationSet.begin(); it != supportingRepresentationSet.end(); ++it)
	{
		if (std::find(seismicSupportSet.begin(), seismicSupportSet.end(), *it) == seismicSupportSet.end() &&
			(it == supportingRepresentationSet.begin() || std::find(supportingRepresentationSet.begin(), it, *it) != supportingRepresentationSet.end())) //  No need to add the rel twice
		{
			Relationship relSupportingRepresentation((*it)->getPartNameInEpcDocument(), "", (*it)->getUuid());
			relSupportingRepresentation.setDestinationObjectType();
			result.push_back(relSupportingRepresentation);
		}
	}

	return result;
}

void Grid2dSetRepresentation::importRelationshipSetFromEpc(common::EpcDocument* epcDoc)
{
	AbstractSurfaceRepresentation::importRelationshipSetFromEpc(epcDoc);

	_resqml2__Grid2dSetRepresentation* grid2dSetRep = static_cast<_resqml2__Grid2dSetRepresentation*>(gsoapProxy2_0_1);

	// Supporting representation
	for (unsigned int patchIndex = 0; patchIndex < grid2dSetRep->Grid2dPatch.size(); ++patchIndex)
	{
		string supportingRepUuid = getSupportingRepresentationUuid(patchIndex);
		if (supportingRepUuid.empty() == false)
		{
			Grid2dRepresentation* supportingGrid2dRepresentation = static_cast<Grid2dRepresentation*>(epcDoc->getResqmlAbstractObjectByUuid(supportingRepUuid));
			if (supportingGrid2dRepresentation != nullptr)
			{
				updateXml = false;
				pushBackGeometryPatch(nullptr, 0, 0, nullptr, supportingGrid2dRepresentation);
				updateXml = true;
			}
		}
	}
}

