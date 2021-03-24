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

/**
 * A macro that defines check range
 *
 * @param 	vector	The vector.
 * @param 	index 	Zero-based index of the.
 */
#define CHECK_RANGE_1_4(vector, index)\
	if (static_cast<witsml14__obj_USCOREtrajectory*>(gsoapProxyTraj1_4)->__obj_USCOREtrajectory_sequence == nullptr) { throw invalid_argument("There is no information about the trajectory in this instance"); }\
	if (index >= static_cast<witsml14__obj_USCOREtrajectory*>(gsoapProxyTraj1_4)->__obj_USCOREtrajectory_sequence->vector.size()) { throw std::range_error("The index is out of range"); }

/**
 * A macro that defines check attribute existence
 *
 * @param 	className	 	Name of the class.
 * @param 	attributeName	Name of the attribute.
 */
#define CHECK_ATTRIBUTE_EXISTENCE_1_4(className, attributeName)\
	if (static_cast<witsml14__obj_USCOREtrajectory*>(gsoapProxyTraj1_4)->__obj_USCOREtrajectory_sequence == nullptr || static_cast<witsml14__obj_USCOREtrajectory*>(gsoapProxyTraj1_4)->__obj_USCOREtrajectory_sequence->attributeName == nullptr) { throw std::invalid_argument("The attribute does not exist"); }

 /**
  * A macro that defines check attribute in vector existence
  *
  * @param 	className	 	Name of the class.
  * @param 	vectorName   	Name of the vector.
  * @param 	attributeName	Name of the attribute.
  */
#define CHECK_ATTRIBUTE_IN_VECTOR_EXISTENCE_1_4(className, vectorName, attributeName) \
	CHECK_RANGE_1_4(vectorName, index)\
	if (static_cast<witsml14__obj_USCOREtrajectory*>(gsoapProxyTraj1_4)->__obj_USCOREtrajectory_sequence->vectorName[index]->attributeName == nullptr) { throw std::invalid_argument("The attribute in vector does not exist"); }

/**
 * A macro that defines getter presence attribute Implementation
 *
 * @param 	className	 	Name of the class.
 * @param 	attributeName	Name of the attribute.
 */
#define GETTER_PRESENCE_ATTRIBUTE_IMPL_1_4(className, fesapiAttributeName, witsmlAttributeName) \
	bool GLUE(,className)::has##fesapiAttributeName() const\
		{ return static_cast<witsml14__obj_USCOREtrajectory*>(gsoapProxyTraj1_4)->__obj_USCOREtrajectory_sequence != nullptr && static_cast<witsml14__obj_USCOREtrajectory*>(gsoapProxyTraj1_4)->__obj_USCOREtrajectory_sequence->witsmlAttributeName != nullptr; }

#define GETTER_PRESENCE_ATTRIBUTE_IN_VECTOR_IMPL_1_4(className, fesapiVectorName, witsmlVectorName, fesapiAttributeName, witsmlAttributeName) bool GLUE(,className)::has##fesapiVectorName##fesapiAttributeName(unsigned int index) const {\
	CHECK_RANGE_1_4(witsmlVectorName, index)\
	return static_cast<witsml14__obj_USCOREtrajectory*>(gsoapProxyTraj1_4)->__obj_USCOREtrajectory_sequence->witsmlVectorName[index]->witsmlAttributeName != nullptr;\
}

/**
 * A macro that defines create attribute if not present
 *
 * @param 	className	 	Name of the class.
 * @param 	attributeName	Name of the attribute.
 * @param 	constructor  	The constructor.
 */
#define CREATE_ATTRIBUTE_IF_NOT_PRESENT_1_4(attributeName, constructor)\
	if (static_cast<witsml14__obj_USCOREtrajectory*>(gsoapProxyTraj1_4)->__obj_USCOREtrajectory_sequence == nullptr) { static_cast<witsml14__obj_USCOREtrajectory*>(gsoapProxyTraj1_4)->__obj_USCOREtrajectory_sequence = soap_new___witsml14__obj_USCOREtrajectory_sequence(gsoapProxyTraj1_4->soap); }\
	if (static_cast<witsml14__obj_USCOREtrajectory*>(gsoapProxyTraj1_4)->__obj_USCOREtrajectory_sequence->attributeName == nullptr) { static_cast<witsml14__obj_USCOREtrajectory*>(gsoapProxyTraj1_4)->__obj_USCOREtrajectory_sequence->attributeName = constructor(gsoapProxyTraj1_4->soap); }

 /**
  * A macro that defines create attribute in vector if not present
  *
  * @param 	className	 	Name of the class.
  * @param 	vectorName   	Name of the vector.
  * @param 	attributeName	Name of the attribute.
  * @param 	constructor  	The constructor.
  */
