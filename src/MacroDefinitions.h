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
  * A macro that defines getter setter of a mandatory attribute
  *
  * @param 	gsoapClassName   	Name of the gsoap class.
  * @param 	proxyVariable	 	The proxy variable.
  * @param 	attributeName	 	Name of the attribute.
  * @param 	attributeDatatype	The attribute datatype.
  */
#define GETTER_SETTER_ATTRIBUTE(gsoapClassName, proxyVariable, attributeName, attributeDatatype)\
	DLL_IMPORT_OR_EXPORT void set##attributeName(const attributeDatatype& value) {\
		if (isPartial()) { throw std::logic_error("Cannot set an attribute of a partial dataobject."); }\
		static_cast<gsoapClassName*>(proxyVariable)->attributeName = value;\
	}\
	DLL_IMPORT_OR_EXPORT attributeDatatype get##attributeName() const {\
		if (isPartial()) { throw std::logic_error("Cannot get an attribute of a partial dataobject."); }\
		return static_cast<gsoapClassName*>(proxyVariable)->attributeName;\
	}

/**
 * A macro that defines checker presence attribute
 *
 * @param 	gsoapClassName	Name of the gsoap class.
 * @param 	proxyVariable 	The proxy variable.
 * @param 	attributeName 	Name of the attribute.
 */
#define CHECKER_PRESENCE_ATTRIBUTE(gsoapClassName, proxyVariable, attributeName)\
	DLL_IMPORT_OR_EXPORT bool has##attributeName() const {\
		return static_cast<gsoapClassName*>(proxyVariable)->attributeName != nullptr;\
	}

/**
 * A macro that defines checker presence attribute in vector
 *
 * @param 	gsoapClassName	Name of the gsoap class.
 * @param 	proxyVariable 	The proxy variable.
 * @param 	vectorName	  	Name of the vector.
 * @param 	attributeName 	Name of the attribute.
 */
#define CHECKER_PRESENCE_ATTRIBUTE_IN_VECTOR(gsoapClassName, proxyVariable, vectorName, attributeName)\
	DLL_IMPORT_OR_EXPORT bool has##vectorName##attributeName(uint64_t index) const {\
	return static_cast<gsoapClassName*>(proxyVariable)->vectorName.at(index)->attributeName != nullptr;\
}

/**
 * A macro that defines getter setter of an optional attribute
 *
 * @param 	gsoapClassName   	Name of the gsoap class.
 * @param 	proxyVariable	 	The proxy variable.
 * @param 	attributeName	 	Name of the attribute.
 * @param 	attributeDatatype	The attribute datatype.
 */
#define GETTER_SETTER_OPTIONAL_ATTRIBUTE(gsoapClassName, proxyVariable, attributeName, attributeDatatype)\
	DLL_IMPORT_OR_EXPORT void set##attributeName(const attributeDatatype& value);\
	DLL_IMPORT_OR_EXPORT attributeDatatype get##attributeName() const {\
		if (isPartial()) { throw std::logic_error("Cannot get an attribute of a partial dataobject."); }\
		if (!has##attributeName()) { throw std::invalid_argument("The attribute does not exist"); }\
		return *static_cast<gsoapClassName*>(proxyVariable)->attributeName;\
	}\
	CHECKER_PRESENCE_ATTRIBUTE(gsoapClassName, proxyVariable, attributeName)

/**
 * A macro that defines getter setter measure optional attribute
 *
 * @param 	gsoapClassName	Name of the gsoap class.
 * @param 	proxyVariable 	The proxy variable.
 * @param 	attributeName 	Name of the attribute.
 * @param 	uomDatatype   	The uom datatype.
 */
#define GETTER_SETTER_MEASURE_OPTIONAL_ATTRIBUTE(gsoapClassName, proxyVariable, attributeName, uomDatatype)\
	DLL_IMPORT_OR_EXPORT void set##attributeName(double value, uomDatatype uom);\
	DLL_IMPORT_OR_EXPORT double get##attributeName##Value() const {\
		if (!has##attributeName()) { throw std::invalid_argument("The attribute does not exist"); }\
		return static_cast<gsoapClassName*>(proxyVariable)->attributeName->__item;\
	}\
	DLL_IMPORT_OR_EXPORT uomDatatype get##attributeName##Uom() const {\
		if (!has##attributeName()) { throw std::invalid_argument("The attribute does not exist"); }\
		return static_cast<gsoapClassName*>(proxyVariable)->attributeName->uom;\
	}\
	CHECKER_PRESENCE_ATTRIBUTE(gsoapClassName, proxyVariable, attributeName)

/**
 * A macro that defines getter setter optional attribute in vector
 *
 * @param 	gsoapClassName   	Name of the gsoap class.
 * @param 	proxyVariable	 	The proxy variable.
 * @param 	vectorName		 	Name of the vector.
 * @param 	attributeName	 	Name of the attribute.
 * @param 	attributeDatatype	The attribute datatype.
 */
#define GETTER_SETTER_OPTIONAL_ATTRIBUTE_IN_VECTOR(gsoapClassName, proxyVariable, vectorName, attributeName, attributeDatatype)\
	DLL_IMPORT_OR_EXPORT void set##vectorName##attributeName(uint64_t index, const attributeDatatype& value);\
	DLL_IMPORT_OR_EXPORT attributeDatatype get##vectorName##attributeName(uint64_t index) const {\
		if (!has##vectorName##attributeName(index)) { throw std::invalid_argument("The attribute does not exist"); }\
		return *static_cast<gsoapClassName*>(proxyVariable)->vectorName[index]->attributeName;\
	}\
	CHECKER_PRESENCE_ATTRIBUTE_IN_VECTOR(gsoapClassName, proxyVariable, vectorName, attributeName)

/**
 * A macro that defines getter setter measure optional attribute in vector
 *
 * @param 	gsoapClassName	Name of the gsoap class.
 * @param 	proxyVariable 	The proxy variable.
 * @param 	vectorName	  	Name of the vector.
 * @param 	attributeName 	Name of the attribute.
 * @param 	uomDatatype   	The uom datatype.
 */
#define GETTER_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IN_VECTOR(gsoapClassName, proxyVariable, vectorName, attributeName, uomDatatype)\
	DLL_IMPORT_OR_EXPORT void set##vectorName##attributeName(uint64_t index, double value, uomDatatype uom);\
	DLL_IMPORT_OR_EXPORT double get##vectorName##attributeName##Value(uint64_t index) const {\
		if (!has##vectorName##attributeName(index)) { throw std::invalid_argument("The attribute does not exist"); }\
		return static_cast<gsoapClassName*>(proxyVariable)->vectorName[index]->attributeName->__item;\
	}\
	DLL_IMPORT_OR_EXPORT uomDatatype get##vectorName##attributeName##Uom(uint64_t index) const {\
		if (!has##vectorName##attributeName(index)) { throw std::invalid_argument("The attribute does not exist"); }\
		return static_cast<gsoapClassName*>(proxyVariable)->vectorName[index]->attributeName->uom;\
	}\
	CHECKER_PRESENCE_ATTRIBUTE_IN_VECTOR(gsoapClassName, proxyVariable, vectorName, attributeName)

/**
 * A macro that defines setter optional attribute Implementation
 *
 * @param 	className	  		Name of the class.
 * @param 	gsoapClassName		Name of the gsoap class.
 * @param 	proxyVariable 		The proxy variable.
 * @param 	attributeName 		Name of the attribute.
 * @param 	attributeDatatype	The attribute datatype.
 * @param 	constructor   		The constructor.
 */
