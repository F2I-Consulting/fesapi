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
#include "PvtSpecification.h"

#include <stdexcept>

using namespace PRODML2_1_NS;
using namespace gsoap_eml2_2;

gsoap_eml2_2::prodml21__PvtModelParameterKind PvtSpecification::getCoefficientKind(unsigned int index) const
{
	if (index >= getCoefficientCount()) {
		throw std::out_of_range("The index is out of range");
	}

	gsoap_eml2_2::prodml21__PvtModelParameterKind result;
	if (gsoap_eml2_2::soap_s2prodml21__PvtModelParameterKind(gsoapProxy->soap, static_cast<gsoap_eml2_2::prodml21__AbstractPvtModel*>(gsoapProxy)->PvtModelParameterSet->Coefficient[index]->kind.c_str(), &result) != SOAP_OK) {
		throw std::logic_error("The kinf of coefficient " + static_cast<gsoap_eml2_2::prodml21__AbstractPvtModel*>(gsoapProxy)->PvtModelParameterSet->Coefficient[index]->kind + " is not recognized");
	}

	return result;
}

void PvtSpecification::pushBackCoefficient(double value, gsoap_eml2_2::prodml21__PvtModelParameterKind kind, const std::string & name)
{
	if (static_cast<gsoap_eml2_2::prodml21__AbstractPvtModel*>(gsoapProxy)->PvtModelParameterSet == nullptr) {
		static_cast<gsoap_eml2_2::prodml21__AbstractPvtModel*>(gsoapProxy)->PvtModelParameterSet = soap_new_prodml21__PvtModelParameterSet(gsoapProxy->soap);
	}

	prodml21__PvtModelParameter* param = soap_new_prodml21__PvtModelParameter(gsoapProxy->soap);
	static_cast<gsoap_eml2_2::prodml21__AbstractPvtModel*>(gsoapProxy)->PvtModelParameterSet->Coefficient.push_back(param);
	param->__item = value;
	param->kind = gsoap_eml2_2::soap_prodml21__PvtModelParameterKind2s(gsoapProxy->soap, kind);
	if (!name.empty()) {
		param->name = soap_new_std__string(gsoapProxy->soap);
		param->name->assign(name);
	}
}