#define CREATE_ATTRIBUTE_IN_VECTOR_IF_NOT_PRESENT_1_4(vectorName, attributeName, constructor)\
	CHECK_RANGE_1_4(vectorName, index)\
	if (static_cast<witsml14__obj_USCOREtrajectory*>(gsoapProxyTraj1_4)->__obj_USCOREtrajectory_sequence->vectorName[index]->attributeName == nullptr) { static_cast<witsml14__obj_USCOREtrajectory*>(gsoapProxyTraj1_4)->__obj_USCOREtrajectory_sequence->vectorName[index]->attributeName = constructor(gsoapProxyTraj1_4->soap); }

 /**
  * A macro that defines getter and setter generic attribute in vector Implementation
  *
  * @param 	attributeDatatype	The attribute datatype.
  * @param 	className		 	Name of the class.
  * @param 	vectorName		 	Name of the vector.
  * @param 	attributeName	 	Name of the attribute.
  */
#define GETTER_AND_SETTER_ENUM_ATTRIBUTE_IN_VECTOR_IMPL_1_4(attributeDatatype, attributeDatatype14, className, fesapiVectorName, witsmlVectorName, fesapiAttributeName, witsmlAttributeName, eml2_1ToStr, strToEml2_1, witsml1_4ToStr, strToWitsml1_4)\
	void GLUE(,className)::set##fesapiVectorName##fesapiAttributeName(unsigned int index, const attributeDatatype & value) {\
		CHECK_RANGE_1_4(witsmlVectorName, index)\
		std::string attStr = eml2_1ToStr(gsoapProxyTraj1_4->soap, value);\
		attributeDatatype14 att1_4;\
		if (strToWitsml1_4(gsoapProxyTraj1_4->soap, attStr.c_str(), &att1_4) == SOAP_OK) { static_cast<witsml14__obj_USCOREtrajectory*>(gsoapProxyTraj1_4)->__obj_USCOREtrajectory_sequence->witsmlVectorName[index]->witsmlAttributeName = att1_4; }\
		else { throw invalid_argument("The enum " + attStr + " is not recognized."); }\
	}\
	attributeDatatype GLUE(,className)::get##fesapiVectorName##fesapiAttributeName(unsigned int index) const {\
		CHECK_RANGE_1_4(witsmlVectorName, index)\
		std::string attStr = witsml1_4ToStr(gsoapProxyTraj1_4->soap, static_cast<witsml14__obj_USCOREtrajectory*>(gsoapProxyTraj1_4)->__obj_USCOREtrajectory_sequence->witsmlVectorName[index]->witsmlAttributeName);\
		attributeDatatype att2_1;\
		if (strToEml2_1(gsoapProxyTraj1_4->soap, attStr.c_str(), &att2_1) == SOAP_OK) { return att2_1; }\
		else { throw invalid_argument("The enum " + attStr + " is not recognized."); }\
	}

 /**
  * A macro that defines getter and setter generic optional attribute Implementation
  *
  * @param 	attributeDatatype	The attribute datatype.
  * @param 	className		 	Name of the class.
  * @param 	attributeName	 	Name of the attribute.
  * @param 	constructor		 	The constructor.
  */
#define GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IMPL_1_4(attributeDatatype, className, fesapiAttributeName, witsmlAttributeName, constructor)\
	void GLUE(,className)::set##fesapiAttributeName(const attributeDatatype & attributeName) {\
		CREATE_ATTRIBUTE_IF_NOT_PRESENT_1_4(witsmlAttributeName, constructor)\
		*static_cast<witsml14__obj_USCOREtrajectory*>(gsoapProxyTraj1_4)->__obj_USCOREtrajectory_sequence->witsmlAttributeName = attributeName;\
	}\
	GETTER_PRESENCE_ATTRIBUTE_IMPL_1_4(className, fesapiAttributeName, witsmlAttributeName)\
	attributeDatatype GLUE(,className)::get##fesapiAttributeName() const {\
		CHECK_ATTRIBUTE_EXISTENCE_1_4(className, witsmlAttributeName)\
		return *static_cast<witsml14__obj_USCOREtrajectory*>(gsoapProxyTraj1_4)->__obj_USCOREtrajectory_sequence->witsmlAttributeName;\
	}

  /**
   * A macro that defines getter and setter generic optional attribute in vector Implementation
   *
   * @param 	attributeDatatype	The attribute datatype.
   * @param 	className		 	Name of the class.
   * @param 	vectorName		 	Name of the vector.
   * @param 	attributeName	 	Name of the attribute.
   * @param 	constructor		 	The constructor.
   */
