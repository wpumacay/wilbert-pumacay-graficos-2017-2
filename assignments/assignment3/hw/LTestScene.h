
#pragma once

#include "../LScene.h"
#include "../LFixedCamera3d.h"
#include "../LMesh.h"
#include "../LMaterial.h"
#include "../LMeshBuilder.h"
#include "../LLightDirectional.h"
#include "../LLightPoint.h"
#include "../LLightSpot.h"
#include "../LFog.h"
#include "../LTexture.h"
#include "../../Config.h"
#include "LBallEntity.h"

using namespace std;
using namespace engine;

namespace hw
{

    struct LPixel
    {
        u8 r;
        u8 g;
        u8 b;
        u8 a;
    };

    struct LImage
    {
        int width;
        int height;

        LPixel* buffer;

        LImage()
        {
            width = 0;
            height = 0;
            buffer = NULL;
        }

        LImage( int width, int height )
        {
            this->width = width;
            this->height = height;

            buffer = new LPixel[ width * height ];
        }

        ~LImage()
        {
            
        }
    };

    class LTestScene : public LScene
    {
        private :

        LBallEntity* m_ballEntity;
        LEntity* m_planeEntity;

        LLightPoint* m_mainPointLight;
        LLightSpot* m_mainSpotLight;

        LImage m_checkerboardImage;

        public :

        LTestScene()
        {
            addCamera( new LFixedCamera3d( LVec3( 7.0f, 3.0f, -10.0f ),
                                           LVec3( -7.0f, -3.0f, 10.0f ),
                                           LVec3( 0.0f, 1.0f, 0.0f ) ) );

            auto _viewMat = m_currentCamera->getViewMatrix();
            auto _invView = glm::inverse( _viewMat );
            auto _invTrans = glm::mat3( _invView );

            //auto _viewRot = glm::mat3( _viewMat );
            //auto _invTrans = glm::transpose( _viewRot );

            glm::vec3 _lightDir = _invTrans * ( glm::vec3( 0.1f, 0.0f, -1.0f ) );
            //cout << "_lightDir: " << glm::to_string( _lightDir ) << endl;
            
            //LVec3 _foo( -7.0f, -3.0f, 10.0f );
            //_foo.normalize();
            //cout << "_foo: " << _foo.toString() << endl;

            addLight( new LLightDirectional( LVec3( 0.0f, 0.0f, 0.0f ),
                                             LVec3( 0.8f, 0.8f, 0.8f ),
                                             LVec3( 0.2f, 0.2f, 0.2f ),
                                             0, LVec3( _lightDir.x, _lightDir.y, _lightDir.z ) ) );
            
            m_mainPointLight = new LLightPoint( LVec3( 0.0f, 0.0f, 0.0f ),
                                                LVec3( 1.0f, 1.0f, 1.0f ),
                                                LVec3( 1.0f, 1.0f, 1.0f ),
                                                0, LVec3( -14.0f, 12.0f, -3.0f ),
                                                2.0f, 0.01f, 0.001f );
            m_mainPointLight->isActive = 1;
            addLight( m_mainPointLight );
            
            m_mainSpotLight = new LLightSpot( LVec3( 0.0f, 0.0f, 0.0f ),
                                              LVec3( 1.0f, 1.0f, 1.0f ),
                                              LVec3( 1.0f, 1.0f, 1.0f ),
                                              0, LVec3( -14.0f, 12.0f, -3.0f ),
                                              LVec3::normalize( LVec3( -6.0f, 0.0f, -4.5f ) - LVec3( -14.0f, 12.0f, -3.0f ) ),
                                              2.0f, 0.01f, 0.001f, 20.0f, 60.0f );
            m_mainSpotLight->isActive = 0;
            addLight( m_mainSpotLight );
            
            m_projMatrix = glm::perspective( glm::radians( 45.0f ),
                                             ( float ) APP_WIDTH / APP_HEIGHT,
                                             0.1f, 100.0f );


            LMaterial* _planeMaterial = new LMaterial( LVec3( 0.2f, 0.2f, 0.2f ),
                                                       LVec3( 0.0f, 1.0f, 0.0f ),
                                                       LVec3( 0.0f, 0.0f, 0.0f ),
                                                       LVec3( 0.0f, 1.0f, 0.0f ),
                                                       20.0f );

            LMesh* _planeMesh  = LMeshBuilder::createPlane( 10.0f, 12.0f );

            _planeMesh->setMaterial( _planeMaterial );

            m_planeEntity = new LEntity( _planeMesh );
            m_planeEntity->pos = LVec3( 0.0f, 0.0f, 2.0f );

            m_ballEntity = new LBallEntity( LVec3( 3.0f, 1.0f, 5.0f ) );

            addEntity( m_ballEntity );
            addEntity( m_planeEntity );

            LFog* _fog = new LFog( FOG_TYPE_LINEAR, 
                                   LVec4( 0.7, 0.7, 0.7, 0.5 ),
                                   0.09,
                                   0.0f, 18.0f );

            //LFog* _fog = new LFog( FOG_TYPE_EXP, 
            //                       LVec4( 0.7, 0.7, 0.7, 0.5 ),
            //                       0.09,
            //                       0.0f, 18.0f );

            //LFog* _fog = new LFog( FOG_TYPE_EXP_SQUARE, 
            //                       LVec4( 0.7, 0.7, 0.7, 0.5 ),
            //                       0.09,
            //                       0.0f, 18.0f );

            addFog( _fog );

            createCheckerboardImage();

            LTexture* _texture = new LTexture();
            _texture->setData( ( u8* ) m_checkerboardImage.buffer, 
                               GL_RGBA,
                               m_checkerboardImage.width,
                               m_checkerboardImage.height,
                               0 );

            vector<LVec2> _texCoord;
            _texCoord.push_back( LVec2( 0.0f, 0.0f ) );
            _texCoord.push_back( LVec2( 0.0f, 1.25f ) );
            _texCoord.push_back( LVec2( 1.5f, 1.25f ) );
            _texCoord.push_back( LVec2( 1.5f, 0.0f ) );

            _planeMesh->setTexture( _texture, _texCoord );
        }

