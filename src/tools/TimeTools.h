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

#include "date.h"

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
	 *
	 * @param 	ts			The UNIX timestamp.
	 * @param 	withTime	Include or not the time in the output.
	 *
	 * @returns	The unix converted timestamp to ISO.
	 */
	std::string convertUnixTimestampToIso(time_t ts, bool withTime = true);

	/**
	 * Converts a UTC time (given in seconds) represented by a string to a UTC time represented by a
	 * time_t type.
	 *
	 * @param 	s	A std::string to process.
	 *
	 * @returns	The ISO converted to unix timestamp.
	 */
	time_t convertIsoToUnixTimestamp(const std::string & s);

	/**
	 * Converts a UTC time represented by a tm``struct to a UTC time represented by a time_t type.
	 *
	 * @param [in,out]	tm	If non-null, the time.
	 *
	 * @returns	A time_t.
	 */
	time_t timegm(std::tm const& t);

	/**
	 * Converts a UTC time represented by a point in time to the same UTC time represented by tm``struct.
	 * From https://github.com/HowardHinnant/date/wiki/Examples-and-Recipes#components_to_time_point
	 *
	 * @param [in,out]	tp	The point in time to convert.
	 *
	 * @returns	the same point in time in a tm``struct.
	 */
	template <typename Clock, typename Duration>
	std::tm to_calendar_time(std::chrono::time_point<Clock, Duration> tp)
	{
		using namespace date;
		auto date = floor<days>(tp);
		auto ymd = year_month_day(date);
		auto weekday = year_month_weekday(date).weekday_indexed().weekday();
		auto tod = make_time(tp - date);
		days daysSinceJan1 = date - sys_days(ymd.year() / 1 / 1);

		std::tm result;
		result.tm_sec = tod.seconds().count();
		result.tm_min = tod.minutes().count();
		result.tm_hour = tod.hours().count();
		result.tm_mday = (ymd.day() - 0_d).count();
		result.tm_mon = (ymd.month() - January).count();
		result.tm_year = (ymd.year() - 1900_y).count();
		result.tm_wday = (weekday - Sunday).count();
		result.tm_yday = daysSinceJan1.count();
		result.tm_isdst = -1; // Information not available
		return result;
	}

	/**
	* Redefines std::chrono::system_clock::from_time_t to be able to support date superior to year 2262.
	* Indeed Linux's system_clock is nanoseconds and 2262 corresponds to 2^63 nanoseconds since the epoch.
	*/
	date::sys_seconds from_time_t(std::time_t time_t);
}
