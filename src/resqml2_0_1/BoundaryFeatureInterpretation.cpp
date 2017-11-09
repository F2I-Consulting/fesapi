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
#include "resqml2_0_1/BoundaryFeatureInterpretation.h"

#include <algorithm>
#include <stdexcept>

#include "resqml2_0_1/BoundaryFeature.h"
#include "resqml2_0_1/WellboreMarkerFrameRepresentation.h"

using namespace std;
using namespace resqml2_0_1;
using namespace gsoap_resqml2_0_1;
using namespace epc;

const char* BoundaryFeatureInterpretation::XML_TAG = "BoundaryFeatureInterpretation";

BoundaryFeatureInterpretation::BoundaryFeatureInterpretation(BoundaryFeature * feature, const string & guid, const string & title)
{
	if (!feature)
		throw invalid_argument("The interpreted feature cannot be null.");

	gsoapProxy2_0_1 = soap_new_resqml2__obj_USCOREBoundaryFeatureInterpretation(feature->getGsoapContext(), 1);
	_resqml2__BoundaryFeatureInterpretation* interp = static_cast<_resqml2__BoundaryFeatureInterpretation*>(gsoapProxy2_0_1);
	interp->Domain = resqml2__Domain__mixed;
	setInterpretedFeature(feature);

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "", "");
}

vector<Relationship> BoundaryFeatureInterpretation::getAllEpcRelationships() const
{
	vector<Relationship> result = AbstractFeatureInterpretation::getAllEpcRelationships();

	vector<WellboreMarkerFrameRepresentation*> tmp;
	for (unsigned int i = 0; i < wellboreMarkerSet.size(); ++i)
	{
		bool alreadyInserted = (std::find(tmp.begin(), tmp.end(), wellboreMarkerSet[i]->getWellMarkerFrameRepresentation()) != tmp.end());
		if (!alreadyInserted)
		{
			Relationship rel(wellboreMarkerSet[i]->getWellMarkerFrameRepresentation()->getPartNameInEpcDocument(), "", wellboreMarkerSet[i]->getWellMarkerFrameRepresentation()->getUuid());
			rel.setSourceObjectType();
			result.push_back(rel);
			tmp.push_back(wellboreMarkerSet[i]->getWellMarkerFrameRepresentation());
		}
	}
        
	return result;
}
