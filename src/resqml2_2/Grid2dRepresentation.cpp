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
#include "Grid2dRepresentation.h"

#include <algorithm>
#include <limits>
#include <stdexcept>

#include "H5public.h"

#include "../resqml2/AbstractFeature.h"
#include "../resqml2/AbstractFeatureInterpretation.h"
#include "../eml2/AbstractHdfProxy.h"
#include "../eml2/AbstractLocal3dCrs.h"

using namespace std;
using namespace RESQML2_2_NS;
using namespace gsoap_eml2_3;

const char* Grid2dRepresentation::XML_NS = "resqml22";

Grid2dRepresentation::Grid2dRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp,
	const string & guid, const std::string & title)
{
	if (interp == nullptr) {
		throw invalid_argument("The interpretation cannot be null.");
	}

	gsoapProxy2_3 = soap_new_resqml22__Grid2dRepresentation(interp->getGsoapContext());
	_resqml22__Grid2dRepresentation* singleGrid2dRep = static_cast<_resqml22__Grid2dRepresentation*>(gsoapProxy2_3);

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "");

	// Surface role
	if (interp->getInterpretedFeature()->getGsoapType() == SOAP_TYPE_gsoap_eml2_3_resqml22__SeismicLatticeFeature) {
		singleGrid2dRep->SurfaceRole = resqml22__SurfaceRole::pick;
	}

	interp->getRepository()->addDataObject(this);
	setInterpretation(interp);
}

resqml22__PointGeometry* Grid2dRepresentation::getPointGeometry2_2(unsigned int) const
{
	return static_cast<_resqml22__Grid2dRepresentation*>(gsoapProxy2_3)->Geometry;
}

COMMON_NS::DataObjectReference Grid2dRepresentation::getHdfProxyDor() const
{
	return getHdfProxyDorFromPointGeometryPatch(getPointGeometry2_2(0));
}

uint64_t Grid2dRepresentation::getNodeCountAlongIAxis() const
{
	return static_cast<_resqml22__Grid2dRepresentation*>(gsoapProxy2_3)->FastestAxisCount;
}

uint64_t Grid2dRepresentation::getNodeCountAlongJAxis() const
{
	return static_cast<_resqml22__Grid2dRepresentation*>(gsoapProxy2_3)->SlowestAxisCount;
}

void Grid2dRepresentation::getZValues(double* values) const
{
	_resqml22__Grid2dRepresentation* rep = static_cast<_resqml22__Grid2dRepresentation*>(gsoapProxy2_3);

	if (rep->Geometry->Points->soap_type() == SOAP_TYPE_gsoap_eml2_3_resqml22__Point3dZValueArray) {
		eml23__AbstractFloatingPointArray* zValues = static_cast<resqml22__Point3dZValueArray*>(rep->Geometry->Points)->ZValues;
		if (dynamic_cast<eml23__FloatingPointExternalArray*>(zValues) != nullptr) {
			eml23__ExternalDataArrayPart const* daPart = static_cast<eml23__FloatingPointExternalArray*>(zValues)->Values->ExternalDataArrayPart[0];
			EML2_NS::AbstractHdfProxy* hdfProxy = getOrCreateHdfProxyFromDataArrayPart(daPart);
			hdfProxy->readArrayNdOfDoubleValues(daPart->PathInExternalFile, values);
		}
		else {
			throw std::logic_error("The Z values can only be retrieved if they are described as a FloatingPointExternalArray.");
		}
	}
	else if (rep->Geometry->Points->soap_type() == SOAP_TYPE_gsoap_eml2_3_resqml22__Point3dLatticeArray) {
		const double zOrigin = getZOrigin();
		double zIOffset = getZIOffset();
		double zJOffset = getZJOffset();

		if (isISpacingConstant() && isJSpacingConstant()) {
			const uint64_t iNodeCount = getNodeCountAlongIAxis();
			const uint64_t jNodeCount = getNodeCountAlongJAxis();
			for (size_t jNode = 0; jNode < jNodeCount; ++jNode) {
				for (size_t iNode = 0; iNode < iNodeCount; ++iNode) {
					values[iNode + jNode*iNodeCount] = zOrigin + zIOffset*iNode + zJOffset*jNode;
				}
			}
		}
		else {
			const uint64_t iNodeCount = getNodeCountAlongIAxis();
			const uint64_t jNodeCount = getNodeCountAlongJAxis();
			std::unique_ptr<double[]> iSpacings(new double[iNodeCount]); /// the size should rigourously be iNodeCount - 1. For optimization reason, we just have one extra item to avoid a range error in the later for loop where the last item is accessed but not used anyhow.
			getISpacing(iSpacings.get());
			std::unique_ptr<double[]> jSpacings(new double[jNodeCount]); /// the size should rigourously be jNodeCount - 1. For optimization reason, we just have one extra item to avoid a range error in the later for loop where the last item is accessed but not used anyhow.
			getJSpacing(jSpacings.get());

			// I Offset unit vector
			const double xIOffset = getXIOffset();
			const double yIOffset = getYIOffset();
			const double iOffsetMagnitude = sqrt(xIOffset*xIOffset + yIOffset*yIOffset + zIOffset*zIOffset);
			zIOffset /= iOffsetMagnitude;

			// J Offset unit vector
			const double xJOffset = getXJOffset();
			const double yJOffset = getYJOffset();
			const double jOffsetMagnitude = sqrt(xJOffset*xJOffset + yJOffset*yJOffset + zJOffset*zJOffset);
			zJOffset /= jOffsetMagnitude;

			double jSpacing = 0;
			for (size_t jNode = 0; jNode < jNodeCount; ++jNode) {
				double iSpacing = 0;
				for (size_t iNode = 0; iNode < iNodeCount; ++iNode) {
					values[iNode + jNode*iNodeCount] = zOrigin + zIOffset*iSpacing + zJOffset*jSpacing;
					iSpacing += iSpacings[iNode];
				}
				jSpacing += jSpacings[jNode];
			}
		}
	}
	else {
		throw std::logic_error("The Z values can only be retrieved for a Point3dZValueArray or a Point3dLatticeArray geometry.");
	}
}

