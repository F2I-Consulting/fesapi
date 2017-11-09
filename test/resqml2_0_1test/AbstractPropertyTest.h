#pragma once

#include "AbstractResqmlDataObjectTest.h"
#include <iostream>

namespace common {
	class EpcDocument;
}

namespace resqml2_0_1test {
	class AbstractPropertyTest : public AbstractResqmlDataObjectTest {
	public:
		/**
		 * Creation of a Resqml property testing object from an EPC document path. At serialize() call,
		 * exising .epc file will be erased. 
		 * @param epcDocPath the path of the .epc file (including .epc extension)
		 * @param uuid the uuid of the Resqml top level object to test
		 * @param title the title of the Resqml top level object to test
		 * @param uuidRepresentation the uuid of the supporting representation
		 * @param titleRepresentation the title of the supporting representation
		 */
		AbstractPropertyTest(const std::string & epcDocPath, const std::string & uuid, const std::string & title, const std::string & uuidRepresentation, const std::string & titleRepresentation);
		
		/**
		 * Creation of a Resqml property testing object from an existing EPC document.
		 * @param epcDoc an existing EPC document
		 * @param uuid the uuid of the Resqml top level object to test
		 * @param title the title of the Resqml top level object to test
		 * @param uuidRepresentation the uuid of the supporting representation
		 * @param titleRepresentation the title of the supporting representation
		 */
		AbstractPropertyTest(common::EpcDocument * epcDoc, const std::string & uuid, const std::string & title, const std::string & uuidRepresentation, const std::string & titleRepresentation);
		
		/**
		 * This methods overrides (and calls) AbstractObjectTest::readEpcDoc(). It includes a test for checking that the supporting representation uuid and title
		 * is consistantly readed. 
		 */
		void readEpcDoc();
	protected:
		const std::string uuidRepresentation;
		const std::string titleRepresentation;
	};
}