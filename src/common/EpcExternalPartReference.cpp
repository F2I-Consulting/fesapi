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
#include "common/EpcExternalPartReference.h"

#include <stdexcept>

#include "tools/GuidTools.h"

#include "resqml2/AbstractRepresentation.h"
#include "resqml2/AbstractProperty.h"
#include "prodml2_0/DasAcquisition.h"

using namespace std;
using namespace common;
using namespace gsoap_resqml2_0_1;
using namespace epc;

const char* EpcExternalPartReference::XML_TAG = "EpcExternalPartReference";

EpcExternalPartReference::EpcExternalPartReference(const string & packageDirAbsolutePath, const string & externalFilePath) :
		packageDirectoryAbsolutePath(packageDirAbsolutePath), relativeFilePath(externalFilePath) {
}

string EpcExternalPartReference::getXmlTag() const
{
	return XML_TAG;
}

vector<Relationship> EpcExternalPartReference::getAllEpcRelationships() const
{
	vector<Relationship> result;

	for (size_t i = 0; i < representationSourceObject.size(); ++i) {
		if (representationSourceObject[i] != nullptr) {
			Relationship rel(representationSourceObject[i]->getPartNameInEpcDocument(), "", representationSourceObject[i]->getUuid());
			rel.setExternalPartProxyToMlType();
			result.push_back(rel);
		}
		else {
			throw domain_error("The representation associated to the external EPC reference cannot be nullptr.");
		}
	}

	for (size_t i = 0; i < propertySourceObject.size(); ++i) {
		if (propertySourceObject[i] != nullptr) {
			Relationship rel(propertySourceObject[i]->getPartNameInEpcDocument(), "", propertySourceObject[i]->getUuid());
			rel.setExternalPartProxyToMlType();
			result.push_back(rel);
		}
		else {
			throw domain_error("The property associated to the external EPC reference cannot be nullptr.");
		}
	}

	for (size_t i = 0; i < dasAcquisitionSourceObject.size(); ++i) {
		if (dasAcquisitionSourceObject[i] != nullptr) {
			Relationship rel(dasAcquisitionSourceObject[i]->getPartNameInEpcDocument(), "", dasAcquisitionSourceObject[i]->getUuid());
			rel.setExternalPartProxyToMlType();
			result.push_back(rel);
		}
		else {
			throw domain_error("The das acquisition associated to the external EPC reference cannot be nullptr.");
		}
	}

	// External part
	Relationship relExt(relativeFilePath, "", "Hdf5File", false);
	relExt.setExternalResourceType();
	result.push_back(relExt);

	return result;
}
