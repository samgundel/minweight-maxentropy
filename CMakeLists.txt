CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

PROJECT(n1graph)

###################
## Configuration ##
###################
SET(CMAKE_BUILD_TYPE Debug)
SET(warnings "-Wall -Wextra -Werror")
SET(SRC "${CMAKE_SOURCE_DIR}/src")
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")
FILE(COPY "${CMAKE_SOURCE_DIR}/scripts/visualize.py" DESTINATION "${CMAKE_BINARY_DIR}")

############################
## Verifying the Compiler ##
############################
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if(COMPILER_SUPPORTS_CXX11)
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
elseif(COMPILER_SUPPORTS_CXX0X)
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
else()
    MESSAGE(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()

#####################
## Our source code ##
#####################
ADD_SUBDIRECTORY(${SRC})
