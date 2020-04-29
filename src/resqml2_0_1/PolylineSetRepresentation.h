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

#include "../resqml2/PolylineSetRepresentation.h"

namespace RESQML2_0_1_NS
{
	/** A polyline set representation. */
	class PolylineSetRepresentation final : public RESQML2_NS::PolylineSetRepresentation
	{
	public:

		/**
		 * Only to be used in partial transfer context
		 *
		 * @param [in,out]	partialObject	If non-null, the partial object.
		 *
		 * @returns	A DLL_IMPORT_OR_EXPORT.
		 */
		DLL_IMPORT_OR_EXPORT PolylineSetRepresentation(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : RESQML2_NS::PolylineSetRepresentation(partialObject) {}

		/**
		 * Creates an instance of this class in a gsoap context.
		 *
		 * @param [in,out]	repo 	If non-null, the repo.
		 * @param 		  	guid 	The guid to set to the new instance. If empty then a new guid will be
		 * 							generated.
		 * @param 		  	title	A title for the instance to create.
		 */
		PolylineSetRepresentation(COMMON_NS::DataObjectRepository * repo, const std::string & guid, const std::string & title);

		/**
		 * @brief	Creates an instance of this class in a gsoap context.
		 *
		 * @exception	std::invalid_argument	If <tt>interp == nullptr</tt>.
		 *
		 * @param [in]	interp	The interpretation this representation represents.
		 * @param 	  	guid  	The guid to set to the new instance. If empty then a new guid will be
		 * 						generated.
		 * @param 	  	title 	A title for the instance to create.
		 */
		PolylineSetRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp,
			const std::string & guid, const std::string & title);

		/**
		 * @brief	Creates an instance of this class in a gsoap context.
		 *
		 * @exception	std::invalid_argument	If <tt>interp == nullptr</tt>.
		 * @exception	std::invalid_argument	If @p roleKind is a break line role.
		 *
		 * @param [in]	interp  	The interpretation this representation represents.
		 * @param 	  	guid		The guid to set to the new instance. If empty then a new guid will be
		 * 							generated.
		 * @param 	  	title   	A title for the instance to create.
		 * @param 	  	roleKind	Indicates the role of this representation.
		 */
		PolylineSetRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp,
			const std::string & guid, const std::string & title, gsoap_eml2_3::resqml22__LineRole roleKind);

		/**
		 * Creates an instance of this class by wrapping a gsoap instance.
		 *
		 * @param [in,out]	fromGsoap	If non-null, from gsoap.
		 */
		PolylineSetRepresentation(gsoap_resqml2_0_1::_resqml20__PolylineSetRepresentation* fromGsoap) : RESQML2_NS::PolylineSetRepresentation(fromGsoap) {}

		/** Destructor does nothing since the memory is managed by the gsoap context. */
		~PolylineSetRepresentation() {}

		COMMON_NS::DataObjectReference getHdfProxyDor() const final;

		DLL_IMPORT_OR_EXPORT unsigned int getPolylineCountOfPatch(unsigned int patchIndex) const final;
		
		DLL_IMPORT_OR_EXPORT unsigned int getPolylineCountOfAllPatches() const final;

		DLL_IMPORT_OR_EXPORT void getNodeCountPerPolylineInPatch(unsigned int patchIndex, unsigned int * nodeCountPerPolyline) const final;

		DLL_IMPORT_OR_EXPORT void getNodeCountPerPolylineOfAllPatches(unsigned int * NodeCountPerPolyline) const final;

		DLL_IMPORT_OR_EXPORT void getXyzPointsOfPatch(unsigned int patchIndex, double * xyzPoints) const final;

		DLL_IMPORT_OR_EXPORT unsigned int getPatchCount() const final;

		DLL_IMPORT_OR_EXPORT void pushBackGeometryPatch(
			unsigned int const * nodeCountPerPolyline, double const * nodes,
			unsigned int polylineCount, bool allPolylinesClosedFlag,
			EML2_NS::AbstractHdfProxy* proxy = nullptr, RESQML2_NS::AbstractLocal3dCrs* localCrs = nullptr) final;

		DLL_IMPORT_OR_EXPORT void pushBackGeometryPatch(
			unsigned int const * nodeCountPerPolyline, double const * nodes,
			unsigned int polylineCount, bool * polylineClosedFlags,
			EML2_NS::AbstractHdfProxy* proxy = nullptr, RESQML2_NS::AbstractLocal3dCrs* localCrs = nullptr) final;

		DLL_IMPORT_OR_EXPORT bool areAllPolylinesClosedOfPatch(unsigned int patchIndex) const final;

		DLL_IMPORT_OR_EXPORT bool areAllPolylinesClosedOfAllPatches() const final;

		DLL_IMPORT_OR_EXPORT bool areAllPolylinesNonClosedOfPatch(unsigned int patchIndex) const final;

		DLL_IMPORT_OR_EXPORT bool areAllPolylinesNonClosedOfAllPatches() const final;

		DLL_IMPORT_OR_EXPORT void getClosedFlagPerPolylineOfPatch(unsigned int patchIndex, bool * closedFlagPerPolyline) const final;

		DLL_IMPORT_OR_EXPORT void getClosedFlagPerPolylineOfAllPatches(bool * closedFlagPerPolyline) const final;

		DLL_IMPORT_OR_EXPORT bool hasALineRole() const final;

		DLL_IMPORT_OR_EXPORT gsoap_eml2_3::resqml22__LineRole getLineRole() const final;

		DLL_IMPORT_OR_EXPORT void setLineRole(gsoap_eml2_3::resqml22__LineRole lineRole) final;

	private:
		gsoap_resqml2_0_1::resqml20__PointGeometry* getPointGeometry2_0_1(unsigned int patchIndex) const final;

		/**
		 * Initializes this object
		 *
		 * @param [in,out]	repo 	If non-null, the repo.
		 * @param 		  	guid 	Unique identifier.
		 * @param 		  	title	The title.
		 */
		void init(COMMON_NS::DataObjectRepository * repo, const std::string & guid, const std::string & title);
	};
}
