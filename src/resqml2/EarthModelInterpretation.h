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

#include "AbstractFeatureInterpretation.h"

/** @brief */
namespace RESQML2_NS
{
	class RockFluidOrganizationInterpretation;
	class StratigraphicColumn;
	class StratigraphicOccurrenceInterpretation;
	class StructuralOrganizationInterpretation;

	/**
	 * This class is a container for stratigraphic, structural and rock fluid organization interpretations that are consistent to each others.
	 * 
	 * BUSINESS RULE: An earth model Interpretation interprets only an earth model feature.
	 */
	class EarthModelInterpretation : public AbstractFeatureInterpretation
	{
	public:

		/** Destructor does nothing since the memory is managed by the gSOAP context. */
		virtual ~EarthModelInterpretation() {}

		 /**
		 * Get the count of structural organization interpretations associated to this earth model interpretation.
		 *
		 * @returns	The count of associated structural organization interpretations.
		 */
		DLL_IMPORT_OR_EXPORT virtual unsigned int getStructuralOrganizationInterpretationCount() const = 0;

		/**
		 * Gets the DOR of a given associated structural organization interpretation.
		 *
		 * @exception	std::out_of_range	If <tt>index &gt;=
		 * 									getStructuralOrganizationInterpretationCount()</tt>.
		 *
		 * @param 	index	Zero-based index of the associated structural organization interpretation we
		 * 					look for the DOR.
		 *
		 * @returns	The DOR of the structural organization interpretation at position @p index.
		 */
		DLL_IMPORT_OR_EXPORT virtual COMMON_NS::DataObjectReference getStructuralOrganizationInterpertationDor(unsigned int index) const = 0;

		/**
		 * Gets a given associated structural organization interpretation.
		 *
		 * @exception	std::out_of_range	If <tt>index &gt;=
		 * 									getStructuralOrganizationInterpretationCount()</tt>.
		 *
		 * @param 	index	Zero-based index of the associated structural organization interpretation we
		 * 					look for.
		 *
		 * @returns	The structural organization interpretation at position @p index.
		 */
		DLL_IMPORT_OR_EXPORT StructuralOrganizationInterpretation* getStructuralOrganizationInterpertation(unsigned int index) const;

		/**
		 * Pushes back a structural organization interpretation.
		 *
		 * @exception	std::invalid_argument	If <tt>structOrganization == nullptr</tt>.
		 *
		 * @param [in]	structOrganization	The structural organization interpretation to push back.
		 */
		DLL_IMPORT_OR_EXPORT virtual void pushBackStructuralOrganizationInterpretation(StructuralOrganizationInterpretation * structOrganization) = 0;

		//Strati column

		/**
		 * Check if a strati column is associated to this earth model interpretation
		 *
		 * @returns	True if a strati column is associated to this earth model interpretation elsa false.
		 */
		DLL_IMPORT_OR_EXPORT virtual bool hasStratiColumn() const = 0;

		/**
		 * Sets the stratigraphic column.
		 *
		 * @exception	std::invalid_argument	If <tt>stratiColumn == nullptr</tt>.
		 *
		 * @param [in]	stratiColumn	The stratigraphic column to set.
		 */
		DLL_IMPORT_OR_EXPORT virtual void setStratiColumn(StratigraphicColumn * stratiColumn) = 0;

		/**
		 * Gets the DOR of the stratigraphic column associated to this earth model interpretation.
		 *
		 * @returns	The DOR of the stratigraphic column associated to this earth model interpretation if
		 * 			it exists, else empty DOR.
		 */
		DLL_IMPORT_OR_EXPORT virtual COMMON_NS::DataObjectReference getStratiColumnDor() const = 0;

		/**
		 * Gets the stratigraphic column associated to this earth model interpretation.
		 *
		 * @returns	The stratigraphic column associated to this earth model interpretation if it exists,
		 * 			else @c nullptr.
		 */
		DLL_IMPORT_OR_EXPORT StratigraphicColumn* getStratiColumn() const;

		/**
		 * Get the count of stratigraphic occurrence interpretations associated to this earth model
		 * interpretation.
		 *
		 * @exception	std::range_error	If the count of stratigraphic occurrence interpretations is
		 * 									strictly greater than unsigned int max.
		 *
		 * @returns	The count of associated stratigraphic occurrence interpretations.
		 */
		DLL_IMPORT_OR_EXPORT virtual unsigned int getStratiOccurenceCount() const = 0;

		/**
		 * Gets the DOR of a given associated stratigraphic occurrence interpretation.
		 *
		 * @exception	std::out_of_range	If <tt>index &gt;= getStratiOccurrenceCount()</tt>.
		 *
		 * @param 	index	Zero-based index of the associated stratigraphic occurrence interpretation we
		 * 					look for the DOR.
		 *
		 * @returns	The DOR of the stratigraphic occurrence interpretation at position @p index.
		 */
		virtual COMMON_NS::DataObjectReference getStratiOccurenceDor(unsigned int index) const = 0;

