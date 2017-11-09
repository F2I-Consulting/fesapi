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
#ifndef FILE_CORE_PROPERTIES_H
#define FILE_CORE_PROPERTIES_H

#include "CoreProperty.h"

namespace epc
{
	class FileCoreProperties
	{
	private:
		CoreProperty properties[CoreProperty::undefinedCoreProperty];

	public:
		FileCoreProperties();
		~FileCoreProperties() {}

		CoreProperty getProperty(const CoreProperty::TypeProperty & index) const;
		std::string toString() const;

		/**
		* Initialize all the core properties with their default values.
		* If a core property has not default value then this method keep it unchanged.
		*/
		void initDefaultCoreProperties();

		void setCategory(const std::string & value);
		void setContentStatus(const std::string & value);
		void setCreated(const std::string & value);
		void setCreator(const std::string & value);
		void setDescription(const std::string & value);
		void setIdentifier(const std::string & value);
		void setKeywords(const std::string & value);
		void addKeywords(const std::string & value);
		void setLanguage(const std::string & value);
		void setLastModifiedBy(const std::string & value);
		void setLastPrinted(const std::string & value);
		void setModified(const std::string & value);
		void setRevision(const std::string & value);
		void setSubject(const std::string & value);
		void setTitle(const std::string & value);
		void setVersion(const std::string & value);

		/**
		* Read a core properties part from a string.
		*/
		void readFromString(const std::string & textInput);
	};
}

#endif
