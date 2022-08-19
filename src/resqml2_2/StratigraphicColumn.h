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

#include "../resqml2/StratigraphicColumn.h"

namespace RESQML2_2_NS
{
	/** This class is a container for other organizations that are consistent to each others. */
	class StratigraphicColumn final : public RESQML2_NS::StratigraphicColumn
	{
	public:

		/**
		 * Only to be used in partial transfer context
		 *
		 * @param [in,out]	partialObject	If non-null, the partial object.
		 *
		 * 
		 */
		DLL_IMPORT_OR_EXPORT StratigraphicColumn(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : RESQML2_NS::StratigraphicColumn(partialObject) {}

		/**
		 * Creates an instance of this class in a gsoap context.
		 *
		 * @param [in,out]	repo 	The repo which will contain the instance.
		 * @param 		  	guid 	The guid to set to the interpretation. If empty then a new guid will
		 * 							be generated.
		 * @param 		  	title	A title for the instance to create.
		 */
		StratigraphicColumn(COMMON_NS::DataObjectRepository* repo, const std::string & guid, const std::string & title);

		/**
		 * Creates an instance of this class by wrapping a gsoap instance.
		 *
		 * @param [in,out]	fromGsoap	If non-null, from gsoap.
		 */
		StratigraphicColumn(gsoap_eml2_3::_resqml22__StratigraphicColumn* fromGsoap) : RESQML2_NS::StratigraphicColumn(fromGsoap) {}

		/** Destructor does nothing since the memory is managed by the gsoap context. */
		~StratigraphicColumn() = default;

		DLL_IMPORT_OR_EXPORT void pushBackStratiColumnRank(RESQML2_NS::StratigraphicColumnRankInterpretation * stratiColumnRank) final;

		DLL_IMPORT_OR_EXPORT uint64_t getStratigraphicColumnRankInterpretationCount() const final;

		COMMON_NS::DataObjectReference getStratigraphicColumnRankInterpretationDor(uint64_t index) const final;

		/**
		* The standard XML namespace for serializing this data object.
		*/
		DLL_IMPORT_OR_EXPORT static constexpr char const* XML_NS = "resqml22";

		/**
		* Get the standard XML namespace for serializing this data object.
		*/
		DLL_IMPORT_OR_EXPORT std::string getXmlNamespace() const final { return XML_NS; }
	};
}
