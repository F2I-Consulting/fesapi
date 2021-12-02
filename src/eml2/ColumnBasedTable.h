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

#include "../common/AbstractObject.h"

namespace EML2_NS
{
	class PropertyKind;

	/** A column-based table allows the exchange of tables, where the values are arranged against columns that are defined by PropertyKind, UOM and Facet. */
	class ColumnBasedTable : public COMMON_NS::AbstractObject
	{
	public:
		/** Destructor does nothing since the memory is managed by the gsoap context. */
		virtual ~ColumnBasedTable() = default;
		
		/**
		 * Gets the row count of this table
		 */
		DLL_IMPORT_OR_EXPORT virtual uint64_t getRowCount() const = 0;

		/**
		 * Gets the column count of this table
		 */
		DLL_IMPORT_OR_EXPORT virtual uint64_t getColumnCount() const = 0;

		/**
		 * Gets the property kind DOR associated to a particular column count of this table
		 *
		 * @param columnIndex	The index of the column which we want the associated property kind DOR from
		 *
		 * @return				The associated property kind DOR.
		 */
		virtual COMMON_NS::DataObjectReference getPropertyKindDor(uint64_t columnIndex) const = 0;

		/**
		 * Gets the property kind associated to a particular column count of this table
		 *
		 * @param columnIndex	The index of the column which we want the associated property kind from
		 *
		 * @return				The associated property kind.
		 */
		DLL_IMPORT_OR_EXPORT class PropertyKind* getPropertyKind(uint64_t columnIndex) const;

		/**
		 * Gets the uom associated to a particular column count of this table
		 *
		 * @param columnIndex	The index of the column which we want the associated uom from
		 *
		 * @return				The associated uom. If no uom is provided or if Euc is provided, this method returns Euc.
		 */
		DLL_IMPORT_OR_EXPORT gsoap_eml2_3::eml23__UnitOfMeasure getUom(uint64_t columnIndex) const;

		/**
		 * Gets the uom associated to a particular column count of this table
		 *
		 * @param columnIndex	The index of the column which we want the associated uom from
		 *
		 * @return				The associated uom as string. If no uom is provided, this method returns an empty string.
		 */
		DLL_IMPORT_OR_EXPORT virtual std::string getUomAsString(uint64_t columnIndex) const = 0;

		/**
		 * Gets the value count per row for a particular column count of this table
		 *
		 * @param columnIndex	The index of the column which we want the associated uom from
		 *
		 * @return				The associated uom. If no uom is provided or if Euc is provided, this method returns Euc.
		 */
		DLL_IMPORT_OR_EXPORT virtual uint64_t getValueCountPerRow(uint64_t columnIndex) const = 0;

		/**
		 * Gets the datatype of a column
		 *
		 * @param columnIndex	The index of the column which we want the datatype from
		 *
		 * @return				The datatype which is used for values in this column
		 */
		DLL_IMPORT_OR_EXPORT virtual COMMON_NS::AbstractObject::hdfDatatypeEnum getDatatype(uint64_t columnIndex) const = 0;

		/**
		 * Gets the values of a column as string values
		 *
		 * @param columnIndex	The index of the column which we want the values from
		 *
		 * @return				The string values
		 */
		DLL_IMPORT_OR_EXPORT virtual std::vector<std::string> getStringValues(uint64_t columnIndex) const = 0;

		/**
		 * Sets the values of a column as XML string values
		 *
		 * @param columnIndex	The index of the column which we want to set the values
		 * @param values		The values to set
		 */
		DLL_IMPORT_OR_EXPORT virtual void setStringValues(uint64_t columnIndex, const std::vector<std::string> & values) = 0;

		/**
		 * Gets the values of a column as double values
		 *
		 * @param columnIndex	The index of the column which we want the values from
		 *
		 * @return				The double values
		 */
		DLL_IMPORT_OR_EXPORT virtual std::vector<double> getDoubleValues(uint64_t columnIndex) const = 0;

		/**
		 * Sets the values of a column as XML double values
		 *
		 * @param columnIndex	The index of the column which we want to set the values
		 * @param values		The values to set
		 */
		DLL_IMPORT_OR_EXPORT virtual void setDoubleValues(uint64_t columnIndex, const std::vector<double> & values) = 0;

		/**
		 * Gets the values of a column as int64 values
		 *
		 * @param columnIndex	The index of the column which we want the values from
		 *
		 * @return				The int64 values
		 */
		DLL_IMPORT_OR_EXPORT virtual std::vector<int64_t> getInt64Values(uint64_t columnIndex) const = 0;

		/**
		 * Sets the values of a column as XML int64 values
		 *
		 * @param columnIndex	The index of the column which we want to set the values
		 * @param values		The values to set
		 */
		DLL_IMPORT_OR_EXPORT virtual void setInt64Values(uint64_t columnIndex, const std::vector<int64_t> & values) = 0;

		/**
		* Pushes back a new column in this table and fill in its header
		*
		* @param isAKeyColumn		Indicate if the column to push back is a key one or not
		* @param propKind			The property kind associated to the value of this column
		* @param valueCountPerRow	The count of values in each row of this column
		*/
		DLL_IMPORT_OR_EXPORT virtual void pushBackColumnHeader(bool isAKeyColumn, PropertyKind* propKind, uint64_t valueCountPerRow = 1) = 0;

	protected:

		/** Default constructor does nothing */
		ColumnBasedTable() {}

		/**
		 * Only to be used in partial transfer context
		 *
		 * @param [in,out]	partialObject	If non-null, the partial object.
		 */
		DLL_IMPORT_OR_EXPORT ColumnBasedTable(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : COMMON_NS::AbstractObject(partialObject) {}

		/**
		 * Creates an instance of this class by wrapping a gsoap instance.
		 *
		 * @param [in,out]	fromGsoap	If non-null, from gsoap.
		 */
		ColumnBasedTable(gsoap_resqml2_0_1::_resqml20__StringTableLookup* fromGsoap) : COMMON_NS::AbstractObject(fromGsoap) {}

		/**
		 * Creates an instance of this class by wrapping a gsoap instance.
		 *
		 * @param [in,out]	fromGsoap	If non-null, from gsoap.
		 */
		ColumnBasedTable(gsoap_resqml2_0_1::_resqml20__DoubleTableLookup* fromGsoap) : COMMON_NS::AbstractObject(fromGsoap) {}

		/**
		 * Creates an instance of this class by wrapping a gsoap instance.
		 *
		 * @param [in,out]	fromGsoap	If non-null, from gsoap.
		 */
		ColumnBasedTable(gsoap_eml2_3::_eml23__ColumnBasedTable* fromGsoap) : COMMON_NS::AbstractObject(fromGsoap) {}
	};
}
