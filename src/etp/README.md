# Prepare the dependencies
Download (build and install if necessary) third party libraries:
- BOOST : All versions containing BEAST (starting from version 1.66) should be ok. https://www.boost.org/doc/libs/1_68_0/libs/beast/doc/html/index.html
- AVRO : https://avro.apache.org/releases.html#Download (build it with the above boost library)

We advise you to install these third party libraries respectively into
- fesapiEnv/dependencies/boost-particularVersion
- fesapiEnv/dependencies/avro-particularVersion
# Configure the build
 - Enable the CMAKE variable called WITH_ETP
 - give real path and files to the following cmake variables:
	- BOOST
		- BOOST_INCLUDE_DIR : where the "boost" directory containing all BOOST headers is located
		- BOOST_LIBRARY_RELEASE : the BOOST system library you want to link to
	- MINIZIP
		- AVRO_INCLUDE_DIR : where the "avro" directory containing all AVRO headers is located
		- AVRO_LIBRARY_RELEASE : the AVRO system library you want to link to
