
// Implementation of the perlin noise function based on these references :
/*
* c++ implementation of perlin3d https://github.com/sol-prog/Perlin_Noise/blob/master/PerlinNoise.cpp
* javascript implementation of perlin2d https://github.com/josephg/noisejs/blob/master/perlin.js
*/

#pragma once

#include "LCommon.h"

#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;

namespace engine
{
	
	class LHeightmapGenerator
	{

		private :

		vector<int> permutations;

		float _fade( float t );
		float _lerp( float a, float b, float t );
		float _dotgrad( int hash, float x, float y );
		float _perlin2d( float x, float y );

		public :

		LHeightmapGenerator();
		~LHeightmapGenerator();


		float getHeight( float x, float y );

	};

}

