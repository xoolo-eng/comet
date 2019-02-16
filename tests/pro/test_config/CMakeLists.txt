cmake_minimum_required( VERSION 3.1 )
set( CMAKE_CXX_STANDARD 14 )
set( CMAKE_INCLUDE_CURRENT_DIR ON )
set( CMAKE_AUTOMOC ON )
set( CMAKE_BUILD_TYPE Release )
add_definitions ( -Wall )
set ( EXECUTABLE_OUTPUT_PATH bin )
set ( test_config_HDRS

	)

set ( test_config_SRCS
	../../src/test_config.cpp
	)
include_directories(../../../include)
add_library(socket SHARED IMPORTED)
set_property(TARGET socket PROPERTY IMPORTED_LOCATION "../../../lib/libsocket.so")
add_executable ( test_config ${test_config_SRCS} ${UIS} ${RSCS} ${TRS} ${MOCS} )
target_link_libraries ( test_config )
