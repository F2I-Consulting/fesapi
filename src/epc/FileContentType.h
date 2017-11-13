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
#ifndef FILE_CONTENT_TYPE_H
#define FILE_CONTENT_TYPE_H

#if defined(_WIN32) || defined(__APPLE__)
#include <unordered_map>
#else
#include <tr1/unordered_map>
#endif

#include "ContentType.h"

namespace epc
{

	class FileContentType
	{
    public:

#if (defined(_WIN32) && _MSC_VER >= 1600) || defined(__APPLE__)
		typedef std::unordered_map<std::string, ContentType> ContentTypeMap;
#else
		typedef std::tr1::unordered_map<std::string, ContentType> ContentTypeMap;
#endif

	private:
		static const char* header;
		ContentTypeMap contentTypeMap;
		static const char* footer;

	public:
		// CONSTRUCTORS
		FileContentType();
		~FileContentType() {};

		// ACCESSORS
		ContentType getContentType(const std::string& extensionOrPartName) const;
		const ContentTypeMap& getAllContentType() const;
		std::string toString() const;

		void addContentType(const ContentType & contentType);

		/**
		* Read a content type part from a string.
		*/
		void readFromString(const std::string & textInput);
	};
}

#endif
