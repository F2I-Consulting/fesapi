#ifndef ETP_MESSAGES__
#define ETP_MESSAGES__

#include <map>
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <array>

#include "boost/optional.hpp"
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
					std::vector<bool> values;
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Datatypes::ArrayOfBoolean> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Datatypes::ArrayOfBoolean& v) {		
			avro::encode(e, v.values);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Datatypes::ArrayOfBoolean& v) {		
			avro::decode(e, v.values);
		}		
	};	
}
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
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Datatypes::ArrayOfDouble> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Datatypes::ArrayOfDouble& v) {		
			avro::encode(e, v.values);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Datatypes::ArrayOfDouble& v) {		
			avro::decode(e, v.values);
		}		
	};	
}
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
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Datatypes::ArrayOfFloat> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Datatypes::ArrayOfFloat& v) {		
			avro::encode(e, v.values);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Datatypes::ArrayOfFloat& v) {		
			avro::decode(e, v.values);
		}		
	};	
}
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
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Datatypes::ArrayOfInt> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Datatypes::ArrayOfInt& v) {		
			avro::encode(e, v.values);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Datatypes::ArrayOfInt& v) {		
			avro::decode(e, v.values);
		}		
	};	
}
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
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Datatypes::ArrayOfLong> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Datatypes::ArrayOfLong& v) {		
			avro::encode(e, v.values);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Datatypes::ArrayOfLong& v) {		
			avro::decode(e, v.values);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Datatypes {			
				struct ArrayOfNullableBoolean{				
					std::vector<boost::optional<bool>> values;
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Datatypes::ArrayOfNullableBoolean> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Datatypes::ArrayOfNullableBoolean& v) {		
			avro::encode(e, v.values);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Datatypes::ArrayOfNullableBoolean& v) {		
			avro::decode(e, v.values);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Datatypes {			
				struct ArrayOfNullableInt{				
					std::vector<boost::optional<int32_t>> values;
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Datatypes::ArrayOfNullableInt> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Datatypes::ArrayOfNullableInt& v) {		
			avro::encode(e, v.values);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Datatypes::ArrayOfNullableInt& v) {		
			avro::decode(e, v.values);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Datatypes {			
				struct ArrayOfNullableLong{				
					std::vector<boost::optional<int64_t>> values;
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Datatypes::ArrayOfNullableLong> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Datatypes::ArrayOfNullableLong& v) {		
			avro::encode(e, v.values);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Datatypes::ArrayOfNullableLong& v) {		
			avro::decode(e, v.values);
		}		
	};	
}
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
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Datatypes::ArrayOfString> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Datatypes::ArrayOfString& v) {		
			avro::encode(e, v.values);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Datatypes::ArrayOfString& v) {		
			avro::decode(e, v.values);
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
					Energistics::Etp::v12::Datatypes::ArrayOfBoolean const & get_ArrayOfBoolean() const {					
						if (idx_ != 0) {						
							throw avro::Exception("Invalid type for union.");
						}						
						return boost::any_cast< Energistics::Etp::v12::Datatypes::ArrayOfBoolean const & >(value_);
					}					
					Energistics::Etp::v12::Datatypes::ArrayOfBoolean& get_ArrayOfBoolean()  {					
						if (idx_ != 0) {						
							throw avro::Exception("Invalid type for union.");
						}						
						return boost::any_cast< Energistics::Etp::v12::Datatypes::ArrayOfBoolean& >(value_);
					}					
					void set_ArrayOfBoolean(const Energistics::Etp::v12::Datatypes::ArrayOfBoolean& v) {					
						idx_ = 0;
						value_ = v;
					}					
					Energistics::Etp::v12::Datatypes::ArrayOfInt const & get_ArrayOfInt() const {					
						if (idx_ != 1) {						
							throw avro::Exception("Invalid type for union.");
						}						
						return boost::any_cast< Energistics::Etp::v12::Datatypes::ArrayOfInt const & >(value_);
					}					
					Energistics::Etp::v12::Datatypes::ArrayOfInt& get_ArrayOfInt()  {					
						if (idx_ != 1) {						
							throw avro::Exception("Invalid type for union.");
						}						
						return boost::any_cast< Energistics::Etp::v12::Datatypes::ArrayOfInt& >(value_);
					}					
					void set_ArrayOfInt(const Energistics::Etp::v12::Datatypes::ArrayOfInt& v) {					
						idx_ = 1;
						value_ = v;
					}					
					Energistics::Etp::v12::Datatypes::ArrayOfLong const & get_ArrayOfLong() const {					
						if (idx_ != 2) {						
							throw avro::Exception("Invalid type for union.");
						}						
						return boost::any_cast< Energistics::Etp::v12::Datatypes::ArrayOfLong const & >(value_);
					}					
					Energistics::Etp::v12::Datatypes::ArrayOfLong& get_ArrayOfLong()  {					
						if (idx_ != 2) {						
							throw avro::Exception("Invalid type for union.");
						}						
						return boost::any_cast< Energistics::Etp::v12::Datatypes::ArrayOfLong& >(value_);
					}					
					void set_ArrayOfLong(const Energistics::Etp::v12::Datatypes::ArrayOfLong& v) {					
						idx_ = 2;
						value_ = v;
					}					
					Energistics::Etp::v12::Datatypes::ArrayOfFloat const & get_ArrayOfFloat() const {					
						if (idx_ != 3) {						
							throw avro::Exception("Invalid type for union.");
						}						
						return boost::any_cast< Energistics::Etp::v12::Datatypes::ArrayOfFloat const & >(value_);
					}					
					Energistics::Etp::v12::Datatypes::ArrayOfFloat& get_ArrayOfFloat()  {					
						if (idx_ != 3) {						
							throw avro::Exception("Invalid type for union.");
						}						
						return boost::any_cast< Energistics::Etp::v12::Datatypes::ArrayOfFloat& >(value_);
					}					
					void set_ArrayOfFloat(const Energistics::Etp::v12::Datatypes::ArrayOfFloat& v) {					
						idx_ = 3;
						value_ = v;
					}					
					Energistics::Etp::v12::Datatypes::ArrayOfDouble const & get_ArrayOfDouble() const {					
						if (idx_ != 4) {						
							throw avro::Exception("Invalid type for union.");
						}						
						return boost::any_cast< Energistics::Etp::v12::Datatypes::ArrayOfDouble const & >(value_);
					}					
					Energistics::Etp::v12::Datatypes::ArrayOfDouble& get_ArrayOfDouble()  {					
						if (idx_ != 4) {						
							throw avro::Exception("Invalid type for union.");
						}						
						return boost::any_cast< Energistics::Etp::v12::Datatypes::ArrayOfDouble& >(value_);
					}					
					void set_ArrayOfDouble(const Energistics::Etp::v12::Datatypes::ArrayOfDouble& v) {					
						idx_ = 4;
						value_ = v;
					}					
					Energistics::Etp::v12::Datatypes::ArrayOfString const & get_ArrayOfString() const {					
						if (idx_ != 5) {						
							throw avro::Exception("Invalid type for union.");
						}						
						return boost::any_cast< Energistics::Etp::v12::Datatypes::ArrayOfString const & >(value_);
					}					
					Energistics::Etp::v12::Datatypes::ArrayOfString& get_ArrayOfString()  {					
						if (idx_ != 5) {						
							throw avro::Exception("Invalid type for union.");
						}						
						return boost::any_cast< Energistics::Etp::v12::Datatypes::ArrayOfString& >(value_);
					}					
					void set_ArrayOfString(const Energistics::Etp::v12::Datatypes::ArrayOfString& v) {					
						idx_ = 5;
						value_ = v;
					}					
					std::string const & get_bytes() const {					
						if (idx_ != 6) {						
							throw avro::Exception("Invalid type for union.");
						}						
						return boost::any_cast< std::string const & >(value_);
					}					
					std::string& get_bytes()  {					
						if (idx_ != 6) {						
							throw avro::Exception("Invalid type for union.");
						}						
						return boost::any_cast< std::string& >(value_);
					}					
					void set_bytes(const std::string& v) {					
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
					avro::encode(e, v.get_ArrayOfBoolean());
					break;								
				case 1:				
					avro::encode(e, v.get_ArrayOfInt());
					break;								
				case 2:				
					avro::encode(e, v.get_ArrayOfLong());
					break;								
				case 3:				
					avro::encode(e, v.get_ArrayOfFloat());
					break;								
				case 4:				
					avro::encode(e, v.get_ArrayOfDouble());
					break;								
				case 5:				
					avro::encode(e, v.get_ArrayOfString());
					break;								
				case 6:				
					avro::encode(e, v.get_bytes());
					break;								
			}			
		}		
		static void decode(Decoder& d, Energistics::Etp::v12::Datatypes::AnyArrayitem_t& v) {
		
			size_t n = d.decodeUnionIndex();
			if (n >= 7) { throw avro::Exception("Union index too big"); }
			switch (n) {			
				case 0:				
					{					
						Energistics::Etp::v12::Datatypes::ArrayOfBoolean vv;
						avro::decode(d, vv);
						v.set_ArrayOfBoolean(vv);
					}					
					break;								
				case 1:				
					{					
						Energistics::Etp::v12::Datatypes::ArrayOfInt vv;
						avro::decode(d, vv);
						v.set_ArrayOfInt(vv);
					}					
					break;								
				case 2:				
					{					
						Energistics::Etp::v12::Datatypes::ArrayOfLong vv;
						avro::decode(d, vv);
						v.set_ArrayOfLong(vv);
					}					
					break;								
				case 3:				
					{					
						Energistics::Etp::v12::Datatypes::ArrayOfFloat vv;
						avro::decode(d, vv);
						v.set_ArrayOfFloat(vv);
					}					
					break;								
				case 4:				
					{					
						Energistics::Etp::v12::Datatypes::ArrayOfDouble vv;
						avro::decode(d, vv);
						v.set_ArrayOfDouble(vv);
					}					
					break;								
				case 5:				
					{					
						Energistics::Etp::v12::Datatypes::ArrayOfString vv;
						avro::decode(d, vv);
						v.set_ArrayOfString(vv);
					}					
					break;								
				case 6:				
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
					Energistics::Etp::v12::Datatypes::AnyArrayitem_t item;
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Datatypes::AnyArray> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Datatypes::AnyArray& v) {		
			avro::encode(e, v.item);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Datatypes::AnyArray& v) {		
			avro::decode(e, v.item);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Datatypes {			
				struct AnySubarray{				
					int64_t start;
					Energistics::Etp::v12::Datatypes::AnyArray slice;
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Datatypes::AnySubarray> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Datatypes::AnySubarray& v) {		
			avro::encode(e, v.start);
			avro::encode(e, v.slice);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Datatypes::AnySubarray& v) {		
			avro::decode(e, v.start);
			avro::decode(e, v.slice);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Datatypes {			
				struct AnySparseArray{				
					std::vector<Energistics::Etp::v12::Datatypes::AnySubarray> slices;
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Datatypes::AnySparseArray> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Datatypes::AnySparseArray& v) {		
			avro::encode(e, v.slices);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Datatypes::AnySparseArray& v) {		
			avro::decode(e, v.slices);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Datatypes {			
				struct Contact{				
					std::string organizationName;
					std::string contactName;
					std::string contactPhone;
					std::string contactEmail;
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Datatypes::Contact> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Datatypes::Contact& v) {		
			avro::encode(e, v.organizationName);
			avro::encode(e, v.contactName);
			avro::encode(e, v.contactPhone);
			avro::encode(e, v.contactEmail);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Datatypes::Contact& v) {		
			avro::decode(e, v.organizationName);
			avro::decode(e, v.contactName);
			avro::decode(e, v.contactPhone);
			avro::decode(e, v.contactEmail);
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
					Energistics::Etp::v12::Datatypes::ArrayOfNullableBoolean const & get_ArrayOfNullableBoolean() const {					
						if (idx_ != 8) {						
							throw avro::Exception("Invalid type for union.");
						}						
						return boost::any_cast< Energistics::Etp::v12::Datatypes::ArrayOfNullableBoolean const & >(value_);
					}					
					Energistics::Etp::v12::Datatypes::ArrayOfNullableBoolean& get_ArrayOfNullableBoolean()  {					
						if (idx_ != 8) {						
							throw avro::Exception("Invalid type for union.");
						}						
						return boost::any_cast< Energistics::Etp::v12::Datatypes::ArrayOfNullableBoolean& >(value_);
					}					
					void set_ArrayOfNullableBoolean(const Energistics::Etp::v12::Datatypes::ArrayOfNullableBoolean& v) {					
						idx_ = 8;
						value_ = v;
					}					
					Energistics::Etp::v12::Datatypes::ArrayOfInt const & get_ArrayOfInt() const {					
						if (idx_ != 9) {						
							throw avro::Exception("Invalid type for union.");
						}						
						return boost::any_cast< Energistics::Etp::v12::Datatypes::ArrayOfInt const & >(value_);
					}					
					Energistics::Etp::v12::Datatypes::ArrayOfInt& get_ArrayOfInt()  {					
						if (idx_ != 9) {						
							throw avro::Exception("Invalid type for union.");
						}						
						return boost::any_cast< Energistics::Etp::v12::Datatypes::ArrayOfInt& >(value_);
					}					
					void set_ArrayOfInt(const Energistics::Etp::v12::Datatypes::ArrayOfInt& v) {					
						idx_ = 9;
						value_ = v;
					}					
					Energistics::Etp::v12::Datatypes::ArrayOfNullableInt const & get_ArrayOfNullableInt() const {					
						if (idx_ != 10) {						
							throw avro::Exception("Invalid type for union.");
						}						
						return boost::any_cast< Energistics::Etp::v12::Datatypes::ArrayOfNullableInt const & >(value_);
					}					
					Energistics::Etp::v12::Datatypes::ArrayOfNullableInt& get_ArrayOfNullableInt()  {					
						if (idx_ != 10) {						
							throw avro::Exception("Invalid type for union.");
						}						
						return boost::any_cast< Energistics::Etp::v12::Datatypes::ArrayOfNullableInt& >(value_);
					}					
					void set_ArrayOfNullableInt(const Energistics::Etp::v12::Datatypes::ArrayOfNullableInt& v) {					
						idx_ = 10;
						value_ = v;
					}					
					Energistics::Etp::v12::Datatypes::ArrayOfLong const & get_ArrayOfLong() const {					
						if (idx_ != 11) {						
							throw avro::Exception("Invalid type for union.");
						}						
						return boost::any_cast< Energistics::Etp::v12::Datatypes::ArrayOfLong const & >(value_);
					}					
					Energistics::Etp::v12::Datatypes::ArrayOfLong& get_ArrayOfLong()  {					
						if (idx_ != 11) {						
							throw avro::Exception("Invalid type for union.");
						}						
						return boost::any_cast< Energistics::Etp::v12::Datatypes::ArrayOfLong& >(value_);
					}					
					void set_ArrayOfLong(const Energistics::Etp::v12::Datatypes::ArrayOfLong& v) {					
						idx_ = 11;
						value_ = v;
					}					
					Energistics::Etp::v12::Datatypes::ArrayOfNullableLong const & get_ArrayOfNullableLong() const {					
						if (idx_ != 12) {						
							throw avro::Exception("Invalid type for union.");
						}						
						return boost::any_cast< Energistics::Etp::v12::Datatypes::ArrayOfNullableLong const & >(value_);
					}					
					Energistics::Etp::v12::Datatypes::ArrayOfNullableLong& get_ArrayOfNullableLong()  {					
						if (idx_ != 12) {						
							throw avro::Exception("Invalid type for union.");
						}						
						return boost::any_cast< Energistics::Etp::v12::Datatypes::ArrayOfNullableLong& >(value_);
					}					
					void set_ArrayOfNullableLong(const Energistics::Etp::v12::Datatypes::ArrayOfNullableLong& v) {					
						idx_ = 12;
						value_ = v;
					}					
					Energistics::Etp::v12::Datatypes::ArrayOfFloat const & get_ArrayOfFloat() const {					
						if (idx_ != 13) {						
							throw avro::Exception("Invalid type for union.");
						}						
						return boost::any_cast< Energistics::Etp::v12::Datatypes::ArrayOfFloat const & >(value_);
					}					
					Energistics::Etp::v12::Datatypes::ArrayOfFloat& get_ArrayOfFloat()  {					
						if (idx_ != 13) {						
							throw avro::Exception("Invalid type for union.");
						}						
						return boost::any_cast< Energistics::Etp::v12::Datatypes::ArrayOfFloat& >(value_);
					}					
					void set_ArrayOfFloat(const Energistics::Etp::v12::Datatypes::ArrayOfFloat& v) {					
						idx_ = 13;
						value_ = v;
					}					
					Energistics::Etp::v12::Datatypes::ArrayOfDouble const & get_ArrayOfDouble() const {					
						if (idx_ != 14) {						
							throw avro::Exception("Invalid type for union.");
						}						
						return boost::any_cast< Energistics::Etp::v12::Datatypes::ArrayOfDouble const & >(value_);
					}					
					Energistics::Etp::v12::Datatypes::ArrayOfDouble& get_ArrayOfDouble()  {					
						if (idx_ != 14) {						
							throw avro::Exception("Invalid type for union.");
						}						
						return boost::any_cast< Energistics::Etp::v12::Datatypes::ArrayOfDouble& >(value_);
					}					
					void set_ArrayOfDouble(const Energistics::Etp::v12::Datatypes::ArrayOfDouble& v) {					
						idx_ = 14;
						value_ = v;
					}					
					Energistics::Etp::v12::Datatypes::ArrayOfString const & get_ArrayOfString() const {					
						if (idx_ != 15) {						
							throw avro::Exception("Invalid type for union.");
						}						
						return boost::any_cast< Energistics::Etp::v12::Datatypes::ArrayOfString const & >(value_);
					}					
					Energistics::Etp::v12::Datatypes::ArrayOfString& get_ArrayOfString()  {					
						if (idx_ != 15) {						
							throw avro::Exception("Invalid type for union.");
						}						
						return boost::any_cast< Energistics::Etp::v12::Datatypes::ArrayOfString& >(value_);
					}					
					void set_ArrayOfString(const Energistics::Etp::v12::Datatypes::ArrayOfString& v) {					
						idx_ = 15;
						value_ = v;
					}					
					std::string const & get_bytes() const {					
						if (idx_ != 16) {						
							throw avro::Exception("Invalid type for union.");
						}						
						return boost::any_cast< std::string const & >(value_);
					}					
					std::string& get_bytes()  {					
						if (idx_ != 16) {						
							throw avro::Exception("Invalid type for union.");
						}						
						return boost::any_cast< std::string& >(value_);
					}					
					void set_bytes(const std::string& v) {					
						idx_ = 16;
						value_ = v;
					}					
					Energistics::Etp::v12::Datatypes::AnySparseArray const & get_AnySparseArray() const {					
						if (idx_ != 17) {						
							throw avro::Exception("Invalid type for union.");
						}						
						return boost::any_cast< Energistics::Etp::v12::Datatypes::AnySparseArray const & >(value_);
					}					
					Energistics::Etp::v12::Datatypes::AnySparseArray& get_AnySparseArray()  {					
						if (idx_ != 17) {						
							throw avro::Exception("Invalid type for union.");
						}						
						return boost::any_cast< Energistics::Etp::v12::Datatypes::AnySparseArray& >(value_);
					}					
					void set_AnySparseArray(const Energistics::Etp::v12::Datatypes::AnySparseArray& v) {					
						idx_ = 17;
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
					avro::encode(e, v.get_ArrayOfNullableBoolean());
					break;								
				case 9:				
					avro::encode(e, v.get_ArrayOfInt());
					break;								
				case 10:				
					avro::encode(e, v.get_ArrayOfNullableInt());
					break;								
				case 11:				
					avro::encode(e, v.get_ArrayOfLong());
					break;								
				case 12:				
					avro::encode(e, v.get_ArrayOfNullableLong());
					break;								
				case 13:				
					avro::encode(e, v.get_ArrayOfFloat());
					break;								
				case 14:				
					avro::encode(e, v.get_ArrayOfDouble());
					break;								
				case 15:				
					avro::encode(e, v.get_ArrayOfString());
					break;								
				case 16:				
					avro::encode(e, v.get_bytes());
					break;								
				case 17:				
					avro::encode(e, v.get_AnySparseArray());
					break;								
			}			
		}		
		static void decode(Decoder& d, Energistics::Etp::v12::Datatypes::DataValueitem_t& v) {
		
			size_t n = d.decodeUnionIndex();
			if (n >= 18) { throw avro::Exception("Union index too big"); }
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
						Energistics::Etp::v12::Datatypes::ArrayOfNullableBoolean vv;
						avro::decode(d, vv);
						v.set_ArrayOfNullableBoolean(vv);
					}					
					break;								
				case 9:				
					{					
						Energistics::Etp::v12::Datatypes::ArrayOfInt vv;
						avro::decode(d, vv);
						v.set_ArrayOfInt(vv);
					}					
					break;								
				case 10:				
					{					
						Energistics::Etp::v12::Datatypes::ArrayOfNullableInt vv;
						avro::decode(d, vv);
						v.set_ArrayOfNullableInt(vv);
					}					
					break;								
				case 11:				
					{					
						Energistics::Etp::v12::Datatypes::ArrayOfLong vv;
						avro::decode(d, vv);
						v.set_ArrayOfLong(vv);
					}					
					break;								
				case 12:				
					{					
						Energistics::Etp::v12::Datatypes::ArrayOfNullableLong vv;
						avro::decode(d, vv);
						v.set_ArrayOfNullableLong(vv);
					}					
					break;								
				case 13:				
					{					
						Energistics::Etp::v12::Datatypes::ArrayOfFloat vv;
						avro::decode(d, vv);
						v.set_ArrayOfFloat(vv);
					}					
					break;								
				case 14:				
					{					
						Energistics::Etp::v12::Datatypes::ArrayOfDouble vv;
						avro::decode(d, vv);
						v.set_ArrayOfDouble(vv);
					}					
					break;								
				case 15:				
					{					
						Energistics::Etp::v12::Datatypes::ArrayOfString vv;
						avro::decode(d, vv);
						v.set_ArrayOfString(vv);
					}					
					break;								
				case 16:				
					{					
						std::string vv;
						avro::decode(d, vv);
						v.set_bytes(vv);
					}					
					break;								
				case 17:				
					{					
						Energistics::Etp::v12::Datatypes::AnySparseArray vv;
						avro::decode(d, vv);
						v.set_AnySparseArray(vv);
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
					Energistics::Etp::v12::Datatypes::DataValueitem_t item;
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Datatypes::DataValue> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Datatypes::DataValue& v) {		
			avro::encode(e, v.item);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Datatypes::DataValue& v) {		
			avro::decode(e, v.item);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Datatypes {			
				struct DataAttribute{				
					int32_t attributeId;
					Energistics::Etp::v12::Datatypes::DataValue attributeValue;
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Datatypes::DataAttribute> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Datatypes::DataAttribute& v) {		
			avro::encode(e, v.attributeId);
			avro::encode(e, v.attributeValue);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Datatypes::DataAttribute& v) {		
			avro::decode(e, v.attributeId);
			avro::decode(e, v.attributeValue);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Datatypes {			
				enum DataValueType {				
					typeBoolean=0,
					typeInt=1,
					typeLong=2,
					typeFloat=3,
					typeDouble=4,
					typeString=5,
					typeArrayOfBoolean=6,
					typeArrayOfInt=7,
					typeArrayOfLong=8,
					typeArrayOfFloat=9,
					typeArrayOfDouble=10,
					typeArrayOfString=11,
					typeBytes=12
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Datatypes::DataValueType> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Datatypes::DataValueType& v) {		
			e.encodeEnum(v);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Datatypes::DataValueType& v) {		
			v = static_cast<Energistics::Etp::v12::Datatypes::DataValueType>(e.decodeEnum());
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Datatypes {			
				struct AttributeMetadataRecord{				
					int32_t attributeId;
					std::string attributeName;
					Energistics::Etp::v12::Datatypes::DataValueType dataType;
					std::string description;
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Datatypes::AttributeMetadataRecord> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Datatypes::AttributeMetadataRecord& v) {		
			avro::encode(e, v.attributeId);
			avro::encode(e, v.attributeName);
			avro::encode(e, v.dataType);
			avro::encode(e, v.description);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Datatypes::AttributeMetadataRecord& v) {		
			avro::decode(e, v.attributeId);
			avro::decode(e, v.attributeName);
			avro::decode(e, v.dataType);
			avro::decode(e, v.description);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Datatypes {			
				enum EndpointCapabilityKind {				
					MaxDataObjectSize=0,
					MaxPartSize=1,
					MaxConcurrentMultipart=2,
					MaxMultipartMessageTimeInterval=3,
					MaxWebSocketFramePayloadSize=4,
					MaxWebSocketMessagePayloadSize=5,
					SupportsAlternateRequestUris=6,
					SupportsMessageHeaderExtension=7
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Datatypes::EndpointCapabilityKind> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Datatypes::EndpointCapabilityKind& v) {		
			e.encodeEnum(v);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Datatypes::EndpointCapabilityKind& v) {		
			v = static_cast<Energistics::Etp::v12::Datatypes::EndpointCapabilityKind>(e.decodeEnum());
		}		
	};	
}
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
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Datatypes::ErrorInfo> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Datatypes::ErrorInfo& v) {		
			avro::encode(e, v.message);
			avro::encode(e, v.code);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Datatypes::ErrorInfo& v) {		
			avro::decode(e, v.message);
			avro::decode(e, v.code);
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
					Energistics::Etp::v12::Datatypes::IndexValueitem_t item;
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Datatypes::IndexValue> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Datatypes::IndexValue& v) {		
			avro::encode(e, v.item);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Datatypes::IndexValue& v) {		
			avro::decode(e, v.item);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Datatypes {			
				struct MessageHeader{				
					int32_t protocol;
					int32_t messageType;
					int64_t correlationId;
					int64_t messageId;
					int32_t messageFlags;
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Datatypes::MessageHeader> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Datatypes::MessageHeader& v) {		
			avro::encode(e, v.protocol);
			avro::encode(e, v.messageType);
			avro::encode(e, v.correlationId);
			avro::encode(e, v.messageId);
			avro::encode(e, v.messageFlags);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Datatypes::MessageHeader& v) {		
			avro::decode(e, v.protocol);
			avro::decode(e, v.messageType);
			avro::decode(e, v.correlationId);
			avro::decode(e, v.messageId);
			avro::decode(e, v.messageFlags);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Datatypes {			
				struct MessageHeaderExtension{				
					std::map<std::string, Energistics::Etp::v12::Datatypes::DataValue> extension;
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Datatypes::MessageHeaderExtension> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Datatypes::MessageHeaderExtension& v) {		
			avro::encode(e, v.extension);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Datatypes::MessageHeaderExtension& v) {		
			avro::decode(e, v.extension);
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
					DEPRECATEDWitsmlSoap=8,
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
					Dataspace=24,
					SupportedTypes=25,
					WitsmlSoap=26
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
					MaxIndexCount=0,
					MaxDataItemCount=1,
					MaxResponseCount=2,
					ChangeDetectionPeriod=3,
					ChangeNotificationRetentionPeriod=4,
					GrowingTimeoutPeriod=5,
					TransactionTimeout=6,
					MaxDataArraySize=7,
					StreamingTimeoutPeriod=8,
					CascadeOnDataObjectTypes=9,
					FrameChangeDetectionPeriod=10,
					DeleteRetentionTime=11
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
				struct SupportedDataObject{				
					std::string qualifiedType;
					std::vector<std::string> dataObjectCapabilities;
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Datatypes::SupportedDataObject> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Datatypes::SupportedDataObject& v) {		
			avro::encode(e, v.qualifiedType);
			avro::encode(e, v.dataObjectCapabilities);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Datatypes::SupportedDataObject& v) {		
			avro::decode(e, v.qualifiedType);
			avro::decode(e, v.dataObjectCapabilities);
		}		
	};	
}
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
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Datatypes::Uuid> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Datatypes::Uuid& v) {		
			avro::encode(e, v.array);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Datatypes::Uuid& v) {		
			avro::decode(e, v.array);
		}		
	};	
}
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
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Datatypes::Version> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Datatypes::Version& v) {		
			avro::encode(e, v.major);
			avro::encode(e, v.minor);
			avro::encode(e, v.revision);
			avro::encode(e, v.patch);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Datatypes::Version& v) {		
			avro::decode(e, v.major);
			avro::decode(e, v.minor);
			avro::decode(e, v.revision);
			avro::decode(e, v.patch);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Datatypes {			
				struct SupportedProtocol{				
					int32_t protocol;
					Energistics::Etp::v12::Datatypes::Version protocolVersion;
					std::string role;
					std::map<std::string, Energistics::Etp::v12::Datatypes::DataValue> protocolCapabilities;
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Datatypes::SupportedProtocol> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Datatypes::SupportedProtocol& v) {		
			avro::encode(e, v.protocol);
			avro::encode(e, v.protocolVersion);
			avro::encode(e, v.role);
			avro::encode(e, v.protocolCapabilities);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Datatypes::SupportedProtocol& v) {		
			avro::decode(e, v.protocol);
			avro::decode(e, v.protocolVersion);
			avro::decode(e, v.role);
			avro::decode(e, v.protocolCapabilities);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Datatypes {			
				struct ServerCapabilities{				
					std::string applicationName;
					std::string applicationVersion;
					Energistics::Etp::v12::Datatypes::Contact contactInformation;
					std::vector<std::string> supportedCompression;
					std::vector<std::string> supportedEncodings;
					std::vector<std::string> supportedFormats;
					std::vector<Energistics::Etp::v12::Datatypes::SupportedDataObject> supportedDataObjects;
					std::vector<Energistics::Etp::v12::Datatypes::SupportedProtocol> supportedProtocols;
					std::map<std::string, Energistics::Etp::v12::Datatypes::DataValue> endpointCapabilities;
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Datatypes::ServerCapabilities> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Datatypes::ServerCapabilities& v) {		
			avro::encode(e, v.applicationName);
			avro::encode(e, v.applicationVersion);
			avro::encode(e, v.contactInformation);
			avro::encode(e, v.supportedCompression);
			avro::encode(e, v.supportedEncodings);
			avro::encode(e, v.supportedFormats);
			avro::encode(e, v.supportedDataObjects);
			avro::encode(e, v.supportedProtocols);
			avro::encode(e, v.endpointCapabilities);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Datatypes::ServerCapabilities& v) {		
			avro::decode(e, v.applicationName);
			avro::decode(e, v.applicationVersion);
			avro::decode(e, v.contactInformation);
			avro::decode(e, v.supportedCompression);
			avro::decode(e, v.supportedEncodings);
			avro::decode(e, v.supportedFormats);
			avro::decode(e, v.supportedDataObjects);
			avro::decode(e, v.supportedProtocols);
			avro::decode(e, v.endpointCapabilities);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Datatypes {			
				namespace ChannelData {				
					struct ChannelChangeRequestInfo{					
						int64_t sinceChangeTime;
						std::vector<int64_t> channelIds;
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Datatypes::ChannelData::ChannelChangeRequestInfo> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Datatypes::ChannelData::ChannelChangeRequestInfo& v) {		
			avro::encode(e, v.sinceChangeTime);
			avro::encode(e, v.channelIds);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Datatypes::ChannelData::ChannelChangeRequestInfo& v) {		
			avro::decode(e, v.sinceChangeTime);
			avro::decode(e, v.channelIds);
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
						Depth=1,
						Scalar=2,
						ElapsedTime=3
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
					struct ChannelSubscribeInfo{					
						int64_t channelId;
						Energistics::Etp::v12::Datatypes::IndexValue startIndex;
						bool dataChanges=false;
						boost::optional<int32_t> requestLatestIndexCount;
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Datatypes::ChannelData::ChannelSubscribeInfo> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Datatypes::ChannelData::ChannelSubscribeInfo& v) {		
			avro::encode(e, v.channelId);
			avro::encode(e, v.startIndex);
			avro::encode(e, v.dataChanges);
			avro::encode(e, v.requestLatestIndexCount);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Datatypes::ChannelData::ChannelSubscribeInfo& v) {		
			avro::decode(e, v.channelId);
			avro::decode(e, v.startIndex);
			avro::decode(e, v.dataChanges);
			avro::decode(e, v.requestLatestIndexCount);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Datatypes {			
				namespace ChannelData {				
					struct DataItem{					
						int64_t channelId;
						std::vector<Energistics::Etp::v12::Datatypes::IndexValue> indexes;
						Energistics::Etp::v12::Datatypes::DataValue value;
						std::vector<Energistics::Etp::v12::Datatypes::DataAttribute> valueAttributes;
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Datatypes::ChannelData::DataItem> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Datatypes::ChannelData::DataItem& v) {		
			avro::encode(e, v.channelId);
			avro::encode(e, v.indexes);
			avro::encode(e, v.value);
			avro::encode(e, v.valueAttributes);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Datatypes::ChannelData::DataItem& v) {		
			avro::decode(e, v.channelId);
			avro::decode(e, v.indexes);
			avro::decode(e, v.value);
			avro::decode(e, v.valueAttributes);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Datatypes {			
				namespace ChannelData {				
					struct FramePoint{					
						Energistics::Etp::v12::Datatypes::DataValue value;
						std::vector<Energistics::Etp::v12::Datatypes::DataAttribute> valueAttributes;
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Datatypes::ChannelData::FramePoint> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Datatypes::ChannelData::FramePoint& v) {		
			avro::encode(e, v.value);
			avro::encode(e, v.valueAttributes);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Datatypes::ChannelData::FramePoint& v) {		
			avro::decode(e, v.value);
			avro::decode(e, v.valueAttributes);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Datatypes {			
				namespace ChannelData {				
					struct FrameRow{					
						std::vector<Energistics::Etp::v12::Datatypes::IndexValue> indexes;
						std::vector<Energistics::Etp::v12::Datatypes::ChannelData::FramePoint> points;
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Datatypes::ChannelData::FrameRow> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Datatypes::ChannelData::FrameRow& v) {		
			avro::encode(e, v.indexes);
			avro::encode(e, v.points);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Datatypes::ChannelData::FrameRow& v) {		
			avro::decode(e, v.indexes);
			avro::decode(e, v.points);
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
				namespace ChannelData {				
					struct TruncateInfo{					
						int64_t channelId;
						Energistics::Etp::v12::Datatypes::IndexValue newEndIndex;
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Datatypes::ChannelData::TruncateInfo> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Datatypes::ChannelData::TruncateInfo& v) {		
			avro::encode(e, v.channelId);
			avro::encode(e, v.newEndIndex);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Datatypes::ChannelData::TruncateInfo& v) {		
			avro::decode(e, v.channelId);
			avro::decode(e, v.newEndIndex);
		}		
	};	
}
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
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Datatypes::DataArrayTypes::DataArray> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Datatypes::DataArrayTypes::DataArray& v) {		
			avro::encode(e, v.dimensions);
			avro::encode(e, v.data);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Datatypes::DataArrayTypes::DataArray& v) {		
			avro::decode(e, v.dimensions);
			avro::decode(e, v.data);
		}		
	};	
}
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
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Datatypes::DataArrayTypes::DataArrayIdentifier> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Datatypes::DataArrayTypes::DataArrayIdentifier& v) {		
			avro::encode(e, v.uri);
			avro::encode(e, v.pathInResource);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Datatypes::DataArrayTypes::DataArrayIdentifier& v) {		
			avro::decode(e, v.uri);
			avro::decode(e, v.pathInResource);
		}		
	};	
}
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
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Datatypes::DataArrayTypes::DataArrayMetadata> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Datatypes::DataArrayTypes::DataArrayMetadata& v) {		
			avro::encode(e, v.dimensions);
			avro::encode(e, v.arrayType);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Datatypes::DataArrayTypes::DataArrayMetadata& v) {		
			avro::decode(e, v.dimensions);
			avro::decode(e, v.arrayType);
		}		
	};	
}
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
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Datatypes::DataArrayTypes::GetDataSubarraysType> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Datatypes::DataArrayTypes::GetDataSubarraysType& v) {		
			avro::encode(e, v.uid);
			avro::encode(e, v.starts);
			avro::encode(e, v.counts);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Datatypes::DataArrayTypes::GetDataSubarraysType& v) {		
			avro::decode(e, v.uid);
			avro::decode(e, v.starts);
			avro::decode(e, v.counts);
		}		
	};	
}
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
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Datatypes::DataArrayTypes::PutDataArraysType> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Datatypes::DataArrayTypes::PutDataArraysType& v) {		
			avro::encode(e, v.uid);
			avro::encode(e, v.array);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Datatypes::DataArrayTypes::PutDataArraysType& v) {		
			avro::decode(e, v.uid);
			avro::decode(e, v.array);
		}		
	};	
}
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
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Datatypes::DataArrayTypes::PutDataSubarraysType> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Datatypes::DataArrayTypes::PutDataSubarraysType& v) {		
			avro::encode(e, v.uid);
			avro::encode(e, v.data);
			avro::encode(e, v.starts);
			avro::encode(e, v.counts);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Datatypes::DataArrayTypes::PutDataSubarraysType& v) {		
			avro::decode(e, v.uid);
			avro::decode(e, v.data);
			avro::decode(e, v.starts);
			avro::decode(e, v.counts);
		}		
	};	
}
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
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Datatypes::DataArrayTypes::PutUninitializedDataArrayType> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Datatypes::DataArrayTypes::PutUninitializedDataArrayType& v) {		
			avro::encode(e, v.uid);
			avro::encode(e, v.metadata);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Datatypes::DataArrayTypes::PutUninitializedDataArrayType& v) {		
			avro::decode(e, v.uid);
			avro::decode(e, v.metadata);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Datatypes {			
				namespace Object {				
					enum ActiveStatusKind {					
						Active=0,
						Inactive=1
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Datatypes::Object::ActiveStatusKind> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Datatypes::Object::ActiveStatusKind& v) {		
			e.encodeEnum(v);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Datatypes::Object::ActiveStatusKind& v) {		
			v = static_cast<Energistics::Etp::v12::Datatypes::Object::ActiveStatusKind>(e.decodeEnum());
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Datatypes {			
				namespace ChannelData {				
					struct FrameChannelMetadataRecord{					
						std::string uri;
						std::string channelName;
						Energistics::Etp::v12::Datatypes::DataValueType dataType;
						std::string uom;
						std::string measureClass;
						Energistics::Etp::v12::Datatypes::Object::ActiveStatusKind status;
						std::string source;
						std::vector<int32_t> axisVectorLengths;
						std::map<std::string, Energistics::Etp::v12::Datatypes::DataValue> customData;
						std::vector<Energistics::Etp::v12::Datatypes::AttributeMetadataRecord> attributeMetadata;
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Datatypes::ChannelData::FrameChannelMetadataRecord> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Datatypes::ChannelData::FrameChannelMetadataRecord& v) {		
			avro::encode(e, v.uri);
			avro::encode(e, v.channelName);
			avro::encode(e, v.dataType);
			avro::encode(e, v.uom);
			avro::encode(e, v.measureClass);
			avro::encode(e, v.status);
			avro::encode(e, v.source);
			avro::encode(e, v.axisVectorLengths);
			avro::encode(e, v.customData);
			avro::encode(e, v.attributeMetadata);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Datatypes::ChannelData::FrameChannelMetadataRecord& v) {		
			avro::decode(e, v.uri);
			avro::decode(e, v.channelName);
			avro::decode(e, v.dataType);
			avro::decode(e, v.uom);
			avro::decode(e, v.measureClass);
			avro::decode(e, v.status);
			avro::decode(e, v.source);
			avro::decode(e, v.axisVectorLengths);
			avro::decode(e, v.customData);
			avro::decode(e, v.attributeMetadata);
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
					struct Dataspace{					
						std::string uri;
						std::string path;
						boost::optional<int64_t> lastChanged;
						std::map<std::string, Energistics::Etp::v12::Datatypes::DataValue> customData;
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Datatypes::Object::Dataspace> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Datatypes::Object::Dataspace& v) {		
			avro::encode(e, v.uri);
			avro::encode(e, v.path);
			avro::encode(e, v.lastChanged);
			avro::encode(e, v.customData);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Datatypes::Object::Dataspace& v) {		
			avro::decode(e, v.uri);
			avro::decode(e, v.path);
			avro::decode(e, v.lastChanged);
			avro::decode(e, v.customData);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Datatypes {			
				namespace Object {				
					struct DeletedResource{					
						std::string uri;
						std::string dataObjectType;
						int64_t deletedTime;
						std::map<std::string, Energistics::Etp::v12::Datatypes::DataValue> customData;
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Datatypes::Object::DeletedResource> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Datatypes::Object::DeletedResource& v) {		
			avro::encode(e, v.uri);
			avro::encode(e, v.dataObjectType);
			avro::encode(e, v.deletedTime);
			avro::encode(e, v.customData);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Datatypes::Object::DeletedResource& v) {		
			avro::decode(e, v.uri);
			avro::decode(e, v.dataObjectType);
			avro::decode(e, v.deletedTime);
			avro::decode(e, v.customData);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Datatypes {			
				namespace Object {				
					struct IndexInterval{					
						Energistics::Etp::v12::Datatypes::IndexValue startIndex;
						Energistics::Etp::v12::Datatypes::IndexValue endIndex;
						std::string uom;
						std::string depthDatum;
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Datatypes::Object::IndexInterval> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Datatypes::Object::IndexInterval& v) {		
			avro::encode(e, v.startIndex);
			avro::encode(e, v.endIndex);
			avro::encode(e, v.uom);
			avro::encode(e, v.depthDatum);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Datatypes::Object::IndexInterval& v) {		
			avro::decode(e, v.startIndex);
			avro::decode(e, v.endIndex);
			avro::decode(e, v.uom);
			avro::decode(e, v.depthDatum);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Datatypes {			
				namespace ChannelData {				
					struct ChannelChangeAnnotation{					
						int64_t changeTime;
						Energistics::Etp::v12::Datatypes::Object::IndexInterval interval;
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Datatypes::ChannelData::ChannelChangeAnnotation> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Datatypes::ChannelData::ChannelChangeAnnotation& v) {		
			avro::encode(e, v.changeTime);
			avro::encode(e, v.interval);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Datatypes::ChannelData::ChannelChangeAnnotation& v) {		
			avro::decode(e, v.changeTime);
			avro::decode(e, v.interval);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Datatypes {			
				namespace ChannelData {				
					struct ChannelChangeResponseInfo{					
						int64_t responseTimestamp;
						std::map<std::string, std::vector<Energistics::Etp::v12::Datatypes::ChannelData::ChannelChangeAnnotation> > channelChanges;
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Datatypes::ChannelData::ChannelChangeResponseInfo> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Datatypes::ChannelData::ChannelChangeResponseInfo& v) {		
			avro::encode(e, v.responseTimestamp);
			avro::encode(e, v.channelChanges);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Datatypes::ChannelData::ChannelChangeResponseInfo& v) {		
			avro::decode(e, v.responseTimestamp);
			avro::decode(e, v.channelChanges);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Datatypes {			
				namespace ChannelData {				
					struct ChannelRangeInfo{					
						std::vector<int64_t> channelIds;
						Energistics::Etp::v12::Datatypes::Object::IndexInterval interval;
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Datatypes::ChannelData::ChannelRangeInfo> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Datatypes::ChannelData::ChannelRangeInfo& v) {		
			avro::encode(e, v.channelIds);
			avro::encode(e, v.interval);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Datatypes::ChannelData::ChannelRangeInfo& v) {		
			avro::decode(e, v.channelIds);
			avro::decode(e, v.interval);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Datatypes {			
				namespace ChannelData {				
					struct IndexMetadataRecord{					
						Energistics::Etp::v12::Datatypes::ChannelData::ChannelIndexKind indexKind;
						Energistics::Etp::v12::Datatypes::Object::IndexInterval interval;
						Energistics::Etp::v12::Datatypes::ChannelData::IndexDirection direction;
						std::string name;
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Datatypes::ChannelData::IndexMetadataRecord> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Datatypes::ChannelData::IndexMetadataRecord& v) {		
			avro::encode(e, v.indexKind);
			avro::encode(e, v.interval);
			avro::encode(e, v.direction);
			avro::encode(e, v.name);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Datatypes::ChannelData::IndexMetadataRecord& v) {		
			avro::decode(e, v.indexKind);
			avro::decode(e, v.interval);
			avro::decode(e, v.direction);
			avro::decode(e, v.name);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Datatypes {			
				namespace ChannelData {				
					struct ChannelMetadataRecord{					
						std::string uri;
						int64_t id;
						std::vector<Energistics::Etp::v12::Datatypes::ChannelData::IndexMetadataRecord> indexes;
						std::string channelName;
						Energistics::Etp::v12::Datatypes::DataValueType dataType;
						std::string uom;
						std::string measureClass;
						Energistics::Etp::v12::Datatypes::Object::ActiveStatusKind status;
						std::string source;
						std::vector<int32_t> axisVectorLengths;
						std::map<std::string, Energistics::Etp::v12::Datatypes::DataValue> customData;
						std::vector<Energistics::Etp::v12::Datatypes::AttributeMetadataRecord> attributeMetadata;
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Datatypes::ChannelData::ChannelMetadataRecord> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Datatypes::ChannelData::ChannelMetadataRecord& v) {		
			avro::encode(e, v.uri);
			avro::encode(e, v.id);
			avro::encode(e, v.indexes);
			avro::encode(e, v.channelName);
			avro::encode(e, v.dataType);
			avro::encode(e, v.uom);
			avro::encode(e, v.measureClass);
			avro::encode(e, v.status);
			avro::encode(e, v.source);
			avro::encode(e, v.axisVectorLengths);
			avro::encode(e, v.customData);
			avro::encode(e, v.attributeMetadata);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Datatypes::ChannelData::ChannelMetadataRecord& v) {		
			avro::decode(e, v.uri);
			avro::decode(e, v.id);
			avro::decode(e, v.indexes);
			avro::decode(e, v.channelName);
			avro::decode(e, v.dataType);
			avro::decode(e, v.uom);
			avro::decode(e, v.measureClass);
			avro::decode(e, v.status);
			avro::decode(e, v.source);
			avro::decode(e, v.axisVectorLengths);
			avro::decode(e, v.customData);
			avro::decode(e, v.attributeMetadata);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Datatypes {			
				namespace ChannelData {				
					struct OpenChannelInfo{					
						Energistics::Etp::v12::Datatypes::ChannelData::ChannelMetadataRecord metadata;
						bool preferRealtime=false;
						bool dataChanges=false;
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Datatypes::ChannelData::OpenChannelInfo> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Datatypes::ChannelData::OpenChannelInfo& v) {		
			avro::encode(e, v.metadata);
			avro::encode(e, v.preferRealtime);
			avro::encode(e, v.dataChanges);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Datatypes::ChannelData::OpenChannelInfo& v) {		
			avro::decode(e, v.metadata);
			avro::decode(e, v.preferRealtime);
			avro::decode(e, v.dataChanges);
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
						authorized=2,
						joined=3,
						unjoined=4
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
					struct ObjectPart{					
						std::string uid;
						std::string data;
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Datatypes::Object::ObjectPart> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Datatypes::Object::ObjectPart& v) {		
			avro::encode(e, v.uid);
			avro::encode(e, v.data);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Datatypes::Object::ObjectPart& v) {		
			avro::decode(e, v.uid);
			avro::decode(e, v.data);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Datatypes {			
				namespace Object {				
					struct PartsMetadataInfo{					
						std::string uri;
						Energistics::Etp::v12::Datatypes::ChannelData::ChannelIndexKind indexKind;
						std::string name;
						Energistics::Etp::v12::Datatypes::Object::IndexInterval indexInterval;
						std::map<std::string, Energistics::Etp::v12::Datatypes::DataValue> customData;
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Datatypes::Object::PartsMetadataInfo> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Datatypes::Object::PartsMetadataInfo& v) {		
			avro::encode(e, v.uri);
			avro::encode(e, v.indexKind);
			avro::encode(e, v.name);
			avro::encode(e, v.indexInterval);
			avro::encode(e, v.customData);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Datatypes::Object::PartsMetadataInfo& v) {		
			avro::decode(e, v.uri);
			avro::decode(e, v.indexKind);
			avro::decode(e, v.name);
			avro::decode(e, v.indexInterval);
			avro::decode(e, v.customData);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Datatypes {			
				namespace Object {				
					struct PutResponse{					
						std::vector<std::string> createdContainedObjectUris;
						std::vector<std::string> deletedContainedObjectUris;
						std::vector<std::string> joinedContainedObjectUris;
						std::vector<std::string> unjoinedContainedObjectUris;
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Datatypes::Object::PutResponse> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Datatypes::Object::PutResponse& v) {		
			avro::encode(e, v.createdContainedObjectUris);
			avro::encode(e, v.deletedContainedObjectUris);
			avro::encode(e, v.joinedContainedObjectUris);
			avro::encode(e, v.unjoinedContainedObjectUris);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Datatypes::Object::PutResponse& v) {		
			avro::decode(e, v.createdContainedObjectUris);
			avro::decode(e, v.deletedContainedObjectUris);
			avro::decode(e, v.joinedContainedObjectUris);
			avro::decode(e, v.unjoinedContainedObjectUris);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Datatypes {			
				namespace Object {				
					enum RelationshipKind {					
						Primary=0,
						Secondary=1,
						Both=2
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Datatypes::Object::RelationshipKind> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Datatypes::Object::RelationshipKind& v) {		
			e.encodeEnum(v);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Datatypes::Object::RelationshipKind& v) {		
			v = static_cast<Energistics::Etp::v12::Datatypes::Object::RelationshipKind>(e.decodeEnum());
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Datatypes {			
				namespace Object {				
					struct ContextInfo{					
						std::string uri;
						int32_t depth;
						std::vector<std::string> dataObjectTypes;
						Energistics::Etp::v12::Datatypes::Object::RelationshipKind navigableEdges;
						bool includeSecondaryTargets=false;
						bool includeSecondarySources=false;
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Datatypes::Object::ContextInfo> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Datatypes::Object::ContextInfo& v) {		
			avro::encode(e, v.uri);
			avro::encode(e, v.depth);
			avro::encode(e, v.dataObjectTypes);
			avro::encode(e, v.navigableEdges);
			avro::encode(e, v.includeSecondaryTargets);
			avro::encode(e, v.includeSecondarySources);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Datatypes::Object::ContextInfo& v) {		
			avro::decode(e, v.uri);
			avro::decode(e, v.depth);
			avro::decode(e, v.dataObjectTypes);
			avro::decode(e, v.navigableEdges);
			avro::decode(e, v.includeSecondaryTargets);
			avro::decode(e, v.includeSecondarySources);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Datatypes {			
				namespace Object {				
					struct Edge{					
						std::string sourceUri;
						std::string targetUri;
						Energistics::Etp::v12::Datatypes::Object::RelationshipKind relationshipKind;
						std::map<std::string, Energistics::Etp::v12::Datatypes::DataValue> customData;
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Datatypes::Object::Edge> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Datatypes::Object::Edge& v) {		
			avro::encode(e, v.sourceUri);
			avro::encode(e, v.targetUri);
			avro::encode(e, v.relationshipKind);
			avro::encode(e, v.customData);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Datatypes::Object::Edge& v) {		
			avro::decode(e, v.sourceUri);
			avro::decode(e, v.targetUri);
			avro::decode(e, v.relationshipKind);
			avro::decode(e, v.customData);
		}		
	};	
}
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
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Datatypes::Object::Resource> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Datatypes::Object::Resource& v) {		
			avro::encode(e, v.uri);
			avro::encode(e, v.alternateUris);
			avro::encode(e, v.dataObjectType);
			avro::encode(e, v.name);
			avro::encode(e, v.sourceCount);
			avro::encode(e, v.targetCount);
			avro::encode(e, v.lastChanged);
			avro::encode(e, v.storeLastWrite);
			avro::encode(e, v.customData);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Datatypes::Object::Resource& v) {		
			avro::decode(e, v.uri);
			avro::decode(e, v.alternateUris);
			avro::decode(e, v.dataObjectType);
			avro::decode(e, v.name);
			avro::decode(e, v.sourceCount);
			avro::decode(e, v.targetCount);
			avro::decode(e, v.lastChanged);
			avro::decode(e, v.storeLastWrite);
			avro::decode(e, v.customData);
		}		
	};	
}
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
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Datatypes::Object::DataObject> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Datatypes::Object::DataObject& v) {		
			avro::encode(e, v.resource);
			avro::encode(e, v.format);
			avro::encode(e, v.blobId);
			avro::encode(e, v.data);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Datatypes::Object::DataObject& v) {		
			avro::decode(e, v.resource);
			avro::decode(e, v.format);
			avro::decode(e, v.blobId);
			avro::decode(e, v.data);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Datatypes {			
				namespace Object {				
					struct ObjectChange{					
						Energistics::Etp::v12::Datatypes::Object::ObjectChangeKind changeKind;
						int64_t changeTime;
						Energistics::Etp::v12::Datatypes::Object::DataObject dataObject;
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Datatypes::Object::ObjectChange> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Datatypes::Object::ObjectChange& v) {		
			avro::encode(e, v.changeKind);
			avro::encode(e, v.changeTime);
			avro::encode(e, v.dataObject);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Datatypes::Object::ObjectChange& v) {		
			avro::decode(e, v.changeKind);
			avro::decode(e, v.changeTime);
			avro::decode(e, v.dataObject);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Datatypes {			
				namespace Object {				
					struct SubscriptionInfo{					
						Energistics::Etp::v12::Datatypes::Object::ContextInfo context;
						Energistics::Etp::v12::Datatypes::Object::ContextScopeKind scope;
						Energistics::Etp::v12::Datatypes::Uuid requestUuid;
						int64_t startTime;
						bool includeObjectData=false;
						std::string format;
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Datatypes::Object::SubscriptionInfo> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Datatypes::Object::SubscriptionInfo& v) {		
			avro::encode(e, v.context);
			avro::encode(e, v.scope);
			avro::encode(e, v.requestUuid);
			avro::encode(e, v.startTime);
			avro::encode(e, v.includeObjectData);
			avro::encode(e, v.format);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Datatypes::Object::SubscriptionInfo& v) {		
			avro::decode(e, v.context);
			avro::decode(e, v.scope);
			avro::decode(e, v.requestUuid);
			avro::decode(e, v.startTime);
			avro::decode(e, v.includeObjectData);
			avro::decode(e, v.format);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Datatypes {			
				namespace Object {				
					struct SupportedType{					
						std::string dataObjectType;
						boost::optional<int32_t> objectCount;
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Datatypes::Object::SupportedType> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Datatypes::Object::SupportedType& v) {		
			avro::encode(e, v.dataObjectType);
			avro::encode(e, v.objectCount);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Datatypes::Object::SupportedType& v) {		
			avro::decode(e, v.dataObjectType);
			avro::decode(e, v.objectCount);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace PrivateProtocols {			
				namespace WitsmlSoap {				
					struct WMLS_AddToStore{					
						std::string WMLtypeIn;
						std::string XMLin;
						std::string OptionsIn;
						std::string CapabilitiesIn;
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
			avro::encode(e, v.WMLtypeIn);
			avro::encode(e, v.XMLin);
			avro::encode(e, v.OptionsIn);
			avro::encode(e, v.CapabilitiesIn);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::PrivateProtocols::WitsmlSoap::WMLS_AddToStore& v) {		
			avro::decode(e, v.WMLtypeIn);
			avro::decode(e, v.XMLin);
			avro::decode(e, v.OptionsIn);
			avro::decode(e, v.CapabilitiesIn);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace PrivateProtocols {			
				namespace WitsmlSoap {				
					struct WMLS_AddToStoreResponse{					
						int32_t Result;
						std::string SuppMsgOut;
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
			avro::encode(e, v.Result);
			avro::encode(e, v.SuppMsgOut);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::PrivateProtocols::WitsmlSoap::WMLS_AddToStoreResponse& v) {		
			avro::decode(e, v.Result);
			avro::decode(e, v.SuppMsgOut);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace PrivateProtocols {			
				namespace WitsmlSoap {				
					struct WMLS_DeleteFromStore{					
						std::string WMLtypeIn;
						std::string XMLin;
						std::string OptionsIn;
						std::string CapabilitiesIn;
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
			avro::encode(e, v.WMLtypeIn);
			avro::encode(e, v.XMLin);
			avro::encode(e, v.OptionsIn);
			avro::encode(e, v.CapabilitiesIn);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::PrivateProtocols::WitsmlSoap::WMLS_DeleteFromStore& v) {		
			avro::decode(e, v.WMLtypeIn);
			avro::decode(e, v.XMLin);
			avro::decode(e, v.OptionsIn);
			avro::decode(e, v.CapabilitiesIn);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace PrivateProtocols {			
				namespace WitsmlSoap {				
					struct WMLS_DeleteFromStoreResponse{					
						int32_t Result;
						std::string SuppMsgOut;
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
			avro::encode(e, v.Result);
			avro::encode(e, v.SuppMsgOut);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::PrivateProtocols::WitsmlSoap::WMLS_DeleteFromStoreResponse& v) {		
			avro::decode(e, v.Result);
			avro::decode(e, v.SuppMsgOut);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace PrivateProtocols {			
				namespace WitsmlSoap {				
					struct WMLS_GetBaseMsg{					
						int32_t ReturnValueIn;
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
			avro::encode(e, v.ReturnValueIn);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::PrivateProtocols::WitsmlSoap::WMLS_GetBaseMsg& v) {		
			avro::decode(e, v.ReturnValueIn);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace PrivateProtocols {			
				namespace WitsmlSoap {				
					struct WMLS_GetBaseMsgResponse{					
						std::string Result;
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
			avro::encode(e, v.Result);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::PrivateProtocols::WitsmlSoap::WMLS_GetBaseMsgResponse& v) {		
			avro::decode(e, v.Result);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace PrivateProtocols {			
				namespace WitsmlSoap {				
					struct WMLS_GetCap{					
						std::string OptionsIn;
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
			avro::encode(e, v.OptionsIn);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::PrivateProtocols::WitsmlSoap::WMLS_GetCap& v) {		
			avro::decode(e, v.OptionsIn);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace PrivateProtocols {			
				namespace WitsmlSoap {				
					struct WMLS_GetCapResponse{					
						int32_t Result;
						std::string CapabilitiesOut;
						std::string SuppMsgOut;
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
			avro::encode(e, v.Result);
			avro::encode(e, v.CapabilitiesOut);
			avro::encode(e, v.SuppMsgOut);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::PrivateProtocols::WitsmlSoap::WMLS_GetCapResponse& v) {		
			avro::decode(e, v.Result);
			avro::decode(e, v.CapabilitiesOut);
			avro::decode(e, v.SuppMsgOut);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace PrivateProtocols {			
				namespace WitsmlSoap {				
					struct WMLS_GetFromStore{					
						std::string WMLtypeIn;
						std::string XMLin;
						std::string OptionsIn;
						std::string CapabilitiesIn;
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
			avro::encode(e, v.WMLtypeIn);
			avro::encode(e, v.XMLin);
			avro::encode(e, v.OptionsIn);
			avro::encode(e, v.CapabilitiesIn);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::PrivateProtocols::WitsmlSoap::WMLS_GetFromStore& v) {		
			avro::decode(e, v.WMLtypeIn);
			avro::decode(e, v.XMLin);
			avro::decode(e, v.OptionsIn);
			avro::decode(e, v.CapabilitiesIn);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace PrivateProtocols {			
				namespace WitsmlSoap {				
					struct WMLS_GetFromStoreResponse{					
						int32_t Result;
						std::string XMLout;
						std::string SuppMsgOut;
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
			avro::encode(e, v.Result);
			avro::encode(e, v.XMLout);
			avro::encode(e, v.SuppMsgOut);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::PrivateProtocols::WitsmlSoap::WMLS_GetFromStoreResponse& v) {		
			avro::decode(e, v.Result);
			avro::decode(e, v.XMLout);
			avro::decode(e, v.SuppMsgOut);
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
		static void encode(Encoder&, const Energistics::Etp::v12::PrivateProtocols::WitsmlSoap::WMLS_GetVersion&) {		
		}		
		static void decode(Decoder&, Energistics::Etp::v12::PrivateProtocols::WitsmlSoap::WMLS_GetVersion&) {		
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace PrivateProtocols {			
				namespace WitsmlSoap {				
					struct WMLS_GetVersionResponse{					
						std::string Result;
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
			avro::encode(e, v.Result);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::PrivateProtocols::WitsmlSoap::WMLS_GetVersionResponse& v) {		
			avro::decode(e, v.Result);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace PrivateProtocols {			
				namespace WitsmlSoap {				
					struct WMLS_UpdateInStore{					
						std::string WMLtypeIn;
						std::string XMLin;
						std::string OptionsIn;
						std::string CapabilitiesIn;
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
			avro::encode(e, v.WMLtypeIn);
			avro::encode(e, v.XMLin);
			avro::encode(e, v.OptionsIn);
			avro::encode(e, v.CapabilitiesIn);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::PrivateProtocols::WitsmlSoap::WMLS_UpdateInStore& v) {		
			avro::decode(e, v.WMLtypeIn);
			avro::decode(e, v.XMLin);
			avro::decode(e, v.OptionsIn);
			avro::decode(e, v.CapabilitiesIn);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace PrivateProtocols {			
				namespace WitsmlSoap {				
					struct WMLS_UpdateInStoreResponse{					
						int32_t Result;
						std::string SuppMsgOut;
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
			avro::encode(e, v.Result);
			avro::encode(e, v.SuppMsgOut);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::PrivateProtocols::WitsmlSoap::WMLS_UpdateInStoreResponse& v) {		
			avro::decode(e, v.Result);
			avro::decode(e, v.SuppMsgOut);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace ChannelDataFrame {				
					struct CancelGetFrame{					
						Energistics::Etp::v12::Datatypes::Uuid requestUuid;
						static const int messageTypeId=5;
						static const int protocolId=Energistics::Etp::v12::Datatypes::ChannelDataFrame;
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::ChannelDataFrame::CancelGetFrame> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::ChannelDataFrame::CancelGetFrame& v) {		
			avro::encode(e, v.requestUuid);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::ChannelDataFrame::CancelGetFrame& v) {		
			avro::decode(e, v.requestUuid);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace ChannelDataFrame {				
					struct GetFrame{					
						std::string uri;
						Energistics::Etp::v12::Datatypes::Object::IndexInterval requestedInterval;
						Energistics::Etp::v12::Datatypes::Uuid requestUuid;
						static const int messageTypeId=3;
						static const int protocolId=Energistics::Etp::v12::Datatypes::ChannelDataFrame;
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::ChannelDataFrame::GetFrame> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::ChannelDataFrame::GetFrame& v) {		
			avro::encode(e, v.uri);
			avro::encode(e, v.requestedInterval);
			avro::encode(e, v.requestUuid);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::ChannelDataFrame::GetFrame& v) {		
			avro::decode(e, v.uri);
			avro::decode(e, v.requestedInterval);
			avro::decode(e, v.requestUuid);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace ChannelDataFrame {				
					struct GetFrameMetadata{					
						std::string uri;
						static const int messageTypeId=1;
						static const int protocolId=Energistics::Etp::v12::Datatypes::ChannelDataFrame;
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::ChannelDataFrame::GetFrameMetadata> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::ChannelDataFrame::GetFrameMetadata& v) {		
			avro::encode(e, v.uri);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::ChannelDataFrame::GetFrameMetadata& v) {		
			avro::decode(e, v.uri);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace ChannelDataFrame {				
					struct GetFrameMetadataResponse{					
						std::string uri;
						std::vector<Energistics::Etp::v12::Datatypes::ChannelData::IndexMetadataRecord> indexes;
						std::vector<Energistics::Etp::v12::Datatypes::ChannelData::FrameChannelMetadataRecord> channels;
						static const int messageTypeId=2;
						static const int protocolId=Energistics::Etp::v12::Datatypes::ChannelDataFrame;
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::ChannelDataFrame::GetFrameMetadataResponse> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::ChannelDataFrame::GetFrameMetadataResponse& v) {		
			avro::encode(e, v.uri);
			avro::encode(e, v.indexes);
			avro::encode(e, v.channels);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::ChannelDataFrame::GetFrameMetadataResponse& v) {		
			avro::decode(e, v.uri);
			avro::decode(e, v.indexes);
			avro::decode(e, v.channels);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace ChannelDataFrame {				
					struct GetFrameResponseHeader{					
						std::vector<std::string> channelUris;
						static const int messageTypeId=4;
						static const int protocolId=Energistics::Etp::v12::Datatypes::ChannelDataFrame;
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::ChannelDataFrame::GetFrameResponseHeader> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::ChannelDataFrame::GetFrameResponseHeader& v) {		
			avro::encode(e, v.channelUris);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::ChannelDataFrame::GetFrameResponseHeader& v) {		
			avro::decode(e, v.channelUris);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace ChannelDataFrame {				
					struct GetFrameResponseRows{					
						std::vector<Energistics::Etp::v12::Datatypes::ChannelData::FrameRow> frame;
						static const int messageTypeId=6;
						static const int protocolId=Energistics::Etp::v12::Datatypes::ChannelDataFrame;
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::ChannelDataFrame::GetFrameResponseRows> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::ChannelDataFrame::GetFrameResponseRows& v) {		
			avro::encode(e, v.frame);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::ChannelDataFrame::GetFrameResponseRows& v) {		
			avro::decode(e, v.frame);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace ChannelDataLoad {				
					struct ChannelData{					
						std::vector<Energistics::Etp::v12::Datatypes::ChannelData::DataItem> data;
						static const int messageTypeId=4;
						static const int protocolId=Energistics::Etp::v12::Datatypes::ChannelDataLoad;
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::ChannelDataLoad::ChannelData> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::ChannelDataLoad::ChannelData& v) {		
			avro::encode(e, v.data);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::ChannelDataLoad::ChannelData& v) {		
			avro::decode(e, v.data);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace ChannelDataLoad {				
					struct ChannelsClosed{					
						std::map<std::string, int64_t> id;
						static const int messageTypeId=7;
						static const int protocolId=Energistics::Etp::v12::Datatypes::ChannelDataLoad;
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::ChannelDataLoad::ChannelsClosed> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::ChannelDataLoad::ChannelsClosed& v) {		
			avro::encode(e, v.id);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::ChannelDataLoad::ChannelsClosed& v) {		
			avro::decode(e, v.id);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace ChannelDataLoad {				
					struct CloseChannels{					
						std::map<std::string, int64_t> id;
						static const int messageTypeId=3;
						static const int protocolId=Energistics::Etp::v12::Datatypes::ChannelDataLoad;
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::ChannelDataLoad::CloseChannels> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::ChannelDataLoad::CloseChannels& v) {		
			avro::encode(e, v.id);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::ChannelDataLoad::CloseChannels& v) {		
			avro::decode(e, v.id);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace ChannelDataLoad {				
					struct OpenChannelsResponse{					
						std::map<std::string, Energistics::Etp::v12::Datatypes::ChannelData::OpenChannelInfo> channels;
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
			avro::encode(e, v.channels);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::ChannelDataLoad::OpenChannelsResponse& v) {		
			avro::decode(e, v.channels);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace ChannelDataLoad {				
					struct OpenChannels{					
						std::map<std::string, std::string> uris;
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
			avro::encode(e, v.uris);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::ChannelDataLoad::OpenChannels& v) {		
			avro::decode(e, v.uris);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace ChannelDataLoad {				
					struct ReplaceRange{					
						Energistics::Etp::v12::Datatypes::Object::IndexInterval changedInterval;
						std::vector<int64_t> channelIds;
						std::vector<Energistics::Etp::v12::Datatypes::ChannelData::DataItem> data;
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
			avro::encode(e, v.changedInterval);
			avro::encode(e, v.channelIds);
			avro::encode(e, v.data);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::ChannelDataLoad::ReplaceRange& v) {		
			avro::decode(e, v.changedInterval);
			avro::decode(e, v.channelIds);
			avro::decode(e, v.data);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace ChannelDataLoad {				
					struct ReplaceRangeResponse{					
						std::map<std::string, int64_t> channelChangeTime;
						static const int messageTypeId=8;
						static const int protocolId=Energistics::Etp::v12::Datatypes::ChannelDataLoad;
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::ChannelDataLoad::ReplaceRangeResponse> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::ChannelDataLoad::ReplaceRangeResponse& v) {		
			avro::encode(e, v.channelChangeTime);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::ChannelDataLoad::ReplaceRangeResponse& v) {		
			avro::decode(e, v.channelChangeTime);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace ChannelDataLoad {				
					struct TruncateChannels{					
						std::map<std::string, Energistics::Etp::v12::Datatypes::ChannelData::TruncateInfo> channels;
						static const int messageTypeId=9;
						static const int protocolId=Energistics::Etp::v12::Datatypes::ChannelDataLoad;
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::ChannelDataLoad::TruncateChannels> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::ChannelDataLoad::TruncateChannels& v) {		
			avro::encode(e, v.channels);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::ChannelDataLoad::TruncateChannels& v) {		
			avro::decode(e, v.channels);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace ChannelDataLoad {				
					struct TruncateChannelsResponse{					
						std::map<std::string, int64_t> channelsTruncatedTime;
						static const int messageTypeId=10;
						static const int protocolId=Energistics::Etp::v12::Datatypes::ChannelDataLoad;
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::ChannelDataLoad::TruncateChannelsResponse> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::ChannelDataLoad::TruncateChannelsResponse& v) {		
			avro::encode(e, v.channelsTruncatedTime);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::ChannelDataLoad::TruncateChannelsResponse& v) {		
			avro::decode(e, v.channelsTruncatedTime);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace ChannelStreaming {				
					struct ChannelData{					
						std::vector<Energistics::Etp::v12::Datatypes::ChannelData::DataItem> data;
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
			avro::encode(e, v.data);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::ChannelStreaming::ChannelData& v) {		
			avro::decode(e, v.data);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace ChannelStreaming {				
					struct ChannelMetadata{					
						std::vector<Energistics::Etp::v12::Datatypes::ChannelData::ChannelMetadataRecord> channels;
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
			avro::encode(e, v.channels);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::ChannelStreaming::ChannelMetadata& v) {		
			avro::decode(e, v.channels);
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
		static void encode(Encoder&, const Energistics::Etp::v12::Protocol::ChannelStreaming::StartStreaming&) {		
		}		
		static void decode(Decoder&, Energistics::Etp::v12::Protocol::ChannelStreaming::StartStreaming&) {		
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
		static void encode(Encoder&, const Energistics::Etp::v12::Protocol::ChannelStreaming::StopStreaming&) {		
		}		
		static void decode(Decoder&, Energistics::Etp::v12::Protocol::ChannelStreaming::StopStreaming&) {		
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace ChannelStreaming {				
					struct TruncateChannels{					
						std::vector<Energistics::Etp::v12::Datatypes::ChannelData::TruncateInfo> channels;
						static const int messageTypeId=5;
						static const int protocolId=Energistics::Etp::v12::Datatypes::ChannelStreaming;
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::ChannelStreaming::TruncateChannels> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::ChannelStreaming::TruncateChannels& v) {		
			avro::encode(e, v.channels);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::ChannelStreaming::TruncateChannels& v) {		
			avro::decode(e, v.channels);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace ChannelSubscribe {				
					struct CancelGetRanges{					
						Energistics::Etp::v12::Datatypes::Uuid requestUuid;
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
			avro::encode(e, v.requestUuid);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::ChannelSubscribe::CancelGetRanges& v) {		
			avro::decode(e, v.requestUuid);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace ChannelSubscribe {				
					struct ChannelData{					
						std::vector<Energistics::Etp::v12::Datatypes::ChannelData::DataItem> data;
						static const int messageTypeId=4;
						static const int protocolId=Energistics::Etp::v12::Datatypes::ChannelSubscribe;
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::ChannelSubscribe::ChannelData> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::ChannelSubscribe::ChannelData& v) {		
			avro::encode(e, v.data);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::ChannelSubscribe::ChannelData& v) {		
			avro::decode(e, v.data);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace ChannelSubscribe {				
					struct ChannelsTruncated{					
						std::vector<Energistics::Etp::v12::Datatypes::ChannelData::TruncateInfo> channels;
						int64_t changeTime;
						static const int messageTypeId=13;
						static const int protocolId=Energistics::Etp::v12::Datatypes::ChannelSubscribe;
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::ChannelSubscribe::ChannelsTruncated> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::ChannelSubscribe::ChannelsTruncated& v) {		
			avro::encode(e, v.channels);
			avro::encode(e, v.changeTime);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::ChannelSubscribe::ChannelsTruncated& v) {		
			avro::decode(e, v.channels);
			avro::decode(e, v.changeTime);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace ChannelSubscribe {				
					struct GetChangeAnnotations{					
						std::map<std::string, Energistics::Etp::v12::Datatypes::ChannelData::ChannelChangeRequestInfo> channels;
						bool latestOnly=false;
						static const int messageTypeId=14;
						static const int protocolId=Energistics::Etp::v12::Datatypes::ChannelSubscribe;
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::ChannelSubscribe::GetChangeAnnotations> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::ChannelSubscribe::GetChangeAnnotations& v) {		
			avro::encode(e, v.channels);
			avro::encode(e, v.latestOnly);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::ChannelSubscribe::GetChangeAnnotations& v) {		
			avro::decode(e, v.channels);
			avro::decode(e, v.latestOnly);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace ChannelSubscribe {				
					struct GetChangeAnnotationsResponse{					
						std::map<std::string, Energistics::Etp::v12::Datatypes::ChannelData::ChannelChangeResponseInfo> changes;
						static const int messageTypeId=15;
						static const int protocolId=Energistics::Etp::v12::Datatypes::ChannelSubscribe;
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::ChannelSubscribe::GetChangeAnnotationsResponse> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::ChannelSubscribe::GetChangeAnnotationsResponse& v) {		
			avro::encode(e, v.changes);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::ChannelSubscribe::GetChangeAnnotationsResponse& v) {		
			avro::decode(e, v.changes);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace ChannelSubscribe {				
					struct GetChannelMetadata{					
						std::map<std::string, std::string> uris;
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
			avro::encode(e, v.uris);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::ChannelSubscribe::GetChannelMetadata& v) {		
			avro::decode(e, v.uris);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace ChannelSubscribe {				
					struct GetChannelMetadataResponse{					
						std::map<std::string, Energistics::Etp::v12::Datatypes::ChannelData::ChannelMetadataRecord> metadata;
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
			avro::encode(e, v.metadata);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::ChannelSubscribe::GetChannelMetadataResponse& v) {		
			avro::decode(e, v.metadata);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace ChannelSubscribe {				
					struct GetRanges{					
						Energistics::Etp::v12::Datatypes::Uuid requestUuid;
						std::vector<Energistics::Etp::v12::Datatypes::ChannelData::ChannelRangeInfo> channelRanges;
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
			avro::encode(e, v.requestUuid);
			avro::encode(e, v.channelRanges);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::ChannelSubscribe::GetRanges& v) {		
			avro::decode(e, v.requestUuid);
			avro::decode(e, v.channelRanges);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace ChannelSubscribe {				
					struct GetRangesResponse{					
						std::vector<Energistics::Etp::v12::Datatypes::ChannelData::DataItem> data;
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
			avro::encode(e, v.data);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::ChannelSubscribe::GetRangesResponse& v) {		
			avro::decode(e, v.data);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace ChannelSubscribe {				
					struct RangeReplaced{					
						int64_t changeTime;
						std::vector<int64_t> channelIds;
						Energistics::Etp::v12::Datatypes::Object::IndexInterval changedInterval;
						std::vector<Energistics::Etp::v12::Datatypes::ChannelData::DataItem> data;
						static const int messageTypeId=6;
						static const int protocolId=Energistics::Etp::v12::Datatypes::ChannelSubscribe;
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::ChannelSubscribe::RangeReplaced> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::ChannelSubscribe::RangeReplaced& v) {		
			avro::encode(e, v.changeTime);
			avro::encode(e, v.channelIds);
			avro::encode(e, v.changedInterval);
			avro::encode(e, v.data);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::ChannelSubscribe::RangeReplaced& v) {		
			avro::decode(e, v.changeTime);
			avro::decode(e, v.channelIds);
			avro::decode(e, v.changedInterval);
			avro::decode(e, v.data);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace ChannelSubscribe {				
					struct SubscribeChannels{					
						std::map<std::string, Energistics::Etp::v12::Datatypes::ChannelData::ChannelSubscribeInfo> channels;
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
			avro::encode(e, v.channels);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::ChannelSubscribe::SubscribeChannels& v) {		
			avro::decode(e, v.channels);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace ChannelSubscribe {				
					struct SubscribeChannelsResponse{					
						std::map<std::string, std::string> success;
						static const int messageTypeId=12;
						static const int protocolId=Energistics::Etp::v12::Datatypes::ChannelSubscribe;
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::ChannelSubscribe::SubscribeChannelsResponse> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::ChannelSubscribe::SubscribeChannelsResponse& v) {		
			avro::encode(e, v.success);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::ChannelSubscribe::SubscribeChannelsResponse& v) {		
			avro::decode(e, v.success);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace ChannelSubscribe {				
					struct SubscriptionsStopped{					
						std::map<std::string, int64_t> channelIds;
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
			avro::encode(e, v.channelIds);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::ChannelSubscribe::SubscriptionsStopped& v) {		
			avro::decode(e, v.channelIds);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace ChannelSubscribe {				
					struct UnsubscribeChannels{					
						std::map<std::string, int64_t> channelIds;
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
			avro::encode(e, v.channelIds);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::ChannelSubscribe::UnsubscribeChannels& v) {		
			avro::decode(e, v.channelIds);
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
		static void encode(Encoder&, const Energistics::Etp::v12::Protocol::Core::Acknowledge&) {		
		}		
		static void decode(Decoder&, Energistics::Etp::v12::Protocol::Core::Acknowledge&) {		
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace Core {				
					struct CloseSession{					
						std::string reason;
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
			avro::encode(e, v.reason);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::Core::CloseSession& v) {		
			avro::decode(e, v.reason);
		}		
	};	
}
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
			avro::encode(e, v.applicationName);
			avro::encode(e, v.applicationVersion);
			avro::encode(e, v.serverInstanceId);
			avro::encode(e, v.supportedProtocols);
			avro::encode(e, v.supportedDataObjects);
			avro::encode(e, v.supportedCompression);
			avro::encode(e, v.supportedFormats);
			avro::encode(e, v.sessionId);
			avro::encode(e, v.currentDateTime);
			avro::encode(e, v.endpointCapabilities);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::Core::OpenSession& v) {		
			avro::decode(e, v.applicationName);
			avro::decode(e, v.applicationVersion);
			avro::decode(e, v.serverInstanceId);
			avro::decode(e, v.supportedProtocols);
			avro::decode(e, v.supportedDataObjects);
			avro::decode(e, v.supportedCompression);
			avro::decode(e, v.supportedFormats);
			avro::decode(e, v.sessionId);
			avro::decode(e, v.currentDateTime);
			avro::decode(e, v.endpointCapabilities);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace Core {				
					struct Ping{					
						int64_t currentDateTime;
						static const int messageTypeId=8;
						static const int protocolId=Energistics::Etp::v12::Datatypes::Core;
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::Core::Ping> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::Core::Ping& v) {		
			avro::encode(e, v.currentDateTime);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::Core::Ping& v) {		
			avro::decode(e, v.currentDateTime);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace Core {				
					struct Pong{					
						int64_t currentDateTime;
						static const int messageTypeId=9;
						static const int protocolId=Energistics::Etp::v12::Datatypes::Core;
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::Core::Pong> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::Core::Pong& v) {		
			avro::encode(e, v.currentDateTime);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::Core::Pong& v) {		
			avro::decode(e, v.currentDateTime);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace Core {				
					struct ProtocolException{					
						boost::optional<Energistics::Etp::v12::Datatypes::ErrorInfo> error;
						std::map<std::string, Energistics::Etp::v12::Datatypes::ErrorInfo> errors;
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
			avro::encode(e, v.error);
			avro::encode(e, v.errors);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::Core::ProtocolException& v) {		
			avro::decode(e, v.error);
			avro::decode(e, v.errors);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace Core {				
					struct RenewSecurityToken{					
						std::string token;
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
			avro::encode(e, v.token);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::Core::RenewSecurityToken& v) {		
			avro::decode(e, v.token);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace Core {				
					struct RenewSecurityTokenResponse{					
						static const int messageTypeId=7;
						static const int protocolId=Energistics::Etp::v12::Datatypes::Core;
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::Core::RenewSecurityTokenResponse> {	
		static void encode(Encoder&, const Energistics::Etp::v12::Protocol::Core::RenewSecurityTokenResponse&) {		
		}		
		static void decode(Decoder&, Energistics::Etp::v12::Protocol::Core::RenewSecurityTokenResponse&) {		
		}		
	};	
}
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
			avro::encode(e, v.applicationName);
			avro::encode(e, v.applicationVersion);
			avro::encode(e, v.clientInstanceId);
			avro::encode(e, v.requestedProtocols);
			avro::encode(e, v.supportedDataObjects);
			avro::encode(e, v.supportedCompression);
			avro::encode(e, v.supportedFormats);
			avro::encode(e, v.currentDateTime);
			avro::encode(e, v.endpointCapabilities);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::Core::RequestSession& v) {		
			avro::decode(e, v.applicationName);
			avro::decode(e, v.applicationVersion);
			avro::decode(e, v.clientInstanceId);
			avro::decode(e, v.requestedProtocols);
			avro::decode(e, v.supportedDataObjects);
			avro::decode(e, v.supportedCompression);
			avro::decode(e, v.supportedFormats);
			avro::decode(e, v.currentDateTime);
			avro::decode(e, v.endpointCapabilities);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace DataArray {				
					struct GetDataArrayMetadata{					
						std::map<std::string, Energistics::Etp::v12::Datatypes::DataArrayTypes::DataArrayIdentifier> dataArrays;
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
			avro::encode(e, v.dataArrays);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::DataArray::GetDataArrayMetadata& v) {		
			avro::decode(e, v.dataArrays);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace DataArray {				
					struct GetDataArrayMetadataResponse{					
						std::map<std::string, Energistics::Etp::v12::Datatypes::DataArrayTypes::DataArrayMetadata> arrayMetadata;
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
			avro::encode(e, v.arrayMetadata);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::DataArray::GetDataArrayMetadataResponse& v) {		
			avro::decode(e, v.arrayMetadata);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace DataArray {				
					struct GetDataArrays{					
						std::map<std::string, Energistics::Etp::v12::Datatypes::DataArrayTypes::DataArrayIdentifier> dataArrays;
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
			avro::encode(e, v.dataArrays);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::DataArray::GetDataArrays& v) {		
			avro::decode(e, v.dataArrays);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace DataArray {				
					struct GetDataArraysResponse{					
						std::map<std::string, Energistics::Etp::v12::Datatypes::DataArrayTypes::DataArray> dataArrays;
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
			avro::encode(e, v.dataArrays);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::DataArray::GetDataArraysResponse& v) {		
			avro::decode(e, v.dataArrays);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace DataArray {				
					struct GetDataSubarrays{					
						std::map<std::string, Energistics::Etp::v12::Datatypes::DataArrayTypes::GetDataSubarraysType> dataSubarrays;
						static const int messageTypeId=3;
						static const int protocolId=Energistics::Etp::v12::Datatypes::DataArray;
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::DataArray::GetDataSubarrays> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::DataArray::GetDataSubarrays& v) {		
			avro::encode(e, v.dataSubarrays);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::DataArray::GetDataSubarrays& v) {		
			avro::decode(e, v.dataSubarrays);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace DataArray {				
					struct GetDataSubarraysResponse{					
						std::map<std::string, Energistics::Etp::v12::Datatypes::DataArrayTypes::DataArray> dataSubarrays;
						static const int messageTypeId=8;
						static const int protocolId=Energistics::Etp::v12::Datatypes::DataArray;
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::DataArray::GetDataSubarraysResponse> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::DataArray::GetDataSubarraysResponse& v) {		
			avro::encode(e, v.dataSubarrays);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::DataArray::GetDataSubarraysResponse& v) {		
			avro::decode(e, v.dataSubarrays);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace DataArray {				
					struct PutDataArrays{					
						std::map<std::string, Energistics::Etp::v12::Datatypes::DataArrayTypes::PutDataArraysType> dataArrays;
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
			avro::encode(e, v.dataArrays);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::DataArray::PutDataArrays& v) {		
			avro::decode(e, v.dataArrays);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace DataArray {				
					struct PutDataArraysResponse{					
						std::map<std::string, std::string> success;
						static const int messageTypeId=10;
						static const int protocolId=Energistics::Etp::v12::Datatypes::DataArray;
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::DataArray::PutDataArraysResponse> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::DataArray::PutDataArraysResponse& v) {		
			avro::encode(e, v.success);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::DataArray::PutDataArraysResponse& v) {		
			avro::decode(e, v.success);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace DataArray {				
					struct PutDataSubarrays{					
						std::map<std::string, Energistics::Etp::v12::Datatypes::DataArrayTypes::PutDataSubarraysType> dataSubarrays;
						static const int messageTypeId=5;
						static const int protocolId=Energistics::Etp::v12::Datatypes::DataArray;
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::DataArray::PutDataSubarrays> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::DataArray::PutDataSubarrays& v) {		
			avro::encode(e, v.dataSubarrays);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::DataArray::PutDataSubarrays& v) {		
			avro::decode(e, v.dataSubarrays);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace DataArray {				
					struct PutDataSubarraysResponse{					
						std::map<std::string, std::string> success;
						static const int messageTypeId=11;
						static const int protocolId=Energistics::Etp::v12::Datatypes::DataArray;
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::DataArray::PutDataSubarraysResponse> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::DataArray::PutDataSubarraysResponse& v) {		
			avro::encode(e, v.success);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::DataArray::PutDataSubarraysResponse& v) {		
			avro::decode(e, v.success);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace DataArray {				
					struct PutUninitializedDataArrays{					
						std::map<std::string, Energistics::Etp::v12::Datatypes::DataArrayTypes::PutUninitializedDataArrayType> dataArrays;
						static const int messageTypeId=9;
						static const int protocolId=Energistics::Etp::v12::Datatypes::DataArray;
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::DataArray::PutUninitializedDataArrays> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::DataArray::PutUninitializedDataArrays& v) {		
			avro::encode(e, v.dataArrays);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::DataArray::PutUninitializedDataArrays& v) {		
			avro::decode(e, v.dataArrays);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace DataArray {				
					struct PutUninitializedDataArraysResponse{					
						std::map<std::string, std::string> success;
						static const int messageTypeId=12;
						static const int protocolId=Energistics::Etp::v12::Datatypes::DataArray;
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::DataArray::PutUninitializedDataArraysResponse> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::DataArray::PutUninitializedDataArraysResponse& v) {		
			avro::encode(e, v.success);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::DataArray::PutUninitializedDataArraysResponse& v) {		
			avro::decode(e, v.success);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace Dataspace {				
					struct DeleteDataspaces{					
						std::map<std::string, std::string> uris;
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
			avro::encode(e, v.uris);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::Dataspace::DeleteDataspaces& v) {		
			avro::decode(e, v.uris);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace Dataspace {				
					struct DeleteDataspacesResponse{					
						std::map<std::string, std::string> success;
						static const int messageTypeId=5;
						static const int protocolId=Energistics::Etp::v12::Datatypes::Dataspace;
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::Dataspace::DeleteDataspacesResponse> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::Dataspace::DeleteDataspacesResponse& v) {		
			avro::encode(e, v.success);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::Dataspace::DeleteDataspacesResponse& v) {		
			avro::decode(e, v.success);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace Dataspace {				
					struct GetDataspaces{					
						boost::optional<int64_t> lastChangedFilter;
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
			avro::encode(e, v.lastChangedFilter);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::Dataspace::GetDataspaces& v) {		
			avro::decode(e, v.lastChangedFilter);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace Dataspace {				
					struct GetDataspacesResponse{					
						std::vector<Energistics::Etp::v12::Datatypes::Object::Dataspace> dataspaces;
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
			avro::encode(e, v.dataspaces);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::Dataspace::GetDataspacesResponse& v) {		
			avro::decode(e, v.dataspaces);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace Dataspace {				
					struct PutDataspaces{					
						std::map<std::string, Energistics::Etp::v12::Datatypes::Object::Dataspace> dataspaces;
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
			avro::encode(e, v.dataspaces);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::Dataspace::PutDataspaces& v) {		
			avro::decode(e, v.dataspaces);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace Dataspace {				
					struct PutDataspacesResponse{					
						std::map<std::string, std::string> success;
						static const int messageTypeId=6;
						static const int protocolId=Energistics::Etp::v12::Datatypes::Dataspace;
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::Dataspace::PutDataspacesResponse> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::Dataspace::PutDataspacesResponse& v) {		
			avro::encode(e, v.success);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::Dataspace::PutDataspacesResponse& v) {		
			avro::decode(e, v.success);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace Discovery {				
					struct GetDeletedResources{					
						std::string dataspaceUri;
						boost::optional<int64_t> deleteTimeFilter;
						std::vector<std::string> dataObjectTypes;
						static const int messageTypeId=5;
						static const int protocolId=Energistics::Etp::v12::Datatypes::Discovery;
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::Discovery::GetDeletedResources> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::Discovery::GetDeletedResources& v) {		
			avro::encode(e, v.dataspaceUri);
			avro::encode(e, v.deleteTimeFilter);
			avro::encode(e, v.dataObjectTypes);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::Discovery::GetDeletedResources& v) {		
			avro::decode(e, v.dataspaceUri);
			avro::decode(e, v.deleteTimeFilter);
			avro::decode(e, v.dataObjectTypes);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace Discovery {				
					struct GetDeletedResourcesResponse{					
						std::vector<Energistics::Etp::v12::Datatypes::Object::DeletedResource> deletedResources;
						static const int messageTypeId=6;
						static const int protocolId=Energistics::Etp::v12::Datatypes::Discovery;
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::Discovery::GetDeletedResourcesResponse> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::Discovery::GetDeletedResourcesResponse& v) {		
			avro::encode(e, v.deletedResources);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::Discovery::GetDeletedResourcesResponse& v) {		
			avro::decode(e, v.deletedResources);
		}		
	};	
}
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
						bool includeEdges=false;
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
			avro::encode(e, v.context);
			avro::encode(e, v.scope);
			avro::encode(e, v.countObjects);
			avro::encode(e, v.storeLastWriteFilter);
			avro::encode(e, v.activeStatusFilter);
			avro::encode(e, v.includeEdges);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::Discovery::GetResources& v) {		
			avro::decode(e, v.context);
			avro::decode(e, v.scope);
			avro::decode(e, v.countObjects);
			avro::decode(e, v.storeLastWriteFilter);
			avro::decode(e, v.activeStatusFilter);
			avro::decode(e, v.includeEdges);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace Discovery {				
					struct GetResourcesEdgesResponse{					
						std::vector<Energistics::Etp::v12::Datatypes::Object::Edge> edges;
						static const int messageTypeId=7;
						static const int protocolId=Energistics::Etp::v12::Datatypes::Discovery;
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::Discovery::GetResourcesEdgesResponse> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::Discovery::GetResourcesEdgesResponse& v) {		
			avro::encode(e, v.edges);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::Discovery::GetResourcesEdgesResponse& v) {		
			avro::decode(e, v.edges);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace Discovery {				
					struct GetResourcesResponse{					
						std::vector<Energistics::Etp::v12::Datatypes::Object::Resource> resources;
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
			avro::encode(e, v.resources);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::Discovery::GetResourcesResponse& v) {		
			avro::decode(e, v.resources);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace DiscoveryQuery {				
					struct FindResources{					
						Energistics::Etp::v12::Datatypes::Object::ContextInfo context;
						Energistics::Etp::v12::Datatypes::Object::ContextScopeKind scope;
						boost::optional<int64_t> storeLastWriteFilter;
						boost::optional<Energistics::Etp::v12::Datatypes::Object::ActiveStatusKind> activeStatusFilter;
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
			avro::encode(e, v.context);
			avro::encode(e, v.scope);
			avro::encode(e, v.storeLastWriteFilter);
			avro::encode(e, v.activeStatusFilter);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::DiscoveryQuery::FindResources& v) {		
			avro::decode(e, v.context);
			avro::decode(e, v.scope);
			avro::decode(e, v.storeLastWriteFilter);
			avro::decode(e, v.activeStatusFilter);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace DiscoveryQuery {				
					struct FindResourcesResponse{					
						std::vector<Energistics::Etp::v12::Datatypes::Object::Resource> resources;
						std::string serverSortOrder;
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
			avro::encode(e, v.resources);
			avro::encode(e, v.serverSortOrder);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::DiscoveryQuery::FindResourcesResponse& v) {		
			avro::decode(e, v.resources);
			avro::decode(e, v.serverSortOrder);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace GrowingObject {				
					struct DeleteParts{					
						std::string uri;
						std::map<std::string, std::string> uids;
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
			avro::encode(e, v.uri);
			avro::encode(e, v.uids);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::GrowingObject::DeleteParts& v) {		
			avro::decode(e, v.uri);
			avro::decode(e, v.uids);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace GrowingObject {				
					struct DeletePartsResponse{					
						std::map<std::string, std::string> success;
						static const int messageTypeId=11;
						static const int protocolId=Energistics::Etp::v12::Datatypes::GrowingObject;
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::GrowingObject::DeletePartsResponse> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::GrowingObject::DeletePartsResponse& v) {		
			avro::encode(e, v.success);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::GrowingObject::DeletePartsResponse& v) {		
			avro::decode(e, v.success);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace GrowingObject {				
					struct GetGrowingDataObjectsHeader{					
						std::map<std::string, std::string> uris;
						std::string format;
						static const int messageTypeId=14;
						static const int protocolId=Energistics::Etp::v12::Datatypes::GrowingObject;
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::GrowingObject::GetGrowingDataObjectsHeader> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::GrowingObject::GetGrowingDataObjectsHeader& v) {		
			avro::encode(e, v.uris);
			avro::encode(e, v.format);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::GrowingObject::GetGrowingDataObjectsHeader& v) {		
			avro::decode(e, v.uris);
			avro::decode(e, v.format);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace GrowingObject {				
					struct GetGrowingDataObjectsHeaderResponse{					
						std::map<std::string, Energistics::Etp::v12::Datatypes::Object::DataObject> dataObjects;
						static const int messageTypeId=15;
						static const int protocolId=Energistics::Etp::v12::Datatypes::GrowingObject;
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::GrowingObject::GetGrowingDataObjectsHeaderResponse> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::GrowingObject::GetGrowingDataObjectsHeaderResponse& v) {		
			avro::encode(e, v.dataObjects);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::GrowingObject::GetGrowingDataObjectsHeaderResponse& v) {		
			avro::decode(e, v.dataObjects);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace GrowingObject {				
					struct GetParts{					
						std::string uri;
						std::string format;
						std::map<std::string, std::string> uids;
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
			avro::encode(e, v.uri);
			avro::encode(e, v.format);
			avro::encode(e, v.uids);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::GrowingObject::GetParts& v) {		
			avro::decode(e, v.uri);
			avro::decode(e, v.format);
			avro::decode(e, v.uids);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace GrowingObject {				
					struct GetPartsByRange{					
						std::string uri;
						std::string format;
						Energistics::Etp::v12::Datatypes::Object::IndexInterval indexInterval;
						bool includeOverlappingIntervals=false;
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
			avro::encode(e, v.uri);
			avro::encode(e, v.format);
			avro::encode(e, v.indexInterval);
			avro::encode(e, v.includeOverlappingIntervals);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::GrowingObject::GetPartsByRange& v) {		
			avro::decode(e, v.uri);
			avro::decode(e, v.format);
			avro::decode(e, v.indexInterval);
			avro::decode(e, v.includeOverlappingIntervals);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace GrowingObject {				
					struct GetPartsByRangeResponse{					
						std::string uri;
						std::string format;
						std::vector<Energistics::Etp::v12::Datatypes::Object::ObjectPart> parts;
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
			avro::encode(e, v.uri);
			avro::encode(e, v.format);
			avro::encode(e, v.parts);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::GrowingObject::GetPartsByRangeResponse& v) {		
			avro::decode(e, v.uri);
			avro::decode(e, v.format);
			avro::decode(e, v.parts);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace GrowingObject {				
					struct GetPartsMetadata{					
						std::map<std::string, std::string> uris;
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
			avro::encode(e, v.uris);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::GrowingObject::GetPartsMetadata& v) {		
			avro::decode(e, v.uris);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace GrowingObject {				
					struct GetPartsMetadataResponse{					
						std::map<std::string, Energistics::Etp::v12::Datatypes::Object::PartsMetadataInfo> metadata;
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
			avro::encode(e, v.metadata);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::GrowingObject::GetPartsMetadataResponse& v) {		
			avro::decode(e, v.metadata);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace GrowingObject {				
					struct GetPartsResponse{					
						std::string uri;
						std::string format;
						std::map<std::string, Energistics::Etp::v12::Datatypes::Object::ObjectPart> parts;
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
			avro::encode(e, v.uri);
			avro::encode(e, v.format);
			avro::encode(e, v.parts);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::GrowingObject::GetPartsResponse& v) {		
			avro::decode(e, v.uri);
			avro::decode(e, v.format);
			avro::decode(e, v.parts);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace GrowingObject {				
					struct PutGrowingDataObjectsHeader{					
						std::map<std::string, Energistics::Etp::v12::Datatypes::Object::DataObject> dataObjects;
						static const int messageTypeId=16;
						static const int protocolId=Energistics::Etp::v12::Datatypes::GrowingObject;
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::GrowingObject::PutGrowingDataObjectsHeader> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::GrowingObject::PutGrowingDataObjectsHeader& v) {		
			avro::encode(e, v.dataObjects);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::GrowingObject::PutGrowingDataObjectsHeader& v) {		
			avro::decode(e, v.dataObjects);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace GrowingObject {				
					struct PutGrowingDataObjectsHeaderResponse{					
						std::map<std::string, std::string> uris;
						static const int messageTypeId=17;
						static const int protocolId=Energistics::Etp::v12::Datatypes::GrowingObject;
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::GrowingObject::PutGrowingDataObjectsHeaderResponse> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::GrowingObject::PutGrowingDataObjectsHeaderResponse& v) {		
			avro::encode(e, v.uris);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::GrowingObject::PutGrowingDataObjectsHeaderResponse& v) {		
			avro::decode(e, v.uris);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace GrowingObject {				
					struct PutParts{					
						std::string uri;
						std::string format;
						std::map<std::string, Energistics::Etp::v12::Datatypes::Object::ObjectPart> parts;
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
			avro::encode(e, v.uri);
			avro::encode(e, v.format);
			avro::encode(e, v.parts);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::GrowingObject::PutParts& v) {		
			avro::decode(e, v.uri);
			avro::decode(e, v.format);
			avro::decode(e, v.parts);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace GrowingObject {				
					struct PutPartsResponse{					
						std::map<std::string, std::string> success;
						static const int messageTypeId=13;
						static const int protocolId=Energistics::Etp::v12::Datatypes::GrowingObject;
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::GrowingObject::PutPartsResponse> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::GrowingObject::PutPartsResponse& v) {		
			avro::encode(e, v.success);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::GrowingObject::PutPartsResponse& v) {		
			avro::decode(e, v.success);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace GrowingObject {				
					struct ReplacePartsByRange{					
						std::string uri;
						Energistics::Etp::v12::Datatypes::Object::IndexInterval deleteInterval;
						bool includeOverlappingIntervals=false;
						std::string format;
						std::vector<Energistics::Etp::v12::Datatypes::Object::ObjectPart> parts;
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
			avro::encode(e, v.uri);
			avro::encode(e, v.deleteInterval);
			avro::encode(e, v.includeOverlappingIntervals);
			avro::encode(e, v.format);
			avro::encode(e, v.parts);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::GrowingObject::ReplacePartsByRange& v) {		
			avro::decode(e, v.uri);
			avro::decode(e, v.deleteInterval);
			avro::decode(e, v.includeOverlappingIntervals);
			avro::decode(e, v.format);
			avro::decode(e, v.parts);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace GrowingObject {				
					struct ReplacePartsByRangeResponse{					
						static const int messageTypeId=18;
						static const int protocolId=Energistics::Etp::v12::Datatypes::GrowingObject;
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::GrowingObject::ReplacePartsByRangeResponse> {	
		static void encode(Encoder&, const Energistics::Etp::v12::Protocol::GrowingObject::ReplacePartsByRangeResponse&) {		
		}		
		static void decode(Decoder&, Energistics::Etp::v12::Protocol::GrowingObject::ReplacePartsByRangeResponse&) {		
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace GrowingObjectNotification {				
					struct PartsChanged{					
						std::string uri;
						Energistics::Etp::v12::Datatypes::Uuid requestUuid;
						Energistics::Etp::v12::Datatypes::Object::ObjectChangeKind changeKind;
						int64_t changeTime;
						std::string format;
						std::vector<Energistics::Etp::v12::Datatypes::Object::ObjectPart> parts;
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
			avro::encode(e, v.uri);
			avro::encode(e, v.requestUuid);
			avro::encode(e, v.changeKind);
			avro::encode(e, v.changeTime);
			avro::encode(e, v.format);
			avro::encode(e, v.parts);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::GrowingObjectNotification::PartsChanged& v) {		
			avro::decode(e, v.uri);
			avro::decode(e, v.requestUuid);
			avro::decode(e, v.changeKind);
			avro::decode(e, v.changeTime);
			avro::decode(e, v.format);
			avro::decode(e, v.parts);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace GrowingObjectNotification {				
					struct PartsDeleted{					
						std::string uri;
						Energistics::Etp::v12::Datatypes::Uuid requestUuid;
						int64_t changeTime;
						std::vector<std::string> uids;
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
			avro::encode(e, v.uri);
			avro::encode(e, v.requestUuid);
			avro::encode(e, v.changeTime);
			avro::encode(e, v.uids);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::GrowingObjectNotification::PartsDeleted& v) {		
			avro::decode(e, v.uri);
			avro::decode(e, v.requestUuid);
			avro::decode(e, v.changeTime);
			avro::decode(e, v.uids);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace GrowingObjectNotification {				
					struct PartsReplacedByRange{					
						std::string uri;
						Energistics::Etp::v12::Datatypes::Uuid requestUuid;
						int64_t changeTime;
						Energistics::Etp::v12::Datatypes::Object::IndexInterval deletedInterval;
						bool includeOverlappingIntervals=false;
						std::string format;
						std::vector<Energistics::Etp::v12::Datatypes::Object::ObjectPart> parts;
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
			avro::encode(e, v.uri);
			avro::encode(e, v.requestUuid);
			avro::encode(e, v.changeTime);
			avro::encode(e, v.deletedInterval);
			avro::encode(e, v.includeOverlappingIntervals);
			avro::encode(e, v.format);
			avro::encode(e, v.parts);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::GrowingObjectNotification::PartsReplacedByRange& v) {		
			avro::decode(e, v.uri);
			avro::decode(e, v.requestUuid);
			avro::decode(e, v.changeTime);
			avro::decode(e, v.deletedInterval);
			avro::decode(e, v.includeOverlappingIntervals);
			avro::decode(e, v.format);
			avro::decode(e, v.parts);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace GrowingObjectNotification {				
					struct PartSubscriptionEnded{					
						Energistics::Etp::v12::Datatypes::Uuid requestUuid;
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
			avro::encode(e, v.requestUuid);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::GrowingObjectNotification::PartSubscriptionEnded& v) {		
			avro::decode(e, v.requestUuid);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace GrowingObjectNotification {				
					struct SubscribePartNotifications{					
						std::map<std::string, Energistics::Etp::v12::Datatypes::Object::SubscriptionInfo> request;
						static const int messageTypeId=7;
						static const int protocolId=Energistics::Etp::v12::Datatypes::GrowingObjectNotification;
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::GrowingObjectNotification::SubscribePartNotifications> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::GrowingObjectNotification::SubscribePartNotifications& v) {		
			avro::encode(e, v.request);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::GrowingObjectNotification::SubscribePartNotifications& v) {		
			avro::decode(e, v.request);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace GrowingObjectNotification {				
					struct SubscribePartNotificationsResponse{					
						std::map<std::string, std::string> success;
						static const int messageTypeId=10;
						static const int protocolId=Energistics::Etp::v12::Datatypes::GrowingObjectNotification;
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::GrowingObjectNotification::SubscribePartNotificationsResponse> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::GrowingObjectNotification::SubscribePartNotificationsResponse& v) {		
			avro::encode(e, v.success);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::GrowingObjectNotification::SubscribePartNotificationsResponse& v) {		
			avro::decode(e, v.success);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace GrowingObjectNotification {				
					struct UnsolicitedPartNotifications{					
						std::vector<Energistics::Etp::v12::Datatypes::Object::SubscriptionInfo> subscriptions;
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
			avro::encode(e, v.subscriptions);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::GrowingObjectNotification::UnsolicitedPartNotifications& v) {		
			avro::decode(e, v.subscriptions);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace GrowingObjectNotification {				
					struct UnsubscribePartNotification{					
						Energistics::Etp::v12::Datatypes::Uuid requestUuid;
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
			avro::encode(e, v.requestUuid);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::GrowingObjectNotification::UnsubscribePartNotification& v) {		
			avro::decode(e, v.requestUuid);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace GrowingObjectQuery {				
					struct FindParts{					
						std::string uri;
						std::string format;
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
			avro::encode(e, v.uri);
			avro::encode(e, v.format);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::GrowingObjectQuery::FindParts& v) {		
			avro::decode(e, v.uri);
			avro::decode(e, v.format);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace GrowingObjectQuery {				
					struct FindPartsResponse{					
						std::string uri;
						std::string serverSortOrder;
						std::string format;
						std::vector<Energistics::Etp::v12::Datatypes::Object::ObjectPart> parts;
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
			avro::encode(e, v.uri);
			avro::encode(e, v.serverSortOrder);
			avro::encode(e, v.format);
			avro::encode(e, v.parts);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::GrowingObjectQuery::FindPartsResponse& v) {		
			avro::decode(e, v.uri);
			avro::decode(e, v.serverSortOrder);
			avro::decode(e, v.format);
			avro::decode(e, v.parts);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace Store {				
					struct Chunk{					
						Energistics::Etp::v12::Datatypes::Uuid blobId;
						std::string data;
						bool final=false;
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
			avro::encode(e, v.blobId);
			avro::encode(e, v.data);
			avro::encode(e, v.final);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::Store::Chunk& v) {		
			avro::decode(e, v.blobId);
			avro::decode(e, v.data);
			avro::decode(e, v.final);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace Store {				
					struct DeleteDataObjects{					
						std::map<std::string, std::string> uris;
						bool pruneContainedObjects=false;
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
			avro::encode(e, v.uris);
			avro::encode(e, v.pruneContainedObjects);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::Store::DeleteDataObjects& v) {		
			avro::decode(e, v.uris);
			avro::decode(e, v.pruneContainedObjects);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace Store {				
					struct DeleteDataObjectsResponse{					
						std::map<std::string, Energistics::Etp::v12::Datatypes::ArrayOfString> deletedUris;
						static const int messageTypeId=10;
						static const int protocolId=Energistics::Etp::v12::Datatypes::Store;
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::Store::DeleteDataObjectsResponse> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::Store::DeleteDataObjectsResponse& v) {		
			avro::encode(e, v.deletedUris);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::Store::DeleteDataObjectsResponse& v) {		
			avro::decode(e, v.deletedUris);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace Store {				
					struct GetDataObjects{					
						std::map<std::string, std::string> uris;
						std::string format;
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
			avro::encode(e, v.uris);
			avro::encode(e, v.format);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::Store::GetDataObjects& v) {		
			avro::decode(e, v.uris);
			avro::decode(e, v.format);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace Store {				
					struct GetDataObjectsResponse{					
						std::map<std::string, Energistics::Etp::v12::Datatypes::Object::DataObject> dataObjects;
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
			avro::encode(e, v.dataObjects);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::Store::GetDataObjectsResponse& v) {		
			avro::decode(e, v.dataObjects);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace Store {				
					struct PutDataObjects{					
						std::map<std::string, Energistics::Etp::v12::Datatypes::Object::DataObject> dataObjects;
						bool pruneContainedObjects=false;
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
			avro::encode(e, v.dataObjects);
			avro::encode(e, v.pruneContainedObjects);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::Store::PutDataObjects& v) {		
			avro::decode(e, v.dataObjects);
			avro::decode(e, v.pruneContainedObjects);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace Store {				
					struct PutDataObjectsResponse{					
						std::map<std::string, Energistics::Etp::v12::Datatypes::Object::PutResponse> success;
						static const int messageTypeId=9;
						static const int protocolId=Energistics::Etp::v12::Datatypes::Store;
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::Store::PutDataObjectsResponse> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::Store::PutDataObjectsResponse& v) {		
			avro::encode(e, v.success);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::Store::PutDataObjectsResponse& v) {		
			avro::decode(e, v.success);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace StoreNotification {				
					struct Chunk{					
						Energistics::Etp::v12::Datatypes::Uuid blobId;
						std::string data;
						bool final=false;
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
			avro::encode(e, v.blobId);
			avro::encode(e, v.data);
			avro::encode(e, v.final);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::StoreNotification::Chunk& v) {		
			avro::decode(e, v.blobId);
			avro::decode(e, v.data);
			avro::decode(e, v.final);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace StoreNotification {				
					struct ObjectAccessRevoked{					
						std::string uri;
						int64_t changeTime;
						Energistics::Etp::v12::Datatypes::Uuid requestUuid;
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
			avro::encode(e, v.uri);
			avro::encode(e, v.changeTime);
			avro::encode(e, v.requestUuid);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::StoreNotification::ObjectAccessRevoked& v) {		
			avro::decode(e, v.uri);
			avro::decode(e, v.changeTime);
			avro::decode(e, v.requestUuid);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace StoreNotification {				
					struct ObjectActiveStatusChanged{					
						Energistics::Etp::v12::Datatypes::Object::ActiveStatusKind activeStatus;
						int64_t changeTime;
						Energistics::Etp::v12::Datatypes::Object::Resource resource;
						Energistics::Etp::v12::Datatypes::Uuid requestUuid;
						static const int messageTypeId=11;
						static const int protocolId=Energistics::Etp::v12::Datatypes::StoreNotification;
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::StoreNotification::ObjectActiveStatusChanged> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::StoreNotification::ObjectActiveStatusChanged& v) {		
			avro::encode(e, v.activeStatus);
			avro::encode(e, v.changeTime);
			avro::encode(e, v.resource);
			avro::encode(e, v.requestUuid);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::StoreNotification::ObjectActiveStatusChanged& v) {		
			avro::decode(e, v.activeStatus);
			avro::decode(e, v.changeTime);
			avro::decode(e, v.resource);
			avro::decode(e, v.requestUuid);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace StoreNotification {				
					struct ObjectChanged{					
						Energistics::Etp::v12::Datatypes::Object::ObjectChange change;
						Energistics::Etp::v12::Datatypes::Uuid requestUuid;
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
			avro::encode(e, v.change);
			avro::encode(e, v.requestUuid);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::StoreNotification::ObjectChanged& v) {		
			avro::decode(e, v.change);
			avro::decode(e, v.requestUuid);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace StoreNotification {				
					struct ObjectDeleted{					
						std::string uri;
						int64_t changeTime;
						Energistics::Etp::v12::Datatypes::Uuid requestUuid;
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
			avro::encode(e, v.uri);
			avro::encode(e, v.changeTime);
			avro::encode(e, v.requestUuid);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::StoreNotification::ObjectDeleted& v) {		
			avro::decode(e, v.uri);
			avro::decode(e, v.changeTime);
			avro::decode(e, v.requestUuid);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace StoreNotification {				
					struct SubscribeNotifications{					
						std::map<std::string, Energistics::Etp::v12::Datatypes::Object::SubscriptionInfo> request;
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
			avro::encode(e, v.request);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::StoreNotification::SubscribeNotifications& v) {		
			avro::decode(e, v.request);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace StoreNotification {				
					struct SubscribeNotificationsResponse{					
						std::map<std::string, std::string> success;
						static const int messageTypeId=10;
						static const int protocolId=Energistics::Etp::v12::Datatypes::StoreNotification;
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::StoreNotification::SubscribeNotificationsResponse> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::StoreNotification::SubscribeNotificationsResponse& v) {		
			avro::encode(e, v.success);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::StoreNotification::SubscribeNotificationsResponse& v) {		
			avro::decode(e, v.success);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace StoreNotification {				
					struct SubscriptionEnded{					
						Energistics::Etp::v12::Datatypes::Uuid requestUuid;
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
			avro::encode(e, v.requestUuid);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::StoreNotification::SubscriptionEnded& v) {		
			avro::decode(e, v.requestUuid);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace StoreNotification {				
					struct UnsolicitedStoreNotifications{					
						std::vector<Energistics::Etp::v12::Datatypes::Object::SubscriptionInfo> subscriptions;
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
			avro::encode(e, v.subscriptions);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::StoreNotification::UnsolicitedStoreNotifications& v) {		
			avro::decode(e, v.subscriptions);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace StoreNotification {				
					struct UnsubscribeNotifications{					
						Energistics::Etp::v12::Datatypes::Uuid requestUuid;
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
			avro::encode(e, v.requestUuid);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::StoreNotification::UnsubscribeNotifications& v) {		
			avro::decode(e, v.requestUuid);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace StoreQuery {				
					struct Chunk{					
						Energistics::Etp::v12::Datatypes::Uuid blobId;
						std::string data;
						bool final=false;
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
			avro::encode(e, v.blobId);
			avro::encode(e, v.data);
			avro::encode(e, v.final);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::StoreQuery::Chunk& v) {		
			avro::decode(e, v.blobId);
			avro::decode(e, v.data);
			avro::decode(e, v.final);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace StoreQuery {				
					struct FindDataObjects{					
						Energistics::Etp::v12::Datatypes::Object::ContextInfo context;
						Energistics::Etp::v12::Datatypes::Object::ContextScopeKind scope;
						boost::optional<int64_t> storeLastWriteFilter;
						boost::optional<Energistics::Etp::v12::Datatypes::Object::ActiveStatusKind> activeStatusFilter;
						std::string format;
						static const int messageTypeId=1;
						static const int protocolId=Energistics::Etp::v12::Datatypes::StoreQuery;
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::StoreQuery::FindDataObjects> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::StoreQuery::FindDataObjects& v) {		
			avro::encode(e, v.context);
			avro::encode(e, v.scope);
			avro::encode(e, v.storeLastWriteFilter);
			avro::encode(e, v.activeStatusFilter);
			avro::encode(e, v.format);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::StoreQuery::FindDataObjects& v) {		
			avro::decode(e, v.context);
			avro::decode(e, v.scope);
			avro::decode(e, v.storeLastWriteFilter);
			avro::decode(e, v.activeStatusFilter);
			avro::decode(e, v.format);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace StoreQuery {				
					struct FindDataObjectsResponse{					
						std::vector<Energistics::Etp::v12::Datatypes::Object::DataObject> dataObjects;
						std::string serverSortOrder;
						static const int messageTypeId=2;
						static const int protocolId=Energistics::Etp::v12::Datatypes::StoreQuery;
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::StoreQuery::FindDataObjectsResponse> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::StoreQuery::FindDataObjectsResponse& v) {		
			avro::encode(e, v.dataObjects);
			avro::encode(e, v.serverSortOrder);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::StoreQuery::FindDataObjectsResponse& v) {		
			avro::decode(e, v.dataObjects);
			avro::decode(e, v.serverSortOrder);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace SupportedTypes {				
					struct GetSupportedTypes{					
						std::string uri;
						Energistics::Etp::v12::Datatypes::Object::ContextScopeKind scope;
						bool returnEmptyTypes=false;
						bool countObjects=false;
						static const int messageTypeId=1;
						static const int protocolId=Energistics::Etp::v12::Datatypes::SupportedTypes;
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::SupportedTypes::GetSupportedTypes> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::SupportedTypes::GetSupportedTypes& v) {		
			avro::encode(e, v.uri);
			avro::encode(e, v.scope);
			avro::encode(e, v.returnEmptyTypes);
			avro::encode(e, v.countObjects);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::SupportedTypes::GetSupportedTypes& v) {		
			avro::decode(e, v.uri);
			avro::decode(e, v.scope);
			avro::decode(e, v.returnEmptyTypes);
			avro::decode(e, v.countObjects);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace SupportedTypes {				
					struct GetSupportedTypesResponse{					
						std::vector<Energistics::Etp::v12::Datatypes::Object::SupportedType> supportedTypes;
						static const int messageTypeId=2;
						static const int protocolId=Energistics::Etp::v12::Datatypes::SupportedTypes;
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::SupportedTypes::GetSupportedTypesResponse> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::SupportedTypes::GetSupportedTypesResponse& v) {		
			avro::encode(e, v.supportedTypes);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::SupportedTypes::GetSupportedTypesResponse& v) {		
			avro::decode(e, v.supportedTypes);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace Transaction {				
					struct CommitTransaction{					
						Energistics::Etp::v12::Datatypes::Uuid transactionUuid;
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
			avro::encode(e, v.transactionUuid);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::Transaction::CommitTransaction& v) {		
			avro::decode(e, v.transactionUuid);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace Transaction {				
					struct CommitTransactionResponse{					
						Energistics::Etp::v12::Datatypes::Uuid transactionUuid;
						bool successful=false;
						std::string failureReason;
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
			avro::encode(e, v.transactionUuid);
			avro::encode(e, v.successful);
			avro::encode(e, v.failureReason);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::Transaction::CommitTransactionResponse& v) {		
			avro::decode(e, v.transactionUuid);
			avro::decode(e, v.successful);
			avro::decode(e, v.failureReason);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace Transaction {				
					struct RollbackTransaction{					
						Energistics::Etp::v12::Datatypes::Uuid transactionUuid;
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
			avro::encode(e, v.transactionUuid);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::Transaction::RollbackTransaction& v) {		
			avro::decode(e, v.transactionUuid);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace Transaction {				
					struct RollbackTransactionResponse{					
						Energistics::Etp::v12::Datatypes::Uuid transactionUuid;
						bool successful=false;
						std::string failureReason;
						static const int messageTypeId=6;
						static const int protocolId=Energistics::Etp::v12::Datatypes::Transaction;
					};					
				};				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Etp::v12::Protocol::Transaction::RollbackTransactionResponse> {	
		static void encode(Encoder& e, const Energistics::Etp::v12::Protocol::Transaction::RollbackTransactionResponse& v) {		
			avro::encode(e, v.transactionUuid);
			avro::encode(e, v.successful);
			avro::encode(e, v.failureReason);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::Transaction::RollbackTransactionResponse& v) {		
			avro::decode(e, v.transactionUuid);
			avro::decode(e, v.successful);
			avro::decode(e, v.failureReason);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace Transaction {				
					struct StartTransaction{					
						bool readOnly=false;
						std::string message;
						std::vector<std::string> dataspaceUris;
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
			avro::encode(e, v.readOnly);
			avro::encode(e, v.message);
			avro::encode(e, v.dataspaceUris);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::Transaction::StartTransaction& v) {		
			avro::decode(e, v.readOnly);
			avro::decode(e, v.message);
			avro::decode(e, v.dataspaceUris);
		}		
	};	
}
namespace Energistics {
	namespace Etp {	
		namespace v12 {		
			namespace Protocol {			
				namespace Transaction {				
					struct StartTransactionResponse{					
						Energistics::Etp::v12::Datatypes::Uuid transactionUuid;
						bool successful=false;
						std::string failureReason;
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
			avro::encode(e, v.transactionUuid);
			avro::encode(e, v.successful);
			avro::encode(e, v.failureReason);
		}		
		static void decode(Decoder& e, Energistics::Etp::v12::Protocol::Transaction::StartTransactionResponse& v) {		
			avro::decode(e, v.transactionUuid);
			avro::decode(e, v.successful);
			avro::decode(e, v.failureReason);
		}		
	};	
}
namespace avro {
	template<> struct codec_traits<boost::optional<bool>> {	
		static void encode(Encoder& e, boost::optional<bool> v) {		
			if (v) {			
				e.encodeUnionIndex(1);
				avro::encode(e, v.get());
			}			
			else {			
				e.encodeUnionIndex(0);
				e.encodeNull();
			}			
		}		
		static void decode(Decoder& d, boost::optional<bool>& v) {		
			size_t n = d.decodeUnionIndex();
			if (n >= 2) { throw avro::Exception("Union index too big"); }
			switch (n) {			
				case 0:				
					{					
						d.decodeNull();
						v = boost::none;
					}					
					break;								
				case 1:				
					{					
						bool vv;
						avro::decode(d, vv);
						v.emplace(vv);
					}					
					break;								
			}			
		}		
	};	
}

namespace avro {
	template<> struct codec_traits<boost::optional<int32_t>> {	
		static void encode(Encoder& e, boost::optional<int32_t> v) {		
			if (v) {			
				e.encodeUnionIndex(1);
				avro::encode(e, v.get());
			}			
			else {			
				e.encodeUnionIndex(0);
				e.encodeNull();
			}			
		}		
		static void decode(Decoder& d, boost::optional<int32_t>& v) {		
			size_t n = d.decodeUnionIndex();
			if (n >= 2) { throw avro::Exception("Union index too big"); }
			switch (n) {			
				case 0:				
					{					
						d.decodeNull();
						v = boost::none;
					}					
					break;								
				case 1:				
					{					
						int32_t vv;
						avro::decode(d, vv);
						v.emplace(vv);
					}					
					break;								
			}			
		}		
	};	
}

namespace avro {
	template<> struct codec_traits<boost::optional<int64_t>> {	
		static void encode(Encoder& e, boost::optional<int64_t> v) {		
			if (v) {			
				e.encodeUnionIndex(1);
				avro::encode(e, v.get());
			}			
			else {			
				e.encodeUnionIndex(0);
				e.encodeNull();
			}			
		}		
		static void decode(Decoder& d, boost::optional<int64_t>& v) {		
			size_t n = d.decodeUnionIndex();
			if (n >= 2) { throw avro::Exception("Union index too big"); }
			switch (n) {			
				case 0:				
					{					
						d.decodeNull();
						v = boost::none;
					}					
					break;								
				case 1:				
					{					
						int64_t vv;
						avro::decode(d, vv);
						v.emplace(vv);
					}					
					break;								
			}			
		}		
	};	
}

namespace avro {
	template<> struct codec_traits<boost::optional<Energistics::Etp::v12::Datatypes::Uuid>> {	
		static void encode(Encoder& e, boost::optional<Energistics::Etp::v12::Datatypes::Uuid> v) {		
			if (v) {			
				e.encodeUnionIndex(1);
				avro::encode(e, v.get());
			}			
			else {			
				e.encodeUnionIndex(0);
				e.encodeNull();
			}			
		}		
		static void decode(Decoder& d, boost::optional<Energistics::Etp::v12::Datatypes::Uuid>& v) {		
			size_t n = d.decodeUnionIndex();
			if (n >= 2) { throw avro::Exception("Union index too big"); }
			switch (n) {			
				case 0:				
					{					
						d.decodeNull();
						v = boost::none;
					}					
					break;								
				case 1:				
					{					
						Energistics::Etp::v12::Datatypes::Uuid vv;
						avro::decode(d, vv);
						v.emplace(vv);
					}					
					break;								
			}			
		}		
	};	
}

namespace avro {
	template<> struct codec_traits<boost::optional<Energistics::Etp::v12::Datatypes::ErrorInfo>> {	
		static void encode(Encoder& e, boost::optional<Energistics::Etp::v12::Datatypes::ErrorInfo> v) {		
			if (v) {			
				e.encodeUnionIndex(1);
				avro::encode(e, v.get());
			}			
			else {			
				e.encodeUnionIndex(0);
				e.encodeNull();
			}			
		}		
		static void decode(Decoder& d, boost::optional<Energistics::Etp::v12::Datatypes::ErrorInfo>& v) {		
			size_t n = d.decodeUnionIndex();
			if (n >= 2) { throw avro::Exception("Union index too big"); }
			switch (n) {			
				case 0:				
					{					
						d.decodeNull();
						v = boost::none;
					}					
					break;								
				case 1:				
					{					
						Energistics::Etp::v12::Datatypes::ErrorInfo vv;
						avro::decode(d, vv);
						v.emplace(vv);
					}					
					break;								
			}			
		}		
	};	
}

namespace avro {
	template<> struct codec_traits<boost::optional<Energistics::Etp::v12::Datatypes::Object::ActiveStatusKind>> {	
		static void encode(Encoder& e, boost::optional<Energistics::Etp::v12::Datatypes::Object::ActiveStatusKind> v) {		
			if (v) {			
				e.encodeUnionIndex(1);
				avro::encode(e, v.get());
			}			
			else {			
				e.encodeUnionIndex(0);
				e.encodeNull();
			}			
		}		
		static void decode(Decoder& d, boost::optional<Energistics::Etp::v12::Datatypes::Object::ActiveStatusKind>& v) {		
			size_t n = d.decodeUnionIndex();
			if (n >= 2) { throw avro::Exception("Union index too big"); }
			switch (n) {			
				case 0:				
					{					
						d.decodeNull();
						v = boost::none;
					}					
					break;								
				case 1:				
					{					
						Energistics::Etp::v12::Datatypes::Object::ActiveStatusKind vv;
						avro::decode(d, vv);
						v.emplace(vv);
					}					
					break;								
			}			
		}		
	};	
}



#endif