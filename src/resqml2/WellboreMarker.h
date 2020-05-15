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

namespace RESQML2_NS
{
	class BoundaryFeatureInterpretation;
	class WellboreMarkerFrameRepresentation;

	/**
	 * @brief	Representation of a wellbore marker that is located along a wellbore trajectory, one
	 * 			for each MD value in the wellbore frame.
	 *
	 * 			BUSINESS RULE: Ordering of the wellbore markers must match the ordering of the nodes
	 * 			in the wellbore marker frame representation.
	 */
	class WellboreMarker : public COMMON_NS::AbstractObject
	{
	public:

		/** Destructor does nothing since the memory is managed by the gSOAP context. */
		virtual ~WellboreMarker() {}

		/**
		 * Indicates if the marker is associated to a particular geologic boundary kind.
		 *
		 * @returns	True if the marker is associated to a particular geologic boundary kind, false if not.
		 */
		DLL_IMPORT_OR_EXPORT virtual bool hasAGeologicBoundaryKind() const = 0;

		/**
		 * Gets the type of the intersected feature of the marker.
		 *
		 * @exception	std::invalid_argument	If the marker has no geologic boundary kind (see method
		 * 										hasAGeologicBoundaryKind()).
		 *
		 * @returns	The geologic boundary kind associated to this marker.
		 */
		DLL_IMPORT_OR_EXPORT virtual gsoap_resqml2_0_1::resqml20__GeologicBoundaryKind getGeologicBoundaryKind() const = 0;

		/** Gets the wellbore marker frame representation which contains this wellbore marker.
		 *
		 * @returns The wellbore marker frame representation which contains this wellbore marker frame, or @c nullptr if it fails.
		 */
		DLL_IMPORT_OR_EXPORT WellboreMarkerFrameRepresentation const * getWellboreMarkerFrameRepresentation() const;

		/** Gets the boundary feature interpretation linked to this well marker.
		 * @returns The boundary feature interpretation linked to this well marker, or @c nullptr if it fails.
		 */
		DLL_IMPORT_OR_EXPORT BoundaryFeatureInterpretation* getBoundaryFeatureInterpretation() const;

		/**
		 * Gets the UUID of the boundary feature interpretation linked to this well marker. Especially
		 * useful in partial transfer mode.
		 *
		 * @returns	The boundary feature interpretation UUID, or empty string if it fails.
		 */
		DLL_IMPORT_OR_EXPORT virtual COMMON_NS::DataObjectReference getBoundaryFeatureInterpretationDor() const = 0;

		/**
		 * Sets the boundary feature interpretation linked to this well marker.
		 *
		 * @exception	std::invalid_argument	If @p interp is @c nullptr.
		 *
		 * @param [in]	interp	The boundary feature interpretation to link to this well marker. It
		 * 						cannot be null.
		 */
		DLL_IMPORT_OR_EXPORT virtual void setBoundaryFeatureInterpretation(BoundaryFeatureInterpretation* interp) = 0;

		/** The standard XML tag without XML namespace for serializing this data object. */
		DLL_IMPORT_OR_EXPORT static const char* XML_TAG;

		DLL_IMPORT_OR_EXPORT virtual std::string getXmlTag() const final { return XML_TAG; }

	protected:

		/**
		 * Default constructor
		 */
		DLL_IMPORT_OR_EXPORT WellboreMarker() {}

		/**
		 * Creates an instance of this class by wrapping a gSOAP instance.
		 *
		 * @param [in]	fromGsoap	If non-null, the gSOAP instance.
		 */
		WellboreMarker(gsoap_resqml2_0_1::resqml20__WellboreMarker* fromGsoap) : AbstractObject(fromGsoap) {}

		/**
		 * Creates an instance of this class by wrapping a gSOAP instance.
		 *
		 * @param [in]	fromGsoap	If non-null, the gSOAP instance.
		 */
		WellboreMarker(gsoap_eml2_3::resqml22__WellboreMarker* fromGsoap) : AbstractObject(fromGsoap) {}

		/** Loads target relationships */
		void loadTargetRelationships() final {}
	};
}
