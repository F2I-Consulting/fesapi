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

#include "../eml2/GraphicalInformationSet.h"

namespace EML2_3_NS
{
	/** @brief	Proxy class for handling the graphical information of data objects. */
	class GraphicalInformationSet : public EML2_NS::GraphicalInformationSet
	{
	public:

		/**
		 * Constructor. Only to be used in partial transfer context
		 *
		 * @param [in]	partialObject	If non-null, the partial object.
		 */
		GraphicalInformationSet(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject): EML2_NS::GraphicalInformationSet(partialObject) {}

		/**
		 * Creates a graphical information set.
		 *
		 * @exception	std::invalid_argument	If @p repo is null.
		 *
		 * @param [in,out]	repo 	The repository where the underlying gSOAP proxy is going to be
		 * 							created.
		 * @param 		  	guid 	The guid to set to graphical information set. If empty then a new
		 * 							guid will be generated.
		 * @param 		  	title	A title for graphical information set. If empty then \"unknown\"
		 * 							title will be set.
		 */
		GraphicalInformationSet(COMMON_NS::DataObjectRepository* repo, std::string const& guid, std::string const& title);

		/**
		 * Creates an instance of this class by wrapping a gSOAP instance.
		 *
		 * @param [in]	fromGsoap	If non-null, the gSOAP instance.
		 */
		GraphicalInformationSet(gsoap_eml2_3::_eml23__GraphicalInformationSet* fromGsoap) :
			EML2_NS::GraphicalInformationSet(fromGsoap) {}

		/**
		 * Destructor does nothing since the memory is managed by the gsoap context.
		 */
		~GraphicalInformationSet() {}
	};
}
