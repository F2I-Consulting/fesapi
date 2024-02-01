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

namespace WITSML2_1_NS
{
	class WellboreMarker;
}

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
		virtual ~WellboreMarker() = default;

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
		 * Gets the DOR of the boundary feature interpretation linked to this well marker. Especially
		 * useful in partial transfer mode.
		 *
		 * @returns	The boundary feature interpretation DOR, or empty DOR if it fails.
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

		/**
		 * Gets the WITSML wellbore marker associated to this wellbore marker.
		 *
		 * @exception	std::logic_error	If more than one WITSML wellbore marker is associated to this
		 * 									wellbore feature.
		 *
		 * @returns	@c nullptr if no WITSML wellbore marker is associated to this wellbore marker, else the
		 * 			associated WITSML wellbore marker.
		 */
		DLL_IMPORT_OR_EXPORT WITSML2_1_NS::WellboreMarker* getWitsmlWellboreMarker() const;

		/**
		 * Gets the DOR of the WITSML wellbore marker linked to this well marker. Especially
		 * useful in partial transfer mode.
		 *
		 * @returns	The WITSML wellbore marker DOR, or empty DOR if it fails.
		 */
		DLL_IMPORT_OR_EXPORT virtual COMMON_NS::DataObjectReference getWitsmlWellboreMarkerDor() const = 0;

		/**
		 * Sets the WITSML wellbore marker associated to this instance.
		 *
		 * @exception	std::invalid_argument	If the WITSML wellbore marker to set is NULL.
		 *
		 * @param [in]	wellbore	The WITSML wellbore marker to associate to this wellbore. It cannot be null.
		 */
		DLL_IMPORT_OR_EXPORT virtual void setWitsmlWellboreMarker(WITSML2_1_NS::WellboreMarker * wellboreMarker) = 0;

		/**
		 * Check wether this marker has got a dip angle or not.
		 * FYI, Dip Angle is store in the WITSML WellboreMarker companion if present.
		 *
		 * @return true if this marker has got a dip angle. 
		 */
		DLL_IMPORT_OR_EXPORT bool hasDipAngle() const;

		/**
		 * Get the Dip angle value.
		 *
		 * @exception	std::logic_error	If the marker has not got any dip value.
		 *
		 * @return the Dip angle value.
		 */
		DLL_IMPORT_OR_EXPORT double getDipAngleValue() const;

		/**
		 * Get the Dip angle uom.
		 *
		 * @exception	std::logic_error	If the marker has not got any dip value.
		 *
		 * @return the Dip angle uom.
		 */
		DLL_IMPORT_OR_EXPORT gsoap_eml2_3::eml23__PlaneAngleUom getDipAngleUom() const;

		/**
		 * Get the Dip angle uom as a string.
		 *
		 * @exception	std::logic_error	If the marker has not got any dip value.
		 *
		 * @return the Dip angle uom as a string.
		 */
		DLL_IMPORT_OR_EXPORT std::string getDipAngleUomAsString() const;

		/**
		 * Check wether this marker has got a dip direction or not.
		 * FYI, Dip direction is store in the WITSML WellboreMarker companion if present.
		 *
		 * @return true if this marker has got a dip direction.
		 */
		DLL_IMPORT_OR_EXPORT bool hasDipDirection() const;

		/**
		 * Get the Dip direction value.
		 *
		 * @exception	std::logic_error	If the marker has not got any dip direction.
		 *
		 * @return the Dip direction value.
		 */
		DLL_IMPORT_OR_EXPORT double getDipDirectionValue() const;

		/**
		 * Get the Dip direction uom.
		 *
		 * @exception	std::logic_error	If the marker has not got any dip direction.
		 *
		 * @return the Dip direction uom.
		 */
		DLL_IMPORT_OR_EXPORT gsoap_eml2_3::eml23__PlaneAngleUom getDipDirectionUom() const;

		/**
		 * Get the Dip direction uom as a string.
		 *
		 * @exception	std::logic_error	If the marker has not got any dip direction.
		 *
		 * @return the Dip direction uom as a string.
		 */
		DLL_IMPORT_OR_EXPORT std::string getDipDirectionUomAsString() const;

		/** The standard XML tag without XML namespace for serializing this data object. */
		DLL_IMPORT_OR_EXPORT static constexpr char const* XML_TAG = "WellboreMarker";

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

		/** Loads target relationships */
		void loadTargetRelationships() final;
	};
}
