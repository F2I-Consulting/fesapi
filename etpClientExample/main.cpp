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
#include "etp/ClientSessionLaunchers.h"
#include "etp/EtpHdfProxy.h"
#include "etp/HttpClientSession.h"
#ifdef WITH_ETP_SSL
#include "etp/ssl/HttpsClientSession.h"
#endif

#include "MyOwnCoreProtocolHandlers.h"
#include "MyOwnDiscoveryProtocolHandlers.h"
#include "MyOwnStoreProtocolHandlers.h"
#include "etp/ProtocolHandlers/DataArrayHandlers.h"
#include "etp/ProtocolHandlers/StoreNotificationHandlers.h"

using namespace ETP_NS;

void setProtocolHandlers(std::shared_ptr<ETP_NS::AbstractSession> session, COMMON_NS::DataObjectRepository* repo) {
	session->setCoreProtocolHandlers(std::make_shared<MyOwnCoreProtocolHandlers>(session.get(), repo));
	session->setDiscoveryProtocolHandlers(std::make_shared<MyOwnDiscoveryProtocolHandlers>(session.get(), repo));
	session->setStoreProtocolHandlers(std::make_shared<MyOwnStoreProtocolHandlers>(session.get(), repo));
	session->setDataArrayProtocolHandlers(std::make_shared<ETP_NS::DataArrayHandlers>(session.get()));
	session->setStoreNotificationProtocolHandlers(std::make_shared<ETP_NS::StoreNotificationHandlers>(session.get()));
}

