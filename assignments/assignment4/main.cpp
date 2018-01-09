

#include "LWindow.h"
#include "LShaderManager.h"
#include "LSceneRenderer.h"
#include "hw/LTestScene.h"

#include <iostream>
#include <vector>

using namespace std;

bool g_isWireframe = false;
bool g_isMainPointLightActive = true;
hw::LTestScene* g_scene;
engine::LWindow* g_window;

engine::LVertexArray* g_xAxis;
engine::LVertexArray* g_yAxis;
engine::LVertexArray* g_zAxis;

engine::LSceneRenderer* g_renderer;

#ifdef GLUT_SUPPORT_ENABLED

void onDisplayCallback()
{
    g_window->clear();

    g_scene->update( 0.021 );

    GLuint _debugShader = engine::LShaderManager::INSTANCE->programs["debug3d"];

    glUseProgram( _debugShader );

    GLuint _u_proj = glGetUniformLocation( _debugShader, "u_tProj" );
    GLuint _u_view = glGetUniformLocation( _debugShader, "u_tView" );
    GLuint _u_color = glGetUniformLocation( _debugShader, "u_color" );

    glUniformMatrix4fv( _u_proj, 1, GL_FALSE, glm::value_ptr( g_scene->getProjMatrix() ) );
    glUniformMatrix4fv( _u_view, 1, GL_FALSE, glm::value_ptr( g_scene->getCurrentCamera()->getViewMatrix() ) );

    // Draw the x axis
    g_xAxis->bind();
    glUniform3f( _u_color, 1.0f, 0.0f, 0.0f );

    glDrawArrays( GL_LINES, 0, 2 );

    g_xAxis->unbind();

    // Draw the y axis
    g_yAxis->bind();
    glUniform3f( _u_color, 1.0f, 0.0f, 1.0f );

    glDrawArrays( GL_LINES, 0, 2 );

    g_yAxis->unbind();

    // Draw the z axis
    g_zAxis->bind();
    glUniform3f( _u_color, 0.0f, 0.0f, 1.0f );

    glDrawArrays( GL_LINES, 0, 2 );

    g_zAxis->unbind();

    glUseProgram( 0 );

    g_renderer->begin( g_scene );
    g_renderer->renderScene( g_scene );
    g_renderer->end( g_scene );
}

#endif

void onKeyCallback( int key, int action )
{
    if ( action == L_KEY_PRESS )
    {
        if ( key == L_KEY_X ) { g_scene->increaseCamera( 1.0f, 0.0f, 0.0f ); }
        else if ( key == L_KEY_X_MAYUS ) { g_scene->increaseCamera( -1.0f, 0.0f, 0.0f ); }
        else if ( key == L_KEY_Y ) { g_scene->increaseCamera( 0.0f, 1.0f, 0.0f ); }
        else if ( key == L_KEY_Y_MAYUS ) { g_scene->increaseCamera( 0.0f, -1.0f, 0.0f ); }
        else if ( key == L_KEY_Z ) { g_scene->increaseCamera( 0.0f, 0.0f, 1.0f ); }
        else if ( key == L_KEY_Z_MAYUS ) { g_scene->increaseCamera( 0.0f, 0.0f, -1.0f ); }
    }
}

int main()
{
    g_window = new engine::LWindow();
    g_window->registerKeyCallback( onKeyCallback );

#ifdef GLUT_SUPPORT_ENABLED
    g_window->registerDisplayCallback( onDisplayCallback );
#endif

    //glEnable( GL_DEPTH_TEST );

    // Initialize shader manager
    engine::LShaderManager::create();

    // TODO: Abstract the debug primitives into a separate layer :(
    engine::LVertexBuffer* _xAxisBuff = new engine::LVertexBuffer();
    GLfloat _xAxisData[] = 
    {
         0.0f, 0.0f, 0.0f,
        10.0f, 0.0f, 0.0f
    };
    _xAxisBuff->setData( 6 * sizeof( GLfloat ), 3, _xAxisData );

    g_xAxis = new engine::LVertexArray();
    g_xAxis->addBuffer( _xAxisBuff, 0 );

    engine::LVertexBuffer* _yAxisBuff = new engine::LVertexBuffer();
    GLfloat _yAxisData[] = 
    {
         0.0f,  0.0f, 0.0f,
         0.0f, 10.0f, 0.0f
    };
    _yAxisBuff->setData( 6 * sizeof( GLfloat ), 3, _yAxisData );

    g_yAxis = new engine::LVertexArray();
    g_yAxis->addBuffer( _yAxisBuff, 0 );

    engine::LVertexBuffer* _zAxisBuff = new engine::LVertexBuffer();
    GLfloat _zAxisData[] = 
    {
         0.0f, 0.0f,  0.0f,
         0.0f, 0.0f, 10.0f
    };
    _zAxisBuff->setData( 6 * sizeof( GLfloat ), 3, _zAxisData );

    g_zAxis = new engine::LVertexArray();
    g_zAxis->addBuffer( _zAxisBuff, 0 );

    g_renderer = new engine::LSceneRenderer();
    
    g_scene = new hw::LTestScene();

#ifdef GLUT_SUPPORT_ENABLED
    g_window->loop();
#endif

#ifdef GLFW_SUPPORT_ENABLED
    while ( g_window->isActive() )
    {
        g_window->clear();
        g_window->pollEvents();

        g_scene->update( 0.02 );

        GLuint _debugShader = engine::LShaderManager::INSTANCE->programs["debug3d"];

        glUseProgram( _debugShader );

        GLuint _u_proj = glGetUniformLocation( _debugShader, "u_tProj" );
        GLuint _u_view = glGetUniformLocation( _debugShader, "u_tView" );
        GLuint _u_color = glGetUniformLocation( _debugShader, "u_color" );

        glUniformMatrix4fv( _u_proj, 1, GL_FALSE, glm::value_ptr( g_scene->getProjMatrix() ) );
        glUniformMatrix4fv( _u_view, 1, GL_FALSE, glm::value_ptr( g_scene->getCurrentCamera()->getViewMatrix() ) );

        // Draw axis x
        g_xAxis->bind();

        glUniform3f( _u_color, 1.0f, 0.0f, 0.0f );

        glDrawArrays( GL_LINES, 0, 2 );

        g_xAxis->unbind();

        // Draw axis y
        g_yAxis->bind();

        glUniform3f( _u_color, 0.0f, 1.0f, 0.0f );

        glDrawArrays( GL_LINES, 0, 2 );

        g_yAxis->unbind();        

        // Draw axis z
        g_zAxis->bind();

        glUniform3f( _u_color, 0.0f, 0.0f, 1.0f );

        glDrawArrays( GL_LINES, 0, 2 );

        g_zAxis->unbind();

        glUseProgram( 0 );

        g_renderer->begin( g_scene );
        g_renderer->renderScene( g_scene );
        g_renderer->end( g_scene );

        g_window->swapBuffers();
    }
#endif
    return 0;
}