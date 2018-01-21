#version 120


struct LMaterial
{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

struct LLightDirectional
{
    vec3 direction;
    // phong model components
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

#define MAX_DIRECTIONAL_LIGHTS 2

uniform LLightDirectional u_directionalLight[MAX_DIRECTIONAL_LIGHTS];
uniform int u_numDirectionalLights;

uniform vec3 u_globalAmbientLight;

uniform LMaterial u_material[4];
uniform vec3 u_viewPos;

varying vec3 fNormal;
varying vec3 fFragPos;

vec3 computeDirectionalContribution( LLightDirectional light, LMaterial material,
                                     vec3 normal, vec3 viewDir );

void main()
{

    vec3 _normal = normalize( fNormal );
    vec3 _viewDir = normalize( u_viewPos - fFragPos );

    int _materialId = 0;

    if ( fFragPos.y != 0.0f ) { _materialId = 1; }

    vec3 _result = u_material[_materialId].ambient * u_globalAmbientLight;

    for ( int q = 0; q < u_numDirectionalLights; q++ )
    {
        if ( q > MAX_DIRECTIONAL_LIGHTS - 1 )
        {
            break;
        }

        _result += computeDirectionalContribution( u_directionalLight[q], u_material[_materialId], 
                                                   _normal, _viewDir );
    }

    gl_FragColor = vec4( _result, 1.0f );
}


vec3 computeDirectionalContribution( LLightDirectional light, LMaterial material, 
                                     vec3 normal, vec3 viewDir )
{
    vec3 _lightDir = normalize( -light.direction );
    // diffuse shadding
    float _diff = max( dot( normal, _lightDir ), 0.0 );
    // specular shading
    vec3 _reflectDir = reflect( -light.direction, normal );
    float _spec = pow( max( dot( viewDir, _reflectDir ), 0.0 ), material.shininess );
    // calculate components
    vec3 _ambient  = light.ambient * material.ambient;
    vec3 _diffuse  = _diff * light.diffuse * material.diffuse;
    vec3 _specular = _spec * light.specular * material.specular;
    
    return _ambient + _diffuse + _specular;
}