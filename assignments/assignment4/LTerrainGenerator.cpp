
#include "LTerrainGenerator.h"




namespace engine
{

    LTerrainGenerator::LTerrainGenerator( LScene* pScene )
    {
        m_scene = pScene;

        m_heightmapGenerator = new LHeightmapGenerator();

        for ( int i = -TERRAIN_INIT_PATCHS_WINDOW; i <= TERRAIN_INIT_PATCHS_WINDOW; i++ )
        {
            for ( int j = -TERRAIN_INIT_PATCHS_WINDOW; j <= TERRAIN_INIT_PATCHS_WINDOW; j++ )
            {
                float _xp = j * TERRAIN_PATCH_AREA;
                float _zp = i * TERRAIN_PATCH_AREA;

                auto _terrainPatch = new LTerrainPatch( _xp, _zp,
                                                        TERRAIN_PATCH_AREA, TERRAIN_PATCH_AREA, 
                                                        TERRAIN_PATCH_BASE_DIV, TERRAIN_PATCH_BASE_DIV,
                                                        m_heightmapGenerator );

                m_terrainPatches.push_back( _terrainPatch );
            }
        }
    }

    LTerrainGenerator::~LTerrainGenerator()
    {
        m_scene = NULL;

        for ( LTerrainPatch* _terrainPatch : m_terrainPatches )
        {
            delete _terrainPatch;
        }
        m_terrainPatches.clear();

        if ( m_heightmapGenerator != NULL )
        {
            delete m_heightmapGenerator;
            m_heightmapGenerator = NULL;
        }
    }



    void LTerrainGenerator::update( float dt )
    {

    }

}