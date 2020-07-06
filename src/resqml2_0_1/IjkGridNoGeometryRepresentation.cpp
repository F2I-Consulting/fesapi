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

#include "../resqml2/AbstractFeatureInterpretation.h"

using namespace std;
using namespace gsoap_resqml2_0_1;
using namespace RESQML2_0_1_NS;

COMMON_NS::DataObjectReference IjkGridNoGeometryRepresentation::getHdfProxyDor() const
{
	gsoap_resqml2_0_1::resqml20__AbstractParentWindow* parentWindow = static_cast<gsoap_resqml2_0_1::resqml20__AbstractGridRepresentation*>(gsoapProxy2_0_1)->ParentWindow;

	if (parentWindow != nullptr) {
		if (parentWindow->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__IjkParentWindow) {
			gsoap_resqml2_0_1::resqml20__IjkParentWindow* pw = static_cast<gsoap_resqml2_0_1::resqml20__IjkParentWindow*>(parentWindow);
			if (pw->IRegrid->Intervals->ChildCountPerInterval->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__IntegerHdf5Array) {
				return COMMON_NS::DataObjectReference(static_cast<gsoap_resqml2_0_1::resqml20__IntegerHdf5Array*>(pw->IRegrid->Intervals->ChildCountPerInterval)->Values->HdfProxy);
			}
			else if (pw->IRegrid->Intervals->ParentCountPerInterval->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__IntegerHdf5Array) {
				return COMMON_NS::DataObjectReference(static_cast<gsoap_resqml2_0_1::resqml20__IntegerHdf5Array*>(pw->IRegrid->Intervals->ParentCountPerInterval)->Values->HdfProxy);
			}
			else if (pw->JRegrid->Intervals->ChildCountPerInterval->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__IntegerHdf5Array) {
				return COMMON_NS::DataObjectReference(static_cast<gsoap_resqml2_0_1::resqml20__IntegerHdf5Array*>(pw->JRegrid->Intervals->ChildCountPerInterval)->Values->HdfProxy);
			}
			else if (pw->JRegrid->Intervals->ParentCountPerInterval->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__IntegerHdf5Array) {
				return COMMON_NS::DataObjectReference(static_cast<gsoap_resqml2_0_1::resqml20__IntegerHdf5Array*>(pw->JRegrid->Intervals->ParentCountPerInterval)->Values->HdfProxy);
			}
			else if (pw->KRegrid->Intervals->ChildCountPerInterval->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__IntegerHdf5Array) {
				return COMMON_NS::DataObjectReference(static_cast<gsoap_resqml2_0_1::resqml20__IntegerHdf5Array*>(pw->KRegrid->Intervals->ChildCountPerInterval)->Values->HdfProxy);
			}
			else if (pw->KRegrid->Intervals->ParentCountPerInterval->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__IntegerHdf5Array) {
				return COMMON_NS::DataObjectReference(static_cast<gsoap_resqml2_0_1::resqml20__IntegerHdf5Array*>(pw->KRegrid->Intervals->ParentCountPerInterval)->Values->HdfProxy);
			}
		}
		else if (parentWindow->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__ColumnLayerParentWindow) {
			gsoap_resqml2_0_1::resqml20__ColumnLayerParentWindow* pw = static_cast<gsoap_resqml2_0_1::resqml20__ColumnLayerParentWindow*>(parentWindow);
			return pw->ColumnIndices->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__IntegerHdf5Array
				? COMMON_NS::DataObjectReference(static_cast<gsoap_resqml2_0_1::resqml20__IntegerHdf5Array*>(pw->ColumnIndices)->Values->HdfProxy)
				: COMMON_NS::DataObjectReference();
		}
		else if (parentWindow->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__CellParentWindow) {
			gsoap_resqml2_0_1::resqml20__CellParentWindow* pw = static_cast<gsoap_resqml2_0_1::resqml20__CellParentWindow*>(parentWindow);
			return pw->CellIndices->soap_type() == SOAP_TYPE_gsoap_resqml2_0_1_resqml20__IntegerHdf5Array
				? COMMON_NS::DataObjectReference(static_cast<gsoap_resqml2_0_1::resqml20__IntegerHdf5Array*>(pw->CellIndices)->Values->HdfProxy)
				: COMMON_NS::DataObjectReference();
		}
		else {
			throw logic_error("Unexpected parent window type.");
		}
	}

	return COMMON_NS::DataObjectReference();
}
