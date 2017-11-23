#version 330 core

uniform vec3 u_light_ambient;
uniform vec3 u_light_diffuse;
uniform vec3 u_light_specular;
uniform vec3 u_light_position;
uniform int u_light_type;
uniform vec3 u_light_dir;

uniform vec3 u_mat_ambient;
uniform vec3 u_mat_diffuse;
uniform vec3 u_mat_specular;
uniform float u_mat_shininess;

uniform vec3 u_view_pos;

in vec3 vNormal;
in vec3 vFragPos;
out vec4 color;

void main()
{
    // ambient component

    vec3 c_ambient = u_light_ambient * u_mat_ambient;

    // diffuse component

    // check if positional or directional

    vec3 _normal = normalize( vNormal );
    vec3 _lightDir = vec3( 0.0f, 0.0f, 0.0f );

    if ( u_light_type == 1 )
    {
        _lightDir = normalize( u_light_position - vFragPos );
    }
    else
    {
        _lightDir = normalize( -u_light_dir );
    }
    
    float _diff = max( dot( _normal, _lightDir ), 0.0 );
    vec3 c_diffuse = _diff * u_light_diffuse * u_mat_diffuse;

    vec3 _viewDir = normalize( u_view_pos - vFragPos );
    vec3 _reflectDir = reflect( -_lightDir, _normal );
    float _spec = pow( max( dot( _viewDir, _reflectDir ), 0.0 ), u_mat_shininess );
    vec3 c_specular = _spec * u_light_specular * u_mat_specular;

    vec3 _res = ( c_ambient + c_diffuse + c_specular );

    color = vec4( _res, 1.0 );
}