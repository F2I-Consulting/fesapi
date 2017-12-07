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
#include "resqml2_0_1/LocalDepth3dCrs.h"

#include <stdexcept>

using namespace std;
using namespace resqml2_0_1;
using namespace gsoap_resqml2_0_1;
using namespace epc;

const char* LocalDepth3dCrs::XML_TAG = "LocalDepth3dCrs";

void LocalDepth3dCrs::init(soap* soapContext, const std::string & guid, const std::string & title,
			const double & originOrdinal1, const double & originOrdinal2, const double & originOrdinal3,
			const double & arealRotation,
			const gsoap_resqml2_0_1::eml20__LengthUom & projectedUom,
			const gsoap_resqml2_0_1::eml20__LengthUom & verticalUom, const bool & isUpOriented)
{
	if (soapContext == nullptr) {
		throw invalid_argument("The soap context where the local CRS will be instantiated must exist.");
	}

	gsoapProxy2_0_1 = soap_new_resqml2__obj_USCORELocalDepth3dCrs(soapContext, 1);
	_resqml2__LocalDepth3dCrs* local3dCrs = static_cast<_resqml2__LocalDepth3dCrs*>(gsoapProxy2_0_1);
	local3dCrs->ArealRotation = soap_new_eml20__PlaneAngleMeasure(gsoapProxy2_0_1->soap, 1);
	local3dCrs->ArealRotation->__item = arealRotation;
	local3dCrs->ArealRotation->uom = eml20__PlaneAngleUom__rad;
	local3dCrs->XOffset = originOrdinal1;
	local3dCrs->YOffset = originOrdinal2;
	local3dCrs->ZOffset = originOrdinal3;
	local3dCrs->ZIncreasingDownward = !isUpOriented;
	local3dCrs->ProjectedUom = projectedUom;
	local3dCrs->VerticalUom = verticalUom;

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "", "");
}

LocalDepth3dCrs::LocalDepth3dCrs(soap* soapContext, const std::string & guid, const std::string & title,
			const double & originOrdinal1, const double & originOrdinal2, const double & originOrdinal3,
			const double & arealRotation,
			const gsoap_resqml2_0_1::eml20__LengthUom & projectedUom, const unsigned long & projectedEpsgCode,
			const gsoap_resqml2_0_1::eml20__LengthUom & verticalUom, const unsigned int & verticalEpsgCode, const bool & isUpOriented)
{
	if (projectedEpsgCode == 0 || verticalEpsgCode == 0) {
		throw invalid_argument("An EPSG code cannot be set to 0.");
	}
	init(soapContext, guid, title, originOrdinal1, originOrdinal2, originOrdinal3, arealRotation, projectedUom, verticalUom, isUpOriented);
	_resqml2__LocalDepth3dCrs* local3dCrs = static_cast<_resqml2__LocalDepth3dCrs*>(gsoapProxy2_0_1);

	// Projected CRS
	eml20__ProjectedCrsEpsgCode* projCrs = soap_new_eml20__ProjectedCrsEpsgCode(gsoapProxy2_0_1->soap, 1);
	local3dCrs->ProjectedCrs = projCrs;
	projCrs->EpsgCode = projectedEpsgCode;

	// Vertical CRS
	eml20__VerticalCrsEpsgCode* vertCrs = soap_new_eml20__VerticalCrsEpsgCode(gsoapProxy2_0_1->soap, 1);
	local3dCrs->VerticalCrs = vertCrs;
	vertCrs->EpsgCode = verticalEpsgCode;
}

