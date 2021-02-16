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
#include "../resqml2/AbstractLocal3dCrs.h"

using namespace std;
using namespace RESQML2_0_1_NS;
using namespace gsoap_resqml2_0_1;

const char* Grid2dRepresentation::XML_NS = "resqml20";

Grid2dRepresentation::Grid2dRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp,
	const string & guid, const std::string & title)
{
	if (interp == nullptr) {
		throw invalid_argument("The interpretation cannot be null.");
	}

	gsoapProxy2_0_1 = soap_new_resqml20__obj_USCOREGrid2dRepresentation(interp->getGsoapContext());
	_resqml20__Grid2dRepresentation* singleGrid2dRep = static_cast<_resqml20__Grid2dRepresentation*>(gsoapProxy2_0_1);

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "");

	// Surface role
	if (interp->getInterpretedFeature()->getGsoapType() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__obj_USCORESeismicLatticeFeature)
		singleGrid2dRep->SurfaceRole = resqml20__SurfaceRole::pick;

	setInterpretation(interp);
}

resqml20__PointGeometry* Grid2dRepresentation::getPointGeometry2_0_1(unsigned int patchIndex) const
{
	return patchIndex == 0 ? static_cast<_resqml20__Grid2dRepresentation*>(gsoapProxy2_0_1)->Grid2dPatch->Geometry : nullptr;
}

COMMON_NS::DataObjectReference Grid2dRepresentation::getHdfProxyDor() const
{
	return getHdfProxyDorFromPointGeometryPatch(getPointGeometry2_0_1(0));
}

uint64_t Grid2dRepresentation::getNodeCountAlongIAxis() const
{
	return static_cast<_resqml20__Grid2dRepresentation*>(gsoapProxy2_0_1)->Grid2dPatch->FastestAxisCount;
}

uint64_t Grid2dRepresentation::getNodeCountAlongJAxis() const
{
	return static_cast<_resqml20__Grid2dRepresentation*>(gsoapProxy2_0_1)->Grid2dPatch->SlowestAxisCount;
}