        LBallEntity* getBall()
        {
            return m_ballEntity;
        }


        void setMainSpotLightMode( int active )
        {
            m_mainSpotLight->isActive = active;
        }

        void setMainPointLightMode( int active )
        {
            m_mainPointLight->isActive = active;
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

        void disableFog()
        {
            if ( m_fog == NULL )
            {
                return;
            }

            m_fog->isActive = 0;
        }

        void enableFog()
        {
            if ( m_fog == NULL )
            {
                return;
            }

            m_fog->isActive = 1;
        }

        void setFogType( int type )
        {
            if ( m_fog == NULL )
            {
                return;
            }

            m_fog->type = type;
        }

        void disableTexture()
        {
            auto _mesh = m_planeEntity->getComponent<LMeshComponent>()->getMesh();
            _mesh->getMaterial()->getTexture()->enabled = false;
        }

        void enableTexture()
        {
            auto _mesh = m_planeEntity->getComponent<LMeshComponent>()->getMesh();
            _mesh->getMaterial()->getTexture()->enabled = true;
        }

        void createCheckerboardImage()
        {
            int _w = 64;
            int _h = 64;

            m_checkerboardImage = LImage( _w, _h );

            // create image

            for ( int i = 0; i < _h; i++ )
            {
                for ( int j = 0; j < _w; j++ )
                {
                    if ( ( ( i & 0x8 ) == 0 ) ^ ( ( j & 0x8 ) == 0 ) )
                    {
                        m_checkerboardImage.buffer[ j + i * _w ].r = 255;
                        m_checkerboardImage.buffer[ j + i * _w ].g = 255;
                        m_checkerboardImage.buffer[ j + i * _w ].b = 255;
                    }
                    else
                    {
                        m_checkerboardImage.buffer[ j + i * _w ].r = 0;
                        m_checkerboardImage.buffer[ j + i * _w ].g = 150;
                        m_checkerboardImage.buffer[ j + i * _w ].b = 0;
                    }
                    m_checkerboardImage.buffer[ j + i * _w ].a = 255;
                }
            }

        }

    };


}