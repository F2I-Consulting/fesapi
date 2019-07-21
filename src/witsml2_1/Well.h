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

#include "witsml2_1/Wellbore.h"

namespace WITSML2_1_NS
{
	class Well : public WITSML2_1_NS::AbstractObject
	{
	public:
		/**
		* Creates an instance of this class in a gsoap context.
		* @param repo	The repo where the underlying gsoap proxy is going to be created.
		* @param guid	The guid to set to this instance. If empty then a new guid will be generated.
		*/
		Well(COMMON_NS::DataObjectRepository * repo,
			const std::string & guid,
			const std::string & title);

		Well(COMMON_NS::DataObjectRepository * repo,
			const std::string & guid,
			const std::string & title,
			const std::string & operator_,
			gsoap_eml2_2::eml22__WellStatus statusWell,
			gsoap_eml2_2::witsml2__WellPurpose purposeWell,
			gsoap_eml2_2::witsml2__WellFluid fluidWell,
			gsoap_eml2_2::witsml2__WellDirection directionWell
		);

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		Well(gsoap_eml2_2::witsml2__Well* fromGsoap):AbstractObject(fromGsoap)  {}

		/**
		* Destructor does nothing since the memory is managed by the gsoap context.
		*/
		~Well() {}

		DLL_IMPORT_OR_EXPORT void setOperator(const std::string & operator_);

		DLL_IMPORT_OR_EXPORT double getLocationProjectedX(const unsigned int & locationIndex);
		DLL_IMPORT_OR_EXPORT double getLocationProjectedY(const unsigned int & locationIndex);

		DLL_IMPORT_OR_EXPORT void pushBackLocation(
			const std::string & guid,
			const double & projectedX,
			const double & projectedY,
			const unsigned int & projectedCrsEpsgCode);

		DLL_IMPORT_OR_EXPORT unsigned int geLocationCount() const;
		
		void pushBackDatum(
			const std::string & guid, 
			const std::string & title,
			gsoap_eml2_2::eml22__WellboreDatumReference code,
			const std::string & datum,
			gsoap_eml2_2::eml22__LengthUom elevationUnit,
			const double & elevation,
			const unsigned int & verticalCrsEpsgCode);

		DLL_IMPORT_OR_EXPORT unsigned int getDatumCount() const;

		static const char* XML_TAG;
		virtual std::string getXmlTag() const {return XML_TAG;}

	private:
		void loadTargetRelationships() {}
	};
}
