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

#include "Wellbore.h"

namespace WITSML2_0_NS
{
	class Wellbore;

	/**
	 * The class is the super class for all wellbore objects (all top level objects pointing to
	 * Wellbore)
	 */
	class WellboreObject : public WITSML2_0_NS::AbstractObject
	{
	public:

		/** Destructor does nothing since the memory is managed by the gsoap context. */
		virtual ~WellboreObject() {}

		/**
		* Get the Data Object Reference of the wellbore linked with this data object.
		*/
		DLL_IMPORT_OR_EXPORT virtual COMMON_NS::DataObjectReference getWellboreDor() const = 0;

		/**
		 * Get the wellbore linked with this data object.
		 *
		 * @returns	Null if it fails, else the wellbore.
		 */
		DLL_IMPORT_OR_EXPORT Wellbore* getWellbore() const;

		/**
		 * Set the wellbore linked with this data object.
		 *
		 * @param [in,out]	witsmlWellbore	If non-null, the witsml wellbore.
		 */
		DLL_IMPORT_OR_EXPORT virtual void setWellbore(Wellbore* witsmlWellbore) = 0;

		/**
		* Resolve all relationships of the object in a repository.
		*/
		virtual void loadTargetRelationships();

	protected:

		/**
		 * Constructor for partial transfer
		 *
		 * @param [in,out]	partialObject	If non-null, the partial object.
		 *
		 *
		 */
		DLL_IMPORT_OR_EXPORT WellboreObject(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : WITSML2_0_NS::AbstractObject(partialObject) {}

		/** Creates an instance of this class in a gsoap context. */
		WellboreObject() :WITSML2_0_NS::AbstractObject() {}

		/**
		 * Creates an instance of this class by wrapping a gsoap instance.
		 *
		 * @param [in,out]	fromGsoap	If non-null, from gsoap.
		 */
		WellboreObject(gsoap_eml2_1::eml21__AbstractObject* fromGsoap) :WITSML2_0_NS::AbstractObject(fromGsoap) {}
	};
}
