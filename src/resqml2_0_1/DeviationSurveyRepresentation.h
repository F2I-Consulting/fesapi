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

#include "../resqml2/AbstractRepresentation.h"

namespace RESQML2_0_1_NS
{
	/**
	 * @brief	A deviation survey representation. It Specifies the station data from a deviation
	 * 			survey.
	 *
	 * 			The deviation survey does not provide a complete specification of the geometry of a
	 * 			wellbore trajectory. Although a minimum-curvature algorithm is used in most cases,
	 * 			the implementation varies sufficiently that no single algorithmic specification is
	 * 			available as a data transfer standard.
	 *
	 * 			Instead, the geometry of a RESQML wellbore trajectory is represented by a parametric
	 * 			line, parameterized by the MD.
	 *
	 * 			CRS and units of measure do not need to be consistent with the CRS and units of
	 * 			measure for wellbore trajectory representation.
	 */
	class DeviationSurveyRepresentation final : public RESQML2_NS::AbstractRepresentation
	{
	public:

		/**
		 * Only to be used in partial transfer context
		 *
		 * @param [in,out]	partialObject	If non-null, the partial object.
		 */
		DLL_IMPORT_OR_EXPORT DeviationSurveyRepresentation(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : RESQML2_NS::AbstractRepresentation(partialObject) {}

		/**
		 * @brief	Creates an instance of this class in a gsoap context.
		 *
		 * @exception	std::invalid_argument	If <tt>interp == nullptr</tt> or <tt>mdInfo ==
		 * 										nullptr</tt>.
		 *
		 * @param [in]	interp 	The WellboreFeature interpretation the instance represents.
		 * @param 	  	guid   	The guid to set to the new instance. If empty then a new guid will be
		 * 						generated.
		 * @param 	  	title  	A title for the instance to create.
		 * @param 	  	isFinal	Used to indicate that this is a final version of the deviation survey, as
		 * 						distinct from the interim interpretations.
		 * @param [in]	mdInfo 	The MD information of the survey, mainly the well reference point.
		 */
		DeviationSurveyRepresentation(class RESQML2_NS::WellboreInterpretation* interp, const std::string& guid, const std::string& title, bool isFinal, RESQML2_NS::MdDatum* mdInfo);

		/**
		 * Creates an instance of this class by wrapping a gsoap instance.
		 *
		 * @param [in,out]	fromGsoap	If non-null, from gsoap.
		 */
		DeviationSurveyRepresentation(gsoap_resqml2_0_1::_resqml20__DeviationSurveyRepresentation* fromGsoap) : RESQML2_NS::AbstractRepresentation(fromGsoap) {}

		/** Destructor */
		~DeviationSurveyRepresentation() = default;

		/**
		 * Sets the geometry of this deviation survey representation.
		 *
		 * @exception	std::invalid_argument	If @p firstStationLocation, @p mds, @p azimuths or @p
		 * 										inclinations is @ nullptr.
		 * @exception	std::invalid_argument	If <tt>proxy == nullptr</tt> and no default HDF proxy is
		 * 										defined in the repository.
		 *
		 * @param 		  	firstStationLocation	An array of size 3 containing the coordinates x, y
		 * 											and z of the first station of this deviation survey in
		 * 											the local CRS.
		 * @param 		  	stationCount			The number of stations (including the first station).
		 * @param 		  	mdUom					The units of measure of the measured depths along
		 * 											this deviation survey.
		 * @param 		  	mds						An array containing the MD values of the stations.
		 * 											The array length equals @p stationCount.
		 * @param 		  	angleUom				The unit of measure of both @p azimuth and
		 * 											@p inclination values.
		 * @param 		  	azimuths				An array of azimuth angles, one for each survey
		 * 											station. The rotation is relative to the projected CRS
		 * 											north with a positive value indicating a clockwise
		 * 											rotation as seen from above. Array length equals @p
		 * 											stationCount.
		 * @param 		  	inclinations			Inclination (or dip) angle for each station. Array
		 * 											length equals @p stationCount.
		 * @param [in,out]	proxy					The HDF proxy where the numerical values will be
		 * 											stored. It must be already opened for writing and won't
		 * 											be closed. If @c nullptr, then the default HDF proxy of
		 * 											the repository will be used.
		 */
		DLL_IMPORT_OR_EXPORT void setGeometry(double const* firstStationLocation, uint64_t stationCount,
			gsoap_resqml2_0_1::eml20__LengthUom mdUom, double const* mds,
			gsoap_resqml2_0_1::eml20__PlaneAngleUom angleUom, double const* azimuths, double const* inclinations,
			EML2_NS::AbstractHdfProxy* proxy);

		/**
		 * Sets the MD datum of this deviation survey representation.
		 *
		 * @exception	std::invalid_argument	If <tt>mdDatum == nullptr</tt>.
		 *
		 * @param [in]	mdDatum	The MD datum to set.
		 */
		DLL_IMPORT_OR_EXPORT void setMdDatum(RESQML2_NS::MdDatum* mdDatum);

		/**
		 * Gets the DOR of the MD datum of this deviation survey representation.
		 *
		 * @return	The DOR of the MD datum of this deviation survey representation.
		 */
		COMMON_NS::DataObjectReference getMdDatumDor() const;

		/**
		 * Gets the MD datum of this deviation survey representation.
		 *
		 * @returns The MD datum of this deviation survey representation.
		 */
		DLL_IMPORT_OR_EXPORT RESQML2_NS::MdDatum* getMdDatum() const;

		/**
		 * Checks whether this is a final version of the deviation survey, as distinct from the
		 * interim interpretations.
		 *
		 * @returns	True if it is a final version, false if not.
		 */
		DLL_IMPORT_OR_EXPORT bool isFinal() const;

		uint64_t getXyzPointCountOfPatch(uint64_t patchIndex) const final;

		DLL_IMPORT_OR_EXPORT void getXyzPointsOfPatch(uint64_t patchIndex, double* xyzPoints) const final;

		/**
		 * Gets the unit of measure of the MDs along this deviation survey.
		 *
		 * @returns	The unit of measure of the MDs.
		 */
		DLL_IMPORT_OR_EXPORT gsoap_resqml2_0_1::eml20__LengthUom getMdUom() const;

		/**
		 * Gets the unit of measure of the azimuth and inclination angle values of this deviation survey.
		 *
		 * @returns	The unit of measure of the azimuth and inclination angle values.
		 */
		DLL_IMPORT_OR_EXPORT gsoap_resqml2_0_1::eml20__PlaneAngleUom getAngleUom() const;

		/**
		 * Gets the MD double values associated to each trajectory station of this deviation survey
		 * representation. The uom is given by getMdUom().
		 *
		 * @exception	logic_error	If the data structure used to store the MD values cannot be read for
		 * 							now by fesapi.
		 *
		 * @param [out]	values	An array to receive the MD double values. It must preallocated with a
		 * 						count of <tt>getXyzPointCountOfPatch(0)</tt>.
		 */
		DLL_IMPORT_OR_EXPORT void getMdValues(double* values) const;

		/**
		 * Gets the inclination double values associated to each trajectory station of this deviation
		 * survey representation. The uom is given by getAngleUom().
		 *
		 * @exception	logic_error	If the data structure used to store the inclination values cannot be
		 * 							read for now by fesapi.
		 *
		 * @param [out]	values	An array to receive the inclination double values. It must preallocated
		 * 						with a count of <tt>getXyzPointCountOfPatch(0)</tt>.
		 */
		DLL_IMPORT_OR_EXPORT void getInclinations(double* values) const;

		/**
		 * Gets the azimuth double values associated to each trajectory station of this deviation survey
		 * representation. The rotation is relative to the projected CRS north with a positive value
		 * indicating a clockwise rotation as seen from above. The uom is given by getAngleUom().
		 *
		 * @exception	logic_error	If the data structure used to store the azimuth values cannot be read
		 * 							for now by fesapi.
		 *
		 * @param [out]	values	An array to receive the azimuth double values. It must preallocated with
		 * 						a count of <tt>getXyzPointCountOfPatch(0)</tt>.
		 */
		DLL_IMPORT_OR_EXPORT void getAzimuths(double* values) const;

		/**
		 * Gets all the wellbore frame representations of the associated wellbore trajectory which share
		 * the same MD datum and MD uom than this deviation survey representation.
		 *
		 * @returns	The vector of all the wellbore frame representations of the associated wellbore
		 * 			trajectory which share the same MD datum and MD uom than this deviation survey
		 * 			representation.
		 */
		DLL_IMPORT_OR_EXPORT std::vector<RESQML2_NS::WellboreFrameRepresentation*> getWellboreFrameRepresentationSet() const;

		/**
		 * Gets the count of wellbore frame representations of the associated wellbore trajectory which
		 * share the same MD datum and MD uom than this deviation survey representation.
		 *
		 * @returns	The the count of wellbore frame representations of the associated wellbore trajectory
		 * 			which share the same MD datum and MD uom than this deviation survey representation.
		 */
		DLL_IMPORT_OR_EXPORT uint64_t getWellboreFrameRepresentationCount() const; // It is mainly used in SWIG context for parsing the vector from a non C++ language.

		/**
		 * Gets a particular wellbore frame representation according to its position in the set of all
		 * the wellbore frame representations of the associated wellbore trajectory which share the same
		 * MD datum and MD uom than this deviation survey representation.
		 *
		 * @exception std::invalid_argument If <tt>index >=  getWellboreFrameRepresentationCount()</tt>.
		 *
		 * @param index Zero-based index of the wellbore frame representation we look for.
		 *
		 * @returns The wellbore frame representation at position @p index in the set of all the wellbore
		 * 			frame representations of the associated wellbore trajectory which share the same MD
		 * 			datum and MD uom than this deviation survey representation.
		 */
		DLL_IMPORT_OR_EXPORT class RESQML2_NS::WellboreFrameRepresentation* getWellboreFrameRepresentation(uint64_t index) const; // It is mainly used in SWIG context for parsing the vector from a non C++ language.

		/**
		 * Gets all the wellbore trajectories which are associated to this deviation survey
		 * representation.
		 *
		 * @returns	The vector of all the associated wellbore trajectories.
		 */
		DLL_IMPORT_OR_EXPORT std::vector<RESQML2_NS::WellboreTrajectoryRepresentation*> getWellboreTrajectoryRepresentationSet() const;

		/**
		 * Get the count of wellbore trajectories which are associated to this deviation survey.
		 *
		 * @exception	std::range_error	If the count of wellbore trajectories is strictly greater
		 * 									than unsigned int max.
		 *
		 * @returns	The count of associated wellbore trajectories.
		 */
		DLL_IMPORT_OR_EXPORT uint64_t getWellboreTrajectoryRepresentationCount() const; // It is mainly used in SWIG context for parsing the vector from a non C++ language.

		/**
		 * Gets the associated wellbore trajectory at a particular position.
		 *
		 * @exception std::out_of_range If <tt>index >= getWellboreTrajectoryRepresentationCount()</tt>.
		 *
		 * @param index Zero-based index of the wellbore trajectory we look for.
		 *
		 * @returns The associated wellbore trajectory at position @p index.
		 */
		DLL_IMPORT_OR_EXPORT RESQML2_NS::WellboreTrajectoryRepresentation* getWellboreTrajectoryRepresentation(uint64_t index) const; // It is mainly used in SWIG context for parsing the vector from a non C++ language.

		COMMON_NS::DataObjectReference getHdfProxyDor() const;

		DLL_IMPORT_OR_EXPORT uint64_t getPatchCount() const final { return 1; }

		/** The standard XML tag without XML namespace for serializing this data object. */
		DLL_IMPORT_OR_EXPORT static constexpr char const* XML_TAG = "DeviationSurveyRepresentation";

		DLL_IMPORT_OR_EXPORT virtual std::string getXmlTag() const final { return XML_TAG; }

		/**
		* The standard XML namespace for serializing this data object.
		*/
		DLL_IMPORT_OR_EXPORT static constexpr char const* XML_NS = "resqml20";

		/**
		* Get the standard XML namespace for serializing this data object.
		*/
		DLL_IMPORT_OR_EXPORT std::string getXmlNamespace() const final { return XML_NS; }

	private:

		/** Loads target relationships */
		void loadTargetRelationships();
	};
}
