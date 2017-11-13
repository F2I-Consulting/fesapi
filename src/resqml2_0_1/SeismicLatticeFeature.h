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

#include "resqml2_0_1/AbstractTechnicalFeature.h"

namespace resqml2_0_1
{
	class DLL_IMPORT_OR_EXPORT SeismicLatticeFeature : public AbstractTechnicalFeature
	{
	public:

		/**
		* Only to be used in partial transfer context
		*/
		SeismicLatticeFeature(gsoap_resqml2_0_1::eml20__DataObjectReference* partialObject) : AbstractTechnicalFeature(partialObject) {}

		/**
		* Creates an instance of this class in a gsoap context.
		* @param soapContext			The soap context where the underlying gsoap proxy is going to be created.
		* @param guid					The guid to set to this instance. If empty then a new guid will be generated.
		* @param title					A title for the instance to create.
		* @param inlineIncrement		The inline index increment.
		*								If inlines are parallel to the i-axis the inline increment will be the difference 
		*								in the inline number from node i=0, j=0 to node i=1, j=0.
		*								If inlines are parallel to the j-axis the inline increment will be the difference 
		*								in the inline number from node i=0, j=0 to node i=0, j=1. 
		*								The increment can be a positive or negative integer, but not zero.
		* @param crosslineIncrement		The crossline increment. The increment can be a positive or negative integer, but not zero.
		* @param originInline			The index of the first inline beginning at i=0, j=0.
		* @param originCrossline		The index of the first crosslineline beginning at i=0, j=0.
		* @param inlineCount			The count of inlines in this seismic lattice.
		* @param crosslineCount			The count of crosslines in this seismic lattice.
		*/
		SeismicLatticeFeature(soap* soapContext, const std::string & guid, const std::string & title,
			const int & inlineIncrement, const int & crosslineIncrement,
			const unsigned int & originInline, const unsigned int & originCrossline,
			const unsigned int & inlineCount, const unsigned int & crosslineCount);

		/**
		* Creates an instance of this class by wrapping a gsoap instance.
		*/
		SeismicLatticeFeature(gsoap_resqml2_0_1::_resqml2__SeismicLatticeFeature* fromGsoap): AbstractTechnicalFeature(fromGsoap) {}

		/**
		* Destructor does nothing since the memory is manged by the gsoap context.
		*/
		~SeismicLatticeFeature() {}

		/**
		* Get the crossline index increment between two consecutive crosslines.
		*/
		int getCrosslineIncrement() const;
		
		/**
		* Get the inline index increment between two consecutive inlines.
		*/
		int getInlineIncrement() const;
		
		/**
		* Get the index of the first crossline.
		*/
		int getOriginCrossline() const;
		
		/**
		* Get the index of the first inline.
		*/
		int getOriginInline() const;

		static const char* XML_TAG;
		virtual std::string getXmlTag() const {return XML_TAG;}
	};
}
