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
#include "AbstractValuesProperty.h"

namespace RESQML2_NS
{
	/**
	 * @brief	Proxy class for a wellbore frame representation. A wellbore frame representation is a
	 * 			representation of a wellbore that is organized along a wellbore trajectory by its MD
	 * 			values. 
	 * 			
	 *			RESQML uses MD values to associate properties on points and to organize
	 * 			association of properties on intervals between MD points.
	 */
	class WellboreFrameRepresentation : public AbstractRepresentation
	{
	public:
		/** Destructor does nothing since the memory is managed by the gSOAP context. */
		~WellboreFrameRepresentation() = default;

		/**
		 * Sets the measured depth (MD) values of this wellbore frame representation as a 1d array of explicit values.
		 *
		 * @exception	std::logic_error	 	If the underlying gSOAP instance is not a RESQML2.0 one.
		 * @exception	std::invalid_argument	If @p proxy is @c nullptr and no default HDF proxy is
		 * 										defined in the repository.
		 *
		 * @param 		  	mdValues		All the MD values to set from top to bottom of the wellbore
		 * 									trajectory. Size if @p mdValueCount.
		 * @param 		  	mdValueCount	The MD values count.
		 * @param [in,out]	proxy			(Optional) The HDF proxy where to write the MD values. It
		 * 									must be already opened for writing and won't be closed in this
		 * 									method. If @c nullptr, then a default HDF proxy must be defined
		 * 									in the repository.
		 */
		DLL_IMPORT_OR_EXPORT void setMdValues(double const * mdValues, unsigned int mdValueCount, EML2_NS::AbstractHdfProxy* proxy = nullptr);

		/**
		 * Sets the measured depth (MD) values of this wellbore frame representation as a regular
		 * discretization along the wellbore trajectory.
		 *
		 * @exception	std::logic_error	If the underlying gSOAP instance is not a RESQML2.0 one.
		 *
		 * @param 	firstMdValue		The first MD value.
		 * @param 	incrementMdValue	The increment value between two MDs.
		 * @param 	mdValueCount		The count of MD values in this wellbore frame representation.
		 */
		DLL_IMPORT_OR_EXPORT void setMdValues(double firstMdValue, double incrementMdValue, unsigned int mdValueCount);

		/**
		 * Indicates either the MDs are regularly spaced or not (useful for optimization). Does not
		 * check the regularity if the writer has used a generic array to store regular MDs.
		 *
		 * @exception	std::logic_error	If the underlying gSOAP instance is not a RESQML2.0 one.
		 *
		 * @returns	True if MD values are regularly spaced, false if not.
		 */
		DLL_IMPORT_OR_EXPORT bool areMdValuesRegularlySpaced() const;

		/**
		 * Indicates the increment value between two MDs in case of regularly spaced MDs. Please check
		 * the regularity of MDs with areMdValuesRegularlySpaced() before using this method.
		 *
		 * @exception	std::logic_error	 	If the underlying gSOAP instance is not a RESQML2.0 one.
		 * @exception	std::invalid_argument	If the MD values are not regularly spaced.
		 *
		 * @returns	The MD constant increment value.
		 */
		DLL_IMPORT_OR_EXPORT double getMdConstantIncrementValue() const;

		/**
		 * Returns the first MD value of this wellbore frame representation.
		 *
		 * @exception	std::logic_error	 	If the underlying gSOAP instance is not a RESQML2.0 one.
		 * @exception	std::logic_error	 	If the MD values are neither stored in a HDF5 double
		 * 										array nor in a double lattice array.
		 * @exception	std::invalid_argument	If the MD values are stored in a HDF5 double array and
		 * 										the HDF proxy is missing.
		 *
		 * @returns	The first MD value.
		 */
		DLL_IMPORT_OR_EXPORT double getMdFirstValue() const;

		/**
		 * Gets the number of MD values in this wellbore frame representation.
		 *
		 * @exception	std::logic_error	If the underlying gSOAP instance is not a RESQML2.0 one.
		 *
		 * @returns	The MD values count.
		 */
		DLL_IMPORT_OR_EXPORT unsigned int getMdValuesCount() const;

		/**
		* Get the xyz point count in a given patch.
		*/
		DLL_IMPORT_OR_EXPORT uint64_t getXyzPointCountOfPatch(unsigned int patchIndex) const override;

		/**
		* Use linear interpolation between 2 trajectory stations.
		*/
		DLL_IMPORT_OR_EXPORT void getXyzPointsOfPatch(unsigned int patchIndex, double * xyzPoints) const override;

