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

#include "AbstractValuesProperty.h"

#include <limits>

namespace RESQML2_NS
{
	/**
	 * @brief	Proxy class for a comment property. It is used to capture comments or annotations
	 * 			associated with a given element type in a data-object, for example, associating
	 * 			comments on the specific location of a well path.
	 */
	class CommentProperty : public AbstractValuesProperty
	{
	public:

		/** Destructor does nothing since the memory is managed by the gSOAP context. */
		virtual ~CommentProperty() = default;

		/**
		* Please use std::string pushBackRefToExistingDataset(EML2_NS::AbstractHdfProxy* hdfProxy, const std::string & datasetName = "") instead. Notice the lack of null value parameter.
		*/
		std::string pushBackRefToExistingIntegerDataset(EML2_NS::AbstractHdfProxy*, const std::string&, LONG64) final {
			throw std::logic_error("You cannot push back integer values in a Continuous Property.");
		}

		/**
		 * Adds an array of string values to the property values.
		 *
		 * @param 	  	values	All the property values to set ordered according the topology of the
		 * 						representation it is based on.
		 * @param [in]	proxy 	The HDF proxy where to write the property values. It must be already
		 * 						opened for writing and won't be closed in this method. If null then a
		 * 						default HDF proxy must be defined in the data object repository.
		 */
		DLL_IMPORT_OR_EXPORT void pushBackStringHdf5ArrayOfValues(const std::vector<std::string> & values, EML2_NS::AbstractHdfProxy* proxy);

		/**
		 * Pushes back a new patch of values for this property where the values have not to be written in
		 * the HDF5 file. The reason can be that the values already exist in an external file (only HDF5
		 * for now) or that the writing of the values in the external file is differed in time.
		 *
		 * @exception	std::invalid_argument	If @p hdfProxy is null.
		 *
		 * @param [in]	hdfProxy   	The HDF5 proxy where the values are already or will be stored. It
		 * 							cannot be null.
		 * @param 	  	datasetName	(Optional) If not provided during the method call, the dataset will
		 * 							be named the same as the dataset naming convention of fesapi:
		 * 							<tt>"/RESQML/" + prop-&gt;uuid + "/values_patch" + patchIndex</tt>
		 * @param 	  	nullValue  	(Optional) Not used for comment properties.
		 *
		 * @returns	The name of the HDF5 dataset.
		 */
		DLL_IMPORT_OR_EXPORT virtual std::string pushBackRefToExistingDataset(EML2_NS::AbstractHdfProxy* hdfProxy, const std::string & datasetName = "") = 0;

		/**
		 * Gets all the values of a given patch of this instance. Values are supposed to be string ones.
		 *
		 * @exception	std::out_of_range	If @p patchIndex is strictly greater than patch count.
		 *
		 * @param 	patchIndex	The index of the patch we want the values from.
		 *
		 * @returns	The string values of the patch.
		 */
		DLL_IMPORT_OR_EXPORT std::vector<std::string> getStringValuesOfPatch(unsigned int patchIndex);

		/** The standard XML tag without XML namespace for serializing this data object */
		DLL_IMPORT_OR_EXPORT static const char* XML_TAG;

		DLL_IMPORT_OR_EXPORT virtual std::string getXmlTag() const final { return XML_TAG; }

	protected:

		/**
		 * Only to be used in partial transfer context.
		 *
		 * @param [in]	partialObject	If non-null, the partial object.
		 */
		DLL_IMPORT_OR_EXPORT CommentProperty(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : AbstractValuesProperty(partialObject) {}

		CommentProperty() {}

		/**
		 * Creates an instance of this class by wrapping a gSOAP instance.
		 *
		 * @param [in]	fromGsoap	If non-null, the gSOAP instance.
		 */
		CommentProperty(gsoap_resqml2_0_1::_resqml20__CommentProperty* fromGsoap) : AbstractValuesProperty(fromGsoap) {}

		/**
		 * Creates an instance of this class by wrapping a gSoap RESQML2.2 instance.
		 *
		 * @param [in]	fromGsoap	If non-null, the gSOAP instance.
		 */
		CommentProperty(gsoap_eml2_3::_resqml22__CommentProperty* fromGsoap) : AbstractValuesProperty(fromGsoap) {}

		virtual EML2_NS::AbstractHdfProxy* getValuesHdfProxyAndDatasetPathOfPatch(unsigned int patchIndex, std::string & datasetPath) const = 0;
	};
}
