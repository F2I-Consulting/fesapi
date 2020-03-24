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

#include "AbstractFeature.h"

namespace RESQML2_NS
{
	class AbstractTechnicalFeature : public AbstractFeature
	{
	protected:

		/**
		* Only to be used in partial transfer context
		*/
		DLL_IMPORT_OR_EXPORT AbstractTechnicalFeature(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : AbstractFeature(partialObject) {}

		/**
		* Default constructor
		* Set the gsoap proxy to nullptr from superclass constructor
		*/
		AbstractTechnicalFeature() {}

		AbstractTechnicalFeature(gsoap_resqml2_0_1::resqml20__AbstractTechnicalFeature* fromGsoap) : AbstractFeature(fromGsoap) {}
		AbstractTechnicalFeature(gsoap_eml2_3::resqml22__AbstractTechnicalFeature* fromGsoap) : AbstractFeature(fromGsoap) {}

	public:
		virtual ~AbstractTechnicalFeature() {}
	};
}
