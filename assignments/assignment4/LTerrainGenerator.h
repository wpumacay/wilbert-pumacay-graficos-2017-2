
#pragma once

#include "LScene.h"
#include "LTerrainPatch.h"
#include "LHeightmapGenerator.h"

#define TERRAIN_INIT_PATCHS_WINDOW 1
#define TERRAIN_PATCH_AREA 20
#define TERRAIN_PATCH_MIN_DIV 10
#define TERRAIN_PATCH_BASE_DIV 200
#define TERRAIN_PATCH_MAX_DIV 200

namespace engine
{

    class LScene;

	class LTerrainGenerator
	{
        private :

        vector<LTerrainPatch*> m_terrainPatches;
        LScene* m_scene;

        LHeightmapGenerator* m_heightmapGenerator;

        public :

		LTerrainGenerator( LScene* pScene );
		~LTerrainGenerator();

		void update( float dt );

        vector<LTerrainPatch*>& getTerrainPatches() { return m_terrainPatches; }
	};
	
}