#define GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IN_VECTOR_IMPL_1_4(attributeDatatype, className, fesapiVectorName, witsmlVectorName, fesapiAttributeName, witsmlAttributeName, constructor)\
	void GLUE(,className)::set##fesapiVectorName##fesapiAttributeName(unsigned int index, const attributeDatatype & value) {\
		CREATE_ATTRIBUTE_IN_VECTOR_IF_NOT_PRESENT_1_4(witsmlVectorName, witsmlAttributeName, constructor)\
		*static_cast<witsml14__obj_USCOREtrajectory*>(gsoapProxyTraj1_4)->__obj_USCOREtrajectory_sequence->witsmlVectorName[index]->witsmlAttributeName = value;\
	}\
	GETTER_PRESENCE_ATTRIBUTE_IN_VECTOR_IMPL_1_4(className, fesapiVectorName, witsmlVectorName, fesapiAttributeName, witsmlAttributeName)\
	attributeDatatype GLUE(,className)::get##fesapiVectorName##fesapiAttributeName(unsigned int index) const {\
		CHECK_ATTRIBUTE_IN_VECTOR_EXISTENCE_1_4(className, witsmlVectorName, witsmlAttributeName)\
		return *static_cast<witsml14__obj_USCOREtrajectory*>(gsoapProxyTraj1_4)->__obj_USCOREtrajectory_sequence->witsmlVectorName[index]->witsmlAttributeName;\
	}

#define GETTER_AND_SETTER_ENUM_OPTIONAL_ATTRIBUTE_IMPL_1_4(attributeDatatype, attributeDatatype14, className, fesapiAttributeName, witsmlAttributeName, constructor, eml2_1ToStr, strToEml2_1, witsml1_4ToStr, strToWitsml1_4)\
	void GLUE(,className)::set##fesapiAttributeName(const attributeDatatype & attributeName) {\
		CREATE_ATTRIBUTE_IF_NOT_PRESENT_1_4(witsmlAttributeName, constructor)\
		std::string attStr = eml2_1ToStr(gsoapProxyTraj1_4->soap, attributeName);\
		attributeDatatype14 att1_4;\
		if (strToWitsml1_4(gsoapProxyTraj1_4->soap, attStr.c_str(), &att1_4) == SOAP_OK) { *static_cast<witsml14__obj_USCOREtrajectory*>(gsoapProxyTraj1_4)->__obj_USCOREtrajectory_sequence->witsmlAttributeName = att1_4; }\
		else { throw invalid_argument("The enum " + attStr + " is not recognized."); }\
	}\
	GETTER_PRESENCE_ATTRIBUTE_IMPL_1_4(className, fesapiAttributeName, witsmlAttributeName)\
	attributeDatatype GLUE(,className)::get##fesapiAttributeName() const {\
		CHECK_ATTRIBUTE_EXISTENCE_1_4(className, witsmlAttributeName)\
		std::string attStr = witsml1_4ToStr(gsoapProxyTraj1_4->soap, *static_cast<witsml14__obj_USCOREtrajectory*>(gsoapProxyTraj1_4)->__obj_USCOREtrajectory_sequence->witsmlAttributeName);\
		attributeDatatype att2_1;\
		if (strToEml2_1(gsoapProxyTraj1_4->soap, attStr.c_str(), &att2_1) == SOAP_OK) { return att2_1; }\
		else { throw invalid_argument("The enum " + attStr + " is not recognized."); }\
	}

#define GETTER_AND_SETTER_ENUM_OPTIONAL_ATTRIBUTE_IN_VECTOR_IMPL_1_4(attributeDatatype, attributeDatatype14, className, fesapiVectorName, witsmlVectorName, fesapiAttributeName, witsmlAttributeName, constructor, eml2_1ToStr, strToEml2_1, witsml1_4ToStr, strToWitsml1_4)\
	void GLUE(,className)::set##fesapiVectorName##fesapiAttributeName(unsigned int index, const attributeDatatype & attributeName) {\
		CREATE_ATTRIBUTE_IN_VECTOR_IF_NOT_PRESENT_1_4(witsmlVectorName, witsmlAttributeName, constructor)\
		std::string attStr = eml2_1ToStr(gsoapProxyTraj1_4->soap, attributeName);\
		attributeDatatype14 att1_4;\
		if (strToWitsml1_4(gsoapProxyTraj1_4->soap, attStr.c_str(), &att1_4) == SOAP_OK) { *static_cast<witsml14__obj_USCOREtrajectory*>(gsoapProxyTraj1_4)->__obj_USCOREtrajectory_sequence->witsmlVectorName[index]->witsmlAttributeName = att1_4; }\
		else { throw invalid_argument("The enum " + attStr + " is not recognized."); }\
	}\
	GETTER_PRESENCE_ATTRIBUTE_IN_VECTOR_IMPL_1_4(className, fesapiVectorName, witsmlVectorName, fesapiAttributeName, witsmlAttributeName)\
	attributeDatatype GLUE(,className)::get##fesapiVectorName##fesapiAttributeName(unsigned int index) const {\
		CHECK_ATTRIBUTE_IN_VECTOR_EXISTENCE_1_4(className, witsmlVectorName, witsmlAttributeName)\
		std::string attStr = witsml1_4ToStr(gsoapProxyTraj1_4->soap, *static_cast<witsml14__obj_USCOREtrajectory*>(gsoapProxyTraj1_4)->__obj_USCOREtrajectory_sequence->witsmlVectorName[index]->witsmlAttributeName);\
		attributeDatatype att2_1;\
		if (strToEml2_1(gsoapProxyTraj1_4->soap, attStr.c_str(), &att2_1) == SOAP_OK) { return att2_1; }\
		else { throw invalid_argument("The enum " + attStr + " is not recognized."); }\
	}

