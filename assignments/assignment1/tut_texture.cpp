

#include <core/LBaseApp.h>
#include <cmath>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#endif

class TutTextureApp : public engine::core::LBaseApp
{
    private :

    GLuint m_textureId;
    GLuint m_vbo;
    GLuint m_ebo;
    GLuint m_vao;

    protected :

    TutTextureApp() : engine::core::LBaseApp()
    {

    }

    public :

    Hw1App() : engine::core::LBaseApp()
    {
        miniengine::LShaderManager::create();
    }

    static void create()
    {
        if ( TutTextureApp::instance != NULL )
        {
            delete TutTextureApp::instance;
        }

        TutTextureApp::instance = new TutTextureApp();
        TutTextureApp::instance->init();
    }

    void onStartup() override
    {
        ENGINE_LOG( "TutTextureApp::onStartup> initializing some custom stuff" );

        miniengine::LShaderManager::instance->initialize();

        // Load the texture
        int _width, _height, _channels;
        unsigned char* _data = stbi_load( "res/imgs/wall.jpg", &_width, &_height, &_channels, 0 );

        if ( _data == NULL )
        {
            std::cout << "error while loading the texture image" << std::endl;
            return;
        }

        glGenTextures( 1, &m_textureId );
        glBindTexture( GL_TEXTURE_2D, m_textureId );
        glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, _width, _height, 0, GL_RGB, GL_UNSIGNED_BYTE, _data );
        glGenerateMipmap( GL_TEXTURE_2D );

        stbi_image_free( _data );

        // Load-bind geometry
        static GLfloat _vertexData[] =
        {
            // positions -    uvs
            -0.5f, -0.5f, 0.0f, 0.0f,
             0.0f,  0.5f, 0.5f, 1.0f,
             0.5f, -0.5f, 1.0f, 0.0f
        };

        static GLuint _indices[] =
        {
            0, 1, 2
        };

        glGenBuffers( 1, &m_vbo );
        glGenBuffers( 1, &m_ebo );
        glGenVertexArrays( 1, &m_vao );

        glBindVertexArray( m_vao );

        glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, m_ebo );
        glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof( GLuint ) * 3,
                      _indices, GL_STATIC_DRAW );

        glBindBuffer( GL_ARRAY_BUFFER, m_vbo );
        glBufferData( GL_ARRAY_BUFFER, sizeof( GLfloat ) * 12,
                      _vertexData, GL_STATIC_DRAW );

        glVertexAttribPointer( 0, 2, GL_FLOAT, GL_FALSE, 0, ( void* ) 0 );
        glEnableVertexAttribArray( 0 );

        glVertexAttribPointer( 0, 2, GL_FLOAT, GL_FALSE, 0, ( void* ) 0 );
        glEnableVertexAttribArray( 0 );

        glBindVertexArray( 0 );

    }

    void render() override
    {

        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
        

        
        
    }

};










int main()
{





}