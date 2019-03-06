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
#include "resqml2_0_1/WellboreFrameRepresentation.h"

#include <stdexcept>

#include "hdf5.h"

#include "resqml2_0_1/WellboreInterpretation.h"
#include "resqml2_0_1/WellboreTrajectoryRepresentation.h"
#include "resqml2/AbstractLocal3dCrs.h"
#include "common/AbstractHdfProxy.h"

using namespace std;
using namespace RESQML2_0_1_NS;
using namespace gsoap_resqml2_0_1;
using namespace epc;

const char* WellboreFrameRepresentation::XML_TAG = "WellboreFrameRepresentation";

WellboreFrameRepresentation::WellboreFrameRepresentation(WellboreInterpretation* interp, const string & guid, const std::string & title, WellboreTrajectoryRepresentation * traj) :
	AbstractRepresentation(interp, traj->getLocalCrs()), trajectory(traj)
{
	gsoapProxy2_0_1 = soap_new_resqml2__obj_USCOREWellboreFrameRepresentation(interp->getGsoapContext(), 1);	
	_resqml2__WellboreFrameRepresentation* frame = static_cast<_resqml2__WellboreFrameRepresentation*>(gsoapProxy2_0_1);

	setInterpretation(interp);

	frame->Trajectory = traj->newResqmlReference();
	traj->addWellboreFrameRepresentation(this);

	initMandatoryMetadata();
	setMetadata(guid, title, std::string(), -1, std::string(), std::string(), -1, std::string());
}


void WellboreFrameRepresentation::getXyzPointsOfPatch(const unsigned int & patchIndex, double * xyzPoints) const
{
	if (patchIndex >= getPatchCount())
		throw range_error("The index of the patch is not in the allowed range of patch.");

	resqml2__PointGeometry* pointGeom = getPointGeometry2_0_1(patchIndex);
	if (pointGeom != nullptr && pointGeom->Points->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__Point3dHdf5Array)
	{
		hdfProxy->readArrayNdOfDoubleValues(static_cast<resqml2__Point3dHdf5Array*>(pointGeom->Points)->Coordinates->PathInHdfFile, xyzPoints);
	}
	else
		throw invalid_argument("The geometry of the representation either does not exist or it is not an explicit one.");
}

vector<Relationship> WellboreFrameRepresentation::getAllEpcRelationships() const
{
	_resqml2__WellboreFrameRepresentation* frame = static_cast<_resqml2__WellboreFrameRepresentation*>(gsoapProxy2_0_1);
	
	vector<Relationship> result = AbstractRepresentation::getAllEpcRelationships();

	// XML forward relationship
	if (trajectory)
	{
		Relationship relTraj(trajectory->getPartNameInEpcDocument(), "", frame->Trajectory->UUID);
		relTraj.setDestinationObjectType();
		result.push_back(relTraj);
	}
	else
		throw domain_error("The trajectory associated to the WellboreFeature frame cannot be nullptr.");

	return result;
}

void WellboreFrameRepresentation::importRelationshipSetFromEpc(COMMON_NS::EpcDocument* epcDoc)
{
	const _resqml2__WellboreFrameRepresentation* const rep = static_cast<const _resqml2__WellboreFrameRepresentation* const>(gsoapProxy2_0_1);

	// need to do that before AbstractRepresentation::importRelationshipSetFromEpc because the trajectory is used for finding the local crs relationship.
	trajectory = static_cast<WellboreTrajectoryRepresentation* const>(epcDoc->getDataObjectByUuid(rep->Trajectory->UUID));
	if (trajectory != nullptr) {
		trajectory->addWellboreFrameRepresentation(this);
	}

	AbstractRepresentation::importRelationshipSetFromEpc(epcDoc);

	int valuesType = rep->NodeMd->soap_type();
	if (valuesType == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__DoubleHdf5Array) {
		setHdfProxy(static_cast<COMMON_NS::AbstractHdfProxy* const>(epcDoc->getDataObjectByUuid(static_cast<resqml2__DoubleHdf5Array* const>(rep->NodeMd)->Values->HdfProxy->UUID)));
	}
}