/**
 * A macro that defines getter and setter time t optional attribute Implementation
 *
 * @param 	className	 	Name of the class.
 * @param 	attributeName	Name of the attribute.
 */
#define GETTER_AND_SETTER_TIME_T_OPTIONAL_ATTRIBUTE_IMPL_1_4(className, fesapiAttributeName, witsmlAttributeName)\
	void GLUE(,className)::set##fesapiAttributeName(const time_t & fesapiAttributeName) {\
		if (static_cast<witsml14__obj_USCOREtrajectory*>(gsoapProxyTraj1_4)->__obj_USCOREtrajectory_sequence == nullptr) { static_cast<witsml14__obj_USCOREtrajectory*>(gsoapProxyTraj1_4)->__obj_USCOREtrajectory_sequence = soap_new___witsml14__obj_USCOREtrajectory_sequence(gsoapProxyTraj1_4->soap); }\
		if (static_cast<witsml14__obj_USCOREtrajectory*>(gsoapProxyTraj1_4)->__obj_USCOREtrajectory_sequence->witsmlAttributeName == nullptr) { static_cast<witsml14__obj_USCOREtrajectory*>(gsoapProxyTraj1_4)->__obj_USCOREtrajectory_sequence->witsmlAttributeName = (tm*)soap_malloc(gsoapProxyTraj1_4->soap, sizeof(tm)); }\
		*static_cast<witsml14__obj_USCOREtrajectory*>(gsoapProxyTraj1_4)->__obj_USCOREtrajectory_sequence->witsmlAttributeName = timeTools::to_calendar_time(std::chrono::system_clock::from_time_t(fesapiAttributeName));\
	}\
	GETTER_PRESENCE_ATTRIBUTE_IMPL_1_4(className, fesapiAttributeName, witsmlAttributeName)\
	time_t GLUE(,className)::get##fesapiAttributeName() const {\
		CHECK_ATTRIBUTE_EXISTENCE_1_4(className, witsmlAttributeName)\
		return timeTools::timegm(*static_cast<witsml14__obj_USCOREtrajectory*>(gsoapProxyTraj1_4)->__obj_USCOREtrajectory_sequence->witsmlAttributeName);\
	}

  /**
   * A macro that defines getter value of measure attribute Implementation
   *
   * @param 	className	 	Name of the class.
   * @param 	attributeName	Name of the attribute.
   */
#define GETTER_VALUE_OF_MEASURE_ATTRIBUTE_IMPL_1_4(className, fesapiAttributeName, witsmlAttributeName)\
	double GLUE(,className)::get##fesapiAttributeName##Value() const {\
		if (!has##fesapiAttributeName()) { throw invalid_argument("The measure attribute to get does not exist."); }\
		return static_cast<witsml14__obj_USCOREtrajectory*>(gsoapProxyTraj1_4)->__obj_USCOREtrajectory_sequence->witsmlAttributeName->__item;\
	}

   /**
	* A macro that defines getter value of measure attribute in vector Implementation
	*
	* @param 	className	 	Name of the class.
	* @param 	vectorName   	Name of the vector.
	* @param 	attributeName	Name of the attribute.
	*/
#define GETTER_VALUE_OF_MEASURE_ATTRIBUTE_IN_VECTOR_IMPL_1_4(className, fesapiVectorName, witsmlVectorName, fesapiAttributeName, witsmlAttributeName)\
	double GLUE(,className)::get##fesapiVectorName##fesapiAttributeName##Value(unsigned int index) const {\
		CHECK_RANGE_1_4(witsmlVectorName, index)\
		return static_cast<witsml14__obj_USCOREtrajectory*>(gsoapProxyTraj1_4)->__obj_USCOREtrajectory_sequence->witsmlVectorName[index]->witsmlAttributeName->__item;\
	}

