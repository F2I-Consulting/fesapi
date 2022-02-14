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
%{
#include "../src/resqml2_2/BlockedWellboreRepresentation.h"
#include "../src/resqml2_2/BoundaryFeature.h"
#include "../src/resqml2_2/BoundaryFeatureInterpretation.h"
#include "../src/resqml2_2/CategoricalProperty.h"
#include "../src/resqml2_2/CmpLineFeature.h"
#include "../src/resqml2_2/CommentProperty.h"
#include "../src/resqml2_2/ContinuousColorMap.h"
#include "../src/resqml2_2/ContinuousProperty.h"
#include "../src/resqml2_2/CulturalFeature.h"
#include "../src/resqml2_2/DiscreteColorMap.h"
#include "../src/resqml2_2/DiscreteProperty.h"
#include "../src/resqml2_2/DoubleTableLookup.h"
#include "../src/resqml2_2/EarthModelInterpretation.h"
#include "../src/resqml2_2/FaultInterpretation.h"
#include "../src/resqml2_2/FluidBoundaryInterpretation.h"
#include "../src/resqml2_2/GenericFeatureInterpretation.h"
#include "../src/resqml2_2/GeobodyBoundaryInterpretation.h"
#include "../src/resqml2_2/GeobodyInterpretation.h"
#include "../src/resqml2_2/Grid2dRepresentation.h"
#include "../src/resqml2_2/GridConnectionSetRepresentation.h"
#include "../src/resqml2_2/HorizonInterpretation.h"
#include "../src/resqml2_2/IjkGridExplicitRepresentation.h"
#include "../src/resqml2_2/IjkGridLatticeRepresentation.h"
#include "../src/resqml2_2/IjkGridNoGeometryRepresentation.h"
#include "../src/resqml2_2/IjkGridParametricRepresentation.h"
#include "../src/resqml2_2/LocalDepth3dCrs.h"
#include "../src/resqml2_2/LocalTime3dCrs.h"
#include "../src/resqml2_2/MdDatum.h"
#include "../src/resqml2_2/Model.h"
#include "../src/resqml2_2/NonSealedSurfaceFrameworkRepresentation.h"
#include "../src/resqml2_2/PlaneSetRepresentation.h"
#include "../src/resqml2_2/PointSetRepresentation.h"
#include "../src/resqml2_2/PointsProperty.h"
#include "../src/resqml2_2/PolylineRepresentation.h"
#include "../src/resqml2_2/PolylineSetRepresentation.h"
#include "../src/resqml2_2/RepresentationSetRepresentation.h"
#include "../src/resqml2_2/RockFluidUnitInterpretation.h"
#include "../src/resqml2_2/RockFluidOrganizationInterpretation.h"
#include "../src/resqml2_2/RockVolumeFeature.h"
#include "../src/resqml2_2/SealedSurfaceFrameworkRepresentation.h"
#include "../src/resqml2_2/SealedVolumeFrameworkRepresentation.h"
#include "../src/resqml2_2/SeismicLatticeFeature.h"
#include "../src/resqml2_2/SeismicLineSetFeature.h"
#include "../src/resqml2_2/SeismicWellboreFrameRepresentation.h"
#include "../src/resqml2_2/ShotPointLineFeature.h"
#include "../src/resqml2_2/StratigraphicColumn.h"
#include "../src/resqml2_2/StratigraphicColumnRankInterpretation.h"
#include "../src/resqml2_2/GeologicUnitOccurrenceInterpretation.h"
#include "../src/resqml2_2/StratigraphicUnitInterpretation.h"
#include "../src/resqml2_2/StreamlinesFeature.h"
#include "../src/resqml2_2/StreamlinesRepresentation.h"
#include "../src/resqml2_2/StringTableLookup.h"
#include "../src/resqml2_2/StructuralOrganizationInterpretation.h"
#include "../src/resqml2_2/SubRepresentation.h"
#include "../src/resqml2_2/TriangulatedSetRepresentation.h"
#include "../src/resqml2_2/UnstructuredGridRepresentation.h"
#include "../src/resqml2_2/WellboreFeature.h"
#include "../src/resqml2_2/WellboreFrameRepresentation.h"
#include "../src/resqml2_2/WellboreInterpretation.h"
#include "../src/resqml2_2/WellboreMarker.h"
#include "../src/resqml2_2/WellboreMarkerFrameRepresentation.h"
#include "../src/resqml2_2/WellboreTrajectoryRepresentation.h"
%}

