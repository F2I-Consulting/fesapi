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

#include "../resqml2/MdDatum.h"

namespace RESQML2_2_NS
{
	/** A md datum. */
	class MdDatum final : public RESQML2_NS::MdDatum
	{
	public:

		/**
		 * Only to be used in partial transfer context
		 *
		 * @param [in,out]	partialObject	If non-null, the partial object.
		 *
		 * @returns	A DLL_IMPORT_OR_EXPORT.
		 */
		DLL_IMPORT_OR_EXPORT MdDatum(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : RESQML2_NS::MdDatum(partialObject) {}

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
		MdDatum(COMMON_NS::DataObjectRepository * repo, const std::string & guid, const std::string & title,
			RESQML2_NS::AbstractLocal3dCrs * locCrs, gsoap_eml2_3::eml23__WellboreDatumReference originKind,
			double referenceLocationOrdinal1, double referenceLocationOrdinal2, double referenceLocationOrdinal3);

		/**
		 * Creates an instance of this class by wrapping a gsoap instance.
		 *
		 * @param [in,out]	fromGsoap	If non-null, from gsoap.
		 */
		MdDatum(gsoap_eml2_3::_resqml22__MdDatum* fromGsoap) :RESQML2_NS::MdDatum(fromGsoap) {}

		/** Destructor does nothing since the memory is managed by the gsoap context. */
		~MdDatum() {}

		/**
		 * Get the Local 3d CRS dor where the reference point ordinals are given
		 *
		 * @returns	Null if it fails, else the local crs dor.
		 */
		COMMON_NS::DataObjectReference getLocalCrsDor() const final;

		/**
		 * Getter of the first ordinal of the reference location.
		 *
		 * @returns	The x coordinate.
		 */
		DLL_IMPORT_OR_EXPORT double getX() const final;

		/**
		 * Getter of the second ordinal of the reference location.
		 *
		 * @returns	The y coordinate.
		 */
		DLL_IMPORT_OR_EXPORT double getY() const final;

		/**
		 * Getter of the third ordinal of the reference location.
		 *
		 * @returns	The z coordinate.
		 */
		DLL_IMPORT_OR_EXPORT double getZ() const final;

		/**
		 * Getter of the origin kind of the MD.
		 *
		 * @returns	The origin kind.
		 */
		DLL_IMPORT_OR_EXPORT gsoap_eml2_3::eml23__WellboreDatumReference getOriginKind() const final;

		/** Loads target relationships */
		void loadTargetRelationships() final {}

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
		DLL_IMPORT_OR_EXPORT void setLocalCrs(RESQML2_NS::AbstractLocal3dCrs * localCrs) final;
	};
}
