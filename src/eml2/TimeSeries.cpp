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
#include "TimeSeries.h"

#include <stdexcept>

#include "../tools/TimeTools.h"

#include "../resqml2/AbstractProperty.h"

using namespace std;
using namespace EML2_NS;

const char* TimeSeries::XML_TAG = "TimeSeries";

void TimeSeries::pushBackTimestamp(time_t timestamp)
{
	pushBackTimestamp(*gmtime(&timestamp));
}

time_t TimeSeries::getTimestamp(unsigned int index) const
{
	tm temp = getTimestampAsTimeStructure(index);
	return timeTools::timegm(&temp);
}

std::vector<RESQML2_NS::AbstractProperty *> TimeSeries::getPropertySet() const
{
	return getRepository()->getSourceObjects<RESQML2_NS::AbstractProperty>(this);
}
