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

#include <set>

#include "resqml2/AbstractProperty.h"

namespace RESQML2_NS
{
	class AbstractRepresentation : public COMMON_NS::AbstractObject
	{
	protected:

		/**
		* Only to be used in partial transfer context
		*/
		AbstractRepresentation(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : COMMON_NS::AbstractObject(partialObject) {}

		/** 
		* Set the domain of the interpretation according to the local CRS
		* Does not set relationship with interp and crs because the gsoap proxy is not allocated yet. This must be done at concrete class level.
		*/
		AbstractRepresentation(class AbstractFeatureInterpretation*	interp) {}

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		AbstractRepresentation(gsoap_resqml2_0_1::resqml2__AbstractRepresentation* fromGsoap) : COMMON_NS::AbstractObject(fromGsoap) {}

		/**
		* Get the point geometry of a specific patch of the representation.
		* @return	nullptr if there is no point geometry for this particular patch otherwise the found point geometry.
		*/
		virtual gsoap_resqml2_0_1::resqml2__PointGeometry* getPointGeometry2_0_1(unsigned int patchIndex) const;

		/**
		* Creates a point geometry patch.
		* @param patchIndex				The index of the patch which will contain this geometry.
		* @param points					All the points to set ordered according the topology of the representation it is based on. It should be 3 * numPoints sized.
		* @param localCrs				The local CRS where the points lie on.
		* @param numPoints				The number of points for each dimension of the array to write.
		* @param numDimensionsInArray	The number of dimensions in the array to write.
		* @param proxy					The HDF proxy where to write the points. It must be already opened for writing and won't be closed in this method.
		*/
		gsoap_resqml2_0_1::resqml2__PointGeometry* createPointGeometryPatch2_0_1(unsigned int patchIndex, double * points, class AbstractLocal3dCrs* localCrs, unsigned long long * numPoints, unsigned int numDimensionsInArray, COMMON_NS::AbstractHdfProxy * proxy);

		gsoap_resqml2_0_1::eml20__DataObjectReference* getHdfProxyDorFromPointGeometryPatch(gsoap_resqml2_0_1::resqml2__PointGeometry* patch) const;

		gsoap_resqml2_0_1::resqml2__Seismic2dCoordinates* getSeismic2dCoordinates(const unsigned int & patchIndex) const;

		gsoap_resqml2_0_1::resqml2__Seismic3dCoordinates* getSeismic3dCoordinates(const unsigned int & patchIndex) const;

	public:

		enum indexableElement { NODE = 0, EDGE = 1, FACE = 2, VOLUME = 3, PILLAR = 4 };

		/**
		* Destructor does nothing since the memory is managed by the gsoap context.
		*/
		virtual ~AbstractRepresentation() {}

		/**
		* Getter (read/write access) for the localCrs
		*/
		DLL_IMPORT_OR_EXPORT class AbstractLocal3dCrs* getLocalCrs() const;

		/**
		* Get the Local 3d CRS dor where the reference point ordinals are given
		*/
		virtual gsoap_resqml2_0_1::eml20__DataObjectReference* getLocalCrsDor() const;
		
		/**
		* Get the Local 3d CRS uuid where the reference point ordinals are given
		*/
		DLL_IMPORT_OR_EXPORT std::string getLocalCrsUuid() const;

		/*
		* Getter for the uuid of the hdf proxy which is used for storing the numerical values of this representation i.e. geometry.
		* An empty string is returned if no hdf proxy is used for storing the representation/geometry.
		*/
		DLL_IMPORT_OR_EXPORT std::string getHdfProxyUuid() const {
			gsoap_resqml2_0_1::eml20__DataObjectReference* dor = getHdfProxyDor();
			return dor == nullptr ? "" : dor->UUID;
		}

		DLL_IMPORT_OR_EXPORT virtual gsoap_resqml2_0_1::eml20__DataObjectReference* getHdfProxyDor() const = 0;

		/**
		* Getter (read only) of all the properties which use this representation as support.
		*/
		DLL_IMPORT_OR_EXPORT std::vector<class AbstractProperty  const *> getPropertySet() const;

		/**
		* Getter of all the properties values which use this representation as support.
		*/
		DLL_IMPORT_OR_EXPORT std::vector<class AbstractValuesProperty const *> getValuesPropertySet() const;

		/**
		* Getter of the count of values properties which use this representation as support.
		* Necessary for now in SWIG context because I ma not sure if I can always wrap a vector of polymorphic class yet.
		*/
		DLL_IMPORT_OR_EXPORT unsigned int getValuesPropertyCount() const;

		/**
		* Getter of a particular values property which use this representation as support. It is identified by its index.
		* Necessary for now in SWIG context because I ma not sure if I can always wrap a vector of polymorphic class yet.
		* Throw an out of bound exception if the index is superior or equal to the count of values property.
		*/
		DLL_IMPORT_OR_EXPORT class AbstractValuesProperty const * getValuesProperty(unsigned int index) const;

		/**
		 * Set the interpretation which is associated to this representation.
		 * And push back this representation as a representation of the interpreation as well.
		 */
		DLL_IMPORT_OR_EXPORT void setInterpretation(class AbstractFeatureInterpretation * interp);

		/**
		* Get the interpretation of this representation
		*/
		DLL_IMPORT_OR_EXPORT class AbstractFeatureInterpretation* getInterpretation() const;

		/**
		* @return	null pointer if no interpretation is associated to this representation. Otherwise return the data object reference of the associated interpretation.
		*/
		gsoap_resqml2_0_1::eml20__DataObjectReference* getInterpretationDor() const;

		/**
		* Get the interpretation uuid of this representation
		*/
		DLL_IMPORT_OR_EXPORT std::string getInterpretationUuid() const;

		/**
		* Get the interpretation content type of this representation
		*/
		DLL_IMPORT_OR_EXPORT std::string getInterpretationContentType() const;

		/**
		* Get all the subrepresentations of this instance.
		*/
		DLL_IMPORT_OR_EXPORT std::vector<SubRepresentation const *> getSubRepresentationSet() const;

		/**
		 * Get the subrepresentation count into this EPC document.
		 * It is mainly used in SWIG context for parsing the vector from a non C++ language.
		 */
		DLL_IMPORT_OR_EXPORT unsigned int getSubRepresentationCount() const;

		/**
		 * Get a particular subrepresentation according to its position in the EPC document.
		 * It is mainly used in SWIG context for parsing the vector from a non C++ language.
		 */
		DLL_IMPORT_OR_EXPORT SubRepresentation const * getSubRepresentation(unsigned int index) const;

		/**
		* Get all the subrepresentations of this instance which represent a fault.
		*/
		DLL_IMPORT_OR_EXPORT std::vector<SubRepresentation const *> getFaultSubRepresentationSet() const;

		/**
		 * Get the subrepresentation count into this EPC document which are representations of a fault.
		 * It is mainly used in SWIG context for parsing the vector from a non C++ language.
		 */
		DLL_IMPORT_OR_EXPORT unsigned int getFaultSubRepresentationCount() const;

		/**
		 * Get a particular fault subrepresentation according to its position in the EPC document.
		 * It is mainly used in SWIG context for parsing the vector from a non C++ language.
		 */
		DLL_IMPORT_OR_EXPORT SubRepresentation const * getFaultSubRepresentation(unsigned int index) const;
        
		/**
		* Get the xyz point count in a given patch.
		*/
		DLL_IMPORT_OR_EXPORT virtual ULONG64 getXyzPointCountOfPatch(const unsigned int & patchIndex) const = 0;

        /**
		* Get the xyz point count of all patches of this representation.
		*/
		DLL_IMPORT_OR_EXPORT ULONG64 getXyzPointCountOfAllPatches() const;

		/**
		* Get all the XYZ points of a particular patch of this representation.
		* XYZ points are given in the local CRS.
		* @param xyzPoints A linearized 2d array where the first (quickest) dimension is coordinate dimension (XYZ) and second dimension is vertex dimension. It must be pre allocated.
		*/
		DLL_IMPORT_OR_EXPORT virtual void getXyzPointsOfPatch(const unsigned int & patchIndex, double * xyzPoints) const = 0;

		/**
		* Get all the XYZ points of a particular patch of this representation.
		* XYZ points are given in the global CRS.
		* @param xyzPoints A linearized 2d array where the first (quickest) dimension is coordinate dimension (XYZ) and second dimension is vertex dimension.  It must be pre allocated.
		*/
		DLL_IMPORT_OR_EXPORT void getXyzPointsOfPatchInGlobalCrs(const unsigned int & patchIndex, double * xyzPoints) const;

		/**
		* Get all the XYZ points of all patches of this individual representation
		* XYZ points are given in the local CRS.
		* @param xyzPoints A linearized 2d array where the first (quickest) dimension is coordinate dimension (XYZ) and second dimension is vertex dimension. It must be pre allocated.
		*/
		DLL_IMPORT_OR_EXPORT void getXyzPointsOfAllPatches(double * xyzPoints) const;

		/**
		* Get all the XYZ points of all patches of this individual representation
		* XYZ points are given in the global CRS.
		* @param xyzPoints A linearized 2d array where the first (quickest) dimension is coordinate dimension (XYZ) and second dimension is vertex dimension.  It must be pre allocated.
		*/
		DLL_IMPORT_OR_EXPORT void getXyzPointsOfAllPatchesInGlobalCrs(double * xyzPoints) const;

		/**
		* Get the seismic support of a specific patch.
		* @return nullptr if seismic info have not been provided.
		*/
		DLL_IMPORT_OR_EXPORT AbstractRepresentation* getSeismicSupportOfPatch(const unsigned int & patchIndex) const;

		/**
		* Get all seismic support of the current geoemtry of this representation.
		* This method does not return the seismic lattice representations which are support of 2D grid representation.
		*/
		DLL_IMPORT_OR_EXPORT std::set<AbstractRepresentation*> getAllSeismicSupport() const;

		DLL_IMPORT_OR_EXPORT virtual unsigned int getPatchCount() const = 0;

		/**
		* Pushes back this representaiton into a representation set
		* @param repSet	The representation set representation which will contain this representation.
		*/
		DLL_IMPORT_OR_EXPORT void pushBackIntoRepresentationSet(class RepresentationSetRepresentation * repSet);

		/**
		* Get all the subrepresentations of this instance which represent a fault.
		*/
		DLL_IMPORT_OR_EXPORT std::vector<RepresentationSetRepresentation const *> getRepresentationSetRespresentationSet() const;

		/**
		 * Get the count of representation set representations which contain this representation
		 */
		DLL_IMPORT_OR_EXPORT ULONG64 getRepresentationSetRepresentationCount() const;

		/**
		 * Get the parent representation set representations at the specified index of the representation set representation list.
		 */
		DLL_IMPORT_OR_EXPORT RepresentationSetRepresentation const * getRepresentationSetRepresentation(const ULONG64  & index) const;

		/**
		* Push back a patch of seismic 3D coordinates info.
		* The index this patch will be located must be consistent with the index of the geometry patch it is related to.
		*/
		DLL_IMPORT_OR_EXPORT void addSeismic3dCoordinatesToPatch(const unsigned int patchIndex, double * inlines, double * crosslines, const unsigned int & pointCount,
			RESQML2_NS::AbstractRepresentation * seismicSupport, COMMON_NS::AbstractHdfProxy * proxy);

		DLL_IMPORT_OR_EXPORT void addSeismic3dCoordinatesToPatch(const unsigned int patchIndex, const double & startInline, const double & incrInline, const unsigned int & countInline,
			const double & startCrossline, const double & incrCrossline, const unsigned int & countCrossline,
			RESQML2_NS::AbstractRepresentation * seismicSupport);

		/**
		* Add seismic coordinates to an existing point geometry patch.
		* @param patchIndex		The index of the geometry patch which receives the seismic coordinates
		* @param lineAbscissa	The abscissa of each points of the patch on the seismic line. The count of this array must be equal to getXyzPointCountOfPatch(patchIndex).
		* @param seismicSupport	The representation of the seismic line.
		* @param proxy			The hdf proxy where the lineAbscissa are stored.
		*/
		DLL_IMPORT_OR_EXPORT void addSeismic2dCoordinatesToPatch(const unsigned int patchIndex, double * lineAbscissa,
			RESQML2_NS::AbstractRepresentation * seismicSupport, COMMON_NS::AbstractHdfProxy * proxy);

		/**
		* Get all the abscissa of the points of a specific patch related to seismic line 2d.
		* @param patchIndex		The index of the geometry patch which stores the seismic coordinates
		* @param values			The array where the abscissa are going to be stored. The count of this array must be equal to getXyzPointCountOfPatch(patchIndex).
		*/
		DLL_IMPORT_OR_EXPORT void getSeismicLineAbscissaOfPointsOfPatch(unsigned int patchIndex, double* values) const;

		/**
		* Get all the inline coordinates of the points of a specific patch related to seismic lattice.
		* @param patchIndex		The index of the geometry patch which stores the seismic coordinates
		* @param values			The array where the inlines coordinates are going to be stored. The count of this array must be equal to getXyzPointCountOfPatch(patchIndex).
		*/
		DLL_IMPORT_OR_EXPORT void getInlinesOfPointsOfPatch(unsigned int patchIndex, double * values) const;

		/**
		* Get all the crossline coordinates of the points of a specific patch related to seismic lattice.
		* @param patchIndex		The index of the geometry patch which stores the seismic coordinates
		* @param values			The array where the crossline coordinates are going to be stored. The count of this array must be equal to getXyzPointCountOfPatch(patchIndex).
		*/
		DLL_IMPORT_OR_EXPORT void getCrosslinesOfPointsOfPatch(unsigned int patchIndex, double * values) const;

		static const char* XML_TAG;

	protected:

		virtual void loadTargetRelationships() const;
	};
}
