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

#include "AbstractGeologicFeature.h"

namespace RESQML2_0_1_NS
{
	class GeologicUnitFeature : public AbstractGeologicFeature
	{
	protected :

		/**
		* Default constructor
		* Set the gsoap proxy to nullptr from superclass constructor
		*/
		GeologicUnitFeature() {}

	public:

		/**
		* Only to be used in partial transfer context
		*/
		DLL_IMPORT_OR_EXPORT GeologicUnitFeature(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : AbstractGeologicFeature(partialObject) {}

		/**
		* Creates an instance of this class in a gsoap context.
		* @param repo		A repo which will manage the memory of this instance.
		* @param guid		The guid to set to the boundary horizon. If empty then a new guid will be generated.
		* @param title		A title for the instance to create.
		*/
		GeologicUnitFeature(COMMON_NS::DataObjectRepository * repo, const std::string & guid, const std::string & title);

		GeologicUnitFeature(gsoap_resqml2_0_1::_resqml20__GeologicUnitFeature* fromGsoap): AbstractGeologicFeature(fromGsoap) {}
		virtual ~GeologicUnitFeature() {}
	
		/**
		* The standard XML tag without XML namespace for serializing this data object.
		*/
		DLL_IMPORT_OR_EXPORT static const char* XML_TAG;

		/**
		* Get the standard XML tag without XML namespace for serializing this data object.
		*/
		DLL_IMPORT_OR_EXPORT virtual std::string getXmlTag() const { return XML_TAG; }
	};
}
