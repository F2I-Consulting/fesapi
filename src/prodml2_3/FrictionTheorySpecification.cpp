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
#include "FrictionTheorySpecification.h"

using namespace PRODML2_3_NS;
using namespace gsoap_eml2_3;

void FrictionTheorySpecification::pushBackPrsvParameter(double a1, double a2, double b1, double b2, double c2, const std::string & fluidComponentReference)
{
	prodml23__PrsvParameter* param = soap_new_prodml23__PrsvParameter(gsoapProxy->soap);
	static_cast<gsoap_eml2_3::prodml23__FrictionTheory*>(gsoapProxy)->PrsvParameter.push_back(param);
	param->a1 = a1;
	param->a2 = a2;
	param->b1 = b1;
	param->b2 = b2;
	param->c2 = c2;
	param->fluidComponentReference = fluidComponentReference;
}
