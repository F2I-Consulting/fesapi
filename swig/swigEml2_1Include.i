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
%{
#include "../src/eml2_1/PropertyKind.h"
%}

#if defined(SWIGJAVA) || defined(SWIGCSHARP)
	%nspace EML2_1_NS::PropertyKind;
#endif

namespace EML2_1_NS
{
	%nodefaultctor; // Disable creation of default constructors
	
	//************************************
	//************ HDF *******************
	//************************************
#if defined(SWIGJAVA) || defined(SWIGPYTHON)
	%rename(eml21_PropertyKind) PropertyKind;
#endif
	class PropertyKind : public EML2_NS::PropertyKind
	{
	public:
	};
	
}
