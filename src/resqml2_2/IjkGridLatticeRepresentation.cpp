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
#include "IjkGridLatticeRepresentation.h"

#include <limits>
#include <stdexcept>

#include "../resqml2/AbstractFeature.h"
#include "../resqml2/AbstractFeatureInterpretation.h"
#include "../resqml2/AbstractLocal3dCrs.h"
#include "../resqml2/AbstractValuesProperty.h"
#include "../eml2/AbstractHdfProxy.h"

using namespace std;
using namespace gsoap_eml2_3;
using namespace RESQML2_2_NS;

COMMON_NS::DataObjectReference IjkGridLatticeRepresentation::getHdfProxyDor() const
{
	return getHdfProxyDorFromPointGeometryPatch(getPointGeometry2_2(0));
}

gsoap_eml2_3::resqml22__Point3dLatticeArray* IjkGridLatticeRepresentation::getArrayLatticeOfPoints3d() const
{
	auto ptGeom = getPointGeometry2_2(0);
    return ptGeom->Points->soap_type() == SOAP_TYPE_gsoap_eml2_3_resqml22__Point3dLatticeArray
		? static_cast<resqml22__Point3dLatticeArray*>(ptGeom->Points)
		: nullptr;
}

double IjkGridLatticeRepresentation::getXOrigin() const
{
	resqml22__Point3dLatticeArray* arrayLatticeOfPoint3d = getArrayLatticeOfPoints3d();
	if (arrayLatticeOfPoint3d)
		return arrayLatticeOfPoint3d->Origin->Coordinate1;
	else
		return std::numeric_limits<double>::signaling_NaN();
}

double IjkGridLatticeRepresentation::getYOrigin() const
{
	resqml22__Point3dLatticeArray* arrayLatticeOfPoint3d = getArrayLatticeOfPoints3d();
	if (arrayLatticeOfPoint3d)
		return arrayLatticeOfPoint3d->Origin->Coordinate2;
	else
		return std::numeric_limits<double>::signaling_NaN();
}

double IjkGridLatticeRepresentation::getZOrigin() const
{
	resqml22__Point3dLatticeArray* arrayLatticeOfPoint3d = getArrayLatticeOfPoints3d();
	if (arrayLatticeOfPoint3d)
		return arrayLatticeOfPoint3d->Origin->Coordinate3;
	else
		return std::numeric_limits<double>::signaling_NaN();
}

double IjkGridLatticeRepresentation::getXIOffset() const
{
	resqml22__Point3dLatticeArray* arrayLatticeOfPoint3d = getArrayLatticeOfPoints3d();
	if (arrayLatticeOfPoint3d)
		return arrayLatticeOfPoint3d->Dimension[0]->Direction->Coordinate1;
	else
		return std::numeric_limits<double>::signaling_NaN();
}

double IjkGridLatticeRepresentation::getYIOffset() const
{
    resqml22__Point3dLatticeArray* arrayLatticeOfPoint3d = getArrayLatticeOfPoints3d();
	if (arrayLatticeOfPoint3d)
		return arrayLatticeOfPoint3d->Dimension[0]->Direction->Coordinate2;
	else
		return std::numeric_limits<double>::signaling_NaN();
}

double IjkGridLatticeRepresentation::getZIOffset() const
{
	resqml22__Point3dLatticeArray* arrayLatticeOfPoint3d = getArrayLatticeOfPoints3d();
	if (arrayLatticeOfPoint3d)
		return arrayLatticeOfPoint3d->Dimension[0]->Direction->Coordinate3;
	else
		return std::numeric_limits<double>::signaling_NaN();
}

double IjkGridLatticeRepresentation::getXJOffset() const
{
	resqml22__Point3dLatticeArray* arrayLatticeOfPoint3d = getArrayLatticeOfPoints3d();
	if (arrayLatticeOfPoint3d)
		return arrayLatticeOfPoint3d->Dimension[1]->Direction->Coordinate1;
	else
		return std::numeric_limits<double>::signaling_NaN();
}

