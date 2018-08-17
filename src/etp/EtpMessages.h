#ifndef ETP_MESSAGES__
#define ETP_MESSAGES__

#include <map>
#include <vector>
#include <string>
#include <sstream>
#include <iostream>

#include "boost/any.hpp"
#include "avro/Specific.hh"
#include "avro/Encoder.hh"
#include "avro/Decoder.hh"

namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Datatypes {			
				enum AnyArrayTypes {				
					arrayOfBoolean=0,
					arrayOfBytes=1,
					arrayOfInt=2,
					arrayOfLong=3,
					arrayOfFloat=4,
					arrayOfDouble=5
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Datatypes::AnyArrayTypes> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Datatypes::AnyArrayTypes& v) {		
			e.encodeEnum(v);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Datatypes::AnyArrayTypes& v) {		
			v = static_cast<Energistics::Etp::v12::Datatypes::AnyArrayTypes>(e.decodeEnum());
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Datatypes {			
				struct ArrayOfBoolean{				
					std::vector<bool> m_values;
				};				
				typedef boost::shared_ptr<ArrayOfBoolean> ArrayOfBooleanPtr;
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Datatypes::ArrayOfBoolean> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Datatypes::ArrayOfBoolean& v) {		
			avro::encode(e, v.m_values);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Datatypes::ArrayOfBoolean& v) {		
			avro::decode(e, v.m_values);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Datatypes {			
				struct ArrayOfFloat{				
					std::vector<float> m_values;
				};				
				typedef boost::shared_ptr<ArrayOfFloat> ArrayOfFloatPtr;
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Datatypes::ArrayOfFloat> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Datatypes::ArrayOfFloat& v) {		
			avro::encode(e, v.m_values);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Datatypes::ArrayOfFloat& v) {		
			avro::decode(e, v.m_values);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Datatypes {			
				struct ArrayOfDouble{				
					std::vector<double> m_values;
				};				
				typedef boost::shared_ptr<ArrayOfDouble> ArrayOfDoublePtr;
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Datatypes::ArrayOfDouble> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Datatypes::ArrayOfDouble& v) {		
			avro::encode(e, v.m_values);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Datatypes::ArrayOfDouble& v) {		
			avro::decode(e, v.m_values);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Datatypes {			
				struct ArrayOfInt{				
					std::vector<int32_t> m_values;
				};				
				typedef boost::shared_ptr<ArrayOfInt> ArrayOfIntPtr;
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Datatypes::ArrayOfInt> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Datatypes::ArrayOfInt& v) {		
			avro::encode(e, v.m_values);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Datatypes::ArrayOfInt& v) {		
			avro::decode(e, v.m_values);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Datatypes {			
				struct ArrayOfLong{				
					std::vector<int64_t> m_values;
				};				
				typedef boost::shared_ptr<ArrayOfLong> ArrayOfLongPtr;
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Datatypes::ArrayOfLong> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Datatypes::ArrayOfLong& v) {		
			avro::encode(e, v.m_values);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Datatypes::ArrayOfLong& v) {		
			avro::decode(e, v.m_values);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Datatypes {			
				struct AnyArrayitem_t {
				private:				
					size_t idx_=0;
					boost::any value_;
								
				public:				
					size_t idx() const { return idx_; }
					bool is_null() const { return idx_==0; }
					void set_null() { idx_=0; value_ = boost::any(); }
					Energistics::Etp::v12::Datatypes::ArrayOfBoolean& get_ArrayOfBoolean()  {					
						if (idx_ != 1) {						
							throw avro::Exception("Invalid type for union.");
						}						
						return boost::any_cast< Energistics::Etp::v12::Datatypes::ArrayOfBoolean& >(value_);
					}					
					void set_ArrayOfBoolean(const Energistics::Etp::v12::Datatypes::ArrayOfBoolean& v) {					
						idx_ = 1;
						value_ = v;
					}					
					std::string& get_bytes()  {					
						if (idx_ != 2) {						
							throw avro::Exception("Invalid type for union.");
						}						
						return boost::any_cast< std::string& >(value_);
					}					
					void set_bytes(const std::string& v) {					
						idx_ = 2;
						value_ = v;
					}					
					Energistics::Etp::v12::Datatypes::ArrayOfInt& get_ArrayOfInt()  {					
						if (idx_ != 3) {						
							throw avro::Exception("Invalid type for union.");
						}						
						return boost::any_cast< Energistics::Etp::v12::Datatypes::ArrayOfInt& >(value_);
					}					
					void set_ArrayOfInt(const Energistics::Etp::v12::Datatypes::ArrayOfInt& v) {					
						idx_ = 3;
						value_ = v;
					}					
					Energistics::Etp::v12::Datatypes::ArrayOfLong& get_ArrayOfLong()  {					
						if (idx_ != 4) {						
							throw avro::Exception("Invalid type for union.");
						}						
						return boost::any_cast< Energistics::Etp::v12::Datatypes::ArrayOfLong& >(value_);
					}					
					void set_ArrayOfLong(const Energistics::Etp::v12::Datatypes::ArrayOfLong& v) {					
						idx_ = 4;
						value_ = v;
					}					
					Energistics::Etp::v12::Datatypes::ArrayOfFloat& get_ArrayOfFloat()  {					
						if (idx_ != 5) {						
							throw avro::Exception("Invalid type for union.");
						}						
						return boost::any_cast< Energistics::Etp::v12::Datatypes::ArrayOfFloat& >(value_);
					}					
					void set_ArrayOfFloat(const Energistics::Etp::v12::Datatypes::ArrayOfFloat& v) {					
						idx_ = 5;
						value_ = v;
					}					
					Energistics::Etp::v12::Datatypes::ArrayOfDouble& get_ArrayOfDouble()  {					
						if (idx_ != 6) {						
							throw avro::Exception("Invalid type for union.");
						}						
						return boost::any_cast< Energistics::Etp::v12::Datatypes::ArrayOfDouble& >(value_);
					}					
					void set_ArrayOfDouble(const Energistics::Etp::v12::Datatypes::ArrayOfDouble& v) {					
						idx_ = 6;
						value_ = v;
					}					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Datatypes::AnyArrayitem_t> {
	
		static void encode(Encoder& e, Energistics::Etp::v12::Datatypes::AnyArrayitem_t v) {
		
			e.encodeUnionIndex(v.idx());
			switch (v.idx()) {			
				case 0:				
					e.encodeNull();
					break;								
				case 1:				
					avro::encode(e, v.get_ArrayOfBoolean());
					break;								
				case 2:				
					avro::encode(e, v.get_bytes());
					break;								
				case 3:				
					avro::encode(e, v.get_ArrayOfInt());
					break;								
				case 4:				
					avro::encode(e, v.get_ArrayOfLong());
					break;								
				case 5:				
					avro::encode(e, v.get_ArrayOfFloat());
					break;								
				case 6:				
					avro::encode(e, v.get_ArrayOfDouble());
					break;								
			}			
		}		
		static void decode(Decoder& d, Energistics::Etp::v12::Datatypes::AnyArrayitem_t& v) {
		
			size_t n = d.decodeUnionIndex();
			if (n >= 7) { throw avro::Exception("Union index too big"); }
			switch (n) {			
				case 0:				
					{					
						d.decodeNull();
						v.set_null();
					}					
					break;								
				case 1:				
					{					
						Energistics::Etp::v12::Datatypes::ArrayOfBoolean vv;
						avro::decode(d, vv);
						v.set_ArrayOfBoolean(vv);
					}					
					break;								
				case 2:				
					{					
						std::string vv;
						avro::decode(d, vv);
						v.set_bytes(vv);
					}					
					break;								
				case 3:				
					{					
						Energistics::Etp::v12::Datatypes::ArrayOfInt vv;
						avro::decode(d, vv);
						v.set_ArrayOfInt(vv);
					}					
					break;								
				case 4:				
					{					
						Energistics::Etp::v12::Datatypes::ArrayOfLong vv;
						avro::decode(d, vv);
						v.set_ArrayOfLong(vv);
					}					
					break;								
				case 5:				
					{					
						Energistics::Etp::v12::Datatypes::ArrayOfFloat vv;
						avro::decode(d, vv);
						v.set_ArrayOfFloat(vv);
					}					
					break;								
				case 6:				
					{					
						Energistics::Etp::v12::Datatypes::ArrayOfDouble vv;
						avro::decode(d, vv);
						v.set_ArrayOfDouble(vv);
					}					
					break;								
			}			
		}		
	};	
}

namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Datatypes {			
				struct AnyArray{				
					Energistics::Etp::v12::Datatypes::AnyArrayitem_t m_item;
				};				
				typedef boost::shared_ptr<AnyArray> AnyArrayPtr;
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Datatypes::AnyArray> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Datatypes::AnyArray& v) {		
			avro::encode(e, v.m_item);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Datatypes::AnyArray& v) {		
			avro::decode(e, v.m_item);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Datatypes {			
				struct AttributeMetadataRecord{				
					int32_t m_attributeId;
					std::string m_attributeName;
					std::string m_dataType;
					std::string m_description;
				};				
				typedef boost::shared_ptr<AttributeMetadataRecord> AttributeMetadataRecordPtr;
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Datatypes::AttributeMetadataRecord> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Datatypes::AttributeMetadataRecord& v) {		
			avro::encode(e, v.m_attributeId);
			avro::encode(e, v.m_attributeName);
			avro::encode(e, v.m_dataType);
			avro::encode(e, v.m_description);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Datatypes::AttributeMetadataRecord& v) {		
			avro::decode(e, v.m_attributeId);
			avro::decode(e, v.m_attributeName);
			avro::decode(e, v.m_dataType);
			avro::decode(e, v.m_description);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Datatypes {			
				struct Contact{				
					std::string m_organizationName;
					std::string m_contactName;
					std::string m_contactPhone;
					std::string m_contactEmail;
				};				
				typedef boost::shared_ptr<Contact> ContactPtr;
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Datatypes::Contact> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Datatypes::Contact& v) {		
			avro::encode(e, v.m_organizationName);
			avro::encode(e, v.m_contactName);
			avro::encode(e, v.m_contactPhone);
			avro::encode(e, v.m_contactEmail);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Datatypes::Contact& v) {		
			avro::decode(e, v.m_organizationName);
			avro::decode(e, v.m_contactName);
			avro::decode(e, v.m_contactPhone);
			avro::decode(e, v.m_contactEmail);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Datatypes {			
				struct DataValueitem_t {
				private:				
					size_t idx_=0;
					boost::any value_;
								
				public:				
					size_t idx() const { return idx_; }
					bool is_null() const { return idx_==0; }
					void set_null() { idx_=0; value_ = boost::any(); }
					double& get_double()  {					
						if (idx_ != 1) {						
							throw avro::Exception("Invalid type for union.");
						}						
						return boost::any_cast< double& >(value_);
					}					
					void set_double(const double& v) {					
						idx_ = 1;
						value_ = v;
					}					
					float& get_float()  {					
						if (idx_ != 2) {						
							throw avro::Exception("Invalid type for union.");
						}						
						return boost::any_cast< float& >(value_);
					}					
					void set_float(const float& v) {					
						idx_ = 2;
						value_ = v;
					}					
					int32_t& get_int()  {					
						if (idx_ != 3) {						
							throw avro::Exception("Invalid type for union.");
						}						
						return boost::any_cast< int32_t& >(value_);
					}					
					void set_int(const int32_t& v) {					
						idx_ = 3;
						value_ = v;
					}					
					int64_t& get_long()  {					
						if (idx_ != 4) {						
							throw avro::Exception("Invalid type for union.");
						}						
						return boost::any_cast< int64_t& >(value_);
					}					
					void set_long(const int64_t& v) {					
						idx_ = 4;
						value_ = v;
					}					
					std::string& get_string()  {					
						if (idx_ != 5) {						
							throw avro::Exception("Invalid type for union.");
						}						
						return boost::any_cast< std::string& >(value_);
					}					
					void set_string(const std::string& v) {					
						idx_ = 5;
						value_ = v;
					}					
					Energistics::Etp::v12::Datatypes::ArrayOfDouble& get_ArrayOfDouble()  {					
						if (idx_ != 6) {						
							throw avro::Exception("Invalid type for union.");
						}						
						return boost::any_cast< Energistics::Etp::v12::Datatypes::ArrayOfDouble& >(value_);
					}					
					void set_ArrayOfDouble(const Energistics::Etp::v12::Datatypes::ArrayOfDouble& v) {					
						idx_ = 6;
						value_ = v;
					}					
					bool& get_boolean()  {					
						if (idx_ != 7) {						
							throw avro::Exception("Invalid type for union.");
						}						
						return boost::any_cast< bool& >(value_);
					}					
					void set_boolean(const bool& v) {					
						idx_ = 7;
						value_ = v;
					}					
					std::string& get_bytes()  {					
						if (idx_ != 8) {						
							throw avro::Exception("Invalid type for union.");
						}						
						return boost::any_cast< std::string& >(value_);
					}					
					void set_bytes(const std::string& v) {					
						idx_ = 8;
						value_ = v;
					}					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Datatypes::DataValueitem_t> {
	
		static void encode(Encoder& e, Energistics::Etp::v12::Datatypes::DataValueitem_t v) {
		
			e.encodeUnionIndex(v.idx());
			switch (v.idx()) {			
				case 0:				
					e.encodeNull();
					break;								
				case 1:				
					avro::encode(e, v.get_double());
					break;								
				case 2:				
					avro::encode(e, v.get_float());
					break;								
				case 3:				
					avro::encode(e, v.get_int());
					break;								
				case 4:				
					avro::encode(e, v.get_long());
					break;								
				case 5:				
					avro::encode(e, v.get_string());
					break;								
				case 6:				
					avro::encode(e, v.get_ArrayOfDouble());
					break;								
				case 7:				
					avro::encode(e, v.get_boolean());
					break;								
				case 8:				
					avro::encode(e, v.get_bytes());
					break;								
			}			
		}		
		static void decode(Decoder& d, Energistics::Etp::v12::Datatypes::DataValueitem_t& v) {
		
			size_t n = d.decodeUnionIndex();
			if (n >= 9) { throw avro::Exception("Union index too big"); }
			switch (n) {			
				case 0:				
					{					
						d.decodeNull();
						v.set_null();
					}					
					break;								
				case 1:				
					{					
						double vv;
						avro::decode(d, vv);
						v.set_double(vv);
					}					
					break;								
				case 2:				
					{					
						float vv;
						avro::decode(d, vv);
						v.set_float(vv);
					}					
					break;								
				case 3:				
					{					
						int32_t vv;
						avro::decode(d, vv);
						v.set_int(vv);
					}					
					break;								
				case 4:				
					{					
						int64_t vv;
						avro::decode(d, vv);
						v.set_long(vv);
					}					
					break;								
				case 5:				
					{					
						std::string vv;
						avro::decode(d, vv);
						v.set_string(vv);
					}					
					break;								
				case 6:				
					{					
						Energistics::Etp::v12::Datatypes::ArrayOfDouble vv;
						avro::decode(d, vv);
						v.set_ArrayOfDouble(vv);
					}					
					break;								
				case 7:				
					{					
						bool vv;
						avro::decode(d, vv);
						v.set_boolean(vv);
					}					
					break;								
				case 8:				
					{					
						std::string vv;
						avro::decode(d, vv);
						v.set_bytes(vv);
					}					
					break;								
			}			
		}		
	};	
}

namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Datatypes {			
				struct DataValue{				
					Energistics::Etp::v12::Datatypes::DataValueitem_t m_item;
				};				
				typedef boost::shared_ptr<DataValue> DataValuePtr;
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Datatypes::DataValue> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Datatypes::DataValue& v) {		
			avro::encode(e, v.m_item);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Datatypes::DataValue& v) {		
			avro::decode(e, v.m_item);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Datatypes {			
				struct DataAttribute{				
					int32_t m_attributeId;
					Energistics::Etp::v12::Datatypes::DataValue m_attributeValue;
				};				
				typedef boost::shared_ptr<DataAttribute> DataAttributePtr;
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Datatypes::DataAttribute> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Datatypes::DataAttribute& v) {		
			avro::encode(e, v.m_attributeId);
			avro::encode(e, v.m_attributeValue);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Datatypes::DataAttribute& v) {		
			avro::decode(e, v.m_attributeId);
			avro::decode(e, v.m_attributeValue);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Datatypes {			
				struct IndexValueitem_t {
				private:				
					size_t idx_=0;
					boost::any value_;
								
				public:				
					size_t idx() const { return idx_; }
					bool is_null() const { return idx_==0; }
					void set_null() { idx_=0; value_ = boost::any(); }
					double& get_double()  {					
						if (idx_ != 1) {						
							throw avro::Exception("Invalid type for union.");
						}						
						return boost::any_cast< double& >(value_);
					}					
					void set_double(const double& v) {					
						idx_ = 1;
						value_ = v;
					}					
					int64_t& get_long()  {					
						if (idx_ != 2) {						
							throw avro::Exception("Invalid type for union.");
						}						
						return boost::any_cast< int64_t& >(value_);
					}					
					void set_long(const int64_t& v) {					
						idx_ = 2;
						value_ = v;
					}					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Datatypes::IndexValueitem_t> {
	
		static void encode(Encoder& e, Energistics::Etp::v12::Datatypes::IndexValueitem_t v) {
		
			e.encodeUnionIndex(v.idx());
			switch (v.idx()) {			
				case 0:				
					e.encodeNull();
					break;								
				case 1:				
					avro::encode(e, v.get_double());
					break;								
				case 2:				
					avro::encode(e, v.get_long());
					break;								
			}			
		}		
		static void decode(Decoder& d, Energistics::Etp::v12::Datatypes::IndexValueitem_t& v) {
		
			size_t n = d.decodeUnionIndex();
			if (n >= 3) { throw avro::Exception("Union index too big"); }
			switch (n) {			
				case 0:				
					{					
						d.decodeNull();
						v.set_null();
					}					
					break;								
				case 1:				
					{					
						double vv;
						avro::decode(d, vv);
						v.set_double(vv);
					}					
					break;								
				case 2:				
					{					
						int64_t vv;
						avro::decode(d, vv);
						v.set_long(vv);
					}					
					break;								
			}			
		}		
	};	
}

namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Datatypes {			
				struct IndexValue{				
					Energistics::Etp::v12::Datatypes::IndexValueitem_t m_item;
				};				
				typedef boost::shared_ptr<IndexValue> IndexValuePtr;
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Datatypes::IndexValue> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Datatypes::IndexValue& v) {		
			avro::encode(e, v.m_item);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Datatypes::IndexValue& v) {		
			avro::decode(e, v.m_item);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Datatypes {			
				struct MessageHeader{				
					int32_t m_protocol;
					int32_t m_messageType;
					int64_t m_correlationId;
					int64_t m_messageId;
					int32_t m_messageFlags;
				};				
				typedef boost::shared_ptr<MessageHeader> MessageHeaderPtr;
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Datatypes::MessageHeader> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Datatypes::MessageHeader& v) {		
			avro::encode(e, v.m_protocol);
			avro::encode(e, v.m_messageType);
			avro::encode(e, v.m_correlationId);
			avro::encode(e, v.m_messageId);
			avro::encode(e, v.m_messageFlags);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Datatypes::MessageHeader& v) {		
			avro::decode(e, v.m_protocol);
			avro::decode(e, v.m_messageType);
			avro::decode(e, v.m_correlationId);
			avro::decode(e, v.m_messageId);
			avro::decode(e, v.m_messageFlags);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Datatypes {			
				enum Protocols {				
					Core=0,
					ChannelStreaming=1,
					ChannelDataFrame=2,
					Discovery=3,
					Store=4,
					StoreNotification=5,
					GrowingObject=6,
					GrowingObjectNotification=7,
					WitsmlSoap=8,
					DataArray=9,
					DataArrayNotification=10,
					ChannelStreamingQuery=11,
					ChannelDataFrameQuery=12,
					DiscoveryQuery=13,
					StoreQuery=14,
					StoreNotificationQuery=15,
					GrowingObjectQuery=16,
					GrowingObjectNotificationQuery=17,
					Transaction=18,
					DirectedDiscovery=19
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Datatypes::Protocols> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Datatypes::Protocols& v) {		
			e.encodeEnum(v);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Datatypes::Protocols& v) {		
			v = static_cast<Energistics::Etp::v12::Datatypes::Protocols>(e.decodeEnum());
		}		
	};	
}
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
				typedef boost::shared_ptr<Version> VersionPtr;
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Datatypes::Version> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Datatypes::Version& v) {		
			avro::encode(e, v.m_major);
			avro::encode(e, v.m_minor);
			avro::encode(e, v.m_revision);
			avro::encode(e, v.m_patch);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Datatypes::Version& v) {		
			avro::decode(e, v.m_major);
			avro::decode(e, v.m_minor);
			avro::decode(e, v.m_revision);
			avro::decode(e, v.m_patch);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Datatypes {			
				struct SupportedProtocol{				
					int32_t m_protocol;
					Energistics::Etp::v12::Datatypes::Version m_protocolVersion;
					std::string m_role;
					std::map<std::string, Energistics::Etp::v12::Datatypes::DataValue> m_protocolCapabilities;
				};				
				typedef boost::shared_ptr<SupportedProtocol> SupportedProtocolPtr;
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Datatypes::SupportedProtocol> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Datatypes::SupportedProtocol& v) {		
			avro::encode(e, v.m_protocol);
			avro::encode(e, v.m_protocolVersion);
			avro::encode(e, v.m_role);
			avro::encode(e, v.m_protocolCapabilities);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Datatypes::SupportedProtocol& v) {		
			avro::decode(e, v.m_protocol);
			avro::decode(e, v.m_protocolVersion);
			avro::decode(e, v.m_role);
			avro::decode(e, v.m_protocolCapabilities);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Datatypes {			
				struct ServerCapabilities{				
					std::string m_applicationName;
					std::string m_applicationVersion;
					std::vector<Energistics::Etp::v12::Datatypes::SupportedProtocol> m_supportedProtocols;
					std::vector<std::string> m_supportedObjects;
					Energistics::Etp::v12::Datatypes::Contact m_contactInformation;
					std::string m_supportedEncodings;
					std::vector<std::string> m_supportedCompression;
				};				
				typedef boost::shared_ptr<ServerCapabilities> ServerCapabilitiesPtr;
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Datatypes::ServerCapabilities> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Datatypes::ServerCapabilities& v) {		
			avro::encode(e, v.m_applicationName);
			avro::encode(e, v.m_applicationVersion);
			avro::encode(e, v.m_supportedProtocols);
			avro::encode(e, v.m_supportedObjects);
			avro::encode(e, v.m_contactInformation);
			avro::encode(e, v.m_supportedEncodings);
			avro::encode(e, v.m_supportedCompression);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Datatypes::ServerCapabilities& v) {		
			avro::decode(e, v.m_applicationName);
			avro::decode(e, v.m_applicationVersion);
			avro::decode(e, v.m_supportedProtocols);
			avro::decode(e, v.m_supportedObjects);
			avro::decode(e, v.m_contactInformation);
			avro::decode(e, v.m_supportedEncodings);
			avro::decode(e, v.m_supportedCompression);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Datatypes {			
				namespace ChannelData {				
					enum ChannelIndexKinds {					
						Time=0,
						Depth=1
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Datatypes::ChannelData::ChannelIndexKinds> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Datatypes::ChannelData::ChannelIndexKinds& v) {		
			e.encodeEnum(v);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Datatypes::ChannelData::ChannelIndexKinds& v) {		
			v = static_cast<Energistics::Etp::v12::Datatypes::ChannelData::ChannelIndexKinds>(e.decodeEnum());
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Datatypes {			
				namespace ChannelData {				
					struct ChannelRangeInfo{					
						std::vector<int64_t> m_channelId;
						int64_t m_startIndex;
						int64_t m_endIndex;
					};					
					typedef boost::shared_ptr<ChannelRangeInfo> ChannelRangeInfoPtr;
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Datatypes::ChannelData::ChannelRangeInfo> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Datatypes::ChannelData::ChannelRangeInfo& v) {		
			avro::encode(e, v.m_channelId);
			avro::encode(e, v.m_startIndex);
			avro::encode(e, v.m_endIndex);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Datatypes::ChannelData::ChannelRangeInfo& v) {		
			avro::decode(e, v.m_channelId);
			avro::decode(e, v.m_startIndex);
			avro::decode(e, v.m_endIndex);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Datatypes {			
				namespace ChannelData {				
					enum ChannelStatuses {					
						Active=0,
						Inactive=1,
						Closed=2
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Datatypes::ChannelData::ChannelStatuses> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Datatypes::ChannelData::ChannelStatuses& v) {		
			e.encodeEnum(v);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Datatypes::ChannelData::ChannelStatuses& v) {		
			v = static_cast<Energistics::Etp::v12::Datatypes::ChannelData::ChannelStatuses>(e.decodeEnum());
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Datatypes {			
				namespace ChannelData {				
					struct DataFrame{					
						std::vector<int64_t> m_index;
						std::vector<Energistics::Etp::v12::Datatypes::DataValue> m_data;
					};					
					typedef boost::shared_ptr<DataFrame> DataFramePtr;
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Datatypes::ChannelData::DataFrame> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Datatypes::ChannelData::DataFrame& v) {		
			avro::encode(e, v.m_index);
			avro::encode(e, v.m_data);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Datatypes::ChannelData::DataFrame& v) {		
			avro::decode(e, v.m_index);
			avro::decode(e, v.m_data);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Datatypes {			
				namespace ChannelData {				
					struct DataItem{					
						std::vector<int64_t> m_indexes;
						int64_t m_channelId;
						Energistics::Etp::v12::Datatypes::DataValue m_value;
						std::vector<Energistics::Etp::v12::Datatypes::DataAttribute> m_valueAttributes;
					};					
					typedef boost::shared_ptr<DataItem> DataItemPtr;
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Datatypes::ChannelData::DataItem> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Datatypes::ChannelData::DataItem& v) {		
			avro::encode(e, v.m_indexes);
			avro::encode(e, v.m_channelId);
			avro::encode(e, v.m_value);
			avro::encode(e, v.m_valueAttributes);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Datatypes::ChannelData::DataItem& v) {		
			avro::decode(e, v.m_indexes);
			avro::decode(e, v.m_channelId);
			avro::decode(e, v.m_value);
			avro::decode(e, v.m_valueAttributes);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Datatypes {			
				namespace ChannelData {				
					enum IndexDirections {					
						Increasing=0,
						Decreasing=1
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Datatypes::ChannelData::IndexDirections> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Datatypes::ChannelData::IndexDirections& v) {		
			e.encodeEnum(v);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Datatypes::ChannelData::IndexDirections& v) {		
			v = static_cast<Energistics::Etp::v12::Datatypes::ChannelData::IndexDirections>(e.decodeEnum());
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Datatypes {			
				namespace ChannelData {				
					struct IndexMetadataRecord{					
						Energistics::Etp::v12::Datatypes::ChannelData::ChannelIndexKinds m_indexKind;
						std::string m_uom;
						std::string m_depthDatum;
						Energistics::Etp::v12::Datatypes::ChannelData::IndexDirections m_direction;
						std::string m_mnemonic;
						std::string m_description;
						std::string m_uri;
						std::map<std::string, Energistics::Etp::v12::Datatypes::DataValue> m_customData;
						int32_t m_scale;
						std::string m_timeDatum;
					};					
					typedef boost::shared_ptr<IndexMetadataRecord> IndexMetadataRecordPtr;
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Datatypes::ChannelData::IndexMetadataRecord> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Datatypes::ChannelData::IndexMetadataRecord& v) {		
			avro::encode(e, v.m_indexKind);
			avro::encode(e, v.m_uom);
			avro::encode(e, v.m_depthDatum);
			avro::encode(e, v.m_direction);
			avro::encode(e, v.m_mnemonic);
			avro::encode(e, v.m_description);
			avro::encode(e, v.m_uri);
			avro::encode(e, v.m_customData);
			avro::encode(e, v.m_scale);
			avro::encode(e, v.m_timeDatum);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Datatypes::ChannelData::IndexMetadataRecord& v) {		
			avro::decode(e, v.m_indexKind);
			avro::decode(e, v.m_uom);
			avro::decode(e, v.m_depthDatum);
			avro::decode(e, v.m_direction);
			avro::decode(e, v.m_mnemonic);
			avro::decode(e, v.m_description);
			avro::decode(e, v.m_uri);
			avro::decode(e, v.m_customData);
			avro::decode(e, v.m_scale);
			avro::decode(e, v.m_timeDatum);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Datatypes {			
				namespace ChannelData {				
					enum Roles {					
						producer=0,
						consumer=1
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Datatypes::ChannelData::Roles> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Datatypes::ChannelData::Roles& v) {		
			e.encodeEnum(v);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Datatypes::ChannelData::Roles& v) {		
			v = static_cast<Energistics::Etp::v12::Datatypes::ChannelData::Roles>(e.decodeEnum());
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Datatypes {			
				namespace ChannelData {				
					struct StreamingStartIndexitem_t {
					private:					
						size_t idx_=0;
						boost::any value_;
										
					public:					
						size_t idx() const { return idx_; }
						bool is_null() const { return idx_==0; }
						void set_null() { idx_=0; value_ = boost::any(); }
						int32_t& get_int()  {						
							if (idx_ != 1) {							
								throw avro::Exception("Invalid type for union.");
							}							
							return boost::any_cast< int32_t& >(value_);
						}						
						void set_int(const int32_t& v) {						
							idx_ = 1;
							value_ = v;
						}						
						int64_t& get_long()  {						
							if (idx_ != 2) {							
								throw avro::Exception("Invalid type for union.");
							}							
							return boost::any_cast< int64_t& >(value_);
						}						
						void set_long(const int64_t& v) {						
							idx_ = 2;
							value_ = v;
						}						
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Datatypes::ChannelData::StreamingStartIndexitem_t> {
	
		static void encode(Encoder& e, Energistics::Etp::v12::Datatypes::ChannelData::StreamingStartIndexitem_t v) {
		
			e.encodeUnionIndex(v.idx());
			switch (v.idx()) {			
				case 0:				
					e.encodeNull();
					break;								
				case 1:				
					avro::encode(e, v.get_int());
					break;								
				case 2:				
					avro::encode(e, v.get_long());
					break;								
			}			
		}		
		static void decode(Decoder& d, Energistics::Etp::v12::Datatypes::ChannelData::StreamingStartIndexitem_t& v) {
		
			size_t n = d.decodeUnionIndex();
			if (n >= 3) { throw avro::Exception("Union index too big"); }
			switch (n) {			
				case 0:				
					{					
						d.decodeNull();
						v.set_null();
					}					
					break;								
				case 1:				
					{					
						int32_t vv;
						avro::decode(d, vv);
						v.set_int(vv);
					}					
					break;								
				case 2:				
					{					
						int64_t vv;
						avro::decode(d, vv);
						v.set_long(vv);
					}					
					break;								
			}			
		}		
	};	
}

namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Datatypes {			
				namespace ChannelData {				
					struct StreamingStartIndex{					
						Energistics::Etp::v12::Datatypes::ChannelData::StreamingStartIndexitem_t m_item;
					};					
					typedef boost::shared_ptr<StreamingStartIndex> StreamingStartIndexPtr;
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Datatypes::ChannelData::StreamingStartIndex> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Datatypes::ChannelData::StreamingStartIndex& v) {		
			avro::encode(e, v.m_item);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Datatypes::ChannelData::StreamingStartIndex& v) {		
			avro::decode(e, v.m_item);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Datatypes {			
				namespace ChannelData {				
					struct ChannelStreamingInfo{					
						int64_t m_channelId;
						Energistics::Etp::v12::Datatypes::ChannelData::StreamingStartIndex m_startIndex;
						bool m_receiveChangeNotification=false;
					};					
					typedef boost::shared_ptr<ChannelStreamingInfo> ChannelStreamingInfoPtr;
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Datatypes::ChannelData::ChannelStreamingInfo> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Datatypes::ChannelData::ChannelStreamingInfo& v) {		
			avro::encode(e, v.m_channelId);
			avro::encode(e, v.m_startIndex);
			avro::encode(e, v.m_receiveChangeNotification);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Datatypes::ChannelData::ChannelStreamingInfo& v) {		
			avro::decode(e, v.m_channelId);
			avro::decode(e, v.m_startIndex);
			avro::decode(e, v.m_receiveChangeNotification);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Datatypes {			
				namespace Object {				
					struct GraphResource{					
						std::string m_uri;
						std::string m_contentType;
						std::string m_name;
						bool m_channelSubscribable=false;
						std::map<std::string, std::string> m_customData;
						std::string m_resourceType;
						int32_t m_sourceCount;
						int32_t m_targetCount;
						int32_t m_contentCount;
						std::string m_uuid;
						int64_t m_lastChanged;
						bool m_objectNotifiable=false;
					};					
					typedef boost::shared_ptr<GraphResource> GraphResourcePtr;
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Datatypes::Object::GraphResource> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Datatypes::Object::GraphResource& v) {		
			avro::encode(e, v.m_uri);
			avro::encode(e, v.m_contentType);
			avro::encode(e, v.m_name);
			avro::encode(e, v.m_channelSubscribable);
			avro::encode(e, v.m_customData);
			avro::encode(e, v.m_resourceType);
			avro::encode(e, v.m_sourceCount);
			avro::encode(e, v.m_targetCount);
			avro::encode(e, v.m_contentCount);
			avro::encode(e, v.m_uuid);
			avro::encode(e, v.m_lastChanged);
			avro::encode(e, v.m_objectNotifiable);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Datatypes::Object::GraphResource& v) {		
			avro::decode(e, v.m_uri);
			avro::decode(e, v.m_contentType);
			avro::decode(e, v.m_name);
			avro::decode(e, v.m_channelSubscribable);
			avro::decode(e, v.m_customData);
			avro::decode(e, v.m_resourceType);
			avro::decode(e, v.m_sourceCount);
			avro::decode(e, v.m_targetCount);
			avro::decode(e, v.m_contentCount);
			avro::decode(e, v.m_uuid);
			avro::decode(e, v.m_lastChanged);
			avro::decode(e, v.m_objectNotifiable);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Datatypes {			
				namespace Object {				
					struct IndexInterval{					
						Energistics::Etp::v12::Datatypes::IndexValue m_startIndex;
						Energistics::Etp::v12::Datatypes::IndexValue m_endIndex;
						std::string m_uom;
						std::string m_depthDatum;
					};					
					typedef boost::shared_ptr<IndexInterval> IndexIntervalPtr;
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Datatypes::Object::IndexInterval> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Datatypes::Object::IndexInterval& v) {		
			avro::encode(e, v.m_startIndex);
			avro::encode(e, v.m_endIndex);
			avro::encode(e, v.m_uom);
			avro::encode(e, v.m_depthDatum);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Datatypes::Object::IndexInterval& v) {		
			avro::decode(e, v.m_startIndex);
			avro::decode(e, v.m_endIndex);
			avro::decode(e, v.m_uom);
			avro::decode(e, v.m_depthDatum);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Datatypes {			
				namespace Object {				
					struct NotificationRequestRecord{					
						std::string m_uri;
						std::string m_uuid;
						bool m_includeObjectData=false;
						int64_t m_startTime;
						std::vector<std::string> m_objectTypes;
					};					
					typedef boost::shared_ptr<NotificationRequestRecord> NotificationRequestRecordPtr;
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Datatypes::Object::NotificationRequestRecord> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Datatypes::Object::NotificationRequestRecord& v) {		
			avro::encode(e, v.m_uri);
			avro::encode(e, v.m_uuid);
			avro::encode(e, v.m_includeObjectData);
			avro::encode(e, v.m_startTime);
			avro::encode(e, v.m_objectTypes);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Datatypes::Object::NotificationRequestRecord& v) {		
			avro::decode(e, v.m_uri);
			avro::decode(e, v.m_uuid);
			avro::decode(e, v.m_includeObjectData);
			avro::decode(e, v.m_startTime);
			avro::decode(e, v.m_objectTypes);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Datatypes {			
				namespace Object {				
					enum ObjectChangeKinds {					
						insert=0,
						update=1
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Datatypes::Object::ObjectChangeKinds> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Datatypes::Object::ObjectChangeKinds& v) {		
			e.encodeEnum(v);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Datatypes::Object::ObjectChangeKinds& v) {		
			v = static_cast<Energistics::Etp::v12::Datatypes::Object::ObjectChangeKinds>(e.decodeEnum());
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Datatypes {			
				namespace Object {				
					struct ObjectIndex{					
						Energistics::Etp::v12::Datatypes::IndexValue m_indexValue;
						std::string m_uom;
						std::string m_depthDatum;
					};					
					typedef boost::shared_ptr<ObjectIndex> ObjectIndexPtr;
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Datatypes::Object::ObjectIndex> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Datatypes::Object::ObjectIndex& v) {		
			avro::encode(e, v.m_indexValue);
			avro::encode(e, v.m_uom);
			avro::encode(e, v.m_depthDatum);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Datatypes::Object::ObjectIndex& v) {		
			avro::decode(e, v.m_indexValue);
			avro::decode(e, v.m_uom);
			avro::decode(e, v.m_depthDatum);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Datatypes {			
				namespace Object {				
					struct ResourcechildCount_t {
					private:					
						size_t idx_=0;
						boost::any value_;
										
					public:					
						size_t idx() const { return idx_; }
						bool is_null() const { return idx_==0; }
						void set_null() { idx_=0; value_ = boost::any(); }
						int32_t& get_int()  {						
							if (idx_ != 1) {							
								throw avro::Exception("Invalid type for union.");
							}							
							return boost::any_cast< int32_t& >(value_);
						}						
						void set_int(const int32_t& v) {						
							idx_ = 1;
							value_ = v;
						}						
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Datatypes::Object::ResourcechildCount_t> {
	
		static void encode(Encoder& e, Energistics::Etp::v12::Datatypes::Object::ResourcechildCount_t v) {
		
			e.encodeUnionIndex(v.idx());
			switch (v.idx()) {			
				case 0:				
					e.encodeNull();
					break;								
				case 1:				
					avro::encode(e, v.get_int());
					break;								
			}			
		}		
		static void decode(Decoder& d, Energistics::Etp::v12::Datatypes::Object::ResourcechildCount_t& v) {
		
			size_t n = d.decodeUnionIndex();
			if (n >= 2) { throw avro::Exception("Union index too big"); }
			switch (n) {			
				case 0:				
					{					
						d.decodeNull();
						v.set_null();
					}					
					break;								
				case 1:				
					{					
						int32_t vv;
						avro::decode(d, vv);
						v.set_int(vv);
					}					
					break;								
			}			
		}		
	};	
}

namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Datatypes {			
				namespace Object {				
					struct ResourcelastChanged_t {
					private:					
						size_t idx_=0;
						boost::any value_;
										
					public:					
						size_t idx() const { return idx_; }
						bool is_null() const { return idx_==0; }
						void set_null() { idx_=0; value_ = boost::any(); }
						int64_t& get_long()  {						
							if (idx_ != 1) {							
								throw avro::Exception("Invalid type for union.");
							}							
							return boost::any_cast< int64_t& >(value_);
						}						
						void set_long(const int64_t& v) {						
							idx_ = 1;
							value_ = v;
						}						
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Datatypes::Object::ResourcelastChanged_t> {
	
		static void encode(Encoder& e, Energistics::Etp::v12::Datatypes::Object::ResourcelastChanged_t v) {
		
			e.encodeUnionIndex(v.idx());
			switch (v.idx()) {			
				case 0:				
					e.encodeNull();
					break;								
				case 1:				
					avro::encode(e, v.get_long());
					break;								
			}			
		}		
		static void decode(Decoder& d, Energistics::Etp::v12::Datatypes::Object::ResourcelastChanged_t& v) {
		
			size_t n = d.decodeUnionIndex();
			if (n >= 2) { throw avro::Exception("Union index too big"); }
			switch (n) {			
				case 0:				
					{					
						d.decodeNull();
						v.set_null();
					}					
					break;								
				case 1:				
					{					
						int64_t vv;
						avro::decode(d, vv);
						v.set_long(vv);
					}					
					break;								
			}			
		}		
	};	
}

namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Datatypes {			
				namespace Object {				
					struct Resource{					
						std::string m_uri;
						std::string m_contentType;
						std::string m_name;
						bool m_channelSubscribable=false;
						std::map<std::string, std::string> m_customData;
						std::string m_resourceType;
						Energistics::Etp::v12::Datatypes::Object::ResourcechildCount_t m_childCount;
						std::string m_uuid;
						Energistics::Etp::v12::Datatypes::Object::ResourcelastChanged_t m_lastChanged;
						bool m_objectNotifiable=false;
					};					
					typedef boost::shared_ptr<Resource> ResourcePtr;
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Datatypes::Object::Resource> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Datatypes::Object::Resource& v) {		
			avro::encode(e, v.m_uri);
			avro::encode(e, v.m_contentType);
			avro::encode(e, v.m_name);
			avro::encode(e, v.m_channelSubscribable);
			avro::encode(e, v.m_customData);
			avro::encode(e, v.m_resourceType);
			avro::encode(e, v.m_childCount);
			avro::encode(e, v.m_uuid);
			avro::encode(e, v.m_lastChanged);
			avro::encode(e, v.m_objectNotifiable);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Datatypes::Object::Resource& v) {		
			avro::decode(e, v.m_uri);
			avro::decode(e, v.m_contentType);
			avro::decode(e, v.m_name);
			avro::decode(e, v.m_channelSubscribable);
			avro::decode(e, v.m_customData);
			avro::decode(e, v.m_resourceType);
			avro::decode(e, v.m_childCount);
			avro::decode(e, v.m_uuid);
			avro::decode(e, v.m_lastChanged);
			avro::decode(e, v.m_objectNotifiable);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Datatypes {			
				namespace Object {				
					struct DataObject{					
						Energistics::Etp::v12::Datatypes::Object::Resource m_resource;
						std::string m_data;
					};					
					typedef boost::shared_ptr<DataObject> DataObjectPtr;
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Datatypes::Object::DataObject> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Datatypes::Object::DataObject& v) {		
			avro::encode(e, v.m_resource);
			avro::encode(e, v.m_data);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Datatypes::Object::DataObject& v) {		
			avro::decode(e, v.m_resource);
			avro::decode(e, v.m_data);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Datatypes {			
				namespace ChannelData {				
					struct ChannelMetadataRecordstartIndex_t {
					private:					
						size_t idx_=0;
						boost::any value_;
										
					public:					
						size_t idx() const { return idx_; }
						bool is_null() const { return idx_==0; }
						void set_null() { idx_=0; value_ = boost::any(); }
						int64_t& get_long()  {						
							if (idx_ != 1) {							
								throw avro::Exception("Invalid type for union.");
							}							
							return boost::any_cast< int64_t& >(value_);
						}						
						void set_long(const int64_t& v) {						
							idx_ = 1;
							value_ = v;
						}						
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Datatypes::ChannelData::ChannelMetadataRecordstartIndex_t> {
	
		static void encode(Encoder& e, Energistics::Etp::v12::Datatypes::ChannelData::ChannelMetadataRecordstartIndex_t v) {
		
			e.encodeUnionIndex(v.idx());
			switch (v.idx()) {			
				case 0:				
					e.encodeNull();
					break;								
				case 1:				
					avro::encode(e, v.get_long());
					break;								
			}			
		}		
		static void decode(Decoder& d, Energistics::Etp::v12::Datatypes::ChannelData::ChannelMetadataRecordstartIndex_t& v) {
		
			size_t n = d.decodeUnionIndex();
			if (n >= 2) { throw avro::Exception("Union index too big"); }
			switch (n) {			
				case 0:				
					{					
						d.decodeNull();
						v.set_null();
					}					
					break;								
				case 1:				
					{					
						int64_t vv;
						avro::decode(d, vv);
						v.set_long(vv);
					}					
					break;								
			}			
		}		
	};	
}

namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Datatypes {			
				namespace ChannelData {				
					struct ChannelMetadataRecordendIndex_t {
					private:					
						size_t idx_=0;
						boost::any value_;
										
					public:					
						size_t idx() const { return idx_; }
						bool is_null() const { return idx_==0; }
						void set_null() { idx_=0; value_ = boost::any(); }
						int64_t& get_long()  {						
							if (idx_ != 1) {							
								throw avro::Exception("Invalid type for union.");
							}							
							return boost::any_cast< int64_t& >(value_);
						}						
						void set_long(const int64_t& v) {						
							idx_ = 1;
							value_ = v;
						}						
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Datatypes::ChannelData::ChannelMetadataRecordendIndex_t> {
	
		static void encode(Encoder& e, Energistics::Etp::v12::Datatypes::ChannelData::ChannelMetadataRecordendIndex_t v) {
		
			e.encodeUnionIndex(v.idx());
			switch (v.idx()) {			
				case 0:				
					e.encodeNull();
					break;								
				case 1:				
					avro::encode(e, v.get_long());
					break;								
			}			
		}		
		static void decode(Decoder& d, Energistics::Etp::v12::Datatypes::ChannelData::ChannelMetadataRecordendIndex_t& v) {
		
			size_t n = d.decodeUnionIndex();
			if (n >= 2) { throw avro::Exception("Union index too big"); }
			switch (n) {			
				case 0:				
					{					
						d.decodeNull();
						v.set_null();
					}					
					break;								
				case 1:				
					{					
						int64_t vv;
						avro::decode(d, vv);
						v.set_long(vv);
					}					
					break;								
			}			
		}		
	};	
}

namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Datatypes {			
				namespace ChannelData {				
					struct ChannelMetadataRecorddomainObject_t {
					private:					
						size_t idx_=0;
						boost::any value_;
										
					public:					
						size_t idx() const { return idx_; }
						bool is_null() const { return idx_==0; }
						void set_null() { idx_=0; value_ = boost::any(); }
						Energistics::Etp::v12::Datatypes::Object::DataObject& get_DataObject()  {						
							if (idx_ != 1) {							
								throw avro::Exception("Invalid type for union.");
							}							
							return boost::any_cast< Energistics::Etp::v12::Datatypes::Object::DataObject& >(value_);
						}						
						void set_DataObject(const Energistics::Etp::v12::Datatypes::Object::DataObject& v) {						
							idx_ = 1;
							value_ = v;
						}						
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Datatypes::ChannelData::ChannelMetadataRecorddomainObject_t> {
	
		static void encode(Encoder& e, Energistics::Etp::v12::Datatypes::ChannelData::ChannelMetadataRecorddomainObject_t v) {
		
			e.encodeUnionIndex(v.idx());
			switch (v.idx()) {			
				case 0:				
					e.encodeNull();
					break;								
				case 1:				
					avro::encode(e, v.get_DataObject());
					break;								
			}			
		}		
		static void decode(Decoder& d, Energistics::Etp::v12::Datatypes::ChannelData::ChannelMetadataRecorddomainObject_t& v) {
		
			size_t n = d.decodeUnionIndex();
			if (n >= 2) { throw avro::Exception("Union index too big"); }
			switch (n) {			
				case 0:				
					{					
						d.decodeNull();
						v.set_null();
					}					
					break;								
				case 1:				
					{					
						Energistics::Etp::v12::Datatypes::Object::DataObject vv;
						avro::decode(d, vv);
						v.set_DataObject(vv);
					}					
					break;								
			}			
		}		
	};	
}

namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Datatypes {			
				namespace ChannelData {				
					struct ChannelMetadataRecord{					
						std::string m_channelUri;
						int64_t m_channelId;
						std::vector<Energistics::Etp::v12::Datatypes::ChannelData::IndexMetadataRecord> m_indexes;
						std::string m_channelName;
						std::string m_dataType;
						std::string m_uom;
						Energistics::Etp::v12::Datatypes::ChannelData::ChannelMetadataRecordstartIndex_t m_startIndex;
						Energistics::Etp::v12::Datatypes::ChannelData::ChannelMetadataRecordendIndex_t m_endIndex;
						std::string m_description;
						Energistics::Etp::v12::Datatypes::ChannelData::ChannelStatuses m_status;
						std::string m_contentType;
						std::string m_source;
						std::string m_measureClass;
						std::string m_uuid;
						std::map<std::string, Energistics::Etp::v12::Datatypes::DataValue> m_customData;
						Energistics::Etp::v12::Datatypes::ChannelData::ChannelMetadataRecorddomainObject_t m_domainObject;
						std::vector<Energistics::Etp::v12::Datatypes::AttributeMetadataRecord> m_attributeMetadata;
					};					
					typedef boost::shared_ptr<ChannelMetadataRecord> ChannelMetadataRecordPtr;
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Datatypes::ChannelData::ChannelMetadataRecord> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Datatypes::ChannelData::ChannelMetadataRecord& v) {		
			avro::encode(e, v.m_channelUri);
			avro::encode(e, v.m_channelId);
			avro::encode(e, v.m_indexes);
			avro::encode(e, v.m_channelName);
			avro::encode(e, v.m_dataType);
			avro::encode(e, v.m_uom);
			avro::encode(e, v.m_startIndex);
			avro::encode(e, v.m_endIndex);
			avro::encode(e, v.m_description);
			avro::encode(e, v.m_status);
			avro::encode(e, v.m_contentType);
			avro::encode(e, v.m_source);
			avro::encode(e, v.m_measureClass);
			avro::encode(e, v.m_uuid);
			avro::encode(e, v.m_customData);
			avro::encode(e, v.m_domainObject);
			avro::encode(e, v.m_attributeMetadata);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Datatypes::ChannelData::ChannelMetadataRecord& v) {		
			avro::decode(e, v.m_channelUri);
			avro::decode(e, v.m_channelId);
			avro::decode(e, v.m_indexes);
			avro::decode(e, v.m_channelName);
			avro::decode(e, v.m_dataType);
			avro::decode(e, v.m_uom);
			avro::decode(e, v.m_startIndex);
			avro::decode(e, v.m_endIndex);
			avro::decode(e, v.m_description);
			avro::decode(e, v.m_status);
			avro::decode(e, v.m_contentType);
			avro::decode(e, v.m_source);
			avro::decode(e, v.m_measureClass);
			avro::decode(e, v.m_uuid);
			avro::decode(e, v.m_customData);
			avro::decode(e, v.m_domainObject);
			avro::decode(e, v.m_attributeMetadata);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Datatypes {			
				namespace Object {				
					struct ObjectChange{					
						Energistics::Etp::v12::Datatypes::Object::ObjectChangeKinds m_changeKind;
						int64_t m_changeTime;
						Energistics::Etp::v12::Datatypes::Object::DataObject m_dataObject;
					};					
					typedef boost::shared_ptr<ObjectChange> ObjectChangePtr;
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Datatypes::Object::ObjectChange> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Datatypes::Object::ObjectChange& v) {		
			avro::encode(e, v.m_changeKind);
			avro::encode(e, v.m_changeTime);
			avro::encode(e, v.m_dataObject);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Datatypes::Object::ObjectChange& v) {		
			avro::decode(e, v.m_changeKind);
			avro::decode(e, v.m_changeTime);
			avro::decode(e, v.m_dataObject);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace ChannelDataFrame {				
					struct ChannelDataFrameSet{					
						std::vector<int64_t> m_channels;
						std::vector<Energistics::Etp::v12::Datatypes::ChannelData::DataFrame> m_data;
						static const int messageTypeId=4;
						static const int protocolId=Energistics::Etp::v12::Datatypes::ChannelDataFrame;
					};					
					typedef boost::shared_ptr<ChannelDataFrameSet> ChannelDataFrameSetPtr;
					const int CHANNELDATAFRAMESET=4;
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::ChannelDataFrame::ChannelDataFrameSet> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::ChannelDataFrame::ChannelDataFrameSet& v) {		
			avro::encode(e, v.m_channels);
			avro::encode(e, v.m_data);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::ChannelDataFrame::ChannelDataFrameSet& v) {		
			avro::decode(e, v.m_channels);
			avro::decode(e, v.m_data);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace ChannelDataFrame {				
					struct ChannelMetadata{					
						std::vector<Energistics::Etp::v12::Datatypes::ChannelData::ChannelMetadataRecord> m_channels;
						static const int messageTypeId=3;
						static const int protocolId=Energistics::Etp::v12::Datatypes::ChannelDataFrame;
					};					
					typedef boost::shared_ptr<ChannelMetadata> ChannelMetadataPtr;
					const int CHANNELMETADATA=3;
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::ChannelDataFrame::ChannelMetadata> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::ChannelDataFrame::ChannelMetadata& v) {		
			avro::encode(e, v.m_channels);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::ChannelDataFrame::ChannelMetadata& v) {		
			avro::decode(e, v.m_channels);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace ChannelDataFrame {				
					struct RequestChannelData{					
						std::string m_uri;
						Energistics::Etp::v12::Datatypes::Object::IndexInterval m_requestedInterval;
						static const int messageTypeId=1;
						static const int protocolId=Energistics::Etp::v12::Datatypes::ChannelDataFrame;
					};					
					typedef boost::shared_ptr<RequestChannelData> RequestChannelDataPtr;
					const int REQUESTCHANNELDATA=1;
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::ChannelDataFrame::RequestChannelData> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::ChannelDataFrame::RequestChannelData& v) {		
			avro::encode(e, v.m_uri);
			avro::encode(e, v.m_requestedInterval);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::ChannelDataFrame::RequestChannelData& v) {		
			avro::decode(e, v.m_uri);
			avro::decode(e, v.m_requestedInterval);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace ChannelStreaming {				
					struct ChannelData{					
						std::vector<Energistics::Etp::v12::Datatypes::ChannelData::DataItem> m_data;
						static const int messageTypeId=3;
						static const int protocolId=Energistics::Etp::v12::Datatypes::ChannelStreaming;
					};					
					typedef boost::shared_ptr<ChannelData> ChannelDataPtr;
					const int CHANNELDATA=3;
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::ChannelStreaming::ChannelData> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::ChannelStreaming::ChannelData& v) {		
			avro::encode(e, v.m_data);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::ChannelStreaming::ChannelData& v) {		
			avro::decode(e, v.m_data);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace ChannelStreaming {				
					struct ChannelDataChange{					
						int64_t m_channelId;
						int64_t m_startIndex;
						int64_t m_endIndex;
						std::vector<Energistics::Etp::v12::Datatypes::ChannelData::DataItem> m_data;
						static const int messageTypeId=6;
						static const int protocolId=Energistics::Etp::v12::Datatypes::ChannelStreaming;
					};					
					typedef boost::shared_ptr<ChannelDataChange> ChannelDataChangePtr;
					const int CHANNELDATACHANGE=6;
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::ChannelStreaming::ChannelDataChange> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::ChannelStreaming::ChannelDataChange& v) {		
			avro::encode(e, v.m_channelId);
			avro::encode(e, v.m_startIndex);
			avro::encode(e, v.m_endIndex);
			avro::encode(e, v.m_data);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::ChannelStreaming::ChannelDataChange& v) {		
			avro::decode(e, v.m_channelId);
			avro::decode(e, v.m_startIndex);
			avro::decode(e, v.m_endIndex);
			avro::decode(e, v.m_data);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace ChannelStreaming {				
					struct ChannelDescribe{					
						std::vector<std::string> m_uris;
						static const int messageTypeId=1;
						static const int protocolId=Energistics::Etp::v12::Datatypes::ChannelStreaming;
					};					
					typedef boost::shared_ptr<ChannelDescribe> ChannelDescribePtr;
					const int CHANNELDESCRIBE=1;
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::ChannelStreaming::ChannelDescribe> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::ChannelStreaming::ChannelDescribe& v) {		
			avro::encode(e, v.m_uris);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::ChannelStreaming::ChannelDescribe& v) {		
			avro::decode(e, v.m_uris);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace ChannelStreaming {				
					struct ChannelMetadata{					
						std::vector<Energistics::Etp::v12::Datatypes::ChannelData::ChannelMetadataRecord> m_channels;
						static const int messageTypeId=2;
						static const int protocolId=Energistics::Etp::v12::Datatypes::ChannelStreaming;
					};					
					typedef boost::shared_ptr<ChannelMetadata> ChannelMetadataPtr;
					const int CHANNELMETADATA=2;
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::ChannelStreaming::ChannelMetadata> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::ChannelStreaming::ChannelMetadata& v) {		
			avro::encode(e, v.m_channels);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::ChannelStreaming::ChannelMetadata& v) {		
			avro::decode(e, v.m_channels);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace ChannelStreaming {				
					struct ChannelRangeRequest{					
						std::vector<Energistics::Etp::v12::Datatypes::ChannelData::ChannelRangeInfo> m_channelRanges;
						static const int messageTypeId=9;
						static const int protocolId=Energistics::Etp::v12::Datatypes::ChannelStreaming;
					};					
					typedef boost::shared_ptr<ChannelRangeRequest> ChannelRangeRequestPtr;
					const int CHANNELRANGEREQUEST=9;
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::ChannelStreaming::ChannelRangeRequest> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::ChannelStreaming::ChannelRangeRequest& v) {		
			avro::encode(e, v.m_channelRanges);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::ChannelStreaming::ChannelRangeRequest& v) {		
			avro::decode(e, v.m_channelRanges);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace ChannelStreaming {				
					struct ChannelRemove{					
						int64_t m_channelId;
						std::string m_removeReason;
						static const int messageTypeId=8;
						static const int protocolId=Energistics::Etp::v12::Datatypes::ChannelStreaming;
					};					
					typedef boost::shared_ptr<ChannelRemove> ChannelRemovePtr;
					const int CHANNELREMOVE=8;
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::ChannelStreaming::ChannelRemove> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::ChannelStreaming::ChannelRemove& v) {		
			avro::encode(e, v.m_channelId);
			avro::encode(e, v.m_removeReason);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::ChannelStreaming::ChannelRemove& v) {		
			avro::decode(e, v.m_channelId);
			avro::decode(e, v.m_removeReason);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace ChannelStreaming {				
					struct ChannelStatusChange{					
						int64_t m_channelId;
						Energistics::Etp::v12::Datatypes::ChannelData::ChannelStatuses m_status;
						static const int messageTypeId=10;
						static const int protocolId=Energistics::Etp::v12::Datatypes::ChannelStreaming;
					};					
					typedef boost::shared_ptr<ChannelStatusChange> ChannelStatusChangePtr;
					const int CHANNELSTATUSCHANGE=10;
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::ChannelStreaming::ChannelStatusChange> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::ChannelStreaming::ChannelStatusChange& v) {		
			avro::encode(e, v.m_channelId);
			avro::encode(e, v.m_status);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::ChannelStreaming::ChannelStatusChange& v) {		
			avro::decode(e, v.m_channelId);
			avro::decode(e, v.m_status);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace ChannelStreaming {				
					struct ChannelStreamingStart{					
						std::vector<Energistics::Etp::v12::Datatypes::ChannelData::ChannelStreamingInfo> m_channels;
						static const int messageTypeId=4;
						static const int protocolId=Energistics::Etp::v12::Datatypes::ChannelStreaming;
					};					
					typedef boost::shared_ptr<ChannelStreamingStart> ChannelStreamingStartPtr;
					const int CHANNELSTREAMINGSTART=4;
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::ChannelStreaming::ChannelStreamingStart> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::ChannelStreaming::ChannelStreamingStart& v) {		
			avro::encode(e, v.m_channels);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::ChannelStreaming::ChannelStreamingStart& v) {		
			avro::decode(e, v.m_channels);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace ChannelStreaming {				
					struct ChannelStreamingStop{					
						std::vector<int64_t> m_channels;
						static const int messageTypeId=5;
						static const int protocolId=Energistics::Etp::v12::Datatypes::ChannelStreaming;
					};					
					typedef boost::shared_ptr<ChannelStreamingStop> ChannelStreamingStopPtr;
					const int CHANNELSTREAMINGSTOP=5;
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::ChannelStreaming::ChannelStreamingStop> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::ChannelStreaming::ChannelStreamingStop& v) {		
			avro::encode(e, v.m_channels);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::ChannelStreaming::ChannelStreamingStop& v) {		
			avro::decode(e, v.m_channels);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace ChannelStreaming {				
					struct Start{					
						int32_t m_minMessageInterval;
						int32_t m_maxDataItems;
						static const int messageTypeId=0;
						static const int protocolId=Energistics::Etp::v12::Datatypes::ChannelStreaming;
					};					
					typedef boost::shared_ptr<Start> StartPtr;
					const int START=0;
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::ChannelStreaming::Start> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::ChannelStreaming::Start& v) {		
			avro::encode(e, v.m_minMessageInterval);
			avro::encode(e, v.m_maxDataItems);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::ChannelStreaming::Start& v) {		
			avro::decode(e, v.m_minMessageInterval);
			avro::decode(e, v.m_maxDataItems);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace Core {				
					struct Acknowledge{					
						static const int messageTypeId=1001;
						static const int protocolId=Energistics::Etp::v12::Datatypes::Core;
					};					
					typedef boost::shared_ptr<Acknowledge> AcknowledgePtr;
					const int ACKNOWLEDGE=1001;
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::Core::Acknowledge> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::Core::Acknowledge& v) {		
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::Core::Acknowledge& v) {		
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace Core {				
					struct CloseSession{					
						std::string m_reason;
						static const int messageTypeId=5;
						static const int protocolId=Energistics::Etp::v12::Datatypes::Core;
					};					
					typedef boost::shared_ptr<CloseSession> CloseSessionPtr;
					const int CLOSESESSION=5;
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::Core::CloseSession> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::Core::CloseSession& v) {		
			avro::encode(e, v.m_reason);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::Core::CloseSession& v) {		
			avro::decode(e, v.m_reason);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace Core {				
					struct OpenSession{					
						std::string m_applicationName;
						std::string m_applicationVersion;
						std::string m_sessionId;
						std::vector<Energistics::Etp::v12::Datatypes::SupportedProtocol> m_supportedProtocols;
						std::vector<std::string> m_supportedObjects;
						std::string m_supportedCompression;
						static const int messageTypeId=2;
						static const int protocolId=Energistics::Etp::v12::Datatypes::Core;
					};					
					typedef boost::shared_ptr<OpenSession> OpenSessionPtr;
					const int OPENSESSION=2;
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::Core::OpenSession> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::Core::OpenSession& v) {		
			avro::encode(e, v.m_applicationName);
			avro::encode(e, v.m_applicationVersion);
			avro::encode(e, v.m_sessionId);
			avro::encode(e, v.m_supportedProtocols);
			avro::encode(e, v.m_supportedObjects);
			avro::encode(e, v.m_supportedCompression);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::Core::OpenSession& v) {		
			avro::decode(e, v.m_applicationName);
			avro::decode(e, v.m_applicationVersion);
			avro::decode(e, v.m_sessionId);
			avro::decode(e, v.m_supportedProtocols);
			avro::decode(e, v.m_supportedObjects);
			avro::decode(e, v.m_supportedCompression);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace Core {				
					struct ProtocolException{					
						int32_t m_errorCode;
						std::string m_errorMessage;
						static const int messageTypeId=1000;
						static const int protocolId=Energistics::Etp::v12::Datatypes::Core;
					};					
					typedef boost::shared_ptr<ProtocolException> ProtocolExceptionPtr;
					const int PROTOCOLEXCEPTION=1000;
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::Core::ProtocolException> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::Core::ProtocolException& v) {		
			avro::encode(e, v.m_errorCode);
			avro::encode(e, v.m_errorMessage);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::Core::ProtocolException& v) {		
			avro::decode(e, v.m_errorCode);
			avro::decode(e, v.m_errorMessage);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace Core {				
					struct RenewSecurityToken{					
						std::string m_token;
						static const int messageTypeId=6;
						static const int protocolId=Energistics::Etp::v12::Datatypes::Core;
					};					
					typedef boost::shared_ptr<RenewSecurityToken> RenewSecurityTokenPtr;
					const int RENEWSECURITYTOKEN=6;
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::Core::RenewSecurityToken> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::Core::RenewSecurityToken& v) {		
			avro::encode(e, v.m_token);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::Core::RenewSecurityToken& v) {		
			avro::decode(e, v.m_token);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace Core {				
					struct RequestSession{					
						std::string m_applicationName;
						std::string m_applicationVersion;
						std::vector<Energistics::Etp::v12::Datatypes::SupportedProtocol> m_requestedProtocols;
						std::vector<std::string> m_supportedObjects;
						std::string m_supportedCompression;
						static const int messageTypeId=1;
						static const int protocolId=Energistics::Etp::v12::Datatypes::Core;
					};					
					typedef boost::shared_ptr<RequestSession> RequestSessionPtr;
					const int REQUESTSESSION=1;
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::Core::RequestSession> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::Core::RequestSession& v) {		
			avro::encode(e, v.m_applicationName);
			avro::encode(e, v.m_applicationVersion);
			avro::encode(e, v.m_requestedProtocols);
			avro::encode(e, v.m_supportedObjects);
			avro::encode(e, v.m_supportedCompression);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::Core::RequestSession& v) {		
			avro::decode(e, v.m_applicationName);
			avro::decode(e, v.m_applicationVersion);
			avro::decode(e, v.m_requestedProtocols);
			avro::decode(e, v.m_supportedObjects);
			avro::decode(e, v.m_supportedCompression);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace DataArray {				
					struct DataArray{					
						std::vector<int64_t> m_dimensions;
						Energistics::Etp::v12::Datatypes::AnyArray m_data;
						static const int messageTypeId=1;
						static const int protocolId=Energistics::Etp::v12::Datatypes::DataArray;
					};					
					typedef boost::shared_ptr<DataArray> DataArrayPtr;
					const int DATAARRAY=1;
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::DataArray::DataArray> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::DataArray::DataArray& v) {		
			avro::encode(e, v.m_dimensions);
			avro::encode(e, v.m_data);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::DataArray::DataArray& v) {		
			avro::decode(e, v.m_dimensions);
			avro::decode(e, v.m_data);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace DataArray {				
					struct DataArrayMetadata{					
						std::vector<int64_t> m_dimensions;
						Energistics::Etp::v12::Datatypes::AnyArrayTypes m_arrayType;
						static const int messageTypeId=7;
						static const int protocolId=Energistics::Etp::v12::Datatypes::DataArray;
					};					
					typedef boost::shared_ptr<DataArrayMetadata> DataArrayMetadataPtr;
					const int DATAARRAYMETADATA=7;
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::DataArray::DataArrayMetadata> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::DataArray::DataArrayMetadata& v) {		
			avro::encode(e, v.m_dimensions);
			avro::encode(e, v.m_arrayType);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::DataArray::DataArrayMetadata& v) {		
			avro::decode(e, v.m_dimensions);
			avro::decode(e, v.m_arrayType);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace DataArray {				
					struct DescribeDataArray{					
						std::string m_uri;
						std::string m_pathInResource;
						static const int messageTypeId=6;
						static const int protocolId=Energistics::Etp::v12::Datatypes::DataArray;
					};					
					typedef boost::shared_ptr<DescribeDataArray> DescribeDataArrayPtr;
					const int DESCRIBEDATAARRAY=6;
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::DataArray::DescribeDataArray> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::DataArray::DescribeDataArray& v) {		
			avro::encode(e, v.m_uri);
			avro::encode(e, v.m_pathInResource);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::DataArray::DescribeDataArray& v) {		
			avro::decode(e, v.m_uri);
			avro::decode(e, v.m_pathInResource);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace DataArray {				
					struct GetDataArray{					
						std::string m_uri;
						std::string m_pathInResource;
						static const int messageTypeId=2;
						static const int protocolId=Energistics::Etp::v12::Datatypes::DataArray;
					};					
					typedef boost::shared_ptr<GetDataArray> GetDataArrayPtr;
					const int GETDATAARRAY=2;
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::DataArray::GetDataArray> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::DataArray::GetDataArray& v) {		
			avro::encode(e, v.m_uri);
			avro::encode(e, v.m_pathInResource);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::DataArray::GetDataArray& v) {		
			avro::decode(e, v.m_uri);
			avro::decode(e, v.m_pathInResource);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace DataArray {				
					struct GetDataArraySlice{					
						std::string m_uri;
						std::string m_pathInResource;
						std::vector<int64_t> m_start;
						std::vector<int64_t> m_count;
						static const int messageTypeId=3;
						static const int protocolId=Energistics::Etp::v12::Datatypes::DataArray;
					};					
					typedef boost::shared_ptr<GetDataArraySlice> GetDataArraySlicePtr;
					const int GETDATAARRAYSLICE=3;
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::DataArray::GetDataArraySlice> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::DataArray::GetDataArraySlice& v) {		
			avro::encode(e, v.m_uri);
			avro::encode(e, v.m_pathInResource);
			avro::encode(e, v.m_start);
			avro::encode(e, v.m_count);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::DataArray::GetDataArraySlice& v) {		
			avro::decode(e, v.m_uri);
			avro::decode(e, v.m_pathInResource);
			avro::decode(e, v.m_start);
			avro::decode(e, v.m_count);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace DataArray {				
					struct PutDataArray{					
						std::string m_uri;
						std::string m_pathInResource;
						Energistics::Etp::v12::Datatypes::AnyArray m_data;
						std::vector<int64_t> m_dimensions;
						static const int messageTypeId=4;
						static const int protocolId=Energistics::Etp::v12::Datatypes::DataArray;
					};					
					typedef boost::shared_ptr<PutDataArray> PutDataArrayPtr;
					const int PUTDATAARRAY=4;
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::DataArray::PutDataArray> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::DataArray::PutDataArray& v) {		
			avro::encode(e, v.m_uri);
			avro::encode(e, v.m_pathInResource);
			avro::encode(e, v.m_data);
			avro::encode(e, v.m_dimensions);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::DataArray::PutDataArray& v) {		
			avro::decode(e, v.m_uri);
			avro::decode(e, v.m_pathInResource);
			avro::decode(e, v.m_data);
			avro::decode(e, v.m_dimensions);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace DataArray {				
					struct PutDataArraySlice{					
						std::string m_uri;
						std::string m_pathInResource;
						Energistics::Etp::v12::Datatypes::AnyArray m_data;
						std::vector<int64_t> m_dimensions;
						std::vector<int64_t> m_start;
						std::vector<int64_t> m_count;
						static const int messageTypeId=5;
						static const int protocolId=Energistics::Etp::v12::Datatypes::DataArray;
					};					
					typedef boost::shared_ptr<PutDataArraySlice> PutDataArraySlicePtr;
					const int PUTDATAARRAYSLICE=5;
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::DataArray::PutDataArraySlice> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::DataArray::PutDataArraySlice& v) {		
			avro::encode(e, v.m_uri);
			avro::encode(e, v.m_pathInResource);
			avro::encode(e, v.m_data);
			avro::encode(e, v.m_dimensions);
			avro::encode(e, v.m_start);
			avro::encode(e, v.m_count);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::DataArray::PutDataArraySlice& v) {		
			avro::decode(e, v.m_uri);
			avro::decode(e, v.m_pathInResource);
			avro::decode(e, v.m_data);
			avro::decode(e, v.m_dimensions);
			avro::decode(e, v.m_start);
			avro::decode(e, v.m_count);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace DirectedDiscovery {				
					struct GetContent{					
						std::string m_uri;
						static const int messageTypeId=1;
						static const int protocolId=Energistics::Etp::v12::Datatypes::DirectedDiscovery;
					};					
					typedef boost::shared_ptr<GetContent> GetContentPtr;
					const int GETCONTENT=1;
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::DirectedDiscovery::GetContent> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::DirectedDiscovery::GetContent& v) {		
			avro::encode(e, v.m_uri);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::DirectedDiscovery::GetContent& v) {		
			avro::decode(e, v.m_uri);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace DirectedDiscovery {				
					struct GetResourcesResponse{					
						Energistics::Etp::v12::Datatypes::Object::GraphResource m_resource;
						static const int messageTypeId=2;
						static const int protocolId=Energistics::Etp::v12::Datatypes::DirectedDiscovery;
					};					
					typedef boost::shared_ptr<GetResourcesResponse> GetResourcesResponsePtr;
					const int GETRESOURCESRESPONSE=2;
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::DirectedDiscovery::GetResourcesResponse> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::DirectedDiscovery::GetResourcesResponse& v) {		
			avro::encode(e, v.m_resource);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::DirectedDiscovery::GetResourcesResponse& v) {		
			avro::decode(e, v.m_resource);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace DirectedDiscovery {				
					struct GetSources{					
						std::string m_uri;
						static const int messageTypeId=3;
						static const int protocolId=Energistics::Etp::v12::Datatypes::DirectedDiscovery;
					};					
					typedef boost::shared_ptr<GetSources> GetSourcesPtr;
					const int GETSOURCES=3;
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::DirectedDiscovery::GetSources> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::DirectedDiscovery::GetSources& v) {		
			avro::encode(e, v.m_uri);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::DirectedDiscovery::GetSources& v) {		
			avro::decode(e, v.m_uri);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace DirectedDiscovery {				
					struct GetTargets{					
						std::string m_uri;
						static const int messageTypeId=4;
						static const int protocolId=Energistics::Etp::v12::Datatypes::DirectedDiscovery;
					};					
					typedef boost::shared_ptr<GetTargets> GetTargetsPtr;
					const int GETTARGETS=4;
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::DirectedDiscovery::GetTargets> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::DirectedDiscovery::GetTargets& v) {		
			avro::encode(e, v.m_uri);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::DirectedDiscovery::GetTargets& v) {		
			avro::decode(e, v.m_uri);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace Discovery {				
					struct GetResources{					
						std::string m_uri;
						static const int messageTypeId=1;
						static const int protocolId=Energistics::Etp::v12::Datatypes::Discovery;
					};					
					typedef boost::shared_ptr<GetResources> GetResourcesPtr;
					const int GETRESOURCES=1;
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::Discovery::GetResources> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::Discovery::GetResources& v) {		
			avro::encode(e, v.m_uri);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::Discovery::GetResources& v) {		
			avro::decode(e, v.m_uri);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace Discovery {				
					struct GetResourcesResponse{					
						Energistics::Etp::v12::Datatypes::Object::Resource m_resource;
						static const int messageTypeId=2;
						static const int protocolId=Energistics::Etp::v12::Datatypes::Discovery;
					};					
					typedef boost::shared_ptr<GetResourcesResponse> GetResourcesResponsePtr;
					const int GETRESOURCESRESPONSE=2;
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::Discovery::GetResourcesResponse> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::Discovery::GetResourcesResponse& v) {		
			avro::encode(e, v.m_resource);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::Discovery::GetResourcesResponse& v) {		
			avro::decode(e, v.m_resource);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace DiscoveryQuery {				
					struct FindResources{					
						std::string m_uri;
						static const int messageTypeId=1;
						static const int protocolId=Energistics::Etp::v12::Datatypes::DiscoveryQuery;
					};					
					typedef boost::shared_ptr<FindResources> FindResourcesPtr;
					const int FINDRESOURCES=1;
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::DiscoveryQuery::FindResources> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::DiscoveryQuery::FindResources& v) {		
			avro::encode(e, v.m_uri);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::DiscoveryQuery::FindResources& v) {		
			avro::decode(e, v.m_uri);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace DiscoveryQuery {				
					struct FindResourcesResponse{					
						Energistics::Etp::v12::Datatypes::Object::Resource m_resource;
						std::string m_serverSortOrder;
						static const int messageTypeId=2;
						static const int protocolId=Energistics::Etp::v12::Datatypes::DiscoveryQuery;
					};					
					typedef boost::shared_ptr<FindResourcesResponse> FindResourcesResponsePtr;
					const int FINDRESOURCESRESPONSE=2;
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::DiscoveryQuery::FindResourcesResponse> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::DiscoveryQuery::FindResourcesResponse& v) {		
			avro::encode(e, v.m_resource);
			avro::encode(e, v.m_serverSortOrder);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::DiscoveryQuery::FindResourcesResponse& v) {		
			avro::decode(e, v.m_resource);
			avro::decode(e, v.m_serverSortOrder);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace GrowingObject {				
					struct DeletePart{					
						std::string m_uri;
						std::string m_uid;
						static const int messageTypeId=1;
						static const int protocolId=Energistics::Etp::v12::Datatypes::GrowingObject;
					};					
					typedef boost::shared_ptr<DeletePart> DeletePartPtr;
					const int DELETEPART=1;
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::GrowingObject::DeletePart> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::GrowingObject::DeletePart& v) {		
			avro::encode(e, v.m_uri);
			avro::encode(e, v.m_uid);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::GrowingObject::DeletePart& v) {		
			avro::decode(e, v.m_uri);
			avro::decode(e, v.m_uid);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace GrowingObject {				
					struct DeletePartsByRange{					
						std::string m_uri;
						Energistics::Etp::v12::Datatypes::Object::IndexInterval m_deleteInterval;
						bool m_includeOverlappingIntervals=false;
						static const int messageTypeId=2;
						static const int protocolId=Energistics::Etp::v12::Datatypes::GrowingObject;
					};					
					typedef boost::shared_ptr<DeletePartsByRange> DeletePartsByRangePtr;
					const int DELETEPARTSBYRANGE=2;
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::GrowingObject::DeletePartsByRange> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::GrowingObject::DeletePartsByRange& v) {		
			avro::encode(e, v.m_uri);
			avro::encode(e, v.m_deleteInterval);
			avro::encode(e, v.m_includeOverlappingIntervals);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::GrowingObject::DeletePartsByRange& v) {		
			avro::decode(e, v.m_uri);
			avro::decode(e, v.m_deleteInterval);
			avro::decode(e, v.m_includeOverlappingIntervals);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace GrowingObject {				
					struct DescribeParts{					
						std::string m_uri;
						static const int messageTypeId=8;
						static const int protocolId=Energistics::Etp::v12::Datatypes::GrowingObject;
					};					
					typedef boost::shared_ptr<DescribeParts> DescribePartsPtr;
					const int DESCRIBEPARTS=8;
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::GrowingObject::DescribeParts> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::GrowingObject::DescribeParts& v) {		
			avro::encode(e, v.m_uri);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::GrowingObject::DescribeParts& v) {		
			avro::decode(e, v.m_uri);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace GrowingObject {				
					struct GetPart{					
						std::string m_uri;
						std::string m_uid;
						static const int messageTypeId=3;
						static const int protocolId=Energistics::Etp::v12::Datatypes::GrowingObject;
					};					
					typedef boost::shared_ptr<GetPart> GetPartPtr;
					const int GETPART=3;
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::GrowingObject::GetPart> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::GrowingObject::GetPart& v) {		
			avro::encode(e, v.m_uri);
			avro::encode(e, v.m_uid);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::GrowingObject::GetPart& v) {		
			avro::decode(e, v.m_uri);
			avro::decode(e, v.m_uid);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace GrowingObject {				
					struct GetPartsByRange{					
						std::string m_uri;
						Energistics::Etp::v12::Datatypes::Object::IndexInterval m_indexInterval;
						bool m_includeOverlappingIntervals=false;
						static const int messageTypeId=4;
						static const int protocolId=Energistics::Etp::v12::Datatypes::GrowingObject;
					};					
					typedef boost::shared_ptr<GetPartsByRange> GetPartsByRangePtr;
					const int GETPARTSBYRANGE=4;
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::GrowingObject::GetPartsByRange> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::GrowingObject::GetPartsByRange& v) {		
			avro::encode(e, v.m_uri);
			avro::encode(e, v.m_indexInterval);
			avro::encode(e, v.m_includeOverlappingIntervals);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::GrowingObject::GetPartsByRange& v) {		
			avro::decode(e, v.m_uri);
			avro::decode(e, v.m_indexInterval);
			avro::decode(e, v.m_includeOverlappingIntervals);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace GrowingObject {				
					struct ObjectPart{					
						std::string m_uri;
						std::string m_contentType;
						std::string m_uid;
						std::string m_data;
						static const int messageTypeId=6;
						static const int protocolId=Energistics::Etp::v12::Datatypes::GrowingObject;
					};					
					typedef boost::shared_ptr<ObjectPart> ObjectPartPtr;
					const int OBJECTPART=6;
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::GrowingObject::ObjectPart> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::GrowingObject::ObjectPart& v) {		
			avro::encode(e, v.m_uri);
			avro::encode(e, v.m_contentType);
			avro::encode(e, v.m_uid);
			avro::encode(e, v.m_data);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::GrowingObject::ObjectPart& v) {		
			avro::decode(e, v.m_uri);
			avro::decode(e, v.m_contentType);
			avro::decode(e, v.m_uid);
			avro::decode(e, v.m_data);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace GrowingObject {				
					struct PartsMetadata{					
						std::string m_uri;
						Energistics::Etp::v12::Datatypes::ChannelData::ChannelIndexKinds m_indexKind;
						Energistics::Etp::v12::Datatypes::ChannelData::IndexDirections m_indexDirection;
						std::string m_name;
						Energistics::Etp::v12::Datatypes::Object::IndexInterval m_indexInterval;
						std::string m_uuid;
						std::map<std::string, Energistics::Etp::v12::Datatypes::DataValue> m_customData;
						static const int messageTypeId=9;
						static const int protocolId=Energistics::Etp::v12::Datatypes::GrowingObject;
					};					
					typedef boost::shared_ptr<PartsMetadata> PartsMetadataPtr;
					const int PARTSMETADATA=9;
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::GrowingObject::PartsMetadata> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::GrowingObject::PartsMetadata& v) {		
			avro::encode(e, v.m_uri);
			avro::encode(e, v.m_indexKind);
			avro::encode(e, v.m_indexDirection);
			avro::encode(e, v.m_name);
			avro::encode(e, v.m_indexInterval);
			avro::encode(e, v.m_uuid);
			avro::encode(e, v.m_customData);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::GrowingObject::PartsMetadata& v) {		
			avro::decode(e, v.m_uri);
			avro::decode(e, v.m_indexKind);
			avro::decode(e, v.m_indexDirection);
			avro::decode(e, v.m_name);
			avro::decode(e, v.m_indexInterval);
			avro::decode(e, v.m_uuid);
			avro::decode(e, v.m_customData);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace GrowingObject {				
					struct PutPart{					
						std::string m_uri;
						std::string m_contentType;
						std::string m_uid;
						std::string m_data;
						static const int messageTypeId=5;
						static const int protocolId=Energistics::Etp::v12::Datatypes::GrowingObject;
					};					
					typedef boost::shared_ptr<PutPart> PutPartPtr;
					const int PUTPART=5;
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::GrowingObject::PutPart> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::GrowingObject::PutPart& v) {		
			avro::encode(e, v.m_uri);
			avro::encode(e, v.m_contentType);
			avro::encode(e, v.m_uid);
			avro::encode(e, v.m_data);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::GrowingObject::PutPart& v) {		
			avro::decode(e, v.m_uri);
			avro::decode(e, v.m_contentType);
			avro::decode(e, v.m_uid);
			avro::decode(e, v.m_data);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace GrowingObject {				
					struct ReplacePartsByRange{					
						std::string m_uri;
						Energistics::Etp::v12::Datatypes::Object::IndexInterval m_deleteInterval;
						bool m_includeOverlappingIntervals=false;
						std::string m_contentType;
						std::string m_uid;
						std::string m_data;
						static const int messageTypeId=7;
						static const int protocolId=Energistics::Etp::v12::Datatypes::GrowingObject;
					};					
					typedef boost::shared_ptr<ReplacePartsByRange> ReplacePartsByRangePtr;
					const int REPLACEPARTSBYRANGE=7;
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::GrowingObject::ReplacePartsByRange> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::GrowingObject::ReplacePartsByRange& v) {		
			avro::encode(e, v.m_uri);
			avro::encode(e, v.m_deleteInterval);
			avro::encode(e, v.m_includeOverlappingIntervals);
			avro::encode(e, v.m_contentType);
			avro::encode(e, v.m_uid);
			avro::encode(e, v.m_data);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::GrowingObject::ReplacePartsByRange& v) {		
			avro::decode(e, v.m_uri);
			avro::decode(e, v.m_deleteInterval);
			avro::decode(e, v.m_includeOverlappingIntervals);
			avro::decode(e, v.m_contentType);
			avro::decode(e, v.m_uid);
			avro::decode(e, v.m_data);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace GrowingObjectQuery {				
					struct FindParts{					
						std::string m_uri;
						static const int messageTypeId=1;
						static const int protocolId=Energistics::Etp::v12::Datatypes::GrowingObjectQuery;
					};					
					typedef boost::shared_ptr<FindParts> FindPartsPtr;
					const int FINDPARTS=1;
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::GrowingObjectQuery::FindParts> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::GrowingObjectQuery::FindParts& v) {		
			avro::encode(e, v.m_uri);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::GrowingObjectQuery::FindParts& v) {		
			avro::decode(e, v.m_uri);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace GrowingObjectQuery {				
					struct FindPartsResponse{					
						std::string m_uri;
						std::string m_uid;
						std::string m_contentType;
						std::string m_data;
						std::string m_serverSortOrder;
						static const int messageTypeId=2;
						static const int protocolId=Energistics::Etp::v12::Datatypes::GrowingObjectQuery;
					};					
					typedef boost::shared_ptr<FindPartsResponse> FindPartsResponsePtr;
					const int FINDPARTSRESPONSE=2;
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::GrowingObjectQuery::FindPartsResponse> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::GrowingObjectQuery::FindPartsResponse& v) {		
			avro::encode(e, v.m_uri);
			avro::encode(e, v.m_uid);
			avro::encode(e, v.m_contentType);
			avro::encode(e, v.m_data);
			avro::encode(e, v.m_serverSortOrder);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::GrowingObjectQuery::FindPartsResponse& v) {		
			avro::decode(e, v.m_uri);
			avro::decode(e, v.m_uid);
			avro::decode(e, v.m_contentType);
			avro::decode(e, v.m_data);
			avro::decode(e, v.m_serverSortOrder);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace GrowingObjectNotification {				
					struct CancelPartNotification{					
						std::string m_requestUuid;
						static const int messageTypeId=4;
						static const int protocolId=Energistics::Etp::v12::Datatypes::GrowingObjectNotification;
					};					
					typedef boost::shared_ptr<CancelPartNotification> CancelPartNotificationPtr;
					const int CANCELPARTNOTIFICATION=4;
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::GrowingObjectNotification::CancelPartNotification> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::GrowingObjectNotification::CancelPartNotification& v) {		
			avro::encode(e, v.m_requestUuid);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::GrowingObjectNotification::CancelPartNotification& v) {		
			avro::decode(e, v.m_requestUuid);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace GrowingObjectNotification {				
					struct DeletePartsByRangeNotification{					
						std::string m_uri;
						Energistics::Etp::v12::Datatypes::Object::IndexInterval m_deletedInterval;
						bool m_includeOverlappingIntervals=false;
						int64_t m_changeTime;
						static const int messageTypeId=5;
						static const int protocolId=Energistics::Etp::v12::Datatypes::GrowingObjectNotification;
					};					
					typedef boost::shared_ptr<DeletePartsByRangeNotification> DeletePartsByRangeNotificationPtr;
					const int DELETEPARTSBYRANGENOTIFICATION=5;
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::GrowingObjectNotification::DeletePartsByRangeNotification> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::GrowingObjectNotification::DeletePartsByRangeNotification& v) {		
			avro::encode(e, v.m_uri);
			avro::encode(e, v.m_deletedInterval);
			avro::encode(e, v.m_includeOverlappingIntervals);
			avro::encode(e, v.m_changeTime);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::GrowingObjectNotification::DeletePartsByRangeNotification& v) {		
			avro::decode(e, v.m_uri);
			avro::decode(e, v.m_deletedInterval);
			avro::decode(e, v.m_includeOverlappingIntervals);
			avro::decode(e, v.m_changeTime);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace GrowingObjectNotification {				
					struct PartChangeNotification{					
						Energistics::Etp::v12::Datatypes::Object::ObjectChangeKinds m_changeKind;
						int64_t m_changeTime;
						std::string m_uri;
						std::string m_contentType;
						std::string m_uid;
						std::string m_data;
						static const int messageTypeId=2;
						static const int protocolId=Energistics::Etp::v12::Datatypes::GrowingObjectNotification;
					};					
					typedef boost::shared_ptr<PartChangeNotification> PartChangeNotificationPtr;
					const int PARTCHANGENOTIFICATION=2;
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::GrowingObjectNotification::PartChangeNotification> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::GrowingObjectNotification::PartChangeNotification& v) {		
			avro::encode(e, v.m_changeKind);
			avro::encode(e, v.m_changeTime);
			avro::encode(e, v.m_uri);
			avro::encode(e, v.m_contentType);
			avro::encode(e, v.m_uid);
			avro::encode(e, v.m_data);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::GrowingObjectNotification::PartChangeNotification& v) {		
			avro::decode(e, v.m_changeKind);
			avro::decode(e, v.m_changeTime);
			avro::decode(e, v.m_uri);
			avro::decode(e, v.m_contentType);
			avro::decode(e, v.m_uid);
			avro::decode(e, v.m_data);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace GrowingObjectNotification {				
					struct PartDeleteNotification{					
						std::string m_uri;
						std::string m_uid;
						int64_t m_changeTime;
						static const int messageTypeId=3;
						static const int protocolId=Energistics::Etp::v12::Datatypes::GrowingObjectNotification;
					};					
					typedef boost::shared_ptr<PartDeleteNotification> PartDeleteNotificationPtr;
					const int PARTDELETENOTIFICATION=3;
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::GrowingObjectNotification::PartDeleteNotification> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::GrowingObjectNotification::PartDeleteNotification& v) {		
			avro::encode(e, v.m_uri);
			avro::encode(e, v.m_uid);
			avro::encode(e, v.m_changeTime);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::GrowingObjectNotification::PartDeleteNotification& v) {		
			avro::decode(e, v.m_uri);
			avro::decode(e, v.m_uid);
			avro::decode(e, v.m_changeTime);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace GrowingObjectNotification {				
					struct ReplacePartsByRangeNotification{					
						std::string m_uri;
						Energistics::Etp::v12::Datatypes::Object::IndexInterval m_deletedInterval;
						bool m_includeOverlappingIntervals=false;
						std::string m_contentType;
						std::string m_uid;
						std::string m_data;
						int64_t m_changeTime;
						static const int messageTypeId=6;
						static const int protocolId=Energistics::Etp::v12::Datatypes::GrowingObjectNotification;
					};					
					typedef boost::shared_ptr<ReplacePartsByRangeNotification> ReplacePartsByRangeNotificationPtr;
					const int REPLACEPARTSBYRANGENOTIFICATION=6;
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::GrowingObjectNotification::ReplacePartsByRangeNotification> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::GrowingObjectNotification::ReplacePartsByRangeNotification& v) {		
			avro::encode(e, v.m_uri);
			avro::encode(e, v.m_deletedInterval);
			avro::encode(e, v.m_includeOverlappingIntervals);
			avro::encode(e, v.m_contentType);
			avro::encode(e, v.m_uid);
			avro::encode(e, v.m_data);
			avro::encode(e, v.m_changeTime);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::GrowingObjectNotification::ReplacePartsByRangeNotification& v) {		
			avro::decode(e, v.m_uri);
			avro::decode(e, v.m_deletedInterval);
			avro::decode(e, v.m_includeOverlappingIntervals);
			avro::decode(e, v.m_contentType);
			avro::decode(e, v.m_uid);
			avro::decode(e, v.m_data);
			avro::decode(e, v.m_changeTime);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace GrowingObjectNotification {				
					struct RequestPartNotification{					
						Energistics::Etp::v12::Datatypes::Object::NotificationRequestRecord m_request;
						static const int messageTypeId=1;
						static const int protocolId=Energistics::Etp::v12::Datatypes::GrowingObjectNotification;
					};					
					typedef boost::shared_ptr<RequestPartNotification> RequestPartNotificationPtr;
					const int REQUESTPARTNOTIFICATION=1;
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::GrowingObjectNotification::RequestPartNotification> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::GrowingObjectNotification::RequestPartNotification& v) {		
			avro::encode(e, v.m_request);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::GrowingObjectNotification::RequestPartNotification& v) {		
			avro::decode(e, v.m_request);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace Store {				
					struct DeleteObject{					
						std::string m_uri;
						static const int messageTypeId=3;
						static const int protocolId=Energistics::Etp::v12::Datatypes::Store;
					};					
					typedef boost::shared_ptr<DeleteObject> DeleteObjectPtr;
					const int DELETEOBJECT=3;
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::Store::DeleteObject> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::Store::DeleteObject& v) {		
			avro::encode(e, v.m_uri);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::Store::DeleteObject& v) {		
			avro::decode(e, v.m_uri);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace Store {				
					struct GetObject{					
						std::string m_uri;
						static const int messageTypeId=1;
						static const int protocolId=Energistics::Etp::v12::Datatypes::Store;
					};					
					typedef boost::shared_ptr<GetObject> GetObjectPtr;
					const int GETOBJECT=1;
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::Store::GetObject> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::Store::GetObject& v) {		
			avro::encode(e, v.m_uri);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::Store::GetObject& v) {		
			avro::decode(e, v.m_uri);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace Store {				
					struct Object{					
						Energistics::Etp::v12::Datatypes::Object::DataObject m_dataObject;
						static const int messageTypeId=4;
						static const int protocolId=Energistics::Etp::v12::Datatypes::Store;
					};					
					typedef boost::shared_ptr<Object> ObjectPtr;
					const int OBJECT=4;
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::Store::Object> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::Store::Object& v) {		
			avro::encode(e, v.m_dataObject);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::Store::Object& v) {		
			avro::decode(e, v.m_dataObject);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace Store {				
					struct PutObject{					
						Energistics::Etp::v12::Datatypes::Object::DataObject m_dataObject;
						static const int messageTypeId=2;
						static const int protocolId=Energistics::Etp::v12::Datatypes::Store;
					};					
					typedef boost::shared_ptr<PutObject> PutObjectPtr;
					const int PUTOBJECT=2;
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::Store::PutObject> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::Store::PutObject& v) {		
			avro::encode(e, v.m_dataObject);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::Store::PutObject& v) {		
			avro::decode(e, v.m_dataObject);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace StoreNotification {				
					struct CancelNotification{					
						std::string m_requestUuid;
						static const int messageTypeId=4;
						static const int protocolId=Energistics::Etp::v12::Datatypes::StoreNotification;
					};					
					typedef boost::shared_ptr<CancelNotification> CancelNotificationPtr;
					const int CANCELNOTIFICATION=4;
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::StoreNotification::CancelNotification> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::StoreNotification::CancelNotification& v) {		
			avro::encode(e, v.m_requestUuid);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::StoreNotification::CancelNotification& v) {		
			avro::decode(e, v.m_requestUuid);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace StoreNotification {				
					struct ChangeNotification{					
						Energistics::Etp::v12::Datatypes::Object::ObjectChange m_change;
						static const int messageTypeId=2;
						static const int protocolId=Energistics::Etp::v12::Datatypes::StoreNotification;
					};					
					typedef boost::shared_ptr<ChangeNotification> ChangeNotificationPtr;
					const int CHANGENOTIFICATION=2;
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::StoreNotification::ChangeNotification> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::StoreNotification::ChangeNotification& v) {		
			avro::encode(e, v.m_change);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::StoreNotification::ChangeNotification& v) {		
			avro::decode(e, v.m_change);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace StoreNotification {				
					struct DeleteNotification{					
						std::string m_uri;
						int64_t m_changeTime;
						static const int messageTypeId=3;
						static const int protocolId=Energistics::Etp::v12::Datatypes::StoreNotification;
					};					
					typedef boost::shared_ptr<DeleteNotification> DeleteNotificationPtr;
					const int DELETENOTIFICATION=3;
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::StoreNotification::DeleteNotification> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::StoreNotification::DeleteNotification& v) {		
			avro::encode(e, v.m_uri);
			avro::encode(e, v.m_changeTime);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::StoreNotification::DeleteNotification& v) {		
			avro::decode(e, v.m_uri);
			avro::decode(e, v.m_changeTime);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace StoreNotification {				
					struct NotificationRequest{					
						Energistics::Etp::v12::Datatypes::Object::NotificationRequestRecord m_request;
						static const int messageTypeId=1;
						static const int protocolId=Energistics::Etp::v12::Datatypes::StoreNotification;
					};					
					typedef boost::shared_ptr<NotificationRequest> NotificationRequestPtr;
					const int NOTIFICATIONREQUEST=1;
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::StoreNotification::NotificationRequest> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::StoreNotification::NotificationRequest& v) {		
			avro::encode(e, v.m_request);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::StoreNotification::NotificationRequest& v) {		
			avro::decode(e, v.m_request);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace Transaction {				
					struct EndSessionTransaction{					
						static const int messageTypeId=3;
						static const int protocolId=Energistics::Etp::v12::Datatypes::Transaction;
					};					
					typedef boost::shared_ptr<EndSessionTransaction> EndSessionTransactionPtr;
					const int ENDSESSIONTRANSACTION=3;
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::Transaction::EndSessionTransaction> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::Transaction::EndSessionTransaction& v) {		
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::Transaction::EndSessionTransaction& v) {		
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace Transaction {				
					struct StartTransaction{					
						static const int messageTypeId=1;
						static const int protocolId=Energistics::Etp::v12::Datatypes::Transaction;
					};					
					typedef boost::shared_ptr<StartTransaction> StartTransactionPtr;
					const int STARTTRANSACTION=1;
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::Transaction::StartTransaction> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::Transaction::StartTransaction& v) {		
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::Transaction::StartTransaction& v) {		
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace Transaction {				
					struct TransactionResponse{					
						std::string m_uuid;
						static const int messageTypeId=2;
						static const int protocolId=Energistics::Etp::v12::Datatypes::Transaction;
					};					
					typedef boost::shared_ptr<TransactionResponse> TransactionResponsePtr;
					const int TRANSACTIONRESPONSE=2;
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::Transaction::TransactionResponse> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::Transaction::TransactionResponse& v) {		
			avro::encode(e, v.m_uuid);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::Transaction::TransactionResponse& v) {		
			avro::decode(e, v.m_uuid);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace StoreQuery {				
					struct FindObjects{					
						std::string m_uri;
						static const int messageTypeId=1;
						static const int protocolId=Energistics::Etp::v12::Datatypes::StoreQuery;
					};					
					typedef boost::shared_ptr<FindObjects> FindObjectsPtr;
					const int FINDOBJECTS=1;
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::StoreQuery::FindObjects> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::StoreQuery::FindObjects& v) {		
			avro::encode(e, v.m_uri);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::StoreQuery::FindObjects& v) {		
			avro::decode(e, v.m_uri);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace StoreQuery {				
					struct FindObjectsResponse{					
						Energistics::Etp::v12::Datatypes::Object::DataObject m_dataObject;
						std::string m_serverSortOrder;
						static const int messageTypeId=2;
						static const int protocolId=Energistics::Etp::v12::Datatypes::StoreQuery;
					};					
					typedef boost::shared_ptr<FindObjectsResponse> FindObjectsResponsePtr;
					const int FINDOBJECTSRESPONSE=2;
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::StoreQuery::FindObjectsResponse> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::StoreQuery::FindObjectsResponse& v) {		
			avro::encode(e, v.m_dataObject);
			avro::encode(e, v.m_serverSortOrder);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::StoreQuery::FindObjectsResponse& v) {		
			avro::decode(e, v.m_dataObject);
			avro::decode(e, v.m_serverSortOrder);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace WitsmlSoap {				
					struct WMLS_AddToStore{					
						std::string m_WMLtypeIn;
						std::string m_XMLin;
						std::string m_OptionsIn;
						std::string m_CapabilitiesIn;
						static const int messageTypeId=1;
						static const int protocolId=Energistics::Etp::v12::Datatypes::WitsmlSoap;
					};					
					typedef boost::shared_ptr<WMLS_AddToStore> WMLS_AddToStorePtr;
					const int WMLS_ADDTOSTORE=1;
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::WitsmlSoap::WMLS_AddToStore> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::WitsmlSoap::WMLS_AddToStore& v) {		
			avro::encode(e, v.m_WMLtypeIn);
			avro::encode(e, v.m_XMLin);
			avro::encode(e, v.m_OptionsIn);
			avro::encode(e, v.m_CapabilitiesIn);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::WitsmlSoap::WMLS_AddToStore& v) {		
			avro::decode(e, v.m_WMLtypeIn);
			avro::decode(e, v.m_XMLin);
			avro::decode(e, v.m_OptionsIn);
			avro::decode(e, v.m_CapabilitiesIn);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace WitsmlSoap {				
					struct WMLS_DeleteFromStore{					
						std::string m_WMLtypeIn;
						std::string m_XMLin;
						std::string m_OptionsIn;
						std::string m_CapabilitiesIn;
						static const int messageTypeId=3;
						static const int protocolId=Energistics::Etp::v12::Datatypes::WitsmlSoap;
					};					
					typedef boost::shared_ptr<WMLS_DeleteFromStore> WMLS_DeleteFromStorePtr;
					const int WMLS_DELETEFROMSTORE=3;
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::WitsmlSoap::WMLS_DeleteFromStore> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::WitsmlSoap::WMLS_DeleteFromStore& v) {		
			avro::encode(e, v.m_WMLtypeIn);
			avro::encode(e, v.m_XMLin);
			avro::encode(e, v.m_OptionsIn);
			avro::encode(e, v.m_CapabilitiesIn);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::WitsmlSoap::WMLS_DeleteFromStore& v) {		
			avro::decode(e, v.m_WMLtypeIn);
			avro::decode(e, v.m_XMLin);
			avro::decode(e, v.m_OptionsIn);
			avro::decode(e, v.m_CapabilitiesIn);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace WitsmlSoap {				
					struct WMLS_GetBaseMsg{					
						int32_t m_ReturnValueIn;
						static const int messageTypeId=5;
						static const int protocolId=Energistics::Etp::v12::Datatypes::WitsmlSoap;
					};					
					typedef boost::shared_ptr<WMLS_GetBaseMsg> WMLS_GetBaseMsgPtr;
					const int WMLS_GETBASEMSG=5;
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::WitsmlSoap::WMLS_GetBaseMsg> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::WitsmlSoap::WMLS_GetBaseMsg& v) {		
			avro::encode(e, v.m_ReturnValueIn);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::WitsmlSoap::WMLS_GetBaseMsg& v) {		
			avro::decode(e, v.m_ReturnValueIn);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace WitsmlSoap {				
					struct WMLS_GetCap{					
						std::string m_OptionsIn;
						static const int messageTypeId=7;
						static const int protocolId=Energistics::Etp::v12::Datatypes::WitsmlSoap;
					};					
					typedef boost::shared_ptr<WMLS_GetCap> WMLS_GetCapPtr;
					const int WMLS_GETCAP=7;
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::WitsmlSoap::WMLS_GetCap> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::WitsmlSoap::WMLS_GetCap& v) {		
			avro::encode(e, v.m_OptionsIn);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::WitsmlSoap::WMLS_GetCap& v) {		
			avro::decode(e, v.m_OptionsIn);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace WitsmlSoap {				
					struct WMLS_GetFromStore{					
						std::string m_WMLtypeIn;
						std::string m_XMLin;
						std::string m_OptionsIn;
						std::string m_CapabilitiesIn;
						static const int messageTypeId=9;
						static const int protocolId=Energistics::Etp::v12::Datatypes::WitsmlSoap;
					};					
					typedef boost::shared_ptr<WMLS_GetFromStore> WMLS_GetFromStorePtr;
					const int WMLS_GETFROMSTORE=9;
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::WitsmlSoap::WMLS_GetFromStore> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::WitsmlSoap::WMLS_GetFromStore& v) {		
			avro::encode(e, v.m_WMLtypeIn);
			avro::encode(e, v.m_XMLin);
			avro::encode(e, v.m_OptionsIn);
			avro::encode(e, v.m_CapabilitiesIn);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::WitsmlSoap::WMLS_GetFromStore& v) {		
			avro::decode(e, v.m_WMLtypeIn);
			avro::decode(e, v.m_XMLin);
			avro::decode(e, v.m_OptionsIn);
			avro::decode(e, v.m_CapabilitiesIn);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace WitsmlSoap {				
					struct WMLS_GetVersion{					
						static const int messageTypeId=11;
						static const int protocolId=Energistics::Etp::v12::Datatypes::WitsmlSoap;
					};					
					typedef boost::shared_ptr<WMLS_GetVersion> WMLS_GetVersionPtr;
					const int WMLS_GETVERSION=11;
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::WitsmlSoap::WMLS_GetVersion> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::WitsmlSoap::WMLS_GetVersion& v) {		
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::WitsmlSoap::WMLS_GetVersion& v) {		
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace WitsmlSoap {				
					struct WMLS_UpdateInStore{					
						std::string m_WMLtypeIn;
						std::string m_XMLin;
						std::string m_OptionsIn;
						std::string m_CapabilitiesIn;
						static const int messageTypeId=13;
						static const int protocolId=Energistics::Etp::v12::Datatypes::WitsmlSoap;
					};					
					typedef boost::shared_ptr<WMLS_UpdateInStore> WMLS_UpdateInStorePtr;
					const int WMLS_UPDATEINSTORE=13;
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::WitsmlSoap::WMLS_UpdateInStore> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::WitsmlSoap::WMLS_UpdateInStore& v) {		
			avro::encode(e, v.m_WMLtypeIn);
			avro::encode(e, v.m_XMLin);
			avro::encode(e, v.m_OptionsIn);
			avro::encode(e, v.m_CapabilitiesIn);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::WitsmlSoap::WMLS_UpdateInStore& v) {		
			avro::decode(e, v.m_WMLtypeIn);
			avro::decode(e, v.m_XMLin);
			avro::decode(e, v.m_OptionsIn);
			avro::decode(e, v.m_CapabilitiesIn);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace WitsmlSoap {				
					struct WMSL_AddToStoreResponse{					
						int32_t m_Result;
						std::string m_SuppMsgOut;
						static const int messageTypeId=2;
						static const int protocolId=Energistics::Etp::v12::Datatypes::WitsmlSoap;
					};					
					typedef boost::shared_ptr<WMSL_AddToStoreResponse> WMSL_AddToStoreResponsePtr;
					const int WMSL_ADDTOSTORERESPONSE=2;
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::WitsmlSoap::WMSL_AddToStoreResponse> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::WitsmlSoap::WMSL_AddToStoreResponse& v) {		
			avro::encode(e, v.m_Result);
			avro::encode(e, v.m_SuppMsgOut);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::WitsmlSoap::WMSL_AddToStoreResponse& v) {		
			avro::decode(e, v.m_Result);
			avro::decode(e, v.m_SuppMsgOut);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace WitsmlSoap {				
					struct WMSL_DeleteFromStoreResponse{					
						int32_t m_Result;
						std::string m_SuppMsgOut;
						static const int messageTypeId=4;
						static const int protocolId=Energistics::Etp::v12::Datatypes::WitsmlSoap;
					};					
					typedef boost::shared_ptr<WMSL_DeleteFromStoreResponse> WMSL_DeleteFromStoreResponsePtr;
					const int WMSL_DELETEFROMSTORERESPONSE=4;
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::WitsmlSoap::WMSL_DeleteFromStoreResponse> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::WitsmlSoap::WMSL_DeleteFromStoreResponse& v) {		
			avro::encode(e, v.m_Result);
			avro::encode(e, v.m_SuppMsgOut);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::WitsmlSoap::WMSL_DeleteFromStoreResponse& v) {		
			avro::decode(e, v.m_Result);
			avro::decode(e, v.m_SuppMsgOut);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace WitsmlSoap {				
					struct WMSL_GetBaseMsgResponse{					
						std::string m_Result;
						static const int messageTypeId=6;
						static const int protocolId=Energistics::Etp::v12::Datatypes::WitsmlSoap;
					};					
					typedef boost::shared_ptr<WMSL_GetBaseMsgResponse> WMSL_GetBaseMsgResponsePtr;
					const int WMSL_GETBASEMSGRESPONSE=6;
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::WitsmlSoap::WMSL_GetBaseMsgResponse> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::WitsmlSoap::WMSL_GetBaseMsgResponse& v) {		
			avro::encode(e, v.m_Result);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::WitsmlSoap::WMSL_GetBaseMsgResponse& v) {		
			avro::decode(e, v.m_Result);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace WitsmlSoap {				
					struct WMSL_GetCapResponse{					
						int32_t m_Result;
						std::string m_CapabilitiesOut;
						std::string m_SuppMsgOut;
						static const int messageTypeId=8;
						static const int protocolId=Energistics::Etp::v12::Datatypes::WitsmlSoap;
					};					
					typedef boost::shared_ptr<WMSL_GetCapResponse> WMSL_GetCapResponsePtr;
					const int WMSL_GETCAPRESPONSE=8;
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::WitsmlSoap::WMSL_GetCapResponse> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::WitsmlSoap::WMSL_GetCapResponse& v) {		
			avro::encode(e, v.m_Result);
			avro::encode(e, v.m_CapabilitiesOut);
			avro::encode(e, v.m_SuppMsgOut);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::WitsmlSoap::WMSL_GetCapResponse& v) {		
			avro::decode(e, v.m_Result);
			avro::decode(e, v.m_CapabilitiesOut);
			avro::decode(e, v.m_SuppMsgOut);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace WitsmlSoap {				
					struct WMSL_GetFromStoreResponse{					
						int32_t m_Result;
						std::string m_XMLout;
						std::string m_SuppMsgOut;
						static const int messageTypeId=10;
						static const int protocolId=Energistics::Etp::v12::Datatypes::WitsmlSoap;
					};					
					typedef boost::shared_ptr<WMSL_GetFromStoreResponse> WMSL_GetFromStoreResponsePtr;
					const int WMSL_GETFROMSTORERESPONSE=10;
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::WitsmlSoap::WMSL_GetFromStoreResponse> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::WitsmlSoap::WMSL_GetFromStoreResponse& v) {		
			avro::encode(e, v.m_Result);
			avro::encode(e, v.m_XMLout);
			avro::encode(e, v.m_SuppMsgOut);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::WitsmlSoap::WMSL_GetFromStoreResponse& v) {		
			avro::decode(e, v.m_Result);
			avro::decode(e, v.m_XMLout);
			avro::decode(e, v.m_SuppMsgOut);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace WitsmlSoap {				
					struct WMSL_GetVersionResponse{					
						std::string m_Result;
						static const int messageTypeId=12;
						static const int protocolId=Energistics::Etp::v12::Datatypes::WitsmlSoap;
					};					
					typedef boost::shared_ptr<WMSL_GetVersionResponse> WMSL_GetVersionResponsePtr;
					const int WMSL_GETVERSIONRESPONSE=12;
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::WitsmlSoap::WMSL_GetVersionResponse> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::WitsmlSoap::WMSL_GetVersionResponse& v) {		
			avro::encode(e, v.m_Result);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::WitsmlSoap::WMSL_GetVersionResponse& v) {		
			avro::decode(e, v.m_Result);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace WitsmlSoap {				
					struct WMSL_UpdateInStoreResponse{					
						int32_t m_Result;
						std::string m_SuppMsgOut;
						static const int messageTypeId=14;
						static const int protocolId=Energistics::Etp::v12::Datatypes::WitsmlSoap;
					};					
					typedef boost::shared_ptr<WMSL_UpdateInStoreResponse> WMSL_UpdateInStoreResponsePtr;
					const int WMSL_UPDATEINSTORERESPONSE=14;
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::WitsmlSoap::WMSL_UpdateInStoreResponse> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::WitsmlSoap::WMSL_UpdateInStoreResponse& v) {		
			avro::encode(e, v.m_Result);
			avro::encode(e, v.m_SuppMsgOut);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::WitsmlSoap::WMSL_UpdateInStoreResponse& v) {		
			avro::decode(e, v.m_Result);
			avro::decode(e, v.m_SuppMsgOut);
		}		
	};	
}


#endif
