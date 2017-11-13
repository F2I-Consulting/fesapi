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

#include "resqml2_0_1/AbstractSurfaceRepresentation.h"

namespace resqml2_0_1
{
	class DLL_IMPORT_OR_EXPORT Grid2dSetRepresentation : public AbstractSurfaceRepresentation
	{
	private :
		gsoap_resqml2_0_1::resqml2__PointGeometry* getPointGeometry2_0_1(const unsigned int & patchIndex) const;

	public:

		/**
		* Only to be used in partial transfer context
		*/
		Grid2dSetRepresentation(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : AbstractSurfaceRepresentation(partialObject) {}

		/**
		* Creates an instance of this class in a gsoap context.
		* @param soap				The soap context to serialize.
		* @param guid				The guid to set to the new instance. If empty then a new guid will be generated.
		* @param title				A title for the instance to create.
		*/
		Grid2dSetRepresentation(resqml2::AbstractFeatureInterpretation* interp, resqml2::AbstractLocal3dCrs * crs,
			const std::string & guid, const std::string & title);

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		Grid2dSetRepresentation(gsoap_resqml2_0_1::_resqml2__Grid2dSetRepresentation* fromGsoap): AbstractSurfaceRepresentation(fromGsoap) {}

		/**
		* Destructor does nothing since the memory is managed by the gsoap context.
		*/
		~Grid2dSetRepresentation() {}

		static const char* XML_TAG;
		virtual std::string getXmlTag() const {return XML_TAG;}

		std::string getHdfProxyUuid() const;

		unsigned int getNodeCountAlongIAxis(const unsigned int & patchIndex) const;

		unsigned int getNodeCountAlongJAxis(const unsigned int & patchIndex) const;

        /**
		* Get the xyz point count in a given patch.
		*/
		ULONG64 getXyzPointCountOfPatch(const unsigned int & patchIndex) const {return getNodeCountAlongIAxis(patchIndex) * getNodeCountAlongJAxis(patchIndex);}

		/**
		* Get all the XYZ points of a particular patch of this representation.
		* XYZ points are given in the local CRS.
		* @param xyzPoints A linearized 2d array where the first (quickest) dimension is coordinate dimension (XYZ) and second dimension is vertex dimension. It must be pre allocated.
		*/
		void getXyzPointsOfPatch(const unsigned int & patchIndex, double * xyzPoints) const;

		/**
		 * Get the number of patches
		 */
		unsigned int getPatchCount() const;

		/**
		* Get all the z values of a patch located at a specific index of the geometry points.
		* Z Values are given in the local CRS.
		* @param values		All the z values of the selected patch. i dimension is the quickest.
		*/
		void getZValuesOfPatch(const unsigned int & patchIndex, double* values) const;

		/**
		* Get all the z values of a patch located at a specific index of the geometry points.
		* Z Values are given in the global CRS.
		* @param values		All the z values of the selected patch. i dimension is the quickest.
		*/
		void getZValuesOfPatchInGlobalCrs(const unsigned int & patchIndex, double* values) const;

		/**
		* Push back a new grid2d patch
		* @param zValues						The Z values of the patch to push back.
		* @param numI							The total number of nodes in the fastest storage direction.
		* @param numJ							The total number of nodes in the slowest storage direction.
		* @param proxy							The hdf proxy identifying the HDF file which will store the z values.
		* @param supportingGrid2dRepresentation	The grid 2d representation representing the support of the Z values.
		* @param startIndexI					The index on I direction of the origin of the patch on the supporting representation.
		* @param startIndexJ					The index on J direction of the origin of the patch on the supporting representation.
		* @param indexIncrementI				The index increment on I direction of the patch on the supporting representation.
		* @param indexIncrementJ				The index increment on J direction of the patch on the supporting representation.
		*/
		void pushBackGeometryPatch(
				double * zValues,
				const unsigned int & numI, const unsigned int & numJ, common::AbstractHdfProxy* proxy,
				Grid2dRepresentation * supportingGrid2dRepresentation,
				const unsigned int & startIndexI = 0, const unsigned int & startIndexJ = 0,
				const int & indexIncrementI = 1, const int & indexIncrementJ = 1);

		/**
		* Get the supporting representation set of this representation
		*/
		std::vector<Grid2dRepresentation *>  getSupportingRepresentationSet() const {return supportingRepresentationSet;}
		
		/**
		* Get the supporting representation uuid of this representation.
		* Useful when the supporting representation is not accessible. At least we know its uuid.
		*/
		std::string getSupportingRepresentationUuid(const unsigned int & patchIndex) const;

		/**
		* Get the supporting representation of a particular patch of the grid 2d set representation
		*/
		Grid2dRepresentation * getSupportingRepresentation(const unsigned int & patchIndex) {return supportingRepresentationSet[patchIndex];}

		/**
		* Get the index of the origin of the current geometry on a particular dimension of the supporting representation of a particular patch of this representation.
		*/
		int getIndexOriginOnSupportingRepresentation(const unsigned int & patchIndex, const unsigned int & dimension) const;

		/**
		* Get the number of nodes of the current geometry which is extracted from a particular dimension of the supporting representation of a particular patch of this representation.
		*/
		int getNodeCountOnSupportingRepresentation(const unsigned int & patchIndex, const unsigned int & dimension) const;

		/**
		* Get the index offset of the nodes of the current geometry on a particular dimension of the supporting representation of a particular patch of this representation.
		*/
		int getIndexOffsetOnSupportingRepresentation(const unsigned int & patchIndex, const unsigned int & dimension) const;

	private:
		std::vector<epc::Relationship> getAllEpcRelationships() const;
		void importRelationshipSetFromEpc(common::EpcDocument* epcDoc);

		std::vector<Grid2dRepresentation *> supportingRepresentationSet;
	};
}
