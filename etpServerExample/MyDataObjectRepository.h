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
#pragma once

#include "common/DataObjectRepository.h"

#include <boost/filesystem.hpp>

#include "etp/AbstractSession.h"

class MyDataObjectRepository : public COMMON_NS::DataObjectRepository
{
public:
	std::vector<ETP_NS::AbstractSession*> sessions;
	std::string hdf5Folder = boost::filesystem::temp_directory_path().string();

	~MyDataObjectRepository() = default;

	COMMON_NS::AbstractObject* getObjectFromUri(const std::string & uri) const;

	void on_CreateDataObject(const std::vector<std::pair<std::chrono::time_point<std::chrono::system_clock>, COMMON_NS::AbstractObject*>>& created);
	void on_UpdateDataObject(const std::vector<std::pair<std::chrono::time_point<std::chrono::system_clock>, COMMON_NS::AbstractObject*>>& updated);

private:
	std::vector<COMMON_NS::AbstractObject*> getDataObjects(const Energistics::Etp::v12::Datatypes::Object::SubscriptionInfo& subscriptionInfo) const;
};
