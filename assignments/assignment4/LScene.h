
#pragma once

#include "LCommon.h"
#include "LILight.h"
#include "LLightDirectional.h"
#include "LLightDirectional.h"
#include "LLightDirectional.h"
#include "LEntity.h"
#include "LICamera.h"
#include "LFog.h"
#include "LTerrainPatch.h"

using namespace std;

namespace engine
{


    class LScene
    {

        protected :

        vector<LILight*> m_lights;
        vector<LEntity*> m_entities;
        vector<LICamera*> m_cameras;

        vector<LTerrainPatch*> m_terrainPatches;

        LICamera* m_currentCamera;

        glm::mat4 m_projMatrix;

        LFog* m_fog;

        public :


        LScene();
        ~LScene();

        void addLight( LILight* pLight ) { m_lights.push_back( pLight ); }
        void addFog( LFog* pFog );
        void addEntity( LEntity* pEntity ) { m_entities.push_back( pEntity ); }
        void addCamera( LICamera* pCamera ) 
        { 
            m_cameras.push_back( pCamera );
            if ( m_currentCamera == NULL )
            {
                m_currentCamera = pCamera;
            }
        }

        void addTerrainPatch( LTerrainPatch* pTerrainPatch ) { m_terrainPatches.push_back( pTerrainPatch ); }
        vector<LTerrainPatch*>& getTerrainPatches() { return m_terrainPatches; }

        glm::mat4 getProjMatrix() { return m_projMatrix; }
        LICamera* getCurrentCamera() { return m_currentCamera; }
        vector<LILight*>& getLights() { return m_lights; }
        vector<LEntity*>& getEntities() { return m_entities; }

        template< class T >
        vector<T*> getLights()
        {
            auto _type = T::getStaticType();

            vector<T*> _lights;

            for ( LILight* _light : m_lights )
            {
                if ( _light->getType() == _type )
                {
                    _lights.push_back( ( T* ) _light );
                }
            }

            return _lights;
        }

        LFog* getFog() { return m_fog; }

        void update( float dt );

        void setShadingMode( bool useSmoothShading );

    };





}