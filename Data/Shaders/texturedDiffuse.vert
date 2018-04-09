#version 330 core

layout(location=0) in vec3 in_Position;
layout(location=2) in vec3 in_Normal;
layout(location=8) in vec2 in_Texcoord;

out vec4 v2f_positionW; // Position in world space.
out vec4 v2f_normalW; // Surface normal in world space.
out vec2 v2f_texcoord;

// Model, View, Projection matrix.
uniform mat4 u_ModelMatrix;
uniform mat4 u_ViewMatrix;
uniform mat4 u_ProjectionMatrix;

void main()
{
    gl_Position = u_ProjectionMatrix * u_ViewMatrix * u_ModelMatrix * vec4(in_Position, 1);

    v2f_positionW = u_ModelMatrix * vec4(in_Position, 1); 
    v2f_normalW = u_ModelMatrix * vec4(in_Normal, 0);	// should be normal matrix, right?
    v2f_texcoord = in_Texcoord;
}