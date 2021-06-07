#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec3 ourColor;

void main() {
	vec3 reverse = vec3(aPos.x * 0.5, aPos.y * 0.2, 1.0);	
	gl_Position = vec4(reverse, 1.0);
	ourColor  = aColor;
}

