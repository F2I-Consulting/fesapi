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
#include "AbstractLocal3dCrsTest.h"

using namespace resqml2_0_1test;
using namespace COMMON_NS;
using namespace std;

AbstractLocal3dCrsTest::AbstractLocal3dCrsTest(const string & epcDocPath, const string & uuid, const string & title)
	: AbstractResqmlDataObjectTest(epcDocPath, uuid, title) {
}

AbstractLocal3dCrsTest::AbstractLocal3dCrsTest(EpcDocument* epcDoc, const string & uuid, const string & title)
	: AbstractResqmlDataObjectTest(epcDoc, uuid, title) {
}

