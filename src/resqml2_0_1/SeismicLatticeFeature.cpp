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
#include "resqml2_0_1/SeismicLatticeFeature.h"

using namespace std;
using namespace resqml2_0_1;
using namespace gsoap_resqml2_0_1;

const char* SeismicLatticeFeature::XML_TAG = "SeismicLatticeFeature";

SeismicLatticeFeature::SeismicLatticeFeature(soap* soapContext, const string & guid, const string & title,
			const int & inlineIncrement, const int & crosslineIncrement,
			const unsigned int & originInline, const unsigned int & originCrossline,
			const unsigned int & inlineCount, const unsigned int & crosslineCount)
{
	if (soapContext == nullptr)
		throw invalid_argument("The soap context cannot be null.");

	gsoapProxy2_0_1 = soap_new_resqml2__obj_USCORESeismicLatticeFeature(soapContext, 1);
	_resqml2__SeismicLatticeFeature* seismicLattice = static_cast<_resqml2__SeismicLatticeFeature*>(gsoapProxy2_0_1);

	seismicLattice->InlineIndexIncrement = inlineIncrement;
	seismicLattice->CrosslineIndexIncrement = crosslineIncrement;
	seismicLattice->FirstInlineIndex = originInline;
	seismicLattice->FirstCrosslineIndex = originCrossline;
	seismicLattice->InlineCount = inlineCount;
	seismicLattice->CrosslineCount = crosslineCount;

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "", "");
}

int SeismicLatticeFeature::getCrosslineIncrement() const
{
	return static_cast<_resqml2__SeismicLatticeFeature*>(gsoapProxy2_0_1)->CrosslineIndexIncrement;
}
		
int SeismicLatticeFeature::getInlineIncrement() const
{
	return static_cast<_resqml2__SeismicLatticeFeature*>(gsoapProxy2_0_1)->InlineIndexIncrement;
}
		
int SeismicLatticeFeature::getOriginCrossline() const
{
	return static_cast<_resqml2__SeismicLatticeFeature*>(gsoapProxy2_0_1)->FirstCrosslineIndex;
}
		
int SeismicLatticeFeature::getOriginInline() const
{
	return static_cast<_resqml2__SeismicLatticeFeature*>(gsoapProxy2_0_1)->FirstInlineIndex;
}


