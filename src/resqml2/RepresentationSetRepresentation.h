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

#include "AbstractRepresentation.h"

namespace RESQML2_NS
{
	/**
	 * @brief	Proxy class for a representation set representation. This is the parent class of the
	 * 			framework representations. It is used to group together individual representations to
	 * 			represent a "bag" of representations.
	 * 			
	 * 			If the individual representations are all of the same type, then you can indicate
	 * 			that the set is homogenous. These "bags" do not imply any geologic consistency. For
	 * 			example, you can define a set of wellbore frames, a set of wellbore trajectories, a
	 * 			set of blocked wellbores. Because the framework representations inherit from this
	 * 			class, they inherit the capability to gather individual representations into sealed
	 * 			and non-sealed surface framework representations, or sealed volume framework
	 * 			representations.
	 */
	class RepresentationSetRepresentation : public RESQML2_NS::AbstractRepresentation
	{
	public:

		/** Destructor does nothing since the memory is managed by the gsoap context. */
		virtual ~RepresentationSetRepresentation() = default;

		/**
		 * Gets the data object reference of the HDF proxy which is used for storing the numerical
		 * values of this representation (i.e. its geometry).
		 *
		 * @returns	Empty data object reference since no geometry is directly associated to a
		 * 			representation set representation.
		 */
		COMMON_NS::DataObjectReference getHdfProxyDor() const final { return COMMON_NS::DataObjectReference(); }

		/** Please do note use: not implemented yet. */ 
		DLL_IMPORT_OR_EXPORT uint64_t getXyzPointCountOfPatch(uint64_t patchIndex) const override;

		/** Please do note use: not implemented yet. */
		DLL_IMPORT_OR_EXPORT void getXyzPointsOfPatch(uint64_t patchIndex, double * xyzPoints) const override;

		/**
		 * Gets the patch count.
		 *
		 * @returns 1 since we consider that representation set representations have only 1 patch.
		 */
		DLL_IMPORT_OR_EXPORT uint64_t getPatchCount() const override {return 1;}

		/**
		 * Checks if this representation set contains only one type of representations (homogeneous) or
		 * several. This methods only read the @c IsHomogeneous attribute.
		 *
		 * @exception	std::logic_error	If the underlying gSOAP instance is not a RESQML2.0 one.
		 *
		 * @returns	True if this representation set is homogeneous, false if not.
		 */
		DLL_IMPORT_OR_EXPORT bool isHomogeneous() const;

		/**
		 * Gets the count of representations in this representation set.
		 *
		 * @exception	std::logic_error	If the underlying gSOAP instance is not a RESQML2.0 one.
		 * @exception	std::range_error	If the count is strictly greater than unsigned int max. 
		 *
		 * @returns	The representation count.
		 */
		DLL_IMPORT_OR_EXPORT uint64_t getRepresentationCount() const;

		/**
		 * Gets a particular representation in this representation set according to its position.
		 *
		 * @exception	std::logic_error	If the underlying gSOAP instance is not a RESQML2.0 one.
		 * @exception	std::out_of_range	If @p index is out of range.									
		 *
		 * @param 	index	Zero-based index of the of the representation we look for.
		 *
		 * @returns	A pointer to the representation at position @p index.
		 */
		DLL_IMPORT_OR_EXPORT RESQML2_NS::AbstractRepresentation* getRepresentation(uint64_t index) const;

		/**
		 * Gets the data object reference of a particular representation in this representation set
		 * according to its position.
		 *
		 * @exception	std::logic_error 	If the underlying gSOAP instance is not a RESQML2.0 one.
		 * @exception	std::out_of_range	If @p index is out of range.
		 *
		 * @param 	index	Zero-based index of the of the representation we look for.
		 *
		 * @returns	The data object reference of the representation at position @p index.
		 */
		COMMON_NS::DataObjectReference getRepresentationDor(uint64_t index) const;

		/**
		 * Pushes back a representation into this representation set. The value of the @c
		 * IsHomogeneous attribute is updated if required (see {@link isHomogeneous}).
		 *
		 * @exception	std::invalid_argument	If @p rep is nullptr.
		 * @exception	std::logic_error	 	If the underlying gSOAP instance is not a RESQML2.0 one.
		 *
		 * @param [in]	rep	The representation to push in this representation set.
		 */
		DLL_IMPORT_OR_EXPORT void pushBack(RESQML2_NS::AbstractRepresentation* rep);

		/**
		 * The standard XML tag without XML namespace for serializing this data object.
		 *
		 * @returns	The XML tag.
		 */
		DLL_IMPORT_OR_EXPORT static constexpr char const* XML_TAG = "RepresentationSetRepresentation";

		DLL_IMPORT_OR_EXPORT virtual std::string getXmlTag() const override { return XML_TAG; }

		/** Loads target relationships */
		void virtual loadTargetRelationships() override;

    protected:

		/** Default constructor */
		RepresentationSetRepresentation() {}

		/**
		 * Only to be used in partial transfer context.
		 *
		 * @param [in]	partialObject	If non-nullptr, the partial object.
		 */
		DLL_IMPORT_OR_EXPORT RepresentationSetRepresentation(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) :
			RESQML2_NS::AbstractRepresentation(partialObject) {}

		/**
		 * Creates an instance of this class by wrapping a gsoap instance.
		 *
		 * @param [in,out]	fromGsoap	If non-null, from gsoap.
		 */
		RepresentationSetRepresentation(gsoap_resqml2_0_1::_resqml20__RepresentationSetRepresentation* fromGsoap) : RESQML2_NS::AbstractRepresentation(fromGsoap) {}

		/**
		 * Creates an instance of this class by wrapping a gsoap instance.
		 *
		 * @param [in,out]	fromGsoap	If non-null, from gsoap.
		 */
		RepresentationSetRepresentation(gsoap_eml2_3::_resqml22__RepresentationSetRepresentation* fromGsoap) : RESQML2_NS::AbstractRepresentation(fromGsoap) {}

	};
}
