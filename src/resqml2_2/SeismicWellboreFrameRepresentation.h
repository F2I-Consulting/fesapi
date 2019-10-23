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

#include "resqml2_2/WellboreFrameRepresentation.h"

namespace RESQML2_0_1_NS
{
	class WellboreInterpretation;
	class WellboreTrajectoryRepresentation;
	class LocalTime3dCrs;
}

namespace RESQML2_2_NS
{
	class SeismicWellboreFrameRepresentation : public RESQML2_2_NS::WellboreFrameRepresentation
	{
	public:

		/**
		* Only to be used in partial transfer context
		*/
		DLL_IMPORT_OR_EXPORT SeismicWellboreFrameRepresentation(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) :
			RESQML2_2_NS::WellboreFrameRepresentation(partialObject) {}

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		SeismicWellboreFrameRepresentation(gsoap_eml2_2::resqml22__SeismicWellboreFrameRepresentation * fromGsoap) :
			RESQML2_2_NS::WellboreFrameRepresentation(fromGsoap) {}

		~SeismicWellboreFrameRepresentation() {}

		/**
		* Creates an instance of this class in a gsoap context.
		* @param interp					The WellboreFeature interpretation the instance represents.
		* @param guid					The guid to set to the new instance. If empty then a new guid will be generated.
		* @param title					A title for the instance to create.
		* @param traj					The trajectory this SeismicWellboreFrameRepresentation frame is based on.
		* @param seismicReferenceDatum	The Z value where the seismic time is equal to zero for this SeismicWellboreFrameRepresentation.
		* @param weatheringVelocity		The weathering velocity (also called veolocity replacement).
		* @param crs					The crs the time values are based on.
		*/
		SeismicWellboreFrameRepresentation(RESQML2_0_1_NS::WellboreInterpretation* interp,
			const std::string& guid, const std::string& title,
			RESQML2_0_1_NS::WellboreTrajectoryRepresentation* traj,
			double seismicReferenceDatum,
			double weatheringVelocity,
			RESQML2_0_1_NS::LocalTime3dCrs* crs);
	
		/**
		* Set the time values of this SeismicWellboreFrameRepresentation frame to an array 1d of explicit values.
		* @param timeValues		All the time values to set from top of the well trajectory to bottom.
		* @param timeValueCount	The time values count. It must be the same that the md values count.
		* @param proxy			The HDF proxy where to write the time values. It must be already opened for writing and won't be closed in this method.
		*/
		DLL_IMPORT_OR_EXPORT void setTimeValues(double const * timeValues, unsigned int timeValueCount, COMMON_NS::AbstractHdfProxy* proxy = nullptr);

		/**
		* Set the time values of this WellboreFrameRepresentation frame as a regular discretization along the wellbore trajectory.
		* @param firstTimeValue		The first time value.
		* @param incrementTimeValue	The increment value between two time values. It must be the same that the md values count.
		* @param timeValueCount		The count of time values in this WellboreFrameRepresentation.
		*/
		DLL_IMPORT_OR_EXPORT void setTimeValues(double firstTimeValue, double incrementTimeValue, unsigned int timeValueCount);

		/**
		* Indicates either the times are regularly spaced or not (useful for optimization)
		* Does not verify if the writer has used a generic array to store regular times.
		*/
		DLL_IMPORT_OR_EXPORT bool areTimeValuesRegularlySpaced() const;

		/**
		* Indicates the increment value between two times only if the times are regularly spaced.
		* Please use areTimeValuesRegularlySpaced before using this method.
		*/
		DLL_IMPORT_OR_EXPORT double getTimeConstantIncrementValue() const;

		/**
		* Returns the first time value of this SeismicWellboreFrameRepresentation
		*/
		DLL_IMPORT_OR_EXPORT double getTimeFirstValue() const;

		/**
		* Get the number of time values in this seismic wellbore frame.
		*/
		DLL_IMPORT_OR_EXPORT unsigned int getTimeValuesCount() const;

		/**
		* Get the time values datatype in the HDF dataset
		*/
		DLL_IMPORT_OR_EXPORT RESQML2_NS::AbstractValuesProperty::hdfDatatypeEnum getTimeHdfDatatype() const;

		/**
		* Get all the time values of the instance which are supposed to be double ones.
		*/
		DLL_IMPORT_OR_EXPORT void getTimeAsDoubleValues(double* values) const;

		/**
		* Get all the time values of the instance which are supposed to be float ones.
		*/
		DLL_IMPORT_OR_EXPORT void getTimeAsFloatValues(float* values) const;

		/**
		* Returns the seismic reference datum
		*/
		DLL_IMPORT_OR_EXPORT double getSeismicReferenceDatum() const;

		/**
		* Returns the weathering velocity
		*/
		DLL_IMPORT_OR_EXPORT double getWeatheringVelocity() const;
			   
		/**
		* The standard XML tag without XML namespace for serializing this data object.
		*/
		DLL_IMPORT_OR_EXPORT static const char* XML_TAG;

		/**
		* Get the standard XML tag without XML namespace for serializing this data object.
		*/
		DLL_IMPORT_OR_EXPORT virtual std::string getXmlTag() const { return XML_TAG; }
	};
}