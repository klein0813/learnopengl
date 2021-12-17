#version 330 core
layout (location = 0) in vec2 apos;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 texCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 oColor;
out vec2 oTexCoords;

void main () {
  gl_Position = projection * view * model * vec4(apos, 0.0, 1.0);
  oColor = color;
  oTexCoords = vec2(texCoords.x, 1.0 - texCoords.y);
}
