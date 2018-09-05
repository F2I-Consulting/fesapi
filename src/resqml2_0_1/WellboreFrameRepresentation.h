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

#include "resqml2/AbstractRepresentation.h"
#include "resqml2/AbstractValuesProperty.h"

namespace WITSML1_4_1_1_NS
{
	class Log;
}

namespace RESQML2_0_1_NS
{
	class DLL_IMPORT_OR_EXPORT WellboreFrameRepresentation : public RESQML2_NS::AbstractRepresentation
	{
	protected:
		gsoap_resqml2_0_1::resqml2__PointGeometry* getPointGeometry2_0_1(const unsigned int & patchIndex) const {return nullptr;}

		WellboreFrameRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp, RESQML2_NS::AbstractLocal3dCrs * crs) : AbstractRepresentation(interp, crs), trajectory(nullptr), witsmlLog(nullptr) {}

	public:

		/**
		* Only to be used in partial transfer context
		*/
		WellboreFrameRepresentation(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) :
			RESQML2_NS::AbstractRepresentation(partialObject), trajectory(nullptr), witsmlLog(nullptr)
		{
		}

		/**
		* Creates an instance of this class in a gsoap context.
		* @param interp		The WellboreFeature interpretation the instance represents.
		* @param guid		The guid to set to the new instance. If empty then a new guid will be generated.
		* @param title		A title for the instance to create.
		* @param traj		The trajectory this WellboreFeature frame is based on.
		*/
		WellboreFrameRepresentation(class WellboreInterpretation* interp, const std::string & guid, const std::string & title, class WellboreTrajectoryRepresentation * traj);

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		WellboreFrameRepresentation(gsoap_resqml2_0_1::_resqml2__WellboreFrameRepresentation* fromGsoap): AbstractRepresentation(fromGsoap), trajectory(nullptr), witsmlLog(nullptr)  {}

		~WellboreFrameRepresentation() {}

		/**
		* Set the MD values of this WellboreFrameRepresentation frame to an array 1d of explicit values.
		* @param mdValues		All the MD values to set from top of the well trajectory to bottom.
		* @param mdValueCount	The MD values count.
		* @param proxy			The HDF proxy where to write the MD values. It must be already opened for writing and won't be closed in this method.
		*/
		void setMdValues(double * mdValues, const unsigned int & mdValueCount, COMMON_NS::AbstractHdfProxy* proxy);

		/**
		* Set the MD values of this WellboreFrameRepresentation frame as a regular discretization along the wellbore trajectory.
		* @param firstMdValue		The first MD value.
		* @param incrementMdValue	The increment value between two Measured depth.
		* @param mdValueCount		The count of md values in this WellboreFrameRepresentation.
		*/
		void setMdValues(const double & firstMdValue, const double & incrementMdValue, const unsigned int & mdValueCount);

		/**
		* Indicates either the MDs are regularly spaced or not (useful for optimization)
		* Does not verify if the writer has used a generic array to store regular mds.
		*/
		bool areMdValuesRegularlySpaced() const;
		
		/**
		* Indicates the incremetn value between two MDs only if the MDs are regualrly spaced.
		* Please use areMdValuesRegularlySpaced before using this method.
		*/
		double getMdConstantIncrementValue() const;

		/**
		* Returns the first MD value of this WellboreFrameRepresentation
		*/
		double getMdFirstValue() const;
		
		/**
		* Get the number of Md values in this WellboreFeature frame.
		*/
		unsigned int getMdValuesCount() const;

		/**
		* Get the xyz point count in a given patch.
		*/
		ULONG64 getXyzPointCountOfPatch(const unsigned int & patchIndex) const {return getMdValuesCount();}

		/**
		* Get all the XYZ points of a particular patch of this representation.
		* XYZ points are given in the local CRS.
		* @param xyzPoints A linearized 2d array where the first (quickest) dimension is coordinate dimension (XYZ) and second dimension is vertex dimension. It must be pre allocated.
		*/
		void getXyzPointsOfPatch(const unsigned int & patchIndex, double * xyzPoints) const;

		/**
		* Get the Measured Depth datatype in the HDF dataset
		*/
		COMMON_NS::AbstractObject::hdfDatatypeEnum getMdHdfDatatype() const;

		/**
		* Get all the md values of the instance which are supposed to be double ones.
		*/
		void getMdAsDoubleValues(double * values);

		/**
		* Get all the md values of the instance which are supposed to be float ones.
		*/
		void getMdAsFloatValues(float * values);

		/**
		* Get the associated resqml wellbore trajectory uuid
		*/
		std::string getWellboreTrajectoryUuid() const;

		/**
		* Get the associated resqml wellbore trajector
		*/
		class WellboreTrajectoryRepresentation* getWellboreTrajectory() {return trajectory;}

		gsoap_resqml2_0_1::eml20__DataObjectReference* getLocalCrsDor() const;

		gsoap_resqml2_0_1::eml20__DataObjectReference* getHdfProxyDor() const;

		unsigned int getPatchCount() const {return 1;}

		void setWitsmlLog(WITSML1_4_1_1_NS::Log * witsmlLogToSet);
		WITSML1_4_1_1_NS::Log* getWitsmlLog() {return witsmlLog;}

		static const char* XML_TAG;
		virtual std::string getXmlTag() const {return XML_TAG;}

		virtual std::vector<epc::Relationship> getAllTargetRelationships() const;

	protected:
		virtual void importRelationshipSetFromEpc(COMMON_NS::EpcDocument* epcDoc);

		class WellboreTrajectoryRepresentation * trajectory;
		WITSML1_4_1_1_NS::Log * witsmlLog;
	};
}

