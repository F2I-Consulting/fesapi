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

#include "../resqml2_0_1/DeviationSurveyRepresentation.h"

/** . */
namespace RESQML2_0_1_NS
{
	class WellboreTrajectoryRepresentation;
	class DeviationSurveyRepresentation;
}

/** . */
namespace RESQML2_NS
{
	/**
	 * Proxy class for a MD datum. An MD datum specifies the location of the measured depth = 0
	 * reference point. The location of this reference point is defined with respect to a CRS, which
	 * need not be the same as the CRS of a wellbore trajectory representation, which may reference
	 * this location.
	 */
	class MdDatum : public COMMON_NS::AbstractObject
	{
	protected :

		/** Default constructor does nothing */
		MdDatum() : COMMON_NS::AbstractObject() {}

		/**
		 * Creates an instance of this class by wrapping a gsoap instance.
		 *
		 * @param [in,out]	fromGsoap	If non-null, from gsoap.
		 */
		MdDatum(gsoap_resqml2_0_1::_resqml20__MdDatum* fromGsoap) : COMMON_NS::AbstractObject(fromGsoap) {}

	public:

		/**
		 * Only to be used in partial transfer context
		 *
		 * @param [in]	partialObject	If non-nullptr, the partial object.
		 */
		DLL_IMPORT_OR_EXPORT MdDatum(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : AbstractObject(partialObject) {}

		/** Destructor does nothing since the memory is managed by the gsoap context. */
		virtual ~MdDatum() {}

		/**
		 * Sets the local CRS where the reference point ordinals are given.
		 *
		 * @exception	std::invalid_argument	If @p localCrs is nullptr and no default CRS is
		 * 										defined in the repository.
		 *
		 * @param [in]	localCrs	If non-nullptr, the local CRS. If nullptr, the data object repository
		 * 							default CRS is set.
		 */
		DLL_IMPORT_OR_EXPORT void setLocalCrs(class AbstractLocal3dCrs * localCrs);

		/** 
		 * Gets the local 3d CRS where the reference point ordinals are given.
		 *
		 * @exception	std::invalid_argument	If the local CRS is not set.
		 * 										
		 * @returns	A pointer to the local CRS.
		 */
		DLL_IMPORT_OR_EXPORT class AbstractLocal3dCrs * getLocalCrs() const;

		/**
		 * Gets the data object reference of the local 3d CRS where the reference point ordinals are
		 * given.
		 *
		 * @returns	nullptr if the local 3d CRS is not set, else the data object reference of the
		 * 			local 3d CRS.
		 */
		virtual gsoap_resqml2_0_1::eml20__DataObjectReference* getLocalCrsDor() const = 0;

		/**
		 * Get the UUID of the local 3d CRS where the reference point ordinals are given.
		 *
		 * @exception	std::invalid_argument	If the local CRS is not set.
		 * 										
		 * @returns	The UUID of the local 3d CRS.
		 */
		DLL_IMPORT_OR_EXPORT std::string getLocalCrsUuid() const;

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
		DLL_IMPORT_OR_EXPORT virtual double getXInGlobalCrs() const = 0;

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
		DLL_IMPORT_OR_EXPORT virtual double getYInGlobalCrs() const = 0;

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
		DLL_IMPORT_OR_EXPORT virtual double getZInGlobalCrs() const = 0;

		/**
		 * Gets the origin kind of this MD datum.
		 *
		 * @returns	The origin kind.
		 */
		DLL_IMPORT_OR_EXPORT virtual gsoap_resqml2_0_1::resqml20__MdReference getOriginKind() const = 0;

		/** The standard XML tag without XML namespace for serializing this data object */
		DLL_IMPORT_OR_EXPORT static const char* XML_TAG;

		/**
		 * Gets the standard XML tag without XML namespace for serializing this data object
		 *
		 * @returns	The XML tag.
		 */
		DLL_IMPORT_OR_EXPORT virtual std::string getXmlTag() const { return XML_TAG; }

	protected:

		/**
		 * Sets XML local crs
		 *
		 * @param [in,out]	localCrs	If non-nullptr, the local crs.
		 */
		virtual void setXmlLocalCrs(RESQML2_NS::AbstractLocal3dCrs * localCrs) = 0;

		/** Loads target relationships */
		void loadTargetRelationships();
	};
}
