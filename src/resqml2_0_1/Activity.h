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

#include "resqml2/Activity.h"

namespace resqml2
{
	class ActivityTemplate;
}

namespace resqml2_0_1
{
	class DLL_IMPORT_OR_EXPORT Activity : public resqml2::Activity
	{
	protected:
		Activity() : resqml2::Activity() {}

	public:

		/**
		* Only to be used in partial transfer context
		*/
		Activity(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : resqml2::Activity(partialObject) {}

		/**
		* Creates an instance of this class in a gsoap context.
		* @param guid		The guid to set to the boundary horizon. If empty then a new guid will be generated.
		* @param title		A title for the instance to create.
		*/
		Activity(resqml2::ActivityTemplate* activityTemplate, const std::string & guid, const std::string & title);

		Activity(gsoap_resqml2_0_1::_resqml2__Activity* fromGsoap) : resqml2::Activity(fromGsoap) {}
		virtual ~Activity() {}

		/**
		* Push back a double parameter in the instance.
		* This parameter must exist in the associated activity template.
		*/
		void pushBackParameter(const std::string title,
			const double & value, const gsoap_resqml2_0_1::resqml2__ResqmlUom & uom = gsoap_resqml2_0_1::resqml2__ResqmlUom__Euc);

		/**
		* Push back a string parameter in the instance.
		* This parameter must exist in the associated activity template.
		*/
		void pushBackParameter(const std::string title,
			const std::string & value);

		/**
		* Push back an integer parameter in the instance.
		* This parameter must exist in the associated activity template.
		*/
		void pushBackParameter(const std::string title,
			const LONG64 & value);

		/**
		* Push back a resqml object parameter in the instance.
		* This parameter must exist in the associated activity template.
		*/
		void pushBackParameter(const std::string title,
			AbstractObject* resqmlObject);
		
		/**
		* Get the count of all the parameters
		*/
		unsigned int getParameterCount() const;

		/**
		* Get the count of all the parameters which have got the same title.
		*/
		unsigned int getParameterCount(const std::string & paramTitle) const;
		const std::string & getParameterTitle(const unsigned int & index) const;
		std::vector<unsigned int> getParameterIndexOfTitle(const std::string & paramTitle) const;

		bool isAFloatingPointQuantityParameter(const std::string & paramTitle) const;
		bool isAFloatingPointQuantityParameter(const unsigned int & index) const;
		std::vector<double> getFloatingPointQuantityParameterValue(const std::string & paramTitle) const;
		double getFloatingPointQuantityParameterValue(const unsigned int & index) const;
		std::vector<gsoap_resqml2_0_1::resqml2__ResqmlUom> getFloatingPointQuantityParameterUom(const std::string & paramTitle) const;
		gsoap_resqml2_0_1::resqml2__ResqmlUom getFloatingPointQuantityParameterUom(const unsigned int & index) const;

		bool isAnIntegerQuantityParameter(const std::string & paramTitle) const;
		bool isAnIntegerQuantityParameter(const unsigned int & index) const;
		std::vector<LONG64> getIntegerQuantityParameterValue(const std::string & paramTitle) const;
		LONG64 getIntegerQuantityParameterValue(const unsigned int & index) const;

		bool isAStringParameter(const std::string & paramTitle) const;
		bool isAStringParameter(const unsigned int & index) const;
		std::vector<std::string> getStringParameterValue(const std::string & paramTitle) const;
		const std::string & getStringParameterValue(const unsigned int & index) const;

		bool isAResqmlObjectParameter(const std::string & paramTitle) const;
		bool isAResqmlObjectParameter(const unsigned int & index) const;
		std::vector<AbstractObject*> getResqmlObjectParameterValue(const std::string & paramTitle) const;
		AbstractObject* getResqmlObjectParameterValue(const unsigned int & index) const;

		/**
		* Set the activity template of the activity
		**/
		void setActivityTemplate(resqml2::ActivityTemplate* activityTemplate);

		gsoap_resqml2_0_1::eml20__DataObjectReference* getActivityTemplateDor() const;

		std::string getResqmlVersion() const;

	private:

		void importRelationshipSetFromEpc(common::EpcDocument* epcDoc);

		std::vector<gsoap_resqml2_0_1::resqml2__AbstractActivityParameter*> getParameterFromTitle(const std::string & paramTitle) const;
	};
}
