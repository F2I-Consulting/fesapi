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

#include "AbstractTechnicalFeature.h"

namespace RESQML2_0_1_NS
{
	class SeismicLineFeature : public AbstractTechnicalFeature
	{
	public:

		/**
		* Only to be used in partial transfer context
		*/
		DLL_IMPORT_OR_EXPORT SeismicLineFeature(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : AbstractTechnicalFeature(partialObject) {}

		/**
		* Creates an instance of this class in a gsoap context.
		* @param repo					The repo where the underlying gsoap proxy is going to be created.
		* @param guid					The guid to set to this instance. If empty then a new guid will be generated.
		* @param title					A title for the instance to create.
		* @param traceIndexIncrement	The trace index increment.
		*								The trace index increment will be the difference in the trace number from abscissa i=0 and abscissa i=1.
		*								The increment can be a positive or negative integer, but not zero.
		* @param firstTraceIndex		The index of the first trace beginning at abscissa i=0.
		* @param traceCount				The count of traces in this seismic line.
		*/
		SeismicLineFeature(COMMON_NS::DataObjectRepository* repo, const std::string & guid, const std::string & title,
			int traceIndexIncrement, int firstTraceIndex, unsigned int traceCount);

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		SeismicLineFeature(gsoap_resqml2_0_1::_resqml20__SeismicLineFeature* fromGsoap): 
			AbstractTechnicalFeature(fromGsoap) {}

		/**
		* Destructor does nothing since the memory is manged by the gsoap context.
		*/
		~SeismicLineFeature() {}

		/**
		* Get the trace index increment between two consecutive traces.
		*/
		DLL_IMPORT_OR_EXPORT int getTraceIndexIncrement() const;
		
		/**
		* Get the first trace index.
		*/
		DLL_IMPORT_OR_EXPORT int getFirstTraceIndex() const;
		
		DLL_IMPORT_OR_EXPORT void setSeismicLineSet(class SeismicLineSetFeature * seisLineSet);

		DLL_IMPORT_OR_EXPORT class SeismicLineSetFeature* getSeismicLineSet() const;

		/**
		* Get the total count of traces in this seismic line.
		*/
		DLL_IMPORT_OR_EXPORT unsigned int getTraceCount() const;

		/**
		* The standard XML tag without XML namespace for serializing this data object.
		*/
		DLL_IMPORT_OR_EXPORT static const char* XML_TAG;

		/**
		* Get the standard XML tag without XML namespace for serializing this data object.
		*/
		DLL_IMPORT_OR_EXPORT virtual std::string getXmlTag() const { return XML_TAG; }

	private:
		void loadTargetRelationships();
	};
}
