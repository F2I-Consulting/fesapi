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

#include "AbstractRepresentation.h"

/** . */
namespace RESQML2_NS
{
	/** A deviation survey representation. */
	class DeviationSurveyRepresentation : public AbstractRepresentation
	{
	public:

		/** Destructor */
		virtual ~DeviationSurveyRepresentation() {}

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
		DLL_IMPORT_OR_EXPORT virtual void setGeometry(double const* firstStationLocation, ULONG64 stationCount,
			gsoap_resqml2_0_1::eml20__LengthUom mdUom, double const* mds,
			gsoap_resqml2_0_1::eml20__PlaneAngleUom angleUom, double const* azimuths, double const* inclinations,
			EML2_NS::AbstractHdfProxy* proxy) = 0;

		/**
		 * Set the Md datum of this trajectory
		 *
		 * @param [in,out]	mdDatum	If non-null, the md datum.
		 */
		DLL_IMPORT_OR_EXPORT virtual void setMdDatum(RESQML2_NS::MdDatum * mdDatum) = 0;

		/**
		* @return	null pointer if no md datum is associated to this representation. Otherwise return the data object reference of the associated md datum.
		*/
		virtual COMMON_NS::DataObjectReference getMdDatumDor() const = 0;

		/**
		 * Getter of the md information associated to this WellboreFeature trajectory representation.
		 *
		 * @returns	Null if it fails, else the md datum.
		 */
		DLL_IMPORT_OR_EXPORT class MdDatum* getMdDatum() const;

		/**
		* Used to indicate that this is a final version of the deviation survey, as distinct from the interim interpretations.
		*/
		DLL_IMPORT_OR_EXPORT virtual bool isFinal() const = 0;

		/**
		 * Units of measure of the measured depths along this deviation survey.
		 *
		 * @returns	The md uom.
		 */
		DLL_IMPORT_OR_EXPORT virtual gsoap_resqml2_0_1::eml20__LengthUom getMdUom() const = 0;

		/**
		 * Defines the units of measure for the azimuth and inclination
		 *
		 * @returns	The angle uom.
		 */
		virtual gsoap_resqml2_0_1::eml20__PlaneAngleUom getAngleUom() const = 0;

		/**
		 * Getter of the md double values associated to each trajectory station of this WellboreFeature
		 * trajectory representation. Uom is given by getMdUom().
		 *
		 * @param [in,out]	values	It must preallocated with a count of getXyzPointCountOfPatch(0)
		 */
		DLL_IMPORT_OR_EXPORT virtual void getMdValues(double* values) const = 0;

		/**
		 * Getter of the inclination double values associated to each trajectory station of this
		 * WellboreFeature trajectory representation. Uom is given by getAngleUom().
		 *
		 * @param [in,out]	values	It must preallocated with a count of getXyzPointCountOfPatch(0)
		 */
		DLL_IMPORT_OR_EXPORT virtual void getInclinations(double* values) const = 0;

		/**
		 * Getter of the azimuth double values associated to each trajectory station of this
		 * WellboreFeature trajectory representation. The rotation is relative to the projected CRS
		 * north with a positive value indicating a clockwise rotation as seen from above. Uom is given
		 * by getAngleUom().
		 *
		 * @param [in,out]	values	It must preallocated with a count of getXyzPointCountOfPatch(0)
		 */
		DLL_IMPORT_OR_EXPORT virtual void getAzimuths(double* values) const = 0;

		/**
		 * Getter of all the wellbore frame representations of associated wellbore trajectory which
		 * share the same md datum and md uom.
		 *
		 * @returns	Null if it fails, else the wellbore frame representation set.
		 */
		DLL_IMPORT_OR_EXPORT std::vector<class RESQML2_NS::WellboreFrameRepresentation *> getWellboreFrameRepresentationSet() const;

		/**
		 * Get the count of all the wellbore frame representations of associated wellbore trajectory
		 * which share the same md datum and md uom. Necessary for now in SWIG context because I am not
		 * sure if I can always wrap a vector of polymorphic class yet.
		 *
		 * @returns	The wellbore frame representation count.
		 */
		DLL_IMPORT_OR_EXPORT unsigned int getWellboreFrameRepresentationCount() const;

		/**
		 * Get a particular wellbore frame representation according to its position. Necessary for now
		 * in SWIG context because I am not sure if I can always wrap a vector of polymorphic class yet.
		 * Throw an out of bound exception if the index is superior or equal to the count of wellbore
		 * frame representation.
		 */
		DLL_IMPORT_OR_EXPORT class RESQML2_NS::WellboreFrameRepresentation * getWellboreFrameRepresentation(unsigned int index) const;

		/**
		 * Getter (in read only mode) of all the wellbore trajectories which are associated to this
		 * deviation survey.
		 *
		 * @returns	Null if it fails, else the wellbore trajectory representation set.
		 */
		DLL_IMPORT_OR_EXPORT std::vector<class WellboreTrajectoryRepresentation *> getWellboreTrajectoryRepresentationSet() const;

		/**
		 * Get the count of all the wellbore trajectories which are associated to this deviation survey.
		 * Necessary for now in SWIG context because I am not sure if I can always wrap a vector of
		 * polymorphic class yet.
		 *
		 * @returns	The wellbore trajectory representation count.
		 */
		DLL_IMPORT_OR_EXPORT unsigned int getWellboreTrajectoryRepresentationCount() const;

		/**
		 * Get a particular wellbore trajectory according to its position. Necessary for now in SWIG
		 * context because I am not sure if I can always wrap a vector of polymorphic class yet. Throw
		 * an out of bound exception if the index is superior or equal to the count of wellbore frame
		 * representation.
		 */
		DLL_IMPORT_OR_EXPORT class WellboreTrajectoryRepresentation * getWellboreTrajectoryRepresentation(unsigned int index) const;

		/**
		 * Gets patch count
		 *
		 * @returns	The patch count.
		 */
		DLL_IMPORT_OR_EXPORT unsigned int getPatchCount() const {return 1;}

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

	protected:

		/**
		 * Only to be used in partial transfer context
		 *
		 * @param [in,out]	partialObject	If non-null, the partial object.
		 *
		 * @returns	A DLL_IMPORT_OR_EXPORT.
		 */
		DLL_IMPORT_OR_EXPORT DeviationSurveyRepresentation(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : AbstractRepresentation(partialObject) {}

		/**
		 * Default constructor
		 */
		DeviationSurveyRepresentation() {}

		/**
		 * Creates an instance of this class by wrapping a gsoap instance.
		 *
		 * @param [in,out]	fromGsoap	If non-null, from gsoap.
		 */
		DeviationSurveyRepresentation(gsoap_resqml2_0_1::_resqml20__DeviationSurveyRepresentation* fromGsoap) : AbstractRepresentation(fromGsoap) {}

		/**
		 * Creates an instance of this class by wrapping a gsoap instance.
		 *
		 * @param [in,out]	fromGsoap	If non-null, from gsoap.
		 */
		DeviationSurveyRepresentation(gsoap_eml2_3::_resqml22__DeviationSurveyRepresentation* fromGsoap) : AbstractRepresentation(fromGsoap) {}

		/** Loads target relationships */
		void loadTargetRelationships();
	};
}