resqml22__Point3dLatticeArray* Grid2dRepresentation::getArrayLatticeOfPoints3d() const
{
	_resqml22__Grid2dRepresentation* grid = static_cast<_resqml22__Grid2dRepresentation*>(gsoapProxy2_3);
	if (grid->Geometry->Points->soap_type() == SOAP_TYPE_gsoap_eml2_3_resqml22__Point3dLatticeArray) {
		return static_cast<resqml22__Point3dLatticeArray*>(grid->Geometry->Points);
	}
	
	if (grid->Geometry->Points->soap_type() == SOAP_TYPE_gsoap_eml2_3_resqml22__Point3dZValueArray) {
		resqml22__Point3dZValueArray* arrayOfZValuePoints3d = static_cast<resqml22__Point3dZValueArray*>(grid->Geometry->Points);
		if (arrayOfZValuePoints3d->SupportingGeometry->soap_type() == SOAP_TYPE_gsoap_eml2_3_resqml22__Point3dLatticeArray) {
			return static_cast<resqml22__Point3dLatticeArray*>(arrayOfZValuePoints3d->SupportingGeometry);
		}
	}

	return nullptr;
}

double Grid2dRepresentation::getXOrigin() const
{
	resqml22__Point3dLatticeArray* arrayLatticeOfPoints3d = getArrayLatticeOfPoints3d();

	if (arrayLatticeOfPoints3d != nullptr) {
		return arrayLatticeOfPoints3d->Origin->Coordinate1;
	}

	if (!getSupportingRepresentationDor().isEmpty()) {
		const uint64_t iOrigin = getIndexOriginOnSupportingRepresentation(1); // I is fastest
		const uint64_t jOrigin = getIndexOriginOnSupportingRepresentation(0); // J is slowest

		RESQML2_NS::Grid2dRepresentation const * supportingRepresentation = getSupportingRepresentation();
		return iOrigin == 0 && jOrigin == 0 ? supportingRepresentation->getXOrigin() :
			supportingRepresentation->getXOrigin() + iOrigin*supportingRepresentation->getXIOffset() + jOrigin*supportingRepresentation->getXJOffset();

	}

	return std::numeric_limits<double>::signaling_NaN();
}

double Grid2dRepresentation::getYOrigin() const
{
	resqml22__Point3dLatticeArray* arrayLatticeOfPoints3d = getArrayLatticeOfPoints3d();

	if (arrayLatticeOfPoints3d != nullptr) {
		return arrayLatticeOfPoints3d->Origin->Coordinate2;
	}
	
	if (!getSupportingRepresentationDor().isEmpty()) {
		const uint64_t iOrigin = getIndexOriginOnSupportingRepresentation(1); // I is fastest
		const uint64_t jOrigin = getIndexOriginOnSupportingRepresentation(0); // J is slowest

		RESQML2_NS::Grid2dRepresentation const * supportingRepresentation = getSupportingRepresentation();
		return iOrigin == 0 && jOrigin == 0 ? supportingRepresentation->getYOrigin() :
			supportingRepresentation->getYOrigin() + iOrigin*supportingRepresentation->getYIOffset() + jOrigin*supportingRepresentation->getYJOffset();
	}

	return std::numeric_limits<double>::signaling_NaN();
}

double Grid2dRepresentation::getZOrigin() const
{
	resqml22__Point3dLatticeArray* arrayLatticeOfPoints3d = getArrayLatticeOfPoints3d();

	if (arrayLatticeOfPoints3d != nullptr) {
		return arrayLatticeOfPoints3d->Origin->Coordinate3;
	}
	
	if (!getSupportingRepresentationDor().isEmpty()) {
		const uint64_t iOrigin = getIndexOriginOnSupportingRepresentation(1); // I is fastest
		const uint64_t jOrigin = getIndexOriginOnSupportingRepresentation(0); // J is slowest

		RESQML2_NS::Grid2dRepresentation const * supportingRepresentation = getSupportingRepresentation();
		return iOrigin == 0 && jOrigin == 0 ? supportingRepresentation->getZOrigin() :
			supportingRepresentation->getZOrigin() + iOrigin*supportingRepresentation->getZIOffset() + jOrigin*supportingRepresentation->getZJOffset();
	}
	
	return std::numeric_limits<double>::signaling_NaN();
}

double Grid2dRepresentation::getXJOffset() const
{
	resqml22__Point3dLatticeArray* arrayLatticeOfPoints3d = getArrayLatticeOfPoints3d();

	if (arrayLatticeOfPoints3d != nullptr) {
		resqml22__Point3d * offset = arrayLatticeOfPoints3d->Dimension[0]->Direction;
		return isJSpacingConstant() ?
			offset->Coordinate1 * getJSpacing() /
			sqrt(offset->Coordinate1 * offset->Coordinate1 + offset->Coordinate2 * offset->Coordinate2) :
			offset->Coordinate1;
	}
	
	if (!getSupportingRepresentationDor().isEmpty()) {
		return getSupportingRepresentation()->getXJOffset() * getIndexOffsetOnSupportingRepresentation(0);
	}

	throw logic_error("No lattice array have been found for this 2d grid.");
}

