

#include "LWindow.h"
#include "LShaderManager.h"
#include "LSceneRenderer.h"
#include "hw/LTestScene.h"

#include <iostream>
#include <vector>

using namespace std;

hw::LTestScene* g_scene;
engine::LWindow* g_window;

engine::LVertexArray* g_xAxis;
engine::LVertexArray* g_yAxis;
engine::LVertexArray* g_zAxis;

void onMouseCallback( int button, int action, double x, double y )
{

}


void onDisplayCallback()
{
    g_window->clear();

    GLuint _debugShader = engine::LShaderManager::INSTANCE->programs["debug3d"];

    glUseProgram( _debugShader );

    GLuint _u_proj = glGetUniformLocation( _debugShader, "u_tProj" );
    GLuint _u_view = glGetUniformLocation( _debugShader, "u_tView" );
    GLuint _u_color = glGetUniformLocation( _debugShader, "u_color" );

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
}

void onKeyCallback( int key, int action )
{

}

int main()
{
    g_window = new engine::LWindow();
    g_window->registerKeyCallback( onKeyCallback );

    g_window->registerMouseCallback( onMouseCallback );
    g_window->registerDisplayCallback( onDisplayCallback );

    glEnable( GL_DEPTH_TEST );

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

    g_scene = new hw::LTestScene();

    g_window->loop();


    return 0;
}