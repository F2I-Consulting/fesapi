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

namespace resqml2_0_1
{
	class DLL_IMPORT_OR_EXPORT PlaneSetRepresentation : public resqml2::AbstractRepresentation
	{
	private :
		gsoap_resqml2_0_1::resqml2__PointGeometry* getPointGeometry2_0_1(const unsigned int & patchIndex) const {return nullptr;}

	public:

		/**
		* Only to be used in partial transfer context
		*/
		PlaneSetRepresentation(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : resqml2::AbstractRepresentation(partialObject) {}

		/**
		* Creates an instance of this class in a gsoap context.
		* @param interp							The interpretation this representation represents.
		* @param crs							The local CRS where the geometry of this representation is given.
		* @param guid							The guid to set to the new instance. If empty then a new guid will be generated.
		* @param title							A title for the instance to create.
		*/
		PlaneSetRepresentation(resqml2::AbstractFeatureInterpretation* interp, resqml2::AbstractLocal3dCrs * crs,
				const std::string & guid, const std::string & title);

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		PlaneSetRepresentation(gsoap_resqml2_0_1::_resqml2__PlaneSetRepresentation* fromGsoap) : resqml2::AbstractRepresentation(fromGsoap) {}

		/**
		* Destructor does nothing since the memory is managed by the gsoap context.
		*/
		~PlaneSetRepresentation() {}

		std::string getHdfProxyUuid() const {return "";};

		static const char* XML_TAG;
		virtual std::string getXmlTag() const {return XML_TAG;}

		/**
		* Get the xyz point count in a given patch.
		*/
		ULONG64 getXyzPointCountOfPatch(const unsigned int & patchIndex) const;

		/**
		* Get all the XYZ points of a particular patch of this representation.
		* XYZ points are given in the local CRS.
		* @param xyzPoints A linearized 2d array where the first (quickest) dimension is coordinate dimension (XYZ) and second dimension is vertex dimension. It must be pre allocated.
		*/
		void getXyzPointsOfPatch(const unsigned int & patchIndex, double * xyzPoints) const;

		/**
		 * Get the number of triangle patch
		 */
		unsigned int getPatchCount() const;

		/**
		* Push back a new patch which is an horizontal plane
		* @param zCoordinate	The Z coordinate of the horizontal plane
		*/
		void pushBackHorizontalPlaneGeometryPatch(const double & zCoordinate);

		/**
		* Push back a new patch which is not a horizontal plane. It s geometry is given by means of 3 XYZ points.
		*/
		void pushBackTiltedPlaneGeometryPatch(const double & x1, const double & y1, const double & z1,
			const double & x2, const double & y2, const double & z2,
			const double & x3, const double & y3, const double & z3);
	};
}
