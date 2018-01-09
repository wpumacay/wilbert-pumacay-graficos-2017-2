

#pragma once

#include "LCommon.h"

namespace engine
{

    class LIRenderable
    {

        public :

        virtual void render() = 0;

        virtual bool isTextured() { return false; }
    };

}