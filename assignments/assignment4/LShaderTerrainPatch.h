
#pragma once

#include "LShader.h"

namespace engine
{


    class LShaderTerrainPatch : public LShader
    {
        protected :

        GLuint m_uView;
        GLuint m_uProj;
        GLuint m_uColor;

        public :

        LShaderTerrainPatch( GLuint id ) : LShader( id )
        {
            bind();

            // Load uniforms
            m_uView  = glGetUniformLocation( m_id, "u_tView" );
            m_uProj  = glGetUniformLocation( m_id, "u_tProj" );
            m_uColor = glGetUniformLocation( m_id, "u_color" );

            unbind();
        }

        void setViewMatrix( const glm::mat4& mat )
        {
            _setMat4( m_uView, mat );
        }

        void setProjectionMatrix( const glm::mat4& mat )
        {
            _setMat4( m_uProj, mat );
        }

        void setPlainColor( const LVec3& color )
        {
            _setVec3( m_uColor, color );
        }

    };



}