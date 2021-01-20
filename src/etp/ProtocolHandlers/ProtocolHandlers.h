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

#include <memory>

#include "../../nsDefinitions.h"
#include "../EtpMessages.h"

#if defined(_WIN32) && !defined(FESAPI_STATIC)
	#ifndef DLL_IMPORT_OR_EXPORT
		#if defined(FesapiCpp_EXPORTS) || defined(FesapiCppUnderDev_EXPORTS)
			#define DLL_IMPORT_OR_EXPORT __declspec(dllexport)
		#else
			#define DLL_IMPORT_OR_EXPORT __declspec(dllimport)
		#endif
	#endif
#else
	#define DLL_IMPORT_OR_EXPORT
#endif

namespace ETP_NS
{
	class AbstractSession;

	class DLL_IMPORT_OR_EXPORT ProtocolHandlers : public std::enable_shared_from_this<ProtocolHandlers>
	{
	protected:
		ProtocolHandlers(AbstractSession* mySession): session(mySession) {}

		AbstractSession* session;

		void printDataObject(const Energistics::Etp::v12::Datatypes::Object::DataObject & dataObject);

	public:
		virtual ~ProtocolHandlers() {}

	    virtual void decodeMessageBody(const Energistics::Etp::v12::Datatypes::MessageHeader & mh, avro::DecoderPtr d) = 0;

		AbstractSession* getSession() { return session; }
	};
}