double IjkGridLatticeRepresentation::getYJOffset() const
{
	resqml22__Point3dLatticeArray* arrayLatticeOfPoint3d = getArrayLatticeOfPoints3d();
	if (arrayLatticeOfPoint3d)
		return arrayLatticeOfPoint3d->Dimension[1]->Direction->Coordinate2;
	else
		return std::numeric_limits<double>::signaling_NaN();
}

double IjkGridLatticeRepresentation::getZJOffset() const
{
	resqml22__Point3dLatticeArray* arrayLatticeOfPoint3d = getArrayLatticeOfPoints3d();
	if (arrayLatticeOfPoint3d)
		return arrayLatticeOfPoint3d->Dimension[1]->Direction->Coordinate3;
	else
		return std::numeric_limits<double>::signaling_NaN();
}

double IjkGridLatticeRepresentation::getXKOffset() const
{
	resqml22__Point3dLatticeArray* arrayLatticeOfPoint3d = getArrayLatticeOfPoints3d();
	if (arrayLatticeOfPoint3d)
		return arrayLatticeOfPoint3d->Dimension[2]->Direction->Coordinate1;
	else
		return std::numeric_limits<double>::signaling_NaN();
}

double IjkGridLatticeRepresentation::getYKOffset() const
{
	resqml22__Point3dLatticeArray* arrayLatticeOfPoint3d = getArrayLatticeOfPoints3d();
	if (arrayLatticeOfPoint3d)
		return arrayLatticeOfPoint3d->Dimension[2]->Direction->Coordinate2;
	else
		return std::numeric_limits<double>::signaling_NaN();
}

double IjkGridLatticeRepresentation::getZKOffset() const
{
	resqml22__Point3dLatticeArray* arrayLatticeOfPoint3d = getArrayLatticeOfPoints3d();
	if (arrayLatticeOfPoint3d)
		return arrayLatticeOfPoint3d->Dimension[2]->Direction->Coordinate3;
	else
		return std::numeric_limits<double>::signaling_NaN();
}

double IjkGridLatticeRepresentation::getISpacing() const
{
    resqml22__Point3dLatticeArray* arrayLatticeOfPoints3d = getArrayLatticeOfPoints3d();

    if (arrayLatticeOfPoints3d && arrayLatticeOfPoints3d->Dimension[0]->Spacing->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__FloatingPointConstantArray)
        return static_cast<eml23__FloatingPointConstantArray*>(arrayLatticeOfPoints3d->Dimension[0]->Spacing)->Value;
    else
        return std::numeric_limits<double>::signaling_NaN();
}

double IjkGridLatticeRepresentation::getJSpacing() const
{
	resqml22__Point3dLatticeArray* arrayLatticeOfPoints3d = getArrayLatticeOfPoints3d();

    if (arrayLatticeOfPoints3d && arrayLatticeOfPoints3d->Dimension[1]->Spacing->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__FloatingPointConstantArray)
        return static_cast<eml23__FloatingPointConstantArray*>(arrayLatticeOfPoints3d->Dimension[1]->Spacing)->Value;
    else
        return std::numeric_limits<double>::signaling_NaN();
}

double IjkGridLatticeRepresentation::getKSpacing() const
{
	resqml22__Point3dLatticeArray* arrayLatticeOfPoints3d = getArrayLatticeOfPoints3d();

    if (arrayLatticeOfPoints3d && arrayLatticeOfPoints3d->Dimension[2]->Spacing->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__FloatingPointConstantArray)
        return static_cast<eml23__FloatingPointConstantArray*>(arrayLatticeOfPoints3d->Dimension[2]->Spacing)->Value;
    else
        return std::numeric_limits<double>::signaling_NaN();
}

int IjkGridLatticeRepresentation::getOriginInline() const
{
	resqml22__Seismic3dCoordinates* s3c = getSeismic3dCoordinates2_2(0);

	if (s3c && s3c->InlineCoordinates->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__FloatingPointLatticeArray)
		return (int)static_cast<eml23__FloatingPointLatticeArray*>(s3c->InlineCoordinates)->StartValue;
	else
		return 0;
}

int IjkGridLatticeRepresentation::getOriginCrossline() const
{
	resqml22__Seismic3dCoordinates* s3c = getSeismic3dCoordinates2_2(0);

	if (s3c && s3c->CrosslineCoordinates->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__FloatingPointLatticeArray)
		return (int)static_cast<eml23__FloatingPointLatticeArray*>(s3c->CrosslineCoordinates)->StartValue;
	else
		return 0;
}

