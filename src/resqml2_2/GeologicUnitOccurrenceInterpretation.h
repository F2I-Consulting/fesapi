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

#include "../resqml2/GeologicUnitOccurrenceInterpretation.h"

namespace RESQML2_2_NS
{
	/**
	* This class is a container for other organizations that are consistent to each others.
	*/
	class GeologicUnitOccurrenceInterpretation final : public RESQML2_NS::GeologicUnitOccurrenceInterpretation
	{
	public:

		/**
		* Only to be used in partial transfer context
		*/
		DLL_IMPORT_OR_EXPORT GeologicUnitOccurrenceInterpretation(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : RESQML2_NS::GeologicUnitOccurrenceInterpretation(partialObject) {}

		/**
		 * @brief	Creates an instance of this class in a gsoap context.
		 *
		 * @exception	std::invalid_argument	If <tt>orgFeat == nullptr</tt>.
		 *
		 * @param [in]	orgFeat				The feature the instance interprets. It must be a
		 * 									stratigraphic organization feature.
		 * @param 	  	guid				The guid to set to the interpretation. If empty then a new
		 * 									guid will be generated.
		 * @param 	  	title				A title for the instance to create.
		 * @param 	  	orderingCriteria	The ordering criteria.
		 */
		GeologicUnitOccurrenceInterpretation(RESQML2_NS::Model * orgFeat, const std::string & guid, const std::string & title, gsoap_resqml2_0_1::resqml20__OrderingCriteria orderingCriteria);

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		GeologicUnitOccurrenceInterpretation(gsoap_eml2_3::_resqml22__GeologicUnitOccurrenceInterpretation* fromGsoap) : RESQML2_NS::GeologicUnitOccurrenceInterpretation(fromGsoap) {}

		/** Destructor does nothing since the memory is managed by the gsoap context. */
		~GeologicUnitOccurrenceInterpretation() = default;

		DLL_IMPORT_OR_EXPORT void setStratigraphicColumnRankInterpretation(RESQML2_NS::StratigraphicColumnRankInterpretation * stratiColumnRankInterp) final;

		COMMON_NS::DataObjectReference getStratigraphicColumnRankInterpretationDor() const final;

		/**
		* The standard XML namespace for serializing this data object.
		*/
		DLL_IMPORT_OR_EXPORT static const char* XML_NS;

		/**
		* Get the standard XML namespace for serializing this data object.
		*/
		DLL_IMPORT_OR_EXPORT std::string getXmlNamespace() const final { return XML_NS; }

		/** The standard XML tag without XML namespace for serializing this data object. */
		DLL_IMPORT_OR_EXPORT static const char* XML_TAG;

		DLL_IMPORT_OR_EXPORT virtual std::string getXmlTag() const final { return XML_TAG; }
	};
}