#define SETTER_OPTIONAL_ATTRIBUTE_IMPL(className, gsoapClassName, proxyVariable, attributeName, attributeDatatype, constructor)\
void className::set##attributeName(const attributeDatatype& value)\
{\
	if (isPartial()) { throw std::logic_error("Cannot set an attribute of a partial dataobject."); }\
	static_cast<gsoapClassName*>(proxyVariable)->attributeName = constructor(proxyVariable->soap);\
	*static_cast<gsoapClassName*>(proxyVariable)->attributeName = value;\
}

/**
 * A macro that defines setter measure attribute Implementation
 *
 * @param 	className	  	Name of the class.
 * @param 	gsoapClassName	Name of the gsoap class.
 * @param 	proxyVariable 	The proxy variable.
 * @param 	attributeName 	Name of the attribute.
 * @param 	uomDatatype   	The uom datatype.
 * @param 	constructor   	The constructor.
 */
#define SETTER_MEASURE_ATTRIBUTE_IMPL(className, gsoapClassName, proxyVariable, attributeName, uomDatatype, constructor)\
void className::set##attributeName(double value, uomDatatype uom)\
{\
	static_cast<gsoapClassName*>(proxyVariable)->attributeName = constructor(proxyVariable->soap);\
	static_cast<gsoapClassName*>(proxyVariable)->attributeName->__item = value;\
	static_cast<gsoapClassName*>(proxyVariable)->attributeName->uom = uom;\
}

/**
 * A macro that defines setter optional attribute in vector Implementation
 *
 * @param 	className		 	Name of the class.
 * @param 	gsoapClassName   	Name of the gsoap class.
 * @param 	proxyVariable	 	The proxy variable.
 * @param 	vectorName		 	Name of the vector.
 * @param 	attributeName	 	Name of the attribute.
 * @param 	attributeDatatype	The attribute datatype.
 * @param 	constructor		 	The constructor.
 */
#define SETTER_OPTIONAL_ATTRIBUTE_IN_VECTOR_IMPL(className, gsoapClassName, proxyVariable, vectorName, attributeName, attributeDatatype, constructor)\
void className::set##vectorName##attributeName(uint64_t index, const attributeDatatype& value)\
{\
	static_cast<gsoapClassName*>(proxyVariable)->vectorName.at(index)->attributeName = constructor(proxyVariable->soap);\
	*static_cast<gsoapClassName*>(proxyVariable)->vectorName[index]->attributeName = value;\
}

/**
 * A macro that defines setter measure attribute in vector Implementation
 *
 * @param 	className	  	Name of the class.
 * @param 	gsoapClassName	Name of the gsoap class.
 * @param 	proxyVariable 	The proxy variable.
 * @param 	vectorName	  	Name of the vector.
 * @param 	attributeName 	Name of the attribute.
 * @param 	uomDatatype   	The uom datatype.
 * @param 	constructor   	The constructor.
 */
#define SETTER_MEASURE_ATTRIBUTE_IN_VECTOR_IMPL(className, gsoapClassName, proxyVariable, vectorName, attributeName, uomDatatype, constructor)\
void className::set##vectorName##attributeName(uint64_t index, double value, uomDatatype uom)\
{\
	static_cast<gsoapClassName*>(proxyVariable)->vectorName.at(index)->attributeName = constructor(proxyVariable->soap);\
	static_cast<gsoapClassName*>(proxyVariable)->vectorName[index]->attributeName->__item = value;\
	static_cast<gsoapClassName*>(proxyVariable)->vectorName[index]->attributeName->uom = uom;\
}

/**
 * *****************
 *  Previous macros
 * *****************
 *
 * @param 	a	A void to process.
 * @param 	b	A void to process.
 */
#define GLUE(a,b) a##b

/**
 * A macro that defines check attribute existence
 *
 * @param 	className	 	Name of the class.
 * @param 	attributeName	Name of the attribute.
 */
#define CHECK_ATTRIBUTE_EXISTENCE(className, attributeName) if (static_cast<witsml21__##className*>(gsoapProxy2_3)->attributeName == nullptr) { throw std::invalid_argument("The attribute does not exist"); }

/**
 * A macro that defines check attribute in vector existence
 *
 * @param 	className	 	Name of the class.
 * @param 	vectorName   	Name of the vector.
 * @param 	attributeName	Name of the attribute.
 */