double Grid2dRepresentation::getYJOffset() const
{
	resqml22__Point3dLatticeArray* arrayLatticeOfPoints3d = getArrayLatticeOfPoints3d();

	if (arrayLatticeOfPoints3d != nullptr) {
		resqml22__Point3d * offset = arrayLatticeOfPoints3d->Dimension[0]->Direction;
		return isJSpacingConstant() ?
			offset->Coordinate2 * getJSpacing() /
			sqrt(offset->Coordinate1 * offset->Coordinate1 + offset->Coordinate2 * offset->Coordinate2) :
			offset->Coordinate2;
	}
	
	if (!getSupportingRepresentationDor().isEmpty()) {
		return getSupportingRepresentation()->getYJOffset() * getIndexOffsetOnSupportingRepresentation(0);
	}

	throw logic_error("No lattice array have been found for this 2d grid.");
}

double Grid2dRepresentation::getZJOffset() const
{
	resqml22__Point3dLatticeArray* arrayLatticeOfPoints3d = getArrayLatticeOfPoints3d();

	if (arrayLatticeOfPoints3d != nullptr) {
		resqml22__Point3d * offset = arrayLatticeOfPoints3d->Dimension[0]->Direction;
		return isJSpacingConstant() ?
			offset->Coordinate3 * getJSpacing() /
			sqrt(offset->Coordinate1 * offset->Coordinate1 + offset->Coordinate2 * offset->Coordinate2) :
			offset->Coordinate3;
	}
	
	if (!getSupportingRepresentationDor().isEmpty()) {
		return getSupportingRepresentation()->getZJOffset() * getIndexOffsetOnSupportingRepresentation(0);
	}

	throw logic_error("No lattice array have been found for this 2d grid.");
}

double Grid2dRepresentation::getXIOffset() const
{
	resqml22__Point3dLatticeArray* arrayLatticeOfPoints3d = getArrayLatticeOfPoints3d();

	if (arrayLatticeOfPoints3d != nullptr) {
		resqml22__Point3d * offset = arrayLatticeOfPoints3d->Dimension[1]->Direction;
		return isISpacingConstant() ? 
			offset->Coordinate1 * getISpacing() /
			sqrt(offset->Coordinate1 * offset->Coordinate1 + offset->Coordinate2 * offset->Coordinate2) :
			offset->Coordinate1;
	}
	
	if (!getSupportingRepresentationDor().isEmpty()) {
		return getSupportingRepresentation()->getXIOffset() * getIndexOffsetOnSupportingRepresentation(1);
	}

	throw logic_error("No lattice array have been found for this 2d grid.");
}

double Grid2dRepresentation::getYIOffset() const
{
	resqml22__Point3dLatticeArray* arrayLatticeOfPoints3d = getArrayLatticeOfPoints3d();

	if (arrayLatticeOfPoints3d != nullptr) {
		resqml22__Point3d * offset = arrayLatticeOfPoints3d->Dimension[1]->Direction;
		return isISpacingConstant() ?
			offset->Coordinate2 * getISpacing() /
			sqrt(offset->Coordinate1 * offset->Coordinate1 + offset->Coordinate2 * offset->Coordinate2) :
			offset->Coordinate2;
	}
	
	if (!getSupportingRepresentationDor().isEmpty()) {
		return getSupportingRepresentation()->getYIOffset() * getIndexOffsetOnSupportingRepresentation(1);
	}

	throw logic_error("No lattice array have been found for this 2d grid.");
}

double Grid2dRepresentation::getZIOffset() const
{
	resqml22__Point3dLatticeArray* arrayLatticeOfPoints3d = getArrayLatticeOfPoints3d();

	if (arrayLatticeOfPoints3d != nullptr) {
		resqml22__Point3d * offset = arrayLatticeOfPoints3d->Dimension[1]->Direction;
		return isISpacingConstant() ?
			offset->Coordinate3 * getISpacing() /
			sqrt(offset->Coordinate1 * offset->Coordinate1 + offset->Coordinate2 * offset->Coordinate2) :
			offset->Coordinate3;
	}

	if (!getSupportingRepresentationDor().isEmpty()) {
		return getSupportingRepresentation()->getYIOffset() * getIndexOffsetOnSupportingRepresentation(1);
	}

	throw logic_error("No lattice array have been found for this 2d grid.");
}

bool Grid2dRepresentation::isJSpacingConstant() const
{
	const resqml22__Point3dLatticeArray* const arrayLatticeOfPoints3d = getArrayLatticeOfPoints3d();

	if (arrayLatticeOfPoints3d != nullptr) {
		if (!arrayLatticeOfPoints3d->Dimension.empty()) {
			return arrayLatticeOfPoints3d->Dimension[0]->Spacing->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__FloatingPointConstantArray;
		}

		throw logic_error("This 2d grid representation does not look to have dimensions.");
	}
	else if (!getSupportingRepresentationDor().isEmpty()) {
		return getSupportingRepresentation()->isJSpacingConstant();
	}

	throw logic_error("This 2D grid representation looks not valid : no lattice geometry and non supporting grid 2D representation.");
}

bool Grid2dRepresentation::isISpacingConstant() const
{
	const resqml22__Point3dLatticeArray* const arrayLatticeOfPoints3d = getArrayLatticeOfPoints3d();

	if (arrayLatticeOfPoints3d != nullptr) {
		if (arrayLatticeOfPoints3d->Dimension.size() > 1) {
			return arrayLatticeOfPoints3d->Dimension[1]->Spacing->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__FloatingPointConstantArray;
		}
		
		throw invalid_argument("This 2d grid representation does not look to have (at least) 2 dimensions.");
	}
	else if (!getSupportingRepresentationDor().isEmpty()) {
		return getSupportingRepresentation()->isISpacingConstant();
	}

	throw logic_error("This 2D grid representation looks not valid : no lattice geometry and non supporting grid 2D representation.");
}

