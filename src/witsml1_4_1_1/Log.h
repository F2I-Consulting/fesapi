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

#include "witsml1_4_1_1/AbstractObject.h"

#include "resqml2_0_1/WellboreFrameRepresentation.h"

namespace WITSML1_4_1_1_NS
{
	class DLL_IMPORT_OR_EXPORT Log : public AbstractObject
	{
	public:
		/**
		* Creates an instance of this class in a gsoap context.
		* @param guid		The guid to set to this instance. If empty then a new guid will be generated.
		*/
		Log(class Wellbore* witsmlWellbore,
			const std::string & guid,
			const std::string & title,
			gsoap_witsml1_4_1_1::witsml1__LogIndexType indexType,
			const std::string & indexCurve);

		Log(class Wellbore* witsmlWellbore,
			const std::string & guid,
			const std::string & title,
			gsoap_witsml1_4_1_1::witsml1__LogIndexType indexType,
			const std::string & indexCurve,
			const std::string & sourceName,
			const time_t & dTimCreation,
			const time_t & dTimLastChange,
			const std::string & comments);

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		Log(gsoap_witsml1_4_1_1::witsml1__obj_USCORElogs* fromGsoap):AbstractObject(fromGsoap), wellbore(nullptr), resqmlWellboreFrameRepresentation(nullptr) {}

		/**
		* Destructor does nothing since the memory is managed by the gsoap context.
		*/
		~Log() {}

		gsoap_witsml1_4_1_1::witsml1__LogIndexType getIndexType();

		std::string getIndexMnemonic();

		std::vector<std::string> getMnemonicSet();

		const std::vector<std::string> & getData() const;

		std::string getDataDelimiter() const;

		void setValues(
			const std::string & description,
			const std::string & dataDelimiter,
			const std::string & startEndIncrementUOM,
			const double & startIndex,
			const double & endIndex,
			const double & stepIncrement,
			gsoap_witsml1_4_1_1::witsml1__LogIndexDirection direction,
			//const std::string & nullValue,
			const std::string & mnemonicList,
			const std::string & unitList,
			std::vector<std::string> const & data);

		/**
		* Get the count of log curve in this log including the index log curve (usually MD)
		*/
		unsigned int getLogCurveCount() const;

		/**
		* Get the mnemonic of a particular log curve of this log
		*/
		std::string getLogCurveMnemonic(const unsigned int & logCurveIndex) const;

		/**
		* Get the datatype of a particular log curve of this log
		*/
		gsoap_witsml1_4_1_1::witsml1__LogDataType getLogCurveDataType(const unsigned int & logCurveIndex) const;

		/**
		* Get the unit of measure of a particular log curve of this log.
		* Return empty string if no uom is provided for this log curve.
		*/
		std::string getLogCurveUom(const unsigned int & logCurveIndex) const;

		void pushBackLogCurveInfo(const std::string & mnemonic, gsoap_witsml1_4_1_1::witsml1__LogDataType typeLogData);

		void pushBackLogCurveInfo(
			const std::string & namingSystem,
			const std::string & mnemonic,
			const std::string & classWitsml,
			const std::string & unit,
			//const string & nullValue,
			const int & datumIndex,
			const std::string & minMaxIndexUOM,
			const double & minIndex,
			const double & maxIndex,
			const std::string & curveDescription,
			gsoap_witsml1_4_1_1::witsml1__PerLengthUom perLengthUOM,
			const double & densData,
			gsoap_witsml1_4_1_1::witsml1__LogTraceOrigin traceOrigin,
			gsoap_witsml1_4_1_1::witsml1__LogDataType typeLogData);

		void setWellbore(class Wellbore* witsmlWellbore);

		class Wellbore* getWellbore() {return wellbore;}

		RESQML2_0_1_NS::WellboreFrameRepresentation* getResqmlWellboreFrameRepresentation() const {return resqmlWellboreFrameRepresentation;}

		soap* getGSoapContext() const {return collection->soap;}

		const std::string & getTitle() const {return static_cast<gsoap_witsml1_4_1_1::witsml1__obj_USCORElogs*>(collection)->log[0]->name;}

		std::string getUuid() const {return *static_cast<gsoap_witsml1_4_1_1::witsml1__obj_USCORElogs*>(collection)->log[0]->uid;}
		time_t getCreation() const
		{
			if (static_cast<gsoap_witsml1_4_1_1::_witsml1__logs*>(collection)->log[0]->commonData->dTimCreation)
				return mktime(static_cast<gsoap_witsml1_4_1_1::_witsml1__logs*>(collection)->log[0]->commonData->dTimCreation);
			else
				return -1;
		}
		time_t getLastUpdate() const
		{
			if (static_cast<gsoap_witsml1_4_1_1::_witsml1__logs*>(collection)->log[0]->commonData->dTimLastChange)
				return mktime(static_cast<gsoap_witsml1_4_1_1::_witsml1__logs*>(collection)->log[0]->commonData->dTimLastChange);
			else
				return -1;
		}

		std::vector<epc::Relationship> getAllEpcRelationships() const;

		/**
		* Resolve all relationships of the object in an epc document.
		*/
		void importRelationshipSetFromEpc(COMMON_NS::EpcDocument* epcDoc);

		static const char* XML_TAG;
		virtual std::string getXmlTag() const {return XML_TAG;}

	protected:

		// XML forwards relationship
		class Wellbore* wellbore;

		// XML backwards relationship
		RESQML2_0_1_NS::WellboreFrameRepresentation* resqmlWellboreFrameRepresentation;
		
		friend void RESQML2_0_1_NS::WellboreFrameRepresentation::setWitsmlLog(Log * witsmlLogToSet);
	};
}

