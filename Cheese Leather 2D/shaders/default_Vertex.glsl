#version 330 core
layout(location = 0) in vec2 vertexPosition_modelspace;
layout(location = 1) in vec4 vertexColor;
layout(location = 2) in vec2 vertexUV;

out vec4 fragmentColor;
out vec2 fragmentPosition;
out vec2 UV;

uniform mat4 MVP;

void main()
{	
	//gl_Position = vec4( MVP * vec3(vertexPosition_modelspace, 1), 1); //gl_Position = MVP * gl_in.gl_Position;
	vec3 skit = vec3(vertexPosition_modelspace, 1);
	vec4 merskit = vec4(skit, 1);
	gl_Position = MVP * merskit;
	//gl_Position = MVP * vec4(vertexPosition_modelspace, 0, 1);
		
	fragmentPosition = vertexPosition_modelspace;
	fragmentColor = vertexColor;
	UV = vertexUV;
}


