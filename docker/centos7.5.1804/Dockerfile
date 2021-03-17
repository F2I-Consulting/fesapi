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

FROM centos:7.5.1804

LABEL maintainer="philippe.verney@f2i-consulting.com"

ENV CFLAGS="-fPIC -O2"
ENV CXXFLAGS="-fPIC -O2"

RUN	yum install -y \
	# minizip is a dependence of fesapi \ 
	minizip-devel \ 	
	# git is used to clone fesapi repository from GitHub \	
	git \				
	# C and C++ compilers
	gcc-c++ \		
	# make is used to process Unix Makefiles
	make \				
	# boost is used for UUID management
	boost-devel \
	# wget is used to download ressources. We use it instead of ADD in order to
	# minimize the size of the docker image by limitating the number of layers
	wget 
	
# epel repository is used to get cmake3 packages
RUN yum search epel-release && \
	yum info epel-release && \
	yum install -y epel-release && \
	yum --enablerepo=epel install -y \
		# cmake3 is used to automatize building configuration
		cmake3

##############
# hdf5 install
# hdf5 is a dependence of fesapi
WORKDIR /fesapiEnv
RUN mkdir dependencies && \
	cd dependencies && \
	wget https://support.hdfgroup.org/ftp/HDF5/releases/hdf5-1.10/hdf5-1.10.6/src/hdf5-1.10.6.tar.gz && \
	tar xf hdf5-1.10.6.tar.gz && \
	cd hdf5-1.10.6 && \
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
		-DCMAKE_INSTALL_PREFIX:STRING=/fesapiEnv/dependencies/hdf5-1.10.6/hdf5 \
		.. && \
	cmake3 --build . --config Release && \	
	make install 

################
# fesapi install
WORKDIR /fesapiEnv
RUN git clone https://github.com/F2I-Consulting/fesapi.git && \
	cd fesapi && \
	cd ..  && \
	mkdir build && \
	cd build && \
	cmake3 \
		-DHDF5_C_INCLUDE_DIR=/fesapiEnv/dependencies/hdf5-1.10.6/hdf5/include \
		-DHDF5_C_LIBRARY_RELEASE=/fesapiEnv/dependencies/hdf5-1.10.6/hdf5/lib/libhdf5.a \
		-DMINIZIP_INCLUDE_DIR=/usr/include/minizip \
		-DMINIZIP_LIBRARY_RELEASE=/usr/lib64/libminizip.so \
		-DZLIB_INCLUDE_DIR=/usr/include \
		-DZLIB_LIBRARY_RELEASE=/usr/lib64/libz.so \
		-DWITH_EXAMPLE=TRUE \
		-DCMAKE_BUILD_TYPE=Release \
		../fesapi && \
	make VERBOSE=OFF && \
	make install

# generate .epc and .h5 files
WORKDIR /fesapiEnv/build/install
RUN ./example
