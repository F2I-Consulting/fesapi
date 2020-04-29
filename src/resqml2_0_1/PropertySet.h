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

#include "../resqml2/PropertySet.h"

namespace RESQML2_0_1_NS
{
	/**
	 * A set of properties collected together for a specific purpose. For example, a property set
	 * can be used to collect all the properties corresponding to the simulation output at a single
	 * time, or all the values of a single property kind for all times.
	 */
	class PropertySet final : public RESQML2_NS::PropertySet
	{
	public:

		/**
		 * Only to be used in partial transfer context
		 *
		 * @param [in,out]	partialObject	If non-null, the partial object.
		 *
		 * 
		 */
		DLL_IMPORT_OR_EXPORT PropertySet(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : RESQML2_NS::PropertySet(partialObject) {}

		/**
		 * @brief	Creates an instance of this class in a gsoap context.
		 *
		 * @exception	std::invalid_argument	If <tt>repo == nullptr</tt>.
		 * @exception	std::invalid_argument	If @p timeSetKind is single time series.
		 *
		 * @param [in]	repo				   	The DataObjectRepository where the instance must be
		 * 											created.
		 * @param 	  	guid				   	A guid for the instance to create. Empty guid lead to the
		 * 										creation of a random one.
		 * @param 	  	title				   	A title for the instance to create.
		 * @param 	  	hasMultipleRealizations	If true, indicates that the collection contains
		 * 										properties with defined realization indices.
		 * @param 	  	hasSinglePropertyKind  	If true, indicates that the collection contains only
		 * 										property values associated with a single property kind.
		 * @param 	  	timeSetKind			   	the time set kind of this property set.
		 */
		PropertySet(COMMON_NS::DataObjectRepository* repo, const std::string & guid, const std::string & title,
			bool hasMultipleRealizations, bool hasSinglePropertyKind, gsoap_eml2_3::resqml22__TimeSetKind timeSetKind);

		/**
		 * Creates an instance of this class by wrapping a gsoap instance.
		 *
		 * @param [in,out]	fromGsoap	If non-null, from gsoap.
		 */
		PropertySet(gsoap_resqml2_0_1::_resqml20__PropertySet* fromGsoap) : RESQML2_NS::PropertySet(fromGsoap) {}

		/** Destructor does nothing since the memory is managed by the gsoap context. */
		~PropertySet() {}

		DLL_IMPORT_OR_EXPORT bool hasMultipleRealizations() const final;

		DLL_IMPORT_OR_EXPORT bool hasSinglePropertyKind() const final;

		DLL_IMPORT_OR_EXPORT gsoap_eml2_3::resqml22__TimeSetKind getTimeSetKind() const final;

	private :

		/**
		 * Sets XML parent
		 *
		 * @param [in,out]	parent	If non-null, the parent.
		 */
		void setXmlParent(RESQML2_NS::PropertySet * parent);

		COMMON_NS::DataObjectReference getParentDor() const;

		/**
		 * Pushes a back XML property
		 *
		 * @param [in,out]	prop	If non-null, the property.
		 */
		void pushBackXmlProperty(RESQML2_NS::AbstractProperty * prop);

		std::vector<COMMON_NS::DataObjectReference> getAllPropertiesDors() const;
	};
}
