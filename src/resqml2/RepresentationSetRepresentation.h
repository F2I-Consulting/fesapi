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

#include "AbstractRepresentation.h"

namespace RESQML2_NS
{
	/**
	* The parent class of the framework representations. It is used to group together individual representations to represent a “bag” of representations. If the individual representations are all of the same, then you can indicate that the set is homogenous.
	* These “bags” do not imply any geologic consistency. For example, you can define a set of wellbore frames, a set of wellbore trajectories, a set of blocked wellbores. 
	* Because the framework representations inherit from this class, they inherit the capability to gather individual representations into sealed and non-sealed surface framework representations, or sealed volume framework representations.
	*/
	class RepresentationSetRepresentation : public RESQML2_NS::AbstractRepresentation
	{
	protected:
		RepresentationSetRepresentation() {}

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		RepresentationSetRepresentation(gsoap_resqml2_0_1::_resqml20__RepresentationSetRepresentation* fromGsoap) : RESQML2_NS::AbstractRepresentation(fromGsoap) {}

	public:

		/**
		* Only to be used in partial transfer context
		*/
		DLL_IMPORT_OR_EXPORT RepresentationSetRepresentation(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) :
			RESQML2_NS::AbstractRepresentation(partialObject)
		{
		}

		/**
		* Destructor does nothing since the memory is managed by the gsoap context.
		*/
		virtual ~RepresentationSetRepresentation() {}

		COMMON_NS::DataObjectReference getHdfProxyDor() const { return COMMON_NS::DataObjectReference(); }

		DLL_IMPORT_OR_EXPORT ULONG64 getXyzPointCountOfPatch(const unsigned int & patchIndex) const;

		/**
		* Get all the XYZ points of a particular patch of this representation.
		* XYZ points are given in the local CRS.
		* @param xyzPoints A linearized 2d array where the first (quickest) dimension is coordinate dimension (XYZ) and second dimension is vertex dimension. It must be pre allocated.
		*/
		DLL_IMPORT_OR_EXPORT void getXyzPointsOfPatch(const unsigned int & patchIndex, double * xyzPoints) const;

		DLL_IMPORT_OR_EXPORT unsigned int getPatchCount() const {return 1;}

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
		DLL_IMPORT_OR_EXPORT RESQML2_NS::AbstractRepresentation* getRepresentation(unsigned int index) const;

		/**
		* Get a particular representation dor of this representation set according to its position.
		*/
		gsoap_resqml2_0_1::eml20__DataObjectReference* getRepresentationDor(const unsigned int & index) const;

		/**
		* Get a particular representation uuid of this representation set according to its position.
		*/
		DLL_IMPORT_OR_EXPORT std::string getRepresentationUuid(const unsigned int & index) const;

		DLL_IMPORT_OR_EXPORT void pushBack(RESQML2_NS::AbstractRepresentation* rep);

		/**
		* The standard XML tag without XML namespace for serializing this data object.
		*/
		DLL_IMPORT_OR_EXPORT static const char* XML_TAG;

		/**
		* Get the standard XML tag without XML namespace for serializing this data object.
		*/
		DLL_IMPORT_OR_EXPORT virtual std::string getXmlTag() const { return XML_TAG; }

    protected:
		virtual void loadTargetRelationships();
	};
}
