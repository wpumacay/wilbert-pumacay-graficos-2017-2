
#pragma once

#include "LVertexBuffer.h"


namespace engine
{

    /*
    * This class implements a terrain that is calculated using perlin noise in gpu
    * Holds a grid with given level of detail, and gives it to the vertex shader to ...
    * take care of the terrain construction
    */
    class LGpuTerrain
    {

        LVertexBuffer* m_terrainVertBuff;

        vector<LVec3> m_terrainVertices;

        GLfloat m_patchWidth;
        GLfloat m_patchDepth;

        int m_patchWidthDiv;
        int m_patchDepthDiv;





    };




    
}
