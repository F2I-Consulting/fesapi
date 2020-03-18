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
	* Representation of a wellbore that is organized along a wellbore trajectory by its MD values. RESQML uses MD values to associate properties on points and to organize association of properties on intervals between MD points. 
	*/
	class WellboreFrameRepresentation : public AbstractRepresentation
	{
	protected:
		WellboreFrameRepresentation() {}

		/**
		* Only to be used in partial transfer context
		*/
		WellboreFrameRepresentation(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) :
			RESQML2_NS::AbstractRepresentation(partialObject) {}

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		WellboreFrameRepresentation(gsoap_resqml2_0_1::_resqml20__WellboreFrameRepresentation* fromGsoap) :
			AbstractRepresentation(fromGsoap) {}

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		WellboreFrameRepresentation(gsoap_eml2_2::resqml22__WellboreFrameRepresentation* fromGsoap) :
			AbstractRepresentation(fromGsoap) {}

	public:
		~WellboreFrameRepresentation() {}

		/**
		* Set the MD values of this WellboreFrameRepresentation frame to an array 1d of explicit values.
		* @param mdValues		All the MD values to set from top of the well trajectory to bottom.
		* @param mdValueCount	The MD values count.
		* @param proxy			The HDF proxy where to write the MD values. It must be already opened for writing and won't be closed in this method.
		*/
		DLL_IMPORT_OR_EXPORT void setMdValues(double const * mdValues, unsigned int mdValueCount, COMMON_NS::AbstractHdfProxy* proxy = nullptr);

		/**
		* Set the MD values of this WellboreFrameRepresentation frame as a regular discretization along the wellbore trajectory.
		* @param firstMdValue		The first MD value.
		* @param incrementMdValue	The increment value between two Measured depth.
		* @param mdValueCount		The count of md values in this WellboreFrameRepresentation.
		*/
		DLL_IMPORT_OR_EXPORT void setMdValues(double firstMdValue, double incrementMdValue, unsigned int mdValueCount);

		/**
		* Indicates either the MDs are regularly spaced or not (useful for optimization).
		* Does not verify if the writer has used a generic array to store regular mds.
		*/
		DLL_IMPORT_OR_EXPORT bool areMdValuesRegularlySpaced() const;
		
		/**
		* Indicates the increment value between two MDs only if the MDs are regularly spaced.
		* Please use areMdValuesRegularlySpaced before using this method.
		*/
		DLL_IMPORT_OR_EXPORT double getMdConstantIncrementValue() const;

		/**
		* Returns the first MD value of this WellboreFrameRepresentation
		*/
		DLL_IMPORT_OR_EXPORT double getMdFirstValue() const;
		
		/**
		* Get the number of Md values in this WellboreFeature frame.
		*/
		DLL_IMPORT_OR_EXPORT unsigned int getMdValuesCount() const;

		/**
		* Get the xyz point count in a given patch.
		*/
		DLL_IMPORT_OR_EXPORT ULONG64 getXyzPointCountOfPatch(const unsigned int & patchIndex) const;

		/**
		* Get all the XYZ points of a particular patch of this representation.
		* XYZ points are given in the local CRS.
		* @param xyzPoints A linearized 2d array where the first (quickest) dimension is coordinate dimension (XYZ) and second dimension is vertex dimension. It must be pre allocated.
		*/
		DLL_IMPORT_OR_EXPORT void getXyzPointsOfPatch(const unsigned int & patchIndex, double * xyzPoints) const;

		/**
		* Get the Measured Depth datatype in the HDF dataset
		*/
		DLL_IMPORT_OR_EXPORT RESQML2_NS::AbstractValuesProperty::hdfDatatypeEnum getMdHdfDatatype() const;

		/**
		* Get all the md values of the instance which are supposed to be double ones.
		*/
		DLL_IMPORT_OR_EXPORT void getMdAsDoubleValues(double * values) const;

		/**
		* Get all the md values of the instance which are supposed to be float ones.
		*/
		DLL_IMPORT_OR_EXPORT void getMdAsFloatValues(float * values) const;

		/**
		* Get the associated RESQML wellbore trajectory data object reference.
		*/
		COMMON_NS::DataObjectReference getWellboreTrajectoryDor() const;

		/**
		* Get the associated RESQML wellbore trajector.
		*/
		DLL_IMPORT_OR_EXPORT class WellboreTrajectoryRepresentation* getWellboreTrajectory() const;

		/**
		* Get the associated RESQML local crs data object reference.
		*/
		COMMON_NS::DataObjectReference getLocalCrsDor(unsigned int patchIndex) const;

		/**
		* Get the associated hdf proxy data object reference.
		*/
		COMMON_NS::DataObjectReference getHdfProxyDor() const;

		/**
		* Get the count of patch of this representation.
		*/
		DLL_IMPORT_OR_EXPORT unsigned int getPatchCount() const {return 1;}

		protected:
			void loadTargetRelationships();
	};
}