double Grid2dRepresentation::getJSpacing() const
{
	if (!isJSpacingConstant()) {
		throw logic_error("The J spacing of this 2d grid does not look to be constant.");
	}

	const resqml22__Point3dLatticeArray* const arrayLatticeOfPoints3d = getArrayLatticeOfPoints3d();

	if (arrayLatticeOfPoints3d != nullptr) {
		return static_cast<eml23__FloatingPointConstantArray*>(arrayLatticeOfPoints3d->Dimension[0]->Spacing)->Value;
	}

	const uint64_t jIndexOffset = getIndexOffsetOnSupportingRepresentation(0);
	const double jSpacingOnSupportingRep = getSupportingRepresentation()->getJSpacing();

	return jIndexOffset * jSpacingOnSupportingRep;
}

void Grid2dRepresentation::getJSpacing(double* const jSpacings) const
{
	const resqml22__Point3dLatticeArray* const arrayLatticeOfPoints3d = getArrayLatticeOfPoints3d();

	const uint64_t jSpacingCount = getNodeCountAlongJAxis() - 1;

	if (arrayLatticeOfPoints3d != nullptr) {
		if (arrayLatticeOfPoints3d->Dimension[0]->Spacing->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__FloatingPointConstantArray) {
			const double constantSpacing = static_cast<eml23__FloatingPointConstantArray*>(arrayLatticeOfPoints3d->Dimension[0]->Spacing)->Value;
			for (uint64_t j = 0; j < jSpacingCount; ++j) {
				jSpacings[j] = constantSpacing;
			}
		}
		else if (dynamic_cast<eml23__FloatingPointExternalArray*>(arrayLatticeOfPoints3d->Dimension[0]->Spacing) != nullptr) {
			eml23__ExternalDataArrayPart const* daPart = static_cast<eml23__FloatingPointExternalArray*>(arrayLatticeOfPoints3d->Dimension[0]->Spacing)->Values->ExternalDataArrayPart[0];
			EML2_NS::AbstractHdfProxy * hdfProxy = getOrCreateHdfProxyFromDataArrayPart(daPart);
			if (hdfProxy == nullptr) {
				throw logic_error("The HDF proxy is missing.");
			}
			hdfProxy->readArrayNdOfDoubleValues(daPart->PathInExternalFile, jSpacings);
		}
		else {
			throw logic_error("Not implemented yet.");
		}
	}
	else if (!getSupportingRepresentationDor().isEmpty())
	{
		const uint64_t jIndexOrigin = getIndexOriginOnSupportingRepresentation(0);
		const uint64_t jIndexOffset = getIndexOffsetOnSupportingRepresentation(0);
		std::unique_ptr<double[]> jSpacingsOnSupportingRep(new double[jSpacingCount]);
		getSupportingRepresentation()->getJSpacing(jSpacingsOnSupportingRep.get());
		
		for (uint64_t j = 0; j < jSpacingCount; ++j) {
			jSpacings[j] = .0;
			if (jIndexOffset > 0) {
				for (int tmp = 0; tmp < jIndexOffset; ++tmp) {
					jSpacings[j] += jSpacingsOnSupportingRep[jIndexOrigin + j * jIndexOffset + tmp];
				}
			}
			else if (jIndexOffset < 0) {
				for (int tmp = 0; tmp > jIndexOffset; --tmp) {
					jSpacings[j] += jSpacingsOnSupportingRep[jIndexOrigin - 1 + j * jIndexOffset + tmp];
				}
			}
			else {
				throw logic_error("The index offset on supporting representation cannot be 0.");
			}
		}
	}
	else
		throw logic_error("This 2D grid representation looks not valid : no lattice geometry and non supporting grid 2D representation.");
}

double Grid2dRepresentation::getISpacing() const
{
	if (!isISpacingConstant()) {
		throw invalid_argument("The I spacing of this 2d grid does not look to be constant.");
	}

	const resqml22__Point3dLatticeArray* const arrayLatticeOfPoints3d = getArrayLatticeOfPoints3d();

	if (arrayLatticeOfPoints3d != nullptr) {
		return static_cast<eml23__FloatingPointConstantArray*>(arrayLatticeOfPoints3d->Dimension[1]->Spacing)->Value;
	}

	const uint64_t iIndexOffset = getIndexOffsetOnSupportingRepresentation(1);
	const double iSpacingOnSupportingRep = getSupportingRepresentation()->getISpacing();

	return iIndexOffset * iSpacingOnSupportingRep;
}

