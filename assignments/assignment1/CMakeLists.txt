
message( "generating test_gl project" )

add_subdirectory( miniengine )

include_directories( ../../engine/include miniengine/include/ )

if( WIN32 )

    add_executable( main main.cpp )
    target_link_libraries( main glew32s glfw3 opengl32 )

elseif( UNIX AND NOT APPLE )

    add_executable( main.out main.cpp )
    target_link_libraries( main.out cat1gl miniengine glfw
                           ${OPENGL_LIBRARIES} 
                           GLEW::GLEW 
                           GLU
                           ${GLUT_LIBRARY} )

    add_executable( editor_ear_clipping_test.out editor_ear_clipping_test.cpp )
    target_link_libraries( editor_ear_clipping_test.out cat1gl miniengine glfw
                           ${OPENGL_LIBRARIES} 
                           GLEW::GLEW 
                           GLU
                           ${GLUT_LIBRARY} )

elseif( APPLE )

    add_executable( main.out main.cpp )
    target_link_libraries( main.out cat1gl miniengine glfw
                           ${OPENGL_LIBRARIES} 
                           ${GLUT_LIBRARY}
                           GLEW::GLEW 
                           GLU )

    add_executable( editor_ear_clipping_test.out editor_ear_clipping_test.cpp )
    target_link_libraries( editor_ear_clipping_test.out cat1gl miniengine glfw
                           ${OPENGL_LIBRARIES} 
                           ${GLUT_LIBRARY}
                           GLEW::GLEW 
                           GLU )

endif()