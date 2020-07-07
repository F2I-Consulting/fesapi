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

#include "../resqml2/BoundaryFeatureInterpretation.h"

namespace RESQML2_NS
{
	/**
	 * @brief	A type of boundary feature, this class identifies if the boundary is a geobody and
	 * 			the type of the boundary.
	 */
	class GeobodyBoundaryInterpretation : public BoundaryFeatureInterpretation
	{
	public:

		/** Destructor does nothing since the memory is managed by the gSOAP context. */
		virtual ~GeobodyBoundaryInterpretation() {}

		/** The standard XML tag without XML namespace for serializing this data object. */
		DLL_IMPORT_OR_EXPORT static const char* XML_TAG;

		DLL_IMPORT_OR_EXPORT virtual std::string getXmlTag() const final { return XML_TAG; }

	protected:

		/** Default constructor. */
		GeobodyBoundaryInterpretation() {}

		/**
		 * Only to be used in partial transfer context
		 *
		 * @param [in,out]	partialObject	If non-null, the partial object.
		 *
		 * 
		 */
		DLL_IMPORT_OR_EXPORT GeobodyBoundaryInterpretation(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) :
			BoundaryFeatureInterpretation(partialObject) {}

		/**
		 * Creates an instance of this class by wrapping a gsoap instance.
		 *
		 * @param [in,out]	fromGsoap	If non-null, from gsoap.
		 */
		GeobodyBoundaryInterpretation(gsoap_resqml2_0_1::_resqml20__GeobodyBoundaryInterpretation* fromGsoap) : BoundaryFeatureInterpretation(fromGsoap) {}

		/**
		 * Creates an instance of this class by wrapping a gsoap instance.
		 *
		 * @param [in,out]	fromGsoap	If non-null, from gsoap.
		 */
		GeobodyBoundaryInterpretation(gsoap_eml2_3::_resqml22__GeobodyBoundaryInterpretation* fromGsoap) : BoundaryFeatureInterpretation(fromGsoap) {}
	};
}
