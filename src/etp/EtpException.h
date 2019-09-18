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

#include <exception>
#include <cstdint>
#include <string>

namespace ETP_NS
{

	class EtpException : public std::exception
	{
	private:
		int32_t errorCode;
		std::string message;

	public:

		EtpException(int32_t code, const std::string & msg) :
			errorCode(code),
			message(msg) {}

		int32_t getErrorCode() const { return errorCode; }

		const char* what() const noexcept {
			return message.c_str();
		}
	};

}
