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

#include "../resqml2/IjkGridLatticeRepresentation.h"

namespace RESQML2_2_NS
{
	/** @brief	An ijk grid lattice representation. This class cannot be inherited. */
	class IjkGridLatticeRepresentation final : public RESQML2_NS::IjkGridLatticeRepresentation
	{
	private :
		gsoap_eml2_3::resqml22__Point3dLatticeArray* getArrayLatticeOfPoints3d() const;
	public:

		/**
		 * @brief	Constructor
		 *
		 * @param [in]		repo  	If non-nullptr, the repo.
		 * @param 		  	guid  	Unique identifier.
		 * @param 		  	title 	The title.
		 * @param 		  	iCount	Number of.
		 * @param 		  	jCount	Number of.
		 * @param 		  	kCount	Number of.
		 */
		IjkGridLatticeRepresentation(COMMON_NS::DataObjectRepository * repo,
			const std::string & guid, const std::string & title,
			unsigned int iCount, unsigned int jCount, unsigned int kCount) :
			RESQML2_NS::IjkGridLatticeRepresentation(repo, guid, title, iCount, jCount, kCount) {}

		/**
		 * @brief	Constructor
		 *
		 * @param [in]		interp	If non-nullptr, the interp.
		 * @param 		  	guid  	Unique identifier.
		 * @param 		  	title 	The title.
		 * @param 		  	iCount	Number of.
		 * @param 		  	jCount	Number of.
		 * @param 		  	kCount	Number of.
		 */
		IjkGridLatticeRepresentation(RESQML2_NS::AbstractFeatureInterpretation* interp,
				const std::string & guid, const std::string & title,
				unsigned int iCount, unsigned int jCount, unsigned int kCount) :
			RESQML2_NS::IjkGridLatticeRepresentation(interp, guid, title, iCount, jCount, kCount) {}

		/**
		 * @brief	Creates an instance of this class by wrapping a gsoap instance.
		 *
		 * @param [in]	fromGsoap	If non-nullptr, from gsoap.
		 */
		IjkGridLatticeRepresentation(gsoap_eml2_3::_resqml22__IjkGridRepresentation* fromGsoap): RESQML2_NS::IjkGridLatticeRepresentation(fromGsoap) {}

		/**
		 * @brief	Constructor
		 *
		 * @param [in]	fromGsoap	If non-nullptr, from gsoap.
		 */
		IjkGridLatticeRepresentation(gsoap_eml2_3::_resqml22__TruncatedIjkGridRepresentation* fromGsoap) : RESQML2_NS::IjkGridLatticeRepresentation(fromGsoap) {}

		/**
		* Destructor does nothing since the memory is managed by the gsoap context.
		*/
		~IjkGridLatticeRepresentation() {}

		DLL_IMPORT_OR_EXPORT double getXOrigin() const final;

		DLL_IMPORT_OR_EXPORT double getYOrigin() const final;

		DLL_IMPORT_OR_EXPORT double getZOrigin() const final;

		/*****************************************************
		* Notice that, in seismic context, I is the slowest axis, J is the intermediate axis and K is the fastest axis.
		* In reservoir grid, I is the fastest axis, J is the intermediate axis and K is slowest axis.
		* It should be improved in future Resqml versions.
		*****************************************************/

		DLL_IMPORT_OR_EXPORT double getXIOffset() const final;

		DLL_IMPORT_OR_EXPORT double getYIOffset() const final;

		DLL_IMPORT_OR_EXPORT double getZIOffset() const final;

		DLL_IMPORT_OR_EXPORT double getXJOffset() const final;

        DLL_IMPORT_OR_EXPORT double getYJOffset() const final;

		DLL_IMPORT_OR_EXPORT double getZJOffset() const final;

		DLL_IMPORT_OR_EXPORT double getXKOffset() const final;

        DLL_IMPORT_OR_EXPORT double getYKOffset() const final;

		DLL_IMPORT_OR_EXPORT double getZKOffset() const final;

		DLL_IMPORT_OR_EXPORT double getISpacing() const final;

		DLL_IMPORT_OR_EXPORT double getJSpacing() const final;

		DLL_IMPORT_OR_EXPORT double getKSpacing() const final;

		DLL_IMPORT_OR_EXPORT int getOriginInline() const final;

		DLL_IMPORT_OR_EXPORT int getOriginCrossline() const final;

		DLL_IMPORT_OR_EXPORT int getInlineIOffset() const final;

		DLL_IMPORT_OR_EXPORT int getInlineJOffset() const final;

		DLL_IMPORT_OR_EXPORT int getInlineKOffset() const final;

		DLL_IMPORT_OR_EXPORT int getCrosslineIOffset() const final;

		DLL_IMPORT_OR_EXPORT int getCrosslineJOffset() const final;

		DLL_IMPORT_OR_EXPORT int getCrosslineKOffset() const final;

		DLL_IMPORT_OR_EXPORT void setGeometryAsCoordinateLineNodes(gsoap_resqml2_0_1::resqml20__PillarShape mostComplexPillarGeometry,
			gsoap_resqml2_0_1::resqml20__KDirection kDirectionKind,
			bool isRightHanded,
			double originX, double originY, double originZ,
			double directionIX, double directionIY, double directionIZ, double spacingI,
			double directionJX, double directionJY, double directionJZ, double spacingJ,
			double directionKX, double directionKY, double directionKZ, double spacingK, RESQML2_NS::AbstractLocal3dCrs * localCrs = nullptr) final;

		DLL_IMPORT_OR_EXPORT void addSeismic3dCoordinatesToPatch(
			unsigned int patchIndex,
			double startInline, double incrInline, unsigned int countInline,
			double startCrossline, double incrCrossline, unsigned int countCrossline,
			unsigned int countSample, RESQML2_NS::AbstractRepresentation * seismicSupport) final;

		COMMON_NS::DataObjectReference getHdfProxyDor() const final;

		/**
		* The standard XML namespace for serializing this data object.
		*/
		DLL_IMPORT_OR_EXPORT static const char* XML_NS;

		/**
		* Get the standard XML namespace for serializing this data object.
		*/
		DLL_IMPORT_OR_EXPORT std::string getXmlNamespace() const final { return XML_NS; }
	};
}
