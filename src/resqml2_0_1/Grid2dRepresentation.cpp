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
#include "resqml2_0_1/Grid2dRepresentation.h"

#include <algorithm>
#include <stdexcept>

#include "resqml2/AbstractFeatureInterpretation.h"
#include "resqml2_0_1/SeismicLatticeFeature.h"
#include "common/AbstractHdfProxy.h"
#include "resqml2/AbstractLocal3dCrs.h"

using namespace std;
using namespace RESQML2_0_1_NS;
using namespace gsoap_resqml2_0_1;
using namespace epc;

const char* Grid2dRepresentation::XML_TAG = "Grid2dRepresentation";

Grid2dRepresentation::Grid2dRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp, RESQML2_NS::AbstractLocal3dCrs * crs,
	const string & guid, const std::string & title):
	AbstractSurfaceRepresentation(interp, crs), supportingRepresentation(nullptr)
{
	gsoapProxy2_0_1 = soap_new_resqml2__obj_USCOREGrid2dRepresentation(interp->getGsoapContext(), 1);
	_resqml2__Grid2dRepresentation* singleGrid2dRep = static_cast<_resqml2__Grid2dRepresentation*>(gsoapProxy2_0_1);

	initMandatoryMetadata();
	setMetadata(guid, title, std::string(), -1, std::string(), std::string(), -1, std::string());

	// Surface role
	if (interp->getInterpretedFeature()->getGsoapType() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__obj_USCORESeismicLatticeFeature)
		singleGrid2dRep->SurfaceRole = resqml2__SurfaceRole__pick;

	// relationhsips
	localCrs = crs;
	localCrs->addRepresentation(this);

	setInterpretation(interp);
}

resqml2__PointGeometry* Grid2dRepresentation::getPointGeometry2_0_1(const unsigned int & patchIndex) const
{
	if (patchIndex == 0)
		return static_cast<_resqml2__Grid2dRepresentation*>(gsoapProxy2_0_1)->Grid2dPatch->Geometry;
	else
		return nullptr;
}

string Grid2dRepresentation::getHdfProxyUuid() const
{
	return getHdfProxyUuidFromPointGeometryPatch(getPointGeometry2_0_1(0));
}

ULONG64 Grid2dRepresentation::getNodeCountAlongIAxis() const
{
	return static_cast<_resqml2__Grid2dRepresentation*>(gsoapProxy2_0_1)->Grid2dPatch->FastestAxisCount;
}

ULONG64 Grid2dRepresentation::getNodeCountAlongJAxis() const
{
	return static_cast<_resqml2__Grid2dRepresentation*>(gsoapProxy2_0_1)->Grid2dPatch->SlowestAxisCount;
}

ULONG64 Grid2dRepresentation::getXyzPointCountOfPatch(const unsigned int & patchIndex) const
{
	if (patchIndex >= getPatchCount()) {
		throw range_error("The index patch is not in the allowed range of patch.");
	}

	return getNodeCountAlongIAxis() * getNodeCountAlongJAxis();
}

void Grid2dRepresentation::getXyzPointsOfPatch(const unsigned int & patchIndex, double * xyzPoints) const
{
	if (patchIndex >= getPatchCount()) {
		throw range_error("The index patch is not in the allowed range of patch.");
	}

	throw logic_error("Please compute X and Y values with the lattice information.");
}

