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

#include "../eml2/ColumnBasedTable.h"

namespace RESQML2_0_1_NS
{
	/** A double table lookup. */
	class DoubleTableLookup final : public EML2_NS::ColumnBasedTable
	{
	public:

		/**
		 * Only to be used in partial transfer context
		 *
		 * @param [in,out]	partialObject	If non-null, the partial object.
		 *
		 * 
		 */
		DLL_IMPORT_OR_EXPORT DoubleTableLookup(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : EML2_NS::ColumnBasedTable(partialObject) {}

		/**
		 * Creates an instance of this class in a gsoap context.
		 *
		 * @param [in,out]	repo 	A repo which will manage the memory of this instance.
		 * @param 		  	guid 	The guid to set to this instance. If empty then a new guid will be
		 * 							generated.
		 * @param 		  	title	A title for the instance to create.
		 */
		DoubleTableLookup(COMMON_NS::DataObjectRepository* repo, const std::string & guid, const std::string & title);

		/**
		 * Creates an instance of this class by wrapping a gsoap instance.
		 *
		 * @param [in,out]	fromGsoap	If non-null, from gsoap.
		 */
		DoubleTableLookup(gsoap_resqml2_0_1::_resqml20__DoubleTableLookup* fromGsoap) : EML2_NS::ColumnBasedTable(fromGsoap) {}

		/** Destructor does nothing since the memory is managed by the gsoap context. */
		~DoubleTableLookup() = default;

		/**
		 * Gets the row count of this table
		 */
		DLL_IMPORT_OR_EXPORT uint64_t getRowCount() const final;

		/**
		 * Gets the column count of this table
		 */
		DLL_IMPORT_OR_EXPORT uint64_t getColumnCount() const final { return 2; }

		/**
		 * Gets the property kind DOR associated to a particular column count of this table
		 *
		 * @param columnIndex	The index of the column which we want the associated property kind DOR from
		 *
		 * @return				The associated property kind DOR.
		 */
		DLL_IMPORT_OR_EXPORT COMMON_NS::DataObjectReference getPropertyKindDor(uint64_t columnIndex) const final;

		/**
		 * @return				Empty since DoubleTableLookup has not got any uom never
		 */
		DLL_IMPORT_OR_EXPORT std::string getUomAsString(uint64_t) const final { return ""; }

		/**
		 * @return				1 since DoubleTableLookup has only one value per column
		 */
		DLL_IMPORT_OR_EXPORT uint64_t getValueCountPerRow(uint64_t) const final { return 1; }

		/**
		 * @return				A double table lookkup only contains double by definition
		 */
		DLL_IMPORT_OR_EXPORT COMMON_NS::AbstractObject::hdfDatatypeEnum getDatatype(uint64_t) const final
		{
			return COMMON_NS::AbstractObject::hdfDatatypeEnum::DOUBLE;
		}

		/**
		 * Not supported in v2.0.1
		 */
		DLL_IMPORT_OR_EXPORT std::vector<std::string> getStringValues(uint64_t) const final
			{ throw std::logic_error("The column does not contain string values"); }

		/**
		 * Not supported in v2.0.1
		 */
		DLL_IMPORT_OR_EXPORT void setStringValues(uint64_t, const std::vector<std::string>&) final
			{ throw std::logic_error("The column does not contain string values"); }

		/**
		 * Gets the values of a column as double values
		 *
		 * @param columnIndex	The index of the column which we want the values from
		 *
		 * @return				The double values
		 */
		DLL_IMPORT_OR_EXPORT std::vector<double> getDoubleValues(uint64_t columnIndex) const final;

		/**
		 * Sets the values of a column as XML double values
		 *
		 * @param columnIndex	The index of the column which we want to set the values. Can only be zero or one.
		 * @param values		The values to set
		 */
		DLL_IMPORT_OR_EXPORT void setDoubleValues(uint64_t columnIndex, const std::vector<double>& values) final;

		/**
		 * Not supported in v2.0.1
		 */
		DLL_IMPORT_OR_EXPORT std::vector<int64_t> getInt64Values(uint64_t) const final
			{ throw std::logic_error("The column does not contain integer values"); }

		/**
		 * Not supported in v2.0.1
		 */
		DLL_IMPORT_OR_EXPORT void setInt64Values(uint64_t, const std::vector<int64_t>&) final
			{ throw std::logic_error("The column does not contain integer values"); }

		DLL_IMPORT_OR_EXPORT void pushBackColumnHeader(bool, EML2_NS::PropertyKind*, uint64_t = 1) final
			{ throw std::logic_error("You cannot push back new column to a double table lookup."); }

		/** The standard XML tag without XML namespace for serializing this data object. */
		DLL_IMPORT_OR_EXPORT static const char* XML_TAG;

		DLL_IMPORT_OR_EXPORT virtual std::string getXmlTag() const final { return XML_TAG; }

		/**
		* The standard XML namespace for serializing this data object.
		*/
		DLL_IMPORT_OR_EXPORT static const char* XML_NS;

		/**
		* Get the standard XML namespace for serializing this data object.
		*/
		DLL_IMPORT_OR_EXPORT std::string getXmlNamespace() const final { return XML_NS; }

	private:
		/**
		*Does nothing since this class has no forward relationship
		*/
		void loadTargetRelationships() final {}
	};
}
