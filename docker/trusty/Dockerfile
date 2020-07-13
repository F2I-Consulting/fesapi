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

FROM ubuntu:trusty

LABEL maintainer="philippe.verney@f2i-consulting.com"

ENV CFLAGS="-fPIC -O2"
ENV CXXFLAGS="-fPIC -O2"

RUN	apt-get update &&\
	apt-get -y install build-essential uuid-dev zlib1g-dev libhdf5-dev wget git

RUN	apt-get purge cmake swig

RUN rm -rf /usr/local/cmake-*

WORKDIR /fesapiEnv

# CMake install
RUN mkdir dependencies && \
	cd dependencies && \
    wget https://cmake.org/files/v3.12/cmake-3.12.0-Linux-x86_64.sh && \
	sh cmake-3.12.0-Linux-x86_64.sh --prefix=/usr/local --exclude-subdir

# Minizip install
RUN cd dependencies && \
	git clone https://github.com/F2I-Consulting/Minizip.git && \
    cd Minizip && \
    mkdir build && \
    cd build && \
	cmake -G "Unix Makefiles" .. && \
	cmake --build . && \
	make install

################
# fesapi install
RUN git clone https://github.com/F2I-Consulting/fesapi.git && \
	cd fesapi && \
	git checkout resqml22 && \
	cd ..  && \
	mkdir build && \
	cd build && \
	cmake \
		-DHDF5_C_INCLUDE_DIR=/usr/include \
		-DHDF5_C_LIBRARY_RELEASE=/usr/lib/x86_64-linux-gnu/libhdf5.so \
		-DMINIZIP_INCLUDE_DIR=/fesapiEnv/dependencies/Minizip/build/install/include \
		-DMINIZIP_LIBRARY_RELEASE=/fesapiEnv/dependencies/Minizip/build/install/lib/libminizip.a \
		-DZLIB_INCLUDE_DIR=/usr/include \
		-DZLIB_LIBRARY_RELEASE=/usr/lib/x86_64-linux-gnu/libz.so \
		-DUUID_INCLUDE_DIR=/usr/include \
		-DUUID_LIBRARY_RELEASE=/usr/lib/x86_64-linux-gnu/libuuid.so \
		-DCMAKE_BUILD_TYPE=Release \
		-DWITH_EXAMPLE=TRUE \
		-DWITH_RESQML2_2=TRUE \
		-DWITH_TEST=TRUE \
		../fesapi && \
	make VERBOSE=OFF && \
	make install

# generate .epc and .h5 files
ENV LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/fesapiEnv/build/install/lib64/:/usr/local/lib/
WORKDIR /fesapiEnv/build/install
RUN ./example
