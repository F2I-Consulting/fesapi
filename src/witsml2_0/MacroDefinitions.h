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

#define CHECK_RANGE(vector, index) if (index >= vector.size()) { throw std::range_error("The index is out of range"); }
#define CHECK_ATTRIBUTE_EXISTENCE(className, attributeName) if (static_cast<witsml2__##className*>(gsoapProxy2_1)->attributeName == nullptr) { throw std::invalid_argument("The attribute does not exist"); }
#define CHECK_ATTRIBUTE_IN_VECTOR_EXISTENCE(className, vectorName, attributeName) \
		CHECK_RANGE(static_cast<witsml2__##className*>(gsoapProxy2_1)->##vectorName, index)\
		if (static_cast<witsml2__##className*>(gsoapProxy2_1)->##vectorName[index]->attributeName == nullptr) { throw std::invalid_argument("The attribute in vector does not exist"); }
#define CREATE_ATTRIBUTE_IF_NOT_PRESENT(className, attributeName, constructor) if (static_cast<witsml2__##className*>(gsoapProxy2_1)->attributeName == nullptr) { static_cast<witsml2__##className*>(gsoapProxy2_1)->attributeName = constructor(gsoapProxy2_1->soap, 1); }
#define CREATE_ATTRIBUTE_IN_VECTOR_IF_NOT_PRESENT(className, vectorName, attributeName, constructor)\
		CHECK_RANGE(static_cast<witsml2__##className*>(gsoapProxy2_1)->##vectorName, index)\
		if (static_cast<witsml2__##className*>(gsoapProxy2_1)->##vectorName[index]->attributeName == nullptr) { static_cast<witsml2__##className*>(gsoapProxy2_1)->##vectorName[index]->attributeName = constructor(gsoapProxy2_1->soap, 1); }

#define GETTER_PRESENCE_ATTRIBUTE(attributeName) DLL_IMPORT_OR_EXPORT bool has##attributeName() const;
#define GETTER_PRESENCE_ATTRIBUTE_IMPL(className, attributeName) bool GLUE(,className)::has##attributeName() const { return static_cast<witsml2__##className*>(gsoapProxy2_1)->attributeName != nullptr; }
#define GETTER_PRESENCE_ATTRIBUTE_IN_VECTOR(vectorName, attributeName) DLL_IMPORT_OR_EXPORT bool has##vectorName##attributeName(unsigned int index) const;
#define GETTER_PRESENCE_ATTRIBUTE_IN_VECTOR_IMPL(className, vectorName, attributeName) bool GLUE(,className)::has##vectorName##attributeName(unsigned int index) const {\
	CHECK_RANGE(static_cast<witsml2__##className*>(gsoapProxy2_1)->##vectorName, index)\
	return static_cast<witsml2__##className*>(gsoapProxy2_1)->##vectorName[index]->attributeName != nullptr;\
}

#define GETTER_AND_SETTER_GENERIC_ATTRIBUTE(attributeDatatype, attributeName)\
	DLL_IMPORT_OR_EXPORT void set##attributeName(const attributeDatatype & value);\
	DLL_IMPORT_OR_EXPORT attributeDatatype get##attributeName() const;
#define GETTER_AND_SETTER_GENERIC_ATTRIBUTE_IMPL(attributeDatatype, className, attributeName)\
	void GLUE(,className)::set##attributeName(const attributeDatatype & value) { static_cast<witsml2__##className*>(gsoapProxy2_1)->attributeName = value; }\
	attributeDatatype GLUE(,className)::get##attributeName() const { return static_cast<witsml2__##className*>(gsoapProxy2_1)->attributeName; }
#define GETTER_AND_SETTER_GENERIC_ATTRIBUTE_IN_VECTOR(attributeDatatype, vectorName, attributeName)\
	DLL_IMPORT_OR_EXPORT void set##vectorName##attributeName(unsigned int index, const attributeDatatype & value);\
	DLL_IMPORT_OR_EXPORT attributeDatatype get##vectorName##attributeName(unsigned int index) const;
#define GETTER_AND_SETTER_GENERIC_ATTRIBUTE_IN_VECTOR_IMPL(attributeDatatype, className, vectorName, attributeName)\
	void GLUE(,className)::set##vectorName##attributeName(unsigned int index, const attributeDatatype & value) {\
		CHECK_RANGE(static_cast<witsml2__##className*>(gsoapProxy2_1)->##vectorName, index)\
		static_cast<witsml2__##className*>(gsoapProxy2_1)->##vectorName[index]->attributeName = value;\
	}\
	attributeDatatype GLUE(,className)::get##vectorName##attributeName(unsigned int index) const {\
		CHECK_RANGE(static_cast<witsml2__##className*>(gsoapProxy2_1)->##vectorName, index)\
		return static_cast<witsml2__##className*>(gsoapProxy2_1)->##vectorName[index]->attributeName;\
	}

#define GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE(attributeDatatype, attributeName)\
	GETTER_AND_SETTER_GENERIC_ATTRIBUTE(attributeDatatype, attributeName)\
	GETTER_PRESENCE_ATTRIBUTE(attributeName)
#define GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IMPL(attributeDatatype, className, attributeName, constructor)\
	void GLUE(,className)::set##attributeName(const attributeDatatype & attributeName) {\
		CREATE_ATTRIBUTE_IF_NOT_PRESENT(className, attributeName, constructor)\
		*static_cast<witsml2__##className*>(gsoapProxy2_1)->attributeName = attributeName;\
	}\
	GETTER_PRESENCE_ATTRIBUTE_IMPL(className, attributeName)\
	attributeDatatype GLUE(,className)::get##attributeName() const {\
		CHECK_ATTRIBUTE_EXISTENCE(className, attributeName)\
		return *static_cast<witsml2__##className*>(gsoapProxy2_1)->attributeName;\
	}
#define GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IN_VECTOR(attributeDatatype, vectorName, attributeName)\
	GETTER_AND_SETTER_GENERIC_ATTRIBUTE_IN_VECTOR(attributeDatatype, vectorName, attributeName)\
	GETTER_PRESENCE_ATTRIBUTE_IN_VECTOR(vectorName, attributeName)
#define GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IN_VECTOR_IMPL(attributeDatatype, className, vectorName, attributeName, constructor)\
	void GLUE(,className)::set##vectorName##attributeName(unsigned int index, const attributeDatatype & value) {\
		CHECK_RANGE(static_cast<witsml2__##className*>(gsoapProxy2_1)->##vectorName, index)\
		CREATE_ATTRIBUTE_IN_VECTOR_IF_NOT_PRESENT(className, vectorName, attributeName, constructor)\
		*static_cast<witsml2__##className*>(gsoapProxy2_1)->##vectorName[index]->attributeName = value;\
	}\
	GETTER_PRESENCE_ATTRIBUTE_IN_VECTOR_IMPL(className, vectorName, attributeName)\
	attributeDatatype GLUE(,className)::get##vectorName##attributeName(unsigned int index) const {\
		CHECK_RANGE(static_cast<witsml2__##className*>(gsoapProxy2_1)->##vectorName, index)\
		CHECK_ATTRIBUTE_IN_VECTOR_EXISTENCE(className, vectorName, attributeName)\
		return *static_cast<witsml2__##className*>(gsoapProxy2_1)->##vectorName[index]->attributeName;\
	}

#define GETTER_AND_SETTER_TIME_T_OPTIONAL_ATTRIBUTE_IMPL(className, attributeName)\
	void GLUE(,className)::set##attributeName(const time_t & attributeName) {\
		CREATE_ATTRIBUTE_IF_NOT_PRESENT(className, attributeName, gsoap_eml2_1::soap_new_std__string)\
		*static_cast<witsml2__##className*>(gsoapProxy2_1)->attributeName = timeTools::convertUnixTimestampToIso(attributeName);\
	}\
	GETTER_PRESENCE_ATTRIBUTE_IMPL(className, attributeName)\
	time_t GLUE(,className)::get##attributeName() const {\
		CHECK_ATTRIBUTE_EXISTENCE(className, attributeName)\
		return timeTools::convertIsoToUnixTimestamp(*static_cast<witsml2__##className*>(gsoapProxy2_1)->attributeName);\
	}
#define GETTER_AND_SETTER_TIME_T_OPTIONAL_ATTRIBUTE_IN_VECTOR_IMPL(className, vectorName, attributeName)\
	void GLUE(,className)::set##vectorName##attributeName(unsigned int index, const time_t & attributeName) {\
		CREATE_ATTRIBUTE_IN_VECTOR_IF_NOT_PRESENT(className, vectorName, attributeName, gsoap_eml2_1::soap_new_std__string)\
		*static_cast<witsml2__##className*>(gsoapProxy2_1)->##vectorName[index]->attributeName = timeTools::convertUnixTimestampToIso(attributeName);\
	}\
	GETTER_PRESENCE_ATTRIBUTE_IN_VECTOR_IMPL(className, vectorName, attributeName)\
	time_t GLUE(,className)::get##vectorName##attributeName(unsigned int index) const {\
		CHECK_RANGE(static_cast<witsml2__##className*>(gsoapProxy2_1)->##vectorName, index)\
		CHECK_ATTRIBUTE_IN_VECTOR_EXISTENCE(className, vectorName, attributeName)\
		return timeTools::convertIsoToUnixTimestamp(*static_cast<witsml2__##className*>(gsoapProxy2_1)->##vectorName[index]->attributeName);\
	}

#define GETTER_AND_SETTER_MEASURE_ATTRIBUTE(attributeName, uomDatatype)\
	DLL_IMPORT_OR_EXPORT void set##attributeName(double value, uomDatatype uom);\
	DLL_IMPORT_OR_EXPORT double get##attributeName##Value() const;\
	DLL_IMPORT_OR_EXPORT uomDatatype get##attributeName##Uom() const;
#define GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE(attributeName, uomDatatype)\
	GETTER_AND_SETTER_MEASURE_ATTRIBUTE(attributeName, uomDatatype)\
	GETTER_PRESENCE_ATTRIBUTE(attributeName)
#define GETTER_AND_SETTER_MEASURE_ATTRIBUTE_IN_VECTOR(vectorName, attributeName, uomDatatype)\
	DLL_IMPORT_OR_EXPORT void set##vectorName##attributeName(unsigned int index, double value, uomDatatype uom);\
	DLL_IMPORT_OR_EXPORT double get##vectorName##attributeName##Value(unsigned int index) const;\
	DLL_IMPORT_OR_EXPORT uomDatatype get##vectorName##attributeName##Uom(unsigned int index) const;
#define GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IN_VECTOR(vectorName, attributeName, uomDatatype)\
	GETTER_AND_SETTER_MEASURE_ATTRIBUTE_IN_VECTOR(vectorName, attributeName, uomDatatype)\
	GETTER_PRESENCE_ATTRIBUTE_IN_VECTOR(vectorName, attributeName)
#define GETTER_AND_SETTER_MEASURE_ATTRIBUTE_IMPL(className, attributeName, uomDatatype, constructor)\
	void GLUE(,className)::set##attributeName(double value, uomDatatype uom) {\
		if (value != value) { throw invalid_argument("You cannot set an undefined length measure"); }\
		CREATE_ATTRIBUTE_IF_NOT_PRESENT(className, attributeName, constructor)\
		static_cast<witsml2__##className*>(gsoapProxy2_1)->attributeName->__item = value;\
		static_cast<witsml2__##className*>(gsoapProxy2_1)->attributeName->uom = uom;\
	}\
	double GLUE(,className)::get##attributeName##Value() const {\
		if (!has##attributeName()) { throw invalid_argument("The length measure attribute to get does not exist."); }\
		return static_cast<witsml2__##className*>(gsoapProxy2_1)->attributeName->__item;\
	}\
	uomDatatype GLUE(, className)::get##attributeName##Uom() const {\
		if (!has##attributeName()) { throw invalid_argument("The length measure attribute to get does not exist."); }\
		return static_cast<witsml2__##className*>(gsoapProxy2_1)->attributeName->uom;\
	}
