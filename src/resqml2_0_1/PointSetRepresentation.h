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
	class DLL_IMPORT_OR_EXPORT PointSetRepresentation : public resqml2::AbstractRepresentation
	{
	private :
		gsoap_resqml2_0_1::resqml2__PointGeometry* getPointGeometry2_0_1(const unsigned int & patchIndex) const;

	public:

		/**
		* Only to be used in partial transfer context
		*/
		PointSetRepresentation(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : resqml2::AbstractRepresentation(partialObject) {}

		/**
		* Creates an instance of this class in a gsoap context.
		* @param interp							The interpretation this representation represents.
		* @param crs							The local CRS where the geometry of this representation is given.
		* @param guid							The guid to set to the new instance. If empty then a new guid will be generated.
		* @param title							A title for the instance to create.
		*/
		PointSetRepresentation(resqml2::AbstractFeatureInterpretation* interp, resqml2::AbstractLocal3dCrs * crs,
				const std::string & guid, const std::string & title);

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		PointSetRepresentation(gsoap_resqml2_0_1::_resqml2__PointSetRepresentation* fromGsoap) : resqml2::AbstractRepresentation(fromGsoap) {}

		/**
		* Destructor does nothing since the memory is managed by the gsoap context.
		*/
		~PointSetRepresentation() {}

		std::string getHdfProxyUuid() const;

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
		* Push back a new patch of polylines
		* @param xyzPointCount	The XYZ point count in this patch.
		* @param xyzPoints		The XYZ values of the points of the patch. Ordered by XYZ and then by xyzPointCount. It must be three times xyzPointCount.
		* @param proxy			The HDF proxy which defines where the XYZ points will be stored.
		*/
		void pushBackGeometryPatch(
				const unsigned int & xyzPointCount, double * xyzPoints,
				common::AbstractHdfProxy* proxy);
	};
}
