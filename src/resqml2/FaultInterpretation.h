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

#include "BoundaryFeatureInterpretation.h"

namespace RESQML2_NS
{
	/**
	 * A fault interpretation. This type of boundary feature contains the data describing an opinion
	 * about the characterization of the fault.
	 */
	class FaultInterpretation : public BoundaryFeatureInterpretation
	{
	public:

		/** Destructor does nothing since the memory is managed by the gSOAP context. */
		virtual ~FaultInterpretation() {}

		/**
		 * Pushes back a new throw interpretation for this fault interpretation. More than one throw
		 * kind is necessary if for example the throw is reverse at a time period and then normal at
		 * another time period.
		 *
		 * @param 	throwKind	The throw kind to push back.
		 */
		DLL_IMPORT_OR_EXPORT virtual void pushBackThrowInterpretation(gsoap_resqml2_0_1::resqml20__ThrowKind throwKind) = 0; // TODO: add a parameter to be able to indicate the time period the throw occured.

		/** The standard XML tag without XML namespace for serializing this data object. */
		DLL_IMPORT_OR_EXPORT static const char* XML_TAG;

		DLL_IMPORT_OR_EXPORT std::string getXmlTag() const final { return XML_TAG; }

	protected:

		/**
		 * Only to be used in partial transfer context
		 *
		 * @param [in,out]	partialObject	If non-null, the partial object.
		 *
		 * @returns	A DLL_IMPORT_OR_EXPORT.
		 */
		DLL_IMPORT_OR_EXPORT FaultInterpretation(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : BoundaryFeatureInterpretation(partialObject) {}

		/**
		 * Default constructor
		 */
		FaultInterpretation() {}

		/**
		 * Creates an instance of this class by wrapping a gsoap instance.
		 *
		 * @param [in,out]	fromGsoap	If non-null, from gsoap.
		 */
		FaultInterpretation(gsoap_resqml2_0_1::_resqml20__FaultInterpretation* fromGsoap) : BoundaryFeatureInterpretation(fromGsoap) {}

		/**
		 * Creates an instance of this class by wrapping a gsoap instance.
		 *
		 * @param [in,out]	fromGsoap	If non-null, from gsoap.
		 */
		FaultInterpretation(gsoap_eml2_3::_resqml22__FaultInterpretation* fromGsoap) : BoundaryFeatureInterpretation(fromGsoap) {}
	};
}
