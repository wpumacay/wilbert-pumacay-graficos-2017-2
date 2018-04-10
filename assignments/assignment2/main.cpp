

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

#define POINT_A engine::LVec3(  3.0f, 1.0f,  5.0f )
#define POINT_B engine::LVec3( -1.0f, 1.0f, -4.0f )
#define POINT_C engine::LVec3(  3.5f, 1.0f, -2.5f )

#ifdef GLUT_SUPPORT_ENABLED

void onMouseCallback( int button, int action, double x, double y )
{
    //cout << "button: " << button << " action: " << action << endl;

    if ( button == 2 && action == 0 )
    {
        // a single right click press was made
        auto _ball = g_scene->getBall();

        if ( _ball->hasMotionStarted() )
        {
            if ( _ball->isPaused() )
            {
                _ball->resumeMovement();
            }
            else
            {
                _ball->stopMovement();
            }   
        }
    }
}

void _onDefaultViewPoint()
{
    g_scene->resetCamera();
}

void onSubMenuEnableLighting( int optionId )
{
    if ( optionId == 0 )
    {
        g_renderer->disableLighting();
        g_scene->disableLighting();
    }
    else if ( optionId == 1 )
    {
        g_renderer->enableLighting();
        g_scene->enableLighting();
    }
}

void onSubMenuShading( int optionId )
{
    if ( optionId == 0 )
    {
        g_scene->setShadingMode( false );
    }
    else if ( optionId == 1 )
    {
        g_scene->setShadingMode( true );
    }
}

void onSubMenuLighting( int optionId )
{
    if ( optionId == 0 )
    {
        g_scene->setMainPointLightMode( 0 );
        g_scene->setMainSpotLightMode( 1 );
    }
    else if ( optionId == 1 )
    {
        g_scene->setMainPointLightMode( 1 );
        g_scene->setMainSpotLightMode( 0 );
    }
}

void onSubMenuWireframe( int optionId )
{
    if ( optionId == 0 )
    {
        g_scene->getBall()->setWireframeMode( false );
    }
    else if ( optionId == 1 )
    {
        g_scene->getBall()->setWireframeMode( true );
    }
}

void onMainMenuCallback( int optionId )
{
    if ( optionId == 0 )
    {
        _onDefaultViewPoint();
    }
    else if ( optionId == 5 )
    {
        exit( 0 );
    }
}

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

    cout << "rendering scene" << endl;
    g_renderer->begin( g_scene );
    g_renderer->renderScene( g_scene );
    g_renderer->end( g_scene );
    cout << "done rendering scene" << endl;
}

#endif

void onKeyCallback( int key, int action )
{
    if ( action == L_KEY_PRESS )
    {
        //cout << "key: " << key << endl;
        //cout << "action: " << action << endl;
        if ( key == L_KEY_W )
        {
            g_isWireframe = !g_isWireframe;
            if ( g_isWireframe )
            {
                cout << "changed to wireframe" << endl;
                g_scene->getBall()->setWireframeMode( true );
                g_renderer->disableLighting();
                g_scene->disableLighting();
            }
            else
            {
                cout << "changed to fill" << endl;
                g_scene->getBall()->setWireframeMode( false );
                g_renderer->enableLighting();
                g_scene->enableLighting();
            }
        }
        else if ( key == L_KEY_S )
        {
            auto _ball = g_scene->getBall();

            if ( _ball->hasMotionStarted() )
            {
                if ( _ball->isPaused() )
                {
                    _ball->resumeMovement();
                }
                else
                {
                    _ball->stopMovement();
                }   
            }
        }
        else if ( key == L_KEY_B || key == L_KEY_B_MAYUS )
        {
            auto _ball = g_scene->getBall();

            if ( _ball->hasMotionStarted() )
            {
                _ball->resetPosition();
            }
            else
            {
                vector<engine::LVec3> _path;
                _path.push_back( POINT_A );
                _path.push_back( POINT_B );
                _path.push_back( POINT_C );
                _path.push_back( POINT_A );

                _ball->startSampleMotion( _path );
            }
        }
        else if ( key == L_KEY_L )
        {
            g_isMainPointLightActive = !g_isMainPointLightActive;
            if ( g_isMainPointLightActive )
            {
                g_scene->setMainPointLightMode( 1 );
                g_scene->setMainSpotLightMode( 0 );
            }
            else
            {
                g_scene->setMainPointLightMode( 0 );
                g_scene->setMainSpotLightMode( 1 );
            }
        }
        else if ( key == L_KEY_X ) { g_scene->increaseCamera( 1.0f, 0.0f, 0.0f ); }
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
    cout << "INITIALIZED GLUT CALLBACKS!!!" << endl;
    g_window->registerMouseCallback( onMouseCallback );
    g_window->registerDisplayCallback( onDisplayCallback );
#endif

    glEnable( GL_DEPTH_TEST );

    // Initialize shader manager
    engine::LShaderManager::create();

    g_renderer = new engine::LSceneRenderer();
    g_scene = new hw::LTestScene();
    
    g_renderer->enableLighting();
    g_scene->enableLighting();

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

#ifdef GLUT_SUPPORT_ENABLED

    // EnableLighting submenu
    auto _smEnableLighting = glutCreateMenu( onSubMenuEnableLighting );
    glutAddMenuEntry( "No", 0 );
    glutAddMenuEntry( "Yes", 1 );
    // Shading submenu
    auto _smShading = glutCreateMenu( onSubMenuShading );
    glutAddMenuEntry( "Flat", 0 );
    glutAddMenuEntry( "Smooth", 1 );
    // Lighting submenu
    auto _smLighting = glutCreateMenu( onSubMenuLighting );
    glutAddMenuEntry( "Spot", 0 );
    glutAddMenuEntry( "Point", 1 );
    // Wireframe submenu
    auto _smWireframe = glutCreateMenu( onSubMenuWireframe );
    glutAddMenuEntry( "No", 0 );
    glutAddMenuEntry( "Yes", 1 );

    glutCreateMenu( onMainMenuCallback );
    glutAddMenuEntry( "Default View Point", 0 );
    glutAddSubMenu( "Enable Lighting", _smEnableLighting );
    glutAddSubMenu( "Shading", _smShading );
    glutAddSubMenu( "Lighting", _smLighting );
    glutAddSubMenu( "Wireframe", _smWireframe );
    glutAddMenuEntry( "Quit", 5 );
    glutAttachMenu( GLUT_LEFT_BUTTON );

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