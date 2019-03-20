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

#define GLUE(a,b) a##b

#define GETTER_PRESENCE_ATTRIBUTE(attributeName) DLL_IMPORT_OR_EXPORT bool has##attributeName() const;
#define GETTER_PRESENCE_ATTRIBUTE_IMPL(className, attributeName) bool GLUE(,className)::has##attributeName() const { return static_cast<witsml2__##className*>(gsoapProxy2_1)->attributeName != nullptr; }

#define GETTER_AND_SETTER_GENERIC_ATTRIBUTE(attributeDatatype, attributeName)\
	DLL_IMPORT_OR_EXPORT void set##attributeName(const GLUE(,##attributeDatatype) & value);\
	DLL_IMPORT_OR_EXPORT GLUE(,##attributeDatatype) get##attributeName() const;
#define GETTER_AND_SETTER_GENERIC_ATTRIBUTE_IMPL(attributeDatatype, className, attributeName)\
	void GLUE(,className)::set##attributeName(const attributeDatatype & attributeName) { static_cast<witsml2__##className*>(gsoapProxy2_1)->attributeName = attributeName; }\
	attributeDatatype GLUE(,className)::get##attributeName() const { return static_cast<witsml2__##className*>(gsoapProxy2_1)->attributeName; }

#define GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE(attributeDatatype, attributeName)\
	GETTER_AND_SETTER_GENERIC_ATTRIBUTE(attributeDatatype, attributeName)\
	GETTER_PRESENCE_ATTRIBUTE(attributeName)
#define GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IMPL(attributeDatatype, className, attributeName, constructor)\
	void GLUE(,className)::set##attributeName(const attributeDatatype & attributeName) {\
		witsml2__##className* myInstance = static_cast<witsml2__##className*>(gsoapProxy2_1);\
		if (myInstance->attributeName == nullptr) { myInstance->attributeName = constructor(gsoapProxy2_1->soap, 1); }\
		*myInstance->attributeName = attributeName;\
	}\
	GETTER_PRESENCE_ATTRIBUTE_IMPL(className, attributeName)\
	attributeDatatype GLUE(,className)::get##attributeName() const {\
		if (!has##attributeName()) { throw invalid_argument("The string attribute to get does not exist."); }\
		return *static_cast<witsml2__##className*>(gsoapProxy2_1)->attributeName;\
	}

#define GETTER_AND_SETTER_TIME_T_ATTRIBUTE(attributeName)\
	DLL_IMPORT_OR_EXPORT void set##attributeName(time_t attributeName);\
	GETTER_PRESENCE_ATTRIBUTE(attributeName)\
	DLL_IMPORT_OR_EXPORT time_t get##attributeName() const;
#define GETTER_AND_SETTER_TIME_T_ATTRIBUTE_IMPL(className, attributeName)\
	void GLUE(,className)::set##attributeName(time_t attributeName) {\
		witsml2__##className* myInstance = static_cast<witsml2__##className*>(gsoapProxy2_1);\
		if (myInstance->attributeName == nullptr) { myInstance->attributeName = gsoap_eml2_1::soap_new_std__string(gsoapProxy2_1->soap, 1); }\
		*myInstance->attributeName = timeTools::convertUnixTimestampToIso(attributeName);\
	}\
	GETTER_PRESENCE_ATTRIBUTE_IMPL(className, attributeName)\
	time_t GLUE(,className)::get##attributeName() const {\
		if (!has##attributeName()) { throw invalid_argument("The string timestamp attribute to get does not exist."); }\
		return timeTools::convertIsoToUnixTimestamp(*static_cast<witsml2__##className*>(gsoapProxy2_1)->attributeName);\
	}

#define GETTER_AND_SETTER_LENGTH_MEASURE_ATTRIBUTE(attributeName)\
	DLL_IMPORT_OR_EXPORT void set##attributeName(double value, gsoap_eml2_1::eml21__LengthUom uom);\
	GETTER_PRESENCE_ATTRIBUTE(attributeName)\
	DLL_IMPORT_OR_EXPORT double get##attributeName##Value() const;\
	DLL_IMPORT_OR_EXPORT gsoap_eml2_1::eml21__LengthUom get##attributeName##Uom() const;
#define GETTER_LENGTH_MEASURE_VALUE_IMPL(className, attributeName)\
	double GLUE(,className)::get##attributeName##Value() const {\
		if (!has##attributeName()) { throw invalid_argument("The length measure attribute to get does not exist."); }\
		return static_cast<witsml2__##className*>(gsoapProxy2_1)->attributeName->__item;\
	}
#define GETTER_LENGTH_MEASURE_UOM_IMPL(className, attributeName)\
	gsoap_eml2_1::eml21__LengthUom GLUE(,className)::get##attributeName##Uom() const {\
		if (!has##attributeName()) { throw invalid_argument("The length measure attribute to get does not exist."); }\
		return static_cast<witsml2__##className*>(gsoapProxy2_1)->attributeName->uom;\
	}
#define GETTER_AND_SETTER_LENGTH_MEASURE_ATTRIBUTE_IMPL(className, attributeName)\
	void GLUE(,className)::set##attributeName(double value, gsoap_eml2_1::eml21__LengthUom uom) {\
		if (value != value) { throw invalid_argument("You cannot set an undefined length measure"); }\
		witsml2__##className* myInstance = static_cast<witsml2__##className*>(gsoapProxy2_1);\
		if (myInstance->attributeName == nullptr) { myInstance->attributeName = gsoap_eml2_1::soap_new_eml21__LengthMeasure(gsoapProxy2_1->soap, 1); }\
		myInstance->attributeName->__item = value;\
		myInstance->attributeName->uom = uom;\
	}\
	GETTER_PRESENCE_ATTRIBUTE_IMPL(className, attributeName)\
	GETTER_LENGTH_MEASURE_VALUE_IMPL(className, attributeName)\
	GETTER_LENGTH_MEASURE_UOM_IMPL(className, attributeName)
