/*-----------------------------------------------------------------------
Licensed to the Apache Software Foundation (ASF) under one
or more contributor license agceements.  See the NOTICE file
distributed with this work for additional information
regarding copyright ownership.  The ASF licenses this file
to you under the Apache License, Version 2.0 (the
"License"; you may not use this file except in compliance
with the License.  You may obtain a copy of the License at

  http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agceed to in writing,
software distributed under the License is distributed on an
"AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
KIND, either express or implied.  See the License for the
specific language governing permissions and limitations
under the License.
-----------------------------------------------------------------------*/
#include "MyOwnStoreProtocolHandlers.h"

#include "etp/AbstractSession.h"
#include "etp/EtpHelpers.h"
#include "etp/EtpException.h"

#include "resqml2/AbstractGridRepresentation.h"
#include "resqml2/GridConnectionSetRepresentation.h"

#include "MyDataObjectRepository.h"

MyOwnStoreProtocolHandlers::MyOwnStoreProtocolHandlers(ETP_NS::AbstractSession* mySession, MyDataObjectRepository* repo_) :
	ETP_NS::StoreHandlers(mySession), repo(repo_) {}

void MyOwnStoreProtocolHandlers::on_GetDataObjects(const Energistics::Etp::v12::Protocol::Store::GetDataObjects & msg, int64_t correlationId)
{
	Energistics::Etp::v12::Protocol::Store::GetDataObjectsResponse objResponse;

	Energistics::Etp::v12::Protocol::Core::ProtocolException pe;
	for (const auto & pair : msg.uris) {
		std::cout << "Store received URI : " << pair.second << std::endl;

		try
		{
			COMMON_NS::AbstractObject* obj = repo->getObjectFromUri(pair.second);

			if (obj->isPartial()) {
				obj = repo->resolvePartial(obj);
			}

			Energistics::Etp::v12::Datatypes::Object::DataObject dataObject = ETP_NS::EtpHelpers::buildEtpDataObjectFromEnergisticsObject(obj);
			objResponse.dataObjects[pair.first] = dataObject;
		}
		catch (ETP_NS::EtpException& ex)
		{
			pe.errors[pair.first].message = ex.what();
			pe.errors[pair.first].code = ex.getErrorCode();
		}
	}

	if (!pe.errors.empty()) {
		session->send(objResponse, correlationId);
		session->send(pe, correlationId, 0x02);
	}
	else {
		session->send(objResponse, correlationId, 0x02);
	}
}

void MyOwnStoreProtocolHandlers::on_PutDataObjects(const Energistics::Etp::v12::Protocol::Store::PutDataObjects & msg, int64_t correlationId)
{
	Energistics::Etp::v12::Protocol::Store::PutDataObjectsResponse objResponse;

	Energistics::Etp::v12::Protocol::Core::ProtocolException pe;
	for (const auto & pair : msg.dataObjects) {
		std::cout << "Store received data object : " << pair.second.resource.dataObjectType << " (" << pair.second.resource.uri << ")" << std::endl;

		COMMON_NS::AbstractObject* importedObj = repo->addOrReplaceGsoapProxy(pair.second.data, pair.second.resource.dataObjectType);
		if (importedObj == nullptr) {
			pe.errors[pair.first].message = "Could not put the dataobject with content type " + pair.second.resource.dataObjectType;
			pe.errors[pair.first].code = 4001;
			continue;
		}

		importedObj->loadTargetRelationships();

		objResponse.success[pair.first] = Energistics::Etp::v12::Datatypes::Object::PutResponse();
	}

	if (!pe.errors.empty()) {
		session->send(objResponse, correlationId);
		session->send(pe, correlationId, 0x02);
	}
	else
	{
		session->send(objResponse, correlationId, 0x02);
	}
}

void MyOwnStoreProtocolHandlers::on_DeleteDataObjects(const Energistics::Etp::v12::Protocol::Store::DeleteDataObjects & msg, int64_t correlationId)
{
	Energistics::Etp::v12::Datatypes::ErrorInfo error;
	error.code = 7;
	error.message = "The operation is not supported by the agent.";
	Energistics::Etp::v12::Protocol::Core::ProtocolException pe;
	pe.error.emplace(error);

	session->send(pe, correlationId, 0x02);
}
