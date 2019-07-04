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

#include "common/AbstractObject.h"

namespace common
{
	class GraphicalInformationSet : public common::AbstractObject
	{
	private:
		gsoap_eml2_2::resqml2__DefaultGraphicalInformation* getDefaultGraphicalInformationForAllIndexableElements(common::AbstractObject* targetObject) const;
		gsoap_eml2_2::resqml2__GraphicalInformationForWholeObject* getDefaultGraphicalInformation(common::AbstractObject* targetObject) const;
		gsoap_eml2_2::resqml2__HsvColor* getDefaultColor(common::AbstractObject* targetObject) const;

	public:
		/**
		* @param repo		The repository where the underlying gsoap proxy is going to be created.
		* @param guid		The guid to set to graphical information set.
		* @param title		A title for graphical information set.
		*/
		GraphicalInformationSet(COMMON_NS::DataObjectRepository* repo, const std::string & guid, const std::string & title);

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		GraphicalInformationSet(gsoap_eml2_2::_eml22__GraphicalInformationSet* fromGsoap) :
			common::AbstractObject(fromGsoap) {}

		/**
		* Destructor does nothing since the memory is managed by the gsoap context.
		*/
		~GraphicalInformationSet() {}

		/**
		* @return	Get the size of the GraphicalInformationSet.
		*/
		DLL_IMPORT_OR_EXPORT unsigned int getGraphicalInformationSetCount() const;

		/**
		* @return	Get the data objet reference of the object which receives some graphical information at a particular index of the GraphicalInformationSet.
		*/
		gsoap_eml2_2::eml22__DataObjectReference* getTargetObjectDor(unsigned int index) const;

		/**
		* @return	Get the Uuid of the object which receives some graphical information at a particular index of the GraphicalInformationSet.
		*/
		DLL_IMPORT_OR_EXPORT std::string getTargetObjectUuid(unsigned int index) const;

		/**
		* Get the object which receives some graphical information at a particular index of the GraphicalInformationSet
		*/
		DLL_IMPORT_OR_EXPORT common::AbstractObject* getTargetObject(unsigned int index) const;

		/**
		* @param targetObject	The object whiwh we want tot est for its presency in the Graphical Information Set
		* @return true if the Graphical Information Set has graphical information about the target object.
		*/
		DLL_IMPORT_OR_EXPORT bool hasGraphicalInformation(const common::AbstractObject* targetObject) const;

		DLL_IMPORT_OR_EXPORT bool hasDefaultColor(common::AbstractObject* targetObject) const;
		DLL_IMPORT_OR_EXPORT double getDefaultHue(common::AbstractObject* targetObject) const;
		DLL_IMPORT_OR_EXPORT double getDefaultSaturation(common::AbstractObject* targetObject) const;
		DLL_IMPORT_OR_EXPORT double getDefaultValue(common::AbstractObject* targetObject) const;
		DLL_IMPORT_OR_EXPORT double getDefaultAlpha(common::AbstractObject* targetObject) const;

		/**
		* https://en.wikipedia.org/wiki/HSV_color_space
		* @param targetObject	The object which receives the color
		* @param hue			angle in degrees in the range [0, 360]
		* @param saturation		numeric value in the range [0, 1]
		* @param value			numeric value in the range [0, 1]
		* @param alpha			numeric value in the range [0, 1] for alpha transparency channel (0 means transparent and 1 means opaque).
		*/
		DLL_IMPORT_OR_EXPORT void setDefaultHsvColor(common::AbstractObject* targetObject, double hue, double saturation, double value, double alpha = 1.0);

		DLL_IMPORT_OR_EXPORT static const char* XML_TAG;
		DLL_IMPORT_OR_EXPORT std::string getXmlTag() const { return XML_TAG; }
		DLL_IMPORT_OR_EXPORT std::string getXmlNamespace() const {
			return "eml22";
		}

		void loadTargetRelationships() const;
	};
}