/**
* A macro that defines getter uom of measure attribute Implementation
*
* @param 	className	 	Name of the class.
* @param 	attributeName	Name of the attribute.
* @param 	uomDatatype  	The uom datatype.
*/
#define GETTER_UOM_OF_MEASURE_ATTRIBUTE_IMPL_1_4(className, fesapiAttributeName, witsmlAttributeName, uomDatatype, uom1_4ToStr, strToUom2_1)\
	uomDatatype GLUE(, className)::get##fesapiAttributeName##Uom() const {\
		if (!has##fesapiAttributeName()) { throw invalid_argument("The measure attribute to get does not exist."); }\
		std::string uomStr = uom1_4ToStr(gsoapProxyTraj1_4->soap, static_cast<witsml14__obj_USCOREtrajectory*>(gsoapProxyTraj1_4)->__obj_USCOREtrajectory_sequence->witsmlAttributeName->uom);\
		uomDatatype result;\
		if (strToUom2_1(gsoapProxyTraj1_4->soap, uomStr.c_str(), &result) == SOAP_OK) { return result; }\
		else { throw invalid_argument("The uom " + uomStr + " is not recognized."); }\
	}

/**
 * A macro that defines getter uom of measure attribute in vector Implementation
 *
 * @param 	className	 	Name of the class.
 * @param 	vectorName   	Name of the vector.
 * @param 	attributeName	Name of the attribute.
 * @param 	uomDatatype  	The uom datatype.
 */
#define GETTER_UOM_OF_MEASURE_ATTRIBUTE_IN_VECTOR_IMPL_1_4(className, fesapiVectorName, witsmlVectorName, fesapiAttributeName, witsmlAttributeName, uomDatatype, uom1_4ToStr, strToUom2_1)\
	uomDatatype GLUE(,className)::get##fesapiVectorName##fesapiAttributeName##Uom(unsigned int index) const {\
		CHECK_RANGE_1_4(witsmlVectorName, index)\
		std::string uomStr = uom1_4ToStr(gsoapProxyTraj1_4->soap, static_cast<witsml14__obj_USCOREtrajectory*>(gsoapProxyTraj1_4)->__obj_USCOREtrajectory_sequence->witsmlVectorName[index]->witsmlAttributeName->uom);\
		uomDatatype result;\
		if (strToUom2_1(gsoapProxyTraj1_4->soap, uomStr.c_str(), &result) == SOAP_OK) { return result; }\
		else { throw invalid_argument("The uom " + uomStr + " is not recognized."); }\
	}

/**
 * A macro that defines getter uom (as string) of measure attribute Implementation
 *
 * @param 	className	 	Name of the class.
 * @param 	attributeName	Name of the attribute.
 * @param 	uomDatatype  	The uom datatype.
 */
#define GETTER_UOM_OF_MEASURE_AS_STRING_ATTRIBUTE_IMPL_1_4(className, fesapiAttributeName, witsmlAttributeName, uomDatatypeStringConversion)\
	std::string GLUE(, className)::get##fesapiAttributeName##UomAsString() const {\
		return uomDatatypeStringConversion(gsoapProxyTraj1_4->soap, get##fesapiAttributeName##Uom());\
	}

/**
 * A macro that defines getter and setter measure attribute Implementation
 *
 * @param 	className	 	Name of the class.
 * @param 	attributeName	Name of the attribute.
 * @param 	uomDatatype  	The uom datatype.
 * @param 	constructor  	The constructor.
 */
#define GETTER_AND_SETTER_MEASURE_ATTRIBUTE_IMPL_1_4(className, fesapiAttributeName, witsmlAttributeName, uomDatatype, uomDatatype14, constructor, eml2_1ToStr, strToEml2_1, witsml1_4ToStr, strToWitsml1_4)\
	void GLUE(,className)::set##fesapiAttributeName(double value, uomDatatype uom) {\
		if (value != value) { throw invalid_argument("You cannot set an undefined measure"); }\
		CREATE_ATTRIBUTE_IF_NOT_PRESENT_1_4(witsmlAttributeName, constructor)\
		static_cast<witsml14__obj_USCOREtrajectory*>(gsoapProxyTraj1_4)->__obj_USCOREtrajectory_sequence->witsmlAttributeName->__item = value;\
		std::string uomStr = eml2_1ToStr(gsoapProxyTraj1_4->soap, uom);\
		uomDatatype14 uom1_4;\
		if (strToWitsml1_4(gsoapProxyTraj1_4->soap, uomStr.c_str(), &uom1_4) == SOAP_OK) { static_cast<witsml14__obj_USCOREtrajectory*>(gsoapProxyTraj1_4)->__obj_USCOREtrajectory_sequence->witsmlAttributeName->uom = uom1_4; }\
		else { throw invalid_argument("The depth uom " + uomStr + " is not recognized."); }\
	}\
	GETTER_VALUE_OF_MEASURE_ATTRIBUTE_IMPL_1_4(className, fesapiAttributeName, witsmlAttributeName)\
	GETTER_UOM_OF_MEASURE_ATTRIBUTE_IMPL_1_4(className, fesapiAttributeName, witsmlAttributeName, uomDatatype, witsml1_4ToStr, strToEml2_1)\
	GETTER_UOM_OF_MEASURE_AS_STRING_ATTRIBUTE_IMPL_1_4(className, fesapiAttributeName, witsmlAttributeName, eml2_1ToStr)

 /**
  * A macro that defines getter and setter measure attribute in vector Implementation
  *
  * @param 	className	 	Name of the class.
  * @param 	vectorName   	Name of the vector.
  * @param 	attributeName	Name of the attribute.
  * @param 	uomDatatype  	The uom datatype.
  * @param 	constructor  	The constructor.
  */
