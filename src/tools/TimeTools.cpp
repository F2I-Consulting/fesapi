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

#include <ctime>
#include <sstream>
#include <iomanip>

using namespace std;
/*
std::string timeTools::convertMicrosecondUnixTimestampToIso(long long ts)
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
*/
std::string timeTools::convertUnixTimestampToIso(time_t ts)
{
	char buf[20]; // 19 for the string below +1 for the terminating char
	strftime(buf, 20, "%Y-%m-%dT%H:%M:%S", gmtime(&ts));

	ostringstream oss;
	oss << buf << 'Z';

	return oss.str();
}

time_t timeTools::convertIsoToUnixTimestamp(const std::string & s)
{
	struct tm tm;
#if defined(__gnu_linux__) || defined(__APPLE__)
	strptime(s.c_str(), "%Y-%m-%dT%H:%M:%S", &tm);
#elif defined(_WIN32)
	std::istringstream iss(s);
	iss >> std::get_time(&tm, "%Y-%m-%dT%H:%M:%S");
#endif
	tm.tm_isdst = -1;
	mktime(&tm);
	return timeTools::timegm(&tm);
}

time_t timeTools::timegm(struct tm *tm)
{
#if defined(__gnu_linux__) || defined(__APPLE__)
	time_t ret;
	char *tz;

	tz = getenv("TZ");
	setenv("TZ", "", 1);
	tzset();
	ret = mktime(tm);
	if (tz)
		setenv("TZ", tz, 1);
	else
		unsetenv("TZ");
	tzset();
	return ret;
#elif defined(_WIN32)
	return _mkgmtime(tm);
#endif
}
