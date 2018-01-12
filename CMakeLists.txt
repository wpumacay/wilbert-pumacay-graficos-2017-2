
cmake_minimum_required( VERSION 3.5.0 )
project( cat1 C CXX )

set( CMAKE_BUILD_TYPE Debug )

set( CMAKE_CXX_STANDARD 11 )
set( CMAKE_CXX_FLAGS_DEBUG "-g -Wno-unused-parameter -Wno-delete-incomplete" )
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

if ( 0 )  ## set to 1 for glfw support

message( "USING GLFW AS WINDOWING SYSTEM" )

set( WINDOWING_SYSTEM "GLFW" CACHE STRING "GLFW" )

add_definitions( -DUSE_GLFW ) 
add_definitions( -DGLFW_SUPPORT_ENABLED ) 
add_definitions( -DUSE_MODERN_OPENGL )
add_definitions( -DUSE_MODERN ) ## use glsl 330+ version

else()

message( "USING GLUT AS WINDOWING SYSTEM" )

set( WINDOWING_SYSTEM "GLUT" CACHE STRING "GLUT" )

add_definitions( -DUSE_GLUT )
add_definitions( -DGLUT_SUPPORT_ENABLED ) 

	if ( 0 ) ## set to 1 to use v330 core glsl shaders

	message( "MODERN OPENGL ENABLED - V120 with GLUT" )
	add_definitions( -DUSE_MODERN )

	endif()

endif()


add_subdirectory( ext/glfw )
add_subdirectory( ext/glm )

include_directories( ext/glfw/include )
include_directories( ext/glm )
include_directories( ext/stb )

add_subdirectory( engine )
add_subdirectory( assignments )




