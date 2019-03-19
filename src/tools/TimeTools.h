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

#include <ctime>
#include <string>

namespace timeTools
{
	/**
	* Convert an Unix timestamp which is given in microseconds into a date in ISO format.
	*/
	// No more used because DAS support has been removed
	// Disabled because it needs to include <cmath> which creates a conflict with gsoap 2.8.81 : see https://github.com/F2I-Consulting/fesapi/issues/90
	//std::string convertMicrosecondUnixTimestampToIso(long long ts);

	/**
	* Convert an Unix timestamp which is given in seconds into a date in ISO format.
	*/
	std::string convertUnixTimestampToIso(time_t ts);

	/**
	* Converts a UTC time (given in seconds) represented by a string to a UTC time represented by a time_t type.
	*/
	time_t convertIsoToUnixTimestamp(const std::string & s);

	/**
	* Converts a UTC time represented by a tm``struct to a UTC time represented by a time_t type.
	*/
	time_t timegm(struct tm *tm);
}