		/**
		 * Gets the MD datatype in the HDF dataset.
		 *
		 * @exception	std::logic_error	 	If the underlying gSOAP instance is not a RESQML2.0 one.
		 * @exception	std::invalid_argument	If the MD values are stored in a HDF5 double array and
		 * 										the HDF proxy is missing.
		 *
		 * @returns	The MD datatype in the HDF dataset if MD values are actually stored in a HDF dataset.
		 * 			Returns @c DOUBLE if MD values are stored as a regular discretization along the
		 * 			wellbore trajectory.
		 */
		DLL_IMPORT_OR_EXPORT COMMON_NS::AbstractObject::hdfDatatypeEnum getMdHdfDatatype() const;

		/**
		 * Gets all the MD values of this instance which are supposed to be double ones.
		 *
		 * @exception	std::logic_error	 	If the underlying gSOAP instance is not a RESQML2.0 one.
		 * @exception	std::logic_error	 	If the MD values are neither stored in a HDF5 double
		 * 										array nor in a double lattice array.
		 * @exception	std::invalid_argument	If the MD values are stored in a HDF5 double array and
		 * 										the HDF proxy is missing.
		 *
		 * @param [out]	values	A buffer to receive the MD values ordered from top to bottom of the
		 * 						wellbore trajectory. It must be preallocated with size of
		 * 						getMdValuesCount().
		 */
		DLL_IMPORT_OR_EXPORT void getMdAsDoubleValues(double * values) const;

		/**
		 * Gets all the MD values of this instance which are supposed to be float ones.
		 *
		 * @exception	std::logic_error	 	If the underlying gSOAP instance is not a RESQML2.0 one.
		 * @exception	std::logic_error	 	If the MD values are neither stored in a HDF5 double
		 * 										array nor in a double lattice array.
		 * @exception	std::invalid_argument	If the MD values are stored in a HDF5 double array and
		 * 										the HDF proxy is missing.
		 *
		 * @param [out]	values	A buffer to receive the MD values ordered from top to bottom of the
		 * 						wellbore trajectory. It must be preallocated with size of
		 * 						getMdValuesCount().
		 */
		DLL_IMPORT_OR_EXPORT void getMdAsFloatValues(float * values) const;

		/**
		 * Gets the data object reference of the associated RESQML wellbore trajectory.
		 *
		 * @exception	std::logic_error	If the underlying gSOAP instance is not a RESQML2.0 one.
		 *
		 * @returns	The data object reference of the associated RESQML wellbore trajectory.
		 */
		COMMON_NS::DataObjectReference getWellboreTrajectoryDor() const;

		/** 
		 * Gets the associated RESQML wellbore trajectory. 
		 *
		 * @exception	std::logic_error	If the underlying gSOAP instance is not a RESQML2.0 one.
		 * 
		 * @return The associated RESQML wellbore trajectory.
		 */
		DLL_IMPORT_OR_EXPORT class WellboreTrajectoryRepresentation* getWellboreTrajectory() const;

		COMMON_NS::DataObjectReference getLocalCrsDor(unsigned int patchIndex) const override;

		/**
		 * @copybrief AbstractRepresentation::getHdfProxyDor()
		 *
		 * @exception	std::logic_error	If the underlying gSOAP instance is not a RESQML v2.0 or RESQML v2.0 one.
		 * 
		 * @copydetails AbstractRepresentation::getHdfProxyDor()
		 */
		COMMON_NS::DataObjectReference getHdfProxyDor() const final;

		DLL_IMPORT_OR_EXPORT unsigned int getPatchCount() const final {return 1;}

	protected:
		/** Default constructor */
		WellboreFrameRepresentation() {}

		/**
		* Only to be used in partial transfer context
		*
		* @param [in,out]	partialObject	If non-null, the partial object.
		*/
		WellboreFrameRepresentation(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) :
			RESQML2_NS::AbstractRepresentation(partialObject) {}

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*
		* @param [in,out]	fromGsoap	If non-null, from gsoap.
		*/
		WellboreFrameRepresentation(gsoap_resqml2_0_1::_resqml20__WellboreFrameRepresentation* fromGsoap) :
			AbstractRepresentation(fromGsoap) {}

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*
		* @param [in,out]	fromGsoap	If non-null, from gsoap.
		*/
		WellboreFrameRepresentation(gsoap_eml2_3::resqml22__WellboreFrameRepresentation* fromGsoap) :
			AbstractRepresentation(fromGsoap) {}

		/** Loads target relationships */
		virtual void loadTargetRelationships() override;
	};
}