void WellboreFrameRepresentation::setMdValues(double * mdValues, const unsigned int & mdValueCount, COMMON_NS::AbstractHdfProxy * proxy)
{
	setHdfProxy(proxy);

	_resqml2__WellboreFrameRepresentation* frame = static_cast<_resqml2__WellboreFrameRepresentation*>(gsoapProxy2_0_1);

	// XML
	resqml2__DoubleHdf5Array* xmlMdValues = soap_new_resqml2__DoubleHdf5Array(gsoapProxy2_0_1->soap, 1);
	xmlMdValues->Values = soap_new_eml20__Hdf5Dataset(gsoapProxy2_0_1->soap, 1);
	xmlMdValues->Values->HdfProxy = hdfProxy->newResqmlReference();
	xmlMdValues->Values->PathInHdfFile = "/RESQML/" + frame->uuid + "/mdValues";

	frame->NodeMd = xmlMdValues;

	frame->NodeCount = mdValueCount;

	// HDF
	hsize_t dim[] = {mdValueCount};
	hdfProxy->writeArrayNd(frame->uuid,
			"mdValues",
			H5T_NATIVE_DOUBLE,
			mdValues,
			dim, 1);
}

void WellboreFrameRepresentation::setMdValues(const double & firstMdValue, const double & incrementMdValue, const unsigned int & mdValueCount)
{
	_resqml2__WellboreFrameRepresentation* frame = static_cast<_resqml2__WellboreFrameRepresentation*>(gsoapProxy2_0_1);

	// XML
	resqml2__DoubleLatticeArray* xmlMdValues = soap_new_resqml2__DoubleLatticeArray(gsoapProxy2_0_1->soap, 1);
	xmlMdValues->StartValue = firstMdValue;
	xmlMdValues->Offset.push_back(soap_new_resqml2__DoubleConstantArray(gsoapProxy2_0_1->soap, 1));
	xmlMdValues->Offset[0]->Count = mdValueCount - 1;
	xmlMdValues->Offset[0]->Value = incrementMdValue;

	frame->NodeMd = xmlMdValues;

	frame->NodeCount = mdValueCount;
}

bool WellboreFrameRepresentation::areMdValuesRegularlySpaced() const
{
	return static_cast<_resqml2__WellboreFrameRepresentation*>(gsoapProxy2_0_1)->NodeMd->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__DoubleLatticeArray;
}

double WellboreFrameRepresentation::getMdConstantIncrementValue() const
{
	if (!areMdValuesRegularlySpaced())
		throw invalid_argument("The MD values are not regularly spaced.");

	return static_cast<resqml2__DoubleLatticeArray*>(static_cast<_resqml2__WellboreFrameRepresentation*>(gsoapProxy2_0_1)->NodeMd)->Offset[0]->Value;
}

double WellboreFrameRepresentation::getMdFirstValue() const
{
	_resqml2__WellboreFrameRepresentation* frame = static_cast<_resqml2__WellboreFrameRepresentation*>(gsoapProxy2_0_1);
	if (frame->NodeMd->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__DoubleHdf5Array)
	{
		if (hdfProxy == nullptr)
			throw invalid_argument("No Hdf Proxy");
		
		double* values = new double[getMdValuesCount()];
		hdfProxy->readArrayNdOfDoubleValues(static_cast<resqml2__DoubleHdf5Array*>(frame->NodeMd)->Values->PathInHdfFile, values);
		double result = values[0];
		delete [] values;

		return result;
	}
	else if (frame->NodeMd->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__DoubleLatticeArray)
	{
		return static_cast<resqml2__DoubleLatticeArray*>(frame->NodeMd)->StartValue;
	}
	else
		throw logic_error("The array structure of MD is not supported?");
}

unsigned int WellboreFrameRepresentation::getMdValuesCount() const
{
	return static_cast<_resqml2__WellboreFrameRepresentation*>(gsoapProxy2_0_1)->NodeCount;
}

