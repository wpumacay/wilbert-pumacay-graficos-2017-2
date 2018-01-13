
#include "LTerrainPatch.h"



namespace engine
{


	LTerrainPatch::LTerrainPatch( float xp, float zp,
								  GLfloat patchWidth, GLfloat patchDepth,
								  int patchWidthDiv, int patchDepthDiv,
								  LHeightmapGenerator* pGenerator )
	{
		// std::cout << "created new patch" << std::endl;

		m_pos.x = xp;
		m_pos.z = zp;

		m_patchWidth = patchWidth;
		m_patchDepth = patchDepth;

		m_patchWidthDiv = patchWidthDiv;
		m_patchDepthDiv = patchDepthDiv;

		m_generator = pGenerator;

		// create the buffers according to the dimensions required
		// Every subgrid has a total of 6 vertices ( repeating vertices for normals )

		m_terrainVertices = vector<LVec3>( 6 * m_patchWidthDiv * m_patchDepthDiv );
		m_terrainNormals = vector<LVec3>( 6 * m_patchWidthDiv * m_patchDepthDiv );

		m_terrainVertBuff = new LVertexBuffer();
		m_terrainNormBuff = new LVertexBuffer();

		m_terrainVao = new LVertexArray();

		resample( m_pos.x, m_pos.z );

		m_terrainVao->addBuffer( m_terrainVertBuff, 0 );
		m_terrainVao->addBuffer( m_terrainNormBuff, 1 );

		m_isWireframe = true;
	}

	LTerrainPatch::~LTerrainPatch()
	{
		m_terrainVertBuff = NULL;
		m_terrainNormBuff = NULL;

		delete m_terrainVao;

		m_terrainVertices.clear();
		m_terrainNormals.clear();
	}

	void LTerrainPatch::resample( float patchX, float patchZ )
	{
		m_pos.x = patchX;
		m_pos.z = patchZ;

		// Create traingle grid again

		float _dw = m_patchWidth / m_patchWidthDiv;
		float _dd = m_patchDepth / m_patchDepthDiv;

		for ( int i = 0; i < m_patchDepthDiv; i++ )
		{
			for ( int j = 0; j < m_patchWidthDiv; j++ )
			{
				// Fill the vertices, normal

				float _xg = m_pos.x + j * _dw - 0.5 * m_patchWidth;
				float _zg = m_pos.z + i * _dd - 0.5 * m_patchDepth;

				LVec3 _p0( _xg +   0, 2.5 * _getHeight( _xg +   0, _zg +   0 ), _zg +   0 );
				LVec3 _p1( _xg +   0, 2.5 * _getHeight( _xg +   0, _zg + _dd ), _zg + _dd );
				LVec3 _p2( _xg + _dw, 2.5 * _getHeight( _xg + _dw, _zg + _dd ), _zg + _dd );
				LVec3 _p3( _xg + _dw, 2.5 * _getHeight( _xg + _dw, _zg +   0 ), _zg +   0 );

				m_terrainVertices[ 6 * ( j + i * m_patchWidthDiv ) + 0 ] = _p0;
				m_terrainVertices[ 6 * ( j + i * m_patchWidthDiv ) + 1 ] = _p1;
				m_terrainVertices[ 6 * ( j + i * m_patchWidthDiv ) + 2 ] = _p2;
				m_terrainVertices[ 6 * ( j + i * m_patchWidthDiv ) + 3 ] = _p0;
				m_terrainVertices[ 6 * ( j + i * m_patchWidthDiv ) + 4 ] = _p2;
				m_terrainVertices[ 6 * ( j + i * m_patchWidthDiv ) + 5 ] = _p3;

				LVec3 _n0 = LVec3::cross( _p1 - _p0, _p2 - _p0 );
				LVec3 _n1 = LVec3::cross( _p2 - _p0, _p3 - _p0 );

				m_terrainNormals[ 6 * ( j + i * m_patchWidthDiv ) + 0 ] = _n0;
				m_terrainNormals[ 6 * ( j + i * m_patchWidthDiv ) + 1 ] = _n0;
				m_terrainNormals[ 6 * ( j + i * m_patchWidthDiv ) + 2 ] = _n0;
				m_terrainNormals[ 6 * ( j + i * m_patchWidthDiv ) + 3 ] = _n1;
				m_terrainNormals[ 6 * ( j + i * m_patchWidthDiv ) + 4 ] = _n1;
				m_terrainNormals[ 6 * ( j + i * m_patchWidthDiv ) + 5 ] = _n1;
			}
		}

		m_terrainVertBuff->setData( sizeof( LVec3 ) * m_terrainVertices.size(),
									3, ( GLfloat* ) m_terrainVertices.data() );
		m_terrainNormBuff->setData( sizeof( LVec3 ) * m_terrainNormals.size(),
									3, ( GLfloat* ) m_terrainNormals.data() );

	}

	void LTerrainPatch::render()
	{
		if ( m_isWireframe )
		{
			glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
		}

		m_terrainVao->bind();

		glDrawArrays( GL_TRIANGLES, 0, m_terrainVertices.size() );

		m_terrainVao->unbind();

	 	if ( m_isWireframe )
		{
			glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
		}
	}


	float LTerrainPatch::_getHeight( float x, float z )
	{
		if ( m_generator == NULL )
		{
			return 0.0f;
		}

		return m_generator->getHeight( x, z );
	}

}