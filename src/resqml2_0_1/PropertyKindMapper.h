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

#if defined(_WIN32) || defined(__APPLE__)
#include <unordered_map>
#else
#include <tr1/unordered_map>
#endif

#include "common/EpcDocument.h"

namespace resqml2_0_1
{
	class DLL_IMPORT_OR_EXPORT PropertyKindMapper
	{
	public:
		PropertyKindMapper(common::EpcDocument* epcDoc):epcDocument(epcDoc) {}
		~PropertyKindMapper() {}

		/**
		* Load in maps all the config files present in a particular directory.
		* Config files are all xml files (extension must be .xml). One of this xml file must be named PropertyKindMapping.xml.
		* PropertyKindMapping.xml is the only file to make the mapping with the standard property types.
		* All others xml files must be local property kinds mapping.
		* @param directory The directory must not end with any slash
		*/
		std::string loadMappingFilesFromDirectory(const std::string & directory);

		/**
		 * Get the name of a resqml standard property kind into a particular application.
		 *
		 * @param  	resqmlStandardPropertyKindName	The enumerated resqml standard property kind name
		 * @apram	application						The name of the application
		 * @return	The property kind name in the particular application. Or an empty string if not found.
		 */
		std::string getApplicationPropertyKindNameFromResqmlStandardPropertyKindName(const gsoap_resqml2_0_1::resqml2__ResqmlPropertyKind & resqmlStandardPropertyKindName, const std::string & application) const;

		/**
		 * @apram	application						The name of the application
		 * @return	The abstract Resqml root property name if no resqml standard property name have been found for this particular application property kind name.
		 */
		gsoap_resqml2_0_1::resqml2__ResqmlPropertyKind getResqmlStandardPropertyKindNameFromApplicationPropertyKindName(const std::string & applicationPropertyKindName, const std::string & application) const;

		/**
		 * @apram	application						The name of the application
		 * @return	empty string if not found
		 */
		std::string getApplicationPropertyKindNameFromResqmlLocalPropertyKindUuid(const std::string & resqmlLocalPropertyKindUuid, const std::string & application) const;

		/**
		* @return empty string if not found
		*/
		std::string getResqmlLocalPropertyKindUuidFromApplicationPropertyKindName(const std::string & applicationPropertyKindName, const std::string & application) const;

		/**
		* Add a resqml local property type into the EPC document given in constructor if not already present in EPC document.
		* This addition will also add all needed resqml local property type parent into the EPC document.
		*/
		class PropertyKind* addResqmlLocalPropertyKindToEpcDocumentFromApplicationPropertyKindName(const std::string & applicationPropertyKindName, const std::string & application);

		/**
		 * Get the title of the parent of a Resqml Standard PropertyKind.
		 */
		gsoap_resqml2_0_1::resqml2__ResqmlPropertyKind getPropertyKindParentOfResqmlStandardPropertyKindName(const gsoap_resqml2_0_1::resqml2__ResqmlPropertyKind & resqmlStandardPropertyKindName) const;

		/**
		 * Get the description of a Resqml Standard PropertyKind.
		 */
		std::string getDescriptionOfResqmlStandardPropertyKindName(const gsoap_resqml2_0_1::resqml2__ResqmlPropertyKind & resqmlStandardPropertyKindName) const;

		/**
		* Check if a resqml property kind is a child of another one.
		* @param child	The resqml property kind which is supposed to be the child
		* @param parent	The resqml property kind which is supposed to be the parent
		*/
		bool isChildOf(gsoap_resqml2_0_1::resqml2__ResqmlPropertyKind child, gsoap_resqml2_0_1::resqml2__ResqmlPropertyKind parent) const;

		/**
		* Check if a resqml property kind is an abstract one or not.
		* @param resqmlStandardPropertyKindName	The resqml property kind to test
		*/
		bool isAbstract(gsoap_resqml2_0_1::resqml2__ResqmlPropertyKind resqmlStandardPropertyKindName) const;

	private:
		common::EpcDocument * epcDocument;


#if (defined(_WIN32) && _MSC_VER >= 1600)
		std::unordered_map<gsoap_resqml2_0_1::resqml2__ResqmlPropertyKind, gsoap_resqml2_0_1::ptm__standardEnergisticsPropertyType*> resqmlStandardPropertyKindNameToApplicationPropertyKindName;
		std::unordered_map<std::string, std::unordered_map<std::string, gsoap_resqml2_0_1::resqml2__ResqmlPropertyKind> > applicationPropertyKindNameToResqmlStandardPropertyKindName; // First key string is the application name Second key string is the application property kind name.

		std::unordered_map<std::string, std::unordered_map<std::string, std::string> > resqmlLocalPropertyKindUuidToApplicationPropertyKindName; // First key string is the application name, second is the uuid of the resqml local property.
		std::unordered_map<std::string, std::unordered_map<std::string, std::string> > applicationPropertyKindNameToResqmlLocalPropertyKindUuid;

		std::unordered_map<std::string, gsoap_resqml2_0_1::_resqml2__PropertyKind*> resqmlLocalPropertyKindUuidToResqmlLocalPropertyKind;
#elif defined(__APPLE__)
		std::unordered_map<gsoap_resqml2_0_1::resqml2__ResqmlPropertyKind, gsoap_resqml2_0_1::ptm__standardEnergisticsPropertyType*, std::hash<int> > resqmlStandardPropertyKindNameToApplicationPropertyKindName;
		std::unordered_map<std::string, std::unordered_map<std::string, gsoap_resqml2_0_1::resqml2__ResqmlPropertyKind> > applicationPropertyKindNameToResqmlStandardPropertyKindName;

		std::unordered_map<std::string, std::unordered_map<std::string, std::string> > resqmlLocalPropertyKindUuidToApplicationPropertyKindName;
		std::unordered_map<std::string, std::unordered_map<std::string, std::string> > applicationPropertyKindNameToResqmlLocalPropertyKindUuid;

		std::unordered_map<std::string, gsoap_resqml2_0_1::_resqml2__PropertyKind*> resqmlLocalPropertyKindUuidToResqmlLocalPropertyKind;
#else
		std::tr1::unordered_map<gsoap_resqml2_0_1::resqml2__ResqmlPropertyKind, gsoap_resqml2_0_1::ptm__standardEnergisticsPropertyType*, std::tr1::hash<int> > resqmlStandardPropertyKindNameToApplicationPropertyKindName;
		std::tr1::unordered_map< std::string, std::tr1::unordered_map<std::string, gsoap_resqml2_0_1::resqml2__ResqmlPropertyKind> > applicationPropertyKindNameToResqmlStandardPropertyKindName;

		std::tr1::unordered_map< std::string, std::tr1::unordered_map<std::string, std::string> > resqmlLocalPropertyKindUuidToApplicationPropertyKindName;
		std::tr1::unordered_map< std::string, std::tr1::unordered_map<std::string, std::string> > applicationPropertyKindNameToResqmlLocalPropertyKindUuid;

		std::tr1::unordered_map<std::string, gsoap_resqml2_0_1::_resqml2__PropertyKind*> resqmlLocalPropertyKindUuidToResqmlLocalPropertyKind;
#endif

	};
}
