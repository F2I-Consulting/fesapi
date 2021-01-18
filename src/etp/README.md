# Prepare the dependencies
Download (build and install if necessary) third party libraries:
- BOOST : All versions from version 1.66 should be ok but you may experience some [min/max build issues](https://github.com/boostorg/beast/issues/1980) using version 1.72 or 1.73.
- AVRO : https://avro.apache.org/releases.html#Download (starting from version 1.9.0, build it with the above boost library)

We advise you to install these third party libraries respectively into
- fesapiEnv/dependencies/boost-particularVersion
- fesapiEnv/dependencies/avro-particularVersion
# Configure the build
 - Enable the CMAKE variable called WITH_ETP
 - give real path and files to the following cmake variables:
	- BOOST
		- Boost_INCLUDE_DIR : the directory where you can find the directory named "boost" which contain all BOOST headers
	- MINIZIP
		- AVRO_INCLUDE_DIR : where the "avro" directory containing all AVRO headers is located
		- AVRO_LIBRARY_RELEASE : the AVRO system library you want to link to
