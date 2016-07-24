
#  Copyright (c) 2014, Facebook, Inc.
#  All rights reserved.
#
#  This source code is licensed under the BSD-style license found in the
#  LICENSE file in the root directory of this source tree. An additional grant
#  of patent rights can be found in the PATENTS file in the same directory.
cmake_minimum_required(VERSION 3.5)
project(server-engine)

MESSAGE(${CMAKE_MODULE_PATH})

include_directories ("${PROJECT_SOURCE_DIR}/include")

add_executable(SearchServer src/SearchServer.cpp src/SearchHandler.cpp)
target_link_libraries(SearchServer proxygenhttpserver folly glog gflags pthread)
