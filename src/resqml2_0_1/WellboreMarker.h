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

#include "common/AbstractObject.h"

namespace resqml2_0_1
{
	/**
	* This class is one of the only one to be a ResqmlDataObject which is not exported into a single file i.e. not a top level element.
	* Consequently its behaviour is slightly different than other class. Especially there is no integration of the instances into an EPC document.
	*/
	class DLL_IMPORT_OR_EXPORT WellboreMarker : public common::AbstractObject
	{
	public:

		/**
		* Creates an instance of this class in a gsoap context.
		* @param wellboreMarkerFrame	The wellbore marker frame which contains the wellbore marker to contruct.
		* @param guid					The guid to set to the new instance. If empty then a new guid will be generated.
		* @param title					A title for the instance to create.
		*/
		WellboreMarker(class WellboreMarkerFrameRepresentation* wellboreMarkerFrame, const std::string & guid, const std::string & title);

		/**
		* Creates an instance of this class in a gsoap context.
		* @param wellboreMarkerFrame	The wellbore marker frame which contains the wellbore marker to contruct.
		* @param guid					The guid to set to the new instance. If empty then a new guid will be generated.
		* @param title					A title for the instance to create.
		* @param geologicBoundaryKind	The type of the feature which the marker intersects.
		*/
		WellboreMarker(class WellboreMarkerFrameRepresentation* wellboreMarkerFrame, const std::string & guid, const std::string & title, const gsoap_resqml2_0_1::resqml2__GeologicBoundaryKind & geologicBoundaryKind);

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		WellboreMarker(gsoap_resqml2_0_1::resqml2__WellboreMarker* fromGsoap, class WellboreMarkerFrameRepresentation* wellboreMarkerFrame) : AbstractObject(fromGsoap), boundaryFeatureInterpretation(nullptr), wellboreMarkerFrameRepresentation(wellboreMarkerFrame)  {}

		/**
		* Destructor
		*/
		~WellboreMarker() {}

		/**
		* Indicates if the marker is associated to a particular GeologicBoundaryKind.
		*/
		bool hasAGeologicBoundaryKind();

		/**
		* Get the type of the intersected feature of the marker.
		* Throw an exception if the marker has no GeologicBoundaryKind (see method hasAGeologicBoundaryKind).
		*/
		gsoap_resqml2_0_1::resqml2__GeologicBoundaryKind getGeologicBoundaryKind();

		class WellboreMarkerFrameRepresentation * getWellMarkerFrameRepresentation() {return wellboreMarkerFrameRepresentation;}

		/**
		* Get the boundary feature interpretation linked to this well marker.
		*/
		class BoundaryFeatureInterpretation* getBoundaryFeatureInterpretation() const {return boundaryFeatureInterpretation;}

		/**
		* Get the UUID of the boundary feature interpretation linked to this well marker.
		* Especially useful in partial transfer mode.
		*/
		std::string getBoundaryFeatureInterpretationUuid() const;

		/**
		* Set the boundary feature interpretation linked to this well marker.
		*/
		void setBoundaryFeatureInterpretation(class BoundaryFeatureInterpretation* interp);

		static const char* XML_TAG;
		virtual std::string getXmlTag() const {return XML_TAG;}

	private:

		// No need these two inherited methods since WellboreMarker is not an EPC top level element.
		std::vector<epc::Relationship> getAllEpcRelationships() const {std::vector<epc::Relationship> result; return result;}
		void importRelationshipSetFromEpc(common::EpcDocument* epcDoc) {};

		class BoundaryFeatureInterpretation* boundaryFeatureInterpretation;
		class WellboreMarkerFrameRepresentation* wellboreMarkerFrameRepresentation;
	};
}
