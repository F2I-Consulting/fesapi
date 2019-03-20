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

#include "witsml2_0/WellboreObject.h"

namespace WITSML2_0_NS
{
	class Trajectory : public WellboreObject
	{
	public:
		/**
		* Constructor for partial transfer
		*/
		Trajectory(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : WellboreObject(partialObject) {}

		Trajectory(class Wellbore* witsmlWellbore,
			const std::string & guid,
			const std::string & title,
			gsoap_eml2_1::witsml2__ChannelStatus channelStatus);
	
		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		Trajectory(gsoap_eml2_1::witsml2__Trajectory* fromGsoap) :WellboreObject(fromGsoap) {}

		/**
		* Destructor does nothing since the memory is managed by the gsoap context.
		*/
		~Trajectory() {}

		DLL_IMPORT_OR_EXPORT gsoap_eml2_1::eml21__DataObjectReference* getWellboreDor() const;
		DLL_IMPORT_OR_EXPORT void setWellbore(class Wellbore* witsmlWellbore);

		GETTER_AND_SETTER_TIME_T_ATTRIBUTE(DTimTrajStart)
		GETTER_AND_SETTER_TIME_T_ATTRIBUTE(DTimTrajEnd)

		GETTER_AND_SETTER_LENGTH_MEASURE_ATTRIBUTE(MdMn)
		GETTER_AND_SETTER_LENGTH_MEASURE_ATTRIBUTE(MdMx)

		GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE(std::string, ServiceCompany)

		GETTER_AND_SETTER_PLANE_ANGLE_MEASURE_ATTRIBUTE(MagDeclUsed)
		GETTER_AND_SETTER_PLANE_ANGLE_MEASURE_ATTRIBUTE(GridConUsed)
		GETTER_AND_SETTER_PLANE_ANGLE_MEASURE_ATTRIBUTE(AziVertSect)

		GETTER_AND_SETTER_LENGTH_MEASURE_ATTRIBUTE(DispNsVertSectOrig)
		GETTER_AND_SETTER_LENGTH_MEASURE_ATTRIBUTE(DispEwVertSectOrig)

		GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE(bool, Definitive)
		GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE(bool, Memory)
		GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE(bool, FinalTraj)

		GETTER_AND_SETTER_GENERIC_OPTIONAL_ATTRIBUTE(gsoap_eml2_1::witsml2__AziRef, AziRef)

		DLL_IMPORT_OR_EXPORT static const char* XML_TAG;
		DLL_IMPORT_OR_EXPORT virtual std::string getXmlTag() const { return XML_TAG; }
	};
}
