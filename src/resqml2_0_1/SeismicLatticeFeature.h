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

#include "../resqml2/AbstractTechnicalFeature.h"

/** . */
namespace RESQML2_0_1_NS
{
	/** A seismic lattice feature. */
	class SeismicLatticeFeature : public RESQML2_NS::AbstractTechnicalFeature
	{
	public:

		/**
		 * Only to be used in partial transfer context
		 *
		 * @param [in,out]	partialObject	If non-null, the partial object.
		 *
		 * @returns	A DLL_IMPORT_OR_EXPORT.
		 */
		DLL_IMPORT_OR_EXPORT SeismicLatticeFeature(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : RESQML2_NS::AbstractTechnicalFeature(partialObject) {}

		/**
		 * Creates an instance of this class in a gsoap context.
		 *
		 * @param [in,out]	repo			  	The repo where the underlying gsoap proxy is going to be
		 * 										created.
		 * @param 		  	guid			  	The guid to set to this instance. If empty then a new
		 * 										guid will be generated.
		 * @param 		  	title			  	A title for the instance to create.
		 * @param 		  	inlineIncrement   	The inline index increment. If inlines are parallel to
		 * 										the i-axis the inline increment will be the difference in
		 * 										the inline number from node i=0, j=0 to node i=1, j=0. If
		 * 										inlines are parallel to the j-axis the inline increment
		 * 										will be the difference in the inline number from node i=0,
		 * 										j=0 to node i=0, j=1. The increment can be a positive or
		 * 										negative integer, but not zero.
		 * @param 		  	crosslineIncrement	The crossline increment. The increment can be a positive
		 * 										or negative integer, but not zero.
		 * @param 		  	originInline	  	The index of the first inline beginning at i=0, j=0.
		 * @param 		  	originCrossline   	The index of the first crosslineline beginning at i=0,
		 * 										j=0.
		 * @param 		  	inlineCount		  	The count of inlines in this seismic lattice.
		 * @param 		  	crosslineCount	  	The count of crosslines in this seismic lattice.
		 */
		SeismicLatticeFeature(COMMON_NS::DataObjectRepository* repo, const std::string & guid, const std::string & title,
			int inlineIncrement, int crosslineIncrement,
			unsigned int originInline, unsigned int originCrossline,
			unsigned int inlineCount, unsigned int crosslineCount);

		/**
		 * Creates an instance of this class by wrapping a gsoap instance.
		 *
		 * @param [in,out]	fromGsoap	If non-null, from gsoap.
		 */
		SeismicLatticeFeature(gsoap_resqml2_0_1::_resqml20__SeismicLatticeFeature* fromGsoap): RESQML2_NS::AbstractTechnicalFeature(fromGsoap) {}

		/** Destructor does nothing since the memory is manged by the gsoap context. */
		~SeismicLatticeFeature() {}

		/**
		 * Get the crossline index increment between two consecutive crosslines.
		 *
		 * @returns	The crossline increment.
		 */
		DLL_IMPORT_OR_EXPORT int getCrosslineIncrement() const;

		/**
		 * Get the inline index increment between two consecutive inlines.
		 *
		 * @returns	The inline increment.
		 */
		DLL_IMPORT_OR_EXPORT int getInlineIncrement() const;

		/**
		 * Get the index of the first crossline.
		 *
		 * @returns	The origin crossline.
		 */
		DLL_IMPORT_OR_EXPORT int getOriginCrossline() const;

		/**
		 * Get the index of the first inline.
		 *
		 * @returns	The origin inline.
		 */
		DLL_IMPORT_OR_EXPORT int getOriginInline() const;

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
		DLL_IMPORT_OR_EXPORT virtual std::string getXmlTag() const { return XML_TAG; }
	};
}
