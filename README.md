
# Prepare your build environment

- Create a folder called fesapiEnv.
- In this folder create the three following folders
	- build
	- fesapi (Git clone this repository into this folder "fesapi". You should then have a path fesapiEnv/fesapi/src)
	- dependencies

The build system uses cmake. The minimal version of the build system is (no 32bits support):

* cmake (vesion >= 3.12)
* VS 2015
* g++ 4.8.5
* clang 5

The following libraries are required:

* [HDF5](https://support.hdfgroup.org/ftp/HDF5/releases/hdf5-1.8) (version >= 1.8.18 & < 1.10.*)
* [Minizip](https://github.com/F2I-Consulting/Minizip)  Version 1.1 is needed : it is the official version included in current zlib distribution https://www.zlib.net/ (look into "contrib" folder). You can directly install minizip development package on most of Linux distributions (https://packages.ubuntu.com/xenial/libminizip-dev). On Windows (or older Linux distributions), you can copy the CMakeLists.txt file from fesapi/cmake/minizip to the zlib minizip directory to help you to build minizip (we also provide a copy of minizip 1.1 with cmake files on github : https://github.com/F2I-Consulting/Minizip). It is also highly recommended to link minizip to the same zlib library than the one associated to your HDF5 library.
* [UUID](https://www.kernel.org/pub/linux/utils/util-linux/) only unix systems (linux, macos)

If the dependencies are installed in non-standard locations, use the following
cmake-variables to inform cmake where to find them:

* HDF5_ROOT
* CMAKE_PREFIX_PATH

The standard cmake variables can be used to configure HDF5. For example to do a static build with HDF5, set the variable HDF5_USE_STATIC_LIBRARIES=ON.

You can use system installed libraries.
If you want to install these third party libraries by yourself, we recommand you to install them respectively into
- fesapiEnv/dependencies/hdf5-particularVersion
- fesapiEnv/dependencies/minizip-particularVersion
- fesapiEnv/dependencies/uuid-particularVersion (or in system directory using : sudo apt-get install uuid-dev)

# Configure the build

We also recommend using cmake-gui (already included in the bin folder of the binary releases of cmake) which provides a graphical user interface on top of cmake.

- yourPath/fesapiEnv/fesapi defines where is the source code folder
- yourPath/fesapiEnv/build/theNameYouWant defines where to build the binaries
- Click on "Configure" button and select your favorite compiler : it will raise several errors.
- Set the paths of your third party libraries in the CMAKE_PREFIX_PATH variable except for HDF5 wich uses HDF5_ROOT.
- Click again on "Configure" button. You should no more have errors so you can now click on "Generate" button.
![alt text](./cmake/cmake.JPG)
- You can now build your solution with your favorite compiler (and linker) using the generated solution in yourPath/fesapiEnv/build/theNameYouWant
- OPTIONALLY, you can also set the variables WITH_DOTNET_WRAPPING or WITH_JAVA_WRAPPING to true if you want to also generate wrappers on top of fesapi for these two other programming languages. Don't forget to click again on "Configure" button once you changed the value of these two variables.
	- You will then have to also provide the path to the SWIG executable http://swig.org/download.html in the SWIG_EXECUTABLE variable (and click again on "Configure" button)
	- FOR Java and only for JAVA, you'll also have to provide various path to some java executables. Still only for Java, it is highly recommended to lower the optimization level of the C++ compilation by setting O1 instead of O2 in the variables called CMAKE_CXX_FLAGS_RELEASE and CMAKE_CXX_FLAGS_RELWITHDEBINFO
	- you will find the wrappers in fesapi/java/src or fesapi/cs/src (fesapi/cs also contains a VS2013 project for the wrappers)
- OPTIONALLY, for ETP1.2 support, you can also set the variable WITH_ETP which is documented [here](https://github.com/F2I-Consulting/fesapi/tree/etp/src/etp)

Remark : you can choose where fesapi will be installed (using "make install" on Linux or by generating the "INSTALL" project on Visual Studio) by setting the cmake variable called CMAKE_INSTALL_PREFIX

# Credits
This software was developed with the gSOAP toolkit from [Genivia Inc](http://genivia.com/)
