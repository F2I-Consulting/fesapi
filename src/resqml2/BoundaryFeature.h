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

#include "AbstractFeature.h"

/** . */
namespace RESQML2_NS
{
	/** A boundary feature. */
	class BoundaryFeature : public AbstractFeature
	{
	public:
		
		/** Destructor does nothing since the memory is managed by the gSOAP context. */
		virtual ~BoundaryFeature() {}

		/** The standard XML tag without XML namespace for serializing this data object. */
		DLL_IMPORT_OR_EXPORT static const char* XML_TAG;

		DLL_IMPORT_OR_EXPORT virtual std::string getXmlTag() const override { return XML_TAG; }
		
	protected:

		/**
		 * Only to be used in partial transfer context.
		 *
		 * @param [in]	partialObject	If non-nullptr, the partial object.
		 */
		DLL_IMPORT_OR_EXPORT BoundaryFeature(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : AbstractFeature(partialObject) {}

		/** Default constructor sets the gSOAP proxy to @c nullptr from the super class constructor. */
		BoundaryFeature() {}

		/**
		 * Creates an instance of this class by wrapping a gSOAP instance.
		 *
		 * @param [in]	fromGsoap	If non-null, the gSOAP instance.
		 */
		BoundaryFeature(gsoap_resqml2_0_1::_resqml20__BoundaryFeature* fromGsoap): AbstractFeature(fromGsoap) {}

		/**
		 * Creates an instance of this class by wrapping a gSOAP instance.
		 *
		 * @param [in]	fromGsoap	If non-null, the gSOAP instance.
		 */
		BoundaryFeature(gsoap_eml2_3::_resqml22__BoundaryFeature* fromGsoap): AbstractFeature(fromGsoap) {}
	
	};
}

