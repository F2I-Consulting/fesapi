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


#include "ContentType.h"

using namespace std; // in order not to prefix by "std::" for each class in the "std" namespace. Never use "using namespace" in *.h file but only in*.cpp file!!!
using namespace epc; // in order not to prefix by "epc::" for each class in the "epc" namespace. Never use "using namespace" in *.h file but only in*.cpp file!!!

ContentType::ContentType(const bool & isAssociatedToAnExtension, const std::string & contentType, const std::string & extensionOrPartName):
	isAssociatedToAnExtension(isAssociatedToAnExtension), contentTypeString(contentType), extensionOrPartName(extensionOrPartName)
{
	// Add the first character as slash if we forgot to add it
	if (!isAssociatedToAnExtension && extensionOrPartName[0] != '/')
		this->extensionOrPartName = '/' + extensionOrPartName;

	// delete star and dot from extension if we forgot not to give them for an extension
	if (isAssociatedToAnExtension && (extensionOrPartName[0] == '*' || extensionOrPartName[0] == '.'))
		this->extensionOrPartName = extensionOrPartName.substr(1);
}

const std::string & ContentType::getContentTypeString() const
{
	return contentTypeString;
}

const std::string & ContentType::getExtensionOrPartName() const
{
	return extensionOrPartName;
}

std::string ContentType::toString() const
{
	if (isAssociatedToAnExtension)
		return "<Default Extension=\"" + extensionOrPartName + "\" ContentType=\"" + contentTypeString + "\" />";
	else
		return "<Override PartName=\"" + extensionOrPartName + "\" ContentType=\"" + contentTypeString + "\"/>";
}















