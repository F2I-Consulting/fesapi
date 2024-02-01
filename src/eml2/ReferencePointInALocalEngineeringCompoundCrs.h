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
	/**
	 * @brief	A reference point which is defined in the context of a Local Engineering compound (2d horizontal + 1D vertical) CRS.
	 */
	class ReferencePointInALocalEngineeringCompoundCrs : public COMMON_NS::AbstractObject
	{
	public:

		/**
		 * Only to be used in partial transfer context
		 *
		 * @param [in]	partialObject	If non-nullptr, the partial object.
		 */
		DLL_IMPORT_OR_EXPORT ReferencePointInALocalEngineeringCompoundCrs(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : AbstractObject(partialObject) {}

		/** Destructor does nothing since the memory is managed by the gsoap context. */
		virtual ~ReferencePointInALocalEngineeringCompoundCrs() = default;

		/**
		 * Gets the local 3d CRS where the reference point ordinals are given.
		 *
		 * @exception	std::invalid_argument	If the local CRS is not set.
		 *
		 * @returns	A pointer to the local CRS.
		 */
		DLL_IMPORT_OR_EXPORT class AbstractLocal3dCrs* getLocalCrs() const;

		/**
		 * Gets the data object reference of the local 3d CRS where the reference point ordinals are
		 * given.
		 *
		 * @returns	nullptr if the local 3d CRS is not set, else the data object reference of the
		 * 			local 3d CRS.
		 */
		virtual COMMON_NS::DataObjectReference getLocalCrsDor() const = 0;

		/**
		 * Gets the first ordinal (x) of the location of the MD reference point relative to the local CRS.
		 *
		 * @returns	The first ordinal of the reference location relative to the local CRS.
		 */
		DLL_IMPORT_OR_EXPORT virtual double getX() const = 0;

		/**
		 * Gets the first ordinal (x) of the location of the MD reference in the global CRS.
		 *
		 * @exception	std::invalid_argument	If the local CRS is not set.
		 *
		 * @returns	The first ordinal of the reference location relative to the global CRS.
		 */
		DLL_IMPORT_OR_EXPORT double getXInGlobalCrs() const;

		/**
		 * Gets the second ordinal (y) of the location of the MD reference point relative to the local CRS.
		 *
		 * @returns	The second ordinal of the reference location relative to the local CRS.
		 */
		DLL_IMPORT_OR_EXPORT virtual double getY() const = 0;

		/**
		 * Gets the second ordinal (y) of the location of the MD reference in the global CRS.
		 *
		 * @exception	std::invalid_argument	If the local CRS is not set.
		 *
		 * @returns	The second ordinal of the reference location relative to the global CRS.
		 */
		DLL_IMPORT_OR_EXPORT double getYInGlobalCrs() const;

		/**
		 * Gets the third ordinal (z) of the location of the MD reference point relative to the local CRS.
		 *
		 * @returns	The third ordinal of the reference location relative to the local CRS.
		 */
		DLL_IMPORT_OR_EXPORT virtual double getZ() const = 0;

		/**
		 * Gets the third ordinal (z) of the location of the MD reference in the global CRS.
		 *
		 * @exception	std::invalid_argument	If the local CRS is not set.
		 *
		 * @returns	The third ordinal of the reference location relative to the global CRS.
		 */
		DLL_IMPORT_OR_EXPORT double getZInGlobalCrs() const;

		/**
		 * Check if this reference point has a defined kind.
		 *
		 * @returns	True if this reference point has a defined kind.
		 */
		DLL_IMPORT_OR_EXPORT virtual bool hasKind() const = 0;

		/**
		 * Gets the kind of this reference point.
		 *
		 * @returns	The kind of this reference point.
		 */
		DLL_IMPORT_OR_EXPORT virtual gsoap_eml2_3::eml23__ReferencePointKind getKind() const = 0;

	protected:

		/** Default constructor does nothing */
		ReferencePointInALocalEngineeringCompoundCrs() : COMMON_NS::AbstractObject() {}

		/**
		 * Creates an instance of this class by wrapping a gsoap instance.
		 *
		 * @param [in,out]	fromGsoap	If non-null, from gsoap.
		 */
		ReferencePointInALocalEngineeringCompoundCrs(gsoap_resqml2_0_1::_resqml20__MdDatum* fromGsoap) : COMMON_NS::AbstractObject(fromGsoap) {}

		/**
		 * Creates an instance of this class by wrapping a gsoap instance.
		 *
		 * @param [in,out]	fromGsoap	If non-null, from gsoap.
		 */
		ReferencePointInALocalEngineeringCompoundCrs(gsoap_eml2_3::_eml23__ReferencePointInALocalEngineeringCompoundCrs* fromGsoap) : COMMON_NS::AbstractObject(fromGsoap) {}

		/**
		 * Sets the local CRS where the reference point ordinals are given.
		 *
		 * @exception	std::invalid_argument	If @p localCrs is nullptr and no default CRS is
		 * 										defined in the repository.
		 *
		 * @param [in]	localCrs	If non-nullptr, the local CRS. If nullptr, the data object repository
		 * 							default CRS is set.
		 */
		DLL_IMPORT_OR_EXPORT virtual void setLocalCrs(class AbstractLocal3dCrs* localCrs) = 0;
	};
}
