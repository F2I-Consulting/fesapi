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

#ifdef WITH_ETP_SSL
#include "etp/ssl/SslServerSession.h"
#endif
#include "etp/PlainServerSession.h"

#include "etp/Server.h"

#include "MyServerInitializationParameters.h"

#include "common/EpcDocument.h"

#include "resqml2/AbstractRepresentation.h"
#include "resqml2_0_1/ContinuousProperty.h"

void generateProperties(RESQML2_NS::AbstractRepresentation* ijkgrid)
{
	for (unsigned short i = 0; i < (std::numeric_limits<unsigned short>::max)(); ++i) {
		auto name = "Two faulted sugar cubes timestamp " + std::to_string(i);
		RESQML2_NS::ContinuousProperty* continuousProp = ijkgrid->getRepository()->createContinuousProperty(ijkgrid, "", name, 1,
			gsoap_eml2_3::resqml22__IndexableElement__cells, gsoap_resqml2_0_1::resqml20__ResqmlUom__m, gsoap_resqml2_0_1::resqml20__ResqmlPropertyKind__length);

		double prop1Values[2] = { i, i };
		continuousProp->pushBackDoubleHdf5Array3dOfValues(prop1Values, 2, 1, 1, nullptr);

		std::cout << "A new discrete property has been added" << std::endl;

		const size_t secondCount = 10;
		std::cout << "New generated property in " << secondCount << " seconds" << std::endl;
		std::chrono::seconds dura(secondCount);
		std::this_thread::sleep_for(dura);
	}
}

