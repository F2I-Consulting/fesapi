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

	if (uri[6] != '/') {
		throw ETP_NS::EtpException(2, "The URI " + uri + " uses some dataspaces or witsml or prodml. This agent does not support dataspace.");
	}

	const size_t openingParenthesisPos = uri.find('(');
	const std::string uuid = uri.substr(openingParenthesisPos + 1, 36);
	COMMON_NS::AbstractObject* result = repo->getDataObjectByUuid(uuid);
	if (result == nullptr) {
		throw ETP_NS::EtpException(11, uuid + " cannot be resolved as a data object in this store");
	}

	return result;
}
