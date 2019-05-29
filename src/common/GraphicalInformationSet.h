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
		* @param packageDirAbsolutePath		The directory where the EPC document is stored. Must end with a slash or back-slash
		* @param externalFilePath			The relative path regarding packageDirectoryAbsolutePath where the external resource is located
		*/
		GraphicalInformationSet(soap* soapContext, const std::string & guid, const std::string & title);

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

	protected:

		void resolveTargetRelationships(common::EpcDocument* epcDoc) {}

		DLL_IMPORT_OR_EXPORT std::vector<epc::Relationship> getAllSourceRelationships() const;
		DLL_IMPORT_OR_EXPORT std::vector<epc::Relationship> getAllTargetRelationships() const;
	};
}
