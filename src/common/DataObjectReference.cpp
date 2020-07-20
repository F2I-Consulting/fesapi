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
#include "DataObjectReference.h"

#include "AbstractObject.h"

using namespace COMMON_NS;

DataObjectReference::DataObjectReference(AbstractObject const * dataObj)
	: dor20(nullptr), dor21(nullptr), dor22(nullptr), dor23(nullptr)
{
	std::string ns = dataObj->getXmlNamespace();
	if (ns == "resqml20" || ns == "eml20") {
		dor20 = dataObj->newResqmlReference();
	}
	else if (ns == "witsml20" || ns == "eml21") {
		dor21 = dataObj->newEmlReference();
	}
	else if (ns == "prodml21" || ns == "eml22") {
		dor22 = dataObj->newEml22Reference();
	}
	else if (ns == "resqml22" || ns == "eml23") {
		dor23 = dataObj->newEml23Reference();
	}
}
