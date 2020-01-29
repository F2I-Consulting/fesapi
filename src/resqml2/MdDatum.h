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
	/** A wellbore trajectory representation. */
	class WellboreTrajectoryRepresentation;
	/** A deviation survey representation. */
	class DeviationSurveyRepresentation;
}

/** . */
namespace RESQML2_NS
{
	/**
	 * Specifies the location of the measured depth = 0 reference point. The location of this
	 * reference point is defined with respect to a CRS, which need not be the same as the CRS of a
	 * wellbore trajectory representation, which may reference this location.
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
		 * @param [in,out]	partialObject	If non-null, the partial object.
		 *
		 * @returns	A DLL_IMPORT_OR_EXPORT.
		 */
		DLL_IMPORT_OR_EXPORT MdDatum(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : AbstractObject(partialObject) {}

		/** Destructor does nothing since the memory is managed by the gsoap context. */
		virtual ~MdDatum() {}

		/**
		 * Set the local CR Swhere the reference point ordinals are given
		 *
		 * @param [in,out]	localCrs	If non-null, the local crs.
		 */
		DLL_IMPORT_OR_EXPORT void setLocalCrs(class AbstractLocal3dCrs * localCrs);

		/** Get the Local 3d CRS where the reference point ordinals are given */
		DLL_IMPORT_OR_EXPORT class AbstractLocal3dCrs * getLocalCrs() const;

		/**
		 * Get the Local 3d CRS dor where the reference point ordinals are given
		 *
		 * @returns	Null if it fails, else the local crs dor.
		 */
		virtual gsoap_resqml2_0_1::eml20__DataObjectReference* getLocalCrsDor() const = 0;

		/**
		 * Get the Local 3d CRS uuid where the reference point ordinals are given
		 *
		 * @returns	The local crs uuid.
		 */
		DLL_IMPORT_OR_EXPORT std::string getLocalCrsUuid() const;

		/**
		 * Getter of the first ordinal of the reference location.
		 *
		 * @returns	The x coordinate.
		 */
		DLL_IMPORT_OR_EXPORT virtual double getX() const = 0;

		/**
		 * Get x coordinate in global crs
		 *
		 * @returns	The x coordinate in global crs.
		 */
		DLL_IMPORT_OR_EXPORT virtual double getXInGlobalCrs() const = 0;

		/**
		 * Getter of the second ordinal of the reference location.
		 *
		 * @returns	The y coordinate.
		 */
		DLL_IMPORT_OR_EXPORT virtual double getY() const = 0;

		/**
		 * Get y coordinate in global crs
		 *
		 * @returns	The y coordinate in global crs.
		 */
		DLL_IMPORT_OR_EXPORT virtual double getYInGlobalCrs() const = 0;

		/**
		 * Getter of the third ordinal of the reference location.
		 *
		 * @returns	The z coordinate.
		 */
		DLL_IMPORT_OR_EXPORT virtual double getZ() const = 0;

		/**
		 * Get z coordinate in global crs
		 *
		 * @returns	The z coordinate in global crs.
		 */
		DLL_IMPORT_OR_EXPORT virtual double getZInGlobalCrs() const = 0;

		/**
		 * Getter of the origin kind of the MD.
		 *
		 * @returns	The origin kind.
		 */
		DLL_IMPORT_OR_EXPORT virtual gsoap_resqml2_0_1::resqml20__MdReference getOriginKind() const = 0;

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
		 * Sets XML local crs
		 *
		 * @param [in,out]	localCrs	If non-null, the local crs.
		 */
		virtual void setXmlLocalCrs(RESQML2_NS::AbstractLocal3dCrs * localCrs) = 0;

		/** Loads target relationships */
		void loadTargetRelationships();
	};
}
