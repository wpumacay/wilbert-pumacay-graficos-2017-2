

#pragma once

#include "LCommon.h"

namespace engine
{

    namespace light
    {
        enum _light
        {
            TYPE_BASE,
            TYPE_DIRECTIONAL,
            TYPE_POSITIONAL,
            TYPE_SPOT
        };
    }


    class LILight
    {

        protected :

        int m_indx;
        light::_light m_type;

        public :

        LVec3 ambient;
        LVec3 diffuse;
        LVec3 specular;

        int isActive;

        LILight( const LVec3& ambient,
                 const LVec3& diffuse,
                 const LVec3& specular,
                 int lIndx )
        {
            this->ambient = ambient;
            this->diffuse = diffuse;
            this->specular = specular;
            this->isActive = 1;

            m_indx = lIndx;
        }

        ~LILight()
        {
            
        }

        static light::_light getStaticType()
        {
            return light::TYPE_BASE;
        }

        light::_light getType() { return m_type; }
        int getIndx() { return m_indx; }

    };




}