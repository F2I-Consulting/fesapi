#pragma once

#include "AbstractResqmlDataObjectTest.h"
#include <iostream>

namespace common {
	class EpcDocument;
}

namespace resqml2_0_1test {
	class AbstractFeatureInterpretationTest : public AbstractResqmlDataObjectTest {
	public:
		/**
		 * Creation of a Resqml interpretation testing object from an EPC document path. At serialize() call,
		 * exising .epc file will be erased. 
		 * @param epcDocPath the path of the .epc file (including .epc extension)
		 * @param uuid the uuid of the Resqml top level object to test
		 * @param title the title of the Resqml top level object to test
		 * @param uuidFeature uuid of the interpreted feature
		 * @param titleFeature title of the interpreted feature
		 */
		AbstractFeatureInterpretationTest(const std::string & epcDocPath, const std::string & uuid, const std::string & title, const std::string & uuidFeature, const std::string & titleFeature);
		
		/**
		 * Creation of a Resqml interpretation testing object from an existing EPC document.
		 * @param epcDoc an existing EPC document
		 * @param uuid the uuid of the Resqml top level object to test
		 * @param title the title of the Resqml top level object to test
		 * @param uuidFeature uuid of the interpreted feature
		 * @param titleFeature title of the interpreted feature
		 */
		AbstractFeatureInterpretationTest(common::EpcDocument * epcDoc, const std::string & uuid, const std::string & title, const std::string & uuidFeature, const std::string & titleFeature);

		/**
		 * This methods overrides (and calls) AbstractObjectTest::readEpcDoc(). It includes a test for checking that the interpreted
		 * feature is consistantly readed. 
		 */
		void readEpcDoc();
	protected:
		const std::string uuidFeature;
		const std::string titleFeature;
	};
}