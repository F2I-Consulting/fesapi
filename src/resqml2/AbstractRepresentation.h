/*-----------------------------------------------------------------------
Copyright F2I-CONSULTING, (2014-2017)

philippe.verney@f2i-consulting.com

This software is a computer program whose purpose is to access to data formatted using Energistics standards.

This software is governed by the CeCILL-B license under French law and
abiding by the rules of distribution of free software.  You can  use, 
modify and/ or redistribute the software under the terms of the CeCILL-B
license as circulated by CEA, CNRS and INRIA at the following URL
"http://www.cecill.info". 

As a counterpart to the access to the source code and  rights to copy,
modify and redistribute granted by the license, users are provided only
with a limited warranty  and the software's author,  the holder of the
economic rights,  and the successive licensors  have only  limited
liability. 

In this respect, the user's attention is drawn to the risks associated
with loading,  using,  modifying and/or developing or reproducing the
software by the user in light of its specific status of free software,
that may mean  that it is complicated to manipulate,  and  that  also
therefore means  that it is reserved for developers  and  experienced
professionals having in-depth computer knowledge. Users are therefore
encouraged to load and test the software's suitability as regards their
requirements in conditions enabling the security of their systems and/or 
data to be ensured and,  more generally, to use and operate it in the 
same conditions as regards security. 

The fact that you are presently reading this means that you have had
knowledge of the CeCILL-B license and that you accept its terms.
-----------------------------------------------------------------------*/
#pragma once

#include "resqml2/AbstractProperty.h"

namespace common {
	class AbstractHdfProxy;
}

namespace resqml2
{
	class DLL_IMPORT_OR_EXPORT AbstractRepresentation : public common::AbstractObject
	{
	protected:

		/**
		* Only to be used in partial transfer context
		*/
		AbstractRepresentation(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : common::AbstractObject(partialObject), interpretation(nullptr), hdfProxy(nullptr), localCrs(nullptr) {}

		/** 
		* Set the domain of the interpretation according to the local CRS
		* Does not set relationship with interp and crs because the gsoap proxy is not allocated yet. This must be done at concrete class level.
		*/
		AbstractRepresentation(class AbstractFeatureInterpretation*	interp, class AbstractLocal3dCrs * crs);

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		AbstractRepresentation(gsoap_resqml2_0_1::resqml2__AbstractRepresentation* fromGsoap) : common::AbstractObject(fromGsoap), interpretation(nullptr), hdfProxy(nullptr), localCrs(nullptr) {}

		/**
		* Push back the seismic support of this representation and sets the opposite relationship
		* i.e. from the base rep to the child rep.
		* Only updates memory, no XML.
		*/
		void pushBackSeismicSupport(AbstractRepresentation * seismicSupport);

		/**
		* Set the interpretation of the isntance only at the XML level
		*/
		void setXmlInterpretation(class AbstractFeatureInterpretation * interp);

		/**
		* Get the point geometry of a specific patch of the representation.
		* @return	nullptr if there is no point geometry for this particular patch otherwise the found point geometry.
		*/
		virtual gsoap_resqml2_0_1::resqml2__PointGeometry* getPointGeometry2_0_1(const unsigned int & patchIndex) const { return nullptr; }

		/**
		* Creates a point geometry patch.
		* @param patchIndex				The index of the patch which will contain this geometry.
		* @param points					All the points to set ordered according the topology of the representation it is based on. It should be 3 * numPoints sized.
		* @param numPoints				The number of points for each dimension of the array to write.
		* @param numDimensionsInArray	The number of dimensions in the array to write.
		* @param proxy					The HDF proxy where to write the points. It must be already opened for writing and won't be closed in this method.
		*/
		gsoap_resqml2_0_1::resqml2__PointGeometry* createPointGeometryPatch2_0_1(const unsigned int & patchIndex, double * points, unsigned long long * numPoints, const unsigned int & numDimensionsInArray, common::AbstractHdfProxy * proxy);

		std::string getHdfProxyUuidFromPointGeometryPatch(gsoap_resqml2_0_1::resqml2__PointGeometry* patch) const;

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
		class AbstractLocal3dCrs* getLocalCrs() const;

		/**
		* Get the Local 3d CRS dor where the reference point ordinals are given
		*/
		virtual gsoap_resqml2_0_1::eml20__DataObjectReference* getLocalCrsDor() const;
		
		/**
		* Get the Local 3d CRS uuid where the reference point ordinals are given
		*/
		std::string getLocalCrsUuid() const;

		/**
		* Getter (read/write access) for the hdf Proxy
		*/
		common::AbstractHdfProxy* getHdfProxy() const;

		/*
		 * Getter for the uuid of the hdf proxy which is used for storing the numerical values of this representation i.e. geometry.
		 * An empty string is returned if no hdf proxy is used for storing the representation/geometry.
		 */
		virtual std::string getHdfProxyUuid() const = 0;

		/**
		* Getter (read only) of all the properties which use this representation as support.
		*/
		const std::vector<class AbstractProperty*> & getPropertySet() const;

		/**
		* Getter of all the properties values which use this representation as support.
		*/
		std::vector<class AbstractValuesProperty*> getValuesPropertySet() const;

		/**
		* Getter of the count of values properties which use this representation as support.
		* Necessary for now in SWIG context because I ma not sure if I can always wrap a vector of polymorphic class yet.
		*/
		unsigned int getValuesPropertyCount() const;

		/**
		* Getter of a particular values property which use this representation as support. It is identified by its index.
		* Necessary for now in SWIG context because I ma not sure if I can always wrap a vector of polymorphic class yet.
		* Throw an out of bound exception if the index is superior or equal to the count of values property.
		*/
		class AbstractValuesProperty* getValuesProperty(const unsigned int & index) const;

		/**
		 * Set the interpretation which is associated to this representation.
		 * And push back this representation as a representation of the interpreation as well.
		 */
		void setInterpretation(class AbstractFeatureInterpretation * interp);

		/**
		* Get the interpretation of this representation
		*/
		class AbstractFeatureInterpretation* getInterpretation() const;

		/**
		* @return	null pointer if no interpretation is associated to this representation. Otherwise return the data object reference of the associated interpretation.
		*/
		gsoap_resqml2_0_1::eml20__DataObjectReference* getInterpretationDor() const;

		/**
		* Get the interpretation uuid of this representation
		*/
		std::string getInterpretationUuid() const;

		/**
		* Get the interpretation content type of this representation
		*/
		std::string getInterpretationContentType() const;

		/**
		* DONOT USE THIS METHOD EXCEPT IF YOU REALLY KNOW WHAT YOU ARE DOING.
		* Push back a subrepresentation to this representation.
		* Does not add the inverse relationship i.e. from the subrepresentation to this representation.
		*/
		void pushBackSubRepresentation(class SubRepresentation* subRep);

		/**
		* Get all the subrepresentations of this instance.
		*/
		std::vector<SubRepresentation*> getSubRepresentationSet() const;

		/**
		 * Get the subrepresentation count into this EPC document.
		 * It is mainly used in SWIG context for parsing the vector from a non C++ language.
		 */
		unsigned int getSubRepresentationCount() const;

		/**
		 * Get a particular subrepresentation according to its position in the EPC document.
		 * It is mainly used in SWIG context for parsing the vector from a non C++ language.
		 */
		SubRepresentation* getSubRepresentation(const unsigned int & index) const;

		/**
		* Get all the subrepresentations of this instance which represent a fault.
		*/
		std::vector<SubRepresentation*> getFaultSubRepresentationSet() const;

		/**
		 * Get the subrepresentation count into this EPC document which are representations of a fault.
		 * It is mainly used in SWIG context for parsing the vector from a non C++ language.
		 */
		unsigned int getFaultSubRepresentationCount() const;

		/**
		 * Get a particular fault subrepresentation according to its position in the EPC document.
		 * It is mainly used in SWIG context for parsing the vector from a non C++ language.
		 */
		SubRepresentation* getFaultSubRepresentation(const unsigned int & index) const;
        
		/**
		* Get the xyz point count in a given patch.
		*/
		virtual ULONG64 getXyzPointCountOfPatch(const unsigned int & patchIndex) const = 0;

        /**
		* Get the xyz point count of all patches of this representation.
		*/
		ULONG64 getXyzPointCountOfAllPatches() const;

		/**
		* Get all the XYZ points of a particular patch of this representation.
		* XYZ points are given in the local CRS.
		* @param xyzPoints A linearized 2d array where the first (quickest) dimension is coordinate dimension (XYZ) and second dimension is vertex dimension. It must be pre allocated.
		*/
		 virtual void getXyzPointsOfPatch(const unsigned int & patchIndex, double * xyzPoints) const = 0;

		/**
		* Get all the XYZ points of a particular patch of this representation.
		* XYZ points are given in the global CRS.
		* @param xyzPoints A linearized 2d array where the first (quickest) dimension is coordinate dimension (XYZ) and second dimension is vertex dimension.  It must be pre allocated.
		*/
		void getXyzPointsOfPatchInGlobalCrs(const unsigned int & patchIndex, double * xyzPoints) const;

		/**
		* Get all the XYZ points of all patches of this individual representation
		* XYZ points are given in the local CRS.
		* @param xyzPoints A linearized 2d array where the first (quickest) dimension is coordinate dimension (XYZ) and second dimension is vertex dimension. It must be pre allocated.
		*/
		void getXyzPointsOfAllPatches(double * xyzPoints) const;

		/**
		* Get all the XYZ points of all patches of this individual representation
		* XYZ points are given in the global CRS.
		* @param xyzPoints A linearized 2d array where the first (quickest) dimension is coordinate dimension (XYZ) and second dimension is vertex dimension.  It must be pre allocated.
		*/
		void getXyzPointsOfAllPatchesInGlobalCrs(double * xyzPoints) const;

		/**
		* Get the seismic support representation set of this representation
		*/
		//const std::vector<AbstractRepresentation*> & getSeismicSupportSet() {return seismicSupportSet;}
		
		/**
		* Get the seismic support representation uuid set of this representation.
		* Useful when one of the seismic support representation is not accessible. At least we know its uuid.
		*/
		//std::vector<std::string> getSeismicSupportUuidSet();

		/**
		* Get the count of seismic points in a particular patch of this representation
		*/
		//unsigned int getSeismicPointCountOfPatch(const unsigned int & patchIndex);

		/**
		* Get the seismic support of a specific patch.
		* @return nullptr if seismic info have not been provided.
		*/
		AbstractRepresentation* getSeismicSupportOfPatch(const unsigned int & patchIndex);

		virtual unsigned int getPatchCount() const = 0;

		/**
		* Pushes back this representaiton into a representation set
		* @param repSet	The representation set representation which will contain this representation.
		* @param xml	If set to true (default), then xml relationships will be updated. If set to no, only memory (and epc) relationships will be updated.
		*/
		void pushBackIntoRepresentationSet(class RepresentationSetRepresentation * repSet, bool xml = true);

		/**
		 * Get the count of representation set representations which contain this representation
		 */
		ULONG64 getRepresentationSetRepresentationCount() const;

		/**
		 * Get the parent representation set representations at the specified index of the representation set representation list.
		 */
		RepresentationSetRepresentation* getRepresentationSetRepresentation(const ULONG64  & index) const;

		void setHdfProxy(common::AbstractHdfProxy * proxy);

		/**
		* Push back a patch of seismic 3D coordinates info.
		* The index this patch will be located must be consistent with the index of the geometry patch it is related to.
		*/
		void addSeismic3dCoordinatesToPatch(const unsigned int patchIndex, double * inlines, double * crosslines, const unsigned int & pointCount,
			resqml2::AbstractRepresentation * seismicSupport, common::AbstractHdfProxy * proxy);

		void addSeismic3dCoordinatesToPatch(const unsigned int patchIndex, const double & startInline, const double & incrInline, const unsigned int & countInline,
			const double & startCrossline, const double & incrCrossline, const unsigned int & countCrossline,
			resqml2::AbstractRepresentation * seismicSupport);

		/**
		* Push back a patch of seismic 2D coordinates info.
		* The index this patch will be located must be consistent with the index of the geometry patch it is related to.
		* @param The index of the geometry patch which receives these seismic coordinates
		*/
		void addSeismic2dCoordinatesToPatch(const unsigned int patchIndex, double * lineAbscissa, const unsigned int & pointCount,
			resqml2::AbstractRepresentation * seismicSupport, common::AbstractHdfProxy * proxy);

		/**
		* Get all the abscissa of the points of a specific patch related to seismic line 2d.
		* @return nullptr if seismic info have not been provided.
		*/
		void getSeismicLineAbscissaOfPointsOfPatch(const unsigned int & patchIndex, double* values);

		static const char* XML_TAG;

	protected:

		virtual std::vector<epc::Relationship> getAllEpcRelationships() const;
		virtual void importRelationshipSetFromEpc(common::EpcDocument* epcDoc);

		// XML forward relationships
		class AbstractFeatureInterpretation*				interpretation;
		common::AbstractHdfProxy * 							hdfProxy;
		class AbstractLocal3dCrs *							localCrs;
		std::vector<AbstractRepresentation*> 				seismicSupportSet;

		// XML backward relationships
		std::vector<SubRepresentation*>						subRepresentationSet;
		std::vector<AbstractProperty*>						propertySet;
		std::vector<AbstractRepresentation*> 				seismicSupportedRepSet;
		std::vector<class RepresentationSetRepresentation*>	representationSetRepresentationSet;

		friend void AbstractProperty::setRepresentation(AbstractRepresentation * rep);
	};
}