void Grid2dRepresentation::getISpacing(double* iSpacings) const
{
	const resqml22__Point3dLatticeArray* const arrayLatticeOfPoints3d = getArrayLatticeOfPoints3d();

	const uint64_t iSpacingCount = getNodeCountAlongIAxis() - 1;

	if (arrayLatticeOfPoints3d != nullptr) {
		if (arrayLatticeOfPoints3d->Dimension[1]->Spacing->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__FloatingPointConstantArray) {
			const double constantSpacing = static_cast<eml23__FloatingPointConstantArray*>(arrayLatticeOfPoints3d->Dimension[1]->Spacing)->Value;
			for (uint64_t i = 0; i < iSpacingCount; ++i) {
				iSpacings[i] = constantSpacing;
			}
		}
		else if (dynamic_cast<eml23__FloatingPointExternalArray*>(arrayLatticeOfPoints3d->Dimension[1]->Spacing) != nullptr) {
			eml23__ExternalDataArrayPart const* daPart = static_cast<eml23__FloatingPointExternalArray*>(arrayLatticeOfPoints3d->Dimension[1]->Spacing)->Values->ExternalDataArrayPart[0];
			EML2_NS::AbstractHdfProxy * hdfProxy = getOrCreateHdfProxyFromDataArrayPart(daPart);
			if (hdfProxy == nullptr) {
				throw invalid_argument("The HDF proxy is missing.");
			}
			hdfProxy->readArrayNdOfDoubleValues(daPart->PathInExternalFile, iSpacings);
		}
		else {
			throw logic_error("Not implemented yet.");
		}
	}
	else if (!getSupportingRepresentationDor().isEmpty())
	{
		const uint64_t iIndexOrigin = getIndexOriginOnSupportingRepresentation(1);
		const uint64_t iIndexOffset = getIndexOffsetOnSupportingRepresentation(1);
		std::unique_ptr<double[]> iSpacingsOnSupportingRep(new double[iSpacingCount]);
		getSupportingRepresentation()->getISpacing(iSpacingsOnSupportingRep.get());

		for (uint64_t i = 0; i < iSpacingCount; ++i) {
			iSpacings[i] = .0;
			if (iIndexOffset > 0) {
				for (int tmp = 0; tmp < iIndexOffset; ++tmp) {
					iSpacings[i] += iSpacingsOnSupportingRep[iIndexOrigin + i * iIndexOffset + tmp];
				}
			}
			else if (iIndexOffset < 0) {
				for (int tmp = 0; tmp > iIndexOffset; --tmp) {
					iSpacings[i] += iSpacingsOnSupportingRep[iIndexOrigin - 1 + i * iIndexOffset + tmp];
				}
			}
			else {
				throw invalid_argument("The index offset on supporting representation cannot be 0.");
			}
		}
	}
	else
		throw logic_error("This 2D grid representation looks not valid : no lattice geometry and non supporting grid 2D representation.");
}

void Grid2dRepresentation::setGeometryAsArray2dOfLatticePoints3d(
	unsigned int numPointsInFastestDirection, unsigned int numPointsInSlowestDirection,
	double xOrigin, double yOrigin, double zOrigin,
	double xOffsetInFastestDirection, double yOffsetInFastestDirection, double zOffsetInFastestDirection,
	double xOffsetInSlowestDirection, double yOffsetInSlowestDirection, double zOffsetInSlowestDirection,
	double spacingInFastestDirection, double spacingInSlowestDirection, EML2_NS::AbstractLocal3dCrs * localCrs)
{
	// The below check exists because Count of spacing must be > 0 in the standard which occurs inly if we have at least two nodes per direction.
	if (numPointsInFastestDirection < 2 || numPointsInSlowestDirection < 2) {
		throw std::invalid_argument("You cannot set a lattice with less than two nodes in a direction.");
	}
	if (localCrs == nullptr) {
		localCrs = getRepository()->getDefaultCrs();
		if (localCrs == nullptr) {
			throw std::invalid_argument("A (default) CRS must be provided.");
		}
	}

	static_cast<_resqml22__Grid2dRepresentation*>(gsoapProxy2_3)->SlowestAxisCount = numPointsInSlowestDirection;
	static_cast<_resqml22__Grid2dRepresentation*>(gsoapProxy2_3)->FastestAxisCount = numPointsInFastestDirection;
	static_cast<_resqml22__Grid2dRepresentation*>(gsoapProxy2_3)->Geometry = createArray2dOfLatticePoints3d(numPointsInFastestDirection, numPointsInSlowestDirection,
		xOrigin, yOrigin, zOrigin,
		xOffsetInFastestDirection, yOffsetInFastestDirection, zOffsetInFastestDirection,
		xOffsetInSlowestDirection, yOffsetInSlowestDirection, zOffsetInSlowestDirection,
		spacingInFastestDirection, spacingInSlowestDirection, localCrs);

	getRepository()->addRelationship(this, localCrs);
}

void Grid2dRepresentation::setGeometryAsArray2dOfExplicitZ(
	double * zValues,
	unsigned int numI, unsigned int numJ, EML2_NS::AbstractHdfProxy * proxy,
	RESQML2_NS::Grid2dRepresentation * supportingGrid2dRepresentation, EML2_NS::AbstractLocal3dCrs * localCrs,
	unsigned int startIndexI, unsigned int startIndexJ,
	int indexIncrementI, int indexIncrementJ)
{
	if (localCrs == nullptr) {
		localCrs = getRepository()->getDefaultCrs();
		if (localCrs == nullptr) {
			throw std::invalid_argument("A (default) CRS must be provided.");
		}
	}

	static_cast<_resqml22__Grid2dRepresentation*>(gsoapProxy2_3)->SlowestAxisCount = numJ;
	static_cast<_resqml22__Grid2dRepresentation*>(gsoapProxy2_3)->FastestAxisCount = numI;
	static_cast<_resqml22__Grid2dRepresentation*>(gsoapProxy2_3)->Geometry = createArray2dOfExplicitZ(0,
		zValues, localCrs,
		numI, numJ, proxy,
		supportingGrid2dRepresentation,
		startIndexI + startIndexJ * getNodeCountAlongIAxis(),
		indexIncrementI, indexIncrementJ);

	getRepository()->addRelationship(this, localCrs);
}

void Grid2dRepresentation::setGeometryAsArray2dOfExplicitZ(
	double * zValues,
	unsigned int numI, unsigned int numJ, EML2_NS::AbstractHdfProxy * proxy,
	double originX, double originY, double originZ,
	double offsetIX, double offsetIY, double offsetIZ, double spacingI,
	double offsetJX, double offsetJY, double offsetJZ, double spacingJ, EML2_NS::AbstractLocal3dCrs * localCrs)
{
	if (localCrs == nullptr) {
		localCrs = getRepository()->getDefaultCrs();
		if (localCrs == nullptr) {
			throw std::invalid_argument("A (default) CRS must be provided.");
		}
	}

	static_cast<_resqml22__Grid2dRepresentation*>(gsoapProxy2_3)->SlowestAxisCount = numJ;
	static_cast<_resqml22__Grid2dRepresentation*>(gsoapProxy2_3)->FastestAxisCount = numI;
	static_cast<_resqml22__Grid2dRepresentation*>(gsoapProxy2_3)->Geometry = createArray2dOfExplicitZ(0,
		zValues, localCrs,
		numI, numJ, proxy,
		originX, originY, originZ,
		offsetIX, offsetIY, offsetIZ, spacingI,
		offsetJX, offsetJY, offsetJZ, spacingJ);

	getRepository()->addRelationship(this, localCrs);
}

