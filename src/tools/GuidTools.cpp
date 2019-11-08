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
#include "../tools/GuidTools.h"

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

std::array<uint8_t, 16> GuidTools::generateUidAsByteArray()
{
	uuid_t uuid;
	uuid_generate_random(uuid);
	
	std::array<uint8_t, 16> result;

	std::copy(std::begin(uuid), std::end(uuid), std::begin(result));

	return result;
}

#endif
