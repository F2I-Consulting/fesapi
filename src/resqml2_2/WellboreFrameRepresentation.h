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

#include "../resqml2/WellboreFrameRepresentation.h"

namespace RESQML2_2_NS
{
	/** @brief	A wellbore frame representation. */
	class WellboreFrameRepresentation : public RESQML2_NS::WellboreFrameRepresentation
	{
	public:

		/**
		* Only to be used in partial transfer context
		*/
		DLL_IMPORT_OR_EXPORT WellboreFrameRepresentation(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) :
			RESQML2_NS::WellboreFrameRepresentation(partialObject) {}

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		WellboreFrameRepresentation(gsoap_eml2_3::resqml22__WellboreFrameRepresentation* fromGsoap):
			RESQML2_NS::WellboreFrameRepresentation(fromGsoap) {}

		/**
		* Creates an instance of this class in a gsoap context.
		* @param interp		The WellboreFeature interpretation the instance represents.
		* @param guid		The guid to set to the new instance. If empty then a new guid will be generated.
		* @param title		A title for the instance to create.
		* @param traj		The trajectory this WellboreFeature frame is based on.
		*/
		WellboreFrameRepresentation(RESQML2_NS::WellboreInterpretation* interp, const std::string& guid, const std::string& title, RESQML2_NS::WellboreTrajectoryRepresentation* traj);

		/**
		* The standard XML tag without XML namespace for serializing this data object.
		*/
		DLL_IMPORT_OR_EXPORT static const char* XML_TAG;

		/**
		* Get the standard XML tag without XML namespace for serializing this data object.
		*/
		DLL_IMPORT_OR_EXPORT virtual std::string getXmlTag() const override { return XML_TAG; }

		/**
		* The standard XML namespace for serializing this data object.
		*/
		DLL_IMPORT_OR_EXPORT static const char* XML_NS;

		/**
		* Get the standard XML namespace for serializing this data object.
		*/
		DLL_IMPORT_OR_EXPORT std::string getXmlNamespace() const final { return XML_NS; }

	protected:
		WellboreFrameRepresentation() {}
	};
}
