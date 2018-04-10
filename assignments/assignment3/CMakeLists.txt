


if( WIN32 )

    message( "Building assignment 3 - windows" )
    message( "Sorry, haven't configured it yet" )

elseif( UNIX AND NOT APPLE )

    message( "Building assignment 3 - linux" )
    add_executable( assignment3.out
                    main.cpp 
                    LCommon.cpp
                    LComponent.cpp
                    LEntity.cpp
                    LFixedCamera3d.cpp
                    LICamera.cpp
                    LIndexBuffer.cpp
                    LTexture.cpp
                    LMeshBuilder.cpp
                    LMeshComponent.cpp
                    LMesh.cpp
                    LScene.cpp
                    LSceneRenderer.cpp
                    LShader.cpp
                    LShaderManager.cpp
                    LVertexArray.cpp
                    LVertexBuffer.cpp
                    LWindow.cpp )

    if ( WINDOWING_SYSTEM STREQUAL "GLFW" )

        message( "GLFW!!!!" )

        target_link_libraries( assignment3.out glfw
                               ${OPENGL_LIBRARIES} 
                               GLEW::GLEW 
                               ${GLUT_LIBRARY} )

    elseif( WINDOWING_SYSTEM STREQUAL "GLUT" )

        message( "GLUT!!!!" )

        target_link_libraries( assignment3.out
                               ${OPENGL_LIBRARIES} 
                               GLEW::GLEW 
                               ${GLUT_LIBRARY} )
    else()

        message( "WINDOWING_SYSTEM NOT SET CORRECTLY" )

    endif()

elseif( APPLE )

    message( "Building assignment 3 - macOS" )
    add_executable( assignment3.out
                    main.cpp 
                    LCommon.cpp
                    LComponent.cpp
                    LEntity.cpp
                    LFixedCamera3d.cpp
                    LICamera.cpp
                    LIndexBuffer.cpp
                    LTexture.cpp
                    LMeshBuilder.cpp
                    LMeshComponent.cpp
                    LMesh.cpp
                    LScene.cpp
                    LSceneRenderer.cpp
                    LShader.cpp
                    LShaderManager.cpp
                    LVertexArray.cpp
                    LVertexBuffer.cpp
                    LWindow.cpp )

    if ( ${WINDOWING_SYSTEM} EQUAL "GLFW" )

        target_link_libraries( assignment3.out glfw
                               "-framework GLUT"
                               "-framework OpenGL"
                               ${GLEW_LIBRARIES} )

    elseif( ${WINDOWING_SYSTEM} EQUAL "GLUT" )

        target_link_libraries( assignment3.out
                               "-framework GLUT"
                               "-framework OpenGL"
                               ${GLEW_LIBRARIES} )
    else()

        message( "WINDOWING_SYSTEM NOT SET CORRECTLY" )

    endif()
endif()
