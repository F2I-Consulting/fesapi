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

namespace RESQML2_NS{
	class AbstractRepresentation;
	class AbstractProperty;
}

namespace COMMON_NS
{
	class DLL_IMPORT_OR_EXPORT EpcExternalPartReference : public COMMON_NS::AbstractObject
	{
	protected:
		/**
		* Only to be used in partial transfer context
		*/
		EpcExternalPartReference(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : COMMON_NS::AbstractObject(partialObject) {}

	public:
		/**
		* @param packageDirAbsolutePath		The directory where the EPC document is stored. Must end with a slash or back-slash
		* @param externalFilePath			The relative path regarding packageDirectoryAbsolutePath where the external resource is located
		*/
		EpcExternalPartReference(const std::string & packageDirAbsolutePath, const std::string & externalFilePath);

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		EpcExternalPartReference(gsoap_resqml2_0_1::_eml20__EpcExternalPartReference* fromGsoap, const std::string & packageDirAbsolutePath, const std::string & externalFilePath):
			COMMON_NS::AbstractObject(fromGsoap), packageDirectoryAbsolutePath(packageDirAbsolutePath), relativeFilePath(externalFilePath) {}

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		EpcExternalPartReference(gsoap_eml2_1::_eml21__EpcExternalPartReference* fromGsoap, const std::string & packageDirAbsolutePath, const std::string & externalFilePath) :
			COMMON_NS::AbstractObject(fromGsoap), packageDirectoryAbsolutePath(packageDirAbsolutePath), relativeFilePath(externalFilePath) {}

		/**
		* Destructor does nothing since the memory is managed by the gsoap context.
		*/
		~EpcExternalPartReference() {}

		/**
		* Get the relative path regarding packageDirectoryAbsolutePath where the external resource is located.
		*/
		std::string getRelativePath() const { return relativeFilePath; }

		static const char* XML_TAG;
		virtual std::string getXmlTag() const;

		std::vector<epc::Relationship> getAllSourceRelationships() const;
		std::vector<epc::Relationship> getAllTargetRelationships() const;

		/**
		* Does nothing since EPC external part reference has not target relationships at all
		*/
		void resolveTargetRelationships(COMMON_NS::EpcDocument* epcDoc);

	protected:

		std::vector<RESQML2_NS::AbstractRepresentation*> representationSourceObject;					/// All the representations that use this external reference.
		std::vector<RESQML2_NS::AbstractProperty*> propertySourceObject;								/// All the properties that use this external reference.
		std::string packageDirectoryAbsolutePath;												/// The directory where the EPC document is stored.
		std::string relativeFilePath;															/// Must be relative to the location of the package
	};
}

