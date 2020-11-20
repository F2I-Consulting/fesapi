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

#include "../resqml2/EarthModelInterpretation.h"

namespace RESQML2_2_NS
{
	/** This class is a container for other organizations that are consistent to each others. */
	class EarthModelInterpretation final : public RESQML2_NS::EarthModelInterpretation
	{
	public:

		/**
		 * Only to be used in partial transfer context
		 *
		 * @param [in,out]	partialObject	If non-null, the partial object.
		 *
		 * 
		 */
		DLL_IMPORT_OR_EXPORT EarthModelInterpretation(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : RESQML2_NS::EarthModelInterpretation(partialObject) {}

		/**
		 * @brief	Creates an instance of this class in a gsoap context.
		 *
		 * @exception	std::invalid_argument	If <tt>orgFeat == nullptr</tt>.
		 *
		 * @param [in]	orgFeat	The feature the instance interprets.
		 * @param 	  	guid   	The guid to set to the interpretation. If empty then a new guid will be
		 * 						generated.
		 * @param 	  	title  	A title for the instance to create.
		 */
		EarthModelInterpretation(RESQML2_NS::Model * orgFeat, const std::string & guid, const std::string & title);

		/**
		 * Creates an instance of this class by wrapping a gsoap instance.
		 *
		 * @param [in,out]	fromGsoap	If non-null, from gsoap.
		 */
		EarthModelInterpretation(gsoap_eml2_3::_resqml22__EarthModelInterpretation* fromGsoap) : RESQML2_NS::EarthModelInterpretation(fromGsoap) {}

		/** Destructor does nothing since the memory is managed by the gsoap context. */
		~EarthModelInterpretation() = default;

		DLL_IMPORT_OR_EXPORT unsigned int getStructuralOrganizationInterpretationCount() const final;

		DLL_IMPORT_OR_EXPORT COMMON_NS::DataObjectReference getStructuralOrganizationInterpertationDor(unsigned int index) const final;

		DLL_IMPORT_OR_EXPORT void pushBackStructuralOrganizationInterpretation(RESQML2_NS::StructuralOrganizationInterpretation * structOrganization) final;

		//Strati column

		DLL_IMPORT_OR_EXPORT bool hasStratiColumn() const final;

		DLL_IMPORT_OR_EXPORT void setStratiColumn(RESQML2_NS::StratigraphicColumn * stratiColumn) final;

		DLL_IMPORT_OR_EXPORT COMMON_NS::DataObjectReference getStratiColumnDor() const final;

		DLL_IMPORT_OR_EXPORT unsigned int getStratiOccurrenceCount() const;

		DLL_IMPORT_OR_EXPORT COMMON_NS::DataObjectReference getStratiOccurrenceDor(unsigned int index) const final;

		DLL_IMPORT_OR_EXPORT void pushBackStratiOccurrence(RESQML2_NS::StratigraphicOccurrenceInterpretation * stratiOccurrence) final;

		DLL_IMPORT_OR_EXPORT unsigned int getRockFluidOrganizationInterpretationCount() const final;

		DLL_IMPORT_OR_EXPORT void pushBackRockFluidOrganizationInterpretation(RESQML2_NS::RockFluidOrganizationInterpretation* rockFluid) final;

		DLL_IMPORT_OR_EXPORT COMMON_NS::DataObjectReference getRockFluidOrganizationInterpretationDor(unsigned int index) const final;

		/**
		* The standard XML namespace for serializing this data object.
		*/
		DLL_IMPORT_OR_EXPORT static const char* XML_NS;

		/**
		* Get the standard XML namespace for serializing this data object.
		*/
		DLL_IMPORT_OR_EXPORT std::string getXmlNamespace() const final { return XML_NS; }
	};
}
