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

#include "AbstractTest.h"

namespace resqml2_test {
	class AbstractBigIjkGridRepresentationTest : public commontest::AbstractTest {
	public:
		const unsigned int iCount;
		const unsigned int jCount;
		const unsigned int kCount;
		const unsigned int faultCount;
		const double xMin;
		const double xMax;
		const double yMin;
		const double yMax;
		const double zMin;
		const double zMax;
		const double faultThrow;
		double* nodesIjkGridRepresentation;

		AbstractBigIjkGridRepresentationTest(
			const std::string & repoPath,
			unsigned int iCount, unsigned int jCount, unsigned int kCount, 
			unsigned int faultCount, 
			double xMin, double xMax, double yMin, double yMax, double zMin, double zMax,
			double faultThrow);

		~AbstractBigIjkGridRepresentationTest() {
			if (nodesIjkGridRepresentation != nullptr) {
				delete[] nodesIjkGridRepresentation;
			}
		}
	protected:
		/**
		 * Get the number of nodes (including splitted ones) of the generated grid. 
		 * @param iCount number of cells in the I direction.
		 * @param jCount number of cells in the J direction.
		 * @param kCount number of cells in the K direction.
		 * @param faultCount number of faults. Faults are parallel to YZ plane (they fit with i-interfaces). faultCount in [0; iCount[.
		 */
		unsigned long long initNodesCountIjkGridRepresentation(unsigned int iCount, unsigned int jCount, unsigned int kCount, unsigned int faultCount);

		/**
		 * Initialize generated grid geometry. Result is stored into class variable nodesIjkGridRepresentation.
		 * @param iCount number of cells in the I direction.
		 * @param jCount number of cells in the J direction.
		 * @param kCount number of cells in the K direction.
		 * @param faultCount number of faults. Faults are parallel to YZ plane (they fit with i-interfaces). faultCount in [0; iCount[.
		 * @param xMin minimum x value of the grid.
		 * @param xMax maximum x value of the grid.
		 * @param yMin minimum y value of the grid.
		 * @param yMax maximum y value of the grid.
		 * @param zMin minimum z value of the grid (without considering any fault throw).
		 * @param zMax maximum z value of the grid (without considering any fault throw).
		 * @param faultThrow length of the fault throw along z axis.
		 * @return nodesIjkGridRepresentation.
		 */
		double * initNodesIjkGridRepresentation(unsigned int iCount, unsigned int jCount, unsigned int kCount,
			unsigned int faultCount,
			double xMin, double xMax, double yMin, double yMax, double zMin, double zMax,
			double faultThrow);
		
		/**
		 * Initialize split coordinate lines informations.
		 * @param pillarOfCoordinateLine					Properly allocated output parameter. For each split coordinate line, indicates which pillar it belongs to. 
		 * @param splitCoordinateLineColumnCumulativeCount	Properly allocated output parameter. For each split coordinate line, indicates how many columns of the ijk grid are incident to it.
															See IjkGridExplicitRepresentation documentation for more information. 
		* @param splitCoordinateLineColumns					For each split coordinate line, indicates which columns are incident to it.
	
		 */
		void initSplitCoordinateLine(unsigned int * pillarOfCoordinateLine, 
			unsigned int * splitCoordinateLineColumnCumulativeCount,
			unsigned int * splitCoordinateLineColumns);

		/**
		 * Initialize generated grid discrete property values. For a given cell, corresponding value
		 * if its k index.
		 * @param discretePropertyValues Properly allocated output parameter.
		 */
		void initDiscreteProperty(unsigned short * discretePropertyValues);

		/**
		 * Initialize generated grid continuous property values. For a given cell, corresponding value
		 * is taken in [0.; 1.] by applying an homogeneous gradient from 0. to 1. in the I direction. 
		 * @param continuousPropertyValues Properly allocated output parameter.
		 */
		void initContinuousProperty(double * continuousPropertyValues);
	};
}
