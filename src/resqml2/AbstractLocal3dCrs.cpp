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
#include "resqml2/AbstractLocal3dCrs.h"

#include <stdexcept>
#include <algorithm>

#include "resqml2/AbstractRepresentation.h"

#include "tools/Trigonometry.h"

using namespace std;
using namespace RESQML2_NS;
using namespace epc;

void AbstractLocal3dCrs::addRepresentation(AbstractRepresentation* rep)
{
	repSet.push_back(rep);
}

vector<Relationship> AbstractLocal3dCrs::getAllTargetRelationships() const
{
	vector<Relationship> result;
	return result;
}

vector<Relationship> AbstractLocal3dCrs::getAllSourceRelationships() const
{
	vector<Relationship> result = common::AbstractObject::getAllSourceRelationships();

	// Geometry/Representation set
	for (size_t i = 0; i < repSet.size(); ++i)
	{
		Relationship rel(repSet[i]->getPartNameInEpcDocument(), "", repSet[i]->getUuid());
		rel.setSourceObjectType();
		result.push_back(rel);
	}

	// MD information set
	for (size_t i = 0; i < mdDatumSet.size(); ++i)
	{
		Relationship rel(mdDatumSet[i]->getPartNameInEpcDocument(), "", mdDatumSet[i]->getUuid());
		rel.setSourceObjectType();
		result.push_back(rel);
	}

	return result;
}

void AbstractLocal3dCrs::convertXyzPointsToGlobalCrs(double * xyzPoints, ULONG64 xyzPointCount, bool withoutTranslation) const
{
	ULONG64 coordinateCount = xyzPointCount * 3;

	if (getArealRotation() != .0)
	{
		pair<double, double> xRotatedUnitVector = trigonometry::rotateXY(1.0, .0, -getArealRotation(), getArealRotationUom());
		pair<double, double> yRotatedUnitVector = trigonometry::rotateXY(.0, 1.0, -getArealRotation(), getArealRotationUom());
		for (ULONG64 i = 0; i < coordinateCount; i += 3)
		{
			xyzPoints[i] = xRotatedUnitVector.first * xyzPoints[i] + yRotatedUnitVector.first * xyzPoints[i];
			xyzPoints[i + 1] = xRotatedUnitVector.second * xyzPoints[i + 1] + yRotatedUnitVector.second * xyzPoints[i + 1];
		}
	}

	if (!withoutTranslation)
	{
		const double originOrdinal1 = getOriginOrdinal1();
		const double originOrdinal2 = getOriginOrdinal2();
		const double originOrdinal3 = getZOffset();
		if (originOrdinal1 == .0 && originOrdinal2 == .0 && originOrdinal3 == .0)
			return;

		for (ULONG64 i = 0; i < coordinateCount; i += 3)
		{
			xyzPoints[i] += originOrdinal1;
			xyzPoints[i + 1] += originOrdinal2;
			xyzPoints[i + 2] += originOrdinal3;
		}
	}
}

void AbstractLocal3dCrs::addMdDatum(MdDatum* mdInfo)
{
	if (find(mdDatumSet.begin(), mdDatumSet.end(), mdInfo) != mdDatumSet.end())
		mdDatumSet.push_back(mdInfo);
}

double AbstractLocal3dCrs::getOriginOrdinal1() const
{
	if (gsoapProxy2_0_1 != nullptr) {
		return static_cast<gsoap_resqml2_0_1::resqml2__AbstractLocal3dCrs*>(gsoapProxy2_0_1)->XOffset;
	}
	else {
		throw logic_error("Not implemented yet");
	}
}

double AbstractLocal3dCrs::getOriginOrdinal2() const
{
	if (gsoapProxy2_0_1 != nullptr) {
		return static_cast<gsoap_resqml2_0_1::resqml2__AbstractLocal3dCrs*>(gsoapProxy2_0_1)->YOffset;
	}
	else {
		throw logic_error("Not implemented yet");
	}
}

double AbstractLocal3dCrs::getOriginDepthOrElevation() const
{
	if (gsoapProxy2_0_1 != nullptr) {
		return static_cast<gsoap_resqml2_0_1::resqml2__AbstractLocal3dCrs*>(gsoapProxy2_0_1)->ZOffset;
	}
	else {
		throw logic_error("Not implemented yet");
	}
}

