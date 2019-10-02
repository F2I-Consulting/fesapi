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

#include "resqml2_0_1/IjkGridLatticeRepresentation.h"

#include <stdexcept>

#include "resqml2/AbstractFeature.h"
#include "resqml2/AbstractFeatureInterpretation.h"
#include "resqml2/AbstractLocal3dCrs.h"
#include "resqml2/AbstractValuesProperty.h"
#include "common/AbstractHdfProxy.h"

using namespace std;
using namespace gsoap_resqml2_0_1;
using namespace RESQML2_0_1_NS;

IjkGridLatticeRepresentation::IjkGridLatticeRepresentation(COMMON_NS::DataObjectRepository * repo,
	const std::string & guid, const std::string & title,
	unsigned int iCount, unsigned int jCount, unsigned int kCount):
	AbstractIjkGridRepresentation(repo, guid, title, iCount, jCount, kCount)
{
}

IjkGridLatticeRepresentation::IjkGridLatticeRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp,
	const std::string & guid, const std::string & title,
	unsigned int iCount, unsigned int jCount, unsigned int kCount):
	AbstractIjkGridRepresentation(interp, guid, title, iCount, jCount, kCount)
{
}

bool IjkGridLatticeRepresentation::isASeismicCube() const
{
	// A Seismic cube is defined by an IjkGridRepresentation that has a feature of type SeismicLatticeFeature and that
	// has at least one continuous property (amplitude).
	bool atLeastOneContProp = false;
	vector<RESQML2_NS::AbstractValuesProperty *> allValuesProperty = getValuesPropertySet();
    for (size_t propIndex = 0; propIndex < allValuesProperty.size(); ++propIndex)
    {
        if (allValuesProperty[propIndex]->getGsoapType() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__obj_USCOREContinuousProperty)
        {
            atLeastOneContProp = true;
            break;
        }
    }
    if (!atLeastOneContProp)
        return false;

    return getInterpretation() && getInterpretation()->getInterpretedFeature()->getGsoapType() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__obj_USCORESeismicLatticeFeature;
}

bool IjkGridLatticeRepresentation::isAFaciesCube() const
{
	// A Facies cube is defined by an IjkGridRepresentation that has a feature of type SeismicLatticeFeature and that
	// has at least one categorical property (facies).
	bool atLeastOneCateProp = false;
	vector<RESQML2_NS::AbstractValuesProperty *> allValuesProperty = getValuesPropertySet();
    for (size_t propIndex = 0; propIndex < allValuesProperty.size(); ++propIndex)
    {
        if (allValuesProperty[propIndex]->getGsoapType() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__obj_USCORECategoricalProperty)
        {
            atLeastOneCateProp = true;
            break;
        }
    }
    if (!atLeastOneCateProp)
        return false;

    return getInterpretation() && getInterpretation()->getInterpretedFeature()->getGsoapType() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__obj_USCORESeismicLatticeFeature;
}

gsoap_resqml2_0_1::eml20__DataObjectReference* IjkGridLatticeRepresentation::getHdfProxyDor() const
{
	return getHdfProxyDorFromPointGeometryPatch(getPointGeometry2_0_1(0));
}

ULONG64 IjkGridLatticeRepresentation::getXyzPointCountOfPatch(const unsigned int & patchIndex) const
{
	if (patchIndex < getPatchCount())
	{
		return (getICellCount()+1) * (getJCellCount()+1) * (getKCellCount()+1);
	}
	else
		throw range_error("An ijk grid has a maximum of one patch.");
}

void IjkGridLatticeRepresentation::getXyzPointsOfPatch(const unsigned int & patchIndex, double *) const
{
	if (patchIndex < getPatchCount())
	{
		throw logic_error("Not yet implemented. Please use lattice information.");
	}
	else
		throw range_error("An ijk grid has a maximum of one patch.");
}

resqml20__Point3dLatticeArray* IjkGridLatticeRepresentation::getArrayLatticeOfPoints3d() const
{
    resqml20__Point3dLatticeArray* result = nullptr;

    resqml20__PointGeometry* ptGeom = getPointGeometry2_0_1(0);
    if (ptGeom->Points->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__Point3dLatticeArray)
    {
        result = static_cast<resqml20__Point3dLatticeArray*>(ptGeom->Points);
    }

    return result;
}

