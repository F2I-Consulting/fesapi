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

#include "resqml2/AbstractValuesProperty.h"

namespace resqml2_0_1
{
	class DLL_IMPORT_OR_EXPORT CommentProperty : public resqml2::AbstractValuesProperty
	{
	public:

		/**
		* Only to be used in partial transfer context
		*/
		CommentProperty(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : resqml2::AbstractValuesProperty(partialObject) {}

		/**
		* Creates an instance of this class in a gsoap context.
		* @param rep						The representation which supports these property values.
		* @param guid						The guid to set to the property. If empty then a new guid will be generated.
		* @param title						A title for the instance to create.
		* @param dimension					The dimension of each value (scalar properties == 1).
		* @param attachmentKind				The topological orbit which support each value.
		* @param energisticsPropertyKind	The property kind of these property values which must be defined in the standard energistics property type dictionary.
		*/
		CommentProperty(resqml2::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			const unsigned int & dimension, const gsoap_resqml2_0_1::resqml2__IndexableElements & attachmentKind, const gsoap_resqml2_0_1::resqml2__ResqmlPropertyKind & energisticsPropertyKind);

		/**
		* Creates an instance of this class in a gsoap context.
		* @param rep						The representation which supports these property values.
		* @param guid						The guid to set to the property. If empty then a new guid will be generated.
		* @param title						A title for the instance to create.
		* @param dimension					The dimension of each value (scalar properties == 1).
		* @param attachmentKind				The topological orbit which support each value.
		* @param localPropKind				The property kind of these property values which must be defined in the EPC document as a local property kind.
		*/
		CommentProperty(resqml2::AbstractRepresentation * rep, const std::string & guid, const std::string & title,
			const unsigned int & dimension, const gsoap_resqml2_0_1::resqml2__IndexableElements & attachmentKind, resqml2::PropertyKind * localPropKind);

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		CommentProperty(gsoap_resqml2_0_1::_resqml2__CommentProperty* fromGsoap): AbstractValuesProperty(fromGsoap) {}

		/**
		* Destructor does nothing since the memory is managed by the gsoap context.
		*/
		~CommentProperty() {}

		static const char* XML_TAG;
		virtual std::string getXmlTag() const {return XML_TAG;}

		/**
		* Add an array of string values to the property values.
		* @param values					All the property values to set ordered according the topology of the representation it is based on.
		* @param proxy					The HDF proxy where to write the property values. It must be already opened for writing and won't be closed in this method.
		*/
		void pushBackStringHdf5ArrayOfValues(const std::vector<std::string> & values, common::AbstractHdfProxy* proxy);

		std::string pushBackRefToExistingDataset(common::AbstractHdfProxy* hdfProxy, const std::string & datasetName = "", const long & nullValue = (std::numeric_limits<long>::max)());

		/**
		* Get all the values of the instance which are supposed to be string ones.
		*/
		std::vector<std::string> getStringValuesOfPatch(const unsigned int & patchIndex);

		/**
		* Check if the associated local property kind is allowed for this property.
		*/
		bool validatePropertyKindAssociation(resqml2::PropertyKind* pk);

		/**
		* Check if the associated standard property kind is allowed for this property.
		*/
		bool validatePropertyKindAssociation(const gsoap_resqml2_0_1::resqml2__ResqmlPropertyKind & pk);

	};
}
