

#pragma once

#include "LIRenderer.h"
#include "LScene.h"
#include "LMesh.h"

using namespace std;

#define DEFAULT_GLOBAL_LIGHT LVec3( 1.0f, 1.0f, 1.0f )

namespace engine
{

    class LSceneRenderer : public LIRenderer
    {

        private :

        bool m_lightingEnabled;

        LVec3 m_globalLight;

        vector<LMesh*> m_nonTexturedRenderables;
        vector<LMesh*> m_texturedRenderables;

        void _renderTextured( LScene* pScene );
        void _renderNonTextured( LScene* pScene );

        public :


        LSceneRenderer();
        ~LSceneRenderer();

        void enableLighting() { m_lightingEnabled = true; }
        void disableLighting() { m_lightingEnabled = false; }

        void renderScene( LScene* pScene ) override;
        void render( LIRenderable* pRenderable ) override;
        void begin( LScene* pScene ) override;
        void end( LScene* pScene ) override;
    };





}



