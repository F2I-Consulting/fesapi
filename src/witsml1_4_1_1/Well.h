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

#include "witsml1_4_1_1/Wellbore.h"

namespace witsml1_4_1_1
{
	class DLL_IMPORT_OR_EXPORT Well : public AbstractObject
	{
	public:
		/**
		* Creates an instance of this class in a gsoap context.
		* @param soapContext	The soap context where the underlying gsoap proxy is going to be created.
		* @param guid		The guid to set to this instance. If empty then a new guid will be generated.
		*/
		Well(soap* soapContext,
			const std::string & guid,
			const std::string & title,
			const std::string & timeZone);

		Well(soap* soapContext,
			const std::string & guid,
			const std::string & title,
			const std::string & timeZone,
			const std::string & operator_,
			gsoap_witsml1_4_1_1::witsml1__WellStatus statusWell,
			gsoap_witsml1_4_1_1::witsml1__WellPurpose purposeWell,
			gsoap_witsml1_4_1_1::witsml1__WellFluid fluidWell,
			gsoap_witsml1_4_1_1::witsml1__WellDirection directionWell,
			const time_t & dTimSpud,
			const std::string & sourceName,
			const time_t & dTimCreation,
			const time_t & dTimLastChange,
			const std::string & comments
		);

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		Well(gsoap_witsml1_4_1_1::_witsml1__wells* fromGsoap):AbstractObject(fromGsoap)  {}

		/**
		* Destructor does nothing since the memory is managed by the gsoap context.
		*/
		~Well() {}

		Wellbore* createWellbore(
			const std::string & guid,
			const std::string & title);

		Wellbore* createWellbore(
			const std::string & guid,
			const std::string & title,
			gsoap_witsml1_4_1_1::witsml1__WellStatus statusWellbore,
			const bool & isActive,
			gsoap_witsml1_4_1_1::witsml1__WellPurpose purposeWellbore,
			gsoap_witsml1_4_1_1::witsml1__WellboreType typeWellbore,
			const bool & achievedTD,
			const std::string & sourceName,
			const time_t & dTimCreation,
			const time_t & dTimLastChange,
			const std::string & comments
		);

		void setOperator(const std::string & operator_);

		double getWellHeadEastingLocationValue();
		gsoap_witsml1_4_1_1::witsml1__LengthUom getWellHeadEastingLocationUom();
		double getWellHeadNorthingLocationValue();
		gsoap_witsml1_4_1_1::witsml1__LengthUom getWellHeadNorthingLocationUom();

		void setEastingNorthingLocation(
			gsoap_witsml1_4_1_1::witsml1__LengthUom uom,
			const double & easting,
			const double & northing,
			class CoordinateReferenceSystem* wellCrs);

		void setWestingSouthingLocation(
			gsoap_witsml1_4_1_1::witsml1__LengthUom uom,
			const double & westing,
			const double & southing,
			class CoordinateReferenceSystem* wellCrs);

		void setProjectedXProjectedYLocation(
			gsoap_witsml1_4_1_1::witsml1__LengthUom uom,
			const double & projectedX,
			const double & projectedY,
			class CoordinateReferenceSystem* wellCrs);

		soap* getGSoapContext() const {return collection->soap;}

		const std::vector<Wellbore*>& getWellbores() const {return wellboreSet;}

		const std::string & getTitle() const {return static_cast<gsoap_witsml1_4_1_1::_witsml1__wells*>(collection)->well[0]->name;}

		std::string getUuid() const {return *static_cast<gsoap_witsml1_4_1_1::_witsml1__wells*>(collection)->well[0]->uid;}
		time_t getCreation() const
		{
			if (static_cast<gsoap_witsml1_4_1_1::_witsml1__wells*>(collection)->well[0]->commonData->dTimCreation)
				return *static_cast<gsoap_witsml1_4_1_1::_witsml1__wells*>(collection)->well[0]->commonData->dTimCreation;
			else
				return -1;
		}
		time_t getLastUpdate() const
		{
			if (static_cast<gsoap_witsml1_4_1_1::_witsml1__wells*>(collection)->well[0]->commonData->dTimLastChange)
				return *static_cast<gsoap_witsml1_4_1_1::_witsml1__wells*>(collection)->well[0]->commonData->dTimLastChange;
			else
				return -1;
		}
		
		// KB
		void pushBackDatum(
			const std::string & guid, 
			const std::string & title,
			gsoap_witsml1_4_1_1::witsml1__ElevCodeEnum code,
			const unsigned int & datumIndex,
			gsoap_witsml1_4_1_1::witsml1__WellVerticalCoordinateUom elevationUnit,
			const double & elevation);

		// SL
		void pushBackDatum(
			const std::string & guid, 
			const std::string & title,
			gsoap_witsml1_4_1_1::witsml1__ElevCodeEnum code,
			const std::string & refNamingSystem,
			const std::string & refCode,
			const std::string & refName);

		unsigned int getDatumCount() const;

		gsoap_witsml1_4_1_1::witsml1__cs_USCOREwellDatum* getDatum(const unsigned int & index) const;
		gsoap_witsml1_4_1_1::witsml1__cs_USCOREwellDatum* getDatum(const std::string & uid) const;
		
		/**
		* Resolve all relationships of the object in an epc document.
		* Does nothing since there is no forward relationship.
		*/
		void importRelationshipSetFromEpc(common::EpcDocument* epcDoc);

		std::vector<epc::Relationship> getAllEpcRelationships() const;

		static const char* XML_TAG;
		virtual std::string getXmlTag() const {return XML_TAG;}

	protected:

		// backwards relationship
		std::vector<Wellbore*> wellboreSet;

		friend void Wellbore::setWell(Well* witsmlWell);
	};
}
