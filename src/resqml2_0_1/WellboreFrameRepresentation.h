/*-----------------------------------------------------------------------
Copyright F2I-CONSULTING, (2014-2017)

philippe.verney@f2i-consulting.com

This software is a computer program whose purpose is to access to data formatted using Energistics standards.

This software is governed by the CeCILL-B license under French law and
abiding by the rules of distribution of free software.  You can  use, 
modify and/ or redistribute the software under the terms of the CeCILL-B
license as circulated by CEA, CNRS and INRIA at the following URL
"http://www.cecill.info". 

As a counterpart to the access to the source code and  rights to copy,
modify and redistribute granted by the license, users are provided only
with a limited warranty  and the software's author,  the holder of the
economic rights,  and the successive licensors  have only  limited
liability. 

In this respect, the user's attention is drawn to the risks associated
with loading,  using,  modifying and/or developing or reproducing the
software by the user in light of its specific status of free software,
that may mean  that it is complicated to manipulate,  and  that  also
therefore means  that it is reserved for developers  and  experienced
professionals having in-depth computer knowledge. Users are therefore
encouraged to load and test the software's suitability as regards their
requirements in conditions enabling the security of their systems and/or 
data to be ensured and,  more generally, to use and operate it in the 
same conditions as regards security. 

The fact that you are presently reading this means that you have had
knowledge of the CeCILL-B license and that you accept its terms.
-----------------------------------------------------------------------*/
#pragma once

#include "resqml2/AbstractRepresentation.h"
#include "resqml2/AbstractValuesProperty.h"

namespace witsml1_4_1_1
{
	class Log;
}

namespace resqml2_0_1
{
	class DLL_IMPORT_OR_EXPORT WellboreFrameRepresentation : public resqml2::AbstractRepresentation
	{
	protected:
		gsoap_resqml2_0_1::resqml2__PointGeometry* getPointGeometry2_0_1(const unsigned int & patchIndex) const {return nullptr;}

		WellboreFrameRepresentation(resqml2::AbstractFeatureInterpretation* interp, resqml2::AbstractLocal3dCrs * crs) : AbstractRepresentation(interp, crs), trajectory(nullptr), witsmlLog(nullptr) {}

	public:

		/**
		* Only to be used in partial transfer context
		*/
		WellboreFrameRepresentation(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) :
			resqml2::AbstractRepresentation(partialObject)
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
		void setMdValues(double * mdValues, const unsigned int & mdValueCount, common::AbstractHdfProxy* proxy);

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
		resqml2::AbstractValuesProperty::hdfDatatypeEnum getMdHdfDatatype() const;

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

		std::string getHdfProxyUuid() const;

		unsigned int getPatchCount() const {return 1;}

		void setWitsmlLog(witsml1_4_1_1::Log * witsmlLogToSet);
		witsml1_4_1_1::Log* getWitsmlLog() {return witsmlLog;}

		static const char* XML_TAG;
		virtual std::string getXmlTag() const {return XML_TAG;}

	protected:

		virtual std::vector<epc::Relationship> getAllEpcRelationships() const;
		virtual void importRelationshipSetFromEpc(common::EpcDocument* epcDoc);

		class WellboreTrajectoryRepresentation * trajectory;
		witsml1_4_1_1::Log * witsmlLog;
	};
}
