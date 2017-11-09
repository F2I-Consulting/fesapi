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
#include "resqml2/AbstractLocal3dCrs.h"

#include <stdexcept>
#include <algorithm>

#include "resqml2/AbstractRepresentation.h"

#include "tools/Trigonometry.h"

using namespace std;
using namespace resqml2;
using namespace epc;

void AbstractLocal3dCrs::addRepresentation(AbstractRepresentation* rep)
{
	repSet.push_back(rep);
}

vector<Relationship> AbstractLocal3dCrs::getAllEpcRelationships() const
{
	vector<Relationship> result;

	// Geometry/Representation set
	for (size_t i = 0; i < repSet.size(); i++)
	{
		Relationship rel(repSet[i]->getPartNameInEpcDocument(), "", repSet[i]->getUuid());
		rel.setSourceObjectType();
		result.push_back(rel);
	}

	// MD information set
	for (size_t i = 0; i < mdDatumSet.size(); i++)
	{
		Relationship rel(mdDatumSet[i]->getPartNameInEpcDocument(), "", mdDatumSet[i]->getUuid());
		rel.setSourceObjectType();
		result.push_back(rel);
	}

	return result;
}

void AbstractLocal3dCrs::convertXyzPointsToGlobalCrs(double * xyzPoints, const ULONG64 & xyzPointCount, bool withoutTranslation) const
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
		double originOrdinal1 = getOriginOrdinal1();
		double originOrdinal2 = getOriginOrdinal2();
		double originOrdinal3 = getZOffset();
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
