#version 330 core
layout (location = 0) in vec2 apos;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 texCoords;

out vec3 oColor;
out vec2 oTexCoords;

void main () {
  gl_Position = vec4(apos.x, apos.y, 0.0, 1.0);
  oColor = color;
  oTexCoords = texCoords;
}
