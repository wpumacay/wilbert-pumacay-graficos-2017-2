

#include "LSceneRenderer.h"
#include "LShaderManager.h"
#include "LShaderTerrainPatch.h"
#include "LShaderSkybox.h"
#include "LShaderEnvMapping.h"
#include "LEntity.h"
#include "LMeshComponent.h"
#include "LMesh.h"
#include "LLightDirectional.h"
#include "LLightPoint.h"
#include "LLightSpot.h"

using namespace std;

namespace engine
{


    LSceneRenderer::LSceneRenderer()
    {
        m_globalLight = DEFAULT_GLOBAL_LIGHT;
        disableLighting();

        //m_shadowMap = new LShadowMap();
    }

    LSceneRenderer::~LSceneRenderer()
    {

    }

    void LSceneRenderer::begin( LScene* pScene )
    {
        auto _entities = pScene->getEntities();

        for ( LEntity* _entity : _entities )
        {
            auto _mesh = ( _entity->getComponent<LMeshComponent>() )->getMesh();

            if ( _mesh->isTextured() )
            {
                m_texturedRenderables.push_back( _mesh );
            }
            else if ( _mesh->drawEnvMapped )
            {
                m_envMappedRenderables.push_back( _mesh );
            }
            else
            {
                m_nonTexturedRenderables.push_back( _mesh );
            }
        }

        if ( m_shadowsEnabled )
        {

        }
    }

    void LSceneRenderer::renderScene( LScene* pScene )
    {
        _renderTerrainPatches( pScene );
        _renderTextured( pScene );
        _renderNonTextured( pScene );

        _renderEnvMapped( pScene );
        _renderSkybox( pScene );
    }

    void LSceneRenderer::_renderEnvMapped( LScene* pScene )
    {
        LShaderEnvMapping* _shader = ( LShaderEnvMapping* ) LShaderManager::INSTANCE->programObjs["envMapping"];

        _shader->bind();

        _shader->setViewMatrix( pScene->getCurrentCamera()->getViewMatrix() );
        _shader->setProjectionMatrix( pScene->getProjMatrix() );
        _shader->setViewPosition( pScene->getCurrentCamera()->getPosition() );

        for ( LMesh* _mesh : m_envMappedRenderables )
        {
            _shader->setModelMatrix( _mesh->getModelMatrix() );

            _mesh->render();
        }

        _shader->unbind();
    }

    void LSceneRenderer::_renderSkybox( LScene* pScene )
    {
        auto _skybox = pScene->getSkybox();

        LShaderSkybox* _shader = ( LShaderSkybox* ) LShaderManager::INSTANCE->programObjs["basic3d_skybox"];

        glDepthFunc( GL_LEQUAL );

        _shader->bind();

        _shader->setViewMatrix( pScene->getCurrentCamera()->getViewMatrix() );
        _shader->setProjectionMatrix( pScene->getProjMatrix() );

        _skybox->render();

        _shader->unbind();

        glDepthFunc( GL_LESS );
    }

    void LSceneRenderer::_renderTerrainPatches( LScene* pScene )
    {
        if ( pScene->getTerrainGenerator() == NULL )
        {
            return;
        }

        LShaderTerrainPatch* _shader = ( LShaderTerrainPatch* ) LShaderManager::INSTANCE->programObjs["terrain_patch"];

        _shader->bind();

        _shader->setViewMatrix( pScene->getCurrentCamera()->getViewMatrix() );
        _shader->setProjectionMatrix( pScene->getProjMatrix() );
        
        _shader->setGlobalAmbientLight( m_globalLight );

        auto _dirLights = pScene->getLights<LLightDirectional>();
        for ( int q = 0; q < _dirLights.size(); q++ )
        {
            _shader->setLightDirectional( _dirLights[q], q );
        }
        _shader->setNumberDirectionalLights( _dirLights.size() );

        _shader->setViewPosition( pScene->getCurrentCamera()->getPosition() );

        auto _terrainPatches = pScene->getTerrainGenerator()->getTerrainPatches();
        auto _terrainMaterials = pScene->getTerrainGenerator()->getTerrainMaterials();
        auto _terrainTextures = pScene->getTerrainGenerator()->getTerrainTextures();

        for ( int m = 0; m < _terrainMaterials.size(); m++ )
        {
            _shader->setMaterial( _terrainMaterials[m], m );
        }

        for ( int m = 0; m < _terrainTextures.size(); m++ )
        {
            _terrainTextures[m]->bind();
            _shader->setTexture( _terrainTextures[m], _terrainTextures[m]->getTextureIndx() );
        }        


        for ( LTerrainPatch* _terrainPatch : _terrainPatches )
        {
            _shader->setTerrainVariation( _terrainPatch->getTerrainVariation() );
            _terrainPatch->render();
        }


        _shader->unbind();
    }