#if defined(SWIGJAVA) || defined(SWIGCSHARP)
	%nspace RESQML2_2_NS::BlockedWellboreRepresentation;
	%nspace RESQML2_2_NS::BoundaryFeature;
	%nspace RESQML2_2_NS::BoundaryFeatureInterpretation;
	%nspace RESQML2_2_NS::CategoricalProperty;
	%nspace RESQML2_2_NS::CmpLineFeature;
	%nspace RESQML2_2_NS::CommentProperty;
	%nspace RESQML2_2_NS::ContinuousColorMap;
	%nspace RESQML2_2_NS::ContinuousProperty;
	%nspace RESQML2_2_NS::CulturalFeature;
	%nspace RESQML2_2_NS::DiscreteColorMap;
	%nspace RESQML2_2_NS::DiscreteProperty;
	%nspace RESQML2_2_NS::DoubleTableLookup;
	%nspace RESQML2_2_NS::EarthModelInterpretation;
	%nspace RESQML2_2_NS::FaultInterpretation;
	%nspace RESQML2_2_NS::FluidBoundaryInterpretation;
	%nspace RESQML2_2_NS::GenericFeatureInterpretation;
	%nspace RESQML2_2_NS::GeobodyBoundaryInterpretation;
	%nspace RESQML2_2_NS::GeobodyInterpretation;
	%nspace RESQML2_2_NS::Grid2dRepresentation;
	%nspace RESQML2_2_NS::GridConnectionSetRepresentation;
	%nspace RESQML2_2_NS::HorizonInterpretation;
	%nspace RESQML2_2_NS::IjkGridExplicitRepresentation;
	%nspace RESQML2_2_NS::IjkGridLatticeRepresentation;
	%nspace RESQML2_2_NS::IjkGridNoGeometryRepresentation;
	%nspace RESQML2_2_NS::IjkGridParametricRepresentation;
	%nspace RESQML2_2_NS::LocalDepth3dCrs;
	%nspace RESQML2_2_NS::LocalTime3dCrs ;
	%nspace RESQML2_2_NS::MdDatum;
	%nspace RESQML2_2_NS::Model;
	%nspace RESQML2_2_NS::NonSealedSurfaceFrameworkRepresentation;
	%nspace RESQML2_2_NS::PlaneSetRepresentation;
	%nspace RESQML2_2_NS::PointSetRepresentation;
	%nspace RESQML2_2_NS::PointsProperty;
	%nspace RESQML2_2_NS::PolylineRepresentation;
	%nspace RESQML2_2_NS::PolylineSetRepresentation;
	%nspace RESQML2_2_NS::RepresentationSetRepresentation;
	%nspace RESQML2_2_NS::RockFluidUnitInterpretation;
	%nspace RESQML2_2_NS::RockFluidOrganizationInterpretation;
	%nspace RESQML2_2_NS::RockVolumeFeature;
	%nspace RESQML2_2_NS::SealedSurfaceFrameworkRepresentation;
	%nspace RESQML2_2_NS::SealedVolumeFrameworkRepresentation;
	%nspace RESQML2_2_NS::SeismicLatticeFeature;
	%nspace RESQML2_2_NS::SeismicLineSetFeature;
	%nspace RESQML2_2_NS::SeismicWellboreFrameRepresentation;
	%nspace RESQML2_2_NS::ShotPointLineFeature;
	%nspace RESQML2_2_NS::StratigraphicColumn;
	%nspace RESQML2_2_NS::StratigraphicColumnRankInterpretation;
	%nspace RESQML2_2_NS::GeologicUnitOccurrenceInterpretation;
	%nspace RESQML2_2_NS::StratigraphicUnitInterpretation;
	%nspace RESQML2_2_NS::StreamlinesFeature;
	%nspace RESQML2_2_NS::StreamlinesRepresentation;
	%nspace RESQML2_2_NS::StringTableLookup;
	%nspace RESQML2_2_NS::StructuralOrganizationInterpretation;
	%nspace RESQML2_2_NS::SubRepresentation;
	%nspace RESQML2_2_NS::TriangulatedSetRepresentation;
	%nspace RESQML2_2_NS::UnstructuredGridRepresentation;
	%nspace RESQML2_2_NS::WellboreFeature;
	%nspace RESQML2_2_NS::WellboreFrameRepresentation;
	%nspace RESQML2_2_NS::WellboreInterpretation;
	%nspace RESQML2_2_NS::WellboreMarker;
	%nspace RESQML2_2_NS::WellboreMarkerFrameRepresentation;
	%nspace RESQML2_2_NS::WellboreTrajectoryRepresentation;