double IjkGridLatticeRepresentation::getXOrigin() const
{
	resqml20__Point3dLatticeArray* arrayLatticeOfPoint3d = getArrayLatticeOfPoints3d();
	if (arrayLatticeOfPoint3d)
		return arrayLatticeOfPoint3d->Origin->Coordinate1;
	else
		return std::numeric_limits<double>::signaling_NaN();
}

double IjkGridLatticeRepresentation::getXOriginInGlobalCrs() const
{
	double result[] = {getXOrigin(), getYOrigin(), .0};
	if (result[0] != result[0])
		return result[0];

	// Only one patch is allowed for an IJK Grid lattice
	getLocalCrs(0)->convertXyzPointsToGlobalCrs(result, 1);

	return result[0];
}

double IjkGridLatticeRepresentation::getYOrigin() const
{
	resqml20__Point3dLatticeArray* arrayLatticeOfPoint3d = getArrayLatticeOfPoints3d();
	if (arrayLatticeOfPoint3d)
		return arrayLatticeOfPoint3d->Origin->Coordinate2;
	else
		return std::numeric_limits<double>::signaling_NaN();
}

double IjkGridLatticeRepresentation::getYOriginInGlobalCrs() const
{
	double result[] = {getXOrigin(), getYOrigin(), .0};
	if (result[0] != result[0])
		return result[0];

	// Only one patch is allowed for an IJK Grid lattice
	getLocalCrs(0)->convertXyzPointsToGlobalCrs(result, 1);

	return result[1];
}

double IjkGridLatticeRepresentation::getZOrigin() const
{
	resqml20__Point3dLatticeArray* arrayLatticeOfPoint3d = getArrayLatticeOfPoints3d();
	if (arrayLatticeOfPoint3d)
		return arrayLatticeOfPoint3d->Origin->Coordinate3;
	else
		return std::numeric_limits<double>::signaling_NaN();
}

double IjkGridLatticeRepresentation::getZOriginInGlobalCrs() const
{
	double result = getZOrigin();
	if (result != result) {
		return result;
	}
	// Only one patch is allowed for an IJK Grid lattice
	RESQML2_NS::AbstractLocal3dCrs const * localCrs = getLocalCrs(0);
	if (localCrs->getGsoapType() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__obj_USCORELocalTime3dCrs) {
		return result;
	}

	return result + localCrs->getOriginDepthOrElevation();
}

double IjkGridLatticeRepresentation::getXIOffset() const
{
	resqml20__Point3dLatticeArray* arrayLatticeOfPoint3d = getArrayLatticeOfPoints3d();
	if (arrayLatticeOfPoint3d)
		return arrayLatticeOfPoint3d->Offset[0]->Offset->Coordinate1;
	else
		return std::numeric_limits<double>::signaling_NaN();
}

double IjkGridLatticeRepresentation::getYIOffset() const
{
    resqml20__Point3dLatticeArray* arrayLatticeOfPoint3d = getArrayLatticeOfPoints3d();
	if (arrayLatticeOfPoint3d)
		return arrayLatticeOfPoint3d->Offset[0]->Offset->Coordinate2;
	else
		return std::numeric_limits<double>::signaling_NaN();
}

double IjkGridLatticeRepresentation::getZIOffset() const
{
	resqml20__Point3dLatticeArray* arrayLatticeOfPoint3d = getArrayLatticeOfPoints3d();
	if (arrayLatticeOfPoint3d)
		return arrayLatticeOfPoint3d->Offset[0]->Offset->Coordinate3;
	else
		return std::numeric_limits<double>::signaling_NaN();
}

double IjkGridLatticeRepresentation::getXJOffset() const
{
	resqml20__Point3dLatticeArray* arrayLatticeOfPoint3d = getArrayLatticeOfPoints3d();
	if (arrayLatticeOfPoint3d)
		return arrayLatticeOfPoint3d->Offset[1]->Offset->Coordinate1;
	else
		return std::numeric_limits<double>::signaling_NaN();
}

