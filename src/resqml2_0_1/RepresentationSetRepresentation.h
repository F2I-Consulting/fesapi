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

#include "resqml2/RepresentationSetRepresentation.h"

namespace RESQML2_0_1_NS
{
	class DLL_IMPORT_OR_EXPORT RepresentationSetRepresentation : public RESQML2_NS::RepresentationSetRepresentation
	{
	protected:
		RepresentationSetRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp) : RESQML2_NS::RepresentationSetRepresentation(interp) {}

	public:

		/**
		* Only to be used in partial transfer context
		*/
		RepresentationSetRepresentation(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : RESQML2_NS::RepresentationSetRepresentation(partialObject) {}

		/**
		* Creates an instance of this class in a gsoap context.
		* @param horizon the feature the instance interprets.
		* @param title A title for the instance to create.
		*/
		RepresentationSetRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp, const std::string & guid, const std::string & title);

		// To use if the representation set representation is not linked to any interpretation
		RepresentationSetRepresentation(COMMON_NS::EpcDocument* epcDoc, const std::string & guid, const std::string & title);

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		RepresentationSetRepresentation(gsoap_resqml2_0_1::_resqml2__RepresentationSetRepresentation* fromGsoap) : RESQML2_NS::RepresentationSetRepresentation(fromGsoap) {}

		/**
		* Destructor does nothing since the memory is managed by the gsoap context.
		*/
		~RepresentationSetRepresentation() {}
	};
}

