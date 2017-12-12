

#include "LSceneRenderer.h"
#include "LShaderManager.h"
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
        disableLighting();
    }

    LSceneRenderer::~LSceneRenderer()
    {

    }

    void LSceneRenderer::enableLighting()
    {
        m_lightingEnabled = true;
        LShaderManager::INSTANCE->currentShader = LShaderManager::INSTANCE->programs["basic3d_lighting"];
        m_shader = LShaderManager::INSTANCE->currentShader;

        m_uniformProj = glGetUniformLocation( m_shader, "u_tProj" );
        m_uniformView = glGetUniformLocation( m_shader, "u_tView" );
        m_uniformModel = glGetUniformLocation( m_shader, "u_tModel" );

        m_uniformNumDirectionalLights = glGetUniformLocation( m_shader, "u_numDirectionalLights" );
        m_uniformNumPointLights       = glGetUniformLocation( m_shader, "u_numPointLights" );
        m_uniformNumSpotLights        = glGetUniformLocation( m_shader, "u_numSpotLights" );;

        m_uniformViewPos = glGetUniformLocation( m_shader, "u_viewPos" );
        m_uniformGlobalLight = glGetUniformLocation( m_shader, "u_globalAmbientLight" );
    }

    void LSceneRenderer::disableLighting()
    {
        m_lightingEnabled = false;
        LShaderManager::INSTANCE->currentShader = LShaderManager::INSTANCE->programs["basic3d"];
        m_shader = LShaderManager::INSTANCE->currentShader;

        m_uniformProj = glGetUniformLocation( m_shader, "u_tProj" );
        m_uniformView = glGetUniformLocation( m_shader, "u_tView" );
        m_uniformModel = glGetUniformLocation( m_shader, "u_tModel" );
    }

    void LSceneRenderer::begin( LScene* pScene )
    {
        glUseProgram( m_shader );

        auto _fog = pScene->getFog();

        if ( _fog != NULL )
        {
            
            GLuint u_fog_type       = glGetUniformLocation( m_shader, "u_fog.type" );
            GLuint u_fog_color      = glGetUniformLocation( m_shader, "u_fog.color" );
            GLuint u_fog_density    = glGetUniformLocation( m_shader, "u_fog.density" );
            GLuint u_fog_start      = glGetUniformLocation( m_shader, "u_fog.start" );
            GLuint u_fog_end        = glGetUniformLocation( m_shader, "u_fog.end" );
            GLuint u_fog_active     = glGetUniformLocation( m_shader, "u_fog.isActive" );

            glUniform1i( u_fog_type, _fog->type );
            glUniform4f( u_fog_color, _fog->color.x, _fog->color.y, _fog->color.z, _fog->color.w );
            glUniform1f( u_fog_density, _fog->density );
            glUniform1f( u_fog_start, _fog->start );
            glUniform1f( u_fog_end, _fog->end );
            glUniform1i( u_fog_active, _fog->isActive );

            // cout << "isActive: " << _fog->isActive << endl;
        }

        glUniformMatrix4fv( m_uniformProj, 1, GL_FALSE, glm::value_ptr( pScene->getProjMatrix() ) );
        glUniformMatrix4fv( m_uniformView, 1, GL_FALSE, glm::value_ptr( pScene->getCurrentCamera()->getViewMatrix() ) );

        if ( m_lightingEnabled )
        {
            auto _viewPos = pScene->getCurrentCamera()->getPosition();
            //cout << "_viewPos: " << _viewPos.toString() << endl;
            glUniform3f( m_uniformViewPos, _viewPos.x, _viewPos.y, _viewPos.z );
            glUniform3f( m_uniformGlobalLight, 1.0f, 1.0f, 1.0f );

            glUniform1i( m_uniformNumDirectionalLights, LLightDirectional::s_count );
            glUniform1i( m_uniformNumPointLights, LLightPoint::s_count );
            glUniform1i( m_uniformNumSpotLights, LLightSpot::s_count );

            auto _lights = pScene->getLights();

            for ( LILight* _light : _lights )
            {
                _light->bind();
            }
        }

    }

    void LSceneRenderer::renderScene( LScene* pScene )
    {
        auto _entities = pScene->getEntities();
        for ( LEntity* _entity : _entities )
        {
            LMeshComponent* _meshComponent = _entity->getComponent<LMeshComponent>();
            LMesh* _mesh = _meshComponent->getMesh();
            glUniformMatrix4fv( m_uniformModel, 1, GL_FALSE, glm::value_ptr( _mesh->getModelMatrix() ) );
            render( _mesh );
        }
    }

    void LSceneRenderer::render( LIRenderable* pRenderable )
    {
        pRenderable->render();
    }

    void LSceneRenderer::end( LScene* pScene )
    {
        if ( m_lightingEnabled )
        {
            auto _lights = pScene->getLights();
            for ( LILight* _light : _lights )
            {
                _light->unbind();
            }
        }        

        glUseProgram( 0 );
    }

}