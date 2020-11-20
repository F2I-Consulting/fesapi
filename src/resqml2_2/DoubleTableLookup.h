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

#include "../resqml2/DoubleTableLookup.h"

namespace RESQML2_2_NS
{
	/** A string table lookup. */
	class DoubleTableLookup final : public RESQML2_NS::DoubleTableLookup
	{
	public:

		/**
		 * Only to be used in partial transfer context
		 *
		 * @param [in,out]	partialObject	If non-null, the partial object.
		 *
		 * 
		 */
		DLL_IMPORT_OR_EXPORT DoubleTableLookup(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : RESQML2_NS::DoubleTableLookup(partialObject) {}

		/**
		 * Creates an instance of this class in a gsoap context.
		 *
		 * @param [in,out]	repo 	A repo which will manage the memory of this instance.
		 * @param 		  	guid 	The guid to set to this instance. If empty then a new guid will be
		 * 							generated.
		 * @param 		  	title	A title for the instance to create.
		 */
		DoubleTableLookup(COMMON_NS::DataObjectRepository* repo, const std::string & guid, const std::string & title);

		/**
		 * Creates an instance of this class by wrapping a gsoap instance.
		 *
		 * @param [in,out]	fromGsoap	If non-null, from gsoap.
		 */
		DoubleTableLookup(gsoap_eml2_3::_resqml22__DoubleTableLookup* fromGsoap) : RESQML2_NS::DoubleTableLookup(fromGsoap) {}

		/** Destructor does nothing since the memory is managed by the gsoap context. */
		~DoubleTableLookup() = default;

		DLL_IMPORT_OR_EXPORT bool containsKey(double key) final;

		DLL_IMPORT_OR_EXPORT unsigned int getItemCount() const final;

		DLL_IMPORT_OR_EXPORT double getKeyAtIndex(unsigned int index) const final;

		DLL_IMPORT_OR_EXPORT double getValueAtIndex(unsigned int index) const final;

		DLL_IMPORT_OR_EXPORT double getValueAtKey(double key) final;

		DLL_IMPORT_OR_EXPORT void addValue(double key, double longValue) final;

		DLL_IMPORT_OR_EXPORT void setValue(double key, double longValue) final;

		DLL_IMPORT_OR_EXPORT double getMinimumValue() final;

		DLL_IMPORT_OR_EXPORT double getMaximumValue() final;

		DLL_IMPORT_OR_EXPORT std::map<double, double> getMap() const final;

		/**
		* The standard XML namespace for serializing this data object.
		*/
		DLL_IMPORT_OR_EXPORT static const char* XML_NS;

		/**
		* Get the standard XML namespace for serializing this data object.
		*/
		DLL_IMPORT_OR_EXPORT std::string getXmlNamespace() const final { return XML_NS; }
	};
}
