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