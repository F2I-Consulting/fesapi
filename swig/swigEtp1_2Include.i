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
#include "../src/etp/Server.h"
#include "../src/etp/PlainServerSession.h"
#include "../src/etp/EtpHelpers.h"
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
	%nspace ETP_NS::ServerInitializationParameters;
	%nspace ETP_NS::PlainServerSession;
	%nspace ETP_NS::Server<ETP_NS::PlainServerSession>;
	
	%nspace Energistics::Etp::v12::Datatypes::SupportedDataObject;
	%nspace Energistics::Etp::v12::Datatypes::Uuid;
	%nspace Energistics::Etp::v12::Datatypes::Version;
	%nspace Energistics::Etp::v12::Datatypes::SupportedProtocol;
	%nspace Energistics::Etp::v12::Datatypes::DataValue;
	%nspace Energistics::Etp::v12::Datatypes::DataValueitem_t;
	%nspace Energistics::Etp::v12::Datatypes::ErrorInfo;
	%nspace Energistics::Etp::v12::Datatypes::AnyArrayType;
	%nspace Energistics::Etp::v12::Datatypes::AnyArray;
	%nspace Energistics::Etp::v12::Datatypes::AnyArrayitem_t;
	%nspace Energistics::Etp::v12::Datatypes::ArrayOfBoolean;
	%nspace Energistics::Etp::v12::Datatypes::ArrayOfInt;
	%nspace Energistics::Etp::v12::Datatypes::ArrayOfLong;
	%nspace Energistics::Etp::v12::Datatypes::ArrayOfFloat;
	%nspace Energistics::Etp::v12::Datatypes::ArrayOfDouble;
	%nspace Energistics::Etp::v12::Datatypes::ArrayOfString;
	
	%nspace Energistics::Etp::v12::Datatypes::Object::ContextInfo;
	%nspace Energistics::Etp::v12::Datatypes::Object::ContextScopeKind;
	%nspace Energistics::Etp::v12::Datatypes::Object::DataObject;
	%nspace Energistics::Etp::v12::Datatypes::Object::Resource;
	
	%nspace Energistics::Etp::v12::Datatypes::DataArrayTypes::DataArrayIdentifier;
	%nspace Energistics::Etp::v12::Datatypes::DataArrayTypes::DataArray;
	%nspace Energistics::Etp::v12::Datatypes::DataArrayTypes::DataArrayMetadata;
	%nspace Energistics::Etp::v12::Datatypes::DataArrayTypes::PutDataArraysType;
	%nspace Energistics::Etp::v12::Datatypes::DataArrayTypes::GetDataSubarraysType;
	%nspace Energistics::Etp::v12::Datatypes::DataArrayTypes::PutDataSubarraysType;
	%nspace Energistics::Etp::v12::Datatypes::DataArrayTypes::PutUninitializedDataArrayType;
	
	%nspace Energistics::Etp::v12::Protocol::Core::OpenSession;
	%nspace Energistics::Etp::v12::Protocol::Core::RequestSession;
	%nspace Energistics::Etp::v12::Protocol::Core::CloseSession;
	%nspace Energistics::Etp::v12::Protocol::Core::ProtocolException;
	%nspace Energistics::Etp::v12::Protocol::Core::Acknowledge;
	
	%nspace Energistics::Etp::v12::Protocol::Discovery::GetResources;
	%nspace Energistics::Etp::v12::Protocol::Discovery::GetResourcesResponse;
	
	%nspace Energistics::Etp::v12::Protocol::Store::GetDataObjects;
	%nspace Energistics::Etp::v12::Protocol::Store::GetDataObjectsResponse;
	%nspace Energistics::Etp::v12::Protocol::Store::PutDataObjects;
	%nspace Energistics::Etp::v12::Protocol::Store::PutDataObjectsResponse;
	%nspace Energistics::Etp::v12::Protocol::Store::DeleteDataObjects;
	%nspace Energistics::Etp::v12::Protocol::Store::DeleteDataObjectsResponse;
	
	%nspace Energistics::Etp::v12::Protocol::DataArray::GetDataArrays;
	%nspace Energistics::Etp::v12::Protocol::DataArray::GetDataArraysResponse;
	%nspace Energistics::Etp::v12::Protocol::DataArray::PutDataArrays;
	%nspace Energistics::Etp::v12::Protocol::DataArray::PutDataArraysResponse;
	%nspace Energistics::Etp::v12::Protocol::DataArray::GetDataSubarrays;
	%nspace Energistics::Etp::v12::Protocol::DataArray::GetDataSubarraysResponse;
	%nspace Energistics::Etp::v12::Protocol::DataArray::PutDataSubarrays;
	%nspace Energistics::Etp::v12::Protocol::DataArray::PutDataSubarraysResponse;
	%nspace Energistics::Etp::v12::Protocol::DataArray::GetDataArrayMetadata;
	%nspace Energistics::Etp::v12::Protocol::DataArray::GetDataArrayMetadataResponse;
	%nspace Energistics::Etp::v12::Protocol::DataArray::PutUninitializedDataArrays;
	%nspace Energistics::Etp::v12::Protocol::DataArray::PutUninitializedDataArraysResponse;