double AbstractLocal3dCrs::getArealRotation() const
{
	if (gsoapProxy2_0_1 != nullptr) {
		return static_cast<gsoap_resqml2_0_1::resqml2__AbstractLocal3dCrs*>(gsoapProxy2_0_1)->ArealRotation->__item;
	}
	else {
		throw logic_error("Not implemented yet");
	}
}

gsoap_resqml2_0_1::eml20__PlaneAngleUom AbstractLocal3dCrs::getArealRotationUom() const
{
	if (gsoapProxy2_0_1 != nullptr) {
		return static_cast<gsoap_resqml2_0_1::resqml2__AbstractLocal3dCrs*>(gsoapProxy2_0_1)->ArealRotation->uom;
	}
	else {
		throw logic_error("Not implemented yet");
	}
}

bool AbstractLocal3dCrs::isDepthOriented() const
{
	if (gsoapProxy2_0_1 != nullptr) {
		return static_cast<gsoap_resqml2_0_1::resqml2__AbstractLocal3dCrs*>(gsoapProxy2_0_1)->ZIncreasingDownward;
	}
	else {
		throw logic_error("Not implemented yet");
	}
}

bool AbstractLocal3dCrs::isProjectedCrsDefinedWithEpsg() const
{
	if (gsoapProxy2_0_1 != nullptr) {
		return static_cast<gsoap_resqml2_0_1::resqml2__AbstractLocal3dCrs*>(gsoapProxy2_0_1)->ProjectedCrs->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_eml20__ProjectedCrsEpsgCode;
	}
	else {
		throw logic_error("Not implemented yet");
	}
}

bool AbstractLocal3dCrs::isProjectedCrsUnknown() const
{
	if (gsoapProxy2_0_1 != nullptr) {
		return static_cast<gsoap_resqml2_0_1::resqml2__AbstractLocal3dCrs*>(gsoapProxy2_0_1)->ProjectedCrs->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_eml20__ProjectedUnknownCrs;
	}
	else {
		throw logic_error("Not implemented yet");
	}
}

const std::string & AbstractLocal3dCrs::getProjectedCrsUnknownReason() const
{
	if (isProjectedCrsUnknown() == false)
		throw invalid_argument("The associated projected Crs is not unknown.");

	if (gsoapProxy2_0_1 != nullptr) {
		return static_cast<gsoap_resqml2_0_1::eml20__ProjectedUnknownCrs*>(static_cast<gsoap_resqml2_0_1::resqml2__AbstractLocal3dCrs*>(gsoapProxy2_0_1)->ProjectedCrs)->Unknown;
	}
	else {
		throw logic_error("Not implemented yet");
	}
}

unsigned long long AbstractLocal3dCrs::getProjectedCrsEpsgCode() const
{
	if (isProjectedCrsDefinedWithEpsg() == false)
		throw invalid_argument("The associated projected Crs is not an EPSG one.");

	if (gsoapProxy2_0_1 != nullptr) {
		return static_cast<gsoap_resqml2_0_1::eml20__ProjectedCrsEpsgCode*>(static_cast<gsoap_resqml2_0_1::resqml2__AbstractLocal3dCrs*>(gsoapProxy2_0_1)->ProjectedCrs)->EpsgCode;
	}
	else {
		throw logic_error("Not implemented yet");
	}
}

bool AbstractLocal3dCrs::isVerticalCrsDefinedWithEpsg() const
{
	if (gsoapProxy2_0_1 != nullptr) {
		return static_cast<gsoap_resqml2_0_1::resqml2__AbstractLocal3dCrs*>(gsoapProxy2_0_1)->VerticalCrs->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_eml20__VerticalCrsEpsgCode;
	}
	else {
		throw logic_error("Not implemented yet");
	}
}

bool AbstractLocal3dCrs::isVerticalCrsUnknown() const
{
	if (gsoapProxy2_0_1 != nullptr) {
		return static_cast<gsoap_resqml2_0_1::resqml2__AbstractLocal3dCrs*>(gsoapProxy2_0_1)->VerticalCrs->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_eml20__VerticalUnknownCrs;
	}
	else {
		throw logic_error("Not implemented yet");
	}
}

