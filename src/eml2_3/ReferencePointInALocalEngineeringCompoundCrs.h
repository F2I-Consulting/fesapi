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

#include "../eml2/ReferencePointInALocalEngineeringCompoundCrs.h"

namespace EML2_3_NS
{
	/** A md datum. */
	class ReferencePointInALocalEngineeringCompoundCrs final : public EML2_NS::ReferencePointInALocalEngineeringCompoundCrs
	{
	public:

		/**
		 * Only to be used in partial transfer context
		 *
		 * @param [in,out]	partialObject	If non-null, the partial object.
		 *
		 * 
		 */
		DLL_IMPORT_OR_EXPORT ReferencePointInALocalEngineeringCompoundCrs(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : EML2_NS::ReferencePointInALocalEngineeringCompoundCrs(partialObject) {}

		/**
		 * Creates an instance of this class in a gsoap context.
		 *
		 * @param [in,out]	repo					 	The repo where the underlying gsoap proxy is
		 * 												going to be created.
		 * @param 		  	guid					 	The guid to set to the local 3d crs. If empty
		 * 												then a new guid will be generated.
		 * @param 		  	title					 	A title for the instance to create.
		 * @param [in,out]	locCrs					 	The local CRS where the ordinal are given.
		 * @param 		  	originKind				 	Indicates the kind of the MD reference point.
		 * @param 		  	referenceLocationOrdinal1	The location of the MD reference point on the
		 * 												first axis of the local 3d CRS.
		 * @param 		  	referenceLocationOrdinal2	The location of the MD reference point on the
		 * 												second axis of the local 3d CRS.
		 * @param 		  	referenceLocationOrdinal3	The location of the MD reference point on the
		 * 												third axis of the local 3d CRS.
		 */
		ReferencePointInALocalEngineeringCompoundCrs(COMMON_NS::DataObjectRepository * repo, const std::string & guid, const std::string & title,
			EML2_NS::AbstractLocal3dCrs * locCrs, gsoap_eml2_3::eml23__WellboreDatumReference originKind,
			double referenceLocationOrdinal1, double referenceLocationOrdinal2, double referenceLocationOrdinal3);

		/**
		 * Creates an instance of this class by wrapping a gsoap instance.
		 *
		 * @param [in,out]	fromGsoap	If non-null, from gsoap.
		 */
		ReferencePointInALocalEngineeringCompoundCrs(gsoap_eml2_3::_eml23__ReferencePointInALocalEngineeringCompoundCrs* fromGsoap) : EML2_NS::ReferencePointInALocalEngineeringCompoundCrs(fromGsoap) {}

		/** Destructor does nothing since the memory is managed by the gsoap context. */
		~ReferencePointInALocalEngineeringCompoundCrs() = default;

		COMMON_NS::DataObjectReference getLocalCrsDor() const final;

		DLL_IMPORT_OR_EXPORT double getX() const final;

		DLL_IMPORT_OR_EXPORT double getY() const final;

		DLL_IMPORT_OR_EXPORT double getZ() const final;

		/**
		 * Check if this reference point has a defined kind.
		 *
		 * @returns	True if this reference point has a defined kind.
		 */
		DLL_IMPORT_OR_EXPORT bool hasKind() const final;

		/**
		 * Gets the kind of this reference point.
		 *
		 * @returns	The kind of this reference point.
		 */
		DLL_IMPORT_OR_EXPORT gsoap_eml2_3::eml23__ReferencePointKind getKind() const final;

		/** Loads target relationships */
		void loadTargetRelationships() final {}

		/**
		* The standard XML namespace for serializing this data object.
		*/
		DLL_IMPORT_OR_EXPORT static constexpr char const* XML_NS = "eml23";

		/**
		* Get the standard XML namespace for serializing this data object.
		*/
		DLL_IMPORT_OR_EXPORT std::string getXmlNamespace() const final { return XML_NS; }

		/** The standard XML tag without XML namespace for serializing this data object */
		DLL_IMPORT_OR_EXPORT static const char* XML_TAG;

		/**
		 * Gets the standard XML tag without XML namespace for serializing this data object
		 *
		 * @returns	The XML tag.
		 */
		DLL_IMPORT_OR_EXPORT virtual std::string getXmlTag() const final { return XML_TAG; }

	private:

		/**
		 * Sets the local CRS where the reference point ordinals are given.
		 *
		 * @exception	std::invalid_argument	If @p localCrs is nullptr and no default CRS is
		 * 										defined in the repository.
		 *
		 * @param [in]	localCrs	If non-nullptr, the local CRS. If nullptr, the data object repository
		 * 							default CRS is set.
		 */
		DLL_IMPORT_OR_EXPORT void setLocalCrs(EML2_NS::AbstractLocal3dCrs * localCrs) final;
	};
}
