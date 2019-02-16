project( socket )
cmake_minimum_required( VERSION 3.1 )
set( CMAKE_CXX_STANDARD 14 )
set( CMAKE_INCLUDE_CURRENT_DIR ON )
set( CMAKE_AUTOMOC ON )
set( CMAKE_BUILD_TYPE Release )
add_definitions ( -Wall )
set ( LIBRARY_OUTPUT_PATH ../../lib )
set ( socket_HDRS
	../../include/comet/socket.h
	)

set ( socket_SRCS
	../../src/comet/socket.cpp
	)
include_directories(../../include)
add_library ( socket SHARED ${socket_SRCS} ${UIS} ${RSCS} ${TRS} ${MOCS} )
target_link_libraries ( socket )
