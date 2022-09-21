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

FROM ubuntu:focal

LABEL maintainer="philippe.verney@f2i-consulting.com"

RUN	apt update
RUN DEBIAN_FRONTEND=noninteractive apt install -y build-essential libboost-all-dev libminizip-dev libhdf5-dev cmake git

# fesapi install
WORKDIR /fesapiEnv
RUN git clone https://github.com/F2I-Consulting/fesapi.git

WORKDIR /fesapiEnv/build
RUN cmake \
		-Wno-dev -Wno-deprecated \
		-DMINIZIP_INCLUDE_DIR=/usr/include/minizip  \
		-DMINIZIP_LIBRARY_RELEASE=/usr/lib/x86_64-linux-gnu/libminizip.so  \
		-DWITH_EXAMPLE=TRUE  \
		-DWITH_RESQML2_2=TRUE  \
		-DWITH_TEST=TRUE  \
		-DCMAKE_BUILD_TYPE=RelWithDebInfo \
		../fesapi
RUN make -j4
RUN make install

WORKDIR /fesapiEnv/build/install
