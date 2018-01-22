# Assignments of the Computer Graphics course :D

## Latest build 1.1

## Dependencies :

* CMake
* GLUT
* GLU
* GLEW -> need to be installed, wip: adding git submodule
* GLFW -> included as a submodule, just clone with --recursive
* GLM -> included as a submodule, just clone with --recursive

## Support :

Tested in :

* OSX -> macbookair ( thanks xavier for letting me use your laptop :D )
* Linux-Ubuntu

## Cloning it :

Make sure to clone the repo using --recursive

```
git clone --recursive https://github.com/wpumacay/wilbert-pumacay-graficos-2017-2.git
```

This will clone also the dependencies that reside in other repositories, like glm and glfw. After some testing, it seems glut in macOS can't create a 3.3 core context, so instread I used GLFW. You don't have to install it, just clone with --recursive to download the repository. The cmake files provided will take care of the compilation. 
If you have problems with other libraries, please let me know at wilbert.pumacay@ucsp.edu.pe so that I can add the submodules or fix the CMake files :D. ( Maybe I forgot some preprocessor flag to skip some dependencies )

## To compile :

If you have the cmake with command line tools, just type :

```
cd [repo_root]
cmake .
make
```

If using the cmake - GUI, just configure it with that, and make the build directory the same as the root directory (in place build) as some resources are loaded relative to some paths. If done wrong, the shaders may not be loaded :(.

The default configuration is to use GLUT as window creation system, and
by default uses ~~legacy~~ ( if using glut, can set the mode to use glsl v120 ) OpenGL.

To use modern OpenGL, just change this part in the root CMakeLists.txt file. Set the '0' to '1' to enable modern opengl.

```cmake
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
```

Modern opengl usage needs glfw as windowing system for macOS, so the library was provided as a submodule. When compiling the code, the glfw library will be compiled as well, so no installation is needed. Just make sure you download it with the **--recursive** option

## Assignments

* [Assignment 1] ( https://github.com/wpumacay/wilbert-pumacay-graficos-2017-2/tree/master/assignments/assignment1 )
* [Assignment 2] ( https://github.com/wpumacay/wilbert-pumacay-graficos-2017-2/tree/master/assignments/assignment2 )
* [Assignment 3] ( https://github.com/wpumacay/wilbert-pumacay-graficos-2017-2/tree/master/assignments/assignment3 )
* [Assignment 4] ( https://github.com/wpumacay/wilbert-pumacay-graficos-2017-2/tree/master/assignments/assignment4 )
