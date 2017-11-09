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
#include "Relationship.h"

#include <sstream>

using namespace std; // in order not to prefix by "std::" for each class in the "std" namespace. Never use "using namespace" in *.h file but only in*.cpp file!!!
using namespace epc; // in order not to prefix by "epc::" for each class in the "epc" namespace. Never use "using namespace" in *.h file but only in*.cpp file!!!

Relationship::Relationship(const bool & internalTarget):
	internalTarget(internalTarget)
{
}

Relationship::Relationship(const string & rsTarget, const string & rsType,const string & rsId, const bool & internalTarget):
	target(rsTarget),type(rsType),id(rsId),internalTarget(internalTarget)
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
