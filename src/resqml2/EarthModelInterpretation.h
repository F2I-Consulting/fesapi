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

/** . */
namespace RESQML2_NS
{
	class RockFluidOrganizationInterpretation;
	class StratigraphicColumn;
	class StratigraphicOccurrenceInterpretation;
	class StructuralOrganizationInterpretation;

	/** This class is a container for other organizations that are consistent to each others. */
	class EarthModelInterpretation : public AbstractFeatureInterpretation
	{
	public:

		/** Destructor does nothing since the memory is managed by the gsoap context. */
		virtual ~EarthModelInterpretation() {}

		 /**
		 * Structural
		 *
		 * @returns	The structural organization interpretation count.
		 */
		DLL_IMPORT_OR_EXPORT virtual unsigned int getStructuralOrganizationInterpretationCount() const = 0;

		/** A structural organization interpretationDOR. */
		DLL_IMPORT_OR_EXPORT virtual COMMON_NS::DataObjectReference getStructuralOrganizationInterpertationDor(unsigned int index) const = 0;

		/** A structural organization interpretation*. */
		DLL_IMPORT_OR_EXPORT StructuralOrganizationInterpretation* getStructuralOrganizationInterpertation(unsigned int index) const;

		/**
		 * Pushes back structural organization interpretation
		 *
		 * @param [in,out]	structOrganization	If non-null, the structure organization.
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
		 * Sets strati column
		 *
		 * @param [in,out]	stratiColumn	If non-null, the strati column.
		 */
		DLL_IMPORT_OR_EXPORT virtual void setStratiColumn(StratigraphicColumn * stratiColumn) = 0;

		/**
		 * Get the strati column DOR associated to this earth model interpretation. Throw an exception if
		 * there is no strati column associated. Check with hasStratiColumn().
		 */
		DLL_IMPORT_OR_EXPORT virtual COMMON_NS::DataObjectReference getStratiColumnDor() const = 0;

		/**
		 * Get the strati column associated to this earth model interpretation. Throw an exception if
		 * there is no strati column associated. Check with hasStratiColumn().
		 */
		DLL_IMPORT_OR_EXPORT StratigraphicColumn* getStratiColumn() const;

		/**
		 * Strati occurences
		 *
		 * @returns	The strati occurence count.
		 */
		DLL_IMPORT_OR_EXPORT virtual unsigned int getStratiOccurenceCount() const = 0;

		/** A stratigraphic occurrence interpretation DOR. */
		virtual COMMON_NS::DataObjectReference getStratiOccurenceDor(unsigned int index) const = 0;

		/** A stratigraphic occurrence interpretation. */
		DLL_IMPORT_OR_EXPORT StratigraphicOccurrenceInterpretation* getStratiOccurence(unsigned int index) const;

		/**
		 * Pushes back strati occurence
		 *
		 * @param [in,out]	stratiOccurence	If non-null, the strati occurence.
		 */
		DLL_IMPORT_OR_EXPORT virtual void pushBackStratiOccurence(StratigraphicOccurrenceInterpretation * stratiOccurence) = 0;

		/**
		 * Rock Fluid
		 *
		 * @returns	The Rock Fluid organization count.
		 */
		DLL_IMPORT_OR_EXPORT virtual unsigned int getRockFluidOrganizationInterpretationCount() const = 0;

		/**
		 * Pushes back rock fluid organization interpretation
		 *
		 * @param [in,out]	rockFluid	If non-null, the rock fluid.
		 */
		DLL_IMPORT_OR_EXPORT virtual void pushBackRockFluidOrganizationInterpretation(RockFluidOrganizationInterpretation* rockFluid) = 0;

		/** A rock fluid organization interpretation DOR. */
		virtual COMMON_NS::DataObjectReference getRockFluidOrganizationInterpretationDor(unsigned int index) const = 0;

		/** A rock fluid organization interpretation. */
		DLL_IMPORT_OR_EXPORT RockFluidOrganizationInterpretation* getRockFluidOrganizationInterpretation(unsigned int index) const;

		/**
		 * The standard XML tag without XML namespace for serializing this data object.
		 *
		 * @returns	The XML tag.
		 */
		DLL_IMPORT_OR_EXPORT static const char* XML_TAG;

		/**
		 * Get the standard XML tag without XML namespace for serializing this data object.
		 *
		 * @returns	The XML tag.
		 */
		DLL_IMPORT_OR_EXPORT virtual std::string getXmlTag() const { return XML_TAG; }

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
