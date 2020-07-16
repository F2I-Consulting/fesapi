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
	%nspace ETP_NS::DiscoveryHandlers;
	%nspace ETP_NS::StoreHandlers;
	%nspace ETP_NS::StoreNotificationHandlers;
	%nspace ETP_NS::DataArrayHandlers;
	%nspace ETP_NS::AbstractSession;
	%nspace ETP_NS::PlainClientSession;
	
	%nspace Energistics::Etp::v12::Datatypes::SupportedDataObject;
	%nspace Energistics::Etp::v12::Datatypes::Uuid;
	%nspace Energistics::Etp::v12::Datatypes::Version;
	%nspace Energistics::Etp::v12::Datatypes::SupportedProtocol;
	
	%nspace Energistics::Etp::v12::Datatypes::Object::ContextInfo;
	%nspace Energistics::Etp::v12::Datatypes::Object::ContextScopeKind;
	%nspace Energistics::Etp::v12::Datatypes::Object::DataObject;
	%nspace Energistics::Etp::v12::Datatypes::Object::Resource;
	
	%nspace Energistics::Etp::v12::Protocol::Core::OpenSession;
	%nspace Energistics::Etp::v12::Protocol::Core::RequestSession;
	%nspace Energistics::Etp::v12::Protocol::Core::CloseSession;
	%nspace Energistics::Etp::v12::Protocol::Core::ProtocolException;
	%nspace Energistics::Etp::v12::Protocol::Core::Acknowledge;
	
	%nspace Energistics::Etp::v12::Protocol::Discovery::GetResources;
	%nspace Energistics::Etp::v12::Protocol::Discovery::GetResourcesResponse;
	
	%nspace Energistics::Etp::v12::Protocol::Store::GetDataObjects;
	%nspace Energistics::Etp::v12::Protocol::Store::GetDataObjectsResponse;
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

%include "std_map.i"
%template(MapStringString) std::map<std::string, std::string>;

%include "stdint.i"

namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Datatypes {			
				struct SupportedDataObject{				
					std::string qualifiedType;
					std::vector<std::string> dataObjectCapabilities;
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
					std::array<uint8_t, 16> array;
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
					int32_t major;
					int32_t minor;
					int32_t revision;
					int32_t patch;
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
					int32_t protocol;
					Energistics::Etp::v12::Datatypes::Version protocolVersion;
					std::string role;
				};				
			};			
		};		
	};	
};
%template(SupportedProtocolVector) std::vector<Energistics::Etp::v12::Datatypes::SupportedProtocol>;

namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Datatypes {			
				namespace Object {				
					struct ContextInfo{					
						std::string uri;
						int32_t depth;
						std::vector<std::string> dataObjectTypes;
					};					
				};				
			};			
		};		
	};	
};

namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Datatypes {			
				namespace Object {				
					enum ContextScopeKind {					
						self=0,
						sources=1,
						targets=2,
						sourcesOrSelf=3,
						targetsOrSelf=4
					};					
				};				
			};			
		};		
	};	
};

namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Datatypes {			
				namespace Object {				
					struct Resource{					
						std::string uri;
						std::vector<std::string> alternateUris;
						std::string dataObjectType;
						std::string name;
						boost::optional<int32_t> sourceCount;
						boost::optional<int32_t> targetCount;
						int64_t lastChanged;
						int64_t storeLastWrite;
						std::map<std::string, std::string> customData;
					};					
				};				
			};			
		};		
	};	
};
%template(ResourceVector) std::vector<Energistics::Etp::v12::Datatypes::Object::Resource>;

namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Datatypes {			
				namespace Object {				
					struct DataObject{					
						Energistics::Etp::v12::Datatypes::Object::Resource resource;
						std::string format;
						boost::optional<Energistics::Etp::v12::Datatypes::Uuid> blobId;
						std::string data;
					};					
				};				
			};			
		};		
	};	
};
%template(MapStringDataObject) std::map<std::string, Energistics::Etp::v12::Datatypes::Object::DataObject>;

/**************** CORE PROTOCOL  *****************/

namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace Core {				
					struct RequestSession{					
						std::string applicationName;
						std::string applicationVersion;
						Energistics::Etp::v12::Datatypes::Uuid clientInstanceId;
						std::vector<Energistics::Etp::v12::Datatypes::SupportedProtocol> requestedProtocols;
						std::vector<Energistics::Etp::v12::Datatypes::SupportedDataObject> supportedDataObjects;
						std::vector<std::string> supportedCompression;
						std::vector<std::string> supportedFormats;
						int64_t currentDateTime;
						std::map<std::string, Energistics::Etp::v12::Datatypes::DataValue> endpointCapabilities;
						static const int messageTypeId=1;
					};					
				};				
			};			
		};		
	};	
};
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace Core {				
					struct OpenSession{					
						std::string applicationName;
						std::string applicationVersion;
						Energistics::Etp::v12::Datatypes::Uuid serverInstanceId;
						std::vector<Energistics::Etp::v12::Datatypes::SupportedProtocol> supportedProtocols;
						std::vector<Energistics::Etp::v12::Datatypes::SupportedDataObject> supportedDataObjects;
						std::string supportedCompression;
						std::vector<std::string> supportedFormats;
						Energistics::Etp::v12::Datatypes::Uuid sessionId;
						int64_t currentDateTime;
						std::map<std::string, Energistics::Etp::v12::Datatypes::DataValue> endpointCapabilities;
						static const int messageTypeId=2;
					};					
				};				
			};			
		};		
	};	
};
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace Core {				
					struct CloseSession{					
						std::string reason;
						static const int messageTypeId=5;
					};					
				};				
			};			
		};		
	};	
};
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace Core {				
					struct ProtocolException{					
						boost::optional<Energistics::Etp::v12::Datatypes::ErrorInfo> error;
						std::map<std::string, Energistics::Etp::v12::Datatypes::ErrorInfo> errors;
						static const int messageTypeId=1000;
					};					
				};				
			};			
		};		
	};	
};
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace Core {				
					struct Acknowledge{					
						static const int messageTypeId=1001;
						int protocolId;
					};
				};				
			};
		};		
	};	
};

/**************** DISCOVERY PROTOCOL  *****************/

namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace Discovery {				
					struct GetResources{					
						Energistics::Etp::v12::Datatypes::Object::ContextInfo context;
						Energistics::Etp::v12::Datatypes::Object::ContextScopeKind scope;
						bool countObjects=false;
						boost::optional<int64_t> storeLastWriteFilter;
						boost::optional<Energistics::Etp::v12::Datatypes::Object::ActiveStatusKind> activeStatusFilter;
						static const int messageTypeId=1;
					};					
				};				
			};			
		};		
	};	
};

namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace Discovery {				
					struct GetResourcesResponse{					
						std::vector<Energistics::Etp::v12::Datatypes::Object::Resource> resources;
						static const int messageTypeId=4;
					};					
				};				
			};			
		};		
	};	
};

/**************** STORE PROTOCOL  *****************/

namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace Store {				
					struct GetDataObjects{					
						std::map<std::string, std::string> uris;
						std::string format;
						static const int messageTypeId=1;
					};					
				};				
			};			
		};		
	};	
};

namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace Store {				
					struct GetDataObjectsResponse{					
						std::map<std::string, Energistics::Etp::v12::Datatypes::Object::DataObject> dataObjects;
						static const int messageTypeId=4;
					};					
				};				
			};			
		};		
	};	
};



%include <std_shared_ptr.i>
%shared_ptr(ETP_NS::ProtocolHandlers)
%shared_ptr(ETP_NS::CoreHandlers)
%shared_ptr(ETP_NS::DiscoveryHandlers)
%shared_ptr(ETP_NS::StoreHandlers)
%shared_ptr(ETP_NS::StoreNotificationHandlers)
%shared_ptr(ETP_NS::DataArrayHandlers)
%shared_ptr(ETP_NS::AbstractSession)
%shared_ptr(ETP_NS::PlainClientSession)

%module(directors="1") fesapi
%feature("director") ETP_NS::CoreHandlers;
%feature("director") ETP_NS::DiscoveryHandlers;
%feature("director") ETP_NS::StoreHandlers;
%feature("director") ETP_NS::StoreNotificationHandlers;
%feature("director") ETP_NS::DataArrayHandlers;
namespace ETP_NS
{
	class AbstractSession;

	%nodefaultctor ProtocolHandlers;
	class ProtocolHandlers
	{
	public:
		std::shared_ptr<AbstractSession> getSession();
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
	
	class DiscoveryHandlers : public ProtocolHandlers
	{
	public:
		DiscoveryHandlers(std::shared_ptr<AbstractSession> mySession);
		virtual ~DiscoveryHandlers() {}

		virtual void on_GetResources(const Energistics::Etp::v12::Protocol::Discovery::GetResources & msg, int64_t correlationId);
		virtual void on_GetResourcesResponse(const Energistics::Etp::v12::Protocol::Discovery::GetResourcesResponse & msg, int64_t correlationId);
	};
	
	class StoreHandlers : public ProtocolHandlers
	{
	public:
		StoreHandlers(std::shared_ptr<AbstractSession> mySession): ProtocolHandlers(mySession) {}
		virtual ~StoreHandlers() {}

	    virtual void on_GetDataObjects(const Energistics::Etp::v12::Protocol::Store::GetDataObjects & msg, int64_t correlationId);
	    virtual void on_PutDataObjects(const Energistics::Etp::v12::Protocol::Store::PutDataObjects & msg, int64_t correlationId);
	    virtual void on_DeleteDataObjects(const Energistics::Etp::v12::Protocol::Store::DeleteDataObjects & msg, int64_t correlationId);
	    virtual void on_GetDataObjectsResponse(const Energistics::Etp::v12::Protocol::Store::GetDataObjectsResponse & msg, int64_t correlationId);
	};
	
