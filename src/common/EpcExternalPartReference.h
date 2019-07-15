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

#include "common/AbstractObject.h"

namespace COMMON_NS
{
	class EpcExternalPartReference : public COMMON_NS::AbstractObject
	{
	public:
		/**
		* @param packageDirAbsolutePath		The directory where the EPC document is stored. Must end with a slash or back-slash
		* @param externalFilePath			The relative path regarding packageDirectoryAbsolutePath where the external resource is located
		*/
		EpcExternalPartReference() {}

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		EpcExternalPartReference(gsoap_resqml2_0_1::_eml20__EpcExternalPartReference* fromGsoap):
			COMMON_NS::AbstractObject(fromGsoap) {}

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		EpcExternalPartReference(gsoap_eml2_1::_eml21__EpcExternalPartReference* fromGsoap) :
			COMMON_NS::AbstractObject(fromGsoap) {}

		/**
		* Destructor does nothing since the memory is managed by the gsoap context.
		*/
		~EpcExternalPartReference() {}

		DLL_IMPORT_OR_EXPORT static const char* XML_TAG;
		DLL_IMPORT_OR_EXPORT virtual std::string getXmlTag() const;

	protected:
		void loadTargetRelationships() const;
	};
}
