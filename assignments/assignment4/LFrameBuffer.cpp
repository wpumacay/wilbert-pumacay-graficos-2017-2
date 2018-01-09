
#include "LFrameBuffer.h"

using namespace std;

namespace engine
{

	LFrameBuffer::LFrameBuffer( GLuint fboFormat, GLuint fboDataType, int width, int height )
	{
		m_fboFormat = fboFormat;
		m_fboDataType = fboDataType;

		m_width = width;
		m_height = height;

		glGenFrameBuffers( 1, &m_frameBufferId );

		
		
		glGenTextures( 1, &m_frameBufferTex );

		
	}

	LFrameBuffer::~LFrameBuffer()
	{
		glDeleteFrameBuffers( 1, &m_frameBufferId );
		glDeleteTextures( 1, &m_frameBufferTex );
	}

	void LFrameBuffer::bind()
	{
		glBindFrameBuffer( GL_FRAMEBUFFER, m_frameBufferId );
	}

	void LFrameBuffer::unbind()
	{
		
	}

}