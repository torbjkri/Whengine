#shader vertex
#version 460 core

layout(location = 0) in vec3 a_Position;

uniform mat4 u_ProjectionViewModel;


void main()
{
	gl_Position = u_ProjectionViewModel * vec4(a_Position, 1.0f);
};

#shader fragment
#version 460 core

layout(location = 0) out vec4 f_Color;

uniform vec3 u_ObjectColor;
uniform vec3 u_LightColor;

const float l_AmbientStrength = 0.1f;

void main()
{
	vec3 ambient = l_AmbientStrength * u_LightColor;
	vec3 color = ambient * u_ObjectColor;
	f_Color = vec4(color, 1.0f);
};