#define CHECK_ATTRIBUTE_IN_VECTOR_EXISTENCE(className, vectorName, attributeName) \
	if (static_cast<witsml21__##className*>(gsoapProxy2_3)->vectorName.at(index)->attributeName == nullptr) { throw std::invalid_argument("The attribute in vector does not exist"); }

/**
 * A macro that defines create attribute if not present
 *
 * @param 	className	 	Name of the class.
 * @param 	attributeName	Name of the attribute.
 * @param 	constructor  	The constructor.
 */
#define CREATE_ATTRIBUTE_IF_NOT_PRESENT(className, attributeName, constructor) if (static_cast<witsml21__##className*>(gsoapProxy2_3)->attributeName == nullptr) { static_cast<witsml21__##className*>(gsoapProxy2_3)->attributeName = constructor(gsoapProxy2_3->soap); }

/**
 * A macro that defines create attribute in vector if not present
 *
 * @param 	className	 	Name of the class.
 * @param 	vectorName   	Name of the vector.
 * @param 	attributeName	Name of the attribute.
 * @param 	constructor  	The constructor.
 */
#define CREATE_ATTRIBUTE_IN_VECTOR_IF_NOT_PRESENT(className, vectorName, attributeName, constructor)\
	if (static_cast<witsml21__##className*>(gsoapProxy2_3)->vectorName.at(index)->attributeName == nullptr) { static_cast<witsml21__##className*>(gsoapProxy2_3)->vectorName[index]->attributeName = constructor(gsoapProxy2_3->soap); }

/**
* A macro that defines getter presence attribute
*
* @param 	attributeName	Name of the attribute.
*/
#define ABSTRACT_GETTER_PRESENCE_ATTRIBUTE(attributeName) DLL_IMPORT_OR_EXPORT virtual bool has##attributeName() const = 0;

/**
* A macro that defines getter presence attribute
*
* @param 	attributeName	Name of the attribute.
*/
#define FINAL_GETTER_PRESENCE_ATTRIBUTE(attributeName) DLL_IMPORT_OR_EXPORT bool has##attributeName() const final;

/**
 * A macro that defines getter presence attribute
 *
 * @param 	attributeName	Name of the attribute.
 */
#define GETTER_PRESENCE_ATTRIBUTE(attributeName) DLL_IMPORT_OR_EXPORT bool has##attributeName() const;

/**
 * A macro that defines getter presence attribute Implementation
 *
 * @param 	className	 	Name of the class.
 * @param 	attributeName	Name of the attribute.
 */
#define GETTER_PRESENCE_ATTRIBUTE_IMPL(className, attributeName) bool GLUE(,className)::has##attributeName() const { return static_cast<witsml21__##className*>(gsoapProxy2_3)->attributeName != nullptr; }

/**
* A macro that defines getter presence attribute in vector
*
* @param 	vectorName   	Name of the vector.
* @param 	attributeName	Name of the attribute.
*/
#define ABSTRACT_GETTER_PRESENCE_ATTRIBUTE_IN_VECTOR(vectorName, attributeName) DLL_IMPORT_OR_EXPORT virtual bool has##vectorName##attributeName(uint64_t index) const = 0;

/**
* A macro that defines getter presence attribute in vector
*
* @param 	vectorName   	Name of the vector.
* @param 	attributeName	Name of the attribute.
*/
#define FINAL_GETTER_PRESENCE_ATTRIBUTE_IN_VECTOR(vectorName, attributeName) DLL_IMPORT_OR_EXPORT bool has##vectorName##attributeName(uint64_t index) const final;

/**
 * A macro that defines getter presence attribute in vector
 *
 * @param 	vectorName   	Name of the vector.
 * @param 	attributeName	Name of the attribute.
 */
#define GETTER_PRESENCE_ATTRIBUTE_IN_VECTOR(vectorName, attributeName) DLL_IMPORT_OR_EXPORT bool has##vectorName##attributeName(uint64_t index) const;

/**
 * A macro that defines getter presence attribute in vector Implementation
 *
 * @param 	className	 	Name of the class.
 * @param 	vectorName   	Name of the vector.
 * @param 	attributeName	Name of the attribute.
 */
#define GETTER_PRESENCE_ATTRIBUTE_IN_VECTOR_IMPL(className, vectorName, attributeName) bool GLUE(,className)::has##vectorName##attributeName(uint64_t index) const {\
	return static_cast<witsml21__##className*>(gsoapProxy2_3)->vectorName.at(index)->attributeName != nullptr;\
}

 /**
  * A macro that defines getter and setter generic attribute
  *
  * @param 	attributeDatatype	The attribute datatype.
  * @param 	attributeName	 	Name of the attribute.
  */
#define ABSTRACT_GETTER_AND_SETTER_GENERIC_ATTRIBUTE(attributeDatatype, attributeName)\
	DLL_IMPORT_OR_EXPORT virtual void set##attributeName(const attributeDatatype & value) = 0;\
	DLL_IMPORT_OR_EXPORT virtual attributeDatatype get##attributeName() const = 0;

/**
* A macro that defines getter and setter generic attribute
*
* @param 	attributeDatatype	The attribute datatype.
* @param 	attributeName	 	Name of the attribute.
*/
#define FINAL_GETTER_AND_SETTER_GENERIC_ATTRIBUTE(attributeDatatype, attributeName)\
	DLL_IMPORT_OR_EXPORT void set##attributeName(const attributeDatatype & value) final;\
	DLL_IMPORT_OR_EXPORT attributeDatatype get##attributeName() const final;

/**
 * A macro that defines getter and setter generic attribute
 *
 * @param 	attributeDatatype	The attribute datatype.
 * @param 	attributeName	 	Name of the attribute.
 */
#define GETTER_AND_SETTER_GENERIC_ATTRIBUTE(attributeDatatype, attributeName)\
	DLL_IMPORT_OR_EXPORT void set##attributeName(const attributeDatatype & value);\
	DLL_IMPORT_OR_EXPORT attributeDatatype get##attributeName() const;

/**
 * A macro that defines getter and setter generic attribute Implementation
 *
 * @param 	attributeDatatype	The attribute datatype.
 * @param 	className		 	Name of the class.
 * @param 	attributeName	 	Name of the attribute.
 */
#define GETTER_AND_SETTER_GENERIC_ATTRIBUTE_IMPL(attributeDatatype, className, attributeName)\
	void GLUE(,className)::set##attributeName(const attributeDatatype & value) { static_cast<witsml21__##className*>(gsoapProxy2_3)->attributeName = value; }\
	attributeDatatype GLUE(,className)::get##attributeName() const { return static_cast<witsml21__##className*>(gsoapProxy2_3)->attributeName; }

 /**
  * A macro that defines getter and setter generic attribute in vector
  *
  * @param 	attributeDatatype	The attribute datatype.
  * @param 	vectorName		 	Name of the vector.
  * @param 	attributeName	 	Name of the attribute.
  */
#define ABSTRACT_GETTER_AND_SETTER_GENERIC_ATTRIBUTE_IN_VECTOR(attributeDatatype, vectorName, attributeName)\
	DLL_IMPORT_OR_EXPORT virtual void set##vectorName##attributeName(uint64_t index, const attributeDatatype & value) = 0;\
	DLL_IMPORT_OR_EXPORT virtual attributeDatatype get##vectorName##attributeName(uint64_t index) const = 0;

/**
* A macro that defines getter and setter generic attribute in vector
*
* @param 	attributeDatatype	The attribute datatype.
* @param 	vectorName		 	Name of the vector.
* @param 	attributeName	 	Name of the attribute.
*/
#define FINAL_GETTER_AND_SETTER_GENERIC_ATTRIBUTE_IN_VECTOR(attributeDatatype, vectorName, attributeName)\
	DLL_IMPORT_OR_EXPORT void set##vectorName##attributeName(uint64_t index, const attributeDatatype & value) final;\
	DLL_IMPORT_OR_EXPORT attributeDatatype get##vectorName##attributeName(uint64_t index) const final;

/**
 * A macro that defines getter and setter generic attribute in vector
 *
 * @param 	attributeDatatype	The attribute datatype.
 * @param 	vectorName		 	Name of the vector.
 * @param 	attributeName	 	Name of the attribute.
 */
#define GETTER_AND_SETTER_GENERIC_ATTRIBUTE_IN_VECTOR(attributeDatatype, vectorName, attributeName)\
	DLL_IMPORT_OR_EXPORT void set##vectorName##attributeName(uint64_t index, const attributeDatatype & value);\
	DLL_IMPORT_OR_EXPORT attributeDatatype get##vectorName##attributeName(uint64_t index) const;

/**
 * A macro that defines getter and setter generic attribute in vector Implementation
 *
 * @param 	attributeDatatype	The attribute datatype.
 * @param 	className		 	Name of the class.
 * @param 	vectorName		 	Name of the vector.
 * @param 	attributeName	 	Name of the attribute.
 */
#define GETTER_AND_SETTER_GENERIC_ATTRIBUTE_IN_VECTOR_IMPL(attributeDatatype, className, vectorName, attributeName)\
	void GLUE(,className)::set##vectorName##attributeName(uint64_t index, const attributeDatatype & value) {\
		static_cast<witsml21__##className*>(gsoapProxy2_3)->vectorName.at(index)->attributeName = value;\
	}\
	attributeDatatype GLUE(,className)::get##vectorName##attributeName(uint64_t index) const {\
		return static_cast<witsml21__##className*>(gsoapProxy2_3)->vectorName.at(index)->attributeName;\
	}

/**
* A macro that defines getter and setter generic optional attribute
*
* @param 	attributeDatatype	The attribute datatype.
* @param 	attributeName	 	Name of the attribute.
*/
#define ABSTRACT_GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE(attributeDatatype, attributeName)\
	ABSTRACT_GETTER_AND_SETTER_GENERIC_ATTRIBUTE(attributeDatatype, attributeName)\
	ABSTRACT_GETTER_PRESENCE_ATTRIBUTE(attributeName)

/**
* A macro that defines getter and setter generic optional attribute
*
* @param 	attributeDatatype	The attribute datatype.
* @param 	attributeName	 	Name of the attribute.
*/
#define FINAL_GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE(attributeDatatype, attributeName)\
	FINAL_GETTER_AND_SETTER_GENERIC_ATTRIBUTE(attributeDatatype, attributeName)\
	FINAL_GETTER_PRESENCE_ATTRIBUTE(attributeName)

