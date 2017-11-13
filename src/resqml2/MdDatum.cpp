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
#include "resqml2/MdDatum.h"

#include <stdexcept>

#include "resqml2/AbstractLocal3dCrs.h"
#include "resqml2_0_1/WellboreTrajectoryRepresentation.h"

using namespace std;
using namespace resqml2;
using namespace gsoap_resqml2_0_1;
using namespace epc;

const char* MdDatum::XML_TAG = "MdDatum";

void MdDatum::importRelationshipSetFromEpc(common::EpcDocument* epcDoc)
{
	_resqml2__MdDatum* mdInfo = static_cast<_resqml2__MdDatum*>(gsoapProxy2_0_1);

	AbstractObject* localCrs = epcDoc->getResqmlAbstractObjectByUuid(mdInfo->LocalCrs->UUID);
	if (dynamic_cast<AbstractLocal3dCrs*>(localCrs) != nullptr) {
		updateXml = false;
		setLocalCrs(static_cast<AbstractLocal3dCrs*>(localCrs));
		updateXml = true;
	}
	else {
		throw logic_error("The referenced local crs does not look to be a local crs.");
	}
}

vector<Relationship> MdDatum::getAllEpcRelationships() const
{
	vector<Relationship> result;

	// local 3d CRS
	AbstractLocal3dCrs* localCrs = getLocalCrs();
	if (localCrs != nullptr)
	{
		Relationship relLocalCrs(localCrs->getPartNameInEpcDocument(), "", getLocalCrsUuid());
		relLocalCrs.setDestinationObjectType();
		result.push_back(relLocalCrs);
	}
	else {
		throw domain_error("The local CRS associated to the MD information cannot be nullptr.");
	}

	// WellboreFeature trajectories
	for (size_t i = 0; i < wellboreTrajectoryRepresentationSet.size(); ++i)
	{
		Relationship rel(wellboreTrajectoryRepresentationSet[i]->getPartNameInEpcDocument(), "", wellboreTrajectoryRepresentationSet[i]->getUuid());
		rel.setSourceObjectType();
		result.push_back(rel);
	}

	return result;
}

void MdDatum::setLocalCrs(AbstractLocal3dCrs * localCrs)
{
	localCrs->addMdDatum(this);

	if (updateXml) {
		setXmlLocalCrs(localCrs);
	}
}

std::string MdDatum::getLocalCrsUuid() const
{
	return getLocalCrsDor()->UUID;
}

AbstractLocal3dCrs * MdDatum::getLocalCrs() const
{
	const string uuidLocalCrs = getLocalCrsUuid();
	return static_cast<AbstractLocal3dCrs*>(epcDocument->getResqmlAbstractObjectByUuid(uuidLocalCrs));
}
