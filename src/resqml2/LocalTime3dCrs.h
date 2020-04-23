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

#include "AbstractLocal3dCrs.h"

/** @brief */
namespace RESQML2_NS
{
	/**
	 * @brief	Defines a local time coordinate system. The geometrical origin and location are
	 * 			defined by the elements of the base class AbstractLocal3dCrs. This CRS defines the
	 * 			time unit that the time-based geometries that refer to it will use.
	 */
	class LocalTime3dCrs : public AbstractLocal3dCrs
	{
	public:

		/**
		 * Only to be used in partial transfer context.
		 *
		 * @param [in]	partialObject	If non-nullptr, the partial object.
		 */
		DLL_IMPORT_OR_EXPORT LocalTime3dCrs(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : AbstractLocal3dCrs(partialObject) {}

		/** Destructor does nothing since the memory is manged by the gSOAP context. */
		virtual ~LocalTime3dCrs() {}

		/**
		 * Gets the unit of measure of this local time 3d CRS.
		 *
		 * @returns	The unit of measure.
		 */
		DLL_IMPORT_OR_EXPORT virtual gsoap_resqml2_0_1::eml20__TimeUom getUnit() const = 0;

		/**
		 * Gets unit of measure of this local time 3d CRS as a string.
		 *
		 * @returns	The unit of measure as a string.
		 */
		DLL_IMPORT_OR_EXPORT virtual std::string getUnitAsString() const = 0;

		/** The standard XML tag without XML namespace for serializing this data object. */
		DLL_IMPORT_OR_EXPORT static const char* XML_TAG;

		DLL_IMPORT_OR_EXPORT virtual std::string getXmlTag() const final { return XML_TAG; }

	protected :

		LocalTime3dCrs() {}

		/**
		 * Creates an instance of this class by wrapping a gsoap instance.
		 *
		 * @param [in,out]	fromGsoap	If non-null, from gsoap.
		 */
		LocalTime3dCrs(gsoap_resqml2_0_1::_resqml20__LocalTime3dCrs* fromGsoap) : AbstractLocal3dCrs(fromGsoap) {}

		/**
		 * Creates an instance of this class by wrapping a gsoap instance.
		 *
		 * @param [in,out]	fromGsoap	If non-null, from gsoap.
		 */
		LocalTime3dCrs(gsoap_eml2_3::_resqml22__LocalTime3dCrs* fromGsoap) : AbstractLocal3dCrs(fromGsoap) {}
	};
}
