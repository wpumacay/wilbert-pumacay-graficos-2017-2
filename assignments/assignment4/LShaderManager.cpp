

#include "LShaderManager.h"
#include "../Config.h"

#include "LShaderBasic3d.h"
#include "LShaderLighting.h"
#include "LShaderTerrainPatch.h"

using namespace std;

namespace engine
{

    LShaderManager* LShaderManager::INSTANCE = NULL;

    LShaderManager::LShaderManager()
    {
        // Load all shaders available

        GLuint _vShader, _fShader, _program;
#ifdef USE_MODERN
        cout << "LShaderManager-> using glsl 330 core shaders" << endl;

        _vShader = createShader( "res/shaders/basic3d_vs.glsl", GL_VERTEX_SHADER );
        _fShader = createShader( "res/shaders/basic3d_fs.glsl", GL_FRAGMENT_SHADER );
        _program = createProgram( _vShader, _fShader );

        programs["basic3d"] = _program;

        _vShader = createShader( "res/shaders/basic3d_lighting_vs.glsl", GL_VERTEX_SHADER );
        _fShader = createShader( "res/shaders/basic3d_lighting_fs.glsl", GL_FRAGMENT_SHADER );
        _program = createProgram( _vShader, _fShader );

        programs["basic3d_lighting"] = _program;

        _vShader = createShader( "res/shaders/debug_shader3d_vs.glsl", GL_VERTEX_SHADER );
        _fShader = createShader( "res/shaders/debug_shader3d_fs.glsl", GL_FRAGMENT_SHADER );
        _program = createProgram( _vShader, _fShader );

        programs["debug3d"] = _program;
#else
        cout << "LShaderManager-> using glsl 120 shaders" << endl;

        _vShader = createShader( "res/shaders/basic3d_vs_120.glsl", GL_VERTEX_SHADER );
        _fShader = createShader( "res/shaders/basic3d_fs_120.glsl", GL_FRAGMENT_SHADER );
        _program = createProgram( _vShader, _fShader );

        programs["basic3d"] = _program;
        programObjs["basic3d"] = new LShaderBasic3d( _program );

        _vShader = createShader( "res/shaders/basic3d_lighting_vs_120.glsl", GL_VERTEX_SHADER );
        _fShader = createShader( "res/shaders/basic3d_lighting_fs_120.glsl", GL_FRAGMENT_SHADER );
        _program = createProgram( _vShader, _fShader );

        programs["basic3d_lighting"] = _program;
        programObjs["basic3d_lighting"] = new LShaderLighting( _program );

        _vShader = createShader( "res/shaders/basic3d_textured_vs_120.glsl", GL_VERTEX_SHADER );
        _fShader = createShader( "res/shaders/basic3d_textured_fs_120.glsl", GL_FRAGMENT_SHADER );
        _program = createProgram( _vShader, _fShader );

        programs["basic3d_textured"] = _program;
        programObjs["basic3d_textured"] = new LShaderBasic3d( _program );

        _vShader = createShader( "res/shaders/basic3d_lighting_textured_vs_120.glsl", GL_VERTEX_SHADER );
        _fShader = createShader( "res/shaders/basic3d_lighting_textured_fs_120.glsl", GL_FRAGMENT_SHADER );
        _program = createProgram( _vShader, _fShader );

        programs["basic3d_lighting_textured"] = _program;
        programObjs["basic3d_lighting_textured"] = new LShaderLighting( _program );

        _vShader = createShader( "res/shaders/debug_shader3d_vs_120.glsl", GL_VERTEX_SHADER );
        _fShader = createShader( "res/shaders/debug_shader3d_fs_120.glsl", GL_FRAGMENT_SHADER );
        _program = createProgram( _vShader, _fShader );

        programs["debug3d"] = _program;
        programObjs["debug3d"] = new LShader( _program );

        _vShader = createShader( "res/shaders/terrain_patch_vs_120.glsl", GL_VERTEX_SHADER );
        _fShader = createShader( "res/shaders/terrain_patch_fs_120.glsl", GL_FRAGMENT_SHADER );
        _program = createProgram( _vShader, _fShader );

        programs["terrain_patch"] = _program;
        programObjs["terrain_patch"] = new LShaderTerrainPatch( _program );

#endif
    }

    LShaderManager::~LShaderManager()
    {
        release();
    }

    void LShaderManager::release()
    {
        map< string, GLuint >::iterator _it;
        for ( _it = programs.begin(); _it != programs.end(); ++_it )
        {
            glDeleteProgram( _it->second );
        }
    }

    void LShaderManager::create()
    {
        if ( LShaderManager::INSTANCE != NULL )
        {
            delete LShaderManager::INSTANCE;
        }

        LShaderManager::INSTANCE = new LShaderManager();
    }


    GLuint LShaderManager::createShader( const char* filename, int shaderType )
    {
        // Load the shader code into a string ********************************************
        string _shaderStrCode;
        ifstream _shaderFile;

        _shaderFile.exceptions( ifstream::badbit );

        try 
        {
            _shaderFile.open( filename );
            stringstream _shaderStream;
            _shaderStream << _shaderFile.rdbuf();

            _shaderFile.close();

            _shaderStrCode = _shaderStream.str();
        }
        catch ( ... )
        {
            cout << "LShader::createFromFile> failed opening the resource file" << endl;
            return 0;
        }

        const char* _shaderCode_cstr = _shaderStrCode.c_str();
        // *******************************************************************************

        GLint _success;
        GLchar _infoLog[1024];

        GLuint _shaderId = glCreateShader( shaderType );
        glShaderSource( _shaderId, 1, &_shaderCode_cstr, NULL );
        glCompileShader( _shaderId );
        glGetShaderiv( _shaderId, GL_COMPILE_STATUS,
                       &_success );

        if ( !_success )
        {
            glGetShaderInfoLog( _shaderId, 1024, 
                                NULL, _infoLog );
            cout << "Shader: " << filename << endl;
            cout << "Failed to compile shader" << endl;
            cout << "Error: " << _infoLog << endl;

            return 0;
        }

        return _shaderId;
    }

    GLuint LShaderManager::createProgram( GLuint vShaderId, GLuint fShaderId )
    {
        GLint _success;
        GLchar _infoLog[1024];

        GLuint _programId = glCreateProgram();
        glAttachShader( _programId, vShaderId );
        glAttachShader( _programId, fShaderId );
        glLinkProgram( _programId );

        glDetachShader( _programId, vShaderId );
        glDetachShader( _programId, fShaderId );
        glDeleteShader( vShaderId );
        glDeleteShader( fShaderId );

        glGetProgramiv( _programId, GL_LINK_STATUS, &_success );
        if ( !_success )
        {
            glGetProgramInfoLog( _programId, 1024, NULL, _infoLog );
            cout << "LINKING ERROR: " << _infoLog << endl;

            return 0;
        }

        return _programId;
    }

}