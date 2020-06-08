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

#include "etp/EtpMessages.h"

constexpr char applicationName[] = "F2I ETP SERVER";
constexpr char applicationVersion[] = "0.0";
constexpr char contactEmail[] = "name@f2i-consulting.com";
constexpr char contactName[] = "Philippe Verney";
constexpr char contactPhone[] = "Please use Zoom";
constexpr char organizationName[] = "F2I-CONSULTING";

std::vector<std::string> makeSupportedEncodings();
const std::vector<std::string> supportedEncodings = makeSupportedEncodings();

std::map<std::string, Energistics::Etp::v12::Datatypes::DataValue> makeEndpointCapabilities();
const std::map<std::string, Energistics::Etp::v12::Datatypes::DataValue> endpointCapabilities = makeEndpointCapabilities();

std::vector<Energistics::Etp::v12::Datatypes::SupportedDataObject> makeSupportedDataObjects();
const std::vector<Energistics::Etp::v12::Datatypes::SupportedDataObject> supportedDataObjects = makeSupportedDataObjects();

std::vector<Energistics::Etp::v12::Datatypes::SupportedProtocol> makeSupportedProtocols();
const std::vector<Energistics::Etp::v12::Datatypes::SupportedProtocol> supportedProtocols = makeSupportedProtocols();
