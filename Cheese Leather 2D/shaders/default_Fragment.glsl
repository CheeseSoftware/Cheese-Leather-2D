#version 330 core

in vec4 fragmentColor;
in vec2 fragmentPosition;

in vec2 UV;
out vec3 color;

uniform sampler2D myTextureSampler;

void main(){
	
	//color = clamp(vec3(fragmentPosition.x, fragmentPosition.y, fragmentPosition.x), 0.f, 1.f);
	//color = vec3(1,0,0);
	//color = vec3(fragmentColor);
	//color = fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.5453);
	color = texture( myTextureSampler, UV ).rgb;
	//color = vec3(1,0,0);
}
