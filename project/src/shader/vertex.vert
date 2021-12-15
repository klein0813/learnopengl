#version 330
in vec3 apos;
layout (location = 0) in vec3 color;

out vec3 o_color;

void main () {
  gl_Position = vec4(apos, 1.0);
  o_color = color;
}