#define GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IMPL(className, attributeName, uomDatatype, constructor)\
	GETTER_AND_SETTER_MEASURE_ATTRIBUTE_IMPL(className, attributeName, uomDatatype, constructor)\
	GETTER_PRESENCE_ATTRIBUTE_IMPL(className, attributeName)
#define GETTER_AND_SETTER_MEASURE_ATTRIBUTE_IN_VECTOR_IMPL(className, vectorName, attributeName, uomDatatype, constructor)\
	void GLUE(,className)::set##vectorName##attributeName(unsigned int index, double value, uomDatatype uom) {\
		if (value != value) { throw invalid_argument("You cannot set an undefined measured depth coord"); }\
		CREATE_ATTRIBUTE_IN_VECTOR_IF_NOT_PRESENT(className, vectorName, attributeName, constructor)\
		static_cast<witsml2__##className*>(gsoapProxy2_1)->vectorName[index]->attributeName->__item = value;\
		static_cast<witsml2__##className*>(gsoapProxy2_1)->vectorName[index]->attributeName->uom = uom;\
	}\
	double GLUE(,className)::get##vectorName##attributeName##Value(unsigned int index) const {\
		CHECK_ATTRIBUTE_IN_VECTOR_EXISTENCE(className, vectorName, attributeName)\
		return static_cast<witsml2__##className*>(gsoapProxy2_1)->vectorName[index]->attributeName->__item;\
	}\
	uomDatatype GLUE(,className)::get##vectorName##attributeName##Uom(unsigned int index) const {\
		CHECK_ATTRIBUTE_IN_VECTOR_EXISTENCE(className, vectorName, attributeName)\
		return static_cast<witsml2__##className*>(gsoapProxy2_1)->vectorName[index]->attributeName->uom;\
	}
#define GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IN_VECTOR_IMPL(className, vectorName, attributeName, uomDatatype, constructor)\
	GETTER_AND_SETTER_MEASURE_ATTRIBUTE_IN_VECTOR_IMPL(className, vectorName, attributeName, uomDatatype, constructor)\
	GETTER_PRESENCE_ATTRIBUTE_IN_VECTOR_IMPL(className, vectorName, attributeName)
