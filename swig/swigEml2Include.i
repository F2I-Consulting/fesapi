/*-----------------------------------------------------------------------
Licensed to the Apache Software Foundation (ASF) under one
or more contributor license agreements.  See the NOTICE file
distributed with this work for additional information
regarding copyright ownership.  The ASF licenses this file
to you under the Apache License, Version 2.0 (the
"License"; you may not use this file except in compliance
with the License.  You may obtain a copy of the License at

  http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing,
software distributed under the License is distributed on an
"AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
KIND, either express or implied.  See the License for the
specific language governing permissions and limitations
under the License.
-----------------------------------------------------------------------*/
%{
#include "../src/eml2/Activity.h"
#include "../src/eml2/ActivityTemplate.h"
#include "../src/eml2/HdfProxy.h"
#include "../src/eml2/PropertyKind.h"
#include "../src/eml2/TimeSeries.h"
%}

#if defined(SWIGJAVA) || defined(SWIGCSHARP)
	%nspace EML2_NS::AbstractHdfProxy;
	%nspace EML2_NS::Activity;
	%nspace EML2_NS::ActivityTemplate;
	%nspace EML2_NS::EpcExternalPartReference;
	%nspace EML2_NS::HdfProxy;
	%nspace EML2_NS::PropertyKind;
	%nspace EML2_NS::TimeSeries;
#endif

namespace EML2_NS
{
	%nodefaultctor; // Disable creation of default constructors
	
	//************************************
	//************ HDF *******************
	//************************************
	class EpcExternalPartReference : public COMMON_NS::AbstractObject {};

	class AbstractHdfProxy : public EpcExternalPartReference
	{
	public:
		virtual bool isOpened() = 0;
		virtual void close() = 0;
		
		std::string getRelativePath();
	};

	class HdfProxy : public AbstractHdfProxy
	{
	public:
		void setCompressionLevel(unsigned int newCompressionLevel);
	};
	
	//************************************
	//************ Property **************
	//************************************
	
	class PropertyKind : public COMMON_NS::AbstractObject {};
	
	class TimeSeries : public COMMON_NS::AbstractObject
	{
	public:
		void pushBackTimestamp(time_t timestamp);
		unsigned int getTimestampIndex(time_t timestamp) const;
		unsigned int getTimestampCount() const;
		time_t getTimestamp(unsigned int index) const;
	};
	
	//************************************
	//************ Activity **************
	//************************************

	class ActivityTemplate : public COMMON_NS::AbstractObject
	{
	public:
		void pushBackParameter(const std::string & title,
			bool isInput, bool isOutput,
			unsigned int minOccurs, int maxOccurs);
		void pushBackParameter(const std::string & title,
			bool isInput, bool isOutput,
			unsigned int minOccurs, int maxOccurs,
			std::string resqmlObjectContentType);
		bool isAnExistingParameter(const std::string & paramTitle) const;
		const unsigned int getParameterCount() const;
		const std::string & getParameterTitle(unsigned int index) const;
		bool getParameterIsInput(unsigned int index) const;
		bool getParameterIsInput(const std::string & paramTitle) const;
		bool getParameterIsOutput(unsigned int index) const;
		bool getParameterIsOutput(const std::string & paramTitle) const;
		LONG64 getParameterMinOccurences(unsigned int index) const;
		LONG64 getParameterMinOccurences(const std::string & paramTitle) const;
		LONG64 getParameterMaxOccurences(unsigned int index) const;
		LONG64 getParameterMaxOccurences(const std::string & paramTitle) const;
	};

	class Activity : public COMMON_NS::AbstractObject
	{
	public:
		void pushBackParameter(const std::string title, const std::string & value);
		void pushBackParameter(const std::string title, LONG64 value);
		void pushBackParameter(const std::string title, COMMON_NS::AbstractObject* resqmlObject);
		
		unsigned int getParameterCount() const;
		unsigned int getParameterCount(const std::string & paramTitle) const;

		const std::string & getParameterTitle(unsigned int index) const;

		bool isAFloatingPointQuantityParameter(const std::string & paramTitle) const;
		bool isAFloatingPointQuantityParameter(unsigned int index) const;
		double getFloatingPointQuantityParameterValue(unsigned int index) const;

		bool isAnIntegerQuantityParameter(const std::string & paramTitle) const;
		bool isAnIntegerQuantityParameter(unsigned int index) const;
		LONG64 getIntegerQuantityParameterValue(unsigned int index) const;

		bool isAStringParameter(const std::string & paramTitle) const;
		bool isAStringParameter(unsigned int index) const;
		const std::string & getStringParameterValue(unsigned int index) const;

		bool isAResqmlObjectParameter(const std::string & paramTitle) const;
		bool isAResqmlObjectParameter(unsigned int index) const;
		COMMON_NS::AbstractObject* getResqmlObjectParameterValue(unsigned int index) const;

		void setActivityTemplate(ActivityTemplate* activityTemplate);
		ActivityTemplate* getActivityTemplate() const;
	};
}