int IjkGridLatticeRepresentation::getInlineIOffset() const
{
	resqml22__Seismic3dCoordinates* s3c = getSeismic3dCoordinates2_2(0);

	if (s3c && s3c->InlineCoordinates->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__FloatingPointLatticeArray)
	{
		eml23__FloatingPointLatticeArray* dla = static_cast<eml23__FloatingPointLatticeArray*>(s3c->InlineCoordinates);
	    if (dla && dla->Offset[0]->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__FloatingPointConstantArray)
		{
			return (int)static_cast<eml23__FloatingPointConstantArray*>(dla->Offset[0])->Value;
		}
	}

	return 0;
}

int IjkGridLatticeRepresentation::getInlineJOffset() const
{
	resqml22__Seismic3dCoordinates* s3c = getSeismic3dCoordinates2_2(0);

	if (s3c && s3c->InlineCoordinates->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__FloatingPointLatticeArray)
	{
		eml23__FloatingPointLatticeArray* dla = static_cast<eml23__FloatingPointLatticeArray*>(s3c->InlineCoordinates);
	    if (dla && dla->Offset[1]->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__FloatingPointConstantArray)
		{
			return (int)static_cast<eml23__FloatingPointConstantArray*>(dla->Offset[1])->Value;
		}
	}

	return 0;
}

int IjkGridLatticeRepresentation::getInlineKOffset() const
{
	resqml22__Seismic3dCoordinates* s3c = getSeismic3dCoordinates2_2(0);

	if (s3c && s3c->InlineCoordinates->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__FloatingPointLatticeArray)
	{
		eml23__FloatingPointLatticeArray* dla = static_cast<eml23__FloatingPointLatticeArray*>(s3c->InlineCoordinates);
	    if (dla && dla->Offset[2]->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__FloatingPointConstantArray)
		{
			return (int)static_cast<eml23__FloatingPointConstantArray*>(dla->Offset[2])->Value;
		}
	}

	return 0;
}

int IjkGridLatticeRepresentation::getCrosslineIOffset() const
{
	resqml22__Seismic3dCoordinates* s3c = getSeismic3dCoordinates2_2(0);

	if (s3c && s3c->CrosslineCoordinates->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__FloatingPointLatticeArray)
	{
		eml23__FloatingPointLatticeArray* dla = static_cast<eml23__FloatingPointLatticeArray*>(s3c->CrosslineCoordinates);
	    if (dla && dla->Offset[0]->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__FloatingPointConstantArray)
		{
			return (int)static_cast<eml23__FloatingPointConstantArray*>(dla->Offset[0])->Value;
		}
	}

	return 0;
}

int IjkGridLatticeRepresentation::getCrosslineJOffset() const
{
	resqml22__Seismic3dCoordinates* s3c = getSeismic3dCoordinates2_2(0);

	if (s3c && s3c->CrosslineCoordinates->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__FloatingPointLatticeArray)
	{
		eml23__FloatingPointLatticeArray* dla = static_cast<eml23__FloatingPointLatticeArray*>(s3c->CrosslineCoordinates);
	    if (dla && dla->Offset[1]->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__FloatingPointConstantArray)
		{
			return (int)static_cast<eml23__FloatingPointConstantArray*>(dla->Offset[1])->Value;
		}
	}

	return 0;
}

int IjkGridLatticeRepresentation::getCrosslineKOffset() const
{
	resqml22__Seismic3dCoordinates* s3c = getSeismic3dCoordinates2_2(0);

	if (s3c && s3c->CrosslineCoordinates->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__FloatingPointLatticeArray)
	{
		eml23__FloatingPointLatticeArray* dla = static_cast<eml23__FloatingPointLatticeArray*>(s3c->CrosslineCoordinates);
	    if (dla && dla->Offset[2]->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__FloatingPointConstantArray)
		{
			return (int)static_cast<eml23__FloatingPointConstantArray*>(dla->Offset[2])->Value;
		}
	}

	return 0;
}

