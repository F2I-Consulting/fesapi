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

#include "../resqml2/CmpLineFeature.h"

namespace RESQML2_2_NS
{
	/** A seismic line feature. */
	class CmpLineFeature final : public RESQML2_NS::CmpLineFeature
	{
	public:

		/**
		 * Only to be used in partial transfer context
		 *
		 * @param [in,out]	partialObject	If non-null, the partial object.
		 *
		 * 
		 */
		DLL_IMPORT_OR_EXPORT CmpLineFeature(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : RESQML2_NS::CmpLineFeature(partialObject) {}

		/**
		 * @brief	Creates an instance of this class in a gsoap context.
		 *
		 * @param [in,out]	repo								The repo where the underlying gsoap proxy
		 * 														is going to be created.
		 * @param 		  	guid								The guid to set to this instance. If
		 * 														empty then a new guid will be generated.
		 * @param 		  	title								A title for the instance to create.
		 * @param 		  	nearestShotPointIndicesIncrement	The trace index increment. The trace
		 * 														index increment will be the difference in the
		 * 														trace number from abscissa i=0 and abscissa
		 * 														i=1. The increment can be a positive or
		 * 														negative integer, but not zero.
		 * @param 		  	firstNearestShotPointIndex			The index of the first trace beginning at
		 * 														abscissa i=0.
		 * @param 		  	nearestShotPointCount				The count of traces in this seismic line.
		 */
		CmpLineFeature(COMMON_NS::DataObjectRepository* repo, const std::string & guid, const std::string & title,
			int64_t nearestShotPointIndicesIncrement, int64_t firstNearestShotPointIndex, uint64_t nearestShotPointCount);

		/**
		 * Creates an instance of this class by wrapping a gsoap instance.
		 *
		 * @param [in,out]	fromGsoap	If non-null, from gsoap.
		 */
		CmpLineFeature(gsoap_eml2_3::_resqml22__CmpLineFeature* fromGsoap):
			RESQML2_NS::CmpLineFeature(fromGsoap) {}

		/** Destructor does nothing since the memory is manged by the gsoap context. */
		~CmpLineFeature() = default;

		/**
		* The standard XML namespace for serializing this data object.
		*/
		DLL_IMPORT_OR_EXPORT static const char* XML_NS;

		/**
		* Get the standard XML namespace for serializing this data object.
		*/
		DLL_IMPORT_OR_EXPORT std::string getXmlNamespace() const final { return XML_NS; }
	};
}