#endif

namespace gsoap_eml2_3
{
	enum class resqml22__InterpolationDomain {
		hsv = 0,
		rgb = 1
	};
	enum class resqml22__InterpolationMethod {
		linear = 0,
		logarithmic = 1
	};
	enum class resqml22__FluidContact {
		free_x0020water_x0020contact = 0,
		gas_x0020oil_x0020contact = 1,
		gas_x0020water_x0020contact = 2,
		seal = 3,
		water_x0020oil_x0020contact = 4
	};
}

namespace RESQML2_2_NS
{
	%nodefaultctor; // Disable creation of default constructors
	
#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(Resqml22_DiscreteColorMap) DiscreteColorMap;
#endif	
	class DiscreteColorMap : public RESQML2_NS::DiscreteColorMap
	{
	public:
	};
	
#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(Resqml22_ContinuousColorMap) ContinuousColorMap;
#endif	
	class ContinuousColorMap : public RESQML2_NS::ContinuousColorMap 
	{
	public:
	};

	//************************************/
	//************ CRS *******************/
	//************************************/
#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(Resqml22_LocalDepth3dCrs) LocalDepth3dCrs;
#endif
	class LocalDepth3dCrs : public RESQML2_NS::LocalDepth3dCrs
	{
	public:
	};

#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(Resqml22_LocalTime3dCrs) LocalTime3dCrs;
#endif
	class LocalTime3dCrs : public RESQML2_NS::LocalTime3dCrs
	{
	public:
	};
	
#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(Resqml22_MdDatum) MdDatum;
#endif
	class MdDatum : public RESQML2_NS::MdDatum
	{
	public:
	};
	
	//************************************/
	//************ FEATURE ***************/
	//************************************/

#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(Resqml22_BoundaryFeature) BoundaryFeature;
#endif
	class BoundaryFeature : public RESQML2_NS::BoundaryFeature
	{
	};

#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(Resqml22_RockVolumeFeature) RockVolumeFeature;
#endif	
	class RockVolumeFeature : public RESQML2_NS::RockVolumeFeature
	{
	public:
	};
	
#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(Resqml22_Model) Model;
#endif
	class Model : public RESQML2_NS::Model
	{
	public:
	};
	
#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(Resqml22_CulturalFeature) CulturalFeature;
#endif	
	class CulturalFeature : public RESQML2_NS::CulturalFeature
	{
	public:
	};

#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(Resqml22_SeismicLineSetFeature) SeismicLineSetFeature;
#endif
	class SeismicLineSetFeature : public RESQML2_NS::SeismicLineSetFeature
	{
	};

#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(Resqml22_ShotPointLineFeature) ShotPointLineFeature;
#endif
	class ShotPointLineFeature : public RESQML2_NS::ShotPointLineFeature
	{
	public:
	};

#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(Resqml22_CmpLineFeature) CmpLineFeature;
#endif
	class CmpLineFeature : public RESQML2_NS::CmpLineFeature
	{
	public:
	};

#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(Resqml22_SeismicLatticeFeature) SeismicLatticeFeature;
#endif
	class SeismicLatticeFeature : public RESQML2_NS::SeismicLatticeFeature
	{
	public:
	};

#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(Resqml22_WellboreFeature) WellboreFeature;
#endif
	class WellboreFeature : public RESQML2_NS::WellboreFeature
	{
	public:
	};