double IjkGridLatticeRepresentation::getYJOffset() const
{
	resqml20__Point3dLatticeArray* arrayLatticeOfPoint3d = getArrayLatticeOfPoints3d();
	if (arrayLatticeOfPoint3d)
		return arrayLatticeOfPoint3d->Offset[1]->Offset->Coordinate2;
	else
		return std::numeric_limits<double>::signaling_NaN();
}

double IjkGridLatticeRepresentation::getZJOffset() const
{
	resqml20__Point3dLatticeArray* arrayLatticeOfPoint3d = getArrayLatticeOfPoints3d();
	if (arrayLatticeOfPoint3d)
		return arrayLatticeOfPoint3d->Offset[1]->Offset->Coordinate3;
	else
		return std::numeric_limits<double>::signaling_NaN();
}

double IjkGridLatticeRepresentation::getXKOffset() const
{
	resqml20__Point3dLatticeArray* arrayLatticeOfPoint3d = getArrayLatticeOfPoints3d();
	if (arrayLatticeOfPoint3d)
		return arrayLatticeOfPoint3d->Offset[2]->Offset->Coordinate1;
	else
		return std::numeric_limits<double>::signaling_NaN();
}

double IjkGridLatticeRepresentation::getYKOffset() const
{
	resqml20__Point3dLatticeArray* arrayLatticeOfPoint3d = getArrayLatticeOfPoints3d();
	if (arrayLatticeOfPoint3d)
		return arrayLatticeOfPoint3d->Offset[2]->Offset->Coordinate2;
	else
		return std::numeric_limits<double>::signaling_NaN();
}

double IjkGridLatticeRepresentation::getZKOffset() const
{
	resqml20__Point3dLatticeArray* arrayLatticeOfPoint3d = getArrayLatticeOfPoints3d();
	if (arrayLatticeOfPoint3d)
		return arrayLatticeOfPoint3d->Offset[2]->Offset->Coordinate3;
	else
		return std::numeric_limits<double>::signaling_NaN();
}

double IjkGridLatticeRepresentation::getISpacing() const
{
    resqml20__Point3dLatticeArray* arrayLatticeOfPoints3d = getArrayLatticeOfPoints3d();

    if (arrayLatticeOfPoints3d && arrayLatticeOfPoints3d->Offset[0]->Spacing->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__DoubleConstantArray)
        return static_cast<resqml20__DoubleConstantArray*>(arrayLatticeOfPoints3d->Offset[0]->Spacing)->Value;
    else
        return std::numeric_limits<double>::signaling_NaN();
}

double IjkGridLatticeRepresentation::getJSpacing() const
{
	resqml20__Point3dLatticeArray* arrayLatticeOfPoints3d = getArrayLatticeOfPoints3d();

    if (arrayLatticeOfPoints3d && arrayLatticeOfPoints3d->Offset[1]->Spacing->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__DoubleConstantArray)
        return static_cast<resqml20__DoubleConstantArray*>(arrayLatticeOfPoints3d->Offset[1]->Spacing)->Value;
    else
        return std::numeric_limits<double>::signaling_NaN();
}

double IjkGridLatticeRepresentation::getKSpacing() const
{
	resqml20__Point3dLatticeArray* arrayLatticeOfPoints3d = getArrayLatticeOfPoints3d();

    if (arrayLatticeOfPoints3d && arrayLatticeOfPoints3d->Offset[2]->Spacing->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__DoubleConstantArray)
        return static_cast<resqml20__DoubleConstantArray*>(arrayLatticeOfPoints3d->Offset[2]->Spacing)->Value;
    else
        return std::numeric_limits<double>::signaling_NaN();
}

int IjkGridLatticeRepresentation::getOriginInline() const
{
	resqml20__Seismic3dCoordinates* s3c = getSeismic3dCoordinates(0);

	if (s3c && s3c->InlineCoordinates->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__DoubleLatticeArray)
		return (int)static_cast<resqml20__DoubleLatticeArray*>(s3c->InlineCoordinates)->StartValue;
	else
		return 0;
}

int IjkGridLatticeRepresentation::getOriginCrossline() const
{
	resqml20__Seismic3dCoordinates* s3c = getSeismic3dCoordinates(0);

	if (s3c && s3c->CrosslineCoordinates->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__DoubleLatticeArray)
		return (int)static_cast<resqml20__DoubleLatticeArray*>(s3c->CrosslineCoordinates)->StartValue;
	else
		return 0;
}