		/**
		 * Gets a given associated stratigraphic occurrence interpretation.
		 *
		 * @exception	std::out_of_range	If <tt>index &gt;= getStratiOccurrenceCount()</tt>.
		 *
		 * @param 	index	Zero-based index of the associated stratigraphic occurrence interpretation we
		 * 					look for.
		 *
		 * @returns	The stratigraphic occurrence interpretation at position @p index.
		 */
		DLL_IMPORT_OR_EXPORT StratigraphicOccurrenceInterpretation* getStratiOccurence(unsigned int index) const;

		/**
		 * @brief	Pushes back a stratigraphic occurrence interpretation.
		 *
		 * @exception	std::invalid_argument	If <tt>stratiOccurrence == nullptr</tt>.
		 *
		 * @param [in]	stratiOccurence	The stratigraphic occurrence interpretation to push back.
		 */
		DLL_IMPORT_OR_EXPORT virtual void pushBackStratiOccurence(StratigraphicOccurrenceInterpretation * stratiOccurence) = 0;

		 /**
		  * Get the count of rock fluid organization interpretations associated to this earth model
		  * interpretation.
		  *
		  * @returns	The count of associated rock fluid organization interpretations.
		  */
		DLL_IMPORT_OR_EXPORT virtual unsigned int getRockFluidOrganizationInterpretationCount() const = 0;

		 /**
		  * Pushes back a rock fluid organization interpretation.
		  *
		  * @exception	std::invalid_argument	If <tt>rockFluid == nullptr</tt>.
		  *
		  * @param [in]	rockFluid	The rock fluid organization interpretation to push back.
		  */
		DLL_IMPORT_OR_EXPORT virtual void pushBackRockFluidOrganizationInterpretation(RockFluidOrganizationInterpretation* rockFluid) = 0;

		/**
		 * Gets the DOR of a given associated rock fluid organization interpretation.
		 *
		 * @exception	std::out_of_range	If <tt>index &gt;=
		 * 									getRockFluidOrganizationInterpretationCount()</tt>.
		 *
		 * @param 	index	Zero-based index of the associated rock fluid organization interpretation we
		 * 					look for the DOR.
		 *
		 * @returns	The DOR of the rock fluid organization interpretation at position @p index.
		 */
		virtual COMMON_NS::DataObjectReference getRockFluidOrganizationInterpretationDor(unsigned int index) const = 0;

		/**
		 * Gets a given associated rock fluid organization interpretation.
		 *
		 * @exception	std::out_of_range	If <tt>index &gt;=
		 * 									getRockFluidOrganizationInterpretationCount()</tt>.
		 *
		 * @param 	index	Zero-based index of the associated rock fluid organization interpretation we
		 * 					look for.
		 *
		 * @returns	The rock fluid organization interpretation at position @p index.
		 */
		DLL_IMPORT_OR_EXPORT RockFluidOrganizationInterpretation* getRockFluidOrganizationInterpretation(unsigned int index) const;

		/** The standard XML tag without XML namespace for serializing this data object. */
		DLL_IMPORT_OR_EXPORT static const char* XML_TAG;

		DLL_IMPORT_OR_EXPORT virtual std::string getXmlTag() const override { return XML_TAG; }

    protected:

		/**
		 * Only to be used in partial transfer context
		 *
		 * @param [in,out]	partialObject	If non-null, the partial object.
		 *
		 * @returns	A DLL_IMPORT_OR_EXPORT.
		 */
		DLL_IMPORT_OR_EXPORT EarthModelInterpretation(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : AbstractFeatureInterpretation(partialObject) {}

		/**
		 * Default constructor
		 */
		EarthModelInterpretation() {}

		/**
		 * Creates an instance of this class by wrapping a gsoap instance.
		 *
		 * @param [in,out]	fromGsoap	If non-null, from gsoap.
		 */
		EarthModelInterpretation(gsoap_resqml2_0_1::_resqml20__EarthModelInterpretation* fromGsoap) : AbstractFeatureInterpretation(fromGsoap) {}

		/**
		 * Creates an instance of this class by wrapping a gsoap instance.
		 *
		 * @param [in,out]	fromGsoap	If non-null, from gsoap.
		 */
		EarthModelInterpretation(gsoap_eml2_3::_resqml22__EarthModelInterpretation* fromGsoap) : AbstractFeatureInterpretation(fromGsoap) {}

		/** Loads target relationships */
		void loadTargetRelationships();
	};
}
