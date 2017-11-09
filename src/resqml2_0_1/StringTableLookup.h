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
	class DLL_IMPORT_OR_EXPORT StringTableLookup : public common::AbstractObject
	{
	public:

		/**
		* Only to be used in partial transfer context
		*/
		StringTableLookup(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : common::AbstractObject(partialObject) {}

		/**
		* Default constructor
		*/
		StringTableLookup() {}

		/**
		* Creates an instance of this class in a gsoap context.
		* @param soap		A gsoap context wihch will manage the memory and the serialization/deserialization of this instance.
		* @param guid		The guid to set to this instance. If empty then a new guid will be generated.
		* @param title		A title for the instance to create.
		*/
		StringTableLookup(soap* soapContext, const std::string & guid, const std::string & title);

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		StringTableLookup(gsoap_resqml2_0_1::_resqml2__StringTableLookup* fromGsoap) : AbstractObject(fromGsoap) {}

		/**
		* Destructor does nothing since the memory is managed by the gsoap context.
		*/
		~StringTableLookup() {}
		
		static const char* XML_TAG;
		virtual std::string getXmlTag() const {return XML_TAG;}

		/**
		* Add a categorical property values object which uses this string lookup.
		* Does not add the inverse relationship i.e. from the categorical property values object to this string lookup.
		*/
		void addCategoricalPropertyValues(class CategoricalProperty* categVal) {categoricalPropertyValuesSet.push_back(categVal);}

		/**
		* Check wether a key value is contained within this string lookup or not.
		*/
		bool containsKey(const long & longValue);

		/**
		* Get the count of item in the stringTableLookup (in the map).
		*/
		unsigned int getItemCount() const;

		/**
		* Get the key of a string value pair at a particular index in the string table lookup (in the map)
		*/
		long getKeyAtIndex(const unsigned int & index) const;

		/**
		* Get the string value of a string value pair at a particular index in the string table lookup (in the map)
		*/
		std::string getStringValueAtIndex(const unsigned int & index) const;

		/**
		* Get a string value from its associated key (long) value.
		* If the key value does not exist, an empty string is returned.
		*/
		std::string getStringValue(const long & longValue);

		/**
		* Add a pair value to the string lookup.
		* No verification that the key value (or string value) already exists
		*/
		void addValue(const std::string & strValue, const long & longValue);

		/**
		* Modify the associated string value according to the key (long) value.
		* If the key value does not exist, nothing is done.
		*/
		void setValue(const std::string & strValue, const long & longValue);

		/*
		* Getter for the underlying map of the string lookup.
		*/
#if (defined(_WIN32) && _MSC_VER >= 1600) || defined(__APPLE__)
		std::unordered_map<long, std::string> getMap() const;
#else
		std::tr1::unordered_map<long, std::string> getMap() const;
#endif

	protected:

		std::vector<epc::Relationship> getAllEpcRelationships() const;
		/**
		* Does nothing since StringTableLookup has not got any forward relationship.
		*/
		void importRelationshipSetFromEpc(common::EpcDocument* epcDoc) {}

		// XML backwards relationships
		std::vector<class CategoricalProperty*> categoricalPropertyValuesSet;
	};
}