#define GETTER_AND_SETTER_MEASURE_ATTRIBUTE_IN_VECTOR_IMPL_1_4(className, fesapiVectorName, witsmlVectorName, fesapiAttributeName, witsmlAttributeName, uomDatatype, uomDatatype14, constructor, eml2_1ToStr, strToEml2_1, witsml1_4ToStr, strToWitsml1_4)\
	void GLUE(,className)::set##fesapiVectorName##fesapiAttributeName(unsigned int index, double value, uomDatatype uom) {\
		if (value != value) { throw invalid_argument("You cannot set an undefined measured depth coord"); }\
		CREATE_ATTRIBUTE_IN_VECTOR_IF_NOT_PRESENT_1_4(witsmlVectorName, witsmlAttributeName, constructor)\
		static_cast<witsml14__obj_USCOREtrajectory*>(gsoapProxyTraj1_4)->__obj_USCOREtrajectory_sequence->witsmlVectorName[index]->witsmlAttributeName->__item = value;\
		std::string uomStr = eml2_1ToStr(gsoapProxyTraj1_4->soap, uom);\
		uomDatatype14 uom1_4;\
		if (strToWitsml1_4(gsoapProxyTraj1_4->soap, uomStr.c_str(), &uom1_4) == SOAP_OK) { static_cast<witsml14__obj_USCOREtrajectory*>(gsoapProxyTraj1_4)->__obj_USCOREtrajectory_sequence->witsmlVectorName[index]->witsmlAttributeName->uom = uom1_4; }\
		else { throw invalid_argument("The depth uom " + uomStr + " is not recognized."); }\
	}\
	GETTER_VALUE_OF_MEASURE_ATTRIBUTE_IN_VECTOR_IMPL_1_4(className, fesapiVectorName, witsmlVectorName, fesapiAttributeName, witsmlAttributeName)\
	GETTER_UOM_OF_MEASURE_ATTRIBUTE_IN_VECTOR_IMPL_1_4(className, fesapiVectorName, witsmlVectorName, fesapiAttributeName, witsmlAttributeName, uomDatatype, witsml1_4ToStr, strToEml2_1)

 /**
  * A macro that defines getter and setter depth measure attribute Implementation
  *
  * @param 	className	 	Name of the class.
  * @param 	attributeName	Name of the attribute.
  * @param 	uomDatatype  	The uom datatype.
  * @param 	constructor  	The constructor.
  */
