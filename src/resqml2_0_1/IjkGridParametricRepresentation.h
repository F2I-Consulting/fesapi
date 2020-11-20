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

#include "../resqml2/IjkGridParametricRepresentation.h"

namespace RESQML2_0_1_NS
{
	/**
	* An IJK Grid parametric representation define the cell corner positions by means of parameters along the pillars of the grid.
	* Adjacent cell corner are supposed to be located the same so they are not repeated unless you define split lines or split nodes.
	*/
	class IjkGridParametricRepresentation final : public RESQML2_NS::IjkGridParametricRepresentation
	{
	public:

		/**
		 * Constructor
		 *
		 * @param [in,out]	repo					If non-null, the repo.
		 * @param 		  	guid					Unique identifier.
		 * @param 		  	title					The title.
		 * @param 		  	iCount					Number of.
		 * @param 		  	jCount					Number of.
		 * @param 		  	kCount					Number of.
		 * @param 		  	withTruncatedPillars	(Optional) True to with truncated pillars.
		 */
		IjkGridParametricRepresentation(COMMON_NS::DataObjectRepository * repo,
			const std::string & guid, const std::string & title,
			unsigned int iCount, unsigned int jCount, unsigned int kCount,
			bool withTruncatedPillars = false) :
			RESQML2_NS::IjkGridParametricRepresentation(repo, guid, title, iCount, jCount, kCount, withTruncatedPillars) {}

		/**
		 * Constructor
		 *
		 * @param [in,out]	interp					If non-null, the interp.
		 * @param 		  	guid					Unique identifier.
		 * @param 		  	title					The title.
		 * @param 		  	iCount					Number of.
		 * @param 		  	jCount					Number of.
		 * @param 		  	kCount					Number of.
		 * @param 		  	withTruncatedPillars	(Optional) True to with truncated pillars.
		 */
		IjkGridParametricRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp,
			const std::string & guid, const std::string & title,
			unsigned int iCount, unsigned int jCount, unsigned int kCount,
			bool withTruncatedPillars = false) :
			RESQML2_NS::IjkGridParametricRepresentation(interp, guid, title, iCount, jCount, kCount, withTruncatedPillars) {}

		/**
		 * @brief	Creates an instance of this class by wrapping a gSOAP instance.
		 *
		 * @param [in]	fromGsoap	If non-null, the gSOAP instance.
		 */
		IjkGridParametricRepresentation(gsoap_resqml2_0_1::_resqml20__IjkGridRepresentation* fromGsoap) : RESQML2_NS::IjkGridParametricRepresentation(fromGsoap) {}

		/**
		 * @brief	Creates an instance of this class by wrapping a gSOAP instance.
		 *
		 * @param [in]	fromGsoap	If non-null, the gSOAP instance.
		 */
		IjkGridParametricRepresentation(gsoap_resqml2_0_1::_resqml20__TruncatedIjkGridRepresentation* fromGsoap) : RESQML2_NS::IjkGridParametricRepresentation(fromGsoap) {}

		/**
		* Destructor clean pillarInformation memory when allocated
		*/
		~IjkGridParametricRepresentation() = default;

		COMMON_NS::DataObjectReference getHdfProxyDor() const final;

		DLL_IMPORT_OR_EXPORT ULONG64 getXyzPointCountOfPatch(unsigned int patchIndex) const final;

		/**
		* @copybrief resqml2::AbstractRepresentation::getXyzPointsOfPatch
		*
		* @exception std::logic_error	If the geometry of the grid either does not exist or if it is not handled yet by fesapi.
		* @exception std::logic_error	If this grid is truncated and the additional grid points cannot be read.
		*
		* @copydetails resqml2::AbstractIjkGridRepresentation::getXyzPointsOfPatch
		*/
		DLL_IMPORT_OR_EXPORT void getXyzPointsOfPatch(unsigned int patchIndex, double * xyzPoints) const final;

		DLL_IMPORT_OR_EXPORT unsigned int getControlPointMaxCountPerPillar() const final;

		DLL_IMPORT_OR_EXPORT bool hasControlPointParameters() const final;

		DLL_IMPORT_OR_EXPORT bool isParametricLineKindConstant() const final;

