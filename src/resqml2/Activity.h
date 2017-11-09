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

namespace resqml2
{
	class DLL_IMPORT_OR_EXPORT Activity : public common::AbstractObject
	{
	protected:
		Activity() : AbstractObject() {}

		Activity(gsoap_resqml2_0_1::_resqml2__Activity* fromGsoap) : common::AbstractObject(fromGsoap) {}

	public:

		/**
		* Only to be used in partial transfer context
		*/
		Activity(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : common::AbstractObject(partialObject) {}

		virtual ~Activity() {}

		/**
		* Push back a string parameter in the instance.
		* This parameter must exist in the associated activity template.
		*/
		virtual void pushBackParameter(const std::string title,
			const std::string & value) = 0;

		/**
		* Push back an integer parameter in the instance.
		* This parameter must exist in the associated activity template.
		*/
		virtual void pushBackParameter(const std::string title,
			const LONG64 & value) = 0;

		/**
		* Push back a resqml object parameter in the instance.
		* This parameter must exist in the associated activity template.
		*/
		virtual void pushBackParameter(const std::string title,
			AbstractObject* resqmlObject) = 0;
		
		/**
		* Get the count of all the parameters
		*/
		virtual unsigned int getParameterCount() const = 0;

		/**
		* Get the count of all the parameters which have got the same title.
		*/
		virtual unsigned int getParameterCount(const std::string & paramTitle) const = 0;
		virtual const std::string & getParameterTitle(const unsigned int & index) const = 0;
		virtual std::vector<unsigned int> getParameterIndexOfTitle(const std::string & paramTitle) const = 0;

		virtual bool isAFloatingPointQuantityParameter(const std::string & paramTitle) const = 0;
		virtual bool isAFloatingPointQuantityParameter(const unsigned int & index) const = 0;
		virtual std::vector<double> getFloatingPointQuantityParameterValue(const std::string & paramTitle) const = 0;
		virtual double getFloatingPointQuantityParameterValue(const unsigned int & index) const = 0;

		virtual bool isAnIntegerQuantityParameter(const std::string & paramTitle) const = 0;
		virtual bool isAnIntegerQuantityParameter(const unsigned int & index) const = 0;
		virtual std::vector<LONG64> getIntegerQuantityParameterValue(const std::string & paramTitle) const = 0;
		virtual LONG64 getIntegerQuantityParameterValue(const unsigned int & index) const = 0;

		virtual bool isAStringParameter(const std::string & paramTitle) const = 0;
		virtual bool isAStringParameter(const unsigned int & index) const = 0;
		virtual std::vector<std::string> getStringParameterValue(const std::string & paramTitle) const = 0;
		virtual const std::string & getStringParameterValue(const unsigned int & index) const = 0;

		virtual bool isAResqmlObjectParameter(const std::string & paramTitle) const = 0;
		virtual bool isAResqmlObjectParameter(const unsigned int & index) const = 0;
		virtual std::vector<AbstractObject*> getResqmlObjectParameterValue(const std::string & paramTitle) const = 0;
		virtual AbstractObject* getResqmlObjectParameterValue(const unsigned int & index) const = 0;

		/**
		* Set the activity template of the activity
		**/
		virtual void setActivityTemplate(class ActivityTemplate* activityTemplate) = 0;

		/**
		* Get the activity template dor of the activity
		**/
		virtual gsoap_resqml2_0_1::eml20__DataObjectReference* getActivityTemplateDor() const = 0;
		
		/**
		* Get the activity template of the activity
		**/
		class ActivityTemplate* getActivityTemplate() const;

		/**
		* Get all objects which are either input or output of this acitivty
		**/
		std::vector<AbstractObject*> getResqmlObjectSet() const;

		static const char* XML_TAG;
		std::string getXmlTag() const {return XML_TAG;}

	protected:

		std::vector<epc::Relationship> getAllEpcRelationships() const;
	};
}
