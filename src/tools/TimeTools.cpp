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
#include "tools/TimeTools.h"

#include <cmath>
#include <ctime>
#include <sstream>

using namespace std;

std::string timeTools::convertMicrosecondUnixTimestampToIso(const long long & ts)
{
	// microsecond part
	long long onlyMicrosec = 0;
	time_t secondUnixTimestamp = 0;
	if (ts > 1e6) {
		double unixTs = ts / static_cast<double>(1e6);
		secondUnixTimestamp = floor(unixTs + 0.5); // floor instead of round https://stackoverflow.com/questions/554204/where-is-round-in-c
		double remainder = unixTs - floor(unixTs); // floor instead of trunc https://stackoverflow.com/questions/6709405/is-there-a-trunc-function-in-c
		onlyMicrosec = floor(remainder*1e6 + 0.5); // floor instead of round https://stackoverflow.com/questions/554204/where-is-round-in-c
	}

	char buf[20]; // 19 for the string below +1 for the terminating char
	strftime(buf, 20, "%Y-%m-%dT%H:%M:%S", gmtime(&secondUnixTimestamp));

	ostringstream oss;
	oss << buf << '.' << onlyMicrosec << "+00:00";

	return oss.str();
}