const std::string & AbstractLocal3dCrs::getVerticalCrsUnknownReason() const
{
	if (isVerticalCrsUnknown() == false)
		throw invalid_argument("The associated vertical Crs is not unknown.");

	if (gsoapProxy2_0_1 != nullptr) {
		return static_cast<gsoap_resqml2_0_1::eml20__VerticalUnknownCrs*>(static_cast<gsoap_resqml2_0_1::resqml2__AbstractLocal3dCrs*>(gsoapProxy2_0_1)->VerticalCrs)->Unknown;
	}
	else {
		throw logic_error("Not implemented yet");
	}
}

unsigned long long AbstractLocal3dCrs::getVerticalCrsEpsgCode() const
{
	if (isVerticalCrsDefinedWithEpsg() == false)
		throw invalid_argument("The associated vertical Crs is not an EPSG one.");

	if (gsoapProxy2_0_1 != nullptr) {
		return static_cast<gsoap_resqml2_0_1::eml20__VerticalCrsEpsgCode*>(static_cast<gsoap_resqml2_0_1::resqml2__AbstractLocal3dCrs*>(gsoapProxy2_0_1)->VerticalCrs)->EpsgCode;
	}
	else {
		throw logic_error("Not implemented yet");
	}
}

gsoap_resqml2_0_1::eml20__LengthUom AbstractLocal3dCrs::getProjectedCrsUnit() const
{
	if (gsoapProxy2_0_1 != nullptr) {
		return static_cast<gsoap_resqml2_0_1::resqml2__AbstractLocal3dCrs*>(gsoapProxy2_0_1)->ProjectedUom;
	}
	else {
		throw logic_error("Not implemented yet");
	}
}

string AbstractLocal3dCrs::getProjectedCrsUnitAsString() const
{
	if (gsoapProxy2_0_1 != nullptr) {
		return gsoap_resqml2_0_1::soap_eml20__LengthUom2s(gsoapProxy2_0_1->soap, static_cast<gsoap_resqml2_0_1::resqml2__AbstractLocal3dCrs*>(gsoapProxy2_0_1)->ProjectedUom);
	}
	else {
		throw logic_error("Not implemented yet");
	}
}

gsoap_resqml2_0_1::eml20__LengthUom AbstractLocal3dCrs::getVerticalCrsUnit() const
{
	if (gsoapProxy2_0_1 != nullptr) {
		return static_cast<gsoap_resqml2_0_1::resqml2__AbstractLocal3dCrs*>(gsoapProxy2_0_1)->VerticalUom;
	}
	else {
		throw logic_error("Not implemented yet");
	}
}

string AbstractLocal3dCrs::getVerticalCrsUnitAsString() const
{
	if (gsoapProxy2_0_1 != nullptr) {
		return gsoap_resqml2_0_1::soap_eml20__LengthUom2s(gsoapProxy2_0_1->soap, static_cast<gsoap_resqml2_0_1::resqml2__AbstractLocal3dCrs*>(gsoapProxy2_0_1)->VerticalUom);
	}
	else {
		throw logic_error("Not implemented yet");
	}
}

gsoap_resqml2_0_1::eml20__AxisOrder2d AbstractLocal3dCrs::getAxisOrder() const
{
	if (gsoapProxy2_0_1 != nullptr) {
		return static_cast<gsoap_resqml2_0_1::resqml2__AbstractLocal3dCrs*>(gsoapProxy2_0_1)->ProjectedAxisOrder;
	}
	else {
		throw logic_error("Not implemented yet");
	}
}

void AbstractLocal3dCrs::setAxisOrder(gsoap_resqml2_0_1::eml20__AxisOrder2d axisOrder) const
{
	if (gsoapProxy2_0_1 != nullptr) {
		static_cast<gsoap_resqml2_0_1::resqml2__AbstractLocal3dCrs*>(gsoapProxy2_0_1)->ProjectedAxisOrder = axisOrder;
	}
	else {
		throw logic_error("Not implemented yet");
	}
}
