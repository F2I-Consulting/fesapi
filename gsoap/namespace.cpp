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
#include "stdsoap2.h"
SOAP_NMAC struct Namespace namespaces[] =
{
	{"SOAP-ENV", "http://schemas.xmlsoap.org/soap/envelope/", "http://www.w3.org/*/soap-envelope", NULL},
	{"SOAP-ENC", "http://schemas.xmlsoap.org/soap/encoding/", "http://www.w3.org/*/soap-encoding", NULL},
	{"xsi", "http://www.w3.org/2001/XMLSchema-instance", "http://www.w3.org/*/XMLSchema-instance", NULL},
	{"xsd", "http://www.w3.org/2001/XMLSchema", "http://www.w3.org/*/XMLSchema", NULL},
	{"gts", "http://www.isotc211.org/2005/gts", NULL, NULL},
	{"gsr", "http://www.isotc211.org/2005/gsr", NULL, NULL},
	{"dc", "http://purl.org/dc/terms/", NULL, NULL},
	{"resqml1", "http://www.resqml.org/schemas/1series", NULL, NULL},
	{"resqml2", "http://www.energistics.org/energyml/data/resqmlv2", NULL, NULL},
	{"witsml1", "http://www.witsml.org/schemas/1series", NULL, NULL},
	{"eml", "http://www.energistics.org/energyml/data/commonv2", NULL, NULL},
	{"gml", "http://www.opengis.net/gml/3.2", NULL, NULL},
	{"xlink", "http://www.w3.org/1999/xlink", NULL, NULL},
	{"gmd", "http://www.isotc211.org/2005/gmd", NULL, NULL},
	{"gco", "http://www.isotc211.org/2005/gco", NULL, NULL},
	{"ptm", "http://www.f2i-consulting.com/PropertyTypeMapping", NULL, NULL},
	{"abstract", "http://www.energistics.org/schemas/abstract", NULL, NULL},
	{NULL, NULL, NULL, NULL}
};

