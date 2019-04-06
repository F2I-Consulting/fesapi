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

#include "resqml2_0_1/DeviationSurveyRepresentation.h"

namespace RESQML2_0_1_NS
{
	class WellboreTrajectoryRepresentation;
	class DeviationSurveyRepresentation;
}

namespace RESQML2_NS
{
	class MdDatum : public COMMON_NS::AbstractObject
	{
	protected :

		/**
		* Default constructor does nothing
		*/
		MdDatum() : COMMON_NS::AbstractObject() {}

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		MdDatum(gsoap_resqml2_0_1::_resqml2__MdDatum* fromGsoap) : COMMON_NS::AbstractObject(fromGsoap) {}

	private :

		/**
		* Add a Wellbore trajectory which uses this MD information
		* Does not add the inverse relationship i.e. from the Wellbore trajectory to this MD information.
		*/
		void addWellboreTrajectoryRepresentation(RESQML2_0_1_NS::WellboreTrajectoryRepresentation* traj) { wellboreTrajectoryRepresentationSet.push_back(traj); }

		/**
		* Add a Deviation Survey which uses this MD information
		* Does not add the inverse relationship i.e. from the deviation survey to this MD information.
		*/
		void addDeviationSurveyRepresentation(RESQML2_0_1_NS::DeviationSurveyRepresentation* deviationSurvey)  { deviationSurveyRepresentationSet.push_back(deviationSurvey); }

	public:

		/**
		* Only to be used in partial transfer context
		*/
		MdDatum(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : AbstractObject(partialObject) {}

		/**
		* Destructor does nothing since the memory is managed by the gsoap context.
		*/
		virtual ~MdDatum() {}

		DLL_IMPORT_OR_EXPORT static const char* XML_TAG;
		DLL_IMPORT_OR_EXPORT virtual std::string getXmlTag() const {return XML_TAG;}

		/**
		* Set the local CR Swhere the reference point ordinals are given
		*/
		DLL_IMPORT_OR_EXPORT void setLocalCrs(class AbstractLocal3dCrs * localCrs);

		/**
		* Get the Local 3d CRS where the reference point ordinals are given
		*/
		DLL_IMPORT_OR_EXPORT class AbstractLocal3dCrs * getLocalCrs() const;

		/**
		* Get the Local 3d CRS dor where the reference point ordinals are given
		*/
		virtual gsoap_resqml2_0_1::eml20__DataObjectReference* getLocalCrsDor() const = 0;

		/**
		* Get the Local 3d CRS uuid where the reference point ordinals are given
		*/
		DLL_IMPORT_OR_EXPORT std::string getLocalCrsUuid() const;

		/**
		* Getter of the first ordinal of the reference location.
		*/
		DLL_IMPORT_OR_EXPORT virtual double getX() const = 0;
		DLL_IMPORT_OR_EXPORT virtual double getXInGlobalCrs() const = 0;

		/**
		* Getter of the second ordinal of the reference location.
		*/
		DLL_IMPORT_OR_EXPORT virtual double getY() const = 0;
		DLL_IMPORT_OR_EXPORT virtual double getYInGlobalCrs() const = 0;

		/**
		* Getter of the third ordinal of the reference location.
		*/
		DLL_IMPORT_OR_EXPORT virtual double getZ() const = 0;
		DLL_IMPORT_OR_EXPORT virtual double getZInGlobalCrs() const = 0;

		/**
		* Getter of the origin kind of the MD.
		*/
		DLL_IMPORT_OR_EXPORT virtual gsoap_resqml2_0_1::resqml2__MdReference getOriginKind() const = 0;

	protected:

		friend void RESQML2_0_1_NS::WellboreTrajectoryRepresentation::setMdDatum(RESQML2_NS::MdDatum* mdDatum);
		friend void RESQML2_0_1_NS::DeviationSurveyRepresentation::setMdDatum(RESQML2_NS::MdDatum* mdDatum);

		virtual void setXmlLocalCrs(RESQML2_NS::AbstractLocal3dCrs * localCrs) = 0;

		std::vector<epc::Relationship> getAllEpcRelationships() const;
		void importRelationshipSetFromEpc(COMMON_NS::EpcDocument* epcDoc);

		// XML backward relationship
		std::vector<RESQML2_0_1_NS::WellboreTrajectoryRepresentation*> wellboreTrajectoryRepresentationSet;
		std::vector<RESQML2_0_1_NS::DeviationSurveyRepresentation*> deviationSurveyRepresentationSet;
	};
}

