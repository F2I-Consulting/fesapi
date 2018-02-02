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

namespace resqml2_0_1
{
	class WellboreTrajectoryRepresentation;
	class DeviationSurveyRepresentation;
}

namespace resqml2
{
	class DLL_IMPORT_OR_EXPORT MdDatum : public common::AbstractObject
	{
	protected :

		/**
		* Default constructor does nothing
		*/
		MdDatum() : common::AbstractObject() {}

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		MdDatum(gsoap_resqml2_0_1::_resqml2__MdDatum* fromGsoap) : common::AbstractObject(fromGsoap) {}

	private :

		/**
		* Add a Wellbore trajectory which uses this MD information
		* Does not add the inverse relationship i.e. from the Wellbore trajectory to this MD information.
		*/
		void addWellboreTrajectoryRepresentation(resqml2_0_1::WellboreTrajectoryRepresentation* traj) { wellboreTrajectoryRepresentationSet.push_back(traj); }

		/**
		* Add a Deviation Survey which uses this MD information
		* Does not add the inverse relationship i.e. from the deviation survey to this MD information.
		*/
		void addDeviationSurveyRepresentation(resqml2_0_1::DeviationSurveyRepresentation* deviationSurvey)  { deviationSurveyRepresentationSet.push_back(deviationSurvey); }

	public:

		/**
		* Only to be used in partial transfer context
		*/
		MdDatum(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : AbstractObject(partialObject) {}

		/**
		* Destructor does nothing since the memory is managed by the gsoap context.
		*/
		virtual ~MdDatum() {}

		static const char* XML_TAG;
		virtual std::string getXmlTag() const {return XML_TAG;}

		/**
		* Set the local CR Swhere the reference point ordinals are given
		*/
		void setLocalCrs(class AbstractLocal3dCrs * localCrs);

		/**
		* Get the Local 3d CRS where the reference point ordinals are given
		*/
		class AbstractLocal3dCrs * getLocalCrs() const;

		/**
		* Get the Local 3d CRS dor where the reference point ordinals are given
		*/
		virtual gsoap_resqml2_0_1::eml20__DataObjectReference* getLocalCrsDor() const = 0;

		/**
		* Get the Local 3d CRS uuid where the reference point ordinals are given
		*/
		std::string getLocalCrsUuid() const;

		/**
		* Getter of the first ordinal of the reference location.
		*/
		virtual double getX() const = 0;
		virtual double getXInGlobalCrs() const = 0;

		/**
		* Getter of the second ordinal of the reference location.
		*/
		virtual double getY() const = 0;
		virtual double getYInGlobalCrs() const = 0;

		/**
		* Getter of the third ordinal of the reference location.
		*/
		virtual double getZ() const = 0;
		virtual double getZInGlobalCrs() const = 0;

		/**
		* Getter of the origin kind of the MD.
		*/
		virtual gsoap_resqml2_0_1::resqml2__MdReference getOriginKind() const = 0;

	protected:

		friend void resqml2_0_1::WellboreTrajectoryRepresentation::setMdDatum(resqml2::MdDatum* mdDatum);
		friend void resqml2_0_1::DeviationSurveyRepresentation::setMdDatum(resqml2::MdDatum* mdDatum);

		virtual void setXmlLocalCrs(resqml2::AbstractLocal3dCrs * localCrs) = 0;

		std::vector<epc::Relationship> getAllEpcRelationships() const;
		void importRelationshipSetFromEpc(common::EpcDocument* epcDoc);

		// XML backward relationship
		std::vector<resqml2_0_1::WellboreTrajectoryRepresentation*> wellboreTrajectoryRepresentationSet;
		std::vector<resqml2_0_1::DeviationSurveyRepresentation*> deviationSurveyRepresentationSet;
	};
}

