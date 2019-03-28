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
	class RepresentationSetRepresentation : public RESQML2_NS::AbstractRepresentation
	{
	protected:
		RepresentationSetRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp) : AbstractRepresentation(interp, nullptr) {}

		RepresentationSetRepresentation() : AbstractRepresentation(nullptr, static_cast<RESQML2_NS::AbstractLocal3dCrs*>(nullptr)) {}

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		RepresentationSetRepresentation(gsoap_resqml2_0_1::_resqml2__RepresentationSetRepresentation* fromGsoap) : RESQML2_NS::AbstractRepresentation(fromGsoap) {}

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

		DLL_IMPORT_OR_EXPORT static const char* XML_TAG;
		DLL_IMPORT_OR_EXPORT virtual std::string getXmlTag() const;

		gsoap_resqml2_0_1::eml20__DataObjectReference* getHdfProxyDor() const {return nullptr;}

		DLL_IMPORT_OR_EXPORT ULONG64 getXyzPointCountOfPatch(const unsigned int & patchIndex) const;

		/**
		* Get all the XYZ points of a particular patch of this representation.
		* XYZ points are given in the local CRS.
		* @param xyzPoints A linearized 2d array where the first (quickest) dimension is coordinate dimension (XYZ) and second dimension is vertex dimension. It must be pre allocated.
		*/
		DLL_IMPORT_OR_EXPORT void getXyzPointsOfPatch(const unsigned int & patchIndex, double * xyzPoints) const;

		DLL_IMPORT_OR_EXPORT unsigned int getPatchCount() const {return 0;}

		/**
		* Indicates if the representation set contains only one type of representations or several.
		*/
		DLL_IMPORT_OR_EXPORT bool isHomogeneous() const;

		/**
		* Get the count of representations in this representation set.
		*/
		DLL_IMPORT_OR_EXPORT unsigned int getRepresentationCount() const;

		/**
		* Get a particular representation of this representation set according to its position.
		*/
		DLL_IMPORT_OR_EXPORT RESQML2_NS::AbstractRepresentation* getRepresentation(const unsigned int & index) const;

		/**
		* Get a particular representation dor of this representation set according to its position.
		*/
		gsoap_resqml2_0_1::eml20__DataObjectReference* getRepresentationDor(const unsigned int & index) const;

		/**
		* Get a particular representation uuid of this representation set according to its position.
		*/
		DLL_IMPORT_OR_EXPORT std::string getRepresentationUuid(const unsigned int & index) const;

		DLL_IMPORT_OR_EXPORT virtual std::vector<epc::Relationship> getAllTargetRelationships() const;
		DLL_IMPORT_OR_EXPORT virtual void resolveTargetRelationships(COMMON_NS::EpcDocument* epcDoc);

    protected:

		void pushBackXmlRepresentation(RESQML2_NS::AbstractRepresentation* rep);

		friend void RESQML2_NS::AbstractRepresentation::pushBackIntoRepresentationSet(RepresentationSetRepresentation * repSet, bool xml);
	};
}
