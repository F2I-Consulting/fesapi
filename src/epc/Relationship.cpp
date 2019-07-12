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
#include "Relationship.h"

#include <sstream>

using namespace std; // in order not to prefix by "std::" for each class in the "std" namespace. Never use "using namespace" in *.h file but only in*.cpp file!!!
using namespace epc; // in order not to prefix by "epc::" for each class in the "epc" namespace. Never use "using namespace" in *.h file but only in*.cpp file!!!

Relationship::Relationship(const bool & internalTarget):
	internalTarget(internalTarget), target(), type(), id()
{
}

Relationship::Relationship(const string & rsTarget, const string & rsType,const string & rsId, const bool & internalTarget):
	internalTarget(internalTarget),target(rsTarget),type(rsType),id(rsId)
{
	if (isdigit(id[0]) != 0)
		id = "_" + id;
}

string Relationship::toString() const
{
	ostringstream oss;

	oss << "<Relationship Id=\"" << id << "\" Type=\"" << type << "\" Target=\"" << target << "\"";
	if (!internalTarget)
		oss << " TargetMode=\"External\"/>";
	else
		oss << "/>";

	return oss.str();
}

bool Relationship::isInternalTarget() const
{
	return internalTarget;
}

const std::string& Relationship::getTarget() const
{
	return target;
}

const std::string& Relationship::getType() const
{
	return type;
}

const std::string& Relationship::getId() const
{
	return id;
}

void Relationship::setIsExternalTarget() 
{
	internalTarget = false;
}

void Relationship::setIsInternalTarget() 
{
	internalTarget = true;
}

void Relationship::setTarget(const string & rsTarget) 
{
	target = rsTarget;
}

void Relationship::setType(const string & rsType) 
{
	type = rsType;
}

void Relationship::setId(const string & rsId)
{
	if (isdigit(rsId[0]) != 0)
		id = "_" + rsId;
	else
		id = rsId;
}

bool epc::operator==(const Relationship& r1, const Relationship& r2)
{
	return
		(r2.getId() == r1.getId()) &&
		(r2.getType() == r1.getType()) &&
		(r2.getTarget() == r1.getTarget());
}















