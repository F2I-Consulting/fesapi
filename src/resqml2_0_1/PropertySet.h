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
	* A set of properties collected together for a specific purpose. For example, a property set can be used to collect all the properties corresponding to the simulation output at a single time, or all the values of a single property kind for all times.
	*/
	class PropertySet : public RESQML2_NS::PropertySet
	{
	public:

		/**
		* Only to be used in partial transfer context
		*/
		DLL_IMPORT_OR_EXPORT PropertySet(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : RESQML2_NS::PropertySet(partialObject) {}

		/**
		* Creates an instance of this class in a gsoap context.
		* @param rep The DataObjectRepository where the instance must be created
		* @param guid A guid for the instance to create. Empty guid lead to the creation of a random one.
		* @param title A title for the instance to create.
		* @param hasMultipleRealizations If true, indicates that the collection contains properties with defined realization indices.
		* @param hasSinglePropertyKind If true, indicates that the collection contains only property values associated with a single property kind.
		* @param timeSetKind the time set kind of this property set.
		*/
		PropertySet(COMMON_NS::DataObjectRepository* repo, const std::string & guid, const std::string & title,
			bool hasMultipleRealizations, bool hasSinglePropertyKind, gsoap_resqml2_0_1::resqml20__TimeSetKind timeSetKind);

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		PropertySet(gsoap_resqml2_0_1::_resqml20__PropertySet* fromGsoap) : RESQML2_NS::PropertySet(fromGsoap) {}

		/**
		* Destructor does nothing since the memory is managed by the gsoap context.
		*/
		~PropertySet() {}

		/**
		* If true, indicates that the collection contains properties with defined realization indices.
		*/
		DLL_IMPORT_OR_EXPORT bool hasMultipleRealizations() const;

		/**
		* If true, indicates that the collection contains only property values associated with a single property kind.
		*/
		DLL_IMPORT_OR_EXPORT bool hasSinglePropertyKind() const;

		/**
		* @return The time set kind of this property set.
		*/
		DLL_IMPORT_OR_EXPORT gsoap_resqml2_0_1::resqml20__TimeSetKind getTimeSetKind() const;

	private :

		void setXmlParent(RESQML2_NS::PropertySet * parent);

		gsoap_resqml2_0_1::eml20__DataObjectReference const * getParentDor() const;

		void pushBackXmlProperty(RESQML2_NS::AbstractProperty * prop);

		std::vector<gsoap_resqml2_0_1::eml20__DataObjectReference *> getAllPropertiesDors() const;
	};
}
