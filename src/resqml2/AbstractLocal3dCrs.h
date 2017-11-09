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

#include "resqml2/MdDatum.h"

namespace resqml2
{
	class DLL_IMPORT_OR_EXPORT AbstractLocal3dCrs : public common::AbstractObject
	{
	protected:

		/**
		* Only to be used in partial transfer context
		*/
		AbstractLocal3dCrs(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : common::AbstractObject(partialObject) {}

		AbstractLocal3dCrs() {}

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		AbstractLocal3dCrs(gsoap_resqml2_0_1::resqml2__AbstractLocal3dCrs* fromGsoap):
			common::AbstractObject(fromGsoap) {}

		/**
		* Get the Z offset which is always equal to zero for a time CRS.
		* Don't mix zOffset vs depthOffset : the schema calls zOffset what is actually a depthOrElevationOffset.
		*/
		virtual double getZOffset() const = 0;

	public:

		/**
		* Destructor does nothing since the memory is manged by the gsoap context.
		*/
		virtual ~AbstractLocal3dCrs() {}

		/**
		* Add a geometrical representation which is based on this local CRS
		* Does not add the inverse relationship i.e. from the geometrical representation to this local CRS.
		*/
		void addRepresentation(class AbstractRepresentation* rep);

		/**
		* Get the first origin ordinal (usually called X) of the local CRS in the global projected CRS.
		*/
		double getOriginOrdinal1() const;

		/**
		* Get the second origin ordinal (usually called Y) of the local CRS in the global projected CRS.
		*/
		double getOriginOrdinal2() const;

		/**
		* Get the depth or elevation origin of this local CRS in the global vertical CRS.
		* If this local CRS is a time CRS, this value defines the Seismic Reference Datum.
		*/
		double getOriginDepthOrElevation() const;

		/**
		* Get the rotation in radians of the the local Y axis relative to the global projected axis which is 90 degrees counter-clockwise from the other global axis.
		* A positive value indicates a clockwise rotation from the global axis.
		* A negative value indicates a counterclockwise rotation form the global axis.
		*/
		double getArealRotation() const;

		/**
		* Indicates if the depth or elevation values given in this local CRS are depth ones or elevation ones.
		*/
		bool isDepthOriented() const;

		/**
		* Indicates either the associated projected Crs is identified by means of EPSG or not.
		*/
		bool isProjectedCrsDefinedWithEpsg() const;

		/**
		* Indicates either the associated projected Crs is unknown.
		*/
		virtual bool isProjectedCrsUnknown() const;

		/**
		* Get the reason why the projected Crs is unknown.
		*/
		const std::string & getProjectedCrsUnknownReason() const;

		/**
		* Get the EPSG code of the projected CRS
		*/
		unsigned long long getProjectedCrsEpsgCode() const;

		/**
		* Indicates either the associated vertical Crs is identified by means of EPSG or not.
		*/
		bool isVerticalCrsDefinedWithEpsg() const;

		/**
		* Indicates either the associated vertical Crs is unknown.
		*/
		bool isVerticalCrsUnknown() const;

		/**
		* Get the reason why the vertical Crs is unknown.
		*/
		const std::string & getVerticalCrsUnknownReason() const;

		/**
		* Get the EPSG code of the vertical CRS
		*/
		unsigned long long getVerticalCrsEpsgCode() const;

		/**
		 * Get the vertical crs unit as a string
		 */
		std::string getVerticalCrsUnitAsString() const;

		gsoap_resqml2_0_1::eml20__PlaneAngleUom getArealRotationUom() const;

		/**
		* Get the projected crs unit
		*/
		gsoap_resqml2_0_1::eml20__LengthUom getProjectedCrsUnit() const;

		/**
		* Get the projected crs unit as a string
		*/
		std::string getProjectedCrsUnitAsString() const;

		/**
		* Get the vertical crs unit
		*/
		gsoap_resqml2_0_1::eml20__LengthUom getVerticalCrsUnit() const;

		/**
		* Get the axis order of the projected Crs
		*/
		gsoap_resqml2_0_1::eml20__AxisOrder2d getAxisOrder() const;

		void convertXyzPointsToGlobalCrs(double * xyzPoints, const ULONG64 & xyzPointCount, bool withoutTranslation = false) const;

	protected:
		
		std::vector<epc::Relationship> getAllEpcRelationships() const;
		void importRelationshipSetFromEpc(common::EpcDocument* epcDoc) {}

		// XML backward relationship
		std::vector<class AbstractRepresentation*> repSet;
		std::vector<MdDatum*> mdDatumSet;

	private:
		/**
		* Add a md information which is based on this local CRS
		* Does not add the inverse relationship i.e. from the md information to this local CRS.
		*/
		void addMdDatum(MdDatum* mdInfo);

		friend void MdDatum::setLocalCrs(AbstractLocal3dCrs * localCrs);
	};
}