RESQML2_NS::AbstractValuesProperty::hdfDatatypeEnum WellboreFrameRepresentation::getMdHdfDatatype() const
{
	_resqml2__WellboreFrameRepresentation* frame = static_cast<_resqml2__WellboreFrameRepresentation*>(gsoapProxy2_0_1);
	if (frame->NodeMd->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__DoubleHdf5Array)
	{
		if (hdfProxy == nullptr)
			return RESQML2_NS::AbstractValuesProperty::UNKNOWN;

		hid_t dt = hdfProxy->getHdfDatatypeInDataset(static_cast<resqml2__DoubleHdf5Array*>(frame->NodeMd)->Values->PathInHdfFile);
		if (H5Tequal(dt, H5T_NATIVE_DOUBLE) > 0)
			return RESQML2_NS::AbstractValuesProperty::DOUBLE;
		else if (H5Tequal(dt, H5T_NATIVE_FLOAT) > 0)
			return RESQML2_NS::AbstractValuesProperty::FLOAT;
		else if (H5Tequal(dt, H5T_NATIVE_LONG) > 0)
			return RESQML2_NS::AbstractValuesProperty::LONG;
		else if (H5Tequal(dt, H5T_NATIVE_ULONG) > 0)
			return RESQML2_NS::AbstractValuesProperty::ULONG;
		else if (H5Tequal(dt, H5T_NATIVE_INT) > 0)
			return RESQML2_NS::AbstractValuesProperty::INT;
		else if (H5Tequal(dt, H5T_NATIVE_UINT) > 0)
			return RESQML2_NS::AbstractValuesProperty::UINT;
		else if (H5Tequal(dt, H5T_NATIVE_SHORT) > 0)
			return RESQML2_NS::AbstractValuesProperty::SHORT;
		else if (H5Tequal(dt, H5T_NATIVE_USHORT) > 0)
			return RESQML2_NS::AbstractValuesProperty::USHORT;
		else if (H5Tequal(dt, H5T_NATIVE_CHAR) > 0)
			return RESQML2_NS::AbstractValuesProperty::CHAR;
		else if (H5Tequal(dt, H5T_NATIVE_UCHAR) > 0)
			return RESQML2_NS::AbstractValuesProperty::UCHAR;
	}
	else if (frame->NodeMd->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__DoubleLatticeArray)
	{
		return RESQML2_NS::AbstractValuesProperty::DOUBLE;
	}

	return RESQML2_NS::AbstractValuesProperty::UNKNOWN; // unknwown datatype...
}

void WellboreFrameRepresentation::getMdAsDoubleValues(double * values)
{	_resqml2__WellboreFrameRepresentation* frame = static_cast<_resqml2__WellboreFrameRepresentation*>(gsoapProxy2_0_1);
	if (frame->NodeMd->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__DoubleHdf5Array)
	{	
		if (hdfProxy == nullptr)
			throw invalid_argument("No Hdf Proxy");
		else
			hdfProxy->readArrayNdOfDoubleValues(static_cast<resqml2__DoubleHdf5Array*>(frame->NodeMd)->Values->PathInHdfFile, values);
	}
	else if (frame->NodeMd->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__DoubleLatticeArray)
	{
		values[0] = static_cast<resqml2__DoubleLatticeArray*>(frame->NodeMd)->StartValue;
		resqml2__DoubleConstantArray* constantArray = static_cast<resqml2__DoubleLatticeArray*>(frame->NodeMd)->Offset[0];
		for (ULONG64 inc = 1; inc <= constantArray->Count; ++inc)
			values[inc] = values[0] + (inc * constantArray->Value);
	}
	else
		throw logic_error("The array structure of MD is not supported?");
}

void WellboreFrameRepresentation::getMdAsFloatValues(float *  values)
{
	_resqml2__WellboreFrameRepresentation* frame = static_cast<_resqml2__WellboreFrameRepresentation*>(gsoapProxy2_0_1);
	if (frame->NodeMd->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__DoubleHdf5Array)
	{
		if (hdfProxy == nullptr)
			throw invalid_argument("No Hdf Proxy");
		else
			hdfProxy->readArrayNdOfFloatValues(static_cast<resqml2__DoubleHdf5Array*>(frame->NodeMd)->Values->PathInHdfFile, values);
	}
	else if (frame->NodeMd->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__DoubleLatticeArray)
	{
		values[0] = static_cast<resqml2__DoubleLatticeArray*>(frame->NodeMd)->StartValue;
		resqml2__DoubleConstantArray* constantArray = static_cast<resqml2__DoubleLatticeArray*>(frame->NodeMd)->Offset[0];
		for (ULONG64 inc = 1; inc <= constantArray->Count; ++inc)
			values[inc] = values[0] + (inc * constantArray->Value);
	}
	else
		throw logic_error("The array structure of MD is not supported?");
}

std::string WellboreFrameRepresentation::getWellboreTrajectoryUuid() const
{
	return static_cast<_resqml2__WellboreFrameRepresentation*>(gsoapProxy2_0_1)->Trajectory->UUID;
}

gsoap_resqml2_0_1::eml20__DataObjectReference* WellboreFrameRepresentation::getLocalCrsDor() const
{
	return trajectory->getLocalCrsDor();
}

std::string WellboreFrameRepresentation::getHdfProxyUuid() const
{
	_resqml2__WellboreFrameRepresentation* frame = static_cast<_resqml2__WellboreFrameRepresentation*>(gsoapProxy2_0_1);
	if (frame->NodeMd->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__DoubleHdf5Array)
	{
		return static_cast<resqml2__DoubleHdf5Array*>(frame->NodeMd)->Values->HdfProxy->UUID;
	}
	else
		return "";
}