#endif

#ifdef SWIGJAVA
	/*
	 When using multiple modules or the nspace feature it is common to invoke SWIG with a different -package command line option for each module.
	 However, by default the generated code may not compile if generated classes in one package use generated classes in another package.
	 The visibility of the getCPtr() and pointer constructor generated from the javabody typemaps needs changing.
	 The default visibility is protected but it needs to be public for access from a different package. Just changing 'protected' to 'public' in the typemap achieves this.
	*/
	#define SWIG_SHARED_PTR_TYPEMAPS(CONST, TYPE...) SWIG_SHARED_PTR_TYPEMAPS_IMPLEMENTATION(public, public, CONST, TYPE)
	
	%insert("runtime") %{
		#define SWIG_JAVA_ATTACH_CURRENT_THREAD_AS_DAEMON
	%}
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
				struct ArrayOfBoolean{				
					std::vector<bool> values;
				};				
			};			
		};		
	};	
};

namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Datatypes {			
				struct ArrayOfInt{				
					std::vector<int32_t> values;
				};				
			};			
		};		
	};	
};

namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Datatypes {			
				struct ArrayOfLong{				
					std::vector<int64_t> values;
				};				
			};			
		};		
	};	
};

namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Datatypes {			
				struct ArrayOfFloat{				
					std::vector<float> values;
				};				
			};			
		};		
	};	
};

namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Datatypes {			
				struct ArrayOfDouble{				
					std::vector<double> values;
				};				
			};			
		};		
	};	
};

namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Datatypes {			
				struct ArrayOfString{				
					std::vector<std::string> values;
				};				
			};			
		};		
	};	
};

namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Datatypes {			
				struct DataValueitem_t {
				public:				
					size_t idx() const;
					
					bool is_null() const;
					void set_null();
									
					bool get_boolean();				
					void set_boolean(const bool& v);
					
					int32_t get_int();			
					void set_int(const int32_t& v);	
					
					int64_t get_long();				
					void set_long(const int64_t& v);
					
					float get_float();				
					void set_float(const float& v);
					
					double get_double();				
					void set_double(const double& v);
					
					std::string get_string();				
					void set_string(const std::string& v);
					
					Energistics::Etp::v12::Datatypes::ArrayOfBoolean get_ArrayOfBoolean();		
					void set_ArrayOfBoolean(const Energistics::Etp::v12::Datatypes::ArrayOfBoolean& v);
					
					Energistics::Etp::v12::Datatypes::ArrayOfInt get_ArrayOfInt();			
					void set_ArrayOfInt(const Energistics::Etp::v12::Datatypes::ArrayOfInt& v);
					
					Energistics::Etp::v12::Datatypes::ArrayOfLong get_ArrayOfLong();
					void set_ArrayOfLong(const Energistics::Etp::v12::Datatypes::ArrayOfLong& v);	
					
					Energistics::Etp::v12::Datatypes::ArrayOfFloat get_ArrayOfFloat();				
					void set_ArrayOfFloat(const Energistics::Etp::v12::Datatypes::ArrayOfFloat& v);
					
					Energistics::Etp::v12::Datatypes::ArrayOfDouble get_ArrayOfDouble();	
					void set_ArrayOfDouble(const Energistics::Etp::v12::Datatypes::ArrayOfDouble& v);
					
					Energistics::Etp::v12::Datatypes::ArrayOfString get_ArrayOfString();			
					void set_ArrayOfString(const Energistics::Etp::v12::Datatypes::ArrayOfString& v);	
					
					std::string get_bytes();				
					void set_bytes(const std::string& v);		
				};				
			};			
		};		
	};	
};

namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Datatypes {			
				struct DataValue{				
					Energistics::Etp::v12::Datatypes::DataValueitem_t item;
				};				
			};			
		};		
	};	
};
%template(MapStringDataValue) std::map<std::string, Energistics::Etp::v12::Datatypes::DataValue>;

namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Datatypes {			
				struct ErrorInfo{				
					std::string message;
					int32_t code;
				};				
			};			
		};		
	};	
};
%template(MapStringErrorInfo) std::map<std::string, Energistics::Etp::v12::Datatypes::ErrorInfo>;

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
						std::map<std::string, Energistics::Etp::v12::Datatypes::DataValue> customData;
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

namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Datatypes {			
				namespace DataArrayTypes {				
					struct DataArrayIdentifier{					
						std::string uri;
						std::string pathInResource;
					};					
				};				
			};			
		};		
	};	
};
%template(MapStringDataArrayIdentifier) std::map<std::string, Energistics::Etp::v12::Datatypes::DataArrayTypes::DataArrayIdentifier>;

namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Datatypes {			
				struct AnyArrayitem_t {
				public:				
					size_t idx() const;
					
					Energistics::Etp::v12::Datatypes::ArrayOfBoolean get_ArrayOfBoolean();
					void set_ArrayOfBoolean(const Energistics::Etp::v12::Datatypes::ArrayOfBoolean& v);
					
					Energistics::Etp::v12::Datatypes::ArrayOfInt get_ArrayOfInt();
					void set_ArrayOfInt(const Energistics::Etp::v12::Datatypes::ArrayOfInt& v);
					
					Energistics::Etp::v12::Datatypes::ArrayOfLong get_ArrayOfLong();
					void set_ArrayOfLong(const Energistics::Etp::v12::Datatypes::ArrayOfLong& v);
					
					Energistics::Etp::v12::Datatypes::ArrayOfFloat get_ArrayOfFloat();
					void set_ArrayOfFloat(const Energistics::Etp::v12::Datatypes::ArrayOfFloat& v);
					
					Energistics::Etp::v12::Datatypes::ArrayOfDouble get_ArrayOfDouble();
					void set_ArrayOfDouble(const Energistics::Etp::v12::Datatypes::ArrayOfDouble& v);
					
					Energistics::Etp::v12::Datatypes::ArrayOfString get_ArrayOfString();
					void set_ArrayOfString(const Energistics::Etp::v12::Datatypes::ArrayOfString& v);
					
					std::string get_bytes();
					void set_bytes(const std::string& v);
				};				
			};			
		};		
	};	
};

namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Datatypes {			
				struct AnyArray{				
					Energistics::Etp::v12::Datatypes::AnyArrayitem_t item;
				};				
			};			
		};		
	};	
};

namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Datatypes {			
				namespace DataArrayTypes {				
					struct DataArray{					
						std::vector<int64_t> dimensions;
						Energistics::Etp::v12::Datatypes::AnyArray data;
					};					
				};				
			};			
		};		
	};	
};
%template(MapStringDataArray) std::map<std::string, Energistics::Etp::v12::Datatypes::DataArrayTypes::DataArray>;

namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Datatypes {			
				enum AnyArrayType {				
					arrayOfBoolean=0,
					arrayOfInt=1,
					arrayOfLong=2,
					arrayOfFloat=3,
					arrayOfDouble=4,
					arrayOfString=5,
					bytes=6
				};				
			};			
		};		
	};	
};

namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Datatypes {			
				namespace DataArrayTypes {				
					struct DataArrayMetadata{					
						std::vector<int64_t> dimensions;
						Energistics::Etp::v12::Datatypes::AnyArrayType arrayType;
					};					
				};				
			};			
		};		
	};	
};
%template(MapStringDataArrayMetadata) std::map<std::string, Energistics::Etp::v12::Datatypes::DataArrayTypes::DataArrayMetadata>;

namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Datatypes {			
				namespace DataArrayTypes {				
					struct PutDataArraysType{
						Energistics::Etp::v12::Datatypes::DataArrayTypes::DataArrayIdentifier uid;
						Energistics::Etp::v12::Datatypes::DataArrayTypes::DataArray array;
					};					
				};				
			};			
		};		
	};	
};
%template(MapStringPutDataArraysType) std::map<std::string, Energistics::Etp::v12::Datatypes::DataArrayTypes::PutDataArraysType>;

namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Datatypes {			
				namespace DataArrayTypes {				
					struct GetDataSubarraysType{					
						Energistics::Etp::v12::Datatypes::DataArrayTypes::DataArrayIdentifier uid;
						std::vector<int64_t> starts;
						std::vector<int64_t> counts;
					};					
				};				
			};			
		};		
	};	
};
%template(MapStringGetDataSubarraysType) std::map<std::string, Energistics::Etp::v12::Datatypes::DataArrayTypes::GetDataSubarraysType>;

namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Datatypes {			
				namespace DataArrayTypes {				
					struct PutDataSubarraysType{					
						Energistics::Etp::v12::Datatypes::DataArrayTypes::DataArrayIdentifier uid;
						Energistics::Etp::v12::Datatypes::AnyArray data;
						std::vector<int64_t> starts;
						std::vector<int64_t> counts;
					};					
				};				
			};			
		};		
	};	
};
%template(MapStringPutDataSubarraysType) std::map<std::string, Energistics::Etp::v12::Datatypes::DataArrayTypes::PutDataSubarraysType>;

namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Datatypes {			
				namespace DataArrayTypes {				
					struct PutUninitializedDataArrayType{					
						Energistics::Etp::v12::Datatypes::DataArrayTypes::DataArrayIdentifier uid;
						Energistics::Etp::v12::Datatypes::DataArrayTypes::DataArrayMetadata metadata;
					};					
				};				
			};			
		};		
	};	
};
%template(MapStringPutUninitializedDataArrayType) std::map<std::string, Energistics::Etp::v12::Datatypes::DataArrayTypes::PutUninitializedDataArrayType>;

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

namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace Store {				
					struct PutDataObjects{					
						std::map<std::string, Energistics::Etp::v12::Datatypes::Object::DataObject> dataObjects;
						bool pruneContainedObjects=false;
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
				namespace Store {				
					struct PutDataObjectsResponse{					
						std::map<std::string, Energistics::Etp::v12::Datatypes::Object::PutResponse> success;
						static const int messageTypeId=9;
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
					struct DeleteDataObjects{					
						std::map<std::string, std::string> uris;
						bool pruneContainedObjects=false;
						static const int messageTypeId=3;
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
					struct DeleteDataObjectsResponse{					
						std::map<std::string, Energistics::Etp::v12::Datatypes::ArrayOfString> deletedUris;
						static const int messageTypeId=10;
					};					
				};				
			};			
		};		
	};	
};

/**************** DATA ARRAY PROTOCOL  *****************/

namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace DataArray {				
					struct GetDataArrays{					
						std::map<std::string, Energistics::Etp::v12::Datatypes::DataArrayTypes::DataArrayIdentifier> dataArrays;
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
				namespace DataArray {				
					struct GetDataArraysResponse{					
						std::map<std::string, Energistics::Etp::v12::Datatypes::DataArrayTypes::DataArray> dataArrays;
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
				namespace DataArray {				
					struct GetDataSubarrays{					
						std::map<std::string, Energistics::Etp::v12::Datatypes::DataArrayTypes::GetDataSubarraysType> dataSubarrays;
						static const int messageTypeId=3;
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
				namespace DataArray {				
					struct GetDataSubarraysResponse{					
						std::map<std::string, Energistics::Etp::v12::Datatypes::DataArrayTypes::DataArray> dataSubarrays;
						static const int messageTypeId=8;
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
				namespace DataArray {				
					struct PutDataArrays{					
						std::map<std::string, Energistics::Etp::v12::Datatypes::DataArrayTypes::PutDataArraysType> dataArrays;
						static const int messageTypeId=4;
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
				namespace DataArray {				
					struct PutDataArraysResponse{					
						std::map<std::string, std::string> success;
						static const int messageTypeId=10;
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
				namespace DataArray {				
					struct PutDataSubarrays{					
						std::map<std::string, Energistics::Etp::v12::Datatypes::DataArrayTypes::PutDataSubarraysType> dataSubarrays;
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
				namespace DataArray {				
					struct PutDataSubarraysResponse{					
						std::map<std::string, std::string> success;
						static const int messageTypeId=11;
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
				namespace DataArray {				
					struct PutUninitializedDataArrays{					
						std::map<std::string, Energistics::Etp::v12::Datatypes::DataArrayTypes::PutUninitializedDataArrayType> dataArrays;
						static const int messageTypeId=9;
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
				namespace DataArray {				
					struct PutUninitializedDataArraysResponse{					
						std::map<std::string, std::string> success;
						static const int messageTypeId=12;
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
				namespace DataArray {				
					struct GetDataArrayMetadata{					
						std::map<std::string, Energistics::Etp::v12::Datatypes::DataArrayTypes::DataArrayIdentifier> dataArrays;
						static const int messageTypeId=6;
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
				namespace DataArray {				
					struct GetDataArrayMetadataResponse{					
						std::map<std::string, Energistics::Etp::v12::Datatypes::DataArrayTypes::DataArrayMetadata> arrayMetadata;
						static const int messageTypeId=7;
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
%shared_ptr(ETP_NS::PlainServerSession)

%module(directors="1") fesapi
%feature("director") ETP_NS::CoreHandlers;
%feature("director") ETP_NS::DiscoveryHandlers;
%feature("director") ETP_NS::StoreHandlers;
%feature("director") ETP_NS::StoreNotificationHandlers;
%feature("director") ETP_NS::DataArrayHandlers;
%feature("director") ETP_NS::ServerInitializationParameters;


/* Following extensions aims at preventing the Python garbage collector from 
   garbage collecting a protocol handler that may be still used by a session. */
#ifdef SWIGPYTHON
	%fragment("core_handler_reference_init", "init") {
	  core_handler_reference();
	}

	%fragment("core_handler_reference_function", "header", fragment="core_handler_reference_init") {

	static PyObject *core_handler_reference() {
	  static PyObject *core_handler_reference_string = SWIG_Python_str_FromChar("__core_handler_reference");
	  return core_handler_reference_string;
	}

	}

	%extend ETP_NS::AbstractSession {
	%typemap(ret, fragment="core_handler_reference_function") void setCoreProtocolHandlers(std::shared_ptr<ETP_NS::CoreHandlers> coreHandlers) %{
	  PyObject_SetAttr($self, core_handler_reference(), args);
	%}
	}
	
	%fragment("discovery_handler_reference_init", "init") {
	  discovery_handler_reference();
	}

	%fragment("discovery_handler_reference_function", "header", fragment="discovery_handler_reference_init") {

	static PyObject *discovery_handler_reference() {
	  static PyObject *discovery_handler_reference_string = SWIG_Python_str_FromChar("__discovery_handler_reference");
	  return discovery_handler_reference_string;
	}

	}

	%extend ETP_NS::AbstractSession {
	%typemap(ret, fragment="discovery_handler_reference_function") void setDiscoveryProtocolHandlers(std::shared_ptr<DiscoveryHandlers> discoveryHandlers) %{
	  PyObject_SetAttr($self, discovery_handler_reference(), args);
	%}
	}
	
	%fragment("store_handler_reference_init", "init") {
	  store_handler_reference();
	}

	%fragment("store_handler_reference_function", "header", fragment="store_handler_reference_init") {

	static PyObject *store_handler_reference() {
	  static PyObject *store_handler_reference_string = SWIG_Python_str_FromChar("__store_handler_reference");
	  return store_handler_reference_string;
	}

	}

	%extend ETP_NS::AbstractSession {
	%typemap(ret, fragment="store_handler_reference_function") void setStoreProtocolHandlers(std::shared_ptr<StoreHandlers> storeHandlers) %{
	  PyObject_SetAttr($self, store_handler_reference(), args);
	%}
	}
	
	%fragment("store_notification_handler_reference_init", "init") {
	  store_notification_handler_reference();
	}

	%fragment("store_notification_handler_reference_function", "header", fragment="store_notification_handler_reference_init") {

	static PyObject *store_notification_handler_reference() {
	  static PyObject *store_notification_handler_reference_string = SWIG_Python_str_FromChar("__store_notification_handler_reference");
	  return store_notification_handler_reference_string;
	}

	}

	%extend ETP_NS::AbstractSession {
	%typemap(ret, fragment="store_notification_handler_reference_function") void setStoreNotificationProtocolHandlers(std::shared_ptr<ETP_NS::StoreNotificationHandlers> storeNotificationHandlers) %{
	  PyObject_SetAttr($self, store_notification_handler_reference(), args);
	%}
	}
	
	%fragment("data_array_handler_reference_init", "init") {
	  data_array_handler_reference();
	}

	%fragment("data_array_handler_reference_function", "header", fragment="data_array_handler_reference_init") {

	static PyObject *data_array_handler_reference() {
	  static PyObject *data_array_handler_reference_string = SWIG_Python_str_FromChar("__data_array_handler_reference");
	  return data_array_handler_reference_string;
	}

	}

	%extend ETP_NS::AbstractSession {
	%typemap(ret, fragment="data_array_handler_reference_function") void setDataArrayProtocolHandlers(std::shared_ptr<DataArrayHandlers> dataArrayHandlers) %{
	  PyObject_SetAttr($self, data_array_handler_reference(), args);
	%}
	}
#endif 
	
#ifdef SWIGCSHARP
%typemap(cscode) ETP_NS::AbstractSession %{
  private CoreHandlers coreHandlersReference;
  private DiscoveryHandlers discoveryHandlersReference;
  private StoreHandlers storeHandlersReference;
  private StoreNotificationHandlers storeNotificationHandlersReference;
  private DataArrayHandlers dataArrayHandlersReference;
%}

%typemap(csin,
         post="      coreHandlersReference = $csinput;"
         ) std::shared_ptr<ETP_NS::CoreHandlers> coreHandlers "CoreHandlers.getCPtr($csinput)"
		 
%typemap(csin,
         post="      discoveryHandlersReference = $csinput;"
         ) std::shared_ptr<ETP_NS::DiscoveryHandlers> discoveryHandlers "DiscoveryHandlers.getCPtr($csinput)"

%typemap(csin,
         post="      storeHandlersReference = $csinput;"
         ) std::shared_ptr<ETP_NS::StoreHandlers> storeHandlers "StoreHandlers.getCPtr($csinput)"
		 
%typemap(csin,
         post="      storeNotificationHandlersReference = $csinput;"
         ) std::shared_ptr<ETP_NS::StoreNotificationHandlers> storeNotificationHandlers "StoreNotificationHandlers.getCPtr($csinput)"
		 
%typemap(csin,
         post="      dataArrayHandlersReference = $csinput;"
         ) std::shared_ptr<ETP_NS::DataArrayHandlers> dataArrayHandlers "DataArrayHandlers.getCPtr($csinput)"
#endif	  
	  
#ifdef SWIGJAVA
%typemap(javacode) ETP_NS::AbstractSession %{
  private CoreHandlers coreHandlersReference;
  private DiscoveryHandlers discoveryHandlersReference;
  private StoreHandlers storeHandlersReference;
  private StoreNotificationHandlers storeNotificationHandlersReference;
  private DataArrayHandlers dataArrayHandlersReference;
%}

%typemap(javain, 
         post="      coreHandlersReference = $javainput;"
         ) std::shared_ptr<ETP_NS::CoreHandlers> coreHandlers "CoreHandlers.getCPtr($javainput)"
		 
%typemap(javain, 
         post="      discoveryHandlersReference = $javainput;"
         ) std::shared_ptr<ETP_NS::DiscoveryHandlers> discoveryHandlers "DiscoveryHandlers.getCPtr($javainput)"
		 
%typemap(javain, 
         post="      storeHandlersReference = $javainput;"
         ) std::shared_ptr<ETP_NS::StoreHandlers> storeHandlers "StoreHandlers.getCPtr($javainput)"
		 
%typemap(javain, 
         post="      storeNotificationHandlersReference = $javainput;"
         ) std::shared_ptr<ETP_NS::StoreNotificationHandlers> storeNotificationHandlers "StoreNotificationHandlers.getCPtr($javainput)"
		 
%typemap(javain, 
         post="      dataArrayHandlersReference = $javainput;"
         ) std::shared_ptr<ETP_NS::DataArrayHandlers> dataArrayHandlers "DataArrayHandlers.getCPtr($javainput)"
#endif

namespace ETP_NS
{
	class AbstractSession;

	%nodefaultctor ProtocolHandlers;
	class ProtocolHandlers
	{
	public:
		AbstractSession* getSession();
	};

	class CoreHandlers : public ProtocolHandlers
	{
	public:
		CoreHandlers(AbstractSession* mySession);
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
		DiscoveryHandlers(AbstractSession* mySession);
		virtual ~DiscoveryHandlers() {}

		virtual void on_GetResources(const Energistics::Etp::v12::Protocol::Discovery::GetResources & msg, int64_t correlationId);
		virtual void on_GetResourcesResponse(const Energistics::Etp::v12::Protocol::Discovery::GetResourcesResponse & msg, int64_t correlationId);
	};
	
	class StoreHandlers : public ProtocolHandlers
	{
	public:
		StoreHandlers(AbstractSession* mySession): ProtocolHandlers(mySession) {}
		virtual ~StoreHandlers() {}

	    virtual void on_GetDataObjects(const Energistics::Etp::v12::Protocol::Store::GetDataObjects & msg, int64_t correlationId);
	    virtual void on_GetDataObjectsResponse(const Energistics::Etp::v12::Protocol::Store::GetDataObjectsResponse & msg, int64_t correlationId);
	    virtual void on_PutDataObjects(const Energistics::Etp::v12::Protocol::Store::PutDataObjects & msg, int64_t correlationId);
		virtual void on_PutDataObjectsResponse(const Energistics::Etp::v12::Protocol::Store::PutDataObjectsResponse & msg, int64_t correlationId);
	    virtual void on_DeleteDataObjects(const Energistics::Etp::v12::Protocol::Store::DeleteDataObjects & msg, int64_t correlationId);
		virtual void on_DeleteDataObjectsResponse(const Energistics::Etp::v12::Protocol::Store::DeleteDataObjectsResponse & msg, int64_t correlationId);
	};
	
	class StoreNotificationHandlers : public ProtocolHandlers
	{
	public:
		StoreNotificationHandlers(AbstractSession* mySession): ProtocolHandlers(mySession) {}
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
		DataArrayHandlers(AbstractSession* mySession): ProtocolHandlers(mySession) {}
		virtual ~DataArrayHandlers() {}

	    virtual void on_GetDataArrays(const Energistics::Etp::v12::Protocol::DataArray::GetDataArrays & gda, int64_t correlationId);
		virtual void on_GetDataArraysResponse(Energistics::Etp::v12::Protocol::DataArray::GetDataArraysResponse & gdar);
	    virtual void on_PutDataArrays(const Energistics::Etp::v12::Protocol::DataArray::PutDataArrays & pda, int64_t correlationId);
		virtual void on_PutDataArraysResponse(const Energistics::Etp::v12::Protocol::DataArray::PutDataArraysResponse & msg, int64_t correlationId);
	    virtual void on_GetDataSubarrays(const Energistics::Etp::v12::Protocol::DataArray::GetDataSubarrays & msg, int64_t correlationId);
		virtual void on_GetDataSubarraysResponse(const Energistics::Etp::v12::Protocol::DataArray::GetDataSubarraysResponse & msg);
	    virtual void on_PutDataSubarrays(const Energistics::Etp::v12::Protocol::DataArray::PutDataSubarrays & msg, int64_t correlationId);
		virtual void on_PutDataSubarraysResponse(const Energistics::Etp::v12::Protocol::DataArray::PutDataSubarraysResponse & msg, int64_t correlationId);
		virtual void on_GetDataArrayMetadata(const Energistics::Etp::v12::Protocol::DataArray::GetDataArrayMetadata & gdam, int64_t correlationId);
		virtual void on_GetDataArrayMetadataResponse(const Energistics::Etp::v12::Protocol::DataArray::GetDataArrayMetadataResponse & gdamr);
		virtual void on_PutUninitializedDataArrays(const Energistics::Etp::v12::Protocol::DataArray::PutUninitializedDataArrays & msg, int64_t correlationId);
		virtual void on_PutUninitializedDataArraysResponse(const Energistics::Etp::v12::Protocol::DataArray::PutUninitializedDataArraysResponse & msg);
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
		%template(send) send<Energistics::Etp::v12::Protocol::Store::GetDataObjectsResponse>;
		%template(send) send<Energistics::Etp::v12::Protocol::Store::PutDataObjects>;
		%template(send) send<Energistics::Etp::v12::Protocol::Store::PutDataObjectsResponse>;
		%template(send) send<Energistics::Etp::v12::Protocol::Store::DeleteDataObjects>;
		%template(send) send<Energistics::Etp::v12::Protocol::Store::DeleteDataObjectsResponse>;
		
		%template(send) send<Energistics::Etp::v12::Protocol::DataArray::GetDataArrays>;
		%template(send) send<Energistics::Etp::v12::Protocol::DataArray::GetDataArraysResponse>;
		%template(send) send<Energistics::Etp::v12::Protocol::DataArray::PutDataArrays>;
		%template(send) send<Energistics::Etp::v12::Protocol::DataArray::PutDataArraysResponse>;
		%template(send) send<Energistics::Etp::v12::Protocol::DataArray::GetDataSubarrays>;
		%template(send) send<Energistics::Etp::v12::Protocol::DataArray::GetDataSubarraysResponse>;
		%template(send) send<Energistics::Etp::v12::Protocol::DataArray::PutDataSubarrays>;
		%template(send) send<Energistics::Etp::v12::Protocol::DataArray::PutDataSubarraysResponse>;
		%template(send) send<Energistics::Etp::v12::Protocol::DataArray::GetDataArrayMetadata>;
		%template(send) send<Energistics::Etp::v12::Protocol::DataArray::GetDataArrayMetadataResponse>;
		%template(send) send<Energistics::Etp::v12::Protocol::DataArray::PutUninitializedDataArrays>;
		%template(send) send<Energistics::Etp::v12::Protocol::DataArray::PutUninitializedDataArraysResponse>;
		
		void close();
	};

	namespace EtpHelpers {
		Energistics::Etp::v12::Datatypes::ErrorInfo validateUri(const std::string & uri, ETP_NS::AbstractSession* session = nullptr);
		Energistics::Etp::v12::Datatypes::ErrorInfo validateDataObjectUri(const std::string & uri, ETP_NS::AbstractSession* session = nullptr);
		Energistics::Etp::v12::Datatypes::Object::Resource buildEtpResourceFromEnergisticsObject(const COMMON_NS::AbstractObject * const obj, bool countRels = true);
		Energistics::Etp::v12::Datatypes::Object::DataObject buildEtpDataObjectFromEnergisticsObject(COMMON_NS::AbstractObject * obj, bool includeSerialization = true);	
		Energistics::Etp::v12::Protocol::Core::ProtocolException buildSingleMessageProtocolException(int32_t m_code, const std::string & m_message);
	}

	/******************* CLIENT ***************************/

	%nodefaultctor PlainClientSession;
	class PlainClientSession : public AbstractSession
	{
	public:
		bool run();
	};

	namespace ClientSessionLaunchers
	{
		std::shared_ptr<ETP_NS::PlainClientSession> createClientSession(const std::string & host, const std::string & port, const std::string & target, const std::string & authorization);
	}
	
	/******************* SERVER ***************************/
	
	class ServerInitializationParameters
	{
	public:
		ServerInitializationParameters();
		ServerInitializationParameters(const std::string & serverUuid);
		virtual ~ServerInitializationParameters();

		virtual std::string getApplicationName();
		virtual std::string getApplicationVersion();
		virtual std::string getContactEmail();
		virtual std::string getContactName();
		virtual std::string getContactPhone();
		virtual std::string getOrganizationName();

		virtual std::vector<std::string> makeSupportedEncodings();
		virtual std::map<std::string, Energistics::Etp::v12::Datatypes::DataValue> makeEndpointCapabilities();
		virtual std::vector<Energistics::Etp::v12::Datatypes::SupportedDataObject> makeSupportedDataObjects();
		virtual std::vector<Energistics::Etp::v12::Datatypes::SupportedProtocol> makeSupportedProtocols();

		virtual void postSessionCreationOperation(AbstractSession* session);
	};
	
	%nodefaultctor PlainServerSession;
	class PlainServerSession : public AbstractSession
	{
	public:
	};

	template <class T>
	class Server
	{
	public:
		Server(ServerInitializationParameters* serverInitializationParams) : serverInitializationParams_(serverInitializationParams) {}
		std::vector< std::shared_ptr<T> >& getSessions() { return sessions_; }
		void listen(const std::string & host, unsigned short port, int threadCount);
	};
	%template(PlainServer) ETP_NS::Server<ETP_NS::PlainServerSession>;

}
