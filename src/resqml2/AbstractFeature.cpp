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
#include "resqml2/AbstractFeature.h"

#include <stdexcept>

using namespace resqml2;
using namespace std;
using namespace epc;

std::vector<AbstractFeatureInterpretation*> AbstractFeature::getInterpretationSet() const
{
	return interpretationSet;
}

unsigned int AbstractFeature::getInterpretationCount() const
{
	return interpretationSet.size();
}

AbstractFeatureInterpretation*	AbstractFeature::getInterpretation(const unsigned int & index) const
{
	if (interpretationSet.size() > index) {
		return interpretationSet[index];
	}
	else {
		throw range_error("The interpretation index is out of the range of the interpretation set of the feature.");
	}
}

vector<Relationship> AbstractFeature::getAllEpcRelationships() const
{
	vector<Relationship> result;

	for (unsigned int i = 0; i < interpretationSet.size(); ++i) {
		if (interpretationSet[i] != nullptr) {
			Relationship rel(interpretationSet[i]->getPartNameInEpcDocument(), "", interpretationSet[i]->getUuid());
			rel.setSourceObjectType();
			result.push_back(rel);
		}
		else {
			throw domain_error("The interpretation associated to the feature cannot be nullptr.");
		}
	}

	return result;
}

