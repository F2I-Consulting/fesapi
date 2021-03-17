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
#include "../src/witsml1_4/Trajectory.h"
%}

#if defined(SWIGJAVA) || defined(SWIGCSHARP)	
	%nspace WITSML1_4_NS::Trajectory;
#endif

namespace WITSML1_4_NS
{
	%nodefaultctor; // Disable creation of default constructors
	
#if defined(SWIGPYTHON)
	%rename(witsml14_Trajectory) Trajectory;
#endif
	/**
	 * @brief	It contains many trajectory stations to capture the information about individual survey points.
	 *			This class can only be used in import mode for now.
	 */
	class Trajectory : public WITSML2_NS::Trajectory
	{
	public:
	};
}
