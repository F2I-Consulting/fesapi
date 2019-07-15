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

#include "resqml2_0_1/EarthModelInterpretation.h"

namespace RESQML2_0_1_NS
{
	/**
	* This class is a container for other organizations that are consistent to each others.
	*/
	class StratigraphicColumn : public COMMON_NS::AbstractObject
	{
	public:

		/**
		* Only to be used in partial transfer context
		*/
		StratigraphicColumn(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : COMMON_NS::AbstractObject(partialObject) {}

		/**
		* Creates an instance of this class in a gsoap context.
		* @param repo		The repo which will contain the instance.
		* @param guid		The guid to set to the interpretation. If empty then a new guid will be generated.
		* @param title		A title for the instance to create.
		*/
		StratigraphicColumn(COMMON_NS::DataObjectRepository* repo, const std::string & guid, const std::string & title);

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/

		StratigraphicColumn(gsoap_resqml2_0_1::_resqml2__StratigraphicColumn* fromGsoap) : AbstractObject(fromGsoap) {}

		/**
		* Destructor does nothing since the memory is managed by the gsoap context.
		*/
		~StratigraphicColumn() {}

		DLL_IMPORT_OR_EXPORT void pushBackStratiColumnRank(class StratigraphicColumnRankInterpretation const * stratiColumnRank);

		/**
		 * Get all the stratigraphic column rank interpretations which are contained in this stratigraphic column.
		 */
		DLL_IMPORT_OR_EXPORT std::vector<class StratigraphicColumnRankInterpretation const *> getStratigraphicColumnRankInterpretationSet() const;
                
		DLL_IMPORT_OR_EXPORT static const char* XML_TAG;
		DLL_IMPORT_OR_EXPORT virtual std::string getXmlTag() const {return XML_TAG;}

    private:
		void loadTargetRelationships() const;
	};
}
