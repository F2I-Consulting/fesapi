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

#include "AbstractDiscreteOrCategoricalProperty.h"

namespace RESQML2_NS
{
	class StringTableLookup;

	/**
	 * @brief	Proxy class for a categorical property. It contains discrete integers. This type of
	 * 			property is associated either: as an internally stored index to a string through a
	 * 			lookup mapping, or as an internally stored double to another double value through an
	 * 			explicitly provided table.
	 */
	class CategoricalProperty : public AbstractDiscreteOrCategoricalProperty
	{
	public:

		/**
		 * Only to be used in partial transfer context.
		 *
		 * @param [in]	partialObject	If non-nullptr, the partial object.
		 */
		DLL_IMPORT_OR_EXPORT CategoricalProperty(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : AbstractDiscreteOrCategoricalProperty(partialObject) {}

		/** Destructor does nothing since the memory is managed by the gSOAP context. */
		virtual ~CategoricalProperty() {}

		/**   
		 * Gets the string lookup which is associated to this categorical property values. 
		 * 
		 * 	@returns A pointer to the string lookup which is associated to this categorical property
		 * 			 values.
		 */
		DLL_IMPORT_OR_EXPORT StringTableLookup* getStringLookup();

		/**
		 * Gets the DOR of the string lookup which is associated to this categorical property values.
		 *
		 * @returns	The DOR of the string lookup which is associated to this categorical property.
		 */
		DLL_IMPORT_OR_EXPORT virtual COMMON_NS::DataObjectReference getStringLookupDor() const = 0;

		/** The standard XML tag without XML namespace for serializing this data object. */
		DLL_IMPORT_OR_EXPORT static const char* XML_TAG;

		DLL_IMPORT_OR_EXPORT virtual std::string getXmlTag() const override { return XML_TAG; }

	protected:

		/** Default constructor */
		CategoricalProperty() {}

		/**
		 * Creates an instance of this class by wrapping a gSOAP RESQML2.0.1 instance
		 *
		 * @param [in]	fromGsoap	If non-null, the gSOAP instance.
		 */
		CategoricalProperty(gsoap_resqml2_0_1::_resqml20__CategoricalProperty* fromGsoap) : AbstractDiscreteOrCategoricalProperty(fromGsoap) {}

		/**
		 * Creates an instance of this class by wrapping a gSOAP RESQML2.2 instance
		 *
		 * @param [in]	fromGsoap	If non-null, the gSOAP instance.
		 */
		CategoricalProperty(gsoap_eml2_3::_resqml22__CategoricalProperty* fromGsoap) : AbstractDiscreteOrCategoricalProperty(fromGsoap) {}

		/** Loads target relationships */
		void loadTargetRelationships() final;
	};
}