	//************************************/
	//************ INTERPRETATION ********/
	//************************************/
#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(Resqml22_GenericFeatureInterpretation) GenericFeatureInterpretation;
#endif
	class GenericFeatureInterpretation : public RESQML2_NS::GenericFeatureInterpretation
	{
	};

#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(Resqml22_BoundaryFeatureInterpretation) BoundaryFeatureInterpretation;
#endif
	class BoundaryFeatureInterpretation : public RESQML2_NS::BoundaryFeatureInterpretation
	{
	};

#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(Resqml22_FaultInterpretation) FaultInterpretation;
#endif
	class FaultInterpretation : public RESQML2_NS::FaultInterpretation
	{
	public: 
		void pushBackThrowInterpretation(gsoap_resqml2_0_1::resqml20__ThrowKind throwKind);
	};

#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(Resqml22_FluidBoundaryInterpretation) FluidBoundaryInterpretation;
#endif
	class FluidBoundaryInterpretation : public RESQML2_NS::FluidBoundaryInterpretation
	{
	public:
	};

#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(Resqml22_HorizonInterpretation) HorizonInterpretation;
#endif
	class HorizonInterpretation : public RESQML2_NS::HorizonInterpretation
	{
	};
	
#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(Resqml22_GeobodyBoundaryInterpretation) GeobodyBoundaryInterpretation;
#endif
	class GeobodyBoundaryInterpretation : public RESQML2_NS::GeobodyBoundaryInterpretation
	{
	};
	
	class WellboreTrajectoryRepresentation;
#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(Resqml22_WellboreInterpretation) WellboreInterpretation;
#endif
	class WellboreInterpretation : public RESQML2_NS::WellboreInterpretation
	{
	public:
	};
	
#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(Resqml22_StratigraphicUnitInterpretation) StratigraphicUnitInterpretation;
#endif
	class StratigraphicUnitInterpretation : public RESQML2_NS::StratigraphicUnitInterpretation
	{
	};
	
#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(Resqml22_GeobodyInterpretation) GeobodyInterpretation;
#endif
	class GeobodyInterpretation : public RESQML2_NS::GeobodyInterpretation
	{
	public :
	};
	
#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(Resqml22_StructuralOrganizationInterpretation) StructuralOrganizationInterpretation;
#endif
	class StructuralOrganizationInterpretation : public RESQML2_NS::StructuralOrganizationInterpretation
	{
	public:
	};
	
#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(Resqml22_StratigraphicColumnRankInterpretation) StratigraphicColumnRankInterpretation;
#endif
	class StratigraphicColumnRankInterpretation : public RESQML2_NS::StratigraphicColumnRankInterpretation
	{
	public:
	};
	
#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(Resqml22_RockFluidUnitInterpretation) RockFluidUnitInterpretation;
#endif	
	class RockFluidUnitInterpretation : public RESQML2_NS::RockFluidUnitInterpretation
	{
	public:
	};
	
#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(Resqml22_RockFluidOrganizationInterpretation) RockFluidOrganizationInterpretation;
#endif
	class RockFluidOrganizationInterpretation : public RESQML2_NS::RockFluidOrganizationInterpretation
	{
	public:
	};
	
