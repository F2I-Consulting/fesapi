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
#ifndef CORE_PROPERTY_H
#define CORE_PROPERTY_H

#include <vector>
#include <string>

namespace epc
{
	class CoreProperty
	{		
	public:

		/**
		* Enumeration of the various types of the core properties.
		*/
		enum TypeProperty {
			category = 0,
			contentStatus = 1,
			created = 2,
			creator = 3,
			description = 4,
			identifier = 5,
			keywords = 6,
			language = 7,
			lastModifiedBy = 8,
			lastPrinted = 9,
			modified = 10,
			revision = 11,
			subject = 12,
			title = 13,
			version = 14,
			undefinedCoreProperty = 15
		};

		CoreProperty();
		CoreProperty(const TypeProperty & pType);
		CoreProperty(const TypeProperty & pType, const std::string & pValue);
		CoreProperty(const TypeProperty & pType, const std::vector<std::string> & pValue);
		~CoreProperty() {}

		/**
		* Indicate wether a property has got a string value or not
		*/
		bool isEmpty() const;

		/**
		* Get the type of the core property.
		*/
		TypeProperty getTypeProperty() const;

		/**
		* Set the type of the core property
		*/
		void setTypeProperty(const TypeProperty & corePropertyType);

		/**
		* Get all the string values. Relevant only for some core properties which can have several string values (such as keywords)
		*/
		std::vector<std::string> getAllValue() const;

		/**
		* Get the first string value of the core property.
		* Usually this method is the common one for retrieving string value of a core property since most of timeonly one string value is necessary for one core property.
		*/
		std::string getValue(const int & index = 0) const;

		/**
		* Serialize the core property into an XML element embeded into a string.
		*/
		std::string toString() const;

		void setCategory(std::string pValue);
		void setContentStatus(std::string pValue);
		void setCreated(std::string pValue);
		void setCreator(std::string pValue);
		void setDescription(std::string pValue);
		void setIdentifier(std::string pValue);
		void setKeywords(std::string pValue);
		void addKeywords(std::string pValue);
		void setLanguage(std::string pValue);
		void setLastModifiedBy(std::string pValue);
		void setLastPrinted(std::string pValue);
		void setModified(std::string pValue);
		void setRevision(std::string pValue);
		void setSubject(std::string pValue);
		void setTitle(std::string pValue);
		void setVersion(std::string pValue);
		
	private:
		TypeProperty type;				/// The type of the core property
		std::vector<std::string> value;	/// The string value of the core property. Can be multiple for some core properties (such as keywords)
	};
}

#endif
