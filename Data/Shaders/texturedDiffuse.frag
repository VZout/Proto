#version 330 core

in vec4 v2f_positionW; // Position in world space.
in vec4 v2f_normalW; // Surface normal in world space.
in vec2 v2f_texcoord;

uniform vec4 u_EyePosW;   // Eye position in world space.
uniform vec4 u_LightPosW; // Light's position in world space.
uniform vec4 u_LightColor; // Light's diffuse and specular contribution.

uniform vec4 u_MaterialEmissive;
uniform vec4 u_MaterialDiffuse;
uniform vec4 u_MaterialSpecular;
uniform float u_MaterialShininess;

uniform vec4 u_Ambient; // Global ambient contribution.

uniform sampler2D diffuseSampler;

layout (location=0) out vec4 out_color;

void main()
{
    // Compute the emissive term.
    vec4 Emissive = u_MaterialEmissive;

    // Compute the diffuse term.
    vec4 N = normalize( v2f_normalW );
    vec4 L = normalize( u_LightPosW - v2f_positionW );
    float NdotL = max( dot( N, L ), 0 );
    vec4 Diffuse =  NdotL * u_LightColor * u_MaterialDiffuse;
    
    // Compute the specular term.
    vec4 V = normalize( u_EyePosW - v2f_positionW );
    vec4 H = normalize( L + V );
    vec4 R = reflect( -L, N );
    float RdotV = max( dot( R, V ), 0 );
    float NdotH = max( dot( N, H ), 0 );
    vec4 Specular = pow( RdotV, u_MaterialShininess ) * u_LightColor * u_MaterialSpecular;
    
    out_color = ( Emissive + u_Ambient + Diffuse + Specular ) * texture( diffuseSampler, v2f_texcoord );
}