void Grid2dRepresentation::getZValues(double* values) const
{
	_resqml2__Grid2dRepresentation* rep = static_cast<_resqml2__Grid2dRepresentation*>(gsoapProxy2_0_1);

	if (rep->Grid2dPatch->Geometry->Points->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__Point3dZValueArray) {
		resqml2__AbstractDoubleArray* zValues = static_cast<resqml2__Point3dZValueArray*>(rep->Grid2dPatch->Geometry->Points)->ZValues;
		if (zValues->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__DoubleHdf5Array) {
			hdfProxy->readArrayNdOfDoubleValues(static_cast<resqml2__DoubleHdf5Array*>(zValues)->Values->PathInHdfFile, values);
		}
		else {
			throw std::logic_error("The Z values can only be retrieved if they are described as a DoubleHdf5Array.");
		}
	}
	else if (rep->Grid2dPatch->Geometry->Points->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__Point3dLatticeArray) {
		const double zOrigin = getZOrigin();
		double zIOffset = getZIOffset();
		double zJOffset = getZJOffset();

		if (isISpacingConstant() && isJSpacingConstant()) {
			const ULONG64 iNodeCount = getNodeCountAlongIAxis();
			const ULONG64 jNodeCount = getNodeCountAlongJAxis();
			for (size_t jNode = 0; jNode < jNodeCount; ++jNode) {
				for (size_t iNode = 0; iNode < iNodeCount; ++iNode) {
					values[iNode + jNode*iNodeCount] = zOrigin + zIOffset*iNode + zJOffset*jNode;
				}
			}
		}
		else {
			const ULONG64 iNodeCount = getNodeCountAlongIAxis();
			const ULONG64 jNodeCount = getNodeCountAlongJAxis();
			double* iSpacings = new double[iNodeCount]; /// the size should rigourously be iNodeCount - 1. For optimization reason, we just have one extra item to avoid a range error in the later for loop where the last item is accessed but not used anyhow.
			getISpacing(iSpacings);
			double* jSpacings = new double[jNodeCount]; /// the size should rigourously be jNodeCount - 1. For optimization reason, we just have one extra item to avoid a range error in the later for loop where the last item is accessed but not used anyhow.
			getJSpacing(jSpacings);

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

			delete[] iSpacings;
			delete[] jSpacings;
		}
	}
	else {
		throw std::logic_error("The Z values can only be retrieved for a Point3dZValueArray or a Point3dLatticeArray geometry.");
	}
}

void Grid2dRepresentation::getZValuesInGlobalCrs(double * values) const
{
	getZValues(values);

	if (localCrs->getGsoapType() != SOAP_TYPE_gsoap_resqml2_0_1_resqml2__obj_USCORELocalTime3dCrs) {
		_resqml2__Grid2dRepresentation* rep = static_cast<_resqml2__Grid2dRepresentation*>(gsoapProxy2_0_1);
		const ULONG64 nodeCount = rep->Grid2dPatch->FastestAxisCount * rep->Grid2dPatch->SlowestAxisCount;
		const double zOffset = localCrs->getOriginDepthOrElevation();
		if (zOffset != .0) {
			for (size_t index = 0; index < nodeCount; ++index)
				values[index] += zOffset;
		}
	}
}

resqml2__Point3dLatticeArray* Grid2dRepresentation::getArrayLatticeOfPoints3d() const
{
	resqml2__Grid2dPatch* patch = static_cast<_resqml2__Grid2dRepresentation*>(gsoapProxy2_0_1)->Grid2dPatch;
	if (patch->Geometry->Points->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__Point3dLatticeArray) {
		return static_cast<resqml2__Point3dLatticeArray*>(patch->Geometry->Points);
	}
	
	if (patch->Geometry->Points->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__Point3dZValueArray) {
		resqml2__Point3dZValueArray* arrayOfZValuePoints3d = static_cast<resqml2__Point3dZValueArray*>(patch->Geometry->Points);
		if (arrayOfZValuePoints3d->SupportingGeometry->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__Point3dLatticeArray) {
			return static_cast<resqml2__Point3dLatticeArray*>(arrayOfZValuePoints3d->SupportingGeometry);
		}
	}

	return nullptr;
}

double Grid2dRepresentation::getXOrigin() const
{
	resqml2__Point3dLatticeArray* arrayLatticeOfPoints3d = getArrayLatticeOfPoints3d();

	if (arrayLatticeOfPoints3d != nullptr) {
		return arrayLatticeOfPoints3d->Origin->Coordinate1;
	}

	if (!getSupportingRepresentationUuid().empty()) {
		const int iOrigin = getIndexOriginOnSupportingRepresentation(1); // I is fastest
		const int jOrigin = getIndexOriginOnSupportingRepresentation(0); // J is slowest

		return iOrigin == 0 && jOrigin == 0 ? supportingRepresentation->getXOrigin() :
			supportingRepresentation->getXOrigin() + iOrigin*supportingRepresentation->getXIOffset() + jOrigin*supportingRepresentation->getXJOffset();

	}

	return std::numeric_limits<double>::signaling_NaN();
}