/**
 * A macro that defines getter and setter generic optional attribute
 *
 * @param 	attributeDatatype	The attribute datatype.
 * @param 	attributeName	 	Name of the attribute.
 */
#define GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE(attributeDatatype, attributeName)\
	GETTER_AND_SETTER_GENERIC_ATTRIBUTE(attributeDatatype, attributeName)\
	GETTER_PRESENCE_ATTRIBUTE(attributeName)

/**
 * A macro that defines getter and setter generic optional attribute Implementation
 *
 * @param 	attributeDatatype	The attribute datatype.
 * @param 	className		 	Name of the class.
 * @param 	attributeName	 	Name of the attribute.
 * @param 	constructor		 	The constructor.
 */
#define GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IMPL(attributeDatatype, className, attributeName, constructor)\
	void GLUE(,className)::set##attributeName(const attributeDatatype & attributeName) {\
		CREATE_ATTRIBUTE_IF_NOT_PRESENT(className, attributeName, constructor)\
		*static_cast<witsml21__##className*>(gsoapProxy2_3)->attributeName = attributeName;\
	}\
	GETTER_PRESENCE_ATTRIBUTE_IMPL(className, attributeName)\
	attributeDatatype GLUE(,className)::get##attributeName() const {\
		CHECK_ATTRIBUTE_EXISTENCE(className, attributeName)\
		return *static_cast<witsml21__##className*>(gsoapProxy2_3)->attributeName;\
	}

/**
* A macro that defines getter and setter generic optional attribute in vector
*
* @param 	attributeDatatype	The attribute datatype.
* @param 	vectorName		 	Name of the vector.
* @param 	attributeName	 	Name of the attribute.
*/
#define ABSTRACT_GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IN_VECTOR(attributeDatatype, vectorName, attributeName)\
	ABSTRACT_GETTER_AND_SETTER_GENERIC_ATTRIBUTE_IN_VECTOR(attributeDatatype, vectorName, attributeName)\
	ABSTRACT_GETTER_PRESENCE_ATTRIBUTE_IN_VECTOR(vectorName, attributeName)

/**
* A macro that defines getter and setter generic optional attribute in vector
*
* @param 	attributeDatatype	The attribute datatype.
* @param 	vectorName		 	Name of the vector.
* @param 	attributeName	 	Name of the attribute.
*/
#define FINAL_GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IN_VECTOR(attributeDatatype, vectorName, attributeName)\
	FINAL_GETTER_AND_SETTER_GENERIC_ATTRIBUTE_IN_VECTOR(attributeDatatype, vectorName, attributeName)\
	FINAL_GETTER_PRESENCE_ATTRIBUTE_IN_VECTOR(vectorName, attributeName)
/**
 * A macro that defines getter and setter generic optional attribute in vector
 *
 * @param 	attributeDatatype	The attribute datatype.
 * @param 	vectorName		 	Name of the vector.
 * @param 	attributeName	 	Name of the attribute.
 */
#define GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IN_VECTOR(attributeDatatype, vectorName, attributeName)\
	GETTER_AND_SETTER_GENERIC_ATTRIBUTE_IN_VECTOR(attributeDatatype, vectorName, attributeName)\
	GETTER_PRESENCE_ATTRIBUTE_IN_VECTOR(vectorName, attributeName)

/**
 * A macro that defines getter and setter generic optional attribute in vector Implementation
 *
 * @param 	attributeDatatype	The attribute datatype.
 * @param 	className		 	Name of the class.
 * @param 	vectorName		 	Name of the vector.
 * @param 	attributeName	 	Name of the attribute.
 * @param 	constructor		 	The constructor.
 */
#define GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE_IN_VECTOR_IMPL(attributeDatatype, className, vectorName, attributeName, constructor)\
	void GLUE(,className)::set##vectorName##attributeName(uint64_t index, const attributeDatatype & value) {\
		CREATE_ATTRIBUTE_IN_VECTOR_IF_NOT_PRESENT(className, vectorName, attributeName, constructor)\
		*static_cast<witsml21__##className*>(gsoapProxy2_3)->vectorName[index]->attributeName = value;\
	}\
	GETTER_PRESENCE_ATTRIBUTE_IN_VECTOR_IMPL(className, vectorName, attributeName)\
	attributeDatatype GLUE(,className)::get##vectorName##attributeName(uint64_t index) const {\
		CHECK_ATTRIBUTE_IN_VECTOR_EXISTENCE(className, vectorName, attributeName)\
		return *static_cast<witsml21__##className*>(gsoapProxy2_3)->vectorName[index]->attributeName;\
	}

/**
 * A macro that defines getter and setter time t optional attribute Implementation
 *
 * @param 	className	 	Name of the class.
 * @param 	attributeName	Name of the attribute.
 */
#define GETTER_AND_SETTER_TIME_T_OPTIONAL_ATTRIBUTE_IMPL(className, attributeName)\
	void GLUE(,className)::set##attributeName(const time_t & attributeName) {\
		CREATE_ATTRIBUTE_IF_NOT_PRESENT(className, attributeName, gsoap_eml2_3::soap_new_tm)\
		*static_cast<witsml21__##className*>(gsoapProxy2_3)->attributeName = timeTools::to_calendar_time(timeTools::from_time_t(attributeName));\
	}\
	GETTER_PRESENCE_ATTRIBUTE_IMPL(className, attributeName)\
	time_t GLUE(,className)::get##attributeName() const {\
		CHECK_ATTRIBUTE_EXISTENCE(className, attributeName)\
		return timeTools::timegm(*static_cast<witsml21__##className*>(gsoapProxy2_3)->attributeName);\
	}

 /**
  * A macro that defines getter and setter time t optional attribute in vector Implementation
  *
  * @param 	className	 	Name of the class.
  * @param 	vectorName   	Name of the vector.
  * @param 	attributeName	Name of the attribute.
  */
#define GETTER_AND_SETTER_TIME_T_ATTRIBUTE_IN_VECTOR_IMPL(className, vectorName, attributeName)\
	void GLUE(,className)::set##vectorName##attributeName(uint64_t index, const time_t & attributeName) {\
		static_cast<witsml21__##className*>(gsoapProxy2_3)->vectorName.at(index)->attributeName = timeTools::to_calendar_time(timeTools::from_time_t(attributeName));\
	}\
	time_t GLUE(,className)::get##vectorName##attributeName(uint64_t index) const {\
		return timeTools::timegm(static_cast<witsml21__##className*>(gsoapProxy2_3)->vectorName.at(index)->attributeName);\
	}

/**
 * A macro that defines getter and setter time t optional attribute in vector Implementation
 *
 * @param 	className	 	Name of the class.
 * @param 	vectorName   	Name of the vector.
 * @param 	attributeName	Name of the attribute.
 */
#define GETTER_AND_SETTER_TIME_T_OPTIONAL_ATTRIBUTE_IN_VECTOR_IMPL(className, vectorName, attributeName)\
	void GLUE(,className)::set##vectorName##attributeName(uint64_t index, const time_t & attributeName) {\
		*static_cast<witsml21__##className*>(gsoapProxy2_3)->vectorName.at(index)->attributeName = timeTools::to_calendar_time(timeTools::from_time_t(attributeName));\
	}\
	time_t GLUE(,className)::get##vectorName##attributeName(uint64_t index) const {\
		return timeTools::timegm(*static_cast<witsml21__##className*>(gsoapProxy2_3)->vectorName.at(index)->attributeName);\
	}\
	GETTER_PRESENCE_ATTRIBUTE_IN_VECTOR_IMPL(className, vectorName, attributeName)

