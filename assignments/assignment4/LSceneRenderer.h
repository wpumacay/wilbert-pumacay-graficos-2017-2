

#pragma once

#include "LIRenderer.h"
#include "LScene.h"
#include "LMesh.h"
#include "LTerrainPatch.h"
#include "LSkybox.h"
//#include "LShadowMap.h"

using namespace std;

#define DEFAULT_GLOBAL_LIGHT LVec3( 0.7f, 0.7f, 0.7f )

namespace engine
{

    class LSceneRenderer : public LIRenderer
    {

        private :

        bool m_lightingEnabled;
        bool m_shadowsEnabled;

        //LShadowMap* m_shadowMap;

        LVec3 m_globalLight;

        vector<LMesh*> m_nonTexturedRenderables;
        vector<LMesh*> m_texturedRenderables;
        vector<LMesh*> m_envMappedRenderables;

        void _configureShadowmapping();

        void _renderTextured( LScene* pScene );
        void _renderNonTextured( LScene* pScene );
        void _renderEnvMapped( LScene* pScene );
        void _renderTerrainPatches( LScene* pScene );
        void _renderSkybox( LScene* pScene );

        public :


        LSceneRenderer();
        ~LSceneRenderer();

        void enableLighting() { m_lightingEnabled = true; }
        void disableLighting() { m_lightingEnabled = false; }

        void enableShadows() { m_shadowsEnabled = true; }
        void disableShadows() { m_shadowsEnabled = false; }

        void renderScene( LScene* pScene ) override;
        void render( LIRenderable* pRenderable ) override;
        void begin( LScene* pScene ) override;
        void end( LScene* pScene ) override;
    };





}