COMMON_NS::DataObjectReference Grid2dRepresentation::getSupportingRepresentationDor() const
{
	_resqml22__Grid2dRepresentation* singleGrid2dRep = static_cast<_resqml22__Grid2dRepresentation*>(gsoapProxy2_3);
	if (singleGrid2dRep != nullptr && singleGrid2dRep->Geometry->Points->soap_type() == SOAP_TYPE_gsoap_eml2_3_resqml22__Point3dZValueArray) {
		resqml22__Point3dZValueArray* tmp = static_cast<resqml22__Point3dZValueArray*>(singleGrid2dRep->Geometry->Points);
		if (tmp->SupportingGeometry->soap_type() == SOAP_TYPE_gsoap_eml2_3_resqml22__Point3dFromRepresentationLatticeArray) {
			return COMMON_NS::DataObjectReference(static_cast<resqml22__Point3dFromRepresentationLatticeArray*>(tmp->SupportingGeometry)->SupportingRepresentation);
		}
	}

	return COMMON_NS::DataObjectReference();
}

uint64_t Grid2dRepresentation::getIndexOriginOnSupportingRepresentation() const
{
	resqml22__Point3dFromRepresentationLatticeArray* geom = getPoint3dFromRepresentationLatticeArrayFromPointGeometryPatch(static_cast<_resqml22__Grid2dRepresentation*>(gsoapProxy2_3)->Geometry);

	if (geom != nullptr) {
		return geom->NodeIndicesOnSupportingRepresentation->StartValue;
	}

	throw logic_error("It does not exist supporting representation for this representation.");
}

uint64_t Grid2dRepresentation::getIndexOriginOnSupportingRepresentation(unsigned int dimension) const
{
	resqml22__Point3dFromRepresentationLatticeArray* geom = getPoint3dFromRepresentationLatticeArrayFromPointGeometryPatch(static_cast<_resqml22__Grid2dRepresentation*>(gsoapProxy2_3)->Geometry);

	if (geom != nullptr)
	{
		if (dimension == 0) // J dimension : slowest
			return geom->NodeIndicesOnSupportingRepresentation->StartValue / getSupportingRepresentation()->getNodeCountAlongIAxis();
		else if (dimension == 1) // I dimension : fastest
			return geom->NodeIndicesOnSupportingRepresentation->StartValue % getSupportingRepresentation()->getNodeCountAlongIAxis();
		throw invalid_argument("There cannot be more than 2 dimensions for a grid 2d representation.");
	}

	throw logic_error("It does not exist supporting representation for this representation.");
}

uint64_t Grid2dRepresentation::getNodeCountOnSupportingRepresentation(unsigned int dimension) const
{
	resqml22__Point3dFromRepresentationLatticeArray* geom = getPoint3dFromRepresentationLatticeArrayFromPointGeometryPatch(static_cast<_resqml22__Grid2dRepresentation*>(gsoapProxy2_3)->Geometry);

	if (geom != nullptr) {
		if (dimension < geom->NodeIndicesOnSupportingRepresentation->Offset.size()) {
			return geom->NodeIndicesOnSupportingRepresentation->Offset[dimension]->Count + 1;
		}
		else {
			throw out_of_range("dimension is out of range.");
		}

	}
	
	throw invalid_argument("It does not exist supporting representation for this representation.");
}

uint64_t Grid2dRepresentation::getIndexOffsetOnSupportingRepresentation(unsigned int dimension) const
{
	resqml22__Point3dFromRepresentationLatticeArray* geom = getPoint3dFromRepresentationLatticeArrayFromPointGeometryPatch(static_cast<_resqml22__Grid2dRepresentation*>(gsoapProxy2_3)->Geometry);

	if (geom != nullptr) {
		if (dimension < geom->NodeIndicesOnSupportingRepresentation->Offset.size()) {
			return geom->NodeIndicesOnSupportingRepresentation->Offset[dimension]->Value;
		}
		else {
			throw out_of_range("dimension is out of range.");
		}
	}

	throw invalid_argument("It does not exist supporting representation for this representation.");
}

resqml22__Point3dFromRepresentationLatticeArray* Grid2dRepresentation::getPoint3dFromRepresentationLatticeArrayFromPointGeometryPatch(resqml22__PointGeometry* patch) const
{
	if (patch != nullptr) {
		resqml22__Point3dFromRepresentationLatticeArray* patchOfSupportingRep = nullptr;

		if (patch->Points->soap_type() == SOAP_TYPE_gsoap_eml2_3_resqml22__Point3dZValueArray) {
			resqml22__Point3dZValueArray* zValuesPatch = static_cast<resqml22__Point3dZValueArray*>(patch->Points);
			if (zValuesPatch->SupportingGeometry->soap_type() == SOAP_TYPE_gsoap_eml2_3_resqml22__Point3dFromRepresentationLatticeArray) {
				patchOfSupportingRep = static_cast<resqml22__Point3dFromRepresentationLatticeArray*>(zValuesPatch->SupportingGeometry);
			}
		}
		else if (patch->Points->soap_type() == SOAP_TYPE_gsoap_eml2_3_resqml22__Point3dFromRepresentationLatticeArray) {
			patchOfSupportingRep = static_cast<resqml22__Point3dFromRepresentationLatticeArray*>(patch->Points);
		}

		return patchOfSupportingRep;
	}

	return nullptr;
}