int IjkGridLatticeRepresentation::getInlineIOffset() const
{
	resqml20__Seismic3dCoordinates* s3c = getSeismic3dCoordinates(0);

	if (s3c && s3c->InlineCoordinates->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__DoubleLatticeArray)
	{
		resqml20__DoubleLatticeArray* dla = static_cast<resqml20__DoubleLatticeArray*>(s3c->InlineCoordinates);
	    if (dla && dla->Offset[0]->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__DoubleConstantArray)
		{
			return (int)static_cast<resqml20__DoubleConstantArray*>(dla->Offset[0])->Value;
		}
	}

	return 0;
}

int IjkGridLatticeRepresentation::getInlineJOffset() const
{
	resqml20__Seismic3dCoordinates* s3c = getSeismic3dCoordinates(0);

	if (s3c && s3c->InlineCoordinates->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__DoubleLatticeArray)
	{
		resqml20__DoubleLatticeArray* dla = static_cast<resqml20__DoubleLatticeArray*>(s3c->InlineCoordinates);
	    if (dla && dla->Offset[1]->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__DoubleConstantArray)
		{
			return (int)static_cast<resqml20__DoubleConstantArray*>(dla->Offset[1])->Value;
		}
	}

	return 0;
}

int IjkGridLatticeRepresentation::getInlineKOffset() const
{
	resqml20__Seismic3dCoordinates* s3c = getSeismic3dCoordinates(0);

	if (s3c && s3c->InlineCoordinates->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__DoubleLatticeArray)
	{
		resqml20__DoubleLatticeArray* dla = static_cast<resqml20__DoubleLatticeArray*>(s3c->InlineCoordinates);
	    if (dla && dla->Offset[2]->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__DoubleConstantArray)
		{
			return (int)static_cast<resqml20__DoubleConstantArray*>(dla->Offset[2])->Value;
		}
	}

	return 0;
}

int IjkGridLatticeRepresentation::getCrosslineIOffset() const
{
	resqml20__Seismic3dCoordinates* s3c = getSeismic3dCoordinates(0);

	if (s3c && s3c->CrosslineCoordinates->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__DoubleLatticeArray)
	{
		resqml20__DoubleLatticeArray* dla = static_cast<resqml20__DoubleLatticeArray*>(s3c->CrosslineCoordinates);
	    if (dla && dla->Offset[0]->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__DoubleConstantArray)
		{
			return (int)static_cast<resqml20__DoubleConstantArray*>(dla->Offset[0])->Value;
		}
	}

	return 0;
}

int IjkGridLatticeRepresentation::getCrosslineJOffset() const
{
	resqml20__Seismic3dCoordinates* s3c = getSeismic3dCoordinates(0);

	if (s3c && s3c->CrosslineCoordinates->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__DoubleLatticeArray)
	{
		resqml20__DoubleLatticeArray* dla = static_cast<resqml20__DoubleLatticeArray*>(s3c->CrosslineCoordinates);
	    if (dla && dla->Offset[1]->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__DoubleConstantArray)
		{
			return (int)static_cast<resqml20__DoubleConstantArray*>(dla->Offset[1])->Value;
		}
	}

	return 0;
}

int IjkGridLatticeRepresentation::getCrosslineKOffset() const
{
	resqml20__Seismic3dCoordinates* s3c = getSeismic3dCoordinates(0);

	if (s3c && s3c->CrosslineCoordinates->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__DoubleLatticeArray)
	{
		resqml20__DoubleLatticeArray* dla = static_cast<resqml20__DoubleLatticeArray*>(s3c->CrosslineCoordinates);
	    if (dla && dla->Offset[2]->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__DoubleConstantArray)
		{
			return (int)static_cast<resqml20__DoubleConstantArray*>(dla->Offset[2])->Value;
		}
	}

	return 0;
}

