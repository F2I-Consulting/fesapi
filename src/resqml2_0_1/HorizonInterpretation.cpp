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
#include "resqml2_0_1/HorizonInterpretation.h"

#include <algorithm>
#include <stdexcept>

#include "resqml2_0_1/Horizon.h"
#include "resqml2_0_1/StructuralOrganizationInterpretation.h"

using namespace std;
using namespace resqml2_0_1;
using namespace gsoap_resqml2_0_1;
using namespace epc;

const char* HorizonInterpretation::XML_TAG = "HorizonInterpretation";

HorizonInterpretation::HorizonInterpretation(Horizon * horizon, const string & guid, const string & title)
{
	if (!horizon)
		throw invalid_argument("The interpreted horizon cannot be null.");

	gsoapProxy2_0_1 = soap_new_resqml2__obj_USCOREHorizonInterpretation(horizon->getGsoapContext(), 1);

	static_cast<_resqml2__HorizonInterpretation*>(gsoapProxy2_0_1)->Domain = resqml2__Domain__mixed;

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "", "");

	setInterpretedFeature(horizon);
}

vector<Relationship> HorizonInterpretation::getAllEpcRelationships() const
{
	vector<Relationship> result = BoundaryFeatureInterpretation::getAllEpcRelationships();

	for (unsigned int i = 0; i < structuralOrganizationInterpretationSet.size(); ++i)
	{
		Relationship rel(structuralOrganizationInterpretationSet[i]->getPartNameInEpcDocument(), "", structuralOrganizationInterpretationSet[i]->getUuid());
		rel.setSourceObjectType();
		result.push_back(rel);
	}

	for (unsigned int i = 0; i < stratigraphicColumnRankInterpretationSet.size(); ++i)
	{
		Relationship rel(stratigraphicColumnRankInterpretationSet[i]->getPartNameInEpcDocument(), "", stratigraphicColumnRankInterpretationSet[i]->getUuid());
		rel.setSourceObjectType();
		result.push_back(rel);
	}
        
	return result;
}
