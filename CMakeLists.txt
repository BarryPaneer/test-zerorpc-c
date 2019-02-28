CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT(test-c-rpc)
SET(test-c-rpc_VERSION_MAJOR 1)
SET(test-c-rpc_VERSION_MINOR 0)
SET(CMAKE_BUILD_TYPE "Debug")
SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb")
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")


find_package(Threads REQUIRED)

INCLUDE_DIRECTORIES(
	/usr/include
	/usr/local/include
	/usr/local/include/msgpack
)
LINK_DIRECTORIES(
	/usr/lib64
	/usr/local/lib
)

AUX_SOURCE_DIRECTORY(. DIR_SRCS)


ADD_EXECUTABLE(test-c-rpc ${DIR_SRCS})
TARGET_LINK_LIBRARIES(test-c-rpc libzmq.5.dylib)

