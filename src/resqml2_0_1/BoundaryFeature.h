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

#include "resqml2_0_1/AbstractGeologicFeature.h"
#include "resqml2_0_1/RockFluidUnitFeature.h"

namespace RESQML2_0_1_NS
{
	class BoundaryFeature : public AbstractGeologicFeature
	{
	public:

		/**
		* Only to be used in partial transfer context
		*/
		BoundaryFeature(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : AbstractGeologicFeature(partialObject) {}

		/**
		* Default constructor
		* Set the gsoap proxy to nullptr from superclass constructor
		*/
		BoundaryFeature() {}

		/**
		* Creates an instance of this class in a gsoap context.
		* @param soapContext	The soap context where the underlying gsoap proxy is going to be created.
		* @param guid			The guid to set to the boundary horizon. If empty then a new guid will be generated.
		* @param title			A title for the instance to create.
		*/
		BoundaryFeature(soap* soapContext, const std::string & guid, const std::string & title);

		BoundaryFeature(gsoap_resqml2_0_1::_resqml2__BoundaryFeature* fromGsoap): AbstractGeologicFeature(fromGsoap) {}
		virtual ~BoundaryFeature() {}

		DLL_IMPORT_OR_EXPORT static const char* XML_TAG;
		DLL_IMPORT_OR_EXPORT virtual std::string getXmlTag() const {return XML_TAG;}

	private:
		std::vector<epc::Relationship> getAllEpcRelationships() const;

		// backward relationship
		std::vector<RockFluidUnitFeature*> topOfRockFluidUnitFeatureSet;
		std::vector<RockFluidUnitFeature*> btmOfRockFluidUnitFeatureSet;

		friend void RockFluidUnitFeature::setTop(BoundaryFeature* top);
		friend void RockFluidUnitFeature::setBottom(BoundaryFeature* bottom);
	};
}