double Grid2dRepresentation::getYOrigin() const
{
	resqml2__Point3dLatticeArray* arrayLatticeOfPoints3d = getArrayLatticeOfPoints3d();

	if (arrayLatticeOfPoints3d != nullptr) {
		return arrayLatticeOfPoints3d->Origin->Coordinate2;
	}
	
	if (!getSupportingRepresentationUuid().empty()) {
		const int iOrigin = getIndexOriginOnSupportingRepresentation(1); // I is fastest
		const int jOrigin = getIndexOriginOnSupportingRepresentation(0); // J is slowest

		return iOrigin == 0 && jOrigin == 0 ? supportingRepresentation->getYOrigin() :
			supportingRepresentation->getYOrigin() + iOrigin*supportingRepresentation->getYIOffset() + jOrigin*supportingRepresentation->getYJOffset();
	}

	return std::numeric_limits<double>::signaling_NaN();
}

double Grid2dRepresentation::getZOrigin() const
{
	resqml2__Point3dLatticeArray* arrayLatticeOfPoints3d = getArrayLatticeOfPoints3d();

	if (arrayLatticeOfPoints3d != nullptr) {
		return arrayLatticeOfPoints3d->Origin->Coordinate3;
	}
	
	if (!getSupportingRepresentationUuid().empty()) {
		const int iOrigin = getIndexOriginOnSupportingRepresentation(1); // I is fastest
		const int jOrigin = getIndexOriginOnSupportingRepresentation(0); // J is slowest

		return iOrigin == 0 && jOrigin == 0 ? supportingRepresentation->getZOrigin() :
			supportingRepresentation->getZOrigin() + iOrigin*supportingRepresentation->getZIOffset() + jOrigin*supportingRepresentation->getZJOffset();
	}
	
	return std::numeric_limits<double>::signaling_NaN();
}

double Grid2dRepresentation::getComponentInGlobalCrs(double x, double y, double z, size_t componentIndex) const
{
	double result[] = { x, y, z };
	if (result[componentIndex] != result[componentIndex]) {
		return result[componentIndex];
	}

	localCrs->convertXyzPointsToGlobalCrs(result, 1, true);

	return result[componentIndex];
}

double Grid2dRepresentation::getXOriginInGlobalCrs() const
{
	return getComponentInGlobalCrs(getXOrigin(), getYOrigin(), getZOrigin(), 0);
}

double Grid2dRepresentation::getYOriginInGlobalCrs() const
{
	return getComponentInGlobalCrs(getXOrigin(), getYOrigin(), getZOrigin(), 1);
}

double Grid2dRepresentation::getZOriginInGlobalCrs() const
{
	return getComponentInGlobalCrs(getXOrigin(), getYOrigin(), getZOrigin(), 2);
}

double Grid2dRepresentation::getXJOffset() const
{
	resqml2__Point3dLatticeArray* arrayLatticeOfPoints3d = getArrayLatticeOfPoints3d();

	if (arrayLatticeOfPoints3d != nullptr) {
		resqml2__Point3d * offset = arrayLatticeOfPoints3d->Offset[0]->Offset;
		return isJSpacingConstant() ?
			offset->Coordinate1 * getJSpacing() /
			sqrt(offset->Coordinate1 * offset->Coordinate1 + offset->Coordinate2 * offset->Coordinate2) :
			offset->Coordinate1;
	}
	
	if (!getSupportingRepresentationUuid().empty()) {
		return supportingRepresentation->getXJOffset() * getIndexOffsetOnSupportingRepresentation(0);
	}

	throw invalid_argument("No lattice array have been found for this 2d grid.");
}

double Grid2dRepresentation::getYJOffset() const
{
	resqml2__Point3dLatticeArray* arrayLatticeOfPoints3d = getArrayLatticeOfPoints3d();

	if (arrayLatticeOfPoints3d != nullptr) {
		resqml2__Point3d * offset = arrayLatticeOfPoints3d->Offset[0]->Offset;
		return isJSpacingConstant() ?
			offset->Coordinate2 * getJSpacing() /
			sqrt(offset->Coordinate1 * offset->Coordinate1 + offset->Coordinate2 * offset->Coordinate2) :
			offset->Coordinate2;
	}
	
	if (!getSupportingRepresentationUuid().empty()) {
		return supportingRepresentation->getYJOffset() * getIndexOffsetOnSupportingRepresentation(0);
	}

	throw invalid_argument("No lattice array have been found for this 2d grid.");
}

