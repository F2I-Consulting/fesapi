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

#include "Helpers.h"

#include "resqml2/AbstractGridRepresentation.h"
#include "resqml2/GridConnectionSetRepresentation.h"

MyOwnStoreProtocolHandlers::MyOwnStoreProtocolHandlers(std::shared_ptr<ETP_NS::AbstractSession> mySession, COMMON_NS::DataObjectRepository* repo_) :
	ETP_NS::StoreHandlers(mySession), repo(repo_) {}

void MyOwnStoreProtocolHandlers::on_GetDataObjects(const Energistics::Etp::v12::Protocol::Store::GetDataObjects & msg, int64_t correlationId)
{
	Energistics::Etp::v12::Protocol::Store::GetDataObjectsResponse objResponse;

	Energistics::Etp::v12::Protocol::Core::ProtocolException pe;
	for (const auto & pair : msg.m_uris) {
		std::cout << "Store received URI : " << pair.second << std::endl;

		try
		{
			COMMON_NS::AbstractObject* obj = Helpers::getObjectFromUri(repo, session, pair.second);

			if (obj->isPartial()) {
				obj = repo->resolvePartial(obj);
			}

			Energistics::Etp::v12::Datatypes::Object::DataObject dataObject = ETP_NS::EtpHelpers::buildEtpDataObjectFromEnergisticsObject(obj);
			objResponse.m_dataObjects[pair.first] = dataObject;
		}
		catch (ETP_NS::EtpException& ex)
		{
			pe.m_errors[pair.first].m_message = ex.what();
			pe.m_errors[pair.first].m_code = ex.getErrorCode();
		}
	}

	if (!pe.m_errors.empty()) {
		session->send(objResponse, correlationId, 0x01);
		session->send(pe, correlationId, 0x01 | 0x02);
	}
	else {
		session->send(objResponse, correlationId, 0x01 | 0x02);
	}
}

void MyOwnStoreProtocolHandlers::on_PutDataObjects(const Energistics::Etp::v12::Protocol::Store::PutDataObjects & msg, int64_t correlationId)
{
	Energistics::Etp::v12::Protocol::Core::ProtocolException pe;
	for (const auto & pair : msg.m_dataObjects) {
		std::cout << "Store received data object : " << pair.second.m_resource.m_dataObjectType << " (" << pair.second.m_resource.m_uri << ")" << std::endl;

		COMMON_NS::AbstractObject* importedObj = repo->addOrReplaceGsoapProxy(pair.second.m_data, pair.second.m_resource.m_dataObjectType);
		if (importedObj == nullptr) {
			pe.m_errors[pair.first].m_message = "Could not put the dataobject with content type " + pair.second.m_resource.m_dataObjectType;
			pe.m_errors[pair.first].m_code = 4001;
			continue;
		}

		importedObj->loadTargetRelationships();

		if (pair.second.m_resource.m_dataObjectType == "resqml20.obj_IjkGridRepresentation") {
			std::cout << "Create a dummy Grid Connection Set for received IJK Grid Representation." << std::endl;
			RESQML2_NS::GridConnectionSetRepresentation* gcsr = repo->createGridConnectionSetRepresentation(std::string(), "Dummy GCSR");
			ULONG64 cellIndexPair[] = { 0, 1 };
			gcsr->setCellIndexPairs(1, cellIndexPair, (std::numeric_limits<unsigned int>::max)(), repo->getHdfProxy(0));
			gcsr->pushBackSupportingGridRepresentation(static_cast<RESQML2_NS::AbstractGridRepresentation*>(importedObj));
		}
	}

	if (!pe.m_errors.empty()) {
		session->send(pe, correlationId, 0x01 | 0x02);
	}
}

void MyOwnStoreProtocolHandlers::on_DeleteDataObjects(const Energistics::Etp::v12::Protocol::Store::DeleteDataObjects & msg, int64_t correlationId)
{
	Energistics::Etp::v12::Datatypes::ErrorInfo error;
	error.m_code = 7;
	error.m_message = "The operation is not supported by the agent.";
	Energistics::Etp::v12::Protocol::Core::ProtocolException pe;
	pe.m_error.set_ErrorInfo(error);

	session->send(pe, correlationId, 0x01 | 0x02);
}