	class WellboreMarkerFrameRepresentation;	
#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(Resqml22_GeologicUnitOccurrenceInterpretation) GeologicUnitOccurrenceInterpretation;
#endif
	class GeologicUnitOccurrenceInterpretation : public RESQML2_NS::GeologicUnitOccurrenceInterpretation
	{
	public:
	};

#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(Resqml22_StratigraphicColumn) StratigraphicColumn;
#endif
	class StratigraphicColumn : public RESQML2_NS::StratigraphicColumn
	{
	public:
	};

#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(Resqml22_EarthModelInterpretation) EarthModelInterpretation;
#endif
	class EarthModelInterpretation : public RESQML2_NS::EarthModelInterpretation
	{
	public:
	};

	//************************************/
	//************ REPRESENTATION ********/
	//************************************/

#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(Resqml22_SubRepresentation) SubRepresentation;
#endif	
	class SubRepresentation : public RESQML2_NS::SubRepresentation
	{
	public:
	};

#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(Resqml22_PolylineSetRepresentation) PolylineSetRepresentation;
#endif
	class PolylineSetRepresentation : public RESQML2_NS::PolylineSetRepresentation
	{
	public:
	};

#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(Resqml22_PointSetRepresentation) PointSetRepresentation;
#endif
	class PointSetRepresentation : public RESQML2_NS::PointSetRepresentation
	{
	public:
	};
	
#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(Resqml22_PlaneSetRepresentation) PlaneSetRepresentation;
#endif
	class PlaneSetRepresentation : public RESQML2_NS::PlaneSetRepresentation
	{
	public:
	};

#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(Resqml22_PolylineRepresentation) PolylineRepresentation;
#endif
	class PolylineRepresentation : public RESQML2_NS::PolylineRepresentation
	{
	public:
	};
	
#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(Resqml22_Grid2dRepresentation) Grid2dRepresentation;
#endif
	class Grid2dRepresentation : public RESQML2_NS::Grid2dRepresentation
	{
	public:
	};

#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(Resqml22_TriangulatedSetRepresentation) TriangulatedSetRepresentation;
#endif
	class TriangulatedSetRepresentation : public RESQML2_NS::TriangulatedSetRepresentation
	{
	public:
	};
	