double Grid2dRepresentation::getZJOffset() const
{
	resqml2__Point3dLatticeArray* arrayLatticeOfPoints3d = getArrayLatticeOfPoints3d();

	if (arrayLatticeOfPoints3d != nullptr) {
		resqml2__Point3d * offset = arrayLatticeOfPoints3d->Offset[0]->Offset;
		return isJSpacingConstant() ?
			offset->Coordinate3 * getJSpacing() /
			sqrt(offset->Coordinate1 * offset->Coordinate1 + offset->Coordinate2 * offset->Coordinate2) :
			offset->Coordinate3;
	}
	
	if (!getSupportingRepresentationUuid().empty()) {
		return supportingRepresentation->getZJOffset() * getIndexOffsetOnSupportingRepresentation(0);
	}

	throw invalid_argument("No lattice array have been found for this 2d grid.");
}

double Grid2dRepresentation::getXJOffsetInGlobalCrs() const
{
	return getComponentInGlobalCrs(getXJOffset(), getYJOffset(), getZJOffset(), 0);
}

double Grid2dRepresentation::getYJOffsetInGlobalCrs() const
{
	return getComponentInGlobalCrs(getXJOffset(), getYJOffset(), getZJOffset(), 1);
}

double Grid2dRepresentation::getZJOffsetInGlobalCrs() const
{
	return getComponentInGlobalCrs(getXJOffset(), getYJOffset(), getZJOffset(), 2);
}

double Grid2dRepresentation::getXIOffset() const
{
	resqml2__Point3dLatticeArray* arrayLatticeOfPoints3d = getArrayLatticeOfPoints3d();

	if (arrayLatticeOfPoints3d != nullptr) {
		resqml2__Point3d * offset = arrayLatticeOfPoints3d->Offset[1]->Offset;
		return isISpacingConstant() ? 
			offset->Coordinate1 * getISpacing() /
			sqrt(offset->Coordinate1 * offset->Coordinate1 + offset->Coordinate2 * offset->Coordinate2) :
			offset->Coordinate1;
	}
	
	if (!getSupportingRepresentationUuid().empty()) {
		return supportingRepresentation->getXIOffset() * getIndexOffsetOnSupportingRepresentation(1);
	}

	throw invalid_argument("No lattice array have been found for this 2d grid.");
}

double Grid2dRepresentation::getYIOffset() const
{
	resqml2__Point3dLatticeArray* arrayLatticeOfPoints3d = getArrayLatticeOfPoints3d();

	if (arrayLatticeOfPoints3d != nullptr) {
		resqml2__Point3d * offset = arrayLatticeOfPoints3d->Offset[1]->Offset;
		return isISpacingConstant() ?
			offset->Coordinate2 * getISpacing() /
			sqrt(offset->Coordinate1 * offset->Coordinate1 + offset->Coordinate2 * offset->Coordinate2) :
			offset->Coordinate2;
	}
	
	if (!getSupportingRepresentationUuid().empty()) {
		return supportingRepresentation->getYIOffset() * getIndexOffsetOnSupportingRepresentation(1);
	}

	throw invalid_argument("No lattice array have been found for this 2d grid.");
}

double Grid2dRepresentation::getZIOffset() const
{
	resqml2__Point3dLatticeArray* arrayLatticeOfPoints3d = getArrayLatticeOfPoints3d();

	if (arrayLatticeOfPoints3d != nullptr) {
		resqml2__Point3d * offset = arrayLatticeOfPoints3d->Offset[1]->Offset;
		return isISpacingConstant() ?
			offset->Coordinate3 * getISpacing() /
			sqrt(offset->Coordinate1 * offset->Coordinate1 + offset->Coordinate2 * offset->Coordinate2) :
			offset->Coordinate3;
	}

	if (!getSupportingRepresentationUuid().empty()) {
		return supportingRepresentation->getYIOffset() * getIndexOffsetOnSupportingRepresentation(1);
	}

	throw invalid_argument("No lattice array have been found for this 2d grid.");
}

double Grid2dRepresentation::getXIOffsetInGlobalCrs() const
{
	return getComponentInGlobalCrs(getXIOffset(), getYIOffset(), getZIOffset(), 0);
}

double Grid2dRepresentation::getYIOffsetInGlobalCrs() const
{
	return getComponentInGlobalCrs(getXIOffset(), getYIOffset(), getZIOffset(), 1);
}

double Grid2dRepresentation::getZIOffsetInGlobalCrs() const
{
	return getComponentInGlobalCrs(getXIOffset(), getYIOffset(), getZIOffset(), 2);
}

