
cmake_minimum_required( VERSION 3.5.0 )
project( cat1 C CXX )

set( CMAKE_BUILD_TYPE Debug )

set( CMAKE_CXX_STANDARD 11 )
set( CMAKE_CXX_FLAGS_DEBUG "-g -Wno-unused-parameter" )
set( CMAKE_CXX_FLAGS_RELEASE "-O3 -Wno-unused-parameter" )

if( WIN32 )

	message( "making cat1 project for windows" )

	include_directories( engine 
						 ext/glew/include 
						 ext/glfw/include 
						 glm/ )
	
	link_directories( ext/glew/lib/Release/x64 
					  ext/glfw/lib-vc2015 )

elseif( UNIX AND NOT APPLE )

	message( "making cat1 project for linux" )

	find_package( OpenGL REQUIRED )
	find_package( GLUT REQUIRED )
	find_package( GLEW REQUIRED )

	include_directories( engine ${GLUT_INCLUDE_DIRS} )

elseif( APPLE )

	message( "making cat 1 project for macos" )

	find_package( OpenGL REQUIRED )
	find_package( GLUT REQUIRED )
	find_package( GLEW REQUIRED )

	include_directories( engine ${GLUT_INCLUDE_DIRS} )

endif()

if ( 0 )

message( "modern opengl enabled" )

add_definitions( -DUSE_GLFW ) 
add_definitions( -DUSE_MODERN_OPENGL )

else()

message( "legacy opengl enabled" )

add_definitions( -DUSE_GLUT ) ## comment for modern opengl support

endif()


add_subdirectory( ext/glfw )
add_subdirectory( ext/glm )

include_directories( ext/glfw/include )
include_directories( ext/glm )

add_subdirectory( engine )
add_subdirectory( assignments )




