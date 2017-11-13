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
#ifndef RELATIONSHIP_H
#define RELATIONSHIP_H

#include <string>

namespace epc
{
	/**
	* This class intends to represent a relationship entry of a rel file of a package part.
	*/
	class Relationship
	{
	private: 
		bool internalTarget;	/// The target mode indicates wether the destination part is external or internal to the package.
		std::string target;			/// The target indicates the destination part path.
		std::string type;			/// The type indicates the name/type of the relationship.
		std::string id;				/// The id uniquely identify the relationship in the context of the rel file. For epc, it also indicates the uuid of the destiantion object.

	public:
		Relationship(const bool & internalTarget = true);
		Relationship(const std::string & rsTarget, const std::string & rsType,const std::string & rsId, const bool & internalTarget = true);
		~Relationship() {}

		/**
		* Serialize the core property into an XML element embeded into a string.
		*/
		std::string toString() const;

		bool isInternalTarget() const;
		const std::string& getTarget() const;
		const std::string& getType() const;
		const std::string& getId() const;

		void setIsExternalTarget();
		void setIsInternalTarget();
		void setTarget(const std::string & rsTarget);

		/**
		* Set an arbitrary type to the relationship
		*/
		void setType(const std::string & rsType);

		// Set predefined types to the relationship
		void setDestinationObjectType()		{type = "http://schemas.energistics.org/package/2012/relationships/destinationObject";}
		void setSourceObjectType()			{type = "http://schemas.energistics.org/package/2012/relationships/sourceObject";}
		void setDestinationMediaType()		{type = "http://schemas.energistics.org/package/2012/relationships/destinationMedia";}
		void setSourceMediaType()			{type = "http://schemas.energistics.org/package/2012/relationships/sourceMedia";}
		void setChunkedPartType()			{type = "http://schemas.energistics.org/package/2012/relationships/chunkedPart";}
		void setExternalPartProxyToMlType()	{type = "http://schemas.energistics.org/package/2012/relationships/externalPartProxyToMl";}
		void setMlToExternalPartProxyType()	{type = "http://schemas.energistics.org/package/2012/relationships/mlToExternalPartProxy";}
		void setExternalResourceType()		{type = "http://schemas.energistics.org/package/2012/relationships/externalResource";}

		/**
		* Set an arbitrary id to the relationship
		*/
		void setId(const std::string & rsId);
	};

	bool operator==(const Relationship& r1, const Relationship& r2);
};

#endif
