
#pragma once

#include "../LScene.h"
#include "../LFixedCamera3d.h"
#include "../LFpsCamera.h"
#include "../LLightDirectional.h"
#include "../LMeshBuilder.h"
#include "../LEntity.h"
#include "../../Config.h"

using namespace std;
using namespace engine;

namespace hw
{

    class LTestScene : public LScene
    {
        private :

        LEntity* m_entity;

        public :

        LTestScene()
        {
            glEnable( GL_DEPTH_TEST );

            addCamera( new LFpsCamera( LVec3( -2.0f, 5.0f, 2.0f ),
                                       LVec3( 0.0f, 1.0f, 0.0f ) ) );



            addLight( new LLightDirectional( LVec3( 0.2f, 0.2f, 0.2f ), 
                                             LVec3( 1.0f, 1.0f, 1.0f ),
                                             LVec3( 1.0f, 1.0f, 1.0f ), 
                                             0, 
                                             LVec3( -0.0f, -1.0f, -0.0f ) ) );

            m_projMatrix = glm::perspective( glm::radians( 75.0f ),
                                             ( float ) APP_WIDTH / APP_HEIGHT,
                                             0.1f, 50.0f );

            // auto _mesh = LMeshBuilder::createBox( 1.0f, 1.0f, 1.0f );
            auto _mesh = LMeshBuilder::createFromObj( "res/models/pokemons/lizardon.obj" );
            _mesh->drawEnvMapped = true;
            
            m_entity = new LEntity( _mesh );
            addEntity( m_entity );

            m_entity->pos.x = -2.5f;
            m_entity->pos.y = 7.5f;
            m_entity->pos.z = -2.5f;

            m_entity->scale = LVec3( 0.25, 0.25, 0.25 );

            addTerrainGenerator( new LTerrainGenerator( this ) );

            addSkybox( new LSkybox( "space" ) );
        }

        void update( float dt ) override
        {
            LScene::update( dt );

            float _dtheta = 0.25 * dt;
            glm::mat4 _rot = glm::rotate( _dtheta, glm::vec3( 1, 1, 1 ) );
            m_entity->rotation = _rot * m_entity->rotation;
        }

    };


}