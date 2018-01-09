
#pragma once

#include "../LScene.h"
#include "../LFixedCamera3d.h"
#include "../LTerrainPatch.h"
#include "../LHeightmapGenerator.h"
#include "../../Config.h"

using namespace std;
using namespace engine;

namespace hw
{

    class LTestScene : public LScene
    {
        private :

        LHeightmapGenerator* m_heightmapGenerator;

        public :

        LTestScene()
        {
            addCamera( new LFixedCamera3d( LVec3( 7.0f, 3.0f, -10.0f ),
                                           LVec3( -7.0f, -3.0f, 10.0f ),
                                           LVec3( 0.0f, 1.0f, 0.0f ) ) );

            m_projMatrix = glm::perspective( glm::radians( 45.0f ),
                                             ( float ) APP_WIDTH / APP_HEIGHT,
                                             0.1f, 100.0f );

            m_heightmapGenerator = new LHeightmapGenerator();

            auto _terrainPatch = new LTerrainPatch( 20, 20, 100, 100, m_heightmapGenerator );
            addTerrainPatch( _terrainPatch );
        }

        void increaseCamera( float dx, float dy, float dz )
        {
            LVec3 _cpos = m_currentCamera->getPosition();

            _cpos.x += dx;
            _cpos.y += dy;
            _cpos.z += dz;

            m_currentCamera->setPosition( _cpos );
        }

        void resetCamera()
        {
            m_currentCamera->setPosition( LVec3( 7.0f, 3.0f, -10.0f ) );
        }

    };


}