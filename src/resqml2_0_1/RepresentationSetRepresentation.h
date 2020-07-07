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

#include "../resqml2/RepresentationSetRepresentation.h"

namespace RESQML2_0_1_NS
{
	/** Proxy class for a representation set representation. */
	class RepresentationSetRepresentation final : public RESQML2_NS::RepresentationSetRepresentation
	{
	public:

		/**
		 * Only to be used in partial transfer context.
		 *
		 * @param [in]	partialObject	If non-nullptr, the partial object.
		 */
		DLL_IMPORT_OR_EXPORT RepresentationSetRepresentation(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : RESQML2_NS::RepresentationSetRepresentation(partialObject) {}

		/**
		 * @brief	Creates an instance of this class in a gSOAP context.
		 *
		 * @exception	std::invalid_argument	If <tt>interp == nullptr</tt>.
		 *
		 * @param [in]	interp	the interpretation the instance represents.
		 * @param 	  	guid  	A guid for the instance to create. Empty guid lead to the creation of a
		 * 						random one.
		 * @param 	  	title 	A title for the instance to create.
		 */
		RepresentationSetRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp, const std::string & guid, const std::string & title);

		/**
		 * To use if the representation set representation is not linked to any interpretation
		 *
		 * @param [in,out]	repo 	If non-null, the repo.
		 * @param 		  	guid 	Unique identifier.
		 * @param 		  	title	The title.
		 */
		RepresentationSetRepresentation(COMMON_NS::DataObjectRepository* repo, const std::string & guid, const std::string & title);

		/**
		 * Creates an instance of this class by wrapping a gsoap instance.
		 *
		 * @param [in,out]	fromGsoap	If non-null, from gsoap.
		 */
		RepresentationSetRepresentation(gsoap_resqml2_0_1::_resqml20__RepresentationSetRepresentation* fromGsoap) : RESQML2_NS::RepresentationSetRepresentation(fromGsoap) {}

		/** Destructor does nothing since the memory is managed by the gsoap context. */
		~RepresentationSetRepresentation() {}

		/**
		* The standard XML namespace for serializing this data object.
		*/
		DLL_IMPORT_OR_EXPORT static const char* XML_NS;

		/**
		* Get the standard XML namespace for serializing this data object.
		*/
		DLL_IMPORT_OR_EXPORT virtual std::string getXmlNamespace() const { return XML_NS; }
	};
}
