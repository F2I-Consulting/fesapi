
set(FESAPI_FRONT_MATTER_FILE ${CMAKE_SOURCE_DIR}/webassembly/front-matter.js)

set(FESAPI_SRC_DIR ${CMAKE_SOURCE_DIR}/src/)


# Build Release by default
set(CMAKE_BUILD_TYPE Release CACHE STRING "Build Type")

# Default is 128*1024*1024 = 128MB
set(INITIAL_MEMORY 134217728 CACHE STRING "Initial Memory")

# Enable for resizable heap, with some amount of slowness
set(ALLOW_MEMORY_GROWTH 1 CACHE STRING "Allow Memory Growth")

# Allows more functions to be added to the table at runtime (This is
# necessary for dynamic linking)
set(ALLOW_TABLE_GROWTH 0 CACHE STRING "Allow Table Growth")

set(EMCC_ARGS
  --bind   
  # Specify a file whose contents are added before the emitted code and optimized together with it
  --pre-js ${FESAPI_FRONT_MATTER_FILE}  
  # Highest level of optimization (code size reduction)
  -Oz
  # Whether to use compile code to WebAssembly
  -s WASM=1
  #
  -fwasm-exceptions
  #
  -s ALLOW_MEMORY_GROWTH=${ALLOW_MEMORY_GROWTH}    
  #
  -s ALLOW_TABLE_GROWTH=${ALLOW_TABLE_GROWTH}    
  # Include the necessary export object expected by the import statement
  -s EXPORT_ES6=1 # AFAIK, this enables MODULARIZE implicitly
  # The code is emited wrapped in a function that returns a promise.
  -s MODULARIZE=1
  # Use the ES6 Module relative import feature 'import.meta.url'
  # to auto-detect WASM Module path.
  # It might not be supported on old browsers / toolchains. This setting
  # may not be disabled when Node.js is targeted (-sENVIRONMENT=*node*).
  #-s USE_ES6_IMPORT_META=0
  # Global variable to export the module as for environments without a standardized module loading system
  -s EXPORT_NAME="FesapiModule"
  
  # The runtime is not quit when main() completes (smaller code)
  -s NO_EXIT_RUNTIME=1  
  # The initial amount of memory to use
  -s INITIAL_MEMORY=${INITIAL_MEMORY}
  #
  -s USE_ZLIB=1
  #
  -s USE_BOOST_HEADERS=1
  #
  -s FORCE_FILESYSTEM=1
  #
  -s EXPORTED_RUNTIME_METHODS=\"['FS', 'AsciiToString', 'UTF8ToString']\"
  # Make the exception message printing function, 'getExceptionMessage' available
  # in the JS library
  -s EXPORT_EXCEPTION_HANDLING_HELPERS=1

  # WebAssembly integration with JavaScript BigInt
  -s WASM_BIGINT
  #  Whether to ignore implicit traps when optimizing in binaryen
  -s BINARYEN_IGNORE_IMPLICIT_TRAPS=1
  # this file can be linked with others, either as a shared library or as the main file that calls a shared library
  -s LINKABLE=0
  #
  # DEBUG 
  #  Whether we should add runtime assertions
  -s ASSERTIONS=2
  # Check each write to the heap
  -s SAFE_HEAP=1
  # Highest level of preserving debug info
  -g3
  # build in libcxxabi's full c++ demangling code, to allow stackTrace() to emit fully proper demangled c++ names
  -s DEMANGLE_SUPPORT=1
  #  Disables generating code to actually catch Emscripten exceptions
#   -s DISABLE_EXCEPTION_CATCHING=0
  # Print out exceptions in emscriptened code
  -s EXCEPTION_DEBUG=1
)

set(EMCC_WEB_ARGS 
  ${EMCC_ARGS}
  # Specify which runtime environments the JS output will be capable of running in
  -s ENVIRONMENT=web
)

set(EMCC_NODE_ARGS 
  ${EMCC_ARGS}
  # Specify which runtime environments the JS output will be capable of running in
  -s ENVIRONMENT=node
  # The File System API will directly use Node.js API
  -s NODERAWFS=1
)

#
# ESM 6 module
#
add_executable(fesapi-wasm ${CMAKE_SOURCE_DIR}/webassembly/src/wrapper.cpp)

add_dependencies(fesapi-wasm ${CPP_LIBRARY_NAME})

target_include_directories(fesapi-wasm PRIVATE 
      $<BUILD_INTERFACE:${FESAPI_SRC_DIR}>
      ${HDF5_INCLUDE_DIRS}
      ${MINIZIP_INCLUDE_DIR}
)

target_link_libraries(fesapi-wasm PRIVATE
      $<TARGET_FILE:${CPP_LIBRARY_NAME}>
      ${HDF5_LIBRARIES}
      ${MINIZIP_LIBRARY_RELEASE}
)

string(REPLACE ";" " " EMCC_WEB_ARGS "${EMCC_WEB_ARGS}")

set_target_properties(fesapi-wasm PROPERTIES
    LINK_FLAGS "${EMCC_WEB_ARGS}"
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/webassembly/dist/esm
    RUNTIME_OUTPUT_NAME fesapi
    SUFFIX ".mjs"
)


#
# Node module
#
add_executable(fesapi-wasm-node ${CMAKE_SOURCE_DIR}/webassembly/src/wrapper.cpp)

add_dependencies(fesapi-wasm-node ${CPP_LIBRARY_NAME})

target_include_directories(fesapi-wasm-node PRIVATE 
      $<BUILD_INTERFACE:${FESAPI_SRC_DIR}>
      ${HDF5_INCLUDE_DIRS}
      ${MINIZIP_INCLUDE_DIR}
)

target_link_libraries(fesapi-wasm-node PRIVATE
      $<TARGET_FILE:${CPP_LIBRARY_NAME}>
      ${HDF5_LIBRARIES}
      ${MINIZIP_LIBRARY_RELEASE}
)

string(REPLACE ";" " " EMCC_NODE_ARGS "${EMCC_NODE_ARGS}")

set_target_properties(fesapi-wasm-node PROPERTIES
    LINK_FLAGS "${EMCC_NODE_ARGS}"
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/webassembly/dist/node
    RUNTIME_OUTPUT_NAME fesapi
    SUFFIX ".mjs"
)