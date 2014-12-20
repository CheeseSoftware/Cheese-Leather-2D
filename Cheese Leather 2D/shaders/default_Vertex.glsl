#version 330 core


layout(location = 0) in vec2 vertexPosition_modelspace;
layout(location = 1) in vec4 vertexColor;

out vec4 fragmentColor;
out vec2 fragmentPosition;

uniform mat3 MVP;

void main()
{	
	//gl_Position = vec4( MVP * vec3(vertexPosition_modelspace, 1), 1); //gl_Position = MVP * gl_in.gl_Position;
	gl_Position = vec4(vertexPosition_modelspace, 1, 1);
		
	fragmentPosition = vertexPosition_modelspace;

	fragmentColor = vertexColor;
}


