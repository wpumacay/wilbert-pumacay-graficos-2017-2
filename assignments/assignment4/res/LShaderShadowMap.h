
#pragma once

#include "LShader.h"

namespace engine
{

	class LShaderShadowMap : public LShader
	{

		private :

        GLuint m_uModel;
        GLuint m_uView;
        GLuint m_uProj;

		public :

		LShaderShadowMap( GLuint id ) : LShader( id )
		{
			bind();

            m_uModel = glGetUniformLocation( m_id, "u_tModel" );
            m_uView  = glGetUniformLocation( m_id, "u_tView" );
            m_uProj  = glGetUniformLocation( m_id, "u_tProj" );

			unbind();
		}

        void setModelMatrix( const glm::mat4& mat )
        {
            _setMat4( m_uModel, mat );
        }

        void setViewMatrix( const glm::mat4& mat )
        {
            _setMat4( m_uView, mat );
        }

        void setProjectionMatrix( const glm::mat4& mat )
        {
            _setMat4( m_uProj, mat );
        }

	};


}