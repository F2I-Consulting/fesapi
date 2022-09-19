// quick_example.cpp
#include "common/EpcDocument.h"
#include "common/DataObjectRepository.h"
#include "common/AbstractObject.h"
#include "common/DataObjectReference.h"

#include "eml2/AbstractHdfProxy.h"

#include "eml2_0/HdfProxy.h"

#include "resqml2/BoundaryFeature.h"
#include "resqml2/StratigraphicColumn.h"
#include "resqml2/PolylineSetRepresentation.h"

#include "resqml2_0_1/BoundaryFeature.h"
#include "resqml2_0_1/PolylineSetRepresentation.h"
#include <emscripten/bind.h>

using namespace emscripten;
using namespace COMMON_NS;


EMSCRIPTEN_BINDINGS(fesapi) {

  enum_<DataObjectRepository::EnergisticsStandard>("EnergisticsStandard")
    .value("RESQML2_0_1", DataObjectRepository::EnergisticsStandard::RESQML2_0_1)
    .value("EML2_0", DataObjectRepository::EnergisticsStandard::EML2_0)
    .value("WITSML2_0", DataObjectRepository::EnergisticsStandard::WITSML2_0)
    .value("EML2_1", DataObjectRepository::EnergisticsStandard::EML2_1)
    .value("PRODML2_1", DataObjectRepository::EnergisticsStandard::PRODML2_1)
    .value("EML2_2", DataObjectRepository::EnergisticsStandard::EML2_2)
    .value("RESQML2_2", DataObjectRepository::EnergisticsStandard::RESQML2_2)
    .value("EML2_3", DataObjectRepository::EnergisticsStandard::EML2_3)
    ;

  enum_<DataObjectRepository::openingMode>("openingMode")
    .value("READ_ONLY", DataObjectRepository::openingMode::READ_ONLY)
    .value("READ_WRITE", DataObjectRepository::openingMode::READ_WRITE)
    .value("READ_WRITE_DO_NOT_CREATE", DataObjectRepository::openingMode::READ_WRITE_DO_NOT_CREATE)
    .value("OVERWRITE", DataObjectRepository::openingMode::OVERWRITE)
    ;

  class_<DataObjectRepository>("DataObjectRepository")
    .constructor<>()
    //.function("getDataObjects", select_overload<const std::unordered_map<std::string, std::vector<COMMON_NS::AbstractObject*>>&(void)>(&DataObjectRepository::getDataObjects), allow_raw_pointers())
    .function("getFaultSet", &DataObjectRepository::getFaultSet, allow_raw_pointers())
    .function("getFault", &DataObjectRepository::getFault, allow_raw_pointers())
    .function("getFaultCount", &DataObjectRepository::getFaultCount)
    //
    //.function("getStratigraphicColumnSet", &DataObjectRepository::getStratigraphicColumnSet, allow_raw_pointers())
    //
    .function("getUuids", &DataObjectRepository::getUuids)
    .function("getDefaultEmlVersion", &DataObjectRepository::getDefaultEmlVersion)
    //
    .function("getHdfProxyCount", &DataObjectRepository::getHdfProxyCount)
    .function("getHdfProxy", &DataObjectRepository::getHdfProxy, allow_raw_pointers())
    .function("getWarnings", &DataObjectRepository::getWarnings)
    //
    .function("getFaultPolylineSetRepresentationCount", &DataObjectRepository::getFaultPolylineSetRepresentationCount)
    .function("getFaultPolylineSetRepresentation", &DataObjectRepository::getFaultPolylineSetRepresentation, allow_raw_pointers())     
    ;

  class_<EpcDocument>("EpcDocument")
    .constructor<std::string>()
    .function("open", &EpcDocument::open)
    .function("close", &EpcDocument::close)
    .function("deserializeInto", &EpcDocument::deserializeInto)
    .function("deserializePartiallyInto", &EpcDocument::deserializePartiallyInto)
    ;


  class_<AbstractObject>("AbstractObject")
    .function("isPartial", &AbstractObject::isPartial)
    .function("isTopLevelElement", &AbstractObject::isTopLevelElement)
    .function("getUuid", &AbstractObject::getUuid)
    .function("getTitle", &AbstractObject::getTitle)
    .function("getEditor", &AbstractObject::getEditor)
    ;

  class_<EML2_NS::AbstractHdfProxy>("AbstractHdfProxy")
    .function("getRelativePath", &EML2_NS::AbstractHdfProxy::getRelativePath)
    ;

  class_<EML2_0_NS::HdfProxy, base<EML2_NS::AbstractHdfProxy>>("EML2_0_NS::HdfProxy")
    .constructor<COMMON_NS::DataObjectReference>()    
    ;

  class_<RESQML2_NS::BoundaryFeature, base<AbstractObject>>("RESQML2_NS::BoundaryFeature")
    // .constructor()    
    .function("getXmlTag", &RESQML2_NS::BoundaryFeature::getXmlTag)
    ;

  class_<RESQML2_0_1_NS::BoundaryFeature, base<RESQML2_NS::BoundaryFeature>>("RESQML2_0_1_NS::BoundaryFeature")
    //.constructor()    
    ;

  class_<RESQML2_NS::StratigraphicColumn, base<AbstractObject>>("RESQML2_NS::StratigraphicColumn")
    // .constructor()    
    .function("getXmlTag", &RESQML2_NS::StratigraphicColumn::getXmlTag)
    ;

  class_<RESQML2_NS::AbstractRepresentation, base<AbstractObject>>("RESQML2_NS::AbstractRepresentation")
    .function("getXyzPointCountOfAllPatches", &RESQML2_NS::AbstractRepresentation::getXyzPointCountOfAllPatches)
    .function("getXyzPointsOfAllPatchesInGlobalCrs", 
          optional_override([](RESQML2_NS::AbstractRepresentation& self,
                                std::vector<double>& values)
                                { return self.getXyzPointsOfAllPatchesInGlobalCrs(values.data()); }
                            )
              )
    // &RESQML2_NS::AbstractRepresentation::getXyzPointsOfAllPatchesInGlobalCrs, allow_raw_pointers())
    ;   

  class_<RESQML2_NS::PolylineSetRepresentation, base<RESQML2_NS::AbstractRepresentation>>("RESQML2_NS::PolylineSetRepresentation")
    ;

  class_<RESQML2_0_1_NS::PolylineSetRepresentation, base<RESQML2_NS::PolylineSetRepresentation>>("RESQML2_0_1_NS::PolylineSetRepresentation")
    // .constructor<gsoap_resqml2_0_1::eml20__DataObjectReference>()
    // .constructor<COMMON_NS::DataObjectReference, std::string, std::string>()
    // .constructor<RESQML2_NS::AbstractFeatureInterpretation, std::string, std::string>()
    // .constructor<RESQML2_NS::AbstractFeatureInterpretation, std::string, std::string, gsoap_eml2_3::resqml22__LineRole>()
    // .constructor<gsoap_resqml2_0_1::_resqml20__PolylineSetRepresentation>()    
    
    ;


  //register_vector<RESQML2_NS::BoundaryFeature>("vector<RESQML2_NS::BoundaryFeature>");    
  // register_vector<RESQML2_NS::StratigraphicColumn>("vector<RESQML2_NS::StratigraphicColumn>");    
  register_vector<RESQML2_NS::BoundaryFeature*>("FaultSet");
  register_vector<std::string>("vectorString"); 
  register_vector<double>("vectorDouble"); 
  //register_vector<EML2_NS::AbstractHdfProxy>("vector<AbstractHdfProxy>"); 
}

