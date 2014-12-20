#version 330 core

in vec4 fragmentColor;
in vec2 fragmentPosition;

out vec3 color;

void main(){
	
	color = clamp(vec3(fragmentPosition.x, fragmentPosition.y, fragmentPosition.x), 0.f, 1.f);
}
