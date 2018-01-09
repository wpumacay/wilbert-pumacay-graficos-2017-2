

#pragma once

#include "../Common.h"
#include "LShader.h"

#include <GL/glew.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <map>

using namespace std;

namespace engine
{

    struct LShaderManager
    {

        private :

        LShaderManager();

        public :

        map< string, GLuint > programs;
        map< string, LShader* > programObjs;
        GLuint currentShader;

        static LShaderManager* INSTANCE;

        static void create();
        ~LShaderManager();
        void release();

        void setCurrentShader( string sId );

        GLuint createShader( const char* filename, int shaderType );
        GLuint createProgram( GLuint vShader, GLuint fShader );


    };

}