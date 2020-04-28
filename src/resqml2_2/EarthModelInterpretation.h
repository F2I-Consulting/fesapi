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
		 * @returns	A DLL_IMPORT_OR_EXPORT.
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
		~EarthModelInterpretation() {}

		/**
		 * Structural
		 *
		 * @returns	The structural organization interpretation count.
		 */
		DLL_IMPORT_OR_EXPORT unsigned int getStructuralOrganizationInterpretationCount() const final;

		/** A structural organization interpretation*. */
		DLL_IMPORT_OR_EXPORT COMMON_NS::DataObjectReference getStructuralOrganizationInterpertationDor(unsigned int index) const final;

		/**
		 * Pushes back structural organization interpretation
		 *
		 * @param [in,out]	structOrganization	If non-null, the structure organization.
		 */
		DLL_IMPORT_OR_EXPORT void pushBackStructuralOrganizationInterpretation(RESQML2_NS::StructuralOrganizationInterpretation * structOrganization) final;

		//Strati column

		/**
		 * Check if a strati column is associated to this earth model interpretation
		 *
		 * @returns	True if a strati column is associated to this earth model interpretation elsa false.
		 */
		DLL_IMPORT_OR_EXPORT bool hasStratiColumn() const final;

		/**
		 * Sets strati column
		 *
		 * @param [in,out]	stratiColumn	If non-null, the strati column.
		 */
		DLL_IMPORT_OR_EXPORT void setStratiColumn(RESQML2_NS::StratigraphicColumn * stratiColumn) final;

		/**
		 * Get the strati column associated to this earth model interpretation. Throw an exception if
		 * there is no strati column associated. Check with hasStratiColumn().
		 */
		DLL_IMPORT_OR_EXPORT COMMON_NS::DataObjectReference getStratiColumnDor() const final;

		/**
		 * Strati occurrences
		 *
		 * @returns	The strati occurence count.
		 */
		DLL_IMPORT_OR_EXPORT unsigned int getStratiOccurrenceCount() const;

		/** A stratigraphic occurrence interpretation*. */
		DLL_IMPORT_OR_EXPORT COMMON_NS::DataObjectReference getStratiOccurrenceDor(unsigned int index) const final;

		/**
		 * Pushes a back strati occurrence
		 *
		 * @param [in,out]	stratiOccurrence	If non-null, the strati occurrence.
		 */
		DLL_IMPORT_OR_EXPORT void pushBackStratiOccurrence(RESQML2_NS::StratigraphicOccurrenceInterpretation * stratiOccurrence) final;

		/**
		 * Rock Fluid
		 *
		 * @returns	The Rock Fluid organization count.
		 */
		DLL_IMPORT_OR_EXPORT unsigned int getRockFluidOrganizationInterpretationCount() const final;

		/**
		 * Pushes back rock fluid organization interpretation
		 *
		 * @param [in,out]	rockFluid	If non-null, the rock fluid.
		 */
		DLL_IMPORT_OR_EXPORT void pushBackRockFluidOrganizationInterpretation(RESQML2_NS::RockFluidOrganizationInterpretation* rockFluid) final;

		/** A rock fluid organization interpretation*. */
		DLL_IMPORT_OR_EXPORT COMMON_NS::DataObjectReference getRockFluidOrganizationInterpretationDor(unsigned int index) const final;
	};
}