bool Grid2dRepresentation::isJSpacingConstant() const
{
	const resqml2__Point3dLatticeArray* const arrayLatticeOfPoints3d = getArrayLatticeOfPoints3d();

	if (arrayLatticeOfPoints3d != nullptr) {
		if (!arrayLatticeOfPoints3d->Offset.empty()) {
			return arrayLatticeOfPoints3d->Offset[0]->Spacing->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__DoubleConstantArray;
		}

		throw invalid_argument("This 2d grid representation does not look to have dimensions.");
	}
	else if (!getSupportingRepresentationUuid().empty()) {
		return supportingRepresentation->isJSpacingConstant();
	}

	throw logic_error("This 2D grid representation looks not valid : no lattice geometry and non supporting grid 2D representation.");
}

bool Grid2dRepresentation::isISpacingConstant() const
{
	const resqml2__Point3dLatticeArray* const arrayLatticeOfPoints3d = getArrayLatticeOfPoints3d();

	if (arrayLatticeOfPoints3d != nullptr) {
		if (arrayLatticeOfPoints3d->Offset.size() > 1) {
			return arrayLatticeOfPoints3d->Offset[1]->Spacing->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__DoubleConstantArray;
		}
		
		throw invalid_argument("This 2d grid representation does not look to have (at least) 2 dimensions.");
	}
	else if (!getSupportingRepresentationUuid().empty()) {
		return supportingRepresentation->isISpacingConstant();
	}

	throw logic_error("This 2D grid representation looks not valid : no lattice geometry and non supporting grid 2D representation.");
}

double Grid2dRepresentation::getJSpacing() const
{
	if (!isJSpacingConstant()) {
		throw invalid_argument("The J spacing of this 2d grid does not look to be constant.");
	}

	const resqml2__Point3dLatticeArray* const arrayLatticeOfPoints3d = getArrayLatticeOfPoints3d();

	if (arrayLatticeOfPoints3d != nullptr) {
		return static_cast<resqml2__DoubleConstantArray*>(arrayLatticeOfPoints3d->Offset[0]->Spacing)->Value;
	}

	const int jIndexOffset = getIndexOffsetOnSupportingRepresentation(0);
	const double jSpacingOnSupportingRep = supportingRepresentation->getJSpacing();

	return jIndexOffset * jSpacingOnSupportingRep;
}

void Grid2dRepresentation::getJSpacing(double* const jSpacings) const
{
	const resqml2__Point3dLatticeArray* const arrayLatticeOfPoints3d = getArrayLatticeOfPoints3d();

	const ULONG64 jSpacingCount = getNodeCountAlongJAxis() - 1;

	if (arrayLatticeOfPoints3d != nullptr) {
		if (arrayLatticeOfPoints3d->Offset[0]->Spacing->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__DoubleConstantArray) {
			const double constantSpacing = static_cast<resqml2__DoubleConstantArray*>(arrayLatticeOfPoints3d->Offset[0]->Spacing)->Value;
			for (ULONG64 j = 0; j < jSpacingCount; ++j) {
				jSpacings[j] = constantSpacing;
			}
		}
		else if (arrayLatticeOfPoints3d->Offset[0]->Spacing->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__DoubleHdf5Array) {
			hdfProxy->readArrayNdOfDoubleValues(static_cast<resqml2__DoubleHdf5Array*>(arrayLatticeOfPoints3d->Offset[0]->Spacing)->Values->PathInHdfFile, jSpacings);
		}
		else {
			throw logic_error("Not implemented yet.");
		}
	}
	else if (getSupportingRepresentationUuid().size())
	{
		const int jIndexOrigin = getIndexOriginOnSupportingRepresentation(0);
		const int jIndexOffset = getIndexOffsetOnSupportingRepresentation(0);
		double* const jSpacingsOnSupportingRep = new double[jSpacingCount];
		supportingRepresentation->getJSpacing(jSpacingsOnSupportingRep);
		
		for (ULONG64 j = 0; j < jSpacingCount; ++j) {
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
				throw invalid_argument("The index offset on supporting representation cannot be 0.");
			}
		}

		delete[] jSpacingsOnSupportingRep;
	}
	else
		throw logic_error("This 2D grid representation looks not valid : no lattice geometry and non supporting grid 2D representation.");
}

