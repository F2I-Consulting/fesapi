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

#include "../resqml2/DeviationSurveyRepresentation.h"

/** . */
namespace RESQML2_0_1_NS
{
	/** A deviation survey representation. */
	class DeviationSurveyRepresentation final : public RESQML2_NS::DeviationSurveyRepresentation
	{
	public:

		/**
		 * Only to be used in partial transfer context
		 *
		 * @param [in,out]	partialObject	If non-null, the partial object.
		 */
		DLL_IMPORT_OR_EXPORT DeviationSurveyRepresentation(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : RESQML2_NS::DeviationSurveyRepresentation(partialObject) {}

		/**
		 * Creates an instance of this class in a gsoap context.
		 *
		 * @param [in,out]	interp 	The WellboreFeature interpretation the instance represents.
		 * @param 		  	guid   	The guid to set to the new instance. If empty then a new guid will be
		 * 							generated.
		 * @param 		  	title  	A title for the instance to create.
		 * @param 		  	isFinal	Used to indicate that this is a final version of the deviation survey,
		 * 							as distinct from the interim interpretations.
		 * @param [in,out]	mdInfo 	The MD information of the survey, mainly the well reference point.
		 */
		DeviationSurveyRepresentation(class RESQML2_NS::WellboreInterpretation * interp, const std::string & guid, const std::string & title, bool isFinal, RESQML2_NS::MdDatum * mdInfo);

		/**
		 * Creates an instance of this class by wrapping a gsoap instance.
		 *
		 * @param [in,out]	fromGsoap	If non-null, from gsoap.
		 */
		DeviationSurveyRepresentation(gsoap_resqml2_0_1::_resqml20__DeviationSurveyRepresentation* fromGsoap) : RESQML2_NS::DeviationSurveyRepresentation(fromGsoap) {}

		/** Destructor */
		~DeviationSurveyRepresentation() {}

		/*
		*  Set the geometry of the representation by means of a parametric line without MD information.
		* @param firstStationLocation			XYZ location of the first station of the deviation survey in the local CRS. It must be three doubles. It is not created and not deleted by this method.
		* @param stationCount					Number of stations (including the first station location).
		* @param mdUom							Units of measure of the measured depths along this deviation survey.
		* @param mds							MD values for the position of the stations. Array length equals station count.
		* @param angleUom						Defines the units of measure for the azimuth and inclination
		* @param azimuths						An array of azimuth angles, one for each survey station. The rotation is relative to the projected CRS north with a positive value indicating a clockwise rotation as seen from above. Array length equals station count.
		* @param inclinations					Dip (or inclination) angle for each station. Array length equals station count.
		* @param proxy							The HDF proxy which indicates in which HDF5 file the numerical values will be stored.
		*										It must be already opened for writing and won't be closed.
		*/
		DLL_IMPORT_OR_EXPORT void setGeometry(double const* firstStationLocation, ULONG64 stationCount,
			gsoap_resqml2_0_1::eml20__LengthUom mdUom, double const* mds,
			gsoap_resqml2_0_1::eml20__PlaneAngleUom angleUom, double const* azimuths, double const* inclinations,
			EML2_NS::AbstractHdfProxy* proxy) final;

		/**
		 * Set the Md datum of this trajectory
		 *
		 * @param [in,out]	mdDatum	If non-null, the md datum.
		 */
		DLL_IMPORT_OR_EXPORT void setMdDatum(RESQML2_NS::MdDatum * mdDatum) final;

		/**
		* @return	null pointer if no md datum is associated to this representation. Otherwise return the data object reference of the associated md datum.
		*/
		COMMON_NS::DataObjectReference getMdDatumDor() const final;

		/**
		* Used to indicate that this is a final version of the deviation survey, as distinct from the interim interpretations.
		*/
		DLL_IMPORT_OR_EXPORT bool isFinal() const final;

		/**
		 * Get the xyz point count in a given patch.
		 *
		 * @param 	patchIndex	Zero-based index of the patch.
		 *
		 * @returns	The xyz point count of patch.
		 */
		ULONG64 getXyzPointCountOfPatch(const unsigned int & patchIndex) const final;

		/**
		 * Get all the XYZ points of a particular patch of this representation. XYZ points are given in
		 * the local CRS.
		 *
		 * @param 		  	patchIndex	Zero-based index of the patch.
		 * @param [in,out]	xyzPoints 	A linearized 2d array where the first (quickest) dimension is
		 * 								coordinate dimension (XYZ) and second dimension is vertex
		 * 								dimension. It must be pre allocated.
		 */
		DLL_IMPORT_OR_EXPORT void getXyzPointsOfPatch(const unsigned int & patchIndex, double * xyzPoints) const final;

		/**
		 * Units of measure of the measured depths along this deviation survey.
		 *
		 * @returns	The md uom.
		 */
		DLL_IMPORT_OR_EXPORT gsoap_resqml2_0_1::eml20__LengthUom getMdUom() const final;

		/**
		 * Defines the units of measure for the azimuth and inclination
		 *
		 * @returns	The angle uom.
		 */
		gsoap_resqml2_0_1::eml20__PlaneAngleUom getAngleUom() const final;

		/**
		 * Getter of the md double values associated to each trajectory station of this WellboreFeature
		 * trajectory representation. Uom is given by getMdUom().
		 *
		 * @param [in,out]	values	It must preallocated with a count of getXyzPointCountOfPatch(0)
		 */
		DLL_IMPORT_OR_EXPORT void getMdValues(double* values) const final;

		/**
		 * Getter of the inclination double values associated to each trajectory station of this
		 * WellboreFeature trajectory representation. Uom is given by getAngleUom().
		 *
		 * @param [in,out]	values	It must preallocated with a count of getXyzPointCountOfPatch(0)
		 */
		DLL_IMPORT_OR_EXPORT void getInclinations(double* values) const final;

		/**
		 * Getter of the azimuth double values associated to each trajectory station of this
		 * WellboreFeature trajectory representation. The rotation is relative to the projected CRS
		 * north with a positive value indicating a clockwise rotation as seen from above. Uom is given
		 * by getAngleUom().
		 *
		 * @param [in,out]	values	It must preallocated with a count of getXyzPointCountOfPatch(0)
		 */
		DLL_IMPORT_OR_EXPORT void getAzimuths(double* values) const final;

		COMMON_NS::DataObjectReference getHdfProxyDor() const final;
	};
}
