#############################
## Include the source root ##
#############################
INCLUDE_DIRECTORIES(${SRC})

##################
## Dependencies ##
##################

# GFlags
FIND_PACKAGE( GFlags REQUIRED )
INCLUDE_DIRECTORIES(${GFLAGS_INCLUDE_DIRS})

# GLog
FIND_PACKAGE( Glog REQUIRED )
INCLUDE_DIRECTORIES(${GLOG_INCLUDE_DIRS})

# GTest
enable_testing()
include_directories(
  ${gtest_SOURCE_DIR}/include
  ${gtest_SOURCE_DIR})

# OpenMP  
FIND_PACKAGE(OpenMP)
if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
endif()
  
  
########################################
## The libraries built in this module ##
########################################
ADD_LIBRARY(n1graph SHARED 	adjacency_graph.cpp
                            degree.cpp
                            matching.cpp
							matrix.cpp
							n1graph.cpp
							text_writer.cpp  
							vector.cpp)

TARGET_LINK_LIBRARIES(n1graph
                      ${GLOG_LIBRARIES})

##########################################
## The Executables built in this module ##
##########################################

# -- MaxEntropyMinWeight -- #

ADD_EXECUTABLE(n1graph_demo  	
               main.cpp)
               
TARGET_LINK_LIBRARIES(n1graph_demo 
                      n1graph 
                      ${GFLAGS_LIBRARIES}
                      ${GLOG_LIBRARIES})

