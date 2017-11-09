#pragma once

#include "resqml2_0_1test/AbstractFeatureInterpretationTest.h"

namespace common {
	class EpcDocument;
}

namespace resqml2_0_1test {
	class StratigraphicColumnRankInterpretationTest : public AbstractFeatureInterpretationTest {
	public:
		static const char* defaultUuid;
		static const char* defaultTitle;

		static const char* defaultOverburdenUuid;
		static const char* defaultOverburdenTitle;
		static const char* defaultOverburdenInterpUuid;
		static const char* defaultOverburdenInterpTitle;

		static const char* defaultUnderburdenUuid;
		static const char* defaultUnderburdenTitle;
		static const char* defaultUnderburdenInterpUuid;
		static const char* defaultUnderburdenInterpTitle;

		/**
		* Creation of a testing object from an EPC document path. At serialize() call,
		* exising .epc file will be erased. 
		* @param epcDocPath the path of the .epc file (including .epc extension)
		*/
		StratigraphicColumnRankInterpretationTest(const std::string & epcDocPath);
		StratigraphicColumnRankInterpretationTest(const std::string & epcDocPath, const std::string & uuid, const std::string & title, const std::string & uuidFeature, const std::string & titleFeature);

		/**
		* Creation of a testing object from an existing EPC document.
		* @param epcDoc an existing EPC document
		* @param init true if this object is created for initialization purpose else false if it is 
		* created for reading purpose. According to init value a iniEpcDoc() or readEpcDoc() is called.
		*/
		StratigraphicColumnRankInterpretationTest(common::EpcDocument* epcDoc, bool init);
		StratigraphicColumnRankInterpretationTest(common::EpcDocument* epcDoc, const std::string & uuid, const std::string & title, const std::string & uuidFeature, const std::string & titleFeature, bool init);
	protected:
		void initEpcDocHandler();
		void readEpcDocHandler();
	};
}