

#include "LMesh.h"
#include "LMeshBuilder.h"

using namespace std;

namespace engine
{


    LMesh::LMesh( const vector<LVec3>& vertices, 
                  const vector<LVec3>& normals,
                  const vector<LVec2>& texCoords )
    {
        m_usesIndices = false;

        type = "base";
        m_vertices = vertices;
        m_normals = normals;
        m_texCoords = texCoords;

        m_vBuffer = new LVertexBuffer();
        m_vBuffer->setData( sizeof( LVec3 ) * vertices.size(),
                            3, (GLfloat*) vertices.data() );

        m_nBuffer = new LVertexBuffer();
        m_nBuffer->setData( sizeof( LVec3 ) * normals.size(),
                            3, (GLfloat*) normals.data() );

        m_tBuffer = new LVertexBuffer();
        m_tBuffer->setData( sizeof( LVec2 ) * texCoords.size(),
                            2, ( GLfloat* ) texCoords.data() );

        m_indexBuffer = NULL;

        m_vertexArray = new LVertexArray();
        m_vertexArray->addBuffer( m_vBuffer, 0 );
        m_vertexArray->addBuffer( m_nBuffer, 1 );
        m_vertexArray->addBuffer( m_tBuffer, 2 );

        // Create a default material
        m_material = new LMaterial();

        scale = LVec3( 1.0f, 1.0f, 1.0f );

        drawAsWireframe = false;
        drawEnvMapped = false;

        rotation = glm::mat4( 1.0f );
    }

    LMesh::LMesh( const vector<LVec3>& vertices, 
                  const vector<LVec3>& normals,
                  const vector<LInd3>& indices )
    {
        type = "base";
        m_usesIndices = true;

        m_vertices = vertices;
        m_normals = normals;
        m_indices = indices;

        m_vBuffer = new LVertexBuffer();
        m_vBuffer->setData( sizeof( LVec3 ) * vertices.size(),
                            3, (GLfloat*) vertices.data() );

        m_nBuffer = new LVertexBuffer();
        m_nBuffer->setData( sizeof( LVec3 ) * normals.size(),
                            3, (GLfloat*) normals.data() );

        m_tBuffer = NULL;// no textures by default

        m_vertexArray = new LVertexArray();
        m_vertexArray->addBuffer( m_vBuffer, 0 );
        m_vertexArray->addBuffer( m_nBuffer, 1 );

        m_indexBuffer = new LIndexBuffer();
        m_indexBuffer->setData( sizeof( LInd3 ) * indices.size(), 
                                3 * indices.size(), (GLuint*) indices.data() );

        // Create a default material
        m_material = new LMaterial();

        scale = LVec3( 1.0f, 1.0f, 1.0f );

        drawAsWireframe = false;
        drawEnvMapped = false;

        rotation = glm::mat4( 1.0f );
    }

    LMesh::~LMesh()
    {
        m_vBuffer = NULL;
        m_nBuffer = NULL;
        m_tBuffer = NULL;

        delete m_vertexArray;

        if ( m_indexBuffer != NULL )
        {
            delete m_indexBuffer;
        }
            
        delete m_material;
    }

    void LMesh::setMaterial( LMaterial* pMaterial )
    { 
        delete m_material;
        m_material = pMaterial;
    }

    glm::mat4 LMesh::getModelMatrix()
    {
        glm::mat4 _model = glm::mat4( 1.0f );

        _model = glm::scale( glm::vec3( scale.x, scale.y, scale.z ) ) * _model;
        _model = rotation * _model;
        _model = glm::translate( glm::vec3( pos.x, pos.y, pos.z ) ) * _model;

        return _model;
    }

    void LMesh::setTexture( LTexture* pTexture, const vector<LVec2>& texCoord )
    {
        m_material->setTexture( pTexture );

        m_tBuffer = new LVertexBuffer();
        m_tBuffer->setData( sizeof( LVec2 ) * texCoord.size(),
                            2, ( GLfloat* ) texCoord.data() );

        m_vertexArray->addBuffer( m_tBuffer, 2 );
    }

    bool LMesh::isTextured()
    {
        if ( m_material->getTexture() != NULL )
        {
            if ( m_material->getTexture()->enabled )
            {
                return true;
            }
        }

        return false;
    }

    void LMesh::render()
    {

        if ( drawAsWireframe )
        {
            glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
        }

        if ( m_usesIndices )
        {
            m_vertexArray->bind();
            m_indexBuffer->bind();

            glDrawElements( GL_TRIANGLES, 
                            m_indexBuffer->getCount(), 
                            GL_UNSIGNED_INT, 0 );

            m_indexBuffer->unbind();
            m_vertexArray->unbind();
        }
        else
        {
            // cout << "drawing?? " << m_vertices.size() << endl;

            m_vertexArray->bind();

            glDrawArrays( GL_TRIANGLES, 
                          0, 
                          m_vertices.size() );

            m_vertexArray->unbind();
        }


        if ( drawAsWireframe )
        {
            glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
        }

    }


    void LMesh::recomputeNormals( bool useSmoothShading )
    {
        if ( type != string( "sphere" ) )
        {
            return;
        }

        if ( !useSmoothShading )
        {
            m_nBuffer->setData( sizeof( LVec3 ) * m_normals.size(),
                                3, (GLfloat*) m_normals.data() );
        }
        else
        {
            vector<LVec3> _normals;
            for ( int q = 0; q < m_vertices.size(); q++ )
            {
                LVec3 _n( 0.0f, 0.0f, 0.0f );
                LVec3 _v = m_vertices[q];

                for ( int t = 0; t < m_indices.size(); t++ )
                {   
                    LInd3 _triInd = m_indices[t];

                    int i1 = _triInd.tri.i1;
                    int i2 = _triInd.tri.i2;
                    int i3 = _triInd.tri.i3;

                    LVec3 v1 = m_vertices[i1];
                    LVec3 v2 = m_vertices[i2];
                    LVec3 v3 = m_vertices[i3];

                    if ( LVec3::equal( _v, v1 ) || LVec3::equal( _v, v2 ) || LVec3::equal( _v, v3 ) )
                    {
                        _n = _n + LMeshBuilder::_computeFaceNormal( m_vertices[i1], m_vertices[i2], m_vertices[i3], true );
                    }
                }
                _n.normalize();
                _normals.push_back( _n );
            }

            m_nBuffer->setData( sizeof( LVec3 ) * _normals.size(),
                                3, (GLfloat*) _normals.data() );
        }
    }

}