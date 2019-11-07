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

#include "../resqml2/TimeSeries.h"

namespace RESQML2_0_1_NS
{
	class TimeSeries : public RESQML2_NS::TimeSeries
	{
	public:
		/**
		* Only to be used in partial transfer context
		*/
		DLL_IMPORT_OR_EXPORT TimeSeries(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject):
			RESQML2_NS::TimeSeries(partialObject) {}

		/**
		* Creates a time series
		* @param repo							the repo where this intance will be stored.
		* @param guid							The guid to set to the local 3d crs. If empty then a new guid will be generated.
		* @param title							The title of the instance.
		*/
		TimeSeries(COMMON_NS::DataObjectRepository* repo, const std::string & guid, const std::string & title);
		 
		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		TimeSeries(gsoap_resqml2_0_1::_resqml20__TimeSeries* fromGsoap) : RESQML2_NS::TimeSeries(fromGsoap) {}

		/**
		* Destructor does nothing since the memory is managed by the gsoap context.
		*/
		~TimeSeries() {}

		/**
		* The standard XML namespace for serializing this data object.
		*/
		DLL_IMPORT_OR_EXPORT static const char* XML_NS;

		/**
		* Get the standard XML namespace for serializing this data object.
		*/
		DLL_IMPORT_OR_EXPORT virtual std::string getXmlNamespace() const { return XML_NS; }

	protected:		
		gsoap_resqml2_0_1::_resqml20__TimeSeries* getSpecializedGsoapProxy() const;
	};
}
