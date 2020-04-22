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

#include "../resqml2/IjkGridNoGeometryRepresentation.h"

namespace RESQML2_2_NS
{
	/** @brief	An ijk grid no geometry representation. This class cannot be inherited. */
	class IjkGridNoGeometryRepresentation final : public RESQML2_NS::IjkGridNoGeometryRepresentation
	{
	public:

		IjkGridNoGeometryRepresentation(COMMON_NS::DataObjectRepository * repo,
			const std::string & guid, const std::string & title,
			unsigned int iCount, unsigned int jCount, unsigned int kCount) :
			RESQML2_NS::IjkGridNoGeometryRepresentation(repo, guid, title, iCount, jCount, kCount) {}

		IjkGridNoGeometryRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp,
			const std::string & guid, const std::string & title,
			unsigned int iCount, unsigned int jCount, unsigned int kCount) :
			RESQML2_NS::IjkGridNoGeometryRepresentation(interp, guid, title, iCount, jCount, kCount) {}

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		IjkGridNoGeometryRepresentation(gsoap_eml2_3::_resqml22__IjkGridRepresentation* fromGsoap) : RESQML2_NS::IjkGridNoGeometryRepresentation(fromGsoap) {}
		IjkGridNoGeometryRepresentation(gsoap_eml2_3::_resqml22__TruncatedIjkGridRepresentation* fromGsoap) : RESQML2_NS::IjkGridNoGeometryRepresentation(fromGsoap) {}

		/**
		* Destructor does nothing since the memory is managed by the gsoap context.
		*/
		virtual ~IjkGridNoGeometryRepresentation() {}

		COMMON_NS::DataObjectReference getHdfProxyDor() const final;
	};
}
