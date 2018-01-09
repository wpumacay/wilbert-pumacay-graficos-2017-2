
#pragma once

#include "LFrameBuffer.h"
#include "LLight.h"

using namespace std;

#define SHADOW_WIDTH 1024
#define SHADOW_HEIGHT 1024

namespace engine
{
	
	class LShadowMap
	{

		private :

		LFrameBuffer* m_shadowBuffer;

		glm::mat4 m_viewMat;
		glm::mat4 m_projMat;

		public :


		LShadowMap();
		~LShadowMap();

		void begin( LLight* pLight );
		void end();

	};



}