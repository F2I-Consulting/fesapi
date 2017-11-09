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

namespace resqml2_0_1
{
	class DLL_IMPORT_OR_EXPORT MdDatum : public resqml2::MdDatum
	{
	public:

		/**
		* Only to be used in partial transfer context
		*/
		MdDatum(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : resqml2::MdDatum(partialObject) {}

		/**
		* Creates an instance of this class in a gsoap context.
		* @param soapContext				The soap context where the underlying gsoap proxy is going to be created.
		* @param guid						The guid to set to the local 3d crs. If empty then a new guid will be generated.
		* @param title						A title for the instance to create.
		* @param locCrs						The local CRS where the ordinal are given
		* @param originKind					Indicates the kind of the MD reference point.
		* @param referenceLocationOrdinal1	The location of the MD reference point on the first axis of the local 3d CRS.
		* @param referenceLocationOrdinal2	The location of the MD reference point on the second axis of the local 3d CRS.
		* @param referenceLocationOrdinal3	The location of the MD reference point on the third axis of the local 3d CRS.
		*/
		MdDatum(soap* soapContext, const std::string & guid, const std::string & title,
			resqml2::AbstractLocal3dCrs * locCrs, const gsoap_resqml2_0_1::resqml2__MdReference & originKind,
			const double & referenceLocationOrdinal1, const double & referenceLocationOrdinal2, const double & referenceLocationOrdinal3);

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		MdDatum(gsoap_resqml2_0_1::_resqml2__MdDatum* fromGsoap) :resqml2::MdDatum(fromGsoap) {}

		/**
		* Destructor does nothing since the memory is managed by the gsoap context.
		*/
		~MdDatum() {}

		/**
		* Get the Local 3d CRS dor where the reference point ordinals are given
		*/
		gsoap_resqml2_0_1::eml20__DataObjectReference* getLocalCrsDor() const;

		/**
		* Getter of the first ordinal of the reference location.
		*/
		double getX() const;
		double getXInGlobalCrs() const;

		/**
		* Getter of the second ordinal of the reference location.
		*/
		double getY() const;
		double getYInGlobalCrs() const;

		/**
		* Getter of the third ordinal of the reference location.
		*/
		double getZ() const;
		double getZInGlobalCrs() const;

		/**
		* Getter of the origin kind of the MD.
		*/
		gsoap_resqml2_0_1::resqml2__MdReference getOriginKind() const;

	protected:

		void setXmlLocalCrs(resqml2::AbstractLocal3dCrs * localCrs);

		// XML backward relationship
		std::vector<class WellboreTrajectoryRepresentation*> wellboreTrajectoryRepresentationSet;
	};
}