int main(int argc, char **argv)
{
	if (argc < 4) {
		std::cerr << "The command must be : etpServerExample ipAddress port epcFileName" << std::endl;
		std::cerr << "EXAMPLE : ./etpServerExample 127.0.0.1 8080 ../../testingPackageCpp.epc" << std::endl;

		return 1;
	}

	COMMON_NS::EpcDocument epcDoc(argv[3]);
	MyDataObjectRepository repo;
	try {
		std::string resqmlResult = epcDoc.deserializePartiallyInto(repo, COMMON_NS::DataObjectRepository::openingMode::READ_WRITE); // Do not open XML files. Simply rely on the EPC content type and rel files.
		repo.registerDataFeeder(&epcDoc); // Necessary to resolve partial objects
		if (!resqmlResult.empty()) {
			std::cerr << "Warning when deserializing " << resqmlResult << std::endl;
		}
	}
	catch (const std::exception&) {
		std::cerr << "Could not deserialize the EPC document named " << argv[3] << std::endl;
		return 1;
	}

	if (argc > 4) {
		std::thread generatePropertiesThread(generateProperties, repo.getDataObjectByUuid<RESQML2_NS::AbstractRepresentation>("df2103a0-fa3d-11e5-b8d4-0002a5d5c51b"));
		generatePropertiesThread.detach(); // Detach the thread since we don't want it to be a blocking one.
	}

	MyServerInitializationParameters serverInitializationParams(&repo);

	const int threadCount = 2;
	std::cout << "Start listening on " << argv[1] << ":" << argv[2] << " with " << threadCount << " threads..." << std::endl;

#ifdef WITH_ETP_SSL
	if (std::stoi(argv[2]) == 443) {
		ETP_NS::Server etpServer(&serverInitializationParams);

		etpServer.listen(argv[1], std::stoi(argv[2]), threadCount,
			"-----BEGIN CERTIFICATE-----\n"
			"MIIDaDCCAlCgAwIBAgIJAO8vBu8i8exWMA0GCSqGSIb3DQEBCwUAMEkxCzAJBgNV\n"
			"BAYTAlVTMQswCQYDVQQIDAJDQTEtMCsGA1UEBwwkTG9zIEFuZ2VsZXNPPUJlYXN0\n"
			"Q049d3d3LmV4YW1wbGUuY29tMB4XDTE3MDUwMzE4MzkxMloXDTQ0MDkxODE4Mzkx\n"
			"MlowSTELMAkGA1UEBhMCVVMxCzAJBgNVBAgMAkNBMS0wKwYDVQQHDCRMb3MgQW5n\n"
			"ZWxlc089QmVhc3RDTj13d3cuZXhhbXBsZS5jb20wggEiMA0GCSqGSIb3DQEBAQUA\n"
			"A4IBDwAwggEKAoIBAQDJ7BRKFO8fqmsEXw8v9YOVXyrQVsVbjSSGEs4Vzs4cJgcF\n"
			"xqGitbnLIrOgiJpRAPLy5MNcAXE1strVGfdEf7xMYSZ/4wOrxUyVw/Ltgsft8m7b\n"
			"Fu8TsCzO6XrxpnVtWk506YZ7ToTa5UjHfBi2+pWTxbpN12UhiZNUcrRsqTFW+6fO\n"
			"9d7xm5wlaZG8cMdg0cO1bhkz45JSl3wWKIES7t3EfKePZbNlQ5hPy7Pd5JTmdGBp\n"
			"yY8anC8u4LPbmgW0/U31PH0rRVfGcBbZsAoQw5Tc5dnb6N2GEIbq3ehSfdDHGnrv\n"
			"enu2tOK9Qx6GEzXh3sekZkxcgh+NlIxCNxu//Dk9AgMBAAGjUzBRMB0GA1UdDgQW\n"
			"BBTZh0N9Ne1OD7GBGJYz4PNESHuXezAfBgNVHSMEGDAWgBTZh0N9Ne1OD7GBGJYz\n"
			"4PNESHuXezAPBgNVHRMBAf8EBTADAQH/MA0GCSqGSIb3DQEBCwUAA4IBAQCmTJVT\n"
			"LH5Cru1vXtzb3N9dyolcVH82xFVwPewArchgq+CEkajOU9bnzCqvhM4CryBb4cUs\n"
			"gqXWp85hAh55uBOqXb2yyESEleMCJEiVTwm/m26FdONvEGptsiCmF5Gxi0YRtn8N\n"
			"V+KhrQaAyLrLdPYI7TrwAOisq2I1cD0mt+xgwuv/654Rl3IhOMx+fKWKJ9qLAiaE\n"
			"fQyshjlPP9mYVxWOxqctUdQ8UnsUKKGEUcVrA08i1OAnVKlPFjKBvk+r7jpsTPcr\n"
			"9pWXTO9JrYMML7d+XRSZA1n3856OqZDX4403+9FnXCvfcLZLLKTBvwwFgEFGpzjK\n"
			"UEVbkhd5qstF6qWK\n"
			"-----END CERTIFICATE-----\n",
			"-----BEGIN PRIVATE KEY-----\n"
			"MIIEvgIBADANBgkqhkiG9w0BAQEFAASCBKgwggSkAgEAAoIBAQDJ7BRKFO8fqmsE\n"
			"Xw8v9YOVXyrQVsVbjSSGEs4Vzs4cJgcFxqGitbnLIrOgiJpRAPLy5MNcAXE1strV\n"
			"GfdEf7xMYSZ/4wOrxUyVw/Ltgsft8m7bFu8TsCzO6XrxpnVtWk506YZ7ToTa5UjH\n"
			"fBi2+pWTxbpN12UhiZNUcrRsqTFW+6fO9d7xm5wlaZG8cMdg0cO1bhkz45JSl3wW\n"
			"KIES7t3EfKePZbNlQ5hPy7Pd5JTmdGBpyY8anC8u4LPbmgW0/U31PH0rRVfGcBbZ\n"
			"sAoQw5Tc5dnb6N2GEIbq3ehSfdDHGnrvenu2tOK9Qx6GEzXh3sekZkxcgh+NlIxC\n"
			"Nxu//Dk9AgMBAAECggEBAK1gV8uETg4SdfE67f9v/5uyK0DYQH1ro4C7hNiUycTB\n"
			"oiYDd6YOA4m4MiQVJuuGtRR5+IR3eI1zFRMFSJs4UqYChNwqQGys7CVsKpplQOW+\n"
			"1BCqkH2HN/Ix5662Dv3mHJemLCKUON77IJKoq0/xuZ04mc9csykox6grFWB3pjXY\n"
			"OEn9U8pt5KNldWfpfAZ7xu9WfyvthGXlhfwKEetOuHfAQv7FF6s25UIEU6Hmnwp9\n"
			"VmYp2twfMGdztz/gfFjKOGxf92RG+FMSkyAPq/vhyB7oQWxa+vdBn6BSdsfn27Qs\n"
			"bTvXrGe4FYcbuw4WkAKTljZX7TUegkXiwFoSps0jegECgYEA7o5AcRTZVUmmSs8W\n"
			"PUHn89UEuDAMFVk7grG1bg8exLQSpugCykcqXt1WNrqB7x6nB+dbVANWNhSmhgCg\n"
			"VrV941vbx8ketqZ9YInSbGPWIU/tss3r8Yx2Ct3mQpvpGC6iGHzEc/NHJP8Efvh/\n"
			"CcUWmLjLGJYYeP5oNu5cncC3fXUCgYEA2LANATm0A6sFVGe3sSLO9un1brA4zlZE\n"
			"Hjd3KOZnMPt73B426qUOcw5B2wIS8GJsUES0P94pKg83oyzmoUV9vJpJLjHA4qmL\n"
			"CDAd6CjAmE5ea4dFdZwDDS8F9FntJMdPQJA9vq+JaeS+k7ds3+7oiNe+RUIHR1Sz\n"
			"VEAKh3Xw66kCgYB7KO/2Mchesu5qku2tZJhHF4QfP5cNcos511uO3bmJ3ln+16uR\n"
			"GRqz7Vu0V6f7dvzPJM/O2QYqV5D9f9dHzN2YgvU9+QSlUeFK9PyxPv3vJt/WP1//\n"
			"zf+nbpaRbwLxnCnNsKSQJFpnrE166/pSZfFbmZQpNlyeIuJU8czZGQTifQKBgHXe\n"
			"/pQGEZhVNab+bHwdFTxXdDzr+1qyrodJYLaM7uFES9InVXQ6qSuJO+WosSi2QXlA\n"
			"hlSfwwCwGnHXAPYFWSp5Owm34tbpp0mi8wHQ+UNgjhgsE2qwnTBUvgZ3zHpPORtD\n"
			"23KZBkTmO40bIEyIJ1IZGdWO32q79nkEBTY+v/lRAoGBAI1rbouFYPBrTYQ9kcjt\n"
			"1yfu4JF5MvO9JrHQ9tOwkqDmNCWx9xWXbgydsn/eFtuUMULWsG3lNjfst/Esb8ch\n"
			"k5cZd6pdJZa4/vhEwrYYSuEjMCnRb0lUsm7TsHxQrUd6Fi/mUuFU/haC0o0chLq7\n"
			"pVOUFq5mW8p0zbtfHbjkgxyF\n"
			"-----END PRIVATE KEY-----\n",
			"-----BEGIN DH PARAMETERS-----\n"
			"MIIBCAKCAQEArzQc5mpm0Fs8yahDeySj31JZlwEphUdZ9StM2D8+Fo7TMduGtSi+\n"
			"/HRWVwHcTFAgrxVdm+dl474mOUqqaz4MpzIb6+6OVfWHbQJmXPepZKyu4LgUPvY/\n"
			"4q3/iDMjIS0fLOu/bLuObwU5ccZmDgfhmz1GanRlTQOiYRty3FiOATWZBRh6uv4u\n"
			"tff4A9Bm3V9tLx9S6djq31w31Gl7OQhryodW28kc16t9TvO1BzcV3HjRPwpe701X\n"
			"oEEZdnZWANkkpR/m/pfgdmGPU66S2sXMHgsliViQWpDCYeehrvFRHEdR9NV+XJfC\n"
			"QMUk26jPTIVTLfXmmwU0u8vUkpR7LQKkwwIBAg==\n"
			"-----END DH PARAMETERS-----\n");
	}
	else {
#endif
		ETP_NS::Server etpServer(&serverInitializationParams);
		etpServer.listen(argv[1], std::stoi(argv[2]), threadCount);
#ifdef WITH_ETP_SSL
	}
#endif

	epcDoc.close();

#ifdef _WIN32
	_CrtDumpMemoryLeaks();
#endif

	return 0;
}
