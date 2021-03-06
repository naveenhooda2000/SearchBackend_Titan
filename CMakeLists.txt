
#  Copyright (c) 2014, Facebook, Inc.
#  All rights reserved.
#
#  This source code is licensed under the BSD-style license found in the
#  LICENSE file in the root directory of this source tree. An additional grant
#  of patent rights can be found in the PATENTS file in the same directory.
cmake_minimum_required(VERSION 3.5)
project(SearchBackend_Titan)

set(CMAKE_CXX_FLAGS "-std=c++1y -fPIC")

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake_config/)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

find_package(Folly REQUIRED)
find_package(Boost REQUIRED COMPONENTS system thread filesystem)
find_package(OpenSSL REQUIRED)
find_package(Threads REQUIRED)
find_library(GLOG_LIBRARY_PATH glog)
find_library(GFLAGS_LIBRARY_PATH gflags)
find_library(Wangle REQUIRED)
find_library(Proxygen REQUIRED)

add_subdirectory(search-common)
add_subdirectory(query-rewrite-engine)
add_subdirectory(document-ranking)
add_subdirectory(server-engine)
add_subdirectory(response-aggregator)