resqml22__PointGeometry* Grid2dRepresentation::createArray2dOfLatticePoints3d(
	unsigned int numPointsInFastestDirection, unsigned int numPointsInSlowestDirection,
	double xOrigin, double yOrigin, double zOrigin,
	double xOffsetInFastestDirection, double yOffsetInFastestDirection, double zOffsetInFastestDirection,
	double xOffsetInSlowestDirection, double yOffsetInSlowestDirection, double zOffsetInSlowestDirection,
	double spacingInFastestDirection, double spacingInSlowestDirection, EML2_NS::AbstractLocal3dCrs * localCrs)
{
	if (localCrs == nullptr) {
		throw invalid_argument("The CRS cannot be the null pointer");
	}

	resqml22__PointGeometry* geom = soap_new_resqml22__PointGeometry(gsoapProxy2_3->soap);
	geom->LocalCrs = localCrs->newEml23Reference();

	// XML
	resqml22__Point3dLatticeArray* xmlPoints = soap_new_resqml22__Point3dLatticeArray(gsoapProxy2_3->soap);
	xmlPoints->Origin = soap_new_resqml22__Point3d(gsoapProxy2_3->soap);
	xmlPoints->Origin->Coordinate1 = xOrigin;
	xmlPoints->Origin->Coordinate2 = yOrigin;
	xmlPoints->Origin->Coordinate3 = zOrigin;

	// first (slowest) dim : fastest is I (or inline), slowest is J (or crossline)
	resqml22__Point3dLatticeDimension* latticeDim = soap_new_resqml22__Point3dLatticeDimension(gsoapProxy2_3->soap);
	latticeDim->Direction = soap_new_resqml22__Point3d(gsoapProxy2_3->soap);
	latticeDim->Direction->Coordinate1 = xOffsetInSlowestDirection;
	latticeDim->Direction->Coordinate2 = yOffsetInSlowestDirection;
	latticeDim->Direction->Coordinate3 = zOffsetInSlowestDirection;
	eml23__FloatingPointConstantArray* spacingInfo = soap_new_eml23__FloatingPointConstantArray(gsoapProxy2_3->soap);
	spacingInfo->Count = numPointsInSlowestDirection - 1;
	spacingInfo->Value = spacingInSlowestDirection;
	latticeDim->Spacing = spacingInfo;
	xmlPoints->Dimension.push_back(latticeDim);

	// Second (fastest) dimension :fastest is I (or inline), slowest is J (or crossline)
	latticeDim = soap_new_resqml22__Point3dLatticeDimension(gsoapProxy2_3->soap);
	latticeDim->Direction = soap_new_resqml22__Point3d(gsoapProxy2_3->soap);
	latticeDim->Direction->Coordinate1 = xOffsetInFastestDirection;
	latticeDim->Direction->Coordinate2 = yOffsetInFastestDirection;
	latticeDim->Direction->Coordinate3 = zOffsetInFastestDirection;
	spacingInfo = soap_new_eml23__FloatingPointConstantArray(gsoapProxy2_3->soap);
	spacingInfo->Count = numPointsInFastestDirection - 1;
	spacingInfo->Value = spacingInFastestDirection;
	latticeDim->Spacing = spacingInfo;
	xmlPoints->Dimension.push_back(latticeDim);

	geom->Points = xmlPoints;

	return geom;
}

resqml22__PointGeometry* Grid2dRepresentation::createArray2dOfExplicitZ(
	unsigned int patchIndex, double * zValues, EML2_NS::AbstractLocal3dCrs * localCrs,
	unsigned int numI, unsigned int numJ, EML2_NS::AbstractHdfProxy * proxy,
	RESQML2_NS::Grid2dRepresentation * supportingRepresentation,
	uint64_t startGlobalIndex,
	int indexIncrementI, int indexIncrementJ)
{
	if (localCrs == nullptr) {
		localCrs = getRepository()->getDefaultCrs();
		if (localCrs == nullptr) {
			throw std::invalid_argument("A (default) CRS must be provided.");
		}
	}
	if (proxy == nullptr) {
		proxy = getRepository()->getDefaultHdfProxy();
		if (proxy == nullptr) {
			throw std::invalid_argument("A (default) HDF Proxy must be provided.");
		}
	}
	getRepository()->addRelationship(this, proxy);

	getRepository()->addRelationship(this, supportingRepresentation);

	resqml22__PointGeometry* geom = soap_new_resqml22__PointGeometry(gsoapProxy2_3->soap);
	geom->LocalCrs = localCrs->newEml23Reference();

	// XML
	resqml22__Point3dZValueArray* xmlPoints = soap_new_resqml22__Point3dZValueArray(gsoapProxy2_3->soap);
	resqml22__Point3dFromRepresentationLatticeArray* patchPoints = soap_new_resqml22__Point3dFromRepresentationLatticeArray(gsoapProxy2_3->soap);
	patchPoints->SupportingRepresentation = supportingRepresentation->newEml23Reference();
	patchPoints->NodeIndicesOnSupportingRepresentation = soap_new_eml23__IntegerLatticeArray(gsoapProxy2_3->soap);
	patchPoints->NodeIndicesOnSupportingRepresentation->StartValue = startGlobalIndex;
	xmlPoints->SupportingGeometry = patchPoints;

	// first (slowest) dim :fastest is I (or inline), slowest is J (or crossline)
	eml23__IntegerConstantArray* offset = soap_new_eml23__IntegerConstantArray(gsoapProxy2_3->soap);
	offset->Count = numJ - 1;
	offset->Value = indexIncrementJ;
	patchPoints->NodeIndicesOnSupportingRepresentation->Offset.push_back(offset);

	//second (fastest) dim :fastest is I (or inline), slowest is J (or crossline)
	offset = soap_new_eml23__IntegerConstantArray(gsoapProxy2_3->soap);
	offset->Count = numI - 1;
	offset->Value = indexIncrementI;
	patchPoints->NodeIndicesOnSupportingRepresentation->Offset.push_back(offset);

	// Z Values
	eml23__FloatingPointExternalArray* xmlZValues = soap_new_eml23__FloatingPointExternalArray(gsoapProxy2_3->soap);
	xmlZValues->Values = soap_new_eml23__ExternalDataArray(gsoapProxy2_3->soap);
	xmlZValues->Values->ExternalDataArrayPart.push_back(createExternalDataArrayPart(getHdfGroup() +"/points_patch" + std::to_string(patchIndex), numJ*numI, proxy));
	xmlPoints->ZValues = xmlZValues;

	// HDF
	hsize_t dim[2] = { numJ, numI };
	proxy->writeArrayNdOfDoubleValues(getHdfGroup(),
		"points_patch" + std::to_string(patchIndex),
		zValues,
		dim, 2);

	geom->Points = xmlPoints;

	return geom;
}