int main(int argc, char **argv)
{
	if (argc < 3) {
		std::cerr << "The command must be : etpClientExample ipAddress port [target]" << std::endl;
		return 1;
	}

	if (argc == 4 && (argv[3][0] != '/')) {
		std::cerr << "Please put a slash at the start of the target " << argv[3] << std::endl;
		return 1;
	}

	std::cout << "Give your authorization to pass to the server (or hit enter if no authorization)" << std::endl;
	std::string authorization;
	std::getline(std::cin, authorization);
	
	// Ask for Server capabilites
	boost::asio::io_context ioc;
#ifdef WITH_ETP_SSL
	const std::string additionalCertificates = "-----BEGIN CERTIFICATE-----\n"
		"MIIDxTCCAq2gAwIBAgIQAqxcJmoLQJuPC3nyrkYldzANBgkqhkiG9w0BAQUFADBs\n"
		"MQswCQYDVQQGEwJVUzEVMBMGA1UEChMMRGlnaUNlcnQgSW5jMRkwFwYDVQQLExB3\n"
		"d3cuZGlnaWNlcnQuY29tMSswKQYDVQQDEyJEaWdpQ2VydCBIaWdoIEFzc3VyYW5j\n"
		"ZSBFViBSb290IENBMB4XDTA2MTExMDAwMDAwMFoXDTMxMTExMDAwMDAwMFowbDEL\n"
		"MAkGA1UEBhMCVVMxFTATBgNVBAoTDERpZ2lDZXJ0IEluYzEZMBcGA1UECxMQd3d3\n"
		"LmRpZ2ljZXJ0LmNvbTErMCkGA1UEAxMiRGlnaUNlcnQgSGlnaCBBc3N1cmFuY2Ug\n"
		"RVYgUm9vdCBDQTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBAMbM5XPm\n"
		"+9S75S0tMqbf5YE/yc0lSbZxKsPVlDRnogocsF9ppkCxxLeyj9CYpKlBWTrT3JTW\n"
		"PNt0OKRKzE0lgvdKpVMSOO7zSW1xkX5jtqumX8OkhPhPYlG++MXs2ziS4wblCJEM\n"
		"xChBVfvLWokVfnHoNb9Ncgk9vjo4UFt3MRuNs8ckRZqnrG0AFFoEt7oT61EKmEFB\n"
		"Ik5lYYeBQVCmeVyJ3hlKV9Uu5l0cUyx+mM0aBhakaHPQNAQTXKFx01p8VdteZOE3\n"
		"hzBWBOURtCmAEvF5OYiiAhF8J2a3iLd48soKqDirCmTCv2ZdlYTBoSUeh10aUAsg\n"
		"EsxBu24LUTi4S8sCAwEAAaNjMGEwDgYDVR0PAQH/BAQDAgGGMA8GA1UdEwEB/wQF\n"
		"MAMBAf8wHQYDVR0OBBYEFLE+w2kD+L9HAdSYJhoIAu9jZCvDMB8GA1UdIwQYMBaA\n"
		"FLE+w2kD+L9HAdSYJhoIAu9jZCvDMA0GCSqGSIb3DQEBBQUAA4IBAQAcGgaX3Nec\n"
		"nzyIZgYIVyHbIUf4KmeqvxgydkAQV8GK83rZEWWONfqe/EW1ntlMMUu4kehDLI6z\n"
		"eM7b41N5cdblIZQB2lWHmiRk9opmzN6cN82oNLFpmyPInngiK3BD41VHMWEZ71jF\n"
		"hS9OMPagMRYjyOfiZRYzy78aG6A9+MpeizGLYAiJLQwGXFK3xPkKmNEVX58Svnw2\n"
		"Yzi9RKR/5CYrCsSXaQ3pjOLAEFe4yHYSkVXySGnYvCoCWw9E1CAx2/S6cCZdkGCe\n"
		"vEsXCS+0yx5DaMkHJ8HSXPfqIbloEpw8nL+e/IBcm2PN7EeqJSdnoDfzAIJ9VNep\n"
		"+OkuE6N36B9K\n"
		"-----END CERTIFICATE-----\n"
		"-----BEGIN CERTIFICATE-----\n"
		"MIIDVDCCAjygAwIBAgIDAjRWMA0GCSqGSIb3DQEBBQUAMEIxCzAJBgNVBAYTAlVT\n"
		"MRYwFAYDVQQKEw1HZW9UcnVzdCBJbmMuMRswGQYDVQQDExJHZW9UcnVzdCBHbG9i\n"
		"YWwgQ0EwHhcNMDIwNTIxMDQwMDAwWhcNMjIwNTIxMDQwMDAwWjBCMQswCQYDVQQG\n"
		"EwJVUzEWMBQGA1UEChMNR2VvVHJ1c3QgSW5jLjEbMBkGA1UEAxMSR2VvVHJ1c3Qg\n"
		"R2xvYmFsIENBMIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEA2swYYzD9\n"
		"9BcjGlZ+W988bDjkcbd4kdS8odhM+KhDtgPpTSEHCIjaWC9mOSm9BXiLnTjoBbdq\n"
		"fnGk5sRgprDvgOSJKA+eJdbtg/OtppHHmMlCGDUUna2YRpIuT8rxh0PBFpVXLVDv\n"
		"iS2Aelet8u5fa9IAjbkU+BQVNdnARqN7csiRv8lVK83Qlz6cJmTM386DGXHKTubU\n"
		"1XupGc1V3sjs0l44U+VcT4wt/lAjNvxm5suOpDkZALeVAjmRCw7+OC7RHQWa9k0+\n"
		"bw8HHa8sHo9gOeL6NlMTOdReJivbPagUvTLrGAMoUgRx5aszPeE4uwc2hGKceeoW\n"
		"MPRfwCvocWvk+QIDAQABo1MwUTAPBgNVHRMBAf8EBTADAQH/MB0GA1UdDgQWBBTA\n"
		"ephojYn7qwVkDBF9qn1luMrMTjAfBgNVHSMEGDAWgBTAephojYn7qwVkDBF9qn1l\n"
		"uMrMTjANBgkqhkiG9w0BAQUFAAOCAQEANeMpauUvXVSOKVCUn5kaFOSPeCpilKIn\n"
		"Z57QzxpeR+nBsqTP3UEaBU6bS+5Kb1VSsyShNwrrZHYqLizz/Tt1kL/6cdjHPTfS\n"
		"tQWVYrmm3ok9Nns4d0iXrKYgjy6myQzCsplFAMfOEVEiIuCl6rYVSAlk6l5PdPcF\n"
		"PseKUgzbFbS9bZvlxrFUaKnjaZC2mqUPuLk/IH2uSrW4nOQdtqvmlKXBx4Ot2/Un\n"
		"hw4EbNX/3aBd7YdStysVAq45pmp06drE57xNNB6pXE0zX5IJL4hmXXeXxx12E6nV\n"
		"5fEWCRE11azbJHFwLJhWC9kXtNHjUStedejV0NxPNO3CBWaAocvmMw==\n"
		"-----END CERTIFICATE-----\n";

	if (std::stoi(argv[2]) == 443) {
		ssl::context ctx{ ssl::context::sslv23_client };
		boost::system::error_code ec;
		ctx.add_certificate_authority(
			boost::asio::buffer(additionalCertificates.data(), additionalCertificates.size()), ec);
		if (ec) {
			std::cerr << "Cannot add certificates : " << additionalCertificates << std::endl;
			return -1;
		}

		auto httpsClientSession = std::make_shared<HttpsClientSession>(ioc, ctx);
		std::string etpServerCapTarget = argc >= 4 ? argv[3] : "/";
		if (etpServerCapTarget[etpServerCapTarget.size() - 1] != '/') {
			etpServerCapTarget += '/';
		}
		etpServerCapTarget += ".well-known/etp-server-capabilities?GetVersion=etp12.energistics.org";
		std::cout << "Requesting " << etpServerCapTarget << " to " << argv[1] << " on port " << argv[2] << std::endl;
		httpsClientSession->run(argv[1], argv[2], etpServerCapTarget.c_str(), 11, authorization);
		// Run the I/O service. The call will return when the get operation is complete.
		ioc.run();
		std::cout << httpsClientSession->getResponse() << std::endl;
	}
	else {
#endif
		auto httpClientSession = std::make_shared<HttpClientSession>(ioc);
		std::string etpServerCapTarget = argc >= 4 ? argv[3] : "/";
		if (etpServerCapTarget[etpServerCapTarget.size() - 1] != '/') {
			etpServerCapTarget += '/';
		}
		etpServerCapTarget += ".well-known/etp-server-capabilities?GetVersion=etp12.energistics.org";
		std::cout << "Requesting " << etpServerCapTarget << " to " << argv[1] << " on port " << argv[2] << std::endl;
		httpClientSession->run(argv[1], argv[2], etpServerCapTarget.c_str(), 11, authorization);
		// Run the I/O service. The call will return when the get operation is complete.
		ioc.run();
		std::cout << httpClientSession->getResponse() << std::endl;
#ifdef WITH_ETP_SSL
	}
#endif

	
	COMMON_NS::DataObjectRepository repo;
	repo.setHdfProxyFactory(new EtpHdfProxyFactory());

	bool successfulConnection = false;
#ifdef WITH_ETP_SSL
	if (std::stoi(argv[2]) == 443) {
		auto wssSession = ClientSessionLaunchers::createWssClientSession(argv[1], argv[2], argc < 4 ? "/" : argv[3], authorization,
			additionalCertificates);
		setProtocolHandlers(wssSession, &repo);
		successfulConnection = wssSession->run();
	}
	else {
#endif
		auto session = ClientSessionLaunchers::createWsClientSession(argv[1], argv[2], argc < 4 ? "/" : argv[3], authorization);
		setProtocolHandlers(session, &repo);
		successfulConnection = session->run();
#ifdef WITH_ETP_SSL
	}
#endif
	
	if (!successfulConnection) {
		std::cout << "Could not connect to the server " << argv[1] << " " << argv[2] << std::endl;
	}

#ifdef _WIN32
	_CrtDumpMemoryLeaks();
#endif
	
	return 0;
}
