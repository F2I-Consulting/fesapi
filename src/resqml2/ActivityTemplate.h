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

#include "resqml2_0_1/Activity.h"

namespace resqml2
{
	class DLL_IMPORT_OR_EXPORT ActivityTemplate : public common::AbstractObject
	{
	protected:
		ActivityTemplate() : AbstractObject() {}

		ActivityTemplate(gsoap_resqml2_0_1::_resqml2__ActivityTemplate* fromGsoap) : common::AbstractObject(fromGsoap) {}

	public:

		/**
		* Only to be used in partial transfer context
		*/
		ActivityTemplate(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : common::AbstractObject(partialObject) {}

		virtual ~ActivityTemplate() {}
		
		/**
		* Push back a parameter in the activity template instance.
		* This parameter has an unconstrained type.
		*/
		virtual void pushBackParameter(const std::string title,
			const bool & isInput, const bool isOutput,
			const unsigned int & minOccurs, const int & maxOccurs) = 0;

		/**
		* Push back a parameter in the activity template instance.
		* This parameter must be of a data object kind.
		* @param resqmlObjectContentType	If empty, there is no constraint on the content type of this parameter.
		*/
		virtual void pushBackParameter(const std::string title,
			const bool & isInput, const bool isOutput,
			const unsigned int & minOccurs, const int & maxOccurs,
			const std::string & resqmlObjectContentType) = 0;

		/**
		* Check if the instance contains a parameter with a particular title
		* @param paramTitle	The title of the parameter we are looking for into the instance
		*/
		virtual bool isAnExistingParameter(const std::string & paramTitle) const = 0;

		virtual const unsigned int getParameterCount() const = 0;
		virtual const std::string & getParameterTitle(const unsigned int & index) const = 0;
		virtual const bool & getParameterIsInput(const unsigned int & index) const = 0;
		virtual const bool & getParameterIsInput(const std::string & paramTitle) const = 0;
		virtual const bool & getParameterIsOutput(const unsigned int & index) const = 0;
		virtual const bool & getParameterIsOutput(const std::string & paramTitle) const = 0;
		virtual const LONG64 getParameterMinOccurences(const unsigned int & index) const = 0;
		virtual const LONG64 getParameterMinOccurences(const std::string & paramTitle) const = 0;
		virtual const LONG64 getParameterMaxOccurences(const unsigned int & index) const = 0;
		virtual const LONG64 getParameterMaxOccurences(const std::string & paramTitle) const = 0;

		const std::vector<Activity*> & getActivityInstanceSet() const { return activityInstanceSet; }

		static const char* XML_TAG;
		std::string getXmlTag() const {return XML_TAG;}


	private:
		std::vector<epc::Relationship> getAllEpcRelationships() const;
		void importRelationshipSetFromEpc(common::EpcDocument * epcDoc) {}
		
        std::vector<Activity*> activityInstanceSet;

		friend void resqml2_0_1::Activity::setActivityTemplate(resqml2::ActivityTemplate* activityTemplate);
	};
}
