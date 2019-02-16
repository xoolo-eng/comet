cmake_minimum_required( VERSION 3.1 )
set( CMAKE_CXX_STANDARD 14 )
set( CMAKE_INCLUDE_CURRENT_DIR ON )
set( CMAKE_AUTOMOC ON )
set( CMAKE_BUILD_TYPE Release )
add_definitions ( -Wall )
set ( EXECUTABLE_OUTPUT_PATH bin )
set ( test_socket_HDRS

	)

set ( test_socket_SRCS
	../../src/test_socket.cpp
	)
	nclude_directories( ../../../include )
	link_directories( ../../../lib )
add_executable ( test_socket ${test_socket_SRCS} ${UIS} ${RSCS} ${TRS} ${MOCS} )
target_link_libraries ( test_socket socket )
