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

#include "WellboreObject.h"

namespace WITSML2_0_NS
{
	/**
	* Captures information about the configuration of the permanently installed components in a wellbore. It does not define the transient drilling strings (see the Tubular object) or the hanging production components (see the Completion object).
	*/
	class WellboreGeometry : public WellboreObject
	{
	public:
		/**
		* Constructor for partial transfer
		*/
		DLL_IMPORT_OR_EXPORT WellboreGeometry(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : WellboreObject(partialObject) {}

		WellboreGeometry(class Wellbore* witsmlWellbore,
			const std::string & guid,
			const std::string & title,
			gsoap_eml2_1::witsml20__ChannelStatus channelStatus);
	
		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		WellboreGeometry(gsoap_eml2_1::witsml20__WellboreGeometry* fromGsoap) :WellboreObject(fromGsoap) {}

		/**
		* Destructor does nothing since the memory is managed by the gsoap context.
		*/
		~WellboreGeometry() {}

		DLL_IMPORT_OR_EXPORT COMMON_NS::DataObjectReference getWellboreDor() const;
		DLL_IMPORT_OR_EXPORT void setWellbore(class Wellbore* witsmlWellbore);

		GETTER_AND_SETTER_DEPTH_MEASURE_OPTIONAL_ATTRIBUTE(MdBase, gsoap_eml2_1::eml21__LengthUom)

		GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE(GapAir, gsoap_eml2_1::eml21__LengthUom)
		GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE(DepthWaterMean, gsoap_eml2_1::eml21__LengthUom)

		//***************************************
		//************** SECTION ****************
		//***************************************

		// Mandatory
		GETTER_AND_SETTER_GENERIC_ATTRIBUTE_IN_VECTOR(std::string, WellboreGeometrySection, uid)

		// Optional bool
		GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IN_VECTOR(bool, WellboreGeometrySection, CurveConductor)

		// Optional double
		GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IN_VECTOR(double, WellboreGeometrySection, FactFric)

		// Optional string
		GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IN_VECTOR(std::string, WellboreGeometrySection, Grade)

		// Optional enum
		GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IN_VECTOR(gsoap_eml2_1::witsml20__HoleCasingType, WellboreGeometrySection, TypeHoleCasing)

		// Optional Length Measure
		GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IN_VECTOR(WellboreGeometrySection, IdSection, gsoap_eml2_1::eml21__LengthUom)
		GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IN_VECTOR(WellboreGeometrySection, OdSection, gsoap_eml2_1::eml21__LengthUom)
		GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IN_VECTOR(WellboreGeometrySection, DiaDrift, gsoap_eml2_1::eml21__LengthUom)

		// Optional Mass per Length Measure
		GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IN_VECTOR(WellboreGeometrySection, WtPerLen, gsoap_eml2_1::eml21__MassPerLengthUom)

		DLL_IMPORT_OR_EXPORT void setWellboreGeometrySectionMdInterval(unsigned int index, double top, double base, const std::string & datum, gsoap_eml2_1::eml21__LengthUom uom);
		DLL_IMPORT_OR_EXPORT double getWellboreGeometrySectionMdIntervalTop(unsigned int index) const;
		DLL_IMPORT_OR_EXPORT gsoap_eml2_1::eml21__LengthUom getWellboreGeometrySectionMdIntervalTopUom(unsigned int index) const;
		DLL_IMPORT_OR_EXPORT double getWellboreGeometrySectionMdIntervalBase(unsigned int index) const;
		DLL_IMPORT_OR_EXPORT gsoap_eml2_1::eml21__LengthUom getWellboreGeometrySectionMdIntervalBaseUom(unsigned int index) const;
		DLL_IMPORT_OR_EXPORT std::string getWellboreGeometrySectionMdIntervaldatum(unsigned int index) const;
		DLL_IMPORT_OR_EXPORT bool hasWellboreGeometrySectionMdInterval(unsigned int index) const;

		DLL_IMPORT_OR_EXPORT void setWellboreGeometrySectionTvdInterval(unsigned int index, double top, double base, const std::string & datum, gsoap_eml2_1::eml21__LengthUom uom);
		DLL_IMPORT_OR_EXPORT double getWellboreGeometrySectionTvdIntervalTop(unsigned int index) const;
		DLL_IMPORT_OR_EXPORT gsoap_eml2_1::eml21__LengthUom getWellboreGeometrySectionTvdIntervalTopUom(unsigned int index) const;
		DLL_IMPORT_OR_EXPORT double getWellboreGeometrySectionTvdIntervalBase(unsigned int index) const;
		DLL_IMPORT_OR_EXPORT gsoap_eml2_1::eml21__LengthUom getWellboreGeometrySectionTvdIntervalBaseUom(unsigned int index) const;
		DLL_IMPORT_OR_EXPORT std::string getWellboreGeometrySectionTvdIntervaldatum(unsigned int index) const;
		DLL_IMPORT_OR_EXPORT bool hasWellboreGeometrySectionTvdInterval(unsigned int index) const;

		/**
		* Push back an empty section into the isntance.
		*/
		DLL_IMPORT_OR_EXPORT void pushBackSection(const std::string & uid = "");

		/**
		* Get the count of sections in this instance
		*
		* @return the count of sections in this instance
		*/
		DLL_IMPORT_OR_EXPORT unsigned int getSectionCount() const;

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
