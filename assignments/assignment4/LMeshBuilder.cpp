
#include "LMeshBuilder.h"

#include <map>

using namespace std;

namespace engine
{

    LMesh* LMeshBuilder::createBox( GLfloat width, GLfloat height, GLfloat depth )
    {
        LMesh* _mesh = NULL;

        vector<LVec3> _vertices;
        vector<LVec3> _normals;
        vector<LInd3> _indices;

        vector<LVec3> _normalsSource;

        _normalsSource.push_back( LVec3(  0,  0,  1 ) );
        _normalsSource.push_back( LVec3(  0,  0, -1 ) );
        _normalsSource.push_back( LVec3(  0,  1,  0 ) );
        _normalsSource.push_back( LVec3(  0, -1,  0 ) );
        _normalsSource.push_back( LVec3(  1,  0,  0 ) );
        _normalsSource.push_back( LVec3( -1,  0,  0 ) );

        LVec3 _scale( 0.5 * width, 0.5 * height, 0.5 * depth );

        // for each face, compute the vertices that form ...
        // the face perpendicular to that normal
        for ( int q = 0; q < _normalsSource.size(); q++ )
        {
            LVec3 _n = _normalsSource[q];

            // form a tri perpendicular right hand system
            LVec3 _s1 = LVec3( _n.y, _n.z, _n.x );
            LVec3 _s2 = LVec3::cross( _n, _s1 );

            // Add the indices accordingly
            _indices.push_back( LInd3( _vertices.size(),
                                       _vertices.size() + 1,
                                       _vertices.size() + 2 ) );

            _indices.push_back( LInd3( _vertices.size(),
                                       _vertices.size() + 2,
                                       _vertices.size() + 3 ) );

            // Generate each vertex of each face ...
            // according to these vectors
            LVec3 _v;

            _v = _n - _s1 - _s2;
            _v.scale( _scale.x, _scale.y, _scale.z );

            _vertices.push_back( _v );
            _normals.push_back( _n );

            _v = _n - _s1 + _s2;
            _v.scale( _scale.x, _scale.y, _scale.z );

            _vertices.push_back( _v );
            _normals.push_back( _n );

            _v = _n + _s1 + _s2;
            _v.scale( _scale.x, _scale.y, _scale.z );

            _vertices.push_back( _v );
            _normals.push_back( _n );

            _v = _n + _s1 - _s2;
            _v.scale( _scale.x, _scale.y, _scale.z );

            _vertices.push_back( _v );
            _normals.push_back( _n );

        }


        _mesh = new LMesh( _vertices, _normals, _indices );

        return _mesh;
    }
    
    LMesh* LMeshBuilder::createPlane( GLfloat width, GLfloat depth )
    {
        LMesh* _mesh = NULL;

        vector<LVec3> _vertices;
        vector<LVec3> _normals;
        vector<LInd3> _indices;


        LVec3 _n = LVec3( 0.0f, 1.0f, 0.0f );
        LVec3 _s1 = LVec3( 0.0f, 0.0f, 1.0f );
        LVec3 _s2 = LVec3( 1.0f, 0.0f, 0.0f );

        LVec3 _scale = LVec3( 0.5 * width, 0.0f, 0.5 * depth );

        _indices.push_back( LInd3( _vertices.size(),
                                   _vertices.size() + 1,
                                   _vertices.size() + 2 ) );

        _indices.push_back( LInd3( _vertices.size(),
                                   _vertices.size() + 2,
                                   _vertices.size() + 3 ) );

        LVec3 _v;

        _v = _n - _s1 - _s2;
        _v.scale( _scale.x, _scale.y, _scale.z );

        _vertices.push_back( _v );
        _normals.push_back( _n );

        _v = _n - _s1 + _s2;
        _v.scale( _scale.x, _scale.y, _scale.z );

        _vertices.push_back( _v );
        _normals.push_back( _n );

        _v = _n + _s1 + _s2;
        _v.scale( _scale.x, _scale.y, _scale.z );

        _vertices.push_back( _v );
        _normals.push_back( _n );

        _v = _n + _s1 - _s2;
        _v.scale( _scale.x, _scale.y, _scale.z );

        _vertices.push_back( _v );
        _normals.push_back( _n );

        _mesh = new LMesh( _vertices, _normals, _indices );

        return _mesh;
    }


    LMesh* LMeshBuilder::createFromFile( const char* filename )
    {
        LMesh* _mesh = NULL;

        vector<LVec3> _vertices;
        vector<LVec3> _normals;
        vector<LInd3> _indices;

        ifstream _fileHandle( filename );

        if ( !_fileHandle.is_open() )
        {
            cout << "LMeshBuilder::createFromFile> couldn't open the file " << filename << endl;
            return NULL;
        }

        string _line;

        getline( _fileHandle, _line );

        int _numFaces = stoi( _line );

        for ( int q = 0; q < _numFaces; q++ )
        {
            getline( _fileHandle, _line );

            int _numVertices = stoi( _line );

            for ( int p = 0; p < _numVertices; p++ )
            {
                getline( _fileHandle, _line );
                vector<string> _vStr = LMeshBuilder::_split( _line, ' ' );

                GLfloat _vx = stof( _vStr[0] );
                GLfloat _vy = stof( _vStr[1] );
                GLfloat _vz = stof( _vStr[2] );

                _vertices.push_back( LVec3( _vx, _vy, _vz ) );
            }

            int _i1 = _indices.size() * 3;
            int _i2 = _indices.size() * 3 + 1;
            int _i3 = _indices.size() * 3 + 2;

            _indices.push_back( LInd3( _i1, _i2, _i3 ) );

            LVec3 _n = _computeFaceNormal( _vertices[_i1], 
                                           _vertices[_i2], 
                                           _vertices[_i3] );
            _normals.push_back( _n );
            _normals.push_back( _n );
            _normals.push_back( _n );
        }

        _mesh = new LMesh( _vertices, _normals, _indices );
        _mesh->type = "sphere";
        
        return _mesh;
    }


