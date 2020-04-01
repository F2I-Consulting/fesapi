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

/** . */
namespace RESQML2_NS
{
	class RockVolumeFeature;

	/** A geobody interpretation. */
	class GeobodyInterpretation : public RESQML2_NS::AbstractFeatureInterpretation
	{
	public:

		/** Destructor does nothing since the memory is managed by the gsoap context. */
		virtual ~GeobodyInterpretation() {}

		/**
		 * Set the geobody 3d shape
		 *
		 * @param 	geobody3dShape	The geobody 3D shape.
		 */
		DLL_IMPORT_OR_EXPORT virtual void set3dShape(gsoap_eml2_3::resqml22__Shape3d geobody3dShape) = 0;

		/**
		 * check if the 3d shape of this geobody is known
		 *
		 * @returns	True if 3D shape, false if not.
		 */
		DLL_IMPORT_OR_EXPORT virtual bool has3dShape() const = 0;

		/**
		 * get the 3d shape of this geobody
		 *
		 * @returns	The 3D shape.
		 */
		DLL_IMPORT_OR_EXPORT virtual gsoap_eml2_3::resqml22__Shape3d get3dShape() const = 0;

		/**
		 * The standard XML tag without XML namespace for serializing this data object.
		 *
		 * @returns	The XML tag.
		 */
		DLL_IMPORT_OR_EXPORT static const char* XML_TAG;

		/**
		 * Get the standard XML tag without XML namespace for serializing this data object.
		 *
		 * @returns	The XML tag.
		 */
		DLL_IMPORT_OR_EXPORT virtual std::string getXmlTag() const final { return XML_TAG; }

	protected:

		/**
		 * Only to be used in partial transfer context
		 *
		 * @param [in,out]	partialObject	If non-null, the partial object.
		 *
		 * @returns	A DLL_IMPORT_OR_EXPORT.
		 */
		DLL_IMPORT_OR_EXPORT GeobodyInterpretation(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : RESQML2_NS::AbstractFeatureInterpretation(partialObject) {}

		/**
		 * Default constructor
		 */
		GeobodyInterpretation() {}

		/**
		 * Creates an instance of this class by wrapping a gsoap instance.
		 *
		 * @param [in,out]	fromGsoap	If non-null, from gsoap.
		 */
		GeobodyInterpretation(gsoap_resqml2_0_1::_resqml20__GeobodyInterpretation* fromGsoap) : RESQML2_NS::AbstractFeatureInterpretation(fromGsoap) {}

		/**
		 * Creates an instance of this class by wrapping a gsoap instance.
		 *
		 * @param [in,out]	fromGsoap	If non-null, from gsoap.
		 */
		GeobodyInterpretation(gsoap_eml2_3::_resqml22__GeobodyInterpretation* fromGsoap) : RESQML2_NS::AbstractFeatureInterpretation(fromGsoap) {}
	};
}
