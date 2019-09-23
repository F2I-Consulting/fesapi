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

#include "Helpers.h"

#include "etp/AbstractSession.h"
#include "etp/EtpException.h"

COMMON_NS::AbstractObject* Helpers::getObjectFromUri(COMMON_NS::DataObjectRepository const * repo, std::shared_ptr<ETP_NS::AbstractSession> session, const std::string & uri) {
	Energistics::Etp::v12::Datatypes::ErrorInfo error = session->validateDataObjectUri(uri, false);
	if (error.m_code > -1) {
		throw ETP_NS::EtpException(error.m_code, error.m_message);
	}

	std::vector<std::string> tokens = tokenize(uri.substr(6), '/');
	if (tokens[0] != "resqml20" && tokens[0] != "eml20" && tokens[0] != "witsml20") {
		throw ETP_NS::EtpException(2, "The URI " + uri + " uses some dataspaces or witsml or prodml. This agent does not support dataspace.");
	}

	tokens = tokenize(tokens[1], '(');
	tokens[1].pop_back();
	COMMON_NS::AbstractObject* result = repo->getDataObjectByUuid(tokens[1]);
	if (result == nullptr) {
		throw ETP_NS::EtpException(11, tokens[1] + " cannot be resolved as a data object in this store");
	}

	return result;
}
