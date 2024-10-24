# Licensed to the Apache Software Foundation (ASF) under one
# or more contributor license agreements.  See the NOTICE file
# distributed with this work for additional information
# regarding copyright ownership.  The ASF licenses this file
# to you under the Apache License, Version 2.0 (the
# "License"; you may not use this file except in compliance
# with the License.  You may obtain a copy of the License at
# http://www.apache.org/licenses/LICENSE-2.0
# Unless required by applicable law or agreed to in writing,
# software distributed under the License is distributed on an
# "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
# KIND, either express or implied.  See the License for the
# specific language governing permissions and limitations
# under the License.

FROM almalinux:8

LABEL maintainer="philippe.verney@f2i-consulting.com"

ENV CFLAGS="-fPIC -O2"
ENV CXXFLAGS="-fPIC -O2"

RUN	dnf install -y \
	# git is used to clone fesapi repository from GitHub \	
	git \
	# C and C++ compilers
	gcc-c++ \
	# make is used to process Unix Makefiles
	make \
	# cmake is used to generate Makefiles
	cmake \
	# boost is used for UUID management
	boost-devel \
	# wget is used to download ressources. We use it instead of ADD in order to
	# minimize the size of the docker image by limitating the number of layers
	wget \
	# zlib is used to build minizip
	zlib-devel

##############
# minizip is a dependency of fesapi
##############
WORKDIR /fesapiEnv
RUN mkdir dependencies && \
	cd dependencies && \
	git clone https://github.com/F2I-Consulting/Minizip.git && \
	mkdir -p minizip-build && \
	cd minizip-build && \
	cmake3 -G "Unix Makefiles" -DCMAKE_INSTALL_PREFIX:STRING=/fesapiEnv/dependencies/minizip-install ../Minizip && \
	cmake3 --build . --config Release && \
	cmake3 --install .

##############
# hdf5 is a dependency of fesapi
##############
WORKDIR /fesapiEnv/dependencies
RUN wget https://support.hdfgroup.org/ftp/HDF5/releases/hdf5-1.12/hdf5-1.12.3/src/hdf5-1.12.3.tar.gz && \
	tar xf hdf5-1.12.3.tar.gz && \
	cd hdf5-1.12.3 && \
	mkdir build && \
	cd build && \
	cmake3 -G "Unix Makefiles" \
		-DCMAKE_BUILD_TYPE:STRING=Release \
		-DBUILD_SHARED_LIBS:BOOL=OFF \
		-DBUILD_TESTING:BOOL=OFF \
		-DHDF5_BUILD_TOOLS:BOOL=OFF \
		-DHDF5_BUILD_EXAMPLES:BOOL=OFF \
		-DHDF5_BUILD_CPP_LIB:BOOL=OFF \
		-DHDF5_BUILD_HL_LIB:BOOL=OFF \
		-DCMAKE_INSTALL_PREFIX:STRING=/fesapiEnv/dependencies/hdf5-install \
		.. && \
	cmake3 --build . --config Release && \	
	cmake3 --install .

################
# fesapi install
WORKDIR /fesapiEnv
RUN git clone https://github.com/F2I-Consulting/fesapi.git && \
	cd fesapi && \
	cd ..  && \
	mkdir build && \
	cd build && \
	cmake3 \
		-DHDF5_ROOT=/fesapiEnv/dependencies/hdf5-install \
		-DHDF5_USE_STATIC_LIBRARIES=TRUE \
		-DMINIZIP_ROOT=/fesapiEnv/dependencies/minizip-install \
		-DWITH_EXAMPLE=TRUE \
		-DCMAKE_BUILD_TYPE=Release \
		../fesapi && \
	cmake3 --build . --config Release && \
	cmake3 --install .

# generate .epc and .h5 files
WORKDIR /fesapiEnv/build/install
RUN ./example
