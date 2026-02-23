/*-----------------------------------------------------------------------
Licensed to the Apache Software Foundation (ASF) under one
or more contributor license agreements.  See the NOTICE file
distributed with this work for additional information
regarding copyright ownership.  The ASF licenses this file
to you under the Apache License, Version 2.0 (the
"License"; you may not use this file except in compliance
with the License.  You may obtain a copy of the License at

  http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing,
software distributed under the License is distributed on an
"AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
KIND, either express or implied.  See the License for the
specific language governing permissions and limitations
under the License.
-----------------------------------------------------------------------*/
#include "ColumnBasedTableTest.h"

#include "catch.hpp"

#include "eml2/PropertyKind.h"

#include "eml2_3/ColumnBasedTable.h"

using namespace std;
using namespace EML2_NS;
using namespace RESQML2_NS;
using namespace eml2_3test;

ColumnBasedTableTest::ColumnBasedTableTest(const string & repoPath)
	: AbstractTest(repoPath) {
}

void ColumnBasedTableTest::initRepo() {
	auto* cbt = repo->createColumnBasedTable("866841eb-0c56-4b7d-96d6-f15f385deaf9", "KrPc");

	auto* pwls3RowIndex = repo->createPropertyKind("b313a407-720b-4c03-83de-0bb31d14c796", "row index", gsoap_eml2_3::eml23__QuantityClassKind::not_x0020a_x0020measure);
	auto* pwls3Saturation = repo->createPropertyKind("cfe9293f-d5a9-486d-815a-a957cace90b6", "saturation", gsoap_eml2_3::eml23__QuantityClassKind::dimensionless);
	auto* pwls3RelPerm = repo->createPropertyKind("8e3c5579-7efd-40d0-ab03-bc79452dd2db", "relative permeability", gsoap_eml2_3::eml23__QuantityClassKind::unitless);
	auto* pwls3CapPressure = repo->createPropertyKind("a816a113-1544-4f58-bc6d-7c030b65627b", "capillary pressure", gsoap_eml2_3::eml23__QuantityClassKind::pressure);

	cbt->pushBackColumnHeader(true, "Row indew", pwls3RowIndex);
	cbt->pushBackColumnHeader(false, "Water Saturation", pwls3Saturation);
	cbt->pushBackColumnHeader(false, "Water Relative Permeability", pwls3RelPerm);
	cbt->pushBackColumnHeader(false, "Oil Relative Permeability", pwls3RelPerm);
	cbt->pushBackColumnHeader(false, "Oil Water Capillary Pressure", pwls3CapPressure);

	int64_t rowIndex[] = { 0, 1, 2, 3, 4, 5, 6 };
	cbt->setInt64Values(0, rowIndex, 7);
	double watSat[] = { 0, 0.157, 0.173, 0.174325, 0.19, 0.19165, 0.207 };
	cbt->setDoubleValues(1, watSat, 7);
	std::vector<double> watRelPerm = { 0, 0, 0.000356, 0.0004392, 0.0014241, 0.0015969, 0.0032041 };
	cbt->setDoubleValues(2, watRelPerm);
	std::vector<std::string> rowIndexStr= { "ZERO", "ONE", "TWO", "THREE", "FOUR", "FIVE", "SIX"};
	cbt->setStringValues(3, rowIndexStr);
}

void ColumnBasedTableTest::readRepo() {
	const auto cbtSet = repo->getColumnBasedTableSet();
	REQUIRE(cbtSet.size() == 1);

	const auto* cbt = cbtSet[0];
	REQUIRE(cbt->getColumnCount() == 5);
	REQUIRE(cbt->getRowCount() == 7);
	REQUIRE(cbt->getPropertyKind(0)->getUuid() == "b313a407-720b-4c03-83de-0bb31d14c796");

	// HDF Int64 column
	REQUIRE(cbt->getDatatype(0) == COMMON_NS::AbstractObject::numericalDatatypeEnum::INT64);
	auto rowIndexColumn = cbt->getInt64Values(0);
	for (size_t i = 0; i < rowIndexColumn.size(); ++i) {
		REQUIRE(rowIndexColumn[i] == i);
	}

	// HDF Double column
	REQUIRE(cbt->getDatatype(1) == COMMON_NS::AbstractObject::numericalDatatypeEnum::DOUBLE);
	auto watSatColumn = cbt->getDoubleValues(1);
	REQUIRE(watSatColumn[0] == 0);
	REQUIRE(watSatColumn[1] == 0.157);
	REQUIRE(watSatColumn[2] == 0.173);
	REQUIRE(watSatColumn[3] == 0.174325);
	REQUIRE(watSatColumn[4] == 0.19);
	REQUIRE(watSatColumn[5] == 0.19165);
	REQUIRE(watSatColumn[6] == 0.207);

	// XML Double column
	REQUIRE(cbt->getDatatype(2) == COMMON_NS::AbstractObject::numericalDatatypeEnum::DOUBLE);
	auto watRelPermColumn = cbt->getDoubleValues(2);
	REQUIRE(watRelPermColumn[0] == 0);
	REQUIRE(watRelPermColumn[1] == 0);
	REQUIRE(watRelPermColumn[2] == 0.000356);
	REQUIRE(watRelPermColumn[3] == 0.0004392);
	REQUIRE(watRelPermColumn[4] == 0.0014241);
	REQUIRE(watRelPermColumn[5] == 0.0015969);
	REQUIRE(watRelPermColumn[6] == 0.0032041);

	// XML Strign column
	REQUIRE(cbt->getDatatype(3) == COMMON_NS::AbstractObject::numericalDatatypeEnum::UNKNOWN);
	auto rowIndexStrColumn = cbt->getStringValues(3);
	REQUIRE(rowIndexStrColumn[0] == "ZERO");
	REQUIRE(rowIndexStrColumn[1] == "ONE");
	REQUIRE(rowIndexStrColumn[2] == "TWO");
	REQUIRE(rowIndexStrColumn[3] == "THREE");
	REQUIRE(rowIndexStrColumn[4] == "FOUR");
	REQUIRE(rowIndexStrColumn[5] == "FIVE");
	REQUIRE(rowIndexStrColumn[6] == "SIX");
}
