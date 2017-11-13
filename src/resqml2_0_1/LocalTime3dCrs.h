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

#include "resqml2/AbstractLocal3dCrs.h"

namespace resqml2_0_1
{
	class DLL_IMPORT_OR_EXPORT LocalTime3dCrs : public resqml2::AbstractLocal3dCrs
	{
	private:
		void init(soap* soapContext, const std::string & guid, const std::string & title,
			const double & originOrdinal1, const double & originOrdinal2, const double & originOrdinal3,
			const double & arealRotation,
			const gsoap_resqml2_0_1::eml20__LengthUom & projectedUom,
			const gsoap_resqml2_0_1::eml20__TimeUom & timeUom,
			const gsoap_resqml2_0_1::eml20__LengthUom & verticalUom, const bool & isUpOriented);

		double getZOffset() const {return .0;}

	public:

		/**
		* Only to be used in partial transfer context
		*/
		LocalTime3dCrs(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : resqml2::AbstractLocal3dCrs(partialObject) {}

		/**
		* Creates a local depth 3d CRS which is fully identified by means of EPSG code.
		* @param soapContext		The soap context where the underlying gsoap proxy is going to be created.
		* @param guid				The guid to set to the local 3d crs. If empty then a new guid will be generated.
		* @param title				A title for the instance to create.
		* @param originOrdinal1		The offset of the global 2d crs on its first axis.
		* @param originOrdinal2		The offset of the global 2d crs on its second axis.
		* @param originOrdinal3		The offset in depth of the local CRS regarding the depth origin of the vertical CRS.
		* @param arealRotation		The areal rotation in radians regarding the projected crs.
		* @param projectedUom		The unit of measure of the projected axis of this instance.
		* @param projectedEpsgCode	The epsg code of the associated projected CRS.
		* @param timeUom			The unit of measure of the Z offset of this instance.
		* @param verticalUom		The unit of measure of the vertical axis of this instance.
		* @param verticalEpsgCode	The epsg code of the associated vertical CRS.
		* @param isUpOriented		If true, indicates that the Z offset if an elevation when positive. If false, the Z offset is a depth when positive.
		*/
		LocalTime3dCrs(soap* soapContext, const std::string & guid, const std::string & title,
			const double & originOrdinal1, const double & originOrdinal2, const double & originOrdinal3,
			const double & arealRotation,
			const gsoap_resqml2_0_1::eml20__LengthUom & projectedUom, const unsigned long & projectedEpsgCode,
			const gsoap_resqml2_0_1::eml20__TimeUom & timeUom,
			const gsoap_resqml2_0_1::eml20__LengthUom & verticalUom, const unsigned int & verticalEpsgCode, const bool & isUpOriented);

		/**
		* Creates a local depth 3d CRS which is fully unknown.
		* @param soapContext			The soap context where the underlying gsoap proxy is going to be created.
		* @param guid					The guid to set to the local 3d crs. If empty then a new guid will be generated.
		* @param title					A title for the instance to create.
		* @param originOrdinal1			The offset of the global 2d crs on its first axis.
		* @param originOrdinal2			The offset of the global 2d crs on its second axis.
		* @param originOrdinal3			The offset in depth of the local CRS regarding the depth origin of the vertical CRS.
		* @param arealRotation			The areal rotation in radians regarding the projected crs.
		* @param projectedUom			The unit of measure of the projected axis of this instance.
		* @param projectedUnknownReason	Indicates why the projected CRS cannot be provided using EPSG or GML.
		* @param timeUom				The unit of measure of the Z offset of this instance.
		* @param verticalUom			The unit of measure of the vertical axis of this instance.
		* @param verticalUnknownReason	Indicates why the vertical CRS cannot be provided using EPSG or GML.
		* @param isUpOriented			If true, indicates that the Z offset if an elevation when positive. If false, the Z offset is a depth when positive.
		*/
		LocalTime3dCrs(soap* soapContext, const std::string & guid, const std::string & title,
			const double & originOrdinal1, const double & originOrdinal2, const double & originOrdinal3,
			const double & arealRotation,
			const gsoap_resqml2_0_1::eml20__LengthUom & projectedUom, const std::string & projectedUnknownReason,
			const gsoap_resqml2_0_1::eml20__TimeUom & timeUom,
			const gsoap_resqml2_0_1::eml20__LengthUom & verticalUom, const std::string & verticalUnknownReason, const bool & isUpOriented);

		/**
		* Creates a local depth 3d CRS which is identified by an EPSG code for its projected part and which is unkown for its vertial part.
		* @param soapContext			The soap context where the underlying gsoap proxy is going to be created.
		* @param guid					The guid to set to the local 3d crs. If empty then a new guid will be generated.
		* @param title					A title for the instance to create.
		* @param originOrdinal1			The offset of the global 2d crs on its first axis.
		* @param originOrdinal2			The offset of the global 2d crs on its second axis.
		* @param originOrdinal3			The offset in depth of the local CRS regarding the depth origin of the vertical CRS.
		* @param arealRotation			The areal rotation in radians regarding the projected crs.
		* @param projectedUom			The unit of measure of the projected axis of this instance.
		* @param timeUom				The unit of measure of the Z offset of this instance.
		* @param projectedEpsgCode		The epsg code of the associated projected CRS.
		* @param verticalUom			The unit of measure of the vertical axis of this instance.
		* @param verticalUnknownReason	Indicates why the vertical CRS cannot be provided using EPSG or GML.
		* @param isUpOriented			If true, indicates that the Z offset if an elevation when positive. If false, the Z offset is a depth when positive.
		*/
		LocalTime3dCrs(soap* soapContext, const std::string & guid, const std::string & title,
			const double & originOrdinal1, const double & originOrdinal2, const double & originOrdinal3,
			const double & arealRotation,
			const gsoap_resqml2_0_1::eml20__LengthUom & projectedUom, const unsigned long & projectedEpsgCode,
			const gsoap_resqml2_0_1::eml20__TimeUom & timeUom,
			const gsoap_resqml2_0_1::eml20__LengthUom & verticalUom, const std::string & verticalUnknownReason, const bool & isUpOriented);

		/**
		* Creates a local depth 3d CRS which unkown for its projected part and which is identified by an EPSG code for its vertical part.
		* @param soapContext			The soap context where the underlying gsoap proxy is going to be created.
		* @param guid					The guid to set to the local 3d crs. If empty then a new guid will be generated.
		* @param title					A title for the instance to create.
		* @param originOrdinal1			The offset of the global 2d crs on its first axis.
		* @param originOrdinal2			The offset of the global 2d crs on its second axis.
		* @param originOrdinal3			The offset in depth of the local CRS regarding the depth origin of the vertical CRS.
		* @param arealRotation			The areal rotation in radians regarding the projected crs.
		* @param projectedUom			The unit of measure of the projected axis of this instance.
		* @param projectedUnknownReason	Indicates why the projected CRS cannot be provided using EPSG or GML.
		* @param timeUom				The unit of measure of the Z offset of this instance.
		* @param verticalUom			The unit of measure of the vertical axis of this instance.
		* @param verticalEpsgCode		The epsg code of the associated vertical CRS.
		* @param isUpOriented			If true, indicates that the Z offset if an elevation when positive. If false, the Z offset is a depth when positive.
		*/
		LocalTime3dCrs(soap* soapContext, const std::string & guid, const std::string & title,
			const double & originOrdinal1, const double & originOrdinal2, const double & originOrdinal3,
			const double & arealRotation,
			const gsoap_resqml2_0_1::eml20__LengthUom & projectedUom, const std::string & projectedUnknownReason,
			const gsoap_resqml2_0_1::eml20__TimeUom & timeUom,
			const gsoap_resqml2_0_1::eml20__LengthUom & verticalUom, const unsigned int & verticalEpsgCode, const bool & isUpOriented);

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		LocalTime3dCrs(gsoap_resqml2_0_1::_resqml2__LocalTime3dCrs* fromGsoap):
			AbstractLocal3dCrs(fromGsoap) {}

		/**
		* Destructor does nothing since the memory is manged by the gsoap context.
		*/
		~LocalTime3dCrs() {}

		gsoap_resqml2_0_1::eml20__TimeUom getUnit() const;

		std::string getUnitAsString() const;

		//******************************************************************
		//********** INHERITED FROM AbstractObjectWithDcMetadata ***********
		//******************************************************************

		static const char* XML_TAG;
		virtual std::string getXmlTag() const {return XML_TAG;}
	};
}
