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
#pragma once

#include "resqml2_0_1/WellboreFrameRepresentation.h"

namespace RESQML2_0_1_NS
{
	class WellboreMarkerFrameRepresentation : public WellboreFrameRepresentation
	{
	public:

		/**
		* Only to be used in partial transfer context
		*/
		WellboreMarkerFrameRepresentation(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) :
			WellboreFrameRepresentation(partialObject), stratigraphicOccurrenceInterpretation(nullptr)
		{
		}

		/**
		* Creates an instance of this class in a gsoap context.
		* @param interp		The WellboreFeature interpretation the instance represents.
		* @param guid		The guid to set to the new instance. If empty then a new guid will be generated.
		* @param title		A title for the instance to create.
		* @param traj		The trajectory this WellboreFeature frame is based on.
		*/
		WellboreMarkerFrameRepresentation(class WellboreInterpretation* interp, const std::string & guid, const std::string & title, class WellboreTrajectoryRepresentation * traj);

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		WellboreMarkerFrameRepresentation(gsoap_resqml2_0_1::_resqml2__WellboreMarkerFrameRepresentation* fromGsoap) : WellboreFrameRepresentation(fromGsoap), stratigraphicOccurrenceInterpretation(nullptr) {}

		// clean the owned markers
		~WellboreMarkerFrameRepresentation();

		/**
		* Pushes back a new WellboreFeature marker to this WellboreFeature marker frame.
		* One WellboreFeature marker must be added per MD of the WellboreFeature marker frame.
		*/
		DLL_IMPORT_OR_EXPORT class WellboreMarker* pushBackNewWellboreMarker(const std::string & guid, const std::string & title);

		/**
		* Add a WellboreFeature marker to this WellboreFeature marker frame with a geologic information on the intersected feature.
		* One WellboreFeature marker must be added per MD of the WellboreFeature marker frame.
		*/
		DLL_IMPORT_OR_EXPORT class WellboreMarker* pushBackNewWellboreMarker(const std::string & guid, const std::string & title, const gsoap_resqml2_0_1::resqml2__GeologicBoundaryKind & geologicBoundaryKind);

		/**
		* Return the number of wellbore marker for this Wellbore marker frame representation
		*/
		DLL_IMPORT_OR_EXPORT unsigned int getWellboreMarkerCount();

		/**
		* Get all the wellbore markers of this well marker frame representation.
		*/
		DLL_IMPORT_OR_EXPORT const std::vector<class WellboreMarker*> & getWellboreMarkerSet() const;

		DLL_IMPORT_OR_EXPORT void setStratigraphicOccurrenceInterpretation(class StratigraphicOccurrenceInterpretation * stratiOccurenceInterp);

		/**
		* Set the correspondance between the interval of the wellbore marker frame rep and the units of a stratiColRankInterp
		* @param stratiUnitIndices	The count must be equal to the count of contacts in stratiColRankInterp
		* @param nullValue			The value which is used to indicate we don't know the related strati units against a particular interval.
		*/
		DLL_IMPORT_OR_EXPORT void setIntervalStratigraphicUnits(unsigned int * stratiUnitIndices, const unsigned int & nullValue, class StratigraphicOccurrenceInterpretation* stratiOccurenceInterp);

		DLL_IMPORT_OR_EXPORT class StratigraphicOccurrenceInterpretation* getStratigraphicOccurrenceInterpretation() { return stratigraphicOccurrenceInterpretation; }

		DLL_IMPORT_OR_EXPORT static const char* XML_TAG;
		DLL_IMPORT_OR_EXPORT virtual std::string getXmlTag() const {return XML_TAG;}

		std::vector<epc::Relationship> getAllTargetRelationships() const;
		void resolveTargetRelationships(COMMON_NS::EpcDocument* epcDoc);

	protected:

		// XML forward relationships
		class StratigraphicOccurrenceInterpretation* stratigraphicOccurrenceInterpretation;

		// only memory relationship
		std::vector<class WellboreMarker*> markerSet;
	};
}