double Grid2dRepresentation::getISpacing() const
{
	if (!isISpacingConstant()) {
		throw invalid_argument("The I spacing of this 2d grid does not look to be constant.");
	}

	const resqml2__Point3dLatticeArray* const arrayLatticeOfPoints3d = getArrayLatticeOfPoints3d();

	if (arrayLatticeOfPoints3d != nullptr) {
		return static_cast<resqml2__DoubleConstantArray*>(arrayLatticeOfPoints3d->Offset[1]->Spacing)->Value;
	}

	const int iIndexOffset = getIndexOffsetOnSupportingRepresentation(1);
	const double iSpacingOnSupportingRep = supportingRepresentation->getISpacing();

	return iIndexOffset * iSpacingOnSupportingRep;
}

void Grid2dRepresentation::getISpacing(double* const iSpacings) const
{
	const resqml2__Point3dLatticeArray* const arrayLatticeOfPoints3d = getArrayLatticeOfPoints3d();

	const ULONG64 iSpacingCount = getNodeCountAlongIAxis() - 1;

	if (arrayLatticeOfPoints3d != nullptr) {
		if (arrayLatticeOfPoints3d->Offset[1]->Spacing->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__DoubleConstantArray) {
			const double constantSpacing = static_cast<resqml2__DoubleConstantArray*>(arrayLatticeOfPoints3d->Offset[1]->Spacing)->Value;
			for (ULONG64 i = 0; i < iSpacingCount; ++i) {
				iSpacings[i] = constantSpacing;
			}
		}
		else if (arrayLatticeOfPoints3d->Offset[1]->Spacing->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__DoubleHdf5Array) {
			hdfProxy->readArrayNdOfDoubleValues(static_cast<resqml2__DoubleHdf5Array*>(arrayLatticeOfPoints3d->Offset[1]->Spacing)->Values->PathInHdfFile, iSpacings);
		}
		else {
			throw logic_error("Not implemented yet.");
		}
	}
	else if (getSupportingRepresentationUuid().size())
	{
		const int iIndexOrigin = getIndexOriginOnSupportingRepresentation(1);
		const int iIndexOffset = getIndexOffsetOnSupportingRepresentation(1);
		double* const iSpacingsOnSupportingRep = new double[iSpacingCount];
		supportingRepresentation->getISpacing(iSpacingsOnSupportingRep);

		for (ULONG64 i = 0; i < iSpacingCount; ++i) {
			iSpacings[i] = .0;
			if (iIndexOffset > 0) {
				for (size_t tmp = 0; tmp < iIndexOffset; ++tmp) {
					iSpacings[i] += iSpacingsOnSupportingRep[iIndexOrigin + i * iIndexOffset + tmp];
				}
			}
			else if (iIndexOffset < 0) {
				for (size_t tmp = 0; tmp > iIndexOffset; --tmp) {
					iSpacings[i] += iSpacingsOnSupportingRep[iIndexOrigin - 1 + i * iIndexOffset + tmp];
				}
			}
			else {
				throw invalid_argument("The index offset on supporting representation cannot be 0.");
			}
		}

		delete[] iSpacingsOnSupportingRep;
	}
	else
		throw logic_error("This 2D grid representation looks not valid : no lattice geometry and non supporting grid 2D representation.");
}

void Grid2dRepresentation::setGeometryAsArray2dOfLatticePoints3d(
			const unsigned int & numPointsInFastestDirection, const unsigned int & numPointsInSlowestDirection,
			const double & xOrigin, const double & yOrigin, const double & zOrigin,
			const double & xOffsetInFastestDirection, const double & yOffsetInFastestDirection, const double & zOffsetInFastestDirection,
			const double & xOffsetInSlowestDirection, const double & yOffsetInSlowestDirection, const double & zOffsetInSlowestDirection,
			const double & spacingInFastestDirection, const double & spacingInSlowestDirection)
{
	resqml2__PointGeometry* geomPatch = createArray2dOfLatticePoints3d(numPointsInFastestDirection, numPointsInSlowestDirection,
			xOrigin, yOrigin, zOrigin,
			xOffsetInFastestDirection, yOffsetInFastestDirection, zOffsetInFastestDirection,
			xOffsetInSlowestDirection, yOffsetInSlowestDirection, zOffsetInSlowestDirection,
			spacingInFastestDirection, spacingInSlowestDirection);

	resqml2__Grid2dPatch* patch = static_cast<_resqml2__Grid2dRepresentation*>(gsoapProxy2_0_1)->Grid2dPatch;
	patch = soap_new_resqml2__Grid2dPatch(gsoapProxy2_0_1->soap, 1);
	patch->PatchIndex = 0;
	patch->Geometry = geomPatch;
	patch->SlowestAxisCount = numPointsInSlowestDirection;
	patch->FastestAxisCount = numPointsInFastestDirection;

	static_cast<_resqml2__Grid2dRepresentation*>(gsoapProxy2_0_1)->Grid2dPatch = patch;
}

