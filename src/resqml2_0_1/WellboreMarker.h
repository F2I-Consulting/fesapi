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

#include "../common/AbstractObject.h"

/** . */
namespace RESQML2_0_1_NS
{
	/**
	 * This class is one of the only one to be a ResqmlDataObject which is not exported into a
	 * single file i.e. not a top level element. Consequently its behaviour is slightly different
	 * than other class. Especially there is no integration of the instances into an EPC document.
	 */
	class WellboreMarker : public COMMON_NS::AbstractObject
	{
	public:

		/**
		 * Creates an instance of this class in a gsoap context.
		 *
		 * @param [in,out]	wellboreMarkerFrame	The wellbore marker frame which contains the wellbore
		 * 										marker to contruct.
		 * @param 		  	guid			   	The guid to set to the new instance. If empty then a new
		 * 										guid will be generated.
		 * @param 		  	title			   	A title for the instance to create.
		 *
		 * @returns	A DLL_IMPORT_OR_EXPORT.
		 */
		DLL_IMPORT_OR_EXPORT WellboreMarker(class WellboreMarkerFrameRepresentation* wellboreMarkerFrame, const std::string & guid, const std::string & title);

		/**
		 * Creates an instance of this class in a gsoap context.
		 *
		 * @param [in,out]	wellboreMarkerFrame 	The wellbore marker frame which contains the wellbore
		 * 											marker to contruct.
		 * @param 		  	guid					The guid to set to the new instance. If empty then a
		 * 											new guid will be generated.
		 * @param 		  	title					A title for the instance to create.
		 * @param 		  	geologicBoundaryKind	The type of the feature which the marker intersects.
		 *
		 * @returns	A DLL_IMPORT_OR_EXPORT.
		 */
		DLL_IMPORT_OR_EXPORT WellboreMarker(class WellboreMarkerFrameRepresentation* wellboreMarkerFrame, const std::string & guid, const std::string & title, gsoap_resqml2_0_1::resqml20__GeologicBoundaryKind geologicBoundaryKind);

		/**
		 * Creates an instance of this class by wrapping a gsoap instance.
		 *
		 * @param [in,out]	fromGsoap	If non-null, from gsoap.
		 */
		WellboreMarker(gsoap_resqml2_0_1::resqml20__WellboreMarker* fromGsoap) : AbstractObject(fromGsoap)  {}

		/** Destructor */
		DLL_IMPORT_OR_EXPORT ~WellboreMarker() {}

		/**
		 * Indicates if the marker is associated to a particular GeologicBoundaryKind.
		 *
		 * @returns	True if a geologic boundary kind, false if not.
		 */
		DLL_IMPORT_OR_EXPORT bool hasAGeologicBoundaryKind() const;

		/**
		 * Get the type of the intersected feature of the marker. Throw an exception if the marker has
		 * no GeologicBoundaryKind (see method hasAGeologicBoundaryKind).
		 *
		 * @returns	The geologic boundary kind.
		 */
		DLL_IMPORT_OR_EXPORT gsoap_resqml2_0_1::resqml20__GeologicBoundaryKind getGeologicBoundaryKind() const;

		/** A wellbore marker frame representation. */
		DLL_IMPORT_OR_EXPORT class WellboreMarkerFrameRepresentation const * getWellMarkerFrameRepresentation() const;

		/** Get the boundary feature interpretation linked to this well marker. */
		DLL_IMPORT_OR_EXPORT class BoundaryFeatureInterpretation* getBoundaryFeatureInterpretation() const;

		/**
		 * Get the UUID of the boundary feature interpretation linked to this well marker. Especially
		 * useful in partial transfer mode.
		 *
		 * @returns	The boundary feature interpretation uuid.
		 */
		DLL_IMPORT_OR_EXPORT std::string getBoundaryFeatureInterpretationUuid() const;

		/**
		 * Set the boundary feature interpretation linked to this well marker.
		 *
		 * @param [in,out]	interp	If non-null, the interp.
		 */
		DLL_IMPORT_OR_EXPORT void setBoundaryFeatureInterpretation(class BoundaryFeatureInterpretation* interp);

		/**
		 * The standard XML tag without XML namespace for serializing this data object.
		 *
		 * @returns	The XML tag.
		 */
		DLL_IMPORT_OR_EXPORT static const char* XML_TAG;

		/**
		 * Get the standard XML tag without XML namespace for serializing this data object.
		 *
		 * @returns	The XML tag.
		 */
		DLL_IMPORT_OR_EXPORT virtual std::string getXmlTag() const { return XML_TAG; }

	private:
		/** Loads target relationships */
		void loadTargetRelationships();
	};
}
