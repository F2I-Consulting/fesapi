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

#include "common/AbstractObject.h"

namespace resqml2
{
	class DLL_IMPORT_OR_EXPORT AbstractProperty: public common::AbstractObject
	{
	public:

		/**
		* Only to be used in partial transfer context
		*/
		AbstractProperty(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : common::AbstractObject(partialObject) {}

		/**
		* Default constructor
		* Set the relationship with an AbstractRepresentation and a local property type.
		*/
		AbstractProperty(): local3dCrs(nullptr) {}

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		AbstractProperty(gsoap_resqml2_0_1::resqml2__AbstractProperty* fromGsoap) : common::AbstractObject(fromGsoap), local3dCrs(nullptr) {}

		/**
		* Destructor does nothing since the memory is managed by the gsoap context.
		*/
		virtual ~AbstractProperty() {}

		/**
		 * Set the representation which is associated to the current property.
		 */
		void setRepresentation(class AbstractRepresentation * rep);

		/**
		* @return	null pointer if no representation is associated to this property. Otherwise return the data object reference of the associated representation.
		*/
		gsoap_resqml2_0_1::eml20__DataObjectReference* getRepresentationDor() const;

		/**
		* Getter for the representation which supports this instance values.
		*/
		class AbstractRepresentation* getRepresentation() const;

		/*
		* Getter for the uuid of the representation which is described by this property
		*/
		std::string getRepresentationUuid() const;

		/*
		* Getter for the title of the representation which is described by this property
		*/
		std::string getRepresentationTitle() const;

		/*
		* Getter for the content type of the representation which is described by this property
		*/
		std::string getRepresentationContentType() const;

		/**
		 * Set the representation which is associated to the current property.
		 */
		void setTimeSeries(class TimeSeries * ts);

		/**
		* Getter for the time series which is associated to this property.
		*/
		TimeSeries* getTimeSeries() const;

		/**
		* @return	null pointer if no time series is associated to this property. Otherwise return the data object reference of the associated time series.
		*/
		gsoap_resqml2_0_1::eml20__DataObjectReference* getTimeSeriesDor() const;

		/*
		* Getter for the uuid of the time series which is associated to this property.
		*/
		std::string getTimeSeriesUuid() const;

		/*
		* Getter for the uuid of the time series which is associated to this property.
		*/
		std::string getTimeSeriesTitle() const;

		/**
		* Set the timestamp of this property by means of an index in a time series
		*
		* @param[in]	 timeIndex	The index of the timestamp of the property in the time series.
		* @param[in]	 ts			The time series which contains the timestamp of this property.
		*/
		void setTimeIndex(const unsigned int & timeIndex, class TimeSeries * ts);

		/**
		* Set the timestep of this property
		*/
		void setTimeStep(const unsigned int & timeStep);

		/**
		* Get the timestamp of this property
		* @return maximum value of unsigned int is returned if no timestamp is allowed.
		*/
		time_t getTimestamp() const;

		/**
		* Get the time index of this property in its assocaited time series
		*/
		unsigned int getTimeIndex() const;

		/**
		* Set the Hdf Proxy where the numerical values are stored.
		*/
		void setHdfProxy(common::AbstractHdfProxy * proxy);

		/**
		* Getter for the hdf proxy which stores this instance values.
		*/
		common::AbstractHdfProxy* getHdfProxy() const;

		/*
		 * Getter for the uuid of the hdf proxy which is used for storing the numerical values of this property.
		 * An empty string is returned if no hd fproxy is used for storing the numerical values.
		 */
		std::string getHdfProxyUuid() const;

		/**
		* Getter (in read only mode) of the element count per property value.
		* If the property is a scalar one then it should be one.
		* If it is a vectorial one, the it should be more than one.
		* It is not possible to have some tensor property values (more dimension than a vector).
		*/
		unsigned int getElementCountPerValue() const;

		/**
		* Get the kind of elments the property values are attached to.
		*/
		gsoap_resqml2_0_1::resqml2__IndexableElements getAttachmentKind() const;

		/**
		* Indicates if the property kind attached to this property is either from the standard catalog of Energistics or from a local property kind.
		*/
		bool isAssociatedToOneStandardEnergisticsPropertyKind() const;

		//*********************************************
		//****** PROP KIND ****************************
		//*********************************************

		/**
		* Get the title of the property kind of this property
		*/
		std::string getPropertyKindDescription() const;

		/**
		* Get the title of the property kind of this property
		*/
		std::string getPropertyKindAsString() const;

		/**
		* Get the title of the parent of the property kind.
		*/
		std::string getPropertyKindParentAsString() const;

		/**
		* Getter for the energistics property kind which is associated to this intance.
		*/
		gsoap_resqml2_0_1::resqml2__ResqmlPropertyKind getEnergisticsPropertyKind() const;

		/**
		* Set the property kind of the property to a local one.
		*/
		void setLocalPropertyKind(class PropertyKind* propKind);

		/**
		* @return	null pointer if no local property kind is associated to this property. Otherwise return the data object reference of the associated local property kind.
		*/
		gsoap_resqml2_0_1::eml20__DataObjectReference* getLocalPropertyKindDor() const;

		/**
		* Get the uuid of the local property kind which is associated to this property.
		*/
		std::string getLocalPropertyKindUuid() const;

		/**
		* Get the title of the local property kind which is associated to this property.
		*/
		std::string getLocalPropertyKindTitle() const;

		/**
		* Getter for the local property kind which is associated to this instance.
		* If nullptr is returned then it means this instance is associated to an energistics standard property kind.
		*/
		class PropertyKind* getLocalPropertyKind() const;

		/**
		* Check if the associated local property kind is allowed for this property.
		*/
		virtual bool validatePropertyKindAssociation(class PropertyKind* pk) = 0;

		/**
		* Check if the associated standard property kind is allowed for this property.
		*/
		virtual bool validatePropertyKindAssociation(const gsoap_resqml2_0_1::resqml2__ResqmlPropertyKind & pk) = 0;

	protected:

		void setXmlRepresentation(class AbstractRepresentation * rep);
		void setXmlTimeSeries(TimeSeries * ts);
		void setXmlLocalPropertyKind(class PropertyKind* propKind);

		virtual std::vector<epc::Relationship> getAllEpcRelationships() const;
		virtual void importRelationshipSetFromEpc(common::EpcDocument * epcDoc);

		class AbstractLocal3dCrs *		local3dCrs;			/// The used local 3D CRS in case the property values need one.
	};
}
