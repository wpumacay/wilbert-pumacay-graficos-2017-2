
#pragma once

#include "LCommon.h"
#include "LIRenderable.h"
#include "LVertexBuffer.h"
#include "LVertexArray.h"
#include "LHeightmapGenerator.h"
#include "LMaterial.h"
#include "LTexture.h"

using namespace std;

namespace engine
{


	class LTerrainPatch : public LIRenderable
	{

		protected :

		LVertexBuffer* m_terrainVertBuff;
		LVertexBuffer* m_terrainNormBuff;
		LVertexArray* m_terrainVao;


		vector<LVec3> m_terrainVertices;
		vector<LVec3> m_terrainNormals;

		GLfloat m_patchWidth;
		GLfloat m_patchDepth;

		int m_patchWidthDiv;
		int m_patchDepthDiv;

		LHeightmapGenerator* m_generator;

		bool m_isWireframe;

		float _getHeight( float x, float z );

		LVec3 m_pos;

		vector<LTexture*> m_textures;
		vector<LMaterial*> m_materials;

		public :

		LTerrainPatch( float xp, float zp,
					   GLfloat patchWidth, GLfloat patchDepth, 
					   int patchWidthDiv, int patchDepthDiv, LHeightmapGenerator* pGenerator = NULL );
		~LTerrainPatch();

		void resample( float patchX, float patchZ );

		void enableWireframe() { m_isWireframe = true; }
		void disableWireframe() { m_isWireframe = false; }
		bool isWireframe() { return m_isWireframe; }

		void addTexture( LTexture* pTexture ) { m_textures.push_back( pTexture ); }
		void addMaterial( LMaterial* pMaterial ) { m_materials.push_back( pMaterial ); }

		LVec3 getPosition(){ return m_pos; }

		vector<LMaterial*> getMaterials() { return m_materials; }

		void render() override;


	};



}