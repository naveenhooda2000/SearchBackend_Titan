cmake_minimum_required(VERSION 3.5)
project(response-aggregator)

MESSAGE(${CMAKE_MODULE_PATH})

include_directories ("${PROJECT_SOURCE_DIR}/include")

add_executable(AggregatorServer src/AggregatorServer.cpp src/AggregatorHandler.cpp)
target_link_libraries(AggregatorServer proxygenhttpserver folly glog gflags pthread)