/**
* A macro that defines getter and setter measure attribute
*
* @param 	attributeName	Name of the attribute.
* @param 	uomDatatype  	The uom datatype.
*/
#define ABSTRACT_GETTER_AND_SETTER_MEASURE_ATTRIBUTE(attributeName, uomDatatype)\
	DLL_IMPORT_OR_EXPORT virtual void set##attributeName(double value, uomDatatype uom) = 0;\
	DLL_IMPORT_OR_EXPORT virtual double get##attributeName##Value() const = 0;\
	DLL_IMPORT_OR_EXPORT virtual uomDatatype get##attributeName##Uom() const = 0;\
	DLL_IMPORT_OR_EXPORT virtual std::string get##attributeName##UomAsString() const = 0;

/**
* A macro that defines getter and setter measure attribute
*
* @param 	attributeName	Name of the attribute.
* @param 	uomDatatype  	The uom datatype.
*/
#define FINAL_GETTER_AND_SETTER_MEASURE_ATTRIBUTE(attributeName, uomDatatype)\
	DLL_IMPORT_OR_EXPORT void set##attributeName(double value, uomDatatype uom) final;\
	DLL_IMPORT_OR_EXPORT double get##attributeName##Value() const final;\
	DLL_IMPORT_OR_EXPORT uomDatatype get##attributeName##Uom() const final;\
	DLL_IMPORT_OR_EXPORT std::string get##attributeName##UomAsString() const final;

/**
 * A macro that defines getter and setter measure attribute
 *
 * @param 	attributeName	Name of the attribute.
 * @param 	uomDatatype  	The uom datatype.
 */
#define GETTER_AND_SETTER_MEASURE_ATTRIBUTE(attributeName, uomDatatype)\
	DLL_IMPORT_OR_EXPORT void set##attributeName(double value, uomDatatype uom);\
	DLL_IMPORT_OR_EXPORT double get##attributeName##Value() const;\
	DLL_IMPORT_OR_EXPORT uomDatatype get##attributeName##Uom() const;\
	DLL_IMPORT_OR_EXPORT std::string get##attributeName##UomAsString() const;

/**
* A macro that defines getter and setter measure optional attribute
*
* @param 	attributeName	Name of the attribute.
* @param 	uomDatatype  	The uom datatype.
*/
#define ABSTRACT_GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE(attributeName, uomDatatype)\
	ABSTRACT_GETTER_AND_SETTER_MEASURE_ATTRIBUTE(attributeName, uomDatatype)\
	ABSTRACT_GETTER_PRESENCE_ATTRIBUTE(attributeName)

/**
* A macro that defines getter and setter measure optional attribute
*
* @param 	attributeName	Name of the attribute.
* @param 	uomDatatype  	The uom datatype.
*/
#define FINAL_GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE(attributeName, uomDatatype)\
	FINAL_GETTER_AND_SETTER_MEASURE_ATTRIBUTE(attributeName, uomDatatype)\
	FINAL_GETTER_PRESENCE_ATTRIBUTE(attributeName)

/**
 * A macro that defines getter and setter measure optional attribute
 *
 * @param 	attributeName	Name of the attribute.
 * @param 	uomDatatype  	The uom datatype.
 */
#define GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE(attributeName, uomDatatype)\
	GETTER_AND_SETTER_MEASURE_ATTRIBUTE(attributeName, uomDatatype)\
	GETTER_PRESENCE_ATTRIBUTE(attributeName)

/**
* A macro that defines getter and setter depth measure attribute
*
* @param 	attributeName	Name of the attribute.
* @param 	uomDatatype  	The uom datatype.
*/
#define ABSTRACT_GETTER_AND_SETTER_DEPTH_MEASURE_ATTRIBUTE(attributeName, uomDatatype)\
	DLL_IMPORT_OR_EXPORT virtual void set##attributeName(double value, uomDatatype uom) = 0;\
	DLL_IMPORT_OR_EXPORT virtual double get##attributeName##Value() const = 0;\
	DLL_IMPORT_OR_EXPORT virtual uomDatatype get##attributeName##Uom() const = 0;

/**
* A macro that defines getter and setter depth measure attribute
*
* @param 	attributeName	Name of the attribute.
* @param 	uomDatatype  	The uom datatype.
*/
#define FINAL_GETTER_AND_SETTER_DEPTH_MEASURE_ATTRIBUTE(attributeName, uomDatatype)\
	DLL_IMPORT_OR_EXPORT void set##attributeName(double value, uomDatatype uom) final;\
	DLL_IMPORT_OR_EXPORT double get##attributeName##Value() const final;\
	DLL_IMPORT_OR_EXPORT uomDatatype get##attributeName##Uom() const final;

/**
 * A macro that defines getter and setter depth measure attribute
 *
 * @param 	attributeName	Name of the attribute.
 * @param 	uomDatatype  	The uom datatype.
 */
#define GETTER_AND_SETTER_DEPTH_MEASURE_ATTRIBUTE(attributeName, uomDatatype)\
	DLL_IMPORT_OR_EXPORT void set##attributeName(double value, uomDatatype uom);\
	DLL_IMPORT_OR_EXPORT double get##attributeName##Value() const;\
	DLL_IMPORT_OR_EXPORT uomDatatype get##attributeName##Uom() const;

/**
* A macro that defines getter and setter depth measure optional attribute
*
* @param 	attributeName	Name of the attribute.
* @param 	uomDatatype  	The uom datatype.
*/
#define ABSTRACT_GETTER_AND_SETTER_DEPTH_MEASURE_OPTIONAL_ATTRIBUTE(attributeName, uomDatatype)\
	ABSTRACT_GETTER_AND_SETTER_DEPTH_MEASURE_ATTRIBUTE(attributeName, uomDatatype)\
	ABSTRACT_GETTER_PRESENCE_ATTRIBUTE(attributeName)

/**
* A macro that defines getter and setter depth measure optional attribute
*
* @param 	attributeName	Name of the attribute.
* @param 	uomDatatype  	The uom datatype.
*/
#define FINAL_GETTER_AND_SETTER_DEPTH_MEASURE_OPTIONAL_ATTRIBUTE(attributeName, uomDatatype)\
	FINAL_GETTER_AND_SETTER_DEPTH_MEASURE_ATTRIBUTE(attributeName, uomDatatype)\
	FINAL_GETTER_PRESENCE_ATTRIBUTE(attributeName)

/**
 * A macro that defines getter and setter depth measure optional attribute
 *
 * @param 	attributeName	Name of the attribute.
 * @param 	uomDatatype  	The uom datatype.
 */
#define GETTER_AND_SETTER_DEPTH_MEASURE_OPTIONAL_ATTRIBUTE(attributeName, uomDatatype)\
	GETTER_AND_SETTER_DEPTH_MEASURE_ATTRIBUTE(attributeName, uomDatatype)\
	GETTER_PRESENCE_ATTRIBUTE(attributeName)

