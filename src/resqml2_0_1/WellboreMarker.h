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

#include "common/AbstractObject.h"

namespace RESQML2_0_1_NS
{
	/**
	* This class is one of the only one to be a ResqmlDataObject which is not exported into a single file i.e. not a top level element.
	* Consequently its behaviour is slightly different than other class. Especially there is no integration of the instances into an EPC document.
	*/
	class DLL_IMPORT_OR_EXPORT WellboreMarker : public COMMON_NS::AbstractObject
	{
	public:

		/**
		* Creates an instance of this class in a gsoap context.
		* @param wellboreMarkerFrame	The wellbore marker frame which contains the wellbore marker to contruct.
		* @param guid					The guid to set to the new instance. If empty then a new guid will be generated.
		* @param title					A title for the instance to create.
		*/
		WellboreMarker(class WellboreMarkerFrameRepresentation* wellboreMarkerFrame, const std::string & guid, const std::string & title);

		/**
		* Creates an instance of this class in a gsoap context.
		* @param wellboreMarkerFrame	The wellbore marker frame which contains the wellbore marker to contruct.
		* @param guid					The guid to set to the new instance. If empty then a new guid will be generated.
		* @param title					A title for the instance to create.
		* @param geologicBoundaryKind	The type of the feature which the marker intersects.
		*/
		WellboreMarker(class WellboreMarkerFrameRepresentation* wellboreMarkerFrame, const std::string & guid, const std::string & title, const gsoap_resqml2_0_1::resqml2__GeologicBoundaryKind & geologicBoundaryKind);

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		WellboreMarker(gsoap_resqml2_0_1::resqml2__WellboreMarker* fromGsoap, class WellboreMarkerFrameRepresentation* wellboreMarkerFrame) : AbstractObject(fromGsoap), boundaryFeatureInterpretation(nullptr), wellboreMarkerFrameRepresentation(wellboreMarkerFrame)  {}

		/**
		* Destructor
		*/
		~WellboreMarker() {}

		/**
		* Indicates if the marker is associated to a particular GeologicBoundaryKind.
		*/
		bool hasAGeologicBoundaryKind();

		/**
		* Get the type of the intersected feature of the marker.
		* Throw an exception if the marker has no GeologicBoundaryKind (see method hasAGeologicBoundaryKind).
		*/
		gsoap_resqml2_0_1::resqml2__GeologicBoundaryKind getGeologicBoundaryKind();

		class WellboreMarkerFrameRepresentation * getWellMarkerFrameRepresentation() {return wellboreMarkerFrameRepresentation;}

		/**
		* Get the boundary feature interpretation linked to this well marker.
		*/
		class BoundaryFeatureInterpretation* getBoundaryFeatureInterpretation() const {return boundaryFeatureInterpretation;}

		/**
		* Get the UUID of the boundary feature interpretation linked to this well marker.
		* Especially useful in partial transfer mode.
		*/
		std::string getBoundaryFeatureInterpretationUuid() const;

		/**
		* Set the boundary feature interpretation linked to this well marker.
		*/
		void setBoundaryFeatureInterpretation(class BoundaryFeatureInterpretation* interp);

		static const char* XML_TAG;
		virtual std::string getXmlTag() const {return XML_TAG;}

	private:

		// No need these three inherited methods since WellboreMarker is not an EPC top level element.
		std::vector<epc::Relationship> getAllSourceRelationships() const {std::vector<epc::Relationship> result; return result;}
		std::vector<epc::Relationship> getAllTargetRelationships() const {std::vector<epc::Relationship> result; return result;}
		void resolveTargetRelationships(COMMON_NS::EpcDocument* epcDoc) {};

		class BoundaryFeatureInterpretation* boundaryFeatureInterpretation;
		class WellboreMarkerFrameRepresentation* wellboreMarkerFrameRepresentation;
	};
}

