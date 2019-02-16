project( config )
cmake_minimum_required( VERSION 3.1 )
set( CMAKE_CXX_STANDARD 14 )
set( CMAKE_INCLUDE_CURRENT_DIR ON )
set( CMAKE_AUTOMOC ON )
set( CMAKE_BUILD_TYPE Release )
add_definitions ( -Wall )
set ( LIBRARY_OUTPUT_PATH ../../lib )
set ( config_HDRS
	../../include/comet/config.h
	)

set ( config_SRCS
	../../src/comet/config.cpp
	)
include_directories(../../include)
add_library ( config SHARED ${config_SRCS} ${UIS} ${RSCS} ${TRS} ${MOCS} )
target_link_libraries ( config )