void Grid2dRepresentation::getZValues(double* values) const
{
	_resqml20__Grid2dRepresentation* rep = static_cast<_resqml20__Grid2dRepresentation*>(gsoapProxy2_0_1);

	if (rep->Grid2dPatch->Geometry->Points->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__Point3dZValueArray) {
		resqml20__AbstractDoubleArray* zValues = static_cast<resqml20__Point3dZValueArray*>(rep->Grid2dPatch->Geometry->Points)->ZValues;
		if (zValues->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__DoubleHdf5Array) {
			eml20__Hdf5Dataset const * dataset = static_cast<resqml20__DoubleHdf5Array*>(zValues)->Values;
			EML2_NS::AbstractHdfProxy * hdfProxy = getHdfProxyFromDataset(dataset);
			hdfProxy->readArrayNdOfDoubleValues(dataset->PathInHdfFile, values);
		}
		else {
			throw std::logic_error("The Z values can only be retrieved if they are described as a DoubleHdf5Array.");
		}
	}
	else if (rep->Grid2dPatch->Geometry->Points->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__Point3dLatticeArray) {
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

resqml20__Point3dLatticeArray* Grid2dRepresentation::getArrayLatticeOfPoints3d() const
{
	resqml20__Grid2dPatch* patch = static_cast<_resqml20__Grid2dRepresentation*>(gsoapProxy2_0_1)->Grid2dPatch;
	if (patch->Geometry->Points->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__Point3dLatticeArray) {
		return static_cast<resqml20__Point3dLatticeArray*>(patch->Geometry->Points);
	}
	
	if (patch->Geometry->Points->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__Point3dZValueArray) {
		resqml20__Point3dZValueArray* arrayOfZValuePoints3d = static_cast<resqml20__Point3dZValueArray*>(patch->Geometry->Points);
		if (arrayOfZValuePoints3d->SupportingGeometry->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__Point3dLatticeArray) {
			return static_cast<resqml20__Point3dLatticeArray*>(arrayOfZValuePoints3d->SupportingGeometry);
		}
	}

	return nullptr;
}

double Grid2dRepresentation::getXOrigin() const
{
	resqml20__Point3dLatticeArray* arrayLatticeOfPoints3d = getArrayLatticeOfPoints3d();

	if (arrayLatticeOfPoints3d != nullptr) {
		return arrayLatticeOfPoints3d->Origin->Coordinate1;
	}

	if (!getSupportingRepresentationDor().isEmpty()) {
		const int iOrigin = getIndexOriginOnSupportingRepresentation(1); // I is fastest
		const int jOrigin = getIndexOriginOnSupportingRepresentation(0); // J is slowest

		RESQML2_NS::Grid2dRepresentation const * supportingRepresentation = getSupportingRepresentation();
		return iOrigin == 0 && jOrigin == 0 ? supportingRepresentation->getXOrigin() :
			supportingRepresentation->getXOrigin() + iOrigin*supportingRepresentation->getXIOffset() + jOrigin*supportingRepresentation->getXJOffset();

	}

	return std::numeric_limits<double>::signaling_NaN();
}

double Grid2dRepresentation::getYOrigin() const
{
	resqml20__Point3dLatticeArray* arrayLatticeOfPoints3d = getArrayLatticeOfPoints3d();

	if (arrayLatticeOfPoints3d != nullptr) {
		return arrayLatticeOfPoints3d->Origin->Coordinate2;
	}
	
	if (!getSupportingRepresentationDor().isEmpty()) {
		const int iOrigin = getIndexOriginOnSupportingRepresentation(1); // I is fastest
		const int jOrigin = getIndexOriginOnSupportingRepresentation(0); // J is slowest

		RESQML2_NS::Grid2dRepresentation const * supportingRepresentation = getSupportingRepresentation();
		return iOrigin == 0 && jOrigin == 0 ? supportingRepresentation->getYOrigin() :
			supportingRepresentation->getYOrigin() + iOrigin*supportingRepresentation->getYIOffset() + jOrigin*supportingRepresentation->getYJOffset();
	}

	return std::numeric_limits<double>::signaling_NaN();
}

double Grid2dRepresentation::getZOrigin() const
{
	resqml20__Point3dLatticeArray* arrayLatticeOfPoints3d = getArrayLatticeOfPoints3d();

	if (arrayLatticeOfPoints3d != nullptr) {
		return arrayLatticeOfPoints3d->Origin->Coordinate3;
	}
	
	if (!getSupportingRepresentationDor().isEmpty()) {
		const int iOrigin = getIndexOriginOnSupportingRepresentation(1); // I is fastest
		const int jOrigin = getIndexOriginOnSupportingRepresentation(0); // J is slowest

		RESQML2_NS::Grid2dRepresentation const * supportingRepresentation = getSupportingRepresentation();
		return iOrigin == 0 && jOrigin == 0 ? supportingRepresentation->getZOrigin() :
			supportingRepresentation->getZOrigin() + iOrigin*supportingRepresentation->getZIOffset() + jOrigin*supportingRepresentation->getZJOffset();
	}
	
	return std::numeric_limits<double>::signaling_NaN();
}

double Grid2dRepresentation::getXJOffset() const
{
	resqml20__Point3dLatticeArray* arrayLatticeOfPoints3d = getArrayLatticeOfPoints3d();

	if (arrayLatticeOfPoints3d != nullptr) {
		resqml20__Point3d * offset = arrayLatticeOfPoints3d->Offset[0]->Offset;
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
	resqml20__Point3dLatticeArray* arrayLatticeOfPoints3d = getArrayLatticeOfPoints3d();

	if (arrayLatticeOfPoints3d != nullptr) {
		resqml20__Point3d * offset = arrayLatticeOfPoints3d->Offset[0]->Offset;
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
	resqml20__Point3dLatticeArray* arrayLatticeOfPoints3d = getArrayLatticeOfPoints3d();

	if (arrayLatticeOfPoints3d != nullptr) {
		resqml20__Point3d * offset = arrayLatticeOfPoints3d->Offset[0]->Offset;
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
	resqml20__Point3dLatticeArray* arrayLatticeOfPoints3d = getArrayLatticeOfPoints3d();

	if (arrayLatticeOfPoints3d != nullptr) {
		resqml20__Point3d * offset = arrayLatticeOfPoints3d->Offset[1]->Offset;
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
	resqml20__Point3dLatticeArray* arrayLatticeOfPoints3d = getArrayLatticeOfPoints3d();

	if (arrayLatticeOfPoints3d != nullptr) {
		resqml20__Point3d * offset = arrayLatticeOfPoints3d->Offset[1]->Offset;
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
	resqml20__Point3dLatticeArray* arrayLatticeOfPoints3d = getArrayLatticeOfPoints3d();

	if (arrayLatticeOfPoints3d != nullptr) {
		resqml20__Point3d * offset = arrayLatticeOfPoints3d->Offset[1]->Offset;
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
	const resqml20__Point3dLatticeArray* const arrayLatticeOfPoints3d = getArrayLatticeOfPoints3d();

	if (arrayLatticeOfPoints3d != nullptr) {
		if (!arrayLatticeOfPoints3d->Offset.empty()) {
			return arrayLatticeOfPoints3d->Offset[0]->Spacing->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__DoubleConstantArray;
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
	const resqml20__Point3dLatticeArray* const arrayLatticeOfPoints3d = getArrayLatticeOfPoints3d();

	if (arrayLatticeOfPoints3d != nullptr) {
		if (arrayLatticeOfPoints3d->Offset.size() > 1) {
			return arrayLatticeOfPoints3d->Offset[1]->Spacing->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__DoubleConstantArray;
		}
		
		throw logic_error("This 2d grid representation does not look to have (at least) 2 dimensions.");
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

	const resqml20__Point3dLatticeArray* const arrayLatticeOfPoints3d = getArrayLatticeOfPoints3d();

	if (arrayLatticeOfPoints3d != nullptr) {
		return static_cast<resqml20__DoubleConstantArray*>(arrayLatticeOfPoints3d->Offset[0]->Spacing)->Value;
	}

	const int jIndexOffset = getIndexOffsetOnSupportingRepresentation(0);
	const double jSpacingOnSupportingRep = getSupportingRepresentation()->getJSpacing();

	return jIndexOffset * jSpacingOnSupportingRep;
}

void Grid2dRepresentation::getJSpacing(double* const jSpacings) const
{
	const resqml20__Point3dLatticeArray* const arrayLatticeOfPoints3d = getArrayLatticeOfPoints3d();

	const uint64_t jSpacingCount = getNodeCountAlongJAxis() - 1;

	if (arrayLatticeOfPoints3d != nullptr) {
		if (arrayLatticeOfPoints3d->Offset[0]->Spacing->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__DoubleConstantArray) {
			const double constantSpacing = static_cast<resqml20__DoubleConstantArray*>(arrayLatticeOfPoints3d->Offset[0]->Spacing)->Value;
			for (uint64_t j = 0; j < jSpacingCount; ++j) {
				jSpacings[j] = constantSpacing;
			}
		}
		else if (arrayLatticeOfPoints3d->Offset[0]->Spacing->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__DoubleHdf5Array) {
			eml20__Hdf5Dataset const * dataset = static_cast<resqml20__DoubleHdf5Array*>(arrayLatticeOfPoints3d->Offset[0]->Spacing)->Values;
			EML2_NS::AbstractHdfProxy * hdfProxy = getRepository()->getDataObjectByUuid<EML2_NS::AbstractHdfProxy>(dataset->HdfProxy->UUID);
			if (hdfProxy == nullptr) {
				throw logic_error("The HDF proxy is missing.");
			}
			hdfProxy->readArrayNdOfDoubleValues(dataset->PathInHdfFile, jSpacings);
		}
		else {
			throw logic_error("Not implemented yet.");
		}
	}
	else if (!getSupportingRepresentationDor().isEmpty())
	{
		const int jIndexOrigin = getIndexOriginOnSupportingRepresentation(0);
		const int jIndexOffset = getIndexOffsetOnSupportingRepresentation(0);
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

	const resqml20__Point3dLatticeArray* const arrayLatticeOfPoints3d = getArrayLatticeOfPoints3d();

	if (arrayLatticeOfPoints3d != nullptr) {
		return static_cast<resqml20__DoubleConstantArray*>(arrayLatticeOfPoints3d->Offset[1]->Spacing)->Value;
	}

	const int iIndexOffset = getIndexOffsetOnSupportingRepresentation(1);
	const double iSpacingOnSupportingRep = getSupportingRepresentation()->getISpacing();

	return iIndexOffset * iSpacingOnSupportingRep;
}

void Grid2dRepresentation::getISpacing(double* const iSpacings) const
{
	const resqml20__Point3dLatticeArray* const arrayLatticeOfPoints3d = getArrayLatticeOfPoints3d();

	const uint64_t iSpacingCount = getNodeCountAlongIAxis() - 1;

	if (arrayLatticeOfPoints3d != nullptr) {
		if (arrayLatticeOfPoints3d->Offset[1]->Spacing->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__DoubleConstantArray) {
			const double constantSpacing = static_cast<resqml20__DoubleConstantArray*>(arrayLatticeOfPoints3d->Offset[1]->Spacing)->Value;
			for (uint64_t i = 0; i < iSpacingCount; ++i) {
				iSpacings[i] = constantSpacing;
			}
		}
		else if (arrayLatticeOfPoints3d->Offset[1]->Spacing->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__DoubleHdf5Array) {
			eml20__Hdf5Dataset const * dataset = static_cast<resqml20__DoubleHdf5Array*>(arrayLatticeOfPoints3d->Offset[1]->Spacing)->Values;
			EML2_NS::AbstractHdfProxy * hdfProxy = getRepository()->getDataObjectByUuid<EML2_NS::AbstractHdfProxy>(dataset->HdfProxy->UUID);
			if (hdfProxy == nullptr) {
				throw invalid_argument("The HDF proxy is missing.");
			}
			hdfProxy->readArrayNdOfDoubleValues(dataset->PathInHdfFile, iSpacings);
		}
		else {
			throw logic_error("Not implemented yet.");
		}
	}
	else if (!getSupportingRepresentationDor().isEmpty())
	{
		const int iIndexOrigin = getIndexOriginOnSupportingRepresentation(1);
		const int iIndexOffset = getIndexOffsetOnSupportingRepresentation(1);
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
	double spacingInFastestDirection, double spacingInSlowestDirection, RESQML2_NS::AbstractLocal3dCrs * localCrs)
{
	if (localCrs == nullptr) {
		localCrs = getRepository()->getDefaultCrs();
		if (localCrs == nullptr) {
			throw std::invalid_argument("A (default) CRS must be provided.");
		}
	}

	resqml20__PointGeometry* geomPatch = createArray2dOfLatticePoints3d(numPointsInFastestDirection, numPointsInSlowestDirection,
			xOrigin, yOrigin, zOrigin,
			xOffsetInFastestDirection, yOffsetInFastestDirection, zOffsetInFastestDirection,
			xOffsetInSlowestDirection, yOffsetInSlowestDirection, zOffsetInSlowestDirection,
			spacingInFastestDirection, spacingInSlowestDirection, localCrs);

	resqml20__Grid2dPatch* patch = soap_new_resqml20__Grid2dPatch(gsoapProxy2_0_1->soap);
	patch->PatchIndex = 0;
	patch->Geometry = geomPatch;
	patch->SlowestAxisCount = numPointsInSlowestDirection;
	patch->FastestAxisCount = numPointsInFastestDirection;

	static_cast<_resqml20__Grid2dRepresentation*>(gsoapProxy2_0_1)->Grid2dPatch = patch;

	getRepository()->addRelationship(this, localCrs);
}

void Grid2dRepresentation::setGeometryAsArray2dOfExplicitZ(
	double * zValues,
	unsigned int numI, unsigned int numJ, EML2_NS::AbstractHdfProxy * proxy,
	RESQML2_NS::Grid2dRepresentation * supportingGrid2dRepresentation, RESQML2_NS::AbstractLocal3dCrs * localCrs,
	unsigned int startIndexI, unsigned int startIndexJ,
	int indexIncrementI, int indexIncrementJ)
{
	if (localCrs == nullptr) {
		localCrs = getRepository()->getDefaultCrs();
		if (localCrs == nullptr) {
			throw std::invalid_argument("A (default) CRS must be provided.");
		}
	}

	resqml20__Grid2dPatch* patch = soap_new_resqml20__Grid2dPatch(gsoapProxy2_0_1->soap);
	static_cast<_resqml20__Grid2dRepresentation*>(gsoapProxy2_0_1)->Grid2dPatch = patch;

	patch->PatchIndex = 0;
	patch->SlowestAxisCount = numJ;
	patch->FastestAxisCount = numI;

	resqml20__PointGeometry* geomPatch = createArray2dOfExplicitZ(0,
			zValues, localCrs,
			numI, numJ, proxy,
			supportingGrid2dRepresentation,
			startIndexI + startIndexJ * getNodeCountAlongIAxis(),
			indexIncrementI, indexIncrementJ);
	patch->Geometry = geomPatch;

	getRepository()->addRelationship(this, localCrs);
}

void Grid2dRepresentation::setGeometryAsArray2dOfExplicitZ(
	double * zValues,
	unsigned int numI, unsigned int numJ, EML2_NS::AbstractHdfProxy * proxy,
	double originX, double originY, double originZ,
	double offsetIX, double offsetIY, double offsetIZ, double spacingI,
	double offsetJX, double offsetJY, double offsetJZ, double spacingJ, RESQML2_NS::AbstractLocal3dCrs * localCrs)
{
	if (localCrs == nullptr) {
		localCrs = getRepository()->getDefaultCrs();
		if (localCrs == nullptr) {
			throw std::invalid_argument("A (default) CRS must be provided.");
		}
	}

	resqml20__Grid2dPatch* patch = soap_new_resqml20__Grid2dPatch(gsoapProxy2_0_1->soap);
	static_cast<_resqml20__Grid2dRepresentation*>(gsoapProxy2_0_1)->Grid2dPatch = patch;

	patch->PatchIndex = 0;
	patch->SlowestAxisCount = numJ;
	patch->FastestAxisCount = numI;

	resqml20__PointGeometry* geomPatch = createArray2dOfExplicitZ(0,
			zValues, localCrs,
			numI, numJ, proxy,
			originX, originY, originZ,
			offsetIX, offsetIY, offsetIZ, spacingI,
			offsetJX, offsetJY, offsetJZ, spacingJ);
	patch->Geometry = geomPatch;

	getRepository()->addRelationship(this, localCrs);
}

COMMON_NS::DataObjectReference Grid2dRepresentation::getSupportingRepresentationDor() const
{
	_resqml20__Grid2dRepresentation* singleGrid2dRep = static_cast<_resqml20__Grid2dRepresentation*>(gsoapProxy2_0_1);
	if (singleGrid2dRep != nullptr && singleGrid2dRep->Grid2dPatch->Geometry->Points->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__Point3dZValueArray) {
		resqml20__Point3dZValueArray* tmp = static_cast<resqml20__Point3dZValueArray*>(singleGrid2dRep->Grid2dPatch->Geometry->Points);
		if (tmp->SupportingGeometry->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__Point3dFromRepresentationLatticeArray) {
			return COMMON_NS::DataObjectReference(static_cast<resqml20__Point3dFromRepresentationLatticeArray*>(tmp->SupportingGeometry)->SupportingRepresentation);
		}
	}

	return COMMON_NS::DataObjectReference();
}

int Grid2dRepresentation::getIndexOriginOnSupportingRepresentation() const
{
	resqml20__Point3dFromRepresentationLatticeArray* geom = getPoint3dFromRepresentationLatticeArrayFromPointGeometryPatch(static_cast<_resqml20__Grid2dRepresentation*>(gsoapProxy2_0_1)->Grid2dPatch->Geometry);

	if (geom != nullptr) {
		return geom->NodeIndicesOnSupportingRepresentation->StartValue;
	}

	throw logic_error("It does not exist supporting representation for this representation.");
}

int Grid2dRepresentation::getIndexOriginOnSupportingRepresentation(unsigned int dimension) const
{
	resqml20__Point3dFromRepresentationLatticeArray* geom = getPoint3dFromRepresentationLatticeArrayFromPointGeometryPatch(static_cast<_resqml20__Grid2dRepresentation*>(gsoapProxy2_0_1)->Grid2dPatch->Geometry);

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

int Grid2dRepresentation::getNodeCountOnSupportingRepresentation(unsigned int dimension) const
{
	resqml20__Point3dFromRepresentationLatticeArray* geom = getPoint3dFromRepresentationLatticeArrayFromPointGeometryPatch(static_cast<_resqml20__Grid2dRepresentation*>(gsoapProxy2_0_1)->Grid2dPatch->Geometry);

	if (geom != nullptr) {
		if (dimension < geom->NodeIndicesOnSupportingRepresentation->Offset.size()) {
			return geom->NodeIndicesOnSupportingRepresentation->Offset[dimension]->Count + 1;
		}
		else {
			throw out_of_range("dimension is out of range.");
		}
	}
	
	throw logic_error("It does not exist supporting representation for this representation.");
}

int Grid2dRepresentation::getIndexOffsetOnSupportingRepresentation(unsigned int dimension) const
{
	resqml20__Point3dFromRepresentationLatticeArray* geom = getPoint3dFromRepresentationLatticeArrayFromPointGeometryPatch(static_cast<_resqml20__Grid2dRepresentation*>(gsoapProxy2_0_1)->Grid2dPatch->Geometry);

	if (geom != nullptr) {
		if (dimension < geom->NodeIndicesOnSupportingRepresentation->Offset.size()) {
			return geom->NodeIndicesOnSupportingRepresentation->Offset[dimension]->Value;
		}
		else {
			throw out_of_range("dimension is out of range.");
		}
	}

	throw logic_error("It does not exist supporting representation for this representation.");
}

gsoap_resqml2_0_1::resqml20__Point3dFromRepresentationLatticeArray* Grid2dRepresentation::getPoint3dFromRepresentationLatticeArrayFromPointGeometryPatch(gsoap_resqml2_0_1::resqml20__PointGeometry* patch) const
{
	if (patch != nullptr) {
		gsoap_resqml2_0_1::resqml20__Point3dFromRepresentationLatticeArray* patchOfSupportingRep = nullptr;

		if (patch->Points->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__Point3dZValueArray) {
			gsoap_resqml2_0_1::resqml20__Point3dZValueArray* zValuesPatch = static_cast<gsoap_resqml2_0_1::resqml20__Point3dZValueArray*>(patch->Points);
			if (zValuesPatch->SupportingGeometry->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__Point3dFromRepresentationLatticeArray) {
				patchOfSupportingRep = static_cast<gsoap_resqml2_0_1::resqml20__Point3dFromRepresentationLatticeArray*>(zValuesPatch->SupportingGeometry);
			}
		}
		else if (patch->Points->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__Point3dFromRepresentationLatticeArray) {
			patchOfSupportingRep = static_cast<gsoap_resqml2_0_1::resqml20__Point3dFromRepresentationLatticeArray*>(patch->Points);
		}

		return patchOfSupportingRep;
	}

	return nullptr;
}

gsoap_resqml2_0_1::resqml20__PointGeometry* Grid2dRepresentation::createArray2dOfLatticePoints3d(
	unsigned int numPointsInFastestDirection, unsigned int numPointsInSlowestDirection,
	double xOrigin, double yOrigin, double zOrigin,
	double xOffsetInFastestDirection, double yOffsetInFastestDirection, double zOffsetInFastestDirection,
	double xOffsetInSlowestDirection, double yOffsetInSlowestDirection, double zOffsetInSlowestDirection,
	double spacingInFastestDirection, double spacingInSlowestDirection, RESQML2_NS::AbstractLocal3dCrs * localCrs)
{
	if (localCrs == nullptr) {
		throw invalid_argument("The CRS cannot be the null pointer");
	}

	gsoap_resqml2_0_1::resqml20__PointGeometry* geom = gsoap_resqml2_0_1::soap_new_resqml20__PointGeometry(gsoapProxy2_0_1->soap);
	geom->LocalCrs = localCrs->newResqmlReference();

	// XML
	gsoap_resqml2_0_1::resqml20__Point3dLatticeArray* xmlPoints = gsoap_resqml2_0_1::soap_new_resqml20__Point3dLatticeArray(gsoapProxy2_0_1->soap);
	xmlPoints->Origin = gsoap_resqml2_0_1::soap_new_resqml20__Point3d(gsoapProxy2_0_1->soap);
	xmlPoints->Origin->Coordinate1 = xOrigin;
	xmlPoints->Origin->Coordinate2 = yOrigin;
	xmlPoints->Origin->Coordinate3 = zOrigin;

	// first (slowest) dim : fastest is I (or inline), slowest is J (or crossline)
	gsoap_resqml2_0_1::resqml20__Point3dOffset* latticeDim = gsoap_resqml2_0_1::soap_new_resqml20__Point3dOffset(gsoapProxy2_0_1->soap);
	latticeDim->Offset = gsoap_resqml2_0_1::soap_new_resqml20__Point3d(gsoapProxy2_0_1->soap);
	latticeDim->Offset->Coordinate1 = xOffsetInSlowestDirection;
	latticeDim->Offset->Coordinate2 = yOffsetInSlowestDirection;
	latticeDim->Offset->Coordinate3 = zOffsetInSlowestDirection;
	gsoap_resqml2_0_1::resqml20__DoubleConstantArray* spacingInfo = gsoap_resqml2_0_1::soap_new_resqml20__DoubleConstantArray(gsoapProxy2_0_1->soap);
	spacingInfo->Count = numPointsInSlowestDirection - 1;
	spacingInfo->Value = spacingInSlowestDirection;
	latticeDim->Spacing = spacingInfo;
	xmlPoints->Offset.push_back(latticeDim);

	// Second (fastest) dimension :fastest is I (or inline), slowest is J (or crossline)
	latticeDim = gsoap_resqml2_0_1::soap_new_resqml20__Point3dOffset(gsoapProxy2_0_1->soap);
	latticeDim->Offset = gsoap_resqml2_0_1::soap_new_resqml20__Point3d(gsoapProxy2_0_1->soap);
	latticeDim->Offset->Coordinate1 = xOffsetInFastestDirection;
	latticeDim->Offset->Coordinate2 = yOffsetInFastestDirection;
	latticeDim->Offset->Coordinate3 = zOffsetInFastestDirection;
	spacingInfo = gsoap_resqml2_0_1::soap_new_resqml20__DoubleConstantArray(gsoapProxy2_0_1->soap);
	spacingInfo->Count = numPointsInFastestDirection - 1;
	spacingInfo->Value = spacingInFastestDirection;
	latticeDim->Spacing = spacingInfo;
	xmlPoints->Offset.push_back(latticeDim);

	geom->Points = xmlPoints;

	return geom;
}

gsoap_resqml2_0_1::resqml20__PointGeometry* Grid2dRepresentation::createArray2dOfExplicitZ(
	unsigned int patchIndex, double * zValues, RESQML2_NS::AbstractLocal3dCrs * localCrs,
	unsigned int numI, unsigned int numJ, EML2_NS::AbstractHdfProxy * proxy,
	RESQML2_NS::Grid2dRepresentation * supportingRepresentation,
	unsigned int startGlobalIndex,
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

	gsoap_resqml2_0_1::resqml20__PointGeometry* geom = gsoap_resqml2_0_1::soap_new_resqml20__PointGeometry(gsoapProxy2_0_1->soap);
	geom->LocalCrs = localCrs->newResqmlReference();

	// XML
	gsoap_resqml2_0_1::resqml20__Point3dZValueArray* xmlPoints = gsoap_resqml2_0_1::soap_new_resqml20__Point3dZValueArray(gsoapProxy2_0_1->soap);
	gsoap_resqml2_0_1::resqml20__Point3dFromRepresentationLatticeArray* patchPoints = gsoap_resqml2_0_1::soap_new_resqml20__Point3dFromRepresentationLatticeArray(gsoapProxy2_0_1->soap);
	patchPoints->SupportingRepresentation = supportingRepresentation->newResqmlReference();
	patchPoints->NodeIndicesOnSupportingRepresentation = gsoap_resqml2_0_1::soap_new_resqml20__IntegerLatticeArray(gsoapProxy2_0_1->soap);
	patchPoints->NodeIndicesOnSupportingRepresentation->StartValue = startGlobalIndex;
	xmlPoints->SupportingGeometry = patchPoints;

	// first (slowest) dim :fastest is I (or inline), slowest is J (or crossline)
	gsoap_resqml2_0_1::resqml20__IntegerConstantArray* offset = gsoap_resqml2_0_1::soap_new_resqml20__IntegerConstantArray(gsoapProxy2_0_1->soap);
	offset->Count = numJ - 1;
	offset->Value = indexIncrementJ;
	patchPoints->NodeIndicesOnSupportingRepresentation->Offset.push_back(offset);

	//second (fastest) dim :fastest is I (or inline), slowest is J (or crossline)
	offset = gsoap_resqml2_0_1::soap_new_resqml20__IntegerConstantArray(gsoapProxy2_0_1->soap);
	offset->Count = numI - 1;
	offset->Value = indexIncrementI;
	patchPoints->NodeIndicesOnSupportingRepresentation->Offset.push_back(offset);

	// Z Values
	gsoap_resqml2_0_1::resqml20__DoubleHdf5Array* xmlZValues = gsoap_resqml2_0_1::soap_new_resqml20__DoubleHdf5Array(gsoapProxy2_0_1->soap);
	xmlZValues->Values = gsoap_resqml2_0_1::soap_new_eml20__Hdf5Dataset(gsoapProxy2_0_1->soap);
	xmlZValues->Values->HdfProxy = proxy->newResqmlReference();
	ostringstream oss3;
	oss3 << "points_patch" << patchIndex;
	xmlZValues->Values->PathInHdfFile = getHdfGroup() + "/" + oss3.str();
	xmlPoints->ZValues = xmlZValues;

	// HDF
	hsize_t dim[2] = { numJ, numI };
	proxy->writeArrayNdOfDoubleValues(getHdfGroup(),
		oss3.str(),
		zValues,
		dim, 2);

	geom->Points = xmlPoints;

	return geom;
}

gsoap_resqml2_0_1::resqml20__PointGeometry* Grid2dRepresentation::createArray2dOfExplicitZ(
	unsigned int patchIndex, double * zValues, RESQML2_NS::AbstractLocal3dCrs * localCrs,
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

	gsoap_resqml2_0_1::resqml20__PointGeometry* geom = gsoap_resqml2_0_1::soap_new_resqml20__PointGeometry(gsoapProxy2_0_1->soap);
	geom->LocalCrs = localCrs->newResqmlReference();

	// XML
	gsoap_resqml2_0_1::resqml20__Point3dZValueArray* xmlPoints = gsoap_resqml2_0_1::soap_new_resqml20__Point3dZValueArray(gsoapProxy2_0_1->soap);
	gsoap_resqml2_0_1::resqml20__Point3dLatticeArray* latticePoints = gsoap_resqml2_0_1::soap_new_resqml20__Point3dLatticeArray(gsoapProxy2_0_1->soap);
	latticePoints->Origin = gsoap_resqml2_0_1::soap_new_resqml20__Point3d(gsoapProxy2_0_1->soap);
	latticePoints->Origin->Coordinate1 = originX;
	latticePoints->Origin->Coordinate2 = originY;
	latticePoints->Origin->Coordinate3 = originZ;

	// first (slowest) dim :fastest is I (or inline), slowest is J (or crossline)
	gsoap_resqml2_0_1::resqml20__Point3dOffset* latticeDimForJ = gsoap_resqml2_0_1::soap_new_resqml20__Point3dOffset(gsoapProxy2_0_1->soap);
	latticeDimForJ->Offset = gsoap_resqml2_0_1::soap_new_resqml20__Point3d(gsoapProxy2_0_1->soap);
	latticeDimForJ->Offset->Coordinate1 = offsetJX;
	latticeDimForJ->Offset->Coordinate2 = offsetJY;
	latticeDimForJ->Offset->Coordinate3 = offsetJZ;
	gsoap_resqml2_0_1::resqml20__DoubleConstantArray* spacingForJ = gsoap_resqml2_0_1::soap_new_resqml20__DoubleConstantArray(gsoapProxy2_0_1->soap);
	spacingForJ->Value = spacingJ;
	spacingForJ->Count = numJ - 1;
	latticeDimForJ->Spacing = spacingForJ;
	latticePoints->Offset.push_back(latticeDimForJ);

	//second (fastest) dim :fastest is I (or inline), slowest is J (or crossline)
	gsoap_resqml2_0_1::resqml20__Point3dOffset* latticeDimForI = gsoap_resqml2_0_1::soap_new_resqml20__Point3dOffset(gsoapProxy2_0_1->soap);
	latticeDimForI->Offset = gsoap_resqml2_0_1::soap_new_resqml20__Point3d(gsoapProxy2_0_1->soap);
	latticeDimForI->Offset->Coordinate1 = offsetIX;
	latticeDimForI->Offset->Coordinate2 = offsetIY;
	latticeDimForI->Offset->Coordinate3 = offsetIZ;
	gsoap_resqml2_0_1::resqml20__DoubleConstantArray* spacingForI = gsoap_resqml2_0_1::soap_new_resqml20__DoubleConstantArray(gsoapProxy2_0_1->soap);
	spacingForI->Value = spacingI;
	spacingForI->Count = numI - 1;
	latticeDimForI->Spacing = spacingForI;
	latticePoints->Offset.push_back(latticeDimForI);

	xmlPoints->SupportingGeometry = latticePoints;

	// Z Values
	gsoap_resqml2_0_1::resqml20__DoubleHdf5Array* xmlZValues = gsoap_resqml2_0_1::soap_new_resqml20__DoubleHdf5Array(gsoapProxy2_0_1->soap);
	xmlZValues->Values = gsoap_resqml2_0_1::soap_new_eml20__Hdf5Dataset(gsoapProxy2_0_1->soap);
	xmlZValues->Values->HdfProxy = proxy->newResqmlReference();
	ostringstream oss3;
	oss3 << "points_patch" << patchIndex;
	xmlZValues->Values->PathInHdfFile = getHdfGroup() + "/" + oss3.str();
	xmlPoints->ZValues = xmlZValues;

	// HDF
	hsize_t dim[2] = { numJ, numI };
	proxy->writeArrayNdOfDoubleValues(getHdfGroup(),
		oss3.str(),
		zValues,
		dim, 2);

	geom->Points = xmlPoints;

	return geom;
}
