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

#include "resqml2/AbstractRepresentation.h"

namespace RESQML2_NS
{
	class DLL_IMPORT_OR_EXPORT RepresentationSetRepresentation : public RESQML2_NS::AbstractRepresentation
	{
	protected:
		RepresentationSetRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp) : AbstractRepresentation(interp, nullptr) {}

		RepresentationSetRepresentation() : AbstractRepresentation(nullptr, static_cast<RESQML2_NS::AbstractLocal3dCrs*>(nullptr)) {}

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		RepresentationSetRepresentation(gsoap_resqml2_0_1::_resqml2__RepresentationSetRepresentation* fromGsoap) : RESQML2_NS::AbstractRepresentation(fromGsoap) {}

		gsoap_resqml2_0_1::resqml2__PointGeometry* getPointGeometry2_0_1(const unsigned int & patchIndex) const { return nullptr; }

	public:

		/**
		* Only to be used in partial transfer context
		*/
		RepresentationSetRepresentation(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) :
			RESQML2_NS::AbstractRepresentation(partialObject)
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
		RESQML2_NS::AbstractRepresentation* getRepresentation(const unsigned int & index) const;

		/**
		* Get a particular representation dor of this representation set according to its position.
		*/
		gsoap_resqml2_0_1::eml20__DataObjectReference* getRepresentationDor(const unsigned int & index) const;

		/**
		* Get a particular representation uuid of this representation set according to its position.
		*/
		std::string getRepresentationUuid(const unsigned int & index) const;
		virtual std::vector<epc::Relationship> getAllTargetRelationships() const;

    protected:

		void pushBackXmlRepresentation(RESQML2_NS::AbstractRepresentation* rep);

		virtual void importRelationshipSetFromEpc(COMMON_NS::EpcDocument* epcDoc);

		friend void RESQML2_NS::AbstractRepresentation::pushBackIntoRepresentationSet(RepresentationSetRepresentation * repSet, bool xml);
	};
}