void Grid2dRepresentation::setGeometryAsArray2dOfExplicitZ(
		double * zValues,
		const unsigned int & numI, const unsigned int & numJ, COMMON_NS::AbstractHdfProxy * proxy,
		Grid2dRepresentation * supportingGrid2dRepresentation,
		const unsigned int & startIndexI, const unsigned int & startIndexJ,
		const int & indexIncrementI, const int & indexIncrementJ)
{
	resqml2__Grid2dPatch* patch = soap_new_resqml2__Grid2dPatch(gsoapProxy2_0_1->soap, 1);
	static_cast<_resqml2__Grid2dRepresentation*>(gsoapProxy2_0_1)->Grid2dPatch = patch;

	patch->PatchIndex = 0;
	patch->SlowestAxisCount = numJ;
	patch->FastestAxisCount = numI;

	setSupportingRepresentation(supportingGrid2dRepresentation);
	resqml2__PointGeometry* geomPatch = createArray2dOfExplicitZ(0,
			zValues,
			numI, numJ, proxy,
			supportingGrid2dRepresentation,
			startIndexI + startIndexJ * getNodeCountAlongIAxis(),
			indexIncrementI, indexIncrementJ);
	patch->Geometry = geomPatch;
}

void Grid2dRepresentation::setGeometryAsArray2dOfExplicitZ(
				double * zValues,
				const unsigned int & numI, const unsigned int & numJ, COMMON_NS::AbstractHdfProxy * proxy,
				const double & originX, const double & originY, const double & originZ,
				const double & offsetIX, const double & offsetIY, const double & offsetIZ, const double & spacingI,
				const double & offsetJX, const double & offsetJY, const double & offsetJZ, const double & spacingJ)
{
	resqml2__Grid2dPatch* patch = soap_new_resqml2__Grid2dPatch(gsoapProxy2_0_1->soap, 1);
	static_cast<_resqml2__Grid2dRepresentation*>(gsoapProxy2_0_1)->Grid2dPatch = patch;

	patch->PatchIndex = 0;
	patch->SlowestAxisCount = numJ;
	patch->FastestAxisCount = numI;

	resqml2__PointGeometry* geomPatch = createArray2dOfExplicitZ(0,
			zValues,
			numI, numJ, proxy,
			originX, originY, originZ,
			offsetIX, offsetIY, offsetIZ, spacingI,
			offsetJX, offsetJY, offsetJZ, spacingJ);
	patch->Geometry = geomPatch;
}

std::string Grid2dRepresentation::getSupportingRepresentationUuid() const
{
	_resqml2__Grid2dRepresentation* singleGrid2dRep = static_cast<_resqml2__Grid2dRepresentation*>(gsoapProxy2_0_1);
	if (singleGrid2dRep != nullptr && singleGrid2dRep->Grid2dPatch->Geometry->Points->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__Point3dZValueArray) {
		resqml2__Point3dZValueArray* tmp = static_cast<resqml2__Point3dZValueArray*>(singleGrid2dRep->Grid2dPatch->Geometry->Points);
		if (tmp->SupportingGeometry->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml2__Point3dFromRepresentationLatticeArray) {
			return static_cast<resqml2__Point3dFromRepresentationLatticeArray*>(tmp->SupportingGeometry)->SupportingRepresentation->UUID;
		}
	}

	return string();
}

void Grid2dRepresentation::setSupportingRepresentation(Grid2dRepresentation * supportingRep)
{
	if (supportingRep == nullptr) {
		throw invalid_argument("The supporting representation to set cannot be null.");
	}

	supportingRepresentation = supportingRep;
	supportingRepresentation->supportedRepresentationSet.push_back(this);
}

int Grid2dRepresentation::getIndexOriginOnSupportingRepresentation() const
{
	resqml2__Point3dFromRepresentationLatticeArray* geom = getPoint3dFromRepresentationLatticeArrayFromPointGeometryPatch(static_cast<_resqml2__Grid2dRepresentation*>(gsoapProxy2_0_1)->Grid2dPatch->Geometry);

	if (geom != nullptr) {
		return geom->NodeIndicesOnSupportingRepresentation->StartValue;
	}

	throw invalid_argument("It does not exist supporting representation for this representation.");
}

