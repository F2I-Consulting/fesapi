#ifndef ETP_MESSAGES__
#define ETP_MESSAGES__

#include <map>
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <array>

#include "boost/any.hpp"
#include "avro/Specific.hh"
#include "avro/Encoder.hh"
#include "avro/Decoder.hh"

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
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Datatypes::AnyArrayType> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Datatypes::AnyArrayType& v) {		
			e.encodeEnum(v);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Datatypes::AnyArrayType& v) {		
			v = static_cast<Energistics::Etp::v12::Datatypes::AnyArrayType>(e.decodeEnum());
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
				struct ArrayOfDouble{				
					std::vector<double> m_values;
				};				
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
				struct ArrayOfFloat{				
					std::vector<float> m_values;
				};				
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
				struct ArrayOfInt{				
					std::vector<int32_t> m_values;
				};				
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
				struct ArrayOfString{				
					std::vector<std::string> m_values;
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Datatypes::ArrayOfString> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Datatypes::ArrayOfString& v) {		
			avro::encode(e, v.m_values);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Datatypes::ArrayOfString& v) {		
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
					Energistics::Etp::v12::Datatypes::ArrayOfBoolean const & get_ArrayOfBoolean() const {					
						if (idx_ != 1) {						
							throw avro::Exception("Invalid type for union.");
						}						
						return boost::any_cast< Energistics::Etp::v12::Datatypes::ArrayOfBoolean const & >(value_);
					}					
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
					Energistics::Etp::v12::Datatypes::ArrayOfInt const & get_ArrayOfInt() const {					
						if (idx_ != 2) {						
							throw avro::Exception("Invalid type for union.");
						}						
						return boost::any_cast< Energistics::Etp::v12::Datatypes::ArrayOfInt const & >(value_);
					}					
					Energistics::Etp::v12::Datatypes::ArrayOfInt& get_ArrayOfInt()  {					
						if (idx_ != 2) {						
							throw avro::Exception("Invalid type for union.");
						}						
						return boost::any_cast< Energistics::Etp::v12::Datatypes::ArrayOfInt& >(value_);
					}					
					void set_ArrayOfInt(const Energistics::Etp::v12::Datatypes::ArrayOfInt& v) {					
						idx_ = 2;
						value_ = v;
					}					
					Energistics::Etp::v12::Datatypes::ArrayOfLong const & get_ArrayOfLong() const {					
						if (idx_ != 3) {						
							throw avro::Exception("Invalid type for union.");
						}						
						return boost::any_cast< Energistics::Etp::v12::Datatypes::ArrayOfLong const & >(value_);
					}					
					Energistics::Etp::v12::Datatypes::ArrayOfLong& get_ArrayOfLong()  {					
						if (idx_ != 3) {						
							throw avro::Exception("Invalid type for union.");
						}						
						return boost::any_cast< Energistics::Etp::v12::Datatypes::ArrayOfLong& >(value_);
					}					
					void set_ArrayOfLong(const Energistics::Etp::v12::Datatypes::ArrayOfLong& v) {					
						idx_ = 3;
						value_ = v;
					}					
					Energistics::Etp::v12::Datatypes::ArrayOfFloat const & get_ArrayOfFloat() const {					
						if (idx_ != 4) {						
							throw avro::Exception("Invalid type for union.");
						}						
						return boost::any_cast< Energistics::Etp::v12::Datatypes::ArrayOfFloat const & >(value_);
					}					
					Energistics::Etp::v12::Datatypes::ArrayOfFloat& get_ArrayOfFloat()  {					
						if (idx_ != 4) {						
							throw avro::Exception("Invalid type for union.");
						}						
						return boost::any_cast< Energistics::Etp::v12::Datatypes::ArrayOfFloat& >(value_);
					}					
					void set_ArrayOfFloat(const Energistics::Etp::v12::Datatypes::ArrayOfFloat& v) {					
						idx_ = 4;
						value_ = v;
					}					
					Energistics::Etp::v12::Datatypes::ArrayOfDouble const & get_ArrayOfDouble() const {					
						if (idx_ != 5) {						
							throw avro::Exception("Invalid type for union.");
						}						
						return boost::any_cast< Energistics::Etp::v12::Datatypes::ArrayOfDouble const & >(value_);
					}					
					Energistics::Etp::v12::Datatypes::ArrayOfDouble& get_ArrayOfDouble()  {					
						if (idx_ != 5) {						
							throw avro::Exception("Invalid type for union.");
						}						
						return boost::any_cast< Energistics::Etp::v12::Datatypes::ArrayOfDouble& >(value_);
					}					
					void set_ArrayOfDouble(const Energistics::Etp::v12::Datatypes::ArrayOfDouble& v) {					
						idx_ = 5;
						value_ = v;
					}					
					Energistics::Etp::v12::Datatypes::ArrayOfString const & get_ArrayOfString() const {					
						if (idx_ != 6) {						
							throw avro::Exception("Invalid type for union.");
						}						
						return boost::any_cast< Energistics::Etp::v12::Datatypes::ArrayOfString const & >(value_);
					}					
					Energistics::Etp::v12::Datatypes::ArrayOfString& get_ArrayOfString()  {					
						if (idx_ != 6) {						
							throw avro::Exception("Invalid type for union.");
						}						
						return boost::any_cast< Energistics::Etp::v12::Datatypes::ArrayOfString& >(value_);
					}					
					void set_ArrayOfString(const Energistics::Etp::v12::Datatypes::ArrayOfString& v) {					
						idx_ = 6;
						value_ = v;
					}					
					std::string const & get_bytes() const {					
						if (idx_ != 7) {						
							throw avro::Exception("Invalid type for union.");
						}						
						return boost::any_cast< std::string const & >(value_);
					}					
					std::string& get_bytes()  {					
						if (idx_ != 7) {						
							throw avro::Exception("Invalid type for union.");
						}						
						return boost::any_cast< std::string& >(value_);
					}					
					void set_bytes(const std::string& v) {					
						idx_ = 7;
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
					avro::encode(e, v.get_ArrayOfInt());
					break;								
				case 3:				
					avro::encode(e, v.get_ArrayOfLong());
					break;								
				case 4:				
					avro::encode(e, v.get_ArrayOfFloat());
					break;								
				case 5:				
					avro::encode(e, v.get_ArrayOfDouble());
					break;								
				case 6:				
					avro::encode(e, v.get_ArrayOfString());
					break;								
				case 7:				
					avro::encode(e, v.get_bytes());
					break;								
			}			
		}		
		static void decode(Decoder& d, Energistics::Etp::v12::Datatypes::AnyArrayitem_t& v) {
		
			size_t n = d.decodeUnionIndex();
			if (n >= 8) { throw avro::Exception("Union index too big"); }
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
						Energistics::Etp::v12::Datatypes::ArrayOfInt vv;
						avro::decode(d, vv);
						v.set_ArrayOfInt(vv);
					}					
					break;								
				case 3:				
					{					
						Energistics::Etp::v12::Datatypes::ArrayOfLong vv;
						avro::decode(d, vv);
						v.set_ArrayOfLong(vv);
					}					
					break;								
				case 4:				
					{					
						Energistics::Etp::v12::Datatypes::ArrayOfFloat vv;
						avro::decode(d, vv);
						v.set_ArrayOfFloat(vv);
					}					
					break;								
				case 5:				
					{					
						Energistics::Etp::v12::Datatypes::ArrayOfDouble vv;
						avro::decode(d, vv);
						v.set_ArrayOfDouble(vv);
					}					
					break;								
				case 6:				
					{					
						Energistics::Etp::v12::Datatypes::ArrayOfString vv;
						avro::decode(d, vv);
						v.set_ArrayOfString(vv);
					}					
					break;								
				case 7:				
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
				struct AnyArray{				
					Energistics::Etp::v12::Datatypes::AnyArrayitem_t m_item;
				};				
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
					bool const & get_boolean() const {					
						if (idx_ != 1) {						
							throw avro::Exception("Invalid type for union.");
						}						
						return boost::any_cast< bool const & >(value_);
					}					
					bool& get_boolean()  {					
						if (idx_ != 1) {						
							throw avro::Exception("Invalid type for union.");
						}						
						return boost::any_cast< bool& >(value_);
					}					
					void set_boolean(const bool& v) {					
						idx_ = 1;
						value_ = v;
					}					
					int32_t const & get_int() const {					
						if (idx_ != 2) {						
							throw avro::Exception("Invalid type for union.");
						}						
						return boost::any_cast< int32_t const & >(value_);
					}					
					int32_t& get_int()  {					
						if (idx_ != 2) {						
							throw avro::Exception("Invalid type for union.");
						}						
						return boost::any_cast< int32_t& >(value_);
					}					
					void set_int(const int32_t& v) {					
						idx_ = 2;
						value_ = v;
					}					
					int64_t const & get_long() const {					
						if (idx_ != 3) {						
							throw avro::Exception("Invalid type for union.");
						}						
						return boost::any_cast< int64_t const & >(value_);
					}					
					int64_t& get_long()  {					
						if (idx_ != 3) {						
							throw avro::Exception("Invalid type for union.");
						}						
						return boost::any_cast< int64_t& >(value_);
					}					
					void set_long(const int64_t& v) {					
						idx_ = 3;
						value_ = v;
					}					
					float const & get_float() const {					
						if (idx_ != 4) {						
							throw avro::Exception("Invalid type for union.");
						}						
						return boost::any_cast< float const & >(value_);
					}					
					float& get_float()  {					
						if (idx_ != 4) {						
							throw avro::Exception("Invalid type for union.");
						}						
						return boost::any_cast< float& >(value_);
					}					
					void set_float(const float& v) {					
						idx_ = 4;
						value_ = v;
					}					
					double const & get_double() const {					
						if (idx_ != 5) {						
							throw avro::Exception("Invalid type for union.");
						}						
						return boost::any_cast< double const & >(value_);
					}					
					double& get_double()  {					
						if (idx_ != 5) {						
							throw avro::Exception("Invalid type for union.");
						}						
						return boost::any_cast< double& >(value_);
					}					
					void set_double(const double& v) {					
						idx_ = 5;
						value_ = v;
					}					
					std::string const & get_string() const {					
						if (idx_ != 6) {						
							throw avro::Exception("Invalid type for union.");
						}						
						return boost::any_cast< std::string const & >(value_);
					}					
					std::string& get_string()  {					
						if (idx_ != 6) {						
							throw avro::Exception("Invalid type for union.");
						}						
						return boost::any_cast< std::string& >(value_);
					}					
					void set_string(const std::string& v) {					
						idx_ = 6;
						value_ = v;
					}					
					Energistics::Etp::v12::Datatypes::ArrayOfBoolean const & get_ArrayOfBoolean() const {					
						if (idx_ != 7) {						
							throw avro::Exception("Invalid type for union.");
						}						
						return boost::any_cast< Energistics::Etp::v12::Datatypes::ArrayOfBoolean const & >(value_);
					}					
					Energistics::Etp::v12::Datatypes::ArrayOfBoolean& get_ArrayOfBoolean()  {					
						if (idx_ != 7) {						
							throw avro::Exception("Invalid type for union.");
						}						
						return boost::any_cast< Energistics::Etp::v12::Datatypes::ArrayOfBoolean& >(value_);
					}					
					void set_ArrayOfBoolean(const Energistics::Etp::v12::Datatypes::ArrayOfBoolean& v) {					
						idx_ = 7;
						value_ = v;
					}					
					Energistics::Etp::v12::Datatypes::ArrayOfInt const & get_ArrayOfInt() const {					
						if (idx_ != 8) {						
							throw avro::Exception("Invalid type for union.");
						}						
						return boost::any_cast< Energistics::Etp::v12::Datatypes::ArrayOfInt const & >(value_);
					}					
					Energistics::Etp::v12::Datatypes::ArrayOfInt& get_ArrayOfInt()  {					
						if (idx_ != 8) {						
							throw avro::Exception("Invalid type for union.");
						}						
						return boost::any_cast< Energistics::Etp::v12::Datatypes::ArrayOfInt& >(value_);
					}					
					void set_ArrayOfInt(const Energistics::Etp::v12::Datatypes::ArrayOfInt& v) {					
						idx_ = 8;
						value_ = v;
					}					
					Energistics::Etp::v12::Datatypes::ArrayOfLong const & get_ArrayOfLong() const {					
						if (idx_ != 9) {						
							throw avro::Exception("Invalid type for union.");
						}						
						return boost::any_cast< Energistics::Etp::v12::Datatypes::ArrayOfLong const & >(value_);
					}					
					Energistics::Etp::v12::Datatypes::ArrayOfLong& get_ArrayOfLong()  {					
						if (idx_ != 9) {						
							throw avro::Exception("Invalid type for union.");
						}						
						return boost::any_cast< Energistics::Etp::v12::Datatypes::ArrayOfLong& >(value_);
					}					
					void set_ArrayOfLong(const Energistics::Etp::v12::Datatypes::ArrayOfLong& v) {					
						idx_ = 9;
						value_ = v;
					}					
					Energistics::Etp::v12::Datatypes::ArrayOfFloat const & get_ArrayOfFloat() const {					
						if (idx_ != 10) {						
							throw avro::Exception("Invalid type for union.");
						}						
						return boost::any_cast< Energistics::Etp::v12::Datatypes::ArrayOfFloat const & >(value_);
					}					
					Energistics::Etp::v12::Datatypes::ArrayOfFloat& get_ArrayOfFloat()  {					
						if (idx_ != 10) {						
							throw avro::Exception("Invalid type for union.");
						}						
						return boost::any_cast< Energistics::Etp::v12::Datatypes::ArrayOfFloat& >(value_);
					}					
					void set_ArrayOfFloat(const Energistics::Etp::v12::Datatypes::ArrayOfFloat& v) {					
						idx_ = 10;
						value_ = v;
					}					
					Energistics::Etp::v12::Datatypes::ArrayOfDouble const & get_ArrayOfDouble() const {					
						if (idx_ != 11) {						
							throw avro::Exception("Invalid type for union.");
						}						
						return boost::any_cast< Energistics::Etp::v12::Datatypes::ArrayOfDouble const & >(value_);
					}					
					Energistics::Etp::v12::Datatypes::ArrayOfDouble& get_ArrayOfDouble()  {					
						if (idx_ != 11) {						
							throw avro::Exception("Invalid type for union.");
						}						
						return boost::any_cast< Energistics::Etp::v12::Datatypes::ArrayOfDouble& >(value_);
					}					
					void set_ArrayOfDouble(const Energistics::Etp::v12::Datatypes::ArrayOfDouble& v) {					
						idx_ = 11;
						value_ = v;
					}					
					Energistics::Etp::v12::Datatypes::ArrayOfString const & get_ArrayOfString() const {					
						if (idx_ != 12) {						
							throw avro::Exception("Invalid type for union.");
						}						
						return boost::any_cast< Energistics::Etp::v12::Datatypes::ArrayOfString const & >(value_);
					}					
					Energistics::Etp::v12::Datatypes::ArrayOfString& get_ArrayOfString()  {					
						if (idx_ != 12) {						
							throw avro::Exception("Invalid type for union.");
						}						
						return boost::any_cast< Energistics::Etp::v12::Datatypes::ArrayOfString& >(value_);
					}					
					void set_ArrayOfString(const Energistics::Etp::v12::Datatypes::ArrayOfString& v) {					
						idx_ = 12;
						value_ = v;
					}					
					std::string const & get_bytes() const {					
						if (idx_ != 13) {						
							throw avro::Exception("Invalid type for union.");
						}						
						return boost::any_cast< std::string const & >(value_);
					}					
					std::string& get_bytes()  {					
						if (idx_ != 13) {						
							throw avro::Exception("Invalid type for union.");
						}						
						return boost::any_cast< std::string& >(value_);
					}					
					void set_bytes(const std::string& v) {					
						idx_ = 13;
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
					avro::encode(e, v.get_boolean());
					break;								
				case 2:				
					avro::encode(e, v.get_int());
					break;								
				case 3:				
					avro::encode(e, v.get_long());
					break;								
				case 4:				
					avro::encode(e, v.get_float());
					break;								
				case 5:				
					avro::encode(e, v.get_double());
					break;								
				case 6:				
					avro::encode(e, v.get_string());
					break;								
				case 7:				
					avro::encode(e, v.get_ArrayOfBoolean());
					break;								
				case 8:				
					avro::encode(e, v.get_ArrayOfInt());
					break;								
				case 9:				
					avro::encode(e, v.get_ArrayOfLong());
					break;								
				case 10:				
					avro::encode(e, v.get_ArrayOfFloat());
					break;								
				case 11:				
					avro::encode(e, v.get_ArrayOfDouble());
					break;								
				case 12:				
					avro::encode(e, v.get_ArrayOfString());
					break;								
				case 13:				
					avro::encode(e, v.get_bytes());
					break;								
			}			
		}		
		static void decode(Decoder& d, Energistics::Etp::v12::Datatypes::DataValueitem_t& v) {
		
			size_t n = d.decodeUnionIndex();
			if (n >= 14) { throw avro::Exception("Union index too big"); }
			switch (n) {			
				case 0:				
					{					
						d.decodeNull();
						v.set_null();
					}					
					break;								
				case 1:				
					{					
						bool vv;
						avro::decode(d, vv);
						v.set_boolean(vv);
					}					
					break;								
				case 2:				
					{					
						int32_t vv;
						avro::decode(d, vv);
						v.set_int(vv);
					}					
					break;								
				case 3:				
					{					
						int64_t vv;
						avro::decode(d, vv);
						v.set_long(vv);
					}					
					break;								
				case 4:				
					{					
						float vv;
						avro::decode(d, vv);
						v.set_float(vv);
					}					
					break;								
				case 5:				
					{					
						double vv;
						avro::decode(d, vv);
						v.set_double(vv);
					}					
					break;								
				case 6:				
					{					
						std::string vv;
						avro::decode(d, vv);
						v.set_string(vv);
					}					
					break;								
				case 7:				
					{					
						Energistics::Etp::v12::Datatypes::ArrayOfBoolean vv;
						avro::decode(d, vv);
						v.set_ArrayOfBoolean(vv);
					}					
					break;								
				case 8:				
					{					
						Energistics::Etp::v12::Datatypes::ArrayOfInt vv;
						avro::decode(d, vv);
						v.set_ArrayOfInt(vv);
					}					
					break;								
				case 9:				
					{					
						Energistics::Etp::v12::Datatypes::ArrayOfLong vv;
						avro::decode(d, vv);
						v.set_ArrayOfLong(vv);
					}					
					break;								
				case 10:				
					{					
						Energistics::Etp::v12::Datatypes::ArrayOfFloat vv;
						avro::decode(d, vv);
						v.set_ArrayOfFloat(vv);
					}					
					break;								
				case 11:				
					{					
						Energistics::Etp::v12::Datatypes::ArrayOfDouble vv;
						avro::decode(d, vv);
						v.set_ArrayOfDouble(vv);
					}					
					break;								
				case 12:				
					{					
						Energistics::Etp::v12::Datatypes::ArrayOfString vv;
						avro::decode(d, vv);
						v.set_ArrayOfString(vv);
					}					
					break;								
				case 13:				
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
				struct ErrorInfo{				
					std::string m_message;
					int32_t m_code;
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Datatypes::ErrorInfo> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Datatypes::ErrorInfo& v) {		
			avro::encode(e, v.m_message);
			avro::encode(e, v.m_code);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Datatypes::ErrorInfo& v) {		
			avro::decode(e, v.m_message);
			avro::decode(e, v.m_code);
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
					int64_t const & get_long() const {					
						if (idx_ != 1) {						
							throw avro::Exception("Invalid type for union.");
						}						
						return boost::any_cast< int64_t const & >(value_);
					}					
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
					double const & get_double() const {					
						if (idx_ != 2) {						
							throw avro::Exception("Invalid type for union.");
						}						
						return boost::any_cast< double const & >(value_);
					}					
					double& get_double()  {					
						if (idx_ != 2) {						
							throw avro::Exception("Invalid type for union.");
						}						
						return boost::any_cast< double& >(value_);
					}					
					void set_double(const double& v) {					
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
					avro::encode(e, v.get_long());
					break;								
				case 2:				
					avro::encode(e, v.get_double());
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
						int64_t vv;
						avro::decode(d, vv);
						v.set_long(vv);
					}					
					break;								
				case 2:				
					{					
						double vv;
						avro::decode(d, vv);
						v.set_double(vv);
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
				enum Protocol {				
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
					DataArrayQuery=19,
					DataArrayNotificationQuery=20,
					ChannelSubscribe=21,
					ChannelDataLoad=22,
					ChannelView=23,
					Dataspace=24
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Datatypes::Protocol> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Datatypes::Protocol& v) {		
			e.encodeEnum(v);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Datatypes::Protocol& v) {		
			v = static_cast<Energistics::Etp::v12::Datatypes::Protocol>(e.decodeEnum());
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Datatypes {			
				enum ProtocolCapabilityKind {				
					SimpleStreamer=0,
					MaxIndexCount=1,
					MinMessageInterval=2,
					MaxDataItems=3,
					MaxResponseCount=4,
					ChangeDetectionPeriod=5,
					ChangeNotificationRetentionPeriod=6,
					DeleteNotificationDetectionPeriod=7,
					TransactionTimeout=8,
					StreamingTimeoutPeriod=9,
					GrowingTimeoutPeriod=10,
					MaxDataObjectSize=11,
					MaxPartSize=12,
					MaxDataArraySize=13
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Datatypes::ProtocolCapabilityKind> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Datatypes::ProtocolCapabilityKind& v) {		
			e.encodeEnum(v);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Datatypes::ProtocolCapabilityKind& v) {		
			v = static_cast<Energistics::Etp::v12::Datatypes::ProtocolCapabilityKind>(e.decodeEnum());
		}		
	};	
}
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
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Datatypes::Uuid> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Datatypes::Uuid& v) {		
			avro::encode(e, v.m_array);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Datatypes::Uuid& v) {		
			avro::decode(e, v.m_array);
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
					Energistics::Etp::v12::Datatypes::Contact m_contactInformation;
					std::vector<std::string> m_supportedCompression;
					std::string m_supportedEncodings;
					std::vector<std::string> m_supportedFormats;
					std::vector<std::string> m_supportedObjects;
					std::vector<Energistics::Etp::v12::Datatypes::SupportedProtocol> m_supportedProtocols;
					std::map<std::string, Energistics::Etp::v12::Datatypes::DataValue> m_capabilities;
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Datatypes::ServerCapabilities> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Datatypes::ServerCapabilities& v) {		
			avro::encode(e, v.m_applicationName);
			avro::encode(e, v.m_applicationVersion);
			avro::encode(e, v.m_contactInformation);
			avro::encode(e, v.m_supportedCompression);
			avro::encode(e, v.m_supportedEncodings);
			avro::encode(e, v.m_supportedFormats);
			avro::encode(e, v.m_supportedObjects);
			avro::encode(e, v.m_supportedProtocols);
			avro::encode(e, v.m_capabilities);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Datatypes::ServerCapabilities& v) {		
			avro::decode(e, v.m_applicationName);
			avro::decode(e, v.m_applicationVersion);
			avro::decode(e, v.m_contactInformation);
			avro::decode(e, v.m_supportedCompression);
			avro::decode(e, v.m_supportedEncodings);
			avro::decode(e, v.m_supportedFormats);
			avro::decode(e, v.m_supportedObjects);
			avro::decode(e, v.m_supportedProtocols);
			avro::decode(e, v.m_capabilities);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Datatypes {			
				namespace ChannelData {				
					enum ChannelIndexKind {					
						Time=0,
						Depth=1
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Datatypes::ChannelData::ChannelIndexKind> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Datatypes::ChannelData::ChannelIndexKind& v) {		
			e.encodeEnum(v);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Datatypes::ChannelData::ChannelIndexKind& v) {		
			v = static_cast<Energistics::Etp::v12::Datatypes::ChannelData::ChannelIndexKind>(e.decodeEnum());
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Datatypes {			
				namespace ChannelData {				
					enum ChannelStatusKind {					
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
	template<> struct codec_traits<Energistics::Etp::v12::Datatypes::ChannelData::ChannelStatusKind> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Datatypes::ChannelData::ChannelStatusKind& v) {		
			e.encodeEnum(v);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Datatypes::ChannelData::ChannelStatusKind& v) {		
			v = static_cast<Energistics::Etp::v12::Datatypes::ChannelData::ChannelStatusKind>(e.decodeEnum());
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Datatypes {			
				namespace ChannelData {				
					struct ChannelSubscribeInfo{					
						int64_t m_channelId;
						Energistics::Etp::v12::Datatypes::IndexValue m_startIndex;
						bool m_dataChanges=false;
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Datatypes::ChannelData::ChannelSubscribeInfo> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Datatypes::ChannelData::ChannelSubscribeInfo& v) {		
			avro::encode(e, v.m_channelId);
			avro::encode(e, v.m_startIndex);
			avro::encode(e, v.m_dataChanges);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Datatypes::ChannelData::ChannelSubscribeInfo& v) {		
			avro::decode(e, v.m_channelId);
			avro::decode(e, v.m_startIndex);
			avro::decode(e, v.m_dataChanges);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Datatypes {			
				namespace ChannelData {				
					struct DataFrame{					
						std::vector<int64_t> m_indexes;
						std::vector<Energistics::Etp::v12::Datatypes::DataValue> m_data;
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Datatypes::ChannelData::DataFrame> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Datatypes::ChannelData::DataFrame& v) {		
			avro::encode(e, v.m_indexes);
			avro::encode(e, v.m_data);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Datatypes::ChannelData::DataFrame& v) {		
			avro::decode(e, v.m_indexes);
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
						int64_t m_channelId;
						std::vector<Energistics::Etp::v12::Datatypes::IndexValue> m_indexes;
						Energistics::Etp::v12::Datatypes::DataValue m_value;
						std::vector<Energistics::Etp::v12::Datatypes::DataAttribute> m_valueAttributes;
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Datatypes::ChannelData::DataItem> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Datatypes::ChannelData::DataItem& v) {		
			avro::encode(e, v.m_channelId);
			avro::encode(e, v.m_indexes);
			avro::encode(e, v.m_value);
			avro::encode(e, v.m_valueAttributes);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Datatypes::ChannelData::DataItem& v) {		
			avro::decode(e, v.m_channelId);
			avro::decode(e, v.m_indexes);
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
					enum IndexDirection {					
						Increasing=0,
						Decreasing=1
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Datatypes::ChannelData::IndexDirection> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Datatypes::ChannelData::IndexDirection& v) {		
			e.encodeEnum(v);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Datatypes::ChannelData::IndexDirection& v) {		
			v = static_cast<Energistics::Etp::v12::Datatypes::ChannelData::IndexDirection>(e.decodeEnum());
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Datatypes {			
				namespace ChannelData {				
					struct OpenChannelInfo{					
						std::string m_uri;
						int64_t m_id;
						Energistics::Etp::v12::Datatypes::IndexValue m_lastIndex;
						bool m_preferRealtime=false;
						bool m_dataChanges=false;
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Datatypes::ChannelData::OpenChannelInfo> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Datatypes::ChannelData::OpenChannelInfo& v) {		
			avro::encode(e, v.m_uri);
			avro::encode(e, v.m_id);
			avro::encode(e, v.m_lastIndex);
			avro::encode(e, v.m_preferRealtime);
			avro::encode(e, v.m_dataChanges);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Datatypes::ChannelData::OpenChannelInfo& v) {		
			avro::decode(e, v.m_uri);
			avro::decode(e, v.m_id);
			avro::decode(e, v.m_lastIndex);
			avro::decode(e, v.m_preferRealtime);
			avro::decode(e, v.m_dataChanges);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Datatypes {			
				namespace ChannelData {				
					enum Role {					
						producer=0,
						consumer=1
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Datatypes::ChannelData::Role> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Datatypes::ChannelData::Role& v) {		
			e.encodeEnum(v);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Datatypes::ChannelData::Role& v) {		
			v = static_cast<Energistics::Etp::v12::Datatypes::ChannelData::Role>(e.decodeEnum());
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Datatypes {			
				namespace DataArrayTypes {				
					struct DataArray{					
						std::vector<int64_t> m_dimensions;
						Energistics::Etp::v12::Datatypes::AnyArray m_data;
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Datatypes::DataArrayTypes::DataArray> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Datatypes::DataArrayTypes::DataArray& v) {		
			avro::encode(e, v.m_dimensions);
			avro::encode(e, v.m_data);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Datatypes::DataArrayTypes::DataArray& v) {		
			avro::decode(e, v.m_dimensions);
			avro::decode(e, v.m_data);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Datatypes {			
				namespace DataArrayTypes {				
					struct DataArrayIdentifier{					
						std::string m_uri;
						std::string m_pathInResource;
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Datatypes::DataArrayTypes::DataArrayIdentifier> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Datatypes::DataArrayTypes::DataArrayIdentifier& v) {		
			avro::encode(e, v.m_uri);
			avro::encode(e, v.m_pathInResource);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Datatypes::DataArrayTypes::DataArrayIdentifier& v) {		
			avro::decode(e, v.m_uri);
			avro::decode(e, v.m_pathInResource);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Datatypes {			
				namespace DataArrayTypes {				
					struct DataArrayMetadata{					
						std::vector<int64_t> m_dimensions;
						Energistics::Etp::v12::Datatypes::AnyArrayType m_arrayType;
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Datatypes::DataArrayTypes::DataArrayMetadata> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Datatypes::DataArrayTypes::DataArrayMetadata& v) {		
			avro::encode(e, v.m_dimensions);
			avro::encode(e, v.m_arrayType);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Datatypes::DataArrayTypes::DataArrayMetadata& v) {		
			avro::decode(e, v.m_dimensions);
			avro::decode(e, v.m_arrayType);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Datatypes {			
				namespace DataArrayTypes {				
					struct GetDataArraySlicesType{					
						std::string m_uri;
						std::string m_pathInResource;
						std::vector<int64_t> m_starts;
						std::vector<int64_t> m_counts;
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Datatypes::DataArrayTypes::GetDataArraySlicesType> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Datatypes::DataArrayTypes::GetDataArraySlicesType& v) {		
			avro::encode(e, v.m_uri);
			avro::encode(e, v.m_pathInResource);
			avro::encode(e, v.m_starts);
			avro::encode(e, v.m_counts);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Datatypes::DataArrayTypes::GetDataArraySlicesType& v) {		
			avro::decode(e, v.m_uri);
			avro::decode(e, v.m_pathInResource);
			avro::decode(e, v.m_starts);
			avro::decode(e, v.m_counts);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Datatypes {			
				namespace DataArrayTypes {				
					struct PutDataArraySlicesType{					
						std::string m_uri;
						std::string m_pathInResource;
						Energistics::Etp::v12::Datatypes::AnyArray m_data;
						std::vector<int64_t> m_dimensions;
						std::vector<int64_t> m_starts;
						std::vector<int64_t> m_counts;
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Datatypes::DataArrayTypes::PutDataArraySlicesType> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Datatypes::DataArrayTypes::PutDataArraySlicesType& v) {		
			avro::encode(e, v.m_uri);
			avro::encode(e, v.m_pathInResource);
			avro::encode(e, v.m_data);
			avro::encode(e, v.m_dimensions);
			avro::encode(e, v.m_starts);
			avro::encode(e, v.m_counts);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Datatypes::DataArrayTypes::PutDataArraySlicesType& v) {		
			avro::decode(e, v.m_uri);
			avro::decode(e, v.m_pathInResource);
			avro::decode(e, v.m_data);
			avro::decode(e, v.m_dimensions);
			avro::decode(e, v.m_starts);
			avro::decode(e, v.m_counts);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Datatypes {			
				namespace DataArrayTypes {				
					struct PutDataArraysType{					
						std::string m_uri;
						std::string m_pathInResource;
						Energistics::Etp::v12::Datatypes::AnyArray m_data;
						std::vector<int64_t> m_dimensions;
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Datatypes::DataArrayTypes::PutDataArraysType> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Datatypes::DataArrayTypes::PutDataArraysType& v) {		
			avro::encode(e, v.m_uri);
			avro::encode(e, v.m_pathInResource);
			avro::encode(e, v.m_data);
			avro::encode(e, v.m_dimensions);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Datatypes::DataArrayTypes::PutDataArraysType& v) {		
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
			namespace Datatypes {			
				namespace Object {				
					struct ContextInfo{					
						std::string m_uri;
						int32_t m_depth;
						std::vector<std::string> m_dataObjectTypes;
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Datatypes::Object::ContextInfo> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Datatypes::Object::ContextInfo& v) {		
			avro::encode(e, v.m_uri);
			avro::encode(e, v.m_depth);
			avro::encode(e, v.m_dataObjectTypes);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Datatypes::Object::ContextInfo& v) {		
			avro::decode(e, v.m_uri);
			avro::decode(e, v.m_depth);
			avro::decode(e, v.m_dataObjectTypes);
		}		
	};	
}
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
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Datatypes::Object::ContextScopeKind> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Datatypes::Object::ContextScopeKind& v) {		
			e.encodeEnum(v);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Datatypes::Object::ContextScopeKind& v) {		
			v = static_cast<Energistics::Etp::v12::Datatypes::Object::ContextScopeKind>(e.decodeEnum());
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Datatypes {			
				namespace Object {				
					struct DataspacelastChanged_t {
					private:					
						size_t idx_=0;
						boost::any value_;
										
					public:					
						size_t idx() const { return idx_; }
						bool is_null() const { return idx_==0; }
						void set_null() { idx_=0; value_ = boost::any(); }
						int64_t const & get_long() const {						
							if (idx_ != 1) {							
								throw avro::Exception("Invalid type for union.");
							}							
							return boost::any_cast< int64_t const & >(value_);
						}						
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
	template<> struct codec_traits<Energistics::Etp::v12::Datatypes::Object::DataspacelastChanged_t> {
	
		static void encode(Encoder& e, Energistics::Etp::v12::Datatypes::Object::DataspacelastChanged_t v) {
		
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
		static void decode(Decoder& d, Energistics::Etp::v12::Datatypes::Object::DataspacelastChanged_t& v) {
		
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
					struct Dataspace{					
						std::string m_uid;
						std::string m_path;
						Energistics::Etp::v12::Datatypes::Object::DataspacelastChanged_t m_lastChanged;
						std::map<std::string, std::string> m_customData;
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Datatypes::Object::Dataspace> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Datatypes::Object::Dataspace& v) {		
			avro::encode(e, v.m_uid);
			avro::encode(e, v.m_path);
			avro::encode(e, v.m_lastChanged);
			avro::encode(e, v.m_customData);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Datatypes::Object::Dataspace& v) {		
			avro::decode(e, v.m_uid);
			avro::decode(e, v.m_path);
			avro::decode(e, v.m_lastChanged);
			avro::decode(e, v.m_customData);
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
				namespace ChannelData {				
					struct ChannelRangeInfo{					
						std::vector<int64_t> m_channelIds;
						Energistics::Etp::v12::Datatypes::Object::IndexInterval m_interval;
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Datatypes::ChannelData::ChannelRangeInfo> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Datatypes::ChannelData::ChannelRangeInfo& v) {		
			avro::encode(e, v.m_channelIds);
			avro::encode(e, v.m_interval);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Datatypes::ChannelData::ChannelRangeInfo& v) {		
			avro::decode(e, v.m_channelIds);
			avro::decode(e, v.m_interval);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Datatypes {			
				namespace ChannelData {				
					struct IndexMetadataRecord{					
						Energistics::Etp::v12::Datatypes::ChannelData::ChannelIndexKind m_indexKind;
						Energistics::Etp::v12::Datatypes::Object::IndexInterval m_interval;
						Energistics::Etp::v12::Datatypes::ChannelData::IndexDirection m_direction;
						std::string m_name;
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Datatypes::ChannelData::IndexMetadataRecord> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Datatypes::ChannelData::IndexMetadataRecord& v) {		
			avro::encode(e, v.m_indexKind);
			avro::encode(e, v.m_interval);
			avro::encode(e, v.m_direction);
			avro::encode(e, v.m_name);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Datatypes::ChannelData::IndexMetadataRecord& v) {		
			avro::decode(e, v.m_indexKind);
			avro::decode(e, v.m_interval);
			avro::decode(e, v.m_direction);
			avro::decode(e, v.m_name);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Datatypes {			
				namespace ChannelData {				
					struct ChannelMetadataRecord{					
						std::string m_uri;
						int64_t m_id;
						std::vector<Energistics::Etp::v12::Datatypes::ChannelData::IndexMetadataRecord> m_indexes;
						std::string m_channelName;
						std::string m_dataType;
						std::string m_uom;
						std::string m_measureClass;
						Energistics::Etp::v12::Datatypes::ChannelData::ChannelStatusKind m_status;
						std::string m_source;
						std::vector<int32_t> m_axisVectorLengths;
						std::map<std::string, Energistics::Etp::v12::Datatypes::DataValue> m_customData;
						std::vector<Energistics::Etp::v12::Datatypes::AttributeMetadataRecord> m_attributeMetadata;
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Datatypes::ChannelData::ChannelMetadataRecord> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Datatypes::ChannelData::ChannelMetadataRecord& v) {		
			avro::encode(e, v.m_uri);
			avro::encode(e, v.m_id);
			avro::encode(e, v.m_indexes);
			avro::encode(e, v.m_channelName);
			avro::encode(e, v.m_dataType);
			avro::encode(e, v.m_uom);
			avro::encode(e, v.m_measureClass);
			avro::encode(e, v.m_status);
			avro::encode(e, v.m_source);
			avro::encode(e, v.m_axisVectorLengths);
			avro::encode(e, v.m_customData);
			avro::encode(e, v.m_attributeMetadata);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Datatypes::ChannelData::ChannelMetadataRecord& v) {		
			avro::decode(e, v.m_uri);
			avro::decode(e, v.m_id);
			avro::decode(e, v.m_indexes);
			avro::decode(e, v.m_channelName);
			avro::decode(e, v.m_dataType);
			avro::decode(e, v.m_uom);
			avro::decode(e, v.m_measureClass);
			avro::decode(e, v.m_status);
			avro::decode(e, v.m_source);
			avro::decode(e, v.m_axisVectorLengths);
			avro::decode(e, v.m_customData);
			avro::decode(e, v.m_attributeMetadata);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Datatypes {			
				namespace Object {				
					enum ObjectChangeKind {					
						insert=0,
						update=1,
						authorized=2
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Datatypes::Object::ObjectChangeKind> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Datatypes::Object::ObjectChangeKind& v) {		
			e.encodeEnum(v);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Datatypes::Object::ObjectChangeKind& v) {		
			v = static_cast<Energistics::Etp::v12::Datatypes::Object::ObjectChangeKind>(e.decodeEnum());
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
					struct ObjectPart{					
						std::string m_uid;
						std::string m_data;
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Datatypes::Object::ObjectPart> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Datatypes::Object::ObjectPart& v) {		
			avro::encode(e, v.m_uid);
			avro::encode(e, v.m_data);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Datatypes::Object::ObjectPart& v) {		
			avro::decode(e, v.m_uid);
			avro::decode(e, v.m_data);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Datatypes {			
				namespace Object {				
					struct PartsMetadataInfo{					
						std::string m_uri;
						Energistics::Etp::v12::Datatypes::ChannelData::ChannelIndexKind m_indexKind;
						std::string m_name;
						Energistics::Etp::v12::Datatypes::Object::IndexInterval m_indexInterval;
						std::map<std::string, Energistics::Etp::v12::Datatypes::DataValue> m_customData;
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Datatypes::Object::PartsMetadataInfo> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Datatypes::Object::PartsMetadataInfo& v) {		
			avro::encode(e, v.m_uri);
			avro::encode(e, v.m_indexKind);
			avro::encode(e, v.m_name);
			avro::encode(e, v.m_indexInterval);
			avro::encode(e, v.m_customData);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Datatypes::Object::PartsMetadataInfo& v) {		
			avro::decode(e, v.m_uri);
			avro::decode(e, v.m_indexKind);
			avro::decode(e, v.m_name);
			avro::decode(e, v.m_indexInterval);
			avro::decode(e, v.m_customData);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Datatypes {			
				namespace Object {				
					struct ResourcesourceCount_t {
					private:					
						size_t idx_=0;
						boost::any value_;
										
					public:					
						size_t idx() const { return idx_; }
						bool is_null() const { return idx_==0; }
						void set_null() { idx_=0; value_ = boost::any(); }
						int32_t const & get_int() const {						
							if (idx_ != 1) {							
								throw avro::Exception("Invalid type for union.");
							}							
							return boost::any_cast< int32_t const & >(value_);
						}						
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
	template<> struct codec_traits<Energistics::Etp::v12::Datatypes::Object::ResourcesourceCount_t> {
	
		static void encode(Encoder& e, Energistics::Etp::v12::Datatypes::Object::ResourcesourceCount_t v) {
		
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
		static void decode(Decoder& d, Energistics::Etp::v12::Datatypes::Object::ResourcesourceCount_t& v) {
		
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
					struct ResourcetargetCount_t {
					private:					
						size_t idx_=0;
						boost::any value_;
										
					public:					
						size_t idx() const { return idx_; }
						bool is_null() const { return idx_==0; }
						void set_null() { idx_=0; value_ = boost::any(); }
						int32_t const & get_int() const {						
							if (idx_ != 1) {							
								throw avro::Exception("Invalid type for union.");
							}							
							return boost::any_cast< int32_t const & >(value_);
						}						
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
	template<> struct codec_traits<Energistics::Etp::v12::Datatypes::Object::ResourcetargetCount_t> {
	
		static void encode(Encoder& e, Energistics::Etp::v12::Datatypes::Object::ResourcetargetCount_t v) {
		
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
		static void decode(Decoder& d, Energistics::Etp::v12::Datatypes::Object::ResourcetargetCount_t& v) {
		
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
					struct Resource{					
						std::string m_uri;
						std::vector<std::string> m_alternateUris;
						std::string m_dataObjectType;
						std::string m_name;
						Energistics::Etp::v12::Datatypes::Object::ResourcesourceCount_t m_sourceCount;
						Energistics::Etp::v12::Datatypes::Object::ResourcetargetCount_t m_targetCount;
						int64_t m_lastChanged;
						std::map<std::string, std::string> m_customData;
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Datatypes::Object::Resource> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Datatypes::Object::Resource& v) {		
			avro::encode(e, v.m_uri);
			avro::encode(e, v.m_alternateUris);
			avro::encode(e, v.m_dataObjectType);
			avro::encode(e, v.m_name);
			avro::encode(e, v.m_sourceCount);
			avro::encode(e, v.m_targetCount);
			avro::encode(e, v.m_lastChanged);
			avro::encode(e, v.m_customData);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Datatypes::Object::Resource& v) {		
			avro::decode(e, v.m_uri);
			avro::decode(e, v.m_alternateUris);
			avro::decode(e, v.m_dataObjectType);
			avro::decode(e, v.m_name);
			avro::decode(e, v.m_sourceCount);
			avro::decode(e, v.m_targetCount);
			avro::decode(e, v.m_lastChanged);
			avro::decode(e, v.m_customData);
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
						std::string m_format;
						std::string m_blobId;
						std::string m_data;
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Datatypes::Object::DataObject> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Datatypes::Object::DataObject& v) {		
			avro::encode(e, v.m_resource);
			avro::encode(e, v.m_format);
			avro::encode(e, v.m_blobId);
			avro::encode(e, v.m_data);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Datatypes::Object::DataObject& v) {		
			avro::decode(e, v.m_resource);
			avro::decode(e, v.m_format);
			avro::decode(e, v.m_blobId);
			avro::decode(e, v.m_data);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Datatypes {			
				namespace Object {				
					struct OptionalDataObject{					
						Energistics::Etp::v12::Datatypes::Object::Resource m_resource;
						std::string m_format;
						std::string m_blobId;
						std::string m_data;
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Datatypes::Object::OptionalDataObject> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Datatypes::Object::OptionalDataObject& v) {		
			avro::encode(e, v.m_resource);
			avro::encode(e, v.m_format);
			avro::encode(e, v.m_blobId);
			avro::encode(e, v.m_data);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Datatypes::Object::OptionalDataObject& v) {		
			avro::decode(e, v.m_resource);
			avro::decode(e, v.m_format);
			avro::decode(e, v.m_blobId);
			avro::decode(e, v.m_data);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Datatypes {			
				namespace Object {				
					struct ObjectChange{					
						Energistics::Etp::v12::Datatypes::Object::ObjectChangeKind m_changeKind;
						int64_t m_changeTime;
						Energistics::Etp::v12::Datatypes::Object::OptionalDataObject m_dataObject;
					};					
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
			namespace Datatypes {			
				namespace Object {				
					struct SubscriptionInfo{					
						Energistics::Etp::v12::Datatypes::Object::ContextInfo m_context;
						Energistics::Etp::v12::Datatypes::Object::ContextScopeKind m_scope;
						Energistics::Etp::v12::Datatypes::Uuid m_requestUuid;
						int64_t m_startTime;
						bool m_includeObjectData=false;
						std::string m_format;
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Datatypes::Object::SubscriptionInfo> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Datatypes::Object::SubscriptionInfo& v) {		
			avro::encode(e, v.m_context);
			avro::encode(e, v.m_scope);
			avro::encode(e, v.m_requestUuid);
			avro::encode(e, v.m_startTime);
			avro::encode(e, v.m_includeObjectData);
			avro::encode(e, v.m_format);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Datatypes::Object::SubscriptionInfo& v) {		
			avro::decode(e, v.m_context);
			avro::decode(e, v.m_scope);
			avro::decode(e, v.m_requestUuid);
			avro::decode(e, v.m_startTime);
			avro::decode(e, v.m_includeObjectData);
			avro::decode(e, v.m_format);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Datatypes {			
				namespace Object {				
					struct SupportedTypeobjectCount_t {
					private:					
						size_t idx_=0;
						boost::any value_;
										
					public:					
						size_t idx() const { return idx_; }
						bool is_null() const { return idx_==0; }
						void set_null() { idx_=0; value_ = boost::any(); }
						int32_t const & get_int() const {						
							if (idx_ != 1) {							
								throw avro::Exception("Invalid type for union.");
							}							
							return boost::any_cast< int32_t const & >(value_);
						}						
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
	template<> struct codec_traits<Energistics::Etp::v12::Datatypes::Object::SupportedTypeobjectCount_t> {
	
		static void encode(Encoder& e, Energistics::Etp::v12::Datatypes::Object::SupportedTypeobjectCount_t v) {
		
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
		static void decode(Decoder& d, Energistics::Etp::v12::Datatypes::Object::SupportedTypeobjectCount_t& v) {
		
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
					struct SupportedType{					
						std::string m_dataObjectType;
						Energistics::Etp::v12::Datatypes::Object::SupportedTypeobjectCount_t m_objectCount;
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Datatypes::Object::SupportedType> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Datatypes::Object::SupportedType& v) {		
			avro::encode(e, v.m_dataObjectType);
			avro::encode(e, v.m_objectCount);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Datatypes::Object::SupportedType& v) {		
			avro::decode(e, v.m_dataObjectType);
			avro::decode(e, v.m_objectCount);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace PrivateProtocols {			
				namespace WitsmlSoap {				
					struct WMLS_AddToStore{					
						std::string m_WMLtypeIn;
						std::string m_XMLin;
						std::string m_OptionsIn;
						std::string m_CapabilitiesIn;
						static const int messageTypeId=1;
						static const int protocolId=Energistics::Etp::v12::Datatypes::WitsmlSoap;
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::PrivateProtocols::WitsmlSoap::WMLS_AddToStore> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::PrivateProtocols::WitsmlSoap::WMLS_AddToStore& v) {		
			avro::encode(e, v.m_WMLtypeIn);
			avro::encode(e, v.m_XMLin);
			avro::encode(e, v.m_OptionsIn);
			avro::encode(e, v.m_CapabilitiesIn);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::PrivateProtocols::WitsmlSoap::WMLS_AddToStore& v) {		
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
			namespace PrivateProtocols {			
				namespace WitsmlSoap {				
					struct WMLS_AddToStoreResponse{					
						int32_t m_Result;
						std::string m_SuppMsgOut;
						static const int messageTypeId=2;
						static const int protocolId=Energistics::Etp::v12::Datatypes::WitsmlSoap;
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::PrivateProtocols::WitsmlSoap::WMLS_AddToStoreResponse> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::PrivateProtocols::WitsmlSoap::WMLS_AddToStoreResponse& v) {		
			avro::encode(e, v.m_Result);
			avro::encode(e, v.m_SuppMsgOut);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::PrivateProtocols::WitsmlSoap::WMLS_AddToStoreResponse& v) {		
			avro::decode(e, v.m_Result);
			avro::decode(e, v.m_SuppMsgOut);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace PrivateProtocols {			
				namespace WitsmlSoap {				
					struct WMLS_DeleteFromStore{					
						std::string m_WMLtypeIn;
						std::string m_XMLin;
						std::string m_OptionsIn;
						std::string m_CapabilitiesIn;
						static const int messageTypeId=3;
						static const int protocolId=Energistics::Etp::v12::Datatypes::WitsmlSoap;
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::PrivateProtocols::WitsmlSoap::WMLS_DeleteFromStore> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::PrivateProtocols::WitsmlSoap::WMLS_DeleteFromStore& v) {		
			avro::encode(e, v.m_WMLtypeIn);
			avro::encode(e, v.m_XMLin);
			avro::encode(e, v.m_OptionsIn);
			avro::encode(e, v.m_CapabilitiesIn);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::PrivateProtocols::WitsmlSoap::WMLS_DeleteFromStore& v) {		
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
			namespace PrivateProtocols {			
				namespace WitsmlSoap {				
					struct WMLS_DeleteFromStoreResponse{					
						int32_t m_Result;
						std::string m_SuppMsgOut;
						static const int messageTypeId=4;
						static const int protocolId=Energistics::Etp::v12::Datatypes::WitsmlSoap;
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::PrivateProtocols::WitsmlSoap::WMLS_DeleteFromStoreResponse> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::PrivateProtocols::WitsmlSoap::WMLS_DeleteFromStoreResponse& v) {		
			avro::encode(e, v.m_Result);
			avro::encode(e, v.m_SuppMsgOut);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::PrivateProtocols::WitsmlSoap::WMLS_DeleteFromStoreResponse& v) {		
			avro::decode(e, v.m_Result);
			avro::decode(e, v.m_SuppMsgOut);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace PrivateProtocols {			
				namespace WitsmlSoap {				
					struct WMLS_GetBaseMsg{					
						int32_t m_ReturnValueIn;
						static const int messageTypeId=5;
						static const int protocolId=Energistics::Etp::v12::Datatypes::WitsmlSoap;
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::PrivateProtocols::WitsmlSoap::WMLS_GetBaseMsg> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::PrivateProtocols::WitsmlSoap::WMLS_GetBaseMsg& v) {		
			avro::encode(e, v.m_ReturnValueIn);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::PrivateProtocols::WitsmlSoap::WMLS_GetBaseMsg& v) {		
			avro::decode(e, v.m_ReturnValueIn);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace PrivateProtocols {			
				namespace WitsmlSoap {				
					struct WMLS_GetBaseMsgResponse{					
						std::string m_Result;
						static const int messageTypeId=6;
						static const int protocolId=Energistics::Etp::v12::Datatypes::WitsmlSoap;
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::PrivateProtocols::WitsmlSoap::WMLS_GetBaseMsgResponse> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::PrivateProtocols::WitsmlSoap::WMLS_GetBaseMsgResponse& v) {		
			avro::encode(e, v.m_Result);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::PrivateProtocols::WitsmlSoap::WMLS_GetBaseMsgResponse& v) {		
			avro::decode(e, v.m_Result);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace PrivateProtocols {			
				namespace WitsmlSoap {				
					struct WMLS_GetCap{					
						std::string m_OptionsIn;
						static const int messageTypeId=7;
						static const int protocolId=Energistics::Etp::v12::Datatypes::WitsmlSoap;
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::PrivateProtocols::WitsmlSoap::WMLS_GetCap> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::PrivateProtocols::WitsmlSoap::WMLS_GetCap& v) {		
			avro::encode(e, v.m_OptionsIn);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::PrivateProtocols::WitsmlSoap::WMLS_GetCap& v) {		
			avro::decode(e, v.m_OptionsIn);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace PrivateProtocols {			
				namespace WitsmlSoap {				
					struct WMLS_GetCapResponse{					
						int32_t m_Result;
						std::string m_CapabilitiesOut;
						std::string m_SuppMsgOut;
						static const int messageTypeId=8;
						static const int protocolId=Energistics::Etp::v12::Datatypes::WitsmlSoap;
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::PrivateProtocols::WitsmlSoap::WMLS_GetCapResponse> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::PrivateProtocols::WitsmlSoap::WMLS_GetCapResponse& v) {		
			avro::encode(e, v.m_Result);
			avro::encode(e, v.m_CapabilitiesOut);
			avro::encode(e, v.m_SuppMsgOut);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::PrivateProtocols::WitsmlSoap::WMLS_GetCapResponse& v) {		
			avro::decode(e, v.m_Result);
			avro::decode(e, v.m_CapabilitiesOut);
			avro::decode(e, v.m_SuppMsgOut);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace PrivateProtocols {			
				namespace WitsmlSoap {				
					struct WMLS_GetFromStore{					
						std::string m_WMLtypeIn;
						std::string m_XMLin;
						std::string m_OptionsIn;
						std::string m_CapabilitiesIn;
						static const int messageTypeId=9;
						static const int protocolId=Energistics::Etp::v12::Datatypes::WitsmlSoap;
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::PrivateProtocols::WitsmlSoap::WMLS_GetFromStore> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::PrivateProtocols::WitsmlSoap::WMLS_GetFromStore& v) {		
			avro::encode(e, v.m_WMLtypeIn);
			avro::encode(e, v.m_XMLin);
			avro::encode(e, v.m_OptionsIn);
			avro::encode(e, v.m_CapabilitiesIn);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::PrivateProtocols::WitsmlSoap::WMLS_GetFromStore& v) {		
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
			namespace PrivateProtocols {			
				namespace WitsmlSoap {				
					struct WMLS_GetFromStoreResponse{					
						int32_t m_Result;
						std::string m_XMLout;
						std::string m_SuppMsgOut;
						static const int messageTypeId=10;
						static const int protocolId=Energistics::Etp::v12::Datatypes::WitsmlSoap;
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::PrivateProtocols::WitsmlSoap::WMLS_GetFromStoreResponse> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::PrivateProtocols::WitsmlSoap::WMLS_GetFromStoreResponse& v) {		
			avro::encode(e, v.m_Result);
			avro::encode(e, v.m_XMLout);
			avro::encode(e, v.m_SuppMsgOut);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::PrivateProtocols::WitsmlSoap::WMLS_GetFromStoreResponse& v) {		
			avro::decode(e, v.m_Result);
			avro::decode(e, v.m_XMLout);
			avro::decode(e, v.m_SuppMsgOut);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace PrivateProtocols {			
				namespace WitsmlSoap {				
					struct WMLS_GetVersion{					
						static const int messageTypeId=11;
						static const int protocolId=Energistics::Etp::v12::Datatypes::WitsmlSoap;
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::PrivateProtocols::WitsmlSoap::WMLS_GetVersion> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::PrivateProtocols::WitsmlSoap::WMLS_GetVersion& v) {		
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::PrivateProtocols::WitsmlSoap::WMLS_GetVersion& v) {		
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace PrivateProtocols {			
				namespace WitsmlSoap {				
					struct WMLS_GetVersionResponse{					
						std::string m_Result;
						static const int messageTypeId=12;
						static const int protocolId=Energistics::Etp::v12::Datatypes::WitsmlSoap;
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::PrivateProtocols::WitsmlSoap::WMLS_GetVersionResponse> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::PrivateProtocols::WitsmlSoap::WMLS_GetVersionResponse& v) {		
			avro::encode(e, v.m_Result);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::PrivateProtocols::WitsmlSoap::WMLS_GetVersionResponse& v) {		
			avro::decode(e, v.m_Result);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace PrivateProtocols {			
				namespace WitsmlSoap {				
					struct WMLS_UpdateInStore{					
						std::string m_WMLtypeIn;
						std::string m_XMLin;
						std::string m_OptionsIn;
						std::string m_CapabilitiesIn;
						static const int messageTypeId=13;
						static const int protocolId=Energistics::Etp::v12::Datatypes::WitsmlSoap;
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::PrivateProtocols::WitsmlSoap::WMLS_UpdateInStore> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::PrivateProtocols::WitsmlSoap::WMLS_UpdateInStore& v) {		
			avro::encode(e, v.m_WMLtypeIn);
			avro::encode(e, v.m_XMLin);
			avro::encode(e, v.m_OptionsIn);
			avro::encode(e, v.m_CapabilitiesIn);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::PrivateProtocols::WitsmlSoap::WMLS_UpdateInStore& v) {		
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
			namespace PrivateProtocols {			
				namespace WitsmlSoap {				
					struct WMLS_UpdateInStoreResponse{					
						int32_t m_Result;
						std::string m_SuppMsgOut;
						static const int messageTypeId=14;
						static const int protocolId=Energistics::Etp::v12::Datatypes::WitsmlSoap;
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::PrivateProtocols::WitsmlSoap::WMLS_UpdateInStoreResponse> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::PrivateProtocols::WitsmlSoap::WMLS_UpdateInStoreResponse& v) {		
			avro::encode(e, v.m_Result);
			avro::encode(e, v.m_SuppMsgOut);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::PrivateProtocols::WitsmlSoap::WMLS_UpdateInStoreResponse& v) {		
			avro::decode(e, v.m_Result);
			avro::decode(e, v.m_SuppMsgOut);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace ChannelDataLoad {				
					struct ChannelClosed{					
						std::map<std::string, int64_t> m_id;
						static const int messageTypeId=7;
						static const int protocolId=Energistics::Etp::v12::Datatypes::ChannelDataLoad;
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::ChannelDataLoad::ChannelClosed> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::ChannelDataLoad::ChannelClosed& v) {		
			avro::encode(e, v.m_id);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::ChannelDataLoad::ChannelClosed& v) {		
			avro::decode(e, v.m_id);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace ChannelDataLoad {				
					struct CloseChannel{					
						std::map<std::string, int64_t> m_id;
						static const int messageTypeId=3;
						static const int protocolId=Energistics::Etp::v12::Datatypes::ChannelDataLoad;
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::ChannelDataLoad::CloseChannel> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::ChannelDataLoad::CloseChannel& v) {		
			avro::encode(e, v.m_id);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::ChannelDataLoad::CloseChannel& v) {		
			avro::decode(e, v.m_id);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace ChannelDataLoad {				
					struct OpenChannelsResponse{					
						std::map<std::string, Energistics::Etp::v12::Datatypes::ChannelData::OpenChannelInfo> m_channels;
						static const int messageTypeId=2;
						static const int protocolId=Energistics::Etp::v12::Datatypes::ChannelDataLoad;
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::ChannelDataLoad::OpenChannelsResponse> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::ChannelDataLoad::OpenChannelsResponse& v) {		
			avro::encode(e, v.m_channels);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::ChannelDataLoad::OpenChannelsResponse& v) {		
			avro::decode(e, v.m_channels);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace ChannelDataLoad {				
					struct OpenChannels{					
						std::map<std::string, Energistics::Etp::v12::Datatypes::ChannelData::ChannelMetadataRecord> m_channels;
						static const int messageTypeId=1;
						static const int protocolId=Energistics::Etp::v12::Datatypes::ChannelDataLoad;
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::ChannelDataLoad::OpenChannels> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::ChannelDataLoad::OpenChannels& v) {		
			avro::encode(e, v.m_channels);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::ChannelDataLoad::OpenChannels& v) {		
			avro::decode(e, v.m_channels);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace ChannelDataLoad {				
					struct RealtimeData{					
						std::vector<Energistics::Etp::v12::Datatypes::ChannelData::DataItem> m_data;
						static const int messageTypeId=4;
						static const int protocolId=Energistics::Etp::v12::Datatypes::ChannelDataLoad;
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::ChannelDataLoad::RealtimeData> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::ChannelDataLoad::RealtimeData& v) {		
			avro::encode(e, v.m_data);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::ChannelDataLoad::RealtimeData& v) {		
			avro::decode(e, v.m_data);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace ChannelDataLoad {				
					struct ReplaceRange{					
						Energistics::Etp::v12::Datatypes::Object::IndexInterval m_changedInterval;
						std::vector<int64_t> m_channelIds;
						std::vector<Energistics::Etp::v12::Datatypes::ChannelData::DataItem> m_data;
						static const int messageTypeId=6;
						static const int protocolId=Energistics::Etp::v12::Datatypes::ChannelDataLoad;
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::ChannelDataLoad::ReplaceRange> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::ChannelDataLoad::ReplaceRange& v) {		
			avro::encode(e, v.m_changedInterval);
			avro::encode(e, v.m_channelIds);
			avro::encode(e, v.m_data);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::ChannelDataLoad::ReplaceRange& v) {		
			avro::decode(e, v.m_changedInterval);
			avro::decode(e, v.m_channelIds);
			avro::decode(e, v.m_data);
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
						static const int messageTypeId=2;
						static const int protocolId=Energistics::Etp::v12::Datatypes::ChannelStreaming;
					};					
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
					struct ChannelMetadata{					
						std::vector<Energistics::Etp::v12::Datatypes::ChannelData::ChannelMetadataRecord> m_channels;
						static const int messageTypeId=1;
						static const int protocolId=Energistics::Etp::v12::Datatypes::ChannelStreaming;
					};					
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
					struct StartStreaming{					
						static const int messageTypeId=3;
						static const int protocolId=Energistics::Etp::v12::Datatypes::ChannelStreaming;
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::ChannelStreaming::StartStreaming> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::ChannelStreaming::StartStreaming& v) {		
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::ChannelStreaming::StartStreaming& v) {		
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace ChannelStreaming {				
					struct StopStreaming{					
						static const int messageTypeId=4;
						static const int protocolId=Energistics::Etp::v12::Datatypes::ChannelStreaming;
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::ChannelStreaming::StopStreaming> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::ChannelStreaming::StopStreaming& v) {		
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::ChannelStreaming::StopStreaming& v) {		
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace ChannelSubscribe {				
					struct CancelGetRanges{					
						Energistics::Etp::v12::Datatypes::Uuid m_requestUuid;
						static const int messageTypeId=11;
						static const int protocolId=Energistics::Etp::v12::Datatypes::ChannelSubscribe;
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::ChannelSubscribe::CancelGetRanges> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::ChannelSubscribe::CancelGetRanges& v) {		
			avro::encode(e, v.m_requestUuid);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::ChannelSubscribe::CancelGetRanges& v) {		
			avro::decode(e, v.m_requestUuid);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace ChannelSubscribe {				
					struct GetChannelMetadata{					
						std::map<std::string, std::string> m_uris;
						static const int messageTypeId=1;
						static const int protocolId=Energistics::Etp::v12::Datatypes::ChannelSubscribe;
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::ChannelSubscribe::GetChannelMetadata> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::ChannelSubscribe::GetChannelMetadata& v) {		
			avro::encode(e, v.m_uris);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::ChannelSubscribe::GetChannelMetadata& v) {		
			avro::decode(e, v.m_uris);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace ChannelSubscribe {				
					struct GetChannelMetadataResponse{					
						std::map<std::string, Energistics::Etp::v12::Datatypes::ChannelData::ChannelMetadataRecord> m_metadata;
						static const int messageTypeId=2;
						static const int protocolId=Energistics::Etp::v12::Datatypes::ChannelSubscribe;
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::ChannelSubscribe::GetChannelMetadataResponse> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::ChannelSubscribe::GetChannelMetadataResponse& v) {		
			avro::encode(e, v.m_metadata);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::ChannelSubscribe::GetChannelMetadataResponse& v) {		
			avro::decode(e, v.m_metadata);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace ChannelSubscribe {				
					struct GetRanges{					
						Energistics::Etp::v12::Datatypes::Uuid m_requestUuid;
						std::vector<Energistics::Etp::v12::Datatypes::ChannelData::ChannelRangeInfo> m_channelRanges;
						static const int messageTypeId=9;
						static const int protocolId=Energistics::Etp::v12::Datatypes::ChannelSubscribe;
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::ChannelSubscribe::GetRanges> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::ChannelSubscribe::GetRanges& v) {		
			avro::encode(e, v.m_requestUuid);
			avro::encode(e, v.m_channelRanges);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::ChannelSubscribe::GetRanges& v) {		
			avro::decode(e, v.m_requestUuid);
			avro::decode(e, v.m_channelRanges);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace ChannelSubscribe {				
					struct GetRangesResponse{					
						std::vector<Energistics::Etp::v12::Datatypes::ChannelData::DataItem> m_data;
						static const int messageTypeId=10;
						static const int protocolId=Energistics::Etp::v12::Datatypes::ChannelSubscribe;
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::ChannelSubscribe::GetRangesResponse> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::ChannelSubscribe::GetRangesResponse& v) {		
			avro::encode(e, v.m_data);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::ChannelSubscribe::GetRangesResponse& v) {		
			avro::decode(e, v.m_data);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace ChannelSubscribe {				
					struct RealtimeData{					
						std::vector<Energistics::Etp::v12::Datatypes::ChannelData::DataItem> m_data;
						static const int messageTypeId=4;
						static const int protocolId=Energistics::Etp::v12::Datatypes::ChannelSubscribe;
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::ChannelSubscribe::RealtimeData> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::ChannelSubscribe::RealtimeData& v) {		
			avro::encode(e, v.m_data);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::ChannelSubscribe::RealtimeData& v) {		
			avro::decode(e, v.m_data);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace ChannelSubscribe {				
					struct ReplaceRange{					
						std::vector<int64_t> m_channelIds;
						Energistics::Etp::v12::Datatypes::Object::IndexInterval m_changedInterval;
						std::vector<Energistics::Etp::v12::Datatypes::ChannelData::DataItem> m_data;
						static const int messageTypeId=6;
						static const int protocolId=Energistics::Etp::v12::Datatypes::ChannelSubscribe;
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::ChannelSubscribe::ReplaceRange> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::ChannelSubscribe::ReplaceRange& v) {		
			avro::encode(e, v.m_channelIds);
			avro::encode(e, v.m_changedInterval);
			avro::encode(e, v.m_data);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::ChannelSubscribe::ReplaceRange& v) {		
			avro::decode(e, v.m_channelIds);
			avro::decode(e, v.m_changedInterval);
			avro::decode(e, v.m_data);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace ChannelSubscribe {				
					struct SubscribeChannels{					
						std::map<std::string, Energistics::Etp::v12::Datatypes::ChannelData::ChannelSubscribeInfo> m_channels;
						static const int messageTypeId=3;
						static const int protocolId=Energistics::Etp::v12::Datatypes::ChannelSubscribe;
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::ChannelSubscribe::SubscribeChannels> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::ChannelSubscribe::SubscribeChannels& v) {		
			avro::encode(e, v.m_channels);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::ChannelSubscribe::SubscribeChannels& v) {		
			avro::decode(e, v.m_channels);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace ChannelSubscribe {				
					struct SubscriptionsStopped{					
						std::map<std::string, int64_t> m_channelIds;
						static const int messageTypeId=8;
						static const int protocolId=Energistics::Etp::v12::Datatypes::ChannelSubscribe;
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::ChannelSubscribe::SubscriptionsStopped> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::ChannelSubscribe::SubscriptionsStopped& v) {		
			avro::encode(e, v.m_channelIds);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::ChannelSubscribe::SubscriptionsStopped& v) {		
			avro::decode(e, v.m_channelIds);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace ChannelSubscribe {				
					struct UnsubscribeChannels{					
						std::map<std::string, int64_t> m_channelIds;
						static const int messageTypeId=7;
						static const int protocolId=Energistics::Etp::v12::Datatypes::ChannelSubscribe;
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::ChannelSubscribe::UnsubscribeChannels> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::ChannelSubscribe::UnsubscribeChannels& v) {		
			avro::encode(e, v.m_channelIds);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::ChannelSubscribe::UnsubscribeChannels& v) {		
			avro::decode(e, v.m_channelIds);
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
						int protocolId;
					};					
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
						Energistics::Etp::v12::Datatypes::Uuid m_serverInstanceId;
						std::vector<Energistics::Etp::v12::Datatypes::SupportedProtocol> m_supportedProtocols;
						std::vector<std::string> m_supportedObjects;
						std::string m_supportedCompression;
						std::vector<std::string> m_supportedFormats;
						std::map<std::string, Energistics::Etp::v12::Datatypes::DataValue> m_capabilities;
						static const int messageTypeId=2;
						static const int protocolId=Energistics::Etp::v12::Datatypes::Core;
					};					
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
			avro::encode(e, v.m_serverInstanceId);
			avro::encode(e, v.m_supportedProtocols);
			avro::encode(e, v.m_supportedObjects);
			avro::encode(e, v.m_supportedCompression);
			avro::encode(e, v.m_supportedFormats);
			avro::encode(e, v.m_capabilities);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::Core::OpenSession& v) {		
			avro::decode(e, v.m_applicationName);
			avro::decode(e, v.m_applicationVersion);
			avro::decode(e, v.m_serverInstanceId);
			avro::decode(e, v.m_supportedProtocols);
			avro::decode(e, v.m_supportedObjects);
			avro::decode(e, v.m_supportedCompression);
			avro::decode(e, v.m_supportedFormats);
			avro::decode(e, v.m_capabilities);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace Core {				
					struct ProtocolExceptionerror_t {
					private:					
						size_t idx_=0;
						boost::any value_;
										
					public:					
						size_t idx() const { return idx_; }
						bool is_null() const { return idx_==0; }
						void set_null() { idx_=0; value_ = boost::any(); }
						Energistics::Etp::v12::Datatypes::ErrorInfo const & get_ErrorInfo() const {						
							if (idx_ != 1) {							
								throw avro::Exception("Invalid type for union.");
							}							
							return boost::any_cast< Energistics::Etp::v12::Datatypes::ErrorInfo const & >(value_);
						}						
						Energistics::Etp::v12::Datatypes::ErrorInfo& get_ErrorInfo()  {						
							if (idx_ != 1) {							
								throw avro::Exception("Invalid type for union.");
							}							
							return boost::any_cast< Energistics::Etp::v12::Datatypes::ErrorInfo& >(value_);
						}						
						void set_ErrorInfo(const Energistics::Etp::v12::Datatypes::ErrorInfo& v) {						
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
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::Core::ProtocolExceptionerror_t> {
	
		static void encode(Encoder& e, Energistics::Etp::v12::Protocol::Core::ProtocolExceptionerror_t v) {
		
			e.encodeUnionIndex(v.idx());
			switch (v.idx()) {			
				case 0:				
					e.encodeNull();
					break;								
				case 1:				
					avro::encode(e, v.get_ErrorInfo());
					break;								
			}			
		}		
		static void decode(Decoder& d, Energistics::Etp::v12::Protocol::Core::ProtocolExceptionerror_t& v) {
		
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
						Energistics::Etp::v12::Datatypes::ErrorInfo vv;
						avro::decode(d, vv);
						v.set_ErrorInfo(vv);
					}					
					break;								
			}			
		}		
	};	
}

namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace Core {				
					struct ProtocolException{					
						Energistics::Etp::v12::Protocol::Core::ProtocolExceptionerror_t m_error;
						std::map<std::string, Energistics::Etp::v12::Datatypes::ErrorInfo> m_errors;
						static const int messageTypeId=1000;
						static const int protocolId=Energistics::Etp::v12::Datatypes::Core;
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::Core::ProtocolException> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::Core::ProtocolException& v) {		
			avro::encode(e, v.m_error);
			avro::encode(e, v.m_errors);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::Core::ProtocolException& v) {		
			avro::decode(e, v.m_error);
			avro::decode(e, v.m_errors);
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
						Energistics::Etp::v12::Datatypes::Uuid m_clientInstanceId;
						std::vector<Energistics::Etp::v12::Datatypes::SupportedProtocol> m_requestedProtocols;
						std::vector<std::string> m_supportedObjects;
						std::string m_supportedCompression;
						std::vector<std::string> m_supportedFormats;
						std::map<std::string, Energistics::Etp::v12::Datatypes::DataValue> m_capabilities;
						static const int messageTypeId=1;
						static const int protocolId=Energistics::Etp::v12::Datatypes::Core;
					};					
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
			avro::encode(e, v.m_clientInstanceId);
			avro::encode(e, v.m_requestedProtocols);
			avro::encode(e, v.m_supportedObjects);
			avro::encode(e, v.m_supportedCompression);
			avro::encode(e, v.m_supportedFormats);
			avro::encode(e, v.m_capabilities);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::Core::RequestSession& v) {		
			avro::decode(e, v.m_applicationName);
			avro::decode(e, v.m_applicationVersion);
			avro::decode(e, v.m_clientInstanceId);
			avro::decode(e, v.m_requestedProtocols);
			avro::decode(e, v.m_supportedObjects);
			avro::decode(e, v.m_supportedCompression);
			avro::decode(e, v.m_supportedFormats);
			avro::decode(e, v.m_capabilities);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace DataArray {				
					struct GetDataArrayMetadata{					
						std::map<std::string, Energistics::Etp::v12::Datatypes::DataArrayTypes::DataArrayIdentifier> m_dataArrays;
						static const int messageTypeId=6;
						static const int protocolId=Energistics::Etp::v12::Datatypes::DataArray;
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::DataArray::GetDataArrayMetadata> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::DataArray::GetDataArrayMetadata& v) {		
			avro::encode(e, v.m_dataArrays);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::DataArray::GetDataArrayMetadata& v) {		
			avro::decode(e, v.m_dataArrays);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace DataArray {				
					struct GetDataArrayMetadataResponse{					
						std::map<std::string, Energistics::Etp::v12::Datatypes::DataArrayTypes::DataArrayMetadata> m_arrayMetadata;
						static const int messageTypeId=7;
						static const int protocolId=Energistics::Etp::v12::Datatypes::DataArray;
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::DataArray::GetDataArrayMetadataResponse> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::DataArray::GetDataArrayMetadataResponse& v) {		
			avro::encode(e, v.m_arrayMetadata);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::DataArray::GetDataArrayMetadataResponse& v) {		
			avro::decode(e, v.m_arrayMetadata);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace DataArray {				
					struct GetDataArrays{					
						std::map<std::string, Energistics::Etp::v12::Datatypes::DataArrayTypes::DataArrayIdentifier> m_dataArrays;
						static const int messageTypeId=2;
						static const int protocolId=Energistics::Etp::v12::Datatypes::DataArray;
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::DataArray::GetDataArrays> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::DataArray::GetDataArrays& v) {		
			avro::encode(e, v.m_dataArrays);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::DataArray::GetDataArrays& v) {		
			avro::decode(e, v.m_dataArrays);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace DataArray {				
					struct GetDataArraySlices{					
						std::map<std::string, Energistics::Etp::v12::Datatypes::DataArrayTypes::GetDataArraySlicesType> m_dataArraySlices;
						static const int messageTypeId=3;
						static const int protocolId=Energistics::Etp::v12::Datatypes::DataArray;
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::DataArray::GetDataArraySlices> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::DataArray::GetDataArraySlices& v) {		
			avro::encode(e, v.m_dataArraySlices);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::DataArray::GetDataArraySlices& v) {		
			avro::decode(e, v.m_dataArraySlices);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace DataArray {				
					struct GetDataArraySlicesResponse{					
						std::map<std::string, Energistics::Etp::v12::Datatypes::DataArrayTypes::DataArray> m_dataArraySlices;
						static const int messageTypeId=8;
						static const int protocolId=Energistics::Etp::v12::Datatypes::DataArray;
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::DataArray::GetDataArraySlicesResponse> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::DataArray::GetDataArraySlicesResponse& v) {		
			avro::encode(e, v.m_dataArraySlices);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::DataArray::GetDataArraySlicesResponse& v) {		
			avro::decode(e, v.m_dataArraySlices);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace DataArray {				
					struct GetDataArraysResponse{					
						std::map<std::string, Energistics::Etp::v12::Datatypes::DataArrayTypes::DataArray> m_dataArrays;
						static const int messageTypeId=1;
						static const int protocolId=Energistics::Etp::v12::Datatypes::DataArray;
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::DataArray::GetDataArraysResponse> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::DataArray::GetDataArraysResponse& v) {		
			avro::encode(e, v.m_dataArrays);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::DataArray::GetDataArraysResponse& v) {		
			avro::decode(e, v.m_dataArrays);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace DataArray {				
					struct PutDataArrays{					
						std::map<std::string, Energistics::Etp::v12::Datatypes::DataArrayTypes::PutDataArraysType> m_dataArrays;
						static const int messageTypeId=4;
						static const int protocolId=Energistics::Etp::v12::Datatypes::DataArray;
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::DataArray::PutDataArrays> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::DataArray::PutDataArrays& v) {		
			avro::encode(e, v.m_dataArrays);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::DataArray::PutDataArrays& v) {		
			avro::decode(e, v.m_dataArrays);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace DataArray {				
					struct PutDataArraySlices{					
						std::map<std::string, Energistics::Etp::v12::Datatypes::DataArrayTypes::PutDataArraySlicesType> m_dataArraySlices;
						static const int messageTypeId=5;
						static const int protocolId=Energistics::Etp::v12::Datatypes::DataArray;
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::DataArray::PutDataArraySlices> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::DataArray::PutDataArraySlices& v) {		
			avro::encode(e, v.m_dataArraySlices);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::DataArray::PutDataArraySlices& v) {		
			avro::decode(e, v.m_dataArraySlices);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace Dataspace {				
					struct DeleteDataspaces{					
						std::map<std::string, std::string> m_uids;
						static const int messageTypeId=4;
						static const int protocolId=Energistics::Etp::v12::Datatypes::Dataspace;
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::Dataspace::DeleteDataspaces> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::Dataspace::DeleteDataspaces& v) {		
			avro::encode(e, v.m_uids);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::Dataspace::DeleteDataspaces& v) {		
			avro::decode(e, v.m_uids);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace Dataspace {				
					struct GetDataspaceslastChangedFilter_t {
					private:					
						size_t idx_=0;
						boost::any value_;
										
					public:					
						size_t idx() const { return idx_; }
						bool is_null() const { return idx_==0; }
						void set_null() { idx_=0; value_ = boost::any(); }
						int64_t const & get_long() const {						
							if (idx_ != 1) {							
								throw avro::Exception("Invalid type for union.");
							}							
							return boost::any_cast< int64_t const & >(value_);
						}						
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
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::Dataspace::GetDataspaceslastChangedFilter_t> {
	
		static void encode(Encoder& e, Energistics::Etp::v12::Protocol::Dataspace::GetDataspaceslastChangedFilter_t v) {
		
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
		static void decode(Decoder& d, Energistics::Etp::v12::Protocol::Dataspace::GetDataspaceslastChangedFilter_t& v) {
		
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
			namespace Protocol {			
				namespace Dataspace {				
					struct GetDataspaces{					
						Energistics::Etp::v12::Protocol::Dataspace::GetDataspaceslastChangedFilter_t m_lastChangedFilter;
						static const int messageTypeId=1;
						static const int protocolId=Energistics::Etp::v12::Datatypes::Dataspace;
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::Dataspace::GetDataspaces> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::Dataspace::GetDataspaces& v) {		
			avro::encode(e, v.m_lastChangedFilter);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::Dataspace::GetDataspaces& v) {		
			avro::decode(e, v.m_lastChangedFilter);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace Dataspace {				
					struct GetDataspacesResponse{					
						std::vector<Energistics::Etp::v12::Datatypes::Object::Dataspace> m_dataspaces;
						static const int messageTypeId=2;
						static const int protocolId=Energistics::Etp::v12::Datatypes::Dataspace;
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::Dataspace::GetDataspacesResponse> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::Dataspace::GetDataspacesResponse& v) {		
			avro::encode(e, v.m_dataspaces);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::Dataspace::GetDataspacesResponse& v) {		
			avro::decode(e, v.m_dataspaces);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace Dataspace {				
					struct PutDataspaces{					
						std::map<std::string, Energistics::Etp::v12::Datatypes::Object::Dataspace> m_dataspaces;
						static const int messageTypeId=3;
						static const int protocolId=Energistics::Etp::v12::Datatypes::Dataspace;
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::Dataspace::PutDataspaces> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::Dataspace::PutDataspaces& v) {		
			avro::encode(e, v.m_dataspaces);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::Dataspace::PutDataspaces& v) {		
			avro::decode(e, v.m_dataspaces);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace Discovery {				
					struct GetResourceslastChangedFilter_t {
					private:					
						size_t idx_=0;
						boost::any value_;
										
					public:					
						size_t idx() const { return idx_; }
						bool is_null() const { return idx_==0; }
						void set_null() { idx_=0; value_ = boost::any(); }
						int64_t const & get_long() const {						
							if (idx_ != 1) {							
								throw avro::Exception("Invalid type for union.");
							}							
							return boost::any_cast< int64_t const & >(value_);
						}						
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
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::Discovery::GetResourceslastChangedFilter_t> {
	
		static void encode(Encoder& e, Energistics::Etp::v12::Protocol::Discovery::GetResourceslastChangedFilter_t v) {
		
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
		static void decode(Decoder& d, Energistics::Etp::v12::Protocol::Discovery::GetResourceslastChangedFilter_t& v) {
		
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
			namespace Protocol {			
				namespace Discovery {				
					struct GetResources{					
						Energistics::Etp::v12::Datatypes::Object::ContextInfo m_context;
						Energistics::Etp::v12::Datatypes::Object::ContextScopeKind m_scope;
						bool m_countObjects=false;
						Energistics::Etp::v12::Protocol::Discovery::GetResourceslastChangedFilter_t m_lastChangedFilter;
						static const int messageTypeId=1;
						static const int protocolId=Energistics::Etp::v12::Datatypes::Discovery;
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::Discovery::GetResources> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::Discovery::GetResources& v) {		
			avro::encode(e, v.m_context);
			avro::encode(e, v.m_scope);
			avro::encode(e, v.m_countObjects);
			avro::encode(e, v.m_lastChangedFilter);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::Discovery::GetResources& v) {		
			avro::decode(e, v.m_context);
			avro::decode(e, v.m_scope);
			avro::decode(e, v.m_countObjects);
			avro::decode(e, v.m_lastChangedFilter);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace Discovery {				
					struct GetResourcesResponse{					
						std::vector<Energistics::Etp::v12::Datatypes::Object::Resource> m_resources;
						static const int messageTypeId=4;
						static const int protocolId=Energistics::Etp::v12::Datatypes::Discovery;
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::Discovery::GetResourcesResponse> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::Discovery::GetResourcesResponse& v) {		
			avro::encode(e, v.m_resources);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::Discovery::GetResourcesResponse& v) {		
			avro::decode(e, v.m_resources);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace Discovery {				
					struct GetSupportedTypes{					
						std::string m_uri;
						Energistics::Etp::v12::Datatypes::Object::ContextScopeKind m_scope;
						bool m_returnEmptyTypes=false;
						bool m_countObjects=false;
						static const int messageTypeId=9;
						static const int protocolId=Energistics::Etp::v12::Datatypes::Discovery;
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::Discovery::GetSupportedTypes> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::Discovery::GetSupportedTypes& v) {		
			avro::encode(e, v.m_uri);
			avro::encode(e, v.m_scope);
			avro::encode(e, v.m_returnEmptyTypes);
			avro::encode(e, v.m_countObjects);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::Discovery::GetSupportedTypes& v) {		
			avro::decode(e, v.m_uri);
			avro::decode(e, v.m_scope);
			avro::decode(e, v.m_returnEmptyTypes);
			avro::decode(e, v.m_countObjects);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace Discovery {				
					struct GetSupportedTypesResponse{					
						std::vector<Energistics::Etp::v12::Datatypes::Object::SupportedType> m_supportedTypes;
						static const int messageTypeId=12;
						static const int protocolId=Energistics::Etp::v12::Datatypes::Discovery;
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::Discovery::GetSupportedTypesResponse> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::Discovery::GetSupportedTypesResponse& v) {		
			avro::encode(e, v.m_supportedTypes);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::Discovery::GetSupportedTypesResponse& v) {		
			avro::decode(e, v.m_supportedTypes);
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
						std::vector<Energistics::Etp::v12::Datatypes::Object::Resource> m_resources;
						std::string m_serverSortOrder;
						static const int messageTypeId=2;
						static const int protocolId=Energistics::Etp::v12::Datatypes::DiscoveryQuery;
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::DiscoveryQuery::FindResourcesResponse> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::DiscoveryQuery::FindResourcesResponse& v) {		
			avro::encode(e, v.m_resources);
			avro::encode(e, v.m_serverSortOrder);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::DiscoveryQuery::FindResourcesResponse& v) {		
			avro::decode(e, v.m_resources);
			avro::decode(e, v.m_serverSortOrder);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace GrowingObject {				
					struct DeleteParts{					
						std::string m_uri;
						std::map<std::string, std::string> m_uids;
						static const int messageTypeId=1;
						static const int protocolId=Energistics::Etp::v12::Datatypes::GrowingObject;
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::GrowingObject::DeleteParts> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::GrowingObject::DeleteParts& v) {		
			avro::encode(e, v.m_uri);
			avro::encode(e, v.m_uids);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::GrowingObject::DeleteParts& v) {		
			avro::decode(e, v.m_uri);
			avro::decode(e, v.m_uids);
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
					struct GetParts{					
						std::string m_uri;
						std::string m_format;
						std::map<std::string, std::string> m_uids;
						static const int messageTypeId=3;
						static const int protocolId=Energistics::Etp::v12::Datatypes::GrowingObject;
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::GrowingObject::GetParts> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::GrowingObject::GetParts& v) {		
			avro::encode(e, v.m_uri);
			avro::encode(e, v.m_format);
			avro::encode(e, v.m_uids);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::GrowingObject::GetParts& v) {		
			avro::decode(e, v.m_uri);
			avro::decode(e, v.m_format);
			avro::decode(e, v.m_uids);
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
						std::string m_format;
						Energistics::Etp::v12::Datatypes::Object::IndexInterval m_indexInterval;
						bool m_includeOverlappingIntervals=false;
						static const int messageTypeId=4;
						static const int protocolId=Energistics::Etp::v12::Datatypes::GrowingObject;
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::GrowingObject::GetPartsByRange> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::GrowingObject::GetPartsByRange& v) {		
			avro::encode(e, v.m_uri);
			avro::encode(e, v.m_format);
			avro::encode(e, v.m_indexInterval);
			avro::encode(e, v.m_includeOverlappingIntervals);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::GrowingObject::GetPartsByRange& v) {		
			avro::decode(e, v.m_uri);
			avro::decode(e, v.m_format);
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
					struct GetPartsByRangeResponse{					
						std::string m_uri;
						std::string m_format;
						std::vector<Energistics::Etp::v12::Datatypes::Object::ObjectPart> m_parts;
						static const int messageTypeId=10;
						static const int protocolId=Energistics::Etp::v12::Datatypes::GrowingObject;
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::GrowingObject::GetPartsByRangeResponse> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::GrowingObject::GetPartsByRangeResponse& v) {		
			avro::encode(e, v.m_uri);
			avro::encode(e, v.m_format);
			avro::encode(e, v.m_parts);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::GrowingObject::GetPartsByRangeResponse& v) {		
			avro::decode(e, v.m_uri);
			avro::decode(e, v.m_format);
			avro::decode(e, v.m_parts);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace GrowingObject {				
					struct GetPartsMetadata{					
						std::map<std::string, std::string> m_uris;
						static const int messageTypeId=8;
						static const int protocolId=Energistics::Etp::v12::Datatypes::GrowingObject;
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::GrowingObject::GetPartsMetadata> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::GrowingObject::GetPartsMetadata& v) {		
			avro::encode(e, v.m_uris);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::GrowingObject::GetPartsMetadata& v) {		
			avro::decode(e, v.m_uris);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace GrowingObject {				
					struct GetPartsMetadataResponse{					
						std::map<std::string, Energistics::Etp::v12::Datatypes::Object::PartsMetadataInfo> m_metadata;
						static const int messageTypeId=9;
						static const int protocolId=Energistics::Etp::v12::Datatypes::GrowingObject;
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::GrowingObject::GetPartsMetadataResponse> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::GrowingObject::GetPartsMetadataResponse& v) {		
			avro::encode(e, v.m_metadata);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::GrowingObject::GetPartsMetadataResponse& v) {		
			avro::decode(e, v.m_metadata);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace GrowingObject {				
					struct GetPartsResponse{					
						std::string m_uri;
						std::string m_format;
						std::map<std::string, Energistics::Etp::v12::Datatypes::Object::ObjectPart> m_parts;
						static const int messageTypeId=6;
						static const int protocolId=Energistics::Etp::v12::Datatypes::GrowingObject;
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::GrowingObject::GetPartsResponse> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::GrowingObject::GetPartsResponse& v) {		
			avro::encode(e, v.m_uri);
			avro::encode(e, v.m_format);
			avro::encode(e, v.m_parts);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::GrowingObject::GetPartsResponse& v) {		
			avro::decode(e, v.m_uri);
			avro::decode(e, v.m_format);
			avro::decode(e, v.m_parts);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace GrowingObject {				
					struct PutParts{					
						std::string m_uri;
						std::string m_format;
						std::map<std::string, Energistics::Etp::v12::Datatypes::Object::ObjectPart> m_parts;
						static const int messageTypeId=5;
						static const int protocolId=Energistics::Etp::v12::Datatypes::GrowingObject;
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::GrowingObject::PutParts> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::GrowingObject::PutParts& v) {		
			avro::encode(e, v.m_uri);
			avro::encode(e, v.m_format);
			avro::encode(e, v.m_parts);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::GrowingObject::PutParts& v) {		
			avro::decode(e, v.m_uri);
			avro::decode(e, v.m_format);
			avro::decode(e, v.m_parts);
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
						std::string m_format;
						std::vector<Energistics::Etp::v12::Datatypes::Object::ObjectPart> m_parts;
						static const int messageTypeId=7;
						static const int protocolId=Energistics::Etp::v12::Datatypes::GrowingObject;
					};					
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
			avro::encode(e, v.m_format);
			avro::encode(e, v.m_parts);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::GrowingObject::ReplacePartsByRange& v) {		
			avro::decode(e, v.m_uri);
			avro::decode(e, v.m_deleteInterval);
			avro::decode(e, v.m_includeOverlappingIntervals);
			avro::decode(e, v.m_format);
			avro::decode(e, v.m_parts);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace GrowingObjectNotification {				
					struct PartsChanged{					
						std::string m_uri;
						Energistics::Etp::v12::Datatypes::Uuid m_requestUuid;
						Energistics::Etp::v12::Datatypes::Object::ObjectChangeKind m_changeKind;
						int64_t m_changeTime;
						std::string m_format;
						std::vector<Energistics::Etp::v12::Datatypes::Object::ObjectPart> m_parts;
						static const int messageTypeId=2;
						static const int protocolId=Energistics::Etp::v12::Datatypes::GrowingObjectNotification;
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::GrowingObjectNotification::PartsChanged> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::GrowingObjectNotification::PartsChanged& v) {		
			avro::encode(e, v.m_uri);
			avro::encode(e, v.m_requestUuid);
			avro::encode(e, v.m_changeKind);
			avro::encode(e, v.m_changeTime);
			avro::encode(e, v.m_format);
			avro::encode(e, v.m_parts);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::GrowingObjectNotification::PartsChanged& v) {		
			avro::decode(e, v.m_uri);
			avro::decode(e, v.m_requestUuid);
			avro::decode(e, v.m_changeKind);
			avro::decode(e, v.m_changeTime);
			avro::decode(e, v.m_format);
			avro::decode(e, v.m_parts);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace GrowingObjectNotification {				
					struct PartsDeleted{					
						std::string m_uri;
						Energistics::Etp::v12::Datatypes::Uuid m_requestUuid;
						int64_t m_changeTime;
						std::vector<std::string> m_uids;
						static const int messageTypeId=3;
						static const int protocolId=Energistics::Etp::v12::Datatypes::GrowingObjectNotification;
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::GrowingObjectNotification::PartsDeleted> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::GrowingObjectNotification::PartsDeleted& v) {		
			avro::encode(e, v.m_uri);
			avro::encode(e, v.m_requestUuid);
			avro::encode(e, v.m_changeTime);
			avro::encode(e, v.m_uids);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::GrowingObjectNotification::PartsDeleted& v) {		
			avro::decode(e, v.m_uri);
			avro::decode(e, v.m_requestUuid);
			avro::decode(e, v.m_changeTime);
			avro::decode(e, v.m_uids);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace GrowingObjectNotification {				
					struct PartsDeletedByRange{					
						std::string m_uri;
						Energistics::Etp::v12::Datatypes::Object::IndexInterval m_deletedInterval;
						bool m_includeOverlappingIntervals=false;
						int64_t m_changeTime;
						Energistics::Etp::v12::Datatypes::Uuid m_requestUuid;
						static const int messageTypeId=5;
						static const int protocolId=Energistics::Etp::v12::Datatypes::GrowingObjectNotification;
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::GrowingObjectNotification::PartsDeletedByRange> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::GrowingObjectNotification::PartsDeletedByRange& v) {		
			avro::encode(e, v.m_uri);
			avro::encode(e, v.m_deletedInterval);
			avro::encode(e, v.m_includeOverlappingIntervals);
			avro::encode(e, v.m_changeTime);
			avro::encode(e, v.m_requestUuid);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::GrowingObjectNotification::PartsDeletedByRange& v) {		
			avro::decode(e, v.m_uri);
			avro::decode(e, v.m_deletedInterval);
			avro::decode(e, v.m_includeOverlappingIntervals);
			avro::decode(e, v.m_changeTime);
			avro::decode(e, v.m_requestUuid);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace GrowingObjectNotification {				
					struct PartsReplacedByRange{					
						std::string m_uri;
						Energistics::Etp::v12::Datatypes::Uuid m_requestUuid;
						int64_t m_changeTime;
						Energistics::Etp::v12::Datatypes::Object::IndexInterval m_deletedInterval;
						bool m_includeOverlappingIntervals=false;
						std::string m_format;
						std::vector<Energistics::Etp::v12::Datatypes::Object::ObjectPart> m_parts;
						static const int messageTypeId=6;
						static const int protocolId=Energistics::Etp::v12::Datatypes::GrowingObjectNotification;
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::GrowingObjectNotification::PartsReplacedByRange> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::GrowingObjectNotification::PartsReplacedByRange& v) {		
			avro::encode(e, v.m_uri);
			avro::encode(e, v.m_requestUuid);
			avro::encode(e, v.m_changeTime);
			avro::encode(e, v.m_deletedInterval);
			avro::encode(e, v.m_includeOverlappingIntervals);
			avro::encode(e, v.m_format);
			avro::encode(e, v.m_parts);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::GrowingObjectNotification::PartsReplacedByRange& v) {		
			avro::decode(e, v.m_uri);
			avro::decode(e, v.m_requestUuid);
			avro::decode(e, v.m_changeTime);
			avro::decode(e, v.m_deletedInterval);
			avro::decode(e, v.m_includeOverlappingIntervals);
			avro::decode(e, v.m_format);
			avro::decode(e, v.m_parts);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace GrowingObjectNotification {				
					struct PartSubscriptionEnded{					
						Energistics::Etp::v12::Datatypes::Uuid m_requestUuid;
						static const int messageTypeId=8;
						static const int protocolId=Energistics::Etp::v12::Datatypes::GrowingObjectNotification;
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::GrowingObjectNotification::PartSubscriptionEnded> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::GrowingObjectNotification::PartSubscriptionEnded& v) {		
			avro::encode(e, v.m_requestUuid);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::GrowingObjectNotification::PartSubscriptionEnded& v) {		
			avro::decode(e, v.m_requestUuid);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace GrowingObjectNotification {				
					struct SubscribePartNotification{					
						Energistics::Etp::v12::Datatypes::Object::SubscriptionInfo m_request;
						static const int messageTypeId=7;
						static const int protocolId=Energistics::Etp::v12::Datatypes::GrowingObjectNotification;
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::GrowingObjectNotification::SubscribePartNotification> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::GrowingObjectNotification::SubscribePartNotification& v) {		
			avro::encode(e, v.m_request);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::GrowingObjectNotification::SubscribePartNotification& v) {		
			avro::decode(e, v.m_request);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace GrowingObjectNotification {				
					struct UnsolicitedPartNotifications{					
						std::vector<Energistics::Etp::v12::Datatypes::Object::SubscriptionInfo> m_subscriptions;
						static const int messageTypeId=9;
						static const int protocolId=Energistics::Etp::v12::Datatypes::GrowingObjectNotification;
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::GrowingObjectNotification::UnsolicitedPartNotifications> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::GrowingObjectNotification::UnsolicitedPartNotifications& v) {		
			avro::encode(e, v.m_subscriptions);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::GrowingObjectNotification::UnsolicitedPartNotifications& v) {		
			avro::decode(e, v.m_subscriptions);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace GrowingObjectNotification {				
					struct UnsubscribePartNotification{					
						Energistics::Etp::v12::Datatypes::Uuid m_requestUuid;
						static const int messageTypeId=4;
						static const int protocolId=Energistics::Etp::v12::Datatypes::GrowingObjectNotification;
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::GrowingObjectNotification::UnsubscribePartNotification> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::GrowingObjectNotification::UnsubscribePartNotification& v) {		
			avro::encode(e, v.m_requestUuid);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::GrowingObjectNotification::UnsubscribePartNotification& v) {		
			avro::decode(e, v.m_requestUuid);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace Store {				
					struct Chunk{					
						std::string m_blobId;
						std::string m_data;
						static const int messageTypeId=8;
						static const int protocolId=Energistics::Etp::v12::Datatypes::Store;
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::Store::Chunk> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::Store::Chunk& v) {		
			avro::encode(e, v.m_blobId);
			avro::encode(e, v.m_data);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::Store::Chunk& v) {		
			avro::decode(e, v.m_blobId);
			avro::decode(e, v.m_data);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace Store {				
					struct GetDataObjects{					
						std::map<std::string, std::string> m_uris;
						std::string m_format;
						static const int messageTypeId=1;
						static const int protocolId=Energistics::Etp::v12::Datatypes::Store;
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::Store::GetDataObjects> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::Store::GetDataObjects& v) {		
			avro::encode(e, v.m_uris);
			avro::encode(e, v.m_format);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::Store::GetDataObjects& v) {		
			avro::decode(e, v.m_uris);
			avro::decode(e, v.m_format);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace Store {				
					struct DeleteDataObjects{					
						std::map<std::string, std::string> m_uris;
						static const int messageTypeId=3;
						static const int protocolId=Energistics::Etp::v12::Datatypes::Store;
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::Store::DeleteDataObjects> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::Store::DeleteDataObjects& v) {		
			avro::encode(e, v.m_uris);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::Store::DeleteDataObjects& v) {		
			avro::decode(e, v.m_uris);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace Store {				
					struct GetDataObjectsResponse{					
						std::map<std::string, Energistics::Etp::v12::Datatypes::Object::DataObject> m_dataObjects;
						static const int messageTypeId=4;
						static const int protocolId=Energistics::Etp::v12::Datatypes::Store;
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::Store::GetDataObjectsResponse> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::Store::GetDataObjectsResponse& v) {		
			avro::encode(e, v.m_dataObjects);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::Store::GetDataObjectsResponse& v) {		
			avro::decode(e, v.m_dataObjects);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace Store {				
					struct PutDataObjects{					
						std::map<std::string, Energistics::Etp::v12::Datatypes::Object::DataObject> m_dataObjects;
						static const int messageTypeId=2;
						static const int protocolId=Energistics::Etp::v12::Datatypes::Store;
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::Store::PutDataObjects> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::Store::PutDataObjects& v) {		
			avro::encode(e, v.m_dataObjects);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::Store::PutDataObjects& v) {		
			avro::decode(e, v.m_dataObjects);
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
						std::string m_format;
						static const int messageTypeId=1;
						static const int protocolId=Energistics::Etp::v12::Datatypes::GrowingObjectQuery;
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::GrowingObjectQuery::FindParts> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::GrowingObjectQuery::FindParts& v) {		
			avro::encode(e, v.m_uri);
			avro::encode(e, v.m_format);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::GrowingObjectQuery::FindParts& v) {		
			avro::decode(e, v.m_uri);
			avro::decode(e, v.m_format);
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
						std::string m_serverSortOrder;
						std::string m_format;
						std::vector<Energistics::Etp::v12::Datatypes::Object::ObjectPart> m_objectParts;
						static const int messageTypeId=2;
						static const int protocolId=Energistics::Etp::v12::Datatypes::GrowingObjectQuery;
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::GrowingObjectQuery::FindPartsResponse> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::GrowingObjectQuery::FindPartsResponse& v) {		
			avro::encode(e, v.m_uri);
			avro::encode(e, v.m_serverSortOrder);
			avro::encode(e, v.m_format);
			avro::encode(e, v.m_objectParts);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::GrowingObjectQuery::FindPartsResponse& v) {		
			avro::decode(e, v.m_uri);
			avro::decode(e, v.m_serverSortOrder);
			avro::decode(e, v.m_format);
			avro::decode(e, v.m_objectParts);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace StoreNotification {				
					struct Chunk{					
						std::string m_blobId;
						std::string m_data;
						static const int messageTypeId=9;
						static const int protocolId=Energistics::Etp::v12::Datatypes::StoreNotification;
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::StoreNotification::Chunk> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::StoreNotification::Chunk& v) {		
			avro::encode(e, v.m_blobId);
			avro::encode(e, v.m_data);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::StoreNotification::Chunk& v) {		
			avro::decode(e, v.m_blobId);
			avro::decode(e, v.m_data);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace StoreNotification {				
					struct ObjectAccessRevoked{					
						std::string m_uri;
						int64_t m_changeTime;
						Energistics::Etp::v12::Datatypes::Uuid m_requestUuid;
						static const int messageTypeId=5;
						static const int protocolId=Energistics::Etp::v12::Datatypes::StoreNotification;
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::StoreNotification::ObjectAccessRevoked> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::StoreNotification::ObjectAccessRevoked& v) {		
			avro::encode(e, v.m_uri);
			avro::encode(e, v.m_changeTime);
			avro::encode(e, v.m_requestUuid);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::StoreNotification::ObjectAccessRevoked& v) {		
			avro::decode(e, v.m_uri);
			avro::decode(e, v.m_changeTime);
			avro::decode(e, v.m_requestUuid);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace StoreNotification {				
					struct ObjectChanged{					
						Energistics::Etp::v12::Datatypes::Object::ObjectChange m_change;
						Energistics::Etp::v12::Datatypes::Uuid m_requestUuid;
						static const int messageTypeId=2;
						static const int protocolId=Energistics::Etp::v12::Datatypes::StoreNotification;
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::StoreNotification::ObjectChanged> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::StoreNotification::ObjectChanged& v) {		
			avro::encode(e, v.m_change);
			avro::encode(e, v.m_requestUuid);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::StoreNotification::ObjectChanged& v) {		
			avro::decode(e, v.m_change);
			avro::decode(e, v.m_requestUuid);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace StoreNotification {				
					struct ObjectDeleted{					
						std::string m_uri;
						int64_t m_changeTime;
						Energistics::Etp::v12::Datatypes::Uuid m_requestUuid;
						static const int messageTypeId=3;
						static const int protocolId=Energistics::Etp::v12::Datatypes::StoreNotification;
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::StoreNotification::ObjectDeleted> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::StoreNotification::ObjectDeleted& v) {		
			avro::encode(e, v.m_uri);
			avro::encode(e, v.m_changeTime);
			avro::encode(e, v.m_requestUuid);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::StoreNotification::ObjectDeleted& v) {		
			avro::decode(e, v.m_uri);
			avro::decode(e, v.m_changeTime);
			avro::decode(e, v.m_requestUuid);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace StoreNotification {				
					struct SubscribeNotifications{					
						Energistics::Etp::v12::Datatypes::Object::SubscriptionInfo m_request;
						static const int messageTypeId=6;
						static const int protocolId=Energistics::Etp::v12::Datatypes::StoreNotification;
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::StoreNotification::SubscribeNotifications> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::StoreNotification::SubscribeNotifications& v) {		
			avro::encode(e, v.m_request);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::StoreNotification::SubscribeNotifications& v) {		
			avro::decode(e, v.m_request);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace StoreNotification {				
					struct SubscriptionEnded{					
						Energistics::Etp::v12::Datatypes::Uuid m_requestUuid;
						static const int messageTypeId=7;
						static const int protocolId=Energistics::Etp::v12::Datatypes::StoreNotification;
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::StoreNotification::SubscriptionEnded> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::StoreNotification::SubscriptionEnded& v) {		
			avro::encode(e, v.m_requestUuid);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::StoreNotification::SubscriptionEnded& v) {		
			avro::decode(e, v.m_requestUuid);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace StoreNotification {				
					struct UnsolicitedStoreNotifications{					
						std::vector<Energistics::Etp::v12::Datatypes::Object::SubscriptionInfo> m_subscriptions;
						static const int messageTypeId=8;
						static const int protocolId=Energistics::Etp::v12::Datatypes::StoreNotification;
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::StoreNotification::UnsolicitedStoreNotifications> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::StoreNotification::UnsolicitedStoreNotifications& v) {		
			avro::encode(e, v.m_subscriptions);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::StoreNotification::UnsolicitedStoreNotifications& v) {		
			avro::decode(e, v.m_subscriptions);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace StoreNotification {				
					struct UnsubscribeNotifications{					
						Energistics::Etp::v12::Datatypes::Uuid m_requestUuid;
						static const int messageTypeId=4;
						static const int protocolId=Energistics::Etp::v12::Datatypes::StoreNotification;
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::StoreNotification::UnsubscribeNotifications> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::StoreNotification::UnsubscribeNotifications& v) {		
			avro::encode(e, v.m_requestUuid);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::StoreNotification::UnsubscribeNotifications& v) {		
			avro::decode(e, v.m_requestUuid);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace StoreQuery {				
					struct Chunk{					
						std::string m_blobId;
						std::string m_data;
						static const int messageTypeId=3;
						static const int protocolId=Energistics::Etp::v12::Datatypes::StoreQuery;
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::StoreQuery::Chunk> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::StoreQuery::Chunk& v) {		
			avro::encode(e, v.m_blobId);
			avro::encode(e, v.m_data);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::StoreQuery::Chunk& v) {		
			avro::decode(e, v.m_blobId);
			avro::decode(e, v.m_data);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace StoreQuery {				
					struct FindObjectsResponse{					
						std::vector<Energistics::Etp::v12::Datatypes::Object::DataObject> m_dataObjects;
						std::string m_serverSortOrder;
						static const int messageTypeId=2;
						static const int protocolId=Energistics::Etp::v12::Datatypes::StoreQuery;
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::StoreQuery::FindObjectsResponse> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::StoreQuery::FindObjectsResponse& v) {		
			avro::encode(e, v.m_dataObjects);
			avro::encode(e, v.m_serverSortOrder);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::StoreQuery::FindObjectsResponse& v) {		
			avro::decode(e, v.m_dataObjects);
			avro::decode(e, v.m_serverSortOrder);
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
						std::string m_format;
						static const int messageTypeId=1;
						static const int protocolId=Energistics::Etp::v12::Datatypes::StoreQuery;
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::StoreQuery::FindObjects> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::StoreQuery::FindObjects& v) {		
			avro::encode(e, v.m_uri);
			avro::encode(e, v.m_format);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::StoreQuery::FindObjects& v) {		
			avro::decode(e, v.m_uri);
			avro::decode(e, v.m_format);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace Transaction {				
					struct CommitTransaction{					
						Energistics::Etp::v12::Datatypes::Uuid m_transactionUuid;
						static const int messageTypeId=3;
						static const int protocolId=Energistics::Etp::v12::Datatypes::Transaction;
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::Transaction::CommitTransaction> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::Transaction::CommitTransaction& v) {		
			avro::encode(e, v.m_transactionUuid);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::Transaction::CommitTransaction& v) {		
			avro::decode(e, v.m_transactionUuid);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace Transaction {				
					struct CommitTransactionResponse{					
						Energistics::Etp::v12::Datatypes::Uuid m_transactionUuid;
						bool m_successful=false;
						std::string m_failureReason;
						static const int messageTypeId=5;
						static const int protocolId=Energistics::Etp::v12::Datatypes::Transaction;
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::Transaction::CommitTransactionResponse> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::Transaction::CommitTransactionResponse& v) {		
			avro::encode(e, v.m_transactionUuid);
			avro::encode(e, v.m_successful);
			avro::encode(e, v.m_failureReason);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::Transaction::CommitTransactionResponse& v) {		
			avro::decode(e, v.m_transactionUuid);
			avro::decode(e, v.m_successful);
			avro::decode(e, v.m_failureReason);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace Transaction {				
					struct RollbackTransaction{					
						Energistics::Etp::v12::Datatypes::Uuid m_transactionUuid;
						static const int messageTypeId=4;
						static const int protocolId=Energistics::Etp::v12::Datatypes::Transaction;
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::Transaction::RollbackTransaction> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::Transaction::RollbackTransaction& v) {		
			avro::encode(e, v.m_transactionUuid);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::Transaction::RollbackTransaction& v) {		
			avro::decode(e, v.m_transactionUuid);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace Transaction {				
					struct StartTransaction{					
						bool m_readOnly=false;
						std::string m_message;
						static const int messageTypeId=1;
						static const int protocolId=Energistics::Etp::v12::Datatypes::Transaction;
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::Transaction::StartTransaction> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::Transaction::StartTransaction& v) {		
			avro::encode(e, v.m_readOnly);
			avro::encode(e, v.m_message);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::Transaction::StartTransaction& v) {		
			avro::decode(e, v.m_readOnly);
			avro::decode(e, v.m_message);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace Transaction {				
					struct StartTransactionResponse{					
						Energistics::Etp::v12::Datatypes::Uuid m_transactionUuid;
						static const int messageTypeId=2;
						static const int protocolId=Energistics::Etp::v12::Datatypes::Transaction;
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::Transaction::StartTransactionResponse> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::Transaction::StartTransactionResponse& v) {		
			avro::encode(e, v.m_transactionUuid);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::Transaction::StartTransactionResponse& v) {		
			avro::decode(e, v.m_transactionUuid);
		}		
	};	
}


#endif