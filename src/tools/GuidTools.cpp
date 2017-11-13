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
#include "tools/GuidTools.h"

using namespace tools;
using namespace std;

#if defined(__gnu_linux__) || defined(__APPLE__)

#include <uuid/uuid.h> // Need package "uuid-dev"
#include <iostream>

std::string GuidTools::generateUidAsString()
{
    uuid_t uuid;
    uuid_generate_random(uuid);
    char uuidStr[37];
    uuid_unparse_lower ( uuid, uuidStr );
    return uuidStr;
}

#elif defined(_WIN32)

#include <Windows.h>

string GuidTools::generateUidAsString()
{
	GUID sessionGUID = GUID_NULL;
	HRESULT hr = CoCreateGuid(&sessionGUID);
	wchar_t uuidWStr[39];
	StringFromGUID2(sessionGUID, uuidWStr, 39);
	uuidWStr[37] = '\0'; // Delete the closing bracket
	char uuidStr[37];
	wcstombs(uuidStr, uuidWStr+1, 39); // +1 in order not to take into account the opening bracket
	for (unsigned int i = 0; i < 37; ++i)
		uuidStr[i] = tolower(uuidStr[i]);

	return uuidStr;
}

#endif