	class StoreNotificationHandlers : public ProtocolHandlers
	{
	public:
		StoreNotificationHandlers(std::shared_ptr<AbstractSession> mySession): ProtocolHandlers(mySession) {}
		virtual ~StoreNotificationHandlers() {}

	    virtual void on_SubscribeNotifications(const Energistics::Etp::v12::Protocol::StoreNotification::SubscribeNotifications & msg, int64_t messageId);
	    virtual void on_UnsubscribeNotifications(const Energistics::Etp::v12::Protocol::StoreNotification::UnsubscribeNotifications & msg, int64_t messageId, int64_t correlationId);
		virtual void on_UnsolicitedStoreNotifications(const Energistics::Etp::v12::Protocol::StoreNotification::UnsolicitedStoreNotifications & msg, int64_t correlationId);
		virtual void on_SubscriptionEnded(const Energistics::Etp::v12::Protocol::StoreNotification::SubscriptionEnded & msg, int64_t correlationId);
	    virtual void on_ObjectChanged(const Energistics::Etp::v12::Protocol::StoreNotification::ObjectChanged & msg, int64_t correlationId);
	    virtual void on_ObjectDeleted(const Energistics::Etp::v12::Protocol::StoreNotification::ObjectDeleted & msg, int64_t correlationId);
		virtual void on_ObjectAccessRevoked(const Energistics::Etp::v12::Protocol::StoreNotification::ObjectAccessRevoked & msg, int64_t correlationId);
	};
	
	class DataArrayHandlers : public ProtocolHandlers
	{
	public:
		DataArrayHandlers(std::shared_ptr<AbstractSession> mySession): ProtocolHandlers(mySession) {}
		virtual ~DataArrayHandlers() {}

	    virtual void on_GetDataArrays(const Energistics::Etp::v12::Protocol::DataArray::GetDataArrays & gda, int64_t correlationId);
		virtual void on_GetDataArraysResponse(Energistics::Etp::v12::Protocol::DataArray::GetDataArraysResponse & gdar);
	    virtual void on_PutDataArrays(const Energistics::Etp::v12::Protocol::DataArray::PutDataArrays & pda, int64_t correlationId);
	    virtual void on_GetDataSubarrays(const Energistics::Etp::v12::Protocol::DataArray::GetDataSubarrays & msg, int64_t correlationId);
		virtual void on_GetDataSubarraysResponse(const Energistics::Etp::v12::Protocol::DataArray::GetDataSubarraysResponse & msg);
	    virtual void on_PutDataSubarrays(const Energistics::Etp::v12::Protocol::DataArray::PutDataSubarrays & msg, int64_t correlationId);
		virtual void on_GetDataArrayMetadata(const Energistics::Etp::v12::Protocol::DataArray::GetDataArrayMetadata & gdam, int64_t correlationId);
		virtual void on_GetDataArrayMetadataResponse(const Energistics::Etp::v12::Protocol::DataArray::GetDataArrayMetadataResponse & gdamr);
	};

	%nodefaultctor AbstractSession;
	class AbstractSession
	{
	public:
		void setCoreProtocolHandlers(std::shared_ptr<ETP_NS::CoreHandlers> coreHandlers);
		void setDiscoveryProtocolHandlers(std::shared_ptr<DiscoveryHandlers> discoveryHandlers);
		void setStoreProtocolHandlers(std::shared_ptr<StoreHandlers> storeHandlers);
		void setStoreNotificationProtocolHandlers(std::shared_ptr<ETP_NS::StoreNotificationHandlers> storeNotificationHandlers);
		void setDataArrayProtocolHandlers(std::shared_ptr<DataArrayHandlers> dataArrayHandlers);
		
		template<typename T> int64_t send(const T & mb, int64_t correlationId = 0, int32_t messageFlags = 0)
		{
			int64_t msgId = encode(mb, correlationId, messageFlags); // put the message to write in the queue

			if(sendingQueue.size() == 1) {
				do_write();
			}

			return msgId;
		}
		%template(send) send<Energistics::Etp::v12::Protocol::Core::RequestSession>;
		%template(send) send<Energistics::Etp::v12::Protocol::Core::OpenSession>;
		%template(send) send<Energistics::Etp::v12::Protocol::Core::CloseSession>;
		%template(send) send<Energistics::Etp::v12::Protocol::Core::ProtocolException>;
		%template(send) send<Energistics::Etp::v12::Protocol::Core::Acknowledge>;
		
		%template(send) send<Energistics::Etp::v12::Protocol::Discovery::GetResources>;
		%template(send) send<Energistics::Etp::v12::Protocol::Discovery::GetResourcesResponse>;
		
		%template(send) send<Energistics::Etp::v12::Protocol::Store::GetDataObjects>;
		%template(send) send<Energistics::Etp::v12::Protocol::Store::PutDataObjects>;
		%template(send) send<Energistics::Etp::v12::Protocol::Store::DeleteDataObjects>;
		%template(send) send<Energistics::Etp::v12::Protocol::Store::GetDataObjectsResponse>;
		
		void close();
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
