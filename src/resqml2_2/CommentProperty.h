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

#include "../resqml2/CommentProperty.h"

#include <limits>

namespace RESQML2_2_NS
{
	/** Proxy class for a comment property. */
	class CommentProperty final : public RESQML2_NS::CommentProperty
	{
	public:

		/**
		 * Only to be used in partial transfer context.
		 *
		 * @param [in]	partialObject	If non-null, the partial object.
		 */
		DLL_IMPORT_OR_EXPORT CommentProperty(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : RESQML2_NS::CommentProperty(partialObject) {}

		/**
		 * Creates a comment property which is of a local property kind.
		 *
		 * @exception	std::invalid_argument	If @p rep or @p propKind is null.. If @p dimension is zero.
		 *
		 * @param [in]	rep			  	The representation on which this property is attached to. It
		 * 								cannot be null.
		 * @param 	  	guid		  	The guid to set to the property. If empty then a new guid will be
		 * 								generated.
		 * @param 	  	title		  	The title to set to the property. If empty then \"unknown\" title
		 * 								will be set.
		 * @param 	  	dimension	  	The dimension of each value of this property. Dimension is 1 for
		 * 								a scalar property.
		 * @param 	  	attachmentKind	The topological element on which the property values are attached
		 * 								to.
		 * @param [in]	propKind		The property kind of these property values. It cannot be null.
		 */
		CommentProperty(RESQML2_NS::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			unsigned int dimension, gsoap_eml2_3::resqml22__IndexableElement attachmentKind, EML2_NS::PropertyKind * propKind);

		/**
		 * Creates an instance of this class by wrapping a gSOAP instance.
		 *
		 * @param [in]	fromGsoap	If non-null, the gSOAP instance.
		 */
		CommentProperty(gsoap_eml2_3::_resqml22__CommentProperty* fromGsoap): RESQML2_NS::CommentProperty(fromGsoap) {}

		/** Destructor does nothing since the memory is managed by the gsoap context. */
		~CommentProperty() {}

		DLL_IMPORT_OR_EXPORT std::string pushBackRefToExistingDataset(EML2_NS::AbstractHdfProxy* hdfProxy, const std::string & datasetName = "") final;

		bool validatePropertyKindAssociation(EML2_NS::PropertyKind*) final { return true; }

		bool validatePropertyKindAssociation(gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind) final { return true; }

		/**
		* The standard XML namespace for serializing this data object.
		*/
		DLL_IMPORT_OR_EXPORT static const char* XML_NS;

		/**
		* Get the standard XML namespace for serializing this data object.
		*/
		DLL_IMPORT_OR_EXPORT std::string getXmlNamespace() const final { return XML_NS; }

	private:
		EML2_NS::AbstractHdfProxy* getValuesHdfProxyAndDatasetPathOfPatch(unsigned int patchIndex, std::string & datasetPath) const final;
	};
}
