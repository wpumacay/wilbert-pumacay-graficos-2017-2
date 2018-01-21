

#include "LWindow.h"
#include "LShaderManager.h"

#include <iostream>
#include <vector>

using namespace std;

engine::LWindow* g_window;

void onDisplayCallback();

struct Terrain
{
    GLuint vbo;
    vector<engine::LVec2> vertices;
};

Terrain g_terrain;
GLuint g_shaderProgram;
glm::mat4 g_projMatrix;
glm::mat4 g_viewMatrix;

vector<engine::LVec2> createTerrainGrid( float width, float height, int divWidth, int divHeight )
{
    vector<engine::LVec2> _vertices;

    float _dw = width / divWidth;
    float _dh = height / divHeight;

    float _halfWidth  = width / 2.0f;
    float _halfHeight = height / 2.0f;

    for ( int _y = 0; _y < divHeight; _y++ )
    {
        for ( int _x = 0; _x < divWidth; _x++ )
        {
            engine::LVec2 _p1( ( _x + 0 ) * _dw - _halfWidth, ( _y + 0 ) * _dh - _halfHeight );
            engine::LVec2 _p2( ( _x + 0 ) * _dw - _halfWidth, ( _y + 1 ) * _dh - _halfHeight );
            engine::LVec2 _p3( ( _x + 1 ) * _dw - _halfWidth, ( _y + 1 ) * _dh - _halfHeight );
            engine::LVec2 _p4( ( _x + 1 ) * _dw - _halfWidth, ( _y + 0 ) * _dh - _halfHeight );

            _vertices.push_back( _p1 ); _vertices.push_back( _p2 ); _vertices.push_back( _p3 );
            _vertices.push_back( _p1 ); _vertices.push_back( _p3 ); _vertices.push_back( _p4 );

            // cout << "x: " << _p1.x << " - y: " << _p1.y << endl;
        }
    }

    return _vertices;
}

Terrain createTerrainObj()
{
    Terrain _terrain;

    _terrain.vertices = createTerrainGrid( 1, 1, 10, 10 );

    glGenBuffers( 1, &_terrain.vbo );
    glBindBuffer( GL_ARRAY_BUFFER, _terrain.vbo );
    glBufferData( GL_ARRAY_BUFFER, sizeof( engine::LVec2 ) * _terrain.vertices.size() , _terrain.vertices.data(), GL_STATIC_DRAW );

    // // if using subdata
    // glBufferData( GL_ARRAY_BUFFER, sizeof( engine::LVec2 ) * _terrain.vertices.size() , NULL, GL_STATIC_DRAW );
    // glBufferSubdata( GL_ARRAY_BUFFER, 0, sizeofverticesinbytes, vertices.data() )
    // glBufferSubdata( GL_ARRAY_BUFFER, sizeofverticesinbytes, sizeofnormalsinbytes, normals.data() )
    // glBufferSubdata( GL_ARRAY_BUFFER, sizeofverticesinbytes + sizeofnormalsinbytes, sizeofcolorsinbytes, colors.data() )

    return _terrain;
}

void init()
{
    glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );

    g_terrain = createTerrainObj();

    GLuint _vShader = engine::LShaderManager::INSTANCE->createShader( "res/shaders/superBasic2d_vs_120.glsl", GL_VERTEX_SHADER );
    GLuint _fShader = engine::LShaderManager::INSTANCE->createShader( "res/shaders/superBasic2d_fs_120.glsl", GL_FRAGMENT_SHADER );
    
    g_shaderProgram = engine::LShaderManager::INSTANCE->createProgram( _vShader, _fShader );

    g_projMatrix = glm::perspective( glm::radians( 45.0f ),
                                     ( float ) APP_WIDTH / APP_HEIGHT,
                                     0.1f, 100.0f );

    g_viewMatrix = glm::lookAt( glm::vec3( 2, 2, 2 ), glm::vec3( 0, 0, 0 ), glm::vec3( 0, 1, 0 ) );

}

int main()
{
    g_window = new engine::LWindow();

    // Initialize shader manager
    engine::LShaderManager::create();

    init();

    g_window->registerDisplayCallback( onDisplayCallback );

    g_window->loop();

    return 0;
}



void onDisplayCallback()
{
    g_window->clear();

    // use a shader
    glUseProgram( g_shaderProgram );

    glUniformMatrix4fv( glGetUniformLocation( g_shaderProgram, "u_ViewMatrix" ), 1, GL_FALSE, glm::value_ptr( g_viewMatrix ) );
    glUniformMatrix4fv( glGetUniformLocation( g_shaderProgram, "u_ProjMatrix" ), 1, GL_FALSE, glm::value_ptr( g_projMatrix ) );

    // Oye shader, usa esta data
    glBindBuffer( GL_ARRAY_BUFFER, g_terrain.vbo );

    glEnableVertexAttribArray( 0 );
    glVertexAttribPointer( 0, 2, GL_FLOAT, GL_FALSE, 0, 0 );
    // // If using one buffer per attrib

    // glBindBuffer( GL_ARRAY_BUFFER, g_terrain.vbonormals );

    // glEnableVertexAttribArray( 1 );
    // glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, 0, 0 );

    // glBindBuffer( GL_ARRAY_BUFFER, g_terrain.vbocolors );

    // glEnableVertexAttribArray( 2 );
    // glVertexAttribPointer( 2, 3, GL_FLOAT, GL_FALSE, 0, 0 );

    // If using one buffer for all attribs ... version 1 ( using subdata )

    // glBindBuffer( GL_ARRAY_BUFFER, g_terrain.vbonormals );

    // glEnableVertexAttribArray( 1 );
    // glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, 0, sizeofverticesinbytes );

    // glBindBuffer( GL_ARRAY_BUFFER, g_terrain.vbocolors );

    // glEnableVertexAttribArray( 2 );
    // glVertexAttribPointer( 2, 3, GL_FLOAT, GL_FALSE, 0, sizeofverticesinbytes + sizeofnormalsinbytes );    

    // If using one buffer for all attribs ... version 2 ( using "combined" data )

    // glBindBuffer( GL_ARRAY_BUFFER, g_terrain.vbonormals );

    // glEnableVertexAttribArray( 1 );
    // glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, sizeofpos(vec2) + sizeofnormal(vec3) + sizeofcolor(vec3), sizeofvec2 );

    // glBindBuffer( GL_ARRAY_BUFFER, g_terrain.vbocolors );

    // glEnableVertexAttribArray( 2 );
    // glVertexAttribPointer( 2, 3, GL_FLOAT, GL_FALSE, sizeofpos + sizeofnormal + sizeofcolor, sizeofvec2 + sizeofvec3 );    

    glDrawArrays( GL_TRIANGLES, 0, g_terrain.vertices.size() );

    glUseProgram( 0 );
}
