/*-----------------------------------------------------------------------
Copyright F2I-CONSULTING, (2014-2017)

philippe.verney@f2i-consulting.com

This software is a computer program whose purpose is to access to data formatted using Energistics standards.

This software is governed by the CeCILL-B license under French law and
abiding by the rules of distribution of free software.  You can  use, 
modify and/ or redistribute the software under the terms of the CeCILL-B
license as circulated by CEA, CNRS and INRIA at the following URL
"http://www.cecill.info". 

As a counterpart to the access to the source code and  rights to copy,
modify and redistribute granted by the license, users are provided only
with a limited warranty  and the software's author,  the holder of the
economic rights,  and the successive licensors  have only  limited
liability. 

In this respect, the user's attention is drawn to the risks associated
with loading,  using,  modifying and/or developing or reproducing the
software by the user in light of its specific status of free software,
that may mean  that it is complicated to manipulate,  and  that  also
therefore means  that it is reserved for developers  and  experienced
professionals having in-depth computer knowledge. Users are therefore
encouraged to load and test the software's suitability as regards their
requirements in conditions enabling the security of their systems and/or 
data to be ensured and,  more generally, to use and operate it in the 
same conditions as regards security. 

The fact that you are presently reading this means that you have had
knowledge of the CeCILL-B license and that you accept its terms.
-----------------------------------------------------------------------*/
#pragma once

#include "witsml1_4_1_1/AbstractObject.h"

#include "resqml2_0_1/WellboreFrameRepresentation.h"

namespace witsml1_4_1_1
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

		resqml2_0_1::WellboreFrameRepresentation* getResqmlWellboreFrameRepresentation() const {return resqmlWellboreFrameRepresentation;}

		soap* getGSoapContext() const {return collection->soap;}

		const std::string & getTitle() const {return static_cast<gsoap_witsml1_4_1_1::witsml1__obj_USCORElogs*>(collection)->log[0]->name;}

		std::string getUuid() const {return *static_cast<gsoap_witsml1_4_1_1::witsml1__obj_USCORElogs*>(collection)->log[0]->uid;}
		time_t getCreation() const
		{
			if (static_cast<gsoap_witsml1_4_1_1::_witsml1__logs*>(collection)->log[0]->commonData->dTimCreation)
				return *static_cast<gsoap_witsml1_4_1_1::_witsml1__logs*>(collection)->log[0]->commonData->dTimCreation;
			else
				return -1;
		}
		time_t getLastUpdate() const
		{
			if (static_cast<gsoap_witsml1_4_1_1::_witsml1__logs*>(collection)->log[0]->commonData->dTimLastChange)
				return *static_cast<gsoap_witsml1_4_1_1::_witsml1__logs*>(collection)->log[0]->commonData->dTimLastChange;
			else
				return -1;
		}

		std::vector<epc::Relationship> getAllEpcRelationships() const;

		/**
		* Resolve all relationships of the object in an epc document.
		*/
		void importRelationshipSetFromEpc(common::EpcDocument* epcDoc);

		static const char* XML_TAG;
		virtual std::string getXmlTag() const {return XML_TAG;}

	protected:

		// XML forwards relationship
		class Wellbore* wellbore;

		// XML backwards relationship
		resqml2_0_1::WellboreFrameRepresentation* resqmlWellboreFrameRepresentation;
		
		friend void resqml2_0_1::WellboreFrameRepresentation::setWitsmlLog(Log * witsmlLogToSet);
	};
}