/**
* A macro that defines getter and setter measure attribute in vector
*
* @param 	vectorName   	Name of the vector.
* @param 	attributeName	Name of the attribute.
* @param 	uomDatatype  	The uom datatype.
*/
#define ABSTRACT_GETTER_AND_SETTER_MEASURE_ATTRIBUTE_IN_VECTOR(vectorName, attributeName, uomDatatype)\
	DLL_IMPORT_OR_EXPORT virtual void set##vectorName##attributeName(uint64_t index, double value, uomDatatype uom) = 0;\
	DLL_IMPORT_OR_EXPORT virtual double get##vectorName##attributeName##Value(uint64_t index) const = 0;\
	DLL_IMPORT_OR_EXPORT virtual uomDatatype get##vectorName##attributeName##Uom(uint64_t index) const = 0;

/**
* A macro that defines getter and setter measure attribute in vector
*
* @param 	vectorName   	Name of the vector.
* @param 	attributeName	Name of the attribute.
* @param 	uomDatatype  	The uom datatype.
*/
#define FINAL_GETTER_AND_SETTER_MEASURE_ATTRIBUTE_IN_VECTOR(vectorName, attributeName, uomDatatype)\
	DLL_IMPORT_OR_EXPORT void set##vectorName##attributeName(uint64_t index, double value, uomDatatype uom) final;\
	DLL_IMPORT_OR_EXPORT double get##vectorName##attributeName##Value(uint64_t index) const final;\
	DLL_IMPORT_OR_EXPORT uomDatatype get##vectorName##attributeName##Uom(uint64_t index) const final;

/**
 * A macro that defines getter and setter measure attribute in vector
 *
 * @param 	vectorName   	Name of the vector.
 * @param 	attributeName	Name of the attribute.
 * @param 	uomDatatype  	The uom datatype.
 */
#define GETTER_AND_SETTER_MEASURE_ATTRIBUTE_IN_VECTOR(vectorName, attributeName, uomDatatype)\
	DLL_IMPORT_OR_EXPORT void set##vectorName##attributeName(uint64_t index, double value, uomDatatype uom);\
	DLL_IMPORT_OR_EXPORT double get##vectorName##attributeName##Value(uint64_t index) const;\
	DLL_IMPORT_OR_EXPORT uomDatatype get##vectorName##attributeName##Uom(uint64_t index) const;

/**
* A macro that defines getter and setter measure optional attribute in vector
*
* @param 	vectorName   	Name of the vector.
* @param 	attributeName	Name of the attribute.
* @param 	uomDatatype  	The uom datatype.
*/
#define ABSTRACT_GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IN_VECTOR(vectorName, attributeName, uomDatatype)\
    ABSTRACT_GETTER_AND_SETTER_MEASURE_ATTRIBUTE_IN_VECTOR(vectorName, attributeName, uomDatatype)\
	ABSTRACT_GETTER_PRESENCE_ATTRIBUTE_IN_VECTOR(vectorName, attributeName)

/**
* A macro that defines getter and setter measure optional attribute in vector
*
* @param 	vectorName   	Name of the vector.
* @param 	attributeName	Name of the attribute.
* @param 	uomDatatype  	The uom datatype.
*/
#define FINAL_GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IN_VECTOR(vectorName, attributeName, uomDatatype)\
    FINAL_GETTER_AND_SETTER_MEASURE_ATTRIBUTE_IN_VECTOR(vectorName, attributeName, uomDatatype)\
	FINAL_GETTER_PRESENCE_ATTRIBUTE_IN_VECTOR(vectorName, attributeName)

/**
 * A macro that defines getter and setter measure optional attribute in vector
 *
 * @param 	vectorName   	Name of the vector.
 * @param 	attributeName	Name of the attribute.
 * @param 	uomDatatype  	The uom datatype.
 */
#define GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IN_VECTOR(vectorName, attributeName, uomDatatype)\
    GETTER_AND_SETTER_MEASURE_ATTRIBUTE_IN_VECTOR(vectorName, attributeName, uomDatatype)\
	GETTER_PRESENCE_ATTRIBUTE_IN_VECTOR(vectorName, attributeName)

/**
* A macro that defines getter and setter depth measure attribute in vector
*
* @param 	vectorName   	Name of the vector.
* @param 	attributeName	Name of the attribute.
* @param 	uomDatatype  	The uom datatype.
*/
#define ABSTRACT_GETTER_AND_SETTER_DEPTH_MEASURE_ATTRIBUTE_IN_VECTOR(vectorName, attributeName, uomDatatype)\
	DLL_IMPORT_OR_EXPORT virtual void set##vectorName##attributeName(uint64_t index, double value, uomDatatype uom) = 0;\
	DLL_IMPORT_OR_EXPORT virtual double get##vectorName##attributeName##Value(uint64_t index) const = 0;\
	DLL_IMPORT_OR_EXPORT virtual uomDatatype get##vectorName##attributeName##Uom(uint64_t index) const = 0;

/**
* A macro that defines getter and setter depth measure attribute in vector
*
* @param 	vectorName   	Name of the vector.
* @param 	attributeName	Name of the attribute.
* @param 	uomDatatype  	The uom datatype.
*/
#define FINAL_GETTER_AND_SETTER_DEPTH_MEASURE_ATTRIBUTE_IN_VECTOR(vectorName, attributeName, uomDatatype)\
	DLL_IMPORT_OR_EXPORT void set##vectorName##attributeName(uint64_t index, double value, uomDatatype uom) final;\
	DLL_IMPORT_OR_EXPORT double get##vectorName##attributeName##Value(uint64_t index) const final;\
	DLL_IMPORT_OR_EXPORT uomDatatype get##vectorName##attributeName##Uom(uint64_t index) const final;

/**
 * A macro that defines getter and setter depth measure attribute in vector
 *
 * @param 	vectorName   	Name of the vector.
 * @param 	attributeName	Name of the attribute.
 * @param 	uomDatatype  	The uom datatype.
 */
#define GETTER_AND_SETTER_DEPTH_MEASURE_ATTRIBUTE_IN_VECTOR(vectorName, attributeName, uomDatatype)\
	DLL_IMPORT_OR_EXPORT void set##vectorName##attributeName(uint64_t index, double value, uomDatatype uom, const std::string & datum);\
	DLL_IMPORT_OR_EXPORT double get##vectorName##attributeName##Value(uint64_t index) const;\
	DLL_IMPORT_OR_EXPORT uomDatatype get##vectorName##attributeName##Uom(uint64_t index) const;\
	DLL_IMPORT_OR_EXPORT std::string get##vectorName##attributeName##Datum(uint64_t index) const;

/**
* A macro that defines getter and setter depth measure optional attribute in vector
*
* @param 	vectorName   	Name of the vector.
* @param 	attributeName	Name of the attribute.
* @param 	uomDatatype  	The uom datatype.
*/
#define ABSTRACT_GETTER_AND_SETTER_DEPTH_MEASURE_OPTIONAL_ATTRIBUTE_IN_VECTOR(vectorName, attributeName, uomDatatype)\
	ABSTRACT_GETTER_AND_SETTER_DEPTH_MEASURE_ATTRIBUTE_IN_VECTOR(vectorName, attributeName, uomDatatype)\
	ABSTRACT_GETTER_PRESENCE_ATTRIBUTE_IN_VECTOR(vectorName, attributeName)

