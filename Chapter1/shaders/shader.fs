#version 330 core

out vec4 FragColor;
in vec3 ourColor;
in vec3 v_position;

void main() {
	FragColor = vec4(v_position, 1.0);
}