void IjkGridLatticeRepresentation::setGeometryAsCoordinateLineNodes(
	gsoap_resqml2_0_1::resqml20__PillarShape mostComplexPillarGeometry,
	gsoap_resqml2_0_1::resqml20__KDirection kDirectionKind,
	bool isRightHanded,
	double originX, double originY, double originZ,
	double directionIX, double directionIY, double directionIZ, double spacingI,
	double directionJX, double directionJY, double directionJZ, double spacingJ,
	double directionKX, double directionKY, double directionKZ, double spacingK, RESQML2_NS::AbstractLocal3dCrs * localCrs)
{
	if (localCrs == nullptr) {
		localCrs = getRepository()->getDefaultCrs();
		if (localCrs == nullptr) {
			throw std::invalid_argument("A (default) CRS must be provided.");
		}
	}

	resqml22__IjkGridGeometry* geom = soap_new_resqml22__IjkGridGeometry(gsoapProxy2_3->soap);
	geom->LocalCrs = localCrs->newEml23Reference();
	if (!isTruncated()) {
		getSpecializedGsoapProxy2_2()->Geometry = geom;
	}
	else {
		getSpecializedTruncatedGsoapProxy2_2()->Geometry = geom;
	}
	geom->GridIsRighthanded = isRightHanded;
	geom->PillarShape = static_cast<resqml22__PillarShape>(mostComplexPillarGeometry);
	geom->KDirection = static_cast<resqml22__KDirection>(kDirectionKind);

	// Pillar defined
	eml23__BooleanConstantArray* definedPillars = soap_new_eml23__BooleanConstantArray(gsoapProxy2_3->soap);
	geom->PillarGeometryIsDefined = definedPillars;
	definedPillars->Count = (getICellCount() + 1) * (getJCellCount() + 1);
	definedPillars->Value = true;

	// XML coordinate lines
	resqml22__Point3dLatticeArray* xmlPoints = soap_new_resqml22__Point3dLatticeArray(gsoapProxy2_3->soap);
	geom->Points = xmlPoints;

	xmlPoints->AllDimensionsAreOrthogonal = (bool*)soap_malloc(gsoapProxy2_3->soap, sizeof(bool));
	*xmlPoints->AllDimensionsAreOrthogonal = true;
	xmlPoints->Origin = soap_new_resqml22__Point3d(gsoapProxy2_3->soap);
	xmlPoints->Origin->Coordinate1 = originX;
	xmlPoints->Origin->Coordinate2 = originY;
	xmlPoints->Origin->Coordinate3 = originZ;

	// slowest axis to fastest axis so k,j,i 
	resqml22__Point3dLatticeDimension * dimK = soap_new_resqml22__Point3dLatticeDimension(gsoapProxy2_3->soap);
	xmlPoints->Dimension.push_back(dimK);
	// the dimension is the index of the axis in the collection. here we start from 0 and goes up by 1
	dimK->Direction = soap_new_resqml22__Point3d(gsoapProxy2_3->soap);
	dimK->Direction->Coordinate1 = directionKX;
	dimK->Direction->Coordinate2 = directionKY;
	dimK->Direction->Coordinate3 = directionKZ;
	eml23__FloatingPointConstantArray * xmlSpacingK = soap_new_eml23__FloatingPointConstantArray(gsoapProxy2_3->soap);
	dimK->Spacing = xmlSpacingK;
	xmlSpacingK->Count = getKCellCount(); // number of cells on K axis
	xmlSpacingK->Value = spacingK;
	
	resqml22__Point3dLatticeDimension * dimJ = soap_new_resqml22__Point3dLatticeDimension(gsoapProxy2_3->soap);
	xmlPoints->Dimension.push_back(dimJ);
	// the dimension is the index of the axis in the collection
	dimJ->Direction = soap_new_resqml22__Point3d(gsoapProxy2_3->soap);
	dimJ->Direction->Coordinate1 = directionJX;
	dimJ->Direction->Coordinate2 = directionJY;
	dimJ->Direction->Coordinate3 = directionJZ;
	eml23__FloatingPointConstantArray * xmlSpacingJ = soap_new_eml23__FloatingPointConstantArray(gsoapProxy2_3->soap);
	dimJ->Spacing = xmlSpacingJ;
	xmlSpacingJ->Count = getJCellCount(); // number of cells on J axis
	xmlSpacingJ->Value = spacingJ;

	resqml22__Point3dLatticeDimension * dimI = soap_new_resqml22__Point3dLatticeDimension(gsoapProxy2_3->soap);
	xmlPoints->Dimension.push_back(dimI);
	// the dimension is the index of the axis in the collection
	dimI->Direction = soap_new_resqml22__Point3d(gsoapProxy2_3->soap);
	dimI->Direction->Coordinate1 = directionIX;
	dimI->Direction->Coordinate2 = directionIY;
	dimI->Direction->Coordinate3 = directionIZ;
	eml23__FloatingPointConstantArray * xmlSpacingI = soap_new_eml23__FloatingPointConstantArray(gsoapProxy2_3->soap);
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
	if (seismicSupport == nullptr)
		throw invalid_argument("The seismic support cannot be null.");

	resqml22__PointGeometry* geom = getPointGeometry2_2(patchIndex);
	if (geom == nullptr)
		throw invalid_argument("The patchIndex does not identify a point geometry.");

	if (geom->SeismicCoordinates == nullptr)
		geom->SeismicCoordinates = soap_new_resqml22__Seismic3dCoordinates(gsoapProxy2_3->soap);
	else if (geom->SeismicCoordinates->soap_type() == SOAP_TYPE_gsoap_eml2_3_resqml22__Seismic2dCoordinates)
		throw invalid_argument("It already exists some seismic 2d coordinates for this patch.");
	resqml22__Seismic3dCoordinates* patch = static_cast<resqml22__Seismic3dCoordinates*>(geom->SeismicCoordinates);

	patch->SeismicSupport = seismicSupport->newEml23Reference();
	getRepository()->addRelationship(this, seismicSupport);

	// inlines XML
	eml23__FloatingPointLatticeArray* inlineValues = soap_new_eml23__FloatingPointLatticeArray(gsoapProxy2_3->soap);
	inlineValues->StartValue = startInline;

	eml23__FloatingPointConstantArray * IoffsetInline = soap_new_eml23__FloatingPointConstantArray(gsoapProxy2_3->soap);
	IoffsetInline->Count = countInline - 1;
	IoffsetInline->Value = incrInline;
	inlineValues->Offset.push_back(IoffsetInline);

	eml23__FloatingPointConstantArray * IoffsetCrossline = soap_new_eml23__FloatingPointConstantArray(gsoapProxy2_3->soap);
	IoffsetCrossline->Count = countCrossline -1;
	IoffsetCrossline->Value = 0;
	inlineValues->Offset.push_back(IoffsetCrossline);

	eml23__FloatingPointConstantArray * IoffsetSample = soap_new_eml23__FloatingPointConstantArray(gsoapProxy2_3->soap);
	IoffsetSample->Count = countSample -1;
	IoffsetSample->Value = 0;
	inlineValues->Offset.push_back(IoffsetSample);

	patch->InlineCoordinates = inlineValues;

	// crosslines XML
	eml23__FloatingPointLatticeArray* crosslineValues = soap_new_eml23__FloatingPointLatticeArray(gsoapProxy2_3->soap);
	crosslineValues->StartValue = startCrossline;

	eml23__FloatingPointConstantArray * CoffsetInline = soap_new_eml23__FloatingPointConstantArray(gsoapProxy2_3->soap);
	CoffsetInline->Count = countInline - 1;
	CoffsetInline->Value = 0;
	crosslineValues->Offset.push_back(CoffsetInline);
	eml23__FloatingPointConstantArray * CoffsetCrossline = soap_new_eml23__FloatingPointConstantArray(gsoapProxy2_3->soap);
	CoffsetCrossline->Count = countCrossline - 1;
	CoffsetCrossline->Value = incrCrossline;
	crosslineValues->Offset.push_back(CoffsetCrossline);
	eml23__FloatingPointConstantArray * CoffsetSample = soap_new_eml23__FloatingPointConstantArray(gsoapProxy2_3->soap);
	CoffsetSample->Count = countSample - 1;
	CoffsetSample->Value = 0;
	crosslineValues->Offset.push_back(CoffsetSample);

	patch->CrosslineCoordinates = crosslineValues;
}
