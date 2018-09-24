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
#pragma once

#include "prodml2_0/DasAcquisition.h"

namespace PRODML2_0_NS
{
	class DLL_IMPORT_OR_EXPORT FiberOpticalPath : public PRODML2_0_NS::AbstractObject
	{
	public:
		/**
		* Default constructor
		*/
		FiberOpticalPath() {}

		/**
		* Creates an instance of this class in a gsoap context.
		* @param soap		A gsoap context wihch will manage the memory and the serialization/deserialization of this instance.
		* @param guid		The guid to set to this instance. If empty then a new guid will be generated.
		* @param title		A title for the instance to create.
		*/
		FiberOpticalPath(soap* soapContext, const std::string & guid, const std::string & title,
			const std::string & firstSegmentUid, const double & firstSegmentLength, const gsoap_eml2_1::eml21__LengthUom & firstSegmentLengthUom,
			const std::string & terminatorUid, const gsoap_eml2_1::prodml2__TerminationType & terminationType);

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		FiberOpticalPath(gsoap_eml2_1::_prodml2__FiberOpticalPath* fromGsoap) : AbstractObject(fromGsoap) {}

		/**
		* Destructor does nothing since the memory is managed by the gsoap context.
		*/
		~FiberOpticalPath() {}
		
		static const char* XML_TAG;
		virtual std::string getXmlTag() const {return XML_TAG;}

	protected:

		std::vector<epc::Relationship> getAllSourceRelationships() const;
		std::vector<epc::Relationship> getAllTargetRelationships() const;

		/**
		* Does nothing since StringTableLookup has not got any forward relationship.
		*/
		void resolveTargetRelationships(COMMON_NS::EpcDocument* epcDoc) {}

		// XML backwards relationships
		std::vector<class DasAcquisition*> dasAcquisitionSet;

		friend void DasAcquisition::setFiberOpticalPath(class FiberOpticalPath* fiberOpticalPath);
	};
}