void IjkGridLatticeRepresentation::setGeometryAsCoordinateLineNodes(
	resqml20__PillarShape mostComplexPillarGeometry,
	resqml20__KDirection kDirectionKind,
	bool isRightHanded,
	double originX, double originY, double originZ,
	double directionIX, double directionIY, double directionIZ, double spacingI,
	double directionJX, double directionJY, double directionJZ, double spacingJ,
	double directionKX, double directionKY, double directionKZ, double spacingK, RESQML2_NS::AbstractLocal3dCrs * localCrs)
{
	if (localCrs == nullptr) {
		localCrs = getRepository()->getDefaultCrs();
	}

	resqml20__IjkGridGeometry* geom = soap_new_resqml20__IjkGridGeometry(gsoapProxy2_0_1->soap);
	geom->LocalCrs = localCrs->newResqmlReference();
	if (!isTruncated()) {
		getSpecializedGsoapProxy()->Geometry = geom;
	}
	else {
		getSpecializedTruncatedGsoapProxy()->Geometry = geom;
	}
	geom->GridIsRighthanded = isRightHanded;
	geom->PillarShape = mostComplexPillarGeometry;
	geom->KDirection = kDirectionKind;

	// Pillar defined
	resqml20__BooleanConstantArray* definedPillars = soap_new_resqml20__BooleanConstantArray(gsoapProxy2_0_1->soap);
	geom->PillarGeometryIsDefined = definedPillars;
	definedPillars->Count = (getICellCount() + 1) * (getJCellCount() + 1);
	definedPillars->Value = true;

	// XML coordinate lines
	resqml20__Point3dLatticeArray* xmlPoints = soap_new_resqml20__Point3dLatticeArray(gsoapProxy2_0_1->soap);
	geom->Points = xmlPoints;

	xmlPoints->AllDimensionsAreOrthogonal = (bool*)soap_malloc(gsoapProxy2_0_1->soap, sizeof(bool));
	*xmlPoints->AllDimensionsAreOrthogonal = true;
	xmlPoints->Origin = soap_new_resqml20__Point3d(gsoapProxy2_0_1->soap);
	xmlPoints->Origin->Coordinate1 = originX;
	xmlPoints->Origin->Coordinate2 = originY;
	xmlPoints->Origin->Coordinate3 = originZ;

	// slowest axis to fastest axis so k,j,i 
	resqml20__Point3dOffset * dimK = soap_new_resqml20__Point3dOffset (gsoapProxy2_0_1->soap);
	xmlPoints->Offset.push_back(dimK);
	// the dimension is the index of the axis in the collection. here we start from 0 and goes up by 1
	dimK->Offset = soap_new_resqml20__Point3d(gsoapProxy2_0_1->soap);
	dimK->Offset->Coordinate1 = directionKX;
	dimK->Offset->Coordinate2 = directionKY;
	dimK->Offset->Coordinate3 = directionKZ;
	resqml20__DoubleConstantArray * xmlSpacingK = soap_new_resqml20__DoubleConstantArray(gsoapProxy2_0_1->soap);
	dimK->Spacing = xmlSpacingK;
	xmlSpacingK->Count = getKCellCount(); // number of cells on K axis
	xmlSpacingK->Value = spacingK;
	
	resqml20__Point3dOffset * dimJ = soap_new_resqml20__Point3dOffset (gsoapProxy2_0_1->soap);
	xmlPoints->Offset.push_back(dimJ);
	// the dimension is the index of the axis in the collection
	dimJ->Offset = soap_new_resqml20__Point3d(gsoapProxy2_0_1->soap);
	dimJ->Offset->Coordinate1 = directionJX;
	dimJ->Offset->Coordinate2 = directionJY;
	dimJ->Offset->Coordinate3 = directionJZ;
	resqml20__DoubleConstantArray * xmlSpacingJ = soap_new_resqml20__DoubleConstantArray(gsoapProxy2_0_1->soap);
	dimJ->Spacing = xmlSpacingJ;
	xmlSpacingJ->Count = getJCellCount(); // number of cells on J axis
	xmlSpacingJ->Value = spacingJ;

	resqml20__Point3dOffset * dimI = soap_new_resqml20__Point3dOffset (gsoapProxy2_0_1->soap);
	xmlPoints->Offset.push_back(dimI);
	// the dimension is the index of the axis in the collection
	dimI->Offset = soap_new_resqml20__Point3d(gsoapProxy2_0_1->soap);
	dimI->Offset->Coordinate1 = directionIX;
	dimI->Offset->Coordinate2 = directionIY;
	dimI->Offset->Coordinate3 = directionIZ;
	resqml20__DoubleConstantArray * xmlSpacingI = soap_new_resqml20__DoubleConstantArray(gsoapProxy2_0_1->soap);
	dimI->Spacing = xmlSpacingI;
	xmlSpacingI->Count = getICellCount(); // number of cells on I axis
	xmlSpacingI->Value = spacingI;

	getRepository()->addRelationship(this, localCrs);
}

