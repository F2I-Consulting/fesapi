Enable CMake boolean variable SWIG_PYTHON_BUILTIN if you want more performance : read [SWIG documentation](http://swig.org/Doc4.0/SWIGDocumentation.html#Python_nn28) for more information about this "builtin" parameter. The main drawback of using such a parameter is that it will be harder/impossible for your Python IDE to enable autocompletion for your FESAPI python extension. The recommendation is to use SWIG_PYTHON_BUILTIN only in production.

Please disable the SWIG_LINKED_TO_RELEASE cmake variable if you build FESAPI in Debug mode.