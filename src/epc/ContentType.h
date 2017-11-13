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
#ifndef CONTENT_TYPE_H
#define CONTENT_TYPE_H

#include <string>

namespace epc
{
	class ContentType
	{
	private:
		std::string contentTypeString;
		std::string extensionOrPartName;

	public:
		bool isAssociatedToAnExtension; /// if false, the content type is associated to a part and overrides another content type.

		// The part URI grammar is defined as follows: 
		// part-URI  = 1*( "/" segment ) 
		// segment   = 1*( pchar ) 
		// pchar is defined in RFC 3986
		//
		// The part URI grammar implies the following constraints. The package implementer shall neither create any part 
		// that violates these constraints nor retrieve any data from a package as a part if the purported part URI violates 
		// these constraints.  
		// *  A part URI shall not be empty. [Note: The Mx.x notation is discussed in ?2. end note] 
		// *  A part URI shall not have empty segments.
		// *  A part URI shall start with a forward slash (?/?) character.
		// *  A part URI shall not have a forward slash as the last character.
		// *  A segment shall not hold any characters other than pchar characters.
		// Part URI segments have the following additional constraints. The package implementer shall neither create any 
		// part with a part URI comprised of a segment that violates these constraints nor retrieve any data from a package 
		// as a part if the purported part URI contains a segment that violates these constraints. 
		// *  A segment shall not contain percent-encoded forward slash (?/?), or backward slash (?\?) characters.
		// *  A segment shall not contain percent-encoded unreserved characters.
		// *  A segment shall not end with a dot (?.?) character.
		// *  A segment shall include at least one non-dot character.

		ContentType(){};
		ContentType(const bool & isAssociatedToAnExtension, const std::string & contentType, const std::string & extensionOrPartName);
		~ContentType() {};

		// GETTTERS
		const std::string & getContentTypeString() const;
		const std::string & getExtensionOrPartName() const;

		// SETTERS
		void setContentTypeString(const std::string & ctString) {contentTypeString = ctString;}
		void setExtensionOrPartName(const std::string & extensionOrPartName) {this->extensionOrPartName = extensionOrPartName;}

		std::string toString() const;
	};
}

#endif
