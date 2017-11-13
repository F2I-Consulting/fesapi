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

#include "resqml2_0_1/WellboreFrameRepresentation.h"

namespace witsml1_4_1_1
{
	class FormationMarker;
}

namespace resqml2_0_1
{
	class DLL_IMPORT_OR_EXPORT WellboreMarkerFrameRepresentation : public WellboreFrameRepresentation
	{
	public:

		/**
		* Only to be used in partial transfer context
		*/
		WellboreMarkerFrameRepresentation(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) :
			WellboreFrameRepresentation(partialObject)
		{
		}

		/**
		* Creates an instance of this class in a gsoap context.
		* @param interp		The WellboreFeature interpretation the instance represents.
		* @param guid		The guid to set to the new instance. If empty then a new guid will be generated.
		* @param title		A title for the instance to create.
		* @param traj		The trajectory this WellboreFeature frame is based on.
		*/
		WellboreMarkerFrameRepresentation(class WellboreInterpretation* interp, const std::string & guid, const std::string & title, class WellboreTrajectoryRepresentation * traj);

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		WellboreMarkerFrameRepresentation(gsoap_resqml2_0_1::_resqml2__WellboreMarkerFrameRepresentation* fromGsoap) : WellboreFrameRepresentation(fromGsoap), stratigraphicOccurrenceInterpretation(nullptr) {}

		// clean the owned markers
		~WellboreMarkerFrameRepresentation();

		/**
		* Pushes back a new WellboreFeature marker to this WellboreFeature marker frame.
		* One WellboreFeature marker must be added per MD of the WellboreFeature marker frame.
		*/
		class WellboreMarker* pushBackNewWellboreMarker(const std::string & guid, const std::string & title);

		/**
		* Add a WellboreFeature marker to this WellboreFeature marker frame with a geologic information on the intersected feature.
		* One WellboreFeature marker must be added per MD of the WellboreFeature marker frame.
		*/
		class WellboreMarker* pushBackNewWellboreMarker(const std::string & guid, const std::string & title, const gsoap_resqml2_0_1::resqml2__GeologicBoundaryKind & geologicBoundaryKind);

		/**
		* Return the number of wellbore marker for this Wellbore marker frame representation
		*/
		unsigned int getWellboreMarkerCount();

		/**
		* Get all the wellbore markers of this well marker frame representation.
		*/
		const std::vector<class WellboreMarker*> & getWellboreMarkerSet() const { return markerSet; }

		void setStratigraphicOccurrenceInterpretation(class StratigraphicOccurrenceInterpretation * stratiOccurenceInterp);

		/**
		* Set the correspondance between the interval of the wellbore marker frame rep and the units of a stratiColRankInterp
		* @param stratiUnitIndices	The count must be equal to the count of contacts in stratiColRankInterp
		* @param nullValue			The value which is used to indicate we don't know the related strati units against a particular interval.
		*/
		void setIntervalStratigraphicUnits(unsigned int * stratiUnitIndices, const unsigned int & nullValue, class StratigraphicOccurrenceInterpretation* stratiOccurenceInterp);

		class StratigraphicOccurrenceInterpretation* getStratigraphicOccurrenceInterpretation() { return stratigraphicOccurrenceInterpretation; }

		void setWitsmlFormationMarker(const unsigned int & resqmlMarkerIndex, witsml1_4_1_1::FormationMarker * witsmlFormationMarker);

		static const char* XML_TAG;
		virtual std::string getXmlTag() const {return XML_TAG;}

	protected:

		std::vector<epc::Relationship> getAllEpcRelationships() const;
		void importRelationshipSetFromEpc(common::EpcDocument* epcDoc);

		// XML forward relationships
		std::vector<witsml1_4_1_1::FormationMarker*> witsmlFormationMarkerSet;
		class StratigraphicOccurrenceInterpretation* stratigraphicOccurrenceInterpretation;

		// only memory relationship
		std::vector<class WellboreMarker*> markerSet;
	};
}