resqml22__PointGeometry* Grid2dRepresentation::createArray2dOfExplicitZ(
	unsigned int patchIndex, double * zValues, EML2_NS::AbstractLocal3dCrs * localCrs,
	unsigned int numI, unsigned int numJ, EML2_NS::AbstractHdfProxy * proxy,
	double originX, double originY, double originZ,
	double offsetIX, double offsetIY, double offsetIZ, double spacingI,
	double offsetJX, double offsetJY, double offsetJZ, double spacingJ)
{
	if (localCrs == nullptr) {
		localCrs = getRepository()->getDefaultCrs();
		if (localCrs == nullptr) {
			throw std::invalid_argument("A (default) CRS must be provided.");
		}
	}
	if (proxy == nullptr) {
		proxy = getRepository()->getDefaultHdfProxy();
		if (proxy == nullptr) {
			throw std::invalid_argument("A (default) HDF Proxy must be provided.");
		}
	}
	getRepository()->addRelationship(this, proxy);

	resqml22__PointGeometry* geom = soap_new_resqml22__PointGeometry(gsoapProxy2_3->soap);
	geom->LocalCrs = localCrs->newEml23Reference();

	// XML
	resqml22__Point3dZValueArray* xmlPoints = soap_new_resqml22__Point3dZValueArray(gsoapProxy2_3->soap);
	resqml22__Point3dLatticeArray* latticePoints = soap_new_resqml22__Point3dLatticeArray(gsoapProxy2_3->soap);
	latticePoints->Origin = soap_new_resqml22__Point3d(gsoapProxy2_3->soap);
	latticePoints->Origin->Coordinate1 = originX;
	latticePoints->Origin->Coordinate2 = originY;
	latticePoints->Origin->Coordinate3 = originZ;

	// first (slowest) dim :fastest is I (or inline), slowest is J (or crossline)
	resqml22__Point3dLatticeDimension* latticeDimForJ = soap_new_resqml22__Point3dLatticeDimension(gsoapProxy2_3->soap);
	latticeDimForJ->Direction = soap_new_resqml22__Point3d(gsoapProxy2_3->soap);
	latticeDimForJ->Direction->Coordinate1 = offsetJX;
	latticeDimForJ->Direction->Coordinate2 = offsetJY;
	latticeDimForJ->Direction->Coordinate3 = offsetJZ;
	eml23__FloatingPointConstantArray* spacingForJ = soap_new_eml23__FloatingPointConstantArray(gsoapProxy2_3->soap);
	spacingForJ->Value = spacingJ;
	spacingForJ->Count = numJ - 1;
	latticeDimForJ->Spacing = spacingForJ;
	latticePoints->Dimension.push_back(latticeDimForJ);

	//second (fastest) dim :fastest is I (or inline), slowest is J (or crossline)
	resqml22__Point3dLatticeDimension* latticeDimForI = soap_new_resqml22__Point3dLatticeDimension(gsoapProxy2_3->soap);
	latticeDimForI->Direction = soap_new_resqml22__Point3d(gsoapProxy2_3->soap);
	latticeDimForI->Direction->Coordinate1 = offsetIX;
	latticeDimForI->Direction->Coordinate2 = offsetIY;
	latticeDimForI->Direction->Coordinate3 = offsetIZ;
	eml23__FloatingPointConstantArray* spacingForI = soap_new_eml23__FloatingPointConstantArray(gsoapProxy2_3->soap);
	spacingForI->Value = spacingI;
	spacingForI->Count = numI - 1;
	latticeDimForI->Spacing = spacingForI;
	latticePoints->Dimension.push_back(latticeDimForI);

	xmlPoints->SupportingGeometry = latticePoints;

	// Z Values
	eml23__FloatingPointExternalArray* xmlZValues = soap_new_eml23__FloatingPointExternalArray(gsoapProxy2_3->soap);
	xmlZValues->Values = soap_new_eml23__ExternalDataArray(gsoapProxy2_3->soap);
	xmlZValues->Values->ExternalDataArrayPart.push_back(createExternalDataArrayPart(getHdfGroup() +"/points_patch" + std::to_string(patchIndex), numJ * numI, proxy));
	xmlPoints->ZValues = xmlZValues;

	// HDF
	hsize_t dim[2] = { numJ, numI };
	proxy->writeArrayNdOfDoubleValues(getHdfGroup(),
		"points_patch" + std::to_string(patchIndex),
		zValues,
		dim, 2);

	geom->Points = xmlPoints;

	return geom;
}
