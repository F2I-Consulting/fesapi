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
#pragma once

#if defined(_WIN32)
#include <objbase.h>
#endif

#include <string>
#include <array>
#include <cstdint>
#include <algorithm>

namespace GuidTools
{
#if defined(_WIN32)
	inline
#endif
	std::string generateUidAsString()
#if defined(_WIN32)
	{
		GUID sessionGUID = GUID_NULL;
		HRESULT hr = CoCreateGuid(&sessionGUID);
		wchar_t uuidWStr[39];
		StringFromGUID2(sessionGUID, uuidWStr, 39);
		uuidWStr[37] = '\0'; // Delete the closing bracket
		char uuidStr[37];
		wcstombs(uuidStr, uuidWStr + 1, 39); // +1 in order not to take into account the opening bracket
		for (size_t i = 0; i < 37; ++i) {
			uuidStr[i] = tolower(uuidStr[i]);
		}

		return uuidStr;
	}
#else
	;
#endif

#if defined(_WIN32)
	inline
#endif
		std::array<uint8_t, 16> generateUidAsByteArray()
#if defined(_WIN32)
	{
		GUID sessionGUID = GUID_NULL;
		HRESULT hr = CoCreateGuid(&sessionGUID);

		std::array<uint8_t, 16> result;

		std::copy_n(static_cast<uint8_t*>(static_cast<void*>(&sessionGUID.Data1)),
			sizeof sessionGUID.Data1,
			result.begin());
		std::copy_n(static_cast<uint8_t*>(static_cast<void*>(&sessionGUID.Data2)),
			sizeof sessionGUID.Data2,
			result.begin() + sizeof sessionGUID.Data1);
		std::copy_n(static_cast<uint8_t*>(static_cast<void*>(&sessionGUID.Data3)),
			sizeof sessionGUID.Data3,
			result.begin() + sizeof sessionGUID.Data1 + sizeof sessionGUID.Data2);
		std::copy_n(static_cast<uint8_t*>(static_cast<void*>(&sessionGUID.Data4)),
			sizeof sessionGUID.Data4,
			result.begin() + sizeof sessionGUID.Data1 + sizeof sessionGUID.Data2 + sizeof sessionGUID.Data3);

		return result;
	}
#else
		;
#endif
}
