# Copyright 2025 Holepunch Inc
# 
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
# 
#     http://www.apache.org/licenses/LICENSE-2.0
# 
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
# Downloaded on 2026-03-16 from https://github.com/holepunchto/cmake-harden/blob/main/cmake-harden.cmake
# Changelog
# 2026-03-16
# add -Wextra
# add -Wsign-conversion
# add -Wbidi-chars=any
# add -U_FORTIFY_SOURCE
# add -D_FORTIFY_SOURCE=3
# add -D_GLIBCXX_ASSERTIONS
# add -fcf-protection=full
# add -mbranch-protection=standard on aarch64|arm64 architecture
# add -Wl,-z,nodlopen as a comment since we need dlopen for SWIG
# add -Wl,--as-needed
# add -Wl,--no-copy-dt-needed-entries
# add fexceptions
# add fhardened
# rename GCC compiler to GNU compiler to apply to gcc and g++
# Check Linker Flag and use LINKER: prefix

cmake_minimum_required(VERSION 3.19)

include_guard()

include(CheckCompilerFlag)
include(CheckLinkerFlag)

# https://best.openssf.org/Compiler-Hardening-Guides/Compiler-Options-Hardening-Guide-for-C-and-C++.html

macro(add_hardened_compiler_flags)
  foreach(flag ${ARGV})
    check_compiler_flag(${lang} ${flag} supports_${flag})

    if(supports_${flag})
      target_compile_options(${target} PRIVATE ${flag})
    endif()
  endforeach()
endmacro()

macro(add_hardened_linker_flags)
  foreach(flag ${ARGV})
    check_linker_flag(${lang} LINKER:${flag} supports_${flag})
  
    if(supports_${flag})
      target_link_options(${target} PRIVATE LINKER:${flag})
    endif()
  endforeach()
endmacro()

macro(harden_posix)
  add_hardened_compiler_flags(
    -Wall
    -Wextra
    -Wformat
    -Wformat=2
    -Wconversion
    -Wsign-conversion
    -Wimplicit-fallthrough
	-Wbidi-chars=any
    -Werror=format-security
    -Werror=implicit
    -Werror=incompatible-pointer-types
    -Werror=int-conversion
	-U_FORTIFY_SOURCE
	-D_FORTIFY_SOURCE=3
	-D_GLIBCXX_ASSERTIONS
    -fstrict-flex-arrays=3
	-fcf-protection=full
    -fno-delete-null-pointer-checks
    -fno-strict-overflow
    -fno-strict-aliasing
    -ftrivial-auto-var-init=zero
	-fexceptions
	-fhardened
  )
 
if(CMAKE_SYSTEM_PROCESSOR MATCHES "aarch64|arm64")
  add_hardened_compiler_flags( 
    -mbranch-protection=standard
  )
endif()

  # The SHARED and MODULE library targets have by default position independent code enabled : https://cmake.org/cmake/help/latest/variable/CMAKE_POSITION_INDEPENDENT_CODE.html
  add_hardened_linker_flags(
# dlopen is needed for JAVA and Python swig port.
#   -z,nodlopen
    -z,noexecstack
    -z,relro
    -z,now
    --as-needed
    --no-copy-dt-needed-entries
  )

  if(runtime)
    add_hardened_compiler_flags(
      -fstack-clash-protection
      -fstack-protector-strong
    )
  endif()
endmacro()

macro(harden_clang)
  harden_posix()
endmacro()

macro(harden_gnu)
  harden_posix()

  add_hardened_compiler_flags(
    -Wtrampolines
  )
endmacro()

macro(harden_msvc)
  message(WARNING "Compiler hardening is not yet supported for MSVC")
endmacro()

function(harden target)
  set(option_keywords
    C
    CXX
    RUNTIME
  )

  cmake_parse_arguments(
    PARSE_ARGV 1 ARGV "${option_keywords}" "" ""
  )

  set(runtime ${ARGV_RUNTIME})

  if(ARGV_CXX)
    set(lang CXX)
  else()
    set(lang C)
  endif()

  set(compiler ${CMAKE_${lang}_COMPILER_ID})

  if(compiler MATCHES "Clang")
    harden_clang()
  elseif(compiler MATCHES "GNU")
    harden_gnu()
  elseif(compiler MATCHES "MSVC")
    harden_msvc()
  endif()
endfunction()
