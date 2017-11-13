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

#include "resqml2/AbstractRepresentation.h"

namespace resqml2
{
	class DLL_IMPORT_OR_EXPORT RepresentationSetRepresentation : public resqml2::AbstractRepresentation
	{
	protected:
		RepresentationSetRepresentation(resqml2::AbstractFeatureInterpretation* interp) : AbstractRepresentation(interp, nullptr) {}

		RepresentationSetRepresentation() : AbstractRepresentation(nullptr, static_cast<resqml2::AbstractLocal3dCrs*>(nullptr)) {}

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		RepresentationSetRepresentation(gsoap_resqml2_0_1::_resqml2__RepresentationSetRepresentation* fromGsoap) : resqml2::AbstractRepresentation(fromGsoap) {}

		gsoap_resqml2_0_1::resqml2__PointGeometry* getPointGeometry2_0_1(const unsigned int & patchIndex) const { return nullptr; }

	public:

		/**
		* Only to be used in partial transfer context
		*/
		RepresentationSetRepresentation(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) :
			resqml2::AbstractRepresentation(partialObject)
		{
		}

		/**
		* Destructor does nothing since the memory is managed by the gsoap context.
		*/
		virtual ~RepresentationSetRepresentation() {}

		static const char* XML_TAG;
		virtual std::string getXmlTag() const;

		std::string getHdfProxyUuid() const {return "";}


		ULONG64 getXyzPointCountOfPatch(const unsigned int & patchIndex) const;

		/**
		* Get all the XYZ points of a particular patch of this representation.
		* XYZ points are given in the local CRS.
		* @param xyzPoints A linearized 2d array where the first (quickest) dimension is coordinate dimension (XYZ) and second dimension is vertex dimension. It must be pre allocated.
		*/
		void getXyzPointsOfPatch(const unsigned int & patchIndex, double * xyzPoints) const;

		unsigned int getPatchCount() const {return 0;}

		/**
		* Indicates if the representation set contains only one type of representations or several.
		*/
		bool isHomogeneous() const;

		/**
		* Get the count of representations in this representation set.
		*/
		unsigned int getRepresentationCount() const;

		/**
		* Get a particular representation of this representation set according to its position.
		*/
		resqml2::AbstractRepresentation* getRepresentation(const unsigned int & index) const;

		/**
		* Get a particular representation dor of this representation set according to its position.
		*/
		gsoap_resqml2_0_1::eml20__DataObjectReference* getRepresentationDor(const unsigned int & index) const;

		/**
		* Get a particular representation uuid of this representation set according to its position.
		*/
		std::string getRepresentationUuid(const unsigned int & index) const;

    protected:

		void pushBackXmlRepresentation(resqml2::AbstractRepresentation* rep);

		virtual std::vector<epc::Relationship> getAllEpcRelationships() const;
		virtual void importRelationshipSetFromEpc(common::EpcDocument* epcDoc);

		friend void resqml2::AbstractRepresentation::pushBackIntoRepresentationSet(RepresentationSetRepresentation * repSet, bool xml);
	};
}