LocalDepth3dCrs::LocalDepth3dCrs(soap* soapContext, const std::string & guid, const std::string & title,
			const double & originOrdinal1, const double & originOrdinal2, const double & originOrdinal3,
			const double & arealRotation,
			const gsoap_resqml2_0_1::eml20__LengthUom & projectedUom, const std::string & projectedUnknownReason,
			const gsoap_resqml2_0_1::eml20__LengthUom & verticalUom, const std::string & verticalUnknownReason, const bool & isUpOriented)
{
	init(soapContext, guid, title, originOrdinal1, originOrdinal2, originOrdinal3, arealRotation, projectedUom, verticalUom, isUpOriented);
	_resqml2__LocalDepth3dCrs* local3dCrs = static_cast<_resqml2__LocalDepth3dCrs*>(gsoapProxy2_0_1);

	// Projected CRS
	eml20__ProjectedUnknownCrs* projCrs = soap_new_eml20__ProjectedUnknownCrs(gsoapProxy2_0_1->soap, 1);
	local3dCrs->ProjectedCrs = projCrs;
	projCrs->Unknown = projectedUnknownReason;

	// Vertical CRS
	eml20__VerticalUnknownCrs* vertCrs = soap_new_eml20__VerticalUnknownCrs(gsoapProxy2_0_1->soap, 1);
	local3dCrs->VerticalCrs = vertCrs;
	vertCrs->Unknown = verticalUnknownReason;
}

LocalDepth3dCrs::LocalDepth3dCrs(soap* soapContext, const std::string & guid, const std::string & title,
			const double & originOrdinal1, const double & originOrdinal2, const double & originOrdinal3,
			const double & arealRotation,
			const gsoap_resqml2_0_1::eml20__LengthUom & projectedUom, const unsigned long & projectedEpsgCode,
			const gsoap_resqml2_0_1::eml20__LengthUom & verticalUom, const std::string & verticalUnknownReason, const bool & isUpOriented)
{
	if (projectedEpsgCode == 0) {
		throw invalid_argument("An EPSG code cannot be set to 0.");
	}
	init(soapContext, guid, title, originOrdinal1, originOrdinal2, originOrdinal3, arealRotation, projectedUom, verticalUom, isUpOriented);
	_resqml2__LocalDepth3dCrs* local3dCrs = static_cast<_resqml2__LocalDepth3dCrs*>(gsoapProxy2_0_1);

	// Projected CRS
	eml20__ProjectedCrsEpsgCode* projCrs = soap_new_eml20__ProjectedCrsEpsgCode(gsoapProxy2_0_1->soap, 1);
	local3dCrs->ProjectedCrs = projCrs;
	projCrs->EpsgCode = projectedEpsgCode;

	// Vertical CRS
	eml20__VerticalUnknownCrs* vertCrs = soap_new_eml20__VerticalUnknownCrs(gsoapProxy2_0_1->soap, 1);
	local3dCrs->VerticalCrs = vertCrs;
	vertCrs->Unknown = verticalUnknownReason;
}

LocalDepth3dCrs::LocalDepth3dCrs(soap* soapContext, const std::string & guid, const std::string & title,
			const double & originOrdinal1, const double & originOrdinal2, const double & originOrdinal3,
			const double & arealRotation,
			const gsoap_resqml2_0_1::eml20__LengthUom & projectedUom, const std::string & projectedUnknownReason,
			const gsoap_resqml2_0_1::eml20__LengthUom & verticalUom, const unsigned int & verticalEpsgCode, const bool & isUpOriented)
{
	if (verticalEpsgCode == 0) {
		throw invalid_argument("An EPSG code cannot be set to 0.");
	}
	init(soapContext, guid, title, originOrdinal1, originOrdinal2, originOrdinal3, arealRotation, projectedUom, verticalUom, isUpOriented);
	_resqml2__LocalDepth3dCrs* local3dCrs = static_cast<_resqml2__LocalDepth3dCrs*>(gsoapProxy2_0_1);

	// Projected CRS
	eml20__ProjectedUnknownCrs* projCrs = soap_new_eml20__ProjectedUnknownCrs(gsoapProxy2_0_1->soap, 1);
	local3dCrs->ProjectedCrs = projCrs;
	projCrs->Unknown = projectedUnknownReason;

	// Vertical CRS
	eml20__VerticalCrsEpsgCode* vertCrs = soap_new_eml20__VerticalCrsEpsgCode(gsoapProxy2_0_1->soap, 1);
	local3dCrs->VerticalCrs = vertCrs;
	vertCrs->EpsgCode = verticalEpsgCode;
}