		DLL_IMPORT_OR_EXPORT short getConstantParametricLineKind() const final;

		using RESQML2_NS::IjkGridParametricRepresentation::setGeometryAsParametricSplittedPillarNodes;

		DLL_IMPORT_OR_EXPORT void setGeometryAsParametricSplittedPillarNodes(
			gsoap_resqml2_0_1::resqml20__PillarShape mostComplexPillarGeometry, bool isRightHanded,
			double const * parameters, double const * controlPoints, double const * controlPointParameters, unsigned int controlPointMaxCountPerPillar, short const * pillarKind, EML2_NS::AbstractHdfProxy* proxy,
			unsigned long splitCoordinateLineCount, unsigned int const * pillarOfCoordinateLine,
			unsigned int const * splitCoordinateLineColumnCumulativeCount, unsigned int const * splitCoordinateLineColumns, RESQML2_NS::AbstractLocal3dCrs * localCrs = nullptr) final;

		DLL_IMPORT_OR_EXPORT void setGeometryAsParametricSplittedPillarNodesUsingExistingDatasets(
			gsoap_resqml2_0_1::resqml20__PillarShape mostComplexPillarGeometry, gsoap_resqml2_0_1::resqml20__KDirection kDirectionKind, bool isRightHanded,
			const std::string & parameters, const std::string & controlPoints, const std::string & controlPointParameters, unsigned int controlPointMaxCountPerPillar, const std::string & pillarKind, const std::string & definedPillars, EML2_NS::AbstractHdfProxy* proxy,
			unsigned long splitCoordinateLineCount, const std::string & pillarOfCoordinateLine,
			const std::string & splitCoordinateLineColumnCumulativeCount, const std::string & splitCoordinateLineColumns, RESQML2_NS::AbstractLocal3dCrs * localCrs = nullptr) final;

		DLL_IMPORT_OR_EXPORT void setGeometryAsParametricSplittedPillarNodesUsingExistingDatasets(
			gsoap_resqml2_0_1::resqml20__KDirection kDirectionKind, bool isRightHanded,
			const std::string & parameters, const std::string & controlPoints, const std::string & controlPointParameters, unsigned int controlPointCountPerPillar, short pillarKind, EML2_NS::AbstractHdfProxy* proxy,
			unsigned long splitCoordinateLineCount, const std::string & pillarOfCoordinateLine,
			const std::string & splitCoordinateLineColumnCumulativeCount, const std::string & splitCoordinateLineColumns, RESQML2_NS::AbstractLocal3dCrs * localCrs = nullptr) final;

		/**
		* The standard XML namespace for serializing this data object.
		*/
		DLL_IMPORT_OR_EXPORT static const char* XML_NS;

		/**
		* Get the standard XML namespace for serializing this data object.
		*/
		DLL_IMPORT_OR_EXPORT std::string getXmlNamespace() const final { return XML_NS; }

	private:
		EML2_NS::AbstractHdfProxy* getParameterDatasetPath(std::string & datasetPathInExternalFile) const final;
		EML2_NS::AbstractHdfProxy* getControlPointDatasetPath(std::string & datasetPathInExternalFile) const final;
		EML2_NS::AbstractHdfProxy* getControlPointParametersDatasetPath(std::string & datasetPathInExternalFile) const final;
		EML2_NS::AbstractHdfProxy* getParametersOfNodesDatasetPath(std::string & datasetPathInExternalFile) const final;

		void getRawParametricLineKind(short * pillarKind) const final;

		void setGeometryAsParametricSplittedPillarNodesWithoutPillarKindUsingExistingDatasets(
			gsoap_resqml2_0_1::resqml20__KDirection kDirectionKind, bool isRightHanded,
			const std::string & parameters, const std::string & controlPoints, const std::string & controlPointParameters, unsigned int controlPointCountPerPillar, EML2_NS::AbstractHdfProxy* proxy,
			unsigned long splitCoordinateLineCount, const std::string & pillarOfCoordinateLine,
			const std::string & splitCoordinateLineColumnCumulativeCount, const std::string & splitCoordinateLineColumns, RESQML2_NS::AbstractLocal3dCrs * localCrs);
	};
}
