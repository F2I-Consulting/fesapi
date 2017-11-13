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
#include "resqml2_0_1/MdDatum.h"

#include <stdexcept>

#include "resqml2/AbstractLocal3dCrs.h"
#include "resqml2_0_1/WellboreTrajectoryRepresentation.h"

using namespace std;
using namespace resqml2_0_1;
using namespace gsoap_resqml2_0_1;
using namespace epc;

MdDatum::MdDatum(soap* soapContext, const string & guid, const string & title,
			resqml2::AbstractLocal3dCrs * locCrs, const resqml2__MdReference & originKind,
			const double & referenceLocationOrdinal1, const double & referenceLocationOrdinal2, const double & referenceLocationOrdinal3)
{
	if (soapContext == nullptr)
		throw invalid_argument("The soap context must exist");

	gsoapProxy2_0_1 = soap_new_resqml2__obj_USCOREMdDatum(soapContext, 1);
	_resqml2__MdDatum* mdInfo = static_cast<_resqml2__MdDatum*>(gsoapProxy2_0_1);
	
	setLocalCrs(locCrs);

	mdInfo->MdReference = originKind;
	mdInfo->Location = soap_new_resqml2__Point3d(soapContext, 1);
	mdInfo->Location->Coordinate1 = referenceLocationOrdinal1;
	mdInfo->Location->Coordinate2 = referenceLocationOrdinal2;
	mdInfo->Location->Coordinate3 = referenceLocationOrdinal3;
	
	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "", "");
}

void MdDatum::setXmlLocalCrs(resqml2::AbstractLocal3dCrs * localCrs)
{
	_resqml2__MdDatum* mdDatum = static_cast<_resqml2__MdDatum*>(gsoapProxy2_0_1);
	mdDatum->LocalCrs = localCrs->newResqmlReference();
}

double MdDatum::getX() const
{
	return static_cast<_resqml2__MdDatum*>(gsoapProxy2_0_1)->Location->Coordinate1;
}

double MdDatum::getXInGlobalCrs() const
{	
	double result[] = {getX(), getY(), .0};
	if (result[0] != result[0])
		return result[0];

	getLocalCrs()->convertXyzPointsToGlobalCrs(result, 1);

	return result[0];
}

double MdDatum::getY() const
{
	return static_cast<_resqml2__MdDatum*>(gsoapProxy2_0_1)->Location->Coordinate2;
}

double MdDatum::getYInGlobalCrs() const
{
	double result[] = {getX(), getY(), .0};
	if (result[0] != result[0])
		return result[0];

	getLocalCrs()->convertXyzPointsToGlobalCrs(result, 1);

	return result[1];
}

double MdDatum::getZ() const
{
	return static_cast<_resqml2__MdDatum*>(gsoapProxy2_0_1)->Location->Coordinate3;
}

double MdDatum::getZInGlobalCrs() const
{
	double originOrdinal3 = .0;
	resqml2::AbstractLocal3dCrs* localCrs = getLocalCrs();
	if (localCrs->getGsoapType() != SOAP_TYPE_gsoap_resqml2_0_1_resqml2__obj_USCORELocalTime3dCrs)
		originOrdinal3 = localCrs->getOriginDepthOrElevation();
	return getZ() + originOrdinal3;
}

gsoap_resqml2_0_1::resqml2__MdReference MdDatum::getOriginKind() const
{
	return static_cast<_resqml2__MdDatum*>(gsoapProxy2_0_1)->MdReference;
}

gsoap_resqml2_0_1::eml20__DataObjectReference* MdDatum::getLocalCrsDor() const
{
	return static_cast<_resqml2__MdDatum*>(gsoapProxy2_0_1)->LocalCrs;
}
