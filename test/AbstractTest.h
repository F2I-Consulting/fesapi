#pragma once

#include <iostream>

#if (defined(_WIN32) && _MSC_VER < 1600) || (defined(__GNUC__) && (__GNUC__ < 4 || (__GNUC__ == 4 && __GNUC_MINOR__ < 6)))
#include "tools/nullptr_emulation.h"
#endif

namespace common {
	class EpcDocument;
}

namespace commontest {
	/**
	 * This abstract class is the most top level testing class. Every test class must derive from it.  
	 */
	class AbstractTest {
	public:
		/**
		 * Creation of a testing object from an EPC document path. At serialize() call,
		 * exising .epc file will be erased. 
		 * @param epcDocPath the path of the .epc file (including .epc extension)
		 */
		AbstractTest(const std::string & epcDocPath);
		
		/**
		 * Creation of a testing object from an existing EPC document.
		 * @param epcDoc an existing EPC document
		 */
		AbstractTest(common::EpcDocument * epcDoc);

		virtual ~AbstractTest() {}

		/**
		 * This methods runs a serailization test. It handles the creation of an EPC document,
		 * calls initEpcDoc() and serialize the EPC document. The EPC document is deleted at the very end
		 * of this method.
		 */
		void serialize();

		/** 
		 * This methods runs a deserialization test. It handles the deserialization of an existing EPC document
		 * and calls readEpcDoc(). The EPC document is deleted at the very end of this method.
		 */
		void deserialize();
	
		/** 
		 * As initialization differs from one unit test to another, it is virtual in this most general testing class.
		 */ 
		virtual void initEpcDoc() = 0;

		/** 
		 * As reading differs from one unit test to another, it is virtual in this most general testing class.
		 */
		virtual void readEpcDoc() = 0;
	protected:
		common::EpcDocument* epcDoc;
		const std::string epcDocPath;
	};
}
