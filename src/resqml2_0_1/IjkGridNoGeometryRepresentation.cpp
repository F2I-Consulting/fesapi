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

#include "resqml2_0_1/IjkGridNoGeometryRepresentation.h"

#include <stdexcept>

#include "resqml2/AbstractFeatureInterpretation.h"

using namespace std;
using namespace gsoap_resqml2_0_1;
using namespace RESQML2_0_1_NS;

IjkGridNoGeometryRepresentation::IjkGridNoGeometryRepresentation(soap* soapContext,
			const std::string & guid, const std::string & title,
			const unsigned int & iCount, const unsigned int & jCount, const unsigned int & kCount):
			AbstractIjkGridRepresentation(soapContext, nullptr, guid, title, iCount, jCount, kCount)
{
}

IjkGridNoGeometryRepresentation::IjkGridNoGeometryRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp,
		const std::string & guid, const std::string & title,
		const unsigned int & iCount, const unsigned int & jCount, const unsigned int & kCount):
	AbstractIjkGridRepresentation(interp, nullptr, guid, title, iCount, jCount, kCount)
{
}

gsoap_resqml2_0_1::eml20__DataObjectReference* IjkGridNoGeometryRepresentation::getHdfProxyDor() const
{
	return nullptr;
}

ULONG64 IjkGridNoGeometryRepresentation::getXyzPointCountOfPatch(const unsigned int & patchIndex) const
{
	if (patchIndex >= getPatchCount()) {
		throw range_error("An ijk grid has a maximum of one patch.");
	}

	if (getParentGrid() != nullptr && getParentGrid()->getGsoapType() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__obj_USCOREIjkGridRepresentation) {
		const ULONG64 kIntervalCount =  getRegridIntervalCount('k');
		ULONG64* const kChildCellCountPerInterval = new ULONG64[kIntervalCount];
		getRegridCellCountPerInterval('k', kChildCellCountPerInterval, true);
		const ULONG64 jIntervalCount = getRegridIntervalCount('j');
		ULONG64* const jChildCellCountPerInterval = new ULONG64[jIntervalCount];
		getRegridCellCountPerInterval('j', jChildCellCountPerInterval, true);
		const ULONG64 iIntervalCount = getRegridIntervalCount('i');
		ULONG64* const iChildCellCountPerInterval = new ULONG64[iIntervalCount];
		getRegridCellCountPerInterval('i', iChildCellCountPerInterval, true);
		
		ULONG64 kCount = 1;
		ULONG64 jCount = 1;
		ULONG64 iCount = 1;
		for (ULONG64 kInterval = 0; kInterval < kIntervalCount; ++kInterval) {
			kCount += kChildCellCountPerInterval[kInterval];
		}
		for (ULONG64 jInterval = 0; jInterval < jIntervalCount; ++jInterval) {
			jCount += jChildCellCountPerInterval[jInterval];
		}
		for (ULONG64 iInterval = 0; iInterval < iIntervalCount; ++iInterval) {
			iCount += iChildCellCountPerInterval[iInterval];
		}

		delete [] kChildCellCountPerInterval;
		delete [] jChildCellCountPerInterval;
		delete [] iChildCellCountPerInterval;

		return iCount * jCount * kCount;
	}
	else if (getParentGrid() == nullptr) {
		return getCellCount(); // There should be only one XYZ (center) per cell
	}
	else {
		throw logic_error("Not yet implemented. Please use parent window information or geometrical property information.");
	}
}

void IjkGridNoGeometryRepresentation::getXyzPointsOfPatch(const unsigned int & patchIndex, double *) const
{
	if (patchIndex >= getPatchCount())
		throw range_error("An ijk grid has a maximum of one patch.");

	throw logic_error("Not yet implemented. Please use parent window information or geometrical property information.");
}

AbstractIjkGridRepresentation::geometryKind IjkGridNoGeometryRepresentation::getGeometryKind() const
{
	return NO_GEOMETRY;
}

