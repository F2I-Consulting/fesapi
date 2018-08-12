/*-----------------------------------------------------------------------
Licensed to the Apache Software Foundation (ASF) under one
or more contributor license agreements.  See the NOTICE file
distributed with this work for additional information
regarding copyright ownership.  The ASF licenses this file
to you under the Apache License, Version 2.0 (the
"License"; you may not use this file except in compliance
with the License.  You may obtain a copy of the License at

  http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing,
software distributed under the License is distributed on an
"AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
KIND, either express or implied.  See the License for the
specific language governing permissions and limitations
under the License.
-----------------------------------------------------------------------*/
#include "tools/GuidTools.h"

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


