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
#include "AbstractObject.h"

using namespace WITSML2_0_NS;

const char* AbstractObject::XML_NS = "witsml20";

std::string AbstractObject::getContentType() const
{
	return "application/x-witsml+xml;version=2.0;type=" + getXmlTag();
}

std::string AbstractObject::getPartNameInEpcDocument() const
{
	return "namespace_witsml20/" + getXmlTag() + "_" + getUuid() + ".xml";
}
