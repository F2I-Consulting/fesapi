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

#include "../resqml2/AbstractFeatureInterpretation.h"
#include "WellboreMarker.h"

/** . */
namespace RESQML2_0_1_NS
{
	/** A boundary feature interpretation. */
	class BoundaryFeatureInterpretation : public RESQML2_NS::AbstractFeatureInterpretation
	{
	public:

		/**
		 * Only to be used in partial transfer context.
		 *
		 * @param [in]	partialObject	If non-nullptr, the partial object.
		 */
		DLL_IMPORT_OR_EXPORT BoundaryFeatureInterpretation(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) :RESQML2_NS::AbstractFeatureInterpretation(partialObject) {}

		/** Default constructor Set the gSOAP proxy to @c nullptr from super class constructor. */
		BoundaryFeatureInterpretation() {}

		/**
		 * Creates an instance of this class in a gsoap context.
		 *
		 * @exception	std::invalid_argument	If @p feature is @c nullptr.
		 *
		 * @param [in]	feature	The interpreted boundary feature. It cannot be null.
		 * @param 	  	guid   	The guid to set to the boundary feature interpretation. If empty then a
		 * 						new guid will be generated.
		 * @param 	  	title  	The title to set to the boundary feature interpretation. If empty then
		 * 						\"unknown\" title will be set.
		 */
		BoundaryFeatureInterpretation(class BoundaryFeature * feature, const std::string & guid, const std::string & title);

		/**
		 * Creates an instance of this class by wrapping a gSOAP instance.
		 *
		 * @param [in]	fromGsoap	If non-null, the gSOAP instance.
		 */
		BoundaryFeatureInterpretation(gsoap_resqml2_0_1::_resqml20__BoundaryFeatureInterpretation* fromGsoap) : RESQML2_NS::AbstractFeatureInterpretation(fromGsoap) {}
		
		/** Destructor does nothing since the memory is managed by the gSOAP context. */
		virtual ~BoundaryFeatureInterpretation() {}

		/** The standard XML tag without XML namespace for serializing this data object. */
		DLL_IMPORT_OR_EXPORT static const char* XML_TAG;

		DLL_IMPORT_OR_EXPORT virtual std::string getXmlTag() const override { return XML_TAG; }
	};
}
