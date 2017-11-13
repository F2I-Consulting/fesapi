#pragma once

#include "AbstractResqmlDataObjectTest.h"
#include <iostream>

#include "proxies/stdsoap2.h"

namespace common {
	class EpcDocument;
}

namespace resqml2_0_1test {
	/**
	 * Base abstract class for testing a Resqml representation.
	 */
	class AbstractRepresentationTest : public AbstractResqmlDataObjectTest {
	public:
		/**
		 * Creation of a Resqml representation testing object from an EPC document path. At serialize() call,
		 * exising .epc file will be erased. 
		 * Remark: if xyz points values and count are provided, AbstractRepresentationTest::readEpcDoc() provides facilities 
		 * for automatically checking them at deserialization.
		 * @param epcDocPath the path of the .epc file (including .epc extension)
 		 * @param uuid the uuid of the Resqml top level object to test
		 * @param title the title of the Resqml top level object to test
		 * @param xyzPointCountOfAllPatches count of xyz points in the whole representation (default 0)
		 * @param xyzPointsOfAllPatchesInGlobalCrs xyz points values (default nullptr)
		 */
		AbstractRepresentationTest(const std::string & epcDocPath, const std::string & uuid, const std::string & title, const ULONG64 & xyzPointCountOfAllPatches = 0, double * xyzPointsOfAllPatchesInGlobalCrs = nullptr);
		
		/**
		 * Creation of a testing object from an existing EPC document.
		 * Remark: if xyz points values and count are provided, AbstractRepresentationTest::readEpcDoc() provides facilities 
		 * for automatically checking them at deserialization.
		 * @param epcDoc an existing EPC document
 		 * @param uuid the uuid of the Resqml top level object to test
		 * @param title the title of the Resqml top level object to test
		 * @param xyzPointCountOfAllPatches count of xyz points in the whole representation (default 0)
		 * @param xyzPointsOfAllPatchesInGlobalCrs xyz points values (default nullptr)
		 */
		AbstractRepresentationTest(common::EpcDocument* epcDoc, const std::string & uuid, const std::string & title, const ULONG64 & xyzPointCountOfAllPatches = 0, double * xyzPointsOfAllPatchesInGlobalCrs = nullptr);
		
		/**
		 * Overrides (and calls) AbstractObject::readEpcDoc(). 
		 * Remark: if xyz points values and count are provided (ie. if xyzPointsOfAllPatchesInGlobalCrs != nullptr), AbstractRepresentationTest::readEpcDoc() provides facilities 
		 * for automatically checking them at deserialization.
		 */
		void readEpcDoc();
	protected:
		double * xyzPointsOfAllPatchesInGlobalCrs;
		const ULONG64 xyzPointCountOfAllPatches;
	};
}
