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

#include "MyOwnEtpServerSession.h"

#include "common/AbstractObject.h"

namespace {
	Energistics::Etp::v12::Datatypes::Object::Resource buildResourceFromObject(COMMON_NS::AbstractObject * obj) {
		if (obj == nullptr) {
			throw std::invalid_argument("Cannot build resource from a null object.");
		}
		if (obj->isPartial()) {
			throw std::invalid_argument("Cannot build resource from a partial object.");
		}

		Energistics::Etp::v12::Datatypes::Object::Resource result;

		result.m_resourceType = Energistics::Etp::v12::Datatypes::Object::ResourceKind::DataObject;
		result.m_objectNotifiable = false;
		result.m_childCount.set_null();
		result.m_contentType = "application/x-resqml+xml;version=2.0;type=obj_" + obj->getXmlTag();
		// TODO : change the xml namespace to be the same as the etp one
		std::string etpNs =  obj->getXmlNamespace();
		if (etpNs[etpNs.size()-1] != '0') etpNs += '0';
		// END TODO
		result.m_uri = "eml://" + etpNs + "/" + obj->getXmlTag() + "(" + obj->getUuid() + ")";
		result.m_name = obj->getTitle();
		result.m_lastChanged.set_long(obj->getLastUpdate() == -1 ? obj->getCreation() : obj->getLastUpdate());

		return result;
	}
}

MyOwnStoreProtocolHandlers::MyOwnStoreProtocolHandlers(MyOwnEtpServerSession* mySession) : ETP_NS::StoreHandlers(mySession) {}

void MyOwnStoreProtocolHandlers::on_GetObject(const Energistics::Etp::v12::Protocol::Store::GetObject_ & getO, int64_t correlationId)
{
	COMMON_NS::AbstractObject* obj = static_cast<MyOwnEtpServerSession*>(session)->getObjectFromUri(getO.m_uri);
	if (obj == nullptr) {
		return;
	}

	Energistics::Etp::v12::Protocol::Store::Object objResponse;
	objResponse.m_dataObject.m_resource = buildResourceFromObject(obj);
	objResponse.m_dataObject.m_data = obj->serializeIntoString();
	session->send(objResponse, correlationId, 0x01 | 0x02);
}