/**
* A macro that defines getter and setter depth measure optional attribute in vector
*
* @param 	vectorName   	Name of the vector.
* @param 	attributeName	Name of the attribute.
* @param 	uomDatatype  	The uom datatype.
*/
#define FINAL_GETTER_AND_SETTER_DEPTH_MEASURE_OPTIONAL_ATTRIBUTE_IN_VECTOR(vectorName, attributeName, uomDatatype)\
	FINAL_GETTER_AND_SETTER_DEPTH_MEASURE_ATTRIBUTE_IN_VECTOR(vectorName, attributeName, uomDatatype)\
	FINAL_GETTER_PRESENCE_ATTRIBUTE_IN_VECTOR(vectorName, attributeName)

/**
 * A macro that defines getter and setter depth measure optional attribute in vector
 *
 * @param 	vectorName   	Name of the vector.
 * @param 	attributeName	Name of the attribute.
 * @param 	uomDatatype  	The uom datatype.
 */
#define GETTER_AND_SETTER_DEPTH_MEASURE_OPTIONAL_ATTRIBUTE_IN_VECTOR(vectorName, attributeName, uomDatatype)\
	GETTER_AND_SETTER_DEPTH_MEASURE_ATTRIBUTE_IN_VECTOR(vectorName, attributeName, uomDatatype)\
	GETTER_PRESENCE_ATTRIBUTE_IN_VECTOR(vectorName, attributeName)

/**
 * A macro that defines getter value of measure attribute Implementation
 *
 * @param 	className	 	Name of the class.
 * @param 	attributeName	Name of the attribute.
 */
#define GETTER_VALUE_OF_MEASURE_ATTRIBUTE_IMPL(className, attributeName)\
	double GLUE(,className)::get##attributeName##Value() const {\
		if (!has##attributeName()) { throw invalid_argument("The measure attribute to get does not exist."); }\
		return static_cast<witsml21__##className*>(gsoapProxy2_3)->attributeName->__item;\
	}

/**
 * A macro that defines getter uom of measure attribute Implementation
 *
 * @param 	className	 	Name of the class.
 * @param 	attributeName	Name of the attribute.
 * @param 	uomDatatype  	The uom datatype.
 */
#define GETTER_UOM_OF_MEASURE_ATTRIBUTE_IMPL(className, attributeName, uomDatatype)\
	uomDatatype GLUE(, className)::get##attributeName##Uom() const {\
		if (!has##attributeName()) { throw invalid_argument("The measure attribute to get does not exist."); }\
		return static_cast<witsml21__##className*>(gsoapProxy2_3)->attributeName->uom;\
	}

/**
 * A macro that defines getter uom (as string) of measure attribute Implementation
 *
 * @param 	className	 	Name of the class.
 * @param 	attributeName	Name of the attribute.
 * @param 	uomDatatype  	The uom datatype.
 */
#define GETTER_UOM_OF_MEASURE_AS_STRING_ATTRIBUTE_IMPL(className, attributeName, uomDatatypeStringConversion)\
	std::string GLUE(, className)::get##attributeName##UomAsString() const {\
		return uomDatatypeStringConversion(gsoapProxy2_3->soap, get##attributeName##Uom());\
	}

/**
 * A macro that defines getter and setter measure attribute Implementation
 *
 * @param 	className	 	Name of the class.
 * @param 	attributeName	Name of the attribute.
 * @param 	uomDatatype  	The uom datatype.
 * @param 	constructor  	The constructor.
 */
#define GETTER_AND_SETTER_MEASURE_ATTRIBUTE_IMPL(className, attributeName, uomDatatype, uomDatatypeStringConversion, constructor)\
	void GLUE(,className)::set##attributeName(double value, uomDatatype uom) {\
		if (value != value) { throw invalid_argument("You cannot set an undefined measure"); }\
		CREATE_ATTRIBUTE_IF_NOT_PRESENT(className, attributeName, constructor)\
		static_cast<witsml21__##className*>(gsoapProxy2_3)->attributeName->__item = value;\
		static_cast<witsml21__##className*>(gsoapProxy2_3)->attributeName->uom = uom;\
	}\
	GETTER_VALUE_OF_MEASURE_ATTRIBUTE_IMPL(className, attributeName)\
	GETTER_UOM_OF_MEASURE_ATTRIBUTE_IMPL(className, attributeName, uomDatatype)\
	GETTER_UOM_OF_MEASURE_AS_STRING_ATTRIBUTE_IMPL(className, attributeName, uomDatatypeStringConversion)

/**
 * A macro that defines getter and setter depth measure attribute Implementation
 *
 * @param 	className	 	Name of the class.
 * @param 	attributeName	Name of the attribute.
 * @param 	uomDatatype  	The uom datatype.
 * @param 	constructor  	The constructor.
 */
#define GETTER_AND_SETTER_MEASURED_DEPTH_ATTRIBUTE_IMPL(className, attributeName, uomDatatype, constructor)\
	void GLUE(,className)::set##attributeName(double value, uomDatatype uom) {\
		if (value != value) { throw invalid_argument("You cannot set an undefined depth measure"); }\
		CREATE_ATTRIBUTE_IF_NOT_PRESENT(className, attributeName, constructor)\
		if (static_cast<witsml21__##className*>(gsoapProxy2_3)->attributeName->MeasuredDepth == nullptr) {\
			static_cast<witsml21__##className*>(gsoapProxy2_3)->attributeName->MeasuredDepth = gsoap_eml2_3::soap_new_eml23__LengthMeasureExt(gsoapProxy2_3->soap); }\
		static_cast<witsml21__##className*>(gsoapProxy2_3)->attributeName->MeasuredDepth->__item = value;\
		static_cast<witsml21__##className*>(gsoapProxy2_3)->attributeName->MeasuredDepth->uom = gsoap_eml2_3::soap_eml23__LengthUom2s(gsoapProxy2_3->soap, uom);\
	}\
	double GLUE(,className)::get##attributeName##Value() const {\
		if (!has##attributeName()) { throw invalid_argument("The measure attribute to get does not exist."); }\
		return static_cast<witsml21__##className*>(gsoapProxy2_3)->attributeName->MeasuredDepth->__item;\
	}\
	uomDatatype GLUE(, className)::get##attributeName##Uom() const {\
		if (!has##attributeName()) { throw invalid_argument("The measure attribute to get does not exist."); }\
		gsoap_eml2_3::eml23__LengthUom result;\
		gsoap_eml2_3::soap_s2eml23__LengthUom(gsoapProxy2_3->soap, static_cast<witsml21__##className*>(gsoapProxy2_3)->attributeName->MeasuredDepth->uom.c_str(), &result);\
		return result;\
	}

/**
 * A macro that defines getter and setter measure optional attribute Implementation
 *
 * @param 	className	 	Name of the class.
 * @param 	attributeName	Name of the attribute.
 * @param 	uomDatatype  	The uom datatype.
 * @param 	constructor  	The constructor.
 */
#define GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IMPL(className, attributeName, uomDatatype, uomDatatypeStringConversion, constructor)\
	GETTER_AND_SETTER_MEASURE_ATTRIBUTE_IMPL(className, attributeName, uomDatatype, uomDatatypeStringConversion, constructor)\
	GETTER_PRESENCE_ATTRIBUTE_IMPL(className, attributeName)

/**
 * A macro that defines getter and setter depth measure optional attribute Implementation
 *
 * @param 	className	 	Name of the class.
 * @param 	attributeName	Name of the attribute.
 * @param 	uomDatatype  	The uom datatype.
 * @param 	constructor  	The constructor.
 */
#define GETTER_AND_SETTER_MEASURED_DEPTH_OPTIONAL_ATTRIBUTE_IMPL(className, attributeName, uomDatatype, constructor)\
	GETTER_AND_SETTER_MEASURED_DEPTH_ATTRIBUTE_IMPL(className, attributeName, uomDatatype, constructor)\
	GETTER_PRESENCE_ATTRIBUTE_IMPL(className, attributeName)

/**
 * A macro that defines getter value of measure attribute in vector Implementation
 *
 * @param 	className	 	Name of the class.
 * @param 	vectorName   	Name of the vector.
 * @param 	attributeName	Name of the attribute.
 */
#define GETTER_VALUE_OF_MEASURE_ATTRIBUTE_IN_VECTOR_IMPL(className, vectorName, attributeName)\
	double GLUE(,className)::get##vectorName##attributeName##Value(uint64_t index) const {\
		CHECK_ATTRIBUTE_IN_VECTOR_EXISTENCE(className, vectorName, attributeName)\
		return static_cast<witsml21__##className*>(gsoapProxy2_3)->vectorName[index]->attributeName->__item;\
	}