#define GETTER_AND_SETTER_DEPTH_MEASURE_ATTRIBUTE_IMPL_1_4(className, fesapiAttributeName, witsmlAttributeName, uomDatatype, constructor)\
	void GLUE(,className)::set##fesapiAttributeName(double value, uomDatatype uom, const std::string & datum) {\
		if (value != value) { throw invalid_argument("You cannot set an undefined depth measure"); }\
		CREATE_ATTRIBUTE_IF_NOT_PRESENT_1_4(witsmlAttributeName, constructor)\
		static_cast<witsml14__obj_USCOREtrajectory*>(gsoapProxyTraj1_4)->__obj_USCOREtrajectory_sequence->witsmlAttributeName->__item = value;\
		std::string uomStr = gsoap_eml2_1::soap_eml21__LengthUom2s(gsoapProxyTraj1_4->soap, uom);\
		witsml14__MeasuredDepthUom uom1_4;\
		if (soap_s2witsml14__MeasuredDepthUom(gsoapProxyTraj1_4->soap, uomStr.c_str(), &uom1_4) == SOAP_OK) { static_cast<witsml14__obj_USCOREtrajectory*>(gsoapProxyTraj1_4)->__obj_USCOREtrajectory_sequence->witsmlAttributeName->uom = uom1_4; }\
		else { throw invalid_argument("The depth uom " + uomStr + " is not recognized."); }\
		if (!datum.empty()) {\
			static_cast<witsml14__obj_USCOREtrajectory*>(gsoapProxyTraj1_4)->__obj_USCOREtrajectory_sequence->witsmlAttributeName->datum = soap_new_std__string(gsoapProxyTraj1_4->soap);\
			static_cast<witsml14__obj_USCOREtrajectory*>(gsoapProxyTraj1_4)->__obj_USCOREtrajectory_sequence->witsmlAttributeName->datum->assign(datum);\
		}\
	}\
	GETTER_VALUE_OF_MEASURE_ATTRIBUTE_IMPL_1_4(className, fesapiAttributeName, witsmlAttributeName)\
	GETTER_UOM_OF_MEASURE_ATTRIBUTE_IMPL_1_4(className, fesapiAttributeName, witsmlAttributeName, uomDatatype, soap_witsml14__MeasuredDepthUom2s, gsoap_eml2_1::soap_s2eml21__LengthUom)\
	std::string GLUE(, className)::get##fesapiAttributeName##Datum() const {\
		if (!has##fesapiAttributeName()) { throw invalid_argument("The measure attribute to get does not exist."); }\
		if (static_cast<witsml14__obj_USCOREtrajectory*>(gsoapProxyTraj1_4)->__obj_USCOREtrajectory_sequence->witsmlAttributeName->datum == nullptr) return "";\
		return *static_cast<witsml14__obj_USCOREtrajectory*>(gsoapProxyTraj1_4)->__obj_USCOREtrajectory_sequence->witsmlAttributeName->datum;\
	}

  /**
   * A macro that defines getter and setter depth measure attribute in vector Implementation
   *
   * @param 	className	 	Name of the class.
   * @param 	vectorName   	Name of the vector.
   * @param 	attributeName	Name of the attribute.
   * @param 	uomDatatype  	The uom datatype.
   * @param 	constructor  	The constructor.
   */
#define GETTER_AND_SETTER_DEPTH_MEASURE_ATTRIBUTE_IN_VECTOR_IMPL_1_4(className, fesapiVectorName, witsmlVectorName, fesapiAttributeName, witsmlAttributeName, uomDatatype, constructor)\
	void GLUE(,className)::set##fesapiVectorName##fesapiAttributeName(unsigned int index, double value, uomDatatype uom, const std::string & datum) {\
		if (value != value) { throw invalid_argument("You cannot set an undefined measured depth coord"); }\
		CREATE_ATTRIBUTE_IN_VECTOR_IF_NOT_PRESENT_1_4(witsmlVectorName, witsmlAttributeName, constructor)\
		static_cast<witsml14__obj_USCOREtrajectory*>(gsoapProxyTraj1_4)->__obj_USCOREtrajectory_sequence->witsmlVectorName[index]->witsmlAttributeName->__item = value;\
		std::string uomStr = gsoap_eml2_1::soap_eml21__LengthUom2s(gsoapProxyTraj1_4->soap, uom);\
		witsml14__MeasuredDepthUom uom1_4;\
		if (soap_s2witsml14__MeasuredDepthUom(gsoapProxyTraj1_4->soap, uomStr.c_str(), &uom1_4) == SOAP_OK) { static_cast<witsml14__obj_USCOREtrajectory*>(gsoapProxyTraj1_4)->__obj_USCOREtrajectory_sequence->witsmlVectorName[index]->witsmlAttributeName->uom = uom1_4; }\
		else { throw invalid_argument("The depth uom " + uomStr + " is not recognized."); }\
		if (!datum.empty()) {\
			static_cast<witsml14__obj_USCOREtrajectory*>(gsoapProxyTraj1_4)->__obj_USCOREtrajectory_sequence->witsmlVectorName[index]->witsmlAttributeName->datum = soap_new_std__string(gsoapProxyTraj1_4->soap);\
			static_cast<witsml14__obj_USCOREtrajectory*>(gsoapProxyTraj1_4)->__obj_USCOREtrajectory_sequence->witsmlVectorName[index]->witsmlAttributeName->datum->assign(datum);\
		}\
	}\
	GETTER_VALUE_OF_MEASURE_ATTRIBUTE_IN_VECTOR_IMPL_1_4(className, fesapiVectorName, witsmlVectorName, fesapiAttributeName, witsmlAttributeName)\
	GETTER_UOM_OF_MEASURE_ATTRIBUTE_IN_VECTOR_IMPL_1_4(className, fesapiVectorName, witsmlVectorName, fesapiAttributeName, witsmlAttributeName, uomDatatype, soap_witsml14__MeasuredDepthUom2s, gsoap_eml2_1::soap_s2eml21__LengthUom)\
	std::string GLUE(, className)::get##fesapiVectorName##fesapiAttributeName##Datum(unsigned int index) const {\
		CHECK_RANGE_1_4(witsmlVectorName, index)\
		if (static_cast<witsml14__obj_USCOREtrajectory*>(gsoapProxyTraj1_4)->__obj_USCOREtrajectory_sequence->witsmlVectorName[index]->witsmlAttributeName->datum == nullptr) return "";\
		return *static_cast<witsml14__obj_USCOREtrajectory*>(gsoapProxyTraj1_4)->__obj_USCOREtrajectory_sequence->witsmlVectorName[index]->witsmlAttributeName->datum;\
	}

  /**
  * A macro that defines getter and setter measure optional attribute Implementation
  *
  * @param 	className	 	Name of the class.
  * @param 	attributeName	Name of the attribute.
  * @param 	uomDatatype  	The uom datatype.
  * @param 	constructor  	The constructor.
  */
