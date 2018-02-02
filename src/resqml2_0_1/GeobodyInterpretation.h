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

#include "resqml2_0_1/StratigraphicColumnRankInterpretation.h"

namespace resqml2_0_1
{
	class DLL_IMPORT_OR_EXPORT GeobodyInterpretation : public resqml2::AbstractFeatureInterpretation
	{
	public:

		/**
		* Only to be used in partial transfer context
		*/
		GeobodyInterpretation(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : resqml2::AbstractFeatureInterpretation(partialObject) {}

		/**
		* Creates an instance of this class in a gsoap context.
		* @param feature	The feature the instance interprets.
		* @param guid		The guid to set to the interpretation. If empty then a new guid will be generated.
		* @param title		A title for the instance to create.
		*/
		GeobodyInterpretation(class GeobodyFeature * feature, const std::string & guid, const std::string & title);

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		GeobodyInterpretation(gsoap_resqml2_0_1::_resqml2__GeobodyInterpretation* fromGsoap) : resqml2::AbstractFeatureInterpretation(fromGsoap) {}

		/**
		* Destructor does nothing since the memory is managed by the gsoap context.
		*/
		~GeobodyInterpretation() {}

		/**
		* Set the geobody 3d shape
		*/
		void set3dShape(gsoap_resqml2_0_1::resqml2__Geobody3dShape geobody3dShape);

		/**
		* check if the 3d shape of this geobody is known
		*/
		bool has3dShape() const;

		/**
		* get the 3d shape of this geobody
		*/
		gsoap_resqml2_0_1::resqml2__Geobody3dShape get3dShape() const;
			
		static const char* XML_TAG;
		virtual std::string getXmlTag() const {return XML_TAG;}
	};
}