	class WellboreFrameRepresentation;
#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(Resqml22_WellboreTrajectoryRepresentation) WellboreTrajectoryRepresentation;
#endif
	class  WellboreTrajectoryRepresentation : public RESQML2_NS::WellboreTrajectoryRepresentation
	{
	public:
	};
	
#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(Resqml22_WellboreFrameRepresentation) WellboreFrameRepresentation;
#endif
	class WellboreFrameRepresentation : public RESQML2_NS::WellboreFrameRepresentation
	{
	public:
	};
	
#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(Resqml22_SeismicWellboreFrameRepresentation) SeismicWellboreFrameRepresentation;
#endif
	class SeismicWellboreFrameRepresentation : public RESQML2_NS::SeismicWellboreFrameRepresentation
	{
	public:
	};
	
#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(Resqml22_WellboreMarker) WellboreMarker;
#endif
	class WellboreMarker : public RESQML2_NS::WellboreMarker
	{
	public:
	};
	
#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(Resqml22_WellboreMarkerFrameRepresentation) WellboreMarkerFrameRepresentation;
#endif
	class WellboreMarkerFrameRepresentation : public RESQML2_NS::WellboreMarkerFrameRepresentation
	{
	public:
	};
	
#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(Resqml22_RepresentationSetRepresentation) RepresentationSetRepresentation;
#endif
	class RepresentationSetRepresentation : public RESQML2_NS::RepresentationSetRepresentation
	{
	public:
	};
	
#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(Resqml22_NonSealedSurfaceFrameworkRepresentation) NonSealedSurfaceFrameworkRepresentation;
#endif
	class NonSealedSurfaceFrameworkRepresentation : public RESQML2_NS::NonSealedSurfaceFrameworkRepresentation
	{
	public:
	};
	
#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(Resqml22_SealedSurfaceFrameworkRepresentation) SealedSurfaceFrameworkRepresentation;
#endif
	class SealedSurfaceFrameworkRepresentation : public RESQML2_NS::SealedSurfaceFrameworkRepresentation
	{
	public:
	};
	
#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(Resqml22_SealedVolumeFrameworkRepresentation) SealedVolumeFrameworkRepresentation;
#endif
	class SealedVolumeFrameworkRepresentation : public RESQML2_NS::SealedVolumeFrameworkRepresentation
	{
	public:
	};

#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(Resqml22_UnstructuredGridRepresentation) UnstructuredGridRepresentation;
#endif
	class UnstructuredGridRepresentation : public RESQML2_NS::UnstructuredGridRepresentation
	{
	public:
	};
	
#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(Resqml22_IjkGridLatticeRepresentation) IjkGridLatticeRepresentation;
#endif
	class IjkGridLatticeRepresentation : public RESQML2_NS::IjkGridLatticeRepresentation
	{
	public:
	};
	
#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(Resqml22_IjkGridExplicitRepresentation) IjkGridExplicitRepresentation;
#endif
	class IjkGridExplicitRepresentation : public RESQML2_NS::IjkGridExplicitRepresentation
	{
	public:
	};

#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(Resqml22_IjkGridParametricRepresentation) IjkGridParametricRepresentation;
#endif	
	class IjkGridParametricRepresentation : public RESQML2_NS::IjkGridParametricRepresentation
	{
	public:
	};
	
#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(Resqml22_IjkGridNoGeometryRepresentation) IjkGridNoGeometryRepresentation;
#endif	
	class IjkGridNoGeometryRepresentation : public RESQML2_NS::IjkGridNoGeometryRepresentation
	{
	public:
	};
	
#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(Resqml22_GridConnectionSetRepresentation) GridConnectionSetRepresentation;
#endif	
	class GridConnectionSetRepresentation : public RESQML2_NS::GridConnectionSetRepresentation
	{
	public:
	};
	
#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(Resqml22_BlockedWellboreRepresentation) BlockedWellboreRepresentation;
#endif	
	class BlockedWellboreRepresentation : public RESQML2_NS::BlockedWellboreRepresentation
	{
	public:
	};

#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(Resqml22_StreamlinesFeature) StreamlinesFeature;
#endif	
	class StreamlinesFeature : public RESQML2_NS::StreamlinesFeature
	{
	public:
	};
	
#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(Resqml22_StreamlinesRepresentation) StreamlinesRepresentation;
#endif	
	class StreamlinesRepresentation : public RESQML2_NS::StreamlinesRepresentation
	{
	public:
	};

	//************************************/
	//************** PROPERTY ************/
	//************************************/
	
#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(Resqml22_DoubleTableLookup) DoubleTableLookup;
#endif	
	class DoubleTableLookup : public RESQML2_NS::DoubleTableLookup
	{
	public:
	};
	
#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(Resqml22_StringTableLookup) StringTableLookup;
#endif	
	class StringTableLookup : public RESQML2_NS::StringTableLookup
	{
	public:
	};
	
#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(Resqml22_CommentProperty) CommentProperty;
#endif	
	class CommentProperty : public RESQML2_NS::CommentProperty
	{
	public:
	};
	
#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(Resqml22_ContinuousProperty) ContinuousProperty;
#endif
	class ContinuousProperty : public RESQML2_NS::ContinuousProperty
	{
	public:
	};
	
#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(Resqml22_DiscreteProperty) DiscreteProperty;
#endif
	class DiscreteProperty : public RESQML2_NS::DiscreteProperty
	{
	public:
	};
	
#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(Resqml22_CategoricalProperty) CategoricalProperty;
#endif
	class CategoricalProperty : public RESQML2_NS::CategoricalProperty
	{
	public:
	};
	
#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(Resqml22_PointsProperty) PointsProperty;
#endif
	class PointsProperty : public RESQML2_NS::PointsProperty
	{
	public:
	};
}
