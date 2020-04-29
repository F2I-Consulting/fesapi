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

#include "AbstractFeatureInterpretation.h"

namespace RESQML2_NS
{
	/** @brief	The interpretation of a stratigraphic unit. */
	class StratigraphicUnitInterpretation : public AbstractFeatureInterpretation
	{
	public:

		/** Destructor does nothing since the memory is managed by the gSOAP context. */
		virtual ~StratigraphicUnitInterpretation() {}

		/**
		 * Indicates if this instance has an information about its deposition mode.
		 *
		 * @returns	True if the deposition mode is known, false if not.
		 */
		DLL_IMPORT_OR_EXPORT virtual bool hasDepositionMode() const = 0;

		/**
		 * Gets the deposition mode of this stratigraphic unit interpretation.
		 *
		 * @exception	logic_error	If the deposition mode is unknown for this instance (you should
		 * 							verify its existence using hasDepositionMode() before to call this
		 * 							function).
		 *
		 * @returns	The deposition mode.
		 */
		DLL_IMPORT_OR_EXPORT virtual gsoap_resqml2_0_1::resqml20__DepositionMode getDepositionMode() const = 0;

		/** The standard XML tag without XML namespace for serializing this data object. */
		DLL_IMPORT_OR_EXPORT static const char* XML_TAG;

		DLL_IMPORT_OR_EXPORT virtual std::string getXmlTag() const final { return XML_TAG; }

	protected :

		/**
		 * Only to be used in partial transfer context
		 *
		 * @param [in,out]	partialObject	If non-null, the partial object.
		 *
		 * 
		 */
		DLL_IMPORT_OR_EXPORT StratigraphicUnitInterpretation(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : AbstractFeatureInterpretation(partialObject) {}

		/**
		 * Creates an instance of this class in a gsoap context.
		 *
		 * @param [in,out]	feature	The feature the instance interprets.
		 * @param 		  	guid   	The guid to set to the interpretation. If empty then a new guid will
		 * 							be generated.
		 * @param 		  	title  	A title for the instance to create.
		 */
		StratigraphicUnitInterpretation() {}

		/**
		 * Creates an instance of this class by wrapping a gsoap instance.
		 *
		 * @param [in,out]	fromGsoap	If non-null, from gsoap.
		 */
		StratigraphicUnitInterpretation(gsoap_resqml2_0_1::_resqml20__StratigraphicUnitInterpretation* fromGsoap) : AbstractFeatureInterpretation(fromGsoap) {}

		/**
		 * Creates an instance of this class by wrapping a gsoap instance.
		 *
		 * @param [in,out]	fromGsoap	If non-null, from gsoap.
		 */
		StratigraphicUnitInterpretation(gsoap_eml2_3::_resqml22__StratigraphicUnitInterpretation* fromGsoap) : AbstractFeatureInterpretation(fromGsoap) {}
	};
}
