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
#include "ContentType.h"

using namespace std; // in order not to prefix by "std::" for each class in the "std" namespace. Never use "using namespace" in *.h file but only in*.cpp file!!!
using namespace epc; // in order not to prefix by "epc::" for each class in the "epc" namespace. Never use "using namespace" in *.h file but only in*.cpp file!!!

ContentType::ContentType(const bool & isAssociatedToAnExtension, const std::string & contentType, const std::string & extensionOrPartName):
	isAssociatedToAnExtension(isAssociatedToAnExtension), contentTypeString(contentType), extensionOrPartName(extensionOrPartName)
{
	// Add the first character as slash if we forgot to add it
	if (!isAssociatedToAnExtension && extensionOrPartName[0] != '/')
		this->extensionOrPartName = '/' + extensionOrPartName;

	// delete star and dot from extension if we forgot not to give them for an extension
	if (isAssociatedToAnExtension && (extensionOrPartName[0] == '*' || extensionOrPartName[0] == '.'))
		this->extensionOrPartName = extensionOrPartName.substr(1);
}

const std::string & ContentType::getContentTypeString() const
{
	return contentTypeString;
}

const std::string & ContentType::getExtensionOrPartName() const
{
	return extensionOrPartName;
}

std::string ContentType::toString() const
{
	if (isAssociatedToAnExtension)
		return "<Default Extension=\"" + extensionOrPartName + "\" ContentType=\"" + contentTypeString + "\" />";
	else
		return "<Override PartName=\"" + extensionOrPartName + "\" ContentType=\"" + contentTypeString + "\"/>";
}