#define GETTER_AND_SETTER_WELL_ELEVATION_COORD_ATTRIBUTE_IMPL(className, attributeName)\
	void GLUE(,className)::set##attributeName(double value, gsoap_eml2_1::eml21__LengthUom uom) {\
		if (value != value) { throw invalid_argument("You cannot set an undefined well elevation coord"); }\
		witsml2__##className* myInstance = static_cast<witsml2__##className*>(gsoapProxy2_1);\
		if (myInstance->attributeName == nullptr) { myInstance->attributeName = gsoap_eml2_1::soap_new_witsml2__WellElevationCoord(gsoapProxy2_1->soap, 1); }\
		myInstance->attributeName->__item = value;\
		myInstance->attributeName->uom = uom;\
	}\
	GETTER_PRESENCE_ATTRIBUTE_IMPL(className, attributeName)\
	GETTER_LENGTH_MEASURE_VALUE_IMPL(className, attributeName)\
	GETTER_LENGTH_MEASURE_UOM_IMPL(className, attributeName)
#define GETTER_AND_SETTER_MEASURED_DEPTH_COORD_ATTRIBUTE_IMPL(className, attributeName)\
	void GLUE(,className)::set##attributeName(double value, gsoap_eml2_1::eml21__LengthUom uom) {\
		if (value != value) { throw invalid_argument("You cannot set an undefined well elevation coord"); }\
		witsml2__##className* myInstance = static_cast<witsml2__##className*>(gsoapProxy2_1);\
		if (myInstance->attributeName == nullptr) { myInstance->attributeName = gsoap_eml2_1::soap_new_witsml2__MeasuredDepthCoord(gsoapProxy2_1->soap, 1); }\
		myInstance->attributeName->__item = value;\
		myInstance->attributeName->uom = uom;\
	}\
	GETTER_PRESENCE_ATTRIBUTE_IMPL(className, attributeName)\
	GETTER_LENGTH_MEASURE_VALUE_IMPL(className, attributeName)\
	GETTER_LENGTH_MEASURE_UOM_IMPL(className, attributeName)

#define GETTER_AND_SETTER_PLANE_ANGLE_MEASURE_ATTRIBUTE(attributeName)\
	DLL_IMPORT_OR_EXPORT void set##attributeName(double value, gsoap_eml2_1::eml21__PlaneAngleUom uom);\
	GETTER_PRESENCE_ATTRIBUTE(attributeName)\
	DLL_IMPORT_OR_EXPORT double get##attributeName##Value() const;\
	DLL_IMPORT_OR_EXPORT gsoap_eml2_1::eml21__PlaneAngleUom get##attributeName##Uom() const;
#define GETTER_AND_SETTER_PLANE_ANGLE_MEASURE_ATTRIBUTE_IMPL(className, attributeName)\
	void GLUE(,className)::set##attributeName(double value, gsoap_eml2_1::eml21__PlaneAngleUom uom) {\
		if (value != value) { throw invalid_argument("You cannot set an undefined length measure"); }\
		witsml2__##className* myInstance = static_cast<witsml2__##className*>(gsoapProxy2_1);\
		if (myInstance->attributeName == nullptr) { myInstance->attributeName = gsoap_eml2_1::soap_new_eml21__PlaneAngleMeasure(gsoapProxy2_1->soap, 1); }\
		myInstance->attributeName->__item = value;\
		myInstance->attributeName->uom = uom;\
	}\
	GETTER_PRESENCE_ATTRIBUTE_IMPL(className, attributeName)\
	double GLUE(,className)::get##attributeName##Value() const {\
		if (!has##attributeName()) { throw invalid_argument("The length measure attribute to get does not exist."); }\
		return static_cast<witsml2__##className*>(gsoapProxy2_1)->attributeName->__item;\
	}\
	gsoap_eml2_1::eml21__PlaneAngleUom GLUE(,className)::get##attributeName##Uom() const {\
		if (!has##attributeName()) { throw invalid_argument("The length measure attribute to get does not exist."); }\
		return static_cast<witsml2__##className*>(gsoapProxy2_1)->attributeName->uom;\
	}
