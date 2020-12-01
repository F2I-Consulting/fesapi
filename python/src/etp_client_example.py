"""
You must run the following command (only once) in order to create the FESAPI Python extension.
Run it from fesapi/swig working directory : python3 setup.py build_ext --build-lib ../python/src

Be sure that the FesapiCpp library and its dependencies are accessible
i.e. are in the (LD_LIBRARY_)PATH meaning for example on Windows that
they are in the same directory than this file and the generated pyd file.
"""

import sys

import fesapi

sys.path.append(r'./etp/')
import my_own_client_core_handlers
import my_own_discovery_protocol_handlers
import my_own_store_protocol_handlers

session = fesapi.createClientSession("127.0.0.1", "8080", "/", "")
session.setCoreProtocolHandlers(my_own_client_core_handlers.MyOwnClientCoreHandlers(session))
session.setDiscoveryProtocolHandlers(my_own_discovery_protocol_handlers.MyOwnDiscoveryProtocolHandlers(session))
session.setStoreProtocolHandlers(my_own_store_protocol_handlers.MyOwnStoreProtocolHandlers(session))
session.run()
print("FINISHED")
