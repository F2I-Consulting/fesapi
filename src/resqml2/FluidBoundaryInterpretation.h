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
	class FluidBoundaryInterpretation : public BoundaryFeatureInterpretation
	{
	public:

		/** Destructor does nothing since the memory is managed by the gSOAP context. */
		virtual ~FluidBoundaryInterpretation() = default;

		/** The standard XML tag without XML namespace for serializing this data object. */
		DLL_IMPORT_OR_EXPORT static constexpr char const* XML_TAG = "FluidBoundaryInterpretation";

		DLL_IMPORT_OR_EXPORT std::string getXmlTag() const final { return XML_TAG; }

	protected:

		/** Default constructor Set the gsoap proxy to nullptr from superclass constructor */
		FluidBoundaryInterpretation() {}

		/**
		 * Only to be used in partial transfer context
		 *
		 * @param [in,out]	partialObject	If non-null, the partial object.
		 *
		 * 
		 */
		DLL_IMPORT_OR_EXPORT FluidBoundaryInterpretation(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : BoundaryFeatureInterpretation(partialObject) {}

		/**
		 * Constructor
		 *
		 * @param [in,out]	fromGsoap	If non-null, from gsoap.
		 */
		FluidBoundaryInterpretation(gsoap_eml2_3::_resqml22__FluidBoundaryInterpretation* fromGsoap) : BoundaryFeatureInterpretation(fromGsoap) {}
	};
}