int Grid2dRepresentation::getIndexOriginOnSupportingRepresentation(const unsigned int & dimension) const
{
	resqml2__Point3dFromRepresentationLatticeArray* geom = getPoint3dFromRepresentationLatticeArrayFromPointGeometryPatch(static_cast<_resqml2__Grid2dRepresentation*>(gsoapProxy2_0_1)->Grid2dPatch->Geometry);

	if (geom != nullptr)
	{
		if (dimension == 0) // J dimension : slowest
			return geom->NodeIndicesOnSupportingRepresentation->StartValue / supportingRepresentation->getNodeCountAlongIAxis();
		else if (dimension == 1) // I dimension : fastest
			return geom->NodeIndicesOnSupportingRepresentation->StartValue % supportingRepresentation->getNodeCountAlongIAxis();
		throw invalid_argument("There cannot be more than 2 dimensions for a grid 2d representation.");
	}

	throw invalid_argument("It does not exist supporting representation for this representation.");
}

int Grid2dRepresentation::getNodeCountOnSupportingRepresentation(const unsigned int & dimension) const
{
	resqml2__Point3dFromRepresentationLatticeArray* geom = getPoint3dFromRepresentationLatticeArrayFromPointGeometryPatch(static_cast<_resqml2__Grid2dRepresentation*>(gsoapProxy2_0_1)->Grid2dPatch->Geometry);

	if (geom != nullptr) {
		return geom->NodeIndicesOnSupportingRepresentation->Offset[dimension]->Count + 1;
	}
	
	throw invalid_argument("It does not exist supporting representation for this representation.");
}

int Grid2dRepresentation::getIndexOffsetOnSupportingRepresentation(const unsigned int & dimension) const
{
	resqml2__Point3dFromRepresentationLatticeArray* geom = getPoint3dFromRepresentationLatticeArrayFromPointGeometryPatch(static_cast<_resqml2__Grid2dRepresentation*>(gsoapProxy2_0_1)->Grid2dPatch->Geometry);

	if (geom != nullptr) {
		return geom->NodeIndicesOnSupportingRepresentation->Offset[dimension]->Value;
	}

	throw invalid_argument("It does not exist supporting representation for this representation.");
}

vector<Relationship> Grid2dRepresentation::getAllEpcRelationships() const
{
	vector<Relationship> result = AbstractSurfaceRepresentation::getAllEpcRelationships();

	// Supporting Grid 2D representation
	std::set<AbstractRepresentation*> allSeisSupport = getAllSeismicSupport();
	if (supportingRepresentation && std::find(allSeisSupport.begin(), allSeisSupport.end(), supportingRepresentation) == allSeisSupport.end())
	{
		Relationship relSupportingRepresentation(supportingRepresentation->getPartNameInEpcDocument(), "", supportingRepresentation->getUuid());
		relSupportingRepresentation.setDestinationObjectType();
		result.push_back(relSupportingRepresentation);
	}

	// Supported Grid 2D representations
	for(vector<AbstractRepresentation*>::const_iterator it = supportedRepresentationSet.begin(); it != supportedRepresentationSet.end(); ++it)
	{
		if (it == supportedRepresentationSet.begin() || std::find(supportedRepresentationSet.begin(), it, *it) != supportedRepresentationSet.end()) //  No need to add the rel twice
		{
			Relationship relChildRepresentation((*it)->getPartNameInEpcDocument(), "", (*it)->getUuid());
			relChildRepresentation.setSourceObjectType();
			result.push_back(relChildRepresentation);
		}
	}

	return result;
}

void Grid2dRepresentation::importRelationshipSetFromEpc(COMMON_NS::EpcDocument* epcDoc)
{
	AbstractSurfaceRepresentation::importRelationshipSetFromEpc(epcDoc);

	_resqml2__Grid2dRepresentation* singleGrid2dRep = static_cast<_resqml2__Grid2dRepresentation*>(gsoapProxy2_0_1);

	// Base representation
	const string supportingRepUuid = getSupportingRepresentationUuid();
	if (!supportingRepUuid.empty())
	{
		Grid2dRepresentation* grid2d = epcDoc->getDataObjectByUuid<Grid2dRepresentation>(supportingRepUuid);
		if (grid2d != nullptr) {
			setSupportingRepresentation(grid2d);
		}
		else {
			throw logic_error(getUuid() + "The referenced supporting representation does not look to be a 2d grid or is partial.");
		}
	}
}

