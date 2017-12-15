
#pragma once

#include "LCommon.h"
#include "LTexture.h"

#define MAT_DEFAULT_PLAIN     LVec3( 0.0f, 1.0f, 0.0f )
#define MAT_DEFAULT_AMBIENT   LVec3( 0.2f, 0.2f, 0.2f )
#define MAT_DEFAULT_DIFFUSE   LVec3( 0.0f, 1.0f, 0.0f )
#define MAT_DEFAULT_SPECULAR  LVec3( 0.0f, 1.0f, 0.0f )
#define MAT_DEFAULT_SHININESS 20.0f

using namespace std;

namespace engine
{

    class LMaterial
    {
        private :

        LTexture* m_texture;

        public :

        LVec3 plainColor;
        
        LVec3 ambient;
        LVec3 diffuse;
        LVec3 specular;
        float shininess;

        LMaterial()
        {
            this->ambient    = MAT_DEFAULT_AMBIENT;
            this->diffuse    = MAT_DEFAULT_DIFFUSE;
            this->specular   = MAT_DEFAULT_SPECULAR;
            this->shininess  = MAT_DEFAULT_SHININESS;

            this->plainColor = MAT_DEFAULT_PLAIN;

            m_texture = NULL;
        }

        LMaterial( const LVec3& cAmbient, 
                   const LVec3& cDiffuse,
                   const LVec3& cSpecular,
                   const LVec3& cPlainColor,
                   float cShininess )
        {
            this->ambient   = cAmbient;
            this->diffuse   = cDiffuse;
            this->specular  = cSpecular;
            this->shininess = cShininess;

            this->plainColor = cPlainColor;

            m_texture = NULL;
        }

        ~LMaterial()
        {
            if ( m_texture != NULL )
            {
                delete m_texture;
            }            
        }

        void setTexture( LTexture* pTexture )
        {
            if ( m_texture != NULL )
            {
                delete m_texture;
            }

            m_texture = pTexture;
        }

        LTexture* getTexture() { return m_texture; }

    };

}


