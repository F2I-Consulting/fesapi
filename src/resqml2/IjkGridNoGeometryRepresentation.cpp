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
#include "IjkGridNoGeometryRepresentation.h"

using namespace std;
using namespace gsoap_resqml2_0_1;
using namespace RESQML2_NS;

uint64_t IjkGridNoGeometryRepresentation::getXyzPointCountOfPatch(uint64_t patchIndex) const
{
	if (patchIndex >= getPatchCount()) {
		throw out_of_range("An ijk grid has a maximum of one patch.");
	}

	if (getParentGrid() != nullptr && getParentGrid()->getXmlTag() == "IjkGridRepresentation") {
		const uint64_t kIntervalCount = getRegridIntervalCount('k');
		std::unique_ptr<uint64_t[]> kChildCellCountPerInterval(new uint64_t[kIntervalCount]);
		getRegridCellCountPerInterval('k', kChildCellCountPerInterval.get(), true);
		const uint64_t jIntervalCount = getRegridIntervalCount('j');
		std::unique_ptr<uint64_t[]> jChildCellCountPerInterval(new uint64_t[jIntervalCount]);
		getRegridCellCountPerInterval('j', jChildCellCountPerInterval.get(), true);
		const uint64_t iIntervalCount = getRegridIntervalCount('i');
		std::unique_ptr<uint64_t[]> iChildCellCountPerInterval(new uint64_t[iIntervalCount]);
		getRegridCellCountPerInterval('i', iChildCellCountPerInterval.get(), true);

		uint64_t kCount = 1;
		uint64_t jCount = 1;
		uint64_t iCount = 1;
		for (uint64_t kInterval = 0; kInterval < kIntervalCount; ++kInterval) {
			kCount += kChildCellCountPerInterval[kInterval];
		}
		for (uint64_t jInterval = 0; jInterval < jIntervalCount; ++jInterval) {
			jCount += jChildCellCountPerInterval[jInterval];
		}
		for (uint64_t iInterval = 0; iInterval < iIntervalCount; ++iInterval) {
			iCount += iChildCellCountPerInterval[iInterval];
		}

		return iCount * jCount * kCount;
	}
	else if (getParentGrid() == nullptr) {
		return getCellCount(); // There should be only one XYZ (center) per cell
	}
	else {
		throw logic_error("Not yet implemented. Please use parent window information or geometrical property information.");
	}
}

void IjkGridNoGeometryRepresentation::getXyzPointsOfPatch(uint64_t patchIndex, double *) const
{
	if (patchIndex >= getPatchCount())
		throw out_of_range("An ijk grid has a maximum of one patch.");

	throw logic_error("Not implemented yet. Please use parent window information or geometrical property information.");
}

AbstractIjkGridRepresentation::geometryKind IjkGridNoGeometryRepresentation::getGeometryKind() const
{
	return AbstractIjkGridRepresentation::geometryKind::NO_GEOMETRY;
}
