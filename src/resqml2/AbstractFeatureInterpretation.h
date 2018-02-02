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
/*-----------------------------------------------------------------------
Copyright F2I-CONSULTING, (2014-2016)

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

#include "resqml2/GridConnectionSetRepresentation.h"

namespace resqml2_0_1
{
	class StructuralOrganizationInterpretation;
}

namespace resqml2
{
	class DLL_IMPORT_OR_EXPORT AbstractFeatureInterpretation : public common::AbstractObject
	{
	protected:

		/**
		* Only to be used in partial transfer context
		*/
		AbstractFeatureInterpretation(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : common::AbstractObject(partialObject) {}

		/**
		* Default constructor
		* Set the gsoap proxy to nullptr.
		*/
		AbstractFeatureInterpretation() {}

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		AbstractFeatureInterpretation(gsoap_resqml2_0_1::resqml2__AbstractFeatureInterpretation* fromGsoap) : common::AbstractObject(fromGsoap) {}

		void setInterpretedFeatureInXml(resqml2::AbstractFeature* feature);

	public:

		/**
		* Destructor does nothing since the memory is managed by the gsoap context.
		*/
		virtual ~AbstractFeatureInterpretation() {}

		/**
		* @return	null pointer if no interpreted feature is associated to this interpretation. Otherwise return the data objet reference of the associated interpreted feature.
		*/
		gsoap_resqml2_0_1::eml20__DataObjectReference* getInterpretedFeatureDor() const;

		std::string getInterpretedFeatureUuid() const;

		/**
		 * Set the feature which is interpreted by the current instance.
		 */
		void setInterpretedFeature(AbstractFeature* feature);

		/**
		* Get the feature this instance interprets
		*/
		AbstractFeature* getInterpretedFeature() const;

		/**
		* Init the domain of the interpretation based on its representations
		* @param	defaultDomain	The default domain to set when there is no representation set to this interpretation
		*/
		const gsoap_resqml2_0_1::resqml2__Domain & initDomain(const gsoap_resqml2_0_1::resqml2__Domain & defaultDomain) const;

		/**
		* Set the domain of the interpretation
		*/
		gsoap_resqml2_0_1::resqml2__Domain getDomain() const;

		/**
		* Get all the representations of this interpretation
		*/
		std::vector<AbstractRepresentation*> getRepresentationSet() const;

		/**
		 * Get the interpretation count of this feature.
		 */
		unsigned int 						getRepresentationCount() const;

		/**
		 * Get a particular interpretation of this feature according to its position in the interpretation ordering.
		 */
		AbstractRepresentation*				getRepresentation(const unsigned int & index) const;

		/**
		* Get all the Grid Connection Set Representation which reference this interpretation.
		*/
		std::vector<GridConnectionSetRepresentation *>	getGridConnectionSetRepresentationSet();

		/**
		* Indicates that this interpretation is a frontier of a stack of an organization
		* BE CAREFUL : Does not add back this instance to the organization. It is assumed it is already done.
		*/
		void setBottomFrontierOf(resqml2_0_1::StructuralOrganizationInterpretation* structOrg);
		void setTopFrontierOf(resqml2_0_1::StructuralOrganizationInterpretation* structOrg);
		void setSideFrontierOf(resqml2_0_1::StructuralOrganizationInterpretation* structOrg);

	protected:

		virtual std::vector<epc::Relationship> getAllEpcRelationships() const;
		
		virtual void importRelationshipSetFromEpc(common::EpcDocument* epcDoc);

		// XML backward relationship
		std::vector<AbstractRepresentation *>						representationSet;
		std::vector<GridConnectionSetRepresentation *>				gridConnectionSetRepresentationSet;

		std::vector<resqml2_0_1::StructuralOrganizationInterpretation *>	isBottomFrontierSet;
		std::vector<resqml2_0_1::StructuralOrganizationInterpretation *>	isTopFrontierSet;
		std::vector<resqml2_0_1::StructuralOrganizationInterpretation *>	isSideFrontierSet;

		friend void AbstractRepresentation::setInterpretation(AbstractFeatureInterpretation * interp);
		friend void GridConnectionSetRepresentation::pushBackInterpretation(AbstractFeatureInterpretation* interp);
	};
}

