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

#include "AbstractObject.h"

/** . */
namespace RESQML2_0_1_NS {
	/** A wellbore feature. */
	class WellboreFeature;
}

/** . */
namespace WITSML2_0_NS
{
	/** A trajectory. */
	class Trajectory;
	/** A wellbore completion. */
	class WellboreCompletion;
	/** A wellbore geometry. */
	class WellboreGeometry;
	/** A log. */
	class Log;

	/** A wellbore. */
	class Wellbore : public WITSML2_0_NS::AbstractObject
	{
	public:

		/**
		 * Only to be used in partial transfer context
		 *
		 * @param [in,out]	partialObject	If non-null, the partial object.
		 *
		 * @returns	A DLL_IMPORT_OR_EXPORT.
		 */
		DLL_IMPORT_OR_EXPORT Wellbore(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : WITSML2_0_NS::AbstractObject(partialObject) {}

		/**
		 * Creates an instance of this class in a gsoap context.
		 *
		 * @param [in,out]	witsmlWell	If non-null, the witsml well.
		 * @param 		  	guid	  	The guid to set to this instance. If empty then a new guid will
		 * 								be generated.
		 * @param 		  	title	  	The title.
		 */
		Wellbore(class Well* witsmlWell,
			const std::string & guid,
			const std::string & title);

		/**
		 * Constructor
		 *
		 * @param [in,out]	witsmlWell	  	If non-null, the witsml well.
		 * @param 		  	guid		  	Unique identifier.
		 * @param 		  	title		  	The title.
		 * @param 		  	statusWellbore	The status wellbore.
		 * @param 		  	isActive	  	True if is active, false if not.
		 * @param 		  	achievedTD	  	True to achieved td.
		 */
		Wellbore(class Well* witsmlWell,
			const std::string & guid,
			const std::string & title,
			gsoap_eml2_1::eml21__WellStatus statusWellbore,
			bool isActive,
			bool achievedTD
		);

		/**
		 * Creates an instance of this class by wrapping a gsoap instance.
		 *
		 * @param [in,out]	fromGsoap	If non-null, from gsoap.
		 */
		Wellbore(gsoap_eml2_1::witsml20__Wellbore* fromGsoap):AbstractObject(fromGsoap) {}

		/** Destructor does nothing since the memory is managed by the gsoap context. */
		~Wellbore() {}

		COMMON_NS::DataObjectReference getWellDor() const;
		DLL_IMPORT_OR_EXPORT class Well* getWell() const;

		/**
		 * Sets a well
		 *
		 * @param [in,out]	witsmlWell	If non-null, the witsml well.
		 */
		DLL_IMPORT_OR_EXPORT void setWell(class Well* witsmlWell);

		/**
		 * Gets resqml wellbore feature
		 *
		 * @returns	Null if it fails, else the resqml wellbore feature.
		 */
		DLL_IMPORT_OR_EXPORT std::vector<RESQML2_0_1_NS::WellboreFeature *> getResqmlWellboreFeature() const;

		/**
		 * Gets wellbore completions
		 *
		 * @returns	Null if it fails, else the wellbore completions.
		 */
		DLL_IMPORT_OR_EXPORT std::vector<WellboreCompletion *> getWellboreCompletions() const;

		/**
		 * Gets the trajectories
		 *
		 * @returns	Null if it fails, else the trajectories.
		 */
		DLL_IMPORT_OR_EXPORT std::vector<Trajectory *> getTrajectories() const;

		/**
		 * Gets wellbore geometries
		 *
		 * @returns	Null if it fails, else the wellbore geometries.
		 */
		DLL_IMPORT_OR_EXPORT std::vector<WellboreGeometry *> getWellboreGeometries() const;

		/**
		 * Gets the logs
		 *
		 * @returns	Null if it fails, else the logs.
		 */
		DLL_IMPORT_OR_EXPORT std::vector<Log *> getLogs() const;

		GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE(std::string, Number)
		GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE(std::string, SuffixAPI)
		GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE(std::string, NumGovt)
		GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE(gsoap_eml2_1::eml21__WellStatus, StatusWellbore)
		GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE(bool, IsActive)
		GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE(gsoap_eml2_1::witsml20__WellPurpose, PurposeWellbore)
		GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE(gsoap_eml2_1::witsml20__WellboreType, TypeWellbore)
		GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE(gsoap_eml2_1::witsml20__WellboreShape, Shape)
		GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE(bool, AchievedTD)
		GETTER_AND_SETTER_DEPTH_MEASURE_OPTIONAL_ATTRIBUTE(Md, gsoap_eml2_1::eml21__LengthUom)
		GETTER_AND_SETTER_DEPTH_MEASURE_OPTIONAL_ATTRIBUTE(MdBit, gsoap_eml2_1::eml21__LengthUom)
		GETTER_AND_SETTER_DEPTH_MEASURE_OPTIONAL_ATTRIBUTE(MdKickoff, gsoap_eml2_1::eml21__LengthUom)
		GETTER_AND_SETTER_DEPTH_MEASURE_OPTIONAL_ATTRIBUTE(MdPlanned, gsoap_eml2_1::eml21__LengthUom)
		GETTER_AND_SETTER_DEPTH_MEASURE_OPTIONAL_ATTRIBUTE(MdSubSeaPlanned, gsoap_eml2_1::eml21__LengthUom)

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

		/** Resolve all relationships of the object in the repository. */
		void loadTargetRelationships();
	};
}
