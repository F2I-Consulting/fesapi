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

#include "IjkGridNoGeometryRepresentation.h"

#include <stdexcept>

#include "../eml2/AbstractHdfProxy.h"

#include "../resqml2/AbstractFeatureInterpretation.h"

using namespace std;
using namespace gsoap_eml2_3;
using namespace RESQML2_2_NS;

const char* IjkGridNoGeometryRepresentation::XML_NS = "resqml22";

COMMON_NS::DataObjectReference IjkGridNoGeometryRepresentation::getHdfProxyDor() const
{
	resqml22__AbstractParentWindow* parentWindow = static_cast<resqml22__AbstractGridRepresentation*>(gsoapProxy2_3)->ParentWindow;

	if (parentWindow != nullptr) {
		if (parentWindow->soap_type() == SOAP_TYPE_gsoap_eml2_3_resqml22__IjkParentWindow) {
			resqml22__IjkParentWindow* pw = static_cast<resqml22__IjkParentWindow *>(parentWindow);
			if (pw->IRegrid->Intervals->ChildCountPerInterval->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__IntegerExternalArray) {
				return COMMON_NS::DataObjectReference(getOrCreateHdfProxyFromDataArrayPart(static_cast<eml23__IntegerExternalArray*>(pw->IRegrid->Intervals->ChildCountPerInterval)->Values->ExternalDataArrayPart[0]));
			}
			else if (pw->IRegrid->Intervals->ParentCountPerInterval->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__IntegerExternalArray) {
				return COMMON_NS::DataObjectReference(getOrCreateHdfProxyFromDataArrayPart(static_cast<eml23__IntegerExternalArray*>(pw->IRegrid->Intervals->ParentCountPerInterval)->Values->ExternalDataArrayPart[0]));
			}
			else if (pw->JRegrid->Intervals->ChildCountPerInterval->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__IntegerExternalArray) {
				return COMMON_NS::DataObjectReference(getOrCreateHdfProxyFromDataArrayPart(static_cast<eml23__IntegerExternalArray*>(pw->JRegrid->Intervals->ChildCountPerInterval)->Values->ExternalDataArrayPart[0]));
			}
			else if (pw->JRegrid->Intervals->ParentCountPerInterval->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__IntegerExternalArray) {
				return COMMON_NS::DataObjectReference(getOrCreateHdfProxyFromDataArrayPart(static_cast<eml23__IntegerExternalArray*>(pw->JRegrid->Intervals->ParentCountPerInterval)->Values->ExternalDataArrayPart[0]));
			}
			else if (pw->KRegrid->Intervals->ChildCountPerInterval->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__IntegerExternalArray) {
				return COMMON_NS::DataObjectReference(getOrCreateHdfProxyFromDataArrayPart(static_cast<eml23__IntegerExternalArray*>(pw->KRegrid->Intervals->ChildCountPerInterval)->Values->ExternalDataArrayPart[0]));
			}
			else if (pw->KRegrid->Intervals->ParentCountPerInterval->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__IntegerExternalArray) {
				return COMMON_NS::DataObjectReference(getOrCreateHdfProxyFromDataArrayPart(static_cast<eml23__IntegerExternalArray*>(pw->KRegrid->Intervals->ParentCountPerInterval)->Values->ExternalDataArrayPart[0]));
			}
		}
		else if (parentWindow->soap_type() == SOAP_TYPE_gsoap_eml2_3_resqml22__ColumnLayerParentWindow) {
			resqml22__ColumnLayerParentWindow* pw = static_cast<resqml22__ColumnLayerParentWindow*>(parentWindow);
			return pw->ColumnIndices->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__IntegerExternalArray
				? COMMON_NS::DataObjectReference(getOrCreateHdfProxyFromDataArrayPart(static_cast<eml23__IntegerExternalArray*>(pw->ColumnIndices)->Values->ExternalDataArrayPart[0]))
				: COMMON_NS::DataObjectReference();
		}
		else if (parentWindow->soap_type() == SOAP_TYPE_gsoap_eml2_3_resqml22__CellParentWindow) {
			resqml22__CellParentWindow* pw = static_cast<resqml22__CellParentWindow*>(parentWindow);
			return pw->CellIndices->soap_type() == SOAP_TYPE_gsoap_eml2_3_eml23__IntegerExternalArray
				? COMMON_NS::DataObjectReference(getOrCreateHdfProxyFromDataArrayPart(static_cast<eml23__IntegerExternalArray*>(pw->CellIndices)->Values->ExternalDataArrayPart[0]))
				: COMMON_NS::DataObjectReference();
		}
		else {
			throw logic_error("Unexpected parent window type.");
		}
	}

	return COMMON_NS::DataObjectReference();
}
