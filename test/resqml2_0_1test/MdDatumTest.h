#pragma once

#include "resqml2_0_1test/AbstractResqmlDataObjectTest.h"
#include <iostream>

namespace common {
	class EpcDocument;
}

namespace resqml2_0_1test {
	class MdDatumTest : public AbstractResqmlDataObjectTest {
	public:
		static const char* defaultUuid;
		static const char* defaultTitle;

		/**
		* Creation of a testing object from an EPC document path. At serialize() call,
		* exising .epc file will be erased. 
		* @param epcDocPath the path of the .epc file (including .epc extension)
		*/
		MdDatumTest(const std::string & epcDocPath);

		/**
		* Creation of a testing object from an existing EPC document.
		* @param epcDoc an existing EPC document
		* @param init true if this object is created for initialization purpose else false if it is 
		* created for reading purpose. According to init value a iniEpcDoc() or readEpcDoc() is called.
		*/
		MdDatumTest(common::EpcDocument* epcDoc, bool init);
	protected:
		void initEpcDocHandler();
		void readEpcDocHandler();
	};
}