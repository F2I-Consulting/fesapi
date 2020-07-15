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
#include "../src/etp/ClientSessionLaunchers.h"
%}

#if defined(SWIGJAVA) || defined(SWIGCSHARP)
	%nspace ETP_NS::ProtocolHandlers;
	%nspace ETP_NS::CoreHandlers;
	%nspace ETP_NS::AbstractSession;
	%nspace ETP_NS::PlainClientSession;
	
	%nspace Energistics::Etp::v12::Datatypes::SupportedDataObject;
	%nspace Energistics::Etp::v12::Datatypes::Uuid;
	%nspace Energistics::Etp::v12::Datatypes::Version;
	%nspace Energistics::Etp::v12::Datatypes::SupportedProtocol;
	
	%nspace Energistics::Etp::v12::Protocol::Core::OpenSession;
#endif

#ifdef SWIGJAVA
	/*
	 When using multiple modules or the nspace feature it is common to invoke SWIG with a different -package command line option for each module.
	 However, by default the generated code may not compile if generated classes in one package use generated classes in another package.
	 The visibility of the getCPtr() and pointer constructor generated from the javabody typemaps needs changing.
	 The default visibility is protected but it needs to be public for access from a different package. Just changing 'protected' to 'public' in the typemap achieves this.
	*/
	#define SWIG_SHARED_PTR_TYPEMAPS(CONST, TYPE...) SWIG_SHARED_PTR_TYPEMAPS_IMPLEMENTATION(public, public, CONST, TYPE)
#endif

%include "stdint.i"

namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Datatypes {			
				struct SupportedDataObject{				
					std::string m_qualifiedType;
					std::vector<std::string> m_dataObjectCapabilities;
				};				
			};			
		};		
	};	
};
%template(SupportedDataObjectVector) std::vector<Energistics::Etp::v12::Datatypes::SupportedDataObject>;

%include "std_array.i"
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Datatypes {			
				struct Uuid{				
					std::array<uint8_t, 16> m_array;
				};				
			};			
		};		
	};	
};
%template(uint8_t16Array) std::array<uint8_t, 16>;

namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Datatypes {			
				struct Version{				
					int32_t m_major;
					int32_t m_minor;
					int32_t m_revision;
					int32_t m_patch;
				};				
			};			
		};		
	};	
};
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Datatypes {			
				struct SupportedProtocol{				
					int32_t m_protocol;
					Energistics::Etp::v12::Datatypes::Version m_protocolVersion;
					std::string m_role;
				};				
			};			
		};		
	};	
};
%template(SupportedProtocolVector) std::vector<Energistics::Etp::v12::Datatypes::SupportedProtocol>;

namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace Core {				
					struct OpenSession{					
						std::string m_applicationName;
						std::string m_applicationVersion;
						Energistics::Etp::v12::Datatypes::Uuid m_serverInstanceId;
						std::vector<Energistics::Etp::v12::Datatypes::SupportedProtocol> m_supportedProtocols;
						std::vector<Energistics::Etp::v12::Datatypes::SupportedDataObject> m_supportedDataObjects;
						std::string m_supportedCompression;
						std::vector<std::string> m_supportedFormats;
						Energistics::Etp::v12::Datatypes::Uuid m_sessionId;
						int64_t m_currentDateTime;
						std::map<std::string, Energistics::Etp::v12::Datatypes::DataValue> m_endpointCapabilities;
						static const int messageTypeId=2;
					};					
				};				
			};			
		};		
	};	
};

%include <std_shared_ptr.i>
%shared_ptr(ETP_NS::ProtocolHandlers)
%shared_ptr(ETP_NS::CoreHandlers)
%shared_ptr(ETP_NS::AbstractSession)
%shared_ptr(ETP_NS::PlainClientSession)

%module(directors="1") fesapi
%feature("director") ETP_NS::CoreHandlers;
namespace ETP_NS
{
	class AbstractSession;

	%nodefaultctor ProtocolHandlers;
	class ProtocolHandlers
	{
	public:
	};

	class CoreHandlers : public ProtocolHandlers
	{
	public:
		CoreHandlers(std::shared_ptr<AbstractSession> mySession);
		virtual ~CoreHandlers();
		
		virtual void on_RequestSession(const Energistics::Etp::v12::Protocol::Core::RequestSession & rs, int64_t correlationId);
	    virtual void on_OpenSession(const Energistics::Etp::v12::Protocol::Core::OpenSession & os, int64_t correlationId);
	    virtual void on_CloseSession(const Energistics::Etp::v12::Protocol::Core::CloseSession & cs, int64_t correlationId);
	    virtual void on_ProtocolException(const Energistics::Etp::v12::Protocol::Core::ProtocolException & pe, int64_t correlationId);
		virtual void on_Acknowledge(const Energistics::Etp::v12::Protocol::Core::Acknowledge & ack, int64_t correlationId);
	};

	%nodefaultctor AbstractSession;
	class AbstractSession
	{
	public:
		void setCoreProtocolHandlers(std::shared_ptr<ETP_NS::CoreHandlers> coreHandlers);
	};

	class PlainClientSession : public AbstractSession
	{
	public:
		bool run();
	};

	namespace ClientSessionLaunchers
	{
		std::shared_ptr<ETP_NS::PlainClientSession> createClientSession(const std::string & host, const std::string & port, const std::string & target, const std::string & authorization);
	}
}

