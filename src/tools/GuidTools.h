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
#include <combaseapi.h>
#endif

#include <string>
#include <array>
#include <cstdint>
#include <algorithm>

/** @brief */
namespace GuidTools
{
#if defined(_WIN32)
	inline
#endif

	/**
	 * Generates an UID as string
	 *
	 * @returns	The UID as string.
	 */
	std::string generateUidAsString()
#if defined(_WIN32)
	{
		GUID sessionGUID = GUID_NULL;
		HRESULT hr = CoCreateGuid(&sessionGUID);
		if (hr != S_OK) {
			throw std::logic_error("Windows could not create a GUID.");
		}

		wchar_t uuidWStr[39];
		StringFromGUID2(sessionGUID, uuidWStr, 39);
		uuidWStr[37] = L'\0'; // Delete the closing bracket
		char uuidStr[37];
		// Assume Multi Bytes character set is used!!!
		wcstombs(uuidStr, uuidWStr + 1, 39); // +1 in order not to take into account the opening bracket
		for (size_t i = 0; i < 37; ++i) {
			uuidStr[i] = tolower(uuidStr[i]);
		}

		return uuidStr;
	}
#else
	///< .
	;
#endif

#if defined(_WIN32)
	inline
#endif

		/**
		 * Generates an UID as byte array
		 *
		 * @returns	The UID as byte array.
		 */
		std::array<uint8_t, 16> generateUidAsByteArray()
#if defined(_WIN32)
	{
		GUID sessionGUID = GUID_NULL;
		HRESULT hr = CoCreateGuid(&sessionGUID);
		if (hr != S_OK) {
			throw std::logic_error("Windows could not create a GUID.");
		}

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
		///< .
		;
#endif

#if defined(_WIN32)
	inline
#endif

		/**
		 * Initializes this object from the given string
		 *
		 * @param 	uuidStr	The uuid string.
		 *
		 * @returns	from converted string.
		 */
		std::array<uint8_t, 16> convertFromString(const std::string& uuidStr)
#if defined(_WIN32)
	{
		wchar_t uuidWStr[39];
		uuidWStr[0] = L'{';
		uuidWStr[37] = L'}';
		uuidWStr[38] = L'\0';
		// Assume Multi Bytes character set is used!!!
		mbstowcs(uuidWStr + 1, uuidStr.c_str(), 36);

		IID iid = GUID_NULL;
		HRESULT hr = IIDFromString(uuidWStr, &iid);
		if (hr != S_OK) {
			throw std::logic_error("Windows could not convert the string UUID " + uuidStr + " to an UUID structure.");
		}

		std::array<uint8_t, 16> result;

		std::copy_n(static_cast<uint8_t*>(static_cast<void*>(&iid.Data1)),
			sizeof iid.Data1,
			result.begin());
		std::copy_n(static_cast<uint8_t*>(static_cast<void*>(&iid.Data2)),
			sizeof iid.Data2,
			result.begin() + sizeof iid.Data1);
		std::copy_n(static_cast<uint8_t*>(static_cast<void*>(&iid.Data3)),
			sizeof iid.Data3,
			result.begin() + sizeof iid.Data1 + sizeof iid.Data2);
		std::copy_n(static_cast<uint8_t*>(static_cast<void*>(&iid.Data4)),
			sizeof iid.Data4,
			result.begin() + sizeof iid.Data1 + sizeof iid.Data2 + sizeof iid.Data3);
		
		return result;
	}
#else
		///< .
		;
#endif

#if defined(_WIN32)
	inline
#endif

		/**
		 * Converts an uuidArray to a string
		 *
		 * @param 	uuidArray	Array of uuids.
		 *
		 * @returns	The given data converted to a string.
		 */
		std::string convertToString(const std::array<uint8_t, 16>& uuidArray)
#if defined(_WIN32)
	{
		GUID sessionGUID = GUID_NULL;
		sessionGUID.Data1 = (reinterpret_cast<const unsigned long*>(uuidArray.data()))[0];
		sessionGUID.Data2 = (reinterpret_cast<const unsigned short*>(uuidArray.data()))[sizeof(unsigned long) / sizeof(unsigned short)];
		sessionGUID.Data3 = (reinterpret_cast<const unsigned short*>(uuidArray.data()))[(sizeof(unsigned long) / sizeof(unsigned short)) + 1];
		for (size_t pos = 0; pos < 8; ++pos) {
			sessionGUID.Data4[pos] = uuidArray.data()[8 + pos];
		}

		wchar_t uuidWStr[39];
		StringFromGUID2(sessionGUID, uuidWStr, 39);
		uuidWStr[37] = L'\0'; // Delete the closing bracket
		char uuidStr[37];
		// Assume Multi Bytes character set is used!!!
		wcstombs(uuidStr, uuidWStr + 1, 39); // +1 in order not to take into account the opening bracket
		for (size_t i = 0; i < 37; ++i) {
			uuidStr[i] = tolower(uuidStr[i]);
		}

		return uuidStr;
	}
#else
		///< .
		;
#endif

}