    LMesh* LMeshBuilder::createFromObj( const char* filename )
    {
        LMesh* _mesh = NULL;

        vector<LVec3> _vertices;
        vector<LVec3> _normals;
        vector<LVec2> _texCoord;
        vector<LInd3> _indices;

        ifstream _fileHandle( filename );

        if ( !_fileHandle.is_open() )
        {
            cout << "LMeshBuilder::createFromObj> couldn't open the file " << filename << endl;
            return NULL;
        }

        LObjInfo _objInfo;

        _parseObj( _fileHandle, _objInfo );

        _mesh = new LMesh( _objInfo.vertices, _objInfo.normals, _objInfo.texCoords );
        _mesh->type = "obj";
        
        return _mesh;
    }

    /***********************************************************************
    * HELPER FUNCTIONS
    ************************************************************************/


    LVec3 LMeshBuilder::_computeFaceNormal( LVec3 v1, LVec3 v2, LVec3 v3, bool normalize )
    {
        LVec3 _res;

        LVec3 _v12 = v2 - v1;
        LVec3 _v23 = v3 - v2;

        _res = LVec3::cross( _v12, _v23 );
        if ( normalize )
        {
            _res.normalize();
        }

        return _res;
    }

    vector<string> LMeshBuilder::_split( const string& txt, char separator )
    {
        vector<string> _res;
                    
        int pos = txt.find( separator );
        if ( pos == std::string::npos )
        {
            _res.push_back( txt );
            return _res;
        }

        int initpos = 0;

        while ( pos != std::string::npos )
        {
            _res.push_back( txt.substr( initpos, pos - initpos ) );
            initpos = pos + 1;

            pos = txt.find( separator, initpos );
        }

        _res.push_back( txt.substr( initpos, std::min( pos, (int) txt.size() ) - initpos ) );
                    
        return _res;
    }

    void LMeshBuilder::_parseObj( ifstream& fileHandle,
                                  LObjInfo& obj )
    {
        cout << "parsing geometry" << endl;

        map<string, LObjGeometryInfo> _objects;

        string _currentObjectName;

        string _materialsFile;
        string _line;

        while ( getline( fileHandle, _line ) )
        {
            vector<string> _vStr = _split( _line, ' ' );
            // cout << "??? " << _vStr[0] << endl;

            if ( _vStr[0] == OBJ_COMMENT )
            {
                continue;
            }
            else if ( _vStr[0] == OBJ_MATERIAL_LIB )
            {
                obj.materialFile = _vStr[1];
            }
            else if ( _vStr[0] == OBJ_OBJECT_NAME )
            {
                _currentObjectName = _vStr[1];
                _objects[_currentObjectName] = LObjGeometryInfo();
            }
            else if ( _vStr[0] == OBJ_GROUP_NAME )
            {
                // cout << "obj model loader doesn't support group names yet" << endl;
                // assert( false );
                continue;
            }
            else if ( _vStr[0] == OBJ_VERTEX )
            {
                if ( _currentObjectName == "" )
                {
                    _currentObjectName = "default";
                    _objects[_currentObjectName] = LObjGeometryInfo();
                }

                LVec3 _v( stof( _vStr[1] ), stof( _vStr[2] ), stof( _vStr[3] ) );

                _objects[_currentObjectName].vertices.push_back( _v );
            }
            else if ( _vStr[0] == OBJ_NORMAL )
            {
                LVec3 _n( stof( _vStr[1] ), stof( _vStr[2] ), stof( _vStr[3] ) );

                _objects[_currentObjectName].normals.push_back( _n );
            }
            else if ( _vStr[0] == OBJ_TEXTURE )
            {
                LVec2 _t( stof( _vStr[1] ), stof( _vStr[2] ) );

                _objects[_currentObjectName].texCoords.push_back( _t );
            }
            else if ( _vStr[0] == OBJ_MATERIAL_ID )
            {
                continue;// skip, no material id support yet
            }
            else if ( _vStr[0] == OBJ_SMOOTH_SHADING )
            {
                continue;
            }
            else if ( _vStr[0] == OBJ_FACE )
            {
                for ( int q = 1; q < 4; q++ )
                {
                    vector<string> _vVertex = _split( _vStr[q], '/' );

                    obj.vertices.push_back( _objects[_currentObjectName].vertices[ stoi( _vVertex[0] ) - 1 ] );
                    obj.texCoords.push_back( _objects[_currentObjectName].texCoords[ stoi( _vVertex[1] ) - 1 ] );
                    obj.normals.push_back( _objects[_currentObjectName].normals[ stoi( _vVertex[2] ) - 1 ] );
                }
            }
            else
            {
                // cout << "not supported: " << _vStr[0] << endl;
                continue;
            }
        }

        cout << "vl: " << obj.vertices.size() << endl;
        cout << "nl: " << obj.normals.size() << endl;
        cout << "tl: " << obj.texCoords.size() << endl;

        cout << "done geometry" << endl;
    }

}