    void LSceneRenderer::_renderTextured( LScene* pScene )
    {
        if ( !m_lightingEnabled )
        {
            LShaderBasic3d* _shader = ( LShaderBasic3d* ) LShaderManager::INSTANCE->programObjs["basic3d_textured"];

            _shader->bind();

            _shader->setViewMatrix( pScene->getCurrentCamera()->getViewMatrix() );
            _shader->setProjectionMatrix( pScene->getProjMatrix() );

            for ( LMesh* _mesh : m_texturedRenderables )
            {
                _shader->setModelMatrix( _mesh->getModelMatrix() );
                _shader->setPlainColor( _mesh->getMaterial()->plainColor );
                _mesh->getMaterial()->getTexture()->bind();
                _mesh->render();
            }

            _shader->unbind();
        }
        else
        {
            LShaderLighting* _shader = ( LShaderLighting* ) LShaderManager::INSTANCE->programObjs["basic3d_lighting_textured"];

            _shader->bind();

            _shader->setViewMatrix( pScene->getCurrentCamera()->getViewMatrix() );
            _shader->setProjectionMatrix( pScene->getProjMatrix() );

            // Set lights
            _shader->setGlobalAmbientLight( m_globalLight );

            auto _dirLights = pScene->getLights<LLightDirectional>();
            for ( int q = 0; q < _dirLights.size(); q++ )
            {
                _shader->setLightDirectional( _dirLights[q], q );
            }
            _shader->setNumberDirectionalLights( _dirLights.size() );

            auto _pointLights = pScene->getLights<LLightPoint>();
            for ( int q = 0; q < _pointLights.size(); q++ )
            {
                _shader->setLightPoint( _pointLights[q], q );
            }
            _shader->setNumberPointLights( _pointLights.size() );

            auto _spotLights = pScene->getLights<LLightSpot>();
            for ( int q = 0; q < _spotLights.size(); q++ )
            {
                _shader->setLightSpot( _spotLights[q], q );
            }
            _shader->setNumberSpotLights( _spotLights.size() );

            // viewpos
            _shader->setViewPosition( pScene->getCurrentCamera()->getPosition() );

            // fog
            auto _fog = pScene->getFog();

            if ( _fog != NULL )
            {
                _shader->setFog( _fog );
            }

            // finllay, draw meshes

            for ( LMesh* _mesh : m_texturedRenderables )
            {
                _shader->setModelMatrix( _mesh->getModelMatrix() );
                _shader->setMaterial( _mesh->getMaterial() );
                _mesh->getMaterial()->getTexture()->bind();
                _mesh->render();
            }

            _shader->unbind();
        }
        
    }

    void LSceneRenderer::_renderNonTextured( LScene* pScene )
    {
        if ( !m_lightingEnabled )
        {
            LShaderBasic3d* _shader = ( LShaderBasic3d* ) LShaderManager::INSTANCE->programObjs["basic3d"];

            _shader->bind();

            _shader->setViewMatrix( pScene->getCurrentCamera()->getViewMatrix() );
            _shader->setProjectionMatrix( pScene->getProjMatrix() );

            for ( LMesh* _mesh : m_nonTexturedRenderables )
            {
                _shader->setModelMatrix( _mesh->getModelMatrix() );
                _shader->setPlainColor( _mesh->getMaterial()->plainColor );
                _mesh->render();
            }

            _shader->unbind();
        }
        else
        {
            LShaderLighting* _shader = ( LShaderLighting* ) LShaderManager::INSTANCE->programObjs["basic3d_lighting"];

            _shader->bind();

            _shader->setViewMatrix( pScene->getCurrentCamera()->getViewMatrix() );
            _shader->setProjectionMatrix( pScene->getProjMatrix() );

            // Set lights
            _shader->setGlobalAmbientLight( m_globalLight );

            auto _dirLights = pScene->getLights<LLightDirectional>();
            for ( int q = 0; q < _dirLights.size(); q++ )
            {
                _shader->setLightDirectional( _dirLights[q], q );
            }
            _shader->setNumberDirectionalLights( _dirLights.size() );

            auto _pointLights = pScene->getLights<LLightPoint>();
            for ( int q = 0; q < _pointLights.size(); q++ )
            {
                _shader->setLightPoint( _pointLights[q], q );
            }
            _shader->setNumberPointLights( _pointLights.size() );

            auto _spotLights = pScene->getLights<LLightSpot>();
            for ( int q = 0; q < _spotLights.size(); q++ )
            {
                _shader->setLightSpot( _spotLights[q], q );
            }
            _shader->setNumberSpotLights( _spotLights.size() );

            // viewpos
            _shader->setViewPosition( pScene->getCurrentCamera()->getPosition() );

            // fog
            auto _fog = pScene->getFog();

            if ( _fog != NULL )
            {
                _shader->setFog( _fog );
            }

            // finllay, draw meshes

            for ( LMesh* _mesh : m_nonTexturedRenderables )
            {
                _shader->setModelMatrix( _mesh->getModelMatrix() );
                _shader->setMaterial( _mesh->getMaterial() );
                _mesh->render();
            }

            _shader->unbind();
        }
    }

    void LSceneRenderer::render( LIRenderable* pRenderable )
    {
        // Do nothing here, the renderer pipeline is given by begin-renderscene-end
    }

    void LSceneRenderer::end( LScene* pScene )
    {
        m_nonTexturedRenderables.clear();
        m_texturedRenderables.clear();
        m_envMappedRenderables.clear();

        glUseProgram( 0 );
    }

}