/**
 * A macro that defines getter uom of measure attribute in vector Implementation
 *
 * @param 	className	 	Name of the class.
 * @param 	vectorName   	Name of the vector.
 * @param 	attributeName	Name of the attribute.
 * @param 	uomDatatype  	The uom datatype.
 */
#define GETTER_UOM_OF_MEASURE_ATTRIBUTE_IN_VECTOR_IMPL(className, vectorName, attributeName, uomDatatype)\
	uomDatatype GLUE(,className)::get##vectorName##attributeName##Uom(uint64_t index) const {\
		CHECK_ATTRIBUTE_IN_VECTOR_EXISTENCE(className, vectorName, attributeName)\
		return static_cast<witsml21__##className*>(gsoapProxy2_3)->vectorName[index]->attributeName->uom;\
	}

/**
 * A macro that defines getter and setter measure attribute in vector Implementation
 *
 * @param 	className	 	Name of the class.
 * @param 	vectorName   	Name of the vector.
 * @param 	attributeName	Name of the attribute.
 * @param 	uomDatatype  	The uom datatype.
 * @param 	constructor  	The constructor.
 */
#define GETTER_AND_SETTER_MEASURE_ATTRIBUTE_IN_VECTOR_IMPL(className, vectorName, attributeName, uomDatatype, constructor)\
	void GLUE(,className)::set##vectorName##attributeName(uint64_t index, double value, uomDatatype uom) {\
		if (value != value) { throw invalid_argument("You cannot set an undefined measured depth coord"); }\
		CREATE_ATTRIBUTE_IN_VECTOR_IF_NOT_PRESENT(className, vectorName, attributeName, constructor)\
		static_cast<witsml21__##className*>(gsoapProxy2_3)->vectorName[index]->attributeName->__item = value;\
		static_cast<witsml21__##className*>(gsoapProxy2_3)->vectorName[index]->attributeName->uom = uom;\
	}\
	GETTER_VALUE_OF_MEASURE_ATTRIBUTE_IN_VECTOR_IMPL(className, vectorName, attributeName)\
	GETTER_UOM_OF_MEASURE_ATTRIBUTE_IN_VECTOR_IMPL(className, vectorName, attributeName, uomDatatype)

 /**
  * A macro that defines getter and setter depth measure attribute in vector Implementation
  *
  * @param 	className	 	Name of the class.
  * @param 	vectorName   	Name of the vector.
  * @param 	attributeName	Name of the attribute.
  * @param 	uomDatatype  	The uom datatype.
  * @param 	constructor  	The constructor.
  */
#define GETTER_AND_SETTER_MEASURED_DEPTH_ATTRIBUTE_IN_VECTOR_IMPL(className, vectorName, attributeName, uomDatatype, constructor)\
	void GLUE(,className)::set##vectorName##attributeName(uint64_t index, double value, uomDatatype uom) {\
		if (value != value) { throw invalid_argument("You cannot set an undefined measured depth coord"); }\
		CREATE_ATTRIBUTE_IN_VECTOR_IF_NOT_PRESENT(className, vectorName, attributeName, constructor)\
		if (static_cast<witsml21__Trajectory*>(gsoapProxy2_3)->TrajectoryStation[index]->Md->MeasuredDepth == nullptr) {\
			static_cast<witsml21__Trajectory*>(gsoapProxy2_3)->TrajectoryStation[index]->Md->MeasuredDepth = gsoap_eml2_3::soap_new_eml23__LengthMeasureExt(gsoapProxy2_3->soap); }\
		static_cast<witsml21__##className*>(gsoapProxy2_3)->vectorName[index]->attributeName->MeasuredDepth->__item = value;\
		static_cast<witsml21__##className*>(gsoapProxy2_3)->vectorName[index]->attributeName->MeasuredDepth->uom = gsoap_eml2_3::soap_eml23__LengthUom2s(gsoapProxy2_3->soap, uom);\
	}\
	double GLUE(,className)::get##vectorName##attributeName##Value(uint64_t index) const {\
		CHECK_ATTRIBUTE_IN_VECTOR_EXISTENCE(className, vectorName, attributeName)\
		return static_cast<witsml21__##className*>(gsoapProxy2_3)->vectorName[index]->attributeName->MeasuredDepth->__item;\
	}\
	uomDatatype GLUE(,className)::get##vectorName##attributeName##Uom(uint64_t index) const {\
		CHECK_ATTRIBUTE_IN_VECTOR_EXISTENCE(className, vectorName, attributeName)\
		gsoap_eml2_3::eml23__LengthUom result;\
		gsoap_eml2_3::soap_s2eml23__LengthUom(gsoapProxy2_3->soap, static_cast<witsml21__##className*>(gsoapProxy2_3)->vectorName[index]->attributeName->MeasuredDepth->uom.c_str(), &result);\
		return result;\
	}

/**
 * A macro that defines getter and setter measure optional attribute in vector Implementation
 *
 * @param 	className	 	Name of the class.
 * @param 	vectorName   	Name of the vector.
 * @param 	attributeName	Name of the attribute.
 * @param 	uomDatatype  	The uom datatype.
 * @param 	constructor  	The constructor.
 */
#define GETTER_AND_SETTER_MEASURE_OPTIONAL_ATTRIBUTE_IN_VECTOR_IMPL(className, vectorName, attributeName, uomDatatype, constructor)\
	GETTER_AND_SETTER_MEASURE_ATTRIBUTE_IN_VECTOR_IMPL(className, vectorName, attributeName, uomDatatype, constructor)\
	GETTER_PRESENCE_ATTRIBUTE_IN_VECTOR_IMPL(className, vectorName, attributeName)

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
#define GETTER_AND_SETTER_MEASURED_DEPTH_OPTIONAL_ATTRIBUTE_IN_VECTOR_IMPL(className, vectorName, attributeName, uomDatatype, constructor)\
	GETTER_AND_SETTER_MEASURED_DEPTH_ATTRIBUTE_IN_VECTOR_IMPL(className, vectorName, attributeName, uomDatatype, constructor)\
	GETTER_PRESENCE_ATTRIBUTE_IN_VECTOR_IMPL(className, vectorName, attributeName)