void IjkGridLatticeRepresentation::addSeismic3dCoordinatesToPatch(
	unsigned int patchIndex,
	double startInline, double incrInline, unsigned int countInline,
	double startCrossline, double incrCrossline, unsigned int countCrossline,
	unsigned int countSample, RESQML2_NS::AbstractRepresentation * seismicSupport)
{
	resqml20__PointGeometry* geom = getPointGeometry2_0_1(patchIndex);
	if (geom == nullptr)
		throw invalid_argument("The patchIndex does not identify a point geometry.");

	if (geom->SeismicCoordinates == nullptr)
		geom->SeismicCoordinates = soap_new_resqml20__Seismic3dCoordinates(gsoapProxy2_0_1->soap);
	else if (geom->SeismicCoordinates->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__Seismic2dCoordinates)
		throw invalid_argument("It already exists some seismic 2d coordinates for this patch.");
	resqml20__Seismic3dCoordinates* patch = static_cast<resqml20__Seismic3dCoordinates*>(geom->SeismicCoordinates);

	patch->SeismicSupport = seismicSupport->newResqmlReference();
	getRepository()->addRelationship(this, seismicSupport);

	// inlines XML
	resqml20__DoubleLatticeArray* inlineValues = soap_new_resqml20__DoubleLatticeArray(gsoapProxy2_0_1->soap);
	inlineValues->StartValue = startInline;

	resqml20__DoubleConstantArray * IoffsetInline = soap_new_resqml20__DoubleConstantArray(gsoapProxy2_0_1->soap);
	IoffsetInline->Count = countInline - 1;
	IoffsetInline->Value = incrInline;
	inlineValues->Offset.push_back(IoffsetInline);

	resqml20__DoubleConstantArray * IoffsetCrossline = soap_new_resqml20__DoubleConstantArray(gsoapProxy2_0_1->soap);
	IoffsetCrossline->Count = countCrossline -1;
	IoffsetCrossline->Value = 0;
	inlineValues->Offset.push_back(IoffsetCrossline);

	resqml20__DoubleConstantArray * IoffsetSample = soap_new_resqml20__DoubleConstantArray(gsoapProxy2_0_1->soap);
	IoffsetSample->Count = countSample -1;
	IoffsetSample->Value = 0;
	inlineValues->Offset.push_back(IoffsetSample);

	patch->InlineCoordinates = inlineValues;

	// crosslines XML
	resqml20__DoubleLatticeArray* crosslineValues = soap_new_resqml20__DoubleLatticeArray(gsoapProxy2_0_1->soap);
	crosslineValues->StartValue = startCrossline;

	resqml20__DoubleConstantArray * CoffsetInline = soap_new_resqml20__DoubleConstantArray(gsoapProxy2_0_1->soap);
	CoffsetInline->Count = countInline - 1;
	CoffsetInline->Value = 0;
	crosslineValues->Offset.push_back(CoffsetInline);
	resqml20__DoubleConstantArray * CoffsetCrossline = soap_new_resqml20__DoubleConstantArray(gsoapProxy2_0_1->soap);
	CoffsetCrossline->Count = countCrossline - 1;
	CoffsetCrossline->Value = incrCrossline;
	crosslineValues->Offset.push_back(CoffsetCrossline);
	resqml20__DoubleConstantArray * CoffsetSample = soap_new_resqml20__DoubleConstantArray(gsoapProxy2_0_1->soap);
	CoffsetSample->Count = countSample - 1;
	CoffsetSample->Value = 0;
	crosslineValues->Offset.push_back(CoffsetSample);

	patch->CrosslineCoordinates = crosslineValues;
}

AbstractIjkGridRepresentation::geometryKind IjkGridLatticeRepresentation::getGeometryKind() const
{
	return LATTICE;
}
