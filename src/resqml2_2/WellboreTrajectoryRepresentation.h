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

#include "../resqml2/WellboreTrajectoryRepresentation.h"

namespace RESQML2_2_NS
{
	/** A wellbore trajectory representation. */
	class WellboreTrajectoryRepresentation final : public RESQML2_NS::WellboreTrajectoryRepresentation
	{
	public:

		/**
		 * Only to be used in partial transfer context.
		 *
		 * @param [in]	partialObject	If non-nullptr, the partial object.
		 */
		DLL_IMPORT_OR_EXPORT WellboreTrajectoryRepresentation(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : RESQML2_NS::WellboreTrajectoryRepresentation(partialObject) {}

		/**
		 * Creates a wellbore trajectory representation.
		 *
		 * @exception	std::invalid_argument	If @p interp or @p mdInfo is @c nullptr.
		 *
		 * @param [in]	interp	The represented wellbore interpretation. It cannot be null.
		 * @param 	  	guid  	The guid to set to the wellbore trajectory representation. If empty then
		 * 						a new guid will be generated.
		 * @param 	  	title 	The title to set to the wellbore trajectory representation. If empty then
		 * 						\"unknown\" title will be set.
		 * @param [in]	mdInfo	The MD information of the trajectory, mainly the well reference point.
		 * 						The unit of measure used for the mdInfo coordinates must also be used for
		 * 						the start and end MD of the trajectory. It cannot be null.
		 */
		WellboreTrajectoryRepresentation(RESQML2_NS::WellboreInterpretation* interp, const std::string& guid, const std::string& title, EML2_NS::ReferencePointInALocalEngineeringCompoundCrs* mdInfo);

		/**
		 * Creates an instance of this class by wrapping a gSOAP instance.
		 *
		 * @param [in]	fromGsoap	If non-null, the gSOAP instance.
		 */
		WellboreTrajectoryRepresentation(gsoap_eml2_3::_resqml22__WellboreTrajectoryRepresentation* fromGsoap) : RESQML2_NS::WellboreTrajectoryRepresentation(fromGsoap) {}

		/** Destructor does nothing since the memory is managed by the gSOAP context. */
		~WellboreTrajectoryRepresentation() = default;

		DLL_IMPORT_OR_EXPORT void setMinimalGeometry(double startMd, double endMd) final;

		DLL_IMPORT_OR_EXPORT void setGeometry(double const* controlPoints, double startMd, double endMd, uint64_t controlPointCount,
			int lineKind, EML2_NS::AbstractHdfProxy* proxy = nullptr, EML2_NS::AbstractLocal3dCrs* localCrs = nullptr) final;
		
		DLL_IMPORT_OR_EXPORT void setGeometry(double const* controlPoints, double const* controlPointParameters, uint64_t controlPointCount, int lineKind,
			EML2_NS::AbstractHdfProxy* proxy = nullptr, EML2_NS::AbstractLocal3dCrs* localCrs = nullptr) final;

		DLL_IMPORT_OR_EXPORT void setGeometry(double const* controlPoints,
			double const* tangentVectors, double const* controlPointParameters, uint64_t controlPointCount, int lineKind,
			EML2_NS::AbstractHdfProxy* proxy = nullptr, EML2_NS::AbstractLocal3dCrs* localCrs = nullptr) final;

		DLL_IMPORT_OR_EXPORT int getGeometryKind() const final;

		DLL_IMPORT_OR_EXPORT void setMdDatum(EML2_NS::ReferencePointInALocalEngineeringCompoundCrs * mdDatum) final;

		COMMON_NS::DataObjectReference getMdDatumDor() const final;

		DLL_IMPORT_OR_EXPORT uint64_t getXyzPointCountOfPatch(uint64_t patchIndex) const final;

		/**
		 * @copybrief resqml2::AbstractRepresentation::getXyzPointsOfPatch
		 * 
		 * @exception std::invalid_argument If the HDF proxy is missing.
		 * @exception	std::logic_error 	If this trajectory has no geometry.
		 * 
		 * @copydetails resqml2::AbstractRepresentation::getXyzPointsOfPatch
		 */
		DLL_IMPORT_OR_EXPORT void getXyzPointsOfPatch(uint64_t patchIndex, double * xyzPoints) const final;

		DLL_IMPORT_OR_EXPORT bool hasMdValues() const final;

		DLL_IMPORT_OR_EXPORT gsoap_resqml2_0_1::eml20__LengthUom getMdUom() const final;

		DLL_IMPORT_OR_EXPORT void getMdValues(double* values) const final;

		DLL_IMPORT_OR_EXPORT double getStartMd() const final;

		DLL_IMPORT_OR_EXPORT double getFinishMd() const final;

		DLL_IMPORT_OR_EXPORT bool hasTangentVectors() const final;

		DLL_IMPORT_OR_EXPORT void getTangentVectors(double* tangentVectors) final;

		DLL_IMPORT_OR_EXPORT void addParentTrajectory(double kickoffMd, double parentMd, RESQML2_NS::WellboreTrajectoryRepresentation* parentTrajRep) final;

		COMMON_NS::DataObjectReference getParentTrajectoryDor() const final;

		DLL_IMPORT_OR_EXPORT double getParentTrajectoryMd() const final;

		COMMON_NS::DataObjectReference getLocalCrsDor(uint64_t patchIndex) const final;

		COMMON_NS::DataObjectReference getHdfProxyDor() const final;

		DLL_IMPORT_OR_EXPORT bool hasGeometry() const final;

		/**
		* The standard XML namespace for serializing this data object.
		*/
		DLL_IMPORT_OR_EXPORT static const char* XML_NS;

		/**
		* Get the standard XML namespace for serializing this data object.
		*/
		DLL_IMPORT_OR_EXPORT std::string getXmlNamespace() const final { return XML_NS; }

	private:

		/**
		 * Gets specialized gsoap proxy
		 *
		 * @returns	Null if it fails, else the specialized gsoap proxy.
		 */
		gsoap_eml2_3::_resqml22__WellboreTrajectoryRepresentation* getSpecializedGsoapProxy() const;
	};
}
