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
	namespace Datatypes {	
		struct ArrayOfBoolean{		
			std::vector<bool> m_values;
		};		
		typedef boost::shared_ptr<ArrayOfBoolean> ArrayOfBooleanPtr;
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Datatypes::ArrayOfBoolean> {	
		static void encode(Encoder& e, const Energistics::Datatypes::ArrayOfBoolean& v) {		
			avro::encode(e, v.m_values);
		}		
		static void decode(Decoder& e, Energistics::Datatypes::ArrayOfBoolean& v) {		
			avro::decode(e, v.m_values);
		}		
	};	
}
namespace Energistics {
	namespace Datatypes {	
		struct ArrayOfDouble{		
			std::vector<double> m_values;
		};		
		typedef boost::shared_ptr<ArrayOfDouble> ArrayOfDoublePtr;
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Datatypes::ArrayOfDouble> {	
		static void encode(Encoder& e, const Energistics::Datatypes::ArrayOfDouble& v) {		
			avro::encode(e, v.m_values);
		}		
		static void decode(Decoder& e, Energistics::Datatypes::ArrayOfDouble& v) {		
			avro::decode(e, v.m_values);
		}		
	};	
}
namespace Energistics {
	namespace Datatypes {	
		struct ArrayOfFloat{		
			std::vector<float> m_values;
		};		
		typedef boost::shared_ptr<ArrayOfFloat> ArrayOfFloatPtr;
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Datatypes::ArrayOfFloat> {	
		static void encode(Encoder& e, const Energistics::Datatypes::ArrayOfFloat& v) {		
			avro::encode(e, v.m_values);
		}		
		static void decode(Decoder& e, Energistics::Datatypes::ArrayOfFloat& v) {		
			avro::decode(e, v.m_values);
		}		
	};	
}
namespace Energistics {
	namespace Datatypes {	
		struct ArrayOfInt{		
			std::vector<int32_t> m_values;
		};		
		typedef boost::shared_ptr<ArrayOfInt> ArrayOfIntPtr;
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Datatypes::ArrayOfInt> {	
		static void encode(Encoder& e, const Energistics::Datatypes::ArrayOfInt& v) {		
			avro::encode(e, v.m_values);
		}		
		static void decode(Decoder& e, Energistics::Datatypes::ArrayOfInt& v) {		
			avro::decode(e, v.m_values);
		}		
	};	
}
namespace Energistics {
	namespace Datatypes {	
		struct ArrayOfLong{		
			std::vector<int64_t> m_values;
		};		
		typedef boost::shared_ptr<ArrayOfLong> ArrayOfLongPtr;
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Datatypes::ArrayOfLong> {	
		static void encode(Encoder& e, const Energistics::Datatypes::ArrayOfLong& v) {		
			avro::encode(e, v.m_values);
		}		
		static void decode(Decoder& e, Energistics::Datatypes::ArrayOfLong& v) {		
			avro::decode(e, v.m_values);
		}		
	};	
}
namespace Energistics {
	namespace Datatypes {	
		struct AnyArrayitem_t {
		private:		
			size_t idx_=0;
			boost::any value_;
				
		public:		
			size_t idx() const { return idx_; }
			bool is_null() const { return idx_==0; }
			void set_null() { idx_=0; value_ = boost::any(); }
			Energistics::Datatypes::ArrayOfBoolean& get_ArrayOfBoolean()  {			
				if (idx_ != 1) {				
					throw avro::Exception("Invalid type for union.");
				}				
				return boost::any_cast< Energistics::Datatypes::ArrayOfBoolean& >(value_);
			}			
			void set_ArrayOfBoolean(const Energistics::Datatypes::ArrayOfBoolean& v) {			
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
			Energistics::Datatypes::ArrayOfInt& get_ArrayOfInt()  {			
				if (idx_ != 3) {				
					throw avro::Exception("Invalid type for union.");
				}				
				return boost::any_cast< Energistics::Datatypes::ArrayOfInt& >(value_);
			}			
			void set_ArrayOfInt(const Energistics::Datatypes::ArrayOfInt& v) {			
				idx_ = 3;
				value_ = v;
			}			
			Energistics::Datatypes::ArrayOfLong& get_ArrayOfLong()  {			
				if (idx_ != 4) {				
					throw avro::Exception("Invalid type for union.");
				}				
				return boost::any_cast< Energistics::Datatypes::ArrayOfLong& >(value_);
			}			
			void set_ArrayOfLong(const Energistics::Datatypes::ArrayOfLong& v) {			
				idx_ = 4;
				value_ = v;
			}			
			Energistics::Datatypes::ArrayOfFloat& get_ArrayOfFloat()  {			
				if (idx_ != 5) {				
					throw avro::Exception("Invalid type for union.");
				}				
				return boost::any_cast< Energistics::Datatypes::ArrayOfFloat& >(value_);
			}			
			void set_ArrayOfFloat(const Energistics::Datatypes::ArrayOfFloat& v) {			
				idx_ = 5;
				value_ = v;
			}			
			Energistics::Datatypes::ArrayOfDouble& get_ArrayOfDouble()  {			
				if (idx_ != 6) {				
					throw avro::Exception("Invalid type for union.");
				}				
				return boost::any_cast< Energistics::Datatypes::ArrayOfDouble& >(value_);
			}			
			void set_ArrayOfDouble(const Energistics::Datatypes::ArrayOfDouble& v) {			
				idx_ = 6;
				value_ = v;
			}			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Datatypes::AnyArrayitem_t> {
	
		static void encode(Encoder& e, Energistics::Datatypes::AnyArrayitem_t v) {
		
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
		static void decode(Decoder& d, Energistics::Datatypes::AnyArrayitem_t& v) {
		
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
						Energistics::Datatypes::ArrayOfBoolean vv;
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
						Energistics::Datatypes::ArrayOfInt vv;
						avro::decode(d, vv);
						v.set_ArrayOfInt(vv);
					}					
					break;								
				case 4:				
					{					
						Energistics::Datatypes::ArrayOfLong vv;
						avro::decode(d, vv);
						v.set_ArrayOfLong(vv);
					}					
					break;								
				case 5:				
					{					
						Energistics::Datatypes::ArrayOfFloat vv;
						avro::decode(d, vv);
						v.set_ArrayOfFloat(vv);
					}					
					break;								
				case 6:				
					{					
						Energistics::Datatypes::ArrayOfDouble vv;
						avro::decode(d, vv);
						v.set_ArrayOfDouble(vv);
					}					
					break;								
			}			
		}		
	};	
}

namespace Energistics {
	namespace Datatypes {	
		struct AnyArray{		
			Energistics::Datatypes::AnyArrayitem_t m_item;
		};		
		typedef boost::shared_ptr<AnyArray> AnyArrayPtr;
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Datatypes::AnyArray> {	
		static void encode(Encoder& e, const Energistics::Datatypes::AnyArray& v) {		
			avro::encode(e, v.m_item);
		}		
		static void decode(Decoder& e, Energistics::Datatypes::AnyArray& v) {		
			avro::decode(e, v.m_item);
		}		
	};	
}
namespace Energistics {
	namespace Datatypes {	
		struct AttributeMetadataRecord{		
			std::string m_attributeID;
			int32_t m_attributeName;
			std::string m_dataType;
			std::string m_description;
		};		
		typedef boost::shared_ptr<AttributeMetadataRecord> AttributeMetadataRecordPtr;
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Datatypes::AttributeMetadataRecord> {	
		static void encode(Encoder& e, const Energistics::Datatypes::AttributeMetadataRecord& v) {		
			avro::encode(e, v.m_attributeID);
			avro::encode(e, v.m_attributeName);
			avro::encode(e, v.m_dataType);
			avro::encode(e, v.m_description);
		}		
		static void decode(Decoder& e, Energistics::Datatypes::AttributeMetadataRecord& v) {		
			avro::decode(e, v.m_attributeID);
			avro::decode(e, v.m_attributeName);
			avro::decode(e, v.m_dataType);
			avro::decode(e, v.m_description);
		}		
	};	
}
namespace Energistics {
	namespace Datatypes {	
		struct ContactorganizationName_t {
		private:		
			size_t idx_=0;
			boost::any value_;
				
		public:		
			size_t idx() const { return idx_; }
			bool is_null() const { return idx_==0; }
			void set_null() { idx_=0; value_ = boost::any(); }
			std::string& get_string()  {			
				if (idx_ != 1) {				
					throw avro::Exception("Invalid type for union.");
				}				
				return boost::any_cast< std::string& >(value_);
			}			
			void set_string(const std::string& v) {			
				idx_ = 1;
				value_ = v;
			}			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Datatypes::ContactorganizationName_t> {
	
		static void encode(Encoder& e, Energistics::Datatypes::ContactorganizationName_t v) {
		
			e.encodeUnionIndex(v.idx());
			switch (v.idx()) {			
				case 0:				
					e.encodeNull();
					break;								
				case 1:				
					avro::encode(e, v.get_string());
					break;								
			}			
		}		
		static void decode(Decoder& d, Energistics::Datatypes::ContactorganizationName_t& v) {
		
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
						std::string vv;
						avro::decode(d, vv);
						v.set_string(vv);
					}					
					break;								
			}			
		}		
	};	
}

namespace Energistics {
	namespace Datatypes {	
		struct ContactcontactName_t {
		private:		
			size_t idx_=0;
			boost::any value_;
				
		public:		
			size_t idx() const { return idx_; }
			bool is_null() const { return idx_==0; }
			void set_null() { idx_=0; value_ = boost::any(); }
			std::string& get_string()  {			
				if (idx_ != 1) {				
					throw avro::Exception("Invalid type for union.");
				}				
				return boost::any_cast< std::string& >(value_);
			}			
			void set_string(const std::string& v) {			
				idx_ = 1;
				value_ = v;
			}			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Datatypes::ContactcontactName_t> {
	
		static void encode(Encoder& e, Energistics::Datatypes::ContactcontactName_t v) {
		
			e.encodeUnionIndex(v.idx());
			switch (v.idx()) {			
				case 0:				
					e.encodeNull();
					break;								
				case 1:				
					avro::encode(e, v.get_string());
					break;								
			}			
		}		
		static void decode(Decoder& d, Energistics::Datatypes::ContactcontactName_t& v) {
		
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
						std::string vv;
						avro::decode(d, vv);
						v.set_string(vv);
					}					
					break;								
			}			
		}		
	};	
}

namespace Energistics {
	namespace Datatypes {	
		struct ContactcontactPhone_t {
		private:		
			size_t idx_=0;
			boost::any value_;
				
		public:		
			size_t idx() const { return idx_; }
			bool is_null() const { return idx_==0; }
			void set_null() { idx_=0; value_ = boost::any(); }
			std::string& get_string()  {			
				if (idx_ != 1) {				
					throw avro::Exception("Invalid type for union.");
				}				
				return boost::any_cast< std::string& >(value_);
			}			
			void set_string(const std::string& v) {			
				idx_ = 1;
				value_ = v;
			}			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Datatypes::ContactcontactPhone_t> {
	
		static void encode(Encoder& e, Energistics::Datatypes::ContactcontactPhone_t v) {
		
			e.encodeUnionIndex(v.idx());
			switch (v.idx()) {			
				case 0:				
					e.encodeNull();
					break;								
				case 1:				
					avro::encode(e, v.get_string());
					break;								
			}			
		}		
		static void decode(Decoder& d, Energistics::Datatypes::ContactcontactPhone_t& v) {
		
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
						std::string vv;
						avro::decode(d, vv);
						v.set_string(vv);
					}					
					break;								
			}			
		}		
	};	
}

namespace Energistics {
	namespace Datatypes {	
		struct ContactcontactEmail_t {
		private:		
			size_t idx_=0;
			boost::any value_;
				
