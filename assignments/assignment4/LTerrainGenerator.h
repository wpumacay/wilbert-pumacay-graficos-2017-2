
#pragma once

#include "LScene.h"
#include "LTerrainPatch.h"
#include "LHeightmapGenerator.h"
#include <queue>

#define TERRAIN_INIT_PATCHS_WINDOW 3
#define TERRAIN_PATCH_AREA 10
#define TERRAIN_PATCH_MIN_DIV 10
#define TERRAIN_PATCH_BASE_DIV 100
#define TERRAIN_PATCH_MAX_DIV 100

#define TERRAIN_RANGE_FOR_RECALCULATION 2

using namespace std;

namespace engine
{

    class LScene;

	class LTerrainGenerator
	{
        private :

        vector<LTerrainPatch*> m_terrainPatches;
        LScene* m_scene;

        LHeightmapGenerator* m_heightmapGenerator;

        queue<LTerrainPatch*> m_terrainPatchesPool;

        LVec3 m_lastPosition;

        bool _isTherePatchInPosition( float x, float z );

        public :

		LTerrainGenerator( LScene* pScene );
		~LTerrainGenerator();

		void update( float dt );

        vector<LTerrainPatch*>& getTerrainPatches() { return m_terrainPatches; }
	};
	
}