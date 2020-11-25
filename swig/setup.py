from distutils.core import setup, Extension

fesapi_module = Extension('_fesapi',
	sources=['swigGeneratedPythonWrapper.cpp'],
	library_dirs=['../../build/v2.0.0.0/fesapiCpp-cs-staticHdf/install/lib'],
	libraries=['FesapiCpp.2.0.0.0',],
)

setup (name = 'fesapi',
	version = '2.0',
	author      = "F2I-CONSULTING",
	description = """An API for the Energistics standards""",
	ext_modules = [fesapi_module],
	py_modules = ["fesapi"],
)
