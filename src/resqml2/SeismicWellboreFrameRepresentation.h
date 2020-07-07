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

#include "WellboreFrameRepresentation.h"

namespace RESQML2_NS
{
	/** @brief	A seismic wellbore frame representation. This class cannot be inherited. */
	class SeismicWellboreFrameRepresentation : public WellboreFrameRepresentation
	{
	public:

		virtual ~SeismicWellboreFrameRepresentation() {}
	
		/**
		* Set the time values of this SeismicWellboreFrameRepresentation frame to an array 1d of explicit values.
		* @param timeValues		All the time values to set from top of the well trajectory to bottom.
		* @param timeValueCount	The time values count. It must be the same that the md values count.
		* @param proxy			The HDF proxy where to write the time values. It must be already opened for writing and won't be closed in this method.
		*/
		DLL_IMPORT_OR_EXPORT void setTimeValues(double const * timeValues, unsigned int timeValueCount, EML2_NS::AbstractHdfProxy* proxy = nullptr);

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
		DLL_IMPORT_OR_EXPORT virtual std::string getXmlTag() const final { return XML_TAG; }

	protected:

		/*
		* Default constructor
		*/
		SeismicWellboreFrameRepresentation() {}

		/**
		* Only to be used in partial transfer context
		*/
		SeismicWellboreFrameRepresentation(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) :
			WellboreFrameRepresentation(partialObject) {}

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		SeismicWellboreFrameRepresentation(gsoap_eml2_3::resqml22__SeismicWellboreFrameRepresentation * fromGsoap) :
			WellboreFrameRepresentation(fromGsoap) {}
	};
}