#define GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IMPL_1_4(className, fesapiAttributeName, witsmlAttributeName, uomDatatype, uomDatatype14, constructor, eml2_1ToStr, strToEml2_1, witsml1_4ToStr, strToWitsml1_4)\
	GETTER_AND_SETTER_MEASURE_ATTRIBUTE_IMPL_1_4(className, fesapiAttributeName, witsmlAttributeName, uomDatatype, uomDatatype14, constructor, eml2_1ToStr, strToEml2_1, witsml1_4ToStr, strToWitsml1_4)\
	GETTER_PRESENCE_ATTRIBUTE_IMPL_1_4(className, fesapiAttributeName, witsmlAttributeName)

  /**
   * A macro that defines getter and setter measure optional attribute in vector Implementation
   *
   * @param 	className	 	Name of the class.
   * @param 	vectorName   	Name of the vector.
   * @param 	attributeName	Name of the attribute.
   * @param 	uomDatatype  	The uom datatype.
   * @param 	constructor  	The constructor.
   */
#define GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IN_VECTOR_IMPL_1_4(className, fesapiVectorName, witsmlVectorName, fesapiAttributeName, witsmlAttributeName, uomDatatype, uomDatatype14, constructor, eml2_1ToStr, strToEml2_1, witsml1_4ToStr, strToWitsml1_4)\
	GETTER_AND_SETTER_MEASURE_ATTRIBUTE_IN_VECTOR_IMPL_1_4(className, fesapiVectorName, witsmlVectorName, fesapiAttributeName, witsmlAttributeName, uomDatatype, uomDatatype14, constructor, eml2_1ToStr, strToEml2_1, witsml1_4ToStr, strToWitsml1_4)\
	GETTER_PRESENCE_ATTRIBUTE_IN_VECTOR_IMPL_1_4(className, fesapiVectorName, witsmlVectorName, fesapiAttributeName, witsmlAttributeName)

 /**
  * A macro that defines getter and setter depth measure optional attribute Implementation
  *
  * @param 	className	 	Name of the class.
  * @param 	attributeName	Name of the attribute.
  * @param 	uomDatatype  	The uom datatype.
  * @param 	constructor  	The constructor.
  */
#define GETTER_AND_SETTER_DEPTH_MEASURE_OPTIONAL_ATTRIBUTE_IMPL_1_4(className, fesapiAttributeName, witsmlAttributeName, uomDatatype, constructor)\
	GETTER_AND_SETTER_DEPTH_MEASURE_ATTRIBUTE_IMPL_1_4(className, fesapiAttributeName, witsmlAttributeName, uomDatatype, constructor)\
	GETTER_PRESENCE_ATTRIBUTE_IMPL_1_4(className, fesapiAttributeName, witsmlAttributeName)

  /**
   * A macro that defines getter and setter depth measure optional attribute in vector
   * Implementation
   *
   * @param 	className	 	Name of the class.
   * @param 	vectorName   	Name of the vector.
   * @param 	attributeName	Name of the attribute.
   * @param 	uomDatatype  	The uom datatype.
   * @param 	constructor  	The constructor.
   */
#define GETTER_AND_SETTER_DEPTH_MEASURE_OPTIONAL_ATTRIBUTE_IN_VECTOR_IMPL_1_4(className, fesapiVectorName, witsmlVectorName, fesapiAttributeName, witsmlAttributeName, uomDatatype, constructor)\
	GETTER_AND_SETTER_DEPTH_MEASURE_ATTRIBUTE_IN_VECTOR_IMPL_1_4(className, fesapiVectorName, witsmlVectorName, fesapiAttributeName, witsmlAttributeName, uomDatatype, constructor)\
	GETTER_PRESENCE_ATTRIBUTE_IN_VECTOR_IMPL_1_4(className, fesapiVectorName, witsmlVectorName, fesapiAttributeName, witsmlAttributeName)