		public:		
			size_t idx() const { return idx_; }
			bool is_null() const { return idx_==0; }
			void set_null() { idx_=0; value_ = boost::any(); }
			std::string& get_string()  {			
				if (idx_ != 1) {				
					throw avro::Exception("Invalid type for union.");
				}				
				return boost::any_cast< std::string& >(value_);
			}			
			void set_string(const std::string& v) {			
				idx_ = 1;
				value_ = v;
			}			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Datatypes::ContactcontactEmail_t> {
	
		static void encode(Encoder& e, Energistics::Datatypes::ContactcontactEmail_t v) {
		
			e.encodeUnionIndex(v.idx());
			switch (v.idx()) {			
				case 0:				
					e.encodeNull();
					break;								
				case 1:				
					avro::encode(e, v.get_string());
					break;								
			}			
		}		
		static void decode(Decoder& d, Energistics::Datatypes::ContactcontactEmail_t& v) {
		
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
						std::string vv;
						avro::decode(d, vv);
						v.set_string(vv);
					}					
					break;								
			}			
		}		
	};	
}

namespace Energistics {
	namespace Datatypes {	
		struct Contact{		
			Energistics::Datatypes::ContactorganizationName_t m_organizationName;
			Energistics::Datatypes::ContactcontactName_t m_contactName;
			Energistics::Datatypes::ContactcontactPhone_t m_contactPhone;
			Energistics::Datatypes::ContactcontactEmail_t m_contactEmail;
		};		
		typedef boost::shared_ptr<Contact> ContactPtr;
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Datatypes::Contact> {	
		static void encode(Encoder& e, const Energistics::Datatypes::Contact& v) {		
			avro::encode(e, v.m_organizationName);
			avro::encode(e, v.m_contactName);
			avro::encode(e, v.m_contactPhone);
			avro::encode(e, v.m_contactEmail);
		}		
		static void decode(Decoder& e, Energistics::Datatypes::Contact& v) {		
			avro::decode(e, v.m_organizationName);
			avro::decode(e, v.m_contactName);
			avro::decode(e, v.m_contactPhone);
			avro::decode(e, v.m_contactEmail);
		}		
	};	
}
namespace Energistics {
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
			Energistics::Datatypes::ArrayOfDouble& get_ArrayOfDouble()  {			
				if (idx_ != 6) {				
					throw avro::Exception("Invalid type for union.");
				}				
				return boost::any_cast< Energistics::Datatypes::ArrayOfDouble& >(value_);
			}			
			void set_ArrayOfDouble(const Energistics::Datatypes::ArrayOfDouble& v) {			
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
namespace avro {
	template<> struct codec_traits<Energistics::Datatypes::DataValueitem_t> {
	
		static void encode(Encoder& e, Energistics::Datatypes::DataValueitem_t v) {
		
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
		static void decode(Decoder& d, Energistics::Datatypes::DataValueitem_t& v) {
		
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
						Energistics::Datatypes::ArrayOfDouble vv;
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
	namespace Datatypes {	
		struct DataValue{		
			Energistics::Datatypes::DataValueitem_t m_item;
		};		
		typedef boost::shared_ptr<DataValue> DataValuePtr;
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Datatypes::DataValue> {	
		static void encode(Encoder& e, const Energistics::Datatypes::DataValue& v) {		
			avro::encode(e, v.m_item);
		}		
		static void decode(Decoder& e, Energistics::Datatypes::DataValue& v) {		
			avro::decode(e, v.m_item);
		}		
	};	
}
namespace Energistics {
	namespace Datatypes {	
		struct DataAttribute{		
			int32_t m_attributeId;
			Energistics::Datatypes::DataValue m_attributeValue;
		};		
		typedef boost::shared_ptr<DataAttribute> DataAttributePtr;
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Datatypes::DataAttribute> {	
		static void encode(Encoder& e, const Energistics::Datatypes::DataAttribute& v) {		
			avro::encode(e, v.m_attributeId);
			avro::encode(e, v.m_attributeValue);
		}		
		static void decode(Decoder& e, Energistics::Datatypes::DataAttribute& v) {		
			avro::decode(e, v.m_attributeId);
			avro::decode(e, v.m_attributeValue);
		}		
	};	
}
namespace Energistics {
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
namespace avro {
	template<> struct codec_traits<Energistics::Datatypes::MessageHeader> {	
		static void encode(Encoder& e, const Energistics::Datatypes::MessageHeader& v) {		
			avro::encode(e, v.m_protocol);
			avro::encode(e, v.m_messageType);
			avro::encode(e, v.m_correlationId);
			avro::encode(e, v.m_messageId);
			avro::encode(e, v.m_messageFlags);
		}		
		static void decode(Decoder& e, Energistics::Datatypes::MessageHeader& v) {		
			avro::decode(e, v.m_protocol);
			avro::decode(e, v.m_messageType);
			avro::decode(e, v.m_correlationId);
			avro::decode(e, v.m_messageId);
			avro::decode(e, v.m_messageFlags);
		}		
	};	
}
namespace Energistics {
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
namespace avro {
	template<> struct codec_traits<Energistics::Datatypes::Protocols> {	
		static void encode(Encoder& e, const Energistics::Datatypes::Protocols& v) {		
			e.encodeEnum(v);
		}		
		static void decode(Decoder& e, Energistics::Datatypes::Protocols& v) {		
			v = static_cast<Energistics::Datatypes::Protocols>(e.decodeEnum());
		}		
	};	
}
namespace Energistics {
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
namespace avro {
	template<> struct codec_traits<Energistics::Datatypes::Version> {	
		static void encode(Encoder& e, const Energistics::Datatypes::Version& v) {		
			avro::encode(e, v.m_major);
			avro::encode(e, v.m_minor);
			avro::encode(e, v.m_revision);
			avro::encode(e, v.m_patch);
		}		
		static void decode(Decoder& e, Energistics::Datatypes::Version& v) {		
			avro::decode(e, v.m_major);
			avro::decode(e, v.m_minor);
			avro::decode(e, v.m_revision);
			avro::decode(e, v.m_patch);
		}		
	};	
}
namespace Energistics {
	namespace Datatypes {	
		struct SupportedProtocol{		
			int32_t m_protocol;
			Energistics::Datatypes::Version m_protocolVersion;
			std::string m_role;
			std::map<std::string, Energistics::Datatypes::DataValue> m_protocolCapabilities;
		};		
		typedef boost::shared_ptr<SupportedProtocol> SupportedProtocolPtr;
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Datatypes::SupportedProtocol> {	
		static void encode(Encoder& e, const Energistics::Datatypes::SupportedProtocol& v) {		
			avro::encode(e, v.m_protocol);
			avro::encode(e, v.m_protocolVersion);
			avro::encode(e, v.m_role);
			avro::encode(e, v.m_protocolCapabilities);
		}		
		static void decode(Decoder& e, Energistics::Datatypes::SupportedProtocol& v) {		
			avro::decode(e, v.m_protocol);
			avro::decode(e, v.m_protocolVersion);
			avro::decode(e, v.m_role);
			avro::decode(e, v.m_protocolCapabilities);
		}		
	};	
}
namespace Energistics {
	namespace Datatypes {	
		struct ServerCapabilities{		
			std::string m_applicationName;
			std::string m_applicationVersion;
			std::vector<Energistics::Datatypes::SupportedProtocol> m_supportedProtocols;
			std::vector<std::string> m_supportedObjects;
			Energistics::Datatypes::Contact m_contactInformation;
			std::string m_supportedEncodings;
			std::string m_supportedCompression;
		};		
		typedef boost::shared_ptr<ServerCapabilities> ServerCapabilitiesPtr;
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Datatypes::ServerCapabilities> {	
		static void encode(Encoder& e, const Energistics::Datatypes::ServerCapabilities& v) {		
			avro::encode(e, v.m_applicationName);
			avro::encode(e, v.m_applicationVersion);
			avro::encode(e, v.m_supportedProtocols);
			avro::encode(e, v.m_supportedObjects);
			avro::encode(e, v.m_contactInformation);
			avro::encode(e, v.m_supportedEncodings);
			avro::encode(e, v.m_supportedCompression);
		}		
		static void decode(Decoder& e, Energistics::Datatypes::ServerCapabilities& v) {		
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
	namespace Datatypes {	
		namespace ChannelData {		
			enum ChannelIndexTypes {			
				Time=0,
				Depth=1
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Datatypes::ChannelData::ChannelIndexTypes> {	
		static void encode(Encoder& e, const Energistics::Datatypes::ChannelData::ChannelIndexTypes& v) {		
			e.encodeEnum(v);
		}		
		static void decode(Decoder& e, Energistics::Datatypes::ChannelData::ChannelIndexTypes& v) {		
			v = static_cast<Energistics::Datatypes::ChannelData::ChannelIndexTypes>(e.decodeEnum());
		}		
	};	
}
namespace Energistics {
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
namespace avro {
	template<> struct codec_traits<Energistics::Datatypes::ChannelData::ChannelRangeInfo> {	
		static void encode(Encoder& e, const Energistics::Datatypes::ChannelData::ChannelRangeInfo& v) {		
			avro::encode(e, v.m_channelId);
			avro::encode(e, v.m_startIndex);
			avro::encode(e, v.m_endIndex);
		}		
		static void decode(Decoder& e, Energistics::Datatypes::ChannelData::ChannelRangeInfo& v) {		
			avro::decode(e, v.m_channelId);
			avro::decode(e, v.m_startIndex);
			avro::decode(e, v.m_endIndex);
		}		
	};	
}
namespace Energistics {
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
namespace avro {
	template<> struct codec_traits<Energistics::Datatypes::ChannelData::ChannelStatuses> {	
		static void encode(Encoder& e, const Energistics::Datatypes::ChannelData::ChannelStatuses& v) {		
			e.encodeEnum(v);
		}		
		static void decode(Decoder& e, Energistics::Datatypes::ChannelData::ChannelStatuses& v) {		
			v = static_cast<Energistics::Datatypes::ChannelData::ChannelStatuses>(e.decodeEnum());
		}		
	};	
}
namespace Energistics {
	namespace Datatypes {	
		namespace ChannelData {		
			struct DataFrame{			
				std::vector<int64_t> m_index;
				std::vector<Energistics::Datatypes::DataValue> m_data;
			};			
			typedef boost::shared_ptr<DataFrame> DataFramePtr;
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Datatypes::ChannelData::DataFrame> {	
		static void encode(Encoder& e, const Energistics::Datatypes::ChannelData::DataFrame& v) {		
			avro::encode(e, v.m_index);
			avro::encode(e, v.m_data);
		}		
		static void decode(Decoder& e, Energistics::Datatypes::ChannelData::DataFrame& v) {		
			avro::decode(e, v.m_index);
			avro::decode(e, v.m_data);
		}		
	};	
}
namespace Energistics {
	namespace Datatypes {	
		namespace ChannelData {		
			struct DataItem{			
				std::vector<int64_t> m_indexes;
				int64_t m_channelId;
				Energistics::Datatypes::DataValue m_value;
				std::vector<Energistics::Datatypes::DataAttribute> m_valueAttributes;
			};			
			typedef boost::shared_ptr<DataItem> DataItemPtr;
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Datatypes::ChannelData::DataItem> {	
		static void encode(Encoder& e, const Energistics::Datatypes::ChannelData::DataItem& v) {		
			avro::encode(e, v.m_indexes);
			avro::encode(e, v.m_channelId);
			avro::encode(e, v.m_value);
			avro::encode(e, v.m_valueAttributes);
		}		
		static void decode(Decoder& e, Energistics::Datatypes::ChannelData::DataItem& v) {		
			avro::decode(e, v.m_indexes);
			avro::decode(e, v.m_channelId);
			avro::decode(e, v.m_value);
			avro::decode(e, v.m_valueAttributes);
		}		
	};	
}
namespace Energistics {
	namespace Datatypes {	
		namespace ChannelData {		
			enum IndexDirections {			
				Increasing=0,
				Decreasing=1
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Datatypes::ChannelData::IndexDirections> {	
		static void encode(Encoder& e, const Energistics::Datatypes::ChannelData::IndexDirections& v) {		
			e.encodeEnum(v);
		}		
		static void decode(Decoder& e, Energistics::Datatypes::ChannelData::IndexDirections& v) {		
			v = static_cast<Energistics::Datatypes::ChannelData::IndexDirections>(e.decodeEnum());
		}		
	};	
}
namespace Energistics {
	namespace Datatypes {	
		namespace ChannelData {		
			struct IndexMetadataRecorddepthDatum_t {
			private:			
				size_t idx_=0;
				boost::any value_;
						
			public:			
				size_t idx() const { return idx_; }
				bool is_null() const { return idx_==0; }
				void set_null() { idx_=0; value_ = boost::any(); }
				std::string& get_string()  {				
					if (idx_ != 1) {					
						throw avro::Exception("Invalid type for union.");
					}					
					return boost::any_cast< std::string& >(value_);
				}				
				void set_string(const std::string& v) {				
					idx_ = 1;
					value_ = v;
				}				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Datatypes::ChannelData::IndexMetadataRecorddepthDatum_t> {
	
		static void encode(Encoder& e, Energistics::Datatypes::ChannelData::IndexMetadataRecorddepthDatum_t v) {
		
			e.encodeUnionIndex(v.idx());
			switch (v.idx()) {			
				case 0:				
					e.encodeNull();
					break;								
				case 1:				
					avro::encode(e, v.get_string());
					break;								
			}			
		}		
		static void decode(Decoder& d, Energistics::Datatypes::ChannelData::IndexMetadataRecorddepthDatum_t& v) {
		
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
						std::string vv;
						avro::decode(d, vv);
						v.set_string(vv);
					}					
					break;								
			}			
		}		
	};	
}

namespace Energistics {
	namespace Datatypes {	
		namespace ChannelData {		
			struct IndexMetadataRecordmnemonic_t {
			private:			
				size_t idx_=0;
				boost::any value_;
						
			public:			
				size_t idx() const { return idx_; }
				bool is_null() const { return idx_==0; }
				void set_null() { idx_=0; value_ = boost::any(); }
				std::string& get_string()  {				
					if (idx_ != 1) {					
						throw avro::Exception("Invalid type for union.");
					}					
					return boost::any_cast< std::string& >(value_);
				}				
				void set_string(const std::string& v) {				
					idx_ = 1;
					value_ = v;
				}				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Datatypes::ChannelData::IndexMetadataRecordmnemonic_t> {
	
		static void encode(Encoder& e, Energistics::Datatypes::ChannelData::IndexMetadataRecordmnemonic_t v) {
		
			e.encodeUnionIndex(v.idx());
			switch (v.idx()) {			
				case 0:				
					e.encodeNull();
					break;								
				case 1:				
					avro::encode(e, v.get_string());
					break;								
			}			
		}		
		static void decode(Decoder& d, Energistics::Datatypes::ChannelData::IndexMetadataRecordmnemonic_t& v) {
		
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
						std::string vv;
						avro::decode(d, vv);
						v.set_string(vv);
					}					
					break;								
			}			
		}		
	};	
}

namespace Energistics {
	namespace Datatypes {	
		namespace ChannelData {		
			struct IndexMetadataRecorddescription_t {
			private:			
				size_t idx_=0;
				boost::any value_;
						
			public:			
				size_t idx() const { return idx_; }
				bool is_null() const { return idx_==0; }
				void set_null() { idx_=0; value_ = boost::any(); }
				std::string& get_string()  {				
					if (idx_ != 1) {					
						throw avro::Exception("Invalid type for union.");
					}					
					return boost::any_cast< std::string& >(value_);
				}				
				void set_string(const std::string& v) {				
					idx_ = 1;
					value_ = v;
				}				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Datatypes::ChannelData::IndexMetadataRecorddescription_t> {
	
		static void encode(Encoder& e, Energistics::Datatypes::ChannelData::IndexMetadataRecorddescription_t v) {
		
			e.encodeUnionIndex(v.idx());
			switch (v.idx()) {			
				case 0:				
					e.encodeNull();
					break;								
				case 1:				
					avro::encode(e, v.get_string());
					break;								
			}			
		}		
		static void decode(Decoder& d, Energistics::Datatypes::ChannelData::IndexMetadataRecorddescription_t& v) {
		
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
						std::string vv;
						avro::decode(d, vv);
						v.set_string(vv);
					}					
					break;								
			}			
		}		
	};	
}

namespace Energistics {
	namespace Datatypes {	
		namespace ChannelData {		
			struct IndexMetadataRecorduri_t {
			private:			
				size_t idx_=0;
				boost::any value_;
						
			public:			
				size_t idx() const { return idx_; }
				bool is_null() const { return idx_==0; }
				void set_null() { idx_=0; value_ = boost::any(); }
				std::string& get_string()  {				
					if (idx_ != 1) {					
						throw avro::Exception("Invalid type for union.");
					}					
					return boost::any_cast< std::string& >(value_);
				}				
				void set_string(const std::string& v) {				
					idx_ = 1;
					value_ = v;
				}				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Datatypes::ChannelData::IndexMetadataRecorduri_t> {
	
		static void encode(Encoder& e, Energistics::Datatypes::ChannelData::IndexMetadataRecorduri_t v) {
		
			e.encodeUnionIndex(v.idx());
			switch (v.idx()) {			
				case 0:				
					e.encodeNull();
					break;								
				case 1:				
					avro::encode(e, v.get_string());
					break;								
			}			
		}		
		static void decode(Decoder& d, Energistics::Datatypes::ChannelData::IndexMetadataRecorduri_t& v) {
		
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
						std::string vv;
						avro::decode(d, vv);
						v.set_string(vv);
					}					
					break;								
			}			
		}		
	};	
}

namespace Energistics {
	namespace Datatypes {	
		namespace ChannelData {		
			struct IndexMetadataRecordtimeDatum_t {
			private:			
				size_t idx_=0;
				boost::any value_;
						
			public:			
				size_t idx() const { return idx_; }
				bool is_null() const { return idx_==0; }
				void set_null() { idx_=0; value_ = boost::any(); }
				std::string& get_string()  {				
					if (idx_ != 1) {					
						throw avro::Exception("Invalid type for union.");
					}					
					return boost::any_cast< std::string& >(value_);
				}				
				void set_string(const std::string& v) {				
					idx_ = 1;
					value_ = v;
				}				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Datatypes::ChannelData::IndexMetadataRecordtimeDatum_t> {
	
		static void encode(Encoder& e, Energistics::Datatypes::ChannelData::IndexMetadataRecordtimeDatum_t v) {
		
			e.encodeUnionIndex(v.idx());
			switch (v.idx()) {			
				case 0:				
					e.encodeNull();
					break;								
				case 1:				
					avro::encode(e, v.get_string());
					break;								
			}			
		}		
		static void decode(Decoder& d, Energistics::Datatypes::ChannelData::IndexMetadataRecordtimeDatum_t& v) {
		
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
						std::string vv;
						avro::decode(d, vv);
						v.set_string(vv);
					}					
					break;								
			}			
		}		
	};	
}

namespace Energistics {
	namespace Datatypes {	
		namespace ChannelData {		
			struct IndexMetadataRecord{			
				Energistics::Datatypes::ChannelData::ChannelIndexTypes m_indexType;
				std::string m_uom;
				Energistics::Datatypes::ChannelData::IndexMetadataRecorddepthDatum_t m_depthDatum;
				Energistics::Datatypes::ChannelData::IndexDirections m_direction;
				Energistics::Datatypes::ChannelData::IndexMetadataRecordmnemonic_t m_mnemonic;
				Energistics::Datatypes::ChannelData::IndexMetadataRecorddescription_t m_description;
				Energistics::Datatypes::ChannelData::IndexMetadataRecorduri_t m_uri;
				std::map<std::string, Energistics::Datatypes::DataValue> m_customData;
				int32_t m_scale;
				Energistics::Datatypes::ChannelData::IndexMetadataRecordtimeDatum_t m_timeDatum;
			};			
			typedef boost::shared_ptr<IndexMetadataRecord> IndexMetadataRecordPtr;
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Datatypes::ChannelData::IndexMetadataRecord> {	
		static void encode(Encoder& e, const Energistics::Datatypes::ChannelData::IndexMetadataRecord& v) {		
			avro::encode(e, v.m_indexType);
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
		static void decode(Decoder& e, Energistics::Datatypes::ChannelData::IndexMetadataRecord& v) {		
			avro::decode(e, v.m_indexType);
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
	namespace Datatypes {	
		namespace ChannelData {		
			enum Roles {			
				producer=0,
				consumer=1
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Datatypes::ChannelData::Roles> {	
		static void encode(Encoder& e, const Energistics::Datatypes::ChannelData::Roles& v) {		
			e.encodeEnum(v);
		}		
		static void decode(Decoder& e, Energistics::Datatypes::ChannelData::Roles& v) {		
			v = static_cast<Energistics::Datatypes::ChannelData::Roles>(e.decodeEnum());
		}		
	};	
}
namespace Energistics {
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
namespace avro {
	template<> struct codec_traits<Energistics::Datatypes::ChannelData::StreamingStartIndexitem_t> {
	
		static void encode(Encoder& e, Energistics::Datatypes::ChannelData::StreamingStartIndexitem_t v) {
		
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
		static void decode(Decoder& d, Energistics::Datatypes::ChannelData::StreamingStartIndexitem_t& v) {
		
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
	namespace Datatypes {	
		namespace ChannelData {		
			struct StreamingStartIndex{			
				Energistics::Datatypes::ChannelData::StreamingStartIndexitem_t m_item;
			};			
			typedef boost::shared_ptr<StreamingStartIndex> StreamingStartIndexPtr;
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Datatypes::ChannelData::StreamingStartIndex> {	
		static void encode(Encoder& e, const Energistics::Datatypes::ChannelData::StreamingStartIndex& v) {		
			avro::encode(e, v.m_item);
		}		
		static void decode(Decoder& e, Energistics::Datatypes::ChannelData::StreamingStartIndex& v) {		
			avro::decode(e, v.m_item);
		}		
	};	
}
namespace Energistics {
	namespace Datatypes {	
		namespace ChannelData {		
			struct ChannelStreamingInfo{			
				int64_t m_channelId;
				Energistics::Datatypes::ChannelData::StreamingStartIndex m_startIndex;
				bool m_receiveChangeNotification=false;
			};			
			typedef boost::shared_ptr<ChannelStreamingInfo> ChannelStreamingInfoPtr;
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Datatypes::ChannelData::ChannelStreamingInfo> {	
		static void encode(Encoder& e, const Energistics::Datatypes::ChannelData::ChannelStreamingInfo& v) {		
			avro::encode(e, v.m_channelId);
			avro::encode(e, v.m_startIndex);
			avro::encode(e, v.m_receiveChangeNotification);
		}		
		static void decode(Decoder& e, Energistics::Datatypes::ChannelData::ChannelStreamingInfo& v) {		
			avro::decode(e, v.m_channelId);
			avro::decode(e, v.m_startIndex);
			avro::decode(e, v.m_receiveChangeNotification);
		}		
	};	
}
namespace Energistics {
	namespace Datatypes {	
		namespace Object {		
			struct GrowingObjectIndexitem_t {
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
namespace avro {
	template<> struct codec_traits<Energistics::Datatypes::Object::GrowingObjectIndexitem_t> {
	
		static void encode(Encoder& e, Energistics::Datatypes::Object::GrowingObjectIndexitem_t v) {
		
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
		static void decode(Decoder& d, Energistics::Datatypes::Object::GrowingObjectIndexitem_t& v) {
		
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
	namespace Datatypes {	
		namespace Object {		
			struct GrowingObjectIndex{			
				Energistics::Datatypes::Object::GrowingObjectIndexitem_t m_item;
			};			
			typedef boost::shared_ptr<GrowingObjectIndex> GrowingObjectIndexPtr;
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Datatypes::Object::GrowingObjectIndex> {	
		static void encode(Encoder& e, const Energistics::Datatypes::Object::GrowingObjectIndex& v) {		
			avro::encode(e, v.m_item);
		}		
		static void decode(Decoder& e, Energistics::Datatypes::Object::GrowingObjectIndex& v) {		
			avro::decode(e, v.m_item);
		}		
	};	
}
namespace Energistics {
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
namespace avro {
	template<> struct codec_traits<Energistics::Datatypes::Object::NotificationRequestRecord> {	
		static void encode(Encoder& e, const Energistics::Datatypes::Object::NotificationRequestRecord& v) {		
			avro::encode(e, v.m_uri);
			avro::encode(e, v.m_uuid);
			avro::encode(e, v.m_includeObjectData);
			avro::encode(e, v.m_startTime);
			avro::encode(e, v.m_objectTypes);
		}		
		static void decode(Decoder& e, Energistics::Datatypes::Object::NotificationRequestRecord& v) {		
			avro::decode(e, v.m_uri);
			avro::decode(e, v.m_uuid);
			avro::decode(e, v.m_includeObjectData);
			avro::decode(e, v.m_startTime);
			avro::decode(e, v.m_objectTypes);
		}		
	};	
}
namespace Energistics {
	namespace Datatypes {	
		namespace Object {		
			enum ObjectChangeTypes {			
				insert=0,
				update=1
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Datatypes::Object::ObjectChangeTypes> {	
		static void encode(Encoder& e, const Energistics::Datatypes::Object::ObjectChangeTypes& v) {		
			e.encodeEnum(v);
		}		
		static void decode(Decoder& e, Energistics::Datatypes::Object::ObjectChangeTypes& v) {		
			v = static_cast<Energistics::Datatypes::Object::ObjectChangeTypes>(e.decodeEnum());
		}		
	};	
}
namespace Energistics {
	namespace Datatypes {	
		namespace Object {		
			struct Resourceuuid_t {
			private:			
				size_t idx_=0;
				boost::any value_;
						
			public:			
				size_t idx() const { return idx_; }
				bool is_null() const { return idx_==0; }
				void set_null() { idx_=0; value_ = boost::any(); }
				std::string& get_string()  {				
					if (idx_ != 1) {					
						throw avro::Exception("Invalid type for union.");
					}					
					return boost::any_cast< std::string& >(value_);
				}				
				void set_string(const std::string& v) {				
					idx_ = 1;
					value_ = v;
				}				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Datatypes::Object::Resourceuuid_t> {
	
		static void encode(Encoder& e, Energistics::Datatypes::Object::Resourceuuid_t v) {
		
			e.encodeUnionIndex(v.idx());
			switch (v.idx()) {			
				case 0:				
					e.encodeNull();
					break;								
				case 1:				
					avro::encode(e, v.get_string());
					break;								
			}			
		}		
		static void decode(Decoder& d, Energistics::Datatypes::Object::Resourceuuid_t& v) {
		
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
						std::string vv;
						avro::decode(d, vv);
						v.set_string(vv);
					}					
					break;								
			}			
		}		
	};	
}

namespace Energistics {
	namespace Datatypes {	
		namespace Object {		
			struct Resource{			
				std::string m_uri;
				std::string m_contentType;
				std::string m_name;
				bool m_channelSubscribable=false;
				std::map<std::string, std::string> m_customData;
				std::string m_resourceType;
				int32_t m_hasChildren;
				Energistics::Datatypes::Object::Resourceuuid_t m_uuid;
				int64_t m_lastChanged;
				bool m_objectNotifiable=false;
			};			
			typedef boost::shared_ptr<Resource> ResourcePtr;
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Datatypes::Object::Resource> {	
		static void encode(Encoder& e, const Energistics::Datatypes::Object::Resource& v) {		
			avro::encode(e, v.m_uri);
			avro::encode(e, v.m_contentType);
			avro::encode(e, v.m_name);
			avro::encode(e, v.m_channelSubscribable);
			avro::encode(e, v.m_customData);
			avro::encode(e, v.m_resourceType);
			avro::encode(e, v.m_hasChildren);
			avro::encode(e, v.m_uuid);
			avro::encode(e, v.m_lastChanged);
			avro::encode(e, v.m_objectNotifiable);
		}		
		static void decode(Decoder& e, Energistics::Datatypes::Object::Resource& v) {		
			avro::decode(e, v.m_uri);
			avro::decode(e, v.m_contentType);
			avro::decode(e, v.m_name);
			avro::decode(e, v.m_channelSubscribable);
			avro::decode(e, v.m_customData);
			avro::decode(e, v.m_resourceType);
			avro::decode(e, v.m_hasChildren);
			avro::decode(e, v.m_uuid);
			avro::decode(e, v.m_lastChanged);
			avro::decode(e, v.m_objectNotifiable);
		}		
	};	
}
namespace Energistics {
	namespace Datatypes {	
		namespace Object {		
			struct DataObject{			
				Energistics::Datatypes::Object::Resource m_resource;
				std::string m_contentEncoding;
				std::string m_data;
			};			
			typedef boost::shared_ptr<DataObject> DataObjectPtr;
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Datatypes::Object::DataObject> {	
		static void encode(Encoder& e, const Energistics::Datatypes::Object::DataObject& v) {		
			avro::encode(e, v.m_resource);
			avro::encode(e, v.m_contentEncoding);
			avro::encode(e, v.m_data);
		}		
		static void decode(Decoder& e, Energistics::Datatypes::Object::DataObject& v) {		
			avro::decode(e, v.m_resource);
			avro::decode(e, v.m_contentEncoding);
			avro::decode(e, v.m_data);
		}		
	};	
}
namespace Energistics {
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
namespace avro {
	template<> struct codec_traits<Energistics::Datatypes::ChannelData::ChannelMetadataRecordstartIndex_t> {
	
		static void encode(Encoder& e, Energistics::Datatypes::ChannelData::ChannelMetadataRecordstartIndex_t v) {
		
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
		static void decode(Decoder& d, Energistics::Datatypes::ChannelData::ChannelMetadataRecordstartIndex_t& v) {
		
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
namespace avro {
	template<> struct codec_traits<Energistics::Datatypes::ChannelData::ChannelMetadataRecordendIndex_t> {
	
		static void encode(Encoder& e, Energistics::Datatypes::ChannelData::ChannelMetadataRecordendIndex_t v) {
		
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
		static void decode(Decoder& d, Energistics::Datatypes::ChannelData::ChannelMetadataRecordendIndex_t& v) {
		
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
	namespace Datatypes {	
		namespace ChannelData {		
			struct ChannelMetadataRecordcontentType_t {
			private:			
				size_t idx_=0;
				boost::any value_;
						
			public:			
				size_t idx() const { return idx_; }
				bool is_null() const { return idx_==0; }
				void set_null() { idx_=0; value_ = boost::any(); }
				std::string& get_string()  {				
					if (idx_ != 1) {					
						throw avro::Exception("Invalid type for union.");
					}					
					return boost::any_cast< std::string& >(value_);
				}				
				void set_string(const std::string& v) {				
					idx_ = 1;
					value_ = v;
				}				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Datatypes::ChannelData::ChannelMetadataRecordcontentType_t> {
	
		static void encode(Encoder& e, Energistics::Datatypes::ChannelData::ChannelMetadataRecordcontentType_t v) {
		
			e.encodeUnionIndex(v.idx());
			switch (v.idx()) {			
				case 0:				
					e.encodeNull();
					break;								
				case 1:				
					avro::encode(e, v.get_string());
					break;								
			}			
		}		
		static void decode(Decoder& d, Energistics::Datatypes::ChannelData::ChannelMetadataRecordcontentType_t& v) {
		
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
						std::string vv;
						avro::decode(d, vv);
						v.set_string(vv);
					}					
					break;								
			}			
		}		
	};	
}

namespace Energistics {
	namespace Datatypes {	
		namespace ChannelData {		
			struct ChannelMetadataRecorduuid_t {
			private:			
				size_t idx_=0;
				boost::any value_;
						
			public:			
				size_t idx() const { return idx_; }
				bool is_null() const { return idx_==0; }
				void set_null() { idx_=0; value_ = boost::any(); }
				std::string& get_string()  {				
					if (idx_ != 1) {					
						throw avro::Exception("Invalid type for union.");
					}					
					return boost::any_cast< std::string& >(value_);
				}				
				void set_string(const std::string& v) {				
					idx_ = 1;
					value_ = v;
				}				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Datatypes::ChannelData::ChannelMetadataRecorduuid_t> {
	
		static void encode(Encoder& e, Energistics::Datatypes::ChannelData::ChannelMetadataRecorduuid_t v) {
		
			e.encodeUnionIndex(v.idx());
			switch (v.idx()) {			
				case 0:				
					e.encodeNull();
					break;								
				case 1:				
					avro::encode(e, v.get_string());
					break;								
			}			
		}		
		static void decode(Decoder& d, Energistics::Datatypes::ChannelData::ChannelMetadataRecorduuid_t& v) {
		
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
						std::string vv;
						avro::decode(d, vv);
						v.set_string(vv);
					}					
					break;								
			}			
		}		
	};	
}

namespace Energistics {
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
				Energistics::Datatypes::Object::DataObject& get_DataObject()  {				
					if (idx_ != 1) {					
						throw avro::Exception("Invalid type for union.");
					}					
					return boost::any_cast< Energistics::Datatypes::Object::DataObject& >(value_);
				}				
				void set_DataObject(const Energistics::Datatypes::Object::DataObject& v) {				
					idx_ = 1;
					value_ = v;
				}				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Datatypes::ChannelData::ChannelMetadataRecorddomainObject_t> {
	
		static void encode(Encoder& e, Energistics::Datatypes::ChannelData::ChannelMetadataRecorddomainObject_t v) {
		
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
		static void decode(Decoder& d, Energistics::Datatypes::ChannelData::ChannelMetadataRecorddomainObject_t& v) {
		
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
						Energistics::Datatypes::Object::DataObject vv;
						avro::decode(d, vv);
						v.set_DataObject(vv);
					}					
					break;								
			}			
		}		
	};	
}

namespace Energistics {
	namespace Datatypes {	
		namespace ChannelData {		
			struct ChannelMetadataRecord{			
				std::string m_channelUri;
				int64_t m_channelId;
				std::vector<Energistics::Datatypes::ChannelData::IndexMetadataRecord> m_indexes;
				std::string m_channelName;
				std::string m_dataType;
				std::string m_uom;
				Energistics::Datatypes::ChannelData::ChannelMetadataRecordstartIndex_t m_startIndex;
				Energistics::Datatypes::ChannelData::ChannelMetadataRecordendIndex_t m_endIndex;
				std::string m_description;
				Energistics::Datatypes::ChannelData::ChannelStatuses m_status;
				Energistics::Datatypes::ChannelData::ChannelMetadataRecordcontentType_t m_contentType;
				std::string m_source;
				std::string m_measureClass;
				Energistics::Datatypes::ChannelData::ChannelMetadataRecorduuid_t m_uuid;
				std::map<std::string, Energistics::Datatypes::DataValue> m_customData;
				Energistics::Datatypes::ChannelData::ChannelMetadataRecorddomainObject_t m_domainObject;
				std::vector<Energistics::Datatypes::AttributeMetadataRecord> m_attributeMetadata;
			};			
			typedef boost::shared_ptr<ChannelMetadataRecord> ChannelMetadataRecordPtr;
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Datatypes::ChannelData::ChannelMetadataRecord> {	
		static void encode(Encoder& e, const Energistics::Datatypes::ChannelData::ChannelMetadataRecord& v) {		
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
		static void decode(Decoder& e, Energistics::Datatypes::ChannelData::ChannelMetadataRecord& v) {		
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
	namespace Datatypes {	
		namespace Object {		
			struct ObjectChange{			
				Energistics::Datatypes::Object::ObjectChangeTypes m_changeType;
				int64_t m_changeTime;
				Energistics::Datatypes::Object::DataObject m_dataObject;
			};			
			typedef boost::shared_ptr<ObjectChange> ObjectChangePtr;
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Datatypes::Object::ObjectChange> {	
		static void encode(Encoder& e, const Energistics::Datatypes::Object::ObjectChange& v) {		
			avro::encode(e, v.m_changeType);
			avro::encode(e, v.m_changeTime);
			avro::encode(e, v.m_dataObject);
		}		
		static void decode(Decoder& e, Energistics::Datatypes::Object::ObjectChange& v) {		
			avro::decode(e, v.m_changeType);
			avro::decode(e, v.m_changeTime);
			avro::decode(e, v.m_dataObject);
		}		
	};	
}
namespace Energistics {
	namespace Protocol {	
		namespace ChannelDataFrame {		
			struct ChannelDataFrameSet{			
				std::vector<int64_t> m_channels;
				std::vector<Energistics::Datatypes::ChannelData::DataFrame> m_data;
				static const int messageTypeId=4;
				static const int protocolId=Energistics::Datatypes::Protocols::ChannelDataFrame;
			};			
			typedef boost::shared_ptr<ChannelDataFrameSet> ChannelDataFrameSetPtr;
			const int CHANNELDATAFRAMESET=4;
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Protocol::ChannelDataFrame::ChannelDataFrameSet> {	
		static void encode(Encoder& e, const Energistics::Protocol::ChannelDataFrame::ChannelDataFrameSet& v) {		
			avro::encode(e, v.m_channels);
			avro::encode(e, v.m_data);
		}		
		static void decode(Decoder& e, Energistics::Protocol::ChannelDataFrame::ChannelDataFrameSet& v) {		
			avro::decode(e, v.m_channels);
			avro::decode(e, v.m_data);
		}		
	};	
}
namespace Energistics {
	namespace Protocol {	
		namespace ChannelDataFrame {		
			struct ChannelMetadata{			
				std::vector<Energistics::Datatypes::ChannelData::ChannelMetadataRecord> m_channels;
				static const int messageTypeId=3;
				static const int protocolId=Energistics::Datatypes::Protocols::ChannelDataFrame;
			};			
			typedef boost::shared_ptr<ChannelMetadata> ChannelMetadataPtr;
			const int CHANNELMETADATA=3;
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Protocol::ChannelDataFrame::ChannelMetadata> {	
		static void encode(Encoder& e, const Energistics::Protocol::ChannelDataFrame::ChannelMetadata& v) {		
			avro::encode(e, v.m_channels);
		}		
		static void decode(Decoder& e, Energistics::Protocol::ChannelDataFrame::ChannelMetadata& v) {		
			avro::decode(e, v.m_channels);
		}		
	};	
}
namespace Energistics {
	namespace Protocol {	
		namespace ChannelDataFrame {		
			struct RequestChannelDatafromIndex_t {
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
namespace avro {
	template<> struct codec_traits<Energistics::Protocol::ChannelDataFrame::RequestChannelDatafromIndex_t> {
	
		static void encode(Encoder& e, Energistics::Protocol::ChannelDataFrame::RequestChannelDatafromIndex_t v) {
		
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
		static void decode(Decoder& d, Energistics::Protocol::ChannelDataFrame::RequestChannelDatafromIndex_t& v) {
		
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
	namespace Protocol {	
		namespace ChannelDataFrame {		
			struct RequestChannelDatatoIndex_t {
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
namespace avro {
	template<> struct codec_traits<Energistics::Protocol::ChannelDataFrame::RequestChannelDatatoIndex_t> {
	
		static void encode(Encoder& e, Energistics::Protocol::ChannelDataFrame::RequestChannelDatatoIndex_t v) {
		
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
		static void decode(Decoder& d, Energistics::Protocol::ChannelDataFrame::RequestChannelDatatoIndex_t& v) {
		
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
	namespace Protocol {	
		namespace ChannelDataFrame {		
			struct RequestChannelData{			
				std::string m_uri;
				Energistics::Protocol::ChannelDataFrame::RequestChannelDatafromIndex_t m_fromIndex;
				Energistics::Protocol::ChannelDataFrame::RequestChannelDatatoIndex_t m_toIndex;
				static const int messageTypeId=1;
				static const int protocolId=Energistics::Datatypes::Protocols::ChannelDataFrame;
			};			
			typedef boost::shared_ptr<RequestChannelData> RequestChannelDataPtr;
			const int REQUESTCHANNELDATA=1;
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Protocol::ChannelDataFrame::RequestChannelData> {	
		static void encode(Encoder& e, const Energistics::Protocol::ChannelDataFrame::RequestChannelData& v) {		
			avro::encode(e, v.m_uri);
			avro::encode(e, v.m_fromIndex);
			avro::encode(e, v.m_toIndex);
		}		
		static void decode(Decoder& e, Energistics::Protocol::ChannelDataFrame::RequestChannelData& v) {		
			avro::decode(e, v.m_uri);
			avro::decode(e, v.m_fromIndex);
			avro::decode(e, v.m_toIndex);
		}		
	};	
}
namespace Energistics {
	namespace Protocol {	
		namespace Core {		
			struct Acknowledge{			
				static const int messageTypeId=1001;
				static const int protocolId=Energistics::Datatypes::Protocols::Core;
			};			
			typedef boost::shared_ptr<Acknowledge> AcknowledgePtr;
			const int ACKNOWLEDGE=1001;
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Protocol::Core::Acknowledge> {	
		static void encode(Encoder& e, const Energistics::Protocol::Core::Acknowledge& v) {		
		}		
		static void decode(Decoder& e, Energistics::Protocol::Core::Acknowledge& v) {		
		}		
	};	
}
namespace Energistics {
	namespace Protocol {	
		namespace Core {		
			struct CloseSessionreason_t {
			private:			
				size_t idx_=0;
				boost::any value_;
						
			public:			
				size_t idx() const { return idx_; }
				bool is_null() const { return idx_==0; }
				void set_null() { idx_=0; value_ = boost::any(); }
				std::string& get_string()  {				
					if (idx_ != 1) {					
						throw avro::Exception("Invalid type for union.");
					}					
					return boost::any_cast< std::string& >(value_);
				}				
				void set_string(const std::string& v) {				
					idx_ = 1;
					value_ = v;
				}				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Protocol::Core::CloseSessionreason_t> {
	
		static void encode(Encoder& e, Energistics::Protocol::Core::CloseSessionreason_t v) {
		
			e.encodeUnionIndex(v.idx());
			switch (v.idx()) {			
				case 0:				
					e.encodeNull();
					break;								
				case 1:				
					avro::encode(e, v.get_string());
					break;								
			}			
		}		
		static void decode(Decoder& d, Energistics::Protocol::Core::CloseSessionreason_t& v) {
		
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
						std::string vv;
						avro::decode(d, vv);
						v.set_string(vv);
					}					
					break;								
			}			
		}		
	};	
}

namespace Energistics {
	namespace Protocol {	
		namespace Core {		
			struct CloseSession{			
				Energistics::Protocol::Core::CloseSessionreason_t m_reason;
				static const int messageTypeId=5;
				static const int protocolId=Energistics::Datatypes::Protocols::Core;
			};			
			typedef boost::shared_ptr<CloseSession> CloseSessionPtr;
			const int CLOSESESSION=5;
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Protocol::Core::CloseSession> {	
		static void encode(Encoder& e, const Energistics::Protocol::Core::CloseSession& v) {		
			avro::encode(e, v.m_reason);
		}		
		static void decode(Decoder& e, Energistics::Protocol::Core::CloseSession& v) {		
			avro::decode(e, v.m_reason);
		}		
	};	
}
namespace Energistics {
	namespace Protocol {	
		namespace Core {		
			struct OpenSession{			
				std::string m_applicationName;
				std::string m_applicationVersion;
				std::string m_sessionId;
				std::vector<Energistics::Datatypes::SupportedProtocol> m_supportedProtocols;
				std::vector<std::string> m_supportedObjects;
				std::string m_supportedCompression;
				static const int messageTypeId=2;
				static const int protocolId=Energistics::Datatypes::Protocols::Core;
			};			
			typedef boost::shared_ptr<OpenSession> OpenSessionPtr;
			const int OPENSESSION=2;
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Protocol::Core::OpenSession> {	
		static void encode(Encoder& e, const Energistics::Protocol::Core::OpenSession& v) {		
			avro::encode(e, v.m_applicationName);
			avro::encode(e, v.m_applicationVersion);
			avro::encode(e, v.m_sessionId);
			avro::encode(e, v.m_supportedProtocols);
			avro::encode(e, v.m_supportedObjects);
			avro::encode(e, v.m_supportedCompression);
		}		
		static void decode(Decoder& e, Energistics::Protocol::Core::OpenSession& v) {		
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
	namespace Protocol {	
		namespace Core {		
			struct ProtocolException{			
				int32_t m_errorCode;
				std::string m_errorMessage;
				static const int messageTypeId=1000;
				static const int protocolId=Energistics::Datatypes::Protocols::Core;
			};			
			typedef boost::shared_ptr<ProtocolException> ProtocolExceptionPtr;
			const int PROTOCOLEXCEPTION=1000;
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Protocol::Core::ProtocolException> {	
		static void encode(Encoder& e, const Energistics::Protocol::Core::ProtocolException& v) {		
			avro::encode(e, v.m_errorCode);
			avro::encode(e, v.m_errorMessage);
		}		
		static void decode(Decoder& e, Energistics::Protocol::Core::ProtocolException& v) {		
			avro::decode(e, v.m_errorCode);
			avro::decode(e, v.m_errorMessage);
		}		
	};	
}
namespace Energistics {
	namespace Protocol {	
		namespace Core {		
			struct RenewSecurityToken{			
				std::string m_token;
				static const int messageTypeId=6;
				static const int protocolId=Energistics::Datatypes::Protocols::Core;
			};			
			typedef boost::shared_ptr<RenewSecurityToken> RenewSecurityTokenPtr;
			const int RENEWSECURITYTOKEN=6;
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Protocol::Core::RenewSecurityToken> {	
		static void encode(Encoder& e, const Energistics::Protocol::Core::RenewSecurityToken& v) {		
			avro::encode(e, v.m_token);
		}		
		static void decode(Decoder& e, Energistics::Protocol::Core::RenewSecurityToken& v) {		
			avro::decode(e, v.m_token);
		}		
	};	
}
namespace Energistics {
	namespace Protocol {	
		namespace Core {		
			struct RequestSession{			
				std::string m_applicationName;
				std::string m_applicationVersion;
				std::vector<Energistics::Datatypes::SupportedProtocol> m_requestedProtocols;
				std::vector<std::string> m_supportedObjects;
				std::string m_supportedCompression;
				static const int messageTypeId=1;
				static const int protocolId=Energistics::Datatypes::Protocols::Core;
			};			
			typedef boost::shared_ptr<RequestSession> RequestSessionPtr;
			const int REQUESTSESSION=1;
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Protocol::Core::RequestSession> {	
		static void encode(Encoder& e, const Energistics::Protocol::Core::RequestSession& v) {		
			avro::encode(e, v.m_applicationName);
			avro::encode(e, v.m_applicationVersion);
			avro::encode(e, v.m_requestedProtocols);
			avro::encode(e, v.m_supportedObjects);
			avro::encode(e, v.m_supportedCompression);
		}		
		static void decode(Decoder& e, Energistics::Protocol::Core::RequestSession& v) {		
			avro::decode(e, v.m_applicationName);
			avro::decode(e, v.m_applicationVersion);
			avro::decode(e, v.m_requestedProtocols);
			avro::decode(e, v.m_supportedObjects);
			avro::decode(e, v.m_supportedCompression);
		}		
	};	
}
namespace Energistics {
	namespace Protocol {	
		namespace ChannelStreaming {		
			struct ChannelData{			
				std::vector<Energistics::Datatypes::ChannelData::DataItem> m_data;
				static const int messageTypeId=3;
				static const int protocolId=Energistics::Datatypes::Protocols::ChannelStreaming;
			};			
			typedef boost::shared_ptr<ChannelData> ChannelDataPtr;
			const int CHANNELDATA=3;
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Protocol::ChannelStreaming::ChannelData> {	
		static void encode(Encoder& e, const Energistics::Protocol::ChannelStreaming::ChannelData& v) {		
			avro::encode(e, v.m_data);
		}		
		static void decode(Decoder& e, Energistics::Protocol::ChannelStreaming::ChannelData& v) {		
			avro::decode(e, v.m_data);
		}		
	};	
}
namespace Energistics {
	namespace Protocol {	
		namespace ChannelStreaming {		
			struct ChannelDataChange{			
				int64_t m_channelId;
				int64_t m_startIndex;
				int64_t m_endIndex;
				std::vector<Energistics::Datatypes::ChannelData::DataItem> m_data;
				static const int messageTypeId=6;
				static const int protocolId=Energistics::Datatypes::Protocols::ChannelStreaming;
			};			
			typedef boost::shared_ptr<ChannelDataChange> ChannelDataChangePtr;
			const int CHANNELDATACHANGE=6;
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Protocol::ChannelStreaming::ChannelDataChange> {	
		static void encode(Encoder& e, const Energistics::Protocol::ChannelStreaming::ChannelDataChange& v) {		
			avro::encode(e, v.m_channelId);
			avro::encode(e, v.m_startIndex);
			avro::encode(e, v.m_endIndex);
			avro::encode(e, v.m_data);
		}		
		static void decode(Decoder& e, Energistics::Protocol::ChannelStreaming::ChannelDataChange& v) {		
			avro::decode(e, v.m_channelId);
			avro::decode(e, v.m_startIndex);
			avro::decode(e, v.m_endIndex);
			avro::decode(e, v.m_data);
		}		
	};	
}
namespace Energistics {
	namespace Protocol {	
		namespace ChannelStreaming {		
			struct ChannelDescribe{			
				std::vector<std::string> m_uris;
				static const int messageTypeId=1;
				static const int protocolId=Energistics::Datatypes::Protocols::ChannelStreaming;
			};			
			typedef boost::shared_ptr<ChannelDescribe> ChannelDescribePtr;
			const int CHANNELDESCRIBE=1;
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Protocol::ChannelStreaming::ChannelDescribe> {	
		static void encode(Encoder& e, const Energistics::Protocol::ChannelStreaming::ChannelDescribe& v) {		
			avro::encode(e, v.m_uris);
		}		
		static void decode(Decoder& e, Energistics::Protocol::ChannelStreaming::ChannelDescribe& v) {		
			avro::decode(e, v.m_uris);
		}		
	};	
}
namespace Energistics {
	namespace Protocol {	
		namespace ChannelStreaming {		
			struct ChannelMetadata{			
				std::vector<Energistics::Datatypes::ChannelData::ChannelMetadataRecord> m_channels;
				static const int messageTypeId=2;
				static const int protocolId=Energistics::Datatypes::Protocols::ChannelStreaming;
			};			
			typedef boost::shared_ptr<ChannelMetadata> ChannelMetadataPtr;
			const int CHANNELMETADATA=2;
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Protocol::ChannelStreaming::ChannelMetadata> {	
		static void encode(Encoder& e, const Energistics::Protocol::ChannelStreaming::ChannelMetadata& v) {		
			avro::encode(e, v.m_channels);
		}		
		static void decode(Decoder& e, Energistics::Protocol::ChannelStreaming::ChannelMetadata& v) {		
			avro::decode(e, v.m_channels);
		}		
	};	
}
namespace Energistics {
	namespace Protocol {	
		namespace ChannelStreaming {		
			struct ChannelRangeRequest{			
				std::vector<Energistics::Datatypes::ChannelData::ChannelRangeInfo> m_channelRanges;
				static const int messageTypeId=9;
				static const int protocolId=Energistics::Datatypes::Protocols::ChannelStreaming;
			};			
			typedef boost::shared_ptr<ChannelRangeRequest> ChannelRangeRequestPtr;
			const int CHANNELRANGEREQUEST=9;
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Protocol::ChannelStreaming::ChannelRangeRequest> {	
		static void encode(Encoder& e, const Energistics::Protocol::ChannelStreaming::ChannelRangeRequest& v) {		
			avro::encode(e, v.m_channelRanges);
		}		
		static void decode(Decoder& e, Energistics::Protocol::ChannelStreaming::ChannelRangeRequest& v) {		
			avro::decode(e, v.m_channelRanges);
		}		
	};	
}
namespace Energistics {
	namespace Protocol {	
		namespace ChannelStreaming {		
			struct ChannelRemoveremoveReason_t {
			private:			
				size_t idx_=0;
				boost::any value_;
						
			public:			
				size_t idx() const { return idx_; }
				bool is_null() const { return idx_==0; }
				void set_null() { idx_=0; value_ = boost::any(); }
				std::string& get_string()  {				
					if (idx_ != 1) {					
						throw avro::Exception("Invalid type for union.");
					}					
					return boost::any_cast< std::string& >(value_);
				}				
				void set_string(const std::string& v) {				
					idx_ = 1;
					value_ = v;
				}				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Protocol::ChannelStreaming::ChannelRemoveremoveReason_t> {
	
		static void encode(Encoder& e, Energistics::Protocol::ChannelStreaming::ChannelRemoveremoveReason_t v) {
		
			e.encodeUnionIndex(v.idx());
			switch (v.idx()) {			
				case 0:				
					e.encodeNull();
					break;								
				case 1:				
					avro::encode(e, v.get_string());
					break;								
			}			
		}		
		static void decode(Decoder& d, Energistics::Protocol::ChannelStreaming::ChannelRemoveremoveReason_t& v) {
		
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
						std::string vv;
						avro::decode(d, vv);
						v.set_string(vv);
					}					
					break;								
			}			
		}		
	};	
}

namespace Energistics {
	namespace Protocol {	
		namespace ChannelStreaming {		
			struct ChannelRemove{			
				int64_t m_channelId;
				Energistics::Protocol::ChannelStreaming::ChannelRemoveremoveReason_t m_removeReason;
				static const int messageTypeId=8;
				static const int protocolId=Energistics::Datatypes::Protocols::ChannelStreaming;
			};			
			typedef boost::shared_ptr<ChannelRemove> ChannelRemovePtr;
			const int CHANNELREMOVE=8;
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Protocol::ChannelStreaming::ChannelRemove> {	
		static void encode(Encoder& e, const Energistics::Protocol::ChannelStreaming::ChannelRemove& v) {		
			avro::encode(e, v.m_channelId);
			avro::encode(e, v.m_removeReason);
		}		
		static void decode(Decoder& e, Energistics::Protocol::ChannelStreaming::ChannelRemove& v) {		
			avro::decode(e, v.m_channelId);
			avro::decode(e, v.m_removeReason);
		}		
	};	
}
namespace Energistics {
	namespace Protocol {	
		namespace ChannelStreaming {		
			struct ChannelStatusChange{			
				int64_t m_channelId;
				Energistics::Datatypes::ChannelData::ChannelStatuses m_status;
				static const int messageTypeId=10;
				static const int protocolId=Energistics::Datatypes::Protocols::ChannelStreaming;
			};			
			typedef boost::shared_ptr<ChannelStatusChange> ChannelStatusChangePtr;
			const int CHANNELSTATUSCHANGE=10;
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Protocol::ChannelStreaming::ChannelStatusChange> {	
		static void encode(Encoder& e, const Energistics::Protocol::ChannelStreaming::ChannelStatusChange& v) {		
			avro::encode(e, v.m_channelId);
			avro::encode(e, v.m_status);
		}		
		static void decode(Decoder& e, Energistics::Protocol::ChannelStreaming::ChannelStatusChange& v) {		
			avro::decode(e, v.m_channelId);
			avro::decode(e, v.m_status);
		}		
	};	
}
namespace Energistics {
	namespace Protocol {	
		namespace ChannelStreaming {		
			struct ChannelStreamingStart{			
				std::vector<Energistics::Datatypes::ChannelData::ChannelStreamingInfo> m_channels;
				static const int messageTypeId=4;
				static const int protocolId=Energistics::Datatypes::Protocols::ChannelStreaming;
			};			
			typedef boost::shared_ptr<ChannelStreamingStart> ChannelStreamingStartPtr;
			const int CHANNELSTREAMINGSTART=4;
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Protocol::ChannelStreaming::ChannelStreamingStart> {	
		static void encode(Encoder& e, const Energistics::Protocol::ChannelStreaming::ChannelStreamingStart& v) {		
			avro::encode(e, v.m_channels);
		}		
		static void decode(Decoder& e, Energistics::Protocol::ChannelStreaming::ChannelStreamingStart& v) {		
			avro::decode(e, v.m_channels);
		}		
	};	
}
namespace Energistics {
	namespace Protocol {	
		namespace ChannelStreaming {		
			struct ChannelStreamingStop{			
				std::vector<int64_t> m_channels;
				static const int messageTypeId=5;
				static const int protocolId=Energistics::Datatypes::Protocols::ChannelStreaming;
			};			
			typedef boost::shared_ptr<ChannelStreamingStop> ChannelStreamingStopPtr;
			const int CHANNELSTREAMINGSTOP=5;
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Protocol::ChannelStreaming::ChannelStreamingStop> {	
		static void encode(Encoder& e, const Energistics::Protocol::ChannelStreaming::ChannelStreamingStop& v) {		
			avro::encode(e, v.m_channels);
		}		
		static void decode(Decoder& e, Energistics::Protocol::ChannelStreaming::ChannelStreamingStop& v) {		
			avro::decode(e, v.m_channels);
		}		
	};	
}
namespace Energistics {
	namespace Protocol {	
		namespace ChannelStreaming {		
			struct Start{			
				int32_t m_maxMessageRate;
				int32_t m_maxDataItems;
				static const int messageTypeId=0;
				static const int protocolId=Energistics::Datatypes::Protocols::ChannelStreaming;
			};			
			typedef boost::shared_ptr<Start> StartPtr;
			const int START=0;
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Protocol::ChannelStreaming::Start> {	
		static void encode(Encoder& e, const Energistics::Protocol::ChannelStreaming::Start& v) {		
			avro::encode(e, v.m_maxMessageRate);
			avro::encode(e, v.m_maxDataItems);
		}		
		static void decode(Decoder& e, Energistics::Protocol::ChannelStreaming::Start& v) {		
			avro::decode(e, v.m_maxMessageRate);
			avro::decode(e, v.m_maxDataItems);
		}		
	};	
}
namespace Energistics {
	namespace Protocol {	
		namespace DataArray {		
			struct DataArray{			
				std::vector<int64_t> m_dimensions;
				Energistics::Datatypes::AnyArray m_data;
				static const int messageTypeId=1;
				static const int protocolId=Energistics::Datatypes::Protocols::DataArray;
			};			
			typedef boost::shared_ptr<DataArray> DataArrayPtr;
			const int DATAARRAY=1;
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Protocol::DataArray::DataArray> {	
		static void encode(Encoder& e, const Energistics::Protocol::DataArray::DataArray& v) {		
			avro::encode(e, v.m_dimensions);
			avro::encode(e, v.m_data);
		}		
		static void decode(Decoder& e, Energistics::Protocol::DataArray::DataArray& v) {		
			avro::decode(e, v.m_dimensions);
			avro::decode(e, v.m_data);
		}		
	};	
}
namespace Energistics {
	namespace Protocol {	
		namespace DataArray {		
			struct GetDataArray{			
				std::string m_uri;
				static const int messageTypeId=2;
				static const int protocolId=Energistics::Datatypes::Protocols::DataArray;
			};			
			typedef boost::shared_ptr<GetDataArray> GetDataArrayPtr;
			const int GETDATAARRAY=2;
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Protocol::DataArray::GetDataArray> {	
		static void encode(Encoder& e, const Energistics::Protocol::DataArray::GetDataArray& v) {		
			avro::encode(e, v.m_uri);
		}		
		static void decode(Decoder& e, Energistics::Protocol::DataArray::GetDataArray& v) {		
			avro::decode(e, v.m_uri);
		}		
	};	
}
namespace Energistics {
	namespace Protocol {	
		namespace DataArray {		
			struct GetDataArraySlice{			
				std::string m_uri;
				std::vector<int64_t> m_start;
				std::vector<int64_t> m_count;
				static const int messageTypeId=3;
				static const int protocolId=Energistics::Datatypes::Protocols::DataArray;
			};			
			typedef boost::shared_ptr<GetDataArraySlice> GetDataArraySlicePtr;
			const int GETDATAARRAYSLICE=3;
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Protocol::DataArray::GetDataArraySlice> {	
		static void encode(Encoder& e, const Energistics::Protocol::DataArray::GetDataArraySlice& v) {		
			avro::encode(e, v.m_uri);
			avro::encode(e, v.m_start);
			avro::encode(e, v.m_count);
		}		
		static void decode(Decoder& e, Energistics::Protocol::DataArray::GetDataArraySlice& v) {		
			avro::decode(e, v.m_uri);
			avro::decode(e, v.m_start);
			avro::decode(e, v.m_count);
		}		
	};	
}
namespace Energistics {
	namespace Protocol {	
		namespace DataArray {		
			struct PutDataArray{			
				std::string m_uri;
				Energistics::Datatypes::AnyArray m_data;
				std::vector<int64_t> m_dimensions;
				static const int messageTypeId=4;
				static const int protocolId=Energistics::Datatypes::Protocols::DataArray;
			};			
			typedef boost::shared_ptr<PutDataArray> PutDataArrayPtr;
			const int PUTDATAARRAY=4;
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Protocol::DataArray::PutDataArray> {	
		static void encode(Encoder& e, const Energistics::Protocol::DataArray::PutDataArray& v) {		
			avro::encode(e, v.m_uri);
			avro::encode(e, v.m_data);
			avro::encode(e, v.m_dimensions);
		}		
		static void decode(Decoder& e, Energistics::Protocol::DataArray::PutDataArray& v) {		
			avro::decode(e, v.m_uri);
			avro::decode(e, v.m_data);
			avro::decode(e, v.m_dimensions);
		}		
	};	
}
namespace Energistics {
	namespace Protocol {	
		namespace DataArray {		
			struct PutDataArraySlice{			
				std::string m_uri;
				Energistics::Datatypes::AnyArray m_data;
				std::vector<int64_t> m_dimensions;
				std::vector<int64_t> m_start;
				std::vector<int64_t> m_count;
				static const int messageTypeId=5;
				static const int protocolId=Energistics::Datatypes::Protocols::DataArray;
			};			
			typedef boost::shared_ptr<PutDataArraySlice> PutDataArraySlicePtr;
			const int PUTDATAARRAYSLICE=5;
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Protocol::DataArray::PutDataArraySlice> {	
		static void encode(Encoder& e, const Energistics::Protocol::DataArray::PutDataArraySlice& v) {		
			avro::encode(e, v.m_uri);
			avro::encode(e, v.m_data);
			avro::encode(e, v.m_dimensions);
			avro::encode(e, v.m_start);
			avro::encode(e, v.m_count);
		}		
		static void decode(Decoder& e, Energistics::Protocol::DataArray::PutDataArraySlice& v) {		
			avro::decode(e, v.m_uri);
			avro::decode(e, v.m_data);
			avro::decode(e, v.m_dimensions);
			avro::decode(e, v.m_start);
			avro::decode(e, v.m_count);
		}		
	};	
}
namespace Energistics {
	namespace Protocol {	
		namespace DirectedDiscovery {		
			struct GetContent{			
				std::string m_uri;
				static const int messageTypeId=1;
				static const int protocolId=Energistics::Datatypes::Protocols::DirectedDiscovery;
			};			
			typedef boost::shared_ptr<GetContent> GetContentPtr;
			const int GETCONTENT=1;
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Protocol::DirectedDiscovery::GetContent> {	
		static void encode(Encoder& e, const Energistics::Protocol::DirectedDiscovery::GetContent& v) {		
			avro::encode(e, v.m_uri);
		}		
		static void decode(Decoder& e, Energistics::Protocol::DirectedDiscovery::GetContent& v) {		
			avro::decode(e, v.m_uri);
		}		
	};	
}
namespace Energistics {
	namespace Protocol {	
		namespace DirectedDiscovery {		
			struct GetResourcesResponse{			
				Energistics::Datatypes::Object::Resource m_resource;
				static const int messageTypeId=2;
				static const int protocolId=Energistics::Datatypes::Protocols::DirectedDiscovery;
			};			
			typedef boost::shared_ptr<GetResourcesResponse> GetResourcesResponsePtr;
			const int GETRESOURCESRESPONSE=2;
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Protocol::DirectedDiscovery::GetResourcesResponse> {	
		static void encode(Encoder& e, const Energistics::Protocol::DirectedDiscovery::GetResourcesResponse& v) {		
			avro::encode(e, v.m_resource);
		}		
		static void decode(Decoder& e, Energistics::Protocol::DirectedDiscovery::GetResourcesResponse& v) {		
			avro::decode(e, v.m_resource);
		}		
	};	
}
namespace Energistics {
	namespace Protocol {	
		namespace DirectedDiscovery {		
			struct GetSourceFolders{			
				std::string m_uri;
				static const int messageTypeId=3;
				static const int protocolId=Energistics::Datatypes::Protocols::DirectedDiscovery;
			};			
			typedef boost::shared_ptr<GetSourceFolders> GetSourceFoldersPtr;
			const int GETSOURCEFOLDERS=3;
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Protocol::DirectedDiscovery::GetSourceFolders> {	
		static void encode(Encoder& e, const Energistics::Protocol::DirectedDiscovery::GetSourceFolders& v) {		
			avro::encode(e, v.m_uri);
		}		
		static void decode(Decoder& e, Energistics::Protocol::DirectedDiscovery::GetSourceFolders& v) {		
			avro::decode(e, v.m_uri);
		}		
	};	
}
namespace Energistics {
	namespace Protocol {	
		namespace DirectedDiscovery {		
			struct GetTargetFolders{			
				std::string m_uri;
				static const int messageTypeId=4;
				static const int protocolId=Energistics::Datatypes::Protocols::DirectedDiscovery;
			};			
			typedef boost::shared_ptr<GetTargetFolders> GetTargetFoldersPtr;
			const int GETTARGETFOLDERS=4;
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Protocol::DirectedDiscovery::GetTargetFolders> {	
		static void encode(Encoder& e, const Energistics::Protocol::DirectedDiscovery::GetTargetFolders& v) {		
			avro::encode(e, v.m_uri);
		}		
		static void decode(Decoder& e, Energistics::Protocol::DirectedDiscovery::GetTargetFolders& v) {		
			avro::decode(e, v.m_uri);
		}		
	};	
}
namespace Energistics {
	namespace Protocol {	
		namespace Discovery {		
			struct GetResources{			
				std::string m_uri;
				static const int messageTypeId=1;
				static const int protocolId=Energistics::Datatypes::Protocols::Discovery;
			};			
			typedef boost::shared_ptr<GetResources> GetResourcesPtr;
			const int GETRESOURCES=1;
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Protocol::Discovery::GetResources> {	
		static void encode(Encoder& e, const Energistics::Protocol::Discovery::GetResources& v) {		
			avro::encode(e, v.m_uri);
		}		
		static void decode(Decoder& e, Energistics::Protocol::Discovery::GetResources& v) {		
			avro::decode(e, v.m_uri);
		}		
	};	
}
namespace Energistics {
	namespace Protocol {	
		namespace Discovery {		
			struct GetResourcesResponse{			
				Energistics::Datatypes::Object::Resource m_resource;
				static const int messageTypeId=2;
				static const int protocolId=Energistics::Datatypes::Protocols::Discovery;
			};			
			typedef boost::shared_ptr<GetResourcesResponse> GetResourcesResponsePtr;
			const int GETRESOURCESRESPONSE=2;
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Protocol::Discovery::GetResourcesResponse> {	
		static void encode(Encoder& e, const Energistics::Protocol::Discovery::GetResourcesResponse& v) {		
			avro::encode(e, v.m_resource);
		}		
		static void decode(Decoder& e, Energistics::Protocol::Discovery::GetResourcesResponse& v) {		
			avro::decode(e, v.m_resource);
		}		
	};	
}
namespace Energistics {
	namespace Protocol {	
		namespace DiscoveryQuery {		
			struct FindResources{			
				std::string m_uri;
				static const int messageTypeId=1;
				static const int protocolId=Energistics::Datatypes::Protocols::DiscoveryQuery;
			};			
			typedef boost::shared_ptr<FindResources> FindResourcesPtr;
			const int FINDRESOURCES=1;
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Protocol::DiscoveryQuery::FindResources> {	
		static void encode(Encoder& e, const Energistics::Protocol::DiscoveryQuery::FindResources& v) {		
			avro::encode(e, v.m_uri);
		}		
		static void decode(Decoder& e, Energistics::Protocol::DiscoveryQuery::FindResources& v) {		
			avro::decode(e, v.m_uri);
		}		
	};	
}
namespace Energistics {
	namespace Protocol {	
		namespace DiscoveryQuery {		
			struct FindResourcesResponse{			
				Energistics::Datatypes::Object::Resource m_resource;
				std::string m_serverSortOrder;
				static const int messageTypeId=2;
				static const int protocolId=Energistics::Datatypes::Protocols::DiscoveryQuery;
			};			
			typedef boost::shared_ptr<FindResourcesResponse> FindResourcesResponsePtr;
			const int FINDRESOURCESRESPONSE=2;
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Protocol::DiscoveryQuery::FindResourcesResponse> {	
		static void encode(Encoder& e, const Energistics::Protocol::DiscoveryQuery::FindResourcesResponse& v) {		
			avro::encode(e, v.m_resource);
			avro::encode(e, v.m_serverSortOrder);
		}		
		static void decode(Decoder& e, Energistics::Protocol::DiscoveryQuery::FindResourcesResponse& v) {		
			avro::decode(e, v.m_resource);
			avro::decode(e, v.m_serverSortOrder);
		}		
	};	
}
namespace Energistics {
	namespace Protocol {	
		namespace GrowingObject {		
			struct DeletePart{			
				std::string m_uri;
				std::string m_uid;
				static const int messageTypeId=1;
				static const int protocolId=Energistics::Datatypes::Protocols::GrowingObject;
			};			
			typedef boost::shared_ptr<DeletePart> DeletePartPtr;
			const int DELETEPART=1;
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Protocol::GrowingObject::DeletePart> {	
		static void encode(Encoder& e, const Energistics::Protocol::GrowingObject::DeletePart& v) {		
			avro::encode(e, v.m_uri);
			avro::encode(e, v.m_uid);
		}		
		static void decode(Decoder& e, Energistics::Protocol::GrowingObject::DeletePart& v) {		
			avro::decode(e, v.m_uri);
			avro::decode(e, v.m_uid);
		}		
	};	
}
namespace Energistics {
	namespace Protocol {	
		namespace GrowingObject {		
			struct DeletePartsByRange{			
				std::string m_uri;
				Energistics::Datatypes::Object::GrowingObjectIndex m_startIndex;
				Energistics::Datatypes::Object::GrowingObjectIndex m_endIndex;
				bool m_includeOverlappingIntervals=false;
				static const int messageTypeId=2;
				static const int protocolId=Energistics::Datatypes::Protocols::GrowingObject;
			};			
			typedef boost::shared_ptr<DeletePartsByRange> DeletePartsByRangePtr;
			const int DELETEPARTSBYRANGE=2;
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Protocol::GrowingObject::DeletePartsByRange> {	
		static void encode(Encoder& e, const Energistics::Protocol::GrowingObject::DeletePartsByRange& v) {		
			avro::encode(e, v.m_uri);
			avro::encode(e, v.m_startIndex);
			avro::encode(e, v.m_endIndex);
			avro::encode(e, v.m_includeOverlappingIntervals);
		}		
		static void decode(Decoder& e, Energistics::Protocol::GrowingObject::DeletePartsByRange& v) {		
			avro::decode(e, v.m_uri);
			avro::decode(e, v.m_startIndex);
			avro::decode(e, v.m_endIndex);
			avro::decode(e, v.m_includeOverlappingIntervals);
		}		
	};	
}
namespace Energistics {
	namespace Protocol {	
		namespace GrowingObject {		
			struct DescribeParts{			
				std::string m_uri;
				static const int messageTypeId=8;
				static const int protocolId=Energistics::Datatypes::Protocols::GrowingObject;
			};			
			typedef boost::shared_ptr<DescribeParts> DescribePartsPtr;
			const int DESCRIBEPARTS=8;
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Protocol::GrowingObject::DescribeParts> {	
		static void encode(Encoder& e, const Energistics::Protocol::GrowingObject::DescribeParts& v) {		
			avro::encode(e, v.m_uri);
		}		
		static void decode(Decoder& e, Energistics::Protocol::GrowingObject::DescribeParts& v) {		
			avro::decode(e, v.m_uri);
		}		
	};	
}
namespace Energistics {
	namespace Protocol {	
		namespace GrowingObject {		
			struct GetPart{			
				std::string m_uri;
				std::string m_uid;
				static const int messageTypeId=3;
				static const int protocolId=Energistics::Datatypes::Protocols::GrowingObject;
			};			
			typedef boost::shared_ptr<GetPart> GetPartPtr;
			const int GETPART=3;
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Protocol::GrowingObject::GetPart> {	
		static void encode(Encoder& e, const Energistics::Protocol::GrowingObject::GetPart& v) {		
			avro::encode(e, v.m_uri);
			avro::encode(e, v.m_uid);
		}		
		static void decode(Decoder& e, Energistics::Protocol::GrowingObject::GetPart& v) {		
			avro::decode(e, v.m_uri);
			avro::decode(e, v.m_uid);
		}		
	};	
}
namespace Energistics {
	namespace Protocol {	
		namespace GrowingObject {		
			struct GetPartsByRange{			
				std::string m_uri;
				Energistics::Datatypes::Object::GrowingObjectIndex m_startIndex;
				Energistics::Datatypes::Object::GrowingObjectIndex m_endIndex;
				std::string m_uom;
				bool m_includeOverlappingIntervals=false;
				static const int messageTypeId=4;
				static const int protocolId=Energistics::Datatypes::Protocols::GrowingObject;
			};			
			typedef boost::shared_ptr<GetPartsByRange> GetPartsByRangePtr;
			const int GETPARTSBYRANGE=4;
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Protocol::GrowingObject::GetPartsByRange> {	
		static void encode(Encoder& e, const Energistics::Protocol::GrowingObject::GetPartsByRange& v) {		
			avro::encode(e, v.m_uri);
			avro::encode(e, v.m_startIndex);
			avro::encode(e, v.m_endIndex);
			avro::encode(e, v.m_uom);
			avro::encode(e, v.m_includeOverlappingIntervals);
		}		
		static void decode(Decoder& e, Energistics::Protocol::GrowingObject::GetPartsByRange& v) {		
			avro::decode(e, v.m_uri);
			avro::decode(e, v.m_startIndex);
			avro::decode(e, v.m_endIndex);
			avro::decode(e, v.m_uom);
			avro::decode(e, v.m_includeOverlappingIntervals);
		}		
	};	
}
namespace Energistics {
	namespace Protocol {	
		namespace GrowingObject {		
			struct ObjectPart{			
				std::string m_uri;
				std::string m_uid;
				std::string m_contentType;
				std::string m_data;
				static const int messageTypeId=6;
				static const int protocolId=Energistics::Datatypes::Protocols::GrowingObject;
			};			
			typedef boost::shared_ptr<ObjectPart> ObjectPartPtr;
			const int OBJECTPART=6;
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Protocol::GrowingObject::ObjectPart> {	
		static void encode(Encoder& e, const Energistics::Protocol::GrowingObject::ObjectPart& v) {		
			avro::encode(e, v.m_uri);
			avro::encode(e, v.m_uid);
			avro::encode(e, v.m_contentType);
			avro::encode(e, v.m_data);
		}		
		static void decode(Decoder& e, Energistics::Protocol::GrowingObject::ObjectPart& v) {		
			avro::decode(e, v.m_uri);
			avro::decode(e, v.m_uid);
			avro::decode(e, v.m_contentType);
			avro::decode(e, v.m_data);
		}		
	};	
}
namespace Energistics {
	namespace Protocol {	
		namespace GrowingObject {		
			struct PartMetadataindexDepthDatum_t {
			private:			
				size_t idx_=0;
				boost::any value_;
						
			public:			
				size_t idx() const { return idx_; }
				bool is_null() const { return idx_==0; }
				void set_null() { idx_=0; value_ = boost::any(); }
				std::string& get_string()  {				
					if (idx_ != 1) {					
						throw avro::Exception("Invalid type for union.");
					}					
					return boost::any_cast< std::string& >(value_);
				}				
				void set_string(const std::string& v) {				
					idx_ = 1;
					value_ = v;
				}				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Protocol::GrowingObject::PartMetadataindexDepthDatum_t> {
	
		static void encode(Encoder& e, Energistics::Protocol::GrowingObject::PartMetadataindexDepthDatum_t v) {
		
			e.encodeUnionIndex(v.idx());
			switch (v.idx()) {			
				case 0:				
					e.encodeNull();
					break;								
				case 1:				
					avro::encode(e, v.get_string());
					break;								
			}			
		}		
		static void decode(Decoder& d, Energistics::Protocol::GrowingObject::PartMetadataindexDepthDatum_t& v) {
		
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
						std::string vv;
						avro::decode(d, vv);
						v.set_string(vv);
					}					
					break;								
			}			
		}		
	};	
}

namespace Energistics {
	namespace Protocol {	
		namespace GrowingObject {		
			struct PartMetadatastartIndex_t {
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
namespace avro {
	template<> struct codec_traits<Energistics::Protocol::GrowingObject::PartMetadatastartIndex_t> {
	
		static void encode(Encoder& e, Energistics::Protocol::GrowingObject::PartMetadatastartIndex_t v) {
		
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
		static void decode(Decoder& d, Energistics::Protocol::GrowingObject::PartMetadatastartIndex_t& v) {
		
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
	namespace Protocol {	
		namespace GrowingObject {		
			struct PartMetadataendIndex_t {
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
namespace avro {
	template<> struct codec_traits<Energistics::Protocol::GrowingObject::PartMetadataendIndex_t> {
	
		static void encode(Encoder& e, Energistics::Protocol::GrowingObject::PartMetadataendIndex_t v) {
		
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
		static void decode(Decoder& d, Energistics::Protocol::GrowingObject::PartMetadataendIndex_t& v) {
		
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
	namespace Protocol {	
		namespace GrowingObject {		
			struct PartMetadatauuid_t {
			private:			
				size_t idx_=0;
				boost::any value_;
						
			public:			
				size_t idx() const { return idx_; }
				bool is_null() const { return idx_==0; }
				void set_null() { idx_=0; value_ = boost::any(); }
				std::string& get_string()  {				
					if (idx_ != 1) {					
						throw avro::Exception("Invalid type for union.");
					}					
					return boost::any_cast< std::string& >(value_);
				}				
				void set_string(const std::string& v) {				
					idx_ = 1;
					value_ = v;
				}				
			};			
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Protocol::GrowingObject::PartMetadatauuid_t> {
	
		static void encode(Encoder& e, Energistics::Protocol::GrowingObject::PartMetadatauuid_t v) {
		
			e.encodeUnionIndex(v.idx());
			switch (v.idx()) {			
				case 0:				
					e.encodeNull();
					break;								
				case 1:				
					avro::encode(e, v.get_string());
					break;								
			}			
		}		
		static void decode(Decoder& d, Energistics::Protocol::GrowingObject::PartMetadatauuid_t& v) {
		
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
						std::string vv;
						avro::decode(d, vv);
						v.set_string(vv);
					}					
					break;								
			}			
		}		
	};	
}

namespace Energistics {
	namespace Protocol {	
		namespace GrowingObject {		
			struct PartMetadata{			
				std::string m_growingObjectUri;
				Energistics::Datatypes::ChannelData::ChannelIndexTypes m_indexType;
				std::string m_indexUom;
				Energistics::Protocol::GrowingObject::PartMetadataindexDepthDatum_t m_indexDepthDatum;
				Energistics::Datatypes::ChannelData::IndexDirections m_indexDirection;
				std::string m_name;
				Energistics::Protocol::GrowingObject::PartMetadatastartIndex_t m_startIndex;
				Energistics::Protocol::GrowingObject::PartMetadataendIndex_t m_endIndex;
				std::string m_description;
				Energistics::Protocol::GrowingObject::PartMetadatauuid_t m_uuid;
				std::map<std::string, Energistics::Datatypes::DataValue> m_customData;
				static const int messageTypeId=9;
				static const int protocolId=Energistics::Datatypes::Protocols::GrowingObject;
			};			
			typedef boost::shared_ptr<PartMetadata> PartMetadataPtr;
			const int PARTMETADATA=9;
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Protocol::GrowingObject::PartMetadata> {	
		static void encode(Encoder& e, const Energistics::Protocol::GrowingObject::PartMetadata& v) {		
			avro::encode(e, v.m_growingObjectUri);
			avro::encode(e, v.m_indexType);
			avro::encode(e, v.m_indexUom);
			avro::encode(e, v.m_indexDepthDatum);
			avro::encode(e, v.m_indexDirection);
			avro::encode(e, v.m_name);
			avro::encode(e, v.m_startIndex);
			avro::encode(e, v.m_endIndex);
			avro::encode(e, v.m_description);
			avro::encode(e, v.m_uuid);
			avro::encode(e, v.m_customData);
		}		
		static void decode(Decoder& e, Energistics::Protocol::GrowingObject::PartMetadata& v) {		
			avro::decode(e, v.m_growingObjectUri);
			avro::decode(e, v.m_indexType);
			avro::decode(e, v.m_indexUom);
			avro::decode(e, v.m_indexDepthDatum);
			avro::decode(e, v.m_indexDirection);
			avro::decode(e, v.m_name);
			avro::decode(e, v.m_startIndex);
			avro::decode(e, v.m_endIndex);
			avro::decode(e, v.m_description);
			avro::decode(e, v.m_uuid);
			avro::decode(e, v.m_customData);
		}		
	};	
}
namespace Energistics {
	namespace Protocol {	
		namespace GrowingObject {		
			struct PutPart{			
				std::string m_uri;
				std::string m_uid;
				std::string m_contentType;
				std::string m_data;
				static const int messageTypeId=5;
				static const int protocolId=Energistics::Datatypes::Protocols::GrowingObject;
			};			
			typedef boost::shared_ptr<PutPart> PutPartPtr;
			const int PUTPART=5;
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Protocol::GrowingObject::PutPart> {	
		static void encode(Encoder& e, const Energistics::Protocol::GrowingObject::PutPart& v) {		
			avro::encode(e, v.m_uri);
			avro::encode(e, v.m_uid);
			avro::encode(e, v.m_contentType);
			avro::encode(e, v.m_data);
		}		
		static void decode(Decoder& e, Energistics::Protocol::GrowingObject::PutPart& v) {		
			avro::decode(e, v.m_uri);
			avro::decode(e, v.m_uid);
			avro::decode(e, v.m_contentType);
			avro::decode(e, v.m_data);
		}		
	};	
}
namespace Energistics {
	namespace Protocol {	
		namespace GrowingObject {		
			struct ReplacePartsByRange{			
				std::string m_uri;
				Energistics::Datatypes::Object::GrowingObjectIndex m_startIndex;
				Energistics::Datatypes::Object::GrowingObjectIndex m_endIndex;
				bool m_includeOverlappingIntervals=false;
				std::string m_contentType;
				std::string m_data;
				static const int messageTypeId=7;
				static const int protocolId=Energistics::Datatypes::Protocols::GrowingObject;
			};			
			typedef boost::shared_ptr<ReplacePartsByRange> ReplacePartsByRangePtr;
			const int REPLACEPARTSBYRANGE=7;
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Protocol::GrowingObject::ReplacePartsByRange> {	
		static void encode(Encoder& e, const Energistics::Protocol::GrowingObject::ReplacePartsByRange& v) {		
			avro::encode(e, v.m_uri);
			avro::encode(e, v.m_startIndex);
			avro::encode(e, v.m_endIndex);
			avro::encode(e, v.m_includeOverlappingIntervals);
			avro::encode(e, v.m_contentType);
			avro::encode(e, v.m_data);
		}		
		static void decode(Decoder& e, Energistics::Protocol::GrowingObject::ReplacePartsByRange& v) {		
			avro::decode(e, v.m_uri);
			avro::decode(e, v.m_startIndex);
			avro::decode(e, v.m_endIndex);
			avro::decode(e, v.m_includeOverlappingIntervals);
			avro::decode(e, v.m_contentType);
			avro::decode(e, v.m_data);
		}		
	};	
}
namespace Energistics {
	namespace Protocol {	
		namespace GrowingObjectNotification {		
			struct CancelPartNotification{			
				std::string m_requestUuid;
				static const int messageTypeId=4;
				static const int protocolId=Energistics::Datatypes::Protocols::GrowingObjectNotification;
			};			
			typedef boost::shared_ptr<CancelPartNotification> CancelPartNotificationPtr;
			const int CANCELPARTNOTIFICATION=4;
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Protocol::GrowingObjectNotification::CancelPartNotification> {	
		static void encode(Encoder& e, const Energistics::Protocol::GrowingObjectNotification::CancelPartNotification& v) {		
			avro::encode(e, v.m_requestUuid);
		}		
		static void decode(Decoder& e, Energistics::Protocol::GrowingObjectNotification::CancelPartNotification& v) {		
			avro::decode(e, v.m_requestUuid);
		}		
	};	
}
namespace Energistics {
	namespace Protocol {	
		namespace GrowingObjectNotification {		
			struct PartChangeNotification{			
				Energistics::Datatypes::Object::ObjectChangeTypes m_changeType;
				int64_t m_changeTime;
				std::string m_uri;
				std::string m_contentType;
				std::string m_data;
				static const int messageTypeId=2;
				static const int protocolId=Energistics::Datatypes::Protocols::GrowingObjectNotification;
			};			
			typedef boost::shared_ptr<PartChangeNotification> PartChangeNotificationPtr;
			const int PARTCHANGENOTIFICATION=2;
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Protocol::GrowingObjectNotification::PartChangeNotification> {	
		static void encode(Encoder& e, const Energistics::Protocol::GrowingObjectNotification::PartChangeNotification& v) {		
			avro::encode(e, v.m_changeType);
			avro::encode(e, v.m_changeTime);
			avro::encode(e, v.m_uri);
			avro::encode(e, v.m_contentType);
			avro::encode(e, v.m_data);
		}		
		static void decode(Decoder& e, Energistics::Protocol::GrowingObjectNotification::PartChangeNotification& v) {		
			avro::decode(e, v.m_changeType);
			avro::decode(e, v.m_changeTime);
			avro::decode(e, v.m_uri);
			avro::decode(e, v.m_contentType);
			avro::decode(e, v.m_data);
		}		
	};	
}
namespace Energistics {
	namespace Protocol {	
		namespace GrowingObjectNotification {		
			struct PartDeleteNotification{			
				Energistics::Datatypes::Object::ObjectChange m_delete;
				static const int messageTypeId=3;
				static const int protocolId=Energistics::Datatypes::Protocols::GrowingObjectNotification;
			};			
			typedef boost::shared_ptr<PartDeleteNotification> PartDeleteNotificationPtr;
			const int PARTDELETENOTIFICATION=3;
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Protocol::GrowingObjectNotification::PartDeleteNotification> {	
		static void encode(Encoder& e, const Energistics::Protocol::GrowingObjectNotification::PartDeleteNotification& v) {		
			avro::encode(e, v.m_delete);
		}		
		static void decode(Decoder& e, Energistics::Protocol::GrowingObjectNotification::PartDeleteNotification& v) {		
			avro::decode(e, v.m_delete);
		}		
	};	
}
namespace Energistics {
	namespace Protocol {	
		namespace GrowingObjectNotification {		
			struct RequestPartNotification{			
				Energistics::Datatypes::Object::NotificationRequestRecord m_request;
				static const int messageTypeId=1;
				static const int protocolId=Energistics::Datatypes::Protocols::GrowingObjectNotification;
			};			
			typedef boost::shared_ptr<RequestPartNotification> RequestPartNotificationPtr;
			const int REQUESTPARTNOTIFICATION=1;
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Protocol::GrowingObjectNotification::RequestPartNotification> {	
		static void encode(Encoder& e, const Energistics::Protocol::GrowingObjectNotification::RequestPartNotification& v) {		
			avro::encode(e, v.m_request);
		}		
		static void decode(Decoder& e, Energistics::Protocol::GrowingObjectNotification::RequestPartNotification& v) {		
			avro::decode(e, v.m_request);
		}		
	};	
}
namespace Energistics {
	namespace Protocol {	
		namespace Store {		
			struct DeleteObject{			
				std::string m_uri;
				static const int messageTypeId=3;
				static const int protocolId=Energistics::Datatypes::Protocols::Store;
			};			
			typedef boost::shared_ptr<DeleteObject> DeleteObjectPtr;
			const int DELETEOBJECT=3;
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Protocol::Store::DeleteObject> {	
		static void encode(Encoder& e, const Energistics::Protocol::Store::DeleteObject& v) {		
			avro::encode(e, v.m_uri);
		}		
		static void decode(Decoder& e, Energistics::Protocol::Store::DeleteObject& v) {		
			avro::decode(e, v.m_uri);
		}		
	};	
}
namespace Energistics {
	namespace Protocol {	
		namespace Store {		
			struct GetObject{			
				std::string m_uri;
				static const int messageTypeId=1;
				static const int protocolId=Energistics::Datatypes::Protocols::Store;
			};			
			typedef boost::shared_ptr<GetObject> GetObjectPtr;
			const int GETOBJECT=1;
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Protocol::Store::GetObject> {	
		static void encode(Encoder& e, const Energistics::Protocol::Store::GetObject& v) {		
			avro::encode(e, v.m_uri);
		}		
		static void decode(Decoder& e, Energistics::Protocol::Store::GetObject& v) {		
			avro::decode(e, v.m_uri);
		}		
	};	
}
namespace Energistics {
	namespace Protocol {	
		namespace Store {		
			struct Object{			
				Energistics::Datatypes::Object::DataObject m_dataObject;
				static const int messageTypeId=4;
				static const int protocolId=Energistics::Datatypes::Protocols::Store;
			};			
			typedef boost::shared_ptr<Object> ObjectPtr;
			const int OBJECT=4;
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Protocol::Store::Object> {	
		static void encode(Encoder& e, const Energistics::Protocol::Store::Object& v) {		
			avro::encode(e, v.m_dataObject);
		}		
		static void decode(Decoder& e, Energistics::Protocol::Store::Object& v) {		
			avro::decode(e, v.m_dataObject);
		}		
	};	
}
namespace Energistics {
	namespace Protocol {	
		namespace Store {		
			struct PutObject{			
				Energistics::Datatypes::Object::DataObject m_dataObject;
				static const int messageTypeId=2;
				static const int protocolId=Energistics::Datatypes::Protocols::Store;
			};			
			typedef boost::shared_ptr<PutObject> PutObjectPtr;
			const int PUTOBJECT=2;
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Protocol::Store::PutObject> {	
		static void encode(Encoder& e, const Energistics::Protocol::Store::PutObject& v) {		
			avro::encode(e, v.m_dataObject);
		}		
		static void decode(Decoder& e, Energistics::Protocol::Store::PutObject& v) {		
			avro::decode(e, v.m_dataObject);
		}		
	};	
}
namespace Energistics {
	namespace Protocol {	
		namespace GrowingObjectQuery {		
			struct FindGrowingPartsResponse{			
				std::string m_uri;
				std::string m_uid;
				std::string m_contentType;
				std::string m_data;
				std::string m_serverSortOrder;
				static const int messageTypeId=2;
				static const int protocolId=Energistics::Datatypes::Protocols::GrowingObjectQuery;
			};			
			typedef boost::shared_ptr<FindGrowingPartsResponse> FindGrowingPartsResponsePtr;
			const int FINDGROWINGPARTSRESPONSE=2;
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Protocol::GrowingObjectQuery::FindGrowingPartsResponse> {	
		static void encode(Encoder& e, const Energistics::Protocol::GrowingObjectQuery::FindGrowingPartsResponse& v) {		
			avro::encode(e, v.m_uri);
			avro::encode(e, v.m_uid);
			avro::encode(e, v.m_contentType);
			avro::encode(e, v.m_data);
			avro::encode(e, v.m_serverSortOrder);
		}		
		static void decode(Decoder& e, Energistics::Protocol::GrowingObjectQuery::FindGrowingPartsResponse& v) {		
			avro::decode(e, v.m_uri);
			avro::decode(e, v.m_uid);
			avro::decode(e, v.m_contentType);
			avro::decode(e, v.m_data);
			avro::decode(e, v.m_serverSortOrder);
		}		
	};	
}
namespace Energistics {
	namespace Protocol {	
		namespace GrowingObjectQuery {		
			struct FindGrowingParts{			
				std::string m_uri;
				static const int messageTypeId=1;
				static const int protocolId=Energistics::Datatypes::Protocols::GrowingObjectQuery;
			};			
			typedef boost::shared_ptr<FindGrowingParts> FindGrowingPartsPtr;
			const int FINDGROWINGPARTS=1;
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Protocol::GrowingObjectQuery::FindGrowingParts> {	
		static void encode(Encoder& e, const Energistics::Protocol::GrowingObjectQuery::FindGrowingParts& v) {		
			avro::encode(e, v.m_uri);
		}		
		static void decode(Decoder& e, Energistics::Protocol::GrowingObjectQuery::FindGrowingParts& v) {		
			avro::decode(e, v.m_uri);
		}		
	};	
}
namespace Energistics {
	namespace Protocol {	
		namespace StoreNotification {		
			struct CancelNotification{			
				std::string m_requestUuid;
				static const int messageTypeId=4;
				static const int protocolId=Energistics::Datatypes::Protocols::StoreNotification;
			};			
			typedef boost::shared_ptr<CancelNotification> CancelNotificationPtr;
			const int CANCELNOTIFICATION=4;
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Protocol::StoreNotification::CancelNotification> {	
		static void encode(Encoder& e, const Energistics::Protocol::StoreNotification::CancelNotification& v) {		
			avro::encode(e, v.m_requestUuid);
		}		
		static void decode(Decoder& e, Energistics::Protocol::StoreNotification::CancelNotification& v) {		
			avro::decode(e, v.m_requestUuid);
		}		
	};	
}
namespace Energistics {
	namespace Protocol {	
		namespace StoreNotification {		
			struct ChangeNotification{			
				Energistics::Datatypes::Object::ObjectChange m_change;
				static const int messageTypeId=2;
				static const int protocolId=Energistics::Datatypes::Protocols::StoreNotification;
			};			
			typedef boost::shared_ptr<ChangeNotification> ChangeNotificationPtr;
			const int CHANGENOTIFICATION=2;
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Protocol::StoreNotification::ChangeNotification> {	
		static void encode(Encoder& e, const Energistics::Protocol::StoreNotification::ChangeNotification& v) {		
			avro::encode(e, v.m_change);
		}		
		static void decode(Decoder& e, Energistics::Protocol::StoreNotification::ChangeNotification& v) {		
			avro::decode(e, v.m_change);
		}		
	};	
}
namespace Energistics {
	namespace Protocol {	
		namespace StoreNotification {		
			struct DeleteNotification{			
				Energistics::Datatypes::Object::ObjectChange m_delete;
				static const int messageTypeId=3;
				static const int protocolId=Energistics::Datatypes::Protocols::StoreNotification;
			};			
			typedef boost::shared_ptr<DeleteNotification> DeleteNotificationPtr;
			const int DELETENOTIFICATION=3;
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Protocol::StoreNotification::DeleteNotification> {	
		static void encode(Encoder& e, const Energistics::Protocol::StoreNotification::DeleteNotification& v) {		
			avro::encode(e, v.m_delete);
		}		
		static void decode(Decoder& e, Energistics::Protocol::StoreNotification::DeleteNotification& v) {		
			avro::decode(e, v.m_delete);
		}		
	};	
}
namespace Energistics {
	namespace Protocol {	
		namespace StoreNotification {		
			struct NotificationRequest{			
				Energistics::Datatypes::Object::NotificationRequestRecord m_request;
				static const int messageTypeId=1;
				static const int protocolId=Energistics::Datatypes::Protocols::StoreNotification;
			};			
			typedef boost::shared_ptr<NotificationRequest> NotificationRequestPtr;
			const int NOTIFICATIONREQUEST=1;
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Protocol::StoreNotification::NotificationRequest> {	
		static void encode(Encoder& e, const Energistics::Protocol::StoreNotification::NotificationRequest& v) {		
			avro::encode(e, v.m_request);
		}		
		static void decode(Decoder& e, Energistics::Protocol::StoreNotification::NotificationRequest& v) {		
			avro::decode(e, v.m_request);
		}		
	};	
}
namespace Energistics {
	namespace Protocol {	
		namespace StoreQuery {		
			struct FindObjects{			
				std::string m_uri;
				static const int messageTypeId=1;
				static const int protocolId=Energistics::Datatypes::Protocols::StoreQuery;
			};			
			typedef boost::shared_ptr<FindObjects> FindObjectsPtr;
			const int FINDOBJECTS=1;
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Protocol::StoreQuery::FindObjects> {	
		static void encode(Encoder& e, const Energistics::Protocol::StoreQuery::FindObjects& v) {		
			avro::encode(e, v.m_uri);
		}		
		static void decode(Decoder& e, Energistics::Protocol::StoreQuery::FindObjects& v) {		
			avro::decode(e, v.m_uri);
		}		
	};	
}
namespace Energistics {
	namespace Protocol {	
		namespace StoreQuery {		
			struct FindObjectsResponse{			
				Energistics::Datatypes::Object::DataObject m_dataObject;
				std::string m_serverSortOrder;
				static const int messageTypeId=2;
				static const int protocolId=Energistics::Datatypes::Protocols::StoreQuery;
			};			
			typedef boost::shared_ptr<FindObjectsResponse> FindObjectsResponsePtr;
			const int FINDOBJECTSRESPONSE=2;
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Protocol::StoreQuery::FindObjectsResponse> {	
		static void encode(Encoder& e, const Energistics::Protocol::StoreQuery::FindObjectsResponse& v) {		
			avro::encode(e, v.m_dataObject);
			avro::encode(e, v.m_serverSortOrder);
		}		
		static void decode(Decoder& e, Energistics::Protocol::StoreQuery::FindObjectsResponse& v) {		
			avro::decode(e, v.m_dataObject);
			avro::decode(e, v.m_serverSortOrder);
		}		
	};	
}
namespace Energistics {
	namespace Protocol {	
		namespace WitsmlSoap {		
			struct WMLS_AddToStore{			
				std::string m_WMLtypeIn;
				std::string m_XMLin;
				std::string m_OptionsIn;
				std::string m_CapabilitiesIn;
				static const int messageTypeId=1;
				static const int protocolId=Energistics::Datatypes::Protocols::WitsmlSoap;
			};			
			typedef boost::shared_ptr<WMLS_AddToStore> WMLS_AddToStorePtr;
			const int WMLS_ADDTOSTORE=1;
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Protocol::WitsmlSoap::WMLS_AddToStore> {	
		static void encode(Encoder& e, const Energistics::Protocol::WitsmlSoap::WMLS_AddToStore& v) {		
			avro::encode(e, v.m_WMLtypeIn);
			avro::encode(e, v.m_XMLin);
			avro::encode(e, v.m_OptionsIn);
			avro::encode(e, v.m_CapabilitiesIn);
		}		
		static void decode(Decoder& e, Energistics::Protocol::WitsmlSoap::WMLS_AddToStore& v) {		
			avro::decode(e, v.m_WMLtypeIn);
			avro::decode(e, v.m_XMLin);
			avro::decode(e, v.m_OptionsIn);
			avro::decode(e, v.m_CapabilitiesIn);
		}		
	};	
}
namespace Energistics {
	namespace Protocol {	
		namespace WitsmlSoap {		
			struct WMLS_DeleteFromStore{			
				std::string m_WMLtypeIn;
				std::string m_XMLin;
				std::string m_OptionsIn;
				std::string m_CapabilitiesIn;
				static const int messageTypeId=3;
				static const int protocolId=Energistics::Datatypes::Protocols::WitsmlSoap;
			};			
			typedef boost::shared_ptr<WMLS_DeleteFromStore> WMLS_DeleteFromStorePtr;
			const int WMLS_DELETEFROMSTORE=3;
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Protocol::WitsmlSoap::WMLS_DeleteFromStore> {	
		static void encode(Encoder& e, const Energistics::Protocol::WitsmlSoap::WMLS_DeleteFromStore& v) {		
			avro::encode(e, v.m_WMLtypeIn);
			avro::encode(e, v.m_XMLin);
			avro::encode(e, v.m_OptionsIn);
			avro::encode(e, v.m_CapabilitiesIn);
		}		
		static void decode(Decoder& e, Energistics::Protocol::WitsmlSoap::WMLS_DeleteFromStore& v) {		
			avro::decode(e, v.m_WMLtypeIn);
			avro::decode(e, v.m_XMLin);
			avro::decode(e, v.m_OptionsIn);
			avro::decode(e, v.m_CapabilitiesIn);
		}		
	};	
}
namespace Energistics {
	namespace Protocol {	
		namespace WitsmlSoap {		
			struct WMLS_GetBaseMsg{			
				int32_t m_ReturnValueIn;
				static const int messageTypeId=5;
				static const int protocolId=Energistics::Datatypes::Protocols::WitsmlSoap;
			};			
			typedef boost::shared_ptr<WMLS_GetBaseMsg> WMLS_GetBaseMsgPtr;
			const int WMLS_GETBASEMSG=5;
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Protocol::WitsmlSoap::WMLS_GetBaseMsg> {	
		static void encode(Encoder& e, const Energistics::Protocol::WitsmlSoap::WMLS_GetBaseMsg& v) {		
			avro::encode(e, v.m_ReturnValueIn);
		}		
		static void decode(Decoder& e, Energistics::Protocol::WitsmlSoap::WMLS_GetBaseMsg& v) {		
			avro::decode(e, v.m_ReturnValueIn);
		}		
	};	
}
namespace Energistics {
	namespace Protocol {	
		namespace WitsmlSoap {		
			struct WMLS_GetCap{			
				std::string m_OptionsIn;
				static const int messageTypeId=7;
				static const int protocolId=Energistics::Datatypes::Protocols::WitsmlSoap;
			};			
			typedef boost::shared_ptr<WMLS_GetCap> WMLS_GetCapPtr;
			const int WMLS_GETCAP=7;
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Protocol::WitsmlSoap::WMLS_GetCap> {	
		static void encode(Encoder& e, const Energistics::Protocol::WitsmlSoap::WMLS_GetCap& v) {		
			avro::encode(e, v.m_OptionsIn);
		}		
		static void decode(Decoder& e, Energistics::Protocol::WitsmlSoap::WMLS_GetCap& v) {		
			avro::decode(e, v.m_OptionsIn);
		}		
	};	
}
namespace Energistics {
	namespace Protocol {	
		namespace WitsmlSoap {		
			struct WMLS_GetFromStore{			
				std::string m_WMLtypeIn;
				std::string m_XMLin;
				std::string m_OptionsIn;
				std::string m_CapabilitiesIn;
				static const int messageTypeId=9;
				static const int protocolId=Energistics::Datatypes::Protocols::WitsmlSoap;
			};			
			typedef boost::shared_ptr<WMLS_GetFromStore> WMLS_GetFromStorePtr;
			const int WMLS_GETFROMSTORE=9;
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Protocol::WitsmlSoap::WMLS_GetFromStore> {	
		static void encode(Encoder& e, const Energistics::Protocol::WitsmlSoap::WMLS_GetFromStore& v) {		
			avro::encode(e, v.m_WMLtypeIn);
			avro::encode(e, v.m_XMLin);
			avro::encode(e, v.m_OptionsIn);
			avro::encode(e, v.m_CapabilitiesIn);
		}		
		static void decode(Decoder& e, Energistics::Protocol::WitsmlSoap::WMLS_GetFromStore& v) {		
			avro::decode(e, v.m_WMLtypeIn);
			avro::decode(e, v.m_XMLin);
			avro::decode(e, v.m_OptionsIn);
			avro::decode(e, v.m_CapabilitiesIn);
		}		
	};	
}
namespace Energistics {
	namespace Protocol {	
		namespace WitsmlSoap {		
			struct WMLS_GetVersion{			
				static const int messageTypeId=11;
				static const int protocolId=Energistics::Datatypes::Protocols::WitsmlSoap;
			};			
			typedef boost::shared_ptr<WMLS_GetVersion> WMLS_GetVersionPtr;
			const int WMLS_GETVERSION=11;
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Protocol::WitsmlSoap::WMLS_GetVersion> {	
		static void encode(Encoder& e, const Energistics::Protocol::WitsmlSoap::WMLS_GetVersion& v) {		
		}		
		static void decode(Decoder& e, Energistics::Protocol::WitsmlSoap::WMLS_GetVersion& v) {		
		}		
	};	
}
namespace Energistics {
	namespace Protocol {	
		namespace WitsmlSoap {		
			struct WMLS_UpdateInStore{			
				std::string m_WMLtypeIn;
				std::string m_XMLin;
				std::string m_OptionsIn;
				std::string m_CapabilitiesIn;
				static const int messageTypeId=13;
				static const int protocolId=Energistics::Datatypes::Protocols::WitsmlSoap;
			};			
			typedef boost::shared_ptr<WMLS_UpdateInStore> WMLS_UpdateInStorePtr;
			const int WMLS_UPDATEINSTORE=13;
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Protocol::WitsmlSoap::WMLS_UpdateInStore> {	
		static void encode(Encoder& e, const Energistics::Protocol::WitsmlSoap::WMLS_UpdateInStore& v) {		
			avro::encode(e, v.m_WMLtypeIn);
			avro::encode(e, v.m_XMLin);
			avro::encode(e, v.m_OptionsIn);
			avro::encode(e, v.m_CapabilitiesIn);
		}		
		static void decode(Decoder& e, Energistics::Protocol::WitsmlSoap::WMLS_UpdateInStore& v) {		
			avro::decode(e, v.m_WMLtypeIn);
			avro::decode(e, v.m_XMLin);
			avro::decode(e, v.m_OptionsIn);
			avro::decode(e, v.m_CapabilitiesIn);
		}		
	};	
}
namespace Energistics {
	namespace Protocol {	
		namespace WitsmlSoap {		
			struct WMSL_AddToStoreResponse{			
				int32_t m_Result;
				std::string m_SuppMsgOut;
				static const int messageTypeId=2;
				static const int protocolId=Energistics::Datatypes::Protocols::WitsmlSoap;
			};			
			typedef boost::shared_ptr<WMSL_AddToStoreResponse> WMSL_AddToStoreResponsePtr;
			const int WMSL_ADDTOSTORERESPONSE=2;
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Protocol::WitsmlSoap::WMSL_AddToStoreResponse> {	
		static void encode(Encoder& e, const Energistics::Protocol::WitsmlSoap::WMSL_AddToStoreResponse& v) {		
			avro::encode(e, v.m_Result);
			avro::encode(e, v.m_SuppMsgOut);
		}		
		static void decode(Decoder& e, Energistics::Protocol::WitsmlSoap::WMSL_AddToStoreResponse& v) {		
			avro::decode(e, v.m_Result);
			avro::decode(e, v.m_SuppMsgOut);
		}		
	};	
}
namespace Energistics {
	namespace Protocol {	
		namespace WitsmlSoap {		
			struct WMSL_DeleteFromStoreResponse{			
				int32_t m_Result;
				std::string m_SuppMsgOut;
				static const int messageTypeId=4;
				static const int protocolId=Energistics::Datatypes::Protocols::WitsmlSoap;
			};			
			typedef boost::shared_ptr<WMSL_DeleteFromStoreResponse> WMSL_DeleteFromStoreResponsePtr;
			const int WMSL_DELETEFROMSTORERESPONSE=4;
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Protocol::WitsmlSoap::WMSL_DeleteFromStoreResponse> {	
		static void encode(Encoder& e, const Energistics::Protocol::WitsmlSoap::WMSL_DeleteFromStoreResponse& v) {		
			avro::encode(e, v.m_Result);
			avro::encode(e, v.m_SuppMsgOut);
		}		
		static void decode(Decoder& e, Energistics::Protocol::WitsmlSoap::WMSL_DeleteFromStoreResponse& v) {		
			avro::decode(e, v.m_Result);
			avro::decode(e, v.m_SuppMsgOut);
		}		
	};	
}
namespace Energistics {
	namespace Protocol {	
		namespace WitsmlSoap {		
			struct WMSL_GetBaseMsgResponse{			
				std::string m_Result;
				static const int messageTypeId=6;
				static const int protocolId=Energistics::Datatypes::Protocols::WitsmlSoap;
			};			
			typedef boost::shared_ptr<WMSL_GetBaseMsgResponse> WMSL_GetBaseMsgResponsePtr;
			const int WMSL_GETBASEMSGRESPONSE=6;
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Protocol::WitsmlSoap::WMSL_GetBaseMsgResponse> {	
		static void encode(Encoder& e, const Energistics::Protocol::WitsmlSoap::WMSL_GetBaseMsgResponse& v) {		
			avro::encode(e, v.m_Result);
		}		
		static void decode(Decoder& e, Energistics::Protocol::WitsmlSoap::WMSL_GetBaseMsgResponse& v) {		
			avro::decode(e, v.m_Result);
		}		
	};	
}
namespace Energistics {
	namespace Protocol {	
		namespace WitsmlSoap {		
			struct WMSL_GetCapResponse{			
				int32_t m_Result;
				std::string m_CapabilitiesOut;
				std::string m_SuppMsgOut;
				static const int messageTypeId=8;
				static const int protocolId=Energistics::Datatypes::Protocols::WitsmlSoap;
			};			
			typedef boost::shared_ptr<WMSL_GetCapResponse> WMSL_GetCapResponsePtr;
			const int WMSL_GETCAPRESPONSE=8;
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Protocol::WitsmlSoap::WMSL_GetCapResponse> {	
		static void encode(Encoder& e, const Energistics::Protocol::WitsmlSoap::WMSL_GetCapResponse& v) {		
			avro::encode(e, v.m_Result);
			avro::encode(e, v.m_CapabilitiesOut);
			avro::encode(e, v.m_SuppMsgOut);
		}		
		static void decode(Decoder& e, Energistics::Protocol::WitsmlSoap::WMSL_GetCapResponse& v) {		
			avro::decode(e, v.m_Result);
			avro::decode(e, v.m_CapabilitiesOut);
			avro::decode(e, v.m_SuppMsgOut);
		}		
	};	
}
namespace Energistics {
	namespace Protocol {	
		namespace WitsmlSoap {		
			struct WMSL_GetFromStoreResponse{			
				int32_t m_Result;
				std::string m_XMLout;
				std::string m_SuppMsgOut;
				static const int messageTypeId=10;
				static const int protocolId=Energistics::Datatypes::Protocols::WitsmlSoap;
			};			
			typedef boost::shared_ptr<WMSL_GetFromStoreResponse> WMSL_GetFromStoreResponsePtr;
			const int WMSL_GETFROMSTORERESPONSE=10;
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Protocol::WitsmlSoap::WMSL_GetFromStoreResponse> {	
		static void encode(Encoder& e, const Energistics::Protocol::WitsmlSoap::WMSL_GetFromStoreResponse& v) {		
			avro::encode(e, v.m_Result);
			avro::encode(e, v.m_XMLout);
			avro::encode(e, v.m_SuppMsgOut);
		}		
		static void decode(Decoder& e, Energistics::Protocol::WitsmlSoap::WMSL_GetFromStoreResponse& v) {		
			avro::decode(e, v.m_Result);
			avro::decode(e, v.m_XMLout);
			avro::decode(e, v.m_SuppMsgOut);
		}		
	};	
}
namespace Energistics {
	namespace Protocol {	
		namespace WitsmlSoap {		
			struct WMSL_GetVersionResponse{			
				std::string m_Result;
				static const int messageTypeId=12;
				static const int protocolId=Energistics::Datatypes::Protocols::WitsmlSoap;
			};			
			typedef boost::shared_ptr<WMSL_GetVersionResponse> WMSL_GetVersionResponsePtr;
			const int WMSL_GETVERSIONRESPONSE=12;
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Protocol::WitsmlSoap::WMSL_GetVersionResponse> {	
		static void encode(Encoder& e, const Energistics::Protocol::WitsmlSoap::WMSL_GetVersionResponse& v) {		
			avro::encode(e, v.m_Result);
		}		
		static void decode(Decoder& e, Energistics::Protocol::WitsmlSoap::WMSL_GetVersionResponse& v) {		
			avro::decode(e, v.m_Result);
		}		
	};	
}
namespace Energistics {
	namespace Protocol {	
		namespace WitsmlSoap {		
			struct WMSL_UpdateInStoreResponse{			
				int32_t m_Result;
				std::string m_SuppMsgOut;
				static const int messageTypeId=14;
				static const int protocolId=Energistics::Datatypes::Protocols::WitsmlSoap;
			};			
			typedef boost::shared_ptr<WMSL_UpdateInStoreResponse> WMSL_UpdateInStoreResponsePtr;
			const int WMSL_UPDATEINSTORERESPONSE=14;
		};		
	};	
};
namespace avro {
	template<> struct codec_traits<Energistics::Protocol::WitsmlSoap::WMSL_UpdateInStoreResponse> {	
		static void encode(Encoder& e, const Energistics::Protocol::WitsmlSoap::WMSL_UpdateInStoreResponse& v) {		
			avro::encode(e, v.m_Result);
			avro::encode(e, v.m_SuppMsgOut);
		}		
		static void decode(Decoder& e, Energistics::Protocol::WitsmlSoap::WMSL_UpdateInStoreResponse& v) {		
			avro::decode(e, v.m_Result);
			avro::decode(e, v.m_SuppMsgOut);
		}		
	};	
}


#endif
