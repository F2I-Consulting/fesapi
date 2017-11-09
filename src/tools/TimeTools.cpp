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
