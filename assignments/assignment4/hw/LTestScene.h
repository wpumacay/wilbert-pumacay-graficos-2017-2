
#pragma once

#include "../LScene.h"
#include "../LFixedCamera3d.h"
#include "../LFpsCamera.h"
#include "../../Config.h"

using namespace std;
using namespace engine;

namespace hw
{

    class LTestScene : public LScene
    {
        private :

        public :

        LTestScene()
        {
            addCamera( new LFpsCamera( LVec3( 0.0f, 0.0f, 0.0f ),
                                       LVec3( 0.0f, 1.0f, 0.0f ) ) );

            m_projMatrix = glm::perspective( glm::radians( 45.0f ),
                                             ( float ) APP_WIDTH / APP_HEIGHT,
                                             0.1f, 100.0f );

            addTerrainGenerator( new LTerrainGenerator( this ) );
        }

    };


}